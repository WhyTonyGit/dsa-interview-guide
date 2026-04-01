# 🚀 interview-data-structures

> A comprehensive C++17 reference for data structures and algorithms — built for technical interview preparation at top tech companies.

[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Build](https://img.shields.io/badge/build-CMake-green.svg)](CMakeLists.txt)

---

## 📋 Table of Contents

- [Overview](#overview)
- [Data Structures](#data-structures)
- [Algorithms](#algorithms)
- [Quick Start](#quick-start)
- [Project Structure](#project-structure)
- [Interview Preparation Guide](#interview-preparation-guide)
- [Contributing](#contributing)

---

## Overview

This repository contains **production-quality** implementations of all major data structures and algorithms you will encounter in software engineering interviews. Every implementation:

- Is written in **C++17** with full template support
- Follows **Google C++ Style Guide**
- Includes **Doxygen-style comments**
- Has **unit tests** with Google Test
- Comes with **interview patterns** and real question examples
- Is **valgrind-clean** (no memory leaks)

---

## Data Structures

| Structure | Frequency | Companies | Difficulty |
|-----------|-----------|-----------|------------|
| [Arrays](src/data_structures/arrays/) | ⭐⭐⭐⭐⭐ 95% | All | Easy–Hard |
| [Linked Lists](src/data_structures/linked_lists/) | ⭐⭐⭐⭐⭐ 85% | Google, Meta, Amazon | Easy–Medium |
| [Stacks & Queues](src/data_structures/stacks_queues/) | ⭐⭐⭐⭐ 80% | All | Easy–Medium |
| [Hash Tables](src/data_structures/hash_tables/) | ⭐⭐⭐⭐⭐ 90% | All | Easy–Hard |
| [Trees (BST/AVL)](src/data_structures/trees/) | ⭐⭐⭐⭐⭐ 88% | Google, Apple, Microsoft | Medium–Hard |
| [Graphs](src/data_structures/graphs/) | ⭐⭐⭐⭐ 75% | Google, Facebook, Uber | Medium–Hard |
| [Heaps](src/data_structures/heaps/) | ⭐⭐⭐⭐ 70% | Amazon, Google | Medium |
| [Tries](src/data_structures/tries/) | ⭐⭐⭐ 55% | Google, Airbnb | Medium–Hard |
| [Union-Find](src/data_structures/union_find/) | ⭐⭐⭐ 50% | Google, Amazon | Medium |
| [Bit Manipulation](src/data_structures/bit_manipulation/) | ⭐⭐⭐ 45% | Low-level / Systems | Easy–Medium |

---

## Algorithms

| Algorithm | Frequency | Notes |
|-----------|-----------|-------|
| [Sorting](src/algorithms/sorting/) | ⭐⭐⭐⭐⭐ | QuickSort, MergeSort, HeapSort |
| [Binary Search](src/algorithms/searching/) | ⭐⭐⭐⭐⭐ | Variants, rotated arrays |
| [Dynamic Programming](src/algorithms/dynamic_programming/) | ⭐⭐⭐⭐⭐ | Memoization, tabulation |
| [Greedy](src/algorithms/greedy/) | ⭐⭐⭐⭐ | Intervals, scheduling |
| [Backtracking](src/algorithms/backtracking/) | ⭐⭐⭐⭐ | Permutations, N-Queens |
| [Two Pointers](src/algorithms/two_pointers/) | ⭐⭐⭐⭐⭐ | Sliding window, fast/slow |

---

## Quick Start

### Prerequisites

```bash
# macOS
brew install cmake googletest

# Ubuntu / Debian
sudo apt-get install cmake libgtest-dev
```

### Build & Run

```bash
git clone https://github.com/yourname/interview-data-structures.git
cd interview-data-structures

mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)

# Run all examples
./examples_arrays
./examples_linked_lists
./examples_trees
./examples_graphs
./examples_heaps
./examples_tries
./examples_sorting
./examples_dp

# Run tests
ctest --output-on-failure
# or directly
./tests/run_tests
```

### Run a single example

```bash
cd build
make examples_arrays
./examples_arrays
```

---

## Project Structure

```
interview-data-structures/
├── README.md
├── CONTRIBUTING.md
├── LICENSE
├── .gitignore
├── CMakeLists.txt
├── docs/
│   ├── interview-frequency.md     # How often each topic appears
│   ├── complexity-cheatsheet.md   # Big-O reference table
│   ├── cpp-tips.md                # C++ specific interview tips
│   └── tips-and-tricks.md        # General interview strategy
├── src/
│   ├── data_structures/           # 10 core data structures
│   └── algorithms/                # 6 algorithm categories
├── tests/                         # Google Test unit tests
└── interview_questions/
    ├── easy.md                    # LeetCode Easy with solutions
    ├── medium.md                  # LeetCode Medium with solutions
    └── hard.md                    # LeetCode Hard with solutions
```

---

## Interview Preparation Guide

### 4-Week Study Plan

**Week 1 — Foundations**
- Arrays, Strings, Hash Tables (95% interview frequency)
- Two Pointers, Sliding Window patterns
- Practice: 10 Easy + 5 Medium problems

**Week 2 — Linear Structures**
- Linked Lists, Stacks, Queues
- Recursion fundamentals
- Practice: 5 Easy + 10 Medium problems

**Week 3 — Tree Structures**
- Binary Trees, BST, Heaps
- DFS / BFS traversals
- Practice: 15 Medium problems

**Week 4 — Advanced Topics**
- Graphs (BFS/DFS/Dijkstra), Dynamic Programming
- Tries, Union-Find, Backtracking
- Practice: 10 Medium + 5 Hard problems

### How to Use This Repo

1. Read the `README.md` in each data structure folder
2. Study the `.hpp` implementation — understand every method
3. Read `patterns.md` to learn the most common interview patterns
4. Run and modify `examples.cpp`
5. Solve the problems listed in `interview_questions/`

---

## Documentation

| Document | Description |
|----------|-------------|
| [Interview Frequency](docs/interview-frequency.md) | Topic frequency by company and level |
| [Complexity Cheatsheet](docs/complexity-cheatsheet.md) | All Big-O complexities in one place |
| [C++ Tips](docs/cpp-tips.md) | STL usage, RAII, common pitfalls |
| [Tips & Tricks](docs/tips-and-tricks.md) | Interview communication strategies |

---

## Sample Interview Questions

```
Easy:   Two Sum, Valid Parentheses, Merge Two Sorted Lists
Medium: LRU Cache, Binary Tree Level Order, Number of Islands
Hard:   Serialize/Deserialize Binary Tree, Word Ladder, Median of Data Streams
```

See [interview_questions/](interview_questions/) for full solutions with explanations.

---

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

---

## License

MIT — see [LICENSE](LICENSE).
