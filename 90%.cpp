#include <stdio.h>	//Permite caracteres especiales
#include <windows.h> //Se puede mandar a imprimir al cursor a una posicion
#include <conio.h>	//Facilidad para detectar si se presionan las teclas
#include <iostream>
#include <fstream> //Para el manejo de archivos
#include <string>

using namespace std;

#define ARRIBA    72
#define IZQUIERDA 75
#define DERECHA   77
#define ABAJO     80
#define ENTER 13
//Menu
void Cuadro(int x1,int y1,int x2,int y2);
int menu_principal(const char *titulo[], const char *opciones[], int num);
//Nos permite decidir donde comienza el cursor
void gotoxy(int x, int y) {
    HANDLE hCon;	
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);	//Recupera el identificador de la consola (tomamos control de la salida de la consola)
    COORD dwPos;	//Es una estructura
    dwPos.X = x;	//Posicion en x
    dwPos.Y = y;	//Posicion en y
    SetConsoleCursorPosition(hCon, dwPos);	//Funcion de la libreria windows (Parametros)
}
//Ocultamos el cursor
void OcultarCursor() {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;		//Estructura (puede controlar el tamano del cursor o si aparece)
    cursor.bVisible = FALSE; // controla si se ve el cursor o no 
    SetConsoleCursorInfo(hCon, &cursor);	//Funcion de la biblioteca
}
//Cambio de color
void CambioColor()
{
	HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, FOREGROUND_GREEN); // El color del texto se convierte en verde
}
//Volver al color normal
void RestauraColor()
{
	HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN); // Restaura el color original del texto
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
	int corazones;
	int tiempo;
	public:
	Nave(int a, int b, int _corazones, int _tiempo);
	void menos_corazones(){corazones--;}
	void mas_corazones(){corazones++;}
	void pintar();
	int vidas(){ return corazones;}
	void eliminar();
	int getX() { return x; }
    int getY() { return y; }
	void mover();
	void muerte();
	void digitar_corazones();
	int time(){ return tiempo;}
	void in_time(){tiempo++;}
};
//Constructor de la clase Nave
Nave::Nave(int a, int b, int _corazones, int _tiempo)
{
	x=a;
	y=b;
	corazones=_corazones;
	tiempo=_tiempo;
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
		eliminar();	//Se borra la posion anterior de la nave
        if (tecla == IZQUIERDA && x>3) x--;
        if (tecla == DERECHA && x+6<77) x++;
        if (tecla == ARRIBA && y>3) y--;
        if (tecla == ABAJO && y+3<23) y++;
        pintar();	//Se imprime la posicion actual de la nave
        
    }
}
//Digitar corazones
void Nave::digitar_corazones()
{
	gotoxy(66,1); printf("Salud");
	gotoxy(72,1); printf("      ");
	for(short i=0;i<corazones;i++)
	{
		gotoxy(72+i,1); printf("%c",157);
	}
}
//Muerte de la nave
void Nave::muerte()
{
	eliminar();
	gotoxy(x,y); printf("   **   ");
	gotoxy(x,y+1); printf("  ****  ");
	gotoxy(x,y+2); printf("   **   ");
	Sleep(200);
	
	eliminar();
	gotoxy(x,y); printf("*      *");
	gotoxy(x,y+1); printf("  ****  ");
	gotoxy(x,y+2); printf("*      *");
	Sleep(200);
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
    void choque(class Nave &N);
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
//Choque de asteriode
void AST::choque(class Nave &N)
{
	if ((N.getX() + 4 >= x && N.getX() <= x && N.getY() <= y + 0 && N.getY() + 3 >= y)&& ((N.time()<=200)||(N.time()>300)))
	{
		N.menos_corazones();
		N.eliminar();
		N.pintar();
		N.digitar_corazones();
		x = rand() % 71 + 3;
        y = 4;
	}
	if ((N.getX() + 4 >= x && N.getX() <= x && N.getY() <= y + 0 && N.getY() + 3 >= y) && ((N.time()<=300) ||N.time()>200))
	{
		N.mas_corazones();
		N.eliminar();
		N.pintar();
		N.digitar_corazones();
		x = rand() % 71 + 3;
        y = 4;
	}
}
//Enemigo
class Enemigo
{
	int x,y;
	public:
	Enemigo(int a, int b);
	void pintar();
	void eliminar();
	void mover();
	void disparo();
	int getX() { return x; }
    int getY() { return y; }
};
//Constructor de la clase Enemigo
Enemigo::Enemigo(int a, int b)
{
	x=a;
	y=b;
}
//Digitamos el Enemigo
void Enemigo::pintar() {
	gotoxy(x,y); printf("%c",175);
	gotoxy(x,y+1); printf("%c%c%c",204,176,209);
	gotoxy(x,y+2); printf("%c",175);
}
//Movimiento del Enemigo
void Enemigo::mover() {
    gotoxy(x, y);
    eliminar();
    x++;
    if (x > 74) {
    	y = rand() % 18 + 3;
        x = 3;
    }
    pintar();
}
//Borrar Enemigo digitado
void Enemigo::eliminar()
{
	gotoxy(x,y); printf("   ");
	gotoxy(x,y+1); printf("   ");
	gotoxy(x,y+2); printf("   ");
}
/*Disparo del Enemigo
void Enemigo::disparo()
{
	for (short i = 6; i < 77; i++) {
        gotoxy(i, y+1); printf("%c",196);
    }
}*/
//Menu
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

void GuardarPuntajes(const char *nickname, int puntaje){
	ofstream archivo;
	archivo.open("puntajes.txt", ios::app);  // Abre el archivo en modo de anexar
    if (archivo.is_open()) {
        archivo << nickname << "   |   " << puntaje << endl;  // Escribe los datos del jugador en el archivo
        archivo.close();  // Cierra el archivo
    } else {
        cout << "No se pudo abrir el archivo para guardar los datos del jugador." << endl;
    }
}

void MostrarPuntajes(){
	ifstream archivoPuntajes("puntajes.txt");
	if (archivoPuntajes.is_open()) {
		string linea;
		int y = 2;
					
		// Lee y muestra los puntajes linea por linea
		while (getline(archivoPuntajes, linea)) {
			int x = 52;
            
            gotoxy(x, y);
			cout << linea << endl;
			y++;
		}

		archivoPuntajes.close();
	} else {
		cout << "No se pudo abrir el archivo de puntajes." << endl;
	}
}

int main() {

	bool repetir= true;
	Cuadro(0,0,119,24);
	Cuadro(20,1,100,3);
	int option;
	const char *titulo[] = {"   ********      **     **           **       ********      **  ","  **//////**    ****   /**          ****     **//////**    **** ",
	" **      //    **//**  /**         **//**   **      //    **//**  ","/**           **  //** /**        **  //** /**           **  //** ","/**    ***** **********/**       **********/**    ***** **********",
	"//**  ////**/**//////**/**      /**//////**//**  ////**/**//////**"," //******** /**     /**/********/**     /** //******** /**     /**","  ////////  //      // //////// //      //   ////////  //      // "};
	const char *opciones[] = {"Comenzar","Mostrar puntajes","Salir"};
	int num=3;
	do{
		option=menu_principal(titulo, opciones, num);
		switch(option){
			case 1:{
				system("CLS");
				OcultarCursor();
			    pintar_limites();	//Llamamos a la funcion que se encarga de digitar los limites
			    Nave n(30,15,3,0);		//Se imprime la primera posicion de la nave
			    n.pintar();		//Llamamos a la funcion que se encarga de digitar la nave
			    n.digitar_corazones();
			    Enemigo e(3,16);	//Se imprime la primera posicion del enemigo
			    e.pintar();
			    
			    AST ast1(10, 5), ast2(15,8), ast3(38,11);
			    bool game_over = false;
			    int puntaje = 0, time = 50;
			
			    while (game_over==false){
			        ast1.mover(); ast1.choque(n);
			        ast2.mover(); ast2.choque(n);
			        ast3.mover(); ast3.choque(n);
			        n.mover();
			        n.in_time();
			        e.mover();
			        puntaje += 1;
			        
			        
					// Imprimir puntaje en cada iteracion
					gotoxy(1, 1);
					printf("Puntaje: %d", puntaje);
					if(puntaje==200){
						CambioColor();
						gotoxy(24,1);
						printf("Atrapa los meteoritos");
					}
					if(puntaje==300 || puntaje==0){
						RestauraColor();
						gotoxy(24,1);
						printf("                     ");
						time -= 10;
					}
					Sleep(time);	//Menos iteraciones por segundo

					if ( (n.getX() + 4 >= e.getX() && n.getX() <= e.getX() && n.getY() <= e.getY() + 0 && n.getY() + 3 >= e.getY())
						|| n.vidas()==0)
					 
					{
        				n.muerte();
						game_over = true; // Colision detectada, el juego termina
   					 }
    			}
				system("CLS");
				printf("Puntaje: %d", puntaje);
				printf("\n");
				cout<<"Ingrese su nickname (SOLO 3 LETRAS): ";
				char nickname[3] = {0,0,0};
				const int maxCaracteres = 3; // Cambia el número a la cantidad deseada
    			nickname[maxCaracteres + 1]; // +1 para el carácter nulo al final
				int i = 0;
				while (i < maxCaracteres) {
					char ingreso = getch();
					
					if (isalpha(ingreso)) {
						cout << ingreso;
						nickname[i] = ingreso;
						i++;
					}
				}
				
				nickname[i] = '\0';
				Sleep(200);
				GuardarPuntajes(strupr(nickname),puntaje);
				cout<<endl;
				system("pause");
				break;
			}
			case 2: 
			{
				system("CLS");
				gotoxy(50,0);
				cout<<"JUGADOR | PUNTAJE";
				gotoxy(50,1);
				cout<<"-----------------";
				MostrarPuntajes();
				system("pause");
				break;
			}
			case 3:
				repetir=false;
				break;
			
		}
	}while(repetir);
    

    return 0;
}

