#ifndef AVLTree_H
#define AVLTree_H
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "NoArv.h"
#include "Hashing.h"

using namespace std;

class AVLTree
{
public:
    AVLTree();
    ~AVLTree();
    void imprime(Hashing *tabela);
    int comparaData(int x,NoArv *p,Hashing *tabela);
    int comparaCodigo(int x,NoArv *p,Hashing *tabela);
    int max(int, int);
    int getBalanceada(NoArv*);
    NoArv* veOBalanceio(NoArv* p);
    void insere(int x, Hashing *tabela);
    int altura();
    int alturaNo(NoArv*);
    void buscaCodigo(int codigo, int &cont, Hashing *tabela,int &comparaca);
    NoArv* rotacaoSimplesEsquerda(NoArv*);
    NoArv* rotacaoSimplesDireita(NoArv*);
    NoArv* rotacaoDuplaEsquerda(NoArv*);
    NoArv* rotacaoDuplaDireita(NoArv*);
    void imprimeTXT(Hashing *tabela,std::ofstream& myfile);

private:
    NoArv *raiz;

    // funcoes auxiliares
    NoArv* auxInsere(NoArv *p, int x,Hashing *tabela);
    void auxImprime(NoArv *p,Hashing *tabela);
    int auxAltura(NoArv* p);
    void auxImprimeNivel(NoArv *p, int cont, int k);
    float auxMediaNivel(NoArv *p, int atual, int *cont, float *soma, int k);
    void auxBuscaCodigo(int codigo, NoArv *raiz, int &cont, Hashing *tabela,int &comparacao);
    void auxImprimeTXT(NoArv *p,Hashing *tabela,std::ofstream& myfile);
    
};

#endif //AVLTree_H