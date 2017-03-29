#include <iostream>
#include <stdio.h>

using namespace std;

struct koral {
    int WagaMojaIDzieci, Numer, IleMamDzieci;
    koral *Tata, *Next;
    koral();
};

koral::koral() {
    IleMamDzieci=0; Next=0;
}

int main()
{
    int Ilosc, i, NumerTaty;
    double Min, wyrazenie, PolowaRafy, WagaRafy;

    scanf("%d%lf",&Ilosc,&WagaRafy);

// DYNAMICZNA TABLICA WSKAZNIKOW
    koral **lista = new koral*[Ilosc];

// KOLEJKA
    koral *Root=NULL, *Tail=NULL;

// WCZYTYWANIE KORALOWCOW
    lista[0] = new koral;
    lista[0]->WagaMojaIDzieci=WagaRafy;
    lista[0]->Numer=0;
    lista[0]->Tata=0;
    for(i=1;i<Ilosc;i++) {
            lista[i] = new koral;
            lista[i]->Numer=i;      ///??
            scanf("%d %d",&lista[i]->WagaMojaIDzieci,&NumerTaty);
            WagaRafy+=lista[i]->WagaMojaIDzieci;
            lista[i]->Tata=lista[NumerTaty];
            lista[NumerTaty]->IleMamDzieci++;
    }

// PRZESZUKIWANIE GRAFU (ZNAJDOWANIE KOMOREK BEZ DZIECI)
// PIERWSZY ZNALEZIONY DO ROOTA...
    for(i=1;i<Ilosc;i++) {
        if(lista[i]->IleMamDzieci==0) {
            Root=lista[i];
            Tail=lista[i];
            break;
        }
    }
    i++;
// ... RESZTA W KOLEJKE
    for(;i<Ilosc;i++) {
        if(lista[i]->IleMamDzieci==0) {
            Tail->Next=lista[i];
            Tail=lista[i];
        }
    }

// OBLICZENIE POLOWY WAGI RAFY - OPTYMALNE ROZWIAZANIE
    Min=WagaRafy;
    PolowaRafy=WagaRafy/2;

// UZUPELNIANIE WAGI KAZDEGO KORALOWCA
    int j=0;
    for(i=0;i<Ilosc-1;i++) {
        Root->Tata->WagaMojaIDzieci+=Root->WagaMojaIDzieci;
        Root->Tata->IleMamDzieci--;
        if(Root->Tata->IleMamDzieci==0) {
            Tail->Next=Root->Tata;
            Tail=Root->Tata;
        }
        if((PolowaRafy-Root->WagaMojaIDzieci)<0) wyrazenie=(PolowaRafy-Root->WagaMojaIDzieci)*-1;
        else wyrazenie=(PolowaRafy-Root->WagaMojaIDzieci);
// SZUKANIE WARTOSCI MINIMUM I LICZENIE ROZWIAZAN
        if(wyrazenie<Min) {
            Min=wyrazenie; j=1;
        } else if(wyrazenie==Min) j++;
        Root=Root->Next;
    }
    if((PolowaRafy-Root->WagaMojaIDzieci)<0) wyrazenie=(PolowaRafy-Root->WagaMojaIDzieci)*-1;
    else wyrazenie=(PolowaRafy-Root->WagaMojaIDzieci);
    if(wyrazenie<Min) {
        Min=wyrazenie; j=1;
    } else if(wyrazenie==Min) j++;

// WYPISANIE ROZWIAZAN
    printf("%.0lf %d\n",Min*2,j);
    for(i=0;i<Ilosc;i++)
        if(((PolowaRafy-lista[i]->WagaMojaIDzieci)*-1==Min)||((PolowaRafy-lista[i]->WagaMojaIDzieci)==Min))  printf("%d %d\n",lista[i]->Tata->Numer,lista[i]->Numer);

//    delete [] lista;

    return 0;
}
