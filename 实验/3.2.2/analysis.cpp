#include <stdexcept>
#include <iterator>
#include <numeric>//accumulate
#include <vector>
#include <algorithm>
#include <iostream>

#include "grade.h"
#include "Student_info.h"
#include "median.h"

using std::accumulate;           using std::back_inserter;
using std::domain_error;         using std::endl;
using std::ostream;              using std::remove_copy;
using std::string;               using std::transform;
using std::vector;

double grade_aux(const Student_info& s)
{
	try {
		return grade(s);
	}
	catch (domain_error) {
		return grade(s.midterm, s.final, 0);
	}
}

double median_analysis(const vector<Student_info>& students)
{
	vector<double> grades;
	transform(students.begin(), students.end(),
		back_inserter(grades), grade_aux);
	return median(grades);
}

void write_analysis(ostream& out, const string& name,
	double analysis(const vector<Student_info>&),
	const vector<Student_info>& did,
	const vector<Student_info>& didnt)
{
	out << name << ":median(did) = " << analysis(did) <<
				 ",median(didnt) = " << analysis(didnt) << endl;
}

//average_analsis 函数使用家庭作业的平均成绩而不是中值成绩计算学生的总成绩
double average(const vector<double>& v)
{
	return accumulate(v.begin(), v.end(), 0.0) / v.size();
	//注意这里要用0.0使得求和结果师浮点数
}

double average_grade(const Student_info& s)
{
	return grade(s.midterm, s.final, average(s.homework));
}

//与median_analysis不同在于它的名称以及它用average_grade代替grade_aux
double average_analysis(const vector<Student_info>& students)
{
	vector<double> grades;

	transform(students.begin(), students.end(),
			back_inserter(grades), average_grade);
	return median(grades);
}

//假设学生上交的家庭作业数量对他们的家庭作业成绩并不会产生影响
//计算每个学生提交的家庭作业的中值成绩，将这个计算称为optimistic中值
//以下函数计算中值
double optimistic_median(const Student_info& s)
{
	vector<double> nonzero;
	remove_copy(s.homework.begin(), s.homework.end(), back_inserter(nonzero), 0);
	//库会提供很多算法的“赋值”版本
	//remove_copy算法假设在目的地有足够的空间用于保存全部被复制的元素

	if (nonzero.empty())
		return grade(s.midterm, s.final, 0);
	else
		return grade(s.midterm, s.final, median(nonzero));
}

double optimistic_median_analysis(const vector<Student_info>& students)
{
	vector<double> grades;

	transform(students.begin(), students.end(),
		back_inserter(grades), optimistic_median);
	return median(grades);
}