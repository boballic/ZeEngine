#include <memory>
#include <iostream>
#include <tuple>
#include <functional>
#include "ecs\ecs.h"
#include <vector>
#include <array>

#include "CppUTest/TestHarness.h"

using namespace ZeEngine::ecs;
using namespace std;

Chunk_pool_factory factory;

template <typename... Args>
std::unique_ptr<Archetype> create()
{
    return Archetype::create<Args...>(factory);
}

struct Component1
{
    std::tuple<int, int, long long> position{ 1,2,3 };
};


TEST_GROUP(ecs_tests)
{
};

TEST(ecs_tests, Chunk_CreateInt_ValidSize)
{
	auto chunk = create<int>();
	CHECK(chunk->get_max_address() <= chunk_size);
}

TEST(ecs_tests, Chunk_CreateLong_ValidSize)
{
	auto chunk = create<long>();
	CHECK(chunk->get_max_address() <= chunk_size);
}

TEST(ecs_tests, Chunk_CreatePair_ValidSize)
{
	auto chunk = create<int, long>();
	CHECK(chunk->get_max_address() <= chunk_size);
}

TEST(ecs_tests, Chunk_CreateMany_ValidSize)
{
	auto chunk = create<int, long, float, double, long long>();
	CHECK(chunk->get_max_address() <= chunk_size);
}

TEST(ecs_tests, Chunk_CreateStruct_ValidSize)
{
	auto chunk = create<int, long, float, double, long long, Component1>();
	CHECK(chunk->get_max_address() <= chunk_size);
}

TEST(ecs_tests, Chunk_CreatePair_ValidSearch)
{
	auto chunk = create<float, int>();

	//Should not throw exception
	auto result = chunk->fetch<int>();
}

TEST(ecs_tests, Chunk_CreatePair_InvalidSearch)
{
	auto func = [] 
	{ 
        auto archetype = create<float, int>();

		//Should throw exception
		auto result = archetype->fetch<short>();
	};
			
	CHECK_THROWS(std::runtime_error, func());
}

TEST(ecs_tests, Archetype_GetEntity_EntityFetched)
{
    auto archetype = create<int>();
	auto& entity = archetype->get_entity();
	size_t expected = 0;
	CHECK_EQUAL(expected, entity.id);
}

//TEST(ecs_tests, Archetype_GetLastEntity_EntityFetched)
//{
//	auto archetype = create<int>();
//	for (size_t i = 0; i < archetype->get_array_count() - 1; ++i)
//	{
//		archetype->get_entity();
//	}
//
//	auto& entity = archetype->get_entity();
//
//	//0 based
//	size_t expected = archetype->get_array_count() - 1;
//
//	CHECK_EQUAL(expected, entity.id);
//}
//
//TEST(ecs_tests, Archetype_GetOneTooMAnyEntities_ExpectException)
//{
//	auto func = []
//	{
//		auto archetype = create<int>();
//		for (size_t i = 0; i < archetype->get_array_count(); ++i)
//		{
//			archetype->get_entity();
//		}
//
//		//Should boom
//		auto& entity = archetype->get_entity();
//	};
//
//	CHECK_THROWS(std::runtime_error, func());
//}
//
//TEST(ecs_tests, Archetype_RemoveEntity_EntityRemoved)
//{
//	auto archetype = create<int>();
//
//	//Create entities
//	auto& entity = archetype->get_entity();
//	auto& entity2 = archetype->get_entity();
//	archetype->remove_entity(entity);
//
//	size_t expected = 1;
//	CHECK_EQUAL(expected, archetype->get_entity_count());
//}
//
//TEST(ecs_tests, Archetype_RemoveManyEntities_EntityRemoved)
//{
//	auto archetype = create<int>();
//	Entity entities[50];
//
//	//Create entities
//	for (size_t i = 0; i < 100; ++i)
//	{
//		auto entity = archetype->get_entity();
//		if (i < 50)
//			entities[i] = entity;
//	}
//
//	for (const auto& entity : entities)
//	{
//		archetype->remove_entity(entity);
//	}
//
//	size_t expected = 50;
//	CHECK_EQUAL(expected, archetype->get_entity_count());
//}
//
//TEST(ecs_tests, Archetype_RemoveEntity_EntityMoved)
//{
//	auto archetype = create<int>();
//
//	//Create entities
//	auto& entity = archetype->get_entity();
//	auto& entity2 = archetype->get_entity();
//	auto& entity3 = archetype->get_entity();
//
//	//Set second entity to 99 since it will have to be moved to the index of entity after we remove
//	auto components = archetype->fetch<int>();
//	components[entity3.index] = 99;
//	archetype->remove_entity(entity);
//
//	size_t expected_index = 0;
//
//	CHECK_EQUAL(expected_index, entity3.index);
//	CHECK_EQUAL(99, components[entity3.index]);
//	CHECK_EQUAL(0, components[entity2.index]);
//}