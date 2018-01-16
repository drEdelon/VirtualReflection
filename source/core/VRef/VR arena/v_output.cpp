#include "v_output.h"
#include "hand.h"
//#include "hand_mdl.h"

float xobj=0;
float yobj=0;
float zobj = 0;
float Cdist=3.0f;
bool acel_draw=true;
bool giro_draw=false;//true;

int tmr = 0;

float vector3_mass[5][3] = {0};

BRUSH brush;//,brush1;
bool folow=false;
char VisMode;
int cpoint=0;

V3Df visTri(0,0,0);



int outputinit(void)
{
	if (!CreateGLWindow("OpenGL 15",800,600,16))	
	{	
		return CREATEGLWINDOW_FALSE;
	}	// Quit If Window Was Not Created
//	brush1.initBrush();
	
	//
	return ERROR_OK;
}

/*
void DrawGLScene(GLvoid)                                    
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the stereo camera system
    StereoCamera cam(
        2000.0f,     // Convergence 
        35.0f,       // Eye Separation
        1.3333f,     // Aspect Ratio
        45.0f,       // FOV along Y in degrees
        10.0f,       // Near Clipping Distance
        20000.0f);   // Far Clipping Distance

    cam.ApplyLeftFrustum();
    glColorMask(true, false, false, false);

    PlaceSceneElements();

    glClear(GL_DEPTH_BUFFER_BIT) ;

    cam.ApplyRightFrustum();
    glColorMask(false, true, true, false);

    PlaceSceneElements();

    glColorMask(true, true, true, true);
}//*/


//void PlaceSceneElements()
//{
//    // translate to appropriate depth along -Z
//    glTranslatef(0.0f, 0.0f, -1800.0f);
//
//    // rotate the scene for viewing
//    glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
//    glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
//
//    // draw intersecting tori
//    glPushMatrix();
//        glTranslatef(0.0f, 0.0f, 240.0f);
//        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
//        glColor3f(0.2, 0.2, 0.6);
//        glutSolidTorus(40, 200, 20, 30);
//        glColor3f(0.7f, 0.7f, 0.7f);
//        glutWireTorus(40, 200, 20, 30);
//    glPopMatrix();
//
//    glPushMatrix();
//        glTranslatef(240.0f, 0.0f, 240.0f);
//        glColor3f(0.2, 0.2, 0.6);
//        glutSolidTorus(40, 200, 20, 30);
//        glColor3f(0.7f, 0.7f, 0.7f);
//        glutWireTorus(40, 200, 20, 30);
//    glPopMatrix();
//}

void FillScene()	// отрисовка кадра сцены для визуализации куба
{
	
	//PlaceSceneElements();
	glPolygonMode(GL_FRONT, GL_LINE);
	glCallList(skyBox);
	glPolygonMode(GL_FRONT, GL_FILL);
	
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);      // Начинаем рисование четырехугольников (quads)
						// Верхняя поверхность
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(visTri.x, 0, 0);        // Верхний правый угол текстуры и четырехугольник
		glVertex3f(0, visTri.y, 0);        // Верхний правый угол текстуры и четырехугольник
		glVertex3f(0, 0, visTri.z);        // Верхний правый угол текстуры и четырехугольник
	glEnd();
	glEnable(GL_TEXTURE_2D);	
	

	brush.tracking();
	brush.rangefix(SBsize);
	brush.draw();

}


//void MyMaterial(GLenum mode,GLfloat *f,GLfloat alpha)
//{
//	GLfloat d[4];
//	d[0]=f[0];
//	d[1]=f[1];
//	d[2]=f[2];
//	d[3]=alpha;
//	glMaterialfv (GL_FRONT_AND_BACK,mode,d);
//}
//
//
//void SelectMaterial(int i)
//{
//  //
//  // Define the reflective properties of the 3D Object faces.
//  //
//  glEnd();
//  GLfloat alpha=materials[i].alpha;
//  MyMaterial (GL_AMBIENT, materials[i].ambient,alpha);
//  MyMaterial (GL_DIFFUSE, materials[i].diffuse,alpha);
//  MyMaterial (GL_SPECULAR, materials[i].specular,alpha);
//  MyMaterial (GL_EMISSION, materials[i].emission,alpha);
//  glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,materials[i].phExp);
//  glBegin(GL_TRIANGLES);
//
//};


int DrawGLScene(GLvoid)			//изобразить сцену согласно выбора режима отображения(куб, график, рука)									// Here's Where We Do All The Drawing
{
	//StereoCamera cam(
 //       2000.0f,     // Convergence 
 //       0.025f,       // Eye Separation
 //       1.3333f,     // Aspect Ratio
 //       45.0f,       // FOV along Y in degrees
 //       1.0f,       // Near Clipping Distance
 //       20000.0f);   // Far Clipping Distance
	////
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clear The Screen And The Depth Buffer
//*	
	glLoadIdentity();												// Reset The Modelview Matrix
	glMatrixMode(GL_MODELVIEW);	
	//glLoadIdentity();
	switch (VisMode)
	{
		case VIS_CUBE:
 		{
			//*/
			//cam.ApplyRightFrustum();
			//cam.ApplyLeftFrustum();
			//cam move
			//glPushMatrix();
			//glColorMask(false, true, true, false);
			//glTranslatef(0.02, 0, 0);
			glTranslatef(0, 0, -Cdist);
			glRotatef(yobj, 1,0,0);
			glRotatef(xobj, 0,1,0);
			glRotatef(zobj, 0,0,1);

			if (folow)
			{
				glTranslatef(-brush.tra.x, -brush.tra.y, -brush.tra.z);
			}
			FillScene();
			
		//	glClear(GL_DEPTH_BUFFER_BIT) ;
		////	cam.ApplyRightFrustum();
		//	cam.ApplyLeftFrustum();
		//	//glPopMatrix();
		//	glColorMask(true, false, false, false);
		//	//glTranslatef(-0.04, 0, 0);
		//	glTranslatef(0, 0, -Cdist);
		//	glRotatef(yobj, 1,0,0);
		//	glRotatef(xobj, 0,1,0);
		//	if (folow)
		//	{
		//		glTranslatef(-brush.tra.x, -brush.tra.y, -brush.tra.z);
		//	}
		//	//PlaceSceneElements();
		//	glPolygonMode(GL_FRONT, GL_LINE);
		//	glCallList(skyBox);
		//	glPolygonMode(GL_FRONT, GL_FILL);
		//	
		//	brush.tracking();
		//	//brush.rangefix(SBsize);
		//	brush.draw();
		//	
		//	/*
		//	brush1.tracking();
		//	brush1.rangefix(SBsize);
		//	brush1.draw();
		//	//*/
		//	glColorMask(true, true, true, true);
			break;
		}
		case VIS_GRAPH:
		{
			glTranslatef(0, 0, -1);

			setcolor(0.5,0.5,0.5);
			line2d(1,0,-1,0);
	
			if (acel_draw)
			{
				setcolor(1,1,1);
				glColorMask(true, false, false, false);
				if (brush.rec.track.infill()>1)
				{
					for (int cnt=1;cnt < brush.rec.track.infill();cnt++)
					{
						line2d(((2.0/brush.rec.track.infill())*cnt)-1, brush.rec.track.read(cnt).p.x,
							   (2.0/brush.rec.track.infill())*(cnt-1)-1, brush.rec.track.read(cnt-1).p.x);
						
						

						glColorMask(true, false, true, false);
						if(brush.rec.track.read(cnt).r.z > 0.5)
						{
								line2d(	((2.0/brush.rec.track.infill())*cnt)-1, 0.05,
										((2.0/brush.rec.track.infill())*cnt)-1, 0.0);
						}

								line2d(	((2.0/brush.rec.track.infill())*cnt)-1, 0,
								(2.0/brush.rec.track.infill())*(cnt-1)-1, 0);

						glColorMask(true, false, false, false);
					}
				}
				//setcolor(0,1,0);
				glColorMask(false, true, false, false);
				if (brush.rec.track.infill()>1)
				{
					for (int cnt=1;cnt < brush.rec.track.infill();cnt++)
					{
						line2d(((2.0/brush.rec.track.infill())*cnt)-1, brush.rec.track.read(cnt).p.y,
							   (2.0/brush.rec.track.infill())*(cnt-1)-1, brush.rec.track.read(cnt-1).p.y);
					}
				}
				//setcolor(0,0,1);
				glColorMask(false, false, true, false);
				if (brush.rec.track.infill()>1)
				{
					for (int cnt=1;cnt < brush.rec.track.infill();cnt++)
					{
						line2d(((2.0/brush.rec.track.infill())*cnt)-1, brush.rec.track.read(cnt).p.z,
							   (2.0/brush.rec.track.infill())*(cnt-1)-1, brush.rec.track.read(cnt-1).p.z);
					}
				}
				glColorMask(true, true, true, false);
			}
//-----------------------------------------------------------------------------//
			if (giro_draw)
			{
				setcolor(1,1,1);
				glColorMask(true, true, false, false);
				if (brush.rec.track.infill()>1)
				{
					for (int cnt=1;cnt < brush.rec.track.infill();cnt++)
					{
						line2d(((2.0/brush.rec.track.infill())*cnt)-1, brush.rec.track.read(cnt).r.x,
							   (2.0/brush.rec.track.infill())*(cnt-1)-1, brush.rec.track.read(cnt-1).r.x);
					}
				}
				//setcolor(0,1,0);
				glColorMask(false, true, true, false);
				if (brush.rec.track.infill()>1)
				{
					for (int cnt=1;cnt < brush.rec.track.infill();cnt++)
					{
						line2d(((2.0/brush.rec.track.infill())*cnt)-1, brush.rec.track.read(cnt).r.y,
							   (2.0/brush.rec.track.infill())*(cnt-1)-1, brush.rec.track.read(cnt-1).r.y);
					}
				}
				//setcolor(0,0,1);
				glColorMask(true, false, true, false);
				if (brush.rec.track.infill()>1)
				{
					for (int cnt=1;cnt < brush.rec.track.infill();cnt++)
					{
						line2d(((2.0/brush.rec.track.infill())*cnt)-1, brush.rec.track.read(cnt).r.z,
							   (2.0/brush.rec.track.infill())*(cnt-1)-1, brush.rec.track.read(cnt-1).r.z);
					}
				}
				glColorMask(true, true, true, false);
			}
			
			break;
		}
		case VIS_HAND:
		{
			glTranslatef(0, 0, -Cdist);
			glRotatef(yobj, 1,0,0);
			glRotatef(xobj, 0,1,0);
			glRotatef(zobj, 0,0,1);
			//glMatrixMode(GL_PROJECTION);	
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			//glCallList(skyBox);
		//	glPolygonMode(GL_FRONT, GL_FILL);

			drawHand();
			
			//glColor3f(1.0f,0.0f,0.0f);
			
			//glDisable(GL_TEXTURE_2D);
			//glPointSize(5.0f);
			

			//for (int cnt=0;cnt<5;cnt++)
			//{
			//	glPushMatrix();
			//	for(int cntt=0;cntt<4;cntt++)
			//	{
			//	
			//		//glBegin(GL_POINTS);
			//		//	/*glColor3f(1.0f,0.0f,0.0f);*/
			//		//	glVertex3f(
			//		//	handbone[cnt][cntt].x,
			//		//	handbone[cnt][cntt].y,
			//		//	handbone[cnt][cntt].z);
			//		//	/*glColor3f(1.0f,1.0f,0.5f);*/
			//		//glEnd;
			//		glBegin(GL_POINTS);
			//		glTranslatef(
			//			handbone[cnt][cntt].x,
			//			handbone[cnt][cntt].y,
			//			handbone[cnt][cntt].z);
			//		glEnd();
			//	}
			//	glPopMatrix();
			//}
			
			//glEnable(GL_TEXTURE_2D);
			//FillScene();
			break;
		}
		case VIS_QUAT:
 		{
			//*/
			//cam.ApplyRightFrustum();
			//cam.ApplyLeftFrustum();
			//cam move
			//glPushMatrix();
			//glColorMask(false, true, true, false);
			//glTranslatef(0.02, 0, 0);
			glTranslatef(0, 0, -Cdist);
			glRotatef(yobj, 1,0,0);
			glRotatef(xobj, 0,1,0);
			glRotatef(zobj, 0,0,1);

			if (folow)
			{
				glTranslatef(-brush.tra.x, -brush.tra.y, -brush.tra.z);
			}
			FillScene();
			
		//	glClear(GL_DEPTH_BUFFER_BIT) ;
		////	cam.ApplyRightFrustum();
		//	cam.ApplyLeftFrustum();
		//	//glPopMatrix();
		//	glColorMask(true, false, false, false);
		//	//glTranslatef(-0.04, 0, 0);
		//	glTranslatef(0, 0, -Cdist);
		//	glRotatef(yobj, 1,0,0);
		//	glRotatef(xobj, 0,1,0);
		//	if (folow)
		//	{
		//		glTranslatef(-brush.tra.x, -brush.tra.y, -brush.tra.z);
		//	}
		//	//PlaceSceneElements();
		//	glPolygonMode(GL_FRONT, GL_LINE);
		//	glCallList(skyBox);
		//	glPolygonMode(GL_FRONT, GL_FILL);
		//	
		//	brush.tracking();
		//	//brush.rangefix(SBsize);
		//	brush.draw();
		//	
		//	/*
		//	brush1.tracking();
		//	brush1.rangefix(SBsize);
		//	brush1.draw();
		//	//*/
		//	glColorMask(true, true, true, true);
			break;
		}
		case VIS_SPHERE:
 		{

			glTranslatef(0, 0, -Cdist);
			glRotatef(yobj, 1,0,0);
			glRotatef(xobj, 0,1,0);
			glRotatef(zobj, 0,0,1);

			if (folow)
			{
				glTranslatef(-brush.tra.x, -brush.tra.y, -brush.tra.z);
			}
			FillScene();
			

			break;
		}
		case VIS_VECTORS:
		{

			glTranslatef(0, 0, -Cdist);
			glRotatef(yobj, 1,0,0);
			glRotatef(xobj, 0,1,0);
			glRotatef(zobj, 0,0,1);

			setcolor(0.5,0.5,0.5);
			

				setcolor(0,0,1);
				//glColorMask(true, true, false, false);

						line3d(0.0, 0.0, 0.0, vector3_mass[0][0], vector3_mass[0][1], vector3_mass[0][2]);
						//line3d(0.0, 0.0, 0.0, 0.5, 0.0, 0.0);
						//line3d(0.0, 0.0, 0.0, 0.0, 0.5, 0.0);
						//line3d(0.0, 0.0, 0.0, 0.0, 0.0, 0.5);
				
						setcolor(1,0,0);
				

						line3d(0.0, 0.0, 0.0, vector3_mass[1][0], vector3_mass[1][1], vector3_mass[1][2]);
				setcolor(0,1,0);
				

						line3d(0.0, 0.0, 0.0, vector3_mass[2][0], vector3_mass[2][1], vector3_mass[2][2]);

				//glColorMask(true, true, true, false);
FillScene();
			break;
		}

		
	}
	return TRUE;													// Keep Going
}

void outputrest()
{
	KillGLWindow();
}


void vectors_infill(float *vec, int num)
{
	for (int i = 0; i < num; i++)
	{
		vector3_mass[i][0] = *vec;
		vec++;
		vector3_mass[i][1] = *vec;
		vec++;
		vector3_mass[i][2] = *vec;
		vec++;
	}
}

//*

//*/
