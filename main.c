#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>


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

static int animation_ongoing;
void on_display(void);
void draw(GLfloat x,GLfloat y,GLfloat z,GLfloat nx,GLfloat ny,GLfloat nz);
static void on_timer(int value);
void graphicsInit();
void keyboard(unsigned char key, int x, int y);

int main(int argc, char ** argv)
{
    // Kreiranje prostora za niz
    niz = malloc(100 * sizeof(struct Koordinate));
    if(niz == NULL){
        exit(1);
    }

    // Inicijalizuje se glut

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    graphicsInit();
    glutKeyboardFunc(keyboard);

    // Program ulazi u glavnu petlju
    glutMainLoop();

    return 0;
}


void on_display(void)
{

    // Brise se prethodni sadrzaj prozora
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Crta se kutija koja se krece
    draw(x,y,z,nx,ny,nz);

    // U ovoj petlji se crtaju vec polozene kutije
    for(int j = 0; j <= i;j++){
        if(j>1) {
                    // Ovo je provera da li je kutija spustena na kutiju ili pored nje, ako je pored izlazi se iz igre
            if (fabsf((niz[j - 2].a - niz[j-1].a)) > 0.2 && fabsf((niz[j - 2].d - niz[j-1].d)) > 0.2) {
                exit(1);
            } else {
                draw(niz[j].a, niz[j].b, niz[j].c, niz[j].d, niz[j].e, niz[j].f);
            }
        }
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

    // Pozivanje callback funkcije i postavljanje boje pozadine
    glutDisplayFunc(on_display);

    // Pstavlja se boja pozadine
    glClearColor(0.3, 0.5, 0.5, 0.3);
}

void draw(GLfloat x,GLfloat y,GLfloat z,GLfloat nx,GLfloat ny,GLfloat nz){

    // Crtanje kutije
    glBegin(GL_QUADS);

    // Gornji deo
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(x, y, nz);
    glVertex3f(nx, y, nz);
    glVertex3f(nx, y, z);
    glVertex3f(x, y, z);

    // Donji deo
    glColor3f(1.0f, 0.5f, 0.0f);
    glVertex3f(x, ny, z);
    glVertex3f(nx, ny, z);
    glVertex3f(nx, ny, nz);
    glVertex3f(x, ny, nz);

    // Napred
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(x, y, z);
    glVertex3f(nx, y, z);
    glVertex3f(nx, ny, z);
    glVertex3f(x, ny, z);

    // Nazad
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(x, ny, nz);
    glVertex3f(nx, ny, nz);
    glVertex3f(nx, y, nz);
    glVertex3f(x, y, nz);

    // Levo
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(nx, y, z);
    glVertex3f(nx, y, nz);
    glVertex3f(nx, ny, nz);
    glVertex3f(nx, ny, z);

    // Desno
    glColor3f(0.3f, 0.4f, 0.2f);
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

            // Pustanje kutije na dole
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
            // Pokrece se animacija.
            if (!animation_ongoing) {
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                animation_ongoing = 1;
            }
            break;

    }
    glutPostRedisplay();
}

static void on_timer(int value)
{

     // Proverava se da li callback dolazi od odgovarajuceg tajmera.

    if (value != TIMER_ID)
        return;

    // Kretanje kutije desno.
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
        if (i < 50 && ny < -0.98 + k && y < -0.98 + k){
            i++;
            k = k + 0.02;

        }

        // Postavljanje p na 0 da kutija ne bi isla na dole dok ne pritisnemo 'd'
        p=0;

        // Vracanje pocetnih vrednosti za kutiju
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



