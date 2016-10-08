#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>//try catch
#include <stdexcept> //定义了domain_error，定义常见异常类
#include <string>
#include <vector>
#include "grade.h"
#include "Student_info.h"

using std::istream;
using std::cin;	
using std::setprecision;
using std::cout;
using std::sort;
using std::domain_error;
using std::streamsize;
using std::endl;
using std::string;
using std::max;
using std::vector;

int main()
{
	vector<Student_info> students;
	Student_info record;
	string::size_type maxlen = 0;

	//读入并存储所有学生的数据
	//不变式：students包含所有的学生记录
	//maxlen包含students中最长的姓名
	while (read(cin, record))
	{
		//找出最长的姓名长度
		maxlen = max(maxlen, record.name.size());
		students.push_back(record);
	}
	//按字母顺序排序学生记录
	sort(students.begin(), students.end(), compare);

	//输出姓名和成绩
	for (vector<Student_info>::size_type i = 0; i != students.size(); ++i)
	{
		//输出姓名，将姓名填充至maxlen+1个字符长度
		cout << students[i].name << string(maxlen + 1 - students[i].name.size(), ' ');

		//计算并输出成绩
		try
		{
			double final_grade = grade(students[i]);
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade << setprecision(prec);
		}
		catch (domain_error e)
		{
			cout << e.what();//返回一个值，报告了问题的所在
		}
		cout << endl;
	}

	system("pause");
	return 0;
}

bool compare(const Student_info& x, const Student_info& y)
{
	return x.name < y.name;//做操作数比有操作数小
}

//从输入流中将家庭作业的成绩读入到一个vector<double>中
istream& read_hw(istream& in, vector<double>& hw)
{
	if (in)
	{
		//清除原先的内容
		hw.clear();

		//读家庭作业成绩
		double x;
		while (in >> x)
			hw.push_back(x);
		//清楚流以使输入动作对下一个学生有效
		in.clear();
		in.ignore();
	}
	return in;
}

istream& read(istream& is, Student_info& s)
{
	//读入并存储学生的姓名以及期中、期末考试成绩
	is >> s.name >> s.midterm >> s.final;

	read_hw(is, s.homework);
	return is;
}


//根据学生的期中考试、期末考试成绩以及家庭作业成绩来计算总成绩
double grade(double midterm, double final, double homework)
{
	return 0.2*midterm + 0.4*final + 0.4*homework;
}

//计算一个vector<double>类型的变量中值
//需要注意的是，调用函数时整个vector参数都会被复制
double median(vector<double> vec)
{
	typedef vector<double>::size_type vec_sz;

	vec_sz size = vec.size();
	if (size == 0)
		throw domain_error("median of an empty vector");

	sort(vec.begin(), vec.end());

	vec_sz mid = size / 2;

	return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

double grade(double midterm, double final, const vector<double>& hw)
{
	if (hw.size() == 0)
		throw domain_error("student has done no homework");
	return grade(midterm, final, median(hw));
}

double grade(const Student_info& s)
{
	return grade(s.midterm, s.final, s.homework);
}