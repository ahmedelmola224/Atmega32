/*
 * DesktopCommunicate_private.h
 *
 * Created: 2/25/2023 4:50:09 PM
 *  Author: ahmed
 */ 


#ifndef DESKTOPCOMMUNICATE_PRIVATE_H_
#define DESKTOPCOMMUNICATE_PRIVATE_H_

static void StringSplit(u8*str,u8*num);
static void LedOn(u8 lednumber);
static void LedOff(u8 lednumber);
static void RelayOn(u8 relaynumber);
static void RelayOff(u8 relaynumber);
static void RGB(u8 color);
static u8 StringCmp(u8*str1,u8*str2);
static u8 GetFunctionIndex(u8*str);

#endif /* DESKTOPCOMMUNICATE_PRIVATE_H_ */