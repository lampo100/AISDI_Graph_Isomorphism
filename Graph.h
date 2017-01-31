//
// Created by kacper on 29.12.16.
//

#ifndef GRAPHISOMORPHISM_GRAPH_H
#define GRAPHISOMORPHISM_GRAPH_H
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <map>
using namespace std;

class Vertex{
public:
    friend class Graph;
    Vertex():loop(false),degree(0),index(-1){}

    Vertex(bool is_loop, size_t dg, int idx, initializer_list<Vertex *> il)
            : loop(is_loop), degree(dg), index(idx), adj(il){}
    Vertex(bool is_loop, size_t dg, int idx)
            : loop(is_loop), degree(dg), index(idx){}
    Vertex(const Vertex &cpy){
        loop = cpy.get_loop();
        degree = cpy.get_degree();
        index = cpy.get_index();
        adj = cpy.adj;
        candidates = cpy.candidates;
//        candidates_index = cpy.candidates_index;
    }
    bool exists()const{return index!=-1;}
    size_t get_degree()const{return degree;}
    int get_index()const{return index;}
    bool get_loop()const{return loop;}
    list<Vertex *> get_adj();
    void add_adjectant(Vertex *na){adj.push_back(na);}
    void set_loop(bool l){loop = l;}
    void set_degree(size_t d){degree = d;}
    void set_index(int i){index = i;}

    void operator =(Vertex &target){
        loop = target.loop;
        degree = target.degree;
        index = target.index;
        adj = target.adj;
    }

protected:
    bool loop;
    size_t degree;
    int index;
    list<Vertex *> adj;
    list<const Vertex *> candidates;
 //   list<int> candidates_index;

};
class Graph{
public:
    Graph():no_nodes(0),no_edges(0), no_loops(0){};
    Graph(string filename);

    bool check_degree_sequence(const Graph &target)const;
    size_t get_nodes()const {return no_nodes;}
    size_t get_edges()const {return no_edges;}
    size_t get_loops()const {return no_loops;}


    bool test_graph_isomorphism(const Graph target);
    bool check_invariants(const Graph &target)const ;
    void print_graph()const;
    void print_candidates()const;

protected:
    bool search_mapping(Graph first_graph, Graph second_graph,
                        list<pair<int, int>> mapping, vector<int> Mq,
                        vector<int> Mg, vector<int> Cq, vector<int> Cg);
    void refine_candidates(Graph &first_graph, Graph &second_graph,
                           list<pair<int, int>> &mapping, vector<int> &Mq,
                           vector<int> &Mg, vector<int> &Cq, vector<int> &Cg, vector<int> &Cr, int u);
    bool is_joinable(Graph &first_graph, Graph &second_graph, list<pair<int, int>> &mapping, vector<int> &Mq,
                     vector<int> &Mg, int u, int v);
    bool is_mapped(int, list<pair<int, int>>, int);
    void print_mapping(const list<pair<int, int>>);
    void save_mapping(const list<pair<int, int>>);
    vector<Vertex> graph;
    //Graph's invariants
    size_t no_nodes;
    size_t no_edges;
    size_t no_loops;
};

#endif //GRAPHISOMORPHISM_GRAPH_H
