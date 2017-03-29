#include <stdio.h>
#include <iostream>

using namespace std;


struct komorka {
    char wartosc;
    komorka *nastepna;
    komorka();
};

komorka::komorka() {
    nastepna = 0;
}


komorka *pierw_rejestr[26];


void wyswietl_rejestr(int indeks)
{
    komorka *temp = pierw_rejestr[indeks];
    while(temp) {
        cout << temp->wartosc;
        temp=temp->nastepna;
    }
    cout <<endl;
}

void zeruj_rejestr(int indeks)
{
    if (pierw_rejestr[indeks]!=0) {
        komorka *temp=pierw_rejestr[indeks];
        komorka *temp_del=pierw_rejestr[indeks];
        temp=temp->nastepna;
        while (temp_del->nastepna) {
            delete temp_del;
            temp_del=temp;
            temp=temp->nastepna;
        }
        delete temp_del;
    }
    pierw_rejestr[indeks]=0;
}

void przesun(int indeks)
{
    if (pierw_rejestr[indeks]!=0) {
        int ilosc;
        cin >> ilosc;

        komorka *temp=pierw_rejestr[indeks];
        komorka *temp_pierw=pierw_rejestr[indeks];

        for(;ilosc>1;ilosc--)  temp=temp->nastepna;

        if(temp->nastepna) {
            temp_pierw=temp->nastepna;
            temp->nastepna=0;
            temp=temp_pierw;
            temp_pierw=pierw_rejestr[indeks];
            pierw_rejestr[indeks]=temp;
            while (temp->nastepna) temp=temp->nastepna;
            temp->nastepna=temp_pierw;
        }
    }
}

void usun(int indeks)
{
    if (pierw_rejestr[indeks]!=0) {
        int ilosc;
        cin >> ilosc;

        komorka *temp=pierw_rejestr[indeks];
        komorka *temp_pierw=pierw_rejestr[indeks];

        for(;ilosc>1;ilosc--) {
            temp_pierw=temp->nastepna;
            delete temp;
            temp=temp_pierw;
        }
        if(temp->nastepna) {
            temp_pierw=temp->nastepna;
            delete temp;
            pierw_rejestr[indeks]=temp_pierw;
        } else pierw_rejestr[indeks]=0;
    }
}

void doklej(int indeks)
{
    char indeks_c2;
    int indeks2;
    cin >> indeks_c2;
    indeks2=indeks_c2-65;

    komorka *temp=pierw_rejestr[indeks];

    while(temp->nastepna) temp=temp->nastepna;
    temp->nastepna=pierw_rejestr[indeks2];
    pierw_rejestr[indeks2]=0;
}

/*            PROSTY SPOSOB NA USTAWIANIE
void ustaw_rejestr(int indeks)
{
    char temp_c;
    scanf("%c",&temp_c);
    zeruj_rejestr(indeks);
    komorka *temp=pierw_rejestr[indeks];
    komorka *nowa = new komorka;
    nowa->wartosc = temp_c;
    pierw_rejestr[indeks] = nowa;
    temp=nowa;
    scanf("%c",&temp_c);
    while(temp_c!=10) {
        komorka *nowa = new komorka;
        nowa->wartosc = temp_c;
        temp->nastepna = nowa;
        temp=nowa;
        scanf("%c",&temp_c);
    }
    temp->nastepna = 0;
} */


void ustaw_rejestr(int indeks)
{
    char temp_c;
    scanf("%c",&temp_c);
    if(pierw_rejestr[indeks]==0){
        komorka *temp=pierw_rejestr[indeks];
        komorka *nowa = new komorka;
        nowa->wartosc = temp_c;
        pierw_rejestr[indeks] = nowa;
        temp=nowa;
        scanf("%c",&temp_c);
        while(temp_c!=10) {
            komorka *nowa = new komorka;
            nowa->wartosc = temp_c;
            temp->nastepna = nowa;
            temp=nowa;
            scanf("%c",&temp_c);
        }
    } else {
        komorka *temp=pierw_rejestr[indeks];
        temp->wartosc=temp_c;
        scanf("%c",&temp_c);
        while(temp_c!=10) {
            if(temp->nastepna!=0) {
                temp=temp->nastepna;
                temp->wartosc=temp_c;
                scanf("%c",&temp_c);
            } else {
                komorka *nowa = new komorka;
                nowa->wartosc=temp_c;
                temp->nastepna=nowa;
                temp=nowa;
                scanf("%c",&temp_c);
            }
        }
        if(temp->nastepna!=0) {
            komorka *temp_del=temp;
            temp=temp->nastepna;
            temp_del->nastepna=0;
            temp_del=temp;
            temp=temp->nastepna;
            while (temp->nastepna) {
                delete temp_del;
                temp_del=temp;
                temp=temp->nastepna;
            }
            delete temp_del;
        }
    }
}


void odwroc(int indeks)
{
    if(pierw_rejestr[indeks]!=0) {
        komorka *temp=pierw_rejestr[indeks];                //pomocnik
        komorka *temp2=pierw_rejestr[indeks];               //pomocnik 2
        komorka *temp_pierw=pierw_rejestr[indeks];          //pierwsza komorka starego porzadku
        komorka *temp_now=pierw_rejestr[indeks];            //aktualna komorka nowego porzadku
        if(temp->nastepna) {
            while(temp->nastepna) {
                temp2=temp;
                temp=temp->nastepna;
            }
            temp2->nastepna=0;
            pierw_rejestr[indeks]=temp;
            temp_now=temp;
            temp_now->nastepna=temp2;
            temp=temp_pierw;

            while(temp->nastepna) {
                while(temp->nastepna) {
                    temp2=temp;
                    temp=temp->nastepna;
                }
                temp2->nastepna=0;
                temp->nastepna=temp2;
                temp=temp_pierw;
            }
        }
    }
}

void mieszaj(int indeks)
{
    char indeks_c2;
    int indeks2;
    cin >> indeks_c2;
    indeks2=indeks_c2-65;

    if(pierw_rejestr[indeks2]!=0) {
        if(pierw_rejestr[indeks]!=0) {
            komorka *temp=pierw_rejestr[indeks];
            komorka *temp2=pierw_rejestr[indeks2];
            komorka *temp3=pierw_rejestr[indeks];

            while((temp->nastepna)&&(temp2->nastepna)) {
                temp3=temp2->nastepna;
                temp2->nastepna=temp->nastepna;
                temp->nastepna=temp2;
                temp=temp2->nastepna;
                temp2=temp3;
            }

            if(temp->nastepna) {
                temp3=temp->nastepna;
                temp->nastepna=temp2;
                temp2->nastepna=temp3;
            } else temp->nastepna=temp2;

            pierw_rejestr[indeks2]=0;
        } else {
            pierw_rejestr[indeks]=pierw_rejestr[indeks2];
            pierw_rejestr[indeks2]=0;
        }
    }
}

void skopiuj(int indeks)
{
    char indeks_c2;
    int indeks2;
    cin >> indeks_c2;
    indeks2=indeks_c2-65;

    komorka *temp=pierw_rejestr[indeks];
    komorka *temp2=pierw_rejestr[indeks2];
    if(pierw_rejestr[indeks2]!=0) {
        if(pierw_rejestr[indeks]!=0) {
            while(temp->nastepna) temp=temp->nastepna;
            while(temp2->nastepna) {
                komorka *nowa = new komorka;
                nowa->wartosc = temp2->wartosc;
                temp->nastepna = nowa;
                temp=nowa;
                temp2=temp2->nastepna;
            }
            komorka *nowa = new komorka;
            nowa->wartosc = temp2->wartosc;
            temp->nastepna = nowa;
            nowa->nastepna = 0;
        } else {
            komorka *nowa = new komorka;
            nowa->wartosc = temp2->wartosc;
            pierw_rejestr[indeks] = nowa;
            temp=nowa;
            if(temp2->nastepna) {
                temp2=temp2->nastepna;
                while(temp2->nastepna) {
                    komorka *nowa = new komorka;
                    nowa->wartosc = temp2->wartosc;
                    temp->nastepna = nowa;
                    temp=nowa;
                    temp2=temp2->nastepna;
                }
                komorka *nowa2 = new komorka;
                nowa2->wartosc = temp2->wartosc;
                temp->nastepna = nowa2;
                nowa2->nastepna = 0;
            } else {
                nowa->nastepna = 0;
            }
        }
    }
}


int main()
{
    for(int i=0;i<26;i++) pierw_rejestr[i]=0;
    char polecenie[10], indeks;
    int indeks_int;
    cin >> polecenie >> indeks;
    indeks_int=indeks-65;
    scanf("%c",&indeks);                                       //usuniecie spacji
    while((polecenie[0]!=EOF)&&(polecenie[0]!=NULL)) {
        switch(polecenie[2]) {
        case 'R':                               // ZERUJ
            zeruj_rejestr(indeks_int);
            break;
        case 'P':                               // WYPISZ
            wyswietl_rejestr(indeks_int);
            break;
        case 'W':                               // ODWROC
            odwroc(indeks_int);
            break;
        case 'T':                               // USTAW
            ustaw_rejestr(indeks_int);
            break;
        case 'Z':                               // PRZESUN
            przesun(indeks_int);
            break;
        case 'U':                               // USUN
            usun(indeks_int);
            break;
        case 'K':                               // DOKLEJ
            doklej(indeks_int);
            break;
        case 'O':                               // SKOPIUJ
            skopiuj(indeks_int);
            break;
        case 'E':                               // MIESZAJ
            mieszaj(indeks_int);
            break;
        }
        cin >> polecenie >> indeks;
        indeks_int=indeks-65;
        scanf("%c",&indeks);                                  //usuniecie spacji
    }
    return 0;
}
