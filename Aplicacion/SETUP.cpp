/* @Author: Sebastian Sanchez Bentolila
https://github.com/Sebastian-Sanchez-Bentolila */

//Modules
#include<iostream>
#include<stdlib.h>
using namespace std;

//Variables
char pyserial[21]="pip install pyserial";

void cmd(){
    system(pyserial);
}

int main(){
    cmd();
    cout<<"Intalacion finalizada. Puede cerrar la ventana\n";
    system("pause");
    return 0;
}
