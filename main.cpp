#include "Player.h"
#include "Equipment.h"
#include "Portion.h"
#include <iostream>
#include"ErrorMessage.h"


int main() {

	Player player = Player("ony");
	auto equip = std::make_unique<Equipment>("sword", 10, PartType::Arm, EquipParameter(), AttributePower(Attribute::Fire, 200));
	auto pot = std::make_unique<Portion>("pot", 10, 100);
	auto part = std::make_unique<Part>(PartType::Arm);
	player.addPart(std::move(part));
	player.addItem(std::move(equip));
	player.addItem(std::move(pot));

	std::cout << "name : " + player.getName() << std::endl;
	std::cout << std::endl;

	CharaParameter param = player.getStatus();
	std::cout << "level   : " << param.level << std::endl;
	std::cout << "hp      : " << param.hp << std::endl;
	std::cout << "attack  : " << param.attack << std::endl;
	std::cout << "defence : " << param.defence << std::endl;
	std::cout << std::endl;


	for (const auto& item : player.getItems()) {
		std::cout << item->getDetail() << std::endl;
	}
	std::cout << std::endl;

	for (const auto& part : player.getParts()) {
		std::cout << part->getDetail() << std::endl;
	}
	std::cout << std::endl;

	player.autoEquipping();

	for (const auto& part : player.getParts()) {
		std::cout << part->getDetail() << std::endl;
	}
	std::cout << std::endl;

	for (const auto& item : player.getItems()) {
		std::cout << item->getDetail() << std::endl;
	}
	std::cout << std::endl;

	player.removeEquipment(0);

	for (const auto& part : player.getParts()) {
		std::cout << part->getDetail() << std::endl;
	}
	std::cout << std::endl;

	return 0;
}