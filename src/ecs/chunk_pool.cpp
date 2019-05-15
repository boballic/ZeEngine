#include "chunk_pool.h"
#include <algorithm>

namespace ZeEngine
{
	namespace ecs
	{
		Chunk_pool::Chunk_pool() : 
			free_chunks_(chunks_per_pool, 0),
			chunk_(std::make_unique<char[]>(pool_size))
		{
			size_t addr = 0;
			for (auto& index : free_chunks_)
			{
				index = addr;
				addr += chunk_size;
			}
		}

		Chunk Chunk_pool::get_chunk()
		{
			if (free_chunks_.size() <= 0)
			{
				return { 0, nullptr };
			}

			auto address = free_chunks_.back();
			auto ptr = &chunk_[address];
			free_chunks_.pop_back();
			used_chunks_.push_back(address);
			return { address, ptr };
		}

		void Chunk_pool::free_chunk(const Chunk& chunk)
		{
			auto it = find(used_chunks_.cbegin(), used_chunks_.cend(), chunk.address_);
			if ( it != used_chunks_.cend())
			{
				free_chunks_.push_back(chunk.address_);
				used_chunks_.erase(it);
			}
		}
	}
}