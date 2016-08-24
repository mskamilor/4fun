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
	AddNewAchievement("Pierwsza œmieræ", "Zgiñ.", 1, 1); 
	AddNewAchievement("Hitman", "Zabij 25 razy gracza za \nktórego jest wystawiona nagroda respektu.", 25, 2); 
	AddNewAchievement("W³amywacz", "Sprobuj w³amaæ siê do czyjegoœ prywatnego pojazdu", 1, 3); 
	AddNewAchievement("Zawodowy kierowca", "Wykonaj misjê (/tr1) 100 razy z\ntras¹ d³u¿sz¹ ni¿ 23.9 km.", 100, 4);
	AddNewAchievement("Wêdkarz", "Z³ów 100 razy rybê.", 100, 5); 
	AddNewAchievement("Kierowca", "Wsi¹dŸ do pojazdu", 1, 6); 
	//AddNewAchievement("Sta³y Gracz", "Zaloguj siê codziennie przez 10 dni.", 10, 7); 
	AddNewAchievement("Drwal","Zetnij 150 drzew",150,7);
	AddNewAchievement("Pilot", "Przelataj 60 minut samolotem.", 1, 8); 
	AddNewAchievement("Jestem lepszy!", "Wygraj pojedynek solo (/duel) z dowolnym graczem.", 1, 9);
	AddNewAchievement("Podró¿nik", "PrzejedŸ swoim prywatnym pojazdem 500.1 km/h.", 1, 10);	
	AddNewAchievement("Zwinne Palce", "Przepisz 100 razy kod jako pierwszy.", 100, 11);	
	AddNewAchievement("Domownik", "Posiadaj w³asny dom.", 1, 12);	
	AddNewAchievement("Nowa to¿samoœæ.", "Zmieñ swój nick za pomoc¹ komendy /zmiennick\nLub /Konto"chat" Zmieñ Nick.", 1, 13);	
	//AddNewAchievement("Audio Plugin", "Zainstaluj audio plugin i wpisz /radio.", 1, 14);
	AddNewAchievement("Msk? £atwo.", "Zabij Msk. 5 razy broni¹ Desert Eagle", 5, 14); 
	AddNewAchievement("24 Godziny", "Przegraj 24 godziny na serwerze.", 1, 15);
	AddNewAchievement("W³asny biznes", "Kup w³asny biznes", 1, 16);
	AddNewAchievement("Mega zestaw", "Wylosuj mega zestaw broni w /Loteria.", 1, 17);
	AddNewAchievement("Spryciarz", "Wykonaj 40 razy zadawanie w Test Reakcji (/TR)", 40, 18);
	AddNewAchievement("Poszukiwacz", "ZnajdŸ 100 walizek / prezentów / samochodów.", 40, 19);
	//AddNewAchievement("Szybkoœæ to moje drugie imie", "Przepisz kod w mniej ni¿ 2.5 sekundy.", 40, 20);  
	AddNewAchievement("Nie potrzebuje eventów!", "Zabij obojêtnie jakiego moderatora 150 razy.", 150, 20); 
	AddNewAchievement("Drifter", "Zdob¹dŸ 5000 punktów w driftingu", 1, 21);  
	AddNewAchievement("Król Driftu", "Osi¹gnij 20000 punktów w driftingu", 1, 22);  
	AddNewAchievement("Pirat drogowy", "Zdob¹dŸ 30 mandatów za przekroczenie prêdkoœci", 30, 23);  
	AddNewAchievement("Celne Oko!", "Zabij 100 osób na arenie /OneDe", 100, 24);  
	AddNewAchievement("Przeszdlem go!", "PrzejdŸ /Labirynt!", 1, 25);  
	AddNewAchievement("Zabijam Bronia dnia!!", "Zabij obojêtnie jakiego gracza 100 razy broni¹ dnia.", 100, 26);  
	AddNewAchievement("Podszywka", "Admin ustawil ci range poprzez /setrange.", 1, 27);  
	AddNewAchievement("KillStreak", "Zabij 10 graczy nie gin¹c przy tym ani raz.", 1, 28);  
	AddNewAchievement("Sniper Fan", "Zabij 250 osób z broni /sniper (uwaga: osi¹gniêcie nie nabija siê na arenie /sniper)", 250, 29);  
	AddNewAchievement("Maniak teleportów", "Teleportuj siê 125 razy.", 125, 30);  
	AddNewAchievement("Nie potrzebuje pomocy!", "Zabij obojêtnie jakiego admina 50 razy.", 50, 31); 
	AddNewAchievement("Niezdecydowany(a)", "Zmieñ swój spawn w /konto 15 razy", 15, 32); 
	AddNewAchievement("Niepowstrzymany", "Osi¹gnij killstreak 22 zabójstw", 1, 33); 
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
		SendClientMessage(playerid, COLOR_ERROR, " Nie jesteœ zarejestrowany(a) twoje osi¹gniêcia nie s¹ zapisane.");
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
			format(achievements, sizeof(achievements), "%s\n{FFFFFF}"chat" %d. {00FF00}%s - Zakoñczone", achievements, i + 1, Osiagniecia[i][Nazwa]);
		else
			format(achievements, sizeof(achievements), "%s\n{FFFFFF}"chat" %d. %s - %d/%d ", achievements, i + 1, Osiagniecia[i][Nazwa], pInfo[playerid][player_achievements][i], Osiagniecia[i][Score]);
	}
	
	if((end + 1) < AchventesCount) strcat(achievements, "\nDalej...");
	
	Dialog_Show(playerid, DIALOG_ACHIEVEMENT_SHOW, DIALOG_STYLE_LIST, "Osi¹gniêcia", achievements, "Wybierz", "Zamknij");
	
	return 1;
	
}

/*
stock show_achievement(playerid, str=0, to_player = -1)
{
	new osiagnieciaList[1000]="Wróæ";
	
 
	SetPVarInt(playerid, "achievement_player_str", str);
	new a_do;
	if(str + 10 > sizeof(Osiagniecia)) a_do = sizeof(Osiagniecia); else a_do = str +10;
	new oss; 
	for(new i=str; i<a_do; i++)
	{
		if(i > sizeof(Osiagniecia)) break;
		if(Osiagniecia[i][Nazwa] == 0) continue;
		
		if(pInfo[playerid][player_achievements][i] == Osiagniecia[i][Score] || pInfo[playerid][player_achievements][i] > Osiagniecia[i][Score]) 	
			format(osiagnieciaList, 1000, "%s\n{FFFFFF}"chat" %d. {00FF00}%s - Zakoñczone", osiagnieciaList, i, Osiagniecia[i][Nazwa]);
		else
			format(osiagnieciaList, 1000, "%s\n{FFFFFF}"chat" %d. %s - %d/%d ", osiagnieciaList, i, Osiagniecia[i][Nazwa], pInfo[playerid][player_achievements][i], Osiagniecia[i][Score]);
		oss++;
	}
	if(oss >= 8)strcat(osiagnieciaList, "Dalej...");
 	if(to_player == -1)
		return  
	else 		
		return Dialog_Show(to_player, DIALOG_ACHIEVEMENT_SHOW, DIALOG_STYLE_LIST, "Osi¹gniêcia", osiagnieciaList, "Wybierz", "Zamknij");

}*/


 
 
stock show_player_achinfo(playerid, os)
{
	if(os > sizeof(Osiagniecia)) return 0;
	new osiagnieciaList[900];
	
	if(pInfo[playerid][player_achievements][os] == Osiagniecia[os][Score]) 	
	format(osiagnieciaList, sizeof(osiagnieciaList), "{CC6600}%s\n\n{00FF00}Zakoñczone\n\n{FFFFFF}%s", Osiagniecia[os][Nazwa], Osiagniecia[os][Opis]);
	else 
	format(osiagnieciaList, sizeof(osiagnieciaList), "{CC6600}%s\n\n{FFFFFF}%d/%d\n\n %s", Osiagniecia[os][Nazwa], pInfo[playerid][player_achievements][os], Osiagniecia[os][Score], Osiagniecia[os][Opis]);
	
	return    ShowPlayerDialog(playerid, 9999, DIALOG_STYLE_MSGBOX, "Osi¹gniêcia", osiagnieciaList, "Zamknij", "");
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
 
	//SendClientMessage(playerid, COLOR_INFO, ""chat" Osi¹gniêcie {b}%s{/b} Status: {b}%d/%d{/b}", Osiagniecia[osiagniecie][Nazwa], pkt, Osiagniecia[osiagniecie][Score]);
	
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
		SendClientMessage(playerid, COLOR_OLD_LACE, ""chat" Gratulacjê! zakoñczy³eœ osi¹gniêcie {87CEEB}%s{/b}", Osiagniecia[osiagniecie][Nazwa]);
	new astr[256];
	format(astr,256,"Gracz %s zdoby³ osi¹gniêcie {87CEEB}%s",playerNick(playerid), Osiagniecia[osiagniecie][Nazwa]);
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
 
 