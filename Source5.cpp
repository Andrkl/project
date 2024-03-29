#include <iostream>
#include <ctime>
#include <chrono>
#include "Graph.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    string usr1 = "����";
    string usr2 = "������";
    string usr3 = "�����";
    string usr4 = "����";
    string usr5 = "����";

    Graph users;

    users.addUser(usr1);
    users.addUser(usr2);
    users.addUser(usr3);
    users.addUser(usr4);
    users.addUser(usr5);

    users.addEdge(usr1, usr2, 1);
    users.addEdge(usr2, usr3, 1);
    users.addEdge(usr3, usr4, 1);
    users.addEdge(usr4, usr5, 1);

    auto start = chrono::high_resolution_clock::now(); 
    users.showFriends(3);
    auto finish = chrono::high_resolution_clock::now(); 
    chrono::duration<double> elapsed = finish - start;
    cout << "Elapsed time: " << elapsed.count() << " sec" << endl; 

    return 0;
}
Graph.h

#pragma once
#include <iostream>
#define SIZE 6

class Graph {
public:
    Graph() {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                matrix[i][j] = 0;
        vertexCount = 0;
    }
    int getIndex(std::string name);
    int getEdgeWeight(std::string v1, std::string v2);
    void showFriends(int handshake);
    void addUser(std::string name);
    void addEdge(std::string v1, std::string v2, int weight);
private:
    void findFriends(std::string start, std::string current, bool visited[], int handshake, int path);
    bool edgeExists(std::string v1, std::string v2);
    bool vertexExists(std::string name);
    int matrix[SIZE][SIZE]; 
    std::string vertexesName[SIZE];
    int vertexCount; 
};
Graph.cpp

#include "Graph.h"

#include <iostream>

int Graph::getIndex(std::string name)
{
    for (int i = 0; i < vertexCount; i++)
    {
        if (vertexesName[i] == name)
            return i;
    }
    return -1;
}

int Graph::getEdgeWeight(std::string v1, std::string v2)
{
    return matrix[getIndex(v1)][getIndex(v2)];
}

void Graph::addUser(std::string name)
{
    vertexesName[vertexCount++] = name;
}

void Graph::addEdge(std::string v1, std::string v2, int weight)
{
    matrix[getIndex(v1)][getIndex(v2)] = weight;
    matrix[getIndex(v2)][getIndex(v1)] = weight;
}

bool Graph::edgeExists(std::string v1, std::string v2)
{
    return matrix[getIndex(v1)][getIndex(v2)] > 0;
}

bool Graph::vertexExists(std::string name)
{
    for (int i = 0; i < vertexCount; i++)
        if (vertexesName[i] == name)
            return true;
    return false;
}

void Graph::showFriends(int handshake)
{
    std::cout << "���� ������������� �������� ����� ��� �����������:" << std::endl;

    bool visited[SIZE];
    for (int i = 0; i < SIZE; i++)
        visited[i] = false;

    int path = 0;
    for (int i = 0; i < vertexCount - 1; i++)
    {
        findFriends(vertexesName[i], vertexesName[i], visited, handshake, path);
        visited[i] = true;
    }
}

void Graph::findFriends(std::string start, std::string current, bool visited[], int handshake, int path)
{
    if (path <= handshake && path > 0)
    {
        std::cout << start << " & " << current << std::endl;
    }

    if (path > handshake)
        return;

    visited[getIndex(current)] = true;
    for (int i = 0; i < vertexCount; i++)
    {
        if (edgeExists(current, vertexesName[i]) && !visited[i])
        {
            path += getEdgeWeight(current, vertexesName[i]);
            findFriends(start, vertexesName[i], visited, handshake, path);
        }
    }
    visited[getIndex(current)] = false;
}