/*=============================================================================

 �f�[�^�Ǘ�[ data.cpp ]

=============================================================================*/
/*=============================================================================
�C���N���[�h�w�b�_
=============================================================================*/
#include <stdio.h>

#include "manager.h"
#include "data.h"

// �Ǘ�����f�[�^
#include "texture.h"
#include "scene3D.h"

// ��������
#include "player.h"
#include "wall.h"
#include "field.h"
#include "item.h"
#include "switch.h"

/*-----------------------------------------------------------------------------
 �t�@�C���g�p�ɂ��x���̃p�X
-----------------------------------------------------------------------------*/
#pragma warning(disable:4996)

/*-----------------------------------------------------------------------------
 �f�[�^���[�h
-----------------------------------------------------------------------------*/
void CData :: Load(const char *pFileName)
{
	// �ϐ��錾
	int nLineCheck;

	// �\���̎g�p�錾
	OBJ_BASE base;

	// �t�@�C���I�[�v��
	FILE *pFile = fopen(pFileName, "r");

	// NULLCHECK
	if (pFile != NULL)
	{
		// �V�[���I�u�W�F�N�g�̓�������E�j��
		CScene::ReleaseAll();

		// �t�@�C������f�[�^�̓ǂݍ���
		while ((nLineCheck = fscanf(pFile,							// �t�@�C���|�C���^
			"%d,%d,%d,%f,%f,%f,%f,%f,%f\n",							// �ǂݍ��ޗ���
			&base.nType, 											// �I�u�W�F�N�g�^�C�v
			&base.nSubType, 										// �h���I�u�W�F�N�g�^�C�v
			&base.nTexType, 										// �e�N�X�`���^�C�v
			&base.pos.x, &base.pos.y, &base.pos.z,					// �|�W�V�����f�[�^
			&base.size.x, &base.size.y, &base.size.z)) != EOF)		// �T�C�Y�f�[�^
		{
			switch (base.nType)
			{
				case TYPE_PLAYER:
					CPlayer::Create(base.nTexType, base.pos, base.size);
					break;

				case TYPE_WALL:
					CWall::Create(base.nTexType, base.pos, base.size, base.nSubType);
					break;

				case TYPE_FIELD:
					CField::Create(base.nTexType, base.pos, base.size);
					break;

				case TYPE_ITEM:
					CItem::Create(base.nTexType, base.pos, base.size, base.nSubType);
					break;

				case TYPE_SWITCH:
					CSwitch::Create(base.nTexType, base.pos, base.size, base.nSubType);
					break;

			}//switch.fin

		}//while.fin

	}
	else
	{
		MessageBox(NULL, "�I�u�W�F�N�g�f�[�^�̃��[�h�Ɏ��s���܂���", "�G���[", MB_OK);
	}//if.fin

	// �N���[�Y
	fclose(pFile);

}

