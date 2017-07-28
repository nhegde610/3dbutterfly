/*
*
*
*			             Computer Graphics Mini-Project using OpenGL in C Language
*
*
*	Aim:Program to simulate a flying butterfly in 3D
*
*	Developer:	Niranjan Hegde
*	Tools:		OpenGL
*	Language:	C Language
*	USN:		1BI14CS100
*	Batch:		B-3
*	Semister:	6th
*
*
*
*/
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;
static GLdouble viewer[]= {0.0, 0.0,40.0};
static GLfloat angle;/* initial viewer location */
static GLint speed = 1.0;
GLint direction,rotate=0,translate=0,backgroundcolor=1,textures= 1,zoom= 1;
static GLfloat distance[] = {0.0,0.0,0.0};
GLfloat materialColor[] = {0.15f,0.15f,0.15f,0.1f};//The color of the middle part
GLfloat materialColor1[] = {1.0f,0.0f,0.0f,1.0f};//the color of wings part
GLuint displayListId,textureId;
int menuID,menuIdTrans,menuIdRotat,menuIdScale,menuIdTex,menuIdBg,frontpage=0,j,flap=0,menuIdanimate;
char text1[]={"Bangalore Institute of Technology"};
char text2[]={"Department of Computer Science & Engineering"};
char text3[]={"Opengl Mini project"};
char text4[]={"3D Butterfly"};
char text5[]={"/----------------------------Instructions------------------------------/"};
char text6[]={"Press right click to use pop-up menu and select the required option"};
char text7[]={"Press x,y and z to do changes along x,y and z axis repectively"};
char text8[]={"Submitted by:"};
char text9[]={"Niranjan Hegde"};
char text10[]={"1BI14CS100"};
char text11[]={"Teacher Incharge:"};
char text12[]={"Prof. Bhanushree K J"};
char text13[]={"Prof. Kavitha K"};
GLuint LoadTexture( const char * filename )
{
  GLuint texture;
  int width, height;
  unsigned char * data;
  FILE * file;
  file = fopen( filename, "rb" );
  if ( file == NULL ) return 0;
  width = 256;
  height = 256;
  data = (unsigned char *)malloc( width * height * 3 );
  //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );
  fclose( file );
  for(int i = 0; i < width * height ; ++i)
   {
     int index = i*3;
     unsigned char B,R;
     B = data[index];
     R = data[index+2];
     data[index] = R;
     data[index+2] = B;
   }
   glGenTextures( 1, &textureId );
   glBindTexture( GL_TEXTURE_2D, textureId );
   glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
   free( data );
   return textureId;
}
void draw_butterfly()
{
  //middle part of the butterfly
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glScalef(5.0,1.4,1.4);
    glutSolidSphere(1.0,150,80);
  glPopMatrix();
  //head part of the butterfly
  glPushMatrix();
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
      glTranslatef(5.0,0.0,0.0);
      glScalef(0.8,1.0,1.0);
      glutSolidSphere(1.0,150,80);
  glPopMatrix();
  //tail part of the butterfly
  glPushMatrix();
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glTranslatef(-4.0,0.0,0.0);
            glScalef(3.0,1.4,1.4);
        glutSolidSphere(1.0,150,80);
  glPopMatrix();
  //legs of the butterfly
  glPushMatrix();//legs1
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,materialColor);
        glTranslatef(1.0,0.0,1.4);
       glRotatef(10.0,0.0,1.0,0.0);
        glScalef(1.4,0.05,0.05);
        glutSolidCube(4.0);
  glPopMatrix();
  glPushMatrix();//legs2
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,materialColor);
        glTranslatef(1.0,0.6,1.4);
       glRotatef(10.0,0.0,1.0,0.0);
        glScalef(1.4,0.05,0.05);
        glutSolidCube(4.0);
  glPopMatrix();
  glPushMatrix();//legs3
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,materialColor);
        glTranslatef(-2.5,0.0,1.0);
       glRotatef(10.0,0.0,1.0,0.0);
        glScalef(1.6,0.05,0.05);
        glutSolidCube(4.0);
  glPopMatrix();
  glPushMatrix();//legs4
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,materialColor);
        glTranslatef(-2.5,0.6,1.0);
       glRotatef(10.0,0.0,1.0,0.0);
        glScalef(1.6,0.05,0.05);
        glutSolidCube(4.0);
  glPopMatrix();
  //antenna part of the butterfly
  glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glTranslatef(8.0,2.0,0.5);
        glRotatef(60.0,1.0,0.0,1.0);
        glScalef(4.3,0.05,0.05);
        glutSolidCube(2.0); //antenna 1
  glPopMatrix();
  glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glTranslatef(8.0,-2.0,-1.0);
        glRotatef(60.0,1.0,0.0,-1.0);
        glScalef(4.3,0.05,0.05);
        glutSolidCube(2.0); //antenna 2
  glPopMatrix();
}
void display(void)
{
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          if(frontpage==0)
          {
              glLoadIdentity();
                gluLookAt(viewer[0],viewer[1],viewer[2],0.0,0.0,0.0,1.0,0.0,0.0);
                glClearColor(0.0,0.0,0.0,0.0);
                                glRasterPos3f(30,25,0);
		            for(j=0;text1[j]!='\0';j++)
			               glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, text1[j]);
                glRasterPos3f(25,30,0);
                for(j=0;text2[j]!='\0';j++)
			               glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, text2[j]);
                glRasterPos3f(20,23,0);
     		            for(j=0;text3[j]!='\0';j++)
     			               glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, text3[j]);
                glRasterPos3f(15,20,0);
         		         for(j=0;text4[j]!='\0';j++)
         			            glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, text4[j]);
                glRasterPos3f(10,60,0);
          		       for(j=0;text5[j]!='\0';j++)
          			           glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, text5[j]);
                glRasterPos3f(05,40,0);
                     for(j=0;text6[j]!='\0';j++)
                           glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, text6[j]);
                glRasterPos3f(0,40,0);
                     for(j=0;text7[j]!='\0';j++)
                           glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, text7[j]);
                glRasterPos3f(-5,-40,0);
                      for(j=0;text8[j]!='\0';j++)
                           glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, text8[j]);
                glRasterPos3f(-10,-40,0);
                      for(j=0;text9[j]!='\0';j++)
                            glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, text9[j]);
                glRasterPos3f(-15,-40,0);
                      for(j=0;text10[j]!='\0';j++)
                            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text10[j]);
                glRasterPos3f(-5,70,0);
                      for(j=0;text11[j]!='\0';j++)
                            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text11[j]);
                glRasterPos3f(-10,70,0);
                      for(j=0;text12[j]!='\0';j++)
                            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text12[j]);
                glRasterPos3f(-15,70,0);
                      for(j=0;text13[j]!='\0';j++)
                             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text13[j]);
              glFlush();
          }
          else
          { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            switch(backgroundcolor)
          {
            case 1:glClearColor(0.65625,0.8,0.10,0.0); //bahina(green)
                    break;
            case 2:glClearColor(0.84,0.519,0.23,0.0); //Tree poppy(brown)
                    break;
            case 3:glClearColor(0.86,0.085,0.085,0.0);//harley davidson orange(red)
                    break;
            case 4:glClearColor(0.109,0.222,0.73,0.0);//persian blue
                    break;
            case 5:glClearColor(1.0,1.0,1.0,0.0); //white
                    break;
            case 6:glClearColor(0.0,0.0,0.0,0.0); //black
                    break;
          }
          GLUquadricObj *wings1,*wings2,*wings3,*wings4;
          glLoadIdentity();
          gluLookAt(viewer[0],viewer[1],viewer[2],0.0,0.0,0.0,0.0,1.0,0.0);
          //translation functions
           glTranslatef(distance[0],distance[1],distance[2]);
          //rotate functions
          glRotatef(theta[0], 1.0, 0.0, 0.0);
          glRotatef(theta[1], 0.0, 1.0, 0.0);
          glRotatef(theta[2], 0.0, 0.0, 1.0);
          //scale functions
          glScalef(zoom,zoom,zoom);
          //calling the middle body of the butterfly
          glCallList(displayListId);
           //wings part of the butterfly
          glPushMatrix(); //wings 1
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor1);
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_COLOR_MATERIAL);
            glBindTexture(GL_TEXTURE_2D,textureId);
            glTranslatef(4.0,0.0,0.0);
            glRotatef(angle,-1.0,0.0,0.0);
            glScalef(3.0,4.0,0.0);
                wings1 = gluNewQuadric();
              gluQuadricTexture(wings1,GL_TRUE);
             gluPartialDisk(wings1,0,5.0,150,150,320,80);
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_COLOR_MATERIAL);
           glPopMatrix();
          glPushMatrix(); //wings 2
             glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,materialColor1);
             glEnable(GL_TEXTURE_2D);
             glEnable(GL_COLOR_MATERIAL);
             glBindTexture(GL_TEXTURE_2D,textureId );
             glTranslatef(4.0,0.0,0.0);
             glRotatef(angle,-1.0,0.0,0.0);
             glScalef(2.5,3.0,0.0);
                  wings2 = gluNewQuadric();
                  gluQuadricTexture(wings2,GL_TRUE);
             gluPartialDisk(wings2,0,5.0,150,150,280,50);
             glDisable(GL_TEXTURE_2D);
             glDisable(GL_COLOR_MATERIAL);
            glPopMatrix();
         glPushMatrix(); //wings 3
             glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,materialColor1);
             glEnable(GL_TEXTURE_2D);
             glEnable(GL_COLOR_MATERIAL);
             glBindTexture(GL_TEXTURE_2D,textureId );
             glTranslatef(4.0,0.0,0.0);
             glRotatef(180-angle,-1.0,0.0,0.0);
             glScalef(2.5,3.0,0.0);
              wings3 = gluNewQuadric();
              gluQuadricTexture(wings3,GL_TRUE);
             gluPartialDisk(wings3,0,5.0,150,150,280,50);
             glDisable(GL_TEXTURE_2D);
             glDisable(GL_COLOR_MATERIAL);
            glPopMatrix();
        glPushMatrix(); //wings 4
             glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,materialColor1);
             glEnable(GL_TEXTURE_2D);
             glEnable(GL_COLOR_MATERIAL);
             glBindTexture(GL_TEXTURE_2D,textureId );
             glTranslatef(4.0,0.0,0.0);
             glRotatef(180-angle,-1.0,0.0,0.0);
             glScalef(3.0,4.0,0.0);
                  wings4 = gluNewQuadric();
                  gluQuadricTexture(wings4,GL_TRUE);
             gluPartialDisk(wings4,0,5.0,150,150,320,80);
             glDisable(GL_TEXTURE_2D);
             glDisable(GL_COLOR_MATERIAL);
            glPopMatrix();
        }
        glFlush();
        glutSwapBuffers();

}
void spinbutterfly() //spins the butterfly along different axis
{
            theta[axis] += 1.0;
            if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
            display();
}
void wings_flap()
{         if(flap==1){
              do{
                    display();
                    angle+=speed;
              }while(angle<75 && angle > 0);
              speed*=-1;
            }
              glutPostRedisplay();
}
void movebutterfly()
{
    distance[direction]+= 1.0;
          if(distance[direction]> 40.0) distance[direction]= -40.0;
          glutPostRedisplay();
}
void keys(unsigned char key, int x, int y)// handles spinning along different axis
{
  /* Use x, X, y, Y, z, and Z keys to move viewer */
  if(rotate == 1){
  if(key == 'x'| key == 'X') axis = 0;spinbutterfly();
  if(key == 'y'| key == 'Y') axis = 1;spinbutterfly();
  if(key == 'z'| key == 'Z') axis = 2;spinbutterfly();
  }
  if(translate == 1){
  if(key == 'y'|key == 'Y') direction = 1;movebutterfly(); // Y-axis
  if(key == 'x'| key == 'X') direction = 0;movebutterfly(); // X-axis
  if(key == 'z'| key == 'Z') direction = 2;movebutterfly(); //Z-axis
  }
  if(key == 13) frontpage = 1;glutPostRedisplay();
}
void reshape(int w, int h) //needs to some work to avoid distortion
{
 glViewport(0, 0, w, h);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();

   if(w>=h)
      glFrustum(-40.0,40.0,-40.0*(GLfloat)h/(GLfloat)w,40.0*(GLfloat)h/(GLfloat)w,20.0,400.0);
   else
      glFrustum(-40.0,40.0,-40.0*(GLfloat)w/(GLfloat)h,40.0*(GLfloat)w/(GLfloat)h,20.0,400.0);
    glMatrixMode(GL_MODELVIEW);
}
void myinit()
{
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        glShadeModel(GL_SMOOTH);
        //Disable color materials, so that glMaterial calls work
        glDisable(GL_COLOR_MATERIAL);
        //Set up a display list for drawing body of the butterfly
	       displayListId = glGenLists(1); //Make room for the display list
	       glNewList(displayListId, GL_COMPILE); //Begin the display list
	        draw_butterfly(); //Add commands for drawing butterfly to the display list
	       glEndList(); //End the display list
}
void mainMenu(int key1)
{
  switch(key1)
  {case 1: exit(0);
          break;
        }
}
void menumove(int key2)
{
  switch(key2){
    case 0: translate = 1;rotate =0;
            break;
    case 1: translate = 0;rotate = 0;
            break;
    }
}
void menuspin(int key3)
{
  switch(key3){
    case 0: translate = 0;rotate = 1;
            break;
    case 1: translate = 0;rotate = 0;
            break;
    }
}
void menuscale(int key4)
{
  switch(key4){
    case 0: zoom+=1.0;
            //glutPostRedisplay();
            break;
    case 1:zoom-=1.0;
            //glutPostRedisplay();
            break;
        }
}
void chooseTex(int key5)
{
  switch(key5){
    case 1: textureId = LoadTexture("tex1.bmp");
            //glutPostRedisplay();
            break;
    case 2: textureId = LoadTexture("tex2.bmp");
            //glutPostRedisplay();
            break;
    case 3: textureId = LoadTexture("tex3.bmp");
            //glutPostRedisplay();
            break;
    case 4: textureId = LoadTexture("tex4.bmp");
            //glutPostRedisplay();
            break;
    case 5: textureId = LoadTexture("tex5.bmp");
            //glutPostRedisplay();
            break;
  }
}
void chooseBg(int key6)
{
  switch(key6){
    case 1:backgroundcolor = 1; //bahina(green)
            break;
    case 2:backgroundcolor = 2; //Tree poppy(brown)
            break;
    case 3:backgroundcolor = 3;//harley davidson orange(red)
            break;
    case 4:backgroundcolor = 4;//persian blue
            break;
    case 5:backgroundcolor = 5; //white
            break;
    case 6:backgroundcolor =6; //black
            break;
  }
}
void menuanimate(int key7)
{
  switch(key7){
    case 1:flap = 1;wings_flap();
            break;
    case 2:flap = 0;
            break;
  }
}
void  main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(5000,5000);
  glutInitWindowPosition(0.0,0.0);
  glutCreateWindow("Butterfly");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  myinit();
  glutKeyboardFunc(keys);
  glEnable(GL_DEPTH_TEST);
  glutIdleFunc(wings_flap);

  menuIdTrans = glutCreateMenu(menumove);
 glutAddMenuEntry("Translate on",0);
 glutAddMenuEntry("Translate off",1);

 menuIdRotat = glutCreateMenu(menuspin);
 glutAddMenuEntry("Rotate on",0);
 glutAddMenuEntry("Rotate off",1);

 menuIdScale = glutCreateMenu(menuscale);
 glutAddMenuEntry("Increase Size",0);
 glutAddMenuEntry("Decrease Size",1);

 menuIdTex = glutCreateMenu(chooseTex);
 glutAddMenuEntry("Texture-1",1);
 glutAddMenuEntry("Texture-2",2);
 glutAddMenuEntry("Texture-3",3);
 glutAddMenuEntry("Texture-4",4);
 glutAddMenuEntry("Texture-5",5);

 menuIdBg = glutCreateMenu(chooseBg);
 glutAddMenuEntry("Green(bahina)",1);
 glutAddMenuEntry("Brown(Tree poppy)",2);
 glutAddMenuEntry("Red(Harley Davidson)",3);
 glutAddMenuEntry("Blue(Persian Blue)",4);
 glutAddMenuEntry("White",5);
 glutAddMenuEntry("Black",6);

 menuIdanimate = glutCreateMenu(menuanimate);
 glutAddMenuEntry("Animation on",1);
 glutAddMenuEntry("Animation off",2);

 menuID = glutCreateMenu(mainMenu);
 glutAddSubMenu("Animation",menuIdanimate);
 glutAddSubMenu("Translation",menuIdTrans);
 glutAddSubMenu("Rotation",menuIdRotat);
 glutAddSubMenu("Change Size",menuIdScale);
 glutAddSubMenu("Change Texture",menuIdTex);
 glutAddSubMenu("Change Background",menuIdBg);
 glutAddMenuEntry("quit",1);
 glutAttachMenu(GLUT_RIGHT_BUTTON);
 glutMainLoop();
}
