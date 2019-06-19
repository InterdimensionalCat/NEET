#include "stdafx.h"
#include "InitAnimations.h"
#include "Animation.h"

void InitAnimations() {
	//addAnimation(new Animation("Player_Idle1", 128, 256, 60*4, 1, 2));
	addAnimation(new Animation("Player_Idle1", 128, 256, 60 * 4, 1, 2));
	addAnimation(new Animation("Player_Move_Right2", 128, 256, 5 * 4, 2, 4));
	addAnimation(new Animation("Player_Move_Left2", 128, 256, 5 * 4, 3, 4));
	addAnimation(new Animation("Player_TurnRun_Right", 128, 256, 15 * 4, 4, 2));
	addAnimation(new Animation("Player_TurnRun_Left", 128, 256, 15 * 4, 5, 2));
	addAnimation(new Animation("Player_Aerial1", 128, 256, 5 * 40, 6, 4));
}