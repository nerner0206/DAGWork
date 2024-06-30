//--------------------------------------------------------------------------------------
// File: DataPath.h
//
// �f�[�^�p�X�N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef DATA_PATH_DEFINED
#define DATA_PATH_DEFINED

/// <summary>
/// �f�[�^�[�p�X�N���X
/// </summary>
class DataPath
{
public:
	//--------------------------------------------------------------------------------------
	//	json�p�X
	//--------------------------------------------------------------------------------------
	
	//	�V�X�e���f�[�^�̃t�@�C���p�X
	static const char* SYSTEM_DATA_PATH;


	//	�v���C�J�����f�[�^�̃t�@�C���p�X
	static const char* PLAY_CAMERA_DATA_PATH;
	//	�v���C���[�f�[�^�̃t�@�C���p�X
	static const char* PLAYER_SPRING_DATA_PATH;
	//	�X�e�[�W��
	static const int STAGE_NUMBER = 7;
	//	�X�e�[�W�f�[�^�̃t�@�C���p�X
	static const char* STAGE_DATA_PATHs[STAGE_NUMBER];

	//--------------------------------------------------------------------------------------
	//	Shader�p�X
	//--------------------------------------------------------------------------------------

	//	�傫���_�̒��_�V�F�[�_�̃t�@�C���p�X
	static const wchar_t* BIG_CLOUD_VS_PATH;
	//	�傫���_�̃s�N�Z���V�F�[�_�̃t�@�C���p�X
	static const wchar_t* BIG_CLOUD_PS_PATH;

	//--------------------------------------------------------------------------------------
	//	���f���p�X
	//--------------------------------------------------------------------------------------

	//	�X�J�C�h�[�����f���̃t�@�C���p�X
	static const wchar_t* SKYDOME_MODEL_PATH;
	//	�傫���_���f���̃t�@�C���p�X
	static const wchar_t* BIG_CLOUD_MODEL_PATH;

	//	�^�C�g���V�[���_���f���̃t�@�C���p�X
	static const wchar_t* TITLE_CLOUD_MODEL_PATH;
	//	�^�C�g���e�L�X�g���f���̐�
	static const int TITLE_TEXT_MODEL_NUMBER = 6;
	//	�^�C�g���e�L�X�g���f���̃t�@�C���p�X�z��
	static const wchar_t* TITLE_TEXT_MODEL_PATHs[TITLE_TEXT_MODEL_NUMBER];

	//	�Z���N�g�V�[���_���f���̃t�@�C���p�X
	static const wchar_t* SELECT_CLOUD_MODEL_PATH;
	//	�Z���N�g�e�L�X�g���f���̃t�@�C���p�X�z��
	static const wchar_t* SELECT_TEXT_MODEL_PATHs[STAGE_NUMBER];

	//	�v���C���[�΂˃��f���̐�
	static const int PLAYER_SPRING_MODEL_NUMBER = 4;
	//	�v���C���[�΂˃��f���̃t�@�C���p�X�z��
	static const wchar_t* PLAYER_SPRING_MODEL_PATHs[PLAYER_SPRING_MODEL_NUMBER];
	//	�v���C���[�����f���̃t�@�C���p�X
	static const wchar_t* PLAYER_HEAD_MODEL_PATH;

	//	�_�i�X�e�[�W�I�u�W�F�N�g�j���f���̃t�@�C���p�X
	static const wchar_t* STAGE_CLOUD_MODEL_PATH;
	//	�S�[���i�X�e�[�W�I�u�W�F�N�g�j���f���̃t�@�C���p�X
	static const wchar_t* STAGE_GOAL_MODEL_PATH;
	//	�X�^�[�g�i�X�e�[�W�I�u�W�F�N�g�j���f���̃t�@�C���p�X
	static const wchar_t* STAGE_START_MODEL_PATH;
	//	���D�i�X�e�[�W�I�u�W�F�N�g�j���f���̃t�@�C���p�X
	static const wchar_t* STAGE_BALLOON_MODEL_PATH;
	//	��s�@�i�X�e�[�W�I�u�W�F�N�g�j���f���̃t�@�C���p�X
	static const wchar_t* STAGE_PLANE_MODEL_PATH;

	//--------------------------------------------------------------------------------------
	//	�f�B���N�g���p�X
	//--------------------------------------------------------------------------------------

	//	���f���t�H���_�ւ̃f�B���N�g���p�X
	static const wchar_t* MODEL_FOLDER_DIRECTORY_PATH;
	//	�e�L�X�g���f���t�H���_�ւ̃f�B���N�g���p�X
	static const wchar_t* TEXT_MODEL_FOLDER_DIRECTORY_PATH;
	//	�v���C���[���f���t�@���_�ւ̃f�B���N�g���p�X
	static const wchar_t* PLAYER_MODEL_FOLDER_DIRECTORY_PATH;
	//	�X�e�[�W���f���t�@���_�ւ̃f�B���N�g���p�X
	static const wchar_t* STAGE_MODEL_FOLDER_DIRECTORY_PATH;

	//--------------------------------------------------------------------------------------
	//	�摜�p�X
	//--------------------------------------------------------------------------------------

	//	�t�F�C�h�p�_�摜�̃t�@�C���p�X
	static const wchar_t* FADE_CLOUD_IMAGE_PATH;
	//	�t�F�C�h�p�����摜�̃t�@�C���p�X
	static const wchar_t* FADE_WHITE_IMAGE_PATH;

	//	�X�y�[�X1�摜�̃t�@�C���p�X
	static const wchar_t* SPACE01_IMAGE_PATH;
	//	�X�y�[�X2�摜�̃t�@�C���p�X
	static const wchar_t* SPACE02_IMAGE_PATH;

	//	�E���摜�̃t�@�C���p�X
	static const wchar_t* RIGHT_ARROW_IMAGE_PATH;
	//	�����摜�̃t�@�C���p�X
	static const wchar_t* LEFT_ARROW_IMAGE_PATH;

	//	�����摜�̐�
	static const int NUMBER_IMAGE_NUMBER = 10;
	//	�����摜�̃t�@�C���p�X�z��
	static const wchar_t* NUMBER_IMAGE_PATHs[NUMBER_IMAGE_NUMBER];

	//	�^�C�}�[�̒��S�L���摜�̃t�@�C���p�X
	static const wchar_t* TIMER_CENTER_IMAGE_PATH;

	//	�ݒ��ʂ̔w�i�摜�̃t�@�C���p�X
	static const wchar_t* SYSTEM_BACK_IMAGE_PATH;
	//	�ݒ��ʂ̑I���t���[���摜�̃t�@�C���p�X
	static const wchar_t* SYSTEM_FRAME_IMAGE_PATH;

	//	�ݒ��ʂ̑I������
	static const int SYSTEM_SELECT_NUMBER = 4;
	//	�ݒ��ʂ̑I�����摜�̃t�@�C���p�X�z��
	static const wchar_t* SYSTEM_SELECT_IMAGE_PATHs[SYSTEM_SELECT_NUMBER];

	//	�}�E�X���x�̔ԍ���
	static const int SYSTEM_MOUSE_NUMBER = 5;
	//	�ݒ��ʂ̃}�E�X���x�I���t���[���摜�̃t�@�C���p�X
	static const wchar_t* SYSTEM_MOUSE_FRAME_IMAGE_PATH;

	//	�Z���N�g�V�[���̃^�C�g���摜�̃t�@�C���p�X
	static const wchar_t* SELECT_IMAGE_PATH;

	//	�X�e�[�W�摜�̃t�@�C���p�X
	static const wchar_t* STAGE_IMAGE_PATH;

	//	���[���摜�̃t�@�C���p�X
	static const wchar_t* RULU_IMAGE_PATH;

	//	�J�����؂�ւ�(������@)�摜�̃t�@�C���p�X
	static const wchar_t* C_ICON_IMAGE_PATH;
	//	�J�����؂�ւ�(������@)�摜�̃t�@�C���p�X
	static const wchar_t* C_BUTTON_IMAGE_PATH;
	//	�\�����̕\���؂�ւ�(������@)�摜�̃t�@�C���p�X
	static const wchar_t* X_ICON_IMAGE_PATH;
	//	�\�����̕\���؂�ւ�(������@)�摜�̃t�@�C���p�X
	static const wchar_t* X_BUTTON_IMAGE_PATH;

	//	�����~�摜�̃t�@�C���p�X
	static const wchar_t* BLACK_CIRCLE_IMAGE_PATH;
	//	�Ԃ��~�摜�̃t�@�C���p�X
	static const wchar_t* RED_CIRCLE_IMAGE_PATH;
	//	���S�A�C�R���摜�̃t�@�C���p�X
	static const wchar_t* DEAD_ICON_IMAGE_PATH;
	//	���U���g�摜�̃t�@�C���p�X
	static const wchar_t* RESULT_IMAGE_PATH;

	//	�_�p�[�e�B�N���摜�̃t�@�C���p�X
	static const wchar_t* CLOUD_PARTICLE_IMAGE_PATH;
	//	���p�[�e�B�N���摜�̃t�@�C���p�X
	static const wchar_t* WIND_PARTICLE_IMAGE_PATH;
	//	�����p�[�e�B�N���摜�̐�
	static const int EXPLOSION_PARTICLE_IMAGE_NUM = 10;
	//	�����p�[�e�B�N���摜�̃t�@�C���p�X
	static const wchar_t* EXPLOSION_PARTICLE_IMAGE_PATHs[EXPLOSION_PARTICLE_IMAGE_NUM];

	//--------------------------------------------------------------------------------------
	//	���f�ރp�X
	//--------------------------------------------------------------------------------------
	
	//	BGM1�̃t�@�C���p�X
	static const wchar_t* BGM_PATH;
	//	BGM2�̃t�@�C���p�X
	static const wchar_t* PLAY_BGM_PATH;

	//	����SE�̃t�@�C���p�X
	static const wchar_t* DECIDE_SE_PATH;
	//	���SE�̃t�@�C���p�X
	static const wchar_t* ARROW_SE_PATH;
	//	�ݒ�SE�̃t�@�C���p�X
	static const wchar_t* SYSTEM_SE_PATH;

	//	�΂�SE�̃t�@�C���p�X
	static const wchar_t* SPRING_SE_PATH;
	//	�W�����vSE�̃t�@�C���p�X
	static const wchar_t* JUMP_SE_PATH;
	//	����SE�̃t�@�C���p�X
	static const wchar_t* EXPLOSION_SE_PATH;
	//	�j��SE�̃t�@�C���p�X
	static const wchar_t* BALLOON_SE_PATH;
	//	��SE�̃t�@�C���p�X
	static const wchar_t* WIND_SE_PATH;

	//	�N���b�J�[�@SE�̃t�@�C���p�X
	static const wchar_t* CRACKER01_SE_PATH;
	//	�N���b�J�[�ASE�̃t�@�C���p�X
	static const wchar_t* CRACKER02_SE_PATH;

	//	�N���ASE�̃t�@�C���p�X
	static const wchar_t* CREAR_SE_PATH;
	//	���SSE�̃t�@�C���p�X
	static const wchar_t* DEAD_SE_PATH;
};
#endif // !DATA_PATH_DEFINED