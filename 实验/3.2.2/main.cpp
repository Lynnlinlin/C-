#include <vector>
#include <iostream>

#include "analysis.h"
#include "Student_info.h"

using namespace std;

int main()
{
	vector<Student_info> mdid, mdidnt, fdid, fdidnt;
	Student_info student;

	while (read(cin, student))
	{
		if (is_male(student))
		{
			if (did_all_hw(student))
				mdid.push_back(student);
			else
				mdidnt.push_back(student);
		}
		else
		{
			if (did_all_hw(student))
				fdid.push_back(student);
			else
				fdidnt.push_back(student);
		}
	}

	//检查向量是否有包含数据
	if (mdid.empty())
	{
		cout << "No male student did all the homework!" << endl;
		system("pause");
		return 1;
	}
	if (mdidnt.empty())
	{
		cout << "Every male student did all the homework!" << endl;
		system("pause");
		return 1;
	}
	if (fdid.empty())
	{
		cout << "No female student did all the homework!" << endl;
		system("pause");
		return 1;
	}
	if (fdidnt.empty())
	{
		cout << "Every female student did all the homework!" << endl;
		system("pause");
		return 1;
	}

	//output
	//male
	write_analysis(cout, "male median", median_analysis, mdid, mdidnt);
	write_analysis(cout, "male average", average_analysis, mdid, mdidnt);
	write_analysis(cout, "male median of homweork turned in", optimistic_median_analysis, mdid, mdidnt);

	cout << endl;

	//female
	write_analysis(cout, "female median", median_analysis, fdid, fdidnt);
	write_analysis(cout, "female average", average_analysis, fdid, fdidnt);
	write_analysis(cout, "female median of homweork turned in", optimistic_median_analysis, fdid, fdidnt);

	system("pause");
	return 0;
}