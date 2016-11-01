#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include "dorm.h"
#include "students.h"
#include "instructions.h"
using namespace std;

int find_stu(Dorm &dorm, int floor, int room, string name)
{
	int i;
	for (i = 0; i != dorm.floors[floor].rooms[room].beds.size(); i++)
		if (dorm.floors[floor].rooms[room].beds[i].student == name)
			return i;
	if (i == dorm.floors[floor].rooms[room].beds.size());
	{
		cout << "can't find " << name << endl;
		return -1;
	}
}

//������
void move_room(Dorm& dorm, map<string, Student>& m_Student, string a_stu_name, int ori_floor, int ori_room, int new_floor, int new_room)
{
	int bed_num = find_stu(dorm, ori_floor, ori_room, a_stu_name);
	if (bed_num!=-1)
		dorm.floors[ori_floor].rooms[ori_room].beds.erase(dorm.floors[ori_floor].rooms[ori_room].beds.begin() + bed_num);
	if (dorm.floors[new_floor].rooms[new_room].capacity > dorm.floors[new_floor].rooms[new_room].beds.size())
	{
		Bed bed;
		bed.student = a_stu_name;
		dorm.floors[new_floor].rooms[new_room].beds.push_back(bed);
		m_Student[a_stu_name].floor = new_floor + 1;
		m_Student[a_stu_name].room = new_room + 1;
	}
	else
		cout << "can't move to " << setfill('0') << setw(2) << ori_floor << "-" << setfill('0') << setw(2) << ori_room << endl;
}

//ѧ����ѧ
void stu_quit(Dorm& dorm, map<string, Student>& m_Student, string a_stu_name)
{
	int floor = m_Student[a_stu_name].floor - 1;
	int room = m_Student[a_stu_name].room - 1;

	int bed_num = find_stu(dorm, floor, room, a_stu_name);
	dorm.floors[floor].rooms[room].beds.erase(dorm.floors[floor].rooms[room].beds.begin() + bed_num);

	m_Student[a_stu_name].enrolled = 0;
}

//ѧ����ѧ
void stu_enrol(Dorm& dorm, map<string, Student>& m_Student, string a_stu_name, string a_stu_gender, int floor, int room)
{
	//Ҫ������λ�á�ѧ��ԭ��û�����޹��Ű����淽������
	if ((dorm.floors[floor].rooms[room].capacity > dorm.floors[floor].rooms[room].beds.size()) &&
		!m_Student[a_stu_name].enrolled)
	{
		Bed bed;
		bed.student = a_stu_name;
		dorm.floors[floor].rooms[room].beds.push_back(bed);
		m_Student[a_stu_name].gender = a_stu_gender;
		m_Student[a_stu_name].enrolled = true;
		m_Student[a_stu_name].floor = floor + 1;
		m_Student[a_stu_name].room = room + 1;
	}
	//�������˱���
	else if (dorm.floors[floor].rooms[room].capacity <= dorm.floors[floor].rooms[room].beds.size())
	{
		cout << "this room was already fulled" << endl;
	}
	//�����ѧ�������ޣ���û����ѧ���ͽ��л����ᴦ��
	else if (m_Student[a_stu_name].enrolled)
	{
		cout << "this student has already enrolled, now change his/her dorm." << endl;
		cout << "original room : " << setfill('0') << setw(2) << m_Student[a_stu_name].floor << "-" << setfill('0') << setw(2) << m_Student[a_stu_name].room <<
			" new room: " << setfill('0') << setw(2) << floor + 1 << "-" << setfill('0') << setw(2) << room + 1 << endl;
		move_room(dorm, m_Student, a_stu_name, m_Student[a_stu_name].floor - 1, m_Student[a_stu_name].room - 1, floor, room);
	}
	else
	{
		cout << "this student can't enrolled" << endl;
	}
}