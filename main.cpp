#include "proyecto.h"
#include <iostream>

int main() {
    Proyecto proyecto;

    // Creación de las tareas con sus ID, descripciones y duraciones
    Tarea* A = new Tarea("A", "Reserva de vuelo", 20);
    Tarea* B = new Tarea("B", "Informar a casa para empacar", 5);
    Tarea* C = new Tarea("C", "Empacar maletas", 40);
    Tarea* D = new Tarea("D", "Preparación del billete por la agencia", 10);
    Tarea* E = new Tarea("E", "Recoger el billete de la agencia", 5);
    Tarea* F = new Tarea("F", "Llevar el billete a la oficina", 10);
    Tarea* G = new Tarea("G", "Recoger las maletas de casa", 20);
    Tarea* H = new Tarea("H", "Llevar maletas a la oficina", 25);
    Tarea* I = new Tarea("I", "Conversación sobre documentos requeridos", 35);
    Tarea* J = new Tarea("J", "Dictar instrucciones para ausencia", 25);
    Tarea* K = new Tarea("K", "Reunir documentos", 15);
    Tarea* L = new Tarea("L", "Organizar documentos", 5);
    Tarea* M = new Tarea("M", "Viajar al aeropuerto y facturar", 25);

    // Agregar dependencias entre las tareas
    E->agregarDependencia(D);
    F->agregarDependencia(E);
    G->agregarDependencia(B);
    H->agregarDependencia(G);
    K->agregarDependencia(I);
    M->agregarDependencia(K);

    // Agregar las tareas al proyecto
    proyecto.agregarTarea(A);
    proyecto.agregarTarea(B);
    proyecto.agregarTarea(C);
    proyecto.agregarTarea(D);
    proyecto.agregarTarea(E);
    proyecto.agregarTarea(F);
    proyecto.agregarTarea(G);
    proyecto.agregarTarea(H);
    proyecto.agregarTarea(I);
    proyecto.agregarTarea(J);
    proyecto.agregarTarea(K);
    proyecto.agregarTarea(L);
    proyecto.agregarTarea(M);

    /* Creamos un vector para almacenar el orden de ejecución de las tareas,
     * seguido de otro para almacenar las asignaciones de tareas a cada persona, y un int para el número de personas.
     * Luego, calculamos el orden de ejecución de las tareas, comprobando si supero los 100 minutos,
     * y asignamos tareas a las personas.
     * Por último, imprimimos las tareas asignadas a cada persona y si es posible completarlas en 100 minutos o menos.
     */
    vector<Tarea*> orden;
    if (proyecto.calcularOrdenEjecucion(orden)) {
        vector<vector<Tarea*>> asignaciones;
        int numPersonas = 3;

        if (proyecto.asignarTareas(orden, asignaciones, numPersonas)) {
            // Imprimir las tareas asignadas a cada persona
            for (int i = 0; i < numPersonas; ++i) {
                cout << "Persona " << i + 1 << ":\n";
                for (Tarea* tarea : asignaciones[i]) {
                    cout << "  " << tarea->id << ": " << tarea->desc << " (" << tarea->duracion << " min)\n";
                }
            }
            cout << "Es posible completar las tareas en 100 minutos o menos.\n";
        } else {
            cout << "No es posible completar las tareas en 100 minutos o menos con tres personas.\n";
        }
    } else {
        cout << "No se puede determinar un orden de ejecución válido debido a dependencias cíclicas.\n";
    }

    return 0;
}