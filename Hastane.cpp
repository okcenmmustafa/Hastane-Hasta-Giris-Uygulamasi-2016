#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "string.h"
struct Hasta{
	int no;
	char ad[25];
	int yas;
	char bilgi[50];
};
typedef struct Hasta hasta;

void hastaGiris();
void hastaSil();
void kayitEdit();
void listele();
void txtKaydet();
void yeniKayit();
void aramaYap();
int secimGir();

int main()
{	
	int secim;
	
		while((secim=secimGir())!=8)
		{system("cls");
			switch(secim)
			{
				case 1:hastaGiris();break;
				case 2:kayitEdit();break;
				case 3:yeniKayit();break;
				case 4:hastaSil();break;
				case 5:listele();break;
				case 6:aramaYap(); break;
				case 7:txtKaydet();break;
			}
		}
}
int secimGir()
{
	
	int menuSecim;
	printf("(\n Secimini yap\n\n"
		"1-Hasta Giris\n"
		"2-hesap guncelle\n"
		"3-yeni hesap ekle\n"
		"4-hesap sil\n"
		"5-Hastalari listele\n"
		"6-Arama Yap\n"
		"7.Txt kaydet\n"
		"8.Cikis\n  :)");
	scanf("%d",&menuSecim);
	return menuSecim;
}
void hastaGiris(){
	FILE *myPtr;
	int i;
	hasta bosHasta={0,"",0,""};
	if((myPtr=fopen("hastaTakip.dat","w"))==NULL)
	printf("Dosya olusturulamadi.\n");
	else
	{
		for(i=0;i<100;i++)
		{
			fwrite(&bosHasta,sizeof(hasta),1,myPtr);
		}
		fclose(myPtr);
	
	}
	if((myPtr=fopen("hastaTakip.dat","r+"))==NULL)
	printf("Dosya olusturulamadi.\n");
	else
	{
		printf("Hasta no gir (1-100 arasi deger)\n"
				"Veri girisini bitirmek icin 0 gir\n?");
		scanf("%d",&bosHasta.no);
		while(bosHasta.no!=0)
		{
			printf("Hasta adi giriniz.\n?");
				fflush(stdin);
			gets(bosHasta.ad);
			printf("Hasta yasini giriniz.\n?");
			scanf("%d",&bosHasta.yas);
			printf("Hasta bilgisi giriniz.\n?");
		 	fflush(stdin);
			gets(bosHasta.bilgi);
			fseek(myPtr,(bosHasta.no-1)*sizeof(hasta),SEEK_SET);
			fwrite(&bosHasta,sizeof(hasta),1,myPtr);
			printf("Hasta No gir.\n?");
			scanf("%d",&bosHasta.no);
		} fclose(myPtr);
	}
}

void aramaYap(){
	FILE *dosya;
	int no,k=0;
	hasta K;
	dosya=fopen("hastaTakip.dat","r");
	printf("Aranacak hasta no giriniz.\n?");
	scanf("%d",&no);
	while(!feof(dosya))
	{
		fread(&K,sizeof(hasta),1,dosya);
		k++;
	}
	rewind(dosya);
	if(no>k)
	{ printf("Isleminiz iptal edildi.\n[Girilen sayi hasta sayisindan buyuk.]\n");
		return;
	}
	fseek(dosya,(no-1)*sizeof(hasta),SEEK_SET);
	fread(&K,sizeof(hasta),1,dosya);
	if(K.no==0)
	printf("Giridiginiz numaraya ait hasta kaydi bulunmamaktadir.\n");
	else{
	
	printf("%-10s%-26s%-11s%10s\n\n","HesapNo","AD","YAS","Bilgi");
	printf("%-10d%-26s%-11d%10s\n",K.no,K.ad,K.yas,K.bilgi);}
	
	fclose(dosya);
	
}

void hastaSil(){
	FILE *dosya,*temp;
	hasta K={0,"",0,""};
	int no,i=1,j=0;
	dosya=fopen("hastaTakip.dat","r+");
	printf("Silinecek hastanin no giriniz.\n?");
	scanf("%d",&no);
	rewind(dosya);
	fseek(dosya,(no-1)*sizeof(hasta),SEEK_SET);
	fwrite(&K,sizeof(hasta),1,dosya);
fclose(dosya);	}
	

void kayitEdit(){
	FILE *dosya;
	int no,secim=0;
	hasta bosHasta={0,"",0,""};
	dosya=fopen("hastaTakip.dat","r+");
	printf("Guncellenecek hesap no gir[1-100]");
	scanf("%d",&no);
	fseek(dosya,(no-1)*sizeof(hasta),SEEK_SET);
	fread(&bosHasta,sizeof(hasta),1,dosya);
	if(bosHasta.no==0)
	printf("%d nolu hesap icin bilgi girilmemis.\n");
	else
	{
		printf("%-10d%-16s%-11d%20s\n",bosHasta.no,bosHasta.ad,bosHasta.yas,bosHasta.bilgi);
		printf("Adini degistirmek istiyor musunuz ?[1-evet 2- hayir]\n?");
		do {scanf("%d",&secim);
			if(secim==1 || secim==2)
			break;
			printf("Yanlis secim girdiniz.\nLutfen [1-2] tuslayiniz.\n?");
		}
		while(secim!=1 || secim!=2);
		
		if(secim==1)
		{
			fflush(stdin);
			gets(bosHasta.ad);
		}
		printf("Yasini istiyor musunuz ?[1-evet 2- hayir]\n?");
		do {scanf("%d",&secim);
			if(secim==1 || secim==2)
			break;
			printf("Yanlis secim girdiniz.\nLutfen [1-2] tuslayiniz.\n?");
		}
		while(secim!=1 || secim!=2);
		 if(secim==1)
		 
		{
			scanf("%d",&bosHasta.yas);
		}
		printf("Bilgisini degistirmek istiyor musunuz ?[1-evet 2- hayir]\n?");
		do {scanf("%d",&secim);
			if(secim==1 || secim==2)
			break;
			printf("Yanlis secim girdiniz.\nLutfen [1-2] tuslayiniz.\n?");
		}
		while(secim!=1 || secim!=2);
		 if(secim==1)
		{
			fflush(stdin);
			gets(bosHasta.bilgi);
		}
		fseek(dosya,(no-1)*sizeof(hasta),SEEK_SET);
		fwrite(&bosHasta,sizeof(hasta),1,dosya);
		
		
	} fclose(dosya);
}

void listele()
{
	FILE *dosya;
	hasta K={0,"",0,""};
	if((dosya=fopen("hastaTakip.dat","r"))==NULL)
		printf("Dosya acilamadi.\n");
	else{
	
	printf("%-10s%-26s%-11s%-10s\n\n","HesapNo","AD","YAS","Bilgi");
	while(!feof(dosya))
	{	
		fread(&K,sizeof(hasta),1,dosya);
		if(K.no!=0)
		printf("%-10d%-26s%-11d%-10s\n",K.no,K.ad,K.yas,K.bilgi);
	}
	}fclose(dosya);
	
getchar();	}

void yeniKayit(){
	FILE *dosya;
	dosya=fopen("hastaTakip.dat","r+");
	int no;
	hasta K={0,"",0,""};
	printf("Eklemek istediginiz kayit no giriniz.\n?");
	scanf("%d",&no);
	fseek(dosya,(no-1)*sizeof(hasta),SEEK_SET);
	fread(&K,sizeof(hasta),1,dosya);
	do
	{if(K.yas==0)
		break;
	else{printf("Giridiginiz Numara dolu Lutfen baska numara giriniz.\n?");
	scanf("%d",&no);
	fseek(dosya,(no-1)*sizeof(hasta),SEEK_SET);
	fread(&K,sizeof(hasta),1,dosya);
	}
	}while(1);
	fseek(dosya,(no-1)*sizeof(hasta),SEEK_SET);
	K.no=no;
	printf("Hasta adi giriniz.\n?");
			fflush(stdin);
			gets(K.ad);
			printf("Hasta yasini giriniz.\n?");
			scanf("%d",&K.yas);
			printf("Hasta bilgisi giriniz.\n?");
		 	fflush(stdin);
			gets(K.bilgi);
			fwrite(&K,sizeof(hasta),1,dosya);
			fclose(dosya);
}

void txtKaydet()
{	FILE *dosya;
	dosya=fopen("hastaTakip.dat","r");
	FILE *yazPtr;
	hasta hesapBilgi={0,"",0,""};
	if((yazPtr=fopen("hastalar.txt","w"))==NULL)
		printf("Dosya acilamadi.\n");
	else
	{
		fprintf(yazPtr,"%-10s%-26s%-11s%-10s\n","HesapNo","AD","YAS","Bilgi");
		while(!feof(dosya))
		{
			fread(&hesapBilgi,sizeof(hasta),1,dosya);
			if(hesapBilgi.no!=0)
			fprintf(yazPtr,"%-10d%-26s%-11d%-10s\n",hesapBilgi.no,hesapBilgi.ad,hesapBilgi.yas,hesapBilgi.bilgi);
		}fclose(yazPtr);
	}fclose(dosya);
}

