#pragma once
#include "Scene.h"
//! First scene, inheriting from Scene
class scene1 : public Scene
{
public:
	//! constructor from scene1, which loads the level list and the first json file
	scene1() { loadLevelList(); loadLevel(0); };
};