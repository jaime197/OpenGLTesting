#include "InputManager.h"

std::map<int, bool> InputManager::keysState;

void InputManager::keyboardManager(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        keysState[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        keysState[key] = false;
    }
}

void InputManager::initInputManager(GLFWwindow* window)
{
	glfwSetKeyCallback(window, keyboardManager);
}
