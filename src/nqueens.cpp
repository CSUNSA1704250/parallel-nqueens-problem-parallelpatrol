#include <omp.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h>
using namespace std;
using std::ofstream;
using std::ifstream;
	int cant;
    bool found = false;
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
        outdata  <<"    ";
				outdata <<"<tr>";
        for (int j=0; j<x;j++){
						if(vector1[i] == j){
							outdata <<"<td>&#9813;</td>";
						}
						else{
							outdata <<"<td> </td>";
						}
        }
				outdata <<"</tr>";
        outdata  <<endl;
    }
    outdata  <<"   </table>>" <<endl;
    outdata  <<" ];" <<endl;
    outdata  <<"}" <<endl;
}

void Graficar2(int *&queens)
{
    int cantidad = cant;
    vector<vector<string>> matriz(cantidad);
    for (int i = 0; i < cantidad; i++)
    {
        matriz[i].resize(cantidad);
    }

    for (int i = 0; i < cantidad; i++)
    {
        matriz[queens[i]][i] = "&#9813;";
    }

    string salida = "digraph D {\n";

    salida = salida + "    node [shape=plaintext]\n  some_node [ \n  label=< \n  <table border=\"0\" cellborder=\"1\" cellspacing=\"0\"> \n ";

    for (int i = 0; i < cantidad; i++)
    {
        salida = salida + " <tr>";
        for (int j = 0; j < cantidad; j++)
        {
            salida = salida + "<td>"+matriz[i][j]+" </td>";
        }
				salida = salida + " </tr>\n";
    }

    salida = salida + "</table>>];\n }";

    ofstream file;
    file.open("graph.dot");
    file << salida;
    file.close();
}

bool comprobar(int reinas[],int n, int k){
	int i;
	for(i=0;i<k;i++){
		if( (reinas[i]==reinas[k]) || (abs(k-i) == abs(reinas[k]-reinas[i]))){
			return false;
		}
	}
	return true;
}

void try_queen_one_solution(int *&queens, int col)
{
    if (found)
        return;
    if (col == cant && !found)
    {
        /* print_solution(queens); */
        found = true;
        Graficar2(queens);
        return;
    }

    for (int i = 0; i < cant; ++i)
        if (comprobar(queens, i, col))
        {
            queens[col] = i;
            try_queen_one_solution(queens, col + 1);
        }
}
void find_a_solution()
{
    int col = 0;
    #pragma omp parallel
    {
        int *priv_queens = new int[cant];
        #pragma omp for nowait
        for (int i = 0; i < cant; ++i)
        {
            if (comprobar(priv_queens, i, col))
            {
                priv_queens[col] = i;
                try_queen_one_solution(priv_queens, col + 1);
            }
        }
        delete[] priv_queens;
    }
}

void Nreinas(int reinas[],int n, int k,ofstream  & outdata, int &x ){
	if(k==n){
		x++;
		for(int i=0;i<n;i++){
			outdata <<reinas[i]<<" ";
		}
		outdata <<endl;
	}
	else{
		for(reinas[k]=0;reinas[k]<n;reinas[k]++){
			if(comprobar(reinas,n,k)){
				Nreinas(reinas,n,k+1,outdata, x);
			}
		}
	}
}

int main(int argc, char *argv[]) {
	int k=0;
    string type=  string(argv[1]);
    if (type == "all")
    {
                cant = atoi(argv[2]);
            int nthreads = cant;
            omp_set_dynamic(0);
        omp_set_num_threads(cant);

            int *total = new int[cant];

            ofstream outdata;
            outdata.open("time.txt");

            ofstream *solutions = new ofstream[cant];

            for(int y=0; y < cant; y++){
                solutions[y].open("thread-" + to_string(y) + ".txt");
            }

            clock_t start, end;
        start = clock();

            int tid;

            #pragma omp parallel private(nthreads, tid)
        {
                tid = omp_get_thread_num();

                int *reinas = new int[cant];

                for(int i=0;i<cant;i++){
                    reinas[i]=-1;
                }

                reinas[0]=tid;
                Nreinas(reinas,cant,k+1, solutions[tid], total[tid]);

                solutions[tid].close();
            }

            end = clock();

            int totalFinal = 0;
            for(int i=0;i<cant;i++){
                totalFinal += total[i];
            }

            outdata  << "Solutions for "<<nthreads << " Queens." << endl << endl;
        outdata  << "process terminated in " << (float)(end - start) / CLOCKS_PER_SEC << " procesor seconds time."<< endl;
            outdata  << "number of solutions: " << totalFinal << endl << endl;
        outdata.close();

            ifstream *concat = new ifstream[cant];

            ofstream of_c("final.txt", std::ios_base::binary);

            ifstream if_b(("time.txt"), std::ios_base::binary);
            of_c << if_b.rdbuf();

            for(int y=0; y < cant; y++){
                ifstream if_a(("thread-" + to_string(y) + ".txt"), std::ios_base::binary);
                of_c << if_a.rdbuf();
            }

            ifstream myfile;
            myfile.open("thread-1.txt");

            vector <int> toRender;
            float a;
        for(int y=0; y < cant; y++){
                myfile >> a;
                toRender.push_back(a);
    }

		Graficar(toRender,cant);
    }
    else if (type == "find")
    {
        cant = atoi(argv[2]);
        find_a_solution();
    }
    else
    {
        cout<< type<<endl;
        cout << "problem type not valid" << endl;
        return -1;
    }
	return 0;
}