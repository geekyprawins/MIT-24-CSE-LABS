#include <stdio.h>
#include <stdlib.h>

// consective integer method for calculating the gcd of two numbers


int gcd_consecutive_integer(int m, int n){

int t = 0;
int opcount = 0;

if(m==0 && n==0){
	t = 0;
}
else if(m==0 && n!= 0){
	t = n;
	opcount++;
}
else if(n==0&& m!=0){
	t = m;
	opcount++;
}
else {

	t = (m<n ? m :n);

	while(1){
		opcount++;

		if(m%t ==0 && n%t==0){
			break;
		}
		else t--;
	}
}

printf("Opcount = %d\n", opcount);
return t;

}


int main(){

int m,n;

printf("Enter two integers m and n : \n");

scanf("%d", &m);
scanf("%d", &n);

int gcd = gcd_consecutive_integer(m,n);

if(gcd == 0)
printf("GCD does not exist for %d and %d ", m,n);
else 
printf("GCD of %d and %d is %d ", m,n,gcd);


return 0;

}