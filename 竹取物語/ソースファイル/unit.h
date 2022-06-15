//------------------------------------------
//									  unit.h
//　制作者:AT11B192 No.17 小畠大季
//更新履歴～～～～～～～～～～～～～～～～～
//2020/02/28
// プログラム制作開始
//2020/02/29
// UNIT構造体の中身を一部JOB_INFO構造体に移動
//2020/03/02
// ユニットの向きを管理する列挙型(UNIT_DIRECTION)を追加
//～～～～～～～～～～～～～～～～～～～～～
#ifndef _UNIT_H_
#define _UNIT_H_

//===== インクルード部 =====
#include "bitmap.h"

//===== 定数・マクロ定義 =====
#define MAX_NAME			(21)	// 名前の最大文字数
#define UNIT_ANIME_DELAY	(5)	// ユニットのアニメの間隔(フレーム)

//===== 列挙型宣言 =====

//--------------------------------------
//向き判定用列挙型
//--------------------------------------
typedef enum
{
	DIRECTION_NONE,		// 待機
	DIRECTION_UP,		// 上向き
	DIRECTION_DOWN,		// 下向き
	DIRECTION_LEFT,		// 左向き
	DIRECTION_RIGHT,	// 右向き
	DIRECTION_MAX		// 4方向
} UNIT_DIRECTION;

//--------------------------------------
//ジョブ設定用列挙型
//--------------------------------------
typedef enum
{
	JOB_SWORDMAN,	//剣兵
	JOB_SPEARMAN,	//槍兵
	JOB_BOWMAN,		//弓兵
	JOB_MAX
} JOB;

//--------------------------------------
//陣営判別用列挙型
//--------------------------------------
typedef enum
{
	TEAM_PLAYER,	// プレイヤーチーム
	TEAM_ENEMY,		// 敵チーム
	TEAM_MAX		// チームの種類
} TEAM;


//===== 構造体宣言 =====

//--------------------------------------
//ジョブ情報用構造体
//--------------------------------------
typedef struct
{
	JOB Job;		//職業
	int nMaxLife;	//最大体力
	int nAtk;		//攻撃力
	int nDef;		//防御力
	int nMove;		//移動力
	int nAtkRange;	//射程
} JOB_INFO;

//--------------------------------------
//ユニット用構造体
//--------------------------------------
typedef struct
{
	char szName[MAX_NAME];	// 名前
	TEAM Team;				// 陣営
	JOB_INFO Job;			// ジョブ情報
	int nLife;				// 体力
	int nPosX;				// 自身のX座標
	int nPosY;				// 自身のY座標
	int nNextPosX;			// 移動先のX座標
	int nNextPosY;			// 移動先のY座標
	UNIT_DIRECTION Dir;		// 向いている方向
	bool bExist;			// 存在するかどうか
	bool bAction;			// 行動済みかどうか
	IMAGE *pImage;			// ユニットの画像データ
	int nAnimeNum;			// アニメーションの番号
	int nAnimeCnt;			// アニメーション用のカウンター
} UNIT;


//===== プロトタイプ宣言 =====
//--------------------------------------
//関数名：InitUnit
//引　数：UNIT*, const char*, JOB
//		(初期化するユニット、ユニットの名前、ジョブ)
//戻り値：なし
//内　容：ユニットの初期化を行う
//--------------------------------------
void InitUnit(UNIT*, const char*, JOB);

#endif // !_UNIT_H_
