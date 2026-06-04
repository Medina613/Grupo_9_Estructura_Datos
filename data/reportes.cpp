// VARIABLES GLOBALES PARA HISTORIAL

string historial[100];
int totalHistorial = 0;

// GENERAR REPORTE

void generarReporte() {

    cout << "\n=====================================\n";
    cout << "      REPORTE DEL SISTEMA\n";
    cout << "=====================================\n";

    int totalProcesos = 0;

    NodoProceso* aux = cabeza;

    while(aux != NULL) {

        totalProcesos++;
        aux = aux->siguiente;
    }

    cout << "\nProcesos registrados: "
         << totalProcesos << endl;

    cout << "Procesos ejecutados: "
         << totalHistorial << endl;

    cout << "\n===== HISTORIAL DE EJECUCION =====\n";

    if(totalHistorial == 0) {

        cout << "No existen procesos ejecutados.\n";
    }
    else {

        for(int i = 0; i < totalHistorial; i++) {

            cout << i + 1 << ". "
                 << historial[i]
                 << endl;
        }
    }

    cout << "\n=====================================\n";
}
