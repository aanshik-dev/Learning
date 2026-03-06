import numpy as np
import matplotlib.pyplot as plt

# Generate data
np.random.seed(42)
x = np.random.randn(100)
y = np.random.randn(100)
colors = np.random.rand(100)
sizes = np.random.randint(20, 200, 100)

# Basic scatter
plt.figure(figsize=(8, 6))
plt.scatter(x, y, c=colors, s=sizes, alpha=0.6, cmap='viridis')
plt.colorbar(label='Color Intensity')
plt.title('Scatter Plot with Color and Size Variation')
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.grid(True, alpha=0.3)
plt.show()

# Scatter with different marker styles
markers = ['o', 's', '^', 'D', 'v', '<', '>', 'p', '*', 'h']
x = np.arange(1, 11)
y = np.random.randint(1, 10, 10)

plt.figure(figsize=(10, 4))
for i, marker in enumerate(markers):
    plt.scatter(x[i], y[i], marker=marker, s=200, label=f'Marker: {marker}')
plt.legend()
plt.grid(True, alpha=0.3)
plt.title('Different Marker Styles')
plt.show()