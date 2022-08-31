#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>


	int i,j,x,y;
	
typedef struct node{ 
    int id; 
    int degree; 
}list; 



	
void Createlist(list z[],int i){

	int w;
}

	
void getArray(){


FILE *file;
char singleline[10];
size_t l=10;
char *token;
int n;
int c=0;

file = fopen("project.txt","r");

if(file==NULL){
	printf("Error\n");
	exit(1);
}


	fgets(singleline,l,file);
	sscanf(singleline,"%d %d",&i,&j);
	printf(" %d  %d\n\n",i,j);

	i+=1;
	j+=1;
	clock_t start,end;
	double time;	
	int matrix[i][j];
	list graph[i-1];
	list S[i-1];
    int L[i];
	n=i;	
	
	printf("Table without aces:\n\n");
	for(x=0;x<i;x++){
			for(y=0;y<j;y++){
				
				matrix[x][y]=0;			//midenizo ton pinaka
				
			printf(" %d",matrix[x][y]);
			}
			printf("\n");

	for(x=0;x<i;x++){
		matrix[x][0]=x;	//vazoume node ID gia eukolia stin anagnorisi
		matrix[0][x]=x;	
	}

	while(fgets(singleline,l,file)!=NULL){
			
			sscanf(singleline,"%d %d",&i,&j);
			printf("%d %d\n",i,j); 		//vazoume asous sto pinaka
			matrix[i][j]=1;	
			}
			
	printf("\nTable with aces:\n\n");
		for(x=0;x<n;x++){
			for(y=0;y<n;y++){	
			printf("  %d ",matrix[x][y]);
				 }
		 printf("\n");
		} 
printf("\n\n");
	for(y=1; y<n; y++){
	graph[y-1].degree=0;
	
		for(x=1; x<n; x++){
			if( matrix[x][y] ==  1)		//vazou sto graph ta posa iserxomena dianismata exei kathhe komvos
			graph[y-1].degree++;
						
		}
		graph[y-1].id=y;
		printf("Degree:%d  ID:%d   \n",graph[y-1].degree,graph[y-1].id);
			
	} 





for(y=1;y<n;y++){
	if(graph[y-1].degree == 0 ){
	 S[y-1].degree=graph[y-1].degree;
	S[y-1].id=graph[y-1].id;			
	printf("\n %d   %d\n",S[y-1].degree,S[y-1].id);	//afto pou exei 0 iserxomena mpeni sto S
	break;
}
}


printf("\n");

start=clock();
if(S[y-1].degree !=0)
printf("graph has circual");
else{
while(S[y-1].degree ==  0){

	printf("%d ->",graph[y-1].id);
	S[y-1].degree=-1;
	L[y-1]=graph[y-1].id;

	//printf("%d",graph[y-1]);

 
	for(x=1;x<n;x++)	
	matrix[graph[y-1].id][x]=0;


	

//	printf("\n");
	#pragma omp parallel firstprivate(y) shared(n,x)  num_threads(1)
{

	#pragma omp for schedule(dynamic,1)
	for(y=1; y<n; y++){
		graph[y-1].degree=0;	//midenizo tin grammi tou dianismatos pou mpike sto S

		for(x=1; x<n; x++){
			if( matrix[x][y] ==  1){
		
			graph[y-1].degree++;			//3anavgazo ton vathmo	
			}
		 }

		if(L[y-1]==graph[y-1].id){
#pragma omp task
			graph[y-1].degree=-1;}	//osa exoun mpi idi sto S ginonte -1
		}


	//	printf("Degree: %d ID:%d\n",graph[y-1].degree,graph[y-1].id);
	

}
	for(y=1;y<n;y++){
	if(graph[y-1].degree == 0 ){
	 S[y-1].degree=graph[y-1].degree; 	//Afto pou den exei mpi kai exei dinami 0 mpeni sto S
	 break;
		}
	 }

}
}
end=clock();
time=(double)(end - start)/ CLOCKS_PER_SEC;
printf("\ntotal time:%f\n",time);
}


int main(){
	
	getArray();


return 0;

	
}
