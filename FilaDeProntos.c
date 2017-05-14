/**
*Autores
*@author ALEX SOUZA    0040481611013
*@author ISAQUE COELHO 0040481611004
*@author RAMON LACAVA  0040481611003
*@author JOSÉ LUIS ZEM Professor da disciplina de Sistemas Operacionais I
*@Faculdade de Tecnologia de Americana ADS 2º Semestre Periodo matutino
*@date 25/10/2016
*@version 1.0.0
*********************************************************************************************
*********************************************************************************************
***@TAREFA 1 - FILA DE PRONTOS UTILIZANDO FILAS(Queue) ESTÁTICAS, STRUCTS E PONTEIROS EM C***
*********************************************************************************************
*********************************************************************************************
OBS: Versão inicial, existem várias melhorias que podem ser realizadas no código. O processo 
de desenvolvimento foi realizado de acordo com o que foi passado na aula. O mesmo poderia 
obter uma maior performance utilizando uma maior quantidade de ponteiros no escalonamento e  
utilizar threads para a obtenção de uma maior performance. Algumas funções também poderiam 
ser criadas visando a melhoria de manutenção do código. Estas são sugestões para futuras 
versões deste software.

*/


//libs
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//tamanho maximo
#define MAX 7


//pid dos processos
int pid = 1000;
int primeiravez = 1;

//estrutura do processo
struct processo{
	char nome[8];//variaveis do processo
	int pid, cpu;

};

typedef struct filadeprocessos Fila;


//fila dos processo
struct filadeprocessos{
	int inicio, final, qtd;
	struct processo dados[MAX];
};


/**
*********************************************************
*********************************************************
************FUNÇÕES DE MANIPULAÇÃO DA FILA***************
*************E FUNCIONALIDADES DO SISTEMA****************
*********************************************************
*********************************************************
*/

//inicio
Fila* cria_Fila();
void libera_Fila(Fila* fi);
int tamanho_Fila(Fila *fi);
int Fila_cheia(Fila *fi);
int Fila_vazia(Fila* fi);
int insere_Fila(Fila* fi, struct processo pr);
int remove_Fila(Fila* fi);
void mostrar_Tela(Fila* fi);
int adicionar_Processo(Fila* fi);
int mostrar_Tabela(Fila* fi);
int alterar(Fila* fi);
int remove_Processo(Fila* fi);
int limpar_Fila(Fila* fi);
int escalonar_Processo(Fila* fi);
//final


//inicio main
int main(){

	Fila *fi;
	fi = cria_Fila();
	libera_Fila(fi);
	
	mostrar_Tela(fi);
	
	

	
	return 0;
}//final main


//criação da fila
Fila* cria_Fila(){
	Fila *fi = (Fila*) malloc(sizeof(struct filadeprocessos));
	
	if(fi != NULL){
		
		fi->inicio = 0;
		fi->final = 0;
		fi->qtd = 0;
	}

return fi;

}//fim criação



//liberação da fila
void libera_Fila(Fila* fi){
	free(fi);
}//fim liberação



//tamanho da fila
int tamanho_Fila(Fila *fi){
	if(fi == NULL){
		return -1;
	}
	return fi->qtd;

}//fim tamanho

//fila cheia
int Fila_cheia(Fila* fi){
	if(fi == NULL) return -1;
	if(fi->qtd == MAX){
		return 1;
	}
	else{
		return 0;
	}
}//fila cheia


//fila vazia
int Fila_vazia(Fila* fi){

	if(fi == NULL) return -1;
	
	if(fi -> qtd == 0) 
		return 1;
	else
		return 0;

}//fila vazia

//inserção na fila
int insere_Fila(Fila* fi, struct processo pr){

	if(fi == NULL) return 0;
	if(Fila_cheia(fi)) return 0;
	fi->dados[fi->final] = pr;
	if(fi->final == 6){
		fi->final = (fi->final + 1);
	}else{
	fi->final = (fi->final + 1) % MAX;
	}
	fi->qtd++;
	return 1;
	
}//fim inserção


//remoção da fila
int remove_Fila(Fila* fi){

	if(fi == NULL || Fila_vazia(fi)){
		return 0;
		
	}

	fi->inicio = (fi->inicio+1) % MAX;
	fi->qtd--;
	return 1;

}//fim remoção


//mostrar na tela
void mostrar_Tela(Fila* fi){
	system("clear");
	
	printf("=====================================================\n");
	printf("=====SIMULADOR DE MANIPULAÇÃO DE FILA DE PRONTOS=====\n");
	printf("=====================================================\n\n");

	printf("\n1 - CRIAR PROCESSO\n");
	printf("2 - ALTERAR PROCESSO\n");
	printf("3 - REMOVER PROCESSO\n");
	printf("4 - LISTAR A TABELA DE PROCESSOS\n");
	printf("5 - LIMPAR A TABELA DE PROCESSOS\n");
	printf("6 - ESCALONAR PROCESSOS\n");
	printf("7 - CRÉDITOS\n");
	printf("8 - SAIR\n");

	int opcao;
	printf("\n\nDigite uma opcao:");
	scanf("%d", &opcao);
	char ch;

	switch(opcao){
		case 1:
			if(adicionar_Processo(fi) == 1){
				printf("Processo adicionado com sucesso!");
			}
			else{
				printf("A fila esta cheia!");
			}
			printf("\n\nTecle qualquer tecla para continuar ...\n");
			scanf("%c", &ch);
			getchar();
			primeiravez = 1;
			mostrar_Tela(fi);
			
		break;

		case 2:
			if(alterar(fi) == 1){
				printf("Processo alterado com sucesso!");
			}
			else{
				printf("PID nao encontrado!");
			}
			printf("\n\nTecle qualquer tecla para continuar ...\n");
			
			scanf("%c", &ch);
			getchar();
			primeiravez = 1;
			mostrar_Tela(fi);
		break;
		
		case 3:
			if(remove_Processo(fi) == 1){
				printf("Processo removido com sucesso!");
			}
			else{
				printf("Processo nao encontrado!");
			}
			printf("\n\nTecle qualquer tecla para continuar ...\n");
			
			scanf("%c", &ch);
			getchar();
			primeiravez = 1;
			mostrar_Tela(fi);
		break;

		case 4:
			mostrar_Tabela(fi);
			printf("\n\nTecle qualquer tecla para continuar ...\n");
			scanf("%c", &ch);
			getchar();
			mostrar_Tela(fi);
			
		break;

		case 5:
			if(limpar_Fila(fi) == 1){
				printf("Fila Limpada com sucesso!\n");
			}
			else{
				printf("Ocorreu um erro!\n");
			}
			
			printf("\n\nTecle qualquer tecla para continuar ...\n");
			scanf("%c", &ch);
			getchar();
			primeiravez = 1;
			mostrar_Tela(fi);


		break;

		case 6:
			if(escalonar_Processo(fi) == 1){
				printf("Fila Escalonada com sucesso!\n");
			}
			else{
				printf("Ocorreu um erro!\n");
			}
			
			printf("\n\nTecle qualquer tecla para continuar ...\n");
			scanf("%c", &ch);
			getchar();
			mostrar_Tela(fi);
		break;

		case 7:
			system("clear");
	
			printf("====================================================\n");
			printf("======================CRÉDITOS======================\n");
			printf("====================================================\n\n");		
					

			printf("\n\nANALISE E DESENVOLVIMENTO DE SISTEMAS 2 SEMESTRE\nFACULDADE DE TECNOLOGIA DE AMERICANA PERIODO MATUTINO\nSISTEMAS OPERACIONAIS I\nProfessor Orientador: JOSE LUIS ZEM\n\nALUNOS\n\nALEX SOUZA\tRA:0040481611013\nISAQUE COELHO\tRA:0040481611004\nRAMON LACAVA\tRA:0040481611003\n\n");
			printf("\n\nTecle qualquer tecla para continuar ...\n");
			scanf("%c", &ch);
			getchar();
			mostrar_Tela(fi);
		break;



		case 8:
			system("clear");
	
			exit(0);
		break;
		

	}
}
//fim menu

/**
*********************************************************
*********************************************************
************FUNÇÕES DE 1 A 7 DO SISTEMA******************
*********************************************************
*********************************************************
*/


int adicionar_Processo(Fila* fi){
	system("clear");
	
	printf("====================================================\n");
	printf("================ADICIONAR PROCESSO==================\n");
	printf("====================================================\n\n");
	struct processo p;
	printf("Digite o nome do processo (maximo de 7 caracteres):\n");
	getchar();
	fgets(p.nome, 8, stdin);
	p.pid = pid;
	pid++;
	printf("Digite a CPU\n");
	scanf("%d", &p.cpu);
	
	int add = insere_Fila(fi, p);
	
	
	if(add == 1){
		return 1;
	}else{
		return 2;
	}


}


int mostrar_Tabela(Fila* fi){
	system("clear");
	
	printf("====================================================\n");
	printf("================TABELA DE PROCESSOS=================\n");
	printf("====================================================\n\n");

	int i;
	printf("\tPID\t\tCPU\t\tNome\n");
	for( i = 0; i < tamanho_Fila(fi); i++){
		
			printf("\t%d\t\t", fi->dados[i].pid);
			printf("%d\t\t", fi->dados[i].cpu);
			printf("%s", fi->dados[i].nome);
		
	}

	printf("\ninicio %d\nfinal %d\nqtd %d", fi->inicio, fi->final, fi->qtd);
	

}

int alterar(Fila* fi){
	int conseguiu = 0;
	system("clear");
	int pid, cpu;
	char nome[8];
	printf("====================================================\n");
	printf("==================ALTERAR PROCESSO==================\n");
	printf("====================================================\n\n");

	int p;
	printf("\tPID\t\tCPU\t\tNome\n");
	for( p = 0; p < tamanho_Fila(fi); p++){
	
			printf("\t%d\t\t", fi->dados[p].pid);
			printf("%d\t\t", fi->dados[p].cpu);
			printf("%s", fi->dados[p].nome);
		
	}
	
	printf("Digite o PID que deseja alterar: ");
	scanf("%d", &pid);
		
	printf("Digite o nome: ");
	getchar();
	fgets(nome, 8, stdin);

	printf("Digite a CPU: ");
	scanf("%d", &cpu);

	int i;
	for( i = 0; i < tamanho_Fila(fi); i++){
		
		if(fi->dados[i].pid == pid){
			fi->dados[i].cpu = cpu;
			strcpy(fi->dados[i].nome, nome);
			conseguiu = 1;
		
		}

	}


	return conseguiu;
}


int remove_Processo(Fila* fi){
	int conseguiu = 0;
	system("clear");
	int pid;
	printf("====================================================\n");
	printf("==================REMOVER PROCESSO==================\n");
	printf("====================================================\n\n");

	int p;
	printf("\tPID\t\tCPU\t\tNome\n");
	for( p = 0; p < tamanho_Fila(fi); p++){
	
			printf("\t%d\t\t", fi->dados[p].pid);
			printf("%d\t\t", fi->dados[p].cpu);
			printf("%s", fi->dados[p].nome);
	}
	
	printf("Digite o PID que deseja remover: ");
	scanf("%d", &pid);
	int i, num_vazio;
	int num = 0;
	
	for( i = 0; i < tamanho_Fila(fi); i++){
	
		
		if(fi->dados[i].pid == pid){
			fi->dados[i].pid = 0;
			fi->dados[i].cpu = 0;
			strcpy(fi->dados[i].nome, "\n");
			num_vazio = i;
			conseguiu = 1;
		
		}		
		

	}
	int achou = 0;
	printf("\tPID\t\tCPU\t\tNome\n");
	for( i = 0; i < tamanho_Fila(fi); i++){
		
		if(i == tamanho_Fila(fi) - 1){
			fi->qtd--;
				fi->final = (fi->final - 1) % MAX;
			break;

			
		}	
		if(fi->dados[i].pid == 0){
			achou = 1;
			fi->dados[i] = fi->dados[i + 1];
			

		}

		if(achou == 1){
			fi->dados[i] = fi->dados[i + 1];
		}
		printf("\t%d\t\t", fi->dados[i].pid);
		printf("%d\t\t", fi->dados[i].cpu);
		printf("%s", fi->dados[i].nome);
	}






	

	return conseguiu;


}



int limpar_Fila(Fila* fi){
	system("clear");
	printf("====================================================\n");
	printf("==================LIMPA PROCESSOS==================\n");
	printf("====================================================\n\n");

	while(Fila_vazia(fi) != 1){
		remove_Fila(fi);
	}

	if(Fila_vazia(fi) == 1){
		fi->inicio = 0;
		fi->final = 0;
		fi->qtd = 0;
		
		return 1;
	}
	else{
		return 0;
	}
	
}



int escalonar_Processo(Fila* fi){
	system("clear");
	printf("====================================================\n");
	printf("==================ESCALONAR PROCESSOS===============\n");
	printf("====================================================\n\n");
	

	
	printf("Iniciando o escalonamento...\n\n");
	int i;
	printf("\nEscalonamento - Ordem de termino dos elementos\n\n");
	while(Fila_vazia(fi) != 1){
		i = 0;
		int linha = 0;
		int naopula = 0;
		while(i < tamanho_Fila(fi)){
			
			
			if(fi->dados[i].cpu > 0){
				fi->dados[i].cpu = fi->dados[i].cpu - 1;
				struct processo proc = fi->dados[i];
				remove_Fila(fi);
				insere_Fila(fi, proc);
				fi->inicio = 0;
				fi->final = tamanho_Fila(fi);	
			}
			
			if(fi->dados[i].cpu == 0){
				printf("\tPID: \t%d\n", fi->dados[i].pid);
				if(i == 0){
					int n = 0;
					while(n < tamanho_Fila(fi)){
						
						fi->dados[n] = fi->dados[n + 1];
						n++;
					}
					fi->qtd = fi->qtd - 1;
					fi->final = tamanho_Fila(fi);
					naopula = 1;
				}
				else{
					int n = i;
					while(n < tamanho_Fila(fi)){
						
						fi->dados[n] = fi->dados[n + 1];
						n++;
					}
					fi->qtd = fi->qtd - 1;
					fi->final = tamanho_Fila(fi);
					naopula = 1;
				}

				

				
				
			}

			if(naopula == 0){
				i++;
			}
			else{
				naopula = 0;
			}
		}
	}
			



	
	return 1;
	

}



