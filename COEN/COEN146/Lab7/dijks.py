# By Behnam Dezfoulu, CSEN, SCU
#
# This program implements dijkstra link state algorithm


import sys
import heapq            # heap
import networkx as nx   # for graphical representation of the network
import matplotlib.pyplot as plt


# --------------------------------------------------
# --------------------------------------------------
# --------------------------------------------------
# defines a vertex of adjacency graph
class Vertex:
    def __init__(self, node):
        self.id = node # id is node label (e.g., 'w')
        self.adjacent = {} # a dictionary holding neighboring vertex labels and weights (e.g., {'u': 6, 'v': 7})
        
        # Set distance to infinity for all nodes
        self.distance = sys.maxsize
        
        # Mark all nodes unvisited
        self.visited = False
        
        # Predecessor
        self.previous = None
    
    
    def add_neighbor(self, neighbor, weight=0):
        self.adjacent[neighbor] = weight
    
    def get_connections(self):
        return self.adjacent.keys()
    
    def get_id(self):
        return self.id # id is node label (e.g., 'w')
    
    def get_weight(self, neighbor):
        return self.adjacent[neighbor]
    
    # sets distance from source node
    def set_distance(self, dist):
        self.distance = dist

    def get_distance(self):
        return self.distance
    
    # the previous node on the shortest path to the source node
    def set_previous(self, prev):
        self.previous = prev
    
    def set_visited(self):
        self.visited = True
        
    def __str__(self):
        return str(self.id) + ' adjacent: ' + str([x.id for x in self.adjacent])



# --------------------------------------------------
# --------------------------------------------------
# --------------------------------------------------
# defines a a weighted graph
class Graph:
    def __init__(self):
        self.vert_dict = {} #this dictionary keeps node labels and objects e.g., {'u': object_u, 'v': object_v}
        self.num_vertices = 0
        self.netx = nx.Graph() # for graph display purposes
    
    
    #define iterator
    def __iter__(self):
        return iter(self.vert_dict.values())

    
    def add_vertex(self, node):
        self.num_vertices = self.num_vertices + 1
        new_vertex = Vertex(node) # create a new vertex with id = node lable
        # this adds new_vertex to key 'node'
        # for example, we will have {'u': object_u, 'v': object_v}
        self.vert_dict[node] = new_vertex
        return new_vertex
    
    
    def get_vertex(self, n):
        return self.vert_dict[n]
    
    def add_edge(self, frm, to, cost = 0):
        if frm not in self.vert_dict:
            self.add_vertex(frm)
        if to not in self.vert_dict:
            self.add_vertex(to)

        self.vert_dict[frm].add_neighbor(self.vert_dict[to], cost)
        self.vert_dict[to].add_neighbor(self.vert_dict[frm], cost)

        self.netx.add_edge(frm, to, weight=cost)



    # returns keys (e.g., ['u', 'w', 'x']) (note: values are vertex objects)
    def get_vertices(self):
        return self.vert_dict.keys()

    def get_netx(self):
        return self.netx



# --------------------------------------------------
# --------------------------------------------------
# --------------------------------------------------
# Computes the shortest path from 'start' to other vertices in the graph
# note: the Graph object is changed accordingly
def dijkstra(aGraph, start):
    print ("Dijkstra algorithm running...")
    
    # Set the distance for the 'start to start' node to zero
    start.set_distance(0)
    
    # Put tuple pair into the priority queue
    # note: we add id(v) so that if the distance are equal the object id would break the tie
    unvisited_queue = [(v.get_distance(), id(v), v) for v in aGraph]
    heapq.heapify(unvisited_queue)
    
    while len(unvisited_queue):
        
        print ('\n')

        # Pops a vertex with the smallest distance (this is the 'current' node)
        uv = heapq.heappop(unvisited_queue)
        current = uv[2] # remember: tuple structure is (v.get_distance(), id(v), v)
        current.set_visited()
        
        #for next in v.adjacent:
        for next in current.adjacent:
            
            # if visited, skip
            if next.visited:
                continue

            # distance from source to current + weight of link between current and next
            new_dist = current.get_distance() + current.get_weight(next)
            prev_dist = next.get_distance()
            
            # if we have a better path to reach 'next' from 'current'
            if new_dist < prev_dist:
                next.set_distance(new_dist)
                next.set_previous(current)

                print ('updated : current = %s next = %s prev_dist = %s new_dist = %s' \
                    %(current.get_id(), next.get_id(), prev_dist, new_dist))
            else:
                print ('not updated : current = %s next = %s prev_dist = %s new_dist = %s' \
                    %(current.get_id(), next.get_id(), prev_dist, new_dist))

        # Rebuild heap
        # 1. Pop every item
        while len(unvisited_queue):
            heapq.heappop(unvisited_queue)

        # 2. Put all vertices not visited into the queue
        unvisited_queue = [(v.get_distance(), id(v), v) for v in aGraph if not v.visited]
        heapq.heapify(unvisited_queue)


# adds the shortest path from v to source node (assigned by dijkstra() function) to list 'path'
def shortest(v, path, SPT_edges):
    if v.previous:
        path.append(v.previous.get_id()) # get_id() returns node label (e.g., 'w')
        SPT_edges.append(tuple([v.get_id(), v.previous.get_id()]));
        shortest(v.previous, path, SPT_edges)
        return



# --------------------------------------------------
# --------------------------------------------------
# --------------------------------------------------
# main function
if __name__ == '__main__':
    
    g = Graph()
    
    g.add_edge('u', 'v', 2)
    g.add_edge('u', 'x', 1)
    g.add_edge('u', 'w', 5)
    g.add_edge('x', 'v', 2)
    g.add_edge('x', 'w', 3)
    g.add_edge('x', 'y', 1)
    g.add_edge('y', 'w', 1)
    g.add_edge('y', 'z', 2)
    g.add_edge('z', 'w', 5)
    g.add_edge('v', 'w', 3)
    
    
    print ('Get vertices:')
    print (g.get_vertices())
    
    print ('Graph data:')
    for v in g:
        for w in v.get_connections():
            vid = v.get_id()
            wid = w.get_id()
            print ('( %s , %s, %3d)'  % ( vid, wid, v.get_weight(w)))


    source_node = 'u'
    # find the best path from 'u' to other nodes
    dijkstra(g, g.get_vertex(source_node))


    SPT_edges = [] # shortest path tree list
    # compute shortest path from source node to all other nodes
    for target_node in g.get_vertices():
        # get the target node object
        target = g.get_vertex(target_node)

        path = {}
        # add node id to the path list
        path[target_node] = [target.get_id()]

        shortest(target, path[target_node], SPT_edges)
        print ('\nShortest path from %s to %s' %(source_node, target_node))
        print ('The shortest path : %s\n' %(path[target_node][::-1]))



    # edges of shortest path tree
    print ('Edges of shortest path tree:\n')
    SPT_edges = set(SPT_edges) # remove duplicate edges
    print (SPT_edges)

    

    G = g.get_netx();

    print("Nodes of graph: ")
    print(G.nodes())
    print("Edges of graph: ")
    print(G.edges())
    
    weights = [G[u][v]["weight"] for u,v in G.edges()]

    labels = nx.get_edge_attributes(G, "weight")
    pos = nx.spring_layout(G)
    
    nx.draw(G, pos, edges=G.edges(), width=weights)
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels, edges=G.edges(), weight=weights)
    nx.draw_networkx_nodes(G, pos, node_size = 500)
    nx.draw_networkx_labels(G, pos, font_size = 10)

    nx.draw_networkx_edges(G, pos, edgelist=SPT_edges, edge_color = "red")

    plt.show()
