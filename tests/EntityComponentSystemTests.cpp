#include <memory>
#include <iostream>
#include <tuple>
#include <functional>
#include "ecs\ecs.h"
#include <vector>
#include <array>

#include "..\libs\cpputest-3.8\include\CppUTest\TestHarness.h"

using namespace ZeEngine::ecs;
using namespace std;

namespace CoreTests
{
    struct Component1
    {
        std::tuple<int, int, long long> position{ 1,2,3 };
    };

    TEST_GROUP(FirstTestGroup)
    {
    };

  //  TEST_CLASS(EntityComponentSystemTests)
  //  {
  //  public:
  //      TEST_METHOD(Chunk_CreateInt_ValidSize)
  //      {
		//	auto chunk = Archetype::create<int>();
		//	Assert::IsTrue(chunk->get_max_address() <= chunk_size);
  //      }  

		//TEST_METHOD(Chunk_CreateLong_ValidSize)
		//{
		//	auto chunk = Archetype::create<long>();
		//	Assert::IsTrue(chunk->get_max_address() <= chunk_size);
		//}

		//TEST_METHOD(Chunk_CreatePair_ValidSize)
		//{
		//	auto chunk = Archetype::create<int, long>();
		//	Assert::IsTrue(chunk->get_max_address() <= chunk_size);
		//}

		//TEST_METHOD(Chunk_CreateMany_ValidSize)
		//{
		//	auto chunk = Archetype::create<int, long, float, double, long long>();
		//	Assert::IsTrue(chunk->get_max_address() <= chunk_size);
		//}

		//TEST_METHOD(Chunk_CreateStruct_ValidSize)
		//{
		//	auto chunk = Archetype::create<int, long, float, double, long long, Component1>();
		//	Assert::IsTrue(chunk->get_max_address() <= chunk_size);
		//}

		//TEST_METHOD(Chunk_CreatePair_ValidSearch)
		//{
		//	auto chunk = Archetype::create<float, int>();

		//	//Should not throw exception
		//	auto result = chunk->fetch<int>();
		//}

		//TEST_METHOD(Chunk_CreatePair_InvalidSearch)
		//{
		//	auto func = [] 
		//	{ 
		//		auto chunk = Archetype::create<float, int>();

		//		//Should throw exception
		//		auto result = chunk->fetch<short>();
		//	};
		//	
		//	Assert::ExpectException<std::runtime_error>(func);
		//}

		//TEST_METHOD(Archetype_GetEntity_EntityFetched)
		//{
		//	auto archetype = Archetype::create<int>();
		//	auto& entity = archetype->get_entity();
		//	size_t expected = 0;

		//	Assert::AreEqual(expected, entity.id);
		//}

		//TEST_METHOD(Archetype_GetLastEntity_EntityFetched)
		//{
		//	auto archetype = Archetype::create<int>();
		//	for (size_t i = 0; i < archetype->get_array_count() - 1; ++i)
		//	{
		//		archetype->get_entity();
		//	}

		//	auto& entity = archetype->get_entity();

		//	//0 based
		//	size_t expected = archetype->get_array_count() - 1;

		//	Assert::AreEqual(expected, entity.id);
		//}

		//TEST_METHOD(Archetype_GetOneTooMAnyEntities_ExpectException)
		//{

		//	auto func = []
		//	{
		//		auto archetype = Archetype::create<int>();
		//		for (size_t i = 0; i < archetype->get_array_count(); ++i)
		//		{
		//			archetype->get_entity();
		//		}

		//		//Should boom
		//		auto& entity = archetype->get_entity();
		//	};

		//	Assert::ExpectException<std::runtime_error>(func);
		//}

		//TEST_METHOD(Archetype_RemoveEntity_EntityRemoved)
		//{
		//	auto archetype = Archetype::create<int>();

		//	//Create entities
		//	auto& entity = archetype->get_entity();
		//	auto& entity2 = archetype->get_entity();
		//	archetype->remove_entity(entity);

		//	size_t expected = 1;
		//	Assert::AreEqual(expected, archetype->get_entity_count());
		//}

		//TEST_METHOD(Archetype_RemoveManyEntities_EntityRemoved)
		//{
		//	auto archetype = Archetype::create<int>();
		//	Entity entities[50];

		//	//Create entities
		//	for (size_t i = 0; i < 100; ++i)
		//	{
		//		auto entity = archetype->get_entity();
		//		if (i < 50)
		//			entities[i] = entity;
		//	}

		//	for (const auto& entity : entities)
		//	{
		//		archetype->remove_entity(entity);
		//	}

		//	size_t expected = 50;
		//	Assert::AreEqual(expected, archetype->get_entity_count());
		//}

		//TEST_METHOD(Archetype_RemoveEntity_EntityMoved)
		//{
		//	auto archetype = Archetype::create<int>();

		//	//Create entities
		//	auto& entity = archetype->get_entity();
		//	auto& entity2 = archetype->get_entity();
		//	auto& entity3 = archetype->get_entity();

		//	//Set second entity to 99 since it will have to be moved to the index of entity after we remove
		//	auto components = archetype->fetch<int>();
		//	components[entity3.index] = 99;
		//	archetype->remove_entity(entity);

		//	size_t expected_index = 0;

		//	Assert::AreEqual(expected_index, entity3.index);
		//	Assert::AreEqual(99, components[entity3.index]);
		//	Assert::AreEqual(0, components[entity2.index]);
		//}
  //  };
}