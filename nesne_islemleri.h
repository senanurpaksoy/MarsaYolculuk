#ifndef _NESNE_ISLEMLERI
#define _NESNE_ISLEMLERI

#define ESC 	27
#define	SAG_OK 	77
#define SOL_OK 	75 
#define Y_OK	72
#define A_OK	80

struct Asker {
	int x1;
	int y1;
	int x2;
	int y2;
	int renk;
	int hp;
};
 
struct Lazer {
	int x1;
	int y1;
	int x2;
	int y2;
	int renk;	
}; 

struct Dusman {
	int x;
	int y;
	int r;
	int renk;	
	int hayattaMi;
};

int tusOku();
void askerAyarla(Asker * d, int x1, int y1, int x2, int y2, int renk, int hp);
void lazerAyarla(Lazer * l, int x1, int y1, int x2, int y2, int renk);
void dusmanAyarla(Dusman * d, int x, int y, int r, int renk, int hayattaMi);

#endif
