#define GLUT_DISABLE_ATEXIT_HACK  
#include <math.h>  
  
#include <GL/glut.h>
//#pragma comment(lib, "glut32.lib")  
  
#define RADIUS 50.0f  
#define SIZE 100.0f  
  
GLboolean bWire = false;  
void OnDisplay(void)  
{  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    glEnable(GL_DEPTH_TEST); //使能深度检测  

    glPushMatrix();  
    glColor3f(1.0f, 1.0f, 1.0f);  
    glEnable(GL_NORMALIZE);  //归一化法向量  
    glutSolidTeapot(RADIUS); 
    glPopMatrix();  
    glutSwapBuffers();  
}  
  
void OnReshape(int w, int h)  
{  
    glViewport(0, 0, w, h);  
    glMatrixMode(GL_PROJECTION);  
  
    float aspect = (float)h / (float)w;  
  
    if(w <= h)  
    {  
        glOrtho(-SIZE, SIZE, -SIZE * aspect, SIZE * aspect, -SIZE, SIZE);  
    }  
    else  
    {  
        glOrtho(-SIZE / aspect, SIZE / aspect, -SIZE, SIZE, -SIZE, SIZE);  
    }  
    gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);  
    //gluLookAt(0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}  
GLfloat diffuseMaterial[4] = { 1,1,1, 1.0 };
void SetupLights()  
{  

    glShadeModel (GL_SMOOTH);
    GLfloat ambientLight[]  = {0.2f,  0.2f,  0.2f,  1.0f};//环境光  
    GLfloat diffuseLight[]  = {0.9f,  0.9f,  0.9f,  1.0f};//漫反射  
    GLfloat specularLight[] = {1.0f,  1.0f,  1.0f,  1.0f};//镜面光  
    GLfloat lightPos[]      = {1.0f, -2.0f, 2.0f, 1.0f};//光源位置
    //GLfloat lightPos2[]      = {1.0f, -2.0f, 2.0f, 0.0f};  
    //GLfloat spot_direction[] = {100.0f, -50.0f, 50.0f};
    GLfloat shinless[] = {50.0};
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
    //glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    //glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, deg);
    //glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);     //设置环境光源  
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);     //设置漫反射光源  
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);   //设置镜面光源  
    glEnable(GL_LIGHT1);


    GLfloat ambientLight2[]  = {0.0f,  0.0f,  0.0f,  1.0f};//环境光  
    GLfloat diffuseLight2[]  = {0.5f,  0.5f,  0.5f,  1.0f};//漫反射  
    GLfloat specularLight2[] = {0.5f,  0.5f,  0.5f,  1.0f};//镜面光  
    GLfloat lightPos2[]      = {1.0f, -2.0f, 2.0f, 0.0f};//光源位置
                              //启用光照  
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos2);        //设置灯光位置  
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight2);     //设置环境光源  
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight2);     //设置漫反射光源  
    //glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight2);   //设置镜面光源  

    glEnable(GL_LIGHT0);
   
                         //打开第一个灯光  
    glEnable(GL_COLOR_MATERIAL);                        //启用材质的颜色跟踪  
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);  //指定材料着色的面  
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularLight); //指定材料对镜面光的反应  
    //glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shinless);
    glMateriali(GL_FRONT, GL_SHININESS, 100);           //指定反射系数     
    
/*
    GLfloat light_position[] = {50.0f, 0.0f, 50.0f, 1.0f };  
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);  
    glEnable(GL_LIGHTING);  
    glEnable(GL_LIGHT0);  
    glDepthFunc(GL_LESS);  
    glEnable(GL_DEPTH_TEST);    
*/
}  
int main(int argc, char* argv[])  
{  
    glutInit(&argc, argv);                                      //初始化OpenGL  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   //设置显示模式  
    glutInitWindowSize(600, 480);  
    glutCreateWindow("GLUT提供的9种实体对象");  
    glutReshapeFunc(OnReshape);  
    glutDisplayFunc(OnDisplay);  
  
    //CreateMenu();                   //实际生成菜单  
    SetupLights();                  //设置光照  
  
    glutMainLoop();                 //进入OpenGL主循环  
    return 0;
}  