#pragma once
#include <string>


/// <summary>
/// アイテムクラス
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

