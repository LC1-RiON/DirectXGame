#include "TitleScene.h"
#include "SceneManager.h"
#include "Audio.h"
#include "Input.h"
#include "DebugText.h"

void TitleScene::Initialize()
{
    // �X�v���C�g���ʃe�N�X�`���ǂݍ���
    SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/title.png");

    // �X�v���C�g�̐���
    sprite = Sprite::Create(1, { 0,0 }, false, false);
}

void TitleScene::Finalize()
{
    delete sprite;
}

void TitleScene::Update()
{
    Input* input = Input::GetInstance();

    if (input->TriggerKey(DIK_SPACE)) {
        // �V�[���ؑ�
        SceneManager::GetInstance()->ChangeScene("GAMEPLAY");
    }

    // �X�v���C�g�X�V
    sprite->Update();
}

void TitleScene::Draw()
{
    // �X�v���C�g�`��O����
    SpriteCommon::GetInstance()->PreDraw();

    /// <summary>
    /// �X�v���C�g�`�揈���̒ǉ��ʒu
    /// </summary>

    // �X�v���C�g�`��
    sprite->Draw();
}
