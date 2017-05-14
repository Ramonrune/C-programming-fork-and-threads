#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>



void processo_filho_01(int numero, int num_limite);
void processo_filho_02(int numero, int num_limite);
FILE *arquivo;
FILE *ler_arquivo;

int main(){
	pid_t filho1, filho2;
	int fatorial, numero1, numero2, total = 1, estado;
	char linha[10000];
	arquivo = fopen("dados.txt", "w");
	if(arquivo == NULL){
		printf("Não foi possível abrir o arquivo");
		exit(0);
	}
	else{
		system("clear");
		printf("*********************************************************\n");
		printf("*********************************************************\n");
		printf("********************CALCULO DE FATORIAL******************\n");
		printf("*********************************************************\n");
		printf("*********************************************************\n\n");		

		printf("Observacao: a partir de 13 os numeros passam do limite inteiro que e 2147483647\n\n");
		printf("Digite o fatorial:\n");
		scanf("%d", &fatorial);
		numero1 = fatorial;
		numero2 = numero1 / 2;

	

		filho1 = fork();
	
		if(filho1 == 0){
			
			//printf("Filho 1...\n");
			processo_filho_01(numero1, numero2);
			exit(0);
	
		}
		waitpid(filho1, estado, 0);

		filho2 = fork();
		if(filho2 == 0){
			//printf("Filho 2...\n");
			processo_filho_02(numero2, 1);
			exit(0);
		}
		
		
		waitpid(filho2, estado, 0);


		ler_arquivo = fopen("dados.txt", "r");

		if(ler_arquivo == NULL){
			printf("Não foi possível abrir o arquivo");
			exit(0);
		
		}else{			

			while(fgets(linha, sizeof(linha), ler_arquivo)){

				total = total * atoi(linha);
				

			}

			printf("\nFatorial de %d e de: %d\n\n\n", fatorial, total);
			fclose(ler_arquivo);
		}
		
	
		

	}
	

	return 0;
}

void processo_filho_01(int numero, int num_limite){
	
	int total = 1, i = 0;

	for(i = numero; numero > num_limite; numero--){
		
		total = total * numero;
	}
	fprintf(arquivo, "%d\n", total);


	

}
void processo_filho_02(int numero, int num_limite){
	int total = 1, i = 0;
	
	for(i = numero; numero > num_limite; numero--){
		
		total = total * numero;
	}
	fprintf(arquivo, "%d\n", total);
	fclose(arquivo);
	

}


