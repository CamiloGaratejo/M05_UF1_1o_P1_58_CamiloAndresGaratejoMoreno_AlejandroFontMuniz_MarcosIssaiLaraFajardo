#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>

// Bordes del mapa 
using namespace std;
#define CONSOLE_HEIGHT 29
#define CONSOLE_WIDTH 119

void RellenarMapa();
void ImprimirPantalla();

enum MAP_TILES { EMPTY = ' ', WALL = 219 };

// Caracteres para imprimir en consola
MAP_TILES ConsoleScreen[CONSOLE_HEIGHT][CONSOLE_WIDTH];

// Vriables
char personaje = 2;
int personaje_x = 10;
int personaje_y = 5;

int main()
{
    RellenarMapa();
    ImprimirPantalla();
}

void RellenarMapa()
{

    //Valores y posiciones que se dan para la fila y la columna 
    for (int i = 0; i < CONSOLE_HEIGHT; i++)
    {
        for (int j = 0; j < CONSOLE_WIDTH; j++)
        {
            if (i == 0 || i == CONSOLE_HEIGHT - 1 || j == 0 || j == CONSOLE_WIDTH - 1)
            {
                ConsoleScreen[i][j] = MAP_TILES::WALL;
            }
            else
            {
                ConsoleScreen[i][j] = MAP_TILES::EMPTY;
            }
        }
    }
}

