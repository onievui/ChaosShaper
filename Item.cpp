#include "Item.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_name">���O</param>
/// <param name="_level">���x��</param>
Item::Item(const std::string& _name, const int _level)
	: name(_name)
	, level(_level) {
}

/// <summary>
/// ���O�̎擾
/// </summary>
/// <returns>
/// ���O
/// </returns>
const std::string& Item::getName() const {
	return name;
}

/// <summary>
/// ���̎擾
/// </summary>
/// <returns>
/// ���e�L�X�g
/// </returns>
std::string Item::getDetail() const {
	std::string str;
	str = name + "+" + std::to_string(level);
	return str;
}

/// <summary>
/// ���x���̎擾
/// </summary>
/// <returns>
/// ���x��
/// </returns>
int Item::getLevel() const {
	return level;
}
