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
	
	//�ж��Ƿ����������ļ���
	if (argc == 4)
	{
		//���ļ�
		ifstream config;
		config.open(argv[1]);

		ifstream dispatch;
		dispatch.open(argv[2]);

		ifstream instruc;
		instruc.open(argv[3]);
		
		if (config&&dispatch&&instruc)
		{
			//��һ��������г�ʼ������ʱѧ��û��ס
			init(dorm, config);

			//��ѧ����ס������г�ʼ��
			init_dispatch(dorm, m_Student, dispatch);
			cout << string(60, '*') << endl;

			//ƥ���Ӧ���ִ��
			instructions(dorm, m_Student, instruc);
		}
		else
			cout << "file open error." << endl;

		//�ر��ļ�
		config.close();
		dispatch.close();
		instruc.close();
	}
	else
		cout << "please input three valid filename" << endl;

	system("pause");
	return 0;
}