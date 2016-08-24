/*
          Duel / solo system [NOT VERSION]
      (c) Copyright 2013-2014 by mrdrifter
 
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
	  @date      : 16 grudnia 2013
	  @update    : 3 stycznia 2014
  
 */ 
stock DuelInit()
{
	Create3DTextLabel(" ", 0, -2000.0, 2000.0, 2000.0, 30.0, 0, 1);
	CreateDynamic3DTextLabel(" ", 0, -2000.0, 2000.0, 2000.0, 30.0, 0, 1);
	CreateDynamicObject(19272, -1982.9070,192.9369,-38.6595, 0.000000, 0.000000, 0.000000);
	
	
	CreateObject(19272, 139.11208, 1738.20386, 1508.84705,   0.00000, 0.00000, 0.00000);
	return 1;
}
CMD:soloweapons(playerid, params[])
{

	new weapons_str[256] = "ID\t Nazwa:";
	for(new i = 20; i < 42;i++)
	{
		if(!DuelWeapon(i)) continue;
 
		format(weapons_str, sizeof weapons_str, "%s%d\t %s\n", weapons_str, i, GetWeaponNameEx(i));
	}
	ShowPlayerDialog(playerid, 9999, DIALOG_STYLE_MSGBOX, "Lista Broni (/solo)", weapons_str, "Zamknij", "");
	return 1;
}
CMD:setduel(playerid, cmdp[])
{
	
	if(pInfo[playerid][player_nopduel] == true)
	{
		pInfo[playerid][player_nopduel] = false;
		SendClientMessage(playerid, COLOR_INFO, ""chat" Odblokowa³eœ(aœ) zaproszenia na solo."); //wygenerowany
	}
	else
	{
		pInfo[playerid][player_nopduel] = true;
		SendClientMessage(playerid, COLOR_INFO, ""chat" Zablokowa³eœ(aœ) zaproszenia na solo."); //wygenerowany
	}
	return 1;
}
CMD:solo(playerid, cmdtext[])
{
	if(GetTickCount() < GetPVarInt(playerid, "UnBlockDuel"))
    {
		new str[128];
  		format(str, sizeof(str), "Tej komendy mo¿na u¿yæ dopiero za {b}%d{/b} sekund!", ((GetPVarInt(playerid, "UnBlockDuel") - GetTickCount()) / 1000) + 1);
    	return SendClientMessage(playerid, COLOR_INFO, str);
	}
	
	new id, bron, bron2;
	if(sscanf(cmdtext, "ddd", id, bron, bron2) && sscanf(cmdtext, "dd", id, bron)) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: {b}/solo <id/nick gracza> <broñ> <bron 2 (opcjonalnie)>"); //wygenerowany
		return 1;
	}
	if(id == playerid) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz wyzwaæ na pojedynek samego siebie..."); 
		return 1;
	}
	
	if(!IsPlayerConnected(id)) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Ten nie jest pod³¹czony!"); //wygenerowany
		return 1;
	}
	if(pInfo[id][player_nopduel] == true)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Ten Gracz ma wy³¹czone zaproszenia na solo!"); 
		return 1;
	}
	if(pInfo[id][player_arena] > 0) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz aktualnie jest na arenie."); //wygenerowany
		return 1;
	}
	if(pInfo[id][player_jail]) 
	{
		SendClientMessage(playerid, 0xFF4444FF, "» Ten gracz aktualnie jest w wiêzieniu"); //wygenerowany
		return 1;
	}
	if(is_event(id)) 
	{
		SendClientMessage(playerid, 0xFF4444FF, "» Ten gracz aktualnie uczestniczy w evencie.");  
		return 1;
	}
	if(pInfo[id][player_duel]) 
	{
		SendClientMessage(playerid, 0xFF4444FF, "» Ten gracz aktualnie jest na solo.");  
		return 1;
	}
	if(pInfo[id][player_gangWarTeam] != 0)
	{	
		SendClientMessage(playerid, 0xFF4444FF, "» Ten gracz aktualnie jest na wojnie gangów");  
		return 1;
	}
	if(!DuelWeapon(bron))
	{
		SendClientMessage(playerid, 0xFF4444FF, "» Wybrana broñ jest nie dozwolona. Dozwolone bronie /soloweapons.");  
		return 1;
	}
	
	if(!DuelWeapon(bron2) && bron2 != 0)
	{
		bron2=0;//xd
		//SendClientMessage(playerid, 0xFF4444FF, "» Wybrana broñ (druga) jest nie dozwolona. Dozwolone bronie /soloweapons.");  
		return 1;
	}
	
	 
	pInfo[playerid][player_duel_toplayer] = id;
	
	pInfo[playerid][player_duel_weapon][0] = bron;
	pInfo[id][player_duel_weapon][0] = bron;
	
	if(bron2 > 0){
		pInfo[playerid][player_duel_weapon][1] = bron2;
		pInfo[id][player_duel_weapon][1] = bron2;
	}
	
	/*
	pInfo[id][player_duel_toplayer] = playerid;
	pInfo[id][player_duel_weapon][0] = bron;
	
	SetPlayerVirtualWorld(playerid, 600 + playerid);
	pInfo[id][player_duel_vw] = GetPlayerVirtualWorld(playerid);
	pInfo[playerid][player_duel_vw] = GetPlayerVirtualWorld(playerid);
	
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Wywa³eœ gracza na solo.");
	format(string2, sizeof(string2), " %s wyzwa³ Ciê na pojedynek solo broni¹ %s\n\nCzy akceptujesz pojedynek?", playerNick(playerid), GetWeaponNameEx(bron));
	Dialog_Show(id, DIALOG_DUEL, DIALOG_STYLE_MSGBOX, "Pojedynek solo", string2, "Tak", "Nie");
	*/
	
	Dialog_Show(playerid, DIALOG_DUEL_ARENA, DIALOG_STYLE_LIST, "Pojedynek solo - Arena", "WH\nKlatka", "Wybierz", "Anuluj");
	return 1;
}

CMD:duel(playerid, cmdtext[]) //tak wiem kopiowanie komendy bez sensu ale to na szybko ; D
{
	if(GetTickCount() < GetPVarInt(playerid, "UnBlockDuel"))
    {
		new str[128];
  		format(str, sizeof(str), "Tej komendy mo¿na u¿yæ dopiero za {b}%d{/b} sekund!", ((GetPVarInt(playerid, "UnBlockDuel") - GetTickCount()) / 1000) + 1);
    	return SendClientMessage(playerid, COLOR_INFO, str);
	}
	
		
	new id, bron, bron2;
	if(sscanf(cmdtext, "ddd", id, bron, bron2) && sscanf(cmdtext, "dd", id, bron)) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: {b}/solo <id/nick gracza> <broñ> <bron 2 (opcjonalnie)>"); //wygenerowany
		return 1;
	}
	if(id == playerid) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz wyzwaæ na pojedynek samego siebie..."); 
		return 1;
	}
	
	if(!IsPlayerConnected(id)) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Ten nie jest pod³¹czony!"); //wygenerowany
		return 1;
	}
	if(pInfo[id][player_nopduel] == true)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Ten Gracz ma wy³¹czone zaproszenia na solo!"); 
		return 1;
	}
	if(pInfo[id][player_arena] > 0) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz aktualnie jest na arenie."); //wygenerowany
		return 1;
	}
	if(pInfo[id][player_jail]) 
	{
		SendClientMessage(playerid, 0xFF4444FF, "» Ten gracz aktualnie jest w wiêzieniu"); //wygenerowany
		return 1;
	}
	if(is_event(id)) 
	{
		SendClientMessage(playerid, 0xFF4444FF, "» Ten gracz aktualnie uczestniczy w evencie.");  
		return 1;
	}
	if(pInfo[id][player_duel]) 
	{
		SendClientMessage(playerid, 0xFF4444FF, "» Ten gracz aktualnie jest na solo.");  
		return 1;
	}
	if(pInfo[id][player_gangWarTeam] != 0)
	{	
		SendClientMessage(playerid, 0xFF4444FF, "» Ten gracz aktualnie jest na wojnie gangów");  
		return 1;
	}
	if(!DuelWeapon(bron))
	{
		SendClientMessage(playerid, 0xFF4444FF, "» Wybrana broñ jest nie dozwolona. Dozwolone bronie /soloweapons.");  
		return 1;
	}
	
	if(!DuelWeapon(bron2) && bron2 != 0)
	{
		bron2=0;//elo
		//SendClientMessage(playerid, 0xFF4444FF, "» Wybrana broñ (druga) jest nie dozwolona. Dozwolone bronie /soloweapons.");  
		return 1;
	}
	
	 
	pInfo[playerid][player_duel_toplayer] = id;
	
	pInfo[playerid][player_duel_weapon][0] = bron;
	pInfo[id][player_duel_weapon][0] = bron;
	
	if(bron2 > 0){
		pInfo[playerid][player_duel_weapon][1] = bron2;
		pInfo[id][player_duel_weapon][1] = bron2;
	}
	
	/*
	pInfo[id][player_duel_toplayer] = playerid;
	pInfo[id][player_duel_weapon][0] = bron;
	
	SetPlayerVirtualWorld(playerid, 600 + playerid);
	pInfo[id][player_duel_vw] = GetPlayerVirtualWorld(playerid);
	pInfo[playerid][player_duel_vw] = GetPlayerVirtualWorld(playerid);
	
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Wywa³eœ gracza na solo.");
	format(string2, sizeof(string2), " %s wyzwa³ Ciê na pojedynek solo broni¹ %s\n\nCzy akceptujesz pojedynek?", playerNick(playerid), GetWeaponNameEx(bron));
	Dialog_Show(id, DIALOG_DUEL, DIALOG_STYLE_MSGBOX, "Pojedynek solo", string2, "Tak", "Nie");
	*/
	
	Dialog_Show(playerid, DIALOG_DUEL_ARENA, DIALOG_STYLE_LIST, "Pojedynek solo - Arena", "WH\nKlatka", "Wybierz", "Anuluj");
	return 1;
}
Dialog:DIALOG_DUEL_ARENA(playerid, response, listitem, inputtext[])
{
	new id = pInfo[playerid][player_duel_toplayer];
	if(!IsPlayerConnected(id)) 
	{
		ResetDuelInfo(playerid,id);
		return 0;
	}
	if(response)
	{
		SetPVarInt(playerid, "UnBlockDuel", GetTickCount() + 10000);
		
		if(!IsPlayerConnected(id))
		{
			InfoBox(playerid, "Ten gracz wyszed³ z servera.");
			return 1;
		}
		if(pInfo[id][player_duel])
		{
			InfoBox(playerid, "Ten gracz ju¿ aktualnie ma pojedynek.");
			return 1;
		}
		pInfo[id][player_duel_toplayer] = playerid;
		
		pInfo[id][player_duel_arena] = listitem;
		pInfo[playerid][player_duel_arena] = listitem;
		
 		pInfo[id][player_duel_vw] = 600 + playerid;
		pInfo[playerid][player_duel_vw] = 600 + playerid;
		
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Wyzwa³eœ gracza na solo.");
		format(string2, sizeof(string2), " %s wyzwa³ Ciê na pojedynek solo broni¹ %s + %s\n\nCzy akceptujesz pojedynek?", playerNick(playerid), GetWeaponNameEx(pInfo[id][player_duel_weapon][0]),  GetWeaponNameEx(pInfo[id][player_duel_weapon][1]));
		Dialog_Show(id, DIALOG_DUEL, DIALOG_STYLE_MSGBOX, "Pojedynek solo", string2, "Tak", "Nie");
		//format(string2, sizeof(string2), "\n|%s|wyzwa³|Ciê|na|pojedynek|solo|broni¹|%s\n\n|Czy|akceptujesz|pojedynek?", playerNick(playerid), GetWeaponNameEx(pInfo[id][player_duel_weapon][0]));
		//Dialog_Show(id, DIALOG_DUEL, DIALOG_STYLE_MSGBOX, "Pojedynek solo", colormenage("FF9933",string2), "Tak", "Nie");
	}
	return 1;
}
stock ResetDuelInfo(playerid, id)
{
	pInfo[playerid][player_duel_toplayer] = -1;
	pInfo[playerid][player_duel_vw] = 0;
	pInfo[playerid][player_duel_weapon][0] = 0;
	pInfo[playerid][player_duel_weapon][1] = 0;
	pInfo[playerid][player_duel] = false;
	
	if(!IsPlayerConnected(id)) return;
	pInfo[id][player_duel_toplayer] = -1;
	pInfo[id][player_duel] = false;
	pInfo[id][player_duel_weapon][0] = 0;
	pInfo[id][player_duel_weapon][1] = 0;
	pInfo[id][player_duel_vw] = 0;
}
stock DuelStart(playerid)
{
	new id = pInfo[playerid][player_duel_toplayer];
	if(!IsPlayerConnected(id)) 
	{
		ResetDuelInfo(playerid,id);
		return 0;
	}
	pInfo[playerid][player_duel] = true;
	pInfo[id][player_duel] = true;
	
	 
	if(pInfo[id][player_duel_toplayer] != playerid)
	{
		ResetDuelInfo(playerid, id);
		return 1;
	}
	if(!IsPlayerConnected(id) || !IsPlayerConnected(playerid))
	{
		ResetDuelInfo(playerid, id);
		return 1;
	}
	if(removeIsEvent(playerid) != 0) SendClientMessage(playerid, COLOR_ERROR, " "chat" Zosta³eœ(aœ) wypisany(a) z eventu z powodu rozpoczêcia solo!");
		
	SetPlayerVirtualWorld(playerid, pInfo[playerid][player_duel_vw]);
	
	SetPlayerPos(playerid, ArenySolo_Data[ pInfo[playerid][player_duel_arena] ][arr_spawn1][0], ArenySolo_Data[pInfo[playerid][player_duel_arena]][arr_spawn1][1], ArenySolo_Data[pInfo[playerid][player_duel_arena]][arr_spawn1][2]);
	SetPlayerFacingAngle(playerid, ArenySolo_Data[pInfo[playerid][player_duel_arena]][arr_spawn1][3]);
	
	SetCameraBehindPlayer(playerid);
	ResetPlayerWeapons(playerid);
	GivePlayerWeapon(playerid, pInfo[playerid][player_duel_weapon][0], 600);
	GivePlayerWeapon(playerid, pInfo[playerid][player_duel_weapon][1], 600);
	TogglePlayerControllable(playerid, false);
	SetPlayerInterior(playerid, ArenySolo_Data[pInfo[playerid][player_duel_arena]][arr_interior]);
	
	SetPlayerHealth(playerid, 100.0);
	SetPlayerArmour(playerid, 100.0);

	SetPlayerVirtualWorld(id,	pInfo[playerid][player_duel_vw]);
	SetPlayerPos(id, ArenySolo_Data[pInfo[playerid][player_duel_arena]][arr_spawn2][0], ArenySolo_Data[pInfo[playerid][player_duel_arena]][arr_spawn2][1],ArenySolo_Data[pInfo[playerid][player_duel_arena]][arr_spawn2][2]);
	SetPlayerFacingAngle(id, ArenySolo_Data[pInfo[playerid][player_duel_arena]][arr_spawn2][3]);
	SetCameraBehindPlayer(id);
	SetPlayerInterior(id, ArenySolo_Data[pInfo[playerid][player_duel_arena]][arr_interior]);
	
	ResetPlayerWeapons(id);
	GivePlayerWeapon(id, pInfo[playerid][player_duel_weapon][0], 600);
	GivePlayerWeapon(id, pInfo[playerid][player_duel_weapon][1], 600);
	
	TogglePlayerControllable(id, false);
	
	SetPlayerArmour(id, 100.0);
	SetPlayerHealth(id, 100.0);
	
	pInfo[playerid][player_duel_timer] = 4;
	pInfo[id][player_duel_timer] = 4;
	
	return 1;
}
CMD:dexit(playerid, params[])
{
	if(!pInfo[playerid][player_duel]) 
	{
		SendClientMessage(playerid, COLOR_LIME_GREEN, ""chat" Nie jesteœ na solo.");
		return 1;
	}
	DuelWin(pInfo[playerid][player_duel_toplayer]);
	SetPlayerSpawn(playerid);

	SendClientMessage(playerid, COLOR_LIME_GREEN, ""chat" Zrezygnowa³eœ z solo.");
	return 1;
}
duel_OnPlayerDeath(playerid, killerid)
{
	if(pInfo[playerid][player_duel])
	{
		if(killerid != INVALID_PLAYER_ID)
			DuelWin(killerid);
		else
			DuelWin(pInfo[playerid][player_duel_toplayer]);
		
	}
	return 1;
}
 
stock DuelWin(playerid)
{
	new id = pInfo[playerid][player_duel_toplayer];
	
	if(!IsPlayerConnected(id)) 
	{
		ResetDuelInfo(playerid,id);
		return 0;
	}
	new Float:hp, Float:armor;
	GetPlayerHealth(playerid, hp);
	GetPlayerArmour(playerid, armor);
		
	SendClientMessageToAll(-1, " Pojedynek Solo {008ae6}%s {/b}vs {008ae6}%s{/b} po raz {008ae6}%d{/b} wygrywa {008ae6}%s{/b} (%.1f HP) ", playerNick(playerid), playerNick(id), addPointEvent(playerid, stats_duel_win), playerNick(playerid), hp+armor);
	GivePlayerScore(playerid, 20);
	
	achievement(playerid, 9);
	addPointEvent(id, stats_duel_lost);
	#if defined ADUIO_PLUGIN
	PlayCompleteMissionSound(playerid);
	#endif
	ResetDuelInfo(playerid, id);
	SetPlayerSpawn(id);

	OnPlayerSpawn(playerid);
	return 1;
}
Dialog:DIALOG_DUEL(playerid, response, listitem, inputtext[])
{
	new id = pInfo[playerid][player_duel_toplayer];
	if(!IsPlayerConnected(id)) 
	{
		ResetDuelInfo(playerid,id);
		return 0;
	}
	if (response)
	{
		if(!IsPlayerConnected(id))
		{
			InfoBox(playerid, "Ten gracz wyszed³ z servera.");
			return 1;
		}
		
		if(pInfo[id][player_duel_toplayer] != playerid)
		{
			InfoBox(playerid, "Ten gracz wyzwa³ ju¿ innego gracza na pojedynek.");
			return 1;
		}
		if(pInfo[id][player_duel])
		{
			InfoBox(playerid, "Ten gracz ju¿ aktualnie ma pojedynek.");
			return 1;
		}
	
		DuelStart(playerid);
		
		SendClientMessage(id, COLOR_GREEN, " %s (%d) zaakceptowa³ Twoje wyzwanie na solo!", playerNick(playerid), playerid);
		SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} *{/b} Akceptowa³eœ pojedynek solo z %s (%d)", playerNick(id), id);
	}
	else
	{
		if(pInfo[id][player_duel_toplayer] != pInfo[playerid][player_duel_toplayer]) return 1;
		
		
		SendClientMessage(playerid, COLOR_RED, " %s (%d) nie akceptowa³ pojedynek solo!", playerNick(pInfo[playerid][player_duel_toplayer]), pInfo[playerid][player_duel_toplayer]);
		SendClientMessage(pInfo[playerid][player_duel_toplayer], COLOR_GREEN, "{FFFFFF} *{/b} Odrzuci³eœ pojedynek solo z %s (%d)", playerNick(playerid), playerid);
		
		ResetDuelInfo(playerid, playerid);
	}
	return 1;
}


stock DuelWeapon(weaponid)
{
	switch(weaponid)
	{
		case 22..34, 40..43: return 1;
	}
	return 0;
}