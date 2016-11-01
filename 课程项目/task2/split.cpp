#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <ctype.h>
#include <algorithm>
using namespace std;

//得到第学生名字、性别（放在a_stu_info中） 得到学生宿舍层号房号（放在a_stu_bed_info中）
void split(const string& a_str, vector<string>& a_stu_info, vector<int>& a_stu_bed_info)
{
	const regex pattern("([^\\s]+)[\\s]+([^\\s]+)[\\s]+(\\d+)\\-(\\d+)[\\s]*");
	match_results<string::const_iterator> result;

	bool valid = regex_match(a_str, result, pattern);
	if (valid)
	{
		//存放学生名字、性别
		a_stu_info.push_back(result[1]);
		a_stu_info.push_back(result[2]);

		//将学生宿舍层数、房号转换为字符串型
		string floor_str = result[3];
		string room_str = result[4];

		//将学生宿舍层数、房号转换为int
		a_stu_bed_info.push_back(atoi(floor_str.c_str()) - 1);//由于存储时由0开始，因而要减一
		a_stu_bed_info.push_back(atoi(room_str.c_str()) - 1);
	}
	else
		cout << "dispatch error" << endl;
}