#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

struct UserInterface {

	UserInterface(GLFWwindow* window);
	~UserInterface();
	void SetSlider(const char* name, float* value, float min, float max);
	bool IsButtonPressed();
	void NewFrame();
	void Render();
};
