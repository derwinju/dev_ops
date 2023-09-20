#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "tubes.h"

#include <stdio.h>
#define boolean int
#define true 1
#define false 0

#include <string.h>
/*
    UNTUK SEMUA INPUT YANG DIPAKAI HARAP DIVALIDASI UNTUK SEMUA KEMUNGKINANNYA
*/

//Untuk mengubah inputam (x,y) menjadi kordinat pada matriks
void generate(char in[100],int inp[2]){
	if (in[2] == ',') {
		inp[0] = (in[0] - '0')*10 + (in[1] - '0');
		if (in[4] < '0' || in[4] > '9')
			inp[1] = (in[3] - '0');
		else
			inp[1] = (in[3]-'0')*10 + (in[4]-'0');
	}
	else if (in[1] == ','){
		inp[0] = (in[0] - '0');
		if (in[3] < '0' || in[3] > '9')
			inp[1] = (in[2] - '0');
		else
			inp[1] = (in[2]-'0')*10 + (in[3]-'0');
	}
}

//Untuk mengecek komponen di rangkaian layout, apakah komponen udh prnah dpake
boolean cek_komp(char used[40][100], char in[100]) {
	boolean found = false;
	int i;
	for (i = 0; i<40; i++) {
		if (strcmp(used[i],in) == 0) {
			found = true;
			break;
		}
	}
	return found;
}


//Keterangan:
//Validasi 1 : Harus komponen RCTJ
//Validasi 2 : Tidak boleh ada komponen yang sama R1, R1
//Validasi 3 : Untuk resistor jarak antar kaki minimal 3 kotak, kapasitor minimal 1 kotak, transistor min 1 kotak, no

//ROUTING MANUAL
void manualRouting(Project *pro) {
	char in[20];
	int netlist, templist,temp,i,j;
	char temprouting;
	char in1[20];
	char symbol;
	//int used[40][2], i, j, k;
	int kor[2];
	printf("Isi 'q' atau 'Q' untuk kembali ke Menu\n");
	printf("Isi 'n' atau 'N' untuk memulai pada simpul (node) baru\n");
	printf("Pilih Simbol (!,@,#,$,%c,^,&,*,(,)): ",'%');
	scanf("%s",in);
	netlist=1;
	if (in[0] == 'q' || in[0] == 'Q')
		;//KEMBALI KE MENU UTAMA
	else {
		while(in[0] != 'q' && in[0] != 'Q') {
			if (in[0] != '!' && in[0] != '@' && in[0] != '#' && in[0] != '$' && in[0] != '%' && in[0] != '^' && in[0] != '&' && in[0] != '*' && in[0] != '(' && in[0] != ')') {
				printf("Masukan harus sesuai simbol [!,@,#,$,%c,^,&,*,(,)]\n",'%');
			}
			else {
				symbol=in[0];
				int count = 1;
				while (in[0] != 'n' && in[0] != 'N') {
					printf("Koordinat %d: ",count);
					scanf("%s",in);
					if (in[0] != 'n' && in[0] != 'N' && in[0] != 'q' && in[0] != 'Q') {
						generate(in,kor);
						//printf("%d%d%c\n",kor[0],kor[1],symbol);
						if((kor[0] <= pro->col )&&(kor[1] <= pro->row )&&(kor[1] > 0 )&&(kor[0] > 0 )){
                            if (pro->routing[kor[0]-1][kor[1]-1] == NULL){
                                pro->netlist[kor[0]-1][kor[1]-1]=netlist;
                                pro->routing[kor[0]-1][kor[1]-1]=symbol;
                                }
                            else{
                                templist=pro->netlist[kor[0]-1][kor[1]-1];
                                temprouting=pro->routing[kor[0]-1][kor[1]-1];
                                for(i=0;i<pro->row;i++){
                                    for(j=0;j<pro->col;j++){
                                        if(pro->routing[i][j] == symbol){
                                            pro->routing[i][j] = temprouting;
                                            pro->netlist[i][j] = templist;
                                        }
                                    }
                                }
                                symbol=temprouting;
                                temp=netlist;
                                netlist=templist;
                                }}
						//printf("%c\n",pro->routing[kor[0]][kor[1]]);
						else {
                            printf("Input koordinat salah, ulangi input\n");
                            count--;
						}
						count++;
					}
					if (in[0] == 'q' || in[0] == 'Q')
						mainMenu(pro);
				}
				if (in[0] == 'q' || in[0] == 'Q')
					mainMenu(pro);
			}
			printf("Pilih Simbol (!,@,#,$,%c,^,&,*,(,)): ",'%');
			scanf("%s",in);
			netlist++;
		}

	}
	mainMenu(pro);
}
void mainMenu(Project *pro){
    //menampilkan tampilan memnu utama
    int menu=0;
    printf("[Menu Utama] :\n");
    printf("Pilih Mode : :\n");
    printf("\t1. Tamplikan Layout\n");
    printf("\t2. Layouting Manual\n");
    printf("\t3. Tamplikan Routing\n");
    printf("\t4. Routing Manual\n");
    printf("\t5. Layout Otomatis\n");
    printf("\t6. Routing Otomatis\n");
    printf("\t7. Design Rule Checker\n");
    printf("\t8. Simpan Proyek dan Keluar\n");
    printf("Pilih Mode :");
    scanf("%d", &menu);

    while((menu < 1) || (menu > 8)){
        printf("\nMode tidak tersedia, silahkan ulangi input\n\n");
        printf("[Menu Utama] :\n");
        printf("Pilih Mode : :\n");
        printf("\t1. Tamplikan Layout\n");
        printf("\t2. Layouting Manual\n");
        printf("\t3. Tamplikan Routing\n");
        printf("\t4. Routing Manual\n");
        printf("\t5. Layout Otomatis\n");
        printf("\t6. Routing Otomatis\n");
        printf("\t7. Design Rule Checker\n");
        printf("\t8. Simpan Proyek dan Keluar\n");
        printf("Pilih Mode :");
        scanf("%d", &menu);
    }
    switch(menu){
        case 1:
        printLayout(pro);
        break;
        case 2:
       manualLayout(pro);
        break;
        case 3:
        printRouting(pro);
        break;
        case 4:
       manualRouting(pro);
        break;
        case 5:
        autoLayout(pro);
        break;
        case 6:
        autoRouting(pro);
        break;
        case 7:

        break;
        case 8:
        saveandExit(pro);
        break;
    }


}
void createNewProject(Project *pro){
    //Inisialisasi membuat matrix layout baru dan routing baru, inisialisasi semua matrix supaya kosong
    printf("Input nama Project :");
    scanf("\n");
    gets(pro->namaPro);
    printf("Input panjang board (1 - 40) : ");
    int temp,i,j;
    scanf("%d",&temp);
    while((temp<1)||(temp>40)){
        printf("Inputan Anda salah , harap ulangi input\n");
        printf("Input panjang board (1 - 40) : ");
        scanf("%d",&temp);
    }
    pro->col=temp;
    printf("Input lebar board (1 - 40) : ");
    scanf("%d",&temp);
    while((temp<1)||(temp>40)){
        printf("Inputan Anda salah , harap ulangi input\n");
        printf("Input lebar board (1 - 40) : ");
        scanf("%d",&temp);
    }
    pro->row=temp;
    for(i=0;i<pro->row;i++){
        for(j=0;j<pro->col;j++){
           pro->layout[i][j].name=NULL;
           pro->routing[i][j]=NULL;
           pro->netlist[i][j]=NULL;}}
    mainMenu(pro);
}

void printLayout(Project *pro){
    int i, j;
    for(i=0;i<=pro->row;i++){
        for(j=0;j<=pro->col;j++){
            if(i == 0){
                if(j==0){
                    printf("   ");
                }
                else{
                printf("%3d",j);
                }
            }
        else if (j == 0){
            printf("%3d",i);
        }
        else{
            if ((pro->layout[i-1][j-1].name ==NULL)) {
                printf("   ");
            }
            else{
            printf("%2c%c", pro->layout[i-1][j-1].name,pro->layout[i-1][j-1].num);
            }
        }}

        printf("\n");
    }
    mainMenu(pro);
}

void printRouting(Project *pro){
    //Print matrix routing
    int i, j;
    //printf("%d",pro->col);
    for(i=0;i<=pro->row;i++){
        for(j=0;j<=pro->col;j++){
            if(i == 0){
                if(j==0){
                    printf("   ");
                }
                else{
                printf("%3d",j);
                }
            }
            else if (j==0){
            printf("%3d",i);
            }
            else{
                if (pro->routing[i-1][j-1] == NULL){
                printf("   ");
                }
                else{
                 printf("%3c", pro->routing[i-1][j-1]);
                }

            }
        }
        printf("\n");
    }
    mainMenu(pro);
}
void manualLayout(Project *pro){
    //menerima input layout dan ekoordinat layout dan memasukannya ke matrix layout
    Layout temp;
    int jarak;
    int numkaki,i, tempx1,tempy1,tempx2,tempy2;
       //     printf("\n%d\n%d\n", pro->col,pro->row);
    printf("[Mode Layout]\nIsi `q` atau `Q` untuk kembali ke menu\nPilih Komponen (R,C,T,J): ");
    scanf(" %c%c",&temp.name,&temp.num);
    //xprintf("%c",temp.name);
    if((temp.name=='q')||(temp.name=='Q')){
        mainMenu(pro);
    }
    else{
       if((temp.name=='J')||(temp.name=='C')||(temp.name=='R')){
        numkaki=2;
        if(temp.name=='J'){
            jarak=1;
        }
        else if(temp.name=='C'){
            jarak=2;
        }

        else if(temp.name=='R'){
            jarak=4;
        }
        for(i=0;i<numkaki;i++){
            printf("Koordinat kaki %d :", i+1);
            scanf("%d,%d",&tempx1, &tempy1);
            //printf("\n%d\n%d\n", pro->col,pro->row);
            while((tempx1<1)||(tempy1>pro->col)||(tempx1>pro->row)||(tempy1<1)||(pro->layout[tempx1-1][tempy1-1].name != NULL)){
                printf("Input eror, ulangi input\n");
                printf("Koordinat kaki %d :", i+1);
                scanf("%d,%d",&tempx1, &tempy1);
            }
            if(i>0){
                while(abs(tempx1+tempy1-tempy2-tempx2) < jarak){
                    printf("jarak kaki terlalu pendek \n");
                    printf("Koordinat kaki %d ", i+1);
                    scanf("%d,%d",&tempx1, &tempy1);
                    while((tempy1<1)||(tempy1>pro->col)||(tempx1>pro->row)||(tempx1<1)){
                        printf("Input eror, ulangi input\n");
                        printf("Koordinat kaki %d :", i+1);
                        scanf("%d,%d",&tempx1, &tempy1);

                        }
                }
            }

            pro->layout[tempx1-1][tempy1-1].name=temp.name;
            pro->layout[tempx1-1][tempy1-1].num=temp.num;
            tempx2=tempx1;
            tempy2=tempy1;
        }
       }
        else if(temp.name=='T'){
        numkaki=3;
        jarak =2;
        for(i=0;i<numkaki;i++){
            printf("Koordinat kaki %d :", i+1);
            scanf("%d,%d",&tempx1, &tempy1);
            while((tempy1<1)||(tempy1>pro->col)||(tempx1>pro->row)||(tempx1<1)||(pro->layout[tempx1-1][tempy1-1].name != NULL)){
                printf("Input eror, ulangi input\n");
                printf("Koordinat kaki %d :", i+1);
                scanf("%d,%d",&tempx1, &tempy1);
            }
            if(i>0){
                while(abs(tempx1+tempy1-tempy2-tempx2) < jarak){
                    printf("jarak kaki terlalu pendek \n");
                    printf("Koordinat kaki %d ", i+1);
                    scanf("%d,%d",&tempx1, &tempy1);
                    while((tempy1<1)||(tempy1>pro->col)||(tempx1>pro->row)||(tempx1<1)){
                        printf("Input eror, ulangi input\n");
                        printf("Koordinat kaki %d :", i+1);
                        scanf("%d,%d",&tempx1, &tempy1);
                        }
                }
            }
            if(i == 0){
                temp.num='c';
            }
            else if(i == 1){
                temp.num='b';
            }
            else if(i == 2){
                temp.num='e';
            }
            pro->layout[tempx1-1][tempy1-1].name=temp.name;
            pro->layout[tempx1-1][tempy1-1].num=temp.num;
            tempx2=tempx1;
            tempy2=tempy1;
        }
       }
        else{
            manualLayout(pro);
        }
    }
    manualLayout(pro);
}

loadFile(Project *pro){
    //printf("\n");
    char nama[30];
    int i, j, max;
    max=0;
    i=0;
    j=0;
    char buffer[1024], *record, *line,v;
    printf("Input nama file Project:");
    scanf("\n",v);
    gets(nama);
    strcat(nama,"_layout.csv");

    FILE *fp = fopen(nama,"r");
   // printf("file berhasil dibuka\n");
    if (fp == NULL)
   {
       printf(" Failed to load file!\n");
        fclose(fp);
       loadFile(pro);

   }
   while((line=fgets(buffer,sizeof(buffer),fp))!= NULL)
   {
    j=0;
    // printf("record : %s\n",line) ;
    record = strtok(line,";");
     while((record != NULL))
     {
     //printf("record : %c%c%d%d\n",record[0],record[1],i,j) ;    //here you can put the record into the array as per your requirement.
     pro->layout[i][j].name = record[0];
     pro->layout[i][j].num = record[1];
     //printf("%c%c\n%d%d\n",record[0],record[1],i,j);
     j++;
     record = strtok(NULL,";");
     }
     if(max<j){max=j;}
     ++i ;
   }
    pro->row=i;
   fclose(fp);
    strcpy(nama,strtok(nama,"_"));
    //printf("%s", nama);
    //////////////////////file routing
    fp = fopen(strcat(nama,"_routing.csv"),"r");

    fp = fopen(nama,"r");
        if (fp == NULL)
   {
       printf(" Failed to load file!\n");
       loadFile(pro);
   }
   printf("\n\n\n");
   i=0;
   while(((line=fgets(buffer,sizeof(buffer),fp))!=NULL))
   {
        j=0;
     //printf("record : %s",line) ;
     record = strtok(line,";");
     while((record != NULL))
     {
     //printf("\nrecord : %s",record) ;    //here you can put the record into the array as per your requirement.
     pro->routing[i][j] = record[0];
     j++;
     record = strtok(NULL,";");
     }
     if(max < j){max=j;}
     ++i ;
   }
   fclose(fp);
    strcpy(pro->namaPro,strtok(nama,"_"));
    if(i > pro->row){
    pro->row=i;}
   pro->col=max;
}
void autoLayout (Project *pro){
    //assign kembali size pcb agar dapat memuat CE
    pro->row=15;
    pro->col=10;

    //assign J1
    pro->layout[6][0].name='J';
    pro->layout[6][0].num='1';
    pro->layout[8][0].name='J';
    pro->layout[8][0].num='1';

    //assign C1
    pro->layout[6][1].name='C';
    pro->layout[6][1].num='1';
    pro->layout[6][3].name='C';
    pro->layout[6][3].num='1';

    //assign R1
    pro->layout[0][3].name='R';
    pro->layout[0][3].num='1';
    pro->layout[4][3].name='R';
    pro->layout[4][3].num='1';

    //assign R2
    pro->layout[8][3].name='R';
    pro->layout[8][3].num='2';
    pro->layout[12][3].name='R';
    pro->layout[12][3].num='2';

    //assign T
    pro->layout[6][4].name='T';
    pro->layout[6][4].num='b';
    pro->layout[5][5].name='T';
    pro->layout[5][5].num='c';
    pro->layout[7][5].name='T';
    pro->layout[7][5].num='e';

    //assign R3
    pro->layout[0][5].name='R';
    pro->layout[0][5].num='3';
    pro->layout[4][5].name='R';
    pro->layout[4][5].num='3';

    //assign C2
    pro->layout[4][6].name='C';
    pro->layout[4][6].num='2';
    pro->layout[4][8].name='C';
    pro->layout[4][8].num='2';

    //assign R4
    pro->layout[8][5].name='R';
    pro->layout[8][5].num='4';
    pro->layout[12][5].name='R';
    pro->layout[12][5].num='4';

    //assign C3
    pro->layout[8][6].name='C';
    pro->layout[8][6].num='3';
    pro->layout[12][6].name='C';
    pro->layout[12][6].num='3';

    //assign J2
    pro->layout[5][8].name='J';
    pro->layout[5][8].num='2';
    pro->layout[7][8].name='J';
    pro->layout[7][8].num='2';

    //pesan bahwa autoLayout berhasil
    printf("Selamat! Auto Layout Rangkaian CE berhasil!\n\n");

    //menandakan bahwa autoLayout telah dilakukan
    pro->autoLay=1;

    //kembali ke main menu
    mainMenu(pro);
}

void autoRouting (Project *pro){
    //periksa apakah autoLayout sudah dilakukan
    //jika belum tidak akan di proses
    int i;
    if (pro->autoLay==0)
        printf("Lakukan Auto Layout terlebih dahulu!\n\n");
    else{
        //kosongin kedua array;
        for(i=0; i<pro->row; i++){
            for(int j=0; j<pro->col; j++){
                pro->routing[i][j]=0;
                pro->netlist[i][j]=NULL;
            }
        }

        //isi routing secara "semiAuto"
        //isi !
        for(i=3; i<=5; i++){
            pro->routing[0][i]='!';
            pro->netlist[0][i]=1;
        }

        //isi @
        for(i=4; i<=8; i++){
            pro->routing[i][3]='@';
            pro->netlist[i][3]=2;
        }
        pro->routing[6][4]='@';
        pro->netlist[6][4]=2;

        //isi #
        for(i=0; i<=1; i++){
            pro->routing[7][i]='#';
            pro->netlist[7][i]=3;
        }

        //isi $
        for(i=8; i<=12; i++){
            pro->routing[i][0]='$';
            pro->netlist[i][0]=4;
        }
        for(i=1; i<=8; i++){
            pro->routing[12][i]='$';
            pro->netlist[12][i]=4;
        }
        for(i=7; i<=11; i++){
            pro->routing[i][8]='$';
            pro->netlist[i][8]=4;
        }

        //isi %
        for(i=4; i<=5; i++){
            pro->routing[i][8]='%';
            pro->netlist[i][8]=5;
        }

        //isi ^
        for(i=5; i<=6; i++){
            pro->routing[4][i]='^';
            pro->netlist[4][i]=6;
        }
        pro->routing[5][5]='^';
        pro->netlist[5][5]=6;

        //isi &
        for(i=5; i<=6; i++){
            pro->routing[8][i]='&';
            pro->netlist[8][i]=7;
        }
        pro->routing[7][5]='&';
        pro->netlist[7][5]=7;

        //keluarkan pesan autoRouting berhasil
        printf("Selamat! Auto Routing berhasil!\n\n");
    }
    mainMenu(pro);
}
void saveandExit(Project *pro){
//    FILE *fp=fopen()
    char nama[30];
    int i, j;
    strcpy(nama, pro->namaPro);
    strcat(nama, "_layout.csv");
    FILE *fp= fopen(nama,"w");
    for (i = 0; i<pro->row; i++){
    for (j = 0; j< pro->col; j++){
        if(pro->layout[i][j].name == NULL){
            pro->layout[i][j].name=' ';
            pro->layout[i][j].num=' ';
        }
        if (j == 0){
            fprintf(fp, "%c%c",pro->layout[i][j].name,pro->layout[i][j].num);}
        else{
            fprintf(fp, ";%c%c",pro->layout[i][j].name,pro->layout[i][j].num);}
        }
        fprintf(fp,"\n");
    }

    fclose(fp);
    strtok(nama,"_");
    strcat(nama, "_routing.csv");
    fp= fopen(nama,"w");
    for (i = 0; i<pro->row; i++){
    for (j = 0; j< pro->col; j++){
        if(pro->routing[i][j] == NULL){
            pro->routing[i][j] = ' ';
        }
        if (j == 0){
            fprintf(fp, "%c",pro->routing[i][j]);}
        else{
            fprintf(fp, ";%c",pro->routing[i][j]);}
        }
        fprintf(fp,"\n");
    }

    fclose(fp);
    exit(0);
}
