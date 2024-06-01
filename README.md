# Ford-Johnson Merge Insertion Sort Algorithm

## Credits
- [Ford-Johnson Merge Insertion Sort Algorithm](https://en.wikipedia.org/wiki/Merge-insertion_sort)
- Based on [@AshParker19](https://github.com/AshParker19)'s [implementation](https://github.com/AshParker19/42_CPP_modules/tree/main/CPP_09/ex02)

## Overview
- The Ford-Johnson Merge Insertion Sort Algorithm is an algorithm that tries to make the lowest number of comparisons possible in order to sort an array of positive integers in the expense of not being performant (at all).

### Disclaimer

- This was my interpretation of the algorthim, I can't assure that it is 100% correct.
- The code isn't 1:1 to the algorithm explained below.
- This repo has the impl of 3 containers: `std::vector`, `std::list` and `std::deque`.
- I highly encourage you try to implement it yourself, choose any 2 containers (that you haven't used) and figure out why one is faster/slower than the other.
- My implementation is over-engineered on purpose :)

## How it works

- Compute the Jacobsthal numbers until 33 nbrs (after the 32nd number, it will overflow uint64_t) and store them (for better perf).

- Split the numbers into groups of 2 and store the pairs.
   - If the number of elements is odd, the last element is removed and saved for later.

- Sort the pairs (cmp `a` with `b` and swap).
   - Insert the `b` element of each pair into the final array and sort it, recursively.

- Find the pair which has the first element in the final array.
   - Insert the `a` element of the pair at the beginning of the final array.
   - Remove the pair from the pair list.

- If there's a letfover, insert it at the end of the pairs with `a` being the leftover and `b` '-1'.

- We're going to find a range to loop through the pairs and insert the a element of each pair into the final array based on the assumption that it must be between the beginning until the b element (already in the final array).
   - Loop through the min between the pairs's size and amount of jacobsthal numbers computed.
   - The beginning of the range will be the jacobshtal number at the current index.
      - if it is bigger than the amount of pairs, the idx will be the amount of pairs - 1 (to force the next loop to run).
   - The end of the range will be:
      - if its the first iteration, will be the first jacobsthal number - 1 (to force the next loop to run).
      - else, the jacobshtal number at the current index - 1.
   - Loop through the range where each index is the pair index.
      - Find the iterator in the final array where the b element is of the pair.
      - Insert the a element using std::lower_bound between the beginning and the iterator.

### Example

- Run: `./PmergeMe 9 16 15 6 1 4 17 12 11 19 3`
- Input: `9 16 15 6 1 4 17 12 11 19 3`

- Split the numbers into pairs: `9 16`, `15 6`, `1 4`, `17 12`, `11 19`
   - Save the leftover: `3`

- Sort the pairs: `9 16`, `6 15`, `1 4`, `12 17`, `11 19`
   - Insert the `b` element of each pair: `16`, `15`, `4`, `17`, `19` (final array: `16 15 4 17 19`)
      - Sort the final array: `4 15 16 17 19`

- Find the pair which has the first element in the final array: element: `4`, pair: `1, 4`
   - Insert the `a` element of the pair at the beginning of the final array: `1 4 15 16 17 19`
   - Remove the pair from the pair list: `9 16`, `6 15`, `12 17`, `11 19`

- Insert the leftover at the end of the pairs: `9 16`, `6 15`, `12 17`, `11 19`, `3 -1`

- Loop
```
loop_size: min(33, pairs.size() = 5) = 5
i: 0
begin: jacobshtal[i] = 0
end: i == 0 ? jacobshtal[i] - 1 : jacobsthal[i - 1] = -1
foreach(0, -1, --):
  pair[i]: 9 16
  value: 9
  iterator: it(16)
  insert(between (final[0] = 1) and 16) -> 1 4 9 15 16 17 19

i: 1
begin: jacobshtal[i] = 1
end: jacobsthal[i - 1] = 0
foreach(1, 0, --):
  pair[i]: 6 15
  value: 6
  iterator: it(15)
  insert(between (final[0] = 1) and 15) -> 1 4 6 9 15 16 17 19

i: 2
begin: jacobshtal[i] = 1
end: jacobsthal[i - 1] = 1
foreach(1, 1, --):
  pair[i]: 12 17
  value: 12
  iterator: it(17)
  insert(between (final[0] = 1) and 17) -> 1 4 6 9 12 15 16 17 19

i: 3
begin: jacobshtal[i] = 2
end: jacobsthal[i - 1] = 1
foreach(2, 1, --):
  pair[i]: 11 19
  value: 11
  iterator: it(19)
  insert(between (final[0] = 1) and 19) -> 1 4 6 9 11 12 15 16 17 19

i: 4
begin: jacobshtal[i] = 3
end: jacobsthal[i - 1] = 2
foreach(3, 2, --):
  pair[i]: 3 -1
  value: 3
  iterator: it(19)
  insert(between (final[0] = 1) and 19) -> 1 3 4 6 9 11 12 15 16 17 19
```

- Output: `1 3 4 6 9 11 12 15 16 17 19`

## How to run

```bash
make
./PmergeMe <space separated positive integers...>
```
