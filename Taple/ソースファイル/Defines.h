#pragma once

// �Q�[���^�C�g��
#define GAME_TITLE	("Taple")

// FPS��
#define FPS	(60)

// ��ʃT�C�Y
#define SCREEN_WIDTH (1024)
#define SCREEN_HEIGHT (768)

// �V�[���Ǘ�
enum SceneKind
{
	SCENE_TITLE = 0,	// �^�C�g��
	SCENE_STAGESELECT,	// �X�e�[�W�Z���N�g
	SCENE_GAME,			// �Q�[��

	SCENE_MAX	// �V�[����
};

// �X�e�[�W�Ǘ�
enum StageKind
{
	STAGE_KIDSROOM = 0,	// �q������
//	STAGE_STUDY,		// ����
	STAGE_KITCHEN,		// �L�b�`��

	RETURN_TITLE,		// �^�C�g���ɖ߂�

	STAGE_MAX	// �X�e�[�W�I��
};


// ���\�[�X�p�X
#define ASSET(path)	("Assets/"path)

// �f���[�g
#define SAFE_DELETE(p)	if(p){delete p; p = nullptr;}
#define SAFE_DELETE_ARRAY(p)	if(p){delete[] p; p = nullptr;}

// �d��
#define GRAVITY			(0.0098f)

// ���W�A���ϊ�
#define PI				(3.14159265f)		// �~����
#define DEG_TO_RAD(deg)	((deg) * PI / 180.0f)	// �x�����W�A���ɕϊ�
#define RAD_TO_DEG(rad) ((rad) * 180.0f / PI)	// ���W�A����x�ɕϊ�
