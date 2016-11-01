#ifndef GUARD_dorm
#define GUARD_dorm

#include <stdio.h>
#include <string>
#include<fstream>
#include <vector>
#include <map>
#include "students.h"

//���ļ����������й�������Ϣ
typedef struct
{
	std::string student;
}Bed;

typedef struct
{
	int room_no;//�����
	std::vector<Bed>::size_type capacity;//��������
	std::vector<Bed> beds;
}Room;

typedef struct
{
	int floor_no;//�ڼ���
	std::vector<Room>::size_type room_amount;//������Ŀ
	std::vector<Room> rooms;
}Floor;

typedef struct
{
	std::vector<Floor>::size_type floor_amount;//����
	std::vector<Floor> floors;
}Dorm;

//��ʼ��һ����λ
Bed init_a_bed();
//��ʼ��һ�䷿�䡢һ�㡢һ������
Room init_a_room();
Floor init_a_floor();
Dorm init_a_dorm();

//�����ʼ��
void init(Dorm &, std::istream&);

//��ʼ��ѧ���������
void init_dispatch(Dorm &, std::map<std::string, Student>&, std::istream&);

#endif