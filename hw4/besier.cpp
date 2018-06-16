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
    //glColor3f(0.0,0.0,0.0); 
    glPointSize(5.0); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluOrtho2D(0.0,480.0,0.0,480.0);    
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
    glColor3f(1.0,0.0,0.0);
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
    for(auto p:vec_point)
    {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_POINTS);
        glVertex2f(p.x, p.y);
        glEnd();
        glFlush();   
    }
    for(auto line:vec_ber)
    {
        for(auto p:line)
        {
            glColor3f(1.0,1.0,1.0);
            glBegin(GL_POINTS);
            glVertex2f(p.x, p.y);
            glEnd();
            glFlush();
        }
        for(int i = 0;i < line.size()-1;i++)
        {
            glColor3f(1.0,1.0,1.0);
            drawLine(line[i],line[i+1]);
        }
        for(int i=0;i<vec_point.size();i++)
        {
            glColor3f(1.0,1.0,1.0);
            glBegin(GL_POINTS);
            glVertex2f(vec_point[i].x, vec_point[i].y);
            glEnd();
            glFlush();
        }
        drawBezier(line);
    }
}
void mouse(int button, int state, int x, int y) 
{
    //cout<<1<<endl;
    if(state == GLUT_DOWN)
    {
        Point p(x,480-y);
        glColor3f(1.0,1.0,1.0);
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
    glutPostRedisplay();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   
    glutInitWindowSize(480,480); 
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("hw4");
    init();
    glClear(GL_COLOR_BUFFER_BIT);
    glutMouseFunc(mouse); 
    glutDisplayFunc(display); 
    glutMainLoop(); 
    return 0;
}