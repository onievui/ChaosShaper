#include "LogSystem.h"
#include "Console.h"
#include <iostream>


/// <summary>
/// �R���X�g���N�^
/// </summary>
LogSystem::LogSystem() 
	: areaLeft()
	, areaTop()
	, areaWidth()
	, areaHeight()
	, topIndex()
	, nextIndex()
	, logs() {
	initializeFlame();
}

/// <summary>
/// �t���[�����̏�����
/// </summary>
void LogSystem::initializeFlame() {
	areaLeft = 2;
	areaTop = 31;
	areaWidth = Console::getIns()->getScreenWidth() - 4;
	areaHeight = Console::getIns()->getScreenHeight() - areaTop - 1;
}

/// <summary>
/// �t���[���̕`��
/// </summary>
void LogSystem::drawFlame() {
	for (int i = 0; i < areaHeight; ++i) {
		Console::getIns()->setCursorPosition(areaLeft, areaTop + i);
		for (int j = 0; j < areaWidth; ++j) {
			if (i == 0 || i == areaHeight - 1 ||
				j == 0 || j == areaWidth - 1) {
				std::cout << "*";
			}
			else {
				std::cout << " ";
			}
		}
		std::cout << "\n";
	}
	std::cout << std::flush;
}

/// <summary>
/// ���O�̕\��
/// </summary>
void LogSystem::drawLogs() {
	Console* console = Console::getIns();
	for (int i = 0; i < LOG_MAX; ++i) {
		console->setCursorPosition(areaLeft + 1, areaTop + i + 1);
		int index = (topIndex + i) % LOG_MAX;
		std::cout << " " << logs[index];
		for (int j = logs[index].size(); j < areaWidth - 4; ++j) {
			std::cout << " ";
		}
	}
	std::cout << std::flush;
}

/// <summary>
/// ���O�̃��Z�b�g
/// </summary>
void LogSystem::resetLog() {
	for (auto& log : logs) {
		log.clear();
	}
	nextIndex = 0;
	topIndex = 0;
	drawLogs();
}

/// <summary>
/// ���O�̒ǉ�
/// </summary>
/// <param name="_log">���O</param>
void LogSystem::addLog(std::string _log) {
	Console* console = Console::getIns();
	logs[(nextIndex++)% LOG_MAX] = _log;
	if (nextIndex > LOG_MAX) {
		topIndex = (topIndex + 1) % LOG_MAX;
	}
	drawLogs();
}
