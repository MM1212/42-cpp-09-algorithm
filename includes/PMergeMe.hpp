#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <ctime>

#include "array.hpp"

class Container;

#define JACOBSTHAL_AMOUNT (static_cast<uint64_t>(33))

class PMergeMe {
public:
  typedef ft::array<uint64_t, JACOBSTHAL_AMOUNT> JacobsthalCache;
public:
  PMergeMe(int ac, char** av);
  PMergeMe(const PMergeMe& other);
  PMergeMe& operator=(const PMergeMe& other);
  ~PMergeMe();


  void compute();
private:
  PMergeMe();
  void computeJacobsthal();
  void parse(int ac, char** av);
  void readInput(const std::string& str, Container& container);
  void setup(Container& container);

  static bool IsNumberValid(const std::string& str);

  template <typename T>
  void computeContainer(const std::string& name, bool showAfter = false) {
    T container(this->jacobsthalCache);

    struct timespec start, afterInsertion, end;
    clock_gettime(CLOCK_REALTIME, &start);

    this->readInput(this->str, container);
    clock_gettime(CLOCK_REALTIME, &afterInsertion);
    this->setup(container);
    container.sortPairs();
    container.insertSmallestPair();
    container.insertLeftover();
    container.run();

    clock_gettime(CLOCK_REALTIME, &end);

    if (showAfter) {
      std::cout << "After: ";
      container.output();
    }
    std::cout << name << ":" << std::endl;
    if (!container.isSorted()) {
      std::cout << "- Not sorted" << std::endl;
    }
    else
      std::cout << "- Sorted" << std::endl;
    double time = (double)(end.tv_sec - start.tv_sec) * 1000000 + (double)(end.tv_nsec - start.tv_nsec) / 1000;
    std::cout << "- Time: " << time / 1000 << "ms" << std::endl;
    double timeInsertion = (double)(end.tv_sec - afterInsertion.tv_sec) * 1000000 + (double)(end.tv_nsec - afterInsertion.tv_nsec) / 1000;
    std::cout << "- Time After Insertion: " << timeInsertion / 1000 << "ms" << std::endl;
  }
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
  virtual void output() const = 0;
  virtual bool hasDuplicates() const = 0;

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
