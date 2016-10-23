#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "dorm.h"
#include "students.h"
#include "split.h"
#include "instructions.h"
using namespace std;


int main(int argc, char *argv[])
{
	Dorm dorm;
	map<string, Student> m_Student;
	
	//判断是否输入三个文件名
	if (argc == 4)
	{
		//打开文件
		ifstream config;
		config.open(argv[1]);

		ifstream dispatch;
		dispatch.open(argv[2]);

		ifstream instruc;
		instruc.open(argv[3]);
		
		if (config&&dispatch&&instruc)
		{
			//对一栋宿舍进行初始化、此时学生没入住
			init(dorm, config);

			//对学生入住宿舍进行初始化
			init_dispatch(dorm, m_Student, dispatch);
			cout << string(60, '*') << endl;

			//匹配对应命令并执行
			instructions(dorm, m_Student, instruc);
		}
		else
			cout << "file open error." << endl;

		//关闭文件
		config.close();
		dispatch.close();
		instruc.close();
	}
	else
		cout << "please input three valid filename" << endl;

	system("pause");
	return 0;
}