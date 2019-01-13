#include "Character.h"
#include "ErrorMessage.h"


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
	//最大部位数に到達したらループを終了する
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
		if (part->isEquipping()) {
			final_parameter.addParameter(part->getEquipment()->getParameter());
		}
	}
	return final_parameter;
}

bool Character::equipItem(std::vector<std::unique_ptr<Item>>::iterator& it) {
	//装備品でないなら処理しない
	Equipment* equip = dynamic_cast<Equipment*>(it->get());
	if (!equip) {
		ErrorMessage("装備品でないものを装備しようとしています");
		return false;
	}
	for (const auto& part : parts) {
		//装備中なら飛ばす
		if (part->isEquipping()) {
			continue;
		}
		//装備可能なら装備
		if (part->canEquip(equip)) {
			//派生クラスに変換して装備させる
			part->setEquipment(std::make_unique<Equipment>(*equip));
			//リストから削除する
			it = items.erase(it);
			return true;
		}
	}
	return false;
}

void Character::autoEquipping() {
	for (auto it = items.begin(); it != items.end();) {
		//装備品でないなら飛ばす
		Equipment* equip = dynamic_cast<Equipment*>(it->get());
		if (!equip) {
			++it;
			continue;
		}
		//装備に失敗したらイテレータを進める
		if (!equipItem(it)) {
			++it;
		}
	}
}

void Character::removeEquipment(const int _part_index) {
	std::unique_ptr<Equipment> equip = parts[_part_index]->removeEquipment();
	addItem(std::move(equip));
}


