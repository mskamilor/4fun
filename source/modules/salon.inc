/*
          Duel / solo system [NOT VERSION]
      (c) Copyright 2013-2014 by mrdrifter
 
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
	  @date      : 18 listopada 2013
   
 */ 
 
 
new CategorySkup[] = {7, 16, 20, 27, 31, 33, 37, 38, 90, 128, 144, 196, 197, 198, 199, 201, 51};

new SKUP_CHECKPOINT;
enum playerSkupEnum
{
	lastGuiShow,
	bool:missionActive,
	missionVehicle
};
new pSkup[MAX_PLAYERS][playerSkupEnum];

stock skup_OnGameModeInit()
{
	SKUP_CHECKPOINT = CreateDynamicCP(-1928.5498,273.1347,41.0469, 5.0);
}
stock Skup_OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if( checkpointid == SKUP_CHECKPOINT)
	{
		if(pSkup[playerid][lastGuiShow] > gettime()) return 1;
		pSkup[playerid][lastGuiShow] = gettime() + 7;
		
		if(pSkup[playerid][missionActive])
		{
			new triller = (GetVehicleTrailer(GetPlayerVehicleID(playerid))), Float:trillerhp;
			if(triller)
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 525 && GetVehicleModel(triller) == pSkup[playerid][missionVehicle])
				{
					SetVehicleToRespawn(GetVehicleTrailer(GetPlayerVehicleID(playerid)));
					SetCameraBehindPlayer(playerid);
					
					GetVehicleHealth(triller, trillerhp);
					if(trillerhp > 600) 
					{ 
						new sped_kasa = (random(1555));
						new sped_score = (random(50))+1;

						SendClientMessage(playerid, COLOR_INFO, " "chat" {b}[Skup]{/b} Dowioz³eœ towar na miejsce otrzymujesz {b}%d$ i %d Respektu{/b}.", sped_kasa, sped_score);
						SendClientMessageToAll(COLOR_INFO*4, " "chat" {d}%s{/b} dostarczy³ pojazd do skupu! otrzymuje %d$ oraz %d respektu. ({d}/Skup{/b}).", playerNick(playerid), sped_kasa, sped_score);
						 
						GivePlayerMoney(playerid, sped_kasa);
						GivePlayerScore(playerid, sped_score);
						pSkup[playerid][missionActive] = false;
						PlayerEventTD(playerid, false);
					}
					else 
					{
						SendClientMessage(playerid, COLOR_INFO, "{FFFFFF}* {b}[Skup]{/b} Dostarczy³eœ towar na miejsce niestety nie odtrzymujesz nagrody poniewa¿ pojazd by³ za bardzo uszkodzony.");
						SendClientMessageToAll(COLOR_INFO*4, " "chat" {d}%s{/b} dostarczy³ pojazd do skupu! niestety nie otrzymuje ¿adnej nagrody poniewa¿ za bardzo uszkodzi³ pojazd. (%d/1000)", trillerhp);
						 
					}
				}
				else 
				{
					SendClientMessage(playerid, COLOR_ERROR, "*[0] Musisz tutaj przyholowaæ {b}%s{/b}. Jeœeli chcesz anulowaæ misje wpisz /SkupCancel ", VehicleNames[pSkup[playerid][missionVehicle] -400 ]);
				}
			} else SendClientMessage(playerid, COLOR_ERROR, "* Musisz tutaj przyholowaa {b}%s{/b}. Je?eli chcesz anulowaæ misje wpisz /SkupCancel ", VehicleNames[pSkup[playerid][missionVehicle] -400 ]);
			return 1;
		}
		
		 
		Dialog_Show(playerid, DIALOG_SKUP, DIALOG_STYLE_MSGBOX, "Misja w skupie.", "Czy chcesz wykonaæ misje w skupie?", "Tak", "Nie");
	}
	return 1;
}
CMD:skupcancel(playerid, cmdtext[])
{
	if(!pSkup[playerid][missionActive]) return SendClientMessage(playerid, COLOR_ERROR, "* Ups coœ posz³o nie tak... Nie wykonujesz misji w skupie.");
	
	pSkup[playerid][missionActive] = false;
	PlayerEventTD(playerid, false);
	
	SendClientMessage(playerid, COLOR_ERROR, "* Misja w skupie anulowana. Tracisz 10 punktów respektu za spartolenie misji.");
	GivePlayerScore(playerid, -10);
	return 1;
}
 

Dialog:DIALOG_SKUP(playerid, response, listitem, inputtext[])
{
	if(!response) return SendClientMessage(playerid, COLOR_RED, "* Anulowa³eœ wykonywanie misji w /Skup.");
	
	pSkup[playerid][lastGuiShow] = gettime() + 7;
	pSkup[playerid][missionVehicle] = CategorySkup[random(sizeof(CategorySkup))] + 400;
	
	string2[0] = EOS;
	string2 = "{FFFFFF}Aktualnie w salonie potrzebujemy pojazdu {FF0000}";
	format(string2, sizeof(string2), "%s%s{FFFFFF}.\nAby wykonaa to zadanie musisz tutaj przyholowaa ten pojazd.\n\nCzy nadal chcesz wykonaa to zadanie?", string2, VehicleNames[pSkup[playerid][missionVehicle] -400 ]);
 	Dialog_Show(playerid, SKUP_AKCEPTMISSION, DIALOG_STYLE_MSGBOX, "Misja - skup. ", string2, "Tak", "Nie");
	
	return 1;
}

Dialog:SKUP_AKCEPTMISSION(playerid, response, listitem, inputtext[])
{
	if(!response) return SendClientMessage(playerid, COLOR_RED, "* Anulowa³eœ wykonywanie misji w /Skup.");
	
	pSkup[playerid][missionActive] = true;
	
	if(GetVehicleModel(pInfo[playerid][player_vehicle]))
	{
		DestroyVehicleEx(pInfo[playerid][player_vehicle]);
	}	
	
	pInfo[playerid][player_vehicle] = CreateVehicle(525,-1913.0339,302.0434,43.0469,175.7559, -1, -1, 60*60);
	PutPlayerInVehicle(playerid, pInfo[playerid][player_vehicle], 0);
	Vehicle_PrivClear(pInfo[playerid][player_vehicle]);
	
	string2[0] = EOS;
	string2 = "{FFFFFF}Rozpoczêto wykonywanie misji.\nZnajdŸ pojazd {FF0000}";
	format(string2, sizeof(string2), "%s%s{FFFFFF} i przyholuj go tutaj aby odebraæ nagrode.\n\n", string2, VehicleNames[pSkup[playerid][missionVehicle]-400]);
	
	strcat(string2, "Pojazd mo¿esz podczepiaæ z pomoc¹ przycisku {FF0000}CTRL {FFFFFF}b¹dŸ komendy {FF0000} /holuj{FFFFFF}.\nUwaga: pojazd musi mieæ wiecej ni¿ 600(/1000) HP (nie mo¿e byæ zniszczony).\n\nPowodzenia. ");
	
	InfoBox(playerid, string2);
	
	string2[0] = EOS;
	
	format(string2, sizeof(string2), "Szukasz pojazdu ~r~%s~w~~n~Aby anulowaæ wpisz ~r~/SkupCancel",  VehicleNames[pSkup[playerid][missionVehicle]-400]);
	PlayerEventTDSet(playerid, string2);
	return 1;
}