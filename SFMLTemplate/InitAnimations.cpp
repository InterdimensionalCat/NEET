#include "stdafx.h"
#include "InitAnimations.h"
#include "Animation.h"

void InitAnimations() {
	addAnimation(new Animation("Player_Idle", 128, 256, 60, 1));
	addAnimation(new Animation("Player_Move_Right", 128, 256, 5, 2));
	addAnimation(new Animation("Player_Move_Left", 128, 256, 5, 3));
	addAnimation(new Animation("Player_TurnRun_Right", 128, 256, 15, 4));
	addAnimation(new Animation("Player_TurnRun_Left", 128, 256, 15, 5));
	addAnimation(new Animation("Player_Aerial", 128, 256, 2, 6));
}