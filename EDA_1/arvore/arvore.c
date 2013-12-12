#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int valor;
    struct no * esquerda;
    struct no * direita;
}No;

//Prototipos
int menu();

//Arvore
//Inserir
void insercao();
void inserir(struct no** , int);
No * adicionar(int);

//Excluir
void exclusao();
void excluir(No **, int);

//funcoes
int nivel(No*, int, int);
int altura(No*);
int comparar(No*, No*);
int contarFolhas(No *);
int contarNos(No *);

//balancear
int perfeitamenteBalanceada(No*);
int balanceada(No*);
void balancear(No**);
//Imprecao
void emOrdem(No *);
void preOrdem(No *);

struct no * arvore;
struct no * comp;

int main ()
{
    int valor;
    arvore = NULL;
    comp = NULL;

    while(1)
    {
        switch(menu())
        {
            case 1:
                insercao();
                break;
            case 2:
                exclusao();
                break;
            case 3:
                printf("Altura da arvore: %d", altura(arvore));
                break;
            case 4:
                if(balanceada(arvore))
                    printf("\na arvore esta balanceada\n\n");
                else
                    printf("\na arvore nao esta balanceada\n\n");
                break;
            case 5:
                if(!perfeitamenteBalanceada(arvore))
                    printf("A arvore esta perfeitamente balanceada");
                else
                    printf("A arvore nao esta perfeitamente balanceada");
                break;
            case 6:
                while(perfeitamenteBalanceada(arvore)>0)
                {
                    balancear(&arvore);
                }

                break;
            case 7:
                printf("Arvore: ");
                preOrdem(arvore);
                if(comp)
                {
                    printf("\nComp: ");
                    preOrdem(comp);
                }
                break;
            case 8:
                if(comp == NULL)
                {
                    comp = arvore;
                    arvore = NULL;
                    printf("\nInforme uma nova arvore:\n");
                }
                else
                {
                    //comparar(arvore, comp);
                    if(comparar(arvore, comp) == 0)
                        printf("Arvores iguais");
                    else
                        printf("As arvores nao sao identicas");
                }
                break;
            case 9:
                printf("numero de nos: %d", contarNos(arvore));
                break;
            case 10:
                printf("numero de folhas: %d", contarFolhas(arvore));
                break;
            case 11:
                printf("Informe valor: ");
                scanf("%d", &valor);
                printf("nivel: %d", nivel(arvore, 1, valor));
        }
    }
}

int menu ()
{
    int opcao;

    printf("\n\n1)insercao\n");
    printf("2)excluir\n");
    printf("3)altura\n");
    printf("4)Verificar Balanceamento\n");
    printf("5)Verificar Balanceamento Perfeito\n");
    printf("6)Balancear\n");
    printf("7)PreOrdem\n");
    printf("8)Comparar\n");
    printf("9)Contar Nos\n");
    printf("10)Contar Folhas\n");
    printf("11)Nivel\n");


    printf("\nEscolha uma opcao: ");
    scanf("%d", &opcao);

    return opcao;
}

void insercao()
{
    int valor;
    printf("\n\nInforme o valor: ");
    scanf("%d", &valor);

    inserir(&arvore, valor);
}

//Insere um VALOR na arvore
void inserir(No ** raiz, int valor)
{
    if(*raiz == NULL)
    {
        No * no = adicionar(valor);
        *raiz = no;
    }
    else
    {
        if(valor < (*raiz)->valor)
            inserir(&(*raiz)->esquerda, valor);
        else if(valor > (*raiz)->valor)
            inserir(&(*raiz)->direita, valor);
    }
}

No * adicionar(int valor)
{
    No * add = (No*)malloc(sizeof(No));

    add->valor = valor;
    add->esquerda = NULL;
    add->direita = NULL;

    return add;
}

//Insere um NO na arvore
void inserirNo(No ** no, No * add)
{
    if(*no == NULL)
    {
        *no = add;
    }
    else
    {
        if(add->valor < (*no)->valor)
            inserirNo(&(*no)->esquerda, add);
        else if(add->valor > (*no)->valor)
            inserirNo(&(*no)->direita, add);
    }
}


//Exclusao

void exclusao()
{
    int valor;
    printf("\nInforme valor para exlcuir: ");
    scanf("%d", &valor);

    excluir(&arvore, valor);
}

void excluir(No ** raiz, int valor)
{
    if(*raiz == NULL)
    {
        printf("\nNao foi possivel excluir.\n");
    }
    else if((*raiz)->valor == valor)
    {
        No * excluir = *raiz;
        No * auxAnt = *raiz;

        int esq = altura((*raiz)->esquerda);
        int dir = altura((*raiz)->direita);

        if(excluir->esquerda == NULL && excluir->direita == NULL)
        {
            *raiz = NULL;
        }
        else if(esq > dir)
        {
            *raiz = (*raiz)->esquerda;
            while((*raiz)->direita != NULL)
            {
                auxAnt = *raiz;
                *raiz = (*raiz)->direita;
            }
            auxAnt->direita = NULL;

            if(excluir->esquerda != NULL)
                inserirNo(&(*raiz), excluir->esquerda);
            if(excluir->direita != NULL)
                inserirNo(&(*raiz), excluir->direita);
        }
        else if( esq <= dir)
        {
            *raiz = (*raiz)->direita;
            while((*raiz)->esquerda != NULL)
            {
                auxAnt = *raiz;
                *raiz = (*raiz)->esquerda;
            }
            if(excluir != auxAnt)
                auxAnt->esquerda = NULL;

            if(excluir->esquerda != NULL)
                inserirNo(&(*raiz), excluir->esquerda);
            if(excluir->esquerda != NULL)
                inserirNo(&(*raiz), excluir->direita);
        }
        free(excluir);
    }
    else
    {
        if(valor < (*raiz)->valor)
            excluir( &(*raiz)->esquerda, valor);
        else if(valor > (*raiz)->valor)
            excluir( &(*raiz)->direita, valor);
    }

}




//Funcoes
//Altura
int altura(No * no)
{
    if(no == NULL)
        return 0;
    else
    {
        int esq = altura(no->esquerda);
        int dir = altura(no->direita);

        return 1 +(esq > dir ? esq : dir);
    }
}

//Nivel
int nivel(No * no, int niv, int valor)
{
    if(no == NULL)
        return 0;
    else
    {
        if(valor == no->valor)
            return niv;
        else
        {
            int n1 = nivel(no->esquerda, niv+1, valor);
            int n2 = nivel(no->direita, niv+1, valor);
            return  n1 > n2 ? n1 : n2;
        }
    }
}

//contarFolhas
int contarFolhas(No * no)
{
    if(no == NULL)
        return 0;
    else
    {
        if(no->esquerda == NULL && no->direita == NULL)
            return 1;
        else
        return 0 + contarFolhas(no->esquerda) + contarFolhas(no->direita);
    }
}

//ContarNos
int contarNos(No * no)
{
    if(no == NULL)
        return 0;
    else
    {
        return 1 + contarNos(no->esquerda) + contarNos(no->direita);
    }
}

//balancear
int perfeitamenteBalanceada(No * no)
{
    if(altura(no) == 0)
    {
        return 0;
    }
    else
    {
        int esq = altura(no->esquerda);
        int dir = altura(no->direita);

        if((esq - dir > 1) || (esq - dir < -1))
            return 1;
        else
        {
            int bEsq = perfeitamenteBalanceada(no->esquerda);
            int bDir = perfeitamenteBalanceada(no->direita);

            return 0 + bEsq + bDir;
        }
    }
}
int balanceada(No * no)
{
    if(altura(no) == 0)
    {
        return 1;
    }
    else
    {
        int esq = altura(no->esquerda);
        int dir = altura(no->direita);

        if((esq - dir > 1) || (esq - dir < -1))
            return 0;
        else
            return 1;
    }

}

void balancear(No ** no)
{

    if(*no == NULL)
        return;

    balancear(&(*no)->esquerda);
    balancear(&(*no)->direita);

    while(!balanceada(*no))
    {
        preOrdem(arvore);
        printf("\n\nNO: %d\n", (*no)->valor);
        int esq = altura((*no)->esquerda);
        int dir = altura((*no)->direita);

        No * add = *no;

        if(esq > dir)
        {
            printf("TROCANDO NO: %d pelo NO: %d\n", (*no)->valor, (*no)->esquerda->valor);
            *no = (*no)->esquerda;
            add->esquerda = NULL;
            inserirNo(&(*no), add);
        }
        else if(esq < dir)
        {
            printf("TROCANDO NO: %d pelo NO: %d\n", (*no)->valor, (*no)->direita->valor);
            *no = (*no)->direita;
            add->direita = NULL;
            inserirNo(&(*no), add);
        }
    }
}


//COMPARANDO
int comparar(No * arv1, No * arv2)
{
    if(arv1 == NULL && arv2 == NULL)
        return 0;
    else if((arv1 == NULL && arv2 != NULL) || (arv1 != NULL && arv2 == NULL))
        return 1;
    else if(arv1->valor == arv2->valor)
    {
        return 0 + comparar(arv1->esquerda, arv2->esquerda) + comparar(arv1->direita, arv2->direita);
    }
    else
        return 1;
}

//Imprecao
void emOrdem(No * aux)
{
    if(aux)
    {
        emOrdem(aux->esquerda);
        printf("%d ", aux->valor);
        emOrdem(aux->direita);
    }
}

void preOrdem(No * aux)
{
    if(aux)
    {
        printf("%d ", aux->valor);
        preOrdem(aux->esquerda);
        preOrdem(aux->direita);
    }
    else
        printf("NULL ");

}

void extensao(No * aux, int nivel)
{
    if(aux)
    {
        if(altura(aux) == nivel)
        {
            printf("%d\t", aux->valor);
        }
        extensao(aux->esquerda, nivel);
        extensao(aux->direita, nivel);
    }
}
