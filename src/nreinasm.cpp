#include <iostream>
#include <cstdlib>
#include <ctime>
#include<stdio.h>
#include <fstream>
using namespace std;
using std::ofstream;

int x=0;

bool comprobar(int reinas[],int n, int k){
	int i;
	for(i=0;i<k;i++){
		if( (reinas[i]==reinas[k]) || (abs(k-i) == abs(reinas[k]-reinas[i]))){
			return false;
		}
	}
	return true;
}

void Nreinas(int reinas[],int n, int k,ofstream  & outdata ){
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
				Nreinas(reinas,n,k+1,outdata);
			}
		}
	}
}
		
int main(int argc, char *argv[]) {
	int k=0;
	int cant;
  int n;

  if(argv[1] != NULL) {

    cant = atoi(argv[1]);
    int *reinas = new int[cant];

    for(int i=0;i<cant;i++){
      reinas[i]=-1;
    }

    clock_t start, end;
    start = clock();
    ofstream outdata; //
    outdata.open("example3.txt");
    if( !outdata ) {
      cerr << "Error: file could not be opened" << endl;
      exit(1);
    }

    outdata  << "#Solutions for " << cant << " Queens." << endl << endl;
    Nreinas(reinas,cant,k, outdata);
    end = clock();
    outdata  << "process terminated in " << ((float)end - start) / CLOCKS_PER_SEC << " seconds." << endl << endl;
    outdata.close();
  }
	return 0;
}