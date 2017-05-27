#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define mV 10

typedef struct
{
	int idVendedor, mesVenda;
	float valorVenda;
}Vendas;

void cadastrarVendedor(){
	//Cadastra um vendedor, através de um número, sua ID, até um máximo de 10 vendedores
	FILE *arquivo;
    arquivo = fopen("vendedores.txt","a+");

    int j = 0, count = 0, pausa = 0, codigoVendedor = 0, status = 1;
    float codigoVendedorTemp = 0;

	if(arquivo == NULL)
	{
		printf("Arquivo nao pode ser aberto \n\n");
		system("pause");
	}

	printf("Informe o codigo do vendedor: ");
	scanf("%d",&codigoVendedor);

	system("cls");

	while((!feof(arquivo)))
	{
		fscanf(arquivo,"%d", &j);
		if(count >= mV)
		{
			printf("Limite atingido.\n\n");
			pausa = 1;
			break;
		}
		count++;
		if(codigoVendedor == j)
		{
			printf("Esse codigo ja esta sendo utilizado por outro vendedor,voltando ao menu.\n\n");
			pausa = 1;
			break;
		}
	}

	if(!pausa)
	{

		fprintf(arquivo, "%d\n",codigoVendedor);
		printf("Vendedor Registrado com sucesso!\n\n");
		count++;
	}

	fclose(arquivo);

}

void cadastrarVenda(){
	//Cadastra uma venda, desde que o vendedor já esteja cadastrado e o mês seja válido
	FILE *arquivo;
	FILE *arqvenda;
	arquivo = fopen("vendas.txt","a+");
	arqvenda = fopen("vendedores.txt","r");

    int j = 0, existe = 0;

	Vendas v;

	printf("Informe o codigo do vendedor: ");
	scanf("%d",&v.idVendedor);

	printf("Informe o mes: ");
	scanf("%d",&v.mesVenda);

	printf("Informe o valor da venda: ");
	scanf("%f",&v.valorVenda);

	while((!feof(arqvenda)))
	{
		fscanf(arqvenda,"%d",&j);

		if(v.idVendedor==j)
		{
			existe=1;
			break;
		}
	}

	system("cls");

	if(existe)
	{
		if(v.mesVenda < 1 || v.mesVenda > 12){
			printf("Mes Invalido, voltando ao menu principal.\n");
		}
		else{
		fprintf(arquivo, "%d\n%d\n%.2f\n", v.idVendedor, v.mesVenda, v.valorVenda);
		printf("Venda registrada com sucesso!\n\n");
		}
	}
	else{
		printf("Vendedor nao existe, voltando ao menu principal.\n\n");
	}

	fclose(arquivo);
	fclose(arqvenda);
}

void consultarVendas(){
	//Consulta as vendas realizadas por um vendedor em determinado mês
	FILE *arquivo;
	arquivo = fopen("vendas.txt","r");

    int codigoVendedor, idTemp, mesAux, mes, existe = 0;
    float totalVendames = 0, valorTemp;

    printf("Informe o codigo do vendedor: ");
    scanf("%d",&codigoVendedor);

    printf("Informe o mes das vendas: ");
    scanf("%d",&mes);

    while(1)
	{
		fscanf(arquivo,"%d %d %f",&idTemp, &mesAux, &valorTemp);
		/*fscanf(arquivo,"%d",&mesAux);
		fscanf(arquivo,"%f",&valorTemp);*/
		if(feof(arquivo)) break;
		if(codigoVendedor==idTemp && mesAux==mes)
		{
			totalVendames+=valorTemp;
			existe=1;
		}
	}

	system("cls");
	if(existe)
		printf("O Valor Vendido nesse mes pelo vendedor %d foi R$ %.2f\n\n", codigoVendedor, totalVendames);
	else
		printf("Valor inexistente, voltando ao menu principal.\n");


}

void consultarTotal(){
	//Consulta todas as vendas realizadas por um vendedor
	FILE *arquivo;
	arquivo = fopen("vendas.txt","r");

    int codigoVendedor, idTemp, mesTemp, existe = 0;
    float valorTemp, total = 0;

    printf("Informe o codigo do vendedor: ");
    scanf("%d",&codigoVendedor);

    while(1)
	{
		fscanf(arquivo,"%d %d %f",&idTemp, &mesTemp, &valorTemp);
		if(feof(arquivo)) break;
		if(codigoVendedor==idTemp)
		{
			total+=valorTemp;
			existe=1;
		}
	}

	system("cls");

	if(existe){
		printf("Total de Vendas do Vendedor %d: R$ %.2f \n\n", codigoVendedor, total);
	}
	else{
		printf("Valor inexistente, voltando ao menu principal.\n");
	}

}

void consultarMelhorVendedor(){
	//Consulta e mostra qual o melhor vendedor em determinado mês
	FILE *arqvenda;
	FILE *arquivo;

	arqvenda = fopen("vendedores.txt","r");

    float valorVenda = 0, vendasTemp = 0, valorTemp = 0, melhorVendas = 0;
    int mesTemp, idTemp, melhorVendedor, mes, i;
    int *idAux = malloc (10 * sizeof (int));

    printf("Informe o mes de venda: ");
    scanf("%d",&mes);

    system("cls");

    	for(i = 0;1;i++)
		{
			fscanf(arqvenda,"%d", &idAux[i]);

			if(feof(arqvenda)) break;
		}
		for(i = 0;i < mV;i++)
		{
		    arquivo = fopen("vendas.txt","r");
			vendasTemp = 0;
			while(1)
			{
				fscanf(arquivo,"%d", &idTemp);
				fscanf(arquivo,"%d", &mesTemp);
				fscanf(arquivo,"%f", &valorTemp);
				if(feof(arquivo))
				{
				    fclose(arquivo);
	                break;
				}

				if(mesTemp == mes)
				{
					if(idAux[i] == idTemp)
						vendasTemp+=valorTemp;
				}

				if(vendasTemp > melhorVendas)
				{
					melhorVendas = vendasTemp;
					melhorVendedor = idTemp;
				}
			}
		}
    if(melhorVendas < 0.05)
    {
        printf("Nenhuma venda realizada no mes.\n\n");
    }
    else
  	printf("O vendedor com mais vendas durante o mes foi o vendedor (%d) com R$ %.2f vendidos\n\n", melhorVendedor, melhorVendas);
}

void consultarMelhorMes(){
	//Consulta em qual mês, foram realizadas mais vendas por todos os vendedores
	FILE *arquivo;
	arquivo = fopen("vendas.txt","r");

	int id, mes, melhorMes, i;
	float soma[13] = {0}, maior, valor;

	while(1)
	{
		fscanf(arquivo,"%d %d %f",&id, &mes, &valor);

		if(feof(arquivo)) break;
		soma[mes]+=valor;
	}

	for(i = 1;i < 13;i++)
	{
		if(soma[i] > maior)
		{
			melhorMes = i;
			maior = soma[i];
		}
	}

	system("cls");
    if(maior<0.05)
    {
        printf("Nenhuma venda cadastrada, voltando ao menu.\n\n");
    }
    else
    {
        printf("O mes com a maior quantidade de vendas foi: %d, com R$ %.2f em vendas.\n\n", melhorMes, maior);
    }

}
void MudarNome(char *nome){
	printf("Digite seu nome: ");
	scanf("\n%[^\n]", nome);
	system("cls");
}
int main(){

	int op = 0;
	int sair = 0;
	char nome[50] = "User";
	system("cls");

	while(sair != 1){

		printf("|------------------------------- MENU PRINCIPAL ------------------------------|\n");
		printf("|  Bem vindo %s!                                                              \n",nome);
		printf("|-----------------------------------------------------------------------------|\n");
		printf("|    (1) Cadastrar Vendedor                                                   |\n");
		printf("|    (2) Cadastrar Venda                                                      |\n");
		printf("|    (3) Consultar as vendas de um vendedor em um determinado mes.            |\n");
		printf("|    (4) Consultar o total das vendas de um determinado vendedor.             |\n");
		printf("|    (5) Mostrar o numero do vendedor que mais vendeu em um determinado mes.  |\n");
		printf("|    (6) Mostrar o numero do mes com mais vendas.                             |\n");
		printf("|    (7) Mudar o nome.                                                        |\n");
		printf("|    (8) Finalizar o programa.                                                |\n");
		printf("|-----------------------------------------------------------------------------|\n");
		printf("\nInforme a opcao desejada: ");
		scanf ("%d",&op);

		switch(op){
				case 1:
					cadastrarVendedor();
					break;

				case 2:
					cadastrarVenda();
					break;

				case 3:
					consultarVendas();
					break;

				case 4:
					consultarTotal();
					break;

				case 5:
					consultarMelhorVendedor();
					break;

				case 6:
					consultarMelhorMes();
					break;

				case 7:
					MudarNome(nome);
					system("cls");
					break;

				case 8:
					sair = 1;
					break;
			}
	}
}

