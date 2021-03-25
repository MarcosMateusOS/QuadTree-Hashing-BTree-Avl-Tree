#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <sstream>

using namespace std;


class RegistroCoordinates
{
        private:
            string dataCompleta,cidade_nome;
            float latitude,longitude;
            int codigoEstado,cidadeCodigo;

        public:
            RegistroCoordinates();
            ~RegistroCoordinates();
            void setdataCompleta(string dataCompleta);
            void setcidade_nome(string cidadeNome);
            void setcidadeCodigo(int cidadeCodigo);
            void setLatitude(float latitude);
            void setLongitude(float longitude);
            void setCodigoEstado(int codigoEstado);
            string getdataCompleta();
            string getcidade_nome();
            int getcidadeCodigo();
            float getLatitude();
            float getLongitude();
            int getcodigoEstado();
            void leArquivoCoordi(RegistroCoordinates *r,int N);
};

