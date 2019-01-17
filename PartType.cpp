#include "PartType.h"
#include "ErrorMessage.h"


constexpr PartTypeBase PartType::Head;
constexpr PartTypeBase PartType::Body;
constexpr PartTypeBase PartType::Arm;
constexpr PartTypeBase PartType::Leg;
constexpr PartTypeBase PartType::Num;


/// <summary>
/// ���ʎ�ޖ��̎擾
/// </summary>
/// <returns>
/// ���ʎ�ޖ�
/// </returns>
std::string PartTypeBase::getName() const {
	switch (data) {
	case PartType::Head: return "��";
	case PartType::Body: return "��";
	case PartType::Arm:  return "�r";
	case PartType::Leg:  return "�r";
	default:             ErrorMessage("�s���ȕ��ʂł�");
						 return "<error>";
	}
}

/// <summary>
/// �����ʎ�ރ^�C�v���ǂ���
/// </summary>
/// <param name="_part_type_base">���ʎ��</param>
/// <returns>
/// true : ����
/// false : �Ⴄ
/// </returns>
bool PartTypeBase::equal(const PartType _part_type_base) const {
	return data == _part_type_base.data;
}

/// <summary>
/// �f�[�^�iID�j�̎擾
/// </summary>
/// <returns>
/// �f�[�^�iID�j
/// </returns>
int PartTypeBase::getData() const {
	return data;
}

