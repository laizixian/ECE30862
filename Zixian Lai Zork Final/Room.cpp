/*
 * Room.cpp
 *
 *  Created on: Dec 7, 2016
 *      Author: lai61
 */

#include "Room.h"
#include <iostream>

namespace std {


Room::Room(rapidxml::xml_node<> *room, int i)
{
	border_num = 0;
	room_number = i;
	xml_node<>* elements = room->first_node();
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
		if(string(elements->name()) == "type")
		{
			type = string(elements->value());
		}
		if(string(elements->name()) == "description")
		{
			description = string(elements->value());
		}
		if(string(elements->name()) == "border")
		{
			border_num++;
			Border* new_border = new Border();
			xml_node<>* sub_element = elements->first_node();
			while(sub_element!= NULL)
			{
				if(string(sub_element->name()) == "name")
				{
					new_border->name = string(sub_element->value());

				}
				if(string(sub_element->name()) == "direction")
				{
					string temp = string(sub_element->value());
					if(temp == "north")
					{
						new_border->direction = "n";
					}
					if(temp == "east")
					{
						new_border->direction = "e";
					}
					if(temp == "west")
					{
						new_border->direction = "w";
					}
					if(temp == "south")
					{
						new_border->direction = "s";
					}
				}
				sub_element = sub_element->next_sibling();
			}
			room_border.push_back(new_border);
		}
		if(string(elements->name()) == "container")
		{
			container.push_back(string(elements->value()));
		}
		if(string(elements->name()) == "item")
		{
			item.push_back(string(elements->value()));
		}
		if(string(elements->name()) == "creature")
		{
			creature.push_back(string(elements->value()));
		}
		if(string(elements->name()) == "trigger")
		{
			Triggers *new_tigger = new Triggers(elements);
			trigger.push_back(new_tigger);
		}
		elements = elements->next_sibling();
	}
}

Room::~Room() {
	// TODO Auto-generated destructor stub
}

string Room::get_name()
{
	return name;
}
string Room::get_status()
{
	return status;
}
string Room::get_type()
{
	return type;
}

string Room::get_description()
{
	return description;
}
string Room::get_border_direction(int i)
{
	return room_border[i]->direction;
}
string Room::get_border_name(int i)
{
	return room_border[i]->name;
}
int Room::get_border_num()
{
	return border_num;
}
string Room::get_container(int i)
{
	return container[i];
}
string Room::get_item(int i)
{
	return item[i];
}
string Room::get_creature(int i)
{
	return creature[i];
}
vector<string> Room::get_creature()
{
	return creature;
}
vector<Triggers*> Room::get_trigger()
{
	return trigger;
}
void Room::print_room()
{
	cout << "room------------------" <<endl;
	cout << "name:" << name <<endl;
	cout << "status:" << status <<endl;
	cout << "type:" << type <<endl;
	cout << "description:" << description <<endl;
	for(unsigned int i = 0; i < room_border.size(); i++)
	{
		cout << "the border of the room" <<endl;
		cout << "name:" << room_border[i]->name <<endl;
		cout << "direction:" << room_border[i]->direction <<endl;
	}
	cout << "container:" <<endl;
	for(unsigned int i = 0; i < container.size(); i++)
	{
		cout << container[i] <<endl;
	}
	cout << "item:" <<endl;
	for(unsigned int i = 0; i < item.size(); i++)
	{
		cout << item[i] <<endl;
	}
	cout << "creature:" <<endl;
	for(unsigned int i = 0; i < creature.size(); i++)
	{
		cout << creature[i] <<endl;
	}

	for(unsigned int i = 0; i < trigger.size(); i++)
	{
		trigger[i]->print_trigger();
	}
}
int Room::get_border_number()
{
	return border_num;
}
bool Room::find_next_room(string input, int i)
{
	if(room_border[i]->direction == input)
	{
		return true;
	}
	return false;
}
void Room::add_item(string new_item)
{
	item.push_back(new_item);
}
int Room::get_container_size()
{
	return container.size();
}
int Room::get_item_size()
{
	return item.size();
}
int Room::get_creature_size()
{
	return creature.size();
}
void Room::delete_item(string delete_item)
{
	bool have_item = false;
	int index;
	for(unsigned int i = 0; i < item.size(); i++)
	{
		if(delete_item == item[i])
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
void Room::add_Container(string new_container)
{
	container.push_back(new_container);
}

void Room::add_Creature(string new_creature)
{
	creature.push_back(new_creature);
}

void Room::delete_border(string old_border)
{
	for(unsigned int i = 0; i < room_border.size(); i++)
	{
		if(old_border == room_border[i]->name)
		{
			room_border.erase(room_border.begin()+i);
			break;
		}
	}
}

void Room::delete_container(string delete_container)
{
	bool have_container = false;
	int index;
	for(unsigned int i = 0; i < container.size(); i++)
	{
		if(delete_container == container[i])
		{
			index = i;
			have_container = true;
		}
	}
	if(have_container == true)
	{
		container.erase(container.begin() + index);
	}
}

void Room::delete_creature(string old_creature)
{
	bool have_creature = false;
	int index;
	for(unsigned int i = 0; i < creature.size(); i++)
	{
		if(old_creature == creature[i])
		{
			index = i;
			have_creature = true;
		}
	}
	if(have_creature == true)
	{
		creature.erase(creature.begin() + index);
	}
}

void Room::set_status(string new_status)
{
	status = new_status;
}


}


