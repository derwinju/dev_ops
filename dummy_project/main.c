
#include <stdio.h>
#include "tubes.c"
/*
    UNTUK SEMUA INPUT YANG DIPAKAI HARAP DIVALIDASI UNTUK SEMUA KEMUNGKINANNYA
*/
int main(){
    Project pro;
    pro.autoLay=0;
    printf("Menu:\n");
    printf("1.\t Buat Proyek Baru\n");
    printf("2.\t Muat Proyek dari Berkas\n");
    printf("3.\t Keluar\n");
    printf("Masukan :");
    int menu;
    scanf("%d", &menu);
    while((menu<1)||(menu>3)){
        printf("Input salah , Ulangi input\n");
        printf("Menu:\n");
        printf("1.\t Buat Proyek Baru\n");
        printf("2.\t Muat Proyek dari Berkas\n");
        printf("3.\t Keluar\n");
        printf("Masukan :");
        scanf("%d", &menu);
    }
    if(menu == 1){
        createNewProject(&pro);

    }
    else if (menu == 2){

        loadFile(&pro);
        mainMenu(&pro);
    }


}
