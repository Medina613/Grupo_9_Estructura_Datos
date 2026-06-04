// ESTRUCTURA Y VARIABLES GLOBALES

struct NodoCola {
    int id;
    string nombre;
    int prioridad;

    NodoCola* siguiente;
};

NodoCola* frente = NULL;
NodoCola* finCola = NULL;

// HISTORIAL DE EJECUCIÓN

string historial[100];
int totalHistorial = 0;

// ENCOLAR PROCESO

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

// EJECUTAR PROCESO

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

    NodoProceso* proceso = buscarPorID(ejecutado->id);

    if(proceso != NULL) {

        proceso->estado = "Ejecutado";
    }

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

// VISUALIZAR COLA CPU

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

// MOSTRAR HISTORIAL

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

// MENU CPU

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
