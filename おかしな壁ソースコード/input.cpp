/*-----------------------------------------------------------------------------

 ���͏��� [input.cpp]
 Author : KIM NAKAMURA

-----------------------------------------------------------------------------*/
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "camera.h"

/*-----------------------------------------------------------------------------
 �}�N����`
-----------------------------------------------------------------------------*/
#define COUNT_WAIT_REPEAT   (20)	// ���s�[�g�҂�����
#define LIMIT_COUNT_REPEAT  (24)	// ���s�[�g�J�E���g���~�b�^�[(20���悢)

// �񋓏�ԁi������^��߂�j
#define DIDENUM_CONTINUE   (0)
#define DIDENU_STOP        (1)

/*-----------------------------------------------------------------------------
 �ÓI�ϐ������o�̓��I�m��
-----------------------------------------------------------------------------*/
LPDIRECTINPUT8 CInput::m_pDInput = NULL;	// DirectInput�I�u�W�F�N�g
LPDIRECTINPUTDEVICE8 CInputGamePad::m_pDevGamePad = NULL;
DIDEVCAPS CInputGamePad::m_DevCaps;

/*-----------------------------------------------------------------------------
 CInput�R���X�g���X�^
-----------------------------------------------------------------------------*/
CInput::CInput()
{
	m_pDIDevice = NULL;
}

/*-----------------------------------------------------------------------------
 CInput�f�X�g���X�^
 -----------------------------------------------------------------------------*/
CInput::~CInput()
{
}

/*-----------------------------------------------------------------------------
 ���͏����̏���������
 -----------------------------------------------------------------------------*/
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̍쐬�ADirectInput�C���^�[�t�F�[�X�̍쐬
	// �L�[�{�[�h�A�p�b�h�A�}�E�X���ʂȂ̂ň��OK�A�����̌p�������œ���
	if (m_pDInput == NULL)
	{
		if (FAILED(DirectInput8Create(
		hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDInput, NULL)))
		{
			MessageBox(hWnd, "DirectXInput�I�u�W�F�N�g���쐬�ł��܂���ł����B",
				"Direct Input Error", MB_OK | MB_DEFBUTTON1);
			return E_FAIL;
		}//if.fin

	}//if.fin

	// �E�B���h�E�n���h���̎擾
	m_hWnd = hWnd;

	// �Ԋ�
	return S_OK;
}

/*-----------------------------------------------------------------------------
 ���͏����̏I������
-----------------------------------------------------------------------------*/
void CInput::Uninit(void)
{
	// �f�o�C�X�I�u�W�F�N�g�̉��
	if(m_pDIDevice)
	{
		m_pDIDevice->Unacquire();

		m_pDIDevice->Release();
		m_pDIDevice = NULL;
	}//if.fin

	// DirectInput�I�u�W�F�N�g�̉��
	if(m_pDInput)
	{
		m_pDInput->Release();
		m_pDInput = NULL;
	}//if.fin

}

/*-----------------------------------------------------------------------------
 CInputKeyboard�R���X�g���X�^
-----------------------------------------------------------------------------*/
CInputKeyboard::CInputKeyboard()
{
	// �e���[�N�̃N���A
	ZeroMemory(m_aKeyState, sizeof m_aKeyState);
	ZeroMemory(m_aKeyStateTrigger, sizeof m_aKeyStateTrigger);
	ZeroMemory(m_aKeyStateRelease, sizeof m_aKeyStateRelease);
	ZeroMemory(m_aKeyStateRepeat, sizeof m_aKeyStateRepeat);
	ZeroMemory(m_aKeyStateRepeatCnt, sizeof m_aKeyStateRepeatCnt);

}

/*-----------------------------------------------------------------------------
 CInputKeyboard�f�X�g���X�^
 -----------------------------------------------------------------------------*/
CInputKeyboard::~CInputKeyboard()
{
}

/*-----------------------------------------------------------------------------
 �L�[�{�[�h�̏���������
 -----------------------------------------------------------------------------*/
HRESULT CInputKeyboard::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// ���͏����̏�����
	CInput::Init(hInst, hWnd);

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDIDevice, NULL);
	if(FAILED(hr) || m_pDIDevice == NULL)
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}//if.fin

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = m_pDIDevice->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}//if.fin

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = m_pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}//if.fin

	// m_pDIDevice�A�N�Z�X�����l��(���͐���J�n)
	m_pDIDevice->Acquire();

	// �Ԋ�
	return hr;

}

/*-----------------------------------------------------------------------------
 �L�[�{�[�h���͏����̊J��
 -----------------------------------------------------------------------------*/
void CInputKeyboard::Uninit(void)
{
	// ���͏����̊J��
	CInput::Uninit();

}

/*-----------------------------------------------------------------------------
 �L�[�{�[�h�̍X�V����
-----------------------------------------------------------------------------*/
HRESULT CInputKeyboard::Update(void)
{
	HRESULT hr;
	BYTE aKeyState[NUM_KEY_MAX];

	if(!m_pDIDevice)
	{
		return E_FAIL;
	}//if.fin

	// �f�o�C�X����f�[�^���擾
	hr = m_pDIDevice->GetDeviceState(sizeof(aKeyState), aKeyState);
	if(SUCCEEDED(hr))
	{
		for(int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];
			m_aKeyStateRepeat[nCntKey] = m_aKeyStateTrigger[nCntKey];

			if(aKeyState[nCntKey])
			{
				m_aKeyStateRepeatCnt[nCntKey]++;
				if(m_aKeyStateRepeatCnt[nCntKey] >= COUNT_WAIT_REPEAT)
				{
					m_aKeyStateRepeat[nCntKey] = aKeyState[nCntKey];
				}//if.fin
			}
			else
			{
				m_aKeyStateRepeatCnt[nCntKey] = 0;
				m_aKeyStateRepeat[nCntKey] = 0;
			}//if.fin

			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}//for.fin
	}
	else
	{
		m_pDIDevice->Acquire();
	}//if.fin

	// �Ԋ�
	return hr;

}

/*-----------------------------------------------------------------------------
 �}�E�X�̏���������
-----------------------------------------------------------------------------*/
HRESULT CInputMouse::Init(HINSTANCE hInst, HWND hWnd)
{
	// �ϐ��錾
	HRESULT hr;

	// ���͏����̏�����
	CInput::Init(hInst, hWnd);

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = m_pDInput->CreateDevice(GUID_SysMouse, &m_pDIDevice, NULL);

	if (FAILED(hr) || m_pDIDevice == NULL)
	{
		MessageBox(hWnd, "�}�E�X���˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}//if.fin

	 // �f�[�^�t�H�[�}�b�g��ݒ�
	hr = m_pDIDevice->SetDataFormat(&c_dfDIMouse2);

	if (FAILED(hr))
	{
		MessageBox(hWnd, "�}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}//if.fin

	 // �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = m_pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	if (FAILED(hr))
	{
		MessageBox(hWnd, "�}�E�X�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}//if.fin

	 // �f�o�C�X�̐ݒ�
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_REL;

	hr = m_pDIDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph);

	// �}�E�X��m_pDIDevice�A�N�Z�X�����l��(���͐���J�n)
	m_pDIDevice->Acquire();

	// �Ԋ�
	return hr;

}

/*-----------------------------------------------------------------------------
 �}�E�X���͏����̊J��
-----------------------------------------------------------------------------*/
void CInputMouse::Uninit(void)
{
	// ���͏����̊J��
	CInput::Uninit();
}

/*-----------------------------------------------------------------------------
 �}�E�X�̍X�V����
-----------------------------------------------------------------------------*/
HRESULT CInputMouse::Update(void)
{
	// �ϐ��錾
	HRESULT hr;

	// �\���̎g�p�錾
	DIMOUSESTATE2 mouseState;

	// NULLCHECK
	if (!m_pDIDevice) return S_FALSE;

	// �f�o�C�X����f�[�^�̎擾
	hr = m_pDIDevice->GetDeviceState(sizeof(mouseState), &mouseState);

	if (SUCCEEDED(hr))
	{
		// X
		m_mouseStateTrigger.lX = ((m_mouseState.lX ^ mouseState.lX) & mouseState.lX);

		// Y
		m_mouseStateTrigger.lY = ((m_mouseState.lY ^ mouseState.lY) & mouseState.lY);

		// Z
		m_mouseStateTrigger.lZ = ((m_mouseState.lZ ^ mouseState.lZ) & mouseState.lZ);

		// �L�[�W���̃��[�v
		for (int nCntKey = 0; nCntKey < 8; nCntKey++)
		{
			m_mouseStateTrigger.rgbButtons[nCntKey]
				= ((m_mouseState.rgbButtons[nCntKey] ^ mouseState.rgbButtons[nCntKey]) & mouseState.rgbButtons[nCntKey]);
		}//for.fin

		// �X�e�[�g�̊m��
		m_mouseState = mouseState;

		// �N���C�A���g���W�̎擾
		ScreenToClient(m_hWnd, &m_MousePosScreen);

		// �p�r�ʂ̂��߂Ɉڂ��ւ���
		m_MousePosClient = m_MousePosScreen;

		// �X�N���[�����W���擾
		GetCursorPos(&m_MousePosScreen);
	}
	else
	{
		// �}�E�X��m_pDIDevice�A�N�Z�X�����l��(���͐���J�n)
		m_pDIDevice->Acquire();
	}//if.fin

	// �Ԋ�
	return hr;

}

/*-----------------------------------------------------------------------------
 �}�E�X�F���[���h���W�ϊ�����
-----------------------------------------------------------------------------*/
D3DXVECTOR3 CInputMouse::GetPosWorld(void)
{
	// �e�s��̋t�s����Z�o
	D3DXMATRIX InvView, InvPrj, InvPort, ViewPort;

	// �r���[�}�g���N�X�̋t�s��Ԋ�
	D3DXMatrixInverse(&InvView, NULL, CCamera::GetViewMtx());

	// �v���W�F�N�V�����}�g���N�X�̋t�s��Ԋ�
	D3DXMatrixInverse(&InvPrj, NULL, CCamera::GetProjectionMtx());

	// �r���[�|�[�g�}�g���N�X�̐��K��
	D3DXMatrixIdentity(&ViewPort);

	ViewPort._11 = SCREEN_WIDTH / 2.0f; ViewPort._22 = -SCREEN_HEIGHT / 2.0f;
	ViewPort._41 = SCREEN_WIDTH / 2.0f; ViewPort._42 =  SCREEN_HEIGHT / 2.0f;

	// �r���[�|�[�g�}�g���N�X�̋t�s��Ԋ�
	D3DXMatrixInverse(&InvPort, NULL, &ViewPort);

	// �t�ϊ�
	D3DXMATRIX tmp = InvPort * InvPrj * InvView;
	D3DXVec3TransformCoord
	(&m_MousePosWrold, &D3DXVECTOR3((float)m_MousePosClient.x, (float)m_MousePosClient.y, 1.0f), &tmp);

	// ���ʂ̕Ԋ�
	return m_MousePosWrold;

}

/*-----------------------------------------------------------------------------
 �Q�[���p�b�h�̏���������
-----------------------------------------------------------------------------*/
HRESULT CInputGamePad::Init(HINSTANCE hInst, HWND hWnd)
{
	// ���͏����̏�����
	CInput::Init(hInst, hWnd);

	// �Q�[���p�b�h�f�o�C�X�̍쐬
	if (FAILED(m_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL,		// �񋓂���f�o�C�X�̎��
		EnumPadCallback,										// �񋓃R�[���o�b�N�֐��̃A�h���X
		NULL,													// �񋓃R�[���o�b�N�֐����Ă΂��x���s
		DIEDFL_ATTACHEDONLY)))									// �񋓂̗t�ɂ��w�肷��t���O�l
	{
		MessageBox(hWnd, "�Q�[���p�b�h���񋓂Ɏ��s���܂����B", "Direct Input Error", MB_ICONWARNING);
		return E_FAIL;
	}//if.fin

	// �Q�[���p�b�h�ڑ��m�F
	if (!m_pDevGamePad) return S_OK;

	// �Q�[���p�b�h�̃f�[�^�t�H�[�}�b�g
	if (FAILED(m_pDevGamePad->SetDataFormat(&c_dfDIJoystick2)))
	{
		MessageBox(hWnd, "�Q�[���p�b�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "Direct Input Error", MB_ICONWARNING);
		return E_FAIL;
	}//if.fin

	 // �厖!�t�H�A�O���E���hor�o�b�N�O���E���h,��r��or�r���A�ڂ����͋��ȏ���
	 // �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j

	 //�Q�[���p�b�h
	if (FAILED(m_pDevGamePad->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		MessageBox(hWnd, "�Q�[���p�b�h�̋������[�h��ݒ�ł��܂���ł����B", "Direct Input Error", MB_ICONWARNING);
		return E_FAIL;
	}//if.fin

	//���͈̔͐ݒ�
	if (FAILED(m_pDevGamePad->EnumObjects(EnumAxesCallback, NULL, DIDFT_AXIS)))
	{
		MessageBox(hWnd, "�Q�[���p�b�h�̎����[�h���ݒ肹���܂���ł����B", "Direct Input Error", MB_ICONWARNING);
	}//if.fin

	// ����I��
	return S_OK;

}

/*-----------------------------------------------------------------------------
 �Q�[���p�b�h�̓��͏����̊J��
-----------------------------------------------------------------------------*/
void CInputGamePad::Uninit(void)
{
	// ���̓f�o�C�X�C���^�[�t�F�[�X�̉��
	SAFE_RELEASE(m_pDevGamePad);

	// ���͏����̊J��
	CInput::Uninit();
}

/*-----------------------------------------------------------------------------
 �Q�[���p�b�h�̍X�V����
-----------------------------------------------------------------------------*/
HRESULT CInputGamePad::Update(void)
{
	// �Q�[���p�b�h�̐ڑ����Ȃ��ꍇ
	if (!m_pDevGamePad) return E_FAIL;

	// �ϐ��錾
	HRESULT hr;
	DIJOYSTATE2 dijs;

	// �����������
	ZeroMemory(&dijs, sizeof(dijs));

	// �f�[�^�̃|�[�����O // �N����������
	hr = m_pDevGamePad->Poll();

	// ���s�Ȃ�Ăѓ���J�n���s��
	if (FAILED(hr))
	{
		hr = m_pDevGamePad->Acquire();

		while (hr == DIERR_INPUTLOST)
		{
			hr = m_pDevGamePad->Acquire();
		}//while.fin

	}//if.fin

	// �Q�[���p�b�h���͂ɂ��f�[�^�𒼐ڎ擾
	if (SUCCEEDED(m_pDevGamePad->GetDeviceState(sizeof(dijs), &dijs)))
	{
		// �A�i���O�X�e�B�b�N�f�[�^���
		m_aPadAnalogStick[0] = dijs.lX;				// ���X�e�B�b�N�F�w���S��
		m_aPadAnalogStick[1] = dijs.lY;				// ���X�e�B�b�N�F�x���S��
		m_aPadAnalogStick[2] = dijs.lZ;				// �E�X�e�B�b�N�F�y�����S��
		m_aPadAnalogStick[3] = dijs.lRz;			// �E�X�e�B�b�N�F�y���c�S��

		// �o�n�u(�\���L�[)�f�[�^���
		m_nPadPOV = dijs.rgdwPOV[0];

		// �{�^���f�[�^�擾�ɐ���
		for (int nCnPad = 0; nCnPad < BUTTON_MAX; nCnPad++)
		{
			// �Q�[���p�b�h�E�{�^���F�L�[�g���K�[�E�����[�X���̎擾

			//�g���K�[
			m_aPadButtonTrigger[nCnPad] = 
				(m_aPadButton[nCnPad] ^ dijs.rgbButtons[nCnPad]) & dijs.rgbButtons[nCnPad];

			//�����[�X
			m_aPadButtonRelease[nCnPad] = 
				(m_aPadButton[nCnPad] ^ dijs.rgbButtons[nCnPad]) & m_aPadButton[nCnPad];

			// �L�[���s�[�g
			if (dijs.rgbButtons[nCnPad] & 0x80)
			{
				if (m_aPadButtonRepeatCnt[nCnPad] < LIMIT_COUNT_REPEAT)
				{
					m_aPadButtonRepeatCnt[nCnPad]++;

					if (m_aPadButtonRepeatCnt[nCnPad] == 1 || m_aPadButtonRepeatCnt[nCnPad] >= LIMIT_COUNT_REPEAT)
					{
						m_aPadButtonRepeat[nCnPad] = m_aPadButton[nCnPad] | dijs.rgbButtons[nCnPad];
					}
					else//������Ă��邯�Ǒҋ@��
					{
						m_aPadButtonRepeat[nCnPad] = 0;
					}//if.fin

				}//if.fin
			}
			else
			{
				m_aPadButtonRepeat[nCnPad] = 0;
				m_aPadButtonRepeatCnt[nCnPad] = 0;
			}//if.fin

			// �L�[�v���X����ۑ�
			m_aPadButton[nCnPad] = dijs.rgbButtons[nCnPad];
		}//for.fin
	}
	else
	{
		// ���s�Ȃ�Ăѓ���J�n���s��
		m_pDevGamePad->Acquire();
	}//if.fin

	// ���ʕԊ�
	return hr;

}

/*-----------------------------------------------------------------------------
 �W���C�X�e�B�b�N�̃A�i���O�X�e�B�b�N�̏�Ԃ̎擾
-----------------------------------------------------------------------------*/
D3DXVECTOR3 CInputGamePad::GetPadAnalogStick(int nPadType)
{
	// �ϐ��錾
	D3DXVECTOR3 StickStatus;

	// ���ꂼ��̎��̒l����
	switch (nPadType)
	{
		// �w�x�������A�i���O�X�e�B�b�N(��
		case GSL:
			StickStatus = D3DXVECTOR3((float)m_aPadAnalogStick[GS_X],
									  (float)m_aPadAnalogStick[GS_Y],
									  (float)m_aPadAnalogStick[GS_Y]);
			break;

		// �������c���A�i���O�X�e�B�b�N(�E
		case GSR:
			StickStatus = D3DXVECTOR3((float)m_aPadAnalogStick[GS_ZX],
									  (float)m_aPadAnalogStick[GS_ZY], 
									  (float)m_aPadAnalogStick[GS_ZY]);
			break;

		// �x�Ƃy�͋���

	}//switch.fin

	// �l��Ԃ�
	return StickStatus;

}

/*-----------------------------------------------------------------------------
 �W���C�X�e�B�b�N�̏\���L�[�̃v���X��Ԃ̎擾
-----------------------------------------------------------------------------*/
int CInputGamePad::GetPadPOVPress(void)
{
	// �\���L�[�f�[�^�i�[�ϐ��錾
	int StickStatus = POV_NOTUSE;

	// ���͂ɂ���Ď擾�o����l�̊���U��
	if (m_nPadPOV == 0)     StickStatus = POV_UP;			// �\���L�[�̏�{�^��
	if (m_nPadPOV == 4500)  StickStatus = POV_UPRIGHT;		// �\���L�[�̉E��{�^��
	if (m_nPadPOV == 9000)  StickStatus = POV_RIGHT;		// �\���L�[�̉E�{�^��
	if (m_nPadPOV == 13500) StickStatus = POV_DOWNRIGHT;	// �\���L�[�̉E���{�^��
	if (m_nPadPOV == 18000) StickStatus = POV_DOWN;			// �\���L�[�̉��{�^��
	if (m_nPadPOV == 22500) StickStatus = POV_DOWNLEFT;		// �\���L�[�̍����{�^��
	if (m_nPadPOV == 27000) StickStatus = POV_LEFT;			// �\���L�[�̍��{�^��
	if (m_nPadPOV == 31500) StickStatus = POV_UPLEFT;		// �\���L�[�̍��{�^��

	// �l��Ԃ�
	return StickStatus;

}

/*-----------------------------------------------------------------------------
 �W���C�X�e�B�b�N�̏\���L�[�̃g���K�[��Ԃ̎擾
-----------------------------------------------------------------------------*/
int CInputGamePad::GetPadPOVTrigger(void)
{
	// �ϐ��錾
	int StickStatus = POV_NOTUSE;		// �\���L�[�f�[�^�i�[
	static bool bUse = false;			// POV���̗͂L�����f

	// �o�n�u�̓��͂��Ȃ��ꍇ
	if (bUse == false)
	{
		// ���͂ɂ���Ď擾�o����l�̊���U��
		if (m_nPadPOV == 0)     StickStatus = POV_UP;			// �\���L�[�̏�{�^��
		if (m_nPadPOV == 4500)  StickStatus = POV_UPRIGHT;		// �\���L�[�̉E��{�^��
		if (m_nPadPOV == 9000)  StickStatus = POV_RIGHT;		// �\���L�[�̉E�{�^��
		if (m_nPadPOV == 13500) StickStatus = POV_DOWNRIGHT;	// �\���L�[�̉E���{�^��
		if (m_nPadPOV == 18000) StickStatus = POV_DOWN;			// �\���L�[�̉��{�^��
		if (m_nPadPOV == 22500) StickStatus = POV_DOWNLEFT;		// �\���L�[�̍����{�^��
		if (m_nPadPOV == 27000) StickStatus = POV_LEFT;			// �\���L�[�̍��{�^��
		if (m_nPadPOV == 31500) StickStatus = POV_UPLEFT;		// �\���L�[�̍��{�^��
	}//if.fin

	 // �\���L�[�̓��͂��������ꍇ
	if (m_nPadPOV != POV_NOTUSE) bUse = true;	// ���͂���
	else                         bUse = false;	// ���͂Ȃ�

	// �l��Ԃ�
	return StickStatus;

}

/*-----------------------------------------------------------------------------
 �W���C�X�e�B�b�N�̏\���L�[�̃��s�[�g��Ԃ̎擾
-----------------------------------------------------------------------------*/
int CInputGamePad::GetPadPOVRepeat(void)
{
	// �ϐ��錾
	int StickStatus = POV_NOTUSE;		// �\���L�[�f�[�^�i�[
	static int  nCntPOV = 0;			// POV���̓J�E���^
	static bool bUse = false;			// POV���̗͂L�����f
	static bool bGo = false;			// POV���s�[�gGoSign

	// �o�n�u�̓��͂��Ȃ��ꍇ
	if (bUse == false)
	{
		// ���͂ɂ���Ď擾�o����l�̊���U��
		if (m_nPadPOV == 0)     StickStatus = POV_UP;			// �\���L�[�̏�{�^��
		if (m_nPadPOV == 4500)  StickStatus = POV_UPRIGHT;		// �\���L�[�̉E��{�^��
		if (m_nPadPOV == 9000)  StickStatus = POV_RIGHT;		// �\���L�[�̉E�{�^��
		if (m_nPadPOV == 13500) StickStatus = POV_DOWNRIGHT;	// �\���L�[�̉E���{�^��
		if (m_nPadPOV == 18000) StickStatus = POV_DOWN;			// �\���L�[�̉��{�^��
		if (m_nPadPOV == 22500) StickStatus = POV_DOWNLEFT;		// �\���L�[�̍����{�^��
		if (m_nPadPOV == 27000) StickStatus = POV_LEFT;			// �\���L�[�̍��{�^��
		if (m_nPadPOV == 31500) StickStatus = POV_UPLEFT;		// �\���L�[�̍��{�^��
	}//if.fin

	// �\���L�[�̓��͂��������ꍇ
	if (m_nPadPOV != POV_NOTUSE)
	{
		if (bGo == false)
		{
			bUse = true;		// ���͂���
			++nCntPOV;			// �J�E���g�A�b�v
		}//if.fin

		 // ���͊Ԋu
		if ((nCntPOV == 90) || (nCntPOV == 120) || (nCntPOV == 150))
		{
			bUse = false;		// ���͂���
		}//if.fin

		 // ���͊J��
		if (nCntPOV == 180)
		{
			bUse = false;		// ���͂���
			bGo = true;			// GoSign
		}//if.fin
	}
	else
	{
		bUse = false;			// ���͂Ȃ�
		bGo = false;			// ���Z�b�g
		nCntPOV = 0;			// �J�E���^���Z�b�g
	}//if.fin

	// �l��Ԃ�
	return StickStatus;

}

/*-----------------------------------------------------------------------------
 �Q�[���p�b�h��񋓂���R�[���o�b�N�֐�
-----------------------------------------------------------------------------*/
BOOL CALLBACK CInputGamePad::EnumPadCallback(const DIDEVICEINSTANCE* pDidInstance, LPVOID pContext)
{
	HRESULT hr;

	// �񋓂��ꂽ�Q�[���p�b�h�ւ̃C���^�[�t�F�[�X���擾����
	hr = m_pDInput->CreateDevice(pDidInstance->guidInstance, &m_pDevGamePad, NULL);

	//�񋓂𑱂���
	if (FAILED(hr)) return DIDENUM_CONTINUE;

	// �Q�[���p�b�h�̏�Ԃ𒲂ׂ�
	m_DevCaps.dwSize = sizeof(DIDEVCAPS);

	hr = m_pDevGamePad->GetCapabilities(&m_DevCaps);

	if (FAILED(hr))
	{
		// ���̓f�o�C�X�C���^�[�t�F�[�X�̉��
		SAFE_RELEASE(m_pDevGamePad);

		//�񋓂𑱂���
		return DIDENUM_CONTINUE;
	}//if.fin

	 // �񋓂̏I��
	return DIDENU_STOP;

	// �Q�ȏ�g�p����ꍇ
	// return DIENUM_CONTENUE;

}

/*-----------------------------------------------------------------------------
 �Q�[���p�b�h�̎���񋓂���R�[���o�b�N�֐�
-----------------------------------------------------------------------------*/
BOOL CALLBACK CInputGamePad::EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE pdidoi, LPVOID pvRef)
{
	// DIPROPRANGE�̎g�p�錾
	DIPROPRANGE diprg;
	
	// �g�p���镪�̃������̈�̊J��
	ZeroMemory(&diprg, sizeof(diprg));

	// ���͔͈͂̐ݒ�
	// �Ԃ��ꂽ���ɂ��ẮA�ŏ�/�ő�l���X�P�[�����O���邽�߂ɁA�񋓂��ꂽ����DIPROP_RANGE�v���p�e�B��ݒ�
	if (pdidoi->dwType & DIDFT_AXIS)
	{
		diprg.diph.dwSize       = sizeof(DIPROPRANGE);
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		diprg.diph.dwHow        = DIPH_BYID;				// �^�C�v�Ŏ擾���邱�Ƃ��w��
		diprg.diph.dwObj        = pdidoi->dwType;			// �񋓂��ꂽ�����w�肵�܂�
		diprg.lMin              = MIN_AXIS_PAD;				// �l�̍ŏ��l
		diprg.lMax              = MAX_AXIS_PAD;				// �l�̍ő�l
		
		//m_pDevGamePad = (LPDIRECTINPUTDEVICE8)pvRef;

		// �ŏ���1�݂̂ŗ񋓂��I������
		if (FAILED(m_pDevGamePad->SetProperty(DIPROP_RANGE, &diprg.diph))) return DIDENU_STOP;

	}//if.fin

	// �Q�ȏ�̗񋓂��K�v�ȏꍇ�ɑ��s����
	return DIDENUM_CONTINUE;

}



