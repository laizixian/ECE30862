/*
 * Item.cpp
 *
 *  Created on: Dec 7, 2016
 *      Author: lai61
 */

#include "Item.h"
#include <iostream>

namespace std {

Item::Item(rapidxml::xml_node<> *item) {
	// TODO Auto-generated constructor stub
	xml_node<>* elements = item->first_node();
	turnon_flag = false;
	while(elements != NULL)
	{
		if(string(elements->name()) == "name")
		{
			name = string(elements->value());
		}
		if(string(elements->name()) == "status")
		{
			status = string(elements->value());
		}
		if(string(elements->name()) == "description")
		{
			description = string(elements->value());
		}
		if(string(elements->name()) == "writing")
		{
			writing = string(elements->value());
		}
		if(string(elements->name()) == "turnon")
		{
			turnon_flag = true;
			xml_node<>* sub_element = elements->first_node();
			while(sub_element!= NULL)
			{
				if(string(sub_element->name()) == "print")
				{
					turnon.print = string(sub_element->value());
				}
				if(string(sub_element->name()) == "action")
				{
					turnon.action = string(sub_element->value());
				}
				sub_element = sub_element->next_sibling();
			}
		}
		if(string(elements->name()) == "trigger")
		{
			Triggers *new_tigger = new Triggers(elements);
			trigger.push_back(new_tigger);
		}
		elements = elements->next_sibling();
	}

}

Item::~Item() {
	// TODO Auto-generated destructor stub
}
void Item::print_item()
{
	cout << "item------------------" <<endl;
	cout << "name:" << name <<endl;
	cout << "status:" << status <<endl;
	cout << "description:" << description <<endl;
	cout << "writing:" << writing <<endl;
	cout << "Turn on" <<endl;
	cout << "print:" << turnon.print <<endl;
	cout << "action:" << turnon.action <<endl;
	for(unsigned int i = 0; i < trigger.size(); i++)
	{
		trigger[i]->print_trigger();
	}
}
string Item::get_name()
{
	return name;
}
void Item::read_writing()
{
	if(writing.empty())
	{
		cout << "Nothing written" <<endl;
	}
	else
	{
		cout << writing <<endl;
	}
}
bool Item::get_turnon_flag()
{
	return turnon_flag;
}
Turnon Item::get_turn_on()
{
	return turnon;
}
void Item::set_status(string new_status)
{
	status = new_status;
}
string Item::get_status()
{
	return status;
}
vector<Triggers*> Item::get_trigger()
{
	return trigger;
}

}
