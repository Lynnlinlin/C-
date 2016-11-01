//���ļ����ڳ�ʼ��	
#include <iostream>
#include <stdlib.h>
#include <regex>
#include "dorm.h"
#include "students.h"
using namespace std;

vector<Floor>::size_type FLOOR;
vector<Room>::size_type ROOM;
vector<Bed>::size_type CAPACITY;

double WEIGHT;
double MONEY;
double KNOWLEDGE;
double CHARM;

double FOOD_WEIGHT;
double FOOD_COST;
double STUDY_WEIGHT;
double STUDY_KNOWLEDGE;
double WORK_MONEY;
double WORK_WEIGHT;

//ѧ��״̬�仯��ʽ��
string WEIGHT_INC;
string MONEY_INC;
string KNOWLEDGE_INC;
string CHARM_INC;

//��ʼ��һ��ѧ����Ϣ
Student init_a_stu()
{
	Student stu;
	stu.weight = WEIGHT;
	stu.money = MONEY;
	stu.knowledge = KNOWLEDGE;
	stu.charm = CHARM;
	stu.enrolled = false;
	return stu;
}

//��ʼ��һ����λ
Bed init_a_bed()
{
	Bed bed;
	return bed;
}

//��ʼ��һ�䷿��
Room init_a_room()
{
	Room room;
	room.capacity = CAPACITY;
	return room;
}

//��ʼ��һ��
Floor init_a_floor()
{
	Floor floor;
	floor.room_amount = ROOM;
	for (int i = 0; i < floor.room_amount; i++)
	{
		Room room = init_a_room();
		room.room_no = i + 1;
		floor.rooms.push_back(room);
	}
	return floor;
}

//��ʼ��һ������
Dorm init_a_dorm()
{
	Dorm dorm;
	dorm.floor_amount = FLOOR;
	for (int i = 0; i < dorm.floor_amount; i++)
	{
		Floor floor = init_a_floor();
		floor.floor_no = i + 1;
		dorm.floors.push_back(floor);
	}
	return dorm;
}

void init(Dorm &dorm, istream &in)
{
	string line;
	match_results<string::const_iterator> result;

	while (getline(in, line))
	{
		//ƥ��FLOOR
		regex pattern("FLOOR:[\\s]*(\\d+)[\\s]*");
		if (regex_match(line, result, pattern))
		{
			//ת��Ϊ�ַ�������
			string str_floor = result[1];
			//ת����int��
			FLOOR = atoi(str_floor.c_str());
		}

		//ƥ��ROOM
		pattern = ("ROOM:[\\s]*(\\d+)[\\s]*");
		if (regex_match(line, result, pattern))
		{
			string str_room = result[1];
			ROOM = atoi(str_room.c_str());
		}

		//ƥ��CAPACITY
		pattern = ("CAPACITY:[\\s]*(\\d+)[\\s]*");
		if (regex_match(line, result, pattern))
		{
			string str_capacity = result[1];
			CAPACITY = atoi(str_capacity.c_str());
		}

		//ƥ��WEIGHT
		pattern = ("WEIGHT:[\\s]*(\\d+)[\\s]*");
		if (regex_match(line, result, pattern))
		{
			string str_weight = result[1];
			WEIGHT = atoi(str_weight.c_str());
		}

		//ƥ��MONEY
		pattern = ("MONEY:[\\s]*(\\d+)[\\s]*");
		if (regex_match(line, result, pattern))
		{
			string str_money = result[1];
			MONEY = atoi(str_money.c_str());
		}

		//ƥ��KNOWLEDGE
		pattern = ("KNOWLEDGE:[\\s]*(\\d+)[\\s]*");
		if (regex_match(line, result, pattern))
		{
			string str_knowledge = result[1];
			KNOWLEDGE = atoi(str_knowledge.c_str());
		}

		//ƥ��KNOWLEDGE
		pattern = ("KNOWLEDGE:[\\s]*(\\d+)[\\s]*");
		if (regex_match(line, result, pattern))
		{
			string str_knowledge = result[1];
			KNOWLEDGE = atoi(str_knowledge.c_str());
		}

		//ƥ��CHARM
		pattern = ("CHARM:[\\s]*(\\d+)[\\s]*");
		if (regex_match(line, result, pattern))
		{
			string str_charm = result[1];
			CHARM = atoi(str_charm.c_str());
		}

		//ƥ��FOOD_WEIGHT
		pattern = ("FOOD_WEIGHT:[\\s]*(\\d+)[\\s]*");
		if (regex_match(line, result, pattern))
		{
			string str_foodweight = result[1];
			FOOD_WEIGHT = atoi(str_foodweight.c_str());
		}

		//ƥ��FOOD_COST
		pattern = ("FOOD_COST:[\\s]*(\\d+)[\\s]*");
		if (regex_match(line, result, pattern))
		{
			string str_foodcost = result[1];
			FOOD_COST = atoi(str_foodcost.c_str());
		}

		//ƥ��STUDY_WEIGHT
		pattern = ("STUDY_WEIGHT:[\\s]*(\\d+)[\\s]*");
		if (regex_match(line, result, pattern))
		{
			string str_studyweight = result[1];
			STUDY_WEIGHT = atoi(str_studyweight.c_str());
		}

		//ƥ��STUDY_KNOWLEDGE
		pattern = ("STUDY_KNOWLEDGE:[\\s]*(\\d+)[\\s]*");
		if (regex_match(line, result, pattern))
		{
			string str_studyknowledge = result[1];
			STUDY_KNOWLEDGE = atoi(str_studyknowledge.c_str());
		}

		//ƥ��WORK_WEIGHT
		pattern = ("WORK_WEIGHT:[\\s]*(\\d+)[\\s]*");
		if (regex_match(line, result, pattern))
		{
			string str_workweight = result[1];
			WORK_WEIGHT = atoi(str_workweight.c_str());
		}

		//ƥ��WORK_MONEY
		pattern = ("WORK_MONEY:[\\s]*(\\d+)[\\s]*");
		if (regex_match(line, result, pattern))
		{
			string str_workmoney = result[1];
			WORK_MONEY = atoi(str_workmoney.c_str());
		}

		//ƥ��WEIGHT_INC
		pattern = ("WEIGHT_INC = (.*)");
		if (regex_match(line, result, pattern))
			WEIGHT_INC = result[1];

		//ƥ��MONEY_INC
		pattern = ("MONEY_INC = (.*)");
		if (regex_match(line, result, pattern))
			MONEY_INC = result[1];

		//ƥ��KNOWLEDGE_INC
		pattern = ("KNOWLEDGE_INC = (.*)");
		if (regex_match(line, result, pattern))
			KNOWLEDGE_INC = result[1];

		//ƥ��CHARM_INC
		pattern = ("CHARM_INC = (.*)");
		if (regex_match(line, result, pattern))
			CHARM_INC = result[1];
	}

	dorm = init_a_dorm();
}