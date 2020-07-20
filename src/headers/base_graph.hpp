#include <iostream>

/////////////////////////////////
/// BASE CLASSES DECLARATIONS ///
/////////////////////////////////
template <typename T>
class Graph;
template <typename T>
class Edge;
template <typename T>
class Vertex;

/////////////////////////////
/// EDGE CLASS DEFINITION ///
/////////////////////////////
template <typename T>
class Edge
{
private:
    Vertex<T>* dstVtx;
    Edge<T>* nextEdge;
    float weight;
public:
    
};

///////////////////////////////
/// VERTEX CLASS DEFINITION ///
///////////////////////////////
template <typename T>
class Vertex
{
private:
    Vertex<T>* nextVtx;
    Edge<T>* adjEdge;
    std::string id;
    
public:
    Vertex();
};

//////////////////////////////
/// GRAPH CLASS DEFINITION ///
//////////////////////////////
template <typename T>
class Graph
{
private:
    Vertex<T>* root;
    std::string id;
    int vertices;
    int edges;

    friend class Vertex<T>;
    friend class Edge<T>;

public:
    Graph(){}
    ~Graph(){}

    // STATUS
    // ADD
    // REMOVE

    // GETTERS
    int getVertices() const;
    int getEdges() const;
    const std::string getId() const;
};

///////////////////////////////////
/// EDGE'S METHODS DECLARATIONS ///
///////////////////////////////////

/////////////////////////////////////
/// VERTEX'S METHODS DECLARATIONS ///
/////////////////////////////////////
template <typename T>
Vertex<T>::Vertex()
{

}

////////////////////////////////////
/// GRAPH'S METHODS DECLARATIONS ///
////////////////////////////////////

template <typename T>
int Graph<T>::getVertices() const
{ return this->vertices; }

template <typename T>
int Graph<T>::getEdges() const
{ return this->edges; }

template <typename T>
const std::string Graph<T>::getId() const
{ return this->id; }
