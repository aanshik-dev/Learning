<!-- Matplot -->

<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **Pandas Notes** 🔥🐦‍🔥

<br>

## 🐦‍🔥 Introduction to matplotlib

Matplotlib is a comprehensive library for creating static, animated, and interactive visualizations in Python. It's the most popular plotting library in the Python ecosystem.

### 🔥 Installation

```py
# Install Matplotlib
pip install matplotlib

# Import convention
import matplotlib.pyplot as plt
import numpy as np
```

<br>

## 🐦‍🔥 LINE PLOT

```py
# Basic data
x = np.array([1, 2, 3, 4, 5])
y = np.array([2, 4, 6, 8, 10])

# Create a simple plot
plt.plot(x, y)
plt.show()  # Display the plot
```

```py
# Generate data
x = np.linspace(0, 10, 100)
y1 = np.sin(x)
y2 = np.cos(x)

# Create line plot
plt.figure(figsize=(10, 6))  # Figure size (width, height) in inches
plt.plot(x, y1, label='sin(x)', color='blue', linestyle='-', linewidth=2)
plt.plot(x, y2, label='cos(x)', color='red', linestyle='--', linewidth=2)

# Customization
plt.title('Sine and Cosine Waves', fontsize=16, fontweight='bold')
plt.xlabel('X-axis (radians)', fontsize=12)
plt.ylabel('Y-axis', fontsize=12)
plt.legend(loc='upper right')
plt.grid(True, alpha=0.3)
plt.xticks(fontsize=10)
plt.yticks(fontsize=10)

# Add text annotation
plt.text(5, 0.5, 'Intersection point', fontsize=10, style='italic')
plt.annotate('local max', xy=(np.pi/2, 1), xytext=(3, 1.5),
             arrowprops=dict(facecolor='black', shrink=0.05))

plt.tight_layout()  # Adjust layout to prevent clipping
plt.show()
```

<br>

## 🐦‍🔥 SCATTER

```py
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
```

<br>

## 🐦‍🔥 HISTOGRAM

```py
# Generate random data
np.random.seed(42)
data = np.random.randn(1000)

plt.figure(figsize=(12, 5))

# Basic histogram
plt.subplot(1, 3, 1)
plt.hist(data, bins=20, color='steelblue', edgecolor='black', alpha=0.7)
plt.title('Basic Histogram')
plt.xlabel('Value')
plt.ylabel('Frequency')

# Histogram with density curve
plt.subplot(1, 3, 2)
counts, bins, patches = plt.hist(data, bins=30, density=True,
                                  color='skyblue', edgecolor='black', alpha=0.7)
plt.plot(bins, 1/(np.sqrt(2*np.pi)) * np.exp(-bins**2/2),
         'r-', linewidth=2, label='Normal Distribution')
plt.title('Histogram with Density Curve')
plt.xlabel('Value')
plt.ylabel('Density')
plt.legend()

# Cumulative histogram
plt.subplot(1, 3, 3)
plt.hist(data, bins=30, cumulative=True, color='coral',
         edgecolor='black', alpha=0.7, density=True)
plt.title('Cumulative Histogram')
plt.xlabel('Value')
plt.ylabel('Cumulative Frequency')

plt.tight_layout()
plt.show()
```

<br>

## 🐦‍🔥 BAR PLOT

```py
# Categories and values
categories = ['A', 'B', 'C', 'D', 'E']
values = [23, 45, 56, 78, 33]
errors = [2, 3, 4, 5, 2]

# Vertical bar plot
plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)  # 1 row, 2 columns, first plot
plt.bar(categories, values, color='steelblue', edgecolor='black', linewidth=2)
plt.title('Vertical Bar Plot')
plt.xlabel('Categories')
plt.ylabel('Values')
plt.grid(axis='y', alpha=0.3)

# Horizontal bar plot with error bars
plt.subplot(1, 2, 2)
plt.barh(categories, values, color='coral', edgecolor='black',
         xerr=errors, capsize=5)
plt.title('Horizontal Bar Plot with Error Bars')
plt.xlabel('Values')
plt.ylabel('Categories')
plt.grid(axis='x', alpha=0.3)

plt.tight_layout()
plt.show()
```

<br>

## 🐦‍🔥 GROUPED BAR PLOT

```py
# Data for grouped bars
categories = ['Group 1', 'Group 2', 'Group 3', 'Group 4']
values1 = [20, 34, 30, 35]
values2 = [25, 32, 34, 20]
values3 = [15, 28, 25, 30]

x = np.arange(len(categories))  # Label locations
width = 0.25  # Width of bars

fig, ax = plt.subplots(figsize=(10, 6))
rects1 = ax.bar(x - width, values1, width, label='Series 1', color='skyblue')
rects2 = ax.bar(x, values2, width, label='Series 2', color='lightcoral')
rects3 = ax.bar(x + width, values3, width, label='Series 3', color='lightgreen')

# Customization
ax.set_xlabel('Categories')
ax.set_ylabel('Values')
ax.set_title('Grouped Bar Plot')
ax.set_xticks(x)
ax.set_xticklabels(categories)
ax.legend()
ax.grid(axis='y', alpha=0.3)

# Add value labels on bars
def autolabel(rects):
  for rect in rects:
    height = rect.get_height()
    ax.annotate(f'{height}',
      xy=(rect.get_x() + rect.get_width() / 2, height),
      xytext=(0, 3),  # 3 points vertical offset
      textcoords="offset points",
      ha='center', va='bottom')

autolabel(rects1)
autolabel(rects2)
autolabel(rects3)

plt.tight_layout()
plt.show()
```


<br>

## 🐦‍🔥 STACKED BAR PLOT

```py
categories = ['A', 'B', 'C', 'D']
values1 = [4, 6, 8, 5]
values2 = [3, 5, 4, 6]
values3 = [2, 3, 5, 4]

plt.figure(figsize=(10, 6))
plt.bar(categories, values1, label='Part 1', color='skyblue')
plt.bar(categories, values2, bottom=values1, label='Part 2', color='lightcoral')
plt.bar(categories, values3, bottom=np.array(values1)+np.array(values2),
        label='Part 3', color='lightgreen')

plt.xlabel('Categories')
plt.ylabel('Total Values')
plt.title('Stacked Bar Plot')
plt.legend()
plt.grid(axis='y', alpha=0.3)
plt.show()
```

</div>
</div>
