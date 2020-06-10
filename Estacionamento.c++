#include <stdlib.h>
#include <stdio.h>
#define MAXQUEUE 10

typedef struct sCarro{
    struct sCarro *next;
    struct sCarro *prev;
    int placa;
    int nDeslocamentos;
} Carro;

typedef struct sRua{ 
    struct sCarro *head;  //HEAD- Proximo da Entrada, primeiro da fila
    struct sCarro *tail;  //TAIL- Longe da Entrada, ultimo carro da fila
    int size;
} Rua;

typedef struct sEstacionamento{ 
    struct sCarro *head;  //HEAD- Proximo da saida, primeiro da fila
    struct sCarro *tail;  //TAIL- Longe da saida, ultimo carro da fila
    int size;
} Estacionamento;

Rua *criaRua();
Estacionamento *criaEstacionamento();
void insereCarro(Estacionamento *e, Rua *rua, int placa);
void removeCarro(Estacionamento *e, Rua *rua, int placa);
void mostraFilas(Estacionamento *e, Rua *rua);
void destroiFilas(Estacionamento *e, Rua *rua);

main(){
    Estacionamento *e= criaEstacionamento();
    Rua *rua= criaRua();

    insereCarro(e, rua, 1);
    insereCarro(e, rua, 2);
    insereCarro(e, rua, 3);
    insereCarro(e, rua, 4);
    insereCarro(e, rua, 5);
    insereCarro(e, rua, 6);
    insereCarro(e, rua, 7);
    insereCarro(e, rua, 8);
    insereCarro(e, rua, 9);
    insereCarro(e, rua, 10);
    insereCarro(e, rua, 11);
    insereCarro(e, rua, 12);
    insereCarro(e, rua, 13);
    
    //removeCarro(e, rua, 1);
    //removeCarro(e, rua, 2);
    //removeCarro(e, rua, 3);
    //removeCarro(e, rua, 4);
    //removeCarro(e, rua, 5);
    //removeCarro(e, rua, 6);
    //removeCarro(e, rua, 7);
    //removeCarro(e, rua, 8);
    //removeCarro(e, rua, 9);
    //removeCarro(e, rua, 10);
    //removeCarro(e, rua, 11);
    //removeCarro(e, rua, 12);
    //removeCarro(e, rua, 13);

    mostraFilas(e, rua);
    destroiFilas(e, rua);
    mostraFilas(e, rua);

    
}

Rua *criaRua(){
    Rua *rua = (Rua*)malloc(sizeof(Rua));
    rua->head = NULL;
    rua->tail = NULL;
    rua->size=0;
    return rua;
}

Estacionamento *criaEstacionamento(){
    Estacionamento *e= (Estacionamento*)malloc(sizeof(Estacionamento));
    e->head = NULL;
    e->tail = NULL;
    e->size=0;
    return e;
}

void insereCarro(Estacionamento *e, Rua *rua, int placa){
    Carro *novo_carro= (Carro*)malloc(sizeof(Carro));
    novo_carro->placa= placa;
    novo_carro->nDeslocamentos=0;

    if(e->size<MAXQUEUE){
        printf("Vagas disponiveis: %i\n",MAXQUEUE - e->size);
        if(e->size==0){
            e->head=novo_carro;
            e->head->prev=NULL;
            e->head->next=NULL;
            e->tail=novo_carro;
        }else{
            
            //percorre o estacionamento a partir do Head 
            //ate achar uma vaga vazia e adiciona o carro.
            Carro *aux= e->head;
            for(int i=0; i < e->size; i++){
                if(aux->next==NULL){
                    novo_carro->prev=aux;
                    novo_carro->next=NULL;
                    aux->next=novo_carro;
                    break;
                }
                aux=aux->next;
            }
        }
        e->size++;
        printf("Automovel adicionado ao estacionamento!\n\n");
    }

    //se o estacionamento estar lotado, o 
    //carro eh adicionado na fila de espera.
    else{
        printf("%s", "Estacionamento cheio, aguarde! \n\n");
        if(rua->size==0){
            rua->head=novo_carro;
            rua->head->prev=NULL;
            rua->head->next=NULL;
            rua->tail=novo_carro;
        } else{
            Carro *aux2= rua->head;

            for(int i=0; i < rua->size; i++){
                if(aux2->next==NULL){
                    novo_carro->prev=aux2;
                    novo_carro->next=NULL;
                    aux2->next=novo_carro;
                    break;
                }
                aux2=aux2->next;
            }
        }
        rua->size++;
    }
}

void removeCarro(Estacionamento *e, Rua *rua, int placa){
    if((e->head!=NULL)and(e->size!=0)){
        
        Carro *aux3= e->head;
        int verify=0;

        //Verifica se a placa pertence a algum 
        //carro do estacionamento e eh excluido.

        //se tiver alguem na linha de espera, automaticamente 
        //entra na ultima vaga do estacionamento.
        int i=0;
        for( i ; i < e->size; i++){
            if(aux3->placa == placa){
                Carro *auxAddDeslocacoes= aux3;
                
                printf("Carro removido!\n");
                printf("Placa: %i \n", aux3->placa);
                printf("nDeslocamentos: %i \n\n", aux3->nDeslocamentos+1);

                if(aux3== e->head){
                    e->head = aux3->next;
                    if(e->head==NULL){
                        e->tail=NULL;
                    }else{
                        aux3->next->prev=NULL;
                    }
                }else{
                    aux3->prev->next = aux3->next;
                    if(aux3->next==NULL){
                        e->tail=aux3->prev;
                    }else{
                        aux3->next->prev = aux3->prev;
                    }
                }
                
                //adiciona +1 no número de deslocações de 
                //todos os carros atrás do carro excluido.
                for(i ; i < e->size-1; i++){
                    auxAddDeslocacoes->next->nDeslocamentos= auxAddDeslocacoes->next->nDeslocamentos+1;
                    auxAddDeslocacoes= auxAddDeslocacoes->next;
                }

                free(aux3);
                e->size--;
                verify=1; 

                if(rua->size > 0){
                    Carro *entra_carro= (Carro*)malloc(sizeof(Carro));
                    int x=rua->head->placa;
                    entra_carro->placa= x;
                    entra_carro->nDeslocamentos=0;

                    //percorre o estacionamento a partir do Head ate achar 
                    //uma vaga vazia e adiciona o Head/primeiro da fila de espera.
                    Carro *auxAdd= e->head;
                    for(int i=0; i < e->size+1; i++){
                        if(auxAdd->next==NULL){
                            entra_carro->prev=auxAdd;
                            entra_carro->next=NULL;
                            auxAdd->next=entra_carro;
                            e->size++;
                            break;
                        }
                        auxAdd=auxAdd->next;
                    }

                    //Exclui o primeiro da fila de espera
                    Carro *aux4=rua->head;
                    rua->head = aux4->next;
                    if(rua->head==NULL){
                        rua->tail=NULL;
                    }else{
                        aux4->next->prev=NULL;
                    }
                    free(aux4);
                    rua->size--;

                }
                break;
            }
            aux3= aux3->next;
        }

        //Se nao encontrar no estacionamento, entao é 
        //procurado na fila de espera automaticamente.
        if(verify==0){
            Carro *aux5= rua->head;
            int i=0;
            for( i ; i < rua->size; i++){
                if(aux5->placa == placa){
                    printf("Carro removido!\n");
                    printf("Placa: %i \n", aux5->placa);
                    printf("nDeslocamentos: 0 \n\n");

                    if(aux5== rua->head){
                        rua->head = aux5->next;
                        if(rua->head==NULL){
                            rua->tail=NULL;
                        }else{
                            aux5->next->prev=NULL;
                        }
                    }else{
                        aux5->prev->next = aux5->next;
                        if(aux5->next==NULL){
                            rua->tail=aux5->prev;
                        }else{
                            aux5->next->prev = aux5->prev;
                        }
                    }
                    free(aux5);
                    rua->size--;
                    break;
                }
                aux5= aux5->next;
            } 
        }    
    }else{
        printf("Nao foi possivel excluir carro: nenhum carro no estacionamento!\n");
        exit(0);
    }
}

void mostraFilas(Estacionamento *e, Rua *rua){
    Carro *aux6= rua->head;

    printf("\n\nFila de espera: %i carros\n", rua->size);
    printf("Entrada <- <- <- <-\n");
    for(int i=0; i < rua->size; i++){
        printf("%i ",aux6->placa);
        aux6=aux6->next;
    }

    aux6= e->head;
    printf("\n\nEstacionamento: %i carros\n", e->size);
    printf("Saida <- <- <- <-\n");
    for(int i=0; i < e->size; i++){
        printf("%i ",aux6->placa);
        aux6=aux6->next;
    }

}

void destroiFilas(Estacionamento *e, Rua *rua){
    Carro *auxDestroiCarros;
    
    printf("\n\n");
    //removendo todos os carros do estacionamento
    while(e->size>0){
        auxDestroiCarros= e->head;
        if(auxDestroiCarros == e->head){
            e->head = auxDestroiCarros->next;
            if(e->head==NULL){
                e->tail=NULL;
            }else{
                auxDestroiCarros->next->prev=NULL;
            }
        }else{
            auxDestroiCarros->prev->next = auxDestroiCarros->next;
            if(auxDestroiCarros->next==NULL){
                e->tail=auxDestroiCarros->prev;
            }else{
                auxDestroiCarros->next->prev = auxDestroiCarros->prev;
            }
        }
        printf("Carro excluido, placa: %i\n", auxDestroiCarros->placa);
        free(auxDestroiCarros);
        e->size--;
    }
    
    //removendo todos os carros da linha de espera
    while(rua->size>0){
        auxDestroiCarros= rua->head;
        if(auxDestroiCarros == rua->head){
            rua->head = auxDestroiCarros->next;
            if(rua->head==NULL){
                rua->tail=NULL;
            }else{
                auxDestroiCarros->next->prev=NULL;
            }
        }else{
            auxDestroiCarros->prev->next = auxDestroiCarros->next;
            if(auxDestroiCarros->next==NULL){
                rua->tail=auxDestroiCarros->prev;
            }else{
                auxDestroiCarros->next->prev = auxDestroiCarros->prev;
            }
        }
        printf("Carro excluido, placa: %i\n", auxDestroiCarros->placa);
        free(auxDestroiCarros);
        rua->size--;
    }    

    free(e);
    free(rua);
}
