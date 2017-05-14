#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int a=0, b=0, c=0;
FILE *arq1, *arq2;

void filho01() { 
	b = 10;
	arq1=fopen("filho1.txt","w");
	fprintf(arq1,"%d",b);
	fclose(arq1);
	exit(0);
}

void filho02() { 
	c = 50;
	arq2=fopen("filho2.txt","w");
	fprintf(arq2,"%d",c);
	fclose(arq2);
	exit(0);
}

int main(int argc,char *argv[]) {
	pid_t   filho1, filho2;
	int estado;
	system("clear");
	printf("Processo-Pai: Iniciando a execucao.\n");
	
	filho1=fork();
	if ( filho1 == 0) { filho01(); }

	filho2=fork();
	if ( filho2 == 0) { filho02(); }

	waitpid(filho1,estado,0);
	waitpid(filho2,estado,0);

	arq1=fopen("filho1.txt","r");
	fscanf(arq1,"%d",&b);
	fclose(arq1);

	arq2=fopen("filho2.txt","r");
	fscanf(arq2,"%d",&c);
	fclose(arq2);

	a = b + c;

	printf("Processo-pai: A = %d, B = %d e C = %d \n", a, b, c);

	printf("Processo-Pai: Encerrando a execucao.\n");
	return 0;
}























