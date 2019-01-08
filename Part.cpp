#include "Part.h"



Part::Part(const PartType _part_type)
	: partType(_part_type)
	, equipment() {

}


Part::~Part() {

}

std::string Part::getDetail() const {
	if (isEquipping()) {
		return equipment->getDetail();
	}
	return partType.getName() + " : none";
}

PartType Part::getPartType() const {
	return partType;
}

bool Part::isEquipping() const {
	return equipment ? true : false;
}

bool Part::canEquip(const Equipment* _equipment) const {
	return partType.equal(_equipment->getPartType());
}

void Part::setEquipment(std::unique_ptr<Equipment>&& _equipment) {
	if (partType.equal(_equipment->getPartType())) {
		equipment = std::move(_equipment);
	}
}

Equipment* Part::getEquipment() const {
	if (isEquipping()) {
		return equipment.get();
	}
	return nullptr;
}
