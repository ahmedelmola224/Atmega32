#include "StdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"
#include "WDT.h"


void WDT_Set(TimeOut_type time)
{
	u8 wdt_val=0x08;
	wdt_val|=time;
	WDTCR|=(1<<WDTOE)|(1<<WDE);
	WDTCR=wdt_val;
}

void WDT_Stop(void)
{
	WDTCR=(1<<WDTOE)|(1<<WDE);
	WDTCR=0x00;
}
