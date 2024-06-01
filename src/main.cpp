#include <PMergeMe.hpp>
#include <iostream>

int main(int ac, char** av) {
  ac--;
  av++;
  try {
    PMergeMe p(ac, av);
    p.compute();
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
