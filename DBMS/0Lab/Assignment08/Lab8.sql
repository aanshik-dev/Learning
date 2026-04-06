use lab;
select * from student;
select * from faculty; 
select * from enrolled;
select * from class;

-- Create the total_credits column
alter table student
add column total_credits int default 0;

-- Creates the credits column
alter table class
add column credits int;

-- Entered the credits of the course
set SQL_SAFE_UPDATES = 0;
update class SET credits = case name
when 'Data Structures' then 3
when 'Database Systems' then 4
when 'Operating System Design' then 5
when 'Archaeology of the Incas' then 4
when 'Aviation Accident Investigation' then 2
when 'Air Quality Engineering' then 4
when 'Introductory Latin' then 3
when 'American Political Parties' then 4
when 'Social Cognition' then 4
when 'Perception' then 3
when 'Multivariate Analysis' then 4
when 'Patent Law' then 3
when 'Urban Economics' then 2
when 'Organic Chemistry' then 4
when 'Marketing Research' then 5
when 'Seminar in American Art' then 4
when 'Orbital Mechanics' then 3
when 'Dairy Herd Management' then 2
when 'Communication Networks' then 3
when 'Optical Electronics' then 4
when 'Intoduction to Math' then 5
end
where name IS NOT NULL;
SET SQL_SAFE_UPDATES = 1;

-- Added the grade column in the enrolled
alter table enrolled
add column grade varchar(2) default null;
-- Set grades to null
update enrolled set grade = null where snum is not null;

-- Enter the grades 
SET SQL_SAFE_UPDATES = 0;
update enrolled
set grade = case
    when snum=112348546 and cname='Database Systems' then 'A'
    when snum=115987938 and cname='Database Systems' then 'B'
    when snum=348121549 and cname='Database Systems' then 'F'
    when snum=322654189 and cname='Database Systems' then NULL
    when snum=552455318 and cname='Database Systems' then 'C'
    when snum=455798411 and cname='Operating System Design' then 'A'
    when snum=552455318 and cname='Operating System Design' then 'A'
    when snum=567354612 and cname='Operating System Design' then 'B'
    when snum=112348546 and cname='Operating System Design' then 'C'
    when snum=115987938 and cname='Operating System Design' then 'F'
    when snum=322654189 and cname='Operating System Design' then 'F'
    when snum=567354612 and cname='Data Structures' then 'F'
    when snum=552455318 and cname='Communication Networks' then 'F'
    when snum=455798411 and cname='Optical Electronics' then 'F'
    when snum=301221823 and cname='Perception' then 'A'
    when snum=301221823 and cname='Social Cognition' then 'B'
    when snum=301221823 and cname='American Political Parties' then 'C'
    when snum=556784565 and cname='Air Quality Engineering' then 'D'
    when snum=099354543 and cname='Patent Law' then 'A'
    when snum=574489456 and cname='Urban Economics' then 'F'
end;
SET SQL_SAFE_UPDATES = 1;


-- Triggers when data is inserted
delimiter $$
create trigger trig_insert
after insert on enrolled
for each row
begin
    declare course_credit int;
    select credits into course_credit from class
        where name = new.cname;
    if new.grade is not null and new.grade = 'D' then
		update student
        set total_credits = total_credits + (course_credit/2)
        where snum = new.snum;
    elseif new.grade is not null and new.grade <> 'F' then
        update student
        set total_credits = total_credits + course_credit
        where snum = new.snum;
    end if;
end$$
delimiter ;

-- triggers when data is updated
DELIMITER $$
create trigger trig_update
after update on enrolled
for each row
begin
    declare course_credits int;
    select credits INTO course_credits from class
    where name = NEW.cname;
    -- If old : F/ Null and new other than F/null then add 
    if (OLD.grade is null or OLD.grade = 'F') and (NEW.grade is not null and NEW.grade <> 'F')
    then
        update student
        set total_credits = total_credits + course_credits
        where snum = NEW.snum;
    -- If Old : other than F/null and new F/null then subtract
    elseif (OLD.grade is not null and OLD.grade <> 'F') and (NEW.grade is null or NEW.grade = 'F') 
    then
        update student
        set total_credits = total_credits - course_credits
        where snum = NEW.snum;
    end if;
end$$
DELIMITER ;

-- creates ready students 
create table ready_students (
    snum numeric(9,0)
);

-- 301221823 Social Cognition B
update enrolled set grade = 'B'
where snum = 556784565 and cname = 'Air Quality Engineering';

select * from ready_students;

-- Trigger to find ready students
DELIMITER $$
create trigger update_ready
after update on student
for each row
begin
    if NEW.total_credits > 10 then
        insert into ready_students values (NEW.snum);
    else
        delete from ready_students where snum = NEW.snum;
    end if;
end$$
DELIMITER ;

show triggers;
drop trigger update_ready;
drop trigger trig_update;
drop trigger update_credits_trigger;