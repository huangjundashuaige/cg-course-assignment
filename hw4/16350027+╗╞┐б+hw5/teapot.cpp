#define GLUT_STATIC
#include <GL/glut.h>
  
#define teapot_size 50.0f  
#define SIZE 100.0f  
   
void display(void)  
{  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    glEnable(GL_DEPTH_TEST);
    glPushMatrix();  

    glColor3f(1.0f, 1.0f, 1.0f);  
    glEnable(GL_NORMALIZE); //according to the doc this will make less mistake in some cases
    glutSolidTeapot(teapot_size); 
    
    glPopMatrix();  

    glutSwapBuffers();  

}  
  
GLfloat diffuseMaterial[4] = { 1,1,1, 1.0 };
void SetupLights()  
{  

    glShadeModel (GL_SMOOTH);
    GLfloat ambientLight[]  = {0.2f,  0.2f,  0.2f,  1.0f};//enviormental light 
    GLfloat diffuseLight[]  = {0.9f,  0.9f,  0.9f,  1.0f};//slow reflection 
    GLfloat specularLight[] = {1.0f,  1.0f,  1.0f,  1.0f};//mirror reflection light 
    GLfloat lightPos[]      = {1.0f, -2.0f, 2.0f, 1.0f};//light source position，spot light
    //GLfloat lightPos2[]      = {1.0f, -2.0f, 2.0f, 0.0f};  
    //GLfloat spot_direction[] = {100.0f, -50.0f, 50.0f};
    GLfloat shinless[] = {50.0};
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
    //glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    //glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, deg);
    //glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);     //set up the ebviormental light  
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);     //set up the slow reflection light  
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);   //set up the mirror reflection light    
    glEnable(GL_LIGHT1);


    GLfloat ambientLight2[]  = {0.0f,  0.0f,  0.0f,  1.0f};//enviormental light 
    GLfloat diffuseLight2[]  = {0.5f,  0.5f,  0.5f,  1.0f};//slow reflection 
    GLfloat specularLight2[] = {0.5f,  0.5f,  0.5f,  1.0f};//mirror reflection light 
    GLfloat lightPos2[]      = {1.0f, -2.0f, 2.0f, 0.0f};//light source position，point light source
 
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos2);        //set the light source position  
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight2);     //set up the ebviormental light  
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight2);     //set up the slow reflection light  
    //glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight2);   //set up the mirror reflection light    

    glEnable(GL_LIGHT0);
    
    glEnable(GL_COLOR_MATERIAL);                        //start the setting of material  
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);  //set up which face 
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularLight); //reaction to the material  
    //glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shinless);
    glMateriali(GL_FRONT, GL_SHININESS, 100);           //reflection rate   
    
/*
    GLfloat light_position[] = {50.0f, 0.0f, 50.0f, 1.0f };  
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);  
    glEnable(GL_LIGHTING);  
    glEnable(GL_LIGHT0);  
    glDepthFunc(GL_LESS);  
    glEnable(GL_DEPTH_TEST);    
*/
}  
void init()
{
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, 480, 480); 
    glOrtho(-SIZE, SIZE, -SIZE , SIZE , -SIZE, SIZE);  
    gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); 
}
int main(int argc, char* argv[])  
{  
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
    glutInitWindowSize(480, 480);  
    glutCreateWindow("simple light source");   
    init();
    glutDisplayFunc(display);  
   
    SetupLights();                  //set the light up 
  
    glutMainLoop();                 //main loop of the opengl  
    return 0;
}  