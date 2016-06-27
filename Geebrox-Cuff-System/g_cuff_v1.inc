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
        player_cuff_status{playerid} = 0;
	    return 1;
	}
	else if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_CUFFED)
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CUFFED);
    new Float:x;
	new Float:y;
	new Float:distance;
	GetPlayerPos(cufferid, x, y, distance);
	distance = GetDistanceBetweenPlayers(playerid, cufferid);
	if(distance <= 2.0 && player_cuff_status{playerid} == 1)
	{
		ClearAnimations(playerid, 1);
	    TogglePlayerControllable(playerid, 0);
	    SetPlayerLook(playerid, x, y);
	    player_cuff_status{playerid} = 2;
	}
	else if(distance > 2.5)
	{
	    TogglePlayerControllable(playerid, 1);
	    ApplyAnimation(playerid, "ped", (distance < 6.0) ? ("WALK_player") : ("run_player"), 4.1, 1, 1, 1, 0, 0, 1);
	    SetPlayerLook(playerid, x, y);
	    if(player_cuff_status{playerid} != 1)
			player_cuff_status{playerid} = 1;
	}
	SetTimerEx("UpdatePlayerCuffStatus", G_CUFF_STATUS_UPDATE_TIME, 0, "dd", playerid, cufferid);
	return 1;
}

CMD:gcuff(playerid, params[])
{
	extract params -> new suspect; else
	    return SendClientMessage(playerid, -1, "{"#G_CUFF_ERROR_COLOR"}- Ошибка! {"#G_CUFF_INFO_COLOR"}Используйте: /gcuff [ID]");
	else if(IsPlayerCuffed(playerid))
	    return SendClientMessage(playerid, -1, "{"#G_CUFF_ERROR_COLOR"}- Ошибка! {"#G_CUFF_INFO_COLOR"}Вы не можете использовать эту команду будучи в наручниках!");
	else if(suspect == playerid || !IsPlayerConnected(suspect))
		return SendClientMessage(playerid, -1, "{"#G_CUFF_ERROR_COLOR"}- Ошибка! {"#G_CUFF_INFO_COLOR"}Неверный ID игрока!");
	else if(IsPlayerCuffed(suspect))
	    return SendClientMessage(playerid, -1, "{"#G_CUFF_ERROR_COLOR"}- Ошибка! {"#G_CUFF_INFO_COLOR"}На этого игрока уже надеты наручники!");
	if(GetDistanceBetweenPlayers(playerid, suspect) > G_CUFF_DISTANCE)
	    return SendClientMessage(playerid, -1, "{"#G_CUFF_ERROR_COLOR"}- Ошибка! {"#G_CUFF_INFO_COLOR"}Вы не рядом с игроком!");
	player_cuff_status{suspect} = 1;
	UpdatePlayerCuffStatus(suspect, playerid);
	return 1;
}

CMD:guncuff(playerid, params[])
{
	extract params -> new suspect; else
		return SendClientMessage(playerid, -1, "{"#G_CUFF_ERROR_COLOR"}- Ошибка! {"#G_CUFF_INFO_COLOR"}Используйте: /gcuff [ID]");
    else if(IsPlayerCuffed(playerid))
	    return SendClientMessage(playerid, -1, "{"#G_CUFF_ERROR_COLOR"}- Ошибка! {"#G_CUFF_INFO_COLOR"}Вы не можете использовать эту команду будучи в наручниках!");
    else if(suspect == playerid || !IsPlayerConnected(suspect))
		return SendClientMessage(playerid, -1, "{"#G_CUFF_ERROR_COLOR"}- Ошибка! {"#G_CUFF_INFO_COLOR"}Неверный ID игрока!");
    else if(!IsPlayerCuffed(suspect))
	    return SendClientMessage(playerid, -1, "{"#G_CUFF_ERROR_COLOR"}- Ошибка! {"#G_CUFF_INFO_COLOR"}На этого игрока не надеты наручники!");
    if(GetDistanceBetweenPlayers(playerid, suspect) > G_CUFF_DISTANCE)
	    return SendClientMessage(playerid, -1, "{"#G_CUFF_ERROR_COLOR"}- Ошибка! {"#G_CUFF_INFO_COLOR"}Вы не рядом с игроком!");
    player_cuff_status{suspect} = 0;
	return 1;

}
