#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Util.h"
#include "Graph.h"

TGraphL* createGraphAdjList(int numberOfNodes) {
	//TODO: 1
	TGraphL* graph = malloc(sizeof(TGraphL));
	if(graph == NULL) 
		return NULL;
	graph->nn = numberOfNodes;
	graph->adl = malloc(numberOfNodes * sizeof(TNode*));
	for(int i=0; i<numberOfNodes;i++)
		graph->adl[i] = NULL;
	return graph;
	return NULL;
}

void addEdgeList(TGraphL* graph, int v1, int v2) {
	//TODO: 1
	ATNode nod1 = calloc(1,sizeof(TNode));
	if(nod1 == NULL) return;
	ATNode nod2 = calloc(1,sizeof(TNode));
	if(nod2 == NULL) return;
	nod1->v = v2;
	nod1->next = graph->adl[v1];
	graph->adl[v1] = nod1;
	
	nod2->v = v1;
	nod2->next = graph->adl[v2];
	graph->adl[v2] = nod2;
}
//stiva == recursivitate
List* dfsIterative(TGraphL* graph, int s) {
	//TODO: 2
	Stack* st = createStack();
	List* path = createList();
	int *visited = calloc(graph->nn, sizeof(int));
	push(st, s);
	visited[s] = 1;
	enqueue(path, s);
	while(!isStackEmpty(st)) {
		int v = top(st);
		ATNode iter;
		for(iter = graph->adl[v]; iter != NULL; iter = iter->next) {
			if(visited[iter->v] == 0) {
				visited[iter->v] = 1;
				push(st, iter->v);
				enqueue(path, iter->v);
				break;
			}
		}
		if(iter == NULL) {
			pop(st);
			break;
		}
	}
	destroyStack(st);
	free(visited);
	return path;
}

void dfsRecHelper(TGraphL* graph, int* visited, List* path, int s) {
	//TODO: 3
	visited[s] = 1;
	enqueue(path, s);
	for(ATNode iter = graph->adl[s]; iter != NULL; iter = iter->next) {
		if(visited[iter->v] == 0) {
			dfsRecHelper(graph,visited, path,iter->v);
		}
	}
}

List* dfsRecursive(TGraphL* graph, int s) {
	// TODO 3
	List* path = createList();
	int *visited = calloc(graph->nn, sizeof(int));
	dfsRecHelper(graph, visited, path, s);
	free(visited);
	return path;
}

List* bfs(TGraphL* graph, int s) {
	// TODO: 4
	Queue* q = createQueue();
	List* path = createQueue();
	int *visited = calloc(graph->nn, sizeof(int));
	enqueue(q, s);
	visited[s] = 1;
	enqueue(path, s);
	while(!isQueueEmpty(q)) {
		int v = front(q);
		dequeue(q);
		ATNode iter;
		for(iter = graph->adl[v]; iter != NULL; iter = iter->next) {
			if(visited[iter->v] == 0) {
				enqueue(q, iter->v);
				visited[iter->v] = 1;
				enqueue(path, iter->v);
			}
		}
	}
	destroyQueue(q);
	free(visited);
	return (List*)path;
}


void destroyGraphAdjList(TGraphL* graph) {
	// TODO: 5
	for(int i = 0; i < graph->nn; i++) {
		ATNode iter = graph->adl[i];
		while(iter != NULL) {
			ATNode garbage = iter;
			iter = iter->next;
			free(garbage);
		}
		free(iter);
	}
	free(graph->adl);
	free(graph);
}

void removeEdgeList(TGraphL* graph, int v1, int v2) {
	TNode* it = graph->adl[v1];
	TNode* prev = NULL;
	while(it != NULL && it->v != v2) {
		prev = it;
		it = it->next;
	}
	if(it == NULL) return;
	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v1] = it->next;
	free(it);
	it = graph->adl[v2];
	prev = NULL;
	while(it != NULL && it->v != v1) {
		prev = it;
		it = it->next;
	}
	if(it == NULL) 
		return;
	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v2] = it->next;
	free(it);
}

void removeNodeList(TGraphL* graph, int v){
	for(int i = 0; i < graph->nn;i++){
		removeEdgeList(graph,v,i);
	}
}
