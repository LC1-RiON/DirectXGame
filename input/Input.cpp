#include "Input.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

Input* Input::GetInstance()
{
    static Input instance;

    return &instance;
}

void Input::Initialize(WinApp* winApp)
{
    HRESULT result;
    this->winApp = winApp;

    // DirectInputインスタンス生成
    result = DirectInput8Create(
        winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
    // キーボードデバイス生成
    result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
    // 入力データ形式セット
    result = devkeyboard->SetDataFormat(&c_dfDIKeyboard); // 標準形式
    // 排他制御レベルセット
    result = devkeyboard->SetCooperativeLevel(
        winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Input::Update()
{
    HRESULT result;

    // 旧入力情報の保存
    memcpy(keyPre, key, sizeof(key));
    // キー情報の取得開始
    result = devkeyboard->Acquire();
    // 全キーの入力情報取得
    result = devkeyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNumber)
{
    if (key[keyNumber]) {
        return true;
    }

    return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
    if (key[keyNumber] && !keyPre[keyNumber]) {
        return true;
    }

    return false;
}
