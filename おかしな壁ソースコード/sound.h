//=============================================================================
//
// サウンド処理 [sound.h]
// Author : TOMOHARU OKANO
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*********************************************************
// インクルードファイル
//*********************************************************
#include "manager.h"

//*********************************************************
// サウンドクラス
//*********************************************************
class CSound
{
	public:

		CSound();
		~CSound();

		// サウンドファイル
		typedef enum
		{
			// BGM
			TITLE_BGM = 0,			// BGM
			SELECT_BGM ,			// BGM
			GAME_BGM ,			// BGM

			// SE
			SE_CURSOR,			// カーソル
			SE_KETTEI,			// 決定
			SE_CANCEL,			// キャンセル
			SE_WALK,			// 歩く
			SE_JUMP,			// ジャンプ
			SE_SWITCH_ON,		// スイッチ雄
			SE_SWITCH_EFFECT,	// スイッチ壁消える
			SE_SKILL_SWAP,		// スキルスワップ

			// NUM MAX
			SOUND_LABEL_MAX
		} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);
	void SetVolume(SOUND_LABEL label, float fValue);

private:
	// パラメータ構造体
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウンタ
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD dwFormat, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ

	static PARAM m_aParam[SOUND_LABEL_MAX];					// パラメータ
};

#endif
