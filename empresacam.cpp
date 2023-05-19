#include <iostream>
#include <stdio.h>
#include <string.h>
#include "auxiliar.h"
#define MAX 100
using namespace std;

typedef struct
{
    int dia;
    int mes;
    int año;
} fecha;

typedef struct
{
    char idCamara[9];
    char modelo[30];
    char ubicacion[30];
    fecha fechaEntrada;
    fecha fechaSalida;
} camara;

camara cameras[MAX];
int lastReg = 0;

void addCamera(camara cam);
void showCamera(int pos);
int isCamera(char id[]);
void showCameras();
void startCamera(int pos);
camara getCamera(int pos);
void updateCamera(camara cam, int pos);
void deleteCamera(int pos);
int menu();
void start();
void saveCameras();
void readCameras();
int calcUltReg(FILE *archivo);

void addCamera(camara cam)
{
    cameras[lastReg] = cam;
    lastReg++;
}

void showCamera(int pos)
{
    cout << "ID: " << cameras[pos].idCamara << endl;
    cout << "MODELO: " << cameras[pos].modelo << endl;
    cout << "UBICACIÓN: " << cameras[pos].ubicacion << endl;
    cout << "FECHA DE ENTRADA: " << cameras[pos].fechaEntrada.dia << "/" << cameras[pos].fechaEntrada.mes << "/" << cameras[pos].fechaEntrada.año << endl;
    cout << "FECHA DE SALIDA: " << cameras[pos].fechaSalida.dia << "/" << cameras[pos].fechaSalida.mes << "/" << cameras[pos].fechaSalida.año << endl;
}

camara getCamera(int pos)
{
    return cameras[pos];
}

int isCamera(char id[])
{
    int posicion = 0;
    for (int i = 0; i < lastReg; i++)
    {
        if (strcmp(id, cameras[i].idCamara) == 0)
        {
            posicion = i;
            break;
        }
    }
    return posicion;
}

void showCameras()
{
    system("cls||clear");
    if (lastReg == 0)
    {
        cout << "No hay registros\n";
        return;
    }
    for (int i = 0; i < lastReg; i++)
    {
        cout << "=========================\n";
        showCamera(i);
    }
    cout << "Último registro...\n";
}

void updateCamera(camara cam, int pos)
{
    cameras[pos] = cam;
}

void deleteCamera(int pos)
{
    if (pos == lastReg)
    {
        cout << "No hay registro\n";
        return;
    }
    for (int i = pos; i < lastReg - 1; i++)
    {
        cameras[i] = cameras[i + 1];
    }
    lastReg--;
    startCamera(lastReg);
}

void startCamera(int pos)
{
    strcpy(cameras[pos].idCamara, "");
    strcpy(cameras[pos].modelo, "");
    strcpy(cameras[pos].ubicacion, "");
    cameras[pos].fechaEntrada.dia = 0;
    cameras[pos].fechaEntrada.mes = 0;
    cameras[pos].fechaEntrada.año = 0;
    cameras[pos].fechaSalida.dia = 0;
    cameras[pos].fechaSalida.mes = 0;
    cameras[pos].fechaSalida.año = 0;
}

int menu()
{
    int op;

   gotoxy(10, 5);
    cout << "EMPRESA CAMLINK\n";
   gotoxy(15, 6);
    cout << "Cantidad de registros: " << lastReg << endl;
   gotoxy(10, 9);
    cout << " 1. Agregar C%cmara\n" << char(64);
   gotoxy(10, 10);
    cout << " 2. Editar Cámara\n";
   gotoxy(10, 11);
    cout << " 3. Eliminar Cámara\n";
   gotoxy(10, 12);
    cout << " 4. Buscar Cámara\n";
   gotoxy(10, 13);
    cout << " 5. Mostrar todas las Cámaras\n";
   gotoxy(10, 14);
    cout << " 6. Salir\n";
   gotoxy(10, 15);
    cout << " Digite la opción: ";
   gotoxy(29, 15);
    cin >> op;
    return op;
}

void start()
{
    int op, pos, resp;
    char id[9];
    camara cam;
    readCameras();
    do
    {
        system("cls||clear");

        op = menu();
        switch (op)
        {
        case 1:
            system("cls || clear");
           gotoxy(10, 5);
            cout << "ID:";
           gotoxy(10, 6);
            cout << "MODELO: ";
           gotoxy(10, 7);
            cout << "UBICACIÓN: ";
           gotoxy(10, 8);
            cout << "FECHA DE ENTRADA dd/MM/yyyy: ";
           gotoxy(10, 9);
            cout << "FECHA DE SALIDA dd/MM/yyyy: ";
           gotoxy(14, 5);
            scanf(" %[^\n]", cam.idCamara);
           gotoxy(18, 6);
            scanf(" %[^\n]", cam.modelo);
           gotoxy(20, 7);
            scanf(" %[^\n]", cam.ubicacion);
           gotoxy(24, 8);
            scanf("%d/%d/%d", &cam.fechaEntrada.dia, &cam.fechaEntrada.mes, &cam.fechaEntrada.año);
           gotoxy(23, 9);
            scanf("%d/%d/%d", &cam.fechaSalida.dia, &cam.fechaSalida.mes, &cam.fechaSalida.año);
            addCamera(cam);
            system("pause");

            break;
        case 2:
            system("cls||clear");
            cout << "Escribe el ID a buscar: ";
            scanf(" %[^\n]", id);
            system("cls||clear");
            pos = isCamera(id);
            showCamera(pos);
            cout << "DATOS A EDITAR\n";
           gotoxy(50, 2);
            cout << "ID:";
           gotoxy(50, 3);
            cout << "MODELO: ";
           gotoxy(50, 4);
            cout << "UBICACIÓN: ";
           gotoxy(50, 5);
            cout << "FECHA DE ENTRADA dd/MM/yyyy: ";
           gotoxy(50, 6);
            cout << "FECHA DE SALIDA dd/MM/yyyy: ";
           gotoxy(54, 2);
            scanf(" %[^\n]", cam.idCamara);
           gotoxy(58, 3);
            scanf(" %[^\n]", cam.modelo);
           gotoxy(60, 4);
            scanf(" %[^\n]", cam.ubicacion);
           gotoxy(64, 5);
            scanf("%d/%d/%d", &cam.fechaEntrada.dia, &cam.fechaEntrada.mes, &cam.fechaEntrada.año);
           gotoxy(63, 6);
            scanf("%d/%d/%d", &cam.fechaSalida.dia, &cam.fechaSalida.mes, &cam.fechaSalida.año);
            updateCamera(cam, pos);
            cout << "Registro actualizado...\n";
            system("pause");
            break;
        case 3:
            system("cls||clear");
            if (lastReg == 0)
            {
                cout << "No hay nada que eliminar\n";
                break;
            }
            cout << "Escribe el ID de la cámara: ";
            cin >> id;
            pos = isCamera(id);
            cam = getCamera(pos);
            cout << "¿Realmente deseas eliminar la cámara: " << cam.modelo << "?\n";
            cout << "Escribe 1 para SI o 2 para NO: ";
            cin >> resp;
            if (resp == 1)
            {
                deleteCamera(pos);
                cout << "Registro Eliminado... \n";
            }
            else
            {
                cout << "Operación cancelada.... \n";
            }
            system("pause");
            break;
        case 4:
            system("cls||clear");
            cout << "Escribe el ID a buscar: ";
            scanf(" %[^\n]", id);
            pos = isCamera(id);
            showCamera(pos);
            system("pause");
            break;
        case 5:
            system("cls||clear");
            showCameras();
            system("pause");
            break;
        case 6:
            break;
        default:
            system("clear||cls");
            cout << "Opción inválida \n";
            system("pause");
            break;
        }
    } while (op != 6);
    saveCameras();
}

void saveCameras()
{
    FILE *registroCamara;
    registroCamara = fopen("camaras.bin", "wb");
    fwrite(cameras, sizeof(camara), lastReg, registroCamara);
    fclose(registroCamara);
}

void readCameras()
{
    FILE *registroCamara;
    registroCamara = fopen("camaras.bin", "rb");
    if (registroCamara == NULL)
    {
        return;
    }
    lastReg = calcUltReg(registroCamara);
    fread(cameras, sizeof(camara), MAX, registroCamara);
    fclose(registroCamara);
}

int calcUltReg(FILE *archivo)
{
    int tam_archivo, num_estudiantes;
    // Obtener el tamaño del archivo
    fseek(archivo, 0, SEEK_END);
    tam_archivo = ftell(archivo);
    rewind(archivo);

    // Calcular el número de alumnos
    num_estudiantes = tam_archivo / sizeof(camara);
    return num_estudiantes;
}