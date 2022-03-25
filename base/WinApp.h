#pragma once
#include <Windows.h>
class WinApp
{
private:
	// ウィンドウハンドル
	HWND hwnd = nullptr;
	// ウィンドウクラスの設定
	WNDCLASSEX wClass{};

public:// 定数
	static const int window_width = 1280;	// ウィンドウ横幅
	static const int window_height = 720;	// ウィンドウ縦幅

public:// 静的メンバ関数
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public:// メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// ゲッターHWND
	/// </summary>
	/// <returns>hwnd ウィンドウハンドル</returns>
	HWND GetHwnd() { return hwnd; }

	/// <summary>
	/// ゲッターHINSTANCE
	/// </summary>
	/// <returns>hInstance .exeへのハンドル</returns>
	HINSTANCE GetHInstance() { return wClass.hInstance; }

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

	/// <summary>
	/// メッセージの処理
	/// </summary>
	/// <returns>TorF 終了メッセージ</returns>
	bool ProcessMessage();
};
