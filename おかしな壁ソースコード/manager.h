/*=============================================================================

 �Ǘ������w�b�_[ manager.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 �C���N���[�h�K�[�h
-----------------------------------------------------------------------------*/
#ifndef _MANAGER_H_
#define _MANAGER_H_

/*-----------------------------------------------------------------------------
 �C���N���[�h�t�@�C��
-----------------------------------------------------------------------------*/
#include <Windows.h>
#include <d3dx9.h>

// ���͏����p�̃w�b�_
#include "input.h"

// Music
#include <XAudio2.h>

// ���w
#define _USE_MATH_DEFINES
#include <math.h>

// ���ڃ��C�u�����Ƀ����N�ł���v���O�}�R�����g�iVS�݂̗̂��Z�j
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

/*-----------------------------------------------------------------------------
 �}�N����`
-----------------------------------------------------------------------------*/
// �Q�ƃJ�E���^�̃f�N�������g
#define SAFE_RELEASE(p) { if(p) { (p) -> Release(); (p) = NULL; } }

// �������̉��
#define SAFE_DELETE(p)     { if(p != NULL) { delete (p); (p) = NULL; } }
#define SAFE_DELETE_Ex(p)  { if(p != NULL) { (p) -> Uninit(); delete (p); (p) = NULL; } }
#define SAFE_DELETE_MUL(p) { if(p != NULL) { delete[] (p); (p) = NULL; } }

// �E�B���h�E�T�C�Y
#define SCREEN_WIDTH  (1000)	// ��
#define SCREEN_HEIGHT (600)		// ����

/*-----------------------------------------------------------------------------
 �O���錾
-----------------------------------------------------------------------------*/
class CInputKeyboard;
class CInputGamePad;
class CMode;
class CSound;
class CFade;

/*-----------------------------------------------------------------------------
 �N���X��`
-----------------------------------------------------------------------------*/
class CManager
{
	private:

		// �C���v�b�g�F�L�[�{�[�h
		static CInputKeyboard *m_pInputKeyboard;

		// �C���v�b�g�F�Q�[���p�b�h
		static CInputGamePad *m_pInputGamePad;

		// ���[�h
		static CMode *m_pMode;

		// �T�E���h
		static CSound *m_Sound;

		// �t�F�[�h
		static CFade *m_pFade;

	public:

		// �R���X�g���N�^ & �f�X�N�g���N�^
		CManager() {}
		virtual ~CManager() {}

		// �e�����֐�
		static HRESULT Init  (HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
		static void    Uninit(void);
		static void    Update(void);
		static void    Draw  (void);

		// �C���v�b�g�F�L�[�{�[�h
		static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }

		// �C���v�b�g�F�Q�[���p�b�h
		static CInputGamePad *GetInputGamePad(void) { return m_pInputGamePad; }

		// ���[�h
		static void SetMode( CMode *pMode );
		static void SetMode( CMode *pMode , int StageID);

		static CSound* GetSound(void){ return m_Sound; }

		// �t�F�[�h
		static CFade *GetFade(void) { return m_pFade; };

		// �X�e�[�W�ԍ��m��
		static int m_nNowStage;

};

/*-----------------------------------------------------------------------------
 �C���N���[�h�G���h
-----------------------------------------------------------------------------*/
#endif