#include "chunk_pool.h"

namespace ZeEngine
{
	namespace ecs
	{
		char* Chunk_pool::get_chunk()
		{
			if (free_chunks_.size() <= 0)
			{
				return nullptr;
			}

			auto address = free_chunks_.back();
			free_chunks_.pop_back();
			return &chunk_[address];
		}
	}
}