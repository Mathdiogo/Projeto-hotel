#include <stdio.h>
#include <stdlib.h>

typedef struct hospede{
	int quarto;			// número do quarto
	char nome[80];
	int acompanhante;	// quantidade de acompanhantes
	char categoria;		// [S]olteiro / [F]amiliar
	int dias;			// tempo de permanência - em dias
}hospede;

typedef struct quarto{
	int num;			// número do quarto
	char categoria;		// [S]olteiro / [F]amiliar
	char status;		// [L]ivre / [O]cupado
}quarto;

void aloca_quarto(quarto **pq,int tam);
void aloca_hospede(hospede **ph,int tam);
void cadastro_quarto(quarto *pq,int tam);
void cadastro_hospede(hospede *ph,quarto *pq,int tam);
int  busca_quarto(quarto *pq,int tam,char categoria);
void check_out(hospede *ph,int qtde,quarto *pq,int tam,int nquarto);
void mostra_quarto(quarto *pq, int tam);
int busca_vago(hospede *ph, int qtde);

main()
{
quarto *pq=NULL;
hospede *ph=NULL;
int op,cont=0,nquarto, posicao;

aloca_quarto(&pq,15);
cadastro_quarto(pq,15);
do{
	system("cls");
	printf("\n[1]Check-in\n[2]Check-out\n[3]Fim\nOpcao: ");
	scanf("%i",&op);
	fflush(stdin);
	switch(op)
	  {
	  	case 1: pisicao = busca_vago(ph, cont);
	  			if(posicao == -1)
	  			{
				aloca_hospede(&ph,cont+1); 
	  			cadastro_hospede(ph+cont,pq,15);
	  			cont++;
	  			}
	  			else 
	  			cadastro_hospede(ph+cont, pq, 15);
	  			break;
	  			
	  	case 2: printf("\nQuarto a ser encerrado: ");
	  			scanf("%i",&nquarto);
	  			fflush(stdin);
	  			check_out(ph,cont,pq,15,nquarto);
	  			
	  	case 3:mostra_hospedes(ph,cont);
	  		
	  			break;
	  			
	  	case 4:
	  		
	  }//switch
  }while(op!=3);

}//main

void aloca_quarto(quarto **pq,int tam)
{
if((*pq=(quarto*)realloc(*pq,tam*sizeof(quarto)))==NULL)
  exit(1);
}//aloca_quarto

void aloca_hospede(hospede **ph,int tam)
{
if((*ph=(hospede*)realloc(*ph,tam*sizeof(hospede)))==NULL)
  exit(1);
}//aloca_hospede

void cadastro_quarto(quarto *pq,int tam)
{
int i;
for(i=0;i<tam;i++)
  {
  	(pq+i)->num=i+1;
  	if(i<5)
  	  (pq+i)->categoria='S';
  	else{
  	(pq+i)->categoria='F';
  	(pq+i)->status='L';
  		}
  }//for
printf("\nQuartos cadastrados com sucesso\n\n");
}//cadastro_quarto

void cadastro_hospede(hospede *ph,quarto *pq,int tam)
{
printf("\nNome: ");
gets(ph->nome);
fflush(stdin);
do{
    printf("\nQuantos acompanhantes - max.3: ");
    scanf("%i",&ph->acompanhante);
    fflush(stdin);
  }while(ph->acompanhante<0 || ph->acompanhante>3);
printf("\nQuantos dias: ");
scanf("%i",&ph->dias);
fflush(stdin);
if(ph->acompanhante==0)
  ph->categoria='S';
else
  ph->categoria='F';
ph->quarto=busca_quarto(pq,tam,ph->categoria);  
if(ph->quarto==-1)  
  printf("\nQuarto indisponivel");
else
  printf("\nCadastro realizado com sucesso - Quarto: %i\n\n",ph->quarto);
system("pause");
}//cadastro_hospede

int  busca_quarto(quarto *pq,int tam,char categoria)
{
int i;
for(i=0;i<tam;i++,pq++)
  if(pq->categoria==categoria && pq->status=='L')
    {
	  pq->status='O';
	  return pq->num;
    }//if
return -1;
}//busca_quarto

void check_out(hospede *ph,int qtde,quarto *pq,int tam,int nquarto)
{
int i;
float valor;
for(i=0;i<qtde;i++,ph++)   //hospede
  if(ph->quarto==nquarto)
    {
    	if(ph->categoria=='S')
    	  valor=85;
    	else
    	  valor=45;
    	valor=(ph->acompanhante+1)*valor*ph->dias;
    	printf("\nNome: %s\nAcompanhantes: %i\nCategoria: %c\nDias: %i\nValor a ser pago: %.2f\n\n",ph->nome,ph->acompanhante,ph->categoria,ph->dias,valor);
    	ph->quarto=-1;   //sinalizar que o hospede deixou o hotel
	}//if
for(i=0;i<tam;i++,pq++)	
  if(pq->num==nquarto)
    pq->status='L';     //liberei o quarto	
system("pause");
}//check_out

void mostra_quarto(quarto *pq, int tam)
{
	int i;
	for(i=0;i<tam;i++,pq++)
		printf("\nQuarto: %d\nCategoria: %c\nStatus: %c\n\n", pq->num, pq->categoria, pq->status);
}

int busca_vago(hospede *ph, int qtde)
{
	int i;
	for(i=0; i<qtde;i++, ph++)
	{
		if(ph->quarto == -1);
		return i;
	}
	return -1;
	
}
