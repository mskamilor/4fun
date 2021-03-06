/*
          Achievement [v1.5]
      (c) Copyright 2013-2014 by mrdrifter
 
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
	  @date      : 16 listopada 2013
	  @update    : 27 stycznia 2014
  
 */ 
new ach_playertimer[MAX_PLAYERS];
stock AchievementInit()
{
	AchventesCount = 0;
	AddNewAchievement("Witamy!", "Zarejestruj swoje  konto.", 1, 0);
	AddNewAchievement("Pierwsza �mier�", "Zgi�.", 1, 1); 
	AddNewAchievement("Hitman", "Zabij 25 razy gracza za \nkt�rego jest wystawiona nagroda respektu.", 25, 2); 
	AddNewAchievement("W�amywacz", "Sprobuj w�ama� si� do czyjego� prywatnego pojazdu", 1, 3); 
	AddNewAchievement("Zawodowy kierowca", "Wykonaj misj� (/tr1) 100 razy z\ntras� d�u�sz� ni� 23.9 km.", 100, 4);
	AddNewAchievement("W�dkarz", "Z��w 100 razy ryb�.", 100, 5); 
	AddNewAchievement("Kierowca", "Wsi�d� do pojazdu", 1, 6); 
	//AddNewAchievement("Sta�y Gracz", "Zaloguj si� codziennie przez 10 dni.", 10, 7); 
	AddNewAchievement("Drwal","Zetnij 150 drzew",150,7);
	AddNewAchievement("Pilot", "Przelataj 60 minut samolotem.", 1, 8); 
	AddNewAchievement("Jestem lepszy!", "Wygraj pojedynek solo (/duel) z dowolnym graczem.", 1, 9);
	AddNewAchievement("Podr�nik", "Przejed� swoim prywatnym pojazdem 500.1 km/h.", 1, 10);	
	AddNewAchievement("Zwinne Palce", "Przepisz 100 razy kod jako pierwszy.", 100, 11);	
	AddNewAchievement("Domownik", "Posiadaj w�asny dom.", 1, 12);	
	AddNewAchievement("Nowa to�samo��.", "Zmie� sw�j nick za pomoc� komendy /zmiennick\nLub /Konto"chat" Zmie� Nick.", 1, 13);	
	//AddNewAchievement("Audio Plugin", "Zainstaluj audio plugin i wpisz /radio.", 1, 14);
	AddNewAchievement("Msk? �atwo.", "Zabij Msk. 5 razy broni� Desert Eagle", 5, 14); 
	AddNewAchievement("24 Godziny", "Przegraj 24 godziny na serwerze.", 1, 15);
	AddNewAchievement("W�asny biznes", "Kup w�asny biznes", 1, 16);
	AddNewAchievement("Mega zestaw", "Wylosuj mega zestaw broni w /Loteria.", 1, 17);
	AddNewAchievement("Spryciarz", "Wykonaj 40 razy zadawanie w Test Reakcji (/TR)", 40, 18);
	AddNewAchievement("Poszukiwacz", "Znajd� 100 walizek / prezent�w / samochod�w.", 40, 19);
	//AddNewAchievement("Szybko�� to moje drugie imie", "Przepisz kod w mniej ni� 2.5 sekundy.", 40, 20);  
	AddNewAchievement("Nie potrzebuje event�w!", "Zabij oboj�tnie jakiego moderatora 150 razy.", 150, 20); 
	AddNewAchievement("Drifter", "Zdob�d� 5000 punkt�w w driftingu", 1, 21);  
	AddNewAchievement("Kr�l Driftu", "Osi�gnij 20000 punkt�w w driftingu", 1, 22);  
	AddNewAchievement("Pirat drogowy", "Zdob�d� 30 mandat�w za przekroczenie pr�dko�ci", 30, 23);  
	AddNewAchievement("Celne Oko!", "Zabij 100 os�b na arenie /OneDe", 100, 24);  
	AddNewAchievement("Przeszdlem go!", "Przejd� /Labirynt!", 1, 25);  
	AddNewAchievement("Zabijam Bronia dnia!!", "Zabij oboj�tnie jakiego gracza 100 razy broni� dnia.", 100, 26);  
	AddNewAchievement("Podszywka", "Admin ustawil ci range poprzez /setrange.", 1, 27);  
	AddNewAchievement("KillStreak", "Zabij 10 graczy nie gin�c przy tym ani raz.", 1, 28);  
	AddNewAchievement("Sniper Fan", "Zabij 250 os�b z broni /sniper (uwaga: osi�gni�cie nie nabija si� na arenie /sniper)", 250, 29);  
	AddNewAchievement("Maniak teleport�w", "Teleportuj si� 125 razy.", 125, 30);  
	AddNewAchievement("Nie potrzebuje pomocy!", "Zabij oboj�tnie jakiego admina 50 razy.", 50, 31); 
	AddNewAchievement("Niezdecydowany(a)", "Zmie� sw�j spawn w /konto 15 razy", 15, 32); 
	AddNewAchievement("Niepowstrzymany", "Osi�gnij killstreak 22 zab�jstw", 1, 33); 
}
	
stock AddNewAchievement(const name[], const desc[], score_p, uixd)
{
	
	format(Osiagniecia[uixd][Nazwa], 50, "%s", name);
	format(Osiagniecia[uixd][Opis], 150, "%s", desc);
	Osiagniecia[uixd][Score] = score_p;
	
	AchventesCount++;
	
	//printf("%d=>Array('osiagniecie'=> '%s', 'opis'=> '%s', 'score'=> %d), ", uixd, Osiagniecia[uixd][Nazwa], Osiagniecia[uixd][Opis], Osiagniecia[uixd][Score]);
}


stock achievement(playerid, osiagniecie) 
{

    if(!pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, " Nie jeste� zarejestrowany(a) twoje osi�gni�cia nie s� zapisane.");
		return;
	}
	
	if(osiagniecie >= MAX_ACHIEVEMENT)
	{
		SendClientMessageToAll(COLOR_ERROR, "WYSTATPIL BLAD - achievement(\"%s\", %d;); {FFFFFF}ZGLOS INFORMACJE NA FORUM{ff0000}!!!", playerNick(playerid), osiagniecie);
		return;
	}
	
	if(!pInfo[playerid][player_logged]) return;
 
    if(pInfo[playerid][player_achievements][osiagniecie] == Osiagniecia[osiagniecie][Score]) return;
    if(pInfo[playerid][player_achievements][osiagniecie] >= Osiagniecia[osiagniecie][Score]) return;
        
    pInfo[playerid][player_achievements][osiagniecie]++;
	pInfo[playerid][player_achievements_count]++;
	
    if(pInfo[playerid][player_achievements][osiagniecie] == Osiagniecia[osiagniecie][Score]) show_achievement_new(playerid, osiagniecie);
    else show_achievement_status(playerid, osiagniecie, pInfo[playerid][player_achievements][osiagniecie]);

}

 
stock show_achievement(playerid, page = 0)
{
	static achievements[1024];
	achievements[0] = EOS;
	achievements = "Zamknij";
	
	pInfo[playerid][player_achievements_page] = page;
	
	new end;
	
	if((page + 10) > AchventesCount)
		end = AchventesCount;
	else 
		end = page + 10;
		
	for(new i = page;i<end;i++)
	{
		if(!Osiagniecia[i][Nazwa][0]) continue;
		
		if(pInfo[playerid][player_achievements][i] >= Osiagniecia[i][Score]) 	
			format(achievements, sizeof(achievements), "%s\n{FFFFFF}"chat" %d. {00FF00}%s - Zako�czone", achievements, i + 1, Osiagniecia[i][Nazwa]);
		else
			format(achievements, sizeof(achievements), "%s\n{FFFFFF}"chat" %d. %s - %d/%d ", achievements, i + 1, Osiagniecia[i][Nazwa], pInfo[playerid][player_achievements][i], Osiagniecia[i][Score]);
	}
	
	if((end + 1) < AchventesCount) strcat(achievements, "\nDalej...");
	
	Dialog_Show(playerid, DIALOG_ACHIEVEMENT_SHOW, DIALOG_STYLE_LIST, "Osi�gni�cia", achievements, "Wybierz", "Zamknij");
	
	return 1;
	
}

/*
stock show_achievement(playerid, str=0, to_player = -1)
{
	new osiagnieciaList[1000]="Wr��";
	
 
	SetPVarInt(playerid, "achievement_player_str", str);
	new a_do;
	if(str + 10 > sizeof(Osiagniecia)) a_do = sizeof(Osiagniecia); else a_do = str +10;
	new oss; 
	for(new i=str; i<a_do; i++)
	{
		if(i > sizeof(Osiagniecia)) break;
		if(Osiagniecia[i][Nazwa] == 0) continue;
		
		if(pInfo[playerid][player_achievements][i] == Osiagniecia[i][Score] || pInfo[playerid][player_achievements][i] > Osiagniecia[i][Score]) 	
			format(osiagnieciaList, 1000, "%s\n{FFFFFF}"chat" %d. {00FF00}%s - Zako�czone", osiagnieciaList, i, Osiagniecia[i][Nazwa]);
		else
			format(osiagnieciaList, 1000, "%s\n{FFFFFF}"chat" %d. %s - %d/%d ", osiagnieciaList, i, Osiagniecia[i][Nazwa], pInfo[playerid][player_achievements][i], Osiagniecia[i][Score]);
		oss++;
	}
	if(oss >= 8)strcat(osiagnieciaList, "Dalej...");
 	if(to_player == -1)
		return  
	else 		
		return Dialog_Show(to_player, DIALOG_ACHIEVEMENT_SHOW, DIALOG_STYLE_LIST, "Osi�gni�cia", osiagnieciaList, "Wybierz", "Zamknij");

}*/


 
 
stock show_player_achinfo(playerid, os)
{
	if(os > sizeof(Osiagniecia)) return 0;
	new osiagnieciaList[900];
	
	if(pInfo[playerid][player_achievements][os] == Osiagniecia[os][Score]) 	
	format(osiagnieciaList, sizeof(osiagnieciaList), "{CC6600}%s\n\n{00FF00}Zako�czone\n\n{FFFFFF}%s", Osiagniecia[os][Nazwa], Osiagniecia[os][Opis]);
	else 
	format(osiagnieciaList, sizeof(osiagnieciaList), "{CC6600}%s\n\n{FFFFFF}%d/%d\n\n %s", Osiagniecia[os][Nazwa], pInfo[playerid][player_achievements][os], Osiagniecia[os][Score], Osiagniecia[os][Opis]);
	
	return    ShowPlayerDialog(playerid, 9999, DIALOG_STYLE_MSGBOX, "Osi�gni�cia", osiagnieciaList, "Zamknij", "");
}
 
stock show_achievement_status(playerid, osiagniecie, pkt)
{
	#if defined ADUIO_PLUGIN
	Audio_PlayEx(playerid,OSIAGNIECIE_SOUND);
	#endif
	GivePlayerScore(playerid, 10);
	
	new sostr[100];
	GivePlayerScore(playerid, pkt);
	format(sostr, sizeof(sostr), "~y~%s ~n~~w~~h~Status: %d/%d", Osiagniecia[osiagniecie][Nazwa], pkt, Osiagniecia[osiagniecie][Score]);
	PlayerTextDrawSetString(playerid, pInfo[playerid][player_achievement], sostr);
	PlayerTDShowForPlayer(playerid, pInfo[playerid][player_achievement], 0xFFFFFF99, 0x00000060, 0x000000080, 8, 8, 8);
 
	//SendClientMessage(playerid, COLOR_INFO, ""chat" Osi�gni�cie {b}%s{/b} Status: {b}%d/%d{/b}", Osiagniecia[osiagniecie][Nazwa], pkt, Osiagniecia[osiagniecie][Score]);
	
	if(ach_playertimer[playerid])
		KillTimer(ach_playertimer[playerid]);
	ach_playertimer[playerid] = SetTimerEx("HideOsiagniecia", 10000, 0, "db", playerid, true);
}

stock show_achievement_new(playerid, osiagniecie)
{ 
    
	GivePlayerScore(playerid, 1000);
	format(string2, sizeof(string2), "~y~Nowe osiagniecie! ~n~~w~~h~%s", Osiagniecia[osiagniecie][Nazwa]);
	PlayerTextDrawSetString(playerid, pInfo[playerid][player_achievement], string2);
	 
	PlayerTDShowForPlayer(playerid, pInfo[playerid][player_achievement], 0xFFFFFF99, 0x00000060, 0x000000080, 8, 8, 8);
	#if defined ADUIO_PLUGIN
	PlayCompleteMissionSound(playerid);
	#endif
	if(osiagniecie > 0)
		SendClientMessage(playerid, COLOR_OLD_LACE, ""chat" Gratulacj�! zako�czy�e� osi�gni�cie {87CEEB}%s{/b}", Osiagniecia[osiagniecie][Nazwa]);
	new astr[256];
	format(astr,256,"Gracz %s zdoby� osi�gni�cie {87CEEB}%s",playerNick(playerid), Osiagniecia[osiagniecie][Nazwa]);
	SendClientMessageToAll(COLOR_OLD_LACE,astr);
	SavePlayer(playerid);
	if(ach_playertimer[playerid])
		KillTimer(ach_playertimer[playerid]);
	ach_playertimer[playerid] = SetTimerEx("HideOsiagniecia", 10000, 0, "db", playerid, true);
  
}
Public:HideOsiagniecia(playerid, bool:frist)
{
	if(frist)
	{
		ach_playertimer[playerid] = SetTimerEx("HideOsiagniecia", 4000, 0, "db", playerid, false);
	}
	else {
		ach_playertimer[playerid] = 0;
		PlayerTextDrawHide(playerid, pInfo[playerid][player_achievement]);
		return;
	}
	PlayerTDHideForPlayer(playerid, pInfo[playerid][player_achievement], 8, 8, 8);	
 
}
Dialog:DIALOG_ACHIEVEMENT_SHOW(playerid, response, listitem, inputtext[])
{
	if(response)
	{		
		if(listitem < 1 ) return 1;
		if(listitem == 11) return show_achievement(playerid, pInfo[playerid][player_achievements_page] + 10);
 
		show_player_achinfo(playerid, (listitem + pInfo[playerid][player_achievements_page]) - 1);
		return 1;
	}
	return 1;
}
 
 