#include "AVLTree.h"
#include <cmath>


AVLTree::AVLTree()
{
    raiz = NULL;
}

AVLTree::~AVLTree()
{
    // destrutor vazio (só para avaliação)
}

int AVLTree::max(int a, int b) 
{ 
    return (a > b)? a : b; 
}

int AVLTree::altura()
{
    if(raiz == NULL)
    {
        cout << "Arvore Vazia!" << endl;
        return -1;
    }
    else
        return auxAltura(raiz);
}

int AVLTree::alturaNo(NoArv *p)
{
    if(p == NULL)
    {
        return -1;
    }
    else
        return auxAltura(p);
}

int AVLTree::auxAltura(NoArv *p)
{
    if(p!=NULL)
    {
        int he = auxAltura(p->getEsq());
        int hd = auxAltura(p->getDir());

        return 1 + (he > hd ? he : hd);
    }
    else return -1;
}

int AVLTree::getBalanceada(NoArv *N) 
{ 
    if (N == NULL) 
        return 0;
    else 
        return N->getAltura(N->getDir()) - N->getAltura(N->getEsq()); 
} 

NoArv* AVLTree::rotacaoSimplesEsquerda(NoArv *p)
{
    /*rotSimplesEsq(p)
        r = p->dir
        p->dir = r->esq
        r->esq = p */

    NoArv* r = p->getDir();
    p->setDir(r->getEsq());

    r->setEsq(p);

    //atualiza alturas
    p->setAltura(max(p->getAltura(p->getEsq()), p->getAltura(p->getDir())) + 1);
    r->setAltura(max(r->getAltura(r->getEsq()), r->getAltura(r->getDir())) + 1);

    //raiz = q;
    return r;
}

NoArv* AVLTree::rotacaoSimplesDireita(NoArv *p)
{
    /*rotSimplesDir(p)
        r = p->esq
        p->esq = r->dir
        r->dir = p */

    NoArv* r = p->getEsq();
    p->setEsq(r->getDir());

    r->setDir(p);

    //atualiza alturas
    p->setAltura(max(p->getAltura(p->getEsq()), p->getAltura(p->getDir())) + 1);
    r->setAltura(max(r->getAltura(r->getEsq()), r->getAltura(r->getDir())) + 1);

    //raiz = q;
    return r;
}

int AVLTree::comparaData(int x,NoArv *p,Hashing *tabela)
{
  
    if(tabela->getData(x) < tabela->getData(p->getInfo()))
        return 1;
    else 
        return 0;
}
int AVLTree::comparaCodigo(int x,NoArv *p,Hashing *tabela)
{
  
    if(tabela->getCodigo(x) < tabela->getCodigo(p->getInfo()))
        return 1;
    else if(tabela->getCodigo(x) > tabela->getCodigo(p->getInfo()))
        return -1;
    else 
        return 0;
}

NoArv* AVLTree::veOBalanceio(NoArv* p)
{
    
    if((getBalanceada(p) == 2) && (  getBalanceada(p->getDir()) == 1  || 
                                    getBalanceada(p->getDir()) == 0  ))
    {
        return rotacaoSimplesEsquerda(p);
    }
    // Rotacao simples a direita:

    if((getBalanceada(p) ==-2) && (  getBalanceada(p->getEsq()) == -1  ||
                                     getBalanceada(p->getEsq()) == 0  ))

        return rotacaoSimplesDireita(p);

    // Rotacao dupla a esquerda:
    
    if((getBalanceada(p) == 2) && (  getBalanceada(p->getDir()) ==-1  ))
    {
        
        p->setDir(rotacaoSimplesDireita(p->getDir()));
        return rotacaoSimplesEsquerda(p);
    }
        //p->setDir(rotacaoSimplesDireita(p->getDir()));
        //return rotacaoSimplesEsquerda(p);

    // Rotacao dupla a direita:

    if((getBalanceada(p) ==-2) && (  getBalanceada(p->getEsq()) == 1  ))
    {
        //cout << "tem essa ota bobera" << endl;
        p->setEsq(rotacaoSimplesEsquerda(p->getEsq()));
        return rotacaoSimplesDireita(p);
    }
        //p->setEsq(rotacaoSimplesEsquerda(p->getEsq()));
        //return rotacaoSimplesDireita(p);
 
    return p;
}

void AVLTree::insere(int x,Hashing *tabela)
{
    raiz = auxInsere(raiz, x,tabela);
}

NoArv* AVLTree::auxInsere(NoArv *p, int x,Hashing *tabela)
{   
    if(p == NULL)
    {
        p = new NoArv();
        p->setInfo(x);
        p->setEsq(NULL);
        p->setDir(NULL);
        p->setAltura(1);
    } 

    else if(comparaCodigo(x,p,tabela) == 1)
        p->setEsq(auxInsere(p->getEsq(), x,tabela));
    else if(comparaCodigo(x,p,tabela) == -1)
        p->setDir(auxInsere(p->getDir(),x,tabela));
    else if(comparaCodigo(x,p,tabela) ==0)
    {   
        if(comparaData(x,p,tabela))
            p->setEsq(auxInsere(p->getEsq(), x,tabela));
        else
            p->setDir(auxInsere(p->getDir(),x,tabela));
    }else //valor igual, retorna pois n pode na AVL
        return p;
    
    // atualiza altura desse no ancestral

    p->setAltura(1 + max(p->getAltura(p->getEsq()), p->getAltura(p->getDir())));
    
    // checa se o No esta balanceado
    int equilibrio = getBalanceada(p); 
    //cout << "o no com chave " << p->getInfo() << " tem balanceamento "     << equilibrio  << endl; 
    //p->setAltura(alturaNo(p));
    //cout << "o no com chave " << p->getInfo() << " possui altura igual a " << p->getAltura() << endl; 
    // Se está desbalanceada, vai ser um dos 4 casos:
    // Rotacao simples a esquerda:
    
    return veOBalanceio(p);
}

void AVLTree::imprime(Hashing *tabela)
{
    auxImprime(raiz,tabela);
    cout << endl;
}

void AVLTree::imprimeTXT(Hashing *tabela,std::ofstream& myfile)
{
    auxImprimeTXT(raiz,tabela,myfile);
    cout << endl;
}

void AVLTree::auxImprimeTXT(NoArv *p,Hashing *tabela,std::ofstream& myfile)
{
    if(p != NULL)
    {
        myfile<<"id: "<<p->getInfo()<<"|Nome da cidade: "<<tabela->buscaNome(p->getInfo())<<"|Codigo: "<<tabela->getCodigo(p->getInfo())<<"|Data: "<<tabela->data(p->getInfo())<<endl;
        auxImprimeTXT(p->getEsq(),tabela,myfile);
        auxImprimeTXT(p->getDir(),tabela,myfile);
    }
}

void AVLTree::auxImprime(NoArv *p,Hashing *tabela)
{
    if(p != NULL)
    {
        cout<<"id: "<<p->getInfo()<<"|Nome da cidade: "<<tabela->buscaNome(p->getInfo())<<"|Codigo: "<<tabela->getCodigo(p->getInfo())<<"|Data: "<<tabela->data(p->getInfo())<<endl;
        auxImprime(p->getEsq(),tabela);
        auxImprime(p->getDir(),tabela);
    }
}

void AVLTree::buscaCodigo(int codigo, int &cont, Hashing *tabela,int &comparacao)
{
    cont = 0;
    auxBuscaCodigo(codigo, raiz, cont, tabela,comparacao);
    cout << endl;
}

void AVLTree::auxBuscaCodigo(int codigo, NoArv *raiz, int &cont, Hashing *tabela,int &comparacao)
{
    NoArv* p = raiz;

    if(p != NULL)
    {
        if(tabela->getCodigo(p->getInfo()) == codigo)
        {
            cont = cont + tabela->getCasos(p->getInfo());
            comparacao = comparacao + 1;
            auxBuscaCodigo(codigo, p->getEsq(),cont, tabela,comparacao);
            auxBuscaCodigo(codigo, p->getDir(),cont, tabela,comparacao);
        }
        else if(tabela->getCodigo(p->getInfo()) > codigo){
            auxBuscaCodigo(codigo, p->getEsq(),cont, tabela,comparacao);
            comparacao = comparacao + 1;
        }
        else{
            auxBuscaCodigo(codigo, p->getDir(),cont, tabela,comparacao);
            comparacao = comparacao + 1;
        }        
    }
    return;
}

