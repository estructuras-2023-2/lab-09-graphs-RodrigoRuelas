#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <sstream>
#include <functional>

using namespace std;

struct Carretera {
    string id;
    string ciudad1;
    string ciudad2;
    int costo;

    Carretera(string id, string ciudad1, string ciudad2, int costo) : id(id), ciudad1(ciudad1), ciudad2(ciudad2), costo(costo) {}
};

struct CarreteraHash {
    size_t operator()(const Carretera& c) const {
        return hash<string>()(c.id);
    }
};

struct CarreteraEqual {
    bool operator()(const Carretera& a, const Carretera& b) const {
        return a.id == b.id;
    }
};


string reconstruye() {
    unordered_map<string, vector<Carretera>> grafo;
    unordered_set<string> todasLasCiudades;

    for (auto it = carreteras.begin(); it != carreteras.end(); ++it) {
        const auto& camino = *it;
        stringstream ss(camino);
        string id, ciudad1, ciudad2;
        ss >> id >> ciudad1 >> ciudad2;

        todasLasCiudades.insert(ciudad1);
        todasLasCiudades.insert(ciudad2);

        int costo = 0;
        if (ss.peek() == ' ') {
            ss >> costo;
            Carretera carretera(id, ciudad1, ciudad2, costo);
            grafo[ciudad1].push_back(carretera);
            grafo[ciudad2].push_back(carretera);
        } else {
            Carretera carretera(id, ciudad1, ciudad2, 0);
            grafo[ciudad1].push_back(carretera);
            grafo[ciudad2].push_back(carretera);
        }
    }


    unordered_set<string> ciudadesVisitadas;
    queue<string> cola;

    cola.push(*todasLasCiudades.begin());

    while (!cola.empty()) {
        string ciudad = cola.front();
        cola.pop();

        ciudadesVisitadas.insert(ciudad);

        for (const auto& carretera : grafo[ciudad]) {
            string siguienteCiudad = (carretera.ciudad1 == ciudad) ? carretera.ciudad2 : carretera.ciudad1;
            if (ciudadesVisitadas.find(siguienteCiudad) == ciudadesVisitadas.end()) {
                cola.push(siguienteCiudad);
            }
        }
    }


    if (ciudadesVisitadas.size() != todasLasCiudades.size()) {
        return "IMPOSIBLE";
    }

    unordered_set<string> carreterasDanadas;
    unordered_set<string> ciudadesConCarretera;

    for (auto it = carreteras.begin(); it != carreteras.end(); ++it) {
        const auto& camino = *it;
        stringstream ss(camino);
        string id, ciudad1, ciudad2;
        ss >> id >> ciudad1 >> ciudad2;

        int costo = 0;
        if (ss.peek() == ' ') {
        ss >> costo;
            if (costo > 0) {
                if (ciudadesConCarretera.find(ciudad1) == ciudadesConCarretera.end() &&
                    ciudadesConCarretera.find(ciudad2) == ciudadesConCarretera.end()) {
                    carreterasDanadas.insert(id);
                    ciudadesConCarretera.insert(ciudad1);
                    ciudadesConCarretera.insert(ciudad2);
                }
            }
        }
    }


    vector<string> resultado;
    for (const auto& carretera : carreterasDanadas) {
        resultado.push_back(carretera);
    }

    sort(resultado.begin(), resultado.end());

    stringstream ss;
    for (const auto& id : resultado) {
        ss << id << " ";
    }

    return ss.str();
}

int main()
{
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
