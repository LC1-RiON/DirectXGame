#include "DebugText.h"

DebugText* DebugText::GetInstance()
{
    static DebugText instance;

    return &instance;
}

void DebugText::Initialize(SpriteCommon* spriteCmn, UINT texnumber)
{
    assert(spriteCmn);

    spriteCommon = spriteCmn;

    // 全てのスプライトデータについて
    for (int i = 0; i < _countof(sprites); i++)
    {
        // スプライトを生成する
        sprites[i] = Sprite::Create(texnumber, { 0,0 });
    }
}

void DebugText::Finalize()
{
    for (auto& sprite : sprites) {
        delete sprite;
    }
}

void DebugText::Print(const std::string& text, float x, float y, float scale)
{
    // 全ての文字について
    for (int i = 0; i < text.size(); i++)
    {
        // 最大文字数超過
        if (spriteIndex >= maxCharCount) {
            break;
        }

        // 1文字取り出す(※ASCIIコードでしか成り立たない)
        const unsigned char& character = text[i];

        // ASCIIコードの2段分飛ばした番号を計算
        int fontIndex = character - 32;
        if (character >= 0x7f) {
            fontIndex = 0;
        }

        int fontIndexY = fontIndex / fontLineCount;
        int fontIndexX = fontIndex % fontLineCount;

        // 座標計算
        sprites[spriteIndex]->SetPosition({ x + fontWidth * scale * i, y, 0 });
        sprites[spriteIndex]->SetTexLeftTop({ (float)fontIndexX * fontWidth, (float)fontIndexY * fontHeight });
        sprites[spriteIndex]->SetTexSize({ fontWidth, fontHeight });
        sprites[spriteIndex]->SetSize({ fontWidth * scale, fontHeight * scale });
        // 頂点バッファ転送
        sprites[spriteIndex]->TransferVertexBuffer();
        // 更新
        sprites[spriteIndex]->Update();

        // 文字を１つ進める
        spriteIndex++;
    }
}

// まとめて描画
void DebugText::DrawAll()
{
    // 全ての文字のスプライトについて
    for (int i = 0; i < spriteIndex; i++)
    {
        // スプライト描画
        sprites[i]->Draw();
    }

    spriteIndex = 0;
}
