#include "Vector.hpp"
#include <algorithm>

Vector::Vector(
  const PMergeMe::JacobsthalCache& jacobsthalCache
) : Container(jacobsthalCache) {}
Vector::Vector(const Vector& other) : Container(other), elems(other.elems) {}
Vector::~Vector() {}

bool Vector::isSorted() const {
  for (size_t i = 1; i < this->elems.size(); ++i) {
    if (this->elems[i - 1] > this->elems[i]) {
      return false;
    }
  }
  return true;
}

void Vector::createPairs() {
  this->pairs.clear();
  for (size_t i = 0; i < this->elems.size(); i += 2) {
    pairs.push_back(std::make_pair(this->elems[i], this->elems[i + 1]));
  }
}

void Vector::insert(int64_t nbr) {
  this->elems.push_back(nbr);
}

void Vector::insertFront(int64_t nbr) {
  this->elems.insert(this->elems.begin(), nbr);
}

void Vector::prepare() {
  if (this->elems.size() % 2 == 1) {
    this->extra = this->elems.back();
    this->elems.pop_back();
  }
}

void Vector::clear() {
  this->elems.clear();
}

void Vector::sort() {
  std::sort(this->elems.begin(), this->elems.end());
}

int64_t Vector::front() const {
  return this->elems.front();
}

void Vector::pop() {
  this->elems.erase(this->elems.begin());
}

int64_t Vector::back() const {
  return this->elems.back();
}

void Vector::popBack() {
  this->elems.pop_back();
}

std::vector<int64_t>::iterator Vector::findInContainer(int64_t value) {
  return std::find(this->elems.begin(), this->elems.end(), value);
}


void Vector::insertWithBinarySearch(uint64_t idx) {
  int64_t value = this->pairs[idx].first;
  std::vector<int64_t>::iterator end = this->findInContainer(this->pairs[idx].second);
  this->elems.insert(std::lower_bound(this->elems.begin(), end, value), value);
}
