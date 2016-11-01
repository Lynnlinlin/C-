#ifndef GUARD_instructions
#define GUAED_instructions
#include <map>
#include <string>
#include <stdlib.h>
#include <iostream>
#include "dorm.h"

void instructions(Dorm &, std::map<std::string, Student>&, std::istream&);

//换宿舍
void move_room(Dorm&, std::map<std::string, Student>&, std::string, int, int, int, int);
//学生退学
void stu_quit(Dorm&, std::map<std::string, Student>&, std::string);
//学生入学
void stu_enrol(Dorm&, std::map<std::string, Student>&, std::string, std::string, int, int);

//增加床位、房间、层数
void add_beds(Dorm&, int, int, int);
void add_rooms(Dorm&, int, int);
void add_floors(Dorm&, int);
#endif