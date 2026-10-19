#include <cstddef>

template<typename T>
class RingBuffer {
public:
	explicit RingBuffer(size_t capacity) :
	capacity_(capacity),
	head_(0),
	tail_(0),
	count_(0),
	buffer_(new T[capacity])
	{}

	~RingBuffer() {
		delete buffer_;
		buffer_ = nullptr;
	}

	void push(const T& item) {}
	bool try_push(const T& item) {}
	bool pop_front() {}
	bool pop_back() {}

	T& front() {}
	T& back() {}

	size_t size() { return head_ - tail_; }
	bool isEmpty() { return head_ == tail_; }
	bool isFull() { return size() == capacity_; }

	//No copy 
	RingBuffer(const RingBuffer&) = delete;
	RingBuffer& operator=(const RingBuffer&) = delete;

private:
	T* buffer_;
	size_t capacity_;
	size_t head_;
	size_t tail_;
	size_t count_;
};

int main() {
	return 0;
}
