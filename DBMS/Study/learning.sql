Create database learning;
use learning;
create table student(
	snum numeric(9,0) primary key,
	sname varchar(30),
	major varchar(25),
	standing varchar(2),
	age numeric(3,0)
	);

create table faculty(
	fid numeric(9,0) primary key,
	fname varchar(30),
	deptid numeric(2,0)
	);
    
create table class(
	name varchar(40) primary key,
	meets_at varchar(20),
	room varchar(10),
	fid numeric(9,0),
	foreign key(fid) references faculty(fid)
	);
    
create table enrolled(
	snum numeric(9,0),
	cname varchar(40),
	primary key(snum,cname),
	foreign key(snum) references student(snum),
	foreign key(cname) references class(name)
	);
    
    
INSERT INTO STUDENT VALUES (051135593,"Maria White","English","SR",21),
(060839453,"Charles Harris","Architecture","SR",22),
(099354543,"Susan Martin","Law","JR",20),
(112348546,"Joseph Thompson","Computer Science","SO",19),
(115987938,"Christopher Garcia","Computer Science","JR",20),
(132977562,"Angela Martinez","History","SR",20),
(269734834,"Thomas Robinson","Psychology","SO",18),
(280158572,"Margaret Clark","Animal Science","FR",18),
(301221823,"Juan Rodriguez","Psychology","JR",20),
(318548912,"Dorthy Lewis","Finance","FR",18),
(320874981,"Daniel Lee","Electrical Engineering","FR",17),
(322654189,"Lisa Walker","Computer Science","SO",17),
(348121549,"Paul Hall","Computer Science","JR",18),
(351565322,"Nancy Allen","Accounting","JR",19),
(451519864,"Mark Young","Finance","FR",18),
(455798411,"Luis Hernandez","Electrical Engineering","FR",17),
(462156489,"Donald King","Mechanical Engineering","SO",19),
(550156548,"George Wright","Education","SR",21),
(552455318,"Ana Lopez","Computer Engineering","SR",19),
(556784565,"Kenneth Hill","Civil Engineering","SR",21),
(567354612,"Karen Scott","Computer Engineering","FR",18),
(573284895,"Steven Green","Kinesiology","SO",19),
(574489456,"Betty Adams","Economics","JR",20),
(578875478,"Edward Baker","Veterinary Medicine","SR",21);

INSERT INTO faculty values 
(142519864,"Ivana Teach",20),
(242518965,"James Smith",68),
(141582651,"Mary Johnson",20),
(011564812,"John Williams",68),
(254099823,"Patricia Jones",68),
(356187925,"Robert Brown",12),
(489456522,"Linda Davis",20),
(287321212,"Michael Miller",12),
(248965255,"Barbara Wilson",12),
(159542516,"William Moore",33),
(090873519,"Elizabeth Taylor",11),
(486512566,"David Anderson",20),
(619023588,"Jennifer Thomas",11),
(489221823,"Richard Jackson",33),
(548977562,"Ulysses Teach",20);

Insert into class values
("Data Structures","MWF 10","R128",489456522),
("Database Systems","MWF 12:30-1:45","1320 DCL",142519864),
("Operating System Design","TuTh 12-1:20","20 AVW",489456522),
("Archaeology of the Incas","MWF 3-4:15","R128",248965255),
("Aviation Accident Investigation","TuTh 1-2:50","Q3",011564812),
("Air Quality Engineering","TuTh 10:30-11:45","R15",011564812),
("Introductory Latin","MWF 3-4:15","R12",248965255),
("American Political Parties","TuTh 2-3:15","20 AVW",619023588),
("Social Cognition","Tu 6:30-8:40","R15",159542516),
("Perception","MTuWTh 3","Q3",489221823),
("Multivariate Analysis","TuTh 2-3:15","R15",090873519),
("Patent Law","F 1-2:50","R128",090873519),
("Urban Economics","MWF 11","20 AVW",489221823),
("Organic Chemistry","TuTh 12:30-1:45","R12",489221823),
("Marketing Research","MW 10-11:15","1320 DCL",489221823),
("Seminar in American Art","M 4","R15",489221823),  
("Orbital Mechanics","MWF 8","1320 DCL",011564812),
("Dairy Herd Management","TuTh 12:30-1:45","R128",356187925),
("Communication Networks","MW 9:30-10:45","20 AVW",141582651),
("Optical Electronics","TuTh 12:30-1:45","R15",254099823),
("Intoduction to Math","TuTh 8-9:30","R128",489221823);

Insert into enrolled values
(112348546,"Database Systems"),
(115987938,"Database Systems"),
(348121549,"Database Systems"),
(322654189,"Database Systems"),
(552455318,"Database Systems"),
(455798411,"Operating System Design"),
(552455318,"Operating System Design"),
(567354612,"Operating System Design"),
(112348546,"Operating System Design"),
(115987938,"Operating System Design"),
(322654189,"Operating System Design"),
(567354612,"Data Structures"),
(552455318,"Communication Networks"),
(455798411,"Optical Electronics"),
(301221823,"Perception"),
(301221823,"Social Cognition"),
(301221823,"American Political Parties"),
(556784565,"Air Quality Engineering"),
(099354543,"Patent Law"),
(574489456,"Urban Economics");

Select sname, age 
from Student;  -- Question 1

Select *  -- Question 2
from student where age > 18;

Select snum 
from enrolled 
where cname = "Database Systems";  -- Question 3

Select sname
from student inner join enrolled on student.snum = enrolled.snum
where cname = "Database Systems"; -- Question 4

select fname
from faculty
where deptid = 20; -- Question 5
