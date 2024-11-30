#ifndef PROYECTO_H
#define PROYECTO_H
#include "tarea.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iostream>
#include <climits> // Incluye para INT_MAX
using namespace std;

/* Hacemos una clase que representa un proyecto que gestiona múltiples tareas.
 * La primera parte, que está en privado, es un mapa que asocia el ID de una tarea con el objeto Tarea correspondiente.
 * Luego, tenemos métodos para agregar una tarea al proyecto,
 * para calcular el orden de ejecución de las tareas basado en sus dependencias, y
 * para asignar tareas a múltiples personas y verificar si se pueden completar en 100 minutos.
 */
class Proyecto {
private:
    unordered_map<string, Tarea*> tareas;

public:
    void agregarTarea(Tarea* tarea) {
        tareas[tarea->id] = tarea;
    }

    /* En este metodo para calcular el orden de ejecución de las tareas,
     * primero inicializamos un mapa para contar las dependencias de cada tarea
     * y una cola para procesar las tareas sin dependencias.
     * Después, incrementamos el grado de entrada de las tareas dependientes tras inicializarlo a 0.
     * Luego, agregamos a la cola las tareas que no tienen dependencias, procesamos las tareas en orden topológico
     * (para reducir el grado de entrada de las tareas dependientes y agregarlas a la cola si no tienen más dependencias),
     * y verificamos si se procesaron todas las tareas.
     */
    bool calcularOrdenEjecucion(vector<Tarea*>& orden) {
        unordered_map<Tarea*, int> gradosEntrada;
        queue<Tarea*> cola;

        for (auto& par : tareas) {
            gradosEntrada[par.second] = 0;
        }

        for (auto& par : tareas) {
            for (Tarea* dep : par.second->dependencias) {
                gradosEntrada[dep]++;
            }
        }

        for (auto& par : tareas) {
            if (gradosEntrada[par.second] == 0) {
                cola.push(par.second);
            }
        }

        while (!cola.empty()) {
            Tarea* tarea = cola.front();
            cola.pop();
            orden.push_back(tarea);

            for (Tarea* dep : tarea->dependencias) {
                gradosEntrada[dep]--;
                if (gradosEntrada[dep] == 0) {
                    cola.push(dep);
                }
            }
        }

        return orden.size() == tareas.size();
    }

    /* Metodo para asignar tareas a múltiples personas y verificar si se pueden completar en 100 minutos.
     * Primero inicializamos un vector para almacenar el tiempo total de tareas asignadas a cada persona
     * y lo ajustamos al número de personas.
     * Luego, asignamos cada tarea a la persona con el menor tiempo acumulado,
     * encontramos la persona con el menor tiempo acumulado, asignamos la tarea a la persona encontrada,
     * y actualizamos su tiempo acumulado.
     * Finalmente, verificamos si alguna persona tiene más de 100 minutos de tareas asignadas.
     */
    bool asignarTareas(vector<Tarea*>& orden, vector<vector<Tarea*>>& asignaciones, int numPersonas) {
        vector<int> tiempos(numPersonas, 0);
        asignaciones.resize(numPersonas);

        for (Tarea* tarea : orden) {
            int persona = -1;
            int tiempoMin = INT_MAX;

            for (int i = 0; i < numPersonas; ++i) {
                if (tiempos[i] < tiempoMin) {
                    tiempoMin = tiempos[i];
                    persona = i;
                }
            }

            if (persona != -1) {
                asignaciones[persona].push_back(tarea);
                tiempos[persona] += tarea->duracion;
            }
        }

        for (int i = 0; i < numPersonas; ++i) {
            if (tiempos[i] > 100) {
                return false;
            }
        }

        return true;
    }
};

#endif // PROYECTO_H