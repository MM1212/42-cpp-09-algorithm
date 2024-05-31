#include "PMergeMe.hpp"
#include "Vector.hpp"
#include <sstream>

PMergeMe::PMergeMe(const std::string& str) : str(str) {
  this->computeJacobsthal();
}

PMergeMe::PMergeMe(const PMergeMe& other) : jacobsthalCache(other.jacobsthalCache), str(other.str) {}

PMergeMe& PMergeMe::operator=(const PMergeMe& other) {
  if (this != &other) {
    this->jacobsthalCache = other.jacobsthalCache;
    this->str = other.str;
  }
  return *this;
}

PMergeMe::~PMergeMe() {}

void PMergeMe::computeJacobsthal() {
  this->jacobsthalCache[0] = 0;
  this->jacobsthalCache[1] = 1;
  for (size_t i = 2; i < JACOBSTHAL_AMOUNT; ++i) {
    this->jacobsthalCache[i] = this->jacobsthalCache[i - 1] + 2 * this->jacobsthalCache[i - 2];
  }
}

void PMergeMe::readInput(const std::string& str, Container& container) {
  std::stringstream ss(str);

  int64_t nbr;
  uint64_t i = 0;
  while (ss >> nbr) {
    container.insert(nbr);
    i++;
  }
  if (i < 2) {
    throw std::invalid_argument("Not enough numbers");
  }
  if (container.isSorted()) {
    throw std::invalid_argument("Already sorted");
  }
}

void PMergeMe::setup(Container& container) {
  container.prepare();
  container.createPairs();
  container.clear();
}

void PMergeMe::compute() {
  Vector vec(this->jacobsthalCache);

  this->readInput(this->str, vec);
  this->setup(vec);
  vec.sortPairs();
  vec.insertSmallestPair();
  vec.insertLeftover();
  vec.run();
}
