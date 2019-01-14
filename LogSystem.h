#pragma once
#include "Singleton.h"
#include <string>


class LogSystem : public Singleton<LogSystem> {

	friend Singleton<LogSystem>;

private:
	int areaLeft;
	int areaTop;
	int areaWidth;
	int areaHeight;

	std::string logs[5];
	int nextIndex;
	int topIndex;

private:
	LogSystem();

private:
	void initializeFlame();
	void drawFlame();
	void drawLogs();

public:
	void addLog(std::string _log);

};

