create table paper
   (pno varchar(20),
	pna varchar(20),
	ppr float(20),
    primary key(pno)); #设置主键为pno

create table customer
   (cno varchar(20), 
	cna varchar(20),
	adr varchar(20),
    primary key(cno)); #设置主键为cno
    
create table cp
   (cno varchar(20),
	pno varchar(20),
	num varchar(20) default'1', #设置num默认值为1
	primary key (cno,pno), #设置主键为pno和cno
    foreign key(cno) references customer(cno), 
    # 保证顾客订阅表(cp)中的顾客编号(cno)必定存在于顾客编码表(customer)中
    foreign key(pno) references paper(pno)); 
    # 保证顾客订阅表(cp)中的报纸编号(pno)必定存在于报纸编码表(paper)中


alter table paper change pna pna varchar(20) character set utf8 collate utf8_general_ci;
alter table customer change cna cna varchar(20) character set utf8 collate utf8_general_ci;
alter table customer change adr adr varchar(20) character set utf8 collate utf8_general_ci;
 # 否则会导致插入中文报错
 
insert into paper values('000001','人民日报',12.5);
insert into paper values('000002','解放军报',14.5);
insert into paper values('000003','光明日报',10.5);
insert into paper values('000004','青年报',11.5);
insert into paper values('000005','扬子日报',18.5);
#依次插入教材中paper表格信息

insert into customer values('0001','李涛','无锡市解放东路123号');
insert into customer values('0002','钱金浩','无锡市人民西路234号');
insert into customer values('0003','邓杰','无锡市惠河路432号');
insert into customer values('0004','朱海红','无锡市中山东路432号');
insert into customer values('0005','欧阳阳文','无锡市中山东路532号');
#依次插入教材中customer表格信息

insert into cp values('0001','000001','2');
insert into cp values('0001','000002','4');
insert into cp values('0001','000005','6');
insert into cp values('0002','000001','2');
insert into cp values('0002','000003','2');
insert into cp values('0002','000005','2');
insert into cp values('0003','000003','2');
insert into cp values('0003','000004','4');
insert into cp values('0004','000001','1');
insert into cp values('0004','000003','3');
insert into cp values('0004','000005','2');
insert into cp values('0005','000003','4');
insert into cp values('0005','000002','1');
insert into cp values('0005','000004','3');
insert into cp values('0005','000005','5');
insert into cp values('0005','000001','4');
#依次插入教材中cp表格信息

create view C_P_N as
select cno,cna,pno,pna,num
from customer natural join paper natural join cp;

select *from dingbao.cp;

select *from dingbao.customer;

select *from dingbao.paper;

SELECT *FROM dingbao.C_P_N;

alter view C_P_N as
select cno,cna,pno,pna,num,ppr #增加报纸单价ppr
from customer natural join paper natural join cp;

#select *from dingbao.C_P_N;

update C_P_N set num=6 where cna='李涛' and pna='人民日报';

update C_P_N set pna='青年日报' where pno='000004';

#drop view if exists C_P_N;

#select *from dingbao.C_P_N;

