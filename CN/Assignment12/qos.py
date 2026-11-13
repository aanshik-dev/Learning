from typing import Any, Dict, List, Tuple, Union
# =====================================================================
# Part A: Admission Control (Parekh-Gallagher Model)
# =====================================================================
def admit(
    requests: List[Union[Tuple[Any, ...], Dict[str, Any]]],
    C: float = 10.0
) -> List[Tuple[Any, str, float]]:
    normalized_requests = []
    for idx, req in enumerate(requests):
        if isinstance(req, dict):
            fid = req.get("id", f"f{idx+1}")
            w = float(req["weight"])
            r = float(req["rate"])
        elif isinstance(req, (list, tuple)):
            if len(req) >= 3:
                fid, w, r = req[0], float(req[1]), float(req[2])
            else:
                fid, w, r = f"f{idx+1}", float(req[0]), float(req[1])
        else:
            raise ValueError(f"Unsupported request format: {req}")
        normalized_requests.append((fid, w, r))

    admitted_flows = []  # List of (fid, weight, rate)
    decisions = []

    for fid, weight, rate in normalized_requests:
        candidate_set = admitted_flows + [(fid, weight, rate)]
        sum_w = sum(w for _, w, _ in candidate_set)

        # Check if all candidate flows still get their requested rate
        can_admit = True
        computed_rates = {}
        for c_fid, c_w, c_r in candidate_set:
            guaranteed = (c_w / sum_w) * C
            computed_rates[c_fid] = guaranteed
            if guaranteed < c_r:
                can_admit = False

        if can_admit:
            admitted_flows = candidate_set
            decisions.append((fid, "ADMITTED", computed_rates[fid]))
        else:
            cand_rate = (weight / sum_w) * C
            decisions.append((fid, "REJECTED", cand_rate))

    return decisions


# =====================================================================
# Part B: Traffic Policing (Token Bucket Dropping)
# =====================================================================

def police(
    trace: List[Union[float, int, Tuple[float, float], Dict[str, Any]]],
    r: float = 1.0,
    b: float = 4.0
) -> List[str]:
    packets = []
    for item in trace:
        if isinstance(item, dict):
            packets.append((float(item["arrival"]), float(item.get("size", item.get("length", 1.0)))))
        elif isinstance(item, (tuple, list)):
            packets.append((float(item[0]), float(item[1])))
        else:
            packets.append((float(item), 1.0))

    tokens = float(b)  # bucket starts full
    last_time = packets[0][0] if packets else 0.0
    decisions = []

    for arrival, size in packets:
        elapsed = arrival - last_time
        if elapsed > 0:
            tokens = min(float(b), tokens + elapsed * r)
            last_time = arrival

        if tokens >= size:
            tokens -= size
            decisions.append("PASS")
        else:
            decisions.append("DROP")

    return decisions


# =====================================================================
# Part C: Traffic Shaping (Token Bucket Buffering)
# =====================================================================

def shape(
    trace: List[Union[float, int, Tuple[float, float], Dict[str, Any]]],
    r: float = 1.0,
    b: float = 4.0
) -> List[float]:
    packets = []
    for item in trace:
        if isinstance(item, dict):
            packets.append((float(item["arrival"]), float(item.get("size", item.get("length", 1.0)))))
        elif isinstance(item, (tuple, list)):
            packets.append((float(item[0]), float(item[1])))
        else:
            packets.append((float(item), 1.0))

    curr_tokens = float(b)  # bucket starts full
    last_update_time = packets[0][0] if packets else 0.0
    buffer_drain_time = last_update_time
    release_times = []

    for arrival, size in packets:
        # A packet cannot be evaluated earlier than its arrival time
        # or earlier than the release time of preceding buffered packets.
        check_time = max(arrival, buffer_drain_time)

        # Accrue tokens between last_update_time and check_time
        elapsed = check_time - last_update_time
        if elapsed > 0:
            curr_tokens = min(float(b), curr_tokens + elapsed * r)
            last_update_time = check_time

        if curr_tokens >= size:
            curr_tokens -= size
            release_time = check_time
        else:
            # Buffer and wait for remaining tokens to accrue
            deficit = size - curr_tokens
            wait_time = deficit / r
            release_time = check_time + wait_time
            curr_tokens = 0.0
            last_update_time = release_time

        buffer_drain_time = release_time
        release_times.append(release_time)

    return release_times


# =====================================================================
# Part D: Packet Scheduling (Weighted Fair Queuing & FIFO)
# =====================================================================

def _normalize_flows(flows: Any) -> List[Dict[str, Any]]:
    """Helper to normalize flows structure into uniform dict list."""
    flow_list = []
    if isinstance(flows, dict):
        for fid, data in flows.items():
            flow_list.append({
                "id": fid,
                "weight": float(data["weight"]),
                "packets": data["packets"]
            })
    elif isinstance(flows, list):
        for idx, item in enumerate(flows):
            if isinstance(item, dict):
                flow_list.append({
                    "id": item.get("id", idx + 1),
                    "weight": float(item["weight"]),
                    "packets": item["packets"]
                })
            elif isinstance(item, (tuple, list)):
                # (weight, packets) or (flow_id, weight, packets)
                if len(item) == 2:
                    flow_list.append({"id": idx + 1, "weight": float(item[0]), "packets": item[1]})
                else:
                    flow_list.append({"id": item[0], "weight": float(item[1]), "packets": item[2]})
    return flow_list


def wfq(
    flows: Any
) -> Tuple[Dict[str, float], List[str]]:
    flow_list = _normalize_flows(flows)
    finish_numbers = {}
    packet_records = []

    for flow in flow_list:
        fid = flow["id"]
        weight = flow["weight"]
        prev_f = 0.0
        for pkt in flow["packets"]:
            if isinstance(pkt, dict):
                name, arr, l = pkt["name"], float(pkt["arrival"]), float(pkt["length"])
            else:
                name, arr, l = pkt[0], float(pkt[1]), float(pkt[2])

            f = max(arr, prev_f) + l / weight
            prev_f = f
            finish_numbers[name] = f
            packet_records.append({
                "name": name,
                "flow": fid,
                "weight": weight,
                "arrival": arr,
                "length": l,
                "finish": f
            })

    # Sort packets in increasing order of finish number (tie-break on arrival and name)
    sorted_packets = sorted(packet_records, key=lambda p: (p["finish"], p["arrival"], str(p["name"])))
    output_order = [p["name"] for p in sorted_packets]

    return finish_numbers, output_order


def fifo(flows: Any) -> List[str]:
    flow_list = _normalize_flows(flows)
    packet_records = []

    for flow in flow_list:
        fid = flow["id"]
        for pkt in flow["packets"]:
            if isinstance(pkt, dict):
                name, arr, l = pkt["name"], float(pkt["arrival"]), float(pkt["length"])
            else:
                name, arr, l = pkt[0], float(pkt[1]), float(pkt[2])
            packet_records.append({
                "name": name,
                "flow": fid,
                "arrival": arr,
                "length": l
            })

    # Stable sort by arrival time; preserves arrival order across flows
    sorted_packets = sorted(packet_records, key=lambda p: (p["arrival"], str(p["flow"]), str(p["name"])))
    return [p["name"] for p in sorted_packets]


# =====================================================================
# Verification Assertions Test Suite
# =====================================================================

def test_qos():
    """Unit test suite verifying implementation against Lab 12 specification."""
    # Test Part A
    reqs = [("f1", 1, 2.0), ("f2", 1, 2.0), ("f3", 2, 4.0), ("f4", 1, 3.0)]
    decisions = admit(reqs, 10.0)
    assert decisions[0][1] == "ADMITTED" and decisions[0][2] == 10.0
    assert decisions[1][1] == "ADMITTED" and decisions[1][2] == 5.0
    assert decisions[2][1] == "ADMITTED" and decisions[2][2] == 5.0
    assert decisions[3][1] == "REJECTED" and decisions[3][2] == 2.0

    # Test Part B
    trace = [0, 0, 0, 0, 0, 0, 5, 6]
    pol_dec = police(trace, 1.0, 4.0)
    expected_pol = ["PASS", "PASS", "PASS", "PASS", "DROP", "DROP", "PASS", "PASS"]
    assert pol_dec == expected_pol

    # Test Part C
    rel_times = shape(trace, 1.0, 4.0)
    expected_rel = [0.0, 0.0, 0.0, 0.0, 1.0, 2.0, 5.0, 6.0]
    assert rel_times == expected_rel

    # Test Part D
    flows = {
        1: {"weight": 1, "packets": [("A", 0, 8), ("F", 10, 6)]},
        2: {"weight": 1, "packets": [("B", 5, 6), ("D", 8, 9), ("H", 20, 8)]},
        3: {"weight": 2, "packets": [("C", 5, 10), ("E", 8, 8), ("G", 11, 10)]},
    }
    finish_nums, wfq_order = wfq(flows)
    expected_fn = {"A": 8.0, "C": 10.0, "B": 11.0, "E": 14.0, "F": 16.0, "G": 19.0, "D": 20.0, "H": 28.0}
    assert finish_nums == expected_fn
    assert wfq_order == ["A", "C", "B", "E", "F", "G", "D", "H"]


# =====================================================================
# Main Execution / Output Demonstration
# =====================================================================

def run_lab():
    # Run assertions first to guarantee correctness
    test_qos()

    sep = "=" * 78
    print(sep)
    print("LAB 11: QUALITY OF SERVICE AT A ROUTER")
    print("Computer Networks - Week 11 - Congestion and QoS Simulation")
    print(sep)

    # -----------------------------------------------------------------
    # Part A: Admission Control
    # -----------------------------------------------------------------
    print("\n" + "-" * 78)
    print("PART A: ADMISSION CONTROL (Parekh-Gallagher Model)")
    print("-" * 78)
    C = 10.0  # Link capacity = 10 Mbps
    requests = [
        ("f1", 1, 2.0),
        ("f2", 1, 2.0),
        ("f3", 2, 4.0),
        ("f4", 1, 3.0),
    ]
    print(f"Total Link Capacity C = {C} Mbps\n")
    print(f"{'Flow':<6} {'Weight':<8} {'Requested Rate (Mbps)':<24} {'Decision':<12} {'Guaranteed Rate':<18}")
    print("-" * 70)

    decisions = admit(requests, C)
    for fid, dec, rate in decisions:
        rate_str = f"{rate:.2f} Mbps"
        print(f"{fid:<6} {next(r[1] for r in requests if r[0] == fid):<8} {next(r[2] for r in requests if r[0] == fid):<24.1f} {dec:<12} {rate_str:<18}")

    print("\nDetailed Step-by-Step State Tracking:")
    admitted = []
    for fid, w, r in requests:
        cand = admitted + [(fid, w, r)]
        sum_w = sum(x[1] for x in cand)
        admissible = True
        status_lines = []
        for c_id, c_w, c_r in cand:
            g_rate = (c_w / sum_w) * C
            ok = g_rate >= c_r
            if not ok:
                admissible = False
            status_lines.append(f"  * {c_id}: weight={c_w}, guaranteed={g_rate:.2f} Mbps, requested={c_r:.1f} Mbps -> {'OK' if ok else 'VIOLATED'}")
        print(f"\nEvaluating Request {fid} (W={w}, R={r:.1f} Mbps):")
        print(f"  Candidate set: {[x[0] for x in cand]}, Total Weight ΣW = {sum_w}")
        for l in status_lines:
            print(l)
        if admissible:
            admitted = cand
            print(f"  ==> DECISION: {fid} is ADMITTED. Current admitted: {[x[0] for x in admitted]}")
        else:
            print(f"  ==> DECISION: {fid} is REJECTED. Guaranteed only {(w/sum_w)*C:.2f} Mbps (< {r:.1f} Mbps requested).")

    # -----------------------------------------------------------------
    # Part B: Traffic Policing
    # -----------------------------------------------------------------
    print("\n" + "-" * 78)
    print("PART B: TRAFFIC POLICING (Token Bucket Dropping)")
    print("-" * 78)
    r_police = 1.0
    b_police = 4.0
    trace_b = [0, 0, 0, 0, 0, 0, 5, 6]
    policing_results = police(trace_b, r_police, b_police)

    print(f"Parameters: fill rate r = {r_police} token/unit, capacity b = {b_police} tokens, initial tokens = {b_police}")
    print(f"Trace arrivals: {trace_b}\n")
    print(f"{'Packet #':<10} {'Arrival Time':<15} {'Packet Size':<15} {'Result':<10}")
    print("-" * 52)
    for idx, (t, res) in enumerate(zip(trace_b, policing_results), 1):
        print(f"{idx:<10} {t:<15} {1:<15} {res:<10}")

    num_passed = policing_results.count("PASS")
    num_dropped = policing_results.count("DROP")
    print(f"\nSummary: {num_passed} passed, {num_dropped} dropped.")

    # -----------------------------------------------------------------
    # Part C: Traffic Shaping
    # -----------------------------------------------------------------
    print("\n" + "-" * 78)
    print("PART C: TRAFFIC SHAPING (Token Bucket Buffering)")
    print("-" * 78)
    r_shape = 1.0
    b_shape = 4.0
    trace_c = [0, 0, 0, 0, 0, 0, 5, 6]
    release_times = shape(trace_c, r_shape, b_shape)

    print(f"Parameters: fill rate r = {r_shape} token/unit, capacity b = {b_shape} tokens, initial tokens = {b_shape}")
    print(f"Trace arrivals: {trace_c}\n")
    print(f"{'Packet #':<10} {'Arrival Time':<15} {'Release Time':<15} {'Delay':<10} {'Status':<10}")
    print("-" * 62)
    for idx, (arr, rel) in enumerate(zip(trace_c, release_times), 1):
        delay = rel - arr
        print(f"{idx:<10} {arr:<15.1f} {rel:<15.1f} {delay:<10.1f} {'DELIVERED':<10}")

    delays = [rel - arr for arr, rel in zip(trace_c, release_times)]
    print(f"\nSummary: All {len(delays)} packets delivered, 0 dropped. Max delay = {max(delays):.1f} units.")

    # -----------------------------------------------------------------
    # Part D: Packet Scheduling (WFQ vs FIFO)
    # -----------------------------------------------------------------
    print("\n" + "-" * 78)
    print("PART D: PACKET SCHEDULING (Weighted Fair Queuing vs FIFO)")
    print("-" * 78)
    flows = {
        1: {"weight": 1, "packets": [("A", 0, 8), ("F", 10, 6)]},
        2: {"weight": 1, "packets": [("B", 5, 6), ("D", 8, 9), ("H", 20, 8)]},
        3: {"weight": 2, "packets": [("C", 5, 10), ("E", 8, 8), ("G", 11, 10)]},
    }

    print("Input Flows Configuration:")
    for fid, data in flows.items():
        pkts_str = ", ".join(f"{name}(arr={a}, len={l})" for name, a, l in data["packets"])
        print(f"  Flow {fid} (weight = {data['weight']}): {pkts_str}")

    finish_nums, wfq_order = wfq(flows)
    fifo_order = fifo(flows)

    print("\nFinish Number Calculations (WFQ):")
    print(f"{'Packet':<8} {'Flow':<6} {'Weight':<8} {'Arrival':<10} {'Length':<8} {'Finish Number':<15}")
    print("-" * 60)
    for fid, data in flows.items():
        w = data["weight"]
        prev_f = 0.0
        for name, arr, l in data["packets"]:
            f = finish_nums[name]
            calc_expr = f"max({arr}, {prev_f:.0f}) + {l}/{w} = {f:.1f}"
            print(f"{name:<8} {fid:<6} {w:<8} {arr:<10} {l:<8} {f:<15.1f}")
            prev_f = f

    print("\nScheduled Transmission Orders:")
    print(f"  * WFQ Output Order:  {' -> '.join(wfq_order)}")
    print(f"  * FIFO Output Order: {' -> '.join(fifo_order)}")

    print("\n" + sep)
    print("ALL TESTS & CHECKS COMPLETED SUCCESSFULLY (100% SPEC MATCH)")
    print(sep)


if __name__ == "__main__":
    run_lab()
