#include <cstddef>
#include <algorithm>
#include <stdexcept>

namespace ft {
  template <typename T, size_t N>
  class array {
  public:
    array() {}
    array(const array& other) {
      for (size_t i = 0; i < N; ++i) {
        storage[i] = other.storage[i];
      }
    }
    array<T, N>& operator=(const array& other) {
      for (size_t i = 0; i < N; ++i) {
        storage[i] = other.storage[i];
      }
      return *this;
    }
    ~array() {}
    T& operator[](size_t pos) {
      return storage[pos];
    }
    const T& operator[](size_t pos) const {
      return storage[pos];
    }
    T& at(size_t pos) {
      if (pos >= N) {
        throw std::out_of_range("array::at");
      }
      return storage[pos];
    }
    const T& at(size_t pos) const {
      if (pos >= N) {
        throw std::out_of_range("array::at");
      }
      return storage[pos];
    }
    T& front() {
      return storage[0];
    }
    const T& front() const {
      return storage[0];
    }
    T& back() {
      return storage[N - 1];
    }
    const T& back() const {
      return storage[N - 1];
    }
    T* data() {
      return storage;
    }
    const T* data() const {
      return storage;
    }
    size_t size() const {
      return N;
    }
    bool empty() const {
      return N == 0;
    }
    void fill(const T& value) {
      for (size_t i = 0; i < N; ++i) {
        storage[i] = value;
      }
    }
    void swap(array& other) {
      for (size_t i = 0; i < N; ++i) {
        T tmp = storage[i];
        storage[i] = other.storage[i];
        other.storage[i] = tmp;
      }
    }
  private:
    T storage[N];
  };
}
