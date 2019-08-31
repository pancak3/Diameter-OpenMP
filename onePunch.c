#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 10000
#define NOT_CONNECTED (INT_MAX)

int diameter(int distance[MAX][MAX], int nodesCount);

int distance[MAX][MAX];

/* initialize all distances to */
void Initialize() {
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            distance[i][j] = NOT_CONNECTED;
        }
        distance[i][i] = 0;
    }
}

uint64_t GetTimeStamp() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * (uint64_t) 1000000 + tv.tv_usec;
}

int main() {
    /* test data area, should be delete before real test*/
//    int testGraph[5][5] =
//            //0  1  2  3  4
//            {{NOT_CONNECTED, 5,             2,             NOT_CONNECTED, 15}, //0
//             {NOT_CONNECTED, NOT_CONNECTED, 6, 1,                         NOT_CONNECTED},  //1
//             {NOT_CONNECTED, NOT_CONNECTED, NOT_CONNECTED, NOT_CONNECTED, 1},  //2
//             {9,             4,             NOT_CONNECTED, NOT_CONNECTED, 2},  //3
//             {NOT_CONNECTED, 6,             NOT_CONNECTED, NOT_CONNECTED, NOT_CONNECTED}   //4
//            };
//
//
//    printf("The ans is: %d\n", diameter(testGraph, 5));
//    /* up */
//
    /* number of nodes */
    int nodeCount;

    /* Number of edges */
    int m;

    Initialize();

    /* get the node count */
    if (scanf("%d", &nodeCount) < 1) {
        fprintf(stderr, "Error reading node count\n");
        exit(1);
    }
    if (nodeCount < 1 || nodeCount > MAX) {
        fprintf(stderr, "Invalid number of nodes, %d.  Must be 1 to %d\n",
                nodeCount, MAX);
        exit(1);
    }

    /* edge count */
    if (scanf("%d", &m) < 1) {
        fprintf(stderr, "Error reading edge count\n");
        exit(1);
    }
    if (m < nodeCount - 1 || m > nodeCount * (nodeCount - 1)) {
        fprintf(stderr, "Invalid number of edges, %d.  Must be %d to %d\n",
                m, nodeCount - 1, nodeCount * (nodeCount - 1));
        exit(1);
    }

    while (m--) {
        /* nodes - let the indexation begin from 0 */
        int a, b;

        /* edge weight */
        int c;

        if (scanf("%d %d %d", &a, &b, &c) < 3) {
            fprintf(stderr, "Error reading edge\n");
            exit(1);
        }
        if (a < 0 || a >= nodeCount || b < 0 || b >= nodeCount || c <= 0) {
            fprintf(stderr, "Invalid edge: from %d to %d weight %d\n", a, b, c);
            exit(1);
        }
        distance[a][b] = c;
    }

    uint64_t start = GetTimeStamp();

    printf("Diameter %d\n", diameter(distance, nodeCount));

    printf("Time: %ld us\n", (uint64_t) (GetTimeStamp() - start));
//
    return 0;
}

/******************************************************************************/
/*  Your changes here */

#include "omp.h"

int localVertexCount;
int localDistance[MAX][MAX];

#pragma omp threadprivate(localVertexCount, localDistance)

int *Dijkstra(int fromVertex, int vertexCount, int graph[MAX][MAX]);

int diameter(int givenDistance[MAX][MAX], int vertexCount) {

    uint64_t start = GetTimeStamp();
    int *distancesTable[vertexCount];
    int maxThreadsNum = omp_get_max_threads();


#pragma omp parallel for
    for (int l = 0; l < maxThreadsNum; ++l) {
        localVertexCount = vertexCount;

//        printf("p: %d\n", omp_get_thread_num());
        for (int k = 0; k < localVertexCount; ++k) {
            for (int i = 0; i < localVertexCount; ++i) {
                localDistance[k][i] = givenDistance[k][i];
            }
        }
    }
    printf("[*] time spent on copy global matrix to local: %ld us\n", GetTimeStamp() - start);
    start = GetTimeStamp();


#pragma omp parallel for
    for (int i = 0; i < vertexCount; ++i) {
        localVertexCount = vertexCount;
//        printf("p: %d local V C %d\n", omp_get_thread_num(), localVertexCount);
        distancesTable[i] = Dijkstra(i, localVertexCount, localDistance);

    }
    printf("[*] time spent on Dijkstra: %ld us\n", GetTimeStamp() - start);
    start = GetTimeStamp();

#pragma omp barrier
//    printf("\n[*] distancesTable:\n");
//    for (int m = 0; m < vertexCount; ++m) {
//        printf("%d: ", m);
//
//        for (int i = 0; i < vertexCount; ++i) {
//            printf("%d ", distancesTable[m][i]);
//        }
//        printf("\n");
//    }

    int diameter = 0;
/*
 * search maximum distance(diameter) in parallel should be here blow
 * in these comments, you can find how to get each vertex's distances to other vertices
 *    EX: *(distancesTable[i] + j)
 *
 * */
    for (int i = 0; i < vertexCount; ++i) {
        int maxDistance = 0;
        for (int j = 0; j < vertexCount; ++j) {
            if (*(distancesTable[i] + j) > maxDistance && *(distancesTable[i] + j) != NOT_CONNECTED)
                maxDistance = *(distancesTable[i] + j);
//            printf("%11d ", *(distancesTable[i] + j));
        }
//        printf("\nmaximum distance for vertex(%d): %d.\n", i, maxDistance);
        if (maxDistance > diameter) {
            diameter = maxDistance;
        }

    }
    printf("[*] time spent on bubble search: %ld us\n", GetTimeStamp() - start);

//    printf("Dijkstra Time: %ld us\n", (uint64_t) (GetTimeStamp() - start));
    return diameter;
}

int *Dijkstra(int fromVertex, int vertexCount, int graph[MAX][MAX]) {
    int visitedVertex[vertexCount];
//    int distancesOfThisVertex[vertexCount];
    int *distancesOfThisVertex = malloc(vertexCount * sizeof(int));

    int minEdge, vertex = 0, searchedEdgesCount = 0;

    for (int i = 0; i < vertexCount; ++i) {
        visitedVertex[i] = 0;
        distancesOfThisVertex[i] = graph[fromVertex][i];
    }
    visitedVertex[fromVertex] = 1;

    distancesOfThisVertex[fromVertex] = 0;

    while (searchedEdgesCount < vertexCount - 1) {
        searchedEdgesCount++;
        minEdge = NOT_CONNECTED;

        for (int i = 0; i < vertexCount; ++i) {
            if (visitedVertex[i] == 0 && minEdge > distancesOfThisVertex[i]) {
                vertex = i;
                minEdge = distancesOfThisVertex[i];
            }
        }

        visitedVertex[vertex] = 1;

        for (int i = 0; i < vertexCount; ++i) {
            if (visitedVertex[i] == 0 && graph[vertex][i] != NOT_CONNECTED &&
                distancesOfThisVertex[vertex] != NOT_CONNECTED) {
                int tmp = distancesOfThisVertex[vertex] + graph[vertex][i];
                if (tmp < distancesOfThisVertex[i]) {
                    distancesOfThisVertex[i] = distancesOfThisVertex[vertex] + graph[vertex][i];
                }

            }
        }

    }
    return distancesOfThisVertex;
}
/* The following is the exact command used to compile this code */
/* g++ -O2 graph-diameter.cpp -o graph-diameter */