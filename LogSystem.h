#pragma once
#include "Singleton.h"
#include <string>


class LogSystem : public Singleton<LogSystem> {

	friend Singleton<LogSystem>;

public:
	static const int LOG_MAX = 6;

private:
	int areaLeft;
	int areaTop;
	int areaWidth;
	int areaHeight;

	std::string logs[LOG_MAX];
	int nextIndex;
	int topIndex;

private:
	LogSystem();

private:
	void initializeFlame();
	void drawFlame();
	void drawLogs();

public:
	void resetLog();
	void addLog(std::string _log);
};

