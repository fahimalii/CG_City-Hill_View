#include <iostream>
#include <GL/gl.h>
#include<GL/glu.h>
#include <GL/glut.h>
#include<math.h>
#include <cstdlib>
#include<cstdio>
#include<cmath>
#include<string>

// Scene 1 Header Files
#include "Scene_1_Sky.h" // This file includes the utilities header, so subsequent files can use utilities as well without including
#include "Scene_1_Left_Buildings.h"
#include "Scene_1_Hospital_Pharmacy.h"
#include "Scene_1_Sun_Moon.h"
#include "Scene_1_Tree_Bushes.h"
#include "Scene_1_Road_Cars.h"

// Scene 2 Header Files
#include "Scene_2_Sky.h"
#include "Scene_2_Sun_Moon.h"
#include "Scene_2_Sea.h"
#include "Scene_2_Ship.h"
#include "Scene_2_Restaurant_Booth.h"
#include "Scene_2_Hill.h"
#include "Scene_2_Land.h"
#include "Scene_2_Road_Cars.h"

using namespace std;

// City View Variables
GLfloat sun_moon_position_city_view = 0.0f;
GLfloat sun_moon_speed_city_view = 0.01f;

GLfloat cloudPositionCityView = 0.0f;
GLfloat cloudSpeedCityView = 0.01f;

GLfloat firstCarPosition = 1.0f;
GLfloat secondCarPosition = 1.2f;
GLfloat thirdCarPosition = -0.2f;
GLfloat fourthCarPosition = 0.5f;


// Hill View Variables
GLfloat sun_moon_position_hill_view = 0.0f;
GLfloat sun_moon_speed_hill_view = 0.01f;

GLfloat firstBusPosition = 1.1f;
GLfloat firstPickupPosition = 1.2f;
GLfloat secondPickupPosition = -0.2f;
GLfloat secondBusPosition = -0.3f;

GLfloat shipPosition = 0.0f;


// Boolean Variables used for changing between day & night
bool day = true;
bool night = false;

// Boolean Variables used for changing between scenes
bool showFirstScene = true;
bool showSecondScene = false;


GLfloat screenChangeTimer = 0.0f;

void mouseHandler(int button, int state, int mousex, int mousey)
{

}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (showFirstScene)
    {
        if(day)
        {
            glLoadIdentity();
            glPushMatrix();

            drawCityViewSkyDay();
            drawSunCityView(sun_moon_position_city_view);
            drawCityViewCloud(cloudPositionCityView);

            drawLeftTree();
            drawRightTree();
            drawMiddleTree();

            drawBushes();

            drawfirstbuilding();
            drawSecondBuilding();
            drawThirdBuilding();

            drawHospital();
            drawPharmacy();

            drawRoadCityView();
            streetLightDayCityView();
            drawFirstCarCityView(firstCarPosition);
            drawSecondCarCityView(secondCarPosition);
            drawThirdCarCityView(thirdCarPosition);
            drawFourthCarCityView(fourthCarPosition);

            glPopMatrix();
        }
        // Night Code of Scene 1 will be in the else block
        else if(night)
        {
            glLoadIdentity();
            glPushMatrix();

            drawCityViewSkyNight();
            drawCityViewNightStars();
            drawMoonCityView(sun_moon_position_city_view);

            drawCityViewCloudNight(cloudPositionCityView);

            drawLeftTree();
            drawRightTree();
            drawMiddleTree();

            drawBushes();

            drawfirstbuilding();
            drawSecondBuilding();
            drawThirdBuilding();

            drawHospital();
            drawPharmacy();

            drawRoadCityView();
            streetLightNightCityView();

            drawFirstCarCityView(firstCarPosition);
            drawSecondCarCityView(secondCarPosition);
            drawThirdCarCityView(thirdCarPosition);
            drawFourthCarCityView(fourthCarPosition);

            glPopMatrix();
        }
    }

    if (showSecondScene)
    {
        //glScissor(0,0,1.0f,1.0f);
        glEnable(GL_SCISSOR_TEST);
        glScissor(0,0,1.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // (or whatever buffer you want to clear)
        glDisable(GL_SCISSOR_TEST);

        glClear(GL_DOUBLEBUFFER);
        glClear(GL_POLYGON);

        // Day view of hill
        if(day){
            glLoadIdentity();
            glPushMatrix();

            drawHillViewSkyDay();
            drawSunHillView(sun_moon_position_hill_view);

            drawHills();
            drawLand();

            drawRestaurant();
            drawBooth();
            drawResturant2();

            drawRoadHillView();
            drawFirstBus(firstBusPosition);
            drawSecondBus(secondBusPosition);
            drawFirstPickup(firstPickupPosition);
            drawSecondPickup(secondPickupPosition);

            drawSea();
            drawShip(shipPosition);

            glPopMatrix();
        }
        // Night view of Hill
        else if(night){

            glLoadIdentity();
            glPushMatrix();

            drawHillViewSkyNight();
            drawHillViewStars();
            drawMoonHillView(sun_moon_position_hill_view);

            drawHills();
            drawLand();

            drawRestaurant();
            drawBooth();
            drawResturant2();

            drawRoadHillView();
            drawFirstBus(firstBusPosition);
            drawSecondBus(secondBusPosition);
            drawFirstPickup(firstPickupPosition);
            drawSecondPickup(secondPickupPosition);

            drawSea();
            drawShip(shipPosition);

            glPopMatrix();
        }
    }
    //drawAxis();
    glFlush();
}

void update(int value)
{
    glutPostRedisplay();

    sun_moon_position_city_view -= sun_moon_speed_city_view;
    cloudPositionCityView += cloudSpeedCityView;

    if(sun_moon_position_city_view < -1.2f)
    {
        sun_moon_position_city_view = 1.01f;
        if(day)
        {
            day = false;
            night = true;
        }else if(night){
            night = false;
            day = true;
        }
    }

    sun_moon_position_hill_view -= sun_moon_speed_hill_view;
    if(sun_moon_position_hill_view < -1.2f){
        sun_moon_position_hill_view = 1.01f;
        /*
        if(day)
        {
            day = false;
            night = true;
        }else if(night){
            night = false;
            day = true;
        }
        */
    }

    if(cloudPositionCityView > 2.1f)
        cloudPositionCityView = -1.5f;

    if(firstCarPosition > 1.5f){
        firstCarPosition = -1.5f;
    }

    if(secondCarPosition < -1.5){
        secondCarPosition = 1.5f;
    }

    if(thirdCarPosition  > 1.5){
        thirdCarPosition  = -1.5f;
    }

    if(fourthCarPosition < -1.5){
        fourthCarPosition = 1.5f;
    }

    firstCarPosition += 0.1f;
	secondCarPosition -= 0.08f;
	thirdCarPosition += 0.05f;
    fourthCarPosition -= 0.05f;

    if(firstBusPosition > 1.5){
        firstBusPosition = -1.5f;
    }

    if(secondBusPosition  < -1.5){
        secondBusPosition = 1.5f;
    }

    if(firstPickupPosition < -1.5){
        firstPickupPosition = 1.5f;
    }

    if(secondPickupPosition > 1.5){
        secondPickupPosition  = -1.5f;
    }

    if(shipPosition > 1.5){
        shipPosition = -1.5f;
    }

    if(screenChangeTimer <= 200){
        showFirstScene = true;
        showSecondScene = false;
    }else if(screenChangeTimer > 200 && screenChangeTimer <= 470){
        showSecondScene = true;
        showFirstScene = false;
    }else if(screenChangeTimer > 470){
        screenChangeTimer = 1.0f;
    }

    cout<<screenChangeTimer<<endl;
    screenChangeTimer += 1.0f;


    firstBusPosition += 0.08f;
    secondBusPosition -= 0.05f;
    firstPickupPosition -= 0.08f;
    secondPickupPosition += 0.05f;

    shipPosition += 0.009f;

	glutTimerFunc(100, update, 0);

}


/**
 * Function to handle when any keyboard key is pressed
 */
void handleKeypress(unsigned char key, int x, int y)
{
    if(key == 'n'){
        // night view
        night = true;
        day = false;
    }else if(key == 'd'){
        // day view
        day = true;
        night = false;
    }else if (key == 'h'){
        // Hill View (Scene 2)
        screenChangeTimer = 201.0f;
        showFirstScene = false;
        showSecondScene = true;
    }else if(key == 'c'){
        // City View (Scene 1)
        screenChangeTimer = 1.0f;
        showFirstScene = true;
        showSecondScene = false;
    }
}

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(0.0, 1280.0, 0.0, 720.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("CITY & HILL VIEW");
    glutDisplayFunc(display);

    glutKeyboardFunc(handleKeypress);
    glutTimerFunc(1000, update, 0);
    //glutMouseFunc(mouseHandler);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);// you enable blending function

    init();
    glutMainLoop();
}
