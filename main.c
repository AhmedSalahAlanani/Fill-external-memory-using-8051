#include <reg52.h>

sbit Error_Led	= P1^0;	  //RED				
sbit End_Led	= P1^7;     //GREEN
sbit Flash_Led	= P1^1;   //YELLOW


unsigned char  xdata loc _at_ 0x0000;
unsigned char  xdata *ptr;
   		 
			 
void delay()	
{
	unsigned char i,j,k;
	for(i = 3; i > 0 ; i--)
	 for(j = 255; j > 0 ; j--)
	  for(k = 255; k > 0 ; k--);
}


void flashing()
{		 
		Flash_Led = (Flash_Led ^ 1);
		delay(); 
}


void fill_ext_mem()
{  
	  unsigned int i;
  	unsigned char mem_code[36]={ 0x02,0x08,0x0C,0xC2,0x91,
					0x12,0x08,0x18,0xD2,0x91,
					0x12,0x08,0x18,0x80,0xF4,
					0x78,0x7F,0xE4,0xF6,0xD8,
					0xFD,0x75,0x81,0x08,0x02,
					0x08,0x00,0x7F,0xFF,0x7E,
					0xFF,0xDE,0xFE,0xDF,0xFA,0x22 };
  						
		ptr = &loc;
					
  	for(i = 0; i < 3; i++, ptr++){
		*ptr = mem_code[i];
		}
		
		ptr = 0x3;
		
		for(i = 0; i < 2045; i++, ptr++){
		*ptr = 0xFF;
		}
		
		ptr = 0x800;
		
		for(i = 3; i < 36; i++, ptr++){
			*ptr = mem_code[i];
		}
 
		ptr = 0x821;
		
		for(i = 0; i < 30687; i++, ptr++){
		*ptr = 0xFF;
		}
}


void main()
{
	  unsigned char count = 5;
				
		Error_Led = 1;
		End_Led   = 1;
		Flash_Led = 1;
	  
	  do {
		flashing();
			
		count--;
		
	   } while(count != 0);
			
		
		fill_ext_mem();
		
		while(1)
		{
				flashing();
		}
}