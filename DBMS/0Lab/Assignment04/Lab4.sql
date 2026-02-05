use lab;
select * from student;
select * from faculty; 
select * from enrolled;
select * from class;

-- Find the name of the youngest student who is either a Finance major or 
-- enrolled in a course taught by Linda Davis.
create view eligible_stud_L41 as 
select * from (select * from student where major = "Finance"
union
select s.snum, s.sname, s.major, standing, age
from student s join enrolled e on s.snum = e.snum
where e.cname in (select c.name from faculty f join class c on f.fid = c.fid where f.fname = "Linda Davis")) as stud;

select sname, age
from eligible_stud_l41
where age = (select min(age) from eligible_stud_l41);  -- Q1

-- Find the names of all classes that either meet in room 20 AVW or have five or more students enrolled
select name from class where room = "20 AVW"
union
select cname from enrolled group by cname having count(*) > 5;

-- Find the names of faculty members who teach in every room in which some class is taught
select f.name from faculty f where 
select distinct room from class where not exists(select * from class);



















SELECT f.fname
FROM faculty f
WHERE NOT EXISTS (
    SELECT DISTINCT c.room
    FROM class c
    WHERE NOT EXISTS (
        SELECT *
        FROM class c2
        WHERE c2.fid = f.fid
          AND c2.room = c.room
    )
);

