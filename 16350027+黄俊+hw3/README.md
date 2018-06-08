# intro 
1. the resutl of this program 
![twostar](./twostar.png)
![twostar](./y.png)
![twostar](./z.png)

2. how to use 
d and shift+d can change the day which means the rotation of the small star

y and shift+Y can change the year which means the rotation of the small star rotate around the big star

q and shift+Q is to change the viewpoint which was implement by using glutroatef in the display function in the begining to make sure it can rotate the whole scence
(if define in other place you might not change it by call the keyword)

3. how to run
```
./install.sh
./hw3
```
only availiable in linux

4. techical detail
using 
```
glPushMatrix();  
    glRotatef((GLfloat)y_index, 1, 1, 1);//可改变角度而不需要用lookat
    //glRotatef((GLfloat)day, 0, 0, 1);
    glutWireSphere(0.5, 20, 16);
    glRotatef((GLfloat)year, 0, 0, 1);//恒星
    glTranslatef(0, 1, 0);
    glRotatef((GLfloat)day, 0, 0, 1);
    glutWireSphere(0.2, 10, 8);   //卫星
    glPopMatrix(); //恢复原来的视角
```
to print the star and by using the transform stack to make sure the star was paint on the right place and the right angel,and using 
```
glPushMatrix();  
```
and
```
    glPopMatrix(); //恢复原来的视角
``` 
can make sure we can still view the origin position and every tranform matrix is all about to make sure the star was place on the right place.
```
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
```
above is that keyword to change the degree and the next loop,it will displace by the new degree instead of just add based on the previous degree because using the 
```
glpopmatrix
```
