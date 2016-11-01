//该头文件用于声明学生信息
#ifndef GUARD_students
#define GUARD_students

#include <string>
#include <map>

typedef struct
{
	std::string name;
	std::string gender;
	bool enrolled;
	double knowledge;
	double charm;
	double weight;
	double money;
	int floor;
	int room;
}Student;

double express_count(double, double, double, std::string);
double charm_count(double, double, double, std::string);
void stu_act_count(double, double, double, std::map<std::string, Student>&, std::string);
#endif