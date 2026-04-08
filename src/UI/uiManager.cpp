#include "UI/uiManager.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

UIManager::UIManager()
= default;

UIManager::UIManager(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460\0");
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
}

void UIManager::Draw()
{
	renderingSettings.Draw();
	blender.Draw();
}

void UIManager::SetAnimator(MorphTargetAnimator& pAnimator)
{
	blender.SetAnimator(pAnimator);
}

void UIManager::SetRenderer(Renderer& pRendering)
{
	renderingSettings.SetRenderer(pRendering);
}
