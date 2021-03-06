#pragma once

#include <string>
/*! An abstract class for Components*/
class Component
{
public:
	virtual void OnUpdate(float dt) = 0;
	virtual void OnMessage(const std::string m) = 0;

};

