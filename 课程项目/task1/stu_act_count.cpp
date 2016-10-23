#include <stdio.h>
#include <iostream>
#include <map>
#include "exprtk.hpp"
#include "instructions.h"
using namespace std;

extern double FOOD_WEIGHT;
extern double FOOD_COST;
extern double STUDY_WEIGHT;
extern double STUDY_KNOWLEDGE;
extern double WORK_MONEY;
extern double WORK_WEIGHT;

//学生状态变化公式：
extern string WEIGHT_INC;
extern string MONEY_INC;
extern string KNOWLEDGE_INC;
extern string CHARM_INC;

double express_count(double sum_eat, double sum_study, double sum_work, string express_string)
{
	typedef exprtk::symbol_table<double> symbol_table_t;
	typedef exprtk::expression<double>     expression_t;
	typedef exprtk::parser<double>             parser_t;

	string expression_string = express_string;

	symbol_table_t symbol_table;
	symbol_table.add_variable("FOOD_TAKEN", sum_eat);
	symbol_table.add_variable("FOOD_WEIGHT", FOOD_WEIGHT);
	symbol_table.add_variable("STUDY_TIME", sum_study);
	symbol_table.add_variable("STUDY_WEIGHT", STUDY_WEIGHT);
	symbol_table.add_variable("WORK_TIME", sum_work);
	symbol_table.add_variable("WORK_WEIGHT", WORK_WEIGHT);
	symbol_table.add_variable("STUDY_KNOWLEDGE", STUDY_KNOWLEDGE);
	symbol_table.add_variable("WORK_MONEY", WORK_MONEY);
	symbol_table.add_variable("FOOD_COST", FOOD_COST);
	symbol_table.add_constants();

	expression_t expression;
	expression.register_symbol_table(symbol_table);

	parser_t parser;
	parser.compile(expression_string, expression);

	return expression.value();
}

double charm_count(double wei_inc, double mon_inc, double kno_inc, string express_string)
{
	typedef exprtk::symbol_table<double> symbol_table_t;
	typedef exprtk::expression<double>     expression_t;
	typedef exprtk::parser<double>             parser_t;

	string expression_string = express_string;

	symbol_table_t symbol_table;
	symbol_table.add_variable("FOOD_WEIGHT", FOOD_WEIGHT);
	symbol_table.add_variable("STUDY_WEIGHT", STUDY_WEIGHT);
	symbol_table.add_variable("WORK_WEIGHT", WORK_WEIGHT);
	symbol_table.add_variable("STUDY_KNOWLEDGE", STUDY_KNOWLEDGE);
	symbol_table.add_variable("WORK_MONEY", WORK_MONEY);
	symbol_table.add_variable("FOOD_COST", FOOD_COST);
	symbol_table.add_variable("WEIGHT_INC", wei_inc);
	symbol_table.add_variable("MONEY_INC", mon_inc);
	symbol_table.add_variable("KNOWLEDGE_INC", kno_inc);
	symbol_table.add_constants();

	expression_t expression;
	expression.register_symbol_table(symbol_table);

	parser_t parser;
	parser.compile(expression_string, expression);

	return expression.value();
}

//利用不同公式计算每个学生的体重、金钱、知识、魅力
void stu_act_count(double sum_eat, double sum_study, double sum_work, map<std::string, Student>& m_Student ,string name)
{
	double wei_inc = express_count(sum_eat, sum_study, sum_work, WEIGHT_INC);
	double mon_inc = express_count(sum_eat, sum_study, sum_work, MONEY_INC);
	double kno_inc = express_count(sum_eat, sum_study, sum_work, KNOWLEDGE_INC);
	m_Student[name].weight += wei_inc;
	m_Student[name].money += mon_inc;
	m_Student[name].knowledge += kno_inc;
	if (m_Student[name].charm <= 100)
		m_Student[name].charm += charm_count(wei_inc, mon_inc, kno_inc, CHARM_INC);
}
