#ifndef GUARD_Student_info
#define GUARD_Student_info
/*
if not define GUARD_Student_info
define ����GUARD_Student_info
endif: ������Ҫ����
*/
#include <iostream>
#include <string>
#include <vector>

//ͷ�ļ���ò�Ҫ��using��Ϊ�û���������޶ȵ�����ԣ����û����ܲ�����using����
struct Student_info
{
	std::string name;
	double midterm, final;
	std::vector<double> homework;
};

bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream&, Student_info&);

#endif