#ifndef ZEENGINE_POOL_H
#define ZEENGINE_POOL_H

#include <memory>
#include <vector>
#include <mutex>

namespace ZeEngine
{
	namespace ecs
	{
		static constexpr size_t pool_size = 1024 * 1024;
		static constexpr size_t chunk_size = 1024 * 16;
		static const size_t chunks_per_pool = pool_size / chunk_size;

		struct Chunk
		{
			size_t address_{ 0 };
			char* ptr_{ nullptr };
		};

		class Chunk_pool
		{
		public:
			Chunk_pool();
			inline size_t get_capacity() const { return free_chunks_.capacity(); }
			inline size_t get_free_size() const { return free_chunks_.size(); }
			inline size_t get_used_size() const { return used_chunks_.size(); }

			Chunk get_chunk();
			void free_chunk(const Chunk& chunk);

		private:
            void sort_reverse();

			std::vector<size_t> free_chunks_;
			std::vector<size_t> used_chunks_;
			std::unique_ptr<char[]> chunk_;
		};

        class Chunk_pool_factory
        {
            public:
                Chunk get_chunk();
            private:
                std::vector<Chunk_pool> pools_;
                std::mutex mutex_;
        };
	}
}
#endif