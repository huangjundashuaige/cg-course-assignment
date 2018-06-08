#define OM_STATIC_BUILD
#define GLUT_STATIC
#include <iostream>  
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>  
#include <GL/glut.h>
#include <string>
#include <vector>
using namespace std;
typedef OpenMesh::TriMesh_ArrayKernelT<> MyMesh;
MyMesh mesh;//openmesh object to read the data
void display();
void onMouseMove(int x, int y);
void mouse(int button, int state, int x, int y);
void keyboard(int key, int x, int y);
void readfile(string file);
void reshape(GLint w, GLint h);
void init();

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // GLUT_Double 表示使用双缓存而非单缓存
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(480, 480);
    glutCreateWindow("hw4 meshLab");
    readfile("cow.obj");
    init();
    glutSpecialFunc(keyboard);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(onMouseMove);


    glutMainLoop();
    return 0;
}
int showstate = 1;
bool face_flag = true;
bool line_flag = false;
bool flatline_flag = false;//display different mode
void CreateNewFunctionListWire(GLuint &list)
{
    glNewList(list, GL_COMPILE);
    glDisable(GL_LIGHTING);
    glLineWidth(1.0f);
    //glColor3f(0.5f, 0.0f, 0.0f);
    //glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    for (MyMesh::HalfedgeIter he_it = mesh.halfedges_begin(); he_it != mesh.halfedges_end(); ++he_it) {
        //链接这个有向边的起点和终点
        glVertex3fv(mesh.point(mesh.from_vertex_handle(*he_it)).data());
        glVertex3fv(mesh.point(mesh.to_vertex_handle(*he_it)).data());
    }
    glEnd();
    glEnable(GL_LIGHTING);
    glEndList();
}
void CreateNewFunctionListFlat(GLuint &list)
{
    glNewList(list, GL_COMPILE);
    for (MyMesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it) {
        glBegin(GL_TRIANGLES);
        for (MyMesh::FaceVertexIter fv_it = mesh.fv_iter(*f_it); fv_it.is_valid(); ++fv_it) {
            glNormal3fv(mesh.normal(*fv_it).data());
            glVertex3fv(mesh.point(*fv_it).data());
        }
        glEnd();
    }
    glEndList();
}
void drawFace()
{
        for (MyMesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it) {
        glBegin(GL_TRIANGLES);
        for (MyMesh::FaceVertexIter fv_it = mesh.fv_iter(*f_it); fv_it.is_valid(); ++fv_it) {
            glNormal3fv(mesh.normal(*fv_it).data());
            glVertex3fv(mesh.point(*fv_it).data());
        }
        glEnd();
    }
}
void drawLine()
{
    glDisable(GL_LIGHTING);
    glLineWidth(1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    for (MyMesh::HalfedgeIter he_it = mesh.halfedges_begin(); he_it != mesh.halfedges_end(); ++he_it) 
    {
        glVertex3fv(mesh.point(mesh.from_vertex_handle(*he_it)).data());
        glVertex3fv(mesh.point(mesh.to_vertex_handle(*he_it)).data());
    }
    glEnd();
    glEnable(GL_LIGHTING);
}
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(5.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST); //more real              
    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0);  
}

void reshape(GLint w, GLint h)
{
    glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w > h)
        glOrtho(-static_cast<GLdouble>(w) / h, static_cast<GLdouble>(w) / h, -1.0, 1.0, -100.0, 100.0);
    else
        glOrtho(-1.0, 1.0, -static_cast<GLdouble>(h) / w, static_cast<GLdouble>(h) / w, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
float x_rotate = 0.0f;//3d model rotate degree
float y_rotate = 0.0f;//3d model rotate degree
float x_position = 0.0f;//current position
float y_position = 0.0f;//current position
float scale = 1.0f;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(x_rotate, 1.0f, 0.0f, 0.0f);
    glRotatef(y_rotate, 0.0f, 1.0f, 0.0f);
    glTranslatef(x_position, y_position,0.0f);
    glScalef(scale, scale, scale); 
    if (face_flag)
    {
        drawFace();
    }
    else if (flatline_flag) 
    {
        drawLine();
        drawFace();
    }
    else if (line_flag)
    {
        drawLine();
    }
    glutSwapBuffers(); //swap the buffer bit
}
//standard use of openmesh to read a 3d model
void readfile(string file) {
    mesh.request_vertex_normals();
    OpenMesh::IO::Options opt;
    OpenMesh::IO::read_mesh(mesh, file, opt);  
    mesh.request_face_normals();
    mesh.update_normals();
    mesh.release_face_normals();
}
string file_arr[3] = {string("cow.obj"),string("cactus.ply"),string("Armadillo.off")};
int file_size = 3;
int currentfile = 0;
void keyboard(int key, int x, int y) {
    switch (key) 
    {
    case GLUT_KEY_F1:
        currentfile++;
        if(currentfile>file_size-1)
            currentfile = 0;
        readfile(file_arr[currentfile]);
        scale = 1.0f;
        if(currentfile == 2)
            scale = 0.01f;
        init();
        break;
    case GLUT_KEY_F2:
        if (face_flag == true) 
        {
            face_flag = false;
            line_flag = true;
            cout<<"wire"<<endl;
        }
        else if (line_flag == true)
        {
            line_flag = false;
            flatline_flag = true;
            cout << "Flatlines" << endl;
        }
        else if (flatline_flag == true) 
        {
            flatline_flag = false;
            face_flag = true;
            cout << "Flat" << endl;
        }
        break;
    case GLUT_KEY_UP://move using up and down and left and right
        y_position += 0.1;
        break;
    case GLUT_KEY_DOWN:
        y_position -= 0.1;
        break;
    case GLUT_KEY_LEFT:
        x_position -= 0.1;
        break;
    case GLUT_KEY_RIGHT:
        x_position += 0.1;
        break; 
    default:
        break;
    }
    glutPostRedisplay();
}
int mousetate = 0;
float x_previous = 0.0; 
float y_previous = 0.0;
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mousetate = 1;
        x_previous = x;
        y_previous = y;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        mousetate = 0;
    if (state == GLUT_UP && button == 3) 
    {
            scale -= 0.1;
    }
    if (state == GLUT_UP && button == 4) 
    {
        scale += 0.1;
    }
    glutPostRedisplay();
}
void onMouseMove(int x, int y) {
    if (mousetate) 
    {
        y_rotate += x - x_previous;
        x_previous = x;
        x_rotate += y - y_previous;
        glutPostRedisplay();
        y_previous = y;
    }
}


