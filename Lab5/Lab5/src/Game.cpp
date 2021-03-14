#include "Game.h"
#include "TransformComponent.h"
#include "ColourComponent.h"
#include <Scene.h>
#include <scene2.h>
#include <scene3.h>
#include <json/json.h>
#include <fstream>
#include <sstream>

Game::Game()
{
	timer = clock();
	m_inputHandler = new InputHandler(&m_camera);

	for (int i = 0 ; i < m_currentScene->getModelVec()->size() ; i++)
	{		
		m_engineInterfacePtr = nullptr;
		m_currentScene->getBG().addComponent(new RedComponent);
		m_currentScene->getBG().addComponent(new GreenComponent);
		m_currentScene->getBG().addComponent(new BlueComponent);
	}
}

void Game::update()
{
	duration = (clock() - timer) / (double)CLOCKS_PER_SEC;
	//std::cout << duration << endl;
	if ((int(duration) == 10) && (!level2Load))
	{
		m_currentScene = new scene2();
		level2Load = true;
		std::cout << "level 2 loaded" << endl;
	}
	if ((int(duration) == 20) && (!level3Load))
	{
		m_currentScene = new scene3();
		level3Load = true;
		std::cout << "level 3 loaded" << endl;
	}
}

void Game::render()
{
	float redValue = 0, greenValue = 0, blueValue = 0;
	if(m_currentScene->getBG().getComponent<RedComponent>())
		redValue = m_currentScene->getBG().getComponent<RedComponent>()->m_colourValue;
	if (m_currentScene->getBG().getComponent<GreenComponent>())
		greenValue = m_currentScene->getBG().getComponent<GreenComponent>()->m_colourValue;
	if (m_currentScene->getBG().getComponent<BlueComponent>())
		blueValue = m_currentScene->getBG().getComponent<BlueComponent>()->m_colourValue;
	
	// e.g. pass object details to the engine to render the next frame
	m_engineInterfacePtr->renderColouredBackground(redValue, greenValue, blueValue);

	// update the camera (probably don't need to do this each frame)
	m_engineInterfacePtr->setCamera(&m_camera);

	// draw the cube
	for (int i = 0; i < m_currentScene->getModelVec()->size(); i++)
	{
		m_engineInterfacePtr->drawModel(m_currentScene->getModelVec()->at(i)->getComponent<ModelComponent>()->getModel() , m_currentScene->getModelVec()->at(i)->getComponent<TransformComponent>()->getModelMatrix());
	}
}