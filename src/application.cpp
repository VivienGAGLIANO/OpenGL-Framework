#include "application.h"

Application::Application() : engine(new Renderer()), scene(new Scene)
{
	engine->init();
}

void Application::start()
{

}
