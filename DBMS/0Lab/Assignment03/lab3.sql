use lab;
select * from student;
select * from faculty; 
select * from enrolled;
select * from class;

-- For each level, print the level and the average age of students for that level.
select standing as level, avg(age) as avg_age
from student
group by standing;    -- Q1

-- For all levels except JR, print the level and the average age of students for that level.
select standing, avg(age) as avg_age
from student
where standing <> "JR"
group by standing; -- Q2

-- For each faculty member that has taught classes,+ print the faculty member’s 
-- name and the total number of classes she or he has taught.
select faculty.fname, count(class.name) as classes
from faculty
join class on class.fid = faculty.fid
group by faculty.fid ; -- Q3

-- Find the highest age of all students.
select max(age) as Max_Age
from student;   -- Q4

-- Find the name and number of students who have enrolled in Database Systems
-- but not in Operating System Design.
select s.snum, s.sname
from student as s join enrolled as e on s.snum = e.snum
where e.cname = "Database Systems" and s.snum not in (
select snum from enrolled
where cname = "Operating System Design"); -- Q5

-- Find the average age of all students taking a course, if that course has at least 2 students.
select e.cname, avg(age)
from student s join enrolled e on s.snum = e.snum
group by e.cname
having count(e.snum) >= 2;       -- Q6

-- Find the ids of faculty members who are teaching more than one course.
select fid from class
group by fid
having count(fid) > 1;  -- Q7

select fid 
from faculty
where fid not in (select fid from class);

-- Find the ids of all students who have enrolled for more than one course.
select snum from enrolled
group by snum having count(snum) > 1;  -- Q8

-- List students (their ids, names, majors , level and age) in ascending order of age.
select snum, sname, major, standing as level, age
from student
order by age asc;       -- Q9

-- Find the names and ids of all students whose major is some branch of Engineering
-- (Electrical Engineering, Mechanical Engineering, Computer Engineering, Civil Engineering).
select sname, snum
from student 
where major in ("Electrical Engineering", "Computer Engineering", "Mechanical Engineering", "Civil Engineering"); -- Q10

-- Count the number of students in each branch of Engineering.
select count(major) total_student, major
from student
where major in ("Electrical Engineering", "Computer Engineering", "Mechanical Engineering", "Civil Engineering")
group by major;    -- Q11

-- Find the names and ids of faculty members who either teach Data Structures or Operating System Design.
select distinct f.fname, f.fid
from faculty f join class c on f.fid = c.fid
where c.name = "Data Structures" or c.name = "Operating System Design";  -- Q12

-- Find the names and ids of instructors who are teaching a course and belonging to department id 20.
select distinct f.fname, f.fid
from faculty f join class c on f.fid = c.fid
where f.deptid = 20;    -- Q13

-- Find the number of courses conducted per room.
select count(*) as classes, room from class
group by room;    -- Q14


-- eval
select count( distinct cname)
from enrolled;

