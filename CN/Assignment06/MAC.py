import numpy as np
import matplotlib.pyplot as plt

# Fixed random seed for reproducibility
np.random.seed(42)

# Parameters
H = 10000  # Number of frame-times
G_values = np.linspace(0.1, 3.0, 30)  # Sweep G from 0.1 to 3.0

# Part A: Pure Aloha
def simulate_pure_aloha(G, H):
    # Total arrivals - Poisson(G * H)
    num_arrivals = np.random.poisson(G * H)
    if num_arrivals == 0:
        return 0.0
    
    # Place arrivals uniformly in time [0, H]
    arrival_times = np.sort(np.random.uniform(0, H, num_arrivals))
    
    successful = 0
    for i in range(num_arrivals):
        t = arrival_times[i]
        # Vulnerable window: (t - 1, t + 1)
        left_conflict = (i > 0) and (t - arrival_times[i - 1] < 1.0)
        right_conflict = (i < num_arrivals - 1) and (arrival_times[i + 1] - t < 1.0)
        
        if not left_conflict and not right_conflict:
            successful += 1
            
    return successful / H

# Part B: Slotted Aloha
def simulate_slotted_aloha(G, H):
    # Poisson count of transmissions per slot (H slots)
    slot_counts = np.random.poisson(G, H)
    # Success if exactly 1 transmission in a slot
    successful = np.sum(slot_counts == 1)
    return successful / H

# Part C: 1-Persistent CSMA
def simulate_csma(G, H, a=0.01):
    num_arrivals = np.random.poisson(G * H)
    if num_arrivals == 0:
        return 0.0
    
    arrival_times = np.sort(np.random.uniform(0, H, num_arrivals))
    
    current_time = 0.0
    successful = 0
    i = 0
    
    while i < num_arrivals:
        # If channel is idle when arrival occurs, transmission starts at arrival time
        if arrival_times[i] >= current_time:
            trans_start = arrival_times[i]
        else:
            # Channel is busy; station defers and attempts transmission at current_time
            trans_start = current_time
        
        # Collect all arrivals that will transmit in this frame cycle:
        # 1. Stations that deferred during the previous frame and release at trans_start
        # 2. Stations arriving within the propagation delay window [trans_start, trans_start + a)
        batch_count = 0
        while i < num_arrivals and arrival_times[i] < trans_start + a:
            batch_count += 1
            i += 1
            
        # Transmission succeeds only if exactly ONE station transmitted
        if batch_count == 1:
            successful += 1
            
        # Channel remains busy for 1.0 frame-time from the start of transmission
        current_time = trans_start + 1.0
        
    return successful / H
# Measure Throughput (S) across G
S_pure = [simulate_pure_aloha(g, H) for g in G_values]
S_slotted = [simulate_slotted_aloha(g, H) for g in G_values]
S_csma_001 = [simulate_csma(g, H, a=0.01) for g in G_values]

# Analytical Curves
S_pure_analytical = G_values * np.exp(-2 * G_values)
S_slotted_analytical = G_values * np.exp(-G_values)

# Print Peak Results
print(f"Pure Aloha Measured Peak: {max(S_pure):.3f} at G = {G_values[np.argmax(S_pure)]:.2f}")
print(f"Slotted Aloha Measured Peak: {max(S_slotted):.3f} at G = {G_values[np.argmax(S_slotted)]:.2f}")
print(f"CSMA (a=0.01) Measured Peak: {max(S_csma_001):.3f} at G = {G_values[np.argmax(S_csma_001)]:.2f}")

# Plotting Part A, B, C Comparison
plt.figure(figsize=(10, 6))
plt.plot(G_values, S_pure, 'bo', label='Pure Aloha (Simulated)')
plt.plot(G_values, S_pure_analytical, 'b--', label=r'Pure Aloha Analytical ($S=Ge^{-2G}$)')

plt.plot(G_values, S_slotted, 'ro', label='Slotted Aloha (Simulated)')
plt.plot(G_values, S_slotted_analytical, 'r--', label=r'Slotted Aloha Analytical ($S=Ge^{-G}$)')

plt.plot(G_values, S_csma_001, 'g-o', label='1-persistent CSMA (a=0.01)')

plt.title('MAC Protocol Throughput Comparison')
plt.xlabel('Offered Load (G)')
plt.ylabel('Throughput (S)')
plt.grid(True)
plt.legend()
plt.savefig('./Assignment06/throughputComparison.png')
plt.show()

# Part D3: CSMA with varying propagation delays
S_csma_005 = [simulate_csma(g, H, a=0.05) for g in G_values]
S_csma_010 = [simulate_csma(g, H, a=0.10) for g in G_values]

print("\n--- Part D3: CSMA Propagation Delay Impact ---")
print(f"CSMA (a=0.01) Peak: {max(S_csma_001):.3f} at G = {G_values[np.argmax(S_csma_001)]:.2f}")
print(f"CSMA (a=0.05) Peak: {max(S_csma_005):.3f} at G = {G_values[np.argmax(S_csma_005)]:.2f}")
print(f"CSMA (a=0.10) Peak: {max(S_csma_010):.3f} at G = {G_values[np.argmax(S_csma_010)]:.2f}")

plt.figure(figsize=(10, 6))
plt.plot(G_values, S_csma_001, 'g-o', label='CSMA (a=0.01)')
plt.plot(G_values, S_csma_005, 'c-o', label='CSMA (a=0.05)')
plt.plot(G_values, S_csma_010, 'm-o', label='CSMA (a=0.10)')
plt.title('1-persistent CSMA Throughput for Varying Propagation Delays (a)')
plt.xlabel('Offered Load (G)')
plt.ylabel('Throughput (S)')
plt.grid(True)
plt.legend()
plt.savefig('./Assignment06/csmaDelayImpact.png')
plt.show()