#pragma once
#include "IEngineCore.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/mat4x4.hpp>
#include "Camera.h"

class Game;
//! Main engine for GLFW, inheriting from IEngineCore
class GLFW_EngineCore
{
public:
	//!Default deconstructer
	~GLFW_EngineCore();
	//!Bool to init the window
	/*!
		Called in main to create the window
		\param width width of the window
		\param height height of the window
		\param windowName name of the window
	*/
	bool initWindow(int width, int height, std::string windowName);
	//!Bool that runs the whole game
	/*!	handles inputs, updating, rendering, polling for events and swaping buffers
		\params game Reference to a variable of type of game
	*/
	bool runEngine(Game& game);
	virtual void renderColouredBackground(float r, float g, float b);

	void setCamera(const Camera* cam);
	void drawModel(Model* model, const glm::mat4& modelMatrix);

private:
	GLFWwindow* m_window;
	GLuint m_defaultShaderProgram;

	static double scroll_offset;
	static std::vector<double> mouse_pos;
	static int m_screenWidth;
	static int m_screenHeight;
	static std::vector<bool> m_keyBuffer;
	static std::vector<bool> m_mouseBuffer;
	static const int m_BufferSize = 400;

	static int m_scrollBuffer;

	static void mousePositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void mouseCallbackEvent(GLFWwindow* window, int button, int action, int mods);
	static void keyCallbackEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void windowResizeCallbackEvent(GLFWwindow* window, int width, int height);
	
	void setDefaultShaders();
};

