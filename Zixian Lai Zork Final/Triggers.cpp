/*
 * Triggers.cpp
 *
 *  Created on: Dec 7, 2016
 *      Author: lai61
 */

#include "Triggers.h"
#include <iostream>

namespace std {

Triggers::Triggers(xml_node<> *trigger) {
	// TODO Auto-generated constructor stub
	type = "single";
	used = false;
	conditions = 0;
	command_flag = false;
	print_flag = false;
	action_flag = false;

	xml_node<>* elements = trigger->first_node();
	while(elements!=NULL)
	{
		if(string(elements->name()) == "condition")
		{
			string object_v, status_v, has_v, owner_v;

			xml_node<>* sub_element = elements->first_node();
			while(sub_element!=NULL)
			{
				if(string(sub_element->name()) == "object")
				{
					object_v = sub_element->value();
					conditions++;
				}
				if(string(sub_element->name()) == "status")
				{
					status_v = sub_element->value();
					conditions++;
				}
				if(string(sub_element->name()) == "has")
				{
					has_v = sub_element->value();
					conditions++;
				}
				if(string(sub_element->name()) == "owner")
				{
					owner_v = sub_element->value();
					conditions++;
				}
				sub_element = sub_element->next_sibling();
			}
			if(conditions == 2)
			{
				status.object = object_v;
				status.status = status_v;
			}
			if(conditions == 3)
			{
				owner.object = object_v;
				owner.has = has_v;
				owner.owner = owner_v;
			}
		}
		if(string(elements->name()) == "type")
		{
			type = elements->value();
		}
		if(string(elements->name()) == "command")
		{
			command_flag = true;
			command = elements->value();
		}
		if(string(elements->name()) == "print")
		{
			print_flag = true;
			print = elements->value();
		}
		if(string(elements->name()) == "action")
		{
			action_flag = true;
			string temp = elements->value();
			action.push_back(temp);
		}
		elements = elements->next_sibling();
	}



}

Triggers::~Triggers() {
	// TODO Auto-generated destructor stub
}
void Triggers::print_trigger()
{
	cout << "trigger---------------" << endl;
	cout << "type:" << type <<endl;
	if(conditions == 2)
	{
		cout << "object:" << status.object <<endl;
		cout << "status:" << status.status <<endl;
	}
	if(conditions == 3)
	{
		cout << "owner:" << owner.owner <<endl;
		cout << "object:" << owner.object <<endl;
		cout << "has:" << owner.has <<endl;
	}
	cout << "command:" << command <<endl;
	cout << "print:" << print <<endl;
	cout << "action:" << endl;
	for(unsigned int i = 0; i < action.size(); i++)
	{
		cout << action[i] <<endl;
	}
}
bool Triggers::get_command_flag()
{
	return command_flag;
}
string Triggers::get_command()
{
	return command;
}

int Triggers::get_condition()
{
	return conditions;
}

vector<string> Triggers::get_action()
{
	return action;
}

Status Triggers::get_status()
{
	return status;
}

bool Triggers::get_used()
{
	return used;
}

Owner Triggers::get_owner()
{
	return owner;
}

void Triggers::set_used()
{
	used = true;
}
string Triggers::get_type()
{
	return type;
}
string Triggers::get_print()
{
	return print;
}

}
