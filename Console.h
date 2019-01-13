#pragma once
#include "Singleton.h"
#include <windows.h>


/// <summary>
/// ���z�L�[�R�[�h
/// </summary>
enum class KeyCode {
	KEY_BACKSPACE = 0x08,
	KEY_ENTER = 0x0D,
	KEY_ESC = 0x1B,
	KEY_SPACE = 0x20,
	KEY_UP = 0x48 | 0x80,
	KEY_LEFT = 0x4B | 0x80,
	KEY_RIGHT = 0x4D | 0x80,
	KEY_DOWN = 0x50 | 0x80,
};


/// <summary>
/// �����E�w�i�F
/// </summary>
enum class ConsoleColor {
	COLOR_BLACK,
	COLOR_DARK_BLUE,
	COLOR_DARK_GREEN,
	COLOR_DARK_CYAN,
	COLOR_DARK_RED,
	COLOR_DARK_MAGENTA,
	COLOR_DARK_YELLOW,
	COLOR_GRAY,
	COLOR_DARK_GRAY,
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_CYAN,
	COLOR_RED,
	COLOR_MAGENTA,
	COLOR_YELLOW,
	COLOR_WHITE,
};


/// <summary>
/// �J�[�\���̏��
/// </summary>
enum class CursorVisibility {
	CURSOR_INVISIBLE,
	CURSOR_VISIBLE
};

class Console : Singleton<Console> {

	friend Singleton<Console>;

private:
	//��ʏ��
	struct ScreenInfo {
		HANDLE hOutput;           // �o�̓f�o�C�X�̃n���h��
		COORD  screenSize;        // ��ʃT�C�Y
		WORD   textAttributes;    // �����̑O�i�F�����Ɣw�i�F����
	};

private:
	ScreenInfo screenInfo;

private:
	Console();
	~Console() = default;

private:
	ScreenInfo GetCurrentConsoleScreenInfo(void);		// �R���\�[����ʂ̏�����
	void       ResizeScreen(SHORT dx, SHORT dy);		// ��ʂ̃T�C�Y�ύX
	void       ExitWithMessage(const char* message);	// �����I��(���b�Z�[�W�t��)

//�R���\�[������֘A�̊֐�
public:
	void SetScreenSize(int screenWidth, int screenHeight);    // ��ʃT�C�Y��ݒ�
	int  GetScreenWidth(void);                                // ��ʕ��̎擾
	int  GetScreenHeight(void);                               // ��ʍ����̎擾
	void SetFontSize(int fontSize);                           // �t�H���g�T�C�Y�̐ݒ�
	int  GetFontSize(void);                                   // �t�H���g�T�C�Y�̎擾

//�J�[�\������p�֐�
public:	
	void SetCursorVisibility(CursorVisibility cursorState);                  // �J�[�\���̕\���E��\���؂�ւ�
	void SetCursorPosition(int cursorPositionX, int cursorPositionY);        // �J�[�\���̈ʒu�ݒ�
	void GetCursorPosition(int* pCursorPositionX, int* pCursorPositionY);    // �J�[�\���̈ʒu�擾
	void MoveCursorPosition(int movementX, int movementY);                   // �J�[�\���̈ړ�

//���͐���p�֐�
public:
	int GetKeyInput(void);                                         // �L�[���͂̎擾
	int WaitKey(void);                                             // �L�[���������܂őҋ@
	int WaitKeyWithMessage(const char* message);                   // �L�[���������܂őҋ@(���b�Z�[�W�t��)
	int WaitKeyWithKeyCode(const int codeList[], int numItems);    // �w��L�[�̓��͑҂�
	int InputInteger(void);                                        // �����l�̓���

//�o�͐���p�֐�
public:
	void ClearScreen(void);                       // ��ʂ̃N���A
	void SetTextColor(ConsoleColor textColor);    // �����F�̐ݒ�
	void SetBackColor(ConsoleColor backColor);    // �w�i�F�̐ݒ�

};