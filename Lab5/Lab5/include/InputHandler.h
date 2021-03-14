#pragma once
#include <map>
#include "GameObject.h"
#include <vector>
#include "TransformComponent.h"
#include "Camera.h"
#include <json/json.h>
#include <fstream>
#include <sstream>
#include <string>

//! Abstract class for handling input
class InputCommand
{
public:
	virtual ~InputCommand() {}
	virtual void execute(Camera* camera) {};
	virtual void execute(Camera* camera, double xValue, double yValue) {};
	virtual void execute(GameObject* gameObject) {};
};

//////////////////
//TRANSFORMATION//
//////////////////
//! Class for translating up
class TransformUp : public InputCommand
{
public:


	void execute(Camera* camera) override {
		if (camera)
			camera->translate(glm::vec3(0.0f, 0.2f, 0.0f));
	}
};
//! Class for translating down
class TransformDown : public InputCommand
{
public:
	void execute(Camera* camera) override {

		if (camera)
			camera->translate(glm::vec3(0.0f, -0.2f, 0.0f));

	}
};
//! Class for translating left
class TransformLeft : public InputCommand
{
public:


	void execute(Camera* camera) override {
		if (camera)
			camera->translate(glm::vec3(0.2f, 0.0f, 0.0f));
	}
};
//! Class for translating right
class TransformRight : public InputCommand
{
public:
	void execute(Camera* camera) override {

		if (camera)
			camera->translate(glm::vec3(-0.2f, 0.0f, 0.0f));

	}
};
//! Class for translating forward
class TransformForward : public InputCommand
{
public:
	void execute(Camera* camera) override {
		if (camera)
			camera->translate(glm::vec3(0.0f, 0.0f, 0.2f));
	}
};
//! Class for translating backward
class TransformBackward : public InputCommand
{
public:
	void execute(Camera* camera) override {

		if (camera)
			camera->translate(glm::vec3(0.0f, 0.0f, -0.2f));

	}
};
//! Class to increase FOV
class FOVUp : public InputCommand
{
public:
	void execute(Camera* camera) override
	{
		if (camera->getFOV() >= 90.0f) {
			camera->setFOV(90.f);
		}
		else
		{
			camera->setFOV(camera->getFOV() + 5);
		}
	}
};
//! Class to decrease FOV
class FOVDown : public InputCommand
{
public:
	void execute(Camera* camera) override
	{
		if (camera) {
			if (camera->getFOV() <= 30.0f) {
				camera->setFOV(30.f);
			}
			else
			{
				camera->setFOV(camera->getFOV() - 5);
			}
		}
	}
};
//! Class to reset FOV to default of 45
class FOVReset : public InputCommand
{
public:
	void execute(Camera* camera) override
	{
		if (camera) {
			camera->setFOV(45.0f);
		}
	}
};
//! Class to process mouse position based rotation
class Rotate : public InputCommand
{
public:
	void execute(Camera* camera, double xValue, double yValue) override
	{
		if (camera)
			camera->teaRotate(xValue*0.004f, yValue*0.004f);
	}
};

struct InputHandler
{
	Camera* camera;

	std::map<int, InputCommand*> m_keyMapping;	//! Map to hold the key codes and their InputCommand class
	std::map<int, InputCommand*> m_mouseMapping; //! Map to hold the mouse button codes and their InputCommand class
	std::map<int, InputCommand*> m_scrollMapping; //! Map to hold the scroll directions and their InputCommand class

	char key = NULL;

	double lastCursorX = 0.0, lastCursorY = 0.0, currCursorX = 0.0, currCursorY = 0.0;

	InputHandler(Camera* cam) : camera(cam)
	{
		std::fstream jsonData;
		Json::Value root;
		Json::Reader reader;
		std::string configFile("assets/config/config.json");
		//! Opens the file from the file path defined by configFile, which is then interpreted by the reader
		jsonData.open(configFile);
		if (!reader.parse(jsonData, root))
		{
			std::cout << "Failed to parse data from: " << configFile << reader.getFormattedErrorMessages();
		}
		//! Defines each object array from the Json to a Json::Value
		const Json::Value configKeys = root["ConfigKeys"];
		const Json::Value configMBs = root["ConfigMBs"];
		const Json::Value configScroll = root["ConfigScroll"];
		/*! \brief Itterators for the inputs
			These are itterators for the three forms of input read from the Json. Each gets their input, key, button or scroll direction,
			and adds that to the map with the respective class also defined in the Json.
		*/
		//!Itterates through the ConfigKeys from the Json, adding both the key and the class to the map
		for (int i{ 0 }; i < configKeys.size(); i++)
		{
			std::cout << configKeys[i]["name"].asString() << " loaded with key: " << configKeys[i]["key"].asString() << std::endl;
			std::string jKey = configKeys[i]["key"].asString();
			int jClass = configKeys[i]["class"].asInt();
			m_keyMapping[int(jKey[0])] = getKeyCommand(jClass);
		}		
		//!Itterates through the ConfigMBs from the Json, adding both the button and the class to the map
		for (int i{ 0 }; i < configMBs.size(); i++)
		{
			std::cout << configMBs[i]["name"].asString() << " loaded with key: " << configMBs[i]["key"].asString() << std::endl;
			std::string jKey = configMBs[i]["key"].asString();
			int jClass = configMBs[i]["class"].asInt();
			m_mouseMapping[int(jKey[0])] = getMBCommand(jClass);
		}
		//!Itterates through the ConfigtScroll from the Json, adding both the scroll direction and the class the map
		for (int i{ 0 }; i < configScroll.size(); i++)
		{
			std::cout << configScroll[i]["name"].asString() << " loaded with scroll direction: " << configScroll[i]["scrollDir"].asString() << std::endl;
			int jKey = configScroll[i]["scrollDir"].asInt();
			int jClass = configScroll[i]["class"].asInt();
			m_scrollMapping[jKey] = getSCommand(jClass);
		}
	}
	//! Void to handle the inputs from the game, passing the buffers and any other variables provided by the callbacks.
	void handleInputs(const std::vector<bool>& keyBuffer, const std::vector<bool>& mouseBuffer, int& scroll_dir, std::vector<double>& mouse_pos)
	{
		//! \brief For loop to iterate through and execute and pressed key
		/*! This loop iterates through all the key codes in m_mouseMapping, defined by the buffer size in GLFW_EngineCore.
		It checks if any have been set to true, which occurs only when the button has been pressed.
		This then executes the appropriate class which is also set in the map with the key code above.
		*/
		for (const auto& mapEntry : m_mouseMapping)
		{
			if (mouseBuffer[mapEntry.first])
			{
				if (mapEntry.first != key)
				{
					std::cout << char(mapEntry.first) << " pressed" << endl;
					key = mapEntry.first;
				}
				mapEntry.second->execute(camera);
			}

		}
		for (const auto& mapEntry : m_keyMapping)
		{
			if (keyBuffer[mapEntry.first])
			{
				mapEntry.second->execute(camera);
			}

		}
		//! This checks if the scroll direction is positive or negative and executes a class accordingly
		if (scroll_dir > 0)
		{
			m_scrollMapping[0]->execute(camera);
		}
		else if (scroll_dir < 0)
		{
			m_scrollMapping[1]->execute(camera);

		}
		else {}
		scroll_dir = 0;

		/*! \brief Mouse movement code
			This is the code that handles the movement of the mouse that's passed in as a vector from the callback.
			It first gets the difference between the last position and the current position.
			This is initialises a new pointer to an InputCommand class of Rotate.
			It then executes this, passing through the difference between mouse positions, before replacing the old mouse positions with the new.
		*/
		currCursorX = mouse_pos.at(0);
		currCursorY = mouse_pos.at(1);

		float deltaX = (float)(lastCursorX - currCursorX);
		float deltaY = (float)(lastCursorY - currCursorY);

		InputCommand* rotate = new Rotate;
		rotate->execute(camera, deltaX, deltaY);

		lastCursorX = currCursorX;
		lastCursorY = currCursorY;
	}
	//!These are the switches that return the class depending on the input type and key pressed.
	InputCommand* getKeyCommand(int p_iClass)
	{
		switch (p_iClass)
		{
		case 1:
			return new TransformForward;
			break;
		case 2:
			return new TransformLeft;
			break;
		case 3:
			return new TransformBackward;
			break;
		case 4:
			return new TransformRight;
			break;
		case 5:
			return new TransformUp;
			break;
		case 6:
			return new TransformDown;
			break;
		}
	}

	InputCommand* getMBCommand(int p_iKey)
	{
		switch (p_iKey)
		{
		case 0:
			return new FOVUp;
			break;
		case 1:
			return new FOVDown;
			break;
		case 2:
			return new FOVReset;
			break;
		}
	}

	InputCommand* getSCommand(int p_iDir)
	{
		switch (p_iDir)
		{
		case 0:
			return new FOVDown;
			break;
		case 1:
			return new FOVUp;
			break;
		}
	}
};
