#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265359



float angulo = 0.4f;
float dx=0.0f;
float dy=0.0f;


void desenhaVertex(float x, float y){
    float nx = dx + x*cos(angulo)-y*sin(angulo);
    float ny = dy + x*sin(angulo)+y*cos(angulo);
    glVertex2f(nx,ny);
}


void circulo(float xc, float yc, float radius){ //OK
    float agl = 0.0f;
    glBegin(GL_POLYGON);
        for(agl=0.0f;agl<=2*PI;agl+=.01){
            desenhaVertex(xc+radius*cos(agl),yc+radius*sin(agl));
        }
    glEnd();
}

void elipse(float xc, float yc, float raioMenor, float raioMaior){
    float agl = 0.0f;
    glBegin(GL_POLYGON);
        for(agl=0.0f;agl<=2*PI;agl+=.001){
            desenhaVertex(xc+raioMenor/2.*cos(agl),yc+raioMaior/2.*sin(agl));
        }
    glEnd();
}

void desenhaCaule(float a,float b, float c, float d){
    glBegin(GL_POLYGON);
    glVertex2f(a,b);
    glVertex2f(c,b);
    glVertex2f(c,d);
    glVertex2f(a,d);
    glEnd();
}

void display(){
     glClearColor(0.0,0.0,0.0,0.0);
     glClear(GL_COLOR_BUFFER_BIT);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();

     glColor3f(0.,1.,0.);
     desenhaCaule(-.05,.05,.05,-1);

     glColor3f(1.,1.,1.);
     //ṕetala 1
     elipse(0.0,.4,.25,.5);
     //petala 2
     glRotatef(-45,0,0,1);
     elipse(0.0,.4,.25,.5);

     //petala 3
     glRotatef(-45,0,0,1);
     elipse(0.0,.4,.25,.5);
     //petala 4
     glRotatef(-45,0,0,1);
     elipse(0.0,.4,.25,.5);
     //petala 5
     glRotatef(-45,0,0,1);
     elipse(0.0,.4,.25,.5);
     //petala 6
     glRotatef(-45,0,0,1);
     elipse(0.0,.4,.25,.5);
     //petala 7
     glRotatef(-45,0,0,1);
     elipse(0.0,.4,.25,.5);
     //petala 8
     glRotatef(-45,0,0,1);
     elipse(0.0,.4,.25,.5);

     // centro
     glColor3f(1.0,1.0,0.0);//amarelo
     circulo(0.0,.0,.3);

     glFlush();
 }

void Keyboard (int key, int x, int y) ;

int main(int argc, char *argv[]){
     glutInit(&argc,argv);
     glutCreateWindow("Translacao");
     glutDisplayFunc(display);
     glutSpecialFunc(Keyboard);
     glutMainLoop();
     return 0;
}


//keyboard listener
void Keyboard (int key, int x, int y) {
    switch(key){
        case GLUT_KEY_RIGHT:
        angulo-=.1;
        break;
        case GLUT_KEY_LEFT:
        angulo+=.1;
        break;
    }
	glutPostRedisplay();
}


