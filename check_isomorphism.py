from igraph import *
from PIL import Image
import sys


def Make_Graph(filename, g):
    file_anchor = open(filename)
    char = file_anchor.readline()
    g.add_vertices(int(char))
    vertices_number = int(char)

    index = 1
    with open(filename) as f:
        for line in f:
            if(index == 1):
                index = index - 1
            else:
                vertex_list = line.split()
                first = int(vertex_list[0])
                second = int(vertex_list[1])
                g.add_edges([(first, second)])
    index = vertices_number - 1
    while(index >= 0):
        g.vs[index]['label'] = str(index)
        g.vs[index]['degree'] = g.degree(index)
        index = index - 1


def Check_Isomorphism(g1, g2):
    if(g1.isomorphic(g2)):
        print("Python mowi ze grafy sa izomorficzne.")
    else:
        print("Python mowi ze grafy nie sa izomorficzne.")

g1 = Graph(0)
g2 = Graph(0)
Make_Graph(sys.argv[1], g1)
Make_Graph(sys.argv[2], g2)
Check_Isomorphism(g1, g2)
