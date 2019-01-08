#include "Item.h"



Item::Item(const std::string& _name, const int _level)
	: name(_name)
	, level(_level) {
}

const std::string& Item::getName() const {
	return name;
}

std::string Item::getDetail() const {
	std::string str;
	str = name + "+" + std::to_string(level);
	return str;
}
