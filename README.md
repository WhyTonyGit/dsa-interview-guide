# 🚀 interview-data-structures

> Полный справочник по структурам данных и алгоритмам на C++17 — для подготовки к техническим собеседованиям в лучших IT-компаниях.

[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Build](https://img.shields.io/badge/build-CMake-green.svg)](CMakeLists.txt)

---

## 📋 Содержание

- [Обзор](#обзор)
- [Структуры данных](#структуры-данных)
- [Алгоритмы](#алгоритмы)
- [Быстрый старт](#быстрый-старт)
- [Структура проекта](#структура-проекта)
- [Гайд по подготовке к собеседованиям](#гайд-по-подготовке-к-собеседованиям)
- [Контрибьютинг](#контрибьютинг)

---

## Обзор

Этот репозиторий содержит **production-quality** реализации всех основных структур данных и алгоритмов, которые вы встретите на собеседованиях в IT-компаниях. Каждая реализация:

- Написана на **C++17** с полной поддержкой шаблонов
- Следует **Google C++ Style Guide**
- Включает **Doxygen-style комментарии**
- Имеет **unit тесты** с Google Test
- Поставляется с **паттернами для интервью** и реальными примерами вопросов
- **Valgrind-clean** (без утечек памяти)

---

## Структуры данных

| Структура | Частота | Компании | Сложность |
|-----------|---------|----------|-----------|
| [Массивы](src/data_structures/arrays/) | ⭐⭐⭐⭐⭐ 95% | Все | Easy–Hard |
| [Связные списки](src/data_structures/linked_lists/) | ⭐⭐⭐⭐⭐ 85% | Google, Meta, Amazon | Easy–Medium |
| [Стеки и очереди](src/data_structures/stacks_queues/) | ⭐⭐⭐⭐ 80% | Все | Easy–Medium |
| [Хеш-таблицы](src/data_structures/hash_tables/) | ⭐⭐⭐⭐⭐ 90% | Все | Easy–Hard |
| [Деревья (BST/AVL)](src/data_structures/trees/) | ⭐⭐⭐⭐⭐ 88% | Google, Apple, Microsoft | Medium–Hard |
| [Графы](src/data_structures/graphs/) | ⭐⭐⭐⭐ 75% | Google, Facebook, Uber | Medium–Hard |
| [Кучи](src/data_structures/heaps/) | ⭐⭐⭐⭐ 70% | Amazon, Google | Medium |
| [Префиксные деревья (Trie)](src/data_structures/tries/) | ⭐⭐⭐ 55% | Google, Airbnb | Medium–Hard |
| [Union-Find](src/data_structures/union_find/) | ⭐⭐⭐ 50% | Google, Amazon | Medium |
| [Битовые операции](src/data_structures/bit_manipulation/) | ⭐⭐⭐ 45% | Low-level / Системное ПО | Easy–Medium |

---

## Алгоритмы

| Алгоритм | Частота | Описание |
|----------|---------|---------|
| [Сортировка](src/algorithms/sorting/) | ⭐⭐⭐⭐⭐ | QuickSort, MergeSort, HeapSort |
| [Бинарный поиск](src/algorithms/searching/) | ⭐⭐⭐⭐⭐ | Варианты, ротированные массивы |
| [Динамическое программирование](src/algorithms/dynamic_programming/) | ⭐⭐⭐⭐⭐ | Мемоизация, табуляция |
| [Жадные алгоритмы](src/algorithms/greedy/) | ⭐⭐⭐⭐ | Интервалы, планирование |
| [Backtracking](src/algorithms/backtracking/) | ⭐⭐⭐⭐ | Перестановки, N-ферзей |
| [Два указателя](src/algorithms/two_pointers/) | ⭐⭐⭐⭐⭐ | Скользящее окно, быстрый/медленный |

---

## Быстрый старт

### Требования

```bash
# macOS
brew install cmake googletest

# Ubuntu / Debian
sudo apt-get install cmake libgtest-dev
```

### Сборка и запуск

```bash
git clone https://github.com/yourname/interview-data-structures.git
cd interview-data-structures

mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)

# Запустить все примеры
./examples_arrays
./examples_linked_lists
./examples_trees
./examples_graphs
./examples_heaps
./examples_tries
./examples_sorting
./examples_dp

# Запустить тесты
ctest --output-on-failure
# или напрямую
./tests/run_tests
```

### Запустить один пример

```bash
cd build
make examples_arrays
./examples_arrays
```

---

## Структура проекта

```
interview-data-structures/
├── README.md
├── CONTRIBUTING.md
├── LICENSE
├── .gitignore
├── CMakeLists.txt
├── docs/
│   ├── interview-frequency.md     # Как часто каждая тема встречается
│   ├── complexity-cheatsheet.md   # Таблица Big-O
│   ├── cpp-tips.md                # Советы по C++ для интервью
│   └── tips-and-tricks.md        # Общие стратегии для собеседования
├── src/
│   ├── data_structures/           # 10 основных структур данных
│   └── algorithms/                # 6 категорий алгоритмов
├── tests/                         # Google Test unit тесты
└── interview_questions/
    ├── easy.md                    # LeetCode Easy с решениями
    ├── medium.md                  # LeetCode Medium с решениями
    └── hard.md                    # LeetCode Hard с решениями
```

---

## Гайд по подготовке к собеседованиям

### План подготовки на 4 недели

**Неделя 1 — Основы**
- Массивы, строки, хеш-таблицы (95% частота на собесах)
- Паттерны "два указателя" и "скользящее окно"
- Практика: 10 Easy + 5 Medium задач

**Неделя 2 — Линейные структуры**
- Связные списки, стеки, очереди
- Основы рекурсии
- Практика: 5 Easy + 10 Medium задач

**Неделя 3 — Древовидные структуры**
- Бинарные деревья, BST, кучи
- Обходы DFS / BFS
- Практика: 15 Medium задач

**Неделя 4 — Продвинутые темы**
- Графы (BFS/DFS/Dijkstra), динамическое программирование
- Tries, Union-Find, Backtracking
- Практика: 10 Medium + 5 Hard задач

### Как использовать этот репозиторий

1. Прочитайте `README.md` в папке каждой структуры данных
2. Изучите реализацию в `.hpp` — поймите каждый метод
3. Прочитайте `patterns.md` чтобы выучить самые частые паттерны
4. Запустите и модифицируйте `examples.cpp`
5. Решите задачи из `interview_questions/`

---

## Документация

| Документ | Описание |
|----------|---------|
| [Частота на собесах](docs/interview-frequency.md) | Частота тем по компаниям и уровням |
| [Таблица сложности](docs/complexity-cheatsheet.md) | Все Big-O сложности в одном месте |
| [Советы по C++](docs/cpp-tips.md) | Использование STL, RAII, частые ошибки |
| [Советы и трюки](docs/tips-and-tricks.md) | Стратегии коммуникации на собеседовании |

---

## Примеры собес-вопросов

```
Easy:   Two Sum, Valid Parentheses, Merge Two Sorted Lists
Medium: LRU Cache, Binary Tree Level Order, Number of Islands
Hard:   Serialize/Deserialize Binary Tree, Word Ladder, Median of Data Streams
```

Полные решения с объяснениями смотрите в [interview_questions/](interview_questions/).

---

## Контрибьютинг

Смотрите [CONTRIBUTING.md](CONTRIBUTING.md) для гайдлайнов.

---

## Лицензия

MIT — смотрите [LICENSE](LICENSE).
