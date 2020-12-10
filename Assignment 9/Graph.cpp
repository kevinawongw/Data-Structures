#include <iostream>
#include <string>
#include <queue>
#include "Graph.hpp"

using namespace std;

Graph::Graph(){

}

Graph::~Graph(){

}

void Graph::addVertex(std::string name)
{
    vertex* newVertex= new vertex;
    newVertex->name=name;
    vertices.push_back(*newVertex);
}

void Graph::addEdge(std::string v1, std::string v2, int distance)
{
    vertex* point=findVertex(v1);
    Edge* newEdge= new Edge;
    vertex* ptCity2=findVertex(v2);
    newEdge->v=ptCity2;
    newEdge->distance=distance;
    point->Edges.push_back(*newEdge);
}

void Graph::displayEdges(){
    string sent="";
    for (int i=0;i<vertices.size();i++){
        cout<< vertices[i].name << "-->";
        for (int j=0;j<vertices[i].Edges.size();j++){
            sent+=vertices[i].Edges[j].v->name+" ("+to_string(vertices[i].Edges[j].distance)+" miles)***";
        }
        sent=sent.substr(0,sent.size()-3);
        cout<<sent<<endl;    
        sent="";
    }
}

void Graph::printDFT()
{
    for (int i=0;i<vertices.size();i++){
        if (!vertices[i].visited){
            DFT_traversal(&vertices[i]);
        }
    }
    setAllVerticesUnvisited();
}

void Graph::printBFT()
{
    for (int i=0;i<vertices.size();i++){
        if (!vertices[i].visited){
            BFT_traversal(&vertices[i]);
        }
    }
    setAllVerticesUnvisited();
}

void Graph::BFT_traversal(vertex* ve)
{
    queue<vertex*>a;
    cout << ve->name << endl;
    ve->visited = true;
    a.push(ve);
    for (int i=0;i<ve->Edges.size();i++){
        if (!a.front()->Edges[i].v->visited){
            ve->Edges[i].v->visited=true;
            a.push(ve->Edges[i].v);
            cout << ve->Edges[i].v->name <<endl;
            a.front()->Edges[i].v->visited=true;
        }
        
    }
    a.pop();
    while (!a.empty()){
        for(int j=0;j<a.front()->Edges.size();j++){
            if  (!a.front()->Edges[j].v->visited){
                a.front()->Edges[j].v->visited=true;
                a.push(a.front()->Edges[j].v);   
                cout << a.front()->Edges[j].v->name <<endl;
                
            }    
        }    
        a.pop();    
    }    
}


void Graph::setAllVerticesUnvisited(){
    for (int i=0;i<vertices.size();i++){
        vertices[i].visited=false;
    }
}

void Graph::DFT_traversal(vertex* ve)
{
    if (!ve->visited){
        cout<<ve->name<<endl;
        ve->visited=true;
    }
    for (int i=0;i<ve->Edges.size();i++){
        if(!ve->Edges[i].v->visited){
            cout << ve->Edges[i].v->name << endl;
            ve->Edges[i].v->visited=true;
            DFT_traversal(ve->Edges[i].v);
        }
    }
}

vertex* Graph::findVertex(string name){
    for (int i=0;i<vertices.size();i++){
        if (vertices[i].name==name){
            return &vertices[i];
        }
    }
}



