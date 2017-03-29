#include <iostream>

using namespace std;

struct plyta {
    plyta *sasiad[4], *next, *next2;
    int wysokosc, pozycja;
    int stan;                                       /// 0-niesprawdzony, 1-odplyw, 2-aktualnie sprawdzany, 3-zalany/odplyw, 4-zalany
    bool kaluza;

    void ustaw_sasiadow(plyta *plansza[],int w, int h);
    void wyszukaj_graf(int *wys_zalania, bool *flaga_zalewania, plyta *temp2, plyta *temp, plyta **root2);
    void zalewanie(int *wys_zalania, int *woda, bool *flaga_zalewania);
    void kolejkowanie(plyta *root2, plyta *dodawany);
    plyta();
};

plyta::plyta() {
    kaluza=false;
    stan=0;
    next=0; next2=0;
    sasiad[0]=0; sasiad[1]=0; sasiad[2]=0; sasiad[3]=0;  /// 0-gora, 1-lewo, 2-prawo, 3-dol
}

void plyta::kolejkowanie(plyta *ostatni, plyta *dodawany) {
    while(ostatni->next2)
        ostatni=ostatni->next2;
    ostatni->next2=dodawany;
    ostatni=dodawany;
}

void plyta::ustaw_sasiadow(plyta *plansza[],int w, int h) {
    if(pozycja==0) {
                                        sasiad[0] = 0;
        sasiad[1] = 0;                                                  sasiad[2] = plansza[pozycja+1];
                                        sasiad[3] = plansza[pozycja+w];
    } else if(pozycja<w-1) {
                                        sasiad[0] = 0;
        sasiad[1] = plansza[pozycja-1];                                     sasiad[2] = plansza[pozycja+1];
                                        sasiad[3] = plansza[pozycja+w];
    } else if(pozycja==w-1) {
                                        sasiad[0] = 0;
        sasiad[1] = plansza[pozycja-1];                                     sasiad[2] = 0;
                                        sasiad[3] = plansza[pozycja+w];
    } else if(((pozycja+1)/w==h)&&((pozycja+1)%w==0)) {
                                        sasiad[0] = plansza[pozycja-w];
        sasiad[1] = plansza[pozycja-1];                                     sasiad[2] = 0;
                                        sasiad[3] = 0;
    } else if(((pozycja+1)/w==h-1)&&((pozycja+1)%w==1)){
                                        sasiad[0] = plansza[pozycja-w];
        sasiad[1] = 0;                                                  sasiad[2] = plansza[pozycja+1];
                                        sasiad[3] = 0;
    } else if((pozycja+1)%w==1) {
                                        sasiad[0] = plansza[pozycja-w];
        sasiad[1] = 0;                                                  sasiad[2] = plansza[pozycja+1];
                                        sasiad[3] = plansza[pozycja+w];
    } else if((pozycja+1)%w==0) {
                                        sasiad[0] = plansza[pozycja-w];
        sasiad[1] = plansza[pozycja-1];                                     sasiad[2] = 0;
                                        sasiad[3] = plansza[pozycja+w];
    } else if ((pozycja+1)/w==h-1) {
                                        sasiad[0] = plansza[pozycja-w];
        sasiad[1] = plansza[pozycja-1];                                     sasiad[2] = plansza[pozycja+1];
                                        sasiad[3] = 0;
    } else {
                                        sasiad[0] = plansza[pozycja-w];
        sasiad[1] = plansza[pozycja-1];                                     sasiad[2] = plansza[pozycja+1];
                                        sasiad[3] = plansza[pozycja+w];
    }
}

void plyta::wyszukaj_graf(int *wys_zalania, bool *flaga_zalewania, plyta *temp2, plyta *temp, plyta **root2) {
    stan=2;
    if((sasiad[0]==0)||(sasiad[1]==0)||(sasiad[2]==0)||(sasiad[3]==0)||(sasiad[0]->stan==1)||(sasiad[1]->stan==1)||(sasiad[2]->stan==1)||(sasiad[3]->stan==1)) {
        stan=1;
        *flaga_zalewania=false;
    }
    for(int i=0;i<4;i++) {
        if(sasiad[i]!=0) {
            if(((sasiad[i]->stan==0)||(sasiad[i]->stan==4))&&(wysokosc==sasiad[i]->wysokosc)) {
                sasiad[i]->wyszukaj_graf(wys_zalania, flaga_zalewania, temp2, sasiad[i], root2);
            }
        }
    }
    if((sasiad[0]==0)||(sasiad[1]==0)||(sasiad[2]==0)||(sasiad[3]==0)||(sasiad[0]->stan==1)||(sasiad[1]->stan==1)||(sasiad[2]->stan==1)||(sasiad[3]->stan==1)) {
        stan=1;
        *flaga_zalewania=false;
    } else {
        stan=3;
        if(*root2!=temp){
            kolejkowanie(*root2,temp);
        }
        for(int i=0;i<4;i++) {
            if((sasiad[i]->wysokosc<*wys_zalania)&&(sasiad[i]->wysokosc>wysokosc))
                *wys_zalania=sasiad[i]->wysokosc;
        }
    }
}

void plyta::zalewanie(int *wys_zalania, int *woda, bool *flaga_zalewania) {

    if(*flaga_zalewania==true) {
        kaluza=true;
        *woda=*woda+*wys_zalania-wysokosc;

        wysokosc=*wys_zalania;
        stan=4;
        if(next2!=0) {
            next2->zalewanie(wys_zalania,woda,flaga_zalewania);
            next2=0;
        }
    } else {
        stan=1;
        if(next2!=0) {
            next2->zalewanie(wys_zalania,woda,flaga_zalewania);
            next2=0;
        }
    }

}

int main()
{
    int w, h, ilosc, woda=0, *wsk_woda=&woda;
    int wys_zalania, *wsk_wys_zalania=&wys_zalania;
    bool flaga_zalewania, *wsk_flaga=&flaga_zalewania;

    cin >> w >> h;
    ilosc=w*h;

    plyta **plansza = new plyta*[ilosc];
    plyta *root=NULL, *tail=NULL, *temp=NULL;
    plyta **root2=NULL, *temp2=NULL;

    plansza[0] = new plyta;
    plansza[0]->pozycja=0;
    cin >> plansza[0]->wysokosc;
    root=plansza[0];
    tail=plansza[0];
    temp=root;

/// WCZYTYWANIE DANYCH NA PLANSZE
    for(int i=1;i<ilosc;i++) {
        plansza[i] = new plyta;
        plansza[i]->pozycja=i;
        cin >> plansza[i]->wysokosc;

        /// SORTOWANIE KOLEJKI WEDLUG WYSOKOSCI
        if(plansza[i]->wysokosc<=root->wysokosc) {
            plansza[i]->next=root;
            root=plansza[i];
        } else {
            temp=root;
            for(;;) {
                if(temp->next) {
                    if(plansza[i]->wysokosc>temp->next->wysokosc) {
                        temp=temp->next;
                    } else {
                        plansza[i]->next=temp->next;
                        temp->next=plansza[i];
                        break;
                    }
                } else {
                    temp->next=plansza[i];
                    tail=plansza[i];
                    break;
                }
            }
        }
    }

/// USTAWIENIE WSKAZNIKOW SASIADOW
    for(int i=0;i<ilosc;i++)
        plansza[i]->ustaw_sasiadow(plansza,w,h);

/// ZALEWANIE
    temp=root;
    plyta *help = new plyta;
    while(temp->next) {
        if(temp->stan==0) {
            wys_zalania=(tail->wysokosc)+1;
            flaga_zalewania=true;
            *root2=temp;
            temp2=temp;
            temp->wyszukaj_graf(wsk_wys_zalania,wsk_flaga,temp2,temp,root2);
            root2->zalewanie(wsk_wys_zalania,wsk_woda,wsk_flaga);
        }
        temp=temp->next;
    }

/// WYPISANIE WYNIKU
    cout << woda << endl;
    for(int i=0;i<h;i++) {
        for(int j=0;j<w;j++)
            if(plansza[w*i+j]->kaluza)
                cout << '#';
            else cout << '.';
        cout << endl;
    }

/// CZYSZCZENIE PAMIECI
    for(int i=0;i<ilosc;i++){
        delete plansza[i];
    }
    delete help;
//    delete *plansza;

    return 0;
}
