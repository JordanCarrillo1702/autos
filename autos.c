#include <stdio.h>
#include <string.h>
#include "autos.h"

 FILE *archivo;

void guardarVehiculos(int cantidad) {
    archivo = fopen("vehiculos.txt", "a");

    int id;
    int disponible = 1;
    char tipo[20];
    char marca[20];
    char modelo[20];
    float precio;

    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        printf("\nID del vehiculo: ");
        scanf("%d", &id);
        getchar();   

        printf("Tipo (camioneta, auto): ");
        fgets(tipo, sizeof(tipo), stdin);
        tipo[strcspn(tipo, "\n")] = '\0';  

        printf("Marca: ");
        fgets(marca, sizeof(marca), stdin);
        marca[strcspn(marca, "\n")] = '\0';

        printf("Modelo: ");
        fgets(modelo, sizeof(modelo), stdin);
        modelo[strcspn(modelo, "\n")] = '\0';

        do {
        printf("Precio: ");
        scanf("%f", &precio);

        if (precio <= 0) {
        printf("Error: el precio debe ser mayor que 0.\n");
        }
        } while (precio <= 0);

        fprintf(archivo, "%d %s %s %s %.2f %d\n",id, tipo, marca, modelo, precio, disponible);
    }

    fclose(archivo);
}

void mostrarVehiculos() {
    archivo = fopen("vehiculos.txt", "r");

    int id;
    char tipo[20];
    char marca[20];
    char modelo[20];
    float precio;
    int disponible;

    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }

    rewind(archivo);

    while (fscanf(archivo, "%d %s %s %s %f %d",
                   &id, tipo, marca, modelo, &precio, &disponible) == 6) {

        if (disponible == 1) {
            printf("\nID: %d\n", id);
            printf("Tipo: %s\n", tipo);
            printf("Marca: %s\n", marca);
            printf("Modelo: %s\n", modelo);
            printf("Precio: %.2f\n", precio);
            printf("Estado: Disponible\n");
        }
    }

    fclose(archivo);
}
void buscarVehiculoPreferencias() {
    archivo = fopen("vehiculos.txt", "r");

    int id;
    int disponible;
    char tipo[20];
    char marca[20];
    char modelo[20];
    float precio;

    char tipoBuscado[20];
    char marcaBuscada[20];
    float presupuesto;

    int encontrado = 0;

    if (archivo == NULL) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("Ingrese tipo de vehiculo (ej: camioneta): ");
    scanf("%s", tipoBuscado);

    printf("Ingrese marca (ej: Chevrolet): ");
    scanf("%s", marcaBuscada);

    printf("Ingrese presupuesto maximo: ");
    scanf("%f", &presupuesto);

    printf("\n--- VEHICULOS QUE CUMPLEN PREFERENCIAS ---\n");

    while (fscanf(archivo, "%d %s %s %s %f %d",&id, tipo, marca, modelo, &precio, &disponible) == 6) {

        if (disponible == 1 &&
            strcmp(tipo, tipoBuscado) == 0 &&
            strcmp(marca, marcaBuscada) == 0 &&
            precio <= presupuesto) {

            printf("ID: %d\n", id);
            printf("Marca: %s\n", marca);
            printf("Modelo: %s\n", modelo);
            printf("Precio: %.2f\n", precio);
            printf("---------------------------\n");

            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("No se encontraron vehiculos con esas preferencias.\n");
    }

    fclose(archivo);
}

void registrarVenta() {
    FILE *temp;
    FILE *ventas;
    FILE *clientes;

    int id, idBuscar;
    char tipo[20];
    char marca[20];
    char modelo[20];
    float precio;
    int disponible;

    int idVenta;
    int idCliente, edad;
    char nombreCliente[30];
    float presupuesto;

    int encontrado = 0;

    archivo = fopen("vehiculos.txt", "r");
    temp = fopen("temp.txt", "w");
    ventas = fopen("ventas.txt", "a");
    clientes = fopen("clientes.txt", "a");

    if (!archivo || !temp || !ventas || !clientes) {
        printf("Error al abrir archivos.\n");
        return;
    }

    //cliente
    printf("ID del cliente: ");
    scanf("%d", &idCliente);

    printf("Nombre del cliente: ");
    scanf("%s", nombreCliente);

    printf("Edad: ");
    scanf("%d", &edad);

    printf("Presupuesto: ");
    scanf("%f", &presupuesto);

    fprintf(clientes, "%d %s %d %.2f\n",
            idCliente, nombreCliente, edad, presupuesto);

    //venta
    printf("ID de la venta: ");
    scanf("%d", &idVenta);

    printf("ID del vehiculo a vender: ");
    scanf("%d", &idBuscar);

    while (fscanf(archivo, "%d %s %s %s %f %d",
                  &id, tipo, marca, modelo, &precio, &disponible) == 6) {

        if (id == idBuscar) {
            encontrado = 1;

            if (disponible == 1) {
                disponible = 0;
                fprintf(ventas, "%d %d %d\n",
                        idVenta, idBuscar, idCliente);
                printf("Venta realizada correctamente.\n");
            } else {
                printf("El vehiculo ya fue vendido.\n");
            }
        }

        fprintf(temp, "%d %s %s %s %.2f %d\n",
                id, tipo, marca, modelo, precio, disponible);
    }

    fclose(archivo);
    fclose(temp);
    fclose(ventas);
    fclose(clientes);

    remove("vehiculos.txt");
    rename("temp.txt", "vehiculos.txt");

    if (!encontrado) {
        printf("Vehiculo no encontrado.\n");
    }
}



    



