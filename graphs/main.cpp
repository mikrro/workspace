#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>
#include <queue>

template<typename T> class Vertex
{
public:
    typedef std::vector<std::shared_ptr<Vertex<T> > > AdjList;

    static std::shared_ptr<Vertex<T> > create(int index) {
        return std::shared_ptr<Vertex<T> >(new Vertex<T>(index));
    }

    Vertex(int i): index(i) {}

    AdjList getEdges() {
        return edges;
    }

    void addEdge(std::shared_ptr<Vertex<T> > w) {
        edges.push_back(w);
    }

    unsigned long E() { return edges.size(); }

    void print() {
        for(auto e : edges)
            std::cout << index << " - " <<  e->getIndex() << std::endl;
    }

    void sortEdges() {
        std::sort(edges.begin(), edges.end(), [](std::shared_ptr<Vertex<T> > a, std::shared_ptr<Vertex<T> > b)
        {
            return a->getIndex() < b->getIndex();
        });
    }

    int getIndex()
    { return index; }

private:
    AdjList edges;
    T value;
    int index;
};

template<typename T> class Graph
{
public:
    Graph(unsigned long V) {
        vertices.reserve(V);
        for(int i=0; i < V; i++)
            vertices.push_back(Vertex<T>::create(i));
    };

    Graph(std::string file_name, bool undirected) {
        std::ifstream file(file_name);
        if (file.is_open()) {
            std::string line;
            std::getline(file, line);
            *this = Graph(atoi(line.c_str()));
            std::getline(file, line); // edges
            while (std::getline(file, line)) {
                ulong split_index = line.find(' ');
                int v = atoi(line.substr(0, line.size() - split_index - 1).c_str());
                int w = atoi(line.substr(split_index).c_str());
                if(undirected)
                    addEdge(w,v);
                addEdge(v,w);
            }

            for(auto v: vertices)
                v->sortEdges();
        }
    };

    void addEdge(int v, int w) {
        vertices[v]->addEdge(vertices[w]);
    };

    typename Vertex<T>::AdjList adj(int v) {};

    unsigned long V()
    { return vertices.size();}

    std::vector<std::shared_ptr<Vertex<T> > > getVertices() {
        return vertices;
    }

    std::shared_ptr<Vertex<T> >  getVertex(int v) {
        return vertices[v];
    }


    unsigned long E()
    {   unsigned long sum = 0;
        std::for_each(vertices.begin(), vertices.end(), [&](std::shared_ptr<Vertex<T> > &v){ sum+= v->E();});
        return sum;
    }


   void print() {
       for(auto v : vertices)
           v->print();
   };

private:
    std::vector<std::shared_ptr<Vertex<T> > > vertices;
};

template<typename T> class DepthFirstSearch {
    std::vector<bool> marked;
    std::vector<int> edgeTo;
    int source;

public:
    DepthFirstSearch(Graph<T> G, int v) :source(v) {
        marked.resize(G.V());
        std::fill(marked.begin(),marked.end(),false);
        edgeTo.resize(G.V());
        std::fill(edgeTo.begin(),edgeTo.end(),-1);
        edgeTo[v] = v;
        //dfs(G,v);
        bfs(G,v);
    }

    bool hasPathTo(int v) {
        return marked[v];
    }

    std::list<int> pathTo(int v) {
        std::list<int> path;
        for (int x = v; x != source; x = edgeTo[x])
            path.push_back(x);
        path.push_back(source);

        return path;
    }

    void print() {
        std::cout << "\nsource " << source << std::endl;
        for(int i = 0; i < edgeTo.size(); i++)
            std::cout << i << " | " << edgeTo[i] << std::endl;
    }

private:
    void dfs(Graph<T> &G, int v) {
        marked[v] = true;
        std::shared_ptr<Vertex<T> > vertex = G.getVertex(v);
        for(auto w : vertex->getEdges()) {
            if(!marked[w->getIndex()]) {
                dfs(G, w->getIndex());
                edgeTo[w->getIndex()] = v;
            }
        }
    }

    void bfs(Graph<T> &G, int v) {
        std::queue<int> q;
        marked[v] = true;
        q.push(v);
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            std::shared_ptr<Vertex<T> > vertex = G.getVertex(v);
            for (auto w : vertex->getEdges()) {
                if (!marked[w->getIndex()]) {
                    q.push(w->getIndex());
                    marked[w->getIndex()] = true;
                    edgeTo[w->getIndex()] = v;
                }
            }
        }
    }
};




int main(int argc, char** argv) {

    std::string file_name = argv[1];
    bool undirected = atoi(argv[2]) != 0;
    Graph<int> G(file_name, undirected);
    G.print();
    DepthFirstSearch<int> dfs(G,atoi(argv[3]));
    std::cout << (dfs.hasPathTo(atoi(argv[4])) ? "yes": "no") << std::endl;
    if(dfs.hasPathTo(atoi(argv[4]))){
        auto path = dfs.pathTo(atoi(argv[4]));
        std::cout << "source " << atoi(argv[3]) << " dest " << atoi(argv[4]) << std::endl;
        for(auto v : path)
        {
            std::cout << v << std::endl;
        }
    }

    dfs.print();
    return 0;
}