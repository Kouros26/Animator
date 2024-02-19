#include "application.hpp"

int main()
{
	Application app;

	while (!app.ShouldClose())
	{
		app.Render();
	}
}
