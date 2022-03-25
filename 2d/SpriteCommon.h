#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
// �p�C�v���C���Z�b�g
struct PipelineSet
{
    // �p�C�v���C���X�e�[�g�I�u�W�F�N�g
    Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelinestate;
    // ���[�g�V�O�l�`��
    Microsoft::WRL::ComPtr<ID3D12RootSignature> rootsignature;
};

class SpriteCommon
{
public:
	// �e�N�X�`���̍ő喇��
	static const int kSpriteSRVCount = 512;

    static SpriteCommon* GetInstance();

private:
    // �p�C�v���C���Z�b�g
    PipelineSet pipelineSet;
    // �ˉe�s��
    DirectX::XMMATRIX matProjection{};
    // �e�N�X�`���p�f�X�N���v�^�q�[�v�̐���
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;
    // �e�N�X�`�����\�[�X�i�e�N�X�`���o�b�t�@�j�̔z��
    Microsoft::WRL::ComPtr<ID3D12Resource> texBuff[kSpriteSRVCount];
    // �f�o�C�X��
    ID3D12Device* device = nullptr;
    // �R�}���h���X�g��
    ID3D12GraphicsCommandList* commandList = nullptr;

public:
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="dev">�f�o�C�X</param>
    /// <param name="cmdList">�R�}���h���X�g</param>
    /// <param name="window_width">�E�B���h�E����</param>
    /// <param name="window_height">�E�B���h�E�c��</param>
    void Initialize(ID3D12Device* dev, ID3D12GraphicsCommandList* cmdList, int window_width, int window_height);

    /// <summary>
    /// �`��O����
    /// </summary>
    void PreDraw();

    /// <summary>
    /// �e�N�X�`���ǂݍ���
    /// </summary>
    /// <param name="texnumber"></param>
    /// <param name="filename"></param>
    void LoadTexture(UINT texnumber, const wchar_t* filename);

    /// <summary>
    /// ���[�g�f�X�N���v�^�e�[�u���ݒ�
    /// </summary>
    /// <param name="rootParameterIndex">���[�g�p�����[�^�ԍ�</param>
    /// <param name="texNumber">�e�N�X�`���ԍ�</param>
    void SetGraphicsRootDescriptorTable(UINT rootParameterIndex, UINT texNumber);

    /// <summary>
    /// GETTER-�e�N�X�`��
    /// </summary>
    /// <param name="texNumber">�e�N�X�`���ԍ�</param>
    /// <returns>�e�N�X�`�����\�[�X</returns>
    ID3D12Resource* GetTexBuff(int texNumber);
    /// <summary>
    /// GETTER-�f�o�C�X
    /// </summary>
    /// <returns>�f�o�C�X�f�[�^</returns>
    ID3D12Device* GetDevice() { return device; }
    /// <summary>
    /// GETTER-�ˉe�s��
    /// </summary>
    /// <returns></returns>
    const DirectX::XMMATRIX& GetMatProjection() { return matProjection; }
    /// <summary>
    /// GETTER-�R�}���h���X�g
    /// </summary>
    /// <returns></returns>
    ID3D12GraphicsCommandList* GetCommandList() { return commandList; }

private:
    /// <summary>
    /// �p�C�v���C������
    /// </summary>
    /// <param name="dev"></param>
    void CreateGraphicsPipeline(ID3D12Device* dev);
};

