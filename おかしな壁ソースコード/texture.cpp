/*=============================================================================

 �e�N�X�`���Ǘ�����[ texture.cpp ]

=============================================================================*/
/*=============================================================================
 �C���N���[�h�w�b�_
=============================================================================*/
#include <stdio.h>

#include "manager.h"
#include "renderer.h"
#include "texture.h"

/*-----------------------------------------------------------------------------
�t�@�C���g�p�ɂ��x���̃p�X
-----------------------------------------------------------------------------*/
#pragma warning(disable:4996)

/*=============================================================================
 �����o�ϐ��̓��I�錾
=============================================================================*/
LPDIRECT3DTEXTURE9 *CTexture :: m_pTextureEx  = NULL;
int                 CTexture :: m_nNumTexture = 0;

/*-----------------------------------------------------------------------------
 �ǂݍ��ݏ����֐�
-----------------------------------------------------------------------------*/
HRESULT CTexture :: Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �I�[�v��(w �ŐV�K�������݁E a �Œǉ���������)
	FILE *pFile = fopen("DATA/FILE/texture.txt", "r");

	// NULLCHECK
	if (pFile != NULL)
	{
		// ������i�[�|�C���^
		char aTexNam[36] = {};

		// �e�N�X�`�������̎擾
		fscanf(pFile, "%d\n", &m_nNumTexture);

		// �C���^�[�t�F�[�X�̓��I�m�ہF�e�N�X�`��������
		m_pTextureEx = new LPDIRECT3DTEXTURE9[m_nNumTexture];

		// �e�N�X�`���̐���
		for(int i = 0; i < m_nNumTexture; i++)
		{
			// �t�@�C�����當����̎擾
			if (fscanf(pFile, "%s\n", aTexNam) != EOF)
			{
				// �e�N�X�`���̐���
				if (FAILED(D3DXCreateTextureFromFile(pDevice, aTexNam, &m_pTextureEx[i])))
				{
					MessageBox(NULL, "�e�N�X�`���̓ǂݍ��ݎ��s���܂���", "�G���[", MB_OK);
					break;
				}//if.fin

			}//if.fin

		}//for.fin

	}
	else
	{
		MessageBox(NULL, "�e�N�X�`���f�[�^�̃��[�h�Ɏ��s���܂���", "�G���[", MB_OK);
	}//if.fin

	// �N���[�Y
	fclose(pFile);

	// ����I��
	return S_OK;

}

/*-----------------------------------------------------------------------------
 ��������֐�
-----------------------------------------------------------------------------*/
void CTexture :: Release(void)
{
	// �e�N�X�`���C���^�[�t�F�[�X�̉��
	for (int i = 0; i < m_nNumTexture; i++) SAFE_RELEASE(*&m_pTextureEx[i]);

	// �܂Ƃߔj��
	delete[] m_pTextureEx;

}

