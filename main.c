#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 20

// Koordinate za pravljenje kutije
GLfloat Y = 0.01;
GLfloat NY = -0.01;
GLfloat x = 0.1;
GLfloat nx = -0.1;
GLfloat y = 0.01;
GLfloat ny = -0.01;
GLfloat z = 0.1;
GLfloat nz = -0.1;

// Promenljiva uz pomoc uz pomoc koje povecavamo koordinate duz y ose tako da kutije ne ulaze jedna u drugu, nego jedna na drugu
GLfloat k = 0;

// Promenljiva za kretanje levo desno. Ako je vrednost 1 ide desno, a ako je 0 kutija ide levo
GLint t=0;

// Promenljiva za kretanje kutije dole. Ako je vrednost 1 kutija ide na dole, ako je 0 ne ide.
GLint p=0;

// Promenljiva koja nam sluzi kao brojac koliko je kutija napravljeno
int i = 0;

// Struktura u koju smestamo koordinate kutije
struct Koordinate{
    GLfloat a;
    GLfloat b;
    GLfloat c;
    GLfloat d;
    GLfloat e;
    GLfloat f;
} ;

// Niz tipa Koordinate u koji smestamo sve kutije koje napravimo
struct Koordinate* niz;

int animation_ongoing;
void on_display(void);
void draw(GLfloat x,GLfloat y,GLfloat z,GLfloat nx,GLfloat ny,GLfloat nz);
void on_timer(int value);
void graphicsInit();
void drawScore() ;
void keyboard(unsigned char key, int x, int y);

int main(int argc, char ** argv)
{
    // Kreiranje prostora za niz koordinata kutija
    niz = malloc(50 * sizeof(struct Koordinate));
    if(niz == NULL){
        fprintf(stderr, " Greska u alokaciji memorije");
        exit(1);
    }

    // Inicijalizuje se glut

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // Funkcija za kreiranje prozora i iscrtavanje
    graphicsInit();

    // Funkcija koja se poziva nakon pritiska na taster tastature
    glutKeyboardFunc(keyboard);

    // Program ulazi u glavnu petlju
    glutMainLoop();

    free(niz);
    return 0;
}


void on_display(void)
{

    // Brise se prethodni sadrzaj prozora
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Postavljamo crvenu boju za ispis skora igraca
    glColor3f(1,0,0);

    // Ispisujemo trenutni skor
    drawScore();

    // Crta se kutija koja se krece
    draw(x,y,z,nx,ny,nz);

    // U ovoj petlji se crtaju vec polozene kutije
    for(int j = 0; j <= i;j++){
        if(j>1) {
            // Ovo je provera da li je kutija spustena na kutiju ili pored nje, ako je pored izlazi se iz igre
            if (fabsf((niz[j - 2].a - niz[j-1].a)) > 0.2 && fabsf((niz[j - 2].d - niz[j-1].d)) > 0.2) {
                exit(1);
            }
            else {
                draw(niz[j].a, niz[j].b, niz[j].c, niz[j].d, niz[j].e, niz[j].f);
            }
        }

        //  Za prvu kutiju ne treba proveravati udaljenost, zbog toga idemo u else granu
        else {
                draw(niz[j].a, niz[j].b, niz[j].c, niz[j].d, niz[j].e, niz[j].f);
        }

    }

     // Nova slika se salje na ekran
    glutSwapBuffers();

}

void graphicsInit() {
    // Kreira se prozor
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Build a Tower");

    // Pozivanje callback funkcije
    glutDisplayFunc(on_display);

    // Postavlja se boja pozadine
    glClearColor(0.3, 0.5, 0.5, 0.3);
}

void draw(GLfloat x,GLfloat y,GLfloat z,GLfloat nx,GLfloat ny,GLfloat nz){

    // Crtanje kutije
    glBegin(GL_QUADS);

    // Gornji deo
    glColor3f(1, 1, 0);
    glVertex3f(x, y, nz);
    glVertex3f(nx, y, nz);
    glVertex3f(nx, y, z);
    glVertex3f(x, y, z);

    // Donji deo
    glColor3f(1, 1, 0);
    glVertex3f(x, ny, z);
    glVertex3f(nx, ny, z);
    glVertex3f(nx, ny, nz);
    glVertex3f(x, ny, nz);

    // Napred
    glColor3f(1, 1, 0);
    glVertex3f(x, y, z);
    glVertex3f(nx, y, z);
    glVertex3f(nx, ny, z);
    glVertex3f(x, ny, z);

    // Nazad
    glColor3f(1, 1, 0);
    glVertex3f(x, ny, nz);
    glVertex3f(nx, ny, nz);
    glVertex3f(nx, y, nz);
    glVertex3f(x, y, nz);

    // Levo
    glColor3f(1, 1, 0);
    glVertex3f(nx, y, z);
    glVertex3f(nx, y, nz);
    glVertex3f(nx, ny, nz);
    glVertex3f(nx, ny, z);

    // Desno
    glColor3f(1, 1, 0);
    glVertex3f(x, y, nz);
    glVertex3f(x, y, z);
    glVertex3f(x, ny, z);
    glVertex3f(x, ny, nz);

    glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
        {

            // Pokretanje kutije nadole
        case 'd':
        case 'D':
            p = 1;

            if (!animation_ongoing) {
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                animation_ongoing = 1;
                }
                break;

            // Izlaz
        case 'q':
        case 'Q':
            exit(0);

        case 's':
        case 'S':
            // Pokrece se igra
            if (!animation_ongoing) {
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                animation_ongoing = 1;
            }
            break;

    }

}
void drawScore() {

    // Deklaracija stringa u koji smestamo skor igraca
    char c[13];

    // Smestanje skora u promenljivu c, za svaku kutiju se dobija 100 poena
    snprintf(c,13,"SCORE : %d  ",i*100);

    // Funkcija kojoj prosledjujemo koordinate gde zelimo da se nalazi nas ispis
    glRasterPos3f(0.4, 0.6, 0.2);

    // U petlji prolazimo kroz string i ispisujemo trenutni skor igraca uz pomoc funkcije glutBitmapCharacter()
    for (int b=0; b < 13; b++)
    {

        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[b]);
    }


}
void on_timer(int value)
{

     // Proverava se da li callback dolazi od odgovarajuceg tajmera

    if (value != TIMER_ID)
        return;

    // Kretanje kutije desno
    if(x<=0.5 && t == 1 && p==0) {
        if(x>=0.499 && x<= 0.501)
            t=0;
        x += 0.01;
        nx += 0.01;
    }
    // Kretanje kutije levo
    if(x>=-0.5 && t == 0 && p == 0) {
        if (x <= -0.499 && x>= -0.501)
            t = 1;
        x -= 0.01;
        nx -= 0.01;
    }

    // Kretanje kutije nadole
    if (y > (-1+k) && ny > (-1 + k)  && p == 1 ) {
        y -= 0.01;
        ny -= 0.01;
    }
    else {
    // Smestanje koordinata kutija u niz
        niz[i].a = x;
        niz[i].b = y;
        niz[i].c = z;
        niz[i].d = nx;
        niz[i].e = ny;
        niz[i].f = nz;

    // Za svaku kutiju povecavamo k i dodajemo ga na y koordinatu, da bi kutije "nalegle" jedna na drugu prilikom spustanja
        if (ny < -0.98 + k && y < -0.98 + k){
            i++;
            k = k + 0.02;

        }

        // Postavljanje p na 0 da kutija ne bi isla nadole dok ne pritisnemo 'd'
        p=0;

        // Vracanje pocetnih vrednosti koordinata za kutiju
        y =Y;
        ny = NY;

    }

    // Forsira se ponovno iscrtavanje prozora.
    glutPostRedisplay();

    // Po potrebi se ponovo postavlja tajmer.
    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}



