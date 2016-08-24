// [\sourcemap\gamemodes\source\main/timers.inc]
/*
          Timers [NOT VERSION]
      (c) Copyright 2013-2014 by mrdrifter, Game
 
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/), Game
	  @date      : 16 listopada 2013
	  @update    : 20 stycznia 2014
  
 */ 
 /*
new reklamy[][] = {
	""chat" Zapraszamy do skorzystania z naszej us³ugi {b}/Portfel{/b} !", 
	""chat" Chcesz w³¹czyæ tryb {b}First Person{/b}? Wpisz {b}/FPS{/b}", 
	""chat" Mi³ej gry na {b}Polski 4 FuN Serwer{/b} ¿yczy Administracja!", 
	""chat" Czy widzia³eœ ju¿ now¹ spedycjê? {b}/TR2{/b}! Wykonaj spedycjê {b}/Burrito{/b}.", 
	""chat" Zapraszamy na serwer Team Speak 3 IP: {b}TS.4fun-serv.pl{/b}", 
	""chat" B¹dŸ najlepszy zdob¹dŸ wszystkie {b}/Osiagniecia{/b}", 
	""chat" Zapraszamy do ubierania na siebie dodatków {b}/Dodatki{/b}", 
	""chat" "HEX_ERROR"NOWOŒÆ:{/b} Na serwer wprowadzono dodatki do pojazdów! wypróbuj "HEX_ERROR"/vdodatki{/b}", 
	""chat" Top Gracze? Wpisz {b}/Top{/b}", 
	""chat" Szukasz wra¿eñ? znajdziesz je w {b}/Labirynt{/b}.", 
	""chat" Szpanuj! jeŸdzij prywatn¹ bryk¹! {b}/PrywatnyPojazd{/b} (/PP).", 
//	""chat" Pamiêtaj jeœli posiadasz prywatny pojazd musisz byæ online przynajmniej co piêæ dni inaczej go stracisz.", 
	""chat" Rangê wyœwietlan¹ ustawiasz sobie sam! {b}/Ranga{/b}", 
	""chat" Widzisz cheatera? wpisz {b}/Raport [ID] [Powód]{/b} nie czekaj...",
	""chat" Zachêcamy do korzystania z {b}lauchera{/b}, dostepnego na {b}4fun-serv.pl/launcher{/b}",
	""chat" Widzisz cheatera? wpisz {b}/Raport [ID] [Powód]{/b} nie czekaj...",
	""chat" Aby wy³aczyæ czapkê miko³aja wpisz /czapka",
	""chat" Wesolych swiat mozesz zyczyc wpisujac /wesolych"
};
new recommend_str[][] = {
	{"Chcesz aby serwer byl bardziej popularny? ~r~Zapros znajomych!"},
	{"/onede - WALKA NA DESERT EAGLE"},
	{"Doladuj szybko portfel! ~y~/portfel"},
	{"Widzisz cheatera? wpisz ~g~~h~/Raport [ID] [Powód] nie czekaj..."},
	{"Szpanuj! jezdzij prywatna bryka! ~y~/PrywatnyPojazd"},
//	{"Zapraszamy na serwer Team Speak 3 IP: ~b~~h~TS.4fun-serv.pl"},
	{"Milej gry na ~b~Polskim ~r~4Fun ~y~Serwerze ~w~¿yczy ~g~Administracja!"},
	{"Doladuj szybko portfel! ~g~/portfel"},
	{"Top Gracze? Wpisz ~r~/Top"},
	{"Na serwer wprowadzono dodatki do pojazdów! wypróbuj ~r~/vdodatki"},
	{"B¹dŸ najlepszy zdob¹dŸ wszystkie ~y~/Osiagniecia"},
	{"Doladuj szybko portfel! ~r~/portfel"},
	{"Chcesz miec konto VIP? Do³aduj szybko portfel! ~r~/portfel"},
	{"Top Gracze? Wpisz ~r~/Top"},
	{"/chainsaw - ~g~~h~Walki na pily lancuchowe"},
	{"/sniper - ~g~~h~WALKA NA SNAJPERKI!"},
	{"Doladuj szybko portfel! ~r~/portfel"},
	{"Chcesz miec konto VIP? Do³aduj szybko portfel! ~r~/portfel"},
	{"Top Gracze? Wpisz ~y~/Top"},
	{">> Baw sie dobrze na Dyskotece! ~g~~h~/Dyskoteka <<"},
	{"Aby wylaczyc ~r~~h~CZAPKE MIKOLAJA ~w~~h~wpisz ~y~/CZAPKA"},
	{"~r~~h~Wesolych swiat ~p~~h~mozesz zyczyc ~b~~h~wpisujac ~y~/~g~wesolych"}
};
*/
#define         MAX_MESSAGE_INFRACTIONS         3
#define         MAX_MESSAGE_RATE                100

//new __timspiki[64];
//task optTest[1000*60]()
Public:optTest()
{
	
	SendRconCommand("minconnectiontime 0");
	UnBlockIpAddress("*.*.*.*");
	 
	
	gmData[animatelogo_running] = true;
	
	fremove("scriptfiles/online_players.launcher");
    file_create("scriptfiles/online_players.launcher");
    file_write("scriptfiles/online_players.launcher", splitf("%02d,%02d,%02d,%02d", Iter_Count(Player), Iter_Count(Admins), Iter_Count(Mods), Iter_Count(Vips)));
	
	//file_read("scriptfiles/online.ts3", __timspiki);
	//TextDrawSetString(PasekBelt[7], __timspiki);
	
//	TextDrawSetString(recommend_box, splitf("_____________________~w~~h~%s", recommend_str[random(sizeof(recommend_str))]));
	TextDrawSetString(recommend_box,"_");

	Biznes_Cash();
	SendRconCommand("minconnectiontime 0");
	if(!gmData[timer_message])
	{
		for(new i;i<23;i++) gmData[server_arenaplayers][i] = 0;
		gmData[server_arenaplayers][stats_onede2] = 0;
		
		foreach(new i : Player)
		{
			if(pInfo[i][player_arena]) gmData[server_arenaplayers][ pInfo[i][player_arena] ]++;
		}
		UpdateArenaPlayers();
		/*
		switch(random(11)+1)
		{
			case 0..2:	SendClientMessageToAll(COLOR_INFO2, "%s", reklamy[random(sizeof(reklamy))]);
			case 3..5:	SendClientMessageToAll(COLOR_DIMGRAY, "%s", reklamy[random(sizeof(reklamy))]);
			case 6..8:	SendClientMessageToAll(COLOR_GOLDENROD, "%s", reklamy[random(sizeof(reklamy))]);
			case 9..12:	SendClientMessageToAll(COLOR_BISQUE_4, "%s", reklamy[random(sizeof(reklamy))]);
		}*/
		gmData[timer_message] = true;
	}
	else
	{	
		gmData[timer_message] = false;
		OPTEvent();
	}
}
Public:UpdateLabelsTimer()
{
	SendRconCommand("unbanip *.*.*.*");
	static czh, czm;
	gettime(czh, czm);
	if(czh == 5)
	{
		foreach(new i : Player)
		{
			SavePlayer (i);
			SendClientMessageToAll(COLOR_GREEN, "Restart SERVERA! (OnGameModeExit Called) (Saving Players)");
		}
		foreach(new i : Gangs)
		{
			saveGang (i);
			SendClientMessageToAll(COLOR_GREEN, "Restart SERVERA! (OnGameModeExit Called) (Saving Gangs) - Prosimy wróciæ po restarcie.");
		}
		this->config::savesql_int("stats/dayrecord", 0);
		SendRconCommand("exit");
		
		return;
	}
	if(czh == 0 || czh == 24)
	{
		static Year, Month, Day;
		Year=0, Month=0, Day=0;
		getdate(Year, Month, Day);
		m_query("SELECT id FROM mreg_adminactive where data='%d-%02d-%02d'", Year, Month, Day);
		mysql_store_result();
		if(!mysql_num_rows())
		{
			static admactive[1846];
			admactive[0]=EOS;
			admactive = "INSERT INTO mreg_adminactive (`uid`,`data`) VALUES ";
			m_query("SELECT id FROM mreg_players where admin>0 limit 60");
			mysql_store_result();
			for(new i;i<mysql_num_rows();i++)
			{
				mysql_data_seek(i);//
				mysql_fetch_row_data();
				
				format(admactive, sizeof(admactive), "%s('%d',NOW()),", admactive, mysql_fetch_field_int("id"));
			}
			strdel(admactive, strlen(admactive)-1, strlen(admactive));
			mysql_query(admactive);
			mysql_free_result();
			
			printf(admactive);
		}
	}
	new t = GetTickCount();
	SendClientMessageToAll(COLOR_INFO, ""chat" Trwa odœwie¿anie/zapisywanie 3dtextów, gangów... - mo¿e wyst¹piæ lag");
	UpdateLabels();
 
	foreach(new i : Gangs)
	{
		saveGang(i);
	}
	SendClientMessageToAll(COLOR_INFO, ""chat" Odœwie¿anie/zapisywanie 3dtextów, gangów... - zakoñczone. Czas trwania %dms", GetTickCount() - t);
	
}
new KURWA;
 
CMD:kurwamacchuj(playerid,params[])
{	
	if(KURWA == 69)
	{
		KURWA = 1;
		SendClientMessage(playerid,COLOR_RED,"chuju:( sam sie wylacz.");
	} else {
		KURWA = 69;
		SendClientMessage(playerid,COLOR_RED,":D! dzia³am");
	}
	
	return 1;
}

Public:refleshStats()
{
	 
 	script_dd_update();
	script_ws_update();
	script_hy_update();
	script_ch_update();
	script_wg_update();
	script_zb_update();
	script_tr_update();
	script_DF_update();
	script_os_update();
	CTFUpdate();
	UpdateEvStat();	
	static czh, czm, czs,y,m,d;
	gettime(czh, czm, czs);
	getdate(y,m,d);
 
	
	if((++gmData[server_hostname])>11)
	{
 		format(string2, 32, "worldtime %02d:%02d",czh, czm);
		SendRconCommand(string2);
		//format(string2, sizeof(string2), "%d (~r~~h~%d~w~|~g~~h~%d~w~|~y~~h~%d~w~) %d/%02d/%02d %02d:%02d", Iter_Count(Player), Iter_Count(Admins), Iter_Count(Mods), Iter_Count(Vips), y,m,d, czh, czm);
		TextDrawSetString2(PasekBelt[9], splitf("_", d,m,y, czh, czm));
		
		TextDrawSetString2(OnlineBelt, splitf("~w~%d I~n~~y~%d I~n~~g~~h~%d I~n~~r~~h~%d I~n~", Iter_Count(Player),Iter_Count(Vips), Iter_Count(Mods), Iter_Count(Admins) ));
 
		
		//TextDrawSetString2(PasekBelt[5], splitf("~g~%d~w~(~r~%d~w~|~g~%d~w~|~y~%d~w~)",Iter_Count(Player), Iter_Count(Admins), Iter_Count(Mods), Iter_Count(Vips)));
		
		gmData[server_hostname]=0;
	}
	if(gmData[vehicles_respawn]++ == 285)
	{
		SendClientMessageToAll(COLOR_GRAY, "{B3FF66}*** {E4FF7A}Za 15 Sekund automatyczny respawn nie u¿ywanych pojazdów! {B3FF66}***");
	}
	else if(gmData[vehicles_respawn] == 300)
	{
		SetVehiclesToRespawn();
		SetVehicleToDelete();
		SendClientMessageToAll(COLOR_GREEN, "{CCFF33}*** {66FFFF}Respawn pojazdów wykonany! {CCFF33}***");
	}
	
	foreach( new playerid : Player)
	{	
		AC_Timer(playerid);
		if(pInfo[playerid][player_jail] > 0)
		{
			pInfo[playerid][player_jail]--;
			GameTextForPlayer(playerid, splitf("~n~~n~~n~~n~Zostaniesz wypuszczony(a) za %ds", pInfo[playerid][player_jail]), 1500, 3);
			ResetPlayerWeapons(playerid);
			if(pInfo[playerid][player_jail] == 0)
			{
				SetPlayerVirtualWorld(playerid, 0);
				OnPlayerSpawn(playerid);
				SendClientMessage(playerid, COLOR_INFO*4, "* Zosta³eœ wypuszczony z wiêzienia.");
			}
			else if(!IsPlayerInRangeOfPoint(playerid, 300.0, Jail_Pozycje) && GetPlayerState(playerid) != PLAYER_STATE_WASTED)
			{
				SetPlayerPos(playerid, Jail_Pozycje);
			}
			SetPlayerInterior(playerid, Jail_Interior);
		}
		if(pInfo[playerid][player_duel_timer] > 0)
		{
			pInfo[playerid][player_duel_timer]--;
			
			if(pInfo[playerid][player_duel_timer] != 0)
			{
				GameTextForPlayer(playerid,  splitf("~n~~n~~n~~n~SOLO ZA %ds", pInfo[playerid][player_duel_timer]), 1000, 3);
			}
			else if(pInfo[playerid][player_duel_timer] == 0)
			{
				GameTextForPlayer(playerid, "~n~~n~~n~~n~START!", 1000, 3);
				TogglePlayerControllable(playerid, true);
			}
		}
	
		if(pInfo[playerid][player_unfreeze] > 0)
		{
			pInfo[playerid][player_unfreeze]--;
			
			if(pInfo[playerid][player_unfreeze] == 0)
			{
				TogglePlayerControllable(playerid, 1);
			}
			else 
			{
				GameTextForPlayer(playerid, splitf("~n~~n~~n~~n~Unfreeze za %ds", pInfo[playerid][player_unfreeze]), 1500, 3);
			}
		}
		if(pInfo[playerid][player_mute] > 0)
		{
			pInfo[playerid][player_mute]--;
			 
			GameTextForPlayer(playerid, splitf("~n~~n~~n~~n~Zostaniesz odciszony(a) za %ds", pInfo[playerid][player_mute]), 1500, 3);
			
			if(pInfo[playerid][player_mute] < 1)
			{
				SendClientMessage(playerid, COLOR_INFO*4, "* Zosta³eœ odciszony. Mo¿esz pisaæ na chacie.");
			}
		}
		if(pInfo[playerid][player_loteria] > 0)
		{
			pInfo[playerid][player_loteria]--;
			if(pInfo[playerid][player_loteria] < 1)
			{
				SendClientMessage(playerid, COLOR_INFO*4, "* Mo¿esz ju¿ u¿yæ komendy /Loteria, ¿yczymy szczêœcia.");
			}
		}
		if(pInfo[playerid][player_deathobject])
		{
			DestroyObject(pInfo[playerid][player_deathobject]);
			pInfo[playerid][player_deathobject] = 0;
		}
		if(pInfo[playerid][player_deathcamera] > 0)
		{
			pInfo[playerid][player_deathcamera]--;
			
			if(pInfo[playerid][player_deathcamera] == 0)
			{
				TogglePlayerSpectating(playerid, 0);
				TDPanorama(playerid, false);
			}
		}
		if(pInfo[playerid][player_blockcmd] > 0)
		{
			pInfo[playerid][player_blockcmd]--;
			 
			GameTextForPlayer(playerid, splitf("~n~~n~~n~~n~Komendy zostana odblokowane za %ds", pInfo[playerid][player_blockcmd]), 1500, 3);
			
			if(pInfo[playerid][player_blockcmd] < 1)
			{
				SendClientMessage(playerid, COLOR_INFO*4, "* Twoje komendy zostaly odblokowane.");
			}
		}
		if(pInfo[playerid][player_ramp_timer] > 0)
		{
			pInfo[playerid][player_ramp_timer]--;
			
			if(!pInfo[playerid][player_ramp_timer])
			{
				if(pInfo[playerid][player_rampcreated] == true)
				{
					pInfo[playerid][player_rampcreated] = false;
					DestroyPlayerObject(playerid, pInfo[playerid][player_ramp]);
				}
			}
		}
		
		if(pInfo[playerid][player_savestats] > 0 && pInfo[playerid][player_id] > 0)
		{
			pInfo[playerid][player_savestats]--;
			
			if(!pInfo[playerid][player_savestats])
			{
			 	SendClientMessage(playerid, COLOR_LIGHTGRAY, ""chat" Twoje statystyki/ustawienia zosta³y zapisane.");
				SavePlayer(playerid);
				pInfo[playerid][player_savestats] = 120+random(10);
			}
		}
		 
		if(pInfo[playerid][player_carge] > 0)
		{
			pInfo[playerid][player_carge]--;
			
			if(pInfo[playerid][player_carge] == 0)
			{
				UnCagePlayer(playerid);
				SendClientMessage(playerid, COLOR_INFO*4, "* Zosta³eœ od kratkowany.");
			}
		}
		if(pInfo[playerid][player_hidespartd] > 0)
		{
			pInfo[playerid][player_hidespartd]--;
			
			if(pInfo[playerid][player_hidespartd] == 0)
			{
				for(new el;el<9;el++)
				{
					TextDrawHideForPlayer(playerid, GangSparTd0[el]);
					PlayerTextDrawHide(playerid, GangSparTd[el][playerid]);
				}
			}
		}
		if(pInfo[playerid][player_spawnkill] > 0)
		{
			switch(pInfo[playerid][player_spawnkill]--)
			{
				case 1,0:
				{
					SetPlayerHealth(playerid, 100.0);
					GivePlayerEquipment(playerid);
					TextDrawHideForPlayer(playerid, SpawnOchrona);
					
					pInfo[playerid][player_spawnkill]=0;
				}
			}
		}
		if(Intro[playerid][i_camerastep] > 0)
		{
			if(Intro[playerid][i_camerastep] > 0)
			{
			
				switch(Intro[playerid][i_camerastep])
				{
					case 16:
					{
					//	SetPlayerTime(playerid, random(2)==1?(21):(22),0);
						//SetPlayerWeather(playerid, 3);
						
						Intro[playerid][i_airobj][2] = CreatePlayerObject(playerid, 1683, -2794.199951, 1755.699951, 163.699997, 0.000000, 0.000000, 0.000000, 0.000000);
 
						MovePlayerObject(playerid, Intro[playerid][i_airobj][2], -2186.899902, 1721.699951, 130.500000, 54.000000);
						
						InterpolateCameraPos(playerid, -2492.399414, 1637.699219, 108.599998, -2502.399414, 1647.699219, 118.599998, 11000, 1);
						InterpolateCameraLookAt(playerid, -2794.199951, 1755.699951, 193.699997, -2186.899902, 1791.699951, 145.500000, 11000, 1);
						
					}
					case 15:
					{
						 
					 
					}
					case 4:
					{
						Intro[playerid][i_step] = 1;
						
						//OnPlayerRequestClass(playerid, 0);
					//	if(pInfo[playerid][player_id]) ShowPlayerDialogLogin(playerid, "");
					}
					case 2:
					{
						if(Intro[playerid][i_airobj][2]>0)
						{
						
							DestroyPlayerObject(playerid, Intro[playerid][i_airobj][2]);
							Intro[playerid][i_airobj][2] = 0;
						}
					}
				}
				Intro[playerid][i_camerastep]--;
			}				
		}
		
	/*	if(pInfo[playerid][player_camera] > 0)
		{
		
			switch(pInfo[playerid][player_camera])
			{
				case 2:
				{
					SetPlayerTime(playerid, 12,0);
					SetPlayerWeather(playerid, 0);
					//InterpolateCameraPos(playerid, -1538.286254, 698.566101, 141.756347, -1544.190673, 693.022033, 141.717239, 1500);
					//InterpolateCameraLookAt(playerid, -1542.875122, 698.410217, 139.776916, -1543.770629, 697.646911, 139.864089, 1500);	
			//		InterpolateCameraPos(playerid,2410.2285,-1671.6150,47.9014,2547.75220, -1660.72327, 40.79000, 10000, CAMERA_CUT);
			//		InterpolateCameraLookAt(playerid,2410.2285,-1671.6150,47.9014,2547.75220, -1660.72327, 40.79000, 10000, CAMERA_CUT);
					Streamer_UpdateEx(playerid,2105.0119, 1006.1265, 58.3233,  360,  -1);
			
				}
				case 1:
				{
					pInfo[playerid][player_introend] = true;
					
					
					OnPlayerRequestClass(playerid, 0);
					if(pInfo[playerid][player_id]) ShowPlayerDialogLogin(playerid, "");
				}
			}
			pInfo[playerid][player_camera]--;
			
		 
			//InterpolateCameraPos(playerid, 3228.695556, 1520.709228, 195.293258, -225.672164, 1607.115112, 105.661277, 60000*3);
		//	InterpolateCameraLookAt(playerid, 3223.745117, 1520.307617, 194.716415, -230.645477, 1607.283813, 106.148780, 60000*2);
		}*/
		
		/*if(pInfo[playerid][player_camera] > 0)
		{
		
			switch(pInfo[playerid][player_camera])
			{
				case 16:
				{
					SetPlayerTime(playerid, random(2)==1?(21):(22),0);
					SetPlayerWeather(playerid, 3);
					
					pInfo[playerid][player_selectobject] = CreatePlayerObject(playerid, 1683, -2794.199951, 1755.699951, 163.699997, 0.000000, 0.000000, 0.000000, 0.000000);
					//SetObjectVritualWorld(pInfo[playerid][player_selectobject], GetPlayerVirtualWorld(playerid));
				}
				case 15:
				{
					 
					MovePlayerObject(playerid, pInfo[playerid][player_selectobject], -2186.899902, 1721.699951, 130.500000, 54.000000);
					
					  
					InterpolateCameraPos(playerid, -2492.399414, 1637.699219, 108.599998, -2502.399414, 1647.699219, 118.599998, 11000, 1);
					InterpolateCameraLookAt(playerid, -2794.199951, 1755.699951, 193.699997, -2186.899902, 1791.699951, 145.500000, 11000, 1);
					
				}
				case 4:
				{
					pInfo[playerid][player_introend] = true;
					
					
					OnPlayerRequestClass(playerid, 0);
					if(pInfo[playerid][player_id]) ShowPlayerDialogLogin(playerid, "");
				}
				case 1:
				{
					if(pInfo[playerid][player_selectobject]>0)
					{
						DestroyObject(pInfo[playerid][player_selectobject]);
						pInfo[playerid][player_selectobject] = 0;
					}
				}
			}
			pInfo[playerid][player_camera]--;
			
		 
			//InterpolateCameraPos(playerid, 3228.695556, 1520.709228, 195.293258, -225.672164, 1607.115112, 105.661277, 60000*3);
		//	InterpolateCameraLookAt(playerid, 3223.745117, 1520.307617, 194.716415, -230.645477, 1607.283813, 106.148780, 60000*2);
		}
		*/
		if(pInfo[playerid][player_tirminssion] > 0)
		{
			czh = pInfo[playerid][player_usevehicle];
			
			if(!IsTir(GetVehicleModel(czh)) && !pInfo[playerid][player_tir_warntime])
			{
				pInfo[playerid][player_tir_warntime] = 61;
			}
			else if(!GetVehicleTrailer(czh) && !pInfo[playerid][player_tir_warntime])
			{
				pInfo[playerid][player_tir_warntime] = 61;
			}
			if(pInfo[playerid][player_tir_warntime] > 0)
			{
				pInfo[playerid][player_tir_warntime]--;
				if(pInfo[playerid][player_tir_warntime] == 0)
				{
					InfoBox(playerid, "Czas min¹³\n\nMisja spedycyjna zosta³a anulowana straci³eœ 5 punktów respektu.");
					Tir_ClearMission(playerid);
					GivePlayerScore(playerid, -5);
				}
				else 
				{
					if( !IsTir(GetVehicleModel(czh)) && !IsWan(GetVehicleModel(czh)) )
					{
						 
						GameTextForPlayer(playerid, splitf("~n~~n~~n~~n~Masz %ds aby wrocic do pojazdu", pInfo[playerid][player_tir_warntime]), 1500, 3);
					}
					else if(!GetVehicleTrailer(czh) && (pInfo[playerid][player_tirfrom] == Tir_CP[TIR_CP_TIR] || pInfo[playerid][player_tirfrom] == Tir_CP[TIR_CP_TIR2]))
					{
						 
						GameTextForPlayer(playerid, splitf( "~n~~n~~n~~n~Masz %ds aby podpiac naczepe", pInfo[playerid][player_tir_warntime]), 1500, 3);
					}
					else 
					{
						pInfo[playerid][player_tir_warntime] = 0;
					}
				}
			}
		}
		if(pInfo[playerid][player_chatspam] > 0)
		{
			pInfo[playerid][player_chatspam]--;
		}
		if(pInfo[playerid][player_cmdspam] > 0)
		{
			pInfo[playerid][player_cmdspam]--;
		}
		if(pInfo[playerid][player_score_drawhide] > 0)
		{
			pInfo[playerid][player_score_drawhide]--;
			
			if(!pInfo[playerid][player_score_drawhide])
			{
				PlayerTextDrawHide(playerid, playerdraw_respect);
				TextDrawHideForPlayer(playerid, RespectAddBox);

			}
		}
		if(pInfo[playerid][player_drift_timer] > 0 && pInfo[playerid][player_driftcouter])
		{
			pInfo[playerid][player_drift_timer]--;
			
			if(pInfo[playerid][player_drift_timer] == 0)
			{
				if(pInfo[playerid][player_driftcouter])
				{	
					if(pInfo[playerid][player_drift_newpoints] > pInfo[playerid][player_largest_drift])
					{
						pInfo[playerid][player_largest_drift] = pInfo[playerid][player_drift_newpoints];
						SendClientMessage(playerid, COLOR_GOLD, ""chat" Nowy wynik driftu! zdoby³eœ %d punktów!", pInfo[playerid][player_drift_newpoints]);
						
						if(gmData[server_largest_drift] < pInfo[playerid][player_drift_newpoints])
						{
							this->config::savesql_int("stats/largest_drift", gmData[server_dayrecord]);
						}
		
					}
					format(pInfo[playerid][player_drifttd], 62, "~g~~h~Wygrana: ~w~%d$", (pInfo[playerid][player_drift_newpoints] / 2));
					
					if(pInfo[playerid][player_drift_newpoints] >= 20000)
						achievement(playerid, 22);
					else if(pInfo[playerid][player_drift_newpoints] >= 5000)
						achievement(playerid, 21);
						
					GivePlayerMoney(playerid, pInfo[playerid][player_drift_newpoints]/2);
					pInfo[playerid][player_drift_newpoints] = 0;
					 
				}
			}
		}
		/*
		if(pInfo[playerid][player_balontime] > 0)
		{
			pInfo[playerid][player_balontime]--;
			
			if(pInfo[playerid][player_balontime] == 0)
			{
				SendClientMessage(playerid, COLOR_INFO, ""chat" Czas na u¿ywanie {b}Balonu{/b} skoñczony.");
				
				BalonStop(playerid);
			}
		}*/
		if(pInfo[playerid][player_score] > pInfo[playerid][player_next_level])
		{
 			pInfo[playerid][player_level] =  floatround(floatsqroot((pInfo[playerid][player_score]/7)), floatround_floor);
			pInfo[playerid][player_next_level] = RespectToLevel(pInfo[playerid][player_level]+1);
			
		
			if(pInfo[playerid][player_level] > 1)
				InfoTDBox( playerid, splitf("Gratulacjê! awansujesz na %d level!", pInfo[playerid][player_level]) );
			pInfo[playerid][player_score_drawhide]=8;
			#if defined ADUIO_PLUGIN
			PlayCompleteMissionSound(playerid);
			#endif
		}
		if(IsPlayerInAnyVehicle(playerid))
		{
			switch(GetVehicleModel(pInfo[playerid][player_usevehicle]))
			{
				case 460,512,513,519,520,553,476,511,577,592,593:
				{
					pInfo[playerid][player_lot]++;
					
					format(string2, sizeof(string2), "~n~~n~~n~~n~~n~~n~~n~~n~Lot samolotem %d min!",  pInfo[playerid][player_lot]/60);
					GameTextForPlayer(playerid, string2, 1500, 3);
					
					if(pInfo[playerid][player_lot] >= 3600 && !pInfo[playerid][player_achievements][8])
						achievement(playerid, 8);
				}
			}
		}
		update@warn[playerid]=0;
		if(++pInfo[playerid][player_afk] < 3)
		{
			pInfo[playerid][player_connected]++;
			if(pInfo[playerid][player_timeplay]++ > (3600*24) && !pInfo[playerid][player_achievements][15])
				achievement(playerid, 15);
		}
		czh = floatround(((pInfo[playerid][player_connected]) / 3600));
		czm = floatround(((pInfo[playerid][player_connected]) / 60) % 60);
		czs = floatround(((pInfo[playerid][player_connected]) - (60 * (czm))) - (3600 * czh));
		
		new strs[60];
		if(czh < 10)
		{
			format(strs,50,"Czas gry: 0%dH ",czh);
		}
		else { 
			format(strs,50,"Czas gry: %dH ",czh);
		}
		if(czm < 10)
		{
			format(strs,50,"%s0%dM",strs,czm);
		}
		else { 
			format(strs,50,"%s%dM",strs,czm);
		}	
		PlayerTextDrawSetString(playerid,CzasGry[playerid],strs);
		 	 
		if(!pInfo[playerid][player_hidehud][hud_all])
		{
			if(pInfo[playerid][player_drawupdate]++ > 14)
			{
				pInfo[playerid][player_drawupdate] = 0;
				 
				if(!pInfo[playerid][player_hidehud][hud_pasek])
				{		
					PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdStats][1], splitf("%d", pInfo[playerid][player_level]));

					PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdStats][2], splitf("%d/%d", pInfo[playerid][player_score], pInfo[playerid][player_next_level]));
					PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdStats][3], splitf("~y~%d~w~pln", pInfo[playerid][player_portfel]));
					PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdStats][4], splitf("~r~~h~~h~%d ~w~/ ~y~~h~%d ~w~/ ~g~~h~%d",   pInfo[playerid][player_kills], pInfo[playerid][player_skill], pInfo[playerid][player_deaths]));
			
				}
			}			
			if(!pInfo[playerid][player_hidehud][hud_fps]) PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdStats][5], splitf("%0.2f / ~y~~h~%d ~w~/ ~p~~h~%dms",NetStats_PacketLossPercent(playerid),GetPlayerFPS(playerid),GetPlayerPing(playerid)));
		}
		
		// kicker fps
		if(GetPlayerFPS(playerid) > 120)
		{
			if(pInfo[playerid][player_id] == 69 || pInfo[playerid][player_id] == 183) {}
			else {
				pInfo[playerid][fpswkickerwarn]++;
				if(pInfo[playerid][fpswkickerwarn] > 35)
				{
					AddPlayerPenalty(playerid, P_KICK, INVALID_PLAYER_ID, 90, "Zbyt du¿a liczba FPS");
				}
			}
		}
		if(KURWA != 69) {
			if(GetPlayerWeapon(playerid) == 38 && pInfo[playerid][player_admin] < 1 && pInfo[playerid][player_arena] != stats_minigun)
			{			
				new ammo = GetPlayerAmmo(playerid);
				if(ammo > 10)
				{
					new str[128], nn[40];
					GetPlayerName(playerid,nn,40);
					format(str,128,"Gracz %s (%d) posiada miniguna. Wpisz /KURWAMACCHUJ zeby wylaczyc sprawdzanie miniguna: ammo: %d",nn,playerid, ammo);
					for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
					{
						if(pInfo[i][player_admin] >= 2)
						{
							SendClientMessage(i,COLOR_RED, str);
						}
					}
				}
			}
		}
		
		if(czh > 0)
		{
			if(czh == pInfo[playerid][player_hourgame])
			{
				if(pInfo[playerid][player_tag])
				{
					GivePlayerScore(playerid, 100*czh);
					SendClientMessageToAll(COLOR_INFO2, ""chat" Gracz %s (%d) dostaje %d puntków respektu za kolejn¹ godzinê gry!", playerNick(playerid), playerid, 100*czh);
				}
				else 
				{
					GivePlayerScore(playerid, 50);
					SendClientMessageToAll(COLOR_INFO2, ""chat" Gracz %s (%d) dostaje 50 punktów respektu za kolejn¹ godzinê gry!", playerNick(playerid), playerid);
				}
				pInfo[playerid][player_hourgame]++;
			}
		}
		/*
		if(pInfo[playerid][player_drawupdate]++ > 10)
		{
			pInfo[playerid][player_drawupdate] = 0;
			format(string2, sizeof(string2), "/Portfel: %dzl~n~~n~Respekt: %s/%s", pInfo[playerid][player_portfel], FormatNumber(pInfo[playerid][player_score]), FormatNumber(pInfo[playerid][player_next_level]));
			PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdStats][0], string2);
			
			format(string2, sizeof(string2), "Level: %d~n~~n~Czas gry: %dh %dm %ds", pInfo[playerid][player_level], czh, czm, czs);
			PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdStats][1], string2);
			
			format(string2, sizeof(string2), " n~~n~Samobojstw: %d", pInfo[playerid][player_kills], pInfo[playerid][player_deaths], pInfo[playerid][player_suicide]);
			PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdStats][2], string2);
		}*/
	 
		
		czm=GetPlayerPing(playerid);
		//if(pInfo[playerid][player_connected] % 3) PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdNT], splitf("~w~Ping: ~r~%d~n~~w~FPS: ~y~%d~n~~w~P-Loss: ~g~%.2f",czm,GetPlayerFPS(playerid),NetStats_PacketLossPercent(playerid)));
		 
		if(++pInfo[playerid][player_pingupdate] > 6 && pInfo[playerid][player_connected] > 40)
		{
			if(pInfo[playerid][player_pingcheck] > 20)
			{
				pInfo[playerid][player_pingcheck] = 0;
				pInfo[playerid][player_pingsum] = 0;
			}
			pInfo[playerid][player_pingupdate] = 0;
 			pInfo[playerid][player_pingsum] += czm;
			pInfo[playerid][player_pingcheck]++;
			pInfo[playerid][player_averageping] = pInfo[playerid][player_pingsum] / pInfo[playerid][player_pingcheck];
			 
			if(((pInfo[playerid][player_averageping] > gmData[max_ping]) || (czm>(gmData[max_ping]*2))) && pInfo[playerid][player_pingcheck] > 3)
			{
				switch(++pInfo[playerid][player_pingwarnings])
				{
					case 1..4: SendClientMessage(playerid, COLOR_INFO2, ""chat" Uwaga! Twój ping {EE0000}(%d/%d){/b} jest zbyt wysoki aby graæ na serwerze! Zmniejsz ping! ostrze¿enie %d/4. ", czm, gmData[max_ping], pInfo[playerid][player_pingwarnings]);
					case 5..6:
					{
						SendClientMessage(playerid, COLOR_RED, "[Kick] Zosta³eœ wyrzucony z serwera przez System, powód: zbyt wysoki ping.");	
						SendClientMessageToAll(COLOR_SAMP, ""chat" Gracz %s (%d) zosta³ wyrzucony przez System za Ping", pInfo[playerid][player_name], playerid);
						
						InfoBox(playerid, "Zosta³eœ wyrzcony z servera");
						Kick(playerid);
						
						continue;
					}
				}
			}
			else if (pInfo[playerid][player_pingwarnings]>0)
				pInfo[playerid][player_pingwarnings]--;
		}
		//hab_Timer(playerid);
		
			
 	}
	gmData[server_infolevel] = false;
}
 
 
//task updateSpeed[250]()
Public:updateSpeed()
{
	static Float:ST[7], Float:vhelath, speed, xx;
 
	foreach( new playerid : Drivers)
	{
		pInfo[playerid][player_usevehicle] = GetPlayerVehicleID(playerid);
		if(pInfo[playerid][player_usevehicle] != pInfo[playerid][player_lastvehicle])
		{
			pInfo[playerid][player_lastvehicle] = pInfo[playerid][player_usevehicle];
			OnPlayerChangeVehicle(playerid);
		}

		xx = GetVehicleModel(pInfo[playerid][player_usevehicle]);
		if(!pInfo[playerid][player_usevehicle]) continue;
		if(!xx) continue;
		if(xx < 50) continue;
		
		GetVehicleHealth(pInfo[playerid][player_usevehicle], vhelath);
		
		if(pInfo[playerid][player_driftcouter])
		{
			if(++pInfo[playerid][player_drift_step] > 2)
			{
				
				if(pInfo[playerid][player_drift_step] > 5)
				{
					pInfo[playerid][player_drift_step] = 0;
					 	
					GetVehiclePos(pInfo[playerid][player_usevehicle], pInfo[playerid][player_driftpos][0], pInfo[playerid][player_driftpos][1], pInfo[playerid][player_driftpos][2]);
				}
				else
				{
				
					GetPlayerPos(playerid, ST[0], ST[1], ST[2]);
				 
					GetVehicleZAngle(pInfo[playerid][player_usevehicle], ST[3]);
					
					ST[4] = GetPlayerTheoreticAngle(playerid, ST[0], ST[1], ST[2], ST[3]);
					ST[5] = floatmul(floatsqroot(floatadd(floatadd(floatpower(floatabs(floatsub(ST[0], pInfo[playerid][player_drift_pos][0])), 2), floatpower(floatabs(floatsub(ST[1], pInfo[playerid][player_drift_pos][1])), 2)), floatpower(floatabs(floatsub(ST[2], pInfo[playerid][player_drift_pos][2])), 2))), 12);

					if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsCar(pInfo[playerid][player_usevehicle]) && floatabs(floatsub(ST[3], ST[4])) > DRIFT_MINKAT && floatabs(floatsub(ST[3], ST[4])) < DRIFT_MAXKAT && ST[5] > DRIFT_SPEED)
					{
						if(!pInfo[playerid][player_drift_timer]) 
							pInfo[playerid][player_drift_timer] = 3;
						else
							pInfo[playerid][player_drift_timer] += 3;
							
						if(pInfo[playerid][player_drift_timer]>8) pInfo[playerid][player_drift_timer] = 8;
						pInfo[playerid][player_drift_newpoints] += floatval(floatabs(floatsub(ST[3], ST[4])) * 3 * (ST[5]*0.1))/24;  
					}
					if(pInfo[playerid][player_drift_newpoints] > 0)
					{
						//if( pInfo[playerid][player_drift_newpoints] > 5000 ) pInfo[playerid][player_drift_newpoints] = 0;
 						format(pInfo[playerid][player_drifttd], 62, "Driftujesz: ~w~~h~%d ~n~Podliczenie za: %ds", pInfo[playerid][player_drift_newpoints], pInfo[playerid][player_drift_timer]);
							
						if(!script_tr[iswin][playerid] && Iter_Contains(t_r_players, playerid) && script_tr[t_zadanie] == 4)
						{
							script_tr[iswin][playerid] = true;
							InfoBox(playerid, "Zaliczono!");
						}
					}
					else 
					{
						pInfo[playerid][player_drifttd][0] = EOS;
					}
					PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdLicznik][2],pInfo[playerid][player_drifttd]);
					pInfo[playerid][player_drift_pos][0] = ST[0];
					pInfo[playerid][player_drift_pos][1] = ST[1];
					pInfo[playerid][player_drift_pos][2] = ST[2];
				}
			}
		}
		
		vhelath = (vhelath - 250.0) / 7.5;
		if (vhelath>100) vhelath = 100;
		
		GetVehicleVelocity(pInfo[playerid][player_usevehicle], ST[0], ST[1], ST[2]);
		
		speed =  floatround(floatmul(VectorSize(ST[0], ST[1], ST[2]), 190.0));
		//speed = floatval(VectorSize(ST[0], ST[1], ST[2])); //floatround(floatsqroot(floatpower(ST[0], 2) + floatpower(ST[1], 2) + floatpower(ST[2], 2)) * 200);
		
		if(!speed && !script_tr[iswin][playerid] && Iter_Contains(t_r_players, playerid) && script_tr[t_zadanie] == 2)
		{
			script_tr[iswin][playerid] = true;
			InfoBox(playerid, "Zaliczono!");
		}
		if(pInfo[playerid][player_car_god] == true)
		{
			RepairVehicle(pInfo[playerid][player_usevehicle]);
		    SetVehicleHealth(pInfo[playerid][player_usevehicle],99999999);
		}
		
		//PlayerTextDrawColor(playerid, pInfo[playerid][player_TdLicznik][0], 20>speed?20:(speed>255?255:speed));
		format(string2, sizeof(string2), "%03d", speed);
		/*switch(speed)
		{
			case 0..70:format(string2, sizeof(string2), "~g~%03d ~w~~h~km/h", speed);
			case 71..140:format(string2, sizeof(string2), "~y~%d km/h", speed);
			case 141..9999:format(string2, sizeof(string2), "~r~%d km/h", speed);
			
		}*/
		
		PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdLicznik][0], string2);
		
		format(string2, sizeof(string2), "%s", VehicleNames[xx-400]);
		PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdLicznik][1], string2);


 		if (vhelath>=95) 
				PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdLicznik][3], "~g~]]]]]");
		else if (vhelath >= 80)
				PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdLicznik][3], "~g~]]]]~l~]");
		else if (vhelath >= 70)
				PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdLicznik][3], "~y~~h~]]]~l~]]");
		else if (vhelath >= 55)
				PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdLicznik][3], "~y~]]]~l~]]");
		else if (vhelath >= 33)
				PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdLicznik][3], "~y~]]~l~]]]");
		else if (vhelath >= 10)
				PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdLicznik][3], "~r~]~l~]]]]");
		else 
				PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdLicznik][3], "~l~]]]]]");
		

		if(pInfo[playerid][player_car_have] && gmData[player_vehicleid][playerid] == pInfo[playerid][player_usevehicle])
		{
			if(pInfo[playerid][player_afk] < 3)
			{ 
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && ++pInfo[playerid][player_car_licznik] > 9)
				{
					pInfo[playerid][player_car_licznik] = 0;
					GetVehiclePos(gmData[player_vehicleid][playerid], pInfo[playerid][player_car_pos][0], pInfo[playerid][player_car_pos][1], pInfo[playerid][player_car_pos][2]);
					GetVehicleZAngle(gmData[player_vehicleid][playerid], pInfo[playerid][player_car_pos][3]);
			 
					GetVehicleVelocity(pInfo[playerid][player_usevehicle], ST[0], ST[1], ST[2]);
					ST[3] = floatsqroot(floatpower(floatabs(ST[0]), 2.0) + floatpower(floatabs(ST[1]), 2.0) + floatpower(floatabs(ST[2]), 2.0)) * 179.28625;
				
					pInfo[playerid][player_car_przebieg] += ST[3]/(2000);
						
					
					format(string2, 162, "{E53E01}W³aœciciel: {FCAD43}%s\n{E53E01}Przebieg: {FCAD43}%.1f KM" , pInfo[playerid][player_name], pInfo[playerid][player_car_przebieg]);
					Update3DTextLabelText(gmData[player_vehicle][playerid], 0xFFFFFFFF, string2);
					
					if(pInfo[playerid][player_car_przebieg] >= 500.0 && !pInfo[playerid][player_achievements][10])
						achievement(playerid, 10);
				}
				else
				{
					format(string2, 162, "{E53E01}W³aœciciel: {FCAD43}%s\n{E53E01}Przebieg: {FCAD43}%.1f KM" , pInfo[playerid][player_name] , pInfo[playerid][player_car_przebieg]);
					Update3DTextLabelText(gmData[player_vehicle][playerid], 0xFFFFFFFF, string2);
				}
			}
		}
	}
	
	if(script_tr[t_zadanie] && script_tr[statees] == true)
	{
		if(GetProgressBarValue(script_tr[tr_bar]) > 1.1)
		{
			SetProgressBarValue(script_tr[tr_bar], GetProgressBarValue(script_tr[tr_bar]) - 1.0);
			foreach( new playerid : t_r_players)
			{
				ShowProgressBarForPlayer(playerid, script_tr[tr_bar]);
			}
		}
		else 
		{
			script_tr[t_zadanie] = 0;
			script_tr[b_time] = 15;
			
			ShowStatsTR();
			HideProgressBarForAll(script_tr[tr_bar]);
			
		}
	}
} 