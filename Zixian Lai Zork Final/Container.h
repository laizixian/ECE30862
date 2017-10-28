/*
 * Container.h
 *
 *  Created on: Dec 7, 2016
 *      Author: lai61
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml.hpp"
#include <string>
#include <list>
#include <vector>
#include "Triggers.h"
using namespace rapidxml;

namespace std {

class Container{
private:
	string name;
	string status;
	string description;
	bool accept_flag;
	vector<string> accept;
	vector<string> item;
	vector<Triggers*> trigger;
	bool opened;

public:
	Container(xml_node<> *container);
	virtual ~Container();
	void print_container();
	string get_name();
	void add_item(string new_item);
	bool find_item(string find);
	void delete_item(string remove_item);
	void open();
	bool get_open();
	bool match_accept(string item_a);
	bool get_accept_flag();
	void set_status(string new_status);
	string get_status();
	vector<string> get_item();
	vector<Triggers*> get_trigger();

};

}

#endif /* CONTAINER_H_ */
