#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

#define NMAX 200001
#define INF (1L << 62)


class Rez {
 public:
    void solve() {
        ofstream fout("fortificatii.out");
        init0();
        read_input();
        fout << rezolvare();
    }

 private:
    vector<long int> d;
    vector<int> p;
    long int n, m, b, k;
    vector<int> barbarians;
    bool is_barb[NMAX];
    vector<pair<long int, long int>> adj[NMAX];
    /*  Se citeste inputul intr-un graf, daca exista o muchie intre 
        2 localitati controlate de barbari aceasta este ignorata*/
    void read_input() {
        ifstream fin("fortificatii.in");
        fin >> n >> m >> k;
        fin >> b;
        for (int i = 0, bi; i < b; i++) {
            fin >> bi;
            barbarians.push_back(bi);
            is_barb[bi] = true;
        }
        for (int i = 1, x, y, w; i <= m; i++) {
            fin >> x >> y >> w;
            if (is_barb[x] && is_barb[y])
                continue;
            adj[x].push_back(pair<long int, long int>(y, w));
            adj[y].push_back(pair<long int, long int>(x, w));
        }
        fin.close();
    }
    void init0() {
        for (int i = 0 ; i <= 200000 ; i++)
            is_barb[i] = false;
    }
    void init() {
        for (int i = 0 ; i <= n ; i++) {
            d.push_back(INF);
            p.push_back(0);
        }
        d[1] = 0;
        p[1] = 0;
    }
    /*  Se afla costurile minime de la toate nodurile la sursa(capitala)
        aplicand algoritmul lui Djikstra    */
    void dijkstra() {
        init();
        set<pair<long int, long int>> pq;
        pq.insert({d[1], 1});

        while (!pq.empty()) {
            auto top = pq.begin();
            long int node = (*top).second;
            pq.erase(top);
            if (is_barb[node])
                continue;
            for (auto& parc : adj[node]) {
                if (d[node] + parc.second < d[parc.first]) {
                    pq.erase({d[parc.first], parc.first});

                    d[parc.first] = d[node] + parc.second;
                    p[parc.first] = node;

                    pq.insert({d[parc.first], parc.first});
                }
            }
        }

        for (int node = 1; node <= n; node++) {
            if (d[node] == INF) {
                d[node] = -1;
            }
        }
    }
    /*  Se pun toate costurile de la capitala la localitatile controlate
        de barbari intr-un vector(prin toate muchiile nodurilor barbare, nu
        numai cel mai scurt drum), se sorteaza vectorul si apoi se adauga
        succesiv de k ori 1 la cel mai mic cost din vector. Dupa k adunari 
        rezultatul final va fi cel mai mic element din vector */
    long int rezolvare() {
        dijkstra();
        vector<long int> costs;
        for (auto &barbar : barbarians) {
            for (auto &muchie : adj[barbar]) {
                if (d[muchie.first] >= 0)
                    costs.push_back(muchie.second + d[muchie.first]);
            }
        }
        long int moves = k;
        sort(costs.begin(), costs.end());
        long int costs_size = (long int)costs.size();
        int i;
        for (i = 0 ; i < costs_size - 1 ;  i++) {
            long int dif = costs[i+1] - costs[i];
            if (dif == 0)
                continue;
            if (dif * (i+1) < moves) {
                moves -= dif * (i+1);
            } else {
                return costs[i] + moves/(i+1);
            }
        }
        return costs[costs.size()-1] + moves/costs.size();
    }
};
int main() {
    Rez tas;
    tas.solve();
    return 0;
}
