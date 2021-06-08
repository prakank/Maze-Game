#pragma once
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include <cstddef>
#include <memory>
#include "../Constants.hpp"

#define pii std::pair<int,int>
#define mp std::make_pair
#define pb push_back
#define ff first
#define ss second

using namespace std;

class Node{
public:
    int row;
    int col;
    bool neighbours[4] = {false, false, false, false}; //{U, L, D, R}
    int id;
    Node(int r, int c){
        row = r;
        col = c;
        id = row * MAZE_COLUMNS + col;
    }

    int getTileId(){
        return 8*(!neighbours[0]) + 4*(!neighbours[1]) + 2*(!neighbours[2]) + (!neighbours[3]);
    }

    static void join(Node* a, Node* b){
        if(!((a->row == b-> row && ((a->col - b->col)*(a->col - b->col)==1)) || (a->col == b-> col && ((a->row - b->row)*(a->row - b->row)==1)))) {cout<<"\n\n\nNodes not adjacent\n\n\n"; return;}
        if(a->row == b->row){
            if(a->col == b->col + 1){
                a->neighbours[1] = true;
                b->neighbours[3] = true;
            }
            else{
                a->neighbours[3] = true;
                b->neighbours[1] = true;
            }
        }

        else{
            if(a->row == b->row - 1){
                a->neighbours[2] = true;
                b->neighbours[0] = true;
            }
            else{
                a->neighbours[0] = true;
                b->neighbours[2] = true;
            }
        }
    }

    bool isWallEdge(int edge){  //edge takes values(0,1,2,3) corresponding to U,L,D,R
        if(edge == 0)
            {if(this->row == 0) return true;}
        else if(edge == 1)
            {if(this->col == 0) return true;}
        else if(edge == 2)
            {if(this->row == MAZE_ROWS - 1) return true;}
        else if(edge == 3)
            {if(this->col == MAZE_COLUMNS - 1) return true;}
        
        return false;
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
    int size;

    UnionSubset(Node* node){
        root = node;
        size = 1;
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
            Node::join(node1, node2);
            vec[root2->id]->size = size1 + size2;

            cout<<"Node3(1) joined("<<node1->row<<", "<<node1->col<<") and ("<<node2->row<<", "<<node2->col<<")\n";
        }
        else if(size1 >= size2){
            vec[root2->id]->root = root1;
            Node::join(node1, node2);
            //vec[node2->id]->parent = node1;
            vec[root1->id]->size = size1 + size2;
            cout<<"Node3(2) joined ("<<node2->row<<", "<<node2->col<<") and ("<<node1->row<<", "<<node1->col<<")\n";
        }

        return size1 + size2;
    }
};

class Graph{
public:
    vector<vector<Node*>> nodes;
    vector<Edge*> edges;
    //vector<Edge*> finalEdges;
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
        cout<<"\n\n Edges:\n";

        for(int i = 0; i< edges.size();i++){
            cout<<"("<<edges[i]->src->row <<" "<<edges[i]->src->col<<"), ("<<edges[i]->dst->row<<" "<<edges[i]->dst->col<<")\n";
        }
        for(int i = 0; i < MAZE_ROWS;i++){
            for(int j = 0; j<MAZE_COLUMNS;j++){
                vec_union.pb(new UnionSubset(nodes[i][j]));
            }
        }

        for(int i = 0;i < edges.size();i++){
            Edge* edge = edges[i];
            Node* node1 = edge->src;
            Node* node2 = edge->dst;

            cout<<"vec_union.size() "<<vec_union.size();
            cout<<"node1: "<<node1->row<<" "<<node1->col<<"\n";
            cout<<"node2: "<<node2->row<<" "<<node2->col<<"\n";
            cout<<"\n\n";
            int x = UnionSubset::union2(vec_union, node1, node2);
            cout<<"x: "<<x<<"\n";
            if(x >= v)
                {break;}
        }
        int cnt = 0;

        /*for(int i = 0;i < MAZE_ROWS;i++){
            for(int j = 0;j < MAZE_COLUMNS;j++){
                tempNode1 = vec_union[i*MAZE_COLUMNS + j]->parent;
                if(tempNode1 == nodes[i][j]){cnt++; continue;}
                else{
                    tempEdge1 = new Edge(nodes[i][j], tempNode1);
                    if(tempNode1->row == i){
                        if(tempNode1->col == j - 1){
                            nodes[i][j]->neighbours[1] = true;
                            nodes[i][j-1]->neighbours[3] = true;
                        }
                        else if(tempNode1->col == j + 1){
                            nodes[i][j]->neighbours[3] = true;
                            nodes[i][j+1]->neighbours[1] = true;
                        }
                        else cout<<"\n\nError, edges not adjacent\n\n";
                    }

                    else if(tempNode1->row == i - 1){
                        if(tempNode1->col == j){
                            nodes[i][j]->neighbours[0] = true;
                            nodes[i-1][j]->neighbours[2] = true;
                        }
                        else cout<<"\n\nError, edges not adjacent\n\n";
                    }

                    else if(tempNode1->row == i + 1){
                        if(tempNode1->col == j){
                            nodes[i][j]->neighbours[2] = true;
                            nodes[i+1][j]->neighbours[0] = true;
                        }
                        else cout<<"\n\nError, edges not adjacent\n\n";
                    }
                    finalEdges.pb(tempEdge1);
                }
            }
        }*/

        cout<<"cnt: "<<cnt;
        
        
    }

        
        
};
class MazeGenerator{


public:
    int random_seed;
    MazeGenerator(int seed){
        random_seed = seed;

        unique_ptr<Graph> graph = make_unique<Graph>(seed);

        cout<<"\n\n\n\n";
        //for(auto edge:edgeList){
        //  cout<<"Src: "<<edge->src->row<<" "<<edge->src->col<<"\n";
        //  cout<<"Dst: "<<edge->dst->row<<" "<<edge->dst->col<<"\n";
        // cout<<"\n";

        cout<<"\n\n\n";
        vector<vector<Node*>> nodeList = graph->nodes;

        MazeGenerator::remove_deadEnds(nodeList);



        std::string filename = "Kruskal.txt";
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

    static void remove_deadEnds(vector<vector<Node*>> nodes){
        Node* tempNode;
        Node* temp;
        int z,r ;
        vector<Node*> deadEnds;
        for(int i = 0;i < nodes.size();i++){
            for(int j = 0;j < nodes[0].size();j++){
                tempNode = nodes[i][j];
                int sum = 0;
                for(int k = 0;k<4;k++) sum+= tempNode->neighbours[k];
                
                if(sum == 1) deadEnds.pb(tempNode);

            }
        }

        cout<<"DeadEnds: \n\n";
        for(int i = 0;i < deadEnds.size();i++){
            cout<<deadEnds[i]->row<<" "<<deadEnds[i]->col<<"\n";
        }

        std::shuffle(deadEnds.begin(), deadEnds.end(), std::default_random_engine(time(0)));
        int n_remove = deadEnds.size()*DEAD_END_REMOVAL;
        for(int i = 0;i<n_remove;i++){
            r = get_random_modulo(4);
            temp = deadEnds[i];
            for(int j = 0;j<4;j++){
                z = (j+r)%4;
                if(!temp->neighbours[z] && !temp->isWallEdge(z)){
                    temp->neighbours[z] = true;
                    cout<<"\n\nrow: "<<temp->row - (z%2 - 1)*(z - 1)<<", col: "<<temp->col + (z%2)*(z - 2)<<", index: "<<2-z + 2*(z%2)<<", isWallEdge: "<<temp->isWallEdge(z)<<"\n";
                    nodes[temp->row - (z%2 - 1)*(z - 1)][temp->col + (z%2)*(z - 2)]->neighbours[2-z + 2*(z%2)] = true;
                    break;
                }
            }
        }
    }

    static int get_random_modulo(int m){
        //srand(time(0));
        srand(50);
        int s = (int)rand();
        return (s%m + m)%m;
    }







};

/*int main(){
    MazeGenerator* gen = new MazeGenerator(45);

}*/
