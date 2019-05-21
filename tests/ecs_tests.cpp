#include <memory>
#include <iostream>
#include <tuple>
#include <functional>
#include "ecs/ecs.h"
#include "ecs/arche_type.h"
#include "ecs/entity.h"
#include "ecs/chunk_pool.h"
#include <vector>
#include <array>

#include "CppUTest/TestHarness.h"

using namespace ZeEngine::ecs;
using namespace std;

template <typename... Args>
std::unique_ptr<Archetype> create(Chunk_pool_factory& factory)
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
    Chunk_pool_factory factory;
	auto chunk = create<int>(factory);
	CHECK(chunk->get_max_address() <= chunk_size);
}

TEST(ecs_tests, Chunk_CreateLong_ValidSize)
{
    Chunk_pool_factory factory;
	auto chunk = create<long>(factory);
	CHECK(chunk->get_max_address() <= chunk_size);
}

TEST(ecs_tests, Chunk_CreatePair_ValidSize)
{
    Chunk_pool_factory factory;
	auto chunk = create<int, long>(factory);
	CHECK(chunk->get_max_address() <= chunk_size);
}

TEST(ecs_tests, Chunk_CreateMany_ValidSize)
{
    Chunk_pool_factory factory;
	auto chunk = create<int, long, float, double, long long>(factory);
	CHECK(chunk->get_max_address() <= chunk_size);
}

TEST(ecs_tests, Chunk_CreateStruct_ValidSize)
{
    Chunk_pool_factory factory;
	auto chunk = create<int, long, float, double, long long, Component1>(factory);
	CHECK(chunk->get_max_address() <= chunk_size);
}

TEST(ecs_tests, Chunk_CreatePair_ValidSearch)
{
    Chunk_pool_factory factory;
	auto chunk = create<float, int>(factory);

	//Should not throw exception
	auto result = chunk->fetch<int>();
}

TEST(ecs_tests, Chunk_CreatePair_InvalidSearch)
{
	auto func = [] 
	{ 
        Chunk_pool_factory factory;
        auto archetype = create<float, int>(factory);

		//Should throw exception
		auto result = archetype->fetch<short>();
	};
			
	CHECK_THROWS(std::runtime_error, func());
}

TEST(ecs_tests, Archetype_GetEntity_EntityFetched)
{
    Chunk_pool_factory factory;
    auto archetype = create<int>(factory);
	auto& entity = archetype->create_entity();
	size_t expected = 0;
	CHECK_EQUAL(expected, entity.id);
}

TEST(ecs_tests, Archetype_GetLastEntity_EntityFetched)
{
    Chunk_pool_factory factory;
	auto archetype = create<int>(factory);
	for (size_t i = 0; i < archetype->get_array_count() - 1; ++i)
	{
		archetype->create_entity();
	}

	auto& entity = archetype->create_entity();

	//0 based
	size_t expected = archetype->get_array_count() - 1;

	CHECK_EQUAL(expected, entity.id);
}

TEST(ecs_tests, Archetype_GetOneTooMAnyEntities_ExpectException)
{
	auto func = []
	{
        Chunk_pool_factory factory;
		auto archetype = create<int>(factory);
		for (size_t i = 0; i < archetype->get_array_count(); ++i)
		{
			archetype->create_entity();
		}

		//Should boom
		auto& entity = archetype->create_entity();
	};

	CHECK_THROWS(std::runtime_error, func());
}

TEST(ecs_tests, Archetype_RemoveEntity_EntityRemoved)
{
    Chunk_pool_factory factory;
	auto archetype = create<int>(factory);

	//Create entities
	auto& entity = archetype->create_entity();
	auto& entity2 = archetype->create_entity();
	archetype->remove_entity(entity);

	size_t expected = 1;
	CHECK_EQUAL(expected, archetype->get_entity_count());
}

TEST(ecs_tests, Archetype_RemoveManyEntities_EntityRemoved)
{
    Chunk_pool_factory factory;
	auto archetype = create<int>(factory);
	Entity entities[50];

	//Create entities
	for (size_t i = 0; i < 100; ++i)
	{
		auto entity = archetype->create_entity();
		if (i < 50)
			entities[i] = entity;
	}

	for (const auto& entity : entities)
	{
		archetype->remove_entity(entity);
	}

	size_t expected = 50;
	CHECK_EQUAL(expected, archetype->get_entity_count());
}

TEST(ecs_tests, Archetype_RemoveEntity_EntityMoved)
{
    Chunk_pool_factory factory;
	auto archetype = create<int>(factory);

	//Create entities
	auto& entity = archetype->create_entity();
	auto& entity2 = archetype->create_entity();
	auto& entity3 = archetype->create_entity();

	//Set second entity to 99 since it will have to be moved to the index of entity after we remove
	auto components = archetype->fetch<int>();
	components[entity3.index] = 99;
	archetype->remove_entity(entity);

	size_t expected_index = 0;

	CHECK_EQUAL(expected_index, entity3.index);
	CHECK_EQUAL(99, components[entity3.index]);
	CHECK_EQUAL(0, components[entity2.index]);
}

TEST(ecs_tests, Archetype_FetchEach_AllFetched)
{
	Chunk_pool_factory factory;
	auto archetype = create<int, float, double> (factory);

	auto a = archetype->fetch<int>();
	auto b =archetype->fetch<float>();
	auto c = archetype->fetch<double>();
}

TEST(ecs_tests, Archetype_CreateInt_IsSupported)
{
	Chunk_pool_factory factory;
	auto archetype = create<int, float, double>(factory);
	auto result = archetype->supports_component<int, float, double>();
	CHECK_EQUAL(true, result);
}

TEST(ecs_tests, Archetype_CreateIntCheckSomethingElse_IsNotSupported)
{
	Chunk_pool_factory factory;
	auto archetype = create<int, float, double>(factory);
	auto result = archetype->supports_component<int, float, double, short>();
	//CHECK_EQUAL(false, result);
}