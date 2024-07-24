#include "List.hpp"
#include <algorithm>
#include <iostream>
#include <set>

List::List(
  const PMergeMe::JacobsthalCache& jacobsthalCache
) : Container(jacobsthalCache) {}
List::List(const List& other) : Container(other), elems(other.elems) {}
List::~List() {}

bool List::isSorted() const {
  for (List::const_iterator it = this->elems.begin(); it != this->elems.end(); ++it) {
    List::const_iterator next = it;
    ++next;
    if (
      next != this->elems.end() &&
      *it > *next
      ) {
      return false;
    }
  }
  return true;
}

void List::createPairs() {
  this->pairs.clear();
  for (List::iterator it = this->elems.begin(); it != this->elems.end(); ++it) {
    List::iterator before = it++;
    if (it != this->elems.end()) {
      pairs.push_back(std::make_pair(*before, *it));
    }
  }
}

void List::insert(int64_t nbr) {
  this->elems.push_back(nbr);
}

void List::insertFront(int64_t nbr) {
  this->elems.push_front(nbr);
}

void List::prepare() {
  if (this->elems.size() % 2 == 1) {
    this->extra = this->elems.back();
    this->elems.pop_back();
  }
  else
    this->extra = -1;
}

void List::clear() {
  this->elems.clear();
}

void List::sort() {
  this->elems.sort();
}

int64_t List::front() const {
  return this->elems.front();
}

void List::pop() {
  this->elems.pop_front();
}

int64_t List::back() const {
  return this->elems.back();
}

void List::popBack() {
  this->elems.pop_back();
}

std::list<int64_t>::iterator List::findInContainer(int64_t value) {
  return std::find(this->elems.begin(), this->elems.end(), value);
}

void List::insertWithBinarySearch(uint64_t idx) {
  int64_t value = this->pairs[idx].first;
  std::list<int64_t>::iterator it = this->findInContainer(this->pairs[idx].second);
  this->elems.insert(std::lower_bound(this->elems.begin(), it, value), value);
}

void List::output() const {
  for (List::const_iterator it = this->elems.begin(); it != this->elems.end(); ++it) {
    if (it != this->elems.begin())
      std::cout << " ";
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

bool List::hasDuplicates() const {
  std::set<int64_t> seen;
  for (List::const_iterator it = this->elems.begin(); it != this->elems.end(); ++it) {
    if (seen.find(*it) != seen.end()) {
      return true;
    }
    seen.insert(*it);
  }
  return false;
}
