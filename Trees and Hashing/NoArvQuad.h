#include <iostream> 
#include <cmath> 
using namespace std; 


class NoArvQuad
{
    
    private:
        string nome;
        int codigoCidade;
        float latitude;
        float longitude;
        bool capital=false;
        NoArvQuad *ne=NULL;
        NoArvQuad *nw=NULL;
        NoArvQuad *sw=NULL;
        NoArvQuad *se=NULL;
    public:
        NoArvQuad()   {};
        ~NoArvQuad()  {};

        void setLatitude(float lat){latitude = lat;};
        void setLongitude(float longe){longitude=longe;};
        void setNome(string nom){nome=nom;};
        void setCodigo(int cod){codigoCidade=cod;};

        void setNE(NoArvQuad *s){ne=s;};
        void setNW(NoArvQuad *s){nw=s;};
        void setSW(NoArvQuad *s){sw=s;};
        void setSE(NoArvQuad *s){se=s;};

        void setCapital(bool capi){capital=capi;};
        float getLatitude(){return latitude;};
        float getLongitude(){return longitude;};
        bool getCapital(){return capital;};
        int getCodigo(){return codigoCidade;};
        string getNome(){return nome;};

        NoArvQuad* getNE(){return ne;};
        NoArvQuad* getNW(){return nw;};
        NoArvQuad* getSW(){return sw;};
        NoArvQuad* getSE(){return se;};
        
        
       


};