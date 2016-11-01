//���ļ����ڷ�����������Ӧ�ĺ���
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
	const regex space("[^\\s]*");//�жϸ����Ƿ�ȫΪ�ո�����ǿո������
	match_results<string::const_iterator> result;

	//ƥ���������᷿�䡢��������λ
	const regex pattern("([^\\s]+)[\\s]+(.*)");
	const regex pattern_addfloor("ADD[\\s]+([\\d]+)[\\s]+FLOOR\\(s\\)[\\s]*");
	const regex pattern_addroom("ADD[\\s]+([\\d]+)[\\s]+ROOM\\(s\\)[\\s]+TO[\\s]+([\\d]+)[\\s]+FLOOR[\\s]*");
	const regex pattern_addbed("ADD[\\s]+([\\d]+)[\\s]+BED\\(s\\)[\\s]+TO[\\s]+([\\d]+)\\-([\\d]+)[\\s]*");

	//ƥ���ѧ���Ĳ���
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
				//ƥ�䵽���Ӳ�������������Ӳ�������
				if (regex_match(a_str, result, pattern_addfloor))
				{
					//ת��Ϊ�ַ�������
					string str_addfloor = result[1];
					//ת����int��
					int add_floor = atoi(str_addfloor.c_str());
					add_floors(dorm, add_floor);
					cout << "added floor(s) amount: " << add_floor << endl;
				}
				//ƥ�䵽���ӷ���������뵽���ӷ��亯��
				else if (regex_match(a_str, result, pattern_addroom))
				{
					string str_addroom = result[1];
					int add_room = atoi(str_addroom.c_str());

					string floor_no = result[2];
					int floor = atoi(floor_no.c_str()) - 1;

					add_rooms(dorm, floor, add_room);
					cout << "floor number: " << floor + 1 << " " << " add room(s) amount: " << add_room << endl;
				}
				//ƥ�䵽���Ӵ�λ������뵽���Ӵ�λ����
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

				//�ȴ�ӡ�����֣������ٴ�Ӧ����Ӧ�������
				cout << a_stu_name << ":" << endl;

				while (a_instruc.size())
				{
					//ƥ�任��������
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
					//ƥ����ѧ����
					else if (regex_match(a_instruc, result, pattern_quit))
					{
						stu_quit(dorm, m_Student, a_stu_name);
						cout << "quitted" << endl;
						a_instruc = result[1];
					}
					//ƥ����ѧ�����뷿������
					else if (regex_match(a_instruc, result, pattern_enrol))
					{
						string a_stu_gender = result[1];
						string str_enrol_floor = result[2];
						string str_enrol_room = result[3];
						a_instruc = result[4];

						int enrol_floor = atoi(str_enrol_floor.c_str()) - 1;
						int enrol_room = atoi(str_enrol_room.c_str()) - 1;

						stu_enrol(dorm, m_Student, a_stu_name, a_stu_gender, enrol_floor, enrol_room);

						cout << "enrolled�� " << "enrol room : " << setfill('0') << setw(2) << m_Student[a_stu_name].floor << "-" << setfill('0') << setw(2) << m_Student[a_stu_name].room << endl;
					}
					//ƥ������
					else if (regex_match(a_instruc, result, pattern_act))
					{

						//��ѧ���Է�����ʱ
						if (result[1] == "EAT")
						{
							string str_eat = result[2];
							sum_eat += atoi(str_eat.c_str());
						}
						//��ѧ��ѧϰ����ʱ
						else if (result[1] == "STUDY")
						{
							string str_study = result[2];
							sum_study += atoi(str_study.c_str());
						}
						//��ѧ����������ʱ
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

				//���ѧ���гԷ�ѧϰ������ʱ�䡢�ͽ����Ǵ�ӡ
				if (sum_eat || sum_study || sum_work)
					cout << "sum_eat:" << sum_eat << " sum_study:" << sum_study << " sum_work:" << sum_work << endl;

				//��ѧ�����仯�����ء�֪ʶ����������Ǯ�������
				stu_act_count(sum_eat, sum_study, sum_work, m_Student, a_stu_name);

				cout << "KNOEWLEDGE: " << m_Student[a_stu_name].knowledge << endl;
				cout << "CHARM: " << m_Student[a_stu_name].charm << endl;
				cout << "WEIGHT: " << m_Student[a_stu_name].weight << endl;
				cout << "MONEY: " << m_Student[a_stu_name].money << endl;

				//���ڷָ�
				cout << endl;
			}
		}
		else
			cout << "invalid instruction" << endl;
	}

	//���ڷָ�
	cout << endl;
}