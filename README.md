<!-- omit in toc -->
# Meta-Hacker-Cup-2022

[![tokei](https://tokei.rs/b1/github/duken72/Meta-Hacker-Cup-2022)](https://github.com/duken72/Meta-Hacker-Cup-2022)

My solutions for [Meta Hacker Cup 2022](https://www.facebook.com/codingcompetitions/hacker-cup/2022)

<!-- omit in toc -->
## Table of Contents

- [Notes](#notes)
- [Qualification round](#qualification-round)
  - [Problem A: Second Hands](#problem-a-second-hands)
  - [Problem B1: Second Friend](#problem-b1-second-friend)
  - [Problem B2: Second-Second Friend](#problem-b2-second-second-friend)
  - [Problem C1 \& C2: Second Meaning](#problem-c1--c2-second-meaning)
- [Round 1](#round-1)
  - [Problem A1: Consecutive Cuts - Chapter 1](#problem-a1-consecutive-cuts---chapter-1)
  - [Problem A2: Consecutive Cuts - Chapter 2](#problem-a2-consecutive-cuts---chapter-2)
  - [Problem B1 \& B2: Watering Well](#problem-b1--b2-watering-well)
  - [Problem C: Lemonade Life](#problem-c-lemonade-life)
- [Round 2](#round-2)
  - [Problem A1: Perfectly Balanced - Chapter 1](#problem-a1-perfectly-balanced---chapter-1)
  - [Problem A2: Perfectly Balanced - Chapter 2](#problem-a2-perfectly-balanced---chapter-2)
  - [Problem C: Balance Scale](#problem-c-balance-scale)
  - [Problem D1: Work-Life Balance - Chapter 1](#problem-d1-work-life-balance---chapter-1)
  - [Problem D2: Work-Life Balance - Chapter 2](#problem-d2-work-life-balance---chapter-2)
- [Round 3](#round-3)
  - [Problem A: Fourth Player](#problem-a-fourth-player)
  - [Problem B: Third Trie](#problem-b-third-trie)
- [Final round](#final-round)

-------

## Notes

- Many usages are not recommended normally, but for the sake of being fast here, e.g.: `using namespace std;`
- Everything is compiled and ran with `run.sh`, change execution permission if needed

-------

## Qualification round

[Source problems](https://www.facebook.com/codingcompetitions/hacker-cup/2022/qualification-round)

### Problem A: Second Hands

It is possible to arrange N parts if:

- No. parts N < the capacity of 2 case 2K
- No part style has more than 2 items
- Using array instead of vector has little improvement, probably too small of a problem

### Problem B1: Second Friend

- It is always possible if the width and height are both greater than 1
- If either the width or height is 1, it is still possible if there is no tree
- In case we need to add tree, filling all spaces with trees will be the simplest method, though it is overkill.

### Problem B2: Second-Second Friend

- Similar to B1, if either the width or height is 1, it is possible if there is no tree
- Define "good tree" as tree that can have at least 2 neighboring trees, "bad tree" as tree that can have only 1 neighboring tree.
- Find all positions for these good trees, by keeping an array of possible neighboring trees, than iteratively remove where there is a bad tree.

    E.g.: with this map:

    ```txt
    ..^.            2231            2220
    .#^#     -->    2020      -->   2020
    ....            3342            3342
    ..^.            2332            2332
    ```

  - The second array represents the counts of possible neighboring trees.
  - The bad tree is the one with value 1, in the top right corner. We reduce that to 0, and also minus 1 from neighboring cell
  - This process is repeated until all bad trees are checked.
- After that, we have a map of all good trees.
- If the original map has a "bad tree", then it is impossible.
- Otherwise, simply fill the map with all good trees.

### Problem C1 & C2: Second Meaning

- Each codeword will be represented as a node in a binary tree

```txt
root    -   --  ---
                --.
            -.  -.-
                -..
        .   .-  .--
                .-.
            ..  ..-
                ...
depth:  1   2   3
length: 1   2   3
```

- Key idea is that codewords with same length will be an unambiguous encoding
- Even for C2, when the length is limited at 10, there will be enough codewords, since N ≤ 100
- For both problems, start with finding the length for enough codewords: `L = log(N) base 2`
- This L might be greater or smaller than the length L1 of the 1st codeword.
- For ease, the rest codewords will have different starting character than the 1st one.

-------

## Round 1

[Source problems](https://www.facebook.com/codingcompetitions/hacker-cup/2022/round-1)

### Problem A1: Consecutive Cuts - Chapter 1

- Some edge cases:
  - 0 cut, the order doesn't change
  - 1 cut, the order changes
  - There is only 2 cards:
    - odd no. cuts, the order changes
    - even no. cuts, the order doesn't change
- Otherwise, if it's possible, it would be with one single cut

### Problem A2: Consecutive Cuts - Chapter 2

- Similar edge cases as A1: 0 cut and only 2 cards.
- With indistinct cards, we have to try more than once.
- First find the type with the smallest no. cards
- Then try all possible cut with that type
- Alternatively, the initial card sequence can be converted to a string and doubled, then we simply need to check whether the later sequence exists as a substring.

### Problem B1 & B2: Watering Well

- We can separate the sum in each axis $x$ and $y$
- In $x$ axis, we have:

  $$ \sum_{i = 1}^N \sum_{j = 1}^Q (a_i - x_j)^2 = \sum_{i = 1}^N \sum_{j = 1}^Q (a_i^2 - 2a_i x_j + x_j^2) = Q \sum_{i = 1}^N a_i^2 + N \sum_{j = 1}^Q x_j^2 - 2 \sum_{i = 1}^N a_i \sum_{j = 1}^Q x_j $$

- The 4 values can be computed in $\mathcal{O}(N)$ as we read the input: $\sum_{i = 1}^N a_i^2$, $\sum_{j = 1}^Q x_j^2$, $\sum_{i = 1}^N a_i$, $\sum_{j = 1}^Q x_j$
- Afterward, the result can be computed in $\mathcal{O}(1)$
- Additionally, be careful with modulus arithmetic.

### Problem C: Lemonade Life

- Firstly, filter the houses coordinates by finding the convex hull
- Run Dijkstra algorithm:
  - With priority queue, correct but slower
  - Without priority queue: much faster, but got 1 case wrong??
    - After finding points on convex hull, sort them based on their distances with start point.
    - Ignore points which is further, compared to target point.

-------

## Round 2

[Source problems](https://www.facebook.com/codingcompetitions/hacker-cup/2022/round-2)

### Problem A1: Perfectly Balanced - Chapter 1

- Edge case: substring has only 1 char
- Firstly, an almost perfectly balanced string must have odd no. characters.
- Secondly, the first half and the second half of the substring must have the same each character, except for the one would be removed
- Thus, simply have a matrix of size $N \times 26$ to store and compare the counts

### Problem A2: Perfectly Balanced - Chapter 2

- Since we have both range query and update, use Segment Tree
- TODO:

### Problem C: Balance Scale

- Precompute all the modulo of factorial
- Compute mod inverse: [guide](https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/)
- The final probability depends on the no. cookies in the 1st batch $C1$, the no. cookies with lighter weight $C2$, equal weight $C3$, heavier weight $C4$ and the no. weighting time $K$.
- With $K + 1 > C - C4$, there will be at least one cookie that is heavier than batch 1, thus, it's impossible for the remaining cookie to be from batch 1
- Calculate the probability of getting $K+1$ cookies that is not heavier than $W1$ and has at least one with $W1$: $\frac{x_1 - x_2}{x_3}$
  - No. way to pick $K+1$ cookies that is not heavier than $W1$: $x_1 = {{C1 + C2 + C3} \choose {K+1}}$
  - No. way to pick $K+1$ cookies that is lighter than $W1$: $x_2 = {{C2} \choose {K+1}}$
  - No. way to pick $K+1$ cookies: $x_3 = {{C} \choose {K+1}}$
- Tie breaking based on $C1$ and $C3$: $\frac{x_1 - x_2}{x_3} \times \frac{C1}{C1 + C3}$

### Problem D1: Work-Life Balance - Chapter 1

- Here, we also have range queries and updates. But instead of arbitrary ranges, we only need to query from start to specified position, and deduce from that. Thus, Fenwick tree is a better alternative here.
- We keep 3 trees for 3 task types: $Ai ∈ \{1,2,3\}$
- Edge case: since each swap increase/reduce the sum by an even number and the final sum is even (as the two sides are equal), the total sum has to be even from the start.
- After getting the counts from 3 Fenwick trees, we will be able to tell which side is greater, and we will switch task from which side to which side.
- For minimum number of switch, we start with all 3-1 switches first, before going for 3-2 and 2-1 switches.
- Be careful, because there might not be enough tasks to switch around

### Problem D2: Work-Life Balance - Chapter 2

- Still using Fenwick tree as with problem D1
- Since we can only swap adjacent elements, in the end, to have the minimum number of swaps, there will be a sub-range of the lower side that is full of '2'.
- Find that position $s$, which leads to the half the total sum
- Next, find the position $t$, which from $s$ to $t$, there is enough '2' to switch to the lower side.
- To compute number of swap, have a separate Fenwick tree calculate sum of indices
- To deal with the inverse case, simply keeping 2 more trees for the inverse direction.

-------

## Round 3

[Source problems](https://www.facebook.com/codingcompetitions/hacker-cup/2022/round-3)

### Problem A: Fourth Player

- Strategy to maximize winning points:
  - B1: covers as many cards of player A1 as possible
  - A2:
    - covers as many cards of B1 as possible
    - improve as many cards of A1 as possible
  - B2: covers as many cards of team A as possible

### Problem B: Third Trie

- Assuming that a string is present in $k$ tries of total $N$ tries, then its contribution to the final sum is ${N \choose 3} - {N-k \choose 3}$
- Thus, we need to count the presence of each string.
- Idea: (not ... very efficient and fast though)
  - Keep a vector of string for each trie, each element of the vector is a node in the trie.
  - Use a hash table to keep and increment the count of each string.
- Problem: a bad structure to store `string` data, leads to OEM problem (Out of memory) for large test case

-------

## Final round

[Source problems](https://www.facebook.com/codingcompetitions/hacker-cup/2022/final-round)
