#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <sstream>
#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED


using namespace std;

class Registro
{
private:
    string dataCompleta, estado, cidade;
    int casos, mortes, codigoCidade;
    bool visitado;

public:
    Registro();
    ~Registro();
    void setDataCompleta(string dataCompleta);
    void setEstado(string estado);
    void setCidade(string cidade);
    void setCodigoCidade(int codigoCidade);
    void setCasos(int casos);
    void setMortes(int mortes);
    void setVisitado( bool visitado);
    bool getVisitado();
    string getDataCompleta();
    string getEstado();
    string getCidade();
    int getCodigoCidade();
    int getCasos();
    int getMortes();
    void transformaCasosAcumuladosEmCasosDiarios(Registro *registros, int N);
    void escreveArquivoSaidaCsv(Registro *r, int size, string nomeSaidaArquivo);
    void leArquivo(Registro *r, int N,string nome);
    void selecionandoRegistrosAleatorios(Registro *registroPrincipal,Registro *registrosAux, int N);
    void preProcessamentoComMergeSort(Registro *registros, int N);
    void exibeRegistrosPreProcessados(Registro *registros, int N);
    void exibeRegistros(Registro *registros, int N);
    void escreveSaidaTxt(Registro *r, int size, string nomeSaidaArquivo);
    int getDataInt();
};

#endif 