#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <list>

#include "array.hpp"

class Container;

#define JACOBSTHAL_AMOUNT (static_cast<uint64_t>(33))

class PMergeMe {
public:
  typedef ft::array<uint64_t, JACOBSTHAL_AMOUNT> JacobsthalCache;
public:
  PMergeMe(const std::string& str);
  PMergeMe(const PMergeMe& other);
  PMergeMe& operator=(const PMergeMe& other);
  ~PMergeMe();

  void compute();
private:
  PMergeMe();
  void computeJacobsthal();
  void readInput(const std::string& str, Container& container);
  void setup(Container& container);
private:
  JacobsthalCache jacobsthalCache;
  std::string str;
};

class Container {
public:
  Container(
    const PMergeMe::JacobsthalCache& jacobsthalCache
  );
  Container(const Container& other);
  virtual ~Container();
  virtual bool isSorted() const = 0;
  virtual void createPairs() = 0;
  virtual void insert(int64_t nbr) = 0;
  virtual void insertFront(int64_t nbr) = 0;
  virtual void prepare() = 0; // set up the leftover
  virtual void clear() = 0;
  virtual void sort() = 0;
  virtual int64_t front() const = 0;
  virtual void pop() = 0;
  virtual int64_t back() const = 0;
  virtual void popBack() = 0;
  virtual void insertWithBinarySearch(uint64_t idx) = 0;

  void sortPairs();
  void insertSmallestPair();
  void insertLeftover();
  void run();
private:
  Container& operator=(const Container& other);
  Container();
protected:
  const PMergeMe::JacobsthalCache& jacobsthalCache;
  std::vector<std::pair<int64_t, int64_t > > pairs;
  int64_t extra;
};
