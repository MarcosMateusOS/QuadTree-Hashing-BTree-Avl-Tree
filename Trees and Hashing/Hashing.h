#include <vector>
#include <iostream>
#include <cstdlib>

#include "Registro.h"

#ifndef HASHING_H_INCLUDED
#define HASHING_H_INCLUDED



using namespace std;
class Hashing
{
private:
    Registro *tabelaHash;
    int tam;
    int chavesArmazenadas;
    vector<int> tabeladeIndex;
    

public:
    Hashing(int tam);
    ~Hashing();
    int funcaoHash(int val,int i);
    int funcaoHash2(int val,int i);
    int insere(int codigo,Registro *r);
    int auxInsere(Registro* v,int codigo, Registro r);
    int getChavesArmazenadas();
    double fatorCarga(int n, int d);
    void verificaRedistribuicao(int n);
    void imprimeTXT(std::ofstream& myfile);
    void imprime();
    bool verifica(int ha);
    int hash(int val);
    int hash1(int val);
    int hash2(int val);
    bool cheio();
    void casosTotaisCidade(int codigoCidade);
    int getCodigo(int i);
    int getData(int i);
    int getCasos(int i);
    int getID(int i);
    void embaralhar();
    int getTam(){return tam;};
    string getNome(int codigo);
    void casosTotaisCidadePorNome(string nome);
    //int getContaColisao(){return contaColisao;};
    string buscaNome(int i);
    string data(int i);




};

#endif // HASHING_H_INCLUDED