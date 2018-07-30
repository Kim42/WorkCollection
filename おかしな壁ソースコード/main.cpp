/*=============================================================================

 ���C������[ main.cpp ]

=============================================================================*/
/*=============================================================================
 �C���N���[�h�w�b�_
=============================================================================*/
#include "manager.h"

/*=============================================================================
 �}�N����`
=============================================================================*/
#define CLASS_NAME  "SWEET WALL"
#define WINDOW_NAME "SWEET WALL"

/*=============================================================================
 �v���g�^�C�v�錾
=============================================================================*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*-----------------------------------------------------------------------------
 ���C���֐�
-----------------------------------------------------------------------------*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �x���Ւf
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// �g���鍐�\����
	WNDCLASSEX wcex;

	wcex.cbSize        = sizeof(WNDCLASSEX);				// WNDCLASSEX�̃������T�C�Y�̎w��
	wcex.style         = CS_CLASSDC;						// �\������E�B���h�E�̃X�^�C���̐ݒ�
	wcex.lpfnWndProc   = WndProc;							// �E�B���h�E�v���V�[�W���̃A�h���X(�֐���)���擾
	wcex.cbClsExtra    = 0;									// �ʏ�͎g�p���Ȃ��̂�"0"���w��
	wcex.cbWndExtra    = 0;									// �ʏ�͎g�p���Ȃ��̂�"0"���w��
	wcex.hInstance     = hInstance;							// WinMain�̃p�����[�^�̃C���X�^���X�n���h��
	wcex.hIcon         = NULL;								// �g�p����A�C�R�����w��(Windows�������Ă���A�C�R��)
	wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);		// �}�E�X�J�[�\�E���̎w��
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);		// �E�B���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�
	wcex.lpszMenuName  = NULL;								// window�ɂ��郁�j���[��ݒ�
	wcex.lpszClassName = CLASS_NAME;						// �E�B���h�E�N���X�̖��O
	wcex.hIconSm       = NULL;								// �������A�C�R�����ݒ肳�ꂽ�ꍇ�̏����L�q

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �n���h����`
	HWND hWnd;
	MSG msg;

	// �E�B���h�E�X�^�C���̐ݒ�
	DWORD WindowStyle = WS_OVERLAPPEDWINDOW &~ (WS_MAXIMIZEBOX | WS_THICKFRAME);

	// �E�B���h�E�g�E�X�N���[���T�C�Y�̎w��ύX
	RECT cr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	AdjustWindowRect(&cr, WindowStyle, FALSE);

	int ww = cr.right - cr.left;
	int wh = cr.bottom - cr.top;

	// �f�X�N�g�b�v�̒��S�ɃE�B���h�E�̕\��
	RECT dr;
	GetWindowRect(GetDesktopWindow(), &dr);

	int dw = dr.right - dr.left;
	int dh = dr.bottom - dr.top;
	int wx = ww > dw ? 0 : (dw - ww) / 2;
	int wy = wh > dh ? 0 : (dh - wh) / 2;

	// �E�B���h�E�̌`��쐬
	hWnd = CreateWindowEx(0,		// �g���E�B���h�E�X�^�C��
		CLASS_NAME,					// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,				// �E�B���h�E�̖��O
		WindowStyle,				// �E�B���h�E�X�^�C�� 
		wx,							// �E�B���h�E�̕\���ꏊ�w
		wy,							// �E�B���h�E�̕\���ꏊ�x
		ww,							// �E�B���h�E�̃t���[���{�X�N���[���̕�
		wh,							// �E�B���h�E�̃t���[���{�X�N���[���̍���
		NULL,						// �e�E�B���h�E�̃n���h��
		NULL,						// ���j���[�n���h���܂��͎q�E�B���h�E�h�c
		hInstance,					// �C���X�^���X�n���h��
		NULL);						// �E�B���h�E�쐬�f�[�^

	ShowWindow(hWnd, nCmdShow);		// �w�肳�ꂽ�E�B���h�E�̕\���F�E�B�����C��
	UpdateWindow(hWnd);				// �E�B���h�E�̏�Ԃ𒼂��ɔ��f�F�E�B�����C��

	// ����������
	if(FAILED(CManager :: Init(hInstance, hWnd, true)))
	{
		// ���b�Z�[�W�̕\��
		MessageBox(NULL, "�Q�[���p�b�h�����ڑ���\n�����ȃG���[�̂��ߏ������Ɏ��s���܂���\n�E�B���h�E����܂�", "�G���[", NULL);
		return E_FAIL;
	}
	else
	{
		// ���b�Z�[�W���[�v
		for(;;)
		{
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
			{
				// Windows�̏���
				if(msg.message == WM_QUIT)
				{
					break;
				}
				else
				{
					// �Ăяo�����̃X���b�h�̃��b�Z�[�W�̖|��Ƒ��M
					TranslateMessage(&msg);

					// �E�B���h�E�v���V�\�W���փ��b�Z�[�W�̑��M
					DispatchMessage(&msg);
				}//if.fin
			}
			else
			{
				// �X�V����
				CManager :: Update();

				// �`�揈��
				CManager :: Draw();

			}//if.fin

		}//for.fin

	}//if.fin

	// �I������
	CManager :: Uninit();

	// �E�B���h�E�N���X�̉���
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �l��Ԃ�
	return (int)msg.wParam;
}

/*-----------------------------------------------------------------------------
 �E�B���h�E�v���V�[�W��
  (CALLBACK : Win32API�֐����Ăяo���̋K��)
  hWnd   : �E�B���h�E�̃n���h��
  uMsg   : ���b�Z�[�W�̎��ʎq
  wParam : ���b�Z�[�W�̍ŏ��̃p�����[�^
  lParam : ���b�Z�[�W�̂Q�Ԗڂ̃p�����[�^
-----------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// �ϐ��錾
	UINT nID;

	// ��x��Ԃ̎d�g��
	switch(uMsg)
	{
		case WM_DESTROY:

			PostQuitMessage(0);
			break;

		case WM_KEYDOWN:

			switch(wParam)		// wParam�ɓ��͂����L�[�̃A�h���X��������
			{
				case VK_ESCAPE:

					nID = MessageBox(NULL, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON1);

					// �I������
					if(nID == IDYES) DestroyWindow(hWnd);
					break;

			}//switch
			break;

		default:

			break;

	}//switch.fin

	// ����̕Ԃ�l
	return DefWindowProc(hWnd, uMsg, wParam, lParam);

}
