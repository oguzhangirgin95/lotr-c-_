//-----------------------------------------------------------------
// Alien Sprite Object
// C++ Source - AlienSprite.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "AlienSprite.h"

//-----------------------------------------------------------------
// External Global Variables
//-----------------------------------------------------------------
extern Bitmap* _pBlobboBitmap;
extern Bitmap* _pBMissileBitmap;
extern Bitmap* _pJellyBitmap;
extern Bitmap* _pJMissileBitmap;
extern Bitmap* _pTimmyBitmap;
extern Bitmap* _pTMissileBitmap;
extern Bitmap* _pGolfBallBitmap;
extern Bitmap* _pSauronBitmap;
extern Bitmap* _pSmaughBitmap;
extern Bitmap* _pAzogBitmap;
extern Bitmap* _pWarriorsBitmap;
extern Bitmap* _pNazgulBitmap;
extern int     _iDifficulty;

//-----------------------------------------------------------------
// AlienSprite Constructor(s)/Destructor
//-----------------------------------------------------------------
AlienSprite::AlienSprite(Bitmap* pBitmap, RECT& rcBounds,
	BOUNDSACTION baBoundsAction) : Sprite(pBitmap, rcBounds,
		baBoundsAction)
{
}

AlienSprite::~AlienSprite()
{
}

//-----------------------------------------------------------------
// AlienSprite General Methods
//-----------------------------------------------------------------
SPRITEACTION AlienSprite::Update()
{
	// Call the base sprite Update() method
	SPRITEACTION saSpriteAction;
	saSpriteAction = Sprite::Update();

	// See if the alien should fire a missile
	if ((rand() % (_iDifficulty / 2)) == 0)
		saSpriteAction |= SA_ADDSPRITE;

	return saSpriteAction;
}

Sprite* AlienSprite::AddSprite()
{
	// Create a new missile sprite
	RECT    rcBounds = { 0, 0, 1050, 750 };
	RECT    rcPos = GetPosition();
	Sprite* pSprite = NULL;
	
	switch (rand() % 5)
	{
	case 0:
		if (GetBitmap() ==_pSauronBitmap)
		{
			// Blobbo missile
			pSprite = new Sprite(_pBMissileBitmap, rcBounds, BA_DIE);
			pSprite->SetVelocity(0, 7);
			pSprite->SetPosition(rcPos.left + (GetWidth() / 2), rcPos.right);
		}
		else if (GetBitmap() == _pSmaughBitmap)
		{
			// Jelly missile
			pSprite = new Sprite(_pJMissileBitmap, rcBounds, BA_DIE);
			pSprite->SetVelocity(0, 5);
			pSprite->SetPosition(rcPos.left + (GetWidth() / 2), rcPos.bottom);
		}
		else if (GetBitmap() == _pAzogBitmap)
		{
			// Timmy missile
			pSprite = new Sprite(_pTMissileBitmap, rcBounds, BA_DIE);
			pSprite->SetVelocity(0, 3);
			pSprite->SetPosition(rcPos.left + (GetWidth() / 2), rcPos.left);
		}
		else if (GetBitmap() == _pNazgulBitmap)
		{
			// Timmy missile
			pSprite = new Sprite(_pBMissileBitmap, rcBounds, BA_DIE);
			pSprite->SetVelocity(0, 3);
			pSprite->SetPosition(rcPos.left + (GetWidth() / 2), rcPos.left);
		}
		else if (GetBitmap() == _pWarriorsBitmap)
		{
			// Timmy missile
			pSprite = new Sprite(_pTMissileBitmap, rcBounds, BA_DIE);
			pSprite->SetVelocity(0, 3);
			pSprite->SetPosition(rcPos.left + (GetWidth() / 2), rcPos.left);
		}
		break;
	}
	




	// Set the missile sprite's position and return it

	return pSprite;
}
