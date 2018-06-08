#define GLUT_STATIC
#include<GL/glut.h>
int year=10,day = 10;
int y_index =0;
void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);  //清空颜色缓冲区
    glColor3f(1, 1, 1);   //重置颜色，白色
    glPushMatrix();  
    glRotatef((GLfloat)y_index, 1, 1, 1);//可改变角度而不需要用lookat
    //glRotatef((GLfloat)day, 0, 0, 1);
    glutWireSphere(0.5, 20, 16);
    glRotatef((GLfloat)year, 0, 0, 1);//恒星
    glTranslatef(0, 1, 0);
    glRotatef((GLfloat)day, 0, 0, 1);
    glutWireSphere(0.2, 10, 8);   //卫星
    glPopMatrix(); //恢复原来的视角
 
    glutSwapBuffers();
    glFlush();   
}
void init(void)
{
    glClearColor(0, 0, 0, 0);
    glShadeModel(GL_FLAT); //平面明暗模式
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case('y'):        
            year = (year + 10) % 360;
            glutPostRedisplay();
            break;
        case('Y'):
            year = (year-10) % 360;
            glutPostRedisplay();
            break;
        case('d'):
            day = (day + 10) % 360;
            glutPostRedisplay();
            break;
        case('D'):
            day = (day - 10) % 360;
            glutPostRedisplay();
            break;
        case('q'):
            y_index ++;
            glutPostRedisplay();
            break;
        case('Q'):
            y_index--;
            glutPostRedisplay();
            break;
    }

}
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);  //指定哪一个矩阵是当前矩阵
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 20);   //60度横宽比和范围
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);//设置摄像机
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   
    glutInitWindowSize(600, 600);    
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("hw3");
    init(); // 初始化
    glutDisplayFunc(display); // 执行显示
    //glMatrixMode(glMatrixMode);
    //glLoadIdentity();
    //gluLookAt(0, 10, 10, 0, 0, 0, 0, 0, 0);
    //glRotatef((GLfloat)year, 0, 0, 0);
    //glutPostRedisplay();
    //year+=10;
    glutReshapeFunc(reshape);//确定window
    glutKeyboardFunc(keyboard);
    glutMainLoop(); //进人GLUT事件处理循环
    return 0;
}
