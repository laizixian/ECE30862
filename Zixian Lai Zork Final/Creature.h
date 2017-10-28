/*
 * Creature.h
 *
 *  Created on: Dec 7, 2016
 *      Author: lai61
 */

#ifndef CREATURE_H_
#define CREATURE_H_
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml.hpp"
#include <string>
#include <list>
#include <vector>
#include "Triggers.h"
using namespace rapidxml;


namespace std {

typedef struct _attack{
	string print;
	vector<string> action;
	bool condition_flag;
	string object;
	string status;
}Attack;

class Creature{
private:
	string name;
	string status;
	string description;
	vector<string> vulnerability;
	Attack attack;
	vector<Triggers*> trigger;

public:
	Creature(xml_node<> *creature);
	virtual ~Creature();
	void print_creature();
	string get_name();
	void set_status(string new_status);
	bool get_vulnerability(string the_one);
	bool get_condition_flag();
	vector<string> get_action();
	string get_print();
	string get_cond_object();
	string get_cond_status();
	string get_status();
	vector<Triggers*> get_trigger();
};

}

#endif /* CREATURE_H_ */
