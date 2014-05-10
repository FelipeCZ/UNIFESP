#include <stdio.h>
#include <math.h>
#include <GL/glut.h>


#define PI 3.1415962



void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo
    
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(1.0, 0.5, 0.5,   //posição da câmera (P_0)
              0.0, 0.0, 0.0,   //para onde a câmera aponta (P_ref)
              0.0, 1.0, 0.0); //vetor view-up (V)

    glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade
    glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0); //define uma projeção ortogonal
    glViewport(0, 0, 500, 500);

/*
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
    */
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

float scale   = 1.0;
float shift = 2.0f;
float angulo = 0.0f;

int scaleSignal   = +1;
int shiftSignal = +1;


void timerFunc(int value){
	
	angulo = (angulo + 0.01);
	if(angulo > 2.0*PI){
		angulo-=2*PI;
	}
	if(shift>3.0 || shift <-3.0){
		shiftSignal=-shiftSignal;
	}
	shift+=-0.1*shiftSignal;
	
	if(scale>5 || scale<0.5){
		scaleSignal=-scaleSignal;
	}
	scale=scale+scaleSignal*0.05;
	glutPostRedisplay();
	glutTimerFunc(10,timerFunc,1);
}


void displayFunc() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
        glMatrixMode(GL_MODELVIEW); //define que a matrix é a de modelo
        
     glOrtho(-3.0,3.0,-3.0,3.0,-3.0,3.0);
     glLoadIdentity();
     gluLookAt(1.0, 0.5, 0.5,   //posição da câmera (P_0)
              0.0, 0.0, 0.0,   //para onde a câmera aponta (P_ref)
              0.0, 1.0, 0.0); //vetor view-up (V)
     //glOrtho(-1.0f, 1.0f, -1.0f, 1.0f,-1.0f,1.0f);
     glViewport(100, 400, 200, 200);
     glColor3f(1.0f, 0.0f, 0.0f);
     cube();
     
      
     glLoadIdentity();
     gluLookAt(1.0+shift, 0.5, 0.5,   //posição da câmera (P_0)
              0.0+shift, 0.0, 0.0,   //para onde a câmera aponta (P_ref)
              0.0, 1.0, 0.0); //vetor view-up (V)
     glViewport(0, 200, 200, 200);
     glColor3f(0.0f, 0.0f, 0.0f);
     cube();
     
     
     glLoadIdentity();
     float x = 1.0;
     float y = .99;
     gluLookAt(x*cos(angulo)+y*sin(angulo),0.5, -x*sin(angulo)+y*cos(angulo),   //posição da câmera (P_0)
              0.0, 0.0, 0.0,   //para onde a câmera aponta (P_ref)
              0.0, 1.0, 0.0); //vetor view-up (V)
     //glOrtho(-1.0f, 1.0f, 1.0f, 1.0f,-1.0f,1.0f);
     glViewport(200, 200, 200, 200);
     glColor3f(0.0f, 1.0f, 0.0f);
     cube();
     
     
     glLoadIdentity();
     glOrtho(-scale*1.0f, scale*1.0f, -scale*1.0f, scale*1.0f,-scale*1.0f,scale*1.0f);
     gluLookAt(1.0, 0.5, 0.5,   //posição da câmera (P_0)
              0.0, 0.0, 0.0,   //para onde a câmera aponta (P_ref)
              0.0, 1.0, 0.0); //vetor view-up (V)
     glViewport(100, 0, 200, 200);
     
     glColor3f(0.0f, 0.0f, 1.0f);
     cube();



     
     

     // GL_MODELVIEW utilizada para aplicar transforma&Atilde;&sect;&Atilde;&micro;es geom&Atilde;&copy;tricas &Atilde;&nbsp;s coordenadas dos objetos
     /*
     glLoadIdentity();
     glOrtho(-200,200,-300,300);
     glViewport(0, 0, 400, 600);
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
       */ 
        
        glFlush(); //força o desenho das primitivas
        //glutSwapBuffers();
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(400,600);
	glutCreateWindow("Viewing 3D - Projecao Ortogonal");
	glutDisplayFunc(displayFunc);
	glutTimerFunc(10,timerFunc,1);
	init();
	glutMainLoop();
	return 0;
}

