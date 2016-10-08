#ifndef GUARD_Student_info
#define GUARD_Student_info
/*
if not define GUARD_Student_info
define 引入GUARD_Student_info
endif: 否则不需要引入
*/
#include <iostream>
#include <string>
#include <vector>

//头文件最好不要用using，为用户保留最大限度的灵活性，因用户可能不想用using声明
struct Student_info
{
	std::string name;
	double midterm, final;
	std::vector<double> homework;
};

bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream&, Student_info&);

#endif