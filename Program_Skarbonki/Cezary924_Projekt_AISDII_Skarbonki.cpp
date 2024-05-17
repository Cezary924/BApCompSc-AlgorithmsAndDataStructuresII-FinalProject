#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Iterator
{
public:
    virtual ~Iterator() { ; }
    Iterator() { ; }
    virtual bool IsDone() = 0;
    virtual T &operator*() = 0;
    virtual void operator++() = 0;
};

//--------------------------------------

class Vertex
{
    int number;

public:
    int weight;
    int zmienna_pomocnicza;
    string label;
    Vertex(int n);
    int Number() const;
};

Vertex::Vertex(int n)
{
    number = n;
}

int Vertex::Number() const
{
    return number;
}

//--------------------------------------

class Edge
{
protected:
    Vertex *v0;
    Vertex *v1;

public:
    int weight;
    string label;
    Edge(Vertex *V0, Vertex *V1);
    Vertex *V0() { return v0; };
    Vertex *V1() { return v1; };
    Vertex *Mate(Vertex *v);
};

Edge::Edge(Vertex *V0, Vertex *V1)
{
    v0 = V0;
    v1 = V1;
}

Vertex *Edge::Mate(Vertex *v)
{
    if (v == v0)
        return v1;
    else
        return v0;
}

//--------------------------------------

template <typename T>
class Visitor
{
public:
    virtual void Visit(T *element) = 0;
    virtual bool IsDone() const { return false; }
};

class CountingVisitor : public Visitor<Vertex>
{
    int counter;

public:
    CountingVisitor() { counter = 0; }
    void Visit(Vertex *element) { cout << element->Number() << " "; counter++; }
    int GetCounterValue() { return counter; }
};

//--------------------------------------

class GraphAsMatrix
{
    vector<Vertex *> vertices;
    vector<vector<Edge *>> adjacencyMatrix;
    bool isDirected;
    int numberOfVertices;
    int numberOfEdges = 0;

    class AllVerticesIter : public Iterator<Vertex>
    {
        GraphAsMatrix &owner;
        int current;

    public:
        AllVerticesIter(GraphAsMatrix &_owner) : owner(_owner)
        {
            current = 0;
        }

        bool IsDone()
        {
            if(current >= owner.NumberOfVertices())
                return true;
            else
                return false;
        }
        Vertex &operator*()
        {
            return *owner.
            vertices[current];
        }
        void operator++() { current++; }
    };

    class AllEdgesIter : public Iterator<Edge>
    {
        GraphAsMatrix &owner;
        int row;
        int col;

    public:
        void next()
        {
            int _row = 0;
            if (row >= 0)
                _row = row;
            for (int i = _row; i < owner.NumberOfVertices(); i++)
            {
                int _col = 0;
                if (i == row)
                    _col = col;
                for (int j = _col; j < owner.NumberOfVertices(); j++)
                {
                    
                    if (i == row && j == col)
                    {
                        if ((i == owner.NumberOfVertices() - 1) && (j == owner.NumberOfVertices() - 1))
                        {
                            row = owner.NumberOfVertices();
                            col = owner.NumberOfVertices();
                            return;
                        }
                        continue;
                    }
                    else if (owner.adjacencyMatrix[i][j] != NULL)
                    {
                        row = i;
                        col = j;
                        return;
                    }
                    if ((i == owner.NumberOfVertices() - 1) && (j == owner.NumberOfVertices() - 1))
                    {
                        row = owner.NumberOfVertices();
                        col = owner.NumberOfVertices();
                        return;
                    }
                }
            }
        }
        AllEdgesIter(GraphAsMatrix &_owner) : owner(_owner)
        {
            row = -1;
            col = -1;
        }
        bool IsDone()
        {
            if (row == owner.NumberOfVertices())
            {
                if (col == owner.NumberOfVertices())
                    return true;
            }
            else
                return false;
        }
        Edge &operator*()
        {
            return *owner.adjacencyMatrix[row][col];
        }
        void operator++() { next(); }
    };

    class EmanEdgesIter : public Iterator<Edge>
    {
        GraphAsMatrix &owner;
        int row;
        int col;

    public:
        void next()
        {
            int _col = 0;
            if (col >= 0)
                _col = col;
            for (int j = _col; j < owner.NumberOfVertices(); j++)
            {
                if (j == col)
                {
                    if (j == owner.NumberOfVertices() - 1)
                    {
                        col = owner.NumberOfVertices();
                        return;
                    }
                    continue;
                }
                else if (owner.adjacencyMatrix[row][j] != NULL)
                {
                    col = j;
                    return;
                }
                if (j == owner.NumberOfVertices() - 1)
                {
                    col = owner.NumberOfVertices();
                    return;
                }
            }
        }
        EmanEdgesIter(GraphAsMatrix &_owner, int v) : owner(_owner)
        {
            row = v;
            col = -1;
        }
        bool IsDone()
        {
            if (col == owner.NumberOfVertices())
                return true;
            else
                return false;
        }
        Edge &operator*()
        {
            return *owner.adjacencyMatrix[row][col];
        }
        void operator++() { next(); }
    };

    class InciEdgesIter : public Iterator<Edge>
    {
        GraphAsMatrix &owner;
        int row;
        int col;

    public:
        void next()
        {
            int _row = 0;
            if (row >= 0)
                _row = row;
            for (int i = _row; i < owner.NumberOfVertices(); i++)
            {
                if (i == row)
                {
                    if (i == owner.NumberOfVertices() - 1)
                    {
                        row = owner.NumberOfVertices();
                        return;
                    }
                    continue;
                }
                else if (owner.adjacencyMatrix[i][col] != NULL)
                {
                    row = i;
                    return;
                }
                if (i == owner.NumberOfVertices() - 1)
                {
                    row = owner.NumberOfVertices();
                    return;
                }
            }
        }
        InciEdgesIter(GraphAsMatrix &_owner, int v) : owner(_owner)
        {
            row = -1;
            col = v;
        }
        bool IsDone()
        {
            if (row == owner.NumberOfVertices())
                return true;
            else
                return false;
        }
        Edge &operator*()
        {
            return *owner.adjacencyMatrix[row][col];
        }
        void operator++() { next(); }
    };

public:
    GraphAsMatrix(int n, bool b);
    int NumberOfVertices();
    bool IsDirected();
    int NumberOfEdges();
    bool IsEdge(int u, int v);
    void MakeNull();
    void AddEdge(int u, int v);
    void AddEdge(Edge *edge);
    Edge *SelectEdge(int u, int v);
    Vertex *SelectVertex(int v);

    Iterator<Vertex> &VerticesIter() {return *new AllVerticesIter(*this);}
    Iterator<Edge> &EdgesIter() {return *new AllEdgesIter(*this);};
    Iterator<Edge> &EmanatingEdgesIter(int v) {return *new EmanEdgesIter(*this, v);};
    Iterator<Edge> &IncidentEdgesIter(int v) {return *new InciEdgesIter(*this, v);};

    int DFS(Vertex *v);
    void DFS1(Vertex *v, vector<bool> &visited);
    void DFS1_visitor(CountingVisitor *visitor, Vertex *v, vector<bool> &visited);

    void DFS_Spanning_Tree(Vertex *v);
    void DFS_Spanning_Tree_1(Vertex *v, vector<bool> &visited, vector<int> &parent);

    bool IsConnected();
};

GraphAsMatrix::GraphAsMatrix(int n, bool b)
{
    numberOfVertices = n;
    vertices.reserve(NumberOfVertices());
    adjacencyMatrix.reserve(NumberOfVertices());
    for (int i = 0; i < NumberOfVertices(); i++)
    {
        Vertex *v = new Vertex(i);
        vertices[i] = v;
        adjacencyMatrix[i].reserve(NumberOfVertices());
        for (int j = 0; j < NumberOfVertices(); j++)
            adjacencyMatrix[i][j] = NULL;
    }
    isDirected = b;
}

int GraphAsMatrix::NumberOfVertices()
{
    return numberOfVertices;
}

bool GraphAsMatrix::IsDirected()
{
    return isDirected;
}

int GraphAsMatrix::NumberOfEdges()
{
    return numberOfEdges;
}

bool GraphAsMatrix::IsEdge(int u, int v)
{
    if (IsDirected())
    {
        for (int i = 0; i < NumberOfVertices(); i++)
            for (int j = 0; j < NumberOfVertices(); j++)
                if (adjacencyMatrix[i][j] != NULL)
                    if (adjacencyMatrix[i][j]->V0()->Number() == u && adjacencyMatrix[i][j]->V1()->Number() == v)
                        return true;
        return false;
    }
    else
    {
        for (int i = 0; i < NumberOfVertices(); i++)
            for (int j = 0; j < NumberOfVertices(); j++)
                if (adjacencyMatrix[i][j] != NULL)
                {
                    if (adjacencyMatrix[i][j]->V0()->Number() == u && adjacencyMatrix[i][j]->V1()->Number() == v)
                        return true;
                    else if (adjacencyMatrix[i][j]->V0()->Number() == v && adjacencyMatrix[i][j]->V1()->Number() == u)
                        return true;
                }

        return false;
    }
}

void GraphAsMatrix::MakeNull()
{
    for (int i = 0; i < NumberOfVertices(); i++)
        for (int j = 0; j < NumberOfVertices(); j++)
            adjacencyMatrix[i][j] = NULL;
    numberOfEdges = 0;
}

void GraphAsMatrix::AddEdge(int u, int v)
{
    if (!IsEdge(u, v))
    {
        if (IsDirected())
        {
            Edge *e = new Edge(vertices[u], vertices[v]);
            adjacencyMatrix[u][v] = e;
        }
        else
        {
            Edge *e1 = new Edge(vertices[u], vertices[v]);
            //Edge *e2 = new Edge(vertices[v], vertices[u]);
            adjacencyMatrix[u][v] = e1;
            adjacencyMatrix[v][u] = e1;
        }
        numberOfEdges++;
    }
}

void GraphAsMatrix::AddEdge(Edge *edge)
{
    Vertex *v1 = edge->V0();
    Vertex *v2 = edge->V1();
    int u = v1->Number();
    int v = v2->Number();
    AddEdge(u, v);
}

Edge *GraphAsMatrix::SelectEdge(int u, int v)
{
    if (IsEdge(u, v))
        return adjacencyMatrix[u][v];
}

Vertex *GraphAsMatrix::SelectVertex(int v)
{
    if (0 <= v && v < NumberOfVertices())
        return vertices[v];
}

int GraphAsMatrix::DFS(Vertex *v)
{
    vector<bool> visited;
    visited.reserve(this->NumberOfVertices());
    for (int i = 0; i < this->NumberOfVertices(); i++)
        visited[i] = false;
    cout << "Odwiedzone wierzcholki grafu: ";
    CountingVisitor cv = CountingVisitor();
    //DFS1(v, visited);
    DFS1_visitor(&cv, v, visited);
    /*for (int i = 0; i < this->NumberOfVertices(); i++)
        if (visited[i] == false)
            //DFS1(this->SelectVertex(i), visited);
            DFS1_visitor(&cv, this->SelectVertex(i), visited);*/
    cout << "   |    Liczba odwiedzonych wierzcholkow: " << cv.GetCounterValue();
    cout << endl;
    return cv.GetCounterValue();
}

void GraphAsMatrix::DFS1(Vertex *v, vector<bool> &visited)
{
    cout << v->Number() << " ";
    visited[v->Number()] = true;
    Iterator<Edge> &it = this->EmanatingEdgesIter(v->Number());
    ++it;
    vector<bool> neighbours;
    neighbours.reserve(this->NumberOfVertices());
    for (int i = 0; i < this->NumberOfVertices(); i++)
        neighbours[i] = false;
    while (!it.IsDone())
    {
        if ((*it).V1()->Number() != v->Number())
            neighbours[(*it).V1()->Number()] = true;
        else
            neighbours[(*it).V0()->Number()] = true;
        ++it;
    }
    delete &it;
    for (int i = 0; i < this->NumberOfVertices(); i++)
        if (neighbours[i] == true && visited[i] == false)
            DFS1(this->SelectVertex(i), visited);
}

void GraphAsMatrix::DFS1_visitor(CountingVisitor *visitor, Vertex *v, vector<bool> &visited)
{
    visitor->Visit(v);
    visited[v->Number()] = true;
    Iterator<Edge> &it = this->EmanatingEdgesIter(v->Number());
    ++it;
    vector<bool> neighbours;
    neighbours.reserve(this->NumberOfVertices());
    for (int i = 0; i < this->NumberOfVertices(); i++)
        neighbours[i] = false;
    while (!it.IsDone())
    {
        if ((*it).V1()->Number() != v->Number())
            neighbours[(*it).V1()->Number()] = true;
        else
            neighbours[(*it).V0()->Number()] = true;
        ++it;
    }
    delete &it;
    //cout << endl;
    for (int i = 0; i < this->NumberOfVertices(); i++)
    {
        //if (neighbours[i] == true)
            //cout << i << " jest sasiadem " << v->Number() << endl;
        if (neighbours[i] == true && visited[i] == false)
            DFS1_visitor(visitor, this->SelectVertex(i), visited);
    }
}

bool GraphAsMatrix::IsConnected()
{
    if (!this->IsDirected())
    {
        if (this->NumberOfVertices() != DFS(this->SelectVertex(0)))
            return false;
        return true;
    }
    for (int i = 0; i < this->NumberOfVertices(); i++)
    {
        if (this->NumberOfVertices() != DFS(this->SelectVertex(i)))
            return false;
    }
    return true;
}

void GraphAsMatrix::DFS_Spanning_Tree(Vertex *v)
{
    //cout << "test\n";
    if (!this->IsConnected())
        return;
    //cout << "test3\n";
    vector<bool> visited;
    visited.reserve(this->NumberOfVertices());
    for (int i = 0; i < this->NumberOfVertices(); i++)
        visited[i] = false;
    vector<int> parent;
    parent.reserve(this->NumberOfVertices());
    for (int i = 0; i < this->NumberOfVertices(); i++)
        parent[i] = -1;
    //cout << "test2\n";
    DFS_Spanning_Tree_1(v, visited, parent);
}

void GraphAsMatrix::DFS_Spanning_Tree_1(Vertex *v, vector<bool> &visited, vector<int> &parent)
{
    visited[v->Number()] = true;
    Iterator<Edge> &it = this->EmanatingEdgesIter(v->Number());
    ++it;
    vector<bool> neighbours;
    neighbours.reserve(this->NumberOfVertices());
    for (int i = 0; i < this->NumberOfVertices(); i++)
        neighbours[i] = false;
    while (!it.IsDone())
    {
        if ((*it).V1()->Number() != v->Number())
            neighbours[(*it).V1()->Number()] = true;
        else
            neighbours[(*it).V0()->Number()] = true;
        ++it;
    }
    delete &it;
    for (int i = 0; i < this->NumberOfVertices(); i++)
    {
        if (neighbours[i] == true && visited[i] == false)
        {
            parent[i] = v->Number();
            cout << "Rodzicem wierzcholka " << i << " jest wierzcholek " << v->Number() << ".\n";
            DFS_Spanning_Tree_1(this->SelectVertex(i), visited, parent);
        }
    }
}

//--------------------------------------

void it_AVI_print(GraphAsMatrix *g1)
{
    Iterator<Vertex> &it = g1->VerticesIter();
    cout << "Wierzcholki grafu wypisane przy pomocy iteratora AVI (nr, waga): ";
    while (!it.IsDone())
    {
        cout << "(" << (*it).Number() << ","<< (*it).weight << ") ";
        ++it;
    }
    cout << endl;
    delete &it;
}

void it_AEI_print(GraphAsMatrix *g1)
{
    Iterator<Edge> &it = g1->EdgesIter();
    cout << "Krawedzie grafu wypisane przy pomocy iteratora AEI (nr v0, nr v1): ";
    ++it;
    while (!it.IsDone())
    {
        //cout << "(" << (*it).V0()->Number() << ","<< (*it).V1()->Number() << ","<< (*it).weight << ") ";
        cout << "(" << (*it).V0()->Number() << ","<< (*it).V1()->Number() << ") ";
        ++it;
    }
    cout << endl;
    delete &it;
}

void it_EEI_print(GraphAsMatrix *g1, int v)
{
    Iterator<Edge> &it = g1->EmanatingEdgesIter(v);
    cout << "Krawedzie grafu wypisane przy pomocy iteratora EEI wychodzace z wierzcholka nr " << v << " (nr v0, nr v1): ";
    ++it;
    while (!it.IsDone())
    {
        //cout << "(" << (*it).V0()->Number() << ","<< (*it).V1()->Number() << ","<< (*it).weight << ") ";
        cout << "(" << (*it).V0()->Number() << ","<< (*it).V1()->Number() << ") ";
        ++it;
    }
    cout << endl;
    delete &it;
}

void it_IEI_print(GraphAsMatrix *g1, int v)
{
    Iterator<Edge> &it = g1->IncidentEdgesIter(v);
    cout << "Krawedzie grafu wypisane przy pomocy iteratora IEI dochodzace do wierzcholka nr " << v << " (nr v0, nr v1): ";
    ++it;
    while (!it.IsDone())
    {
        //cout << "(" << (*it).V0()->Number() << ","<< (*it).V1()->Number() << ","<< (*it).weight << ") ";
        cout << "(" << (*it).V0()->Number() << ","<< (*it).V1()->Number() << ") ";
        ++it;
    }
    cout << endl;
    delete &it;
}

//--------------------------------------

int main()
{
    cout << "|=========================================|" << endl;
    cout << "|             Projekt AISD II             |" << endl;
    cout << "|-----------------------------------------|" << endl;
    cout << "|                 Cezary924               |" << endl;
    cout << "|-----------------------------------------|" << endl;
    cout << "|               \"Skarbonki\"               |" << endl;
    cout << "|=========================================|" << endl;
    
    cout << " Wprowadz liczbe skarbonek: ";
    int liczba_skarbonek;
    cin >> liczba_skarbonek;
    cout << "|-----------------------------------------|" << endl;
    if (liczba_skarbonek <= 0 || liczba_skarbonek > 1000000)
    {
        cout << "|     Nieprawidlowa liczba skarbonek!     |" << endl;
        cout << "|=========================================|" << endl;
        return 1;
    }

    cout << " Wprowadz numery skarbonek: " << endl;
    int klucze[liczba_skarbonek];
    for (int i = 0; i < liczba_skarbonek; i++)
    {
        cout << "    " << i+1 << " -> ";
        cin >> klucze[i];
        if (klucze[i] <= 0 || klucze[i] > liczba_skarbonek)
        {
            cout << "|-----------------------------------------|" << endl;
            cout << "|      Nieprawidlowy numer skarbonki!     |" << endl;
            cout << "|=========================================|" << endl;
            return 1;
        }
        klucze[i]--;
    }

    cout << "|-----------------------------------------|" << endl;
    cout << "|             Tworzenie grafu             |" << endl;
    GraphAsMatrix graf = GraphAsMatrix(liczba_skarbonek, true);
    for (int i = 0; i < liczba_skarbonek; i++)
        graf.AddEdge(i, klucze[i]);
    cout << "|-----------------------------------------|" << endl;

    int liczba_skarbonek_do_rozbicia = 0;
    for (int i = 0; i < graf.NumberOfVertices(); i++)
        graf.SelectVertex(i)->zmienna_pomocnicza = -1;
    for (int i = 0; i < graf.NumberOfVertices(); i++)
    {
        int j = i;
        while (graf.SelectVertex(j)->zmienna_pomocnicza == -1)
        {
            graf.SelectVertex(j)->zmienna_pomocnicza = i;
            Iterator<Edge> &it = graf.EmanatingEdgesIter(j);
            ++it;
            j = (*it).V1()->Number();
            delete &it;
        }
        if (graf.SelectVertex(j)->zmienna_pomocnicza == i)
            liczba_skarbonek_do_rozbicia++;
    }
    for (int i = 0; i < graf.NumberOfVertices(); i++)
        graf.SelectVertex(i)->zmienna_pomocnicza = -1;
    
    cout << " Minimalna liczba skarbonek do rozbicia: " << liczba_skarbonek_do_rozbicia << endl;

    cout << "|=========================================|" << endl;
    return 0;
}