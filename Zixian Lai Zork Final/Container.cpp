/*
 * Container.cpp
 *
 *  Created on: Dec 7, 2016
 *      Author: lai61
 */

#include "Container.h"
#include <iostream>

namespace std {

Container::Container(rapidxml::xml_node<> *container) {
	// TODO Auto-generated constructor stub
	accept_flag = false;
	opened = false;

	xml_node<>* elements = container->first_node();
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
		if(string(elements->name()) == "accept")
		{
			accept_flag = true;
			string temp = string(elements->value());
			accept.push_back(temp);
		}
		if(string(elements->name()) == "item")
		{
			string temp = string(elements->value());
			item.push_back(temp);
		}
		if(string(elements->name()) == "trigger")
		{
			Triggers *new_tigger = new Triggers(elements);
			trigger.push_back(new_tigger);
		}
		elements = elements->next_sibling();

	}

}

Container::~Container() {
	// TODO Auto-generated destructor stub
}
void Container::print_container()
{
	cout << "container------------------" <<endl;
	cout << "name:" << name <<endl;
	cout << "status:" << status <<endl;
	cout << "description:" << description <<endl;
	cout << "accept:" << endl;
	for(unsigned int i = 0; i < accept.size(); i++)
	{
		cout << accept[i] <<endl;
	}
	cout << "item:" <<endl;
	for(unsigned int i = 0; i < item.size(); i++)
	{
		cout << item[i] <<endl;
	}
	for(unsigned int i = 0; i < trigger.size(); i++)
	{
		trigger[i]->print_trigger();
	}
}
string Container::get_name()
{
	return name;
}
void Container::add_item(string new_item)
{
	item.push_back(new_item);
}
bool Container::find_item(string find)
{
	bool found = false;
	for(unsigned int i = 0; i < item.size(); i++)
	{
		if(item[i] == find)
		{
			found = true;
			break;
		}
	}
	return found;
}
void Container::delete_item(string remove_item)
{
	bool have_item = false;
	int index;
	for(unsigned int i = 0; i < item.size(); i++)
	{
		if(remove_item == item[i])
		{
			index = i;
			have_item = true;
		}
	}
	if(have_item == true)
	{
		item.erase(item.begin() + index);
	}
}
void Container::open()
{
	opened = true;
	if(item.size() == 0)
	{
		cout << name << " is empty" <<endl;
	}
	else
	{
		cout << name << " contains "<<item[0];
		for(unsigned int i = 1; i < item.size(); i++)
		{
			cout << ", " << item[i];
		}
		cout << endl;
	}
}
bool Container::get_open()
{
	return opened;
}
bool Container::match_accept(string item_a)
{
	bool can_in = false;
	for(unsigned int i = 0; i < accept.size(); i++)
	{
		if(item_a == accept[i])
		{
			can_in = true;
			break;
		}
	}
	return can_in;
}
bool Container::get_accept_flag()
{
	return accept_flag;
}
void Container::set_status(string new_status)
{
	status = new_status;
}
string Container::get_status()
{
	return status;
}
vector<string> Container::get_item()
{
	return item;
}

vector<Triggers*> Container::get_trigger()
{
	return trigger;
}

}
