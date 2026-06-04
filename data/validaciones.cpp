// VALIDACIONES EN REGISTRO DE PROCESOS

if(id <= 0) {

    cout << "ID invalido.\n";
    return;
}

if(buscarPorID(id) != NULL) {

    cout << "Ya existe un proceso con ese ID.\n";
    return;
}

if(prioridad < 1 || prioridad > 10) {

    cout << "Prioridad invalida.\n";
    return;
}

if(memoria <= 0) {

    cout << "Memoria invalida.\n";
    return;
}

// VALIDACIONES EN BUSQUEDA

if(p == NULL) {

    cout << "Proceso no encontrado.\n";
    return;
}

// VALIDACIONES EN ELIMINACION

if(actual == NULL) {

    cout << "Proceso no encontrado.\n";
    return;
}

// VALIDACIONES EN COLA CPU

if(frente == NULL) {

    cout << "La cola esta vacia.\n";
    return;
}

if(proceso == NULL) {

    cout << "Proceso no encontrado.\n";
    return;
}

// VALIDACIONES EN MEMORIA

if(cima == NULL) {

    cout << "No hay bloques de memoria.\n";
    return;
}

if(proceso == NULL) {

    cout << "Proceso no encontrado.\n";
    return;
}

// VALIDACIONES EN REPORTES

if(totalHistorial == 0) {

    cout << "No existen procesos ejecutados.\n";
}
