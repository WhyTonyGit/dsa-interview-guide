# Contributing to interview-data-structures

Thank you for taking the time to contribute! This project aims to be the best C++ interview preparation resource available.

## How to Contribute

### Reporting Issues

- Use GitHub Issues to report bugs or suggest improvements
- Include the data structure name and a minimal reproducible example
- For compilation errors, include your compiler version and OS

### Adding a New Implementation

1. **Fork** the repository and create a feature branch:
   ```bash
   git checkout -b feature/add-segment-tree
   ```

2. **Follow the file structure** for the data structure folder:
   ```
   src/data_structures/your_structure/
   ├── your_structure.hpp   # Template implementation
   ├── README.md            # Overview + complexity table
   ├── patterns.md          # Interview patterns
   └── examples.cpp         # Runnable examples
   ```

3. **Code standards** — all code must:
   - Compile with `-Wall -Wextra -Wpedantic` and produce **zero warnings**
   - Use C++17 features where appropriate
   - Follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
   - Include Doxygen comments on every public method
   - Have no memory leaks (test with `valgrind --leak-check=full`)
   - Use RAII — never raw `new`/`delete` without a smart pointer or destructor

4. **Add tests** in `tests/test_your_structure.cpp`:
   - Cover all public methods
   - Include edge cases (empty container, single element, duplicates)
   - Add the test file to `tests/CMakeLists.txt`

5. **Update CMakeLists.txt** to include your example binary.

6. **Submit a Pull Request** with a clear description.

### Improving Documentation

- Fix typos, improve explanations, add missing complexity analyses
- Add real interview questions you have encountered (anonymised)
- Translate comments if you want, but code comments must remain in English

## Code Style

```cpp
// ✅ Good
template <typename T>
class MyStructure {
 public:
  /**
   * @brief Insert an element.
   * @param value The value to insert.
   * @complexity O(log n)
   */
  void Insert(const T& value);

 private:
  std::vector<T> data_;
};

// ❌ Bad — no comments, raw pointers, no templates
class MyStructure {
  int* arr;
  void insert(int x);
};
```

## Commit Messages

Use [Conventional Commits](https://www.conventionalcommits.org/):

```
feat(trees): add AVL tree rotation tests
fix(heap): correct index calculation in SiftDown
docs(arrays): add two-sum pattern explanation
refactor(graph): use adjacency list instead of matrix
```

## Review Checklist

Before submitting a PR, verify:

- [ ] Compiles cleanly: `cmake .. && make 2>&1 | grep -E "error|warning"` is empty
- [ ] Tests pass: `ctest --output-on-failure`
- [ ] Valgrind clean: `valgrind --leak-check=full ./examples_xxx`
- [ ] README updated if public API changed
- [ ] patterns.md includes at least 3 interview question examples

## Questions?

Open an issue with the label `question` — we reply within 48 hours.
