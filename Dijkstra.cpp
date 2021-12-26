//
// Created by kuzin on 24.12.2021.
//


#include "Dijkstra.h"
float *Dijkstra(float **GR, int V, int st) {
//Алгоритм Дейкстры - находит расстояние вершины номер st
//графа GR размерностью V	до всех остальных
//Вернет массив расстояний, INT_MAX - прохода нет
    int  count, index, i, u;
    float *distance;
    bool *visited;
    distance = new float [V];
    visited = new bool [V];
    for (i=0; i<V; i++) { distance[i]=INT_MAX; visited[i]=false; }
    distance[st]=0;
    for (count=0; count<V-1; count++) {
        int min=INT_MAX;
        for (i=0; i<V; i++)
            if (!visited[i] && distance[i]<=min) { min=distance[i]; index=i; }
        u=index;
        visited[u]=true;
        for (i=0; i<V; i++)
            if (!visited[i] && GR[u][i] && distance[u]!=INT_MAX &&
                distance[u]+GR[u][i]<distance[i])
                distance[i]=distance[u]+GR[u][i];
    }
    return distance;
}

