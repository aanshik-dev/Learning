use learning;

create table users(
  id numeric,
  name varchar(30) not null,
  age numeric,
  married boolean,
  balance numeric default 0
);

create table follow(
  id numeric primary key,
  followers numeric default 0,
  following numeric default 0,
  constraint folr_pos check(followers >0),
  constraint folg_pos check(followers >0)
);
alter table users add constraint foreign key(id) references follow(id);
insert into follow values (1, 280 ,2), (2, 256, 3), (3, 56, 52);

alter table users change column id id numeric;
alter table users add constraint pr primary key (id);
alter table users modify column age numeric check(age > 0);
show index from users;
alter table users drop index id_2;

insert into users values 
  (1, "Aanshik", 21, true, 50000),
  (2, "Aanshik", 25, false, 50000), 
  (3, "Abhi", 18, true, 60000)
;

Alter table users rename to userdata;
truncate table users;

select * from follow, users;
select * from users join follow using(id)
where (followers, name) = (280, "Aanshik");

select * from users where age > 18 and married = true;
select * from users;
select * from follow;
show columns from users;
describe users;
alter table users drop primary key;
alter table users drop constraint users_chk_2;

show create table users;
show create table follow;
select "855"

