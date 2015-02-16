/* graph structure and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

/* TODO: complete the graph interface */

#ifndef GRAPH_H
#define GRAPH_H

struct graph {};
struct edge { int u, int v};

void graph_init(struct graph *graph, void (* destroy)(void *));
void graph_destroy(struct graph *graph);
int graph_vertex_insert(struct graph *graph, const void *object);
int graph_edge_insert(struct graph *graph, const void *object1, const void *object);
int graph_vertex_remove(struct graph *graph, const void *object);
int graph_edge_remove(struct graph *graph, const void *object);

/* a number of vertices in the graph */
int graph_vertices(const struct graph *graph);

/* a number of egdes in the graph */
int graph_edges(const struct graph *graph);

#endif

