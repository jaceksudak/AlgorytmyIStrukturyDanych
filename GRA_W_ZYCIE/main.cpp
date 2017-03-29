#include <iostream>
#include <stdio.h>

using namespace std;

struct komorka {
    int pozycja, ilu_mam_sasiadow;
    char wartosc, wartosc_nowsza;
    komorka *sasiad[8];

    void ustaw_sasiadow(komorka *tab[],int x,int y);
    void ustal_ilosc_sasiadow();
    void ustal_stan();
    void nowy_stan();
    komorka();
};

komorka::komorka() {
    sasiad[0] = 0; sasiad[1] = 0; sasiad[2] = 0;
    sasiad[3] = 0;                sasiad[4] = 0;
    sasiad[5] = 0; sasiad[6] = 0; sasiad[7] = 0;
}

void komorka::ustaw_sasiadow(komorka *tab[], int x, int y)
{
    if(pozycja==0) {
        sasiad[0] = 0;                  sasiad[1] = 0;                  sasiad[2] = 0;
        sasiad[3] = 0;                                                  sasiad[4] = tab[pozycja+1];
        sasiad[5] = 0;                  sasiad[6] = tab[pozycja+x];     sasiad[7] = tab[pozycja+x+1];
    } else if(pozycja<x-1) {
        sasiad[0] = 0;                  sasiad[1] = 0;                  sasiad[2] = 0;
        sasiad[3] = tab[pozycja-1];                                     sasiad[4] = tab[pozycja+1];
        sasiad[5] = tab[pozycja+x-1];   sasiad[6] = tab[pozycja+x];     sasiad[7] = tab[pozycja+x+1];
    } else if(pozycja==x-1) {
        sasiad[0] = 0;                  sasiad[1] = 0;                  sasiad[2] = 0;
        sasiad[3] = tab[pozycja-1];                                     sasiad[4] = 0;
        sasiad[5] = tab[pozycja+x-1];   sasiad[6] = tab[pozycja+x];     sasiad[7] = 0;
    } else if(((pozycja+1)/x==y)&&((pozycja+1)%x==0)) {
        sasiad[0] = tab[pozycja-x-1];   sasiad[1] = tab[pozycja-x];     sasiad[2] = 0;
        sasiad[3] = tab[pozycja-1];                                     sasiad[4] = 0;
        sasiad[5] = 0;                  sasiad[6] = 0;                  sasiad[7] = 0;
    } else if(((pozycja+1)/x==y-1)&&((pozycja+1)%x==1)){
        sasiad[0] = 0;                  sasiad[1] = tab[pozycja-x];     sasiad[2] = tab[pozycja-x+1];
        sasiad[3] = 0;                                                  sasiad[4] = tab[pozycja+1];
        sasiad[5] = 0;                  sasiad[6] = 0;                  sasiad[7] = 0;
    } else if((pozycja+1)%x==1) {
        sasiad[0] = 0;                  sasiad[1] = tab[pozycja-x];     sasiad[2] = tab[pozycja-x+1];
        sasiad[3] = 0;                                                  sasiad[4] = tab[pozycja+1];
        sasiad[5] = 0;                  sasiad[6] = tab[pozycja+x];     sasiad[7] = tab[pozycja+x+1];
    } else if((pozycja+1)%x==0) {
        sasiad[0] = tab[pozycja-x-1];   sasiad[1] = tab[pozycja-x];     sasiad[2] = 0;
        sasiad[3] = tab[pozycja-1];                                     sasiad[4] = 0;
        sasiad[5] = tab[pozycja+x-1];   sasiad[6] = tab[pozycja+x];     sasiad[7] = 0;
    } else if ((pozycja+1)/x==y-1) {
        sasiad[0] = tab[pozycja-x-1];   sasiad[1] = tab[pozycja-x];     sasiad[2] = tab[pozycja-x+1];
        sasiad[3] = tab[pozycja-1];                                     sasiad[4] = tab[pozycja+1];
        sasiad[5] = 0;                  sasiad[6] = 0;                  sasiad[7] = 0;
    } else {
        sasiad[0] = tab[pozycja-x-1];   sasiad[1] = tab[pozycja-x];     sasiad[2] = tab[pozycja-x+1];
        sasiad[3] = tab[pozycja-1];                                     sasiad[4] = tab[pozycja+1];
        sasiad[5] = tab[pozycja+x-1];   sasiad[6] = tab[pozycja+x];     sasiad[7] = tab[pozycja+x+1];
    }
}
void komorka::ustal_stan()
{
    int zywi_sasiedzi=0;
    for(int i=0;i<8;i++)
        if(sasiad[i]!=0)
            if(sasiad[i]->wartosc=='#') zywi_sasiedzi++;
    if(zywi_sasiedzi==3) wartosc_nowsza='#';
    else if (zywi_sasiedzi==2) wartosc_nowsza=wartosc;
    else wartosc_nowsza='.';
}

void komorka::ustal_ilosc_sasiadow()
{
    int zywi_sasiedzi=0;
    for(int i=0;i<8;i++)
        if(sasiad[i]!=0)
            if(sasiad[i]->wartosc=='#') zywi_sasiedzi++;
    ilu_mam_sasiadow=zywi_sasiedzi;
}

void komorka::nowy_stan()
{
    wartosc=wartosc_nowsza;
}

int main()
{
    int x, y, t;
    char temp;
    cin >> x >> y >>t;
    komorka *plansza[x*y];                                                          // utworzenie planszy
    scanf("%c",&temp);
    for(int j=0;j<y;j++) {                                                          // wczytanie planszy
        for(int i=0;i<x;i++) {
            komorka *nowa=new komorka;
            nowa->pozycja=(j*y+i);
            scanf("%c",&(nowa->wartosc));
            plansza[(j*y+i)]=nowa;
        }
        scanf("%c",&temp);
    }
    for(int i=0;i<(x*y);i++) plansza[i]->ustaw_sasiadow(plansza,x,y);                // ustawianie wskaznikow na sasiadow
    while(t--){
        for(int i=0;i<(x*y);i++) plansza[i]->ustal_stan();
        for(int i=0;i<(x*y);i++) plansza[i]->nowy_stan();
    }
    for(int i=0;i<(x*y);i++) plansza[i]->ustal_ilosc_sasiadow();

    for(int j=0;j<y;j++) {                                                          // wypisanie planszy
        for(int i=0;i<x;i++) cout << plansza[j*y+i]->wartosc;
        cout << endl;
    }
    for(int j=0;j<y;j++) {                                                          // wypisanie sasiadow komorek
        for(int i=0;i<x;i++) cout << plansza[j*y+i]->ilu_mam_sasiadow;
        cout << endl;
    }


    return 0;
}
