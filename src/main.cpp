#include "Application/application.hpp"

int main()
{
	Application app;

	while (!app.ShouldClose())
	{
		app.Update();
	}
}
