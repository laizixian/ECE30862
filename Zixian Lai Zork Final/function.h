/*
 * function.h
 *
 *  Created on: Dec 10, 2016
 *      Author: lai61
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
//include the class
#include "Room.h"
#include "Item.h"
#include "Creature.h"
#include "Container.h"
//#include "rapidxml_iterators.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml.hpp"



using namespace std;
using namespace rapidxml;

void move(string user_input, Room* &current, vector<Room*> &Room_obj);
void open_exit(Room* &current, bool &END_FLAG);
void check_inventory(vector<string> &inventory);
void drop(string user_input, vector<string> &inventory, Room* &current);
void open(string user_input, Room* &current, vector<Container*> &Container_obj);
void put(string user_input, vector<string> &inventory, Room* &current, vector<Container*> &Container_obj);
void take(string user_input, vector<string> &inventory, Room* &current, vector<Container*> &Container_obj);
void read(string user_input, vector<string> &inventory, vector<Item*> &Item_obj);
void take_command(string user_input, vector<string> &inventory, Room* &current, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj, bool &END_FLAG);
void turn_on(string user_input, vector<string> &inventory, Room* &current, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj, bool &END_FLAG);
void help();
void Game_Over(bool &END_FLAG);
void Add(string make_action, vector<string> &inventory, Room* &current, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj, bool &END_FLAG);
void Delete(string make_action, vector<string> &inventory, Room* &current, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj, bool &END_FLAG);
void Update(string make_action, vector<string> &inventory, Room* &current, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj, bool &END_FLAG);
void attack(string user_input, vector<string> &inventory, Room* &current, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj, bool &END_FLAG);
void check_trigger(string user_input, vector<string> &inventory, Room* &current, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj, bool &END_FLAG, bool &overridden, bool no_command);
bool check_object_status(string cond_obj, string cond_status, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj);
bool check_owner_status(string cond_own, string cond_obj, string cond_has, vector<string> &inventory, vector<Room*> &Room_obj, vector<Container*> &Container_obj);
void each_trigger(Triggers* one_trigger, string user_input, vector<string> &inventory, Room* &current, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj, bool &END_FLAG, bool &overridden, bool no_command);

#endif /* FUNCTION_H_ */
