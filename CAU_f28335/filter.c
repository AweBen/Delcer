/*filter_test,2010-08-16*/ 
/*       b0+b1*z-1+b2*z-2+b3*z-3+b4*z-4   	*/
/* D(z)=---------------------------------   */
/*        1+a1*z-1+a2*z-2+a3*z-3+a4*z-4   	*/



#define fa1 -3.665829681654813
#define fa2 +5.031152024139294
#define fa3 -3.063606514954111
#define fa4 +0.698297242873079 
#define fb0 +4.324705504569087e-16
#define fb1 +2.532760816876748e-2
#define fb2 -5.065823360717994e-2
#define fb3 +2.533059244186083e-2
#define fb4 0.0


volatile float x1[5]={0,0,0,0,0},y1[5]={0,0,0,0,0};
volatile float x2[5]={0,0,0,0,0},y2[5]={0,0,0,0,0};
volatile float x3[5]={0,0,0,0,0},y3[5]={0,0,0,0,0};
volatile float x4[5]={0,0,0,0,0},y4[5]={0,0,0,0,0};
volatile float x5[5]={0,0,0,0,0},y5[5]={0,0,0,0,0};
volatile float x6[5]={0,0,0,0,0},y6[5]={0,0,0,0,0};


float filter_ua(float);
float filter_ub(float);
float filter_uc(float);
float filter_ia(float);
float filter_ib(float);
float filter_ic(float);

/*filter function*/
//execute time:15.5us
float filter_ua(float xin){
	int k;
	x1[0] = xin;
	y1[0] = fb0* x1[0]; 
	y1[0] += fb1*x1[1] - fa1*y1[1];
	y1[0] += fb2*x1[2] - fa2*y1[2]; 
	y1[0] += fb3*x1[3] - fa3*y1[3];
	y1[0] += fb4*x1[4] - fa4*y1[4]; 
	for(k=3;k>=0;k--){
		x1[k+1] = x1[k];
		y1[k+1] = y1[k];
	}
	return (y1[0]);
}


float filter_ub(float xin){
	int k;
	x2[0] = xin;
	y2[0] = fb0* x2[0]; 
	y2[0] += fb1*x2[1] - fa1*y2[1];
	y2[0] += fb2*x2[2] - fa2*y2[2]; 
	y2[0] += fb3*x2[3] - fa3*y2[3];
	y2[0] += fb4*x2[4] - fa4*y2[4]; 
	for(k=3;k>=0;k--){
		x2[k+1] = x2[k];
		y2[k+1] = y2[k];
	}
	return (y2[0]);
}


float filter_uc(float xin){
	int k;
	x3[0] = xin;
	y3[0] = fb0* x3[0]; 
	y3[0] += fb1*x3[1] - fa1*y3[1];
	y3[0] += fb2*x3[2] - fa2*y3[2]; 
	y3[0] += fb3*x3[3] - fa3*y3[3];
	y3[0] += fb4*x3[4] - fa4*y3[4]; 
	for(k=3;k>=0;k--){
		x3[k+1] = x3[k];
		y3[k+1] = y3[k];
	}
	return (y3[0]);
}


float filter_ia(float xin){
	int k;
	x4[0] = xin;
	y4[0] = fb0* x4[0]; 
	y4[0] += fb1*x4[1] - fa1*y4[1];
	y4[0] += fb2*x4[2] - fa2*y4[2]; 
	y4[0] += fb3*x4[3] - fa3*y4[3];
	y4[0] += fb4*x4[4] - fa4*y4[4]; 
	for(k=3;k>=0;k--){
		x4[k+1] = x4[k];
		y4[k+1] = y4[k];
	}
	return (y4[0]);
}


float filter_ib(float xin){
	int k;
	x5[0] = xin;
	y5[0] = fb0* x5[0]; 
	y5[0] += fb1*x5[1] - fa1*y5[1];
	y5[0] += fb2*x5[2] - fa2*y5[2]; 
	y5[0] += fb3*x5[3] - fa3*y5[3];
	y5[0] += fb4*x5[4] - fa4*y5[4]; 
	for(k=3;k>=0;k--){
		x5[k+1] = x5[k];
		y5[k+1] = y5[k];
	}
	return (y5[0]);
}


float filter_ic(float xin){
	int k;
	x6[0] = xin;
	y6[0] = fb0* x6[0]; 
	y6[0] += fb1*x6[1] - fa1*y6[1];
	y6[0] += fb2*x6[2] - fa2*y6[2]; 
	y6[0] += fb3*x6[3] - fa3*y6[3];
	y6[0] += fb4*x6[4] - fa4*y6[4]; 
	for(k=3;k>=0;k--){
		x6[k+1] = x6[k];
		y6[k+1] = y6[k];
	}
	return (y6[0]);
}


/*end of file*/
