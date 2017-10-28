/*
 * Item.h
 *
 *  Created on: Dec 7, 2016
 *      Author: lai61
 */

#ifndef ITEM_H_
#define ITEM_H_
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml.hpp"
#include <string>
#include <list>
#include <vector>
#include "Triggers.h"

using namespace rapidxml;
namespace std {

typedef struct _turnon{
	string print;
	string action;
}Turnon;

class Item{
private:
	string name;
	string status;
	string description;
	string writing;
	Turnon turnon;
	bool turnon_flag;
	vector<Triggers*> trigger;

public:
	Item(xml_node<> *item);
	virtual ~Item();
	void print_item();
	string get_name();
	void read_writing();
	bool get_turnon_flag();
	Turnon get_turn_on();
	void set_status(string new_status);
	string get_status();
	vector <Triggers*> get_trigger();

};

}

#endif /* ITEM_H_ */
