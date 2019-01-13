#pragma once
#include "Singleton.h"


class ShareDataManager : public Singleton<ShareDataManager> {

	friend Singleton<ShareDataManager>;

private:

private:
	ShareDataManager();
	~ShareDataManager() = default;

public:
	void initialize();	//‰Šú‰»

};







