#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Part.h"
#include "Item.h"
#include "Parameter.h"


/// <summary>
/// キャラクタークラス
/// </summary>
class Character {
public:
	static const int PARTS_MAX;
	static const int ITEMS_MAX;
protected:
	std::string name;
	std::vector<std::unique_ptr<Part>> parts;
	std::vector<std::unique_ptr<Item>> items;
	CharaParameter parameter;

public:
	Character(const std::string& _name);
	Character(const std::string& _name, std::vector<std::unique_ptr<Part>>&& _parts,
		std::vector<std::unique_ptr<Item>>&& _items, const CharaParameter& _parameter);
	virtual ~Character() = default;

public:
	std::string& getName();
	void setName(std::string& _name);

	bool addPart(std::unique_ptr<Part>&& _part);
	bool addParts(std::vector<std::unique_ptr<Part>>&& _parts);
	std::vector<std::unique_ptr<Part>>& getParts();

	bool addItem(std::unique_ptr<Item>&& _item);
	bool addItems(std::vector<std::unique_ptr<Item>>&& _items);
	std::vector<std::unique_ptr<Item>>& getItems();

	void setStatus(const CharaParameter& _parameter);
	const CharaParameter& getDefaultStatus();
	CharaParameter getStatus();

public:
	bool equipItem(std::vector<std::unique_ptr<Item>>::iterator& _it);
	void autoEquipping();
	void removeEquipment(const int _part_index);
};
