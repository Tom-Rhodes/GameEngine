#pragma once

#include "Model.h"
#include "ModelComponent.h"
#include "GLFW_EngineCore.h"
#include "InputHandler.h"
#include "GameObject.h"
#include "Camera.h"
#include "Scene.h"
#include "scene1.h"
#include <json/json.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
//! Game class that runs most updated functions
class Game
{
public:
	Game();
	GLFW_EngineCore* m_engineInterfacePtr;
	InputHandler* m_inputHandler;
	Scene* m_currentScene = new scene1();
	Camera m_camera;
	
	double duration;	//!< double used in time tracking for scene loading
	clock_t timer;	//!< clock used to track time passed for scene loading
	bool level1Load = false, level2Load = false, level3Load = false; //!< bools to prevent reloading of the same level

	void update();
	void render();

private:
};