//--------------------------------------------------------------------------------------
// File: DataPath.cpp
//
// �f�[�^�p�X�N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "DataPath.h"

//--------------------------------------------------------------------------------------
//	json�p�X
//--------------------------------------------------------------------------------------

//	�V�X�e���f�[�^�̃t�@�C���p�X
const char* DataPath::SYSTEM_DATA_PATH = "Resources/Datas/MouseSetting.json";

//	�v���C�J�����f�[�^�̃t�@�C���p�X
const char* DataPath::PLAY_CAMERA_DATA_PATH = "Resources/Datas/PlayCamera.json";
//	�v���C���[�f�[�^�̃t�@�C���p�X
const char* DataPath::PLAYER_SPRING_DATA_PATH = "Resources/Datas/PlayerSpring.json";

//	�X�e�[�W�f�[�^�̃t�@�C���p�X
const char* DataPath::STAGE_DATA_PATHs[STAGE_NUMBER] =
{
	"Resources/Datas/Stages/Stage01.json",
	"Resources/Datas/Stages/Stage02.json",
	"Resources/Datas/Stages/Stage03.json",
	"Resources/Datas/Stages/Stage04.json",
	"Resources/Datas/Stages/Stage05.json",
	"Resources/Datas/Stages/Stage06.json",
	"Resources/Datas/Stages/Stage07.json"
};

//--------------------------------------------------------------------------------------
//	Shader�p�X
//--------------------------------------------------------------------------------------

//	�傫���_�̒��_�V�F�[�_�̃t�@�C���p�X
const wchar_t* DataPath::BIG_CLOUD_VS_PATH = L"Resources/Shader/cso/Cloud_VS.cso";
//	�傫���_�̃s�N�Z���V�F�[�_�̃t�@�C���p�X
const wchar_t* DataPath::BIG_CLOUD_PS_PATH = L"Resources/Shader/cso/Cloud_PS.cso";

//--------------------------------------------------------------------------------------
//	���f���p�X
//--------------------------------------------------------------------------------------

//	�X�J�C�h�[�����f���̃t�@�C���p�X
const wchar_t* DataPath::SKYDOME_MODEL_PATH = L"Resources/Models/SkyDome.cmo";
//	�傫���_���f���̃t�@�C���p�X
const wchar_t* DataPath::BIG_CLOUD_MODEL_PATH = L"Resources/Models/BigCloud.cmo";

//	�^�C�g���V�[���_���f���̃t�@�C���p�X
const wchar_t* DataPath::TITLE_CLOUD_MODEL_PATH = L"Resources/Models/Clouds/TitleCloud.cmo";
//	�^�C�g���e�L�X�g���f���̃t�@�C���p�X�z��
const wchar_t* DataPath::TITLE_TEXT_MODEL_PATHs[TITLE_TEXT_MODEL_NUMBER] =
{
	L"Resources/Models/Texts/Title/ba.cmo",
	L"Resources/Models/Texts/Title/ne.cmo",
	L"Resources/Models/Texts/Title/zi.cmo",
	L"Resources/Models/Texts/Title/ya.cmo",
	L"Resources/Models/Texts/Title/n.cmo",
	L"Resources/Models/Texts/Title/pu.cmo"
};

//	�Z���N�g�V�[���_���f���̃t�@�C���p�X
const wchar_t* DataPath::SELECT_CLOUD_MODEL_PATH = L"Resources/Models/Clouds/SelectCloud.cmo";
//	�Z���N�g�e�L�X�g���f���̃t�@�C���p�X�z��
const wchar_t* DataPath::SELECT_TEXT_MODEL_PATHs[STAGE_NUMBER] =
{
	L"Resources/Models/Texts/Number/Num_01.cmo",
	L"Resources/Models/Texts/Number/Num_02.cmo",
	L"Resources/Models/Texts/Number/Num_03.cmo",
	L"Resources/Models/Texts/Number/Num_04.cmo",
	L"Resources/Models/Texts/Number/Num_05.cmo",
	L"Resources/Models/Texts/Number/Num_06.cmo",
	L"Resources/Models/Texts/Number/Num_07.cmo"
};

//	�v���C���[�΂˃��f���̃t�@�C���p�X�z��
const wchar_t* DataPath::PLAYER_SPRING_MODEL_PATHs[PLAYER_SPRING_MODEL_NUMBER] =
{
	L"Resources/Models/Player/Spring_01.cmo",
	L"Resources/Models/Player/Spring_02.cmo",
	L"Resources/Models/Player/Spring_03.cmo",
	L"Resources/Models/Player/Spring_04.cmo"
};
//	�v���C���[�����f���̃t�@�C���p�X
const wchar_t* DataPath::PLAYER_HEAD_MODEL_PATH = L"Resources/Models/Player/Head.cmo";

//	�_�i�X�e�[�W�I�u�W�F�N�g�j���f���̃t�@�C���p�X
const wchar_t* DataPath::STAGE_CLOUD_MODEL_PATH = L"Resources/Models/Stage/Cloud.cmo";
//	�S�[���i�X�e�[�W�I�u�W�F�N�g�j���f���̃t�@�C���p�X
const wchar_t* DataPath::STAGE_GOAL_MODEL_PATH = L"Resources/Models/Stage/Goal.cmo";
//	�X�^�[�g�i�X�e�[�W�I�u�W�F�N�g�j���f���̃t�@�C���p�X
const wchar_t* DataPath::STAGE_START_MODEL_PATH = L"Resources/Models/Stage/Start.cmo";
//	���D�i�X�e�[�W�I�u�W�F�N�g�j���f���̃t�@�C���p�X
const wchar_t* DataPath::STAGE_BALLOON_MODEL_PATH = L"Resources/Models/Stage/Balloon.cmo";
//	��s�@�i�X�e�[�W�I�u�W�F�N�g�j���f���̃t�@�C���p�X
const wchar_t* DataPath::STAGE_PLANE_MODEL_PATH = L"Resources/Models/Stage/Plane01.cmo";


//--------------------------------------------------------------------------------------
//	�f�B���N�g���p�X
//--------------------------------------------------------------------------------------

//	���f���t�H���_�ւ̃f�B���N�g���p�X
const wchar_t* DataPath::MODEL_FOLDER_DIRECTORY_PATH = L"Resources/Models";
//	�e�L�X�g���f���t�H���_�ւ̃f�B���N�g���p�X
const wchar_t* DataPath::TEXT_MODEL_FOLDER_DIRECTORY_PATH = L"Resources/Models/Texts";
//	�v���C���[���f���t�@���_�ւ̃f�B���N�g���p�X
const wchar_t* DataPath::PLAYER_MODEL_FOLDER_DIRECTORY_PATH = L"Resources/Models/Player";
//	�X�e�[�W���f���t�@���_�ւ̃f�B���N�g���p�X
const wchar_t* DataPath::STAGE_MODEL_FOLDER_DIRECTORY_PATH = L"Resources/Models/Stage";

//--------------------------------------------------------------------------------------
//	�摜�p�X
//--------------------------------------------------------------------------------------

//	�t�F�C�h�p�_�摜�̃t�@�C���p�X
const wchar_t* DataPath::FADE_CLOUD_IMAGE_PATH = L"Resources/Textures/CloudFade.png";
//	�t�F�C�h�p�����摜�̃t�@�C���p�X
const wchar_t* DataPath::FADE_WHITE_IMAGE_PATH = L"Resources/Textures/White.png";

//	�X�y�[�X1�摜�̃t�@�C���p�X
const wchar_t* DataPath::SPACE01_IMAGE_PATH = L"Resources/Textures/Space.png";
//	�X�y�[�X2�摜�̃t�@�C���p�X
const wchar_t* DataPath::SPACE02_IMAGE_PATH = L"Resources/Textures/SpacePress.png";

//	�E���摜�̃t�@�C���p�X
const wchar_t* DataPath::RIGHT_ARROW_IMAGE_PATH = L"Resources/Textures/RightArrow.png";
//	�����摜�̃t�@�C���p�X
const wchar_t* DataPath::LEFT_ARROW_IMAGE_PATH = L"Resources/Textures/LeftArrow.png";

//	�����摜�̃t�@�C���p�X�z��
const wchar_t* DataPath::NUMBER_IMAGE_PATHs[NUMBER_IMAGE_NUMBER] =
{
	L"Resources/Textures/Number/00.png",
	L"Resources/Textures/Number/01.png",
	L"Resources/Textures/Number/02.png",
	L"Resources/Textures/Number/03.png",
	L"Resources/Textures/Number/04.png",
	L"Resources/Textures/Number/05.png",
	L"Resources/Textures/Number/06.png",
	L"Resources/Textures/Number/07.png",
	L"Resources/Textures/Number/08.png",
	L"Resources/Textures/Number/09.png"
};

//	�^�C�}�[�̒��S�L���摜�̃t�@�C���p�X
const wchar_t* DataPath::TIMER_CENTER_IMAGE_PATH = L"Resources/Textures/TimeCenter.png";

//	�ݒ��ʂ̔w�i�摜�̃t�@�C���p�X
const wchar_t* DataPath::SYSTEM_BACK_IMAGE_PATH = L"Resources/Textures/System/Back.png";
//	�ݒ��ʂ̑I���t���[���摜�̃t�@�C���p�X
const wchar_t* DataPath::SYSTEM_FRAME_IMAGE_PATH = L"Resources/Textures/System/Frame.png";

//	�ݒ��ʂ̑I�����摜�̃t�@�C���p�X�z��
const wchar_t* DataPath::SYSTEM_SELECT_IMAGE_PATHs[SYSTEM_SELECT_NUMBER] =
{
	L"Resources/Textures/System/Mouse.png",
	L"Resources/Textures/System/Select.png",
	L"Resources/Textures/System/Title.png",
	L"Resources/Textures/System/Exit.png"
};

//	�ݒ��ʂ̃}�E�X���x�I���t���[���摜�̃t�@�C���p�X
const wchar_t* DataPath::SYSTEM_MOUSE_FRAME_IMAGE_PATH = L"Resources/Textures/System/MouseFrame.png";

//	�Z���N�g�V�[���̃^�C�g���摜�̃t�@�C���p�X
const wchar_t* DataPath::SELECT_IMAGE_PATH = L"Resources/Textures/SelectScene/StageSelect.png";

//	�X�e�[�W�摜�̃t�@�C���p�X
const wchar_t* DataPath::STAGE_IMAGE_PATH = L"Resources/Textures/PlayScene/Stage.png";

//	���[���摜�̃t�@�C���p�X
const wchar_t* DataPath::RULU_IMAGE_PATH = L"Resources/Textures/PlayScene/Rulu.png";

//	�J�����؂�ւ�(������@)�摜�̃t�@�C���p�X
const wchar_t* DataPath::C_ICON_IMAGE_PATH = L"Resources/Textures/PlayScene/C_Icon.png";
//	�J�����؂�ւ�(������@)�摜�̃t�@�C���p�X
const wchar_t* DataPath::C_BUTTON_IMAGE_PATH = L"Resources/Textures/PlayScene/C_Button.png";
//	�\�����̕\���؂�ւ��摜�̃t�@�C���p�X
const wchar_t* DataPath::X_ICON_IMAGE_PATH = L"Resources/Textures/PlayScene/X_Icon.png";
//	�\�����̕\���؂�ւ�(������@)�摜�̃t�@�C���p�X
const wchar_t* DataPath::X_BUTTON_IMAGE_PATH = L"Resources/Textures/PlayScene/X_Button.png";

//	�����~�摜�̃t�@�C���p�X
const wchar_t* DataPath::BLACK_CIRCLE_IMAGE_PATH = L"Resources/Textures/PlayScene/BlackCircle.png";
//	�Ԃ��~�摜�̃t�@�C���p�X
const wchar_t* DataPath::RED_CIRCLE_IMAGE_PATH = L"Resources/Textures/PlayScene/RedCircle.png";
//	���S�A�C�R���摜�̃t�@�C���p�X
const wchar_t* DataPath::DEAD_ICON_IMAGE_PATH = L"Resources/Textures/PlayScene/Skull.png";
//	���U���g�摜�̃t�@�C���p�X
const wchar_t* DataPath::RESULT_IMAGE_PATH = L"Resources/Textures/PlayScene/Result.png";

//	�_�G�t�F�N�g�摜�̃t�@�C���p�X
const wchar_t* DataPath::CLOUD_PARTICLE_IMAGE_PATH = L"Resources/Textures/PlayScene/CloudParticle.png";
//	���p�[�e�B�N���摜�̃t�@�C���p�X
const wchar_t* DataPath::WIND_PARTICLE_IMAGE_PATH = L"Resources/Textures/PlayScene/WindParticle.png";
//	�����G�t�F�N�g�摜�̃t�@�C���p�X
const wchar_t* DataPath::EXPLOSION_PARTICLE_IMAGE_PATHs[EXPLOSION_PARTICLE_IMAGE_NUM] =
{
	L"Resources/Textures/PlayScene/Explosion/explosion01.png",
	L"Resources/Textures/PlayScene/Explosion/explosion02.png",
	L"Resources/Textures/PlayScene/Explosion/explosion03.png",
	L"Resources/Textures/PlayScene/Explosion/explosion04.png",
	L"Resources/Textures/PlayScene/Explosion/explosion05.png",
	L"Resources/Textures/PlayScene/Explosion/explosion06.png",
	L"Resources/Textures/PlayScene/Explosion/explosion07.png",
	L"Resources/Textures/PlayScene/Explosion/explosion08.png",
	L"Resources/Textures/PlayScene/Explosion/explosion09.png",
	L"Resources/Textures/PlayScene/Explosion/explosion10.png"
};

//--------------------------------------------------------------------------------------
//	���f�ރp�X
//--------------------------------------------------------------------------------------

//	BGM1�̃t�@�C���p�X
const wchar_t* DataPath::BGM_PATH = L"Resources/Audios/BGM_01.wav";
//	BGM2�̃t�@�C���p�X
const wchar_t* DataPath::PLAY_BGM_PATH = L"Resources/Audios/BGM_02.wav";

//	����SE�̃t�@�C���p�X
const wchar_t* DataPath::DECIDE_SE_PATH = L"Resources/Audios/Decide.wav";
//	���SE�̃t�@�C���p�X
const wchar_t* DataPath::ARROW_SE_PATH = L"Resources/Audios/Arrow.wav";
//	�ݒ�SE�̃t�@�C���p�X
const wchar_t* DataPath::SYSTEM_SE_PATH = L"Resources/Audios/SystemWindow.wav";

//	�΂�SE�̃t�@�C���p�X
const wchar_t* DataPath::SPRING_SE_PATH = L"Resources/Audios/Spring.wav";
//	�W�����vSE�̃t�@�C���p�X
const wchar_t* DataPath::JUMP_SE_PATH = L"Resources/Audios/Jump.wav";
//	����SE�̃t�@�C���p�X
const wchar_t* DataPath::EXPLOSION_SE_PATH = L"Resources/Audios/Explosion.wav";
//	�j��SE�̃t�@�C���p�X
const wchar_t* DataPath::BALLOON_SE_PATH = L"Resources/Audios/BalloonBreak.wav";
//	��SE�̃t�@�C���p�X
const wchar_t* DataPath::WIND_SE_PATH = L"Resources/Audios/Wind.wav";

//	�N���b�J�[�@SE�̃t�@�C���p�X
const wchar_t* DataPath::CRACKER01_SE_PATH = L"Resources/Audios/Cracker01.wav";
//	�N���b�J�[�ASE�̃t�@�C���p�X
const wchar_t* DataPath::CRACKER02_SE_PATH = L"Resources/Audios/Cracker02.wav";

//	�N���ASE�̃t�@�C���p�X
const wchar_t* DataPath::CREAR_SE_PATH = L"Resources/Audios/Clear.wav";
//	���SSE�̃t�@�C���p�X
const wchar_t* DataPath::DEAD_SE_PATH = L"Resources/Audios/Dead.wav";