/*
          Teleports 1.2
      (c) Copyright 2013-2014 by mrdrifter
 
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
	  @date      : 16 listopada 2013
	  @update    : 20 stycznia 2014
  
 */

#define MAX_TELES 200 //max ilosc TP
#define CATEGORIES 3

#define TELES_BLOCK 276, 275, 271 //id teleportow ktore nie maja byc spawnami
 
enum TelesEn
{
	telID,
	telName[32],
	telInterior, 
	telGang,
	Float:telPos[4],
	bool:telSpawn,
	bool:telLoad,
	telFreeze
}
new tInfo[MAX_TELES][TelesEn],
	loadedTeleports;
new teleporty[CATEGORIES][2624];

enum pickups {
	tpData_text[128],
	tpData_pickupid,
	Float:tpto_pos[4],
	tpData_interior,
	
	Text3D:tpData_t3d,
	tpData_mapicon,
	tpData_gang
}

#define MAX_TELEPICKUPS 400


new TelePickups[MAX_TELEPICKUPS][pickups], telePickapow;

#define MAX_SPAWNS 200
new Float:Spawns_player[MAX_SPAWNS][4], loadspawns;

stock LoadSpawns()
{
	new czas = GetTickCount(),buffs[512];
	loadspawns = 0;
	m_query("select pos_x,pos_y,pos_z,pos_a from "prefix"_spawns limit %d ",MAX_SPAWNS);
	mysql_store_result();
	while(mysql_fetch_row(buffs, "|"))
	{
		sscanf(buffs, "p<|>ffff", Spawns_player[loadspawns][0],Spawns_player[loadspawns][1],Spawns_player[loadspawns][2], Spawns_player[loadspawns][3] );
		CreateDynamic3DTextLabel("Zapraszamy na nasze forum: {FFFF99}4fun-serv.eu\n{F4A460}Chcesz zakupiæ konto VIP? odpowiedŸ {FFFF99}/Portfel{c72a00}.\n{E53E01}Wszystkie komendy znajdziesz pod {FFFF99}/CMD{c72a00}\n{FCAD43}Lista teleportów pod {FFFF99}/Teles{c72a00}.\n{33AA33}Widzisz cheatera? wpisz {FFFF99}/Raport{c72a00}.", 0xc72a00ff, Spawns_player[loadspawns][0],Spawns_player[loadspawns][1],Spawns_player[loadspawns][2]+0.2, 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 30.0);
		CreateDynamicPickup(1239, 1, Spawns_player[loadspawns][0],Spawns_player[loadspawns][1],Spawns_player[loadspawns][2]-0.4, 0, 0, -1);
		loadspawns++;
	}
	mysql_free_result();
	printf("[load] wczytanych  spawnów:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
}
LoadTeleports()
{
	for(new xi;xi<8;xi++) 	CreateDynamic3DTextLabel("-",-1,0.0,0.0,0.0,0.1);
	
	new czas = GetTickCount();
	
	teleporty[0][0] = EOS;
	teleporty[1][0] = EOS;
	teleporty[2][0] = EOS;
  
	format(teleporty[2], 256, ""chat" Stwórz teleport Gangu!");
	mysql_query("SELECT * FROM "prefix"_teles");
	mysql_store_result();
	new f[16], position[128];
	loadedTeleports = 1;
	for(new i;i<mysql_num_rows();i++)
	{
		mysql_data_seek(i);//
		mysql_fetch_row_data();

		mysql_fetch_field("name", tInfo[loadedTeleports][telName]);	
		
		#if defined Plugin_4Fun
		Plugin_SaveTeleport(tInfo[loadedTeleports][telName], loadedTeleports);
		#endif
		mysql_fetch_field("interior", f);	
		tInfo[loadedTeleports][telInterior] = strval(f);
		
		
		mysql_fetch_field("togang", f);	
		tInfo[loadedTeleports][telGang] = strval(f);
		
		mysql_fetch_field("freeze", f);	
		tInfo[loadedTeleports][telFreeze] = strval(f);
		
		mysql_fetch_field("id", f);	
		tInfo[loadedTeleports][telID] = strval(f);
		
		tInfo[loadedTeleports][telSpawn] = true;
		
		mysql_fetch_field("position", position);	
		sscanf(position, "p<,>a<f>[4]", tInfo[loadedTeleports][telPos]);
		
		mysql_fetch_field("type", f);	
		new cat = strval(f);
		
		if(tInfo[loadedTeleports][telGang]>0) cat=2;
		
		format(teleporty[cat], 2600, "%s\n"chat" %s", teleporty[cat], tInfo[loadedTeleports][telName]);
		
		tInfo[loadedTeleports][telLoad] = true;
		CrateSpawnLabel(loadedTeleports);
		loadedTeleports++;
		 
	}
	printf("[load] wczytanych aren ch:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	mysql_free_result();
	LoadInfosMapIconsEtc();
	LoadTelePickup();
}
LoadTelePickup(bool:tdebug=false){
	mysql_query("SELECT * FROM "prefix"_telepickups limit "#MAX_TELEPICKUPS"");
	mysql_store_result();
	new Float:_pos[3], interior, pickupid, str2[128], mapicon, id, data[64];
	new i;
	telePickapow=0;
	for(;i<mysql_num_rows();)
	{
		mysql_data_seek(i);//
		mysql_fetch_row_data();
		
		if (IsValidDynamicPickup(TelePickups[i][tpData_pickupid]) || TelePickups[i][tpData_pickupid])
			DestroyDynamicPickup(TelePickups[i][tpData_pickupid]);
		if (IsValidDynamic3DTextLabel(TelePickups[i][tpData_t3d]) || TelePickups[i][tpData_t3d])
			DestroyDynamic3DTextLabel(TelePickups[i][tpData_t3d]);
		if (IsValidDynamicMapIcon(TelePickups[i][tpData_mapicon]) || TelePickups[i][tpData_mapicon])
			DestroyDynamicMapIcon(TelePickups[i][tpData_mapicon]);

				
		#define telep_FetchInt(%0) (mysql_fetch_field(%0, data), strval(data))
		
		interior = telep_FetchInt("tinterior");
		id = telep_FetchInt("id");
		pickupid = telep_FetchInt("pickup_model");
		mapicon = telep_FetchInt("mapicon");
		TelePickups[i][tpData_interior] = telep_FetchInt("tointerior");
		TelePickups[i][tpData_gang] = telep_FetchInt("gang");
		
		mysql_fetch_field("ttext", TelePickups[i][tpData_text]);
		
		mysql_fetch_field("posxyz", str2);
		sscanf(str2, "p<,>a<f>[3]", _pos);
		
		mysql_fetch_field("toposxyz", str2);
		sscanf(str2, "p<,>a<f>[4]", TelePickups[i][tpto_pos]);
	
		TelePickups[i][tpData_pickupid] = CreateDynamicPickup(pickupid, 1, _pos[0], _pos[1], _pos[2]+0.25, -1, interior, -1);
		if(tdebug) printf("tworze w %f. %f. %f", _pos[0], _pos[1], _pos[2]);
		
		if(tdebug) format(TelePickups[i][tpData_text], 128, "%s\n[%d]",TelePickups[i][tpData_text], id);
		if(TelePickups[i][tpData_gang]) format(TelePickups[i][tpData_text], 128, "%s\n{FFFFFF}Tylko dla cz³onków {%06x}<%s>",TelePickups[i][tpData_text], gInfo[GetGangFromUid(TelePickups[i][tpData_gang])][gangColor]>>>8, gInfo[GetGangFromUid(TelePickups[i][tpData_gang])][gangNazwa]);
		if(TelePickups[i][tpData_text][0])
		{
			TelePickups[i][tpData_t3d] = CreateDynamic3DTextLabel(TelePickups[i][tpData_text],0xFFFFFFFF, _pos[0], _pos[1], _pos[2]+0.3, 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, interior);
		}
		if (mapicon>0) {
			TelePickups[i][tpData_mapicon] = CreateDynamicMapIcon(_pos[0], _pos[1], _pos[2], mapicon, 1, -1, interior, -1, 1200.0);
		}
		telePickapow++;
		i++;
	}
 
	for (;i<MAX_TELEPICKUPS;i++) 
	{
		if (IsValidDynamicPickup(TelePickups[i][tpData_pickupid]))
			DestroyDynamicPickup(TelePickups[i][tpData_pickupid]);
		if (IsValidDynamic3DTextLabel(TelePickups[i][tpData_t3d]))
			DestroyDynamic3DTextLabel(TelePickups[i][tpData_t3d]);
		if (IsValidDynamicMapIcon(TelePickups[i][tpData_mapicon]))
			DestroyDynamicMapIcon(TelePickups[i][tpData_mapicon]);

	}


	mysql_free_result();
	return 1;
}

stock OnPlayerEnterTelePickup(playerid, i)
{
	new bool:succes = true;
	
	//if(pInfo[playerid][player_lasthouse_dialogshow] > gettime()) return 0;
	if(pInfo[playerid][player_arena] || is_event(playerid)) SendClientMessage(playerid, COLOR_ERROR, ""chat" Na arenach i eventach nie mo¿na korzystaæ z telepickapów"), succes = false;
	
	if(TelePickups[i][tpData_gang]>=1&&gInfo[pInfo[playerid][player_gang]][gangid]!=TelePickups[i][tpData_gang])
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Teleport tylko dla cz³onków gangu %s (%s).", gInfo[GetGangFromUid(TelePickups[i][tpData_gang])][gangNazwa], gInfo[GetGangFromUid(TelePickups[i][tpData_gang])][gangTag]);
		succes = false;
	}
			
	pInfo[playerid][player_lasthouse_dialogshow] = gettime() + 2;
	if(!succes) return 0;
	
	SetPlayerPos(playerid, TelePickups[i][tpto_pos][0], TelePickups[i][tpto_pos][1], TelePickups[i][tpto_pos][2]);
	SetPlayerFacingAngle(playerid, TelePickups[i][tpto_pos][3]);
	SetPlayerInterior(playerid, TelePickups[i][tpData_interior]);
	
	return 1;
}

LoadInfosMapIconsEtc()
{

	new czas = GetTickCount();
	
	mysql_query("SELECT * FROM "prefix"_infos");
	mysql_store_result();
	new data[128], text[256], Float:e_pos[3], model, type;
	for(new i;i<mysql_num_rows();i++)
	{
		mysql_data_seek(i);//
		mysql_fetch_row_data();

		mysql_fetch_field("text", text);	
		
		mysql_fetch_field("model", data);	
		model = strval(data);
		
		mysql_fetch_field("type", data);	
		type = strval(data);
		
		mysql_fetch_field("cordob", data);	
		sscanf(data, "p<,>a<f>[3]", e_pos);
		
		switch(type)
		{
			case 0:
			{
				CreateDynamic3DTextLabel(text, COLOR_INFO, e_pos[0],e_pos[1],e_pos[2], 30.0);
			}
			case 1:
			{
				Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, CreateDynamicMapIcon(e_pos[0], e_pos[1], e_pos[2], model, 1, 0, 0, -1, 1200.0), E_STREAMER_STYLE, 1);
			}
		}
	
		 
	}
	printf("[load] wczytanych aren ch:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	mysql_free_result();
}
stock CrateSpawnLabel(s)
{
	//new Float:change = 2.5;
//	if(GetServerVarAsInt ("port") != 7777)
//	{
//		CreateDynamicMapIcon (tInfo[s][telPos][0] ,tInfo[s][telPos][1] ,tInfo[s][telPos][2] , 57, 1, -1, 0, -1, 1200.0);
//	}
	new buffs[128];
	format(buffs,sizeof buffs, "Teleport: {%06x}%s",COLOR_ERROR>>>8,tInfo[s][telName]);
 	CreateDynamic3DTextLabel(buffs, 0x008000FF, tInfo[s][telPos][0],tInfo[s][telPos][1],tInfo[s][telPos][2]-0.9, 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 30.0);
	

	/*switch(random(3))
	{
		case 0:
		{
			CreateDynamic3DTextLabel("Chcesz zakupiæ konto VIP? odpowiedŸ {FFFF99}/Portfel{c72a00}.", 0xF4A46090, tInfo[s][telPos][0]+change,tInfo[s][telPos][1],tInfo[s][telPos][2], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 30.0);
			CreateDynamic3DTextLabel("Wszystkie komendy znajdziesz pod {FFFF99}/CMD{c72a00}.", 0xE53E0190, tInfo[s][telPos][0]-change,tInfo[s][telPos][1],tInfo[s][telPos][2], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 30.0);
			CreateDynamic3DTextLabel("Lista tInfoów pod {FFFF99}/Teles{c72a00}.", 0xFCAD4390, tInfo[s][telPos][0],tInfo[s][telPos][1]+change,tInfo[s][telPos][2], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 30.0);
			CreateDynamic3DTextLabel("{c72a00}Zapraszamy na nasze forum: {FFFF99}4fun-serv.pl", 0x33AA3390, tInfo[s][telPos][0],tInfo[s][telPos][1]-change,tInfo[s][telPos][2], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 30.0);
		}
		case 1:
		{
			CreateDynamic3DTextLabel("Chcesz do³adowaæ swój portfel? Wpisz {FFFF99}/Portfel{c72a00}.", 0xF4A46090, tInfo[s][telPos][0]+change,tInfo[s][telPos][1],tInfo[s][telPos][2], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 30.0);
			CreateDynamic3DTextLabel("Nie posiadasz broni? Wpisz komendê {FFFF99}/Bronie{c72a00}.", 0xE53E0190, tInfo[s][telPos][0]-change,tInfo[s][telPos][1],tInfo[s][telPos][2], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 30.0);
			CreateDynamic3DTextLabel("Wszystkie komendy serwera pod {FFFF99}/CMD{c72a00}.", 0xFCAD4390, tInfo[s][telPos][0],tInfo[s][telPos][1]-change,tInfo[s][telPos][2], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 30.0);
			CreateDynamic3DTextLabel("Jesteœ tu nowy? potrzebujesz pomocy? {FFFF99}/Pomoc{c72a00}.", 0x33AA3390, tInfo[s][telPos][0],tInfo[s][telPos][1]-change,tInfo[s][telPos][2], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 30.0);

		}
		case 2:
		{
			CreateDynamic3DTextLabel("Szukasz gangu? Wpisz komendê {FFFF99}/Gang{c72a00} :)", 0xE53E0190, tInfo[s][telPos][0]+change,tInfo[s][telPos][1],tInfo[s][telPos][2], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 30.0);
			CreateDynamic3DTextLabel("Nie posiadasz broni? Wpisz komendê {FFFF99}/Bronie{c72a00}.", 0xF4A46090, tInfo[s][telPos][0]-change,tInfo[s][telPos][1],tInfo[s][telPos][2], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 30.0);
			CreateDynamic3DTextLabel("Prywatny pojazd? Wpisz {FFFF99}/PrywatnyPojazd{c72a00}.", 0x33AA3390, tInfo[s][telPos][0],tInfo[s][telPos][1]+change,tInfo[s][telPos][2], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 30.0);
			CreateDynamic3DTextLabel("Wszystkie komendy serwera pod {FFFF99}/CMD{c72a00}.", 0xFCAD4390, tInfo[s][telPos][0],tInfo[s][telPos][1]-change,tInfo[s][telPos][2], 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 30.0);
		}
	}*/
}
stock LastTeleportID()
{
	for(new i = loadedTeleports; i < MAX_TELES; i++) if(!tInfo[i][telLoad]) return i+1;
	return 0;
}
stock SetPlayerSpawn(playerid)
{
	if(pInfo[playerid][player_sync] || (GetPVarInt(playerid, "flo_command")-25) > gettime())
	{
		pInfo[playerid][player_sync] = false;
		return 1;
	}
	
	switch(pInfo[playerid][wybrany_spawn])
	{
		case 0: {
			new rand = random(loadspawns);
			SetPlayerPos(playerid, Spawns_player[rand][0], Spawns_player[rand][1], Spawns_player[rand][2]);
			SetPlayerFacingAngle(playerid, Spawns_player[rand][3]);
			SetPlayerInterior(playerid,0);
		}
		case 1: {
			if(pInfo[playerid][player_house] == 0) {
				pInfo[playerid][wybrany_spawn] = 0;
				SendClientMessage(playerid,-1,"{FF0000}Twój dom straci³ wa¿noœæ. Twój standardowy spawn zosta³ zmieniony na losowy.");
				new rand = random(loadspawns);
				SetPlayerPos(playerid, Spawns_player[rand][0], Spawns_player[rand][1], Spawns_player[rand][2]);
				SetPlayerFacingAngle(playerid, Spawns_player[rand][3]);
				SetPlayerInterior(playerid,0);
			} else {
				SendClientMessage(playerid,-1,"{FFFFFF}Zosta³eœ zrespawnowany przed swoim domem. Je¿eli chcesz zmieniæ swój spawn wpisz {FFFF00}/konto{FFFFFF} i wybierz opcjê '{FFFF00}Zmieñ spawn{FFFFFF}'");
				exitPlayerHouse(playerid, pInfo[playerid][player_thouse]);
			}
		}
		case 2: {
			if(!pInfo[playerid][player_gang]) {
				pInfo[playerid][wybrany_spawn] = 0;
				SendClientMessage(playerid,-1,"{FF0000}Ju¿ nie posiadasz gangu. Twój standardowy spawn zosta³ zmieniony na losowy.");
				new rand = random(loadspawns);
				SetPlayerPos(playerid, Spawns_player[rand][0], Spawns_player[rand][1], Spawns_player[rand][2]);
				SetPlayerFacingAngle(playerid, Spawns_player[rand][3]);
				SetPlayerInterior(playerid,0);
			} else {
				SendClientMessage(playerid,-1,"{FFFFFF}Zosta³eœ zrespawnowany w bazie gangu. Je¿eli chcesz zmieniæ swój spawn wpisz {FFFF00}/konto{FFFFFF} i wybierz opcjê '{FFFF00}Zmieñ spawn{FFFFFF}'");
				DialogFunc:DIALOG_GANG(playerid, 1, 1, "B gf");
			}
		}
		default: {
			new rand = random(loadspawns);
			SetPlayerPos(playerid, Spawns_player[rand][0], Spawns_player[rand][1], Spawns_player[rand][2]);
			SetPlayerFacingAngle(playerid, Spawns_player[rand][3]);
		}
	}

	
	
	SetPlayerVirtualWorld(playerid, 0);
	FreezePlayerTime(playerid, 2);
	//new i = random(loadedTeleports);
	 
	//if(TeleportsBlocked(tInfo[i][telID]) || (gInfo[pInfo[playerid][player_gang]][gangid] != tInfo[i][telGang] && tInfo[loadedTeleports][telGang] > 0)) return SetPlayerSpawn(playerid);
	TogglePlayerControllable(playerid, 1);
	
//	SetPlayerTeleport(playerid, i);
	
	//format(string2, sizeof(string2), "Zespawnowano Cie do %s", tInfo[i][telName]);
	//ShowPlayerDialog(playerid, 9998, DIALOG_STYLE_MSGBOX, "Spawn", string2, "Zamknij", "");
	
	pInfo[playerid][player_spawnkill] = 3;
	pInfo[playerid][player_spawned]=true;
 	SetPlayerHealth(playerid, 1000.0);
	UpdateSpec(playerid);

	TextDrawShowForPlayer(playerid, SpawnOchrona);
	//GivePlayerEquipment(playerid);
	return 1;
	
}
stock TeleportsBlocked(t)
{
	switch(t) 
	{
		case TELES_BLOCK: return 1;
	}
	return 0;
}
stock SetPlayerTeleport(playerid, listitem)
{
	if(pInfo[playerid][player_driftcouter] == true)return SendClientMessage(playerid,COLOR_ERROR,"Nie mo¿esz siê teraz teleportowaæ");
	
	if(GetPVarInt(playerid, "Dyskoteka"))  
	{
		DeletePVar(playerid, "Dyskoteka");
		StopAudioStreamForPlayer(playerid);
	}
	
	achievement(playerid, 30);
	
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && tInfo[listitem][telInterior] == 0)
	{
		new veh = GetPlayerVehicleID(playerid);
		SetVehiclePos(veh, tInfo[listitem][telPos][0], tInfo[listitem][telPos][1], tInfo[listitem][telPos][2] + 0.5);
		SetVehicleZAngle(veh, tInfo[listitem][telPos][3]);
		LinkVehicleToInterior(veh, 0);
	}
	else
	{
		SetPlayerPos(playerid, tInfo[listitem][telPos][0], tInfo[listitem][telPos][1], tInfo[listitem][telPos][2] + 0.6);
		SetPlayerFacingAngle(playerid, tInfo[listitem][telPos][3]);
	}
	SetPlayerInterior(playerid, tInfo[listitem][telInterior]);
	SetPlayerVirtualWorld(playerid, 0);
	
	SetCameraBehindPlayer(playerid);
	Streamer_Update(playerid);
	
	if(tInfo[loadedTeleports][telFreeze]) FreezePlayerTime(playerid, 2);
	
	InfoTDBox(playerid, splitf("~w~Witamy ~g~na:~n~ ~r~%s", tInfo[listitem][telName]));
	return 1;
}