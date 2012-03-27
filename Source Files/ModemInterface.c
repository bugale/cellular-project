#include "CommonHeader.h"

void Modem_Set()
{
	Relay0Starter = 0;
	Timers_Wait_ms(1000);
	printf("AT+CMGF=1\n");  // Set modem to text mode
}
void Modem_SendTextMessage(TextMessage m)
{
	data short s;
	printf("AT+CMGS=\"%s\"\n", m._header._number);
	s = privModem_WaitResponseCMGS();
	if (s < 0) { HandleInternalError(s); return; }
	
	printf("%s%c", m._data, EndOfFile);
	s = privModem_GetReferenceCMGS();
	if (s < 0) { HandleInternalError(s); return; }
}
TextMessageHeader_ptr Modem_ListTextMessages(char max, StatusValue status)
{
	printf("AT+CMGL=\"");
	switch (status)
	{
		case Read:   printf("REC READ");   break;
		case Unread: printf("REC UNREAD"); break;
		case Sent:   printf("STO SENT");   break;
		case Unsent: printf("STO UNSENT"); break;
		default:     printf("ALL");        break;
	}
	printf("\"\n");
	return privModem_GetMessageHeaderList(max);
}
TextMessage Modem_RecieveMessage(char index, char max)
{
	data TextMessage ret;
	printf("AT+CMGR=%d\n", index);
	ret = privModem_GetMessageCMGR(max);
	if (ret._header._index < 0) { HandleInternalError(ret._header._index); return ret; }
	return ret;
}
void Modem_RemoveMessage(char index)
{
	data short s;
	printf("AT+CMGD=%d\n", index);
	s = privModem_CheckCMGD();
	if (s < 0) { HandleInternalError(s); return; }
}
void Modem_RemoveMessages(StatusValue status)
{
	data TextMessageHeader_ptr cur;
	cur = Modem_ListTextMessages(1, status);
	while ((*((TextMessageHeader*)cur))._index != -100)
	{
		Modem_RemoveMessage((*((TextMessageHeader*)cur))._index);
		free(cur);
		cur = Modem_ListTextMessages(1, status);
	}
	free(cur);
}

char privModem_WaitResponseCMGS()
{
	if (getchar() != '\r') return -1; //Critical Error: Wrong response syntax
	if (getchar() != '\n') return -1; //Critical Error: Wrong response syntax
	if (getchar() != '>') return -1; //Critical Error: Wrong response syntax
	if (getchar() != ' ') return -1; //Critical Error: Wrong response syntax
	return 0;
}
short privModem_GetInteger()
{
	data short ans;
	data char c;
	while (1)
	{
		c = getchar();
		ans *= 10;
		if (c >= '0' && c <= '9') ans += (c - '0');
		else return ans;
	}
}
short privModem_GetReferenceCMGS()
{
	data short ret;
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
		if (getchar() != 'S') return -1; //Critical Error: Wrong response syntax
		if (getchar() != ':') return -1; //Critical Error: Wrong response syntax
		ret = privModem_GetInteger();
		if (getchar() != '\n') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'O') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'K') return -1; //Critical Error: Wrong response syntax
		if (getchar() != '\r') return -1; //Critical Error: Wrong response syntax
		if (getchar() != '\n') return -1; //Critical Error: Wrong response syntax
		return ret;
	}
}
short privModem_CheckCMGD()
{
	if (getchar() == '\r')
	{
		if (getchar() != '\n') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'O') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'K') return -1; //Critical Error: Wrong response syntax
		if (getchar() != '\r') return -1; //Critical Error: Wrong response syntax
		if (getchar() != '\n') return -1; //Critical Error: Wrong response syntax
	}
	else
	{
		if (getchar() != '+') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'C') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'M') return -1; //Critical Error: Wrong response syntax
		if (getchar() != 'S') return -1; //Critical Error: Wrong response syntax
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
}
TextMessage privModem_GetMessageCMGR(char max)
{
	data TextMessage err;
	data TextMessage ret;
	err._header._index = -1;
	if (getchar() != '+') return err; //Critical Error: Wrong response syntax	
	if (getchar() != 'C') return err; //Critical Error: Wrong response syntax
	if (getchar() != 'M') return err; //Critical Error: Wrong response syntax
	if (getchar() == 'S')
	{
		if (getchar() != ' ') return err; //Critical Error: Wrong response syntax
		if (getchar() != 'E') return err; //Critical Error: Wrong response syntax
		if (getchar() != 'R') return err; //Critical Error: Wrong response syntax
		if (getchar() != 'R') return err; //Critical Error: Wrong response syntax
		if (getchar() != 'O') return err; //Critical Error: Wrong response syntax
		if (getchar() != 'R') return err; //Critical Error: Wrong response syntax
		if (getchar() != ':') return err; //Critical Error: Wrong response syntax
		if (getchar() != ' ') return err; //Critical Error: Wrong response syntax
		err._header._index = -privModem_GetInteger();
		return err;
	}
	else
	{
		if (getchar() != 'G') return err; //Critical Error: Wrong response syntax
		if (getchar() != 'R') return err; //Critical Error: Wrong response syntax
		if (getchar() != ':') return err; //Critical Error: Wrong response syntax
		if (getchar() != ' ') return err; //Critical Error: Wrong response syntax
		ret._header._status = privModem_GetMessageStatus();
		if (ret._header._status < 0) return ret;
		if (getchar() != ',') return err; //Critical Error: Wrong response syntax
		if (getchar() != '+') return err; //Critical Error: Wrong response syntax
		ret._header._number = privModem_GetPhoneNumber();
		if (getchar() != '"') return err; //Critical Error: Wrong response syntax
		while (getchar() != '"') //Wait for '"'
		if  (ret._header._status == 0 || ret._header._status == 1) //REC (UN)READ
		{
			if (getchar() != ',') return err; //Critical Error: Wrong response syntax
			ret._header._time = privModem_GetTime();
		}
		if (getchar() != '\r') return err; //Critical Error: Wrong response syntax
		if (getchar() != '\n') return err; //Critical Error: Wrong response syntax
		ret._data = privModem_GetUntilCRLF(max);
		if (getchar() != 'O') return err; //Critical Error: Wrong response syntax
		if (getchar() != 'K') return err; //Critical Error: Wrong response syntax
		if (getchar() != '\r') return err; //Critical Error: Wrong response syntax
		if (getchar() != '\n') return err; //Critical Error: Wrong response syntax
		return ret;
	}
}
TextMessageHeader privModem_GetMessageHeader()
{
	data TextMessageHeader ret;
	data TextMessageHeader err; err._index = -1; //Critical Error: Wrong response syntax
	if (getchar() != 'C') return err; //Critical Error: Wrong response syntax
	if (getchar() != 'M') return err; //Critical Error: Wrong response syntax
	if (getchar() != 'G') return err; //Critical Error: Wrong response syntax
	if (getchar() != 'L') return err; //Critical Error: Wrong response syntax
	if (getchar() != ':') return err; //Critical Error: Wrong response syntax
	if (getchar() != ' ') return err; //Critical Error: Wrong response syntax
	ret._index = privModem_GetInteger();
	if (getchar() != ',') return err; //Critical Error: Wrong response syntax
	if (getchar() != '"') return err; //Critical Error: Wrong response syntax
	ret._status = privModem_GetMessageStatus();
	if (getchar() != '"') return err; //Critical Error: Wrong response syntax
	if (getchar() != ',') return err; //Critical Error: Wrong response syntax
	if (getchar() != '"') return err; //Critical Error: Wrong response syntax
	if (getchar() != '+') return err; //Critical Error: Wrong response syntax
	ret._number = privModem_GetPhoneNumber();
	if (getchar() != ',') return err; //Critical Error: Wrong response syntax
	if (getchar() != '"') return err; //Critical Error: Wrong response syntax
	while (getchar() != '"') //Wait for '"'
	if (getchar() != ',') return err; //Critical Error: Wrong response syntax
	if (getchar() != '"') return err; //Critical Error: Wrong response syntax
	ret._time = privModem_GetTime();
	if (getchar() != '\r') return err; //Critical Error: Wrong response syntax
	if (getchar() != '\n') return err; //Critical Error: Wrong response syntax
	privModem_WaitForCRLF();
	return ret;
}
TextMessageHeader_ptr privModem_GetMessageHeaderList(char max)
{
	data char cur;
	data TextMessageHeader end;
	data TextMessageHeader_ptr headers = (TextMessageHeader_ptr)Memory_malloc(sizeof(TextMessageHeader)*max);
	end._index = -100;
	for (cur = 0; cur < max; cur++)
	{
		if (getchar() == '+') ((TextMessageHeader*)headers)[cur] = privModem_GetMessageHeader();
		else if (getchar() == 'O')
		{
			if (getchar() != 'K') { HandleInternalError(-1); return 0; } //Critical Error: Wrong response syntax
			else
			{
				((TextMessageHeader*)headers)[cur] = end;
				return headers;
			}
		}
		else { HandleInternalError(-1); return 0; } //Critical Error: Wrong response syntax
		if (((TextMessageHeader*)headers)[cur]._index < 0) { HandleInternalError(((TextMessageHeader*)headers)[cur]._index); return 0; }
	}
	return headers;
}
char_ptr privModem_GetPhoneNumber()
{
	data char pos = 0;
	data char_ptr ret = (char_ptr)Memory_malloc(13);
	for (((char*)ret)[pos] = getchar();
	     ((char*)ret)[pos] >= '0' && ((char*)ret)[pos] <= '9' && pos < 12;
		 ((char*)ret)[++pos] = getchar());
	((char*)ret)[pos] = 0;
	return ret;
}
char_ptr privModem_GetTime()
{
	data char pos = 0;
	data char_ptr ret = (char_ptr)Memory_malloc(23);
	for (((char*)ret)[pos] = getchar();
		 ((char*)ret)[pos] != '"' && pos < 22;
		 ((char*)ret)[++pos] = getchar());
	((char*)ret)[pos] = 0;
	return ret;
}
char privModem_GetMessageStatus()
{
	switch (getchar())
	{
		case 'R':
		{
			if (getchar() != 'E') return -1; //Critical Error: Wrong response syntax
			if (getchar() != 'C') return -1; //Critical Error: Wrong response syntax
			if (getchar() != ' ') return -1; //Critical Error: Wrong response syntax
			switch (getchar())
			{
				case 'U':
				{
					if (getchar() != 'N') return -1; //Critical Error: Wrong response syntax
					if (getchar() != 'R') return -1; //Critical Error: Wrong response syntax
					if (getchar() != 'E') return -1; //Critical Error: Wrong response syntax
					if (getchar() != 'A') return -1; //Critical Error: Wrong response syntax
					if (getchar() != 'D') return -1; //Critical Error: Wrong response syntax
					return 0; //Recieved Unread
				}
				case 'R':
				{
					if (getchar() != 'E') return -1; //Critical Error: Wrong response syntax
					if (getchar() != 'A') return -1; //Critical Error: Wrong response syntax
					if (getchar() != 'D') return -1; //Critical Error: Wrong response syntax
					return 1; //Recieved Read
				}
				default: return -1; //Critical Error: Wrong response syntax
			}
		}
		case 'S':
		{
			if (getchar() != 'T') return -1; //Critical Error: Wrong response syntax
			if (getchar() != 'O') return -1; //Critical Error: Wrong response syntax
			if (getchar() != ' ') return -1; //Critical Error: Wrong response syntax
			switch (getchar())
			{
				case 'U':
				{
					if (getchar() != 'N') return -1; //Critical Error: Wrong response syntax
					if (getchar() != 'S') return -1; //Critical Error: Wrong response syntax
					if (getchar() != 'E') return -1; //Critical Error: Wrong response syntax
					if (getchar() != 'N') return -1; //Critical Error: Wrong response syntax
					if (getchar() != 'T') return -1; //Critical Error: Wrong response syntax
					return 2; //Stored Unsent
				}
				case 'S':
				{
					if (getchar() != 'E') return -1; //Critical Error: Wrong response syntax
					if (getchar() != 'N') return -1; //Critical Error: Wrong response syntax
					if (getchar() != 'T') return -1; //Critical Error: Wrong response syntax
					return 3; //Stored Sent
				}
				default: return -1; //Critical Error: Wrong response syntax
			}
		}
		default: return -1; //Critical Error: Wrong response syntax
	}
}
void privModem_WaitForCRLF()
{
	data char a, b;
	a = getchar();
	b = getchar();
	while (a != '\r' || b != '\n')
	{
		a = b;
		b = getchar();
	}
}
char_ptr privModem_GetUntilCRLF(char max)
{
	data char pos = 0;
	data char_ptr ret = (char_ptr)Memory_malloc(max);
	if (max == 0) return ret;
	((char*)ret)[pos++] = getchar();
	if (max == 1) return ret;
	for (((char*)ret) [pos++]  = getchar();
		 (((char*)ret)[pos-1] != '\n' || ((char*)ret)[pos-2] != '\r') && pos < (max - 1);
		 ((char*)ret) [pos++]  = getchar());
	if (((char*)ret)[pos-2] == '\r' && ((char*)ret)[pos-1] == '\n') ((char*)ret)[pos-2] = 0;
	else if (((char*)ret)[pos-1] == '\r') ((char*)ret)[pos-1] = 0;
	else ((char*)ret)[pos] = 0;
	return ret;
}