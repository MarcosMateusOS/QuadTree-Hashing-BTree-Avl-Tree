#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <climits>
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <vector>
#include "QuadTree.h"
#include "AVLTree.h"
#include "ArvB.h"
#include "RegistroCoordinates.h"

using namespace std;

using namespace std::chrono;
#define TAMANHOMAX 1431490
#define QUANTCIDADES 5571


//g++ -o teste -O3 *.cpp
//.teste
void menuPrincipal(Registro *registros,RegistroCoordinates *registrosCoord,Hashing *hashPrinci,QuadTree *quadPrinci,int *idhash,int t,string nomeArq);
void moduloTeste(Registro *registro, RegistroCoordinates *registroCidades,Hashing *hashPrinci,QuadTree *quadPrinci,int *idhash,int t,string nome);


void criaArquivoSaidaTxt(string nomeArquivo)
{
    ofstream arq(nomeArquivo);
    arq.close();
}

void testeQuadTree(RegistroCoordinates *registroCidades, int N)
{

    QuadTree *quad = new QuadTree();

    //arq."Cidades Inseridades na QuadTree"<<endl;
   
    for (int i = 0; i < N; i++)
    {
        NoArvQuad *no = new NoArvQuad();
        no->setLatitude(registroCidades[i].getLatitude());
        no->setLongitude(registroCidades[i].getLongitude());
        no->setNome(registroCidades[i].getcidade_nome());
        no->setCodigo(registroCidades[i].getcidadeCodigo());
        quad->insere(no);
      
    }
   
    

    if (N <= 20)
    {
        cout << "Saida Console" << endl;
        quad->imprime();
    }
    else
    {
        cout << "Arquivo TXT criado" << endl;
        ofstream arq; // ("a:lista.dat", ios::ate | ios::out | ios::in)
        arq.open("QuadTree.txt", ios::ate | ios::out | ios::in);
        quad->imprimeTXT(arq);
        arq.close();
    }
    cout << "Final" << endl;
}

void testeHash(Registro *registro, int N)
{

    Hashing *hash = new Hashing(N);
    int cont = 0;
    register int chave, id;

    
    for (int i = 0; i < N; i++)
    {
        
        chave = registro[i].getCodigoCidade() + registro[i].getDataInt();
        id = hash->insere(chave, &registro[i]);
        cont++;
       
    }
    
    if (N <= 20)
    {
        cout << "Saida no Console ===> Cidades Inseridas na Hash" << endl;
        hash->imprime();
    }
    else
    {
        cout << "Arquivo TXT criado" << endl;
        ofstream arq; // ("a:lista.dat", ios::ate | ios::out | ios::in)
        arq.open("Hashing.txt", ios::ate | ios::out | ios::in);
        hash->imprimeTXT(arq);
        arq.close();
    }
    cout << endl;
    cout << "Teste finalizado" << endl;
}

void testeAvl(Registro *registro, int N)
{
    Hashing *hash = new Hashing(N);
    register int chave, id;
    AVLTree *avl = new AVLTree();

    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        chave = registro[i].getCodigoCidade() + registro[i].getDataInt();
        id = hash->insere(chave, &registro[i]);
        avl->insere(id, hash);
    }
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    cout<<"Tempo de Insercao: "<<(duration_cast<duration<double>>(fim - inicio).count())<<endl;

    if (N <= 20)
    {
        cout << "Saida no Console ===> Cidades Inseridas na Hash" << endl;
        avl->imprime(hash);
    }
    else
    {
        cout << "Arquivo TXT criado" << endl;
        ofstream arq; // ("a:lista.dat", ios::ate | ios::out | ios::in)
        arq.open("Avl.txt", ios::ate | ios::out | ios::in);
        avl->imprimeTXT(hash, arq);
        arq.close();
    }
  
    int cont=0;
    cout << "Teste finalizado" << endl;
    hash->~Hashing();
}
void testeAVB(Registro *registro, int N,int *idhash,int tam)
{
    Hashing *hash = new Hashing(N);
    int cont = 0;
    register int chave, id;
    ArvB *arvB = new ArvB(20);

    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        chave = registro[i].getCodigoCidade() + registro[i].getDataInt();
        id = hash->insere(chave, &registro[i]);
        arvB->insereArvB(id, hash);
    }
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    cout<<"Tempo de Insercao: "<<(duration_cast<duration<double>>(fim - inicio).count())<<endl;
    if (N <= 20)
    {

        cout << "Saida no Console ===> Cidades Inseridas na Hash" << endl;
        arvB->imprimeArv(hash);
    }
    else
    {
        cout << "Arquivo TXT criado" << endl;
        ofstream arq; // ("a:lista.dat", ios::ate | ios::out | ios::in)
        arq.open("AvB.txt", ios::ate | ios::out | ios::in);
        arvB->imprimeArvTXT(hash, arq);
        
    }
   
    
   
    cout << "Teste finalizado" << endl;
    cout << endl;
    
    hash->~Hashing();
}

//Etapa 1 Aqui armazena na QuadTree os Registros Coordinates
void etapa1(RegistroCoordinates *registrosCoordinate, QuadTree *quadPrincipal)
{       

        cout<<"Lendo Arquivo com as cidades e Armazenando na QuadTree"<<endl;
        registrosCoordinate->leArquivoCoordi(registrosCoordinate, QUANTCIDADES);
    
        for (int i = 0; i < QUANTCIDADES; i++)
        {
            NoArvQuad *no = new NoArvQuad();
            no->setLatitude(registrosCoordinate[i].getLatitude());
            no->setLongitude(registrosCoordinate[i].getLongitude());
            no->setNome(registrosCoordinate[i].getcidade_nome());
            no->setCodigo(registrosCoordinate[i].getcidadeCodigo());
            quadPrincipal->insere(no);
        }
  
}
//Etapa 2 Aqui armazena na Hashing os Registros
void etapa2(Registro *registros,Hashing *hashingPrincipal,int *idhash,string nome)
{   
    cout<<"Lendo Registros e Armazenando na Hashing Table"<<endl;
    cout<<nome<<endl;
    registros->leArquivo(registros,TAMANHOMAX,nome);
    int chave, id;
    
    for (int i = 0; i < TAMANHOMAX; i++)
    {
        chave = registros[i].getCodigoCidade() + registros[i].getDataInt();
        id = hashingPrincipal->insere(chave, &registros[i]);
        idhash[i]=id; //Armazenando no vetor os ids gerados pelo hashing para a proximas etapas
                      //inserir nas Arvores B e AVL  
    }   
    
    
}
//Funcao que embaralha o vetor para gerar registros aletorios
void embaralhar(int *vet, int vetSize)
{   
    srand(time(NULL));

	for (int i = 0; i < vetSize; i++)
	{   
        if(vet[i]!=0){
            int r = rand() % vetSize;

            if(vet[r]!=0)
            {
                int temp = vet[i];
                vet[i] = vet[r];
                vet[r] = temp;
            }
        }
    }

}

double insere(int tamanho,Hashing *hashing,int *idhash,ArvB *ar)
{   
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    for(int j=0;j<tamanho;j++){

        int id=hashing->getID(j);
        ar->insereArvB(id,hashing);  
    }
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    return (duration_cast<duration<double>>(fim - inicio).count());

}

void insere2(int tamanho,Hashing *hashing,int *idhash,AVLTree *ar)
{
    for(int j=0;j<tamanho;j++){
      
        ar->insere(hashing->getID(j),hashing);
    }
}

//Funcao Para etapa 5 onde se geras as metricas para o txt
void execArvB(int TAM,int N,std::ofstream& myfile,int *idhash,Hashing *hash,int tam,int codigo)
{
   
    
    int mediaComparacao = 0;
    double mediaTempoInsere = 0;
    double mediaBusca=0;
    int val;
    int comparaMedia;
    int *c = new int;
    int *comp = new int;

    //Faz o teste para as quantidades de registros
    for (int exec = 0;exec < 5 ; exec++)
    {   
        ArvB *arvB = new ArvB(TAM);
        *c=0;
        *comp=0;
        myfile<<endl;

        myfile<<"Execução "<<exec+1<<endl;
        double tempo = insere(N,hash,idhash,arvB); 
        myfile<<"Tempo de inserção: "<<tempo<<endl;
        mediaTempoInsere = mediaTempoInsere + tempo;
        

        //Busca
        high_resolution_clock::time_point inicio2 = high_resolution_clock::now();
        arvB->buscaCodigo(codigo,hash,*c,*comp); 
        high_resolution_clock::time_point fim2 = high_resolution_clock::now();

        myfile<<"Tempo de Busca: "<<(duration_cast<duration<double>>(fim2 - inicio2).count())<<endl;
        mediaBusca = mediaBusca + (duration_cast<duration<double>>(fim2 - inicio2).count());

        val=*c;
        comparaMedia=*comp;
        myfile<<endl;
    }

    myfile<<endl;
    myfile<<"A cidade: "<<hash->getNome(codigo)<<" teve casos: "<< val/5 <<endl;
    myfile << "Media de Tempo em 5 execs de inserção: " << mediaTempoInsere / 5 << endl;
    myfile << "Media de Busca em 5 execs: " << mediaBusca / 5 << endl;
    myfile << "Media de Comparações em 5 execs: " << comparaMedia/ 5 << endl;

    delete c;
    delete comp;
    val=0;
}



//Funcao Para etapa 5 onde se geras as metricas para o txt
void execAVL(int N,std::ofstream& myfile,int *idhash,Hashing *hash,int tam,int codigo)
{
    int mediaComparacao = 0;
    double mediaTempoInsere = 0;
    double mediaBusca=0;
    int comparaMe;
    int valor;
    int *cA = new int;
    int *comp2 = new int;


    //Faz o teste para as quantidades de registros

    for (int exec = 0;exec < 5 ; exec++)
    {
        
        AVLTree *arvl = new AVLTree();
        
        *cA=0;
        *comp2=0;
        myfile<<endl;
        myfile<<"Execução "<<exec+1<<endl;
        high_resolution_clock::time_point inicio = high_resolution_clock::now();
        insere2(N,hash,idhash,arvl);   
        high_resolution_clock::time_point fim = high_resolution_clock::now();
        myfile<<"Tempo de inserção: "<<(duration_cast<duration<double>>(fim - inicio).count())<<endl;
        mediaTempoInsere = mediaTempoInsere + (duration_cast<duration<double>>(fim - inicio).count());
        

        //Busca
        high_resolution_clock::time_point inicio2 = high_resolution_clock::now();
        arvl->buscaCodigo(codigo,*cA,hash,*comp2); 
        high_resolution_clock::time_point fim2 = high_resolution_clock::now();
        myfile<<"Tempo de Busca: "<<(duration_cast<duration<double>>(fim2 - inicio2).count())<<endl;
        mediaBusca = mediaBusca + (duration_cast<duration<double>>(fim2 - inicio2).count());

        valor=*cA;
        comparaMe=*comp2;
        myfile<<endl;
        
    }
    myfile<<endl;
    myfile<<"A cidade: "<<hash->getNome(codigo)<<" teve casos: "<<valor/5<<endl;
    myfile << "Media de Tempo em 5 execs de inserção: " << mediaTempoInsere / 5 << endl;
    myfile << "Media de Busca em 5 execs: " << mediaBusca / 5 << endl;
    myfile << "Media de Comparações em 5 execs: " << comparaMe/ 5 << endl;

    delete cA;
    delete comp2;
    valor=0;


}

//Função S1
void buscaCasosS1(Hashing *hashPrinci,int *idHash,int tam)
{   
    int tamanhoN[] = {10000, 50000, 100000, 500000, 1000000};
    int opt;
    int codigo;
    int M=5;
    cout<<"Escolha como quer buscar a cidade" << endl;
    cout<<"Digite o Codigo da cidade"<<endl;
    cin >> codigo;
    hashPrinci->embaralhar();
    
    criaArquivoSaidaTxt("saidaS1.txt");
    ofstream arq1;
    arq1.open("saidaS1.txt", ios::ate | ios::out | ios::in);

    
    
    arq1<<"Arvore B com norma(10)"<<endl;
    for(int i=0;i<5;i++){
        arq1<<endl;
        arq1<<"Arvore com "<<tamanhoN[i]<<" Registros"<<endl;
        execArvB(10,tamanhoN[i],arq1,idHash,hashPrinci,tam,codigo);
        
    }
    
    arq1<<endl;
    arq1<<"Arvore B com norma(100)"<<endl;

    for(int i=0;i<5;i++){
        arq1<<endl;
        arq1<<"Arvore com "<<tamanhoN[i]<<" Registros"<<endl;
        execArvB(100,tamanhoN[i],arq1,idHash,hashPrinci,tam,codigo);
    }

    arq1<<endl;
    arq1<<"Arvore AVL"<<endl;
    for(int i=0;i<5;i++){
        arq1<<endl;
        arq1<<"Arvore com "<<tamanhoN[i]<<" Registros"<<endl;
        execAVL(tamanhoN[i],arq1,idHash,hashPrinci,tam,codigo);
    }

}
//Função S2
void funcaoS2(Hashing *hashPrinci,int *idHash,int tam,QuadTree *quadPrinci)
{
     
    hashPrinci->embaralhar();//VETOR COM TODOS OS IDS GERADOS PELO HASHING SERA EMBARALHADO PARA GERAR IDS ALEATORIOS
    srand(time(NULL));
    int tamanhoN[] = {10000, 50000, 100000, 500000, 1000000};
    float x0,y0,x,y;
    
    
    
    cout<<"Escolha o intervalo que deseja busca"<<endl;
    cout<<"x0: "<<endl; cin>> x0;
    cout<<"y0: "<<endl; cin>> y0;
    cout<<"x: "<<endl; cin>> x;
    cout<<"y: "<<endl; cin>> y;

    vector<NoArvQuad*> vet;
    criaArquivoSaidaTxt("saidaS2.txt");
    ofstream arq2;
    arq2.open("saidaS2.txt", ios::ate | ios::out | ios::in);
    
    //referencias: x -> -21.0276    y -> -44.3204 ; 
    //                                   x0,   x,  y0,   y
    //-22.4694,-48.9863,
    //-7.0918,-38.1681,

    arq2<<"Cidades no intervalo"<<endl;
    quadPrinci->cidadesNoIntervalo(vet, arq2, x0, x, y0, y);

    for(int i=0;i<vet.size();i++)
    {
        arq2<<"Nome da cidade: "<<hashPrinci->getNome(vet.at(i)->getCodigo())<<endl;
    }
    arq2<<"----------------------------------------------------"<<endl;
    
    for(int i=0;i<vet.size();i++){
        arq2<<endl;

         for(int j=0;j<5;j++){
            arq2<<endl;
            arq2<<"Arvore com "<<tamanhoN[j]<<endl;
            arq2<<"Arvore B com norma(20)"<<endl;
            execArvB(10,tamanhoN[j],arq2,idHash,hashPrinci,tam,vet.at(i)->getCodigo());
            arq2<<"Arvore B com norma(200)"<<endl;
            execArvB(100,tamanhoN[i],arq2,idHash,hashPrinci,tam,vet.at(i)->getCodigo());
            arq2<<"Arvore AVL"<<endl;
            execAVL(tamanhoN[j],arq2,idHash,hashPrinci,tam,vet.at(i)->getCodigo());
        }
         arq2<<endl;
    }
    cout<<"Txt gerado"<<endl;
    
    
  
}

//Chamada da etapa 5
void etapa5(Hashing *hashPrinci,QuadTree *quadPrinci,int *idHash,int tam)
{  
    int opt;
    cout<<"Escolha uma opcao"<<endl;
    cout<<"[1] S1 "<<endl;
    cout<<"[2] S2 "<<endl;
    cin>>opt;


    if(opt == 1){
        buscaCasosS1(hashPrinci,idHash,tam);
    }
    if(opt == 2)
    {
        funcaoS2(hashPrinci,idHash,tam,quadPrinci);
    }
}
//Menu Princicipal
void menuPrincipal(Registro *registros,RegistroCoordinates *registrosCoord,Hashing *hashPrinci,QuadTree *quadPrinci,int *idhash,int t,string nomeArq)
{   
   
    
    int menu;
    cout << "====================MENU PRINCIPAL====================" << endl;
    cout << "Digite:" << endl;
    cout << "[1] Carregar o arquivo de cidades " << endl;
    cout << "[2] Carregamento do arquivo pre-processado de casos" << endl;
    cout << "[3] Modulo de teste" << endl;
    cout << "[4] Etapa 5" << endl;
    cout << "[5] Fechar" << endl;
    cin >> menu;
    
    switch(menu)
    {
    case 1:
        system("cls");
        etapa1(registrosCoord,quadPrinci);
        cout << "Etapa 1 concluida!" << endl;
        menuPrincipal(registros,registrosCoord,hashPrinci,quadPrinci,idhash,t,nomeArq);
        break;
        
    case 2:
        system("cls");
        etapa2(registros,hashPrinci,idhash,nomeArq);
        cout << "Etapa 2 concluida!" << endl;
        menuPrincipal(registros,registrosCoord,hashPrinci,quadPrinci,idhash,t,nomeArq);
        break;
        
       
    case 3:
        system("cls");
        moduloTeste(registros, registrosCoord,hashPrinci,quadPrinci,idhash,t,nomeArq);
        cout << "Etapa 3 concluida!" << endl;
        break;
         
    case 4:
         system("cls");
         etapa5(hashPrinci,quadPrinci,idhash,t);
        menuPrincipal(registros,registrosCoord,hashPrinci,quadPrinci,idhash,t,nomeArq);
         
         break;
    case 5:
        cout << "Fechando Exec!" << endl;
        exit(1);
        break;
       
    default:
        cout << "Valor invalido" << endl;
        menuPrincipal(registros,registrosCoord,hashPrinci,quadPrinci,idhash,t,nomeArq);
        
        break;
    }
    cout << "Fim" << endl;
}
//Menu modulo de teste
void moduloTeste(Registro *registro, RegistroCoordinates *registroCidades,Hashing *hashPrinci,QuadTree *quadPrinci,int *idhash,int t,string nome)
{
    
    int menuTeste, n;
    cout << "===============Modulo de Teste===============" << endl;
    cout << "[1] Insercao de N cidades na quad tree" << endl;
    cout << "[2] Insercao de N registros na tabela hash " << endl;
    cout << "[3] Insercao de N chaves na arvore AVL" << endl;
    cout << "[4] Insercao de N chaves na arvore B" << endl;
    cout << "[5] Voltar para o menu principal" << endl;

    cin >> menuTeste;

    switch (menuTeste)
    {
    case 1:
        system("cls");
        cout << "Digite N cidades que sera inseridas" << endl;
        cin >> n;
        criaArquivoSaidaTxt("QuadTree.txt");
        testeQuadTree(registroCidades, n);
        moduloTeste(registro, registroCidades,hashPrinci,quadPrinci,idhash,t,nome);

        break;
    case 2:
         system("cls");
        cout << "Digite  N registro que sera inseridos" << endl;
        cin >> n;
        criaArquivoSaidaTxt("Hashing.txt");
        testeHash(registro, n);
        moduloTeste(registro, registroCidades,hashPrinci,quadPrinci,idhash,t,nome);

        break;
    case 3:
        system("cls");
        cout << "Digite N chaves que sera inseridas na AVL" << endl;
        cin >> n;
        criaArquivoSaidaTxt("Avl.txt");
        testeAvl(registro, n);
        moduloTeste(registro, registroCidades,hashPrinci,quadPrinci,idhash,t,nome);
        break;

    case 4:
        system("cls");
        cout << "Digite N cidades que sera inseridas na ARV B" << endl;
        cin >> n;
        criaArquivoSaidaTxt("AvB.txt");
        testeAVB(registro, n,idhash,t);
        moduloTeste(registro, registroCidades,hashPrinci,quadPrinci,idhash,t,nome);

        break;
    case 5:
        menuPrincipal(registro,registroCidades,hashPrinci,quadPrinci,idhash,t,nome);
    default:
        break;
    }
}
int main(int argc, char *argv[])
{   
    

    string filename(argv[1]);
    filename += "brazil_covid19_cities_processados.csv";
    cout<<filename<<endl;
    
  

    QuadTree *quadPrincipal = new QuadTree();
    RegistroCoordinates *registrosCoordinate = new RegistroCoordinates[QUANTCIDADES];
    Registro *registro = new Registro[TAMANHOMAX];
    Hashing *hashPrincipal = new Hashing(TAMANHOMAX);
    int tam = hashPrincipal->getTam();
    int *idHashing = new int[tam];
    
    
    menuPrincipal(registro,registrosCoordinate,hashPrincipal,quadPrincipal,idHashing,tam,filename);

   
    return 0;
}
