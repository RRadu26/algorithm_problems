#include <bits/stdc++.h>
using namespace std;
#define DMAX 100001
#define LMAX 1001
class Rez{
 public:
    void solve() {
        ofstream fout("curatare.out");
        read_input();
        vector<vector<bool>> vs = visited_b;
        create_graf();
        vector<int> timp_fiecare(n_robots + 1, 0);
        vector<bool> spatiu_vizitat(n_spaces + 1, false);
        spatiu_vizitat[0] = true;
        vector<int> poz(n_robots + 1, 0);
        int m = DMAX;
        for (int i = 1; i<= n_robots ; i++)
            m = min(m, back(timp_fiecare, spatiu_vizitat, i, poz));
        fout << m;
    }

 private:
    class location {
     public:
        int l, c, d;
        location(int l, int c , int d) {
            this->l = l;
            this->c = c;
            this->d = d;
        }
    };
    int n_robots = 0;
    int n_spaces = 0;
    vector<pair<int, int>> robots_coordonates;
    vector<pair<int, int>> spaces_coordonates;
    int adj[5][9];
    vector<vector <bool>> visited_b;
    int n, m;
    void read_input() {
        visited_b.push_back(vector<bool>());
        ifstream fin("curatare.in");
        fin >> n >> m;
        for (int i = 1 ; i <= n ; i++) {
            visited_b.push_back(vector<bool>(m+1, false));
            for (int j = 1 ; j <= m ; j++) {
                char p;
                fin >> p;
                if (p == 'R') {
                    n_robots++;
                    robots_coordonates.push_back(pair<int, int>(i, j));
                } else if (p == 'S') {
                    n_spaces ++;
                    spaces_coordonates.push_back(pair<int, int>(i, j));
                } else if (p == 'X') {
                    visited_b[i][j] = true;
                }
            }
        }
    }
    /*  Functie care gaseste distanta dintre 2 puncte se dau coordonatele 
        punctului sursa si destinatie. Se viziteaza toate celulele libere 
        folosind BFS, cand se viziteaza celula cautata returneaza distanta 
        de la sursa */

    int distance(pair<int, int> c1, pair<int, int> c2) {
        location source(c1.first, c1.second, 0);
        vector<vector<bool>> visited = visited_b;
        queue<location> q;
        q.push(source);
        visited[c1.first][c1.second] = true;
        while (!q.empty()) {
            source = q.front();
            q.pop();
            if (source.l == c2.first && source.c == c2.second)
                return source.d;
            if (source.l >= 2 && !visited[source.l -1][source.c]) {
                q.push(location(source.l - 1, source.c, source.d + 1));
                visited[source.l - 1][source.c] = true;
            }
            if (source.l <= n - 1 && !visited[source.l + 1][source.c]) {
                q.push(location(source.l + 1, source.c, source.d + 1));
                visited[source.l + 1][source.c] = true;
            }
            if (source.c >= 2 && !visited[source.l][source.c - 1]) {
                q.push(location(source.l, source.c - 1, source.d + 1));
                visited[source.l][source.c - 1] = true;
            }
            if (source.l <= m - 1 && !visited[source.l][source.c + 1]) {
                q.push(location(source.l, source.c + 1, source.d + 1));
                visited[source.l][source.c + 1] = true;
            }
        }
        return -1;
    }
    /*  Se creaza un graf care are ca noduri locatia robotilor si a locurilor,
        de curatat. Se leaga muchii intre toate locurile de curatat cu toate
        celelalte locuri de curatat si roboti   */
    void create_graf() {
        for (int i = 0 ; i <= 4 ; i++)
            for (int j = 0 ; j <= 8 ; j++)
                adj[i][j] = 0;
        for (int i = 1 ; i <= n_robots ; i++) {
            for (int j = 1 ; j <= n_spaces ; j++)
                adj[j][i] = distance(robots_coordonates[i-1],
                                      spaces_coordonates[j-1]);
        }
        for (int i = 1 ; i <= n_spaces ; i++) {
            for (int j = i+1 ; j <= n_spaces ; j++) {
                adj[i][j+4] = distance(spaces_coordonates[i-1],
                                        spaces_coordonates[j-1]);
                adj[j][i+4] = distance(spaces_coordonates[i-1],
                                        spaces_coordonates[j-1]);
            }
        }
    }
    /*  Functie recursiva ce foloseste backtracking, gaseste timpul minim
        in care plecand din toti robotii(multiple noduri sursa in acelasi 
        timp) toate nodurile locurilor de curatat sunt vizitate */
    int back(vector<int> timp_fiecare,
              vector<bool>spatiu_vizitat, int r, vector<int> poz) {
        if (find(spatiu_vizitat.begin(),
            spatiu_vizitat.end(), false) == spatiu_vizitat.end()) {
            int m = -1;
            for (int i = 1; i <= n_robots ; i++) {
                m = max(m, timp_fiecare[i]);
            }
            return m;
        }
        int glmin = DMAX;
        for (int i = 1 ; i< spatiu_vizitat.size() ; i++) {
            if (!spatiu_vizitat[i]) {
                vector<int> n_timp_fiecare = timp_fiecare;
                vector<bool> n_spatiu_vizitat = spatiu_vizitat;
                vector<int> n_poz = poz;

                if (poz[r] == 0)
                    n_timp_fiecare[r] += adj[i][r];
                else
                    n_timp_fiecare[r] += adj[i][poz[r] + 4];
                n_spatiu_vizitat[i] = true;
                n_poz[r] = i;
                int m = DMAX;
                for (int i = 1; i <= n_robots ; i++)
                    m = min(m ,
                            back(n_timp_fiecare, n_spatiu_vizitat, i, n_poz));
                glmin = min(m, glmin);
            }
        }
        return glmin;
    }
};

int main() {
    Rez tas;
    tas.solve();
    return 0;
}
