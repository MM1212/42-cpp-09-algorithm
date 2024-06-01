#include "PMergeMe.hpp"
#include "Vector.hpp"
#include "Deque.hpp"
#include "List.hpp"
#include <sstream>
#include <iostream>
#include <limits>

PMergeMe::PMergeMe(int ac, char** av) {
  this->computeJacobsthal();
  this->parse(ac, av);
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
  if (container.hasDuplicates()) {
    throw std::invalid_argument("Duplicates");
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
  std::cout << "Before: " << this->str << std::endl;
  this->computeContainer<Vector>("Vector", true);
  this->computeContainer<Deque>("Deque");
  this->computeContainer<List>("List");
}

void PMergeMe::parse(int ac, char** av) {
  for (uint32_t i = 0; i < static_cast<uint32_t>(ac); i++) {
    if (!IsNumberValid(av[i])) {
      throw std::invalid_argument("Invalid number");
    }
    this->str += av[i];
    if (i < static_cast<uint32_t>(ac) - 1) {
      this->str += " ";
    }
  }
}

bool PMergeMe::IsNumberValid(const std::string& str) {
  for (uint64_t i = 0; i < str.size(); i++) {
    if (!std::isdigit(str[i])) {
      return false;
    }
  }
  long long nbr = std::atoll(str.c_str());
  if (nbr < std::numeric_limits<int>::min() || nbr > std::numeric_limits<int>::max()) {
    return false;
  }
  return true;
}
