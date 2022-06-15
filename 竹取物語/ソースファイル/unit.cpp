//------------------------------------------
//									unit.cpp
//�@�����:AT11B192 No.17 ������G
//�X�V�����`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//2020/02/28
// �v���O��������J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//===== �C���N���[�h�� =====
#include <string.h>
#define CONIOEX
#include "conioex.h"
#include "unit.h"

//===== �O���[�o���ϐ� =====
JOB_INFO g_JobInfo[JOB_MAX] = {	// �W���u�f�[�^
	{JOB_SWORDMAN, 100, 50, 30, 5, 1},
	{JOB_SPEARMAN, 150, 40, 20, 6, 2},
	{JOB_BOWMAN  ,  70, 30, 10, 6, 3},
};	//�W���u���@�@Life,Atk,Def,Mov,Range

void InitUnit(UNIT *pUnit, const char *szName, JOB Job)
{
	//===== ���������� =====
	strcpy(pUnit->szName, szName);	// ���O�̐ݒ�
	pUnit->Job = g_JobInfo[Job];	// �X�e�[�^�X�̐ݒ�
	pUnit->nLife = pUnit->Job.nMaxLife;
	pUnit->bExist = true;
	pUnit->bAction = false;
	pUnit->nAnimeNum = 0;
	pUnit->nAnimeCnt = rand() % UNIT_ANIME_DELAY;
}