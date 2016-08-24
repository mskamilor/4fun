/*
			Functions included
      (c) Copyright 2013-2014 by mrdrifter, Game
 
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/), Game
	  @date      : 14 grudnia 2013
	  @update    : 3 stycznia 2014
  
 */
#define ForceClassSelection xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 
stock SendAdminsMessageEx(color, fmat[])
{
	foreach(new i : Admins)
	{
		p4s_msg(i, color, fmat);
	}
}
#define SendAdminsMessage(%1,%2) (p4s_format(%1, msg_Messger,sizeof(msg_Messger),%2),SendAdminsMessageEx(%1,msg_Messger))
 
  
stock SendMessageEventPlayersEx(fmat[])
{

	foreach(new playerid : EventPlayers) p4s_msg(playerid, 0xDDDD11FF, fmat);
	
	return 1;
}
#define SendMessageEventPlayers(%2) (p4s_format(0xDDDD11FF, msg_Messger,sizeof(msg_Messger),%2),SendMessageEventPlayersEx(msg_Messger))
 
 
stock samp_systemprintfex(soruce[])
{
	return systemprint("print", soruce, true);
}
#define samp_systemprintf(%2) (format(msg_Messger,sizeof(msg_Messger),%2),samp_systemprintfex(msg_Messger))
 
stock systemprintfex(tag[], soruce[], bool:dirtag)
{
	return systemprint(tag, soruce, dirtag);
}
#define systemprintf(%0,%1,%2) (format(msg_Messger,sizeof(msg_Messger),%2),systemprintfex(%0,msg_Messger,%1))
#define systemprintf_nt(%0,%1) (format(msg_Messger,sizeof(msg_Messger),%1),systemprint_nt(%0,msg_Messger))


stock OutputLogEx(tag[], soruce[])
{
	return systemprint(tag, soruce, true);
}
#define OutputLog(%0,%2) (format(msg_Messger,sizeof(msg_Messger),%2),OutputLogEx(%0,msg_Messger))


new sqlinfo, sqltick;
new lastQuery[512];
stock sqlquery(const query[], resultid = (-1), spareid = (0), MySQL:handle = (MySQL:0))
{
	sqltick = GetTickCount();
	sqlinfo = mysql_query(query, resultid, spareid, handle);
	sqltick = GetTickCount() - sqltick;
	
	if (sqltick>30)
	{
		systemprintf("debug_mysql", true, "response: %d, time %d ms - %s ",sqlinfo,sqltick,query);
	}
	if (sqltick>500)
	{
		SendAdminsMessage(COLOR_INFO2, query);
		SendAdminsMessage(COLOR_INFO2, "mysql_query dump: response %d, time %dms" ,sqlinfo,sqltick);
	}
	lastQuery[0] = EOS;
	strcat(lastQuery, query);
	return sqlinfo;
}
#define mysql_query sqlquery


stock _GetPlayerMoney(playerid)
{
	return pInfo[playerid][player_cash];
}
#define GetPlayerMoney(%0) _GetPlayerMoney(%0)

stock _GivePlayerMoney(playerid, money){

	pInfo[playerid][player_cash] = pInfo[playerid][player_cash] + money;
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, pInfo[playerid][player_cash]);

}
#define GivePlayerMoney(%0,%1) _GivePlayerMoney(%0,%1)

stock PlayerTextDrawColorEx(playerid, PlayerText:text, color)
{
	pInfo[playerid][player_textdrawcolor][text] = color;
	return PlayerTextDrawColor(playerid, PlayerText:text, color);
}
#define PlayerTextDrawColor(%0,%1) PlayerTextDrawColorEx(%0,%1)

stock PlayerTextDrawBoxColorEx(playerid, PlayerText:text, color)
{
	pInfo[playerid][player_textdrawboxcolor][text] = color;
	return PlayerTextDrawBoxColor(playerid, PlayerText:text, color);
}
#define PlayerTextDrawBoxColor(%0,%1) PlayerTextDrawBoxColorEx(%0,%1)

stock PlayerTextDrawBackgroundColorEx(playerid, PlayerText:text, color)
{
	pInfo[playerid][player_textdrawbgcolor][text] = color;
	return PlayerTextDrawBackgroundColor(playerid, PlayerText:text, color);
}
#define PlayerTextDrawBackgroundColor(%0,%1) PlayerTextDrawBackgroundColorEx(%0,%1)

stock PutPlayerInVehicleEx(playerid, vehicleid, seatid)
{
	UpdateSpec(playerid);
	pInfo[playerid][player_usevehicle] = vehicleid;
	AC_PutPlayerInVehicleEx(playerid);
	return PutPlayerInVehicle(playerid, vehicleid, seatid);
}
#define PutPlayerInVehicle(%0,%1) PutPlayerInVehicleEx(%0,%1)

stock HK_SetPlayerPos(playerid, Float:x, Float:y, Float:z)
{
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
	
	AC_SetPlayerPos(playerid, x, y, z);
	
	return SetPlayerPos(playerid, x, y, z);
}
#define SetPlayerPos(%0) HK_SetPlayerPos(%0)


/*
stock GivePlayerWeaponEx(playerid, weaponid, ammo)
{
	pInfo[playerid][player_weapons][weaponid] = true; 
	return GivePlayerWeapon(playerid, weaponid, ammo);
}
#define GivePlayerWeapon(%0,%1,%2) GivePlayerWeaponEx(%0,%1,%2)

*/
Public:Call_GivePlayerWeaponEx(playerid, weaponid, ammo)
{
	
	if(!IsPlayerValid(playerid) && IsWeaponWH(weaponid)) pInfo[playerid][player_weapons][weaponid] = true; 
	return 1;
}

Public:Call_ResetPlayerWeaponsEx(playerid)
{
	
	for(new i;i<46;i++) SetPlayerAmmo(playerid, i, 0);
	
	for(new ply; ply<50;ply++)  pInfo[playerid][player_weapons][ply] = false;
	return 1;
}
#if defined ADUIO_PLUGIN
stock Audio_PlayStreamedEx(playerid,url[])
{
	if (!Audio_IsClientConnected(playerid)) 
		return false;	
	if(pInfo[playerid][player_stacja]) 
	{
		Audio_Stop(playerid,pInfo[playerid][player_stacja]);
	}
	pInfo[playerid][player_stacja] = Audio_PlayStreamed(playerid, url);
	return 1;
}
stock Audio_StreamedStopEx(playerid)
{
	if (!Audio_IsClientConnected(playerid)) 
		return false;
	if(pInfo[playerid][player_stacja]) 
	{
		Audio_Stop(playerid,pInfo[playerid][player_stacja]);
	}
	return 1;
}
stock Audio_PlayEx(playerid,audioid)
{
	if (!Audio_IsClientConnected(playerid)) 
		return 0;	
	if(pInfo[playerid][player_sound]) 
	{
		if(pInfo[playerid][player_stacja]) 
		{
			Audio_Resume(playerid, pInfo[playerid][player_stacja]);
		}
		Audio_Stop(playerid,pInfo[playerid][player_sound]);
	}
	if(pInfo[playerid][player_pause]==false)
	{
		if(pInfo[playerid][player_stacja]) 
		{
			pInfo[playerid][player_pause]=true;
			Audio_SetVolume(playerid,pInfo[playerid][player_stacja],10);
		}
	}
	pInfo[playerid][player_sound] = Audio_Play(playerid, audioid);
	Audio_SetVolume(playerid,pInfo[playerid][player_sound], 100);
	return 1;
}
stock Audio_StopEx(playerid)
{
	if(!Audio_IsClientConnected(playerid)) 
		return 0;
	if(pInfo[playerid][player_sound]) 
	{
		Audio_Stop(playerid,pInfo[playerid][player_sound]);
	}
	return 1;
}
public Audio_OnTransferFile(playerid, file[], current, total, result) 
{
    /* // szkoda spamiæ chat (...)
	if(current==1) 
	{ 		
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Rozpoczeto synchronizacje plikow audio");
	}
	*/
    if(total==current)
	{
		SendClientMessage(playerid, COLOR_GOLD, ""chat" Synchronizacja plikow audio zakonczona");
	}
    return 1;
}
public Audio_OnClientConnect(playerid) 
{
    Audio_TransferPack(playerid);
}
public Audio_OnClientDisconnect(playerid)
{
	if(!IsPlayerConnected(playerid)) 
		return 0;
	SendClientMessage(playerid, COLOR_GOLD, ""chat" Po³¹czenie z audio pluginem utracone!");
	return 1;
}
public Audio_OnStop(playerid, handleid)
{
	if(pInfo[playerid][player_sound] == handleid)
	{
		if(pInfo[playerid][player_stacja]) 
		{
			if(pInfo[playerid][player_pause]==true)
			{
				Audio_SetVolume(playerid,pInfo[playerid][player_stacja], 100);
				pInfo[playerid][player_pause]=false;
			}
		}
	}
	return 1;
}
#endif
stock IsWeaponWH(weaponid)
{
	switch(weaponid)
	{
		case 16..45: return 1;
	}
	return 0;
}

stock IsAimWeapon(weaponid)
{
	switch(weaponid)
	{
		case 26,28,30,31,32,35..45: return 0;
	}
	return 1;
}
 
forward Call_OnCreateVehicle(modelid);
public Call_OnCreateVehicle(modelid)
{
	Vehicle_PrivClear(modelid);
}

forward Call_DestroyVehicl(modelid);
public Call_DestroyVehicl(modelid)
{ 
	DestroyNeon(modelid);
	return 1;
}


forward GetP4SAdminLevel(a);
public GetP4SAdminLevel(a)
{ 
	return pInfo[a][player_admin];
}

stock BackupRecord(const tquery[], const info[], oneRecord = false)
{ 
	new query[256], d=1;
	new str[1024];
 	m_query("select %s", tquery);
	mysql_store_result();
	
	if(mysql_num_rows())
	{
	    while(mysql_fetch_row(query, ","))
	    {
			if(!oneRecord)
				m_query("INSERT INTO `mreg_backup` (`id`, `file`, `backup`, `ts`) VALUES (NULL, '[%d] %s', '%s', CURRENT_TIMESTAMP);", ++d, info, query);
			else 
				format(str, sizeof(str), "%s *%s*", str, query);
		}
		if(oneRecord)
			m_query("INSERT INTO `mreg_backup` (`id`, `file`, `backup`, `ts`) VALUES (NULL, '[%d] %s', '%s', CURRENT_TIMESTAMP);", ++d, info, str);
		
		mysql_free_result();
	}
	return 1;
}


loadDynamicPickup()
{
	new czas = GetTickCount();
	mysql_query("select * from "prefix"_pickup");
	mysql_store_result();
	if (mysql_num_rows())
	{
		new param[ 128 ];
		while (mysql_fetch_row (param , "|"))
		{
			new id,typ,Float:pos[3];
			sscanf(param, "p<|>ddfff", id, typ, pos[0], pos[1], pos[2]);
			CreateDynamicPickup(typ, 2, pos[0], pos[1], pos[2], 0, -1, -1, 100.0);
		}
		printf("[load] wczytanych pickupow:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	}
	else
		print("[Pickupy] Brak dodanych Pickupów do bazy!");
}

loadDynamicFigure()
{
	FigureCount = 0;
	new czas = GetTickCount();
	mysql_query("select * from "prefix"_figure limit "#MAX_Figure"");
	mysql_store_result();
	if (mysql_num_rows())
	{
		new param[ 128 ];
		while (mysql_fetch_row (param , "|"))
		{
			sscanf(param, "p<|>dfff", FigureInfo[FigureCount][Figureid_sql], FigureInfo[FigureCount][Figurex], FigureInfo[FigureCount][Figurey], FigureInfo[FigureCount][Figurez]);
			
			FigureInfo[FigureCount][Figureid] = CreateDynamicPickup(1276, 23, FigureInfo[FigureCount][Figurex], FigureInfo[FigureCount][Figurey], FigureInfo[FigureCount][Figurez], 0);
			FigureInfo[FigureCount][Figureid_label] = CreateDynamic3DTextLabel("Figurka [/figurka]", 0xFFA500FF, FigureInfo[FigureCount][Figurex], FigureInfo[FigureCount][Figurey], FigureInfo[FigureCount][Figurez], 5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
			
			FigureCount++;
		}
		printf("[load] wczytanych figor:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	}
	else
		print("[FIGURKI] Brak dodanych Figurek do bazy!");
	
	mysql_free_result();
	return 1;
}
CMD:figurka(playerid, cmdt[]){
	 
	format(string2, sizeof(string2), "\n\t\t\t{FFDD00}Figurki\n\n{FF7F10}Figurki s¹ ukryty na ca³ej mapie!\n{FF7F10}Za znalezienie figurki dostajesz a¿ 150 Expa!\n{FF7F10}Wystarszczy ¿e wejdziesz w figurkê a dostaniesz 150 Expa\n{FF7F10}Administratorzy codziennie dodaj¹ nowe figurki\n{FF7F10}Aktualny stan figurek: {FFDD00}%d{FF7F10}/{FFDD00}%d\n\n{FF7F10}Administracja ¿yczy mi³ego szukania figurek :)\n\n", FigureCount, MAX_Figure);
 
	InfoBox(playerid, string2);
	return 1;
}
stock IsValidEmailEx(const string[])
{
    static RegEx:rEmail ;
    if (!rEmail)
    {       
        rEmail = regex_build("[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?");
    }    
    return regex_match_exid(string, rEmail);
}
stock IsValidTextEx(const string[])
{
    static RegEx:rText;
    if(!rText)
    {       
        rText = regex_build("[ a-yA-ßa-zA-Z0-9_,!\\.\\?\\-\\+\\(\\)]+");
    }
    return regex_match_exid(string, rText);
}
stock IsValidUrl(const string[])
{
    static RegEx:rHttp;
    if(!rHttp)
    {       
        rHttp = regex_build(\"^(http|https|ftp)\://[a-zA-Z0-9\-\.]+\.[a-zA-Z]{2,3}(:[a-zA-Z0-9]*)?/?([a-zA-Z0-9\-\._\?\,\'/\\\+&amp;%\$#\=~])*$");
		//rHttp = regex_build(\"(([url]http://)|(https://))?([/url][a-zA-Z0-9]+[.])+[a-zA-Z]{2,4}(:\d+)?(/[~_.\-a-zA-Z0-9=&%@:]+)*\??[~_.\-a-zA-Z0-9=&%@:]*)");
    }
    return regex_match_exid(string, rHttp);
}
stock ContainsIPEx(const string[])
{

	if(strfind(string, "pbsdm", true) != -1 || strfind(string, "goldserver", true) != -1 || strfind(string, "theotherside", true) != -1|| strfind(string, "psr", true) != -1)
	{
//		SendClientMessage(playerid, -1, "[ANTI REKLAMA] Wykryto reklamê, wiadomoœæ nie pojawi³a siê na chacie!");
		return 1;
	} 
    static RegEx:rCIP;
    if(!rCIP)
    {       
        rCIP = regex_build("(.*?)([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})(.*?)");
    }
    return regex_match_exid(string, rCIP);
}
 
stock loadDynamicNoDmZone()
{
	new czas = GetTickCount();
	new query[1024];
	zone_count = 0;
	
	mysql_query("select id, min_x, min_y, max_x, max_y from "prefix"_zones where type = 0  limit "#MAX_ZONE"");
	mysql_store_result();
	
	for(new i;i<MAX_ZONE;i++)
	{
		if(zone_created[zone_count]) DestroyDynamicArea(zone_created[zone_count]); 
	}
	if(!mysql_num_rows())
		print("Nie odnaleziono ¿adnej strefy bez dm!");
	else 
	{
		while(mysql_fetch_row (query))
		{
			sscanf(query, "p<|>dffff", zone[zone_count][zone_id], zone[zone_count][min_x], zone[zone_count][min_y], zone[zone_count][max_x], zone[zone_count][max_y]);
			zone_created[zone_count] = CreateDynamicRectangle(zone[zone_count][min_x], zone[zone_count][min_y], zone[zone_count][max_x], zone[zone_count][max_y]);			
			zone_count++;
		}
		printf("[load] wczytanych stref:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	}
	mysql_free_result();
	gmData[impreza_zone] = -1;//CreateDynamicRectangle(2111.4324,967.4344,2361.2625,1078.9612);	
}
#if defined ADUIO_PLUGIN
stock PlayCompleteMissionSound(playerid)
{
	Audio_PlayEx(playerid, MISSION_COMPLETTE);
}
#endif
stock SetPlayerMoney(playerid, money)
{
	pInfo[playerid][player_cash] = money;
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, pInfo[playerid][player_cash]);
}
stock _ResetPlayerMoney(playerid)
{

	pInfo[playerid][player_cash] = 0;
	ResetPlayerMoney(playerid);
}
#define ResetPlayerMoney(%0) _ResetPlayerMoney(%0)
  
stock _SetPlayerScore(playerid, score)
{

	pInfo[playerid][player_score] = score;
 	SetPlayerScore(playerid, pInfo[playerid][player_score]);

}
#define SetPlayerScore(%0,%1) _SetPlayerScore(%0,%1)
 
 
stock ChangeVehiclePaintjobEx(vehicleid, painthob)
{
	foreach(new fi : Player)
	{
		if(pInfo[fi][player_car_have] == false) continue;
		
		if(gmData[player_vehicleid][fi] == vehicleid)
		{
 			pInfo[fi][player_car_paintjob] = painthob;
			break;
		}
	}	
	return ChangeVehiclePaintjob(vehicleid, painthob);
}
#define ChangeVehiclePaintjob(%0,%1) ChangeVehiclePaintjobEx(%0,%1)

stock GivePlayerScore(playerid, score, reason[] = "")
{
	if(reason[0])
	{
		SendClientMessage(playerid, COLOR_OLD_LACE, ""chat" Dostajesz{87CEEB} %d respektu powód {87CEEB}%s.", score, reason);
	}
	if (score >= 15)
	{
		PlaySoundForPlayer(playerid, 1137);
	}
	else if (score >= 10)
	{
		PlaySoundForPlayer(playerid, 1139);	
	}
	else if (score >= 5)
	{
		PlaySoundForPlayer(playerid, 1138);	
	}
 	if(score > 0)
	{
 		InfoTDBox(playerid, splitf("~w~Respekt ~g~+%d", score));
	}
	else 
	{
		InfoTDBox(playerid, splitf("~w~Respekt ~r~%d", score));
	}
	 
	
	pInfo[playerid][player_score] = (pInfo[playerid][player_score] + score);
 	SetPlayerScore(playerid, pInfo[playerid][player_score]);

}

stock InfoTDBox(playerid, fmat[])
{
	PlayerTextDrawSetString(playerid, playerdraw_respect, fmat);
	
	PlayerTextDrawShow(playerid, playerdraw_respect);
	//TextDrawShowForPlayer(playerid, RespectAddBox);
	pInfo[playerid][player_score_drawhide] = pInfo[playerid][player_connected] > 20 ? (3):(1); 
}

stock strcopy(dest[], const source[], length = sizeof(source))
{
	strins((dest[0] = EOS, dest), source, 0, length);
}

stock GivePlayerPortfel(playerid, zlc)
{
	pInfo[playerid][player_portfel] = (pInfo[playerid][player_portfel] + zlc);
	SavePlayer(playerid);
}
stock _Kick(playerid)
{
	//BlockIpAddress(pInfo[playerid][player_ip], 10);
	SetTimerEx("Kick_", 200, 0, "d", playerid);
	return 1;
}
forward Kick_(playerid);
public Kick_(playerid)
{
	printf("Function Kick_ - %d", playerid);
	Kick(playerid);
	return 1;
}
#define Kick(%0) _Kick(%0)

stock LastVehicleCreated()
{
	new vx = CreateVehicle(511, 22.0, 22.0, 22.2, 30.0, 3, 3, 3);
	new i = vx;
	DestroyVehicleEx(i);
	
	return vx;
}
stock floatval(Float:val)
{  
	new efstr[32];
	format(efstr, 32, "%.0f", val);
	format(efstr, 32, "%s", efstr);
	return strval(efstr);
}
stock Float:GetKilometrsToPoint(playerid, Float:point1, Float:point2, Float:point3)
{
 	new Float:distrace = (GetPlayerDistanceFromPoint(playerid, point1, point2, point3)/100.0);
	return distrace;
}
Float:GetPlayerTheoreticAngle(playerid, Float:x, Float:y, Float:z, Float:angle2)
{
	new Float:angleupd[5];
  
	if(z != 0.5) angleupd[1] = floatsqroot(floatpower(floatabs(floatsub(x, pInfo[playerid][player_driftpos][0])), 2)+floatpower(floatabs(floatsub(y, pInfo[playerid][player_driftpos][1])), 2));
		
	if(x>pInfo[playerid][player_driftpos][0]) angleupd[2] = x - pInfo[playerid][player_driftpos][0];
	else angleupd[2] = pInfo[playerid][player_driftpos][0] - x;
	
	if(y>pInfo[playerid][player_driftpos][1]) angleupd[3] = y - pInfo[playerid][player_driftpos][1];
	else angleupd[3] = pInfo[playerid][player_driftpos][1] - y;
	
	if(pInfo[playerid][player_driftpos][1]>y && pInfo[playerid][player_driftpos][0]>x)
	{
		angleupd[0]  =  asin(angleupd[2]/angleupd[1]);
		angleupd[4]  =  floatsub(floatsub(floatadd(angleupd[0], 90), floatmul(angleupd[0], 2)), - 90.0);
	}
	if(pInfo[playerid][player_driftpos][1]<y && pInfo[playerid][player_driftpos][0]>x)
	{
		angleupd[0]  =  asin(angleupd[2]/angleupd[1]);
		angleupd[4]  =  floatsub(floatadd(angleupd[0], 180), 180.0);
	}
	if(pInfo[playerid][player_driftpos][1]<y && pInfo[playerid][player_driftpos][0]<x)
	{
		angleupd[0]  =  acos(angleupd[3]/angleupd[1]);
		angleupd[4]  =  floatsub(floatadd(angleupd[0], 360), floatmul(angleupd[0], 2));
	}
	if(pInfo[playerid][player_driftpos][1]>y && pInfo[playerid][player_driftpos][0]<x)
	{
		angleupd[0]  =  asin(angleupd[2]/angleupd[1]);
		angleupd[4]  =  floatadd(angleupd[0], 180);
	}
  	
    
    if(angleupd[4]  ==  0.0)
		return angle2;
  	else
		return angleupd[4];
}
stock IsChar(check)
{
	switch(check)
	{
		case '0'..'9': return 0;
	}
	return 1;
}
stock CreateStructure()
{
	
	#define Structure_NEW(%0,%1) new structure_%0[500] = %1
	#define Structure_ADD(%0,%1) strcat(structure_%0,%1)
	#define Structure_build(%0) mysql_query(structure_%0)
	
	//prefix_players
	Structure_NEW(players, "CREATE TABLE IF NOT EXISTS `"prefix"_players` (");
	
	Structure_ADD(players, " `id` int(12) NOT NULL AUTO_INCREMENT,");
	Structure_ADD(players, " `nick` varchar(25) NOT NULL,");
	Structure_ADD(players, " `password` varchar(42) NOT NULL,");
	Structure_ADD(players, " `cash` int(11) NOT NULL DEFAULT '0',");
	Structure_ADD(players, " `admin` int(4) NOT NULL DEFAULT '0',");
	Structure_ADD(players, " `score` int(11) NOT NULL DEFAULT '0',");
	Structure_ADD(players, " `portfel` int(11) NOT NULL DEFAULT '0',");
	Structure_ADD(players, " PRIMARY KEY (`id`)");
	Structure_ADD(players, ") ENGINE=MyISAM  DEFAULT CHARSET=latin2 AUTO_INCREMENT=0 ;");
	Structure_build(players);
}
stock UnCagePlayer(playerid)
{
	if(pInfo[playerid][player_carge_object])
	{
		pInfo[playerid][player_carge_object] = DestroyObject(pInfo[playerid][player_carge_object]);
		pInfo[playerid][player_carge_object] = 0;
	}
}
CagePlayer(playerid)
{
	if(pInfo[playerid][player_carge_object]) UnCagePlayer(playerid);
	if(IsPlayerConnected(playerid))
 	{
		new Float:X5, Float:Y5, Float:Z5;
		GetPlayerPos(playerid, X5, Y5, Z5);
		
		pInfo[playerid][player_carge_object] = CreateObject(18856, X5, Y5, Z5+1,   0.00, 0.00, 0.00);
		PlayerPlaySound(playerid, 1137, X5, Y5, Z5);
	}
	return 1;
}

stock RespectToLevel(lvl)
	return floatround(((lvl+1)*(lvl+1)*7));
	
stock mix_string(string[], Return[], max_swap = 0, dest_size = sizeof Return)
{
	new tmp_str[ 200 ], swap;
	format(tmp_str, 200, "%s", string);
	new size = strlen(tmp_str);
	
	
	for(new i=0; tmp_str[ i ]; i++)
	{
		if(i > size) break;
		if(max_swap > 0 && max_swap == swap) break;
		
		new tmp = tmp_str[ i ], swit = random(size-1);
		
		tmp_str[ i ] = tmp_str[ swit ];
		tmp_str[ swit ] = tmp;
		swap++;
	}
	format(Return, dest_size, tmp_str);
	return true;
}

/*
stock Config_LoadServerConfig()
{
	printf("---------------------------------");
	printf("|     £adowanie configu         |");
	 
  
	m_query("select config_title, config_value from "prefix"_config");
	mysql_store_result();
	
	new f_title[25], f_value[100], f_c;
	for(new i;i<mysql_num_rows();i++)
	{
		mysql_data_seek(i);
		mysql_fetch_row_data();
		
		mysql_fetch_field("config_title", f_title);
		mysql_fetch_field("config_value", f_value);
		
		if(!strcmp(f_title, "hostname", true))
		{
			format(string2, sizeof(string2), "hostname %s", f_value);
			SendRconCommand(string2);
		}
		else
		if(!strcmp(f_title, "gamemodetext", true))
		{
 			SetGameModeText(f_value);
		}
		
		f_c++;
	}
	mysql_free_result();
	printf("|    wczytano %d configi         |", f_c);	
	printf("---------------------------------");
}*/

stock DestroyNeon(vehicleid)
{
	if(vehicleid >= MAX_VEHICLES || vehicleid < 0)  return 1;
	if(VehicleNeon[vehicleid][0] != -1)
	{
		DestroyDynamicObject(VehicleNeon[vehicleid][0]);
		VehicleNeon[vehicleid][0] = -1;
	}
	if(VehicleNeon[vehicleid][1] != -1)
	{
		DestroyDynamicObject(VehicleNeon[vehicleid][1]);
		VehicleNeon[vehicleid][1] = -1;
	}
	return 1;
}
//for register on change pass  
#define isLower(%0) ((%0>=97)&&(%0<=122)) //mala literka
#define isUpper(%0) ((%0>=65)&&(%0<=90))
#define isNumber(%0) ((%0>=48)&&(%0<=57))
 
stock PasswordCheck(password[]) //by mrdrifter
{
        new bool:check[1], rank, i, len = strlen(password);
       
        if(len >= 6) rank++;
       
        while(((isLower(password[i])&&!check{0})?(check{0}=true,rank++):(0),(isUpper(password[i])&&!check{1})?(check{1}=true,rank++):(0),(isNumber(password[i])&&!check{2})?(check{2}=true,rank++):(0)),(len>i++)){}
       
        return rank;
}
stock PasswordCorrect(password[])
{

	for(new i, p = strlen(password);i<p;i++)
	{
		switch(password[i])
		{
			case 'a' .. 'z': continue;
			case 'A' .. 'Z': continue;
			case '0' .. '9': continue;
		//	case '!': continue;
			default: return 0;
 		}
	}
	return 1;
}

stock ValidText(String[])
{
	if(strlen(String) > 32)
	    return false;

    for(new Char = 0, g = strlen(String); Char < g; Char++)
    {
        if(String[Char] >= 'a' && String[Char] <= 'z')
            continue;
		if(String[Char] >= 'A' && String[Char] <= 'Z')
		    continue;
		if(String[Char] >= '0' && String[Char] <= '9')
		    continue;
		if(String[Char] == '_' || String[Char] == '.' || String[Char] == '[' || String[Char] == ']' || String[Char] == '(' || String[Char] == ')')
		    continue;
		return false;
	}
	return true;
}
stock LoadStaticVehiclesFromFile(const filename[])
{
	new File:file_ptr;
	new line[256];
	new var_from_line[64];
	new vehicletype;
	new Float:SpawnX;
	new Float:SpawnY;
	new Float:SpawnZ;
	new Float:SpawnRot;
    new Color1, Color2;
	new index;
	new vehicles_loaded;

	file_ptr = fopen(filename,filemode:io_read);
	if(!file_ptr) return 0;

	vehicles_loaded = 0;

	while(fread(file_ptr,line,256) > 0)
	{
	    index = 0;

	    // Read type
  		index = token_by_delim(line,var_from_line,',',index);
  		if(index == (-1)) continue;
  		vehicletype = strval(var_from_line);
   		if(vehicletype < 400 || vehicletype > 611) continue;

  		// Read X, Y, Z, Rotation
  		index = token_by_delim(line,var_from_line,',',index+1);
  		if(index == (-1)) continue;
  		SpawnX = floatstr(var_from_line);

  		index = token_by_delim(line,var_from_line,',',index+1);
  		if(index == (-1)) continue;
  		SpawnY = floatstr(var_from_line);

  		index = token_by_delim(line,var_from_line,',',index+1);
  		if(index == (-1)) continue;
  		SpawnZ = floatstr(var_from_line);

  		index = token_by_delim(line,var_from_line,',',index+1);
  		if(index == (-1)) continue;
  		SpawnRot = floatstr(var_from_line);

  		// Read Color1, Color2
  		index = token_by_delim(line,var_from_line,',',index+1);
  		if(index == (-1)) continue;
  		Color1 = strval(var_from_line);

  		index = token_by_delim(line,var_from_line,';',index+1);
  		Color2 = strval(var_from_line);
  		
  		//printf("%d,%.2f,%.2f,%.2f,%.4f,%d,%d",vehicletype,SpawnX,SpawnY,SpawnZ,SpawnRot,Color1,Color2);

		AddStaticVehicleExEx(vehicletype,SpawnX,SpawnY,SpawnZ,SpawnRot,Color1,Color2,(30*60)); // respawn 30 minutes
		
		vehicles_loaded++;
	}

	fclose(file_ptr);
 	return vehicles_loaded;
}
 

stock token_by_delim(const string[], return_str[], delim, start_index)
{
	new x=0;
	while(string[start_index] != EOS && string[start_index] != delim) {
	    return_str[x] = string[start_index];
	    x++;
	    start_index++;
	}
	return_str[x] = EOS;
	if(string[start_index] == EOS) start_index = (-1);
	return start_index;
}

stock RandCode(str[]) 
{

	new x, len = random(12) + 5;

	if(len > 16)
		len = 16;

	for(new i; i < len; i++)
	{
	    x = random(35);

	    if(x > 25)
	    {
	        x = (x - 25) + ('0' - 1);

	    	str[i] = x;
		}
		else
		{
		    if(!random(4))

		    	str[i] = toupper(x + 'a');
			else
			    str[i] = x + 'a';
		}
	}
	return str;

}

stock HashCode(str[], bool:dehash = false) 
{

	new x;
	new len = strlen(str);

	for(new i; i < len; i++)
	{
	    x = str[i];
		if(!dehash)
		{
			str[i] = (x + 'A');
		}
		else 
		{
			str[i] = (x - 'A');
		}
	}
	return str;

}

stock GetPlayerObjectFreeSlot(playerid)
{
	for(new i=0; i<MAX_PLAYER_ATTACHED_OBJECTS; i++)
	{
		if(!IsPlayerAttachedObjectSlotUsed(playerid, i)) return i;
	}
	
	return -1;
}

 
stock GetVehicleID(const data[])
{
	new i = -1;
	while(++i < sizeof(VehicleNames))
	{
		if(!(strfind(VehicleNames[i], data, true) == -1)) return i + 400;
	}
	return 0;
}

stock GetVehicleIDStrcmp(const data[])
{
	new i = -1;
	while(++i < sizeof(VehicleNames))
	{
		if(!strcmp(VehicleNames[i], data, true)) return i + 400;
	}
	return 0;
}
IsNumeric(const string[])
{
	for (new i = 0, j = strlen(string); i < j; i++)
	{
		if (string[i] > '9' || string[i] < '0') return 0;
	}
	return 1;
}
 
stock findPlayer(source[]) 
{
 
	if(!strlen(source))
		return INVALID_PLAYER_ID;
	 
	 
	if(IsNumeric(source))
	{
		new p = strval(source);
		if(IsPlayerConnected(p) && p != 0){
			return p;
		}
	}
    new find_from[30];
 	
	foreach(new i : Player) 
	{		
		GetPlayerName(i, find_from, sizeof (find_from));
			 
		if(strcmp(source, find_from, false) == 0)
			return i;  
    }
	
    foreach(new i : Player) 
	{
		GetPlayerIp(i, find_from, sizeof (find_from));
			 
		if(strcmp(source, find_from, false) == 0)
			return i;  
    }
	
    return INVALID_PLAYER_ID;
}


TuneCar(carid)
{
	SetVehicleHealth(carid, 1000);
	new modelid;
	modelid = GetVehicleModel(carid);
	switch(modelid)
	{
		case 400:
		{
		    AddVehicleComponent(carid, 1010);//NOS
		    AddVehicleComponent(carid, 1087);//HYDROLIK
		    AddVehicleComponent(carid, 1018);//POT
		    AddVehicleComponent(carid, 1013);//PHARE ROND
		    AddVehicleComponent(carid, 1081);//JANTE
		    AddVehicleComponent(carid, 1086);//STEREO
	    }
    	case 401:
		{
		    AddVehicleComponent(carid, 1086);//STEREO
		    AddVehicleComponent(carid, 1139);//SPOILER
		    AddVehicleComponent(carid, 1081);//JANTE
		    AddVehicleComponent(carid, 1010);//NOS
		    AddVehicleComponent(carid, 1087);//HYDROLIK
		    AddVehicleComponent(carid, 1012);//CAPOT
		    AddVehicleComponent(carid, 1013);//PHARE ROND
		    AddVehicleComponent(carid, 1042);//CONDUITR
		    AddVehicleComponent(carid, 1043);//CONDUITL
		    AddVehicleComponent(carid, 1018);//POT
		    AddVehicleComponent(carid, 1006);//TOIT
   		    AddVehicleComponent(carid, 1007);//JUPE
   		    AddVehicleComponent(carid, 1017);//JUPE
		}
		//DUMPER
		case 406:
		{
	        AddVehicleComponent(carid, 1081);//JANTE
		}
		//FIRETRUCK
		case 407:
		{
		    AddVehicleComponent(carid, 1081);//JANTE
		    AddVehicleComponent(carid, 1010);//NOS
		}
		case 578, 579, 580, 582, 583, 584, 585, 587, 588, 589, 596, 597, 
		598, 599, 600, 601, 602, 603, 604, 605, 609, 568, 572, 574, 402, 
		403, 404, 405, 408, 409, 410, 411, 412, 413, 414, 415, 416, 418, 
		419, 421, 422, 423, 424, 426, 427, 428, 429, 431, 432, 433, 434, 
		436, 437, 438, 439, 440, 441, 442, 443, 444, 445, 451, 455, 456, 
		457, 458, 459, 466, 467, 470, 474, 475, 477, 478, 479, 480, 482, 
		483, 485, 486, 489, 492, 494, 495, 496, 498, 499, 500, 502, 503, 
		504, 505, 506, 507, 508, 514, 515, 516, 517, 518, 524, 525, 526, 
		527, 528, 529, 530, 531, 532, 533, 540, 541, 542, 543, 566, 544, 
		545, 546, 547, 549, 550, 551, 552, 554, 555:
		{
			AddVehicleComponent(carid, 1010);//NOS
		    AddVehicleComponent(carid, 1087);//HYDROLIK
		    AddVehicleComponent(carid, 1081);//JANTE
		}
		//TAXI
		case 420:
		{
			AddVehicleComponent(carid, 1010);//NOS//nos
		    AddVehicleComponent(carid, 1087);//HYDROLIK
		    AddVehicleComponent(carid, 1081);//JANTE
		    AddVehicleComponent(carid, 1139);//SPOILER//SPOILER//spoiler
		}
		//REMINGTON
		case 534:
		{
		    ChangeVehiclePaintjob(carid, 2);
		    AddVehicleComponent(carid, 1180);
		    AddVehicleComponent(carid, 1185);
		    AddVehicleComponent(carid, 1100);
		    AddVehicleComponent(carid, 1010);//NOS//nos
		    AddVehicleComponent(carid, 1127);//POT D'ECHAPPEMMENT
		    AddVehicleComponent(carid, 1101);//BAS DE CAISSE
		    AddVehicleComponent(carid, 1122);//BAS DE CAISSE
		    AddVehicleComponent(carid, 1087);//HYDROLIK
		}
		//SLAMVAN
		case 535:
		{
		    ChangeVehiclePaintjob(carid, 2);
			AddVehicleComponent(carid, 1109);
			AddVehicleComponent(carid, 1115);
			AddVehicleComponent(carid, 1117);
			AddVehicleComponent(carid, 1010);//NOS//nos
		    AddVehicleComponent(carid, 1087);//HYDROLIK
		    AddVehicleComponent(carid, 1114);//POT D'ECHAPPEMMENT
		    AddVehicleComponent(carid, 1081);//JANTE
		    AddVehicleComponent(carid, 1119);//BAS DE CAISSE
		    AddVehicleComponent(carid, 1121);//BAS DE CAISSE
		}
		//BLADE
		case 536:
		{
		    AddVehicleComponent(carid, 1010);//NOS//nos
		    AddVehicleComponent(carid, 1183);
		    AddVehicleComponent(carid, 1181);
		    AddVehicleComponent(carid, 1107);//BAS DE CAISSE
		    AddVehicleComponent(carid, 1104);//POT D'ECHAPPEMMENT
		    AddVehicleComponent(carid, 1108);//BAS DE CAISSE
		    AddVehicleComponent(carid, 1087);//HYDROLIK
		    AddVehicleComponent(carid, 1081);//JANTE
		}
		//MONSTERA
		case 556, 557:
		{
			AddVehicleComponent(carid, 1010);//NOS
		}
		//URANUS
		case 558:
		{
		    AddVehicleComponent(carid, 1092);//POT D'ECHAPPEMMENT
		    AddVehicleComponent(carid, 1166);
		    AddVehicleComponent(carid, 1165);
		    AddVehicleComponent(carid, 1090);//BAS DE CAISSE
		    AddVehicleComponent(carid, 1094);//BAS DE CAISSE
		    AddVehicleComponent(carid, 1010);//NOS
		    AddVehicleComponent(carid, 1087);//HYDROLIK
		    AddVehicleComponent(carid, 1163);//SPOILER
		    AddVehicleComponent(carid, 1091);//ROOF
		    ChangeVehiclePaintjob(carid, random(2)+1);
		}
		//JESTER
		case 559:
		{
		    AddVehicleComponent(carid, 1070);//BAS DE CAISSE
		    AddVehicleComponent(carid, 1066);//POT D'ECHAPPEMMENT
		    AddVehicleComponent(carid, 1072);//BAS DE CAISSE
			AddVehicleComponent(carid, 1010);//NOS
		    AddVehicleComponent(carid, 1087);//HYDROLIK
		    AddVehicleComponent(carid, 1147);//SPOILER
		    AddVehicleComponent(carid, 1068);//ROOF
		    AddVehicleComponent(carid, 1173);
		    AddVehicleComponent(carid, 1161);
		    ChangeVehiclePaintjob(carid, random(2)+1);
		}
		//SULTAN
		case 560:
		{
		    AddVehicleComponent(carid, 1028);//POT D'ECHAPPEMMENT
		    AddVehicleComponent(carid, 1140);
		    AddVehicleComponent(carid, 1170);
		    AddVehicleComponent(carid, 1010);//NOS
		    AddVehicleComponent(carid, 1087);//HYDROLIK
		    AddVehicleComponent(carid, 1139);//SPOILER
		    AddVehicleComponent(carid, 1033);//ROOF
		    AddVehicleComponent(carid, 1031);//BAS DE CAISSE
		    AddVehicleComponent(carid, 1030);//BAS DE CAISSE
		    ChangeVehiclePaintjob(carid, random(2)+1);
		}
		//STRATUM
		case 561:
		{
		   	AddVehicleComponent(carid, 1056);//BAS DE CAISSE
		   	AddVehicleComponent(carid, 1156);
		   	AddVehicleComponent(carid, 1157);
		    AddVehicleComponent(carid, 1062);//BAS DE CAISSE
		    AddVehicleComponent(carid, 1059);//POT D'ECHAPPEMMENT
			AddVehicleComponent(carid, 1010);//NOS
		    AddVehicleComponent(carid, 1087);//HYDROLIK
		    AddVehicleComponent(carid, 1146);//SPOILER
		    AddVehicleComponent(carid, 1061);//ROOF
		    ChangeVehiclePaintjob(carid, random(2)+1);
		}
		//ELEGY
		case 562:
		{
		    ChangeVehiclePaintjob(carid, random(2)+1);
		    AddVehicleComponent(carid, 1037);//POT D'ECHAPPEMMENT
		    AddVehicleComponent(carid, 1010);//NOS
		    AddVehicleComponent(carid, 1035);//ROOF
		    AddVehicleComponent(carid, 1039);//BAS DE CAISSE
		    AddVehicleComponent(carid, 1041);//BAS DE CAISSE
		    AddVehicleComponent(carid, 1086);//STEREO
		    AddVehicleComponent(carid, 1087);//HYDROLIK
		    AddVehicleComponent(carid, 1147);//SPOILER
		    AddVehicleComponent(carid, 1148);
		    AddVehicleComponent(carid, 1172);
		}
		//FLASH
		case 565:
		{
		    ChangeVehiclePaintjob(carid, random(2)+1);
		    AddVehicleComponent(carid, 1046);//POT D'ECHAPPEMMENT
		    AddVehicleComponent(carid, 1151);
		    AddVehicleComponent(carid, 1152);
		    AddVehicleComponent(carid, 1010);//NOS
		    AddVehicleComponent(carid, 1087);//HYDROLIK
		    AddVehicleComponent(carid, 1139);//SPOILER
		    AddVehicleComponent(carid, 1081);//JANTE
		    AddVehicleComponent(carid, 1053);//ROOF
		    AddVehicleComponent(carid, 1047);//BAS DE CAISSE
		    AddVehicleComponent(carid, 1051);//BAS DE CAISSE
		}
 		//SAVANNA
		case 567:
		{
		   	AddVehicleComponent(carid, 1188);
		   	AddVehicleComponent(carid, 1186);
		   	AddVehicleComponent(carid, 1102);//BAS DE CAISSE
		   	AddVehicleComponent(carid, 1133);//BAS DE CAISSE
		    AddVehicleComponent(carid, 1018);//POT D'ECHAPPEMMENT
		    AddVehicleComponent(carid, 1010);//NOS
		    AddVehicleComponent(carid, 1087);//HYDROLIK
		    ChangeVehiclePaintjob(carid, random(2)+1);
			AddVehicleComponent(carid, 1081);//JANTE
   		}
   		case 575:
   		{
		    ChangeVehiclePaintjob(carid, random(2)+1);
		    AddVehicleComponent(carid, 1175);
		    AddVehicleComponent(carid, 1177);
		    AddVehicleComponent(carid, 1043);//POT D'ECHAPPEMMENT
		    AddVehicleComponent(carid, 1010);//NOS
		    AddVehicleComponent(carid, 1081);//JANTE
		    AddVehicleComponent(carid, 1042);//BAS DE CAISSE
		    AddVehicleComponent(carid, 1099);//BAS DE CAISSE
		  	AddVehicleComponent(carid, 1087);//HYDROLIK
		}
		//TORNADO
   		case 576:
		{
		    ChangeVehiclePaintjob(carid, random(2)+1);
		    AddVehicleComponent(carid, 1191);
		    AddVehicleComponent(carid, 1193);
		    AddVehicleComponent(carid, 1010);//NOS
		    AddVehicleComponent(carid, 1018);//POT D'ECHAPPEMMENT
		    AddVehicleComponent(carid, 1081);//JANTE
		    AddVehicleComponent(carid, 1087);//HYDROLIK
		    AddVehicleComponent(carid, 1134);//BAS DE CAISSE
		    AddVehicleComponent(carid, 1137);//BAS DE CAISSE
		}

	}
}
stock IsCar(vid)
{
	    new model = GetVehicleModel(vid);
	    switch(model)
	    {
		case 443:return 0;
		case 448:return 0;
		case 461:return 0;
		case 462:return 0;
		case 463:return 0;
		case 468:return 0;
		case 521:return 0;
		case 522:return 0;
		case 523:return 0;
		case 581:return 0;
		case 586:return 0;
		case 481:return 0;
		case 509:return 0;
		case 510:return 0;
		case 430:return 0;
		case 446:return 0;
		case 452:return 0;
		case 453:return 0;
		case 454:return 0;
		case 472:return 0;
		case 473:return 0;
		case 484:return 0;
		case 493:return 0;
		case 595:return 0;
		case 417:return 0;
		case 425:return 0;
		case 447:return 0;
		case 465:return 0;
		case 469:return 0;
		case 487:return 0;
		case 488:return 0;
		case 497:return 0;
		case 501:return 0;
		case 548:return 0;
		case 563:return 0;
		case 406:return 0;
		case 444:return 0;
		case 556:return 0;
		case 557:return 0;
		case 573:return 0;
		case 460:return 0;
		case 464:return 0;
		case 476:return 0;
		case 511:return 0;
		case 512:return 0;
		case 513:return 0;
		case 519:return 0;
		case 520:return 0;
		case 539:return 0;
		case 553:return 0;
		case 577:return 0;
		case 592:return 0;
		case 593:return 0;
		case 471:return 0;
	    }
  		return 1;
}
Public:WyslijPM(playerid, receiverid, text[])
{

	if(pInfo[playerid][player_mute] > 0)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Zostaniesz odciszony(a) za %ds", pInfo[playerid][player_mute]);
		return 0;
	}
	if(pInfo[playerid][player_jail] > 0)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Zostaniesz wypuszczony(a) z wiêzienia za %ds", pInfo[playerid][player_jail]);
		return 0;
	}
	if(pInfo[playerid][player_afk] > 3)
	{ 
		Time_Convert(pInfo[playerid][player_afk], mm, ss);
		SendClientMessage(playerid, COLOR_ERROR, "» Gracz do którego wysy³asz wiadomoœæ jest AFK (%02dmin %02d sek.)", mm, ss);
	}
	
	if(ContainsIPEx(text))
	{
		SendClientMessage(playerid, 0xFFCC10FF, "(PM) >> %s (%d): reklama!", playerNick(receiverid), receiverid); 
		
		foreach(new i : Admins)
		{
			SendClientMessage(i, COLOR_ERROR, " »(Admin info) Prawdopodobna próba reklamy %s na PM(%d).", playerNick(playerid), playerid);
			SendClientMessage(i, COLOR_ERROR, " » Treœæ wiadomoœci: %s", text);
		}
		return 0;
	}
	foreach(new adminid : ViewPM)
	{
		if(adminid == playerid || adminid == receiverid) continue;
		
		if(pInfo[playerid][player_admin] > pInfo[adminid][player_admin]) continue;
		if(pInfo[receiverid][player_admin] > pInfo[adminid][player_admin]) continue;

		SendClientMessage(adminid, COLOR_INFO2, "(Podgl¹d PM) %s (%d) -> %s (%d): %s", playerNick(playerid), playerid, playerNick(receiverid), receiverid, text); //wygenerowany
	}
 
	SendClientMessage(playerid, 0xFFCC10FF, "(PM) >> %s (%d): %s", playerNick(receiverid), receiverid, text); 
	SendClientMessage(receiverid, 0xFFCC10FF, "(PM) << %s (%d): %s", playerNick(playerid), playerid, text);
	
	
	InfoTDBox(receiverid, "Dostales PM");
	PlayerPlaySound(receiverid, 1057, 0.0, 0.0, 0.0);
	#if defined ADUIO_PLUGIN
	Audio_PlayEx(receiverid,MSG_PW);
	#endif
	return 1;
}

stock GetXYInFrontOfPlayer(playerid, &Float:x, &Float:y, Float:distance)
{
	new
			Float:angle;
	GetPlayerPos(playerid, x, y, angle);
	GetPlayerFacingAngle(playerid, angle);
	x += (distance * floatsin(-angle, degrees));
	y += (distance * floatcos(-angle, degrees));
}


 
stock RunComment(playerid, command[])
{
	
	new f;
	f = strfind(command, "/", true);
	if(command[0] != '/' && f != -1)
	{
		strdel(command, 0, f);
	}
	if(command[0])
		CallRemoteFunction("OnPlayerCommandText", "ds", playerid, command);
}

new MonthTimes[12][3] = 
{
	{ 31, 31, 2678400 }, 
	{ 28, 29, 2505600 }, 
	{ 31, 31, 2678400 }, 
	{ 30, 30, 2592000 }, 
	{ 31, 31, 2678400 }, 
	{ 30, 30, 2592000 }, 
	{ 31, 31, 2678400 }, 
	{ 31, 31, 2678400 }, 
	{ 30, 30, 2592000 }, 
	{ 31, 31, 2678400 }, 
	{ 30, 30, 2592000 }, 
	{ 31, 31, 2678400 }
};


stock UnixTime(type, time) 
{
 	switch(tolower(type)) 
	{
		case 'd': 	   time = time * 86400;
		case 'h': 	   time = time * 3600;
		case 'm': 	   time = time * 60;	
	}
	return time;
}
stock IsLeapYear(year)
{
	if(year %4 == 0) return 1;
	else return 0;
}
stock DateFormat(timestamp)
{
   new nYear, nMonth, nDay, nHour, nMinute, nSecond, formattedData[128];
   TimestampToDate(timestamp, nYear, nMonth, nDay, nHour, nMinute, nSecond, 1);
   
   
   format(formattedData, 128, "%02d.%02d.%d %02d:%02d:%02d", nDay, nMonth, nYear, nHour, nMinute, nSecond);
   return formattedData;
}
stock TimestampToDate(Timestamp, &year, &month, &day, &iHour, &iMinute, &second, iHourGMT, iMinuteGMT = 0)
{
	new tmp = 2;
	year = 1970;
	month = 1;
	for(;;)
	{
		if(Timestamp >= 31536000)
		{
			year ++;
			Timestamp -= 31536000;
			tmp ++;
			if(tmp == 4)
			{
				if(Timestamp >= 31622400)
				{
					tmp = 0;
					year ++;
					Timestamp -= 31622400;
				}
				else break;
			}
		}
		else break;
	}		
	for(new i = 0; i < 12; i ++)
	{
		if(Timestamp >= MonthTimes[i][2])
		{
			month ++;
			Timestamp -= MonthTimes[i][2];
		}
		else break;
	}
	day = 1 + (Timestamp / 86400);
	Timestamp %= 86400;
	iHour = iHourGMT + (Timestamp / 3600);
	Timestamp %= 3600;
	iMinute = iMinuteGMT + (Timestamp / 60);
	second = (Timestamp %60);
	if(iMinute > 59)
	{
		iMinute = 0;
		iHour ++;
		if(iHour > 23)
		{
			iHour -= 24;
			day ++;
			if(day > MonthTimes[month][IsLeapYear(year)])
			{
				day = 1;
				month ++;
				if(month > 12)
				{
					month = 1;
					year ++;
				}
			}
		}
	}
	return 1;
}

 
stock InsertGlitchInfo(playerid){

	m_query("INSERT INTO `mreg_glitchs` (`id`, `uid`, `gltime`, `ts`, `pl`) VALUES (NULL, '%d', '%d', CURRENT_TIMESTAMP, '%.1f');", pInfo[playerid][player_id], pInfo[playerid][player_glitchCount][3], NetStats_PacketLossPercent(playerid));

}
stock GetWeaponNameEx(weaponid)
{
	return gweaponName[weaponid];
}


AllowAnim(playerid, cmd[])
{
   #define strcmp2(%0,%1,%2) strcmp(%0,%1,%2,strlen(%1))

	if(pInfo[playerid][player_ishouse] == true)
	{
		if(!strcmp2(cmd, "/anim", true)) return 1;
		if(!strcmp2(cmd, "/rece", true)) return 1;
		if(!strcmp2(cmd, "/pijany", true)) return 1;
		if(!strcmp2(cmd, "/pijak1", true)) return 1;
		if(!strcmp2(cmd, "/pijak2", true)) return 1;
		if(!strcmp2(cmd, "/bomba", true)) return 1;
		if(!strcmp2(cmd, "/aresztuj", true)) return 1;
		if(!strcmp2(cmd, "/smiech", true)) return 1;
		if(!strcmp2(cmd, "/ramiona", true)) return 1;
		if(!strcmp2(cmd, "/lez", true)) return 1;
		if(!strcmp2(cmd, "/wal", true)) return 1;
		if(!strcmp2(cmd, "/wytrysk", true)) return 1;
		if(!strcmp2(cmd, "/schowaj", true)) return 1;
		if(!strcmp2(cmd, "/wymiotuj", true)) return 1;
		if(!strcmp2(cmd, "/pa", true)) return 1;
		if(!strcmp2(cmd, "/daj", true)) return 1;
		if(!strcmp2(cmd, "/pal", true)) return 1;
		if(!strcmp2(cmd, "/pal2", true)) return 1;
		if(!strcmp2(cmd, "/usiadz", true)) return 1;
		if(!strcmp2(cmd, "/smierc", true)) return 1;
		if(!strcmp2(cmd, "/spij", true)) return 1;
		if(!strcmp2(cmd, "/caluj", true)) return 1;
		if(!strcmp2(cmd, "/ranny", true)) return 1;
		if(!strcmp2(cmd, "/taxi", true)) return 1;
		if(!strcmp2(cmd, "/rozgladaj", true)) return 1;
		if(!strcmp2(cmd, "/yes", true)) return 1;
		if(!strcmp2(cmd, "/no", true)) return 1;
		if(!strcmp2(cmd, "/myjrece", true)) return 1;
		if(!strcmp2(cmd, "/medyk", true)) return 1;
		if(!strcmp2(cmd, "/oh", true)) return 1;
		if(!strcmp2(cmd, "/dowody", true)) return 1;
		if(!strcmp2(cmd, "/wniebo", true)) return 1;
		if(!strcmp2(cmd, "/spadam", true)) return 1;
		if(!strcmp2(cmd, "/spadam2", true)) return 1;
		if(!strcmp2(cmd, "/spadam3", true)) return 1;
		if(!strcmp2(cmd, "/start", true)) return 1;
		if(!strcmp2(cmd, "/naprawia", true)) return 1;
		if(!strcmp2(cmd, "/naprawil", true)) return 1;
		if(!strcmp2(cmd, "/chatauto", true)) return 1;
		if(!strcmp2(cmd, "/chatauto2", true)) return 1;
		if(!strcmp2(cmd, "/bagaznik", true)) return 1;
		if(!strcmp2(cmd, "/krzeslouderz", true)) return 1;
		if(!strcmp2(cmd, "/krzeslowypij", true)) return 1;
		if(!strcmp2(cmd, "/krzeslokomp", true)) return 1;
		if(!strcmp2(cmd, "/krzeslozegarek", true)) return 1;
		if(!strcmp2(cmd, "/krzeslorozm1", true)) return 1;
		if(!strcmp2(cmd, "/krzeslorozm2", true)) return 1;
		if(!strcmp2(cmd, "/wypij", true)) return 1;
		if(!strcmp2(cmd, "/barman", true)) return 1;
		if(!strcmp2(cmd, "/barman2", true)) return 1;
		if(!strcmp2(cmd, "/wyjmijbutelke", true)) return 1;
		if(!strcmp2(cmd, "/nalej", true)) return 1;
		if(!strcmp2(cmd, "/jem", true)) return 1;
		if(!strcmp2(cmd, "/jem2", true)) return 1;
		if(!strcmp2(cmd, "/jem3", true)) return 1;
		if(!strcmp2(cmd, "/jem4", true)) return 1;
		if(!strcmp2(cmd, "/polchodz", true)) return 1;
		if(!strcmp2(cmd, "/polodejdz", true)) return 1;
		if(!strcmp2(cmd, "/polstop", true)) return 1;
		if(!strcmp2(cmd, "/skok2", true)) return 1;
		if(!strcmp2(cmd, "/trup2", true)) return 1;
		if(!strcmp2(cmd, "/ratunku", true)) return 1;
		if(!strcmp2(cmd, "/krzeslo", true)) return 1;
		if(!strcmp2(cmd, "/trup", true)) return 1;
		if(!strcmp2(cmd, "/calus", true)) return 1;
		if(!strcmp2(cmd, "/sikaj", true)) return 1;
		if(!strcmp2(cmd, "/st", true)) return 1;
		if(!strcmp2(cmd, "/wt2", true)) return 1;
		if(!strcmp2(cmd, "/drunk", true)) return 1;
		if(!strcmp2(cmd, "/rap1", true)) return 1;
		if(!strcmp2(cmd, "/lookout", true)) return 1;
		if(!strcmp2(cmd, "/napad", true)) return 1;
		if(!strcmp2(cmd, "/hide", true)) return 1;
		if(!strcmp2(cmd, "/rzygaj", true)) return 1;
		if(!strcmp2(cmd, "/jedz", true)) return 1;
		if(!strcmp2(cmd, "/machaj", true)) return 1;
		if(!strcmp2(cmd, "/klepnij", true)) return 1;
		if(!strcmp2(cmd, "/deal", true)) return 1;
		if(!strcmp2(cmd, "/cpun", true)) return 1;
		if(!strcmp2(cmd, "/rece", true)) return 1;
		if(!strcmp2(cmd, "/rece", true)) return 1;
		if(!strcmp2(cmd, "/rece2", true)) return 1;
		if(!strcmp2(cmd, "/rece3", true)) return 1;
		if(!strcmp2(cmd, "/siadaj", true)) return 1;
		if(!strcmp2(cmd, "/fucku", true)) return 1;
		if(!strcmp2(cmd, "/taichi", true)) return 1;
		if(!strcmp2(cmd, "/pij", true)) return 1;
		if(!strcmp2(cmd, "/inbedleft", true)) return 1;
		if(!strcmp2(cmd, "/inbedright", true)) return 1;
		if(!strcmp2(cmd, "/fotel", true)) return 1;
		if(!strcmp2(cmd, "/rap", true)) return 1;
		if(!strcmp2(cmd, "/rap2", true)) return 1;
		if(!strcmp2(cmd, "/rap3", true)) return 1;
		if(!strcmp2(cmd, "/rap4", true)) return 1;
		if(!strcmp2(cmd, "/rap5", true)) return 1;
		if(!strcmp2(cmd, "/rap6", true)) return 1;
		if(!strcmp2(cmd, "/patrz", true)) return 1;
		if(!strcmp2(cmd, "/opieraj", true)) return 1;
		if(!strcmp2(cmd, "/yo", true)) return 1;
		if(!strcmp2(cmd, "/yo2", true)) return 1;
		if(!strcmp2(cmd, "/yo3", true)) return 1;
		if(!strcmp2(cmd, "/yo4", true)) return 1;
		if(!strcmp2(cmd, "/zolwik", true)) return 1;
		if(!strcmp2(cmd, "/carchat", true)) return 1;
		if(!strcmp2(cmd, "/krzycz", true)) return 1;
		if(!strcmp2(cmd, "/wtf", true)) return 1;
		if(!strcmp2(cmd, "/adhd", true)) return 1;
		if(!strcmp2(cmd, "/raczkuj", true)) return 1;
		if(!strcmp2(cmd, "/down", true)) return 1;
		if(!strcmp2(cmd, "/scratch", true)) return 1;
		if(!strcmp2(cmd, "/beach", true)) return 1;
		if(!strcmp2(cmd, "/circle", true)) return 1;
		if(!strcmp2(cmd, "/rofl", true)) return 1;
		if(!strcmp2(cmd, "/getin", true)) return 1;
		if(!strcmp2(cmd, "/spray ", true)) return 1;
		if(!strcmp2(cmd, "/headbutt", true)) return 1;
		if(!strcmp2(cmd, "/lightcig", true)) return 1;
		if(!strcmp2(cmd, "/tapcig", true)) return 1;
		if(!strcmp2(cmd, "/bat", true)) return 1;
		if(!strcmp2(cmd, "/chant", true)) return 1;
		if(!strcmp2(cmd, "/finger", true)) return 1;
		if(!strcmp2(cmd, "/shouting", true)) return 1;
		if(!strcmp2(cmd, "/cop", true)) return 1;
		if(!strcmp2(cmd, "/lowbodypush", true)) return 1;
		if(!strcmp2(cmd, "/push", true)) return 1;
		if(!strcmp2(cmd, "/medic", true)) return 1;
		if(!strcmp2(cmd, "/rollfall", true)) return 1;
		if(!strcmp2(cmd, "/boxanim", true)) return 1;
		if(!strcmp2(cmd, "/fall", true)) return 1;
		if(!strcmp2(cmd, "/fallback", true)) return 1;
		if(!strcmp2(cmd, "/robman", true)) return 1;
		if(!strcmp2(cmd, "/smoke", true)) return 1;
		if(!strcmp2(cmd, "/aim", true)) return 1;
		if(!strcmp2(cmd, "/run", true)) return 1;
		if(!strcmp2(cmd, "/lay", true)) return 1;
		if(!strcmp2(cmd, "/wave", true)) return 1;
		if(!strcmp2(cmd, "/walk", true)) return 1;
		if(!strcmp2(cmd, "/look", true)) return 1;
		if(!strcmp2(cmd, "/shout", true)) return 1;
		if(!strcmp2(cmd, "/bj", true)) return 1;
		if(!strcmp2(cmd, "/swat2", true)) return 1;
		if(!strcmp2(cmd, "/lean", true)) return 1;
		if(!strcmp2(cmd, "/stance", true)) return 1;
		if(!strcmp2(cmd, "/hike", true)) return 1;
		if(!strcmp2(cmd, "/face", true)) return 1;
		if(!strcmp2(cmd, "/tancz", true)) return 1;
		if(!strcmp2(cmd, "/chat", true)) return 1;
	}

	return 0;
}

stock Allow_Comment(playerid, cmd[])
{
	if(!strcmp(cmd, "/ban", true, 4)) return 1;
	if(!strcmp(cmd, "/rsp", true, 4)) return 1;
	if(!strcmp(cmd, "/toadmin", true, 8)) return 1;
	if(!strcmp(cmd, "/kill", true, 5)) return 1;
	if(!strcmp(cmd, "/astop", true, 6)) return 1;
	if(!strcmp(cmd, "/wypisz", true, 7)) return 1;
	if(!strcmp(cmd, "/glitchexit", true, 11)) return 1;
	if(!strcmp(cmd, "/skupcancel", true, 11)) return 1;
	if(!strcmp(cmd, "/kick", true, 5)) return 1;
	if(!strcmp(cmd, "/mute", true, 5)) return 1;
	if(!strcmp(cmd, "/dompanel", true, 9)) return 1;
	if(!strcmp(cmd, "/wyjdz", true, 6)) return 1;
	if(!strcmp(cmd, "/jail", true, 5)) return 1;
	if(!strcmp(cmd, "/unfreeze", true, 9)) return 1;
	if(!strcmp(cmd, "/freeze", true, 7)) return 1;
	if(!strcmp(cmd, "/giveweapon", true, 11)) return 1;
	if(!strcmp(cmd, "/sethp", true, 6)) return 1;
	if(!strcmp(cmd, "/setarmor", true, 9)) return 1;
	if(!strcmp(cmd, "/raport", true, 7)) return 1;
	if(!strcmp(cmd, "/ramp", true, 5)) return 1;
	if(!strcmp(cmd, "/pm", true, 3)) return 1;
	if(!strcmp(cmd, "/spec", true, 3)) return 1;
	if(!strcmp(cmd, "/explode", true, 7)) return 1;
	if(!strcmp(cmd, "/l ", true, 3)) return 1;
	if(!strcmp(cmd, "/resrace", true, 8)) return 1; 
	if(!strcmp(cmd, "/lock", true, 5)) return 1;
	if(!strcmp(cmd, "/unlock", true, 7)) return 1;
	if(!strcmp(cmd, "/dzien", true, 6)) return 1;
	if(!strcmp(cmd, "/noc", true, 4)) return 1;
	if(!strcmp(cmd, "/addevp", true, 7)) return 1;
	if(!strcmp(cmd, "/aexit", true, 6)) return 1;  
	//if(!strcmp(cmd, "/flip", true, 5)) return 1;  
	if(!strcmp(cmd, "/dexit", true, 6)) return 1;
	if(!strcmp(cmd, "/explode", true, 8)) return 1;
 	if(!strcmp(cmd, "/pw", true, 3)) return 1;
	if(!strcmp(cmd, "/setpm", true, 6)) return 1;
	if(!strcmp(cmd, "/settp", true, 6)) return 1;
	if(!strcmp(cmd, "/spec", true, 3)) return 1;
	if(!strcmp(cmd, "/eye", true, 4)) return 1;
	if(!strcmp(cmd, "/spadochron", true, 11)) return 1;
	if(!strcmp(cmd, "/tirexit", true, 8)) return 1;
	if(!strcmp(cmd, "/cb", true, 3)) return 1;
	if(!strcmp(cmd, "/me", true, 3)) return 1;
	if(!strcmp(cmd, "/jj", true, 3)) return 1;
	if(!strcmp(cmd, "/zw", true, 3)) return 1;//
	if(!strcmp(cmd, "/labiryntexit", true, 13)) return 1;//
	if(!strcmp(cmd, "/lbexit", true, 7)) return 1;//
	if(!strcmp(cmd, "/skupcancel", true, 11)) return 1;
	if(!strcmp(cmd, "/holuj", true, 6)) return 1;
	if(!strcmp(cmd, "/report", true, 7)) return 1;
	if(!strcmp(cmd, "/evcar", true, 6)) return 1;
	
	  
	if(Iter_Contains(d_f_players, playerid) && pInfo[playerid][player_arena] == 0)
	{
		if(!strcmp(cmd, "/dfrustler", true, 10)) return 1;
		if(!strcmp(cmd, "/dfsparrow", true, 10)) return 1;
	}
	return 0;
}
 

stock GetPlayerHighestScores(array[][gangspar_rankingEnum], left, right)
{
    new
        tempLeft = left,
        tempRight = right,
        pivot = array[(left + right) / 2][player_Score],
        tempVar
    ;
    while(tempLeft <= tempRight)
    {
        while(array[tempLeft][player_Score] > pivot) tempLeft++;
        while(array[tempRight][player_Score] < pivot) tempRight--;

        if(tempLeft <= tempRight)
        {
            tempVar = array[tempLeft][player_Score], array[tempLeft][player_Score] = array[tempRight][player_Score], array[tempRight][player_Score] = tempVar;
            tempVar = array[tempLeft][player_ID], array[tempLeft][player_ID] = array[tempRight][player_ID], array[tempRight][player_ID] = tempVar;
            tempLeft++, tempRight--;
        }
    }
    if(left < tempRight) GetPlayerHighestScores(array, left, tempRight);
    if(tempLeft < right) GetPlayerHighestScores(array, tempLeft, right);
}
stock OnPlayerDisconnectFunctions(playerid)
{
	if(pInfo[playerid][player_admin] >=1 && pInfo[playerid][player_id]>=1)
    {
		m_query("update "prefix"_adminactive set time=time+%d where uid=%d and data= CURDATE() limit 1;",pInfo[playerid][player_connected],pInfo[playerid][player_id]);
    }
	if(pInfo[playerid][player_tir3dt])
	{
		Delete3DTextLabel(pInfo[playerid][player_tir3dt]);
		pInfo[playerid][player_tir3dt] = Text3D:0;
	}
	
	if(pInfo[playerid][player_selectobject]>0)
	{
		DestroyObject(pInfo[playerid][player_selectobject]);
		pInfo[playerid][player_selectobject] = 0;
	}
	if(pInfo[playerid][player_duel]) DuelWin(pInfo[playerid][player_duel_toplayer]);
	
	if(GetServerVarAsInt("port") == 7777) 
	{
		if(pInfo[playerid][player_sqlonline] > 0)
		{
			m_query("delete from mreg_online where id=%d", pInfo[playerid][player_sqlonline]);
		}
	}
	Gang_OnPlayerDisconnect(playerid);
 	UpdatePlayerOnline(playerid, 1);
 	SavePlayer(playerid);
	UnCagePlayer(playerid);
	DestroyPrivcar(playerid);
	
	OnPlayerDisconnectReports(playerid);
	
	pInfo[playerid][player_spec] = -1;
	pInfo[playerid][player_arena] = 0;
	
	if(pInfo[playerid][player_arena]>0) {
		gmData[server_arenaplayers][pInfo[playerid][player_arena]]--;
		UpdateArenaPlayers();
	}
	pInfo[playerid][player_arena] = 0;
	for(new c; c<MAX_GANG2;c++)
	{
		gangPodania[playerid][c] = -1;
	}
		
	for(new xc;xc<MAX_PLAYER_VEHICLE_OBJECT;xc++)
	{
		if(player_vehicle_object[playerid][xc] > 0)
		{
			DestroyDynamicObject(player_vehicle_object[playerid][xc]);
		}
	}
	Iter_Remove(Drivers, playerid);
	Iter_Remove(ViewPM, playerid);
	Iter_Remove(VievEye, playerid);
	Iter_Remove(Admins, playerid);
	Iter_Remove(Mods, playerid);
	Iter_Remove(Vips, playerid);
		
	if(GetVehicleModel(pInfo[playerid][player_vehicle]))
	{
		DestroyVehicleEx(pInfo[playerid][player_vehicle]);
	}
	return 1;
}
stock IsVehicleInUse(vehicleid)
{
	foreach(new I : Player)
	{
	
		if(GetPlayerState(I) == PLAYER_STATE_DRIVER)
		{
			if(GetPlayerVehicleID(I) == vehicleid)	
			{
				return 1;
			}
		}
	}
	return 0;
}
stock IsTrailer(vehicleid)
{
	new model = GetVehicleModel(vehicleid);
	switch(model)
	{
		case 435:return 1;
		case 450:return 1;
		case 591:return 1;
		case 606:return 1;
		case 610:return 1;
		case 584:return 1;
		case 608:return 1;
		case 611:return 1;
		case 607:return 1;
	}
	return 0;
}
native IsValidVehicle(vehicleid);

stock RespawnTrailers()
{
	new bool:VehUsed[MAX_VEHICLES],vehID;

	for(new playerid,g = GetMaxPlayers(); playerid != g; playerid++)
		if(IsPlayerConnected(playerid))
		{
			vehID = GetPlayerVehicleID(playerid);
			if(vehID > 0)
			{
				VehUsed[vehID] = true;
				new vehMod = GetVehicleModel(vehID);
				if(vehMod == 403 || vehMod == 514 || vehMod == 515 || vehMod == 525 || vehMod == 531 || vehMod == 572 || vehMod == 583) // Linerunner,Tanker,Roadtrain,Towtruck,Tractor,Mower,Tug
				{
					vehID = GetVehicleTrailer(vehID);
					if(vehID > 0)
						VehUsed[vehID] = true;
				}
			}
		}

	for(new vehicleid = 1; vehicleid != MAX_VEHICLES; vehicleid++)
		if(!VehUsed[vehicleid] && IsValidVehicle(vehicleid))
		{
			if(IsTrailer(vehicleid))
			{
					SetVehicleToRespawn(vehicleid);
			}
		}

	return;
}

stock UnixTimetoDate(time, out[], size = sizeof(out))
{
	new secs = time - gettime(), data[12];
	if(secs < 0)
	{
		format(out, size, "---");
		return 0;
	}
	
	new year = secs / 31556926;
	secs -= year*31556926;
	
	new msc = secs / (86400*31);
	secs -= msc*(86400*31);
	
	new day = secs / 86400;
	secs -= day*86400;
	
	new hour = secs / 3600;
	secs -= hour*3600;
	
	new minutes = secs / 60;
	secs -= minutes*60;
 
	
	#if defined dli
	#undef dli
	#endif
	#define dli(%1,%2,%3,%4) ((%1==1)?(%2):(((%1% 10>1)&&(%1% 10<5)&&!((%1% 100>=10)&&(%1% 100<=21)))?(%3):(%4)))
	
	if(year > 0)
		format(data, sizeof(data), "%d %s", year, dli(year, "roku", "Lat", "Lat"));
	if(data[0]) 
		format(out, size, "%s %s",out, data);
	data[0] = EOS;
	
	if(msc > 0) 
		format(data, sizeof(data), "%d %s",msc, dli(msc,"miesi¹c","miesi¹ce","miesi¹cy"));
	if(data[0]) 
		format(out, size, "%s %s",out, data);
	data[0] = EOS;
	
	if(day > 0) 
		format(data, sizeof(data), "%d %s",day, dli(day,"dzieñ","dni","dni"));
	if(data[0]) 
		format(out, size, "%s %s",out, data);
	data[0] = EOS;
	
	if(hour > 0) 
		format(data, sizeof(data), "%d %s",hour, dli(hour,"godzina", "godziny","godzin"));
	if(data[0]) 
		format(out, size, "%s %s",out, data);
	data[0] = EOS;
	
	if(minutes > 0) 
		format(data, sizeof(data), "%d %s",minutes, dli(minutes,"minuta","minuty","minut"));
	if(data[0]) 
		format(out, size, "%s %s",out, data);
	data[0] = EOS;
	
	if((secs % 60) > 0) 
		format(data, sizeof(data), "%d %s",secs, dli(secs,"sekunda","sekundy","sekund"));
	if(data[0])
		format(out, size, "%s %s",out, data);
	data[0] = EOS;
	
	#undef dli
	return 1;
}
/*
stock StartSpec(playerid, specid, bool:downup = false, dtype = 0, bool:update = false)
{
	if(playerid == specid) return StopSpec(playerid); //wtf?
	
	if (pInfo[specid][player_afk] > 3)
		SendClientMessage(playerid, COLOR_INFO2, ""chat" Gracz którego specujesz jest AFK %d sekund.", pInfo[specid][player_afk]);
	
	if(downup)
	{
		if(dtype == 1)
		{
			if(pInfo[playerid][player_spec] >= MAX_PLAYERS) return 1;
	
			for(new i = pInfo[playerid][player_spec]; i < MAX_PLAYERS; i++)
			{
				if(i == pInfo[playerid][player_spec]) continue;
				
				if(IsPlayerConnected(i)&& i != playerid && GetPlayerState(i) > 0 && GetPlayerState(i) < 7)
				{
					specid = i;
					break;
				}
			}
		}
		else 
		{
			if(pInfo[playerid][player_spec] < 1) return 1;
	
			for(new i = pInfo[playerid][player_spec]; --i;)
			{
				if(IsPlayerConnected(i)&& i != playerid && GetPlayerState(i) > 0 && GetPlayerState(i) < 7)
				{
					specid = i;
					break;
				}
			}
		}
	}
 
	
	if(!update) GetPlayerWeaponList(playerid, specid);
	
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(specid));
	SetPlayerInterior(playerid, GetPlayerInterior(specid));
	
	pInfo[playerid][player_spec] = specid;
	
	format(string2, sizeof(string2), "Specujesz %s (%d).%s", playerNick(specid), specid, GetPVarInt(playerid, "NRG_TURBO") == 1?("~n~Turbo w NRG i Infernusach ~g~ON~w~."):(""));
	
	PlayerEventTDSet(playerid, string2);
	if(IsPlayerInAnyVehicle(specid))
	{
		TogglePlayerSpectating(playerid, 1);
		PlayerSpectateVehicle(playerid, GetPlayerVehicleID(specid));
	}
	else
	{
		TogglePlayerSpectating(playerid, 1);
		PlayerSpectatePlayer(playerid, specid);
	}
	return 1;
} 
stock StopSpec(playerid)
{	 

	if(GetPlayerState(i) != PLAYER_STATE_SPECTATING) return 1;
	
	PlayerEventTD(playerid, false);
	TogglePlayerSpectating(playerid, 0);
	
	
	pInfo[playerid][player_spec] = -1;
	return 1;
}

forward fix_UpdateSpec(playerid, adminid);
public fix_UpdateSpec(playerid, adminid){
	StartSpec(adminid,playerid,false,0,true);
	return 1;
}
stock UpdateSpec(playerid)
{
	foreach(new i : Admins)
	{
		if(pInfo[i][player_spec] == playerid && playerid != i && pInfo[i][player_admin] != 0 && GetPlayerState(i) == PLAYER_STATE_SPECTATING)
		{
			SetTimerEx("fix_UpdateSpec", 1000, 0, "dd", playerid, i);
		}
	}
	return 1;
}
*/


stock StartSpec(playerid, specid, bool:downup = false, dtype = 0, bool:update = false)
{
	if(playerid == specid) return StopSpec(playerid); //wtf?
	
	if (pInfo[specid][player_afk] > 3)
		SendClientMessage(playerid, COLOR_INFO2, ""chat" Gracz którego specujesz jest AFK %d sekund.", pInfo[specid][player_afk]);
	
	if(downup)
	{
		if(dtype == 1)
		{
			if(pInfo[playerid][player_spec] >= MAX_PLAYERS) 
				pInfo[playerid][player_spec] = 0;
	
			for(new i = pInfo[playerid][player_spec]; i < MAX_PLAYERS; i++)
			{
				if(i == pInfo[playerid][player_spec]) continue;
				
				if(IsPlayerConnected(i)&& i != playerid && GetPlayerState(i) > 0 && GetPlayerState(i) < 7)
				{
					specid = i;
					break;
				}
			}
		}
		else 
		{
			if(pInfo[playerid][player_spec] < 1) 
				pInfo[playerid][player_spec] = GetPlayerPoolSize();
	
			for(new i = pInfo[playerid][player_spec]; --i;)
			{
				if(IsPlayerConnected(i)&& i != playerid && GetPlayerState(i) > 0 && GetPlayerState(i) < 7)
				{
					specid = i;
					break;
				}
			}
		}
	}
 
	
	//if(!update) GetPlayerWeaponList(playerid, specid); //robilo tylko spam a i tak maja komenda /aweapons ;')
	
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(specid));
	SetPlayerInterior(playerid, GetPlayerInterior(specid));
	
	if(!update)
		pInfo[playerid][player_spec] = specid;
	else //XD
		pInfo[playerid][player_spec] = specid;
		
	format(string2, sizeof(string2), "Specujesz %s (%d).%s", playerNick(specid), specid, GetPVarInt(playerid, "NRG_TURBO") == 1?("~n~Turbo w NRG i Infernusach ~g~ON~w~."):(""));
	
	PlayerEventTDSet(playerid, string2);
	if(IsPlayerInAnyVehicle(specid))
	{
		TogglePlayerSpectating(playerid, 1);
		PlayerSpectateVehicle(playerid, GetPlayerVehicleID(specid));
	}
	else
	{
		TogglePlayerSpectating(playerid, 1);
		PlayerSpectatePlayer(playerid, specid);
	}
	return 1;
} 
stock StopSpec(playerid)
{	 

	if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING) return 1;
	
	PlayerEventTD(playerid, false);
	TogglePlayerSpectating(playerid, 0);
	
	
	pInfo[playerid][player_spec] = -1;
	return 1;
}

forward fix_UpdateSpec(playerid, adminid);
public fix_UpdateSpec(playerid, adminid){
	StartSpec(adminid,playerid,false,0,true);
	return 1;
}
stock UpdateSpec(playerid)
{
	foreach(new i : Admins)
	{
		if(pInfo[i][player_spec] == playerid && playerid != i && pInfo[i][player_admin] != 0 && GetPlayerState(i) == PLAYER_STATE_SPECTATING)
		{
			SetTimerEx("fix_UpdateSpec", 200, 0, "dd", playerid, i);
		}
	}
	return 1;
}

stock Float:GetDistanceBetweenPoint(playerid, player)
{

	#define GetDistanceBetweenPoints(%0,%1,%2,%3,%4,%5) (((%0 - %3) * (%0 - %3)) + ((%1 - %4) * (%1 - %4)) + ((%2 - %5) * (%2 - %5)))
	
	new Float: distance, Float: playeridX, Float: playeridY, Float: playeridZ, Float: playerX, Float: playerY, Float: playerZ;
	GetPlayerPos(player, playerX, playerY, playerZ);
	GetPlayerPos(playerid, playeridX, playeridY, playeridZ);
	distance = GetDistanceBetweenPoints(playeridX, playeridY, playeridZ, playerX, playerY, playerZ);
	
	#undef GetDistanceBetweenPoints
	
	return distance;
}

stock SendPlayerMail(playerid, type=0)
{
	new bool:block = true;
	
	if(!block) return;
	if(pInfo[playerid][player_mailstatus] == 0 && type != 0) return;
	switch(type)
	{
		case 0: format(string2, sizeof(string2), "4fun-serv.pl/email/email.php?ghash=fgfd45d34fdsfg4345&pemail=%s&pid=%d&pnick=%s&phash=%s&type=register", pInfo[playerid][player_email], pInfo[playerid][player_id], pInfo[playerid][player_name], pInfo[playerid][player_ucode]);
		case 1: format(string2, sizeof(string2), "4fun-serv.pl/email/email.php?ghash=fgfd45d34fdsfg4345&pemail=%s&pid=%d&pnick=%s&ip=%s&passwords=%s&type=loginattempts", pInfo[playerid][player_email], pInfo[playerid][player_id], pInfo[playerid][player_name], pInfo[playerid][player_ip], pInfo[playerid][player_loginpass]);
	}
	HTTP(playerid, HTTP_POST, string2, "", "OnRegisterHTTP");
	printf(string2);
	
} 
Public:OnRegisterHTTP(index, response_code, data[])
{
	printf("OnRegisterHTTP from mail (id %d) response_code = %d;", index, response_code);
}
stock rot13(string4[])
{
	new string[128];
	strins(string, string4, 0);
	for (new index = 0; index < strlen(string); index++)
	{
		if ('a' <= string[index] <= 'z')
		{
			string[index] = (string[index] - 'a' + 13) %26 + 'a';
		}
		else if ('A' <= string[index] <= 'Z')
		{
			string[index] = (string[index] - 'A' + 13) %26 + 'A';
		}
	}
	return string;
}
stock method mysql::init()
{
 	mysql_init(LOG_ALL, 1);
	if(mysql_connect(gmData[mysql_host], gmData[mysql_user], gmData[mysql_pass], gmData[mysql_db], MySQL:0, 1))
	{
		printf("["version"] pomyslnie polaczono z baza danych");
	} 
	else 
	{
//		printf("["version"] nie polaczono z baza danych dane(%s, %s, %s, %s)", gmData[mysql_host], gmData[mysql_user], gmData[mysql_pass], gmData[mysql_db]);
		SendRconCommand("hostname P4S - blad bazy danych");
		SendRconCommand("password witam");
	}
}

stock SendModsMessage(color, msg [])
{
	foreach(new i : Mods)
	{
		SendClientMessage(i, color, msg);
	}
}
stock SendVipsMessage(color, msg [])
{
	foreach(new i : Vips)
	{
		SendClientMessage(i, color, msg);
	}
}
stock SetTextdrawGranient(name[], pos, color[])
{
	new len = strlen(name), tmp[128];
	
	format(tmp, 128, "%s", name);
	
	if(pos > len + 5) return tmp;
	 
	if(pos + 1 < len) strins(tmp, "~w~", pos + 1);
	if(pos < len) 
	{		
		strins(tmp, color, pos);
			
	}
	if(pos-1 >= 0 && pos-1 < len)   strins(tmp, GetLighterColor(color, 1), pos-1);
	if(pos-2 >= 0 && pos-2 < len) 	strins(tmp, GetLighterColor(color, 2), pos-2);
	if(pos-3 >= 0 && pos-3 < len) 	strins(tmp, GetLighterColor(color, 3), pos-3);
	if(pos-4 >= 0 && pos-4 < len) 	strins(tmp, GetLighterColor(color, 4), pos-4);	
	if(pos-5 >= 0 && pos-5 < len) 	strins(tmp, GetLighterColor(color, 5), pos-5);	
 
 
	return tmp;
}
stock SetVehicleSpeed(vehicleid, Float:speed)
{
    new Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2, Float:a;
    GetVehicleVelocity(vehicleid, x1, y1, z1);
    GetVehiclePos(vehicleid, x2, y2, z2);
    GetVehicleZAngle(vehicleid, a); a = 360 - a;
    x1 = (floatsin(a, degrees) * (speed/100) + floatcos(a, degrees) * 0 + x2) - x2;
    y1 = (floatcos(a, degrees) * (speed/100) + floatsin(a, degrees) * 0 + y2) - y2;
    SetVehicleVelocity(vehicleid, x1, y1, z1);
}
stock GetLighterColor(color[], multip)
{
	new __str__[80];
	format(__str__, sizeof(__str__), "%s", color);
	for(new i; i < multip; i++)
	{
		strins(__str__, "~h~", strlen(color));
	}
	
	return __str__;
}
stock DarkerNick(c)
{
	new h[1];
	h[0] = c;
	h{3} = 45;
	return h[0];
}

stock SetAlpha(c,alpha)
{
	new h[1];
	h[0] = c;
	h{3} = alpha;
	return h[0];
}

stock AddAllSkins()
{
	AddPlayerClassEx2(0, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);//no skiny meskie ale w³asnie w mapie w wybiera³ce one s¹ po koleji: 1,2,3,4,5,6,7,8,9,10,11,12,13,14
	//AddPlayerClassEx2(0, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
	//AddPlayerClassEx2(1, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    //AddPlayerClassEx2(2, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);//no bo tak maja byc wtf 
    AddPlayerClassEx2(303, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(3, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(4, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(5, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(6, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(7, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(8, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(14, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(15, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(16, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(17, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(18, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(19, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(20, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(21, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(22, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(23, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(24, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(25, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(26, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(27, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(28, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(29, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(30, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(32, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(33, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(34, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(35, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(36, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(37, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(42, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(43, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(44, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(45, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(46, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(47, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(48, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(49, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(50, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(51, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(52, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(57, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(58, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(59, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(60, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(61, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(62, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(66, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(67, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(68, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(70, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(71, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(72, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(73, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(78, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(79, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(80, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(81, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(82, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(83, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(84, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(86, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(94, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(95, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(96, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(97, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(98, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(99, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(100, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(101, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(102, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(103, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(104, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(105, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(106, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(107, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(108, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(109, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(110, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(111, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(112, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(113, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(114, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(115, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(116, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(117, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(118, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(119, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(120, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(121, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(122, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(123, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(124, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(125, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(126, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(127, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(128, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(132, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(133, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(134, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(135, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(136, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(137, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(142, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(143, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(144, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(146, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(147, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(149, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(153, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(154, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(155, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(156, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(158, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(159, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(160, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(161, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(162, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(163, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(164, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(165, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(166, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(167, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(168, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(170, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(171, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(173, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(174, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(175, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(176, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(177, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(179, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(180, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(181, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(182, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(183, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(184, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(185, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(186, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(187, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(188, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(189, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(200, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(202, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(203, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(204, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(206, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(208, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(209, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(210, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(212, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(213, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(217, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(220, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(221, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(222, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(223, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(227, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(228, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(229, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(230, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(234, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(235, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(236, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(239, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(240, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(241, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(242, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(247, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(248, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(249, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(250, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(252, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(253, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(254, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(255, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(258, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(259, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(260, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(261, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(262, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(264, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(265, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
  //  AddPlayerClassEx2(266, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(267, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
  //  AddPlayerClassEx2(268, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(269, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    //AddPlayerClassEx2(270, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    //AddPlayerClassEx2(271, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(272, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(273, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(274, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    //AddPlayerClassEx2(275, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
  //  AddPlayerClassEx2(276, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(277, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    //AddPlayerClassEx2(278, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(279, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(280, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(281, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(282, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(283, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(284, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(285, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(286, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(287, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(288, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(289, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(290, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(291, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(292, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(293, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(294, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(295, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(296, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(297, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(299, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(300, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(301, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(302, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(303, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(304, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(305, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(310, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(311, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);

	//Kobiety
    AddPlayerClassEx2(9, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(10, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(11, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(12, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(13, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(219, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(224, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(225, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(226, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(231, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(233, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(237, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(238, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
	AddPlayerClassEx2(31, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(38, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(39, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(40, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(41, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(53, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(75, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(76, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(77, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(85, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(87, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(88, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(89, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(90, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(91, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(92, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(93, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(129, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(130, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(131, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(138, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(139, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(140, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(141, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(145, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(148, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(150, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(151, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(152, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(157, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(169, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(172, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(190, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(191, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(192, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(193, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(194, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(195, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(196, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(197, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(198, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(199, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(201, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(205, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(207, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(211, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(214, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(215, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(216, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(218, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(243, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(244, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(245, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(246, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(251, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(256, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(257, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(263, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(298, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(54, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(55, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(56, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(63, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(64, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(65, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(69, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(306, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(307, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(308, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
    AddPlayerClassEx2(309, 2481.8794,-1665.4646,12.8973,209.1601, 0, 0, 0, 0, 0, 0);
}
stock AddPlayerClassEx2(skin, Float:x, Float:y, Float:z, Float:Angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo)
{

	if(skin == 1 || skin == 2)
		return printf("[Missing Error] AddPlayerClassEx2 -> skin = %d;", skin);
	gmData[gm_skins][skin] = skin;
	gmData[gm_skinscount]++;
	return AddPlayerClass(skin, x, y, z, Angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);
}
stock GetSkinAddID(skinid)
{
	for(new i;i<gmData[gm_skinscount];i++) if(gmData[gm_skins][i] == skinid) return i;
	return 0;
}
stock DzisiejszaData(const data[])
{
	new d,m,r, strdata[15];
	getdate(r, m, d);
	format(strdata, sizeof(strdata), "%02d-%02d-%02d", r, m, d);
	return strcmp(strdata, data, true, strlen(strdata));
}
stock SetTDSkinID(skinid, &s1, &s2, &s3)
{
	/*
		skinid - aktualny œrodkowy skimn
		s1 - pierwszy skin
		s2 - œrodkowy
		s3 - ostatni..

	*/
/*
	if(!skinid)
	{
		s1 = gmData[gm_skins][gmData[gm_skinscount] - 1];
	} 
	else s1 = gmData[gm_skins][skinid-1];
	
	s2 = gmData[gm_skins][skinid];
	
	if(skinid > 311)
	{
		s3 = gmData[gm_skins][0];
	} else s3 = gmData[gm_skins][skinid+1];
*/

	if(skinid < 0) s2 = 310;
	else if(skinid  > 310) s2 = 0;
	else s2 = skinid;

	s1 = s2 - 1;
	s3 = s2 + 1;

	if(s1 < 0) s1 = 310;
	if(s1 > 310) s1 = 0;

	if(s3 < 0) s3 = 310;
	if(s3 > 310) s3 = 0;

	CheckSkinIsAdded(s1, true);
	CheckSkinIsAdded(s3, false);
}

stock CheckSkinIsAdded(&skin, bool:down)
{
	if(!gmData[gm_skins][skin])
	{
		new bool:xyz = true;
		while(xyz) //stunff
		{
			if(down)
			{
				skin--;

				if(skin < 0) skin = 310;
				if(gmData[gm_skins][skin])
					return;
			}
			else 
			{
				skin++;

				if(skin > 310) skin = 0;
				if(gmData[gm_skins][skin])
					return;
			}
		}
	}
}
stock UpdatePlayerClassSelect(playerid,  s1, s2, s3)
{
	pInfo[playerid][player_skin] = s2;

	PlayerTextDrawSetPreviewModel(playerid, SelectSkin_[0], s1);
	PlayerTextDrawSetPreviewModel(playerid, SelectSkin_[1], s2);
	PlayerTextDrawSetPreviewModel(playerid, SelectSkin_[2], s3);
		
	PlayerTextDrawSetString(playerid, SelectSkin_[4], splitf("ID: %d", s1));
	PlayerTextDrawSetString(playerid, SelectSkin_[5], splitf("ID: %d", s2));
	PlayerTextDrawSetString(playerid, SelectSkin_[6], splitf("ID: %d", s3));
			
	for(new i; i < 10; i++) PlayerTextDrawShow(playerid, SelectSkin_[i]);
}

stock GetTextDrawCount()
{
	new Text:c;
	TextDrawDestroy((c = TextDrawCreate(0.0, 0.0, "EOS"), c));
	return _:c;
}
stock tostr(dec)
{
	return splitf("%d", dec);
	/*new ix[64];
	format(ix, sizeof(ix), "%d", dec);
	return ix;
*/}
stock AddTop(name[], sql[], cat)
{
	new c = topCount[cat];
	format(topInfo[cat][c][ename], 64, "%s", name);
	format(topInfo[cat][c][esql], 36, "%s", sql);
	
	topCount[cat]++;
}
stock LoadTop()
{
	AddTop("Najwiêcej Respektu", "score", 0); //Kategoria: Dotycz¹ce gry
	AddTop("Najwiêcej Kasy", "cash", 0);//1
	AddTop("Najwiêcej Zabiæ", "kills", 0);//2
	AddTop("Najwiêcej Œmierci", "deaths", 0);//3
	AddTop("Najwiêcej Samobójstw", "suicides", 0);//4
	AddTop("Najwiêcej Osi¹gniêæ", "achievements_count", 0);//5
	AddTop("Najw j Mandatów", "mandats", 0);//19
	AddTop("Najwiêcej Czasu Gry", "timeplay", 0);//20
	AddTop("Najwiêkszy Skill", "skill", 0);//21
	
	AddTop("Najwiêcej wygranych /WG", "wg", 1); //Kategoria: Dotycz¹ce eventow
	AddTop("Najwiêcej wygranych /CH", "ch", 1);//1
	AddTop("Najwiêcej wygranych /HY", "hy", 1);//2
	AddTop("Najwiêcej wygranych /WS", "ws", 1);//3
	AddTop("Najwiêcej wygranych /DD", "dd", 1);//4
	AddTop("Najwiêcej wygranych /CTF", "ctf", 1);//5
	AddTop("Najwiêcej wygranych /ZB", "zb", 1);//6
	AddTop("Najwiêcej wygranych /TR", "tr", 1);//7
	
	AddTop("Najwiêcej fragów /OneDe", "onede", 2); //Kategoria: Dotycz¹ce aren
	AddTop("Najwiêcej fragów /Minigun", "minigun", 2);//1
	AddTop("Najwiêcej fragów /Sawn", "sawn", 2);//2
	AddTop("Najwiêcej fragów /Snajper", "snajper", 2);//3...
	AddTop("Najwiêcej fragów /ArenaGang", "arenagang", 2);

	AddTop("Przepisanych kodów", "result_codes", 3); ////Kategoria: inne
	AddTop("Testów Matematycznych", "result_matematyk", 3);
	AddTop("U³o¿onych s³ówek", "result_scrable", 3);
	//AddTop("Najszybciej przepisany kod", "cast(timecodes as decimal(38,10))", 3);  
//	AddTop("Najszybciej podany wynik", "cast(timematematyk as decimal(38,10))", 3); 
	//AddTop("Najszybciej u³o¿one s³ówko", "cast(timescrable as decimal(38,10))", 3); 
	
}

stock LoadRadars()
{
	new czas = GetTickCount();
	mysql_query("select * from "prefix"_radars limit "#MAX_RADAR"");
	mysql_store_result();
	new strx[ 150 ], 
		param[ 200 ];
	RadarsCount=0;
	
	while (mysql_fetch_row(param, "|"))
	{
	    new Float:angle;
	    sscanf(param, "p<|>ifffffi", RadarInfo[RadarsCount][RADid], RadarInfo[RadarsCount][RADx], RadarInfo[RadarsCount][RADy], RadarInfo[RadarsCount][RADz], angle, RadarInfo[RadarsCount][RADrange], RadarInfo[RadarsCount][RADlimit]);
		
		format(strx, sizeof strx, "FOTORADAR\n"HEX_ERROR"Ograniczenie do "HEX_SAMP"%d km/h"HEX_ERROR".", RadarInfo[RadarsCount][RADlimit]);
		
		CreateDynamic3DTextLabel(strx, COLOR_SAMP, RadarInfo[RadarsCount][RADx], RadarInfo[RadarsCount][RADy], RadarInfo[RadarsCount][RADz] + 0.5, 50);
		CreateDynamicObject(18880, RadarInfo[RadarsCount][RADx], RadarInfo[RadarsCount][RADy], RadarInfo[RadarsCount][RADz] - 1.0, 0.0, 0.0, angle);
		
		RadarInfo[RadarsCount][RADStrefa] = CreateDynamicSphere(RadarInfo[RadarsCount][RADx], RadarInfo[RadarsCount][RADy], RadarInfo[RadarsCount][RADz], 40);
		RadarsCount++;
	}
	printf("[load] wczytanych radarów:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	mysql_free_result();
}


stock SetVehiclesToRespawn()
{
	new count;
	for(new i=0; i<MAX_VEHICLES; i++)
	{
		if(!IsVehicleInUse(i) && GetVehicleModel(i) && !IsTrailer(i) && !Vehicle_IsPriv(i) && !Vehicle_IsWp(i))
		{
			SetVehicleToRespawn(i);
			count++;
		}
	}
	return count;
}

stock SetVehicleToDelete()
{
	new count;
	for(new i=gmData[last_vehicle];i<MAX_VEHICLES;i++)
	{
		if(!IsVehicleInUse(i) && !Vehicle_IsPriv(i) && !IsTrailer(i) && GetVehicleModel(i))
		{
			foreach(new playerid : Player)
			{
				if(pInfo[playerid][player_vehicle] == i) pInfo[playerid][player_vehicle] = 0;
			}
		
 			DestroyVehicleEx(i);
			count++;
		}
	}
	return count;
}
/*
stock ReloadAllVehicles()
{
	for(new i=0;i<MAX_VEHICLES;i++) DestroyVehicle(i);
	
	new count = LoadVehiclesFromData(0, gmData[last_vehicle]);
	
	foreach(new i : Player)
	{
		gmData[player_vehicleid][i] = 0;
		LoadPlayerVehicle(i);
	}
	
	SendClientMessageToAll(COLOR_INFO2, ""chat" [System] Prze³adowano wszystkie pojazdy! Na mapie jest ich %d.", count);
	return count;
}*/

stock OnPlayerChangeVehicle(playerid)
{
	if(GetVehicleModel(pInfo[playerid][player_usevehicle])) 
	{
		//PlayerTextDrawSetPreviewModel(playerid, pInfo[playerid][player_TextureVeh], GetVehicleModel(GetPlayerVehicleID(playerid)));
		//PlayerTextDrawShow(playerid, pInfo[playerid][player_TextureVeh]);
		
		PlayerText_Licznik(playerid, false);
		PlayerText_Licznik(playerid, true);
	}
	return 1;
}

stock GetPlayerAbsentDays(ltime)
	return (gettime()-ltime)/86400;
	
	
stock OnPlayerDisconnectReports(playerid)
{ 

	for(new i;i<MAX_RAPORTOW;i++)
	{
		if(rData[i][rUsed])
		{
			
			if(rData[i][rZglaszajacy] == playerid || rData[i][rZgloszony] == playerid)	
				rData[i][rUsed] = false;
		}
	}

	return 1;
}

stock AddNewReport(playerid, zgloszonyid, reason[])
{ 
	new sqlreason[64];
	
	mysql_real_escape_string(reason, sqlreason);
	
	m_query("INSERT INTO mreg_reports (`given`, `user`, `start_time`, `reason`, `given_username`) VALUES ('%d', '%d', CURRENT_TIMESTAMP, '%s', '%s|%s');", pInfo[playerid][player_id], pInfo[zgloszonyid][player_id], sqlreason, playerNick(playerid), playerNick(zgloszonyid));
	new acount, addreport;
	foreach(new i : Admins)
	{
		SendClientMessage(i, COLOR_INFO2, "» [Raport] %s (%d) zg³asza gracza %s (%d) powód {b}%s{/b}.", playerNick(playerid), playerid, playerNick(zgloszonyid), zgloszonyid,reason);
		SendClientMessage(i, 0xFF000010, "» Lista raportów dostêpna pod komend¹ {b}/reports{/b}. Pamiêtaj aby po sprawdzeniu raportu usun¹æ go!");
		#if defined ADUIO_PLUGIN
		if(Audio_IsClientConnected(i))
		{
			Audio_PlayEx(i,NEW_REPORT);
		}
		else 
		#endif
		if(!is_event(i) && !pInfo[i][player_arena] && pInfo[i][player_lastshowreport] < gettime()) 
		{
	//		ShowPlayerDialog(i, 9999, DIALOG_STYLE_MSGBOX, "Report", string2, "Ok", "");
		}
		InfoTDBox(i, "~r~OTRZYMA£EŒ NOWY RAPORT~n~~r~SPRAWDZ GO!");
		
		pInfo[i][player_lastshowreport] = gettime() + 25;
		acount++;
	}	
	for(new i;i<MAX_RAPORTOW;i++)
	{
		if(!rData[i][rUsed])
		{
			
			rData[i][rZglaszajacy] = playerid;
			rData[i][rZgloszony] = zgloszonyid;
			format(rData[i][rReason], 59, "%s", reason);
			rData[i][rUsed] = true;
			rData[i][rMessage] = false;
			addreport = 1;
			break;
		}
	}
	if(!addreport)
	{
		rData[0][rZglaszajacy] = playerid;
		rData[0][rZgloszony] = zgloszonyid;
		format(rData[0][rReason], 59, "%s", reason);
		rData[0][rUsed] = true;
		rData[0][rMessage] = false;
	}
	return acount;
}
stock Reports(playerid)
{
	string2[0] = EOS;
	
	new g;
	for(new i;i<MAX_RAPORTOW;i++)
	{
		if(!rData[i][rUsed]) continue;
		
		format(string2, sizeof string2, "%s%d.%s -> %s: %s\n", string2, g, playerNick(rData[i][rZglaszajacy]), playerNick(rData[i][rZgloszony]), rData[i][rReason]);
		
		pInfo[playerid][player_reportID][g] = i;
		g++;
	}
	if(!g) 
		InfoBox(playerid, "Brak raportów");
	else 
		Dialog_Show(playerid, DIALOG_REPORTS, DIALOG_STYLE_LIST, "Raporty", string2, "Wybierz", "Anuluj");
}
new rtfa_str2[512 + 128], rtfa_str[5][68] /*5x64*/; 
new rtfa_lastreport[68];
stock ReportTextdrawForAdmin(report[])
{
	if(report[0] && rtfa_lastreport[0])
	{
		if(strcmp(rtfa_lastreport, report, true) == 0)
		{
			ReportsTextdrawShow();
			return;
		}
	}
	format(rtfa_lastreport, sizeof(rtfa_lastreport), "%s", report);
	//AdminTDInfo
	new czh, czm;
	gettime(czh, czm);
	
	for(new s = 4; s >= 1; s--) rtfa_str[s] = rtfa_str[s - 1];
	
	strins((rtfa_str[0][0]=EOS, rtfa_str[0]), splitf("~w~[%02d:%02d] %s~n~", czh, czm, report), 0);
	rtfa_str2[0] = EOS;
	
	for(new s = 0; s < 5; s++)
		strcat(rtfa_str2, rtfa_str[s]);

	 
	TextDrawSetString(AdminTDInfo, rtfa_str2);
	ReportsTextdrawShow();
} 
stock ReportsTextdrawShow(bool:upg = false)
{
	foreach(new i : Admins)
	{
		TextDrawShowForPlayer(i, AdminTDInfo);
		if(upg)
		{
			PlaySoundForPlayer(i, 1027);
			FlashScreen(i);
		}
	}
}
stock SetPlayerFacingPlayer(playerid, targetid)
{
	new Float:p_pos[4];
	GetPointInAngleOfPlayer(playerid, p_pos[0], p_pos[1], p_pos[2], 1.5, 180.0);
	GetPlayerFacingAngle(playerid, p_pos[3]);
	
	SetPlayerPos(targetid, p_pos[0], p_pos[1], p_pos[2]);
	SetPlayerFacingAngle(targetid, p_pos[3]);
	/*
	if(p_pos[3] <= 90.0) SetPlayerFacingAngle(targetid, 180.0 + p_pos[3]);
	else if(p_pos[3] > 270.0) SetPlayerFacingAngle(targetid, 90.0 + (p_pos[3] - 270.0));
	else if(p_pos[3] > 90.0 && p_pos[3] <= 180.0) SetPlayerFacingAngle(targetid, 270.0 + (p_pos[3] - 90.0));
	else if(p_pos[3] > 180.0 && p_pos[3] <= 270.0) SetPlayerFacingAngle(targetid, 0.0 + (p_pos[3] - 180.0));
	*/
	
	return 1;
}

stock GetPointInAngleOfPlayer(playerid, &Float:x, &Float:y, &Float:z, Float:distance, Float:angle)
{
	new Float:current_angle;
	GetPlayerPos(playerid, x, y, z);
	
	GetPlayerFacingAngle(playerid, current_angle);
	
	if(IsPlayerInAnyVehicle(playerid))
	{
		GetVehicleZAngle(GetPlayerVehicleID(playerid), current_angle);
	}
	
	new Float:a = current_angle + angle;
	
	x += (distance * floatsin(-a, degrees));
	y += (distance * floatcos(-a, degrees));
}
stock SpawnWeapon(w)
{
	if(w==(29,30,31,25,27,26,34,22,24)) return 1;
	return 0;
}
stock IsPlayerValid(p)
{
	if(!IsPlayerConnected(p)) return 1;
	switch(p)
	{
		case 0..MAX_PLAYERS: return 0;
	}
	return 1;
}
CMD:turbo(playerid, cmd[])
{
	if(!GetPVarInt(playerid, "NRG_TURBO")) 
	{
	 
		switch(IsPlayerVehicleTurbo(playerid))
		{
			case -1:
			{
				SendClientMessage(playerid, COLOR_ERROR, ""chat" Turbo w Infernusach jest tylko dla VIPów");
				return 1;
			}
			case 0:
			{
				SendClientMessage(playerid, COLOR_ERROR, ""chat" Turbo jest dostêpne tylko w NRG (dla vipów te¿ w infernusach)");
				return 1;
			}
			case 1:
			{
				SetPVarInt(playerid, "NRG_TURBO", 1);
				SendClientMessage(playerid, COLOR_INFO2, ""chat" Aktywowa³eœ turbo! Aby wy³¹czyæ wpisz ponownie /turbo");
				return 1;
			}
		}
	}
	else
	{
	
		SetPVarInt(playerid, "NRG_TURBO", 0);
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Wy³¹czy³eœ TURBO");		
	}
	return 1;
}
stock IsPlayerVehicleTurbo(playerid)
{
	new vehicle = GetVehicleModel(pInfo[playerid][player_usevehicle]);
	if(vehicle == 522 || vehicle == 411) return 1;
	return 0;
}
Public:Loteria__Public(playerid)
{
	switch(random(24))
	{		
		case 0:
		{
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) jetpack'a w {b}(/Loteria) "HEX_GREEN_YELLOW"- Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);		
			SetPlayerSpecialAction(playerid, 2);
		}
		case 1:
		{
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) 20 expa w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			GivePlayerScore(playerid, 20);
		}
		case 2:
		{
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) 50 expa w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			GivePlayerScore(playerid, 50);
		}
		case 3:
		{
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) mega zestaw broni w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			
			GivePlayerWeapon(playerid, 24, 5000);
			GivePlayerWeapon(playerid, 9, 1);
			GivePlayerWeapon(playerid, 26, 5000);
			GivePlayerWeapon(playerid, 30, 5000);
			GivePlayerWeapon(playerid, 34, 5000);
			achievement(playerid, 17);
		}
		case 4:
		{
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s nic nie wygra³(a) :(w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			
		}
		case 5:
		{
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) losowy spawn w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			
			OnPlayerSpawn(playerid);
		}
		case 6:
		{
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) -50 expa w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			
			GivePlayerScore(playerid, -50);
		}
		case 7:
		{
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s nic nie wygra³(a) :(w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			
		}
		case 8:
		{
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) reset swojego ekwipunku w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			ResetPlayerWeapons(playerid);
		}
		case 9:
		{
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) bombe w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			new Float:PlayerPos[3];
			GetPlayerPos(playerid, PlayerPos[0], PlayerPos[1], PlayerPos[2]);
			CreateExplosion(PlayerPos[0], PlayerPos[1], PlayerPos[2], 7, 5.0);
		}
		case 10:
		{
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s nic nie wygra³(a) :(w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			
		}
		case 11:
		{
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) ¿ycie oraz kamizelkê w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			
			SetPlayerHealth(playerid, 100);
			SetPlayerArmour(playerid, 100);
		}
		case 12,13:
		{
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) bombe w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			
			new Float:PlayerPos[3];
			GetPlayerPos(playerid, PlayerPos[0], PlayerPos[1], PlayerPos[2]);
			CreateExplosion(PlayerPos[0], PlayerPos[1], PlayerPos[2], 7, 5.0);
		}
		case 14:
		{
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) -20 expa w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			
			GivePlayerScore(playerid, -20);
		}
		case 15: {
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) Monster trucka w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);

			new cv = CreatePlayerVehicle(playerid, 557);
			PutPlayerInVehicle(playerid,cv,0);
		}
		case 16: {
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) Minigunna z 10 ammo w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);

			GivePlayerWeapon(playerid,38,10);
		}
		case 17: {
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) Rogi w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);

			SetPlayerAttachedObject(playerid, 0, 19314, 2, 0.157000, 0.000000, 0.000000, -0.199999, -7.600006, -88.599998, 1.000000, 1.000000, 1.000000);//cuernos 1
		}
		case 18: {
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) 2 nasionka zio³a w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);

			pInfo[playerid][player_nasionka] += 2;
		}
		case 19: {
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) Spadochron w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			
			GivePlayerWeapon(playerid, 46,1);
		}
		case 20: {
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) 25.000$ w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			
			GivePlayerMoney(playerid,25000);
		}
		case 21: {
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) 100.000$ w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			
			GivePlayerMoney(playerid,100000);
		}
		case 22: {
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) -100.000$ w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			
			GivePlayerMoney(playerid,-100000);
		}
		case 23: {
			SendClientMessageToAll(COLOR_GOLD, ""chat" "HEX_GREEN_YELLOW"Gracz %s wygra³(a) -20.000$ w {b}(/Loteria) - "HEX_GREEN_YELLOW"Losowaæ, wygrywaæ nie za³owaæ!",pInfo[playerid][player_name]);
			
			GivePlayerMoney(playerid,-20000);
		}
	}
	return 1;
}
Public:CreatePlayerTurbo(playerid, l_Step)
{
	if (l_Step>0 && (GetPlayerState(playerid)!=PLAYER_STATE_DRIVER))
		l_Step=19;
	switch(l_Step)
	{
		case 0: 
		{
			if (GetTickCount()-GetPVarInt(playerid, "vehicleSpecialLastUsed")<7000)
				return;
				
			new Float:ST[3];
			GetVehicleVelocity(pInfo[playerid][player_usevehicle], ST[0], ST[1], ST[2]);
		
			new spd = floatround(floatsqroot(floatpower(ST[0], 2) + floatpower(ST[1], 2) + floatpower(ST[2], 2)) * 200);
		
 			if (spd<10) return;
			if (spd<60) 
			{
				GameTextForPlayer(playerid, "~n~~n~~n~~g~Jedziesz zbyt wolno", 500, 5);
				return;
			} 
			else if (spd>200)
				return;
			SetPVarInt(playerid, "vehicleSpecialLastUsed", GetTickCount());
			SetPlayerAttachedObject(playerid, 9, 18718, 1, 0.000000, 0.500000, 0.000000, 90.000000, 335.000000, 25.000000, 1.000000, 1.000000, 1.000000);
			CreatePlayerTurbo(playerid, l_Step+1);
			return;//18718
		}
		case 1..18: 
		{
			new Float:PV[3], Float:VA;
			new Keys, ud, lr;
			GetPlayerKeys(playerid, Keys, ud, lr);

			GetVehicleVelocity(pInfo[playerid][player_usevehicle], PV[0], PV[1], PV[2]);
			GetVehicleZAngle(pInfo[playerid][player_usevehicle], VA);
			
			new spd = floatround(floatsqroot(floatpower(PV[0], 2) + floatpower(PV[1], 2) + floatpower(PV[2], 2)) * 200);
		
			PV[0]+=(0.3*floatsin(-VA, degrees));
			PV[1]+=(0.3*floatcos(-VA, degrees));
			
			if (Keys&KEY_SPRINT==KEY_SPRINT) 
			{
				if (spd<300)
					SetVehicleVelocity(pInfo[playerid][player_usevehicle], PV[0], PV[1], PV[2]*1.05);
			} 
			else if (Keys&KEY_JUMP!=KEY_JUMP && random(2)==1 && l_Step>1)
				l_Step--;	
			else if (Keys&KEY_JUMP==KEY_JUMP && l_Step<18) l_Step++;	// hamulec

			SetTimerEx("CreatePlayerTurbo", Keys&KEY_SPRINT==KEY_SPRINT ? 130 : 250, false, "dd", playerid, l_Step+1);
	 	}
		case 19: 
		{
			RemovePlayerAttachedObject(playerid, 9);
			return;
		}
	}
	return;
}
stock ResetPlayerWeapons2(playerid,...) //by Mr_Auto
{
	new weapons[13][2],
		arweapon = GetPlayerWeapon(playerid);
	for(new SL; SL < 13; SL++)
	{
		GetPlayerWeaponData(playerid, SL, weapons[SL][0], weapons[SL][1]);
	}
	if(numargs() <= 1)
		return 0;
	new ID;
	for(new z = 1; z < numargs(); z++)
	{
	    ID = getarg(z,0);
	    if(IsWeapon(ID))
			continue;
	    if(weapons[GetWeaponSlot(ID)][0] == ID)
			weapons[GetWeaponSlot(ID)][0] = 0;
	}
	ResetPlayerWeapons(playerid);
	for(new SL; SL < 13; SL++)
	{
	    if(weapons[SL][0] == 0)
			continue;
	    GivePlayerWeapon(playerid, weapons[SL][0], weapons[SL][1]);
	}
	if(weapons[GetWeaponSlot(arweapon)][0] == 0)
		SetPlayerArmedWeapon(playerid,0);
	else
		SetPlayerArmedWeapon(playerid, arweapon);
	return 1;
}

new const weaponslots[] =
{
	0,0,1,1,1,1,1,1,1,1,10,10,10,10,10,10,8,8,-1,-1,-1,8,
	2,2,2,3,3,3,4,4,5,5,4,6,6,7,7,7,7,8,12,9,9,9,11,11,11
};

stock GetWeaponSlot(weaponid)
{
	if(!(0 <= weaponid <= sizeof(weaponslots)))
		return -1;

	return weaponslots[weaponid];
}

stock IsSum(lb)
{
	switch(lb)
	{
		case 1..15:return 1;
	}
	return 0;
}
stock GetWeekDay(day=0, month=0, year=0) 
{ 
	if(!day) 
	{
		getdate(year, month, day); 
	}
	new st[2];
	if(month <= 2) 
	{ 
		month += 12; 
		--year; 
	} 
	st[0] = year %100; 
	st[1] = year / 100; 
	switch((day + (month+1)*26/10 + st[0] + st[0]/4 + st[1]/4 - 2*st[1]) %7) 
	{ 
		case 0: return 6; //Sobota 
		case 1: return 7; //Niedziela 
		case 2: return 1; //Poniedzia³ek 
		case 3: return 2; //Wtorek 
		case 4: return 3; //Œroda 
		case 5: return 4; //Czwartek 
		case 6: return 5; //Pi¹tek 
	} 
	return -1; 
}
stock get_random(str[], size = sizeof(str))
{	
	new len = random(15) + 10;	
	if(len > size - 1) len = size-1; 
	for(new i;i<len;i++)
	{
		str[i] = random(10)>5?(random(25)+'a'):(random(25)+'A');
	}
	str[random(len)] = random(8)+'1';
	str[random(len)] = random(8)+'1';
	str[random(len)] = random(8)+'1';
	str[random(len)] = random(8)+'1';
	str[random(len)] = random(8)+'1';
	
}
stock TeleportPlayerToPlayer(playerid, targetid, bool:info = false)
{
	if(!IsPlayerConnected(playerid) || !IsPlayerConnected(targetid)) return;
	new Float:pos[7],
		interior=GetPlayerInterior(targetid),
		virtualworld=GetPlayerVirtualWorld(targetid);

	if(IsPlayerInAnyVehicle(targetid))
	{
		new vehicleid = GetPlayerVehicleID(targetid);

		GetVehiclePos(vehicleid, pos[0], pos[1], pos[2]);
		GetVehicleZAngle(vehicleid, pos[3]);
		GetVehicleVelocity(vehicleid, pos[4], pos[5], pos[6]);
		pos[2] += 2.0;
	}
	else
	{
		GetPlayerPos(targetid, pos[0], pos[1], pos[2]);
		GetPlayerFacingAngle(targetid, pos[3]);
		GetPlayerVelocity(targetid, pos[4], pos[5], pos[6]);
		pos[0] -= floatsin(-pos[3], degrees);
		pos[1] -= floatcos(-pos[3], degrees);
	}

	if(IsPlayerInAnyVehicle(playerid))
	{
		new vehicleid = GetPlayerVehicleID(playerid);

		SetVehiclePos(vehicleid, pos[0], pos[1], pos[2]);
		SetVehicleZAngle(vehicleid, pos[3]);
		SetVehicleVelocity(vehicleid, pos[4], pos[5], pos[6]);
		LinkVehicleToInterior(vehicleid, interior);
		SetVehicleVirtualWorld(vehicleid, virtualworld);
	}
	else
	{
		SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		SetPlayerFacingAngle(playerid, pos[3]);
		SetPlayerVelocity(playerid, pos[4], pos[5], pos[6]);
		SetPlayerInterior(playerid, interior);
		SetPlayerVirtualWorld(playerid, virtualworld);
	}
	if(info)
	{
		SendClientMessage(playerid, COLOR_DARKSLATEGRAY, " Zosta³eœ teleportowany do gracza %s (%d).", playerNick(targetid), targetid);
		SendClientMessage(targetid, COLOR_DARKSLATEGRAY, " Gracz %s (%d) zosta³ do Ciebie teleportowany.", playerNick(playerid), playerid);
	}
}
stock _check(ip_long) 
{
	match(ip_long, 0x527C000, 0x15);//5
	match(ip_long, 0x5398000, 0x12);//5
	match(ip_long, 0x53C0000, 0x10);//5
	match(ip_long, 0x53FB800, 0x15);//5
	match(ip_long, 0x5664000, 0x15);//5
	match(ip_long, 0x568D000, 0x15);//5
	match(ip_long, 0x568F800, 0x15);//5
	match(ip_long, 0x5850800, 0x15);//5
	match(ip_long, 0x585F800, 0x15);//5
	match(ip_long, 0x5864000, 0x14);//5
	match(ip_long, 0x586D000, 0x15);//5
	match(ip_long, 0x595A000, 0x15);//5
	match(ip_long, 0x595C000, 0x15);//5
	match(ip_long, 0x598A000, 0x15);//5
	match(ip_long, 0x5ACB800, 0x15);//5
	match(ip_long, 0x5ACE000, 0x13);//5
	match(ip_long, 0x5AD0000, 0x10);//5
	match(ip_long, 0x5AE0000, 0x10);//5
	match(ip_long, 0x5B80000, 0xF);//5
	match(ip_long, 0x5BB3000, 0x15);//5
	match(ip_long, 0x5C90000, 0x11);//5
	match(ip_long, 0x5CEF000, 0x14);//5
	match(ip_long, 0x5E24000, 0x12);//5
	match(ip_long, 0x5E28000, 0x15);//5
	match(ip_long, 0x1F000000, 0xF);//3
	match(ip_long, 0x1F020000, 0x11);//3
	match(ip_long, 0x1F064000, 0x15);//3
	match(ip_long, 0x1F068000, 0x11);//3
	match(ip_long, 0x1F072800, 0x15);//3
	match(ip_long, 0x1F0B8000, 0x11);//3
	match(ip_long, 0x1F166000, 0x15);//3
	match(ip_long, 0x1F19F800, 0x15);//3
	match(ip_long, 0x1F3C0000, 0xE);//3
	match(ip_long, 0x1FACB000, 0x14);//3
	match(ip_long, 0x1FAE0000, 0xF);//3
	match(ip_long, 0x1FB20000, 0xF);//3
	match(ip_long, 0x1FB60000, 0xF);//3
	match(ip_long, 0x1FBA5000, 0x15);//3
	match(ip_long, 0x1FBAC000, 0x13);//3
	match(ip_long, 0x1FBB0000, 0x12);//3
	match(ip_long, 0x1FC0D800, 0x15);//3
	match(ip_long, 0x1FC16000, 0x15);//3
	match(ip_long, 0x1FD83800, 0x15);//3
	match(ip_long, 0x1FDC9000, 0x15);//3
	match(ip_long, 0x1FDE1000, 0x15);//3
	match(ip_long, 0x25070000, 0x10);//3
	match(ip_long, 0x2508C000, 0x12);//3
	match(ip_long, 0x251AA000, 0x15);//3
	match(ip_long, 0x251AC000, 0x15);//3
	match(ip_long, 0x251C9800, 0x15);//3
	match(ip_long, 0x251E0000, 0xF);//3
	match(ip_long, 0x252F0000, 0x10);//3
	match(ip_long, 0x253C1800, 0x15);//3
	match(ip_long, 0x25487800, 0x15);//3
	match(ip_long, 0x2548A800, 0x15);//3
	match(ip_long, 0x254D9800, 0x15);//3
	match(ip_long, 0x2562D000, 0x14);//3
	match(ip_long, 0x256C0000, 0x10);//3
	match(ip_long, 0x256D0000, 0x10);//3
	match(ip_long, 0x257BC800, 0x15);//3
	match(ip_long, 0x25800000, 0x11);//3
	match(ip_long, 0x25809800, 0x15);//3
	match(ip_long, 0x2580A000, 0x15);//3
	match(ip_long, 0x25820000, 0x12);//3
	match(ip_long, 0x25838000, 0x13);//3
	match(ip_long, 0x2583A000, 0x14);//3
	match(ip_long, 0x258B4800, 0x15);//3
	match(ip_long, 0x258B9000, 0x15);//3
	match(ip_long, 0x25981000, 0x14);//3
	match(ip_long, 0x259DC800, 0x15);//3
	match(ip_long, 0x25BE8000, 0x11);//3
	match(ip_long, 0x25CA2000, 0x14);//3
	match(ip_long, 0x25D18000, 0x13);//3
	match(ip_long, 0x25E10000, 0x10);//3
	match(ip_long, 0x25E40000, 0x12);//3
	match(ip_long, 0x25E96000, 0x14);//3
	match(ip_long, 0x25F73800, 0x15);//3
	match(ip_long, 0x25F78000, 0x11);//3
	match(ip_long, 0x25F80000, 0xF);//3
	match(ip_long, 0x2E117000, 0x15);//4
	match(ip_long, 0x2E143000, 0x14);//4
	match(ip_long, 0x2E15D000, 0x14);//4
	match(ip_long, 0x2E16A000, 0x14);//4
	match(ip_long, 0x2E1C0800, 0x15);//4
	match(ip_long, 0x2E1CF000, 0x15);//4
	match(ip_long, 0x2E1D1000, 0x15);//4
	match(ip_long, 0x2E1D9000, 0x15);//4
	match(ip_long, 0x2E1F2000, 0x15);//4
	match(ip_long, 0x2E24E000, 0x13);//4
	match(ip_long, 0x2E298000, 0x12);//4
	match(ip_long, 0x2E2D4000, 0x12);//4
	match(ip_long, 0x2E4C0000, 0xF);//4
	match(ip_long, 0x2E700000, 0xF);//4
	match(ip_long, 0x2E860000, 0x10);//4
	match(ip_long, 0x2EA80000, 0xF);//4
	match(ip_long, 0x2EAA0000, 0xF);//4
	match(ip_long, 0x2EB66000, 0x15);//4
	match(ip_long, 0x2EB7D000, 0x15);//4
	match(ip_long, 0x2EBA0000, 0x11);//4
	match(ip_long, 0x2EBB8000, 0x11);//4
	match(ip_long, 0x2ECC0000, 0xF);//4
	match(ip_long, 0x2ED70000, 0x10);//4
	match(ip_long, 0x2EE32000, 0x15);//4
	match(ip_long, 0x2EE36800, 0x15);//4
	match(ip_long, 0x2EE3F000, 0x15);//4
	match(ip_long, 0x2EE45000, 0x14);//4
	match(ip_long, 0x2EE4E000, 0x14);//4
	match(ip_long, 0x2EE59000, 0x14);//4
	match(ip_long, 0x2EE73800, 0x15);//4
	match(ip_long, 0x2EE79800, 0x15);//4
	match(ip_long, 0x2EE88000, 0x15);//4
	match(ip_long, 0x2EEB7800, 0x15);//4
	match(ip_long, 0x2EEE4000, 0x12);//4
	match(ip_long, 0x2EEEC000, 0x12);//4
	match(ip_long, 0x2EEF8000, 0x12);//4
	match(ip_long, 0x2EF28000, 0x11);//4
	match(ip_long, 0x2EF5C000, 0x15);//4
	match(ip_long, 0x2EF8A000, 0x13);//4
	match(ip_long, 0x2EFAA000, 0x13);//4
	match(ip_long, 0x2EFDD000, 0x14);//4
	match(ip_long, 0x2EFE4800, 0x15);//4
	match(ip_long, 0x3E03A000, 0x13);//6
	match(ip_long, 0x3E150000, 0x11);//6
	match(ip_long, 0x3E1D8000, 0x11);//6
	match(ip_long, 0x3E3D2000, 0x13);//6
	match(ip_long, 0x3E45C000, 0x12);//6
	match(ip_long, 0x3E578000, 0x11);//6
	match(ip_long, 0x3E594000, 0x12);//6
	match(ip_long, 0x3E5D2000, 0x13);//6
	match(ip_long, 0x3E6CA000, 0x13);//6
	match(ip_long, 0x3E6F8000, 0x11);//6
	match(ip_long, 0x3E794000, 0x12);//6
	match(ip_long, 0x3E798000, 0x13);//6
	match(ip_long, 0x3E81C000, 0x12);//6
	match(ip_long, 0x3E858000, 0x13);//6
	match(ip_long, 0x3E8DC000, 0x12);//6
	match(ip_long, 0x3E944000, 0x13);//6
	match(ip_long, 0x3E988000, 0x13);//6
	match(ip_long, 0x3EB50000, 0x13);//6
	match(ip_long, 0x3EB5A000, 0x13);//6
	match(ip_long, 0x3EE98000, 0x13);//6
	match(ip_long, 0x3EE9A000, 0x13);//6
	match(ip_long, 0x3EE9C000, 0x12);//6
	match(ip_long, 0x3EF48000, 0x13);//6
	match(ip_long, 0x4D200000, 0xF);//7
	match(ip_long, 0x4D2D0000, 0x11);//7
	match(ip_long, 0x4D2E0000, 0x11);//7
	match(ip_long, 0x4D370000, 0x10);//7
	match(ip_long, 0x4D410000, 0x11);//7
	match(ip_long, 0x4D418000, 0x11);//7
	match(ip_long, 0x4D4FC000, 0x12);//7
	match(ip_long, 0x4D588000, 0x12);//7
	match(ip_long, 0x4D594000, 0x12);//7
	match(ip_long, 0x4D5B0000, 0x12);//7
	match(ip_long, 0x4D5C2000, 0x13);//7
	match(ip_long, 0x4D5F3000, 0x15);//7
	match(ip_long, 0x4D700000, 0xE);//7
	match(ip_long, 0x4DDEE000, 0x13);//7
	match(ip_long, 0x4DDFC000, 0x13);//7
	match(ip_long, 0x4DDFE000, 0x13);//7
	match(ip_long, 0x4DEC0000, 0x13);//7
	match(ip_long, 0x4DED0000, 0x13);//7
	match(ip_long, 0x4DF2E000, 0x14);//7
	match(ip_long, 0x4DF5F000, 0x14);//7
	match(ip_long, 0x4DFC0000, 0xE);//7
	match(ip_long, 0x4E080000, 0xE);//7
	match(ip_long, 0x4E18A000, 0x15);//7
	match(ip_long, 0x4E1C0000, 0x12);//7
	match(ip_long, 0x4E1E4000, 0x12);//7
	match(ip_long, 0x4E291800, 0x15);//7
	match(ip_long, 0x4E580000, 0x10);//7
	match(ip_long, 0x4E838000, 0x11);//7
	match(ip_long, 0x4E858000, 0x11);//7
	match(ip_long, 0x4E980000, 0x13);//7
	match(ip_long, 0x4E9A4000, 0x13);//7
	match(ip_long, 0x4E9B6000, 0x13);//7
	match(ip_long, 0x4E9CA000, 0x13);//7
	match(ip_long, 0x4E9F4000, 0x13);//7
	match(ip_long, 0x4F600000, 0x10);//7
	match(ip_long, 0x4F629000, 0x15);//7
	match(ip_long, 0x4F6E0000, 0x14);//7
	match(ip_long, 0x4F7C6000, 0x13);//7
	match(ip_long, 0x4F85C000, 0x13);//7
	match(ip_long, 0x4F87A000, 0x13);//7
	match(ip_long, 0x4F8B0000, 0x11);//7
	match(ip_long, 0x4FA20000, 0xF);//7
	match(ip_long, 0x4FAA7800, 0x15);//7
	match(ip_long, 0x4FAB0000, 0x15);//7
	match(ip_long, 0x4FAD0000, 0x12);//7
	match(ip_long, 0x4FAFC000, 0x12);//7
	match(ip_long, 0x4FB80000, 0xD);//7
	match(ip_long, 0x50300000, 0xD);//8
	match(ip_long, 0x50482000, 0x14);//8
	match(ip_long, 0x5048C000, 0x14);//8
	match(ip_long, 0x50521000, 0x14);//8
	match(ip_long, 0x5055E000, 0x14);//8
	match(ip_long, 0x50572000, 0x14);//8
	match(ip_long, 0x505E1000, 0x14);//8
	match(ip_long, 0x50F0A000, 0x14);//8
	match(ip_long, 0x50F0B000, 0x14);//8
	match(ip_long, 0x50F18000, 0x15);//8
	match(ip_long, 0x50F48000, 0x14);//8
	match(ip_long, 0x50F49000, 0x14);//8
	match(ip_long, 0x50F5B000, 0x14);//8
	match(ip_long, 0x50F90000, 0x14);//8
	match(ip_long, 0x50FC0000, 0x14);//8
	match(ip_long, 0x51068000, 0x12);//8
	match(ip_long, 0x510F8000, 0x11);//8
	match(ip_long, 0x5112C000, 0x14);//8
	match(ip_long, 0x5112D000, 0x14);//8
	match(ip_long, 0x5115C000, 0x14);//8
	match(ip_long, 0x511A0000, 0x14);//8
	match(ip_long, 0x511A1000, 0x14);//8
	match(ip_long, 0x511E8000, 0x14);//8
	match(ip_long, 0x515FC000, 0x14);//8
	match(ip_long, 0x51A88000, 0x11);//8
	match(ip_long, 0x51BE0000, 0x10);//8
	match(ip_long, 0x51D20000, 0x11);//8
	match(ip_long, 0x51DB0000, 0x10);//8
	match(ip_long, 0x52734000, 0x13);//8
	match(ip_long, 0x528B0000, 0x12);//8
	match(ip_long, 0x528B8000, 0x12);//8
	match(ip_long, 0x528F8000, 0x12);//8
	match(ip_long, 0x52914000, 0x13);//8
	match(ip_long, 0x5292E000, 0x13);//8
	match(ip_long, 0x52A00000, 0x10);//8
	match(ip_long, 0x52B10000, 0x10);//8
	match(ip_long, 0x52C52000, 0x13);//8
	match(ip_long, 0x52D28000, 0x12);//8
	match(ip_long, 0x52D68000, 0x12);//8
	match(ip_long, 0x53000000, 0xB);//8
	match(ip_long, 0x53444000, 0x13);//8
	match(ip_long, 0x53889800, 0x15);//8
	match(ip_long, 0x5388E000, 0x15);//8
	match(ip_long, 0x53904000, 0x12);//8
	match(ip_long, 0x53918000, 0x12);//8
	match(ip_long, 0x53A84000, 0x12);//8
	match(ip_long, 0x53DA6000, 0x13);//8
	match(ip_long, 0x53DC6000, 0x13);//8
	match(ip_long, 0x53E60000, 0x11);//8
	match(ip_long, 0x53EE0000, 0x10);//8
	match(ip_long, 0x540A0000, 0x10);//8
	match(ip_long, 0x5417A000, 0x13);//8
	match(ip_long, 0x5427A000, 0x14);//8
	match(ip_long, 0x54288000, 0x11);//8
	match(ip_long, 0x550B4000, 0x12);//8
	match(ip_long, 0x550E4000, 0x12);//8
	match(ip_long, 0x551C8000, 0x12);//8
	match(ip_long, 0x5559A000, 0x13);//8
	match(ip_long, 0x5570C000, 0x13);//8
	match(ip_long, 0x55750000, 0x13);//8
	match(ip_long, 0x55800000, 0x11);//8
	match(ip_long, 0x55808000, 0x11);//8
	match(ip_long, 0x55C1C000, 0x12);//8
	match(ip_long, 0x55C6C000, 0x12);//8
	match(ip_long, 0x55DB8000, 0x11);//8
	match(ip_long, 0x55DD8000, 0x11);//8
	match(ip_long, 0x55DE0000, 0x11);//8
	match(ip_long, 0x55E8E000, 0x13);//8
	match(ip_long, 0x55EDA000, 0x13);//8
	match(ip_long, 0x563F4000, 0x12);//8
	match(ip_long, 0x563F8000, 0x13);//8
	match(ip_long, 0x57600000, 0x11);//8
	match(ip_long, 0x57630000, 0x12);//8
	match(ip_long, 0x57690000, 0x10);//8
	match(ip_long, 0x5774C000, 0x12);//8
	match(ip_long, 0x57770000, 0x12);//8
	match(ip_long, 0x57C70000, 0x10);//8
	match(ip_long, 0x57CC0000, 0xF);//8
	match(ip_long, 0x57CE0000, 0xF);//8
	match(ip_long, 0x57F6C000, 0x12);//8
	match(ip_long, 0x57F84000, 0x13);//8
	match(ip_long, 0x57FAA000, 0x13);//8
	match(ip_long, 0x57FBE000, 0x13);//8
	match(ip_long, 0x58978800, 0x15);//8
	match(ip_long, 0x589C0000, 0x10);//8
	match(ip_long, 0x58C70000, 0x10);//8
	match(ip_long, 0x58DC0000, 0x10);//8
	match(ip_long, 0x5911E000, 0x13);//8
	match(ip_long, 0x59198000, 0x11);//8
	match(ip_long, 0x591CE000, 0x15);//8
	match(ip_long, 0x591F4000, 0x15);//8
	match(ip_long, 0x59400000, 0xC);//8
	match(ip_long, 0x596B9800, 0x15);//8
	match(ip_long, 0x596CC000, 0x12);//8
	match(ip_long, 0x59970000, 0x12);//8
	match(ip_long, 0x59A10000, 0x11);//8
	match(ip_long, 0x59A18000, 0x11);//8
	match(ip_long, 0x59A70000, 0x11);//8
	match(ip_long, 0x59AB0000, 0x10);//8
	match(ip_long, 0x59AE0000, 0x10);//8
	match(ip_long, 0x59BA0000, 0x13);//8
	match(ip_long, 0x59BBE000, 0x13);//8
	match(ip_long, 0x59BCC000, 0x13);//8
	match(ip_long, 0x59BF8000, 0x13);//8
	match(ip_long, 0x59BFA000, 0x13);//8
	match(ip_long, 0x59E40000, 0xE);//8
	match(ip_long, 0x59E96800, 0x15);//8
	match(ip_long, 0x59EAC000, 0x12);//8
	match(ip_long, 0x59EE0000, 0x12);//8
	match(ip_long, 0x59EF4000, 0x12);//8
	match(ip_long, 0x59FAC000, 0x14);//8
	match(ip_long, 0x5A9C0000, 0x11);//9
	match(ip_long, 0x5B5E0000, 0x10);//9
	match(ip_long, 0x5B666800, 0x15);//9
	match(ip_long, 0x5B667000, 0x15);//9
	match(ip_long, 0x5B6A1800, 0x15);//9
	match(ip_long, 0x5B8EC000, 0x14);//9
	match(ip_long, 0x5B918000, 0x12);//9
	match(ip_long, 0x5B92C000, 0x12);//9
	match(ip_long, 0x5B95C000, 0x12);//9
	match(ip_long, 0x5BB9B800, 0x15);//9
	match(ip_long, 0x5BBBE000, 0x13);//9
	match(ip_long, 0x5BBC6000, 0x13);//9
	match(ip_long, 0x5C2A7000, 0x15);//9
	match(ip_long, 0x5C2B7000, 0x15);//9
	match(ip_long, 0x5C2B9000, 0x15);//9
	match(ip_long, 0x5C37C000, 0x12);//9
	match(ip_long, 0x5C3C8000, 0x14);//9
	match(ip_long, 0x5C3F2000, 0x14);//9
	match(ip_long, 0x5CF42000, 0x13);//9
	match(ip_long, 0x5D59C000, 0x14);//9
	match(ip_long, 0x5D5BD000, 0x14);//9
	match(ip_long, 0x5D5E1000, 0x15);//9
	match(ip_long, 0x5D5EB800, 0x15);//9
	match(ip_long, 0x5D5F5800, 0x15);//9
	match(ip_long, 0x5D690000, 0x10);//9
	match(ip_long, 0x5D9A8000, 0x11);//9
	match(ip_long, 0x5D9EE800, 0x16);//9
	match(ip_long, 0x5D9F0000, 0x12);//9
	match(ip_long, 0x5D9F8000, 0x12);//9
	match(ip_long, 0x5DAE1800, 0x15);//9
	match(ip_long, 0x5DB0C000, 0x12);//9
	match(ip_long, 0x5DB3C000, 0x12);//9
	match(ip_long, 0x5DB4A000, 0x13);//9
	match(ip_long, 0x5DB58000, 0x12);//9
	match(ip_long, 0x5E280000, 0x10);//9
	match(ip_long, 0x5E2A0000, 0x10);//9
	match(ip_long, 0x5E484000, 0x12);//9
	match(ip_long, 0x5E4B4000, 0x12);//9
	match(ip_long, 0x5E4E8000, 0x12);//9
	match(ip_long, 0x5E651000, 0x14);//9
	match(ip_long, 0x5E7C0000, 0x15);//9
	match(ip_long, 0x5E7C0800, 0x15);//9
	match(ip_long, 0x5E7C1000, 0x15);//9
	match(ip_long, 0x5E7F6800, 0x15);//9
	match(ip_long, 0x5E8D8000, 0x13);//9
	match(ip_long, 0x5E980000, 0x10);//9
	match(ip_long, 0x5EE5D000, 0x14);//9
	match(ip_long, 0x5EE61000, 0x14);//9
	match(ip_long, 0x5EE7E000, 0x14);//9
	match(ip_long, 0x5EF00000, 0x12);//9
	match(ip_long, 0x5EF68000, 0x12);//9
	match(ip_long, 0x5EFB8000, 0x11);//9
	match(ip_long, 0x5EFE8000, 0x11);//9
	match(ip_long, 0x5F280000, 0xF);//9
	match(ip_long, 0x5F300000, 0xE);//9
	match(ip_long, 0x5F6C0000, 0x11);//9
	match(ip_long, 0x5F81E000, 0x15);//9
	match(ip_long, 0x5F832000, 0x15);//9
	match(ip_long, 0x5F8EF000, 0x14);//9
	match(ip_long, 0x5F8FF000, 0x14);//9
	match(ip_long, 0x5F9B4000, 0x12);//9
	match(ip_long, 0x5F9E4000, 0x12);//9
	match(ip_long, 0x5FA00000, 0x10);//9
	match(ip_long, 0x5FAB6000, 0x13);//9
	match(ip_long, 0x5FABC000, 0x13);//9
	match(ip_long, 0x5FAE2000, 0x13);//9
	match(ip_long, 0x5FAF0000, 0x13);//9
	match(ip_long, 0x5FB20000, 0x11);//9
	match(ip_long, 0x6D455800, 0x15);//1
	match(ip_long, 0x6D4A6000, 0x14);//1
	match(ip_long, 0x6D6B0000, 0x13);//1
	match(ip_long, 0x6D6EC000, 0x13);//1
	match(ip_long, 0x6D7DC000, 0x12);//1
	match(ip_long, 0x6DAD8000, 0x11);//1
	match(ip_long, 0x6DC70000, 0x13);//1
	match(ip_long, 0x6DC74000, 0x13);//1
	match(ip_long, 0x6DC84000, 0x13);//1
	match(ip_long, 0x6DCD3000, 0x15);//1
	match(ip_long, 0x6DE70000, 0x12);//1
	match(ip_long, 0x6DE81800, 0x15);//1
	match(ip_long, 0x6DE8F000, 0x15);//1
	match(ip_long, 0x6DE95800, 0x15);//1
	match(ip_long, 0x6DE96800, 0x15);//1
	match(ip_long, 0x6DF10000, 0x10);//1
	match(ip_long, 0x6DF30000, 0x10);//1
	match(ip_long, 0x807F5000, 0x14);//1
	match(ip_long, 0x80CCD800, 0x15);//1
	match(ip_long, 0x82B4C000, 0x15);//1
	match(ip_long, 0x82B96000, 0x15);//1
	match(ip_long, 0x82FF9800, 0x15);//1
	match(ip_long, 0x8D691000, 0x15);//1
	match(ip_long, 0x8D8AA000, 0x15);//1
	match(ip_long, 0x94510000, 0x10);//1
	match(ip_long, 0x96FE0000, 0x10);//1
	match(ip_long, 0x97F82000, 0x14);//1
	match(ip_long, 0x97F83800, 0x15);//1
	match(ip_long, 0x97F95000, 0x15);//1
	match(ip_long, 0x9EFF5800, 0x15);//1
	match(ip_long, 0x9FCD0000, 0x10);//1
	match(ip_long, 0x9FFDF000, 0x15);//1
	match(ip_long, 0x9FFFB000, 0x14);//1
	match(ip_long, 0xA428F000, 0x15);//1
	match(ip_long, 0xA47E0000, 0xF);//1
	match(ip_long, 0xB020A000, 0x14);//1
	match(ip_long, 0xB03A1000, 0x15);//1
	match(ip_long, 0xB0DD6000, 0x13);//1
	match(ip_long, 0xB0E3A000, 0x15);//1
	match(ip_long, 0xB0F14800, 0x15);//1
	match(ip_long, 0xB0F1F000, 0x15);//1
	match(ip_long, 0xB2106000, 0x14);//1
	match(ip_long, 0xB2107000, 0x14);//1
	match(ip_long, 0xB2136000, 0x14);//1
	match(ip_long, 0xB213B000, 0x14);//1
	match(ip_long, 0xB2158800, 0x15);//1
	match(ip_long, 0xB2159800, 0x15);//1
	match(ip_long, 0xB2176800, 0x15);//1
	match(ip_long, 0xB217C000, 0x15);//1
	match(ip_long, 0xB2240000, 0xF);//1
	match(ip_long, 0xB22A0000, 0xF);//1
	match(ip_long, 0xB2380000, 0x10);//1
	match(ip_long, 0xB2490000, 0x12);//1
	match(ip_long, 0xB2B40000, 0xE);//1
	match(ip_long, 0xB2EB0000, 0x10);//1
	match(ip_long, 0xB2EEF000, 0x14);//1
	match(ip_long, 0xB2EF0000, 0x14);//1
	match(ip_long, 0xB2EF8000, 0x14);//1
	match(ip_long, 0xB2F84800, 0x15);//1
	match(ip_long, 0xB2F95800, 0x15);//1
	match(ip_long, 0xB2FA2800, 0x15);//1
	match(ip_long, 0xB2FC0000, 0x12);//1
	match(ip_long, 0xB2FF2800, 0x15);//1
	match(ip_long, 0xB9022400, 0x16);//1
	match(ip_long, 0xB9023C00, 0x16);//1
	match(ip_long, 0xB9024C00, 0x16);//1
	match(ip_long, 0xB9027000, 0x16);//1
	match(ip_long, 0xB9033C00, 0x16);//1
	match(ip_long, 0xB9037000, 0x16);//1
	match(ip_long, 0xB903E000, 0x16);//1
	match(ip_long, 0xB904D400, 0x16);//1
	match(ip_long, 0xB9056000, 0x16);//1
	match(ip_long, 0xB905D800, 0x16);//1
	match(ip_long, 0xB9060000, 0x16);//1
	match(ip_long, 0xB9061C00, 0x16);//1
	match(ip_long, 0xB9063400, 0x16);//1
	match(ip_long, 0xB9067000, 0x16);//1
	match(ip_long, 0xB9076800, 0x16);//1
	match(ip_long, 0xB907A800, 0x16);//1
	match(ip_long, 0xB9093800, 0x16);//1
	match(ip_long, 0xB9097C00, 0x16);//1
	match(ip_long, 0xB90A1800, 0x16);//1
	match(ip_long, 0xB90A7800, 0x16);//1
	match(ip_long, 0xB90B6400, 0x16);//1
	match(ip_long, 0xB90B6C00, 0x16);//1
	match(ip_long, 0xB90B8000, 0x16);//1
	match(ip_long, 0xB90C1400, 0x16);//1
	match(ip_long, 0xB90D9000, 0x16);//1
	match(ip_long, 0xB90DA800, 0x16);//1
	match(ip_long, 0xB90DAC00, 0x16);//1
	match(ip_long, 0xB90DB800, 0x16);//1
	match(ip_long, 0xB90DE800, 0x16);//1
	match(ip_long, 0xB90E4800, 0x16);//1
	match(ip_long, 0xB90E7000, 0x16);//1
	match(ip_long, 0xB90E9400, 0x16);//1
	match(ip_long, 0xB90F0000, 0x16);//1
	match(ip_long, 0xB90F2C00, 0x16);//1
	match(ip_long, 0xB90F5000, 0x16);//1
	match(ip_long, 0xB90F8400, 0x16);//1
	match(ip_long, 0xB90FE800, 0x16);//1
	match(ip_long, 0xB9102000, 0x16);//1
	match(ip_long, 0xB9102400, 0x16);//1
	match(ip_long, 0xB9108000, 0x16);//1
	match(ip_long, 0xB9109000, 0x16);//1
	match(ip_long, 0xB9112800, 0x16);//1
	match(ip_long, 0xB911A000, 0x16);//1
	match(ip_long, 0xB9124400, 0x16);//1
	match(ip_long, 0xB9128400, 0x16);//1
	match(ip_long, 0xB9128C00, 0x16);//1
	match(ip_long, 0xB912B000, 0x16);//1
	match(ip_long, 0xB9137400, 0x16);//1
	match(ip_long, 0xB9141400, 0x16);//1
	match(ip_long, 0xB9149400, 0x16);//1
	match(ip_long, 0xB914AC00, 0x16);//1
	match(ip_long, 0xB9152400, 0x16);//1
	match(ip_long, 0xB9155400, 0x16);//1
	match(ip_long, 0xB9159400, 0x16);//1
	match(ip_long, 0xB9160800, 0x16);//1
	match(ip_long, 0xB9167000, 0x16);//1
	match(ip_long, 0xB9168800, 0x16);//1
	match(ip_long, 0xB9170C00, 0x16);//1
	match(ip_long, 0xB9171400, 0x16);//1
	match(ip_long, 0xB9179400, 0x16);//1
	match(ip_long, 0xB9181800, 0x16);//1
	match(ip_long, 0xB9185800, 0x16);//1
	match(ip_long, 0xB918A400, 0x16);//1
	match(ip_long, 0xB918C400, 0x16);//1
	match(ip_long, 0xB918C800, 0x16);//1
	match(ip_long, 0xB918D800, 0x16);//1
	match(ip_long, 0xB9196C00, 0x16);//1
	match(ip_long, 0xB9197800, 0x16);//1
	match(ip_long, 0xB9199400, 0x16);//1
	match(ip_long, 0xB919D800, 0x16);//1
	match(ip_long, 0xB91B3400, 0x16);//1
	match(ip_long, 0xB91BBC00, 0x16);//1
	match(ip_long, 0xB91C1000, 0x16);//1
	match(ip_long, 0xB91C7400, 0x16);//1
	match(ip_long, 0xB91CB000, 0x16);//1
	match(ip_long, 0xB91CF800, 0x16);//1
	match(ip_long, 0xB91D0C00, 0x16);//1
	match(ip_long, 0xB91D5400, 0x16);//1
	match(ip_long, 0xB91E7C00, 0x16);//1
	match(ip_long, 0xB91F1800, 0x16);//1
	match(ip_long, 0xB91F3000, 0x16);//1
	match(ip_long, 0xB91F5000, 0x16);//1
	match(ip_long, 0xB91F5800, 0x16);//1
	match(ip_long, 0xB91FB800, 0x16);//1
	match(ip_long, 0xB91FD800, 0x16);//1
	match(ip_long, 0xB9200400, 0x16);//1
	match(ip_long, 0xB9203000, 0x16);//1
	match(ip_long, 0xB9209000, 0x16);//1
	match(ip_long, 0xB9209C00, 0x16);//1
	match(ip_long, 0xB9212400, 0x16);//1
	match(ip_long, 0xB9221C00, 0x16);//1
	match(ip_long, 0xB9223000, 0x16);//1
	match(ip_long, 0xB9224C00, 0x16);//1
	match(ip_long, 0xB922EC00, 0x16);//1
	match(ip_long, 0xB923C400, 0x16);//1
	match(ip_long, 0xB9249800, 0x16);//1
	match(ip_long, 0xB924A800, 0x16);//1
	match(ip_long, 0xB9257000, 0x16);//1
	match(ip_long, 0xB926DC00, 0x16);//1
	match(ip_long, 0xB926E000, 0x16);//1
	match(ip_long, 0xB926F800, 0x16);//1
	match(ip_long, 0xB927A000, 0x16);//1
	match(ip_long, 0xB9287000, 0x16);//1
	match(ip_long, 0xB928E400, 0x16);//1
	match(ip_long, 0xB9294400, 0x16);//1
	match(ip_long, 0xB9295000, 0x16);//1
	match(ip_long, 0xB9295C00, 0x16);//1
	match(ip_long, 0xB9298000, 0x16);//1
	match(ip_long, 0xB92A2C00, 0x16);//1
	match(ip_long, 0xB92AB800, 0x16);//1
	match(ip_long, 0xB92B8800, 0x16);//1
	match(ip_long, 0xB92BA000, 0x16);//1
	match(ip_long, 0xB92CAC00, 0x16);//1
	match(ip_long, 0xB92CD800, 0x16);//1
	match(ip_long, 0xB92DD800, 0x16);//1
	match(ip_long, 0xB92E5C00, 0x16);//1
	match(ip_long, 0xB92E6800, 0x16);//1
	match(ip_long, 0xB92EA800, 0x16);//1
	match(ip_long, 0xB92ECC00, 0x16);//1
	match(ip_long, 0xB92EF000, 0x16);//1
	match(ip_long, 0xB92EF400, 0x16);//1
	match(ip_long, 0xB92F4000, 0x16);//1
	match(ip_long, 0xB9300800, 0x16);//1
	match(ip_long, 0xB9301C00, 0x16);//1
	match(ip_long, 0xB9308000, 0x16);//1
	match(ip_long, 0xB930A800, 0x16);//1
	match(ip_long, 0xB930B000, 0x16);//1
	match(ip_long, 0xB930E800, 0x16);//1
	match(ip_long, 0xB9310C00, 0x16);//1
	match(ip_long, 0xB9311C00, 0x16);//1
	match(ip_long, 0xB9319400, 0x16);//1
	match(ip_long, 0xB931C800, 0x16);//1
	match(ip_long, 0xB9323000, 0x16);//1
	match(ip_long, 0xBC210000, 0x10);//1
	match(ip_long, 0xBC2F0000, 0x10);//1
	match(ip_long, 0xBC405000, 0x15);//1
	match(ip_long, 0xBC412800, 0x15);//1
	match(ip_long, 0xBC5DA000, 0x15);//1
	match(ip_long, 0xBC5F1800, 0x15);//1
	match(ip_long, 0xBC700000, 0x12);//1
	match(ip_long, 0xBC724000, 0x13);//1
	match(ip_long, 0xBC740000, 0x12);//1
	match(ip_long, 0xBC758000, 0x12);//1
	match(ip_long, 0xBC790000, 0x13);//1
	match(ip_long, 0xBC7A0000, 0x13);//1
	match(ip_long, 0xBC7BC000, 0x13);//1
	match(ip_long, 0xBC7CA000, 0x13);//1
	match(ip_long, 0xBC7D2000, 0x13);//1
	match(ip_long, 0xBC7D8000, 0x13);//1
	match(ip_long, 0xBC7DE000, 0x13);//1
	match(ip_long, 0xBC7F0000, 0x13);//1
	match(ip_long, 0xBC808000, 0x11);//1
	match(ip_long, 0xBC890000, 0x11);//1
	match(ip_long, 0xBC920000, 0xF);//1
	match(ip_long, 0xBCA49000, 0x15);//1
	match(ip_long, 0xBCA4F000, 0x15);//1
	match(ip_long, 0xBCF68000, 0x13);//1
	match(ip_long, 0xBCFC0000, 0x11);//1
	match(ip_long, 0xC13B0000, 0x10);//1
	match(ip_long, 0xC15B0000, 0x14);//1
	match(ip_long, 0xC15B1000, 0x14);//1
	match(ip_long, 0xC1C0A000, 0x15);//1
	match(ip_long, 0xC1C0A800, 0x16);//1
	match(ip_long, 0xC1C0AC00, 0x16);//1
	match(ip_long, 0xC1C0B000, 0x14);//1
	match(ip_long, 0xC1C14000, 0x13);//1
	match(ip_long, 0xC25C0000, 0x10);//1
	match(ip_long, 0xC2B50000, 0x10);//1
	match(ip_long, 0xC2B72000, 0x13);//1
	match(ip_long, 0xC2CC8000, 0x13);//1
	match(ip_long, 0xC2CCA000, 0x13);//1
	match(ip_long, 0xC3088000, 0x13);//1
	match(ip_long, 0xC3508000, 0x15);//1
	match(ip_long, 0xC352A000, 0x13);//1
	match(ip_long, 0xC35EC000, 0x13);//1
	match(ip_long, 0xC372A000, 0x13);//1
	match(ip_long, 0xC3740000, 0x10);//1
	match(ip_long, 0xC3750000, 0x10);//1
	match(ip_long, 0xC3880000, 0x10);//1
	match(ip_long, 0xC38CEC00, 0x16);//1
	match(ip_long, 0xC3960000, 0x10);//1
	match(ip_long, 0xC3A40000, 0x10);//1
	match(ip_long, 0xC3BB0000, 0x10);//1
	match(ip_long, 0xC3CD0000, 0x10);//1
	match(ip_long, 0xC3D86000, 0x13);//1
	match(ip_long, 0xD4026000, 0x13);//2
	match(ip_long, 0xD40E0000, 0x13);//2
	match(ip_long, 0xD40E2000, 0x13);//2
	match(ip_long, 0xD4214000, 0x13);//2
	match(ip_long, 0xD426C000, 0x13);//2
	match(ip_long, 0xD4312000, 0x13);//2
	match(ip_long, 0xD433C000, 0x13);//2
	match(ip_long, 0xD43BE000, 0x13);//2
	match(ip_long, 0xD4438000, 0x13);//2
	match(ip_long, 0xD4454000, 0x13);//2
	match(ip_long, 0xD44B6000, 0x13);//2
	match(ip_long, 0xD44C2000, 0x13);//2
	match(ip_long, 0xD44D6000, 0x13);//2
	match(ip_long, 0xD4556000, 0x13);//2
	match(ip_long, 0xD4570000, 0x13);//2
	match(ip_long, 0xD457E000, 0x13);//2
	match(ip_long, 0xD45B0000, 0x13);//2
	match(ip_long, 0xD460E000, 0x13);//2
	match(ip_long, 0xD46A0000, 0x13);//2
	match(ip_long, 0xD46A8000, 0x12);//2
	match(ip_long, 0xD46D8000, 0x13);//2
	match(ip_long, 0xD46DA000, 0x15);//2
	match(ip_long, 0xD47AC000, 0x13);//2
	match(ip_long, 0xD47E0000, 0x13);//2
	match(ip_long, 0xD47F4000, 0x13);//2
	match(ip_long, 0xD4A00000, 0x10);//2
	match(ip_long, 0xD4B48000, 0x11);//2
	match(ip_long, 0xD4B60000, 0x11);//2
	match(ip_long, 0xD4BF0000, 0x10);//2
	match(ip_long, 0xD4CB8000, 0x11);//2
	match(ip_long, 0xD4F40000, 0x10);//2
	match(ip_long, 0xD5118000, 0x11);//2
	match(ip_long, 0xD5190000, 0x10);//2
	match(ip_long, 0xD5490000, 0x13);//2
	match(ip_long, 0xD54C0000, 0x10);//2
	match(ip_long, 0xD54D0000, 0x10);//2
	match(ip_long, 0xD55C8000, 0x11);//2
	match(ip_long, 0xD5868000, 0x13);//2
	match(ip_long, 0xD586A000, 0x13);//2
	match(ip_long, 0xD5872000, 0x13);//2
	match(ip_long, 0xD588E000, 0x13);//2
	match(ip_long, 0xD5922000, 0x13);//2
	match(ip_long, 0xD59BA000, 0x13);//2
	match(ip_long, 0xD59C6000, 0x13);//2
	match(ip_long, 0xD59EC000, 0x13);//2
	match(ip_long, 0xD5A16000, 0x13);//2
	match(ip_long, 0xD5ACA000, 0x13);//2
	match(ip_long, 0xD5B48000, 0x13);//2
	match(ip_long, 0xD5B80000, 0x13);//2
	match(ip_long, 0xD5BA4000, 0x13);//2
	match(ip_long, 0xD5BD2000, 0x13);//2
	match(ip_long, 0xD5C04000, 0x12);//2
	match(ip_long, 0xD5C38000, 0x12);//2
	match(ip_long, 0xD5C7C000, 0x12);//2
	match(ip_long, 0xD5D84000, 0x12);//2
	match(ip_long, 0xD5DA4000, 0x12);//2
	match(ip_long, 0xD5DEC000, 0x13);//2
	match(ip_long, 0xD5E34000, 0x12);//2
	match(ip_long, 0xD5E7C000, 0x12);//2
	match(ip_long, 0xD5EE4000, 0x12);//2
	match(ip_long, 0xD5F10000, 0x11);//2
	match(ip_long, 0xD908A000, 0x14);//2
	match(ip_long, 0xD908B000, 0x14);//2
	match(ip_long, 0xD909A000, 0x14);//2
	match(ip_long, 0xD909B000, 0x14);//2
	match(ip_long, 0xD90B8000, 0x14);//2
	match(ip_long, 0xD90B9000, 0x14);//2
	match(ip_long, 0xD9112000, 0x14);//2
	match(ip_long, 0xD91C9000, 0x14);//2
	match(ip_long, 0xD91E8000, 0x14);//2
	match(ip_long, 0xD91E9000, 0x14);//2
	match(ip_long, 0xD943C000, 0x14);//2
	match(ip_long, 0xD943D000, 0x14);//2
	match(ip_long, 0xD9463000, 0x14);//2
	match(ip_long, 0xD949B000, 0x14);//2
	match(ip_long, 0xD949F000, 0x14);//2
	match(ip_long, 0xD94A4000, 0x14);//2
	match(ip_long, 0xD94B3000, 0x14);//2
	match(ip_long, 0xD94C7000, 0x14);//2
	match(ip_long, 0xD94F9000, 0x14);//2
	match(ip_long, 0xD9600000, 0xE);//2
	match(ip_long, 0xD9718000, 0x14);//2
	match(ip_long, 0xD9719000, 0x14);//2
	match(ip_long, 0xD971E000, 0x14);//2
	match(ip_long, 0xD9746000, 0x14);//2
	match(ip_long, 0xD9758000, 0x14);//2
	match(ip_long, 0xD9774000, 0x14);//2
	match(ip_long, 0xD990C000, 0x14);//2
	match(ip_long, 0xD990D000, 0x14);//2
	match(ip_long, 0xD995F000, 0x14);//2
	match(ip_long, 0xD9990000, 0x11);//2
	match(ip_long, 0xD9998000, 0x11);//2
	match(ip_long, 0xD9A88000, 0x14);//2
	match(ip_long, 0xD9A8C000, 0x14);//2
	match(ip_long, 0xD9AAA000, 0x14);//2
	match(ip_long, 0xD9AB3000, 0x14);//2
	match(ip_long, 0xD9ACE000, 0x14);//2
	match(ip_long, 0xD9ACF000, 0x14);//2
	match(ip_long, 0xD9AD0000, 0x14);//2
	match(ip_long, 0xD9ADC000, 0x14);//2
	match(ip_long, 0xD9C5A000, 0x14);//2
	match(ip_long, 0x1F291800, 0x15);//3
	match(ip_long, 0x1F295000, 0x15);//3
	match(ip_long, 0x1F298800, 0x15);//3
	match(ip_long, 0x1F299000, 0x15);//3
	match(ip_long, 0x1F29A800, 0x15);//3
	match(ip_long, 0x1F29B000, 0x15);//3
	match(ip_long, 0x1F29D000, 0x15);//3
	match(ip_long, 0x1F29E800, 0x15);//3
	match(ip_long, 0x1F2A0000, 0x14);//3
	match(ip_long, 0x1F2A1000, 0x14);//3
	match(ip_long, 0x1F800000, 0x13);//3
	match(ip_long, 0x1F826000, 0x14);//3
	match(ip_long, 0x1F82D800, 0x15);//3
	match(ip_long, 0x1F833000, 0x14);//3
	match(ip_long, 0x1F83A800, 0x15);//3
	match(ip_long, 0x1F844000, 0x15);//3
	match(ip_long, 0x1F850000, 0x15);//3
	match(ip_long, 0x1F851000, 0x15);//3
	match(ip_long, 0x1F863000, 0x14);//3
	match(ip_long, 0x1F871000, 0x14);//3
	match(ip_long, 0x1F87A000, 0x15);//3
	match(ip_long, 0x1F87A800, 0x15);//3
	match(ip_long, 0x1F87C000, 0x14);//3
	match(ip_long, 0x2E940000, 0x14);//4
	match(ip_long, 0x2E944000, 0x14);//4
	match(ip_long, 0x2E945000, 0x14);//4
	match(ip_long, 0x2E949000, 0x14);//4
	match(ip_long, 0x2E94A000, 0x14);//4
	match(ip_long, 0x2E959000, 0x14);//4
	match(ip_long, 0x2E95D000, 0x14);//4
	match(ip_long, 0x2E95F000, 0x14);//4
	match(ip_long, 0x2E971000, 0x15);//4
	match(ip_long, 0x2E974800, 0x15);//4
	match(ip_long, 0x2E977000, 0x15);//4
	match(ip_long, 0x2E978800, 0x15);//4
	match(ip_long, 0x2E97B800, 0x15);//4
	match(ip_long, 0x2E97D800, 0x15);//4
	match(ip_long, 0x2EAE0000, 0x15);//4
	match(ip_long, 0x2EAE1800, 0x15);//4
	match(ip_long, 0x2EAE4800, 0x15);//4
	match(ip_long, 0x2EAEA800, 0x15);//4
	match(ip_long, 0x2EAEB000, 0x15);//4
	match(ip_long, 0x2EAED000, 0x15);//4
	match(ip_long, 0x2EAEE000, 0x15);//4
	match(ip_long, 0x2EAEE800, 0x15);//4
	match(ip_long, 0x2EAF0E00, 0x17);//4
	match(ip_long, 0x2EAF2800, 0x15);//4
	match(ip_long, 0x2EAF6800, 0x15);//4
	match(ip_long, 0x2EAF7000, 0x15);//4
	match(ip_long, 0x2EAFE000, 0x14);//4
	match(ip_long, 0x3E7A7000, 0x15);//6
	match(ip_long, 0x3E7A7800, 0x15);//6
	match(ip_long, 0x3E7AE800, 0x15);//6
	match(ip_long, 0x3EB66800, 0x15);//6
	match(ip_long, 0x3EB69000, 0x15);//6
	match(ip_long, 0x3EB6D000, 0x15);//6
	match(ip_long, 0x3EB6E000, 0x15);//6
	match(ip_long, 0x4D570000, 0x15);//7
	match(ip_long, 0x4D574800, 0x15);//7
	match(ip_long, 0x4D577800, 0x15);//7
	match(ip_long, 0x4D578800, 0x15);//7
	match(ip_long, 0x4D57D800, 0x15);//7
	match(ip_long, 0x4E1F5800, 0x15);//7
	match(ip_long, 0x4E1F7800, 0x15);//7
	match(ip_long, 0x4E1F8800, 0x15);//7
	match(ip_long, 0x4E1F9000, 0x15);//7
	match(ip_long, 0x4E1F9800, 0x15);//7
	match(ip_long, 0x4E1FA200, 0x17);//7
	match(ip_long, 0x4E1FA600, 0x17);//7
	match(ip_long, 0x4E1FD100, 0x18);//7
	match(ip_long, 0x4E1FD600, 0x17);//7
	match(ip_long, 0x4F6EC000, 0x14);//7
	match(ip_long, 0x5044E000, 0x14);//8
	match(ip_long, 0x50EE4000, 0x13);//8
	match(ip_long, 0x50EE6000, 0x13);//8
	match(ip_long, 0x51A13E00, 0x18);//8
	match(ip_long, 0x51A16400, 0x16);//8
	match(ip_long, 0x51A16800, 0x15);//8
	match(ip_long, 0x51A17000, 0x17);//8
	match(ip_long, 0x51A1C000, 0x14);//8
	match(ip_long, 0x51A2D000, 0x15);//8
	match(ip_long, 0x51A30800, 0x15);//8
	match(ip_long, 0x51A3C000, 0x15);//8
	match(ip_long, 0x51A3C800, 0x15);//8
	match(ip_long, 0x51BAE000, 0x14);//8
	match(ip_long, 0x538E2800, 0x15);//8
	match(ip_long, 0x538E3800, 0x15);//8
	match(ip_long, 0x538E7000, 0x15);//8
	match(ip_long, 0x538E7800, 0x15);//8
	match(ip_long, 0x538E8800, 0x15);//8
	match(ip_long, 0x538E9800, 0x15);//8
	match(ip_long, 0x538EA800, 0x15);//8
	match(ip_long, 0x538EB000, 0x15);//8
	match(ip_long, 0x538EB800, 0x15);//8
	match(ip_long, 0x538EC000, 0x15);//8
	match(ip_long, 0x538EC800, 0x15);//8
	match(ip_long, 0x538ED800, 0x15);//8
	match(ip_long, 0x538F2800, 0x15);//8
	match(ip_long, 0x538F6000, 0x15);//8
	match(ip_long, 0x538F8000, 0x15);//8
	match(ip_long, 0x538F8800, 0x15);//8
	match(ip_long, 0x538FA000, 0x15);//8
	match(ip_long, 0x53972000, 0x14);//8
	match(ip_long, 0x53AF8000, 0x14);//8
	match(ip_long, 0x53AF9000, 0x14);//8
	match(ip_long, 0x53AFA000, 0x14);//8
	match(ip_long, 0x53AFB000, 0x14);//8
	match(ip_long, 0x53F24000, 0x13);//8
	match(ip_long, 0x53F27000, 0x14);//8
	match(ip_long, 0x53F32000, 0x15);//8
	match(ip_long, 0x53F36800, 0x15);//8
	match(ip_long, 0x54261000, 0x14);//8
	match(ip_long, 0x54265000, 0x14);//8
	match(ip_long, 0x54266000, 0x14);//8
	match(ip_long, 0x5426A000, 0x14);//8
	match(ip_long, 0x5426D000, 0x14);//8
	match(ip_long, 0x54C9D000, 0x14);//8
	match(ip_long, 0x54CD0000, 0x13);//8
	match(ip_long, 0x54CDA000, 0x13);//8
	match(ip_long, 0x54EA0000, 0x14);//8
	match(ip_long, 0x54EA2000, 0x14);//8
	match(ip_long, 0x54EA7000, 0x14);//8
	match(ip_long, 0x551FE000, 0x14);//8
	match(ip_long, 0x551FF000, 0x14);//8
	match(ip_long, 0x55CA2000, 0x14);//8
	match(ip_long, 0x55CA3000, 0x14);//8
	match(ip_long, 0x55CA6000, 0x14);//8
	match(ip_long, 0x55CA9000, 0x14);//8
	match(ip_long, 0x55CAD000, 0x14);//8
	match(ip_long, 0x55FF0000, 0x14);//8
	match(ip_long, 0x55FFF000, 0x14);//8
	match(ip_long, 0x566F6000, 0x13);//8
	match(ip_long, 0x566FC800, 0x15);//8
	match(ip_long, 0x566FF000, 0x15);//8
	match(ip_long, 0x57636000, 0x13);//8
	match(ip_long, 0x57651000, 0x14);//8
	match(ip_long, 0x57652000, 0x14);//8
	match(ip_long, 0x57654000, 0x14);//8
	match(ip_long, 0x57EF2800, 0x15);//8
	match(ip_long, 0x57EF4800, 0x15);//8
	match(ip_long, 0x57EF5800, 0x15);//8
	match(ip_long, 0x57EFA800, 0x15);//8
	match(ip_long, 0x57EFB000, 0x15);//8
	match(ip_long, 0x57EFC000, 0x15);//8
	match(ip_long, 0x57EFD800, 0x15);//8
	match(ip_long, 0x57EFF000, 0x15);//8
	match(ip_long, 0x5887A000, 0x13);//8
	match(ip_long, 0x59162000, 0x15);//8
	match(ip_long, 0x5916C000, 0x15);//8
	match(ip_long, 0x5916D000, 0x15);//8
	match(ip_long, 0x59C89000, 0x15);//8
	match(ip_long, 0x59C89800, 0x15);//8
	match(ip_long, 0x59C8A000, 0x15);//8
	match(ip_long, 0x59C8D000, 0x15);//8
	match(ip_long, 0x59C8E000, 0x15);//8
	match(ip_long, 0x59CE0000, 0x12);//8
	match(ip_long, 0x5B5A3800, 0x15);//9
	match(ip_long, 0x5B5A4800, 0x15);//9
	match(ip_long, 0x5B5A5800, 0x15);//9
	match(ip_long, 0x5B5A7000, 0x15);//9
	match(ip_long, 0x5B5AA000, 0x14);//9
	match(ip_long, 0x5B5AB000, 0x14);//9
	match(ip_long, 0x5B7BA000, 0x14);//9
	match(ip_long, 0x5B7BB000, 0x14);//9
	match(ip_long, 0x5B7BD000, 0x14);//9
	match(ip_long, 0x5B8E8900, 0x18);//9
	match(ip_long, 0x5B968000, 0x13);//9
	match(ip_long, 0x5B96A000, 0x13);//9
	match(ip_long, 0x5B96C000, 0x13);//9
	match(ip_long, 0x5BBD0000, 0x15);//9
	match(ip_long, 0x5BBD1000, 0x15);//9
	match(ip_long, 0x5BBD1800, 0x15);//9
	match(ip_long, 0x5BBD2000, 0x15);//9
	match(ip_long, 0x5BBD3800, 0x15);//9
	match(ip_long, 0x5BBD4800, 0x15);//9
	match(ip_long, 0x5BBD8800, 0x15);//9
	match(ip_long, 0x5BBDD800, 0x15);//9
	match(ip_long, 0x5BBDF800, 0x15);//9
	match(ip_long, 0x5BC00000, 0x16);//9
	match(ip_long, 0x5BC03800, 0x16);//9
	match(ip_long, 0x5BC04C00, 0x16);//9
	match(ip_long, 0x5BC05800, 0x16);//9
	match(ip_long, 0x5BC07800, 0x16);//9
	match(ip_long, 0x5BC09000, 0x16);//9
	match(ip_long, 0x5BC0A400, 0x16);//9
	match(ip_long, 0x5BC0C400, 0x16);//9
	match(ip_long, 0x5BC0CC00, 0x16);//9
	match(ip_long, 0x5BC0E000, 0x16);//9
	match(ip_long, 0x5BC0E400, 0x16);//9
	match(ip_long, 0x5BC0F800, 0x16);//9
	match(ip_long, 0x5BC10C00, 0x16);//9
	match(ip_long, 0x5BC12800, 0x17);//9
	match(ip_long, 0x5BC13400, 0x16);//9
	match(ip_long, 0x5BC14900, 0x18);//9
	match(ip_long, 0x5BC15400, 0x16);//9
	match(ip_long, 0x5BC15A00, 0x17);//9
	match(ip_long, 0x5BC16000, 0x16);//9
	match(ip_long, 0x5BC17800, 0x16);//9
	match(ip_long, 0x5BC19000, 0x16);//9
	match(ip_long, 0x5BC1A000, 0x16);//9
	match(ip_long, 0x5BC1B800, 0x16);//9
	match(ip_long, 0x5BC1C400, 0x16);//9
	match(ip_long, 0x5BC1D000, 0x16);//9
	match(ip_long, 0x5BC21200, 0x17);//9
	match(ip_long, 0x5BC26A00, 0x17);//9
	match(ip_long, 0x5BC27A00, 0x17);//9
	match(ip_long, 0x5BC28A00, 0x17);//9
	match(ip_long, 0x5BC29000, 0x17);//9
	match(ip_long, 0x5BC29C00, 0x17);//9
	match(ip_long, 0x5BC2BC00, 0x17);//9
	match(ip_long, 0x5BC2C600, 0x17);//9
	match(ip_long, 0x5BC2D200, 0x17);//9
	match(ip_long, 0x5BC2E400, 0x17);//9
	match(ip_long, 0x5BC31A00, 0x17);//9
	match(ip_long, 0x5BC32A00, 0x17);//9
	match(ip_long, 0x5BC32E00, 0x17);//9
	match(ip_long, 0x5BC33800, 0x17);//9
	match(ip_long, 0x5BC35C00, 0x17);//9
	match(ip_long, 0x5BC36C00, 0x17);//9
	match(ip_long, 0x5BC38600, 0x17);//9
	match(ip_long, 0x5BC39E00, 0x17);//9
	match(ip_long, 0x5BC3BE00, 0x17);//9
	match(ip_long, 0x5BC3E800, 0x17);//9
	match(ip_long, 0x5BC3FA00, 0x17);//9
	match(ip_long, 0x5BC40800, 0x16);//9
	match(ip_long, 0x5BC40C00, 0x16);//9
	match(ip_long, 0x5BC41C00, 0x16);//9
	match(ip_long, 0x5BC43000, 0x16);//9
	match(ip_long, 0x5BC43800, 0x16);//9
	match(ip_long, 0x5BC46C00, 0x16);//9
	match(ip_long, 0x5BC4D400, 0x16);//9
	match(ip_long, 0x5BC50C00, 0x16);//9
	match(ip_long, 0x5BC55800, 0x16);//9
	match(ip_long, 0x5BC59400, 0x16);//9
	match(ip_long, 0x5BC59800, 0x16);//9
	match(ip_long, 0x5BC5E000, 0x16);//9
	match(ip_long, 0x5BC60F00, 0x18);//9
	match(ip_long, 0x5BC61000, 0x18);//9
	match(ip_long, 0x5BC61400, 0x18);//9
	match(ip_long, 0x5BC63500, 0x18);//9
	match(ip_long, 0x5BC63700, 0x18);//9
	match(ip_long, 0x5BC63800, 0x18);//9
	match(ip_long, 0x5BC64100, 0x18);//9
	match(ip_long, 0x5BC64A00, 0x18);//9
	match(ip_long, 0x5BC64C00, 0x18);//9
	match(ip_long, 0x5BC65000, 0x18);//9
	match(ip_long, 0x5BC65900, 0x18);//9
	match(ip_long, 0x5BC65E00, 0x18);//9
	match(ip_long, 0x5BC66100, 0x18);//9
	match(ip_long, 0x5BC66400, 0x18);//9
	match(ip_long, 0x5BC66E00, 0x18);//9
	match(ip_long, 0x5BC66F00, 0x18);//9
	match(ip_long, 0x5BC67600, 0x18);//9
	match(ip_long, 0x5BC67900, 0x18);//9
	match(ip_long, 0x5BC69100, 0x18);//9
	match(ip_long, 0x5BC69200, 0x18);//9
	match(ip_long, 0x5BC69600, 0x18);//9
	match(ip_long, 0x5BC6A100, 0x18);//9
	match(ip_long, 0x5BC6B100, 0x18);//9
	match(ip_long, 0x5BC6B300, 0x18);//9
	match(ip_long, 0x5BC6BA00, 0x18);//9
	match(ip_long, 0x5BC6C200, 0x18);//9
	match(ip_long, 0x5BC6D100, 0x18);//9
	match(ip_long, 0x5BC6D900, 0x18);//9
	match(ip_long, 0x5BC6DE00, 0x18);//9
	match(ip_long, 0x5BC6E200, 0x18);//9
	match(ip_long, 0x5BC6E800, 0x18);//9
	match(ip_long, 0x5BC6F500, 0x18);//9
	match(ip_long, 0x5BC6F600, 0x18);//9
	match(ip_long, 0x5BC6F800, 0x18);//9
	match(ip_long, 0x5BC70C00, 0x18);//9
	match(ip_long, 0x5BC71600, 0x18);//9
	match(ip_long, 0x5BC71900, 0x18);//9
	match(ip_long, 0x5BC73000, 0x18);//9
	match(ip_long, 0x5BC73300, 0x18);//9
	match(ip_long, 0x5BC73900, 0x18);//9
	match(ip_long, 0x5BC75900, 0x18);//9
	match(ip_long, 0x5BC75F00, 0x18);//9
	match(ip_long, 0x5BC76100, 0x18);//9
	match(ip_long, 0x5BC76500, 0x18);//9
	match(ip_long, 0x5BC76900, 0x18);//9
	match(ip_long, 0x5BC77500, 0x18);//9
	match(ip_long, 0x5BC77F00, 0x18);//9
	match(ip_long, 0x5BC78400, 0x18);//9
	match(ip_long, 0x5BC78C00, 0x18);//9
	match(ip_long, 0x5BC78D00, 0x18);//9
	match(ip_long, 0x5BC7B000, 0x18);//9
	match(ip_long, 0x5BC7CB00, 0x18);//9
	match(ip_long, 0x5BC7F000, 0x18);//9
	match(ip_long, 0x5BC7F600, 0x18);//9
	match(ip_long, 0x5BC7FA00, 0x18);//9
	match(ip_long, 0x5BC81800, 0x16);//9
	match(ip_long, 0x5BC82000, 0x16);//9
	match(ip_long, 0x5BC82400, 0x16);//9
	match(ip_long, 0x5BC84400, 0x16);//9
	match(ip_long, 0x5BC84C00, 0x16);//9
	match(ip_long, 0x5BC85C00, 0x16);//9
	match(ip_long, 0x5BC86800, 0x16);//9
	match(ip_long, 0x5BC8AC00, 0x16);//9
	match(ip_long, 0x5BC8B800, 0x16);//9
	match(ip_long, 0x5BC8EC00, 0x16);//9
	match(ip_long, 0x5BC91000, 0x16);//9
	match(ip_long, 0x5BC92C00, 0x16);//9
	match(ip_long, 0x5BC95800, 0x16);//9
	match(ip_long, 0x5BC97800, 0x16);//9
	match(ip_long, 0x5BC99800, 0x16);//9
	match(ip_long, 0x5BCA6400, 0x16);//9
	match(ip_long, 0x5BCA7C00, 0x16);//9
	match(ip_long, 0x5BCA9800, 0x16);//9
	match(ip_long, 0x5BCAAC00, 0x16);//9
	match(ip_long, 0x5BCAB000, 0x16);//9
	match(ip_long, 0x5BCAC000, 0x16);//9
	match(ip_long, 0x5BCAE400, 0x16);//9
	match(ip_long, 0x5BCB1000, 0x16);//9
	match(ip_long, 0x5BCB3400, 0x16);//9
	match(ip_long, 0x5BCB6800, 0x18);//9
	match(ip_long, 0x5BCB8400, 0x16);//9
	match(ip_long, 0x5BCB9C00, 0x16);//9
	match(ip_long, 0x5BCBD800, 0x16);//9
	match(ip_long, 0x5BCBDC00, 0x16);//9
	match(ip_long, 0x5BCBF400, 0x16);//9
	match(ip_long, 0x5BCBF800, 0x16);//9
	match(ip_long, 0x5BCC5800, 0x16);//9
	match(ip_long, 0x5BCC8C00, 0x16);//9
	match(ip_long, 0x5BCC9800, 0x16);//9
	match(ip_long, 0x5BCCA000, 0x16);//9
	match(ip_long, 0x5BCCCC00, 0x16);//9
	match(ip_long, 0x5BCD1400, 0x16);//9
	match(ip_long, 0x5BCD4800, 0x16);//9
	match(ip_long, 0x5BCD5800, 0x16);//9
	match(ip_long, 0x5BCDE400, 0x16);//9
	match(ip_long, 0x5BCDF400, 0x16);//9
	match(ip_long, 0x5BCE0600, 0x17);//9
	match(ip_long, 0x5BCE1A00, 0x17);//9
	match(ip_long, 0x5BCE2600, 0x17);//9
	match(ip_long, 0x5BCE4000, 0x17);//9
	match(ip_long, 0x5BCE5600, 0x17);//9
	match(ip_long, 0x5BCE5A00, 0x18);//9
	match(ip_long, 0x5BCE6000, 0x17);//9
	match(ip_long, 0x5BCE6C00, 0x17);//9
	match(ip_long, 0x5BCE7200, 0x17);//9
	match(ip_long, 0x5BCE9A00, 0x17);//9
	match(ip_long, 0x5BCEAC00, 0x17);//9
	match(ip_long, 0x5BCEB200, 0x17);//9
	match(ip_long, 0x5BCEB400, 0x17);//9
	match(ip_long, 0x5BCED200, 0x17);//9
	match(ip_long, 0x5BCEF400, 0x17);//9
	match(ip_long, 0x5BCF0A00, 0x17);//9
	match(ip_long, 0x5BCF0E00, 0x17);//9
	match(ip_long, 0x5BCF3000, 0x17);//9
	match(ip_long, 0x5BCF3400, 0x17);//9
	match(ip_long, 0x5BCF4000, 0x17);//9
	match(ip_long, 0x5BCF4400, 0x17);//9
	match(ip_long, 0x5BCF7E00, 0x17);//9
	match(ip_long, 0x5BCF9400, 0x17);//9
	match(ip_long, 0x5BCF9C00, 0x17);//9
	match(ip_long, 0x5BCFA600, 0x17);//9
	match(ip_long, 0x5BCFA800, 0x17);//9
	match(ip_long, 0x5BCFB800, 0x17);//9
	match(ip_long, 0x5BCFBA00, 0x17);//9
	match(ip_long, 0x5BCFC800, 0x17);//9
	match(ip_long, 0x5BCFCA00, 0x17);//9
	match(ip_long, 0x5BCFF200, 0x17);//9
	match(ip_long, 0x5BD00A00, 0x18);//9
	match(ip_long, 0x5BD02000, 0x18);//9
	match(ip_long, 0x5BD02C00, 0x18);//9
	match(ip_long, 0x5BD03200, 0x18);//9
	match(ip_long, 0x5BD03700, 0x18);//9
	match(ip_long, 0x5BD04800, 0x18);//9
	match(ip_long, 0x5BD04E00, 0x18);//9
	match(ip_long, 0x5BD05D00, 0x18);//9
	match(ip_long, 0x5BD06A00, 0x18);//9
	match(ip_long, 0x5BD08500, 0x18);//9
	match(ip_long, 0x5BD08700, 0x18);//9
	match(ip_long, 0x5BD09600, 0x18);//9
	match(ip_long, 0x5BD0B600, 0x18);//9
	match(ip_long, 0x5BD0BA00, 0x18);//9
	match(ip_long, 0x5BD0BD00, 0x18);//9
	match(ip_long, 0x5BD0BE00, 0x18);//9
	match(ip_long, 0x5BD0F700, 0x18);//9
	match(ip_long, 0x5BD0FA00, 0x18);//9
	match(ip_long, 0x5BD10400, 0x18);//9
	match(ip_long, 0x5BD11400, 0x18);//9
	match(ip_long, 0x5BD11B00, 0x18);//9
	match(ip_long, 0x5BD13800, 0x18);//9
	match(ip_long, 0x5BD15D00, 0x18);//9
	match(ip_long, 0x5BD15F00, 0x18);//9
	match(ip_long, 0x5BD17400, 0x18);//9
	match(ip_long, 0x5BD18D00, 0x18);//9
	match(ip_long, 0x5BD19800, 0x18);//9
	match(ip_long, 0x5BD19900, 0x18);//9
	match(ip_long, 0x5BD19B00, 0x18);//9
	match(ip_long, 0x5BD1B100, 0x18);//9
	match(ip_long, 0x5BD1B400, 0x18);//9
	match(ip_long, 0x5BD1C700, 0x18);//9
	match(ip_long, 0x5BD1DD00, 0x18);//9
	match(ip_long, 0x5BD1DE00, 0x18);//9
	match(ip_long, 0x5BD20C00, 0x16);//9
	match(ip_long, 0x5BD23000, 0x16);//9
	match(ip_long, 0x5BD28000, 0x16);//9
	match(ip_long, 0x5BD2D000, 0x16);//9
	match(ip_long, 0x5BD2EC00, 0x16);//9
	match(ip_long, 0x5BD2F000, 0x16);//9
	match(ip_long, 0x5BD2F400, 0x16);//9
	match(ip_long, 0x5BD35400, 0x16);//9
	match(ip_long, 0x5BD36400, 0x16);//9
	match(ip_long, 0x5BD3DC00, 0x16);//9
	match(ip_long, 0x5BD3FC00, 0x16);//9
	match(ip_long, 0x5BD40200, 0x18);//9
	match(ip_long, 0x5BD40500, 0x18);//9
	match(ip_long, 0x5BD40900, 0x18);//9
	match(ip_long, 0x5BD41900, 0x18);//9
	match(ip_long, 0x5BD41E00, 0x18);//9
	match(ip_long, 0x5BD42100, 0x18);//9
	match(ip_long, 0x5BD45400, 0x18);//9
	match(ip_long, 0x5BD45600, 0x18);//9
	match(ip_long, 0x5BD46400, 0x18);//9
	match(ip_long, 0x5BD47F00, 0x18);//9
	match(ip_long, 0x5BD49B00, 0x18);//9
	match(ip_long, 0x5BD4A500, 0x18);//9
	match(ip_long, 0x5BD4A900, 0x18);//9
	match(ip_long, 0x5BD4AA00, 0x18);//9
	match(ip_long, 0x5BD4AC00, 0x18);//9
	match(ip_long, 0x5BD4DF00, 0x18);//9
	match(ip_long, 0x5BD4E700, 0x18);//9
	match(ip_long, 0x5BD4F200, 0x18);//9
	match(ip_long, 0x5BD52600, 0x18);//9
	match(ip_long, 0x5BD53A00, 0x18);//9
	match(ip_long, 0x5BD54000, 0x18);//9
	match(ip_long, 0x5BD54700, 0x18);//9
	match(ip_long, 0x5BD55800, 0x18);//9
	match(ip_long, 0x5BD56000, 0x18);//9
	match(ip_long, 0x5BD56B00, 0x18);//9
	match(ip_long, 0x5BD56C00, 0x18);//9
	match(ip_long, 0x5BD57600, 0x18);//9
	match(ip_long, 0x5BD57B00, 0x18);//9
	match(ip_long, 0x5BD57C00, 0x18);//9
	match(ip_long, 0x5BD58900, 0x18);//9
	match(ip_long, 0x5BD59C00, 0x18);//9
	match(ip_long, 0x5BD5A200, 0x18);//9
	match(ip_long, 0x5BD5AA00, 0x18);//9
	match(ip_long, 0x5BD5C100, 0x18);//9
	match(ip_long, 0x5BD5CE00, 0x18);//9
	match(ip_long, 0x5BD5E200, 0x18);//9
	match(ip_long, 0x5BD5ED00, 0x18);//9
	match(ip_long, 0x5BD5EE00, 0x18);//9
	match(ip_long, 0x5BD5EF00, 0x18);//9
	match(ip_long, 0x5BD5FF00, 0x18);//9
	match(ip_long, 0x5BD60000, 0x16);//9
	match(ip_long, 0x5BD61800, 0x16);//9
	match(ip_long, 0x5BD62400, 0x16);//9
	match(ip_long, 0x5BD63400, 0x16);//9
	match(ip_long, 0x5BD6EC00, 0x16);//9
	match(ip_long, 0x5BD70000, 0x16);//9
	match(ip_long, 0x5BD72000, 0x16);//9
	match(ip_long, 0x5BD72C00, 0x16);//9
	match(ip_long, 0x5BD75000, 0x16);//9
	match(ip_long, 0x5BD76800, 0x16);//9
	match(ip_long, 0x5BD7E400, 0x16);//9
	match(ip_long, 0x5BD7EC00, 0x16);//9
	match(ip_long, 0x5BD80500, 0x18);//9
	match(ip_long, 0x5BD81000, 0x18);//9
	match(ip_long, 0x5BD81900, 0x18);//9
	match(ip_long, 0x5BD81E00, 0x18);//9
	match(ip_long, 0x5BD83300, 0x18);//9
	match(ip_long, 0x5BD84000, 0x18);//9
	match(ip_long, 0x5BD86300, 0x18);//9
	match(ip_long, 0x5BD87300, 0x18);//9
	match(ip_long, 0x5BD87C00, 0x18);//9
	match(ip_long, 0x5BD87D00, 0x18);//9
	match(ip_long, 0x5BD88600, 0x18);//9
	match(ip_long, 0x5BD89500, 0x18);//9
	match(ip_long, 0x5BD8A000, 0x18);//9
	match(ip_long, 0x5BD8BF00, 0x18);//9
	match(ip_long, 0x5BD8C000, 0x18);//9
	match(ip_long, 0x5BD8C200, 0x18);//9
	match(ip_long, 0x5BD8CA00, 0x18);//9
	match(ip_long, 0x5BD8CC00, 0x18);//9
	match(ip_long, 0x5BD8D500, 0x18);//9
	match(ip_long, 0x5BD8D600, 0x18);//9
	match(ip_long, 0x5BD8E000, 0x18);//9
	match(ip_long, 0x5BD8EF00, 0x18);//9
	match(ip_long, 0x5BD8FE00, 0x18);//9
	match(ip_long, 0x5BD90000, 0x17);//9
	match(ip_long, 0x5BD91200, 0x17);//9
	match(ip_long, 0x5BD91600, 0x17);//9
	match(ip_long, 0x5BD91800, 0x17);//9
	match(ip_long, 0x5BD92800, 0x17);//9
	match(ip_long, 0x5BD93000, 0x17);//9
	match(ip_long, 0x5BD96200, 0x17);//9
	match(ip_long, 0x5BD96800, 0x17);//9
	match(ip_long, 0x5BD97200, 0x17);//9
	match(ip_long, 0x5BD98400, 0x18);//9
	match(ip_long, 0x5BD98E00, 0x18);//9
	match(ip_long, 0x5BD99600, 0x18);//9
	match(ip_long, 0x5BD99800, 0x18);//9
	match(ip_long, 0x5BD99E00, 0x18);//9
	match(ip_long, 0x5BD9A100, 0x18);//9
	match(ip_long, 0x5BD9A300, 0x18);//9
	match(ip_long, 0x5BD9AB00, 0x18);//9
	match(ip_long, 0x5BD9B600, 0x18);//9
	match(ip_long, 0x5BD9C600, 0x18);//9
	match(ip_long, 0x5BD9CC00, 0x18);//9
	match(ip_long, 0x5BD9D000, 0x18);//9
	match(ip_long, 0x5BD9D900, 0x18);//9
	match(ip_long, 0x5BD9DA00, 0x18);//9
	match(ip_long, 0x5BD9DD00, 0x18);//9
	match(ip_long, 0x5BD9E000, 0x18);//9
	match(ip_long, 0x5BD9E400, 0x18);//9
	match(ip_long, 0x5BD9F200, 0x18);//9
	match(ip_long, 0x5BDA3C00, 0x16);//9
	match(ip_long, 0x5BDA4400, 0x16);//9
	match(ip_long, 0x5BDA4C00, 0x16);//9
	match(ip_long, 0x5BDA9C00, 0x16);//9
	match(ip_long, 0x5BDAA400, 0x16);//9
	match(ip_long, 0x5BDAC400, 0x16);//9
	match(ip_long, 0x5BDAC800, 0x16);//9
	match(ip_long, 0x5BDAD000, 0x16);//9
	match(ip_long, 0x5BDAD800, 0x16);//9
	match(ip_long, 0x5BDAF000, 0x16);//9
	match(ip_long, 0x5BDB0000, 0x16);//9
	match(ip_long, 0x5BDB6800, 0x16);//9
	match(ip_long, 0x5BDB7000, 0x16);//9
	match(ip_long, 0x5BDB7800, 0x16);//9
	match(ip_long, 0x5BDB8000, 0x16);//9
	match(ip_long, 0x5BDBB800, 0x16);//9
	match(ip_long, 0x5BDBD000, 0x16);//9
	match(ip_long, 0x5BDC0000, 0x18);//9
	match(ip_long, 0x5BDC0A00, 0x18);//9
	match(ip_long, 0x5BDC1100, 0x18);//9
	match(ip_long, 0x5BDC1200, 0x18);//9
	match(ip_long, 0x5BDC2000, 0x18);//9
	match(ip_long, 0x5BDC2700, 0x18);//9
	match(ip_long, 0x5BDC2C00, 0x18);//9
	match(ip_long, 0x5BDC3600, 0x18);//9
	match(ip_long, 0x5BDC4900, 0x18);//9
	match(ip_long, 0x5BDC6100, 0x18);//9
	match(ip_long, 0x5BDC6700, 0x18);//9
	match(ip_long, 0x5BDC6900, 0x18);//9
	match(ip_long, 0x5BDCA400, 0x18);//9
	match(ip_long, 0x5BDCB100, 0x18);//9
	match(ip_long, 0x5BDCCD00, 0x18);//9
	match(ip_long, 0x5BDCDE00, 0x18);//9
	match(ip_long, 0x5BDCE100, 0x18);//9
	match(ip_long, 0x5BDCEE00, 0x18);//9
	match(ip_long, 0x5BDD1A00, 0x17);//9
	match(ip_long, 0x5BDD2C00, 0x17);//9
	match(ip_long, 0x5BDD5800, 0x17);//9
	match(ip_long, 0x5BDD7200, 0x17);//9
	match(ip_long, 0x5BDD7A00, 0x17);//9
	match(ip_long, 0x5BDD7E00, 0x17);//9
	match(ip_long, 0x5BDD9000, 0x17);//9
	match(ip_long, 0x5BDD9E00, 0x17);//9
	match(ip_long, 0x5BDDAC00, 0x17);//9
	match(ip_long, 0x5BDDD600, 0x17);//9
	match(ip_long, 0x5BDE1800, 0x16);//9
	match(ip_long, 0x5BDE3800, 0x16);//9
	match(ip_long, 0x5BDE4400, 0x16);//9
	match(ip_long, 0x5BDE4800, 0x16);//9
	match(ip_long, 0x5BDE6400, 0x16);//9
	match(ip_long, 0x5BDE6C00, 0x16);//9
	match(ip_long, 0x5BDE7400, 0x16);//9
	match(ip_long, 0x5BDE7C00, 0x16);//9
	match(ip_long, 0x5BDE8C00, 0x16);//9
	match(ip_long, 0x5BDE9000, 0x16);//9
	match(ip_long, 0x5BDE9400, 0x16);//9
	match(ip_long, 0x5BDEA000, 0x16);//9
	match(ip_long, 0x5BDEB800, 0x16);//9
	match(ip_long, 0x5BDEC000, 0x16);//9
	match(ip_long, 0x5BDED400, 0x16);//9
	match(ip_long, 0x5BDEE000, 0x16);//9
	match(ip_long, 0x5BDF0300, 0x18);//9
	match(ip_long, 0x5BDF0400, 0x18);//9
	match(ip_long, 0x5BDF0600, 0x18);//9
	match(ip_long, 0x5BDF0D00, 0x18);//9
	match(ip_long, 0x5BDF0E00, 0x18);//9
	match(ip_long, 0x5BDF1700, 0x18);//9
	match(ip_long, 0x5BDF1F00, 0x18);//9
	match(ip_long, 0x5BDF2100, 0x18);//9
	match(ip_long, 0x5BDF3400, 0x18);//9
	match(ip_long, 0x5BDF3700, 0x18);//9
	match(ip_long, 0x5BDF3900, 0x18);//9
	match(ip_long, 0x5BDF4000, 0x18);//9
	match(ip_long, 0x5BDF4400, 0x18);//9
	match(ip_long, 0x5BDF4800, 0x18);//9
	match(ip_long, 0x5BDF4E00, 0x18);//9
	match(ip_long, 0x5BDF5100, 0x18);//9
	match(ip_long, 0x5BDF5300, 0x18);//9
	match(ip_long, 0x5BDF7700, 0x18);//9
	match(ip_long, 0x5BDF8200, 0x18);//9
	match(ip_long, 0x5BDF8600, 0x18);//9
	match(ip_long, 0x5BDF8700, 0x18);//9
	match(ip_long, 0x5BDF8E00, 0x18);//9
	match(ip_long, 0x5BDFA000, 0x18);//9
	match(ip_long, 0x5BDFA700, 0x18);//9
	match(ip_long, 0x5BDFA800, 0x18);//9
	match(ip_long, 0x5BDFAB00, 0x18);//9
	match(ip_long, 0x5BDFAF00, 0x18);//9
	match(ip_long, 0x5BDFB800, 0x18);//9
	match(ip_long, 0x5BDFC400, 0x18);//9
	match(ip_long, 0x5BDFD400, 0x18);//9
	match(ip_long, 0x5BDFDD00, 0x18);//9
	match(ip_long, 0x5BDFE100, 0x18);//9
	match(ip_long, 0x5BDFF100, 0x18);//9
	match(ip_long, 0x5BDFFA00, 0x18);//9
	match(ip_long, 0x5BE01C00, 0x17);//9
	match(ip_long, 0x5BE02600, 0x17);//9
	match(ip_long, 0x5BE02E00, 0x17);//9
	match(ip_long, 0x5BE03800, 0x17);//9
	match(ip_long, 0x5BE03C00, 0x17);//9
	match(ip_long, 0x5BE06800, 0x17);//9
	match(ip_long, 0x5BE07400, 0x17);//9
	match(ip_long, 0x5BE07600, 0x17);//9
	match(ip_long, 0x5BE07800, 0x17);//9
	match(ip_long, 0x5BE08000, 0x17);//9
	match(ip_long, 0x5BE08E00, 0x17);//9
	match(ip_long, 0x5BE09000, 0x17);//9
	match(ip_long, 0x5BE09200, 0x17);//9
	match(ip_long, 0x5BE0B400, 0x17);//9
	match(ip_long, 0x5BE0B800, 0x17);//9
	match(ip_long, 0x5BE0C000, 0x17);//9
	match(ip_long, 0x5BE0C400, 0x17);//9
	match(ip_long, 0x5BE0C600, 0x17);//9
	match(ip_long, 0x5BE0D600, 0x17);//9
	match(ip_long, 0x5BE0D800, 0x17);//9
	match(ip_long, 0x5BE0DC00, 0x17);//9
	match(ip_long, 0x5BE0E000, 0x17);//9
	match(ip_long, 0x5BE0EC00, 0x17);//9
	match(ip_long, 0x5BE10800, 0x16);//9
	match(ip_long, 0x5BE11C00, 0x16);//9
	match(ip_long, 0x5BE14000, 0x16);//9
	match(ip_long, 0x5BE18400, 0x16);//9
	match(ip_long, 0x5BE19C00, 0x16);//9
	match(ip_long, 0x5BE1B000, 0x16);//9
	match(ip_long, 0x5BE1B800, 0x16);//9
	match(ip_long, 0x5BE1BC00, 0x16);//9
	match(ip_long, 0x5BE1F000, 0x16);//9
	match(ip_long, 0x5BE20600, 0x17);//9
	match(ip_long, 0x5BE21000, 0x17);//9
	match(ip_long, 0x5BE21600, 0x17);//9
	match(ip_long, 0x5BE21A00, 0x17);//9
	match(ip_long, 0x5BE22600, 0x17);//9
	match(ip_long, 0x5BE22800, 0x17);//9
	match(ip_long, 0x5BE23200, 0x17);//9
	match(ip_long, 0x5BE24400, 0x16);//9
	match(ip_long, 0x5BE26400, 0x16);//9
	match(ip_long, 0x5BE26E00, 0x17);//9
	match(ip_long, 0x5BE27500, 0x18);//9
	match(ip_long, 0x5BE29200, 0x18);//9
	match(ip_long, 0x5BE2C200, 0x17);//9
	match(ip_long, 0x5BE2C400, 0x16);//9
	match(ip_long, 0x5BE2E400, 0x16);//9
	match(ip_long, 0x5BE2E800, 0x17);//9
	match(ip_long, 0x5BE2EC00, 0x16);//9
	match(ip_long, 0x5BE2FB00, 0x18);//9
	match(ip_long, 0x5BE30000, 0x16);//9
	match(ip_long, 0x5BE31500, 0x18);//9
	match(ip_long, 0x5BE32400, 0x16);//9
	match(ip_long, 0x5BE32800, 0x17);//9
	match(ip_long, 0x5BE33800, 0x16);//9
	match(ip_long, 0x5BE33C00, 0x17);//9
	match(ip_long, 0x5BE33F00, 0x18);//9
	match(ip_long, 0x5BE34000, 0x16);//9
	match(ip_long, 0x5BE34C00, 0x18);//9
	match(ip_long, 0x5BE34D00, 0x18);//9
	match(ip_long, 0x5BE35000, 0x16);//9
	match(ip_long, 0x5BE35800, 0x17);//9
	match(ip_long, 0x5BE36600, 0x17);//9
	match(ip_long, 0x5BE36800, 0x16);//9
	match(ip_long, 0x5BE37300, 0x18);//9
	match(ip_long, 0x5BE37400, 0x16);//9
	match(ip_long, 0x5BE37800, 0x18);//9
	match(ip_long, 0x5BE37A00, 0x17);//9
	match(ip_long, 0x5BE38400, 0x17);//9
	match(ip_long, 0x5BE39C00, 0x16);//9
	match(ip_long, 0x5BE3A700, 0x18);//9
	match(ip_long, 0x5BE3B000, 0x18);//9
	match(ip_long, 0x5BE3C400, 0x17);//9
	match(ip_long, 0x5BE3C700, 0x18);//9
	match(ip_long, 0x5BE3C800, 0x16);//9
	match(ip_long, 0x5BE3D400, 0x16);//9
	match(ip_long, 0x5BE3D800, 0x16);//9
	match(ip_long, 0x5BE40800, 0x17);//9
	match(ip_long, 0x5BE40B00, 0x18);//9
	match(ip_long, 0x5BE41C00, 0x18);//9
	match(ip_long, 0x5BE42000, 0x16);//9
	match(ip_long, 0x5BE42A00, 0x17);//9
	match(ip_long, 0x5BE43800, 0x18);//9
	match(ip_long, 0x5BE45000, 0x16);//9
	match(ip_long, 0x5BE45800, 0x18);//9
	match(ip_long, 0x5BE45900, 0x18);//9
	match(ip_long, 0x5BE45C00, 0x16);//9
	match(ip_long, 0x5BE47000, 0x18);//9
	match(ip_long, 0x5BE47100, 0x18);//9
	match(ip_long, 0x5BE47D00, 0x18);//9
	match(ip_long, 0x5BE48800, 0x16);//9
	match(ip_long, 0x5BE49C00, 0x16);//9
	match(ip_long, 0x5BE4B900, 0x18);//9
	match(ip_long, 0x5BE4C400, 0x16);//9
	match(ip_long, 0x5BE4CC00, 0x18);//9
	match(ip_long, 0x5BE4ED00, 0x18);//9
	match(ip_long, 0x5BE51600, 0x18);//9
	match(ip_long, 0x5BE51A00, 0x17);//9
	match(ip_long, 0x5BE52800, 0x16);//9
	match(ip_long, 0x5BE54400, 0x16);//9
	match(ip_long, 0x5BE55200, 0x17);//9
	match(ip_long, 0x5BE55400, 0x16);//9
	match(ip_long, 0x5BE55800, 0x17);//9
	match(ip_long, 0x5BE56A00, 0x17);//9
	match(ip_long, 0x5BE5C100, 0x18);//9
	match(ip_long, 0x5BE5D400, 0x17);//9
	match(ip_long, 0x5BE5EE00, 0x18);//9
	match(ip_long, 0x5BE5F900, 0x18);//9
	match(ip_long, 0x5BE5FA00, 0x17);//9
	match(ip_long, 0x5BE60800, 0x17);//9
	match(ip_long, 0x5BE61100, 0x18);//9
	match(ip_long, 0x5BE61800, 0x18);//9
	match(ip_long, 0x5BE62400, 0x17);//9
	match(ip_long, 0x5BE62A00, 0x17);//9
	match(ip_long, 0x5BE63A00, 0x17);//9
	match(ip_long, 0x5BE64A00, 0x18);//9
	match(ip_long, 0x5BE64B00, 0x18);//9
	match(ip_long, 0x5BE64C00, 0x17);//9
	match(ip_long, 0x5BE65600, 0x17);//9
	match(ip_long, 0x5BE65800, 0x17);//9
	match(ip_long, 0x5BE66200, 0x17);//9
	match(ip_long, 0x5BE67000, 0x16);//9
	match(ip_long, 0x5BE67400, 0x16);//9
	match(ip_long, 0x5BE67800, 0x18);//9
	match(ip_long, 0x5BE67A00, 0x18);//9
	match(ip_long, 0x5BE69400, 0x18);//9
	match(ip_long, 0x5BE69C00, 0x18);//9
	match(ip_long, 0x5BE69D00, 0x18);//9
	match(ip_long, 0x5BE69F00, 0x18);//9
	match(ip_long, 0x5BE6A200, 0x17);//9
	match(ip_long, 0x5BE6A400, 0x16);//9
	match(ip_long, 0x5BE6B400, 0x18);//9
	match(ip_long, 0x5BE6C800, 0x16);//9
	match(ip_long, 0x5BE6CC00, 0x17);//9
	match(ip_long, 0x5BE6DD00, 0x18);//9
	match(ip_long, 0x5BE6DE00, 0x17);//9
	match(ip_long, 0x5BE6E900, 0x18);//9
	match(ip_long, 0x5BE70200, 0x18);//9
	match(ip_long, 0x5BE70900, 0x18);//9
	match(ip_long, 0x5BE70C00, 0x16);//9
	match(ip_long, 0x5BE71200, 0x18);//9
	match(ip_long, 0x5BE71300, 0x18);//9
	match(ip_long, 0x5BE71400, 0x17);//9
	match(ip_long, 0x5BE71700, 0x18);//9
	match(ip_long, 0x5BE71800, 0x16);//9
	match(ip_long, 0x5BE72000, 0x17);//9
	match(ip_long, 0x5BE72400, 0x16);//9
	match(ip_long, 0x5BE72C00, 0x17);//9
	match(ip_long, 0x5BE73400, 0x17);//9
	match(ip_long, 0x5BE73C00, 0x17);//9
	match(ip_long, 0x5BE74600, 0x17);//9
	match(ip_long, 0x5BE74800, 0x16);//9
	match(ip_long, 0x5BE75000, 0x16);//9
	match(ip_long, 0x5BE75C00, 0x17);//9
	match(ip_long, 0x5BE76400, 0x16);//9
	match(ip_long, 0x5BE76800, 0x16);//9
	match(ip_long, 0x5BE76E00, 0x17);//9
	match(ip_long, 0x5BE77400, 0x17);//9
	match(ip_long, 0x5BE77600, 0x17);//9
	match(ip_long, 0x5BE77800, 0x16);//9
	match(ip_long, 0x5BE77C00, 0x18);//9
	match(ip_long, 0x5BE77D00, 0x18);//9
	match(ip_long, 0x5BE78C00, 0x18);//9
	match(ip_long, 0x5BE79800, 0x18);//9
	match(ip_long, 0x5BE79D00, 0x18);//9
	match(ip_long, 0x5BE7A800, 0x17);//9
	match(ip_long, 0x5BE7B200, 0x18);//9
	match(ip_long, 0x5BE7CD00, 0x18);//9
	match(ip_long, 0x5BE7DD00, 0x18);//9
	match(ip_long, 0x5BE7E600, 0x17);//9
	match(ip_long, 0x5BE7F100, 0x18);//9
	match(ip_long, 0x5BE7F200, 0x18);//9
	match(ip_long, 0x5BE7F400, 0x16);//9
	match(ip_long, 0x5BE7F800, 0x16);//9
	match(ip_long, 0x5BE80400, 0x17);//9
	match(ip_long, 0x5BE81B00, 0x18);//9
	match(ip_long, 0x5BE82600, 0x18);//9
	match(ip_long, 0x5BE82C00, 0x17);//9
	match(ip_long, 0x5BE82E00, 0x17);//9
	match(ip_long, 0x5BE83000, 0x16);//9
	match(ip_long, 0x5BE83400, 0x18);//9
	match(ip_long, 0x5BE83500, 0x18);//9
	match(ip_long, 0x5BE83A00, 0x18);//9
	match(ip_long, 0x5BE83E00, 0x17);//9
	match(ip_long, 0x5BE85A00, 0x17);//9
	match(ip_long, 0x5BE86600, 0x18);//9
	match(ip_long, 0x5BE87000, 0x18);//9
	match(ip_long, 0x5BE88C00, 0x16);//9
	match(ip_long, 0x5BE8A000, 0x17);//9
	match(ip_long, 0x5BE8A400, 0x16);//9
	match(ip_long, 0x5BE8AF00, 0x18);//9
	match(ip_long, 0x5BE8B000, 0x18);//9
	match(ip_long, 0x5BE8B700, 0x18);//9
	match(ip_long, 0x5BE8BE00, 0x17);//9
	match(ip_long, 0x5BE8C000, 0x16);//9
	match(ip_long, 0x5BE8F800, 0x16);//9
	match(ip_long, 0x5BE91200, 0x18);//9
	match(ip_long, 0x5BE91300, 0x18);//9
	match(ip_long, 0x5BE91900, 0x18);//9
	match(ip_long, 0x5BE92200, 0x18);//9
	match(ip_long, 0x5BE93C00, 0x18);//9
	match(ip_long, 0x5BE94500, 0x18);//9
	match(ip_long, 0x5BE94600, 0x17);//9
	match(ip_long, 0x5BE94800, 0x16);//9
	match(ip_long, 0x5BE94C00, 0x16);//9
	match(ip_long, 0x5BE96800, 0x18);//9
	match(ip_long, 0x5BE96B00, 0x18);//9
	match(ip_long, 0x5BE97000, 0x16);//9
	match(ip_long, 0x5BE98800, 0x16);//9
	match(ip_long, 0x5BE99C00, 0x16);//9
	match(ip_long, 0x5BE9A000, 0x17);//9
	match(ip_long, 0x5BE9A200, 0x18);//9
	match(ip_long, 0x5BE9B800, 0x16);//9
	match(ip_long, 0x5BE9C400, 0x16);//9
	match(ip_long, 0x5BE9CC00, 0x17);//9
	match(ip_long, 0x5BE9E400, 0x17);//9
	match(ip_long, 0x5BE9E800, 0x16);//9
	match(ip_long, 0x5BE9EC00, 0x17);//9
	match(ip_long, 0x5BE9FA00, 0x17);//9
	match(ip_long, 0x5BEA0800, 0x18);//9
	match(ip_long, 0x5BEA0C00, 0x16);//9
	match(ip_long, 0x5BEA2C00, 0x17);//9
	match(ip_long, 0x5BEA3100, 0x18);//9
	match(ip_long, 0x5BEA4200, 0x17);//9
	match(ip_long, 0x5BEA6400, 0x16);//9
	match(ip_long, 0x5BEA7000, 0x16);//9
	match(ip_long, 0x5BEA7C00, 0x16);//9
	match(ip_long, 0x5BEA8000, 0x16);//9
	match(ip_long, 0x5BEA8E00, 0x17);//9
	match(ip_long, 0x5BEA9000, 0x18);//9
	match(ip_long, 0x5BEA9200, 0x18);//9
	match(ip_long, 0x5BEAB000, 0x18);//9
	match(ip_long, 0x5BEABA00, 0x17);//9
	match(ip_long, 0x5BEACF00, 0x18);//9
	match(ip_long, 0x5BEAD900, 0x18);//9
	match(ip_long, 0x5BEAE800, 0x18);//9
	match(ip_long, 0x5BEAF500, 0x18);//9
	match(ip_long, 0x5BEAF600, 0x17);//9
	match(ip_long, 0x5BEAFC00, 0x17);//9
	match(ip_long, 0x5BEB0000, 0x17);//9
	match(ip_long, 0x5BEB1000, 0x16);//9
	match(ip_long, 0x5BEB1400, 0x16);//9
	match(ip_long, 0x5BEB1800, 0x17);//9
	match(ip_long, 0x5BEB7C00, 0x17);//9
	match(ip_long, 0x5BEB7E00, 0x18);//9
	match(ip_long, 0x5BEB9500, 0x18);//9
	match(ip_long, 0x5BEB9800, 0x16);//9
	match(ip_long, 0x5BEBA000, 0x16);//9
	match(ip_long, 0x5BEBC000, 0x16);//9
	match(ip_long, 0x5BEBCA00, 0x18);//9
	match(ip_long, 0x5BEBCC00, 0x16);//9
	match(ip_long, 0x5BEBD800, 0x16);//9
	match(ip_long, 0x5BEBDE00, 0x17);//9
	match(ip_long, 0x5BEBE400, 0x17);//9
	match(ip_long, 0x5BEBE600, 0x18);//9
	match(ip_long, 0x5BEBE700, 0x18);//9
	match(ip_long, 0x5BEBEE00, 0x17);//9
	match(ip_long, 0x5BEBFC00, 0x16);//9
	match(ip_long, 0x5BEC0000, 0x18);//9
	match(ip_long, 0x5BEC0400, 0x16);//9
	match(ip_long, 0x5BEC0800, 0x17);//9
	match(ip_long, 0x5BEC0D00, 0x18);//9
	match(ip_long, 0x5BEC1400, 0x17);//9
	match(ip_long, 0x5BEC2000, 0x16);//9
	match(ip_long, 0x5BEC3400, 0x16);//9
	match(ip_long, 0x5BEC3900, 0x18);//9
	match(ip_long, 0x5BEC4800, 0x17);//9
	match(ip_long, 0x5BEC4A00, 0x17);//9
	match(ip_long, 0x5BEC5400, 0x16);//9
	match(ip_long, 0x5BEC6900, 0x18);//9
	match(ip_long, 0x5BEC7D00, 0x18);//9
	match(ip_long, 0x5BEC8000, 0x16);//9
	match(ip_long, 0x5BEC8400, 0x17);//9
	match(ip_long, 0x5BEC8900, 0x18);//9
	match(ip_long, 0x5BECA300, 0x18);//9
	match(ip_long, 0x5BECAC00, 0x16);//9
	match(ip_long, 0x5BECE500, 0x18);//9
	match(ip_long, 0x5BECE800, 0x18);//9
	match(ip_long, 0x5BECE900, 0x18);//9
	match(ip_long, 0x5BED1200, 0x17);//9
	match(ip_long, 0x5BED2400, 0x18);//9
	match(ip_long, 0x5BED3400, 0x18);//9
	match(ip_long, 0x5BED3C00, 0x16);//9
	match(ip_long, 0x5BED4400, 0x16);//9
	match(ip_long, 0x5BED4800, 0x17);//9
	match(ip_long, 0x5BED4D00, 0x18);//9
	match(ip_long, 0x5BED4F00, 0x18);//9
	match(ip_long, 0x5BED5000, 0x17);//9
	match(ip_long, 0x5BED5400, 0x17);//9
	match(ip_long, 0x5BED5600, 0x18);//9
	match(ip_long, 0x5BED7000, 0x17);//9
	match(ip_long, 0x5BED7600, 0x18);//9
	match(ip_long, 0x5BED8800, 0x17);//9
	match(ip_long, 0x5BED8A00, 0x17);//9
	match(ip_long, 0x5BED9500, 0x18);//9
	match(ip_long, 0x5BED9A00, 0x17);//9
	match(ip_long, 0x5BED9C00, 0x16);//9
	match(ip_long, 0x5BEDA000, 0x17);//9
	match(ip_long, 0x5BEDAB00, 0x18);//9
	match(ip_long, 0x5BEDAC00, 0x17);//9
	match(ip_long, 0x5BEDBE00, 0x18);//9
	match(ip_long, 0x5BEDC400, 0x18);//9
	match(ip_long, 0x5BEDDB00, 0x18);//9
	match(ip_long, 0x5BEDE000, 0x16);//9
	match(ip_long, 0x5BEDE400, 0x17);//9
	match(ip_long, 0x5BEE2400, 0x18);//9
	match(ip_long, 0x5BEE3400, 0x16);//9
	match(ip_long, 0x5BEE3800, 0x16);//9
	match(ip_long, 0x5BEE3C00, 0x18);//9
	match(ip_long, 0x5BEE3E00, 0x18);//9
	match(ip_long, 0x5BEE3F00, 0x18);//9
	match(ip_long, 0x5BEE4C00, 0x17);//9
	match(ip_long, 0x5BEE4E00, 0x18);//9
	match(ip_long, 0x5BEE5500, 0x18);//9
	match(ip_long, 0x5BEE6B00, 0x18);//9
	match(ip_long, 0x5BEE7C00, 0x18);//9
	match(ip_long, 0x5BEE7D00, 0x18);//9
	match(ip_long, 0x5BEE8600, 0x17);//9
	match(ip_long, 0x5BEE8E00, 0x17);//9
	match(ip_long, 0x5BEE9100, 0x18);//9
	match(ip_long, 0x5BEEA600, 0x17);//9
	match(ip_long, 0x5BEEAC00, 0x16);//9
	match(ip_long, 0x5BEEB200, 0x17);//9
	match(ip_long, 0x5BEED800, 0x18);//9
	match(ip_long, 0x5BEEE800, 0x16);//9
	match(ip_long, 0x5BEEF000, 0x16);//9
	match(ip_long, 0x5BEEF600, 0x17);//9
	match(ip_long, 0x5BEEFE00, 0x18);//9
	match(ip_long, 0x5BEF1C00, 0x16);//9
	match(ip_long, 0x5BEF2400, 0x18);//9
	match(ip_long, 0x5BEF3D00, 0x18);//9
	match(ip_long, 0x5BEF4200, 0x17);//9
	match(ip_long, 0x5BEF5A00, 0x18);//9
	match(ip_long, 0x5BEF7100, 0x18);//9
	match(ip_long, 0x5BEF7200, 0x17);//9
	match(ip_long, 0x5BEF7400, 0x16);//9
	match(ip_long, 0x5BEF7800, 0x18);//9
	match(ip_long, 0x5BEF8100, 0x18);//9
	match(ip_long, 0x5BEF9000, 0x18);//9
	match(ip_long, 0x5BEF9800, 0x16);//9
	match(ip_long, 0x5BEFA800, 0x16);//9
	match(ip_long, 0x5BEFB400, 0x16);//9
	match(ip_long, 0x5BEFB900, 0x18);//9
	match(ip_long, 0x5BEFC400, 0x16);//9
	match(ip_long, 0x5BEFCD00, 0x18);//9
	match(ip_long, 0x5BEFF400, 0x16);//9
	match(ip_long, 0x5BEFF800, 0x16);//9
	match(ip_long, 0x5BEFFE00, 0x18);//9
	match(ip_long, 0x5BF01C00, 0x16);//9
	match(ip_long, 0x5BF02C00, 0x18);//9
	match(ip_long, 0x5BF02E00, 0x17);//9
	match(ip_long, 0x5BF04400, 0x18);//9
	match(ip_long, 0x5BF04600, 0x18);//9
	match(ip_long, 0x5BF04C00, 0x18);//9
	match(ip_long, 0x5BF05D00, 0x18);//9
	match(ip_long, 0x5BF06400, 0x17);//9
	match(ip_long, 0x5BF06A00, 0x17);//9
	match(ip_long, 0x5BF08200, 0x18);//9
	match(ip_long, 0x5BF08300, 0x18);//9
	match(ip_long, 0x5BF08400, 0x16);//9
	match(ip_long, 0x5BF08800, 0x16);//9
	match(ip_long, 0x5BF09800, 0x17);//9
	match(ip_long, 0x5BF0C100, 0x18);//9
	match(ip_long, 0x5BF0C400, 0x16);//9
	match(ip_long, 0x5BF0DF00, 0x18);//9
	match(ip_long, 0x5BF0EE00, 0x17);//9
	match(ip_long, 0x5BF0F800, 0x16);//9
	match(ip_long, 0x5BF0FE00, 0x18);//9
	match(ip_long, 0x5BF10200, 0x18);//9
	match(ip_long, 0x5BF10500, 0x18);//9
	match(ip_long, 0x5BF11800, 0x16);//9
	match(ip_long, 0x5BF11F00, 0x18);//9
	match(ip_long, 0x5BF12000, 0x16);//9
	match(ip_long, 0x5BF12400, 0x16);//9
	match(ip_long, 0x5BF12800, 0x17);//9
	match(ip_long, 0x5BF13000, 0x16);//9
	match(ip_long, 0x5BF13C00, 0x16);//9
	match(ip_long, 0x5BF23800, 0x15);//9
	match(ip_long, 0x5BF2AE00, 0x17);//9
	match(ip_long, 0x5BF2DA00, 0x18);//9
	match(ip_long, 0x5BF2DC00, 0x17);//9
	match(ip_long, 0x5BF34200, 0x17);//9
	match(ip_long, 0x5BF44600, 0x17);//9
	match(ip_long, 0x5BF4B800, 0x15);//9
	match(ip_long, 0x5BF4D000, 0x14);//9
	match(ip_long, 0x5BF4E100, 0x18);//9
	match(ip_long, 0x5BF4E600, 0x17);//9
	match(ip_long, 0x5BF4F800, 0x16);//9
	match(ip_long, 0x5BF55000, 0x15);//9
	match(ip_long, 0x5BF5DB00, 0x18);//9
	match(ip_long, 0x5BF60F00, 0x18);//9
	match(ip_long, 0x5BF64000, 0x15);//9
	match(ip_long, 0x5BF64800, 0x16);//9
	match(ip_long, 0x5BF64C00, 0x16);//9
	match(ip_long, 0x5BF66800, 0x15);//9
	match(ip_long, 0x5BF6A800, 0x16);//9
	match(ip_long, 0x5BF6D000, 0x15);//9
	match(ip_long, 0x5BF79300, 0x18);//9
	match(ip_long, 0x5BF7FC00, 0x18);//9
	match(ip_long, 0x5D9D4000, 0x15);//9
	match(ip_long, 0x5D9D4800, 0x15);//9
	match(ip_long, 0x5D9D5800, 0x16);//9
	match(ip_long, 0x5D9D5C00, 0x16);//9
	match(ip_long, 0x5D9D6000, 0x15);//9
	match(ip_long, 0x5D9D7000, 0x15);//9
	match(ip_long, 0x5D9D9800, 0x15);//9
	match(ip_long, 0x5DAF4000, 0x13);//9
	match(ip_long, 0x5DAF6000, 0x13);//9
	match(ip_long, 0x5DAF8000, 0x14);//9
	match(ip_long, 0x5DAFA000, 0x14);//9
	match(ip_long, 0x5E9A1000, 0x15);//9
	match(ip_long, 0x5E9A1800, 0x15);//9
	match(ip_long, 0x5E9A3800, 0x15);//9
	match(ip_long, 0x5E9A6000, 0x15);//9
	match(ip_long, 0x5E9E8000, 0x14);//9
	match(ip_long, 0x5E9EE000, 0x14);//9
	match(ip_long, 0x5EE70000, 0x14);//9
	match(ip_long, 0x5EE73000, 0x14);//9
	match(ip_long, 0x5EE82000, 0x15);//9
	match(ip_long, 0x5EE89000, 0x15);//9
	match(ip_long, 0x5EE89800, 0x15);//9
	match(ip_long, 0x5EE8D800, 0x15);//9
	match(ip_long, 0x5FD71400, 0x16);//9
	match(ip_long, 0x5FD71800, 0x15);//9
	match(ip_long, 0x5FD73400, 0x16);//9
	match(ip_long, 0x5FD74C00, 0x16);//9
	match(ip_long, 0x5FD7C000, 0x15);//9
	match(ip_long, 0x5FD7E800, 0x16);//9
	match(ip_long, 0x6D5EF000, 0x14);//1
	match(ip_long, 0x6D5F0000, 0x15);//1
	match(ip_long, 0x6D5F1800, 0x15);//1
	match(ip_long, 0x6D5F5800, 0x15);//1
	match(ip_long, 0x6D5F7000, 0x15);//1
	match(ip_long, 0x6D5F8800, 0x15);//1
	match(ip_long, 0x6D5F9000, 0x15);//1
	match(ip_long, 0x6D5F9800, 0x15);//1
	match(ip_long, 0x6D5FA800, 0x15);//1
	match(ip_long, 0x6D5FB000, 0x15);//1
	match(ip_long, 0x6D5FC800, 0x15);//1
	match(ip_long, 0x6D5FE800, 0x15);//1
	match(ip_long, 0x6DC40000, 0x14);//1
	match(ip_long, 0x6DC42000, 0x14);//1
	match(ip_long, 0x6DC43000, 0x14);//1
	match(ip_long, 0x6DC45000, 0x14);//1
	match(ip_long, 0x6DC47000, 0x14);//1
	match(ip_long, 0x6DC49000, 0x14);//1
	match(ip_long, 0x6DC4E000, 0x14);//1
	match(ip_long, 0x6DC4F000, 0x14);//1
	match(ip_long, 0x6DC52000, 0x15);//1
	match(ip_long, 0x6DC52800, 0x15);//1
	match(ip_long, 0x6DC53800, 0x15);//1
	match(ip_long, 0x6DC54000, 0x15);//1
	match(ip_long, 0x6DC56000, 0x15);//1
	match(ip_long, 0x6DC5A400, 0x18);//1
	match(ip_long, 0x6DC5A800, 0x15);//1
	match(ip_long, 0x6DC5B800, 0x15);//1
	match(ip_long, 0x6DCEC000, 0x13);//1
	match(ip_long, 0x6DCF3000, 0x14);//1
	match(ip_long, 0x6DCF6000, 0x14);//1
	match(ip_long, 0x6DCF9000, 0x14);//1
	match(ip_long, 0x8D620000, 0x10);//1
	match(ip_long, 0x91ED0000, 0x10);//1
	match(ip_long, 0x959C0000, 0x10);//1
	match(ip_long, 0x99130000, 0x10);//1
	match(ip_long, 0x9B9E0000, 0x10);//1
	match(ip_long, 0x9C110000, 0x10);//1
	match(ip_long, 0x9D190000, 0x10);//1
	match(ip_long, 0x9D9E0000, 0x10);//1
	match(ip_long, 0x9E420000, 0x10);//1
	match(ip_long, 0x9E4B0000, 0x10);//1
	match(ip_long, 0xAB19B600, 0x18);//1
	match(ip_long, 0xAB19B700, 0x18);//1
	match(ip_long, 0xAB19C000, 0x18);//1
	match(ip_long, 0xAB19C400, 0x16);//1
	match(ip_long, 0xAB19D800, 0x18);//1
	match(ip_long, 0xAB19E200, 0x17);//1
	match(ip_long, 0xAB19E600, 0x18);//1
	match(ip_long, 0xAB19E700, 0x18);//1
	match(ip_long, 0xB0602000, 0x14);//1
	match(ip_long, 0xB0609000, 0x15);//1
	match(ip_long, 0xB060A000, 0x14);//1
	match(ip_long, 0xB0611000, 0x15);//1
	match(ip_long, 0xB0611800, 0x15);//1
	match(ip_long, 0xB0613000, 0x15);//1
	match(ip_long, 0xB0615000, 0x14);//1
	match(ip_long, 0xB0618800, 0x15);//1
	match(ip_long, 0xB061F800, 0x15);//1
	match(ip_long, 0xB0627000, 0x15);//1
	match(ip_long, 0xB0627800, 0x15);//1
	match(ip_long, 0xB0633000, 0x15);//1
	match(ip_long, 0xB064C000, 0x15);//1
	match(ip_long, 0xB0655000, 0x15);//1
	match(ip_long, 0xB0658000, 0x14);//1
	match(ip_long, 0xB065A000, 0x15);//1
	match(ip_long, 0xB0665000, 0x14);//1
	match(ip_long, 0xB066B000, 0x14);//1
	match(ip_long, 0xB0672000, 0x15);//1
	match(ip_long, 0xB0672800, 0x15);//1
	match(ip_long, 0xB0674800, 0x15);//1
	match(ip_long, 0xB067A000, 0x15);//1
	match(ip_long, 0xB067A800, 0x15);//1
	match(ip_long, 0xB0687000, 0x15);//1
	match(ip_long, 0xB068B000, 0x15);//1
	match(ip_long, 0xB0698000, 0x14);//1
	match(ip_long, 0xB06A2000, 0x15);//1
	match(ip_long, 0xB06A6800, 0x15);//1
	match(ip_long, 0xB06B2000, 0x15);//1
	match(ip_long, 0xB06B2800, 0x15);//1
	match(ip_long, 0xB06B6800, 0x15);//1
	match(ip_long, 0xB06B7000, 0x15);//1
	match(ip_long, 0xB06BA800, 0x15);//1
	match(ip_long, 0xB06C8000, 0x15);//1
	match(ip_long, 0xB06D3000, 0x15);//1
	match(ip_long, 0xB06D8000, 0x15);//1
	match(ip_long, 0xB06DA000, 0x15);//1
	match(ip_long, 0xB06E9000, 0x14);//1
	match(ip_long, 0xB06F1000, 0x14);//1
	match(ip_long, 0xB06F7000, 0x15);//1
	match(ip_long, 0xB06F7800, 0x15);//1
	match(ip_long, 0xB06F8000, 0x13);//1
	match(ip_long, 0xB06FE000, 0x14);//1
	match(ip_long, 0xB0704800, 0x15);//1
	match(ip_long, 0xB0707000, 0x15);//1
	match(ip_long, 0xB071C000, 0x14);//1
	match(ip_long, 0xB072E800, 0x15);//1
	match(ip_long, 0xB0730000, 0x13);//1
	match(ip_long, 0xB0735000, 0x15);//1
	match(ip_long, 0xB073F000, 0x14);//1
	match(ip_long, 0xB0749400, 0x16);//1
	match(ip_long, 0xB074C800, 0x15);//1
	match(ip_long, 0xB0768800, 0x15);//1
	match(ip_long, 0xB0772000, 0x13);//1
	match(ip_long, 0xB0787800, 0x15);//1
	match(ip_long, 0xB0795000, 0x15);//1
	match(ip_long, 0xB0797000, 0x14);//1
	match(ip_long, 0xB07AC700, 0x18);//1
	match(ip_long, 0xB07AD400, 0x16);//1
	match(ip_long, 0xB07AD800, 0x15);//1
	match(ip_long, 0xB07AE000, 0x14);//1
	match(ip_long, 0xB07AF400, 0x17);//1
	match(ip_long, 0xB07B3C00, 0x17);//1
	match(ip_long, 0xB07BDF00, 0x18);//1
	match(ip_long, 0xB07C8C00, 0x16);//1
	match(ip_long, 0xB07CBE00, 0x18);//1
	match(ip_long, 0xB07CF000, 0x16);//1
	match(ip_long, 0xB07CF400, 0x17);//1
	match(ip_long, 0xB07E3800, 0x16);//1
	match(ip_long, 0xB29F8000, 0x14);//1
	match(ip_long, 0xB29FA000, 0x14);//1
	match(ip_long, 0xB29FC000, 0x14);//1
	match(ip_long, 0xB2D41800, 0x15);//1
	match(ip_long, 0xB2D42800, 0x15);//1
	match(ip_long, 0xB2D43000, 0x15);//1
	match(ip_long, 0xB2D47800, 0x15);//1
	match(ip_long, 0xB2D49000, 0x15);//1
	match(ip_long, 0xB2D49800, 0x15);//1
	match(ip_long, 0xB2D4A000, 0x15);//1
	match(ip_long, 0xB2D4A800, 0x15);//1
	match(ip_long, 0xB2D4D800, 0x15);//1
	match(ip_long, 0xB2D4FF00, 0x18);//1
	match(ip_long, 0xB2D53800, 0x15);//1
	match(ip_long, 0xB2D55800, 0x15);//1
	match(ip_long, 0xB2D56000, 0x15);//1
	match(ip_long, 0xB2D57800, 0x15);//1
	match(ip_long, 0xB2D58800, 0x15);//1
	match(ip_long, 0xB2D5A000, 0x15);//1
	match(ip_long, 0xB2D5D800, 0x15);//1
	match(ip_long, 0xB2D60000, 0x13);//1
	match(ip_long, 0xB2D68000, 0x13);//1
	match(ip_long, 0xB2D7C000, 0x14);//1
	match(ip_long, 0xB2D81800, 0x15);//1
	match(ip_long, 0xB2D82800, 0x15);//1
	match(ip_long, 0xB2D85800, 0x15);//1
	match(ip_long, 0xB2D86800, 0x15);//1
	match(ip_long, 0xB2D88800, 0x15);//1
	match(ip_long, 0xB2D8C800, 0x15);//1
	match(ip_long, 0xB2D92000, 0x15);//1
	match(ip_long, 0xB2D97000, 0x15);//1
	match(ip_long, 0xB2D98800, 0x15);//1
	match(ip_long, 0xB2D9B800, 0x15);//1
	match(ip_long, 0xB2D9C000, 0x15);//1
	match(ip_long, 0xB2D9D800, 0x15);//1
	match(ip_long, 0xB2D9F800, 0x15);//1
	match(ip_long, 0xB2DAE000, 0x14);//1
	match(ip_long, 0xB2DB1000, 0x14);//1
	match(ip_long, 0xB2DB6000, 0x14);//1
	match(ip_long, 0xB2DB7000, 0x14);//1
	match(ip_long, 0xB2DB8000, 0x14);//1
	match(ip_long, 0xB9010400, 0x16);//1
	match(ip_long, 0xB9010900, 0x18);//1
	match(ip_long, 0xB9010A00, 0x17);//1
	match(ip_long, 0xB9011100, 0x18);//1
	match(ip_long, 0xB9011500, 0x18);//1
	match(ip_long, 0xB9011600, 0x18);//1
	match(ip_long, 0xBC002000, 0x15);//1
	match(ip_long, 0xBCBF8000, 0x17);//1
	match(ip_long, 0xBCBFC800, 0x15);//1
	match(ip_long, 0xBCBFD800, 0x15);//1
	match(ip_long, 0xC036DC00, 0x18);//1
	match(ip_long, 0xC0376D00, 0x18);//1
	match(ip_long, 0xC0443300, 0x18);//1
	match(ip_long, 0xC053A500, 0x18);//1
	match(ip_long, 0xC0560E00, 0x18);//1
	match(ip_long, 0xC058CC00, 0x18);//1
	match(ip_long, 0xC066E100, 0x18);//1
	match(ip_long, 0xC07C7400, 0x18);//1
	match(ip_long, 0xC087FE00, 0x18);//1
	match(ip_long, 0xC0932A00, 0x18);//1
	match(ip_long, 0xC0938D00, 0x18);//1
	match(ip_long, 0xC0950300, 0x18);//1
	match(ip_long, 0xC0965300, 0x18);//1
	match(ip_long, 0xC0966800, 0x18);//1
	match(ip_long, 0xC0997F00, 0x18);//1
	match(ip_long, 0xC0A06E00, 0x18);//1
	match(ip_long, 0xC0A22C00, 0x16);//1
	match(ip_long, 0xC0A23000, 0x16);//1
	match(ip_long, 0xC0A23C00, 0x16);//1
	match(ip_long, 0xC0A25C00, 0x16);//1
	match(ip_long, 0xC0A28000, 0x16);//1
	match(ip_long, 0xC0A29000, 0x16);//1
	match(ip_long, 0xC0A29400, 0x16);//1
	match(ip_long, 0xC0A2A400, 0x16);//1
	match(ip_long, 0xC0A2AC00, 0x16);//1
	match(ip_long, 0xC0A2B000, 0x16);//1
	match(ip_long, 0xC0A2F800, 0x18);//1
	match(ip_long, 0xC0A67800, 0x17);//1
	match(ip_long, 0xC0A6CA00, 0x17);//1
	match(ip_long, 0xC0A6D800, 0x16);//1
	match(ip_long, 0xC0A6FF00, 0x18);//1
	match(ip_long, 0xC0BCE900, 0x18);//1
	match(ip_long, 0xC0BCEA00, 0x17);//1
	match(ip_long, 0xC0BCEC00, 0x17);//1
	match(ip_long, 0xC0C34800, 0x18);//1
	match(ip_long, 0xC0C36A00, 0x18);//1
	match(ip_long, 0xC0F5A900, 0x18);//1
	match(ip_long, 0xC1004000, 0x12);//1
	match(ip_long, 0xC1008000, 0x18);//1
	match(ip_long, 0xC1009000, 0x18);//1
	match(ip_long, 0xC100C000, 0x16);//1
	match(ip_long, 0xC100C400, 0x17);//1
	match(ip_long, 0xC100D000, 0x16);//1
	match(ip_long, 0xC100EC00, 0x18);//1
	match(ip_long, 0xC100F200, 0x18);//1
	match(ip_long, 0xC1082D00, 0x18);//1
	match(ip_long, 0xC1083900, 0x18);//1
	match(ip_long, 0xC1083D00, 0x18);//1
	match(ip_long, 0xC108B600, 0x17);//1
	match(ip_long, 0xC1091900, 0x18);//1
	match(ip_long, 0xC1097900, 0x18);//1
	match(ip_long, 0xC1097B00, 0x18);//1
	match(ip_long, 0xC1106300, 0x18);//1
	match(ip_long, 0xC1106B00, 0x18);//1
	match(ip_long, 0xC110E500, 0x18);//1
	match(ip_long, 0xC110EF00, 0x18);//1
	match(ip_long, 0xC110F000, 0x18);//1
	match(ip_long, 0xC110FF00, 0x18);//1
	match(ip_long, 0xC1110E00, 0x18);//1
	match(ip_long, 0xC1112900, 0x18);//1
	match(ip_long, 0xC1113600, 0x18);//1
	match(ip_long, 0xC1114700, 0x18);//1
	match(ip_long, 0xC1115400, 0x18);//1
	match(ip_long, 0xC111AC00, 0x18);//1
	match(ip_long, 0xC111AE00, 0x18);//1
	match(ip_long, 0xC111B800, 0x18);//1
	match(ip_long, 0xC111C800, 0x18);//1
	match(ip_long, 0xC111CB00, 0x18);//1
	match(ip_long, 0xC111D400, 0x18);//1
	match(ip_long, 0xC111D600, 0x18);//1
	match(ip_long, 0xC111DF00, 0x18);//1
	match(ip_long, 0xC1136800, 0x17);//1
	match(ip_long, 0xC1137A00, 0x17);//1
	match(ip_long, 0xC1137C00, 0x17);//1
	match(ip_long, 0xC1138C00, 0x16);//1
	match(ip_long, 0xC113A400, 0x16);//1
	match(ip_long, 0xC113D400, 0x16);//1
	match(ip_long, 0xC1160500, 0x18);//1
	match(ip_long, 0xC1161C00, 0x18);//1
	match(ip_long, 0xC1165100, 0x18);//1
	match(ip_long, 0xC1165300, 0x18);//1
	match(ip_long, 0xC1165B00, 0x18);//1
	match(ip_long, 0xC116A900, 0x18);//1
	match(ip_long, 0xC116AF00, 0x18);//1
	match(ip_long, 0xC116FC00, 0x18);//1
	match(ip_long, 0xC1173000, 0x18);//1
	match(ip_long, 0xC1173300, 0x18);//1
	match(ip_long, 0xC1173600, 0x18);//1
	match(ip_long, 0xC1173D00, 0x18);//1
	match(ip_long, 0xC1173F00, 0x18);//1
	match(ip_long, 0xC1177D00, 0x18);//1
	match(ip_long, 0xC117AE00, 0x18);//1
	match(ip_long, 0xC1180E00, 0x18);//1
	match(ip_long, 0xC1181800, 0x18);//1
	match(ip_long, 0xC118C800, 0x16);//1
	match(ip_long, 0xC118CC00, 0x16);//1
	match(ip_long, 0xC118F400, 0x16);//1
	match(ip_long, 0xC1190000, 0x15);//1
	match(ip_long, 0xC119A000, 0x17);//1
	match(ip_long, 0xC119A600, 0x17);//1
	match(ip_long, 0xC119A800, 0x17);//1
	match(ip_long, 0xC119B800, 0x17);//1
	match(ip_long, 0xC119C100, 0x18);//1
	match(ip_long, 0xC119DE00, 0x18);//1
	match(ip_long, 0xC119DF00, 0x18);//1
	match(ip_long, 0xC11A1900, 0x18);//1
	match(ip_long, 0xC11A8300, 0x18);//1
	match(ip_long, 0xC11AD200, 0x18);//1
	match(ip_long, 0xC11AD300, 0x18);//1
	match(ip_long, 0xC11AD700, 0x18);//1
	match(ip_long, 0xC11B0500, 0x18);//1
	match(ip_long, 0xC11B0600, 0x18);//1
	match(ip_long, 0xC11B0800, 0x18);//1
	match(ip_long, 0xC11B5200, 0x17);//1
	match(ip_long, 0xC11B5A00, 0x17);//1
	match(ip_long, 0xC11BC600, 0x17);//1
	match(ip_long, 0xC11BCC00, 0x17);//1
	match(ip_long, 0xC11BD200, 0x17);//1
	match(ip_long, 0xC11C0000, 0x18);//1
	match(ip_long, 0xC11C5400, 0x18);//1
	match(ip_long, 0xC11C9E00, 0x18);//1
	match(ip_long, 0xC11CBB00, 0x18);//1
	match(ip_long, 0xC11CBD00, 0x18);//1
	match(ip_long, 0xC11CE200, 0x18);//1
	match(ip_long, 0xC11CE600, 0x18);//1
	match(ip_long, 0xC11D3000, 0x18);//1
	match(ip_long, 0xC11D3300, 0x18);//1
	match(ip_long, 0xC11DCD00, 0x18);//1
	match(ip_long, 0xC11DCF00, 0x18);//1
	match(ip_long, 0xC11DFF00, 0x18);//1
	match(ip_long, 0xC11E6D00, 0x18);//1
	match(ip_long, 0xC11EA000, 0x18);//1
	match(ip_long, 0xC1202400, 0x18);//1
	match(ip_long, 0xC1202500, 0x18);//1
	match(ip_long, 0xC1203200, 0x18);//1
	match(ip_long, 0xC1203B00, 0x18);//1
	match(ip_long, 0xC1210000, 0x17);//1
	match(ip_long, 0xC1210400, 0x17);//1
	match(ip_long, 0xC1210800, 0x17);//1
	match(ip_long, 0xC1212200, 0x17);//1
	match(ip_long, 0xC1212A00, 0x17);//1
	match(ip_long, 0xC1213A00, 0x17);//1
	match(ip_long, 0xC1216E00, 0x17);//1
	match(ip_long, 0xC1217C00, 0x17);//1
	match(ip_long, 0xC121AE00, 0x17);//1
	match(ip_long, 0xC121B000, 0x17);//1
	match(ip_long, 0xC1220000, 0x16);//1
	match(ip_long, 0xC1222C00, 0x16);//1
	match(ip_long, 0xC1223400, 0x16);//1
	match(ip_long, 0xC1227000, 0x16);//1
	match(ip_long, 0xC1228A00, 0x17);//1
	match(ip_long, 0xC1229E00, 0x17);//1
	match(ip_long, 0xC122A200, 0x17);//1
	match(ip_long, 0xC122B200, 0x17);//1
	match(ip_long, 0xC122C100, 0x19);//1
	match(ip_long, 0xC122C380, 0x19);//1
	match(ip_long, 0xC122C400, 0x19);//1
	match(ip_long, 0xC122C500, 0x19);//1
	match(ip_long, 0xC122C680, 0x19);//1
	match(ip_long, 0xC122CB80, 0x19);//1
	match(ip_long, 0xC122CC00, 0x18);//1
	match(ip_long, 0xC122D400, 0x16);//1
	match(ip_long, 0xC122DC00, 0x16);//1
	match(ip_long, 0xC1232400, 0x18);//1
	match(ip_long, 0xC1232900, 0x18);//1
	match(ip_long, 0xC1232F00, 0x18);//1
	match(ip_long, 0xC1233C00, 0x18);//1
	match(ip_long, 0xC1236300, 0x18);//1
	match(ip_long, 0xC1236E00, 0x18);//1
	match(ip_long, 0xC124B700, 0x18);//1
	match(ip_long, 0xC1258B00, 0x18);//1
	match(ip_long, 0xC1258C00, 0x18);//1
	match(ip_long, 0xC1263000, 0x18);//1
	match(ip_long, 0xC1274700, 0x18);//1
	match(ip_long, 0xC1292C00, 0x18);//1
	match(ip_long, 0xC1297000, 0x17);//1
	match(ip_long, 0xC129AC00, 0x16);//1
	match(ip_long, 0xC129D200, 0x17);//1
	match(ip_long, 0xC129E600, 0x18);//1
	match(ip_long, 0xC129E700, 0x18);//1
	match(ip_long, 0xC12A9300, 0x18);//1
	match(ip_long, 0xC12A9900, 0x18);//1
	match(ip_long, 0xC12A9A00, 0x18);//1
	match(ip_long, 0xC12AD300, 0x18);//1
	match(ip_long, 0xC12ADA00, 0x18);//1
	match(ip_long, 0xC12AE400, 0x16);//1
	match(ip_long, 0xC12B0080, 0x19);//1
	match(ip_long, 0xC12B0C00, 0x17);//1
	match(ip_long, 0xC12B4D00, 0x18);//1
	match(ip_long, 0xC12B5A00, 0x18);//1
	match(ip_long, 0xC12B9000, 0x18);//1
	match(ip_long, 0xC12B9400, 0x18);//1
	match(ip_long, 0xC12BB500, 0x18);//1
	match(ip_long, 0xC12BE400, 0x16);//1
	match(ip_long, 0xC12BF000, 0x16);//1
	match(ip_long, 0xC12E2F00, 0x18);//1
	match(ip_long, 0xC12E4400, 0x18);//1
	match(ip_long, 0xC12EB500, 0x18);//1
	match(ip_long, 0xC12EB900, 0x18);//1
	match(ip_long, 0xC12EBA00, 0x18);//1
	match(ip_long, 0xC12EBB00, 0x18);//1
	match(ip_long, 0xC12ED400, 0x18);//1
	match(ip_long, 0xC12EED00, 0x18);//1
	match(ip_long, 0xC12F9700, 0x18);//1
	match(ip_long, 0xC12F9E00, 0x17);//1
	match(ip_long, 0xC12FA000, 0x18);//1
	match(ip_long, 0xC12FA300, 0x18);//1
	match(ip_long, 0xC12FF700, 0x18);//1
	match(ip_long, 0xC135FF00, 0x18);//1
	match(ip_long, 0xC13AE800, 0x18);//1
	match(ip_long, 0xC13AF900, 0x18);//1
	match(ip_long, 0xC1541D00, 0x18);//1
	match(ip_long, 0xC1544700, 0x18);//1
	match(ip_long, 0xC1544A00, 0x18);//1
	match(ip_long, 0xC1544F00, 0x18);//1
	match(ip_long, 0xC154B600, 0x18);//1
	match(ip_long, 0xC154F600, 0x18);//1
	match(ip_long, 0xC15D4400, 0x16);//1
	match(ip_long, 0xC15D5800, 0x16);//1
	match(ip_long, 0xC15D5C00, 0x16);//1
	match(ip_long, 0xC15D6800, 0x16);//1
	match(ip_long, 0xC15D9000, 0x16);//1
	match(ip_long, 0xC15D9C00, 0x16);//1
	match(ip_long, 0xC15DCC00, 0x16);//1
	match(ip_long, 0xC1680200, 0x18);//1
	match(ip_long, 0xC1682D00, 0x18);//1
	match(ip_long, 0xC1682E00, 0x18);//1
	match(ip_long, 0xC1683200, 0x18);//1
	match(ip_long, 0xC1684700, 0x18);//1
	match(ip_long, 0xC1685800, 0x18);//1
	match(ip_long, 0xC1686300, 0x18);//1
	match(ip_long, 0xC1689A00, 0x18);//1
	match(ip_long, 0xC1689C00, 0x18);//1
	match(ip_long, 0xC168A100, 0x18);//1
	match(ip_long, 0xC168A300, 0x18);//1
	match(ip_long, 0xC168A600, 0x18);//1
	match(ip_long, 0xC168B800, 0x18);//1
	match(ip_long, 0xC168DD00, 0x18);//1
	match(ip_long, 0xC168EB00, 0x18);//1
	match(ip_long, 0xC168EF00, 0x18);//1
	match(ip_long, 0xC168F400, 0x18);//1
	match(ip_long, 0xC168FB00, 0x18);//1
	match(ip_long, 0xC1691000, 0x18);//1
	match(ip_long, 0xC1691400, 0x18);//1
	match(ip_long, 0xC1691800, 0x18);//1
	match(ip_long, 0xC1691D00, 0x18);//1
	match(ip_long, 0xC1692000, 0x18);//1
	match(ip_long, 0xC1692300, 0x18);//1
	match(ip_long, 0xC1692D00, 0x18);//1
	match(ip_long, 0xC1693F00, 0x18);//1
	match(ip_long, 0xC1694200, 0x18);//1
	match(ip_long, 0xC1694B00, 0x18);//1
	match(ip_long, 0xC1696E00, 0x18);//1
	match(ip_long, 0xC1697A00, 0x18);//1
	match(ip_long, 0xC1697D00, 0x18);//1
	match(ip_long, 0xC1698100, 0x18);//1
	match(ip_long, 0xC1698F00, 0x18);//1
	match(ip_long, 0xC169A700, 0x18);//1
	match(ip_long, 0xC169B200, 0x18);//1
	match(ip_long, 0xC169B400, 0x18);//1
	match(ip_long, 0xC169BF00, 0x18);//1
	match(ip_long, 0xC169C000, 0x18);//1
	match(ip_long, 0xC169CA00, 0x18);//1
	match(ip_long, 0xC169DD00, 0x18);//1
	match(ip_long, 0xC169E300, 0x18);//1
	match(ip_long, 0xC169E500, 0x18);//1
	match(ip_long, 0xC169F200, 0x18);//1
	match(ip_long, 0xC169F800, 0x18);//1
	match(ip_long, 0xC169FB00, 0x18);//1
	match(ip_long, 0xC16A4C00, 0x16);//1
	match(ip_long, 0xC16A5400, 0x16);//1
	match(ip_long, 0xC16A6400, 0x16);//1
	match(ip_long, 0xC16A6800, 0x16);//1
	match(ip_long, 0xC16A8000, 0x16);//1
	match(ip_long, 0xC16A9800, 0x16);//1
	match(ip_long, 0xC16A9C00, 0x16);//1
	match(ip_long, 0xC16AC000, 0x16);//1
	match(ip_long, 0xC16AD000, 0x17);//1
	match(ip_long, 0xC16AD800, 0x16);//1
	match(ip_long, 0xC16AE400, 0x16);//1
	match(ip_long, 0xC16AEE00, 0x18);//1
	match(ip_long, 0xC16AF400, 0x16);//1
	match(ip_long, 0xC16B0800, 0x16);//1
	match(ip_long, 0xC16B2000, 0x16);//1
	match(ip_long, 0xC16B5800, 0x16);//1
	match(ip_long, 0xC16BA400, 0x16);//1
	match(ip_long, 0xC16BC400, 0x16);//1
	match(ip_long, 0xC16BD400, 0x16);//1
	match(ip_long, 0xC16BF800, 0x16);//1
	match(ip_long, 0xC16C2200, 0x17);//1
	match(ip_long, 0xC16C7C00, 0x16);//1
	match(ip_long, 0xC16CB100, 0x18);//1
	match(ip_long, 0xC16CC200, 0x18);//1
	match(ip_long, 0xC16CCA00, 0x18);//1
	match(ip_long, 0xC16CCE00, 0x18);//1
	match(ip_long, 0xC16CDC00, 0x18);//1
	match(ip_long, 0xC16CE400, 0x17);//1
	match(ip_long, 0xC16D3A00, 0x17);//1
	match(ip_long, 0xC16D5B00, 0x18);//1
	match(ip_long, 0xC16D7300, 0x18);//1
	match(ip_long, 0xC16D7B00, 0x18);//1
	match(ip_long, 0xC16D7F00, 0x18);//1
	match(ip_long, 0xC16DD400, 0x18);//1
	match(ip_long, 0xC16DE100, 0x18);//1
	match(ip_long, 0xC16DE200, 0x18);//1
	match(ip_long, 0xC16DEF00, 0x18);//1
	match(ip_long, 0xC16DF400, 0x17);//1
	match(ip_long, 0xC16E5000, 0x18);//1
	match(ip_long, 0xC16E6000, 0x17);//1
	match(ip_long, 0xC16E6200, 0x17);//1
	match(ip_long, 0xC16E7800, 0x16);//1
	match(ip_long, 0xC16E8900, 0x18);//1
	match(ip_long, 0xC16E8E00, 0x18);//1
	match(ip_long, 0xC16EE400, 0x16);//1
	match(ip_long, 0xC16F1600, 0x17);//1
	match(ip_long, 0xC16F1A00, 0x17);//1
	match(ip_long, 0xC16F2400, 0x18);//1
	match(ip_long, 0xC16F2500, 0x18);//1
	match(ip_long, 0xC16F2600, 0x18);//1
	match(ip_long, 0xC16F2700, 0x18);//1
	match(ip_long, 0xC16F2900, 0x18);//1
	match(ip_long, 0xC16F9000, 0x16);//1
	match(ip_long, 0xC16FA600, 0x18);//1
	match(ip_long, 0xC16FEC00, 0x18);//1
	match(ip_long, 0xC18A4100, 0x18);//1
	match(ip_long, 0xC18A6E00, 0x18);//1
	match(ip_long, 0xC18A7600, 0x18);//1
	match(ip_long, 0xC18A8800, 0x16);//1
	match(ip_long, 0xC18A8C00, 0x16);//1
	match(ip_long, 0xC18AD000, 0x16);//1
	match(ip_long, 0xC18AF000, 0x16);//1
	match(ip_long, 0xC18E7000, 0x18);//1
	match(ip_long, 0xC18E7100, 0x18);//1
	match(ip_long, 0xC18E7300, 0x18);//1
	match(ip_long, 0xC18ED200, 0x18);//1
	match(ip_long, 0xC18EF300, 0x18);//1
	match(ip_long, 0xC18F4D00, 0x18);//1
	match(ip_long, 0xC18F7900, 0x18);//1
	match(ip_long, 0xC1960200, 0x17);//1
	match(ip_long, 0xC1961500, 0x18);//1
	match(ip_long, 0xC1962400, 0x17);//1
	match(ip_long, 0xC1962900, 0x18);//1
	match(ip_long, 0xC1962A00, 0x17);//1
	match(ip_long, 0xC1962C00, 0x16);//1
	match(ip_long, 0xC1963200, 0x17);//1
	match(ip_long, 0xC1964500, 0x18);//1
	match(ip_long, 0xC1964C00, 0x16);//1
	match(ip_long, 0xC1967B00, 0x18);//1
	match(ip_long, 0xC196A500, 0x18);//1
	match(ip_long, 0xC1970800, 0x16);//1
	match(ip_long, 0xC1972400, 0x16);//1
	match(ip_long, 0xC1973000, 0x16);//1
	match(ip_long, 0xC1973400, 0x16);//1
	match(ip_long, 0xC1974000, 0x16);//1
	match(ip_long, 0xC1974400, 0x16);//1
	match(ip_long, 0xC1974C00, 0x16);//1
	match(ip_long, 0xC1976000, 0x16);//1
	match(ip_long, 0xC1976400, 0x16);//1
	match(ip_long, 0xC1977000, 0x16);//1
	match(ip_long, 0xC1A40100, 0x18);//1
	match(ip_long, 0xC1A40200, 0x17);//1
	match(ip_long, 0xC1A40400, 0x17);//1
	match(ip_long, 0xC1A40600, 0x18);//1
	match(ip_long, 0xC1A41000, 0x14);//1
	match(ip_long, 0xC1A48100, 0x18);//1
	match(ip_long, 0xC1A48E00, 0x18);//1
	match(ip_long, 0xC1A49D00, 0x18);//1
	match(ip_long, 0xC1A4FE00, 0x17);//1
	match(ip_long, 0xC1A83600, 0x18);//1
	match(ip_long, 0xC1A91200, 0x17);//1
	match(ip_long, 0xC1A94E00, 0x17);//1
	match(ip_long, 0xC1A97000, 0x16);//1
	match(ip_long, 0xC1A97400, 0x17);//1
	match(ip_long, 0xC1A99400, 0x17);//1
	match(ip_long, 0xC1A9E800, 0x17);//1
	match(ip_long, 0xC1B27500, 0x18);//1
	match(ip_long, 0xC1B28400, 0x18);//1
	match(ip_long, 0xC1B28F00, 0x18);//1
	match(ip_long, 0xC1B2A100, 0x18);//1
	match(ip_long, 0xC1B2A400, 0x18);//1
	match(ip_long, 0xC1B2A700, 0x18);//1
	match(ip_long, 0xC1B2D500, 0x18);//1
	match(ip_long, 0xC1B2D600, 0x18);//1
	match(ip_long, 0xC1B2F000, 0x16);//1
	match(ip_long, 0xC1BA0400, 0x18);//1
	match(ip_long, 0xC1BA2700, 0x18);//1
	match(ip_long, 0xC1BAFF00, 0x18);//1
	match(ip_long, 0xC1BB3400, 0x18);//1
	match(ip_long, 0xC1BB3500, 0x18);//1
	match(ip_long, 0xC1BB4000, 0x15);//1
	match(ip_long, 0xC1BC0000, 0x18);//1
	match(ip_long, 0xC1BC86A0, 0x1D);//1
	match(ip_long, 0xC1BCC600, 0x17);//1
	match(ip_long, 0xC1BCFD00, 0x18);//1
	match(ip_long, 0xC1BD4800, 0x17);//1
	match(ip_long, 0xC1BD4C00, 0x17);//1
	match(ip_long, 0xC1BD7400, 0x17);//1
	match(ip_long, 0xC1C03E00, 0x17);//1
	match(ip_long, 0xC1C1A800, 0x18);//1
	match(ip_long, 0xC1C1B500, 0x18);//1
	match(ip_long, 0xC1C27B00, 0x18);//1
	match(ip_long, 0xC1C81400, 0x18);//1
	match(ip_long, 0xC1C82E00, 0x17);//1
	match(ip_long, 0xC1C83200, 0x17);//1
	match(ip_long, 0xC1C84200, 0x17);//1
	match(ip_long, 0xC1C85200, 0x17);//1
	match(ip_long, 0xC1C86C00, 0x17);//1
	match(ip_long, 0xC1C87600, 0x17);//1
	match(ip_long, 0xC1C87800, 0x17);//1
	match(ip_long, 0xC1C87A00, 0x17);//1
	match(ip_long, 0xC1C88500, 0x18);//1
	match(ip_long, 0xC1C89200, 0x18);//1
	match(ip_long, 0xC1C8BA00, 0x18);//1
	match(ip_long, 0xC1C8BB00, 0x18);//1
	match(ip_long, 0xC1C8C500, 0x18);//1
	match(ip_long, 0xC1C8D700, 0x18);//1
	match(ip_long, 0xC1C8D800, 0x18);//1
	match(ip_long, 0xC1C8E200, 0x18);//1
	match(ip_long, 0xC1C8E300, 0x18);//1
	match(ip_long, 0xC1C8E800, 0x18);//1
	match(ip_long, 0xC1C8E900, 0x18);//1
	match(ip_long, 0xC1C8EA00, 0x18);//1
	match(ip_long, 0xC1C91200, 0x17);//1
	match(ip_long, 0xC1C92200, 0x18);//1
	match(ip_long, 0xC1C92400, 0x18);//1
	match(ip_long, 0xC1C98800, 0x16);//1
	match(ip_long, 0xC1C99000, 0x19);//1
	match(ip_long, 0xC1C99540, 0x1A);//1
	match(ip_long, 0xC1C9A400, 0x18);//1
	match(ip_long, 0xC1C9A700, 0x18);//1
	match(ip_long, 0xC1CA7200, 0x18);//1
	match(ip_long, 0xC1CA7500, 0x18);//1
	match(ip_long, 0xC1CB2C00, 0x16);//1
	match(ip_long, 0xC1CB3800, 0x16);//1
	match(ip_long, 0xC1CB6200, 0x17);//1
	match(ip_long, 0xC1CBCE00, 0x17);//1
	match(ip_long, 0xC1CBD000, 0x17);//1
	match(ip_long, 0xC1CBDE00, 0x17);//1
	match(ip_long, 0xC1DA7300, 0x18);//1
	match(ip_long, 0xC1DA7E00, 0x17);//1
	match(ip_long, 0xC1DA8400, 0x16);//1
	match(ip_long, 0xC1DA9400, 0x16);//1
	match(ip_long, 0xC1DA9800, 0x16);//1
	match(ip_long, 0xC1DAB000, 0x16);//1
	match(ip_long, 0xC1DB1C00, 0x18);//1
	match(ip_long, 0xC1DB6B00, 0x18);//1
	match(ip_long, 0xC1DB7100, 0x18);//1
	match(ip_long, 0xC1DB7200, 0x18);//1
	match(ip_long, 0xC1DB7E00, 0x18);//1
	match(ip_long, 0xC1DD7A00, 0x18);//1
	match(ip_long, 0xC1DD7E00, 0x18);//1
	match(ip_long, 0xC1DE8300, 0x18);//1
	match(ip_long, 0xC1DE8700, 0x18);//1
	match(ip_long, 0xC1DF0000, 0x18);//1
	match(ip_long, 0xC1E36400, 0x18);//1
	match(ip_long, 0xC1E36900, 0x18);//1
	match(ip_long, 0xC1E37000, 0x18);//1
	match(ip_long, 0xC1E37400, 0x18);//1
	match(ip_long, 0xC1E37B00, 0x18);//1
	match(ip_long, 0xC1E38300, 0x18);//1
	match(ip_long, 0xC1E3D800, 0x15);//1
	match(ip_long, 0xC1E4AE00, 0x18);//1
	match(ip_long, 0xC1EE0C00, 0x16);//1
	match(ip_long, 0xC1EE1000, 0x16);//1
	match(ip_long, 0xC1EE1800, 0x18);//1
	match(ip_long, 0xC1EE2800, 0x16);//1
	match(ip_long, 0xC1EE4000, 0x16);//1
	match(ip_long, 0xC1EE5C00, 0x16);//1
	match(ip_long, 0xC1EEA800, 0x16);//1
	match(ip_long, 0xC1EEAC00, 0x16);//1
	match(ip_long, 0xC1EEB400, 0x16);//1
	match(ip_long, 0xC1EEC800, 0x16);//1
	match(ip_long, 0xC1EF2400, 0x16);//1
	match(ip_long, 0xC1EF2C00, 0x16);//1
	match(ip_long, 0xC1EF3800, 0x16);//1
	match(ip_long, 0xC1EF3C00, 0x16);//1
	match(ip_long, 0xC1EF5000, 0x16);//1
	match(ip_long, 0xC1EF6400, 0x16);//1
	match(ip_long, 0xC1EF7C00, 0x16);//1
	match(ip_long, 0xC1EF8800, 0x17);//1
	match(ip_long, 0xC1EF9000, 0x17);//1
	match(ip_long, 0xC1EFB800, 0x18);//1
	match(ip_long, 0xC1EFCC00, 0x17);//1
	match(ip_long, 0xC1EFCE00, 0x17);//1
	match(ip_long, 0xC1EFD000, 0x17);//1
	match(ip_long, 0xC1EFE000, 0x17);//1
	match(ip_long, 0xC1F26400, 0x18);//1
	match(ip_long, 0xC1F28800, 0x16);//1
	match(ip_long, 0xC1F28E00, 0x17);//1
	match(ip_long, 0xC1F29200, 0x17);//1
	match(ip_long, 0xC1F29800, 0x18);//1
	match(ip_long, 0xC1F2A800, 0x17);//1
	match(ip_long, 0xC1F2AC00, 0x18);//1
	match(ip_long, 0xC1F2D400, 0x17);//1
	match(ip_long, 0xC1F2D700, 0x18);//1
	match(ip_long, 0xC1F38E00, 0x17);//1
	match(ip_long, 0xC1F39200, 0x17);//1
	match(ip_long, 0xC1F39400, 0x17);//1
	match(ip_long, 0xC1F39A00, 0x17);//1
	match(ip_long, 0xC1FEEE00, 0x17);//1
	match(ip_long, 0xC1FEF600, 0x17);//1
	match(ip_long, 0xC2003E00, 0x18);//1
	match(ip_long, 0xC2006000, 0x16);//1
	match(ip_long, 0xC2006400, 0x16);//1
	match(ip_long, 0xC2008000, 0x18);//1
	match(ip_long, 0xC2009A00, 0x18);//1
	match(ip_long, 0xC200A700, 0x18);//1
	match(ip_long, 0xC200AB00, 0x18);//1
	match(ip_long, 0xC200B500, 0x18);//1
	match(ip_long, 0xC200C700, 0x18);//1
	match(ip_long, 0xC200D300, 0x18);//1
	match(ip_long, 0xC200DC00, 0x18);//1
	match(ip_long, 0xC200E900, 0x18);//1
	match(ip_long, 0xC200F000, 0x18);//1
	match(ip_long, 0xC200F400, 0x18);//1
	match(ip_long, 0xC200FB00, 0x18);//1
	match(ip_long, 0xC2019000, 0x18);//1
	match(ip_long, 0xC2019200, 0x18);//1
	match(ip_long, 0xC2019900, 0x18);//1
	match(ip_long, 0xC201C400, 0x18);//1
	match(ip_long, 0xC201C700, 0x18);//1
	match(ip_long, 0xC201C900, 0x18);//1
	match(ip_long, 0xC201D900, 0x18);//1
	match(ip_long, 0xC201F600, 0x18);//1
	match(ip_long, 0xC201FC00, 0x17);//1
	match(ip_long, 0xC201FE00, 0x18);//1
	match(ip_long, 0xC206CC00, 0x16);//1
	match(ip_long, 0xC206F100, 0x18);//1
	match(ip_long, 0xC206F500, 0x18);//1
	match(ip_long, 0xC206F600, 0x18);//1
	match(ip_long, 0xC2080E00, 0x18);//1
	match(ip_long, 0xC2082D00, 0x18);//1
	match(ip_long, 0xC2082E00, 0x18);//1
	match(ip_long, 0xC2084200, 0x17);//1
	match(ip_long, 0xC2084400, 0x17);//1
	match(ip_long, 0xC2091000, 0x17);//1
	match(ip_long, 0xC2091800, 0x17);//1
	match(ip_long, 0xC2092E00, 0x17);//1
	match(ip_long, 0xC2093400, 0x17);//1
	match(ip_long, 0xC2094200, 0x17);//1
	match(ip_long, 0xC2094400, 0x18);//1
	match(ip_long, 0xC2094E00, 0x17);//1
	match(ip_long, 0xC209DF00, 0x18);//1
	match(ip_long, 0xC20B1600, 0x18);//1
	match(ip_long, 0xC20B1800, 0x18);//1
	match(ip_long, 0xC20F7800, 0x16);//1
	match(ip_long, 0xC20F7C00, 0x18);//1
	match(ip_long, 0xC218A400, 0x17);//1
	match(ip_long, 0xC218AE00, 0x17);//1
	match(ip_long, 0xC218B400, 0x17);//1
	match(ip_long, 0xC218EE00, 0x17);//1
	match(ip_long, 0xC218F400, 0x17);//1
	match(ip_long, 0xC21C0C00, 0x16);//1
	match(ip_long, 0xC21C2000, 0x16);//1
	match(ip_long, 0xC21C2800, 0x16);//1
	match(ip_long, 0xC21C3000, 0x16);//1
	match(ip_long, 0xC21C5000, 0x16);//1
	match(ip_long, 0xC21C6800, 0x16);//1
	match(ip_long, 0xC21CA800, 0x16);//1
	match(ip_long, 0xC21CBC00, 0x16);//1
	match(ip_long, 0xC21CC800, 0x16);//1
	match(ip_long, 0xC21CDC00, 0x16);//1
	match(ip_long, 0xC21CE400, 0x16);//1
	match(ip_long, 0xC21D8000, 0x13);//1
	match(ip_long, 0xC21DA000, 0x14);//1
	match(ip_long, 0xC21DB000, 0x16);//1
	match(ip_long, 0xC21DB400, 0x16);//1
	match(ip_long, 0xC21EA400, 0x18);//1
	match(ip_long, 0xC21EB300, 0x18);//1
	match(ip_long, 0xC21F2000, 0x16);//1
	match(ip_long, 0xC21F2400, 0x17);//1
	match(ip_long, 0xC21F2600, 0x18);//1
	match(ip_long, 0xC21F2800, 0x17);//1
	match(ip_long, 0xC21F2B00, 0x18);//1
	match(ip_long, 0xC21F3000, 0x17);//1
	match(ip_long, 0xC21F3C00, 0x18);//1
	match(ip_long, 0xC21F3F00, 0x18);//1
	match(ip_long, 0xC21FFC00, 0x18);//1
	match(ip_long, 0xC2214800, 0x16);//1
	match(ip_long, 0xC2214C00, 0x17);//1
	match(ip_long, 0xC2215300, 0x18);//1
	match(ip_long, 0xC2216F00, 0x18);//1
	match(ip_long, 0xC2217400, 0x16);//1
	match(ip_long, 0xC221B900, 0x18);//1
	match(ip_long, 0xC221BB00, 0x18);//1
	match(ip_long, 0xC222C600, 0x18);//1
	match(ip_long, 0xC224A500, 0x18);//1
	match(ip_long, 0xC224A800, 0x18);//1
	match(ip_long, 0xC2290C00, 0x16);//1
	match(ip_long, 0xC22A2800, 0x18);//1
	match(ip_long, 0xC22A6E00, 0x17);//1
	match(ip_long, 0xC22A7400, 0x17);//1
	match(ip_long, 0xC22A7600, 0x17);//1
	match(ip_long, 0xC22A7800, 0x17);//1
	match(ip_long, 0xC230D800, 0x18);//1
	match(ip_long, 0xC230DB00, 0x18);//1
	match(ip_long, 0xC2317C00, 0x18);//1
	match(ip_long, 0xC2322500, 0x18);//1
	match(ip_long, 0xC2323100, 0x18);//1
	match(ip_long, 0xC2323500, 0x18);//1
	match(ip_long, 0xC2323D00, 0x18);//1
	match(ip_long, 0xC2324B00, 0x18);//1
	match(ip_long, 0xC2325300, 0x18);//1
	match(ip_long, 0xC2325900, 0x18);//1
	match(ip_long, 0xC2326E00, 0x18);//1
	match(ip_long, 0xC2327500, 0x18);//1
	match(ip_long, 0xC2327B00, 0x18);//1
	match(ip_long, 0xC2328400, 0x16);//1
	match(ip_long, 0xC2329B00, 0x18);//1
	match(ip_long, 0xC2329C00, 0x16);//1
	match(ip_long, 0xC232B400, 0x18);//1
	match(ip_long, 0xC232BA00, 0x18);//1
	match(ip_long, 0xC232D600, 0x18);//1
	match(ip_long, 0xC232FC00, 0x18);//1
	match(ip_long, 0xC2361000, 0x16);//1
	match(ip_long, 0xC2361400, 0x16);//1
	match(ip_long, 0xC2361800, 0x16);//1
	match(ip_long, 0xC2365400, 0x16);//1
	match(ip_long, 0xC236BC00, 0x16);//1
	match(ip_long, 0xC238D300, 0x18);//1
	match(ip_long, 0xC23C4F00, 0x18);//1
	match(ip_long, 0xC23CE200, 0x17);//1
	match(ip_long, 0xC23CFB00, 0x18);//1
	match(ip_long, 0xC23D3900, 0x18);//1
	match(ip_long, 0xC23D4200, 0x18);//1
	match(ip_long, 0xC23D4400, 0x16);//1
	match(ip_long, 0xC23F8000, 0x16);//1
	match(ip_long, 0xC23F8400, 0x16);//1
	match(ip_long, 0xC245CF00, 0x18);//1
	match(ip_long, 0xC24F1800, 0x16);//1
	match(ip_long, 0xC2580300, 0x18);//1
	match(ip_long, 0xC2580C00, 0x18);//1
	match(ip_long, 0xC2588000, 0x17);//1
	match(ip_long, 0xC2589A00, 0x17);//1
	match(ip_long, 0xC2589E00, 0x17);//1
	match(ip_long, 0xC258D600, 0x17);//1
	match(ip_long, 0xC258E000, 0x17);//1
	match(ip_long, 0xC258F400, 0x17);//1
	match(ip_long, 0xC25D7C00, 0x16);//1
	match(ip_long, 0xC2637500, 0x18);//1
	match(ip_long, 0xC2698400, 0x17);//1
	match(ip_long, 0xC26AC000, 0x17);//1
	match(ip_long, 0xC26AC800, 0x17);//1
	match(ip_long, 0xC26AD200, 0x17);//1
	match(ip_long, 0xC26AD600, 0x17);//1
	match(ip_long, 0xC26B1200, 0x18);//1
	match(ip_long, 0xC26B7800, 0x18);//1
	match(ip_long, 0xC26E1A00, 0x18);//1
	match(ip_long, 0xC26E4000, 0x17);//1
	match(ip_long, 0xC26E4D00, 0x18);//1
	match(ip_long, 0xC26E7400, 0x18);//1
	match(ip_long, 0xC26E7F00, 0x18);//1
	match(ip_long, 0xC26EEE00, 0x18);//1
	match(ip_long, 0xC26EEF00, 0x18);//1
	match(ip_long, 0xC26EF000, 0x18);//1
	match(ip_long, 0xC2729400, 0x16);//1
	match(ip_long, 0xC2748200, 0x17);//1
	match(ip_long, 0xC2748400, 0x17);//1
	match(ip_long, 0xC2748600, 0x17);//1
	match(ip_long, 0xC2748A00, 0x17);//1
	match(ip_long, 0xC274A600, 0x18);//1
	match(ip_long, 0xC274B600, 0x17);//1
	match(ip_long, 0xC274C000, 0x17);//1
	match(ip_long, 0xC274FC00, 0x17);//1
	match(ip_long, 0xC275E400, 0x17);//1
	match(ip_long, 0xC275F000, 0x17);//1
	match(ip_long, 0xC27EA400, 0x16);//1
	match(ip_long, 0xC27ECF00, 0x18);//1
	match(ip_long, 0xC27ED200, 0x18);//1
	match(ip_long, 0xC27ED800, 0x18);//1
	match(ip_long, 0xC27EDD00, 0x18);//1
	match(ip_long, 0xC27EDE00, 0x18);//1
	match(ip_long, 0xC27EE500, 0x18);//1
	match(ip_long, 0xC27EE800, 0x18);//1
	match(ip_long, 0xC27EEE00, 0x18);//1
	match(ip_long, 0xC27EFE00, 0x18);//1
	match(ip_long, 0xC27F8800, 0x18);//1
	match(ip_long, 0xC27F8900, 0x18);//1
	match(ip_long, 0xC28CE900, 0x18);//1
	match(ip_long, 0xC28CF100, 0x18);//1
	match(ip_long, 0xC28CFA00, 0x18);//1
	match(ip_long, 0xC28CFF00, 0x18);//1
	match(ip_long, 0xC2916000, 0x14);//1
	match(ip_long, 0xC2917400, 0x18);//1
	match(ip_long, 0xC291B800, 0x16);//1
	match(ip_long, 0xC291CC00, 0x17);//1
	match(ip_long, 0xC291E100, 0x18);//1
	match(ip_long, 0xC291E400, 0x18);//1
	match(ip_long, 0xC291E500, 0x18);//1
	match(ip_long, 0xC2927800, 0x18);//1
	match(ip_long, 0xC2927B00, 0x18);//1
	match(ip_long, 0xC2928000, 0x16);//1
	match(ip_long, 0xC292D800, 0x16);//1
	match(ip_long, 0xC292F800, 0x16);//1
	match(ip_long, 0xC292FC00, 0x16);//1
	match(ip_long, 0xC2936C00, 0x18);//1
	match(ip_long, 0xC293F800, 0x18);//1
	match(ip_long, 0xC2955800, 0x18);//1
	match(ip_long, 0xC295E400, 0x16);//1
	match(ip_long, 0xC295F000, 0x18);//1
	match(ip_long, 0xC2966000, 0x16);//1
	match(ip_long, 0xC2966400, 0x16);//1
	match(ip_long, 0xC296A600, 0x17);//1
	match(ip_long, 0xC296AA00, 0x17);//1
	match(ip_long, 0xC296B800, 0x17);//1
	match(ip_long, 0xC296C400, 0x17);//1
	match(ip_long, 0xC296CE00, 0x17);//1
	match(ip_long, 0xC296E600, 0x17);//1
	match(ip_long, 0xC296EE00, 0x17);//1
	match(ip_long, 0xC296F600, 0x17);//1
	match(ip_long, 0xC296FA00, 0x17);//1
	match(ip_long, 0xC2982E00, 0x17);//1
	match(ip_long, 0xC2983200, 0x17);//1
	match(ip_long, 0xC2983500, 0x18);//1
	match(ip_long, 0xC2983800, 0x17);//1
	match(ip_long, 0xC2983C00, 0x17);//1
	match(ip_long, 0xC2995F00, 0x18);//1
	match(ip_long, 0xC2996B00, 0x18);//1
	match(ip_long, 0xC2997300, 0x18);//1
	match(ip_long, 0xC2997700, 0x18);//1
	match(ip_long, 0xC2998500, 0x18);//1
	match(ip_long, 0xC2998600, 0x18);//1
	match(ip_long, 0xC2999F00, 0x1A);//1
	match(ip_long, 0xC299AA00, 0x18);//1
	match(ip_long, 0xC299D800, 0x18);//1
	match(ip_long, 0xC2A50800, 0x17);//1
	match(ip_long, 0xC2A52900, 0x18);//1
	match(ip_long, 0xC2A53000, 0x18);//1
	match(ip_long, 0xC2A53600, 0x18);//1
	match(ip_long, 0xC2A97E00, 0x18);//1
	match(ip_long, 0xC2A97F00, 0x18);//1
	match(ip_long, 0xC2A9DC00, 0x18);//1
	match(ip_long, 0xC2A9E200, 0x18);//1
	match(ip_long, 0xC2A9E300, 0x18);//1
	match(ip_long, 0xC2A9E400, 0x18);//1
	match(ip_long, 0xC2A9E500, 0x18);//1
	match(ip_long, 0xC2A9EC00, 0x18);//1
	match(ip_long, 0xC2A9F100, 0x18);//1
	match(ip_long, 0xC2B06500, 0x18);//1
	match(ip_long, 0xC2B06600, 0x18);//1
	match(ip_long, 0xC2B10400, 0x16);//1
	match(ip_long, 0xC2B11C00, 0x16);//1
	match(ip_long, 0xC2BB2800, 0x16);//1
	match(ip_long, 0xC2BB3400, 0x16);//1
	match(ip_long, 0xC2BB4800, 0x16);//1
	match(ip_long, 0xC2BB7400, 0x16);//1
	match(ip_long, 0xC2BB9000, 0x16);//1
	match(ip_long, 0xC2BBA800, 0x16);//1
	match(ip_long, 0xC2BBB400, 0x16);//1
	match(ip_long, 0xC2BBC800, 0x16);//1
	match(ip_long, 0xC2BBEC00, 0x16);//1
	match(ip_long, 0xC2D50100, 0x18);//1
	match(ip_long, 0xC2D51600, 0x18);//1
	match(ip_long, 0xC2D51A00, 0x18);//1
	match(ip_long, 0xC2F20000, 0x17);//1
	match(ip_long, 0xC2F22700, 0x18);//1
	match(ip_long, 0xC2F23400, 0x18);//1
	match(ip_long, 0xC2F23E00, 0x18);//1
	match(ip_long, 0xC2F26800, 0x16);//1
	match(ip_long, 0xC2F62760, 0x1B);//1
	match(ip_long, 0xC2F627C0, 0x1B);//1
	match(ip_long, 0xC2F66200, 0x18);//1
	match(ip_long, 0xC2F66A00, 0x17);//1
	match(ip_long, 0xC2F67C00, 0x17);//1
	match(ip_long, 0xC2F70000, 0x17);//1
	match(ip_long, 0xC2F70200, 0x17);//1
	match(ip_long, 0xC2F72900, 0x18);//1
	match(ip_long, 0xC2F72E00, 0x18);//1
	match(ip_long, 0xC2F73E00, 0x18);//1
	match(ip_long, 0xC302D000, 0x17);//1
	match(ip_long, 0xC302DE00, 0x17);//1
	match(ip_long, 0xC302FE00, 0x17);//1
	match(ip_long, 0xC3039800, 0x16);//1
	match(ip_long, 0xC303C800, 0x16);//1
	match(ip_long, 0xC303DC00, 0x16);//1
	match(ip_long, 0xC303E800, 0x16);//1
	match(ip_long, 0xC305B500, 0x18);//1
	match(ip_long, 0xC305B600, 0x18);//1
	match(ip_long, 0xC305BC00, 0x18);//1
	match(ip_long, 0xC3083400, 0x17);//1
	match(ip_long, 0xC3086100, 0x18);//1
	match(ip_long, 0xC3086300, 0x18);//1
	match(ip_long, 0xC3086500, 0x18);//1
	match(ip_long, 0xC3086A00, 0x18);//1
	match(ip_long, 0xC3086B00, 0x18);//1
	match(ip_long, 0xC308D800, 0x17);//1
	match(ip_long, 0xC308DC00, 0x17);//1
	match(ip_long, 0xC30C2000, 0x16);//1
	match(ip_long, 0xC30D2580, 0x19);//1
	match(ip_long, 0xC30D2600, 0x17);//1
	match(ip_long, 0xC30D2E00, 0x19);//1
	match(ip_long, 0xC30E0300, 0x18);//1
	match(ip_long, 0xC30E0400, 0x18);//1
	match(ip_long, 0xC30E0B00, 0x18);//1
	match(ip_long, 0xC30E1E00, 0x18);//1
	match(ip_long, 0xC30E7400, 0x17);//1
	match(ip_long, 0xC3140000, 0x16);//1
	match(ip_long, 0xC3146E00, 0x17);//1
	match(ip_long, 0xC3147B00, 0x18);//1
	match(ip_long, 0xC3148300, 0x18);//1
	match(ip_long, 0xC3148600, 0x18);//1
	match(ip_long, 0xC3148A00, 0x18);//1
	match(ip_long, 0xC3149600, 0x18);//1
	match(ip_long, 0xC314C800, 0x17);//1
	match(ip_long, 0xC314D400, 0x17);//1
	match(ip_long, 0xC314DA00, 0x17);//1
	match(ip_long, 0xC3166000, 0x16);//1
	match(ip_long, 0xC3167400, 0x16);//1
	match(ip_long, 0xC3167C00, 0x16);//1
	match(ip_long, 0xC318F800, 0x17);//1
	match(ip_long, 0xC31A0C00, 0x17);//1
	match(ip_long, 0xC31A1600, 0x17);//1
	match(ip_long, 0xC31A1800, 0x18);//1
	match(ip_long, 0xC31A4800, 0x16);//1
	match(ip_long, 0xC31A4C00, 0x16);//1
	match(ip_long, 0xC31C0000, 0x17);//1
	match(ip_long, 0xC31C1000, 0x17);//1
	match(ip_long, 0xC31CAA00, 0x17);//1
	match(ip_long, 0xC31CBE00, 0x17);//1
	match(ip_long, 0xC3225000, 0x17);//1
	match(ip_long, 0xC322D000, 0x16);//1
	match(ip_long, 0xC322D800, 0x16);//1
	match(ip_long, 0xC3235000, 0x18);//1
	match(ip_long, 0xC3260C00, 0x16);//1
	match(ip_long, 0xC3261F00, 0x18);//1
	match(ip_long, 0xC327D800, 0x17);//1
	match(ip_long, 0xC32A6200, 0x17);//1
	match(ip_long, 0xC32A7000, 0x17);//1
	match(ip_long, 0xC32A8C00, 0x17);//1
	match(ip_long, 0xC32A9800, 0x17);//1
	match(ip_long, 0xC32AF900, 0x18);//1
	match(ip_long, 0xC32B4200, 0x17);//1
	match(ip_long, 0xC32B4800, 0x17);//1
	match(ip_long, 0xC32B5400, 0x17);//1
	match(ip_long, 0xC32B8E00, 0x18);//1
	match(ip_long, 0xC32B8F00, 0x18);//1
	match(ip_long, 0xC32B9C00, 0x18);//1
	match(ip_long, 0xC32E2400, 0x17);//1
	match(ip_long, 0xC32E2800, 0x16);//1
	match(ip_long, 0xC32FC900, 0x18);//1
	match(ip_long, 0xC32FCB00, 0x18);//1
	match(ip_long, 0xC32FE300, 0x18);//1
	match(ip_long, 0xC32FF600, 0x18);//1
	match(ip_long, 0xC3362E00, 0x17);//1
	match(ip_long, 0xC3363200, 0x17);//1
	match(ip_long, 0xC336B800, 0x16);//1
	match(ip_long, 0xC336BC00, 0x17);//1
	match(ip_long, 0xC33C4000, 0x17);//1
	match(ip_long, 0xC33C5060, 0x1B);//1
	match(ip_long, 0xC33C50A0, 0x1B);//1
	match(ip_long, 0xC33C5300, 0x1B);//1
	match(ip_long, 0xC33C5B80, 0x19);//1
	match(ip_long, 0xC33C5C80, 0x1A);//1
	match(ip_long, 0xC33C5E00, 0x19);//1
	match(ip_long, 0xC33CD800, 0x16);//1
	match(ip_long, 0xC33CF000, 0x16);//1
	match(ip_long, 0xC33E0C00, 0x17);//1
	match(ip_long, 0xC33E2800, 0x17);//1
	match(ip_long, 0xC33E4000, 0x17);//1
	match(ip_long, 0xC3408200, 0x17);//1
	match(ip_long, 0xC3409600, 0x17);//1
	match(ip_long, 0xC3409E00, 0x17);//1
	match(ip_long, 0xC340AE00, 0x17);//1
	match(ip_long, 0xC3421000, 0x15);//1
	match(ip_long, 0xC3424400, 0x18);//1
	match(ip_long, 0xC3424900, 0x18);//1
	match(ip_long, 0xC3425600, 0x18);//1
	match(ip_long, 0xC3425800, 0x18);//1
	match(ip_long, 0xC3426200, 0x18);//1
	match(ip_long, 0xC3426700, 0x18);//1
	match(ip_long, 0xC3427400, 0x18);//1
	match(ip_long, 0xC3429000, 0x17);//1
	match(ip_long, 0xC344C000, 0x17);//1
	match(ip_long, 0xC344E200, 0x17);//1
	match(ip_long, 0xC344E800, 0x17);//1
	match(ip_long, 0xC3455000, 0x16);//1
	match(ip_long, 0xC3457C00, 0x16);//1
	match(ip_long, 0xC345D000, 0x16);//1
	match(ip_long, 0xC3489400, 0x16);//1
	match(ip_long, 0xC34A3000, 0x16);//1
	match(ip_long, 0xC34A3800, 0x16);//1
	match(ip_long, 0xC34A4000, 0x18);//1
	match(ip_long, 0xC34A4500, 0x18);//1
	match(ip_long, 0xC34A4F00, 0x18);//1
	match(ip_long, 0xC34A5B00, 0x18);//1
	match(ip_long, 0xC34A5C00, 0x18);//1
	match(ip_long, 0xC34E3000, 0x17);//1
	match(ip_long, 0xC34E4200, 0x17);//1
	match(ip_long, 0xC34EEC00, 0x16);//1
	match(ip_long, 0xC3509400, 0x16);//1
	match(ip_long, 0xC350E500, 0x18);//1
	match(ip_long, 0xC350EC00, 0x18);//1
	match(ip_long, 0xC350ED00, 0x18);//1
	match(ip_long, 0xC355C300, 0x18);//1
	match(ip_long, 0xC355C400, 0x18);//1
	match(ip_long, 0xC355C700, 0x18);//1
	match(ip_long, 0xC355D100, 0x18);//1
	match(ip_long, 0xC355E300, 0x18);//1
	match(ip_long, 0xC355E600, 0x18);//1
	match(ip_long, 0xC355F100, 0x18);//1
	match(ip_long, 0xC355F300, 0x18);//1
	match(ip_long, 0xC355F900, 0x18);//1
	match(ip_long, 0xC355FC00, 0x18);//1
	match(ip_long, 0xC3581C00, 0x17);//1
	match(ip_long, 0xC3581E00, 0x17);//1
	match(ip_long, 0xC3583200, 0x17);//1
	match(ip_long, 0xC3585A00, 0x17);//1
	match(ip_long, 0xC3587200, 0x17);//1
	match(ip_long, 0xC3588000, 0x17);//1
	match(ip_long, 0xC3589000, 0x17);//1
	match(ip_long, 0xC358B400, 0x18);//1
	match(ip_long, 0xC358BA00, 0x17);//1
	match(ip_long, 0xC358E800, 0x17);//1
	match(ip_long, 0xC35A6600, 0x17);//1
	match(ip_long, 0xC35A6A00, 0x17);//1
	match(ip_long, 0xC35A7E00, 0x17);//1
	match(ip_long, 0xC35D8600, 0x17);//1
	match(ip_long, 0xC35D8E00, 0x17);//1
	match(ip_long, 0xC35DA200, 0x17);//1
	match(ip_long, 0xC35DB200, 0x17);//1
	match(ip_long, 0xC35DCA00, 0x17);//1
	match(ip_long, 0xC35DDE00, 0x17);//1
	match(ip_long, 0xC35DE600, 0x17);//1
	match(ip_long, 0xC35DEC00, 0x17);//1
	match(ip_long, 0xC35DFA00, 0x17);//1
	match(ip_long, 0xC35F8100, 0x18);//1
	match(ip_long, 0xC35F9000, 0x18);//1
	match(ip_long, 0xC35F9A00, 0x18);//1
	match(ip_long, 0xC35FA400, 0x18);//1
	match(ip_long, 0xC35FA900, 0x18);//1
	match(ip_long, 0xC35FAA00, 0x18);//1
	match(ip_long, 0xC35FB000, 0x18);//1
	match(ip_long, 0xC35FB600, 0x18);//1
	match(ip_long, 0xC35FBA00, 0x18);//1
	match(ip_long, 0xC35FBC00, 0x18);//1
	match(ip_long, 0xC35FEA00, 0x17);//1
	match(ip_long, 0xC36E3000, 0x17);//1
	match(ip_long, 0xC36E3200, 0x17);//1
	match(ip_long, 0xC3720000, 0x17);//1
	match(ip_long, 0xC3727E00, 0x17);//1
	match(ip_long, 0xC3801C00, 0x16);//1
	match(ip_long, 0xC3807000, 0x15);//1
	match(ip_long, 0xC3808700, 0x18);//1
	match(ip_long, 0xC3808C00, 0x18);//1
	match(ip_long, 0xC3808E00, 0x18);//1
	match(ip_long, 0xC3809400, 0x18);//1
	match(ip_long, 0xC3809A00, 0x18);//1
	match(ip_long, 0xC380AC00, 0x17);//1
	match(ip_long, 0xC380B400, 0x17);//1
	match(ip_long, 0xC380E400, 0x17);//1
	match(ip_long, 0xC380F200, 0x17);//1
	match(ip_long, 0xC382C500, 0x18);//1
	match(ip_long, 0xC382D400, 0x18);//1
	match(ip_long, 0xC387E400, 0x16);//1
	match(ip_long, 0xC389A100, 0x18);//1
	match(ip_long, 0xC389A200, 0x18);//1
	match(ip_long, 0xC389A800, 0x18);//1
	match(ip_long, 0xC389BD00, 0x18);//1
	match(ip_long, 0xC389D000, 0x17);//1
	match(ip_long, 0xC389F600, 0x17);//1
	match(ip_long, 0xC38AC800, 0x18);//1
	match(ip_long, 0xC38ACF00, 0x18);//1
	match(ip_long, 0xC38AD000, 0x18);//1
	match(ip_long, 0xC38AD300, 0x18);//1
	match(ip_long, 0xC38C9800, 0x16);//1
	match(ip_long, 0xC38CBC00, 0x16);//1
	match(ip_long, 0xC38CDC00, 0x16);//1
	match(ip_long, 0xC3900900, 0x18);//1
	match(ip_long, 0xC3900C00, 0x18);//1
	match(ip_long, 0xC3954000, 0x18);//1
	match(ip_long, 0xC3954400, 0x18);//1
	match(ip_long, 0xC3954D00, 0x18);//1
	match(ip_long, 0xC3955F00, 0x18);//1
	match(ip_long, 0xC3956200, 0x18);//1
	match(ip_long, 0xC3956400, 0x18);//1
	match(ip_long, 0xC3957600, 0x18);//1
	match(ip_long, 0xC3957C00, 0x18);//1
	match(ip_long, 0xC395C600, 0x17);//1
	match(ip_long, 0xC395E000, 0x15);//1
	match(ip_long, 0xC395E800, 0x15);//1
	match(ip_long, 0xC39EE200, 0x17);//1
	match(ip_long, 0xC39EF600, 0x17);//1
	match(ip_long, 0xC3A0AE00, 0x17);//1
	match(ip_long, 0xC3A0B200, 0x17);//1
	match(ip_long, 0xC3A0B400, 0x17);//1
	match(ip_long, 0xC3A0B800, 0x17);//1
	match(ip_long, 0xC3A21000, 0x17);//1
	match(ip_long, 0xC3A21800, 0x17);//1
	match(ip_long, 0xC3A24C00, 0x17);//1
	match(ip_long, 0xC3AAB600, 0x18);//1
	match(ip_long, 0xC3AABA00, 0x18);//1
	match(ip_long, 0xC3AABC00, 0x18);//1
	match(ip_long, 0xC3AABF00, 0x18);//1
	match(ip_long, 0xC3B14000, 0x16);//1
	match(ip_long, 0xC3B15400, 0x16);//1
	match(ip_long, 0xC3B16400, 0x16);//1
	match(ip_long, 0xC3B1C400, 0x17);//1
	match(ip_long, 0xC3B1D200, 0x17);//1
	match(ip_long, 0xC3B1D800, 0x17);//1
	match(ip_long, 0xC3B21A00, 0x17);//1
	match(ip_long, 0xC3B27200, 0x17);//1
	match(ip_long, 0xC3B27A00, 0x17);//1
	match(ip_long, 0xC3B60900, 0x18);//1
	match(ip_long, 0xC3B60E00, 0x18);//1
	match(ip_long, 0xC3B61300, 0x18);//1
	match(ip_long, 0xC3B61700, 0x18);//1
	match(ip_long, 0xC3B62200, 0x18);//1
	match(ip_long, 0xC3B62300, 0x18);//1
	match(ip_long, 0xC3B62600, 0x18);//1
	match(ip_long, 0xC3B62800, 0x18);//1
	match(ip_long, 0xC3B63100, 0x18);//1
	match(ip_long, 0xC3B63300, 0x18);//1
	match(ip_long, 0xC3B63400, 0x18);//1
	match(ip_long, 0xC3B63600, 0x18);//1
	match(ip_long, 0xC3B6CE00, 0x17);//1
	match(ip_long, 0xC3B6DA00, 0x17);//1
	match(ip_long, 0xC3B85200, 0x17);//1
	match(ip_long, 0xC3B85400, 0x17);//1
	match(ip_long, 0xC3B85800, 0x17);//1
	match(ip_long, 0xC3BD2000, 0x16);//1
	match(ip_long, 0xC3BD2800, 0x16);//1
	match(ip_long, 0xC3BD3400, 0x16);//1
	match(ip_long, 0xC3BD4C00, 0x16);//1
	match(ip_long, 0xC3BD5400, 0x16);//1
	match(ip_long, 0xC3BD5800, 0x16);//1
	match(ip_long, 0xC3BDE600, 0x17);//1
	match(ip_long, 0xC3BE0100, 0x18);//1
	match(ip_long, 0xC3BE1100, 0x18);//1
	match(ip_long, 0xC3BF0800, 0x17);//1
	match(ip_long, 0xC3BF3E00, 0x17);//1
	match(ip_long, 0xC3BFA200, 0x17);//1
	match(ip_long, 0xC3BFAA00, 0x17);//1
	match(ip_long, 0xC3BFB400, 0x17);//1
	match(ip_long, 0xC3BFB800, 0x17);//1
	match(ip_long, 0xC3BFE800, 0x17);//1
	match(ip_long, 0xC3BFF800, 0x17);//1
	match(ip_long, 0xC3C85800, 0x17);//1
	match(ip_long, 0xC3C8C700, 0x18);//1
	match(ip_long, 0xC3C8CE00, 0x18);//1
	match(ip_long, 0xC3C8D400, 0x18);//1
	match(ip_long, 0xC3C8D600, 0x18);//1
	match(ip_long, 0xC3C8EA00, 0x17);//1
	match(ip_long, 0xC3CE7000, 0x16);//1
	match(ip_long, 0xC3CE7400, 0x16);//1
	match(ip_long, 0xC3CE7C00, 0x16);//1
	match(ip_long, 0xC3CEE400, 0x17);//1
	match(ip_long, 0xC3D20C00, 0x17);//1
	match(ip_long, 0xC3D21800, 0x17);//1
	match(ip_long, 0xC3D22200, 0x17);//1
	match(ip_long, 0xC3D23C00, 0x17);//1
	match(ip_long, 0xC3D30000, 0x16);//1
	match(ip_long, 0xC3D30800, 0x16);//1
	match(ip_long, 0xC3D8DB00, 0x18);//1
	match(ip_long, 0xC3D8FA00, 0x18);//1
	match(ip_long, 0xC3D8FE00, 0x18);//1
	match(ip_long, 0xC3DE6400, 0x16);//1
	match(ip_long, 0xC3DE7000, 0x16);//1
	match(ip_long, 0xC3E12400, 0x17);//1
	match(ip_long, 0xC3E14400, 0x16);//1
	match(ip_long, 0xC3E14C00, 0x16);//1
	match(ip_long, 0xC3E15C00, 0x16);//1
	match(ip_long, 0xC3E17800, 0x16);//1
	match(ip_long, 0xC3E18800, 0x16);//1
	match(ip_long, 0xC3E1B400, 0x16);//1
	match(ip_long, 0xC3E1D400, 0x16);//1
	match(ip_long, 0xC3E1F400, 0x16);//1
	match(ip_long, 0xC3E1F800, 0x16);//1
	match(ip_long, 0xC3E2C600, 0x18);//1
	match(ip_long, 0xC3E2CF00, 0x18);//1
	match(ip_long, 0xC3E67100, 0x18);//1
	match(ip_long, 0xC3E67800, 0x18);//1
	match(ip_long, 0xC3EA0800, 0x17);//1
	match(ip_long, 0xC3EA1000, 0x17);//1
	match(ip_long, 0xC3EA1400, 0x17);//1
	match(ip_long, 0xC3EA2800, 0x18);//1
	match(ip_long, 0xC3EA3F00, 0x18);//1
	match(ip_long, 0xC3EA8D00, 0x18);//1
	match(ip_long, 0xC3EAA400, 0x18);//1
	match(ip_long, 0xC3EABD00, 0x18);//1
	match(ip_long, 0xC3EE4200, 0x17);//1
	match(ip_long, 0xC3EE4600, 0x17);//1
	match(ip_long, 0xC3EEA400, 0x16);//1
	match(ip_long, 0xC3EEA800, 0x16);//1
	match(ip_long, 0xC3EEB800, 0x16);//1
	match(ip_long, 0xC3EEE300, 0x18);//1
	match(ip_long, 0xC3EEE400, 0x18);//1
	match(ip_long, 0xC3EEEC00, 0x18);//1
	match(ip_long, 0xC3EEF500, 0x18);//1
	match(ip_long, 0xC3F24000, 0x17);//1
	match(ip_long, 0xC3F24400, 0x17);//1
	match(ip_long, 0xC3F25A00, 0x17);//1
	match(ip_long, 0xC3F25C00, 0x17);//1
	match(ip_long, 0xC3F26C00, 0x17);//1
	match(ip_long, 0xC3F27400, 0x17);//1
	match(ip_long, 0xC3F27C00, 0x17);//1
	match(ip_long, 0xC3F28000, 0x17);//1
	match(ip_long, 0xC3F28600, 0x17);//1
	match(ip_long, 0xC3F28A00, 0x17);//1
	match(ip_long, 0xC3F2B000, 0x18);//1
	match(ip_long, 0xC3F2B700, 0x18);//1
	match(ip_long, 0xC3F2BA00, 0x18);//1
	match(ip_long, 0xC3F2E800, 0x16);//1
	match(ip_long, 0xC3F2FC00, 0x16);//1
	match(ip_long, 0xC3F41A00, 0x17);//1
	match(ip_long, 0xC3F54200, 0x17);//1
	match(ip_long, 0xC3F54400, 0x17);//1
	match(ip_long, 0xC3F55400, 0x17);//1
	match(ip_long, 0xC3F55E00, 0x17);//1
	match(ip_long, 0xC3F56800, 0x17);//1
	match(ip_long, 0xC3F5C600, 0x18);//1
	match(ip_long, 0xC3F5CB00, 0x18);//1
	match(ip_long, 0xC3F5CC00, 0x18);//1
	match(ip_long, 0xC3F5D500, 0x18);//1
	match(ip_long, 0xC3F5D900, 0x18);//1
	match(ip_long, 0xC3F5DE00, 0x18);//1
	match(ip_long, 0xC3F5E000, 0x18);//1
	match(ip_long, 0xC3F5E200, 0x18);//1
	match(ip_long, 0xC3F67E00, 0x17);//1
	match(ip_long, 0xC3F6C800, 0x18);//1
	match(ip_long, 0xC3F6D800, 0x18);//1
	match(ip_long, 0xC3F6E000, 0x17);//1
	match(ip_long, 0xC3F84800, 0x18);//1
	match(ip_long, 0xC3F85800, 0x18);//1
	match(ip_long, 0xC3F8E200, 0x17);//1
	match(ip_long, 0xC3F8F600, 0x17);//1
	match(ip_long, 0xC3F8FE00, 0x17);//1
	match(ip_long, 0xC3FA2500, 0x18);//1
	match(ip_long, 0xC3FA2600, 0x18);//1
	match(ip_long, 0xC3FA3600, 0x18);//1
	match(ip_long, 0xC3FE8A00, 0x17);//1
	match(ip_long, 0xC3FE9C00, 0x17);//1
	match(ip_long, 0xC3FEAE00, 0x17);//1
	match(ip_long, 0xC3FEB000, 0x17);//1
	match(ip_long, 0xC3FEB800, 0x17);//1
	match(ip_long, 0xD5050000, 0x15);//2
	match(ip_long, 0xD5050800, 0x15);//2
	match(ip_long, 0xD5052800, 0x15);//2
	match(ip_long, 0xD5058800, 0x15);//2
	match(ip_long, 0xD5059000, 0x15);//2
	match(ip_long, 0xD505C800, 0x15);//2
	match(ip_long, 0xD505D000, 0x15);//2
	match(ip_long, 0xD505F800, 0x15);//2
	match(ip_long, 0xD56C0800, 0x15);//2
	match(ip_long, 0xD56C3800, 0x15);//2
	match(ip_long, 0xD56C5000, 0x15);//2
	match(ip_long, 0xD56C7000, 0x15);//2
	match(ip_long, 0xD56C9800, 0x15);//2
	match(ip_long, 0xD56CE000, 0x15);//2
	match(ip_long, 0xD56D2000, 0x14);//2
	match(ip_long, 0xD9ADA000, 0x14);//2
	match(ip_long, 0xD9ADB000, 0x14);//2
	match(ip_long, 0xD9C54000, 0x14);//2
	 
	return 0;
}
stock ip2long(const _ip[])
{
	new _count,_ipreturn,_len = strlen(_ip);
		
	if(_len > 0 && _len <= 16)
	{
	    for(new i = 0; i < _len; i++)
	        if(_ip[i] == '.')
	            _count++;
	            
		if(_count == 3)
		{
			_ipreturn = strval(_ip) << 24;
			_count = strfind(_ip, ".", false, 0) + 1;
			_ipreturn += strval(_ip[_count]) << 16;
			_count = strfind(_ip, ".", false, _count) + 1;
			_ipreturn += strval(_ip[_count]) << 8;
			_count = strfind(_ip, ".", false, _count) + 1;
			_ipreturn += strval(_ip[_count]);
		}
	}
	return _ipreturn;
}
stock IsPolishIP(const _ip[]) 
	return _check(ip2long(_ip));
  
  
Public:vote_aktualize(czas)
{
	
	if(czas > 0)
	{
		TextDrawSetString(glosowanie[3], vote_string);
		format(string2, sizeof(string2), "~g~~h~/Tak ~w~(%d)___~g~%s___~r~~h~/Nie (%d)~n~Pozostalo %ds", glosy[0], (glosy[0]==glosy[1])?("Remis"):(glosy[0]>glosy[1])?("Tak"):("Nie"), glosy[1], czas);
		TextDrawSetString(glosowanie[4], string2);
		
		for(new i;i!=5;i++)
		{
			if(i == 5) break;
			TextDrawShowForAll(glosowanie[i]);
		}
		SetTimerEx("vote_aktualize", 1000, 0, "d", czas - 1);
	} 
	else 
	{
		for(new i;i!=5;i++)
		{
			if(i == 5) break;
			TextDrawHideForAll(glosowanie[i]);
		}
		SendClientMessageToAll(COLOR_RED, "»  G³osowanie zakoñczone wynik: {b}%s{/b}", ((glosy[0]==glosy[1])?("Remis"):(glosy[0]>glosy[1])?("Tak"):("Nie")), glosy[0], glosy[1]);  
		glosy[0] = 0;
		glosy[1] = 0;
		for(new ix;ix<MAX_PLAYERS;ix++)
		{
			vote_oddal_glos[ix] = false;
		}
		if(glosy[0]>glosy[1] && glosy[0]!=glosy[1])
		{
			if(vote_kick && vote_kickid > -1)
			{
				if(IsPlayerConnected(vote_kickid))
				{
					BlockIpAddress(pInfo[vote_kickid][player_ip], (1000*60) * 60);
					Kick_(vote_kickid);
				}
			}
		}
		vote_kick = false;
		vote_kickid = -1;
		vote_trwa = false;
	}
}

DestroyVehicleEx(vehicleid)
{
	DestroyVehicle(vehicleid);

	WyjebDoczepianeObiekty(vehicleid);
	
	return 1;
}

// ----------------------------------- Tune Object Vehicle by Lagowy XD . 
// AHA CHCIA£EM JESZCZE DODAÆ ¯E DRIFTER LUBI SSAÆ MI PA£KE . POZDRO . 

IsVehicleDoczepianeObiekty(vehicleid)
{
	new i = GetVehicleModel(vehicleid), Kurwa;
		
	new Lista[] = {522, 562, 411, 470, 539, 560, 587, 451, 540, 482, 549, 535, 431};
	for(new l; l != sizeof Lista; l++) 
	{
		if(i == Lista[l]) 
		{
			Kurwa = 1;
			break;
		}
	}
	
	return Kurwa;
}

WyjebDoczepianeObiekty(vehicleid)
{
	for(new i; i != 2; i++) 
	{ 
		if(TuneObjekty[vehicleid][i] != -1)
		{
			DestroyDynamicObject(TuneObjekty[vehicleid][i]);
			TuneObjekty[vehicleid][i] = -1;
		}
	}
}

DoczepianeObiekty(vehicleid) // By Lagowy hehe
{
	new i = GetVehicleModel(vehicleid);
	WyjebDoczepianeObiekty(vehicleid);

	if(i == 522) // NRG - 500
	{
		TuneObjekty[vehicleid][0] = CreateDynamicObject(18702, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][0], vehicleid, 0.00, -1.125000, -1.049999, 0.00, 0.00, 0.00);
        TuneObjekty[vehicleid][1] = CreateDynamicObject(1019, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][1],vehicleid, 0.000000, -0.3, 0.225, -18.9, 0.0, 0.0);	
	}
	else if(i == 562) // ELEGY 
	{
		TuneObjekty[vehicleid][0] = CreateDynamicObject(18646, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][0], vehicleid, -0.225000,-0.150000,0.824999,0.00,0.00,0.00);
	}
	else if(i == 411) // INFERNUS
	{
        TuneObjekty[vehicleid][0] = CreateDynamicObject(3267, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
        AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][0], vehicleid, 0.000000, -0.1275, 0.105, 0.0, 0.0, 0.0);	
	}
	else if(i == 470) // PATRIOT
	{
		TuneObjekty[vehicleid][0] = CreateDynamicObject(2985, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][0], vehicleid, 1.065, 0.774, 0.155, 90.45, -0.0, 89.44);		
	}
	else if(i == 539) // VORTEX
	{
    	TuneObjekty[vehicleid][0] = CreateDynamicObject(18782, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][0], vehicleid, -0.435, 0.0, 0.585, 0.0, 0.0, 0.0);
	}
	else if(i == 560) // SULTAN
	{
		TuneObjekty[vehicleid][0] = CreateDynamicObject(1003, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][0], vehicleid, 0.0,-1.2,0.6,0.0,0.0,0.0);
	}
	else if(i == 587) // EUROS
	{
		TuneObjekty[vehicleid][0] = CreateDynamicObject(1012, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][0], vehicleid, 0.0,1.2,0.225,0.0,0.0,0.0);
		TuneObjekty[vehicleid][1] = CreateDynamicObject(1003, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][1], vehicleid, 0.0,-2.325,0.225,0.0,0.0,0.0);	
	}
	else if(i == 451) // TURISMO
	{
		TuneObjekty[vehicleid][0] = CreateDynamicObject(1006, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][0], vehicleid, 0.225,-0.2250,0.525,0.0,0.0,0.0);
		TuneObjekty[vehicleid][1] = CreateDynamicObject(1006, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][1], vehicleid, -0.225,-0.225,0.525,0.0,0.0,0.0);
	}
	else if(i == 540) // VINCENT
	{
		TuneObjekty[vehicleid][0] = CreateDynamicObject(362, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][0], vehicleid, -0.0,-0.3,1.0,-0.0,30.0,90.0);
	}
	else if(i == 482) // BURITTO
	{
		TuneObjekty[vehicleid][0] = CreateDynamicObject(2232, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][0], vehicleid, -0.0,0.0,-0.0,0.0,0.0,180.0);
		TuneObjekty[vehicleid][1] = CreateDynamicObject(1016, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][1], vehicleid, 0.0,0.0,0.0,-25.0,0.0,0.0);
	}
	else if(i == 549) // TAMPA
	{
		TuneObjekty[vehicleid][0] = CreateDynamicObject(728, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][0], vehicleid, 0.0,0.0,-1.35,0.0,0.0,0.0);
		TuneObjekty[vehicleid][1] = CreateDynamicObject(728, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][1], vehicleid, 0.075,-1.05,-1.35,0.0,0.0,-202.5);
	}
	else if(i == 535) // SLAMVAN
	{
		TuneObjekty[vehicleid][0] = CreateDynamicObject(19128, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
    	AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][0], vehicleid, 0.0,0.0,-0.7,0.0,0.0,0.0);
		TuneObjekty[vehicleid][1] = CreateDynamicObject(370, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][1], vehicleid, 0.0,-1.725,0.15,-90.0,0.0,0.0);
	}
	else if(i == 431) // BUS
	{
		TuneObjekty[vehicleid][0] = CreateDynamicObject(18651, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][0], vehicleid,  0.0,0.0,2.175,0.0,0.0,0.0);
		TuneObjekty[vehicleid][1] = CreateDynamicObject(18646, 0.0, 0.0, -1000.0, 0, 0, 0, 0, 0, -1, 100.0);
		AttachDynamicObjectToVehicle(TuneObjekty[vehicleid][1], vehicleid,0.0,2.0,2.175,0.0,0.0,0.0);
	}
	return 1;
}

//boty do dyskoteki 

stock initDyskActors()
{ 
	crateDyskActor(45, Float:{1679.5896,-1346.0549,804.6895,134.2089}, "MSK.");
	crateDyskActor(152, Float:{1683.0527,-1337.7643,805.2202,304.6404}, "TANCERKA MAGIKA");
}
stock crateDyskActor(actorSkin, Float:actorPos[4], actorName[])
{
	new actor;
	actor = CreateActor(actorSkin, actorPos[0], actorPos[1], actorPos[2], actorPos[3]);
	
	switch(random(10))
	{
		case 0: ApplyActorAnimation(actor, "DANCING", "dnce_M_a" ,  4.0, 1, 0, 0, 0, 0);
		case 1: ApplyActorAnimation(actor, "DANCING", "dnce_M_b" ,  4.0, 1, 0, 0, 0, 0);
		case 2: ApplyActorAnimation(actor, "DANCING", "dnce_M_c" ,  4.0, 1, 0, 0, 0, 0);
		case 3: ApplyActorAnimation(actor, "DANCING", "dnce_M_d" ,  4.0, 1, 0, 0, 0, 0);
		case 4: ApplyActorAnimation(actor, "DANCING", "DAN_Loop_A" , 4.0, 1, 0, 0, 0, 0);
		case 5: ApplyActorAnimation(actor, "DANCING", "DAN_Loop_A" , 4.0, 1, 0, 0, 0, 0);
		case 6: ApplyActorAnimation(actor, "DANCING", "DAN_Loop_A" , 4.0, 1, 0, 0, 0, 0);
		case 7: ApplyActorAnimation(actor, "DANCING", "DAN_Loop_A" , 4.0, 1, 0, 0, 0, 0);
		case 8: ApplyActorAnimation(actor, "DANCING", "DAN_Loop_A" , 4.0, 1, 0, 0, 0, 0);
		case 9: ApplyActorAnimation(actor, "DANCING", "dnce_M_b" , 4.0, 1, 0, 0, 0, 0);
	}
	CreateDynamic3DTextLabel(splitf("{ffffff}%s {ff0000}(%d)", actorName, actor), 0xc72a00ff, actorPos[0], actorPos[1], actorPos[2]+1.5, 10.0);

}

CMD:dodajdziwke(playerid,params[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	
	new skin, name[33];
	
	if(sscanf(params, "is[33]", skin, name)) 
		return SendClientMessage(playerid, COLOR_GREEN, ""chat" U¿yj: {b}/dodajdziwke <skin> <nick>"); //wygenerowany
	
	if(!(1 <= skin <= 311)) 
		return SendClientMessage(playerid, COLOR_GREEN, ""chat" Niepoprawne ID skinu "); //wygenerowany
	
	new Float:pos[4];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, pos[3]);
	
	crateDyskActor(skin, pos, name);
	
	SendClientMessage(playerid, COLOR_INFO2, "crateDyskActor(%d, Float:{%.2f, %.2f, %.2f, %.2f}, \"%s\");", skin, pos[0], pos[1], pos[2], pos[3], name); //wygenerowany
	
	SendClientMessage(playerid, COLOR_INFO3, "Pomyœlnie doda³eœ now¹ dziwkê \"{b}%s{/b}\". ", name); //wygenerowany
	
	return 1;
}
