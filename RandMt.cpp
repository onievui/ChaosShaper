#include "RandMt.h"


std::mt19937 RandMt::mt;

int RandMt::GetRand(const int _range) {
	static RandMt instance;
	return mt() % _range;
}
