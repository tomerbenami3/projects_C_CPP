// ALGORITHM

//You are given a vector of k linked-lists lists, each linked-list is sorted in ascending order.
// Merge all the linked-lists into one sorted linked-list and return it.

// 1. Create Min Heap
// 2. push the first node of each linked list to the min heap.
// 3. loop until:
//     extract the minimum which is the head of the heap.
//     push this node to the linked list
//     go to the next node of this linked list and push it back to the heap.
// 4. return the new sorted linked list.

// Given an text file group all words in the file into groups of anagrams.
// return a vector of lists where each list contain words that are anagrams to each other.
// the vector should be sorted by length of lists (descending).

// 1. Read the words from the file and store them in a list.
    // for each word, sort by key and store it in the relevant place
// 2. Create hashmap to store the words sorted.
// # every list is a group of anagram words
// 3. sort the anagram by size.
// 4. return a vector of lists.

// Given an m x n 2D grid(vector<vector<int>>) which represents a map of '1's (land) and '0's (water), return the number of islands.
// An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. 
// You may assume all four edges of the grid are all surrounded by water.

// 1. go cell by cell until we meet 1 (land).
// 2. if a land found - call a helper function which check every cell if its in the matrix bounds.
// change the cell it self to 0 (in that case 0 means visited).
// 3. if this function return true - increase counter by 1.




