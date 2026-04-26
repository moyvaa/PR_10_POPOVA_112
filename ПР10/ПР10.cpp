#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <ctime>
#include <cstdio>

using namespace std;

const int MXC = 20;

struct Dt {
    int d, m, y;
};

struct Ch {
    char sn[50];
    char nm[50];
    char g;
    double h;
    Dt bd;
};

Ch defDB[MXC] = {
    {"Ivanov",   "Ivan",    'M', 145.0, {12, 3, 2015}},
    {"Petrova",  "Anna",    'F', 142.0, {5, 7, 2016}},
    {"Sidorov",  "Dmitry",  'M', 150.0, {20, 1, 2014}},
    {"Smirnova", "Elena",   'F', 138.0, {15, 9, 2017}},
    {"Kuznetsov","Alexey",  'M', 147.0, {3, 11, 2015}},
    {"Popova",   "Maria",   'F', 140.0, {25, 4, 2016}},
    {"Vasiliev", "Sergey",  'M', 152.0, {8, 6, 2014}},
    {"Sokolova", "Olga",    'F', 139.0, {10, 12, 2017}},
    {"Mikhailov","Andrey",  'M', 148.0, {1, 2, 2015}},
    {"Novikova", "Tatiana", 'F', 141.0, {18, 8, 2016}},
    {"Morozov",  "Nikita",  'M', 146.0, {22, 5, 2015}},
    {"Volina",   "Yulia",   'F', 137.0, {30, 10, 2017}},
    {"Lebedev",  "Maxim",   'M', 151.0, {7, 3, 2014}},
    {"Orlova",   "Polina",  'F', 143.0, {14, 7, 2016}},
    {"Zaitsev",  "Kirill",  'M', 149.0, {2, 1, 2015}},
    {"Belova",   "Alina",   'F', 136.0, {28, 9, 2017}},
    {"Gusev",    "Roman",   'M', 153.0, {11, 4, 2014}},
    {"Titova",   "Veronika",'F', 144.0, {19, 6, 2016}},
    {"Komarov",  "Artem",   'M', 147.5, {6, 11, 2015}},
    {"Frolova",  "Daria",   'F', 135.0, {23, 12, 2017}}
};

void ldDB(Ch s[], int& n) {
    for (int i = 0; i < MXC; ++i) {
        s[i] = defDB[i];
    }
    n = MXC;
}

void pCh(const Ch& c) {
    cout << left << setw(15) << c.sn
        << setw(10) << c.nm
        << setw(5) << c.g
        << setw(8) << c.h
        << c.bd.d << "."
        << c.bd.m << "."
        << c.bd.y << endl;
}

void pWr(const char* t, const Ch a[], int n) {
    cout << "\n--- " << t << " ---" << endl;
    if (n == 0) {
        cout << "Список пуст" << endl;
        return;
    }
    cout << left << setw(15) << "Фамилия"
        << setw(10) << "Имя"
        << setw(5) << "Пол"
        << setw(8) << "Рост"
        << "Дата Рождения" << endl;
    for (int i = 0; i < n; ++i) {
        pCh(a[i]);
    }
}

void updGen(const char* fn, Ch s[], int n) {
    ifstream fin(fn);
    if (!fin.is_open()) {
        cout << "Не удалось открыть файл " << fn << endl;
        return;
    }

    char sn[50];
    int cd;
    while (fin >> sn >> cd) {
        bool fnd = false;
        for (int i = 0; i < n; ++i) {
            if (strcmp(s[i].sn, sn) == 0) {
                s[i].g = (cd == 0) ? 'M' : 'F';
                fnd = true;
                break;
            }
        }
        if (!fnd) {
            cout << "Фамилия " << sn << " не найдена" << endl;
        }
    }
    fin.close();
    cout << "Обновление полов из файла " << fn << " выполнено" << endl;
}

void saveBin(const char* fn, const Ch s[], int n) {
    ofstream fout(fn, ios::binary | ios::out);
    if (!fout.is_open()) {
        cout << "Ошибка открытия бинарного файла для записи!" << endl;
        return;
    }
    fout.write((char*)&n, sizeof(n));
    fout.write((char*)s, sizeof(Ch) * n);
    fout.close();
    cout << "Данные сохранены в бинарный файл " << fn << endl;
}

bool loadBin(const char* fn, Ch s[], int& n) {
    ifstream fin(fn, ios::binary | ios::in);
    if (!fin.is_open()) {
        cout << "Бинарный файл " << fn << " не найден" << endl;
        return false;
    }
    int fc = 0;
    fin.read((char*)&fc, sizeof(fc));
    if (fc > MXC) {
        cout << "слишком много записей в файле" << endl;
        fin.close();
        return false;
    }
    fin.read((char*)s, sizeof(Ch) * fc);
    n = fc;
    fin.close();
    cout << "Данные загружены из бинарного файла " << fn << " (" << n << " записей)" << endl;
    return true;
}

void bSort(Ch s[], int n) {
    bool swp;
    for (int i = 0; i < n - 1; ++i) {
        swp = false;
        for (int j = 0; j < n - i - 1; ++j) {
            int cmp = strcmp(s[j].sn, s[j + 1].sn);
            bool nd = false;
            if (cmp > 0) nd = true;
            else if (cmp == 0 && strcmp(s[j].nm, s[j + 1].nm) > 0) nd = true;

            if (nd) {
                Ch tmp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = tmp;
                swp = true;
            }
        }
        if (!swp) break;
    }
}

void updSt(Ch s[], int n, const char* tgt) {
    for (int i = 0; i < n; ++i) {
        if (strcmp(s[i].sn, tgt) == 0) {
            cout << "Редактирование ученика: " << s[i].sn << endl;
            cout << "Введите новые данные (фамилия имя пол рост день месяц год): ";
            cin >> s[i].sn >> s[i].nm >> s[i].g
                >> s[i].h >> s[i].bd.d
                >> s[i].bd.m >> s[i].bd.y;
            cout << "Данные изменены" << endl;
            return;
        }
    }
    cout << "Ученик с фамилией " << tgt << " не найден" << endl;
}

int fGirls(const Ch src[], int sc, Ch dst[]) {
    int dc = 0;
    for (int i = 0; i < sc; ++i) {
        if (src[i].g == 'F') dst[dc++] = src[i];
    }
    return dc;
}

int top5Girls(const Ch g[], int gc, Ch t5[]) {
    int sel = 0;
    bool used[MXC] = { false };
    while (sel < 5 && sel < gc) {
        int mxi = -1;
        for (int i = 0; i < gc; ++i) {
            if (!used[i] && (mxi == -1 || g[i].h > g[mxi].h))
                mxi = i;
        }
        if (mxi != -1) {
            t5[sel++] = g[mxi];
            used[mxi] = true;
        }
    }
    return sel;
}

int fBDay(const Ch src[], int sc, Ch dst[], int curM) {
    int dc = 0;
    for (int i = 0; i < sc; ++i) {
        if (src[i].bd.m == curM)
            dst[dc++] = src[i];
    }
    return dc;
}

int main() {
    setlocale(LC_ALL, "rus");
    Ch s[MXC];
    int n = 0;

    if (!loadBin("children.bin", s, n)) {
        ldDB(s, n);
        cout << "Загружены встроенные данные (" << n << " записей)\n";
    }

    updGen("gender.txt", s, n);
    pWr("После обновления полов из текстового файла", s, n);

    saveBin("children.bin", s, n);

    double sumH = 0;
    int cntB = 0;
    for (int i = 0; i < n; ++i)
        if (s[i].g == 'M') {
            sumH += s[i].h;
            cntB++;
        }
    if (cntB > 0)
        cout << "\nСредний рост мальчиков: " << fixed << setprecision(1)
        << (sumH / cntB) << " см" << endl;

    Ch g[MXC];
    int gc = fGirls(s, n, g);
    Ch t5[5];
    int t5c = top5Girls(g, gc, t5);
    pWr("5 самых высоких девочек", t5, t5c);

    bSort(s, n);
    pWr("Все ученики (лексикографическая сортировка)", s, n);

    char sName[50];
    cout << "\nВведите фамилию для поиска: ";
    cin >> sName;
    bool f = false;
    for (int i = 0; i < n; ++i) {
        if (strcmp(s[i].sn, sName) == 0) {
            cout << "Найденный ученик:" << endl;
            pCh(s[i]);
            f = true;
            break;
        }
    }
    if (!f) cout << "Ученик не найден" << endl;

    cout << "\nВведите фамилию для редактирования (или 'нет'): ";
    cin >> sName;
    if (strcmp(sName, "нет") != 0) {
        updSt(s, n, sName);
    }

    time_t t = time(0);
    tm* now = localtime(&t);
    int curM = now->tm_mon + 1;
    Ch bKids[MXC];
    int bdc = fBDay(s, n, bKids, curM);
    char mTit[50];
    sprintf(mTit, "Именинники месяца %d", curM);
    pWr(mTit, bKids, bdc);

    saveBin("children.bin", s, n);

    return 0;
}