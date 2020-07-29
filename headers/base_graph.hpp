#pragma once
#include <iostream>
#define WEIGHTLESS 0

// gph stands for graph, this namespace is used mainly for
// avoiding duplicated keywords when other libraries are included
namespace gph
{
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
        float* weight;

        friend class Vertex<T>;
        friend class Graph<T>;

    public:
        Edge(const int& weight);
        ~Edge();
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
        std::string *id;
        T* value;

        friend class Graph<T>;
        friend class Edge<T>;
        
    public:
        Vertex(const std::string& id, const T& value);
        ~Vertex();
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
        bool weighted;
        bool directed;

        friend class Vertex<T>;
        friend class Edge<T>;

    public:
        Graph(const std::string& id, bool directed = false, bool weighted = WEIGHTLESS);
        ~Graph();

        const int& getVertices() const;
        const int& getEdges() const;
        const std::string& getId() const;

        Vertex<T>*& operator[](const int& index);
        Vertex<T>*& getVertex(const std::string& id);

        void add_vertex(const std::string &id, const T &value);
        void add_edge(const Vertex<T>*& org, const Vertex<T>*& dst, const int& weight);
        bool is_empty();
        bool vertex_exists(const std::string& id);
    };

    ///////////////////////////////////
    /// EDGE'S METHODS DECLARATIONS ///
    ///////////////////////////////////

    template <typename T>
    Edge<T>::Edge(const int& weight)
    {
        this->dstVtx = nullptr;
        this->nextEdge = nullptr;
        this->weight = weight;
    }

    template <typename T>
    Edge<T>::~Edge()
    {
        delete this->dstVtx;
        delete this->nextEdge;
        delete this->weight;
        this->weight = nullptr;
        this->nextEdge = nullptr;
        this->dstVtx = nullptr;
    }


    /////////////////////////////////////
    /// VERTEX'S METHODS DECLARATIONS ///
    /////////////////////////////////////

    template <typename T>
    Vertex<T>::Vertex(const std::string &id, const T &value)
    {
        this->id = new std::string(id);
        this->value = new T(value);
        this->adjEdge = nullptr;
        this->nextVtx = nullptr;
    }

    template <typename T>
    Vertex<T>::~Vertex()
    {
        delete this->id;
        delete this->value;
        delete this->adjEdge;
        delete this->nextVtx;
        this->id = nullptr;
        this->value = nullptr;
        this->adjEdge = nullptr;
        this->nextVtx = nullptr;
    }


    ////////////////////////////////////
    /// GRAPH'S METHODS DECLARATIONS ///
    ////////////////////////////////////

    template <typename T>
    Graph<T>::Graph(const std::string& id, bool directed, bool weighted)
    {
        this->root = nullptr;
        this->vertices = 0;
        this->edges = 0;
        this->directed = directed;
        this->weighted = weighted;
        this->id = id;
    }

    template <typename T>
    Graph<T>::~Graph()
    {
        delete this->root;
        this->root = nullptr;
    }

    template <typename T>
    const int& Graph<T>::getVertices() const
    { return this->vertices; }

    template <typename T>
    const int& Graph<T>::getEdges() const
    { return this->edges; }

    template <typename T>
    const std::string& Graph<T>::getId() const
    { return this->id; }
    
    template <typename T>
    bool Graph<T>::is_empty()
    { return !this->vertices; }

    /// Creates a new vertex and adds it at the end of the vertices list
    template <typename T>
    void Graph<T>::add_vertex(const std::string &id, const T &value)
    {
        Vertex<T>* auxVtx = this->root;
        if (is_empty())
            this->root = new Vertex<T>(id, value);
        else {
            for (; auxVtx->nextVtx != nullptr; auxVtx = auxVtx->nextVtx);
            auxVtx->nextVtx = new Vertex<T>(id, value);
        }
        this->vertices++;
    }

    /// Creates a new edge which will connect two given existing vertices.
    /// It'll also be appended to the origin vertex's edges list.
    template <typename T>
    void Graph<T>::add_edge(const Vertex<T> *&org, const Vertex<T> *&dst, const int &weight)
    {

    }

    /// Returns true if a given id matches with an existing vertex
    /// and it returns false otherwise
    template <typename T>
    bool Graph<T>::vertex_exists(const std::string& id)
    {
        Vertex<T>* auxVtx = this->root;
        if (is_empty())
            return false;
        if (*auxVtx->id == id)
            return true;
        for (; auxVtx->nextVtx != nullptr; auxVtx = auxVtx->nextVtx)
            if (*auxVtx->id == id)
                return true;
        return false;
    }
}