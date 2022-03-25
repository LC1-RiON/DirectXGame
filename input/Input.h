#include<windows.h>
#include<wrl.h>
#define DIRECTINPUT_VERSION		0x0800		// DirectInput�o�[�W�����w��
#include<dinput.h>

#include "WinApp.h"
#pragma once
class Input
{
public:
	static Input* GetInstance();

public:
	// namespace�̏ȗ�
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	// WindowsAPI
	WinApp* winApp = nullptr;
	// DirectInput�C���X�^���X
	ComPtr<IDirectInput8> dinput = nullptr;
	// �L�[�{�[�h�f�o�C�X
	ComPtr<IDirectInputDevice8> devkeyboard;
	// ���L�[���
	BYTE key[256] = {};
	// ���L�[���
	BYTE keyPre[256] = {};

public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �L�[���͔���
	/// </summary>
	/// <param name="keyNumber">�L�[�ԍ��iDIK_0,DIK_SPACE,etc..�j</param>
	/// <returns>�L�[�̓��͔���</returns>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	/// �L�[�g���K�[����
	/// </summary>
	/// <param name="keyNumber">�L�[�ԍ��iDIK_0,DIK_SPACE,etc..�j</param>
	/// <returns>�L�[�̃g���K�[����</returns>
	bool TriggerKey(BYTE keyNumber);
};

