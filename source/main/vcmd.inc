/*
          Vip commands [NOT VERSION]
      (c) Copyright 2013-2014 by mrdrifter
 
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
	  @date      : 16 listopada 2013
	  @update    : 3 stycznia 2014
  
 */ 
 
CMD:vogl(playerid, params[]) 
{
	RankVip(playerid);
	if(pInfo[playerid][player_mute]) 
		return SendClientMessage(playerid, COLOR_ERROR, ""chat" Nie mo�esz u�y� tej komendy poniewa� jeste� uciszony");
	if(gmData[timer_vip_ann] > 0)return SendClientMessage(playerid, COLOR_ERROR, ""chat" Aktualnie ju� trwa jedno og�oszenie!"); //wygenerowany
	
	if(GetPVarInt(playerid, "ogl_v") > gettime()) 
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Ogloszenie mo�na pisa� co 90 sekund!"); //wygenerowany
		return 1;
	}
	
	
	if(strlen(params) >= 75) return SendClientMessage(playerid, COLOR_WHITE, "Podany tekst jest za d�ugi");
	
	new text[81];
	if(sscanf(params, "s[80]", text)) return SendClientMessage(playerid, COLOR_WHITE, "Podany tekst jest za d�ugi"); //wygenerowany
	SetPVarInt(playerid, "ogl_v", gettime() + 85);
	if(strlen(text) > 15 && strfind(text, "~n~") == -1)
	{
		strins(text, "...~n~", 15);
	}
	if(strlen(text) > 40 && strfind(text, "~n~") == -1)
	{
		strins(text, "...~n~", 40);
	}
	new voglcnt;
	for(new i=0; i<strlen(text); i++)
	{
		if(text[i] == '~') voglcnt++;
	}
	if(voglcnt%2 != 0) return SendClientMessage(playerid, COLOR_ERROR, ""chat" W tek�cie znajduje si� {b}nieparzysta{/b} liczba znak�w ~ co spowoduje b��d!"); //wygenerowany

	ShowVipAnn(playerid, text);
	return 1;
}
CMD:vbank(playerid, params[])
{
	RankVip(playerid);
	
	Dialog_BankMenu(playerid);
	
	return 1;
}

CMD:vgranaty(playerid, params[])
{
	RankVip(playerid);
	
	GivePlayerWeapon(playerid, 16, 4);
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Dosta�e� granaty.");
	return 1;
}
CMD:vjetpack(playerid, params[])
{
	if(!pInfo[playerid][player_admin])RankVip(playerid);
	
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Dosta�e� jetpack.");
	return 1;
}

CMD:vdotacja(playerid, params[])
{
	RankVip(playerid);
	
	if(pInfo[playerid][vip_dot] == true) return SendClientMessage(playerid, COLOR_ERROR, ""chat" Ju� otrzyma�e� dotacj� dla Vipa!");
	
	pInfo[playerid][vip_dot] = true;
	GivePlayerMoney(playerid, 10000);
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Otrzyma�e� dotacje.");
	return 1;
}

CMD:vzestaw(playerid, cmdtext[])
{
	RankVip(playerid);
	if(IsPlayerEventItp(playerid))
	{
		InfoBox(playerid, "Nie mo�esz teraz tego zrobi�. ");
		return 1;
	}
	
	GivePlayerWeapon(playerid, 16, 50);
	GivePlayerWeapon(playerid, 31, 1000);
	GivePlayerWeapon(playerid, 32, 1000);
	GivePlayerWeapon(playerid, 34, 1000);
	GivePlayerWeapon(playerid, 41, 1000);
	GivePlayerWeapon(playerid, 24, 1000);
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Otrzyma�e� zestaw broni Vipa!");
	return 1;
}

CMD:vsay(playerid, cmdtext[])
{
	RankVip(playerid);
	if(pInfo[playerid][player_mute]) 
		return SendClientMessage(playerid, COLOR_ERROR, ""chat" Nie mo�esz u�y� tej komendy poniewa� jeste� uciszony");
	new vtekst[90];
	if(sscanf(cmdtext, "s[90]", vtekst)) return SendClientMessage(playerid, COLOR_ERROR, ""chat" U�yj: {b}/vsay <tekst>{/b}");
	
	if(strlen(vtekst) < 1 || strlen(vtekst) > 90) return SendClientMessage(playerid, COLOR_ERROR, ""chat" Tekst musi mie� 1-90 znak�w!");
	
	
	if(strfind(vtekst, "jebac") != -1 || strfind(vtekst, "jeba�") != -1 || strfind(vtekst, "chuj") != -1 || strfind(vtekst, "pizda") != -1 || strfind(vtekst, "kurwa") != -1 || strfind(vtekst, "lewak") != -1)
	{
		SendClientMessageToAll(COLOR_VIP, "[Vip] %s (%d) >> {ff0000}chcia�em napisa� co� brzydkiego ale zosta�em wyrzucony ;|", playerNick(playerid), playerid);
		Kick(playerid);
	}
	else SendClientMessageToAll(COLOR_VIP, "[Vip] %s (%d) >> %s", playerNick(playerid), playerid, vtekst);
	return 1;
}

CMD:vrepair(playerid, cmdtext[])
{
	RankVip(playerid);
	
	new id;
	if(sscanf(cmdtext, "u", id)) return SendClientMessage(playerid, COLOR_ERROR, ""chat" U�yj: /vrepair <id gracza>");
	
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, ""chat" Ten  nie jest pod��czony!");
	if(!IsPlayerInAnyVehicle(id)) return SendClientMessage(playerid, COLOR_ERROR, ""chat" Ten  nie siedzi w poje�dzie!");
	
	RepairVehicle(GetPlayerVehicleID(id));
	
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Naprawi�e� pojazd graczowi {b}%s{/b} (%d).", playerNick(id), id);
	
	SendClientMessage(id, COLOR_GREEN, ""chat" Vip {b}%s{/b} (%d) naprawi� Ci pojazd.", playerNick(playerid), playerid);
	return 1;
}


CMD:autofix(id, cmdtext[])
{
	RankVip(id);
	
	 
	if(!IsPlayerInAnyVehicle(id)) return SendClientMessage(id, COLOR_ERROR, ""chat" Nie jestes w poje�dzie!");
	
	RepairVehicle(GetPlayerVehicleID(id));
	
	SendClientMessage(id, COLOR_GREEN, ""chat" Naprawi�e� pojazd graczowi {b}%s{/b} (%d).", playerNick(id), id);
	 
	return 1;
}

CMD:vheal(playerid, cmdtext[])
{
	RankVip(playerid);
	
	if(GetPVarInt(playerid, "vheal") > gettime()) 
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Mozesz uleczac co 10 sekund!!"); //wygenerowany
		return 1;
	}
	SetPVarInt(playerid, "vheal", gettime() + 10);
	
	new id;
	if(sscanf(cmdtext, "u", id)) return SendClientMessage(playerid, COLOR_ERROR, ""chat" U�yj: /vheal <id gracza>");
	
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, ""chat" Ten  nie jest pod��czony!");
	if(is_event(id) || pInfo[id][player_arena] > 0) return SendClientMessage(playerid, COLOR_ERROR, ""chat" Ten  jest teraz na evencie lub na arenie!");
	if(pInfo[id][player_last_damage] > gettime()) 
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Ten Gracz nie mo�e teraz zosta� uzdrowionym.");
		return 1;
	}
	if(pInfo[id][player_gangWarTeam] != 0)
	{	
		SendClientMessage(playerid, COLOR_ERROR, ""chat"  Ten gracz aktualnie jest na wojnie gang�w");  
		return 1;
	}
	if(pInfo[id][player_duel]) 
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat"Ten gracz aktualnie jest na solo.");  
		return 1;
	}
	
	SetPlayerHealth(id, 100.0);
	
	SendClientMessage(playerid, COLOR_INFO, ""chat" Uzdrowi�e� gracza {b}%s{/b} (%d).", playerNick(id), id);
	SendClientMessage(id, COLOR_GREEN, ""chat" Vip {b}%s{/b} (%d) uzdrowi� Ci�.", playerNick(playerid), playerid);
	return 1;
}

CMD:varmor(playerid, cmdtext[])
{
	RankVip(playerid);
	
	if(GetPVarInt(playerid, "varmor") > gettime()) 
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Mozesz uleczac co 10 sekund!!"); //wygenerowany
		return 1;
	}
	SetPVarInt(playerid, "varmor", gettime() + 10);
	
	SetPlayerArmour(playerid, 100.0);
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Otrzyma�e� kamizelk�.");
	return 1;
}

CMD:vcolor(playerid, cmdtext[])
{
	RankVip(playerid);
	
	SetPlayerColor(playerid, COLOR_VIP);
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Ustawi�e� sobie kolor VIP.");
	return 1;
}

CMD:vpozostalo(playerid, cmdtext[])
{
	RankVip(playerid);
	
	new str_enddate[50];
	UnixTimetoDate(pInfo[playerid][player_vip], str_enddate);

	SendClientMessage(playerid, COLOR_GREEN, ""chat" Twoje konto VIP wygasa za {b}%s{/b}.", str_enddate);
	return 1;
}

CMD:vinvisible(playerid, cmdtext[])
{
	RankVip(playerid);
	SetPlayerColor(playerid, 0xFFFFFF00);
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Ustawi�e� sobie niewidzialny kolor.");
	return 1;
}
 
CMD:vpomoc(playerid, params[])
{
	RankVip(playerid);
	
	new vcmd[669];
	strcat(vcmd, "{F5DC0B}Vip{FFFFFF}\n");
	strcat(vcmd, "/vpozostalo - wy�wietla date wyga�ni�cia twojego konta Vip.\n");//
	strcat(vcmd, "/vinvisible - Niewidzialny nick");
	strcat(vcmd, "/vjetpack - dajesz sobie jetpacka.\n");//
	strcat(vcmd, "/vheal - uleczasz si� za darmo.\n");//
	strcat(vcmd, "/varmor - dostajesz kamizelk� za darmo.\n");//
	strcat(vcmd, "/vsay <tekst> - piszesz na czacie jako Vip.\n");//
	strcat(vcmd, "/vrepair <id gracza> - naprawiasz graczowi pojazd.\n");//
	strcat(vcmd, "/vdotacja - dostajesz doracj�.\n");//
	strcat(vcmd, "/vcolor - ustawnianie ��tego koloru nicku.\n");//
	strcat(vcmd, "/vzestaw - otrzymujesz zestaw broni Vipa.\n");
	strcat(vcmd, "/vbank - otwierasz dialog banku.\n");
	strcat(vcmd, "/vogl - piszesz na chacie og�szenie");
	strcat(vcmd, "/vgranaty - otrzymujesz granaty");
 	InfoBox(playerid, vcmd);
	return 1;
}
