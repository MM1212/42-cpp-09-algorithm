#include "PMergeMe.hpp"
#include <list>

class List : public Container {
public:
  typedef std::list<int64_t>::iterator iterator;
  typedef std::list<int64_t>::const_iterator const_iterator;
  List(
    const PMergeMe::JacobsthalCache& jacobsthalCache
  );
  List(const List& other);
  ~List();
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
  std::list<int64_t>::iterator findInContainer(int64_t value);
  List& operator=(const List& other);
  List();
private:
  std::list<int64_t> elems;
};
