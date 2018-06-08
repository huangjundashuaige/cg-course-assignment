#define GLUT_STATIC
#include <GL/glut.h>
#include <math.h>
class Point
{
public:
    int x,y;
    Point(int x,int y)
    {
        this->x=x;
        this->y=y;
    }
};
void init()
{
    //glClearColor(0, 0, 0, 0);
    //glShadeModel(GL_FLAT); //平面明暗模式
    //glClearColor(0, 0, 0, 0);
    glClearColor(1.0, 1.0, 1.0, 0); //设定背景为黑色
    glColor3f(0.0,0.0,0.0); //绘图颜色为白色
    glPointSize(2.0); //设定点的大小为2*2像素的
    glMatrixMode(GL_PROJECTION); // 设定合适的矩阵
    //glLoadIdentity(); // 是一个无参的无值函数，其功能是用一个4×4的单位矩阵来替换当前矩阵，实际上就是对当前矩阵进行初始化。也就是说，无论以前进行了多少次矩阵变换，在该命令执行后，当前矩阵均恢复成一个单位矩阵，即相当于没有进行任何矩阵变换状态
    gluOrtho2D(0.0,600.0,0.0,480.0);

}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    //glColor3f(0.0,0.0,0.0); //绘图颜色为白色
    Point p1(100,100);
    Point p2(200,100);
    Point p3(100,200);
    //glVertex2f(p1.x,p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p3.x, p3.y);
    glEnd();
    glBegin(GL_LINES);
    //glColor3f(0.0,0.0,0.0); //绘图颜色为白色
    //Point p1(100,100);
    //Point p2(200,100);
    //Point p3(100,200);
    glVertex2f(p1.x,p1.y);
    glVertex2f(p2.x, p2.y);
    //glVertex2f(p3.x, p3.y);
    glEnd();
    glFlush();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   //缓存模式
    glutInitWindowSize(600, 480);    //显示框的大小
    glutInitWindowPosition(100, 100); //确定显示框左上角的位置
    glutCreateWindow("testline");
    init();
    glutDisplayFunc(display);
    glutMainLoop(); 
    return 0;
}