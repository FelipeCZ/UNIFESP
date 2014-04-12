#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define XSIZE 400
#define YSIZE 400

typedef struct {
    GLfloat r,g,b;
} RGB;

typedef struct {
    float a,b;
} pairf;

//global variables
RGB* colors;
pairf lastCoords;
int lastColor = 0;
//functions
pairf glConvertCoord(int x, int y, int xSize, int ySize);
RGB* initRGB();
void init();
void desenhaPonto();
void Keyboard (unsigned char key, int x, int y) ;
void MouseInt (int botao, int estado, int x, int y);


int main( int argc, char *argv[ ] ) {
    init();
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(XSIZE,YSIZE);
    glutInit(&argc, argv);
    glutCreateWindow("Cria um triangulo");
    glutDisplayFunc(desenhaPonto);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(MouseInt);
    glutMainLoop ();
    return 0;
}



RGB* initRGB(){
    RGB* colors = (RGB*)malloc(10*sizeof(RGB));
    //azul
    colors[0].r=0.0f;
    colors[0].g=0.0f;
    colors[0].b=1.0f;
    //vermelho
    colors[1].r=1.0f;
    colors[1].g=0.0f;
    colors[1].b=0.0f;
    //verde
    colors[2].r=0.0f;
    colors[2].g=1.0f;
    colors[2].b=0.0f;
    //branco
    colors[3].r=1.0f;
    colors[3].g=1.0f;
    colors[3].b=1.0f;
    //preto
    colors[4].r=0.0f;
    colors[4].g=0.0f;
    colors[4].b=0.0f;
    //amarelo
    colors[5].r=1.0f;
    colors[5].g=1.0f;
    colors[5].b=0.0f;
    //rosa
    colors[6].r=1.0f;
    colors[6].g=0.0f;
    colors[6].b=1.0f;
    //verde agua
    colors[7].r=0.0f;
    colors[7].g=1.0f;
    colors[7].b=1.0f;
    //cinza escuro
    colors[8].r=0.6666f;
    colors[8].g=0.6666f;
    colors[8].b=0.6666f;
    //cinza claro
    colors[9].r=0.3333f;
    colors[9].g=0.3333f;
    colors[9].b=0.3333f;
    return colors;
}


//implementação das funcoes auxiliares

//converte uma coordenada x,y da janela para x,y do openGL
pairf glConvertCoord(int x, int y, int xSize, int ySize){
    pairf p;
    x=x-xSize/2.0f;
    y=y-ySize/2.0f;
    p.a=((float)x)/((float)xSize/2.0f);
    p.b=-((float)y)/((float)ySize/2.0f);
    lastCoords=p;
    return p;
}
//keyboard listener
void Keyboard (unsigned char key, int x, int y) {
    if(key>=48 && key<=58)
        lastColor=key-48;
    glutPostRedisplay();
}

//init variables
void init(){
    colors = initRGB();
    lastCoords = glConvertCoord(XSIZE/2.0,YSIZE/2.0,XSIZE,YSIZE);
}

//draw point
void desenhaPonto(){
    printf("desenhando nas coordenadas: (%.3f,%.3f) com a cor (%.2f,%.2f,%.2f)\n",lastCoords.a,lastCoords.b,colors[lastColor].r,colors[lastColor].g,colors[lastColor].b);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glColor3f(colors[lastColor].r,colors[lastColor].g,colors[lastColor].b);
        glVertex2f(lastCoords.a,lastCoords.b);
    glEnd();
    glFlush();
}

//mouse listener
void MouseInt (int botao, int estado, int x, int y) {
    switch(botao) {
    case GLUT_LEFT_BUTTON:
        if(estado == GLUT_DOWN){
            glConvertCoord(x,y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
        }
        break;
    }
    glutPostRedisplay();
}

