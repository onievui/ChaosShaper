#include "Player.h"
#include "Equipment.h"
#include <iostream>


int main() {

	//Item item = Item("pot", 100);
	Player player = Player("ony");
	auto equip = std::make_unique<Equipment>("sword", 10, PartType::Arm, EquipParameter(), AttributePower(Attribute::Fire, 200));
	auto part = std::make_unique<Part>(PartType::Arm);
	player.addPart(std::move(part));
	player.addItem(std::move(equip));

	std::cout << "name : " + player.getName() << std::endl;
	std::cout << std::endl;

	CharaParameter param = player.getStatus();
	std::cout << "level   : " << param.level << std::endl;
	std::cout << "hp      : " << param.hp << std::endl;
	std::cout << "attack  : " << param.attack << std::endl;
	std::cout << "defence : " << param.defence << std::endl;
	std::cout << std::endl;


	auto& parts = player.getParts();
	for (const auto& part : parts) {
		std::cout << part->getDetail() << std::endl;
	}
	std::cout << std::endl;

	player.autoEquipping();

	for (const auto& part : parts) {
		std::cout << part->getDetail() << std::endl;
	}
	std::cout << std::endl;


	return 0;
}