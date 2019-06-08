//-----------------------------------------------------------------
// Space Out Application
// C++ Header - SpaceOut.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Resource.h"
#include "GameEngine.h"
#include "Bitmap.h"
#include "Sprite.h"
#include "Background.h"
#include "AlienSprite.h"
//

class coord {
public:
	int x;
	int y;
	int dist;
	coord* prev;

public:
	coord::coord(int x, int y) {
		this->x = x; this->y = y;
		dist = 0;    prev = NULL;
	}
	coord::coord(int x, int y, int dist, coord* prev) {
		this->x = x; this->y = y;
		this->dist = dist; this->prev = prev;
	}
};

//-----------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------
HINSTANCE         _hInstance;
GameEngine*       _pGame;
HDC               _hOffscreenDC;
HBITMAP           _hOffscreenBitmap;
Bitmap*           _pDesertBitmap;
Bitmap*           _pCarBitmap;
Bitmap*           _pSmCarBitmap;
Bitmap*           _pMissileBitmap;
Bitmap*           _pMissileBitmap_for_wall;
Bitmap*           _pBlobboBitmap;
Bitmap*           _pBMissileBitmap;
Bitmap*           _pJellyBitmap;
Bitmap*           _pJMissileBitmap;
Bitmap*           _pTimmyBitmap;
Bitmap*           _pTMissileBitmap;
Bitmap*           _pSmExplosionBitmap;
Bitmap*           _pLgExplosionBitmap;
Bitmap*           _pGameOverBitmap;
Bitmap*           _pGolfBallBitmap;
Bitmap*           _pHealthBitmap;
Bitmap*           _pPowerBitmap;
Bitmap*           _pDamageBitmap;
Bitmap*           _pSpeedBitmap;
Bitmap*           _pNazgulBitmap;
Bitmap*           _pAzogBitmap;
Bitmap*           _pWarriorsBitmap;
Bitmap*           _pThorinBitmap;
Bitmap*           _pSauronBitmap;
Bitmap*           _pSmaughBitmap;
Bitmap*           _pbFollowBackground;
Bitmap*           _pbFollowBackground_R_L;
StarryBackground* _pBackground;
Sprite*           _pCarSprite;
Sprite*           _pGolfSprite;
Sprite*           _psFollowBackground_Left;
Sprite*           _psFollowBackground_Right;
Sprite*           _psFollowBackground_Top;
Sprite*           _psFollowBackground_Bottom;
AlienSprite*      _pSauronSprite;
AlienSprite*      _pSmaughSprite;
AlienSprite*      _pAzogSprite;
AlienSprite*      _pNazgulSprite;
AlienSprite*      _pWarriorsSprite;
Sprite*           _pThorinSprite;
int               _iFireInputDelay;
int               _iNumLives, _iScore, _iDifficulty;
int               _iDamage;
int               _speed_increase_counter;
int               _counter_to_destroy_wall;
int               _stage_level=1;
int               _temp_level = 1;
int               _ring_counter;
BOOL              _bGameOver;
//

int **map;
int maxrow = 15, maxcol = 19;  // 6*9
int wall, maxwall = ((maxrow - 3) / 2)*((maxcol - 3) / 2);

//-----------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------
void NewGame();
void AddAlien();
