#ifndef _V3D
#define _V3D

#include <math.h>

//#define VTYPE float
template <typename VTYPE>
struct V3D
{
	VTYPE x,y,z;
	V3D<VTYPE>():x(0),y(0),z(0){}
	V3D<VTYPE>(VTYPE ix,VTYPE iy,VTYPE iz):x(ix),y(iy),z(iz){}
	V3D<VTYPE> & operator = (const V3D<VTYPE> & other)
	{		
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
	V3D<VTYPE>  operator + (const V3D<VTYPE> & other) 
	{	return V3D<VTYPE>(x + other.x, y + other.y, z + other.z);	}

	//V3D<VTYPE>  operator + (const char & other) 
	//{	return V3D<VTYPE>(x + other.x, y + other.y, z + other.z);	}
	//V3D<VTYPE>  operator + (const short & other) 
	//{	return V3D<VTYPE>(x + other.x, y + other.y, z + other.z);	}
	//V3D<VTYPE>  operator + (const int & other) 
	//{	return V3D<VTYPE>(x + other.x, y + other.y, z + other.z);	}
	//V3D<VTYPE>  operator + (const long long & other) 
	//{	return V3D<VTYPE>(x + other.x, y + other.y, z + other.z);	}
	//V3D<VTYPE>  operator + (const long & other) 
	//{	return V3D<VTYPE>(x + other.x, y + other.y, z + other.z);	}
	//V3D<VTYPE>  operator + (const float & other) 
	//{	return V3D<VTYPE>(x + other.x, y + other.y, z + other.z);	}
	//V3D<VTYPE>  operator + (const double & other) 
	//{	return V3D<VTYPE>(x + other.x, y + other.y, z + other.z);	}


	V3D<VTYPE>  operator - (const V3D<VTYPE> & other)
	{	return V3D<VTYPE>(x - other.x,y - other.y,z - other.z);	}
	
	/*V3D<VTYPE>  operator - (const char & other)
	{	return V3D<VTYPE>(x - other.x,y - other.y,z - other.z);	}
	V3D<VTYPE>  operator - (const short & other)
	{	return V3D<VTYPE>(x - other.x,y - other.y,z - other.z);	}
	V3D<VTYPE>  operator - (const int & other)
	{	return V3D<VTYPE>(x - other.x,y - other.y,z - other.z);	}
	V3D<VTYPE>  operator - (const long long & other)
	{	return V3D<VTYPE>(x - other.x,y - other.y,z - other.z);	}
	V3D<VTYPE>  operator - (const long & other)
	{	return V3D<VTYPE>(x - other.x,y - other.y,z - other.z);	}
	V3D<VTYPE>  operator - (const float & other)
	{	return V3D<VTYPE>(x - other.x,y - other.y,z - other.z);	}
	V3D<VTYPE>  operator - (const double & other)
	{	return V3D<VTYPE>(x - other.x,y - other.y,z - other.z);	}
	*/
	
	V3D<VTYPE>  operator - ()
	{		
		return V3D<VTYPE>(-x,-y,-z);
	}
	V3D<VTYPE>  operator * (const float & other)
	{	
		return V3D<VTYPE>(x * other,y * other,z * other);	
	}
	V3D<VTYPE>  operator * (const V3D<VTYPE> & other)
	{	
		return V3D<VTYPE>((y * other.z)-(z * other.y),
					(x * other.z)-(z * other.x),
					(x * other.y)-(y * other.x));
	}	
	V3D<VTYPE>  operator / (const float & other)
	{		
		return V3D<VTYPE>(x / other,y / other,z / other);
	}
	float mod()
	{		
		return sqrt(x*x+y*y+z*z);
	}
	V3D<VTYPE> norm()
	{	
		V3D<VTYPE> e(x,y,z);
		return e / e.mod();
	}
	bool  operator == (const V3D<VTYPE> & other)
	{		
		return (x == other.x)&&(y == other.y)&&(z == other.z);
	}
	bool  operator >= (const V3D<VTYPE> & other)
	{		
		return ((x >= other.x)&&(y >= other.y)&&(z >= other.z));
	}
	bool  operator <= (const V3D<VTYPE> & other)
	{		
		return ((x <= other.x)&&(y <= other.y)&&(z <= other.z));
	}
	bool  iszero()
	{
		return ((this->x==0)&&(this->y==0)&&(this->z==0));
	}	
//V3Df & V3Df::operator = (const V3Df & other)
//bool  V3Df::operator == (const V3Df & other)
//bool  V3Df::operator >= (const V3Df & other)
//bool  V3Df::operator <= (const V3Df & other)
//V3Df  V3Df::operator + (const V3Df & other)
//V3Df  V3Df::operator - (const V3Df & other)
//V3Df  V3Df::operator - ()
//V3Df  V3Df::operator * (const float & other)
//V3Df  V3Df::operator * (const V3Df & other)
//V3Df  V3Df::operator / (const float & other)
//float V3Df::mod()
//V3Df  V3Df::norm()
};

typedef V3D<double> V3Dd;
typedef V3D<float> V3Df;
typedef V3D<long long> V3Dll;
typedef V3D<long> V3Dl;
typedef V3D<int> V3Di;
typedef V3D<short> V3Ds;
typedef V3D<char> V3Dc;



struct DV3Df
{
	V3Df p,r;
	DV3Df():p(V3Df()),r(V3Df()){}
	DV3Df(V3Df ip,V3Df ir):p(ip),r(ir){}
	V3Df getP()	{ return p;}
	V3Df getR()	{ return r;}
	DV3Df & operator = (const DV3Df & other)
	{
		p = other.p;
		r = other.r;
		return *this;
	}
//DV3Df & DV3Df::operator = (const DV3Df & other)
};





#endif