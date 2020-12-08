/**/
//sampling point assume 1000.
//QUARTER_SIZE equal to quarter of sampleing point.
//for example:sampleing point is 1000,and QUARTER_SIZE should be 250.
#define	QUARTER_SIZE	250
#define HALF_HITS		500



struct UI_ABC{
	signed int ua;
	signed int ub;
	signed int uc;
	signed int ia;
	signed int ib;
	signed int ic;
};

struct UI_PEAK{
	signed int ua_peak;
	signed int ub_peak;
	signed int uc_peak;
	signed int ia_peak;
	signed int ib_peak;
	signed int ic_peak;
	unsigned int cnt;
};

struct UI_VECT_ABC{
	float ua_p;
	float ua_n;
	float ub_p;
	float ub_n;
	float uc_p;
	float uc_n;
	float ia_p;
	float ia_n;
	float ib_p;
	float ib_n;
	float ic_p;
	float ic_n;
};

//end of file.

