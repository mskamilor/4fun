/*
	Commands 1.0
	{
	
		(c) Copyright 2013-2014 by mrdrifter, Game
		{
			@author    : mrdrifter (http://4fun-serv.pl/__drifter__/),Game
			@date      : 14 grudnia 2013
			@update    : 3 stycznia 2014
		}
	}
*/
CMD:delgun(playerid,params[])
{
	ResetPlayerWeapons(playerid);
	return 1;
}

CMD:kolor(playerid,p[])
{
	pInfo[playerid][player_acolor] = playerid;
	new listakolorow[4500];
	for(new i=0; i<100; i++)format(listakolorow, sizeof(listakolorow), "%s{FFFFFF}%d. {%06x}Wybierz kolor nicku\n", listakolorow, i, GangColors[i]>>>8);
	
	Dialog_Show(playerid, DIALOG_ACOLOR, DIALOG_STYLE_LIST, "Wybierz swój kolor", listakolorow, "Zmieñ", "Zamknij");
	return 1;
}
CMD:launcher(playerid,p[])
{
	InfoBox(playerid,msg_granient(0xF03C3CFF,"\n|Launcher|daje|Ci|mo¿liwoœæ|wejœcia|na|serwer|jednym|przyciskiem\n\t\t\t|bez|odpalania|sampa!\n|W|launcherze|dodatkowo|masz|podgl¹d|graczy|OnLine|na|serwerze\n|Za|ka¿de|wejœcie|launcherem|dostajesz|osi¹gniêcie!|oraz|dodatkowo|20|respektu\n|Launchera|mo¿na|pobraæ|z|strony:|http://4fun-serv.pl/launcher"));
	return 1;
}

CMD:fps(playerid, cmdtext[])
{
	if(pInfo[playerid][player_fps])
	{
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Wy³¹czy³eœ tryb First Person");
		pInfo[playerid][player_fps] = false;
		SetCameraBehindPlayer(playerid);
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREEN, ""chat" W³¹czy³eœ tryb First Person");
		pInfo[playerid][player_fps] = true;
		SyncCamera(playerid);
	}
	return 1;
}

CMD:setobject(playerid, cmdp[])
{ // nie oddana oficjalnie ;_;
// Edit by Lagowy, ODDANA OFICJALNIE.

	if(!pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, " Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do tej komendy.");
		return 1;
	}
	
	Streamer_DestroyAllVisibleItems(playerid, 0);
	  
	if(!pInfo[playerid][player_objected])
	{
		SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} *{/b} {b}Wy³¹czy³eœ{/b} wszystkie obiekty na mapie");
		Streamer_ToggleIdleUpdate(playerid, 0);
		Streamer_ToggleItemUpdate(playerid, 0, 0);
		
		pInfo[playerid][player_objected] = true;
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} *{/b} {b}W³¹czy³eœ{/b} wszystkie obiekty na mapie"); 
		Streamer_ToggleIdleUpdate(playerid, 1);
		Streamer_ToggleItemUpdate(playerid, 0, 1);
		
		pInfo[playerid][player_objected] = false;
		 
	}
	return 1;
}
CMD:v(playerid, cmdtext[])
{
	if(pInfo[playerid][player_last_damage] > gettime()) 
	{
		SendClientMessage(playerid,COLOR_ERROR, "Niestety nie mo¿esz tego zrobiæ!\nPrawdobodobnie uciekasz z walki.\n\nMusisz odczekaæ 5 sekund od zadanych obra¿eñ");
		return 0;
	}
	new veh = GetVehicleID(cmdtext);
	if(veh > 0)
	{
		new cv = CreatePlayerVehicle(playerid, veh);
		PutPlayerInVehicle(playerid, cv, 0);
		
		SendClientMessage(playerid, COLOR_GOLD, ""chat" Stworzy³eœ pojazd %s, koszt 5.000$ (Je¿eli nie posiada³eœ takiej sumy pojazd by³ za darmo).", VehicleNames[veh-400]);
		if(GetPlayerMoney(playerid) < 5000) GivePlayerMoney(playerid, -5000);
		
		return 1;
	}
	Gui_ShowVehiclesCategories(playerid);
	return 1;
}
CMD:skin(playerid, cmdtext[])
{
	if(GetPlayerMoney(playerid) < 1000)
		return SendClientMessage(playerid, COLOR_ERROR, ""chat" Zmiana skinu kosztuje 1.000$");
	
	if(isnull(cmdtext))
		return SendClientMessage(playerid, COLOR_ERROR, ""chat" /Skin <id skinu>");
		
	new s = strval(cmdtext);
	if(s < 0 || s > 311)
		return SendClientMessage(playerid, COLOR_ERROR, ""chat" B³êdne id skinu.");
	
	if(!gmData[gm_skins][s] && s > 0)
		return SendClientMessage(playerid, COLOR_ERROR, ""chat" Skin o podanym id nie zosta³ dodany do mapy (prawdopodobnie by³ zbugowany).");
	
	SendClientMessage(playerid, COLOR_GOLD, ""chat" Zmieni³eœ skina, koszt 1.000$.");
	GivePlayerMoney(playerid, -1000);
	
	SetPlayerSkin(playerid, s);
	pInfo[playerid][player_skin] = s;	
	return 1;
}
/*
CMD:ms(playerid, cmdtext[])
{
	
	if(!pInfo[playerid][player_class])
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Wybrana komenda jest dostêpna tylko w wybiera³ce skinów.");
		return 1;
	}
	if(!pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, " Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do tej komendy.");
		return 1;
	}
	
	OnPlayerRequestClass(playerid, GetSkinAddID(pInfo[playerid][player_loadskin]));
	
	return 1;
}*/
CMD:mycar(playerid, cmdtext[])
{
	
	if(GetPlayerMoney(playerid) < 500)
		return SendClientMessage(playerid, COLOR_ERROR, ""chat" Przywo³anie pojazdu kosztuje 500$");
	
	if(!GetVehicleModel(pInfo[playerid][player_vehicle]))
		return SendClientMessage(playerid, COLOR_ERROR, ""chat" Nie stworzy³eœ jeszcze pojazdu b¹dŸ Twój pojazd zosta³ usuniêty.");
	
	if(IsPlayerInAnyVehicle(playerid))
		return SendClientMessage(playerid, COLOR_ERROR, ""chat" Jesteœ w pojedzie nie mo¿esz u¿yæ tej komendy.");
	
	new Float:x, Float:y, Float:z;
	new Float:facing;
	new Float:distance;
	
	GetPlayerPos(playerid, x, y, z);
	
	if(IsPlayerInRangeOfPoint(playerid,100.0,1104.2842,-1334.5215,13.7878))return SendClientMessage(playerid,COLOR_ERROR,"Nie mo¿esz przywo³aæ pojazdu w tym miejscu.");
	
	GetPlayerFacingAngle(playerid, facing);
	
	new Float:size_x, Float:size_y, Float:size_z;
	GetVehicleModelInfo(GetVehicleModel(pInfo[playerid][player_vehicle]), VEHICLE_MODEL_INFO_SIZE, size_x, size_y, size_z);
	distance = size_x + 0.5;
	x += (distance * floatsin(-facing, degrees));
	y += (distance * floatcos(-facing, degrees));
	
	SetVehiclePos(pInfo[playerid][player_vehicle], x, y, (z * 0.25));
	
	SendClientMessage(playerid, COLOR_GOLD, ""chat" Przywo³a³eœ pojazd %s, koszt 500$.", VehicleNames[GetVehicleModel(pInfo[playerid][player_vehicle])-400]);
	GivePlayerMoney(playerid, -500);
	return 1;
}
CMD:radio(playerid,cmdtext[])
{
	string2[0] = EOS;
	for(new i = 0;i<sizeof(StacjeRadiowe);i++)
	{
		format(string2,sizeof(string2),"%s%s\n",string2, StacjeRadiowe[i][Nazwa]);
	}
	Dialog_Show(playerid, DIALOG_STACJE2, DIALOG_STYLE_LIST, "{16C60D}Wybierz stacje radiow¹", string2, "Wybieram", "Anuluj...");
	return 1;
}
CMD:radiooff(playerid, params[])
{
	SendClientMessage(playerid, COLOR_NAVAJO_WHITE, "» Radio wy³¹czone");
	StopAudioStreamForPlayer(playerid);
	return 1;
}
CMD:regulamin(playerid, params[])
{
    static outdata[2048];
    outdata[0] = EOS;
    #define reg_splitf(%0); strcat(outdata, "» "%0"\n");

	reg_splitf("Na serwerze zabrania siê:");
	reg_splitf("1. U¿ywania wszelkiego typu programów ulatwiajacych rozgrywke");
	reg_splitf("2. Reklamowania stron majacych na celu popularyzowanie cheatow");
	reg_splitf("3. Reklamowania konkurencyjnych serwerow");
	reg_splitf("4. Drive-by oraz drive-thru - strzelanie do graczy z wszelkiego typu pojazdow");
	reg_splitf("5. Zabijania gracza przy uzyciu pojazdu czy tez smigla helikoptera");
	reg_splitf("6. Wykorzystywania bugow dzialajacych na niekorzysc graczy lub serwera");
	reg_splitf("7. Tworzenia wiecej niz jednego konta w przypadku, gdy na pierwszym nalozona jest blokada czasowa (ban czasowy lub permanentny)");
	reg_splitf("8. U¿ywania Joypad'a");
	reg_splitf("9. Omijania kary (ban, jail, mute, warn)");
	reg_splitf("10. Spamu niepotrzebnymi wiadomosciami na /pm czy tez na chacie glownym");
	reg_splitf("11. Spamu flood");
	reg_splitf("12. Spamu teleportami, raportami oraz solo");
	reg_splitf("13. Wyzywania graczy lub administracji");
	reg_splitf("14. Prowokowania/wszczynania klotni");
	reg_splitf("15. Uzywania obrazliwych lub podobnych nickow do administracji");
	reg_splitf("16. Zabijania w strefach bez DM oraz w miejscu spawnu");
	reg_splitf("17. Przeszkadzania w eventach, zabawach oraz turniejach organizowanych przez administratora lub moderatora");
	reg_splitf("18. Wyludzania expa/dolarow/wirtualnych zlotowek na wlasna odpowiedzialnosc");
	reg_splitf("19. Podszywania sie pod graczy lub administracje");
	reg_splitf("20. Pisania falszywych raportow");
	reg_splitf("21. Wymuszania rang od administracji");
	reg_splitf("22. Uzywania komendy /zw oraz uzywania klawisza ESC podczas walki");
	reg_splitf("23. Uleczanie podczas walki");
	reg_splitf("24. Zasmiecania miejsca spawnu zbednymi pojazdami");
	reg_splitf("25. Przeszkadzania w spedycji");
	reg_splitf("26. Sprzeciwiania sie zarzadzeniom administratora");
	reg_splitf("27. Naduzywania cenzuralnych oraz niecenzuralnych slow");
	ShowPlayerDialog(playerid, 9999, DIALOG_STYLE_MSGBOX, "Regulamin", outdata, "Zamknij", "");
	return 1;
}
CMD:loteria(playerid,cmdtext[])
{
	if(pInfo[playerid][player_loteria] > 0)
		return SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz odczekaæ %d sek, aby móc losowaæ w (/loteria)",pInfo[playerid][player_loteria]);
	
	Loteria__Public(playerid);
	pInfo[playerid][player_loteria] = 60;
	return 1;
}

CMD:taryfikator(playerid,params[])
{
	new tartext[2512];
	strcat(tartext, "{FFFFFF}Bany permanentne:\n");
	strcat(tartext, "{999999}1. Reklamowanie innych serwerów {FF9999}(Adresy IP, Strony WWW, Tagi)\n");
	strcat(tartext, "{999999}2. Omijanie aktywnego bana {FF9999}(ban-evading, skrót: be){999999}.\n");
	strcat(tartext, "{999999}3. Sprzedawanie kont/respektu za do³adowania{999999}.\n");
	strcat(tartext, "{999999}3. Wykorzystywanie multikont do sumowania respektu{999999}.\n\n");
		
	strcat(tartext, "{FFFFFF}Bany czasowe:\n");
	strcat(tartext, "{999999}1. Ka¿dy rodzaj cheatów/wspomagaczy - {EEEEEE}ban {FF9999}30{EEEEEE} dniowy{999999}.\n");
	strcat(tartext, "{999999}2. Obraza rodziców na ka¿dym z mo¿liwych czatów - {EEEEEE}ban {FF9999}7 {EEEEEE}dniowy{999999}.\n");
	strcat(tartext, "{999999}3. Ci¹g³y/nagminny trolling - {EEEEEE}ban {FF9999}5 {EEEEEE}dniowy{999999}.\n");
	strcat(tartext, "{999999}4. Prowokacje - {EEEEEE}ban {FF9999}5 {EEEEEE}dniowy{999999}.\n");
	strcat(tartext, "{999999}5. GroŸby - {EEEEEE}ban {FF9999}4 {EEEEEE}dniowy{999999}.\n");
	strcat(tartext, "{999999}6. Wykorzystywanie bugów (bug-using, skrót: bu) - {EEEEEE}ban {FF9999}3{EEEEEE} dniowy{999999}.\n");
	strcat(tartext, "{999999}7. Podszywanie siê - {EEEEEE}ban {FF9999}1{EEEEEE} dniowy{999999}.\n\n");
		
	strcat(tartext, "{FFFFFF}Jailowanie:\n");
	strcat(tartext, "{EEEEEE}W ka¿dej sytuacji {99BBFF}200{EEEEEE} sekund, powtarzaj¹ce siê sytuacje {99BBFF}+100 {EEEEEE}sekund do ka¿dej nastêpnej kary:\n");
	strcat(tartext, "{999999}1. Car-Kill{99BBFF} (w tym celowe rozje¿d¿anie){999999}.\n");
	strcat(tartext, "{999999}2. Ucieczka/Uleczanie podczas walki - {99BBFF}(UPW){999999}.\n");
	strcat(tartext, "{999999}3. Przeszkadzanie w evencie - {99BBFF}(PWE){999999}.\n");
	strcat(tartext, "{999999}4. Przeszkadzanie w spedycji - {99BBFF}(PWS){999999}.\n");
	strcat(tartext, "{999999}5. Zabijanie Jetpackiem/Jetpack-Kill - {99BBFF}(JPK){999999}.\n\n");

	strcat(tartext, "{FFFFFF}Wyciszanie:\n");
	strcat(tartext, "{EEEEEE}W ka¿dej sytuacji {99BBFF}200{EEEEEE} sekund, powtarzaj¹ce siê sytuacje {99BBFF}+100 {EEEEEE}sekund do ka¿dej nastêpnej kary:\n");
	strcat(tartext, "{999999}1. Spamowanie / Floodowanie / U¿ywanie Caps-Locka / Omijanie cenzury.\n");
	strcat(tartext, "{999999}2. Obra¿anie graczy/vipów.\n\n");

	strcat(tartext, "{FFFFFF}Ostrze¿enia (Warny):\n");
	strcat(tartext, "{999999}1. Zak³ócanie pracy administracji {FFDD77}(Fake-reporty, Podawanie IP P4S, Nadu¿ywanie /toadmin).\n");
	strcat(tartext, "{999999}2. Spamowanie / Floodowanie na {EEEEEE}/pm{999999}.\n");
	strcat(tartext, "{999999}3. U¿ywanie {EEEEEE}slide/run-buga{999999} na {EEEEEE}arenach/solo{999999}.\n");
	strcat(tartext, "{999999}4. Fistowanie {EEEEEE}(bicie piêœci¹) {999999}na arenach.\n\n\n");
		
	strcat(tartext, "{999999}{FF7777}Autor taryfikatora:{EEEEEE} Magik.\n{FFDD77}Wykonanie skryptu:{EEEEEE} VisztaPL.\n{BBFF99}Aktualizacja:{EEEEEE} 22:23, 07/08/2016.");
	ShowPlayerDialog(playerid, 999, 0, "Taryfikator", tartext, "Zamknij", "");
 	
	return 1;
}

CMD:tar(playerid,params[])
{
	return cmd_taryfikator(playerid,params);
}

CMD:ryby(playerid, cmdtext[])
{
	new i = random(fCount);
	SetPlayerPos(playerid, fData[i][fishing_pos][0], fData[i][fishing_pos][1], fData[i][fishing_pos][2]);
	SendClientMessage(playerid, COLOR_GOLD, ""chat" Zosta³eœ teleportowany nad staw - powodzenia! ");
	return 1;
}
CMD:help(playerid, cmdtext[])
{
	Gui_ShowPlayersHelp(playerid);
	return 1;
}
CMD:cmd(playerid, cmdtext[])
{
	//SendClientMessage(playerid, COLOR_GREEN, "» Na serverze aktualnie jest %d komend.", Command_GetPlayerCommandCount(playerid));
	Gui_ShowPlayersCommandsMenu(playerid);
	return 1;
}
CMD:drift(playerid, cmdtext[])
{
	Gui_ShowPlayerDriftDialog(playerid);
	return 1;
}
CMD:teles(playerid, cmdtext[])
{
	ShowPlayerDialog(playerid, DIALOG_TELES, DIALOG_STYLE_LIST, "• Teleports •", "Stunt/Drift/Race/Rozrywka\nInne\nGangowe", "Teleportuj", "WyjdŸ");
	return 1;
}
CMD:neon(playerid, params[])
{
	if(!IsPlayerInAnyVehicle(playerid))
		return SendClientMessage(playerid, COLOR_ERROR, " Musisz byæ w pojedzie!");
	
	Dialog_Show(playerid, DIALOG_SELECT_NEON, DIALOG_STYLE_LIST, "Neon", "» Ciemny niebieski\n» Czerwony\n» Zielony\n» Bia³y\n» Fioletowy\n» ¯ó³ty\n» B³êkitny\n» Jasnoniebieski\n» Ró¿owy\n» Pomarañczowy\n» Jasnozielony\n» Jasno¿ó³ty\n» {FF0000}Usuñ neon", "Wybierz", "Anuluj");
	return 1;
}
CMD:register(playerid, params[])
{
	if(pInfo[playerid][player_register])
		return SendClientMessage(playerid, COLOR_ERROR, " Jesteœ ju¿ zarejestrowany/a.");
	
	Dialog_Show(playerid, Register_1, DIALOG_STYLE_PASSWORD, "Rejestracja (1/3)", "Dziêkujemy za chêæ zarejestrowania siê\nDziêki temu Twoje statystyki, osi¹gniêcia bêd¹ zapisywane\n\n{00FF00}Aby przejœæ do nastêpnego kroku podaj has³o do Twojego konta:", "Dalej", "Zamknij");	
	return 1;
}
CMD:settp(playerid, cmdp[])
{
	if(pInfo[playerid][player_teleports] == true)
	{
		pInfo[playerid][player_teleports] = false;
		SendClientMessage(playerid, COLOR_INFO, ""chat" Odblokowa³eœ(aœ) teleporty do ciebie."); //wygenerowany
	}
	else
	{
		pInfo[playerid][player_teleports] = true;
		SendClientMessage(playerid, COLOR_INFO, ""chat" Zablokowa³eœ(aœ) teleporty do ciebie."); //wygenerowany
	}
	return 1;
}
CMD:setpm(playerid, cmdp[])
{	
	if(pInfo[playerid][player_pm] == true)
	{
		pInfo[playerid][player_pm] = false;
		SendClientMessage(playerid, COLOR_INFO, ""chat" Odblokowa³eœ(aœ) prywatne wiadomoœci do ciebie."); //wygenerowany
	}
	else
	{
		pInfo[playerid][player_pm] = true;
		SendClientMessage(playerid, COLOR_INFO, ""chat" Zablokowa³eœ(aœ) prywatne wiadomoœci do ciebie."); //wygenerowany
	}
	return 1;
}
CMD:konto(playerid, params[])
{
	if(!pInfo[playerid][player_register])
		return SendClientMessage(playerid, COLOR_ERROR, " Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do tej komendy.");
	
	ShowPlayerGui(playerid);
	return 1;
}
CMD:sv(playerid, params[])
{
	if(!pInfo[playerid][player_register])
		return SendClientMessage(playerid, COLOR_ERROR, " Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do tej komendy.");
	
	if(pInfo[playerid][player_savestats])
		return SendClientMessage(playerid, COLOR_ERROR, " Statystyki mo¿esz zapisaæ dopiero za %d sekund.", pInfo[playerid][player_savestats]);
	
	SendClientMessage(playerid, COLOR_ERROR, ""chat"Twoje Statystyki zosta³y zapisane.");
	SavePlayer(playerid);
	pInfo[playerid][player_savestats] = 120;
	return 1;
}
CMD:zmiennick(playerid, params[])
{	
	if(!pInfo[playerid][player_register])
		return SendClientMessage(playerid, COLOR_ERROR, " Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do tej komendy.");
	
	DialogFunc:Dialog_Konto(playerid, 1, 4, "hop");
	return 1;
}
CMD:osiagniecia(playerid, params[])
{
	if(!pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, " Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do tej komendy.");
		return 1;
	}	
	show_achievement(playerid);
	return 1;
}
CMD:stats(playerid, params[])
{
	Dialog_Show(playerid, DIALOG_STATS0, DIALOG_STYLE_LIST, "• Stats •", "» Twoje Statystyki\n» Statystyki Servera\n» Statystyki TOP", "Wybierz", "Zamknij");
	return 1;
}
CMD:top(playerid, params[])
{
	Dialog_Show(playerid, DIALOG_TOPS0, DIALOG_STYLE_LIST, "• Top •", " » Dotycz¹ce Gry\n » Dotycz¹ce Eventow\n » Dotycz¹ce Aren\n » Inne", "Wybierz", "Zamknij");
	return 1;
}
CMD:topglitch(playerid, params[]){
	
	m_query("SELECT mp.nick, mg.gltime FROM  mreg_glitchs mg left join mreg_players mp on mp.id=mg.uid where mg.gltime > 1 order by mg.gltime asc limit 25");
	mysql_store_result();
	
	new str[1024], Query[64], user[24],type[34], value, id=1;
	format(str,sizeof(str),""HEX_INFO"ID:\tNick:\t\t\t\tCzas:\n");
	
	while(mysql_fetch_row(Query))
	{

		sscanf(Query,"p<|>s[32]d", user, value);
		format(type, sizeof(type), "%0.4fs", value);
		
	
		format(str,sizeof(str),"%s\n"HEX_INFO"%02d.	%26s	    	   %32s",str, id++, user, type);
	}
	InfoBox(playerid, str);
	return 1;
}
CMD:bronie(playerid, params[])
{
	Dialog_Show(playerid, DIALOG_BRONIE, DIALOG_STYLE_LIST, "Broñ kosztuje 10 respektu oraz 1500$", "Katana\n9mm\nDesert Eagle\nSawnoff Shotgun\nCombat Shotgun\nMicro Uzi\nTec-9\nMP5\nM4\nSniper Rifle\nParachute\nPompa\nPi³a Mech.\nAK-47", "Kup", "Wyjdz");
	return 1;
}
CMD:autor(playerid, params[])
{
	DialogFunc:Help(playerid, 1, 2, "hop");
	return 1;
}
Dialog:DIALOG_BRONIE(playerid, response, listitem, inputtext[])
{	
	if(!response)
		return 1;
	
	if(IsPlayerEventItp(playerid))
	{
		InfoBox(playerid, "Nie mo¿esz teraz tego zrobiæ. :P");
		return 1;
	}
	
	if(GetPlayerMoney(playerid) < 1500)
		return SendClientMessage(playerid, 0, "Nie masz tyle kasy!");
	if(GetPlayerScore(playerid) < 10)
		return SendClientMessage(playerid, 0, "Nie masz tyle respektu!");
	
	GivePlayerMoney(playerid, -1500);
	GivePlayerScore(playerid, -5);
	
	SendClientMessage(playerid, COLOR_GRAY, ""chat" Broñ zosta³a zakupiona!");
	switch(listitem)
	{
		case 0:
		{
			
			GivePlayerWeapon(playerid, 8, 1);
		}
		case 1:
		{
			GivePlayerWeapon(playerid, 22, 500);
		}
		case 2:
		{
			GivePlayerWeapon(playerid, 24, 500);
		}
		case 3:
		{
			GivePlayerWeapon(playerid, 26, 500);
		}
		case 4:
		{
			GivePlayerWeapon(playerid, 27, 500);
		}
		case 5:
		{
			GivePlayerWeapon(playerid, 28, 500);
		}
		case 6:
		{
			GivePlayerWeapon(playerid, 32, 500);
		}
		case 7:
		{
			GivePlayerWeapon(playerid, 29, 500);
		}
		case 8:
		{
			GivePlayerWeapon(playerid, 31, 500);
		}
		case 9:
		{
			GivePlayerWeapon(playerid, 34, 500);
		}
		case 10:
		{
			GivePlayerWeapon(playerid, 46, 1);
		}
		case 11:
		{
			GivePlayerWeapon(playerid, 25, 1000);
		}
		case 12:
		{
			GivePlayerWeapon(playerid, 9, 100);
		}
		case 13:
		{
			GivePlayerWeapon(playerid, 30, 1000);
		}
	}
	
	return 1;
}
CMD:ach(playerid,cmdtext[])
{
	if(!pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, " Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do tej komendy.");
		return 1;
	}
	new aid;
	if(sscanf(cmdtext, "d", aid)) 
		return SendClientMessage(playerid, COLOR_ERROR, "* U¿yj /Ach <osi¹gniêcie>");
	if(aid >= sizeof(Osiagniecia) || aid < 0) return SendClientMessage(playerid, COLOR_ERROR, "* Nie prawid³owe osi¹gniêcie.");
	
	show_player_achinfo(playerid, aid);
	return 1;
}
 
CMD:vip(playerid,params[])return cmd_portfel(playerid,params);

CMD:portfel(playerid, cmd[])
{
	if(!pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, " Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do tej komendy.");
		return 1;
	}
	//\n» {FF00FF}WprowadŸ Darmowy Kod Aktywacyjny
	ShowPlayerDialog(playerid, DIALOG_PORTFEL, DIALOG_STYLE_LIST, "• Wallet •", "» Doladuj portfel\n» Stan portfela\n» Kupno\n» Regulamin\n» Przelew œrodków\n» Wpisz darmowy kod VIP\n» {00FFFF}Co daje VIP?", "Ok", "Anuluj");
	return 1;
}
CMD:dodatki(playerid, cmd[])
{	
	new string[228];
	for(new x;x<MAX_PLAYER_ATTACHED_OBJECTS;x++)
	{
		if(IsPlayerAttachedObjectSlotUsed(playerid, x))
			format(string, sizeof(string), "%s» Slot - %d (U¿ywany)\n ", string, x);
		else
			format(string, sizeof(string), "%s» Slot - %d\n", string, x);
	}
	Dialog_Show(playerid, D_A_I_SELECTION, DIALOG_STYLE_LIST, "{FF0000}Dodawanie obiektu do skina", string, "Wybierz", "Anuluj");
	return 1;
}

CMD:vdodatki(playerid, cmd[])
{	

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{
		SendClientMessage(playerid, COLOR_ERROR, " Musisz byæ w pojeŸdzie aby u¿yæ tej komendy.");
		return 1;
	}
	new string[228];
	for(new x;x<MAX_PLAYER_VEHICLE_OBJECT;x++)
	{
		if(player_vehicle_object[playerid][x])
			format(string, sizeof(string), "%s» Slot - %d (U¿ywany)\n ", string, x);
		else
			format(string, sizeof(string), "%s» Slot - %d\n", string, x);
	}
	Dialog_Show(playerid, D_A_I_SELECTIONVEH, DIALOG_STYLE_LIST, "{FF0000}Dodawanie obiektu do pojazdu - Slot", string, "Wybierz", "Anuluj");
	return 1;
}

CMD:modernizacja(playerid, cmdtext[])
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{
		SendClientMessage(playerid, COLOR_ERROR, " Musisz byæ w pojeŸdzie aby u¿yæ tej komendy.");
		return 1;
	}
	
	Dialog_Show(playerid, DIALOG_AUTO, DIALOG_STYLE_LIST, "Modernizacja pojazdu", "» Silnik\n»  Œwiat³a\n»  Alarm\n»  Drzwi\n»  Baga¿nik\n»  Maska\n»  Tablica Rejestracyjna", "Wybierz", "Zamknij");
	return 1;
}
CMD:tunemenu(playerid, cmds[])
{
	if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_ERROR, " Musisz byæ w pojeŸdzie!");
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_ERROR, " Musisz byæ kierowc¹.");
	
	Dialog_Show(playerid, DIALOG_TUNEMENU, DIALOG_STYLE_LIST, "Tuning Menu", "» Felgi\n» Kolory\n» Hydraulika\n» Nitro\n» Stereo\n» Paint Job\n» Dodatkowe Obiekty", "Wybierz", "Zamknij");
	return 1;
}
CMD:ramp(playerid, cmdtext[])
{
	
	new ramptype;
	if(sscanf(cmdtext, "d", ramptype)) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "  Wpisz: /ramp <1-5> (<0 - wy³¹czenie>)");
		return 1;
	}
	if(ramptype < 0 || ramptype > 5)
	{
		SendClientMessage(playerid, COLOR_ERROR, "  Wpisz: /ramp <0-5>");
		return 1;
	}
	if(ramptype == 0)
	{
		SendClientMessage(playerid, COLOR_GREEN, ""chat"  Rampy zosta³y {b}wy³¹czone{/b}.");
		pInfo[playerid][player_ramp_pers] = -1;
		return 1;
	}
	
	if(ramptype == 1)
		pInfo[playerid][player_ramp_pers] = 1655;
	else if(ramptype == 2)
		pInfo[playerid][player_ramp_pers] = 1632;
	else if(ramptype == 3)
		pInfo[playerid][player_ramp_pers] = 1631;
	else if(ramptype == 4)
		pInfo[playerid][player_ramp_pers] = 8302;
	else if(ramptype == 5)
		pInfo[playerid][player_ramp_pers] = 1503;
	
	SendClientMessage(playerid, COLOR_GREEN, ""chat"  Typ ramp zosta³ zmieniony.");
	
	return 1;
}
CMD:100hp(playerid, params[]){
	
	if(GetPVarInt(playerid, "100hp") > gettime())
	{
		SendClientMessage(playerid, COLOR_ERROR, "» T¹ komende mo¿esz u¿yæ dopiero za %d sekund", GetPVarInt(playerid, "100hp") - gettime()); //wygenerowany
		return 1;
	}
	if(pInfo[playerid][player_last_damage] > gettime())
	{
		InfoBox(playerid,"Niestety nie mo¿esz tego zrobiæ!\nPrawdobodobnie uleczasz si siê podczas walki.\n\nMusisz odczekaæ 3 sekundy od zadanych obra¿eñ");
		return 1;
	}
	if(GetPlayerMoney(playerid) < 2500)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Aby si siê uleczyæ potrzebujesz 2.500$");
		return 1;
	}
	SetPlayerHealth(playerid, 100.0);
	SetPVarInt(playerid, "100hp", gettime() + 20);
	GivePlayerMoney(playerid, -2500);
	SendClientMessage(playerid, GetPlayerColor(playerid), "Uzupe³ni³eœ ¿ycie, kosztowa³o Ciê ono  2.500$");
	return 1;
}
CMD:armor(playerid, params[])
{
	if(GetPVarInt(playerid, "armorcmd") > gettime())
	{
		SendClientMessage(playerid, COLOR_ERROR, "» T¹ komendê mo¿esz u¿yæ dopiero za %d sekund", gettime() - GetPVarInt(playerid, "armorcmd")); //wygenerowany
		return 1;
	}
	if(pInfo[playerid][player_last_damage] > gettime())
	{
		InfoBox(playerid, "Niestety nie mo¿esz tego zrobiæ!\nPrawdobodobnie uleczasz siê podczas walki.\n\nMusisz odczekaæ 3 sekundy od zadanych obra¿eñ");
		return 1;
	}
	if(GetPlayerMoney(playerid) < 2500)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Aby odnowiæ kamizelkê potrzebujesz 2.500$"); //wygenerowany
		return 1;
	}
	SetPlayerArmour(playerid, 100.0);
	SetPVarInt(playerid, "armorcmd", gettime() + 10);
	
	GivePlayerMoney(playerid, -2500);
	SendClientMessage(playerid, GetPlayerColor(playerid), "Uzupe³ni³eœ kamizelkê, wyda³eœ na ni¹ {b}2.500$"); //wygenerowany
	return 1;
}
CMD:wyrzuc(playerid, params[])
{
	new temp;
	if(GetPlayerState(playerid)==PLAYER_STATE_PASSENGER)return SendClientMessage(playerid, COLOR_WHITE, ""chat" Musisz byæ kierowc¹ pojazdu, aby kogoœ wyrzuciæ.");
	new passes[100] = {-1, ...};
	foreach( new i : Player)
	{
		if(IsPlayerConnected(i) && IsPlayerInVehicle(i, GetPlayerVehicleID(playerid)) && GetPlayerState(i)==PLAYER_STATE_PASSENGER)
		{
			passes[temp] = i;
			temp++;
			
			if(temp > 99) break;
		}
	}
	if(passes[0] != -1)
	{
		for(new g=0;g<100;g++)
		{
			if(passes[g] != -1)
			{
				RemovePlayerFromVehicle(passes[g]);
			} else break;
		}
	}
	if(temp>0)
		SendClientMessage(playerid, COLOR_GRAY, "» Wyrzuci³eœ %d graczy z pojazdu.", temp);
	else
		SendClientMessage(playerid, COLOR_GRAY, "» Nikogo nie ma w Twoim samochodzie.");
	
	return 1;
}
CMD:dzien(playerid, params[])
{
	SetPlayerTime(playerid, 12, 30);
	return 1;
}
CMD:pogoda(playerid, cmdtext[])
{
	new w;
	if(sscanf(cmdtext, "d", w)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /pogoda <id pogody>"); //wygenerowany
	
	//if(w < 0 || w > 45) return SendClientMessage(playerid, COLOR_ERROR, "» Nieprawid³owe ID pogody. (0-45)"); //wygenerowany
	
	SetPlayerWeather(playerid, w);
	
	SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} »{/b} Zmieni³eœ(aœ) sobie pogodê ID %d.", w);
	return 1;
}
CMD:noc(playerid, params[])
{
	SetPlayerTime(playerid, 23, 30);
	return 1;
}
CMD:kill(playerid, params[])
{
	if(Rob[Active] && pRob[playerid][playing])return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz teraz u¿yæ tej komendy.");
	if(GetPVarInt(playerid, "killer") > gettime())
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Komenda zablokowana na %d sekund", GetPVarInt(playerid, "killer") - gettime()); //wygenerowany
		return 1;
	}
	SetPVarInt(playerid, "killer", gettime() + 10);
		
	SetPlayerHealth(playerid, 0.0);
	SendClientMessage(playerid, COLOR_GOLD, "Odda³eœ {b}¿ycie{/b} za {b}4FunServer{/b}"); //wygenerowany
	
	SendClientMessageToAll(COLOR_INFO, ""chat"  {%06x}%s{/b} pope³ni³ samobójstwo. (/kill)", GetPlayerColor(playerid)>>>8, playerNick(playerid));
	return 1;
}

CMD:savepos(playerid, cmdtext[])
{
	if(IsPlayerInRangeOfPoint(playerid,300.0,1104.2842,-1334.5215,13.7878) && Rob[Active])return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz u¿yæ tej komendy w tym miejscu.");
	GetPlayerPos(playerid, SavePos[0], SavePos[1], SavePos[2]);
	SendClientMessage(playerid, COLOR_GREEN, "* Zapisa³eœ swoj¹ pozycjê. Teraz ka¿dy bêdzie siê móg³ do niej teleportowaæ u¿ywaj¹c {b}/Telpos{/b}.");
	return 1;
}
CMD:telpos(playerid, cmdtext[])
{
	if(SavePos[0] == 0.0)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Na serwerze aktualnie nie ma zapisanej pozycji."); //
		return 1;
	}
	SetPlayerPos(playerid, SavePos[0], SavePos[1], SavePos[2]);
	if(IsPlayerInRangeOfPoint(playerid,300.0,1104.2842,-1334.5215,13.7878) && Rob[Active])
	{
		OnPlayerSpawn(playerid);
		SendClientMessage(playerid, COLOR_GREEN, "* Nie mo¿esz siê tam teleportowaæ podczas napadu.");
	}
	SendClientMessage(playerid, COLOR_GREEN, "* Teleportowa³eœ siê do zapisanego miejsca");
	return 1;
}

CMD:l(playerid, cmdtext[])
{
	new strtext[100];
	if(sscanf(cmdtext, "s[100]", strtext))
		return SendClientMessage(playerid, COLOR_INFO, ""chat" U¿yj: {b}/l <tekst>"); //wygenerowany
	
	if(strlen(strtext) > 100) return SendClientMessage(playerid, COLOR_ERROR, "» Wiadomoœæ mo¿e mieæ maksymalnie 100 znaków d³ugoœci!"); //wygenerowany
	
	new Float:Xl, Float:Yl, Float:Zl;
	new strl[140];
	GetPlayerPos(playerid, Xl, Yl, Zl);
	format(strl, sizeof(strl), "[Local chat] %s: %s", playerNick(playerid), strtext);
	SendClientMessage(playerid, COLOR_GOLD, strl); //wygenerowany
	foreach(Player, ll)
	{
		if(!IsPlayerInRangeOfPoint(ll, 50.0, Xl, Yl, Zl)) continue;
		if(ll == playerid) continue;
		SendClientMessage(ll, COLOR_GOLD, strl); //wygenerowany
	}
	return 1;
}
CMD:czysc(playerid, cmdp[])
{
	for(new c=0; c<100; c++)
		SendClientMessage(playerid, 0, " ");
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Twój czat zosta³ wyczyszczony."); //wygenerowany
	return 1;
}

CMD:vc(playerid, cmdtext[])
{
	new kolor1, kolor2;
	if(sscanf(cmdtext, "dd", kolor1, kolor2)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: {b}/vc [kolor1] [kolor2]"); //wygenerowany
	
	if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "» {b}Musisz{/b} byæ w pojeŸdzie!"); //wygenerowany
	if(kolor1 < 0 || kolor2 < 0 || kolor1 > 255 || kolor2 > 255) return SendClientMessage(playerid, COLOR_ERROR, "» Nieprawid³owe ID kolorów. (0-255)"); //wygenerowany
	
	ChangeVehicleColor(GetPlayerVehicleID(playerid), kolor1, kolor2);
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Zmieni³eœ kolor pojazdu."); //wygenerowany
	return 1;
}
CMD:sp(playerid, cmdp[])
{
	if(IsPlayerInRangeOfPoint(playerid,300.0,1104.2842,-1334.5215,13.7878) && Rob[Active])return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz u¿yæ tej komendy w tym miejscu.");
	GetPlayerPos(playerid, pInfo[playerid][player_save_pos][0], pInfo[playerid][player_save_pos][1], pInfo[playerid][player_save_pos][2]);
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Zapisa³eœ swoj¹ pozycjê. Mo¿esz j¹ póŸniej wczytaæ wpisuj¹c /Lp"); //wygenerowany
	return 1;
}

CMD:lp(playerid, cmdp[])
{
	if(pInfo[playerid][player_save_pos][0] == 0.0 && pInfo[playerid][player_save_pos][1] == 0.0 && pInfo[playerid][player_save_pos][2] == 0.0) return SendClientMessage(playerid, COLOR_ERROR, "» Nie masz zapisanej pozycji!"); //wygenerowany
	
	SetPlayerPos(playerid, pInfo[playerid][player_save_pos][0], pInfo[playerid][player_save_pos][1], pInfo[playerid][player_save_pos][2]);
	
	if(IsPlayerInRangeOfPoint(playerid,300.0,1104.2842,-1334.5215,13.7878) && Rob[Active])
	{
		OnPlayerSpawn(playerid);
		SendClientMessage(playerid, COLOR_GREEN, "* Nie mo¿esz siê tam teleportowaæ podczas napadu.");
	}
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Zosta³eœ przeniesiony do swojej wczeœniej zapisanej pozycji."); //wygenerowany
	return 1;
}

CMD:skok(playerid, cmdtext[])
{
	new wys;
	if(sscanf(cmdtext, "d", wys)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: {b}/skok [200-20000]"); //wygenerowany
	
	if(wys < 199 || wys > 20000) return SendClientMessage(playerid, COLOR_ERROR, "» Nieprawid³owa wysokoœæ. (200-20000)"); //wygenerowany
	
	new Float:jPos[3];
	GetPlayerPos(playerid, jPos[0], jPos[1], jPos[2]);
	SetPlayerPos(playerid, jPos[0], jPos[1], (jPos[2]+wys));
	GivePlayerWeapon(playerid, 46, 1);
	
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Wykonujesz skok spadochronowy z wysokoœci %d metrów.", (wys)); //wygenerowany
	return 1;
}
CMD:spadochron(playerid, params[])
{
	GivePlayerWeapon(playerid, 46, 1);
	SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} *{/b} Dosta³eœ {b}spadochron{/b}"); //wygenerowany
	return 1;
}
CMD:dystans(playerid, cmdtext[])
{
	new id;
	if(sscanf(cmdtext, "u", id)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: {b}/dystans <id/nick gracza>"); //wygenerowany
	
	if(id == playerid) return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz sprawdziæ dystansu do samego siebie!"); //wygenerowany
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!"); //wygenerowany
	
	new Float:pos1[3], Float:pos2[3];
	GetPlayerPos(playerid, pos1[0], pos1[1], pos1[2]);
	GetPlayerPos(id, pos2[0], pos2[1], pos2[2]);
	new Float:dys = floatsqroot(floatpower(pos1[0] - pos1[1], 2) + floatpower(pos2[0] - pos2[1], 2));
	
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Twój dystans do gracza {b}%s{/b} (%d) wynosi %.2f metrów.", playerNick(id), id, dys); //wygenerowany
	
	return 1;
}

CMD:do(playerid, cmdtext[])
{
	new id, tresc[256];
	if(sscanf(cmdtext, "us[256]", id, tresc)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: {b}/do <id/nick gracza> <tresc>{/b}"); //wygenerowany
	if(strlen(tresc) >= 255 || strlen(tresc) <= 1) return SendClientMessage(playerid, COLOR_ERROR, "» Treœæ musi mieæ minimum jeden znak a max 255"); //wygenerowany
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!"); //wygenerowany
	
	string2[0] = EOS;
	
	format(string2, sizeof(string2), "{%06x}%s{ffffff}, %s",GetPlayerColor(id)>>>8, playerNick(id), tresc);
	OnPlayerText(playerid, string2);
	return 1;
}

CMD:okradnij(playerid, params[])
{
	if(!pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, " Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do tej komendy.");
		return 1;
	}
	new id;
	if(sscanf(params, "u", id))
	{
		SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: {b}/okradnij <id/nick gracza>"); //wygenerowany
		return 1;
	}
	if(id == playerid)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz okradaæ siebie...");
		return 1;
	}
	if(!IsPlayerConnected(id))
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!"); //wygenerowany
		return 1;
	}
	new Float:xPos[3];
	GetPlayerPos(id, xPos[0], xPos[1], xPos[2]);
	
	if(!IsPlayerInRangeOfPoint(playerid, 1.5, xPos[0], xPos[1], xPos[2]))
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Musisz byæ bli¿ej ni¿ 1.5m od gracza by go okraœæ."); //wygenerowany
		return 1;
	}
	if(pInfo[id][player_afk] > 2)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz jest AFK!"); //wygenerowany
		return 1;
	}
	
	new c = GetPlayerMoney(id)/10;
	
	GivePlayerMoney(playerid, c);
	GivePlayerMoney(id, (-c));
	
	SendClientMessage(id, COLOR_RED, ""chat" %s (%d) okrad³ Ciê z %d$ ", playerNick(playerid), playerid, c);
	SendClientMessage(playerid, COLOR_RED, ""chat" okrad³eœ %s (%d) z %d$ ", playerNick(id), id, c);
	return 1;
}

CMD:idzdo(playerid, cmdtext[])
{
	
	new id;
	if(sscanf(cmdtext, "u", id))
	{
		SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: {b}/idzdo <id/nick gracza>"); //wygenerowany
		return 1;
	}
	if(id == playerid)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz teleportowaæ siê do siebie...");
		return 1;
	}
	
	if(!IsPlayerConnected(id))
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Ten nie jest pod³¹czony!"); //wygenerowany
		return 1;
	}
	
	if(pInfo[id][player_arena] > 0)
	{
		SendClientMessage(playerid, COLOR_ERROR, "Ten gracz aktualnie jest na arenie."); //wygenerowany
		return 1;
	}
	if(pInfo[id][player_jail])
	{
		SendClientMessage(playerid, 0xFF4444FF, "Ten gracz aktualnie jest w wiêzieniu"); //wygenerowany
		return 1;
	}
	if(is_event(id))
	{
		SendClientMessage(playerid, 0xFF4444FF, "Ten gracz aktualnie uczestniczy w evencie.");
		return 1;
	}
	if(pInfo[id][player_duel])
	{
		SendClientMessage(playerid, 0xFF4444FF, "Ten gracz aktualnie jest na solo.");
		return 1;
	}
	
	if(pInfo[id][player_teleports])
	{
		SendClientMessage(playerid, 0xFF4444FF, "Ten gracz aktualnie ma zablokowane teleporty.");
		return 1;
	}
	
	if(pInfo[ id ][player_gangWarTeam] != 0)
	{
		SendClientMessage(playerid, 0xFF4444FF, "Ten gracz aktualnie uczestniczy w wojnie gangów.");
		return 1;
	}
	
	if(pRob[id][playing] == true)
	{
		SendClientMessage(playerid, 0xFF4444FF, "Nie mo¿esz siê teleportowaæ do tego gracza.");
		return 1;
	}
	
	pInfo[id][player_tp_to] = playerid;
	pInfo[playerid][player_tp_to] = id;
	
	format(string2, sizeof(string2), " %s chce siê do Ciebie teleportowaæ czy wyra¿asz na to zgodê?", playerNick(playerid));
	Dialog_Show(id, DIALOG_TP, DIALOG_STYLE_MSGBOX, "Teleportacja", string2, "Tak", "Nie");
	return 1;
}

CMD:lock(playerid, cmdp[])
{
	if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "» {b}Musisz{/b} byæ w pojeŸdzie!"); //wygenerowany
	
	PlayerPlaySound(playerid, 1147, 0, 0, 0);
	GameTextForPlayer(playerid, "~r~Pojazd Zamkniety!", 2000, 3);
	new c = GetPlayerVehicleID(playerid);
	foreach(new i : Player)
	{
		if(!IsPlayerConnected(i)) continue;
		SetVehicleParamsForPlayer(c, i, 0, 1);
	}
	return 1;
}
CMD:unlock(playerid, cmdp[])
{
	if(!IsPlayerInAnyVehicle(playerid)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» {b}Musisz{/b} byæ w pojeŸdzie!"); //wygenerowany
	PlayerPlaySound(playerid, 1147, 0, 0, 0);
	GameTextForPlayer(playerid, "~w~Pojazd Otworzony!", 2000, 3);
	new c = GetPlayerVehicleID(playerid);
	foreach(new i : Player)
	{
		if(!IsPlayerConnected(i)) continue;
		SetVehicleParamsForPlayer(c, i, 0, 0);
	}
	return 1;
}
CMD:pm(playerid, cmdtext[])
{
	new id, tresc[140];
	
	if(sscanf(cmdtext, "us[140]", id, tresc)) 
		return SendClientMessage(playerid, COLOR_GREEN, ""chat" U¿yj: {b}/pm <id/nick gracza> <wiadomoœæ>"); //wygenerowany
	if(id == playerid) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz wys³aæ wiadomoœci do samego siebie!"); //wygenerowany
	if(!IsPlayerConnected(id)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!"); //wygenerowany
	if(strlen(tresc) > 100)
		return SendClientMessage(playerid, COLOR_ERROR, "» Treœæ wiadomoœci jest za d³uga!"); //wygenerowany
	if(pInfo[id][player_pm] == true)
		return SendClientMessage(playerid, COLOR_ERROR, "» Ten Gracz ma wy³¹czone prywatne wiadomoœci!"); //wygenerowany
	if(pInfo[playerid][player_pm] == true)
		return SendClientMessage(playerid, COLOR_ERROR, "» Masz wy³¹czone prywatne wiadomoœci /setpm."); //wygenerowany
	if(pInfo[playerid][player_jail])
		return SendClientMessage(playerid, COLOR_ERROR, "W wiêzieniu nie mo¿na u¿ywaæ tej komendy"); //wygenerowany
	WyslijPM(playerid, id, tresc);
	return 1;
}
 
CMD:zw(playerid, params[])
{
	if(Iter_Contains(c_h_players, playerid))return 0;
	if(pInfo[playerid][player_mute]) params[0] = EOS;
	if(pInfo[playerid][player_jail] > 0)
		return SendClientMessage(playerid, COLOR_ERROR, "W wiêzieniu nie mo¿na u¿ywaæ tej komendy"); //
	if(pInfo[playerid][player_zw]) 
	{
		SendClientMessage(playerid, COLOR_ERROR, "Jesteœ juz ZW");
		return 1;
	}
	if(IsPlayerEventItp(playerid))
	{
		SendClientMessage(playerid, COLOR_ERROR, "Nie mo¿esz u¿yæ tej komendy na evencie.");
		return 1;
	}
	
	SendClientMessageToAll(COLOR_GREEN, ""chat"  {b}%s{/b} mówi: {008aff}Zaraz Wracam", playerNick(playerid)); //wygenerowany
	
	if(IsPlayerInAnyVehicle(playerid))
	{
		SetVehicleVelocity(GetPlayerVehicleID(playerid), 0.0, 0.0, 0.0);
		RemovePlayerFromVehicle(playerid);
	}
	SendClientMessage(playerid, COLOR_GRAY, "Aby zostaæ odmro¿onym wpisz /jj");
	pInfo[playerid][player_zw] = true;
	RemoveFromEventAfk(playerid);
	TogglePlayerControllable(playerid, 0);
	TextDrawShowForPlayer(playerid, FlashTextdraw);

	return 1;
}
CMD:jj(playerid, params[])
{
	if(Iter_Contains(c_h_players, playerid))return 0;
	if(pInfo[playerid][player_mute]) params[0] = EOS;
	if(pInfo[playerid][player_jail] > 0)
		return SendClientMessage(playerid, COLOR_ERROR, "W wiêzieniu nie mo¿na u¿ywaæ tej komendy"); //
	if(!pInfo[playerid][player_zw]) return SendClientMessage(playerid, COLOR_ERROR, "Nie jesteœ ZW");
	if(IsPlayerEventItp(playerid))
	{
		SendClientMessage(playerid, COLOR_ERROR, "Nie mo¿esz u¿yæ tej komendy na evencie.");
		return 1;
	}
	if(!isnull(params))
	{
		SendClientMessageToAll(COLOR_GREEN, ""chat"  {b}%s{/b} mówi: {008aff}Ju¿ Jestem {808080}({FFFFFF}%s{808080})", playerNick(playerid), params); //wygenerowany
	}
	else
	{
		SendClientMessageToAll(COLOR_GREEN, ""chat"  {b}%s{/b} mówi: {008aff}Ju¿ Jestem", playerNick(playerid)); //wygenerowany
	}
	if(IsPlayerInAnyVehicle(playerid))
	{
		SetVehicleVelocity(GetPlayerVehicleID(playerid), 0.0, 0.0, 0.0);
		RemovePlayerFromVehicle(playerid);
	}
	TextDrawHideForPlayer(playerid, FlashTextdraw);

	pInfo[playerid][player_zw] = false;
	removeIsEvent(playerid);
	TogglePlayerControllable(playerid, 1);
	return 1;
}
CMD:siema(playerid, params[])
{
	if(pInfo[playerid][player_mute]) params[0] = EOS;
	if(!isnull(params))
	{
		SendClientMessageToAll(COLOR_GREEN, ""chat"  {b}%s{/b} mówi: {008aff}Siema {808080}({FFFFFF}%s{808080})", playerNick(playerid), params); //wygenerowany
	}
	else
	{
		SendClientMessageToAll(COLOR_GREEN, ""chat"  {b}%s{/b} mówi: {008aff}Siema", playerNick(playerid)); //wygenerowany
	}
	return 1;
}
CMD:czesc(playerid, params[])
{
	if(pInfo[playerid][player_mute]) params[0] = EOS;
	if(!isnull(params))
	{
		SendClientMessageToAll(COLOR_GREEN, ""chat"  {b}%s{/b} mówi: {008aff}Czeœæ {808080}({FFFFFF}%s{808080})", playerNick(playerid), params); //wygenerowany
	}
	else
	{
		SendClientMessageToAll(COLOR_GREEN, ""chat"  {b}%s{/b} mówi: {008aff}Czeœæ ", playerNick(playerid)); //wygenerowany
	}
	return 1;
}
CMD:pa(playerid, params[])
{
	if(pInfo[playerid][player_mute]) params[0] = EOS;
	if(!isnull(params))
	{
		SendClientMessageToAll(COLOR_GREEN, ""chat"  {b}%s{/b} mówi: {008aff}Pa Pa {808080}({FFFFFF}%s{808080})", playerNick(playerid), params); //wygenerowany
	}
	else
	{
		SendClientMessageToAll(COLOR_GREEN, ""chat"  {b}%s{/b} mówi: {008aff}Pa Pa", playerNick(playerid)); //wygenerowany
	}
	
	return 1;
}
CMD:nara(playerid, params[])
{
	if(pInfo[playerid][player_mute]) params[0] = EOS;
	if(!isnull(params))
	{
			SendClientMessageToAll(COLOR_GREEN, ""chat"  {b}%s{/b} mówi: {008aff}Nara {808080}({FFFFFF}%s{808080})", playerNick(playerid), params); //wygenerowany
	}
	else
	{
			SendClientMessageToAll(COLOR_GREEN, ""chat"  {b}%s{/b} mówi: {008aff}Nara ", playerNick(playerid)); //wygenerowany
	}
	return 1;
}
CMD:vips(playerid, cmds[])
{
	new vlist[1524] = "Vipy On-Line\n\n";
	new vcnt = 0;
	foreach(new i : Player)
	{
		if(!IsPlayerConnected(i)) continue;
		if(Iter_Contains(Vips, i))
		{
			vcnt++;
			format(vlist, sizeof(vlist), "%s%d. {%06x}%s (%d){FFFFFF}\n", vlist, vcnt, GetPlayerColor(i)>>> 8, playerNick(i), i);
		}
	}
	if(vcnt == 0) vlist = "\nBrak vipów online.\n";
	
	ShowPlayerDialog(playerid, 8844, DIALOG_STYLE_MSGBOX, "Vipy Online", vlist, "Zamknij", "");
	return 1;
}
CMD:admins(playerid, cmds[])
{
	new vlist[3064] = "Administratorzy On-Line\n\n";
	new vcnt = 0;
	
	new rannks[][] = {"-", "Moderator", "Junior admin", "Admin", "V Head Admin", "Head Admin"};
	for(new x=5;x!=0;x--)
	{
		foreach(new i : Player)
		{
			if(!IsPlayerConnected(i)) continue;
			if(pInfo[i][player_admin] == x)
			{
				vcnt++;
				format(vlist, sizeof(vlist), "%s%d. %s %s (%d){FFFFFF} - %s\n", vlist, vcnt, pInfo[i][player_admin] == 1 ? ("{00ff00}"):("{ff0000}"), playerNick(i), i,  pInfo[i][player_afk] > 3 ? ( "AFK" ) : ( rannks[x] ));
			}
		}
		strcat(vlist, "\n");
	}
	if(vcnt == 0) vlist = "\nBrak administratorów online.\n";
	
	ShowPlayerDialog(playerid, 8844, DIALOG_STYLE_MSGBOX, "Administratorzy Online", vlist, "Zamknij", "");
	return 1;
}
CMD:tune(playerid, cmdp[])
{
	if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "» {b}Musisz{/b} byæ w pojeŸdzie!"); //wygenerowany
	if(GetPlayerMoney(playerid) < 8000) return SendClientMessage(playerid, COLOR_ERROR, "» Potrzebujesz{b} 8000${/b}, by móc stuningowaæ pojazd!", "Potrzebujesz 8000$, by móc stuningowaæ pojazd!"); //wygenerowany
	
	GivePlayerMoney(playerid, -8000);
	TuneCar(GetPlayerVehicleID(playerid));
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Stuningowa³eœ pojazd za 8000$."); //wygenerowany
	
	if(IsVehicleDoczepianeObiekty(GetPlayerVehicleID(playerid))) Dialog_Show(playerid, DoczepianeObiektyDialog, DIALOG_STYLE_MSGBOX, "{00FF11}Doczepiane Obiekty!", "{00CDFF}UWAGA! W twoim pojeŸdzie mog¹ zostaæ {FFB300}doczepione dodatkowe obiekty!\n{00FFB3}Czy chcesz je doczepiæ? {B300FF}Opcja jest ca³kowicie za darmo!", "{00FF33}Doczep", "{00CDFF}Nie chcê");

	
	return 1;
}
CMD:cardive(playerid, cmdp[])
{
	if(pInfo[playerid][player_driftcouter]) return SendClientMessage(playerid, COLOR_ERROR, "Masz w³¹czony licznik driftu i nie mo¿esz u¿yæ tej komendy!");
	if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "» {b}Musisz{/b} byæ w pojeŸdzie!"); //wygenerowany
	
	new Float:cdive[3];
	GetVehiclePos(GetPlayerVehicleID(playerid), cdive[0], cdive[1], cdive[2]);
	SetVehiclePos(GetPlayerVehicleID(playerid), cdive[0], cdive[1], (cdive[2]+800.0));
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Wykonujesz {b}cardive{/b}..."); //wygenerowany
	return 1;
}


CMD:napraw(playerid, cmdp[])
{
	if(!IsPlayerInAnyVehicle(playerid))
		return SendClientMessage(playerid, COLOR_GOLD, "{339999}Nie jesteœ w ¿adnym pojeŸdzie."); //wygenerowany
	
	
	RepairVehicle(GetPlayerVehicleID(playerid));
	GameTextForPlayer(playerid, "~n~~n~~n~~n~~g~~h~Pojazd naprawiony", 1000, 5);
	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	return 1;
}

CMD:flip(playerid, cmdp[])
{
	if(!IsPlayerInAnyVehicle(playerid))
		return SendClientMessage(playerid, COLOR_GOLD, "{339999}Nie jesteœ w ¿adnym pojeŸdzie."); //wygenerowany
 
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
	
	new VehicleID, Float:X, Float:Y, Float:Z, Float:Angle;
	GetPlayerPos(playerid, X, Y, Z);
	VehicleID = GetPlayerVehicleID(playerid);
	GetVehicleZAngle(VehicleID, Angle);
	SetVehiclePos(VehicleID, X, Y, Z);
	SetVehicleZAngle(VehicleID, Angle);
	return 1;
}


CMD:stylwalki(playerid, cmdp[])
{
	Dialog_Show(playerid, DIALOG_STYLE_WALKI, DIALOG_STYLE_LIST, "Styl Walki", "Normalny\nKungFu\nBoks\nKneeHead\nGrabKick\nElBow", "Wybierz", "Zamknij");
	return 1;
}

CMD:bounty(playerid, cmdtext[])
{
	new id;
	if(sscanf(cmdtext, "u", id)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /bounty <id/nick gracza>"); //wygenerowany
	
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!"); //wygenerowany
	
	SendClientMessage(playerid, COLOR_GREEN, ""chat" Nagroda za zabicie gracza {b}%s (%d){/b} wynosi {b}%d{/b} Respektu.", playerNick(id), id, pInfo[id][player_bounty]);
	return 1;
}

CMD:stream(playerid, params[])
{
	Dialog_Show(playerid, DIALOG_STREAM, DIALOG_STYLE_INPUT, "Stream audio","Wklej poni¿ej stream do radia, które chcesz odtworzyæ.\n\n","Play","Anuluj");
	return 1;
}
Dialog:DIALOG_STREAM(playerid, response, listitem, inputtext[])
{	
	if(!response)
		return 1;
	PlayAudioStreamForPlayer(playerid,inputtext);
	return 1;
}
CMD:sendscore(playerid, cmdtext[])
{
	return SendClientMessage(playerid,COLOR_ERROR,"Komenda zablokowana.");
	/*new id, score, reason[64];
	if(sscanf(cmdtext, "dds[64]", id, score, reason)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /sendscore <id/nick gracza> <score> <powód>"); //wygenerowany
	
	SendScore(playerid, id, score, reason);
	
	return 1;*/
}
CMD:sendmoney(playerid, cmdtext[])
{
	new id, money;
	if(sscanf(cmdtext, "dd", id, money)) return SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /sendmoney <id/nick gracza> <kasa>"); //wygenerowany
	
	SendCash(playerid, id, money, false);
	return 1;
}


CMD:hitman(playerid, cmdtext[])
{
	new id, kwota;
	if(sscanf(cmdtext, "ud", id, kwota))
	{
		SendClientMessage(playerid, COLOR_ERROR, "» U¿yj: /hitman <id/nick gracza> <kwota (Exp)>"); //wygenerowany
		return 1;
	}
	if(!IsPlayerConnected(id))
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Ten Gracz nie jest pod³¹czony!"); //wygenerowany
		return 1;
	}
	if(kwota < 0)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Nieprawid³owa kwota."); //wygenerowany
		return 1;
	}
	if(kwota > GetPlayerScore(playerid))
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Nie masz tyle Respektu!"); //wygenerowany
		return 1;
	}
	if(kwota > 500)
	{
		SendClientMessage(playerid, COLOR_ERROR, "» Nagroda nie mo¿e byæ wiêksza ni¿ 500 XP!"); //wygenerowany
		return 1;
	}
	
	GivePlayerScore(playerid, -kwota);
	pInfo[id][player_bounty] += kwota;
	
	
	SendClientMessageToAll(0xFF761AFF, ""chat" %s (%d) wystawi³ nagrodê %d Respektu za zabicie gracza %s (%d). Razem jest %d respektu", playerNick(playerid), playerid, kwota, playerNick(id), id,pInfo[id][player_bounty]);
	return 1;
}


CMD:c4(playerid, params[])
{
	if(aEData[ev_on])
	{
		return SendClientMessage(playerid, COLOR_RED, "Nie mo¿esz podk³adaæ C4 podczas trwania eventu. ");
	}
	if(pInfo[playerid][player_bomb])
	{
		SendClientMessage(playerid, COLOR_RED, "» Mo¿esz pod³o¿yæ tylko jedn¹ bombê naraz!"); //wygenerowany
		return 1;
	}
	if(Iter_Contains(EventPlayers,playerid) && !aEData[ev_started] && pInfo[playerid][player_admin] == 0 && aEData[ev_lider] != playerid)
	{
		SendClientMessage(playerid, COLOR_RED, "» Chyba sobie kpisz"); //wygenerowany
		return 1;
	}
	GetPlayerPos(playerid, pInfo[playerid][player_bombpos][0], pInfo[playerid][player_bombpos][1], pInfo[playerid][player_bombpos][2]);
	GetXYInFrontOfPlayer(playerid, pInfo[playerid][player_bombpos][0], pInfo[playerid][player_bombpos][1], 0.7);
	
	SendClientMessage(playerid, 0x0066FFAA, ""chat" Bomba pod³o¿ona, eksplozja za {b}10 sekund{/b}."); //wygenerowany
	
	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);
	
	pInfo[playerid][player_bomb_object] = CreateDynamicObject(1252, pInfo[playerid][player_bombpos][0], pInfo[playerid][player_bombpos][1], pInfo[playerid][player_bombpos][2] - 0.8, 270, 0, 0);
	
	SetTimerEx("BombTimer", 10000, 0, "d", playerid);
	
	pInfo[playerid][player_bomb] = true;
	
	return 1;
}
Public:BombTimer(playerid)
{
	CreateExplosion(pInfo[playerid][player_bombpos][0], pInfo[playerid][player_bombpos][1], pInfo[playerid][player_bombpos][2], 11, 10);
	SendClientMessage(playerid, COLOR_GRAY, "Bomba zosta³a zdetonowana."); //wygenerowany
	DestroyDynamicObject(pInfo[playerid][player_bomb_object]);
	pInfo[playerid][player_bomb] = false;
	return 1;
}


CMD:p4s(playerid, cmdtext[])
{
	SendClientMessageToAll(COLOR_INFO, "{FF0000}*{/b} %s (%d) mówi ¿e {b}Polski 4FuN Server{/b} jest NAJLEPSZY!", playerNick(playerid), playerid);
	return 1;
}

CMD:zajebisty(playerid, cmdtext[])
{
	
	new rand;

	if((rand=strval(cmdtext), rand) == 0) rand = random(GetPlayerPoolSize());
	
	if(rand > MAX_PLAYERS) return 0;
	if(!IsPlayerConnected(rand)) return 0;
	SendClientMessageToAll(0xFF8000FF, "*** {FFFF00}%s {6699FF}(ID:%d) {00CC00}mówi ¿e {FF9966}%s {B8FF29}jest zajebisty/a ! =D", playerNick(playerid), playerid, playerNick(rand));
	return 1;
}

//addobjects

CMD:bombero(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 19330, 2, 0.166000, -0.038999, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000); //FIREMAN
	return 1;
}

CMD:policia(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 19161, 2, 0.078999, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000); //POLICE
	return 1;
}

CMD:hatmj(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 18639, 2, 0.131000, 0.019000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000); //HAT MJ
	return 1;
}

CMD:obrero(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 18638, 2, 0.148999, 0.031000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000); //WORKER
	return 1;
}

CMD:gorra(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 18939, 2, 0.164000, 0.001999, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000); //Gorare
	return 1;
}

CMD:hat(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 19488, 2, 0.121999, 0.000000, -0.005999, -83.199966, 98.200027, -2.500000, 1.000000, 1.000000, 1.000000); //sombrero
	return 1;
}

CMD:hatmg(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 19352, 2, 0.106999, 0.016000, -0.010999, 4.500000, 82.099990, -3.100001, 1.000000, 1.000000, 1.000000); //magicosombr
	return 1;
}

CMD:bolsa(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 19090, 2, -0.315999, 0.019999, 0.030000, 0.000000, 0.000000, 0.000000, 1.455999, 0.526000, 0.541000); //BAG
	return 1;
}

CMD:dj(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 19424, 2, 0.070999, -0.026000, -0.002000, -85.299987, 1.600005, -99.500000, 0.944001, 0.915000, 0.809999); //DJ
	return 1;
}

CMD:dloro(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 19078, 1, -1.000000, -0.517000, 0.000000, 0.000000, 0.299999, 10.499994, 8.673998, 9.400999, 7.410993);//dizfraz de loro
	return 1;
}

CMD:loro(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 19078, 4, -0.067000, 0.053999, 0.018000, -168.400039, -169.800003, -2.800000, 1.000000, 1.000000, 1.000000);//loro en hombro
	return 1;
}

CMD:parche(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 19085, 2, 0.090999, 0.035000, -0.015000, 106.599983, 83.199996, 0.800003, 1.000000, 1.000000, 1.000000);//parche
	return 1;
}

CMD:dildo(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 19086, 15, 0.051000, 0.000000, -0.424999, 0.000000, 0.000000, -102.100006, 1.000000, 1.000000, 1.000000);//dildo
	return 1;
}

CMD:chicken(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 19137, 2, 0.101000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000);//cabeza de pollo
	return 1;
}

CMD:dchicken(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 19137, 15, 0.040999, 0.000000, -0.130000, -86.300003, 106.100013, -96.100051, 7.741999, 4.874000, 5.584998);//disfraz de pollo
	return 1;
}

CMD:ciervo(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 19315, 1, -0.247999, 0.509999, -0.015999, 4.300004, 86.900024, 85.500015, 3.010000, 4.463000, 3.824000);//ciervo
	return 1;
}

CMD:cuernos1(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 19314, 2, 0.157000, 0.000000, 0.000000, -0.199999, -7.600006, -88.599998, 1.000000, 1.000000, 1.000000);//cuernos 1
	return 1;
}

CMD:cuernos2(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 19314, 2, 0.157000, 0.000000, 0.000000, 1.400000, -7.600006, -28.599973, 0.711000, 0.919999, 0.361999);//cuernos 2
	return 1;
}

CMD:dcalabaza(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 19320, 2, 0.000000, 0.000000, 0.000000, 4.299999, 72.999992, 3.199999, 3.594999, 3.787999, 4.951001);//disfraz de calabaza
	return 1;
}

CMD:cabezon(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 18963, 2, 0.261000, 0.084999, 0.004999, 4.999999, 85.400039, 84.699974, 2.097000, 2.627000, 3.033999);//cabezón
	return 1;
}

CMD:delfin(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 1607, 2, 0.267000, 0.000000, 0.000000, -0.199999, 81.199996, -3.499999, 1.135000, 1.000000, 1.126999);//delfin
	return 1;
}

CMD:tiburon(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 1608, 1, 0.000000, 0.000000, 0.000000, 0.499999, 89.200042, 0.199999, 1.000000, 1.000000, 1.000000);//tiburón
	return 1;
}

CMD:turtle(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 1609, 1, -0.358000, 0.000000, 0.170000, 0.000000, 93.099998, 0.000000, 1.427000, 1.509000, 1.641000);//tortuga
	return 1;
}

CMD:vaca(playerid, params[])
{
	SetPlayerAttachedObject(playerid, 0, 16442, 15, 0.000000, 0.000000, 0.259000, 0.000000, 0.000000, -104.400001, 1.000000, 1.000000, 1.000000);//vaca
	return 1;
}

LoopingAnim(playerid, animlib[], animname[], Float:Speed, looping, lockx, locky, lockz, lp, fs = 0)
{
	ApplyAnimation(playerid, animlib, animname, Speed, looping, lockx, locky, lockz, lp, fs);
	SendClientMessage(playerid, COLOR_BLUE, "Aby zatrzymaæ animacjê wpisz {b}/astop{/b}."); //wygenerowany
	return 1;
}

CMD:rece(playerid, params[])
{
	LoopingAnim(playerid, "PED", "handsup", 4.0, 0, 1, 1, 1, 0);
	return 1;
}

CMD:pijany(playerid, params[])
{
	LoopingAnim(playerid, "PED", "WALK_DRUNK", 4.0, 1, 1, 1, 1, -1);
	return 1;
}

CMD:pijak1(playerid, params[])
{
	LoopingAnim(playerid, "PAULNMAC", "PnM_Loop_A", 4.0, 1, 1, 1, 1, 0);
	return 1;
}

CMD:pijak2(playerid, params[])
{
	LoopingAnim(playerid, "PAULNMAC", "PnM_Loop_B", 4.0, 1, 1, 1, 1, 0);
	return 1;
}

CMD:bomba(playerid, params[])
{
	ClearAnimations(playerid);
	LoopingAnim(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:aresztuj(playerid, params[])
{
	LoopingAnim(playerid, "ped", "ARRESTgun", 4.0, 0, 1, 1, 1, -1);
	return 1;
}

CMD:smiech(playerid, params[])
{
	LoopingAnim(playerid, "RAPPING", "Laugh_01", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:ramiona(playerid, params[])
{
	LoopingAnim(playerid, "COP_AMBIENT", "Coplook_loop", 4.0, 1, 0, 0, 0, -1);
	return 1;
}

CMD:lez(playerid, params[])
{
	LoopingAnim(playerid, "BEACH", "bather", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:wal(playerid, params[])
{
	LoopingAnim(playerid, "PAULNMAC", "wank_loop", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:wytrysk(playerid, params[])
{
	LoopingAnim(playerid, "PAULNMAC", "wank_out", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:schowaj(playerid, params[])
{
	LoopingAnim(playerid, "ped", "cower", 3.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:wymiotuj(playerid, params[])
{
	LoopingAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:papa(playerid, params[])
{
	LoopingAnim(playerid, "PED", "endchat_03", 3.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:daj(playerid, params[])
{
	LoopingAnim(playerid, "DEALER", "DEALER_DEAL", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:pal(playerid, params[])
{
	LoopingAnim(playerid, "SMOKING", "M_smklean_loop", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:pal2(playerid, params[])
{
	LoopingAnim(playerid, "SMOKING", "F_smklean_loop", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:usiadz(playerid, params[])
{
	LoopingAnim(playerid, "BEACH", "ParkSit_M_loop", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:smierc(playerid, params[])
{
	LoopingAnim(playerid, "WUZI", "CS_Dead_Guy", 4.0, 0, 1, 1, 1, -1);
	return 1;
}

CMD:spij(playerid, params[])
{
	LoopingAnim(playerid, "INT_HOUSE", "BED_Loop_R", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:caluj(playerid, params[])
{
	LoopingAnim(playerid, "KISSING", "Playa_Kiss_02", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:ranny(playerid, params[])
{
	LoopingAnim(playerid, "SWEET", "Sweet_injuredloop", 4.0, 1, 0, 0, 1, 0);
	return 1;
}

CMD:taxi(playerid, params[])
{
	LoopingAnim(playerid, "ped", "IDLE_taxi", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:rozgladaj(playerid, params[])
{
	LoopingAnim(playerid, "ped", "roadcross", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:yes(playerid, params[])
{
	LoopingAnim(playerid, "GANGS", "Invite_Yes", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:no(playerid, params[])
{
	LoopingAnim(playerid, "GANGS", "Invite_No", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:myjrece(playerid, params[])
{
	LoopingAnim(playerid, "INT_HOUSE", "wash_up", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:medyk(playerid, params[])
{
	LoopingAnim(playerid, "MEDIC", "CPR", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:oh(playerid, params[])
{
	LoopingAnim(playerid, "MISC", "plyr_shkhead", 4.0, 0, 0, 0, 0, -1);
	return 1;
}

CMD:dowody(playerid, params[])
{
	LoopingAnim(playerid, "MISC", "Run_Dive", 4.0, 0, 1, 0, 1, 0);
	return 1;
}

CMD:wniebo(playerid, params[])
{
	LoopingAnim(playerid, "ON_LOOKERS", "lkup_loop", 4.0, 1, 1, 1, 1, -1);
	return 1;
}

CMD:spadam(playerid, params[])
{
	LoopingAnim(playerid, "TRAIN", "tran_stmb", 4.0, 0, 0, 0, 1, 0);
	return 1;
}

CMD:spadam2(playerid, params[])
{
	LoopingAnim(playerid, "TRAIN", "tran_hng", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:spadam3(playerid, params[])
{
	LoopingAnim(playerid, "TRAIN", "tran_gtup", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:start(playerid, params[])
{
	LoopingAnim(playerid, "CAR", "flag_drop", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:naprawia(playerid, params[])
{
	LoopingAnim(playerid, "CAR", "Fixn_Car_Loop", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:naprawil(playerid, params[])
{
	LoopingAnim(playerid, "CAR", "Fixn_Car_Out", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:chatauto(playerid, params[])
{
	LoopingAnim(playerid, "CAR_CHAT", "car_talkm_loop", 4.0, 1, 0, 0, 1, 0);
	return 1;
}

CMD:chatauto2(playerid, params[])
{
	LoopingAnim(playerid, "CAR_CHAT", "car_talkm_out", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:bagaznik(playerid, params[])
{
	LoopingAnim(playerid, "POOL", "POOL_Place_White", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:krzeslouderz(playerid, params[])
{
	LoopingAnim(playerid, "INT_OFFICE", "OFF_Sit_Crash", 4.0, 0, 0, 0, 1, 0);
	return 1;
}

CMD:krzeslowypij(playerid, params[])
{
	LoopingAnim(playerid, "INT_OFFICE", "OFF_Sit_Drink", 4.0, 0, 0, 0, 1, 0);
	return 1;
}

CMD:krzeslokomp(playerid, params[])
{
	LoopingAnim(playerid, "INT_OFFICE", "OFF_Sit_Type_Loop", 4.0, 1, 0, 0, 1, 0);
	return 1;
}

CMD:krzeslozegarek(playerid, params[])
{
	LoopingAnim(playerid, "INT_OFFICE", "OFF_Sit_Watch", 4.0, 0, 0, 0, 1, 0);
	return 1;
}

CMD:krzeslorozm1(playerid, params[])
{
	LoopingAnim(playerid, "MISC", "Seat_Talk_01", 4.0, 1, 0, 0, 1, 0);
	return 1;
}

CMD:krzeslorozm2(playerid, params[])
{
	LoopingAnim(playerid, "MISC", "Seat_Talk_02", 4.0, 1, 0, 0, 1, 0);
	return 1;
}

CMD:wypij(playerid, params[])
{
	LoopingAnim(playerid, "BAR", "dnk_stndM_loop", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:barman(playerid, params[])
{
	LoopingAnim(playerid, "BAR", "BARman_idle", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:barman2(playerid, params[])
{
	LoopingAnim(playerid, "BAR", "Barserve_loop", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:wyjmijbutelke(playerid, params[])
{
	LoopingAnim(playerid, "BAR", "Barserve_bottle", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:nalej(playerid, params[])
{
	LoopingAnim(playerid, "BAR", "Barserve_glass", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:jem(playerid, params[])
{
	LoopingAnim(playerid, "FOOD", "EAT_Burger", 3.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:jem2(playerid, params[])
{
	LoopingAnim(playerid, "FOOD", "FF_Sit_Eat1", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:jem3(playerid, params[])
{
	LoopingAnim(playerid, "FOOD", "FF_Sit_Eat2", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:jem4(playerid, params[])
{
	LoopingAnim(playerid, "FOOD", "FF_Sit_Eat3", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:polchodz(playerid, params[])
{
	LoopingAnim(playerid, "POLICE", "CopTraf_Come", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:polodejdz(playerid, params[])
{
	LoopingAnim(playerid, "POLICE", "CopTraf_Left", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:polstop(playerid, params[])
{
	LoopingAnim(playerid, "POLICE", "CopTraf_Stop", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:skok2(playerid, params[])
{
	LoopingAnim(playerid, "DAM_JUMP", "DAM_Launch", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:trup2(playerid, params[])
{
	LoopingAnim(playerid, "SWAT", "gnstwall_injurd", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:ratunku(playerid, params[])
{
	LoopingAnim(playerid, "BD_FIRE", "BD_Panic_03", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:krzeslo(playerid, params[])
{
	LoopingAnim(playerid, "INT_OFFICE", "OFF_Sit_Idle_Loop", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:trup(playerid, params[])
{
	LoopingAnim(playerid, "WUZI", "CS_Dead_Guy", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:calus(playerid, params[])
{
	LoopingAnim(playerid, "KISSING", "Playa_Kiss_02", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:sikaj(playerid, params[])
{
	LoopingAnim(playerid, "PAULNMAC", "Piss_in", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:st2(playerid, params[])
{
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
	return 1;
}

CMD:wt(playerid, params[])
{
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
	return 1;
}

CMD:drunk(playerid, params[])
{
	LoopingAnim(playerid, "PED", "WALK_DRUNK", 4.0, 1, 1, 1, 1, 0);
	return 1;
}

CMD:rap1(playerid, params[])
{
	LoopingAnim(playerid, "RAPPING", "RAP_B_Loop", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:lookout(playerid, params[])
{
	LoopingAnim(playerid, "SHOP", "ROB_Shifty", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:napad(playerid, params[])
{
	LoopingAnim(playerid, "SHOP", "ROB_Loop_Threat", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:hide(playerid, params[])
{
	LoopingAnim(playerid, "ped", "cower", 3.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:rzygaj(playerid, params[])
{
	LoopingAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:jedz(playerid, params[])
{
	LoopingAnim(playerid, "FOOD", "EAT_Burger", 3.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:machaj(playerid, params[])
{
	LoopingAnim(playerid, "ON_LOOKERS", "wave_loop", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:klepnij(playerid, params[])
{
	LoopingAnim(playerid, "SWEET", "sweet_ass_slap", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:deal(playerid, params[])
{
	LoopingAnim(playerid, "DEALER", "DEALER_DEAL", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:cpun(playerid, params[])
{
	LoopingAnim(playerid, "CRACK", "crckdeth2", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:rece2(playerid, params[])
{
	LoopingAnim(playerid, "DAM_JUMP", "DAM_Dive_Loop", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:rece3(playerid, params[])
{
	LoopingAnim(playerid, "COP_AMBIENT", "Coplook_loop", 4.0, 0, 1, 1, 1, -1);
	return 1;
}

CMD:siadaj(playerid, params[])
{
	LoopingAnim(playerid, "BEACH", "ParkSit_M_loop", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:fucku(playerid, params[])
{
	LoopingAnim(playerid, "PED", "fucku", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:taichi(playerid, params[])
{
	LoopingAnim(playerid, "PARK", "Tai_Chi_Loop", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:pij(playerid, params[])
{
	LoopingAnim(playerid, "BAR", "dnk_stndF_loop", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:inbedright(playerid, params[])
{
	LoopingAnim(playerid, "INT_HOUSE", "BED_In_R", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:inbedleft(playerid, params[])
{
	LoopingAnim(playerid, "INT_HOUSE", "BED_In_L", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:fotel(playerid, params[])
{
	LoopingAnim(playerid, "INT_HOUSE", "LOU_In", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:rap2(playerid, params[])
{
	LoopingAnim(playerid, "RAPPING", "RAP_B_Loop", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:rap3(playerid, params[])
{
	LoopingAnim(playerid, "RAPPING", "RAP_C_Loop", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:rap4(playerid, params[])
{
	LoopingAnim(playerid, "RAPPING", "Laugh_0", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:rap5(playerid, params[])
{
	LoopingAnim(playerid, "RAPPING", "RAP_B_IN", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:rap6(playerid, params[])
{
	LoopingAnim(playerid, "RAPPING", "RAP_A_IN", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:patrz(playerid, params[])
{
	LoopingAnim(playerid, "SHOP", "SHP_Serve_Start", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:opieraj(playerid, params[])
{
	LoopingAnim(playerid, "GANGS", "leanIDLE", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:yo2(playerid, params[])
{
	LoopingAnim(playerid, "GANGS", "hndshkaa", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:yo3(playerid, params[])
{
	LoopingAnim(playerid, "GANGS", "hndshkba", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:yo4(playerid, params[])
{
	LoopingAnim(playerid, "GANGS", "hndshkba", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:zolwik(playerid, params[])
{
	LoopingAnim(playerid, "GANGS", "hndshkda", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:yo(playerid, params[])
{
	LoopingAnim(playerid, "GANGS", "hndshkfa", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:carchat(playerid, params[])
{
	LoopingAnim(playerid, "CAR_CHAT", "car_talkm_out", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:krzycz(playerid, params[])
{
	LoopingAnim(playerid, "RIOT", "RIOT_shout", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:wtf(playerid, params[])
{
	LoopingAnim(playerid, "RIOT", "RIOT_ANGRY", 4.1, 0, 1, 1, 1, 1);
	return 1;
}

CMD:adhd(playerid, params[])
{
	LoopingAnim(playerid, "PED", "BIKE_fallR", 4.1, 0, 1, 1, 1, 0);
	return 1;
}

CMD:raczkuj(playerid, params[])
{
	LoopingAnim(playerid, "PED", "CAR_crawloutRHS", 4.1, 0, 1, 1, 1, 0);
	return 1;
}

CMD:down(playerid, params[])
{
	LoopingAnim(playerid, "BOX", "bxhwlki", 3.1, 0, 1, 1, 1, 0);
	return 1;
}

CMD:scratch(playerid, params[])
{
	LoopingAnim(playerid, "MISC", "Scratchballs_01", 3.0, 1, 0, 0, 0, 0, 1);
	return 1;
}

CMD:beach(playerid, params[])
{
	LoopingAnim(playerid, "BEACH", "SitnWait_loop_W", 4.0999, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:circle(playerid, params[])
{
	LoopingAnim(playerid, "CHAINSAW", "CSAW_Hit_2", 4.0999, 1, 1, 1, 1, 1, 1);
	return 1;
}

CMD:rofl(playerid, params[])
{
	LoopingAnim(playerid, "PED", "Crouch_Roll_L", 4.0999, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:getin(playerid, params[])
{
	LoopingAnim(playerid, "NEVADA", "NEVADA_getin", 4.0999, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:spray(playerid, params[])
{
	LoopingAnim(playerid, "SPRAYCAN", "spraycan_full", 4.0, 0, 0, 0, 0, 0, 1);
	return 1;
}

CMD:headbutt(playerid, params[])
{
	LoopingAnim(playerid, "WAYFARER", "WF_Fwd", 4.0, 0, 0, 0, 0, 0, 1);
	return 1;
}

CMD:lightcig(playerid, params[])
{
	LoopingAnim(playerid, "SMOKING", "M_smk_in", 3.0, 0, 0, 0, 0, 0, 1);
	return 1;
}

CMD:tapcig(playerid, params[])
{
	LoopingAnim(playerid, "SMOKING", "M_smk_tap", 3.0, 0, 0, 0, 0, 0, 1);
	return 1;
}

CMD:bat(playerid, params[])
{
	LoopingAnim(playerid, "BASEBALL", "Bat_IDLE", 4.0, 1, 1, 1, 1, 0, 1);
	return 1;
}

CMD:chant(playerid, params[])
{
	LoopingAnim(playerid, "RIOT", "RIOT_CHANT", 4.0, 1, 1, 1, 1, 0, 1);
	return 1;
}

CMD:finger(playerid, params[])
{
	LoopingAnim(playerid, "RIOT", "RIOT_FUKU", 2.0, 0, 0, 0, 0, 0, 1);
	return 1;
}

CMD:shouting(playerid, params[])
{
	LoopingAnim(playerid, "RIOT", "RIOT_shout", 4.0, 1, 0, 0, 0, 0, 1);
	return 1;
}

CMD:cop(playerid, params[])
{
	LoopingAnim(playerid, "SWORD", "sword_block", 50.0, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:lowbodypush(playerid, params[])
{
	LoopingAnim(playerid, "GANGS", "shake_carSH", 4.0, 0, 0, 0, 0, 0, 1);
	return 1;
}

CMD:push(playerid, params[])
{
	LoopingAnim(playerid, "GANGS", "shake_cara", 4.0, 0, 0, 0, 0, 0, 1);
	return 1;
}

CMD:medic(playerid, params[])
{
	LoopingAnim(playerid, "MEDIC", "CPR", 4.0, 0, 0, 0, 0, 0, 1);
	return 1;
}

CMD:rollfall(playerid, params[])
{
	LoopingAnim(playerid, "PED", "BIKE_fallR", 4.0, 0, 1, 1, 1, 0, 1);
	return 1;
}

CMD:boxanim(playerid, params[])
{
	LoopingAnim(playerid, "GYMNASIUM", "GYMshadowbox", 4.0, 1, 1, 1, 1, 0, 1);
	return 1;
}

CMD:fall(playerid, params[])
{
	LoopingAnim(playerid, "PED", "KO_skid_front", 4.0999, 0, 1, 1, 1, 0, 1);
	return 1;
}

CMD:fallback(playerid, params[])
{
	LoopingAnim(playerid, "PED", "FLOOR_hit_f", 4.0, 1, 0, 0, 0, 0, 1);
	return 1;
}

CMD:robman(playerid, params[])
{
	LoopingAnim(playerid, "SHOP", "ROB_Loop_Threat", 4.0, 1, 0, 0, 0, 0, 1);
	return 1;
}

CMD:smoke(playerid, params[])
{
	new sk;
	if(sscanf(params, "d", sk)) return SendClientMessage(playerid, COLOR_ERROR, "» Wpisz: /smoke [1-4]"); //wygenerowany
	
	switch(sk)
	{
		case 1:
			LoopingAnim(playerid, "SMOKING", "M_smklean_loop", 4.0, 1, 0, 0, 0, 0, 1);
		case 2:
			LoopingAnim(playerid, "SMOKING", "F_smklean_loop", 4.0, 1, 0, 0, 0, 0, 1);
		case 3:
			LoopingAnim(playerid, "SMOKING", "M_smkstnd_loop", 4.0, 1, 0, 0, 0, 0, 1);
		case 4:
			LoopingAnim(playerid, "SMOKING", "M_smk_out", 4.0, 1, 0, 0, 0, 0, 1);
		default: return 0;
	}
	return 1;
}

CMD:aim(playerid, params[])
{
	new am;
	if(sscanf(params, "d", am)) return SendClientMessage(playerid, COLOR_ERROR, "» Wpisz: /aim [1-3]"); //wygenerowany
	
	switch(am)
	{
		case 1:
			LoopingAnim(playerid, "PED", "gang_gunstand", 4.0, 1, 1, 1, 1, 1, 1);
		case 2:
			LoopingAnim(playerid, "PED", "Driveby_L", 4.0, 0, 1, 1, 1, 1, 1);
		case 3:
			LoopingAnim(playerid, "PED", "Driveby_R", 4.0, 0, 1, 1, 1, 1, 1);
		default: return 0;
	}
	return 1;
}

CMD:run(playerid, params[])
{
	new run;
	if(sscanf(params, "d", run)) return SendClientMessage(playerid, COLOR_ERROR, "» Wpisz: /run [1-9]"); //wygenerowany
	
	switch(run)
	{
		case 1:
			LoopingAnim(playerid, "FAT", "FatRun", 4.0, 1, 1, 1, 1, 1, 1);
		case 2:
			LoopingAnim(playerid, "PED", "run_player", 4.0, 1, 1, 1, 1, 1, 1);
		case 3:
			LoopingAnim(playerid, "PED", "jog_femaleA", 4.0, 1, 1, 1, 1, 1, 1);
		case 4:
			LoopingAnim(playerid, "PED", "jog_maleA", 4.0, 1, 1, 1, 1, 1, 1);
		case 5:
			LoopingAnim(playerid, "PED", "run_old", 4.0, 1, 1, 1, 1, 1, 1);
		case 6:
			LoopingAnim(playerid, "PED", "run_left", 4.0, 1, 1, 1, 1, 1, 1);
		case 7:
			LoopingAnim(playerid, "PED", "run_fatold", 4.0, 1, 1, 1, 1, 1, 1);
		case 8:
			LoopingAnim(playerid, "PED", "run_gang1", 4.0, 1, 1, 1, 1, 1, 1);
		case 9:
			LoopingAnim(playerid, "PED", "run_fat", 4.0, 1, 1, 1, 1, 1, 1);
		default: return 0;
	}
	return 1;
}

CMD:lay(playerid, params[])
{
	new lay;
	if(sscanf(params, "d", lay)) return SendClientMessage(playerid, COLOR_ERROR, "» Wpisz: /lay [1-9]"); //wygenerowany
	
	switch(lay)
	{
		case 1:
			LoopingAnim(playerid, "BEACH", "bather", 4.0, 1, 0, 0, 0, 0, 1);
		case 2:
			LoopingAnim(playerid, "BEACH", "parksit_w_loop", 4.0, 1, 0, 0, 0, 0, 1);
		case 3:
			LoopingAnim(playerid, "BEACH", "parksit_m_loop", 4.0, 1, 0, 0, 0, 0, 1);
		case 4:
			LoopingAnim(playerid, "BEACH", "lay_bac_loop", 4.0, 1, 0, 0, 0, 0, 1);
		case 5:
			LoopingAnim(playerid, "BEACH", "sitnwait_loop_w", 4.0, 1, 0, 0, 0, 0, 1);
		case 6:
			LoopingAnim(playerid, "SUNBATHE", "Lay_Bac_in", 3.0, 0, 1, 1, 1, 0, 5);
		case 7:
			LoopingAnim(playerid, "SUNBATHE", "batherdown", 3.0, 0, 1, 1, 1, 0, 1);
		case 8:
			LoopingAnim(playerid, "SUNBATHE", "parksit_m_in", 3.0, 0, 1, 1, 1, 0, 1);
		case 9:
			LoopingAnim(playerid, "CAR", "Fixn_Car_Loop", 4.0, 1, 0, 0, 0, 0, 1);
		default: return 0;
	}
	return 1;
}

CMD:wave(playerid, params[])
{
	new wv;
	if(sscanf(params, "d", wv)) return SendClientMessage(playerid, COLOR_ERROR, "» Wpisz: /wave [1-5]"); //wygenerowany
	
	switch(wv)
	{
		case 1:
			LoopingAnim(playerid, "ON_LOOKERS", "wave_loop", 4.0, 1, 0, 0, 0, 0, 1);
		case 2:
			LoopingAnim(playerid, "BD_Fire", "BD_GF_Wave", 4.0, 0, 0, 0, 0, 0, 1);
		case 3:
			LoopingAnim(playerid, "RIOT", "RIOT_CHANT", 4.0, 1, 1, 1, 1, 0, 1);
		case 4:
			LoopingAnim(playerid, "WUZI", "Wuzi_Follow", 5.0, 0, 0, 0, 0, 0, 1);
		case 5:
			LoopingAnim(playerid, "KISSING", "gfwave2", 4.0, 0, 0, 0, 0, 0, 1);
		default: return 0;
	}
	return 1;
}

CMD:chat(playerid, params[])
{
	new ch;
	if(sscanf(params, "d", ch)) return SendClientMessage(playerid, COLOR_ERROR, "» Wpisz: /chat [1-3]"); //wygenerowany
	
	switch(ch)
	{
		case 1:
			LoopingAnim(playerid, "PED", "IDLE_CHAT", 2.0, 1, 0, 0, 1, 1, 1);
		case 2:
			LoopingAnim(playerid, "MISC", "IDLE_CHAT_02", 2.0, 1, 0, 0, 1, 1, 1);
		case 3:
			LoopingAnim(playerid, "BAR", "Barcustom_order", 3.0, 0, 0, 0, 0, 0, 1);
		default: return 0;
	}
	return 1;
}

CMD:walk(playerid, params[])
{
	new wk;
	if(sscanf(params, "d", wk)) return SendClientMessage(playerid, COLOR_ERROR, "» Wpisz: /walk [1-9]"); //wygenerowany
	
	switch(wk)
	{
		case 1:
			LoopingAnim(playerid, "PED", "WALK_gang1", 4.0999, 1, 1, 1, 1, 1, 1);
		case 2:
			LoopingAnim(playerid, "PED", "WALK_gang2", 4.0999, 1, 1, 1, 1, 1, 1);
		case 3:
			LoopingAnim(playerid, "FAT", "FatWalk", 4.0999, 1, 1, 1, 1, 1, 1);
		case 4:
			LoopingAnim(playerid, "WUZI", "CS_Wuzi_pt1", 4.0999, 1, 1, 1, 1, 1, 1);
		case 5:
			LoopingAnim(playerid, "WUZI", "Wuzi_walk", 3.0, 1, 1, 1, 1, 1, 1);
		case 6:
			LoopingAnim(playerid, "POOL", "Pool_walk", 3.0, 1, 1, 1, 1, 1, 1);
		case 7:
			LoopingAnim(playerid, "PED", "Walk_player", 3.0, 1, 1, 1, 1, 1, 1);
		case 8:
			LoopingAnim(playerid, "PED", "Walk_old", 3.0, 1, 1, 1, 1, 1, 1);
		case 9:
			LoopingAnim(playerid, "PED", "Walk_fatold", 3.0, 1, 1, 1, 1, 1, 1);
		default: return 0;
	}
	return 1;
}

CMD:look(playerid, params[])
{
	new lk;
	if(sscanf(params, "d", lk)) return SendClientMessage(playerid, COLOR_ERROR, "» Wpisz: /look [1-4]"); //wygenerowany
	
	switch(lk)
	{
		case 1:
			LoopingAnim(playerid, "ON_LOOKERS", "lkup_loop", 3.0, 1, 0, 0, 0, 0, 1);
		case 2:
			LoopingAnim(playerid, "ON_LOOKERS", "lkaround_loop", 3.0, 1, 0, 0, 0, 0, 1);
		case 3:
			LoopingAnim(playerid, "PED", "flee_lkaround_01", 3.0, 1, 1, 1, 1, 1, 1);
		case 4:
			LoopingAnim(playerid, "BAR", "Barserve_bottle", 3.0, 0, 1, 1, 1, 0, 1);
		default: return 0;
	}
	return 1;
}

CMD:shout(playerid, params[])
{
	new st;
	if(sscanf(params, "d", st)) return SendClientMessage(playerid, COLOR_ERROR, "» Wpisz: /st [1-3]"); //wygenerowany
	
	switch(st)
	{
		case 1:
			LoopingAnim(playerid, "ON_LOOKERS", "shout_loop", 3.0, 1, 0, 0, 0, 0, 6);
		case 2:
			LoopingAnim(playerid, "ON_LOOKERS", "shout_01", 3.0, 1, 0, 0, 0, 0, 1);
		case 3:
			LoopingAnim(playerid, "ON_LOOKERS", "shout_02", 3.0, 1, 0, 0, 0, 0, 1);
		default: return 0;
	}
	return 1;
}

CMD:bj(playerid, params[])
{
	new bj;
	if(sscanf(params, "d", bj)) return SendClientMessage(playerid, COLOR_ERROR, "» Wpisz: /bj [1-3]"); //wygenerowany
	
	switch(bj)
	{
		case 1:
			LoopingAnim(playerid, "BLOWJOBZ", "BJ_STAND_END_W", 4.0, 0, 1, 1, 1, 0, 1);
		case 2:
			LoopingAnim(playerid, "BLOWJOBZ", "BJ_STAND_END_P", 4.0, 0, 1, 1, 1, 0, 1);
		case 3:
			LoopingAnim(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_W", 4.0, 0, 1, 1, 1, 0, 1);
		default: return 0;
	}
	return 1;
}

CMD:swat(playerid, params[])
{
	new as;
	if(sscanf(params, "d", as)) return SendClientMessage(playerid, COLOR_ERROR, "» Wpisz: /swat [1-6]"); //wygenerowany
	
	switch(as)
	{
		case 1:
			LoopingAnim(playerid, "SWAT", "gnstwall_injurd", 4.0, 0, 1, 1, 1, 0, 1);
		case 2:
			LoopingAnim(playerid, "SWAT", "JMP_Wall1m_180", 4.0, 0, 1, 1, 1, 0, 1);
		case 5:
			LoopingAnim(playerid, "SWAT", "swt_breach_01", 4.0, 0, 1, 1, 1, 0, 1);
		case 6:
			LoopingAnim(playerid, "SWAT", "swt_breach_02", 4.0, 0, 1, 1, 1, 0, 1);
		default: return 0;
	}
	return 1;
}

CMD:lean(playerid, params[])
{
	new ln;
	if(sscanf(params, "d", ln)) return SendClientMessage(playerid, COLOR_ERROR, "» Wpisz: /lean [1-2]"); //wygenerowany
	
	switch(ln)
	{
		case 1:
			LoopingAnim(playerid, "GANGS", "leanIDLE", 4.0, 0, 1, 1, 1, 0, 1);
		case 2:
			LoopingAnim(playerid, "MISC", "Plyrlean_loop", 4.0, 0, 1, 1, 1, 0, 1);
		default: return 0;
	}
	return 1;
}

CMD:stance(playerid, params[])
{
	new stance;
	if(sscanf(params, "d", stance)) return SendClientMessage(playerid, COLOR_ERROR, "» Wpisz: /stance [1-9]"); //wygenerowany
	
	switch(stance)
	{
		case 1:
			LoopingAnim(playerid, "DEALER", "DEALER_IDLE", 4.0, 1, 0, 0, 0, 0, 1);
		case 2:
			LoopingAnim(playerid, "PED", "WOMAN_IDLESTANCE", 4.0, 1, 0, 0, 0, 0, 1);
		case 3:
			LoopingAnim(playerid, "PED", "CAR_HOOKERTALK", 4.0, 1, 0, 0, 0, 0, 1);
		case 4:
			LoopingAnim(playerid, "FAT", "FatIdle", 4.0, 1, 0, 0, 0, 0, 1);
		case 5:
			LoopingAnim(playerid, "WUZI", "Wuzi_Stand_Loop", 4.0, 1, 0, 0, 0, 0, 1);
		case 6:
			LoopingAnim(playerid, "GRAVEYARD", "mrnf_loop", 4.0, 1, 0, 0, 0, 0, 1);
		case 7:
			LoopingAnim(playerid, "GRAVEYARD", "mrnm_loop", 4.0, 1, 0, 0, 0, 0, 1);
		case 8:
			LoopingAnim(playerid, "GRAVEYARD", "prst_loopa", 4.0, 1, 0, 0, 0, 0, 1);
		case 9:
			LoopingAnim(playerid, "PED", "idlestance_fat", 4.0, 1, 0, 0, 0, 0, 1);
		default: return 0;
	}
	return 1;
}

CMD:hike(playerid, params[])
{
	new hike;
	if(sscanf(params, "d", hike)) return SendClientMessage(playerid, COLOR_ERROR, "» Wpisz: /hike [1-3]"); //wygenerowany
	
	switch(hike)
	{
		case 1:
			LoopingAnim(playerid, "MISC", "hiker_pose", 4.0, 1, 0, 0, 0, 0, 1);
		case 2:
			LoopingAnim(playerid, "MISC", "hiker_pose_l", 4.0, 1, 0, 0, 0, 0, 1);
		case 3:
			LoopingAnim(playerid, "PED", "idle_taxi", 3.0, 0, 0, 0, 0, 0, 1);
		default: return 0;
	}
	return 1;
}

CMD:face(playerid, params[])
{
	new face;
	if(sscanf(params, "d", face)) return SendClientMessage(playerid, COLOR_ERROR, "» Wpisz: /face [1-6]"); //wygenerowany
	
	switch(face)
	{
		case 1:
			LoopingAnim(playerid, "PED", "facanger", 3.0, 1, 1, 1, 1, 1, 1);
		case 2:
			LoopingAnim(playerid, "PED", "facgum", 3.0, 1, 1, 1, 1, 1, 1);
		case 3:
			LoopingAnim(playerid, "PED", "facsurp", 3.0, 1, 1, 1, 1, 1, 1);
		case 4:
			LoopingAnim(playerid, "PED", "facsurpm", 3.0, 1, 1, 1, 1, 1, 1);
		case 5:
			LoopingAnim(playerid, "PED", "factalk", 3.0, 1, 1, 1, 1, 1, 1);
		case 6:
			LoopingAnim(playerid, "PED", "facurios", 3.0, 1, 1, 1, 1, 1, 1);
		default: return 0;
	}
	return 1;
}

CMD:tancz(playerid, params[])
{
	new dancestyle;
	if(sscanf(params, "d", dancestyle)) return SendClientMessage(playerid, COLOR_ERROR, "» Wpisz: /tancz [1-3]"); //wygenerowany
	
	switch(dancestyle)
	{
		case 1: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE1);
		case 2: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE2);
		case 3:	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE3);
		default: return 0;
	}
	return 1;
}

CMD:astop(playerid, params[])
{
	ClearAnimations(playerid);
	return 1;
}

CMD:anim(playerid, params[])
{
	static str[4600];
	str[0] = EOS;
	//strcat(str, "Animacje na serwerze:\n");
	strcat(str, "\n/rece \n/pijany \n/pijak1 \n/pijak2 \n/bomba \n/aresztuj\n");
	strcat(str, "\n/smiech \n/ramiona \n/lez \n/wal \n/wytrysk \n/schowaj\n");
	strcat(str, "\n/wymiotuj \n/pa \n/daj \n/pal \n/pal2 \n/usiadz\n");
	strcat(str, "\n/smierc \n/spij \n/caluj \n/ranny \n/taxi \n/rozgladaj \n/yes \n/no\n");
	strcat(str, "\n/myjrece \n/medyk \n/oh \n/dowody \n/wniebo \n/spadam \n/spadam2 \n/spadam3\n");
	strcat(str, "\n/start \n/naprawia \n/naprawil \n/chatauto \n/chatauto2 \n/bagaznik\n");
	strcat(str, "\n/krzeslouderz \n/krzeslowypij \n/krzeslokomp \n/krzeslozegarek\n");
	strcat(str, "\n/krzeslorozm1 \n/krzeslorozm2 \n/wypij \n/barman \n/barman2 \n/wyjmijbutelke\n");
	strcat(str, "\n/nalej \n/jem \n/jem2 \n/jem3 \n/jem4 \n/polchodz \n/polodejdz \n/polstop\n");
	strcat(str, "\n/skok2 \n/trup2 \n/ratunku \n/krzeslo \n/trup \n/calus \n/sikaj \n/st \n/wt \n/drunk\n");
	strcat(str, "\n/rap1 \n/lookout \n/napad \n/hide \n/rzygaj \n/jedz \n/machaj \n/klepnij \n/deal\n");
	strcat(str, "\n/cpun \n/rece \n/rece \n/rece2 \n/rece3 \n/siadaj \n/fucku \n/taichi \n/pij\n");
	strcat(str, "\n/inbedleft \n/inbedright \n/fotel \n/rap \n/rap2 \n/rap3 \n/rap4 \n/rap5 \n/rap6\n");
	strcat(str, "\n/patrz \n/opieraj \n/yo \n/yo2 \n/yo3 \n/yo4 \n/zolwik \n/carchat \n/krzycz \n/wtf\n");
	strcat(str, "\n/adhd \n/raczkuj \n/down \n/scratch \n/beach \n/circle \n/rofl \n/getin \n/spray \n");
	strcat(str, "\n/headbutt \n/lightcig \n/tapcig \n/bat \n/chant \n/finger \n/shouting \n/cop\n");
	strcat(str, "\n/lowbodypush \n/push \n/medic \n/rollfall \n/boxanim \n/fall \n/fallback \n/robman\n");
	strcat(str, "\n/smoke [1-4] \n/aim [1-3] \n/run [1-9] \n/lay [1-9] \n/wave [1-5] \n/walk [1-9]\n");
	strcat(str, "\n/look [1-4] \n/shout [1-3] \n/bj [1-3] \n/swat [1-6] \n/lean [1-2] \n/stance [1-9]\n");
	strcat(str, "\n/hike [1-3] \n/face [1-6] \n/tancz [1-3] \n/chat [1-3]\n");
	
	Dialog_Show(playerid, DIALOG_CMD_SEND, DIALOG_STYLE_LIST, "Aby zatrzymaæ animacjê wpisz /astop", str, "Uruchom", "Anuluj");
	return 1;
}

CMD:labirynt(playerid, cmdtext[])
{
	
 	pInfo[playerid][player_inlabirynt] = true;
	SetPlayerInterior(playerid, 0);
	
	Streamer_ToggleIdleUpdate(playerid, 1);
	Streamer_ToggleItemUpdate(playerid, 0, 1);
	
	if(pInfo[playerid][player_inlabirynt])
	{
		new rand = random(sizeof(LabyrinthFinish));
		SetPlayerCheckpoint(playerid, LabyrinthFinish[rand][0], LabyrinthFinish[rand][1], LabyrinthFinish[rand][2], 5);
		SetPlayerPos(playerid,1154.4518,1360.0472,10.8203);
		
	}
	ResetPlayerWeapons(playerid);
	SendClientMessage(playerid,COLOR_YELLOW,""chat" Jesteœ w labiryncie. PrzejdŸ go bezpiecznie, nagroda czeka. Aby opuœciæ wpisz /lbexit.");
	return 1;
}

CMD:labiryntexit(playerid, cmdtext[])
{
 	if(!pInfo[playerid][player_inlabirynt])
	{
		SendClientMessage(playerid,COLOR_WHITE,""chat" Musisz byæ w labiryncie, aby go opuœciæ.");
		return 1;
	}
	pInfo[playerid][player_inlabirynt] = false;
	OnPlayerSpawn(playerid);
	DisablePlayerCheckpoint(playerid);
 	DisablePlayerCheckpoint(playerid);
	return 1;
}

CMD:brondnia(playerid, params[])
{
	format(string2,
			sizeof(string2), 
			"Broñ dnia to taki ma³y event za zabijanie ni¹ dostajemy dodatkowy respekt.\n losuje siê co uruchomienie servera.\n\nAktualna broñ dnia to %s (%d)", GetWeaponNameEx(gmData[server_gunday]), gmData[server_gunday]);
		
	InfoBox(playerid, string2);
	return 1;
}
 
CMD:flo(playerid, params[])
{
	if(Iter_Contains(EventPlayers, playerid))
		return SendClientMessage(playerid, COLOR_ERROR, "» Na Evencie nie mo¿na u¿ywaæ tej komendy :)");
		
	if(GetPVarInt(playerid, "flo_command") > gettime())
	{
		SendClientMessage(playerid, COLOR_ERROR, "» T¹ komende mo¿esz u¿yæ dopiero za %d sekund.", GetPVarInt(playerid, "flo_command") - gettime()); //
		return 1;
	}
	if(pInfo[playerid][player_arena] != 0)
	{
		SendClientMessage(playerid, COLOR_INFO2, "Nie mo¿esz u¿ywac tej komendy przebywaj¹c na arenie.");
		return 1;
	}
	
	if(IsPlayerInAnyVehicle(playerid))
	{
		SendClientMessage(playerid, COLOR_INFO2, "Wysiadz z pojazdu zanim uzyjesz {b}/flo{/b}.");
		return 1;
	}
	
	if(!IsPlayerSpawned(playerid))
	{
		SendClientMessage(playerid, COLOR_INFO2, "Musisz byc zespawnowany aby uzyc rsp.");
		return 1;
	}
	
	 
	if(pInfo[playerid][player_afk]>3)
		SendClientMessage(playerid,COLOR_ERROR, "Jestes AFK! Prawdpodobnie masz laga i musisz od nowa po³¹czyæ siêz serverem!");
	
	SetPVarInt(playerid, "flo_command", gettime() + 2);
	
	new c = GetTickCount();
	
	new Float:HP[2], Float:PPos[4], Weapons[10], Ammos[10], skinID, vwID, intID, currentWeapon;
	GetPlayerPos(playerid, PPos[0], PPos[1], PPos[2]);
	GetPlayerFacingAngle(playerid, PPos[3]);
	GetPlayerHealth(playerid, HP[0]);
	GetPlayerArmour(playerid, HP[1]);
	
	skinID = GetPlayerSkin(playerid);
	vwID = GetPlayerVirtualWorld(playerid);
	intID = GetPlayerInterior(playerid);
	currentWeapon = GetPlayerWeapon(playerid);
	
	for(new Order = 0; Order < 9; Order++)
		GetPlayerWeaponData(playerid, Order, Weapons[Order], Ammos[Order]);
	
	
	pInfo[playerid][player_sync] = true;
		
	SpawnPlayer(playerid);
		
	SetPlayerHealth(playerid, HP[0]);
	SetPlayerArmour(playerid, HP[1]);
	SetPlayerPos(playerid, PPos[0], PPos[1], PPos[2]);
	SetPlayerFacingAngle(playerid, PPos[3]);
	
	for(new Order = 0; Order < 9; Order++)
		if(Ammos[Order] > 0)
			GivePlayerWeapon(playerid, Weapons[Order], Ammos[Order]);
		
	SetPlayerSkin(playerid, skinID);
	SetPlayerInterior(playerid, intID);
	SetPlayerVirtualWorld(playerid, vwID);
	SetPlayerArmedWeapon(playerid, currentWeapon);
	
	SendClientMessage(playerid, COLOR_INFO3, ""chat" Respawn wykonany w {b}%02dms{/b}.", GetTickCount()-c);
	return 1;
}
 
 
CMD:toadmin(playerid, params[])
{
	
	if(!Iter_Count(Admins)) return SendClientMessage(playerid, COLOR_ERROR, " Niestety aktualnie nie ma ¿adnego administratora online");
	
	if(isnull(params)) return SendClientMessage(playerid, COLOR_ERROR, " Wpisz /toadmin <wiadomoœæ>");
	if(!(3 <= strlen(params) <= 84)) return SendClientMessage(playerid, COLOR_ERROR, " Wiadomoœæ nie mo¿e mieæ wiêcej ni¿ 84 znaków a mniej ni¿ 3");
	
	SendAdminsMessage(COLOR_BURLYWOOD_3, "DO ADMINÓW %s (%d): {FF0000}%s", playerNick(playerid), playerid, params);
	SendAdminsMessage(COLOR_BURLYWOOD_3, "Aby odpisaæ na t¹ wiadomoœæ wpisz {b}/toplayer %d <wiadomoœæ>{/b}.", playerid);
	
	SendClientMessage(playerid, COLOR_ROSY_BROWN_4, " Wysla³eœ wiadomoœæ do %d adminów. Czekaj na odpowiedŸ.", Iter_Count(Admins));
	return 1;
}
 
CMD:toplayer(playerid, params[])
{
	
	RankAdmin(playerid, R_JADMIN);
	if(isnull(params)) return SendClientMessage(playerid, COLOR_ERROR, " Wpisz /toplayer <id gracza> <wiadomoœæ>");
	
	new id, buff[140];
	
	if(sscanf(params, "us[140]", id, buff)) 
		return SendClientMessage(playerid, COLOR_GREEN, ""chat" U¿yj: {b}/toplayer <id/nick gracza> <wiadomoœæ>"); //wygenerowany
	if(id == playerid) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Nie mo¿esz wys³aæ wiadomoœci do samego siebie!"); //wygenerowany
	if(!IsPlayerConnected(id)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Ten gracz nie jest pod³¹czony!"); //wygenerowany
		
	if(!(10 <= strlen(buff) <= 84)) 
		return SendClientMessage(playerid, COLOR_ERROR, " Wiadomoœæ nie mo¿e mieæ wiêcej ni¿ 84 znaków a mniej ni¿ 10");
	
 
	SendClientMessage(id, COLOR_YELLOW_3, "OdpowiedŸ od admina %s (%d): %s", playerNick(playerid), playerid, buff);
	SendClientMessage(playerid, COLOR_YELLOW_3, "Wysla³eœ odpowiedŸ graczowi %s (%d): %s", playerNick(id), id, buff);
	return 1;
}

CMD:cb(playerid, params[])
{
	if(!IsPlayerInAnyVehicle(playerid))
	{
	    SendClientMessage(playerid, COLOR_ERROR, " Musisz byæ w pojedzie!");
	    return 1;
	}

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{
	    SendClientMessage(playerid, COLOR_ERROR, " Musisz byæ kierowc¹.");
	    return 1;
	}

	new nChannel = strval(params);

	if(strlen(params) < 1 || !IsNumeric(params) || nChannel < 0 || nChannel > 22)
	{
	    SendClientMessage(playerid, COLOR_ERROR, "  U¿yj /cb [0-22]");
	    return 1;
	}

	pInfo[playerid][player_cbchannel] = nChannel;

	SendClientMessage(playerid, COLOR_GREEN, "* Zmieni³eœ(aœ) kana³ CB na {b}%d{/b}.", nChannel);

	return 1;
}
CMD:glitch(playerid, params[])
{
	if(pInfo[playerid][player_glitchTest] == 1) return SendClientMessage(playerid, -1, "Jesteœ ju¿ na arenie glitch!");
	pInfo[playerid][player_glitchCount][0] = 0; pInfo[playerid][player_glitchCount][1] = 0; pInfo[playerid][player_glitchCount][2] = 0; pInfo[playerid][player_glitchCount][3] = 0;
	pInfo[playerid][player_glitchTest] = 1;
 
	SetPlayerPos(playerid, 1414.453, 2.553, 1000.925);
	SetPlayerInterior(playerid, 1);
	SetPlayerTeam(playerid, MAX_PLAYERS+1);
	
	ResetPlayerWeapons(playerid);
	
	SetPlayerVirtualWorld(playerid,42);
	
	GivePlayerWeapon(playerid, 24, 7);
	SetPlayerHealth(playerid, 9999999.0);
    return 1;
}

CMD:me(playerid,params[])
{
	if(pInfo[playerid][player_mute] != 0)return SendClientMessage(playerid, -1, " Nie mo¿esz teraz u¿yæ tej komendy.");
	if(pInfo[playerid][player_jail] != 0)return SendClientMessage(playerid, -1, " Nie mo¿esz teraz u¿yæ tej komendy.");
	new str[128],text[128];
	if(sscanf(params,"s[128]",text))return SendClientMessage(playerid, -1, "/me [text]");
	GetPlayerName(playerid, str, sizeof(str));
    format(str, sizeof(str), "* %s %s", str, text);
    SendClientMessageToAll(0xccccffFF, str);
    return 1;
}

CMD:glitchexit(playerid, params[])
{
	if(pInfo[playerid][player_glitchTest] != 1) return SendClientMessage(playerid, -1, " Nie Jesteœ na arenie glitch!");

	pInfo[playerid][player_glitchCount][0] = 0; 
	pInfo[playerid][player_glitchCount][1] = 0; 
	pInfo[playerid][player_glitchCount][2] = 0; 
	pInfo[playerid][player_glitchCount][3] = 0;
	
    pInfo[playerid][player_glitchTest] = 0;
	SetPlayerVirtualWorld(playerid,0);
    OnPlayerSpawn(playerid);
    return 1;
}

Command_Alt(cars,v);
Command_Alt(rsp,flo);
Command_Alt(p,cars);
Command_Alt(pojazdy,cars);	
Command_Alt(car,cars);	
 
Command_Alt(raporty,lastreports);	
Command_Alt(raport,report);	
Command_Alt(anims,anim);	
Command_Alt(animacje,anim);	
Command_Alt(pojazd,privcar);	
Command_Alt(pp,privcar);	
Command_Alt(givescore,sendscore);
Command_Alt(sendexp,sendscore);
Command_Alt(givecash,sendmoney);
Command_Alt(givemoney,sendmoney); 
Command_Alt(lowisko,ryby); 
Command_Alt(lowienie,ryby); 
Command_Alt(staw,ryby); 
Command_Alt(lowiska,ryby); 
Command_Alt(lbexit,labiryntexit); 
Command_Alt(panel,konto); 

 
