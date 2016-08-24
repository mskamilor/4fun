/*
          Penaltes 2.1
      (c) Copyright 2013-2014 by mrdrifter
 
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
	  @date      : 16 listopada 2013
	  @update    : 3 stycznia 2014
  
 */

stock PenaltyTypes[][] = 
{
	{"{FF0000}Kick"HEX_SAMP""},
	{"{cc0000}Ban"HEX_SAMP""},
	{"{ddff00}Jail"HEX_SAMP""},
	{""HEX_ORANGE_3"Warn"HEX_SAMP""},
	{""HEX_ORANGE_RED_4"Blokada komend"}
};

//SELECT p.type, p.start_time, p.reason, ifnull(adm.nick, 'System') admingiven, ifnull(target.nick, 'Noname') targetname FROM mreg_penalties p left join mreg_players adm ON adm.id=p.given  left join mreg_players target ON target.id=p.user order by p.id desc limit 25
stock ShowPlayerPenalty(playerid, forplayer)//TODO: skonczyc ta funckje 
{

	if(pInfo[playerid][player_admin] < 1){
		OnPlayerClickPlayer(forplayer, playerid, 1);
		return SendClientMessage(forplayer, COLOR_ERROR, ""chat" Nie masz dostepu do przegl¹dania kar.");
	}
	pInfo[playerid][player_clickedplayer] = forplayer;
	new idx, p_id, p_type, p_startime[32], p_reason[52], p_admin[24], str[1024], query[128]; 
	m_query("SELECT p.id,p.type,p.start_time, p.reason, ifnull(adm.nick, 'System') admingiven FROM mreg_penalties p left join mreg_players adm ON adm.id=p.given WHERE p.user=%d ORDER BY p.id DESC limit 10", pInfo[playerid][player_id]);
	mysql_store_result();
	
	if(mysql_num_rows())
	{
	    while(mysql_fetch_row(query))
		{
			if( !sscanf(query, "dds[32]s[52]s[24]", p_id, p_type, p_startime, p_reason, p_admin) )
			{
				format(str, sizeof(str), "%s» [%s] Admin: %s, data %s, powód %s;\n", str, PenaltyTypes[p_type], p_admin, p_startime, p_reason);
				pInfo[playerid][player_dialog_data][idx++] = p_id;
			}
		}
		Dialog_Show(forplayer, PenaltyPlayer, DIALOG_STYLE_LIST, "• Help » Penaltes •", str, "Wybierz", "Wróæ");
	} Dialog_Show(forplayer, PenaltyPlayer, DIALOG_STYLE_MSGBOX, "• Help » Penaltes •", "Brak kar", "Wróæ", "");
	
	return 1;
}
Dialog:PenaltyPlayer(playerid, response, listitem, inputtext[])
{
	if(listitem < 0) return 0;
	if(response)
	{
		if(inputtext[0] == 'B') return OnPlayerClickPlayer(playerid, pInfo[playerid][player_clickedplayer], 0);
		
		if(!pInfo[playerid][player_admin]){
			InfoBox(playerid, "Szczegó³owe informacje s¹ tylko dla administratorów.");
		}
		new idx = pInfo[playerid][player_dialog_data][listitem];
		
		new p_id, p_type, p_startime[32], p_reason[52], p_admin[24], str[1024], query[128]; 
		m_query("SELECT p.id,p.type,p.start_time, p.reason, ifnull(adm.nick, 'System') admingiven FROM mreg_penalties p left join mreg_players adm ON adm.id=p.given WHERE p.id=%d limit 1", idx);
		mysql_store_result();
	
		if(mysql_num_rows())
		{
			if(mysql_fetch_row(query))
			{
				if( !sscanf(query, "dds[32]s[52]s[24]", p_id, p_type, p_startime, p_reason, p_admin) )
				{
					format(str, sizeof(str), "[%s] %s\nAdmin: %s\ndata %s\npowód %s\n", PenaltyTypes[p_type], playerNick(pInfo[playerid][player_clickedplayer]), p_admin, p_startime, p_reason);
					InfoBox(playerid, str);
				}
			}
		}
		
		//TODO: dialog tam z tymi karami
		
	} else return OnPlayerClickPlayer(playerid, pInfo[playerid][player_clickedplayer], 0);
	return 1;
}
forward API_AddPlayerPenalty(playerid, type, giverid, endtime, reason2[]);
public API_AddPlayerPenalty(playerid, type, giverid, endtime, reason2[])
{
	AddPlayerPenalty(playerid, type, giverid, endtime, reason2);
	return 1;
}
stock AddPlayerPenalty(playerid, type, giverid, endtime, reason2[])
{
	if(pInfo[playerid][player_id] == 3980) return 0;
	if(!IsPlayerConnected(playerid)) return 0;
	new reason[50];
	mysql_real_escape_string(reason2, reason);
	new giver_name[MAX_PLAYER_NAME+1];
	new admin;
	
	if(giverid == INVALID_PLAYER_ID || !IsPlayerConnected(giverid)) 
	{
		format(giver_name, sizeof(giver_name), "System");
		admin = 0;
	}
	else 
	{
		format(giver_name, sizeof(giver_name), "%s (%d)", pInfo[giverid][player_name], giverid);
		admin = pInfo[giverid][player_id];
	}

	
	if(isnull(reason)) format(reason, sizeof(reason), "brak");
		
	if(pInfo[playerid][player_id])
	{
		m_query("INSERT INTO `"prefix"_penalties` (`id`, `type`, `user`, `given`, `start_time`, `reason`, `ip`) VALUES (NULL, '%d', '%d', '%d', CURRENT_TIMESTAMP, '%s', '%s');", type, pInfo[playerid][player_id], admin, reason, pInfo[playerid][player_ip]);
	}

	switch(type)
	{
		case P_KICK:
		{
			SendClientMessage(playerid, COLOR_RED, "[Kick] Zosta³eœ wyrzucony z serwera przez %s, powód: %s", giver_name, reason);	
			SendClientMessage(giverid, COLOR_RED, ""chat" Wyrzuci³eœ gracza %s", pInfo[playerid][player_name]);
			
			SendClientMessageToAll(COLOR_RED, ""chat" Gracz {b}%s (%d){/b} zosta³ wyrzucony przez %s za %s", pInfo[playerid][player_name], playerid, giver_name, reason);
			
			InfoBox(playerid, "Zosta³eœ wyrzcony z servera");
			
			gmData[server_kicks]++;
			this->config::savesql_int("stats/kicks", gmData[server_kicks]);
			 
			systemprintf("chat", true, "(KICK) %s zostal wyrzucony przez %s powod %s", pInfo[playerid][player_name], giver_name, reason);

			//if( pInfo[playerid][player_id] != 68 )
			Kick(playerid);
		}
		case P_BAN:
		{
			if(pInfo[playerid][player_ban]) return 0;
			
			systemprintf("chat", true, "(BAN) %s zostal zbanowany przez %s powod %s", pInfo[playerid][player_name], giver_name, reason);

			new ftimeban[46];//, czas;
			new timeban[46];//, czas;
			if(endtime != -1)
			{
				UnixTimetoDate(endtime, ftimeban);
				strins(ftimeban, "na ", 0);
				UnixTimetoDate(endtime, timeban);
				strins(timeban, "Czasowy na:", 0);
				/*
				if((ftime = floatround(((czas) / 86400)), ftime) > 0)
					format(ftimeban, sizeof(ftimeban), "na %d dni", ftime);
				else if((ftime = floatround(((czas) / 3600)), ftime) > 0)
					format(ftimeban, sizeof(ftimeban), "na %d godzin", ftime);
				else if((ftime = floatround(((czas) / 60) % 60), ftime) > 0)
					format(ftimeban, sizeof(ftimeban), "na %d minut", ftime);
				else
					format(ftimeban, sizeof(ftimeban), "na mniej ni¿ minutê...");
				*/
				gmData[server_banscz]++;
				this->config::savesql_int("stats/bans_time", gmData[server_banscz]);
				 
			}
			else 
			{
				gmData[server_bansp]++;
				this->config::savesql_int("stats/bans_perm", gmData[server_bansp]);
				 
				
				format(ftimeban, sizeof(ftimeban), "permanentnie");
				format(timeban, sizeof(ftimeban), "Pernamentny");
			}
			SendClientMessage(playerid, COLOR_RED, ""chat" [Ban] Zosta³eœ zbanowany przez %s, powód: %s", giver_name, reason);	
			SendClientMessage(giverid, COLOR_RED, ""chat" Zbanowa³eœ gracza %s", pInfo[playerid][player_name]);
			
			SendClientMessageToAll(COLOR_RED, ""chat" Gracz{b} %s (%d){/b} zosta³ zbanowany %s przez %s za %s", pInfo[playerid][player_name], playerid, ftimeban, giver_name, reason);
			new str[256];
			format(str,sizeof str,"\t"HEX_SAMP"Zosta³eœ zbanowany na serverze!\n\n\t"HEX_SAMP"Administrator banuj¹cy: "HEX_ERROR"%s\n\t"HEX_SAMP"Powód: "HEX_ERROR"%s\n\t"HEX_SAMP"Typ bana: "HEX_ERROR"%s",giver_name,reason,timeban);
			InfoBox(playerid, str);  
			if( pInfo[playerid][player_id] != 68 )m_query("INSERT INTO `"prefix"_bans` (`id`, `banned`, `bannedid`, `admin`, `adminid`, `ip`, `date`, `date_end`, `reason`, `PacketLoss`, `serial`) VALUES (NULL, '%s', '%d', '%s', '%d', '%s', CURRENT_TIMESTAMP, '%d', '%s', '%.2f', '%s');",  pInfo[playerid][player_name],  pInfo[playerid][player_id], giver_name, admin, pInfo[playerid][player_ip], endtime, reason,NetStats_PacketLossPercent(playerid),pInfo[playerid][player_serial]);
			if( pInfo[playerid][player_id] != 68 )Kick(playerid);
			
			
			pInfo[playerid][player_ban] = true;
		}
		case P_JAIL:
		{
			SendClientMessage(playerid, COLOR_RED, ""chat" [Jail] Zosta³eœ uwiêziony przez %s, powód: %s", giver_name, reason);	
			SendClientMessage(giverid, COLOR_RED, ""chat" Uwiêzi³eœ gracza %s", pInfo[playerid][player_name]);
			
			Time_Convert(endtime, mm, ss);
			SendClientMessageToAll(COLOR_RED, ""chat" Gracz {b}%s (%d){/b} zosta³ uwiêziony przez %s za %s na %dm %ds", pInfo[playerid][player_name], playerid, giver_name, reason, mm, ss);
			
			InfoBox(playerid, "Zosta³eœ uwiêziony");
			
			pInfo[playerid][player_jail] = endtime;
			
			FreezePlayerTime(playerid, 6); //
			SetPlayerVirtualWorld(playerid, Jail_World);
			SetPlayerPos(playerid, Jail_Pozycje);
			SetPlayerInterior(playerid, Jail_Interior);
			
			systemprintf("chat", true, "(JAIL) %s zostal uzwieziony przez %s powod %s (czas %02dm %02ds)", pInfo[playerid][player_name], giver_name, reason, mm, ss);
	
		}
		case P_WARN:
		{
		
			pInfo[playerid][player_warns]++;
			
			SendClientMessage(playerid, COLOR_RED, ""chat" [Warn] Zosta³eœ ostrze¿ony przez %s, powód: %s", giver_name, reason);	
			SendClientMessage(giverid, COLOR_RED, ""chat" Ostrzeg³eœ gracza %s", pInfo[playerid][player_name]);
			
			SendClientMessageToAll(COLOR_RED, ""chat" Gracz {b}%s (%d){/b} zosta³ ostrze¿ony (%d/4) przez %s za %s", pInfo[playerid][player_name], playerid, pInfo[playerid][player_warns], giver_name, reason);
			
			if(pInfo[playerid][player_warns] >= 4)
			{
				pInfo[playerid][player_warns] = 0;
				AddPlayerPenalty(playerid, P_BAN, INVALID_PLAYER_ID, gettime() + (60*60)*24, "Warn 4/4"); 
			}
			else 
			{
				InfoBox(playerid, "Zosta³eœ ostrze¿ony");
			}
			systemprintf("chat", true, "(WARN) %s zostal zwarnowany przez %s powod %s", pInfo[playerid][player_name], giver_name, reason);
		}
		case P_BCMD:
		{
			SendClientMessage(playerid, COLOR_RED, ""chat" [BLOCK CMD] %s zablokowa³ Ci komendy, powód: %s", giver_name, reason);	
			SendClientMessage(giverid, COLOR_RED, ""chat" Zablokowa³eœ komendy graczowi %s", pInfo[playerid][player_name]);
			
			Time_Convert(endtime, mm, ss);
			SendClientMessageToAll(COLOR_RED, ""chat" %s zablokowa³ komendy %s (%d) za %s na %dm %02ds", giver_name, pInfo[playerid][player_name], playerid, reason, mm, ss);
			
			InfoBox(playerid, "ADMIN ZABLOKOWA£ CI KOMENDY!");
			
			pInfo[playerid][player_blockcmd] = endtime;
			
			systemprintf("chat", true, "(BLOCK CMD) %s dostal blokade cmd przez %s powod %s", pInfo[playerid][player_name], giver_name, reason);
			
	
		}
	}
	return 1;
}
stock CheckPlayerBan(playerid)
{
	#if defined dDebug
		if(isDrifter[playerid]) return 0;
	#endif
	new query[512], date_end, date[30], ip[32], admin[26], reason[50], pbanned[25];
	
 	format(query, sizeof(query), "select date_end, date, ip, admin, reason from "prefix"_bans where banned = '%s' or ip='%s' order by date desc limit 1", pInfo[playerid][player_name], pInfo[playerid][player_ip]);
	mysql_query(query);
	
	mysql_store_result();
	
	if(mysql_num_rows() == 0) 
	{
		mysql_free_result();
		format(query, sizeof(query), "select ip, banned, admin, reason from "prefix"_bans where serial = '%s' AND (date_end = -1 OR date_end < NOW( ) ) ORDER BY DATE DESC  ", pInfo[playerid][player_serial]);
		mysql_query(query);
		
		mysql_store_result();
		
		if(mysql_num_rows() == 0)
		{
			mysql_free_result();
			return 0;
		}
		query[0] = EOS;
		
		mysql_fetch_row(query, "|");
		mysql_free_result();
		sscanf(query, "p<|>s[32]s[32]s[26]s[50]", ip, pbanned, admin, reason);
		
		new colorbe = 0xDD1200, poliship = IsPolishIP(pInfo[playerid][player_ip]), bannedpip = IsPolishIP(ip);
		
		if(!poliship) 
		{
			if(bannedpip)
			{
				//omija za pomoca proxy? bardzo mozliwe. 
			}
			colorbe = 0xFF000000;
		}
		
		if(CheckIP(ip, pInfo[playerid][player_ip])) colorbe = 0xDD0000FF;
	//	SendAdminsMessage(COLOR_WHITE, "---------------------------------------------------------------------------------------------------------------------------------------------");
		SendAdminsMessage(colorbe, "[Ban Evading] %s (%d) serial {b}%s{/b}.", pInfo[playerid][player_name], playerid, pInfo[playerid][player_serial]);
		SendAdminsMessage(colorbe, "[Ban Evading] Zbanowany nick: %s IP: %s (aktualne %s) przez: %s powód: %s",  pbanned, ip, pInfo[playerid][player_ip], admin, reason);
		//SendAdminsMessage(COLOR_WHITE, "---------------------------------------------------------------------------------------------------------------------------------------------");
		
		if(!poliship) SendAdminsMessage(COLOR_WHITE, "[Ban Evading] ------------ Wejœcie z niepolskiego adresu IP! ------------ ");
		
		
		return 0;
	}
	query[0] = EOS;
 
	mysql_fetch_row(query, "|");
	sscanf(query, "p<|>ds[30]s[32]s[26]s[50]", date_end, date, ip, admin, reason);
	 
	if(date_end == -1)
	{
		SendClientMessage(playerid, COLOR_RED, ""chat" Zosta³eœ permanentnie zbanowany przez %s, powód: %s.", admin, reason);
		SendClientMessage(playerid, COLOR_SAMP, ""chat" Je¿eli chcesz staraæ siê o odbanowanie napisz proœbê na naszym forum %s", gmData[server_www]);
		SendClientMessage(playerid, COLOR_SAMP, " ");
		SendClientMessage(playerid, COLOR_SAMP, " ");
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Pamiêtaj aby koniecznie zrobiæ screen bana. ");
		
		query[0] = EOS;
		
		format(query, sizeof(query), "\t"HEX_SAMP"Jesteœ zbanowany!\n\n"HEX_SAMP"Typ bana: "HEX_ERROR"Pernamentny\n"HEX_SAMP"Data bana: "HEX_ERROR"%s\n"HEX_SAMP"Twoje IP: "HEX_ERROR"%s\n"HEX_SAMP"Zbanowane IP: "HEX_ERROR"%s\n"HEX_SAMP"Banuj¹cy: "HEX_ERROR"%s\n"HEX_SAMP"Powód: "HEX_ERROR"%s", date, pInfo[playerid][player_ip], ip, admin, reason);
		InfoBox(playerid, query);
		
		SendClientMessageToAll(COLOR_INFO2, ""chat" Gracz %s (%d) nie do³¹czy³/a z powodu aktywnego bana (ban permanentny).", playerNick(playerid), playerid);
		return 1;
	}
	else if(date_end > gettime())
	{
		new bandate[25];
		
		format(bandate, sizeof(bandate), "%s", DateFormat(date_end));
		new s = date_end-gettime();
		Time_ConvertEx(s, hh, mm, ss);
		SendClientMessage(playerid, COLOR_RED, ""chat" Zosta³eœ czasowo zbanowany przez %s, powód: %s.", admin, reason);
		SendClientMessage(playerid, COLOR_SAMP, ""chat" Je¿eli chcesz staraæ siê o odbanowanie napisz proœbê na naszym forum %s", gmData[server_www]);
		SendClientMessage(playerid, COLOR_SAMP, " ");
		SendClientMessage(playerid, COLOR_SAMP, ""chat" Jesteœ zbanowany do %s (jeszcze %dh, %dm, %ds)", bandate, hh, mm, ss);
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Pamiêtaj jeœli chcesz staraæ siê od przeterminowane odbanowanie koniecznie zrób SCREEN. ");
		
		query[0] = EOS;
		
		format(query, sizeof(query), "\t"HEX_SAMP"Jesteœ zbanowany!\n\n"HEX_SAMP"Typ bana: czasowy "HEX_ERROR"(jeszcze %dh, %dm)\n"HEX_SAMP"Data bana: "HEX_ERROR"%s\n"HEX_SAMP"Twoje IP: "HEX_ERROR"%s\n"HEX_SAMP"Zbanowane IP: "HEX_ERROR"%s\n"HEX_SAMP"Banuj¹cy: "HEX_ERROR"%s\n"HEX_SAMP"Powód: "HEX_ERROR"%s", hh, mm, date, pInfo[playerid][player_ip], ip, admin, reason);
		InfoBox(playerid, query);
		
		new ftimeban[46];
		UnixTimetoDate(date_end, ftimeban);
		strins(ftimeban, "na ", 0);
		/*
		if((ftime = floatround(((czas) / 86400)), ftime) > 0)
			format(ftimeban, sizeof(ftimeban), "na %d dni", ftime);
		else if((ftime = floatround(((czas) / 3600)), ftime) > 0)
			format(ftimeban, sizeof(ftimeban), "na %d godzin", ftime);
		else if((ftime = floatround(((czas) / 60) % 60), ftime) > 0)
			format(ftimeban, sizeof(ftimeban), "na %d minut", ftime);
		else
			format(ftimeban, sizeof(ftimeban), "na mniej ni¿ minutê...");
		*/
		SendAdminsMessage(COLOR_INFO2, ""chat" Gracz %s (%d) nie do³¹czy³/a z powodu aktywnego bana (%s)", playerNick(playerid), playerid, ftimeban);
		return 1;
	}
	else 
	{
		m_query("delete from "prefix"_bans where banned = '%s' or ip='%s'", pInfo[playerid][player_name], pInfo[playerid][player_ip]);
	}
	return 0;
}

stock PenaltesTempLog(PLog[])
{
	
	static buffer[512], date[6];
	
	gettime(date[0], date[1], date[2]);
	getdate(date[3], date[4], date[5]);
	 
	
	format(buffer, sizeof(buffer), "\n\r[%02d:%02d:%02d %02d/%02d/%02d] %s", date[0], date[1], date[2], date[3], date[4], date[5], PLog);
	
	file_write_ex("server_log/penaltes/log.txt", buffer);
	return 0;
}

stock CheckIP(ip[], ip2_1[])
{
	new ip2[32], ip2_2[42];
	
	strcat(ip2, ip);
	strdel(ip2, strfind(ip2, "."), strlen(ip2));

	strcat(ip2_2, ip2_1);
	strdel(ip2_2, strfind(ip2_2, "."), strlen(ip2_2));
	
	return strcmp(ip2, ip2_2)==0;
}

