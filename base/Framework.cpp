#include "Framework.h"

void Framework::Run()
{
    // ゲーム初期化
    Initialize();

    // ゲームループ
    while (true)
    {
        // ゲーム更新
        Update();

        // 終了リクエストでループアウト
        if (GetEnd()) {
            break;
        }

        // ゲーム描画
        Draw();
    }

    // ゲーム後処理
    Finalize();
}

void Framework::Initialize()
{
    winApp = new WinApp();
    winApp->Initialize();

    // DirectX
    dxCommon = new DirectXCommon();
    dxCommon->Initialize(winApp);

    // インプット
    input = Input::GetInstance();
    input->Initialize(winApp);

    // オーディオ
    audio = Audio::GetInstance();
    audio->Initialize();

    // スプライト
    spriteCommon = SpriteCommon::GetInstance();
    spriteCommon->Initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->window_width, winApp->window_height);

    // デバッグテキスト
    debugText = DebugText::GetInstance();

    // デバッグテキスト用のテクスチャ番号を指定
    const int debugTextTexNumber = 0;
    // デバッグテキスト用のテクスチャ読み込み
    spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
    // デバッグテキスト初期化
    debugText->Initialize(spriteCommon, debugTextTexNumber);

    // 3Dオブジェクト静的初期化
    Object3d::StaticInitialize(dxCommon->GetDev(), dxCommon->GetCmdList(), WinApp::window_width, WinApp::window_height);
}

void Framework::Finalize()
{
    // デバッグテキスト
    debugText->Finalize();
    // オーディオ
    audio->Finalize();
    // DirectX
    delete dxCommon;
    // WindowsAPI
    winApp->Finalize();
    delete winApp;
}

void Framework::Update()
{
#pragma region ウィンドウメッセージ処理
    if (winApp->ProcessMessage()) {
        // ゲームループを抜ける
        endRequest = true;
        return;
    }
#pragma endregion ウィンドウメッセージ処理

    input->Update();

    SceneManager::GetInstance()->Update();
}

void Framework::Draw()
{
    // 描画前処理
    dxCommon->PreDraw();

    // シーン描画
    SceneManager::GetInstance()->Draw();

    // デバッグテキスト描画
    debugText->DrawAll();

    // 描画後処理
    dxCommon->PostDraw();
}
