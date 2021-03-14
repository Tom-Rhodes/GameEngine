#pragma once
#include "GameObject.h"
#include "Model.h"
#include <time.h>
#include <json/json.h>
#include <fstream>
//! Parent class for the three scenes
class Scene
{
public:
	std::vector<GameObject*>* getModelVec(); /*!< Initialises a pointer vector of GameObjects pointers that will point to the game objects after they've had their components added*/
	std::vector<std::string>* getLevels();	/*!< The getter for a pointer vector of strings used to hold the json names from loadLevelList()*/
	GameObject getBG();
	//! Loads a specific json with the model data.
	/*!
		Loads model data from a json file specified by the levelNum parameter.
		This includes the position, name, and model type of the GameObject.
		\param levelNum integer used to specify the level t o load from the getLevels() function
	*/
	void loadLevel(int levelNum);	
	//! Loads a text file with a list of json levels
	/*! Loads a text file and stores each json file name in a vector (v_levels) which is accessed by the getter function above.*/
	void loadLevelList();
	//! Clears the model vector for a new level
	void removeLevel();
private:	
	std::fstream jsonData;//!< An fstream to open the json data in loadLevel()
	Json::Value root;	//!< Initial Json::Value to access the "GameObjects" in the json file
	Json::Reader reader;	//!< A reader used to read the data in Json and store in root
	GameObject m_playerBackground;
	std::vector<GameObject*> m_modelVector; 	//!< A vector of GameObject pointer used to hold the GameObjects, accessed via getModelVec();
	std::vector<std::string> v_levels;	//!< Vector of strings for the names of the json levels, accessed via getLevels().
	time_t timer;	//!< A timer used to count duration to automate changing of scenes
};