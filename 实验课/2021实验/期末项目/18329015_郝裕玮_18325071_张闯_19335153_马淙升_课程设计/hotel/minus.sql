use hotel;

delimiter //

create procedure minus(in rtype1 int,in num1 int)
begin
	declare Minim int;
    declare cnt int default 0;
    declare num int;
    set num=num1;
    select min(rid) into Minim from room where rtype=rtype1;
    while cnt<=num-1
		do
        delete from room where rid=Minim+cnt;
        set cnt=cnt+1;
        end while;
end//



GRANT EXECUTE ON hotel.* TO '123'@'%';