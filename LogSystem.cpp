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
	areaWidth = Console::getIns()->GetScreenWidth() - 4;
	areaHeight = Console::getIns()->GetScreenHeight() - areaTop - 1;
}

/// <summary>
/// �t���[���̕`��
/// </summary>
void LogSystem::drawFlame() {
	for (int i = 0; i < areaHeight; ++i) {
		Console::getIns()->SetCursorPosition(areaLeft, areaTop + i);
		for (int j = 0; j < areaWidth; ++j) {
			if (i == 0 || i == areaHeight - 1 ||
				j == 0 || j == areaWidth - 1) {
				std::cout << "*";
			}
			else {
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
}

/// <summary>
/// ���O�̕\��
/// </summary>
void LogSystem::drawLogs() {
	drawFlame();
	Console* console = Console::getIns();
	for (int i = 0; i < LOG_MAX; ++i) {
		console->SetCursorPosition(areaLeft + 1, areaTop + i + 1);
		std::cout << " " << logs[(topIndex + i) % LOG_MAX] << std::endl;
	}
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
