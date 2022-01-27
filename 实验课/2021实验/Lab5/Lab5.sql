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

delimiter //
create procedure select_s()
begin
	select * from student where ssex='女';
end//
call select_s();

delimiter //
create procedure insrectos(in sno1 varchar(20),out sname1 varchar(20) character set utf8,out sage1 int)
begin
	select sname,sage into sname1,sage1
	from student
	where sno=sno1;
end//

delimiter ;
set @sno1="2005002",@sname1=" ",@sage1=0; # 设置初始值
call insrectos(@sno1,@sname1,@sage1); # 调用
select @sname1,@sage1; #显示返回结果


delimiter //
create procedure SELECT_STUDENT() #创建新表
begin
	select * from student where ssex="女";
end//

#drop procedure if exists select_s; #删除旧表
#drop procedure select_s; #删除旧表

update jxgl.select_s
set name = 'SELECT_STUDENT',
specific_name = 'SELECT_STUDENT'
where db = 'jxgl' and name = 'select_s';



