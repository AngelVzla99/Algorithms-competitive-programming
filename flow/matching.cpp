/*
Ocupa menos memoria que Dinic y es mucho mas corto
 
n = cantidad de nodos en el grafo sin contar S y T
add_edge( from, to, c ) se hace con cap[from][to] = c
S = n y T = n+1  

( Hasta ahora solo probado con un grafo Unitario, todos los edges costo 1 )
* Tardo lo mismo que Dinic en 1 problema
*/

int n;
int cap[MAXINT][MAXINT];
int visited[MAXINT];

/* Find an augmenting path from s to t in the flow graph using DFS.
 * Returns amount of flow added.
 */
int augment(int s, int t, int c) {
  if (s == t) return c;
  visited[s] = true;
  for (int x = 0; x < n+2; ++x) {
    if (cap[s][x] && !visited[x]) {
      // If there is capacity to an unvisited node, try to augment that way.
      int add = augment(x, t, min(c, cap[s][x]));
      if (add) {
		// Augmenting path found, update capacities
		cap[s][x] -= add;
		cap[x][s] += add;
		return add;
      }
    }
  }
  return 0;
}

/* Ford-Fulkersons algorithm for finding the maximum flow from s to t.
 * Returns the total maximum flow that could be added.
 */
int max_flow(int s, int t) {
  int totflow = 0, addflow = 0;
  do {
    memset(visited, 0, sizeof(visited));
    addflow = augment(s, t, 1<<28);
    totflow += addflow;
  } while (addflow);
  return totflow;
}
