use hotel;

delimiter //
create procedure addr(in rtype1 int,in num1 int,in rprice float)
begin
	declare max int;
    declare cnt int default 1;
    declare num int;
    set num=num1;
    select max(rid) into max from room where rtype=rtype1;
    while cnt<=num
		do
        insert into room values(max+cnt,rtype1,rprice);
        set cnt=cnt+1;
	end while;
end//
