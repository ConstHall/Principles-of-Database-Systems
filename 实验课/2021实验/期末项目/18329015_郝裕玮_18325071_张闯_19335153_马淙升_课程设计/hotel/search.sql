use hotel;
delimiter //
create procedure search(rt int,st date,et date)
begin
	declare n int;
    declare i int default 0;
    set n=datediff(et,st);
    select num,rtype
    from(
    select count(distinct T.rid)as num,rtype
    from(select rid,count(distinct reserve.t) as d from reserve where st<=reserve.t and et>reserve.t and reserve.gid='000000000000000000' group by(rid))as T,room
    where d=n and room.rid=T.rid and room.rtype=rt)as S
    where S.num>0;
end//