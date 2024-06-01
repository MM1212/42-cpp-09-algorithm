#include "PMergeMe.hpp"
#include <deque>

class Deque : public Container {
public:
  Deque(
    const PMergeMe::JacobsthalCache& jacobsthalCache
  );
  Deque(const Deque& other);
  ~Deque();
  bool isSorted() const;
  void createPairs();
  void insert(int64_t nbr);
  void insertFront(int64_t nbr);
  void prepare();
  void clear();
  void sort();
  int64_t front() const;
  void pop();
  int64_t back() const;
  void popBack();
  void insertWithBinarySearch(uint64_t idx);
  void output() const;
  bool hasDuplicates() const;
private:
  std::deque<int64_t>::iterator findInContainer(int64_t value);
  Deque& operator=(const Deque& other);
  Deque();
private:
  std::deque<int64_t> elems;
};
