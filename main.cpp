#include "Player.h"
#include "Equipment.h"
#include <iostream>


int main() {

	//Item item = Item("pot", 100);
	Equipment equip = Equipment("sword", 10, PartType::Arm, CharaParameter(), AttributePower(Attribute::Fire, 200));

	//std::cout << item.getName();
	//std::cout << std::endl;
	//std::cout << item.getDetail();
	//std::cout << std::endl;

	std::cout << equip.getName();
	std::cout << std::endl;
	std::cout << equip.getDetail();
	std::cout << std::endl;

	return 0;
}