#include "CommonHeader.h"

void Timers_SetMainTimer()
{
	TMOD = 0x02;
	TH0 = 0;
}
void Timers_StartMainTimer()
{
	TR0 = 1;
}
void Timers_StopMainTimer()
{
	TR0 = 0;
}
void Timers_Wait_rounds(unsigned int rounds)
{
	data unsigned int i;
	for (i = 0; i < rounds; i++, CF = 0)
		while (!TF0);
}
void Timers_Wait_ms(unsigned int milliseconds)
{
	Timers_Wait_rounds((milliseconds*clk_freq_khz) / 0x100);
}