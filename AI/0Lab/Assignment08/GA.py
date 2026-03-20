# 0 10 15 20 25 10 0 35 25 17 15 35 0 30 28 20 25 30 0 23 25 17 28 23 0

import random
import numpy as np
import matplotlib.pyplot as plt


def tournament(pop, fitness, k=3):
    selected = random.sample(list(zip(pop, fitness)), k)
    selected.sort(key=lambda x: x[1])
    return selected[0][0]

def tsp_fitness(path, dist):
    total = 0
    for i in range(len(path) - 1):
        total += dist[path[i]][path[i+1]]
    total += dist[path[-1]][path[0]]
    return total

def order_cross(p1, p2):
    n = len(p1)
    a, b = sorted(random.sample(range(1, n), 2))

    child = [-1]*n
    child[a:b] = p1[a:b]

    fill = [x for x in p2 if x not in child]
    j = 0
    for i in range(n):
        if child[i] == -1:
            child[i] = fill[j]
            j += 1
    return child

def swap_mutation(path):
    i, j = random.sample(range(1, len(path)), 2)
    path[i], path[j] = path[j], path[i]
    return path

def solve_tsp(dist, pop_size=50, generations=100):
    n = len(dist)
    pop = []
    for z in range(pop_size):
        perm = list(range(1, n))
        random.shuffle(perm)
        pop.append([0] + perm)

    best_history = []

    for _ in range(generations):
        fitness = [tsp_fitness(p, dist) for p in pop]
        new_pop = []

        for _ in range(pop_size):
            p1 = tournament(pop, fitness)
            p2 = tournament(pop, fitness)
            child = order_cross(p1, p2)

            if random.random() < 0.2:
                child = swap_mutation(child)
            new_pop.append(child)

        pop = new_pop
        best_history.append(min(fitness))

    best = min(pop, key=lambda x: tsp_fitness(x, dist))
    return best, tsp_fitness(best, dist), best_history


# Optimal Power Flow (OPF)
def opf_fitness(ind, a, b, c, demand):
    cost = sum(a[i] + b[i]*ind[i] + c[i]*(ind[i]**2) for i in range(len(ind)))
    penalty = 1000 * (sum(ind) - demand)**2
    return cost + penalty

def sbx(p1, p2, eta_c=20):
    c1, c2 = [], []
    for i in range(len(p1)):
        u = random.random()
        if u <= 0.5:
            beta = (2*u)**(1/(eta_c+1))
        else:
            beta = (1/(2*(1-u)))**(1/(eta_c+1))
        child1 = 0.5*((1+beta)*p1[i] + (1-beta)*p2[i])
        child2 = 0.5*((1-beta)*p1[i] + (1+beta)*p2[i])
        c1.append(child1)
        c2.append(child2)
    return c1, c2

def polynomial_mutation(ind, xmin, xmax, eta_m=20):
    new = []
    for i in range(len(ind)):
        u = random.random()
        if u < 0.5:
            delta = (2*u)**(1/(eta_m+1)) - 1
        else:
            delta = 1 - (2*(1-u))**(1/(eta_m+1))

        x = ind[i] + (xmax[i] - xmin[i]) * delta

        x = max(xmin[i], min(xmax[i], x))
        new.append(x)
    return new


def solve_opf(a, b, c, pmin, pmax, demand, eta_c=20,
              pop_size=50, generations=100):

    n = len(a)

    pop = [[random.uniform(pmin[i], pmax[i]) for i in range(n)]
          for _ in range(pop_size)]

    best_history = []

    for _ in range(generations):
        fitness = [opf_fitness(ind, a, b, c, demand) for ind in pop]
        new_pop = []

        for _ in range(pop_size//2):
            p1 = tournament(pop, fitness)
            p2 = tournament(pop, fitness)

            c1, c2 = sbx(p1, p2, eta_c)

            c1 = polynomial_mutation(c1, pmin, pmax)
            c2 = polynomial_mutation(c2, pmin, pmax)

            new_pop.extend([c1, c2])

        pop = new_pop
        best_history.append(min(fitness))

    best = min(pop, key=lambda x: opf_fitness(x, a, b, c, demand))
    return best, opf_fitness(best, a, b, c, demand), best_history


dist = [
    [0,10,15,20],
    [10,0,35,25],
    [15,35,0,30],
    [20,25,30,0]
]

path, cost, hist = solve_tsp(dist)

print("\nTSP Solution:")
print("Path:", path + [0])
print("Distance:", cost)

plt.plot(hist)
plt.title("TSP Convergence")
plt.xlabel("Generation")
plt.ylabel("Best Distance")
plt.show()

a = [10, 15]
b = [0.5, 0.4]
c = [0.02, 0.015]
pmin = [20, 30]
pmax = [80, 120]
demand = 100

sol1, cost1, hist1 = solve_opf(a, b, c, pmin, pmax, demand, eta_c=2)
sol2, cost2, hist2 = solve_opf(a, b, c, pmin, pmax, demand, eta_c=20)

print("\nOPF Solution (eta_c=20):")
print("Power:", [round(x,2) for x in sol2])
print("Cost:", round(cost2,2))

plt.plot(hist1, label="eta_c=2")
plt.plot(hist2, label="eta_c=20")
plt.legend()
plt.title("OPF Convergence Comparison")
plt.xlabel("Generation")
plt.ylabel("Cost")
plt.show()