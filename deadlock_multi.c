#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int numProcesses, numResources;
int allocation[MAX][MAX], request[MAX][MAX];
bool visited[MAX];
bool deadlocked[MAX];
int i,j;

bool dfs(int graph[MAX][MAX], int v, int parent) {
    visited[v] = true;
    for ( i = 0; i < numProcesses; i++) {
        if (graph[v][i]) {
            if (!visited[i]) {
                if (dfs(graph, i, v)) {
                    return true;
                }
            } else if (i != parent) {
                return true;
            }
        }
    }
    return false;
}


void buildWaitForGraph(int graph[MAX][MAX]) {
    for ( i = 0; i < numProcesses; i++) {
        for ( j = 0; j < numProcesses; j++) {
            if (i != j && request[i][j] > 0 && allocation[j][i] > 0) {
                graph[i][j] = 1;
            } else {
                graph[i][j] = 0;
            }
        }
    }
}


void detectDeadlock() {
    int graph[MAX][MAX];
    buildWaitForGraph(graph);

    for ( i = 0; i < numProcesses; i++) {
        visited[i] = false;
    }

    bool isDeadlock = false;

    for ( i = 0; i < numProcesses; i++) {
        if (!visited[i]) {
            if (dfs(graph, i, -1)) {
                isDeadlock = true;
                break;
            }
        }
    }

    if (isDeadlock) {
        printf("Deadlock detected.\nDeadlocked processes are:\n");
        for ( i = 0; i < numProcesses; i++) {
            if (visited[i]) {
                printf("Process %d\n", i);
            }
        }
    } else {
        printf("No deadlock detected.\n");
    }
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    printf("Enter the allocation matrix:\n");
    for ( i = 0; i < numProcesses; i++) {
        for ( j = 0; j < numResources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the request matrix:\n");
    for ( i = 0; i < numProcesses; i++) {
        for ( j = 0; j < numResources; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    detectDeadlock();

    return 0;
}
