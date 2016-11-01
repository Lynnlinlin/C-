#ifndef GUARD_instructions
#define GUAED_instructions
#include <map>
#include <string>
#include <stdlib.h>
#include <iostream>
#include "dorm.h"

void instructions(Dorm &, std::map<std::string, Student>&, std::istream&);

//������
void move_room(Dorm&, std::map<std::string, Student>&, std::string, int, int, int, int);
//ѧ����ѧ
void stu_quit(Dorm&, std::map<std::string, Student>&, std::string);
//ѧ����ѧ
void stu_enrol(Dorm&, std::map<std::string, Student>&, std::string, std::string, int, int);

//���Ӵ�λ�����䡢����
void add_beds(Dorm&, int, int, int);
void add_rooms(Dorm&, int, int);
void add_floors(Dorm&, int);
#endif