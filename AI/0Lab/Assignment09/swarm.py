import numpy as np
from sklearn.datasets import fetch_openml
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

w, c1, c2, num_particles, num_iterations = input("Enter w c1 c2 particles iterations: ").split()
w = float(w)
c1 = float(c1)
c2 = float(c2)
num_particles = int(num_particles)
num_iterations = int(num_iterations)

np.random.seed(42)

boston = fetch_openml(name='boston', version=1, as_frame=False, parser='liac-arff')
X = boston.data.astype(float)
y = boston.target.astype(float)

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

X_train = np.c_[np.ones(len(X_train)), X_train]
X_test = np.c_[np.ones(len(X_test)), X_test]

dim = X_train.shape[1]

positions = np.random.uniform(-50, 50, (num_particles, dim))
velocities = np.random.uniform(-1, 1, (num_particles, dim))

pbest = positions.copy()
pbest_scores = np.full(num_particles, np.inf)

gbest = positions[0].copy()
gbest_score = np.inf

def mse(wt, X, y):
    return np.mean((y - X.dot(wt))**2)

for _ in range(num_iterations):
    for i in range(num_particles):
        score = mse(positions[i], X_train, y_train)
        if score < pbest_scores[i]:
            pbest_scores[i] = score
            pbest[i] = positions[i].copy()
        if score < gbest_score:
            gbest_score = score
            gbest = positions[i].copy()
    for i in range(num_particles):
        r1 = np.random.rand(dim)
        r2 = np.random.rand(dim)
        velocities[i] = w * velocities[i] + c1 * r1 * (pbest[i] - positions[i]) + c2 * r2 * (gbest - positions[i])
        positions[i] = positions[i] + velocities[i]
        positions[i] = np.clip(positions[i], -50, 50)

train_mse = mse(gbest, X_train, y_train)
test_mse = mse(gbest, X_test, y_test)

best_weights = [round(float(v), 3) for v in gbest]

output = f"""Best Weights: {best_weights}
Training MSE: {round(train_mse, 2)}
Testing MSE: {round(test_mse, 2)}"""

print(output)

with open("Learning/AI/0Lab/Assignment09/output.txt", "w") as f:
    f.write(output)