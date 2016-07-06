#if !defined G_GEO_COUNTRY_LESS
const G_GEO_COUNTRY_LENGTH = 32;
#else
const G_GEO_COUNTRY_LENGTH = 3;
#endif
#define G_GEO_COUNTRY_DETECT_URL "freegeoip.net/csv/"

const G_GEO_MAX_IP_LENGTH = 16;

forward g_geo_OnPlayerCountryDetected(playerid, response_code, data[]);

static g_geo_g_geo_player_ip[MAX_PLAYERS][G_GEO_MAX_IP_LENGTH];
new player_country[MAX_PLAYERS][G_GEO_COUNTRY_LENGTH];

public OnPlayerConnect(playerid)
{
	{
	    GetPlayerIp(playerid, g_geo_player_ip[playerid], G_GEO_MAX_IP_LENGTH);
		new request[G_GEO_MAX_IP_LENGTH+19];
		strcat(request, G_GEO_COUNTRY_DETECT_URL);
		strcat(request, g_geo_player_ip[playerid]);
		HTTP(playerid, HTTP_GET, request, "", "g_geo_OnPlayerCountryDetected");
	}
#if defined g_geo_OnPlayerConnect
    g_geo_OnPlayerConnect(playerid);
#endif
    return 1;
}

public g_geo_OnPlayerCountryDetected(playerid, response_code, data[])
{
	if(response_code == 200)
	{
#if defined G_GEO_COUNTRY_LESS
		sscanf(data, "p<,>{s[16]}s[3]{s[1]}", player_country[playerid]);
#else
        sscanf(data, "p<,>{s[16]s[3]}s[32]{s[1]}", player_country[playerid]);
#endif
	}
	else
	{
#if defined G_GEO_COUNTRY_LESS
		strmid(player_country[playerid], "--", 0, G_GEO_COUNTRY_LENGTH);
#else
        strmid(player_country[playerid], "Неизвестно", 0, G_GEO_COUNTRY_LENGTH);
#endif
	}
#if defined G_GEO_SEND_COUNTRY_INFO
	static const content[] = "Новое подключение! \
	Имя: [ {CD0000}%s{ffffff} ]    Страна: [ {CD0000}%s{ffffff} ]";
	new message[sizeof(content)-2+MAX_PLAYER_NAME-2+G_GEO_COUNTRY_LENGTH];
	new g_geo_name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, g_geo_name, MAX_PLAYER_NAME);
	format(message, sizeof(message), content, g_geo_name,
	player_country[playerid]);
	SendClientMessageToAll(-1, message);
#endif
	return 1;
}

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect g_geo_OnPlayerConnect
#if defined g_geo_OnPlayerConnect
forward g_geo_OnPlayerConnect(playerid);
#endif
