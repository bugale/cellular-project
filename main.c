#include "CommonHeader.h"

void main()
{
	///*
	Timers_SetMainTimer();
	Modem_Set();
	Memory_Set();
	Timers_StopMainTimer();
	Timers_StartMainTimer();
	Led0_TurnOn();
	Led0_TurnOff();
	Led0_Toggle();
	Led1_TurnOn();
	Led1_TurnOff();
	Led1_Toggle();
	Modem_SendTextMessage(*((TextMessage*)NULL));
	Modem_RecieveMessage(0, 0);
	Modem_RemoveMessages(All);
	//*/
	while(1);
}