/*
	Автор: Geebrox (bek)
	VK: vk.com/geebrox
*/

#if !defined _samp_included
	#include <a_samp>
#endif
#include <dc_cmd>
#include <sscanf2>

#if !defined G_CUFF_STATUS_UPDATE_TIME
	#define G_CUFF_STATUS_UPDATE_TIME 1000
#endif
#if !defined G_CUFF_DISTANCE
	#define G_CUFF_DISTANCE 5.0
#endif
#if !defined G_CUFF_ERROR_COLOR
	#define G_CUFF_ERROR_COLOR e74c3c
#endif
#if !defined G_CUFF_INFO_COLOR
	#define G_CUFF_INFO_COLOR f1c40f
#endif
#if !defined G_CUFF_TP_RANGE
	#define G_CUFF_TP_RANGE 20.0
#endif

const G_PCS_UNCUFFED = 0;
const G_PCS_CUFFED = 1;
const G_PCS_FOLLOWING = 2;
const G_PCS_CLOSE = 3;

forward UpdatePlayerCuffStatus(playerid, cufferid);

static player_cuff_status[MAX_PLAYERS char];

stock SetPlayerLook(playerid, Float:x, Float:y)
{
	new Float:pos_x;
	new Float:pos_y;
	new Float:angle;
	GetPlayerPos(playerid, pos_x, pos_y, angle);
	angle = atan2(y-pos_y, x-pos_x)-90.0;
	SetPlayerFacingAngle(playerid, angle);
	return 1;
}

stock IsPlayerCuffed(playerid)
	return (player_cuff_status{playerid}) ? (1) : (0);

stock Float:GetDistanceBetweenPlayers(player_x, player_y)
{
	new Float:x, Float:x2;
	new Float:y, Float:y2;
	new Float:z, Float:z2;
	GetPlayerPos(player_x, x, y, z);
	GetPlayerPos(player_y, x2, y2, z2);
	return VectorSize(x-x2, y-y2, z-z2);
}

public UpdatePlayerCuffStatus(playerid, cufferid)
{
	if(!IsPlayerCuffed(playerid) || !IsPlayerConnected(cufferid))
	{
	    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED)
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        TogglePlayerControllable(playerid, 1);
        player_cuff_status{playerid} = G_PCS_UNCUFFED;
	    return 1;
	}
	else if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_CUFFED)
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CUFFED);
    else if(player_cuff_status{playerid} == G_PCS_CUFFED)
	{
	    TogglePlayerControllable(playerid, 0);
	    return 1;
	}
    new Float:x;
	new Float:y;
	new Float:distance;
	GetPlayerPos(cufferid, x, y, distance);
	distance = GetDistanceBetweenPlayers(playerid, cufferid);
	if(distance <= 2.0 && player_cuff_status{playerid} == G_PCS_FOLLOWING)
	{
		ClearAnimations(playerid, 1);
	    TogglePlayerControllable(playerid, 0);
	    SetPlayerLook(playerid, x, y);
	    player_cuff_status{playerid} = G_PCS_CLOSE;
	}
	else if(distance > 2.5)
	{
	    ApplyAnimation(playerid, "ped",
			(distance < 6.0) ? ("WALK_player") : ("run_player"),
			4.1, 1, 1, 1, 0, 0, 1);
	    SetPlayerLook(playerid, x, y);
	    if(player_cuff_status{playerid} != G_PCS_FOLLOWING)
	    {
	        TogglePlayerControllable(playerid, 1);
			player_cuff_status{playerid} = G_PCS_FOLLOWING;
		}
	}
	SetTimerEx("UpdatePlayerCuffStatus",
		G_CUFF_STATUS_UPDATE_TIME, 0,
		"dd", playerid, cufferid);
	return 1;
}

public OnPlayerConnect(playerid)
{
	SetPVarInt(playerid, "cuffed_playerid", INVALID_PLAYER_ID);
#if defined g_cuff_OnPlayerConnect
    g_cuff_OnPlayerConnect(playerid);
#endif
    return 1;
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect g_cuff_OnPlayerConnect
#if defined g_cuff_OnPlayerConnect
forward g_cuff_OnPlayerConnect(playerid);
#endif

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
    if(GetPVarInt(playerid, "cuffed_playerid") != INVALID_PLAYER_ID
		&& newinteriorid != oldinteriorid)
		SetPlayerInterior(GetPVarInt(playerid, "cuffed_playerid"),
		    newinteriorid);
#if defined g_cuff_OnPlayerInteriorChange
    g_cuff_OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
#endif
    return 1;
}
#if defined _ALS_OnPlayerInteriorChange
    #undef OnPlayerInteriorChange
#else
	#define _ALS_OnPlayerInteriorChange
#endif
#define OnPlayerInteriorChange g_cuff_OnPlayerInteriorChange
#if defined g_cuff_OnPlayerInteriorChange
forward g_cuff_OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
#endif

stock g_cuff_SetPlayerPos(playerid, Float:x, Float:y, Float:z)
{
    if(GetPVarInt(playerid, "cuffed_playerid") != INVALID_PLAYER_ID)
	{
	    new Float:sx, Float:sy, Float:sz;
	    GetPlayerPos(GetPVarInt(playerid, "cuffed_playerid"), sx, sy, sz);
	    if(VectorSize(x-sx, y-sy, z-sz) > G_CUFF_TP_RANGE)
	    	SetPlayerPos(GetPVarInt(playerid, "cuffed_playerid"), x+1, y+1, z);
	}
	return SetPlayerPos(playerid, x, y, z);
}
#if defined _ALS_SetPlayerPos
    #undef SetPlayerPos
#else
    #define _ALS_SetPlayerPos
#endif
#define SetPlayerPos g_cuff_SetPlayerPos

CMD:stayhere(playerid, params[])
{
    extract params -> new suspect; else
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Используйте: /stayhere [ID]");
    else if(IsPlayerCuffed(playerid))
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Вы не можете использовать эту команду будучи \
			в наручниках!");
    else if(suspect == playerid || !IsPlayerConnected(suspect))
		return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Неверный ID игрока!");
    else if(player_cuff_status{suspect} < G_PCS_FOLLOWING)
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Игрок не следует за кем-то");
    else if(GetDistanceBetweenPlayers(playerid, suspect) > G_CUFF_DISTANCE)
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Вы не рядом с игроком!");
    else if(GetPVarInt(playerid, "cuffed_playerid") != suspect)
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Этот игрок не следует за вами!");
	player_cuff_status{suspect} = G_PCS_CUFFED;
	return 1;
}

CMD:followme(playerid, params[])
{
    extract params -> new suspect; else
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Используйте: /followme [ID]");
    else if(IsPlayerCuffed(playerid))
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Вы не можете использовать эту команду будучи \
			в наручниках!");
    else if(suspect == playerid || !IsPlayerConnected(suspect))
		return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Неверный ID игрока!");
    else if(player_cuff_status{suspect} == G_PCS_FOLLOWING)
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Этот игрок уже следует за кем-то!");
    else if(!IsPlayerCuffed(suspect))
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}На этого игрока не надеты наручники!");
    else if(GetDistanceBetweenPlayers(playerid, suspect) > G_CUFF_DISTANCE)
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Вы не рядом с игроком!");
    else if(GetPVarInt(playerid, "cuffed_playerid") != suspect)
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Вы не надевали на этого игрока наручники!");
	player_cuff_status{suspect} = G_PCS_FOLLOWING;
    UpdatePlayerCuffStatus(suspect, playerid);
    return 1;
}

CMD:gcuff(playerid, params[])
{
	extract params -> new suspect; else
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Используйте: /gcuff [ID]");
	else if(IsPlayerCuffed(playerid))
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Вы не можете использовать эту команду будучи \
			в наручниках!");
	else if(GetPVarInt(playerid, "cuffed_playerid") != INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Вы уже надели на кого то наручники!");
	else if(suspect == playerid || !IsPlayerConnected(suspect))
		return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Неверный ID игрока!");
	else if(IsPlayerCuffed(suspect))
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}На этого игрока уже надеты наручники!");
	else if(GetDistanceBetweenPlayers(playerid, suspect) > G_CUFF_DISTANCE)
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Вы не рядом с игроком!");
    SetPlayerSpecialAction(suspect, SPECIAL_ACTION_CUFFED);
	TogglePlayerControllable(suspect, 0);
	player_cuff_status{suspect} = G_PCS_CUFFED;
	SetPVarInt(playerid, "cuffed_playerid", suspect);
	return 1;
}

CMD:guncuff(playerid, params[])
{
	extract params -> new suspect; else
		return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Используйте: /guncuff [ID]");
    else if(IsPlayerCuffed(playerid))
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Вы не можете использовать эту команду будучи \
			в наручниках!");
    else if(suspect == playerid || !IsPlayerConnected(suspect))
		return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Неверный ID игрока!");
    else if(!IsPlayerCuffed(suspect))
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}На этого игрока не надеты наручники!");
    else if(GetDistanceBetweenPlayers(playerid, suspect) > G_CUFF_DISTANCE)
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Вы не рядом с игроком!");
    else if(GetPVarInt(playerid, "cuffed_playerid") != suspect)
	    return SendClientMessage(playerid, -1,
			"{"#G_CUFF_ERROR_COLOR"}- Ошибка! \
			{"#G_CUFF_INFO_COLOR"}Вы не надевали на этого игрока наручники!");
	if(player_cuff_status{suspect} == G_PCS_CUFFED)
	{
	    if(GetPlayerSpecialAction(suspect) == SPECIAL_ACTION_CUFFED)
			SetPlayerSpecialAction(suspect, SPECIAL_ACTION_NONE);
        TogglePlayerControllable(suspect, 1);
	}
    player_cuff_status{suspect} = G_PCS_UNCUFFED;
    SetPVarInt(playerid, "cuffed_playerid", INVALID_PLAYER_ID);
	return 1;
}
