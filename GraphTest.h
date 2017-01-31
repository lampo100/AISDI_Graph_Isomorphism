//
// Created by kacper on 29.12.16.
//

#ifndef GRAPHISOMORPHISM_GRAPHTEST_H
#define GRAPHISOMORPHISM_GRAPHTEST_H
#include "Graph.h"
class GraphTest{
public:
    bool test_initialization(string filename, size_t nodes, size_t edges, size_t loops, bool print_graph){
        Graph test(filename);
        bool correct = true;
        if(!((test.get_nodes() == nodes)&&(test.get_edges() == edges)&&(test.get_loops() == loops)))
            correct = false;
        if(print_graph) test.print_graph();
        return correct;
    }
    bool test_invariants(string filename1, string filename2){
        Graph first_graph(filename1);
        Graph second_graph(filename2);
        bool flag = first_graph.check_invariants(second_graph);
        return flag;
    }
    bool test_isomorphism(string filename1, string filename2) {
        Graph first_graph(filename1);
        Graph second_graph(filename2);
        bool flag = first_graph.test_graph_isomorphism(second_graph);
        return flag;
    }

};
#endif //GRAPHISOMORPHISM_GRAPHTEST_H
