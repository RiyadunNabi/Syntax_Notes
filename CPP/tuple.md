# ✅ Tuples in C++

## ✅ Declaration
```cpp
#include <vector>
#include <tuple>
using namespace std;

vector<tuple<int, int, int>> MST;
```

---

## ✅ Insertion
You can insert tuples using `make_tuple` or initializer list (`{}`):

```cpp
MST.push_back(make_tuple(u, v, weight));  // preferred
MST.push_back({u, v, weight});            // also works (C++11+)
```

---

## ✅ Accessing Elements
Use `get<index>()` to access tuple elements:

```cpp
int u = get<0>(MST[i]);
int v = get<1>(MST[i]);
int w = get<2>(MST[i]);
```

Or use structured bindings (C++17+):

```cpp
auto [u, v, w] = MST[i];
```
