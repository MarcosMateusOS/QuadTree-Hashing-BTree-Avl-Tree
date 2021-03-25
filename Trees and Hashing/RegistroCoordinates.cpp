#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <climits>
#include <stdio.h>
#include <string.h>
#include "RegistroCoordinates.h"

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
RegistroCoordinates::RegistroCoordinates()
{
    dataCompleta = "";
    cidade_nome = "";
    cidadeCodigo = -1;
    latitude = -1;
    longitude =-1;
    codigoEstado =-1;
   
}
RegistroCoordinates::~RegistroCoordinates() {}

void RegistroCoordinates::leArquivoCoordi(RegistroCoordinates *r,int N)
{
    ifstream arq("Arquivos/brazil_cities_coordinates.csv");

    if(!arq.is_open()){
        cout<<"ERRO LEITURA DE ARQUIVO!"<<endl;
        return;
    }
    string linha,dataCompleta,capital,nom,stringT,stringCodigoCidade,stringT2,stringT3;
    int estadoCodigo;
    float lat,longe, cidadeCodigo;
    int conta = 0;

   //Pula a primeira linha; 
    getline(arq,linha);

    while (getline(arq,linha))
    {
        stringstream ss(linha);
        getline(ss,stringT,',');
        istringstream(stringT)>>estadoCodigo;
        r[conta].setCodigoEstado(estadoCodigo);
        getline(ss,stringCodigoCidade,',');
        stringCodigoCidade.erase(stringCodigoCidade.size()-1);
        istringstream(stringCodigoCidade)>>cidadeCodigo;
        r[conta].setcidadeCodigo(cidadeCodigo);
        getline(ss,nom,',');
        r[conta].setcidade_nome(tiraAcento(nom));
        getline(ss,stringT2,',');
        istringstream(stringT2)>>lat;
        r[conta].setLatitude(lat);
        getline(ss,stringT3,',');
        istringstream(stringT3)>>longe;
        r[conta].setLongitude(longe);
        getline(ss,capital,',');
        
        
        
       
        

        if(conta>N)
            break;
        conta++;

    }
    cout<<"Arquivo lido com->"<<conta<<"cidades!"<<endl;
    arq.close();
    

}



void RegistroCoordinates::setcidade_nome(string cidadeNome)
{
    this->cidade_nome =  cidadeNome;
}

string RegistroCoordinates::getcidade_nome()
{
    return cidade_nome;

}
void RegistroCoordinates::setdataCompleta(string dataCompleta)
{
    this->dataCompleta = dataCompleta;
}
string RegistroCoordinates::getdataCompleta()
{
    return dataCompleta;
}

void RegistroCoordinates::setcidadeCodigo(int cidadeCodigo)
{            
    this->cidadeCodigo = cidadeCodigo;
}

int RegistroCoordinates::getcidadeCodigo()
{
    return cidadeCodigo;
}

void RegistroCoordinates::setLatitude(float latitude)
{
    this->latitude = latitude;
}
float RegistroCoordinates::getLatitude()
{
    return latitude;
}
void RegistroCoordinates::setLongitude(float longitude)
{
    this->longitude = longitude;
}
float RegistroCoordinates::getLongitude()
{
    return longitude;
}
void RegistroCoordinates::setCodigoEstado(int codigoEstado)
{
    this->codigoEstado = codigoEstado;
}
int RegistroCoordinates::getcodigoEstado()
{
    return codigoEstado;
}