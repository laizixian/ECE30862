//============================================================================
// Name        : Zork_final.cpp
// Author      : Zixian Lai
// Version     : 1.0
// Copyright   : my zork
// Description : The Zork game, Ansi-style
//============================================================================


#include "function.h"



using namespace std;
using namespace rapidxml;

void move(string user_input, Room* &current, vector<Room*> &Room_obj)
{
	int cur_border_size = current->get_border_number();
	string next_room;
	bool can_go = false;
	int index = 0;
	for(int i = 0; i < cur_border_size; i++)
	{
		if(current->find_next_room(user_input, i))
		{
			can_go = true;
			next_room = current->get_border_name(i);
		}
	}
	if(can_go)
	{
		for(unsigned int i = 0; i < Room_obj.size(); i++)
		{
			if(next_room == Room_obj[i]->get_name())
			{
				index = i;
				break;
			}
		}
		current = Room_obj[index];
		cout << current->get_description() <<endl;
	}
	else
	{
		cout << "Can't go that way" <<endl;
	}
}

void open_exit(Room* &current, bool &END_FLAG)
{
	if(current->get_type() == "exit")
	{
		cout << "Game Over" <<endl;
		END_FLAG = true;
	}
	else
	{
		cout << "ERROR" <<endl;
	}
}

void check_inventory(vector<string> &inventory)
{
	if(inventory.size() == 0)
	{
		cout << "Inventory: empty" <<endl;
	}
	else if(inventory.size() == 1)
	{
		cout << "Inventory: " << inventory[0] <<endl;
	}
	else
	{
		cout << "Inventory: "<< inventory[0];
		for(unsigned int i = 1; i < inventory.size(); i++)
		{
			cout << ", " << inventory[i];
		}
		cout << endl;
	}
}

void drop(string user_input, vector<string> &inventory, Room* &current)
{
	user_input.erase(0,5);
	bool found = false;
	int index;
	for(unsigned int i=0; i < inventory.size(); i++)
	{
		if(inventory[i] == user_input)
		{
			found = true;
			index = i;
			break;
		}
	}
	if(found == false)
	{
		cout << "Don't have the item" <<endl;
	}
	if(found == true)
	{
		cout << inventory[index] << " dropped" <<endl;
		current->add_item(inventory[index]);
		inventory.erase(inventory.begin() + index);
	}
}

void open(string user_input, Room* &current, vector<Container*> &Container_obj)
{
	user_input.erase(0,5);
	bool container_room = false;
	for(int i = 0; i < current->get_container_size(); i++)
	{
		if(current->get_container(i) == user_input)
		{
			container_room = true;
			break;
		}
	}
	if(container_room == true)
	{
		for(unsigned int i = 0; i < Container_obj.size(); i++)
		{
			if(Container_obj[i]->get_name() == user_input)
			{
				if(Container_obj[i]->get_accept_flag() == true)
				{
					cout << Container_obj[i]->get_name() << " can't be opened" <<endl;
					break;
				}
				else
				{
					Container_obj[i]->open();
					break;
				}
			}
		}
	}

	if(container_room == false)
	{
		cout << "Can't find " << user_input <<endl;
	}

}

void put(string user_input, vector<string> &inventory, Room* &current, vector<Container*> &Container_obj)
{
	bool have_item = false;
	bool room_container = false;
	user_input.erase(0,4);
	int gap = user_input.find(" ");
	int index1, index2;
	string put_item = user_input.substr(0, gap);
	string put_in = user_input.erase(0, gap + 4);

	for(unsigned int i = 0; i < inventory.size(); i++)
	{
		if(inventory[i] == put_item)
		{
			index1 = i;
			have_item = true;
			break;
		}
	}
	for(int i = 0; i < current->get_container_size(); i++)
	{
		if(current->get_container(i) == put_in)
		{
			room_container = true;
			break;
		}
	}
	if(room_container == true)
	{
		for(unsigned int i = 0; i < Container_obj.size(); i++)
		{
			if(Container_obj[i]->get_name() == put_in)
			{
				index2 = i;
				break;
			}
		}
	}

	if(have_item == false)
	{
		cout << "Don't have " << put_item << " in inventory" <<endl;
	}
	if(room_container == false)
	{
		cout << "Don't have " << put_in << " in the room" <<endl;
	}
	if(room_container == true && have_item == true)
	{
		//bool container_accept = false;
		if(Container_obj[index2]->get_accept_flag() == false)
		{
			if(Container_obj[index2]->get_open() == true)
			{
				Container_obj[index2]->add_item(put_item);
				inventory.erase(inventory.begin() + index1);
				cout << "Item " << put_item << " added to "<<put_in<<endl;
			}
			else if(Container_obj[index2]->get_open() == false)
			{
				cout << put_in << " is closed" <<endl;
			}
		}
		else if(Container_obj[index2]->get_accept_flag() == true)
		{
			if(Container_obj[index2]->match_accept(put_item) == true)
			{
				Container_obj[index2]->add_item(put_item);
				inventory.erase(inventory.begin() + index1);
				cout << "Item " << put_item << " added to "<<put_in<<endl;
			}
			else if(Container_obj[index2]->match_accept(put_item) == false)
			{
				cout << put_in << " does not accept " << put_item <<endl;
			}
		}
	}
}

void take(string user_input, vector<string> &inventory, Room* &current, vector<Container*> &Container_obj)
{
	user_input.erase(0,5);
	bool room_item = false;
	bool container_item = false;
	int index1, index2;
	for(int i = 0; i < current->get_item_size(); i++)
	{
		if(current->get_item(i) == user_input)
		{
			index1 = i;
			room_item = true;
			break;
		}
	}
	for(int i = 0; i < current->get_container_size(); i++)
	{
		string temp = current->get_container(i);
		for(unsigned int j = 0; j < Container_obj.size(); j++)
		{
			if(temp == Container_obj[j]->get_name())
			{
				container_item = Container_obj[j]->find_item(user_input);
				if(container_item == true)
				{
					index2 = j;
					break;
				}
			}
		}
		if(container_item == true)
		{
			break;
		}
	}
	if(room_item == true)
	{
		cout << "Item " << user_input << " added to inventory" <<endl;
		current->delete_item(user_input);
		inventory.push_back(user_input);
	}
	else if(container_item == true && Container_obj[index2]->get_accept_flag() == true)
	{
		cout << "Item " << user_input << " added to inventory" <<endl;
		Container_obj[index2]->delete_item(user_input);
		inventory.push_back(user_input);
	}
	else if(container_item == true && Container_obj[index2]->get_open() == true)
	{
		cout << "Item " << user_input << " added to inventory" <<endl;
		Container_obj[index2]->delete_item(user_input);
		inventory.push_back(user_input);
	}
	else
	{
		cout << "Can't find " << user_input <<endl;
	}
}

void read(string user_input, vector<string> &inventory, vector<Item*> &Item_obj)
{
	user_input.erase(0,5);
	bool in_inventory = false;
	for(unsigned int i = 0; i < inventory.size(); i++)
	{
		if(inventory[i] == user_input)
		{
			in_inventory = true;
			break;
		}
	}
	if(in_inventory == false)
	{
		cout << user_input << " does not exist in inventory" <<endl;
	}
	if(in_inventory == true)
	{
		for(unsigned int i = 0; i < Item_obj.size(); i++)
		{
			if(user_input == Item_obj[i]->get_name())
			{
				Item_obj[i]->read_writing();
				break;
			}
		}
	}
}
void Game_Over(bool &END_FLAG)
{
	cout << "Victory!" << endl;
	END_FLAG = true;
}
void Add(string make_action, vector<string> &inventory, Room* &current, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj, bool &END_FLAG)
{
	make_action.erase(0,4);
	string object_name;
	string room_container;
	int gap = make_action.find(" to ");
	object_name = make_action.substr(0, gap);
	room_container = make_action.substr(gap + 4);
	bool to_room = false;
	bool to_container = false;
	int index1, index2;
	for(unsigned int i = 0; i < Room_obj.size(); i++)
	{
		if(room_container == Room_obj[i]->get_name())
		{
			to_room = true;
			index1 = i;
			break;
		}
	}
	for(unsigned int i = 0; i < Container_obj.size(); i++)
	{
		if(room_container == Container_obj[i]->get_name())
		{
			to_container = true;
			index2 = i;
			break;
		}
	}
	if(to_room == true)
	{
		for(unsigned int i = 0; i < Container_obj.size(); i++)
		{
			if(object_name == Container_obj[i]->get_name())
			{
				Room_obj[index1]->add_Container(object_name);
				break;
			}
		}
		for(unsigned int i = 0; i < Item_obj.size(); i++)
		{
			if(object_name == Item_obj[i]->get_name())
			{
				Room_obj[index1]->add_item(object_name);
				break;
			}
		}
		for(unsigned int i = 0; i < Creature_obj.size(); i++)
		{
			if(object_name == Creature_obj[i]->get_name())
			{
				Room_obj[index1]->add_Creature(object_name);
				break;
			}
		}

	}
	else if(to_container == true)
	{
		for(unsigned int i = 0; i < Item_obj.size(); i++)
		{
			if(object_name == Item_obj[i]->get_name())
			{
				Container_obj[index2]->add_item(object_name);
				break;
			}
		}
	}
	else
	{
		cout << "Can't find the room/container to Add" << endl;
	}


}
void Delete(string make_action, vector<string> &inventory, Room* &current, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj, bool &END_FLAG)
{
	make_action.erase(0,7);
	//if delete room
	for(unsigned int i = 0; i < Room_obj.size(); i++)
	{
		if(make_action == Room_obj[i]->get_name())
		{
			for(unsigned int j = 0; j < Room_obj.size(); j++)
			{
				Room_obj[j]->delete_border(make_action);
			}
			break;
		}
	}
	//if delete item
	for(unsigned int i = 0; i < Item_obj.size(); i++)
	{
		if(make_action == Item_obj[i]->get_name())
		{
			for(unsigned int j = 0; j < Room_obj.size(); j++)
			{
				Room_obj[j]->delete_item(make_action);
			}
			for(unsigned int k = 0; k < Container_obj.size(); k++)
			{
				Container_obj[k]->delete_item(make_action);
			}
			break;
		}
	}
	//if delete container
	for(unsigned int i = 0; i < Container_obj.size(); i++)
	{
		if(make_action == Container_obj[i]->get_name())
		{
			for(unsigned int j = 0; j < Room_obj.size(); j++)
			{
				Room_obj[j]->delete_container(make_action);
			}
			break;
		}
	}
	//if delete creature
	for(unsigned int i = 0; i < Creature_obj.size(); i++)
	{
		if(make_action == Creature_obj[i]->get_name())
		{
			for(unsigned int j = 0; j < Room_obj.size(); j++)
			{
				Room_obj[j]->delete_creature(make_action);
			}
		}
	}



}
void Update(string make_action, vector<string> &inventory, Room* &current, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj, bool &END_FLAG)
{
	make_action.erase(0,7);
	string object_name;
	string new_status;
	int gap = make_action.find(" to ");
	object_name = make_action.substr(0, gap);
	new_status = make_action.substr(gap + 4);
	for(unsigned int i = 0; i < Room_obj.size(); i++)
	{
		if(object_name == Room_obj[i]->get_name())
		{
			Room_obj[i]->set_status(new_status);
			break;
		}
	}
	for(unsigned int i = 0; i < Item_obj.size(); i++)
	{
		if(object_name == Item_obj[i]->get_name())
		{
			Item_obj[i]->set_status(new_status);
			break;
		}
	}
	for(unsigned int i = 0; i < Container_obj.size(); i++)
	{
		if(object_name == Container_obj[i]->get_name())
		{
			Container_obj[i]->set_status(new_status);
			break;
		}
	}
	for(unsigned int i = 0; i < Creature_obj.size(); i++)
	{
		if(object_name == Creature_obj[i]->get_name())
		{
			Creature_obj[i]->set_status(new_status);
			break;
		}
	}


}
void take_action(string make_action, vector<string> &inventory, Room* &current, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj, bool &END_FLAG)
{
	if(make_action.find("Add") != string::npos)
	{
		Add(make_action, inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG);
	}
	else if(make_action.find("Delete") != string::npos)
	{
		Delete(make_action, inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG);
	}
	else if(make_action.find("Update") != string::npos)
	{
		Update(make_action, inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG);
	}
	else if(make_action == ("Game Over"))
	{
		Game_Over(END_FLAG);
	}
	else
	{
		take_command(make_action, inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG);
	}
}
void turn_on(string user_input, vector<string> &inventory, Room* &current, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj, bool &END_FLAG)
{
	user_input.erase(0,8);
	bool in_inventory = false;
	for(unsigned int i = 0; i < inventory.size(); i++)
	{
		if(inventory[i] == user_input)
		{
			in_inventory = true;
			break;
		}
	}
	if(in_inventory == true)
	{
		for(unsigned int i = 0; i < Item_obj.size(); i++)
		{
			if(user_input == Item_obj[i]->get_name())
			{
				//Item_obj[i]->turn_item();
				if(Item_obj[i]->get_turnon_flag() == false)
				{
					cout << "You can't turn on " << Item_obj[i]->get_name() <<endl;
				}
				else if(Item_obj[i]->get_turnon_flag() == true)
				{
					cout << "You activate the " << Item_obj[i]->get_name() <<endl;
					cout << Item_obj[i]->get_turn_on().print <<endl;
					take_action(Item_obj[i]->get_turn_on().action, inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG);
				}
				break;
			}
		}
	}
	else if(in_inventory == false)
	{
		cout << "You don't have " << user_input << endl;
	}
}

void help()
{
	cout << "n, s, e, w – movement commands to put the player in a different room" <<endl;
	cout << "i – short for “inventory”, lists all items in the player’s inventory" <<endl;
	cout << "take (item) – changes item ownership from room or container to inventory " <<endl;
	cout << "open (container) – prints contents of container" <<endl;
	cout << "open exit – if the room is of type exit prints “Game Over” and gracefully ends the program" <<endl;
	cout << "read (item) – prints whatever is written on an object that the player has" <<endl;
	cout << "drop (item) – changes item ownership from inventory to present room" <<endl;
	cout << "put (item) in (container) – adds the item to the containers inventory" <<endl;
	cout << "turn on (item) – activates an item" <<endl;
	cout << "attack (creature) with (item) - attack the creature" <<endl;
}

void attack(string user_input, vector<string> &inventory, Room* &current, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj, bool &END_FLAG)
{
	string att_creature;
	string use_item;
	user_input.erase(0,7);
	int gap = user_input.find(" with ");
	att_creature = user_input.substr(0, gap);
	use_item = user_input.substr(gap + 6);
	bool creature_in_room = false;
	bool have_item = false;
	int index1;
	for(unsigned int i = 0; i < current->get_creature().size(); i++)
	{
		if(att_creature == (current->get_creature())[i])
		{
			creature_in_room = true;
			break;
		}
	}
	for(unsigned int i = 0; i < inventory.size(); i++)
	{
		if(use_item == inventory[i])
		{
			have_item = true;
			break;
		}
	}
	if(creature_in_room == false)
	{
		cout << "Don't have " << att_creature << " in the room" <<endl;
	}
	else if(have_item == false)
	{
		cout << "Don't have " << use_item << " int the inventory" <<endl;
	}
	else
	{
		cout << "You assault the " << att_creature << " with the " << use_item <<endl;
		bool check_V = false;
		for(unsigned int i = 0; i < Creature_obj.size(); i++)
		{
			if(att_creature == Creature_obj[i]->get_name())
			{
				index1 = i;
				check_V = Creature_obj[i]->get_vulnerability(use_item);
				break;
			}
		}
		if(check_V == true)
		{
			if(Creature_obj[index1]->get_condition_flag() == false)
			{
				for(unsigned int i = 0; i < Creature_obj[index1]->get_action().size(); i++)
				{
					take_action((Creature_obj[index1]->get_action())[i], inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG);
				}
				cout << Creature_obj[index1]->get_print() <<endl;
			}
			else
			{
				string cond_obj = Creature_obj[index1]->get_cond_object();
				string cond_status = Creature_obj[index1]->get_cond_status();
				// check the status of the object
				bool match = false;
				match = check_object_status(cond_obj, cond_status, Room_obj, Container_obj, Item_obj, Creature_obj);

				if(match == true)
				{
					for(unsigned int i = 0; i < Creature_obj[index1]->get_action().size(); i++)
					{
						take_action((Creature_obj[index1]->get_action())[i], inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG);
					}
					cout << Creature_obj[index1]->get_print() <<endl;
				}
				else
				{
					cout << "Condition isn't satisfied" << endl;
				}
			}
		}
		else
		{
			cout << use_item << " was ineffective" << endl;
		}
	}



}

bool check_object_status(string cond_obj, string cond_status, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj)
{
	bool match = false;
	for(unsigned int i = 0; i < Item_obj.size(); i++)
	{
		if(cond_obj == Item_obj[i]->get_name() && cond_status == Item_obj[i]->get_status())
		{
			match = true;
			break;
		}
	}
	for(unsigned int i = 0; i < Room_obj.size(); i++)
	{
		if(cond_obj == Room_obj[i]->get_name() && cond_status == Room_obj[i]->get_status())
		{
			match = true;
			break;
		}
	}
	for(unsigned int i = 0; i < Container_obj.size(); i++)
	{
		if(cond_obj == Container_obj[i]->get_name() && cond_status == Container_obj[i]->get_status())
		{
			match = true;
			break;
		}
	}
	for(unsigned int i = 0; i < Creature_obj.size(); i++)
	{
		if(cond_obj == Creature_obj[i]->get_name() && cond_status == Creature_obj[i]->get_status())
		{
			match = true;
			break;
		}
	}
	return match;
}

bool check_owner_status(string cond_own, string cond_obj, string cond_has, vector<string> &inventory, vector<Room*> &Room_obj, vector<Container*> &Container_obj)
{
	bool match = false;
	bool found = false;
	if(cond_own == "inventory")
	{
		for(unsigned int i = 0; i < inventory.size(); i++)
		{
			if(inventory[i] == cond_obj)
			{
				found = true;
				break;
			}
		}
	}
	for(unsigned int i = 0; i < Room_obj.size(); i++)
	{
		if(Room_obj[i]->get_name() == cond_own)
		{
			for(int j = 0; j < Room_obj[i]->get_container_size(); j++)
			{
				if(Room_obj[i]->get_container(j) == cond_obj)
				{
					found = true;
					break;
				}
			}
			for(int j = 0; j < Room_obj[i]->get_item_size(); j++)
			{
				if(Room_obj[i]->get_item(j) == cond_obj)
				{
					found = true;
					break;
				}
			}

			break;
		}
	}
	for(unsigned int i = 0; i < Container_obj.size(); i++)
	{
		if(Container_obj[i]->get_name() == cond_own)
		{
			for(unsigned int j = 0; j < Container_obj[i]->get_item().size(); j++)
			{
				if(Container_obj[i]->get_item()[j] == cond_obj)
				{
					found = true;
					break;
				}
			}
			break;
		}
	}
	if(found == true && cond_has == "yes")
	{
		match = true;
	}
	else if(found == false && cond_has == "no")
	{
		match = true;
	}
	return match;
}

void each_trigger(Triggers* one_trigger, string user_input, vector<string> &inventory, Room* &current, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj, bool &END_FLAG, bool &overridden, bool no_command)
{
	if(one_trigger->get_used() == false)
	{
		bool match = false;
		if(one_trigger->get_condition() == 2)
		{
			string cond_obj = one_trigger->get_status().object;
			string cond_status = one_trigger->get_status().status;
			match = check_object_status(cond_obj, cond_status, Room_obj, Container_obj, Item_obj, Creature_obj);
		}
		else if(one_trigger->get_condition() == 3)
		{
			string cond_obj = one_trigger->get_owner().object;
			string cond_has = one_trigger->get_owner().has;
			string cond_own = one_trigger->get_owner().owner;
			match = check_owner_status(cond_own, cond_obj, cond_has, inventory, Room_obj, Container_obj);
		}
		if((match == true) && (one_trigger->get_command_flag() == true) && (one_trigger->get_command() == user_input) && no_command == false)
		{
			overridden = true;
			if(one_trigger->get_type() == "single")
			{
				one_trigger->set_used();
			}
			cout << one_trigger->get_print() <<endl;
			for(unsigned int z = 0; z < one_trigger->get_action().size(); z++)
			{
				string temp = (one_trigger->get_action())[z];
				take_action(temp, inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG);
			}
			//cout << one_trigger->get_print() <<endl;
		}
		else if((match == true) && (one_trigger->get_command_flag() == false) && no_command == true)
		{
			if(one_trigger->get_type() == "single")
			{
				one_trigger->set_used();
			}
			cout << one_trigger->get_print() <<endl;
			for(unsigned int z = 0; z < one_trigger->get_action().size(); z++)
			{
				string temp = (one_trigger->get_action())[z];
				take_action(temp, inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG);
			}
			
		}
	}
}

void check_trigger(string user_input, vector<string> &inventory, Room* &current, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj, bool &END_FLAG, bool &overridden, bool no_command)
{
	//check the room trigger
	for(unsigned int i = 0; i < current->get_trigger().size(); i++)
	{
		each_trigger(current->get_trigger()[i], user_input, inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG, overridden, no_command);
	}
	//check the item trigger
	for(int i = 0; i < current->get_item_size(); i++)
	{
		for(unsigned int j = 0; j < Item_obj.size(); j++)
		{
			if(current->get_item(i) == Item_obj[j]->get_name())
			{
				for(unsigned int k = 0; k < Item_obj[j]->get_trigger().size(); k++)
				{
					each_trigger(Item_obj[j]->get_trigger()[k], user_input, inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG, overridden, no_command);
				}
				break;
			}
		}
	}
	//check container trigger
	for(int i = 0; i < current->get_container_size(); i++)
	{
		for(unsigned int j = 0; j < Container_obj.size(); j++)
		{
			if(current->get_container(i) == Container_obj[j]->get_name())
			{
				for(unsigned int k = 0; k < Container_obj[j]->get_trigger().size(); k++)
				{
					each_trigger(Container_obj[j]->get_trigger()[k], user_input, inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG, overridden, no_command);
				}
				break;
			}
		}
	}
	//check creature trigger
	for(int i = 0; i < current->get_creature_size(); i++)
	{
		for(unsigned int j = 0; j < Creature_obj.size(); j++)
		{
			if(current->get_creature(i) == Creature_obj[j]->get_name())
			{
				for(unsigned int k = 0; k < Creature_obj[j]->get_trigger().size(); k++)
				{
					each_trigger(Creature_obj[j]->get_trigger()[k], user_input, inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG, overridden, no_command);
				}
				break;
			}
		}
	}
}


void take_command(string user_input, vector<string> &inventory, Room* &current, vector<Room*> &Room_obj, vector<Container*> &Container_obj, vector<Item*> &Item_obj, vector<Creature*> &Creature_obj, bool &END_FLAG)
{
	if(user_input == "n" || user_input == "s" || user_input == "e" || user_input == "w")
	{
		move(user_input, current, Room_obj);
	}
	else if(user_input == "open exit")
	{
		open_exit(current, END_FLAG);
	}
	else if(user_input == "i")
	{
		check_inventory(inventory);
	}
	else if(user_input.find("drop") != string::npos)
	{
		drop(user_input, inventory, current);
	}
	else if(user_input.find("open") != string::npos)
	{
		open(user_input, current, Container_obj);
	}
	else if(user_input.find("put") != string::npos)
	{
		put(user_input, inventory, current, Container_obj);
	}
	else if(user_input.find("take") != string::npos)
	{
		take(user_input, inventory, current, Container_obj);
	}
	else if(user_input.find("read") != string::npos)
	{
		read(user_input, inventory, Item_obj);
	}
	else if(user_input.find("turn on") != string::npos)
	{
		turn_on(user_input, inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG);
	}
	else if(user_input.find("attack") != string::npos)
	{
		attack(user_input, inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG);
	}
	else if(user_input == "help")
	{
		help();
	}
	else
	{
		cout << "Not a command! For command help input 'help' " <<endl;
	}
}


int main(int argc, char *argv[]) {
	//char filename;
	//cin >> filename;
	if(argc != 2)
	{
		cout << "Input a xml file!!!" <<endl;
		return 0;
	}
	file<> xmlFile(argv[1]);
	xml_document<> Zork;
	Zork.parse<0>(xmlFile.data());

	xml_node<> *root_node = Zork.first_node() -> first_node();

	//create the list for room, item, containers, creatures
	///////////////////////////////////////////////////////
	vector<xml_node<>*> room_list;
	vector<xml_node<>*> item_list;
	vector<xml_node<>*> container_list;
	vector<xml_node<>*> creature_list;

	while(root_node != NULL)
	{
		if(string(root_node->name()) == string("room"))
		{
			room_list.push_back(root_node);
		}
		if(string(root_node->name()) == string("item"))
		{
			item_list.push_back(root_node);
		}
		if(string(root_node->name()) == string("container"))
		{
			container_list.push_back(root_node);
		}
		if(string(root_node->name()) == string("creature"))
		{
			creature_list.push_back(root_node);
		}
		root_node = root_node -> next_sibling();
	}
	//Add room object///////////////////////////////////
	int room_number = room_list.size();
	vector<Room*> Room_obj;
	Room *room;
	for(int i = 0; i < room_number; i++)
	{
		room = new Room(room_list[i], i);
		Room_obj.push_back(room);
	}
	////////////////////////////////////////////////////
	////////////////////////////////////////////////////
	//Add item object
	int item_number = item_list.size();
	vector<Item*> Item_obj;
	Item *item;
	for(int i = 0; i < item_number; i++)
	{
		item = new Item(item_list[i]);
		Item_obj.push_back(item);
	}
	///////////////////////////////////////////////////
	///////////////////////////////////////////////////
	//Add container object
	int container_number = container_list.size();
	vector<Container*> Container_obj;
	Container *container;
	for(int i = 0; i < container_number; i++)
	{
		container = new Container(container_list[i]);
		Container_obj.push_back(container);
	}
	///////////////////////////////////////////////////
	///////////////////////////////////////////////////
	//Add creature object
	int creature_number = creature_list.size();
	vector<Creature*> Creature_obj;
	Creature *creature;
	for(int i = 0; i < creature_number; i++)
	{
		creature = new Creature(creature_list[i]);
		Creature_obj.push_back(creature);
	}

	//game start
	bool END_FLAG = false;
	string user_input;
	Room *current;
	vector<string> inventory;
	current = Room_obj[0];
	cout << current->get_description() <<endl;
	while(END_FLAG == false)
	{
		bool overridden = false;
		//get command
		////////////////////////////////////////////////////////////////////////////////////
		getline(cin, user_input);
		// check_trigger
		check_trigger(user_input, inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG, overridden, false);

		if(overridden == false)
		{
			take_command(user_input, inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG);
		}

		check_trigger(user_input, inventory, current, Room_obj, Container_obj, Item_obj, Creature_obj, END_FLAG, overridden, true);


	}


	return 0;
}
