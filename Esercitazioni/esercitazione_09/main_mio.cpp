#include <iostream>
#include <fstream>
#include <string>
#include "unidirected_graph.hpp"
#include "graph.hpp"

/* Per ottenere le immagini dei grafi con GraphViz devo tradurre i grafi in linguaggio DOT (Abstract grammar for defining Graphviz nodes, edges, graphs, subgraphs, and clusters) 
Per visualizzarli, fare 
dot -Tpng bfs.dot 		-o bfs.png
dot -Tpng dfs.dot 		-o dfs.png
dot -Tpng dfs_rec.dot 	-o dfs_rec.png
dot -Tpng dijkstra.dot 	-o dijkstra.png */

template <typename T>
void to_dot(const unidirected_graph<T>& g, const std::string& filename, const std::string& title = "") 
{
	std::ofstream file(filename);
	file << "graph G {\n";
	if (!title.empty()) file << "  label=\"" << title << "\";" << "\n labelloc=t;\n";
	for (const auto& e : g.all_edges()) {
		file << " " << e.from() << " -- " << e.to() << ";\n";
	}
	file << "}\n";
	std::cout << "File DOT scritto: " << filename << "\n";
}


int main() {
	/* Costruzione del grafo di esempio non pesato */
	unidirected_graph<int> G;
	G.add_edge(1,2); 
	G.add_edge(1,3);
	G.add_edge(1,4);
	G.add_edge(1,6);
	G.add_edge(2,4);
	G.add_edge(2,5);
	G.add_edge(2,7);
	G.add_edge(3,6);
	G.add_edge(4,6);
	G.add_edge(4,7);
	G.add_edge(5,7);
	G.add_edge(6,7);
	G.add_edge(6,8);
	G.add_edge(7,9);
	G.add_edge(8,9);
	
	unidirected_graph<std::string> G1;
    G1.add_edge("A", "B");
    G1.add_edge("A", "D");
    G1.add_edge("B", "D");
    G1.add_edge("E", "D");
    G1.add_edge("B", "C");
    G1.add_edge("C", "E");
    G1.add_edge("E", "B");
    G1.add_edge("E", "F");
	
	std::cout << " Grafo originale (albero) \n" << G << "\n\n";
	to_dot(G, "original.dot", "Grafo originale");
	//to_dot(G1, "original.dot", "Grafo originale");
	
	
	// BFS - visita in ampiezza - implementata con struttura queue, cioè con paradigma FiFo
	std::cout << " BFS (ampiezza) \n";
	fifo<int> q;
	fifo<std::string> q1;
	//auto bfsG = graph_visit(G1, std::string("A"), q1);
	auto bfsG = graph_visit(G, 1, q); 
	std::cout << bfsG << "\n";
	to_dot(bfsG, "bfs.dot", "BFS da nodo 1");
	std::cout << "\n";
	
	
	// DFS iterativa- visita in profondità - implementata con struttura stack, cioè con paradigma LiFo
	std::cout << " DFS iterativa (profondità) \n";
	lifo<int> s;
	lifo<std::string> s1;
	//auto dfsG = graph_visit(G1, std::string("A"), s1); 
	auto dfsG = graph_visit(G, 1, s); 
	std::cout << dfsG << "\n";
	to_dot(dfsG, "dfs.dot", "DFS iterativa da nodo 1");
	std::cout << "\n";
	
	
	// DFS ricorsiva
	std::cout << " DFS ricorsiva \n";
	//auto rdfsG = recursive_dfs(G1, std::string("A"));
	auto rdfsG = recursive_dfs(G, 1); 
	std::cout << rdfsG << "\n";
	to_dot(rdfsG, "dfs_rec.dot", "DFS ricorsiva da nodo 1");
	std::cout << "\n";
	
	
	// Dijkstra - cammini minimi su grafo non pesato; uso lo stesso grafo usato per BFS e DFS 
	std::cout << " Dijkstra (cammini minimi da nodo 1) \n";
	
	/*Versione con interi*/
	std::map<int, int> dist;
	std::map<int, int> pred;
		
	dijkstra (G, 1, dist, pred);
	for (const auto& d : dist) {
		if (d.second == -1)  { std::cout << "Non raggiungibile \n"; }
		else 
		{
			std::cout 	<< "Nodo: " << d.first 
						<< " Dist: " << d.second
						<< " Pred: " << pred[d.first]
						<< "\n";
		}
	}
	unidirected_graph<int> dijkstraG;
	for (const auto& p : pred) {
		int v = p.first;
		int prec = p.second;
		if (v != prec) //salto sorgente e nodi non raggiunti
		{ dijkstraG.add_edge(prec,v); }
	}
	to_dot(dijkstraG, "dijkstra.dot", "Dijkstra da nodo 1");
	std::cout << "\n";
	
	
	/* Versione con stringhe */
	/* 
	std::map<std::string, int> dist;
	std::map<std::string, std::string> pred;
		
	dijkstra(G1, std::string("A"), dist, pred);
	for (const auto& d : dist) {
		if (d.second == -1)  { std::cout << "Non raggiungibile \n"; }
		else 
		{
			std::cout 	<< "Nodo: " << d.first 
						<< " Dist: " << d.second
						<< " Pred: " << pred[d.first]
						<< "\n";
		}
	}
	unidirected_graph<std::string> dijkstraG;
	for (const auto& p : pred) {
		std::string v = p.first;
		std::string prec = p.second;
		if (v != prec) //salto sorgente e nodi non raggiunti
		{ dijkstraG.add_edge(prec,v); }
	}
	to_dot(dijkstraG, "dijkstra.dot", "Dijkstra da nodo 1");
	std::cout << "\n";
	*/ 
	
	return 0;
}