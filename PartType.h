#pragma once
#include <string>



class PartType;

/// <summary>
/// ���ʎ�ރx�[�X�N���X
/// </summary>
class PartTypeBase {

	friend PartType;

private:
	int data;
	PartTypeBase() = default;
	PartTypeBase(const PartTypeBase&) = default;
	constexpr explicit PartTypeBase(const int data) : data(data) {}
	constexpr operator int() const { return data; }

public:
	std::string getName() const;
	bool equal(const PartType _part_type_base) const;
};

/// <summary>
/// ���ʎ�ރN���X
/// </summary>
class PartType : public PartTypeBase {
public:
	static constexpr PartTypeBase Head{ 0 };
	static constexpr PartTypeBase Body{ 1 };
	static constexpr PartTypeBase Arm { 2 };
	static constexpr PartTypeBase Leg { 3 };

public:
	PartType() = default;
	constexpr explicit PartType(const int data) : PartTypeBase(data) {}
	constexpr PartType(const PartTypeBase& base) : PartTypeBase(base) {}

};