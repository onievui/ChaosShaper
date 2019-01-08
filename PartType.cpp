#include "PartType.h"
#include "ErrorMessage.h"

constexpr PartTypeBase PartType::Head;
constexpr PartTypeBase PartType::Body;
constexpr PartTypeBase PartType::Arm;
constexpr PartTypeBase PartType::Leg;


std::string PartTypeBase::getName() const {
	switch (data) {
	case PartType::Head: return "��";
	case PartType::Body: return "��";
	case PartType::Arm:  return "�r";
	case PartType::Leg:  return "�r";
	default:             ErrorMessage(L"�s���ȕ��ʂł�");
						 return "<error>";
	}
}

bool PartTypeBase::equal(const PartType _part_type_base) const {
	return data == _part_type_base.data;
}

