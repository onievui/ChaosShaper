#include "Character.h"



const int Character::PARTS_MAX = 10;
const int Character::ITEMS_MAX = 10;

Character::Character(const std::string& _name)
	: name(_name)
	, parts{}
	, items{}
	, parameter() {
}

Character::Character(const std::string& _name, std::vector<std::unique_ptr<Part>>&& _parts,
	std::vector<std::unique_ptr<Item>>&& _items, const CharaParameter& _parameter) 
	: name(_name)
	, parts(std::move(_parts))
	, items(std::move(_items))
	, parameter(_parameter) {
}

std::string& Character::getName() {
	return name;
}

bool Character::addPart(std::unique_ptr<Part>&& _part) {
	if (parts.size() == PARTS_MAX) {
		return false;
	}
	parts.emplace_back(std::move(_part));
	return true;
}

bool Character::addParts(std::vector<std::unique_ptr<Part>>&& _parts) {
	int pri_size = parts.size();
	int add_size = _parts.size();
	if (pri_size == PARTS_MAX || add_size == 0) {
		return false;
	}

	for (int i = 0; i < add_size && pri_size + i < PARTS_MAX; ++i) {
		parts.emplace_back(std::move(_parts[i]));
	}
	return true;
}

std::vector<std::unique_ptr<Part>>& Character::getParts() {
	return parts;
}

bool Character::addItem(std::unique_ptr<Item>&& _item) {
	if (items.size() == ITEMS_MAX) {
		return false;
	}
	items.emplace_back(std::move(_item));
	return true;
}

bool Character::addItems(std::vector<std::unique_ptr<Item>>&& _items) {
	int pri_size = items.size();
	int add_size = _items.size();
	if (pri_size == ITEMS_MAX || add_size == 0) {
		return false;
	}

	for (int i = 0; i < add_size && pri_size + i < ITEMS_MAX; ++i) {
		items.emplace_back(std::move(_items[i]));
	}
	return true;
}

std::vector<std::unique_ptr<Item>>& Character::getItems() {
	return items;
}

void Character::setStatus(const CharaParameter& _parameter) {
	parameter = _parameter;
}

const CharaParameter& Character::getDefaultStatus() {
	return parameter;
}

CharaParameter Character::getStatus() {
	CharaParameter final_parameter = parameter;
	for (const auto &part : parts) {
		Equipment* equip = part->getEquipment();
		if (equip) {
			final_parameter.addParameter(equip->getParameter());
		}
	}
	return final_parameter;
}

void Character::autoEquipping() {
	//for (const auto& item : items) {
	//	Equipment* equip = dynamic_cast<Equipment*>(item.get());
	//	if (equip) {
	//		for (const auto& part : parts) {
	//			if (part->canEquip(equip)) {
	//				break;
	//			}
	//		}
	//	}
	//}
	for (const auto& part : parts) {
		//‘•”õ’†‚È‚ç”ò‚Î‚·
		if (part.get()->isEquipping()) {
			continue;
		}
		for (int i, size = items.size(); i < size; ++i) {
			//‘•”õ•i‚Å‚È‚¢‚È‚ç”ò‚Î‚·
			Equipment* equip = dynamic_cast<Equipment*>(items[i].get());
			if (!equip) {
				continue;
			}
			//‘•”õ‰Â”\‚È‚ç‘•”õ
			if (part->canEquip(equip)) {

			}
		}
	}
}

