//此文件用于分配各条命令对应的函数
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <regex>
#include <string>
#include "dorm.h"
#include "students.h"
#include "instructions.h"
using namespace std;

void instructions(Dorm &dorm, map<std::string, Student>& m_Student, istream& in)
{
	string a_str;
	const regex space("[^\\s]*");//判断改行是否全为空格，如果是空格就跳过
	match_results<string::const_iterator> result;

	//匹配增加宿舍房间、层数、床位
	const regex pattern("([^\\s]+)[\\s]+(.*)");
	const regex pattern_addfloor("ADD[\\s]+([\\d]+)[\\s]+FLOOR\\(s\\)[\\s]*");
	const regex pattern_addroom("ADD[\\s]+([\\d]+)[\\s]+ROOM\\(s\\)[\\s]+TO[\\s]+([\\d]+)[\\s]+FLOOR[\\s]*");
	const regex pattern_addbed("ADD[\\s]+([\\d]+)[\\s]+BED\\(s\\)[\\s]+TO[\\s]+([\\d]+)\\-([\\d]+)[\\s]*");

	//匹配对学生的操作
	const regex pattern_move("MOVE[\\s]+FROM[\\s]+([\\d]+)\\-([\\d]+)[\\s]+TO[\\s]+([\\d]+)\\-([\\d]+)[\\s]*(.*)");
	const regex pattern_quit("QUIT[\\s]*(.*)");
	const regex pattern_enrol("([^\\s]*)[\\s]*ENROL[\\s]+(\\d+)\\-(\\d+)[\\s]*(.*)");
	const regex pattern_act("([A-Z]+)[\\s]+(\\d+)[\\s]*(.*)");

	while (getline(in, a_str))
	{
		match_results<string::const_iterator> result;

		if (regex_match(a_str, result, space))
			continue;
		else if (regex_match(a_str, result, pattern))
		{
			if (result[1] == "ADD")
			{
				//匹配到增加层数命令，进入增加层数函数
				if (regex_match(a_str, result, pattern_addfloor))
				{
					//转换为字符串类型
					string str_addfloor = result[1];
					//转换到int型
					int add_floor = atoi(str_addfloor.c_str());
					add_floors(dorm, add_floor);
					cout << "added floor(s) amount: " << add_floor << endl;
				}
				//匹配到增加房间命令，进入到增加房间函数
				else if (regex_match(a_str, result, pattern_addroom))
				{
					string str_addroom = result[1];
					int add_room = atoi(str_addroom.c_str());

					string floor_no = result[2];
					int floor = atoi(floor_no.c_str()) - 1;

					add_rooms(dorm, floor, add_room);
					cout << "floor number: " << floor + 1 << " " << " add room(s) amount: " << add_room << endl;
				}
				//匹配到增加床位命令，进入到增加床位函数
				else if (regex_match(a_str, result, pattern_addbed))
				{
					string str_addbed = result[1];
					int add_bed = atoi(str_addbed.c_str());

					string floor_no = result[2];
					int floor = atoi(floor_no.c_str()) - 1;

					string room_no = result[3];
					int room = atoi(room_no.c_str()) - 1;

					add_beds(dorm, floor, room, add_bed);
					cout << "room_number: " << setfill('0') << setw(2) << floor + 1 << "-" << setfill('0') << setw(2) << room + 1 << " add bed(s) amount : " << add_bed << endl;
				}
				else
				{
					cout << "ADD instruction error" << endl;
				}
			}
			else
			{
				string a_stu_name = result[1];
				string a_instruc = result[2];

				int sum_eat = 0, sum_study = 0, sum_work = 0;

				//先打印出名字，后面再答应出对应操作结果
				cout << a_stu_name << ":" << endl;

				while (a_instruc.size())
				{
					//匹配换宿舍命令
					if (regex_match(a_instruc, result, pattern_move))
					{
						string str_ori_floor = result[1];
						string str_ori_room = result[2];
						string str_new_floor = result[3];
						string str_new_room = result[4];
						a_instruc = result[5];

						int ori_floor = atoi(str_ori_floor.c_str()) - 1;
						int ori_room = atoi(str_ori_room.c_str()) - 1;
						int new_floor = atoi(str_new_floor.c_str()) - 1;
						int new_room = atoi(str_new_room.c_str()) - 1;

						move_room(dorm, m_Student, a_stu_name, ori_floor, ori_room, new_floor, new_room);

						cout << "original room : " << setfill('0') << setw(2) << ori_floor + 1 << "-" << setfill('0') << setw(2) << ori_room + 1 <<
							" new room: " << setfill('0') << setw(2) << new_floor + 1 << "-" << setfill('0') << setw(2) << new_room + 1 << endl;
					}
					//匹配退学命令
					else if (regex_match(a_instruc, result, pattern_quit))
					{
						stu_quit(dorm, m_Student, a_stu_name);
						cout << "quitted" << endl;
						a_instruc = result[1];
					}
					//匹配入学、搬入房间命令
					else if (regex_match(a_instruc, result, pattern_enrol))
					{
						string a_stu_gender = result[1];
						string str_enrol_floor = result[2];
						string str_enrol_room = result[3];
						a_instruc = result[4];

						int enrol_floor = atoi(str_enrol_floor.c_str()) - 1;
						int enrol_room = atoi(str_enrol_room.c_str()) - 1;

						stu_enrol(dorm, m_Student, a_stu_name, a_stu_gender, enrol_floor, enrol_room);

						cout << "enrolled： " << "enrol room : " << setfill('0') << setw(2) << m_Student[a_stu_name].floor << "-" << setfill('0') << setw(2) << m_Student[a_stu_name].room << endl;
					}
					//匹配活动命令
					else if (regex_match(a_instruc, result, pattern_act))
					{

						//找学生吃饭总用时
						if (result[1] == "EAT")
						{
							string str_eat = result[2];
							sum_eat += atoi(str_eat.c_str());
						}
						//找学生学习总用时
						else if (result[1] == "STUDY")
						{
							string str_study = result[2];
							sum_study += atoi(str_study.c_str());
						}
						//找学生工作总用时
						else if (result[1] == "WORK")
						{
							string str_work = result[2];
							sum_work += atoi(str_work.c_str());
						}
						else
						{
							cout << "invalid student act instruction" << endl;
							break;
						}
						a_instruc = result[3];
					}
					else
					{
						cout << "invalid student instruction" << endl;
						break;
					}
				}

				//如果学生有吃饭学习工作的时间、就将他们打印
				if (sum_eat || sum_study || sum_work)
					cout << "sum_eat:" << sum_eat << " sum_study:" << sum_study << " sum_work:" << sum_work << endl;

				//对学生活动后变化的体重、知识、魅力、金钱计算出来
				stu_act_count(sum_eat, sum_study, sum_work, m_Student, a_stu_name);

				cout << "KNOEWLEDGE: " << m_Student[a_stu_name].knowledge << endl;
				cout << "CHARM: " << m_Student[a_stu_name].charm << endl;
				cout << "WEIGHT: " << m_Student[a_stu_name].weight << endl;
				cout << "MONEY: " << m_Student[a_stu_name].money << endl;

				//用于分隔
				cout << endl;
			}
		}
		else
			cout << "invalid instruction" << endl;
	}

	//用于分隔
	cout << endl;
}