#pragma once
#include "../global/vars.h"

void inject_larafire(bool replace);

void InitialiseNewWeapon();
void LaraTargetInfo(WEAPON_INFO* winfo);
short* get_current_ammo_pointer(long weapon_type);
long FireWeapon(long weapon_type, ITEM_INFO* target, ITEM_INFO* src, short* angles);
void AimWeapon(WEAPON_INFO* winfo, LARA_ARM* arm);
void LaraGetNewTarget(WEAPON_INFO* winfo);
void HitTarget(ITEM_INFO* item, GAME_VECTOR* hitpos, long damage, long grenade);
long WeaponObject(long weapon_type);
long WeaponObjectMesh(long weapon_type);

#define LaraGun	( (void(__cdecl*)()) 0x0042D840 )
#define DoProperDetection	( (void(__cdecl*)(short, long, long, long, long, long, long)) 0x0042EB30 )
