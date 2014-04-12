#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define XSIZE 600
#define YSIZE 600

#define RADIUS 120

#define EXEC 1

int min (int a, int b){return a<b?a:b;}
int max (int a, int b){return a>b?a:b;}


typedef struct {
    GLfloat r,g,b;
} RGB;

typedef struct {
    float a,b;
    int pxa, pxb;
} pairf;

//global variables
//int clickNumber=1;
//int firstTime = 1;
//int choice = RETA;
float point_size=1.0f;
//RGB* colors;
pairf lastCoords;
//pairf pastLastCoords;
//pairf pastPastLastCoords;
//int lastColor = 0;
//functions
pairf glConvertCoord(int x, int y, int xSize, int ySize);
pairf convertCoord(int x, int y, int xSize, int ySize);
//RGB* initRGB();
//void init();
void desenhaPonto();
void desenhaCirculo(int x0,int y0,int radius);
//void desenhaReta(pairf p1, pairf p2);
//void desenhaTriangulo(pairf p1, pairf p2, pairf p3);
//void Keyboard (unsigned char key, int x, int y) ;
void MouseInt (int botao, int estado, int x, int y);





int main( int argc, char *argv[ ] ) {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(XSIZE,YSIZE);
    glutInit(&argc, argv);
    glutCreateWindow("Cria um circulo");
    glutDisplayFunc(desenhaPonto);
    //glutKeyboardFunc(Keyboard);
    glutMouseFunc(MouseInt);
    glutMainLoop ();
    return 0;
}



void desenhaPonto(){

	printf("Clearing screen\n");
		glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(point_size);
        glBegin(GL_POINTS);
			desenhaCirculo(lastCoords.pxa,lastCoords.pxb,RADIUS);
		glEnd();
		glFlush();
}

//converte uma coordenada x,y da janela para x,y do openGL e atualiza as variaveis globais
pairf glConvertCoord(int x, int y, int xSize, int ySize){
    pairf p = convertCoord(x,y,xSize,ySize);
    lastCoords=p;
    return p;
}

//converte uma coordenada x,y da janela para x,y do openGL
pairf convertCoord(int x, int y, int xSize, int ySize){
    pairf p;
    p.pxa = x;
    p.pxb = y;
    x=x-xSize/2.0f;
    y=y-ySize/2.0f;
    p.a=((float)x)/((float)xSize/2.0f);
    p.b=-((float)y)/((float)ySize/2.0f);
    return p;
}



void desenhaCirculo(int x0,int y0,int radius){
    int x = 0;
    int y = radius;
    int delta = 2 - 2 * radius;
    int error = 0;

    while(y >= 0){
		pairf point = convertCoord(x0 + x, y0 + y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
        glVertex2f(point.a, point.b);
        point = convertCoord(x0 - x, y0 + y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
        glVertex2f(point.a, point.b);
        //glVertex2f(x0 - x, y0 + y);
        point = convertCoord(x0 + x, y0 - y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
        glVertex2f(point.a, point.b);
        //glVertex2f(x0 + x, y0 - y);
        point = convertCoord(x0 - x, y0 - y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
        glVertex2f(point.a, point.b);
        //glVertex2f(x0 - x, y0 - y);
        error = 2 * (delta + y) - 1;
        if(delta < 0 && error <= 0) { //faz os dois quadrantes
            ++x;
            delta += 2 * x + 1;
            continue;
        }
        
        error = 2 * (delta - x) - 1;
        
        if(delta > 0 && error > 0) {
            --y;
            delta += 1 - 2 * y;
            continue;
        }
        
        ++x;
        delta += 2 * (x - y);
        --y;
    }
}


//mouse listener
void MouseInt (int botao, int estado, int x, int y) {
    switch(botao) {
    case GLUT_LEFT_BUTTON:
        if(estado == GLUT_DOWN){
		//desenhaCirculo(x,y,RADIUS);
			glConvertCoord(x,y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
			break;
		}
	}
    glutPostRedisplay();
}


