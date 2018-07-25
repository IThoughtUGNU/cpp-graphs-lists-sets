//
//  graph.h
//  Grafi
//
//  Created by Ruggiero Altini on 14/12/16.
//  Copyright © 2016 Ruggiero Altini. All rights reserved.
//

#ifndef graph_h
#define graph_h

#include "../Lista/linearlist.h"
#include "../Lista/Collegata/linkedlist.h"
#include "../Insieme/Lista/listset.h"

struct GraphException : public std::exception
{
    std::string s;
    GraphException(std::string ss) : s(ss) {}
    ~GraphException() throw () {}
    const char* what() const throw() { return s.c_str(); }
};


struct GraphInvalidNodeException : public GraphException
{
    //std::string s;
    GraphInvalidNodeException(std::string ss = "This node is not valid") : GraphException(ss) {}
    ~GraphInvalidNodeException() throw () {}
    const char* what() const throw() { return s.c_str(); }
};

struct GraphEdgeException : public GraphException
{
    GraphEdgeException(std::string ss = "Invalid edge"): GraphException(ss) {}
    ~GraphEdgeException() throw () {}
    const char* what() const throw() { return s.c_str(); }
};

template<class P, class N>
class GraphEdge {
public:
    N node1;
    N node2;
    P weight;
};

template<class L, class W, class N, class I, class P>
class Graph {
public:
    typedef L label;
    typedef W weight;
    typedef N node;
	typedef I iterator;
    typedef P const_iterator;

    typedef GraphEdge<weight, node> edge;

    virtual void init() = 0;
    virtual bool isEmpty() const = 0;
    virtual void insNode(node&) = 0;
    virtual node insNode(const label&) = 0;
    virtual void insEdge(const node&, const node&, const weight&) = 0;
    virtual void removeNode(const node&) = 0;
    virtual void removeEdge(const node&, const node&) = 0;
    virtual void adjacents(const node&, LinearList<node, iterator, const_iterator>&) const = 0;
    virtual void nodesList(LinearList<node, iterator, const_iterator>&) const = 0;
    virtual label readLabel(const node&) const = 0;
    virtual void writeLabel(const node&, const label&) = 0;
    virtual weight readWeight(const node&, const node&) const = 0;
    virtual void writeWeight(const node&, const node&, const weight&) = 0;

	virtual bool existsEdge(const node&, const node&) const = 0;

    virtual int nodesNumber() const = 0;
    virtual int edgesNumber() const = 0;

    virtual void print() const = 0;
    virtual ~Graph() {};
    //	virtual bool esisteNodo(Nodo) = 0;
    //	virtual bool esisteArco(Arco) = 0;
    //virtual bool existsNode(const node&) const = 0;
    template<class II, class PP>
    void DFS(LinearList<node, II, PP> &, node n) const;

    virtual void adjacents(const node& n, LinkedList<node>& list) const = 0;
protected:
private:
    template<class II, class PP>
    void DFS_recursive(LinearList<node, II, PP> &, node n, ListSet<node>& visited) const;
};


template<class L, class W, class N, class I, class P>
inline std::ostream& operator<<(std::ostream& os, const Graph<L, W,N,I, P> &g) {
    g.print();
    return os;
}

template<class L, class W, class N, class I, class P>
template<class II, class PP>
void Graph<L,W,N,I,P>::DFS(LinearList<node, II, PP> & list, node n) const {
    list.init();
    ListSet<node> visited;
    DFS_recursive(list, n, visited);
}

template<class L, class W, class N, class I, class P>
template<class II, class PP>
void Graph<L, W, N, I, P>::DFS_recursive(LinearList<node, II, PP> & list, node n, ListSet<node>& visited) const {
    visited.add(n);
    list.push_back(n);
    LinkedList<node> adjs;
    adjacents(n, adjs);
    for (auto it = adjs.begin(); !adjs.end(it); ++it) {
        if (!visited.contains(*it)) {
            DFS_recursive(list, *it, visited);
        }
    }
}

#endif
