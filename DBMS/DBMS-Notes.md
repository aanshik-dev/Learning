<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **DBMS NOTES** 🔥🐦‍🔥

A Database Management System (DBMS) is software that allows users to define, create, maintain, and control access to databases.

<br>

## 🐦‍🔥 What is Database?

- Organized collection of structured information or data
- Typically stored electronically in a computer system
- Managed by a DBMS

<br>

## 🐦‍🔥 Types of Databases

- `Relational Databases (SQL)`- MySQL, PostgreSQL, Oracle
- `Non-Relational Databases (NoSQL)`- MongoDB, Cassandra, CouchDB, Redis
- `Graph Databases`- Neo4j, OrientDB
- `Hierarchical Databases`
- `Network Databases`
- `Object-oriented Databses`

<br>

## 🐦‍🔥 DBMS ARCHITECTURE

1. External Level (View Level)

   - User's view of database
   - Multiple views for different users

2. Conceptual Level (Logical Level)

   - Global view of entire database
   - Describes what data is stored
   - Relationships between data

3. Internal Level (Physical Level)
   - How data is actually stored
   - Physical storage details

### 🔥 Database Schema

`Schema`: Overall design/blueprint of database
`Instance`: Actual data at a particular moment

Types of Schema:

- Physical Schema - Physical storage
- Logical Schema - Logical structure
- View Schema - User views

<br>

## 🐦‍🔥 DATA MODELS

### 🔥 Relational Model

### 🔥 Entity-Relationship (ER) Model

- `Entity` - Real-world object (Student, Course)
- `Attributes` - Properties of entity (Name, Age)
- `Relationships` - Association between entities

⚡ Types of Attributes:

- Simple vs Composite
- Single-valued vs Multi-valued
- Derived (Calculated from other attributes)
- Key Attribute (Uniquely identifies entity)

⚡ Types of Relationships:

- One-to-One (1:1)
- One-to-Many (1:M)
- Many-to-One (M:1)
- Many-to-Many (M:N)

<br>

## 🐦‍🔥 RELATIONAL MODEL

- Data organized into tables (relations)
- Each table has rows (tuples) and columns (attributes)
- Based on mathematical set theory

### 🔥 Important Terms

- `Relation`: Table
- `Tuple`: Row/Record
- `Attribute`: Column/Field
- `Domain`: Set of valid values
- `Degree`: Number of columns
- `Cardinality`: Number of rows

### 🔥 Types of Keys in DBMS

- `Super Key` Set of attributes that uniquely identifies a tuple, They can be single or composite
- `Candidate Key`
  - Minimal super key (no proper subset is super key)
  - Can be multiple in a relation
- `Primary Key`
  - Chosen candidate key to identify tuples uniquely
  - Cannot be NULL
  - Must be unique
- `Alternate Key` Candidate keys not chosen as primary key
- `Foreign Key`
  - Attribute that references primary key of another table
  - Establishes relationship between tables
- `Composite Key` Primary key with multiple attributes
- `Surrogate Key` Artificial key (Auto-increment ID)

<br>

## 🐦‍🔥 SQL BASICS

### 🔥 SQL Catagories

1. DDL (Data Definition Language)

   - CREATE, ALTER, DROP, TRUNCATE, RENAME

2. DML (Data Manipulation Language)

   - SELECT, INSERT, UPDATE, DELETE

3. DCL (Data Control Language)

   - GRANT, REVOKE

4. TCL (Transaction Control Language)
   - COMMIT, ROLLBACK, SAVEPOINT

---

### 🔥 DDL Commands

⚡ **Create Database** - Creates a Database

```sql
CREATE DATABASE University;
USE University;
```

⚡ **Create Table** - Defines the schema of database

```sql
CREATE TABLE Students (
    StudentID INT PRIMARY KEY,
    Name VARCHAR(50) NOT NULL,
    Age INT CHECK (Age >= 18),
    Email VARCHAR(100) UNIQUE,
    DepartmentID INT,
    FOREIGN KEY (DepartmentID) REFERENCES Departments(DeptID)
);
```

⚡ **Alter Table** - used to make changes

```sql
ALTER TABLE Students
ADD Phone VARCHAR(20);
```

⚡ **Drop Table** - deletes a table

```sql
DROP TABLE Students;
```

---

### 🔥 DATA TYPES IN SQL

⚡ Numeric Types

- `TINYINT` 1 Byte
- `SMALLINT` 2 Bytes
- `INT` 4 Bytes
- `BIGINT` 8 Bytes
- `DECIMAL(p,s)` variable
- `NUMERIC(p,s)` variable
  P (Precision): total number of digits
  S (Scale) number of digits after decimal
- `FLOAT`8 Bytes
- `REAL`4 Bytes

⚡ Character Types

- `CHAR(n)` Fixed
- `VARCHAR(n)` Variable
- `TEXT` Large text

⚡ Date/Time Types

- `DATE` YYYY-MM-DD
- `TIME` HH:MM:SS
- `DATETIME` YYYY-MM-DD HH:MM:SS
- `TIMESTAMP` Automatic timestamp

⚡ Other Types

- `BOOLEAN` True/ False
- `BLOB` Binary Large Object

<br>

## 🐦‍🔥 TYPES OF CONSTRAINTS

- `NOT NULL` -- Column cannot be NULL
- `UNIQUE` -- All values must be unique
- `PRIMARY KEY` -- NOT NULL + UNIQUE
- `FOREIGN KEY` -- References another table
- `CHECK` -- Validates condition
- `DEFAULT` -- Default value if not specified

### 🔥 Adding Constraints

```sql
 -- Column Level
CREATE TABLE Employees (
    EmpID INT PRIMARY KEY,
    Name VARCHAR(50) NOT NULL,
    Salary DECIMAL(10,2) CHECK (Salary > 0),
    DeptID INT DEFAULT 1
);

-- Table Level
CREATE TABLE Employees (
    EmpID INT,
    Name VARCHAR(50),
    DeptID INT,
    PRIMARY KEY (EmpID),
    FOREIGN KEY (DeptID) REFERENCES Departments(DeptID),
    CHECK (Salary > 0)
);

-- Adding Later
ALTER TABLE Employees
ADD CONSTRAINT CHK_Salary CHECK (Salary > 10000);

-- Removing Constraint
ALTER TABLE Employees
DROP CONSTRAINT CHK_Salary;
```

<br>

## 🐦‍🔥 DML COMMANDS

</div>
</div>
