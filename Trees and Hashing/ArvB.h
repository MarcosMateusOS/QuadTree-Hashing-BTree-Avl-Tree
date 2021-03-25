#include <iostream>
#include <cstdlib>
#include <math.h>
#include "NoArvB.h"



using namespace std;

class ArvB
{
private:
    NoArvB *raiz;
    int tamanhodoNo;
public:
    ArvB(int tam);
    ~ArvB();
    //NoArvB* buscaArvB(int chave, NoArvB *p);
    void insereArvB(int chave, Hashing *tabela);
    void imprimeArv(Hashing *tabela);
    NoArvB* busca(int chave,Hashing *tabela);
    int compara(int x,int *ch,Hashing *tabela,int i);
    int comparaData(int x,int *ch,Hashing *tabela,int i);
    void imprimeArvTXT(Hashing *tabela,std::ofstream& myfile);
    void imprimeArvTXTBusca(Hashing *tabela,std::ofstream& myfile,int k,int &cont);
    void buscaCodigo(int codigo,Hashing *tabela,int &cont,int &contaComparacao);
   
};


