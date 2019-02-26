#include <stdio.h>

int main(){
	
	int n;
	scanf("%d",&n);
	
	int x,count=0,temp=0;
	
	for (int i=0;i<n;i++){
		scanf("%d",&x);
		if (i==0){temp=x;continue;}
		
		if	(temp<=x){
			count+=1;
		}else if (temp>x){
			count-=1;
		}
		temp=x;
	}
	
	if (count==n-1){
		printf("%d",1);
	}else{
		printf("%d",0);
	}
	
	return 0;
}