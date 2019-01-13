#pragma once
#include "PartType.h"
#include "Equipment.h"
#include <memory>



class Part {
private:
	PartType partType;
	std::unique_ptr<Equipment> equipment;

public:
	Part(const PartType _part_type);
	virtual ~Part();

public:
	std::string getDetail() const;
	PartType getPartType() const;
	bool isEquipping() const;
	bool canEquip(const Equipment* _equipment) const;
	void setEquipment(std::unique_ptr<Equipment>&& _equipment);
	Equipment* getEquipment() const;

	std::unique_ptr<Equipment> removeEquipment();
};

