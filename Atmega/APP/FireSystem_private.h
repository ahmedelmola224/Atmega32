


#ifndef FIRESYSTEM_PRIVATE_H_
#define FIRESYSTEM_PRIVATE_H_

#define PASSADDRESS       (u16)15
#define ENTERKEY          (u8)'C'
#define CHANGEPASSKEY     (u8)'1'
#define CONFIGKEY         (u8)'2'
#define TEMPSENSKEY       (u8)'3'
#define SMOKESENSKEY      (u8)'4'
#define UNLOCKMSG         (u8)222

void FIRESYS_ReceievePassword(u8*str);
u8 FIRESYS_CheckPassword(u8*str1,u8*str2);
void FIRESYS_CopyPassword(u8*str1,u8*str2);
void FIRESYS_RecieveConfig(u8*degree);
void EX_Interrupt(void);

#endif 