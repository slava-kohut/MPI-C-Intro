#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc,char *argv[]) {

 double upper_limit, random_number, Nf;
 double power_sum_1, power_sum_2, power_sum_3, power_sum_4, power_sum_5;
 double mean, moment_2, moment_3, moment_4, moment_5;
 int i, N;
  
 srand((unsigned int)time(NULL));

 upper_limit=1.;
 N=atoi(argv[1]);

 power_sum_1=0.;
 power_sum_2=0.;
 power_sum_3=0.;
 power_sum_4=0.;
// power_sum_5=0.;

 for (i=0;i<N;i++) {
 random_number=((float)rand()/(float)(RAND_MAX))*upper_limit;

 power_sum_1+=random_number;
 power_sum_2+=pow(random_number,2.);
 power_sum_3+=pow(random_number,3.);
 power_sum_4+=pow(random_number,4.);
// power_sum_5+=pow(random_number,5.);

 printf("%.5f\n",random_number);
 }

 mean=power_sum_1/(double) N;
 moment_2=power_sum_2/(double) N;
 moment_3=power_sum_3/(double) N;
 moment_4=power_sum_4/(double) N;
// moment_2=-(power_sum_1*power_sum_1)/(Nf*Nf)\
//          +power_sum_2/Nf; 
// moment_3=2.*pow(power_sum_1,3.)/(pow(Nf,3.))\
//          -3.*(power_sum_1*power_sum_2)/(Nf*Nf)\
//          +power_sum_3/Nf; 
// moment_4=-3.*pow(power_sum_1,4.)/(pow(Nf,4.))\
//          +6.*power_sum_1*power_sum_1*power_sum_2/(pow(Nf,3.))\
//          -4.*power_sum_1*power_sum_3/Nf/Nf\
//          +power_sum_4/Nf; 
// moment_5=4.*pow(power_sum_1,5.)/(pow(Nf,5.))\
//          -10.*pow(power_sum_1,3.)*power_sum_2/pow(Nf,4.)\
//          +10.*power_sum_1*power_sum_1*power_sum_3/(pow(Nf,3.))\
//          -5.*power_sum_1*power_sum_4/Nf/Nf\
//          +power_sum_5/Nf; 

 printf("moment 1= %.5f\n",mean);
 printf("moment 2= %.5f\n",moment_2);
 printf("moment 3= %.5f\n",moment_3);
 printf("moment 4= %.5f\n",moment_4);
//printf("m5= %.5f\n",moment_5);

 return 0;

}
