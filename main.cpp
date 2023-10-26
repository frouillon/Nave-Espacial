#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>

#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define ENTER 13
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
void menu();
float operacion(float);
void Cuadro(int x1,int y1,int x2,int y2);
void gotoxy(int x,int y);
int menu_principal(const char *titulo[], const char *opciones[], int num);
int main(){
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	bool repetir= true;
	system("COLOR B0");
	Cuadro(0,0,119,24);
	Cuadro(20,1,100,3);
	int option;
	const char *titulo[] = {"   ********      **     **           **       ********      **  ","  **//////**    ****   /**          ****     **//////**    **** ",
	" **      //    **//**  /**         **//**   **      //    **//**  ","/**           **  //** /**        **  //** /**           **  //** ","/**    ***** **********/**       **********/**    ***** **********",
	"//**  ////**/**//////**/**      /**//////**//**  ////**/**//////**"," //******** /**     /**/********/**     /** //******** /**     /**","  ////////  //      // //////// //      //   ////////  //      // "};
	const char *opciones[] = {"Comenzar","Salir"};
	int num=2;
	/*
	gotoxy(55,2);cout<<"###GALAGA###"<<endl;
	char resp=' ';
	float sueldo,sueldo_neto;*/
	do{
		option=menu_principal(titulo, opciones, num);
		switch(option){
			case 1:
				system("cls");
				cout<<"incializando"<<endl;
				system("pause");
				break;
			
			case 2:
				repetir=false;
				break;
			
		}
		/*
		menu();
		gotoxy(2,12);
		cout<<"Ingrese una valor correcto: "<<endl;
		gotoxy(2,14);
		cin>>resp;
		switch(resp){
			case '1':{
				system("cls");
				cout<<"Mencione su sueldo b�sico:"<<endl;
				cin>>sueldo;
				sueldo_neto=operacion(sueldo);
				cout<<"Tu sueldo es: "<<sueldo_neto;
			break;
			}
			default:{
				menu();	
			break;
			}
			*/
	}while(repetir);
	return 0;
}
/*
void menu(){
	gotoxy(2,6);
	cout<<"Escoja una de las siguientes opciones:"<<endl;
	gotoxy(2,8);
	cout<<"1.- Usted es nombrado.";
	gotoxy(2,10);
	cout<<"0.- Salir ";
}
*/
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
		}while(tecla!=TECLA_ARRIBA && tecla!=TECLA_ABAJO && tecla!=ENTER);
		
		switch(tecla){
			case TECLA_ARRIBA:
				seleccion--;
				if(seleccion==0){
					seleccion=num;
				}
				break;
			case TECLA_ABAJO:
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

void gotoxy(int x,int y){
      HANDLE hcon;
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD dwPos;
      dwPos.X = x;
      dwPos.Y= y;
      SetConsoleCursorPosition(hcon,dwPos);
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

