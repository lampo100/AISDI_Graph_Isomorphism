from igraph import *
from PIL import Image
import sys
import random


def random_color():
    levels = range(32, 256, 32)
    return tuple(random.choice(levels) for _ in range(3))


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


def Color_Graphs(filename, graph1, graph2):
    mapping_list = []
    with open(filename) as f:
        for line in f:
            mapping_list.append(line.split())
    color_dict1 = {}
    color_dict2 = {}
    for i in mapping_list:
        color = "rgb"
        color += str(random_color())
        color_dict1[i[0]] = color
        color_dict2[i[1]] = color
    graph1.vs["color"] = [color_dict1[number] for number in graph1.vs['label']]
    graph2.vs["color"] = [color_dict2[number] for number in graph2.vs['label']]


def Print_Both(filename1, filename2):
    g1 = Graph(0)
    g2 = Graph(0)
    Make_Graph(filename1, g1)
    Make_Graph(filename2, g2)
    layout1 = g1.layout("kk")
    layout2 = g2.layout("kk")
    Color_Graphs('Mapping', g1, g2)
    img1 = filename1 + '.png'
    img2 = filename2 + '.png'
    plot(g1, img1, layout=layout1, bbox=(300, 300))
    plot(g2, img2, layout=layout2, bbox=(300, 300))


Print_Both(sys.argv[1], sys.argv[2])
img1name = sys.argv[1] + '.png'
img2name = sys.argv[2] + '.png'
img1 = Image.open(img1name)
img1.show()
img2 = Image.open(img2name)
img2.show()
img1.close()
img2.close()
