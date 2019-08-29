#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define X 10000
//#define vertexCount  7  //实际上共有六个顶点（1---6）
#define EdgeNum  9
#define NOT_CONNECTED (INT_MAX)

int giverGraph[5][5] =
        //  1  2  3  4  5  6{}
//        {
//                X, 6, 3, X, X, X,  //1
//                X, X, X, 5, X, X,  //2
//                X, 2, X, 3, 4, X,  //3
//                X, X, X, X, X, 3,  //4
//                X, X, X, 2, X, 5,  //5
//                X, X, X, X, X, X   //6
//        };
        //0  1  2  3  4
        {{X, 5, 2, X, 15}, //0
         {X, X, 6, 1, X},  //1
         {X, X, X, X, 1},  //2
         {9, 4, X, X, 2},  //3
         {X, 6, X, X, X}   //4
        };


void ourDijkstra(int fromVertex, int vertexCount, int visitedVertex[], int path[], int distances[]) {
    int minEdge, Vertex, i, j, searchedEdgeCount;
    searchedEdgeCount = 0;
    visitedVertex[fromVertex] = 1;
    for (i = 0; i < vertexCount; i++) distances[i] = giverGraph[fromVertex][i];

    distances[fromVertex] = 0;
    printf("     0  1  2  3  4  5\n");
    printf("-----------------------------------\n");
    printf("s:%d", searchedEdgeCount);
    for (i = 0; i < vertexCount; i++)
        if (distances[i] == X) printf("  *"); else printf("%3d", distances[i]);
    printf("\n");
    while (searchedEdgeCount < vertexCount - 1) {
        searchedEdgeCount++;
        minEdge = X;
        for (j = 0; j < vertexCount; j++)
            if (visitedVertex[j] == 0 && minEdge > distances[j]) {
                Vertex = j;
                minEdge = distances[j];
            }
        visitedVertex[Vertex] = 1;
        printf("s:%d", searchedEdgeCount);
        for (j = 0; j < vertexCount; j++) {
            if (visitedVertex[j] == 0 && distances[Vertex] + giverGraph[Vertex][j] < distances[j]) {
                distances[j] = distances[Vertex] + giverGraph[Vertex][j];
                path[j] = Vertex;
            }
            //printf("%6d",distances[j]);
            if (distances[j] == X) printf("  *"); else printf("%3d", distances[j]);
        }
        printf("\n");
    }
}

void main() {

    int i;
    int k;
    int vertexCount = 5;
    int visitedVertex[vertexCount];
    int path[vertexCount];
    int distances[vertexCount];

    for (i = 0; i < vertexCount; i++) {
        visitedVertex[i] = 0;
        path[i] = 1;
        distances[i] = NOT_CONNECTED;
    }
    ourDijkstra(2, vertexCount, visitedVertex, path, distances);
    printf("\n\nAll Path-------------------------\n");


    for (i = 0; i < vertexCount; i++) //printf("%5d",visitedVertex[i]);
    {
        printf("[%d] ", distances[i]);
        k = i;
        do {
            printf("%d<--", k);
            k = path[k];
        } while (k != 1);
        printf("2 \n");
    }
}