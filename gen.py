from igraph import *
import random
import sys


def Save_Graph(filename, graph):
    anchor = open(filename, 'w')
    anchor.write(str(graph.vcount()) + '\n')
    for i in graph.get_edgelist():
        anchor.write(str(i[0]) + " " + str(i[1]) + '\n')
    anchor.close()


def Set_Label(graph):
    vertices_number = graph.vcount()
    index = vertices_number - 1
    while(index >= 0):
        graph.vs[index]['label'] = str(index)
        index = index - 1


def Make_Permute_List(graph):
    lista = []
    index = 0
    for i in graph.vs:
        lista.append(index)
        index += 1
    random.shuffle(lista)
    return lista

graph1 = Graph.Erdos_Renyi(30, p=0.8, loops=True)
layout = graph1.layout("large")
Set_Label(graph1)
if(len(sys.argv) != 3):
    Save_Graph('Graph1', graph1)
    permutation = Make_Permute_List(graph1)
    graph1 = graph1.permute_vertices(permutation)
    Save_Graph('Graph2', graph1)
else:
    Save_Graph(sys.argv[1], graph1)
    permutation = Make_Permute_List(graph1)
    graph1 = graph1.permute_vertices(permutation)
    Save_Graph(sys.argv[2], graph1)
