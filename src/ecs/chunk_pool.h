#ifndef ZEENGINE_POOL_H
#define ZEENGINE_POOL_H

#include <array>
#include <vector>

namespace ZeEngine
{
	namespace ecs
	{
		constexpr size_t pool_size = 1024 * 1024;

		class Chunk_pool
		{
		public:
			Chunk_pool() : free_chunks_(1024 / 16384, 0)
			{
				size_t addr = 0;
				for (auto& index : free_chunks_)
				{
					index = addr;
					addr += 16384;
				}
			}

			inline size_t get_capacity() const { return free_chunks_.capacity(); }
			char* get_chunk();

		private:
			std::vector<size_t> free_chunks_;
			std::array<char, 1024> chunk_ { 0 };
		};
	}
}
#endif