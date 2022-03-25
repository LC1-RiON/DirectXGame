#pragma once

#include "SpriteCommon.h"

#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>

class Sprite
{
public:
    // 頂点データ
    struct VertexPosUv
    {
        DirectX::XMFLOAT3 pos; // xyz座標
        DirectX::XMFLOAT2 uv;  // uv座標
    };

    // 定数バッファ用データ構造体
    struct ConstBufferData {
        DirectX::XMFLOAT4 color; // 色 (RGBA)
        DirectX::XMMATRIX mat;   // ３Ｄ変換行列
    };

private:
    //頂点バッファ;
    Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
    //頂点バッファビュー;
    D3D12_VERTEX_BUFFER_VIEW vbView{};
    //定数バッファ;
    Microsoft::WRL::ComPtr<ID3D12Resource> constBuff;
    // Z軸回りの回転角
    float rotation = 0.0f;
    // 座標
    DirectX::XMFLOAT3 position = { 0,0,0 };
    // ワールド行列
    DirectX::XMMATRIX matWorld;
    // 色(RGBA)
    DirectX::XMFLOAT4 color = { 1, 1, 1, 1 };
    // テクスチャ番号
    UINT textureNumber = 0;
    // 大きさ
    DirectX::XMFLOAT2 size = { 100, 100 };
    // アンカーポイント
    DirectX::XMFLOAT2 anchorpoint = { 0.5f, 0.5f };
    // 左右反転
    bool isFlipX = false;
    // 上下反転
    bool isFlipY = false;
    // テクスチャ左上座標
    DirectX::XMFLOAT2 texLeftTop = { 0, 0 };
    // テクスチャ切り出しサイズ
    DirectX::XMFLOAT2 texSize = { 100, 100 };
    // 非表示
    bool isInvisible = false;

public:
    /// <summary>
    /// スプライト生成
    /// </summary>
    /// <param name="texNumber">テクスチャ番号</param>
    /// <param name="anchor">アンカーポイント</param>
    /// <param name="flipX">X反転</param>
    /// <param name="flipY">Y反転</param>
    /// <returns>スプライトデータ</returns>
    static Sprite* Create(UINT texNumber, DirectX::XMFLOAT2 anchor = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize(UINT texNumber, DirectX::XMFLOAT2 anchor = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

    /// <summary>
    /// 頂点バッファ転送
    /// </summary>
    void TransferVertexBuffer();

    void SetPosition(const DirectX::XMFLOAT3& pos) { position = pos; }
    void SetRotation(float rot) { rotation = rot; }
    void SetSize(const DirectX::XMFLOAT2 siz) { size = siz; }
    void SetTexLeftTop(const DirectX::XMFLOAT2 txlt) { texLeftTop = txlt; }
    void SetTexSize(const DirectX::XMFLOAT2 txsz) { texSize = txsz; }
};

