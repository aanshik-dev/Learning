import random

def path_length(n):
    length = 0
    while n > 0:
        n = random.randint(0, n - 1)
        length += 1
    return length

def lvl_simulate(test = 10000, start=50):
    total = 0
    for _ in range(test):
        total += path_length(start)
    return total / test


def even_probability(n):
    if n == 0:
        return 1.0
    prefix = 1.0
    p = 1.0
    for k in range(1, n + 1):
        p = 1 - prefix / k
        prefix += p
    return p

print(even_probability(2000))




print("Level 1 :", lvl_simulate())

  

