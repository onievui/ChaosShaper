#include "PartType.h"
#include "ErrorMessage.h"

constexpr PartTypeBase PartType::Head;
constexpr PartTypeBase PartType::Body;
constexpr PartTypeBase PartType::Arm;
constexpr PartTypeBase PartType::Leg;


std::string PartTypeBase::getName() const {
	switch (data) {
	case PartType::Head: return "頭";
	case PartType::Body: return "体";
	case PartType::Arm:  return "腕";
	case PartType::Leg:  return "脚";
	default:             ErrorMessage(L"不正な部位です");
						 return "<error>";
	}
}

bool PartTypeBase::equal(const PartType _part_type_base) const {
	return data == _part_type_base.data;
}

