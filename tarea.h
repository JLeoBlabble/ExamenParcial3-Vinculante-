#ifndef TAREA_H
#define TAREA_H
#include <string>
#include <vector>
using namespace std;

class Tarea {
public:
    string id;
    string desc;
    int duracion;
    vector<Tarea*> dependencias;

    Tarea(string id, string desc, int duracion)
        : id(id), desc(desc), duracion(duracion) {}

    void agregarDependencia(Tarea* tarea) {
        dependencias.push_back(tarea);
    }
};

#endif // TAREA_H