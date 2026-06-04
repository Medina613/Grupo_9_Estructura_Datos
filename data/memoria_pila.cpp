// ESTRUCTURA Y VARIABLE GLOBAL

struct NodoPila {
    int idProceso;
    int memoria;

    NodoPila* siguiente;
};

NodoPila* cima = NULL;

// ASIGNAR MEMORIA

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

// LIBERAR MEMORIA

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

// VISUALIZAR MEMORIA

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

// MENU MEMORIA

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
