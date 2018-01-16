//набор инструментов для OpenGL 


#ifndef _MYGL
#define _MYGL
#include <windows.h>												// Header File For Windows
#include <gl\gl.h>													// Header File For The OpenGL32 Library
#include <gl\glu.h>	
#include <gl\glut.h>
#include <stdio.h>	
#include "v_calc.h"	
#include "v_output.h"
#include "math.h"





#pragma comment( lib, "opengl32.lib" )								// Search For OpenGL32.lib While Linking ( NEW )
#pragma comment( lib, "glu32.lib" )									// Search For GLu32.lib While Linking    ( NEW )

extern float SBsize;
extern GLuint  skyBox;
extern GLuint  Brush;
extern HDC hDC;


void initSkyBox(void);
void initBrush(void);
GLvoid KillGLWindow(GLvoid);
BOOL CreateGLWindow(char* title, int width, int height, int bits);
GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
int InitGL(GLvoid);
void glVertex3Vf(V3Df vinp);


void setcolor(float red,float green,float blue);
void line2d(float x1,float y1,float x2,float y2);
void line3d(float x1, float y1, float z1, float x2, float y2, float z2);


#define PI          3.141592653589793238462643383279502884L /* pi */
class StereoCamera
{
public:
    StereoCamera(   
        float Convergence, 
        float EyeSeparation, 
        float AspectRatio, 
        float FOV, 
        float NearClippingDistance, 
        float FarClippingDistance
        )
    {
        mConvergence            = Convergence; 
        mEyeSeparation          = EyeSeparation; 
        mAspectRatio            = AspectRatio; 
        mFOV                    = FOV * PI / 180.0f; 
        mNearClippingDistance   = NearClippingDistance;
        mFarClippingDistance    = FarClippingDistance;
    }

    void ApplyLeftFrustum()
    {
        float top, bottom, left, right;

        top     = mNearClippingDistance * tan(mFOV/2);
        bottom  = -top;

        float a = mAspectRatio * tan(mFOV/2) * mConvergence;

        float b = a - mEyeSeparation/2;
        float c = a + mEyeSeparation/2;

        left    = -b * mNearClippingDistance/mConvergence;
        right   =  c * mNearClippingDistance/mConvergence;

        // Set the Projection Matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();   
        glFrustum(left, right, bottom, top, 
                  mNearClippingDistance, mFarClippingDistance);

        // Displace the world to right
        glMatrixMode(GL_MODELVIEW);                     
        glLoadIdentity();   
        glTranslatef(mEyeSeparation/2, 0.0f, 0.0f);
    }

    void ApplyRightFrustum()
    {
        float top, bottom, left, right;

        top     = mNearClippingDistance * tan(mFOV/2);
        bottom  = -top;

        float a = mAspectRatio * tan(mFOV/2) * mConvergence;

        float b = a - mEyeSeparation/2;
        float c = a + mEyeSeparation/2;

        left    =  -c * mNearClippingDistance/mConvergence;
        right   =   b * mNearClippingDistance/mConvergence;

        // Set the Projection Matrix
        glMatrixMode(GL_PROJECTION);                        
        glLoadIdentity();   
        glFrustum(left, right, bottom, top, 
                  mNearClippingDistance, mFarClippingDistance);

        // Displace the world to left
        glMatrixMode(GL_MODELVIEW);                     
        glLoadIdentity();   
        glTranslatef(-mEyeSeparation/2, 0.0f, 0.0f);
    }

private:
    float mConvergence;
    float mEyeSeparation;
    float mAspectRatio;
    float mFOV;
    float mNearClippingDistance;
    float mFarClippingDistance;

};


#endif