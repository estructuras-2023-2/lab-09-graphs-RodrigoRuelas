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
    Carretera(string id, string ciudad1, string ciudad2, int costo) : id(id), ciudad1(ciudad1), ciudad2(ciudad2),
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
    return NULL;
}

int main()
{
    cout<<"Hello World";

    return 0;
}
