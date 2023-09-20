#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#ifndef TUBES_H
#define TUBES_H
//Struct Layout
typedef struct Layout{
    char name;
    char num;}Layout;
typedef struct Project{
    char nama[30];
    Layout layout[40][40];
    char routing[40][40];
    int row;
    int col;
    char namaPro[30];
    int netlist [40][40];
    int autoLay;
    }Project;

//Procedure
void mainMenu(Project *pro);
void loadFile(Project *pro);
void saveandExit(Project *pro);
void createNewProject(Project *pro);
void printLayout(Project *pro);
void printRouting(Project *pro);
void manualLayout(Project *pro);
void manualRouting(Project *pro);
//Design Rule Checker , gw masih ga ngerti ini ngapain

/////////////////////////////////////////////BONUS
void autoLayout(Project *pro);
void autoRouting(Project *pro);

#endif
