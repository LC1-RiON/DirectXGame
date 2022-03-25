#pragma once
#include "DirectXMath.h"

#include <d3dx12.h>
#include <d3d12.h>
#include <wrl.h>
#include <vector>
#include <string>
class Model
{
private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	// ���_�f�[�^�\����
	struct VertexPosNormalUv
	{
		DirectX::XMFLOAT3 pos; // xyz���W
		DirectX::XMFLOAT3 normal; // �@���x�N�g��
		DirectX::XMFLOAT2 uv;  // uv���W
	};

	// �}�e���A��
	struct Material
	{
		std::string name;	// �}�e���A����
		DirectX::XMFLOAT3 ambient;	// �A���r�G���g�e���x
		DirectX::XMFLOAT3 diffuse;	// �f�B�t���[�Y�e���x
		DirectX::XMFLOAT3 specular;	// �X�y�L�����[�e���x
		float alpha;		// �A���t�@
		std::string textureFilename;	// �e�N�X�`���t�@�C����
		// �R���X�g���N�^
		Material() {
			ambient = { 0.3f, 0.3f, 0.3f };
			diffuse = { 0.0f, 0.0f, 0.0f };
			specular = { 0.0f, 0.0f, 0.0f };
			alpha = 1.0f;
		}
	};

	// �萔�o�b�t�@�p�f�[�^�\����B1
	struct ConstBufferDataB1
	{
		DirectX::XMFLOAT3 ambient; // �A���r�G���g�W��
		float pad1; // �p�f�B���O
		DirectX::XMFLOAT3 diffuse; // �f�B�t���[�Y�W��
		float pad2; // �p�f�B���O
		DirectX::XMFLOAT3 specular; // �X�y�L�����[�W��
		float alpha;	// �A���t�@
	};

private:	// �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device;

public:	// �ÓI�����o�֐�
	/// <summary>
	/// .obj����3D���f���ǂݍ���
	/// </summary>
	/// <returns>Model* ���f���f�[�^</returns>
	static Model* LoadFromOBJ(const std::string& modelname);

	/// <summary>
	/// Setter_DEVICE
	/// </summary>
	/// <param name="device">�f�o�C�X����</param>
	static void SetDevice(ID3D12Device* device) { Model::device = device; }

private:	// �����o�ϐ�
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff;
	// �}�e���A��
	Material material;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView;
	// ���_�f�[�^�z��
	//VertexPosNormalUv vertices[vertexCount];
	std::vector<VertexPosNormalUv> vertices;
	// ���_�C���f�b�N�X�z��
	//unsigned short indices[planeCount * 3];
	std::vector<unsigned short> indices;
	// �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texbuff;
	// �f�X�N���v�^�T�C�Y
	UINT descriptorHandleIncrementSize;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// �f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffB1;

private:	// ����J�����o�֐�
	/// <summary>
	/// .obj����3D���f���ǂݍ���
	/// </summary>
	void LoadFromOBJInternal(const std::string& modelname);

	/// <summary>
	/// �f�X�N���v�^�q�[�v�̏�����
	/// </summary>
	/// <returns></returns>
	bool InitializeDescriptorHeap();

	/// <summary>
	/// �}�e���A���ǂݍ���
	/// </summary>
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <returns>����</returns>
	bool LoadTexture(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// �e��o�b�t�@����
	/// </summary>
	void CreateBuffers();

public:	// �����o�֐�
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="cmdList">�`��R�}���h���X�g</param>
	/// <param name="rootParamIndexMaterial">�}�e���A���p���[�g�p�����[�^�ԍ�</param>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParamIndexMaterial);
};
