#include "GL/glut.h"


#define TIMERFUNC 1

/*
#define SISTEMA_DE_COORDENADAS gluOrtho2D
#define AREA_VISIVEL glViewport
#define INICIAR_DESENHO glBeginjuG2u
#define INICIAR_DESENHO glEnd
*/



void drawObject(){
     glBegin(GL_TRIANGLES);
        glVertex2i(50,-50);
        glVertex2i(0,50);
        glVertex2i(-50,-50);
     glEnd();
}

void drawOutline(){
     glBegin(GL_LINE_LOOP);
        glVertex2i(-100,100);
        glVertex2i(100,100);
        glVertex2i(100,-100);
        glVertex2i(-100,-100);
     glEnd();
}

void init(){
     glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

float xfactor = 0.0;
float yfactor = 0.0;
float scale   = 5.0;

int xfactorSignal = +1;
int yfactorSignal = +1;
int scaleSignal   = +1;


void timerFunc(int value)
{
    //xfactor
    if(xfactor>100 || xfactor<-100){
		xfactorSignal=-xfactorSignal;
	}
    xfactor = xfactor+xfactorSignal*5;
    
    //yfactor
    if(yfactor>100 || yfactor<-100){
		yfactorSignal=-yfactorSignal;
	}
    yfactor = yfactor+yfactorSignal*5;
    
    //scale
    if(scale<0 || scale>5){
		scaleSignal=-scaleSignal;
	}
    scale = scale+0.05*scaleSignal;
    
    //printf("%f, %f, %f\n",xfactor,yfactor,scale);
    
    glutPostRedisplay();
    
    glutTimerFunc(10,timerFunc,1);
}



void displayFunc() {
     glClear(GL_COLOR_BUFFER_BIT);     //desenha o fundo (limpa a janela)
     glMatrixMode(GL_PROJECTION);
     
     glLoadIdentity();
     gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
     glViewport(100, 400, 200, 200);
     glColor3f(1.0f, 0.0f, 0.0f);
     drawObject();
     
      
     glLoadIdentity();
     gluOrtho2D(xfactor-100.0f, xfactor+100.0f, -100.0f, 100.0f);
     glViewport(0, 200, 200, 200);
     glColor3f(0.0f, 0.0f, 0.0f);
     drawObject();
     
     
     glLoadIdentity();
     gluOrtho2D(-100.0f, 100.0f, yfactor-100.0f, yfactor+100.0f);
     glViewport(200, 200, 200, 200);
     glColor3f(0.0f, 1.0f, 0.0f);
     drawObject();
     
     
     glLoadIdentity();
     printf("%f, %f, %f, %f\n",-scale*100.0f, scale*100.0f, -scale*100.0f, scale*100.0f);
     gluOrtho2D(-scale*100.0f, scale*100.0f, -scale*100.0f, scale*100.0f);
     glViewport(100, 0, 200, 200);
     glColor3f(0.0f, 0.0f, 1.0f);
     drawObject();

     //Primeira janela glOrtho2D(xw_min,xw_max,yw_min,yw_max) = (-100,100,-100,100) - sist. de coordenadas do mundo (-oo,oo,-oo,oo)
     //Primeira Viewport glViewport(xv_min,yv_min,width,height) = (100,400,200,200) - sist. de coordenadas da janela (0,400,0,600)

     //Segunda janela glOrtho2D(xw_min,xw_max,yw_min,yw_max) = (,,,) - sist. de coordenadas do mundo (-oo,oo,-oo,oo)
     //Segunda Viewport glViewport(xv_min,yv_min,width,height) = (,,,) - sist. de coordenadas da janela (0,400,0,600)
     //...

     //Terceira janela glOrtho2D(xw_min,xw_max,yw_min,yw_max) = (,,,) - sist. de coordenadas do mundo (-oo,oo,-oo,oo)
     //Terceira Viewport glViewport(xv_min,yv_min,width,height) = (,,,) - sist. de coordenadas da janela (0,400,0,600)
     //...

     //Quarta janela glOrtho2D(xw_min,xw_max,yw_min,yw_max) = (,,,) - sist. de coordenadas do mundo (-oo,oo,-oo,oo)
     //Quarta Viewport glViewport(xv_min,yv_min,width,height) = (,,,) - sist. de coordenadas da janela (0,400,0,600)
     //...

     glLoadIdentity();
     gluOrtho2D(-200,200,-300,300);
     glViewport(0, 0, 400, 600);
     

     // GL_MODELVIEW utilizada para aplicar transforma&Atilde;&sect;&Atilde;&micro;es geom&Atilde;&copy;tricas &Atilde;&nbsp;s coordenadas dos objetos
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();


	 glPushMatrix();
     glColor3f(0.0f, 0.0f, 0.0f);
     glTranslatef(0,200,0);
     drawOutline();
	 glPopMatrix();
	
	 glPushMatrix();
     glLoadIdentity();
     glTranslatef(-100,0,0);
     drawOutline();
	 glPopMatrix();
	 
	 glPushMatrix();
     glLoadIdentity();
     glTranslatef(100,0,0);
     drawOutline();
	 glPopMatrix();
	 
	 glPushMatrix();
     glLoadIdentity();
     glTranslatef(0,-200,0);
     drawOutline();
	 glPopMatrix();

	//	glutSwapBuffers();     
     
     
     
    glFlush();
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(400,600);
	glutCreateWindow("Viewing 2D");
	glutDisplayFunc(displayFunc);
	if(TIMERFUNC)glutTimerFunc(10,timerFunc,1);
	init();
	glutMainLoop();
	return 0;
}
