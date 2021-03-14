#include "Scene.h"
#include <json/json.h>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <TransformComponent.h>
#include <ModelComponent.h>
#include <sstream>

#include <time.h>
//! This is the funtion to load the text document listing the Json levels.
void Scene::loadLevelList()
{
	ifstream levelListFile;
	std::stringstream ss;
	std::string s;
	std::string s_levelListPath("assets/levels/levelList.txt");
	levelListFile.open(s_levelListPath, ios_base::in);
	//! After opening the document from the path, it then itirates through the list and pushes the level back on a a vector.
	if (levelListFile.is_open())
	{
		for (int i = 0; i < 3; i++)
		{
			std::getline(levelListFile, s);
			getLevels()->push_back(s);
			std::cout << s << " stored from " << s_levelListPath << std::endl;
		}
	}
	else
	{
		std::cout << "Error loading: " << s_levelListPath << std::endl;
	}
}

//!This level loader is used to load the Json file and then attach the model and other data to a GameObject through components.
void Scene::loadLevel(int levelNum)
{	
	std::fstream jsonData;
	Json::Value root;
	Json::Reader reader;
	jsonData.open(("assets/levels/"+ getLevels()->at(levelNum)).c_str());
	if (!reader.parse(jsonData, root))
	{
		std::cout << "Failed to parse data from: " << getLevels()->at(levelNum) <<".json " << reader.getFormattedErrorMessages();
	}
	else {
		std::cout << "Json loaded from: assets/levels/" << getLevels()->at(levelNum) << std::endl;
		//! After reading the data, it extracts the GameObjects array, and iterates through it.
		const Json::Value gameObjects = root["GameObjects"];
		for (int i{ 0 }; i < gameObjects.size(); i++)
		{
			std::cout << gameObjects[i]["name"].asString() << " loaded\n";
			float x, y, z;
			//! While iterating through it, it acquires the positions and saves them as a vec3.
			const Json::Value posNode = gameObjects[i]["position"];
			x = posNode[0].asFloat();
			y = posNode[1].asFloat();
			z = posNode[2].asFloat();

			glm::vec3 pos(x, y, z);
			
			const Json::Value jType = gameObjects[i]["type"];
			//Here is acquires the model type that was specified in the file and loads the .obj file of that model
			Model* model = new Model("assets/models/" + jType.asString()+".obj");
			GameObject* l_goTemp = new GameObject();
			//!The position and type data is then added to the temporary GameObject before being pushed back onto the GameObject vector.
			l_goTemp->addComponent(new TransformComponent(pos));
			l_goTemp->addComponent(new ModelComponent(model));
			getModelVec()->push_back(l_goTemp);
		}
	}
}
//! This function clears the GameObject array to be used again
void Scene::removeLevel()
{
	getModelVec()->clear();
}
//! This returns the level list
std::vector<std::string>* Scene::getLevels()
{
	return &v_levels;
}
//! This return the GameObject vector
std::vector<GameObject*>* Scene::getModelVec()
{
	return &m_modelVector;
}
GameObject Scene::getBG()
{
	return m_playerBackground;
}