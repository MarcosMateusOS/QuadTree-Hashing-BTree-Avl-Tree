#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include "NoArvB.h"


using namespace std;

NoArvB::NoArvB(int tamanho,bool f)
{
    tam = tamanho;
    folha = f;
    chaves = new int [2*tam-1];
    filhos = new NoArvB * [2*tam];
    n = 0;
    comparacoes=0;
}
int NoArvB::comparaData(int x,int *ch,Hashing *tabela,int i)
{
  
    if(tabela->getData(x) < tabela->getData(ch[i]))
        return -2;
    else 
        return 2;
}
int NoArvB::compara(int x,int *ch,Hashing *tabela,int i)
{
  
    if(tabela->getCodigo(x) < tabela->getCodigo(ch[i]))
        return -1;
    else if(tabela->getCodigo(x) > tabela->getCodigo(ch[i]))
        return 1;
    else if(tabela->getCodigo(x) == tabela->getCodigo(ch[i]))
    {
        int comp = comparaData(x,ch,tabela,i);
        return comp;
    }
    return 0;
}

void NoArvB::split(int i,NoArvB *r, Hashing *tabela)
{
    //cout<<"Split"<<endl;
    NoArvB *q = new NoArvB(r->getTam(),r->getFolha());
    q->setN(tam-1);
    
    int k;
    for(int j=0;j<tam-1;j++)
    {   
        //Transfere as chaves com valores maiores para o novo No
        q->setChave(j,r->getChaves(j+tam));
        //cout<<"Chaves K: "<<q->getChaves(j)<<endl;
        //cout<<"Chaves J: "<<r->getChaves(j+tam)<<endl;
    }

    if(r->getFolha()==false)
    {
        for(int j=0;j<tam;j++){
            q->setFilhos(j,r->getFilhos(j+tam));
        }

    }
    
    r->setN(tam-1);
    

    for(int j=n;j>=i+1;j--)
    {
        filhos[j+1]=filhos[j];
        this->setFilhos(j+1,this->getFilhos(j));
    }
    
    this->setFilhos(i+1,q);
   

    for (int j=n-1; j >= i; j--)
    {
       this->setChave(j + 1, this->getChaves(j)); 
    }
       
    
    this->setChave(i, r->getChaves(tam-1)); 
    //chaves[i]=q->chaves[tam-1];
    n=n + 1;
}



void NoArvB::insertFilho(int k, Hashing *tabela)
{
    int i = n-1;

    //cout<<"N: "<<n<<endl;
    //Se for folha inseria a chave na posição correta 
    if(folha==true){
        
        while (i>=0 && (compara(k,chaves,tabela,i) == -1 ||compara(k,chaves,tabela,i) == -2 )/*chaves[i]>k*/)
        {   
            //Ajusta as chaves dentro do No
            chaves[i+1]=chaves[i];
            i--;
        }
        chaves[i+1] = k;
        n=n+1;
       
    }else{
        
        
        while (i>=0 && (compara(k,chaves,tabela,i) == -1 ||compara(k,chaves,tabela,i) == -2 ))
        {
            i--;
        }
        // verifca OverFlow do no N folha
        if(filhos[i+1]->getN()==2*tam-1)
        {
            split(i+1,filhos[i+1],tabela);

            if((compara(k,chaves,tabela,i+1) == 1 ||compara(k,chaves,tabela,i+1) == 2 ))
                i++;
        }
       filhos[i+1]->insertFilho(k,tabela);
    }
   
}
void NoArvB::buscaCodigo(int codigo, Hashing *tabela,int &cont,int &contaComparacao)
{
    int i;
    
  
    for(i = 0; i<this->n;i++)
    {   
        contaComparacao = contaComparacao + 1;
        if(this->folha == false)
        {
            this->filhos[i]->buscaCodigo(codigo,tabela,cont,contaComparacao);
        }
        
        if(tabela->getCodigo(this->chaves[i]) == codigo)
        {   
            contaComparacao = contaComparacao + 1;
            this->setComparacoes();
            cont = cont + tabela->getCasos(chaves[i]);
        }

        if(tabela->getCodigo(this->chaves[i]) > codigo){
            contaComparacao = contaComparacao + 1;
            break;
            
        }
    
        if(this->folha == true){
            contaComparacao = contaComparacao + 1;
            break;
            
        }

        
    }

    if(this->folha == false){
        this->filhos[i]->buscaCodigo(codigo,tabela,cont,contaComparacao);
    }
}
void NoArvB::imprimeTXTBusca(Hashing  *tabela,std::ofstream& myfile, int k,int &cont)
{   
    int i;
    for(i = 0; i<this->n;i++)
    {
        if(this->folha == false)
        {
            this->filhos[i]->imprimeTXTBusca(tabela,myfile,k,cont);
        }
        
        if(tabela->getCodigo(this->chaves[i]) == tabela->getCodigo(k))
        {
            myfile<<"Id: "<< this->chaves[i]<<"|Cidade: "<<tabela->buscaNome(chaves[i])<<"|Codigo: "<<tabela->getCodigo(chaves[i])
            <<"|Data: "<<tabela->data(chaves[i])<<"|Casos: "<<tabela->getCasos(chaves[i])<<endl;
            cont = cont + tabela->getCasos(chaves[i]);
        }

    }

    if(this->folha == false){
        this->filhos[i]->imprimeTXTBusca(tabela,myfile,k,cont);
    }
}

NoArvB* NoArvB::busca_no_No(int k,Hashing *tabela)
{
   int i=0;
    
    while (i<n && (compara(k,chaves,tabela,i) == 1 ||compara(k,chaves,tabela,i) == 2))
    {
       i++;
    }

    if(tabela->getCodigo(chaves[i]) == tabela->getCodigo(k)){
        //cout<<"Chave encotrada: "<<chaves[i]<<endl;
        cout<<"Nome: "<<tabela->buscaNome(k)<<endl;
        return filhos[i]->busca_no_No(k,tabela);
    }
    
    
    if(folha == true)
        return NULL;
    
    return filhos[i]->busca_no_No(k,tabela);
}

void NoArvB::imprime(Hashing  *tabela)
{   
    int i;
    for(i = 0; i<this->n;i++)
    {
        if(this->folha == false)
        {
            this->filhos[i]->imprime(tabela);
        }

        cout<<"Id: "<< this->chaves[i]<<"|Cidade: "<<tabela->buscaNome(chaves[i])<<"|Codigo: "<<tabela->getCodigo(chaves[i])<<"|Data: "<<tabela->data(chaves[i])<<endl;

    }

    if(this->folha == false){
        this->filhos[i]->imprime(tabela);
    }
}

void NoArvB::imprimeTXT(Hashing  *tabela,std::ofstream& myfile)
{   
    int i;
    for(i = 0; i<this->n;i++)
    {
        if(this->folha == false)
        {
            this->filhos[i]->imprimeTXT(tabela,myfile);
        }

        myfile<<"Id: "<< this->chaves[i]<<"|Cidade: "<<tabela->buscaNome(chaves[i])<<"|Codigo: "<<tabela->getCodigo(chaves[i])<<"|Data: "<<tabela->data(chaves[i])<<endl;

    }

    if(this->folha == false){
        this->filhos[i]->imprimeTXT(tabela,myfile);
    }
}