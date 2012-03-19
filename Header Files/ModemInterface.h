#define ModemInterface
#include "CommonHeader.h"

typedef struct
{
	int _index;
	char* _number;
	char* _time;
	char _read;
	char _sent;
} TextMessageHeader;

typedef struct
{
	TextMessageHeader _header;
	char* _data;
} TextMessage;

void Modem_Set();
void Modem_SendTextMessage(TextMessage m);
TextMessageHeader* Modem_ListAllTextMessages();
TextMessageHeader* Modem_ListReadTextMessages();
TextMessageHeader* Modem_ListUnreadTextMessages();
TextMessage Modem_RecieveMessage(int index);
void Modem_RemoveMessage(int index);
void Modem_RemoveAllMessages();
void Modem_RemoveReadMessages();
void Modem_RemoveUnreadMessages();

char privModem_WaitResponseCMGW();
short privModem_GetIndexCMGW();
short privModem_GetInteger();
short privModem_GetReferenceCMSS();