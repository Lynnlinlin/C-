#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>//try catch
#include <stdexcept> //������domain_error�����峣���쳣��
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

	//���벢�洢����ѧ��������
	//����ʽ��students�������е�ѧ����¼
	//maxlen����students���������
	while (read(cin, record))
	{
		//�ҳ������������
		maxlen = max(maxlen, record.name.size());
		students.push_back(record);
	}
	//����ĸ˳������ѧ����¼
	sort(students.begin(), students.end(), compare);

	//��������ͳɼ�
	for (vector<Student_info>::size_type i = 0; i != students.size(); ++i)
	{
		//��������������������maxlen+1���ַ�����
		cout << students[i].name << string(maxlen + 1 - students[i].name.size(), ' ');

		//���㲢����ɼ�
		try
		{
			double final_grade = grade(students[i]);
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade << setprecision(prec);
		}
		catch (domain_error e)
		{
			cout << e.what();//����һ��ֵ�����������������
		}
		cout << endl;
	}

	system("pause");
	return 0;
}

bool compare(const Student_info& x, const Student_info& y)
{
	return x.name < y.name;//�����������в�����С
}

//���������н���ͥ��ҵ�ĳɼ����뵽һ��vector<double>��
istream& read_hw(istream& in, vector<double>& hw)
{
	if (in)
	{
		//���ԭ�ȵ�����
		hw.clear();

		//����ͥ��ҵ�ɼ�
		double x;
		while (in >> x)
			hw.push_back(x);
		//�������ʹ���붯������һ��ѧ����Ч
		in.clear();
		in.ignore();
	}
	return in;
}

istream& read(istream& is, Student_info& s)
{
	//���벢�洢ѧ���������Լ����С���ĩ���Գɼ�
	is >> s.name >> s.midterm >> s.final;

	read_hw(is, s.homework);
	return is;
}


//����ѧ�������п��ԡ���ĩ���Գɼ��Լ���ͥ��ҵ�ɼ��������ܳɼ�
double grade(double midterm, double final, double homework)
{
	return 0.2*midterm + 0.4*final + 0.4*homework;
}

//����һ��vector<double>���͵ı�����ֵ
//��Ҫע����ǣ����ú���ʱ����vector�������ᱻ����
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