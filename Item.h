#pragma once
#include <string>


/// <summary>
/// �A�C�e���N���X
/// </summary>
class Item {
protected:
	std::string name;
	int level;

public:
	Item(const std::string& _name, const int _level);
	virtual ~Item() = default;

public:
	const std::string& getName() const;
	virtual std::string getDetail() const;
};

