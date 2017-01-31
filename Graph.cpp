//
// Created by kacper on 29.12.16.
//
#include "Graph.h"

list<Vertex *> Vertex::get_adj() {
    std::list<Vertex *> result(adj);
    return result;
}

Graph::Graph(string filename) : no_edges(0) {
    ifstream anchor;
    char string_input[1024];
    int input, input2;

    anchor.open(filename);
    anchor.getline(string_input, 1024, '\n');
    input = stoi(string_input);
    no_nodes = static_cast<size_t>(input);
    no_loops = 0;
    graph.resize(no_nodes);

    for (anchor.getline(string_input, 1024, ' ');
         !anchor.eof();
         anchor.getline(string_input, 1024, ' ')) {
        input = stoi(string_input);
        anchor.getline(string_input, 1024, '\n');
        input2 = stoi(string_input);

        if (graph[input].exists()) {//Pierwszy wierzchołek już istnieje
            graph[input].set_degree(graph[input].get_degree() + 1);
            if (input2 == input) {
                graph[input].set_loop(true);
                ++no_edges;
                ++no_loops;
                continue;
            }
            if (graph[input2].exists()) {//drugi wierzchołek już istnieje
                graph[input2].set_degree(graph[input2].get_degree() + 1);
                graph[input].add_adjectant(&graph[input2]);
                graph[input2].add_adjectant(&graph[input]);
            } else {//drugi wierzchołek jeszcze nie istnieje
                Vertex new_vertex(false, 1, input2, {&graph[input]});
                graph[input2] = new_vertex;
                graph[input].add_adjectant(&graph[input2]);
            }
        } else {//Pierwszy wierzchołek jeszcze nie istnieje
            Vertex new_vertex(false, 1, input);
            graph[input] = new_vertex;
            if (input2 == input) {
                graph[input].set_loop(true);
                ++no_edges;
                ++no_loops;
                continue;
            }
            if (graph[input2].exists()) {//drugi wierzchołek już istnieje
                graph[input2].set_degree(graph[input2].get_degree() + 1);
                graph[input].add_adjectant(&graph[input2]);
                graph[input2].add_adjectant(&graph[input]);
            } else {//drugi wierzchołek jeszcze nie istnieje
                Vertex new_vertex(false, 1, input2, {&graph[input]});
                graph[input2] = new_vertex;
                graph[input].add_adjectant(&graph[input2]);
            }
        }
        ++no_edges;
    }
    anchor.close();
    for (int i = 0; i < no_nodes; ++i)
        if (!graph[i].exists()) {
            graph[i].set_index(i);
            graph[i].set_degree(0);
        }
}

bool Graph::check_degree_sequence(const Graph &target) const {
    vector<size_t> this_degree_sequence;
    vector<size_t> target_degree_sequence;
    this_degree_sequence.resize(this->get_nodes());
    target_degree_sequence.resize(target.get_nodes());
    size_t index = 0;
    for (auto i: graph) {
        this_degree_sequence[index] = i.get_degree();
        ++index;
    }
    index = 0;
    for (auto i: target.graph) {
        target_degree_sequence[index] = i.get_degree();
        ++index;
    }/* TODO delete this piece
    cout<<"\nTATATATATATAT\n";
    for(auto x: this_degree_sequence)
        cout<<x<<" ";
    cout<<"\nTATATATATATAT\n";
    for(auto x: target_degree_sequence)
        cout<<x<<" ";*/
    sort(this_degree_sequence.begin(), this_degree_sequence.end());
    sort(target_degree_sequence.begin(), target_degree_sequence.end());

    for (index = 0; index < this_degree_sequence.size(); ++index)
        if (this_degree_sequence[index] != target_degree_sequence[index])
            return false;
    return true;

}

void Graph::print_graph() const {
    cout << "INDEX | DEG | LOOP | ADJACENT\n";
    for (auto i: graph) {
        cout << "  " << i.get_index() << "      " << i.get_degree() << "      " << i.get_loop() << "    ";
        for (auto x: i.get_adj()) {
            cout << x->get_index() << "  ";
        }
        cout << endl;
    }
}

void Graph::print_candidates() const {
    for (auto i: graph) {
        cout << "C(" << i.get_index() << "): ";
        for (auto j: i.candidates)
            cout << j->get_index() << " ";
        cout << endl;
    }

}

bool Graph::test_graph_isomorphism(const Graph target) {
    /*First check if graphs have the same invariants, if not then they cannot be isomorphic, is yes then check isomorphism with VF2 algorithm*/
    if (!check_invariants(target)) {
        cout << "Nieizomorficzne\n";
        return false;
    }
    if (no_nodes == 0) {

        cout << "Izomorficzne\n";
        return true;
    }
    if (no_edges == 0) {
        cout << "Izomorficzne\n";
        for (int i = 0; i < graph.size(); ++i)
            cout << i << " --> " << i << endl;
        return true;
    }
    if ((no_edges == no_nodes) && (no_loops == no_nodes)) {
        cout << "Izomorficzne\n";
        for (int i = 0; i < graph.size(); ++i)
            cout << i << " --> " << i << endl;
        return true;
    }
    /*
     * VF2 algorithm is described in this paper http://www.vldb.org/pvldb/vol6/p133-han.pdf
     * Basically it is performed like that:
     * 2. NEXTVERTEX: We take random vertex from set of vertices connected to already mapped vertices from the first graph
     *               (if there isn't one but we still haven't mapped all vertices then it means that the graph is disjoint.
     *                In that case take random vertex that isn't already mapped)
     * 3. GETCANDIDATES: Candidates for the mapping are vertices of the same degree(same group)
     * 4. REFINECANDIDATES:         We prune some vertices from set of candidates based on 4 rules:
     *      -RULE1(not connected):  We remove any candidates that are not connected to already matched vertices in second graph
     *      -RULE2:                 Let A be a set of not-yet-matched vertices that are connected to already
     *                              mapped vertices of the first graph, and B be a set not-yet-matched vertices that are
     *                              connected to already mapped vertices of the second graph, and adj(u) set of vertices
     *                              connected to the vertex u. We remove any candidate v that doesn't fulfil requirement
     *                              |A ∩ adj(u)| > |B ∩ adj(v)|
     *      -RULE3:                 Let C be a set of already matched vertices from the first graph, and D be a set of already
     *                              matched vertices from the second graph.
     *                              We remove any candidate that doesn't fulfil requirement
     *                              |adj(u)\A\C| > |adj(v)\B\D|
     *      -RULE4:                 We remove any vertex that has different loop flag
     * */

    list <pair<int, int>> mapping;//Mapping of isomorphism from graph1 to graph2

    for (auto i: graph) {
        for (auto j: target.graph)
            if ((j.get_degree() == i.get_degree()) && (j.get_loop() == i.get_loop())) {
                graph[i.get_index()].candidates.push_back(&(target.graph[j.get_index()]));
                //              graph[i.get_index()].candidates_index.push_back(j.get_index());
            }
        if (graph[i.get_index()].candidates.empty()) {
            cout << "Nieizomorficzne";
            return false;
        }
    }

    vector<int> A, B, C, D;
    A.reserve(no_nodes);
    B.reserve(no_nodes);
    C.reserve(no_nodes);
    D.reserve(no_nodes);


    bool are_isomorphic = search_mapping(*this, target, mapping, A, B, C, D);
    if(!are_isomorphic){
        cout<<"Nieizomorficzne\n";
    }
    return are_isomorphic;
}

bool Graph::search_mapping(Graph first_graph, Graph second_graph,
                           list <pair<int, int>> mapping, vector<int> Mq,
                           vector<int> Mg, vector<int> Cq, vector<int> Cg) {
/*
    cout<<"|||||INFORMACJE|||||\n"
        <<"Cg = {";
    for(auto i: Cg)
        cout<<i<<";";

    cout<<"}\nCq = {";
    for(auto i: Cq)
        cout<<i<<";";
    cout<<"}\nMg = {";
    for(auto i: Mg)
        cout<<i<<";";
    cout<<"}\nMq = {";
    for(auto i: Mq)
        cout<<i<<";";
    cout<<"}\n";
    print_mapping(mapping);
    cout<<"||||||||||||||||||||\n\n";
*/

    /*
     * Mapping - mapowanie wierzchołków
     * Mq - zmapowane wierzchołki 1 grafu
     * Mg - zmapowane wierzchołki 2 grafu
     * Cq - niezmapowane wierzchołki 1 grafu przyległe do Mq
     * Cg - niezmapowane wierzchołki 2 grafu przyległe do Mg
     */
    // Implementacja NEXTQUERY:
    if (mapping.size() == first_graph.no_nodes) {
        cout << "Izomorficzne\n";
        print_mapping(mapping);
        save_mapping(mapping);
        return true;
    }
    int u = -1;
    if (mapping.empty()) {//Jeżeli jest to pierwsze wywołanie search_mapping to mapowanie jest pusty
        u = first_graph.graph[0].get_index();//i w takim wypadku wybieramy pierwszy wierzchołek
    } else {
        if (Cq.empty()) {//Jeżeli zbiór niezmapowanych wierzchołków jest pusty to szukamy wierzhołka odłączonego od już zmapowanych wierzchołków
            bool is_already_mapped = false;
            for (auto i: graph) {
                u = graph[i.get_index()].get_index();
                is_already_mapped = is_mapped(u, mapping, 1);
                if (!is_already_mapped) break;
            }
        } else {
            u = Cq.back();
            Cq.pop_back();
        }
    }
    if (u == -1)
        return false;


    vector<int> Cr; // obecna lista kandydatów
    for (auto i: first_graph.graph[u].candidates)
        Cr.push_back(i->get_index());
    //REFINECANDIDATES:
    refine_candidates(first_graph, second_graph, mapping, Mq, Mg, Cq, Cg, Cr, u);

    for (auto i: first_graph.graph[u].adj)
        if (!is_mapped(i->get_index(), mapping, 1)) {
            bool flag = false;
            for (auto x: Cq)
                if (x == i->get_index()) flag = true;
            if (!flag)
                Cq.push_back(i->get_index());
        }
    /*
    vector<int> Cr; // obecna lista kandydatów
    for (auto i: first_graph.graph[u].candidates)
        Cr.push_back(i->get_index());
    //IMPLEMENTACJA REFINECANDIDATES:
   // refine_candidates(first_graph, second_graph, mapping, Mq, Mg, Cq, Cg, Cr, u);*/ // TO PRZENOSZĘ NA GÓRĘ, YOLO


    Mq.push_back(u);
    for(auto i: Cr){
        if(!is_mapped(i, mapping, 2))
            if(is_joinable(first_graph, second_graph, mapping, Mq, Mg, u, i)){
                mapping.push_back(make_pair(u, i));
                Mg.push_back(i);
                //Uaktualnianie Cg
                vector<int> Cg_before(Cg);
                for (auto j: second_graph.graph[i].adj)// HOW DID IT WORK BEFORE WITH graph[u]!!!!???
                    if (!is_mapped(j->get_index(), mapping, 2)) {
                        bool flag = false;
                        for (auto x: Cg)
                            if (x == j->get_index()) flag = true;
                        if (!flag)
                            Cg.push_back(j->get_index());
                    }

                for (auto i: Cg)
                    if (is_mapped(i, mapping, 2))
                        for (auto x = Cg.begin(); x != Cg.end(); x++)
                            if (*x == i) {
                                Cg.erase(x);
                                break;
                            }

                if(search_mapping(first_graph, second_graph, mapping, Mq, Mg, Cq, Cg))
                    return true;
                mapping.pop_back();
                Mg.pop_back();
                Cg = Cg_before;
        }
    }
    return false;

}

bool Graph::is_mapped(int u, list <pair<int, int>> mapping, int which_graph) {
    for (auto i: mapping) {
        if (which_graph == 1)
            if (u == i.first) return true;
        if (which_graph == 2)
            if (u == i.second) return true;
    }
    return false;
}

void Graph::print_mapping(const list <pair<int, int>> mapping) {
    for (auto i: mapping)
        cout << i.first << " --> " << i.second << endl;
}

bool Graph::check_invariants(const Graph &target) const {
    if (no_nodes != target.get_nodes()) return false;
    if (no_edges != target.get_edges()) return false;
    if (no_loops != target.get_loops()) return false;
    if (!check_degree_sequence(target)) return false;
    return true;
}

void Graph::refine_candidates(Graph &first_graph, Graph &second_graph,
                              list <pair<int, int>> &mapping, vector<int> &Mq,
                              vector<int> &Mg, vector<int> &Cq, vector<int> &Cg, vector<int> &Cr, int u)
{
    if (!Mg.empty()) {
        //-RULE1(not connected):  Usuwamy kandydatów którzy nie są połączeni z obecnie zmapowanymi wierzchołkami 2 grafu(nie należą do Cg)(tylko jeżeli
        // obecnie mapowany wierzchołek jest połączony z którymś ze zmapowanych wierzchołków.
        bool is_u_connected = false;
        for(auto i: Mq){
            for(auto x: first_graph.graph[i].adj)
                if(x->get_index() == u){
                    is_u_connected = true;
                    break;
                }
            if(is_u_connected == true)
                break;
        }
        if(is_u_connected){
            for (auto i: Cr) {
                bool is_adj = false;
                for (auto x: Cg)
                    if (i == x)
                        is_adj = true;
                if (!is_adj)
                    for (auto z = Cr.begin(); z != Cr.end(); z++)
                        if (*z == i){
                            Cr.erase(z);
                            break;
                        }
            }
        }/*
        //-RULE2 |Cq ∩ adj(u)| > |Cg ∩ adj(v)|
        int pow1 = 0;
        for (auto i: Cq) {
            for (auto x: first_graph.graph[u].adj)
                if (x->get_index() == i) pow1++;
        }
        cout<<"\nWierzcholek ["<<u<<"] pow = "<<pow1<<"\n";

        for (auto i: Cr) {
            int pow2 = 0;
            for (auto x: Cg) {
                for (auto z: second_graph.graph[i].adj)
                    if (z->get_index() == x) pow2++;
            }
            cout<<"\nWierzcholek mapowany ["<<i<<"] pow = "<<pow2<<"\n";
            if (pow1 <= pow2) {
                for (auto z = Cr.begin(); z != Cr.end(); z++)
                    if (*z == i) {
                        Cr.erase(z);
                        break;
                    }
            }
        }*/
    }
}

bool Graph::is_joinable(Graph &first_graph, Graph &second_graph,
                        list <pair<int, int>> &mapping, vector<int> &Mq,
                        vector<int> &Mg, int u, int v){
    vector<int> to_check; // które wierzchołki w drugim grafie powinny mieć połączenie z v
    for(auto i: Mq){
        for(auto x: first_graph.graph[u].adj)
            if(x->get_index() == i){
                for(auto z: mapping)
                    if(z.first == i){
                        to_check.push_back(z.second);
                        break;
                    }
            }
    }
//    cout<<"Mapujemy "<<u<<" do "<<v<<"; Należy sprawdzić: \n";
//    for(auto i: to_check)
//        cout<<i<<endl;

    for(auto i: to_check){
        for(auto x: second_graph.graph[v].adj){
            if(x->get_index() == i) {
                to_check.pop_back();
                break;
            }
        }
    }
    return to_check.empty();
}

void Graph::save_mapping(const list<pair<int, int>> mapping){
    ofstream file_anchor("Mapping");
    string input("");
    for(auto i: mapping){
        input+= to_string(i.first);
        input+= " ";
        input+= to_string(i.second);
        input+="\n";
    }
    file_anchor.write(input.c_str(), input.size());
    file_anchor.close();
}