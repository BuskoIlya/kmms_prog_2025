#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

// Задача № 1
void dfs_base(
	int v, 
	std::vector<std::vector<int>>& g, 
	std::vector<bool>& visited
) {
    visited[v] = true;
    for (int to: g[v]) {
        if (!visited[to]) {
            dfs_base(to, g, visited);
        }
    }
}

bool dfs_from_to(
	int from, int to, 
	std::vector<std::vector<int>>& g, 
	std::vector<bool>& visited
) {
    if (from == to) return true;
    visited[from] = true;
    for (int v: g[from]) {
        if (!visited[v]) {
            if (dfs_from_to(v, to, g, visited)) {
                return true;
            }
        }
    }
    return false;
}

// Задача № 2
void dfs_iterative(
	int start, 
	std::vector<std::vector<int>>& g, 
	std::vector<bool>& visited
) {
    std::stack<int> st;
    st.push(start);

    while(!st.empty()) {
        int cur = st.top();
        st.pop();
        if (visited[cur]) {
            continue;
        }
        visited[cur] = true;
        for (int i = g[cur].size() - 1; i >= 0; i--) {
            int to = g[cur][i];
            if (!visited[to]) {
                st.push(to);
            }
        }
    }
}

// Задача № 3
void dfs_component(
	int v, 
	std::vector<std::vector<int>>& g, 
	std::vector<int>& vertexes, 
	int component
) {
	vertexes[v] = component;
	for (int to: g[v]) {
		if (!vertexes[to]) {
			dfs_component(to, g, vertexes, component);
		}
	}
}

void find_all_component(
	std::vector<int>& vertexes, 
	std::vector<std::vector<int>>& g
) {
	int component = 0;
	for (int v = 0; v < g.size(); v++) {
		if (!vertexes[v]) {
			component++;
			dfs_component(v, g, vertexes, component);
		}
	}
}

// Задача № 4
void dfs_directed_graph_has_cycle(
	int v, 
	std::vector<std::vector<int>>& g, 
	std::vector<int>& visited, 
	bool& has_cycle
) {	
	visited[v] = 1;
	for (int to: g[v]) {
		if (visited[to] == 0) {
			dfs_directed_graph_has_cycle(to, g, visited, has_cycle);
		} else if (visited[to] == 1) {
			has_cycle = true;
		}
	}
	visited[v] = 2;
}

int main() {
	std::vector<std::vector<int>> edges = {
		{0, 4}, {1, 4}, {1, 2}, {2, 5}, 
		{4, 5}, {4, 6}, {5, 7}, {6, 7}
	};
	int vertex_count = 8;
	std::vector<std::vector<int>> g(vertex_count);
	for (int i = 0; i < edges.size(); i++) {
		int from = edges[i][0];
		int to = edges[i][1];
		g[from].push_back(to);
		g[to].push_back(from);
	}
	std::vector<bool> visited(g.size(), false);

	// ------------------------------------------------------------------------
	// Задача № 1
	// ------------------------------------------------------------------------
	std::cout 
		<< "Проверка достижимости вершин "
		<< "неориентированного графа из заданной вершины: ";
	dfs_base(4, g, visited);
	for (bool is_achievable: visited) {
		std::cout << is_achievable << ", ";
	}
	std::cout << std::endl;
	
	std::cout	
		<< "Проверка достижимости конкретной вершины "
		<< "из заданной вершины: ";
	visited.assign(g.size(), false);
	std::cout << dfs_from_to(0, 3, g, visited);
	std::cout << std::endl;
	
	// ------------------------------------------------------------------------
	// Задача № 2
	// ------------------------------------------------------------------------
	std::cout 
		<< "Проверка достижимости вершин графа "
		<< "из заданной вершины при использовании "
		<< "нерекурсивного DFS: ";
	visited.assign(g.size(), false);
	dfs_iterative(3, g, visited);
	for (bool is_achievable: visited) {
		std::cout << is_achievable << ", ";
	}
	std::cout << std::endl;
	
	// ------------------------------------------------------------------------
	// Задача № 3
	// ------------------------------------------------------------------------
	std::cout 
		<< "Значения компонент связности, "
		<< "в которых находятся вершины: ";
	std::vector<int> vertexes(g.size(), 0);
	find_all_component(vertexes, g);
	for (int cc: vertexes) {
		std::cout << cc << " ";
	}
	std::cout << std::endl;
	
	// ------------------------------------------------------------------------
	// Задача № 4
	// ------------------------------------------------------------------------
	std::vector<std::vector<int>> edges2 = {
		{0, 3}, {0, 6}, {3, 1}, {3, 5}, {6, 5}, {6, 2},
		{5, 8}, {8, 1}, {8, 4}, {4, 9}, {9, 8}, {9, 5},
		{9, 2}, {7, 1}, {7, 4}
	};
	vertex_count = 10;
	std::vector<std::vector<int>> g2(vertex_count);
	for (int i = 0; i < edges2.size(); i++) {
		int from = edges2[i][0];
		int to = edges2[i][1];
		g2[from].push_back(to);
	}
	
	std::cout << "Является ли ориентированный граф циклическим? - ";
	std::vector<int> colored_visited(g2.size(), 0);
	bool has_cycle = false;
	for (int v = 0; v < g2.size(); v++) {
		if (!visited[v]) {
			dfs_directed_graph_has_cycle(
				v, 
				g2, 
				colored_visited, 
				has_cycle
			);
		}
	}
	std::cout << has_cycle << std::endl;
}
