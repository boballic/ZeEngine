#include "CppUTest/TestHarness.h"
#include "ecs/chunk_pool.h"

using namespace ZeEngine::ecs;
using namespace std;

TEST_GROUP(Chunk_pool_tests)
{
};

TEST(Chunk_pool_tests, Pool_Create_ValidInitialFreeSize)
{
	Chunk_pool pool;
	auto free = pool.get_free_size();

	CHECK_EQUAL(ZeEngine::ecs::chunks_per_pool, free);
}

TEST(Chunk_pool_tests, Pool_Create_ValidInitialUsedSize)
{
	Chunk_pool pool;
	auto used = pool.get_used_size();
	CHECK_EQUAL(0, used);
}

TEST(Chunk_pool_tests, Pool_PreserveSortWhenGet_IsSorted)
{
	Chunk_pool pool;
    auto chunk1 = pool.get_chunk();
    auto chunk2 = pool.get_chunk();

	CHECK(chunk1.address_ < chunk2.address_);
}

TEST(Chunk_pool_tests, Pool_PreserveSortWhenGetAndFree_IsSorted)
{
    Chunk_pool pool;
    auto chunk1 = pool.get_chunk();
    auto chunk2 = pool.get_chunk();
    auto chunk3 = pool.get_chunk();

    pool.free_chunk(chunk2);
    chunk2 = pool.get_chunk();

    CHECK(chunk1.address_ < chunk2.address_ && chunk2.address_ < chunk3.address_);
}

TEST(Chunk_pool_tests, Pool_Create_ValidateMemory)
{
    Chunk_pool pool;
    auto capacity = pool.get_capacity();
    CHECK_EQUAL(ZeEngine::ecs::chunks_per_pool, capacity);
}

TEST(Chunk_pool_tests, Pool_Retrieve_NotNull)
{
	Chunk_pool pool;
	auto chunk = pool.get_chunk();
	
	CHECK(chunk.ptr_ != nullptr);
}

TEST(Chunk_pool_tests, Pool_GetMaxChunks_RetrieveChunk)
{
	Chunk_pool pool;

	for (size_t i = 0; i < ZeEngine::ecs::chunks_per_pool - 1; ++i)
	{
		pool.get_chunk();
	}

	auto chunk = pool.get_chunk();
	CHECK(chunk.ptr_ != nullptr);
}

TEST(Chunk_pool_tests, Pool_ExhaustChunks_ExpectNullPtr)
{
	Chunk_pool pool;

	for (size_t i = 0; i < ZeEngine::ecs::chunks_per_pool; ++i)
	{
		pool.get_chunk();
	}

	auto chunk = pool.get_chunk();
	CHECK(chunk.ptr_ == nullptr);
}

TEST(Chunk_pool_tests, Pool_ExhaustChunksThenFree_ValidSize)
{
	Chunk_pool pool;
	std::vector<Chunk> chunks;
	for (size_t i = 0; i < ZeEngine::ecs::chunks_per_pool; ++i)
	{
		chunks.emplace_back(pool.get_chunk());
	}

	for(auto chunk : chunks)
	{
		pool.free_chunk(chunk);
	}

	auto expected = ZeEngine::ecs::chunks_per_pool;
	CHECK_EQUAL(expected, pool.get_free_size());
}

TEST(Chunk_pool_tests, Pool_DoubleFreeChunk_ValidSize)
{
	Chunk_pool pool;
	std::vector<Chunk> chunks;
	for (size_t i = 0; i < ZeEngine::ecs::chunks_per_pool; ++i)
	{
		chunks.emplace_back(pool.get_chunk());
	}

	for (auto chunk : chunks)
	{
		pool.free_chunk(chunk);
		pool.free_chunk(chunk);
	}

	auto expected = ZeEngine::ecs::chunks_per_pool;
	CHECK_EQUAL(expected, pool.get_free_size());
}


