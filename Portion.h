#pragma once
#include "Item.h"


/// <summary>
/// �|�[�V�����N���X
/// </summary>
class Portion : public Item {
private:
	int power;
public:
	Portion(const std::string& _name, const int _level, const int _power);
	virtual ~Portion() = default;

public:
	std::string getDetail() const override;
};

