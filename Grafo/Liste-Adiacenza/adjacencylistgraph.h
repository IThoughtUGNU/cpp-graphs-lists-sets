//
//  adjacencylistgraph.h
//  Grafi
//
//  Created by Ruggiero Altini on 14/12/16.
//  Copyright © 2016 Ruggiero Altini. All rights reserved.
//
//  C++11 compliant

//#pragma once
#ifndef adjacencylistgraph_h
#define adjacencylistgraph_h

#include "../graph.h"
#include "../../RogeCode-library/rogecodelibrary.h"
#include "../../Lista/Collegata/linkedlist.h"
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

class AdjacencyListGraphNode {
    //friend class AdjacencyListGraph<L,W>
public:
    AdjacencyListGraphNode(const AdjacencyListGraphNode& other) { nodeId = other.nodeId; }
    

    inline AdjacencyListGraphNode(int _id) {
        nodeId = _id;
    }
    inline AdjacencyListGraphNode() : nodeId(-1) {}

    inline int getId() const { return nodeId; }
    inline void setId(int _id) { nodeId = _id; }

    AdjacencyListGraphNode& operator=(const AdjacencyListGraphNode& right) { if (this != &right) nodeId = right.nodeId; return *this; }
	bool operator==(const AdjacencyListGraphNode& right) const { return nodeId == right.nodeId; }
	bool operator!=(const AdjacencyListGraphNode& right) const { return nodeId != right.nodeId; }
private:
    int nodeId;
};

inline std::ostream& operator<<(std::ostream& os, const AdjacencyListGraphNode &n) {
    os << "(id:" << n.getId() << ")";
    return os;
}

template<class L, class W>
class AdjacencyListGraph: public Graph<L, W, AdjacencyListGraphNode, LinkedList<AdjacencyListGraphNode>::iterator, LinkedList<AdjacencyListGraphNode>::position > {
public:
    typedef typename Graph<L, W, AdjacencyListGraphNode, LinkedList<AdjacencyListGraphNode>::iterator, LinkedList<AdjacencyListGraphNode>::position >::const_iterator const_iterator;
    typedef typename Graph<L, W, AdjacencyListGraphNode, LinkedList<AdjacencyListGraphNode>::iterator, LinkedList<AdjacencyListGraphNode>::position >::iterator iterator;
    typedef typename Graph<L, W, AdjacencyListGraphNode, LinkedList<AdjacencyListGraphNode>::iterator, LinkedList<AdjacencyListGraphNode>::position >::label label;
    typedef typename Graph<L, W, AdjacencyListGraphNode, LinkedList<AdjacencyListGraphNode>::iterator, LinkedList<AdjacencyListGraphNode>::position >::weight weight;
    typedef typename Graph<L, W, AdjacencyListGraphNode, LinkedList<AdjacencyListGraphNode>::iterator, LinkedList<AdjacencyListGraphNode>::position >::node node;
    typedef typename Graph<L, W, AdjacencyListGraphNode, LinkedList<AdjacencyListGraphNode>::iterator, LinkedList<AdjacencyListGraphNode>::position >::edge edge;


    //AdjacencyListGraph(int dimension = 10);
    AdjacencyListGraph(bool directed = true, int dimension = 10);
	AdjacencyListGraph(const AdjacencyListGraph<L,W>&);
    ~AdjacencyListGraph();

    void init();
    bool isEmpty() const;
    node insNode(const label&);
    void insNode(node&);
    void insEdge(const node& n1, const node& n2, const weight& w);
    void removeNode(const node&);
    void removeEdge(const node&, const node&);
    void adjacents(const node&, LinearList<node, iterator, const_iterator>&) const;
    void nodesList(LinearList<node, iterator, const_iterator>&) const;
    label readLabel(const node&) const;
    void writeLabel(const node&, const label&);
    weight readWeight(const node&, const node&) const;
    void writeWeight(const node&, const node&, const weight&);
	bool existsEdge(const node&, const node&) const;
    int nodesNumber() const;
    int edgesNumber() const;

    void adjacents(const node& n, LinkedList<node>& list) const;
    /*
    //	virtual bool esisteNodo(Nodo) = 0;
    //	virtual bool esisteArco(Arco) = 0;
    virtual weight readWeight(const node&, const node&) = 0;
    virtual void writeWeight(const node&, const node&) const = 0;

    virtual int nodesNumber() = 0;
    virtual int edgesNumber() = 0;
    */

    void print() const;

	AdjacencyListGraph<L,W>& operator=(const AdjacencyListGraph<L, W>&);

    bool operator==(const AdjacencyListGraph<L, W>&) const;
    bool operator!=(const AdjacencyListGraph<L, W>&) const;
private:
    class EdgeRecord {
    public:
        weight _weight;
        node _to;

        bool operator==(const EdgeRecord& right) const { return _weight == right._weight && _to == right._to; }
        bool operator!=(const EdgeRecord& right) const { return _weight != right._weight || _to != right._to; }
    };

    class NodeRecord {
    public:
        label _label;
        bool empty;
        LinkedList<EdgeRecord> edges;

        inline NodeRecord() {
            empty = true;
        }


        bool operator==(const NodeRecord& right) const {
            return (_label == right._label) && (empty == right.empty) && edges == right.edges;
        }
        bool operator!=(const NodeRecord& right) const { return !(*this == right); }
    };

    void validateNode(const node&, bool) const;

    NodeRecord* matrix;
    int dimension;
    int nodes;
    int edges;
    bool directed;

protected:
};

template<class L, class W>
AdjacencyListGraph<L, W>::~AdjacencyListGraph() {
    if (matrix != nullptr) {
        delete [] matrix;
    }
}

template<class L, class W>
AdjacencyListGraph<L, W>::AdjacencyListGraph(const AdjacencyListGraph<L,W>& graph) 
    : matrix(nullptr), dimension(graph.dimension), nodes(graph.nodes), edges(graph.edges), directed(graph.directed) {

	/*dimension = graph.dimension;
	nodes = graph.nodes;
	edges = graph.edges;
	directed = graph.directed;*/
	matrix = new NodeRecord[dimension];
	for (int i = 0; i < dimension; ++i) {
		matrix[i] = graph.matrix[i];
	}
}

template<class L, class W>
AdjacencyListGraph<L, W>& AdjacencyListGraph<L, W>::operator=(const AdjacencyListGraph<L,W>& graph) {
	if (this != &graph) {
		if (matrix != nullptr) {
			delete[] matrix;
		}
		dimension = graph.dimension;
		nodes = graph.nodes;
		edges = graph.edges;
		directed = graph.directed;
		matrix = new NodeRecord[dimension];
		for (int i = 0; i < dimension; ++i) {
			matrix[i] = graph.matrix[i];
		}
	}
	return *this;
}

/*
template<class L, class W>
AdjacencyListGraph<L, W>::AdjacencyListGraph(int dimension): dimension(dimension) {
    init();
}
*/
template<class L, class W>
AdjacencyListGraph<L, W>::AdjacencyListGraph(bool directed, int dimension) :
    matrix(nullptr), dimension(dimension), nodes(0), edges(0), directed(directed) {

    init();
}

template<class L, class W>
void AdjacencyListGraph<L, W>::init() {
    nodes = 0;
    edges = 0;
    if (matrix != nullptr) {
        delete[] matrix;
    }
    matrix = new NodeRecord[dimension];

    for (int i = 0; i < dimension; ++i) {
        matrix[i].edges.init();
        matrix[i].empty = true;
    }
}

template<class L, class W>
bool AdjacencyListGraph<L, W>::isEmpty() const {
    return nodes == 0;
}


template<class L, class W>
inline typename AdjacencyListGraph<L, W>::node AdjacencyListGraph<L, W>::insNode(const label& l) {
    node n;
    insNode(n);
    writeLabel(n, l);
    return n;
}

template<class L, class W>
void AdjacencyListGraph<L, W>::insNode(node& n) {
    /*
    if (n.getId() < 0) {
        throw GraphInvalidNodeException();
    }
    else if (n.getId() >= dimension) {
        rogecode::changeDimension(matrix, dimension, n.getId() +10);
        dimension = n.getId() + 10;
    }
    if (nodes < dimension) {
        rogecode::changeDimension(matrix, dimension, int(dimension*1.5) + 1);
        dimension = int(dimension*1.5) + 1;
    }
    */
    int num = 0;
    while (num < dimension && matrix[num].empty == false) {
        num++;
    }
    if (num >= dimension) {
        rogecode::changeDimension(matrix, dimension, num + 10);
        dimension = num + 10;
    }
    nodes++;
    matrix[num].empty = false;
    n.setId(num);
}

template<class L, class W>
void AdjacencyListGraph<L, W>::insEdge(const node& n1, const node& n2, const weight& w) {
    EdgeRecord record;
    record._weight = w;
    record._to = n2;

    //bool found = false;
    for (auto it = matrix[n1.getId()].edges.begin(); !matrix[n1.getId()].edges.end(it); ++it) {
        if ((*it)._to.getId() == n2.getId()) {
            //found = true;
            throw GraphEdgeException("This edge already exists");
            //break;
        }
    }
    //if (!found) {
    matrix[n1.getId()].edges.push_front(record);
    edges++;
    //}
    //matrix[n1.getId()].edges.push_front(record);

    if (!directed) {
        EdgeRecord record2;
        record2._weight = w;
        record2._to = n1;
        //matrix[n2.getId()].edges.push_front(record2);
        bool found = false;
        for (auto it = matrix[n2.getId()].edges.begin(); !matrix[n2.getId()].edges.end(it); ++it) {
            if ((*it)._to.getId() == n1.getId()) {
                found = true;
                break;
            }
        }
        if (!found) {
            matrix[n2.getId()].edges.push_front(record2);
            edges++;
        }


    }
}

template<class L, class W>
void AdjacencyListGraph<L, W>::removeNode(const node& n) {
    // Eliminare il nodo n._id dalla matrice
    // Eliminare in quella corrispondenza, tutti gli archi
    // Eliminare gli archi degli altri nodi
    validateNode(n, true);

    //auto& linkedNodes = matrix[n.getId()].edges;
    edges -= matrix[n.getId()].edges.size();
    matrix[n.getId()].edges.init();
    matrix[n.getId()].empty = true;

    /*
    for (auto it = linkedNodes.begin(); !linkedNodes.end(it); ++it) {
        auto edgeRecord = linkedNodes.read(it);
        if (edgeRecord._to.getId() == n.getId()) {
            linkedNodes.erase(it++);
        }
    }*/

    for (int i = 0; i < nodes; ++i) {
        if (matrix[i].empty) {
            continue;
        }
        for (auto it = matrix[i].edges.begin(); !matrix[i].edges.end(it); ++it) {
            auto edgeRecord = matrix[i].edges.read(it);
            if (edgeRecord._to.getId() == n.getId()) {
                it = matrix[i].edges.erase(it);
                edges--;
            }
        }
    }
    nodes--;
}

template<class L, class W>
void AdjacencyListGraph<L, W>::removeEdge(const node& n1, const node& n2) {
    validateNode(n1, true);
    validateNode(n2, true);

    for (auto it = matrix[n1.getId()].edges.begin(); !matrix[n1.getId()].edges.end(it); ++it) {
        if (matrix[n1.getId()].edges.read(it)._to.getId() == n2.getId()) {
            it = matrix[n1.getId()].edges.erase(it);
            edges--;
            break;
        }
    }

    if(!directed) {
        for (auto it = matrix[n2.getId()].edges.begin(); !matrix[n2.getId()].edges.end(it); ++it) {
            if (matrix[n2.getId()].edges.read(it)._to.getId() == n1.getId()) {
                it = matrix[n2.getId()].edges.erase(it);
                edges--;
                break;
            }
        }
    }
}

template<class L, class W>
inline void AdjacencyListGraph<L, W>::validateNode(const node& n, bool max) const {
    if (n.getId() < 0) {
        throw GraphInvalidNodeException();
    }
    if (max) {
        if (n.getId() >= dimension) {
            throw GraphInvalidNodeException();
        }
    }
}

template<class L, class W>
void AdjacencyListGraph<L, W>::adjacents(const node& n, LinearList<node, iterator, const_iterator>& list) const {
    validateNode(n, true);

    list.init();
    for (auto it = matrix[n.getId()].edges.begin(); !matrix[n.getId()].edges.end(it); ++it) {
        list.push_back(node(matrix[n.getId()].edges.read(it)._to));
    }
}
template<class L, class W>
void AdjacencyListGraph<L, W>::adjacents(const node& n, LinkedList<node>& list) const {
    validateNode(n, true);

    list.init();
    for (auto it = matrix[n.getId()].edges.begin(); !matrix[n.getId()].edges.end(it); ++it) {
        list.push_back(node(matrix[n.getId()].edges.read(it)._to));
    }
}



template<class L, class W>
void AdjacencyListGraph<L, W>::nodesList(LinearList<node, iterator, const_iterator>& list) const {
    list.init();
    for (int i = 0; i < dimension; ++i) {
        if (!matrix[i].empty) {
            list.push_back(node(i));
        }
    }
}

template<class L, class W>
inline typename AdjacencyListGraph<L, W>::label AdjacencyListGraph<L, W>::readLabel(const node& n) const {
    validateNode(n, true);

    return matrix[n.getId()]._label;
}

template<class L, class W>
inline void AdjacencyListGraph<L, W>::writeLabel(const node& n, const label& l) {
    validateNode(n, true);

    matrix[n.getId()]._label = l;
}

template<class L, class W>
typename AdjacencyListGraph<L, W>::weight AdjacencyListGraph<L, W>::readWeight(const node& n1, const node& n2) const {
    for (auto it = matrix[n1.getId()].edges.begin(); !matrix[n1.getId()].edges.end(it); ++it) {
        if (matrix[n1.getId()].edges.read(it)._to.getId() == n2.getId()) {
            return matrix[n1.getId()].edges.read(it)._weight;
        }
    }

    if (!directed) {
        for (auto it = matrix[n2.getId()].edges.begin(); !matrix[n2.getId()].edges.end(it); ++it) {
            if (matrix[n2.getId()].edges.read(it)._to.getId() == n1.getId()) {
                return matrix[n2.getId()].edges.read(it)._weight;
            }
        }
    }
    throw GraphInvalidNodeException();
}

template<class L, class W>
void AdjacencyListGraph<L, W>::writeWeight(const node& n1, const node& n2, const weight& w) {
    validateNode(n1, true);
    validateNode(n2, true);

    for (auto it = matrix[n1.getId()].edges.begin(); !matrix[n1.getId()].edges.end(it); ++it) {
        if (matrix[n1.getId()].edges.read(it)._to.getId() == n2.getId()) {
            auto _edgeRecord = matrix[n1.getId()].edges.read(it);
            _edgeRecord._weight = w;
            matrix[n1.getId()].edges.write(_edgeRecord, it);
        }
    }

    if (!directed) {
        for (auto it = matrix[n2.getId()].edges.begin(); !matrix[n2.getId()].edges.end(it); ++it) {
            if (matrix[n2.getId()].edges.read(it)._to.getId() == n1.getId()) {
                auto _edgeRecord = matrix[n2.getId()].edges.read(it);
                _edgeRecord._weight = w;
                matrix[n2.getId()].edges.write(_edgeRecord, it);
            }
        }
    }
}

template<class L, class W>
inline int AdjacencyListGraph<L, W>::nodesNumber() const {
    return nodes;
}

template<class L, class W>
inline int AdjacencyListGraph<L, W>::edgesNumber() const {
    return edges;
}


template<class L, class W>
bool AdjacencyListGraph<L, W>::existsEdge(const node& n1, const node& n2) const {
	if (!matrix[n1.getId()].empty) {
		for (auto it = matrix[n1.getId()].edges.begin(); !matrix[n1.getId()].edges.end(it); ++it) {
			if ((*it)._to == n2) {
				return true;
			}
		}
	}
	return false;
	//if (!directed) {
	//}
}

template<class L, class W>
void AdjacencyListGraph<L, W>::print() const {
    for (int i = 0; i < dimension; ++i) {
        if (matrix[i].empty) {
            continue;
        }
        cout << "[index:" << i << ", label:" << matrix[i]._label << "]: ";
        cout << "[";
        for (auto it = matrix[i].edges.begin(); !matrix[i].edges.end(it); ++it) {
            auto edgeRecord = matrix[i].edges.read(it);
            cout << "(id:" << edgeRecord._to.getId() << "," << "w:" << edgeRecord._weight << ")";
            if (!matrix[i].edges.end(matrix[i].edges.next(it)) ) {
                cout << ",";
            }
        }
        cout << "]\n";
    }
    cout << "nodes: " << nodes << ", edges: " << edges << endl;
}


template<class L, class W>
bool AdjacencyListGraph<L, W>::operator==(const AdjacencyListGraph<L, W>& right) const {
    if (nodes != right.nodes || edges != right.edges || directed != right.directed ) {
        return false;
    }
    if (dimension != right.dimension) return false;

    for (int i = 0; i < dimension; ++i) {
        if (matrix[i] != right.matrix[i]) {
            return false;
        }
    }
    return true;
}

template<class L, class W>
bool AdjacencyListGraph<L, W>::operator!=(const AdjacencyListGraph<L, W>& right) const {
    return !(*this == right);
}

#endif