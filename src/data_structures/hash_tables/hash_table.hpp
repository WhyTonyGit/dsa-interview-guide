#pragma once

#include <functional>
#include <list>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

/**
 * @file hash_table.hpp
 * @brief Hash table using separate chaining for collision resolution.
 *
 * Load factor is kept below kMaxLoadFactor by rehashing (doubling bucket count).
 * Average-case O(1) for insert, lookup, and delete.
 *
 * @tparam Key   Key type. Must support std::hash<Key> and operator==.
 * @tparam Value Value type.
 */
template <typename Key, typename Value>
class HashMap {
 public:
  using value_type = std::pair<Key, Value>;
  using Bucket     = std::list<value_type>;

  // ─── Constructor ──────────────────────────────────────────────────────────

  /**
   * @brief Construct with given initial bucket count.
   * @complexity O(n) — allocates n buckets
   */
  explicit HashMap(std::size_t bucket_count = 16)
      : buckets_(bucket_count), size_(0) {}

  // ─── Capacity ─────────────────────────────────────────────────────────────

  bool        empty() const noexcept { return size_ == 0; }
  std::size_t size()  const noexcept { return size_; }

  double load_factor() const noexcept {
    return static_cast<double>(size_) / buckets_.size();
  }

  // ─── Modifiers ────────────────────────────────────────────────────────────

  /**
   * @brief Insert or overwrite key-value pair.
   * @complexity O(1) average
   */
  void insert(const Key& key, const Value& value) {
    if (load_factor() > kMaxLoadFactor) rehash();
    Bucket& bucket = buckets_[bucket_index(key)];
    for (auto& [k, v] : bucket) {
      if (k == key) { v = value; return; }  // overwrite
    }
    bucket.emplace_back(key, value);
    ++size_;
  }

  /**
   * @brief Access value by key. Inserts default value if key not found.
   * @complexity O(1) average
   */
  Value& operator[](const Key& key) {
    if (load_factor() > kMaxLoadFactor) rehash();
    Bucket& bucket = buckets_[bucket_index(key)];
    for (auto& [k, v] : bucket)
      if (k == key) return v;
    if (load_factor() > kMaxLoadFactor) rehash();
    bucket.emplace_back(key, Value{});
    ++size_;
    return bucket.back().second;
  }

  /**
   * @brief Remove key. Returns true if erased.
   * @complexity O(1) average
   */
  bool erase(const Key& key) {
    Bucket& bucket = buckets_[bucket_index(key)];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
      if (it->first == key) {
        bucket.erase(it);
        --size_;
        return true;
      }
    }
    return false;
  }

  void clear() noexcept {
    for (auto& b : buckets_) b.clear();
    size_ = 0;
  }

  // ─── Lookup ───────────────────────────────────────────────────────────────

  /**
   * @brief Returns pointer to value for key, or nullptr if not found.
   * @complexity O(1) average
   */
  Value* find(const Key& key) {
    Bucket& bucket = buckets_[bucket_index(key)];
    for (auto& [k, v] : bucket)
      if (k == key) return &v;
    return nullptr;
  }

  const Value* find(const Key& key) const {
    const Bucket& bucket = buckets_[bucket_index(key)];
    for (const auto& [k, v] : bucket)
      if (k == key) return &v;
    return nullptr;
  }

  /**
   * @brief Returns 1 if key exists, 0 otherwise.
   * @complexity O(1) average
   */
  std::size_t count(const Key& key) const {
    return find(key) ? 1 : 0;
  }

  /**
   * @brief Access value by key. Throws if not found.
   * @throws std::out_of_range
   */
  const Value& at(const Key& key) const {
    const Value* v = find(key);
    if (!v) throw std::out_of_range("HashMap::at — key not found");
    return *v;
  }

 private:
  // ─── Internals ────────────────────────────────────────────────────────────

  static constexpr double kMaxLoadFactor = 0.75;

  std::size_t bucket_index(const Key& key) const {
    return std::hash<Key>{}(key) % buckets_.size();
  }

  /**
   * @brief Double bucket count and redistribute all elements.
   * @complexity O(n)
   */
  void rehash() {
    std::vector<Bucket> new_buckets(buckets_.size() * 2);
    for (auto& bucket : buckets_) {
      for (auto& [k, v] : bucket) {
        std::size_t idx = std::hash<Key>{}(k) % new_buckets.size();
        new_buckets[idx].emplace_back(k, v);
      }
    }
    buckets_ = std::move(new_buckets);
  }

  std::vector<Bucket> buckets_;
  std::size_t         size_;
};
