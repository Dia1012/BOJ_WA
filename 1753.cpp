#include <iostream>
#include <algorithm>

using namespace std;

int v, e, k;
int inf = 1000;

int a[20001][20001];
bool vis[20001];
int d[20001];

int getSmallIndex(){
    int min = inf;
    int index = 0;
    for(int i = 0; i < v; i++){
        if(d[i] < min && !vis[i]){
            min = d[i];
            index = i;
        }
    }
    return index;
}

void dijkstra(int start){
    for(int i = 0; i < v; i++) d[i] = a[start][i];
    vis[start] = true;
    for(int i = 0; i < v - 2; i++){
        int current = getSmallIndex();
        vis[current] = true;
        for(int j = 0; j < v; j++){
            if(!vis[j]){
                if(d[current] + a[current][j] < d[j]){
                    d[j] = d[current] + a[current][j];
                }
            }
        }
    }
}

int main(){
    fill(&a[0][0], &a[20001][20001], inf);
    cin >> v >> e >> k;
    for(int i = 0; i < v; i++) a[i][i] = 0;
    for(int i = 0; i < e; i++){
        int l, m, n;
        cin >> l >> m >> n;
        a[l][m] = n;
    }
    dijkstra(k);
    for(int i = 1; i <= v; i++){
        if(d[i] == 1000) cout << "INF" << '\n';
        else cout << d[i] << '\n';
    }
}
