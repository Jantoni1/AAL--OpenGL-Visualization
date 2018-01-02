//
// Created by Kuba on 02.01.2018.
//
#include <iostream>
#include <GL/freeglut.h>
#define GLUT_DISABLE_ATEXIT_HACK
#ifdef _WIN32
#	include <windows.h>
#else
#	include <sys/time.h>
#endif

#include "Scene.h"

static bool g_bButtonLDown = false;
static bool g_bButtonRDown = false;

CuboidContainer* cuboidContainer;
static std::vector<Cuboid*>* allCubs;
std::vector<std::vector<Cuboid*> >*solvedCuboids;
static int allCubsN;

static GLfloat rotation_y = 0.0;
static GLfloat rotation_x = 0.0;
static GLfloat eye_x = 0.0;
static GLfloat eye_y = 0.0;
static GLfloat origin_x = 0.0;
static GLfloat origin_y = 0.0;
static GLfloat g_fViewDistance = 3 * VIEWING_DISTANCE_MIN;
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;
static int g_Width = 600;                          // Initial window width
static int g_Height = 600;                         // Initial window height
static int g_yClick = 0;
static int g_xClick = 0;
static float g_lightPos[4] = { 10, 10, -100, 1 };  // Position of light

void drawCube(float posX, float posY, float posZ, float x, float y, float z)
{
    glPushMatrix();
    glBegin(GL_QUADS); //bot
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(posX, posY, posZ);
    glVertex3f(posX, posY, posZ + z);
    glVertex3f(posX + x, posY, posZ + z);
    glEnd();
    glBegin(GL_QUADS); //top
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(posX + x, posY + y, posZ);
    glVertex3f(posX, posY + y, posZ);
    glVertex3f(posX, posY + y, posZ + z);
    glVertex3f(posX + x, posY + y, posZ + z);
    glEnd();
    glBegin(GL_QUADS); //left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(posX, posY + y, posZ + z);
    glVertex3f(posX, posY + y, posZ);
    glVertex3f(posX, posY, posZ);
    glVertex3f(posX, posY, posZ + z);
    glEnd();
    glBegin(GL_QUADS); //front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(posX + x, posY + y, posZ + z);
    glVertex3f(posX, posY + y, posZ + z);
    glVertex3f(posX, posY, posZ + z);
    glVertex3f(posX + x, posY, posZ + z);
    glEnd();
    glBegin(GL_QUADS); //right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(posX + x, posY + y, posZ + z);
    glVertex3f(posX + x, posY + y, posZ);
    glVertex3f(posX + x, posY, posZ);
    glVertex3f(posX + x, posY, posZ + z);
    glEnd();
    glBegin(GL_QUADS); //back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(posX + x, posY + y, posZ);
    glVertex3f(posX, posY + y, posZ);
    glVertex3f(posX, posY, posZ);
    glVertex3f(posX + x, posY, posZ);
    glEnd();
    glPopMatrix();
}

void drawCube(Cuboid* cuboid)
{
    float posX =   static_cast<float>(cuboid->getDisplacement()[0]);
    float posY =   static_cast<float>(cuboid->getDisplacement()[0]);
    float posZ =   static_cast<float>(cuboid->getDisplacement()[0]);
    float x =      static_cast<float>(cuboid->getSizes()[0]);
    float y =      static_cast<float>(cuboid->getSizes()[0]);
    float z =      static_cast<float>(cuboid->getSizes()[0]);
	drawCube(posX, posY, posZ, x, y, z);
}

float* Scene::getRandomColor()
{
	int choice = rand() % 3;
	int choice2 = (choice + 1) % 3;
	int choice3 = (choice + 2) % 3;

	float* result = new float[3];

	result[choice] = float((rand() % 30 + 70) / 100.0);
	result[choice2] = float((rand() % 50 + 30) / 100.0);
	result[choice3] = float((rand() % 20 + 30) / 100.0);

	return result;
}

void RenderObjects(void)
{
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix(); // skalowanie
	glScalef((GLfloat)GLOBAL_SCALE, (GLfloat)GLOBAL_SCALE, (GLfloat)GLOBAL_SCALE);
		glRotatef(rotation_y, 1, 0, 0);
		glRotatef(rotation_x, 0, 1, 0);

		glPushMatrix(); // tacka
			glColor4f(1.0, 0.0, 0.0, 0.5);
            glTranslatef(0.0, -0.5, 0.0);
            drawCube(0, 0, 0,(float) cuboidContainer->getSizes()[0], 0.5,(float) cuboidContainer->getSizes()[2]);
		glPopMatrix(); // tacka

		glPushMatrix();
			glTranslatef(0.0, 0.0, 0.0);
			for (int i = 0; i < allCubsN; i++)
			{
                Cuboid* current = (*allCubs)[i];
				glPushMatrix();
					glColor4f(current->getColor()[0], current->getColor()[1], current->getColor()[2],(GLfloat) BOX_ALPHA);
                    drawCube(current);
				glPopMatrix();
			}
		glPopMatrix();

	glPopMatrix(); // skalowanie
}

void display(void)
{
	// Clear frame buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set up viewing transformation, looking down -Z axis
	glLoadIdentity();
	gluLookAt(eye_x, eye_y, -g_fViewDistance, origin_x, origin_y, 0, 0, 1, 0);

	// Set up the stationary light
	glLightfv(GL_LIGHT0, GL_POSITION, g_lightPos);

    // Render the scene
	RenderObjects();

	// Make sure changes appear onscreen
	glutSwapBuffers();

	fflush(stdout);
}

void reshape(GLint width, GLint height)
{
	g_Width = width;
	g_Height = height;

	glViewport(0, 0, g_Width, g_Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (float) g_Width / g_Height, g_nearPlane, g_farPlane);
	glMatrixMode(GL_MODELVIEW);
}

void InitGraphics(void)
{
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    glMaterialfv(GL_FRONT, GL_AMBIENT, g_lightPos);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void MouseButton(int button, int state, int x, int y)
{
	// Respond to mouse button presses.
	// If button1 pressed, mark this state so we know in motion function.

	if (button == GLUT_LEFT_BUTTON)
	{
		g_bButtonLDown = (state == GLUT_DOWN) ? true : false;
		g_yClick = y + (int)rotation_y;
		g_xClick = x - (int)rotation_x;
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		g_bButtonRDown = (state == GLUT_DOWN) ? true : false;
		g_yClick = y - (int)(ZOOM_SPEED * g_fViewDistance);
	}
}

void MouseMotion(int x, int y)
{
	// If button1 pressed, zoom in/out if mouse is moved up/down.

	if (g_bButtonLDown)
	{
		rotation_x =(GLfloat) (x - g_xClick);
		rotation_y = (GLfloat)-(y - g_yClick);
		glutPostRedisplay();
	}
	else if (g_bButtonRDown)
	{
		g_fViewDistance = (y - g_yClick) / (GLfloat)ZOOM_SPEED;
		if (g_fViewDistance < VIEWING_DISTANCE_MIN)
			g_fViewDistance = VIEWING_DISTANCE_MIN;
		glutPostRedisplay();
	}
}

void Keyboard(unsigned char key, int x, int y)
{
	int step = 10;
	switch (key)
	{
        case 27:             // ESCAPE key
            glutLeaveMainLoop();
            break;
        case 'w':
            origin_y += step;
            eye_y += step;
            break;
        case 's':
            origin_y -= step;
            eye_y -= step;
            break;
        case 'a':
            origin_x += step;
            eye_x += step;
            break;
        case 'd':
            origin_x -= step;
            eye_x -= step;
            break;
        case 'q' :
            g_fViewDistance += step;
            break;
        case 'e' :
            g_fViewDistance -= step;
            break;
        case '1':
            if (!(*solvedCuboids)[1].empty())
            {
                allCubs = &(*solvedCuboids)[1];
                allCubsN = allCubs->size();
                RenderObjects();
            }
            break;
        case '2':
            if (!(*solvedCuboids)[0].empty())
            {
                allCubs = &(*solvedCuboids)[0];
                allCubsN = allCubs->size();
                RenderObjects();
            }
            break;
        case '3':
            if (!(*solvedCuboids)[2].empty())
            {
                allCubs = &(*solvedCuboids)[2];
                allCubsN = allCubs->size();
                RenderObjects();
            }
            break;
	}
	glutPostRedisplay();
}

void Scene::start(int argc, char** argv, CuboidContainer* otherCuboidContainer,
                  std::vector<std::vector<Cuboid*> >* emplacedCuboids)
{
    for(auto& x : *emplacedCuboids) {
        std::cout<<x.size()<<std::endl;
    }
 	g_lightPos[0] = static_cast<float>((-1)*otherCuboidContainer->getSizes()[0]*2);
    g_lightPos[2] = static_cast<float>((-1)*otherCuboidContainer->getSizes()[1]*2);
	cuboidContainer = otherCuboidContainer;
    for(int i = 0; i < 3; ++i) {
        solvedCuboids = emplacedCuboids;
    }
    for(int i = 0; i < emplacedCuboids->size(); ++i) {
        if(!(*emplacedCuboids)[i].empty()) {
            allCubs = &(*emplacedCuboids)[i];
            break;
        }
    }
	allCubsN = allCubs->size();

	// GLUT Window Initialization:
	glutInit(&argc, argv);
	glutInitWindowSize(g_Width, g_Height);
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("AAL");

	// Initialize OpenGL graphics state
	InitGraphics();

	// Register callbacks:
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	std::vector<float* > colors;
	for (int j = 0; j < allCubs->size(); j++)
	{
		colors.push_back(Scene::getRandomColor());
	}
	for (int i = 0; i < 3; i++)
	{
		if (!(*solvedCuboids)[i].empty())
		{
            int k = 0;
            for(Cuboid* cuboid : (*solvedCuboids)[i]) {
                cuboid->setColor(colors[k++]);
            }
		}	
	}

	// Turn the flow of control over to GLUT
	glutMainLoop();
}

void Scene::close()
{

}

