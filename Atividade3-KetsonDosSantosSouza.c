/*
Autor: Kétson dos Santos Souza
Curso: Ciencia da Computação
03/11/2020
*/

//importando bibliotecas
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
  amigo *listaAmgs; // lista de amigos
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
    novo -> id = id; //insere o valor de id
    novo -> idade = idade; //insere o valor da idade
    strcpy(novo -> nome, nome); //insere nome
    strcpy(novo -> email, email); //insere o nome
    novo -> prox = NULL; //o ponteiro prox aponta para NULL
    novo -> ant = NULL; //o ponteiro ant aponta para NUll
    novo -> listaAmgs = NULL; //o ponteiro listaAmgs aponta para NULL

    return novo;
}

//busca na lista ordenada
no *buscaOrd (no *L,int id){    //vai receber o ponteiro para o inicio da lista, e um id que quer procurar na lista
    no *aux = L;
    while (aux != NULL && id > aux -> id){
        if(aux -> prox == NULL) break; //verifica se  o aux seta prox é igual a NULL
        aux = aux -> prox; //caso não estaja apontando para o ultimo elemento da lista, aux aponta para o proximo elemento
    }
    return aux;
}

no *insereOrd(no *L, int id, int idade, char nome[50],char email[50]){
    no *novo = criaNo(id,idade,nome,email);  //cria um novo nó onde recebe parametros que quer inserir
    no *aux = buscaOrd(L,id); //faz uma busca pela lista ordenada, sabe que o aux vai estar apontando ou para o nó com a lista e o id que está buscando, ou para o nó sucessor ou apontando para o ultimo nó da lista
    if(aux == NULL) L = novo; //se a lista estiver vázia o L recebe novo
    else{
        //verifica se o id que está em aux é menor que a id que quer inserir
        if(aux -> id < id){
            aux -> prox = novo; //atuliza o ultimo ponteiro prox da lista
            novo -> ant = aux; //e o do ponteiro ant da lista
        }else{ // se a chave que vai inserir não for maior, que aux seta id, vai verificar se o elemento vai ser inserido no meio da lista, ou no incio da lista
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

//Função para preencher comm os dados so usuário
no *preencher(no *L){
    int id, idade;
    char nome[50], email[50];
    no *aux = NULL;

    //para preencher com os dados do usuário
    do{
        printf("\n ===INSIRA OS DADOS===");
        printf("\n ID: ");
        scanf("%d",&id);

        aux = buscaOrd(L,id);
        if(aux == NULL)
            break;
        if(aux -> id == id)
            printf("  O ID informado já existe");
    }while(aux -> id == id);//caso digite um id que ja exista

    printf("\n IDADE: ");
    scanf("%d",&idade);

    printf("\n NOME: ");
    fflush(stdin);
    gets(nome);

    printf("\n EMAIL: ");
    gets(email);
    fflush(stdin);

    L = insereOrd(L,id,idade,nome,email);

    return L;
}

//função para imprimir lista de usuário
void imprimirListaAmigos(amigo *L){
    if(L == NULL){
        printf(" Usuario não tem amigos\n");
    }else{
        amigo *aux = L;
        while(aux != NULL){
            printf(" %d",aux->id);
            aux = aux -> prox;
        }
    }
}

//Função para imprimir
void imprime(no *L, int id){
    no *aux = buscaOrd(L,id);

    if(aux == NULL || aux -> id != id){
        printf("\n O ID informado não existe\n");
    } else{
        printf("\n Dados do usuário: ");
        printf(" ID: %d",aux -> id);
        printf(" NOME: %s",aux -> nome);
        printf(" EMAIL: %s",aux -> email);
        printf(" IDADE: %d",aux -> idade);
        printf("\n ID's dos amigos: ");
        imprimirListaAmigos(aux->listaAmgs);
    }
}

amigo *criarAmigo(int id){
    amigo *novo; //ponteiro nó
    novo = (amigo*)malloc(sizeof(amigo)); //aloca

    //se a alocação falhar
    if(novo == NULL){
        printf(" ERRO: problemas com a alocação de memoria.\n");
        exit(1);
    }
    novo -> id = id; //insere o valor de id
    novo -> prox = NULL;    //o ponteiro prox aponta para NULL
    novo -> ant = NULL; //o ponteiro ant aponta para NULL

    return novo;
}

//busca amigos
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

//função para criar uma amizade
no *criarAmizade(no *L, int id1, int id2){
    //
    no *aux1 = buscaOrd(L,id1);
    no *aux2 = buscaOrd(L,id2);
    amigo *verif1;
    amigo *verif2;

    if(aux1 == NULL || aux1 -> id != id1)
        printf(" O ID não foi encontrado");

    else{
        if(aux2 == NULL || aux2 -> id != id2){
            printf(" O ID não foi encontrado");
        }
        else{
             verif1 = buscarAmigoOrd(aux1 -> listaAmgs,id2);
             verif2 = buscarAmigoOrd(aux2 -> listaAmgs,id1);
             if((verif1 != NULL && verif1->id == id2) || (verif2 != NULL && verif2 ->id == id1)){
                printf(" Já existe essa amizade\n");
             }else{
                 aux1 -> listaAmgs = inserirAmigo(aux1 -> listaAmgs,id2);
                 aux2 -> listaAmgs = inserirAmigo(aux2 -> listaAmgs,id1);
             }
         }
    }
    return L;
}

//Função para buscar amigos em comum
void amigosComum(no *L, int id1, int id2){ //recebe como parametro uma lista, e dois ID's
    //variaveis auxiliares que recebem a função busca ordenada
    no *aux1 = buscaOrd(L, id1);
    no *aux2 = buscaOrd(L, id1);
    amigo *verif1;
    amigo *verif2;

    int x = 0;

     if(aux1 == NULL || aux1 -> id != id1)
        printf(" O ID não foi encontrado");
    else{
        if(aux2 == NULL || aux2 -> id != id2){
            printf(" O ID não foi encontrado");
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
            printf(" Nenhuma amizade encontrada");
    }
}

//exclui uma amizade
amigo *umaAmizade(amigo *L, int id){
    amigo *aux = buscarAmigoOrd(L,id);

    if(aux != NULL){
        if(aux -> ant == NULL)
            L = aux -> prox;
        else
            aux -> ant -> prox = aux -> prox;
        if(aux -> prox != NULL)
            aux -> prox -> ant = aux -> ant;
        free(aux); //libera espaço ocupado por amigo em aux
    }
    return L;
}

no *ExcluiAmizade(no *L, int id1, int id2){ //recebe como parametro uma lista, e dois ID's
    //variaveis auxiliares que recebem a função busca ordenada
    no *aux1 = buscaOrd(L, id1);
    no *aux2 = buscaOrd(L, id2);
    amigo *verif1 = NULL;
    amigo *verif2 = NULL;

    if(aux1 == NULL || aux1 -> id != id1)
        printf(" O ID não foi encontrado");
    else{
        if(aux2 == NULL || aux2 -> id != id2){
            printf(" O ID não foi encontrado");
        }else{
            verif1 = buscarAmigoOrd(aux1 -> listaAmgs,id2);
            verif2 = buscarAmigoOrd(aux2 -> listaAmgs,id1);
            if((verif1 != NULL && verif1->id == id2) && (verif2 != NULL && verif2 ->id == id1)){
                aux1 -> listaAmgs = umaAmizade(aux1 -> listaAmgs, id2);
                aux2 -> listaAmgs = umaAmizade(aux2 -> listaAmgs, id1);
                printf("\n Amizade excluída.");
            }else{
                printf(" Não são amigos");
            }
        }
    }
    return L;
}
//função exclui lista de amigos de um usuario
no *excluirListaAmigos(no *L){
    if(L != NULL){
        amigo *aux = L ->listaAmgs; //aux apontando para o primeiro da lista

        /*ira atualizar L e liberar a memória de aux e aux aponta para o primeiro da lista, até a lista de amigos*/
        while(aux != NULL){
            L -> listaAmgs = L -> listaAmgs -> prox;
            free(aux);  //libera espaço ocupado por amigo em aux
            aux = L -> listaAmgs;
        }
    }
    return L;
}

//exclui um usuario e sua lista de amigos
no *excluiUsuario(no *L, int id){
    no *aux = buscaOrd(L,id); //aux vai armazenar o nó com o um id caso esteja

    //se o id não exista não exista na lista de amigos
    if(aux == NULL || aux -> id != id)
        printf("\n O ID informado não existe.\n");
        //se o id existir na lista de amigos
    else{
        if(aux != NULL){
                //se o aux se o primeiro da lista
            if(aux ->ant == NULL)
                L = aux -> prox;
        //se aux estiver no meio da lista
            else
                aux -> ant -> prox = aux -> prox;
                //casao aux não for o ultimo da lista
            if(aux -> prox != NULL)
                aux -> prox -> ant = aux -> ant;

            aux = excluirListaAmigos(aux); //vai excluir a lista de amigos do usuario de id que foi inserido

            free(aux);  //libera espaço ocupado por nó em aux

            printf("\n Usuário excluído com sucesso!");
        }
    }
    return L;

}


//Função principal
int main(){
    setlocale(LC_ALL,"portuguese");

    no *L = NULL;
    int id1, id2;
    int op;

   do{
      printf("\n");
      printf("==============================================================================\n");
      printf("                            BEM - VINDO(A) A REDE SOCIAL                        \n");
      printf("==============================================================================\n");
      printf("\n");
      printf("\n");
      printf("\n");
      printf("\n");
      printf("\n");
      printf("                            DIGITE A OPCAO:\n");
      printf("\n");
      printf("                          [1] Buscar usuário                     \n");
      printf("                          [2] Criar novo usuário                          \n");
      printf("                          [3] Excluir usuário                            \n");
      printf("                          [4] Cadastrar amizade                            \n");
      printf("                          [5] Listar amigos em comum                           \n");
      printf("                          [6] Excluir amizade                            \n");
      printf("                          [7] Sair                           \n");
      printf("\n");
      printf("\n Opção: ");
      scanf("%d",&op);
      system("cls");

      switch(op){
        case 1:
          printf("\n 1 - Buscar usuário.\n");
          printf("\n ID a ser buscado: ");
          scanf("%d",&id1);
          buscaOrd(L,id1);
          imprime(L,id1);
          break;

        case 2:
          printf("\n 2 - Criar novo usuário.\n");
          printf("\n Insira os dados do novo usuário:\n");
          L = preencher(L);
          printf("\n Usuário criado com sucesso.\n");
          break;

        case 3:
          printf("\n 3 - Excluir usuário.\n");
          printf("\n ID a ser excluido: ");
          scanf("%d",&id1);
          L = excluiUsuario(L,id1);
          break;


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
          printf("\n ID do primeiro usuário: ");
          scanf("%d",&id1);
          printf(" ID do segundo usuário:  ");
          scanf("%d",&id2);
          L = ExcluiAmizade(L,id1,id2);
          break;

        case 7:
          printf("\n Programa encerrado...");
          break;

        default:
          printf("\n Opção inválida;\n Insira um dos valores do menu.\n ");
          break;
      }
    }while(op != 7);
}
