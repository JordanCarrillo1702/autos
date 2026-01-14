#include <stdio.h>
#include <string.h>
#include "autos.h"

int main() {
    int opcion;

    do {
        printf("\n--- CONCESIONARIA RUEDAS DE ORO ---\n");
        printf("1. Registrar vehiculo\n");
        printf("2. Mostrar vehiculos\n");
        printf("3. Buscar vehiculo por preferencias\n");
        printf("4. Registrar venta\n");
        printf("5. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                int cantidad;
                printf("Cuantos vehiculos desea ingresar: ");
                scanf("%d", &cantidad);
                guardarVehiculos(cantidad);
                break;
            }
            
            case 2: 
                mostrarVehiculos();
                break;
            case 3:
                buscarVehiculoPreferencias();
                break;
            case 4:
                registrarVenta();
                break;
            
        }
    } while (opcion != 5);

    return 0;
}