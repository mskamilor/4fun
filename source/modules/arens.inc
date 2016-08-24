/*
Areans [NOT VERSION]
(c) Copyright 2013-2014 by mrdrifter, Game

@author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
@date      : 16 grudnia 2013
@update    : 3 stycznia 2014

*/

/*
#define getPlayers_onede 0
#define getPlayers_sawn 1
#define getPlayers_minigun 2
#define getPlayers_snajper 3
#define getPlayers_arenagang 4
#define getPlayers_onede 5
*/

stock ShowPlayerArenaFrag(playerid)
{
	if(IsPlayerValid(playerid)) return 0;
	
	new a_name[32];
	if(pInfo[playerid][player_arena])
	{
		switch(pInfo[playerid][player_arena])
		{
			case stats_onede: a_name = "/Onede";
			case stats_onede2: a_name = "/Onede2";
			case stats_sawn: a_name = "/Chainsaw";
			case stats_minigun: a_name = "/Minigun";
			case stats_snajper: a_name = "/Sniper";
			case stats_arenagang: a_name = "/ArenaGang";
		}
		if(a_name[0])
		{
			format(string2, sizeof(string2), "~g~Fragi na %s:~n~~>~~y~%d~<~", a_name, pInfo[playerid][player_eventpoints][pInfo[playerid][player_arena]]);
			PlayerEventTDSet(playerid, string2, a_name);
		} 
		else PlayerEventTD(playerid, false);
	}
	return 1;
}
CMD:onede(playerid, params[])
{
	gmData[server_arenaplayers][stats_onede]++;
	SpawnPlayerToArena(playerid, stats_onede, true);
	return 1;
}

CMD:onede2(playerid, params[])
{
//	RankAdmin(playerid, R_VICEHEADADMIN);
	
	gmData[server_arenaplayers][stats_onede2]++;
	SpawnPlayerToArena(playerid, stats_onede2, true);
	return 1;
}

CMD:chainsaw(playerid, params[])
{
	gmData[server_arenaplayers][stats_sawn]++;
	SpawnPlayerToArena(playerid, stats_sawn, true);
	return 1;
}
CMD:minigun(playerid, params[])
{
	gmData[server_arenaplayers][stats_minigun]++;
	SpawnPlayerToArena(playerid, stats_minigun, true);
	return 1;
}
CMD:sniper(playerid, params[])
{
	gmData[server_arenaplayers][stats_snajper]++;
	SpawnPlayerToArena(playerid, stats_snajper, true);
	return 1;
}
CMD:dm1(playerid,params[])
{
	gmData[server_arenaplayers][stats_dm1]++;
	SpawnPlayerToArena(playerid, stats_dm1, true);
	return 1;
}
CMD:dm2(playerid,params[])
{
	gmData[server_arenaplayers][stats_dm2]++;
	SpawnPlayerToArena(playerid, stats_dm2, true);
	return 1;
}
CMD:dm3(playerid,params[])
{
	gmData[server_arenaplayers][stats_dm3]++;
	SpawnPlayerToArena(playerid, stats_dm3, true);
	return 1;
}

CMD:arenagang(playerid, params[])
{
	if(!pInfo[playerid][player_gang])
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Aby do³¹czyæ do tej areny musisz byæ cz³onkiem gangu!");
		pInfo[playerid][player_arena] = 0;
		
		return 1;
	}
			
	gmData[server_arenaplayers][stats_arenagang]++;
	SpawnPlayerToArena(playerid, stats_arenagang, true);
	return 1;
}

CMD:aexit(playerid, params[])
{
	if(!pInfo[playerid][player_arena])
	{
		SendClientMessage(playerid, COLOR_ERROR, "Nie jesteœ na ¿adnej arenie");
		return 1;
	}
	
	gmData[server_arenaplayers][pInfo[playerid][player_arena]]--;
	UpdateArenaPlayers();
	
	pInfo[playerid][player_arena] = 0;
	
	Streamer_ToggleIdleUpdate(playerid, 1);
	Streamer_ToggleItemUpdate(playerid, 0, 1);
		
	ResetPlayerWeapons(playerid);
	OnPlayerSpawn(playerid);
	SetPlayerHealth(playerid,100.00);
	SetPlayerInterior(playerid,0);
	SetPlayerVirtualWorld(playerid,0);
	SetPlayerColorEx(playerid);
	PlayerEventTD(playerid, false);
	SendClientMessage(playerid, COLOR_GREEN, " Opuœci³eœ arenê.");
	return 1;
}

stock UpdateArenaPlayers()
{
	for(new i;i<24;i++) if(gmData[server_arenaplayers][i] < 0) gmData[server_arenaplayers][i] = 0;
	if(gmData[server_arenaplayers][stats_onede2] < 0) gmData[server_arenaplayers][stats_onede2] = 0;
	
	format(string2, sizeof(string2), "~n~~w~/Onede (~y~%d~w~)~n~~w~/Onede2 (~y~%d~w~)~n~~w~/Sniper (~y~%d~w~)~n~~w~/Chainsaw (~y~%d~w~)~n~~w~/Minigun (~y~%d~w~)~n~~w~/ArenaGang (~y~%d~w~)",
	gmData[server_arenaplayers][stats_onede],gmData[server_arenaplayers][stats_onede2], gmData[server_arenaplayers][stats_snajper], gmData[server_arenaplayers][stats_sawn], gmData[server_arenaplayers][stats_minigun], gmData[server_arenaplayers][stats_arenagang]);
	
	//format(string2, sizeof(string2), "~n~~w~/Onede (~y~%d~w~)~n~~w~__/Chainsaw (~y~%d~w~)~n~~w~_/Minigun (~y~%d~w~)~n~~w~/Sniper (~y~%d~w~)~n~~w~____/ArenaGang (~y~%d~w~)",
	//gmData[server_arenaplayers][stats_onede], gmData[server_arenaplayers][stats_sawn], gmData[server_arenaplayers][stats_minigun], gmData[server_arenaplayers][stats_snajper], gmData[server_arenaplayers][stats_arenagang]);

	TextDrawSetString(Areny, string2);
	
}
stock SpawnPlayerToArena(playerid, arenaid, bool:info = false)
{

	if(NetStats_PacketLossPercent(playerid) > 8.5 && strfind(pInfo[playerid][player_name],"[XMR]",true) == -1 )
	{
		SendClientMessage(playerid, COLOR_RED, ""chat" Masz za du?e Packet Lossty (%.2f/8.5). Nie mo¿esz przebywaæ na ¿adnej arenie.", NetStats_PacketLossPercent(playerid));
		
		if(pInfo[playerid][player_arena])
		{
		 
			gmData[server_arenaplayers][pInfo[playerid][player_arena]]--;
			pInfo[playerid][player_arena] = 0;
			OnPlayerSpawn(playerid);
		}
		return;
	}
	TextDrawHideForPlayer(playerid, SpawnOchrona);
	
	Streamer_ToggleIdleUpdate(playerid, 0);
	Streamer_ToggleItemUpdate(playerid, 0, 0);
	
	SetPlayerColor(playerid, 0xffff80FF);
		
	pInfo[playerid][player_spawnkill] = 0;
	pInfo[playerid][player_arena] = arenaid;
	
	UpdateArenaPlayers();
	
	ResetPlayerWeapons(playerid);
	switch(arenaid)
	{
		case stats_onede:
		{
			if(info)
			{
				SendClientMessageToAll(-1, "** {008ae6}%s (%d){/b} dolaczyl do areny {008ae6}/Onede{/b}. Dolacz i Ty.", playerNick(playerid), playerid);
				SendClientMessage(playerid, -1, " *{/b} Jesteœ na arenie: {008ae6}/onede{/b} aby wyjsc wpisz {008ae6}/Aexit");
				ShowPlayerArenaFrag(playerid);
			}
			
			GivePlayerWeapon(playerid, 24, 9999);
			SetPlayerHealth(playerid, 10.000000);
			SetPlayerArmour(playerid, 0.0);
			switch(random(10))
			{
				case 0:
				{
					SetPlayerPos(playerid, 298.277008, 173.203994, 1007.169982);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 200);
				}
				case 1:
				{
					SetPlayerPos(playerid, 276.273010, 186.367996, 1007.169982);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 200);
				}
				case 2:
				{
					SetPlayerPos(playerid, 246.565002, 176.500000, 1003.030029);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 200);
				}
				case 3:
				{
					SetPlayerPos(playerid, 230.483001, 161.380996, 1003.020019);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 200);
				}
				case 4:
				{
					SetPlayerPos(playerid, 231.630996, 141.561996, 1003.020019);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 200);
				}
				case 5:
				{
					SetPlayerPos(playerid, 221.617996, 146.522994, 1003.020019);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 200);
				}
				case 6:
				{
					SetPlayerPos(playerid, 211.166000, 146.794006, 1003.020019);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 200);
				}
				case 7:
				{
					SetPlayerPos(playerid, 214.261001, 165.919998, 1003.020019);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 200);
				}
				case 8:
				{
					SetPlayerPos(playerid, 193.046997, 178.776992, 1003.020019);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 200);
				}
				case 9:
				{
					SetPlayerPos(playerid, 193.152999, 157.944000, 1003.020019);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 200);
				}
				case 10:
				{
					SetPlayerPos(playerid, 218.279006, 182.927001, 1003.030029);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 200);
				}
			}
		}
		case stats_onede2:
		{
			if(info)
			{
				SendClientMessageToAll(-1, "** {008ae6}%s (%d){/b} dolaczyl do areny {008ae6}/Onede2{/b}. Dolacz i Ty.", playerNick(playerid), playerid);
				SendClientMessage(playerid, -1, " * Jesteœ na arenie: {008ae6}/onede2{/b} aby wyjsc wpisz {008ae6}/Aexit");
			}
			
			GivePlayerWeapon(playerid, 24, 9999);
			SetPlayerHealth(playerid, 10.000000);
			SetPlayerArmour(playerid, 0.0);
			switch(random(10))
			{
				case 0:
				{
					SetPlayerPos(playerid, 298.277008, 173.203994, 1007.169982);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 210);
				}
				case 1:
				{
					SetPlayerPos(playerid, 276.273010, 186.367996, 1007.169982);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 210);
				}
				case 2:
				{
					SetPlayerPos(playerid, 246.565002, 176.500000, 1003.030029);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 210);
				}
				case 3:
				{
					SetPlayerPos(playerid, 230.483001, 161.380996, 1003.020019);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 210);
				}
				case 4:
				{
					SetPlayerPos(playerid, 231.630996, 141.561996, 1003.020019);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 210);
				}
				case 5:
				{
					SetPlayerPos(playerid, 221.617996, 146.522994, 1003.020019);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 210);
				}
				case 6:
				{
					SetPlayerPos(playerid, 211.166000, 146.794006, 1003.020019);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 210);
				}
				case 7:
				{
					SetPlayerPos(playerid, 214.261001, 165.919998, 1003.020019);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 210);
				}
				case 8:
				{
					SetPlayerPos(playerid, 193.046997, 178.776992, 1003.020019);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 210);
				}
				case 9:
				{
					SetPlayerPos(playerid, 193.152999, 157.944000, 1003.020019);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 210);
				}
				case 10:
				{
					SetPlayerPos(playerid, 218.279006, 182.927001, 1003.030029);
					SetPlayerInterior(playerid, 3);
					SetPlayerVirtualWorld(playerid, 210);
				}
			}
		}
		case stats_sawn:
		{
			if(info)
			{
				SendClientMessageToAll(-1, "** {008ae6}%s (%d){/b} dolaczyl do areny {b}/chainsaw{/b}. Dolacz i Ty.", playerNick(playerid), playerid);
				SendClientMessage(playerid, -1, " Jesteœ na arenie: {008ae6}/chainsaw{/b} aby wyjsc wpisz {008ae6}/Aexit");
			}
		
			GivePlayerWeapon(playerid, 9, 1);
			SetPlayerHealth(playerid, 100.000000);
			SetPlayerArmour(playerid, 0.0);
			switch(random(7))
			{
				case 0:
				{
					SetPlayerPos(playerid, 962.9533,2164.9194,1011.0234);
					SetPlayerInterior(playerid, 1);
					SetPlayerVirtualWorld(playerid, 201);
				}
				case 1:
				{
					SetPlayerPos(playerid,958.7234,2154.4739,1011.0234);
					SetPlayerInterior(playerid, 1);
					SetPlayerVirtualWorld(playerid, 201);
				}
				case 2:
				{
					SetPlayerPos(playerid, 951.2156,2172.7886,1011.0234);
					SetPlayerInterior(playerid, 1);
					SetPlayerVirtualWorld(playerid, 201);
				}
				case 3:
				{
					SetPlayerPos(playerid, 933.3184,2173.4980,1011.0234);
					SetPlayerInterior(playerid, 1);
					SetPlayerVirtualWorld(playerid, 201);
				}
				case 4:
				{
					SetPlayerPos(playerid, 960.6320,2097.1455,1011.0225);
					SetPlayerInterior(playerid, 1);
					SetPlayerVirtualWorld(playerid, 201);
				}
				case 5:
				{
					SetPlayerPos(playerid,959.1338,2125.3589,1011.0234);
					SetPlayerInterior(playerid, 1);
					SetPlayerVirtualWorld(playerid, 201);
				}
				case 6:
				{
					SetPlayerPos(playerid, 933.5980,2139.5713,1011.0234);
					SetPlayerInterior(playerid, 1);
					SetPlayerVirtualWorld(playerid, 201);
				}
				case 7:
				{
					SetPlayerPos(playerid, 954.5153,2158.0693,1011.0234);
					SetPlayerInterior(playerid, 1);
					SetPlayerVirtualWorld(playerid, 201);
				}
			}
		}
		case stats_minigun:
		{
			if(info)
			{
				SendClientMessageToAll(-1, "** {008ae6}%s (%d){/b} dolaczyl do areny {008ae6}/Minigun{/b}. Dolacz i Ty.", playerNick(playerid), playerid);
				SendClientMessage(playerid, -1, " * Jesteœ na arenie: {008ae6}/minigun{/b} aby wyjsc wpisz{008ae6} /Aexit");
			}
			 
			GivePlayerWeapon(playerid, 38, 9999);
			SetPlayerHealth(playerid, 100.000000);
			SetPlayerArmour(playerid, 0.0);
			SetPlayerVirtualWorld(playerid, 444);
			//SetPlayerColor(playerid,0xFFFFFF00);
			switch(random(6))
			{
				case 0:
				{
					SetPlayerPos(playerid, -1063.4893,-693.7926,32.3516);
				}
				case 1:
				{
					SetPlayerPos(playerid, -1122.7025,-632.5530,32.0078);
				}
				case 2:
				{
					SetPlayerPos(playerid, -1103.9275,-597.0306,32.0078);
				}
				case 3:
				{
					SetPlayerPos(playerid, -1068.9471,-596.6239,32.0078);
				}
				case 4:
				{
					SetPlayerPos(playerid, -1017.9597,-704.9951,32.0078);
				}
				case 5:
				{
					SetPlayerPos(playerid,-987.4427,-708.7636,32.0078);
				}
			/*	case 6:
				{
					SetPlayerPos(playerid, -1055.65, -632.66, 135.88);
				}
				case 7:
				{
					SetPlayerPos(playerid, -987.15, -643.76, 174.05);
				}
				case 8:
				{
					SetPlayerPos(playerid, -1014.73, -704.99, 136.32);
				}
				case 9:
				{
					SetPlayerPos(playerid, -1026.87, -705.24, 135.50);
				}
				case 10:
				{
					SetPlayerPos(playerid, -1042.43, -693.56, 32.00);
				}
				case 11:
				{
					SetPlayerPos(playerid, -1071.51, -685.07, 32.35);
				}
				case 12:
				{
					SetPlayerPos(playerid, -1086.07, -624.35, 34.08);
				}
				case 13:
				{
					SetPlayerPos(playerid, -1075.54, -596.64, 32.00);
				}
				case 14:
				{
					SetPlayerPos(playerid, -1027.04, -623.25, 32.00);
				}
				case 15:
				{
					SetPlayerPos(playerid, -993.21, -625.96, 32.00);
				}*/
			}
		}
		case stats_snajper:
		{
			if(info)
			{
				SendClientMessageToAll(-1, "** {008ae6}%s (%d){/b} dolaczyl do areny {008ae6}/sniper{/b}. Dolacz i Ty.", playerNick(playerid), playerid);
				SendClientMessage(playerid, -1, "* Jesteœ na arenie: {008ae6}/sniper{/b} aby wyjsc wpisz {008ae6}/Aexit");
			}
			 
			GivePlayerWeapon(playerid, 34, 999);
			SetPlayerHealth(playerid, 20.000000);
			SetPlayerArmour(playerid, 0.0);
			SetPlayerColor(playerid,0xFFFFFF00);
			switch(random(7))
			{
				case 0:
				{
					SetPlayerPos(playerid,-969.4065,1033.1636,1345.0685);
					SetPlayerInterior(playerid, 10);
					SetPlayerVirtualWorld(playerid, 203);
				}
				case 1:
				{
					SetPlayerPos(playerid, -1131.9219,1028.9187,1345.7321);
					SetPlayerInterior(playerid, 10);
					SetPlayerVirtualWorld(playerid, 203);
				}
				case 2:
				{
					SetPlayerPos(playerid, -1127.9688,1092.3306,1345.7650);
					SetPlayerInterior(playerid, 10);
					SetPlayerVirtualWorld(playerid, 203);
				}
				case 3:
				{
					SetPlayerPos(playerid, -1101.6678,1019.4661,1342.0938);
					SetPlayerInterior(playerid, 10);
					SetPlayerVirtualWorld(playerid, 203);
				}
				case 4:
				{
					SetPlayerPos(playerid, -1057.9979,1070.3015,1341.3516);
					SetPlayerInterior(playerid, 10);
					SetPlayerVirtualWorld(playerid, 203);
				}
				case 5:
				{
					SetPlayerPos(playerid,-974.3973,1089.0225,1344.9792);
					SetPlayerInterior(playerid, 10);
					SetPlayerVirtualWorld(playerid, 203);
				}
				case 6:
				{
					SetPlayerPos(playerid, -972.9406,1041.4862,1352.7015);
					SetPlayerInterior(playerid, 10);
					SetPlayerVirtualWorld(playerid, 203);
				}
				case 7:
				{
					SetPlayerPos(playerid, -1132.9979,1078.3234,1353.4465);
					SetPlayerInterior(playerid, 10);
					SetPlayerVirtualWorld(playerid, 203);
				}
				
			}
		}
		case stats_arenagang:
		{
			if(!pInfo[playerid][player_gang])
			{
				SendClientMessage(playerid, COLOR_ERROR, ""chat" Aby do³¹czyæ do tej areny musisz byæ cz³onkiem gangu!");
				pInfo[playerid][player_arena] = 0;
			}
			else 
			{
				if(info)
				{
					SendClientMessageToAll(-1, "** {008ae6}%s (%d) {/b}dolaczyl do areny {008ae6}/ArenaGang{/b}. Dolacz i Ty.", playerNick(playerid), playerid);
					SendClientMessage(playerid, -1, " * Jesteœ na arenie: {008ae6}/ArenaGang{/b} aby wyjsc wpisz {008ae6}/Aexit");
				}
				 
				
				GivePlayerWeapon(playerid, 24, 999);
				GivePlayerWeapon(playerid, 25, 999);
				GivePlayerWeapon(playerid, 34, 999);
				
				SetPlayerHealth(playerid, 100.000000);
				SetPlayerArmour(playerid, 100.0);
				
				SetPlayerTeam(playerid, pInfo[playerid][player_gang] + MAX_PLAYERS);
				SetPlayerVirtualWorld(playerid, 204);
				SetPlayerInterior(playerid, 0);
				
				switch(random(3))
				{
					case 0:
					{
						SetPlayerPos(playerid, -70.300003051758, 2252.1000976563, 123.69999694824);
						SetPlayerFacingAngle( playerid, 4.68 );
					}
					case 1:
					{
						SetPlayerPos(playerid, -286.5, 2158.3999023438, 115.16);
						SetPlayerFacingAngle( playerid, 106.83 );
					}
					case 2:
					{
						SetPlayerPos(playerid, -291.5, 2368.8999023438, 112.16);
						SetPlayerFacingAngle( playerid, 4.68 );
					}
 				}
			}
		}

		case stats_dm1:
		{
			if(info)
			{
				SendClientMessageToAll(-1, "** {008ae6}%s (%d) {/b}dolaczyl do areny {008ae6}/Dm1{/b}. Dolacz i Ty.", playerNick(playerid), playerid);
				SendClientMessage(playerid, -1, " * Jesteœ na arenie: {008ae6}/Dm1{/b} aby wyjsc wpisz{008ae6} /Aexit");
			}
			GivePlayerWeapon(playerid,24,99999);
			GivePlayerWeapon(playerid,34,99999);
			GivePlayerWeapon(playerid,25,99999);
			SetPlayerHealth(playerid,100.0);
			SetPlayerArmour(playerid,100.0);
			switch(random(6))
			{
				case 0:
				{
					SetPlayerPos(playerid, 1995.9683,1852.4586,122.0156);
					SetPlayerInterior(playerid,0);
					SetPlayerVirtualWorld(playerid,205);
				}
				case 1:
				{
					SetPlayerPos(playerid,1991.5996,1880.0302,122.0156 );
					SetPlayerInterior(playerid,0);
					SetPlayerVirtualWorld(playerid,205);
				}
				case 2:
				{
					SetPlayerPos(playerid, 1934.9303,1913.1172,122.0156);
					SetPlayerInterior(playerid,0);
					SetPlayerVirtualWorld(playerid,205);
				}
				case 3:
				{
					SetPlayerPos(playerid, 1889.8220,1916.2408,122.0156);
					SetPlayerInterior(playerid,0);
					SetPlayerVirtualWorld(playerid,205);
				}
				case 4:
				{
					SetPlayerPos(playerid, 1976.3285,1941.0226,122.0156);
					SetPlayerInterior(playerid,0);
					SetPlayerVirtualWorld(playerid,205);
				}
				case 5:
				{
					SetPlayerPos(playerid,1995.4539,1968.3359,122.0156 );
					SetPlayerInterior(playerid,0);
					SetPlayerVirtualWorld(playerid,205);
				}
				case 6:
				{
					SetPlayerPos(playerid,1965.1685,1914.7169,130.9375 );
					SetPlayerInterior(playerid,0);
					SetPlayerVirtualWorld(playerid,205);
				}
			}
		}


		case stats_dm3:
		{
			if(info)
			{
				SendClientMessageToAll(-1, "** {008ae6}%s (%d) {/b}dolaczyl do areny {008ae6}/Dm3{/b}. Dolacz i Ty.", playerNick(playerid), playerid);
				SendClientMessage(playerid, -1, " * Jesteœ na arenie: {008ae6}/Dm1{/b} aby wyjsc wpisz{008ae6} /Aexit");
			}
			GivePlayerWeapon(playerid,25,99999);
			GivePlayerWeapon(playerid,34,99999);
			SetPlayerHealth(playerid,100.0);
			SetPlayerArmour(playerid,100.0);
			SetPlayerInterior(playerid,0);
			SetPlayerVirtualWorld(playerid,207);
			switch(random(4))
			{
				case 0:
				{
					SetPlayerPos(playerid, 1551.0114,-1114.2959,135.8281);
				}
				case 1:
				{
					SetPlayerPos(playerid,1550.4653,-1150.6349,135.8281 );
				}
				case 2:
				{
					SetPlayerPos(playerid, 1532.5967,-1141.0105,136.0831);
				}
				case 3:
				{
					SetPlayerPos(playerid,1497.6879,-1150.9760,135.8281);
				}
				case 4:
				{
					SetPlayerPos(playerid, 1493.3700,-1120.3842,135.8281);
				}
			}
		}

		case stats_dm2:
		{
			if(info)
			{
				SendClientMessageToAll(-1, "** {008ae6}%s (%d) {/b}dolaczyl do areny {008ae6}/Dm2{/b}. Dolacz i Ty.", playerNick(playerid), playerid);
				SendClientMessage(playerid, -1, " * Jesteœ na arenie: {008ae6}/Dm1{/b} aby wyjsc wpisz{008ae6} /Aexit");
			}
			GivePlayerWeapon(playerid,26,99999);
			GivePlayerWeapon(playerid,28,99999);
			SetPlayerHealth(playerid,100.0);
			SetPlayerArmour(playerid,100.0);
			SetPlayerInterior(playerid,0);
			SetPlayerVirtualWorld(playerid,206);
			switch(random(4))
			{
				case 0:
				{
					SetPlayerPos(playerid, 2546.8389,1354.8593,78.4764);
				}
				case 1:
				{
					SetPlayerPos(playerid,2547.9287,1331.8022,78.4764 );
				}
				case 2:
				{
					SetPlayerPos(playerid, 2569.1091,1342.0491,78.4764);
				}
				case 3:
				{
					SetPlayerPos(playerid, 2607.2402,1354.8485,78.4764);
				}
				case 4:
				{
					SetPlayerPos(playerid, 2607.5037,1331.5819,78.4764);
				}
			}
		}

	}
}