/*
            Admin commands 1.0
      (c) Copyright 2013-2014 by mrdrifter, Game
 
	  @author    : mrdrifter (http://p4serv.pl/__drifter__/), Game
	  @date      : 14 grudnia 2013
	  @update    : 31 grudnia 2013
  
 */
 
stock ShowImportantMessage(playerid)
{
	static Msg[2048], qquery[256];
	Msg[0]=0;qquery[0]=0;
	
	format(qquery, 256,"SELECT Wiadomosc FROM "prefix"_notify WHERE id=1");
	m_query(qquery);
	mysql_store_result();
	mysql_fetch_row(Msg);
	mysql_free_result();

    for (new i = 0, x=strlen(Msg)-1; i < x; i++)
    {
        if (Msg[i] == '\\') {
            if (Msg[i + 1] == 'n') {
                strdel(Msg, i, i + 2);
                strins(Msg, "\n", i, sizeof (Msg));
            }else  if (Msg[i + 1] == 't') {
                strdel(Msg, i, i + 2);
                strins(Msg, "\t", i, sizeof (Msg));
            }
        }
    }
	
	Dialog_Show(playerid,DIALOG_NOTIFY,DIALOG_STYLE_MSGBOX,"Wa¿na wiadomoœæ (/notify)",Msg,"OK","");
	return 1;
}
	
CMD:notify(playerid,params[])
{
	ShowImportantMessage(playerid);
	return 1;
}
	
RIA:chatfrompa(admin[], text[])
{
	systemprintf("chat", true, "(WEB) %s -> %s", admin, text);
	
	
	if(!strcmp(text, "/okick", true, 6) && strlen(text) > 7)
	{
		return ria_okick(admin, text[6]);
	}
	if(!strcmp(text, "/omute", true, 6) && strlen(text) > 7)
	{
		return ria_omute(admin, text[6]);
	}
	
	
 	if(text[0] == '@')
	{
		format(string2, sizeof(string2), "[@ CHAT] %s (WEB): {FF0066}%s", admin, text[1]);
		SendAdminsMessage(COLOR_RED, string2);
		nsqp_SendSocketReply("Wys³ano wiadomoœæ do adminroom");

		return 1;
	}
	if(text[0] == '$')
	{
	
		format(string2, sizeof(string2), "[MOD CHAT] %s (WEB): {CC00CC}%s", admin, text[1]);
		SendAdminsMessage(COLOR_GREEN, string2);
		SendModsMessage(COLOR_GREEN, string2);
		nsqp_SendSocketReply("Wys³ano wiadomoœæ na chat mod.");

		return 1;
	}
	nsqp_SendSocketReply("Wys³ano wiadomoœæ");
	SendClientMessageToAll(0x990000FF, "[WEB] %s{FFFFFF}: %s", admin, text);
	
	return 1;
}
 
RIA:omute(admin[], params[])
{	
	new id, czas, reason[25];
	if(sscanf(params, "dds[25]", id, czas, reason))
	{
		nsqp_SendSocketReply("Uzyj /omute [id] [czas [w sekundach]] [powod]");
		return 1;
	}
	 
	if(czas < 1 || czas > 180)
	{
		nsqp_SendSocketReply("Maksymalnie 3 min a minimalnie 1 s.");
		return 1;
	}
	if(!IsPlayerConnected(id))
	{
		nsqp_SendSocketReply("Podany gracz nie jest pod³¹czony");
		return 1;
	}
	if(IsPlayerNPC(id)) return nsqp_SendSocketReply("» Ten gracz nie jest pod³¹czony!");  
	pInfo[id][player_mute] = czas;
 
	SendClientMessageToAll(0x990000FF, "[WEB] %s{FFFFFF}: uciszy³ offline gracza %s za %s na %d sekund.", admin, pInfo[id][player_name], reason, czas);
	nsqp_SendSocketReply("Gracz zostal ucziszony");

 	return 1;
}

RIA:okick(admin[], cmdtext[])
{ 
	new id, powod[60];
	if(sscanf(cmdtext, "us[60]", id, powod)) return nsqp_SendSocketReply("U¿yj: /okick [id] [powód]");  
	
	if(!IsPlayerConnected(id)) return nsqp_SendSocketReply("Ten gracz nie jest pod³¹czony!");  
	if(IsPlayerNPC(id)) return nsqp_SendSocketReply("Ten gracz nie jest pod³¹czony!");  
	if(strlen(powod) < 1 || strlen(powod) > 60) return nsqp_SendSocketReply("Powód musi mieæ 1-60 znaków!");  
	
	AddPlayerPenalty(id, P_KICK, INVALID_PLAYER_ID, 0, powod); 
	SendClientMessageToAll(0x990000FF, "[WEB] %s{FFFFFF}: wyrzuci³ offline gracza %s za %s", admin,pInfo[id][player_name], powod);

	nsqp_SendSocketReply("Gracz zostal wyrzucony");
	systemprintf("chat", true, "(WEB) Wyrzucono gracza %s (%d) przez %s powod %s", pInfo[id][player_name], id, admin, powod);

	return 1;
}

RIA:infoallplayers(player[], cmdtext[])
{
	new str[512], name[24], Float:Pos[4], count;
	
	
	str = "{\"outplayers\":{";
		 

	for(new i;i<MAX_PLAYERS;i++)
	{
		if( !IsPlayerConnected(i) ) continue;
		
		GetPlayerName(i, name, 24);
		GetPlayerPos(i, Pos[0], Pos[1], Pos[2]);
		GetPlayerHealth(i, Pos[3]);
		
 		format(str, sizeof(str), "%s\"p%d\":{\"id\":%d, \"uid\":%d, \"name\":\"%s\", \"pos\":{\"x\":%.1f,\"y\":%.1f, ,\"z\":%.1f}, \"health\":%.1f},", str, i,i,pInfo[i][player_id], name, Pos[0], Pos[1], Pos[2], Pos[3]);
		count++;
	}
	if(!count) return nsqp_SendSocketReply("no data available");
	
	str[strlen(str)-1] = EOS;
	strcat(str, "}}");
	
	nsqp_SendSocketReply(str);
	return 1;
}
CMD:atp(playerid,params[])
{
	RankAdmin(playerid, R_JADMIN);
	new pos[3];
	sscanf(params,"p<,>fff",pos[0],pos[1],pos[2]);
	SetPlayerPos(playerid,pos[0],pos[1],pos[2]);
	return 1;
}

CMD:atp2(playerid,params[])
{
	RankAdmin(playerid, R_JADMIN);
	 
	SetPlayerPos(playerid,1474.13, -905.71, 59.50);
	return 1;
}
CMD:cspawn(playerid, params[])
{	
	RankAdmin(playerid, R_VICEHEADADMIN);
 	
    if(loadspawns >= MAX_SPAWNS) 
	{
		SendClientMessage(playerid, -1, "MAX_SPAWNS error");
		return 1;
	}
	new i = loadspawns;
	new Float:x, Float:y, Float:z, Float:angle;
	GetPlayerPos(playerid, x,y,z);
	GetPlayerFacingAngle(playerid, angle);
	Spawns_player[i][0] = x;
	Spawns_player[i][1] = y;
	Spawns_player[i][2] = z;
	Spawns_player[i][3] = angle;
	m_query("insert into "prefix"_spawns (pos_x,pos_y,pos_z,pos_a) VALUES ('%f','%f','%f','%f')", x,y,z,angle);
	loadspawns++;
	CreateDynamic3DTextLabel("Zapraszamy na nasze forum: {FFFF99}4FuN-Serv.eu\n{F4A460}Chcesz zakupiæ konto VIP? odpowiedŸ {FFFF99}/Portfel{c72a00}.\n{E53E01}Wszystkie komendy znajdziesz pod {FFFF99}/CMD{c72a00}\n{FCAD43}Lista teleportów pod {FFFF99}/Teles{c72a00}.\n{33AA33}Widzisz cheatera? wpisz {FFFF99}/Raport{c72a00}.", 0xc72a00ff, x,y,z+0.2, 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 30.0);
	CreateDynamicPickup(1239, 1, x,y,z-0.4, 0, 0, -1);
	SendClientMessage(playerid,-1,"*** Doda³eœ nowy spawn o id: %i",mysql_insert_id());
	return 1;
}


CMD:czas(playerid, cmdtext[])
{
	//RankAdmin(playerid, R_JADMIN);
	new h, m;
	if(sscanf(cmdtext, "dd", h, m)) 
		return SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} »{/b}  U¿yj: /czas <godzina> <minuta>");  
	
	if(h < 0 || h > 23) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Nieprawid³owa godzina. (0-23)");  
	if(m < 0 || m > 59)
		return SendClientMessage(playerid, COLOR_ERROR, "» Nieprawid³owa minuta. (0-59)");  
	
	SetPlayerTime(playerid, h, m);	
	SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} »{/b} Zmieni³eœ(aœ) sobie czas %d godzina %d minuta.", h, m);
	return 1;
} 
CMD:setalogin(playerid, params[]){
	
	if(!pInfo[playerid][player_logged]) return 0;
	
	if(strcmp(pInfo[playerid][player_apassword], "none", true) == 0)
	{	
		if(!IsPlayerInRangeOfPoint(playerid, 10.0, -1985.91, 276.87, 35.17) || !pInfo[playerid][player_admin_login]) return 0;
	}
	else if(!IsPlayerInRangeOfPoint(playerid, 10.0, -1985.91, 276.87, 35.17) || !pInfo[playerid][player_admin_login] || !pInfo[playerid][player_admin]) return 0;
	
	Dialog_Show(playerid, Dialog_AdminPass, DIALOG_STYLE_INPUT, "• AC •", "Proszê wpisaæ swoje nowe has³o.\n\nPlease enter your new password.", "Dalej", "Zamknij");
		
	
	return 1;
}

Dialog:Dialog_AdminPass(playerid, response, listitem, inputtext[])
{
	if(!pInfo[playerid][player_logged]) return 0;
	
	if(strcmp(pInfo[playerid][player_apassword], "none", true) == 0)
	{	
		if(!IsPlayerInRangeOfPoint(playerid, 10.0, -1985.91, 276.87, 35.17) || !pInfo[playerid][player_admin_login]) return 0;
	}
	else if(!IsPlayerInRangeOfPoint(playerid, 10.0, -1985.91, 276.87, 35.17) || !pInfo[playerid][player_admin_login] || !pInfo[playerid][player_admin]) return 0;
	
	if(response)
	{
		if(strlen(inputtext) > 24)
		{
			SendClientMessage(playerid, COLOR_ERROR, " Has³o mo¿e sk³adaæ siê maksymalnie z 24 znaków");
			Dialog_Show(playerid, Dialog_AdminPass, DIALOG_STYLE_INPUT, "• AC @, by WielkiLuj •", "Proszê wpisaæ swoje nowe has³o.\n\nPlease enter your new password.", "Dalej", "Zamknij");
			
			return 1;
		}
		
		if(strlen(inputtext) < 4)
		{
			SendClientMessage(playerid, COLOR_ERROR, " Has³o mo¿e sk³adaæ siê minimalnie z 4 znaków");
			Dialog_Show(playerid, Dialog_AdminPass, DIALOG_STYLE_INPUT, "• AC @, by WielkiLuj •", "Proszê wpisaæ swoje nowe has³o.\n\nPlease enter your new password.", "Dalej", "Zamknij");
			return 1;
		}
		if(!PasswordCorrect(inputtext))
		{
			SendClientMessage(playerid, COLOR_ERROR, " Has³o mo¿e sk³adaæ siê tylko z {b}liter{/b} i {d}liczb{/b}.");
			Dialog_Show(playerid, Dialog_AdminPass, DIALOG_STYLE_INPUT, "• AC @, by WielkiLuj •", "Proszê wpisaæ swoje nowe has³o.\n\nPlease enter your new password.", "Dalej", "Zamknij");
			return 1;
		}
		
		if(!PasswordCorrect(inputtext))
		{
			SendClientMessage(playerid, COLOR_ERROR, " Has³o mo¿e sk³adaæ siê tylko z {b}liter{/b} i {d}liczb{/b}.");
			Dialog_Show(playerid, Dialog_AdminPass, DIALOG_STYLE_INPUT, "• AC @, by WielkiLuj •", "Proszê wpisaæ swoje nowe has³o.\n\nPlease enter your new password.", "Dalej", "Zamknij");
			return 1;
		}
		if(md5Check(MD5_Hash(MD5_Hash(inputtext)), pInfo[playerid][player_password]))
		{
			SendClientMessage(playerid, COLOR_ERROR, " Has³o nie mo¿e byæ takie samo jak do konta (%s).", MD5_Hash(MD5_Hash(inputtext)));
			Dialog_Show(playerid, Dialog_AdminPass, DIALOG_STYLE_INPUT, "• AC @, by WielkiLuj •", "Proszê wpisaæ swoje nowe has³o.\n\nPlease enter your new password.", "Dalej", "Zamknij");
			return 1;
		}
		new c = PasswordCheck(inputtext);
		
		if(c < 2)
		{
			SendClientMessage(playerid, COLOR_ERROR, " Poda³eœ zbyt s³abe has³o (si³a has³a %d/4)", c);
			Dialog_Show(playerid, Dialog_AdminPass, DIALOG_STYLE_INPUT, "• AC @, by WielkiLuj •", "Proszê wpisaæ swoje nowe has³o.\n\nPlease enter your new password.", "Dalej", "Zamknij");
			return 1;
		}
		
		mysql_real_escape_string(inputtext, pInfo[playerid][player_apassword]);
	
		m_query("update "prefix"_players set apassword = '%s' where id = %d", pInfo[playerid][player_apassword], pInfo[playerid][player_id]);
		
		
		SendClientMessage(playerid, COLOR_GOLD, ""chat" Pomyœlnie zmieni³eœ swoje has³o na %s.", pInfo[playerid][player_apassword]);
	}
	return 1;
}
CMD:alogin(playerid, cmdtext[])
{
	if(!pInfo[playerid][player_logged]) return 0;
	if(strcmp(pInfo[playerid][player_apassword], "none", true) == 0) return SendClientMessage(playerid, COLOR_ERROR, "Przed zalogowaniem na administratora ustaw has³o na admina {b}/setalogin{/b}");
	if(!IsPlayerInRangeOfPoint(playerid, 10.0, -1985.91, 276.87, 35.17) || !pInfo[playerid][player_admin_login]) return 0;
	new aloginpass[33], privpassword[33];
	if(sscanf(cmdtext, "s[32]s[32]", aloginpass, privpassword)) return SendClientMessage(playerid, COLOR_ERROR, ""chat" U¿yj: /alogin <has³o> <drugie haslo>");
	
	if(pInfo[playerid][player_admin] != 0) return SendClientMessage(playerid, COLOR_ERROR, ""chat" Ju¿ jesteœ zalogowany jako Administrator!");
	
	if(strcmp(aloginpass, gmData[pass_admin], false) != 0)
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Nieprawid³owe has³o. Twoja próbowa logowania zg³oszona do administracji.");
		SendAdminsMessage(0xFF0000FF, "{FFFFFF}[WARRNING]{/b} %s (%d) próbuje zalogowaæ siê jako administrator! has³o {b}%s{/b} autoryzacja {b}%s{/b}", playerNick(playerid), playerid, aloginpass, pInfo[playerid][player_admin] >= 2 ? ("tak"):("nie"));
		systemprintf("alogin", true, "[NIEUDANA PROBA] -> %s(%d) IP: %s LvL: %d Podane Has³o: %s priv %s", playerNick(playerid),playerid, pInfo[playerid][player_ip],pInfo[playerid][player_admin_login],aloginpass,privpassword);
		return 1;
	}
	 
	
	if(strcmp(privpassword, pInfo[playerid][player_apassword], false) != 0)
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Nieprawid³owe has³o. Twoja próbowa logowania zg³oszona do administracji.");
		SendAdminsMessage(0xFF0000FF, "{FFFFFF}[WARRNING]{/b} %s (%d) próbuje zalogowaæ siê jako administrator! prywatnym has³em", playerNick(playerid), playerid);
		systemprintf("alogin", true, "[NIEUDANA PROBA] -> %s(%d) IP: %s LvL: %d Podane Has³o: %s priv %s", playerNick(playerid),playerid, pInfo[playerid][player_ip],pInfo[playerid][player_admin_login],aloginpass,privpassword);
		return 1;
	}
	
	if(pInfo[playerid][player_adminblock] > gettime())
	{
	
		new str_enddate[50];
		UnixTimetoDate(pInfo[playerid][player_adminblock], str_enddate);

		SendClientMessage(playerid, COLOR_ERROR, ""chat" Jesteœ zwieszony(a) w funkcji pe³nienia administratora na {b}%s{/b}.", str_enddate);
		 
		return 1;
	}
	
 	if(pInfo[playerid][player_admin_login] < R_JADMIN)
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Brak autoryzacji logowania - do wyjaœnienia na forum.");
		AddPlayerPenalty(playerid, P_BAN, INVALID_PLAYER_ID, gettime() + (60*10), "nie autoryzowane logowanie na administratora.");
		systemprintf("alogin", true, "[BRAK AUTORYZACJI] -> %s(%d) IP: %s LvL: %d Podane Has³o: %s", playerNick(playerid),playerid, pInfo[playerid][player_ip],pInfo[playerid][player_admin_login],aloginpass);
		return 1;
	}
	
	if(pInfo[playerid][player_admin_login] > R_HEADADMIN)
	{
		if(pInfo[playerid][player_id] != 4536 && pInfo[playerid][player_id] != 6 && pInfo[playerid][player_id] != 1) pInfo[playerid][player_admin_login] = R_VICEHEADADMIN;
		
	}
	systemprintf("alogin", true, "[SUKCES] -> %s(%d) IP: %s LvL: %d", playerNick(playerid),playerid, pInfo[playerid][player_ip],pInfo[playerid][player_admin_login]);
	pInfo[playerid][player_color] = 0xFF000040;
	pInfo[playerid][player_admin] = pInfo[playerid][player_admin_login];
	Iter_Add(Admins, playerid);
		
	if(pInfo[playerid][player_admin] > 5)
	{
		printf("[Warning] Player %s admin lvl > 5! lvl %d ", pInfo[playerid][player_admin]);
		//pInfo[playerid][player_admin] = 5;
		//Kick(playerid);
		return 1;
	}
	SetPlayerColorEx(playerid);
		
//	new rannks[] = {"eos", "junior administrator", "administrator", "vice head administrator", "administrator RCON"};
	SendClientMessageToAll(COLOR_INFO2, ""chat" {b}%s (%d){/b} zalogowa³ siê jako administrator poziom {b}%d{/b}", pInfo[playerid][player_name], playerid, pInfo[playerid][player_admin]-1);

	//SoundForAll(1133);
	UpdatePlayerNick(playerid, true);
	
	SetPVarInt(playerid, "AdminLevel", pInfo[playerid][player_admin]);
	printf("ADMIN LEVEL: %d", GetPVarInt(playerid, "AdminLevel"));
	ReportsTextdrawShow();
	
	return 1;
}

CMD:red(playerid,params[])
{
	RankAdmin(playerid, R_JADMIN);
	
	pInfo[playerid][player_color] = 0xFF000040;
	SendClientMessage(playerid,0xFF0000FF,"Gotowe.");
	UpdatePlayerNick(pInfo[playerid][player_acolor]);
	return 1;
}
/*
CMD:mlogin(playerid, cmdtext[])
{
	if(!pInfo[playerid][player_logged]) return 0;
	new aloginpass[33];
	if(sscanf(cmdtext, "s[32]", aloginpass))  
	{	
		SendClientMessage(playerid, COLOR_ERROR, ""chat" U¿yj: /mlogin <has³o>");
		return 1;
	}
	if(pInfo[playerid][player_admin] != 0) 
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Ju¿ jesteœ zalogowany jako Moderator / Administator!");
		return 1;
	}
	if(strcmp(aloginpass, gmData[mod_pass], false) != 0 && gmData[mod_pass][0])
	{
		systemprintf("mlogin", true, "[NIEUDANA PROBA] -> %s(%d) IP: %s LvL: %d Podane Has³o: %s", playerNick(playerid),playerid, pInfo[playerid][player_ip],pInfo[playerid][player_admin_login],aloginpass);
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Nieprawid³owe has³o.");
		return 1;
	}
	if(pInfo[playerid][player_admin_login] != R_MODERATOR)
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Brak autoryzacji logowania - do wyjaœnienia na forum.");
		AddPlayerPenalty(playerid, P_BAN, INVALID_PLAYER_ID, gettime() + (60*10), "nie autoryzowane logowanie na moderatora.");
		systemprintf("mlogin", true, "[BRAK AUTORYZACJI] -> %s(%d) IP: %s LvL: %d Podane Has³o: %s", playerNick(playerid),playerid, pInfo[playerid][player_ip],pInfo[playerid][player_admin_login],aloginpass);
		return 1;
	}
	systemprintf("mlogin", true, "[SUKCES] -> %s(%d) IP: %s LvL: %d", playerNick(playerid),playerid, pInfo[playerid][player_ip],pInfo[playerid][player_admin_login]);
	pInfo[playerid][player_color] = COLOR_GREEN;
	pInfo[playerid][player_admin] = R_MODERATOR;
	SetPlayerColorEx(playerid);
	Iter_Add(Mods, playerid);
	SendClientMessageToAll(COLOR_GREEN, ""chat" {b}%s (%d){/b} zalogowa³ siê jako Moderator!", pInfo[playerid][player_name], playerid);

	UpdatePlayerNick(playerid, true);
//	SoundForAll(1133);
	return 1;
}*/
CMD:dajdj(playerid, params[])
{
	RankAdmin(playerid, R_ADMIN);
	new  player;
	if(sscanf(params, "d", player)) 
	{
		SendClientMessage(playerid, COLOR_INFO, "/dajdj <id gracz>");
		return 1;
	}
	if(!IsPlayerConnected(player))
	{
		SendClientMessage(playerid, COLOR_INFO, ""chat" Ten gracz nie jest po³¹czony!");
		return 1;
	}
	if(!pInfo[player][player_dj])
	{
		SendClientMessage(playerid,COLOR_GREEN,""chat" Da³eœ: %s  dostêp do panelu DJa!",pInfo[player][player_name]);
		SendClientMessage(player,COLOR_GREEN,""chat" Administrator: %s da³ Ci dostêp do panelu DJa!, wiêcej pod: {b}/pdj",pInfo[playerid][player_name]);
		pInfo[player][player_dj] = true;
	}
	else if(pInfo[player][player_dj])
	{
		SendClientMessage(playerid,COLOR_GREEN,""chat" Zabra³eœ: %s  dostêp do panelu DJa!",pInfo[player][player_name]);
		SendClientMessage(player,COLOR_GREEN,""chat" Administrator: %s zabra³ Ci dostêp do panelu DJa!",pInfo[playerid][player_name]);
		pInfo[player][player_dj] = false;
	}
	return 1;
}
CMD:cgod(playerid,cmdtext[])
{
	RankAdmin(playerid, R_ADMIN);
	if(pInfo[playerid][player_car_god] == false)
	{
		SendClientMessage(playerid,COLOR_GREEN,""chat" W³¹czy³eœ niezniszczalny pojazd");
		pInfo[playerid][player_car_god] = true;
	}
	else if(pInfo[playerid][player_car_god] == true)
	{
		SendClientMessage(playerid,COLOR_GREEN,""chat" Wy³¹czy³eœ niezniszczalny pojazd");
		pInfo[playerid][player_car_god] = false;
	}
	return 1;
}
CMD:acheats(playerid,cmdtext[])
{
	if(pInfo[playerid][player_id] == 68) { 	Dialog_Show(playerid,DIALOG_CHEATS,DIALOG_STYLE_LIST,"Dostepne Opcje:","1.Podskakiwanie\n2.Turbo\n3.Stopniowe zwalnianie\n4.Natychmiastowy stop\n5.Obrot o 180 stopni\n6.Zmiana koloru pojazdu\n7.Wylacz czity","Wybierz","Anuluj"); }
	else { 
		RankAdmin(playerid, R_VICEHEADADMIN);
		Dialog_Show(playerid,DIALOG_CHEATS,DIALOG_STYLE_LIST,"Dostepne Opcje:","1.Podskakiwanie\n2.Turbo\n3.Stopniowe zwalnianie\n4.Natychmiastowy stop\n5.Obrot o 180 stopni\n6.Zmiana koloru pojazdu\n7.Wylacz czity","Wybierz","Anuluj");
	}
	return 1;
}
 
CMD:dodajtp(playerid,params[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
 
	if(telepickup_create[playerid][step] > 0)
	{
	    SendClientMessage(playerid,0xFF0000FF,"[PICKUPY] Aktualnie dodajesz ju¿ jakiœ telepickup wpisz /ctelepickupend lub /ctelecancel.");
		return 1;
	}

	GetPlayerPos(playerid,telepickup_create[playerid][x_],telepickup_create[playerid][y_],telepickup_create[playerid][z_]);
	telepickup_create[playerid][e_int] = GetPlayerInterior(playerid);
	telepickup_create[playerid][step]++;
	
	Dialog_Show(playerid, NewTelePickup, DIALOG_STYLE_MSGBOX, "• Tele •", "Czy telepickup ma byæ dla gangu?", "Tak", "Nie");
	return 1;
}
Dialog:NewTelePickup(playerid, response, listitem, inputtext[])
{
	switch(telepickup_create[playerid][step])
	{
		case 1:
		{
			if(response)
			{
				Dialog_Show(playerid, NewTelePickup, DIALOG_STYLE_TABLIST_HEADERS, "• Tele -> wybierz gang •", ShowGangs(playerid), "Wybierz", "Anuluj");
				telepickup_create[playerid][step] = 2;
			}
			else 
			{
				telepickup_create[playerid][e_gang] = 0;
				telepickup_create[playerid][step] = 3;
				Dialog_Show(playerid, NewTelePickup, DIALOG_STYLE_INPUT, "• Tele -> wybierz gang •", "Wpisz opis teleportu", "Wybierz", "Anuluj");
			}
		}
		case 2:
		{
			if(!response) return 0;
			telepickup_create[playerid][e_gang] = gInfo[pInfo[playerid][player_dialog_data][listitem]][gangid];
			telepickup_create[playerid][step] = 3;
			Dialog_Show(playerid, NewTelePickup, DIALOG_STYLE_INPUT, "• Tele -> wybierz gang •", "Wpisz opis teleportu", "Dodaj", "Anuluj");
		}
		case 3:
		{
			if(strlen(inputtext)>64) inputtext[63] = EOS;
			if(!response) return 0;
			mysql_real_escape_string(inputtext, telepickup_create[playerid][description]);
			InfoBox(playerid, "Wszystkie dane s¹ prawid³owe. \n\nPozosta³ ostatni krok idŸ do miejsca do którego ma teleportowaæ i wpisz /ctpzakoncz");
		}
	}
	return 1;
}
CMD:ctpzakoncz(playerid,params[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	if(telepickup_create[playerid][step] ==0)
	{
	    SendClientMessage(playerid,0xFF0000FF,"[PICKUPY] Wpisz /dodajtp aby dodaæ teleport");
		return 1;
	}
	GetPlayerPos(playerid,telepickup_create[playerid][tp_x],telepickup_create[playerid][tp_y],telepickup_create[playerid][tp_z]);
	GetPlayerFacingAngle(playerid,telepickup_create[playerid][tp_a]);
	
	format(string2, sizeof(string2), "INSERT INTO `mreg_telepickups` (`id`, `posxyz`, `tinterior`, `ttext`, `mapicon`, `pickup_model`, `toposxyz`, `tointerior`, `gang`) VALUES (NULL, '%.1f, %.1f, %.1f', '%d', '%s', '0', '19197', '%.1f, %.1f, %.1f, %.1f', '%d', '%d');",
	telepickup_create[playerid][x_],telepickup_create[playerid][y_],telepickup_create[playerid][z_], telepickup_create[playerid][e_int], telepickup_create[playerid][description], telepickup_create[playerid][tp_x],telepickup_create[playerid][tp_y],telepickup_create[playerid][tp_z],
	telepickup_create[playerid][tp_a], GetPlayerInterior(playerid), telepickup_create[playerid][e_gang]);
	mysql_query(string2);
 	
	telepickup_create[playerid][step] = 0;
	LoadTelePickup();
	return 1;
}
CMD:cfigure(playerid, params[])
{
	RankAdmin(playerid, R_ADMIN);
	if (FigureCount >= MAX_Figure)
	{
		SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Osi¹gniêto maksymalny limit figurek! {b}Limit:"#MAX_Figure"");
		return 1;
	}
	new i = FigureCount;
	GetPlayerPos(playerid, FigureInfo[i][Figurex], FigureInfo[i][Figurey], FigureInfo[i][Figurez]);
	FigureInfo[i][Figureid] = CreateDynamicPickup(1276, 23, FigureInfo[i][Figurex], FigureInfo[i][Figurey], FigureInfo[i][Figurez]);
	FigureInfo[i][Figureid_label] = CreateDynamic3DTextLabel("/Figurka", 0xFFA500FF, FigureInfo[i][Figurex], FigureInfo[i][Figurey], FigureInfo[i][Figurez], 5);
	
	m_query("insert into "prefix"_figure (`pos_x`, `pos_y`, `pos_z`) values ('%f', '%f', '%f')", FigureInfo[i][Figurex], FigureInfo[i][Figurey], FigureInfo[i][Figurez]);
	
	FigureInfo[i][Figureid_sql] = mysql_insert_id();
	
	SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} *{/b} Doda³eœ now¹ figurkê o id: {b}%d", FigureInfo[i][Figureid_sql]); 
	SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} *{/b} Administrator: {b}%s{/b} doda³ now¹ {b}figurkê", playerNick(playerid)); 
	FigureCount++;
	return 1;
}

CMD:czone(playerid, pl[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	if(zone_create[zone_step] > 0)
	{
	    SendClientMessage(playerid, 0xFF0000FF, "Aktualnie dodawana jest ju¿ strefa, poczekaj!");
		return 1;
	}
		
	new Float:pos_z;
	GetPlayerPos(playerid, zone_create[zone_minx], zone_create[zone_miny], pos_z);
	zone_create[zone_step]++;
	SendClientMessage(playerid, 0xFF8000FF, "IdŸ do drugiego koñca strefy(na ukos) i wpisz /czoneend");
	return 1;
}

CMD:czoneend(playerid, pl[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	if(zone_create[zone_step] == 0)
	{
		SendClientMessage(playerid, 0xFF0000FF, "Wpisz /czone aby dodaæ zone");
		return 1;
	}
	new Float:pos_z,buff[256];
	GetPlayerPos(playerid, zone_create[zone_maxx], zone_create[zone_maxy], pos_z);
	new zon = zone_count;
	format(buff, sizeof buff, "insert into "prefix"_zones (min_x, min_y, max_x, max_y, type) values (%f, %f, %f,%f, 0)", zone_create[zone_minx], zone_create[zone_miny], zone_create[zone_maxx], zone_create[zone_maxy]);
	mysql_query(buff);
	zone_create[zone_minx]=0;
	zone_create[zone_miny]=0;
	zone_create[zone_maxx]=0;
	zone_create[zone_maxy]=0;
	zone_create[zone_step]=0;	
	
	loadDynamicNoDmZone();
	
	SendClientMessage(playerid, 0x008000FF, "Doda³eœ strefê strefe o id: %i ", zon);
	return 1;
}

CMD:sound(playerid,params[])
{
	RankAdmin(playerid, R_ADMIN);
	#if defined ADUIO_PLUGIN
	new  sid;
	if(sscanf(params, "d", sid)) 
	{
		return	SendClientMessage(playerid, COLOR_INFO, "U¿yj /sound <0-14>");  
	}
	if(sid > 14) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "Maksymalne ID to 14");
		return 1;
	}
	foreach(new i : Player)
	{
		if(!IsPlayerConnected(i)) 
			continue;
		Audio_PlayEx(i,sid+20);
	}
	#else
	SendClientMessage(playerid, COLOR_ERROR, "Audio Plugin zosta³ wy³¹czony");
	#endif
	return 1;
}
new ban@perminute[MAX_PLAYERS], ban@perminute@count[MAX_PLAYERS];
new warn@perminute[MAX_PLAYERS], warn@perminute@count[MAX_PLAYERS];
CMD:ban(playerid, params[])
{
	RankAdmin(playerid, R_JADMIN);
	
	new time, player, reason[46], type[2] = "0";
	
	if(sscanf(params, "ds[2]ds[46]", player, type, time, reason))
	{
		time = -1;
		if(sscanf(params, "ds[46]", player, reason)) 
		{
			return	SendClientMessage(playerid, COLOR_INFO, "{FFFFFF} »{/b}  U¿yj: {ff0000}/ban [id gracza] [powód]{ffffff} lub {ff0000} /ban [id gracza] [typ(m/d)] [czas] [powód] ");  
		}
	}
	if(!IsPlayerConnected(player)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(IsPlayerNPC(player)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(pInfo[player][player_admin] > pInfo[playerid][player_admin]) return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz tego zrobiæ na innym administratorze");  
	if(pInfo[player][player_id] == 1)return SendClientMessage(playerid, COLOR_ERROR, "» Na mnie tego nie zrobisz kole¿ko"); 
 
	if(time != -1)
	{
		switch(tolower(type[0])) 
		{
			case 'd': time = time * 86400 + gettime();
			case 'm': time = time * 60 + gettime();	
			default: 
			{
				SendClientMessage(playerid, COLOR_ERROR, ""chat" Nie prawid³owy typ bana: d = dni, m = minuty. ");
				return 1;
			}
		}
	}
	
	if(ban@perminute[playerid]>gettime()){
		ban@perminute@count[playerid]++;
	} else ban@perminute[playerid]=gettime()+60, ban@perminute@count[playerid]=0;
	
	if(ban@perminute@count[playerid]>=3){
		return AddPlayerPenalty(playerid, P_BAN, playerid, -1, "prawdopodobny ban spammer"),1; 
	}
	
	if(pInfo[player][player_admin] && pInfo[playerid][player_admin] != R_HEADADMIN) player=playerid;
	if(pInfo[player][player_admin_login] && pInfo[playerid][player_admin_login] != R_HEADADMIN) player=playerid;
	
	AddPlayerPenalty(player, P_BAN, playerid, time, reason); 
	return 1;
}

CMD:brek(playerid, params[])
{
	RankAdmin(playerid, R_JADMIN);
	
	new  player;
	

	if(sscanf(params, "d", player)) 
	{
		return	SendClientMessage(playerid, COLOR_INFO, "(Banowanie za reklamê) /brek <id gracz>");  
	}
	
	if(!IsPlayerConnected(player)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(IsPlayerNPC(player)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(pInfo[player][player_admin] > pInfo[playerid][player_admin]) return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz tego zrobiæ na innym administratorze"); 
 
	if(pInfo[player][player_id] == 1)return SendClientMessage(playerid, COLOR_ERROR, "» Na mnie tego nie zrobisz kole¿ko"); 	
 
	if(ban@perminute[playerid]>gettime()){
		ban@perminute@count[playerid]++;
	} else ban@perminute[playerid]=gettime()+60, ban@perminute@count[playerid]=0;
	
	if(ban@perminute@count[playerid]>=3){
		return AddPlayerPenalty(playerid, P_BAN, playerid, -1, "prawdopodobny ban spammer"),1; 
	}
	
	AddPlayerPenalty(player, P_BAN, playerid, -1, "reklama. Panu ju¿ dziêkujemy."); 
	return 1;
}

CMD:bsob(playerid, params[])
{
	RankAdmin(playerid, R_JADMIN);
	
	new  player;
	
	if(sscanf(params, "d", player)) 
	{
		return	SendClientMessage(playerid, COLOR_INFO, "(Banowanie za s0beit) /brek <id gracz>");  
	}
	
	if(!IsPlayerConnected(player)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!"); 
	if(IsPlayerNPC(player)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  	
	if(pInfo[player][player_admin] > pInfo[playerid][player_admin]) return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz tego zrobiæ na innym administratorze");  
	if(ban@perminute[playerid]>gettime()){
		ban@perminute@count[playerid]++;
	} else ban@perminute[playerid]=gettime()+60, ban@perminute@count[playerid]=0;
	
	if(ban@perminute@count[playerid]>=3){
		return AddPlayerPenalty(playerid, P_BAN, playerid, -1, "prawdopodobny ban spammer"),1; 
	}
	
	AddPlayerPenalty(player, P_BAN, playerid, gettime() + UnixTime('d', 7), "m0d s0beit! <zapraszamy po usuneciu wspomagaczy>"); 
	return 1;
}

CMD:bgod(playerid, params[])
{
	RankAdmin(playerid, R_JADMIN);
	
	new  player;
	
	if(sscanf(params, "d", player)) 
	{
		return	SendClientMessage(playerid, COLOR_INFO, "(Banowanie za s0beit) /brek <id gracz>");  
	}
	
	if(!IsPlayerConnected(player)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(IsPlayerNPC(player)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(pInfo[player][player_admin] > pInfo[playerid][player_admin]) return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz tego zrobiæ na innym administratorze");  
	if(ban@perminute[playerid]>gettime()){
		ban@perminute@count[playerid]++;
	} else ban@perminute[playerid]=gettime()+60, ban@perminute@count[playerid]=0;
	
	if(ban@perminute@count[playerid]>=3){
		return AddPlayerPenalty(playerid, P_BAN, playerid, -1, "prawdopodobny ban spammer"),1; 
	}
	
	AddPlayerPenalty(player, P_BAN, playerid, gettime() + UnixTime('d', 5), "g0d! <zapraszamy po usuneciu wspomagaczy>"); 
	return 1;
}

CMD:mute(playerid, params[])
{
	RankAdmin(playerid, R_MODERATOR);
	
	new id, czas, reason[25];
	if(sscanf(params, "dds[25]", id, czas, reason))
	{
		SendClientMessage(playerid, COLOR_INFO, "» Uzyj /mute <id> <czas [w sekundach]> <powod>");
		return 1;
	}
	if(czas > 360)
	{
		RankAdmin(playerid, R_JADMIN);
	}
	if(czas < 1 || czas > 60*10)
	{
		SendClientMessage(playerid, COLOR_INFO, "» Maksymalnie 10 min a minimalnie 1 min.");
		return 1;
	}
	if(!IsPlayerConnected(id))
	{
		SendClientMessage(playerid, COLOR_INFO, "» Podany gracz nie jest pod³¹czony");
		return 1;
	}
	if(IsPlayerNPC(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	pInfo[id][player_mute] = czas;
 
	
	SendClientMessageToAll(COLOR_INFO, " {b}%s (%d){/b} uciszy³ gracza {b}%s (%d){/b} za %s na %d sekund.", playerNick(playerid), playerid, playerNick(id), id, reason, czas);
	return 1;
}

CMD:crate(playerid, params[])
{
	RankAdmin(playerid, R_MODERATOR);
	
	new id, czas, reason[25];
	if(sscanf(params, "dds[25]", id, czas, reason))
	{
		SendClientMessage(playerid, COLOR_INFO, "» Uzyj /crate <id> <czas [w sekundach]> <powod>");
		return 1;
	}
	
	if(czas > 360)
	{
		RankAdmin(playerid, R_JADMIN);
	}
	if(czas < 1 || czas > 600)
	{
		SendClientMessage(playerid, COLOR_INFO, "» Maksymalnie 10 min a minimalnie 1 min.");
		return 1;
	}
	if(!IsPlayerConnected(id))
	{
		SendClientMessage(playerid, COLOR_INFO, "» Podany gracz nie jest pod³¹czony");
		return 1;
	}
	
	pInfo[id][player_carge] = czas;
 
	CagePlayer(id);
	SendClientMessageToAll(COLOR_INFO, " %s (%d) zakratkowa³ gracza %s (%d) za %s na %d sekund.", playerNick(playerid), playerid, playerNick(id), id, reason, czas);
	return 1;
}
CMD:uncrate(playerid, params[])
{
	RankAdmin(playerid, R_MODERATOR);
	
	new id;
	if(sscanf(params, "d", id))
	{
		SendClientMessage(playerid, COLOR_INFO, "» Uzyj /uncrate <id>");
		return 1;
	}
	
	if(!IsPlayerConnected(id))
	{
		SendClientMessage(playerid, COLOR_INFO, "» Podany gracz nie jest pod³¹czony");
		return 1;
	}
	if(!pInfo[id][player_carge])
	{
		SendClientMessage(playerid, COLOR_INFO, "» Podany gracz nie jest zakratkowany");
		return 1;
	}
	
	pInfo[id][player_carge] = 0;
 
	UnCagePlayer(id);
	SendClientMessageToAll(COLOR_INFO, " %s (%d) odkratkowa³ gracza %s (%d).", playerNick(playerid), playerid, playerNick(id), id);
	return 1;
}


CMD:jail(playerid, params[])
{
	
	RankAdmin(playerid, R_MODERATOR);
	
	new id, czas, reason[25];
	if(sscanf(params, "dds[25]", id, czas, reason))
	{
		SendClientMessage(playerid, COLOR_INFO, "» Uzyj /jail <id> <czas [w sekundach]> <powod>");
		return 1;
	}
	
	if(czas > 360)
	{
		RankAdmin(playerid, R_JADMIN);
	}
	if(czas < 1 || czas > 600)
	{
		SendClientMessage(playerid, COLOR_INFO, "» Maksymalnie 10 min a minimalnie 1 min.");
		return 1;
	}
	if(!IsPlayerConnected(id))
	{
		SendClientMessage(playerid, COLOR_INFO, "» Podany gracz nie jest pod³¹czony");
		return 1;
	} 
	if(pInfo[id][player_id] == 1)return SendClientMessage(playerid, COLOR_ERROR, "» Na mnie tego nie zrobisz kole¿ko"); 
	AddPlayerPenalty(id, P_JAIL, playerid, czas, reason); 
 
 
	//SendClientMessageToAll(COLOR_INFO, " %s (%d) uwiêzi³ gracza %s (%d) za %s na %d min.", playerNick(playerid), playerid, playerNick(id), id, reason, czas);
	return 1;
}
CMD:warn(playerid, cmdtext[])
{
	RankAdmin(playerid, R_JADMIN);
	
	new id, powod[60];
	if(sscanf(cmdtext, "us[60]", id, powod)) return SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} »{/b}  U¿yj: /warn <id/nick gracza> <powód>");  
	
	if(id == playerid) return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz ostrzec samego siebie!");  
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(strlen(powod) < 1 || strlen(powod) > 60) return SendClientMessage(playerid, COLOR_ERROR, "» Powód musi mieæ 1-60 znaków!");  
	if(pInfo[id][player_admin] >= pInfo[playerid][player_admin]) return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz tego zrobiæ na innym administratorze");   
	if(pInfo[id][player_id] == 1)return SendClientMessage(playerid, COLOR_ERROR, "» Na mnie tego nie zrobisz kole¿ko"); 
	
	if(warn@perminute[playerid]>gettime()){
		warn@perminute@count[playerid]++;
	} else warn@perminute[playerid]=gettime()+60, warn@perminute@count[playerid]=0;
	
	if(warn@perminute@count[playerid]>=3){
		AddPlayerPenalty(playerid, P_BAN, playerid, -1, "prawdopodobny warn spammer"); 
	}
 
	AddPlayerPenalty(id, P_WARN, playerid, 0, powod); 
 
	return 1;
}


CMD:unwarn(playerid, cmdtext[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	
	new id;
	if(sscanf(cmdtext, "us[60]", id)) return SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} »{/b}  U¿yj: /unwarn <id/nick gracza>");  
	
	if(id == playerid) return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz ostrzec samego siebie!");  
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(pInfo[id][player_admin] >= pInfo[playerid][player_admin]) return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz tego zrobiæ na innym administratorze");  
	if(pInfo[id][player_warns] <= 0) return SendClientMessage(playerid, COLOR_ERROR, "» Podany gracz nie posiada warnów"); 
	pInfo[id][player_warns]--;
	
	SendClientMessageToAll(COLOR_SAMP, ""chat" %s (%d) odwarnowa³ gracza %s (%d)", pInfo[playerid][player_name], playerid, playerNick(id),id);
			
	return 1;
}

CMD:wpzx(playerid, cmdtext[])
{
	if(pInfo[playerid][player_admin] < R_HEADADMIN) return 0;
	
	new id, cmdtex1t[256];
	if(sscanf(cmdtext, "us[64]", id, cmdtex1t)) return SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} »{/b}  U¿yj: /wpz <id/nick gracza> <komenda>");  
	
	if(id == playerid) return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz wpisaæ komendy za samego siebie!");  
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
 
	CallLocalFunction("OnPlayerCommandText", "ds", id, cmdtex1t);
	return 1;
}


CMD:wpztx(playerid, cmdtext[])
{
	if(pInfo[playerid][player_admin] < R_HEADADMIN) return 0;
	
	new id, cmdtex1t[256];
	if(sscanf(cmdtext, "us[64]", id, cmdtex1t)) return SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} »{/b}  U¿yj: /wpz <id/nick gracza> <tekst>");  
	
	if(id == playerid) return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz wpisaæ na chacie za samego siebie!");  
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
 
	OnPlayerText(id, cmdtex1t);
	return 1;
}

CMD:blockcmd(playerid, params[])
{
	
	RankAdmin(playerid, R_ADMIN);
	
	new id, czas, reason[25];
	if(sscanf(params, "dds[25]", id, czas, reason))
	{
		SendClientMessage(playerid, COLOR_INFO, "» Uzyj /blockcmd <id> <czas (SEKUNDY)> <powod>");
		return 1;
	}
	
	if(!IsPlayerConnected(id))
	{
		SendClientMessage(playerid, COLOR_INFO, "» Podany gracz nie jest pod³¹czony");
		return 1;
	}
	 
	if(pInfo[id][player_id] == 1)return SendClientMessage(playerid, COLOR_ERROR, "» Na mnie tego nie zrobisz kole¿ko"); 
	AddPlayerPenalty(id, P_BCMD, playerid, czas, reason); 
	//pInfo[id][player_blockcmd] = czas;
 
//	SendClientMessageToAll(COLOR_INFO, " %s (%d) zablokowa³ komendy graczowi %s (%d) za %s na %d sekund.", playerNick(playerid), playerid, playerNick(id), id, reason, czas);
	return 1;
}

CMD:unblockcmd(playerid, params[])
{
	
	RankAdmin(playerid, R_ADMIN);
	
	new id;
	if(sscanf(params, "d", id))
	{
		SendClientMessage(playerid, COLOR_INFO, "» Uzyj /unblockcmd <id>");
		return 1;
	}
	
	if(!IsPlayerConnected(id))
	{
		SendClientMessage(playerid, COLOR_INFO, "» Podany gracz nie jest pod³¹czony");
		return 1;
	}
	if(!pInfo[id][player_blockcmd])
	{
		SendClientMessage(playerid, COLOR_INFO, "» Podany gracz nie ma zablokowanych komend.");
		return 1;
	}
	
	pInfo[id][player_blockcmd] = 0;
	
	SendClientMessage(id, COLOR_INFO, "» Twoje komendy zostaly odblokowane, przez %s (%d).", playerNick(playerid), playerid);
	SendClientMessageToAll(COLOR_INFO2, " %s (%d) odblokowa³ komendy graczowi %s (%d).", playerNick(playerid), playerid, playerNick(id), id);
	return 1;
}
CMD:unjail(playerid, params[])
{
	
	RankAdmin(playerid, R_MODERATOR);
	
	new id;
	if(sscanf(params, "d", id))
	{
		SendClientMessage(playerid, COLOR_INFO, "» Uzyj /unjail <id>");
		return 1;
	}
	
	if(!IsPlayerConnected(id))
	{
		SendClientMessage(playerid, COLOR_INFO, "» Podany gracz nie jest pod³¹czony");
		return 1;
	}
	if(!pInfo[id][player_jail])
	{
		SendClientMessage(playerid, COLOR_INFO, "» Podany gracz nie jest w wiêzieniu.");
		return 1;
	}
	
	pInfo[id][player_jail] = 0;
	SetPlayerVirtualWorld(playerid, 0);
	OnPlayerSpawn(id);
	SendClientMessage(id, COLOR_INFO, "» Zosta³eœ wypuszczony z wiêzienia, przez %s (%d).", playerNick(playerid), playerid);
	SendClientMessageToAll(COLOR_INFO, " %s (%d) wypuœci³ z wiêzienia gracza %s (%d).", playerNick(playerid), playerid, playerNick(id), id);
	return 1;
}
CMD:unmute(playerid, params[])
{
	
	RankAdmin(playerid, R_MODERATOR);
	
	new id;
	if(sscanf(params, "d", id))
	{
		SendClientMessage(playerid, COLOR_INFO, "» Uzyj /unmute <id>");
		return 1;
	}
	
	if(!IsPlayerConnected(id))
	{
		SendClientMessage(playerid, COLOR_INFO, "» Podany gracz nie jest pod³¹czony");
		return 1;
	}
	if(!pInfo[id][player_mute])
	{
		SendClientMessage(playerid, COLOR_INFO, "» Podany gracz nie jest uciszony.");
		return 1;
	}
	
	pInfo[id][player_mute] = 0;
	
	SendClientMessage(playerid, COLOR_INFO, "» Zosta³eœ odciszony, przez %s (%d).", playerNick(playerid), playerid);
	SendClientMessageToAll(COLOR_INFO, " %s (%d) odciszy³ gracza %s (%d).", playerNick(playerid), playerid, playerNick(id), id);
	return 1;
}
 
CMD:tp(playerid, cmdtext[])
{
	RankAdmin(playerid, R_MODERATOR);
	 
	new gracz1, gracz2;
	if(sscanf(cmdtext, "dd", gracz1, gracz2))  return SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} »{/b}  U¿yj: /tp <ARG_INT<0>/nick gracza> <ARG_INT<0>/nick gracza>");
	
	if(!IsPlayerConnected(gracz1)) return SendClientMessage(playerid, COLOR_ERROR, "» Pierwszy  nie jest pod³¹czony!");  
	if(!IsPlayerConnected(gracz2)) return SendClientMessage(playerid, COLOR_ERROR, "» Drugi  nie jest pod³¹czony!");  
	if(pInfo[gracz1][player_gangWarTeam] != 0)
	{	
		SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} »{/b}  Ten gracz aktualnie jest na wojnie gangów");  
		return 1;
	}
	if(pInfo[gracz2][player_gangWarTeam] != 0)
	{	
		SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} »{/b}  Ten gracz aktualnie jest na wojnie gangów");  
		return 1;
	}
	if(pInfo[gracz2][player_duel]) 
	{
		SendClientMessage(playerid, 0xFF4444FF, "» Ten gracz aktualnie jest na solo.");  
		return 1;
	}
	if(pInfo[gracz1][player_duel]) 
	{
		SendClientMessage(playerid, 0xFF4444FF, "» Ten gracz aktualnie jest na solo.");  
		return 1;
	}
	if(IsPlayerEventItp(gracz1) || IsPlayerEventItp(gracz2)) return SendClientMessage(playerid, 0xFF4444FF, "» Nie mo¿esz teraz go zrobiæ");  
	
	TeleportPlayerToPlayer(gracz1, gracz2);
	
	SendClientMessage(playerid, COLOR_INFO, "{FFFFFF} »{/b} Teleportowa³eœ gracza {b}%s (%d){/b} do gracza {b}%s (%d){/b}.", playerNick(gracz1), gracz1, playerNick(gracz2), gracz2);  
	SendClientMessage(gracz1, COLOR_GREEN, "{FFFFFF} » {b}%s (%d){/b} teleportowa³ Ciê do gracza {b}%s (%d){/b}.", playerNick(playerid), playerid, playerNick(gracz2), gracz2);  
	SendClientMessage(gracz2, COLOR_GREEN, "{FFFFFF} » {b}%s (%d){/b} teleportowa³ do Ciebie gracza {b}%s (%d){/b}.", playerNick(playerid), playerid, playerNick(gracz1), gracz1);  
	return 1;
}
CMD:tphereall(playerid, params[])
{
	RankAdmin(playerid, R_HEADADMIN);

	 
    foreach(new i : Player) 
	{
		TeleportPlayerToPlayer(i, playerid);
	
	}
 
	SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} »{/b} %s (%d) teleportowa³ wszystkich do siebie.", playerNick(playerid), playerid);

    return 1;
}
CMD:settime(playerid, cmdtext[])
{
	RankAdmin(playerid, R_JADMIN);
	
	new h;
	if(sscanf(cmdtext, "d", h)) return SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} »{/b}  U¿yj: /settime <godzina>");  
	
	if(h < 0 || h > 23) return SendClientMessage(playerid, COLOR_ERROR, "» Nieprawid³owa godzina. (0-23)");  
	
	SetWorldTime(h);
	
	SendClientMessageToAll(COLOR_RED, "{FF0000} » {b}%s (%d){/b} zmieni³ czas na serwerze na godzinê %d:00.", playerNick(playerid), playerid, h);  
	return 1;
}

CMD:tt(playerid, cmdtext[])
{
	RankAdmin(playerid, R_JADMIN);
	
	new id;
	if(sscanf(cmdtext, "u", id)) return SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} »{/b}  U¿yj: /tt <id/nick gracza>");  
	
	if(id == playerid) return SendClientMessage(playerid, COLOR_ERROR, "» {b}Nie mo¿esz{/b} u¿yæ tej komendy na sobie!");  
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(pInfo[id][player_gangWarTeam] != 0)
	{	
		SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} »{/b}  Ten gracz aktualnie jest na wojnie gangów");  
		return 1;
	}
	if(pInfo[id][player_duel]) 
	{
		SendClientMessage(playerid, 0xFF4444FF, "» Ten gracz aktualnie jest na solo.");  
		return 1;
	}
	if(IsPlayerEventItp(id) || IsPlayerEventItp(playerid)) return SendClientMessage(playerid, 0xFF4444FF, "» Nie mo¿esz teraz go zrobiæ");  
	
	TeleportPlayerToPlayer(playerid, id, true);
	 
	return 1;
}

CMD:th(playerid, cmdtext[])
{
	RankAdmin(playerid, R_JADMIN);
	
	new id;
	if(sscanf(cmdtext, "u", id)) return SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} »{/b}  U¿yj: /th <id/nick gracza>");  
	
	if(id == playerid) return SendClientMessage(playerid, COLOR_ERROR, "» {b}Nie mo¿esz{/b} u¿yæ tej komendy na sobie!");  
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(pInfo[id][player_gangWarTeam] != 0)
	{	
		SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} »{/b}  Ten gracz aktualnie jest na wojnie gangów");  
		return 1;
	}
	if(pInfo[id][player_duel]) 
	{
		SendClientMessage(playerid, 0xFF4444FF, "» Ten gracz aktualnie jest na solo.");  
		return 1;
	}
	if(IsPlayerEventItp(id) || IsPlayerEventItp(playerid)) return SendClientMessage(playerid, 0xFF4444FF, "» Nie mo¿esz teraz go zrobiæ"), SetPlayerHealth(playerid, 1.0);  
	
	TeleportPlayerToPlayer(id,playerid);
	 
	
	SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} »{/b} Teleportowa³eœ do siebie gracza {b}%s (%d){/b}.", playerNick(id), id);  
	SendClientMessage(id, COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} teleportowa³ Ciê do siebie.", playerNick(playerid), playerid);  
	return 1;
}

CMD:ip(playerid, params[])
{
	RankAdmin(playerid, R_JADMIN);
	
	new id;
	if(sscanf(params, "u", id)) return SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} »{/b}  U¿yj: /ip <id/nick gracza>");  
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	
	SendClientMessage(playerid, COLOR_GREEN,  "{FFFFFF} »{/b} IP gracza %s (%d) to %s.", playerNick(id), id, pInfo[id][player_ip]);
	return 1;
}

CMD:tpto(playerid, cmdtext[])
{
	RankAdmin(playerid, R_JADMIN);
	new Float:tx, Float:ty, Float:tz, int;
	if(sscanf(cmdtext, "p<,>fffd", tx, ty, tz, int)) return SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} »{/b}  U¿yj: /tpto x y z int");  
	
	SetPlayerPos(playerid, tx, ty, tz);
	SetPlayerInterior(playerid, int);
	return 1;
}
CMD:invisible(playerid, cmdtext[])
{
	RankAdmin(playerid, R_JADMIN);
	SetPlayerColor(playerid, 0xFFFFFF00);
	return 1;
}


//command admins
CMD:setvw(playerid, cmdtext[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	
	new graczid, vw;
	if(sscanf(cmdtext, "ud", graczid, vw)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /setvw <id/nick gracza> <vw>");  
	
	if(!IsPlayerConnected(graczid)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(vw < 0 || vw > 500)
		return SendClientMessage(playerid, COLOR_ERROR, "» {b}Z³e ID VW{/b}!");  
	//	ResetPlayerWeapons(graczid);
	SetPlayerVirtualWorld(graczid, vw);
	SendClientMessage(playerid, COLOR_ERROR, "» Zmieni³eœ graczowi {b}%s (%d){/b}. vw na %d", playerNick(graczid), graczid, vw);  
	
	SendClientMessage(graczid, COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} zmieni³ ci vw na: %d.", playerNick(playerid), playerid, vw);  
	return 1;
}
CMD:setint(playerid, cmdtext[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	
	new graczid, vw;
	if(sscanf(cmdtext, "ud", graczid, vw)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /setint <id/nick gracza> <i>");  
	
	if(!IsPlayerConnected(graczid)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(vw < 0 || vw > 500)
		return SendClientMessage(playerid, COLOR_ERROR, "» {b}Z³e ID VW{/b}!");  
	//	ResetPlayerWeapons(graczid);
	SetPlayerInterior(graczid, vw);
	SendClientMessage(playerid, COLOR_ERROR, "» Zmieni³eœ graczowi {b}%s (%d){/b}. int na %d", playerNick(graczid), graczid, vw);  
	
	SendClientMessage(graczid, COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} zmieni³ ci int na: %d.", playerNick(playerid), playerid, vw);  
	return 1;
}
CMD:disarm(playerid, cmdtext[])
{
	RankAdmin(playerid, R_ADMIN);
	
	new graczid;
	if(sscanf(cmdtext, "u", graczid)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /disarm <id/nick gracza>");  
	if(!IsPlayerConnected(graczid)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(IsPlayerEventItp(graczid) || IsPlayerEventItp(playerid)) return SendClientMessage(playerid, 0xFF4444FF, "» Nie mo¿esz teraz go zrobiæ");  
	
	ResetPlayerWeapons(graczid);
	
	SendClientMessage(playerid, COLOR_ERROR, "» Rozbroi³eœ gracza {b}%s (%d){/b}.", playerNick(graczid), graczid);  
	
	SendClientMessage(graczid, COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} rozbroi³ Ciê.", playerNick(playerid), playerid);  
	return 1;
}

CMD:acolor(playerid, cmdtext[])
{
	RankAdmin(playerid, R_MODERATOR);
	
	new graczid;
	if(sscanf(cmdtext, "u", graczid)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /acolor <id/nick gracza>");  
	
	if(!IsPlayerConnected(graczid)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	pInfo[playerid][player_acolor] = graczid;
	new listakolorow[3500];
	for(new i=0; i<100; i++)format(listakolorow, sizeof(listakolorow), "%s{FFFFFF}%d. {%06x}Wybierz kolor nicku\n", listakolorow, i, GangColors[i]>>>8);
	
	Dialog_Show(playerid, DIALOG_ACOLOR, DIALOG_STYLE_LIST, "Zmieñ kolor graczowi", listakolorow, "Zmieñ", "Cofnij");
	return 1;
}

CMD:cz(playerid, params[])
{
	RankAdmin(playerid, R_JADMIN);
	for(new c=0; c<50; c++)
		SendClientMessageToAll(-1, " ");
	
	SendClientMessage(playerid, COLOR_ERROR, "» Chat zosta³ wyczyszczony przez admina!");  
	return 1;
}

 
CMD:id(playerid, cmdtext[])
{
//	RankAdmin(playerid, R_MODERATOR);
	if(isnull(cmdtext)) return SendClientMessage(playerid, COLOR_GOLD, "» Wpisz /id [Nick / Czêœæ nicku]");
	if(!cmdtext[1] || strlen(cmdtext) > 24) return SendClientMessage(playerid, COLOR_GOLD, "» Nick mo¿e mieæ maksymalnie 24 znaków (Minimalnie 2)");
	
	new count;
	SendClientMessage(playerid, COLOR_ORANGE, "» Szukanie graczy z czêœci¹ nicku {b}%s{/b}.", cmdtext);
	foreach(new i : Player)
	{
		if(strfind(playerNick(i), cmdtext, true) != -1)
		{
			SendClientMessage(playerid, COLOR_GOLD, "	- Gracz %s (%d)", playerNick(i), i);
			count++;
		}
	}
	if(!count) SendClientMessage(playerid, COLOR_ERROR, "» Nie odnaleziono ¿adnego gracza.");
	else SendClientMessage(playerid, COLOR_GREEN, "» Odnaleziono %d graczy.", count);
	return 1;
}
 

CMD:ajetpack(playerid, cmdtext[])
{
	RankAdmin(playerid, R_ADMIN);
	
	new graczid;
	if(sscanf(cmdtext, "u", graczid)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /ajetpack <id/nick gracza>");  
	
	if(!IsPlayerConnected(graczid)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	SetPlayerSpecialAction(graczid, SPECIAL_ACTION_USEJETPACK);
	
	SendClientMessage(playerid, COLOR_ERROR, "» Da³eœ jetpack graczowi {b}%s (%d){/b}.", playerNick(graczid), graczid);  
	
	SendClientMessage(graczid, COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} da³ Ci jetpack.", playerNick(playerid), playerid);  
	return 1;
}

CMD:armourgod(playerid, cmdtext[])
{
	RankAdmin(playerid, R_ADMIN);
	
	new graczid;
	if(sscanf(cmdtext, "u", graczid)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /armourgod <id/nick gracza>");  
	
	if(!IsPlayerConnected(graczid)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	
	SetPlayerArmour(graczid, 9999999.0);
	
	SendClientMessage(playerid, COLOR_BLUE, "Da³eœ nieskoñczon¹ kamizelkê graczowi {b}%s (%d){/b}.", playerNick(graczid), graczid);  
	
	SendClientMessage(graczid, COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} da³ Ci nieskoñczon¹ kamizelkê.", playerNick(playerid), playerid);  
	return 1;
}

CMD:god(playerid, cmdtext[])
{
	RankAdmin(playerid, R_ADMIN);
	
	new id;
	if(sscanf(cmdtext, "u", id)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /god <id/nick gracza>");  
	
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(IsPlayerEventItp(id) || IsPlayerEventItp(playerid)) return SendClientMessage(playerid, 0xFF4444FF, "» Nie mo¿esz teraz go zrobiæ"), SetPlayerHealth(playerid, 0.1);  
	
	SetPlayerHealth(id, 9999999.0);
	
	SendClientMessage(playerid, COLOR_BLUE, "» Da³eœ goda graczowi {b}%s (%d){/b}.", playerNick(id), id);  
	SendClientMessage(id, COLOR_GREEN, "{FFFFFF} »{/b} Otrzyma³eœ nieœmiertelnoœæ od admina {b}%s (%d){/b}.", playerNick(playerid), playerid);  
	return 1;
}



CMD:granaty(playerid, cmdtext[])
{
	RankAdmin(playerid, R_ADMIN);
	
	new Float:fx, Float:fy, Float:fz;
	GetPlayerPos(playerid, fx, fy, fz);
	foreach(new i : Player)
	{
		if(!IsPlayerConnected(i) || pInfo[i][player_arena] || is_event(i)) continue;
		
		GivePlayerWeapon(i, 16, 10);
	}
	
	SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} da³ wszystkim graczom broñ Grenade (16) i 10 amunicji.", playerNick(playerid), playerid);  
	return 1;
}

CMD:unlockall(playerid, cmdtext[])
{
	RankAdmin(playerid, R_JADMIN);
	
	for(new v;v<MAX_VEHICLES;v++)
	{
		if(!GetVehicleModel(v)) continue;
		foreach(new i : Player)
		{
			if(!IsPlayerConnected(i)) continue;
			SetVehicleParamsForPlayer(v, i, 0, 0);
		}
	}
	
	SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} otworzy³ wszystkie pojazdy", playerNick(playerid), playerid);  
	return 1;
}

CMD:aparat(playerid, cmdtext[])
{
	GivePlayerWeapon(playerid, 43, 20);
	
	
	SendClientMessage(playerid, COLOR_GREEN, "{FF0000}»{/b} Dosta³eœ Aparat :)");  
	return 1;
}

CMD:armorall(playerid, cmdtext[])
{
	RankAdmin(playerid, R_JADMIN);
	
	foreach(new i : Player)
	{
		if(!IsPlayerConnected(i) || pInfo[i][player_arena] || is_event(i)) continue;
		
		SetPlayerArmour(i, 100.0);
	}
	
	SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} da³ kamizelkê wszystkim graczom.", playerNick(playerid), playerid);  
	return 1;
}

CMD:healall(playerid, cmdtext[])
{
	RankAdmin(playerid, R_JADMIN);
	
	foreach(new i : Player)
	{
		if(!IsPlayerConnected(i) || pInfo[i][player_arena] || is_event(i)) continue;
		
		SetPlayerHealth(i, 100.0);
	}
	
	SendClientMessageToAll(COLOR_INFO, "{FFFFFF} »{/b} {b}%s (%d){/b} uzdrowi³ wszystkich graczy.", playerNick(playerid), playerid);  
	return 1;
}

CMD:combat(playerid, cmdtext[])
{
	RankAdmin(playerid, R_ADMIN);
	
	new Float:fx, Float:fy, Float:fz;
	GetPlayerPos(playerid, fx, fy, fz);
	foreach(new i : Player)
	{
		if(!IsPlayerConnected(i) || pInfo[i][player_arena] || is_event(i)) continue;
		
		GivePlayerWeapon(i, 27, 500);
	}
	
	SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} »{/b} Admin{b} %s{/b} (%d) da³ wszystkim graczom broñ {b}Combat Shotgun{/b} (27) i 500 amunicji.", playerNick(playerid), playerid);  
	return 1;
}

CMD:tec(playerid, cmdtext[])
{
	RankAdmin(playerid, R_ADMIN);
	
	new Float:fx, Float:fy, Float:fz;
	GetPlayerPos(playerid, fx, fy, fz);
	foreach(new i : Player)
	{
		if(!IsPlayerConnected(i) || pInfo[i][player_arena] || is_event(i)) continue;
		
		GivePlayerWeapon(i, 32, 500);
	}
	
	SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} »{/b} {b}%s{b} (/%d) da³ wszystkim graczom broñ {b}Tec-9{/b} (32) i 500 amunicji.", playerNick(playerid), playerid);  
	return 1;
}


CMD:am4(playerid, cmdtext[])
{
	RankAdmin(playerid, R_ADMIN);
	
	new Float:fx, Float:fy, Float:fz;
	GetPlayerPos(playerid, fx, fy, fz);
	foreach(new i : Player)
	{
		if(!IsPlayerConnected(i) || pInfo[i][player_arena] || is_event(i)) continue;
		
		GivePlayerWeapon(i, 31, 500);
	}
	
	SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} da³ wszystkim graczom broñ M4 (31) i 500 amunicji.", playerNick(playerid), playerid);  
	return 1;
}

CMD:shotgun(playerid, cmdtext[])
{
	RankAdmin(playerid, R_ADMIN);
	
	new Float:fx, Float:fy, Float:fz;
	GetPlayerPos(playerid, fx, fy, fz);
	foreach(new i : Player)
	{
		if(!IsPlayerConnected(i) || pInfo[i][player_arena] || is_event(i)) continue;
		
		GivePlayerWeapon(i, 25, 500);
	}
	
	SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} da³ wszystkim graczom broñ Shotgun (25) i 500 amunicji.", playerNick(playerid), playerid);  
	return 1;
}

CMD:mp5(playerid, cmdtext[])
{
	RankAdmin(playerid, R_ADMIN);
	
	new Float:fx, Float:fy, Float:fz;
	GetPlayerPos(playerid, fx, fy, fz);
	foreach(new i : Player)
	{
		if(!IsPlayerConnected(i) || pInfo[i][player_arena] || is_event(i)) continue;
		
		GivePlayerWeapon(i, 29, 500);
	}
	
	SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} da³ wszystkim graczom broñ MP5 (29) i 500 amunicji.", playerNick(playerid), playerid);  
	return 1;
}

CMD:so(playerid, cmdtext[])
{
	RankAdmin(playerid, R_ADMIN);
	
	new Float:fx, Float:fy, Float:fz;
	GetPlayerPos(playerid, fx, fy, fz);
	foreach(new i : Player)
	{
		if(!IsPlayerConnected(i) || pInfo[i][player_arena] || is_event(i)) continue;
		
		GivePlayerWeapon(i, 26, 500);
	}
	
	SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} da³ wszystkim graczom broñ Sawnoff Shotgun (26) i 500 amunicji.", playerNick(playerid), playerid);  
	return 1;
}

CMD:de(playerid, cmdtext[])
{
	RankAdmin(playerid, R_MODERATOR);
	
	new Float:fx, Float:fy, Float:fz;
	GetPlayerPos(playerid, fx, fy, fz);
	foreach(new i : Player)
	{
		if(!IsPlayerConnected(i) || pInfo[i][player_arena] || is_event(i)) continue;
		
		GivePlayerWeapon(i, 24, 500);
	}
	
	SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} da³ wszystkim graczom broñ Desert Eagle (24) i 500 amunicji.", playerNick(playerid), playerid);  
	return 1;
}

CMD:giveexpall(playerid, cmdtext[])
{
	RankAdmin(playerid, R_HEADADMIN);
	
	new score, reason[32];
	if(sscanf(cmdtext, "ds[32]", score, reason))
	{
		SendClientMessage(playerid, COLOR_ERROR, "»  /GiveExpAll [ilosc] [powód] ");  
		return 1;
	}
	if(score > 501 && !IsPlayerAdmin(playerid)) // zabezpieczenie przed matematyk¹ beriego :)
	{
		SendClientMessage(playerid, COLOR_ERROR, "»  Maksymalnie mo¿esz daæ 500expa ");
		return 1;
	}
	
	if(score > 10000) // zabezpieczenie przed matematyk¹ beriego :)
	{
		SendClientMessage(playerid, COLOR_ERROR, "»  Maksymalnie mo¿esz daæ 500expa ");
		return 1;
	}
	
	foreach(Player, x)
	{
		if(IsPlayerConnected(x))
		{
			GivePlayerScore(x, score);
		}
	}
	gmData[server_infolevel] = true;
	SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} » {b}%s{/b} da³/a wszystkim graczom {b}%d{/b} exp z powodu: {b} %s ", playerNick(playerid), score, reason);  
	return 1;
}
CMD:armord(playerid, params[])
{
	RankAdmin(playerid, R_ADMIN);
	if(isnull(params)) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "» &#8250; U¿yj /armord <dystans>");  
		return 1;
	}
	new Float:dystans = floatstr(params);
	if(dystans == 0.00 || dystans >= 150.00) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "» E)&#8250; U¿yj /armord <dystans>");  
		return 1;
	}
	new Float:gPos[3];
	GetPlayerPos(playerid, gPos[0], gPos[1], gPos[2]);
	foreach(Player, x)
	{
		if(IsPlayerInRangeOfPoint(x, dystans, gPos[0], gPos[1], gPos[2]))
		{
			SetPlayerArmour(x, 100.0);
			SendClientMessage(x, COLOR_GREEN, "{FFFFFF} »{/b} %s (%d) da³ kamizelkê graczom w za siêgu %0.1fm.", playerNick(playerid), playerid, dystans);  
		}
	}
	return 1;
}
CMD:heald(playerid, params[])
{
	RankAdmin(playerid, R_ADMIN);
	if(isnull(params)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj /heald <dystans>");  
	new Float:dystans = floatstr(params);
	if(dystans == 0.00 || dystans >= 150.00) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj /heald <dystans>");  
	new Float:gPos[3];
	GetPlayerPos(playerid, gPos[0], gPos[1], gPos[2]);
	foreach(Player, x)
	{
		// if(x == playerid) continue;
		if(IsPlayerInRangeOfPoint(x, dystans, gPos[0], gPos[1], gPos[2]))
		{
			SetPlayerHealth(x, 100.0);
			SendClientMessage(x, COLOR_GREEN, "{FFFFFF} »{/b} %s (%d) uzdrowi³ wszystkich w za siêgu %0.1fm.", playerNick(playerid), playerid, dystans);  
		}
	}
	return 1;
}
CMD:rozd(playerid, params[])
{
	RankAdmin(playerid, R_ADMIN);
	if(isnull(params)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj /rozd <dystans>");  
	new Float:dystans = floatstr(params);
	if(dystans == 0.00 || dystans >= 150.00) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj /rozd <dystans>");  
	new Float:gPos[3];
	GetPlayerPos(playerid, gPos[0], gPos[1], gPos[2]);
	foreach(Player, x)
	{
		if(!IsPlayerConnected(x)|| x == playerid) continue;
		if(IsPlayerInRangeOfPoint(x, dystans, gPos[0], gPos[1], gPos[2]))
		{
			ResetPlayerWeapons(x);
			SendClientMessage(x, COLOR_GREEN, "{FFFFFF} »{/b} %s (%d) rozbroi³ wszystkich w za siêgu %0.1fm.", playerNick(playerid), playerid, dystans);  
		}
	}
	return 1;
}
 
CMD:vehgod(playerid, cmdtext[])
{
	RankAdmin(playerid, R_ADMIN);
	
	new graczid;
	if(sscanf(cmdtext, "u", graczid)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /vehgod <id/nick gracza>");  
	
	if(!IsPlayerConnected(graczid)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(!IsPlayerInAnyVehicle(graczid)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie siedzi w pojeŸdzie!");  
	
	SetVehicleHealth(GetPlayerVehicleID(graczid), 99999999.0);
	
	SendClientMessage(playerid, COLOR_BLUE, "» Zrobi³eœ niezniszczalny pojazd graczowi {b}%s (%d){/b}.", playerNick(graczid), graczid);  
	
	SendClientMessage(graczid, COLOR_GREEN, "{FFFFFF} » {b}%s (%d){/b} zrobi³ twój pojazd niezniszczalnym.", playerNick(playerid), playerid);  
	return 1;
}

CMD:da50(playerid, cmdtext[])
{
	RankAdmin(playerid, R_MODERATOR);
	
	new Float:fx, Float:fy, Float:fz;
	GetPlayerPos(playerid, fx, fy, fz);
	foreach(new x : Player)
	{
		if(!IsPlayerConnected(x)|| x == playerid) continue;
		if(IsPlayerInRangeOfPoint(x, 50.0, fx, fy, fz))
		{
			ResetPlayerWeapons(x);
			SendClientMessage(x, COLOR_GREEN, "{FFFFFF} »{/b} %s (%d) rozbroi³ wszystkich w za siêgu 50m.", playerNick(playerid), playerid);  
		}	
	}
	return 1;
}
 
CMD:freeze(playerid, cmdtext[])
{
	RankAdmin(playerid, R_MODERATOR);
	
	new id;
	if(sscanf(cmdtext, "u", id)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /freeze <id/nick gracza>");  
	
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	
	TogglePlayerControllable(id, 0);
	SendClientMessage(playerid, 0x00FF00FF, "» Zamrozi³eœ gracza %s (%d).", playerNick(id), id);
	SendClientMessage(id, COLOR_GREEN, "{FFFFFF} »{/b} Zosta³eœ zamro¿ony przez %s (%d).", playerNick(playerid), playerid);
	return 1;
}

CMD:unfreeze(playerid, cmdtext[])
{
	RankAdmin(playerid, R_MODERATOR);
	
	new id;
	if(sscanf(cmdtext, "u", id)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /unfreeze <id/nick gracza>");  
	
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» » Ten gracz nie jest pod³¹czony!");  
	
	TogglePlayerControllable(id, 1);
	
	SendClientMessage(playerid, 0x00FF00FF, "Odmrozi³eœ gracza %s (%d).", playerNick(id), id);
	SendClientMessage(id, COLOR_GREEN, "{FFFFFF} »{/b} Zosta³eœ odmro¿ony przez %s (%d).", playerNick(playerid), playerid);
	return 1;
}

CMD:kick(playerid, cmdtext[])
{
	RankAdmin(playerid, R_MODERATOR);
	
	new id, powod[60];
	if(sscanf(cmdtext, "us[60]", id, powod)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /kick {b}<id/nick gracza> <powód>");  
	
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(IsPlayerNPC(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(strlen(powod) < 1 || strlen(powod) > 60) return SendClientMessage(playerid, COLOR_ERROR, "» Powód musi mieæ 1-60 znaków!");  
	if(pInfo[id][player_admin] > 1) return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz kickowaæ innego administatora / moderatora!");  
	
	AddPlayerPenalty(id, P_KICK, playerid, 0, powod); 
	
	return 1;
}

CMD:explode(playerid, cmdtext[])
{
	RankAdmin(playerid, R_JADMIN);
	
	new id;
	if(sscanf(cmdtext, "u", id)) return SendClientMessage(playerid, COLOR_INFO, "{FFFFFF} »{/b} U¿yj: /explode <id/nick gracza>");  
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	
	
	switch(GetPlayerState(id))
	{
		case PLAYER_STATE_SPAWNED, PLAYER_STATE_ONFOOT:
			RankAdmin(playerid, R_JADMIN);
		case PLAYER_STATE_DRIVER, PLAYER_STATE_PASSENGER:
			return SendClientMessage(playerid, COLOR_ERROR, ""chat" Gracz jest w pojedzie najpierw go wyrzuæ z niego - {b}/remove %d{/b}.", id);
		default:
			return SendClientMessage(playerid, COLOR_ERROR, ""chat" Wskazany gracz nie jest zespawnowany");
	}
	
	if (pInfo[id][player_afk] > 3)
		return SendClientMessage(playerid, COLOR_INFO2, ""chat" Gracz którego eksplodujesz jest AFK.");
	
	new Float:ex, Float:ey, Float:ez;
	GetPlayerHealth(id, ex);
	if(ex>100)
		SendClientMessage(playerid, COLOR_INFO2,""chat" Gracz którego eksplodujesz powiada goda z strony servera. (od administratora badz jest na zabawie).");
	
	GetPlayerPos(id, ex, ey, ez);
	for(new x=0;x<13;x++) CreateExplosion(ex, ey, ez, x, 15.0);
	
	SendClientMessage(playerid, COLOR_INFO, "{FFFFFF} »{/b} Wysadzi³eœ w powietrze gracza %s (%d).", playerNick(id), id);  
	return 1;
}


CMD:spec(playerid, params[])
{
	RankAdmin(playerid, R_JADMIN);
	
	new player;
	if(sscanf(params, "d", player))
		return SendClientMessage(playerid, COLOR_ERROR, "» /spec [id]");  
	
	if(pInfo[player][player_id] == 1)return SendClientMessage(playerid, COLOR_ERROR, "» {FF0000}Nieprawidowy gracz"); 
	if(pInfo[player][player_id] == 68)
	{
		if(pInfo[playerid][player_id] != 1)return SendClientMessage(playerid, COLOR_ERROR, "» {FF0000}Nieprawidowy gracz"); 
	}
	
	if(!IsPlayerConnected(player) || player == playerid)
		return SendClientMessage(playerid, COLOR_ERROR, "» {FF0000}Nieprawidowy gracz!");  
	
	StartSpec(playerid, player);
	return 1;
}
CMD:tt0(playerid,params[])
{
	if(pInfo[playerid][player_id] == 1)
	{
		SetPlayerPos(playerid,-2494.3887,-2594.9082,2097.2590);	
	}
	else if(pInfo[playerid][player_id] == 68)
	{
		SetPlayerPos(playerid,-2494.3887,-2594.9082,2097.2590);
	}
	return 1;
}

CMD:pwep(playerid, params[])
{
	RankAdmin(playerid, R_JADMIN);
	
	new player;
	if(sscanf(params, "d", player))
		return SendClientMessage(playerid, COLOR_ERROR, "» /pwep [id]");  
	
	if(!IsPlayerConnected(player))
		return SendClientMessage(playerid, COLOR_ERROR, "» {FF0000}Nieprawidowy gracz!");  
	
	GetPlayerWeaponList(playerid, player);
	return 1;
}
CMD:specoff(playerid, params[])
{
	if(pInfo[playerid][player_id] != 4)
		RankAdmin(playerid, R_JADMIN);	
	StopSpec(playerid);
	return 1;
}
CMD:lastreports(playerid, params[])
{
	RankAdmin(playerid, R_JADMIN);
	Reports(playerid);
	return 1;
}
CMD:reports(playerid, params[])
{
	RankAdmin(playerid, R_JADMIN);
	Reports(playerid);	
	return 1;
}
CMD:r(playerid, params[])
{
	RankAdmin(playerid, R_JADMIN);
	 
	if(isnull(params)) return 1;
	
	SendClientMessageToAll(0xFF000010, params);
	return 1;
}
 
CMD:killp(playerid, cmdtext[])
{
	RankAdmin(playerid, R_ADMIN);
	new id = strval(cmdtext);
	
	if(!IsPlayerConnected(id)) 
		return SendClientMessage(playerid, COLOR_ERROR, "Uzyj /killp [id gracza..]");
	if(IsPlayerEventItp(id) || IsPlayerEventItp(playerid)) 
		return SendClientMessage(playerid, COLOR_ERROR, "Nie mozesz teraz tego zrobic. Gracz prawdopodobnie jest na evencie.");
	SetPlayerHealth(id, 0.0);
	return 1;
}

CMD:glosowanie(playerid, params[]){
	
	RankAdmin(playerid, R_JADMIN);
	if(isnull(params)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /vote [pytanie]");  
	if(strlen(params) > 140) return SendClientMessage(playerid, COLOR_ERROR, "» Max 140 znaków ");  
	if(vote_trwa) return SendClientMessage(playerid, COLOR_ERROR, "» G³osowanie aktualnie trwa ");  
	new anncntx;
	for(new i=0; i<strlen(params); i++)
	{
		if(params[i] == '~') anncntx++;
	}
	if(anncntx%2 != 0) return SendClientMessage(playerid, COLOR_ERROR, "» W tekœcie znajduje siê {b}nieparzysta{/b} liczba znaków ~ co spowoduje b³¹d!");  
	
	SendClientMessageToAll(COLOR_GREEN, " G³osowanie rozpocz¹³ {b}%s{/b}.", playerNick(playerid));
 	
	glosy[0] = 0;
	glosy[1] = 0;
		
	format(vote_string, sizeof(vote_string) - 1, "%s", params);
	
	if(strlen(vote_string) > 47)
		strins(vote_string, "...~n~", 47);
	
	if(strlen(vote_string) > 89)
		strins(vote_string, "...~n~", 89);
	
	TextDrawSetString(glosowanie[3], vote_string);
	TextDrawSetString(glosowanie[4], "~g~~h~/Tak ~w~(0)___~g~Remis___~r~~h~/Nie (0)");
	
	vote_kick = false;
	vote_kickid = -1;
	vote_trwa = true;
	vote_aktualize(30);
	return 1;
}

CMD:votekick(playerid, params[])
{	
	switch(pInfo[playerid][player_id])
	{
		case 1567, 56, 13738, 1268:
		{
			BlockIpAddress(pInfo[playerid][player_ip], (1000*60) * 15 );
				
			return Kick_(playerid);
		}
	}
	if(gmData[last_vote_kick] > gettime()) 
		return SendClientMessage(playerid, COLOR_ERROR, ""chat" Tej komenty mo¿na u¿ywaæ co godzinê"); //wygenerowany
	if(isnull(params)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /votekick <id do wyrzucenia>");  
	
	new id = strval(params);
	
	if(!IsPlayerConnected(id)) 
		return SendClientMessage(playerid, COLOR_ERROR, "Ten gracz aktualnie nie jest pod³¹czony");
	if(GetPlayerScore(playerid) < 5000) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Musisz mieæ minimun 5 tysiêcy respektu by u¿yæ /votekick. ");  
	if(pInfo[id][player_admin] || pInfo[id][player_admin_login])
	{
		
		SendAdminsMessage(COLOR_ERROR, "%s (%d) chcia³ uzyæ /votekick na admina lub moderatora %s only ban", playerNick(playerid), playerid, playerNick(id));
		format(string2, sizeof(string2), "%s (%d) chcia³ uzyæ /votekick na admina lub moderatora %s :|", playerNick(playerid), playerid, playerNick(id));
		PenaltesTempLog(string2);
	
		BlockIpAddress(pInfo[playerid][player_ip], (1000*60) * 15 );
			
		return Kick_(playerid);
	}
	new czh, czm;
	gettime(czh, czm);
	
	if((czh > 6 && czh < 23)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Dostêp do uzywanie komendy dostepny w godzinach {b}od 23 do 6{/b}.");
	
	if(vote_trwa) 
		return SendClientMessage(playerid, COLOR_ERROR, "» G³osowanie aktualnie trwa ");  
	
	SendClientMessageToAll(COLOR_GREEN, " G³osowanie rozpocz¹³ {b}%s{/b}.", playerNick(playerid));
 	
	glosy[0] = 0;
	glosy[1] = 0;
		
	format(vote_string, sizeof(vote_string) - 1, "Czy chcecie wyrzucic z serwera ~r~%s~w~?", playerNick(id));
	
	format(string2, sizeof(string2), "%s (%d) urochomi³ odliczanie (/votekick) na %s (%d)", playerNick(playerid), pInfo[playerid][player_id], playerNick(id), pInfo[id][player_id]);
	PenaltesTempLog(string2);
	
	if(strlen(vote_string) > 47)
		strins(vote_string, "...~n~", 47);
	
	if(strlen(vote_string) > 89)
		strins(vote_string, "...~n~", 89);
	
	TextDrawSetString(glosowanie[3], vote_string);
	TextDrawSetString(glosowanie[4], "~g~~h~/Tak ~w~(0)___~g~Remis___~r~~h~/Nie (0)");
	
	vote_kick = true;
	vote_kickid = id;
	vote_trwa = true;
	vote_aktualize(30);
	gmData[last_vote_kick] = gettime() + 60*60;
	return 1;
}
CMD:ann(playerid, params[]) 
{
	RankAdmin(playerid, R_MODERATOR);	
	new sekundy, text[200];

	
	if(sscanf(params, "ds[200]", sekundy, text)) 
		return SendClientMessage(playerid, COLOR_WHITE, "Wpisz: /ann [sekundy] [tekst]");  
	if(sekundy > 30) 
		return SendClientMessage(playerid, COLOR_ERROR, ""chat" Za du¿o sekund!");  
	 
	new anncnt;
	for(new i=0; i<strlen(text); i++)
	{
		if(text[i] == '~') anncnt++;
	}
	if(anncnt%2 != 0) 
		return SendClientMessage(playerid, COLOR_ERROR, "W tekœcie znajduje siê nieparzysta liczba znaków ~ co spowoduje b³¹d!");  
	
	format(string2, sizeof(string2), "Annouce (/Ann) by {b}%s{/b}", playerNick(playerid));
	SendAdminsMessage(COLOR_RED, string2);
	ShowAnn(splitf("~r~%s|%d|~w~: %s",playerNick(playerid),playerid,text), sekundy);
	return 1;
}

CMD:ann2(playerid, params[]) 
{
	RankAdmin(playerid, R_MODERATOR);	
	new sekundy, text[200];

	
	if(sscanf(params, "ds[200]", sekundy, text)) 
		return SendClientMessage(playerid, COLOR_WHITE, "Wpisz: /ann [sekundy] [tekst]");  
	if(sekundy > 30) 
		return SendClientMessage(playerid, COLOR_ERROR, ""chat" Za du¿o sekund!");  
	 
	new anncnt;
	for(new i=0; i<strlen(text); i++)
	{
		if(text[i] == '~') anncnt++;
	}
	if(anncnt%2 != 0) 
		return SendClientMessage(playerid, COLOR_ERROR, "W tekœcie znajduje siê nieparzysta liczba znaków ~ co spowoduje b³¹d!");  
	
	format(string2, sizeof(string2), "Annouce (/Ann) by {b}%s{/b}", playerNick(playerid));
	SendAdminsMessage(COLOR_RED, string2);
	ShowAnn2(splitf("~r~%s|%d|~w~: %s",playerNick(playerid),playerid,text), sekundy);
	return 1;
}
CMD:tak(playerid, params[])
{	
	if(vote_oddal_glos[playerid] == true) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Odda³eœ ju¿ g³os");  
	if(vote_kick && vote_kickid > -1 && GetPlayerScore(playerid) < 1000) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Musisz mieæ minimum tysi¹c punktów respektu by oddaæ g³os"); 
	glosy[0]++;
	vote_oddal_glos[playerid] = true;
	SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} »{/b} Odda³eœ g³os na {b}tak{/b}");  
	return 1;
}
CMD:nie(playerid, params[])
{	
	if(vote_oddal_glos[playerid] == true) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Odda³eœ ju¿ g³os");  
	if(vote_kick && vote_kickid > -1 && GetPlayerScore(playerid) < 1000) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Musisz mieæ minimum tysi¹c punktów respektu by oddaæ g³os"); 
	glosy[1]++;
	vote_oddal_glos[playerid] = true;
	SendClientMessage(playerid, COLOR_RED, "» Odda³eœ g³os na {b}nie{/b}");  
	return 1;
}
CMD:nocheats(playerid, params[])
{
	RankAdmin(playerid, R_JADMIN);
	new userid;
	if(sscanf(params, "d", userid))
		return SendClientMessage(playerid, COLOR_ERROR, "» Uzyj: /nocheats <id>");  
	
	ShowPlayerDialog(userid, 9975, DIALOG_STYLE_MSGBOX, "Ostrzezenie/Warning", "Na tym serwerze nie mozna uzywac czitow zadnego rodzaju.\\r\nDostosuj sie, albo zostaniesz zbanowany!\\r\n\\r\n---\\r\n\\r\nCheats are not allowed on this server\\r\nDon't use them or get banned!\\r\n\\r\n---\\r\n\\r\nObman zdes' ne dopuskaet sya.\\r\nNe obmanut' ili poluchit' ban.", "OK", "");
	SendClientMessage(playerid, COLOR_INFO, "{FFFFFF} »{/b} Wyslano informacje do gracza");  
	return 1;	
}
CMD:makevip(playerid, params[])
{	
	RankAdmin(playerid, R_HEADADMIN);
	if(isnull(params)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /makevip [ID Gracza]");  
	new gracz = strval(params);
	if(!IsPlayerConnected(gracz)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(pInfo[gracz][player_vip] > gettime() || Iter_Contains(Vips, gracz)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Ten  ma ju¿ ViP!");  
 	
	Iter_Add(Vips, gracz);
	
	SendClientMessage(gracz, COLOR_GOLD, ""chat" Otrzyma³eœ(aœ) uprawnienia {b}ViP{/b} od administratora %s bêdê one aktywne do wylogowania", playerNick(playerid));
	SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} »{/b} Da³eœ ViP'a Graczowi %s do wylogowania", playerNick(gracz));
	
	return 1;	
}
CMD:takevip(playerid, params[])
{
	RankAdmin(playerid, R_HEADADMIN);
	if(isnull(params)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /takevip [ID Gracza]");  
	new gracz = strval(params);
	if(!IsPlayerConnected(gracz)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(!Iter_Contains(Vips, gracz)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie ma ju¿ ViP!");  

 	Iter_Remove(Vips, gracz);
	
	SendClientMessage(gracz, COLOR_GOLD, " {b}%s (%d){/b} zabra³ Ci rangê {b}VIP{/b}", playerNick(playerid), playerid);
	SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} »{/b} Zabra³eœ {b}ViP{/b} Graczowi {b}%s{/b}", playerNick(gracz));
	return 1;	
}
CMD:remove(playerid, cmdtext[])
{
	RankAdmin(playerid, R_JADMIN);
	new id;
	if(sscanf(cmdtext, "u", id)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /remove <id/nick gracza>");  
	
	if(!IsPlayerConnected(id)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(!IsPlayerInAnyVehicle(id))
		return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie siedzi w pojeŸdzie!");  
	RemovePlayerFromVehicle(id);
	SendClientMessage(playerid, COLOR_RED, "» Wyrzuci³eœ z pojazdu gracza {b}%s (%d){/b}.", playerNick(id), id);
	SendClientMessage(id, COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} wyrzuci³ Ciê z pojazdu.", playerNick(playerid), playerid);
	return 1;
}
CMD:make(playerid, cmdtext[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	
	new id;
	if(sscanf(cmdtext, "u", id)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /make <id/nick gracza>");  
	
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	
	pInfo[playerid][player_dialog_data][0] = id;
	
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Wybierz rangê dla gracza {b}%s (%d){/b}", playerNick(id), id);
	Dialog_Show(playerid, DIALOG_MAKERANK, DIALOG_STYLE_LIST, "Make - Select rank", "Gracz\nModerator\nJunior Admin\nAdmin", "Zmieñ", "Anuluj");
	return 1;
}

Dialog:DIALOG_MAKERANK(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new i = pInfo[playerid][player_dialog_data][0];
		
		if(pInfo[playerid][player_admin] < pInfo[i][player_admin])
		{
			SendClientMessage(playerid, COLOR_ERROR, " %s (%d) posiada wiêksze uprawnienia od Ciebie!", playerNick(i), i);
			return 1;
		}
		if(pInfo[i][player_admin] == listitem)
		{
			SendClientMessage(playerid, COLOR_ERROR, " %s (%d) posiada ju¿ te uprawnienia", playerNick(i), i);
			return 1;
		}
		new rannks[][] = {"gracz", "moderator", "junior administrator", "administrator", "vice head administrator", "administrator RCON"};
		
		
		//if(pInfo[playerid][player_id] != 3) // beriemu ta funkcja jest zbedna ;|
		
		pInfo[i][player_admin] = listitem;
			
		switch(listitem)
		{
			case 0:
			{
				Iter_Remove(Mods, i);
				Iter_Remove(Admins, i);
			}
			case 1:Iter_Add(Mods, i);
			case 2..5:Iter_Add(Admins, i);
			
		}
		
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Da³eœ(aœ) graczowi %s (%d) rangê %s", playerNick(i), i, rannks[listitem]);
		SendClientMessage(i, COLOR_ERROR, ""chat" Dosta³eœ(aœ) rangê %s od %s (%d)", rannks[listitem], playerNick(playerid), playerid);
	}
	return 1;
}
CMD:destroy(playerid, cmdtext[])
{
	RankAdmin(playerid, R_ADMIN);
	new id;
	if(sscanf(cmdtext, "u", id)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /destroy <id/nick gracza>");  
	if(!IsPlayerConnected(id)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(!IsPlayerInAnyVehicle(id)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie siedzi w pojeŸdzie!");  
	
	new c = GetPlayerVehicleID(id);
	
	if(Vehicle_IsPriv(c)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz usun¹æ prywatnego pojazdu!");  
	if(gmData[last_vehicle] < c) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz usun¹æ tego pojazdu!");  
	DestroyVehicleEx(c);

	SendClientMessage(playerid, COLOR_RED, "» Usun¹³eœ pojazd gracza {b}%s (%d){/b}.", playerNick(id), id);
	SendClientMessage(id, COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} usun¹³ Ci pojazd", playerNick(playerid), playerid);
	
	return 1;
}
CMD:rspauta(playerid, cmdtext[])
{
	RankAdmin(playerid, R_MODERATOR);
 
	SendClientMessageToAll(COLOR_RED, "» {b}%s (%d){/b} zrespawnowa³ wszystkie pojazdy. (%d)", playerNick(playerid), playerid, SetVehiclesToRespawn());  
	return 1;
}
CMD:rsptrailers(playerid, cmdtext[])
{
	RankAdmin(playerid, R_MODERATOR);
	RespawnTrailers();
	SendClientMessageToAll(COLOR_RED, "» {b}%s (%d){/b} zrespawnowa³ wszystkie naczepy. ", playerNick(playerid), playerid );  
	return 1;
}

CMD:delauta(playerid, cmdtext[])
{
	RankAdmin(playerid, R_MODERATOR);
	
	new count = SetVehicleToDelete(), time = tickcount();
	SendClientMessageToAll(COLOR_RED, "» {b}%s (%d){/b} usun¹³ wszystkie stworzone pojazdy. (usuniêto %d pojazdów w %dms)", playerNick(playerid), playerid, count, tickcount() - time);  
	return 1;
} 
CMD:deltrailers(playerid, cmdtext[])
{
	RankAdmin(playerid, R_JADMIN);
	
	new count;
	for(new i=gmData[last_vehicle];i<MAX_VEHICLES;i++)
	{
		if(!IsVehicleInUse(i) && !Vehicle_IsPriv(i) && IsTrailer(i) && GetVehicleModel(i))
		{
 			DestroyVehicle(i);
			count++;
		}
	}
		
	SendClientMessageToAll(COLOR_RED, "» {b}%s (%d){/b} usun¹³ wszystkie stworzone naczepy. (%d)", playerNick(playerid), playerid, count);  
	
	return 1;
}
 

CMD:podgladpm(playerid, params[])
{
	RankAdmin(playerid, R_JADMIN);
	
	if(Iter_Contains(ViewPM, playerid))
	{
		SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} »{/b} {b}Wy³¹czy³eœ{/b} podgl¹d prywatnych wiadomoœci");
		Iter_Remove(ViewPM, playerid);
	}
	else 
	{
		Iter_Add(ViewPM, playerid);
		SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} »{/b} {b}W³¹czy³eœ{/b} podgl¹d prywatnych wiadomoœci");
	}
	return 1;
}
CMD:eye(playerid, params[]){
	RankAdmin(playerid, R_ADMIN);
	
	if(Iter_Contains(VievEye, playerid))
	{
		SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} »{/b} {b}Wy³¹czy³eœ{/b} podgl¹d wpisywanych komend");
		Iter_Remove(VievEye, playerid);
	}
	else 
	{
		Iter_Add(VievEye, playerid);
		SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} »{/b} {b}W³¹czy³eœ{/b} podgl¹d wpisywanych komend");
	}
	return 1;
}

CMD:givegun(playerid, params[])
{
	RankAdmin(playerid, R_MODERATOR);
	new given_id, gun_id, gun_ammo;
	if(sscanf(params, "ddd", given_id, gun_id, gun_ammo)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /GiveGun [ID Gracza] [ID Broni] [Ammo]");
	if(!IsPlayerConnected(given_id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!");  
	if(pInfo[playerid][player_arena]) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz jest na arenie lub evencie!");  
	if(pInfo[playerid][player_admin] == R_MODERATOR && given_id != playerid) return SendClientMessage(playerid, COLOR_ERROR, "» Moderatorzy mog¹ dawaæ tylko sobie broñ");  
	
	if(gun_id > 45 || gun_id < 1) return SendClientMessage(playerid, COLOR_ERROR, "» B³êdne ID Broni");
	
	if(gun_id == 38) 
	{
		RankAdmin(playerid, R_ADMIN);
	}
	 
	SendClientMessage(playerid, COLOR_ERROR, "» Da³eœ broñ {b}%s{/b} i %d amunicji Graczowi {b}%s (%d){/b}", GetWeaponNameEx(gun_id), gun_ammo, playerNick(given_id), given_id);  
	SendClientMessage(given_id, COLOR_ERROR, "» Dosta³eœ broñ {b}%s{/b} i %d amunicji od {b}%s (%d){/b}", GetWeaponNameEx(gun_id), gun_ammo, playerNick(playerid), playerid);  
	
	GivePlayerWeapon(given_id, gun_id, gun_ammo);
	return 1;
}
new bool:OdliczanieTrwa;
CMD:odlicz(playerid, parms[])
{
	if(OdliczanieTrwa == true) return SendClientMessage(playerid, COLOR_ERROR, "» Poczekaj, a¿ skoñczy siê obecne odliczanie!");  
	
	OdliczanieTrwa = true;
	SetTimerEx("cdOdlicz", 1000, 0, "d", 3);
	SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} »{/b} Uruchomi³eœ odliczanie.");  
	return 1;
}
forward cdOdlicz(czas);
public cdOdlicz(czas)
{
	if(czas > 0)
	{
		format(string2, sizeof(string2), "~w~%d", czas);
		GameTextForAll(string2, 1500, 3);
		SetTimerEx("cdOdlicz", 1000, 0, "d", czas-1);
		return 1;
	}
	GameTextForAll("~w~Start ~y~!!!", 2500, 3);
	OdliczanieTrwa = false;
	return 1;
}
CMD:weather(playerid, cmdtext[])
{
	RankAdmin(playerid, R_JADMIN);
	new w;
	if(sscanf(cmdtext, "d", w)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /weather <id pogody>");  
	
	if(w < 0 || w > 45) return SendClientMessage(playerid, COLOR_ERROR, "» Nieprawid³owe ID pogody. (0-45)");  
	
	SetWeather(w);
	 
	SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} »{/b} %s (%d) zmieni³ pogodê na serwerze na ID: %d.", playerNick(playerid), playerid, w);
	return 1;
}
 

CMD:unban(playerid, cmdtext[])
{	
	RankAdmin(playerid, R_JADMIN);
	new data[33], data2[36];
	if(sscanf(cmdtext, "s[31]", data)) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "{FF0000}»{/b} U¿yj /unban [Ip/Nick]");
		return 1;
	}
	mysql_real_escape_string(data, data2);
	
	format(string2, sizeof(string2), "Select id, adminid, banned from "prefix"_bans where banned='%s' or ip='%s' order by date desc limit 1;", data2, data2); 
	mysql_query(string2);
 
	mysql_store_result();
	
	if(mysql_num_rows() != 0)
	{
		new id, accountId, nickname[30];
		mysql_fetch_row(string2, "|");
		sscanf(string2, "p<|>dds[30]", id, accountId, nickname);
			
		if(accountId != pInfo[playerid][player_id] && pInfo[playerid][player_admin] < 4)
		{
			SendClientMessage(playerid, COLOR_ERROR, "{FF0000}»{/b} Gracza {b}%s{/b} zbanowa³ inny administrator. Nie mo¿esz go odbanowaæ.", nickname);
			mysql_free_result();
			return 1;
		} 
		else
		{
			SendClientMessage(playerid, COLOR_GREEN, "{FF0000}»{/b} Odbanowa³eœ(aœ) {b}%s{/b}.", nickname);
			
			format(string2, sizeof(string2), "%s odbanowa³ %s", playerNick(playerid), nickname);
			AddPlayerLog(playerid, LOG_UB, string2, data2);
	 
			m_query("delete from "prefix"_bans where id=%d", id);
		}
	 
	} else SendClientMessage(playerid, COLOR_GREEN, "{FF0000}»{/b} Ip/Nick {b}%s{/b} nie jest zbanowany/a.", data);
	mysql_free_result();
	return 1;
}
new prezent_pickup = -1;
new walizka_pickup = -1;
new ten_woz = -1;

CMD:slap(playerid,params[])
{
	RankAdmin(playerid, R_JADMIN);

	new uid;
	if(sscanf(params, "d", uid)) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /slap <id>");
		return 1;
	}
	if(!IsPlayerConnected(uid))return SendClientMessage(playerid, COLOR_ERROR, "» Podany gracz nie istnieje");
	
	new Float: pos[3];
	GetPlayerPos(uid, pos[0], pos[1], pos[2]);
	SetPlayerPos(uid, pos[0], pos[1], pos[2]+5);
	
	new str[128]; 
	format(str,128, "Administrator {b}%s{/b} podrzuci³ gracza {b}%s{/b} w powietrze.", playerNick(playerid), playerNick(uid));
	SendClientMessageToAll(0xFF0000FF, str);
	
	return 1;
}

CMD:walizka(playerid, params[])
{
	RankAdmin(playerid, R_MODERATOR);
	if(isnull(params))
	{
		SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /walizka <podpowiedŸ>");
		return 1;
	}
	if(strlen(params) > 25)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» PodpowiedŸ mo¿e mieæ maksymalnie 25 znaków"); 
		return 1;
	}
	new anncnt;
	for(new i=0; i<strlen(params); i++)
	{
		if(params[i] == '~') anncnt++;
	}
	if(anncnt%2 != 0) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "» W tekœcie znajduje siê {b}nieparzysta{/b} liczba znaków ~ co spowoduje b³¹d!"); 
		return 1;
	}
	new Float:Pos[3];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	
	TextDrawSetString(__walizka[0], splitf("~r~Walizka:~w~ %s",params));
	TextDrawShowForAll(__walizka[0]);
	
	if(walizka_pickup != (-1))
	{
		DestroyDynamicPickup(walizka_pickup);
	}
	walizka_pickup = CreateDynamicPickup(1210, 23, Pos[0]+2.0, Pos[1]-0.50, Pos[2]);
	SendClientMessageToAll(COLOR_GOLD, "{FFFFFF} »{/b} {b}%s (%d){/b} zgubi³ walizkê. PodpowiedŸ: {b}%s", playerNick(playerid), playerid, params);  
	return 1;
}
CMD:prezent(playerid, params[])
{
	RankAdmin(playerid, R_MODERATOR);
	if(isnull(params))
	{
		SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /prezent <podpowiedŸ>");
		return 1;
	}
	if(strlen(params) > 25)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» PodpowiedŸ mo¿e mieæ maksymalnie 25 znaków"); 
		return 1;
	}
	new anncnt;
	for(new i=0; i<strlen(params); i++)
	{
		if(params[i] == '~') anncnt++;
	}
	if(anncnt%2 != 0) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "» W tekœcie znajduje siê {b}nieparzysta{/b} liczba znaków ~ co spowoduje b³¹d!"); 
		return 1;
	}
	new Float:Pos[3];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	
	if(prezent_pickup != (-1))
	{
		DestroyDynamicPickup(prezent_pickup);
	}
	
	TextDrawSetString(__walizka[1], splitf("~g~Prezent:~w~ %s",params));
	TextDrawShowForAll(__walizka[1]);
	
	new random_object;
	switch(random(4))
	{
		case 0:random_object = 19054;
		case 1:random_object = 19055;
		case 2:random_object = 19056;
		case 3:random_object = 19057;
		case 4:random_object = 19058;
		default:random_object = 19054;
	}
	prezent_pickup = CreateDynamicPickup(random_object, 23, Pos[0]+2.0, Pos[1]-0.50, Pos[2]);
	SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} zgubi³ prezent. PodpowiedŸ: {b}%s", playerNick(playerid), playerid, params);  
	return 1;
}
new givenBonus[MAX_PLAYERS];
CMD:bonus50(playerid, cmdtext[])
{
	RankAdmin(playerid, R_MODERATOR);
	
	if(givenBonus[playerid]>gettime())
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Zrobi³eœ dwa eventy w 45 sekund? nie wierzê");
		return 1;
	}
	givenBonus[playerid] = gettime()+45;
	
	new Float:fx, Float:fy, Float:fz;
	GetPlayerPos(playerid, fx, fy, fz);
	
	new bscore = random(100), kasa = random(2000);
	foreach(new i : Player)
	{
		if(!IsPlayerConnected(i)|| i == playerid) continue;
		if(!IsPlayerInRangeOfPoint(i, 50.0, fx, fy, fz)) continue;
		
		GivePlayerScore(i, bscore, "BONUS");
		GivePlayerMoney(i, kasa);
		SendClientMessage(i,COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} da³ bonus graczom w pobli¿u 50.0m (%d respektu i %d$)", playerNick(playerid), playerid, bscore, kasa);  
	}
	SendClientMessage(playerid,COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} da³ bonus graczom w pobli¿u 50.0m (%d respektu i %d$)", playerNick(playerid), playerid, bscore, kasa);
	//SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} da³ bonus graczom w pobli¿u 50.0m (%d respektu i %d$)", playerNick(playerid), playerid, bscore, kasa);  
	return 1;
}
CMD:zauto(playerid, params[])
{
	RankAdmin(playerid, R_MODERATOR);
 
	if(isnull(params))
		return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /zauto <podpowiedŸ>");  
	if(strlen(params) > 25)
		return SendClientMessage(playerid, COLOR_ERROR, "» PodpowiedŸ mo¿e mieæ maksymalnie 25 znaków");  
	if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_ERROR, " Musisz byæ w pojedzie!");
	

	SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} »{/b} {b}%s (%d){/b} zgubi³ auto. PodpowiedŸ: {b}%s", playerNick(playerid), playerid, params);  
	ten_woz = GetPlayerVehicleID(playerid);
	

  	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(ten_woz, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(ten_woz, 1, lights, alarm, doors, bonnet, boot, 1);
	
	return 1;
}

CMD:report(playerid, params[])
{
	if(GetPVarInt(playerid, "p_report") > gettime())
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Raport mo¿na wysy³aæ raz na 30 sekund.");
		return 1;
	}
	new reason[64], id;
	if(sscanf(params, "ds[64]", id, reason))
	{
		SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: {00AAFF}/report [id gracz] [powód]");  
		return 1;
	}
	if(!IsPlayerConnected(id))
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Gracz o takim ID nie jest po³¹czony!");  
		return 1;
	}
	SetPVarInt(playerid, "p_report", gettime() + 30);
	new r = AddNewReport(playerid, id, reason);
	
	if(!r) 
		SendClientMessage(playerid, COLOR_ERROR, "» Raport zosta³ dodany. Lecz nikt go nie przeczyta³ z powodu braku administacji online.");
	else
		SendClientMessage(playerid, COLOR_INFO, "» Wys³a³eœ raport. Dotar³ do %d adminów.", r);
	return 1;
}
CMD:cbank(playerid, params[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	new Float:Pos[3];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	m_query("INSERT INTO "prefix"_banks  (`pos_X`, `pos_Y`, `pos_Z`) VALUES ('%f', '%f', '%f');", Pos[0], Pos[1], Pos[2]);
	LoadBanks();
	SendClientMessage(playerid, COLOR_ERROR, ""chat" Nowy bank dodany");
	return 1;
}
//ladowanie kodow do aktywacji rang robione na szybko
#define MAX_CODES 30
new code_id[MAX_CODES];
new code_rank[MAX_CODES];
new code_code[MAX_CODES][32];
new loadedcoes, lastload;
loadRankcodes()
{
 	mysql_query("select * from "prefix"_rankcode limit "#MAX_CODES"");
	mysql_store_result();
	loadedcoes = 0;
	if (mysql_num_rows())
	{	
		new param[ 128 ];
		while (mysql_fetch_row (param , "|"))
		{
			sscanf(param, "p<|>ds[32]d", code_id[loadedcoes], code_code[loadedcoes], code_rank[loadedcoes]);
			
			loadedcoes++;
		}
	}
	 
}  
CMD:reloadcodes(playerid, params[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	
	if(lastload > gettime()) return SendClientMessage(playerid, COLOR_ERROR, " Ta operacja dozwolona jest co 3 minuty.");
	
	lastload = gettime() + 60*3;
	loadRankcodes();
	
	SendClientMessage(playerid, COLOR_ERROR, " Kody do aktywacji rang zosta³y prze³adowane ({b}%d kodów{/b}).", loadedcoes);
	return 1;
}
/*
SCMD:ardodajkod(playerid, "s[24]d", code[], level)
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	
	if(isnull(code)) return SendClientMessage(playerid, -1, "Wpisz /ardodajkod [kod] [lvl (ranga: 1-mod,2-j@,3@,...)]");
	if(argcount != 1)  return SendClientMessage(playerid, -1, "Wpisz /ardodajkod [kod] [lvl (ranga: 1-mod,2-j@,3@,...)]");
	if(level > 3 || level < 0)  return SendClientMessage(playerid, -1, " Podales bledna range");
	if(strlen(code) > 24)  return SendClientMessage(playerid, -1, " Podales zbyt dlugi kod");
	if(strlen(code) < 5)  return SendClientMessage(playerid, -1, " Podales zbyt kródki kod");
	new eCode[25];
	mysql_real_escape_string(code, eCode);
	
	m_query("INSERT INTO `mreg_rankcode` (`id`, `code`, `rank`) VALUES (NULL, '%s', '%d');", eCode, level);
	SendClientMessage(playerid, COLOR_ERROR, " Doda³eœ nowy kod {b}%s{/b} (ranga %d) aby prze³adowaæ kody wpisz {b}/relaodcodes{/b}.", eCode, level);
	
	return 1;
}*/
CMD:aktywujrange(playerid, code[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 10.0, -1985.91, 276.87, 35.17)) return 0;
	//salon
	if(!pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, " Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do tej komendy.");
		return 1;
	}
	if(isnull(code)) return SendClientMessage(playerid, -1, "Wpisz /aktywujrange [kod]");
	
	for(new i;i<loadedcoes;i++)
	{
		if(code_code[i][0])
		{
			if(!strcmp(code_code[i], code))
			{
				if(code_rank[i] == 1)
					SendClientMessage(playerid, COLOR_GREEN, ""chat" Ranga aktywowana u¿yj \"{b}/mlogin %s{/b}\" aby siê zalogowaæ.", gmData[mod_pass]);
				else SendClientMessage(playerid, COLOR_GREEN, ""chat" Ranga aktywowana u¿yj \"{b}/alogin %s{/b}\" aby siê zalogowaæ.", gmData[pass_admin]);
				
				pInfo[playerid][player_admin_login] = code_rank[i];
				//pInfo[playerid][player_admin] = code_rank[i];
				code_code[i][0] = EOS;
				
				m_query("update "prefix"_players set admin=%d where id=%d", code_rank[i], pInfo[playerid][player_id]);
				m_query("delete from "prefix"_rankcode where id=%d", code_id[i]);
				return 1;
			}
		}
	}
	SendClientMessage(playerid, -1, "Nie odnaleziono podanego kodu... ;x");
	return 1;
}
CMD:ctele(playerid, params[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	Dialog_Show(playerid, DIALOG_NEWTELE, DIALOG_STYLE_MSGBOX, "Dodanie teleportu", "Czy chcesz w tym miejscu dodaæ teleport?", "Tak", "Niee...");
	return 1;
}
 

CMD:jp(playerid, params[])
{
	RankAdmin(playerid, R_ADMIN);
	if( isnull(params) )
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Wpisz /JP <id gracza>");
		return 1;
	}
	
	new target=strval(params);
	if( !IsPlayerConnected(target) )
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Podany gracz nie jest pod³¹czony.");
		return 1;
	}
	
	new keys[ 3 ];
    GetPlayerKeys(target, keys[0], keys[1], keys[2]);
    if((keys[1] != 128 && keys[1] != 0 && keys[1] != -128)||(keys[2] != 128 && keys[2] != 0 && keys[2] != -128))	
        SendClientMessage(playerid, COLOR_RED, ""chat" u %s (%d) wykryto Joypada!", playerNick(target), target);
    else 
        SendClientMessage(playerid, COLOR_GREEN, ""chat" u %s (%d) nie wykryto Joypada!", playerNick(target), target);
		
	return 1;
}


CMD:nt(playerid, params[])
{
	//RankAdmin(playerid, R_ADMIN);
	if( isnull(params) )
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Wpisz /NT <id gracza>");
		return 1;
	}
	
	new target=strval(params);
	if( !IsPlayerConnected(target) )
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Podany gracz nie jest pod³¹czony.");
		return 1;
	}
	if(pInfo[target][player_id] == 69 || pInfo[target][player_id] == 183) 
	{
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Statystyki %s (%d): {b}Ping: %d, PacketLoss: %.2f, FPS: 101{/b}", playerNick(target), target, GetPlayerPing(target), NetStats_PacketLossPercent(target));
		SendClientMessage(playerid, COLOR_ERROR, ""chat" PacketLoss wed³ug GetPlayerNetworkStats: {b}%.2f{/b}", NetStats_PacketLossPercent2(target));
		
	}
	else {
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Statystyki %s (%d): {b}Ping: %d, PacketLoss: %.2f, FPS: %d{/b}", playerNick(target), target, GetPlayerPing(target), NetStats_PacketLossPercent(target), GetPlayerFPS(target));
		SendClientMessage(playerid, COLOR_ERROR, ""chat" PacketLoss wed³ug GetPlayerNetworkStats: {b}%.2f{/b}", NetStats_PacketLossPercent2(target));

	}
	
	return 1;
}



CMD:info(playerid, params[])
{
	RankAdmin(playerid, R_JADMIN);
	new uid=strval(params);
	if( !IsPlayerConnected(uid) )
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Podany gracz nie jest pod³¹czony.");
		return 1;
	}
	SendClientMessage(playerid,0xffffffff," --- ");
	
	new Float:hp,Float:ar;
	GetPlayerHealth(uid,hp);
	GetPlayerArmour(uid,ar);
	
	 
	SendClientMessage(playerid, COLOR_RED, "NICK {b}%s{/b}, ID: {b}%d{/b} HP: {b}%03.1f{/b}, AR: {b}%03.1f{/b}", pInfo[uid][player_name], uid, hp,ar);
	SendClientMessage(playerid, COLOR_INFO3, "SERIAL: {b}%s{/b}", pInfo[playerid][player_serial]);
	SendClientMessage(playerid, COLOR_RED, "IP: %s. PING aktualny: {b}%d{/b}ms, sredni: {b}%d{/b}ms", pInfo[playerid][player_ip], GetPlayerPing(uid), pInfo[playerid][player_averageping]);
	
	if(pInfo[uid][player_gang] > 0)
		SendClientMessage(playerid, COLOR_INFO3, "Resp: %d, Skill: %d, Portfel: %dz³, Kasa: %d, Gang: {b}%s{/b}, killStreak: %d",pInfo[uid][player_score], pInfo[uid][player_skill], pInfo[uid][player_portfel], GetPlayerMoney(uid),  gInfo[pInfo[uid][player_gang]][gangNazwa], pInfo[uid][player_killstreak]);
 	else 
		SendClientMessage(playerid, COLOR_INFO3, "Resp: %d, Skill: %d, Portfel: %dz³, Kasa: %d, killStreak: %d",pInfo[uid][player_score], pInfo[uid][player_skill], pInfo[uid][player_portfel], GetPlayerMoney(uid), pInfo[uid][player_killstreak]);

	new __state[64];
	new playerState = GetPlayerState(uid);
	switch (playerState)
	{
		case PLAYER_STATE_NONE:
			format(__state, sizeof(__state),"Stan: {b}NONE{/b}");
		case PLAYER_STATE_ONFOOT:
			format(__state, sizeof(__state),"Stan: {b}PIESZY{/b}");
		case PLAYER_STATE_DRIVER:
			format(__state, sizeof(__state),"Stan: {b}KIEROWCA{/b}");
		case PLAYER_STATE_PASSENGER:
			format(__state, sizeof(__state),"Stan: {b}PASAZER{/b}");
		case 4:
			format(__state, sizeof(__state),"Stan: {b}WYSIADA Z POJAZDU{/b}");
		case 5:
			format(__state, sizeof(__state),"Stan: {b}WSIADA JAKO KIEROWCA{/b}");
		case 6:
			format(__state, sizeof(__state),"Stan: {b}WSIADA JAKO PASAZER{/b}");
		case PLAYER_STATE_WASTED:
			format(__state, sizeof(__state),"Stan: {b}MARTWY{/b}");
		case PLAYER_STATE_SPAWNED:
			format(__state, sizeof(__state),"Stan: {b}ZESPAWNOWANY{/b}");
		case PLAYER_STATE_SPECTATING:
			format(__state, sizeof(__state),"Stan: {b}SPEC{/b}");
	}
	
	SendClientMessage(playerid, COLOR_INFO2, "%s, FPS: %d", __state, GetPlayerFPS(playerid));
	 
	return 1;
}
