#include <omp.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<stdio.h>
#include <fstream>
#include <unistd.h>
using namespace std;
using std::ofstream;

bool comprobar(int reinas[],int n, int k){
	int i;
	for(i=0;i<k;i++){
		if( (reinas[i]==reinas[k]) || (abs(k-i) == abs(reinas[k]-reinas[i]))){
			return false;
		}
	}
	return true;
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
	int cant;

  if(argv[1] != NULL) {

    cant = atoi(argv[1]);
		int nthreads = cant;
		omp_set_dynamic(0);
    omp_set_num_threads(cant);

		int *total = new int[cant];

		ofstream outdata;
		outdata.open("time.txt");

		ofstream *solutions = new ofstream[cant];

		for(int y=0; y < cant; y++){
			solutions[y].open("sol" + to_string(y) + ".txt");
			solutions[y]  << "#Solutions for " << cant << " Queens." << endl << endl;
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

    outdata  << "process terminated in " << (float)(end - start) / CLOCKS_PER_SEC << " seconds." << endl << endl;
		outdata  << "number of solutions: " << totalFinal << endl << endl;
    outdata.close();
  }
	return 0;
}