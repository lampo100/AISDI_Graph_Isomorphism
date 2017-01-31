#include "Graph.h"
#include "GraphTest.h"
#include <unistd.h>

void stupid_test(int);

void smart_test(string in1, string in2);

int main(int argc, char *argv[]) {
    smart_test(argv[1], argv[2]);
}

void smart_test(string in1, string in2) {
    int pid = fork();
    if(pid != 0){
        Graph g1(in1);
        Graph g2(in2);
        g1.test_graph_isomorphism(g2);
    }
    if (pid == 0) {
        //sleep(4);
        execl("/usr/bin/python", "python", "graph.py", in1.c_str(), in2.c_str(), (char *) 0);
        return;
    }
}

void stupid_test(int choice) {
    int do_stupid_tests = choice;
    if (do_stupid_tests == 1) {
        {//Check initialization
            GraphTest test;
            bool test_flag;

            test_flag = test.test_initialization("GraphInitializationTest/GraphTest1.txt", 0, 0, 0,
                                                 false);//EMPTY GRAPH
            cout << "Initialization test 1: " << test_flag << "\n";

            test_flag = test.test_initialization("GraphInitializationTest/GraphTest2.txt", 3, 0, 0,
                                                 false);//3 VERTICES NO EDGES
            cout << "Initialization test 2: " << test_flag << "\n";

            test_flag = test.test_initialization("GraphInitializationTest/GraphTest3.txt", 5, 5, 5,
                                                 false);// 5 VERTICES ALL LOOPS
            cout << "Initialization test 3: " << test_flag << "\n";

            test_flag = test.test_initialization("GraphInitializationTest/GraphTest4.txt", 5, 7, 4,
                                                 false);// 5 VERTICES, SOME LOOPS
            cout << "Initialization test 4: " << test_flag << "\n";
        }
        {//Check invariants checking
            GraphTest test;
            bool test_flag;
            for (int i = 0, j = 1; i < 6; i++, j += 2) {
                string in1 = "GraphInvariantsTests/GraphInvariantsCheck";
                string in2 = "GraphInvariantsTests/GraphInvariantsCheck";
                string x(to_string(j));
                in1 += x;
                x.clear();
                x = to_string(j + 1);
                in2 += x;
                test_flag = test.test_invariants(in1, in2);
                cout << "Invariants test " << i + 1 << ": " << test_flag << "\n";
                if (!test_flag) {
                    in1.erase(in1.begin(), in1.begin() + 21);
                    in2.erase(in2.begin(), in2.begin() + 21);
                    cout << "\tFiles: " << in1 << " || " << in2 << endl;
                }
            }
        }
        {//CHECK EASY ISOMORPHISM
            GraphTest test;
            bool test_flag;
            for (int i = 0, j = 1; i < 3; i++, j += 2) {
                string in1 = "GraphEasyIsomorphismCheck/GraphEasyIsomorphismCheck";
                string in2 = "GraphEasyIsomorphismCheck/GraphEasyIsomorphismCheck";
                string x(to_string(j));
                in1 += x;
                x.clear();
                x = to_string(j + 1);
                in2 += x;
                test_flag = test.test_isomorphism(in1, in2);
                cout << "Easy isomorphism test " << i + 1 << ": " << test_flag << "\n";
                if (!test_flag) {
                    in1.erase(in1.begin(), in1.begin() + 21);
                    in2.erase(in2.begin(), in2.begin() + 21);
                    cout << "\tFiles: " << in1 << " || " << in2 << endl;
                }
            }
        }
        {//HARD ISOMORPHISM CHECK
            GraphTest test;
            bool test_flag;
            for (int i = 0, j = 1; i < 4; i++, j += 2) {
                string in1 = "GraphHardIsomorphismCheck/GraphHardIsomorphismCheck";
                string in2 = "GraphHardIsomorphismCheck/GraphHardIsomorphismCheck";
                string x(to_string(j));
                in1 += x;
                x.clear();
                x = to_string(j + 1);
                in2 += x;
                test_flag = test.test_isomorphism(in1, in2);
                cout << "Hard isomorphism test " << i + 1 << ": " << test_flag << "\n";
                if (!test_flag) {
                    in1.erase(in1.begin(), in1.begin() + 21);
                    in2.erase(in2.begin(), in2.begin() + 21);
                    cout << "\tFiles: " << in1 << " || " << in2 << endl;
                }
            }
        }
    }

}