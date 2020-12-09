//
#define WREN	0x06
#define WRDI	0x04
#define RDSR	0x05
#define WRSR	0x01
#define READ	0x03
#define WRITE	0x02


void wr_enable(void);
void wr_disable(void);
unsigned int rd_status(void);
void wr_status(unsigned int sta_data);
unsigned int rd_word(unsigned int);
float rd_float(unsigned int);
void wr_word(unsigned int,unsigned int);
void wr_float(unsigned int,float);