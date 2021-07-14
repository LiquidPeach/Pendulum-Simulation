#include "UserInterface.h"

UserInterface::UserInterface(GLFWwindow* window) {
    // Set up ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // Set up style
    ImGui::StyleColorsDark();
    // Set up Platform and Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

UserInterface::~UserInterface() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UserInterface::SetSlider(const char* name, float* value, float min, float max) {
    ImGui::SliderFloat(name, value, min, max);
}

bool UserInterface::IsButtonPressed() const{
    return ImGui::IsItemActive();
}

void UserInterface::NewFrame() const{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UserInterface::Render() const{
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}