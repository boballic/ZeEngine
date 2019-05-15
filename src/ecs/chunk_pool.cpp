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

            sort_reverse();
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

                sort_reverse();
			}
		}

        //Keep the list sorted (reverse since we pop_back) so we can keep the memory close together when we pull from the vector
        void Chunk_pool::sort_reverse()
        {
            std::sort(free_chunks_.begin(), free_chunks_.end(), std::greater<size_t>());
        }

        //If no free chunks are found then create a new pool
        Chunk Chunk_pool_factory::get_chunk()
        {
            std::lock_guard<std::mutex> lock(mutex_);

            //Search for existing
            for (auto& chunk_pool : pools_)
            {
                auto chunk = chunk_pool.get_chunk();

                if (chunk.ptr_ != nullptr)
                {
                    return chunk;
                }
            }

            //Create and return
            pools_.emplace_back();
            auto& new_pool = pools_.back();
            return new_pool.get_chunk();
        }
	}
}