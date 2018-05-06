#include <stdio.h>
#include <stdlib.h>
//<------------------------------bagli_liste---------------------->
//bagli liste eleman tanimlama
struct eleman{
	int icerik;
	struct eleman* ileri;		//elemanin kendisinden sonraki elemani isaret etmesi icin pointer
};

typedef struct eleman Eleman;
typedef Eleman* Elemanptr;		//kolaylik olmasi acisindan kisaltmalar

//bagli liste yeni eleman olusturma
Elemanptr yeni_eleman(int icerik){
	Elemanptr eleman;
	eleman = (Elemanptr)malloc(sizeof(Eleman));//heap'ten elemana yer ayir
	eleman->icerik = icerik;	//olusturulan elemanın icerik ozelligine parametre olarak gelen icerik atanir
	eleman->ileri = NULL;		//eleman yeni olusturuldugundan bir yere isaret etmez
	return eleman;
}

//bagli liste tanimlama
struct liste{
	Elemanptr bas;				//elemanlardan olusan bir liste tanimliyoruz
	Elemanptr son;				//listenin basindaki ve sonundaki elemanlari isaret eden pointerlar tanimliyoruz
};

typedef struct liste Liste;
typedef Liste* Listeptr;

//yeni bagli liste olusturma
Listeptr yeni_liste(){
	Listeptr liste;
	liste = (Listeptr)malloc(sizeof(Liste));
	liste->bas = liste->son = NULL;//yeni olusturulan listenin hic elemani olmadigindan ilk ve son elemani NULL
	return liste;
}

//l isimli listenin basina yeni isimli elemani ekleme
void liste_basina_ekle(Listeptr l,Elemanptr yeni){
	if(l->bas == NULL)//yada if(!l->bas)
		l->son = yeni;			//listenin basi bos ise(yani liste bos ise) listenin basi ve sonu yeni olacak
	else
		yeni->ileri = l->bas;	//liste bos olmadiginda yeni'nin sonuna listenin basini bagla
	l->bas = yeni;				//listenin basi yeni elemani gostersin								
}

//l isimli listenin sonuna yeni isimli elemani ekleme
void liste_sonuna_ekle(Listeptr l,Elemanptr yeni){
	if(l->son == NULL)			//liste bos ise
		l->bas = yeni;			//listenin basi yeni olsun
	else
		l->son->ileri = yeni;	//liste bos olmadiginda listenin sonunun ilerisine yeni'yi bagla
	l->son = yeni;				//listenin sonu yeni olsun
}

void liste_ortaya_ekle(Elemanptr once,Elemanptr yeni){
	yeni->ileri = once->ileri;	//yeni elemanin ilerisindeki eleman, eklenecek yerdeki elemanin ilerisindeki eleman olsun
	once->ileri = yeni;			//yeni eleman oncenin ilerisini tuttuğuna gore oncenin ilerisi artik yeni olsun
}

//yeni elemani listeye buyuklugune gore ilk uygun yere ekleme
void liste_sirali_ekle(Listeptr l, Elemanptr yeni){
    Elemanptr onceki,simdiki;
    onceki=NULL;
    simdiki=l->bas;
    //listede yeni'nin iceriginden buyuk icerikli bir eleman bulana kadar ilerliyoruz
    while(simdiki!=NULL && simdiki->icerik < yeni->icerik){
        onceki=simdiki;			//geriye gidemedigimiz icin bir onceki konumu tutuyoruz
        simdiki=simdiki->ileri;
    }
    //liste bossa 
    if(l->bas==NULL) {
        l->bas=l->son=yeni;
    }
    //while dongusuyle yeni'nin iceriginden daha buyuk icerikli bir eleman bulunamadiysa
    else if(simdiki==l->bas) {
       yeni->ileri=l->bas;
       l->bas=yeni;
    }
    //while dongusunde bulunan yeni'den buyuk elemanin bir oncesine yeniyi ekliyoruz
    else {
		if(simdiki==NULL) l->son=yeni;//listenin sonunun yeri kaydigi icin ekledim
        onceki->ileri=yeni;
        yeni->ileri=simdiki;
    }
}

//tum listeyi siralama(liste_sirali_ekle(..) fonksiyonuyla birlikte calisiyor)
void liste_sirala(Listeptr l){
    Elemanptr simdiki,sonraki;
    if(l->bas == l->son) return;//tek elemanli ise zaten sirali 
    simdiki=l->bas->ileri;		//liste basindan sonraki listeyi gecici olarak tut
    l->bas->ileri=NULL;			//listenin basini listeden ayir 
    l->son=l->bas;				//tek elemanli bir listemiz oldu
    while(simdiki!=NULL){		//gecici listede eleman kalmayana kadar 
        sonraki=simdiki->ileri;
        simdiki->ileri=NULL;	//tek tek listenin baslarini gecici listeden ayir
        liste_sirali_ekle(l,simdiki);	//her ayrilan elemani basta elde ettigimiz listeye sirali ekle
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

int inci_eleman(Listeptr l,int i){
	Elemanptr temp = l->bas;
	int j = 0;
	while (temp != NULL && j<i){
		j++;
		temp = temp->ileri;
	}
	return j;
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
        printf("%4d ",liste_basi->icerik);
    }
}

//listeyi özyinelemeli olarak ters çevirme
Elemanptr *ters(Elemanptr *liste_basi){
    	Elemanptr gecici;
    	if(*liste_basi==NULL)
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
    Listeptr liste2;

    liste1=yeni_liste();
    liste2=yeni_liste();
    
    liste_basina_ekle(liste1,yeni_eleman(20));
    liste_basina_ekle(liste1,yeni_eleman(80));
    liste_sonuna_ekle(liste1,yeni_eleman(-50));
    liste_sonuna_ekle(liste1,yeni_eleman(-30));
    liste_sonuna_ekle(liste1,yeni_eleman(-100));
    liste_sonuna_ekle(liste1,yeni_eleman(300));
    liste_sonuna_ekle(liste1,yeni_eleman(760));
    liste_sonuna_ekle(liste1,yeni_eleman(670));
    liste_ortaya_ekle(liste1->bas->ileri->ileri,yeni_eleman(140));
    
    liste_basina_ekle(liste2,yeni_eleman(81));
    liste_sonuna_ekle(liste2,yeni_eleman(-51));
    liste_sonuna_ekle(liste2,yeni_eleman(-31));
    liste_sonuna_ekle(liste2,yeni_eleman(-101));
    liste_ortaya_ekle(liste2->bas->ileri,yeni_eleman(171));

    printf("olusturdugunuz liste:\n");
    liste_yaz(liste1);

    printf("listenin eleman sayisi:\n");
    printf("%4d\n",eleman_sayisi(liste1));

    liste_sirala(liste1);
    printf("listenin siralanmis hali:\n");
    liste_yaz(liste1);

	liste_sirali_ekle(liste1,yeni_eleman(40));
	printf("yeni eklenen elemanin sirali eklenmis hali:\n");
	liste_yaz(liste1);

	printf("listenin tersten yazdirilmasi:\n");
	liste_yaz_tersten(liste1->bas);
	printf("\n");
	
	{liste1->son=liste1->bas;
    ters(&(liste1->bas));}//ters(..) fonksiyonu listenin sonunu degistirmedigi icin
    //listeyi fonksiyona sokmadan once listenin sonunu basa aldım 
    printf("listenin tersten siralanmis hali:\n");
    liste_yaz(liste1);

	printf("birinci liste:\n");
	liste_yaz(liste1);
	printf("ikinci liste:\n");
	liste_yaz(liste2);
	Listeptr liste3 = birlestir(liste1,liste2);
	printf("birinci ve ikinci listenin birlesmesiyle olusan ucuncu liste:\n");
	liste_yaz(liste3);

	Elemanptr aranilan = liste_ara(liste3,80);
	if(aranilan)
		printf("aradiginiz deger listede mevcut\n\n");
	else
		printf("aradiginiz deger listede yok\n\n");

	int kacinci = inci_eleman(liste3,80);
		printf("aradiginiz deger listede %d. sirada\n\n",kacinci);

	liste_basi_sil(liste3);
	printf("listenin basindan eleman silindi:\n");
	liste_yaz(liste3);

	liste_sonu_sil(liste3);
	printf("listenin sonundan eleman silindi:\n");
	liste_yaz(liste3);

	listeden_sil(liste3,liste3->bas->ileri->ileri);
	printf("listeden istediginiz eleman silindi:\n");
	liste_yaz(liste3);

	printf("listeden istediginiz degerdeki eleman silindi:\n");
	liste_eleman_sil(liste3,-50);
	liste_yaz(liste3);

	liste_sil(&liste3);
	if(!liste3)
		printf("liste silindi\n");

    return (EXIT_SUCCESS);
}
