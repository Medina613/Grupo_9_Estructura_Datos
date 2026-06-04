#include <iostream>
#include <string>

using namespace std;

// 1. ESTRUCTURAS

// Lista enlazada - Procesos
struct NodoProceso {
    int id;
    string nombre;
    int prioridad;
    int memoria;
    string estado;

    NodoProceso* siguiente;
};

// Cola FIFO - CPU
struct NodoCola {
    int id;
    string nombre;
    int prioridad;

    NodoCola* siguiente;
};

// Pila - Memoria
struct NodoPila {
    int idProceso;
    int memoria;

    NodoPila* siguiente;
};

// 2. VARIABLES GLOBALES

NodoProceso* cabeza = NULL;
NodoCola* frente = NULL;
NodoCola* finCola = NULL;
NodoPila* cima = NULL;

// Historial y reportes
string historial[100];
int totalHistorial = 0;

// 3. FUNCIONES AUXILIARES

NodoProceso* buscarPorID(int id) {

    NodoProceso* aux = cabeza;

    while(aux != NULL) {

        if(aux->id == id)
            return aux;

        aux = aux->siguiente;
    }

    return NULL;
}

// 4. MODULO GESTOR DE PROCESOS

void registrarProceso() {

    int id;
    string nombre;
    int prioridad;
    int memoria;

    cout << "\n===== REGISTRAR PROCESO =====\n";

    cout << "ID: ";
    cin >> id;

    if(id <= 0) {
        cout << "ID invalido.\n";
        return;
    }

    if(buscarPorID(id) != NULL) {
        cout << "Ya existe un proceso con ese ID.\n";
        return;
    }

    cout << "Nombre: ";
    cin >> nombre;

    cout << "Prioridad (1-10): ";
    cin >> prioridad;

    if(prioridad < 1 || prioridad > 10) {
        cout << "Prioridad invalida.\n";
        return;
    }

    cout << "Memoria (MB): ";
    cin >> memoria;

    if(memoria <= 0) {
        cout << "Memoria invalida.\n";
        return;
    }

    NodoProceso* nuevo = new NodoProceso;

    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->prioridad = prioridad;
    nuevo->memoria = memoria;
    nuevo->estado = "Listo";
    nuevo->siguiente = NULL;

    if(cabeza == NULL) {

        cabeza = nuevo;
    }
    else {

        NodoProceso* aux = cabeza;

        while(aux->siguiente != NULL) {
            aux = aux->siguiente;
        }

        aux->siguiente = nuevo;
    }

    cout << "Proceso registrado correctamente.\n";
}

void listarProcesos() {

    cout << "\n----- LISTA DE PROCESOS -----\n";

    if(cabeza == NULL) {

        cout << "No existen procesos.\n";
        return;
    }

    NodoProceso* aux = cabeza;

    while(aux != NULL) {

        cout << "\nID: " << aux->id;
        cout << "\nNombre: " << aux->nombre;
        cout << "\nPrioridad: " << aux->prioridad;
        cout << "\nMemoria: " << aux->memoria;
        cout << "\nEstado: " << aux->estado;
        cout << "\n---------------------\n";

        aux = aux->siguiente;
    }
}

void buscarProceso() {

    int opcion;

    cout << "\n1. Buscar por ID";
    cout << "\n2. Buscar por nombre";
    cout << "\nOpcion: ";

    cin >> opcion;

    if(opcion == 1) {

        int id;

        cout << "ID: ";
        cin >> id;

        NodoProceso* p = buscarPorID(id);

        if(p == NULL) {

            cout << "Proceso no encontrado.\n";
            return;
        }

        cout << "\nID: " << p->id;
        cout << "\nNombre: " << p->nombre;
        cout << "\nPrioridad: " << p->prioridad;
        cout << "\nMemoria: " << p->memoria;
        cout << "\nEstado: " << p->estado << endl;
    }
    else if(opcion == 2) {

        string nombre;

        cout << "Nombre: ";
        cin >> nombre;

        NodoProceso* aux = cabeza;
        bool encontrado = false;

        while(aux != NULL) {

            if(aux->nombre == nombre) {

                encontrado = true;

                cout << "\nID: " << aux->id;
                cout << "\nNombre: " << aux->nombre;
                cout << "\nPrioridad: " << aux->prioridad;
                cout << "\nMemoria: " << aux->memoria;
                cout << "\nEstado: " << aux->estado << endl;

                break;
            }

            aux = aux->siguiente;
        }

        if(!encontrado)
            cout << "Proceso no encontrado.\n";
    }
}

void modificarProceso() {

    int id;

    cout << "\nID del proceso: ";
    cin >> id;

    NodoProceso* p = buscarPorID(id);

    if(p == NULL) {

        cout << "Proceso no encontrado.\n";
        return;
    }

    cout << "Nueva prioridad: ";
    cin >> p->prioridad;

    cout << "Nueva memoria: ";
    cin >> p->memoria;

    cout << "Proceso actualizado.\n";
}

void eliminarProceso() {

    int id;

    cout << "\nID a eliminar: ";
    cin >> id;

    NodoProceso* actual = cabeza;
    NodoProceso* anterior = NULL;

    while(actual != NULL && actual->id != id) {

        anterior = actual;
        actual = actual->siguiente;
    }

    if(actual == NULL) {

        cout << "Proceso no encontrado.\n";
        return;
    }

    if(anterior == NULL)
        cabeza = actual->siguiente;
    else
        anterior->siguiente = actual->siguiente;

    delete actual;

    cout << "Proceso eliminado correctamente.\n";
}

// 5. MODULO PLANIFICADOR CPU (COLA FIFO)

void encolarProceso() {

    int id;

    cout << "\n---- ENCOLAR PROCESO -----\n";
    cout << "Ingrese ID del proceso: ";
    cin >> id;

    NodoProceso* proceso = buscarPorID(id);

    if(proceso == NULL) {

        cout << "Proceso no encontrado.\n";
        return;
    }

    NodoCola* nuevo = new NodoCola;

    nuevo->id = proceso->id;
    nuevo->nombre = proceso->nombre;
    nuevo->prioridad = proceso->prioridad;
    nuevo->siguiente = NULL;

    if(frente == NULL) {

        frente = nuevo;
        finCola = nuevo;
    }
    else {

        finCola->siguiente = nuevo;
        finCola = nuevo;
    }

    proceso->estado = "En espera";

    cout << "Proceso agregado a la cola CPU.\n";
}

void ejecutarProceso() {

    cout << "\n----- EJECUTAR PROCESO -----\n";

    if(frente == NULL) {

        cout << "La cola esta vacia.\n";
        return;
    }

    NodoCola* ejecutado = frente;

    cout << "Ejecutando proceso...\n";
    cout << "ID: " << ejecutado->id << endl;
    cout << "Nombre: " << ejecutado->nombre << endl;
    cout << "Prioridad: " << ejecutado->prioridad << endl;

    // Actualizar estado en la lista enlazada
    NodoProceso* proceso = buscarPorID(ejecutado->id);

    if(proceso != NULL) {

        proceso->estado = "Ejecutado";
    }

    // Guardar historial
    if(totalHistorial < 100) {

    historial[totalHistorial] =
        "Proceso " + ejecutado->nombre +
        " ejecutado";

    totalHistorial++;
	}

    frente = frente->siguiente;

    if(frente == NULL) {

        finCola = NULL;
    }

    delete ejecutado;

    cout << "Proceso ejecutado correctamente.\n";
}

void visualizarColaCPU() {

    cout << "\n----- COLA CPU -----\n";

    if(frente == NULL) {

        cout << "No hay procesos en espera.\n";
        return;
    }

    NodoCola* aux = frente;
    int posicion = 1;

    while(aux != NULL) {

        cout << "\nPosicion: " << posicion;
        cout << "\nID: " << aux->id;
        cout << "\nNombre: " << aux->nombre;
        cout << "\nPrioridad: " << aux->prioridad;
        cout << "\n---------------------\n";

        posicion++;
        aux = aux->siguiente;
    }
}

void mostrarHistorial() {

    cout << "\n===== HISTORIAL DE EJECUCION =====\n";

    if(totalHistorial == 0) {

        cout << "No existen procesos ejecutados.\n";
        return;
    }

    for(int i = 0; i < totalHistorial; i++) {

        cout << i + 1 << ". "
             << historial[i]
             << endl;
    }
}

// 6. MENU PLANIFICADOR CPU

void menuCPU() {

    int opcion;

    do {

        cout << "\n---------------------------\n";
        cout << " PLANIFICADOR DE CPU (FIFO)\n";
        cout << "------------------------------\n";

        cout << "1. Encolar proceso\n";
        cout << "2. Ejecutar proceso\n";
        cout << "3. Visualizar cola\n";
        cout << "4. Historial de ejecucion\n";
        cout << "0. Volver\n";

        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {

            case 1:
                encolarProceso();
                break;

            case 2:
                ejecutarProceso();
                break;

            case 3:
                visualizarColaCPU();
                break;

            case 4:
                mostrarHistorial();
                break;

            case 0:
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while(opcion != 0);
}

// 7. MODULO GESTOR DE MEMORIA (PILA)

void asignarMemoria() {

    int id;

    cout << "\n------ ASIGNAR MEMORIA ------\n";
    cout << "ID del proceso: ";
    cin >> id;

    NodoProceso* proceso = buscarPorID(id);

    if(proceso == NULL) {

        cout << "Proceso no encontrado.\n";
        return;
    }

    NodoPila* nuevo = new NodoPila;

    nuevo->idProceso = proceso->id;
    nuevo->memoria = proceso->memoria;

    nuevo->siguiente = cima;
    cima = nuevo;

    cout << "Memoria asignada correctamente.\n";
}

void liberarMemoria() {

    cout << "\n------ LIBERAR MEMORIA ------\n";

    if(cima == NULL) {

        cout << "No hay bloques de memoria.\n";
        return;
    }

    NodoPila* eliminar = cima;

    cout << "ID proceso: "
         << eliminar->idProceso
         << endl;

    cout << "Memoria liberada: "
         << eliminar->memoria
         << " MB\n";

    cima = cima->siguiente;

    delete eliminar;

    cout << "Bloque eliminado correctamente.\n";
}

void visualizarMemoria() {

    cout << "\n------ ESTADO DE MEMORIA ------\n";

    if(cima == NULL) {

        cout << "No existen bloques asignados.\n";
        return;
    }

    NodoPila* aux = cima;
    int pos = 1;

    while(aux != NULL) {

        cout << "\nPosicion: " << pos;
        cout << "\nID Proceso: " << aux->idProceso;
        cout << "\nMemoria: " << aux->memoria << " MB";
        cout << "\n-------------------\n";

        pos++;
        aux = aux->siguiente;
    }
}

// 8. REPORTES

void generarReporte() {

    cout << "\n-------------------------------\n";
    cout << "      REPORTE DEL SISTEMA\n";
    cout << "---------------------------------\n";

    int totalProcesos = 0;

    NodoProceso* aux = cabeza;

    while(aux != NULL) {

        totalProcesos++;
        aux = aux->siguiente;
    }

    cout << "Procesos registrados: "
         << totalProcesos << endl;

    cout << "Procesos ejecutados: "
         << totalHistorial << endl;

    cout << "\n----- HISTORIAL ----\n";

    for(int i = 0; i < totalHistorial; i++) {

        cout << historial[i] << endl;
    }
}

// 9. LIBERAR MEMORIA DINAMICA

void liberarLista() {

    while(cabeza != NULL) {

        NodoProceso* aux = cabeza;

        cabeza = cabeza->siguiente;

        delete aux;
    }
}

void liberarCola() {

    while(frente != NULL) {

        NodoCola* aux = frente;

        frente = frente->siguiente;

        delete aux;
    }
}

void liberarPila() {

    while(cima != NULL) {

        NodoPila* aux = cima;

        cima = cima->siguiente;

        delete aux;
    }
}

// 10. MENU GESTOR DE PROCESOS

void menuProcesos() {

    int opcion;

    do {

        cout << "\n-------------------------\n";
        cout << " GESTOR DE PROCESOS\n";
        cout << "---------------------------\n";

        cout << "1. Registrar proceso\n";
        cout << "2. Buscar proceso\n";
        cout << "3. Modificar proceso\n";
        cout << "4. Eliminar proceso\n";
        cout << "5. Listar procesos\n";
        cout << "0. Volver\n";

        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {

            case 1:
                registrarProceso();
                break;

            case 2:
                buscarProceso();
                break;

            case 3:
                modificarProceso();
                break;

            case 4:
                eliminarProceso();
                break;

            case 5:
                listarProcesos();
                break;

            case 0:
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while(opcion != 0);
}

// 11. MENU MEMORIA

void menuMemoria() {

    int opcion;

    do {

        cout << "\n------------------------\n";
        cout << " GESTOR DE MEMORIA\n";
        cout << "--------------------------\n";

        cout << "1. Asignar memoria\n";
        cout << "2. Liberar memoria\n";
        cout << "3. Visualizar memoria\n";
        cout << "0. Volver\n";

        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {

            case 1:
                asignarMemoria();
                break;

            case 2:
                liberarMemoria();
                break;

            case 3:
                visualizarMemoria();
                break;

            case 0:
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while(opcion != 0);
}

// 12. MENU PRINCIPAL

void menuPrincipal() {

    int opcion;

    do {

        cout << "\n--------------------------------------\n";
        cout << " SISTEMA DE GESTION DE PROCESOS\n";
        cout << "----------------------------------------\n";

        cout << "1. Gestor de Procesos\n";
        cout << "2. Planificador CPU\n";
        cout << "3. Gestor de Memoria\n";
        cout << "4. Reportes\n";
        cout << "0. Salir\n";

        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {

            case 1:
                menuProcesos();
                break;

            case 2:
                menuCPU();
                break;

            case 3:
                menuMemoria();
                break;

            case 4:
                generarReporte();
                break;

            case 0:
                cout << "\nCerrando sistema...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while(opcion != 0);
}

// 13. MAIN

int main() {

    menuPrincipal();

    liberarLista();
    liberarCola();
    liberarPila(); 

    cout << "\n Memoria liberada correctamente.\n";

    return 0;
}
