#include "CppUTest/CommandLineTestRunner.h"

#include "ecs/ecs.h"
int main(int ac, char** av)
{
	//Initialize static variables here so they dont fail leak test
	ZeEngine::ecs::Entity_manager manager;
	manager.create_entity<int>();

	return CommandLineTestRunner::RunAllTests(ac, av);
}
