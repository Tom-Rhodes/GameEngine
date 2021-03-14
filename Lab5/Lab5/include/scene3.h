#pragma once
#include "Scene.h"
//! Third scene, inheriting from Scene
class scene3 : public Scene
{
public:
	//! constructor from scene2, which empties the previous GameObjects, loads the level list and the third json file
	scene3() { removeLevel(); loadLevelList(); loadLevel(2); };
};