/*#ifndef MAZE_GENERATION_HPP
#define MAZE_GENERATION_HPP

#include <iostream>
#include<algorithm>
#include<random>
#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include "../Constants.hpp"

#define pii std::pair<int,int>
#define mp std::make_pair
#define pb push_back
#define ff first
#define ss second

class Node{
public:
    int row;
    int col;
    bool neighbors[4] = {false, false, false, false}; //{U, L, D, R}
    int id;
    Node(int r, int c){
        row = r;
        col = c;
        id = row * MAZE_COLUMNS + col;
    }

    int getTileId(){
        return 8*neighbors[0] + 4*neighbors[1] + 2*neighbors[2] + neighbors[3];
    }
};

class Edge{
public:
    Node* src;
    Node* dst;
    int id;
    Edge(Node* node1, Node* node2){
        src = node1;
        dst = node2;
    }
        
};

class UnionSubset{
public:
    Node* root;
    Node* parent;
    int size = 1;

    UnionSubset(Node* node){
        root = node;
        parent = node;
    }

    static Node* find(vector<UnionSubset*> vec, Node *node){
        //path compression included
        if(vec[node->id]->root != node){
            vec[node->id]->root = find(vec, vec[node->id]->root);
        }
        return vec[node->id]->root;
    }


    static int union2(vector<UnionSubset*> vec, Node *node1, Node* node2){
        Node* root1 = find(vec, node1);
        Node* root2 = find(vec, node2);
        if(root1 == root2) return vec[root1->id]->size;
        int size1 = vec[root1->id]->size;
        int size2 = vec[root2->id]->size;
        if(size1 < size2){
            vec[root1->id]->root = root2;
            vec[root1->id]->parent = root2;
            vec[root2->id]->size = size1 + size2;
        }
        else if(size1 >= size2){
            vec[root2->id]->root = root1;
            vec[root2->id]->parent = root1;
            vec[root1->id]->size = size1 + size2;
        }

        return size1 + size2;
    }
};

class Graph{
public:
    vector<vector<Node*>> nodes;
    vector<Edge*> edges;
    vector<Edge*> finalEdges;
    vector<UnionSubset*> vec_union;
    int v = MAZE_ROWS * MAZE_COLUMNS;
    int e = (MAZE_ROWS - 1) * MAZE_COLUMNS + (MAZE_COLUMNS - 1) * MAZE_ROWS;
    



    Graph(int seed){

        srand(seed);
        Node* tempNode1;
        Edge* tempEdge1;
        UnionSubset* tempUnionSubset;
        for(int i = 0;i < MAZE_ROWS; i++){
            vector<Node*> v1;
            for(int j = 0;j < MAZE_COLUMNS; j++){
                v1.pb(new Node(i, j));
            }
            nodes.pb(v1);
        }

        for(int i = 0; i < MAZE_ROWS; i++){
            for(int j = 0; j < MAZE_COLUMNS - 1; j++){
                edges.pb(new Edge(nodes[i][j], nodes[i][j+1]));
            }
        }

        for(int i = 0; i < MAZE_ROWS - 1; i++){
            for(int j = 0; j < MAZE_COLUMNS; j++){
                edges.pb(new Edge(nodes[i][j], nodes[i + 1][j]));
            }
        }

       

        shuffle(edges.begin(), edges.end(), default_random_engine(seed));
        for(int i = 0; i < MAZE_ROWS;i++){
            for(int j = 0; j<MAZE_COLUMNS;j++){
                vec_union.pb(new UnionSubset(nodes[i][j]));
            }
        }

        for(int i = 0;i < edges.size();i++){
            Edge* edge = edges[i];
            Node* node1 = edge->src;
            Node* node2 = edge->dst;

            if(UnionSubset::union2(vec_union, node1, node2) >= v);
                break;
        }
        int cnt = 0;

        for(int i = 0;i < MAZE_ROWS;i++){
            for(int j = 0;j < MAZE_COLUMNS;j++){
                tempNode1 = vec_union[i*MAZE_COLUMNS + j]->parent;
                if(tempNode1 == nodes[i][j]){cnt++; continue;}
                else{
                    tempEdge1 = new Edge(nodes[i][j], tempNode1);
                    if(tempNode1->row == i){
                        if(tempNode1->col == j - 1){
                            nodes[i][j]->neighbors[1] = true;
                            nodes[i][j-1]->neighbors[3] = true;
                        }
                        else if(tempNode1->col == j + 1){
                            nodes[i][j]->neighbors[3] = true;
                            nodes[i][j+1]->neighbors[1] = true;
                        }
                        else cout<<"\n\nError, edges not adjacent\n\n";
                    }

                    else if(tempNode1->row == i - 1){
                        if(tempNode1->col == j){
                            nodes[i][j]->neighbors[0] = true;
                            nodes[i-1][j]->neighbors[2] = true;
                        }
                        else cout<<"\n\nError, edges not adjacent\n\n";
                    }

                    else if(tempNode1->row == i + 1){
                        if(tempNode1->col == j){
                            nodes[i][j]->neighbors[2] = true;
                            nodes[i+1][j]->neighbors[0] = true;
                        }
                        else cout<<"\n\nError, edges not adjacent\n\n";
                    }
                    finalEdges.pb(tempEdge1);
                }
            }
        }

        cout<<"cnt: "<<cnt;
        
        
    }

        
        
};

//class MazeGeneration{

    public:
        // 20*25 Current dimensions
        static const int Rows    =    MAZE_ROWS;
        static const int Columns = MAZE_COLUMNS;
        int Visited[Rows][Columns];
        // Will use Visited array to store the TileMap
        
        std::string Neighbours[Rows][Columns];
        
        // Neighbours[..][..]
        // D will be Down Neighbour
        // R will be Right Neighbour

        int startX, startY;
        std::stack< pii > cells;

        MazeGeneration(); // Initialize Visited to 0
        
        void Generate();
        void PushIntoArray(pii x, pii y);
        void GenerateTileMap();
        bool ContainsChar(int i, int j, std::string s);
        void WriteToText();
        void MazeGenerator();

};

class MazeGenerator{


public:
    MazeGenerator(int seed){

        unique_ptr<Graph> graph = make_unique<Graph>(seed);
        vector<Edge*> edgeList = graph->finalEdges;

        cout<<"\n\n\n\n";
        //for(auto edge:edgeList){
        //  cout<<"Src: "<<edge->src->row<<" "<<edge->src->col<<"\n";
        //  cout<<"Dst: "<<edge->dst->row<<" "<<edge->dst->col<<"\n";
        // cout<<"\n";
        }

        cout<<"\n\n\n";
        vector<vector<Node*>> nodeList = graph->nodes;

        std::string filename = "Maze.txt";
        std::ofstream output(filename);

        for(int i = 0;i<MAZE_ROWS;i++){
            for(int j = 0;j<MAZE_COLUMNS;j++){
                output<< nodeList[i][j]->getTileId();
                if(j == MAZE_COLUMNS - 1) output<<"\n";
                else output<<",";
            }

        }

        output.close();

        
    }







};

#endif
*/

#ifndef MAZE_GENERATION_HPP
#define MAZE_GENERATION_HPP

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "../Constants.hpp"

#define pii std::pair<int,int>
#define mp std::make_pair
#define pb push_back
#define ff first
#define ss second

class MazeGeneration{

    public:
        // 20*25 Current dimensions
        static const int Rows    =    MAZE_ROWS;
        static const int Columns = MAZE_COLUMNS;
        int Visited[Rows][Columns];
        // Will use Visited array to store the TileMap
        
        bool Neighbours[Rows][Columns][4];   //Order: U,L,D,R
        
        // Neighbours[..][..]
        // D will be Down Neighbour
        // R will be Right Neighbour

        int startX, startY;
        std::stack< pii > cells;
        int random_seed;

        MazeGeneration(int seed); // Initialize Visited to 0
        
        void Generate();
        void PushIntoArray(pii x, pii y);
        void GenerateTileMap();
        bool ContainsChar(int i, int j, std::string s);
        void WriteToText();
        void MazeGenerator();

};

#endif 