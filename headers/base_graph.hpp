#pragma once
#include <iostream>
#include <stdexcept>
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
        Edge(){}
        Edge(const int& weight, Vertex<T> *dst);
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

        friend class Graph<T>;
        friend class Edge<T>;

    public:
        T* value;
        std::string *id;
        Vertex(){}
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

        Vertex<T>* operator[](const int& index);
        Vertex<T>* get_vertex(const std::string& id);
        Vertex<T>* get_vertex(const T& value);

    public:
        Graph(){}
        Graph(const std::string& id, bool directed = false, bool weighted = WEIGHTLESS);
        ~Graph();

        const int& get_vertices() const;
        const int& get_edges() const;
        const std::string& get_id() const;
        const float& get_weight(const std::string& org, const std::string& dst) const;

        bool is_empty();
        void add_vertex(const std::string &id, const T &value);
        void add_edge(const std::string& org, const std::string& dst, const int& weight);
        bool vertex_exists(const std::string& id);
        bool vertex_exists(const T& value);
        bool edge_exists(const std::string& org, const std::string& dst);
        void print(const Vertex<T>& vtx = nullptr, bool edges = false);
    };

    ///////////////////////////////////
    /// EDGE'S METHODS DECLARATIONS ///
    ///////////////////////////////////

    template <typename T>
    Edge<T>::Edge(const int& weight, Vertex<T> *dst)
    {
        this->dstVtx = dst;
        this->nextEdge = nullptr;
        this->weight = new float(weight);
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
    const int& Graph<T>::get_vertices() const
    { return this->vertices; }

    template <typename T>
    const int& Graph<T>::get_edges() const
    { return this->edges; }

    template <typename T>
    const std::string& Graph<T>::get_id() const
    { return this->id; }

    template <typename T>
    bool Graph<T>::is_empty()
    { return !this->vertices; }

    /// Creates a new vertex and adds it at the end of the vertices list
    template <typename T>
    void Graph<T>::add_vertex(const std::string &id, const T &value)
    {
        Vertex<T>* auxVtx = this->root;
        std::string msg;
        if (is_empty())
            this->root = new Vertex<T>(id, value);
        else if (vertex_exists(id)) {
            msg = "The given id \"";
            msg += id;
            msg += "\" is already in use";
            throw std::range_error(msg);
        }
        else {
            for (; auxVtx->nextVtx != nullptr; auxVtx = auxVtx->nextVtx);
            auxVtx->nextVtx = new Vertex<T>(id, value);
        }
        this->vertices++;
    }

    /// Creates a new edge which will connect two given existing vertices.
    /// It'll also be appended to the origin vertex's edges list.
    template <typename T>
    void Graph<T>::add_edge(const std::string& org, const std::string& dst, const int &weight)
    {
        Vertex<T> *auxOrg;
        Edge<T> *auxEdg;
        if (is_empty())
            throw std::range_error("The graph has no vertices, therefore is not possible to add an edge");
        if (!vertex_exists(org) || !vertex_exists(dst))
            throw std::range_error("The given vertex is not available");
        //auxOrg = get_vertex(org);
        // If origin vertex's edge list is empty we create a new edge as the first in the list
        std::cout << "value: " << auxOrg->id << std::endl;
        if (auxOrg->adjEdge == nullptr) {
            std::cout << "ASLKAJSDSF" << std::endl;
            auxOrg->adjEdge = new Edge<T>(weight, get_vertex(dst));
        }
        // Otherwise we iterate over origin vertex's edge list until we reach the end of the list so
        // we can create a new Edge (similar to push_back)
        // In both cases we use dst as edge destination vertex
        else {
            for (auxEdg = auxOrg->adjEdge; auxEdg->nextEdge != nullptr; auxEdg != auxEdg->nextEdge);
            auxEdg->nextEdge = new Edge<T>(weight, get_vertex(dst));
        }
    }

    /// Returns true if a given id matches with an existing vertex
    /// and it returns false otherwise
    template <typename T>
    bool Graph<T>::vertex_exists(const std::string& id)
    {
        Vertex<T>* auxVtx = this->root;
        if (is_empty())
            return false;
        for (; auxVtx != nullptr; auxVtx = auxVtx->nextVtx)
            if (*auxVtx->id == id)
                return true;
        return false;
    }

    /// Returns true if a given value matches with an existing vertex
    /// and it returns false otherwise
    template<typename T>
    bool Graph<T>::vertex_exists(const T &value)
    {
        Vertex<T>* auxVtx = this->root;
        if (is_empty())
            return false;
        for (; auxVtx != nullptr; auxVtx = auxVtx->nextVtx)
            if (*auxVtx->value == value)
                return true;
        return false;
    }

    /// Returns a Vertex using an index (0 <= index < vertices) for the vtx list.
    /// If no vertex is found then the function an error will pop up.
    template<typename T>
    Vertex<T> *Graph<T>::operator[](const int &index)
    {
        Vertex<T>* auxVtx = this->root;
        if (index >= this->vertices)
            throw std::range_error("Index is greater or equal than the number of vertices stored");
        if (index < 0)
            throw std::range_error("Index is smaller than zero");
        for (int crrtPos = 0; crrtPos < index; crrtPos++)
            auxVtx = auxVtx->nextVtx;
        return auxVtx;
    }

    /// Returns a vertex using an id so the method can iterate over every vtx in the list until a matching
    /// id is found. If no matching id is found then the method will return a nullptr.
    template<typename T>
    Vertex<T> *Graph<T>::get_vertex(const std::string &id)
    {
        Vertex<T>* auxVtx = this->root;
        Vertex<T>* result = nullptr;
        if (is_empty())
            throw std::range_error("This graph has no vertices");
        if (!vertex_exists(id))
            throw std::range_error("The given id doesn't correspond to any vertex stored in the graph");
        for (; auxVtx != nullptr; auxVtx = auxVtx->nextVtx)
            if (*auxVtx->id == id)
                result = auxVtx;
        return result;
    }

    /// Returns a pointer to a vertex so it can be easily accessed
    template<typename T>
    Vertex<T> *Graph<T>::get_vertex(const T &value)
    {
        Vertex<T>* auxVtx = this->root;
        Vertex<T>* result = nullptr;
        if (is_empty())
            throw std::range_error("This graph has no vertices");
        if (!vertex_exists(value))
            throw std::range_error("The given value doesn't correspond to any vertex stored in this graph");
        for (; auxVtx != nullptr; auxVtx = auxVtx->nextVtx)
            if (*auxVtx->value = value)
                result = auxVtx;
        return result;
    }

    template<typename T>
    const float &Graph<T>::get_weight(const std::string& org, const std::string& dst) const
    {
        if (!vertex_exists(org) || !vertex_exists(dst))
            throw std::range_error("One of the given vertices doesn't exist");
    }

    template <typename T>
    bool Graph<T>::edge_exists(const std::string& org, const std::string& dst)
    {
        Vertex<T> *auxVtx;
        Edge<T> *auxEdg;
        if (!vertex_exists(org) || !vertex_exists(dst)) {
            std::cout << "One of the given vertices doesn't exist" << std::endl;
            return false;
        }
        auxVtx = get_vertex(org);
        auxEdg = auxVtx->adjEdge;
        if (auxEdg == nullptr)
            return false;
        for (; auxEdg->nextEdge != nullptr; auxEdg = auxEdg->nextEdge);
        if (*auxEdg->dstVtx->id == dst)
            return true;
        return false;
    }
}