create database jxgl;
use jxgl;
set SQL_SAFE_UPDATES=0;
create table student
	(sno varchar(20),
	 sname varchar(20),
	 sage int,
	 ssex varchar(20),
	 sdept varchar(20),
     primary key(sno));

create table course
	(cno varchar(20),
	 cname varchar(20),
	 cpno char(20),
	 ccredit int,
     primary key(cno));

create table sc
	(sno varchar(20),
	 cno varchar(20),
	 grade int,
	 primary key(sno,cno),
	 foreign key(sno) references student(sno),
	 foreign key(cno) references course(cno));

alter table student change sname sname varchar(20) character set utf8 collate utf8_general_ci;
alter table student change ssex ssex varchar(20) character set utf8 collate utf8_general_ci;
alter table course change cname cname varchar(20) character set utf8 collate utf8_general_ci;


insert into student values('2005001','钱横',18,'男','Cs');
insert into student values('2005002','王林',19,'女','Cs');
insert into student values('2005003','李民',20,'男','Is');
insert into student values('2005004','赵欣然',16,'女','Ma');
insert into student values('2005010','赵青江',18,'男','Cs');
insert into student values('2005011','张丽萍',19,'女','Ch');
insert into student values('2005012','陈景欢',20,'男','Is');
insert into student values('2005013','陈婷婷',16,'女','Ph');
insert into student values('2005014','李军',16,'女','Ph');




insert into course values('1','数据库系统','5',4);
insert into course values('2','数学分析',null,2);
insert into course values('3','信息系统导论','1',3);
insert into course values('4','操作系统原理','6',3);
insert into course values('5','数据结构','7',4);
insert into course values('6','数据处理基础',null,4);
insert into course values('7','C 语言','6',3);

insert into sc values('2005001','1',87);
insert into sc values('2005001','2',67);
insert into sc values('2005001','3',90);
insert into sc values('2005002','2',95);
insert into sc values('2005003','3',88);
insert into sc values('2005010','1',87);
insert into sc values('2005010','2',null);
insert into sc values('2005010','3',80);
insert into sc values('2005010','4',87);
insert into sc values('2005010','6',85);
insert into sc values('2005011','1',52);
insert into sc values('2005011','2',47);
insert into sc values('2005011','3',53);
insert into sc values('2005011','5',45);
insert into sc values('2005012','1',84);
insert into sc values('2005012','3',null);
insert into sc values('2005012','4',67);
insert into sc values('2005012','5',81);



select * from jxgl.student;

select * from jxgl.course;

select * from jxgl.sc;

insert into sc
select sno,'7',null
from student
where sdept='Is';

select *
from sc
where sno in (select sno
			  from student
			  where sdept='Is') and cno='7';
              
create table ts like student;

insert into ts
select *
from student
where sno in (select sno
			  from sc
			  group by sno having max(grade)<60);
              

select * from jxgl.ts;

update student 
set sname='刘华',sage=sage+1
where sno='2005001';	

select *
from student
where sno='2005001';

select *
from sc 
where cno='1';


update sc 
set grade=null
where cno in (select cno
			  from course
              where cname='数据库系统') and grade<60;


select *
from sc 
where cno='1';

insert into sc 
values('2005002','3',null);

select *
from sc
where sno='2005002' and cno='3';

create table sc2 like sc;
insert into sc2
select * from sc;

select *
from sc
where sno in(select sno
			 from student
			 where ssex='女');
             

update sc
set grade=grade*1.05
where grade<(select avg(grade)
			 from sc2) and sno in(select sno
								 from student
								 where ssex='女');


select *
from sc
where sno in(select sno
			 from student
			 where ssex='女');
        
select *
from sc
where cno='2';        
        
update sc 
set grade=grade*0.98
where grade<=80 and cno='2';

update sc
set grade=grade*0.99
where grade>80 and cno='2';

select *
from sc
where cno='2';

select *
from sc
where sno in(select sno
			 from student where sname='刘华');


delete from sc
where sno in(select sno
			 from student where sname='刘华');
             
select *
from sc
where sno in(select sno
			 from student where sname='刘华');

select *
from sc
where sno='2005001';

select *
from student
where sno='2005001';
             
delete from sc where sno='2005001';
delete from student where sno='2005001';

select *
from sc
where sno='2005001';

select *
from student
where sno='2005001';