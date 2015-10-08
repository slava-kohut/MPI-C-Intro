#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mpi.h"

int main(int argc,char *argv[]) {
 
 int i,k,N,size; 
 double *random_numbers, moment_4=0.0f, Gmoment_4, tail;
 const double upper_limit=1.;
 int noprocs, nid;
 MPI_Status status;

 MPI_Init(&argc, &argv);
 MPI_Comm_size(MPI_COMM_WORLD, &noprocs);
 MPI_Comm_rank(MPI_COMM_WORLD, &nid);
  
/*

   MASTER
--------------------------------------------
1) generate random numbers on the master node 
2) send all the data to all the processors

*/
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

   random_numbers=(double *) calloc(N,sizeof(double));

   srand((unsigned int)time(NULL));
   
   for (i=0;i<N;++i) {
    random_numbers[i]=((double)rand()/(double)(RAND_MAX))*upper_limit;
   }

/*broadcast N*/

   MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);  

   size=N/noprocs;

/*send chunks of the array*/

   for (i=1;i<noprocs;i++){
    MPI_Send(&random_numbers[(i-1)*size],size,MPI_DOUBLE,i,10,MPI_COMM_WORLD);
   }
  }
/*

   SLAVES
-----------------------------------------------
1) receive chunks of the array
*/
  else {

   MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

   size=N/noprocs;

   random_numbers=(double *) calloc(size,sizeof(double));

   MPI_Recv(&random_numbers[0],size,MPI_DOUBLE,0,10,MPI_COMM_WORLD,&status);

  }


/*compute 4th moment*/
 if (nid!=0) {
  for (i=0;i<size;i++){
   moment_4+=pow(random_numbers[i],4.);/*each node does a chunk equal to 'size'*/
 }  
 } else {
   tail=size*(noprocs-1);/*the master node does the "tail" of the array*/  
   for (i=tail;i<N;i++){
    moment_4+=pow(random_numbers[i],4.);
 }  
 } 

/*fetch the total*/
 MPI_Reduce(&moment_4,&Gmoment_4,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
 
 if (nid==0) {
  Gmoment_4=Gmoment_4/(double) N;
  printf("moment 4 = %.5f\n",Gmoment_4); /*output 4th moment*/
 } 
  
 MPI_Finalize();

 return 0;

}

