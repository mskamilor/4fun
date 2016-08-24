/*
          Dialogs RELASED
      (c) Copyright 2013-2014 by mrdrifter,Game
 
	  @author    : mrdrifter (http://p4serv.pl/__drifter__/), Game
	  @date      : 14 grudnia 2013
	  @update    : 3 stycznia 2014
  
 */
 						
#define additional_commend "» /test - xx \n\
						» /nastepna - blabla	"
						
#define vip_commend "» /test - xx \n\
						» /nastepna - blabla	"
						
#define mod_commend "» /test - xx \n\
						» /nastepna - blabla	"
						
#define admin_commend "» /test - xx \n\
						» /nastepna - blabla	"
						


stock Gui_ShowPlayersCommandsMenu(playerid)
{
	Dialog_Show(playerid, CommandsMenu, DIALOG_STYLE_LIST, "• Help » commands •", "» G³ówne\n» Dodatkowe\n» Vip\n» Moderator\n» Administrator", "Wybierz", "Wróæ");
}

stock Gui_ShowPlayersHelp(playerid)
{
	Dialog_Show(playerid, Help, DIALOG_STYLE_LIST, "• Help •", "» Listy komend\n» Nowoœci\n» Autorzy", "Wybierz", "Zamknij");
}
stock Gui_ShowPlayerDriftDialog(playerid)
{
	Dialog_Show(playerid, Drift, DIALOG_STYLE_MSGBOX, "• Drift •", "Czy chcesz w³¹czyæ licznik driftu?", "Tak", "Nie");
}
stock Gui_ShowVehiclesCategories(playerid)
{
	Dialog_Show(playerid, Vehicles, DIALOG_STYLE_LIST, "• Vehicles •", "» Samoloty\n» Helikoptery\n» Motory & Rowery\n» Kabriolety\n» Przemys³owe\n» Lowriders\n» Off Road\n» Publiczne\n» Salonowe\n» Sportowe\n» £odzie\n» Unikalne", "Wybierz", "Zamknij");
}
Dialog:DIALOG_TOPS0(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		#define c listitem
		
		new i_string2[1900];
		pInfo[playerid][player_dialog_data][0] = c;
		for(new i;i<topCount[c];i++)
		{
			format(i_string2, sizeof(i_string2), "%s» %s\n", i_string2, topInfo[c][i][ename]); 
		}
		strdel(i_string2, strlen(i_string2)-2, strlen(i_string2));
		Dialog_Show(playerid, DIALOG_TOPS10, DIALOG_STYLE_LIST, "• Top •", i_string2, "Wybierz", "Zamknij");
		
		#undef c
	}
	return 1;
}

Dialog:Dialog_WyborSpawnu(playerid,response,listitem,inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0: {
				pInfo[playerid][wybrany_spawn] = 0;
				SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Zmieni³eœ swój spawn na losowy.");
				achievement(playerid,32);
			}
			case 1: {
				if(pInfo[playerid][player_house] == 0) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Nie posiadasz domu!");
				pInfo[playerid][wybrany_spawn] = 1;
				SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Zmieni³eœ swój spawn na dom.");
				achievement(playerid,32);
			}
			case 2: {
				if(!pInfo[playerid][player_gang]) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Nie posiadasz gangu!");
				pInfo[playerid][wybrany_spawn] = 2;
				SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Zmieni³eœ swój spawn na baze gangu.");
				achievement(playerid,32);
			}
		}
	}
	return 1;
}

Dialog:DIALOG_TOPS10(playerid, response, listitem, inputtext[])
{
	new Query[128], id=1, user[32], value, type[32] = "desc", Float:value2, bool:floaat;
	static str[2048];
	str[0] = EOS;
	if(response)
	{
		#define c pInfo[playerid][player_dialog_data][0]
		
		if(c==3)
		{
			switch(listitem)
			{
				case 3,4,5: 
				{
					floaat = true;
					type = "asc";
				}
			}
		}
		else if(c==0&&listitem==11) floaat = true;
		m_query("select nick,%s from "prefix"_players order by %s %s limit 15", topInfo[c][listitem][esql], topInfo[c][listitem][esql], type);
		mysql_store_result();
		format(str,sizeof(str),""HEX_INFO"ID:\t{EAB171}Nick:\t\t\t\t{AC3E00}Punkty:\n");
 		while(mysql_fetch_row(Query))
		{
 			if(floaat)
			{
				sscanf(Query,"p<|>s[32]f", user, value2);
				format(type, sizeof(type), "%.2f", value2);
			}
			else 
			{				
				sscanf(Query,"p<|>s[32]d", user, value);				
				format(type, sizeof(type), "%d", value);
			}
			if(!strcmp(topInfo[c][listitem][esql], "timeplay", true))
			{
				new days = floatround(((value) / 86400)), 
					godz = floatround(((value) / 3600) - (24 * days)), 
					minut = floatround(((value) / 60) % 60), 
					sek = floatround(((value) - (60 * (minut))) - (3600 * godz) - (86400 * days) );
				format(str,sizeof(str),"%s\n"HEX_INFO"%02d.	{EAB171}%24s		   {AC3E00} %02dd %02dh %02dm %02d",str, id++, user, days, godz, minut, sek);
				continue;
			}
			if(!strcmp(type, "99.9", true, 3) || !strcmp(type, "0", true)) type = "--";
 			format(str,sizeof(str),"%s\n"HEX_INFO"%02d.	{EAB171}%26s	    	   {AC3E00}%32s",str, id++, user, type);
		}
		Dialog_Show(playerid, DIALOG_TOPS102, DIALOG_STYLE_MSGBOX, "• Top •", str, "Zamknij", "Wróæ");
		#undef c
	} else Dialog_Show(playerid, DIALOG_TOPS0, DIALOG_STYLE_LIST, "• Top •", " » Dotycz¹ce Gry\n » Dotycz¹ce Eventow\n » Dotycz¹ce Aren\n » Inne", "Wybierz", "Zamknij");
	return 1;
}
Dialog:DIALOG_STATS0(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0: ShowPlayerStats(playerid, playerid);
			case 1:
			{
				new str[512];
				
				format(str, sizeof(str), "Statystyki Servera:\n\nRekord Graczy: %d\nDzisijeszy rekord Graczy: %d\nBanów czasowych: %d\nBanów Permanentnych %d\nRozdanych kicków: %d", gmData[server_record], gmData[server_dayrecord], gmData[server_banscz], gmData[server_bansp], gmData[server_kicks]);
				ShowPlayerDialog(playerid, 9999, DIALOG_STYLE_MSGBOX, "Statystyki Servera", str, "Zamknij", "");
			}
			case 2:Dialog_Show(playerid, DIALOG_TOPS0, DIALOG_STYLE_LIST, "• Top •", " » Dotycz¹ce Gry\n » Dotycz¹ce Eventow\n » Dotycz¹ce Aren\n » Inne", "Wybierz", "Zamknij");
		}
	}
	return 1;
}
 
Dialog:DIALOG_TOPS102(playerid, response, listitem, inputtext[])
{
	
	if(response){}
	else 
	{
		DialogFunc:DIALOG_TOPS0(playerid, 1, pInfo[playerid][player_dialog_data][0], inputtext);
	}
	//Dialog_Show(playerid, DIALOG_TOPS0, DIALOG_STYLE_LIST, "• Top •", " » Dotycz¹ce Gry\n » Dotycz¹ce Eventow\n » Dotycz¹ce Aren\n » Inne", "Wybierz", "Zamknij");
	
	return 1;
}
Dialog:DIALOG_NEWTELE(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		Dialog_Show(playerid, DIALOG_NEWTELE_TYPE, DIALOG_STYLE_LIST, "Wybierz typ teleportu", "Stunt/Drift/Race/Rozrywka\nInne", "Dalej", "Anuluj...");
	}
	return 1;
}


Dialog:DIALOG_STACJE2(playerid, response, listitem, inputtext[])
{
	if(!response) 
		return 0;
	SendClientMessage(playerid, COLOR_NAVAJO_WHITE, "» Wybra³eœ: %s (Radio alternatywne aby wy³¹czyæ wpisz /radio2off)", StacjeRadiowe[listitem][Nazwa]);
	PlayAudioStreamForPlayer(playerid,StacjeRadiowe[listitem][URL]);
	return 1;
}
Dialog:DIALOG_GLOSNOSC(playerid, response, listitem, inputtext[])
{
	if(!response) 
		return 0;
	SendClientMessage(playerid, COLOR_NAVAJO_WHITE, "» Ustawi³eœ poziom g³oœnoœci radia na: {b}%i{/b} procent", listitem);
	#if defined ADUIO_PLUGIN
	Audio_SetVolume(playerid, pInfo[playerid][player_stacja], listitem);
	#endif
	return 1;
}
Dialog:DIALOG_NEWTELE_TYPE(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		pInfo[playerid][player_dialog_data][0] = listitem;
		Dialog_Show(playerid, DIALOG_NEWTELE_NAME, DIALOG_STYLE_INPUT, "Wybierz nazwê", "Wpisz nazwê teleportu ("HEX_ERROR"Musisz dodaæ przed nazw¹ '/'"HEX_SAMP"). \n\n", "Dalej", "Anuluj...");
	}
	return 1;
}
Dialog:DIALOG_CHEATS(playerid, response, listitem, inputtext[])
{
	if(response) 
	{
		if(IsPlayerEventItp(playerid))
		{
			InfoBox(playerid, "Nie mo¿esz teraz tego zrobiæ.");
			return 1;
		}
	
		pInfo[playerid][player_cheats]=listitem+1;
		switch(listitem)
		{
			case 0: SendClientMessage(playerid, 0xFFFF00AA, "Wybrano opcje: Podskakiwanie, nacisnij klakson zeby wlaczyc.");
			case 1: SendClientMessage(playerid, 0xFFFF00AA, "Wybrano opcje: Turbo, nacisnij klakson zeby wlaczyc.");
			case 2: SendClientMessage(playerid, 0xFFFF00AA, "Wybrano opcje: Stopniowe zwalnianie, nacisnij klakson zeby wlaczyc.");
			case 3: SendClientMessage(playerid, 0xFFFF00AA, "Wybrano opcje: Natychmiastowy stop, nacisnij klakson zeby wlaczyc.");
			case 4: SendClientMessage(playerid, 0xFFFF00AA, "Wybrano opcje: Obrot o 180 stopni, nacisnij klakson zeby wlaczyc.");
			case 5: SendClientMessage(playerid, 0xFFFF00AA, "Wybrano opcje: Zmiana koloru pojazdu, nacisnij klakson zeby wlaczyc.");
			case 6: 
			{
				pInfo[playerid][player_cheats]=0;
				SendClientMessage(playerid, 0xFFFF00AA, "Czity wylaczone pomyslnie.");
			}
		}
	}
	else 
		SendClientMessage(playerid, 0xFFFFFFFF, "* Wybieranie Anulowane.");
	return 1;
}

Dialog:DIALOG_NEWTELE_NAME(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		RankAdmin(playerid, R_VICEHEADADMIN);
		if(!inputtext[1] || inputtext[0] != '/')
		{
			Dialog_Show(playerid, DIALOG_NEWTELE_NAME, DIALOG_STYLE_INPUT, "Wybierz nazwê", "Wpisz nazwê teleportu ("HEX_ERROR"Musisz dodaæ przed nazw¹ '/'"HEX_SAMP"). \n\n", "Dalej", "Anuluj...");
			return 1;
		}
		
		new Float:pos[4];
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		GetPlayerFacingAngle(playerid, pos[3]);		
		
		for(new i;i<4;i++)
			tInfo[loadedTeleports][telPos][i] = pos[i];
			
		mysql_real_escape_string(inputtext, tInfo[loadedTeleports][telName]);
			
		tInfo[loadedTeleports][telLoad] = true;
		tInfo[loadedTeleports][telInterior] = GetPlayerInterior(playerid);
		loadedTeleports++;
		format(teleporty[pInfo[playerid][player_dialog_data][0]], 2500, "%s\n"chat"%s", teleporty[pInfo[playerid][player_dialog_data][0]], tInfo[loadedTeleports][telName]);
		
		m_query("INSERT INTO `mreg_teles` (`id`, `name`, `position`, `interior`, `type`, `author`) VALUES (NULL, '%s', '%f, %f, %f, %f', '%d', '%d', '%s');", inputtext, pos[0], pos[1], pos[2], pos[3], GetPlayerInterior(playerid), pInfo[playerid][player_dialog_data][0], playerNick(playerid));
 	}
	return 1;
}
Dialog:Drift(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		pInfo[playerid][player_driftcouter] = true;
		SendClientMessage(playerid, COLOR_GOLD, ""chat" W³¹czy³eœ licznik driftu. Od teraz Twoje punkty driftu bêdê naliczane.");
	}
	else 
	{
		pInfo[playerid][player_driftcouter] = false;
		SendClientMessage(playerid, COLOR_GOLD, ""chat" Wy³¹czy³eœ licznik driftu. Od teraz Twoje punkty driftu nie bêdê naliczane.");
	}
}
Dialog:SaveGlitch(playerid, response, listitem, inputtext[])
{
	SetTimerEx("glitch_NextPart", 2000, 0, "i", playerid);
	if(response)
	{
		if(pInfo[playerid][player_glitchSaved] > 3) 
		{
			if(GetPlayerScore(playerid) < 200)
				return SendClientMessage(playerid, 0, "Nie masz tyle respektu!");
			GivePlayerScore(playerid, -200);
		}
		pInfo[playerid][player_glitchSaved]++;
		InsertGlitchInfo(playerid);
		
		SendClientMessage(playerid, COLOR_GOLD, ""chat" Zapisa³eœ Glitch'a do bazy danych");
	}
	pInfo[playerid][player_glitchCount][0] = 0; pInfo[playerid][player_glitchCount][1] = 0; pInfo[playerid][player_glitchCount][2] = 0; pInfo[playerid][player_glitchCount][3] = 0;
					 
	return 1;
}

Dialog:VehiclesBuy(playerid, response, listitem, inputtext[])
{
 
	if (response)
	{
	
		if(IsPlayerEventItp(playerid) || is_event(playerid))
		{
			InfoBox(playerid, "Nie mo¿esz teraz tego zrobiæ.");
			return 1;
		}
		
		new cv = CreatePlayerVehicle(playerid, pInfo[playerid][player_dialog_data][listitem] + 400);
		
		PutPlayerInVehicle(playerid, cv, 0);
		
		SendClientMessage(playerid, COLOR_GOLD, ""chat" Stworzy³eœ pojazd %s.", VehicleNames[pInfo[playerid][player_dialog_data][listitem]]);
		if(GetPlayerMoney(playerid) < 5000) GivePlayerMoney(playerid, -5000);
	}  else Gui_ShowVehiclesCategories(playerid);
	return 1;
}
 
Dialog:DIALOG_CMD_SEND(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		RunComment(playerid, inputtext);
	}
	return 1;
}

Dialog:DIALOG_CMD_FROMGANGS(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		if(listitem == 0)
		{
			if(!pInfo[playerid][player_gang])
			{
				InfoBox(playerid, "Nie nale¿ysz do ¿adnego gangu. Aby móc stworzyæ teleport dla Gangu musisz byæ cz³onkiem gangu.");
				return 1;
			}
			if(!pInfo[playerid][player_portfel] || pInfo[playerid][player_portfel] < 1)
			{
				InfoBox(playerid, "Nie mo¿esz stworzyæ teleportu poniewa¿ nie masz 1z³ w wirtualnym porteflu.");
				return 1;
			}
			Dialog_Show(playerid, DIALOG_GANGTELE_ACCEPT, DIALOG_STYLE_MSGBOX, "• Teleports •", "Czy chcesz stworzyæ teleport dla swojego Gangu?\nStworzenie teleportu kosztuje 1z³ z wirtualnego portfela.", "Tak", "Nie");
		}
		else 
			RunComment(playerid, inputtext);
	}
	return 1;
}


Dialog:DIALOG_GANGTELE_ACCEPT(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		Dialog_Show(playerid, DIALOG_GANGTELE, DIALOG_STYLE_INPUT, "Wybierz nazwê", "Wpisz nazwê teleportu:", "Dalej", "Anuluj...");

	}
}
Dialog:DIALOG_GANGTELE(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(!inputtext[1] || inputtext[0] != '/')
		{
			Dialog_Show(playerid, DIALOG_GANGTELE, DIALOG_STYLE_INPUT, "Wybierz nazwê", "Wpisz nazwê teleportu ("HEX_ERROR"Musisz dodaæ przed nazw¹ '/'"HEX_SAMP"). \n\n", "Dalej", "Anuluj...");
			return 1;
		}
		
		if(!PasswordCorrect(inputtext[1]))
		{
			Dialog_Show(playerid, DIALOG_GANGTELE, DIALOG_STYLE_INPUT, "Wybierz nazwê", "Wpisz nazwê teleportu ("HEX_ERROR"Nazwa teleportu mo¿e zawieraæ znaki A-Z, a-z, 0-9."HEX_SAMP"). \n\n", "Dalej", "Anuluj...");
			return 1;
		}
		
		new Float:pos[4];
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		GetPlayerFacingAngle(playerid, pos[3]);		
		
		for(new i;i<4;i++)
			tInfo[loadedTeleports][telPos][i] = pos[i];
			
		mysql_real_escape_string(inputtext, tInfo[loadedTeleports][telName]);
			
		tInfo[loadedTeleports][telLoad] = true;
		tInfo[loadedTeleports][telInterior] = GetPlayerInterior(playerid);
		
		format(teleporty[2], 2500, "%s\n"chat"%s", teleporty[2], tInfo[loadedTeleports][telName]);
		loadedTeleports++;
		m_query("INSERT INTO `mreg_teles` (`id`, `name`, `position`, `interior`, `type`, `author`, `togang`) VALUES (NULL, '%s', '%f, %f, %f, %f', '%d', '%d', '%s', '%d');", inputtext, pos[0], pos[1], pos[2], pos[3], GetPlayerInterior(playerid), pInfo[playerid][player_dialog_data][0], playerNick(playerid),gInfo[pInfo[playerid][player_gang]][gangid]);
		
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Teleport dodany. :)");
		
		AddPlayerLog(playerid, LOG_PORTFEL, tInfo[loadedTeleports][telName], "-newtele-");
		GivePlayerPortfel(playerid, -1);
	}
	return 1;
}
Dialog:DIALOG_REPORTS(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new rid = pInfo[playerid][player_reportID][listitem],
		nstr[68];
		
		if(!rData[rid][rMessage])
		{
			SendClientMessage(rData[rid][rZglaszajacy], COLOR_GOLDENROD, ""chat" Raport który wys³a³eœ jest w³aœnie sprawdzany przez administratora!");
			rData[rid][rMessage] = true;
		}
		pInfo[playerid][player_actionplayer] = rid;
		format(nstr, sizeof(nstr), "[%s] \t\tZamknij [x]\nSpec\nUsuñ", playerNick(rData[rid][rZgloszony]));
		
		Dialog_Show(playerid, DIALOG_REPORTS2, DIALOG_STYLE_LIST, "Raport", nstr, "Wykonaj", "Anuluj");
	}
	return 1;
}
Dialog:DIALOG_REPORTS2(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		
		new rid = pInfo[playerid][player_actionplayer];
		
		switch(listitem)
		{
			case 0:
			{
				return 1;
			}
			case 1:
			{
				StartSpec(playerid, rData[rid][rZgloszony]);
				return 1;
			}
			case 2:
			{
				rData[rid][rUsed] = false;
				SendClientMessage(playerid, COLOR_INFO, ""chat" Raport zosta³ usuniêty.");
				
				Reports(playerid);
				
			}
		}
	}
	return 1;
}

	 
Dialog:Vehicles(playerid, response, listitem, inputtext[])
{
	 
	if (response)
	{
		static buff[2000];
		buff[0] = EOS;
		for(new i;i<MAX_DIALOG_DATA;i++) pInfo[playerid][player_dialog_data][i] = 0;
		switch(listitem)
		{
		
			case 0:
			{
				for(new i;i<sizeof(CategoryAirplanes);i++)  
					pInfo[playerid][player_dialog_data][i] = CategoryAirplanes[i];
			}
			case 1:
			{
				for(new i;i<sizeof(CategoryHelis);i++)  
					pInfo[playerid][player_dialog_data][i] = CategoryHelis[i];
			}
			case 2:
			{
				for(new i;i<sizeof(CategoryMotorsAndBikes);i++)  
					pInfo[playerid][player_dialog_data][i] = CategoryMotorsAndBikes[i];
			}
			case 3:
			{
				for(new i;i<sizeof(CategoryCabriolets);i++)  
					pInfo[playerid][player_dialog_data][i] = CategoryCabriolets[i];
			}
			case 4:
			{
				for(new i;i<sizeof(CategoryIndustrials);i++)  
					pInfo[playerid][player_dialog_data][i] = CategoryIndustrials[i];
			}	
			case 5:
			{
				for(new i;i<sizeof(CategoryLowriders);i++)  
					pInfo[playerid][player_dialog_data][i] = CategoryLowriders[i];
			}
			case 6:{//
				for(new i;i<sizeof(CategoryOffroad);i++)  
					pInfo[playerid][player_dialog_data][i] = CategoryOffroad[i];
			}
			case 7:
			{
				for(new i;i<sizeof(CategoryPublic);i++)  
					pInfo[playerid][player_dialog_data][i] = CategoryPublic[i];
			}
			case 8:
			{
				for(new i;i<sizeof(CategorySaloon);i++)  
					pInfo[playerid][player_dialog_data][i] = CategorySaloon[i];
			}
			case 9:
			{
				for(new i;i<sizeof(CategorySport);i++)  
					pInfo[playerid][player_dialog_data][i] = CategorySport[i];
			}
			case 10:
			{
				for(new i;i<sizeof(CategoryBoats);i++)  
					pInfo[playerid][player_dialog_data][i] = CategoryBoats[i];
			}
			case 11:
			{
				for(new i;i<sizeof(CategoryUnicals);i++)  
					pInfo[playerid][player_dialog_data][i] = CategoryUnicals[i];
			}
		}
		
		for(new i;i<MAX_DIALOG_DATA;i++)
		{
			if(!pInfo[playerid][player_dialog_data][i]) continue;
			
			format(buff, sizeof(buff), "%s » %s \n", buff, VehicleNames[pInfo[playerid][player_dialog_data][i]]);
			 
		}
		Dialog_Show(playerid, VehiclesBuy, DIALOG_STYLE_LIST, "• Vehicles •", buff, "Wybierz", "Zamknij");
	}  
/*	else 
	{
		Gui_ShowVehiclesCategories(playerid);
	}*/
}

Dialog:Nowosci(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		switch(listitem)
		{
			
			case 0:
			{
				Dialog_Show(playerid, ToHelp, DIALOG_STYLE_LIST, "• News •", "Wszystkie nowoœci dostêpne na forum www.4fun-serv.eu", "Zamknij", "Wróæ");
			}
			
		}
	}  
	return 1;
}
Dialog:Help(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		switch(listitem)
		{
			case 0: Gui_ShowPlayersCommandsMenu(playerid);
			case 1: 
			{
				Dialog_Show(playerid, Nowosci, DIALOG_STYLE_LIST, "• News •", "HAPPY FUN 1.3 {0080FF}* Msk. Aktualizacja *", "Poka¿", "Zamknij");
			}
			case 2:
			{
			
				static autorzy[1500];
				autorzy[0] = EOS;
				
				strcat(autorzy, "Polski 4Fun Server "HEX_GOLD""gamemode""HEX_SAMP"\n\n");
				strcat(autorzy, ""HEX_GOLD"Programista: \t"HEX_SAMP"Game & mrdrifter , kontynuacja Msk.\n");
			//	strcat(autorzy, ""HEX_GOLD"Obiektorzy: \t"HEX_SAMP"Tabi, GF5, Jakub.\n\n\n");
				
				strcat(autorzy, ""HEX_GOLD"Podziêkowania dla/beta testerzy:"HEX_SAMP"\nSA-MP Team, Y_Less, DracoBlue, Pytelek, eider, silent, {FF0000}ToxiC`"HEX_SAMP", Emmet_, Andrew, \nIncognito, JaTochNietDan, Toribio, Fro1sha, ");
				strcat(autorzy, "Correlli, Msk.(Kamilek), Mkw., bartekdvd.");
				
				strcat(autorzy, "\n\n\nCopyrighnt 2013-2014 "HEX_GOLD"Polski 4Fun Server "HEX_SAMP""version""HEX_ERROR".");
				
				Dialog_Show(playerid, ToHelp, DIALOG_STYLE_MSGBOX, "• Authors •", autorzy, "Zamknij", "Wróæ");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_TP(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		if(IsPlayerEventItp(playerid))
		{
			InfoBox(playerid, "Nie mo¿esz teraz tego zrobiæ.");
			return 1;
		}
		
		if(!IsPlayerConnected(pInfo[playerid][player_tp_to])) return SendClientMessage(playerid, COLOR_ERROR, "» Ten  nie jest pod³¹czony!");
		
		if(pInfo[ playerid ][player_gangWarTeam] != 0)
		{	
			AddPlayerPenalty(pInfo[playerid][player_tp_to], P_JAIL, INVALID_PLAYER_ID, 100, "Bug using (/idzdo na sparze)");
			return 1;
		}
		/*if(IsPlayerEventItp(playerid) || IsPlayerEventItp(pInfo[playerid][player_tp_to])){
			SetPlayerHealth(playerid, 0.0);
			SetPlayerHealth(playerid, 0.0);
			
			SendClientMessage(pInfo[playerid][player_tp_to], COLOR_INFO, ""chat" !!!!!!!! SMIERÆ ZA PROBE OSZUSTFA :|||| !!!!!!!!!!");
			SendClientMessage(playerid, COLOR_INFO, ""chat" !!!!!!!! SMIERÆ ZA PROBE OSZUSTFA :|||| !!!!!!!!!!");
		}
		*/
		TeleportPlayerToPlayer(pInfo[playerid][player_tp_to], playerid, true);
	}
	else SendClientMessage(pInfo[playerid][player_tp_to], COLOR_INFO3, ""chat" Gracz {b}%s{/b} odrzuci³ twoj¹ proœbê o teleport.", playerNick(playerid));

	return 1;
}
Dialog:DIALOG_STYLE_WALKI(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		switch(listitem)
		{
			case 0:
			{
				SetPlayerFightingStyle(playerid, FIGHT_STYLE_NORMAL);
				SendClientMessage(playerid, COLOR_GREEN, ""chat" Ustawi³eœ styl walki {b}Normalny");
			}
			case 1:
			{
				SetPlayerFightingStyle(playerid, FIGHT_STYLE_KUNGFU);
				SendClientMessage(playerid, COLOR_GREEN, ""chat" Ustawi³eœ styl walki {b}KungFu");
			}
			case 2:{
				SetPlayerFightingStyle(playerid, FIGHT_STYLE_BOXING);
				SendClientMessage(playerid, COLOR_GREEN, ""chat" Ustawi³eœ styl walki {b}Boks");
			}
			case 3:{
				SetPlayerFightingStyle(playerid, FIGHT_STYLE_KNEEHEAD);
				SendClientMessage(playerid, COLOR_GREEN, ""chat" Ustawi³eœ styl walki {b}KneeHead");
			}
			case 4:{
				SetPlayerFightingStyle(playerid, FIGHT_STYLE_GRABKICK);
				SendClientMessage(playerid, COLOR_GREEN, ""chat" Ustawi³eœ styl walki {b}GrabKick");
			}
			case 5:{
				SetPlayerFightingStyle(playerid, FIGHT_STYLE_ELBOW);
				SendClientMessage(playerid, COLOR_GREEN, ""chat" Ustawi³eœ styl walki {b}ElBow");
			}
		}
	}
}
 
Dialog:ToHelp(playerid, response, listitem, inputtext[])
{
	if(!response) Gui_ShowPlayersHelp(playerid);
	
	return 1;
}
Dialog:CommandsList(playerid, response, listitem, inputtext[])
{
	if(!response) Gui_ShowPlayersCommandsMenu(playerid);
	else RunComment(playerid, inputtext);
	return 1;
}
Dialog:CommandsMenu(playerid, response, listitem, inputtext[])
{
        if (response)
        {
			static command_show[1500];
			command_show[0] = EOS;
			#define cmd_splitf(%0,%1); strcat(command_show, "» "%0" \t\t "%1"\n");
			switch(listitem)
			{
				case 0:
				{
					command_show[0] = EOS;
 					 
					cmd_splitf("/Register", "Rejestrujesz swoje konto na serverze");
					cmd_splitf("/Konto", "Zarz¹dzasz swoim kontem.");
					cmd_splitf("/Teles", "Sprawdzasz listê dostêpnych teleportów na serwerze");
					cmd_splitf("/Osiagniecia", "Sprawdzasz swoje osi¹gniêcia");
					cmd_splitf("/Ach", "Sprawdzasz informacje o wybranym osi¹gniêciu");
					cmd_splitf("/Portfel", "Zarz¹dzasz p³atnymi us³ugami");
					cmd_splitf("/Car", "Spawnujesz wybrany pojazd za 10.000$");
					cmd_splitf("/MyCar", "Przywo³ujesz stworzony pojazd za 500$");
					cmd_splitf("/Ramp", "Zmieniasz typ rampy lub j¹ wy³¹czasz.");
					cmd_splitf("/100hp", "Uleczasz siê za 5.000$");
					cmd_splitf("/Armor", "Uzupe³niasz kamizelkê za 5.000$");
					cmd_splitf("/Dzien", "Zmieniasz godzinê na dzieñ");
					cmd_splitf("/Noc", "Zmieniasz godzinê na noc");
					cmd_splitf("/Kill", "Pope³niasz samobójstwo.");
					cmd_splitf("/L", "Piszesz w promieniu 50 metrów.");
					cmd_splitf("/Czysc", "Czyœcisz sobie chat.");
					cmd_splitf("/Settp", "W³¹czasz / wy³¹czasz mo¿liwoœæ teleportowania siê do Ciebie");
					cmd_splitf("/Setpm", "W³¹czasz / wy³¹czasz mo¿liwoœæ pisania prywatnych wiadomoœci do Ciebie");
					cmd_splitf("/PM", "Piszesz prywatn¹ wiadomoœæ");
					cmd_splitf("/Stylwalki", "Ustawiasz swój styl walki");
					cmd_splitf("/Anims", "Wyœwietlasz listê animacji na serverze");
					cmd_splitf("/Flo (i /rsp) ", "Respawnujesz siê...");
		 			cmd_splitf("/kolor ", "Zmieñ swój kolor nicku");
					cmd_splitf("/setobject", "W³¹czasz/Wy³¹czasz obiekty na serwerze");
					Dialog_Show(playerid, CommandsList, DIALOG_STYLE_LIST, "• Help » commands » main •", command_show, "Wybierz", "Wróæ");
				}
				case 1:
				{
					command_show[0] = EOS;
					
					cmd_splitf("/Labirynt ", "Do³¹czasz do labiryntu");
					cmd_splitf("/LabiryntExit ", "Opuszczasz labirynt");
					cmd_splitf("/Tak ", "Oddajesz g³os na TAK w g³osowaniu.");
					cmd_splitf("/Nie", "Oddajesz g³os na NIE w g³osowaniu.");
					cmd_splitf("/Neon", "Dodajesz neon do swojego samochodu");
					cmd_splitf("/Pogoda", "Ustawiasz sobie pogodê.");
					cmd_splitf("/Czas", "Ustawiasz sobie czas.");
					cmd_splitf("/Dodatki", "Nak³adasz na siebie ró¿ne dodatki");
					cmd_splitf("/Modernizacja", "Zarz¹dzasz pojazdem");
					cmd_splitf("/Tunemenu", "Otwierasz menu tuningu");
					cmd_splitf("/Wyrzuc", "Wyrzucasz wszystkich z swojego pojazdu");
					cmd_splitf("/Savepos", "Zapisujesz pozycjê do której ka¿dy mo¿e siê teleportowaæ");
					cmd_splitf("/Telpos", "Teleportujesz siê do zapisanej pozycji");
					cmd_splitf("/Vc", "Zmieniasz kolor swojego samochodu");
					cmd_splitf("/Sp & /Lp", "Zapisujesz / wczytujesz swoj¹ zapisan¹ pozycjê.");
					cmd_splitf("/Skok", "Wykonujesz skok z spadochronu.");
					cmd_splitf("/Dystans", "Sprawdzasz swój dystans do gracza.");
					cmd_splitf("/Idzdo", "Teleportujesz siê do danego gracza.");
					cmd_splitf("/Lock & /Unlock", "Zamykasz / otwierasz swój pojazd.");
					cmd_splitf("/Tune", "Tuningujesz swój samochód");
					cmd_splitf("/Cardive", "Wykonujesz cardive");
					cmd_splitf("/Napraw", "Naprawiasz swój pojazd");
					cmd_splitf("/Flip", "Postawiasz swój pojazd na kó³ka");
					cmd_splitf("/Bounty", "Sprawdzasz nagrodê za zabicie gracza");
					cmd_splitf("/Hitman", "Wystawiasz nagrodê za zabicie gracza");
					cmd_splitf("/C4", "Podk³adasz bombê");
					
					Dialog_Show(playerid, CommandsList, DIALOG_STYLE_MSGBOX, "• Help » commands » additional •", command_show, "Wybierz", "Wróæ");
				}
				case 2:
				{
					command_show[0] = EOS;
					cmd_splitf("/vpozostalo", "wyœwietla date wygaœniêcia twojego konta Vip.");//
					cmd_splitf("/vjetpack", "dajesz sobie jetpacka.");//
					cmd_splitf("/vheal", "uleczasz siê za darmo.");//
					cmd_splitf("/varmor", "dostajesz kamizelkê za darmo.");//
					cmd_splitf("/vsay <tekst>", "piszesz na czacie jako Vip.");//
					cmd_splitf("/vrepair <id gracza>", "naprawiasz graczowi pojazd.");//
					cmd_splitf("/vdotacja", "dostajesz doracjê.");//
					cmd_splitf("/vinvisible", "niewidzialnoœæ na mapie");//
					cmd_splitf("/vcolor", "ustawnianie ¿ó³tego koloru nicku.");//
					cmd_splitf("/vzestaw", "otrzymujesz zestaw broni Vipa.");
					cmd_splitf("/vbank", "otwierasz dialog banku.");
					cmd_splitf("/vogl", "piszesz na chacie og³szenie");
					Dialog_Show(playerid, CommandsList, DIALOG_STYLE_MSGBOX, "• Help » commands » vip •", command_show, "Wybierz", "Wróæ");
				}
				case 3:
				{
					RankAdmin(playerid, R_MODERATOR);
					cmd_splitf("/Mute", "(Moderator): Uciszasz gracza");
					cmd_splitf("/UnMute", "(Moderator): Od ciszasz gracza");
					cmd_splitf("/Crate", "(Moderator): Kratkujesz gracza");
					cmd_splitf("/UnCrate", "(Moderator): Odkratkujesz gracza");
					cmd_splitf("/Jail", "(Moderator): Wsadzasz gracza do wiê¿enia");
					cmd_splitf("/Unjail", "(Moderator): Wypuszczasz gracza z wiê¿enia");
					cmd_splitf("/Freeze", "(Moderator): Zamra¿asz gracza");
					cmd_splitf("/Unfrezze", "(Moderator): Odmra¿asz gracza");
					cmd_splitf("/ID", "(Moderator): Szukasz gracza po czêœci nicku");
					cmd_splitf("/Ann", "(Moderator): Piszesz tekst na œrodku ekranu");
					cmd_splitf("/Prezent", "(Moderator): Postawiasz Prezent");
					cmd_splitf("/Zauto", "(Moderator): Gubisz auto");
 					cmd_splitf("/De", "(Moderator): Dajesz wszystkim: DE");  
					cmd_splitf("/bonus50", "(Moderator): Dajesz bonus graczom w pobli¿u 50.0m.");  
					Dialog_Show(playerid, CommandsList, DIALOG_STYLE_MSGBOX, "• Help » commands » mod •", command_show, "Wybierz", "Wróæ");
				}
				case 4:
				{
					RankAdmin(playerid, R_JADMIN);
					cmd_splitf("Komendy", "Junior administratora");
					cmd_splitf("Komendy", "Administratora");
					cmd_splitf("Komendy", "Head administratora");
					Dialog_Show(playerid, AdminCommands, DIALOG_STYLE_LIST, "• Help » commands » admin •", command_show, "Wybierz", "Wróæ");
				}
			}
        }
		else 
		{
			Gui_ShowPlayersHelp(playerid);
		}
        return 1;
}

Dialog:AdminCommands(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		static command_show[1024];
		command_show[0] = EOS;
		switch(listitem)
		{
			
			case 0:
			{
				RankAdmin(playerid, R_JADMIN);
				command_show[0] = EOS;
				cmd_splitf("/Ban", "(J-Admin): Banujesz podanego Gracza");
				cmd_splitf("/Kick", "(J-Admin): Wyrzucasz podanego Gracza ");
				cmd_splitf("/Explode", "(J-Admin): Wysadzasz podanego Gracza ");
				cmd_splitf("/Spec", "(J-Admin): Obserwujesz gracza");
				cmd_splitf("/Specoff", "(J-Admin): Przestajesz obserwowaæ gracza");
				cmd_splitf("/Lastreports", "(J-Admin): Sprawdzasz ostatnie raporty");
				cmd_splitf("/R", "(J-Admin): Piszesz na ekranie kolorem czerwonym");
				cmd_splitf("/Killp", "(J-Admin): Zabijasz podanego gracza");
				cmd_splitf("/Warn", "(J-Admin): dajesz Graczowi ostrze¿enie.");
				cmd_splitf("/Tp", "(J-Admin): Teleportujesz siê do gracza");
				cmd_splitf("/Settime", "(J-Admin): Zmieniasz Godzinê na serwerze");
				cmd_splitf("/Acolor", "(J-Admin): Zmieniasz Graczowi kolor");
				cmd_splitf("/Cz", "(J-Admin): Czyœcisz chat");
				cmd_splitf("/TT", "(J-Admin): Teleportujesz siê do danego gracza");
				cmd_splitf("/TH", "(J-Admin): Teleportujesz danego Gracza do Siebie");
				cmd_splitf("/ArmorAll", "(J-Admin): Dajesz ka¿demu armor");
				cmd_splitf("/HealAll", "(J-Admin): Dajesz ka¿demu full HP");
				cmd_splitf("/SetWorld", "(J-Admin): Zmieniasz Graczowi Virtual-Word");
				//cmd_splitf("/Walizka", "(J-Admin): Tworzysz Walizkê");
				cmd_splitf("/Delauta", "(J-Admin): Usuwasz wszystkie stworzone pojazdy");
				cmd_splitf("/Remove", "(J-Admin): Wyrzucasz gracza z pojazdu");
				cmd_splitf("/Rspauta", "(J-Admin): Represjonujesz pojazdy");
				cmd_splitf("/Glosowanie", "(J-Admin) Odpalasz G³osowanie");
				cmd_splitf("/Weather", "(J-Admin): Zmieniasz pogodê na serwerze.");
				cmd_splitf("/DelTrailers", "(J-Admin): usuwasz wszystkie stworzone naczepy");
				Dialog_Show(playerid, CommandsList, DIALOG_STYLE_MSGBOX, "• Help » commands » 1 •", command_show, "Wybierz", "Wróæ");
			}
			case 1:
			{
				RankAdmin(playerid, R_ADMIN);
				cmd_splitf("/Tpto", "(Admin): Teleportujesz siê do lokalizacji");
				cmd_splitf("/Disarm", "(Admin): Rozbrajasz Gracza");
				cmd_splitf("/Ajetpack", "(Admin): Dajesz Graczowi Jet-Pack");
				cmd_splitf("/ArmourGod", "(Admin): Dajesz graczowi Goda na kamizelka");
				cmd_splitf("/God", "(Admin): Dajesz graczowi Goda");
				cmd_splitf("/Granaty", "(Admin): Dajesz wszystkim: granaty");
				cmd_splitf("/Combat", "(Admin): Dajesz wszystkim: combata");
				cmd_splitf("/Tec", "(Admin): Dajesz wszystkim: tec");
				cmd_splitf("/Sniper", "(Admin): Dajesz wszystkim: sniperke");
				cmd_splitf("/Am4", "(Admin): Dajesz wszystkim: M4");
				cmd_splitf("/Shotgun", "(Admin): Dajesz wszystkim: shotgun");
				cmd_splitf("/So", "(Admin): Dajesz wszystkim: SO");
				cmd_splitf("/M5", "(Admin): Dajesz wszystkim: M5");
				cmd_splitf("/Armord", "(Admin): Dajesz Armor na dystans");
				cmd_splitf("/Heald", "(Admin): Dajesz HP na dystans");
				cmd_splitf("/Rozd", "(Admin): Rozbrajasz w dystansie");
				cmd_splitf("/Vehgod", "(Admin): Dajesz Goda na pojazd");
				cmd_splitf("/Da50", "(Admin): Rozbrajasz w promieniu 50 metrów"); //
				cmd_splitf("/Destroy", "(Admin): Usuwasz pojazd w którym aktualnie jesteœ."); //
				cmd_splitf("/DajDj", "(Admin): Dajesz / zabierasz graczu DJ'a."); //
				Dialog_Show(playerid, CommandsList, DIALOG_STYLE_MSGBOX, "• Help » commands » 2 •", command_show, "Wybierz", "Wróæ");
			}
			case 2:
			{
				RankAdmin(playerid, R_HEADADMIN);
				cmd_splitf("/GiveExp", "((Vice) Head admin): Dajesz graczowi Exp");
				cmd_splitf("/GiveExpAll", "((Vice) Head admin): Dajesz wszystkim Exp");
				cmd_splitf("/CBank", "((Vice) Head admin): Tworzysz nowy bankomat");
				cmd_splitf("/Ctele", "(Vice Head admin): Tworzysz nowy Teleport");
			//	cmd_splitf("/Arena_Derby", "((Vice) Head admin): Tworzysz now¹ arene na /DD");
			//	cmd_splitf("/Arena_WC", "((Vice) Head admin): Tworzysz now¹ arene na /WC");
			//	cmd_splitf("/Arena_Wg", "((Vice) Head admin): Tworzysz now¹ arene na /WG");
			//	cmd_splitf("/Arena_Ch", "((Vice) Head admin): Tworzysz now¹ arene na /CH");
			//	cmd_splitf("/zarzadzaj_ev", "((Vice) Head admin/3): Zarz¹dzasz wszystkimi eventami ");
				cmd_splitf("/CFigure", "(Vice Head admin): Tworzysz now¹ figurke ");
				cmd_splitf("/acheats", "(Vice Head admin): Uruchamiasz legalne cheaty ");
				cmd_splitf("/NH", "(Vice Head admin): Tworzysz nowy Dom");
				cmd_splitf("/NowyDomInt", "(Head admin): Tworzysz nowy Interior domu.");
				//cmd_splitf("/MakeVip", "((Vice) Head admin): Dajesz graczowi VIP (do wylogowania).");
				//cmd_splitf("/TakeVip", "((Vice) Head admin): Zabierasz graczowi VIP ");
				cmd_splitf("/Make", "((Vice) Head admin): Zarz¹dzasz rang¹ wybranego gracza. (dajesz/zabierasz moda, admina) ");
				Dialog_Show(playerid, CommandsList, DIALOG_STYLE_MSGBOX, "• Help » commands » 3 •", command_show, "Wybierz", "Wróæ");
			}
			
		}
	}
	return 1;
}
//attaches, modernizacja, tunemenu
 
Dialog:DIALOG_ACOLOR(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		printf("colored %d %d", playerid, listitem);
		SetPlayerColor(pInfo[playerid][player_acolor], GangColors[listitem]);
		pInfo[pInfo[playerid][player_acolor]][player_color] = GangColors[listitem];
	
		UpdatePlayerNick(pInfo[playerid][player_acolor]);
		
		if(pInfo[playerid][player_acolor] != playerid)
		{
			SendClientMessage(playerid, COLOR_ERROR, "Zmieni³eœ kolor graczu %s (%d)", playerNick(pInfo[playerid][player_acolor]), pInfo[playerid][player_acolor]);
			SendClientMessage(pInfo[playerid][player_acolor], COLOR_ERROR, " %s (%d) zmieni³ Ci kolor nicku", playerNick(playerid), playerid);
		}
	}

	ShowImportantMessage(playerid);
	pInfo[playerid][player_1spawn] = 1;
}

Dialog:D_A_I_SELECTIONVEH(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(IsPlayerEventItp(playerid))
		{
			InfoBox(playerid, "Nie mo¿esz teraz tego zrobiæ.");
			return 1;
		}
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		{
			SendClientMessage(playerid, COLOR_ERROR, " Musisz byæ w pojeŸdzie aby u¿yæ tej komendy.");
			return 1;
		}
		if(player_vehicle_object[playerid][listitem])
		{
			Dialog_Show(playerid, D_A_EDITREPLACEVEH, DIALOG_STYLE_MSGBOX, "Modyfikacja Dodatku ", "Co chcesz zrobiæ z tym dodatkiem?", "Zmieñ", "Usuñ");
		}
		else
		{
			static string3[2000+1];
			string3[0] = EOS;
			for(new x;x<sizeof(AttachmentVehObjects);x++)
			{
				format(string3, sizeof(string3), "%s%s\n", string3, AttachmentVehObjects[x][vattachname]);
			}
			Dialog_Show(playerid, D_A_MODEL_SELECTIONVEH, DIALOG_STYLE_LIST, "{FF0000}Wybieranie dodatku", string3, "Wybierz", "Anuluj");
		}
		SetPVarInt(playerid, "VehAttachmentIndexSel", listitem);
	}
	return 1;
}
Dialog:D_A_MODEL_SELECTIONVEH(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		{
			SendClientMessage(playerid, COLOR_ERROR, " Musisz byæ w pojeŸdzie aby u¿yæ tej komendy.");
			return 1;
		}
		if(player_vehicle_object[playerid][GetPVarInt(playerid, "VehAttachmentIndexSel")])
		{
			DestroyDynamicObject(player_vehicle_object[playerid][GetPVarInt(playerid, "VehAttachmentIndexSel")]);
			player_vehicle_object[playerid][GetPVarInt(playerid, "VehAttachmentIndexSel")] = 0;
		}
		
		new Float:x, Float:z, Float:y;
		GetPlayerPos(playerid, x, y, z);

		player_vehicle_object[playerid][GetPVarInt(playerid, "VehAttachmentIndexSel")] = CreateDynamicObject(AttachmentVehObjects[listitem][vattachmodel], x, y, z, 0.0, 0.0, 0.0, -1, -1, -1, 200.0);
		EditDynamicObject(playerid, player_vehicle_object[playerid][GetPVarInt(playerid, "VehAttachmentIndexSel")]);
	}
	return 1;
}
Dialog:D_A_EDITREPLACEVEH(playerid, response, listitem, inputtext[])
{
	DestroyDynamicObject(player_vehicle_object[playerid][GetPVarInt(playerid, "VehAttachmentIndexSel")]);
	player_vehicle_object[playerid][GetPVarInt(playerid, "VehAttachmentIndexSel")] = 0;
	
	if(response) DialogFunc:D_A_I_SELECTIONVEH(playerid, 1, GetPVarInt(playerid, "VehAttachmentIndexSel"), "");
	else SendClientMessage(playerid, COLOR_GREEN, ""chat" Usun¹³eœ obiekt przyczepiony do pojazdu!");
 	return 1;
}
Dialog:D_A_I_SELECTION(playerid, response, listitem, inputtext[])
{
	if(response)
	{
	
		if(IsPlayerAttachedObjectSlotUsed(playerid, listitem))
		{
			Dialog_Show(playerid, D_A_EDITREPLACE, DIALOG_STYLE_MSGBOX, "Modyfikacja Dodatki ", " Czy chcesz zmieniæ dodatek", "Tak", "Usuñ");
		}
		else
		{
			static string3[2000+1];
			string3[0] = EOS;
			for(new x;x<sizeof(AttachmentObjects);x++)
			{
				format(string3, sizeof(string3), "%s%s\n", string3, AttachmentObjects[x][attachname]);
			}
			Dialog_Show(playerid, D_A_MODEL_SELECTION, DIALOG_STYLE_LIST, "{FF0000}Wybieranie dodatku", string3, "Wybierz", "Anuluj");
		}
		SetPVarInt(playerid, "AttachmentIndexSel", listitem);
	}
	return 1;
}
Dialog:D_A_EDITREPLACE(playerid, response, listitem, inputtext[])
{
	if(response) EditAttachedObject(playerid, GetPVarInt(playerid, "AttachmentIndexSel"));
	else RemovePlayerAttachedObject(playerid, GetPVarInt(playerid, "AttachmentIndexSel"));
	DeletePVar(playerid, "AttachmentIndexSel");
	return 1;
}
Dialog:D_A_MODEL_SELECTION(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(GetPVarInt(playerid, "AttachmentUsed") == 1) EditAttachedObject(playerid, listitem);
		else
		{
			SetPVarInt(playerid, "AttachmentModelSel", AttachmentObjects[listitem][attachmodel]);
			new string3[256+1];
			for(new x;x<sizeof(AttachmentBones);x++)
			{
				format(string3, sizeof(string3), "%s%s\n", string3, AttachmentBones[x]);
			}
			Dialog_Show(playerid, D_A_BONE_SELECTION, DIALOG_STYLE_LIST, "{FF0000}Wybierz miejsce na którym chcesz dodaæ dodatek:", string3, "Wybierz", "Anuluj");
		}
	}
	else DeletePVar(playerid, "AttachmentIndexSel");
	return 1;
}
Dialog:D_A_BONE_SELECTION(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		SetPlayerAttachedObject(playerid, GetPVarInt(playerid, "AttachmentIndexSel"), GetPVarInt(playerid, "AttachmentModelSel"), listitem+1);
		EditAttachedObject(playerid, GetPVarInt(playerid, "AttachmentIndexSel"));
		// SendClientMessage(playerid, COLOR_GREEN, " U¿yj klawicza \"Sprint\"");
	}
	DeletePVar(playerid, "AttachmentIndexSel");
	DeletePVar(playerid, "AttachmentModelSel");
	return 1;
}

//modernizacja

 
Dialog:DIALOG_AUTO(playerid, response, listitem, inputtext[])
{	
	if(IsPlayerEventItp(playerid))
	{
		InfoBox(playerid, "Nie mo¿esz teraz tego zrobiæ.");
		return 1;
	}
	if(response)
	{
		switch(listitem)
		{
			case 0: Dialog_Show(playerid, DIALOG_SILNIK, DIALOG_STYLE_MSGBOX, "Silnik", "Wy³¹cz lub Odpal silnik:", "Odpal", "Zgaœ");
			case 1: Dialog_Show(playerid, DIALOG_SWIATLA, DIALOG_STYLE_MSGBOX, "Œwiat³a", "Wy³¹cz lub W³¹cz œwiat³a:\n\n(Œwiat³a widoczne s¹ tylko w nocy)", "W³¹cz", "Wy³¹cz");
			case 2: Dialog_Show(playerid, DIALOG_m_alarm, DIALOG_STYLE_MSGBOX, "alarm", "Wy³¹cz lub w³¹cz auto alarm:", "W³¹cz", "Wy³¹cz");
			case 3: Dialog_Show(playerid, DIALOG_DRZWI, DIALOG_STYLE_MSGBOX, "Drzwi", "Zamknij lub otwórz drzwi pojazdu:", "Otwórz", "Zamknij");
			case 4: Dialog_Show(playerid, DIALOG_BAGAZNIK, DIALOG_STYLE_MSGBOX, "Maska", "Otwórz lub zamknij maskê.", "Otwórz", "Zamknij");
			case 5: Dialog_Show(playerid, DIALOG_MASKA, DIALOG_STYLE_MSGBOX, "Baga¿nik", "Otwórz lub zamknij baka¿nik", "Otwórz", "Zamknij");
			case 6: Dialog_Show(playerid, DIALOG_TABLICA_TEXT, DIALOG_STYLE_INPUT, "Numery pojazdu", "Wpisz treœæ tablicy rejestracyjnej", "Zmieñ", "Cofnij");
		}
	}
	return 1;
}

Dialog:DIALOG_SILNIK(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Silnik pojazdu {b}uruchomiony{/b}.");
		GetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, m_elights, m_alarm, m_doors, m_bonnet, m_boot, m_objective);
		SetVehicleParamsEx(GetPlayerVehicleID(playerid), 1, m_elights, m_alarm, m_doors, m_bonnet, m_boot, m_objective);
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Silnik pojazdu {b}zgaszony{/b}.");
		GetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, m_elights, m_alarm, m_doors, m_bonnet, m_boot, m_objective);
		SetVehicleParamsEx(GetPlayerVehicleID(playerid), 0, m_elights, m_alarm, m_doors, m_bonnet, m_boot, m_objective);
	}
	
	Dialog_Show(playerid, DIALOG_AUTO, DIALOG_STYLE_LIST, "Modernizacja pojazdu", "Silnik\nŒwiat³a\nalarm\nDrzwi\nBaga¿nik\nMaska\nTablica Rejestracyjna", "Wybierz", "Zamknij");
}

Dialog:DIALOG_SWIATLA(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Œwiat³a pojazdu zosta³y {b}w³¹czone{/b}.");
		GetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, m_elights, m_alarm, m_doors, m_bonnet, m_boot, m_objective);
		SetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, 1, m_alarm, m_doors, m_bonnet, m_boot, m_objective);
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Œwiat³a pojazdu zosta³y {b}wy³¹czone{/b}.");
		GetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, m_elights, m_alarm, m_doors, m_bonnet, m_boot, m_objective);
		SetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, 0, m_alarm, m_doors, m_bonnet, m_boot, m_objective);
	}
	
	Dialog_Show(playerid, DIALOG_AUTO, DIALOG_STYLE_LIST, "Modernizacja pojazdu", "Silnik\nŒwiat³a\nalarm\nDrzwi\nBaga¿nik\nMaska\nTablica Rejestracyjna", "Wybierz", "Zamknij");
}

Dialog:DIALOG_m_alarm(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Auto alarm zosta³ {b}w³¹czony{/b}.");
		GetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, m_elights, m_alarm, m_doors, m_bonnet, m_boot, m_objective);
		SetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, m_elights, 1, m_doors, m_bonnet, m_boot, m_objective);
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Auto alarm zosta³ {b}wy³¹czony{/b}.");
		GetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, m_elights, m_alarm, m_doors, m_bonnet, m_boot, m_objective);
		SetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, m_elights, 0, m_doors, m_bonnet, m_boot, m_objective);
	}
	
	Dialog_Show(playerid, DIALOG_AUTO, DIALOG_STYLE_LIST, "Modernizacja pojazdu", "Silnik\nŒwiat³a\nalarm\nDrzwi\nBaga¿nik\nMaska\nTablica Rejestracyjna", "Wybierz", "Zamknij");
}

Dialog:DIALOG_BAGAZNIK(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Baga¿nik {b}otworzony{/b}.  ");
		GetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, m_elights, m_alarm, m_doors, m_bonnet, m_boot, m_objective);
		SetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, m_elights, m_alarm, m_doors, m_bonnet, 1, m_objective);
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Baga¿nik {b}zamkniêty{/b}. ");
		GetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, m_elights, m_alarm, m_doors, m_bonnet, m_boot, m_objective);
		SetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, m_elights, m_alarm, m_doors, m_bonnet, 0, m_objective);
	}
	
	Dialog_Show(playerid, DIALOG_AUTO, DIALOG_STYLE_LIST, "Modernizacja pojazdu", "Silnik\nŒwiat³a\nalarm\nDrzwi\nBaga¿nik\nMaska\nTablica Rejestracyjna", "Wybierz", "Zamknij");
}

Dialog:DIALOG_MASKA(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Maska {b}otworzona{/b}.");
		GetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, m_elights, m_alarm, m_doors, m_bonnet, m_boot, m_objective);
		SetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, m_elights, m_alarm, m_doors, 1, m_boot, m_objective);
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Maska {b}zamkniêta{/b}.");
		GetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, m_elights, m_alarm, m_doors, m_bonnet, m_boot, m_objective);
		SetVehicleParamsEx(GetPlayerVehicleID(playerid), m_engine, m_elights, m_alarm, m_doors, 0, m_boot, m_objective);
	}
	
	Dialog_Show(playerid, DIALOG_AUTO, DIALOG_STYLE_LIST, "Modernizacja pojazdu", "Silnik\nŒwiat³a\nalarm\nDrzwi\nBaga¿nik\nMaska\nTablica Rejestracyjna", "Wybierz", "Zamknij");
}

Dialog:DIALOG_DRZWI(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Drzwi pojazdu otworzone.");
		
		new veh = GetPlayerVehicleID(playerid);
		for(new i=0;i<MAX_PLAYERS;i++)
		{
			if(i != playerid)
			{
				SetVehicleParamsForPlayer(veh, i, 0, 0);
 			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Drzwi pojazdu zamkniête.");
		
		new veh = GetPlayerVehicleID(playerid);
		for(new i=0;i<MAX_PLAYERS;i++)
		{
			if(i != playerid)
			{
				SetVehicleParamsForPlayer(veh, i, 0, 1);
 			}
		}
		
	}
	
	Dialog_Show(playerid, DIALOG_AUTO, DIALOG_STYLE_LIST, "Modernizacja pojazdu", "Silnik\nŒwiat³a\nAlarm\nDrzwi\nBaga¿nik\nMaska\nTablica Rejestracyjna", "Wybierz", "Zamknij");
}

Dialog:DIALOG_TABLICA_TEXT(playerid, response, listitem, inputtext[])
{
	if(strlen(inputtext) < 1 || strlen(inputtext) > 8) return SendClientMessage(playerid, COLOR_GREEN, ""chat" Niepoprawna d³ugoœæ tekstu! {b}Od 1 do 8 znaków.");
	
	new Float:X, Float:Y, Float:Z, Float:angle;
	if(response)
	{
		SendClientMessage(playerid, COLOR_GOLD, ""chat" Numery pojazdu zmienione.");
		GetPlayerPos(playerid, X, Y, Z);
		GetPlayerFacingAngle(playerid, angle);
		SetVehicleNumberPlate(GetPlayerVehicleID(playerid), inputtext);
		SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		SetVehicleZAngle(GetPlayerVehicleID(playerid), angle);
		PutPlayerInVehicle(playerid, GetPlayerVehicleID(playerid), 0);
		SetVehiclePos(GetPlayerVehicleID(playerid), X, Y, Z+2);
	}
	else
	{
		Dialog_Show(playerid, DIALOG_AUTO, DIALOG_STYLE_LIST, "Modernizacja pojazdu", "Silnik\nŒwiat³a\nalarm\nDrzwi\nBaga¿nik\nMaska\nTablica Rejestracyjna", "Wybierz", "Zamknij");
	}
	
	return 1;
}

 
Dialog:DIALOG_TUNEMENU(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(IsPlayerEventItp(playerid))
		{
			InfoBox(playerid, "Nie mo¿esz teraz tego zrobiæ.");
			return 1;
		}
		
		new vehicleid = GetPlayerVehicleID(playerid);
		switch(listitem)
		{
			case 0: Dialog_Show(playerid, DIALOG_TUNEMENU_FELGI, DIALOG_STYLE_LIST, "Felgi", "Switch\nMega\nCutter\nOffroad\nShadow\nRimshine\nWires\nClassic\nTwist\nGrove\nImport\nDollar\nTrance\nAtomic\nAhab\nVirtual\nAccess\n", "Wybierz", "Cofnij");
			case 1: Dialog_Show(playerid, DIALOG_TUNEMENU_KOLORY, DIALOG_STYLE_LIST, "Tuning Menu » Kolory", "Czarny\nBialy\nSzary\nZolty\nNiebieski\nBlekitny\nGranatowy\nFiloetowy\nCzerwony\nJasny Czerwony\nZielony\nRozowy", "Wybierz", "Cofnij");
			case 2:
			{
				SendClientMessage(playerid, COLOR_GREEN, " {b}Hydraulika{/b} zosta³a zamontowana");
				PlayerPlaySound(playerid, 1133, 0, 0, 0);
				AddVehicleComponent(vehicleid, 1087);
				Dialog_Show(playerid, DIALOG_TUNEMENU, DIALOG_STYLE_LIST, "Tuning Menu", "Felgi\nKolory\nHydraulika\nNitro\nStereo\nPaint Job", "Wybierz", "Zamknij");
			}
			case 3:
			{
				SendClientMessage(playerid, COLOR_GREEN, " {b}Nitro{/b} zosta³o zamontowane");
				PlayerPlaySound(playerid, 1133, 0, 0, 0);
				AddVehicleComponent(vehicleid, 1010);
				Dialog_Show(playerid, DIALOG_TUNEMENU, DIALOG_STYLE_LIST, "Tuning Menu", "Felgi\nKolory\nHydraulika\nNitro\nStereo\nPaint Job", "Wybierz", "Zamknij");
			}
			case 4:
			{
				SendClientMessage(playerid, COLOR_GREEN, " {b}Stereo{/b} zosta³o zamontowane");
				PlayerPlaySound(playerid, 1133, 0, 0, 0);
				AddVehicleComponent(vehicleid, 1086);
				Dialog_Show(playerid, DIALOG_TUNEMENU, DIALOG_STYLE_LIST, "Tuning Menu", "Felgi\nKolory\nHydraulika\nNitro\nStereo\nPaint Job", "Wybierz", "Zamknij");
			}
			case 5: Dialog_Show(playerid, DIALOG_TM_PAINTJOB, DIALOG_STYLE_LIST, "Tuning Menu » Paint Job", "Paint Job 1\nPaint Job 2\nPaint Job 3\nUsun Paint Job'a", "Wybierz", "Cofnij");
			case 6:
			{
				if(!IsVehicleDoczepianeObiekty(vehicleid))
				{
					InfoBox(playerid, "{FFFF00}Niestety do tego pojazdu nie ma doczepianych obiektów!\n\n{FFFFFF}Doczepiane obiekty dostêpne w:\n:{0080FF}NRG-500, ELEGY, INFERNUS, PATRIOT, VORTEX, SULTAN, EUROS, TURISMO, VINCENT, BURITTO, TAMPA, SLAMVAN, BUS");
					return 1;
				}
				
				SendClientMessage(playerid, 0x00CDFFFF, "[DOCZEPIANE OBIEKTY] {00FF89}Obiekty zosta³y {F7FF00}doczepione!");
				DoczepianeObiekty(vehicleid);
			}
		}
	}
	return 1;
}
Dialog:DIALOG_TUNEMENU_FELGI(playerid, response, listitem, inputtext[])
{
	if(response == 1)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		PlayerPlaySound(playerid, 1133, 0, 0, 0);
		switch(listitem)
		{
			case 0: AddVehicleComponent(vehicleid, 1080); //Switch
			case 1: AddVehicleComponent(vehicleid, 1074); //Mega
			case 2: AddVehicleComponent(vehicleid, 1079); //Cutter
			case 3: AddVehicleComponent(vehicleid, 1025); //Offroad
			case 4: AddVehicleComponent(vehicleid, 1073); //Shadow
			case 5: AddVehicleComponent(vehicleid, 1075); //Rimshine
			case 6: AddVehicleComponent(vehicleid, 1076); //Wires
			case 7: AddVehicleComponent(vehicleid, 1077); //Classic
			case 8: AddVehicleComponent(vehicleid, 1078); //Twist
			case 9: AddVehicleComponent(vehicleid, 1081); //Grove
			case 10: AddVehicleComponent(vehicleid, 1082); //Import
			case 11: AddVehicleComponent(vehicleid, 1083); //Dollar
			case 12: AddVehicleComponent(vehicleid, 1084); //Trance
			case 13: AddVehicleComponent(vehicleid, 1085); //Atomic
			case 14: AddVehicleComponent(vehicleid, 1096); //Ahab
			case 15: AddVehicleComponent(vehicleid, 1097); //Virtual
			case 16: AddVehicleComponent(vehicleid, 1098); //Access
		}
		SendClientMessage(playerid, COLOR_GREEN, " {b}Felgi{/b} zosta³y zmienione");
		Dialog_Show(playerid, DIALOG_TUNEMENU_FELGI, DIALOG_STYLE_LIST, "Felgi", "Switch\nMega\nCutter\nOffroad\nShadow\nRimshine\nWires\nClassic\nTwist\nGrove\nImport\nDollar\nTrance\nAtomic\nAhab\nVirtual\nAccess\n", "Wybierz", "Cofnij");
		}else{
		Dialog_Show(playerid, DIALOG_TUNEMENU, DIALOG_STYLE_LIST, "Tuning Menu", "Felgi\nKolory\nHydraulika\nNitro\nStereo\nPaint Job", "Wybierz", "Zamknij");
	}
	return 1;
}
Dialog:DIALOG_TUNEMENU_KOLORY(playerid, response, listitem, inputtext[])
{
	if(response == 1)
	{
		PlayerPlaySound(playerid, 1134, 0, 0, 0);
		new vehicleid = GetPlayerVehicleID(playerid);
		switch(listitem)
		{
			case 0: ChangeVehicleColor(vehicleid, 0, 0);
			case 1: ChangeVehicleColor(vehicleid, 1, 1);
			case 2: ChangeVehicleColor(vehicleid, 33, 33);
			case 3: ChangeVehicleColor(vehicleid, 6, 6);
			case 4: ChangeVehicleColor(vehicleid, 108, 108);
			case 5: ChangeVehicleColor(vehicleid, 7, 7);
			case 6: ChangeVehicleColor(vehicleid, 79, 79);
			case 7: ChangeVehicleColor(vehicleid, 405, 405);
			case 8: ChangeVehicleColor(vehicleid, 3, 3);
			case 9: ChangeVehicleColor(vehicleid, 166, 166);
			case 10:ChangeVehicleColor(vehicleid, 16, 16);
			case 11:ChangeVehicleColor(vehicleid, 146, 146);
		}
		SendClientMessage(playerid, COLOR_GREEN, " {b}Kolor{/b} pojazdu zosta³ zmieniony");
		Dialog_Show(playerid, DIALOG_TUNEMENU_KOLORY, DIALOG_STYLE_LIST, "Tuning Menu » Kolory", "Czarny\nBialy\nSzary\nZolty\nNiebieski\nBlekitny\nGranatowy\nFiloetowy\nCzerwony\nJasny Czerwony\nZielony\nRozowy", "Wybierz", "Cofnij");
		}else{
		Dialog_Show(playerid, DIALOG_TUNEMENU, DIALOG_STYLE_LIST, "Tuning Menu", "Felgi\nKolory\nHydraulika\nNitro\nStereo\nPaint Job", "Wybierz", "Zamknij");
	}
	return 1;
}
Dialog:DIALOG_TM_PAINTJOB(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		ChangeVehicleColor(vehicleid, 1, 1);
		switch(listitem)
		{
			case 0: ChangeVehiclePaintjob(vehicleid, 0);
			case 1: ChangeVehiclePaintjob(vehicleid, 1);
			case 2: ChangeVehiclePaintjob(vehicleid, 2);
			case 3: ChangeVehiclePaintjob(vehicleid, 3);
			case 4: ChangeVehiclePaintjob(vehicleid, 4);
		}
		
		Dialog_Show(playerid, DIALOG_TM_PAINTJOB, DIALOG_STYLE_LIST, "Tuning Menu » Paint Job", "Paint Job 1\nPaint Job 2\nPaint Job 3\nUsun Paint Job'a", "Wybierz", "Cofnij");
		}else{
		Dialog_Show(playerid, DIALOG_TUNEMENU, DIALOG_STYLE_LIST, "Tuning Menu", "Felgi\nKolory\nHydraulika\nNitro\nStereo\nPaint Job", "Wybierz", "Zamknij");
	}
	return 1;
}




  
Dialog:DIALOG_SELECT_NEON(playerid, response, listitem, inputtext[])
{
	if(!response || !IsPlayerInAnyVehicle(playerid)) return 1;
	
	new vid = GetPlayerVehicleID(playerid);
	DestroyNeon(vid);
	if(listitem == 12) return 1;
	
	switch(listitem)
	{
		case 0:
		{
			VehicleNeon[vid][0] = CreateDynamicObject(18648, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			VehicleNeon[vid][1] = -1;
		}
		case 1:
		{
			VehicleNeon[vid][0] = CreateDynamicObject(18647, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			VehicleNeon[vid][1] = -1;
		}
		case 2:
		{
			VehicleNeon[vid][0] = CreateDynamicObject(18649, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			VehicleNeon[vid][1] = -1;
		}
		case 3:
		{
			VehicleNeon[vid][0] = CreateDynamicObject(18652, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			VehicleNeon[vid][1] = -1;
		}
		case 4:
		{
			VehicleNeon[vid][0] = CreateDynamicObject(18651, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			VehicleNeon[vid][1] = -1;
		}
		case 5:
		{
			VehicleNeon[vid][0] = CreateDynamicObject(18650, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			VehicleNeon[vid][1] = -1;
		}
		case 6:
		{
			VehicleNeon[vid][0] = CreateDynamicObject(18648, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			VehicleNeon[vid][1] = CreateDynamicObject(18649, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		}
		case 7:
		{
			VehicleNeon[vid][0] = CreateDynamicObject(18648, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			VehicleNeon[vid][1] = CreateDynamicObject(18652, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		}
		case 8:
		{
			VehicleNeon[vid][0] = CreateDynamicObject(18647, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			VehicleNeon[vid][1] = CreateDynamicObject(18652, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		}
		case 9:
		{
			VehicleNeon[vid][0] = CreateDynamicObject(18647, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			VehicleNeon[vid][1] = CreateDynamicObject(18650, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			
		}
		case 10:
		{
			VehicleNeon[vid][0] = CreateDynamicObject(18649, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			VehicleNeon[vid][1] = CreateDynamicObject(18652, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			
		}
		case 11:
		{
			VehicleNeon[vid][0] = CreateDynamicObject(18652, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			VehicleNeon[vid][1] = CreateDynamicObject(18650, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		}
	}
	
	if(VehicleNeon[vid][1] != -1)
		AttachDynamicObjectToVehicle(VehicleNeon[vid][1], vid, 0.0, 0.0, -0.70, 0.0, 0.0, 0.0);
	
	AttachDynamicObjectToVehicle(VehicleNeon[vid][0], vid, 0.0, 0.0, -0.70, 0.0, 0.0, 0.0);
	SendClientMessage(playerid, COLOR_GOLD, ""chat" Neon zosta³ zainstalowany.");
	return 1;
}

Dialog:Dialog_Konto(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		pInfo[playerid][player_dialog_data][0] = listitem;
		switch(listitem)
		{
			case 0: 
			{
				 Dialog_Show(playerid, Dialog_KontoEdit, DIALOG_STYLE_MSGBOX, "Panel » Rampy ", "Czy chcesz mieæ w³¹czone rampy pod przyciskiem "HEX_ERROR"\"CTRL\""HEX_SAMP"?", "Tak", "Nie");
			}
			case 1: 
			{
				 Dialog_Show(playerid, Dialog_KontoEdit, DIALOG_STYLE_MSGBOX, "Panel » /Idzdo", "Czy chcesz mieæ w³¹czone proœby o teleport ("HEX_ERROR"/idzdo"HEX_SAMP")?", "Tak", "Nie");
			}
			case 2: 
			{
				 Dialog_Show(playerid, Dialog_KontoEdit, DIALOG_STYLE_MSGBOX, "Panel » Prywatne wiadomoœci", "Czy chcesz mieæ w³¹czone prywatne wiadomoœci?", "Tak", "Nie");
			}
			case 3:
			{
				 Dialog_Show(playerid, Dialog_KontoEdit, DIALOG_STYLE_PASSWORD, "Panel » Zmiana has³a", "Je¿eli chcesz zmieniæ swoje has³o podaj poni¿ej\nswoje nowe has³o:", "Dalej", "Anuluj");
			}
			case 4:
			{
				if(GetPlayerScore(playerid) < 2500)
				{
					InfoBox(playerid, "Zmiana nicku kosztuje 2500 punktów respektu");
					return 1;
				}
				if(pInfo[playerid][player_admin] || Iter_Contains(Vips, playerid)){
					new c = pInfo[playerid][player_nichchange];
					
					if(((c) - ((60*60)*60)) > (gettime()))
					{
						InfoBox(playerid, "Nick mo¿na zmieniaæ raz w ci¹gu 12 godzin.");
						return 1;
					}
				}
				else {	
					if(pInfo[playerid][player_nichchange] > gettime())
					{
						InfoBox(playerid, "Nick mo¿na zmieniaæ raz w ci¹gu 72 godzin (Dla VIP co 12 godzin).");
						return 1;
					}
				}
				format(string2, sizeof(string2), "%s, \n\nJe¿eli chcesz zmieniæ swój nick wystarczy ¿e w polu poni¿ej podasz swój nowy nick.\nPamiêtaj ¿e nick mo¿na zmieniaæ raz na "HEX_ERROR"72"HEX_SAMP" godziny ", pInfo[playerid][player_name]);
				strcat(string2, "oraz ka¿dorazowa zmiana nicku kosztuje 250 punktów respektu. \nJe¿eli chcesz kontynuowaæ zmianê nicku wpisz w polu poni¿ej swój nowy nick i klinij \"Dalej\".");
				Dialog_Show(playerid, Dialog_KontoEdit, DIALOG_STYLE_INPUT, "Panel » Zmiana nicku", string2, "Dalej", "Anuluj");
				
			}
			case 5: 
			{
				show_achievement(playerid);
			}
			case 6:
			{
				ShowPlayerStats(playerid, playerid);
			}
			case 7: 
			{
				cmd_setobject(playerid,"");
			}		
			case 8: 
			{
				cmd_setduel(playerid,"");
			}
			case 9: 
			{
				Dialog_Show(playerid, Dialog_WyborSpawnu, DIALOG_STYLE_LIST, "Panel » Zmiana spawnu", "Losowy spawn\nDom\nBaza gangu","Wybierz","Anuluj");
			}
		}
	}
	return 1;
}

Dialog:Dialog_KontoEdit(playerid, response, listitem, inputtext[])
{
	
	switch(pInfo[playerid][player_dialog_data][0])
	{
		case 0:
		{
			if(response)
			{
				pInfo[playerid][player_ramp_pers] = 0;
				InfoBox(playerid, "W³¹czy³eœ rampy pod przyciskiem "HEX_ERROR"\"CTRL\""HEX_SAMP".");
			}
			else
			{
				pInfo[playerid][player_ramp_pers] = -1;
				InfoBox(playerid, ""HEX_ERROR"Wy³¹czy³eœ "HEX_SAMP"rampy.");
			}
		}
		case 1:
		{
			if(response)
			{
				pInfo[playerid][player_teleports] = false;
				InfoBox(playerid, "W³¹czy³eœ proœby o teleport.");
			}
			else
			{
				pInfo[playerid][player_teleports] = true;
				InfoBox(playerid, ""HEX_ERROR"Wy³¹czy³eœ "HEX_SAMP"proœby o teleport.");
			}
		}
		case 2:
		{
			if(response)
			{
				pInfo[playerid][player_pm] = false;
				InfoBox(playerid, "W³¹czy³eœ prywatne wiadomoœci.");
			}
			else
			{
				pInfo[playerid][player_pm] = true;
				InfoBox(playerid, ""HEX_ERROR"Wy³¹czy³eœ "HEX_SAMP"prywatne wiadomoœci.");
			}
		}
		case 3:
		{
			if(response)
			{
				if(!pInfo[playerid][player_logged]) return 1;
				if(strlen(inputtext) > 24)
				{
					SendClientMessage(playerid, COLOR_ERROR, " Has³o mo¿e sk³adaæ siê maksymalnie z 24 znaków");
					DialogFunc:Dialog_Konto(playerid, 1, 3, "hop");
					
					return 1;
				}
				
				if(strlen(inputtext) < 4)
				{
					SendClientMessage(playerid, COLOR_ERROR, " Has³o mo¿e sk³adaæ siê minimalnie z 4 znaków");
					DialogFunc:Dialog_Konto(playerid, 1, 3, "hop");
					return 1;
				}
				if(!PasswordCorrect(inputtext))
				{
					SendClientMessage(playerid, COLOR_ERROR, " Has³o mo¿e sk³adaæ siê tylko z {b}liter{/b} i {d}liczb{/b}.");
					DialogFunc:Dialog_Konto(playerid, 1, 3, "hop");
					return 1;
				}
				
				new c = PasswordCheck(inputtext);
				
				if(c < 2)
				{
					SendClientMessage(playerid, COLOR_ERROR, " Poda³eœ zbyt s³abe has³o (si³a has³a %d/4)", c);
					DialogFunc:Dialog_Konto(playerid, 1, 3, "hop");
					return 1;
				}
				
				mysql_real_escape_string(inputtext, pInfo[playerid][player_dialog_data_ex]);
				
				format(string2, sizeof(string2), "Czy na-pewno chcesz zmieniæ has³o na %s?", pInfo[playerid][player_dialog_data_ex]);
				Dialog_Show(playerid, Dialog_KontoPass, DIALOG_STYLE_MSGBOX, "Panel » Zmiana has³a » Potwierdzenie", string2, "Tak", "Nie");
				
				
			}
		}
		
		case 4:
		{
			if(response)
			{
				if(!pInfo[playerid][player_logged]) return 1;
				if(strlen(inputtext) < 3 || strlen(inputtext) > 24)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Nick musi posiadaæ od 3 do 24 znaków.");
					DialogFunc:Dialog_Konto(playerid, 1, 4, "hop");
					
					return 1;
				}
				
				if(!ValidText(inputtext))
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Nick nie mo¿e mieæ znaków specjalnych oraz spacji. (Wyj¹tek: '[,]', '(,)', '.,_')");
					DialogFunc:Dialog_Konto(playerid, 1, 4, "hop");
					return 1;
				}
				mysql_real_escape_string(inputtext, pInfo[playerid][player_dialog_data_ex]);
				
				if(AccountExists("nick", pInfo[playerid][player_dialog_data_ex]))
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Podany Nick jest ju¿ u¿ywany przez innego gracza.");
					DialogFunc:Dialog_Konto(playerid, 1, 4, "hop");
					return 1;
				}
				
				format(string2, sizeof(string2), "Czy na-pewno chcesz zmieniæ nick z %s na %s za 1500 respektu?", pInfo[playerid][player_name], pInfo[playerid][player_dialog_data_ex]);
				Dialog_Show(playerid, Dialog_KontoNick, DIALOG_STYLE_MSGBOX, "Panel » Zmiana nicku » Potwierdzenie", string2, "Tak", "Nie");
				
			//	m_query("update "prefix"_players set nick = '%s' where id = %d", pInfo[playerid][player_name], pInfo[playerid][player_id]);
			}
		}
	}
	
	return 1;
}
Dialog:Dialog_ChangeMail(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(strlen(inputtext) > 42)
		{
			SendClientMessage(playerid, COLOR_ERROR, " E-Mail mo¿e sk³adaæ siê maksymalnie z 24 znaków");
			#define text@1 "Witaj w naszej bazie danych nie znaleziono Twojego adresu e-mail. Aby kontynuowaæ grê na naszym serwerze, musisz podaæ swój adres E-Mail\n\n"HEX_ERROR"Uwaga:"HEX_SAMP" Je¿eli jesteœ zarejestrowany, a widzisz t¹ informacje, znaczy ¿e twoje konto by³o importowane z idnych systemów rejestracji."
			Dialog_Show(playerid, Dialog_KontoEdit, DIALOG_STYLE_INPUT, "Panel » Zmiana adresu e-mail", text@1, "Dalej", "Anuluj");
			return 1;
		}
		
		if(strlen(inputtext) < 4)
		{
			SendClientMessage(playerid, COLOR_ERROR, " E-Mail mo¿e sk³adaæ siê minimalnie z 4 znaków");
			#define text@1 "Witaj w naszej bazie danych nie znaleziono Twojego adresu e-mail. Aby kontynuowaæ grê na naszym serwerze, musisz podaæ swój adres E-Mail\n\n"HEX_ERROR"Uwaga:"HEX_SAMP" Je¿eli jesteœ zarejestrowany, a widzisz t¹ informacje, znaczy ¿e twoje konto by³o importowane z idnych systemów rejestracji."
			Dialog_Show(playerid, Dialog_KontoEdit, DIALOG_STYLE_INPUT, "Panel » Zmiana adresu e-mail", text@1, "Dalej", "Anuluj");

			return 1;
		}
		for(new i, len = strlen(inputtext); i<len; i++) inputtext[i] = tolower(inputtext[i]);
		
		if(!IsValidEmailEx(inputtext))
		{
			SendClientMessage(playerid, COLOR_ERROR, " Podany E-Mail jest nie prawid³owy.");
			#define text@1 "Witaj w naszej bazie danych nie znaleziono Twojego adresu e-mail. Aby kontynuowaæ grê na naszym serwerze, musisz podaæ swój adres E-Mail\n\n"HEX_ERROR"Uwaga:"HEX_SAMP" Je¿eli jesteœ zarejestrowany, a widzisz t¹ informacje, znaczy ¿e twoje konto by³o importowane z idnych systemów rejestracji."
			Dialog_Show(playerid, Dialog_KontoEdit, DIALOG_STYLE_INPUT, "Panel » Zmiana adresu e-mail", text@1, "Dalej", "Anuluj");

			return 1;
		}
		mysql_real_escape_string(inputtext, pInfo[playerid][player_email]);
		if(AccountExists("mail", pInfo[playerid][player_email]))
		{
			SendClientMessage(playerid, COLOR_ERROR, " Podany E-Mail jest ju¿ przez kogoœ u¿ywany.");
			#define text@1 "Witaj w naszej bazie danych nie znaleziono Twojego adresu e-mail. Aby kontynuowaæ grê na naszym serwerze, musisz podaæ swój adres E-Mail\n\n"HEX_ERROR"Uwaga:"HEX_SAMP" Je¿eli jesteœ zarejestrowany, a widzisz t¹ informacje, znaczy ¿e twoje konto by³o importowane z idnych systemów rejestracji."
			Dialog_Show(playerid, Dialog_KontoEdit, DIALOG_STYLE_INPUT, "Panel » Zmiana adresu e-mail", text@1, "Dalej", "Anuluj");
			return 1;
		}
	 
		m_query("update "prefix"_players set mail = '%s' where id = %d", pInfo[playerid][player_email], pInfo[playerid][player_id]);
		
		SendPlayerMail(playerid);
		
		GivePlayerScore(playerid, 10);
		SendClientMessage(playerid, COLOR_GOLD, ""chat" Pomyœlnie ustawi³eœ(aœ) swój adres e-mail na %s.", pInfo[playerid][player_email]);
		
		
	}
	return 1;
}
Dialog:Dialog_KontoPass(playerid, response, listitem, inputtext[])
{	
	if(!pInfo[playerid][player_logged]) return;
	if(response)
	{		
		 
		mysql_real_escape_string(pInfo[playerid][player_dialog_data_ex], pInfo[playerid][player_password]);
		m_query("update "prefix"_players set password = md5(md5('%s')), upass=1 where id = %d", pInfo[playerid][player_password], pInfo[playerid][player_id]);
		
		pInfo[playerid][player_chpassword] = 1;
		
		SendClientMessage(playerid, COLOR_GOLD, ""chat" Pomyœlnie zmieni³eœ swoje has³o na %s.", pInfo[playerid][player_dialog_data_ex]);
	}
}
Dialog:DIALOG_PICKUP(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new Float:pos[3];
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		CreateDynamicPickup(pickupTemp[listitem][ID], 2, pos[0], pos[1], pos[2], 0, -1, -1, 100.0);
		m_query("insert into "prefix"_pickup (id, type, pos_x, pos_y, pos_z) VALUES (NULL, '%i', '%0.2f', '%0.2f', '%0.2f');", pickupTemp[listitem][ID], pos[0], pos[1], pos[2]);
		SendClientMessage(playerid, COLOR_GOLD, ""chat" Doda³eœ pickup: %s o id: %i", pickupTemp[listitem][Nazwa], pickupTemp[listitem][ID]);
	}
	return 1;
}
Dialog:Dialog_KontoNick(playerid, response, listitem, inputtext[])
{	
	if(response)
	{	
		if(!pInfo[playerid][player_logged]) return;
		AddPlayerLog(playerid, LOG_CHANGENAME, pInfo[playerid][player_name], pInfo[playerid][player_dialog_data_ex]);
		
		SendClientMessageToAll(COLOR_GOLD, ""chat" Gracz %s (%d) zmieni³(a) swój nick na %s.", pInfo[playerid][player_name], playerid, pInfo[playerid][player_dialog_data_ex]);
	 	mysql_real_escape_string(pInfo[playerid][player_dialog_data_ex], pInfo[playerid][player_name]);
		
		SetPlayerName(playerid, pInfo[playerid][player_name]);
		UpdatePlayerNick(playerid, true);
		
		m_query("update "prefix"_players set nick = '%s' where id = %d", pInfo[playerid][player_name], pInfo[playerid][player_id]);
		
		GivePlayerScore(playerid, -1500);//jp
		SendClientMessage(playerid, COLOR_GOLD, ""chat" Pomyœlnie zmieni³eœ swój nick na %s.", pInfo[playerid][player_name]);
		
		pInfo[playerid][player_nichchange] = gettime() + ((60*60)*72);
		
		achievement(playerid, 13);
	}
}
Dialog:Register_1(playerid, response, listitem, inputtext[])
{
	if(pInfo[playerid][player_class]) TDPanorama(playerid, true); 
	if (response)
	{
		if(strlen(inputtext) > 24)
		{
			SendClientMessage(playerid, COLOR_ERROR, " Has³o mo¿e sk³adaæ siê maksymalnie z 24 znaków");
			Dialog_Show(playerid, Register_1, DIALOG_STYLE_PASSWORD, "Rejestracja (1/3) » Has³o", "Dziêkujemy za chêæ zarejestrowania siê\nDziêki temu Twoje statystyki, osi¹gniêcia bêd¹ zapisywane\n\n{00FF00}Aby przejœæ do nastêpnego kroku podaj has³o do Twojego konta:", "Dalej", "Zamknij");
			
			return 1;
		}
		
		if(strlen(inputtext) < 4)
		{
			SendClientMessage(playerid, COLOR_ERROR, " Has³o mo¿e sk³adaæ siê minimalnie z 4 znaków");
			Dialog_Show(playerid, Register_1, DIALOG_STYLE_PASSWORD, "Rejestracja (1/3) » Has³o", "Dziêkujemy za chêæ zarejestrowania siê\nDziêki temu Twoje statystyki, osi¹gniêcia bêd¹ zapisywane\n\n{00FF00}Aby przejœæ do nastêpnego kroku podaj has³o do Twojego konta:", "Dalej", "Zamknij");
			
			return 1;
		}
		if(!PasswordCorrect(inputtext))
		{
			SendClientMessage(playerid, COLOR_ERROR, " Has³o mo¿e sk³adaæ siê tylko z {b}liter{/b} i {d}liczb{/b}.");
			Dialog_Show(playerid, Register_1, DIALOG_STYLE_PASSWORD, "Rejestracja (1/3) » Has³o", "Dziêkujemy za chêæ zarejestrowania siê\nDziêki temu Twoje statystyki, osi¹gniêcia bêd¹ zapisywane\n\n{00FF00}Aby przejœæ do nastêpnego kroku podaj has³o do Twojego konta:", "Dalej", "Zamknij");
			
			return 1;
		}
		new c = PasswordCheck(inputtext);
				
		if(c < 2)
		{
			SendClientMessage(playerid, COLOR_ERROR, " Poda³eœ zbyt s³abe has³o (si³a has³a ({b}%d/4{/b})", c);
			Dialog_Show(playerid, Register_1, DIALOG_STYLE_PASSWORD, "Rejestracja (1/3) » Has³o", "Dziêkujemy za chêæ zarejestrowania siê\nDziêki temu Twoje statystyki, osi¹gniêcia bêd¹ zapisywane\n\n{00FF00}Aby przejœæ do nastêpnego kroku podaj has³o do Twojego konta:", "Dalej", "Zamknij");
			
			return 1;
		}
		mysql_real_escape_string(inputtext, pInfo[playerid][player_password]);
		printf("[regpassdebug] %s wpisal %s", pInfo[playerid][player_name], pInfo[playerid][player_loginpass]);

		Dialog_Show(playerid, Register_2, DIALOG_STYLE_INPUT, "Rejestracja (2/3) » E-Mail", "Dziêkujemy za chêæ zarejestrowania siê\nDziêki temu Twoje statystyki, osi¹gniêcia bêd¹ zapisywane\n\n{00FF00}Aby przejœæ do nastêpnego kroku Twój adres E-Mail", "Dalej", "Zamknij");
		if(pInfo[playerid][player_class]) TDPanorama(playerid, true); 
	} else if(pInfo[playerid][player_class])OnPlayerRequestClass(playerid, 0);
	return 1;
}

Dialog:Register_2(playerid, response, listitem, inputtext[])
{
	if(pInfo[playerid][player_class]) TDPanorama(playerid, true); 
	if (response)
	{
		if(strlen(inputtext) > 42)
		{
			SendClientMessage(playerid, COLOR_ERROR, " E-Mail mo¿e sk³adaæ siê maksymalnie z 24 znaków");
			Dialog_Show(playerid, Register_2, DIALOG_STYLE_INPUT, "Rejestracja (2/3) » E-Mail", "Dziêkujemy za chêæ zarejestrowania siê\nDziêki temu Twoje statystyki, osi¹gniêcia bêd¹ zapisywane\n\n{00FF00}Aby przejœæ do nastêpnego kroku Twój adres E-Mail", "Dalej", "Zamknij");
			
			return 1;
		}
		
		if(strlen(inputtext) < 4)
		{
			SendClientMessage(playerid, COLOR_ERROR, " E-Mail mo¿e sk³adaæ siê minimalnie z 4 znaków");
			Dialog_Show(playerid, Register_2, DIALOG_STYLE_INPUT, "Rejestracja (2/3) » E-Mail", "Dziêkujemy za chêæ zarejestrowania siê\nDziêki temu Twoje statystyki, osi¹gniêcia bêd¹ zapisywane\n\n{00FF00}Aby przejœæ do nastêpnego kroku Twój adres E-Mail", "Dalej", "Zamknij");
			
			return 1;
		}
		for(new i, len = strlen(inputtext); i<len; i++) inputtext[i] = tolower(inputtext[i]);
		
		if(!IsValidEmailEx(inputtext))
		{
			SendClientMessage(playerid, COLOR_ERROR, " Podany E-Mail jest nie prawid³owy.");
			Dialog_Show(playerid, Register_2, DIALOG_STYLE_INPUT, "Rejestracja (2/3) » E-Mail", "Dziêkujemy za chêæ zarejestrowania siê\nDziêki temu Twoje statystyki, osi¹gniêcia bêd¹ zapisywane\n\n{00FF00}Aby przejœæ do nastêpnego kroku Twój adres E-Mail", "Dalej", "Zamknij");
			
			return 1;
		}
		mysql_real_escape_string(inputtext, pInfo[playerid][player_email]);
		if(AccountExists("mail", pInfo[playerid][player_email]))
		{
			SendClientMessage(playerid, COLOR_ERROR, " Podany E-Mail jest ju¿ przez kogoœ u¿ywany.");
			Dialog_Show(playerid, Register_2, DIALOG_STYLE_INPUT, "Rejestracja (2/3) » E-Mail", "Dziêkujemy za chêæ zarejestrowania siê\nDziêki temu Twoje statystyki, osi¹gniêcia bêd¹ zapisywane\n\n{00FF00}Aby przejœæ do nastêpnego kroku Twój adres E-Mail", "Dalej", "Zamknij");
			
			return 1;
		}
		
		new ucode[20];
		RandCode(ucode);
		
		m_query("INSERT INTO `"prefix"_players` (`nick`, `password`, `ucode`, `ip_register`, `ip_last`, `date_last`, `mail`) VALUES ('%s', md5(md5('%s')), '%s', '%s', '%s', NOW(), '%s');", pInfo[playerid][player_name], pInfo[playerid][player_password], ucode, pInfo[playerid][player_ip], pInfo[playerid][player_ip], pInfo[playerid][player_email]);
		//zostawmy printfa dla debugu 
		//systemprintf("register",true, "INSERT INTO `"prefix"_players` (`nick`, `password`, `ucode`, `ip_register`, `ip_last`, `date_last`, `mail`) VALUES ('%s', md5(md5('%s')), '%s', '%s', '%s', NOW(), '%s');", pInfo[playerid][player_name], rot13(pInfo[playerid][player_password]), ucode, pInfo[playerid][player_ip], pInfo[playerid][player_ip], pInfo[playerid][player_email]);
		
		SendClientMessage(playerid, COLOR_DARK_ORCHID_2, " ");
		SendClientMessage(playerid, COLOR_DARK_ORCHID_2, " ");
		SendClientMessage(playerid, COLOR_DARK_ORCHID_2, " ");
		SendClientMessage(playerid, COLOR_DARK_ORCHID_2, " ");
		
		SendClientMessage(playerid, COLOR_DARK_ORCHID_2, " ~ -------------------------------------------------------------------------------------- ~");
		
		SendClientMessage(playerid, COLOR_INFO*2, "* Zosta³eœ zarejestrowany. Twój unikalny kod to {b}%s{/b} - Zapamiêtaj go!", ucode);
		
		pInfo[playerid][player_userank] = 17;
		
		GivePlayerScore(playerid, 150);
		GivePlayerMoney(playerid, 10000);
		

		pInfo[playerid][player_id] = mysql_insert_id();
		pInfo[playerid][player_logged] = true; 
		pInfo[playerid][player_register] = true; 
		
		SavePlayer(playerid);
		
		if(CheckPlayerData(playerid, true))
		{
			format(string2, sizeof(string2), "Rejestracja przebieg³a prawid³owo. \nDane konta:\n\nG³ówne\n\t»Nick: %s\n\t»E-Mail: %s\n\nInne\n\t» ID Konta: %d\n\t» Unikalny kod: %s\n\n\nAdres naszego forum to 4fun-serv.pl", pInfo[playerid][player_name], pInfo[playerid][player_email], pInfo[playerid][player_id], ucode);
			ShowPlayerDialog(playerid, 9999, DIALOG_STYLE_MSGBOX, "Rejestracja (3/3) » Zakoñczenie", string2, "Zamknij", "");
		}
		else 
		{
			InfoBox(playerid, "Wyst¹pi³ b³¹d z rejestracja Twojego konta. \nProsimy wyjœæ i ponownie wejœæ na server i spróbowaæ siê\nzarejestrowaæ.");
			return 0;
		}
		
		pInfo[playerid][player_logged] = true; 
		achievement(playerid, 0);
		
		SendPlayerMail(playerid);
		
		gmData[server_registered]++;
		this->config::savesql_int("stats/registered", gmData[server_registered]);

		 
		if(pInfo[playerid][player_vip] > gettime())
		{
			pInfo[playerid][player_vip] = pInfo[playerid][player_vip] + UnixTime('d', 3);
		}
		else 
		{
			pInfo[playerid][player_vip] = gettime()	+ UnixTime('d', 3);
		}
		Iter_Add(Vips, playerid);
		m_query("Update "prefix"_players SET vip = %d WHERE id=%d LIMIT 1", pInfo[playerid][player_vip], pInfo[playerid][player_id]);
			
		SendClientMessage(playerid, COLOR_YELLOW, " Otrzyma³eœ darmowe konto VIP na okres trzech dni za rejestracje"); 
		SendClientMessage(playerid, COLOR_DARK_ORCHID_2, " ~ -------------------------------------------------------------------------------------- ~");
		SendClientMessageToAll(COLOR_GREEN, ""chat" Mamy nowego zarejestrowanego gracza! {b}%s (%d){/b} jest to nasz %d zarejestrowany gracz - Witamy!", playerNick(playerid), playerid, gmData[server_registered]);
		SendClientMessage(playerid, COLOR_DARK_ORCHID_2, " ");
		SendClientMessage(playerid, COLOR_DARK_ORCHID_2, " ");
		
		if(pInfo[playerid][player_class])OnPlayerRequestClass(playerid, 0);
	} else if(pInfo[playerid][player_class])OnPlayerRequestClass(playerid, 0);
	return 1;
}

Dialog:DoczepianeObiektyDialog(playerid, response, listitem, inputtext[])
{
	if(response) 
	{
		SendClientMessage(playerid, 0x00CDFFFF, "[DOCZEPIANE OBIEKTY] {00FF89}Obiekty zosta³y {F7FF00}doczepione!");
		DoczepianeObiekty(GetPlayerVehicleID(playerid));
	}
}

Dialog:BarDyskoteka(playerid, response, listitem, inputtext[])
{
	if(!response || listitem == 10 || listitem == 0) return DeletePVar(playerid, "SklepikBlokuj");
	
	switch(listitem)
	{
		case 1: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
		case 2: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
		case 3: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
		case 4: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
		case 6: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER); // OBY SIE NIE NAJEBALI XDDDDDDDDDDDDD
		case 7: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
		case 8: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
		case 9: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
		case 11: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
		case 12: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
		case 13: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
		case 14: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
		case 15: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
		case 16: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
		case 17: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
	}

	DeletePVar(playerid, "SklepikBlokuj");
	SendClientMessage(playerid, 0xFD9A32FF, "BAR {64CD00}P4S: {64FCFF}Dosta³eœ %s", inputtext);
	return 1;
}

Dialog:DIALOG_STACJE_DYSKA(playerid, response, listitem, inputtext[])
{
	if(!response)  return 0;
	SendClientMessage(playerid, COLOR_NAVAJO_WHITE, "{30CC00}[DYSKOTEKA] {FF32FD}Puœci³eœ {FFFF00}%s ! :D", StacjeRadiowe[listitem][Nazwa]);
	
	MuzaNaDysce = listitem;
	
	foreach(Player, x) if(GetPVarInt(x, "Dyskoteka")) PlayAudioStreamForPlayer(x,StacjeRadiowe[listitem][URL]);
	return 1;
}
new timeCodeUsed[MAX_PLAYERS];


Dialog:DIALOG_KOD_AKTYWACYJNY(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
	
	if (!(1 <= strlen(inputtext) <= 22)) return InfoBox(playerid, "Nieprawdilowa dlugosc kodu!");
	
    if(timeCodeUsed[playerid] > gettime()) return SendClientMessage(playerid, COLOR_ERROR, "Kodu mo¿na u¿ywaæ co 5 minut"), mysql_free_result();

	new cod[64];
	mysql_real_escape_string(inputtext,cod);    
    m_query("SELECT c.*, ifnull(p.nick, 'Brak') admin FROM mreg_codes c  LEFT JOIN mreg_players p ON p.id = c.admin where c.code = '%s';", cod);
   
    mysql_store_result();
       
    if(!mysql_num_rows()) return SendClientMessage(playerid, COLOR_ERROR, "Nieprawid³owy kod aktywacyjny!"), mysql_free_result();
    else
    {
		new tmp[300];
        mysql_fetch_row(tmp, "|");
        mysql_free_result();

        new id, days, used, status, code[50], admin, reszta[50];
		
        new admin_nick[24];
        sscanf(tmp, "p<|>dddds[50]ds[50]s[50]s[24]", id, days, used, status, code, admin, reszta, reszta, admin_nick);
               
        if(status == 2 || status == 1 || used != 0) return SendClientMessage(playerid, COLOR_ERROR, "Kod zosta³ wykorzystany lub nieuwa¿niony!");
                            
        if(pInfo[playerid][player_vip] > gettime()) pInfo[playerid][player_vip] = pInfo[playerid][player_vip] + UnixTime('d', days);
        else  pInfo[playerid][player_vip] = gettime() + UnixTime('d', days);
               
        Iter_Add(Vips, playerid);
        SavePlayer(playerid);
        m_query("update `mreg_players` set `vip`='%d' WHERE `id` = '%d'",pInfo[playerid][player_vip], pInfo[playerid][player_id]);   

		
        m_query("SELECT `nick` FROM `mreg_players` WHERE `id` = '%d'", admin);
        mysql_store_result();
         
              
             // InfoBox(playerid, msg_granient(0xF03C3CFF,"|B³¹d|po³¹czenia|z|API|SMS.\nSpróbuj|ponownie.\n\n|Reklamacje|dotycz¹ce|us³ugi|nale¿y|sk³adaæ|pod|adresem|bok@servhost.pl"));
        InfoBox(playerid, splitf(msg_granient(0xF03C3CFF,"|Pomyœlnie|aktywowa³eœ|darmowy|kod|VIP|na|{b}%d|dni{/b},|kod|zosta³|wygenerowany:|{b}%s{/b}|przez|Administratora|:|{b}%s{/b}"), days, reszta, admin_nick));          
        timeCodeUsed[playerid] = gettime() + 5*60;
        m_query("UPDATE `mreg_codes` SET `status` = '1', `used` = '%d', `date_use` = now() WHERE `id` = '%d'",pInfo[playerid][player_id], id);
    }
 
    return 1;
}

new player@tutorialidx[MAX_PLAYERS];
stock Tutorial_List(playerid)
{
	Dialog_Show(playerid, DIALOG_TUT1, DIALOG_STYLE_LIST, "Tutorial", "/Solo (/soloinfo)\n/Spedycja (/spdinfo)\nPieni¹dze (/moneyinfo)\nRespekt (/rspinfo)", "Czytaj", "Zamknij");
	return 1;
}

Dialog:DIALOG_TUT1(playerid, response, listitem, inputtext[])
{
	if( response )
	{
		Tutorial_Desc(playerid, listitem);
	}
	return 1;
}


Dialog:DIALOG_TUT2(playerid, response, listitem, inputtext[])
{
	if( response )
	{
		Tutorial_Desc(playerid, player@tutorialidx[playerid] + 1);
	}
	return 1;
}


stock Tutorial_Desc(playerid, tutorial)
{

	new tut_str[2048];
	
	#define Tutorial_Strcat(%0) strcat(tut_str, ""%0"\n")
	#define Tutorial_Show(%0) Dialog_Show(playerid, DIALOG_TUT2, DIALOG_STYLE_MSGBOX, "Tutorial: "%0"", tut_str, "Dalej", "Zamknij")
	 
	player@tutorialidx[playerid] = tutorial;
	
	switch(tutorial)
	{
	
		case 0:
		{
			Tutorial_Strcat("Aby zarejestrowaæ swoje konto na tym serwerze wystarczy, ¿e wpiszesz");
			Tutorial_Strcat("/register nastêpnie wpiszesz has³o i email (logowanie bêdzie siê odbywaæ przy po³¹czeniu z serwerem).\n");
			Tutorial_Strcat("Mo¿esz tak¿e zmieniæ swoje has³o, przypisaæ swój ulubiony skin,");
			Tutorial_Strcat("przejrzeæ swoje statystyki, w³¹czaæ lub wy³¹czaæ prywatne wiadomoœci, teleporty lub rampy");
			Tutorial_Strcat("zrobisz to wpisuj¹c komendê /panel .\n");
			Tutorial_Strcat("Zalecamy zarejestrowaæ swoje konto aby Twoje statystyki, pieni¹dze, osi¹gniêcia by³y zapisywane.");
			Tutorial_Strcat("Rejestracja jest szybka i darmowa.");
			
			Tutorial_Show("Rejestracja i zarz¹dzanie kontem.");
		}
		case 1:
		{
			Tutorial_Strcat("Pojedynki solo");
			Tutorial_Strcat("Ka¿dy Gracz mo¿e wzi¹æ udzia³ w pojedynku solo z dowolnym Graczem.");
			Tutorial_Strcat("Wystarczy ¿e zaprosisz Gracza na solo (/solo [id gracza] [bron]) a on je zaakceptuje");
			Tutorial_Strcat("Po akceptacji solo jesteœcie przenoszeni na specjaln¹ arenê na której jest odliczanie. ");
			Tutorial_Strcat("Po skoñczeniu odliczania obaj zostajecie odmro¿eni i zaczynacie solo. Wygraæ mo¿e tylko jeden.");
			Tutorial_Strcat("Po wygraniu solo wygrany dostaje dodatkowy poziom osi¹gniêcia (/ach 7) oraz 10 punktów respektu.");
			Tutorial_Strcat("Listê broni na solo mo¿emy zobaczyæ pod komend¹ /soloweapons.");
			
			Tutorial_Show("Pojedynki solo (/soloinfo)");
		}
		case 2:
		{
			Tutorial_Strcat("Przewozy tirami");
			Tutorial_Strcat("Na serwerze jest wbudowany system przewodu towaru (/spedycja).");
			Tutorial_Strcat("Przewóz polega na przewiezieniu wybranego towaru z punktu A do punktu B");
			Tutorial_Strcat("Towar jest przydzielany losowo (w punkcie bazy spedycyjnej) ");
			Tutorial_Strcat("Aby za³adowaæ towar musimy wjechaæ tirem z naczep¹ w czerwony punkt.");
			Tutorial_Strcat("Jeœli w pobli¿u nie ma przyczepy lub tira mo¿emy u¿yæ komend /naczepa lub /tir.");
			Tutorial_Strcat("\nPo przywiezieniu towaru do punktu B otrzymujemy nagrodê w postaci");
			Tutorial_Strcat("\t› Losowo pieni¹dze (/moneyinfo) w skali 1:198801.");
			Tutorial_Strcat("\t› Losowo punkty respekt (/rspinfo) w skali 1:129.");
			Tutorial_Strcat("\t› Osi¹gniêcie \"Zawodowy kierowaca\" ((/ach 1).\n");
			Tutorial_Show("(/spdinfo)");
		}
		case 3:
		{ 
			Tutorial_Strcat("Na serwerze mamy mo¿liwoœæ zarabiania pieniêdzy ($).");
			Tutorial_Strcat("Za które mo¿emy kupowaæ kamizelkê, ¿ycie, broñ etc... ");
			Tutorial_Strcat("Pieni¹dze mo¿emy zarobiæ na kilka sposobów");
			Tutorial_Strcat("\t› Udzia³ w evenach (/ws, /wg...) ");
			Tutorial_Strcat("\t› Przewóz tirami (/spdinfo).");
			Tutorial_Strcat("\t› Przywo¿enie aut do skupu (/skupinfo).");
			
			
		 
			Tutorial_Show("Pieni¹dze (/moneyinfo)");
		}
		case 4:
		{
			 
				
			Tutorial_Strcat("Jest to serwer na którym po zarejestrowaniu mo¿esz odblokowaæ nowe levele.");
			Tutorial_Strcat("Respekt zdobywa siê poprzez branie udzia³u w eventach, b¹dŸ zabijanie innych graczy.");
			Tutorial_Strcat("Najszybciej zdobêdziesz respekt posiadaj¹c Konto Premium które mno¿y respekt za zabicie graczy x2.\n");
			Tutorial_Strcat("Info dot. Twojego aktualnego levelu oraz respektu znajdziesz pod komend¹ /panel > Statystyki");
			Tutorial_Strcat("lub w pasku informacyjnym znajduj¹cym siê pod HUD-em gracza.\n");
			Tutorial_Strcat("Nowy level pozwala odblokowywaæ nowe bronie, wiêksze iloœci kamizelki na starcie, czy czarny kolor.");
			Tutorial_Strcat("Aby respekt zapisywa³ siê musisz byæ zarejestrowanym graczem.");
			Tutorial_Strcat("Kilka sposób zarobkowania respektu:");

			Tutorial_Strcat("\t› Udzia³ w evenach");
			Tutorial_Strcat("\t› Wykonywanie zadañ spedycyjnych (/spdinfo).");
			Tutorial_Strcat("\t› Dostarczanie aut do skupu pojazdów (/skupinfo).");
			Tutorial_Strcat("\t› Wygrywanie pojedynków z graczami (/soloinfo).");
			Tutorial_Strcat("\t› Zbieranie figurek/walizek/prezentów postawionych na mapie.");
			Tutorial_Strcat("\t› Przepisywanie kodów i rozwi¹zywanie zadañ matematycznych które pojawiaj¹ siê co jakiœ czas na ekranie.");
			
			Tutorial_Show("Respekt i level.");
			 
		}
		case 5:
		{
			Tutorial_Strcat("Prywatny dom");
			Tutorial_Strcat("Na serwerze jest wbudowany system domów ka¿dy gracz mo¿e posiadaæ prywatny dom");
			Tutorial_Strcat("Aby zdobyæ w³asny dom nale¿y z najœæ dom na mapie (lista domów /domy{FFFFFF}) oraz posiadaæ ");
			Tutorial_Strcat("Odpowiedni¹ iloœæ respektu na zakup domu, po czym wejœæ w pickup z domem i wybraæ opcjê kupna.");
			Tutorial_Strcat("\nPo kupnie domu mo¿emy nim zarz¹dzaæ zmieniaæ has³o, zmieniaæ nazwê, ustawiaæ spawn w domu, sprzedaæ dom.");
			Tutorial_Strcat("Do domu mo¿esz zapraszaæ goœci oraz robiæ w nim ró¿ne imprezy.");
			Tutorial_Strcat("System domów ma te¿ komendy /domtp, /wyjdz, /domy{FFFFFF} ");
		 
		 
			Tutorial_Show("(/domyinfo)");
		}
	}
}

CMD:soloinfo(playerid, cmdtext[])
{
	Tutorial_Desc(playerid, 0);
	return 1;
}
CMD:spdinfo(playerid, cmdtext[])
{
	Tutorial_Desc(playerid, 1);
	return 1;
}
CMD:moneyinfo(playerid, cmdtext[])
{
	Tutorial_Desc(playerid, 2);
	return 1;
}
CMD:rspinfo(playerid, cmdtext[])
{
	Tutorial_Desc(playerid, 3);
	return 1;
}
CMD:domyinfo(playerid, cmdtext[])
{
	Tutorial_Desc(playerid, 4);
	return 1;
}