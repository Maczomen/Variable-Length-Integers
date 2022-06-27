#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

#define MAX_LICZBA 1000000000
#define ILE_CYFR_W_LICZBIE 9

int ktora_mniejsza_3(int* liczba1, int* liczba2, double ile_cyfr) {
    for (int i = (int)ceil(ile_cyfr / ILE_CYFR_W_LICZBIE) - 1; i >= 0; i--) {
        if (liczba1[i] < liczba2[i])
            return 1;
        else if (liczba1[i] > liczba2[i])
            return 2;

    }
    return 0;
}

int ktora_mniejsza_2(int numer, int min, int* liczba_ile_cyfr_znak, int** liczby) {
    if (liczba_ile_cyfr_znak[numer * 2] > liczba_ile_cyfr_znak[min * 2])
        return numer;
    else if (liczba_ile_cyfr_znak[numer * 2] < liczba_ile_cyfr_znak[min * 2])
        return min;
    else if (ktora_mniejsza_3(liczby[numer], liczby[min], liczba_ile_cyfr_znak[numer * 2]) == 1)
        return min;
    else if (ktora_mniejsza_3(liczby[numer], liczby[min], liczba_ile_cyfr_znak[numer * 2]) == 2)
        return numer;
    else return -1;
}

int ktora_mniejsza(int numer, int min, int* liczba_ile_cyfr_znak, int** liczby) {
    if (liczba_ile_cyfr_znak[min * 2 + 1] == -1) {
        if (liczba_ile_cyfr_znak[numer * 2 + 1] == -1)
            return ktora_mniejsza_2(numer, min, liczba_ile_cyfr_znak, liczby);
        else
            return min;

    }
    else {
        if (liczba_ile_cyfr_znak[numer * 2 + 1] == 1) {
            if (min == ktora_mniejsza_2(numer, min, liczba_ile_cyfr_znak, liczby))
                return numer;
            else
                return min;

        }
        else
            return numer;

    }
}

void obliczenia(int** liczby, int* liczba_ile_cyfr_znak, int wynik, int liczba1, int liczba2, char obliczenie) {
    int ilosc_wierszy[2];
    if (liczba_ile_cyfr_znak[liczba1 * 2] > liczba_ile_cyfr_znak[liczba2 * 2]) {
        ilosc_wierszy[0] = (int)ceil((double)liczba_ile_cyfr_znak[liczba1 * 2] / ILE_CYFR_W_LICZBIE) + 1;
        ilosc_wierszy[1] = (int)ceil((double)liczba_ile_cyfr_znak[liczba2 * 2] / ILE_CYFR_W_LICZBIE);
        liczba_ile_cyfr_znak[wynik * 2] = liczba_ile_cyfr_znak[liczba1 * 2];

    }
    else {
        ilosc_wierszy[0] = (int)ceil((double)liczba_ile_cyfr_znak[liczba2 * 2] / ILE_CYFR_W_LICZBIE) + 1;
        ilosc_wierszy[1] = (int)ceil((double)liczba_ile_cyfr_znak[liczba1 * 2] / ILE_CYFR_W_LICZBIE);
        liczba_ile_cyfr_znak[wynik * 2] = liczba_ile_cyfr_znak[liczba2 * 2];

    }

    int* liczba = new int[ilosc_wierszy[0]];
    for (int i = 0; i < ilosc_wierszy[0]; i++)
        liczba[i] = 0;

    if ((obliczenie == '+' && liczba_ile_cyfr_znak[liczba1 * 2 + 1] == liczba_ile_cyfr_znak[liczba2 * 2 + 1]) || (obliczenie == '-' && liczba_ile_cyfr_znak[liczba1 * 2 + 1] != liczba_ile_cyfr_znak[liczba2 * 2 + 1])) {
        if ((obliczenie == '+' && liczba_ile_cyfr_znak[liczba1 * 2 + 1] == 1) || (obliczenie == '-' && liczba_ile_cyfr_znak[liczba2 * 2 + 1] == -1))
            liczba_ile_cyfr_znak[wynik * 2 + 1] = 1;
        else
            liczba_ile_cyfr_znak[wynik * 2 + 1] = -1;

        for (int i = 0; i < ilosc_wierszy[1]; i++) {
            liczba[i] += liczby[liczba1][i] + liczby[liczba2][i];
            if (liczba[i] >= MAX_LICZBA) {
                liczba[i + 1] += 1;
                liczba[i] -= MAX_LICZBA;

            }

        }
        if (liczba_ile_cyfr_znak[liczba1 * 2] > liczba_ile_cyfr_znak[liczba2 * 2])
            for (int i = ilosc_wierszy[1]; i < ilosc_wierszy[0] - 1; i++)
                liczba[i] += liczby[liczba1][i];
        else
            for (int i = ilosc_wierszy[1]; i < ilosc_wierszy[0] - 1; i++)
                liczba[i] += liczby[liczba2][i];

    }
    else {
        int buffer;

        buffer = ktora_mniejsza_2(liczba1, liczba2, liczba_ile_cyfr_znak, liczby);
        if (buffer == liczba2) {
            liczba2 = liczba1;
            liczba1 = buffer;
            if (obliczenie == '-')
                liczba_ile_cyfr_znak[wynik * 2 + 1] = liczba_ile_cyfr_znak[liczba1 * 2 + 1] * -1;
            else
                liczba_ile_cyfr_znak[wynik * 2 + 1] = liczba_ile_cyfr_znak[liczba1 * 2 + 1];


        }
        else
            liczba_ile_cyfr_znak[wynik * 2 + 1] = liczba_ile_cyfr_znak[liczba1 * 2 + 1];

        if (buffer != -1) {
            for (int i = 0; i < ilosc_wierszy[1]; i++) {
                liczba[i] = liczba[i] + liczby[liczba1][i] - liczby[liczba2][i];
                if (liczba[i] < 0 && ilosc_wierszy[0] - 2 != i) {
                    liczba[i + 1] -= 1;
                    liczba[i] += MAX_LICZBA;

                }

            }
            for (int i = ilosc_wierszy[1]; i < ilosc_wierszy[0] - 1; i++)
                liczba[i] += liczby[liczba1][i];

        }
        else {
            delete[] liczba;
            liczba = new int[1];
            liczba[0] = 0;
            liczba_ile_cyfr_znak[wynik * 2 + 1] = 1;
            liczba_ile_cyfr_znak[wynik * 2] = 1;

        }

    }
    delete[] liczby[wynik];
    liczby[wynik] = liczba;
}

void wypisanie_liczby(int* liczba, int ile_cyfr, int znak) {
    if (znak == -1)
        cout << "-";
    int a = (int)ceil((double)ile_cyfr / ILE_CYFR_W_LICZBIE) - 1;
    int pomin = 0;
    for (int i = a; i > 0; i--) {
        if (liczba[i] == 0 && a != 0)
            pomin += 1;
        else {
            break;

        }

    }
    cout << liczba[a - pomin];
    for (int i = a - pomin - 1; i >= 0; i--) {
        for (int j = 1; j < 9; j++)
            if (liczba[i] < MAX_LICZBA / pow(10, j))
                cout << 0;
            else
                break;
        cout << liczba[i];

    }
    cout << endl;
}

int main()
{
    int ile_liczb;
    cin >> ile_liczb;
    int** liczby;
    liczby = new int* [ile_liczb];
    int* liczba_ile_cyfr_znak;
    liczba_ile_cyfr_znak = new int[ile_liczb * 2];
    char znak;
    int min = 0, max = 0;
    znak = getchar();
    for (int i = 0; i < ile_liczb; i++) {
        int ile_cyfr = 0;
        int miesjce_chwilowe = 7;
        int* tabela_chwilowa = new int[miesjce_chwilowe];
        for (int j = 0; j < miesjce_chwilowe; j++)
            tabela_chwilowa[j] = 0;
        liczba_ile_cyfr_znak[i * 2 + 1] = 1;
        while (znak = getchar()) {
            if (ile_cyfr >= ILE_CYFR_W_LICZBIE * miesjce_chwilowe) {
                miesjce_chwilowe *= 2;
                int* tab = new int[miesjce_chwilowe];
                for (int j = 0; j < miesjce_chwilowe / 2; j++)
                    tab[j] = tabela_chwilowa[j];
                for (int j = miesjce_chwilowe / 2; j < miesjce_chwilowe; j++)
                    tab[j] = 0;
                delete[] tabela_chwilowa;
                tabela_chwilowa = tab;


            }
            if (znak < 48 || znak > 57)
                if (znak == '-')
                    liczba_ile_cyfr_znak[i * 2 + 1] = -1;
                else
                    break;
            else {
                tabela_chwilowa[ile_cyfr / ILE_CYFR_W_LICZBIE] = tabela_chwilowa[ile_cyfr / ILE_CYFR_W_LICZBIE] * 10 + (znak - 48);
                ile_cyfr += 1;

            }

        }

        int ile_cyfr_9 = (int)ceil((double)ile_cyfr / ILE_CYFR_W_LICZBIE);
        liczby[i] = new int[ile_cyfr_9];
        int przesuniecie = (int)pow(10, ile_cyfr % ILE_CYFR_W_LICZBIE);
        for (int j = 0; j < ile_cyfr_9; j++) {
            if (j == ile_cyfr_9 - 1)
                liczby[i][j] = tabela_chwilowa[0];
            else {
                if (ile_cyfr % 9 == 0)
                    liczby[i][j] = tabela_chwilowa[ile_cyfr_9 - 1 - j];
                else {
                    liczby[i][j] = tabela_chwilowa[ile_cyfr_9 - 1 - j] + (tabela_chwilowa[ile_cyfr_9 - 2 - j] % (MAX_LICZBA / przesuniecie)) * przesuniecie;
                    tabela_chwilowa[ile_cyfr_9 - 2 - j] = tabela_chwilowa[ile_cyfr_9 - 2 - j] / (MAX_LICZBA / przesuniecie);

                }

            }

        }
        liczba_ile_cyfr_znak[i * 2] = ile_cyfr;
        min = ktora_mniejsza(i, min, liczba_ile_cyfr_znak, liczby);
        if (max == ktora_mniejsza(i, max, liczba_ile_cyfr_znak, liczby))
            max = i;
        delete[] tabela_chwilowa;

    }
    while (cin >> znak) {

        if (znak == 'm') {
            cin >> znak;
            if (znak == 'i') {
                cin >> znak;
                if (znak == 'n')
                    wypisanie_liczby(liczby[min], liczba_ile_cyfr_znak[min * 2], liczba_ile_cyfr_znak[min * 2 + 1]);

            }
            else if (znak == 'a') {
                cin >> znak;
                if (znak == 'x')
                    wypisanie_liczby(liczby[max], liczba_ile_cyfr_znak[max * 2], liczba_ile_cyfr_znak[max * 2 + 1]);

            }

        }
        else if (znak == '?')
            for (int i = 0; i < ile_liczb; i++)
                wypisanie_liczby(liczby[i], liczba_ile_cyfr_znak[i * 2], liczba_ile_cyfr_znak[i * 2 + 1]);
        else if (znak == 'q')
            return 0;
        else if (znak >= 48 && znak <= 57) {
            int a = (znak - 48), b, c;
            while (cin >> znak) {
                if (znak >= 48 && znak <= 57)
                    a = a * 10 + (znak - 48);
                else
                    break;

            }

            cin >> b;
            cin >> znak;
            cin >> c;
            obliczenia(liczby, liczba_ile_cyfr_znak, a, b, c, znak);
            if (a == min)
                for (int i = 0; i < ile_liczb; i++) {
                    min = ktora_mniejsza(i, min, liczba_ile_cyfr_znak, liczby);

                }
            if (a == max)
                for (int i = 0; i < ile_liczb; i++) {
                    if (max == ktora_mniejsza(i, max, liczba_ile_cyfr_znak, liczby))
                        max = i;

                }
            if (a != min && a != max) {
                min = ktora_mniejsza(a, min, liczba_ile_cyfr_znak, liczby);
                if (max == ktora_mniejsza(a, max, liczba_ile_cyfr_znak, liczby))
                    max = a;

            }

        }

    }
    return 0;
}