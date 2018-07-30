/*=============================================================================

 ���͏��� [input.h]
 Author : KIM NAKAMURA

=============================================================================*/
/*-----------------------------------------------------------------------------
 �C���N���[�h�K�[�h
-----------------------------------------------------------------------------*/
#ifndef _INPUT_H_
#define _INPUT_H_

/*-----------------------------------------------------------------------------
 �C���N���[�h�t�@�C��
-----------------------------------------------------------------------------*/
#define  DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <XInput.h>

/*-----------------------------------------------------------------------------
 �}�N����`
-----------------------------------------------------------------------------*/
#define NUM_KEY_MAX        (256)	// �L�[�ő吔

//�Q�[���p�b�h
#define BUTTON_MAX         (32)		// �Q�[���p�b�h�g�p�{�^���ő吔
#define MAX_BUF_PAD        (1000)	// �Q�[���p�b�h�̃o�b�t�@�̍ő�l
#define XYZ                (4)		// �A�i���O�X�e�B�b�N�i0�E1 = ���^2�E3 = �E�j
#define MIN_AXIS_PAD       (0)		// �Q�[���p�b�h�̎��̍ŏ��l
#define MAX_AXIS_PAD       (65535)	// �Q�[���p�b�h�̎��̍ő�l

/*-----------------------------------------------------------------------------
 �C���v�b�g�N���X
-----------------------------------------------------------------------------*/
class CInput
{
	public:

		CInput();
		virtual ~CInput();

		virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
		virtual void    Uninit(void);
		virtual HRESULT Update(void) = 0;		// ---> �������z�֐���

	protected:

		HWND m_hWnd;							// �E�B���h�E�n���h��

		static LPDIRECTINPUT8 m_pDInput;		// DirectInput�I�u�W�F�N�g
		LPDIRECTINPUTDEVICE8 m_pDIDevice;		// Device�I�u�W�F�N�g(���͂ɕK�v)

};

/*-----------------------------------------------------------------------------
 �C���v�b�g�N���X�F�L�[�{�[�h
-----------------------------------------------------------------------------*/
class CInputKeyboard : public CInput
{
	private:

		BYTE m_aKeyState         [NUM_KEY_MAX];			// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
		BYTE m_aKeyStateTrigger  [NUM_KEY_MAX];			// �g���K�[���[�N
		BYTE m_aKeyStateRelease  [NUM_KEY_MAX];			// �����[�X���[�N
		BYTE m_aKeyStateRepeat   [NUM_KEY_MAX];			// ���s�[�g���[�N
		int  m_aKeyStateRepeatCnt[NUM_KEY_MAX];			// ���s�[�g�J�E���^

	public:

		CInputKeyboard();
		~CInputKeyboard();

		// �e�����֐�
		HRESULT Init(HINSTANCE hInst, HWND hWnd);
		void    Uninit(void);
		HRESULT Update(void) override;

		// �L�[�{�[�h�f�[�^�擾(�v���X)
		BOOL GetKeyPress(int nKey)
		{
			return (m_aKeyState[nKey] & 0x80) ? TRUE : FALSE;
		}//end

		// �L�[�{�[�h�f�[�^�擾(�g���K�[)
		BOOL GetKeyTrigger(int nKey)
		{
			return (m_aKeyStateTrigger[nKey] & 0x80) ? TRUE : FALSE;
		}//end

		// �L�[�{�[�h�f�[�^�擾(�����[�X)
		BOOL GetKeyRelease(int nKey)
		{
			return (m_aKeyStateRelease[nKey] & 0x80) ? TRUE : FALSE;
		}//end

		// �L�[�{�[�h�f�[�^�擾(���s�[�g)
		BOOL GetKeyRepeat(int nKey)
		{
			return (m_aKeyStateRepeat[nKey] & 0x80) ? TRUE : FALSE;
		}//end

		// �L�[�{�[�h�f�[�^�폜(�g���K�[)
		void FlushKeyTrigger(int nKey)
		{
			m_aKeyStateTrigger[nKey] = 0;
		}//end

};

/*-----------------------------------------------------------------------------
 �C���v�b�g�N���X�F�}�E�X
-----------------------------------------------------------------------------*/
class CInputMouse : public CInput
{
	private:

		DIMOUSESTATE2 m_mouseState;
		DIMOUSESTATE2 m_mouseStateTrigger;
		POINT         m_MousePosScreen;			// �X�N���[���ł̃|�W�V����
		POINT         m_MousePosClient;			// �N���C�A���g�̈�ł̃|�W�V����
		D3DXVECTOR3   m_MousePosWrold;			// ���[���h���W�ϊ����̃|�W�V����

	public:

		CInputMouse() {}
		~CInputMouse() {}

		// �e�����֐�
		HRESULT Init(HINSTANCE hInst, HWND hWnd);
		void    Uninit(void);
		HRESULT Update(void) override;

		// ���{�^���F�v���X
		BOOL GetLeftPress(void)
		{
			return (m_mouseState.rgbButtons[0] & 0x80) ? TRUE : FALSE;
		}//end

		// ���{�^���F�g���K�[
		BOOL GetLeftTrigger(void)
		{
			return (m_mouseStateTrigger.rgbButtons[0] & 0x80) ? TRUE : FALSE;
		}//end

		// �E�{�^���F�v���X
		BOOL GetRightPress(void)
		{
			return (m_mouseState.rgbButtons[1] & 0x80) ? TRUE : FALSE;
		}//end

		// �E�{�^���F�g���K�[
		BOOL GetRightTrigger(void)
		{
			return (m_mouseStateTrigger.rgbButtons[1] & 0x80) ? TRUE : FALSE;
		}//end

		// �����{�^���F�v���X
		BOOL GetCenterPress(void)
		{
			return (m_mouseState.rgbButtons[2] & 0x80) ? TRUE : FALSE;
		}//end

		// �����{�^���F�g���K�[
		BOOL GetCenterTrigger(void)
		{
			return (m_mouseStateTrigger.rgbButtons[2] & 0x80) ? TRUE : FALSE;
		}//end

		// �O�t���[���̍��W�ʒu���擾
		LONG GetAxisX(void) { return m_mouseState.lX; }
		LONG GetAxisY(void) { return m_mouseState.lY; }
		LONG GetAxisZ(void) { return m_mouseState.lZ; }

		// ���W�ʒu�擾
		const POINT& GetPosScreen(void) { return m_MousePosScreen; }
		const POINT& GetPosClient(void) { return m_MousePosClient; }
		D3DXVECTOR3 GetPosWorld(void);

};

/*-----------------------------------------------------------------------------
 �C���v�b�g�N���X�F�Q�[���p�b�h
-----------------------------------------------------------------------------*/
class CInputGamePad : public CInput
{
	private:

		static LPDIRECTINPUTDEVICE8 m_pDevGamePad;	//�Q�[���p�b�h�f�o�C�X
		static DIDEVCAPS m_DevCaps;					//�Q�[���p�b�h�̏�ԏ��

		BYTE m_aPadButton         [BUTTON_MAX];		//�Q�[���p�b�h�̓��͏�񃏁[�N
		BYTE m_aPadButtonTrigger  [BUTTON_MAX];		//�Q�[���p�b�h�̃g���K�[��񃏁[�N
		BYTE m_aPadButtonRelease  [BUTTON_MAX];		//�Q�[���p�b�h�̃����[�X��񃏁[�N
		BYTE m_aPadButtonRepeat   [BUTTON_MAX];		//�Q�[���p�b�h�̃��s�[�g��񃏁[�N
		BYTE m_aPadButtonRepeatCnt[BUTTON_MAX];		//�Q�[���p�b�h�̃��s�[�g�J�E���^

		int m_aPadAnalogStick[XYZ];					// �A�i���O�X�e�B�b�N�̏�񃏁[�N
		int m_nPadPOV;								// �Q�[���p�b�h�\���L�[�̏�񃏁[�N
		int m_nPadPOVTrigger;						// �Q�[���p�b�h�\���L�[�̃g���K�[��񃏁[�N
		int m_nPadPOVRepeat;						// �Q�[���p�b�h�\���L�[�̃��s�[�g��񃏁[�N

		//�񋓂��ꂽ�f�o�C�X���ƂɌĂяo�����R�[���o�b�N�֐�
		static BOOL CALLBACK EnumPadCallback(const DIDEVICEINSTANCE* pdidInstance, LPVOID pContext);
		static BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);

	public:

		CInputGamePad()
		{
			m_pDevGamePad = NULL;
			m_nPadPOV     = POV_NOTUSE;
		}//end

		~CInputGamePad() {}

		// �Q�[���p�b�h�񋓌^
		typedef enum
		{
#if 0
			GB_Y = 0,			// �x�{�^��
			GB_B,				// �a�{�^��
			GB_A,				// �`�{�^��
			GB_X,				// �w�{�^��
			GB_L1,				// �k�P�{�^��
			GB_R1,				// �q�P�{�^��
			GB_L2,				// �k�Q�{�^��
			GB_R2,				// �q�Q�{�^��
			GB_BACK,			// �o�b�N�{�^��
			GB_STRAT,			// �X�^�[�g�{�^��
			GB_L3,				// �k�R�{�^��
			GB_R3,				// �q�R�{�^��
#else
			GB_A = 0,			// �`�{�^��
			GB_B,				// �a�{�^��
			GB_X,				// �w�{�^��
			GB_Y,				// �x�{�^��
			GB_L1,				// �k�P�{�^��
			GB_R1,				// �q�P�{�^��
			GB_BACK,			// �o�b�N�{�^��
			GB_STRAT,			// �X�^�[�g�{�^��
			GB_L3,				// �k�R�{�^��
			GB_R3,				// �q�R�{�^��
#endif
			GBA_MAX,			// ����ȏ�̃{�^���͂���܂���

			GS_X = 0,			// �w�������A�i���O�X�e�B�b�N(��
			GS_Y,				// �x�������A�i���O�X�e�B�b�N(��
			GS_ZX,				// �y���������A�i���O�X�e�B�b�N(�E
			GS_ZY,				// �y���c�����A�i���O�X�e�B�b�N(�E

			GSL,				// ���X�e�B�b�N���g�p����
			GSR,				// �E�X�e�B�b�N���g�p����

			POV_NOTUSE = -1,	// �\���L�[�̖��g�p
			POV_UP = 0,			// �\���L�[�̏�{�^��
			POV_UPRIGHT,		// �\���L�[�̉E��{�^��
			POV_RIGHT,			// �\���L�[�̉E�{�^��
			POV_DOWNRIGHT,		// �\���L�[�̉E���{�^��
			POV_DOWN,			// �\���L�[�̉��{�^��
			POV_DOWNLEFT,		// �\���L�[�̍����{�^��
			POV_LEFT,			// �\���L�[�̍��{�^��
			POV_UPLEFT,			// �\���L�[�̍��{�^��

		}GAMEPAD;

		// �e�����֐�
		HRESULT Init(HINSTANCE hInstance, HWND hWnd);
		void Uninit(void);
		HRESULT Update(void) override;

		/* �̗p���Ă���擾���
			�v���X�@�F�����Ă���ԁA�^�ƂȂ�
			�g���K�[�F�������Ƃ��ɐ^�ƂȂ�
			���s�[�g�F�����Ă���ԁA���̃��Y���Ő^�ƂȂ�
			�����[�X�F�������Ƃ��ɐ^�ƂȂ�
		*/

		// �Q�[���p�b�h�F�{�^��
		BOOL GetPadButton       (int nPad) { return (m_aPadButton       [nPad] & 0x80) ? true : false; }
		BOOL GetPadButtonTrigger(int nPad) { return (m_aPadButtonTrigger[nPad] & 0x80) ? true : false; }
		BOOL GetPadButtonRepeat (int nPad) { return (m_aPadButtonRepeat [nPad] & 0x80) ? true : false; }
		BOOL GetPadButtonRelease(int nPad) { return (m_aPadButtonRelease[nPad] & 0x80) ? true : false; }

		// �Q�[���p�b�h�F�o�n�u�i�\���L�[�j
		int GetPadPOVPress(void);
		int GetPadPOVTrigger(void);
		int GetPadPOVRepeat(void);

		// �A�i���O�X�e�B�b�N�̏�Ԃ̎擾
		D3DXVECTOR3 GetPadAnalogStick(int nPadType);

		// �Q�[���p�b�h�ڑ��󋵂̎擾
		LPDIRECTINPUTDEVICE8 GetGamePad(void) { return m_pDevGamePad; }

};

/*-----------------------------------------------------------------------------
 �C���N���[�h�G���h
-----------------------------------------------------------------------------*/
#endif

