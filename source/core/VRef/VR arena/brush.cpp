#include "brush.h"


BRUSH::BRUSH()
{	
	V3Df(0.1,0.1,0.1);
	//tra = V3Df(0.5,0.5,0.5);
	//rot = V3Df(40,30,20);
	//sz = V3Df(0.05f,0.01f,0.1f);
	tra = V3Df(0, 0, 0);
	rot = V3Df(0, 0, 0);
	sz = V3Df(0.4f, 0.2f, 0.7f);
	bdraw=true;
	record=false;
	initBrush();
}

void BRUSH::recordStart()	// разрешает дублирование данных в массив(rec) 
{
	record=true;
}
void BRUSH::recordStop()	// запрещает дублирование данных в массив(rec) 
{
	record=false;
}
DV3Df BRUSH::getFrame(WORD fr)	// возврат значения из массива
{
	return rec.track.read(fr);//DV3Df();//
}

//------------------------------------------ 
void BRUSH::setB(float x,float y,float z,float rx,float ry,float rz)
{
	setB(DV3Df(V3Df(x,y,z),V3Df(rx,ry,rz)));
}

void BRUSH::setB(V3Df ipos,V3Df irot)
{
	setB(DV3Df(ipos,irot));
}
void BRUSH::setB(DV3Df inp)	// создает объект с нужными размерами
{
	if (record) {store(inp);}
	tra=inp.p;
	rot=inp.r;	
}
//------------------------------------------
void BRUSH::setPos(V3Df inp) // устанавливает координаты расположения для объекта
{	
	setB(inp,rot); 
}
void BRUSH::setPos(float x,float y,float z)
{	
	setPos(V3Df(x,y,z));
}

//------------------------------------------
void BRUSH::move(V3Df inp) // сместить объект относительно имеющихся координат
{
	tra=tra+inp;
}
void BRUSH::move(float x,float y,float z)
{
	move(V3Df(x,y,z)); 
}

//------------------------------------------
void BRUSH::setRot(V3Df inp)	// задать углы поворота для объекта
{
	//if (record) {store(tra,inp);}
	setB(tra,inp); 
}
void BRUSH::setRot(float x,float y,float z)
{
	setRot(V3Df(x,y,z)); 
}


//------------------------------------------
void BRUSH::setSiz(V3Df inp)	//задать изменение масштаба для объекта
{	
	sz=inp; 
}
void BRUSH::setSiz(float x,float y,float z)
{
	setSiz(V3Df(x,y,z));
}

//------------------------------------------
void BRUSH::store(V3Df ipos,V3Df irot)	// запись данных в массив(rec) без отображения
{ 
	store(DV3Df(ipos,irot));
}
void BRUSH::store(DV3Df inp)
{
	//track.put(inp);
	rec.track.forcePut(inp);
}
//------------------------------------------
void BRUSH::initBrush(void)
{	
	//float SBsize=0.1f;
	glDeleteLists (GLBrush,1);
	GLBrush=glGenLists(1);
	glNewList(GLBrush,GL_COMPILE);      // Новый откомпилированный список отображения box`

	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINES);
	
		glColor3f(1.0f,0.0f,0.0f);		glVertex3f(sz.x,0,0);
		glColor3f(0.0f,0.0f,0.0f);		glVertex3f(-sz.x,0,0);
		
		glColor3f(0.0f,1.0f,0.0f);		glVertex3f(0,sz.y,0);
		glColor3f(0.0f,0.0f,0.0f);		glVertex3f(0,-sz.y,0);

		glColor3f(0.0f,0.0f,1.0f);		glVertex3f(0,0,sz.z);
		glColor3f(0.0f,0.0f,0.0f);		glVertex3f(0,0,-sz.z);
	glEnd();
	glColor3f(1.0f,1.0f,1.0f); 		
	
	glBegin(GL_QUADS); 
		// Верхняя поверхность
		glColor3f(0.0f,0.0f,1.0f);		glVertex3f(-sz.x/2,  sz.y/2, -sz.z/2);        // Верхний правый угол текстуры и четырехугольник
		glColor3f(0.50f,0.50f,1.0f);	glVertex3f(-sz.x/2,  sz.y/2,  sz.z/2);        // Нижний правый угол текстуры и четырехугольни
		glColor3f(0.0f,0.0f,0.0f);		glVertex3f( sz.x/2,  sz.y/2,  sz.z/2);        // Нижний левый угол текстуры и четырехугольник
		glColor3f(0.0f,0.0f,0.0f);		glVertex3f( sz.x/2,  sz.y/2, -sz.z/2);  

		// Нижняя поверхность
		glColor3f(0.0f,0.0f,1.0f);		glVertex3f(-sz.x/2, -sz.y/2, -sz.z/2);        // Верхний правый угол текстуры и четырехугольник
		glColor3f(0.50f,0.50f,1.0f);	glVertex3f(-sz.x/2, -sz.y/2,  sz.z/2);        // Нижний правый угол текстуры и четырехугольни
		glColor3f(0.0f,0.0f,0.0f);		glVertex3f( sz.x/2, -sz.y/2,  sz.z/2);        // Нижний левый угол текстуры и четырехугольник
		glColor3f(0.0f,0.0f,0.0f);		glVertex3f( sz.x/2, -sz.y/2, -sz.z/2);  
	
		// Передняя поверхность
		glColor3f(0.0f,0.0f,1.0f);		glVertex3f(-sz.x/2, -sz.y/2,  sz.z/2);        // Верхний правый угол текстуры и четырехугольник
		glColor3f(0.50f,0.50f,1.0f);	glVertex3f( sz.x/2, -sz.y/2,  sz.z/2);        // Нижний правый угол текстуры и четырехугольни
		glColor3f(0.0f,0.0f,0.0f);		glVertex3f( sz.x/2,  sz.y/2,  sz.z/2);        // Нижний левый угол текстуры и четырехугольник
		glColor3f(0.0f,0.0f,0.0f);		glVertex3f(-sz.x/2,  sz.y/2,  sz.z/2);  
	
		// Задняя поверхность
		glColor3f(0.0f,0.0f,1.0f);		glVertex3f(-sz.x/2, -sz.y/2, -sz.z/2);        // Верхний правый угол текстуры и четырехугольник
		glColor3f(0.50f,0.50f,1.0f);	glVertex3f( sz.x/2, -sz.y/2, -sz.z/2);        // Нижний правый угол текстуры и четырехугольни
		glColor3f(0.0f,0.0f,0.0f);		glVertex3f( sz.x/2,  sz.y/2, -sz.z/2);        // Нижний левый угол текстуры и четырехугольник
		glColor3f(0.0f,0.0f,0.0f);		glVertex3f(-sz.x/2,  sz.y/2, -sz.z/2);  
		
		// Правая поверхность
		glColor3f(0.0f,0.0f,1.0f);		glVertex3f( sz.x/2, -sz.y/2, -sz.z/2);        // Верхний правый угол текстуры и четырехугольник
		glColor3f(0.50f,0.50f,1.0f);	glVertex3f( sz.x/2,  sz.y/2, -sz.z/2);        // Нижний правый угол текстуры и четырехугольни
		glColor3f(0.0f,0.0f,0.0f);		glVertex3f( sz.x/2,  sz.y/2,  sz.z/2);        // Нижний левый угол текстуры и четырехугольник
		glColor3f(0.0f,0.0f,0.0f);		glVertex3f( sz.x/2, -sz.y/2,  sz.z/2);  

		// Левая поверхность
		glColor3f(0.0f,0.0f,1.0f);		glVertex3f(-sz.x/2, -sz.y/2, -sz.z/2);        // Верхний правый угол текстуры и четырехугольник
		glColor3f(0.50f,0.50f,1.0f);	glVertex3f(-sz.x/2,  sz.y/2, -sz.z/2);        // Нижний правый угол текстуры и четырехугольни
		glColor3f(0.0f,0.0f,0.0f);		glVertex3f(-sz.x/2,  sz.y/2,  sz.z/2);        // Нижний левый угол текстуры и четырехугольник
		glColor3f(0.0f,0.0f,0.0f);		glVertex3f(-sz.x/2, -sz.y/2,  sz.z/2);  

	glEnd();
	glColor3f(1.0f,1.0f,1.0f);
	glEnable(GL_TEXTURE_2D);
	
	glEndList(); // Закончили создание списка box
	rec.track.init();
}




//------------------------------------------
void BRUSH::rangefix(float insize)		// закольцовка пространства
{
	rangefix(V3Df(insize,insize,insize));
}

void BRUSH::rangefix(V3Df in)
{
	rangefix(-in,in);
}

void BRUSH::rangefix(V3Df inmin,V3Df inmax)
{
	min=inmin;
	max=inmax;
	while (tra.x > inmax.x)		{ tra.x -= inmax.x - inmin.x; }
	while (tra.x < inmin.x)		{ tra.x += inmax.x - inmin.x; }
	while (tra.y > inmax.y)		{ tra.y -= inmax.y - inmin.y; }
	while (tra.y < inmin.y)		{ tra.y += inmax.y - inmin.y; }
	while (tra.z > inmax.z)		{ tra.z -= inmax.z - inmin.z; }
	while (tra.z < inmin.z)		{ tra.z += inmax.z - inmin.z; }
}
//------------------------------------------
void BRUSH::draw(void)
{
	glDisable(GL_TEXTURE_2D);
	//glColor3f(0.50f,0.50f,0.50f);
	//glBegin(GL_LINES);
	//	glVertex3f(tra.x,tra.y,max.z);
	//	glVertex3f(tra.x,tra.y,min.z);
	//	
	//	glVertex3f(tra.x,max.y,tra.z);
	//	glVertex3f(tra.x,min.y,tra.z);
	//
	//	glVertex3f(max.x,tra.y,tra.z);
	//	glVertex3f(min.x,tra.y,tra.z);
	//glEnd();
	glEnable(GL_TEXTURE_2D);

	if (!bdraw) { return;}
	glPushMatrix();
	glTranslatef(tra.x,tra.y,tra.z);
	
	glRotatef(rot.z, 0,0,1);
	glRotatef(rot.x, 1,0,0);
	glRotatef(rot.y, 0,1,0);
	
	
	glCallList(GLBrush);
	glPopMatrix();
}

void _glVertex3Vf(V3Df vinp)
{
	glVertex3f(vinp.x,vinp.y,vinp.z);
}

void BRUSH::tracking(void)	// отрисовка временного состояния объекта
{

if (rec.track.infill()!=0)
	{		
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_LINES);
		for (unsigned short cntt=0;cntt < rec.track.infill()-1;cntt++)
		{	
			if ((getFrame(cntt).p-getFrame(cntt+1).p).mod()<0.5)
			{
				glColor3f(0.5f,0.0f,0.0f);
				_glVertex3Vf(getFrame(cntt).p);
				glColor3f(0.0f,1.0f,0.5f);
				_glVertex3Vf(getFrame(cntt+1).p);
				//TODO допилить трасировку ориентации
			}
		}
		glEnd();
		glEnable(GL_TEXTURE_2D);	
	}
}