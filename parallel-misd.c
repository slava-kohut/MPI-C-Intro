#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mpi.h"
#define ARRAY_SIZE 1000000000

int main(int argc,char *argv[]) {
 
 int i,k,N; 
 double random_numbers[ARRAY_SIZE];
 const double upper_limit=1.;
 int noprocs, nid;
 double *moments;

 MPI_Init(&argc, &argv);
 MPI_Comm_size(MPI_COMM_WORLD, &noprocs);
 MPI_Comm_rank(MPI_COMM_WORLD, &nid);
 
/*allocate an array for the moments*/
 
 moments=(double *)malloc(sizeof(double)*noprocs);   

/*
1) generate random numbers on the master node 
2) send all the data to all processors
*/
/*-------------------------------------------------*/
 if (nid==0) {
 
/*read the input from command line*/

  if (argc!=2) {
   printf("ERROR: provide a command-line argument!\n");
   return 1;
  } 
  else { 
   N=atoi(argv[1]);//convert the command-line argument to a number
  }

/*generate random numbers*/

   srand((unsigned int)time(NULL));
   
   for (i=0;i<N;++i) {
    random_numbers[i]=((double)rand()/(double)(RAND_MAX))*upper_limit;
   }
  }

/*send the data*/

  MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&random_numbers, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
/*-------------------------------------------------*/

/*now calculate the moments on each processor*/

  moments[nid]=0.; // initialze moments to 0. 
  for (k=0;k<N;k++) {
  moments[nid]+=pow(random_numbers[k],(double) nid+1)/(double) N;
  }
  printf("moment %d = %.5f\n",nid+1,moments[nid]);

 MPI_Finalize();

 return 0;

}

