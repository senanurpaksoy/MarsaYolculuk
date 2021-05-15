#include <stdio.h>
#include <time.h>
#include <graphics.h>
#include "nesne_islemleri.h"
#include "eaDSDynamicArray.h"

#define MAX_ETAP			3
#define DUSMAN_SAYISI 		13
#define WIDTH				1200
#define HEIGHT				700
#define ETAP_GECIS_PUANI	50



// C'de dinamik dizi için yazýlmýþ bir kütüphane için gerekli 3 fonksiyon
void * lazerCreateAndCopy(const void * data)
{
	return (void *)data;
}

int lazerCompare(const void * p1, const void * p2)
{
	return 0;
}

void lazerClear(void * a)
{
	free(a);
}

void kurulum(Asker * a, eaDSDynamicArray * l, Dusman * d)
{
	int i;
	
	srand(time(0));
	
	initwindow(WIDTH, HEIGHT);
	
	setcolor(RED);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, 5);
	outtextxy(110, 170, "     MARS'A YOLA ÇIKMAYA HAZIR MISINIZ? "); 
	settextstyle(COMPLEX_FONT, HORIZ_DIR,3);
	outtextxy(110, 280, "TEK YAPMANIZ GERKEN: GÖK TAÞLARINA ATEÞ ETMEK");
	outtextxy(110, 391, "DÝKKAT EDÝN GÖK TAÞLARINA DEÐERSENÝZ OYUNU KAYBEDERSÝNÝZ");
	outtextxy(110, 500, "<ESC> BASINCA OYUNDAN ÇIKAR. 5 sn SONRA OYUN BAÞLAYACAK");
	outtextxy(110, 600, "HAZIRLAYAN: SENANUR PAKSOY ");
	delay(5000);
	
	
	// dinamik dizinin init ediliþi.
	*l = eaDSDynamicArrayInit(lazerCreateAndCopy, lazerCompare, lazerClear);
	askerAyarla(a, 500, 600, 600, 675, 9, 3);
	
	for (i = 0; i < DUSMAN_SAYISI; i++)
		dusmanAyarla(&d[i], 0, 0, 0, 0, 0); // buradaki deðerler önemli deðil. önemli olan sondaki 0
}

void lazerleriGoster(eaDSDynamicArray lazerler)
{
	// Lazerleri ekranda göster ve hareketlendir
	for (size_t i = 0; i < eaDSDynamicArrayGetCount(lazerler); i++)// lazerler 0 ise yani yoksa buraya girmeyecek. 
	{
		Lazer * l = (Lazer *) eaDSDynamicArrayGetAddressFrom(lazerler, i);
		
		l->y1 -= 5;
		l->y2 -= 5;
		setcolor(l->renk);
		rectangle(l->x1, l->y1, l->x2, l->y2);
		
		if (l->y1 <= 0)
		{
			eaDSDynamicArrayRemoveAt(lazerler, i--);
			 
			continue;
		}
	}
}

void kurulum(Asker * a, eaDSDynamicArray * l, Dusman * d);
void lazerleriGoster(eaDSDynamicArray lazerler);

int main()
{   
    char p[10] = {4};
    char e[10] = {1};
	char s[10] = {0};
	int tus, a = 0, puan = 0, etap = 1, atesEdildi = 0 ;
	int sagsol = 0;
	Asker asker;
	eaDSDynamicArray lazerler; // dinamik dizi için referans
	Dusman dusmanlar[DUSMAN_SAYISI];
	
	kurulum(&asker, &lazerler, dusmanlar);
	
    while(1)
	{
		tus = tusOku();
		
		if (tus == SAG_OK) sagsol = 1;
		else if (tus == SOL_OK) sagsol = -1;
		
		if (sagsol == 1)
		{
			asker.x1 += 8;
			asker.x2 += 8;
		}
		else if (sagsol == -1)
		{
			asker.x1 -= 8;
			asker.x2 -= 8;
		}
		
		if (tus == Y_OK)
		{
			sagsol = 0; 
			
			Lazer * l = (Lazer *) malloc(sizeof(Lazer)); // yeni lazeri bellekten alma
			
			lazerAyarla(l, asker.x1 + 50 , asker.y1, asker.x2 - 60, asker.y2 - 65, rand() % 16);  
			
			eaDSDynamicArrayAdd(lazerler, l);
		}
		else if (tus == ESC)
		{
			break;
		}	
		
		// Askeri ekranda göster
        setcolor(asker.renk);
 	    rectangle(asker.x1, asker.y1, asker.x2, asker.y2);
 	    
 	    // Lazerleri göster ve hareketlendir
 	    lazerleriGoster(lazerler);
 	    
		// lazer dusmaný vurdu mu?
		for (size_t i = 0; i < eaDSDynamicArrayGetCount(lazerler); i++) // lazerler 0 ise yani yoksa buraya girmeyecek. 
		{
			Lazer * l = (Lazer *) eaDSDynamicArrayGetAddressFrom(lazerler, i);
			
			for (int j = 0; j < DUSMAN_SAYISI; j++)
			{
				if ((dusmanlar[j].hayattaMi == 1) && ((dusmanlar[j].x - l->x1) * (dusmanlar[j].x - l->x1) + (dusmanlar[j].y - l->y1) * (dusmanlar[j].y - l->y1) <= dusmanlar[j].r * dusmanlar[j].r))
				{
				    puan += 5;
				    itoa(puan, s, 10);
					dusmanlar[j].hayattaMi = 0;	
					eaDSDynamicArrayRemoveAt(lazerler, i--);
				    
		            
					if (puan / ETAP_GECIS_PUANI == etap)
					{
						etap++;
					    itoa(etap, e, 10);
					    
					    if (etap > MAX_ETAP)
					    { 
					        setcolor(RED);
					        settextstyle(COMPLEX_FONT, HORIZ_DIR, 5);
					    	outtextxy(270, 170, "      TEBRÝKLER!!  "); 
							outtextxy(270, 280, "   MARS'A ULAÞTINIZ!!! ");
							outtextxy(100, 100,"Puanýnýz:  "); 
							outtextxy(320, 100, s);
							outtextxy(100, 150,"ETAP:  ");
							outtextxy(220, 150, e);
							delay(3000);
							
							eaDSDynamicArrayClear(lazerler); // dinamik dizinin silinmesi
							closegraph();
							exit(0);
						}
					}
					
					break;
				}	
			}
		}
		
		for (int i = 0; i < DUSMAN_SAYISI; i++)
		{
			if (((rand() % 35) == 5) && (dusmanlar[i].hayattaMi == 0))
			{
				dusmanAyarla(&dusmanlar[i], rand()%1000 + 100, rand()%100, 30, 10, 1);	
			}
			else if (dusmanlar[i].hayattaMi == 1)
			{
				dusmanlar[i].y += etap;
				setcolor(dusmanlar[i].renk);
			    circle(dusmanlar[i].x, dusmanlar[i].y, dusmanlar[i].r);
			    
			
				// Düþmanlarýn askere deðip deðmediðini anlýyoruz.
				if ((dusmanlar[i].x >= asker.x1) && (dusmanlar[i].x <= asker.x2) && (dusmanlar[i].y >= asker.y1) && (dusmanlar[i].y <= asker.y2))
				{
					asker.hp--;
					itoa(asker.hp, p, 10);
					dusmanlar[i].hayattaMi = 0;
					
					if (asker.hp == 0)
					{
						setcolor(RED);
					    settextstyle(COMPLEX_FONT, HORIZ_DIR, 5);
						outtextxy(270, 170, "    MARS'A ULAÞAMADINIZ!!  "); 
						outtextxy(270, 280, "       TEKRAR DENEYÝN!!! ");
						outtextxy(100, 100,"Puanýnýz:  ");
						outtextxy(320, 100, s);
						outtextxy(100, 150,"ETAP: ");
						outtextxy(220, 150, e);
						delay(3000);
						
						eaDSDynamicArrayClear(lazerler); // dinamik dizinin silinmesi
						closegraph();
						exit(0);
					}
				}
				
				// Duþmanlar alttaki sýnýrý geçene kadar oluþuyor
				if (dusmanlar[i].y >= HEIGHT)
				{
					dusmanAyarla(&dusmanlar[i], rand() % 1000 + 100, rand()%100, 30, 10, 1);
				}
			}
		}
	
		outtextxy(100, 100, "Puan :  ");
		outtextxy(180, 100, s);
		outtextxy(100, 160, "Etap :  ");
		outtextxy(200, 160, e);
		outtextxy(100, 220, "hp :  ");
	    outtextxy(180, 220, p);

		delay(10);
		cleardevice();
	}
	
	eaDSDynamicArrayClear(lazerler); // dinamik dizinin silinmesi
	closegraph();
	
    return 0;
}


