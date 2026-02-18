use lab;
use company;
select * from student;
select * from faculty; 
select * from enrolled;
select * from class;

create database company;
create table employees (
    person varchar(20),
    supervisor varchar(20)
);
insert into employees values
('Ravi', 'Aman'),
('Mary', 'Sujata'),
('Aman', 'Devi'),
('Devi', 'Mary');

-- Q1 Find the names of all classes that either meet in room 20 AVW or have five or more students enrolled.
select name, room from class 
where room = "20 AVW" or name in (select cname from enrolled group by cname having count(*) >= 5);

-- Q2 Find the number of courses conducted per room.
select room, count(*) as class from class group by room;

-- Q3 List all faculty members, showing their id, name and the number of classes they teach.
-- The number of classes of those who teach no classes must be shown as 0. 
select f.fid, f.fname, count(c.name) from faculty f left outer join class c on f.fid = c.fid group by fid, fname; 

-- Q4 List all the courses with their names, where they are taught and the number of students enrolled for each. 
-- If no students are enrolled, show the number of students as 0.
select c.name, c.room, count(e.snum) as students
from class c left join enrolled e on c.name = e.cname group by c.name, c.room;

-- Q5 Find all faculty members who belong to department 20 and whose courses are conducted in room R128
select distinct f.fname from faculty f join class c on f.fid = c.fid
where f.deptid = 20 and c.room = 'R128';

-- Q6 Find the maximum age of all students of each major
select major, max(age) as max_age from student group by major;

-- Q7 Find the names of students and faculty members whose names contain the string “son”.
select sname as name from student
where sname like '%son%'
union 
select fname as name from faculty
where fname like '%son%';

-- Q8 Find all faculty members who belong to department 20 and whose courses are conducted in room R128. Use a nested query.
-- Do not create views or use a“with” statement.
select fname from faculty where deptid = 20 and fid in (
select fid from class where room = 'R128' );

-- Q9 Find all faculty members who belong to department 20 and whose courses are conducted in room R128. 
-- Answer the question by creating a view and using it, without using a nested query.
create view r128_faculty as
select distinct fid
from class
where room = 'R128';

select f.fname
from faculty f
join r128_faculty r
on f.fid = r.fid
where f.deptid = 20;

-- Q10 Find the supervisor of Ravi. 
select supervisor from employees where person = 'Ravi';

-- Q11 Find the supervisor of the supervisor of Ravi. 
select e2.supervisor from employees e1 join employees e2 on e1.supervisor = e2.person
where e1.person = 'Ravi';

-- Q12 Find all the supervisors (direct and indirect) of Ravi.
with recursive supervisors as (
    select supervisor
    from employees
    where person = "Ravi"
    union
    select e.supervisor
    from employees e
    join supervisors s
    on e.person = s.supervisor
)
select supervisor
from supervisors;





