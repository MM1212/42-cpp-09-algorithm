#include "Deque.hpp"
#include <set>

Deque::Deque(
  const PMergeMe::JacobsthalCache& jacobsthalCache
) : Container(jacobsthalCache) {}

Deque::Deque(const Deque& other) : Container(other), elems(other.elems) {}

Deque::~Deque() {}

bool Deque::isSorted() const {
  for (size_t i = 1; i < this->elems.size(); ++i) {
    if (this->elems[i - 1] > this->elems[i]) {
      return false;
    }
  }
  return true;
}

void Deque::createPairs() {
  this->pairs.clear();
  for (size_t i = 0; i < this->elems.size(); i += 2) {
    pairs.push_back(std::make_pair(this->elems[i], this->elems[i + 1]));
  }
}

void Deque::insert(int64_t nbr) {
  this->elems.push_back(nbr);
}

void Deque::insertFront(int64_t nbr) {
  this->elems.push_front(nbr);
}

void Deque::prepare() {
  if (this->elems.size() % 2 == 1) {
    this->extra = this->elems.back();
    this->elems.pop_back();
  }
  else
    this->extra = -1;
}

void Deque::clear() {
  this->elems.clear();
}

void Deque::sort() {
  std::sort(this->elems.begin(), this->elems.end());
}

int64_t Deque::front() const {
  return this->elems.front();
}

void Deque::pop() {
  this->elems.pop_front();
}

int64_t Deque::back() const {
  return this->elems.back();
}

void Deque::popBack() {
  this->elems.pop_back();
}

void Deque::insertWithBinarySearch(uint64_t idx) {
  int64_t value = this->pairs[idx].first;
  std::deque<int64_t>::iterator it = this->findInContainer(this->pairs[idx].second);
  this->elems.insert(std::lower_bound(this->elems.begin(), it, value), value);
}

std::deque<int64_t>::iterator Deque::findInContainer(int64_t value) {
  return std::find(this->elems.begin(), this->elems.end(), value);
}

void Deque::output() const {
  for (size_t i = 0; i < this->elems.size(); ++i) {
    std::cout << this->elems[i];
    if (i != this->elems.size() - 1)
      std::cout << " ";
  }
  std::cout << std::endl;
}

bool Deque::hasDuplicates() const {
  std::set<int64_t> seen;
  for (size_t i = 0; i < this->elems.size(); ++i) {
    if (seen.find(this->elems[i]) != seen.end()) {
      return true;
    }
    seen.insert(this->elems[i]);
  }
  return false;
}
