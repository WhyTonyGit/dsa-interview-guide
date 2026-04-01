# Graph Interview Patterns

## Pattern 1: Number of Islands (Grid BFS/DFS)

```cpp
int numIslands(std::vector<std::vector<char>>& grid) {
    if (grid.empty()) return 0;
    int rows = grid.size(), cols = grid[0].size(), count = 0;
    std::function<void(int, int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != '1') return;
        grid[r][c] = '0';  // mark visited
        dfs(r+1,c); dfs(r-1,c); dfs(r,c+1); dfs(r,c-1);
    };
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            if (grid[r][c] == '1') { dfs(r, c); ++count; }
    return count;
}
```

## Pattern 2: Course Schedule (Cycle in Directed Graph)

```cpp
bool canFinish(int numCourses, const std::vector<std::vector<int>>& prereqs) {
    std::vector<std::vector<int>> adj(numCourses);
    std::vector<int> in_degree(numCourses, 0);
    for (const auto& e : prereqs) {
        adj[e[1]].push_back(e[0]);
        ++in_degree[e[0]];
    }
    std::queue<int> q;
    for (int i = 0; i < numCourses; ++i)
        if (in_degree[i] == 0) q.push(i);
    int done = 0;
    while (!q.empty()) {
        int cur = q.front(); q.pop(); ++done;
        for (int nbr : adj[cur])
            if (--in_degree[nbr] == 0) q.push(nbr);
    }
    return done == numCourses;  // false if cycle exists
}
```

## Pattern 3: Word Ladder (BFS shortest path)

```cpp
int ladderLength(const std::string& begin, const std::string& end,
                 std::vector<std::string>& wordList) {
    std::unordered_set<std::string> word_set(wordList.begin(), wordList.end());
    if (!word_set.count(end)) return 0;
    std::queue<std::string> q;
    q.push(begin);
    int steps = 1;
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; ++i) {
            std::string word = q.front(); q.pop();
            if (word == end) return steps;
            for (int j = 0; j < (int)word.size(); ++j) {
                char orig = word[j];
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == orig) continue;
                    word[j] = c;
                    if (word_set.count(word)) {
                        q.push(word);
                        word_set.erase(word);  // avoid revisiting
                    }
                }
                word[j] = orig;
            }
        }
        ++steps;
    }
    return 0;
}
```

## Pattern 4: Dijkstra's (Network Delay Time)

```cpp
int networkDelayTime(const std::vector<std::vector<int>>& times, int n, int k) {
    std::vector<std::vector<std::pair<int,int>>> adj(n + 1);
    for (const auto& t : times) adj[t[0]].push_back({t[1], t[2]});

    std::vector<int> dist(n + 1, INT_MAX);
    dist[k] = 0;
    std::priority_queue<std::pair<int,int>,
                        std::vector<std::pair<int,int>>,
                        std::greater<>> pq;
    pq.push({0, k});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    int ans = *std::max_element(dist.begin() + 1, dist.end());
    return ans == INT_MAX ? -1 : ans;
}
```

## Pattern 5: Bipartite Graph Check

```cpp
bool isBipartite(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<int> color(n, -1);
    for (int start = 0; start < n; ++start) {
        if (color[start] != -1) continue;
        std::queue<int> q;
        q.push(start);
        color[start] = 0;
        while (!q.empty()) {
            int node = q.front(); q.pop();
            for (int nbr : graph[node]) {
                if (color[nbr] == -1) {
                    color[nbr] = 1 - color[node];
                    q.push(nbr);
                } else if (color[nbr] == color[node]) {
                    return false;
                }
            }
        }
    }
    return true;
}
```

## Common Interview Questions

| Question | Algorithm | Difficulty |
|----------|-----------|------------|
| Number of Islands | DFS/BFS grid | Medium |
| Course Schedule | Topo sort / cycle | Medium |
| Course Schedule II | Topo sort | Medium |
| Clone Graph | DFS + hash map | Medium |
| Network Delay Time | Dijkstra | Medium |
| Word Ladder | BFS | Hard |
| Pacific Atlantic Water Flow | BFS from borders | Medium |
| Is Graph Bipartite? | BFS coloring | Medium |
| Minimum Cost to Connect All Points | Kruskal's / Prim's | Medium |
| Alien Dictionary | Topological sort | Hard |
