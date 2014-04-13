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

float angulo_gl = 0.0f;
float dx=0.0f;
float dy=0.0f;


void desenhaVertex(float x, float y){
	float angulo = 0;
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


void semiCirculo(float xc, float yc, float radius){ //OK
    float agl = 0.0f;
    glBegin(GL_POLYGON);
        for(agl=0.0f;agl<=PI;agl+=.01){
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
	//criar um quadrado na origem, rotaciona e mover para o centro
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
		nx = x*cos(angulo)-y*sin(angulo);
		ny = x*sin(angulo)+y*cos(angulo);
		glVertex2f(dx+centro.x+nx,centro.y+ny);
		//vertice inferior direito
		x=+aresta/2.;
		y=-aresta/2.;
		nx = x*cos(angulo)-y*sin(angulo);
		ny = x*sin(angulo)+y*cos(angulo);
		glVertex2f(dx+centro.x+nx,centro.y+ny);
		//vertice inferior esquerdo
		x=-aresta/2.;
		y=-aresta/2.;
		nx = x*cos(angulo)-y*sin(angulo);
		ny = x*sin(angulo)+y*cos(angulo);
		glVertex2f(dx+centro.x+nx,centro.y+ny);
    glEnd();	
}

void bracoEsquerdo(point centro, float angulo){
	//criar um retangulo com o ponto superior direito na origem, rotacionar e mover para o centro
	//vertice superior esquerdo
	float arestaX = 0.1;
	float arestaY = 0.5;
	float x = -arestaX;
	float y = 0.0;
	float nx = x*cos(angulo)-y*sin(angulo);
	float ny = x*sin(angulo)+y*cos(angulo);
	glBegin(GL_POLYGON);
		glVertex2f(centro.x+nx,centro.y+ny);
		//vertice superior direito
		x=0.0f;
		y=0.0f;
		nx = x*cos(angulo)-y*sin(angulo);
		ny = x*sin(angulo)+y*cos(angulo);
		glVertex2f(centro.x+nx,centro.y+ny);
		//vertice inferior direito
		x=0.0f;
		y=-arestaY;
		nx = x*cos(angulo)-y*sin(angulo);
		ny = x*sin(angulo)+y*cos(angulo);
		glVertex2f(centro.x+nx,centro.y+ny);
		//vertice inferior esquerdo
		x=-arestaX;
		y=-arestaY;
		nx = x*cos(angulo)-y*sin(angulo);
		ny = x*sin(angulo)+y*cos(angulo);
		glVertex2f(centro.x+nx,centro.y+ny);
    glEnd();	
}

void bracoDireito(point centro, float angulo){
	//criar um retangulo com o ponto superior esquerdo na origem, rotacionar e mover para o centro
	//vertice superior esquerdo
	float arestaX = 0.1;
	float arestaY = 0.5;
	float x = 0.0;
	float y = 0.0;
	float nx = x*cos(angulo)-y*sin(angulo);
	float ny = x*sin(angulo)+y*cos(angulo);
	glBegin(GL_POLYGON);
		glVertex2f(centro.x+nx,centro.y+ny);
		//vertice superior direito
		x=arestaX;
		y=0.0f;
		nx = x*cos(angulo)-y*sin(angulo);
		ny = x*sin(angulo)+y*cos(angulo);
		glVertex2f(centro.x+nx,centro.y+ny);
		//vertice inferior direito
		x=arestaX;
		y=-arestaY;
		nx = x*cos(angulo)-y*sin(angulo);
		ny = x*sin(angulo)+y*cos(angulo);
		glVertex2f(centro.x+nx,centro.y+ny);
		//vertice inferior esquerdo
		x=0.0;
		y=-arestaY;
		nx = x*cos(angulo)-y*sin(angulo);
		ny = x*sin(angulo)+y*cos(angulo);
		glVertex2f(centro.x+nx,centro.y+ny);
    glEnd();	
}

void display(){
     glClearColor(0.0,0.0,0.0,0.0);
     glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(0,1,0);
     
     //cabeca
     semiCirculo(0,.35,.2);
     //corpo
     point centro = {0.0,.1};
     quadrado(centro,.4,0);
     centro.x =0.0;
     centro.y= -.1;
     quadrado(centro,.4,0);
     //pes
     centro.x =-0.1;
     centro.y= -.4;
     quadrado(centro,.09,0);
     centro.x =-0.1;
     centro.y= -.45;
     quadrado(centro,.09,0);
     
     centro.x =0.1;
     centro.y= -.4;
     quadrado(centro,.09,0);
     centro.x =0.1;
     centro.y= -.45;
     quadrado(centro,.09,0);
     //braco
     
     centro.x= -0.25;
     centro.y= 0.3f;
     bracoEsquerdo(centro, -angulo_gl);
     centro.x=-centro.x;
     bracoDireito (centro, angulo_gl);
	
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
        angulo_gl=PI/4.;
        break;
        case GLUT_KEY_LEFT:
        angulo_gl=0.0;
        break;
    }
	glutPostRedisplay();
}
