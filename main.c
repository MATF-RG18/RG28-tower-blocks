#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void on_display(void);
void graphicsInit();

int main(int argc, char ** argv)
{   // Inicijalizuje se glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    graphicsInit();

    // Program ulazi u glavnu petlju
    glutMainLoop();

    return 0;
}


void on_display(void)
{
    // Brise se prethodni sadrzaj prozora
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    glClearColor(0.3, 0.5, 0.5, 0.3);
}


