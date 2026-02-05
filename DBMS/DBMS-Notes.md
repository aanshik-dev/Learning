<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **DBMS NOTES** 🔥🐦‍🔥

A Database Management System (DBMS) is software that allows users to define, create, maintain, and control access to databases.

<br>

## 🐦‍🔥 What is Data?

Data is a collection of raw, unorganized facts, symbols, or observations that represent quantities, characters, or signals.

On its own, data is often "meaningless" until it is processed and put into context. Once data is organized, analyzed, and interpreted, it becomes information.

## 🐦‍🔥 What is Database?

- Organized collection of structured information or data
- Typically stored electronically in a computer system
- Managed by a DBMS

## 🐦‍🔥 Types of Databases

- `Relational Databases (SQL)`- MySQL, PostgreSQL, Oracle
- `Non-Relational Databases (NoSQL)`- MongoDB, Cassandra, CouchDB, Redis
- `Graph Databases`- Neo4j, OrientDB
- `Hierarchical Databases`
- `Network Databases`
- `Object-oriented Databses`

## 🐦‍🔥 What is DBMS?

- A Database Management System (DBMS) is a collection of interrelated data and a set of programs to access that data.
- Database Management System (DBMS) is software that allows users to define, create, maintain, and control access to databases.
- DBMS is a collection of tools and procedures that manage and control the data in a database.

<br>

## 🐦‍🔥 Why we need the DBMS ?

⚡ Data redundancy and inconsistency in files

- Same data stored in multiple files
- Entry changed in one but not updated in another file

⚡ Difficulty in accessing the data

- No inbuilt functions to access data

⚡Data Isolation

- Data stored in multiple format files like .csv, .json, .txt etc
- Difficult to combine

⚡ Integrity Problem

- To apply constraint on data, like min bank balence
- One Id per person

⚡Atomicity Problem

- Either all operations complete or none
- Like transaction in a bank account

⚡ Concurrent Access Problem

- Two users accessing the data at the same time

⚡ Security Problem

- All users should not access the entire database

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

- `Schema`: Overall design/blueprint of database
- `Instance`: Actual data at a particular moment

⚡ Types of Schema:

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

2. DQL (Data Query Language)
   - SELECT

3. DML (Data Manipulation Language)
   - INSERT, UPDATE, DELETE

4. DCL (Data Control Language)
   - GRANT, REVOKE

5. TCL (Transaction Control Language)
   - COMMIT, ROLLBACK, SAVEPOINT

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
- `FLOAT`8 Bytes with precision of 23 digits
- `DOUBLE`8 Bytes with precision of 53 digits
- `REAL`4 Bytes

⚡ Character Types

- `CHAR(n)` Fixed
- `VARCHAR(n)` Variable
  n : 0 to 255 characters
- `TEXT` Large text
- `CLOB` Stores large Text Data

⚡ Date/Time Types

- `DATE` YYYY-MM-DD
- `TIME` HH:MM:SS
- `DATETIME` YYYY-MM-DD HH:MM:SS
- `TIMESTAMP` Automatic timestamp
- `YEAR` 1-4 digits

⚡ Other Types

- `BOOLEAN` True/ False
- `BLOB` Binary Large Object, like images or pdf

> 📝 NOTE : We can use `SIGNED` AND `UNSIGNED` keywords with the data types

---

### 🔥 Types of Constraints

- `NOT NULL` -- Column cannot be NULL
- `UNIQUE` -- All values must be unique
- `PRIMARY KEY` -- NOT NULL + UNIQUE
- `FOREIGN KEY` -- References another table
- `CHECK` -- Validates condition
- `DEFAULT` -- Default value if not specified

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

## 🐦‍🔥 OPERATORS IN SQL

### 🔥 Arithmetic Operators

`+`, `-`, `*`, `/`, `%`

### 🔥 Comparison Operators

`=`, `!=` or `<>`, `<`, `>`, `<=`, `>=`

### 🔥 Compound Operators

`+=`, `-=`, `*=`, `/=`, `%=`

### 🔥 Bitwise Operator

`&`, `|`, `^`

### 🔥 Logical Operators

`AND`, `OR`, `NOT`

### 🔥 Special Operators

`IS NULL`, `IS NOT NULL`, `ALL`, `SOME`, `ANY`, `EXISTS`, `BETWEEN`, `IN`, `LIKE`, `CASE`, `WHEN`, `THEN`, `ELSE`, `END`, `IF`

```sql
-- IN (matches any value in list)
SELECT * FROM Students WHERE Age IN (20, 21, 22);

-- BETWEEN (range inclusive)
SELECT * FROM Students WHERE Age BETWEEN 18 AND 25;

-- LIKE (pattern matching)
SELECT * FROM Students WHERE Name LIKE 'A%';
-- '%a%' - Contains a
-- 'A%' - Starts with A
-- '%A' - Ends with A
-- '_a%' - Second letter is a

-- IS NULL / IS NOT NULL
SELECT * FROM Students WHERE Email IS NULL;
```

<br>

## 🐦‍🔥 DDL Commands

Commands used for data definition

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

⚡ **Drop Table** - deletes a table or Database

```sql
DROP TABLE Students;
DROP DATABASE University;
```

⚡ **Truncate Table** - deletes all data in a table

```sql
TRUNCATE TABLE Students;
```

⚡ **Alter Table** - used to make changes

```sql
ALTER TABLE Students
ADD COLUMN Phone VARCHAR(20) FIRST;
-- FIRST places column at beginning of table

ALTER TABLE Students
DROP COLUMN Phone;

-- renames a table
ALTER TABLE Students
RENAME TO StudentsInfo;

-- changes name, data type and constraints of column
ALTER TABLE Students
CHANGE COLUMN old_name new_name data_type constraints;

-- changes data type & constraints of column
ALTER TABLE Students
MODIFY COLUMN Age INT NOT NULL;
```

⚡ **Show database** - displays all databases

```sql
SHOW DATABASES;
```

⚡ **Describe Table_name** -  It displays the table schema
```sql
Describle table_name;
desc Table_name;
Show columns from Table_name;
-- they all do the same work

show create table users;
-- This gives the entire details of internal schema
```

<br>

## 🐦‍🔥 DML COMMANDS

Commands used to manipulate data

⚡ **Insert** - Insert data into a table

```sql
-- Insert multiple rows
INSERT INTO Students VALUES
(3, 'Bob', 22, 'bob@email.com'),
(4, 'Charlie', 23, 'charlie@email.com');

-- Insert specific columns
INSERT INTO Students (StudentID, Name, Age)
VALUES (2, 'Alice', 21);
```

⚡ **Select** - Retrieve data from a table

```sql
-- Select all columns
SELECT * FROM Students;

-- Select specific columns
SELECT Name, Age FROM Students;

-- Select with alias
SELECT Name AS StudentName, Age AS StudentAge FROM Students;

-- Select distinct values
SELECT DISTINCT Department FROM Students;

-- Select with conditions
SELECT * FROM Students WHERE Age > 20;
```

⚡ **Update** - Update data in a table

```sql
-- Update single record
UPDATE Students
SET Age = 22, marks = marks + 5;
WHERE StudentID = 1;

-- Update multiple columns
UPDATE Students
SET Age = 23, Email = 'new@email.com'
WHERE StudentID = 2;

-- Update all records (BE CAREFUL!)
UPDATE Students
SET Status = 'Active';
```

⚡ **Delete** - Delete data from a table

```sql
-- Delete specific records
DELETE FROM Students
WHERE Age < 18;

-- Delete all records (BE CAREFUL!)
DELETE FROM Students;

-- TRUNCATE (faster, cannot rollback)
TRUNCATE TABLE Students;
```

<br>

## 🐦‍🔥 FUNCTIONS IN SQL

### 🔥 Aggregate Functions

Return single value from multiple rows

- `COUNT()` - Returns the number of rows
- `SUM()` - Returns the sum of all values
- `AVG()` - Returns the average of all values
- `MIN()` - Returns the smallest value
- `MAX()` - Returns the largest value

```sql
SELECT COUNT(*) FROM Students;
SELECT AVG(Age) FROM Students;
SELECT MAX(Salary), MIN(Salary) FROM Employees;
```

### 🔥 String Functions

- `LENGTH()` `- Returns the length of a string
- `UPPER()` - Converts a string to uppercase
- `LOWER()` - Converts a string to lowercase
- `TRIM()` - Removes leading and trailing spaces
- `CONCAT()` - Concatenates two or more strings
- `SUBSTRING()` - Returns a substring from a string
- `REPLACE()` - Replaces a substring with another substring

```sql
SELECT CONCAT(Name, ' - ', Department) FROM Students;
SELECT UPPER(Name) FROM Students;
SELECT SUBSTRING(Name, 1, 3) FROM Students;
```

### 🔥 Numeric Functions

- `ROUND()` - Rounds a number to a specified number of decimal places
- `FLOOR()` - Returns the largest integer less than or equal to a number
- `CEILING()` - Returns the smallest integer greater than or equal to a number
- `ABS()` - Returns the absolute value of a number

```sql
SELECT ROUND(AvgMarks, 2) FROM Students;
SELECT FLOOR(AvgMarks) FROM Students;
SELECT CEILING(AvgMarks) FROM Students;
SELECT ABS(AvgMarks) FROM Students;
```

### 🔥 Date Functions

- `NOW()`- Returns the current date and time
- `CURDATE()` - Returns the current date
- `CURTIME()` - Returns the current time
- `YEAR()` - Returns the year
- `MONTH()` - Returns the month
- `DAY()` - Returns the day
- `DATE_ADD()` - Adds a date or time to a date or time
- `DATE_SUB()` - Subtracts a date or time from a date or time
- `DATEDIFF()` - Returns the number of days between two dates

<br>

## 🐦‍🔥 CLAUSES IN SQL

### 🔥 WHERE clause

```sql
SELECT * FROM Students
WHERE Age > 20 AND Department = 'CS';
```

### 🔥 GROUP BY Clause

```sql
-- Group rows with same values
SELECT Department, COUNT(*) as Total
FROM Students
GROUP BY Department;
```

### 🔥 ORDER BY Clause

```sql
-- Sort results
SELECT * FROM Students
ORDER BY Name ASC;  -- Ascending (default)

SELECT * FROM Students
ORDER BY Age DESC;  -- Descending

-- Multiple columns
SELECT * FROM Students
ORDER BY Department ASC, Age DESC;
```

### 🔥 LIMIT Clause

```sql
-- Limit number of rows returned
SELECT * FROM Students
LIMIT 10;

-- With offset (pagination)
SELECT * FROM Students
LIMIT 10 OFFSET 20;  -- Skip 20, return next 10
```

### 🔥 HAVING Clause

```sql
-- With HAVING clause (filter groups)
SELECT Department, AVG(Age) as AvgAge
FROM Students
GROUP BY Department
HAVING AVG(Age) > 20;
```

> 📝 NOTE : `HAVING` clause is used with the grouped/Aggregate data i.e. after the GROPUP BY, So we can not use `HAVING Age > 20`

| Name  | Department | Age |
| ----- | ---------- | --- |
| Alice | Math       | 19  |
| Bob   | Math       | 22  |
| Carol | Science    | 18  |
| Dave  | Science    | 21  |

- Math group: Ages = [19, 22] → MAX = 22 → KEEP (22 > 20)
- Science group: Ages = [18, 21] → MAX = 21 → KEEP (21 > 20)
- Result: Both departments shown

---

### 🔥 General Order

- SELECT columns(s)
- FROM table_name
- WHERE condition
- GROUP BY column(s)
- HAVING condition
- ORDER BY column(s) ASC/DESC;
- LIMIT number_of_rows

<br>

## 🐦‍🔥 Foreign Keys

- Foreign keys are used to link two tables together. They are used to enforce referential integrity, ensuring that the data in one table is consistent with the data in another table.

- Foreign keys are those keys which are primary keys in another table.

```sql
CREATE TABLE Students (
  StudentID INT PRIMARY KEY,
  Name VARCHAR(50),
  DepartmentID INT,
  FOREIGN KEY (DepartmentID) REFERENCES Departments(DepartmentID)
  ON UPDATE CASCADE
  ON DELETE CASCADE
);
```

- `ON UPDATE CASCADE` - If a record in the parent table is updated, the corresponding record in the child table will be updated as well.
- `ON DELETE SET NULL` - If a record in the parent table is deleted, the corresponding record in the child table will be set to NULL.
- `ON DELETE CASCADE` - If a record in the parent table is deleted, the corresponding record in the child table will be deleted as well.

## 🐦‍🔥 JOINS

Joins are used to combine rows from two or more tables based on a related column between them.

### 🔥 Types of Joins

- `INNER JOIN` - Returns matching records from both tables
- `LEFT (OUTER) JOIN` - All records from left table + matching from right
- `RIGHT (OUTER) JOIN` - All records from right table + matching from left
- `FULL (OUTER) JOIN` - All records when there's match in either table
- `CROSS JOIN` - Cartesian product of both tables
- `SELF JOIN` - Join table with itself

> 📝 NOTE : `FULL JOIN` is not present in mySQl, so we use the `UNION`

```sql
-- INNER JOIN
SELECT s.Name, d.DepartmentName
FROM Students as s
INNER JOIN Departments d ON s.DeptID = d.DeptID;

-- LEFT JOIN/ RIGHT JOIN
SELECT s.Name, d.DepartmentName
FROM Students s
LEFT JOIN Departments d ON s.DeptID = d.DeptID;

-- FULL JOIN
SELECT * FROM Students as s
LEFT JOIN Departments d ON s.DeptID = d.DeptID
UNION
RIGHT JOIN Departments d ON s.DeptID = d.DeptID

-- SELF JOIN
SELECT e1.Name AS Employee, e2.Name AS Manager
FROM Employees e1
LEFT JOIN Employees e2 ON e1.ManagerID = e2.EmpID;

-- MULTIPLE JOINS
SELECT s.Name, d.DepartmentName, c.CourseName
FROM Students s
JOIN Departments d ON s.DeptID = d.DeptID
JOIN Courses c ON d.DeptID = c.DeptID;
-- JOIN is by default INNER JOIN
```

```sql
-- LEFT EXTERNAL JOIN - ONLY LEFT
SELECT *
FROM Student as a
LEFT JOIN course as b ON a.cid = b.id
WHERE b.id IS NULL;
```

<br>

## 🐦‍🔥 SUBQUERIES

### 🔥 Types of Subqueries

- `Single-row subquery` (returns one row)
- `Multi-row subquery` (returns multiple rows)
- `Correlated subquery` (references outer query)
- `Nested subquery` (subquery within subquery)

```sql
-- Single-row subquery
SELECT Name, Salary
FROM Employees
WHERE Salary > (SELECT AVG(Salary) FROM Employees);

-- Multi-row subquery with IN
SELECT Name
FROM Students
WHERE DeptID IN (SELECT DeptID FROM Departments WHERE Location = 'Building A');

-- Correlated subquery
SELECT Name, Salary
FROM Employees e1
WHERE Salary > (SELECT AVG(Salary)
                FROM Employees e2
                WHERE e1.DeptID = e2.DeptID);

-- EXISTS operator
SELECT DeptName
FROM Departments d
WHERE EXISTS (SELECT 1 FROM Students s
              WHERE s.DeptID = d.DeptID);
```

<br>

## 🐦‍🔥 SET OPERATIONS

### 🔥 Union

```sql
-- Combine results, remove duplicates
SELECT Name FROM Students
UNION
SELECT Name FROM Alumni;

-- UNION ALL (keep duplicates)
SELECT Name FROM Students
UNION ALL
SELECT Name FROM Alumni;
```

### 🔥 Intersect

```sql
-- Common records in both queries
SELECT StudentID FROM CS_Students
INTERSECT
SELECT StudentID FROM Scholarship_Students;
```

### 🔥 Except/Minus

```sql
-- Records in first but not in second
SELECT StudentID FROM Students
EXCEPT
SELECT StudentID FROM Graduated_Students;
```

<br>

## 🐦‍🔥 WINDOW FUNCTIONS

Window functions perform calculations across a set of table rows that are somehow related to the current row.
Unlike regular aggregate functions, window functions do not collapse rows - they maintain the original rows while adding computed values

- Operate on a window of rows related to current row
- Use `OVER()` clause to define the window
- Can be used with `ORDER BY`, `PARTITION BY`, `ROWS/RANGE` clauses

### 🔥 Aggregate Window Functions

- `SUM()`, `AVG()`, `COUNT()`, `MIN()`, `MAX()`

```sql
SELECT
    date,
    sales,
    SUM(sales) OVER (ORDER BY date) as total_sales,
    AVG(sales) OVER (ORDER BY date) as avg_sales,
    COUNT(sales) OVER (ORDER BY date) as num_days,
    MIN(sales) OVER (ORDER BY date) as min_sales,
    MAX(sales) OVER (ORDER BY date) as max_sales
FROM daily_sales;
```

```sql
SELECT
    department,
    employee_id,
    salary,
    AVG(salary) OVER (PARTITION BY department) as dept_avg_salary,
    salary - AVG(salary) OVER() as diff_from_avg
FROM employees;
```

### 🔥 RANKING FUNCTIONS

- `ROW_NUMBER()` - Assigns unique sequential integer to rows (1,2,3,4...)
- `RANK()` - Same as row number but leaves gap for ties (1,2,2,4...)
- `DENSE_RANK()` - rank without gaps for ties(1,2,2,3...)
- `NTILE()` - Divide rows into n approx equal groups (1,1,2,2,3,3...)

```sql
SELECT
    Student, Marks,
    ROW_NUMBER() OVER (ORDER BY Marks DESC) as RowNum,
    RANK() OVER (ORDER BY marks DESC) as rank,
    DENSE_RANK() OVER (ORDER BY Marks DESC) as DenseRank,
    NTILE(4) OVER (ORDER BY Marks) as quartile
FROM employees;
```

| Student | Marks | RowNum | Rank | DenseRank | Quartile |
| ------- | :---: | :----: | :--: | :-------: | :------: |
| Alice   |  95   |   1    |  1   |     1     |    1     |
| Bob     |  92   |   2    |  2   |     2     |    1     |
| Charlie |  92   |   3    |  2   |     2     |    2     |
| Dave    |  88   |   4    |  4   |     3     |    2     |
| Eve     |  85   |   5    |  5   |     4     |    3     |

### 🔥 ANALYTICAL/VALUE FUNCTIONS

- `LAG(column, offset, default)` - Returns value from previous row
- `LEAD(column, offset, default)` - Returns value from next row
- `FIRST_VALUE(column)` - Returns value from first row
- `LAST_VALUE(column)` - Returns value from last row
- `NTH_VALUE(column, n)` - Returns value from nth row

```sql
SELECT
    date, sales,
    LEAD(sales,1,0) OVER (ORDER BY date) as Next_day_sales,
    LAG(sales,1,0) OVER (ORDER BY date) as Prev_day_sales,
    NTH_VALUE(sales,2) OVER (ORDER BY date) as Second_day_sales
From daily_sales;
```

```sql
SELECT
    department,
    employee_id,
    salary,
    FIRST_VALUE(salary) OVER (PARTITION BY department ORDER BY salary DESC) as highest_in_dept,
    LAST_VALUE(salary) OVER (PARTITION BY department ORDER BY salary DESC) as lowest_in_dept
FROM employees;
```

### 🔥 Window Frames

```sql
-- Default frame (when ORDER BY is present):
RANGE BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW

-- Common frames:
ROWS BETWEEN 2 PRECEDING AND CURRENT ROW  -- Last 3 rows including current
ROWS BETWEEN 1 PRECEDING AND 1 FOLLOWING  -- Previous, current, next
ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW -- All rows up to current
ROWS BETWEEN CURRENT ROW AND UNBOUNDED FOLLOWING -- Current to end
ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING -- Entire partition
```

## 🐦‍🔥 VIEWS

### 🔥 Creating Views

```sql
-- Virtual table based on query
CREATE VIEW StudentDetails AS
SELECT s.StudentID, s.Name, d.DepartmentName, c.CourseName
FROM Students s
JOIN Departments d ON s.DeptID = d.DeptID
JOIN Courses c ON s.CourseID = c.CourseID;

-- Using the view
SELECT * FROM StudentDetails
WHERE DepartmentName = 'Computer Science';

-- Updatable view (with certain conditions)
CREATE VIEW ActiveStudents AS
SELECT * FROM Students
WHERE Status = 'Active';

-- WITH CHECK OPTION (prevents updates violating view condition)
CREATE VIEW CS_Students AS
SELECT * FROM Students
WHERE Department = 'CS'
WITH CHECK OPTION;
```

### 🔥 Modifing Views

```sql
-- Alter view
CREATE OR REPLACE VIEW StudentDetails AS
SELECT s.StudentID, s.Name, s.Email, d.DepartmentName
FROM Students s
JOIN Departments d ON s.DeptID = d.DeptID;

-- Drop view
DROP VIEW StudentDetails;
```

<br>

## 🐦‍🔥 INDEXES

### 🔥 Types of Indexes

- Clustered Index
  - Defines physical order of data
  - Only one per table (usually Primary Key)
- Non-clustered Index
  - Separate structure with pointers to data
  - Multiple per table

### 🔥 Creating Indexes

```sql
-- Single column index
CREATE INDEX idx_name ON Students(Name);

-- Composite index
CREATE INDEX idx_dept_age ON Students(Department, Age);

-- Unique index
CREATE UNIQUE INDEX idx_email ON Students(Email);

-- Clustered index (usually on Primary Key)
CREATE CLUSTERED INDEX idx_studentid ON Students(StudentID);

-- Drop index
DROP INDEX idx_name ON Students;

-- Show index
SHOW INDEXES IN Students;
SHOW INDEXES FROM Students;
```

### 🔥 When to use Indexes

✅ DO Index:

- Primary and Foreign Keys
- Columns frequently in WHERE clause
- Columns used in JOIN conditions
- Columns used in ORDER BY/GROUP BY

❌ DON'T Index:

- Small tables
- Columns with many NULLs
- Frequently updated columns
- Columns with few unique values

<br>

## 🐦‍🔥 NORMALIZATION

### 🔥 Normalization

⚡ 1NF (First Normal Form)

- Atomic values (no multi-valued attributes)
- Each column has unique name
- Order doesn't matter

⚡ 2NF (Second Normal Form)

- Must be in 1NF
- No partial dependency (all non-key attributes depend on entire primary key)

⚡ 3NF (Third Normal Form)

- Must be in 2NF
- No transitive dependency (non-key attributes shouldn't depend on other non-key attributes)

⚡ BCNF (Boyce-Codd Normal Form)

- Stronger than 3NF
- Every determinant must be candidate key

⚡ 4NF (Fourth Normal Form)

- No multi-valued dependencies

⚡ 5NF (Fifth Normal Form)

- No join dependency

```sql
-- Unnormalized Table
Student (ID, Name, {Course1, Course2}, Phone)

-- 1NF (Remove multi-valued)
Student (ID, Name, Phone)
Courses (StudentID, CourseName)

-- 2NF (Remove partial dependencies)
Students (ID, Name, DeptID)        -- DeptID is foreign key
Departments (DeptID, DeptName)
StudentCourses (StudentID, CourseID)
Courses (CourseID, CourseName)

-- 3NF (Remove transitive dependencies)
Students (ID, Name, DeptID)
Departments (DeptID, DeptName, HOD_ID)  -- HOD_ID references Teachers
Teachers (TeacherID, Name, Department)
```

<br>

## 🐦‍🔥 TRANSACTIONS

### 🔥 ACID properties

- `Atomicity` - Either all operations complete or none
- `Consistency` - Database remains consistent before and after
- `Isolation` - Concurrent transactions don't interfere
- `Durability` - Committed changes persist even after system failure

```sql
-- Start transaction
BEGIN TRANSACTION;

-- Operations
UPDATE Accounts SET Balance = Balance - 100 WHERE AccNo = 1;
UPDATE Accounts SET Balance = Balance + 100 WHERE AccNo = 2;

-- Savepoint
SAVEPOINT before_final;

-- More operations
UPDATE Accounts SET Balance = Balance - 50 WHERE AccNo = 1;

-- Rollback to savepoint
ROLLBACK TO before_final;

-- Commit transaction
COMMIT;

-- Rollback entire transaction
ROLLBACK;
```

### 🔥 Concurrency Control

⚡ Problems with concurrent Transactions

- `Dirty Read` - Read uncommitted data
- `Lost Update` - Overwrite by another transaction
- `Unrepeatable Read` - Different values in same read
- `Phantom Read` - New rows appear in second read

⚡ Isolation Levels

- READ UNCOMMITTED
  - Allows dirty reads
  - Lowest isolation, highest performance
- READ COMMITTED
  - Prevents dirty reads
  - Default in many databases
- REPEATABLE READ
  - Prevents dirty and non-repeatable reads
  - Default in MySQL InnoDB
- SERIALIZABLE
  - Highest isolation
  - Transactions execute serially

⚡ Setting Isolation Level

```sql
-- Set for current session
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;

-- Set for all transactions
ALTER DATABASE University
SET READ_COMMITTED_SNAPSHOT ON;
```

<br>

## 🐦‍🔥 LOCKS

### 🔥Types of Locks

- Shared Lock (S Lock)
  - For reading operations
  - Multiple transactions can hold
- Exclusive Lock (X Lock)
  - For writing operations
  - Only one transaction can hold
- Intention Locks
  - Indicate intention to lock at finer granularity
  - IS (Intention Shared), IX (Intention Exclusive)

### 🔥Lock granularity

`Database Level → Table Level → Page Level → Row Level`

### 🔥 Lock Compatibility matrix

|     | NL  | IS  | IX  | S   | SIX | X   |
| --- | --- | --- | --- | --- | --- | --- |
| NL  | ✓   | ✓   | ✓   | ✓   | ✓   | ✓   |
| IS  | ✓   | ✓   | ✓   | ✓   | ✓   | ✗   |
| IX  | ✓   | ✓   | ✗   | ✗   | ✗   | ✗   |
| S   | ✓   | ✓   | ✗   | ✓   | ✗   | ✗   |
| SIX | ✓   | ✓   | ✗   | ✗   | ✗   | ✗   |
| X   | ✓   | ✗   | ✗   | ✗   | ✗   | ✗   |

<br>

## 🐦‍🔥 DEADLOCKS

### 🔥 What is a `deadlock`?

Transaction T1 holds lock on Resource R1, waits for R2
Transaction T2 holds lock on Resource R2, waits for R1
→ Both wait indefinitely

### 🔥 Deadlock Handling

- Prevention
  - Require all locks at beginning
  - Use lock ordering
- Avoidance
  - Banker's algorithm
  - Resource allocation graph
- Detection & Recovery
  - Wait-for graph
  - Choose victim and rollback

### 🔥 Deadlock Detection

```sql
-- Check for deadlocks (SQL Server)
DBCC TRACEON (1222, -1);

-- MySQL
SHOW ENGINE INNODB STATUS;

-- PostgreSQL
SELECT * FROM pg_stat_activity
WHERE wait_event_type IS NOT NULL;
```

</div>
</div>
