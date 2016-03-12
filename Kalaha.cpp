//POP_2015_12_22_Projekt_1_Jakubowski_Aleksander_AIR_2_160347, napisano w Visual Studio 2015

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
using namespace std;


/*
funkcja otrzymuje ilosc kamieni w polu, które jest aktualnie rysowane przez funkcję rysuj_funkcję()
i dopisuje spację przed liczbą kamieni, jesli tak jest mniejsza od 10.
Pozwala to na wyświetlanie liczb w równych rzędach
*/
void s(short a)
{
    if (a<10)
    {
        cout<<" "<<a;
    }
    else cout<<a;
}



/*
Funkcja rysuje szkielet planszy i wypełnia ją liczbami kamieni w polach graczy i w bazie


Otrzymywane zmienne:
- mp[] - moje pola - tablica przechowująca ilość kamieni w sześciu polach użytkownika
- pp[] - pola przeciwnika - tablica przechowująca ilość kamieni w sześciu polach komputera
- km - kamienie moje - ilość kamieni w mojej bazie
- kp - kamienie przeciwnika - ilość kamieni w bazie komputera
*/
void rysuj_plansze(short mp[], short pp[], short km, short kp)
{
    cout<<endl<<"        +-----+-----+-----+-----+-----+-----+"<<endl;
    cout<<"        |     |     |     |     |     |     |"<<endl;
    cout<<"+-------+ "; s(pp[5]); cout<<"  | "; s(pp[4]); cout<<"  | "; s(pp[3]); cout<<"  | ";    s(pp[2]); cout<<"  | "; s(pp[1]); cout<<"  | "; s(pp[0]); cout<<"  +-------+"<<endl;
    cout<<"|       |     |     |     |     |     |     |       |"<<endl;
    cout<<"|  "; s(kp); cout<<"   +-----+-----+-----+-----+-----+-----+  "; s(km); cout<<"   |"<<endl;
    cout<<"|       |     |     |     |     |     |     |       |"<<endl;
    cout<<"+-------+ "; s(mp[0]); cout<<"  | "; s(mp[1]); cout<<"  | "; s(mp[2]); cout<<"  | ";    s(mp[3]); cout<<"  | "; s(mp[4]); cout<<"  | "; s(mp[5]); cout<<"  +-------+"<<endl;
    cout<<"        |     |     |     |     |     |     |"<<endl;
    cout<<"        +-----+-----+-----+-----+-----+-----+"<<endl;
    cout<<"           a     b     c     d     e     f"<<endl<<endl;
}



/*
Funkcja sprawdza, na podstawie ilości kamieni w polach, czy nastąpił koniec gry.
Gra kończy się w momencie, gdy wszystkie pola (poza bazą) dowolnego gracza są puste.
Funkcja zwraca 1, gdy stwierdzi istnienie warunków koniecznych do zakończenia gry;
w przeciwnym razie zwraca 0.


Otrzymywane zmienne:
- mp[] - moje pola - tablica przechowująca ilość kamieni w sześciu polach użytkownika
- pp[] - pola przeciwnika - tablica przechowująca ilość kamieni w sześciu polach komputera
*/
bool czy_koniec_gry(short mp[], short pp[])
{
    bool flag[2]={0,0}; //0 oznacza koniec gry

    for (short i=0; i<6; i++)  if (mp[i]) flag[0]=1;
    for (short i=0; i<6; i++)  if (pp[i]) flag[1]=1;

    if (flag[0]==0 || flag[1]==0) return 1;
    else return 0;
}



/*
Funkcja realizuje algorytmy wykorzystywane podczas ruchu komputera.

Decyzja o bieżącym ruchu komputera podejmowana jest następująco:
1) sprawdź, czy użytkownik może zbić ci jakieś kamienie i ile może ich zbić
2) sprawdź, czy możesz zbić użytkownikowi jakieś kamienie i ile możesz ich zbić
3) jeśli użytkownik może zbić ci więcej kamieni niż ty jemu, wybierz pole z tymi kamieniami w celu ochrony ich;
	w przeciwnym razie wybierz pole, dzięki któremu zbijesz kamienie przeciwnika
4) jeśli nie ma możliwości ochrony własnych kamieni ani zbicia kamieni przeciwnika, wybierz pole, dzięki któremu możesz wykonać ruch ponownie
5) jeśli żadne z powyższych warunków nie zaistniały, wybierz losowo pole, na którym jest co najmniej 1 kamień.

Moja implementacja powyższych algorytmów nie bierze pod uwagę sytuacji, w których kamieni jest na tyle dużo, że kilkukrotnie okrążają planszę podczas rozdawania ich.
Algorytmy te nie biorą pod uwagę również sytuacji, w której użytkownik wykona kilka ruchów pod rząd.
Znając to łatwo można komputer wykiwać zbijając mu kamienie podczas robienia drugiego ruchu pod rząd albo wyboru pola z taką ilością kamieni
która podczas rozdawania okrąży planszę i trafi na nasze puste pole (czyli drugi sposób zbicia kamieni komputera).


Otrzymywane zmienne:
- mp[] - moje pola - tablica przechowująca ilość kamieni w sześciu polach użytkownika
- pp[] - pola przeciwnika - tablica przechowująca ilość kamieni w sześciu polach komputera
- km - kamienie moje - ilość kamieni w mojej bazie
- kp - kamienie przeciwnika - ilość kamieni w bazie komputera
*/
short decyzja_komputera(short mp[], short pp[], short km, short kp)
{
    short wynik;
    short korzysc[2][2]={{0,0},{0,0}}; //[ktore pole wybrac][jaki bedzie zysk/ile kamieni sie uratuje]

    for (int i=0; i<6; i++) // funkcja obliczajaca ile kamieni uzytkownik moze zabrac komputerowi
    {
        if (mp[i]<6-i && mp[i]>0 && mp[i+mp[i]]==0) //sprawdzanie czy uzytkownik moze zbic kamienie komputera
        {
            korzysc[0][0]=5-i-mp[i]; //sprawdzanie ktore pole jest zagrozone zbiciem kamieni
            korzysc[0][1]=pp[5-i-mp[i]]; //sprawdzanie ile kamieni jest zagrozonych zbiciem
        }
    }


    for (int i=0; i<6; i++) //wybor ruchu tak, zeby zbic kamienie przeciwnika
    {
        if (pp[i]+i<6 && pp[i]>0 && pp[i+pp[i]]==0 && mp[5-i-pp[i]]>0)
        {
            if (mp[5-i-pp[i]]>korzysc[1][1])
            {
                korzysc[1][0]=i;
                korzysc[1][1]=mp[5-i-pp[i]];
            }
        }
    }

    //cout<<"korzysci z ratowania kamieni startujac z pola "<<korzysc[0][0]<<": "<<korzysc[0][1]<<endl;
    //cout<<"korzysci ze zbijania kamieni startujac z pola "<<korzysc[1][0]<<": "<<korzysc[1][1]<<endl;

    //decyzja: najlepiej zbic kamienie przeciwnika
    if (korzysc[1][1]>=korzysc[0][1] && korzysc[0][1]>0)
		return korzysc[1][0]; //lepiej zbic kamienie przeciwnika niz komputera
    if (korzysc[0][1]>0)
		return korzysc[0][0]; //a jesli kamienie komputera sa cenniejsze niz szansa na zbicie przeciwnika, ratujemy nasze kamienie



    for (int i=5; i>=0; i--) //wybor ruchu tak, zeby moc go od razu wykonac ponownie
    {
        if (pp[i]==6-i)
        {
            return i;
        }
    }

    do //skoro nie wybrano wczesniej zadnych korzystnych dla komputera ruchow, jakis trzeba bedzie wylosowac
    {
        wynik=rand()%6;
    } while (!pp[wynik]); //wylosuj to pole, które nie jest puste

    return wynik;
}


/*
Funkcja obsługuje zbijanie kamieni w przypadku, gdy ostatni z rozdawanych kamieni danego gracza wpadnie do jego pustego pola.
Funkcja wywoływana jest przez funkcję ruch_uzytkownika() przy rozdawaniu każdego kamienia.


Otrzymywane zmienne:
- mp[] - moje pola - tablica przechowująca ilość kamieni w sześciu polach użytkownika
- pp[] - pola przeciwnika - tablica przechowująca ilość kamieni w sześciu polach komputera
- km - kamienie moje - ilość kamieni w mojej bazie
- kp - kamienie przeciwnika - ilość kamieni w bazie komputera
- i - numer aktualnie rozdawanego kamienia
- zmienna - ilosc rozdawanych kamieni w bieżącym ruchu gracza
- ruch - numer pola wybranego przez gracza
- czy_ja - ma wartosc true, jesli aktualnie graczem jest uzytkownik
- czy_moje_kamienie - ma wartosc true, jesli aktualnie rozdawane sa moje kamienie (prawdopodobnie niepotrzebna, ale nie bede sie nad tym zastanawial, bo jutro kolokwium z techniki cyfrowej)
*/
void bonus(short mp[], short pp[], short &km, short &kp, short i, short zmienna, short ruch, bool czy_ja, bool czy_moje_kamienie)
{
    if (i==zmienna-1) //jeżeli mamy ostatni kamień
    {
        if ((czy_ja && czy_moje_kamienie && !(mp[ruch]-1)) || (!czy_ja && !czy_moje_kamienie && !(pp[ruch]-1)))
        {

            if (czy_ja)
            {
                if (pp[5-ruch])
                {
                    cout<<"BONUS! "<<endl;
                    cout<<"Komputer traci "<<pp[5-ruch]<<" kamien";
                    if (pp[5-ruch]<5 && pp[5-ruch]>1) cout<<"ie"; //komputer umie odmieniac to slowo
                    if (pp[5-ruch]>4) cout<<"i";
                    cout<<endl;
                    km+=pp[5-ruch];
                    pp[5-ruch]=0;
                }
            }
            else
            {
                if (mp[5-ruch])
                {
                    cout<<"BONUS! "<<endl;
                    cout<<"Uzytkownik traci "<<mp[5-ruch]<<" kamien";
                    if (mp[5-ruch]<5 && mp[5-ruch]>1) cout<<"ie"; //tu tez komputer odmienia "kamienie", bo jest bardzo madry
                    if (mp[5-ruch]>4) cout<<"i";
                    cout<<endl;
                    kp+=mp[5-ruch];
					mp[5-ruch]=0;
                }
            }
        }
    }
}

/*
Funkcja relizuje ruch dowolnego gracza (i komputera i użytkownika):
1) pyta o ruch lub wywołuje funkcję decyzja_komputera()
2) rozdaje w petli kamienie kazdorazowo wywolujac funkcje bonus() w celu sprawdzenia, czy kamienie któegoś z graczy nie zostaly zbite
3) wywoluje funkcje rysuj_plansze() w celu graficznego przedstawienia graczowi efektow jego ruchu

Funkcja zwraca wartość 1 jeśli użytkownik ma ponowny ruch (trafił ostatnim kamieniem do swojej bazy).


Otrzymywane zmienne:
- czy_ja - ma wartosc true, jesli aktualnie graczem jest uzytkownik
- ruch - numer pola wybranego przez gracza
- mp[] - moje pola - tablica przechowująca ilość kamieni w sześciu polach użytkownika
- pp[] - pola przeciwnika - tablica przechowująca ilość kamieni w sześciu polach komputera
- km - kamienie moje - ilość kamieni w mojej bazie
- kp - kamienie przeciwnika - ilość kamieni w bazie komputera
*/
bool ruch_uzytkownika(bool czy_ja, short mp[], short pp[], short &km, short &kp) //funkcja zwraca true, jeœli uzytkownik ma ponowny ruch
{
    char ruch_char;
	short ruch;
    if (czy_koniec_gry(mp, pp)) return 0;

    if (czy_ja)
    {
        cout<<"Twoj ruch: ";
        cin>>ruch_char;
        ruch=int(ruch_char-97);

        while (ruch<0 || ruch>5 || !mp[ruch])
        {
        if (ruch<0 || ruch>5) cout<<"Nie istnieje takie pole. Podaj inna wartosc."<<endl;
        else cout<<"Nie mozesz wybrac pustego pola. Poddaj inna wartosc."<<endl;
        cout<<"Twoj ruch: ";
        cin>>ruch_char;
        ruch=int(ruch_char-97);
        }
    }
    else
    {
        ruch=decyzja_komputera(mp, pp ,km, kp);
        ruch_char=ruch+97;
        cout<<"Ruch komputera."<<endl<<"Komputer wybral: "<<char(ruch_char)<<endl;
    }

    bool czy_moje_kamienie=czy_ja; //zmienna sprawdza czy aktualnie przeliczane sa moje kamienie

    short zmienna; //bufor kamieni
    if (czy_ja) //zabieranie kamieni z wybranego pola i wrzucanie ich do bufora
    {
        zmienna=mp[ruch];
        mp[ruch]=0;
    }
    else
    {
        zmienna=pp[ruch];
        pp[ruch]=0;
    }

    ruch++;


    for (short i=0; i<zmienna; i++)
    {

        if(ruch<=5) //kamien trafia do pola
        {
            if (czy_moje_kamienie) mp[ruch]++;
            else pp[ruch]++;
            bonus(mp, pp ,km, kp, i, zmienna, ruch, czy_ja, czy_moje_kamienie);
            ruch++;
        }
        else //kamien trafia do bazy
        {
            if (czy_moje_kamienie) km++;
            else kp++;
            czy_moje_kamienie=!czy_moje_kamienie;
            ruch=0;
        }
    }
    rysuj_plansze(mp, pp ,km, kp);

    if (ruch) return 0;
    else if ((czy_ja && !czy_moje_kamienie) || (!czy_ja && czy_moje_kamienie)) return 1; //gracz ma ponowny ruch
    else return 0; //gracz nie ma ponownego ruchu
}


/*
Funkcja zbiera pozostałe kamienie graczy z ich pól do ich baz i wyświetla wynik gry. Wywoływana jest jako ostatnia przed zakończeniem gry.


Otrzymywane zmienne:
- mp[] - moje pola - tablica przechowująca ilość kamieni w sześciu polach użytkownika
- pp[] - pola przeciwnika - tablica przechowująca ilość kamieni w sześciu polach komputera
- km - kamienie moje - ilość kamieni w mojej bazie
- kp - kamienie przeciwnika - ilość kamieni w bazie komputera
*/
void wyswietl_wynik(short mp[], short pp[], short km, short kp)
{
    /*
    for (int i=0; i<6; i++) //petla zbiera kamienie z pol gracza do jego bazy, bo gra sie zakonczyla
    {
        km+=mp[i];
        kp+=pp[i];
    }
    */

    cout<<endl<<"KONIEC GRY!"<<endl<<endl;
    if(km>kp) cout<<"Gratulacje, udalo Ci sie pokonac przeciwnika!"<<endl;
    else if(km==kp) cout<<"Gratulacje, udalo Ci sie nie przegrac!"<<endl;
    else cout<<"Niestety, przegrales. Moze nastepnym razem sie uda?"<<endl;
    cout<<"Wynik tej rundy: ";
    if(km>=kp) cout<<km<<":"<<kp<<endl;
    else cout<<kp<<":"<<km<<endl;
}

//============================================================================================================

int main()
{
    const short k=6; //k to początkowa_ilosc_kamieni
    short moje_pola[6]={k,k,k,k,k,k}; //ilość kamieni na każdym z sześciu pól użytkownika
    short pola_przeciwnika[6]={k,k,k,k,k,k}; //ilość kamieni na każdym z sześciu pól komputera
    short moja_baza=0; //ilość kamieni w bazie użytkownika
    short baza_przeciwnika=0; //ilość kamieni w bazie komputera

    srand (time(NULL)); // potrzebne do losowania decyzji komputera

    rysuj_plansze(moje_pola, pola_przeciwnika ,moja_baza, baza_przeciwnika);

    do
    {

        while (ruch_uzytkownika(1, moje_pola, pola_przeciwnika, moja_baza, baza_przeciwnika)) {} //ruch użytkownika
        while (ruch_uzytkownika(0, moje_pola, pola_przeciwnika, moja_baza, baza_przeciwnika)) {} //ruch komputera

    } while (!czy_koniec_gry(moje_pola, pola_przeciwnika));

    wyswietl_wynik(moje_pola, pola_przeciwnika, moja_baza, baza_przeciwnika);
    system("pause");
}
