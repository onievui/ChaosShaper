#include "Portion.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_name">���O</param>
/// <param name="_level">���x��</param>
/// <param name="_power">���x</param>
Portion::Portion(const std::string& _name, const int _level, const int _power)
	: Item(_name, _level) 
	, power(_power) {
}

/// <summary>
/// ���̎擾
/// </summary>
/// <returns>
/// ���e�L�X�g
/// </returns>
std::string Portion::getDetail() const {
	std::string str;
	str = name + "+" + std::to_string(level);
	return str;
}
