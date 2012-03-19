#include "CommonHeader.h"

void Modem_Set()
{
	printf("AT+CMGF=1\n");  // Set modem to text mode
}
void Modem_SendTextMessage(TextMessage m)
{
	short s;
	printf("AT+CMGW=\"%s\"\r", m._header._number); //Store Message
	privModem_WaitResponseCMGW();
	
	printf("%s%c", m._data, EndOfFile);
	s = privModem_GetIndexCMGW;
	if (s < 0) { HandleInternalError(s); return; }
	
	printf("AT+CMSS=\"%s\"\r", m._header._number); //Send Message
	s = privModem_GetReferenceCMSS();
	if (s < 0) { HandleInternalError(s); return; }
}
TextMessageHeader* Modem_ListAllTextMessages()
{
}
TextMessageHeader* Modem_ListReadTextMessages()
{
}
TextMessageHeader* Modem_ListUnreadTextMessages()
{
}
TextMessage Modem_RecieveMessage(int index)
{
}
void Modem_RemoveMessage(int index)
{
}
void Modem_RemoveAllMessages()
{
}
void Modem_RemoveReadMessages()
{
}
void Modem_RemoveUnreadMessages()
{
}

char privModem_WaitResponseCMGW()
{
	if (getchar() != '\r') return -1; //Critical Error: Wrong response syntax
	if (getchar() != '\n') return -1; //Critical Error: Wrong response syntax
	if (getchar() != '>') return -1; //Critical Error: Wrong response syntax
	if (getchar() != ' ') return -1; //Critical Error: Wrong response syntax
	return 0;
}
short privModem_GetIndexCMGW()
{
	if (getchar() != '+') return -1; //Critical Error: Wrong response syntax
	if (getchar() != 'C') return -1; //Critical Error: Wrong response syntax
	if (getchar() != 'M') return -1; //Critical Error: Wrong response syntax
	if (getchar() == 'S')
	{
		if (getchar() != ' ') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'E') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'R') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'R') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'O') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'R') return -1; //Critical Error: Wrong response syntax
		if (getchar() != ':') return -1; //Critical Error: Wrong response syntax
		if (getchar() != ' ') return -1; //Critical Error: Wrong response syntax
		return -privModem_GetInteger();
	}
	else
	{
		if (getchar() != 'G') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'W') return -1; //Critical Error: Wrong response syntax
		if (getchar() != ':') return -1; //Critical Error: Wrong response syntax
		if (getchar() != ' ') return -1; //Critical Error: Wrong response syntax
		return privModem_GetInteger();
	}
}
short privModem_GetInteger()
{
	short ans;
	char c;
	while (1)
	{
		c = getchar();
		ans *= 10;
		if (c >= '0' && c <= '9') ans += (c - '0');
		else return ans;
	}
}
short privModem_GetReferenceCMSS()
{
	if (getchar() != '+') return -1; //Critical Error: Wrong response syntax	
	if (getchar() != 'C') return -1; //Critical Error: Wrong response syntax
	if (getchar() != 'M') return -1; //Critical Error: Wrong response syntax
	if (getchar() != 'S') return -1; //Critical Error: Wrong response syntax
	if (getchar() == ' ')
	{
		if (getchar() != ' ') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'E') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'R') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'R') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'O') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'R') return -1; //Critical Error: Wrong response syntax
		if (getchar() != ':') return -1; //Critical Error: Wrong response syntax
		if (getchar() != ' ') return -1; //Critical Error: Wrong response syntax
		return -privModem_GetInteger();
	}
	else
	{
		if (getchar() != 'S') return -1; //Critical Error: Wrong response syntax
		if (getchar() != ':') return -1; //Critical Error: Wrong response syntax
		return privModem_GetInteger();
	}
}