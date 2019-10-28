//
// Created by Miłosz Chodkowski on 10/20/19.
//    ______ ______ ______                                                    _
//   |____  |____  |____  |                                                  | |
//       / /    / /    / /   _ __ ___   ___  _ __   ___ _   _ _ __ ___   __ _| | _____ _ __
//      / /    / /    / /   | '_ ` _ \ / _ \| '_ \ / _ | | | | '_ ` _ \ / _` | |/ / _ | '__|
//     / /    / /    / /    | | | | | | (_) | | | |  __| |_| | | | | | | (_| |   |  __| |
//    /_/    /_/    /_/     |_| |_| |_|\___/|_| |_|\___|\__, |_| |_| |_|\__,_|_|\_\___|_|
//                                                       __/ |
//

#include <iostream>
#include <string>
#include <cstdlib>
#include "Graph.hpp"


    Graph::Graph(int nv){
        this->num_of_vert = nv;
        this->createMatrix();
        this->createList();
        this->createPredList();
    }

    void Graph::isAdjoint() {
     // TODO compare all x,y pairs of Vertices and give result
     if(this->multigraph_status) {
         this->adjoint_status = false;
         return;
     }
     int nv = this->num_of_vert; int size = 0, common_els = 0;
        for (int i = 0; i < nv; i++) {
            if(this->adj_list[i].size()>1)  // checks if there is any vertex that has any successors
                for (int j = (i + 1); j < nv; j++)
                    for(int k = 1; k < (int)this->adj_list[i].size(); k++)
                        for(int l = 1; l < (int)this->adj_list[j].size(); l++){
                            if(this->adj_list[i].size() >= this->adj_list[j].size()) // sets the number of our common elements
                                size = (int)this->adj_list[i].size() - 1;
                            else                                                     // sets the number of our common elements as above
                                size = (int)this->adj_list[j].size() - 1;
                            if(this->adj_list[i][k] == this->adj_list[j][l]) // if we found common element, then we increment
                                common_els++;
                        }
        }
        if((common_els not_eq size) or (common_els not_eq 0)) // we don't have any common elements
            this->adjoint_status = false;                            // or our size is not equal to the size we need
        return;
    }

    void Graph::isLine() {
        int nv = this->num_of_vert;
        if(this->adjoint_status){ // if graph is not adjoint, then it's not line graph
            for(int i=0; i<nv; i++)
                for(int j=0;j<nv;j++)
                    for(int k=0; k<(int)this->pred_list[i].size();k++)
                        for(int l=0; l<(int)this->pred_list[j].size();l++)
                            if(this->pred_list[i][k] == this->pred_list[j][l]) { // if we find any predecessor then we know that this is not line graph
                                this->line_status = false;
                                return;
                            }

        }else{
            this->line_status = false;
        }
        return;

    }

    void Graph::getAdjointStatus() {
        this->isAdjoint();
        if(this->adjoint_status)
            cout<<"Graph is adjoint"<<endl;
        else
            cout<<"Graph is not adjoint"<<endl;
    }

    void Graph::getLineStatus() {
        this->isLine();
        if(this->line_status)
            cout<<"Graph is line graph"<<endl;
        else
            cout<<"Graph is not line graph"<<endl;
    }

    void Graph::createMatrix(){ //creates N^2 size matrix based on number of vertices
        int nv = this->num_of_vert;
        for(int i=0; i<nv; i++)
            for(int j=0; j<nv; j++)
                this->adj_matrix[i][j] = (int)random() % 2; // randomize matrix/create random graph
    }

    void Graph::printMatrix(){
        int nv = this->num_of_vert;
        cout<<"Number of vertices "<< nv <<endl;
        for(int i=0; i<nv; i++){
            for(int j=0; j<nv; j++)
                cout<<this->adj_matrix[i][j]<<" ";
            cout<<endl;
        }
    }

    void Graph::clearMatrix(){ // sets whole matrix to '0'
        int nv = this->num_of_vert;
        for(int i=0; i<nv; i++)
            for(int j=0; j<nv; j++)
                this->adj_matrix[i][j]= 0;
    }

    void Graph::createList(){ // creates list that is based on indexes of adjacency matrix
        int nv = this->num_of_vert;
        this->clearList();
        for(int i=0; i<nv; i++)
            for(int j=0; j<nv; j++) {
                if (this->adj_matrix[i][j] == 1)
                    this->adj_list[i].push_back(j + 1); // pushes index of current column + 1 (current vertex)
                if (this->adj_matrix[i][j] > 1) {
                    this->multigraph_status = true;
                    this->adjoint_status = false;
                    for (int k = 0; k < this->adj_matrix[i][j]; k++) {
                        this->adj_list[i].push_back(j + 1);
                    }
                }
            }
    }

    void Graph::createPredList(){
        int nv = this->num_of_vert;
        this->clearPredList();
        for(int i=0; i<nv; i++)
            for(int j=0; j<nv; j++){
                if(this->adj_matrix[i][j] >= 1)
                    this->pred_list[j].push_back(i+1); // pushes index of current column + 1 (current vertex)
            }
}

    void Graph::printList(){
        int nv = this->num_of_vert;
        cout<<endl<<"Successors"<<endl;
        for(int i=0; i<nv; i++){
            cout<<i+1<<":";
            for(int j=0; j<adj_list[i].size(); j++)
                cout<<"-> "<<this->adj_list[i][j];
            cout<<endl;
        }
    }

    void Graph::printPredList() {
        int nv = this->num_of_vert;
        cout<<endl<<"Predecessors"<<endl;
        for(int i=0; i<nv; i++){
            cout<<i+1<<":";
            for(auto j=0; j<(int)this->pred_list[i].size(); j++)
                cout<<"-> "<<this->pred_list[i][j];
            cout<<endl;
        }
    }

    void Graph::clearList() { //resets list to be empty
        for(int i=0; i<50; i++){
            this->adj_list[i].resize(1);
            this->adj_list[i].clear();
        }
    }

    void Graph::clearPredList(){
        for(int i=0; i<50; i++){
            this->pred_list[i].resize(1);
            this->pred_list[i].clear();
        }
    }

    void Graph::addArc(int &tail, int &head){
        // TODO test function, upgrade if needed
        this->adj_matrix[tail-1][head-1] += 1;
        this->createList();
        this->createPredList();
    }

    void Graph::removeArc(int &tail, int &head){
        // TODO test function, upgrade if needed
        this->adj_matrix[tail-1][head-1] -= 1;
        this->createList();
        this->createPredList();
    }

    void Graph::saveGraph() {
        fstream file; int nv = this->num_of_vert;
        file.open("graph.txt", ios::out);
        if (file.good()) {
            file.clear();
            file << nv << endl; //read first line which is our number of vertices
            for (int i = 0; i < nv; i++) {
                for (int j = 0; j < nv; j++) {
                    if (this->adj_matrix[i][j] == 1) // if our column for current vertex is == 1,
                        file << j + 1 << " ";        // then saves it as our vertex
                    if (j == (this->num_of_vert - 1)) // if at end of columns-
                        file << "/";                  // set end of adj list for this vertex
                }
                file << endl;
            }
            file.close();
        } else {
            cout << "Error while opening the file" << endl;
        }
    }

    void Graph::loadGraph(){
        string val; int nv = this->num_of_vert; fstream file;
        file.open("graph.txt", ios::in);
        if(file.good()){
            this->clearMatrix();
            file>>val; // reads number of vertices (first line)
            this->num_of_vert = stoi(val); nv = stoi(val);

            for(int i=0; i<nv; ){
                for(int j=0; j<nv; j++){
                    file>>val; // read the number
                    if(val == "/") {    // if end of number then go to next line(vertex),
                        i++;            // set columns to zero, and empty our 'val' variable
                        j = 0;
                        val = "0";
                    }
                    if(stoi(val) not_eq 0) // if number is good then put '1' in the column which the number is pointing
                        this->adj_matrix[i][stoi(val)-1] += 1; // (number - 1, starting from 0)
                }
            }
            this->createList();
            this->createPredList();
        }else{
            cout<<"Error while opening the file"<<endl;
        }
    }





