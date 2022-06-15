//==========================================
//									bitmap.h
//　制作者:AT11B192 No.17 小畠大季
//～～～～～～～～更新履歴～～～～～～～～～
//2020/02/07
// プログラム制作開始
//2020/02/18
// 関数コメントの記述
//～～～～～～～～～～～～～～～～～～～～～

#ifndef _BITMAP_H_
#define _BITMAP_H_

//===== インクルード部 =====
#include <windows.h>

//===== 定数・マクロ定義 =====
#define FILEHEADERSIZE	(14)
#define INFOHEADERSIZE	(40)
#define HEADERSIZE		(FILEHEADERSIZE+INFOHEADERSIZE)


//===== 構造体宣言 =====

//------------------
//RBGデータを保存するための構造体
//------------------
typedef struct {
	unsigned char r;	
	unsigned char g;
	unsigned char b;
} RGB;

//------------------
//ビットマップデータを保存するための構造体
//------------------
typedef struct {
	unsigned int height;	//画像の高さ
	unsigned int width;		//画像の長さ
	RGB *data;				//RGBデータ
	CHAR_INFO *cell;
} IMAGE;


//===== プロトタイプ宣言 ======

//--------------------------------------
//関数名：Read_Bmp
//引　数：const char*, unsigned int, unsigned int
//(読み込むファイルの名前、欲しいデータのサイズ(高さ、長さ))
//戻り値：IMAGE* (読み込んだビットマップの情報)
//内　容：ビットマップデータを指定した大きさに縮尺を変更して読み込む
//--------------------------------------
IMAGE *Read_Bmp(const char*, unsigned int, unsigned int);
//--------------------------------------
//関数名：Free_Image
//引　数：IMAGE* (消去したいビットマップデータ)
//戻り値：なし
//内　容：読み込んだビットマップデータを消去し、メモリ領域を解放する
//--------------------------------------
void Free_Image(IMAGE*);

#endif // !_BITMAP_H_
