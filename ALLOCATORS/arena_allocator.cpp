#include <cstddef>
#include <iostream>
#include <memory>
#include <new>

class Arena {
	public:
		explicit Arena(std::size_t size) :
			m_buffer(static_cast<std::byte*>(::operator new(size))),
			m_capacity(size) {} 

		~Arena() {
			::operator delete(m_buffer);
		}
		
		void* allocate(std::size_t size, std::size_t alignment) {
			void* ptr { m_buffer + m_offset };
			std::size_t space { m_capacity - m_offset };

			if (std::align(alignment, size, ptr, space) == nullptr) {
				throw std::bad_alloc();
			}

			m_offset = static_cast<std::size_t>(static_cast<std::byte*>(ptr) - m_buffer) + size;

			return ptr;
		}

		void reset() noexcept {
			m_offset = 0;
		}

		[[nodiscard]] 
		std::size_t used() noexcept {
			return m_offset;
		}

		[[nodiscard]]
		std::size_t remaining() noexcept {
			return m_capacity - m_offset;
		}

		[[nodiscard]]
		std::size_t capacity() noexcept {
			return m_capacity;
		}

		//Non-Copiable
		Arena(const Arena&) = delete;
		Arena& operator=(const Arena&) = delete;

		//Non-movable
		Arena(Arena&&) = delete;
		Arena& operator=(Arena&&) = delete;

	private:
		std::byte* m_buffer;
		std::size_t m_offset{};
		std::size_t m_capacity{};
};

int main() { 
	Arena arena(1024);


	return 0; 
}
