#pragma once
#include <string>

/// <summary>
/// ��������
/// </summary>
enum class Attribute : int {
	Normal,
	Fire,
	Freeze,
	Wind,
	Num
};


/// <summary>
/// �����l�N���X
/// </summary>
class AttributePower {
public:
	Attribute attribute;
	int power;

public:
	AttributePower(const Attribute _attribute, const int _power);

public:
	std::string getDetail() const;	//���̎擾
};