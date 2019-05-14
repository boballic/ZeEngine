#include "CppUTest/TestHarness.h"
#include "ecs/chunk_pool.h"

using namespace ZeEngine::ecs;
using namespace std;

TEST_GROUP(Chunk_pool_tests)
{
};

TEST(Chunk_pool_tests, Pool_Create_ValidSize)
{
	Chunk_pool pool;

	auto count = pool.get_capacity();
	auto expected = ZeEngine::ecs::pool_size / 16384;

	CHECK_EQUAL(count, expected);
}

TEST(Chunk_pool_tests, Pool_Create_RetrieveChunk)
{
	Chunk_pool pool;
	auto chunk = pool.get_chunk();
	
	CHECK(chunk != nullptr);
}


