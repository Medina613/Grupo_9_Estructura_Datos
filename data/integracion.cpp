// LIBERAR LISTA DE PROCESOS

void liberarLista() {

    while(cabeza != NULL) {

        NodoProceso* aux = cabeza;
        cabeza = cabeza->siguiente;

        delete aux;
    }
}

// LIBERAR COLA CPU

void liberarCola() {

    while(frente != NULL) {

        NodoCola* aux = frente;
        frente = frente->siguiente;

        delete aux;
    }

    finCola = NULL;
}

// LIBERAR PILA DE MEMORIA

void liberarPila() {

    while(cima != NULL) {

        NodoPila* aux = cima;
        cima = cima->siguiente;

        delete aux;
    }
}

// MENU PRINCIPAL

void menuPrincipal() {

    int opcion;

    do {

        cout << "\n=====================================\n";
        cout << " SISTEMA DE GESTION DE PROCESOS\n";
        cout << "=====================================\n";

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
                cout << "\nSaliendo del sistema...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while(opcion != 0);
}

// FUNCION PRINCIPAL

int main() {

    menuPrincipal();

    liberarLista();
    liberarCola();
    liberarPila();

    cout << "\nMemoria liberada correctamente.\n";

    return 0;
}
