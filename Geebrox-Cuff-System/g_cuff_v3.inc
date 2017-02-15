/*
	AUTHOR: Geebrox (bek)
	VK: vk.com/geebrox
	INSTAGRAM: instagram.com/geebrox
*/


#if defined _g_cuff_included
	#endinput
#endif
#define _g_cuff_included


#if !defined _samp_included
	#include <a_samp>
#endif


#if !defined sscanf
	#tryinclude "../include/sscanf2"
#endif
#if !defined sscanf
	#tryinclude "../sscanf2"
#endif
#if !defined sscanf
	#include <VLP/sscanf2>
#endif


#if !defined CMD
    #tryinclude "../include/dc_cmd.inc"
#endif
#if !defined CMD
    #tryinclude "../dc_cmd.inc"
#endif
#if !defined CMD
    #tryinclude <dc_cmd>
#endif
#if !defined CMD
    #tryinclude "../include/zcmd.inc"
#endif
#if !defined CMD
    #tryinclude "../zcmd.inc"
#endif
#if !defined CMD
    #tryinclude <zcmd>
#endif
#if !defined CMD
    #tryinclude "../include/Pawn.CMD.inc"
#endif
#if !defined CMD
    #tryinclude "../Pawn.CMD.inc"
#endif
#if !defined CMD
	#tryinclude <VLP/Pawn.CMD>
#endif
#if !defined CMD
    #error This include requires DC_CMD/ZCMD/YCMD/Pawn.CMD to work.
#endif  


// SETTINGS:

#if !defined gc_SUSPECT_UPDATE_INTERVAL
	#define gc_SUSPECT_UPDATE_INTERVAL 1000
#endif

#if !defined gc_CUFF_DISTANCE
	#define gc_CUFF_DISTANCE 3.0
#endif

#if !defined gc_UNCUFF_DISTANCE
	#define gc_UNCUFF_DISTANCE 3.0
#endif

#if !defined gc_FOLLOW_DISTANCE
	#define gc_FOLLOW_DISTANCE 5.0
#endif

#if !defined gc_SUSPECT_RANGE_RUN
	#define gc_SUSPECT_RANGE_RUN 4.0
#endif

#if !defined gc_SUSPECT_RANGE_TP
	#define gc_SUSPECT_RANGE_TP 20.0
#endif

#if !defined gc_COLOR_INFO
	#define gc_COLOR_INFO "{ecf0f1}"
#endif

#if !defined gc_COLOR_NOTE
	#define gc_COLOR_NOTE "{e67e22}"
#endif

#if !defined gc_COLOR_ERROR
	#define gc_COLOR_ERROR "{c0392b}"
#endif

#if !defined gc_COLOR_SUCCESS
	#define gc_COLOR_SUCCESS "{2ecc71}"
#endif

// END OF SETTINGS


enum
{
	gc_SUSPECT_STATUS_UNCUFFED,
	gc_SUSPECT_STATUS_CUFFED,
	gc_SUSPECT_STATUS_FOLLOWING,
	gc_SUSPECT_STATUS_WAITING
};


enum gc_results
{
    gc_RESULT_ERROR_ID,
    gc_RESULT_ERROR_PERMISSIONS,
    gc_RESULT_ERROR_USED,
    gc_RESULT_ERROR_CUFFED,
    gc_RESULT_ERROR_UNCUFFED,
    gc_RESULT_ERROR_FOLLOW,
    gc_RESULT_ERROR_DISTANCE
};


stock const gc_result_string[gc_results][] =
{
    !gc_COLOR_ERROR"- Ошибка! \
		"gc_COLOR_INFO"Укажите "gc_COLOR_NOTE"валидный ID \
		"gc_COLOR_INFO"игрока!",

    !gc_COLOR_ERROR"- Ошибка! \
		"gc_COLOR_INFO"Вы не можете использовать эту команду будучи \
		в наручниках!",

	!gc_COLOR_ERROR"- Ошибка! \
		"gc_COLOR_INFO"Вы не можете снять/надеть \
		наручники на этого игрока!",

	!gc_COLOR_ERROR"- Ошибка! \
		"gc_COLOR_INFO"На этого игрока уже надеты наручники!",

	!gc_COLOR_ERROR"- Ошибка! \
		"gc_COLOR_INFO"На этого игрока не надеты наручники!",

	!gc_COLOR_ERROR"- Ошибка! \
		"gc_COLOR_INFO"Вы не можете потащить за собой этого игрока!",

	!gc_COLOR_ERROR"- Ошибка! \
		"gc_COLOR_INFO"Игрок не рядом с вами!"
};


static 
	gc_cufferid[MAX_PLAYERS] =
		{INVALID_PLAYER_ID, INVALID_PLAYER_ID, ...},

	gc_cuffed_playerid[MAX_PLAYERS] =
		{INVALID_PLAYER_ID, INVALID_PLAYER_ID, ...},

	gc_suspect_status[MAX_PLAYERS char];

static stock const gc_vehicle_max_seats[212] =
{
	4, 2, 2, 2, 4, 4, 1, 2, 2, 4, 2, 2, 2, 4, 2, 2, 4, 2, 4, 2, 4, 4, 2, 2, 2,
	1, 4, 4, 4, 2, 1, 9, 1, 2, 2, 1, 2, 9, 4, 2, 4, 1, 2, 2, 2, 4, 1, 2, 1, 6,
	1, 2, 1, 1, 1, 2, 2, 2, 4, 4, 2, 2, 2, 2, 2, 2, 4, 4, 2, 2, 4, 2, 1, 1, 2,
	2, 1, 2, 2, 4, 2, 1, 4, 3, 1, 1, 1, 4, 2, 2, 4, 2, 4, 1, 2, 2, 2, 4, 4, 2,
	2, 2, 2, 2, 2, 2, 2, 4, 2, 1, 1, 2, 1, 1, 2, 2, 4, 2, 2, 1, 1, 2, 2, 2, 2,
	2, 2, 2, 2, 4, 1, 1, 1, 2, 2, 2, 2, 0, 0, 1, 4, 2, 2, 2, 2, 2, 4, 4, 2, 2,
	4, 4, 2, 1, 2, 2, 2, 2, 2, 2, 4, 4, 2, 2, 1, 2, 4, 4, 1, 0, 0, 1, 1, 2, 1,
	2, 2, 2, 2, 4, 4, 2, 4, 1, 1, 4, 2, 2, 2, 2, 6, 1, 2, 2, 2, 1, 4, 4, 4, 2,
	2, 2, 2, 2, 4, 2, 1, 1, 1, 4, 1, 1
};


stock Float: gc_GetDistanceBetweenPlayers(player_x, player_y)
{
	new 
		Float: x,
		Float: y,
		Float: z,
		Float: x2,
		Float: y2,
		Float: z2;

	GetPlayerPos(player_x, x, y, z);
	GetPlayerPos(player_y, x2, y2, z2);
	return VectorSize(x-x2, y-y2, z-z2);
}


stock gc_IsSuspectCuffed(suspectid)
{
	return (gc_suspect_status{suspectid}) ? (1) : (0);
}


stock gc_SetSuspectLook(suspectid, Float: look_x, Float: look_y)
{
	new 
		Float: x,
		Float: y,
		Float: a;

	GetPlayerPos(suspectid, x, y, a);
	a = atan2(look_y - y, look_x - x) - 90.0;
	SetPlayerFacingAngle(suspectid, a);
	return 1;
}


stock gc_GetFreeSeat(vehicleid)
{
    new
        tmp,
        seat;

#if defined _foreach_included  
    foreach(Player, i)
#else
    for(new i = 0; i < GetPlayerPoolSize(); i++)
#endif
    {
        if(GetPlayerVehicleID(i) == vehicleid)
        {
            if(0 <= (seat = GetPlayerVehicleSeat(i)) < cellbits)
            {
                tmp |= 1 << seat;
            }
        }
    }

    tmp = ~tmp;
    for(new i = 1; i < gc_vehicle_max_seats[GetVehicleModel(vehicleid) - 400];
    	i++)
    {
    	if((~(tmp - 1) & tmp) == 1 << i)
    	{
    		return i;
    	}
    }
    return -1;
}


forward gc_UpdateSuspect(suspectid);
public gc_UpdateSuspect(suspectid)
{
	if(gc_suspect_status{suspectid} == gc_SUSPECT_STATUS_FOLLOWING ||
		gc_suspect_status{suspectid} == gc_SUSPECT_STATUS_WAITING)
	{
		new
			Float: x,
			Float: y,
			Float: z,
			Float: distance;

		GetPlayerPos(gc_cufferid[suspectid], x, y, z);
		distance =
			gc_GetDistanceBetweenPlayers(gc_cufferid[suspectid], suspectid);

		if(distance > gc_SUSPECT_RANGE_TP)
		{
			new Float: a;
			GetPlayerFacingAngle(gc_cufferid[suspectid], a);

			x += ((gc_SUSPECT_RANGE_RUN - 1.0 > 0.0) ?
				(gc_SUSPECT_RANGE_RUN - 1.0) : (1.0)) * floatsin(-a, degrees);
			y += ((gc_SUSPECT_RANGE_RUN - 1.0 > 0.0) ?
				(gc_SUSPECT_RANGE_RUN - 1.0) : (1.0)) * floatcos(-a, degrees);
			gc_suspect_status{suspectid} = gc_SUSPECT_STATUS_WAITING;

			SetPlayerPos(suspectid, x, y, z);
			goto gc_reset_suspect_updating;
		}

		else if(distance > gc_SUSPECT_RANGE_RUN)
		{
			if(gc_suspect_status{suspectid} == gc_SUSPECT_STATUS_WAITING)
			{
				TogglePlayerControllable(suspectid, 1);
				ApplyAnimation(suspectid, "ped", "run_civi",
					4.1, 1, 1, 1, 0, 0, 1);

				gc_suspect_status{suspectid} = gc_SUSPECT_STATUS_FOLLOWING;
			}
		}

		else if(distance < gc_SUSPECT_RANGE_RUN && gc_SUSPECT_STATUS_FOLLOWING)
		{
			TogglePlayerControllable(suspectid, 0);
			gc_suspect_status{suspectid} = gc_SUSPECT_STATUS_WAITING;
		}

		gc_reset_suspect_updating:
		gc_SetSuspectLook(suspectid, x, y);
		SetTimerEx("gc_UpdateSuspect", gc_SUSPECT_UPDATE_INTERVAL, 0, 
			"i", suspectid);
	}
	return 1;
}


CMD:cuff(playerid, params[])
{
	extract params -> new suspectid; else
	    return SendClientMessage(playerid, -1,
	    	gc_result_string[gc_RESULT_ERROR_ID]);

	else if(gc_IsSuspectCuffed(playerid))
		return SendClientMessage(playerid, -1,
	    	gc_result_string[gc_RESULT_ERROR_PERMISSIONS]);

	else if(suspectid == playerid || !IsPlayerConnected(suspectid))
		return SendClientMessage(playerid, -1,
			gc_result_string[gc_RESULT_ERROR_ID]);

	else if(gc_GetDistanceBetweenPlayers(playerid, suspectid) >
		gc_CUFF_DISTANCE)
	    return SendClientMessage(playerid, -1,
	    	gc_result_string[gc_RESULT_ERROR_DISTANCE]);

	else if(gc_IsSuspectCuffed(suspectid))
		return SendClientMessage(playerid, -1, 
			gc_result_string[gc_RESULT_ERROR_CUFFED]);

	else if(gc_cuffed_playerid[playerid] != INVALID_PLAYER_ID)
		return SendClientMessage(playerid, -1, 
			gc_result_string[gc_RESULT_ERROR_USED]);

	gc_suspect_status{suspectid} = gc_SUSPECT_STATUS_CUFFED;
	gc_cufferid[suspectid] = playerid;
	gc_cuffed_playerid[playerid] = suspectid;

	SetPlayerSpecialAction(suspectid, SPECIAL_ACTION_CUFFED);
	TogglePlayerControllable(suspectid, 0);
	SendClientMessage(suspectid, -1, !gc_COLOR_NOTE"На вас надели наручники!");
	SendClientMessage(playerid, -1, !gc_COLOR_SUCCESS"Наручники надеты!");
	return 1;
}


CMD:uncuff(playerid, params[])
{
	extract params -> new suspectid; else
	    return SendClientMessage(playerid, -1,
	    	gc_result_string[gc_RESULT_ERROR_ID]);

	else if(gc_IsSuspectCuffed(playerid))
		return SendClientMessage(playerid, -1,
	    	gc_result_string[gc_RESULT_ERROR_PERMISSIONS]);

	else if(suspectid == playerid || !IsPlayerConnected(suspectid))
		return SendClientMessage(playerid, -1,
			gc_result_string[gc_RESULT_ERROR_ID]);

	else if(gc_GetDistanceBetweenPlayers(playerid, suspectid) >
		gc_UNCUFF_DISTANCE)
	    return SendClientMessage(playerid, -1,
	    	gc_result_string[gc_RESULT_ERROR_DISTANCE]);

	else if(!gc_IsSuspectCuffed(suspectid))
		return SendClientMessage(playerid, -1, 
			gc_result_string[gc_RESULT_ERROR_UNCUFFED]);

	else if(gc_cuffed_playerid[playerid] != suspectid)
		return SendClientMessage(playerid, -1, 
			gc_result_string[gc_RESULT_ERROR_USED]);

	gc_suspect_status{suspectid} = gc_SUSPECT_STATUS_UNCUFFED;
	gc_cufferid[suspectid] = gc_cuffed_playerid[playerid] = INVALID_PLAYER_ID;

	ClearAnimations(suspectid, 1);
	SetPlayerSpecialAction(suspectid, SPECIAL_ACTION_NONE);
	TogglePlayerControllable(suspectid, 1);
	SendClientMessage(suspectid, -1, !gc_COLOR_NOTE"С вас сняли наручники!");
	SendClientMessage(playerid, -1, !gc_COLOR_SUCCESS"Наручники сняты!");
	return 1;
}


CMD:followme(playerid, params[])
{
	extract params -> new suspectid; else
	    return SendClientMessage(playerid, -1,
	    	gc_result_string[gc_RESULT_ERROR_ID]);

	else if(gc_IsSuspectCuffed(playerid))
		return SendClientMessage(playerid, -1,
	    	gc_result_string[gc_RESULT_ERROR_PERMISSIONS]);

	else if(suspectid == playerid || !IsPlayerConnected(suspectid))
		return SendClientMessage(playerid, -1,
			gc_result_string[gc_RESULT_ERROR_ID]);

	else if(gc_GetDistanceBetweenPlayers(playerid, suspectid) >
		gc_FOLLOW_DISTANCE)
	    return SendClientMessage(playerid, -1,
	    	gc_result_string[gc_RESULT_ERROR_DISTANCE]);

	else if(!gc_IsSuspectCuffed(suspectid))
		return SendClientMessage(playerid, -1, 
			gc_result_string[gc_RESULT_ERROR_UNCUFFED]);

	else if(gc_cuffed_playerid[playerid] != suspectid)
		return SendClientMessage(playerid, -1, 
			gc_result_string[gc_RESULT_ERROR_FOLLOW]);

	gc_suspect_status{suspectid} = gc_SUSPECT_STATUS_FOLLOWING;
	gc_UpdateSuspect(suspectid);
	return 1;
}


CMD:stayhere(playerid, params[])
{
	extract params -> new suspectid; else
	    return SendClientMessage(playerid, -1,
	    	gc_result_string[gc_RESULT_ERROR_ID]);

	else if(gc_IsSuspectCuffed(playerid))
		return SendClientMessage(playerid, -1,
	    	gc_result_string[gc_RESULT_ERROR_PERMISSIONS]);

	else if(suspectid == playerid || !IsPlayerConnected(suspectid))
		return SendClientMessage(playerid, -1,
			gc_result_string[gc_RESULT_ERROR_ID]);
	
	else if(gc_GetDistanceBetweenPlayers(playerid, suspectid) >
		gc_FOLLOW_DISTANCE)
	    return SendClientMessage(playerid, -1,
	    	gc_result_string[gc_RESULT_ERROR_DISTANCE]);

	else if(gc_suspect_status{suspectid} == gc_SUSPECT_STATUS_FOLLOWING ||
		gc_suspect_status{suspectid} == gc_SUSPECT_STATUS_WAITING)
	{
		gc_suspect_status{suspectid} = gc_SUSPECT_STATUS_CUFFED;

		ClearAnimations(suspectid, 1);
		TogglePlayerControllable(suspectid, 0);
	}
	return 1;
}


public OnPlayerDisconnect(playerid, reason)
{
	if(gc_cuffed_playerid[playerid] != INVALID_PLAYER_ID)
	{
		gc_suspect_status{gc_cuffed_playerid[playerid]} =
			gc_SUSPECT_STATUS_UNCUFFED;
		gc_cufferid[gc_cuffed_playerid[playerid]] =
			gc_cuffed_playerid[playerid] = INVALID_PLAYER_ID;
	}

	else if(gc_cufferid[playerid] != INVALID_PLAYER_ID)
	{
		gc_suspect_status{playerid} = gc_SUSPECT_STATUS_UNCUFFED;
		gc_cuffed_playerid[gc_cufferid[playerid]] = gc_cufferid[playerid] =
			INVALID_PLAYER_ID;
	}
	#if defined gc_OnPlayerDisconnect
		return gc_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect gc_OnPlayerDisconnect
#if defined gc_OnPlayerDisconnect
	forward gc_OnPlayerDisconnect(playerid, reason);
#endif


public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	if(gc_cuffed_playerid[playerid] != INVALID_PLAYER_ID)
	{
		SetPlayerInterior(gc_cuffed_playerid[playerid], newinteriorid);

		new
			Float: x,
			Float: y,
			Float: z,
			Float: a;

		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, a);

		x += floatsin(-a, degrees);
		y += floatcos(-a, degrees);

		SetPlayerPos(gc_cuffed_playerid[playerid], x, y, z);
	}
	#if defined gc_OnPlayerInteriorChange
		return gc_OnPlayerInteriorChange(playerid, newinteriorid,
			oldinteriorid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerInteriorChange
	#undef OnPlayerInteriorChange
#else
	#define _ALS_OnPlayerInteriorChange
#endif

#define OnPlayerInteriorChange gc_OnPlayerInteriorChange
#if defined gc_OnPlayerInteriorChange
	forward gc_OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
#endif


stock gc_SetPlayerVirtualWorld(playerid, worldid)
{
	if(gc_cuffed_playerid[playerid] != INVALID_PLAYER_ID)
	{
		SetPlayerVirtualWorld(gc_cuffed_playerid[playerid], worldid);
	}
	return SetPlayerVirtualWorld(playerid, worldid);
}
#if defined _ALS_SetPlayerVirtualWorld
	#undef SetPlayerVirtualWorld
#else
	#define _ALS_SetPlayerVirtualWorld
#endif

#define SetPlayerVirtualWorld gc_SetPlayerVirtualWorld


public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(gc_cuffed_playerid[playerid] != INVALID_PLAYER_ID)
	{
		if(newstate == PLAYER_STATE_DRIVER ||
			newstate == PLAYER_STATE_PASSENGER)
		{
			new
				free_seatid,
				vehicleid = GetPlayerVehicleID(playerid);
			
			if((free_seatid = gc_GetFreeSeat(vehicleid)) != -1)
			{
				gc_suspect_status{gc_cuffed_playerid[playerid]} =
					gc_SUSPECT_STATUS_CUFFED;

				ClearAnimations(gc_cuffed_playerid[playerid], 1);
				TogglePlayerControllable(gc_cuffed_playerid[playerid], 0);
				PutPlayerInVehicle(gc_cuffed_playerid[playerid],
					vehicleid, free_seatid);
			}

			else
			{
				SendClientMessage(playerid, -1, !gc_COLOR_ERROR"- В машине не \
					хватает место для преступника\\подозреваемого!");
			}
		}

		else if(newstate == PLAYER_STATE_ONFOOT &&
			(oldstate == PLAYER_STATE_DRIVER ||
			oldstate == PLAYER_STATE_PASSENGER) &&
			IsPlayerInAnyVehicle(gc_cuffed_playerid[playerid]))
		{
			RemovePlayerFromVehicle(gc_cuffed_playerid[playerid]);
			gc_suspect_status{gc_cuffed_playerid[playerid]} =
				gc_SUSPECT_STATUS_FOLLOWING;
			gc_UpdateSuspect(gc_cuffed_playerid[playerid]);
		}
	}
	#if defined gc_OnPlayerStateChange
		return gc_OnPlayerStateChange(playerid, newstate, oldstate);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange gc_OnPlayerStateChange
#if defined gc_OnPlayerStateChange
	forward gc_OnPlayerStateChange(playerid, newstate, oldstate);
#endif
