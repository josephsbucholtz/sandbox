#include <cstddef>
#include <iostream>
#include <new>
#include <utility>
#include <vector>

class MemoryPool {
	public:
		explicit MemoryPool(std::size_t size, int preAlloc, int maxAlloc)
		{
			m_blockSize = std::max(size, sizeof(FreeNode));
			m_capacity = maxAlloc;
			m_blocks.reserve(maxAlloc);

			for (size_t i {}; i < preAlloc && i < maxAlloc; ++i) {
				pushFree(newBlock());
			}
		}

		~MemoryPool() {
			for (auto block : m_blocks) {
				::operator delete(block);
			}
		}

		int inUse() const {
			return m_used;
		}

		int availible() const {
			return m_capacity - m_used;
		}

		std::size_t blockSize() const {
			return m_blockSize;
		}

		void* allocate() {
			if (freeList == nullptr) {
				if (m_blocks.size() >= m_capacity) {
					throw std::bad_alloc();
				}	
				pushFree(newBlock());
			}

			FreeNode* node = freeList;
			freeList = freeList->next;
			++m_used;
			return node;
		}

		void deallocate(void* ptr) {
			if (ptr == nullptr) {
				return;
			}

			pushFree(ptr);
			--m_used;
		}

		template<typename T, typename... Args>
		T* make(Args... args) {
			if (sizeof(T) > m_blockSize) {
				throw std::bad_alloc();
			}	

			return new (allocate()) T(std::forward<Args>(args)...);
		}

		//No Copy 
		MemoryPool(const MemoryPool&) = delete;
		MemoryPool& operator=(const MemoryPool&) = delete;

	private:
		struct FreeNode {
			FreeNode* next;
		};
		
		void* newBlock() {
			void* block = ::operator new(m_blockSize);
			m_blocks.push_back(block);
			return block;
		}

		void pushFree(void* block) {
			freeList = new (block) FreeNode{freeList};
		}


		FreeNode* freeList{};
		std::vector<void*> m_blocks{};

		std::size_t m_blockSize;
		std::size_t m_capacity;
		std::size_t m_used {};

};

int main() {
	MemoryPool pool(sizeof(int), 4, 10);

	int* a = pool.make<int>(12);
	int* b = pool.make<int>(10);

	std::cout << *a << "\n";
	std::cout << pool.inUse() << "\n";

	pool.deallocate(a);

	std::cout << pool.inUse() << "\n";

	return 0;
}
