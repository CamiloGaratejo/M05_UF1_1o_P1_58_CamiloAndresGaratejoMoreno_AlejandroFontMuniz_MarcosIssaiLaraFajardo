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
void Inputs();
void Logica();
void LimpiarPantalla();

enum MAP_TILES { EMPTY = ' ', WALL = 219 };
enum USER_INPUTS { NONE, UP, DOWN, RIGHT, LEFT, QUIT };

// Caracteres para imprimir en consola
MAP_TILES ConsoleScreen[CONSOLE_HEIGHT][CONSOLE_WIDTH];

// Vriables
USER_INPUTS input = USER_INPUTS::NONE;
char personaje = 2;
int personaje_x = 10;
int personaje_y = 5;
bool run = true;

int main()
{
    RellenarMapa();
    while (run)
    {
        ImprimirPantalla();
        Inputs();
        Logica();
        LimpiarPantalla();
    }
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
    ConsoleScreen[12][0] = MAP_TILES::EMPTY;
    ConsoleScreen[12][CONSOLE_WIDTH - 1] = MAP_TILES::EMPTY;
    ConsoleScreen[13][0] = MAP_TILES::EMPTY;
    ConsoleScreen[13][CONSOLE_WIDTH - 1] = MAP_TILES::EMPTY;
    ConsoleScreen[14][0] = MAP_TILES::EMPTY;
    ConsoleScreen[14][CONSOLE_WIDTH - 1] = MAP_TILES::EMPTY;
    ConsoleScreen[15][0] = MAP_TILES::EMPTY;
    ConsoleScreen[15][CONSOLE_WIDTH - 1] = MAP_TILES::EMPTY;
    ConsoleScreen[16][0] = MAP_TILES::EMPTY;
    ConsoleScreen[16][CONSOLE_WIDTH - 1] = MAP_TILES::EMPTY;

    ConsoleScreen[0][56] = MAP_TILES::EMPTY;
    ConsoleScreen[CONSOLE_HEIGHT - 1][56] = MAP_TILES::EMPTY;
    ConsoleScreen[0][57] = MAP_TILES::EMPTY;
    ConsoleScreen[CONSOLE_HEIGHT - 1][57] = MAP_TILES::EMPTY;
    ConsoleScreen[0][58] = MAP_TILES::EMPTY;
    ConsoleScreen[CONSOLE_HEIGHT - 1][58] = MAP_TILES::EMPTY;
    ConsoleScreen[0][59] = MAP_TILES::EMPTY;
    ConsoleScreen[CONSOLE_HEIGHT - 1][59] = MAP_TILES::EMPTY;
    ConsoleScreen[0][60] = MAP_TILES::EMPTY;
    ConsoleScreen[CONSOLE_HEIGHT - 1][60] = MAP_TILES::EMPTY;
    ConsoleScreen[0][61] = MAP_TILES::EMPTY;
    ConsoleScreen[CONSOLE_HEIGHT - 1][61] = MAP_TILES::EMPTY;
    ConsoleScreen[0][62] = MAP_TILES::EMPTY;
    ConsoleScreen[CONSOLE_HEIGHT - 1][62] = MAP_TILES::EMPTY;
}

void Inputs()
{
    char _input = _getch();
    switch (_input)
    {
    case 'W':
    case 'w':
        input = USER_INPUTS::UP;
        break;
    case 'A':
    case 'a':
        input = USER_INPUTS::LEFT;
        break;
    case 'S':
    case 's':
        input = USER_INPUTS::DOWN;
        break;
    case 'D':
    case 'd':
        input = USER_INPUTS::RIGHT;
        break;
    case 'Q':
    case 'q':
        input = USER_INPUTS::QUIT;
        break;
    default:
        input = USER_INPUTS::NONE;
        break;
    }
}

void Logica()
{
    int personaje_y_new = personaje_y;
    int personaje_x_new = personaje_x;
    switch (input)
    {
    case UP:
        personaje_y_new--;
        break;
    case DOWN:
        personaje_y_new++;
        break;
    case RIGHT:
        personaje_x_new++;
        break;
    case LEFT:
        personaje_x_new--;
        break;
    case QUIT:
        run = false;
        break;
    default:
        break;
    }
    if (personaje_x_new < 0) {
        personaje_x_new = CONSOLE_WIDTH - 1;
    }
    personaje_x_new %= CONSOLE_WIDTH;
    if (personaje_y_new < 0) {
        personaje_y_new = CONSOLE_HEIGHT - 1;
    }
    personaje_y_new %= CONSOLE_HEIGHT;
    if (ConsoleScreen[personaje_y_new][personaje_x_new] == MAP_TILES::WALL)
    {
        personaje_y_new = personaje_y;
        personaje_x_new = personaje_x;
    }
    personaje_y = personaje_y_new;
    personaje_x = personaje_x_new;
}

void ImprimirPantalla()
{
    for (int i = 0; i < CONSOLE_HEIGHT; i++)
    {
        for (int j = 0; j < CONSOLE_WIDTH; j++)
        {
            if (personaje_x == j && personaje_y == i)
            {
                cout << personaje;
            }
            else
            {
                cout << (char)ConsoleScreen[i][j];
            }
        }
        cout << endl;
    }
}
void LimpiarPantalla() {
    COORD cursorPosition; cursorPosition.X = 0; cursorPosition.Y = 0; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}