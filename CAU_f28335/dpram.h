/**/
struct DATA_UP{
	unsigned int state_tirg;
	unsigned int state_vect;
	signed int uab_peak;
	signed int ubc_peak;
	signed int uca_peak;
	signed int ia_peak;
	signed int ib_peak;
	signed int ic_peak;
	unsigned int vavle_ctrl_a;//alpha_a
	unsigned int vavle_ctrl_b;//alpha_b
	unsigned int vavle_ctrl_c;//alpha_c
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
	unsigned int a_ovld;
	unsigned int b_ovld;
	unsigned int c_ovld;
	unsigned int a_up;
	unsigned int b_up;
	unsigned int c_up;
	unsigned int a_down;
	unsigned int b_down;
	unsigned int c_down;
	unsigned int ovld_value;
	float manual_Ba;
	float manual_Bb;
	float manual_Bc;
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
	float basisa;
	float basisb;
	float basisc;
	unsigned int ovld_value;
	unsigned int rsvd3;
	float manual_Ba;//manual input susceptance(B) modifed by CAN Bus & SCI. use in mode 1
	float manual_Bb;
	float manual_Bc;
};


//end of file

