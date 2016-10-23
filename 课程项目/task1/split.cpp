#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <ctype.h>
#include <algorithm>
using namespace std;

//�õ���ѧ�����֡��Ա𣨷���a_stu_info�У� �õ�ѧ�������ŷ��ţ�����a_stu_bed_info�У�
void split(const string& a_str, vector<string>& a_stu_info, vector<int>& a_stu_bed_info)
{
	const regex pattern("([^\\s]+)[\\s]+([^\\s]+)[\\s]+(\\d+)\\-(\\d+)[\\s]*");
	match_results<string::const_iterator> result;

	bool valid = regex_match(a_str, result, pattern);
	if (valid)
	{
		//���ѧ�����֡��Ա�
		a_stu_info.push_back(result[1]);
		a_stu_info.push_back(result[2]);

		//��ѧ���������������ת��Ϊ�ַ�����
		string floor_str = result[3];
		string room_str = result[4];

		//��ѧ���������������ת��Ϊint
		a_stu_bed_info.push_back(atoi(floor_str.c_str()) - 1);//���ڴ洢ʱ��0��ʼ�����Ҫ��һ
		a_stu_bed_info.push_back(atoi(room_str.c_str()) - 1);
	}
	else
		cout << "dispatch error" << endl;
}