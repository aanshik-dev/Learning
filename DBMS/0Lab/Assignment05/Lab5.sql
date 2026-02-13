use lab;
select * from student;
select * from faculty; 
select * from enrolled;
select * from class;

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
select c.name from class c left outer join enrolled e on c.name = e.cname group by e.cname;
