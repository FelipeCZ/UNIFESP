/**
 * Discentes:									RA:
 * 				Salety Baracho							63611
 * 				Jade Mendes								?????
 * 				Felipe Zanichelli						61561
 *
 * 	Jogo:
 * 				BOLICHE
 *
 * */



 /**
  * Para compilar pela linha de comando no linux:
  * 	gcc -o nome_do_programa codigo_fonte.c  -lglut -lGLU -lGL -W -w -lm
  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(4.0, 2.0, 1.0,   //posição da câmera
              0.0, 0.0, 0.0,   //para onde a câmera aponta
              0.0, 1.0, 0.0);  //vetor view-up

    glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade
    //glOrtho(-1.0, 1.0, -1.0, 1.0, 2.0, 8.0); //define uma projeção ortogonal
    gluPerspective(90.0, 1.0, 2.0, 8.0); //define uma projeção perspectiva
    //glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 8.0); //define uma projeção perspectiva simétrica
    //glFrustum(-2.0, 1.0, -1.0, 2.0, 2.0, 8.0); //define uma projeção perspectiva obliqua
    glViewport(0, 0, 500, 500);


    //imprime as matrized GL_PROJECTION e GL_MODELVIEW
    printf("M_ortho = \n");
    float matrix[16];
    int i,j;
    glGetFloatv(GL_PROJECTION_MATRIX,matrix);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%f ",matrix[i + j * 4]);
        }
        printf("\n");
    }
    printf("\n");

    printf("\n\nM_wc,vc = \n");
    glGetFloatv(GL_MODELVIEW_MATRIX,matrix);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%f ",matrix[i + j * 4]);
        }
        printf("\n");
    }
    printf("\n");
}

void cube(){
     glColor3f(1.0,0.0,0.0);
     glBegin(GL_POLYGON);
        glVertex3f(-0.5,-0.5,0.5);
        glVertex3f(0.5,-0.5,0.5);
        glVertex3f(0.5,0.5,0.5);
        glVertex3f(-0.5,0.5,0.5);
     glEnd();
     glColor3f(0.0,1.0,0.0);
     glBegin(GL_POLYGON);
        glVertex3f(0.5,0.5,0.5);
        glVertex3f(0.5,-0.5,0.5);
        glVertex3f(0.5,-0.5,-0.5);
        glVertex3f(0.5,0.5,-0.5);
     glEnd();
     glColor3f(0.0,0.0,1.0);
     glBegin(GL_POLYGON);
        glVertex3f(0.5,-0.5,0.5);
        glVertex3f(-0.5,-0.5,0.5);
        glVertex3f(-0.5,-0.5,-0.5);
        glVertex3f(0.5,-0.5,-0.5);
     glEnd();
     glColor3f(1.0,1.0,0.0);
     glBegin(GL_POLYGON);
        glVertex3f(-0.5,0.5,0.5);
        glVertex3f(0.5,0.5,0.5);
        glVertex3f(0.5,0.5,-0.5);
        glVertex3f(-0.5,0.5,-0.5);
     glEnd();
     glColor3f(0.0,1.0,1.0);
     glBegin(GL_POLYGON);
        glVertex3f(-0.5,-0.5,-0.5);
        glVertex3f(-0.5,0.5,-0.5);
        glVertex3f(0.5,0.5,-0.5);
        glVertex3f(0.5,-0.5,-0.5);
     glEnd();
     glColor3f(1.0,1.0,1.0);
     glBegin(GL_POLYGON);
        glVertex3f(-0.5,0.5,-0.5);
        glVertex3f(-0.5,-0.5,-0.5);
        glVertex3f(-0.5,-0.5,0.5);
        glVertex3f(-0.5,0.5,0.5);
     glEnd();
}

void displayFunc() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
        glMatrixMode(GL_MODELVIEW); //define que a matrix é a de modelo
        //desenhar os objetos aqui:

        //[TODO] PINO
        //[TODO] PISTA
        //[TODO] BOLA

        cube(); //desenha um cubo
        glFlush(); //força o desenho das primitivas
        //glutSwapBuffers();
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(500,500);
	glutCreateWindow("Viewing 3D - Projecao Perspectiva");
	glutDisplayFunc(displayFunc);
	//glutTimerFunc(60,timerFunc,1);
	init();
	glutMainLoop();
	return 0;
}

