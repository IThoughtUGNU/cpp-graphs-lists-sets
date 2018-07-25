//
//  vectorgraph.h
//  Grafi
//
//  Created by Ruggiero Altini on 14/12/16.
//  Copyright © 2016 Ruggiero Altini. All rights reserved.
//
//  C++11 compliant

//#pragma once
#ifndef vectorgraph_h
#define vectorgraph_h

#include "../../RogeCode-library/rogecodelibrary.h"
#include "../graph.h"
#include "../../Lista/Vettore/arraylist.h"
#include <iostream>
#include <string>
//using rogecode::constants;

template<class L, class W>
class VectorGraph;

template<class L, class W>
class VectorGraphNode;

//template<class L, class W>
//inline std::ostream& operator<<(std::ostream& os, const VectorGraphNode<L, W> &n);

template<class L, class W>
class VectorGraphNode {
    friend class VectorGraph<L, W>;
    //friend std::ostream& operator<<(std::ostream& os, const VectorGraphNode<L, W> &n);
public:
    VectorGraphNode(const VectorGraphNode<L,W>& other): n(other.n) {  }

    VectorGraphNode() : n(-1) {}


    VectorGraphNode<L,W>& operator=(const VectorGraphNode<L, W>& right) { if (this != &right) n = right.n; return *this; }
    bool operator==(const VectorGraphNode<L, W>& right) const { return n == right.n; }
    bool operator!=(const VectorGraphNode<L, W>& right) const { return n != right.n; }

    void print(std::ostream& os) const { os << "(id:" << n << ")"; }
private:
    inline VectorGraphNode(int _id) :n(_id) { }

    int n;
    //label _label;
};

template<class L, class W>
std::ostream& operator<<(std::ostream& os, const VectorGraphNode<L,W> &n) {
    n.print(os);
    return os;
}

template<class L, class W>
class VectorGraph : public Graph<L, W, VectorGraphNode<L, W>, typename ArrayList<VectorGraphNode<L, W> >::iterator, typename ArrayList<VectorGraphNode<L, W> >::position > {
public:
    typedef typename Graph<L, W, VectorGraphNode<L, W>, typename ArrayList<VectorGraphNode<L, W> >::iterator, typename ArrayList<VectorGraphNode<L, W> >::position >::const_iterator const_iterator;
    typedef typename Graph<L, W, VectorGraphNode<L, W>, typename ArrayList<VectorGraphNode<L, W> >::iterator, typename ArrayList<VectorGraphNode<L, W> >::position >::iterator iterator;
    typedef typename Graph<L, W, VectorGraphNode<L, W>, typename ArrayList<VectorGraphNode<L, W> >::iterator, typename ArrayList<VectorGraphNode<L, W> >::position >::label label;
    typedef typename Graph<L, W, VectorGraphNode<L, W>, typename ArrayList<VectorGraphNode<L, W> >::iterator, typename ArrayList<VectorGraphNode<L, W> >::position >::weight weight;
    typedef typename Graph<L, W, VectorGraphNode<L, W>, typename ArrayList<VectorGraphNode<L, W> >::iterator, typename ArrayList<VectorGraphNode<L, W> >::position >::node node;
    //typedef typename Graph<L, W, VectorGraphNode<L, W>, ArrayList<VectorGraphNode<L, W> >::iterator, ArrayList<VectorGraphNode<L, W> >::position >::edge edge;

    VectorGraph(int dimension = 10, int edges = 20, bool dynamicSize = true);
    VectorGraph(const VectorGraph<L,W>& other);
    ~VectorGraph();
    void init();
    bool isEmpty() const;
    void insNode(node&);
    node insNode(const label&);
    virtual void insEdge(const node&, const node&, const weight&);
    bool existsEdge(const node&, const node&) const;
    void removeNode(const node&);
    virtual void removeEdge(const node&, const node&);
    void adjacents(const node&, LinearList<node, iterator, const_iterator>&) const;
    void nodesList(LinearList<node, iterator, const_iterator>&) const;
    label readLabel(const node&) const;
    void writeLabel(const node&, const label&);
    weight readWeight(const node&, const node&) const;
    virtual void writeWeight(const node&, const node&, const weight&);

    void print() const;

    //Overload
    void nodesList(const node& n, LinkedList<node>& list) const;
    void adjacents(const node& n, LinkedList<node>& list) const;

    int nodesNumber() const { return _nodesNumber; }
    int edgesNumber() const { return _edgesNumber; }
    
private:
    //static const int NO_START = -1;
    struct Edge {
        int to;
        weight w;
    };
    struct NodeRecord {
        bool used;
        int start;
        label _label;
    };
    bool dynamicSize;
    int dimension;
    int edgesDimension;
    int _nodesNumber;
    int _nodesMax;
    int _edgesNumber;
    NodeRecord* nodes;
    Edge* edges;
    //int* map;

    void destroyArrays();
    void cleanNodesArray(int start, int dimension);
    void cleanEdgesArray(int start, int dimension);

    int findFirstFreeNodeIndex();

    int endIndex(const node& n) const {
        if (n.n == _nodesMax - 1) {
            return _edgesNumber;
        } else {
            return nodes[n.n + 1].start;
        }
    }

    bool hasStart(const node& n) const {
        if (n.n == _nodesMax - 1) {
            return nodes[n.n].start < _edgesNumber;
        }

        if (nodes[n.n + 1].start == nodes[n.n].start) {
            return false;
        }
        return true;
    }

    int edgesNumberOf(const node& n) const {
        if (n.n == _nodesMax - 1) {
            return _edgesNumber - nodes[n.n].start;
        }
        return nodes[n.n + 1].start - nodes[n.n].start;
    }

    void resizeEdgesArray(int newDim) {
        rogecode::changeDimension(edges, edgesDimension, newDim);
        cleanEdgesArray(edgesDimension, newDim);
        edgesDimension = newDim;
    }
protected:
};

template<class L, class W>
class UndirectedVectorGraph : public VectorGraph<L, W> {
public:
    typedef typename VectorGraph<L, W>::const_iterator const_iterator;
    typedef typename VectorGraph<L, W>::iterator iterator;
    typedef typename VectorGraph<L, W>::label label;
    typedef typename VectorGraph<L, W>::weight weight;
    typedef typename VectorGraph<L, W>::node node;

    UndirectedVectorGraph(int dimension = 10, int edges = 20, bool dynamicSize = true): VectorGraph<L, W>(dimension, edges, dynamicSize) {}

    void insEdge(const node& n, const node& n2, const weight& w) {
        VectorGraph<L, W>::insEdge(n, n2, w);
        VectorGraph<L, W>::insEdge(n2, n, w);
    }
    void writeWeight(const node& n, const node& n2, const weight& w) {
        VectorGraph<L, W>::writeWeight(n, n2, w);
        VectorGraph<L, W>::writeWeight(n2, n, w);
    }
    void removeEdge(const node& n, const node& n2) {
        VectorGraph<L, W>::removeEdge(n, n2);
        VectorGraph<L, W>::removeEdge(n2, n);
    }
    /*bool existsEdge(const node& n, const node& n2) const {
        return VectorGraph<L, W>::existsEdge(n, n2) || VectorGraph<L, W>::existsEdge(n2, n);
    }*/
};

template<class L, class W>
inline void VectorGraph<L, W>::cleanNodesArray(int start, int dimension) {
    for (int i = start; i < dimension; ++i) {
        nodes[i].used = false;
        nodes[i].start = 0;

    }
}
template<class L, class W>
inline void VectorGraph<L, W>::cleanEdgesArray(int start, int dimension) {
    for (int i = start; i < dimension; ++i) {
        edges[i].to = -1;
    }
}
template<class L, class W>
inline int VectorGraph<L, W>::findFirstFreeNodeIndex() {
    
    //int i;
    //for (i = 0; i < dimension && nodes[i].start != -1; ++i);

    int i = -1;
    if (_nodesNumber == _nodesMax) {
        i = _nodesNumber;
    } else {
        for (int j = 0; j < dimension; ++j) {
            if (!nodes[j].used) {
                i = j;
                break;
            }
        }
    }
    if (i == dimension && dynamicSize) {
        int newDim = dimension + 10;
        rogecode::changeDimension(nodes, dimension, newDim);
        cleanNodesArray(dimension, newDim);
        dimension = newDim;
    } else if (i == dimension && !dynamicSize) {
        throw GraphException("GraphException: Insufficient size for creating new nodes");
    }

    if (i == -1) {
        throw GraphException("Invalid index");
    }
    return i;
}

template<class L, class W>
inline void VectorGraph<L, W>::destroyArrays() {
    if (nodes != nullptr) {
        delete[] nodes;
    }
    if (edges != nullptr) {
        delete[] edges;
    }
}

template<class L, class W>
inline VectorGraph<L, W>::~VectorGraph() {
    destroyArrays();
}

template<class L, class W>
inline VectorGraph<L,W>::VectorGraph(int dimension, int edges, bool dynamicSize): dynamicSize(dynamicSize), dimension(dimension), edgesDimension(edges), _nodesNumber(0), _nodesMax(0), _edgesNumber(0), nodes(nullptr), edges(nullptr) {
    init();
}

template<class L, class W>
inline void VectorGraph<L, W>::init() {
    _nodesNumber = 0;
    _nodesMax = 0;
    _edgesNumber = 0;
    destroyArrays();
    nodes = new NodeRecord[dimension];
    edges = new Edge[edgesDimension];

    cleanNodesArray(0, dimension);
    cleanEdgesArray(0, edgesDimension);
}

template<class L, class W>
VectorGraph<L,W>::VectorGraph(const VectorGraph<L,W>& other):
dynamicSize(other.dynamicSize), dimension(other.dimension), edgesDimension(other.edgesDimension),
_nodesNumber(other._nodesNumber), _nodesMax(other._nodesMax), _edgesNumber(other._edgesNumber),
nodes(nullptr), edges(nullptr)
{
    nodes = new NodeRecord[dimension];
    edges = new Edge[edgesDimension];
    for(int i = 0; i < dimension; ++i) {
        nodes[i] = other.nodes[i];
    }
    for(int i = 0; i < edgesDimension; ++i) {
        edges[i] = other.edges[i];
    }
}

template<class L, class W>
inline bool VectorGraph<L, W>::isEmpty() const {
    return _nodesNumber == 0;
}


template<class L, class W>
inline void VectorGraph<L, W>::insNode(node& n) {
    if (n.n == -1) {
        n.n = findFirstFreeNodeIndex();
    }
    if (n.n < _nodesNumber) {
        ++_nodesNumber;
        if (n.n == _nodesMax) {
            _nodesMax++;
        }
        nodes[n.n].used = true;
        //++_nodesMax;
    } else {
        throw GraphInvalidNodeException("GraphException: Node already in the graph");
    }
}

template<class L, class W>
inline auto VectorGraph<L, W>::insNode(const label& l) -> node {
    auto pos = findFirstFreeNodeIndex();
    nodes[pos].used = true;
    nodes[pos]._label = l;
    if (pos == _nodesMax) {
        _nodesMax++;
    }
    ++_nodesNumber;
    if (pos != 0) {
        nodes[pos].start = _edgesNumber;
    }
    //++_nodesMax;
    return node(pos);
}
template<class L, class W>
inline void VectorGraph<L, W>::insEdge(const node& n, const node& n2, const weight& w) {
    // PRE formale: n1.n o n2.n non superano la dimensione dell'array
    guard(n.n < _nodesMax && n2.n < _nodesMax) else {
        throw GraphInvalidNodeException("GraphInvalidNodeException: At least one in two nodes sent is not valid.\n");
    }
    // PRE: n1 fa parte dei nodi. n2 fa parte dei nodi
    //      Non esiste un arco tra n1 e n2
    /*guard(nodes[n1.n].used && nodes[n2.n].used) else {
        throw GraphInvalidNodeException("GraphInvalidNodeException: At least one in two nodes sent is not valid.\n");
    }*/

    //if (nodes[n.n].start >= edgesDimension) {
    //    resizeEdgesArray(nodes[n.n].start + 10);
    //}
    if (!existsEdge(n, n2)) {
        for (int i = n.n + 1; i < _nodesMax;++i) {
            nodes[i].start += 1;
        }
        ++_edgesNumber;
        if (_edgesNumber == edgesDimension) {
            if (dynamicSize) {
                resizeEdgesArray(edgesDimension + 10);
            } else {
                throw GraphException("GraphException: Max limit of edges reached.");
            }
        }
        rogecode::shiftArray(edges, nodes[n.n].start, _edgesNumber, constants::SHIFT_UP);
        edges[nodes[n.n].start].to = n2.n;
        edges[nodes[n.n].start].w = w;

        /*
        int _start = nodes[n1.n + 1].start;
        rogecode::shiftArray(edges, _start, _edgesNumber, 1);
        for (int i = n1.n; i < _nodesNumber; ++i) {
            if (nodes[i].start != NO_START || i == n1.n) {
                nodes[i].start += 1;
            }
        }
        edges[_start].to = n2.n;*/
    } else {
        throw GraphEdgeException("GraphEdgeException: The edge exists already.\n");
    }
}

template<class L, class W>
inline bool VectorGraph<L, W>::existsEdge(const node& n1, const node& n2) const {
    guard((n1.n < _nodesMax && n2.n < _nodesMax) && n1.n >= 0 && n2.n >= 0) else {
        throw GraphInvalidNodeException("GraphInvalidNodeException: At least one in two nodes sent is not valid.\n");
    }
    guard(nodes[n1.n].start < edgesDimension) else {
        //std::cout << nodes[n1.n].start << "\n";
        throw GraphInvalidNodeException("GraphInvalidNodeException: At least one in two nodes sent is not valid.\n");
    }
    if (!hasStart(n1)) {
        return false;
    }

    int end = endIndex(n1);
    for (int i = nodes[n1.n].start; i < end; ++i) {
        if (edges[i].to == n2.n) {
            return true;
        }
    }

    return false;
}


template<class L, class W> // TODO: Fixare questa funzione
void VectorGraph<L, W>::removeNode(const node& n) {
    // PRE: n è un nodo del grafo
    guard(n.n < _nodesMax) else {
        throw GraphInvalidNodeException("GraphInvalidNodeException: This node is not a node of the graph.\n");
    }
    guard(nodes[n.n].used) else {
        throw GraphInvalidNodeException("GraphInvalidNodeException: This node is not a node of the graph.\n");
    }

    // 1. Ottieni il numero di archi (diff) del nodo
    int diff = edgesNumberOf(n);

    // 2. Tra start ..< start+diff, esegui shift a sx 
    //    Lo shift in edges deve partire da start+diff e diminuire di 1 ogni volta
    int j = 0;
    for (int i = nodes[n.n].start; i < nodes[n.n].start+diff; ++i) {
        rogecode::shiftArray(edges, nodes[n.n].start /*+diff - j*/, _edgesNumber, constants::SHIFT_DOWN);
        ++j;
        --_edgesNumber;
    }

    //  3. Esegui lo shift a sx eliminando il nodo corrente
    //  4. Rimuovi diff a tutti i nodi seguenti
    for (int i = n.n+1; i < _nodesMax; ++i) {
        nodes[i].start -= diff;
    }

    nodes[n.n].used = false;
    --_nodesNumber;

    //  5. Se in edges ci sono collegamenti su n, elimina l'arco
    for (int i = 0; i < _edgesNumber; ++i) {
        if (edges[i].to == n.n) {
            rogecode::shiftArray(edges, i /*+ 1*/, _edgesNumber, constants::SHIFT_DOWN);
            --_edgesNumber;

            /*for (int j = i+1; j < _nodesNumber; ++j) {
                --nodes[j].start;
            }*/
            // Un arco è stato eliminato. Riduci lo start del nodo successivo al nodo per cui start == i
            for (int j = 0; j < _nodesMax;++j) {
                if (nodes[j].start > i) {
                    --nodes[j].start;
                }
            }
        }
    }
}

template<class L, class W>
void VectorGraph<L, W>::removeEdge(const node& n1, const node& n2) {
    // PRE: n1 ed n2 sono nodi del grafo
    guard(n1.n < _nodesMax && n2.n < _nodesMax) else {
        throw GraphInvalidNodeException("GraphInvalidNodeException: At least one in two nodes sent is not valid.\n");
    }

    int _start = nodes[n1.n].start;
    int _end = endIndex(n1);//nodes[n1.n + 1].start;
    for (int i = _start; i < _end; ++i) {
        if (edges[i].to == n2.n) {
            rogecode::shiftArray(edges, i, _edgesNumber, constants::SHIFT_DOWN);
            --_edgesNumber;

            for (int i = n1.n + 1; i < _nodesMax; ++i) {
                nodes[i].start -= 1;
            }
            return;
        }
    }


    throw GraphEdgeException("GraphEdgeException: No edge between n1 and n2.\n");
}

template<class L, class W>
inline void VectorGraph<L, W>::adjacents(const node& n, LinearList<node, iterator, const_iterator>& list) const {
    // PRE: n è un nodo
    guard(n.n < _nodesMax) else {
        throw GraphInvalidNodeException("GraphInvalidNodeException: Node passed isn't a node of the graph.\n");
    }

    list.init();
    if (!hasStart(n)) {
        return;
    }

    int end = endIndex(n);
    for (int i = nodes[n.n].start; i < end; ++i) {
        list.push_back(node(edges[i].to));
    }
}


template<class L, class W>
inline void VectorGraph<L, W>::adjacents(const node& n, LinkedList<node>& list) const {
    // PRE: n è un nodo
    guard(n.n < _nodesMax) else {
        throw GraphInvalidNodeException("GraphInvalidNodeException: Node passed isn't a node of the graph.\n");
    }

    list.init();
    if (!hasStart(n)) {
        return;
    }

    int end = endIndex(n);/*;
    if (n.n == _nodesMax - 1) {
        end = _nodesMax;
    } else {
        end = nodes[n.n + 1].start;
    }*/

    for (int i = nodes[n.n].start; i < end; ++i) {
        list.push_back(node(edges[i].to));
    }
}

template<class L, class W>
inline void VectorGraph<L, W>::nodesList(LinearList<node, iterator, const_iterator>& list) const {
    list.init();
    for (int i = 0; i < _nodesMax; ++i) {
        list.push_back(node(i));
    }
}

template<class L, class W>
inline void VectorGraph<L, W>::nodesList(const node& n, LinkedList<node>& list) const {
    list.init();
    for (int i = 0; i < _nodesMax; ++i) {
        list.push_back(node(i));
    }
}

template<class L, class W>
inline auto VectorGraph<L, W>::readLabel(const node& n) const -> label {
    // PRE: n è un nodo
    guard(n.n < _nodesMax) else {
        throw GraphInvalidNodeException("GraphInvalidNodeException: Node passed isn't a node of the graph.\n");
    }

    return nodes[n.n]._label;
}

template<class L, class W>
inline void VectorGraph<L, W>::writeLabel(const node& n, const label& l) {
    // PRE: n è un nodo
    guard(n.n < _nodesMax) else {
        throw GraphInvalidNodeException("GraphInvalidNodeException: Node passed isn't a node of the graph.\n");
    }

    nodes[n.n]._label = l;
}

template<class L, class W>
inline auto VectorGraph<L, W>::readWeight(const node& n, const node& n2) const -> weight {
    // PRE: n1,n2 sono nodi
    guard(n.n < _nodesMax && n2.n < _nodesMax) else {
        throw GraphInvalidNodeException("GraphInvalidNodeException: Node passed isn't a node of the graph.\n");
    }

    for (int i = nodes[n.n].start; i < endIndex(n); ++i) {
        if (edges[i].to == n2.n) {
            return edges[i].w;
        }
    }

    throw GraphEdgeException("GraphEdgeException: There is no edge between nodes passed.\n");
}

template<class L, class W>
inline void VectorGraph<L, W>::writeWeight(const node& n, const node& n2, const weight& w) {
    // PRE: n1,n2 sono nodi
    guard(n.n < _nodesMax && n2.n < _nodesMax) else {
        throw GraphInvalidNodeException("GraphInvalidNodeException: Node passed isn't a node of the graph.\n");
    }

    int end = endIndex(n);
    for (int i = nodes[n.n].start; i < end; ++i) {
        if (edges[i].to == n2.n) {
            edges[i].w = w;
        }
    }

    throw GraphEdgeException("GraphEdgeException: There is no edge between nodes passed.\n");
}

template<class L, class W>
void VectorGraph<L, W>::print() const {
    std::cout << "Graph nodes:\n";
    for (int i = 0; i < _nodesMax; ++i) {
        if(nodes[i].used)
        std::cout << i << "[" << nodes[i].start << "|" << nodes[i]._label << "]" << std::endl;
    }
    std::cout << "Edges:\n";
    for (int i = 0; i < _edgesNumber; ++i) {
        std::cout << i << "[" << edges[i].to <<  "|" << edges[i].w << "]" << std::endl;
    }
}
#endif
