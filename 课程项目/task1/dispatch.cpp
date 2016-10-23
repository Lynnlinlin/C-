//本文件用于把学生记录进对应宿舍
#include <iostream>
#include <map>
#include <iomanip>
#include "dorm.h"
#include "split.h"
#include "students.h"
using namespace std;

void init_dispatch(Dorm &dorm, map<string, Student>& m_Student, istream& in)
{
	string a_str;

	extern double WEIGHT;
	extern double MONEY;
	extern double KNOWLEDGE;
	extern double CHARM;

	while (getline(in, a_str))
	{
		vector<string> a_stu_info;
		vector<int> a_stu_bed_info;

		split(a_str, a_stu_info, a_stu_bed_info);

		m_Student[a_stu_info[0]].name = a_stu_info[0];
		m_Student[a_stu_info[0]].gender = a_stu_info[1];

		m_Student[a_stu_info[0]].weight = WEIGHT;
		m_Student[a_stu_info[0]].money = MONEY;
		m_Student[a_stu_info[0]].knowledge = KNOWLEDGE;
		m_Student[a_stu_info[0]].charm = CHARM;

		if (a_stu_bed_info[0] <= dorm.floors.size() - 1 && a_stu_bed_info[1] <= dorm.floors[a_stu_bed_info[0]].rooms.size() - 1)
		{
			//学生数量少于可容纳量、宿舍还没有人入住、要入宿的人的性别要和第一个入宿的人性别相同才能入宿
			if (dorm.floors[a_stu_bed_info[0]].rooms[a_stu_bed_info[1]].beds.size() <
				dorm.floors[a_stu_bed_info[0]].rooms[a_stu_bed_info[1]].capacity &&
				(dorm.floors[a_stu_bed_info[0]].rooms[a_stu_bed_info[1]].beds.size() == 0 ||
					m_Student[a_stu_info[0]].gender ==
					m_Student[dorm.floors[a_stu_bed_info[0]].rooms[a_stu_bed_info[1]].beds[0].student].gender))
			{
				m_Student[a_stu_info[0]].floor = a_stu_bed_info[0] + 1;
				m_Student[a_stu_info[0]].room = a_stu_bed_info[1] + 1;

				Bed bed;
				bed.student = a_stu_info[0];
				bed.enrolled = true;
				dorm.floors[a_stu_bed_info[0]].rooms[a_stu_bed_info[1]].beds.push_back(bed);

				cout << a_stu_info[0] << "\t" << a_stu_info[1] << "\t" << setfill('0') << setw(2) << a_stu_bed_info[0] << "-" << setfill('0') << setw(2) << a_stu_bed_info[1] << endl;
			}
			else if (m_Student[a_stu_info[0]].gender != m_Student[dorm.floors[a_stu_bed_info[0]].rooms[a_stu_bed_info[1]].beds[0].student].gender)
			{
				cout << a_stu_info[0] << " can't dispatch, because boys and girls can't live in a dorm" << endl;
			}
			else if (dorm.floors[a_stu_bed_info[0]].rooms[a_stu_bed_info[1]].beds.size() >= dorm.floors[a_stu_bed_info[0]].rooms[a_stu_bed_info[1]].capacity)
			{
				cout << a_stu_info[0] << " can't dispatch, because " <<
					setfill('0') << setw(2) << a_stu_bed_info[0] << "-" << setfill('0') << setw(2) << a_stu_bed_info[1] << "was full." << endl;
			}
			else
				cout << a_stu_info[0] << " can't dispatch" << endl;

		}
		else
			cout << a_stu_info[0] << " can't dispatch, because don't have this room." << endl;
	}

	//用于分隔
	cout << endl;
}