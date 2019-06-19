#include "stdafx.h"
#include "SceneManager.h"


SceneManager::SceneManager(string name)
{
	load(name);
	currentScene = new Scene(name);
}


SceneManager::~SceneManager()
{

}

void SceneManager::load(string name) {
	
}