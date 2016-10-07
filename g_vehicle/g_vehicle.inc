#if defined __g_veh_included
#endinput
#endif
#define __g_veh_included

const g_veh_MAX_VEHICLE_NAME = 18;

static g_veh_color[MAX_VEHICLES][2];
static g_veh_paintjobid[MAX_VEHICLES];
static g_veh_id;
static const g_veh_name[][] = 
{
	"Landstalker", "Bravura", "Buffalo", "Linerunner", "Pereniel", "Sentinel", 
	"Dumper", "Firetruck", "Trashmaster", "Stretch", "Manana", "Infernus", 
	"Voodoo", "Pony", "Mule", "Cheetah", "Ambulance", "Leviathan", "Moonbeam",
	"Esperanto", "Taxi", "Washington", "Bobcat", "Mr Whoopee", "BF Injection",
	"Hunter", "Premier", "Enforcer", "Securicar", "Banshee", "Predator", "Bus", 
	"Rhino", "Barracks", "Hotknife", "Trailer", "Previon", "Bus", "Cabbie",  
	"Stallion", "Rumpo", "RC Bandit", "Romero", "Packer", "Monster Truck", 
	"Admiral", "Squalo", "Seasparrow", "Pizzaboy", "Tram", "Trailer", 
	"Turismo", "Speeder", "Reefer", "Tropic", "Flatbed", "Yankee", "Caddy", 
	"Solair", "Berkley's RC Van", "Skimmer", "PCJ-600", "Faggio", "Freeway", 
	"RC Baron", "RC Raider", "Glendale", "Oceanic", "Sanchez", "Sparrow",
	"Patriot", "Quad", "Coastguard", "Dinghy", "Hermes", "Sabre", "Rustler", 
	"ZR-350", "Walton", "Regina", "Comet", "BMX", "Burrito", "Camper", 
	"Marquis", "Baggage", "Dozer", "Maverick", "News Chopper", "Rancher", 
	"FBI Rancher", "Virgo", "Greenwood", "Jetmax", "Hotring", "Sandking",  
	"Blista Compact", "Police Maverick", "Boxville", "Benson", "Mesa",  
	"RC Goblin", "Hotring Racer", "Hotring Racer", "Bloodring Banger", 
	"Rancher", "Super GT", "Elegant", "Journey", "Bike", "Mountain Bike",  
	"Beagle", "Cropdust", "Stunt", "Tanker", "RoadTrain", "Nebula", "Majestic",
	"Buccaneer", "Shamal", "Hydra", "FCR-900", "NRG-500", "HPV1000",  
	"Cement Truck", "Tow Truck", "Fortune", "Cadrona", "FBI Truck", "Willard", 
 	"Forklift", "Tractor", "Combine", "Feltzer", "Remington", "Slamvan", 
 	"Blade", "Freight", "Streak", "Vortex", "Vincent", "Bullet", "Clover", 
 	"Sadler", "Firetruck", "Hustler", "Intruder", "Primo", "Cargobob", "Tampa", 
 	"Sunrise", "Merit", "Utility", "Nevada", "Yosemite", "Windsor", 
 	"Monster Truck", "Monster Truck", "Uranus", "Jester", "Sultan", "Stratum", 
 	"Elegy", "Raindance", "RC Tiger", "Flash", "Tahoma", "Savanna",  
 	"Bandito", "Freight", "Trailer", "Kart", "Mower", "Duneride", "Sweeper", 
 	"Broadway", "Tornado", "AT-400", "DFT-30", "Huntley", "Stafford", "BF-400", 
 	"Newsvan", "Tug", "Trailer", "Emperor", "Wayfarer", "Euros", "Hotdog", 
 	"Club", "Trailer", "Trailer", "Andromada", "Dodo", "RC Cam", "Launch",  
 	"Police (LSPD)", "Police (SFPD)", "Police (LVPD)", "Police Ranger", 
 	"Picador", "S.W.A.T. Van", "Alpha", "Phoenix", "Glendale", "Sadler", 
 	"Luggage Trailer", "Luggage Trailer", "Stair Trailer", "Boxville", 
 	"Farm Plow", "Utility Trailer"
};

stock g_veh_CreateVehicle(vehicletype, 
	Float:x, Float:y, Float:z, Float:rotation, 
	color1, color2, respawn_delay, addsiren=0)
{
	if((g_veh_id = CreateVehicle(vehicletype, x, y, z, rotation, 
		color1, color2, respawn_delay, addsiren)) != INVALID_VEHICLE_ID)
	{
		g_veh_color[g_veh_id][0] = color1;
		g_veh_color[g_veh_id][1] = color2;
	}	
	return g_veh_id; 
}
#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif

#define CreateVehicle g_veh_CreateVehicle

stock g_veh_AddStaticVehicle(modelid, 
	Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2)
{
	if((g_veh_id = AddStaticVehicle(modelid, 
		spawn_x, spawn_y,spawn_z, z_angle, 
		color1, color2)) != INVALID_VEHICLE_ID)
	{
		g_veh_color[g_veh_id][0] = color1;
		g_veh_color[g_veh_id][1] = color2;
	}	
	return g_veh_id; 
}
#if defined _ALS_AddStaticVehicle
	#undef AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif

#define AddStaticVehicle g_veh_AddStaticVehicle

stock g_veh_AddStaticVehicleEx(modelid, 
	Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, 
	color1, color2, respawn_delay, addsiren=0)
{
	if((g_veh_id = AddStaticVehicleEx(modelid, 
		spawn_x, spawn_y, spawn_z, z_angle, 
		color1, color2, respawn_delay, addsiren)) != INVALID_VEHICLE_ID)
	{
		g_veh_color[g_veh_id][0] = color1;
		g_veh_color[g_veh_id][1] = color2;
	}	
	return g_veh_id; 
}
#if defined _ALS_AddStaticVehicleEx
	#undef AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif

#define AddStaticVehicleEx g_veh_AddStaticVehicleEx

stock g_veh_DestroyVehicle(vehicleid)
{
	g_veh_color[vehicleid][0] = g_veh_color[vehicleid][1] =
	g_veh_paintjobid[vehicleid] = 0;
	return DestroyVehicle(vehicleid);
}
#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif

#define DestroyVehicle g_veh_DestroyVehicle

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	g_veh_paintjobid[vehicleid] = paintjobid;
	#if defined g_veh_OnVehiclePaintjob
		return g_veh_OnVehiclePaintjob(playerid, vehicleid, paintjobid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnVehiclePaintjob
	#undef OnVehiclePaintjob
#else
	#define _ALS_OnVehiclePaintjob
#endif

#define OnVehiclePaintjob g_veh_OnVehiclePaintjob
#if defined g_veh_OnVehiclePaintjob
	forward g_veh_OnVehiclePaintjob(playerid, vehicleid, paintjobid);
#endif

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	g_veh_color[vehicleid][0] = color1;
	g_veh_color[vehicleid][1] = color2;
	#if defined g_veh_OnVehicleRespray
		return g_veh_OnVehicleRespray(playerid, vehicleid, color1, color2);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnVehicleRespray
	#undef OnVehicleRespray
#else
	#define _ALS_OnVehicleRespray
#endif

#define OnVehicleRespray g_veh_OnVehicleRespray
#if defined g_veh_OnVehicleRespray
	forward g_veh_OnVehicleRespray(playerid, vehicleid, color1, color2);
#endif

stock IsVehicleOccupied(vehicleid)
{
#if defined Player@YSII_Ag
	foreach(Player, i)
#else
	for(new i = 0, j = GetPlayerPoolSize(); i < j; i++)
#endif
	{
		if(!IsPlayerConnected(i))
			continue;
		if(GetPlayerVehicleID(i) == vehicleid)
			return 1;
	}
	return 0;
}

stock GetVehicleName(vehicleid, &array[], array_size = sizeof(array))
{
	if(array_size < g_veh_MAX_VEHICLE_NAME)
		return -1;
	else if(!IsValidVehicle(vehicleid))
		return 0;
	array[0] = EOS;
	strcat(array, g_veh_name[GetVehicleModel(vehicleid)-400]);
	return 1;
}

stock GetVehicleColor(vehicleid, color)
{
	if(!IsValidVehicle(vehicleid))
		return -1;
	if(0 < color < 3)
		return g_veh_color[vehicleid][color-1];
	return -2;
}

stock GetVehiclePainjob(vehicleid)
{
	if(!IsValidVehicle(vehicleid))
		return -1;
	return g_veh_paintjobid[vehicleid];
}
