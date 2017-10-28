/*
 * Creature.cpp
 *
 *  Created on: Dec 7, 2016
 *      Author: lai61
 */

#include "Creature.h"
#include <iostream>

namespace std {

Creature::Creature(rapidxml::xml_node<> *creature) {
	// TODO Auto-generated constructor stub
	xml_node<>* elements = creature->first_node();
	attack.condition_flag = false;
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
		if(string(elements->name()) == "vulnerability")
		{
			string temp = string(elements->value());
			vulnerability.push_back(temp);
		}
		if(string(elements->name()) == "attack")
		{
			xml_node<>* sub_element = elements->first_node();
			while(sub_element!= NULL)
			{
				if(string(sub_element->name()) == "print")
				{
					attack.print = string(sub_element->value());
				}
				if(string(sub_element->name()) == "action")
				{
					string temp = string(sub_element->value());
					attack.action.push_back(temp);
				}
				if(string(sub_element->name()) == "condition")
				{
					attack.condition_flag = true;
					xml_node<>* sub_2nd_element = sub_element->first_node();
					while(sub_2nd_element != NULL)
					{
						if(string(sub_2nd_element->name()) == "object")
						{
							attack.object = string(sub_2nd_element->value());
						}
						if(string(sub_2nd_element->name()) == "status")
						{
							attack.status = string(sub_2nd_element->value());
						}
						sub_2nd_element = sub_2nd_element->next_sibling();
					}
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

Creature::~Creature() {
	// TODO Auto-generated destructor stub
}

void Creature::print_creature()
{
	cout << "creature------------------" <<endl;
	cout << "name:" << name <<endl;
	cout << "status:" << status <<endl;
	cout << "description:" << description <<endl;
	cout << "vulnerability:" <<endl;
	for(unsigned int i = 0; i < vulnerability.size(); i++)
	{
		cout << vulnerability[i] <<endl;
	}
	cout << "Attack:" <<endl;
	cout << "print:" << attack.print <<endl;
	cout << "action:" <<endl;
	for(unsigned int i = 0; i < attack.action.size(); i++)
	{
		cout << attack.action[i] <<endl;
	}
	if(attack.condition_flag == true)
	{
		cout << "object:" << attack.object <<endl;
		cout << "status:" << attack.status <<endl;
	}
	for(unsigned int i = 0; i < trigger.size(); i++)
	{
		trigger[i]->print_trigger();
	}
}

string Creature::get_name()
{
	return name;
}

void Creature::set_status(string new_status)
{
	status = new_status;
}

bool Creature::get_vulnerability(string the_one)
{
	bool match = false;
	for(unsigned int i = 0; i < vulnerability.size(); i++)
	{
		if(the_one == vulnerability[i])
		{
			match = true;
			break;
		}
	}
	return match;
}

bool Creature::get_condition_flag()
{
	return attack.condition_flag;
}

vector<string> Creature::get_action()
{
	return attack.action;
}

string Creature::get_print()
{
	return attack.print;
}

string Creature::get_cond_object()
{
	return attack.object;
}
string Creature::get_cond_status()
{
	return attack.status;
}
string Creature::get_status()
{
	return status;
}
vector<Triggers*> Creature:: get_trigger()
{
	return trigger;
}

}
