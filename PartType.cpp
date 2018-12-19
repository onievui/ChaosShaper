#include "PartType.h"


namespace PartTypeFunc {

	std::string getPartTypeName(const PartType _part_type) {
		switch (_part_type) {
		case PartType::Head: return "“ª";
		case PartType::Body: return "‘Ì";
		case PartType::Arm: return "˜r";
		case PartType::Leg: return "‹r";
		default: return "<error>";
		}
	}

}
