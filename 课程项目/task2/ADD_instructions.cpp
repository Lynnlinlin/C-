#include <stdio.h>
#include <iostream>
#include <string>
#include "dorm.h"
#include "students.h"
#include "instructions.h"
using namespace std;

//增加床位
void add_beds(Dorm& dorm, int floor, int room, int add_bed_amount)
{
	dorm.floors[floor].rooms[room].capacity += add_bed_amount;
}

//增加房间
void add_rooms(Dorm& dorm, int floor, int add_room_amount)
{
	for (int i = 0; i != add_room_amount; i++)
	{
		Room room = init_a_room();
		room.room_no = dorm.floors[floor].room_amount + i + 1;
		dorm.floors[floor].rooms.push_back(room);
	}
	dorm.floors[floor].room_amount += add_room_amount;
}

//增加层数
void add_floors(Dorm& dorm, int add_floor_amount)
{
	for (int i = 0; i != add_floor_amount; i++)
	{
		Floor floor = init_a_floor();
		floor.floor_no = dorm.floor_amount + i + 1;
		dorm.floors.push_back(floor);
	}
	dorm.floor_amount += add_floor_amount;
}