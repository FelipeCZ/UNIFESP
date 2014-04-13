#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265359

typedef struct {
	float x, y;
} point;

typedef struct pl {
	point p;
	struct pl* prox;
} pointList;

pointList* append(pointList* list, float x, float y){
	pointList* next = (pointList*)malloc(sizeof(pointList));
	next->p.x=x;
	next->p.y=y;
	next->prox=NULL;
	if(list==NULL){
		list=next;
	} else {
		pointList* atual = list;
		while(atual->prox!=NULL){
			atual=atual->prox;
		}
		atual->prox=next;
	}
	return list;
}

void deleteObject(pointList* list){
	if(list!=NULL){
		deleteObject(list->prox);
		free(list);
	}
}

float angulo = 0.0f;
float anguloRoda = 0.0f;
float dx=0.0f;
float dy=0.0f;


void desenhaVertex(float x, float y){
    float nx = x*cos(angulo)-y*sin(angulo);
    float ny = x*sin(angulo)+y*cos(angulo);
    glVertex2f(nx,ny);
}

void circulo(float xc, float yc, float radius){ //OK
    float agl = 0.0f;
    glBegin(GL_POLYGON);
        for(agl=0.0f;agl<=2*PI;agl+=.01){
            desenhaVertex(dx+xc+radius*cos(agl),dy+yc+radius*sin(agl));
        }
    glEnd();
}

void elipse(float xc, float yc, float raioMenor, float raioMaior){
    float agl = 0.0f;
    glBegin(GL_POLYGON);
        for(agl=0.0f;agl<=2*PI;agl+=.001){
            desenhaVertex(dx+xc+raioMenor/2.*cos(agl),dy+yc+raioMaior/2.*sin(agl));
        }
    glEnd();
}

void quadrado(point centro, float aresta, float angulo){
	//criar um quadrado na origem, rotaciona o angulo da roda e mover para o centro
	//vertice superior esquerdo
	float x = -aresta/2.;
	float y = aresta/2.;
	float nx = x*cos(angulo)-y*sin(angulo);
	float ny = x*sin(angulo)+y*cos(angulo);
	glBegin(GL_POLYGON);
		glVertex2f(dx+centro.x+nx,centro.y+ny);
		//vertice superior direito
		x=+aresta/2;
		y=+aresta/2;
		nx = x*cos(anguloRoda)-y*sin(anguloRoda);
		ny = x*sin(anguloRoda)+y*cos(anguloRoda);
		glVertex2f(dx+centro.x+nx,centro.y+ny);
		//vertice inferior direito
		x=+aresta/2.;
		y=-aresta/2.;
		nx = x*cos(anguloRoda)-y*sin(anguloRoda);
		ny = x*sin(anguloRoda)+y*cos(anguloRoda);
		glVertex2f(dx+centro.x+nx,centro.y+ny);
		//vertice inferior esquerdo
		x=-aresta/2.;
		y=-aresta/2.;
		nx = x*cos(anguloRoda)-y*sin(anguloRoda);
		ny = x*sin(anguloRoda)+y*cos(anguloRoda);
		glVertex2f(dx+centro.x+nx,centro.y+ny);
    glEnd();	
}

void display(){
     glClearColor(0.0,0.0,0.0,0.0);
     glClear(GL_COLOR_BUFFER_BIT);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
	//desenha a rua
     glColor3f(.5,.5,.5);
     glBegin(GL_POLYGON);
		desenhaVertex(-2,-.2);
		desenhaVertex(2,-.2);
		desenhaVertex(2,-2);
		desenhaVertex(-2,-2);
     glEnd();
     
     //desenha o carro
     glColor3f(1.,0.,0.);
     elipse(0.0,0.,0.7,0.3);
     elipse(0.0,0.13,0.3,0.2);
     //desenha as rodas
     glColor3f(.9,0.9,0.9);
     circulo(-.2,-0.13,0.08);//centro em -0.2,-0.13, raio = 0.08
     circulo( .2,-0.13,0.08);//centro em  0.2,-0.13, raio = 0.08
     glColor3f(.0,0.0,0.0);
     point centro={-0.2,-0.13};
     float aresta = 0.06;
     quadrado(centro, aresta,anguloRoda);
     centro.x=0.2;
     centro.y=-0.13;
     quadrado(centro, aresta,anguloRoda);
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
        dx=dx+.05/2.;
        anguloRoda-=.29/2.;
        break;
        case GLUT_KEY_LEFT:
        dx=dx-.05/2.;
        anguloRoda+=.29/2.;
        break;
    }
	glutPostRedisplay();
}
