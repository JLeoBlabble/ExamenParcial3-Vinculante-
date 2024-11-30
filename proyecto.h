#ifndef PROYECTO_H
#define PROYECTO_H

#include "tarea.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iostream>
#include <climits> // Include for INT_MAX

class Proyecto {
private:
    std::unordered_map<std::string, Tarea*> tareas;

public:
    void agregarTarea(Tarea* tarea) {
        tareas[tarea->id] = tarea;
    }

    bool calcularOrdenEjecucion(std::vector<Tarea*>& orden) {
        std::unordered_map<Tarea*, int> gradosEntrada;
        std::queue<Tarea*> cola;

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

    bool asignarTareas(std::vector<Tarea*>& orden, std::vector<std::vector<Tarea*>>& asignaciones, int numPersonas) {
        std::vector<int> tiempos(numPersonas, 0);
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