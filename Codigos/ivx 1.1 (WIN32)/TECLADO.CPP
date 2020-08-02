
#include "teclado.h"

int rawkey,keys[128];			/* Holds the scan code
						and out litte buffer */
void interrupt (far *oldint9)(...);  	/* Saves the old interrupt, you really need to. */

void interrupt far newint9(...)
{
 register char a;
 rawkey=inp(0x60);			/* Sorry I smashed the code */
 outp(0x61,(a=inp(0x61)|0x82));		/* you really dont need the info */
 outp(0x61,a&0x7f);			/* of what it does. Email me if you need it */

 outp(0x20,0x20);			/* Renable hardware interrupts */

 if(rawkey<128)  keys[rawkey]=1;	/* If the key it pressed make the buffer true. */
 else keys[rawkey-128]=0;		/* If the key is release make the buffer false.
					   Yes, the release scan codes are 128 apart
					   from the orginal scan codes. */
 enableints();				/* equal to sti */
}

void install_kb(void)			/* Install interrupt */
{
 oldint9=_dos_getvect(9);		/* Save the old int, we need that */
 _dos_setvect(9,newint9);		/* Set new interrupt code */
}

void uninstall_kb(void)			/* uninstall interrupt */
{
 _dos_setvect(9,oldint9);		/* Install the old interrupt code */
}
