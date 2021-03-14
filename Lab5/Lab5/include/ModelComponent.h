#pragma once
#include "Component.h"
#include "Model.h"
//! A class to point to the model, inheriting from the abstract component class*/
/*! Used to attach a model to a GameObject through the GameObject template for components*/
class ModelComponent : public Component
{
public:
	//! A pointer to the model class
	Model* model;
	
	void OnUpdate(float dt) override{}	/*!< Empty body, override functions for the parent Component*/
	void OnMessage(const std::string m) override{}

	//! Class constructer
	/*!
		Passes through a model pointer, which is then used to define the model class pointer using member initilisation.
	*/
	ModelComponent(Model* theModel) : model(theModel) {}

	//! Getter to return the model paired with the GameObject
	Model* getModel()
	{
		return model;
	}
};