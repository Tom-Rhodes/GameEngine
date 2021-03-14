#pragma once
#include "Scene.h"
//! Second scene, inheriting from Scene
class scene2 : public Scene
{
public:
	//! constructor from scene2, which empties the previous GameObjects, loads the level list and the second json file
	scene2() { removeLevel(); loadLevelList(); loadLevel(1); };
};