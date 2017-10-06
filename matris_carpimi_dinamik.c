#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tek_boyutlu_dizi {
    int eleman_sayisi;
    int *dizi_basi;
};

void tek_boyutlu_dizi_olustur(struct tek_boyutlu_dizi *tek, int eleman_sayisi){
    int i;
    tek->eleman_sayisi= eleman_sayisi;
    tek->dizi_basi = (int*)malloc(eleman_sayisi*sizeof(int));
    for(i=0; i<eleman_sayisi; i++){
        tek->dizi_basi[i] = rand()%10;
    }
}

void print_tek_boyutlu_dizi(struct tek_boyutlu_dizi *tek){
    int i;
    for(i=0; i<tek->eleman_sayisi; i++){
         printf("%4d ", tek->dizi_basi[i]);
    }
    printf("\n");
}

void matris_olustur_dinamik(int ***dizi,int satir,int sutun){
    int i,j;
    *dizi=(int**)malloc(satir*sizeof(int*));
   
    for(i=0; i<satir; i++){
        *(*dizi+i)= (int*)malloc(sutun*sizeof(int));//i. satir icin sutun sayisi kadar yer ayir
        for(j=0; j<sutun; j++)
            *(*(*dizi+i)+j)= rand()%10;	//i. satirdaki elemanlarin herbirine 0<=rastgele degerler<10 ata
    }
}

void matris_degistir(int **dizi, int satir, int sutun){
    int i,j;
    for(i=0; i<satir; i++)
        for(j=0; j<sutun; j++)
            *(*(dizi+i)+j)=rand()%2;//matristeki her elemana rastgele 0 yada 1 ata 
}

void matris_yaz_dinamik(int **dizi,int satir,int sutun){
    int i,j;
    for(i=0; i<satir; i++){
        for(j=0; j<sutun; j++) printf("%4d ",*(*(dizi+i)+j));
        printf("\n");
    }
}

void matris_carpimi_dinamik(int **A,int A_satir, int A_sutun,
                           int **B, int B_satir, int B_sutun,
                           int **C, int C_satir, int C_sutun){
    int i,j,k;
    if(A_sutun!=B_satir){
        printf("Carpim matrislerinin boyutlari uyusmuyor!!!");
        return;
    }
    else if(A_satir!=C_satir || B_sutun!=C_sutun){
        printf("Sonuc matrisinin boyutlari carpan matrislere uymuyor!!!\n");
        return;
    }
    else{
        for(i=0; i<A_satir; i++)
            for(j=0; j<B_sutun; j++){
                C[i][j]=0;
                for(k=0; k<A_sutun; k++)
                    C[i][j]=C[i][j]+A[i][k]*B[k][j];
                    
		}   
    }
}

int main(int argc, char** argv) {
    int **A,**B,**C;
    srand(time(NULL)); // rastgele (random) sayilar olusturmak icin
    
    printf("---------------------dinamik_dizi---------------------------\n");
    struct tek_boyutlu_dizi tek;
    struct tek_boyutlu_dizi *d=&tek;
    tek_boyutlu_dizi_olustur(d,10);
    print_tek_boyutlu_dizi(d);
 
	printf("---------------------dinamik_matris-------------------------\n");
    matris_olustur_dinamik(&A,5,6);
    matris_olustur_dinamik(&B,6,7);
    matris_olustur_dinamik(&C,5,7);
    printf("--- A matrisi ----\n");
    matris_yaz_dinamik(A,5,6);
    printf("--- B matrisi ----\n");
    matris_yaz_dinamik(B,6,7);
    printf("--- C matrisi ----\n");
    matris_yaz_dinamik(C,5,7);
    
    printf("--------------------matrisleri_degistir---------------------\n");
    matris_degistir(A,5,6);
    matris_degistir(B,6,7);
    matris_degistir(C,5,7);
    printf("--- A matrisi ----\n");
    matris_yaz_dinamik(A,5,6);
    printf("--- B matrisi ----\n");
    matris_yaz_dinamik(B,6,7);
    printf("--- C matrisi ----\n");
    matris_yaz_dinamik(C,5,7);
    
    printf("--------------------matrislerin_carpimi---------------------\n");
    matris_carpimi_dinamik(A,5,6,B,6,7,C,5,7);
    printf("---- C=A*B matrisi ----\n");
    matris_yaz_dinamik(C,5,7);
    
    return (EXIT_SUCCESS);
}

