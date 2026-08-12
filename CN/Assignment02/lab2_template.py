import math
import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

C_LIGHT = 3e8
TX_DBM, RX_SENS_DBM = 0.0, -40.0
SNR_DB = 25
CU_ALPHA, FI_ALPHA = 8.0, 0.3
CAT5E_ALPHA_100MHZ, LAN_BUDGET_DB = 220.0, 22.0
CABLES = [("Cat5e", 100e6), ("Cat6", 250e6), ("Cat6a", 500e6)]
BANDS = [900e6, 2400e6, 5000e6]

def snr_db_to_linear(snr_db):
    return 10.0 ** (snr_db / 10.0)

def levels_for_rate(B, target_rate):
    return 2.0 ** (target_rate / (2.0 * B))

def shannon_capacity_db(B, snr_db):
    linear_snr = snr_db_to_linear(snr_db)
    return B * math.log2(1.0 + linear_snr)

def max_span_km(tx_dbm, rx_sens_dbm, alpha_db_km):
    return (tx_dbm - rx_sens_dbm) / alpha_db_km

def fspl_db(d_m, f_hz):
    return 20.0 * math.log10(d_m) + 20.0 * math.log10(f_hz) + 20.0 * math.log10(4.0 * math.pi / C_LIGHT)

def ber_bpsk(ebn0_db):
    ebn0_linear = 10.0 ** (ebn0_db / 10.0)
    return 0.5 * math.erfc(math.sqrt(ebn0_linear))

def run():
    print("Part A Bandwidth -> bit rate (SNR = %d dB)" % SNR_DB)
    for name, B in CABLES:
        print("", name, levels_for_rate(B, 1e9), shannon_capacity_db(B, SNR_DB))
    print("Part B copper/fibre span, Cat5e@100MHz reach:",
          max_span_km(TX_DBM, RX_SENS_DBM, CU_ALPHA),
          max_span_km(TX_DBM, RX_SENS_DBM, FI_ALPHA),
          LAN_BUDGET_DB / CAT5E_ALPHA_100MHZ * 1000)
    print("Part C received power at 5 km per band:")
    for f in BANDS:
        print("", f/1e6, "MHz:", TX_DBM - fspl_db(5000, f))

    s = np.linspace(0, 40, 200)
    plt.figure()
    for name, B in CABLES:
        plt.plot(s, [shannon_capacity_db(B, x)/1e6 for x in s], label=name)
    plt.axvline(SNR_DB, ls='--', color='grey')
    plt.legend(); plt.xlabel("SNR (dB)"); plt.ylabel("Capacity (Mb/s)"); plt.title("A")
    plt.savefig("partA.png")

    d = np.linspace(0.01, 60, 400)
    plt.figure()
    plt.plot(d, TX_DBM - CU_ALPHA*d, label="copper")
    plt.plot(d, TX_DBM - FI_ALPHA*d, label="fibre")
    plt.axhline(RX_SENS_DBM, ls='--', color='grey')
    plt.legend(); plt.xlabel("distance (km)"); plt.ylabel("dBm"); plt.title("B")
    plt.savefig("partB.png")

    dm = np.linspace(10, 20000, 400)
    plt.figure()
    for f in BANDS:
        plt.plot(dm/1000, [TX_DBM - fspl_db(x, f) for x in dm], label=f"{f/1e6:.0f} MHz")
    plt.legend(); plt.xlabel("distance (km)"); plt.ylabel("dBm"); plt.title("C")
    plt.savefig("partC.png")

    e = np.linspace(0, 12, 400)
    plt.figure(); plt.semilogy(e, [ber_bpsk(x) for x in e])
    plt.axhline(1e-3, ls='--', color='crimson')
    plt.xlabel("Eb/N0 (dB)"); plt.ylabel("BER"); plt.title("D")
    plt.savefig("partD.png")

if __name__ == "__main__":
    run()