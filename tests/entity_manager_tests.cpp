#include "CppUTest/TestHarness.h"
#include "ecs/ecs.h"

using namespace ZeEngine::ecs;
using namespace std;

TEST_GROUP(ecs_entitymanager_tests)
{
};

TEST(ecs_entitymanager_tests, EntityManager_CreateEntity_IsCreated)
{
	Entity_manager manager;
	auto& entity = manager.create_entity<int>();
	CHECK_EQUAL(0, entity.id);
}

TEST(ecs_entitymanager_tests, EntityManager_CreateTwoEntities_IsCreated)
{
	Entity_manager manager;
	manager.create_entity<int>();
	auto& entity = manager.create_entity<int>();
	CHECK_EQUAL(1, entity.id);
}

TEST(ecs_entitymanager_tests, EntityManager_CreateManyEntities_CreatesNewChunk)
{
	Entity_manager manager;
	for (size_t i = 0; i < 1000; ++i)
	{
		manager.create_entity<int>();
	}

	auto& entity = manager.create_entity<int>();
	CHECK_TRUE(entity.id < 500);
}