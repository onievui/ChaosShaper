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

	std::string getPartTypeName(const PartType _part_type) {
		switch (_part_type) {
		case PartType::Head: return "Head";
		case PartType::Body: return "Body";
		case PartType::Arm: return "Arm";
		case PartType::Leg: return "Leg";
		default: return "<error>";
		}
	}
};
