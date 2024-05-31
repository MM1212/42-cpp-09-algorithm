#include "PMergeMe.hpp"

class Vector : public Container {
public:
  Vector(
    const PMergeMe::JacobsthalCache& jacobsthalCache
  );
  Vector(const Vector& other);
  ~Vector();
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
private:
  std::vector<int64_t>::iterator findInContainer(int64_t value);
  Vector& operator=(const Vector& other);
  Vector();
private:
  std::vector<int64_t> elems;
};
