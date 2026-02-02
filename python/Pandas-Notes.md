<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **Pandas Notes** 🔥🐦‍🔥

<br>

## 🐦‍🔥 INTRODUCTION TO PANDAS

Pandas is a fast, powerful, and flexible open-source data analysis and manipulation library built on top of Python. It provides:

- Series: 1D labeled array
- DataFrame: 2D labeled data structure (like a spreadsheet)
- Data manipulation tools: filtering, grouping, merging, reshaping
- Time series functionality
- Missing data handling

### 🔥 Installation

```py
# Install pandas
pip install pandas

# Import convention
import pandas as pd
```

<br>

## 🐦‍🔥 PANDAS SERIES

### 🔥 Creating Series

```py
# From a list
s1 = pd.Series([1, 3, 5, np.nan, 6, 8])
print(s1)

# From a dictionary (keys become index)
s2 = pd.Series({'a': 1, 'b': 2, 'c': 3})
print(s2)

# With custom index
s3 = pd.Series([10, 20, 30], index=['x', 'y', 'z'])
print(s3)

# From numpy array
s4 = pd.Series(np.array([1, 2, 3, 4]))
print(s4)
```

### 🔥 Series Properties and methods

```py
s = pd.Series([1, 2, 3, 4, 5], index=['a', 'b', 'c', 'd', 'e'])

print(s.index)        # Index(['a', 'b', 'c', 'd', 'e'])
print(s.values)       # array([1, 2, 3, 4, 5])
print(s.dtype)        # dtype('int64')
print(s.shape)        # (5,)
print(s.size)         # 5
print(s.name)         # None (can set with s.name = 'my_series')

# Basic operations
print(s.head(3))      # First 3 elements
print(s.tail(3))      # Last 3 elements
print(s.describe())   # Summary statistics
print(s.unique())     # Unique values
print(s.value_counts())  # Frequency count
```

### 🔥 Series Operations

```py
s1 = pd.Series([1, 2, 3], index=['a', 'b', 'c'])
s2 = pd.Series([4, 5, 6], index=['b', 'c', 'd'])

# Arithmetic operations (aligns by index)
print(s1 + s2)  # a: NaN, b: 6, c: 8, d: NaN

# Vectorized operations
print(s1 * 2)          # Multiply by scalar
print(s1 + 10)         # Add scalar
print(np.sqrt(s1))     # Apply numpy functions
print(s1.apply(lambda x: x**2))  # Apply custom function

# Comparison operations
print(s1 > 2)          # Boolean mask
print(s1[s1 > 2])      # Filter with boolean indexing
```

<br>

## 🐦‍🔥 PANDAS DATAFRAMES

### 🔥 Creating Dataframes

```py
# From dictionary of lists
data = {
    'Name': ['Alice', 'Bob', 'Charlie'],
    'Age': [25, 30, 35],
    'City': ['NYC', 'LA', 'Chicago']
}
df1 = pd.DataFrame(data)
print(df1)

# From list of dictionaries
data = [
    {'Name': 'Alice', 'Age': 25, 'City': 'NYC'},
    {'Name': 'Bob', 'Age': 30, 'City': 'LA'},
    {'Name': 'Charlie', 'Age': 35, 'City': 'Chicago'}
]
df2 = pd.DataFrame(data)
print(df2)

# From numpy array
arr = np.array([[1, 2, 3], [4, 5, 6]])
df3 = pd.DataFrame(arr, columns=['A', 'B', 'C'])
print(df3)

# From CSV file
df = pd.read_csv('filename.csv')

# From Excel file
df = pd.read_excel('filename.xlsx')

# From SQL database
import sqlite3
conn = sqlite3.connect('database.db')
df = pd.read_sql_query('SELECT * FROM table_name', conn)
```

### 🔥 Dataframes Properties

```py
df = pd.DataFrame({
    'A': [1, 2, 3],
    'B': [4, 5, 6],
    'C': [7, 8, 9]
})

print(df.shape)           # (3, 3)
print(df.size)            # 9
print(df.ndim)            # 2
print(df.index)           # RangeIndex(start=0, stop=3, step=1)
print(df.columns)         # Index(['A', 'B', 'C'])
print(df.dtypes)          # Data types of each column
print(df.info())          # Concise summary
print(df.describe())      # Statistical summary
print(df.head(2))         # First 2 rows
print(df.tail(2))         # Last 2 rows
print(df.T)               # Transpose
print(df.memory_usage())  # Memory usage per column
```

### 🔥 Column Operations

```py
df = pd.DataFrame({
    'Name': ['Alice', 'Bob', 'Charlie'],
    'Age': [25, 30, 35],
    'Salary': [50000, 60000, 70000]
})

# Access columns
print(df['Name'])          # Get one column (returns Series)
print(df[['Name', 'Age']]) # Get multiple columns (returns DataFrame)
print(df.Name)             # Dot notation (not recommended if column names have spaces)

# Add new column
df['Bonus'] = df['Salary'] * 0.1
df['Department'] = 'IT'    # Same value for all rows
df['Age_Group'] = df['Age'].apply(lambda x: 'Young' if x < 30 else 'Senior')

# Modify columns
df['Salary'] = df['Salary'] * 1.1  # 10% raise
df['Name'] = df['Name'].str.upper()

# Delete columns
del df['Bonus']                     # In-place deletion
df = df.drop('Department', axis=1)  # Returns new DataFrame
df.drop('Department', axis=1, inplace=True)  # In-place

# Rename columns
df = df.rename(columns={'Salary': 'Annual_Salary', 'Age': 'Years'})
```

### 🔥 Row Operations

```py
# Access rows by index
print(df.iloc[0])      # First row by integer position
print(df.loc[0])       # First row by label (if default index)
print(df.iloc[0:2])    # First two rows

# Add rows
new_row = {'Name': 'David', 'Age': 28, 'Salary': 55000}
df = df.append(new_row, ignore_index=True)

# Or from another DataFrame
new_df = pd.DataFrame({'Name': ['Eve'], 'Age': [32], 'Salary': [80000]})
df = pd.concat([df, new_df], ignore_index=True)

# Delete rows
df = df.drop(0)                    # Drop first row
df = df.drop([1, 2])               # Drop multiple rows
df = df.drop(df[df.Age < 30].index)  # Drop based on condition
```

<br>

## 🐦‍🔥 DATA SELECTION AND FILTERING

### 🔥 Indexing Methods

```py
df = pd.DataFrame({
    'A': range(1, 7),
    'B': range(11, 17),
    'C': range(21, 27)
}, index=['row1', 'row2', 'row3', 'row4', 'row5', 'row6'])

# iloc: integer position based
print(df.iloc[0])           # First row
print(df.iloc[:, 0])        # First column
print(df.iloc[0:3, 1:3])    # Rows 0-2, columns 1-2

# loc: label based
print(df.loc['row1'])       # Row with label 'row1'
print(df.loc[:, 'A'])       # Column 'A'
print(df.loc['row1':'row3', 'A':'B'])  # Slicing with labels

# at: fast scalar access
print(df.at['row1', 'A'])   # Single value

# iat: fast integer scalar access
print(df.iat[0, 0])         # Single value by position
```

### 🔥 Boolean Indexing

```py
df = pd.DataFrame({
    'Name': ['Alice', 'Bob', 'Charlie', 'David', 'Eve'],
    'Age': [25, 30, 35, 40, 45],
    'Salary': [50000, 60000, 70000, 80000, 90000],
    'Department': ['IT', 'HR', 'IT', 'Finance', 'HR']
})

# Simple conditions
print(df[df['Age'] > 30])
print(df[df['Department'] == 'IT'])

# Multiple conditions
print(df[(df['Age'] > 30) & (df['Department'] == 'IT')])  # AND
print(df[(df['Age'] < 30) | (df['Department'] == 'HR')])  # OR
print(df[~(df['Department'] == 'IT')])                    # NOT

# Query method (SQL-like syntax)
print(df.query('Age > 30 and Department == "IT"'))

# isin method
print(df[df['Department'].isin(['IT', 'HR'])])
print(df[df['Name'].str.contains('li')])  # String contains
```

### 🔥 Filtering Function

```py
# where() - replace values where condition is False
print(df.where(df > 30, other='Low'))

# mask() - opposite of where()
print(df.mask(df > 30, other='High'))

# filter() - filter rows or columns by labels
print(df.filter(items=['Name', 'Age']))          # Columns
print(df.filter(like='Sa', axis=1))              # Columns containing 'Sa'
print(df.filter(regex='^A', axis=1))             # Regex pattern

# between()
print(df[df['Age'].between(30, 40)])

# isna() / notna()
print(df[df['Salary'].isna()])      # Rows with NaN in Salary
print(df[df['Salary'].notna()])     # Rows without NaN
```

</div>
</div>
