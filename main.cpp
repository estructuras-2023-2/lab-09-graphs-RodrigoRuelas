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
    vector<Road> damagedRoads;
    UnionFind uf;
    set<string> cities;
    set<string> selectedRoads;

    for (const auto& roadStr : carreteras) {
        stringstream ss(roadStr);
        string id, city1, city2;
        ss >> id >> city1 >> city2;
        uf.makeSet(city1);
        uf.makeSet(city2);
        cities.insert(city1);
        cities.insert(city2);
    }

    for (const auto& roadStr : carreteras) {
        stringstream ss(roadStr);
        string id, city1, city2;
        int cost = 0;
        ss >> id >> city1 >> city2;
        if (!(ss >> cost)) {
            uf.unionSets(city1, city2);
        } else {
            damagedRoads.emplace_back(id, city1, city2, cost);
        }
    }

    sort(damagedRoads.begin(), damagedRoads.end(), [](const Road& a, const Road& b) {
        if (a.cost != b.cost) {
            return a.cost < b.cost;
        }
        return a.id < b.id;
    });

    for (const auto& road : damagedRoads) {
        if (uf.find(road.city1) != uf.find(road.city2)) {
            uf.unionSets(road.city1, road.city2);
            selectedRoads.insert(road.id);
        }
    }

    string root = uf.find(*cities.begin());
    for (const auto& city : cities) {
        if (uf.find(city) != root) {
            return "IMPOSIBLE";
        }
    }

    string result;
    for (const auto& id : selectedRoads) {
        result += id + " ";
    }

    return result.empty() ? "" : result.substr(0, result.length() - 1);
}

int main() {
    vector<vector<string>> entradas = {
        {"C1 Lima Trujillo 1", "C2 Tacna Trujillo", "C3 Tacna Arequipa"},
        {"T1 Tumbes Quito", "C1 Iquitos StMartin 1000"},
        {"N1 Bogota Bucaramanga"},
        {"C1 Callao Ica 1", "C2 Callao Puno 2", "S0 Puno Ica"}
    };

    for (const auto& entrada : entradas) {
        cout << "Resultado: " << reconstruye(entrada) << endl;
    }

    return 0;
}
