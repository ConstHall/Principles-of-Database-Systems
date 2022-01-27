// mysql.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include "mysql.h"
#include <iomanip>
#include <cstring>


using namespace std;

MYSQL mysql;
MYSQL_FIELD* fd;
MYSQL_RES* res;
MYSQL_ROW row;

//清空MySql操作缓冲区的内容，防止下次MySql操作出错
void clear() {
    do
    {
        MYSQL_RES* pRes = mysql_store_result(&mysql);
        if (pRes != NULL)
            mysql_free_result(pRes);
    } while (!mysql_next_result(&mysql));
}

//用于打印SQL语句执行结果
void printTable() {
    res = mysql_store_result(&mysql);
    if (!res) cout << "Could not get result from " << mysql_error(&mysql);
    else {
        int columns = mysql_num_fields(res);
        char* field[32];
        for (int i = 0; i < columns; ++i) {
            field[i] = mysql_fetch_field(res)->name;
        }
        for (int i = 0; i < columns; ++i) {
            cout << setw(20) << field[i];
        }
        cout << endl;
        while (row = mysql_fetch_row(res)) {
            for (int i = 0; i < columns; ++i)
                cout << setw(20) << row[i];
            cout << endl;
        }
    }
    cout << endl << endl;

}

//结账功能,调用存储过程pay
void pay(int oid) {
    //call pay(oid);
    char strquery[100] = "call pay(";
    char temp[100];
    _itoa(oid, temp, 10);
    strcat(strquery, temp);
    strcat(strquery, ");");
    mysql_query(&mysql, strquery);
}

//财报功能
void sum(string year, string month, string day) {
    //select sum(sprice) as Sum from summary where t like '%'-'%'-'%';
    char query[100] = "select sum(sprice) as Sum from summary where t like '";
    if (strcmp(year.c_str(), "0") == 0) {
        strcat(query, "%");
    }
    else {
        strcat(query, year.c_str());

    }
    strcat(query, "-");
    if (strcmp(month.c_str(), "0") == 0) {
        strcat(query, "%");
    }
    else {
        strcat(query, month.c_str());
    }
    strcat(query, "-");
    if (strcmp(day.c_str(),"0")==0) {
        strcat(query, "%");
    }
    else {
        strcat(query, day.c_str());
    }
    strcat(query, "';");
    mysql_query(&mysql, query);
    printTable();
    clear();
}

//判断输入是否为数字，防止注入式攻击
bool is_num(string p) {
    bool res = true;
    int i = 0;
    for (; i < p.size();++ i) {
        if (p[i] > '9' || p[i] < '0') {
            res = false;
            break;
        }
        i++;
    }
    return res;
}

//查询空房,调用存储过程search
void show_empty_room(int rt,const char* st,const char* et)
{
    //call search(rt,'st','et');
    char strquery[100] = "call search(";
    char temp[10];
    _itoa(rt, temp, 10);
    strcat(strquery, temp);
    strcat(strquery, ",'");
    strcat(strquery, st);
    strcat(strquery, "','");
    strcat(strquery, et);
    strcat(strquery, "');");
    mysql_query(&mysql, strquery);
    printTable();
    clear();
}

//订房(下订单),调用存储过程orderr
void reserve(int rt, const char* st, const char* et,int num,const char* gid,int team)
{
    //call orderr(rt,'st','et',num,'gid',team);
    char strquery[100] = "call orderr(";
    char temp[10];
    _itoa(rt, temp,10);
    strcat(strquery, temp);
    strcat(strquery, ",'");
    strcat(strquery, st);
    strcat(strquery, "','");
    strcat(strquery, et);
    char temp1[10];
    _itoa(num, temp1, 10);
    strcat(strquery, "',");
    strcat(strquery, temp1);
    strcat(strquery, ",'");
    strcat(strquery, gid);
    strcat(strquery, "',");
    char temp2[10];
    _itoa(team, temp2, 10);
    strcat(strquery, temp1);
    strcat(strquery, ");");
    mysql_query(&mysql, strquery);
    
    printTable();
    clear();

}

//获取订房时间
void getTime(string& inYear, string& inMonth, string& inDay, string& outYear, string& outMonth, string& outDay, 
            /*output*/string&inTime,string&outTime) {
    int time;
    while (1) {
        cout << "Please enter the time you want to move in\n";
        cout << "Year: ";
        cin >> inYear;
        if (!is_num(inYear)) continue;
        cout << "Month: ";
        cin >> inMonth;
        if (!is_num(inMonth)) continue;
        cout << "Day: ";
        cin >> inDay;
        if (!is_num(inDay)) continue;
        cout << "Please enter the time you want to move out\n";
        cout << "Year: ";
        cin >> outYear;
        if (!is_num(outYear)) continue;
        cout << "Month: ";
        cin >> outMonth;
        if (!is_num(outMonth)) continue;
        cout << "Day: ";
        cin >> outDay;
        if (!is_num(outDay)) continue;
        if (inMonth.size() == 1) inMonth = '0' + inMonth;
        if (outMonth.size() == 1) outMonth = '0' + outMonth;
        if (inDay.size() == 1) inDay = '0' + inDay;
        if (outDay.size() == 1) outDay = '0' + outDay;
        inTime = inYear + '-' + inMonth + '-' + inDay;
        outTime = outYear + '-' + outMonth + '-' + outDay;
        break;
    }
}

//用户查询已订房间
void show_room_with_orderid(const char* gid1)
{
    //select * from reserve where gid='.....';
    char strquery[100] = "select * from reserve where gid='";
    strcat(strquery, gid1);
    strcat(strquery, "';");
    mysql_query(&mysql, strquery);
    printTable();
    clear();
}

//用户注册并赋予相关权限
int guest_register(const char* id,const char* code,const char* name)
{
    int res = 0;
    //create user '...'@'%' identified by '...';
    char strquery[100] = "create user '";
    strcat(strquery, id);
    strcat(strquery, "'@'%' identified by '");
    strcat(strquery, code);
    strcat(strquery, "';");
    if (mysql_query(&mysql, strquery) == 0) {
        res = 1;
        cout << "Guest Registration Succeed!" << endl << endl << endl;
    }
    else {
        cout << "Guest Registration Failed!" << endl;
        //cout << "失败原因：" << mysql_error(&mysql) << endl << endl << endl;
        cout << "Unable to register with this username or password!" << endl<<endl;
    }
    
    //赋予权限
    //grant all privileges on hotel.* to '....'@'%';
    char strquery1[100] = "grant all privileges on hotel.* to '";
    strcat(strquery1, id);
    strcat(strquery1, "'@'%';");
    mysql_query(&mysql, strquery1);

    //赋予执行存储过程的权限
    //grant execute on hotel.* to '....'@'%';
    char strquery2[100] = "grant execute on hotel.* to '";
    strcat(strquery2, id);
    strcat(strquery2, "'@'%';");
    mysql_query(&mysql, strquery2);

    //将注册客户加入到guest表中
    //insert guest values('...','...');
    char strquery3[100] = "insert guest values('";
    strcat(strquery3, id);
    strcat(strquery3, "','");

    strcat(strquery3, name);
    strcat(strquery3, "');");
    mysql_query(&mysql, strquery3);
    return res;
}

//管理员注册并赋予相关权限
int manager_register(const char* id, const char* code, const char* name)
{
    int res = 0;
    //create user '...'@'%' identified by '...';
    char strquery[100] = "create user ";
    strcat(strquery, name);
    strcat(strquery, "@'%' identified by '");
    strcat(strquery, code);
    strcat(strquery, "';");
    if (mysql_query(&mysql, strquery) == 0) {
        res = 1;
        cout << "Manager Registration Succeed!" << endl << endl << endl;
    }
    else {
        cout << "Manager Registration Failed!" << endl;
        cout << "Unable to register with this username or password!" << endl<<endl;
        //cout << "失败原因：" << mysql_error(&mysql) << endl << endl << endl;
    }

    //赋予权限
    //grant all privileges on hotel.* to '....'@'%';    
    char strquery1[100] = "grant all privileges on hotel.* to '";
    strcat(strquery1, name);
    strcat(strquery1, "'@'%';");
    mysql_query(&mysql, strquery1);

    //赋予执行存储过程的权限
    //grant execute on hotel.* to '....'@'%';
    char strquery2[100] = "grant execute on hotel.* to '";
    strcat(strquery2, name);
    strcat(strquery2, "'@'%';");
    mysql_query(&mysql, strquery2);
    return res;
}

//修改房间数量(增),调用存储过程addr
void add_room(int rt, int num, float rprice)
{
    //call addr(rt,num,rpice);
    char strquery[100] = "call addr(";
    char temp[10];
    _itoa(rt, temp, 10);
    strcat(strquery, temp);
    char temp1[10];
    _itoa(num, temp1, 10);
    strcat(strquery, ",");
    strcat(strquery, temp1);
    strcat(strquery, ",");
    char temp2[100];
    sprintf(temp2, "%f", rprice);
    strcat(strquery, temp2);
    strcat(strquery, ");");
    mysql_query(&mysql, strquery);
}

//修改房间数量(减),调用存储过程minus
void minus_room(int rt, int num)
{
    //call minus(rt,num);
    char strquery[100] = "call minus(";
    char temp[10];
    _itoa(rt, temp, 10);
    strcat(strquery, temp);
    char temp1[10];
    _itoa(num, temp1, 10);
    strcat(strquery, ",");
    strcat(strquery, temp1);
    strcat(strquery, ");");
    mysql_query(&mysql, strquery);
}

//更改房价
void update_room_price(int rtype1, float price_new)
{
    //update room set oprice=price_new where rtype=rtype1;
    char strquery[100] = "update room set rprice=";
    char temp[100];
    sprintf(temp, "%f", price_new);
    strcat(strquery, temp);
    strcat(strquery, " where rtype=");
    char temp1[100];
    _itoa(rtype1, temp1, 10);
    strcat(strquery, temp1);
    strcat(strquery, ";");
    mysql_query(&mysql, strquery);
}

//修改房间类型
void update_room_type(int rid1, int rtype_new)
{
    //update room set rtype=rtype_new where rid=rid1;
    char strquery[100] = "update room set rtype=";
    char temp[100];
    _itoa(rtype_new, temp, 10);
    strcat(strquery, temp);
    strcat(strquery, " where rid=");
    char temp1[100];
    _itoa(rid1, temp1, 10);
    strcat(strquery, temp1);
    strcat(strquery, ";");
    mysql_query(&mysql, strquery);
}

//展示所有房间信息
void show_all_room_info()
{
    //select * from room;
    mysql_query(&mysql, "select * from room;");
    printTable();
}

//管理者，展示用户信息
void show_customer_info()
{
    //select * from guest;
    mysql_query(&mysql, "select * from guest;");
    printTable();
}

//管理者：订单号查询用户信息
void show_customer_with_order_number(const char* oid1)
{
    //select rorder.gid,guest.gname from rorder,guest where oid=oid1 and rorder.gid=guest.gid;
    char strquery[100] = "select rorder.gid,guest.gname from rorder,guest where oid=";
    strcat(strquery, oid1);
    strcat(strquery, " and rorder.gid=guest.gid;");
    mysql_query(&mysql, strquery);
    printTable();
}

//管理者：身份证查询用户信息
void show_customer_with_id(const char* gid1)
{
    //select gid,gname from guest where gid=gid1;
    char strquery[100] = "select gid,gname from guest where gid=\"";
    strcat(strquery, gid1);
    strcat(strquery, "\";");
    mysql_query(&mysql, strquery);
    printTable();
}


//主程序
int main()
{   //初始化MySql
    while (1) {
        cout << "***********************Welcome to Our Hotel*************************\n\n";
        int is_guest = 0;
        int type;
        do {
            cout << "Enter 0 for Log in, 1 for Register a new account.\n";
            cout << "Log in or Regester: ";
            cin >> type;
        } while (type != 0 && type != 1);
        int times = 0;
        string account, password;
        if (type == 1) {
            mysql_init(&mysql);
            if (!mysql_real_connect(&mysql, "localhost", "root", "hyw19991201", "hotel", 3306, 0, 0)) {
                cout << "Server crash, visit us later, goodbye!\n";
                break;
            }
            string query;
            while (1) {
                int re;
                cout << "Register as Manager or Guest. Press 0 for Manager, 1 for Guest\n";
                cin >> re;
                if ((re != 0) && (re != 1)) cout << "not such server\n";
                else if (re == 1) {
                    cout << "Please enter your desire account and password\n";
                    cout << "Account: ";
                    cin >> account;
                    cout << "Password: ";
                    cin >> password;
                    string username;
                    cout << "Username: ";
                    cin >> username;
                    int res;
                    res = guest_register(account.c_str(), password.c_str(), username.c_str());
                    if (res) break;
                }
                else if (re == 0) {
                    cout << "Please enter the manager code:\n";
                    string code;
                    cin >> code;
                    if (code == "123456") {

                    }
                    else {
                        cout << "Wrong Code! We will back to the init interface.";
                        continue;
                    }
                    cout << "Please enter your desire account and password\n";
                    cout << "Account: ";
                    cin >> account;
                    cout << "Password: ";
                    cin >> password;
                    string username;
                    cout << "Username: ";
                    cin >> username;
                    int res;
                    res = manager_register(account.c_str(), password.c_str(), username.c_str());
                    if (res) break;
                }

                }
            }

            do {
                mysql_init(&mysql);
                if (times > 0) {
                    cout << "Account or password is not correct, please check and try again\n\n";
                }
                cout << "Please enter you account and password to log in\n";
                cout << "Account: ";
                cin >> account;
                cout << "Password: ";
                cin >> password;
                cout << endl;
                times++;
            } while (!mysql_real_connect(&mysql, "localhost", account.c_str(), password.c_str(), "hotel", 3306, 0, 0));
            cout << "Hello! You have logged in successfully!\n";
            while (1) {
                int serve, roomType;
                if (is_num(account) && account.size() == 18) is_guest = 1;
                string inYear, inMonth, inDay, outYear, outMonth, outDay, inTime, outTime;
                if (is_guest == 1) {
                    
                    cout << "********************************************************************\n\n";
                    cout << "0--Exit.   1--Reservation.   2--Check Availability\n";
                    cout << "3--Query Your Order Records\n\n";
                    cout << "********************************************************************\n";
                    cout << "Please choose the service you want: ";
                }
                else {
                    cout << "********************************************************************\n\n";
                    cout << "0--Exit.   1--Reservation.   2--Check Availability\n";
                    cout << "3--Query Your Order Records\n";
                    cout << "4--Room Information  5--Guest Information   6--Add Room.\n";
                    cout << "7--Delete Room.      8--Modify Room Price   9--Modify Room Type\n";
                    cout << "10--Pay              11--Financial Report\n\n";
                    cout << "********************************************************************\n";
                    cout << "Please choose the service you want: ";
                }
                cin >> serve;
                string query;
                if (serve == 0) break;
                else if (serve == 1) {
                    int team;
                    cout << "Press 0 for Individual Reservation, 1 for Team Reservation: ";
                    cin >> team;
                    if (team) {
                        getTime(inYear, inMonth, inDay, outYear, outMonth, outDay, inTime, outTime);
                        cout << "Please enter the ID of the guest(18 digits of numbers): \n";
                        char gid[20];
                        cin >> gid;
                        while (strlen(gid) != 18 || (!is_num(gid))) {
                            cout << "It is not a vaild id, please try again!\n\n";
                            cin >> gid;
                        }
                        int num;
                        cout << "How many single rooms do you need: ";
                        cin >> num;
                        reserve(1, inTime.c_str(), outTime.c_str(), num, gid, team);
                        cout << "How many double rooms do you need: ";
                        cin >> num;
                        reserve(2, inTime.c_str(), outTime.c_str(), num, gid, team);
                        cout << "How many large rooms do you need: ";
                        cin >> num;
                        reserve(3, inTime.c_str(), outTime.c_str(), num, gid, team);
                    }
                    else {
                        getTime(inYear, inMonth, inDay, outYear, outMonth, outDay, inTime, outTime);
                        cout << "Which type of the room do you want to reserve, 1 for single room, 2 for double room, 3 for large room\n";
                        cin >> roomType;
                        int num = 1;
                        cout << "Please enter the ID of the guest(18 digits of numbers): \n";
                        char gid[20];
                        cin >> gid;
                        while (strlen(gid) != 18 || (!is_num(gid))) {
                            cout << "It is not a vaild id, please try again\n\n";
                            cin >> gid;
                        }
                        if (roomType > 0 && roomType < 4) reserve(roomType, inTime.c_str(), outTime.c_str(), 1, gid, team);
                        else cout << "We don't have such a room\n\n";
                    }

                }
                else if (serve == 2) {
                    getTime(inYear, inMonth, inDay, outYear, outMonth, outDay, inTime, outTime);
                    cout << "Which type of room are you to query, 1 for single room, 2 for double room, 3 for large room\n";
                    cin >> roomType;
                    if (roomType > 0 && roomType < 4) show_empty_room(roomType, inTime.c_str(), outTime.c_str());
                    else cout << "We don't have such a room\n\n";

                }
                else if (serve == 3) {
                    string id;
                    cout << "Enter your ID: ";
                    cin >> id;
                    if (is_num(id))
                        show_room_with_orderid(id.c_str());
                }
                else if (is_guest == 0) {
                    if (serve == 4) {
                        show_all_room_info();
                    }
                    else if (serve == 5) {
                        cout << "Press 0 for All Guest Information, 1 for Specific Guest\n";
                        int t, q;
                        cin >> t;
                        if (t == 0) show_customer_info();
                        else if (t == 1) {
                            cout << "Press 0 for Searching by Order ID, 1 for Searching by Guest ID\n";
                            cin >> q;
                            if (q == 0) {
                                cout << "Order ID: ";
                                string p;
                                cin >> p;
                                if (is_num(p))
                                    show_customer_with_order_number(p.c_str());
                            }
                            else if (q == 1) {
                                cout << "Guest ID: ";
                                string p;
                                cin >> p;
                                if (is_num(p))
                                    show_customer_with_id(p.c_str());
                            }
                            else cout << "not such serve\n";
                        }
                        else cout << "not such serve\n";
                    }
                    else if (serve == 6) {
                        cout << "Enter the Room Type to update its number: ";
                        int rt1;
                        cin >> rt1;
                        cout << "the number of rooms you want to add: ";
                        int num;
                        cin >> num;
                        float price;
                        cout << "set the price: ";
                        cin >> price;
                        add_room(rt1, num, price);
                    }
                    else if (serve == 7) {
                        cout << "Enter the Room Type to update its number: ";
                        int rt1;
                        cin >> rt1;
                        cout << "The number of rooms you want to minus: ";
                        int num;
                        cin >> num;
                        minus_room(rt1, num);
                    }
                    else if (serve == 8) {
                        cout << "Enter the Room Type to modify its price: ";
                        int rt1;
                        cin >> rt1;
                        cout << "The new price for this type of room: ";
                        float price;
                        cin >> price;
                        update_room_price(rt1, price);
                    }
                    else if (serve == 9) {
                        cout << "Enter the Room_ID to modify its type: ";
                        int rn1;
                        cin >> rn1;
                        cout << "The new type for this room: ";
                        int rt1;
                        cin >> rt1;
                        update_room_type(rn1, rt1);

                    }
                    else if (serve == 10) {
                        cout << "Enter the Order ID to pay:\n";
                        int oid;
                        cin >> oid;
                        pay(oid);
                    }
                    else if (serve == 11) {
                        string year, month, day;
                        cout << "Enter the year of the report you want to query(0 for not set):\n";
                        cin >> year;
                        cout << "Enter the month of the report you want to query(0 for not set):\n";
                        cin >> month;
                        cout << "Enter the day of the report you want to query(0 for not set):\n";
                        cin >> day;
                        sum(year, month, day);
                    }
                    else cout << "We don't have this command!\n\n";

                }
                else {
                    cout << "We don't have this command!\n\n";
                }
            }

        }
        //关闭MySql*/
        mysql_close(&mysql);
}
