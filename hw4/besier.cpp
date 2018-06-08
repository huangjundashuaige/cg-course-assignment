#define GLUT_STATIC
#include <GL/glut.h>
#include <math.h>
#include<vector>
#include<iostream>
using namespace std;
class Point
{
public:
int x,y;
    Point(int x,int y)
    {
        this->x=x;
        this->y=y;
    }
    Point();
};
vector<Point> vec_point;
vector<vector<Point>> vec_ber;
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0); //设定背景为黑色
    glColor3f(0.0,0.0,0.0); //绘图颜色为白色
    glPointSize(5.0); //设定点的大小为2*2像素的
    glMatrixMode(GL_PROJECTION); // 设定合适的矩阵
    glLoadIdentity(); // 是一个无参的无值函数，其功能是用一个4×4的单位矩阵来替换当前矩阵，实际上就是对当前矩阵进行初始化。也就是说，无论以前进行了多少次矩阵变换，在该命令执行后，当前矩阵均恢复成一个单位矩阵，即相当于没有进行任何矩阵变换状态
    gluOrtho2D(0.0,600.0,0.0,480.0); //平行投影，四个参数分别是x,y范围   
}
void drawLine(Point p1,Point p2)
{
    glBegin(GL_LINES);
    glVertex2f(p1.x,p1.y);
    glVertex2f(p2.x,p2.y);
    glEnd();
    glFlush();
}
void drawBezier(vector<Point> vec_point)
{
    glColor3f(1.0,1.0,0.0);
    Point p1 = vec_point[0];
    Point p2 = vec_point[1];
    Point p3 = vec_point[2];
    Point p4 = vec_point[3];
    Point temp_p(0,0);
    for(double t=0;t<=1.0;t+=0.01)
    {
        Point p(0,0);
        double a1 = pow((1 - t), 3);
        double a2 = pow((1 - t), 2) * 3 * t;
        double a3 = 3 * t*t*(1 - t);
        double a4 = t*t*t;
        p.x = a1*p1.x + a2*p2.x + a3*p3.x + a4*p4.x;
        p.y = a1*p1.y + a2*p2.y + a3*p3.y + a4*p4.y;
        if(t==0)
        {
            temp_p.x = p.x;
            temp_p.y = p.y;
        }
        else
        {
            drawLine(temp_p,p);
            temp_p.x = p.x;
            temp_p.y = p.y;
        }
    }
    
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for(auto line:vec_ber)
    {
        for(auto p:line)
        {
            glColor3f(1.0,1.0,0.0);
            glBegin(GL_POINTS);
            glVertex2f(p.x, p.y);
            glEnd();
            glFlush();
        }
        for(int i = 0;i < line.size()-1;i++)
        {
            glColor3f(1.0,0.0,0.0);
            drawLine(line[i],line[i+1]);
        }
        for(int i=0;i<vec_point.size();i++)
        {
            glColor3f(1.0,1.0,0.0);
            glBegin(GL_POINTS);
            glVertex2f(vec_point[i].x, vec_point[i].y);
            glEnd();
            glFlush();
        }
        drawBezier(line);
    }
}
void mymouseFunction(int button, int state, int x, int y) 
{
    //cout<<1<<endl;
    if(state == GLUT_DOWN)
    {
        Point p(x,480-y);
        glColor3f(1.0,1.0,0.0);
        glBegin(GL_POINTS);
        glVertex2f(p.x, p.y);
        glEnd();
        glFlush();
        vec_point.push_back(p);
        if(vec_point.size()==4)
        {
            vec_ber.push_back(vec_point);
            vec_point.clear();
        }  
    }
    display();
}
int main(int argc, char *argv[])
{
    /*
    Point p1(0,0),p2(100,100),p3(200,200),p4(100,200);
    vec_point.push_back(p1);
    vec_point.push_back(p2);
    vec_point.push_back(p3);
    vec_point.push_back(p4);
    vec_ber.push_back(vec_point);
    */
    glutInit(&argc, argv); //固定格式
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   //缓存模式
    glutInitWindowSize(600, 480);    //显示框的大小
    glutInitWindowPosition(100, 100); //确定显示框左上角的位置
    glutCreateWindow("第四次作业");
    init();
    glClear(GL_COLOR_BUFFER_BIT);
    glutMouseFunc(mymouseFunction); // 添加鼠标事件
    glutDisplayFunc(display); // 执行显示   
    glutMainLoop(); //进人GLUT事件处理循环
    return 0;
}