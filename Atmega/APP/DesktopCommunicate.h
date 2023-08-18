
#ifndef DESKTOPCOMMUNICATE_H_
#define DESKTOPCOMMUNICATE_H_

#define NUMBEROFFUNCTIONS 5


#define FIRSTLEDPIN PINA0
#define RELAYPIN     PINC3
typedef struct
{
	void(*pf)(u8);
	u8* pstr	;
	}Element_type;

void DesktopCommunicate_Init(void);
void DesktopCommunicate_Runnable(void);



#endif 