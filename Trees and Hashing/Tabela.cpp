#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <math.h>

#include "Tabela.h"
#include "Registro.h"

using namespace std;

Tabela::Tabela()
{
    setNext(-2);
}
Tabela::~Tabela(){}

Registro Tabela::getInfo()
{
    return info;
}
void Tabela::setInfo(Registro r)
{
    info = r;
}
int Tabela::getNext()
{
    return next;
}
void Tabela::setNext(int val)
{
    next = val;
}


