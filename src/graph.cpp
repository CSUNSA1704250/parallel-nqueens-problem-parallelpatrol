#include <iostream>
#include <cstdlib>
#include <ctime>
#include<stdio.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
using std::ofstream;
void Graficar(vector<int> &vector1,int & x){
    ofstream outdata; //
    outdata.open("graph.dot"); // opens the file
    if( !outdata ) { 
            cerr << "Error: file could not be opened" << endl;
            exit(1);
    }
    outdata  << "digraph D { "<< endl;
    outdata  <<" node [shape=plaintext]"<<endl;
    outdata  <<" some_node [" <<endl;
    outdata  <<"  label=<" <<endl;
    outdata  <<"   <table border=\"0\" cellborder=\"1\" cellspacing=\"0\">" <<endl;

    for (int i=0 ; i<x;i++){
        bool bandera =false ;
        outdata  <<"    ";
        for (int j=0; j<x+1;j++){
            if (j==0){
                outdata <<"<tr><td>";
                if (vector1.front()==j+1 & bandera == false){
                
                outdata <<"&#9813;";
                bandera = true;
                vector1.front() = vector1.back();
                vector1.pop_back();
                }
                outdata <<" ";
                continue;
            }
            if(j==x){
                outdata <<"</td></tr>";
            }

            else{
                outdata <<"</td><td>";
                
                if (vector1.front()==j+1 & bandera == false){
                    
                    outdata <<"&#9813;";
                    bandera = true;
                    vector1.front() = vector1.back();
                    vector1.pop_back();
                }
                outdata <<" ";
                continue;
            }
            
        }
        outdata  <<endl;
    }
    outdata  <<"   </table>>" <<endl;
    outdata  <<" ];" <<endl;
    outdata  <<"}" <<endl;
}

int main(int argc, char *argv[]) {
    int x = 4;
    vector <int> pos{2,4,1,3};
    Graficar(pos,x);
    return 0;
return 0;
}