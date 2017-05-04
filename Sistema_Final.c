#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define mV 10
#define meses 12
typedef float** MatrizVendas;
typedef struct 
{
	int idVendedor, mesVenda;
	float valorVenda;
}Vendas;

void cadastrarVendedor(){
	//Cadastra um vendedor, através de um número, sua ID, até um máximo de 10 vendedores
	FILE *arquivo;
    int j = 0, count = 0, pausa = 0, codigoVendedor = 0;
    int status = 1;
    float codigoVendedorTemp = 0;
    
	arquivo = fopen("vendedores.txt","a+");

	if(arquivo == NULL){
		printf("Arquivo nao pode ser aberto \n\n");
		system("pause");
	}

	printf("Informe o codigo do vendedor: ");
	scanf("%d",&codigoVendedor);

	system("clear");

	while((!feof(arquivo)))
		{
			fscanf(arquivo,"%d",&j);
			if(count>=mV)
			{
				printf("Limite atingido.\n\n");
				pausa=1;
				break;
			}
			count++;
			if(codigoVendedor==j)
			{
				printf("Esse codigo ja esta sendo utilizado por outro vendedor,ignorando comando\n\n");
				pausa=1;
				break;
			}
		}
	
	if(!pausa)
	{
		
		fprintf(arquivo, "%d\n",codigoVendedor);
		printf("Vendedor Registrado com sucesso \n\n");
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

    int j = 0, existe=0;
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
	system("clear");
	if(existe){
		if(v.mesVenda<1 || v.mesVenda>12){
			printf("Mes Invalido\n");
		}
		else{
		fprintf(arquivo, "%d\n%d\n%.2f\n", v.idVendedor, v.mesVenda, v.valorVenda);
		}
	}
	else{
		printf("Vendedor nao existe. Comando ignorado\n\n");
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
	
	system("clear");
	if(existe){
		printf("O Valor Vendido nesse mes pelo vendedor %d foi R$ %.2f\n\n", codigoVendedor, totalVendames);
	}
	else
		printf("Valor inexistente\n");
	

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
	system("clear");
	if(existe){
		printf("Total de Vendas do Vendedor %d: R$ %.2f \n\n", codigoVendedor, total);	
	}
	else{
		printf("Valor inexistente\n");
	}

}

void consultarMelhorVendedor(){
	//Consulta e mostra qual o melhor vendedor em determinado mês
	FILE *arqvenda;
	FILE *arquivo;

	arqvenda = fopen("vendedores.txt","r");

    float valorVenda = 0, vendasTemp = 0, valorTemp = 0, melhorVendas = 0;
    int mesTemp, idTemp, melhorVendedor;//idAux[10],
    int mes,i;
    int *idAux = malloc (10 * sizeof (int));
    /*
    MatrizVendas V = (MatrizVendas)calloc(mV,sizeof(float*));

    if (V == NULL)
	{
		puts("Erro aloc. matriz");
		exit(0);
	}
	for (i=0; i<mV; i++)
	{
		/* Para cada componente de V, aloca-se meses colunas*/
		/*V[i] = (float*)calloc(meses, sizeof(float));
		if (V[i]==NULL)
		{
			puts("Erro aloc. matriz");
			exit(0);
		}
	}*/


    printf("Informe o mes de venda: ");
    scanf("%d",&mes);

    system("clear");

    	for(i=0;1;i++)
		{
			fscanf(arqvenda,"%d",&idAux[i]);

			if(feof(arqvenda)) break;
		}
		for(i=0;i<mV;i++)
		{
		    arquivo = fopen("vendas.txt","r");
			vendasTemp=0;
			while(1){
			fscanf(arquivo,"%d",&idTemp);
			fscanf(arquivo,"%d",&mesTemp);
			fscanf(arquivo,"%f",&valorTemp);
			if(feof(arquivo))
			{
			    fclose(arquivo);
                break;
			}
            //printf("\n%d %d %d %.2f\n\n",idAux[i],idTemp,mesTemp,valorTemp);

			if(mesTemp==mes)
				{
					if(idAux[i]==idTemp)
					{
						vendasTemp+=valorTemp;
						//printf("%.2f\n", vendasTemp);
					}

				}

			if(vendasTemp>melhorVendas)
			{
				melhorVendas=vendasTemp;
				melhorVendedor=idTemp;
			}
			}
		}

  	printf("O vendedor com mais vendas durante o mes foi o vendedor (%d) com R$ %.2f vendidos\n\n",melhorVendedor,melhorVendas);
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
	
	system("clear");
  	
  	printf("O mes com a maior quantidade de vendas foi: %d, com R$ %.2f em vendas.\n\n", melhorMes, maior);
}

int main(){
    
	int op = 0;
	int sair = 0;
	
	system("clear");
	
	while(sair != 1){		
		
		printf("---------------------------- MENU PRINCIPAL --------------------------\n");
		printf("(1) Cadastrar Vendedor\n");
		printf("(2) Cadastrar Venda\n");
		printf("(3) Consultar as vendas de um vendedor em um determinado mês\n");
		printf("(4) Consultar o total das vendas de um determinado vendedor\n");
		printf("(5) Mostrar o numero do vendedor que mais vendeu em um determinado mes\n");
		printf("(6) Mostrar o numero do mes com mais vendas\n");
		printf("(7) Finalizar o programa\n\n");
		printf("Informe a opcao desejada: ");
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
					sair = 1;
					break;	
			}
	}
}