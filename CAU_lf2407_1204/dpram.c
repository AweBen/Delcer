/*data xchange*/
//
#include "dpram.h"

//
unsigned int ua_rms,ub_rms,uc_rms,ia_rms,ib_rms,ic_rms;
unsigned int alpha_a,alpha_b,alpha_c;
unsigned int basisa_int,basisb_int,basisc_int;

unsigned int up_a,up_b,up_c,down_a,down_b,down_c;
unsigned int up_a_u,up_b_u,up_c_u,down_a_u,down_b_u,down_c_u;



#pragma DATA_SECTION(data_up_dpram,"dpram_up");
volatile struct DATA_UP data_up_dpram;//Local in DPRAM
volatile struct DATA_UP moni_data;//Local in DSP SRAM
volatile struct DATA_UP_NEW moni_data_new;
#pragma DATA_SECTION(data_dn_dpram,"dpram_dn");
volatile struct DATA_DN data_dn_dpram;
volatile struct DATA_DN order_data;
volatile struct DATA_DN_NEW order_data_new;



extern void delay(unsigned int);



//functions
/*get data from dpram*/
void monitor_data(void){

	SEM0 = 0x0;//to take 0x100~0x7FF resource

	if(0x0000 == SEM0){//gain control of the resource 0x100~0x7FF,another case is SEM0 is 0xFFFF,indicate loss control.

		moni_data.state_tirg = data_up_dpram.state_tirg;
		moni_data.state_vect = data_up_dpram.state_vect;
		moni_data.uab_peak = data_up_dpram.uab_peak;
		moni_data.ubc_peak = data_up_dpram.ubc_peak;
		moni_data.uca_peak = data_up_dpram.uca_peak;
		moni_data.ia_peak = data_up_dpram.ia_peak;
		moni_data.ib_peak = data_up_dpram.ib_peak;
		moni_data.ic_peak = data_up_dpram.ic_peak;
		moni_data.vavle_ctrl_a = data_up_dpram.vavle_ctrl_a;
		moni_data.vavle_ctrl_b = data_up_dpram.vavle_ctrl_b;
		moni_data.vavle_ctrl_c = data_up_dpram.vavle_ctrl_c;
		moni_data.i_tcr_a = data_up_dpram.i_tcr_a;
		moni_data.i_tcr_b = data_up_dpram.i_tcr_b;
		moni_data.i_tcr_c = data_up_dpram.i_tcr_c;
		moni_data.upa = data_up_dpram.upa;
		moni_data.upb = data_up_dpram.upb;
		moni_data.upc = data_up_dpram.upc;
		moni_data.downa = data_up_dpram.downa;
		moni_data.downb = data_up_dpram.downb;
		moni_data.downc = data_up_dpram.downc;
		moni_data.kpa = data_up_dpram.kpa;
		moni_data.kpb = data_up_dpram.kpb;
		moni_data.kpc = data_up_dpram.kpc;
		moni_data.kia = data_up_dpram.kia;
		moni_data.kib = data_up_dpram.kib;
		moni_data.kic = data_up_dpram.kic;
		moni_data.kda = data_up_dpram.kda;
		moni_data.kdb = data_up_dpram.kdb;
		moni_data.kdc = data_up_dpram.kdc;
		moni_data.scale = data_up_dpram.scale;
		moni_data.cond_a = data_up_dpram.cond_a;
		moni_data.cond_b = data_up_dpram.cond_b;
		moni_data.cond_c = data_up_dpram.cond_c;
		moni_data.basisa = data_up_dpram.basisa;
		moni_data.basisb = data_up_dpram.basisb;
		moni_data.basisc = data_up_dpram.basisc;
		moni_data.a_ovld = data_up_dpram.a_ovld;
		moni_data.b_ovld = data_up_dpram.b_ovld;
		moni_data.c_ovld = data_up_dpram.c_ovld;
		moni_data.a_up = data_up_dpram.a_up;
		moni_data.b_up = data_up_dpram.b_up;
		moni_data.c_up = data_up_dpram.c_up;
		moni_data.a_down = data_up_dpram.a_down;
		moni_data.b_down = data_up_dpram.b_down;
		moni_data.c_down = data_up_dpram.c_down;
		moni_data.ovld_value = data_up_dpram.ovld_value;
		moni_data.manual_Ba = data_up_dpram.manual_Ba;
		moni_data.manual_Bb = data_up_dpram.manual_Bb;
		moni_data.manual_Bc = data_up_dpram.manual_Bc;
	}

	SEM0 = 0x1;//release control.

	//
	alpha_a = (unsigned int)(18000 - 0.5493499 * (float)moni_data.vavle_ctrl_a);
	alpha_b = (unsigned int)(18000 - 0.5493499 * (float)moni_data.vavle_ctrl_b);
	alpha_c = (unsigned int)(18000 - 0.5493499 * (float)moni_data.vavle_ctrl_c);

	up_a_u = (unsigned int)(180 - 0.005493499 * (float)moni_data.upa);//pulse up read back value
	up_b_u = (unsigned int)(180 - 0.005493499 * (float)moni_data.upb);//pulse up read back value
	up_c_u = (unsigned int)(180 - 0.005493499 * (float)moni_data.upc);//pulse up read back value

	down_a_u = (unsigned int)(180 - 0.005493499 * (float)moni_data.downa);//pulse down read back value
	down_b_u = (unsigned int)(180 - 0.005493499 * (float)moni_data.downb);//pulse down read back value
	down_c_u = (unsigned int)(180 - 0.005493499 * (float)moni_data.downc);//pulse down read back value
}

/*put data to dpram*/
void put_data(void){

//	unsigned int inst_up_a,inst_up_b,inst_up_c;
//	unsigned int inst_down_a,inst_down_b,inst_down_c;

	order_data.upa = (unsigned int)(182.033333 * (float)(180 - up_a));
	order_data.upb = (unsigned int)(182.033333 * (float)(180 - up_b));
	order_data.upc = (unsigned int)(182.033333 * (float)(180 - up_c));

	order_data.downa = (unsigned int)(182.033333 * (float)(180 - down_a));
	order_data.downb = (unsigned int)(182.033333 * (float)(180 - down_b));
	order_data.downc = (unsigned int)(182.033333 * (float)(180 - down_c));

	SEM1 = 0x0;//to take 0x800~0xFFF resource

	if(0x0000 == SEM1){//gain control of the resource 0x800~0xFFF.

		data_dn_dpram.upa = order_data.upa;
		data_dn_dpram.upb = order_data.upb;
		data_dn_dpram.upc = order_data.upc;
		data_dn_dpram.downa = order_data.downa;
		data_dn_dpram.downb = order_data.downb;
		data_dn_dpram.downc = order_data.downc;
		data_dn_dpram.contrl_word = order_data.contrl_word;
		data_dn_dpram.rsvd1 = order_data.rsvd1;
		data_dn_dpram.rsvd2 = order_data.rsvd2;
		data_dn_dpram.f28335_run = order_data.f28335_run;
		data_dn_dpram.kpa = order_data.kpa;
		data_dn_dpram.kpb = order_data.kpb;
		data_dn_dpram.kpc = order_data.kpc;
		data_dn_dpram.kia = order_data.kia;
		data_dn_dpram.kib = order_data.kib;
		data_dn_dpram.kic = order_data.kic;
		data_dn_dpram.kda = order_data.kda;
		data_dn_dpram.kdb = order_data.kdb;
		data_dn_dpram.kdc = order_data.kdc;
		data_dn_dpram.scale = order_data.scale;
		data_dn_dpram.basisa = order_data.basisa;
		data_dn_dpram.basisb = order_data.basisb;
		data_dn_dpram.basisc = order_data.basisc;
		data_dn_dpram.ovld_value = order_data.ovld_value;
		data_dn_dpram.rsvd3 = order_data.rsvd3;
		data_dn_dpram.manual_Ba = order_data.manual_Ba;
		data_dn_dpram.manual_Bb = order_data.manual_Bb;
		data_dn_dpram.manual_Bc = order_data.manual_Bc;
	}

	SEM1 = 0x1;//release control.
}


/*
voltage rms caculate function.
	ua	->	ua_rms
	ub	->	ub_rms
	uc	->	uc_rms
*/
void voltage_cal(void){


}

//end
