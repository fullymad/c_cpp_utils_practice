/*****************************************************************************
https://www.hackerrank.com/challenges/bfsshortreach/problem
******************************************************************************/
#include <cmath>
#include <cstdio>
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

void print_graph(
	vector<vector<bool> > &graph
)
{
	for (int i = 0; i < graph.size(); i++) {
		vector<bool> &adj_list = graph[i];
		cout << "Node: " << i + 1 << endl;

		for (int j = 0; j < adj_list.size(); j++) {
			if (adj_list[j] == true) {
				cout << "Edge from node " << i + 1
					<< " to " << j + 1 << endl;
			}
		}

		cout << endl;
	}

	return;

} /* end print_graph */

void print_queue(
	queue<pair<short, short> > &in_queue
)
{
	queue<pair<short, short> > temp_queue(in_queue);

	cout << "Start of queue" << endl;
	while (! temp_queue.empty()) {
		cout << "(" << temp_queue.front().first << ", "
				<< temp_queue.front().second << "),";
		temp_queue.pop();
	}
	cout << "End of queue" << endl;

} /* end print_queue */

int main() {
	int	queries, nodes, edges, start_node, first_node, second_node;

	cin >> queries;

	for (int q = 0; q < queries; q++) {
		cin >> nodes >> edges;

		/* Create a graph based on adjacency list that contains a bitmap */
		vector<vector<bool> > graph(nodes, vector<bool>(nodes, false));

		for (int e = 0; e < edges; e++) {
			cin >> first_node >> second_node;

			/* Set adjacency list element to True for both nodes */
			vector<bool> &adj_list_1 = graph[first_node - 1];
			adj_list_1[second_node - 1] = true;

			vector<bool> &adj_list_2 = graph[second_node - 1];
			adj_list_2[first_node - 1] = true;
		}

		cin >> start_node;

		// Initialize distance from start_node to every other node as 0. Note
		// that the same array is used to mark that a node has been queued
		// (that is, value is not 0 if already queued).

		vector<int> distances(nodes, 0);

		// Breadth-first search starting with given start node
		// The pair contains the node being visited and its 'previous node'
		queue<pair<short, short> > bfs_queue;

		/* Parent does not matter for start node */
		bfs_queue.push(pair<short, short>(start_node, start_node));

		while (! bfs_queue.empty()) {
			pair<short, short> queue_elem = bfs_queue.front();
			bfs_queue.pop();

			int next_node = queue_elem.first;
			int prev_node = queue_elem.second;

			if (next_node != start_node &&
				distances[next_node - 1] == 0) { /* Not yet visited */
				distances[next_node - 1] = distances[prev_node - 1] + 6;
			}

			vector<bool> &adj_list = graph[next_node - 1];

			for (int i = 0; i < nodes; i++) {
				if (adj_list[i] == true) {
					if (distances[i] == 0) { // Not yet visited
						bfs_queue.push(pair<short, short>(i + 1, next_node));
					}
				}
			}

			//print_queue(bfs_queue);
		}

		/* Print shortest distances from given node to every other node */
		bool first_edge = true; /* No space before first edge in output */
		
		for (int i = 0; i < distances.size(); i++) {
			if (i != (start_node - 1)) {

				if (first_edge) {
					first_edge = false;
				}
				else {
					cout << " ";
				}

				if (distances[i] == 0) {
					cout << "-1";
				}
				else {
					cout << distances[i];
				}
			}
		}
		cout << endl;

		//print_graph(graph);

	} /* for each query */

	return 0;
}

