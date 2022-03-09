#include "../tomb4/pch.h"
#include "voncroy.h"
#include "camera.h"
#include "../specific/3dmath.h"
#include "control.h"

void SetCutSceneCamera(ITEM_INFO* item)
{
	VonCroyCutData* cut;

	bVoncroyCutScene = 1;
	camera.old_type = FIXED_CAMERA;
	camera.type = CHASE_CAMERA;
	camera.speed = 1;
	CalculateCamera();
	actualCameraTarget.x = camera.target.x;
	actualCameraTarget.y = camera.target.y;
	actualCameraTarget.z = camera.target.z;
	actualFOV = CurrentFov;
	actualRoomNumber = camera.pos.room_number;
	camera.underwater = 0;
	actualCameraPos.x = camera.pos.x;
	actualCameraPos.y = camera.pos.y;
	actualCameraPos.z = camera.pos.z;
	cut = &VonCroyCutscenes[VonCroyCutIndices[lara.locationPad]];

	if (cut->FOV)
		AlterFOV(182 * cut->FOV);

	if (cut->flags & 4)
	{
		camera.pos.x = cut->CameraPos.x;
		camera.pos.y = cut->CameraPos.y;
		camera.pos.z = cut->CameraPos.z;
	}
	else
	{
		camera.pos.x += cut->CameraPos.x;
		camera.pos.y += cut->CameraPos.y;
		camera.pos.z += cut->CameraPos.z;
	}

	if (cut->flags & 8)
	{
		camera.target.x = cut->CameraTarget.x;
		camera.target.y = cut->CameraTarget.y;
		camera.target.z = cut->CameraTarget.z;
	}
	else
	{
		camera.target.x += cut->CameraTarget.x;
		camera.target.y += cut->CameraTarget.y;
		camera.target.z += cut->CameraTarget.z;
	}

	if (cut->flags & 2)
	{
		camera.target.x = item->pos.x_pos;
		camera.target.y = item->pos.y_pos - 256;
		camera.target.z = item->pos.z_pos;
	}

	if (IsRoomOutside(camera.pos.x, camera.pos.y, camera.pos.z) == -2)
	{
		camera.pos.x = actualCameraPos.x;
		camera.pos.y = actualCameraPos.y;
		camera.pos.z = actualCameraPos.z;
		camera.pos.room_number = (short)actualRoomNumber;
	}
	else
		camera.pos.room_number = IsRoomOutsideNo;

	phd_LookAt(camera.pos.x, camera.pos.y, camera.pos.z, camera.target.x, camera.target.y, camera.target.z, 0);
}

void ClearCutSceneCamera()
{
	camera.pos.x = actualCameraPos.x;
	camera.pos.y = actualCameraPos.y;
	camera.pos.z = actualCameraPos.z;
	camera.target.x = actualCameraTarget.x;
	camera.target.y = actualCameraTarget.y;
	camera.target.z = actualCameraTarget.z;
	camera.pos.room_number = (short)actualRoomNumber;
	camera.speed = 1;
	camera.old_type = FIXED_CAMERA;
	camera.type = CHASE_CAMERA;
	bVoncroyCutScene = 0;
	AlterFOV((short)actualFOV);
}

void GetAIEnemy(CREATURE_INFO* info, long tfl)
{
	AIOBJECT* ai;

	for (int i = 0; i < nAIObjects; i++)
	{
		ai = &AIObjects[i];

		if (ai->trigger_flags == tfl && ai->room_number != 255)
		{
			info->enemy = &info->ai_target;
			info->ai_target.object_number = ai->object_number;
			info->ai_target.room_number = ai->room_number;
			info->ai_target.pos.x_pos = ai->x;
			info->ai_target.pos.y_pos = ai->y;
			info->ai_target.pos.z_pos = ai->z;
			info->ai_target.pos.y_rot = ai->y_rot;
			info->ai_target.flags = ai->flags;
			info->ai_target.trigger_flags = ai->trigger_flags;
			info->ai_target.box_number = ai->box_number;

			if (!(info->ai_target.flags & IFL_TRIGGERED))
			{
				info->ai_target.pos.x_pos += (256 * phd_sin(info->ai_target.pos.y_rot)) >> 14;
				info->ai_target.pos.z_pos += (256 * phd_cos(info->ai_target.pos.y_rot)) >> 14;
			}
		}
	}
}

void inject_voncroy(bool replace)
{
	INJECT(0x00418D00, SetCutSceneCamera, replace);
	INJECT(0x00418F10, ClearCutSceneCamera, replace);
	INJECT(0x00418FA0, GetAIEnemy, replace);
}
