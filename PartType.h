#pragma once
#include <string>


enum class PartType : int {
	Head,
	Body,
	Arm,
	Leg,
	Num
};


namespace PartTypeFunc {
	extern std::string getPartTypeName(const PartType _part_type);
};
