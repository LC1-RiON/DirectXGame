#pragma once

#include <xaudio2.h>
#include <cstdint>
#include <wrl.h>
#include <map>
#include <string>

class Audio
{
public:
    static Audio* GetInstance();

public:
    // チャンクヘッダ
    struct ChunkHeader
    {
        char id[4]; // チャンク毎のID
        int32_t size;  // チャンクサイズ
    };

    // RIFFヘッダチャンク
    struct RiffHeader
    {
        ChunkHeader chunk;   // "RIFF"
        char type[4]; // "WAVE"
    };

    // FMTチャンク
    struct FormatChunk
    {
        ChunkHeader chunk; // "fmt "
        WAVEFORMATEX fmt; // 波形フォーマット
    };

    // 音声データ
    struct SoundData
    {
        // 波形フォーマット
        WAVEFORMATEX wfex;
        // バッファの先頭アドレス
        BYTE* pBuffer;
        // バッファのサイズ
        unsigned int bufferSize;
    };

private:
    // XAudio2インスタンス
    Microsoft::WRL::ComPtr<IXAudio2> xAudio2;
    // サウンドデータ連想配列
    std::map<std::string, SoundData> soundDatas;
    // サウンド格納ディレクトリ
    std::string directoryPath;

public:
    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize(const std::string directPath = "Resources/");

    /// <summary>
    /// 終了処理
    /// </summary>
    void Finalize();

    /// <summary>
    /// .wavファイル読み込み
    /// </summary>
    /// <param name="filename">.wavファイル名</param>
    void LoadWave(const std::string& filename);

    /// <summary>
    /// サウンドデータ開放
    /// </summary>
    /// <param name="soundData">サウンドデータ</param>
    void Unload(SoundData* soundData);

    /// <summary>
    /// .wav音声再生
    /// </summary>
    /// <param name="filename">サウンドデータ名</param>
    void PlayWave(const std::string& filename);
};

