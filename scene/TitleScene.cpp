#include "TitleScene.h"
#include "SceneManager.h"
#include "Audio.h"
#include "Input.h"
#include "DebugText.h"

void TitleScene::Initialize()
{
    // スプライト共通テクスチャ読み込み
    SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/beastealthTitle.png");

    // スプライトの生成
    sprite = Sprite::Create(1, { 0,0 }, false, false);
}

void TitleScene::Finalize()
{
    delete sprite;
}

void TitleScene::Update()
{
    Input* input = Input::GetInstance();

    count++;
    float spritePos = count / 10 * -1280.0f;
    if (spritePos <= -1280.0f * 5) {
        spritePos = -1280 * 5;
    }
    sprite->SetPosition({ spritePos,0,0 });

    if (input->TriggerKey(DIK_SPACE)) {
        // シーン切替
        SceneManager::GetInstance()->ChangeScene("GAMEPLAY");
    }

    // スプライト更新
    sprite->Update();
}

void TitleScene::Draw()
{
    // スプライト描画前処理
    SpriteCommon::GetInstance()->PreDraw();

    /// <summary>
    /// スプライト描画処理の追加位置
    /// </summary>

    // スプライト描画
    sprite->Draw();
}
