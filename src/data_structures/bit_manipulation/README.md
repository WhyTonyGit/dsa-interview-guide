# Bit Manipulation

Bit manipulation operates directly on the binary representation of integers. It produces concise, highly efficient O(1) solutions to problems that would otherwise require O(n) code.

## Essential Bit Operations

| Operation | Syntax | Description |
|-----------|--------|-------------|
| AND | `a & b` | 1 only if both bits are 1 |
| OR | `a \| b` | 1 if either bit is 1 |
| XOR | `a ^ b` | 1 if bits differ |
| NOT | `~a` | Flip all bits |
| Left shift | `a << n` | Multiply by 2^n |
| Right shift | `a >> n` | Divide by 2^n (arithmetic for signed) |

## Essential Bit Tricks

| Trick | Code | Use |
|-------|------|-----|
| Get bit i | `(n >> i) & 1` | Test if bit i is set |
| Set bit i | `n \| (1 << i)` | Force bit i to 1 |
| Clear bit i | `n & ~(1 << i)` | Force bit i to 0 |
| Toggle bit i | `n ^ (1 << i)` | Flip bit i |
| Clear lowest set bit | `n & (n-1)` | Remove rightmost 1-bit |
| Isolate lowest set bit | `n & (-n)` | Get value of rightmost 1 |
| Is power of two | `n > 0 && (n & (n-1)) == 0` | |
| Count set bits | `__builtin_popcount(n)` | Hamming weight |

## ✅ When to Use

- XOR to find single/unique element (cancellation property)
- Bitmask DP (track subsets with an integer)
- Check properties of numbers (power of 2, odd/even)
- Space-efficient boolean flags
- Swap without temporary variable

## 📊 Interview Frequency

- **45%** overall, higher at systems/embedded companies
- Commonly appears at Apple, Google (systems questions)
- Usually Easy to Medium difficulty

## Key XOR Properties

```
x ^ x = 0       (cancellation)
x ^ 0 = x       (identity)
XOR is commutative and associative

→ XOR all elements: duplicates cancel, unique remains
```

See [patterns.md](patterns.md) for interview patterns.
