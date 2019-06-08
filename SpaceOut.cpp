//-----------------------------------------------------------------
// Space Out Application
// C++ Source - SpaceOut.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "SpaceOut.h"

//-----------------------------------------------------------------
// Game Engine Functions
//-----------------------------------------------------------------
int sauron_counter = 0;
int azog_counter = 0;

BOOL GameInitialize(HINSTANCE hInstance)
{
	// Create the game engine
	_pGame = new GameEngine(hInstance, TEXT("The Lord of The Rings"),
		TEXT("The Lord of The Rings"), IDI_SPACEOUT, IDI_SPACEOUT_SM, 24 * 50, 15 * 50);
	if (_pGame == NULL)
		return FALSE;

	// Set the frame rate
	_pGame->SetFrameRate(30);

	// Store the instance handle
	_hInstance = hInstance;

	return TRUE;
}

void GameStart(HWND hWindow)
{
	// Seed the random number generator
	srand(GetTickCount());

	// Create the offscreen device context and bitmap
	_hOffscreenDC = CreateCompatibleDC(GetDC(hWindow));
	_hOffscreenBitmap = CreateCompatibleBitmap(GetDC(hWindow),
		_pGame->GetWidth(), _pGame->GetHeight());
	SelectObject(_hOffscreenDC, _hOffscreenBitmap);

	// Create and load the bitmaps
	HDC hDC = GetDC(hWindow);

	_pGolfBallBitmap = new Bitmap(hDC, IDB_GOLFBALL, _hInstance);
	_pDesertBitmap = new Bitmap(hDC, IDB_DESERT, _hInstance);
	_pCarBitmap = new Bitmap(hDC, IDB_CAR, _hInstance);
	_pSmCarBitmap = new Bitmap(hDC, IDB_SMCAR, _hInstance);
	_pMissileBitmap = new Bitmap(hDC, IDB_MISSILE, _hInstance);
	_pMissileBitmap_for_wall = new Bitmap(hDC, IDB_MISSILE, _hInstance);
	_pBlobboBitmap = new Bitmap(hDC, IDB_BLOBBO, _hInstance);
	_pBMissileBitmap = new Bitmap(hDC, IDB_BMISSILE, _hInstance);
	_pJellyBitmap = new Bitmap(hDC, IDB_JELLY, _hInstance);
	_pJMissileBitmap = new Bitmap(hDC, IDB_JMISSILE, _hInstance);
	_pTimmyBitmap = new Bitmap(hDC, IDB_TIMMY, _hInstance);
	_pTMissileBitmap = new Bitmap(hDC, IDB_TMISSILE, _hInstance);
	_pSmExplosionBitmap = new Bitmap(hDC, IDB_SMEXPLOSION, _hInstance);
	_pLgExplosionBitmap = new Bitmap(hDC, IDB_LGEXPLOSION, _hInstance);
	_pHealthBitmap = new Bitmap(hDC, IDB_HEALTH, _hInstance);
	_pSpeedBitmap = new Bitmap(hDC, IDB_SPEED, _hInstance);
	_pPowerBitmap = new Bitmap(hDC, IDB_POWER, _hInstance);
	_pDamageBitmap = new Bitmap(hDC, IDB_DAMAGE, _hInstance);
	_pSauronBitmap = new Bitmap(hDC, IDB_SAURON, _hInstance);
	_pAzogBitmap = new Bitmap(hDC, IDB_AZOG, _hInstance);
	_pSmaughBitmap = new Bitmap(hDC, IDB_SMAUGH, _hInstance);
	_pWarriorsBitmap = new Bitmap(hDC, IDB_WARRIORS, _hInstance);
	_pNazgulBitmap = new Bitmap(hDC, IDB_NAZGUL,_hInstance);
	_pThorinBitmap = new Bitmap(hDC,IDB_THORIN,_hInstance);
	_pGameOverBitmap = new Bitmap(hDC, IDB_GAMEOVER, _hInstance);
	_pbFollowBackground= new Bitmap(hDC,IDB_FOLLOWBACKGROUND, _hInstance);
	_pbFollowBackground_R_L = new Bitmap(hDC, IDB_FOLLOWBACKGROUND_R_L, _hInstance);



	// Create the starry background
	_pBackground = new StarryBackground(21 * 50, 15 * 50);

	//
	// allocating array
	map = new int*[maxrow];
	for (int i = 0; i < maxrow; i++) map[i] = new int[maxcol];
	// base labyrinth
	for (int y = 0; y < maxrow; y++) {
		for (int x = 0; x < maxcol; x++) {
			map[y][x] = 0;    // 0:empty   100:base wall   101:additional wall
			if (y == 0 || y == maxrow - 1 || x == 0 || x == maxcol - 1)
			{
				map[y][x] = 100;

			}
			if (y % 2 == 0 && x % 2 == 0)
			{
				map[y][x] = 100;
			}
		}
	}

	// additional walls
	for (wall = 0; wall < maxwall*0.75; wall++) {
		int x, y, x1, y1, x2, y2;
		bool wallok;

		wallok = false;
		do {
			x = rand() % maxcol;
			y = rand() % maxrow;

			if (map[y][x] == 0 && ((x % 2 == 0 && y % 2 == 1) || (x % 2 == 1 && y % 2 == 0))) {
				map[y][x] = 101; wallok = true;


			}
		} while (wallok == false);
	}

	// Play the background music
   // _pGame->PlayMIDISong(TEXT("Music.mid"));

	// Start the game
	NewGame();
}

void GameEnd()
{
	// Close the MIDI player for the background music
	_pGame->CloseMIDIPlayer();

	// Cleanup the offscreen device context and bitmap
	DeleteObject(_hOffscreenBitmap);
	DeleteDC(_hOffscreenDC);

	// Cleanup the bitmaps
	
	delete _pGolfBallBitmap;
	delete _pDesertBitmap;
	delete _pCarBitmap;
	delete _pSmCarBitmap;
	delete _pMissileBitmap_for_wall;
	delete _pMissileBitmap;
	delete _pBlobboBitmap;
	delete _pBMissileBitmap;
	delete _pJellyBitmap;
	delete _pJMissileBitmap;
	delete _pTimmyBitmap;
	delete _pTMissileBitmap;
	delete _pSmExplosionBitmap;
	delete _pLgExplosionBitmap;
	delete _pNazgulBitmap;
	delete _pWarriorsBitmap;
	delete _pSauronBitmap;
	delete _pAzogBitmap;
	delete _pHealthBitmap;
	delete _pSpeedBitmap;
	delete _pPowerBitmap;
	delete _pDamageBitmap;
	delete _pThorinBitmap;
	delete _pGameOverBitmap;
	delete _pbFollowBackground;
	delete _pbFollowBackground_R_L;

	// Cleanup the background
	delete _pBackground;

	// Cleanup the sprites
	_pGame->CleanupSprites();

	// Cleanup the game engine
	delete _pGame;
}

void GameActivate(HWND hWindow)
{
	// Resume the background music
	_pGame->PlayMIDISong(TEXT(""), FALSE);
}

void GameDeactivate(HWND hWindow)
{
	// Pause the background music
	_pGame->PauseMIDISong();
}

void GamePaint(HDC hDC)
{

	// Draw the background
	_pBackground->Draw(hDC);


	// Draw the sprites
	_pGame->DrawSprites(hDC);

	// Draw the power
	TCHAR szTextip[64];
	RECT  rectip = { 0, 0, 1050, 90 };
	wsprintf(szTextip, "%s", "Power=");
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255, 255, 255));
	DrawText(hDC, szTextip, -1, &rectip, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);

	// Draw the power
	TCHAR szTextipp[64];
	RECT  rectipp = { 0, 0, 1075, 90 };
	wsprintf(szTextipp, "%d", _iDamage);
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255, 255, 255));
	DrawText(hDC, szTextipp, -1, &rectipp, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);

	// Draw the score
	TCHAR szTexti[64];
	RECT  recti = { 0, 0, 1050, 60 };
	wsprintf(szTexti, "%s","Score=");
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255, 255, 255));
	DrawText(hDC, szTexti, -1, &recti, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);

	// Draw the score
	TCHAR szText[64];
	RECT  rect = { 0, 0, 1075, 60 };
	wsprintf(szText, "%d", _iScore);
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255, 255, 255));
	DrawText(hDC, szText, -1, &rect, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);

	// Draw the stage
	TCHAR szText__[64];
	RECT  rect__ = { 0, 0, 1050, 120 };
	wsprintf(szText__, "%s","Stage= ");
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255, 255, 255));
	DrawText(hDC, szText__, -1, &rect__, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);

	// Draw the stage
	TCHAR szText_[64];
	RECT  rect_ = { 0, 0, 1075, 120 };
	wsprintf(szText_, "%d", _stage_level);
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255, 255, 255));
	DrawText(hDC, szText_, -1, &rect_, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);

	// Draw the number of remaining lives (cars)
	for (int i = 0; i < _iNumLives; i++)
	  _pSmCarBitmap->Draw(hDC, 1050 + (_pSmCarBitmap->GetWidth() * i), 10, TRUE);
	

	  // Draw the game over message, if necessary
	if (_bGameOver)
		_pGameOverBitmap->Draw(hDC, (16 * 50) / 2, (15 * 50) / 2, TRUE);
}

void GameCycle()
{
	if (!_bGameOver)
	{
		// Randomly add aliens
		if ((rand() % _iDifficulty) == 0)
			AddAlien();

		//add_missile(5, 3, 5);
		// Update the background
		_pBackground->Update();

		// Update the sprites
		_pGame->UpdateSprites();

		// Obtain a device context for repainting the game
		HWND  hWindow = _pGame->GetWindow();
		HDC   hDC = GetDC(hWindow);

		// Paint the game to the offscreen device context
		GamePaint(_hOffscreenDC);

		// Blit the offscreen bitmap to the game screen
		BitBlt(hDC, 0, 0, _pGame->GetWidth(), _pGame->GetHeight(), _hOffscreenDC, 0, 0, SRCCOPY);

		// Cleanup
		ReleaseDC(hWindow, hDC);
	}
}

void HandleKeys()
{
	if (!_bGameOver)
	{
		// Move the car based upon left/right key presses
		POINT ptVelocity = _pCarSprite->GetVelocity();
		RECT rcPos = _pCarSprite->GetPosition();

		RECT  rcBounds = { 0, 0, 1050, 750 };

		ptVelocity.x = max(0,0);
		ptVelocity.y = max(0, 0);
		_pCarSprite->SetVelocity(ptVelocity);

		if (GetAsyncKeyState(VK_LEFT) < 0)
		{
			// Move left
			ptVelocity.x = max(-_speed_increase_counter - 1, -4);
			_pCarSprite->SetVelocity(ptVelocity);
			_psFollowBackground_Left->SetPosition(rcPos.left-2150,0);
			_psFollowBackground_Right->SetPosition(rcPos.right+200,0);
			

		}
		else if (GetAsyncKeyState(VK_RIGHT) < 0)
		{
			// Move right
			ptVelocity.x = min(_speed_increase_counter + 2, 6);
			_pCarSprite->SetVelocity(ptVelocity);
			_psFollowBackground_Left->SetPosition(rcPos.left - 2150, 0);
			_psFollowBackground_Right->SetPosition(rcPos.right + 200, 0);
		
		}
		else if (GetAsyncKeyState(VK_DOWN) < 0)
		{
			// Move down
			ptVelocity.y = min(_speed_increase_counter + 2, 6);
			_pCarSprite->SetVelocity(ptVelocity);
			_psFollowBackground_Bottom->SetPosition(-100, rcPos.top +200);
			_psFollowBackground_Top->SetPosition(-100, rcPos.bottom -1000);

		}
		else if (GetAsyncKeyState(VK_UP) < 0)
		{
			// Move up
			ptVelocity.y = min(-_speed_increase_counter - 1, -4);
			_pCarSprite->SetVelocity(ptVelocity);
			//_psFollowBackground_Top->SetVelocity(ptVelocity);
			_psFollowBackground_Top->SetPosition(-100, rcPos.bottom-1000);
			_psFollowBackground_Bottom->SetPosition(-100, rcPos.top +200);
		}

		// Fire missiles based upon spacebar presses
		if ((++_iFireInputDelay > 6) && GetAsyncKeyState(VK_SPACE) < 0 && GetAsyncKeyState(VK_UP) < 0 && _iDamage==1)
		{
			// Create a new missile sprite
			Sprite* pSprite = new Sprite(_pMissileBitmap, rcBounds, BA_DIE);
			pSprite->SetPosition(rcPos.left + 15, rcPos.top); // car's missile follow car position 
			pSprite->SetVelocity(0, -7);
			_pGame->AddSprite(pSprite);
			_psFollowBackground_Top->SetPosition(-100, rcPos.bottom - 1000);
			_psFollowBackground_Bottom->SetPosition(-100, rcPos.top + 200);
			// Play the missile (fire) sound
			PlaySound((LPCSTR)IDW_MISSILE, _hInstance, SND_ASYNC | SND_RESOURCE | SND_NOSTOP);
			_iDamage = 0;
			// Reset the input delay
			_iFireInputDelay = 0;
		}
		else if ((++_iFireInputDelay > 6) && GetAsyncKeyState(VK_SPACE) < 0 && GetAsyncKeyState(VK_DOWN) < 0 && _iDamage == 1)
		{
			// Create a new missile sprite
			Sprite* pSprite = new Sprite(_pMissileBitmap, rcBounds, BA_DIE);
			pSprite->SetPosition(rcPos.left + 15, rcPos.top-25); // car's missile follow car position 
			pSprite->SetVelocity(0, 7);
			_pGame->AddSprite(pSprite);
			_psFollowBackground_Bottom->SetPosition(-100, rcPos.top + 200);
			_psFollowBackground_Top->SetPosition(-100, rcPos.bottom - 1000);
			// Play the missile (fire) sound
			PlaySound((LPCSTR)IDW_MISSILE, _hInstance, SND_ASYNC | SND_RESOURCE | SND_NOSTOP);
			_iDamage = 0;
			// Reset the input delay
			_iFireInputDelay = 0;
		}
		else if ((++_iFireInputDelay > 6) && GetAsyncKeyState(VK_SPACE) < 0 && GetAsyncKeyState(VK_RIGHT) < 0 && _iDamage == 1)
		{
			// Create a new missile sprite
			Sprite* pSprite = new Sprite(_pMissileBitmap, rcBounds, BA_DIE);
			pSprite->SetPosition(rcPos.left + 15, rcPos.top); // car's missile follow car position 
			pSprite->SetVelocity(7, 0);
			_pGame->AddSprite(pSprite);
			_psFollowBackground_Left->SetPosition(rcPos.left - 2150, 0);
			_psFollowBackground_Right->SetPosition(rcPos.right + 200, 0);
			// Play the missile (fire) sound
			PlaySound((LPCSTR)IDW_MISSILE, _hInstance, SND_ASYNC | SND_RESOURCE | SND_NOSTOP);
			_iDamage = 0;
			// Reset the input delay
			_iFireInputDelay = 0;
		}
		else if ((++_iFireInputDelay > 6) && GetAsyncKeyState(VK_SPACE) < 0 && GetAsyncKeyState(VK_LEFT) < 0 && _iDamage == 1)
		{
			// Create a new missile sprite
			Sprite* pSprite = new Sprite(_pMissileBitmap, rcBounds, BA_DIE);
			pSprite->SetPosition(rcPos.left + 15, rcPos.top); // car's missile follow car position 
			pSprite->SetVelocity(-7, 0);
			_pGame->AddSprite(pSprite);
			_psFollowBackground_Left->SetPosition(rcPos.left - 2150, 0);
			_psFollowBackground_Right->SetPosition(rcPos.right + 200, 0);
			// Play the missile (fire) sound
			PlaySound((LPCSTR)IDW_MISSILE, _hInstance, SND_ASYNC | SND_RESOURCE | SND_NOSTOP);
			_iDamage = 0;
			// Reset the input delay
			_iFireInputDelay = 0;
		}

		else if ((++_iFireInputDelay > 6) && GetAsyncKeyState(VK_SPACE) < 0 && GetAsyncKeyState(VK_LEFT) < 0)
		{
			// Create a new missile sprite
			Sprite* pSprite = new Sprite(_pMissileBitmap_for_wall, rcBounds, BA_DIE);
			pSprite->SetPosition(rcPos.left + 15, rcPos.top); // car's missile follow car position 
			pSprite->SetVelocity(-7, 0);
			_pGame->AddSprite(pSprite);
			_psFollowBackground_Left->SetPosition(rcPos.left - 2000, 0);
			_psFollowBackground_Right->SetPosition(rcPos.right + 300, 0);
			// Play the missile (fire) sound
			PlaySound((LPCSTR)IDW_MISSILE, _hInstance, SND_ASYNC | SND_RESOURCE | SND_NOSTOP);
			// Reset the input delay
			_iFireInputDelay = 0;
		}

		else if ((++_iFireInputDelay > 6) && GetAsyncKeyState(VK_SPACE) < 0 && GetAsyncKeyState(VK_RIGHT) < 0)
		{
			// Create a new missile sprite
			Sprite* pSprite = new Sprite(_pMissileBitmap_for_wall, rcBounds, BA_DIE);
			pSprite->SetPosition(rcPos.left + 15, rcPos.top); // car's missile follow car position 
			pSprite->SetVelocity(7, 0);
			_pGame->AddSprite(pSprite);
			_psFollowBackground_Left->SetPosition(rcPos.left - 2000, 0);
			_psFollowBackground_Right->SetPosition(rcPos.right + 300, 0);
			// Play the missile (fire) sound
			PlaySound((LPCSTR)IDW_MISSILE, _hInstance, SND_ASYNC | SND_RESOURCE | SND_NOSTOP);
			// Reset the input delay
			_iFireInputDelay = 0;
		}

		else if ((++_iFireInputDelay > 6) && GetAsyncKeyState(VK_SPACE) < 0 && GetAsyncKeyState(VK_UP) < 0)
		{
			// Create a new missile sprite
			Sprite* pSprite = new Sprite(_pMissileBitmap_for_wall, rcBounds, BA_DIE);
			pSprite->SetPosition(rcPos.left + 15, rcPos.top); // car's missile follow car position 
			pSprite->SetVelocity(0, -7);
			_pGame->AddSprite(pSprite);
			_psFollowBackground_Bottom->SetPosition(-100, rcPos.top + 100);
			_psFollowBackground_Top->SetPosition(-100, rcPos.bottom - 1050);
			// Play the missile (fire) sound
			PlaySound((LPCSTR)IDW_MISSILE, _hInstance, SND_ASYNC | SND_RESOURCE | SND_NOSTOP);
			// Reset the input delay
			_iFireInputDelay = 0;
		}

		else if ((++_iFireInputDelay > 6) && GetAsyncKeyState(VK_SPACE) < 0 && GetAsyncKeyState(VK_DOWN) < 0)
		{
		Sprite* pSprite = new Sprite(_pMissileBitmap_for_wall, rcBounds, BA_DIE);
		pSprite->SetPosition(rcPos.left + 15, rcPos.top - 25); // car's missile follow car position 
		pSprite->SetVelocity(0, 7);
		_pGame->AddSprite(pSprite);
		_psFollowBackground_Bottom->SetPosition(-100, rcPos.top + 100);
		_psFollowBackground_Top->SetPosition(-100, rcPos.bottom - 1050);
		// Play the missile (fire) sound
		PlaySound((LPCSTR)IDW_MISSILE, _hInstance, SND_ASYNC | SND_RESOURCE | SND_NOSTOP);
		// Reset the input delay
		_iFireInputDelay = 0;
		}
	}

	// Start a new game based upon an Enter (Return) key press
	if (_bGameOver && (GetAsyncKeyState(VK_RETURN) < 0))
		// Start a new game
		NewGame();
}

void MouseButtonDown(int x, int y, BOOL bLeft)
{
}

void MouseButtonUp(int x, int y, BOOL bLeft)
{
}

void MouseMove(int x, int y)
{
}

void HandleJoystick(JOYSTATE jsJoystickState)
{
}

BOOL SpriteCollision(Sprite* pSpriteHitter, Sprite* pSpriteHittee)
{

	// See if a player missile and an alien have collided
	Bitmap* pHitter = pSpriteHitter->GetBitmap();
	Bitmap* pHittee = pSpriteHittee->GetBitmap();

	// For travel in maze with dont pass inside of walls
	if ((pHitter == _pGolfBallBitmap && (pHittee == _pCarBitmap)))
	{
		pSpriteHitter->SetVelocity(0, 0);
		pSpriteHittee->SetVelocity(0, 0);
		return TRUE;

	}
	if ((pHitter == _pGolfBallBitmap) && ((pHittee == _pSauronBitmap)) || (pHitter == _pCarBitmap) && ((pHittee == _pSauronBitmap)))
	{
		pSpriteHitter->SetVelocity(0, 0);
		switch (rand() % 8)
		{
		case 0:
			pSpriteHittee->SetVelocity(0, 4);
			break;
		case 1:
			pSpriteHittee->SetVelocity(0, -4);
			break;
		case 2:
			pSpriteHittee->SetVelocity(4, 0);
			break;
		case 3:
			pSpriteHittee->SetVelocity(-4, 0);
			break;
		}
		return TRUE;

	}
	if ((pHitter == _pGolfBallBitmap) && (pHittee == _pSmaughBitmap))
	{
		pSpriteHitter->SetVelocity(0, 0);
		switch (rand() % 8)
		{
		case 0:
			pSpriteHittee->SetVelocity(0, 4);
			break;
		case 1:
			pSpriteHittee->SetVelocity(0, -4);
			break;
		case 2:
			pSpriteHittee->SetVelocity(4, 0);
			break;
		case 3:
			pSpriteHittee->SetVelocity(-4, 0);
			break;
		}
		return TRUE;

	}
	if ((pHitter == _pGolfBallBitmap) && ((pHittee == _pAzogBitmap)  ))
	{
		pSpriteHitter->SetVelocity(0, 0);
		switch (rand() % 8)
		{
		case 0:
			pSpriteHittee->SetVelocity(0, 4);
			break;
		case 1:
			pSpriteHittee->SetVelocity(0, -4);
			break;
		case 2:
			pSpriteHittee->SetVelocity(4, 0);
			break;
		case 3:
			pSpriteHittee->SetVelocity(-4, 0);
			break;
		}
		return TRUE;
	}
	if ((pHitter == _pGolfBallBitmap) && ((pHittee == _pWarriorsBitmap)))
	{
		pSpriteHitter->SetVelocity(0, 0);
		switch (rand() % 8)
		{
		case 0:
			pSpriteHittee->SetVelocity(0, 4);
			break;
		case 1:
			pSpriteHittee->SetVelocity(0, -4);
			break;
		case 2:
			pSpriteHittee->SetVelocity(4, 0);
			break;
		case 3:
			pSpriteHittee->SetVelocity(-4, 0);
			break;
		}
		return TRUE;
	}
	if ((pHitter == _pGolfBallBitmap) && ((pHittee == _pNazgulBitmap)))
	{
		pSpriteHitter->SetVelocity(0, 0);
		switch (rand() % 8)
		{
		case 0:
			pSpriteHittee->SetVelocity(0, 4);
			break;
		case 1:
			pSpriteHittee->SetVelocity(0, -4);
			break;
		case 2:
			pSpriteHittee->SetVelocity(4, 0);
			break;
		case 3:
			pSpriteHittee->SetVelocity(-4, 0);
			break;
		}
		return TRUE;
	}
	if ((pHitter == _pGolfBallBitmap) && ((pHittee == _pThorinBitmap)))
	{
		pSpriteHitter->SetVelocity(0, 0);
		switch (rand() % 8)
		{
		case 0:
			pSpriteHittee->SetVelocity(0, 4);
			break;
		case 1:
			pSpriteHittee->SetVelocity(0, -4);
			break;
		case 2:
			pSpriteHittee->SetVelocity(4, 0);
			break;
		case 3:
			pSpriteHittee->SetVelocity(-4, 0);
			break;
		}
		return TRUE;
	}
	if (pHitter==_pCarBitmap && (pHittee==_pSauronBitmap || pHittee==_pNazgulBitmap || pHittee==_pAzogBitmap || pHittee==_pSmaughBitmap || pHittee==_pWarriorsBitmap || pHittee==_pThorinBitmap))
	{
		pSpriteHitter->SetVelocity(0, 0);
		switch (rand() % 4)
		{
		case 0:
			pSpriteHittee->SetVelocity(0, 4);
			break;
		case 1:
			pSpriteHittee->SetVelocity(0, -4);
			break;
		case 2:
			pSpriteHittee->SetVelocity(4, 0);
			break;
		case 3:
			pSpriteHittee->SetVelocity(-4, 0);
			break;
		}
		return TRUE;
	}
	if (pHitter == _pGolfBallBitmap && (pHittee == _pJMissileBitmap || pHittee == _pTMissileBitmap|| pHittee == _pBMissileBitmap))
	{
		pSpriteHittee->Kill();
	}

	// Frodo shot the wall and destroy wall and ýf a chance , frodo can get a award
	if ((pHitter == _pGolfBallBitmap && pHittee == _pMissileBitmap_for_wall) || (pHittee == _pGolfBallBitmap && pHitter == _pMissileBitmap_for_wall))
	{
		RECT rcBounds = { 0, 0, 1050, 750 };
		RECT rcPos;
		Sprite* pSprite;
		//pSpriteHittee->Kill();
		rcPos = pSpriteHitter->GetPosition();
		// Play the small explosion sound
		PlaySound((LPCSTR)IDW_LGEXPLODE, _hInstance, SND_ASYNC | SND_RESOURCE);
		
		
		if (_counter_to_destroy_wall == 3)
		{
			if (pHitter == _pGolfBallBitmap)
			{
				pSpriteHitter->Kill();
			}
			else
			{
				pSpriteHittee->Kill();
			}
			switch (rand() % 4)
			{
			case 0:
				pSprite = new Sprite(_pHealthBitmap, rcBounds);
				pSprite->SetPosition(rcPos.left, rcPos.top);
				_pGame->AddSprite(pSprite);
				_counter_to_destroy_wall = 0;
				break;
			case 1:
				pSprite = new Sprite(_pPowerBitmap, rcBounds);
				pSprite->SetPosition(rcPos.left, rcPos.top);
				_pGame->AddSprite(pSprite);
				_counter_to_destroy_wall = 0;
				break;
			case 2:
				pSprite = new Sprite(_pSpeedBitmap, rcBounds);
				pSprite->SetPosition(rcPos.left, rcPos.top);
				_pGame->AddSprite(pSprite);
				_counter_to_destroy_wall = 0;
				break;
			case 3:
				pSprite = new Sprite(_pDamageBitmap, rcBounds);
				pSprite->SetPosition(rcPos.left, rcPos.top);
				_pGame->AddSprite(pSprite);
				_counter_to_destroy_wall = 0;
				break;
			}
			_counter_to_destroy_wall = 0;
		}
		if (pHittee == _pMissileBitmap_for_wall)
		{
			pSpriteHittee->Kill();
		}
		else
		{
			pSpriteHitter->Kill();
		}
	
		_counter_to_destroy_wall = _counter_to_destroy_wall + 1;
		// Create a large explosion sprite at the alien's position


	   // rcPos = pSpriteHitter->GetPosition();
		pSprite = new Sprite(_pLgExplosionBitmap, rcBounds);
		pSprite->SetNumFrames(8, TRUE);
		pSprite->SetPosition(rcPos.left, rcPos.top);
		_pGame->AddSprite(pSprite);
	}

	

	//if frodo go to on heart icon , frodo's live are one up
	if (pHittee == _pHealthBitmap && pHitter == _pCarBitmap)
	{
		RECT rcBounds = { 0, 0, 1050, 750 };
		RECT rcPos;
		rcPos = pSpriteHitter->GetPosition();
		// Play the small explosion sound
		PlaySound((LPCSTR)IDW_LGEXPLODE, _hInstance, SND_ASYNC | SND_RESOURCE);

		pSpriteHittee->Kill();
		_ring_counter = _ring_counter + 1;

		if (_ring_counter == 5)
		{
			_stage_level = _stage_level + 1;
			_ring_counter = 1;
			//NewGame();
		}
	}

	// if frodo go to on speed icon , frodo's speed is increase
	if (pHittee == _pSpeedBitmap && pHitter == _pCarBitmap)
	{
		RECT rcBounds = { 0, 0, 1050, 750 };
		RECT rcPos;
		rcPos = pSpriteHitter->GetPosition();
		// Play the small explosion sound
		PlaySound((LPCSTR)IDW_LGEXPLODE, _hInstance, SND_ASYNC | SND_RESOURCE);

		pSpriteHittee->Kill();
		_speed_increase_counter = _speed_increase_counter + 1;
		

	}

	// if frodo take power icon , frodo attack speed will increase
	if (pHittee == _pPowerBitmap && pHitter == _pCarBitmap)
	{
		PlaySound((LPCSTR)IDW_LGEXPLODE, _hInstance, SND_ASYNC | SND_RESOURCE);

		pSpriteHittee->Kill();
		_iFireInputDelay = _iFireInputDelay + 2;
	}

	//if frodo take damage icon , frodo hit higher than before damage
	if (pHittee == _pDamageBitmap && pHitter == _pCarBitmap)
	{
		PlaySound((LPCSTR)IDW_LGEXPLODE, _hInstance, SND_ASYNC | SND_RESOURCE);

		pSpriteHittee->Kill();
		_iDamage = 1;
	}

	if ((pHitter == _pMissileBitmap && (pHittee == _pSauronBitmap ||
		pHittee == _pSmaughBitmap || pHittee == _pAzogBitmap || pHittee==_pWarriorsBitmap || pHittee==_pNazgulBitmap))  ||
		(pHittee == _pMissileBitmap && (pHitter == _pSauronBitmap ||
			pHitter == _pSmaughBitmap || pHitter == _pAzogBitmap || pHitter == _pWarriorsBitmap || pHitter == _pNazgulBitmap)))
	{
		// Play the small explosion sound
		PlaySound((LPCSTR)IDW_LGEXPLODE, _hInstance, SND_ASYNC |
			SND_RESOURCE);

		// Kill both sprites
		pSpriteHitter->Kill();
		pSpriteHittee->Kill();

		// Create a large explosion sprite at the alien's position
		RECT rcBounds = { 0, 0, 1050, 750 };
		RECT rcPos;
		if (pHitter == _pMissileBitmap)
			rcPos = pSpriteHittee->GetPosition();
		else
			rcPos = pSpriteHitter->GetPosition();
		Sprite* pSprite = new Sprite(_pLgExplosionBitmap, rcBounds);
		pSprite->SetNumFrames(8, TRUE);
		pSprite->SetPosition(rcPos.left, rcPos.top);
		_pGame->AddSprite(pSprite);
		/*AlienSprite*  p_Sprite;
		p_Sprite = new AlienSprite(_pBlobboBitmap, rcBounds, BA_BOUNCE);
		p_Sprite->SetNumFrames(2);
		p_Sprite->SetPosition(55, 50);
		_pGame->AddSprite(p_Sprite);*/

		// Update the score
		_iScore += 25;
		_iDifficulty = max(80 - (_iScore / 20), 20);
	}

	// See if an alien missile has collided with the car
	if ((pHitter == _pCarBitmap && (pHittee == _pBMissileBitmap ||
		pHittee == _pJMissileBitmap || pHittee == _pTMissileBitmap)) ||
		(pHittee == _pCarBitmap && (pHitter == _pBMissileBitmap ||
			pHitter == _pJMissileBitmap || pHitter == _pTMissileBitmap)))
	{
		// Play the large explosion sound
		PlaySound((LPCSTR)IDW_LGEXPLODE, _hInstance, SND_ASYNC |
			SND_RESOURCE);

		// Kill the missile sprite
		if (pHitter == _pCarBitmap)
			pSpriteHittee->Kill();
		else
			pSpriteHitter->Kill();

		// Create a large explosion sprite at the car's position
		RECT rcBounds = { 0, 0, 1050, 750 };
		RECT rcPos;
		if (pHitter == _pCarBitmap)
			rcPos = pSpriteHitter->GetPosition();
		else
			rcPos = pSpriteHittee->GetPosition();
		Sprite* pSprite = new Sprite(_pLgExplosionBitmap, rcBounds);
		pSprite->SetNumFrames(8, TRUE);
		pSprite->SetPosition(rcPos.left, rcPos.top);
		_pGame->AddSprite(pSprite);

		// Move the car back to the start
		_pCarSprite->SetPosition(50, 650);

		// See if the game is over
		if (--_iNumLives == 0)
		{
			// Play the game over sound
			PlaySound((LPCSTR)IDW_GAMEOVER, _hInstance, SND_ASYNC |
				SND_RESOURCE);
			_bGameOver = TRUE;
		}
	}

	return FALSE;
}

void SpriteDying(Sprite* pSprite)
{
	// See if an alien missile sprite is dying
	if (pSprite->GetBitmap() == _pBMissileBitmap ||
		pSprite->GetBitmap() == _pJMissileBitmap ||
		pSprite->GetBitmap() == _pTMissileBitmap)
	{
		// Play the small explosion sound
		PlaySound((LPCSTR)IDW_SMEXPLODE, _hInstance, SND_ASYNC |
			SND_RESOURCE | SND_NOSTOP);

		// Create a small explosion sprite at the missile's position
		RECT rcBounds = { 0, 0, 1000, 750 };
		RECT rcPos = pSprite->GetPosition();
		Sprite* pSprite = new Sprite(_pSmExplosionBitmap, rcBounds);
		pSprite->SetNumFrames(8, TRUE);
		pSprite->SetPosition(rcPos.left, rcPos.top);
		_pGame->AddSprite(pSprite);
	}
}

//-----------------------------------------------------------------
// Functions
//-----------------------------------------------------------------
void NewGame()
{
	// Clear the sprites
	_pGame->CleanupSprites();
	RECT rcBounds = { 0, 0, 1050, 750 };
	int counter = 0;
	for (int y = 0; y < maxrow; y++) {
		for (int x = 0; x < maxcol; x++) {
			if (map[y][x] >= 100 && counter<150)
			{
				_pGolfSprite = new Sprite(_pGolfBallBitmap, rcBounds, BA_BOUNCE);
				_pGolfSprite->SetPosition(x * 50, y * 50);
				_pGame->AddSprite(_pGolfSprite);
				counter = counter + 1;
			}
		}
	}

	// Create the car sprite < 21*50, 15*50
	_pCarSprite = new Sprite(_pCarBitmap, rcBounds, BA_WRAP);
	_pCarSprite->SetPosition(50, 650);
	_pCarSprite->SetNumFrames(2);
	_pGame->AddSprite(_pCarSprite);
	_pThorinSprite = new Sprite(_pThorinBitmap,rcBounds,BA_WRAP);
	_pThorinSprite->SetPosition(150, 650);
	_pThorinSprite->SetNumFrames(2);
	_pThorinSprite->SetVelocity(0, 1);
	_pGame->AddSprite(_pThorinSprite);
	_pSauronSprite = new AlienSprite(_pSauronBitmap, rcBounds, BA_WRAP);
	_pSauronSprite->SetPosition(50, 50);
	_pSauronSprite->SetVelocity(5, 0);
	_pSauronSprite->SetNumFrames(2);
	_pGame->AddSprite(_pSauronSprite);
	_pSmaughSprite = new AlienSprite(_pSmaughBitmap, rcBounds, BA_WRAP);
	_pSmaughSprite->SetPosition(850, 50);
	_pSmaughSprite->SetVelocity(0, 7);
	_pSmaughSprite->SetNumFrames(2);
	_pGame->AddSprite(_pSmaughSprite);
	_pAzogSprite = new AlienSprite(_pAzogBitmap, rcBounds, BA_WRAP);
	_pAzogSprite->SetPosition(850, 650);
	_pAzogSprite->SetVelocity(-2, 0);
	_pAzogSprite->SetNumFrames(3);
	_pGame->AddSprite(_pAzogSprite);
	_psFollowBackground_Top = new Sprite(_pbFollowBackground, rcBounds, BA_WRAP);
	_psFollowBackground_Top->SetPosition(-100, -250);
	_psFollowBackground_Top->SetZOrder(150);
	_pGame->AddSprite(_psFollowBackground_Top);
	_psFollowBackground_Bottom = new Sprite(_pbFollowBackground, rcBounds, BA_WRAP);
	_psFollowBackground_Bottom->SetPosition(-100, 750);
	_psFollowBackground_Bottom->SetZOrder(150);
	_pGame->AddSprite(_psFollowBackground_Bottom);
	_psFollowBackground_Left = new Sprite(_pbFollowBackground_R_L, rcBounds, BA_WRAP);
	_psFollowBackground_Left->SetPosition(-2000, 450);
	_psFollowBackground_Left->SetZOrder(150);
	_pGame->AddSprite(_psFollowBackground_Left);
	_psFollowBackground_Right = new Sprite(_pbFollowBackground_R_L, rcBounds, BA_WRAP);
	_psFollowBackground_Right->SetPosition(300, 350);
	_psFollowBackground_Right->SetZOrder(150);
	_pGame->AddSprite(_psFollowBackground_Right);

	// Initialize the game variables
	_iFireInputDelay = 0;
	_iScore = 0;
	_iNumLives = 3;
	_iDifficulty = 80;
	_bGameOver = FALSE;

	// Play the background music
	_pGame->PlayMIDISong();
}

void AddAlien()
{
	
  // Create a new random alien sprite 21*50, 15*50
  RECT          rcBounds = { 0, 0, 1050, 750 };

  switch (rand() % 4)
  {
  case 0:
	  sauron_counter = sauron_counter + 1;
	  _pNazgulSprite = new AlienSprite(_pNazgulBitmap, rcBounds, BA_BOUNCE);
	  _pNazgulSprite->SetNumFrames(2);
	  _pNazgulSprite->SetPosition(50,50);
	  _pNazgulSprite->SetVelocity(5, 0);
	  _pGame->AddSprite(_pNazgulSprite);
	  if (sauron_counter == 5)
	  {
		  _pSauronSprite = new AlienSprite(_pSauronBitmap, rcBounds, BA_BOUNCE);
		  _pSauronSprite->SetNumFrames(2);
		  _pSauronSprite->SetPosition(850, 50);
		  _pSauronSprite->SetVelocity((rand() % 7) - 2, (rand() % 7) - 2);
		  _pGame->AddSprite(_pSauronSprite);
		sauron_counter = 0;
	  }


	break;
  case 1:
	  azog_counter = azog_counter + 1;
	  _pWarriorsSprite = new AlienSprite(_pWarriorsBitmap, rcBounds, BA_BOUNCE);
	  _pWarriorsSprite->SetNumFrames(2);
	  _pWarriorsSprite->SetPosition(850, 650);
	  _pWarriorsSprite->SetVelocity(-2, 0);
	  _pGame->AddSprite(_pWarriorsSprite);
	  if (azog_counter == 5)
	  {
		  _pAzogSprite = new AlienSprite(_pAzogBitmap, rcBounds, BA_BOUNCE);
		  _pAzogSprite->SetNumFrames(3);
		  _pAzogSprite->SetPosition(850, 650);
		  _pAzogSprite->SetVelocity((rand() % 7) - 2, (rand() % 7) - 2);
		  _pGame->AddSprite(_pAzogSprite);
		  azog_counter = 0;
	  }


	  break;

  }
 
}
void add_monster()
{

}
void add_wall()
{

}

