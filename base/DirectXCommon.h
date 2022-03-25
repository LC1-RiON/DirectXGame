#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dx12.h>

#include "WinApp.h"
#pragma once
class DirectXCommon
{
private:
	WinApp* winApp = nullptr;

	// �f�o�C�X
	Microsoft::WRL::ComPtr<ID3D12Device> dev;
	// DXGI�t�@�N�g��
	Microsoft::WRL::ComPtr<IDXGIFactory6> dxgiFactory;
	// �R�}���h�A���P�[�^
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;
	// �R�}���h���X�g
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList;
	// �R�}���h�L���[
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> cmdQueue;
	// �X���b�v�`�F�[��
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapchain;
	// RTV�p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	// �[�x�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer;
	// DSV�p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;
	// �t�F���X
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	// �o�b�N�o�b�t�@
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
	// �t�F���X�l
	UINT64 fenceVal = 0;

private:
	/// <summary>
	/// �f�o�C�X������
	/// </summary>
	void InitializeDevice();
	/// <summary>
	/// �R�}���h�֘A������
	/// </summary>
	void InitializeCommand();
	/// <summary>
	/// �X���b�v�`�F�[��������
	/// </summary>
	void InitializeSwapchain();
	/// <summary>
	/// �����_�[�^�[�Q�b�g�r���[������
	/// </summary>
	void InitializeRenderTargetView();
	/// <summary>
	/// �[�x�o�b�t�@������
	/// </summary>
	void InitializeDepthBuffer();
	/// <summary>
	/// �t�F���X������
	/// </summary>
	void InitializeFence();

public:	// �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WinApp* winApp);
	/// <summary>
	/// �`��O����
	/// </summary>
	void PreDraw();
	/// <summary>
	/// �`��㏈��
	/// </summary>
	void PostDraw();
	/// <summary>
	/// �f�o�C�X�擾
	/// </summary>
	ID3D12Device* GetDev() { return dev.Get(); }
	/// <summary>
	/// �R�}���h���X�g�擾
	/// </summary>
	ID3D12GraphicsCommandList* GetCmdList() { return cmdList.Get(); }
};
