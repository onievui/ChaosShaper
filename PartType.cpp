#include "PartType.h"
#include "ErrorMessage.h"


constexpr PartTypeBase PartType::Head;
constexpr PartTypeBase PartType::Body;
constexpr PartTypeBase PartType::Arm;
constexpr PartTypeBase PartType::Leg;
constexpr PartTypeBase PartType::Num;


/// <summary>
/// 部位種類名の取得
/// </summary>
/// <returns>
/// 部位種類名
/// </returns>
std::string PartTypeBase::getName() const {
	switch (data) {
	case PartType::Head: return "頭";
	case PartType::Body: return "体";
	case PartType::Arm:  return "腕";
	case PartType::Leg:  return "脚";
	default:             ErrorMessage("不正な部位です");
						 return "<error>";
	}
}

/// <summary>
/// 同部位種類タイプかどうか
/// </summary>
/// <param name="_part_type_base">部位種類</param>
/// <returns>
/// true : 同じ
/// false : 違う
/// </returns>
bool PartTypeBase::equal(const PartType _part_type_base) const {
	return data == _part_type_base.data;
}

/// <summary>
/// データ（ID）の取得
/// </summary>
/// <returns>
/// データ（ID）
/// </returns>
int PartTypeBase::getData() const {
	return data;
}

