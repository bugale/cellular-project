#define ModemInterface
#include "CommonHeader.h"

typedef struct
{
	char _index;
	char_ptr _number;
	char_ptr _time;
	char _status;
} TextMessageHeader;

typedef struct
{
	TextMessageHeader _header;
	char_ptr _data;
} TextMessage;

typedef short TextMessageHeader_ptr;
typedef short TextMessage_ptr;
typedef enum
{
	Unread = 0,
	Read = 1,
	Unsent = 2,
	Sent = 3,
	All = 4
} StatusValue;

void Modem_Set();
void Modem_SendTextMessage(TextMessage m);
TextMessageHeader_ptr Modem_ListTextMessages(char max, StatusValue status);
TextMessage Modem_RecieveMessage(char index, char max);
void Modem_RemoveMessage(char index);
void Modem_RemoveMessages(StatusValue status);

char privModem_WaitResponseCMGS();
short privModem_GetInteger();
short privModem_GetReferenceCMGS();
short privModem_CheckCMGD();
TextMessage privModem_GetMessageCMGR(char max);
TextMessageHeader privModem_GetMessageHeader();
TextMessageHeader_ptr privModem_GetMessageHeaderList(char max);
char_ptr privModem_GetPhoneNumber();
char_ptr privModem_GetTime();
char privModem_GetMessageStatus();
void privModem_WaitForCRLF();
char_ptr privModem_GetUntilCRLF(char max);