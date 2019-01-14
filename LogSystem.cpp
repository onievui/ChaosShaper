#include "LogSystem.h"
#include "Console.h"
#include <iostream>


/// <summary>
/// コンストラクタ
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
/// フレーム情報の初期化
/// </summary>
void LogSystem::initializeFlame() {
	areaLeft = 2;
	areaTop = 31;
	areaWidth = Console::getIns()->GetScreenWidth() - 4;
	areaHeight = Console::getIns()->GetScreenHeight() - areaTop - 1;
}

/// <summary>
/// フレームの描画
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
/// ログの表示
/// </summary>
void LogSystem::drawLogs() {
	drawFlame();
	Console* console = Console::getIns();
	for (int i = 0; i < 5; ++i) {
		console->SetCursorPosition(areaLeft + 1, areaTop + i + 1);
		std::cout << " " << logs[(topIndex + i) % 5] << std::endl;
	}
}

/// <summary>
/// ログの追加
/// </summary>
/// <param name="_log">ログ</param>
void LogSystem::addLog(std::string _log) {
	Console* console = Console::getIns();
	logs[(nextIndex++)%5] = _log;
	if (nextIndex >= 5) {
		logs[topIndex] = "";
		topIndex = (topIndex + 1) % 5;
	}
	drawLogs();
}
