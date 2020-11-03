/*
Kétson dos Santos Souza
Ciencia da Computação
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>

typedef struct amigo{ // estrutura para a lista de amigos de cada usuário
  int id; // id do amigo
  struct amigo *prox, *ant; // ponteiros para construção da lista de amigos
}amigo;

typedef struct usuario{ // estrutura de cada usuário
  int id; // id do usuário
  int idade; // idade do usuário
  char nome[50]; // nome do usuário
  char email[50]; // email do usuário
  amigo *listaAmgs; // lista de amigos (friend list)
  struct usuario *prox, *ant; // ponteiros para construção da lista de usuários
}no;

no *criaNo(int id, int idade, char nome[50],char email[50]){

    no *novo; //ponteiro nó
    novo = (no*)malloc(sizeof(no)); //aloca

    //se a alocação falhar
    if(novo == NULL){
        printf("ERRO: problemas com a alocação de memoria.\n");
        exit(1);
    }
    novo -> id = id;
    novo -> idade = idade;
    strcpy(novo -> nome, nome);
    strcpy(novo -> email, email);
    novo -> prox = NULL;
    novo -> ant = NULL;
    novo -> listaAmgs = NULL;

    return novo;
}

//busca na lista ordenada
no *buscaOrd (no *L,int id){
    no *aux = L;
    while (aux != NULL && id > aux -> id){
        if(aux -> prox == NULL) break;
        aux = aux -> prox;
    }
    return aux;
}

no *insereOrd(no *L, int id, int idade, char nome[50],char email[50]){
    no *novo = criaNo(id,idade,nome,email);  //cria um novo nó onde coloca a chave que quer inserir
    no *aux = buscaOrd(L,id); //faz uma busca pela lista ordenada, sabe que o aux vai estar apontando ou para o nó com a chave que está buscando, ou para o nó sucessor ou apontando para o ultimo nó da lista
    if(aux == NULL) L = novo; //se a lista estiver vázia o L recebe novo
    else{
        //verifica se a chave que está em aux é menor que a chave que quer inserir
        if(aux -> id < id){
            aux -> prox = novo; //atuliza o ultimo ponteiro prox da lista
            novo -> ant = aux; //e o do ponteiro ant da lista
        }else{ // se a chave que vai inserir não for maior, que aux seta chave, vai verificar se o elemento vai ser inserido no meio da lista, ou no incio da lista
            novo -> prox = aux;
            if(aux -> ant == NULL)  L = novo;
            else{ //se aux seta ant for diferente de NULL
                aux -> ant -> prox = novo; //
                novo -> ant = aux -> ant;
            }
            aux -> ant = novo;
        }
    }
    return L;
}

no *preencher(no *L){
    int id, idade;
    char nome[50], email[50];
    no *aux = NULL;

    do{
        printf("\n===INSIRA OS DADOS===");
        printf("\nID: ");
        scanf("%d",&id);

        aux = buscaOrd(L,id);
        if(aux == NULL)
            break;
        if(aux -> id == id)
            printf("O ID informado já existe");
    }while(aux -> id == id);

    printf("\nIDADE: ");
    scanf("%d",&idade);

    printf("\nNOME: ");
    fflush(stdin);
    gets(nome);

    printf("\nEMAIL: ");
    gets(email);
    fflush(stdin);

    L = insereOrd(L,id,idade,nome,email);

}

void imprimirListaAmigos(amigo *L){
    if(L == NULL){
        printf("Usuario não tem amigos\n");
    }else{
        amigo *aux = L;
        while(aux != NULL){
            printf(" %d",aux->id);
            aux = aux -> prox;
        }
    }
}

void imprime(no *L, int id){
    no *aux = buscaOrd(L,id);

    if(aux == NULL || aux -> id != id){
        printf("Usuario não encontrado\n");
    } else{
        printf("\n Dados do usuário: ");
        printf(" ID: %d",aux -> id);
        printf(" NOME: %s",aux -> nome);
        printf(" EMAIL: %s",aux -> email);
        printf(" IDADE: %d",aux -> idade);
        printf("\nID's dos amigos: ");
        imprimirListaAmigos(aux->listaAmgs);
    }
}

amigo *criarAmigo(int id){
    amigo *novo; //ponteiro nó
    novo = (amigo*)malloc(sizeof(amigo)); //aloca

    //se a alocação falhar
    if(novo == NULL){
        printf("ERRO: problemas com a alocação de memoria.\n");
        exit(1);
    }
    novo -> id = id;
    novo -> prox = NULL;
    novo -> ant = NULL;

    return novo;

}

amigo *buscarAmigoOrd(amigo *L, int id){
    amigo *aux = L;

    while (aux != NULL && id > aux -> id){
        if(aux -> prox == NULL) break;
        aux = aux -> prox;
    }
    return aux;
}

amigo *inserirAmigo(amigo *L, int id){
    amigo *novo = criarAmigo(id);  //cria um novo nó onde coloca a chave que quer inserir
    amigo *aux = buscarAmigoOrd(L,id); //faz uma busca pela lista ordenada, sabe que o aux vai estar apontando ou para o nó com a chave que está buscando, ou para o nó sucessor ou apontando para o ultimo nó da lista
    if(aux == NULL) L = novo; //se a lista estiver vázia o L recebe novo
    else{
        //verifica se a chave que está em aux é menor que a chave que quer inserir
        if(aux -> id < id){
            aux -> prox = novo; //atuliza o ultimo ponteiro prox da lista
            novo -> ant = aux; //e o do ponteiro ant da lista
        }else{ // se a chave que vai inserir não for maior, que aux seta chave, vai verificar se o elemento vai ser inserido no meio da lista, ou no incio da lista
            novo -> prox = aux;
            if(aux -> ant == NULL)  L = novo;
            else{ //se aux seta ant for diferente de NULL
                aux -> ant -> prox = novo; //
                novo -> ant = aux -> ant;
            }
            aux -> ant = novo;
        }
    }
    return L;
}

no *criarAmizade(no *L, int id1, int id2){

    no *aux1 = buscaOrd(L,id1);
    no *aux2 = buscaOrd(L,id2);
    amigo *verif1;
    amigo *verif2;

    if(aux1 == NULL || aux1 -> id != id1)
        printf("O  ID não foi encontrado");

    else{
        if(aux2 == NULL || aux2 -> id != id2){
            printf("O  ID não foi encontrado");
        }
        else{
             verif1 = buscarAmigoOrd(aux1 -> listaAmgs,id2);
             verif2 = buscarAmigoOrd(aux2 -> listaAmgs,id1);
             if((verif1 != NULL && verif1->id == id2) || (verif2 != NULL && verif2 ->id == id1)){
                printf("Já existe essa amizade\n");
             }else{
                 aux1 -> listaAmgs = inserirAmigo(aux1 -> listaAmgs,id2);
                 aux2 -> listaAmgs = inserirAmigo(aux2 -> listaAmgs,id1);
             }
         }
    }
    return L;
}

void amigosComum(no *L, int id1, int id2){
    no *aux1 = buscaOrd(L, id1);
    no *aux2 = buscaOrd(L, id1);
    amigo *verif1;
    amigo *verif2;

    int x = 0;

     if(aux1 == NULL || aux1 -> id != id1)
        printf("O  ID não foi encontrado");
    else{
        if(aux2 == NULL || aux2 -> id != id2){
            printf("O  ID não foi encontrado");
        }
        else{
            verif1 = aux1 -> listaAmgs;
            verif2 = aux2 -> listaAmgs;
            while(verif1 != NULL){
                while(verif2 != NULL && verif1 -> id >= verif2 -> id){
                    if(verif1 -> id == verif2 -> id){
                        printf("%d",verif1 -> id);
                        x++;
                    }
                    verif2 = verif2 -> prox;
                }
                verif2 = aux2 -> listaAmgs;
                verif1 = verif1 -> prox;
            }
        }
        if(x == 0)
            printf("Nenhuma amizade encontrada");
    }
}

int main(){
    setlocale(LC_ALL,"portuguese");

    no *L = NULL;
    int id1, id2;
    int op;

   do{
      printf("\n ==================================== MENU ====================================\n");
      printf("\n 0 - Imprimir;");
      printf("\n 1 - Buscar usuário;");
      printf("\n 2 - Criar novo usuário;");
      printf("\n 3 - Excluir usuário;");
      printf("\n 4 - Cadastrar amizade;");
      printf("\n 5 - Listar amigos em comum;");
      printf("\n 6 - Excluir amizade;");
      printf("\n 7 - Sair.");
      printf("\n Opção: ");
      scanf("%d",&op);

      switch(op){
        case 0:
          printf("\n 0 - Imprimir.\n");
          printf("ID: ");
          scanf("%d",&id1);
          imprime(L,id1);
          break;

        case 1:
          printf("\n 1 - Buscar usuário.\n");
          printf("\n ID a ser buscado: ");
          scanf("%d",&id1);
          buscaOrd(L,id1);
          imprime(L,id1);
          break;


        case 2:
          printf("\n 2 - Criar novo usuário.\n");
          printf("\nInsira os dados do novo usuário:\n");
          L = preencher(L);
          printf("\n Usuário criado com sucesso.\n");
          break;
/*
        case 3:
          printf("\n 3 - Excluir usuário.\n");
          break;
*/

    case 4:
          printf("\n 4 - Cadastrar amizade.\n");
          printf("\n ID do primeiro usuário: ");
          scanf("%d",&id1);
          printf(" ID do segundo usuário:  ");
          scanf("%d",&id2);
          L = criarAmizade(L,id1,id2);
          printf("\n Amizade cadastrada com sucesso.\n");
          break;

        case 5:
          printf("\n 5 - Listar amigos em comum.\n");
          printf("\n ID do primeiro usuário: ");
          scanf("%d",&id1);
          printf(" ID do segundo usuário:  ");
          scanf("%d",&id2);
          printf(" Amigos em comum entre %d e %d: ",id1,id2);
          amigosComum(L,id1,id2);
          break;


        case 6:
          printf("\n 6 - Excluir amizade.\n");
          break;

        case 7:
          printf("\n Saindo...");
          break;

        default:
          printf("\n Opção inválida;\n Insira um dos valores do menu.\n ");
          break;


      }

    }while(op != 7);

}
