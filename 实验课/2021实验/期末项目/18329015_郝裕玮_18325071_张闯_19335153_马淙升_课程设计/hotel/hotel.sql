create database hotel default charset=UTF8;

use hotel;
create table room(
	rid int not null,
    rtype int,
    rprice float,
    primary key(rid))default charset=UTF8;

create table guest(
	gid varchar(18) not null,
    gname varchar(10),
    primary key(gid))default charset=UTF8;

create table rorder(
	oid int unique AUTO_INCREMENT,
    starttime date,
    endtime date,
    gid varchar(18),
    oprice float,
    team int,
    primary key(oid),
    foreign key (gid)references guest(gid))auto_increment=1 default charset=UTF8;

create table reserve(
	rid int,
    gid varchar(18)  default '000000000000000000',
    t date,
    discount float,
    primary key (rid,t),
    foreign key (rid) references room(rid),
    foreign key (gid) references guest(gid))default charset=UTF8;

create table summary(
	t date,
    sprice float,
    primary key(t)
)default charset=UTF8;

create table oorder(
	oid int,
    starttime date,
    endtime date,
    gid varchar(18),
    oprice float,
    team int,
    primary key(oid),
    foreign key (gid)references guest(gid))default charset=UTF8;