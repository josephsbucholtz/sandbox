#include <cstddef>
#include <iostream>
#include <vector>

struct Block {
	std::byte* buffer;
	Block* next;
};

class MemoryPool {
	public:
		explicit MemoryPool(std::size_t size, int preAlloc, int maxAlloc) :
			m_blockSize(size),
			m_maxAlloc(maxAlloc)
			{}

		~MemoryPool() {
			
		}

		int allocated() const {
			return m_allocated.size();
		}

		int availible() const {
			return m_maxAlloc - m_allocated.size();
		}

		std::size_t blockSize() const {
			return m_blockSize;
		}

		void* get() {
			return nullptr;
		}

		void release(void* ptr) {

		}


	private:
		std::vector<void*> m_allocated;
		std::size_t m_blockSize;
		int m_maxAlloc {};

};

int main() {
	MemoryPool pool(64, 4, 10);

	std::cout << pool.allocated() << "\n";

	return 0;
}
