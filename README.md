# Skip List Implementation in C++

## What is a skip list?
A skip list stores sorted data across multiple linked lists stacked on top of each 
other. The bottom level has every element, and each level above is kind of like an 
express lane with fewer stops. This makes search, insert, and delete O(log n) on 
average without having to deal with all the rebalancing stuff that comes with trees.

## Why I chose this
Honestly Red-Black Trees kind of broke my brain. I wanted to find something that 
gets the same O(log n) performance but without all the painful rebalancing. The cool 
thing about skip lists is they use random coin flips to stay balanced on average — 
no rotations, no color flipping, just probability doing the work. They're also used 
in real systems like Redis which I thought was pretty cool.

## Operations
- **insert(value)** - inserts a value and flips a coin to decide how many levels it gets promoted to
- **search(value)** - starts at the top level and drops down until it finds the value
- **deleteNode(value)** - removes a value and re-links the pointers at each level
- **print()** - prints the skip list level by level so you can see the structure

## How to Run
```bash
g++ skip_list.cpp -o skip_list
./skip_list
```

## Challenges
- Managing the pointers across multiple levels during deletion was definitely the 
trickiest part
- I also wanted to actually understand the probability behind why this works and 
not just take it on faith