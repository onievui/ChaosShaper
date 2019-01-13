#include "Console.h"
#include <iostream> 
#include <conio.h>  


/// <summary>
/// �R���X�g���N�^
/// </summary>
Console::Console() {
	screenInfo = GetCurrentConsoleScreenInfo();
}

/// <summary>
/// ��ʃT�C�Y�̐ݒ�
/// </summary>
/// <param name="screenWidth">��ʂ̕�</param>
/// <param name="screenHeight">��ʂ̍���</param>
void Console::SetScreenSize(int screenWidth, int screenHeight) {
	SHORT dx = screenWidth - screenInfo.screenSize.X;    // ���������̍���
	SHORT dy = screenHeight - screenInfo.screenSize.Y;    // ���������̍���
	
	ResizeScreen(dx, 0);
	ResizeScreen(0, dy);
}

/// <summary>
/// ��ʕ��̎擾
/// </summary>
/// <returns>
/// ��ʕ��i���p�����P�ʁj
/// </returns>
int Console::GetScreenWidth() {
	return screenInfo.screenSize.X;
}

/// <summary>
/// ��ʍ����̎擾
/// </summary>
/// <returns>
/// ��ʍ����i���p�����P�ʁj
/// </returns>
int Console::GetScreenHeight() {
	return screenInfo.screenSize.Y;
}

/// <summary>
/// �t�H���g�T�C�Y�i�����j�̐ݒ�
/// </summary>
/// <param name="fontSize">�t�H���g�T�C�Y[pixel]</param>
void Console::SetFontSize(int fontSize) {
	// �t�H���g���
	CONSOLE_FONT_INFOEX fontInfo = { sizeof(fontInfo) };    

	// ���ݎg�p���̃t�H���g�̎擾
	if (GetCurrentConsoleFontEx(screenInfo.hOutput, FALSE, &fontInfo) == 0) {
		ExitWithMessage("�t�H���g�Ɋւ�����̎擾�Ɏ��s���܂���");
	}

	// �t�H���g�T�C�Y�̐ݒ�
	fontInfo.dwFontSize.X = (SHORT)fontSize / 2;
	fontInfo.dwFontSize.Y = (SHORT)fontSize;

	// �t�H���g�̍X�V
	if (SetCurrentConsoleFontEx(screenInfo.hOutput, FALSE, &fontInfo) == 0) {
		ExitWithMessage("�t�H���g�̍X�V�Ɏ��s���܂���");
	}
}

/// <summary>
/// �t�H���g�T�C�Y�i�����j�̎擾
/// </summary>
/// <returns>
/// �t�H���g�T�C�Y[pixel]
/// </returns>
int Console::GetFontSize() {
	// �t�H���g���
	CONSOLE_FONT_INFOEX fontInfo = { sizeof(fontInfo) };    

	// ���ݎg�p���̃t�H���g�̎擾
	if (GetCurrentConsoleFontEx(screenInfo.hOutput, FALSE, &fontInfo) == 0) {
		ExitWithMessage("�t�H���g�Ɋւ�����̎擾�Ɏ��s���܂���");
	}

	// �t�H���g�T�C�Y�̕ԋp
	return (int)fontInfo.dwFontSize.Y;
}

/// <summary>
/// �J�[�\���̕\���E��\���؂�ւ�
/// </summary>
/// <param name="cursorState">�J�[�\���̕\�����</param>
void Console::SetCursorVisibility(CursorVisibility cursorState) {
	// �J�[�\�����
	CONSOLE_CURSOR_INFO cursorInfo;    

	// �J�[�\���̕\����Ԃ̕ύX
	if (GetConsoleCursorInfo(screenInfo.hOutput, &cursorInfo) == 0) {
		ExitWithMessage("�J�[�\���Ɋւ�����̎擾�Ɏ��s���܂���");
	}
	cursorInfo.bVisible = (int)cursorState;

	// �J�[�\���̕\����Ԃ̍X�V
	if (SetConsoleCursorInfo(screenInfo.hOutput, &cursorInfo) == 0) {
		ExitWithMessage("�J�[�\���Ɋւ�����̍X�V�Ɏ��s���܂���");
	}
}

/// <summary>
/// �J�[�\���̈ʒu�ݒ�
/// </summary>
/// <param name="cursorPositionX">�J�[�\����X���W</param>
/// <param name="cursorPositionY">�J�[�\����Y���W</param>
void Console::SetCursorPosition(int cursorPositionX, int cursorPositionY) {
	// �J�[�\���̈ʒu���
	COORD  cursorPosition = {
		(SHORT)cursorPositionX,    // X���W
		(SHORT)cursorPositionY     // Y���W
	};

	// �J�[�\���ʒu�̐ݒ�
	SetConsoleCursorPosition(screenInfo.hOutput, cursorPosition);
}

/// <summary>
/// �J�[�\���̍��W�擾
/// </summary>
/// <param name="pCursorPositionX">�J�[�\����X���W���i�[����ϐ��ւ̃|�C���^</param>
/// <param name="pCursorPositionY">�J�[�\����Y���W���i�[����ϐ��ւ̃|�C���^</param>
void Console::GetCursorPosition(int* pCursorPositionX, int* pCursorPositionY) {
	// �X�N���[���o�b�t�@�Ɋւ�����
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;    

	// �X�N���[���o�b�t�@�Ɋւ�����̎擾
	if (GetConsoleScreenBufferInfo(screenInfo.hOutput, &screenBufferInfo) == 0) {
		ExitWithMessage("�X�N���[���o�b�t�@�Ɋւ�����̎擾�Ɏ��s���܂���");
	}

	// �J�[�\���ʒu�̏�������
	*pCursorPositionX = screenBufferInfo.dwCursorPosition.X;
	*pCursorPositionY = screenBufferInfo.dwCursorPosition.Y;
}

/// <summary>
/// �J�[�\���̈ړ�
/// </summary>
/// <param name="movementX"> X�����̈ړ���</param>
/// <param name="movementY"> Y�����̈ړ���</param>
void Console::MoveCursorPosition(int movementX, int movementY) {
	int cursorPositionX;    // �J�[�\����X���W
	int cursorPositionY;    // �J�[�\����Y���W

	// �J�[�\���ʒu�̐ݒ�
	GetCursorPosition(&cursorPositionX, &cursorPositionY);
	SetCursorPosition((cursorPositionX + movementX), (cursorPositionY + movementY));
}

/// <summary>
/// �L�[���͂̎擾
/// </summary>
/// <returns>
/// �L�[�R�[�h �L�[���͂���(����L�[�̏ꍇ�͉��z�L�[�R�[�h��ԋp)
/// 0              �L�[���͂Ȃ�
/// </returns>
int Console::GetKeyInput() {
	// ���͂��ꂽ�L�[�̃R�[�h
	int code = 0;    

	// ���͂��ꂽ�L�[�̎擾
	if (_kbhit()) {
		// ���̓L�[�̎擾
		code = _getch();    

		// ���ꕶ���̏ꍇ
		if (code == 0xE0 || code == 0x00)    
		{
			code = _getch() | 0x80;
		}
	}

	// �����R�[�h�̕ԋp
	return code;
}

/// <summary>
/// �L�[���������܂őҋ@
/// </summary>
/// <returns>
/// ���͂��ꂽ�L�[�̃R�[�h��ԋp
/// </returns>
int Console::WaitKey() {
	// ���͂��ꂽ�L�[�̃R�[�h
	int code;    

	// ���͏��� 
	while (1) {
		// ���̓L�[�̎擾
		code = GetKeyInput();    

		// ���͏����̍��v����
		if (code != 0) {
			return code;
		}
	}
}

/// <summary>
/// �L�[���������܂őҋ@(���b�Z�[�W�t��)
/// </summary>
/// <param name="message">�o�̓��b�Z�[�W</param>
/// <returns>
/// ���͂��ꂽ�L�[�̃R�[�h��ԋp
/// </returns>
int Console::WaitKeyWithMessage(const char* message) {
	// ���b�Z�[�W�̕\��
	std::cout << message << std::endl;

	// ���͏��� 
	return WaitKey();
}

/// <summary>
/// �w�肳�ꂽ�L�[���������܂őҋ@
/// </summary>
/// <param name="codeList">�L�[�R�[�h�̃��X�g</param>
/// <param name="numItems">���X�g�̃A�C�e����</param>
/// <returns>
/// �I�����̒�������͂��ꂽ�L�[�̃R�[�h��ԋp
/// </returns>
int Console::WaitKeyWithKeyCode(const int codeList[], int numItems) {
	int code;    // ���͂��ꂽ�L�[�̃R�[�h
	int i;       // ���[�v�p

	// ���͏���
	while (1) {
		// ���̓L�[�̎擾
		code = GetKeyInput();    

		// ���͏����̍��v���� 
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
/// �����l�̓���
/// </summary>
/// <returns>
/// ���͂��ꂽ�����l
/// </returns>
int Console::InputInteger() {
	int digit = 0;    // ��
	int number = 0;    // ���͒l
	int code;          // ���͂��ꂽ�L�[�̃R�[�h

	// ���͏��� 
	while (1) {
		// ���̓L�[�̎擾
		code = GetKeyInput();    

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


	// ���͂��ꂽ�����l��ԋp ----------------------------
	return number;
}

/// <summary>
/// ��ʂ̃N���A
/// </summary>
void Console::ClearScreen() {
	DWORD length = screenInfo.screenSize.X * screenInfo.screenSize.Y;    // �������ޕ�����
	COORD writeCoord = { 0, 0 };                                         // �������������ރX�N���[���o�b�t�@���W
	DWORD numCharactersWritten;                                          // �X�N���[���o�b�t�@�Ɏ��ۂɏ������܂ꂽ������

	// ��ʂ��N���A
	FillConsoleOutputCharacter(screenInfo.hOutput, ' ', length, writeCoord, &numCharactersWritten);
	FillConsoleOutputAttribute(screenInfo.hOutput, screenInfo.textAttributes, length, writeCoord, &numCharactersWritten);

	SetCursorPosition(0, 0);
}

/// <summary>
/// �����F�̐ݒ�
/// </summary>
/// <param name="textColor">�����F</param>
void Console::SetTextColor(ConsoleColor textColor) {
	// �����F�̕ύX
	screenInfo.textAttributes = (screenInfo.textAttributes & 0xF0) | (int)textColor;

	// �����̑����̍X�V
	if (SetConsoleTextAttribute(screenInfo.hOutput, screenInfo.textAttributes) == 0) {
		ExitWithMessage("�����F�̕ύX�Ɏ��s���܂����B");
	}
}

/// <summary>
/// �w�i�F�̐ݒ�
/// </summary>
/// <param name="backColor">�w�i�F</param>
void Console::SetBackColor(ConsoleColor backColor) {
	// �w�i�F�̕ύX
	screenInfo.textAttributes = (screenInfo.textAttributes & 0x0F) | ((int)backColor << 4);

	// �����̑����̍X�V
	if (SetConsoleTextAttribute(screenInfo.hOutput, screenInfo.textAttributes) == 0) {
		ExitWithMessage("�w�i�F�̕ύX�Ɏ��s���܂����B");
	}
}

/// <summary>
/// ���݂̃R���\�[����ʂɊւ�������擾
/// </summary>
/// <returns>
/// ���݂̃R���\�[����ʂɊւ�����
/// </returns>
Console::ScreenInfo  Console::GetCurrentConsoleScreenInfo() {
	HANDLE                     hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);    // �W���o�̓f�o�C�X�̃n���h��
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;                                // �X�N���[���o�b�t�@�Ɋւ�����
	ScreenInfo                 screenInfo;                                      // �R���\�[����ʂɊւ�����

	// �X�N���[���o�b�t�@�Ɋւ�����̎擾
	if (GetConsoleScreenBufferInfo(hStdOutput, &screenBufferInfo) == 0) {
		ExitWithMessage("�X�N���[���o�b�t�@�Ɋւ�����̎擾�Ɏ��s���܂���");
	}


	// �R���\�[����ʂɊւ�����̐ݒ� ------------------
	screenInfo.hOutput = hStdOutput;
	screenInfo.screenSize.X = screenBufferInfo.srWindow.Right + 1;
	screenInfo.screenSize.Y = screenBufferInfo.srWindow.Bottom + 1;
	screenInfo.textAttributes = screenBufferInfo.wAttributes;


	// �R���\�[����ʂɊւ�����̕ԋp ------------------
	return screenInfo;
}

/// <summary>
/// ��ʂ̊g��E�k��
/// </summary>
/// <param name="dx">���������̍���</param>
/// <param name="dy">���������̍���</param>
void Console::ResizeScreen(SHORT dx, SHORT dy) {
	// �X�N���[���o�b�t�@�̃T�C�Y
	COORD  screenBufferSize = {
		screenInfo.screenSize.X + dx,    // ��
		screenInfo.screenSize.Y + dy     // ����
	};

	// �E�B���h�E��`
	SMALL_RECT windowRect = {
		0,                         // ��
		0,                         // ��
		screenBufferSize.X - 1,    // �E
		screenBufferSize.Y - 1     // ��
	};

	// ��ʂ̃T�C�Y�ύX
	if (dx > 0 || dy > 0) {
		// �g��̏ꍇ
		if (!SetConsoleScreenBufferSize(screenInfo.hOutput, screenBufferSize)) {
			ExitWithMessage("�X�N���[���o�b�t�@�̃T�C�Y�̕ύX�Ɏ��s���܂����B");
		}

		if (!SetConsoleWindowInfo(screenInfo.hOutput, TRUE, &windowRect)) {
			ExitWithMessage("�E�B���h�E�̃T�C�Y�̕ύX�Ɏ��s���܂����B");
		}
	}
	else {
		// �k���̏ꍇ
		if (!SetConsoleWindowInfo(screenInfo.hOutput, TRUE, &windowRect)) {
			ExitWithMessage("�E�B���h�E�̃T�C�Y�̕ύX�Ɏ��s���܂����B");
		}

		if (!SetConsoleScreenBufferSize(screenInfo.hOutput, screenBufferSize)) {
			ExitWithMessage("�X�N���[���o�b�t�@�̃T�C�Y�̕ύX�Ɏ��s���܂����B");
		}
	}

	// ��ʂɊւ�������̃T�C�Y�����X�V
	screenInfo.screenSize = screenBufferSize;
}

/// <summary>
/// �����I��(���b�Z�[�W�t��)
/// </summary>
/// <param name="message">�o�̓��b�Z�[�W</param>
void Console::ExitWithMessage(const char* message) {
	WaitKeyWithMessage(message);

	exit(-1);
}