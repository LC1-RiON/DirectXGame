#include<windows.h>
#include<wrl.h>
#define DIRECTINPUT_VERSION		0x0800		// DirectInputバージョン指定
#include<dinput.h>

#include "WinApp.h"
#pragma once
class Input
{
public:
	static Input* GetInstance();

public:
	// namespaceの省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	// WindowsAPI
	WinApp* winApp = nullptr;
	// DirectInputインスタンス
	ComPtr<IDirectInput8> dinput = nullptr;
	// キーボードデバイス
	ComPtr<IDirectInputDevice8> devkeyboard;
	// 現キー情報
	BYTE key[256] = {};
	// 旧キー情報
	BYTE keyPre[256] = {};

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// キー入力判定
	/// </summary>
	/// <param name="keyNumber">キー番号（DIK_0,DIK_SPACE,etc..）</param>
	/// <returns>キーの入力判定</returns>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	/// キートリガー判定
	/// </summary>
	/// <param name="keyNumber">キー番号（DIK_0,DIK_SPACE,etc..）</param>
	/// <returns>キーのトリガー判定</returns>
	bool TriggerKey(BYTE keyNumber);
};

