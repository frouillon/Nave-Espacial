#include <stdio.h>	//Permite caracteres especiales
#include <windows.h> //Se puede mandar a imprimir al cursor a una posicion
#include <conio.h>	//Facilidad para detectar si se presionan las teclas
#include <iostream>
#include <string>
using namespace std;

#define ARRIBA    72
#define IZQUIERDA 75
#define DERECHA   77
#define ABAJO     80
#define ENTER 13
//Menu
void menu();
float operacion(float);
void Cuadro(int x1,int y1,int x2,int y2);
void gotoxy(int x,int y);
int menu_principal(const char *titulo[], const char *opciones[], int num);
//Nos permite decidir donde comienza el cursor
void gotoxy(int x, int y) {
    HANDLE hCon;	
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);	//Recupera el identificador de la consola (tomamos control de la salida de la consola)
    COORD dwPos;	//Es una estructura
    dwPos.X = x;	//Posici�n en x
    dwPos.Y = y;	//Posici�n en y
    SetConsoleCursorPosition(hCon, dwPos);	//Funci�n de la librer�a windows (Par�metros)
}
//Ocultamos el cursor
void OcultarCursor() {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;		//Estructura (puede controlar el tama�o del cursor o si aparece)
    cursor.bVisible = FALSE; // controla si se ve el cursor o no 
    SetConsoleCursorInfo(hCon, &cursor);	//Funci�n de la biblioteca
}
//Hacemos los limites
void pintar_limites() {
    for (short i = 2; i < 78; i++) {
        gotoxy(i, 2); printf("%c",205);
        gotoxy(i, 23); printf("%c",205);
    }
    for (short i = 3; i < 23; i++) {
        gotoxy(2, i); printf("%c",186);
        gotoxy(77, i); printf("%c",186);
    }
}
//Hacemos la nave
class Nave
{
	int x,y;
	public:
	Nave(int a, int b);
	void pintar();
	void eliminar();
	int getX() { return x; }
    int getY() { return y; }
	void mover();
};
//Constructor de la clase Nave
Nave::Nave(int a, int b)
{
	x=a;
	y=b;
}
//Digitamos la nave
void Nave::pintar()
{
	gotoxy(x,y); printf("  %c",207);
	gotoxy(x,y+1); printf(" %c%c%c",40,207,41);
	gotoxy(x,y+2); printf("%c%c %c%c",174,190,190,175);
}
//Borramos la anterior nave digitada
void Nave::eliminar()
{
	gotoxy(x,y); printf("     ");
	gotoxy(x,y+1); printf("     ");
	gotoxy(x,y+2); printf("     ");
}
//Movimiento de la nave
void Nave::mover()
{
	if (kbhit()) //Comprueba en la consola si se ha presionado una tecla recientemente
	{
        char tecla = getch();
		eliminar();	//Se borra la posici�n anterior de la nave
        if (tecla == IZQUIERDA && x>3) x--;
        if (tecla == DERECHA && x+6<77) x++;
        if (tecla == ARRIBA && y>3) y--;
        if (tecla == ABAJO && y+3<23) y++;
        pintar();	//Se imprime la posici�n actual de la nave
    }
}
//Hacemos los asteroides
class AST {
private:
    int x, y;
public:
    AST(int a, int b); 
    void pintar();
    void mover();
    int getX() { return x; }
    int getY() { return y; }
    void reiniciar();
};
//Constructor de la clase asteroide
AST::AST(int a, int b)
{
	x=a;
	y=b;
}
//Digitamos los asteroides
void AST::pintar() {
    gotoxy(x, y);
    printf("%c",184);
}
//Movimiento del asteroide
void AST::mover() {
    gotoxy(x, y);
    printf("  ");
    y++;
    if (y > 22) {
        x = rand() % 71 + 3;
        y = 4;
    }
    pintar();
}

int main() {
	string nick[3];
	bool repetir= true;
	Cuadro(0,0,119,24);
	Cuadro(20,1,100,3);
	int option;
	const char *titulo[] = {"   ********      **     **           **       ********      **  ","  **//////**    ****   /**          ****     **//////**    **** ",
	" **      //    **//**  /**         **//**   **      //    **//**  ","/**           **  //** /**        **  //** /**           **  //** ","/**    ***** **********/**       **********/**    ***** **********",
	"//**  ////**/**//////**/**      /**//////**//**  ////**/**//////**"," //******** /**     /**/********/**     /** //******** /**     /**","  ////////  //      // //////// //      //   ////////  //      // "};
	const char *opciones[] = {"Comenzar","Salir"};
	int num=2;
	do{
		option=menu_principal(titulo, opciones, num);
		switch(option){
			case 1:{
				system("cls");
				OcultarCursor();
			    pintar_limites();	//Llamamos a la funcion que se encarga de digitar los limites
			    Nave n(30,15);		//Se imprime la primera posici�n de la nave
			    n.pintar();		//Llamamos a la funcion que se encarga de digitar la nave
			    AST ast(10, 5);
			    bool game_over = false;
			    int puntaje = 0;
			
			    while (game_over==false){
			        ast.mover();
			        n.mover();
			        puntaje += 1;
			        //ast.reiniciar();
			        
					// Imprimir puntaje en cada iteraci�n
					gotoxy(1, 1);
					printf("Puntaje: %d", puntaje);
					Sleep(30);	//Menos iteraciones por segundo

					if (n.getX() + 4 >= ast.getX() && n.getX() <= ast.getX() && n.getY() <= ast.getY() + 0 && n.getY() + 3 >= ast.getY()) {
        				game_over = true; // Colisión detectada, el juego termina
   					 }
    			}
				system("CLS");
				gotoxy(30,10);
				printf("Puntaje: %d", puntaje);
				gotoxy(30,12);
				printf("Ingrese su nickname: ");
				scanf("%s",nick);
				printf("\n");

				system("pause");
				break;
			}
			case 2:
				repetir=false;
				break;
			
		}
	}while(repetir);
    

    return 0;
}
int menu_principal(const char *titulo[], const char *opciones[], int num){
	int seleccion = 1;
	int tecla;
	bool repite=true;
	do{
		system("cls");
		for(int a=0;a<8;a++){
			gotoxy(21,2+a);cout<<titulo[a];
		}
		gotoxy(8,11 + 2 * seleccion); cout<<"==>";
		for(int i=0;i<num;i++){
			gotoxy(16,13+2*i);cout<<opciones[i];
		}
		
		do{
		tecla=getch();	
		}while(tecla!=ARRIBA && tecla!=ABAJO && tecla!=ENTER);
		
		switch(tecla){
			case ARRIBA:
				seleccion--;
				if(seleccion==0){
					seleccion=num;
				}
				break;
			case ABAJO:
				seleccion++;
				if(seleccion>num){
					seleccion=1;
				}
				break;
			case ENTER:
				repite=false;
				break;
		}
	}while(repite);
	return seleccion;
}

void Cuadro(int x1,int y1,int x2,int y2){
	int i;

    for (i=x1;i<x2;i++){
		gotoxy(i,y1); printf("\304"); //linea horizontal superior
		gotoxy(i,y2); printf("\304"); //linea horizontal inferior
    }

    for (i=y1;i<y2;i++){
		gotoxy(x1,i); printf("\263"); //linea vertical izquierda
		gotoxy(x2,i); printf("\263"); //linea vertical derecha
	}

    gotoxy(x1,y1); printf("\332");
    gotoxy(x1,y2); printf("\300");
    gotoxy(x2,y1); printf("\277");
    gotoxy(x2,y2); printf("\331");
}

