// ESTRUCTURA Y VARIABLE GLOBAL

struct NodoProceso {
    int id;
    string nombre;
    int prioridad;
    int memoria;
    string estado;

    NodoProceso* siguiente;
};

NodoProceso* cabeza = NULL;

// FUNCION AUXILIAR

NodoProceso* buscarPorID(int id) {

    NodoProceso* aux = cabeza;

    while(aux != NULL) {

        if(aux->id == id)
            return aux;

        aux = aux->siguiente;
    }

    return NULL;
}

// REGISTRAR PROCESO

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

// LISTAR PROCESOS

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

// BUSCAR PROCESO

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

// MODIFICAR PROCESO

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

// ELIMINAR PROCESO

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

// MENU DE PROCESOS

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
