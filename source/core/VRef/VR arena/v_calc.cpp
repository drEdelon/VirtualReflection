#include "v_calc.h"
#include "..\userdef.h"

#include <iostream>
bool modeAxelGiro=true; // true - axel mode, false giro mode

//V3Dd afix(-814,-52,542); //pepsi
#ifdef EZZH 
V3Dd afix(-756,242,806); //yellow
#endif
//V3Dd afix(0,0,0); // zero
#ifdef DEN 
V3Dd afix(-428,416,1166); // new_pepsi
#endif 
//V3Dd afix(0,0,0); // sheeld



float SFACTOR=(1.0/32768.0);
float R2D=57.2958; // radian to degree
int calcinit(void)
{
	return 0;
}
void calcrest(){}

void tobinb(BYTE inp)
{	
	char boo[9];
	for(int i=0; i<=7;i++)
    {
		if ((inp & (1<<(i))) != 0)
		{
			boo[7-i]='1';
		}
        else 
		{
			boo[7-i]='0';
		}
    }
    boo[8]=0;
	printf(boo);
}

void tobin(WORD inp)
{	
	char boo[17];
	for(int i=0; i<=15;i++)
    {
		if ((inp & (1<<(i))) != 0)
		{
			boo[15-i]='1';
		}
        else 
		{
			boo[15-i]='0';
		}
    }
    boo[16]=0;
	printf(boo);
}

double getAngleXY(double x,double y, int type)
{
	/*if(x == 0)
		if (y > 0)
			return 0;
		else 
			return 180;
	else */
		/*if (x > 0)*/
			return (atan2(y , x)) * R2D ;
		//if (type == 2 && y < 0) 
		//	return (atan(-y / -x)) * R2D ;
		/*else 
			return (atan2(x , y)) * R2D + 180 ;*/
}


double getAngleXY2(double x,double y, int type)
{
	if(x == 0)
		if (y > 0)
			return 0;
		else 
			return 180;
	else 
	{
		if (x > 0 && y > 0)
			return (atan(y / x)) * R2D ;
		if (x > 0 && y < 0) 
			return (90 - atan(-y / x) * R2D + 90);
		if (x < 0 && y < 0) 
			return (atan(-y / -x)) * R2D + 180 ;
		if (x < 0 && y > 0) 
			return (90 - atan(y / -x) * R2D + 270) ;
	}

}

struct QUAT
{
	double w, x, y, z;
	
	QUAT(){w = 1, x = 0, y = 0, z = 0;}
	~QUAT(){};
};

QUAT multyQuat(QUAT &a, QUAT &b)
{
	QUAT res;
	
	res.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
    res.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
    res.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
    res.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
    
	return res;
}
int first_mag_vec = 0;
double mx_base = 0, my_base = 0, mz_base = 0;
double vec[] = {0,0,-1.0};
int mx_max = 0, mx_min = 0, my_max = 0, my_min = 0, mz_max = 0, mz_min = 0;
//void c_send_data(V3Di ain,V3Di gin,unsigned int ts){}
void c_send_data(MATCHFRAME in)
{

in.mp.gx += 34.0;
in.mp.gy -= 21.0;
in.mp.gz += 42.0;

//if(in.mp.gx > mx_max) mx_max = in.mp.gx;
//if(in.mp.gx < mx_min) mx_min = in.mp.gx;
//
//if(in.mp.gy > my_max) my_max = in.mp.gy;
//if(in.mp.gy < my_min) my_min = in.mp.gy;
//
//if(in.mp.gz > mz_max) mz_max = in.mp.gz;
//if(in.mp.gz < mz_min) mz_min = in.mp.gz;





	if(first_mag_vec == 0)
	{
		mx_base = in.mp.gx;
		my_base = in.mp.gy;
		mz_base = 0;//in.mp.gz;
		
	double tmp_lenth = sqrt(mx_base * mx_base + my_base * my_base + mz_base * mz_base);

		mx_base /= tmp_lenth;
		my_base /= tmp_lenth;
		mz_base /= tmp_lenth;

		//vec[0] = in.mp.ax;
		//vec[1] = in.mp.ay;
		//vec[2] = in.mp.az;

		first_mag_vec = 1;
	}
	
	
	double vec_norm[3] = {0}, mvec_norm[3] = {0};
	double temp = 0, mtemp = 0;
	double vec_pov[3] = {0}, mvec_pov[3] = {0};
	double vec_scal = 0, mvec_scal = 0, n1 = 0, n2 = 0, mn1 = 0, mn2 = 0;
	double angle = 0, mangle = 0;
	QUAT q, q_vec;
	QUAT q_inv;
	QUAT q_rez;
	QUAT mq;
	double mx = in.mp.gx, my = in.mp.gy, mz = 0;//in.mp.gz;
	q_vec.z = -1;




	temp = sqrt((double)in.mp.ax * (double)in.mp.ax + (double)in.mp.ay * (double)in.mp.ay + (double)in.mp.az * (double)in.mp.az);
	mtemp = sqrt(mx * mx + my * my + mz * mz);
	
	vec_norm[0] = in.mp.ax/temp;
	vec_norm[1] = in.mp.ay/temp;
	vec_norm[2] = in.mp.az/temp;

	mvec_norm[0] = mx/mtemp;
	mvec_norm[1] = my/mtemp;
	mvec_norm[2] = mz/mtemp;

	vec_pov[0] = vec[1] * vec_norm[2] - vec[2] * vec_norm[1];
	vec_pov[1] = vec[2] * vec_norm[0] - vec[0] * vec_norm[2];
	vec_pov[2] = vec[0] * vec_norm[1] - vec[1] * vec_norm[0];

	//mvec_pov[0] = my_base * mvec_norm[2] - mz_base * mvec_norm[1];
	//mvec_pov[1] = mz_base * mvec_norm[0] - mx_base * mvec_norm[2];
	//mvec_pov[2] = mx_base * mvec_norm[1] - my_base * mvec_norm[0];
	
	vec_scal = vec[0] * vec_norm[0] + vec[1] * vec_norm[1] + vec[2] * vec_norm[2];
	/*mvec_scal = mx_base * mvec_norm[0] + my_base * mvec_norm[1] + mz_base * mvec_norm[2];*/

	n1 = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	n2 = temp;

	//mn1 = sqrt(mx_base * mx_base + my_base * my_base + mz_base * mz_base);
	//mn2 = mtemp;

	angle = acos(vec_scal/(n1*n2));
	//mangle = acos(mvec_scal/(mn1*mn2));

	q.w = cos(angle/2);
	q.x = sin(angle/2) * vec_pov[0];
	q.y = sin(angle/2) * vec_pov[1];
	q.z = sin(angle/2) * vec_pov[2];

	//mq.w = cos(mangle/2);
	//mq.x = sin(mangle/2) * mvec_pov[0];
	//mq.y = sin(mangle/2) * mvec_pov[1];
	//mq.z = sin(mangle/2) * mvec_pov[2];

	double length = sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z); 
	q.w = q.w / length;
    q.x = q.x / length;
    q.y = q.y / length;
    q.z = q.z / length;

	//double mlength = sqrt(mq.w * mq.w + mq.x * mq.x + mq.y * mq.y + mq.z * mq.z); 
	//mq.w = mq.w / mlength;
 //   mq.x = mq.x / mlength;
 //   mq.y = mq.y / mlength;
 //   mq.z = mq.z / mlength;

//	q = multyQuat(mq, q);

	q_inv.w = q.w;
	q_inv.x = -q.x;
	q_inv.y = -q.y;
	q_inv.z = -q.z;

	QUAT mq_vec;

	mq_vec.w = 0;
	mq_vec.x = mvec_norm[0];
	mq_vec.y = mvec_norm[1];
	mq_vec.z = mvec_norm[2];



	q_rez = multyQuat(q_inv, mq_vec);
	q_rez = multyQuat(q_rez, q);

	double new_mx = q_rez.x;
	double new_my = q_rez.y;
	double new_mz = 0;//q_rez.z;

	double new_tmp = sqrt(new_mx * new_mx + new_my * new_my + new_mz * new_mz);

	new_mx /= new_tmp;
	new_my /= new_tmp;
	new_mz /= new_tmp;

	mvec_pov[0] = my_base * new_mz - mz_base * new_my;
	mvec_pov[1] = mz_base * new_mx - mx_base * new_mz;
	mvec_pov[2] = mx_base * new_my - my_base * new_mx;


	mvec_scal = mx_base * new_mx + my_base * new_my + mz_base * new_mz;


	mn1 = sqrt(mx_base * mx_base + my_base * my_base + mz_base * mz_base);
	mn2 = sqrt(new_mx * new_mx + new_my * new_my + new_mz * new_mz);


	mangle = acos(mvec_scal/(mn1*mn2));



	mq.w = cos(mangle/2);
	mq.x = sin(mangle/2) * mvec_pov[0];
	mq.y = sin(mangle/2) * mvec_pov[1];
	mq.z = sin(mangle/2) * mvec_pov[2];

	new_tmp = sqrt(mq.w * mq.w + mq.x * mq.x + mq.y * mq.y + mq.z * mq.z);
	mq.w /= new_tmp;
	mq.x /= new_tmp;
	mq.y /= new_tmp;
	mq.z /= new_tmp;


	q = multyQuat(q_rez, mq);

	double roll = atan2(2 * q.z * q.w - 2 * q.x * q.y, 1 - 2 * q.z * q.z - 2 * q.y * q.y);
    double pitch = asin(2 * q.x * q.z + 2 * q.y * q.w);
    double yaw = atan2(2 * q.x * q.w - 2 * q.z * q.y, 1 - 2 * q.x * q.x - 2 * q.y * q.y);

			

	//myBase = myTmpBuff.parse();
	//in.draw();
	if (lastError == ERROR_OK) 
	{
		 brush.setPos(in.mp.ax*SFACTOR, in.mp.ay*SFACTOR, in.mp.az*SFACTOR);
//		 brush.setPos((in.mp.gx + 0)*SFACTOR * 300 , (in.mp.gy - 0)*SFACTOR * 300, (in.mp.gz + 0)*SFACTOR  * 300);
		// brush.setB(in.mp.ax*SFACTOR, in.mp.ay*SFACTOR, in.mp.az*SFACTOR,in.mp.gx*SFACTOR, in.mp.gy*SFACTOR, in.mp.gz*SFACTOR);
		
		V3Dd normV=(V3Dd((in.mp.ax),
						(in.mp.ay),
						(in.mp.az))+afix)*(SFACTOR*2);
		V3Dd Vrot(0,0,0);
		

Vrot.y=-roll * R2D;	//тангаж
Vrot.x=-pitch * R2D;	//рысканье
Vrot.z=-yaw * R2D;	//крен

		//*
		{	//только тангаж
//			Vrot.x=getAngleXY(normV.z,normV.y, 1);	//тангаж
		} //*/

			/*
		{	//только крен
			Vrot.x=getAngleXY(normV.z,normV.y, 1);	//тангаж
		} //*/

		/*
		{	//поиск с доворотом
			Vrot.x=getAngleXY(normV.z,normV.y, 1);	//тангаж
			normV = V3Dd(normV.x,
						 normV.y * cos(Vrot.x/R2D) - normV.z * sin(Vrot.x/R2D),
						 normV.y * sin(Vrot.x/R2D) + normV.z * cos(Vrot.x/R2D)); 
			Vrot.z=getAngleXY(normV.z, normV.x, 1);	//крен
		} //*/
		
		/*
		{	//все три психанули! 
			Vrot.x=getAngleXY(normV.z,normV.y, 1);	//тангаж
			Vrot.y=getAngleXY(normV.y, normV.x, 1);	//рысканье
			Vrot.z=getAngleXY(normV.z, normV.x, 1);	//крен
		} //*/


		//printf(" %i %i %i %i %i %i\n", mx_max, mx_min, my_max, my_min, mz_max, mz_min);
		printf(" %i %i %i %i %i %i\n", in.mp.ax, in.mp.gx, in.mp.ay, in.mp.gy, in.mp.az, in.mp.gz);
//		brush.rot = V3Df(Vrot.x, Vrot.y, Vrot.z);


//		printf(" %f  %f\n",Vrot.x,Vrot.z);
//		brush.rot = V3Df(Vrot.x, Vrot.y, Vrot.z);	 
	}

}

