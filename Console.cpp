#include "Console.h"
#include <iostream> 
#include <conio.h>  


/// <summary>
/// コンストラクタ
/// </summary>
Console::Console() {
	screenInfo = getCurrentConsoleScreenInfo();
}

/// <summary>
/// 画面サイズの設定
/// </summary>
/// <param name="screenWidth">画面の幅</param>
/// <param name="screenHeight">画面の高さ</param>
void Console::setScreenSize(int screenWidth, int screenHeight) {
	SHORT dx = screenWidth - screenInfo.screenSize.X;    // 水平方向の差分
	SHORT dy = screenHeight - screenInfo.screenSize.Y;    // 垂直方向の差分
	
	resizeScreen(dx, 0);
	resizeScreen(0, dy);
}

/// <summary>
/// 画面幅の取得
/// </summary>
/// <returns>
/// 画面幅（半角文字単位）
/// </returns>
int Console::getScreenWidth() {
	return screenInfo.screenSize.X;
}

/// <summary>
/// 画面高さの取得
/// </summary>
/// <returns>
/// 画面高さ（半角文字単位）
/// </returns>
int Console::getScreenHeight() {
	return screenInfo.screenSize.Y;
}

/// <summary>
/// フォントサイズ（高さ）の設定
/// </summary>
/// <param name="fontSize">フォントサイズ[pixel]</param>
void Console::setFontSize(int fontSize) {
	// フォント情報
	CONSOLE_FONT_INFOEX fontInfo = { sizeof(fontInfo) };    

	// 現在使用中のフォントの取得
	if (GetCurrentConsoleFontEx(screenInfo.hOutput, FALSE, &fontInfo) == 0) {
		exitWithMessage("フォントに関する情報の取得に失敗しました");
	}

	// フォントサイズの設定
	fontInfo.dwFontSize.X = (SHORT)fontSize / 2;
	fontInfo.dwFontSize.Y = (SHORT)fontSize;

	// フォントの更新
	if (SetCurrentConsoleFontEx(screenInfo.hOutput, FALSE, &fontInfo) == 0) {
		exitWithMessage("フォントの更新に失敗しました");
	}
}

/// <summary>
/// フォントサイズ（高さ）の取得
/// </summary>
/// <returns>
/// フォントサイズ[pixel]
/// </returns>
int Console::getFontSize() {
	// フォント情報
	CONSOLE_FONT_INFOEX fontInfo = { sizeof(fontInfo) };    

	// 現在使用中のフォントの取得
	if (GetCurrentConsoleFontEx(screenInfo.hOutput, FALSE, &fontInfo) == 0) {
		exitWithMessage("フォントに関する情報の取得に失敗しました");
	}

	// フォントサイズの返却
	return (int)fontInfo.dwFontSize.Y;
}

/// <summary>
/// カーソルの表示・非表示切り替え
/// </summary>
/// <param name="cursorState">カーソルの表示状態</param>
void Console::setCursorVisibility(CursorVisibility cursorState) {
	// カーソル情報
	CONSOLE_CURSOR_INFO cursorInfo;    

	// カーソルの表示状態の変更
	if (GetConsoleCursorInfo(screenInfo.hOutput, &cursorInfo) == 0) {
		exitWithMessage("カーソルに関する情報の取得に失敗しました");
	}
	cursorInfo.bVisible = (int)cursorState;

	// カーソルの表示状態の更新
	if (SetConsoleCursorInfo(screenInfo.hOutput, &cursorInfo) == 0) {
		exitWithMessage("カーソルに関する情報の更新に失敗しました");
	}
}

/// <summary>
/// カーソルの位置設定
/// </summary>
/// <param name="cursorPositionX">カーソルのX座標</param>
/// <param name="cursorPositionY">カーソルのY座標</param>
void Console::setCursorPosition(int cursorPositionX, int cursorPositionY) {
	// カーソルの位置情報
	COORD  cursorPosition = {
		(SHORT)cursorPositionX,    // X座標
		(SHORT)cursorPositionY     // Y座標
	};

	// カーソル位置の設定
	SetConsoleCursorPosition(screenInfo.hOutput, cursorPosition);
}

/// <summary>
/// カーソルの座標取得
/// </summary>
/// <param name="pCursorPositionX">カーソルのX座標を格納する変数へのポインタ</param>
/// <param name="pCursorPositionY">カーソルのY座標を格納する変数へのポインタ</param>
void Console::getCursorPosition(int* pCursorPositionX, int* pCursorPositionY) {
	// スクリーンバッファに関する情報
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;    

	// スクリーンバッファに関する情報の取得
	if (GetConsoleScreenBufferInfo(screenInfo.hOutput, &screenBufferInfo) == 0) {
		exitWithMessage("スクリーンバッファに関する情報の取得に失敗しました");
	}

	// カーソル位置の書き込み
	*pCursorPositionX = screenBufferInfo.dwCursorPosition.X;
	*pCursorPositionY = screenBufferInfo.dwCursorPosition.Y;
}

/// <summary>
/// カーソルの移動
/// </summary>
/// <param name="movementX"> X方向の移動量</param>
/// <param name="movementY"> Y方向の移動量</param>
void Console::moveCursorPosition(int movementX, int movementY) {
	int cursorPositionX;    // カーソルのX座標
	int cursorPositionY;    // カーソルのY座標

	// カーソル位置の設定
	getCursorPosition(&cursorPositionX, &cursorPositionY);
	setCursorPosition((cursorPositionX + movementX), (cursorPositionY + movementY));
}

/// <summary>
/// キー入力の取得
/// </summary>
/// <returns>
/// キーコード キー入力あり(特殊キーの場合は仮想キーコードを返却)
/// 0              キー入力なし
/// </returns>
int Console::getKeyInput() {
	// 入力されたキーのコード
	int code = 0;    

	// 入力されたキーの取得
	if (_kbhit()) {
		// 入力キーの取得
		code = _getch();    

		// 特殊文字の場合
		if (code == 0xE0 || code == 0x00)    
		{
			code = _getch() | 0x80;
		}
	}

	// 文字コードの返却
	return code;
}

/// <summary>
/// キーが押されるまで待機
/// </summary>
/// <returns>
/// 入力されたキーのコードを返却
/// </returns>
int Console::waitKey() {
	// 入力されたキーのコード
	int code;    

	// 入力処理 
	while (1) {
		// 入力キーの取得
		code = getKeyInput();    

		// 入力条件の合致判定
		if (code != 0) {
			return code;
		}
	}
}

/// <summary>
/// キーが押されるまで待機(メッセージ付き)
/// </summary>
/// <param name="message">出力メッセージ</param>
/// <returns>
/// 入力されたキーのコードを返却
/// </returns>
int Console::waitKeyWithMessage(const char* message) {
	// メッセージの表示
	std::cout << message << std::endl;

	// 入力処理 
	return waitKey();
}

/// <summary>
/// 指定されたキーが押されるまで待機
/// </summary>
/// <param name="codeList">キーコードのリスト</param>
/// <param name="numItems">リストのアイテム数</param>
/// <returns>
/// 選択肢の中から入力されたキーのコードを返却
/// </returns>
int Console::waitKeyWithKeyCode(const int codeList[], int numItems) {
	int code;    // 入力されたキーのコード
	int i;       // ループ用

	// 入力処理
	while (1) {
		// 入力キーの取得
		code = getKeyInput();    

		// 入力条件の合致判定 
		if (code != 0) {
			for (i = 0; i < numItems; i++) {
				if (code == codeList[i]) {
					return codeList[i];
				}
			}
		}
	}
}

/// <summary>
/// 整数値の入力
/// </summary>
/// <returns>
/// 入力された整数値
/// </returns>
int Console::inputInteger() {
	int digit = 0;    // 桁
	int number = 0;    // 入力値
	int code;          // 入力されたキーのコード

	// 入力処理 
	while (1) {
		// 入力キーの取得
		code = getKeyInput();    

		if (code >= '0' && code <= '9') {
			digit++;
			_putch(code);
			number = number * 10 + (code - '0');
		}
		else if (code == (int)KeyCode::KEY_ENTER) {
			_putch('\n');
			break;
		}
		else if (code == (int)KeyCode::KEY_BACKSPACE) {
			if (digit > 0) {
				digit--;
				number /= 10;
				_putch((int)KeyCode::KEY_BACKSPACE);
				_putch((int)KeyCode::KEY_SPACE);
				_putch((int)KeyCode::KEY_BACKSPACE);
			}
		}
	}


	// 入力された整数値を返却 ----------------------------
	return number;
}

/// <summary>
/// 画面のクリア
/// </summary>
void Console::clearScreen() {
	DWORD length = screenInfo.screenSize.X * screenInfo.screenSize.Y;    // 書き込む文字数
	COORD writeCoord = { 0, 0 };                                         // 文字を書き込むスクリーンバッファ座標
	DWORD numCharactersWritten;                                          // スクリーンバッファに実際に書き込まれた文字数

	// 画面をクリア
	FillConsoleOutputCharacter(screenInfo.hOutput, ' ', length, writeCoord, &numCharactersWritten);
	FillConsoleOutputAttribute(screenInfo.hOutput, screenInfo.textAttributes, length, writeCoord, &numCharactersWritten);

	setCursorPosition(0, 0);
}

/// <summary>
/// 文字色の設定
/// </summary>
/// <param name="textColor">文字色</param>
void Console::setTextColor(ConsoleColor textColor) {
	// 文字色の変更
	screenInfo.textAttributes = (screenInfo.textAttributes & 0xF0) | (int)textColor;

	// 文字の属性の更新
	if (SetConsoleTextAttribute(screenInfo.hOutput, screenInfo.textAttributes) == 0) {
		exitWithMessage("文字色の変更に失敗しました。");
	}
}

/// <summary>
/// 背景色の設定
/// </summary>
/// <param name="backColor">背景色</param>
void Console::setBackColor(ConsoleColor backColor) {
	// 背景色の変更
	screenInfo.textAttributes = (screenInfo.textAttributes & 0x0F) | ((int)backColor << 4);

	// 文字の属性の更新
	if (SetConsoleTextAttribute(screenInfo.hOutput, screenInfo.textAttributes) == 0) {
		exitWithMessage("背景色の変更に失敗しました。");
	}
}

/// <summary>
/// 中央揃えで出力
/// </summary>
/// <param name="text">出力文字列</param>
void Console::printCenter(std::string text, bool useEndl) {
	int x, y, width;
	getCursorPosition(&x, &y);
	width = getScreenWidth();
	setCursorPosition((width - x - text.size()) / 2 + x, y);
	std::cout << text;
	if (useEndl) {
		std::cout << "\n";
	}
}

/// <summary>
/// 右揃えで出力
/// </summary>
/// <param name="text">出力文字列</param>
/// <param name="offset">オフセット（右から）</param>
void Console::printRight(std::string text, int offset) {
	int x, y, width;
	getCursorPosition(&x, &y);
	width = getScreenWidth();
	setCursorPosition(width - text.size() - offset, y);
	std::cout << text;
	for (int i = 0; i < offset; ++i) {
		std::cout << " ";
	}
}

/// <summary>
/// 右揃えで出力
/// </summary>
/// <param name="osstream">出力ストリーム</param>
/// <param name="offset">オフセット（右から）</param>
void Console::printRight(std::ostringstream& osstream, int offset) {
	printRight(osstream.str(), offset);
	osstream.str("");
	osstream.clear(std::stringstream::goodbit);
}

/// <summary>
/// 現在のコンソール画面に関する情報を取得
/// </summary>
/// <returns>
/// 現在のコンソール画面に関する情報
/// </returns>
Console::ScreenInfo  Console::getCurrentConsoleScreenInfo() {
	HANDLE                     hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);    // 標準出力デバイスのハンドル
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;                                // スクリーンバッファに関する情報
	ScreenInfo                 screenInfo;                                      // コンソール画面に関する情報

	// スクリーンバッファに関する情報の取得
	if (GetConsoleScreenBufferInfo(hStdOutput, &screenBufferInfo) == 0) {
		exitWithMessage("スクリーンバッファに関する情報の取得に失敗しました");
	}


	// コンソール画面に関する情報の設定 ------------------
	screenInfo.hOutput = hStdOutput;
	screenInfo.screenSize.X = screenBufferInfo.srWindow.Right + 1;
	screenInfo.screenSize.Y = screenBufferInfo.srWindow.Bottom + 1;
	screenInfo.textAttributes = screenBufferInfo.wAttributes;


	// コンソール画面に関する情報の返却 ------------------
	return screenInfo;
}

/// <summary>
/// 画面の拡大・縮小
/// </summary>
/// <param name="dx">水平方向の差分</param>
/// <param name="dy">垂直方向の差分</param>
void Console::resizeScreen(SHORT dx, SHORT dy) {
	// スクリーンバッファのサイズ
	COORD  screenBufferSize = {
		screenInfo.screenSize.X + dx,    // 幅
		screenInfo.screenSize.Y + dy     // 高さ
	};

	// ウィンドウ矩形
	SMALL_RECT windowRect = {
		0,                         // 左
		0,                         // 上
		screenBufferSize.X - 1,    // 右
		screenBufferSize.Y - 1     // 下
	};

	// 画面のサイズ変更
	if (dx > 0 || dy > 0) {
		// 拡大の場合
		if (!SetConsoleScreenBufferSize(screenInfo.hOutput, screenBufferSize)) {
			exitWithMessage("スクリーンバッファのサイズの変更に失敗しました。");
		}

		if (!SetConsoleWindowInfo(screenInfo.hOutput, TRUE, &windowRect)) {
			exitWithMessage("ウィンドウのサイズの変更に失敗しました。");
		}
	}
	else {
		// 縮小の場合
		if (!SetConsoleWindowInfo(screenInfo.hOutput, TRUE, &windowRect)) {
			exitWithMessage("ウィンドウのサイズの変更に失敗しました。");
		}

		if (!SetConsoleScreenBufferSize(screenInfo.hOutput, screenBufferSize)) {
			exitWithMessage("スクリーンバッファのサイズの変更に失敗しました。");
		}
	}

	// 画面に関する情報内のサイズ情報を更新
	screenInfo.screenSize = screenBufferSize;
}

/// <summary>
/// 強制終了(メッセージ付き)
/// </summary>
/// <param name="message">出力メッセージ</param>
void Console::exitWithMessage(const char* message) {
	waitKeyWithMessage(message);

	exit(-1);
}