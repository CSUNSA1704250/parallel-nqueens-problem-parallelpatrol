#include <omp.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <unistd.h>
using namespace std;
using std::ofstream;
using std::ifstream;
string type;
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


bool comprobar(int reinas[],int n, int k){
	int i;
	for(i=0;i<k;i++){
		if( (reinas[i]==reinas[k]) || (abs(k-i) == abs(reinas[k]-reinas[i]))){
			return false;
		}
	}
	return true;
}

void try_queen_one_solution(vector<int> &queens, bitset<200> &rows, bitset<200> &d1, bitset<200> &d2, int col)
{
    if (found)
        return;
    if (col == cant && !found)
    {
        found = true;
        cout <<"Solution for "<<cant<<" Queens: "<<endl;
        for (int i: queens)
            std::cout << i << ' ';
        Graficar(queens, cant);
        return;
    }

    for (int r = 0; r < cant; ++r)
        if (!rows[r] && !d1[r - col + cant - 1] && !d2[r + col])
        {
            queens[col] = r;
            rows[r] = d1[r - col + cant - 1] = d2[r + col] = 1;
            try_queen_one_solution(queens, rows, d1, d2, col + 1);
            rows[r] = d1[r - col + cant - 1] = d2[r + col] = 0;
        }
}
void find_a_solution()
{
    int col = 0;
    #pragma omp parallel
    {
        vector<int> priv_queens(cant);
        bitset<200> rows, d1, d2;
        #pragma omp for nowait
        for (int i = 0; i < cant; ++i)
        {
            priv_queens[col] = i;
            rows[i] = d1[i - col + cant - 1] = d2[i + col] = 1;
            try_queen_one_solution(priv_queens, rows, d1, d2, col + 1);
        }
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
            if(!(reinas[k-1] == reinas[k] || reinas[k-1]+1 == reinas[k] || reinas[k-1]-1 == reinas[k])){
                if(comprobar(reinas,n,k)){
                    Nreinas(reinas,n,k+1,outdata, x);
                }
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

            ofstream of_c("solutions.txt", std::ios_base::binary);

            ifstream if_b(("time.txt"), std::ios_base::binary);
            of_c << if_b.rdbuf();

            for(int y=0; y < cant; y++){
                ifstream if_a(("thread-" + to_string(y) + ".txt"), std::ios_base::binary);
                of_c << if_a.rdbuf();
            }
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

