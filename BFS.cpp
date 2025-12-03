#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Graph{
    vector<vector<int>> matrix;
    int m, n;
public:
    Graph(int _m, int _n){
        n = _n;
        m = _m;
        matrix.resize(m, vector<int>(n));  // 使用 vector 来管理二维数组
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j){
                cin >> matrix[i][j];
            }
        }
    }

    // 计算所有连通块的大小
    int BFS(){
        vector<vector<bool>> v(m, vector<bool>(n, false));
        int ans = 0;
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j){
                if (!v[i][j] && matrix[i][j] == 0){  // 只在遇到值为0的位置进行 BFS
                    v[i][j] = true;
                    ans += bfs(v, i, j);
                }
            }
        }
        return ans;
    }

    // 从 (r, c) 开始进行 BFS，返回连通块的大小
    int bfs(vector<vector<bool>>& v, int r, int c){
        if (r < 0 || r >= m || c < 0 || c >= n) return 0;  // 检查边界
        if (matrix[r][c] != 0 || v[r][c]) return 0;  // 只处理值为 0 且未访问的位置

        queue<pair<int, int>> q;
        int dx[4] = {1, 0, -1, 0};
        int dy[4] = {0, -1, 0, 1};
        int cnt = 1;  // 从当前点开始计数
        q.push({r, c});
        v[r][c] = true;

        while (!q.empty()){
            auto f = q.front();
            q.pop();
            for (int j = 0; j < 4; ++j){
                int a = f.first + dx[j];
                int b = f.second + dy[j];
                if (a >= 0 && a < m && b >= 0 && b < n && matrix[a][b] == 0 && !v[a][b]){
                    cnt++;
                    q.push({a, b});
                    v[a][b] = true;
                }
            }
        }
        return cnt;
    }
};

int main(){
    int t;
    cin >> t;
    while (t--){
        int m, n;
        cin >> m >> n;
        Graph g(m, n);
        cout << g.BFS() << endl;
    }
    return 0;
}
