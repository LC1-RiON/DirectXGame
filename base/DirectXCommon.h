#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dx12.h>

#include "WinApp.h"
#pragma once
class DirectXCommon
{
private:
	WinApp* winApp = nullptr;

	// デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> dev;
	// DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory6> dxgiFactory;
	// コマンドアロケータ
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;
	// コマンドリスト
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList;
	// コマンドキュー
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> cmdQueue;
	// スワップチェーン
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapchain;
	// RTV用デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	// 深度バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer;
	// DSV用デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;
	// フェンス
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	// バックバッファ
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
	// フェンス値
	UINT64 fenceVal = 0;

private:
	/// <summary>
	/// デバイス初期化
	/// </summary>
	void InitializeDevice();
	/// <summary>
	/// コマンド関連初期化
	/// </summary>
	void InitializeCommand();
	/// <summary>
	/// スワップチェーン初期化
	/// </summary>
	void InitializeSwapchain();
	/// <summary>
	/// レンダーターゲットビュー初期化
	/// </summary>
	void InitializeRenderTargetView();
	/// <summary>
	/// 深度バッファ初期化
	/// </summary>
	void InitializeDepthBuffer();
	/// <summary>
	/// フェンス初期化
	/// </summary>
	void InitializeFence();

public:	// メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WinApp* winApp);
	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();
	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw();
	/// <summary>
	/// デバイス取得
	/// </summary>
	ID3D12Device* GetDev() { return dev.Get(); }
	/// <summary>
	/// コマンドリスト取得
	/// </summary>
	ID3D12GraphicsCommandList* GetCmdList() { return cmdList.Get(); }
};
