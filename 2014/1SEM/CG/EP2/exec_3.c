#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define XSIZE 600
#define YSIZE 600

#define EXEC 3

#define RETA        1
#define TRIANGULO   2
#define ESPESSURA   4
#define COR         8

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
int clickNumber=1;
int firstTime = 1;
int choice = RETA;
float point_size=1.0f;
RGB* colors;
pairf lastCoords;
pairf pastLastCoords;
pairf pastPastLastCoords;
int lastColor = 0;
//functions
pairf glConvertCoord(int x, int y, int xSize, int ySize);
pairf convertCoord(int x, int y, int xSize, int ySize);
RGB* initRGB();
void init();
void desenhaPonto();
void desenhaReta(pairf p1, pairf p2);
void desenhaTriangulo(pairf p1, pairf p2, pairf p3);
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

//converte uma coordenada x,y da janela para x,y do openGL e atualiza as variaveis globais
pairf glConvertCoord(int x, int y, int xSize, int ySize){
    pairf p = convertCoord(x,y,xSize,ySize);
    pastPastLastCoords = pastLastCoords;
    pastLastCoords=lastCoords;
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


//keyboard listener
void Keyboard (unsigned char key, int x, int y) {
    if(key>=48 && key<=58 && (choice & COR )==COR){//mudando a cor
        lastColor=key-48;
    } else if(key>=49 && key<=58 && (choice & ESPESSURA )==ESPESSURA){ //mudando a espessura
        point_size=(float)key-48.0f;
    } else {
		switch(key){
			case 'r':   //selecionado reta
			case 'R':
				if((choice & TRIANGULO)==TRIANGULO){
                    choice -=TRIANGULO;
                }
                choice=choice | RETA;
				printf("Selecionado reta\n");
				break;
			case 't':   //selecionado triangulo
			case 'T':
				if((choice & RETA) == RETA){
				    choice -= RETA;
				}
				choice=choice | TRIANGULO;
				printf("Selecionado triangulo\n");
				break;
            case 'e': //selecionado espessura
            case 'E':
                if((choice & COR) == COR){
                    choice -= COR;
                }
                choice = choice | ESPESSURA;
                printf("Selecionado espessura\n");
                break;
            case 'k': //selecionado cor
            case 'K':
                if((choice & ESPESSURA) == ESPESSURA){
                    choice -= ESPESSURA;
                }
                choice = choice | COR;
                printf("Selecionado cor\n");
                break;

		}
	}
	glutPostRedisplay();
}

//init variables
void init(){
    colors = initRGB();
    lastCoords = glConvertCoord(XSIZE/2.0,YSIZE/2.0,XSIZE,YSIZE);
    pastLastCoords=lastCoords;
    pastPastLastCoords=pastLastCoords;
}

//draw point
void desenhaPonto(){
	if(clickNumber==1){
		printf("Clearing screen\n");
		glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(point_size);
        glBegin(GL_POINTS);
        if((choice & RETA) == RETA){
			printf("desenhando nas coordenadas: (%.3f,%.3f) -> (%.3f, %.3f) com a cor (%.2f,%.2f,%.2f)\n",pastLastCoords.a,pastLastCoords.b,lastCoords.a,lastCoords.b,colors[lastColor].r,colors[lastColor].g,colors[lastColor].b);
            glColor3f(colors[lastColor].r,colors[lastColor].g,colors[lastColor].b);
            desenhaReta(pastLastCoords,lastCoords);
		} else if((choice & TRIANGULO) == TRIANGULO){
			printf("desenhando nas coordenadas: (%.3f,%.3f) -> (%.3f, %.3f) -> (%.3f, %.3f) com a cor (%.2f,%.2f,%.2f)\n",pastPastLastCoords.a,pastPastLastCoords.b,pastLastCoords.a,pastLastCoords.b,lastCoords.a,lastCoords.b,colors[lastColor].r,colors[lastColor].g,colors[lastColor].b);
			glColor3f(colors[lastColor].r,colors[lastColor].g,colors[lastColor].b);
			desenhaTriangulo(pastPastLastCoords,pastLastCoords,lastCoords);
		} else {
		    printf("Opcao desconhecida %d\n", choice);
		}
		glEnd();
    }
    glFlush();
}

//mouse listener
void MouseInt (int botao, int estado, int x, int y) {
    switch(botao) {
    case GLUT_LEFT_BUTTON:
        if(estado == GLUT_DOWN){
            glConvertCoord(x,y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
            if((choice & RETA )==RETA){
				clickNumber=(clickNumber+1)%2;
			} else {
				clickNumber=(clickNumber+1)%3;
			}
            firstTime=0;
        }
        break;
    }
    glutPostRedisplay();
}

// desenha reta de acordo com o algoritmo de bresenham
void desenhaReta(pairf p1, pairf p2){
    int dx = (p2.pxa-p1.pxa);
    int dy = (p2.pxb-p1.pxb);
    if(dx < 0){ //inverter pontos
        pairf tmp = p1;
        p1 = p2;
        p2 = tmp;
        dx = (p2.pxa-p1.pxa);
        dy = (p2.pxb-p1.pxb);
    }
    printf("\treta vai de %d,%d -> %d,%d. dx=%d, dy=%d\n",p1.pxa,p1.pxb,p2.pxa,p2.pxb,dx,dy);
    if(p2.pxa == p1.pxa){ //sem variação em x
        printf("Reta sem variacao em x\n");
        int idx = min(p1.pxb, p2.pxb);
        int maxIdx = max(p1.pxb,p2.pxb);
        do{
            pairf p = convertCoord(p1.pxa,idx++,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
            glVertex2f(p.a,p.b);
        } while(idx<maxIdx);
    } else if(p1.b==p2.b){ //sem variação em y
        printf("Reta sem variacao em y\n");
        int idx = min(p1.pxa, p2.pxa);
        int maxIdx = max(p1.pxa,p2.pxa);
        do{
            pairf p = convertCoord(idx++,p1.pxb,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
            glVertex2f(p.a,p.b);
        } while(idx<maxIdx);
    } else { //reta inclinada
        if(dy < 0){ // m < 0
            printf("m<0\n");

            if(abs(dy)>abs(dx)){ // m < -1
                printf("dy>dx\n");
                dy=abs(dy);
                int pk = 2*dx-dy; //p0
                int pk_ant;
                int x = p1.pxa;
                int y = p1.pxb;
                //desenha ponto inicial
                pairf p = convertCoord(x,y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
                glVertex2f(p.a,p.b);
                do{
                    y--;
                    if(pk>=0){
                        x++;
                    }
                    //atualiza pk para o proximo pk
                    pk_ant = pk;
                    pk = (pk<0 ? pk+2*dx : pk+2*dx-2*dy);

                    //desenha o ponto
                    pairf p = convertCoord(x,y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
                    glVertex2f(p.a,p.b);
                    //printf("pk=%d x=%d,y=%d\n",pk_ant,x,y);
                } while(y>p2.pxb);
            } else { // -1<= m < 0
                printf("dy<=dx\n");
                dy=abs(dy);
                int pk = 2*dy-dx; //p0
                int pk_ant;
                int x = p1.pxa;
                int y = p1.pxb;
                //desenha ponto inicial
                pairf p = convertCoord(x,y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
                glVertex2f(p.a,p.b);
                do{
                    x++;
                    if(pk>=0){
                        y--;
                    }
                    //atualiza pk para o proximo pk
                    pk_ant = pk;
                    pk = (pk<0 ? pk+2*dy : pk+2*dy-2*dx);

                    //desenha o ponto
                    pairf p = convertCoord(x,y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
                    glVertex2f(p.a,p.b);
                    //printf("pk=%d x=%d,y=%d\n",pk_ant,x,y);
                } while(x<p2.pxa);
            }
        } else if(dy > dx) { //m > 1
            printf("m>1\n");
            int pk = 2*dx-dy; //p0
            int pk_ant;
            int x = p1.pxa;
            int y = p1.pxb;
            //desenha ponto inicial
            pairf p = convertCoord(x,y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
            glVertex2f(p.a,p.b);
            do{
                y++;
                if(pk>=0){
                    x++;
                }
                //atualiza pk para o proximo pk
                pk_ant = pk;
                pk = (pk<0 ? pk+2*dx : pk+2*dx-2*dy);

                //desenha o ponto
                pairf p = convertCoord(x,y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
                glVertex2f(p.a,p.b);
                //printf("pk=%d x=%d,y=%d\n",pk_ant,x,y);
            } while(y<p2.pxb);
        } else {    // 0 < m <=1
            printf("0<m<=1\n");
            int pk = 2*dy-dx; //p0
            int pk_ant;
            int x = p1.pxa;
            int y = p1.pxb;
            //desenha ponto inicial
            pairf p = convertCoord(x,y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
            glVertex2f(p.a,p.b);
            do{
                x++;
                if(pk>=0){
                    y++;
                }
                //atualiza pk para o proximo pk
                pk_ant = pk;
                pk = (pk<0 ? pk+2*dy : pk+2*dy-2*dx);

                //desenha o ponto
                pairf p = convertCoord(x,y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
                glVertex2f(p.a,p.b);
                //printf("pk=%d x=%d,y=%d\n",pk_ant,x,y);
            } while(x<p2.pxa);
        }
    }
}

//desenha um triangulo
void desenhaTriangulo(pairf p1, pairf p2, pairf p3){
    desenhaReta(p1,p2);
    desenhaReta(p2,p3);
    desenhaReta(p3,p1);
}


