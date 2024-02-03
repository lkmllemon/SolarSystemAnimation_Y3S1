#define _USE_MATH_DEFINES 
#include <cmath>        
#include <cstdlib>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h> 
#include "getBMP.h"

// Globals.
static int p = 20; 
static int q = 20; 
static float* vertices = NULL; 
static float* textureCoordinates = NULL; 
static unsigned int texture[10]; 
static int isDraw = 0;
static double d = -15.0;
static double x_rotate = 0.0;
static double y_rotate = 0.0;
static double z_rotate = 0.0;
static float angleRevolution_Mercury = -50;
static float angleRevolution_Venus = -135;
static float angleRevolution_Earth = 0;
static float angleRevolution_Mars = -180;
static float angleRevolution_Jupyter = 0;
static float angleRevolution_Saturn = -230;
static float angleRevolution_Neptune = 65;
static float angleRevolution_Uranus = 230;
static float angleRotation_Mercury = 0;
static float angleRotation_Venus = 0;
static float angleRotation_Earth = 0;
static float angleRotation_Mars = 0;
static float angleRotation_Jupyter = 0;
static float angleRotation_Saturn = 0;
static float angleRotation_Neptune = 0;
static float angleRotation_Uranus = 0;
imageFile* image[10];
GLfloat lightpos1[] = { 20, 80, 90, 1 };
GLfloat specular[] = { 1,1,1,1 };
GLfloat shininess[] = { 50 };
GLfloat diffuse[] = { 1,1,1,1 };
//Globals ends.

// Load image as a texture. 
void loadTextures(int id)
{
	glBindTexture(GL_TEXTURE_2D, texture[id]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[id]->width, image[id]->height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[id]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

// Fuctions to map the grid vertex (u_i,v_j) to the mesh vertex (f(u_i,v_j), g(u_i,v_j), h(u_i,v_j)) on the sphere.
float f(int i, int j, float R)
{
	return (R * cos(-M_PI / 2.0 + (float)j / q * M_PI) * cos(2.0 * (float)i / p * M_PI));
}

float g(int i, int j, float R)
{
	return (R * sin(-M_PI / 2.0 + (float)j / q * M_PI));
}

float h(int i, int j, float R)
{
	return (-R * cos(-M_PI / 2.0 + (float)j / q * M_PI) * sin(2.0 * (float)i / p * M_PI));
}

// Routine to fill the vertex array with co-ordinates of the mapped sample points.
void fillVertexArray(float R)
{
	int i, j, k;

	k = 0;
	for (j = 0; j <= q; j++)
		for (i = 0; i <= p; i++)
		{
			vertices[k++] = f(i, j, R); //x
			vertices[k++] = g(i, j, R); //y
			vertices[k++] = h(i, j, R); //z
		}
}

// Routine to fill the texture co-ordinates array with the texture co-ordinate values at the mapped sample points.
void fillTextureCoordArray(void)
{
	int i, j, k;

	k = 0;
	for (j = 0; j <= q; j++)
		for (i = 0; i <= p; i++)
		{
			textureCoordinates[k++] = (float)i / p;
			textureCoordinates[k++] = (float)j / q;
		}
}

// Initialization routine.
void setup(void)
{
	image[0] = getBMP("../Textures/sun.bmp");
	image[1] = getBMP("../Textures/mercury1.bmp");
	image[2] = getBMP("../Textures/venus.bmp");
	image[3] = getBMP("../Textures/earth.bmp");
	image[4] = getBMP("../Textures/mars.bmp");
	image[5] = getBMP("../Textures/jupyter.bmp");
	image[6] = getBMP("../Textures/saturn.bmp");
	image[7] = getBMP("../Textures/uranus.bmp");
	image[8] = getBMP("../Textures/neptune1.bmp");
	image[9] = getBMP("../Textures/starrynight.bmp");

	glEnable(GL_DEPTH_TEST);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glGenTextures(10, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	vertices = new float[3 * (p + 1) * (q + 1)];
	textureCoordinates = new float[2 * (p + 1) * (q + 1)];
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinates);
	fillTextureCoordArray();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_SMOOTH);
}
//Function to draw a sphere with radius and texture mapping
void sphere(float R, int id) {
	loadTextures(id);
	fillVertexArray(R);
	int i, j;
	for (j = 0; j < q; j++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i <= p; i++)
		{
			glArrayElement((j + 1) * (p + 1) + i);
			glArrayElement(j * (p + 1) + i);
		}
		glEnd();
	}
}
//backgroundTexture() is for backgound tetxure mapping
void backgroundTexture( int id) {
	loadTextures(id);
	glPushMatrix();
	glRotatef(-15,1, 0, 0);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3f(-800.0, -800.0, -230.0);
		glTexCoord2f(1.0, 0.0); glVertex3f(800.0, -800.0, -230.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(800.0, 800.0, -230.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(-800.0, 800.0, -230.0);
		glEnd();
	glPopMatrix();
}
//drawOrbit() is for drawing orbits for each planets
void drawOrbit(float radius, float c1, float c2, float c3) {
	//Add light source to orbits
	GLfloat ambient[] = { c1, c2, c3,1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos1);
	glLightfv(GL_LIGHT0, GL_SHININESS, shininess);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	glDisable(GL_TEXTURE_2D);
	//Draw orbit using line loop
	float numVertices = 360;
	float t = 0;
	glColor3f(c1, c2, c3);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < numVertices; ++i)
	{
		glVertex3f(radius * cos(t), radius * sin(t), 0.0);
		t += 2 * M_PI / numVertices;
	}
	glEnd();
	glEnable(GL_TEXTURE_2D);
}
//Function to draw the sun
void drawSun() {
	glPushMatrix();
	sphere(20.0, 0); 
	glPopMatrix();
}
//Function to draw the Mercury
void drawMercury() {
	glPushMatrix();
	glRotatef(angleRevolution_Mercury, 0, 1, 0);
	glPushMatrix();
	glTranslatef(45, 0, 0);
	glRotatef(angleRotation_Mercury, 0, 1, 0);
	sphere(4.0, 1);
	glPopMatrix();
	glTranslatef(45, 0, 0);
	glTranslatef(-45, 0, 0);
	glTranslatef(45, 0, 0);
	glPopMatrix();
}
//Function to draw the Venus
void drawVenus() {
	glPushMatrix();
	glRotatef(angleRevolution_Venus, 0, 1, 0);
	glPushMatrix();
	glTranslatef(60, 0, 0);
	glRotatef(angleRotation_Venus, 0, 1, 0);
	sphere(6.0, 2);
	glPopMatrix();
	glTranslatef(60, 0, 0);
	glTranslatef(-60, 0, 0);
	glTranslatef(60, 0, 0);
	glPopMatrix();
}
//Function to draw the Earth
void drawEarth() {
	glPushMatrix();
	glRotatef(angleRevolution_Earth, 0, 1, 0);
	glPushMatrix();
	glTranslatef(80, 0, 0);
	glRotatef(angleRotation_Earth, 0, 1, 0);
	sphere(7.5, 3);
	glPopMatrix();
	glTranslatef(60, 0, 0);
	glTranslatef(-60, 0, 0);
	glTranslatef(60, 0, 0);
	glPopMatrix();
}
//Function to draw the Mars
void drawMars() {
	glPushMatrix();
	glRotatef(angleRevolution_Mars, 0, 1, 0);
	glPushMatrix();
	glTranslatef(100, 0, 0);
	glRotatef(angleRotation_Mars, 0, 1, 0);
	sphere(6.5, 4);
	glPopMatrix();
	glTranslatef(100, 0, 0);
	glTranslatef(-100, 0, 0);
	glTranslatef(100, 0, 0);
	glPopMatrix();
}
//Function to draw the Jupiter
void drawJupyter() {
	glPushMatrix();
	glRotatef(angleRevolution_Jupyter, 0, 1, 0);
	glPushMatrix();
	glTranslatef(130, 0, 0);
	glRotatef(angleRotation_Jupyter, 0, 1, 0);
	sphere(12, 5);
	glPopMatrix();
	glTranslatef(130, 0, 0);
	glTranslatef(-130, 0, 0);
	glTranslatef(130, 0, 0);
	glPopMatrix();
}
//Function to draw the Saturn
void drawSaturn() {
	glPushMatrix();
	glRotatef(angleRevolution_Saturn, 0, 1, 0);
	glPushMatrix();
	glPushMatrix();
	glTranslatef(160, 0, 0);
	glRotatef(angleRotation_Saturn, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	//External ring of Saturn
	gluDisk(gluNewQuadric(), 9, 13, 20, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(160, 0, 0);
	glRotatef(angleRotation_Saturn, 0, 1, 0);
	//Saturn sphere
	sphere(8, 6);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(160, 0, 0);
	glTranslatef(-160, 0, 0);
	glTranslatef(160, 0, 0);
	glPopMatrix();
}
//Function to draw the Uranus
void drawUranus() {
	glPushMatrix();
	glRotatef(angleRevolution_Uranus, 0, 1, 0);
	glPushMatrix();
	glTranslatef(190, 0, 0);
	glRotatef(angleRotation_Uranus, 0, 1, 0);
	sphere(10, 7);
	glPopMatrix();
	glTranslatef(190, 0, 0);
	glTranslatef(-190, 0, 0);
	glTranslatef(190, 0, 0);
	glPopMatrix();
}
//Function to draw the Neptune
void drawNeptune() {
	glPushMatrix();
	glRotatef(angleRevolution_Neptune, 0, 1, 0);
	glPushMatrix();
	glTranslatef(220, 0, 0);
	glRotatef(angleRotation_Neptune, 0, 1, 0);
	sphere(9, 8);
	glPopMatrix();
	glTranslatef(220, 0, 0);
	glTranslatef(-220, 0, 0);
	glTranslatef(220, 0, 0);
	glPopMatrix();
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.0, 100.0, 260.0+d, 0.0, 0.0, 1.0+d, 0.0, 1.0, 0.0);
	glTranslatef(0,40,-20);

	backgroundTexture(9);		  //starry night background
	glRotatef(x_rotate, 1, 0, 0); //For rotating whole scene in x-axis
	glRotatef(y_rotate, 0, 1, 0); //For rotating whole scene in y-axis
	glRotatef(z_rotate, 0, 0, 1); //For rotating whole scene in z-axis

	glPushMatrix();
	//orbit
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawOrbit(45, 0.923, 0.806, 0.650);	 //orbit mercury
	drawOrbit(60, 0.85, 0.54, 0.43);	 //orbit venus
	drawOrbit(80, 0.117, 0.564, 1);		 //orbit earth
	drawOrbit(100, 0.698, 0.133, 0.133); //orbit mars
	drawOrbit(130, 0.704, 0.500, 0.210); //orbit jupyter
	drawOrbit(160, 0.100, 0.520, 0.120); //orbit saturn
	drawOrbit(190, 0.074, 0.344, 0.604); //orbit uranus
	drawOrbit(220, 0.312, 0.30, 0.70);	 //orbit neptune
	glPopMatrix();

	//Drawing sphere
	drawSun();		//Sun
	drawMercury();	//Mercury
	drawVenus();	//Venus
	drawEarth();	//Earth
	drawMars();		//Mars
	drawJupyter();	//Jupyter
	drawSaturn();	//Saturn
	drawUranus();	//Uranus
	drawNeptune();	//Neptune
	glPopMatrix();

	glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 800.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//Timer function to vary the speed of revolution and rotation in separate events
void timer(int value) {
	if (isDraw) {
		//Speed of rotation of Mercury
		angleRotation_Mercury += 1.2;
		if (angleRotation_Mercury > 360)
			angleRotation_Mercury -= 360;
		//Speed of revolution of Mercury around the Sun
		angleRevolution_Mercury += 7.0;
		if (angleRevolution_Mercury > 360)
			angleRevolution_Mercury -= 360;
		//Speed of rotation of Venus
		angleRotation_Venus += 0.7;
		if (angleRotation_Venus > 360)
			angleRotation_Venus -= 360;
		//Speed of revolution of Venus around the Sun
		angleRevolution_Venus += 4.6;
		if (angleRevolution_Venus > 360)
			angleRevolution_Venus -= 360;
		//Speed of rotation of Earth
		angleRotation_Earth += 7.0;
		if (angleRotation_Earth > 360)
			angleRotation_Earth -= 360;
		//Speed of revolution of Earth around the Sun
		angleRevolution_Earth += 4.0;
		if (angleRevolution_Earth > 360)
			angleRevolution_Earth -= 360;
		//Speed of rotation of Mars
		angleRotation_Mars += 9.0;
		if (angleRotation_Mars > 360)
			angleRotation_Mars -= 360;
		//Speed of revolution of Mars around the Sun
		angleRevolution_Mars += 3.1;
		if (angleRevolution_Mars > 360)
			angleRevolution_Mars -= 360;
		//Speed of rotation of Jupiter
		angleRotation_Jupyter += 8.0;
		if (angleRotation_Jupyter > 360)
			angleRotation_Jupyter -= 360;
		//Speed of revolution of Jupiter around the Sun
		angleRevolution_Jupyter += 2.5;
		if (angleRevolution_Jupyter > 360)
			angleRevolution_Jupyter -= 360;
		//Speed of rotation of Saturn
		angleRotation_Saturn += 7.0;
		if (angleRotation_Saturn > 360)
			angleRotation_Saturn -= 360;
		//Speed of revolution of Saturn around the Sun
		angleRevolution_Saturn += 2.0;
		if (angleRevolution_Saturn > 360)
			angleRevolution_Saturn -= 360;
		//Speed of rotation of Uranus
		angleRotation_Uranus += 6.0;
		if (angleRotation_Uranus > 360)
			angleRotation_Uranus -= 360;
		//Speed of revolution of Uranus around the Sun
		angleRevolution_Uranus += 1.2;
		if (angleRevolution_Uranus > 360)
			angleRevolution_Uranus -= 360;
		//Speed of rotation of Neptune
		angleRotation_Neptune += 5.0;
		if (angleRotation_Neptune > 360)
			angleRotation_Neptune -= 360;
		//Speed of revolution of Neptune around the Sun
		angleRevolution_Neptune += 0.7;
		if (angleRevolution_Neptune > 360)
			angleRevolution_Neptune -= 360;

		glutPostRedisplay();       
		glutTimerFunc(40, timer, 1);  
	}
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	//Press 'Esc' to exit the program 
	case 27:
		exit(0);
		break;
	//Press space bar to start animation
	case ' ':
		if (isDraw) {
			break;
		}
		else {
			isDraw = 1;
			timer(1);
		}
		break;
	//Press 's' to stop animation and reset planet's position
	case 's':
		while (isDraw) {
			angleRevolution_Mercury = -50;
			angleRevolution_Venus = -135;
			angleRevolution_Earth = 0;
			angleRevolution_Mars = -180;
			angleRevolution_Jupyter = 0;
			angleRevolution_Saturn = -230;
			angleRevolution_Neptune = 65;
			angleRevolution_Uranus = 230;
			timer(1);
			isDraw = 0;
		}
		break;
	//Press 'x' or 'X' to rotate whole scene in x-axis 
	case 'x':
		x_rotate += 5;
		if (x_rotate > 360.0) x_rotate -= 360.0;
		glutPostRedisplay();
		break;
	case 'X':
		x_rotate -= 5;
		if (x_rotate < 0) x_rotate += 360.0;
		glutPostRedisplay();
		break;
	//Press 'y' or 'Y' to rotate whole scene in y-axis 
	case 'y':
		y_rotate += 5;
		if (y_rotate > 360.0) y_rotate -= 360.0;
		glutPostRedisplay();
		break;
	case 'Y':
		y_rotate -= 5;
		if (y_rotate < 0) y_rotate += 360.0;
		glutPostRedisplay();
		break;
	//Press 'z' or 'Z' to rotate whole scene in z-axis 
	case 'z':
		z_rotate += 5;
		if (z_rotate > 360.0) z_rotate -= 360.0;
		glutPostRedisplay();
		break;
	case 'Z':
		z_rotate -= 5;
		if (z_rotate < 0) z_rotate += 360.0;
		glutPostRedisplay();
		break;
	//Press 'w' to reset the axis after rotation
	case 'w':
		x_rotate = 0;
		y_rotate = 0;
		z_rotate = 0;
		glutPostRedisplay();
		break;
	//Press '-' to zoom out the scene
	case '-':
		d++;
		glutPostRedisplay();
		break;
	//Press '+' to zoom in the scene
	case '+':
		d--;
		glutPostRedisplay();
		break;
	//Press 'r' to reset the camera to initial position
	case 'r':
		d = -8;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}
//Function for printing interaction in console
void printInteraction(void)
{
	std::cout << "Interaction : " << std::endl;
	std::cout << "Press space key to start the animation." << std::endl;
	std::cout << "Press 's' to switch and to reset the animation to the starting position." << std::endl
		<< "Press 'x/X' to rotate / rotate back to the entire model along the x-axis." << std::endl
		<< "Press 'y/Y' to rotate / rotate back to the entire model along the y-axis." << std::endl
		<< "Press 'z/Z' to rotate / rotate back to the entire model along the z-axis." << std::endl
		<< "Press 'w' to reset the whole solar system to its initial position." << std::endl
		<< "Press '+' to zoom in the scene." << std::endl
		<< "Press '-' to zoom in the scene." << std::endl
		<< "Press 'r' to reset the camera to its initial position." << std::endl;
}
// Main routine.
int main(int argc, char** argv)
{
	printInteraction();
	glutInit(&argc, argv);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 750);
	glutInitWindowPosition(310, 0);
	glutCreateWindow("Project_CST2104044.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}