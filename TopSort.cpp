#include <algorithm>
#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<uint32_t>>;

bool CycleFindDFS(uint32_t ver, std::vector<uint16_t>& used, const Graph& g) {
  used[ver] = 1;
  for (auto neighbour : g[ver]) {
    if (!used[neighbour]) {
      if (CycleFindDFS(neighbour, used, g)) {
        return true;
      }
    } else if (used[neighbour] == 1) {
      return true;
    }
  }
  used[ver] = 2;
  return false;
}

bool HasCycle(const Graph& graph) {
  std::vector<uint16_t> used(graph.size(), 0);
  for (size_t i = 1; i < graph.size(); ++i) {
    if (!used[i] && CycleFindDFS(i, used, graph)) {
      return true;
    }
  }
  return false;
}

void DFS(uint32_t ver, std::vector<bool>& used, const Graph& g, std::vector<uint32_t>& topsort) {
  used[ver] = true;
  for (auto neighbour : g[ver]) {
    if (!used[neighbour]) {
      DFS(neighbour, used, g, topsort);
    }
  }
  topsort.emplace_back(ver);
}

void TopSort(const Graph& graph) {
  if (HasCycle(graph)) {
    std::cout << -1 << std::endl;
    return;
  }
  std::vector<bool> used(graph.size(), false);
  std::vector<uint32_t> topsort;
  for (size_t i = 1; i < graph.size(); ++i) {
    if (!used[i]) {
      DFS(static_cast<uint32_t>(i), used, graph, topsort);
    }
  }
  for (auto it = topsort.rbegin(); it != topsort.rend(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  Graph graph(n + 1);
  for (size_t i = 0; i < m; ++i) {
    uint32_t from, to;
    std::cin >> from >> to;
    graph[from].emplace_back(to);
  }
  TopSort(graph);
}