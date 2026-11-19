class Solution {
    struct Edge {
        int u, v, weight;
    };

    int find(int vertex, std::vector<int>& parent) {
        if (parent[vertex] != vertex) {
            parent[vertex] = find(parent[vertex], parent);
        }
        return parent[vertex];
    }

public:
    int minCostConnectPoints(std::vector<std::vector<int>>& points) {
        int n = static_cast<int>(points.size());
        std::vector<Edge> edges;
        // n *(n-1) /2  is the total edges  
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int weight = std::abs(points[i][0] - points[j][0])
                           + std::abs(points[i][1] - points[j][1]);
                edges.push_back({i, j, weight});
            }
        }

        std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.weight < b.weight;
        }); // sort the edges 


        //
        std::vector<int> parent(n);
        std::iota(parent.begin(), parent.end(), 0);
        std::vector<int> size(n, 1);

        int totalCost = 0;
        int edgesUsed = 0;

        for (const Edge& edge : edges) {
            int u = find(edge.u, parent);
            int v = find(edge.v, parent);
            if (u == v) continue;

            if (size[u] < size[v]) std::swap(u, v);
            parent[v] = u;
            size[u] += size[v];

            totalCost += edge.weight;
            if (++edgesUsed == n - 1) break;
        }

        return totalCost;
    }
};
