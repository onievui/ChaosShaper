#include "Portion.h"


Portion::Portion(const std::string& _name, const int _level, const int _power)
	: Item(_name, _level) 
	, power(_power) {
}
