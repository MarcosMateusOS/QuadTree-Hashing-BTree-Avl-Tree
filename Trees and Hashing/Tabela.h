#ifndef TABELA_H_INCLUDED
#define TABELA_H_INCLUDED
#include "Registro.h"

using namespace std;
 class Tabela
 {
 private:
    Registro info;
    int next;

public:
    Tabela();
    ~Tabela();
    Registro getInfo();
    void setInfo(Registro r);
    int getNext();
    void setNext(int val); //next
 };


#endif // TABELA_H_INCLUDED