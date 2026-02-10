use lab;
select * from student;
select * from faculty; 
select * from enrolled;
select * from class;

-- 1. Find the name of the youngest student who is either a Finance major or 
-- enrolled in a course taught by Linda Davis.
create view eligible_stud_L41 as 
select * from (select * from student where major = "Finance"
union
select s.snum, s.sname, s.major, standing, age
from student s join enrolled e on s.snum = e.snum
where e.cname in (select c.name from faculty f join class c on f.fid = c.fid where f.fname = "Linda Davis")) as stud;

select sname, age
from eligible_stud_l41
where age = (select min(age) from eligible_stud_l41);

-- 2. Find the names of all classes that either meet in room 20 AVW or have five or more students enrolled
select name from class where room = "20 AVW"
union
select cname from enrolled group by cname having count(*) > 5;

-- 3. Find the names of faculty members who teach in every room in which some class is taught
select f.fname, class
from faculty f
join (
  select fid, count(distinct room) as class
  from class
  group by fid
  having count(distinct room) = (select count(distinct room) from class)
) as sub
ON f.fid = sub.fid;

-- 4. Find the names of faculty members who teach the minimum number of classes.
select f.fname
from faculty f join (select fid
from class
group by fid
having count(fid) = (
  select min(cnt)
  from (select count(fid) as cnt
  from class
  group by fid) as sub
)) ids on f.fid = ids.fid;

-- 5. Find the names of faculty members who do not teach any class
select fname from faculty where fid not in (select distinct fid from class);

-- 6. For each age value that appears in Students, find the level value that appears most often. For example, if there are more 
-- FR level students aged 18 than SR, JR, or SO students aged 18, you should print the pair (18, FR).
select distinct s.age, s.standing
from student s 
join (
  select age, max(cnt) as cnt 
  from (
     select age, standing, count(*) cnt 
	 from student group by age, standing
  ) grp 
  group by age
) grp
on grp.age = s.age
where (
 select count(*) 
 from student s2 
 where s2.age = s.age and s2.standing = s.standing
) = grp.cnt;

select age, max(cnt) as cnt from ( 
select age, standing, count(*) cnt from student group by age, standing) grp group by age;


select age, standing, count(*) cnt from student group by age, standing;

-- 7. Find the number of courses conducted per room.
select room, count(*) from class group by room;

-- 8. Find the courses conducted in room R128 for which at least one student has enrolled.
select c.room, c.name from class c join enrolled e on c.name = e.cname where c.room = "R128";

-- 9. Find the times at which classes occur for those courses for which at least one student has enrolled
select distinct c.name, c.meets_at from class c join enrolled e on c.name = e.cname;

-- 10. Find the students of standing JR who have enrolled in some course which is conducted in room R128
select s.snum, s.sname, s.standing, c.room, c.name
from student s 
join enrolled e on s.snum = e.snum 
join class c on e.cname = c.name
where c.room = "R128" and s.standing = "JR";

-- 11. List the students who are older than 18 years and have a level of SR and whose major is not a branch of Engineering.
select * from student where age > 18 and standing = "SR" and major not like "%Engineering%";

-- 12. Find the classes for which no student has enrolled.
select * from class c where c.name not in (select distinct cname from enrolled);
