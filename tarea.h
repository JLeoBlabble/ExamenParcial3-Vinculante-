#ifndef TAREA_H
#define TAREA_H
#include <string>
#include <vector>
using namespace std;

/* Primero creamos una clase que representa una tarea con su ID, descripción, duración y dependencias.
 * Seguimos con un constructor que inicializa la tarea con sus atributos, y
 * por último un metodo para agregar dependencias.
 */
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