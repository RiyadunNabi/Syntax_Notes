
# Learning C++ Tuples Through Edge Representation

This guide helps you understand how to use `tuple` in C++ through an example of storing edges in a graph.

---

## ✅ Declaration

To store a list of edges (each represented as a source, destination, and weight), use the `tuple` and `vector` libraries:

```cpp
#include <vector>
#include <tuple>
using namespace std;

// Format: {source, destination, weight}
vector<tuple<int, int, int>> edges;
```

#### 💡 Pro Tip: Type Alias

Improve readability by using a type alias:

```cpp
using Edge = tuple<int, int, int>;
vector<Edge> edges;
```

---

## ✅ Insertion

You can insert a tuple using `make_tuple` or brace initialization:

```cpp
// Method 1: Using make_tuple
edges.push_back(make_tuple(u, v, weight));

// Method 2: Using brace initialization (C++11+)
edges.push_back({u, v, weight});
```

#### ⚡ Modern C++17 Approach

With C++17, prefer `emplace_back` for slightly better performance:

```cpp
edges.emplace_back(u, v, weight);
```

---

## ✅ Accessing Elements

Use `get<index>` to access values inside a tuple:

```cpp
int u = get<0>(edges[i]);
int v = get<1>(edges[i]);
int w = get<2>(edges[i]);
//or
int w, u, v;
std::tie(w, u, v) = t;
```

#### ✨ C++17 Feature: Structured Bindings

Cleaner and more intuitive:

```cpp
auto [u, v, w] = edges[i];
```

---

## ✅ Iterating Through the Tuples

#### 🔁 Traditional Loop

```cpp
for (int i = 0; i < edges.size(); ++i) {
    int u = get<0>(edges[i]);
    int v = get<1>(edges[i]);
    int w = get<2>(edges[i]);
    cout << u << " -- " << v << " : " << w << endl;
}
//or
for (auto &it : edges) {
    int w, u, v;
    std::tie(w, u, v) = it;
    cout << u << " - " << v << " (Weight: " << w << ")\n";
}
```

#### 🔁 C++17 Range-based Loop

```cpp
for (const auto& [u, v, w] : edges) {
    cout << u << " -- " << v << " : " << w << endl;
}
```

---

## Summary

- Use `tuple` to store fixed-size related data.
- Prefer `emplace_back` and structured bindings if you're using C++17.
- Type aliases make your code cleaner and easier to read.
