#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

class UnionFind {
private:
    map<string, string> padre;
    map<string, int> rango;

public:
    void hacerConjunto(const string& s) {
        padre[s] = s;
        rango[s] = 0;
    }

    string encontrar(const string& s) {
        if (padre[s] != s)
            padre[s] = encontrar(padre[s]);
        return padre[s];
    }

    bool unirConjuntos(const string& a, const string& b) {
        string raizA = encontrar(a);
        string raizB = encontrar(b);

        if (raizA == raizB)
            return false;

        if (rango[raizA] < rango[raizB])
            padre[raizA] = raizB;
        else if (rango[raizA] > rango[raizB])
            padre[raizB] = raizA;
        else {
            padre[raizB] = raizA;
            rango[raizA]++;
        }

        return true;
    }
};

class Carretera {
public:
    string id;
    string ciudad1;
    string ciudad2;
    int costo;

    Carretera(string i, string c1, string c2, int co = 0) : id(i), ciudad1(c1), ciudad2(c2), costo(co) {}
};

string reconstruye(vector<string> carreteras) {
    vector<Carretera> carreterasDañadas;
    UnionFind uf;
    set<string> ciudades;
    set<string> carreterasSeleccionadas;

    for (const auto& carreteraStr : carreteras) {
        stringstream ss(carreteraStr);
        string id, ciudad1, ciudad2;
        ss >> id >> ciudad1 >> ciudad2;
        uf.hacerConjunto(ciudad1);
        uf.hacerConjunto(ciudad2);
        ciudades.insert(ciudad1);
        ciudades.insert(ciudad2);
    }

    for (const auto& carreteraStr : carreteras) {
        stringstream ss(carreteraStr);
        string id, ciudad1, ciudad2;
        int costo = 0;
        ss >> id >> ciudad1 >> ciudad2;
        if (!(ss >> costo)) {
            uf.unirConjuntos(ciudad1, ciudad2);
        } else {
            carreterasDañadas.emplace_back(id, ciudad1, ciudad2, costo);
        }
    }

    sort(carreterasDañadas.begin(), carreterasDañadas.end(), [](const Carretera& a, const Carretera& b) {
        if (a.costo != b.costo) {
            return a.costo < b.costo;
        }
        return a.id < b.id;
    });

    for (const auto& carretera : carreterasDañadas) {
        if (uf.encontrar(carretera.ciudad1) != uf.encontrar(carretera.ciudad2)) {
            uf.unirConjuntos(carretera.ciudad1, carretera.ciudad2);
            carreterasSeleccionadas.insert(carretera.id);
        }
    }

    string raiz = uf.encontrar(*ciudades.begin());
    for (const auto& ciudad : ciudades) {
        if (uf.encontrar(ciudad) != raiz) {
            return "IMPOSIBLE";
        }
    }

    string resultado;
    for (const auto& id : carreterasSeleccionadas) {
        resultado += id + " ";
    }

    return resultado.empty() ? "" : resultado.substr(0, resultado.length() - 1);
}
