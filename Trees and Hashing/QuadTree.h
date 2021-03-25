#include <iostream> 
#include <cmath> 
#include <vector>
#include "NoArvQuad.h"
using namespace std; 


class QuadTree
{
    private:
        
        NoArvQuad *raiz;
        NoArvQuad* auxInsere(NoArvQuad *r,NoArvQuad *p);
        void auxImprime(NoArvQuad *p);
        void auxCidadesNoIntervalo(vector<NoArvQuad*> &vet, std::ofstream& myfile, NoArvQuad *p, float x0, float x, float y0, float y);
        void auxImprimeTXT(NoArvQuad *p,std::ofstream& myfile);
        int cont;
      

    public:
        QuadTree();
        ~QuadTree();
        void insere(NoArvQuad *r);
        NoArvQuad* compara(NoArvQuad *r,NoArvQuad *p);
        NoArvQuad* quadrante(NoArvQuad *r,NoArvQuad *p);
        NoArvQuad* buscaValor(NoArvQuad *r);
        void imprime();
        void imprimeTXT(std::ofstream& myfile);
        void imprimeCapital();
        void auxImprimeCapital(NoArvQuad *p);
        void cidadesNoIntervalo(vector<NoArvQuad*> &vet, std::ofstream& myfile, float x0, float x, float y0, float y);
        int getCont(){ return cont; };
        
        


};



