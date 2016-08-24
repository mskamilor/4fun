/*
PlayerData 1.0
(c) Copyright 2013-2014 by mrdrifter, Game

@author    : mrdrifter (http://4fun-serv.pl/__drifter__/), Game
@date      : 16 listopada 2013
@update    : 12 stycznia 2014

*/

stock CheckPlayerData(playerid, bool:isreg = false)
{
	new isacc=0;
	static query[1124 + MAX_ACHIEVEMENT + 256 + 32], hhud[32], ipreg[32];
	new bool:sendjoininfo = isreg;
	query[0] = EOS;
	query = "select id,mailstatus,acc,warn,score,skill,upass,mute,timeplay,launcher,hitman,skin,lot,show_rank,jail,bank,level,cash,admin,portfel,kills,deaths,suicides,gang,gang_ranga,nickchange,car_color1,car_color2,car_date,car_paintjob,car_model,wg,ch,hy,ws,dd,ctf,zb,tr,df,os,onede,onede2,dm1,dm2,dm3,sawn,minigun,snajper,arenagang,result_matematyk,result_codes, result_scrable, duel_win, duel_lost, tir_count,walizki,prezenty,figurki,zauta,skupcount";
	new posveh[128];
	format(query, sizeof(query), "%s,messages,house,mandats,mandatcash,largest_drift,achievements_count,vip,timecodes,timematematyk,timescrable,car_przebieg, tir_km, date_last, ip_last, achievements, password, apassword, ucode, mail, car_pos, car_components, ip_register, hide_hud, wybrany_spawn, nasionka, marihuana, posadzonych_krzakow, zebranych_krzakow, spalonego_skuna, cut_tree from "prefix"_players where nick = '%s' order by score limit 1", query, pInfo[playerid][player_name]);
	mysql_query(query);
	
	mysql_store_result();
	
	if(mysql_num_rows() == 0)return 0;
	query[0] = EOS;
	string2[0] = EOS;
	
	mysql_fetch_row(query, "|");
	mysql_free_result();
	
	if(sscanf(query, "p<|>ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddfffffs[24]s[24]s[260]s[50]s[50]s[24]s[42]s[128]s[46]s[32]s[32]ddddddd",
	pInfo[playerid][player_id],
	pInfo[playerid][player_mailstatus],
	isacc,
	pInfo[playerid][player_warns],
	pInfo[playerid][player_score],
	pInfo[playerid][player_skill],
	pInfo[playerid][player_chpassword],
	pInfo[playerid][player_mute],
	pInfo[playerid][player_timeplay],
	pInfo[playerid][player_launcher],
	pInfo[playerid][player_bounty],
	pInfo[playerid][player_loadskin],
	pInfo[playerid][player_lot],
	pInfo[playerid][player_userank],
	pInfo[playerid][player_jail],
	pInfo[playerid][player_bank],
	pInfo[playerid][player_level],
	pInfo[playerid][player_cash],
	pInfo[playerid][player_admin_login],
	pInfo[playerid][player_portfel],
	pInfo[playerid][player_kills],
	pInfo[playerid][player_deaths],
	pInfo[playerid][player_suicide],
	pInfo[playerid][player_gangID],
	pInfo[playerid][player_gangrank],
	pInfo[playerid][player_nichchange],
	//
	pInfo[playerid][player_car_color][0],
	pInfo[playerid][player_car_color][1],
	pInfo[playerid][player_car_date],
	pInfo[playerid][player_car_paintjob],
	pInfo[playerid][player_car_model],
	//
	pInfo[playerid][player_eventpoints][stats_wg],
	pInfo[playerid][player_eventpoints][stats_ch],
	pInfo[playerid][player_eventpoints][stats_hy],
	pInfo[playerid][player_eventpoints][stats_ws],
	pInfo[playerid][player_eventpoints][stats_dd],
	pInfo[playerid][player_eventpoints][stats_ctf],
	pInfo[playerid][player_eventpoints][stats_zb],
	pInfo[playerid][player_eventpoints][stats_tr],
	pInfo[playerid][player_eventpoints][stats_df],
	pInfo[playerid][player_eventpoints][stats_os],
	pInfo[playerid][player_eventpoints][stats_onede],
	pInfo[playerid][player_eventpoints][stats_onede2],
	pInfo[playerid][player_eventpoints][stats_dm1],
	pInfo[playerid][player_eventpoints][stats_dm2],
	pInfo[playerid][player_eventpoints][stats_dm3],
	pInfo[playerid][player_eventpoints][stats_sawn],
	pInfo[playerid][player_eventpoints][stats_minigun],
	pInfo[playerid][player_eventpoints][stats_snajper],
	pInfo[playerid][player_eventpoints][stats_arenagang],
	pInfo[playerid][player_eventpoints][stats_matematyk],
	pInfo[playerid][player_eventpoints][stats_codes],
	pInfo[playerid][player_eventpoints][stats_scrable],
	pInfo[playerid][player_eventpoints][stats_duel_win],
	pInfo[playerid][player_eventpoints][stats_duel_lost],
	pInfo[playerid][player_eventpoints][stats_tir],
	pInfo[playerid][player_eventpoints][stats_walizki],
	pInfo[playerid][player_eventpoints][stats_prezenty],
	pInfo[playerid][player_eventpoints][stats_figurki],
	pInfo[playerid][player_eventpoints][stats_zauta],
	pInfo[playerid][player_eventpoints][stats_skupcount],
	 
	pInfo[playerid][player_messages],
	pInfo[playerid][player_house],
	pInfo[playerid][player_mandats],
	pInfo[playerid][player_mandatcash],
	pInfo[playerid][player_largest_drift],
	pInfo[playerid][player_achievements_count],
	pInfo[playerid][player_vip],
	pInfo[playerid][player_gamecodes],
	pInfo[playerid][player_gamematematyk],
	pInfo[playerid][player_gamescrable],
	pInfo[playerid][player_car_przebieg],
	pInfo[playerid][player_stats_tirkm],
	pInfo[playerid][player_lastlogin],
	pInfo[playerid][player_lastip],
	string2,
	pInfo[playerid][player_password],
	pInfo[playerid][player_apassword],
	pInfo[playerid][player_ucode],
	pInfo[playerid][player_email],
	posveh,
	pInfo[playerid][player_car_component], ipreg, hhud,
	pInfo[playerid][wybrany_spawn],
	pInfo[playerid][player_nasionka],
	pInfo[playerid][player_marihuana],
	pInfo[playerid][posadzonych_krzakow],
	pInfo[playerid][zebranych_krzakow],
	pInfo[playerid][spalonego_skuna],
	pInfo[playerid][cut_tree]))
	printf("[Login] B£¥D: SSCANF %s", query);
	
	sscanf(pInfo[playerid][player_car_component], "p<,>a<d>[15]", pInfo[playerid][player_car_component]);
	sscanf(posveh, "p<,>a<f>[5]", pInfo[playerid][player_car_pos]);
	sscanf(string2, "p<,>a<d>[128]", pInfo[playerid][player_achievements]);
	sscanf(hhud, "p<,>a<d>[7]", pInfo[playerid][player_hidehud]);
	
	GivePlayerMoney(playerid, 5000);
	GivePlayerScore(playerid, 1);
	
	pInfo[playerid][player_register] = true;
	pInfo[playerid][player_logged] = false;
	
	pInfo[playerid][player_next_level] = RespectToLevel(pInfo[playerid][player_level]+1);
	
	if(pInfo[playerid][player_cash] < 0) pInfo[playerid][player_cash] = 5000;
	if(!strcmp(ipreg, "127.0.0.1", true)) m_query("update "prefix"_players set ip_register = '%s' where id=%d", pInfo[playerid][player_ip], pInfo[playerid][player_id]);
	if(GangPlayer(playerid))
	{
		if(gInfo[pInfo[playerid][player_gang]][gangColor] != 0)
			pInfo[playerid][player_color] = gInfo[pInfo[playerid][player_gang]][gangColor];
		SetPlayerColorEx(playerid);
		
		if(!sendjoininfo)
		{
			sendjoininfo = true;
			new gr[][] = {"Cz³onek", "Cz³onek", "Zastêpca szefa", "Szef"};
			
			SendClientMessageToAll(gInfo[pInfo[playerid][player_gang]][gangColor],""chat" %s (%d) {b}%s{/b} gangu %s do³¹czy³ do gry!", playerNick(playerid), playerid, gr[pInfo[playerid][player_gangrank]], gInfo[pInfo[playerid][player_gang]][gangNazwa]);
		}
		
	}
	
	if(pInfo[playerid][player_vip] > gettime() || /*vip perm*/ pInfo[playerid][player_vip] == -1)
	{
		pInfo[playerid][player_color] = COLOR_VIP;
		SetPlayerColorEx(playerid);
		Iter_Add(Vips, playerid);
		
		if(!sendjoininfo) SendClientMessageToAll(COLOR_VIP, ""chat" Vip %s (%d) do³¹cza do Gry :)", pInfo[playerid][player_name], playerid);
		sendjoininfo = true;
	}
	
	
	if(!sendjoininfo) SendClientMessageToAll(0xC0C0C0FF, ""chat" Gracz %s (%d) do³¹cza na serwer!", pInfo[playerid][player_name], playerid);
	
	/*
	new info[512];
	format(info, sizeof(info), "Witaj %s, \n\n"HEX_TAN"Zosta³eœ zalogowany pomyœlnie."HEX_SAMP"\nOstatnim razem logowa³eœ siê "HEX_LIGHT_GOLDENROD_4" %s"HEX_SAMP".\n\n\n", pInfo[playerid][player_name], pInfo[playerid][player_lastlogin]);
	
	if(strcmp(pInfo[playerid][player_lastip], pInfo[playerid][player_ip], true))
	{
		format(info, sizeof(info), "%s"HEX_ERROR"Uwaga: "HEX_DARK_RED"Ostatnim razem logowa³eœ siê z innym adresem IP", info);
	}
	*/
	
	if(isacc)
	{
		/*if(!CallRemoteFunction("AC_IsPlayerUsingAc", "d", playerid))
		{
			AddPlayerPenalty(playerid, P_KICK, INVALID_PLAYER_ID, 0, "brak anti cheata"); 
		}*/
		pInfo[playerid][player_ac] = true;

		 
	}
	House_OnPlayerLoad(playerid);
 	UpdatePlayerNick(playerid);
	return 1;
}


stock SendScore(given, user, score, const reason2[])
{
	if(score == 0) 
	{
		SendClientMessage(given, COLOR_ERROR, "» Nie mo¿na przelaæ 0"); //wygenerowany
		return 1;
	}
	if(!IsPlayerConnected(user))
	{
		SendClientMessage(given, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!"); //wygenerowany
		return 1;
	}
	if(!pInfo[user][player_logged])
	{
		SendClientMessage(given, COLOR_ERROR, "» Podany gracz nie jest zalogowany(a) nie mo¿esz mu wys³aæ respektu.");
		return 1;
	}
	if(!pInfo[user][player_register])
	{
		SendClientMessage(given, COLOR_ERROR, "» Podany gracz nie jest zarejestrowany(a) nie mo¿esz mu wys³aæ respektu.");
		return 1;
	}
	if(user == given)
	{
		SendClientMessage(given, COLOR_ERROR, "» Nie mo¿esz wys³aæ sobie respektu.");
		return 1;
	}
	if(GetPlayerScore(given) < score)
	{
		SendClientMessage(given, COLOR_ERROR, "» Nie masz tyle punktów respektu.");
		return 1;
	}
	if(score < 0)
	{
		SendClientMessage(given, COLOR_ERROR, "» Musisz wys³aæ minimum 1 punkt respektu.");
		return 1;
	}
	new reason[68];
	mysql_real_escape_string(reason2, reason);
	
	format(string2, sizeof(string2), "to: %d, score: %d, nick: %s", pInfo[user][player_id], score, pInfo[user][player_name]);
	AddPlayerLog(given, LOG_SENDSCORE, string2, reason);
	
	GivePlayerScore(given, (-score));
	GivePlayerScore(user, (score));
	
	SavePlayer(given);
	if(score > 500)
		SavePlayer(user);
	
	SendClientMessage(given, COLOR_GOLD, ""chat" Wys³a³eœ %d respektu graczowi %s (%d).", score, playerNick(user), user);
	SendClientMessage(user, COLOR_GOLD, ""chat" Otrzyma³eœ %d respektu od gracza %s (%d).", score, playerNick(given), given);
	//InfoBox(user, "Otrzyma³eœ respekt!");
	return 1;
}
stock SendCash(given, user, cash, bool:gui = false)
{
	//if(cash < 1000) return 0;
	
	if(!IsPlayerConnected(user))
	{
		SendClientMessage(given, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony - przelewanie pieniêdzy nie powid³o siê!"); //wygenerowany
		
		if(gui) DialogFunc:DIALOG_PLAYER(given, 1, 1, "EOS");
		return 1;
	}
	
	if(!pInfo[user][player_register])
	{
		SendClientMessage(given, COLOR_ERROR, "» Podany gracz nie jest zarejestrowany(a) nie mo¿esz mi wys³aæ pieniêdzy.");
		
		if(gui) DialogFunc:DIALOG_PLAYER(given, 1, 1, "EOS");
		return 1;
	}
	if(user == given)
	{
		SendClientMessage(given, COLOR_ERROR, "» Nie mo¿esz wys³aæ sobie pieniêdzy.");
		
		if(gui) DialogFunc:DIALOG_PLAYER(given, 1, 1, "EOS");
		return 1;
	}
	if(GetPlayerMoney(given) < cash)
	{
		SendClientMessage(given, COLOR_ERROR, "» Nie masz tyle pieniêdzy.");
		
		if(gui) DialogFunc:DIALOG_PLAYER(given, 1, 1, "EOS");
		return 1;
	}
	if(cash < 10000)
	{
		SendClientMessage(given, COLOR_ERROR, "» Zbyt ma³o pieniêdzy.");
		
		if(gui) DialogFunc:DIALOG_PLAYER(given, 1, 1, "EOS");
		return 1;
	}
	GivePlayerMoney(given, (-cash));
	GivePlayerMoney(user, (cash));
	
	SendClientMessage(given, COLOR_GOLD, ""chat" Wys³a³eœ %d pieniêdzgraczowizu %s (%d).", cash, playerNick(user), user);
	SendClientMessage(user, COLOR_GOLD, ""chat" Otrzyma³eœ %d pieniêdzy od gracza %s (%d).", cash, playerNick(given), given);
	//InfoBox(user, "Otrzyma³eœ pieni¹dze!");
	
	if(gui) OnPlayerClickPlayer(given, pInfo[given][player_clickedplayer], 0);
	return 1;
}
stock SavePlayer(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		if(pInfo[playerid][player_logged])
		{
			string2[0] = EOS;
			
			for(new i; i<MAX_ACHIEVEMENT;i++)
			{
				if(i > 0)
					format(string2, sizeof(string2), "%s,%d", string2, pInfo[playerid][player_achievements][i]);
				else
					format(string2, sizeof(string2), "%d", pInfo[playerid][player_achievements][i]);
			}
			
			new hhud[32];
			for(new i; i<7;i++)
			{
				if(i > 0)
					format(hhud, sizeof(hhud), "%s,%d", hhud, pInfo[playerid][player_hidehud][ hide_huds:i ]);
				else
					format(hhud, sizeof(hhud), "%d", pInfo[playerid][player_hidehud][hide_huds:i]);
			}
			
			new car_components[36];
			for(new i;i<14;i++)
			{
				format(car_components, sizeof(car_components), "%s%s%d", car_components, i == 0 ? (""):(","), GetVehicleComponentInSlot(gmData[player_vehicleid][playerid], i));
			}
			
			static query[1500 + (MAX_ACHIEVEMENT*2) + 300];
			
			query[0] = EOS;
			format(query, sizeof(query), "update "prefix"_players set score=%d,warn=%d,lot=%d,show_rank=%d,nickchange=%d,mute=%d,hitman=%d,jail=%d,bank=%d,level=%d,cash=%d,portfel=%d,kills=%d,deaths=%d, suicides=%d, gang=%d, gang_ranga=%d, wg=%d, ch=%d, hy=%d, ws=%d,dd=%d,ctf=%d, zb=%d,tr=%d,os=%d,onede=%d,onede2=%d,dm1=%d,dm2=%d,dm3=%d, sawn=%d, minigun=%d, snajper=%d,arenagang=%d,result_matematyk=%d,result_codes=%d,result_scrable=%d,duel_win=%d,duel_lost=%d,tir_count=%d,tir_km='%.2f',messages=%d,walizki=%d,prezenty=%d,figurki=%d,zauta=%d,",
			pInfo[playerid][player_score],pInfo[playerid][player_warns], pInfo[playerid][player_lot], pInfo[playerid][player_userank], pInfo[playerid][player_nichchange], pInfo[playerid][player_mute], pInfo[playerid][player_bounty], pInfo[playerid][player_jail], pInfo[playerid][player_bank], pInfo[playerid][player_level], pInfo[playerid][player_cash], pInfo[playerid][player_portfel], pInfo[playerid][player_kills], pInfo[playerid][player_deaths], pInfo[playerid][player_suicide], pInfo[playerid][player_gangID],
			pInfo[playerid][player_gangrank], pInfo[playerid][player_eventpoints][stats_wg], pInfo[playerid][player_eventpoints][stats_ch], pInfo[playerid][player_eventpoints][stats_hy], pInfo[playerid][player_eventpoints][stats_ws],
			pInfo[playerid][player_eventpoints][stats_dd], pInfo[playerid][player_eventpoints][stats_ctf], pInfo[playerid][player_eventpoints][stats_zb], pInfo[playerid][player_eventpoints][stats_tr], pInfo[playerid][player_eventpoints][stats_os],pInfo[playerid][player_eventpoints][stats_onede],pInfo[playerid][player_eventpoints][stats_onede2], pInfo[playerid][player_eventpoints][stats_dm1],pInfo[playerid][player_eventpoints][stats_dm2],pInfo[playerid][player_eventpoints][stats_dm3],	pInfo[playerid][player_eventpoints][stats_sawn],
			pInfo[playerid][player_eventpoints][stats_minigun], pInfo[playerid][player_eventpoints][stats_snajper], pInfo[playerid][player_eventpoints][stats_arenagang], pInfo[playerid][player_eventpoints][stats_matematyk], pInfo[playerid][player_eventpoints][stats_codes],
			pInfo[playerid][player_eventpoints][stats_scrable], pInfo[playerid][player_eventpoints][stats_duel_win], pInfo[playerid][player_eventpoints][stats_duel_lost], pInfo[playerid][player_eventpoints][stats_tir], pInfo[playerid][player_stats_tirkm], pInfo[playerid][player_messages], 	pInfo[playerid][player_eventpoints][stats_walizki], pInfo[playerid][player_eventpoints][stats_prezenty], pInfo[playerid][player_eventpoints][stats_figurki], pInfo[playerid][player_eventpoints][stats_zauta]);
			
			format(query, sizeof(query), "%smandats=%d,mandatcash=%d,df=%d,house=%d,", query,
			pInfo[playerid][player_mandats], pInfo[playerid][player_mandatcash],pInfo[playerid][player_eventpoints][stats_df], pInfo[playerid][player_house]);
			
			format(query, sizeof(query), "%s timeplay=%d,skupcount=%d,skill=%d,largest_drift=%d,achievements_count=%d,timecodes='%.2f',timematematyk='%.2f',timescrable='%.2f',skin=%d,ip_last='%s',date_last=now(),car_pos = '%f, %f, %f, %f', car_model=%d, car_color1=%d, \
			car_color2=%d, car_components='%s', car_date=%d, car_przebieg='%f', car_paintjob=%d, achievements='%s', hide_hud='%s', wybrany_spawn=%d, nasionka=%d, marihuana=%d, posadzonych_krzakow=%d, zebranych_krzakow=%d, spalonego_skuna=%d, cut_tree=%d where id=%d limit 1",
			query,
			pInfo[playerid][player_timeplay],pInfo[playerid][player_eventpoints][stats_skupcount],pInfo[playerid][player_skill],pInfo[playerid][player_largest_drift],pInfo[playerid][player_achievements_count],pInfo[playerid][player_gamecodes],pInfo[playerid][player_gamematematyk], pInfo[playerid][player_gamescrable],pInfo[playerid][player_skin], pInfo[playerid][player_ip], pInfo[playerid][player_car_pos][0], pInfo[playerid][player_car_pos][1], pInfo[playerid][player_car_pos][2], pInfo[playerid][player_car_pos][3], pInfo[playerid][player_car_model],
			pInfo[playerid][player_car_color][0], pInfo[playerid][player_car_color][1],
			car_components, pInfo[playerid][player_car_date], pInfo[playerid][player_car_przebieg], pInfo[playerid][player_car_paintjob],
			string2, hhud, pInfo[playerid][wybrany_spawn],pInfo[playerid][player_nasionka],pInfo[playerid][player_marihuana], pInfo[playerid][posadzonych_krzakow], pInfo[playerid][zebranych_krzakow],pInfo[playerid][spalonego_skuna],pInfo[playerid][cut_tree],pInfo[playerid][player_id]);
			
			mysql_query(query);
		}
	}
}
CMD:ranga(playerid, params[])
{
	UpdatePlayerNick(playerid, true);
	DialogRanga(playerid);
	return 1;
}
stock DialogRanga(p)
{
	Dialog_Show(p, DIALOG_RANGA, DIALOG_STYLE_LIST, "• Ustawianie rangi przy nicku •", "» Brak Rangi\n» Tag Gangu\n» Ranga na serwerze (Admin, Vip, Mod)\n» Sta³y Gracz\n» Drifter\n» $ponsor\n» Fan /OneDe\n» Pilot\n» Snajper\n» Rolnik\n» Dziewffczynka\n» Farmer Ganji\n» Zjaraniec\n» GanjaMaster\n» Chory cz³owiek\n» Podró¿nik\n» Drwal\n» Newbie\n» Spammer\n» Desperat\n» Expert\n» Unstoppable", "Wybierz", "Zamknij");
}
Dialog:DIALOG_RANGA(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				pInfo[playerid][player_userank] = 0;
			}
			
			case 1:
			{
				if(!GangPlayer(playerid))
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz byæ w Gangu!");
					DialogRanga(playerid);
					return 1;
				}
				pInfo[playerid][player_userank] = 1;
			}
			case 2:
			{
				pInfo[playerid][player_userank] = 2;
			}
			case 3:
			{
				if(!pInfo[playerid][player_tag])
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz mieæ w nicku Tag servera! (%s)!", gmData[server_tag]);
					DialogRanga(playerid);
					return 1;
				}
				pInfo[playerid][player_userank] = 3;
			}
			case 4:
			{
				if(!pInfo[playerid][player_achievements][21])
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz zdobyæ osi¹gniêcie Drifter aby ustawiæ t¹ rangê. Wiêcej info {b}/ach 21{/b}!");
					DialogRanga(playerid);
					return 1;
				}
				pInfo[playerid][player_userank] = 4;
			}
			case 5:
			{
				if(pInfo[playerid][player_portfel] < 20)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz mieæ 20z³ w portfelu ({b}/Portfel{/b}) aby ustawiæ t¹ rangê!");
					DialogRanga(playerid);
					return 1;
				}
				pInfo[playerid][player_userank] = 5;
			}
			case 6:
			{
				if(pInfo[playerid][player_eventpoints][stats_onede] < 100)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz mieæ 100 zabiæ !");
					DialogRanga(playerid);
					return 1;
				}
				pInfo[playerid][player_userank] = 6;
			}
			case 7:
			{
				if(pInfo[playerid][player_lot] < 3600)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz przelecieæ samolotem godzine! brakuje Ci %02d minut!", (3600 - pInfo[playerid][player_lot])/60);
					DialogRanga(playerid);
					return 1;
				}
				pInfo[playerid][player_userank] = 7;
			}
			
			case 8: 
			{
				if(pInfo[playerid][player_achievements][29] < 250)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz zabiæ 250 osób z broni Sniper. Aktualnie zabi³eœ {b}%d/250{/b}.", pInfo[playerid][player_achievements][29]);
					DialogRanga(playerid);
					return 1;
				}
				pInfo[playerid][player_userank] = 8;
			}
			case 9,10: {pInfo[playerid][player_userank] = listitem; }
			case 11: {//Farmer
				if(pInfo[playerid][posadzonych_krzakow] < 100)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz posiadaæ 100 posadzonych krzaków marihuany (/ziolohelp) aby ustawiæ t¹ rangê.");
					DialogRanga(playerid);
					return 1;
				}
				pInfo[playerid][player_userank] = 11;
			}
			case 12: {//zjaraniec
				if(pInfo[playerid][spalonego_skuna] < 150)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz posiadaæ 150 spalonego zio³a(/ziolohelp) aby ustawiæ t¹ rangê.");
					DialogRanga(playerid);
					return 1;
				}
				pInfo[playerid][player_userank] = 12;
				
			}
			case 13: {//master
				if(pInfo[playerid][zebranych_krzakow] < 200)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz posiadaæ 200 zebranych krzaków marihuany (/ziolohelp) aby ustawiæ t¹ rangê.");
					DialogRanga(playerid);
					return 1;
				}
				pInfo[playerid][player_userank] = 13;
				
			}
			case 14: { //chory czlowiek
				if(pInfo[playerid][player_kills] < 10000)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz posiadaæ 10000 zabójstw ¿eby ustawiæ t¹ rangê");
					DialogRanga(playerid);
					return 1;
				}
				pInfo[playerid][player_userank] = 14;
			}
			case 15: {//Podró¿nik
				if(pInfo[playerid][player_car_przebieg] < 2500)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Twój prywatny pojazd (/pp) musi posiadaæ minimum 2500 km przebiegu");
					DialogRanga(playerid);
					return 1;
				}
				pInfo[playerid][player_userank] = 15;
			}
			case 16: {//drwal
				if(pInfo[playerid][cut_tree] < 150)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz posiadaæ minimum 150 œciêtych drzew!");
					DialogRanga(playerid);
					return 1;
				}
				pInfo[playerid][player_userank] = 16;
			}
			case 17: {//nowy
				pInfo[playerid][player_userank] = 17;
			}
			case 18: {//spammer
				if(pInfo[playerid][player_messages] < 10000)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz posiadaæ minimum 10.000 napisanych wiadomoœci na czacie!");
					DialogRanga(playerid);
					return 1;
				}
				pInfo[playerid][player_userank] = 18;
			}
			case 19: {//desperat
				if(pInfo[playerid][player_suicide] < 250)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz posiadaæ minimum 250 samobójstw!");
					DialogRanga(playerid);
					return 1;
				}
				pInfo[playerid][player_userank] = 19;
			}
			case 20: {//expert
				if(GetPlayerScore(playerid) < 1000000)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz posiadaæ minimum 1.000.000 XP!");
					DialogRanga(playerid);
					return 1;
				}
				pInfo[playerid][player_userank] = 20;
			}
			case 21: {//unstoppable
				if(pInfo[playerid][player_ks] < 33)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" T¹ rangê mo¿esz ustawiæ TYLKO w momencie gdy twój killstreak wynosi minimum 33 zabójstw!!");
					DialogRanga(playerid);
					return 1;
				}
				pInfo[playerid][player_userank] = 21;
			}
		}
		SendClientMessage(playerid, COLOR_GOLD, ""chat" Zmieni³eœ swoj¹ rangê");
	}
	UpdatePlayerNick(playerid);
	return 1;
}

stock UpdatePlayerNick(playerid, bool:nick = true)
{
	if(nick != true) nick = true;
	
	if(nick)
	{	
		PlayerTextDrawHide(playerid, pInfo[playerid][player_TdStats][0]); 
		if(pInfo[playerid][player_admin] > 1)
			PlayerTextDrawColor(playerid, pInfo[playerid][player_TdStats][0], 0xFF0000FF);
		else if(pInfo[playerid][player_admin] == 1)
			PlayerTextDrawColor(playerid, pInfo[playerid][player_TdStats][0], 0x008000FF); // Mod
		else if(pInfo[playerid][player_vip] > gettime())
			PlayerTextDrawColor(playerid, pInfo[playerid][player_TdStats][0], 0xF2F200FF); // ViP
		else
			PlayerTextDrawColor(playerid, pInfo[playerid][player_TdStats][0], 0xC0C0C0FF); // Gracz
		
		PlayerTextDrawShow(playerid, pInfo[playerid][player_TdStats][0]); 
		
		SetPlayerColor(playerid, pInfo[playerid][player_color]);
		switch(pInfo[playerid][player_userank])
		{
			case 0:
			{
				format(pInfo[playerid][player_showname], 128, "{%06x}%s{FFFFFF}", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
			}
			case 1:
			{
				if(!GangPlayer(playerid))
				{
					pInfo[playerid][player_userank] = 0;
					UpdatePlayerNick(playerid);
					
				}
				format(pInfo[playerid][player_showname], 128, "{%06x}%s (%s){FFFFFF}", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name], gInfo[pInfo[playerid][player_gang]][gangTag]);
			}
			case 2:
			{
				
				new adminlvl[][] = {{"{FFFFFF}(Gracz)"}, {"{FFFFFF}({57AD00}Mod{FFFFFF})"}, {"{FFFFFF}({BF1515}JA{FFFFFF})"}, {"{FFFFFF}({BF1515}A{FFFFFF})"}, {"{FFFFFF}({BF1515}vHA{FFFFFF})"}, {"{FFFFFF}({FF1515}HA{FFFFFF})"}};
				
				new show[64];
				
				if(!pInfo[playerid][player_admin] && (pInfo[playerid][player_vip] > gettime() || pInfo[playerid][player_vip] == -1))
				{
					show = "{FFFFFF}("HEX_YELLOW"ViP{FFFFFF})";
				}
				else
				{
					format(show, sizeof(show), "%s", adminlvl[pInfo[playerid][player_admin]]);
				}
				format(pInfo[playerid][player_showname], 128, "{%06x}%s %s", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name], show);
				
			}
			case 3:
			{
				format(pInfo[playerid][player_showname], 128, "{%06x}%s{0000cc} (Sta³y Gracz){ffffff}", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
			}
			case 4:
			{
				format(pInfo[playerid][player_showname], 128, "{%06x}%s{f000f0} (Drifter){ffffff}", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
			}
			case 5:
			{
				format(pInfo[playerid][player_showname], 128, "{%06x}%s{ee0000} ($ponsor){ffffff}", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
			}
			case 6:
			{
				format(pInfo[playerid][player_showname], 128, "{%06x}%s{FFFFFF} (Fan /OneDe)", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
			}
			case 7:
			{
				format(pInfo[playerid][player_showname], 128, "{%06x}%s{FFFFFF} (Pilot)", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
			}
			case 8: {
				format(pInfo[playerid][player_showname], 128, "{%06x}%s{FFFFFF} (Snajper)", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
			}
			case 9: {
				format(pInfo[playerid][player_showname], 128, "{%06x}%s{FFFFFF} (Rolnik)", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
			}
			case 10: {
				format(pInfo[playerid][player_showname], 128, "{%06x}%s{f000f0} (Dziewffczynka){ffffff}", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
			}
			case 11: {// farmer
				format(pInfo[playerid][player_showname], 128, "{%06x}%s{00FF00} (Farmer){ffffff}", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
				
			}
			case 12: {//zjaraniec
				format(pInfo[playerid][player_showname], 128, "{%06x}%s{f000f0} (Zjaraniec){ffffff}", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
				
			}
			case 13: {//ganjamaster
				format(pInfo[playerid][player_showname], 128, "{%06x}%s{f000f0} (GanjaMaster){ffffff}", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
				
			}
			case 14: {//chory cz³owiek
				format(pInfo[playerid][player_showname], 128, "{%06x}%s {1a1a1a}(Chory cz³owiek){ffffff}", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
			}
			case 15: {//podroznik
				format(pInfo[playerid][player_showname], 128, "{%06x}%s {00b36b}(Podró¿nik){ffffff}", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
			}
			case 16: {//drwal
				format(pInfo[playerid][player_showname], 128, "{%06x}%s {996633}-> (Drwal) <-{ffffff}", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
			}
			case 17: { //newbie
				format(pInfo[playerid][player_showname], 128, "{%06x}%s {FFFFFF}({80dfff}Newbie{ffffff})", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
			}
			case 18: { //spammer
				format(pInfo[playerid][player_showname], 128, "{%06x}%s (Spammer)", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
			}
			case 19: { //Desperat
				format(pInfo[playerid][player_showname], 128, "{%06x}%s {FFFFFF}({ff99e6}Desperat{FFFFFF})", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
			}
			case 20: { //expert
				format(pInfo[playerid][player_showname], 128, "{%06x}%s {FFFFFF}({e6b800}Expert{FFFFFF})", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
			}
			case 21: {//unstoppable
				format(pInfo[playerid][player_showname], 128, "{%06x}%s {FFFFFF}(* Unstoppable *)", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name]);
			}
			default:
			{
				pInfo[playerid][player_userank] = 0;
				UpdatePlayerNick(playerid);
			}
		}
	}
}

CMD:setrange(playerid, params[])
{
	RankAdmin(playerid, R_JADMIN);
	
	new pid, rng[12];
	if(sscanf(params,"ds[12]",pid,rng))return SendClientMessage(playerid,COLOR_ERROR,"U¿yj /setrange <id gracza> <ranga>");
	if(!IsPlayerConnected(pid))return SendClientMessage(playerid,COLOR_ERROR,"Podany gracz nie jest online.");
	if(pInfo[pid][player_admin] >= pInfo[playerid][player_admin] && pid != playerid)return SendClientMessage(playerid,COLOR_ERROR,"Pojeba³o cie?");
	SetPlayerRange(playerid,pid,rng);

	SendClientMessage(playerid,COLOR_ERROR,"Wys³ano propozycje ustawienia rangi");
	
	return 1;
}

stock SetPlayerRange(playerid,playerset,ranga[])
{
	new rstr[256];
	format(rstr,256,"{FFFFFF}Administrator %s sk³ada ci propozycjê ustawienia rangi do wylogowania.\n\nRanga: %s\nKoszt: 2500XP\n\nCzy akceptujesz zmianê rangi?",playerNick(playerid), ranga);
	Dialog_Show(playerset, DIALOG_SETRANGE,DIALOG_STYLE_MSGBOX,"Ustawienie rangi",rstr,"Tak","Nie");
	//setrangerang
	format(pInfo[playerset][setrangerang], 12,"%s",ranga);
	return 1;
}

Dialog:DIALOG_SETRANGE(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		GivePlayerScore(playerid, -2500);
		format(pInfo[playerid][player_showname], 128, "{%06x}%s{FFFFFF} (%s)", pInfo[playerid][player_color]>>>8, pInfo[playerid][player_name],pInfo[playerid][setrangerang] );
		SendClientMessage(playerid,COLOR_ERROR,"Ranga ustawiona");
		achievement(playerid,27);
	}
	return 1;
}
stock CreatePlayerVehicle(playerid, selecteditem, Float:anglex = 0.0)
{
 
	if(script_tr[t_zadanie] != 2 && !Iter_Contains(t_r_players, playerid))
	{
		if(GetPlayerInterior(playerid) != 0)
		{
			return SendClientMessage(playerid, COLOR_ERROR, "W tym interiorze nie wolno tworzyæ pojazdów"), 0;
		}
		switch(selecteditem)
		{
			case 425, 432, 441, 406, 449, 464, 465, 501, 520, 537, 538, 564, 569, 570, 590, 591, 594, 606..608, 610, 611:
			{
				SendClientMessage(playerid, COLOR_INFO, "{FFFFFF} "chat"{/b} Tego pojazdu nie mo¿na zespawaæ! (Nawet w strefie DM).");
				return 0;
			}
		}
	}
	
	if(GetVehicleModel(pInfo[playerid][player_vehicle]))
	{
		DestroyVehicleEx(pInfo[playerid][player_vehicle]);
	}	
	if(GetVehicleModel(pInfo[playerid][player_vehicle]))
	{
		DestroyVehicleEx(pInfo[playerid][player_vehicle]);
	}
	pInfo[playerid][player_vehicle] = SpawnVehicle_InfrontOfPlayer2(playerid, selecteditem, -1, -1, anglex);
	Vehicle_PrivClear(pInfo[playerid][player_vehicle]);
	SetVehicleVirtualWorld(pInfo[playerid][player_vehicle], GetPlayerVirtualWorld(playerid));
	
	return pInfo[playerid][player_vehicle];
}

stock SpawnVehicle_InfrontOfPlayer2(playerid, vehiclemodel, color1, color2, Float:anglex = 0.0)
{
	new Float:x, Float:y, Float:z;
	new Float:facing;
	new Float:distance;
	
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, facing);
	
	new Float:size_x, Float:size_y, Float:size_z;
	GetVehicleModelInfo(vehiclemodel, VEHICLE_MODEL_INFO_SIZE, size_x, size_y, size_z);
	distance = size_x + 0.5;
	x += (distance * floatsin(-facing, degrees));
	y += (distance * floatcos(-facing, degrees));
	
	if(anglex != 0.0) facing = anglex;
	return CreateVehicle(vehiclemodel, x, y, z + (size_z * 0.25), facing, color1, color2, 60*60*2);
}

stock UpdatePlayerOnline(playerid, dissconect = 0)
{
	if(pInfo[playerid][player_id] < 1) return 1;
	if(dissconect == 0)
	{
		m_query("update "prefix"_players set isonline = 1, visits = visits+1 where id=%d limit 1", pInfo[playerid][player_id]);
		return 1;
	}
	
	m_query("update "prefix"_players set isonline = 0 where id=%d limit 1", pInfo[playerid][player_id]);
	return 1;
	
}
stock InsertPlayerOnline(playerid)
{
	m_query("INSERT INTO mreg_online (`id`, `nick`, `samp_id`, `account_id`) VALUES (NULL, '%s', '%d', '%d');", pInfo[playerid][player_name], playerid, pInfo[playerid][player_id]);
//	mysql_store_result();
	pInfo[playerid][player_sqlonline] = mysql_insert_id();
	//mysql_free_result();
	//printf("sql id %d", pInfo[playerid][player_sqlonline]);
	return 1;
}
stock SyncCamera(playerid)
{
	if(pInfo[playerid][player_fps])
	{
		gmData[player_objectToPlayer][playerid]=1;
		if(!IsPlayerInAnyVehicle(playerid))
		{
			AttachObjectToPlayer(gmData[player_object][playerid], playerid, 0.0, 0.15, 0.65, 0.0, 0.0, 0.0);
			AttachCameraToObject(playerid, gmData[player_object][playerid]);
		}
		else
		{
			AttachObjectToVehicle(gmData[player_object][playerid], GetPlayerVehicleID(playerid), 0.0, 0.15, 0.10, 0.0, 0.0, 0.0);
			AttachCameraToObject(playerid, gmData[player_object][playerid]);
		}
	} 
	else 
	if(gmData[player_objectToPlayer][playerid]==1)
	{
		gmData[player_objectToPlayer][playerid]=0;
		SetObjectPos(gmData[player_object][playerid], 555.5 + random(500) * 1.0, 666.6, 2954.0);
	}
	return 1;
}


stock AccountExists(const type[], date[])
{
	m_query("select 1 from "prefix"_players where %s='%s' limit 1", type, date);
	
	mysql_store_result();
	
	if(mysql_num_rows() > 0)
	{
		mysql_free_result();
		return 1;
	}
	mysql_free_result();
	return 0;
}
GivePlayerEquipment(userid)
{
	if(pInfo[userid][player_duel]) return;
	
	PlaySoundForPlayer(userid, 30800);
	
	GivePlayerWeapon(userid, 4, 1);
	
	if(pInfo[userid][player_level] <= 3)
		GivePlayerWeapon(userid, 30, 500);
	else if(pInfo[userid][player_level] > 3 && pInfo[userid][player_level] <= 5)
		GivePlayerWeapon(userid, 29, 500);
	else if(pInfo[userid][player_level] > 5)
		GivePlayerWeapon(userid, 31, 500);
	
	if(pInfo[userid][player_level] <= 2)
		GivePlayerWeapon(userid, 25, 500);
	else if(pInfo[userid][player_level] > 2 && pInfo[userid][player_level] <= 4)
		GivePlayerWeapon(userid, 27, 500);
	else if(pInfo[userid][player_level] > 4)
		GivePlayerWeapon(userid, 26, 500);
	
	if(pInfo[userid][player_level] >= 10)
		GivePlayerWeapon(userid, 34, 500);
	
	if(pInfo[userid][player_level] >= 8)
		SetPlayerArmour(userid, 100.0);
	
	if(pInfo[userid][player_level] <= 2)
	{
		GivePlayerWeapon(userid, 22, 500);
		SetPlayerArmedWeapon(userid, 22);
	}
	else if(pInfo[userid][player_level] > 2)
	{
		GivePlayerWeapon(userid, 24, 300);
		SetPlayerArmedWeapon(userid, 24);
	}
}
/*
#define stats_wg 0
#define stats_ch 1
#define stats_hy 2
#define stats_ws 3
#define stats_dd 4
#define stats_ctf 5
#define stats_onede 6
#define stats_sawn 7
#define stats_minigun 8
#define stats_snajper 9
#define stats_matematyk 10
#define stats_codes 11
#define stats_scrable 12
#define stats_duel_win 13
#define stats_duel_lost 14
#define stats_tir 15
#define stats_zb 16
#define stats_tr 17
*/
stock ShowPlayerStats(playerid, forplayer)
{
	if(!pInfo[forplayer][player_register])
	{
		SendClientMessage(forplayer, COLOR_ERROR, ""chat" Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do tej funkcji.");
		return 1;
	}
	else if(!pInfo[playerid][player_register])
	{
		SendClientMessage(forplayer, COLOR_ERROR, ""chat" Ten gracz nie jest zarejestrowany.");
		return 1;
	}
	
	static pinfo[2548];
	pinfo[0] = EOS;
	#define formatpinfo(%0,%1); format(pinfo, sizeof(pinfo), "%s"%0"", pinfo, %1);
	
	format(string2, sizeof(string2), "{0397EF}Statystyki Gracza: {16C60D}%s {0397EF}({16C60D}%i{0397EF})", pInfo[playerid][player_name], playerid);
	
	new ctime = pInfo[playerid][player_timeplay];
	new days = floatround(((ctime) / 86400)),
	godz = floatround(((ctime) / 3600) - (24 * days)),
	minut = floatround(((ctime) / 60) % 60),
	sek = floatround(((ctime) - (60 * (minut))) - (3600 * godz) - (86400 * days) );
	
	new Float:ratio_duel, Float:ratio;
	if(pInfo[playerid][player_eventpoints][stats_duel_win]==0 || pInfo[playerid][player_eventpoints][stats_duel_lost]==0)
		ratio_duel = 0.00;
	else
		ratio_duel = floatdiv(pInfo[playerid][player_eventpoints][stats_duel_win], pInfo[playerid][player_eventpoints][stats_duel_lost]);
	
	if(pInfo[playerid][player_kills]==0 || pInfo[playerid][player_deaths]==0)
		ratio = 0.00;
	else
		ratio = floatdiv(pInfo[playerid][player_kills], pInfo[playerid][player_deaths]);
	
	formatpinfo("\n\t\t\t{007100}Ogólne:\n{0397EF}Respekt:\t\t{16C60D}%d\n{0397EF}Level:\t\t\t{16C60D}%d\n{0397EF}Zginiêæ:\t\t{16C60D}%d\n{0397EF}Zabójstw:\t\t{16C60D}%d\n{0397EF}Ratio:\t\t\t{16C60D}%0.2f\n",\
	pInfo[playerid][player_score], pInfo[playerid][player_level], pInfo[playerid][player_deaths], pInfo[playerid][player_kills], ratio);
	formatpinfo("{0397EF}Samobójstw:\t\t{16C60D}%d\n{0397EF}Czas Gry (Ogólny):\t{16C60D}%d {0397EF}dni, {16C60D}%d {0397EF}godzin, {16C60D}%d {0397EF}minut, {16C60D}%d {0397EF}sekund\n", pInfo[playerid][player_suicide], days, godz, minut, sek);
	
	godz = floatround(((pInfo[playerid][player_connected]) / 3600));
	minut = floatround(((pInfo[playerid][player_connected]) / 60) % 60);
	sek = floatround(((pInfo[playerid][player_connected]) - (60 * (minut))) - (3600 * godz));
	
	formatpinfo("{0397EF}Czas gry:\t\t{16C60D}0 {0397EF}dni, {16C60D}%d {0397EF}godzin, {16C60D} %d {0397EF}minut, {16C60D} %d {0397EF}sekund",\
	godz, minut, sek);
	formatpinfo("\n\n\t\t\t{007100}Eventy:\n{0397EF}Wygranych /WG:\t{16C60D}%d\n{0397EF}Wygranych /CH:\t{16C60D}%d\n{0397EF}Wygranych /HY:\t{16C60D}%d\n", pInfo[playerid][player_eventpoints][stats_wg], pInfo[playerid][player_eventpoints][stats_ch], pInfo[playerid][player_eventpoints][stats_hy]);
	formatpinfo("{0397EF}Wygranych /WS:\t{16C60D}%d\n{0397EF}Wygranych /DD:\t{16C60D}%d\n{0397EF}Wygranych /CTF:\t{16C60D}%d",\
	pInfo[playerid][player_eventpoints][stats_ws], pInfo[playerid][player_eventpoints][stats_dd], pInfo[playerid][player_eventpoints][stats_ctf]);
	formatpinfo("\n\n\t\t\t{007100}Areny:\n{0397EF}Fragów /Onede:\t{16C60D}%d\n{0397EF}Fragów /Chainsaw:\t{16C60D}%d\n{0397EF}Fragów /Minigun:\t{16C60D}%d\n", pInfo[playerid][player_eventpoints][stats_onede], pInfo[playerid][player_eventpoints][stats_sawn], pInfo[playerid][player_eventpoints][stats_minigun]);
	formatpinfo("{0397EF}Fragów /Sniper:\t{16C60D}%d\n\n\t\t\t{007100}Solo:\n{0397EF}Wygranych:\t\t{16C60D}%d\n{0397EF}Przegranych:\t\t{16C60D}%d\n{0397EF}Ratio:\t\t\t{16C60D}%0.2f",\
	pInfo[playerid][player_eventpoints][stats_snajper], pInfo[playerid][player_eventpoints][stats_duel_win], pInfo[playerid][player_eventpoints][stats_duel_lost], ratio_duel);
	
	formatpinfo("\n\n{0397EF}Skill:\t{16C60D}%d",pInfo[playerid][player_skill]);
	
	formatpinfo("\n\n{0397EF}Nasionka:\t{16C60D}%d\n\r{0397EF}Marihuana:\t{16C60D}%d\n\r{0397EF}Posadzonych krzaków:{FFFFFF} %d\n\r{0397EF}Zebranych krzaków: {FFFFFF}%d\n\r{0397EF}Spalonego skuna: {FFFFFF}%d\n\r{0397EF}Sciêtych drzew:{FFFFFF} %d",pInfo[playerid][player_nasionka], pInfo[playerid][player_marihuana], pInfo[playerid][posadzonych_krzakow], pInfo[playerid][zebranych_krzakow], pInfo[playerid][spalonego_skuna], pInfo[playerid][cut_tree]);
	
	ShowPlayerDialog(forplayer, 9999, DIALOG_STYLE_MSGBOX, string2, pinfo, "OK", "");
	
	return 1;
}

stock ShowPlayerGui(playerid)
{
	new str512[512];
	
	if(pInfo[playerid][player_ramp_pers] == -1)
		format(str512, sizeof(str512), ""chat" /Rampy (OFF)");
	else
		format(str512, sizeof(str512), ""chat" /Rampy (ON)");
	
	if(pInfo[playerid][player_teleports])
		format(str512, sizeof(str512), "%s\n"chat" /Idzdo (OFF)", str512);
	else
		format(str512, sizeof(str512), "%s\n"chat" /Idzdo (ON)", str512);
	
	
	if(pInfo[playerid][player_pm])
		format(str512, sizeof(str512), "%s\n"chat" /PM (OFF)", str512);
	else
		format(str512, sizeof(str512), "%s\n"chat" /PM (ON)", str512);
	
	strcat(str512, "\n"chat" Zmieñ has³o");
	strcat(str512, "\n"chat" Zmieñ nick");
	strcat(str512, "\n"chat" Osi¹gniêcia");
	strcat(str512, "\n"chat" Statystyki");
	
	if(!pInfo[playerid][player_objected])
		format(str512, sizeof(str512), "%s\n"chat" /Setobject (ON)", str512);
	else 
		format(str512, sizeof(str512), "%s\n"chat" /Setobject (OFF)", str512);
		
	if(pInfo[playerid][player_nopduel] == true)
		format(str512, sizeof(str512), "%s\n"chat" /Setduel (OFF)", str512);
	else
		format(str512, sizeof(str512), "%s\n"chat" /Setduel (ON)", str512);
		
	strcat(str512, "\n"chat" Zmieñ spawn");
	

	
	Dialog_Show(playerid, Dialog_Konto, DIALOG_STYLE_LIST, "Panel", str512, "Dalej", "Zamknij");
}

stock ShowPlayerDialogLogin(playerid, const note[])
{
 
//	if(!pInfo[playerid][player_introend]) return;
	static string_log[1000];
	string_log[0] = EOS;
	
	format(string_log, sizeof(string_log), "%s{00CC00}%s{00EA00} witaj{00CC00} ponownie{00AE00} na{009000} Polskim{007200} 4Fun{005400} Serwerze{00CC00} v."version"!\n\n{CC0000}Twój nic\
	k{EA0000} jest{CC0000} zarejestrowany{AE0000} aby{900000} dalej{AE0000} graæ{EA0000} musisz{CC0000} siê{EA0000} zalogowaæ{AE0000} podaj¹c{900000} has³o{AE0000} poni¿ej:", note, playerNick(playerid));
	
	if(note[0])
	{
		strins(string_log, "\n\n\n", strlen(note));
	}
	ShowPlayerDialog(playerid, DIALOG_LOG, DIALOG_STYLE_PASSWORD, "{00CC00}• {AE0000}Login {00CC00}•", string_log, "Zaloguj", "Kick");
}
/*
stock UpdatePlayerLabelText(playerid)
{
	pInfo[playerid][player_labelt][0] = EOS;
	
	if(pInfo[playerid][player_admin] >= R_JADMIN)
		strcopy(pInfo[playerid][player_labelt], "{ff0000}Admin");
	else if (pInfo[playerid][player_admin] == R_MODERATOR)
	strcopy(pInfo[playerid][player_labelt], "{33AA33}Moderator");
	else if (pInfo[playerid][player_vip] > gettime())
	strcopy(pInfo[playerid][player_labelt], "{E9E312}VIP");
	
	if(pInfo[playerid][player_gang])
	{
		if(strlen(pInfo[playerid][player_labelt])>3)
			strcat(pInfo[playerid][player_labelt]," {ffffff}¦ ");
		
		format(pInfo[playerid][player_labelt], 64, "%s{%06x}%s", pInfo[playerid][player_labelt], gInfo[pInfo[playerid][player_gang]][gangColor]>>>8, gInfo[pInfo[playerid][player_gang]][gangNazwa]);
	}
	if(pInfo[playerid][player_afk] > 2)
	{
		if(pInfo[playerid][player_afk] > 4 && pInfo[playerid][player_afk] < 6)
		{
			RemoveFromEventAfk(playerid);
		}
		
		if(strlen(pInfo[playerid][player_labelt])>3)
			strcat(pInfo[playerid][player_labelt],"\n");
		else
			strcat(pInfo[playerid][player_labelt]," {ffffff}¦ ");
		
		Time_Convert(pInfo[playerid][player_afk], tc_min, tc_sek);
		format(pInfo[playerid][player_labelt], 64, "%s\nAFK: %dm %02ds", pInfo[playerid][player_labelt], tc_min, tc_sek);
	}
}*/
stock FreezePlayerTime(playerid, time)
{
	TogglePlayerControllable(playerid, 0);
	pInfo[playerid][player_unfreeze] = time;
}

GetPlayerWeaponList(playerid,uid)
{
	
	if (!IsPlayerConnected(uid)) return;
	
	new buf[130];
	new wepid,ammo;
	new warn=0;
	new clr, bool:systemgive;
	SendClientMessage(playerid, COLOR_INFO2, ""chat" Bronie gracza {b}%s (%d){/b}", playerNick(uid), uid);
	for (new slot=0; slot<=12;slot++) {
		GetPlayerWeaponData(uid,slot,wepid,ammo);
		if (ammo==0) continue;
		warn=0;
		systemgive = true;
		if (wepid<=15 && ammo>1) warn++;
		if (wepid<=15 && ammo>10) warn++;
		if (ammo==198) warn++;
		else if (ammo<0) warn++;
		
		if (wepid ==36 || wepid == 44 || wepid==45)
		warn += 2;
		
		if(IsWeaponWH(wepid))
			if(!pInfo[playerid][player_weapons][wepid]) systemgive = false;
		
		if(!systemgive) warn += 2;
		
		if(warn > 5) warn = 6;
		clr=0xff - (warn*50);
		format(buf, sizeof(buf), "%s {ff%02x%02x}%s (id: %d, ammo: %d%s)", buf, clr, clr, GetWeaponNameEx(wepid), wepid, ammo, systemgive == false ? (", {b}prawdopodobny WH{/b}"):(""));
		if (strlen(buf)>128)
		{
			SendClientMessage(playerid,-1,buf);
			format(buf, sizeof(buf), "");
		}
	}
	if (strlen(buf)>0)
	SendClientMessage(playerid,-1,buf);
	return;
}

stock GivePlayerHealth(playerid, Float:health)
{
	new Float:h1[2];
	
	GetPlayerHealth(playerid, h1[0]);
	GetPlayerArmour(playerid, h1[1]);
	
	if(h1[1] > health)
		return SetPlayerArmour(playerid, h1[1] + health);
	else 
		return SetPlayerHealth(playerid, h1[0] + health);
}

stock IsPlayerEventItp(playerid)
{
	if(pInfo[playerid][player_fishing] || pInfo[playerid][player_arena] || pInfo[playerid][player_duel]) return 1;
	if(is_event(playerid)) return 1;
	
	return 0;
}

stock RemoveFromEventAfk(playerid)
{
	if(IsPlayerEventItp(playerid))
	{
		if(pInfo[playerid][player_arena])
		{
			gmData[server_arenaplayers][pInfo[playerid][player_arena]]--;
			UpdateArenaPlayers();
			
			pInfo[playerid][player_arena] = 0;
			
			ResetPlayerWeapons(playerid);
			OnPlayerSpawn(playerid);
			
		 
 			SetPlayerColorEx(playerid);
			PlayerEventTD(playerid, false);
			SendClientMessage(playerid, COLOR_GREEN, "Zosta³eœ wyrzucony z areny poniewa¿ by³eœ {b}AFK{/b}");
		}
		if(pInfo[playerid][player_duel])
		{
			if(pInfo[playerid][player_duel_toplayer])
			{
			 
				DuelWin(pInfo[playerid][player_duel_toplayer]);
				SendClientMessage(playerid, COLOR_LIME_GREEN, ""chat" Zosta³eœ wyrzucony z solo poniewa¿ by³eœ {b}AFK{/b}");
			}
		}
		if(is_event(playerid)){
			removeIsEvent(playerid);
		}
		
	}
	return 1;
}

new NetStats_stats[256];
stock Float:NetStats_PacketLossPercent2(playerid){
	 
    GetPlayerNetworkStats(playerid, NetStats_stats, sizeof(NetStats_stats));
	
	new g = strfind(NetStats_stats, "Packetloss: ", true);
	//printf("halo %s",NetStats_stats);
	if(g>0) {
		
		strdel(NetStats_stats, 0, g+12);
		strdel(NetStats_stats, strfind(NetStats_stats, "%", true), strlen(NetStats_stats));
	}
	return floatstr(NetStats_stats);
}