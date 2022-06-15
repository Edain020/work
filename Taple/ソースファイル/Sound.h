/*
InitSound関数をLoadTexture関数より後に呼び出すとエラー
※内部でCOMオブジェクトを利用するため

リスナー
音を聞くための「耳」に相当。3Dサウンドで必要。
ソース
音を発する「音源」に相当。スピーカー。XAudio2ではVoiceと呼ばれる。
バッファ
音データを格納しておくバッファ。WAVファイル、OGGファイルなどからロード。
 */
#ifndef __SOUND_H__
#define __SOUND_H__

#include <xaudio2.h>

#pragma comment(lib, "xaudio2.lib")

//----------
// プロトタイプ宣言
//----------
HRESULT InitSound(void);
void UninitSound(void);

class Sound
{
public:
	Sound()
		: m_pSound(nullptr)
		, m_pSpeaker(nullptr)
		, m_fVolume(1.0f)
	{}
	~Sound() {}

	// サウンドの読み込み
	void Load(const char *file, bool loop = false);
	// サウンドの再生
	void Play(void);
	// サウンドの停止
	void Stop(void);
	// 音量設定
	void SetVolume(float volume);

private:
	XAUDIO2_BUFFER		*m_pSound;		// 音
	IXAudio2SourceVoice *m_pSpeaker;	// 音を鳴らしているオブジェクト
	float m_fVolume;	// 音量
};

#endif // __SOUND_H__