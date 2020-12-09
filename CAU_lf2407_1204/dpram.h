/*user defined IO port*/



struct DATA_UP{
	unsigned int start_stop; //state_tirg;
	unsigned int state_vect;
	signed int uab_peak;  //use old
	signed int ubc_peak;  //use old
	signed int uca_peak;  //use old
	signed int ia_peak;  //use old
	signed int ib_peak;  //use old
	signed int ic_peak;  //use old
	unsigned int   dc_voltage;      // vavle_ctrl_a;
	unsigned int   dc_current;     // vavle_ctrl_b;

	unsigned int vavle_ctrl_c;  //alpha_c
	unsigned int i_tcr_a;
	unsigned int i_tcr_b;
	unsigned int i_tcr_c;
	unsigned int upa;
	unsigned int upb;
	unsigned int upc;
	unsigned int downa;
	unsigned int downb;
	unsigned int downc;
	float kpa;
	float kpb;
	float kpc;
	float kia;
	float kib;
	float kic;
	float kda;
	float kdb;
	float kdc;
	float scale;
	float cond_a;
	float cond_b;
	float cond_c;
	float basisa;
	float basisb;
	float basisc;
	unsigned int ca_AC_protect;      //a_ovld;
	unsigned int power_fault;        //b_ovld;
	unsigned int other_fault;        //c_ovld;
	unsigned int ab_AC_protect;      //a_up;
	unsigned int dc_protect;         //b_up;
	unsigned int pulse_lose_protect;  //c_up;
	unsigned int bc_AC_protect;      //a_down;
	unsigned int dc_over_voltaged;   //b_down;
	unsigned int cooling_fault;      //c_down;
	unsigned int ovld_value;
	float manual_Ba;
	float manual_Bb;
	float manual_Bc;
};

struct DATA_DN_NEW{

	float p_set;
	float i_set;
	float d_set;
	float pid_up_set;
	float pid_down_set;
	float current_value;
	float exceed_current_value;
	float exceed_DCvoltage_value;
	unsigned int time_value;
	unsigned int  phase_value;
	unsigned int  start_stop_control;

};

struct DATA_DN{
	unsigned int upa;
	unsigned int upb;
	unsigned int upc;
	unsigned int downa;
	unsigned int downb;
	unsigned int downc;
	unsigned int contrl_word;
	unsigned int rsvd1;
	unsigned int rsvd2;
	unsigned int f28335_run;//0x4567
	float kpa;
	float kpb;
	float kpc;
	float kia;
	float kib;
	float kic;
	float kda;
	float kdb;
	float kdc;
	float scale;
	float basisa;//susceptance(B) offset modified by SCI. saved in EEROM.
	float basisb;
	float basisc;
	unsigned int ovld_value;
	unsigned int rsvd3;
	float manual_Ba;//manual input susceptance(B) modifed by CAN Bus & SCI. use in mode 1
	float manual_Bb;
	float manual_Bc;
};


//
#define		SEM0				*((volatile unsigned int *)0xE000)
#define		SEM1				*((volatile unsigned int *)0xE001)

//DAC port defined
#define		DAC		portf000
ioport	unsigned	portf000;

//end