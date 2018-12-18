#include "Item.h"



Item::Item(const std::string& _name, const int _level)
	: name(_name)
	, level(_level) {
}

std::string& Item::getName() {
	return name;
}
