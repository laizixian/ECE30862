/*
 * Room.h
 *
 *  Created on: Dec 7, 2016
 *      Author: lai61
 */

#ifndef ROOM_H_
#define ROOM_H_

#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml.hpp"
#include <string>
#include <list>
#include <vector>
#include "Triggers.h"
using namespace rapidxml;

namespace std{
typedef struct _border{
	string direction;
	string name;
}Border;
}

namespace std {

class Room{
private:
	string name;
	string status;
	string type;
	string description;
	vector<Border*> room_border;
	vector<string> container;
	vector<string> item;
	vector<string> creature;
	vector<Triggers*> trigger;
	int border_num;
	int room_number;

public:
	//Room();
	Room(xml_node<> *room, int room_number);
	virtual ~Room();
	string get_name();
	string get_status();
	string get_type();
	string get_description();
	string get_border_direction(int i);
	string get_border_name(int i);
	int get_border_num();
	string get_container(int i);
	string get_item(int i);
	vector<string> get_creature();
	vector<Triggers*> get_trigger();
	void print_room();
	int get_border_number();
	bool find_next_room(string input, int i);
	void add_item(string new_item);
	int get_container_size();
	int get_item_size();
	void delete_item(string delete_item);
	void add_Container(string new_container);
	void add_Creature(string new_creature);
	void delete_border(string old_border);
	void delete_container(string old_container);
	void delete_creature(string old_creature);
	void set_status(string new_status);
	int get_creature_size();
	string get_creature(int i);

};

}

#endif /* ROOM_H_ */
