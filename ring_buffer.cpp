#include <cstddef>
#include <stdexcept>

template<typename T>
class RingBuffer {
public:
	explicit RingBuffer(size_t capacity) :
	head_(0),
	tail_(0),
	count_(0),
	buffer_(new T[capacity])
	{
		if (capacity == 0) 
		{
			throw std::invalid_argument("Capacity must be non zero");
		} 
		else 
		{
			capacity_ = new T[capacity];
		}
	}

	~RingBuffer() {
		delete[] buffer_;
	}

	void push(const T& item) {
		const bool was_full = isFull();

		buffer_[tail_] = item;
		tail_ = (++tail_) % capacity_;

		if (was_full) {
			head_ = tail_;
		} else{
			count_++;
		}
	}

	bool try_push(const T& item) {
		if (isFull()) {
			return false;
		}
		buffer_[tail_] = item;
		tail_ = (++tail_) % capacity_;
		count_++;
		return true;
	}


	bool pop_front(T& item) {
		if (isEmpty()) {
			return false;
		}

		item = buffer_[head_++];
		head_ %= capacity_;
		count_--;
		return true;
	}
	bool pop_back(T& item) {
		if (isEmpty()) {
			return false;
		}

		tail_ = (tail_ + capacity_ - 1) % capacity_;
        item = buffer_[tail_];
		count_--;
		return true;
	}

	T& front() {
		if (isEmpty()) {
			throw std::out_of_range("Front doesn't exist.");
		}
		return buffer_[head_];
	}
	T& back() {
		if (isEmpty()) {
			throw std::out_of_range("Front doesn't exist.");
		}
		return buffer_[(tail_ + capacity_ - 1) % capacity_];
	}

	size_t size() { return count_; }
	bool isEmpty() { return count_ == 0; }
	bool isFull() { return count_ == capacity_; }

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
