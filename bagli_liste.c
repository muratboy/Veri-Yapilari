#include <stdio.h>
#include <stdlib.h>
//<------------------------------bagli_liste---------------------->
//bagli liste eleman tanimlama
struct eleman{
	int icerik;
	struct eleman* ileri;
};

typedef struct eleman Eleman;
typedef Eleman* Elemanptr;

//bagli liste yeni eleman olusturma
Elemanptr yeni_eleman(int icerik){
	Elemanptr eleman;
	eleman = (Elemanptr)malloc(sizeof(Eleman));
	eleman->icerik = icerik;
	eleman->ileri = NULL;
	return eleman;
}

//bagli liste tanimlama
struct liste{
	Elemanptr bas;
	Elemanptr son;
};

typedef struct liste Liste;
typedef Liste* Listeptr;

//yeni bagli liste olusturma
Listeptr yeni_liste(){
	Listeptr liste;
	liste = (Listeptr)malloc(sizeof(Liste));
	liste->bas = liste->son = NULL;
	return liste;
}

void liste_basina_ekle(Listeptr l,Elemanptr yeni){
	if(l->bas == NULL)//yada if(!l->bas)
		l->son = yeni;
	else
		yeni->ileri = l->bas;//liste bos olmadiginda yeni'nin sonuna listenin basini bagla
	l->bas = yeni;
//listenin basi bos ise(yani liste bos ise) listenin basi ve sonu yeni olacak
}

void liste_sonuna_ekle(Listeptr l,Elemanptr yeni){
	if(l->son == NULL)
		l->bas = yeni;
	else
		l->son->ileri = yeni;//liste bos olmadiginda listenin sonuna yeni'yi bagla
	l->son = yeni;
}

void liste_ortaya_ekle(Elemanptr yeni,Elemanptr once){
	yeni->ileri = once->ileri;//yeni'yi eklenecek yerin ilerisine tuttur
	once->ileri = yeni;//sonra once'nin bagini kopar yeniye bagla
}

void liste_sirali_ekle(Listeptr l, Elemanptr yeni){
    Elemanptr onceki,simdiki;
    onceki=NULL;
    simdiki=l->bas;
    while(simdiki!=NULL && simdiki->icerik < yeni->icerik){
        onceki=simdiki;
        simdiki=simdiki->ileri;
    }
    if(l->bas==NULL) {
        l->bas=l->son=yeni;
    }
    else if(simdiki==l->bas) {
       yeni->ileri=l->bas;
       l->bas=yeni;
    }
    else {
        onceki->ileri=yeni;
        yeni->ileri=simdiki;
    }
}

void liste_sirala(Listeptr l){
    Elemanptr simdiki,sonraki;
    if(l->bas == l->son) return;
    simdiki=l->bas->ileri;
    l->bas->ileri=NULL;
    l->son=l->bas;
    while(simdiki!=NULL){
        sonraki=simdiki->ileri;
        simdiki->ileri=NULL;
        liste_sirali_ekle(l,simdiki);
        simdiki=sonraki;
    }
}

Elemanptr liste_ara(Listeptr l,int deger){
	Elemanptr temp;
	temp = l->bas;
	while(temp){
		if(temp->icerik == deger)
			return temp;
		temp = temp->ileri;
	}
	return NULL;
}

Elemanptr inci_eleman(Listeptr l,int i){
	Elemanptr temp = l->bas;
	int j = 0;
	while (temp != NULL && j<i){
		j++;
		temp = temp->ileri;
	}
	return temp;
}

void liste_basi_sil(Listeptr l){
	l->bas = l->bas->ileri;
	if(l->bas == NULL)
		l->son = NULL;
}

void liste_sonu_sil(Listeptr l){
	Elemanptr temp,once;
	temp = l->bas;
	once = NULL;
	while(temp != l->son){
		once = temp;
		temp = temp->ileri;
	}
	if(once == NULL)
		l->bas = NULL;
	else
		once->ileri = NULL;
	l->son = once;
}

void listeden_sil(Listeptr l,Elemanptr s){
	Elemanptr tmp,once;
	tmp = l->bas;
	once = NULL;
	while(tmp != s){
		once = tmp;
		tmp = tmp->ileri;
	}
	once->ileri = s->ileri;
}

void liste_eleman_sil(Listeptr l, int silinen){
	Elemanptr simdiki,onceki;
	simdiki=l->bas;
	while(simdiki!=NULL && simdiki->icerik!=silinen){
        onceki=simdiki;
        simdiki=simdiki->ileri;
	}
	if(simdiki==NULL) return;
	else if(simdiki==l->bas) {
		l->bas=l->bas->ileri;
    		if(simdiki==l->son) l->son = l->bas;
    	}
    	else{
        onceki->ileri=simdiki->ileri;
        if(simdiki==l->son) l->son = onceki;
    	}
}

void liste_sil(Listeptr *l){
	Elemanptr simdiki,sonraki;
    	simdiki=(*l)->bas;
    	while(simdiki!=NULL){
        	sonraki=simdiki->ileri;
        	free(simdiki);
        	simdiki=sonraki;
    	}
    	free(*l);
    	*l=NULL;
}

int eleman_sayisi(Listeptr l){
	int sayac = 0;
	Elemanptr temp;
	temp = l->bas;
	while(temp){
		temp = temp->ileri;
		sayac++;
	}
	return sayac;
}

Listeptr birlestir(Listeptr l1,Listeptr l2){
	Listeptr temp;
	if(l1->bas == NULL)
		return l2;
	if(l2->bas == NULL)
		return l1;
	temp =(Listeptr)malloc(sizeof(Liste));
	temp->bas = l1->bas;
	temp->son = l2->son;
	l1->son->ileri = l2->bas;
	return temp;
}

void liste_yaz(Listeptr l){
	Elemanptr temp;
	if(l==NULL) return;
	temp = l->bas;
	while(temp){//yada while(temp!=NULL)
		printf("%4d ",temp->icerik);
		temp = temp->ileri;
	}
	printf("\n");
}

void liste_yaz_tersten(Elemanptr liste_basi){
    if(liste_basi){//yada if(liste_basi!=NULL)
        liste_yaz_tersten(liste_basi->ileri);
        printf("%5d ",liste_basi->icerik);
    }
}

Elemanptr *ters(Elemanptr *liste_basi){
    	Elemanptr gecici;
    	if(*liste_basi==NULL)// yada if(!*liste_basi)
		return liste_basi;
    	else if((*liste_basi)->ileri==NULL)
		return &((*liste_basi)->ileri);
    	else {
        	gecici=*liste_basi;
        	*liste_basi=(*liste_basi)->ileri;
        	*ters(liste_basi)=gecici;
         	gecici->ileri=NULL;
        	return &(gecici->ileri);
    	}
}
//----------------------------------------------------------------
int main(int argc, char** argv) {
    Listeptr liste1;
    //Listeptr sirali;

    liste1=yeni_liste();
    liste_basina_ekle(liste1,yeni_eleman(20));
    liste_basina_ekle(liste1,yeni_eleman(80));
    liste_sonuna_ekle(liste1,yeni_eleman(-50));
    liste_sonuna_ekle(liste1,yeni_eleman(-30));
    liste_sonuna_ekle(liste1,yeni_eleman(-100));
    liste_sonuna_ekle(liste1,yeni_eleman(300));
    liste_sonuna_ekle(liste1,yeni_eleman(76));
    liste_sonuna_ekle(liste1,yeni_eleman(67));

    liste_yaz(liste1);
    printf("\n");

    ters(&(liste1->bas));
    liste_yaz(liste1);
    printf("\n");

    return (EXIT_SUCCESS);
}
