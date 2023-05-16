#pragma once
#include <iostream>
#include <map>
#include <GLFW/glfw3.h>

class InputManager
{
public:
	static std::map<int, bool> keysState;
	static void keyboardManager(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void initInputManager(GLFWwindow* window);
	
	static bool getKeyState(int key) {
		if (keysState.find(key) != keysState.end()) {
			return keysState[key];
		}
		return false;
	}
};

