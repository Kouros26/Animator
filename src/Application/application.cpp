#include "Application/application.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

Application::Application()
{
	GameObject& obj = gameObjectManager.CreateGameObject("bob", "resources/models/default.fbx");
	animator = new MorphTargetAnimator(obj.GetModel());
	animator->Init("resources/models/Gunan/");
	window.GetUIManager().SetAnimator(*animator);
}

Application::~Application()
{
	delete animator;
}

void Application::Update()
{
	renderer.Clear();
	time.UpdateDeltaTime();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ProcessInput(time.GetDeltaTime());

	animator->Update();
	renderer.Render(gameObjectManager.GetGameObjects(), gameObjectManager.GetMainCamera());

	window.GetUIManager().Draw();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	window.SwapBuffers();
	window.PollEvents();
}

bool Application::ShouldClose() const
{
	return window.ShouldClose();
}

void Application::ProcessInput(const double& deltaTime)
{
	GLFWwindow* windowRef = window.GetWindow();

	if (glfwGetKey(windowRef, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(windowRef, true);

	if (glfwGetKey(windowRef, GLFW_KEY_MINUS) == GLFW_PRESS)
		renderer.ToggleWireFrame();

	if (glfwGetKey(windowRef, GLFW_KEY_W) == GLFW_PRESS)
		gameObjectManager.GetMainCamera().GetTransform().AddPosition(glm::vec3{ 0, 0, 100 } *= deltaTime);

	if (glfwGetKey(windowRef, GLFW_KEY_A) == GLFW_PRESS)
		gameObjectManager.GetMainCamera().GetTransform().AddPosition(glm::vec3{ 100, 0, 0 } *= deltaTime);

	if (glfwGetKey(windowRef, GLFW_KEY_S) == GLFW_PRESS)
		gameObjectManager.GetMainCamera().GetTransform().AddPosition(glm::vec3{ 0, 0, -100 } *= deltaTime);

	if (glfwGetKey(windowRef, GLFW_KEY_D) == GLFW_PRESS)
		gameObjectManager.GetMainCamera().GetTransform().AddPosition(glm::vec3{ -100, 0, 0 } *= deltaTime);
}
