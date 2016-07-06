//Game Mode for Tests!!

#include <a_samp>
#include <crashdetect>
#include <fixes>
#include <YSF>
#include <sscanf2>
#include <dc_cmd>
#include <streamer>
#include <g_hp>

#define COLOR_DIALOG_CAPTION 3498db
#define COLOR_DIALOG_TEXT ffffff
#define COLOR_ERROR e74c3c
#define COLOR_SUCCESS 2ecc71
#define COLOR_WARNING f1c40f
#define COLOR_NOTE f39c12

forward OnPlayerUpdateStatus(playerid);

enum dialog_ids
{
	DIALOG_ID_NONE,
	DIALOG_ID_SKIN
}

public OnGameModeInit()
{
	SetGameModeText("Test Mode");
	AddPlayerClass(0, 1958.378, 1343.157, 15.374, 269.142, 0, 0, 0, 0, 0, 0);
	SendRconCommand("hostname Server for testing");
	SendRconCommand("language Russian");
	return 1;
}

public OnPlayerConnect(playerid)
{
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	if(GetPVarInt(playerid, "second_timer"))
		KillTimer(GetPVarInt(playerid, "second_timer"));
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	ShowPlayerDialog(playerid, DIALOG_ID_SKIN, DIALOG_STYLE_INPUT,
	!"{"#COLOR_DIALOG_CAPTION"}Выбор модели",
	!"{"#COLOR_DIALOG_TEXT"}Введите ID модели с которым хотите начать \
	тест (1-299):", !"Выбрать", !"");
	return 1;
}

public OnPlayerSpawn(playerid)
{
	SetPlayerPos(playerid, 0.0, 0.0, 3.2);
	SetPlayerSkin(playerid, GetPVarInt(playerid, "logged"));
	SetPlayerHealth(playerid, 100);
	if(!GetPVarInt(playerid, "second_timer"))
		SetPVarInt(playerid, "second_timer",
	SetTimerEx("OnPlayerUpdateStatus", 1000, 0, "d", playerid));
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case DIALOG_ID_SKIN:
		{
			if(!response)
				return ShowPlayerDialog(playerid, DIALOG_ID_SKIN,
					DIALOG_STYLE_INPUT, !"{"#COLOR_DIALOG_CAPTION"}Выбор модели",
	 				!"{"#COLOR_DIALOG_TEXT"}Введите ID модели с которым \
				 	хотите начать тест (1-299):", !"Выбрать", !"");
			new model_id;
			if(!(model_id = strval(inputtext)))
				return ShowPlayerDialog(playerid, DIALOG_ID_SKIN,
					DIALOG_STYLE_INPUT, !"{"#COLOR_DIALOG_CAPTION"}Выбор модели",
	 				!"{"#COLOR_DIALOG_TEXT"}Введите ID модели с которым \
				 	хотите начать тест (1-299):", !"Выбрать", !"");
			if(1 > model_id > 299)
				return ShowPlayerDialog(playerid, DIALOG_ID_SKIN,
					DIALOG_STYLE_INPUT, !"{"#COLOR_DIALOG_CAPTION"}Выбор модели",
	 				!"{"#COLOR_DIALOG_TEXT"}Введите ID модели с которым \
				 	хотите начать тест (1-299):", !"Выбрать", !"");
			SetPVarInt(playerid, "logged", model_id);
			SetSpawnInfo(playerid, 0, model_id, 0.0, 0.0, 3.2, 0.0,
			0, 0, 0, 0, 0, 0);
			SpawnPlayer(playerid);
		}
	}
	return 1;
}

public OnPlayerUpdateStatus(playerid)
{
	new Float:health;
	GetPlayerHealth(playerid, health);
	SendClientMessagef(playerid, -1, "Log №1: health:%0.1f - mustbe:%0.1f",
	player_health[playerid], health);
	if(_:health > _:player_health[playerid])
	    ShowPlayerDialog(playerid, DIALOG_ID_NONE, DIALOG_STYLE_MSGBOX,
	    " ", "{"#COLOR_ERROR"}Вы подозреваетесь в читерстве!", "Закрыть", "");
	else if(_:health < _:player_health[playerid])
	    player_health[playerid] = health;
    SendClientMessagef(playerid, -1, "Log №2: health:%0.1f - mustbe:%0.1f",
	player_health[playerid], health);
	SetPVarInt(playerid, "second_timer",
	SetTimerEx("OnPlayerUpdateStatus", 1000, 0, "d", playerid));
	return 1;
}

public OnPlayerRequestSpawn(playerid)
	return (GetPVarInt(playerid, "logged")) ? (1) : (0);

CMD:weapon(playerid, params[])
{
	extract params -> new weaponid, ammo; else
		return SendClientMessage(playerid, -1,
			!"{"#COLOR_ERROR"}Ошибка: используйте /wepon [id] [патроны]");
	GivePlayerWeapon(playerid, weaponid, ammo);
	SendClientMessagef(playerid, -1, "Вы получили оружие %d c %d патронами",
	weaponid, ammo);
	return 1;
}

CMD:health(playerid, params[])
{
	extract params -> new Float:health; else
	    return SendClientMessage(playerid, -1, "Use: /health [amount]");
	if(0 > health > 25000)
		return SendClientMessage(playerid, -1, "Use amount between 0 and 25000");
	SetPlayerHealth(playerid, health);
	return 1;
}

main(){}
