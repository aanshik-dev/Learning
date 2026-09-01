import math
import random

# LEVEL 1: Monte Carlo Simulation
def path_length(n):
    # Counts how many jumps it takes to reach 0 from n
    length = 0
    while n > 0:
        n = random.randint(0, n - 1)
        length += 1
    return length


def lvl_simulate(trials=10000, start=50):
    # Runs the simulation 10,000 times and returns the average steps
    random.seed(42)
    total_steps = 0
    for _ in range(trials):
        total_steps += path_length(start)
    return total_steps / trials


# LEVEL 2: Exact Probability of Even Path Length
def even_probability(n):
    # Base case: 0 jumps is even, so probability is 1.0
    if n == 0:
        return 1.0
    prefix_sum = 1.0  # Keeps running sum of all previous P(j)
    p = 1.0
    # Calculate P(even) iteratively in O(n) time
    for k in range(1, n + 1):
        p = 1.0 - (prefix_sum / k)
        prefix_sum += p
    return p


# LEVEL 3: Expected Path Length for huge numbers (n = 10^500)
def expected_path_length_large(exponent=500):
    # Expected length from state n is the Harmonic number H_n
    # Formula: H_n ≈ ln(n) + 0.5772156649 (Euler's constant)
    # Since n = 10^500, ln(10^500) = 500 * ln(10)    
    gamma = 0.5772156649015329
    ln_n = exponent * math.log(10)
    return ln_n + gamma


print("Level 1 (Mean path length for n=50):", lvl_simulate())
print("Level 2 (Even probability for n=2000):", even_probability(2000))
print("Level 3 (Expected path length for n=10^500):", expected_path_length_large(500))