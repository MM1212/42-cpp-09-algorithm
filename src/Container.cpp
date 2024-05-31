#include "PMergeMe.hpp"

Container::Container(
  const PMergeMe::JacobsthalCache& jacobsthalCache
) : jacobsthalCache(jacobsthalCache) {}

Container::Container(const Container& other) : jacobsthalCache(other.jacobsthalCache), pairs(other.pairs), extra(other.extra) {}

Container::~Container() {}

void Container::sortPairs() {
  for (size_t i = 0; i < this->pairs.size(); ++i) {
    if (this->pairs[i].first > this->pairs[i].second) {
      std::swap(this->pairs[i].first, this->pairs[i].second);
    }
    this->insert(this->pairs[i].second);
  }
  this->sort();
}

void Container::insertSmallestPair() {
  int64_t smallest = this->front();
  for (uint32_t i = 0; i < this->pairs.size(); i++) {
    if (this->pairs[i].second != smallest)
      continue;
    this->insertFront(this->pairs[i].first);
    this->pairs.erase(this->pairs.begin() + i);
    return;
  }
}

void Container::insertLeftover() {
  this->pairs.push_back(std::make_pair(this->extra, 0));
}

void Container::run() {
  for (size_t i = 0; i < std::min(JACOBSTHAL_AMOUNT, this->pairs.size()); i++) {
    uint64_t currIndex = this->jacobsthalCache[i];
    if (currIndex >= this->pairs.size())
      currIndex = this->pairs.size() - 1;
    int64_t prevIndex = i == 0 ? this->jacobsthalCache[i] - 1 : this->jacobsthalCache[i - 1];
    for (int64_t j = currIndex; j > prevIndex; j--)
      this->insertWithBinarySearch(j);
  }

}
