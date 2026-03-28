#include <algorithm>
#include <iostream>
#include <limits.h>
#include <queue>
#include <set>
#include <stack>
#include <vector>

const int MAX_VAL = 1e9;

// Задача № 5
std::vector<int> bfs_base(
	std::vector<std::vector<int>>& g, 
	const int start
) {
	std::vector<int> dist(g.size(), -1);
	std::queue<int> q;
	
	q.push(start);
	dist[start] = 0;
	
	while(!q.empty()) {
		const int from = q.front();
		q.pop();
		for (int to: g[from]) {
			if (dist[to] == -1) {
				dist[to] = dist[from] + 1;
				q.push(to);
			}
		}
	}
	return dist;
}

// Задача № 6
std::pair<std::vector<int>, std::vector<int>> bfs_base_find_path(
	std::vector<std::vector<int>>& g, const int start
) {
	std::vector<int> dist(g.size(), -1);
	std::vector<int> from_arr(g.size(), -1);
	std::queue<int> q;
	
	q.push(start);
	dist[start] = 0;
	
	while(!q.empty()) {
		const int from = q.front();
		q.pop();
		for (int to: g[from]) {
			if (dist[to] == -1) {
				dist[to] = dist[from] + 1;
				from_arr[to] = from;
				q.push(to);
			}
		}
	}
	return {dist, from_arr};
}

std::vector<int> get_path(
	std::vector<int>& from_arr, 
	const int finish
) {
	std::vector<int> path;
	for (int to = finish; to != -1; to = from_arr[to]) {
		path.push_back(to);
	}
	std::reverse(path.begin(), path.end());
	return path;
}

// Задача № 7
std::vector<int> bfs_dijkstra(
	std::vector<std::vector<std::pair<int, int>>>& g, 
	const int start
) {
	std::vector<int> dist(g.size(), MAX_VAL);
	dist[start] = 0;
	std::vector<bool> visited(g.size(), false);
	
	for (int i = 0; i < g.size(); i++) {
		int nearest = -1;
		for (int v = 0; v < g.size(); v++) {
			if (!visited[v] 
				&& (nearest == -1 || dist[nearest] > dist[v])
			) {
				nearest = v;
			}
		}
		
		visited[nearest] = true;
		
		for (auto& [to, weight]: g[nearest]) {
			if (dist[to] > dist[nearest] + weight) {
				dist[to] = dist[nearest] + weight;
			}
		}
	}
	
	return dist;
}

// Задача № 8
std::vector<int> bfs_dijkstra_set(
	std::vector<std::vector<std::pair<int, int>>>& g, 
	const int start
) {
	std::vector<int> dist(g.size(), MAX_VAL);
	dist[start] = 0;
	std::set<std::pair<int, int>> q;
	q.insert({dist[start], start});
	
	while (!q.empty()) {
		int nearest = q.begin()->second;
		q.erase(q.begin());
	
		for (auto& [to, weight]: g[nearest]) {
			if (dist[to] > dist[nearest] + weight) {
				q.erase({dist[to], to});
				dist[to] = dist[nearest] + weight;
				q.insert({dist[to], to});
			}
		}
	}
	
	return dist;
}

int main() {
	// ------------------------------------------------------------------------
	// Неориентированный невзвешенный граф
	// ------------------------------------------------------------------------
	std::vector<std::vector<int>> edges = {
		{0, 1}, {1, 8}, {8, 5}, {0, 3}, {8, 2}, {5, 6}, {7, 3}, 
		{3, 2}, {2, 6}, {7, 9}, {3, 9}, {2, 9}, {2, 4}
	};
	const int vertex_count = 10;
	std::vector<std::vector<int>> graph(vertex_count);
	for (int i = 0; i < edges.size(); i++) {
		const int from = edges[i][0];
		const int to = edges[i][1];
		graph[from].push_back(to);
		graph[to].push_back(from);
	}
	
	// ------------------------------------------------------------------------
	// Задача № 5
	// ------------------------------------------------------------------------
	{
		std::cout 
		<< "Поиск кратчайших путей "
		<< "в неоринетированных невзвешенных графах" 
		<< std::endl;
		const int start = 0;
		std::cout 
			<< "Кратчайшие расстояния от "
			<< start 
			<< " до остальных вершин: ";
		std::vector<int> dist = bfs_base(graph, start);
		for (int i = 0; i < dist.size(); i++) {
			std::cout << i << " = " << dist[i] << ", ";
		}
		std::cout << std::endl << std::endl;
	}
	
	// ------------------------------------------------------------------------
	// Задача № 6
	// ------------------------------------------------------------------------
	{
		std::cout 
			<< "Поиск кратчайших путей "
			<< "в неоринетированных невзвешенных графах "
			<< "и восстановление пути"
			<< std::endl;
		
		const int start = 0;
		auto [dist, from_arr] = bfs_base_find_path(graph, start);
		
		for (int i = 0; i < dist.size(); i++) {
			std::cout 
				<< "Кратчайшее расстояния от "
				<< start 
				<< " до вершины "
				<< i << " = " << dist[i]
				<< ", а путь состоит из: ";
			for(int v: get_path(from_arr, i)) {
				std::cout << v << ", ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;
	}

	// ------------------------------------------------------------------------
	// Неориентированный взвешенный граф
	// ------------------------------------------------------------------------
	std::vector<std::vector<std::pair<int, int>>> weight_graph = {
		{{1, 15}, {5, 20}}, // вершина 0, её соседи и веса рёбер
		{{2, 25}, {6, 0}, {0, 15}}, // 1
		{{3, 10}, {7, 70}, {1, 25}}, // 2
		{{8, 50}, {2, 10}}, // 3
		{{9, 10}}, // 4
		{{10, 30}, {0, 20}}, // 5
		{{7, 40}, {10, 10}, {1, 0}}, // 6
		{{8, 30}, {12, 60}, {2, 70}, {6, 40}}, // 7
		{{12, 5}, {13, 70}, {3, 50}, {7, 30}}, // 8
		{{14, 25}, {4, 10}}, // 9
		{{11, 10}, {5, 30}, {6, 10}}, // 10
		{{12, 35}, {10, 10}}, // 11
		{{13, 70}, {7, 60}, {8, 5}, {11, 35}}, // 12
		{{8, 70}, {12, 70}}, // 13
		{{9, 25}} // 14
	};
	
	// ------------------------------------------------------------------------
	// Задача № 7 и 8
	// ------------------------------------------------------------------------
	{
		std::cout 
			<< "Поиск кратчайших путей "
			<< "в неоринетированных взвешенных графах"
			<< "(алгоритм Дейкстры): ";
		
		const int start = 7;
		// + bfs_dijkstra_set
		std::vector<int> dist = bfs_dijkstra(weight_graph, start);
		for (int i = 0; i < dist.size(); i++) {
			if (dist[i] != MAX_VAL) {
				std::cout << i << " = " << dist[i] << ", ";
			} else {
				std::cout << i << " = " << "-, ";
			}
		}
		std::cout << std::endl << std::endl;
	} 
}
