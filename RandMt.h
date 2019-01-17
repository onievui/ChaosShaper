#pragma once
#include <random>


class RandMt {
private:
	std::random_device seed;
	static std::mt19937 mt;
	RandMt() {
		mt.seed(seed());
	}
	~RandMt() = default;

public:
	RandMt(const RandMt&) = delete;
	RandMt& operator=(const RandMt&) = delete;
	RandMt(RandMt&&) = delete;
	RandMt& operator=(RandMt&&) = delete;

	static int GetRand(const int _range);
};
