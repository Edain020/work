//------------------------------------------
//								  cursor.cpp
//Å@êßçÏé“:AT11B192 No.17 è¨î©ëÂãG
//çXêVóöóÅ`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`
//2020/02/29
// ÉvÉçÉOÉâÉÄêßçÏäJén
//2020/03/01
// ÉJÅ[É\ÉãÇì_ñ≈Ç∑ÇÈÇÊÇ§Ç…ïœçX
//Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`
//===== ÉCÉìÉNÉãÅ[Éhïî =====
#define CONIOEX
#include "conioex.h"
#include "bitmap.h"
#include "buffer.h"
#include "cursor.h"
#include "field.h"
#include "player.h"
#include "main.h"
#include "battle.h"
#include "enemy.h"

//===== íËêîÅEÉ}ÉNÉçíËã` =====
#define CURSOR_ANIME_FRAME	(2)						// ÉJÅ[É\ÉãÇÃÉAÉjÉÅÅ[ÉVÉáÉìÇÃÉRÉ}êî
#define CURSOR_ANIME_DELAY	(15)					// ÉJÅ[É\ÉãÇÃÉAÉjÉÅÅ[ÉVÉáÉìä‘äu(ÉtÉåÅ[ÉÄ)
#define CURSOR_FILE1		("bmp/Cursor.bmp")		// ÉJÅ[É\ÉãÇÃÉAÉjÉÅÅ[ÉVÉáÉìÇÃ1ÉRÉ}ñ⁄
#define CURSOR_FILE2		("bmp/Invisible.bmp")	// ÉJÅ[É\ÉãÇÃÉAÉjÉÅÅ[ÉVÉáÉìÇÃ2ÉRÉ}ñ⁄
#define CURSOR_DELAY		(1)						// ÉJÅ[É\ÉãëÄçÏÇÃéÊìæä‘äu

//===== ÉOÉçÅ[ÉoÉãïœêî =====
BUFFER g_CursorBuffer;
IMAGE *g_paCursorImage[CURSOR_ANIME_FRAME];
CURSOR g_Cursor;
int nCnt;

void InitCursor(void)
{
	InitBuffer(&g_CursorBuffer);
	g_paCursorImage[0] = Read_Bmp(CURSOR_FILE1, TILE_SIZE, TILE_SIZE * 2);
	g_paCursorImage[1] = Read_Bmp(CURSOR_FILE2, TILE_SIZE, TILE_SIZE * 2);
	g_Cursor.Pos.Y = FIELD_BUFFER_HEIGHT / 2;
	g_Cursor.Pos.X = FIELD_BUFFER_WIDTH / 2;
	g_Cursor.bClick = false;
	g_Cursor.nFlame = 0;
}

void UpdateCursor(void)
{
	//===== ïœêîêÈåæ =====
	int i;
	int bufx, bufy;
	UNIT *pUnit;

	//===== èâä˙âªèàóù =====
	bufx = GetFieldBufferX();
	bufy = GetFieldBufferY();

	//===== çXêVèàóù =====
	if (++g_Cursor.nFlame > CURSOR_ANIME_DELAY * CURSOR_ANIME_FRAME)	g_Cursor.nFlame = 0;

	if (nCnt-- < 0)
	{
		if (inport(PK_UP))
		{
			if (g_Cursor.Pos.Y > 0)	g_Cursor.Pos.Y--;
			else if (bufy > 0)		MoveFieldBuffer(0, -1);
			nCnt = CURSOR_DELAY;
		}
		if (inport(PK_DOWN))
		{
			if (g_Cursor.Pos.Y < FIELD_BUFFER_HEIGHT - 1)		g_Cursor.Pos.Y++;
			else if (bufy + FIELD_BUFFER_HEIGHT < FIELD_HEIGHT)	MoveFieldBuffer(0, 1);
			nCnt = CURSOR_DELAY;
		}
		if (inport(PK_LEFT))
		{
			if (g_Cursor.Pos.X > 0)	g_Cursor.Pos.X--;
			else if (bufx > 0)		MoveFieldBuffer(-1, 0);
			nCnt = CURSOR_DELAY;
		}
		if (inport(PK_RIGHT))
		{
			if (g_Cursor.Pos.X < FIELD_BUFFER_WIDTH - 1)		g_Cursor.Pos.X++;
			else if (bufx + FIELD_BUFFER_WIDTH < FIELD_WIDTH)	MoveFieldBuffer(1, 0);
			nCnt = CURSOR_DELAY;
		}

		if (inport(PK_ENTER) && !g_Cursor.bClick)
		{
			switch (GetMODE())
			{
			case MODE_PLAYER:
				if (GetFieldxy(g_Cursor.Pos.X + bufx, g_Cursor.Pos.Y + bufy)->UnitType == FIELD_UNIT_PLAYER)
				{
					pUnit = GetPlayerUnit();
					while (pUnit->nPosY != g_Cursor.Pos.Y + bufy || pUnit->nPosX != g_Cursor.Pos.X + bufx)	pUnit++;

					if (pUnit->bAction)	break;

					g_Cursor.pSelectUnit = pUnit;
					SetMODE(MODE_MOVEUNIT);
				}
				break;
			case MODE_MOVEUNIT:
				if (GetFieldxy(g_Cursor.Pos.X + bufx, g_Cursor.Pos.Y + bufy)->bPass)
				{
					GetFieldxy(g_Cursor.pSelectUnit->nPosX, g_Cursor.pSelectUnit->nPosY)->UnitType = FIELD_UNIT_NONE;
					g_Cursor.pSelectUnit->nPosX = g_Cursor.Pos.X + bufx;
					g_Cursor.pSelectUnit->nPosY = g_Cursor.Pos.Y + bufy;
					GetFieldxy(g_Cursor.pSelectUnit->nPosX, g_Cursor.pSelectUnit->nPosY)->UnitType = FIELD_UNIT_PLAYER;
					g_Cursor.pSelectUnit->bAction = true;
					AddActionCnt();
					ResetPass();
					SetMODE(MODE_PLAYER);
					Battle(g_Cursor.pSelectUnit);
					for (i = 0, pUnit = GetEnemyUnit(); i < MAX_ENEMY_UNIT_NUM; i++, pUnit++)
					{
						if (pUnit->bExist)	return;
					}
					SetMODE(MODE_CLEAR);
				}
				else
				{
					ResetPass();
					SetMODE(MODE_PLAYER);
				}
					break;
			default:
				break;
			}
			g_Cursor.bClick = true;
		}
		else if (!inport(PK_ENTER) && g_Cursor.bClick)
		{
			g_Cursor.bClick = false;
		}
		
		if (inport(PK_Z))
		{
			SetMODE(MODE_ENEMY);
		}
	}

	
}

void DrawCursor(void)
{
	//===== ïœêîêÈåæ =====
	int x, y;

	//===== ï`âÊèàóù =====
	for (y = 0; y < FIELD_BUFFER_HEIGHT; y++)
	{
		for (x = 0; x < FIELD_BUFFER_WIDTH; x++)
		{
			if (g_Cursor.Pos.Y != y || g_Cursor.Pos.X != +x) continue;

			if (g_Cursor.nFlame < CURSOR_ANIME_DELAY)	UpdateBuffer(&g_CursorBuffer, g_paCursorImage[0], x * TILE_SIZE * 2, y * TILE_SIZE);
			else										UpdateBuffer(&g_CursorBuffer, g_paCursorImage[1], x * TILE_SIZE * 2, y * TILE_SIZE);
		}
	}

	CombineBuffer(&g_CursorBuffer);
}

void EndCursor(void)
{

}

CURSOR* GetCursor_DK(void)
{
	return &g_Cursor;
}

void SetCursorXY_DK(int x, int y)
{
	g_Cursor.Pos.X = x;
	if (g_Cursor.Pos.X < 0)				g_Cursor.Pos.X = 0;
	if (g_Cursor.Pos.X <= FIELD_WIDTH)	g_Cursor.Pos.X = FIELD_WIDTH - 1;

	g_Cursor.Pos.Y = y;
	if (g_Cursor.Pos.Y < 0)				g_Cursor.Pos.Y = 0;
	if (g_Cursor.Pos.Y <= FIELD_HEIGHT)	g_Cursor.Pos.Y = FIELD_HEIGHT - 1;
}