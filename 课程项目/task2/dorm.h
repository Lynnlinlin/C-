#ifndef GUARD_dorm
#define GUARD_dorm

#include <stdio.h>
#include <string>
#include<fstream>
#include <vector>
#include <map>
#include "students.h"

//该文件用于声明有关宿舍信息
typedef struct
{
	std::string student;
}Bed;

typedef struct
{
	int room_no;//房间号
	std::vector<Bed>::size_type capacity;//房间容量
	std::vector<Bed> beds;
}Room;

typedef struct
{
	int floor_no;//第几层
	std::vector<Room>::size_type room_amount;//房间数目
	std::vector<Room> rooms;
}Floor;

typedef struct
{
	std::vector<Floor>::size_type floor_amount;//层数
	std::vector<Floor> floors;
}Dorm;

//初始化一个床位
Bed init_a_bed();
//初始化一间房间、一层、一栋宿舍
Room init_a_room();
Floor init_a_floor();
Dorm init_a_dorm();

//宿舍初始化
void init(Dorm &, std::istream&);

//初始化学生宿舍分配
void init_dispatch(Dorm &, std::map<std::string, Student>&, std::istream&);

#endif