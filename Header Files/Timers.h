#define Timers
#include "CommonHeader.h"
#define ulong unsigned long long
#define clk_freq_hz 11052000
#define clk_freq_khz 11052

void Timers_SetMainTimer();
void Timers_StartMainTimer();
void Timers_StopMainTimer();
void Timers_Wait_rounds(unsigned int rounds);
void Timers_Wait_ms(unsigned int milliseconds);