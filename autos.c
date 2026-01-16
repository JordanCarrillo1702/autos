#include <stdio.h>
#include <string.h>
#include "autos.h"

 FILE *archivo;
int idRepetidoArchivo(int idNuevo) {
    FILE *f = fopen("vehiculos.txt", "r");

    if (f == NULL) {
        return 0; // no hay archivo → no hay IDs repetidos
    }

    int id, disponible;
    char tipo[20], marca[20], modelo[20];
    float precio;

    while (fscanf(f, "%d %s %s %s %f %d",
                  &id, tipo, marca, modelo, &precio, &disponible) == 6) {

        if (id == idNuevo) {
            fclose(f);
            return 1; // ID repetido
        }
    }

    fclose(f);
    return 0; // ID único
}


void guardarVehiculos(int cantidad) {
    archivo = fopen("vehiculos.txt", "a");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    int id;
    int disponible = 1;
    char tipo[20];
    char marca[20];
    char modelo[20];
    float precio;

    for (int i = 0; i < cantidad; i++) {

        /* VALIDAR ID UNICO */
        do {
            printf("\nID del vehiculo: ");
            scanf("%d", &id);
            getchar();

            if (idRepetidoArchivo(id)) {
                printf("Error: el ID ya existe. Ingrese otro.\n");
            }
        } while (idRepetidoArchivo(id));
        printf("Tipo (camioneta, auto): ");
        fgets(tipo, sizeof(tipo), stdin);
        tipo[strcspn(tipo, "\n")] = '\0';  

        printf("Marca: (ej: Chevrolet, kia, hyundai, honda) ");
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
    archivo = fopen("vehiculos.txt", "r");// permite hacer lectura en el archivo

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

    rewind(archivo);//coloca el puntero al inicio del archivo

    while (fscanf(archivo, "%d %s %s %s %f %d",&id, tipo, marca, modelo, &precio, &disponible) == 6) {

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
    archivo = fopen("vehiculos.txt", "r");// se abre el archivo en modo lectura

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
    getchar();
    printf("Ingrese tipo de vehiculo (ej: camioneta o auto): ");
    fgets(tipoBuscado, sizeof(tipoBuscado), stdin);
    tipoBuscado[strcspn(tipoBuscado, "\n")] = '\0';

    printf("Ingrese marca (ej: Chevrolet, kia, hyundai, honda): ");
    fgets(marcaBuscada, sizeof(marcaBuscada), stdin);
    marcaBuscada[strcspn(marcaBuscada, "\n")] = '\0';

    do {
        printf("Ingrese presupuesto maximo: ");
        scanf("%f", &presupuesto);

    if (presupuesto <= 0) {
        printf("Error: el presupuesto debe ser mayor a 0.\n");
    }
    } while (presupuesto <= 0);

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
    FILE *archivo = fopen("vehiculos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    FILE *ventas = fopen("ventas.txt", "a");

    if (!archivo || !temp || !ventas) {
        printf("Error al abrir archivos.\n");
        return;
    }

    int id, idBuscar, disponible;
    char tipo[20];
    char marca[20];
    char modelo[20];
    float precio;

    int numVenta;
    char nombreCliente[50];
    int encontrado = 0;
    
    printf("Numero de venta: ");
    scanf("%d", &numVenta);
    getchar();
    printf("Nombre del cliente: ");
    fgets(nombreCliente, sizeof(nombreCliente), stdin);
    nombreCliente[strcspn(nombreCliente, "\n")] = '\0';

    printf("ID del vehiculo a vender: ");
    scanf("%d", &idBuscar);

    while (fscanf(archivo, "%d %s %s %s %f %d",
                  &id, tipo, marca, modelo, &precio, &disponible) == 6) {

        if (id == idBuscar) {
            encontrado = 1;
            if (disponible == 1) {
                disponible = 0;

                fprintf(ventas, "%d %s %s %s %d %.2f\n",
                        numVenta, nombreCliente, marca, modelo, idBuscar, precio);

                printf("Venta realizada con exito.\n");
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

    remove("vehiculos.txt");
    rename("temp.txt", "vehiculos.txt");

    if (!encontrado) {
        printf("Vehiculo no encontrado.\n");
    }
}
