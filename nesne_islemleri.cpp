#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include "nesne_islemleri.h"
	
int tusOku()
{
	int tus = 0;
	
	if(kbhit())
	{
		tus = getch();
		
		if (tus == ESC)
			exit(0);
	}
	
	return tus;
}

void askerAyarla(Asker * a, int x1, int y1, int x2, int y2, int renk, int hp)
{
	a->x1=x1;
	a->y1=y1;
	a->x2=x2;
	a->y2=y2;
	a->hp=hp;
	a->renk=renk;
}

void lazerAyarla(Lazer * l, int x1, int y1, int x2, int y2, int renk)
{
	l->x1=x1;
	l->y1=y1;
	l->x2=x2;
	l->y2=y2;
	l->renk=renk;
}

void dusmanAyarla(Dusman * d, int x, int y, int r, int renk, int hayattaMi)
{
	d->x=x;
	d->y=y;
	d->r=r;
	d->renk=renk;
	d->hayattaMi=hayattaMi;
}

