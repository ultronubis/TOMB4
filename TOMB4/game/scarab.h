#pragma once
#include "../global/vars.h"

void inject_scarab(bool replace);

void InitialiseScarab(short item_number);
void ScarabControl(short item_number);
long GetFreeScarab();
void ClearScarabs();
void TriggerScarab(short item_number);
void UpdateScarabs();

#define DrawScarabs	( (void(__cdecl*)()) 0x0040E630 )
