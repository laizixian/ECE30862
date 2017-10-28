/*
 * Triggers.h
 *
 *  Created on: Dec 7, 2016
 *      Author: lai61
 */

#ifndef TRIGGERS_H_
#define TRIGGERS_H_
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml.hpp"
#include <string>
#include <vector>

using namespace rapidxml;
namespace std {
typedef struct _owner{
	string object;
	string has;
	string owner;
}Owner;
typedef struct _status{
	string object;
	string status;
}Status;

class Triggers {
private:
	string type;
	bool used;
	int conditions;
	string command;
	bool command_flag;
	string print;
	bool print_flag;
	vector<string> action;
	bool action_flag;
	Owner owner;
	Status status;


public:
	Triggers(xml_node<> *trigger);
	virtual ~Triggers();
	void print_trigger();
	bool get_command_flag();
	string get_command();
	int get_condition();
	vector<string> get_action();
	Status get_status();
	bool get_used();
	Owner get_owner();
	string get_type();
	void set_used();
	string get_print();
};

}

#endif /* TRIGGERS_H_ */
