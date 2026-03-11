use lab;
drop table enrolled;
create table Enrolled(
    snum numeric(9,0),
    cname varchar(50),
    grade char(1),
    foreign key(snum) references Student(snum),
    foreign key(cname) references Class(name)
);

insert into enrolled values (112348546,'Database Systems', 'A'),
(115987938,'Database Systems', 'B'),
(348121549,'Database Systems', 'F'),
(322654189,'Database Systems', null),
(552455318,'Database Systems', 'C'),
(455798411,'Operating System Design', 'A'),
(552455318,'Operating System Design', 'A'),
(567354612,'Operating System Design', 'B'),
(112348546,'Operating System Design', 'C'),
(115987938,'Operating System Design', 'F'),
(322654189,'Operating System Design', 'F'),
(567354612,'Data Structures', 'F'),
(552455318,'Communication Networks', 'F'),
(455798411,'Optical Electronics','F'),
(301221823,'Perception','A'),
(301221823,'Social Cognition', 'B'),
(301221823,'American Political Parties', 'C'),
(556784565,'Air Quality Engineering', 'D'),
(099354543,'Patent Law', 'A'),
(574489456,'Urban Economics','F');

delimiter $$
create function student_count(instructor int)
returns int
deterministic
begin
    declare total int;
    select count(*) into total
    from Enrolled E join Class C on E.cname = C.name
    where C.fid = instructor;
    return total;
end$$
delimiter ;

select fname
from Faculty
where student_count(fid) > 1;

-- Write an SQL function that returns the number of students who have got an F grade in a given course. 
-- Using this function, list the names of instructors who are teaching a course for which more than 1 student has an F grade.
delimiter $$
create function f_student(course varchar(50))
returns int
deterministic
begin
  declare cnt int;
  select count(*) into cnt
  from enrolled 
  where cname = course and grade = 'F';
  return cnt;
end$$
delimiter ;

drop function f_student;

select fname 
from faculty f join class c on f.fid = c.fid 
where f_student(name) > 1;

select * from enrolled;