#include "hand.h"
#include "myGL.h"
unsigned char dataFromResistors[24];

V3Df handbone[5][4]=
{
	//{	// большой 
	//	V3Df(	0.0f,	0.0f,	0.0f),
	//	V3Df(	0.25f,	0.1f,	-0.5f),
	//	V3Df(	0.75f,	0.75f,	-0.5f),
	//	V3Df(	0.0f,	0.4f,	0.0f)
	//},{	//указательный
	//	V3Df(	0.0f,	1.5f,	0.0f),
	//	V3Df(	0.0f,	1.0f,	0.0f),
	//	V3Df(	0.0f,	0.5f,	0.0f),
	//	V3Df(	0.0f,	0.4f,	0.0f)
	//},{ //средний
	//	V3Df(	-0.5f,	1.5f,	0.0f),
	//	V3Df(	0.0f,	1.25f,	0.0f),
	//	V3Df(	0.0f,	0.5f,	0.0f),
	//	V3Df(	0.0f,	0.4f,	0.0f)
	//},{ //безымянный
	//	V3Df(	-1.0f,	1.5f,	0.0f),
	//	V3Df(	0.0f,	1.0f,	0.0f),
	//	V3Df(	0.0f,	0.5f,	0.0f),
	//	V3Df(	0.0f,	0.4f,	0.0f)
	//},{ //мезинец
	//	V3Df(	-1.5f,	1.25f,	0.0f),
	//	V3Df(	0.0f,	0.75f,	0.0f),
	//	V3Df(	0.0f,	0.5f,	0.0f),
	//	V3Df(	0.0f,	0.4f,	0.0f)
	//}
	{	// большой 
		V3Df(	0.4f,	0.0f,	-0.5f),
		V3Df(	0.0f,	0.61f,	0.0f),
		V3Df(	0.0f,	0.437f,	0.0f),
		V3Df(	0.0f,	0.354f,	0.0f)
	},{	//указательный
		V3Df(	0.289f,	0.89f,	0.0f),
		V3Df(	0.0f,	0.537f,	0.0f),
		V3Df(	0.0f,	0.339f,	0.0f),
		V3Df(	0.0f,	0.294f,	0.0f)
	},{ //средний
		V3Df(	-0.0f,	0.84f,	0.0f),
		V3Df(	0.0f,	0.58f,	0.0f),
		V3Df(	0.0f,	0.407f,	0.0f),
		V3Df(	0.0f,	0.304f,	0.0f)
	},{ //безымянный
		V3Df(	-0.254f,	0.77f,	0.0f),
		V3Df(	0.0f,	0.540f,	0.0f),
		V3Df(	0.0f,	0.4f,	0.0f),
		V3Df(	0.0f,	0.292f,	0.0f)
	},{ //мезинец
		V3Df(	-0.474f,	0.68f,	0.0f),
		V3Df(	0.0f,	0.457f,	0.0f),
		V3Df(	0.0f,	0.378f,	0.0f),
		V3Df(	0.0f,	0.272f,	0.0f)
	}
};

void hDrawBone(int fing,int phal) //вызов отрисовки каждой кости
{
	glBegin(GL_QUADS);
		glVertex3f(handbone[fing][phal].y/10,0,0);
		glVertex3f(
			handbone[fing][phal].x+handbone[fing][phal].y/10,
			handbone[fing][phal].y,
			handbone[fing][phal].z);
		glVertex3f(
			handbone[fing][phal].x-handbone[fing][phal].y/10,
			handbone[fing][phal].y,
			handbone[fing][phal].z);
		glVertex3f(-handbone[fing][phal].y/10,0,0);
	glEnd();
	//glBegin(GL_LINES);
	//	glVertex3f(0,0,0);
	//	glVertex3f(
	//		handbone[fing][phal].x,
	//		handbone[fing][phal].y,
	//		handbone[fing][phal].z);
	//glEnd();
}

float binScale (unsigned char inp)	// перевод в нужный диапазон (0-1)
{
	return (float)inp/256;
}

void drawHand() // отрисовать руку
{

	glDisable(GL_TEXTURE_2D);
	glPointSize(5.0f);
	//glColor3f(1.0f,1.0f,0.5f);
	//int cnt=0;
	
	for (int cnt=0;cnt<5;cnt++)
	{
		glPushMatrix();
		for(int cntt=0;cntt<4;cntt++)
		{
			glColor3f(0.5,0.5,0.5f);
			hDrawBone(cnt,cntt);
			/*glBegin(GL_LINES);
				glVertex3f(0,0,0);
				glVertex3f(
					handbone[cnt][cntt].x,
					handbone[cnt][cntt].y,
					handbone[cnt][cntt].z);
			glEnd();*/
			
			glTranslatef(
				handbone[cnt][cntt].x,
				handbone[cnt][cntt].y,
				handbone[cnt][cntt].z);
			
			if (cnt>=0)
			{
				if (cntt==0)
				{
					glRotatef((-25+50*binScale(dataFromResistors[cntt+cnt*4]))*(1-binScale(dataFromResistors[cntt+1+cnt*4])), 0,0,1);
				}
				glRotatef(-90*binScale(dataFromResistors[cntt+1+cnt*4]), 1,0,0);
			}
		}
		glPopMatrix();
	}
	

	//glRotatef(90.0f, 1,0,0);
	//glTranslatef(0, 0, -1);

	
	glEnable(GL_TEXTURE_2D);

//	ajustbone();

	//int i;
	//int j;
	//int mcount=0;
	//int mindex=0;
	//glBegin (GL_TRIANGLES);
	//	for(i=0;i<sizeof(face_indicies)/sizeof(face_indicies[0]);i++)
	//	{
	//		if(!mcount)
	//		{
	//			SelectMaterial(material_ref[mindex][0]);
	//			mcount=material_ref[mindex][1];
	//			mindex++;
	//		}
	//		mcount--;
	//		for(j=0;j<3;j++)
	//		{
	//			int vi=face_indicies[i][j];
	//			//int ni=face_indicies[i][j+3];//Normal index
	//			int ti=face_indicies[i][j+6];//Texture index
	//			//glNormal3f (normals[ni][0],normals[ni][1],normals[ni][2]);
	//			glTexCoord2f(textures[ti][0],textures[ti][1]);
	//			glVertex3f (vertices[vi][0],vertices[vi][1],vertices[vi][2]);
	//		}
	//	}
	//glEnd ();

}
//void JOINT::draw()
//{
//	
//}
//
//void PHALANX::draw()
//{
//	joint.draw();
//}
//void FINGER::draw()
//{
//	joint.draw();
//	for (char indx=0;indx < 3;indx++)
//	{	phalanx[indx].draw();}
//}
////void PALM::draw()
////{
////
////}
//void HAND::draw()
//{
//	palm.draw();
//	finger[0].draw();
//}
