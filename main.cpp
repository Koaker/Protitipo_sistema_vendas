// GRUPO: Rafael Montedo, Rafael Alarcon 


#include <ctype.h>  	//toupper
#include <stdio.h>  	//printf e scanf 
#include <time.h>	  	// utilizar a função _strdate
#include <locale.h> 	//português
#include <stdlib.h> 	//exit
#include <string.h> 	//strcmp
#include <conio.h>  	//getche
#define QTD 100  		// numero maximo de registro no estoque

int Dia=0,Mes=0,Ano=0,i=0; // Variaveis globais para setar a DATA e para controlar o caixa.
float gcMes,gcDia;		// Variaveis globais para setar a DATA e para controlar o caixa.

//////////////////////////
//		Structs    		//
//////////////////////////
typedef struct 				//Dados do armazenamento
	{
	int cod,vdia,vmes,vano,quantidade;
	char nome[20];
	float valor;
	}Item;

typedef struct 				//Registro de um produto
	{			
	Item info[QTD];
	int cont;				//Contador da lista (proxima posição de inclusao)
	}ListaItem;
	

//////////////////////////
//      Prototipos      //
//////////////////////////
void today(void);  											//Designa a data Atual para comparativo de vencimento de produtos e informação do caixa
void cadastrar(ListaItem *pCadastro,int *autocod);			//insere os dados de cadastro do produto
void listarItem(ListaItem *pCadastro); 						// Exibe o relatório dos itens cadastrados
void ordenaval(ListaItem *pCadastro); 						// Printa a lista ordenando por prazo de validade
void vender(ListaItem *pCadastro); 							// Vende os itens em estoque.
int validaritem(ListaItem *pCadastro); 						//Faz a verificação da data de validade do produto
void passardia(void); 										//Passa um dia e controla a data
void excluir(ListaItem *pCadastro); 						//Exclui um item

//////////////////////////
//        Main          //
//////////////////////////

main ()
	{
	setlocale(LC_ALL,"Portuguese"); 		//Deixar o idioma em português
	ListaItem cadastro;
	cadastro.cont=0;						//seta o contador como 0
	int autocod=0,control=0,opcao=666;		//variaveis de controle
	today();
	while (opcao!=0)
		{
		system("cls");
		printf("\t================== MENU DE OPÇÕES ====================\n"); // Estrutura do Menu de opções
		printf("\nData Atual: %i/%i/%i\t\t Caixa total: %0.2f \nCaixa do dia: %0.2f\n\n",Dia,Mes,Ano,gcMes,gcDia);
		printf("\n [1] - Cadastrar produto.");
		printf("\n [2] - Venda.");
		printf("\n [3] - Fechar o caixa e passar o dia.");
		printf("\n [4] - Listar Itens / Relatório.");
		printf("\n [5] - Ordenar relatório (Data de validade).");
		printf("\n [6] - Excluir Produto.");
		printf("\n [0] - Sair.");
		printf("\n\n Sua opção: ");
		fflush(stdin); 					//Limpar o buffer do teclado
		scanf("%i",&opcao);
		switch(opcao) 					// Transformar a opção escolhida em letra maiúscula para opção sair e sair do laço.
			{
			case 1:
				if(Dia!=0)
					{				
					cadastrar(&cadastro,&autocod);
	        		}
				else 
					{
	        		printf("\nInforme uma data na opção 0 para continuar\n\n");		
	        		system("pause");
					}
			break;
			case 2:
				if(Dia!=0)
					{				
					vender(&cadastro);
	        		}
				else 
					{
	        		printf("\nInforme uma data na opção 0 para continuar\n\n");		
	        		system("pause");					
					}
			break;
			case 3:
				if(Dia!=0)
					{				
					passardia();
	        		}
				else 
					{
	        		printf("\nInforme uma data na opção 0 para continuar\n\n");		
	        		system("pause");
	        		}
			break;
			case 4:
				if(Dia!=0)
					{				
					listarItem(&cadastro);
	        		}
				else
					{
	        		printf("\nInforme uma data na opção 0 para continuar\n\n");		
	        		system("pause");
	        		}
			break;
			case 5:
				ordenaval(&cadastro);
			break;
			case 6:
				if(Dia!=0)
					{				
					excluir(&cadastro);
	        		}
				else 
					{
	        		printf("\nInforme uma data na opção 0 para continuar\n\n");		
	        		system("pause");
	        		}
	        break;
			case 0:
				//finaliza o switch/programa
			break;
			default:
				system("cls");
				printf("\nEscolha uma opção válida!! \n");
				system("pause");
				break;
			}
		}
	}

//////////////////////////
//        Funções       //
//////////////////////////
//Função para obtenção da data atual, conversão em int e preparação para comparativos futuros
void today(void)
	{
	char hoje[9];  										//armazena a data vigente no formato americano mm/dd/aaaa [10 digitos]
	_strdate(hoje); 									//coleta a data de hoje do sistema e joga na variavel "hoje"
	char _Ano[4] = {hoje[6],hoje[7]}; 					// Seta os caracteres da posição 6,7,8 e 9 do vetor "hoje" dentro do vetor "Ano"
	char _Mes[2] = {hoje[0],hoje[1]}; 					//seta os caracteres da posição 0 e 1 do vetor "hoje" dentro do vetor "Mes"
	char _Dia[2] = {hoje[3],hoje[4]}; 					//seta os caracteres da posição 3 e 4 do vetor "hoje" dentro do vetor "Dia"
	Ano = atoi(_Ano); 									//converte o char para int dentro da variavel
	Mes = atoi(_Mes); 									//converte o char para int dentro da variavel
	Dia = atoi(_Dia); 									//converte o char para int dentro da variavel
	Ano=Ano+2000;
   
	}

// Função cadastrar produto com codigo automatizado
void cadastrar(ListaItem *pCadastro,int *autocod)
	{
	int alex=0,sam=0,clover=0; 									// variaveis de controle para definição de data
    Item aux;                 									// variaves da struct  
	system("cls");   
	printf("\t================== MENU DE CADASTRO ====================\n\n");       
	printf("\nDigite o nome do produto: ");
	fflush(stdin);
	gets(aux.nome);
	while(alex!=1)
		{
		printf("\nDigite a data de vencimento do produto: "); 	//parametro de comparação para data por dia
		printf("\nDia: ");
		scanf("%i",&aux.vdia);
		if (aux.vdia>0 && aux.vdia<31)
			{
			alex=1;
			}
		else
			{
			system("CLS");
			printf("Digite o dia entre 1 e 30!");
			}
		}
		while(sam!=1)
			{
			printf("\nMês: ");									//parametro de comparação para data por mes
			scanf("%i",&aux.vmes);
			if(aux.vmes<13 && aux.vmes>0)
				{
				sam=1;
				}
			else
				{
				printf("Digite o mes entre 1 e 12");
				}
			}
		printf("\nAno:");
		i=pCadastro->cont;       								 // aqui a variavel global I ( INDICE ) recebe o contador para que possa ser verificado a validade do produto que esta sendo cadastrado
		scanf("%i",&aux.vano);
		pCadastro->info[pCadastro->cont]=aux;  					// aqui a struct recebe os dados da data informado pelo usuário, para conseguir verificar a validade do produto
		if(validaritem(pCadastro)==1)							//aqui chamamos a função validaritem para verificar a validade do mesmo
			{
			printf("\nDigite a quantidade de %s a ser cadastrado: ",aux.nome);
			scanf("%i",&aux.quantidade);
			while(aux.quantidade < 0)							// Evita a inclusão de quantidade negativa de produtos
				{
				system("cls");
				printf("\nNão é possível cadastrar uma quantidade negativa de %s.",aux.nome);
				printf("\nDigite a quantidade de %s a ser cadastrado: ",aux.nome);
				scanf("%i",&aux.quantidade);
				}
			printf("\nDigite o valor da unidade de %s: R$ ",aux.nome);
			scanf("%f",&aux.valor);
			while(aux.valor < 0.00)   							// Evita a inclusão de preço negativo
				{
				system("cls");
				printf("\nNão é possível cadastrar um valor negativo para: %s!",aux.nome);
				printf("\nDigite o valor da unidade de %s: R$ ",aux.nome);
				scanf("%f",&aux.valor);
				}
			++*autocod;											 //incrementação do codigo, automatizado
			aux.cod=*autocod; 
			pCadastro->info[pCadastro->cont]=aux; 				//aqui a struct recebe os dados da data informado pelo usuário novamente para ficar completo
			pCadastro->cont++;
			} 
			else 
				{		
				printf("\nNão é possivel cadastrar um produto vencido");  //Caso o produto que o usuário esteja tentando cadastrar esteja fora da validade
				}
			printf("\n\n");
			system("pause");
			system("cls");
	}

//listagem de itens
void listarItem(ListaItem *pCadastro) 										//função para listar todos os itens cadastrados
		{
		system("cls");
		printf("\t============== PRODUTOS CADASTRADOS =================\n\n");       
		if(pCadastro->cont==0)  											//condicional para caso não haja nenhum produto cadastrado
			{
			printf("\nNenhum Produto Cadastrado\n");
			}
		else
			{
			printf("Data Atual: %i/%i/%i \n\n",Dia,Mes,Ano); // aqui mostra o dia atual para comparação da data de validade dos produtos
			for(int x=0;x<pCadastro->cont;x++)
				{
				i=x; 														// aqui a variavel global i ( INDICE) recebe x do laço for para que possa ser feita a verificação da data de validade do produto 
				printf("\nCodigo do produto: %i",pCadastro->info[x].cod);  	//Informações do produto 
				printf("\nNome: %s",pCadastro->info[x].nome);
				printf("\nEstoque: %i",pCadastro->info[x].quantidade);
				printf("\nValor: R$%0.2f",pCadastro->info[x].valor);
				printf("\nData de validade: %i/%i/%i",pCadastro->info[x].vdia,pCadastro->info[x].vmes,pCadastro->info[x].vano);
				validaritem(pCadastro); 									//verificação da data de validade
				printf("\n---------------------------------------------------\n");
				}
			}
			printf("\n\n");
			system("pause");
			system("cls");
		}
	
//Função para vender itens em estoque que não estão vencidos	
void vender(ListaItem *pCadastro)
	{ 
	Item aux;
	int acod=0,control=1; // Variaveis de comparação de codigo e controle 
	system("cls");
	printf("\t============== MÓDULO DE VENDAS =================\n\n");
	if(pCadastro->cont==0) // condicional para verificar se a algum produto cadastrado
		{
		printf("\nNenhum Produto Cadastrado\n");
		}
	else
		{	
		printf ("\nDigite o nome produto que deseja vender: ");
		fflush(stdin);
		gets(aux.nome);
		for(int x=0;x<pCadastro->cont;x++)		                	  	//Laço de repeitção para procurar os produtos
			{
			if (!strcmpi(pCadastro->info[x].nome,aux.nome))    			//Condicional com a função STRING COMPARE para achar o produto solicitado pelo usuário
				{
				control=1;  											// variavel de controle
				printf ("\nNome: %s", pCadastro->info[x].nome);    		  	// INFORMAÇÕES DO PRODUTO
				printf ("\nCodigo: %i",pCadastro->info[x].cod);
				printf("\nEstoque: %i",pCadastro->info[x].quantidade);
				printf("\nValor: R$%0.2f",pCadastro->info[x].valor);
				printf("\nData de validade: %i/%i/%i",pCadastro->info[x].vdia,pCadastro->info[x].vmes,pCadastro->info[x].vano);		
				printf ("\n------------------------------\n");
				}
			}
		while(control==1)  												//Laço de repetição para o usuário inserir o código correto
			{
			if(control==1)                                           	//Condicional para proseguir com o codigo caso algum produto tenha sido encontrado
				{
				printf ("\nDigite o código do produto que deseja vender: ");
				scanf("%i",&acod);
				for(int x=0; x<pCadastro->cont;x++)						//Laço de repetição para achar o codigo da remessa dos produtos
					{       					
					i=x;                                      			//aqui a variavel global i ( INDICE) recebe x do laço for para que possa ser feita a verificação da data de validade do produto 
					if(acod==pCadastro->info[x].cod)        			//Condicional de comparação para verificar se o usuário escreveu o codigo correto
						{
						if(validaritem(pCadastro)==1)	 				// função validaritem , caso o usuário tente vender um produto fora da validade
							{			
							system("cls");	        
			 				printf("\n\nDigite a quantidade que deseja vender: ");
							scanf("%i",&aux.quantidade);
							if(aux.quantidade>pCadastro->info[x].quantidade)
								{
								printf("\nVocê não pode vender mais do que têm no estoque");
								}
							else
								{
								control=-1;		 													//Variavel de controle		
								pCadastro->info[x].quantidade -= aux.quantidade;        			//Decrementando a Variavel Acumuladora do estoque
								gcDia += (float)aux.quantidade*pCadastro->info[x].valor; 			// Transformando a variavel quantidade em float para efetuar calculo com o Valor do produto
								}                   												//Para incrementar no caixa do dia
							}       
  						}
 					}
				}
			}
		    if(acod==0)
				{
				printf("\nProduto não encontrado");
				}
		}	
		printf("\n\n");
		system("pause");
		system("cls");
	}

// Função que passa um dia, fecha o caixa e adiciona o total
void passardia(void) 			
	{
	Dia++;
	if(Dia>30)				//condicional para arrumar a data e incrementar corretamente
		{
		Dia=1;
		Mes++;
		if(Mes>12)
			{
			Ano++;
			Mes=1;
			}
		}
	gcMes +=gcDia; 			//Caixa total acumulador
	gcDia=0; 				//reseta o caixa do dia
	}	
	
//função para ordenar lista por data de validade
void ordenaval(ListaItem *pCadastro)
	{
	Item aux;
	int ord=0;																			//Variavel auxiliar para ajudar na ordenação da lista
	for(int wheysley=0;wheysley<pCadastro->cont;wheysley++)							//Percorre o vetor a partir da primeira posição
  		{
	 	for(int j=wheysley+1; j<pCadastro->cont; j++)								//Percorre a partir da posição n+1
 			{
 			if((pCadastro->info[j].vano < pCadastro->info[wheysley].vano) || 		//Faz os comparativos possiveis para ordenação da lista
			 	(pCadastro->info[j].vano == pCadastro->info[wheysley].vano && pCadastro->info[j].vmes < pCadastro->info[wheysley].vmes) || 
				(pCadastro->info[j].vano == pCadastro->info[wheysley].vano && pCadastro->info[j].vmes == pCadastro->info[wheysley].vmes && pCadastro->info[j].vdia < pCadastro->info[wheysley].vdia))
	 			{
	 			aux=pCadastro->info[wheysley];										//auxiliar recebe posição maior (que esta fora da ordem)
	 			pCadastro->info[wheysley]=pCadastro->info[j];						//posição anterior recebe a posição menor de  J
	 			pCadastro->info[j]=aux;												//J recebe a informação da variavel auxiliar(que ficou guardada)
	 			ord=1;
				}
			}
		}
	if (ord==1)																		//testa, fora do laço for(Evitando varios prints)se ordenação foi feita ou não
		{
		printf("\nOrdenação efetuada com sucesso! \n");								//informa que a operação ocorreu
	 	system("pause");
		system("cls");
		}
	else
		{
		printf("\nLista já está em ordem por prazo de validade! \n"); 				//informa que a lista ja esta ordenada para que usuário nao fique sem retorno
		system("pause");		
		system("cls");
		}
	}		
	
//função serve para verificar se o item esta ou não na validade	
int validaritem(ListaItem *pCadastro) 
	{  
	int pepeugomes=0;
	if((pCadastro->info[i].vano<Ano) || (pCadastro->info[i].vmes<Mes && pCadastro->info[i].vano<=Ano) || (pCadastro->info[i].vdia<Dia && pCadastro->info[i].vmes<=Mes && pCadastro->info[i].vano<=Ano))
		{                  
		printf("\nProduto está fora da validade\n");
    	}
	else 	
		{
		pepeugomes=1;
		printf ("\nProduto se encontra na validade\n");
		}
	return pepeugomes;  												//retorno referente ao teste de validade
	}

//Função para excluir um produto do estoque
void excluir(ListaItem *pCadastro)
	{ 
    system("cls");
    printf("\t============== EXCLUIR PRODUTOS =================\n\n");
	if(pCadastro->cont==0)              								//Condicional para testar se ha ou não um produto cadastrado
		{ 
		printf("\nNenhum produto cadastrado");
		}
	else
		{
		int acod=0,in=0,x=0; // variaveis para controle
		char resp;
		printf("\nDigite o código do produto a ser excluido: ");
		scanf("%i",&acod);
		for(x=0;x<pCadastro->cont;x++) 									// Laço de repetição para percorrer o vetor struct
			{
			if (pCadastro->info[x].cod==acod) 							//Condicional para achar o produto que o usuário quer excluir
				{
				in = x; 												// aqui o in recebe o indice do produto encontrado
				break;
				}
			}
		printf("\nDeseja confirmar a exclusão do produto %s ? <S> Sim <N> Não \nOpção: ",pCadastro->info[in].nome);  
		fflush(stdin);
		scanf("%c",&resp);
		if(toupper(resp)=='S') 											// Condicional com toupper para facilitar a confirmação do usuário caso ele insira errado
			{                    
			printf("\nProduto excluido com sucesso!");
			for(x=in;x<pCadastro->cont;x++) 							//Laço de repetição para percorrer o vetor struct que começa no produto que o usuário deseja excluir
				{	
				pCadastro->info[x]= pCadastro->info[x+1];      
				}
				pCadastro->cont--; 										//Controladora do contador de vetores
			}
		else printf("\nOperação Abortada");
		}
	printf("\n\n");
  	system("pause");
	system("cls");
	}
