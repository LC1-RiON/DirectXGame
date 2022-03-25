#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
// パイプラインセット
struct PipelineSet
{
    // パイプラインステートオブジェクト
    Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelinestate;
    // ルートシグネチャ
    Microsoft::WRL::ComPtr<ID3D12RootSignature> rootsignature;
};

class SpriteCommon
{
public:
	// テクスチャの最大枚数
	static const int kSpriteSRVCount = 512;

    static SpriteCommon* GetInstance();

private:
    // パイプラインセット
    PipelineSet pipelineSet;
    // 射影行列
    DirectX::XMMATRIX matProjection{};
    // テクスチャ用デスクリプタヒープの生成
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;
    // テクスチャリソース（テクスチャバッファ）の配列
    Microsoft::WRL::ComPtr<ID3D12Resource> texBuff[kSpriteSRVCount];
    // デバイス器
    ID3D12Device* device = nullptr;
    // コマンドリスト器
    ID3D12GraphicsCommandList* commandList = nullptr;

public:
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="dev">デバイス</param>
    /// <param name="cmdList">コマンドリスト</param>
    /// <param name="window_width">ウィンドウ横幅</param>
    /// <param name="window_height">ウィンドウ縦幅</param>
    void Initialize(ID3D12Device* dev, ID3D12GraphicsCommandList* cmdList, int window_width, int window_height);

    /// <summary>
    /// 描画前処理
    /// </summary>
    void PreDraw();

    /// <summary>
    /// テクスチャ読み込み
    /// </summary>
    /// <param name="texnumber"></param>
    /// <param name="filename"></param>
    void LoadTexture(UINT texnumber, const wchar_t* filename);

    /// <summary>
    /// ルートデスクリプタテーブル設定
    /// </summary>
    /// <param name="rootParameterIndex">ルートパラメータ番号</param>
    /// <param name="texNumber">テクスチャ番号</param>
    void SetGraphicsRootDescriptorTable(UINT rootParameterIndex, UINT texNumber);

    /// <summary>
    /// GETTER-テクスチャ
    /// </summary>
    /// <param name="texNumber">テクスチャ番号</param>
    /// <returns>テクスチャリソース</returns>
    ID3D12Resource* GetTexBuff(int texNumber);
    /// <summary>
    /// GETTER-デバイス
    /// </summary>
    /// <returns>デバイスデータ</returns>
    ID3D12Device* GetDevice() { return device; }
    /// <summary>
    /// GETTER-射影行列
    /// </summary>
    /// <returns></returns>
    const DirectX::XMMATRIX& GetMatProjection() { return matProjection; }
    /// <summary>
    /// GETTER-コマンドリスト
    /// </summary>
    /// <returns></returns>
    ID3D12GraphicsCommandList* GetCommandList() { return commandList; }

private:
    /// <summary>
    /// パイプライン生成
    /// </summary>
    /// <param name="dev"></param>
    void CreateGraphicsPipeline(ID3D12Device* dev);
};

