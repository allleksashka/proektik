#include <stdio.h>
#define MAX 1000
int nu[MAX][MAX], ew[MAX][MAX], nc[MAX];

int dfs(int u, int parent, int w) {
	int i, chld = 0, leaf = 1;
	for (i = 0; i < nc[u]; ++i) {
		if (nu[u][i] != parent) {
			leaf = 0;
			chld += dfs(nu[u][i], u, ew[u][nu[u][i]]);
		}
	}
	return (w < chld || leaf) ? w : chld;
}
int main(){
	int i, n, c;
	while(scanf("%d%d", &n, &c) == 2) {
		for(i = 0; i < n; ++i)
      nc[i] = 0;
		for(i = 1; i < n; ++i){
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
      --u; --v;
			nu[u][nc[u]++] = v;
			nu[v][nc[v]++] = u;
			ew[u][v] = ew[v][u] = w;
		}
		printf("%d\n", dfs(c-1, -1, 10000000));
	}
	return 0;
}
