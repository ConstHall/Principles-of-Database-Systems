use hotel;
delimiter //
create procedure orderr(rt int,st date,et date,num int,id varchar(18),te int)
begin
	declare n int;
    declare i int default 0;
    declare nprice float default 0;
    declare price float;
    declare d date;
    set n=datediff(et,st);
    while i<n
    do
		set d = date_add(st,interval i day);
        create table r select reserve.rid,t,rprice from reserve,room where reserve.rid=room.rid and rt=room.rtype and d=reserve.t and gid='000000000000000000' limit num;
		update reserve set gid=id where rid in(select rid from r) and t=d;
        select sum(p)into price from (select r.rprice*reserve.discount as p from r,reserve where r.rid=reserve.rid and reserve.t=d)as P;
        set nprice=nprice+price;
        set i=i+1;
        drop table r;
	end while;
    insert into rorder(starttime,endtime,gid,oprice,team) values(st,et,id,nprice,te);
    select oid from rorder where starttime = st and endtime = et and gid=id and oprice=nprice and team=te;
end//