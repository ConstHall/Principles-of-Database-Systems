create database jxgl;
use jxgl;

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

select * from jxgl.student;

select * from jxgl.course;

select * from jxgl.sc;


