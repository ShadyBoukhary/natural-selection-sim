#include "simulation.hpp"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <chrono>
#include <thread>

void keyboard(unsigned char key, int x, int y);
void idle();
void display();
void draw();

const uint64_t width = 200;
const uint64_t height = 200;
const uint64_t organismCount = 35000;
Simulation simulation(organismCount, width, height);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Natural Selection");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glewInit();

    glutMainLoop();

    return 0;
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  // escape key
  case 033:
    exit(EXIT_SUCCESS);
    break;
  case 'e':
    break;
  }
}

void idle()
{
  glutPostRedisplay();
}

void draw()
{
  const auto& map = simulation.getMap();
  const auto& organisms = simulation.getOrganisms();
  glUseProgram(0);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glPointSize(25);
  glTranslatef(-0.99, -1, 0);
  glScalef(2, 1.95, 1);
  glBegin(GL_POINTS);

  //for (auto & [location, index] : simulation.getMap())
  //{
  //    glColor3f(0, 1, 0);
  //    // y is flipped in OpenGL
  //    glVertex3f(location.getY() / (float)width, 1 - location.getX() / (float)height, 0);
  //}
  for (int x = 0; x < simulation.getMapSize().first; x++) {
    for (int y = 0; y < simulation.getMapSize().second; y++) {
        Location location(x, y);
        auto it = map.find(location);
        if (it != map.end())
        {
            const auto & organism = simulation.getOrganisms()[it->second];
            switch (organism->getTrophicLevel()) {
            case TrophicLevel::Plant:
              glColor3f(0, 1, 0);
              break;
            case TrophicLevel::Primary:
              glColor3f(0.1, 0.4, 0.1); // dark green
              break;
            case TrophicLevel::Secondary:
              glColor3f(0.8, 0.5, 0); //yellow-ish
              break;
            case TrophicLevel::Tertiary:
              glColor3f(0.6, 0.3, 0.2); // brown-ish
              break;
            case TrophicLevel::Apex:
              glColor3f(0.8, 0.1, 0.7); // purple-sh
              break;
            }
            // y is flipped in OpenGL
            glVertex3f(y / (float)width, 1 - x / (float)height, 0);
        }
        else
        {
          glColor3f(0, 0, 0);
          glVertex3f(y / (float)width, 1 - x / (float)height, 0);
        }
    }
  }
  glEnd();
  static int i = 0;
  simulation.step();
}

void display()
{
  draw();
  glutSwapBuffers();
  // Calculate frame rate
  static int frame, fps, time, timebase = 0;
  frame++;
  time = glutGet(GLUT_ELAPSED_TIME);
  char display_string[100];
  if (time - timebase > 1000) {
    fps = frame * 1000.0 / (time - timebase);
    sprintf(display_string, "FPS:%d Alive: %lu", fps, simulation.getMap().size());
    glutSetWindowTitle(display_string);
    timebase = time;
    frame = 0;
  }
  //std::this_thread::sleep_for(std::chrono::milliseconds(40));
}
