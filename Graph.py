import networkx as nx
import time

start_time = time.clock()


G = nx.Graph()

usa = open('contiguous-usa.dat')
for line in usa:
    s1, s2 = line.strip().split()
    G.add_edge(s1, s2)
for state in G.nodes():
    if state != 'CA':
        G.node[state]['demand'] = 1
G.node['CA']['demand'] = -48
G = nx.DiGraph(G)
uniform_capacity = 16
for (s1, s2) in G.edges():
    G.edge[s1][s2]['capacity'] = uniform_capacity




def flow_with_demands(graph):

    for state in G.nodes():
        if G.node[state]['demand'] > 0:
            G.add_edge(state,'t')
            G.node['t']['demand'] = 48
            G.edge[state]['t']['capacity'] = 1
        else:
            G.add_edge('s',state)
            G.node['s']['demand'] = -48
            G.edge['s'][state]['capacity'] = 48

    G2=G.copy()
    S=0
    T=0
    for state in G.nodes():
        if G.node[state]['demand'] > 0:
            T= T + G.node[state]['demand']
        else:
            S= S + G.node[state]['demand']

    if S+T != 0:
        raise nx.NetworkXUnfeasible



    flow_value, flow_dict = nx.maximum_flow(G,'s','t')
    del flow_dict['s']
    del flow_dict['t']



    for n in flow_dict:
        m = flow_dict[n]
        if 't' in m.keys():
            del m['t']

    S=0
    T=0
    for state in G.nodes():
        if G.node[state]['demand'] > 0:
            T= T + G.node[state]['demand']
        else:
            S= S + G.node[state]['demand']

    if S+T != 0:
        raise nx.NetworkXUnfeasible

    G.remove_node('s')
    G.remove_node('t')
    return flow_dict





flow = flow_with_demands(G)

print (flow)

print (time.clock() - start_time, "seconds")

    #    G.add_edge(s1, s2)
