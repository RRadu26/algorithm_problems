#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
class rez{
 public:
    int n;
    // se creaza un vector de 26 de vectori care vor tine costurile
    // pentru fiecare litera a unui cuvant. Costul este diferenta dintre
    // numarul de litere curente(din vector) si numarul de alte litere
    vector<vector<int>> profits = vector<vector<int>>(26);
    // calculeaza concatenarile folosind metoda greedy, pentru a lua rezultatul
    // cel bun se alege cel mai mare rezultat.
    int max_concatenations() {
        int max_words = 0;
        for (int i = 0 ; i < 26 ; i++) {
            sort(profits[i].begin(), profits[i].end());
            int prof = 0;
            int max_words_local = 0;
            for (int j=n-1 ; j >= 0 ; j--) {
                prof+=profits[i][j];
                if (prof <= 0)
                    break;
                max_words_local++;
            }
            if (max_words_local > max_words)
                max_words = max_words_local;
        }
        if (max_words == 0)
            return -1;
        return max_words;
    }
    // functie care itereaza prin toate cuvintele din fisier si
    // calculeaza profitul pentru toate literele
    void calculate_profits() {
        ifstream rfile("statistics.in");
        rfile >> n;
        for (int i = 0 ; i < n ; i++) {
            string s;
            rfile >> s;
            word_profits(s);
        }
    }
    // functie care calculeaza profitul pentru toate literele si le adauga in
    // vectorul profits . Se creaza un vector care tine toate profiturile
    // cuvantului initializat cu toate valorile ca fiind lungimea cuvantului,
    // apoi se itereaza  prin toate caracterele cuvantului, se adauga 2 pentru
    // caracterul curent in vector la pozitia literei (0 pentru a, 1 pentru b,
    // ect.). La final se adauga oate profiturile in cei 26 de vectori ai lui
    // profits
    void word_profits(string &s){
        int k = s.length();
        vector<int> word_profits(26, -k);
        for (int i = 0 ; i < k ; i++) {
            word_profits[s[i]-97]+=2;
        }
        for (int i = 0 ; i < 26 ; i++)
            profits[i].push_back(word_profits[i]);
    }
};
int main() {
    rez r;
    r.calculate_profits();
    ofstream ofile("statistics.out");
    ofile  << r.max_concatenations();
}
