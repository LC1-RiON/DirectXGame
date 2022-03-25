#pragma once
#include <Windows.h>
class WinApp
{
private:
	// �E�B���h�E�n���h��
	HWND hwnd = nullptr;
	// �E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX wClass{};

public:// �萔
	static const int window_width = 1280;	// �E�B���h�E����
	static const int window_height = 720;	// �E�B���h�E�c��

public:// �ÓI�����o�֐�
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public:// �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �Q�b�^�[HWND
	/// </summary>
	/// <returns>hwnd �E�B���h�E�n���h��</returns>
	HWND GetHwnd() { return hwnd; }

	/// <summary>
	/// �Q�b�^�[HINSTANCE
	/// </summary>
	/// <returns>hInstance .exe�ւ̃n���h��</returns>
	HINSTANCE GetHInstance() { return wClass.hInstance; }

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

	/// <summary>
	/// ���b�Z�[�W�̏���
	/// </summary>
	/// <returns>TorF �I�����b�Z�[�W</returns>
	bool ProcessMessage();
};
