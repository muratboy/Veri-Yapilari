#include <stdio.h>
#include <stdlib.h>

struct cift_yonlu_eleman{
	int icerik;
	struct cift_yonlu_eleman* ileri;
	struct cift_yonlu_eleman* geri;
};

typedef struct cift_yonlu_eleman Celeman;
typedef Celeman* Celemanptr;

Celemanptr yeni_eleman(int icerik){
	Celemanptr eleman;
	eleman = (Celemanptr)malloc(sizeof(Celeman));
	eleman->icerik = icerik;
	eleman->geri = eleman->ileri = NULL;
	return eleman;
}

struct ciftliste{
	Celemanptr bas;
	Celemanptr son;
};

typedef struct ciftliste Cliste;
typedef Cliste* Clisteptr;

Clisteptr yeni_liste(){
	Clisteptr liste;
	liste = (Clisteptr)malloc(sizeof(Cliste));
	liste->bas = liste->son = NULL;
	return liste;
}

void liste_basina_ekle(Celemanptr yeni,Clisteptr liste){
	if(liste->son == NULL)
		liste->son = yeni;
	else{
		liste->bas->geri = yeni;
		yeni->ileri = liste->bas;
	}
	liste->bas = yeni;
}

void liste_sonuna_ekle(Celemanptr yeni,Clisteptr liste){
	if(liste->bas == NULL)
		liste->bas = yeni;
	else{
		liste->son->ileri = yeni;
		yeni->geri = liste->son;
	}
	liste->son = yeni;
}

void liste_ortasina_ekle(Celemanptr yeni,Celemanptr once){
	yeni->ileri = once->ileri;
	yeni->geri = once;
	once->ileri->geri = yeni;
	once->ileri = yeni;
}

void liste_basini_sil(Clisteptr liste){
	if(!liste) return;
	liste->bas = liste->bas->ileri;
	if(liste->bas == NULL)
		liste->son = NULL;
	else
		liste->bas->geri = NULL;
}

void liste_sonunu_sil(Clisteptr liste){
	if(!liste) return;
	liste->son = liste->son->geri;
	if(liste->son == NULL)
		liste->bas = NULL;
	else
		liste->son->ileri = NULL;
}

void listeden_sil(Celemanptr s){
	s->geri->ileri = s->ileri;
	s->ileri->geri = s->geri;
}

void liste_yazdir(Clisteptr liste){
  Celemanptr eleman;
  eleman=liste->bas;
  while(eleman!=NULL){
      printf("%4d ",eleman->icerik);
      eleman=eleman->ileri;
  }
}

void liste_yazdir_sondan(Clisteptr liste){
  Celemanptr eleman;
  eleman=liste->son;
  while(eleman!=NULL){
      printf("%4d ",eleman->icerik);
      eleman=eleman->geri;
  }
}

int eleman_sayisi(Celemanptr eleman){
     if(eleman==NULL) return 0;
     return 1+eleman_sayisi(eleman->ileri);
}

//<-------------------------------------dairesel bagli liste------------------------------->

struct daireliste{
	Celemanptr bas;
};

typedef struct daireliste Dliste;
typedef Dliste* Dlisteptr;

Dlisteptr yeni_daire_liste(){
	Dlisteptr d;
	d = (Dlisteptr)malloc(sizeof(Dliste));
	d->bas = NULL;
	return d;
}

void daire_eleman_ekle(Celemanptr yeni, Dlisteptr d){
	if(!yeni) return;
	if(!d->bas) {
		yeni->ileri = yeni;
		yeni->geri = yeni;
	}else{
		yeni->ileri = d->bas;
		yeni->geri = d->bas->geri;
		d->bas->geri->ileri = yeni;
		d->bas->geri = yeni;
	}
	d->bas = yeni;
}

void daire_eleman_sil(Celemanptr e, Dlisteptr d){
	if(!e || !d->bas) return;
	Celemanptr temp = d->bas;
	while(temp && temp->icerik != e->icerik){
		temp = temp->ileri;
	}
	if(!temp) return;
	if(temp->icerik == e->icerik){
		temp->geri->ileri = temp->ileri;
		temp->ileri->geri = temp->geri;
	}
}

//------------------------------------------------------------
int main(int argc, char** argv) {
    Clisteptr liste;
    liste=yeni_liste();
    liste_basina_ekle(yeni_eleman(100),liste);
    liste_basina_ekle(yeni_eleman(500),liste);
    liste_sonuna_ekle(yeni_eleman(700),liste);
    liste_ortasina_ekle(yeni_eleman(9),liste->bas->ileri);
    liste_yazdir(liste);
    printf("\n");
	liste_yazdir_sondan(liste);
	printf("\n");
	listeden_sil(liste->bas->ileri);
	liste_yazdir(liste);
	printf("\n");
	liste_basini_sil(liste);
	liste_yazdir(liste);
	printf("\n");
	liste_sonunu_sil(liste);
	liste_yazdir(liste);
    printf("\n");
    printf("Eleman sayisi: %4d\n",eleman_sayisi(liste->bas));
	Dlisteptr dliste = yeni_daire_liste();
	daire_eleman_ekle(yeni_eleman(111),dliste);
	daire_eleman_ekle(yeni_eleman(222),dliste);
	daire_eleman_ekle(yeni_eleman(333),dliste);
	daire_eleman_sil(dliste->bas,dliste);

    return (EXIT_SUCCESS);
}
