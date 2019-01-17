#pragma once
#include "Item.h"
#include "PartType.h"
#include "Parameter.h"
#include <vector>
#include <memory>


class ItemFactory {
public:
	static std::vector<std::unique_ptr<Item>> createItems(const int _floor);

private:
	static std::string generateName(const PartType _part_type, const int _rank);
	static EquipParameter generateParameter(const PartType _part_type, const int _rank, const int _floor);
	static AttributePower generateAttributePower(const Attribute _attribute, EquipParameter* _parameter, const PartType _part_type);
};




