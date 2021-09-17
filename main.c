#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

void menu();
void cadastrarCliente();
void listarCliente();
void deleteCliente();
void melhorComprador();
void mostrarCompras();
void updateCompras();
void zeraMontantes();

typedef struct pessoa {
	char nome[30];
	int anoNasc;
	int validacao;
	float montante;
}CLIENTE;
CLIENTE *cliente;

//maximo de clientes eu coloquei 11 porque o contador começa em 0 ai fica sempre um numero redondo
int maxCliente = 11;

//ponteiro para maximos de clientes
int *pMaxCliente = &maxCliente;

int main() {
	
	setlocale(LC_ALL, "Portuguese");
	
	if (maxCliente == 10) {
		cliente = (CLIENTE *) malloc ((maxCliente) * sizeof(CLIENTE));
		if (cliente == NULL) {
			printf("Está nulo");
		} else {
			int i;
			for (i = 0; i < maxCliente; i++) {
				cliente[i].validacao = 0;
			}
		}
	} else if (maxCliente > 10) {
		cliente = realloc (cliente, (maxCliente) * sizeof(CLIENTE));
		if (cliente != NULL) {
			printf("Alocando");
			int i;
			for (i = (maxCliente-10); i < maxCliente; i++){
				cliente[i].validacao = 0;
			}
		} else {
			printf("ERRO");
		}
	}
	
	menu(&cliente);
	
	cliente = NULL;
	return 0;
}
void menu(CLIENTE *cliente) {
	
	int valorDigitado;
	
	do {
		//limpa linhas
		system("cls");
		
		printf("Digite o número da opção escolhida\n");
		printf("1 - Cadastrar cliente\n");
		printf("2 - Exibir clientes cadastrados\n");
		printf("3 - Excluir cliente\n");
		printf("4 - Mostrar melhor comprador\n");
		printf("5 - Mostrar compras de um cliente a sua escolha\n");
		printf("6 - Alterar as compras de um cliente\n");
		printf("7 - Zerar montantes\n");
		printf("8 - Sair\n");
		printf("Opção: ");
		
		//limpa buffer do teclado
		fflush(stdin);
		scanf("%d", &valorDigitado);
		
		switch (valorDigitado) {
			case 1 :
				cadastrarCliente(&cliente);
				break;
			case 2 :
				listarCliente(&cliente);
				break;	
			case 3 :
				deleteCliente(&cliente);
				break;
			case 4 :
				melhorComprador(&cliente);
				break;
			case 5 :
				mostrarCompras(&cliente);
				break;
			case 6 :
				updateCompras(&cliente);
				break;
			case 7 :
				zeraMontantes(&cliente);
				break;
			case 8 :
				cliente = NULL;
				exit(0);
				break;
			default :
				printf("opção inválida!");
			break;	
		}
	} while (valorDigitado != 8);
}


void cadastrarCliente(CLIENTE **cliente) {
	
	char nomeCliente[30];
	int anoNascimento;
	int o; 
	int valorCadastro;
	int valorDigitado; 
	int ex; 
	int i;
	float montanteMes;
	
	do {
		system("cls");
		printf("Cadastro:\n");
		fflush(stdin);
		printf("Nome: ");
		fgets(nomeCliente, sizeof(nomeCliente), stdin);
		printf("Ano de Nascimento: ");
		scanf("%d", &anoNascimento);
		printf("Valor gasto no mês: R$ ");
		scanf("%f", &montanteMes);
		
		for(o = 0; o < maxCliente; o++){
			if ((*(*cliente+o)).validacao == 0) {
				strcpy((*(*cliente+o)).nome, nomeCliente);
				(*(*cliente+o)).anoNasc = anoNascimento;
				(*(*cliente+o)).montante = montanteMes;
				(*(*cliente+o)).validacao = 1;
				system("cls");
				printf("Cadastrado com sucesso\n");
				break;
			}
			if ((*(*cliente+maxCliente-1)).validacao == 1) {
				do {
					system("cls");
					printf("Número máximo de clientes cadastrado atingido, deseja aumentar o número de cadastrados de %d para %d?\n", maxCliente-1, maxCliente + 9);
					printf("1 - Sim\n");
					printf("2 - Não\n");
					printf("Opção: ");
					scanf("%d", &valorCadastro);
					if (valorCadastro == 1) {
						*pMaxCliente = *pMaxCliente + 10;
						valorCadastro = 2;
						main();
						break;
					}
				} while (valorCadastro != 2);
				break;
			}
		}
		printf("====================\n");
		printf("1 - Cadastrar outro cliente\n");
		printf("2 - Sair\n");
		printf("====================\n");
		printf("Opção: ");
		fflush(stdin);
		scanf("%d", &valorDigitado);
		
	} while (valorDigitado != 2);
}

void listarCliente(CLIENTE **cliente) {
	
	int i;
	int valorDigitado;
	
	do {
		system("cls");
		for (i = 0; i < maxCliente; i++){
			if((*(*cliente+i)).validacao == 1){
				printf("Cliente - %d\n", i);
				printf("Nome: %s", (*(*cliente+i)).nome);
				printf("Ano de nascimento: %d\n", (*(*cliente+i)).anoNasc);
				printf("Valor gasto no mês: R$ %.2f\n", (*(*cliente+i)).montante);
				printf("====================\n");
			}
		}
		printf("1 - Sair\n");
		printf("====================\n");
		printf("Opção: ");
		fflush(stdin);
		scanf("%d", &valorDigitado);
	}while (valorDigitado != 1);
}


void melhorComprador(CLIENTE **cliente) {
	
	float  a;
	int u;
	int i; 
	int valorDigitado;
	a = (*(*cliente)).montante;
	i = 0;
	
	for (u = 0; u < maxCliente; u++) {
		if(a < (*(*cliente+u)).montante) {
			a = (*(*cliente+u)).montante;
			i = u;
		}
	}
	if ((*(*cliente+i)).montante == 0){
		system("cls");
		printf("Erro, não constam cadastros no sistema:\n");
		printf("Cadastre um cliente selecionando a opção 1 no menu\n");
		printf("1 - Voltar ao menu\n");
		printf("Opção: ");
		fflush(stdin);
		scanf("%d", &valorDigitado);
	} else {
		do {
			system("cls");
			printf("Cliente com maior valor de compra\n");
			printf("=================================\n");
			printf("Cliente - %d\n", i);
			printf("Nome: %s", (*(*cliente+i)).nome);
			printf("Ano de nascimento: %d\n", (*(*cliente+i)).anoNasc);
			printf("Valor gasto no mês: R$ %.2f\n", (*(*cliente+i)).montante);
			printf("=================================\n");
			printf("1 - Sair\n");
			printf("Opção: ");
			fflush(stdin);
			scanf("%d", &valorDigitado);
		} while (valorDigitado != 1);
	}
}


void deleteCliente(CLIENTE **cliente) {
	
	int i;
	int valorDigitado;
	int valorDigitadox; 
	int valorDigitador;
	
	do {
		system("cls");
		for (i = 0; i < maxCliente; i++){
			if((*(*cliente+i)).validacao == 1){
				printf("Cliente - %d\n", i);
				printf("Nome: %s", (*(*cliente+i)).nome);
				printf("Ano de nascimento: %d\n", (*(*cliente+i)).anoNasc);
				printf("Valor gasto no mês: R$ %.2f\n", (*(*cliente+i)).montante);
				printf("====================\n");
			}
		}
		printf("Selecione o número do cliente para exclui-lo, ou digite 0 para sair\n");
		printf("Opção: ");
		fflush(stdin);
		scanf("%d", &valorDigitadox);
		if ((*(*cliente+valorDigitadox)).validacao == 1){
			do {
				system("cls");
				printf("Tem certeza que deseja excluir o cliente %d permanentemente?\n", valorDigitadox);
				printf("Nome: %s", (*(*cliente+valorDigitadox)).nome);
				printf("Ano de nascimento: %d\n", (*(*cliente+valorDigitadox)).anoNasc);
				printf("Valor gasto no mês: R$ %.2f\n", (*(*cliente+valorDigitadox)).montante);
				printf("====================\n");
				printf("1 - Sim\n");
				printf("2 - Não\n");
				printf("====================\n");
				printf("Opção: ");
				fflush(stdin);
				scanf("%d", &valorDigitador);
				if (valorDigitador == 1){
					(*(*cliente+valorDigitadox)).validacao = 0;
					(*(*cliente+valorDigitadox)).montante = 0;
					system("cls");
					printf("Cliente número %d removido com êxito\n", valorDigitadox);
					break;
				} else {
					system("cls");
					printf("Remoção %d cancelada\n", valorDigitadox);
					break;
				}
			} while (valorDigitador != 2);
		} else if (valorDigitadox == 0) {
			system("cls");
			printf("Digite 2 para sair\n");
		} else {
			system("cls");
			printf("O cliente informado não consta no sistema\n");
		}
		printf("====================\n");
		printf("1 - Remover outro cliente\n");
		printf("2 - Sair\n");
		printf("====================\n");
		printf("Opção: ");
		fflush(stdin);
		scanf("%d", &valorDigitado);
	}while (valorDigitado != 2);
}


void mostrarCompras(CLIENTE **cliente) {
	
	int i; 
	int valorDigitado; 
	int valorCadastro;
	
	do {
		system("cls");
		printf("====================\n");
		printf("Escolha o cliente que deseja consultar\n");
		printf("Digte 0, caso queira voltar\n");
		printf("====================\n");
		printf("Número do cliente: ");
		fflush(stdin);
		scanf("%d", &valorDigitado);
		
		if ((*(*cliente+valorDigitado)).validacao == 1){
			system("cls");
			printf("Cliente - %d\n", valorDigitado);
			printf("Nome: %s", (*(*cliente+valorDigitado)).nome);
			printf("Ano de nascimento: %d\n", (*(*cliente+valorDigitado)).anoNasc);
			printf("Montante mensal: R$ %.2f\n", (*(*cliente+valorDigitado)).montante);
		} else if (valorDigitado == 0) {
			system("cls");
			printf("Digite 2 para voltar ao menu principal\n");
		} else {
			system("cls");
			printf("Cliente inválido\n");
		}
		printf("====================\n");
		printf("1 - Tentar novamente\n");
		printf("2 - Sair\n");
		printf("====================\n");
		fflush(stdin);
		printf("Opção: ");
		scanf("%d", &valorCadastro);
	} while (valorCadastro != 2);
}


void updateCompras(CLIENTE **cliente) { 
	
	int i; 
	int valorDigitado; 
	int valorDigitadom;
	float valor; 
	float despesa;
	
	do {
		do {
			system("cls");
			printf("Selecione um cliente para atualizar as compras do mês, ou digite 0 para sair\n");
			printf("====================\n");
			for (i = 0; i < maxCliente; i++){
				if((*(*cliente+i)).validacao == 1){
					printf("Cliente - %d\n", i);
					printf("Nome: %s", (*(*cliente+i)).nome);
					printf("Ano de nascimento: %d\n", (*(*cliente+i)).anoNasc);
					printf("Valor gasto no mês: R$ %.2f\n", (*(*cliente+i)).montante);
					printf("====================\n");
				}
			}
			printf("Opção: ");
			fflush(stdin);
			scanf("%d", &valorDigitado);
			if ((*(*cliente+valorDigitado)).validacao == 1) {
				do {
					system("cls");
					printf("Cliente - %d\n", valorDigitado);
					printf("Nome: %s", (*(*cliente+valorDigitado)).nome);
					printf("Ano de nascimento: %d\n", (*(*cliente+valorDigitado)).anoNasc);
					printf("Valor gasto no mês: R$ %.2f\n", (*(*cliente+valorDigitado)).montante);
					printf("====================\n");
					printf("Selecione uma opção\n");
					printf("1 - Mudar o valor\n");
					printf("2 - Acrescentar uma despesa a mais\n");
					printf("3 - Sair\n");
					printf("====================\n");
					printf("Opção: ");
					fflush(stdin);
					scanf("%d", &valorDigitadom);
					if (valorDigitadom == 1) {
						system("cls");
						valor = 0;
						printf("====================\n");
						printf("Valor gasto do mês do cliente %d: R$ %.2f\n",valorDigitado, (*(*cliente+valorDigitado)).montante);
						printf("Valor a ser mudado: R$ ");
						scanf("%f", &valor);
						(*(*cliente+valorDigitado)).montante = valor;
						printf("Valor atualizado com sucesso\n");
					} else if (valorDigitadom == 2) {
						system("cls");
						valor = 0;
						printf("====================\n");
						printf("Valor gasto do mês do cliente %d: R$ %.2f\n",valorDigitado, (*(*cliente+valorDigitado)).montante);
						printf("Valor da despesa: R$ ");
						scanf("%f", &despesa);
						(*(*cliente+valorDigitado)).montante = (*(*cliente+valorDigitado)).montante + despesa;
						printf("Valor atualizado com sucesso\n");
					} else if (valorDigitadom == 3) {
						system("cls");
						printf("Digite 2 para sair para a tela inicial\n");
					} else {
						system("cls");
						printf("Opção inválida\n");
					}
				} while (valorDigitadom != 3);
			} else if (valorDigitado == 0) {
				system("cls");
				printf("Digite 2 para sair para a tela principal");
			} else {
				system("cls");
				printf("O cliente informado não consta no sistema\n");
			}
		} while (valorDigitado = 0);
		
		printf("====================\n");
		printf("1 - Atualizar outro cliente\n");
		printf("2 - Sair\n");
		printf("====================\n");
		printf("Opção: ");
		fflush(stdin);
		scanf("%d", &valorDigitado);
	}while (valorDigitado != 2);
}


void zeraMontantes(CLIENTE **cliente) {
	
	int i; 
	int valorDigitado;
	
	do {
		system("cls");
		for (i = 0; i < maxCliente; i++){
			if((*(*cliente+i)).validacao == 1){
				printf("Cliente - %d\n", i);
				printf("Nome: %s", (*(*cliente+i)).nome);
				printf("Ano de nascimento: %d\n", (*(*cliente+i)).anoNasc);
				printf("Valor gasto no mês: R$ %.2f\n", (*(*cliente+i)).montante);
				printf("====================\n");
			}
		}
		printf("Todos os montantes serão zerados, está certo(a) disso?\n");
		printf("====================\n");
		printf("1 - Sim\n");
		printf("2 - Não, voltar para a tela inicial\n");
		printf("====================\n");
		printf("Opção: ");
		fflush(stdin);
		scanf("%d", &valorDigitado);
		if (valorDigitado == 1){
			for (i = 0; i < maxCliente; i++) {
				if((*(*cliente+i)).validacao == 1) {
					(*(*cliente+i)).montante = 0;
					system("cls");
					printf("Valor zerado com sucesso");
				}
			}
		}
	} while (valorDigitado != 2);
}
