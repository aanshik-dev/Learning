def run_gbn(payloads, W, drops, detailed = False):
    N = len(payloads)
    base = expected = transmissions = round_num = 0
    sent_in, delivery_order, tx_counts = {}, [], {}

    while base < N:
        round_num += 1
        sent_this_round = []
        for seq in range(base, min(base + W, N)):
            if seq not in sent_in or sent_in[seq] < round_num:
                sent_in[seq] = round_num
                transmissions += 1
                tx_counts[seq] = tx_counts.get(seq, 0) + 1
                sent_this_round.append(seq)

        # Receiver & ACK processing
        delivered = [s for s in sorted(sent_this_round) if (round_num, "data", s) not in drops]
        ack_to_send = None
        for seq in delivered:
            if seq == expected:
                delivery_order.append(payloads[seq])
                expected += 1
                ack_to_send = expected - 1
        if delivered and ack_to_send is None and expected > 0:
            ack_to_send = expected - 1

        ack_delivered = (ack_to_send is not None) and ((round_num, "ack", ack_to_send) not in drops)
        if ack_delivered:
            base = ack_to_send + 1

        if detailed:
            ack_str = f"cumulative ACK {ack_to_send}, base -> {base}" if ack_delivered else f"no ack delivered, base stays {base}"
            print(f"  GBN Round {round_num}: send {sent_this_round}, {ack_str}")

    resent = [s for s, c in tx_counts.items() if c > 1]
    return transmissions, round_num, delivery_order, resent


def run_sr(payloads: list, W: int, drops: set, detailed: bool = False):
    N = len(payloads)
    base = rcv_base = transmissions = round_num = 0
    acked, sent_in, rcv_buffer, delivery_order, tx_counts = set(), {}, {}, [], {}

    while base < N:
        round_num += 1
        sent_this_round = []
        for seq in range(base, min(base + W, N)):
            if seq not in acked and (seq not in sent_in or sent_in[seq] < round_num):
                sent_in[seq] = round_num
                transmissions += 1
                tx_counts[seq] = tx_counts.get(seq, 0) + 1
                sent_this_round.append(seq)

        # Receiver & ACK processing
        delivered = [s for s in sorted(sent_this_round) if (round_num, "data", s) not in drops]
        acks_to_send = []
        for seq in delivered:
            if rcv_base <= seq < rcv_base + W:
                if seq not in rcv_buffer:
                    rcv_buffer[seq] = payloads[seq]
                acks_to_send.append(seq)
            elif seq < rcv_base:
                acks_to_send.append(seq)

        while rcv_base in rcv_buffer:
            delivery_order.append(rcv_buffer.pop(rcv_base))
            rcv_base += 1

        delivered_acks = [a for a in acks_to_send if (round_num, "ack", a) not in drops]
        for a in delivered_acks:
            acked.add(a)

        while base in acked:
            base += 1

        if detailed:
            print(f"  SR Round {round_num}: send {sent_this_round}, individual ACKs {delivered_acks}, base -> {base}")

    resent = [s for s, c in tx_counts.items() if c > 1]
    return transmissions, round_num, delivery_order, resent

scenarios = [
    ("S0 clean channel", 6, 4, set()),
    ("S1 one data frame lost", 6, 4, {(1, "data", 2)}),
    ("S2 first frame of full window", 8, 8, {(1, "data", 0)}),
    ("S3 one ack lost", 4, 4, {(1, "ack", 3)}),
]

# Parts A & B: Summary Verification
print("\n--- Parts A & B: Test Results ---")
for label, N, W, drops in scenarios:
    p = list(range(N))
    tx_g, r_g, ord_g, _ = run_gbn(p, W, drops)
    tx_s, r_s, ord_s, _ = run_sr(p, W, drops)
    print(f"{label} (N={N}, W={W}):")
    print(f"  GBN -> {tx_g} transmissions, {r_g} rounds, order: {ord_g}")
    print(f"  SR  -> {tx_s} transmissions, {r_s} rounds, order: {ord_s}")

# Part A & B: S2 Per-round Logs
print("\n--- S2 Per-Round Logs ---")
print("Go-Back-N:")
run_gbn(list(range(8)), 8, {(1, "data", 0)}, detailed=True)
print("Selective Repeat:")
run_sr(list(range(8)), 8, {(1, "data", 0)}, detailed=True)

# Part C: Retransmissions
print("\n--- Part C: Comparison & Resent Sequences ---")
for label, N, W, drops in [("S1", 6, 4, {(1, "data", 2)}), ("S2", 8, 8, {(1, "data", 0)})]:
    p = list(range(N))
    tx_g, _, _, resent_g = run_gbn(p, W, drops)
    tx_s, _, _, resent_s = run_sr(p, W, drops)
    print(f"{label} (N={N}, W={W}):")
    print(f"  GBN total tx: {tx_g}, resent seqs: {resent_g}")
    print(f"  SR  total tx: {tx_s}, resent seqs: {resent_s}")

# Part D: Overhead Calculation
print("\n--- Part D: Retransmission Overhead ---")
for label, N, W, drops in [("S1", 6, 4, {(1, "data", 2)}), ("S2", 8, 8, {(1, "data", 0)})]:
    p = list(range(N))
    tx_g, _, _, _ = run_gbn(p, W, drops)
    tx_s, _, _, _ = run_sr(p, W, drops)
    ov_g, ov_s = tx_g / N, tx_s / N
    print(f"{label}: GBN overhead = {tx_g}/{N} ({ov_g:.3f}) | SR overhead = {tx_s}/{N} ({ov_s:.3f}) | gap = {ov_g - ov_s:.3f}")
print()