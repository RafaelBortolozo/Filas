//Questao 2:
//Implemente uma fila de prioridade ascendente e suas 
//operacoes, pqinsert, pqmindelete e empty, usando 
//cada um dos quatro metodos apresentados no texto.

//A questao 3 estah inclusa nesse algoritmo:

//Demonstre como classificar um conjunto de numeros de entrada usando 
//uma fila de prioridade e as operacoes pqinsert, pqmindelete e empty.

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct sElemento{ 
    struct sElemento *next;
    struct sElemento *prev;
    int dado; 
} Elemento;

typedef struct sApq{ 
    struct sElemento *front;
    struct sElemento *rear; 
    int size;
} Apq;

Apq *criaFila();
void pqInsert(Apq *apq, int dado);
void pqMinDelete(Apq *apq);
void empty(Apq *apq);
void mostraFila(Apq *apq);
void destroiFila(Apq *apq);

main(){
    Apq *apq= criaFila();

    empty(apq);
    pqInsert(apq, 10);
    pqInsert(apq, 20);
    pqInsert(apq, 30);
    pqInsert(apq, 40);
    pqInsert(apq, 5);
    pqInsert(apq, 6);
    pqInsert(apq, 7);
    pqInsert(apq, 8);
    pqInsert(apq, 9);
    pqInsert(apq, 10);
    pqInsert(apq, 1);
    pqInsert(apq, 2);
    pqInsert(apq, 3);
    pqInsert(apq, 4);
    pqInsert(apq, 5);
    pqInsert(apq, 6);
    pqInsert(apq, 7);
    pqInsert(apq, 8);
    pqInsert(apq, 9);

    mostraFila(apq);

    pqMinDelete(apq);
    
    mostraFila(apq);
    
    empty(apq);
    pqMinDelete(apq);
    pqMinDelete(apq);
    pqMinDelete(apq);
    pqMinDelete(apq);
    pqMinDelete(apq);
    pqMinDelete(apq);
    pqMinDelete(apq);
    pqMinDelete(apq);
    mostraFila(apq);
    
    destroiFila(apq);
    mostraFila(apq);
}

Apq *criaFila(){
    Apq *apq = (Apq*)malloc(sizeof(Apq));
    apq->front = NULL;
    apq->rear = NULL;
    apq->size=0;
    return apq;
}

void pqInsert(Apq *apq, int dado){
    Elemento *novo_elemento= (Elemento*)malloc(sizeof(Elemento));
    novo_elemento->dado= dado;

    //se a fila esta vazia, adiciona o primeiro elemento como front e rear da fila
    if(apq->size==0){
        apq->front=novo_elemento;
        apq->front->prev=NULL;
        apq->front->next=NULL;
        apq->rear=novo_elemento;
    }else{
        //senao, percorre a fila até encontrar o ultimo elemento e adiciona elemento
        Elemento *aux= apq->front;
        for(int i=0; i < apq->size; i++){
            if(aux->next==NULL){
                novo_elemento->prev=aux;
                novo_elemento->next=NULL;
                aux->next=novo_elemento;
                break;
            }
            aux=aux->next;
        }
    }
    apq->size++;
    printf("Elemento %i adicionado!\n", novo_elemento->dado);
    
}

void pqMinDelete(Apq *apq){
    if((apq->front!=NULL)and(apq->size!=0)){
        
        Elemento *aux= apq->front;
        Elemento *auxDelete=NULL;

        int i=0;
        int aux2=INT_MAX;
        //pesquisa qual elemento é o menor
        for( i ; i < apq->size; i++){
            if(aux->dado <= aux2){
                aux2= aux->dado;
                auxDelete=aux;
            }
            aux=aux->next;
        }

        //procedimento para remover o elemento menor
        if(auxDelete== apq->front){
            apq->front = auxDelete->next;
            if(apq->front==NULL){
                apq->rear=NULL;
            }else{
                auxDelete->next->prev=NULL;
            }
        }else{
            auxDelete->prev->next = auxDelete->next;
            if(auxDelete->next==NULL){
                apq->rear=auxDelete->prev;
            }else{
                auxDelete->next->prev = auxDelete->prev;
            }
        }

        printf("Menor elemento %i excluido!\n", auxDelete->dado);
        free(auxDelete);
        apq->size--;

    }else{
        printf("Nao foi possivel excluir elemento: nenhum elemento na fila!\n");
    }
}

void empty(Apq *apq){
    bool empty;
    if(apq->size==0){
        empty=true;
    }else{
        empty=false;
    }
    printf("\nEmpty: %s\n", empty ? "true" : "false");
}

void mostraFila(Apq *apq){
    Elemento *aux= apq->front;

    printf("\n\nFila: %i elementos\n", apq->size);
    printf("Front <- <- <- <-\n");

    for(int i=0; i < apq->size; i++){
        printf("%i ",aux->dado);
        aux=aux->next;
    }
    printf("\n\n");
}

void destroiFila(Apq *apq){
    Elemento *auxDestroiElementos;
    
    printf("\n\n");
    //todos os elementos sao destruidos pelo head
    while(apq->size>0){
        auxDestroiElementos= apq->front;
        apq->front = auxDestroiElementos->next;
        if(apq->front==NULL){
            apq->rear=NULL;
        }else{
            auxDestroiElementos->next->prev=NULL;
        }
   
        printf("Elemento destruido: %i\n", auxDestroiElementos->dado);
        free(auxDestroiElementos);
        apq->size--;
    }
    
    free(apq);
}
