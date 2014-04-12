#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define XSIZE 600
#define YSIZE 600

#define RAIOMENOR 120
#define RAIOMAIOR 180

#define EXEC 2
#define AUTOR FELIPE_C_Z

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
void desenhaElipse(int x0,int y0,int radioMenor, int raioMaior);
//void desenhaReta(pairf p1, pairf p2);
//void desenhaTriangulo(pairf p1, pairf p2, pairf p3);
//void Keyboard (unsigned char key, int x, int y) ;
void MouseInt (int botao, int estado, int x, int y);





int main( int argc, char *argv[ ] ) {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(XSIZE,YSIZE);
    glutInit(&argc, argv);
    glutCreateWindow("Cria uma elipse");
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
			desenhaElipse(lastCoords.pxa,lastCoords.pxb,RAIOMENOR,RAIOMAIOR);
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



void desenhaElipse(int x0,int y0,int raioMenor, int raioMaior){
    int a2 = raioMenor * raioMenor;
    int b2 = raioMaior * raioMaior;
    int fa2 = 4 * a2, fb2 = 4 * b2;
    int  x, y, sigma;

    /* first half */
    pairf point;
    for (x = 0, y = raioMaior, sigma = 2*b2+a2*(1-2*raioMaior); b2*x <= a2*y; x++){
		point = convertCoord(x0 + x, y0 + y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
		glVertex2f(point.a,point.b);
        //DrawPixel (x0 + x, y0 + y);
        point = convertCoord(x0 - x, y0 + y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
        glVertex2f(point.a,point.b);
        //DrawPixel (x0 - x, y0 + y);
        point = convertCoord(x0 + x, y0 - y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
        glVertex2f(point.a,point.b);
        //DrawPixel (x0 + x, y0 - y);
        point = convertCoord(x0 - x, y0 - y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
        glVertex2f(point.a,point.b);
        //DrawPixel (x0 - x, y0 - y);
        if (sigma >= 0)
        {
            sigma += fa2 * (1 - y);
            y--;
        }
        sigma += b2 * ((4 * x) + 6);
    }

    /* second half */
    for (x = raioMenor, y = 0, sigma = 2*a2+b2*(1-2*raioMenor); a2*y <= b2*x; y++)
    {
		point = convertCoord(x0 + x, y0 + y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
		glVertex2f(point.a,point.b);
        //DrawPixel (x0 + x, y0 + y);
        point = convertCoord(x0 - x, y0 + y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
        glVertex2f(point.a,point.b);
        //DrawPixel (x0 - x, y0 + y);
        point = convertCoord(x0 + x, y0 - y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
        glVertex2f(point.a,point.b);
        //DrawPixel (x0 + x, y0 - y);
        point = convertCoord(x0 - x, y0 - y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
        glVertex2f(point.a,point.b);
        //DrawPixel (x0 - x, y0 - y);
        //DrawPixel (x0 + x, y0 + y);
        //DrawPixel (x0 - x, y0 + y);
        //DrawPixel (x0 + x, y0 - y);
        //DrawPixel (x0 - x, y0 - y);
        if (sigma >= 0)
        {
            sigma += fb2 * (1 - x);
            x--;
        }
        sigma += a2 * ((4 * y) + 6);
    }
}


//mouse listener
void MouseInt (int botao, int estado, int x, int y) {
    switch(botao) {
    case GLUT_LEFT_BUTTON:
        if(estado == GLUT_DOWN){
			glConvertCoord(x,y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
			break;
		}
	}
    glutPostRedisplay();
}



