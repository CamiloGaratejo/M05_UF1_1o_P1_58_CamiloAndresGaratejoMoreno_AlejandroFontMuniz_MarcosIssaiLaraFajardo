#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>

// Bordes del mapa
using namespace std;
#define CONSOLE_HEIGHT 29
#define CONSOLE_WIDTH 119

// Declarando las funciones para saber donde estan en el codigo
void RellenarMapa();
void ImprimirPantalla();
void Inputs();
void Logica();
void LimpiarPantalla();
void ImprimirScore();
void GameOver();

// Declarando los enums
enum MAP_TILES { EMPTY = ' ', WALL = 219, PUNTO = 248};
enum USER_INPUTS { NONE, UP, DOWN, RIGHT, LEFT, QUIT };

// Caracteres para imprimir en consola
MAP_TILES ConsoleScreen[CONSOLE_HEIGHT][CONSOLE_WIDTH];

// Vriables generales
USER_INPUTS input = USER_INPUTS::NONE;
char personaje = 2;
int personaje_x = 10;
int personaje_y = 5;
int score;
int mapaPoints = 24;
bool run = true;

// El main es para ejecuatar el codigo y que representa el orden en el cual se ejecuta en un bucle
int main()
{
    RellenarMapa();
    while (run)
    {
        ImprimirPantalla();
        Inputs();
        Logica();
        ImprimirScore();
        GameOver();
        LimpiarPantalla();
    }
    char s;
    cin >> s;
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

    // Para poder poner los puntas en el mapa
    ConsoleScreen[12][0] = MAP_TILES::PUNTO;
    ConsoleScreen[12][CONSOLE_WIDTH - 1] = MAP_TILES::PUNTO;
    ConsoleScreen[13][0] = MAP_TILES::PUNTO;
    ConsoleScreen[13][CONSOLE_WIDTH - 1] = MAP_TILES::PUNTO;
    ConsoleScreen[14][0] = MAP_TILES::PUNTO;
    ConsoleScreen[14][CONSOLE_WIDTH - 1] = MAP_TILES::PUNTO;
    ConsoleScreen[15][0] = MAP_TILES::PUNTO;
    ConsoleScreen[15][CONSOLE_WIDTH - 1] = MAP_TILES::PUNTO;
    ConsoleScreen[16][0] = MAP_TILES::PUNTO;
    ConsoleScreen[16][CONSOLE_WIDTH - 1] = MAP_TILES::PUNTO;
    ConsoleScreen[0][56] = MAP_TILES::PUNTO;
    ConsoleScreen[CONSOLE_HEIGHT - 1][56] = MAP_TILES::PUNTO;
    ConsoleScreen[0][57] = MAP_TILES::PUNTO;
    ConsoleScreen[CONSOLE_HEIGHT - 1][57] = MAP_TILES::PUNTO;
    ConsoleScreen[0][58] = MAP_TILES::PUNTO;
    ConsoleScreen[CONSOLE_HEIGHT - 1][58] = MAP_TILES::PUNTO;
    ConsoleScreen[0][59] = MAP_TILES::PUNTO;
    ConsoleScreen[CONSOLE_HEIGHT - 1][59] = MAP_TILES::PUNTO;
    ConsoleScreen[0][60] = MAP_TILES::PUNTO;
    ConsoleScreen[CONSOLE_HEIGHT - 1][60] = MAP_TILES::PUNTO;
    ConsoleScreen[0][61] = MAP_TILES::PUNTO;
    ConsoleScreen[CONSOLE_HEIGHT - 1][61] = MAP_TILES::PUNTO;
    ConsoleScreen[0][62] = MAP_TILES::PUNTO;
    ConsoleScreen[CONSOLE_HEIGHT - 1][62] = MAP_TILES::PUNTO;
}

void Inputs()
{
    // Mediante un switch podemos espesificar que teclas son las que se usan para poder gestionar el juego 
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


/// <summary>
/// E la logica lo que hace es pillar los imputs del usuario y hace que el jugador se mueva en el entorno
/// con mayor fluides y va restando los puntos restantes del mapa y va sumando el score 
/// tambien mediante estos metodos de programacion hacemos que el jugador pueda hacer los traspasos
/// de lado a lado esto es mediante una condicional (IF) que gestiona la posision del personaje al traspasar los bordes  
/// </summary>
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
    if (ConsoleScreen[personaje_y_new][personaje_x_new] == MAP_TILES::PUNTO) {
        ConsoleScreen[personaje_y_new][personaje_x_new] = MAP_TILES::EMPTY;
        score++;
        mapaPoints--;
    }
    personaje_y = personaje_y_new;
    personaje_x = personaje_x_new;
}

void ImprimirPantalla()
{
    // Mediante un buble se pone el imprimir la pantalla y con ella se ve genera todo los elementos visibles
    for (int i = 0; i < CONSOLE_HEIGHT; i++)
    {
        for (int j = 0; j < CONSOLE_WIDTH; j++)
        {
            if (personaje_x == j && personaje_y == i)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x6);
                cout << personaje;
            }
            else
            {
                if (ConsoleScreen[i][j] == MAP_TILES::PUNTO)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else if (ConsoleScreen[i][j] == MAP_TILES::WALL) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
                }
                cout << (char)ConsoleScreen[i][j];
            }
        }
        cout << endl;
    }
}

// Sistema para poder limpiar la terminal y que no parpadee al meter los imputs
void LimpiarPantalla() {
    COORD cursorPosition; cursorPosition.X = 0; cursorPosition.Y = 0; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

// Sistema para imprimir en panatlla el score y los puntos restantes
void ImprimirScore() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "Score: " << score ;
    cout << "  Puntos Totales: " << mapaPoints << " ";
}

// Sistema para que cuando se acaben los puntos del mapa se cancele el buble de ejecutar y sale la pantalla de HAS GANADO 
void GameOver() {
    if (mapaPoints <= 0) {
        system("CLS");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << R"(
      :::    :::     :::      ::::::::          ::::::::      :::     ::::    :::     :::     :::::::::   ::::::::    
     :+:    :+:   :+: :+:   :+:    :+:        :+:    :+:   :+: :+:   :+:+:   :+:   :+: :+:   :+:    :+: :+:    :+:    
    +:+    +:+  +:+   +:+  +:+               +:+         +:+   +:+  :+:+:+  +:+  +:+   +:+  +:+    +:+ +:+    +:+     
   +#++:++#++ +#++:++#++: +#++:++#++        :#:        +#++:++#++: +#+ +:+ +#+ +#++:++#++: +#+    +:+ +#+    +:+      
  +#+    +#+ +#+     +#+        +#+        +#+   +#+# +#+     +#+ +#+  +#+#+# +#+     +#+ +#+    +#+ +#+    +#+       
 #+#    #+# #+#     #+# #+#    #+#        #+#    #+# #+#     #+# #+#   #+#+# #+#     #+# #+#    #+# #+#    #+#        
###    ### ###     ###  ########          ########  ###     ### ###    #### ###     ### #########   ########          

)";
        cout << "Pulsa q para cerrar";
        run = false;
    }
}