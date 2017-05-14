#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc,char *argv[]) {
	system("clear");
	printf("Processo-Pai: Iniciando a execucao.\n");
	while (1) {
		fork();
		printf("Processo-Filho: Iniciando a execucao\n");
		sleep(3);
		printf("Processo-Filho: Encerrando a execucao\n");
		printf("Processo-Pai: Encerrando a execucao\n");
	}
	return 0;
}
