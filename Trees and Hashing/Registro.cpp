#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <algorithm> // std::swap
#include <climits>
#include <stdio.h>
#include <string.h>
#include "Registro.h"

using namespace std::chrono;
static char vogal(char c)
{
    switch (c)
    {
    case -93: case -94: case -95: case -96:
        return 'a';
        break;
    case -87: case -86:
        return 'e';
        break;
    case -83:
        return 'i';
        break;
    case -77: case-76:
        return 'o';
        break;
    case -70:
        return 'u';
        break;
    case -89:
        return 'c';
        break;
    case -125: case -126: case -127: case -128:
        return 'A';
        break;
    case -119: case -118: 
        return 'E';
        break;
    case -111:
        return 'I';
        break;
    case -109: case -108:
        return 'O';
        break;
    case -102:
        return 'U';
        break;
    default:
        return c;
        break;
    }

}
static string tiraAcento(string s)
{
    int cont = 0;
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] < 0)
        {
            s[i] = vogal(s[i+1]);
            cont ++;
            for(int j = i+1; j < s.size(); j++)
            {
                s[j] = s[j+1];
            }
        }
    }
    s.resize(s.size()-cont);
    return s;
}

Registro::Registro()
{
    dataCompleta = "";
    estado = "";
    cidade = "";
    codigoCidade = -1;
    casos = -1;
    mortes = -1;
    visitado = false;
}

Registro::~Registro() {}

void Registro::transformaCasosAcumuladosEmCasosDiarios(Registro *registros, int N)
{
    Registro *aux = new Registro[N];
    for (int i = 0; i < N; i++)
    {
        aux[i] = registros[i];
    }
    for (int i = 1; i < N; i++)
    {
        if (aux[i].getCidade() == aux[i - 1].getCidade())
        {
            registros[i].setCasos(aux[i].getCasos() - aux[i - 1].getCasos());
        }
    }
    delete[] aux;
}

void Registro::escreveArquivoSaidaCsv(Registro *r, int size, string nomeSaidaArquivo)
{
    ofstream arq(nomeSaidaArquivo);
    cout << "Escrevendo arquivo de saida..." << endl;
    arq << "data,estado,nomeCidade,codigo,casos,mortes" << endl;
    int i;
    if(r[0].getDataCompleta()!=""){
        for (i=0; i <= size-1; i++)
    {
        arq << r[i].getDataCompleta() << "," << r[i].getEstado() << "," << r[i].getCidade() << "," << r[i].getCodigoCidade() << "," << r[i].getCasos() << "," << r[i].getMortes() << endl;
    }
    }else {for (i=1; i <= size; i++)
    {
        arq << r[i].getDataCompleta() << "," << r[i].getEstado() << "," << r[i].getCidade() << "," << r[i].getCodigoCidade() << "," << r[i].getCasos() << "," << r[i].getMortes() << endl;
    }}
    
    arq.close();
}

void Registro::escreveSaidaTxt(Registro *r, int size, string nomeSaidaArquivo)
{
    ofstream arq(nomeSaidaArquivo);
    arq << "vapo";
    arq.close();
}

void Registro::leArquivo(Registro *r, int N,string nome)
{
    cout<<nome<<endl;
    ifstream arq(nome);
    if (!arq.is_open())
    {
        cout << "Problema ao abrir o Arquivo!" << endl;
        return;
    }
    string dataCompleta, estado, cidade;
    int casos, mortes;
    int codigoCidade;
    string linha, stringTemporaria1, stringTemporaria2, stringTemporaria3;
    int cont = 0;
    getline(arq, linha); //pula primeira linha
    while (getline(arq, linha))
    {

        stringstream ss(linha);
        getline(ss, dataCompleta, ',');
        r[cont].setDataCompleta(dataCompleta);
        getline(ss, estado, ',');
        r[cont].setEstado(estado);
        getline(ss, cidade, ',');
        r[cont].setCidade(tiraAcento(cidade));
        getline(ss, stringTemporaria1, ',');
        istringstream(stringTemporaria1) >> codigoCidade;
        r[cont].setCodigoCidade(codigoCidade);
        getline(ss, stringTemporaria2, ',');
        istringstream(stringTemporaria2) >> casos;
        r[cont].setCasos(casos);
        getline(ss, stringTemporaria3, ',');
        istringstream(stringTemporaria3) >> mortes;
        r[cont].setMortes(mortes);
        r[cont].setVisitado(false);

        if (cont > N)
            break;
        cont++;
    }
    cout << "Arquivo com " << cont << " registros lido com sucesso!" << endl;
    arq.close();
}

void Registro::selecionandoRegistrosAleatorios(Registro *registroPrincipal, Registro *registrosAux, int N)
{
    int somaIndex=rand() % 1000000 + 26412;;
    int indexzada=rand() % 1000000 + 26412;
    for (int i = 0; i < N; i++)
    {
        indexzada = indexzada + somaIndex;
        if(registroPrincipal[indexzada].getVisitado()){
            indexzada= indexzada+(somaIndex/3);
        }
        if(indexzada>=1431490){
            indexzada = somaIndex;
        }
        registrosAux[i] = registroPrincipal[indexzada];
        registroPrincipal[indexzada].setVisitado(true);

    }
    for (int i = 0; i < 1431490; i++){
        registroPrincipal[i].setVisitado(false);
    }
}

void Registro::exibeRegistrosPreProcessados(Registro *r, int N)
{
    for (int i = 1; i <(N+1); i++)
    {
        cout << r[i].getDataCompleta() << "," << r[i].getEstado() << "," << r[i].getCidade() << "," << r[i].getCodigoCidade() << "," << r[i].getCasos() << "," << r[i].getMortes() << endl;
    }
}
void Registro::exibeRegistros(Registro *r, int N)
{
    if(r[0].getDataCompleta()!=""){
        for (int i = 0; i <(N); i++)
        {
            cout << r[i].getDataCompleta() << "," << r[i].getEstado() << "," << r[i].getCidade() << "," << r[i].getCodigoCidade() << "," << r[i].getCasos() << "," << r[i].getMortes() << endl;
        }
    }else{
        for (int i = 1; i <(N+1); i++)
        {
            cout << r[i].getDataCompleta() << "," << r[i].getEstado() << "," << r[i].getCidade() << "," << r[i].getCodigoCidade() << "," << r[i].getCasos() << "," << r[i].getMortes() << endl;
        }
    }
    
}


void Registro::setVisitado(bool visitado)
{
    this->visitado = visitado;
}

bool Registro::getVisitado()
{
    return visitado;
}

void Registro::setDataCompleta(string dataCompleta)
{
    this->dataCompleta = dataCompleta;
}
void Registro::setEstado(string estado)
{
    this->estado = estado;
}
void Registro::setCidade(string cidade)
{
    this->cidade = cidade;
}
void Registro::setCodigoCidade(int codigoCidade)
{
    this->codigoCidade = codigoCidade;
}
void Registro::setCasos(int casos)
{
    this->casos = casos;
}
void Registro::setMortes(int mortes)
{
    this->mortes = mortes;
}

string Registro::getDataCompleta()
{
    return dataCompleta;
}
string Registro::getCidade()
{
    return cidade;
}
string Registro::getEstado()
{
    return estado;
}
int Registro::getCodigoCidade()
{
    return codigoCidade;
}
int Registro::getCasos()
{
    return casos;
}
int Registro::getMortes()
{
    return mortes;
}
int Registro::getDataInt()
{
    string str1=dataCompleta;
    string str2;

   for(int contador = 0; contador <str1.size(); contador++){

        if(str1[contador]!='-'){
            str2+=str1[contador];
        }
   }
   int data = stoi(str2);
 
    
    return data;
}