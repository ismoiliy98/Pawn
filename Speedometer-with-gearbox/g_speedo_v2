#if !defined G_SP_UPDATE_TIME
	#define G_SP_UPDATE_TIME 300
#endif
#if !defined FIXES_Single
	#tryinclude <fixes>
#endif

static Text:TD_speedometer[6];
static PlayerText:PTD_speedometer[MAX_PLAYERS][7];
static g_sp_player_ignore_update[MAX_PLAYERS];
static g_sp_vehicle_gearbox[MAX_PLAYERS];
static Float:gearbox_level[7] =
{
	40.000000,
	0.000000,
	-40.000000,
	-90.000000,
	-140.000000,
	-180.000000,
	-220.000000
};
static g_sp_player_is_holding_key_down[MAX_PLAYERS];
static g_sp_player_logged[MAX_PLAYERS];

#if !defined G_SP_HIDE_VEHICLE_NAME
static const vehicle_name[212][] =
{
    "Landstalker", "Bravura", "Buffalo", "Linerunner", "Pereniel", "Sentinel",
	"Dumper", "Firetruck", "Trashmaster", "Stretch", "Manana", "Infernus",
    "Voodoo", "Pony", "Mule", "Cheetah", "Ambulance", "Leviathan", "Moonbeam",
	"Esperanto", "Taxi", "Washington", "Bobcat", "Mr Whoopee", "BF Injection",
    "Hunter", "Premier", "Enforcer", "Securicar", "Banshee", "Predator", "Bus",
	"Rhino", "Barracks", "Hotknife", "Trailer", "Previon", "Coach", "Cabbie",
    "Stallion", "Rumpo", "RC Bandit", "Romero", "Packer", "Monster", "Admiral",
	"Squalo", "Seasparrow", "Pizzaboy", "Tram", "Trailer", "Turismo", "Speeder",
    "Reefer", "Tropic", "Flatbed", "Yankee", "Caddy", "Solair", "Berkley's RC Van",
	"Skimmer", "PCJ-600", "Faggio", "Freeway", "RC Baron", "RC Raider",
    "Glendale", "Oceanic", "Sanchez", "Sparrow", "Patriot", "Quad", "Coastguard",
	"Dinghy", "Hermes", "Sabre", "Rustler", "ZR3 50", "Walton", "Regina",
    "Comet", "BMX", "Burrito", "Camper", "Marquis", "Baggage", "Dozer", "Maverick",
	"News Chopper", "Rancher", "FBI Rancher", "Virgo", "Greenwood", "Jetmax",
	"Hotring", "Sandking", "Blista Compact", "Police Maverick", "Boxville", "Benson",
	"Mesa", "RC Goblin", "Hotring A", "Hotring B", "Bloodring Banger", "Rancher",
	"Super GT", "Elegant", "Journey", "Bike", "Mountain Bike", "Beagle", "Cropdust",
	"Stunt", "Tanker", "RoadTrain", "Nebula", "Majestic", "Buccaneer", "Shamal",
	"Hydra", "FCR-900", "NRG-500", "HPV1000", "Cement Truck", "Tow Truck", "Fortune",
	"Cadrona", "FBI Truck", "Willard", "Forklift", "Tractor", "Combine", "Feltzer",
	"Remington", "Slamvan", "Blade", "Freight", "Streak", "Vortex", "Vincent",
	"Bullet", "Clover", "Sadler", "Firetruck", "Hustler", "Intruder", "Primo",
	"Cargobob", "Tampa", "Sunrise", "Merit", "Utility", "Nevada", "Yosemite", "Windsor",
	"Monster A", "Monster B", "Uranus", "Jester", "Sultan", "Stratum", "Elegy",
	"Raindance", "RC Tiger", "Flash", "Tahoma", "Savanna", "Bandito", "Freight",
	"Trailer", "Kart", "Mower", "Duneride", "Sweeper", "Broadway", "Tornado",
	"AT-400", "DFT-30", "Huntley", "Stafford", "BF-400", "Newsvan","Tug", "Trailer A",
	"Emperor", "Wayfarer", "Euros", "Hotdog", "Club", "Trailer B", "Trailer C",
	"Andromada", "Dodo", "RC Cam", "Launch", "Police Car", "Police Car", "Police Car",
	"Police Ranger", "Picador", "S.W.A.T.", "Alpha", "Phoenix", "Glendale", "Sadler",
	"L Trailer A", "L Trailer B", "Stair Trailer", "Boxville", "Farm Plow", "U Trailer"
};
#endif
static const gearbox_lvl_shifter[212] =
{
    28,	26,	33,	20,	24,	29,	20,	18,	28,	23,	40,	30,	20,	19,	34,	28,	28,	21,	27,
	26,	27,	25,	17,	24,	38,	31,	30,	28,	36,	34,	23,	28,	20,	30,	12,	27,	28,	25,
	30,	24,	13,	25,	22,	20,	29,	43,	23,	20,	38,	14,	35,	34,	12,	24,	28,	19,	17,
	28,	24,	37,	29,	20,	26,	10,	8,	26,	25,	26,	26,	28,	20,	26,	21,	27,	31,	50,
	33,	21,	25,	33,	17,	28,	22,	13,	18,	11,	34,	33,	25,	28,	27,	25,	22,	39,	32,
	29,	33,	19,	22,	25,	6,	39,	39,	31,	25,	32,	30,	19,	18,	23,	34,	33,	39,	39,
	21,	25,	28,	28,	29,	49,	49,	30,	31,	27,	23,	29,	28,	27,	32,	27,	11,	12,	20,
	30,	30,	28,	31,	49,	49,	18,	27,	36,	29,	27,	26,	26,	27,	25,	28,	27,	26,	28,
	22,	49,	26,	28,	20,	20,	28,	32,	30,	27,	32,	30,	16,	29,	29,	31,	26,	1,	45,
	16,	11,	20,	11,	28,	28,	49,	23,	28,	27,	27,	24,	15,	1,	27,	26,	29,	19,	29,
	1,	15,	49,	40,	11,	24,	31,	31,	28,	27,	20,	30,	31,	26,	27,	18,	18,	1,	19,
	5,	14, 1

};

public OnGameModeInit()
{
	TD_speedometer[0] = TextDrawCreate(425.000000, 324.000000, "BG");
    TextDrawLetterSize(TD_speedometer[0], 0.449999, 1.600000);
    TextDrawTextSize(TD_speedometer[0], 170.000000, 170.000000);
    TextDrawAlignment(TD_speedometer[0], 1);
    TextDrawColor(TD_speedometer[0], 16777215);
    TextDrawUseBox(TD_speedometer[0], true);
    TextDrawBoxColor(TD_speedometer[0], 0);
    TextDrawSetShadow(TD_speedometer[0], 0);
    TextDrawSetOutline(TD_speedometer[0], 1);
    TextDrawBackgroundColor(TD_speedometer[0], 0x00000000);
    TextDrawFont(TD_speedometer[0], 5);
    TextDrawSetProportional(TD_speedometer[0], 1);
    TextDrawSetPreviewModel(TD_speedometer[0], 19159);
    TextDrawSetPreviewRot(TD_speedometer[0], 90.000000, 0.000000, 90.000000, 1.000000);

    TD_speedometer[1] = TextDrawCreate(535.000000, 257.000000, "BG");
    TextDrawLetterSize(TD_speedometer[1], 0.449999, 1.600000);
    TextDrawTextSize(TD_speedometer[1], 208.418731, 173.500030);
    TextDrawAlignment(TD_speedometer[1], 1);
    TextDrawColor(TD_speedometer[1], 65535);
    TextDrawUseBox(TD_speedometer[1], true);
    TextDrawBoxColor(TD_speedometer[1], 0);
    TextDrawSetShadow(TD_speedometer[1], 0);
    TextDrawSetOutline(TD_speedometer[1], 1);
    TextDrawBackgroundColor(TD_speedometer[1], 0x00000000);
    TextDrawFont(TD_speedometer[1], 5);
    TextDrawSetProportional(TD_speedometer[1], 1);
    TextDrawSetPreviewModel(TD_speedometer[1], 2197);
    TextDrawSetPreviewRot(TD_speedometer[1], -90.000000, 90.000000, 90.000000, 1.000000);

    TD_speedometer[2] = TextDrawCreate(486.000000, 374.000000, "BG");
    TextDrawLetterSize(TD_speedometer[2], 0.449999, 1.600000);
    TextDrawTextSize(TD_speedometer[2], 190.000000, 70.000000);
    TextDrawAlignment(TD_speedometer[2], 1);
    TextDrawColor(TD_speedometer[2], 255);
    TextDrawUseBox(TD_speedometer[2], true);
    TextDrawBoxColor(TD_speedometer[2], 0);
    TextDrawSetShadow(TD_speedometer[2], 0);
    TextDrawSetOutline(TD_speedometer[2], 1);
    TextDrawBackgroundColor(TD_speedometer[2], 0x00000000);
    TextDrawFont(TD_speedometer[2], 5);
    TextDrawSetProportional(TD_speedometer[2], 1);
    TextDrawSetPreviewModel(TD_speedometer[2], 3401);
    TextDrawSetPreviewRot(TD_speedometer[2], 90.000000, 0.000000, 90.000000, 1.000000);

    TD_speedometer[3] = TextDrawCreate(435.000000, 334.000000, "BG");
    TextDrawLetterSize(TD_speedometer[3], 0.449999, 1.600000);
    TextDrawTextSize(TD_speedometer[3], 150.000000, 150.000000);
    TextDrawAlignment(TD_speedometer[3], 1);
    TextDrawColor(TD_speedometer[3], 255);
    TextDrawUseBox(TD_speedometer[3], true);
    TextDrawBoxColor(TD_speedometer[3], 0);
    TextDrawSetShadow(TD_speedometer[3], 0);
    TextDrawSetOutline(TD_speedometer[3], 1);
    TextDrawBackgroundColor(TD_speedometer[3], 0x00000000);
    TextDrawFont(TD_speedometer[3], 5);
    TextDrawSetProportional(TD_speedometer[3], 1);
    TextDrawSetPreviewModel(TD_speedometer[3], 19159);
    TextDrawSetPreviewRot(TD_speedometer[3], 90.000000, 0.000000, 90.000000, 1.000000);

    TD_speedometer[4] = TextDrawCreate(588.589416, 413.583068, "KM/H");
    TextDrawLetterSize(TD_speedometer[4], 0.180322, 1.433333);
    TextDrawAlignment(TD_speedometer[4], 1);
    TextDrawColor(TD_speedometer[4], 9502719);
    TextDrawUseBox(TD_speedometer[4], true);
    TextDrawBoxColor(TD_speedometer[4], 0);
    TextDrawSetShadow(TD_speedometer[4], 0);
    TextDrawSetOutline(TD_speedometer[4], 0);
    TextDrawBackgroundColor(TD_speedometer[4], 0x00000000);
    TextDrawFont(TD_speedometer[4], 2);
    TextDrawSetProportional(TD_speedometer[4], 1);
    TextDrawSetPreviewModel(TD_speedometer[4], 19159);
    TextDrawSetPreviewRot(TD_speedometer[4], 90.000000, 0.000000, 90.000000, 1.000000);

    TD_speedometer[5] = TextDrawCreate(506.000000, 380.500000, ".");
    TextDrawLetterSize(TD_speedometer[5], 1.000000, 4.000000);
    TextDrawAlignment(TD_speedometer[5], 1);
    TextDrawColor(TD_speedometer[5], 16777215);
    TextDrawSetShadow(TD_speedometer[5], 0);
    TextDrawSetOutline(TD_speedometer[5], 0);
    TextDrawBackgroundColor(TD_speedometer[5], 0x00000000);
    TextDrawFont(TD_speedometer[5], 1);
    TextDrawSetProportional(TD_speedometer[5], 1);
    TextDrawSetPreviewModel(TD_speedometer[5], 0);
    TextDrawSetPreviewRot(TD_speedometer[5], 0.000000, 0.000000, 0.000000, 0.000000);
#if	defined	g_sp_OnGameModeInit
	g_sp_OnGameModeInit();
#endif    
    return 1;
}
#if	defined	_ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define	_ALS_OnGameModeInit
#endif
#define	OnGameModeInit g_sp_OnGameModeInit
#if	defined	g_sp_OnGameModeInit
forward g_sp_OnGameModeInit();
#endif

public OnPlayerDisconnect(playerid, reason)
{
	if(g_sp_player_logged[playerid])
	    g_sp_player_logged[playerid] = 0;
#if	defined	g_sp_OnPlayerDisconnect
	g_sp_OnPlayerDisconnect(playerid, reason);
#endif
	return 1;
}
#if	defined	_ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define	_ALS_OnPlayerDisconnect
#endif
#define	OnPlayerDisconnect g_sp_OnPlayerDisconnect
#if	defined	g_sp_OnPlayerDisconnect
forward g_sp_OnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerSpawn(playerid)
{
	if(!g_sp_player_logged[playerid])
	{
		PTD_speedometer[playerid][0] = CreatePlayerTextDraw(playerid, 588.589294, 376.833251, "-");
	    PlayerTextDrawLetterSize(playerid, PTD_speedometer[playerid][0], 0.610773, 6.418330);
	    PlayerTextDrawAlignment(playerid, PTD_speedometer[playerid][0], 3);
	    PlayerTextDrawColor(playerid, PTD_speedometer[playerid][0], 9502719);
	    PlayerTextDrawUseBox(playerid, PTD_speedometer[playerid][0], true);
	    PlayerTextDrawBoxColor(playerid, PTD_speedometer[playerid][0], 0);
	    PlayerTextDrawSetShadow(playerid, PTD_speedometer[playerid][0], 0);
	    PlayerTextDrawSetOutline(playerid, PTD_speedometer[playerid][0], 1);
	    PlayerTextDrawBackgroundColor(playerid, PTD_speedometer[playerid][0], 16777215);
	    PlayerTextDrawFont(playerid, PTD_speedometer[playerid][0], 2);
	    PlayerTextDrawSetProportional(playerid, PTD_speedometer[playerid][0], 1);

	    PTD_speedometer[playerid][1] = CreatePlayerTextDraw(playerid, 474.000000, 370.000000, "___________5   3   ___________1");
	    PlayerTextDrawLetterSize(playerid, PTD_speedometer[playerid][1], 0.300000, 1.200000);
	    PlayerTextDrawTextSize(playerid, PTD_speedometer[playerid][1], 80.000000, 80.000000);
	    PlayerTextDrawAlignment(playerid, PTD_speedometer[playerid][1], 1);
	    PlayerTextDrawColor(playerid, PTD_speedometer[playerid][1], 16777215);
	    PlayerTextDrawUseBox(playerid, PTD_speedometer[playerid][1], true);
	    PlayerTextDrawBoxColor(playerid, PTD_speedometer[playerid][1], 0);
	    PlayerTextDrawSetShadow(playerid, PTD_speedometer[playerid][1], 0);
	    PlayerTextDrawSetOutline(playerid, PTD_speedometer[playerid][1], 1);
	    PlayerTextDrawBackgroundColor(playerid, PTD_speedometer[playerid][1], 255);
	    PlayerTextDrawFont(playerid, PTD_speedometer[playerid][1], 1);
	    PlayerTextDrawSetProportional(playerid, PTD_speedometer[playerid][1], 1);

	    PTD_speedometer[playerid][2] = CreatePlayerTextDraw(playerid, 486.362915, 378.083343, "4     2");
	    PlayerTextDrawLetterSize(playerid, PTD_speedometer[playerid][2], 0.302810, 1.077499);
	    PlayerTextDrawTextSize(playerid, PTD_speedometer[playerid][2], 80.000000, 80.000000);
	    PlayerTextDrawAlignment(playerid, PTD_speedometer[playerid][2], 1);
	    PlayerTextDrawColor(playerid, PTD_speedometer[playerid][2], 16777215);
	    PlayerTextDrawUseBox(playerid, PTD_speedometer[playerid][2], true);
	    PlayerTextDrawBoxColor(playerid, PTD_speedometer[playerid][2], 0);
	    PlayerTextDrawSetShadow(playerid, PTD_speedometer[playerid][2], 0);
	    PlayerTextDrawSetOutline(playerid, PTD_speedometer[playerid][2], 1);
	    PlayerTextDrawBackgroundColor(playerid, PTD_speedometer[playerid][2], 255);
	    PlayerTextDrawFont(playerid, PTD_speedometer[playerid][2], 1);
	    PlayerTextDrawSetProportional(playerid, PTD_speedometer[playerid][2], 1);

	    PTD_speedometer[playerid][3] = CreatePlayerTextDraw(playerid, 528.500000, 378.500000, "~R~R     N");
	    PlayerTextDrawLetterSize(playerid, PTD_speedometer[playerid][3], 0.302341, 1.100831);
	    PlayerTextDrawTextSize(playerid, PTD_speedometer[playerid][3], 80.000000, 80.000000);
	    PlayerTextDrawAlignment(playerid, PTD_speedometer[playerid][3], 1);
	    PlayerTextDrawColor(playerid, PTD_speedometer[playerid][3], 16777215);
	    PlayerTextDrawUseBox(playerid, PTD_speedometer[playerid][3], true);
	    PlayerTextDrawBoxColor(playerid, PTD_speedometer[playerid][3], 0);
	    PlayerTextDrawSetShadow(playerid, PTD_speedometer[playerid][3], 0);
	    PlayerTextDrawSetOutline(playerid, PTD_speedometer[playerid][3], 1);
	    PlayerTextDrawBackgroundColor(playerid, PTD_speedometer[playerid][3], 255);
	    PlayerTextDrawFont(playerid, PTD_speedometer[playerid][3], 1);
	    PlayerTextDrawSetProportional(playerid, PTD_speedometer[playerid][3], 1);

	#if !defined G_SP_HIDE_VEHICLE_NAME
	    PTD_speedometer[playerid][4] = CreatePlayerTextDraw(playerid, 588.000000, 368.000000, "_");
	    PlayerTextDrawLetterSize(playerid, PTD_speedometer[playerid][4], 0.400000, 1.600000);
	    PlayerTextDrawAlignment(playerid, PTD_speedometer[playerid][4], 2);
	    PlayerTextDrawColor(playerid, PTD_speedometer[playerid][4], 16777215);
	    PlayerTextDrawSetShadow(playerid, PTD_speedometer[playerid][4], 0);
	    PlayerTextDrawSetOutline(playerid, PTD_speedometer[playerid][4], 1);
	    PlayerTextDrawBackgroundColor(playerid, PTD_speedometer[playerid][4], 95);
	    PlayerTextDrawFont(playerid, PTD_speedometer[playerid][4], 1);
	    PlayerTextDrawSetProportional(playerid, PTD_speedometer[playerid][4], 1);
	#endif

	    PTD_speedometer[playerid][5] = CreatePlayerTextDraw(playerid, 469.500000, 375.000000, "ARROW");
	    PlayerTextDrawLetterSize(playerid, PTD_speedometer[playerid][5], 0.449999, 1.600000);
	    PlayerTextDrawTextSize(playerid, PTD_speedometer[playerid][5], 80.000000, 80.000000);
	    PlayerTextDrawAlignment(playerid, PTD_speedometer[playerid][5], 1);
	    PlayerTextDrawColor(playerid, PTD_speedometer[playerid][5], 0x90FFFFAA);
	    PlayerTextDrawUseBox(playerid, PTD_speedometer[playerid][5], true);
	    PlayerTextDrawBoxColor(playerid, PTD_speedometer[playerid][5], 0);
	    PlayerTextDrawSetShadow(playerid, PTD_speedometer[playerid][5], 0);
	    PlayerTextDrawSetOutline(playerid, PTD_speedometer[playerid][5], 1);
	    PlayerTextDrawBackgroundColor(playerid, PTD_speedometer[playerid][5], 0x00000000);
	    PlayerTextDrawFont(playerid, PTD_speedometer[playerid][5], 5);
	    PlayerTextDrawSetProportional(playerid, PTD_speedometer[playerid][5], 1);
	    PlayerTextDrawSetPreviewModel(playerid, PTD_speedometer[playerid][5], 1559);
	    PlayerTextDrawSetPreviewRot(playerid, PTD_speedometer[playerid][5], 0.000000, 0.000000, 70.000000, 2.000000);

	    PTD_speedometer[playerid][6] = CreatePlayerTextDraw(playerid, 594.000000, 391.000000, "E__D__L");
	    PlayerTextDrawLetterSize(playerid, PTD_speedometer[playerid][6], 0.400000, 2.000000);
	    PlayerTextDrawAlignment(playerid, PTD_speedometer[playerid][6], 1);
	    PlayerTextDrawColor(playerid, PTD_speedometer[playerid][6], -1);
	    PlayerTextDrawUseBox(playerid, PTD_speedometer[playerid][6], true);
	    PlayerTextDrawBoxColor(playerid, PTD_speedometer[playerid][6], 0);
	    PlayerTextDrawSetShadow(playerid, PTD_speedometer[playerid][6], 0);
	    PlayerTextDrawSetOutline(playerid, PTD_speedometer[playerid][6], 0);
	    PlayerTextDrawBackgroundColor(playerid, PTD_speedometer[playerid][6], 51);
	    PlayerTextDrawFont(playerid, PTD_speedometer[playerid][6], 1);
	    PlayerTextDrawSetProportional(playerid, PTD_speedometer[playerid][6], 1);
	    g_sp_player_logged[playerid] = 1;
	    g_sp_player_is_holding_key_down[playerid] = 0x7FFFFFFF;
	}
#if	defined	g_sp_OnPlayerSpawn
	g_sp_OnPlayerSpawn(playerid);
#endif
	return 1;
}
#if	defined	_ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define	_ALS_OnPlayerSpawn
#endif
#define	OnPlayerSpawn g_sp_OnPlayerSpawn
#if	defined	g_sp_OnPlayerSpawn
forward g_sp_OnPlayerSpawn(playerid);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER)
	{
	#if !defined G_SP_HIDE_VEHICLE_NAME
	    PlayerTextDrawSetString(playerid, PTD_speedometer[playerid][4], vehicle_name[GetVehicleModel(GetPlayerVehicleID(playerid))-400]);
	#endif
	    new i = 6;
	    while(--i != -1)
			TextDrawShowForPlayer(playerid, TD_speedometer[i]);
		i = 7;
		while(--i != -1)
		    PlayerTextDrawShow(playerid, PTD_speedometer[playerid][i]);
        g_sp_vehicle_gearbox[playerid] = 1;
	    g_sp_UpdatePlayerSpeedometer(playerid, GetPlayerVehicleID(playerid));
	}
	else if(newstate == PLAYER_STATE_ON_FOOT && oldstate == PLAYER_STATE_DRIVER)
	    g_sp_UpdatePlayerSpeedometer(playerid, INVALID_VEHICLE_ID);
#if	defined	g_sp_OnPlayerStateChange
	g_sp_OnPlayerStateChange(playerid, newstate, oldstate);
#endif
	return 1;
}
#if	defined	_ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
#define	OnPlayerStateChange	g_sp_OnPlayerStateChange
#if	defined	g_sp_OnPlayerStateChange
forward g_sp_OnPlayerStateChange(playerid, newstate, oldstate);
#endif

public OnPlayerUpdate(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && GetTickCount() > g_sp_player_ignore_update[playerid])
	{
	    g_sp_UpdatePlayerSpeedometer(playerid, GetPlayerVehicleID(playerid));
	    g_sp_player_ignore_update[playerid] = GetTickCount()+G_SP_UPDATE_TIME;
	}
#if	defined	g_sp_OnPlayerUpdate
	g_sp_OnPlayerUpdate(playerid);
#endif
	return 1;
}
#if	defined	_ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define	_ALS_OnPlayerUpdate
#endif
#define	OnPlayerUpdate g_sp_OnPlayerUpdate
#if	defined	g_sp_OnPlayerUpdate
forward g_sp_OnPlayerUpdate(playerid);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if((newkeys & KEY_JUMP) && (GetPlayerState(playerid) == PLAYER_STATE_DRIVER))
		g_sp_player_is_holding_key_down[playerid] = GetTickCount();
	if((oldkeys & KEY_JUMP) && (GetPlayerState(playerid) == PLAYER_STATE_DRIVER))
		g_sp_player_is_holding_key_down[playerid] = 0x7FFFFFFF;
#if	defined	OnPlayerKeyStateChange
	g_sp_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif
	return 1;
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif
#define	OnPlayerKeyStateChange g_sp_OnPlayerKeyStateChange
#if	defined	g_sp_OnPlayerKeyStateChange
forward g_sp_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

stock g_sp_UpdatePlayerSpeedometer(playerid, vehicleid)
{
	new i;
	if(vehicleid == INVALID_VEHICLE_ID)
	{
	    i = 6;
	    while(--i != -1)
			TextDrawHideForPlayer(playerid, TD_speedometer[i]);
		i = 7;
		while(--i != -1)
		    PlayerTextDrawHide(playerid, PTD_speedometer[playerid][i]);
        g_sp_player_is_holding_key_down[playerid] = 0x7FFFFFFF;
		return 1;
	}
	new v_engine;
	new v_doors;
	new v_lights;
	new v_speed = g_sp_GetVehicleSpeed(vehicleid);
	new v_status[20];
	GetVehicleParamsEx(vehicleid, v_engine, v_lights, i, v_doors, i, i, i);
	strcat(v_status, (v_engine) ? ("~g~E_") : ("~r~E_"));
	strcat(v_status, (v_doors) ? ("~r~_D_") : ("~g~_D_"));
	strcat(v_status, (v_lights) ? ("~g~_L") : ("~r~_L"));
	PlayerTextDrawSetString(playerid, PTD_speedometer[playerid][6], v_status);
	PlayerTextDrawShow(playerid, PTD_speedometer[playerid][6]);
	v_status[0] = EOS;
	if(!v_engine)
	{
	    g_sp_vehicle_gearbox[playerid] = 0;
	    PlayerTextDrawSetPreviewRot(playerid, PTD_speedometer[playerid][5], 0.000000, gearbox_level[g_sp_vehicle_gearbox[playerid]], 70.000000, 2.000000);
		PlayerTextDrawShow(playerid, PTD_speedometer[playerid][5]);
		return 1;
	}
	valstr(v_status, v_speed);
	PlayerTextDrawSetString(playerid, PTD_speedometer[playerid][0], v_status);
	PlayerTextDrawShow(playerid, PTD_speedometer[playerid][0]);
	if((GetTickCount()-g_sp_player_is_holding_key_down[playerid]) >= 1600)
	    g_sp_vehicle_gearbox[playerid] = 6;
	else
	{
	    if(g_sp_vehicle_gearbox[playerid] == 0 || g_sp_vehicle_gearbox[playerid] == 6)
	        g_sp_vehicle_gearbox[playerid] = 1;
		if(v_speed >= gearbox_lvl_shifter[GetVehicleModel(vehicleid)-401]*g_sp_vehicle_gearbox[playerid])
		{
		    if(g_sp_vehicle_gearbox[playerid] < 5)
				g_sp_vehicle_gearbox[playerid]++;
		}
		else if(v_speed+5 <= gearbox_lvl_shifter[GetVehicleModel(vehicleid)-401]*(g_sp_vehicle_gearbox[playerid]-1))
		{
		    if(g_sp_vehicle_gearbox[playerid] > 1)
				g_sp_vehicle_gearbox[playerid]--;
		}
	}
	PlayerTextDrawSetPreviewRot(playerid, PTD_speedometer[playerid][5], 0.000000, gearbox_level[g_sp_vehicle_gearbox[playerid]], 70.000000, 2.000000);
	PlayerTextDrawShow(playerid, PTD_speedometer[playerid][5]);
 	return 1;
}

stock g_sp_GetVehicleSpeed(vehicleid)
{
    new Float:x;
    new Float:y;
    new Float:z;
    GetVehicleVelocity(vehicleid, x, y, z);
	return floatround(floatsqroot(x*x+y*y+z*z)*163);
}
