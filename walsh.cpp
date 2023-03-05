#include <iostream>
#include <fstream>
using namespace std;
// functie recurenta care gaseste recurent solutia. Se imparte
// tabebelul walsh in 4 cadrane si se verifica in care cadran
// se afla elementul de coordonate x, y . Se repeta pana se ajunge
// la dimensiunea 1 a tabelului. Se tine minte de cate ori elementul
// s-a aflat in cadranul 4(in negations) . Deoarece tabelele sunt construite
// sa aiba tabelul 4 negat . Daca la final negatile sunt numar par , s-au anulat
// intre ele deci rasunsul va fi 0, altfel va fi 1.
int recur(int x, int y, int negations, int index) {
    if (index == 1) {
        if (negations%2 == 0)
            return 0;
        else
            return 1;
    }
    int nnegations = negations, nx = x, ny = y;
    // se transforma x si y in pozitii din tabelul de dimensiune index/2
    if (x > index/2)
        nx = nx-index/2;
    if (y > index/2)
        ny = ny-index/2;
    // se verifica daca elementul e in cadranul 4
    if (y > index/2 && x > index/2)
        nnegations++;
    return recur(nx, ny, nnegations, index/2);
}
int main() {
    ofstream ofile("walsh.out");
    ifstream rfile("walsh.in");
    int n, k;
    rfile >> n >> k;
    // pentru fiecare pereche x y se gaseste valoarea
    // corespunzatoare din matrice apelandu-se functia
    // recur
    for (int i = 0; i < k; i++) {
        int x, y;
        rfile >> x >> y;
        ofile << recur(x, y, 0, n) << endl;
    }
}
