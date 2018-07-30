/*============================================================================

�|���S���\��[scene.h]

Author: Miyu Ishikawa
Date: 2017/04/26

=============================================================================*/
#ifndef _MODE_H_	     // �Q�d�C���N���[�h�h�~�̃}�N����`
#define _MODE_H_

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/

/*******************************************************************************
* �}�N����`
*******************************************************************************/

/*******************************************************************************
* �O���錾
*******************************************************************************/
class CCamera;
class CLight;

/*******************************************************************************
* �N���X��`
*******************************************************************************/

class CMode
{
public:
	virtual void Init( void ){}	// ������
	virtual void Init( int ){}
	virtual void Uninit( void ) = 0;								// �I��
	virtual void Update( void ) = 0;								// �X�V
	virtual void Draw( void )	= 0;								// �`��

protected:
	

};

class CModeGame:public CMode
{
public:
	void Init( int StageID );							// ������
	void Uninit( void );						// �I��
	void Update( void );						// �X�V
	void Draw( void );							// �`��

private:
	static CCamera *m_pCamera;					// �J�����|�C���^
	static CLight *m_pLight;					// ���C�g�|�C���^

};

class CModeStageSelect:public CMode
{
public:
	void Init( void );							// ������
	void Uninit( void );						// �I��
	void Update( void );						// �X�V
	void Draw( void );							// �`��


	private:
	static CCamera *m_pCamera;					// �J�����|�C���^
	static CLight *m_pLight;					// ���C�g�|�C���^


};

class CModeTitle:public CMode
{
public:
	void Init( void );// ������
	void Uninit( void );						// �I��
	void Update( void );						// �X�V
	void Draw( void );							// �`��


private:
	

};

#endif
#pragma once
