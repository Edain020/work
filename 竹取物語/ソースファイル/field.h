//------------------------------------------
//									 field.h
//　制作者:AT11B192 No.17 小畠大季
//更新履歴～～～～～～～～～～～～～～～～～
//2020/02/21
// プログラム制作開始
//～～～～～～～～～～～～～～～～～～～～～
#ifndef _FIELD_H_
#define _FIELD_H_

//===== インクルード部 =====
#include "buffer.h"

//===== 定数・マクロ定義 =====
#define TILE_SIZE			(16)	// マップタイルのサイズ
#define FIELD_HEIGHT		(20)	// フィールドの縦の大きさ(タイル数)
#define FIELD_WIDTH			(20)	// フィールドの横の大きさ(タイル数)
#define FIELD_BUFFER_HEIGHT	(WINDOW_HEIGHT / TILE_SIZE)			// 画面に表示するタイル数(縦)
#define FIELD_BUFFER_WIDTH	(WINDOW_WIDTH  / (TILE_SIZE * 2))	// 画面に表示するタイル数(横)
#define MAX_TERRAIN_NAME	(11)	// 地形の名前の最大文字数

//===== 列挙型宣言 =====

//--------------------------------------
//地形判定用列挙型
//--------------------------------------
typedef enum
{
	TERRAIN_PLAIN,		//平地
	TERRAIN_FOREST,		//森
	TERRAIN_MOUNTAINS,	//山
	TERRAIN_RIVER,		//川
	TERRAIN_MAX			//地形の種類
} TERRAIN;

//--------------------------------------
//ユニット判定用列挙型
//--------------------------------------
typedef enum
{
	FIELD_UNIT_NONE,	// ユニット無し
	FIELD_UNIT_PLAYER,	// 味方ユニット
	FIELD_UNIT_ENEMY,	// 敵ユニット
	FIELD_UNIT_MAX		// ユニットの種類
} FIELD_UNIT;

//===== 構造体宣言 =====

//--------------------------------------
//地形情報用構造体
//--------------------------------------
typedef struct
{
	TERRAIN Terrain;					// 地形番号
	char TerrainName[MAX_TERRAIN_NAME];	// 地形名
	IMAGE *pImage;						// 画像データ
	int nPassCost;						// 通過コスト
} TERRAIN_INFO;

//--------------------------------------
//フィールド用構造体
//--------------------------------------
typedef struct
{
	int nPosX;				// X座標
	int nPosY;				// Y座標
	TERRAIN_INFO Terrain;	// 地形情報
	FIELD_UNIT UnitType;	// 乗っているユニットの種類
	bool bPass;				// 通行可能かどうか
} FIELD;


//===== プロトタイプ宣言 =====

//--------------------------------------
//関数名：InitField
//引　数：なし
//戻り値：なし
//内　容：フィールド前処理
//--------------------------------------
void InitField(void);
//--------------------------------------
//関数名：UpdateField
//引　数：なし
//戻り値：なし
//内　容：フィールドの更新
//--------------------------------------
void UpdateField(void);
//--------------------------------------
//関数名：DrawField
//引　数：なし
//戻り値：なし
//内　容：フィールドを表示する
//--------------------------------------
void DrawField(void);
//--------------------------------------
//関数名：EndField
//引　数：なし
//戻り値：なし
//内　容：フィールドの後処理
//--------------------------------------
void EndField(void);
//--------------------------------------
//関数名：GetField
//引　数：なし
//戻り値：FIELD* (フィールドデータ)
//内　容：別のファイルにフィールドのデータを渡す
//--------------------------------------
FIELD* GetField(void);
//--------------------------------------
//関数名：GetField
//引　数：int, int (タイルの情報を読み込みたい座標(x, y))
//戻り値：FIELD* (フィールドデータ)
//内　容：指定された位置のタイルのデータを渡す
//--------------------------------------
FIELD* GetFieldxy(int, int);
//--------------------------------------
//関数名：GetFieldBufferX
//引　数：なし
//戻り値：int (X座標)
//内　容：別のファイルにフィールドの用バッファの位置を渡す
//--------------------------------------
int GetFieldBufferX(void);
//--------------------------------------
//関数名：GetFieldBufferY
//引　数：なし
//戻り値：int (Y座標)
//内　容：別のファイルにフィールドの用バッファの位置を渡す
//--------------------------------------
int GetFieldBufferY(void);



void SetFieldBuffer(int, int);
//--------------------------------------
//関数名：MoveFieldBuffer
//引　数：int, int (移動量(x,y))
//戻り値：なし
//内　容：フィールドバッファを移動
//--------------------------------------
void MoveFieldBuffer(int, int);
//--------------------------------------
//関数名：GetTerrainInfo
//引　数：int, int (地形情報を読み込みたい座標(x, y))
//戻り値：TERRAIN_INFO* (地形情報)
//内　容：指定された座標の地形情報を渡す
//--------------------------------------
TERRAIN_INFO* GetTerrainInfo(int, int);

void CheckEnemyUnitMove(int, int, int);


void ResetPass(void);

#endif // !_FIELD_H_
