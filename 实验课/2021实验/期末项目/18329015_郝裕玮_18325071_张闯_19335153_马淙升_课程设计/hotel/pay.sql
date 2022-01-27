
use hotel;
delimiter //
create procedure pay(id int)
begin
	declare st date;
    declare price float;
    set st=(select endtime from rorder where oid=id);
    select oprice into price from rorder where oid=id;
    if st not in (select t from summary)then
	insert into summary values(st,0);
    end if;
    insert into oorder (select * from rorder where id=oid);
    delete from rorder where id=oid;
    update summary set sprice=sprice+price where st=t;
end//