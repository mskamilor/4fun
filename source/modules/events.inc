/*
          Events [NOT VERSION]
      (c) Copyright 2013-2014 by mrdrifter
 
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
	  @date      : 16 listopada 2013
	  @update    : 3 stycznia 2014
  
 */ 
 
new ee_stri[256], z_ee_stri[64], stev_name[64], stev_cmd[32], stev_time, statsUpdate;
new Text:TextDrawEventStart;

#define _derby 1
#define d_d_start_players 2
#define d_d_start_players_max 100 

enum d_d_event 
{
	winreed, 
	bool:statees, 
	bool:starting, 
	Timer, 
	autho[MAX_PLAYERS + 2], 
	_spawn[MAX_PLAYERS], 
	arena, 
	dd_toupdate,
	load_aren
}
new script_dd[d_d_event];
new Iterator:d_d_players<MAX_PLAYERS>;
 
 
#define MAX_DD_AREN 7
#define MAX_DD_AREN_SP 80

new dd_losowanie[MAX_DD_AREN];

enum dd_arens{

	dd_name[80], 
	uid, 
	loades, 
	bool:active, 
	dd_vehicle
};
new script_dd_aren[MAX_DD_AREN][dd_arens];

enum dd_arens_{
	Float:possek[4]
};
new script_dd_spawn[MAX_DD_AREN][MAX_DD_AREN_SP][dd_arens_];

 
 
 
CMD:ddexit(playerid, params[])
{
	if(removeIsEvent(playerid) == 0)
		return SendClientMessage(playerid, COLOR_ERROR, " Nie jesteœ zapisany(a) na ¿aden event");
 
	SendClientMessage(playerid, COLOR_ERROR, " Wypisa³eœ(aœ) siê z Derbów.");
	return 1;
}

CMD:dd(playerid, params[])
{
 	if(Iter_Contains(d_d_players, playerid))
 		return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *(DDb} Jesteœ ju¿ zapisany(a) na Derby");
	if(Iter_Count(d_d_players) >= script_dd_aren[script_dd[arena]][loades] && script_dd[starting] == true) 
		return SendClientMessage(playerid, COLOR_ERROR, " Na Derby zapisa³o siê zbyt du¿o osób, spróbuj w nastêpnej kolejce."); 
	if(script_dd[statees] == true) 
		return SendClientMessage(playerid, COLOR_ERROR, " Derby aktualnie trwaj¹");
	
	if(pInfo[playerid][player_objected])
		return InfoBox(playerid, "Nie mozesz zapisac sie na event poniewaz masz wylaczone obiekty");

	removeIsEvent(playerid);

	Iter_Add(d_d_players, playerid);
	if(Iter_Count(d_d_players) >= d_d_start_players && script_dd[statees] == false && script_dd[starting] == false)
	{
	
		start_dd(); 
		script_dd[starting] = true;

	}
	statsUpdate = 11;
	UpdateEvStat();
	SendClientMessage(playerid, COLOR_GREEN, " Zapisa³eœ(aœ) siê na Derby.");
 	return 1;
}
stock start_dd()
{
	if(script_dd[load_aren] == 0) 
	{
		Iter_Clear(d_d_players);
		UpdateEvStat();	
		script_dd[starting] = false;
		return SendClientMessageToAll(-1, " Derby nie mog¹ wystartowaæ z powodu braku areny");
	}
	UpdateEvStat();
	if(script_dd[starting] == true) return 1;
	new losuj = dd_losowanie[random(script_dd[load_aren])];
	if(script_dd_aren[losuj][active] == false) return start_dd();
	script_dd[arena] = losuj;
   	SetTimer("script_dd_Go", 20000, 0);
	TextDrawUpdateEventStart("Derby", "/DD");
   	SendClientMessageToAll(-1, "››› {008ae6}Derby{/b} wystartuj¹ za {008ae6}20 sekund {/b}Zapisy nadal trwaj¹ {008ae6}(/dd)");
	return 1;
}
forward script_dd_Go();
public script_dd_Go()
{
	script_dd[starting] = false;
	if(Iter_Count(d_d_players) <= 1)
	{
	 
	    //KillTimer(script_dd[Timer]);
		Iter_Clear(d_d_players);
	    script_dd[statees] = false;
		SendClientMessageToAll(COLOR_ERROR, " Derby nie wystartowa³y z powodu braku graczy.");
	    return 1;
	}
	 
	script_dd[winreed] = INVALID_PLAYER_ID;
	script_dd[dd_toupdate] = 4;
	statsUpdate = 11;
	UpdateEvStat();
	SendClientMessageToAll(-1, " {008ae6}Derby{/b} wystartowa³y!");
	////();
 
	//();
	new spawn;
	//Streamer_UpdateEx(p, script_dd_spawn[script_dd[arena]] [0][possek][0], script_dd_spawn[script_dd[arena]][0][possek][1], script_dd_spawn[script_dd[arena]][0][possek][2]);
  	foreach (new p : d_d_players)
   	{
   	    if(!IsPlayerConnected(p)) continue;
		//Streamer_Update(p);
		//if(p > sizeof(script_dd_spawn[script_dd[arena]]))break; 
		SetPlayerArmour(p, 0.0);
        ResetPlayerWeapons(p);
		SetPlayerVirtualWorld(p, 147);
		SetPlayerInterior(p, 0);
		RemovePlayerFromVehicle(p);
		SetPlayerPos(p, script_dd_spawn[script_dd[arena]][spawn][possek][0], script_dd_spawn[script_dd[arena]][spawn][possek][1], script_dd_spawn[script_dd[arena]][spawn][possek][2] + 11.0);
		SetPlayerFacingAngle(p, script_dd_spawn[script_dd[arena]][spawn][possek][3]);
		script_dd[_spawn][p] = spawn;
		spawn++;
		PlayerEventTDSet(p, "Startuje", "Derby");
		 
	}
	foreach (new p : d_d_players)
	{
		TogglePlayerControllable(p, 0);
	}
 	script_dd[statees] = true;
	 
 	SetTimer("script_dd_veh", 1500, 0);
	 
	return 1;
}
forward script_dd_veh();
public script_dd_veh(){
	#define spawn script_dd[_spawn][p]
	foreach (new p : d_d_players)
   	{
		SetPlayerPos(p, script_dd_spawn[script_dd[arena]][spawn][possek][0], script_dd_spawn[script_dd[arena]][spawn][possek][1], script_dd_spawn[script_dd[arena]][spawn][possek][2] + 11.0);
		SetPlayerFacingAngle(p, script_dd_spawn[script_dd[arena]][spawn][possek][3]);

 		script_dd[autho][p] = CreatePlayerVehicle(p, script_dd_aren[script_dd[arena]][dd_vehicle], script_dd_spawn[script_dd[arena]][spawn][possek][3]); //CreateVehicle(script_dd_aren[script_dd[arena]][dd_vehicle], script_dd_spawn[script_dd[arena]][spawn][possek][0], script_dd_spawn[script_dd[arena]][spawn][possek][1], script_dd_spawn[script_dd[arena]][spawn][possek][2], script_dd_spawn[script_dd[arena]][spawn][possek][3] + 8.0, -1, -1, 99999);
	 
		SetVehiclePos(script_dd[autho][p], script_dd_spawn[script_dd[arena]][spawn][possek][0], script_dd_spawn[script_dd[arena]][spawn][possek][1], script_dd_spawn[script_dd[arena]][spawn][possek][2] + 5.0);
		SetVehicleVirtualWorld(script_dd[autho][p], 147);
		SetPlayerHealth(p, 100.0);
		
		PutPlayerInVehicle(p, script_dd[autho][p], 0);
		 
		//SendClientMessage(p, COLOR_GREEN, "ID Twojego pojazdu to: %d", script_dd[autho][p]);
		TogglePlayerControllable(p, 0);
		SetVehiclePos(script_dd[autho][p], script_dd_spawn[script_dd[arena]][spawn][possek][0], script_dd_spawn[script_dd[arena]][spawn][possek][1], script_dd_spawn[script_dd[arena]][spawn][possek][2] + 5.0);
	}
	#undef spawn
	SetTimerEx("script_dd_rlg", 1000, 0, "d", 3);
}
forward script_dd_rlg(czas);
public script_dd_rlg(czas)
{
	if(script_dd[statees] != true) return 1;
	
 
	if(czas > 0)
	{
		format(string2, sizeof(string2), "~g~Start za: ~r~%d", czas);
		foreach (new i : d_d_players)
		{
			new Float:pos[4];
			GetPlayerPos(i, pos[0], pos[1], pos[2]);
			if(pos[2] < script_dd_spawn[script_dd[arena]][script_dd[_spawn][i] ][possek][2])
			{
				SetVehiclePos(script_dd[autho][i], script_dd_spawn[script_dd[arena]] [script_dd[_spawn][i]][possek][0], script_dd_spawn[script_dd[arena]][script_dd[_spawn][i] ][possek][1], script_dd_spawn[script_dd[arena]][script_dd[_spawn][i] ][possek][2] + 1.0);
			}
			PlayerEventTDSet(i, string2, "Derby");
		}
		SetTimerEx("script_dd_rlg", 1000, 0, "d", czas - 1);
		return 1;
	}
	
	foreach (new i : d_d_players)
   	{
   	    if(!IsPlayerConnected(i)) continue;
		TogglePlayerControllable(i, 1);
		SetVehiclePos(script_dd[autho][i], script_dd_spawn[script_dd[arena]] [script_dd[_spawn][i]][possek][0], script_dd_spawn[script_dd[arena]][script_dd[_spawn][i] ][possek][1], script_dd_spawn[script_dd[arena]][script_dd[_spawn][i] ][possek][2] + 2.0);
   		PlayerEventTDSet(i, "Trwa", "Derby");
	}

   // script_dd[Timer] = SetTimer("script_dd_update", 1000, 1);
	return 1;
}

forward script_dd_update();
public script_dd_update()
{
	if(script_dd[statees] != true) return 1;
	if(script_dd[dd_toupdate] > 0)
	{
		script_dd[dd_toupdate]--;
		return 1;
	}
	if(Iter_Count(d_d_players) == 0)
	{
		//();
		// KillTimer(script_dd[Timer]);
		Iter_Clear(d_d_players);
		script_dd[statees] = false;
		SendClientMessageToAll(COLOR_ERROR, " Derby zosta³y zakoñczona z powodu braku graczy.");
		return 1;
	}
	
	if(Iter_Count(d_d_players) == 1)
	{
		//KillTimer(script_dd[Timer]);
		foreach (new p : d_d_players)
		{
			if(!IsPlayerConnected(p)) continue;
			
			SetPlayerColorEx(p);
			
			SetPlayerVirtualWorld(p, 0);
			TogglePlayerControllable(p, 1);
			SetPlayerHealth(p, 100.0);
			ResetPlayerWeapons(p);
			script_dd[statees] = false;
			
			OnPlayerSpawn(p);
			new kasy = random(1000), score = random(300);
			GivePlayerScore(p, score);
			GivePlayerMoney(p, kasy);
			#if defined ADUIO_PLUGIN
			PlayCompleteMissionSound(p);
			PlayCompleteMissionSound(p);
			#endif
			SendClientMessageToAll(-1, "{008ae6} %s (%d) {/b}po raz {008ae6}%d{/b} wygra³ {008ae6}/DD{/b}. I otrzymuje {008ae6}%d Score i %d${/b} ", pInfo[p][player_name], p, addPointEvent(p, stats_dd), score, kasy);
			Iter_Remove(d_d_players, p);
			break;
		}
		Iter_Clear(d_d_players);
		//();
		
		script_dd[statees] = false;
		return 1;
	}
	
	if(script_dd[winreed] != INVALID_PLAYER_ID)
	{
		
		//KillTimer(script_dd[Timer]);
		new kasy = random(10000), score = random(300);
		GivePlayerMoney(script_dd[winreed], kasy);
		GivePlayerScore(script_dd[winreed], score);
		#if defined ADUIO_PLUGIN
		PlayCompleteMissionSound(script_dd[winreed]);
		#endif
		SendClientMessageToAll(-1, " {008ae6}%s (%d) {/b}wygra³ {008ae6}/dd{/b}. I otrzymuje {008ae6}%d Score i %d${/b} ", pInfo[script_dd[winreed]][player_name], script_dd[winreed], addPointEvent(script_dd[winreed], stats_dd), score, kasy);
		//();
		script_dd[statees] = false;
		foreach (new p : d_d_players)
		{
			OnPlayerSpawn(p);
		}
		Iter_Clear(d_d_players);
		UpdateEvStat();
		return 1;
	}
	new Float:player_possek[4], next;
	format(ee_stri, sizeof(ee_stri), "~r~Graczy ~g~%d", Iter_Count(d_d_players));
	foreach (new p : d_d_players)
	{
		if(!IsPlayerConnected(p)) continue;
		
		
		PlayerEventTDSet(p, ee_stri, "Derby");
		GetPlayerPos(p, player_possek[0], player_possek[1], player_possek[2]);
		if(floatround(player_possek[2]) <= (script_dd_spawn[script_dd[arena]][script_dd[_spawn][p]][possek][2]/2))
		{
			if(p >= MAX_PLAYERS)
			{
				Iter_SafeRemove(d_d_players, p, next);
				p = next;
			}
			if(!IsPlayerConnected(p)) continue;
			OnPlayerSpawn(p);
			SetPlayerColorEx(p);
			Iter_SafeRemove(d_d_players, p, next);
			p = next;
			
			continue;
		}
		if(pInfo[p][player_afk] > 3)
		{
			if(p >= MAX_PLAYERS)
			{
				Iter_SafeRemove(d_d_players, p, next);
				p = next;
			}
			if(!IsPlayerConnected(p)) continue;
			OnPlayerSpawn(p);
			SetPlayerColorEx(p);
			Iter_SafeRemove(d_d_players, p, next);
			p = next;
			
			continue;
		}
		if(!IsPlayerInRangeOfPoint(p, 900.0, script_dd_spawn[script_dd[arena]] [0][possek][0], script_dd_spawn[script_dd[arena]][0][possek][1], script_dd_spawn[script_dd[arena]][0][possek][2])){
			
			if(p >= MAX_PLAYERS)
			{
				Iter_SafeRemove(d_d_players, p, next);
				p = next;
			}
			if(!IsPlayerConnected(p)) continue;
			OnPlayerSpawn(p);
			
			Iter_SafeRemove(d_d_players, p, next);
			p = next;
			
			continue;
		}
		if(!IsPlayerInAnyVehicle(p))
		{
			if(p >= MAX_PLAYERS)
			{
				Iter_SafeRemove(d_d_players, p, next);
				p = next;
			}
			if(!IsPlayerConnected(p)) continue;
			OnPlayerSpawn(p);
			
			Iter_SafeRemove(d_d_players, p, next);
			p = next;

			continue;
		}
		
	}
 	
	return 1;
}



 
 
 

LoadEvent_DD()
{
	new czas = GetTickCount();
	 
	mysql_query("SELECT * FROM "prefix"_dd");
	mysql_store_result();
	new f[20], f2[55];
	for(new i;i<mysql_num_rows();i++)
	{
		mysql_data_seek(i);//
		mysql_fetch_row_data();
		
		mysql_fetch_field("id", f);	
		script_dd_aren[strval(f)][uid] = strval(f);
		script_dd_aren[strval(f)][active] = true;
		dd_losowanie[i] = strval(f);
		
		mysql_fetch_field("dName", script_dd_aren[script_dd_aren[i][uid]][dd_name]);	
		
		mysql_fetch_field("dVehicle", f2);	
		script_dd_aren[strval(f)][dd_vehicle] = strval(f2);
		
		 
		script_dd[load_aren]++;
		
		 
	}
	printf("[load] wczytanych aren dd:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	mysql_free_result();

}
LoadEvent_DDSpawn(){
	new czas = GetTickCount();
	 
	mysql_query("SELECT * FROM "prefix"_dd_sp");
	mysql_store_result();
	new cord[128];
	new f[20], f2, glob, spawn;
	for(new i;i<mysql_num_rows();i++)
	{
		mysql_data_seek(i);//
		mysql_fetch_row_data();
		
		mysql_fetch_field("dd_id", f);	
		f2 = strval(f);
		if(f2 != glob) {spawn = 0;}
		mysql_fetch_field("cordob", cord);	
		if(sscanf(cord, "p<,>a<f>[4]", script_dd_spawn[f2][spawn][possek])) {printf("blad rodzielania");continue;}
		script_dd_aren[f2][loades]++; 
		 
	//	printf("%f", script_dd_spawn[f2]  [spawn][possek][0]);
		spawn++;
		glob = f2;
	}
	printf("[load] wczytanych spawnów dd:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	mysql_free_result();

} 
   
#define _hay 2
#define h_y_start_players 2
#define h_y_start_players_max 50 

#define hy_sek_weapon 7 //co ile sekund ma dawaæ broñ //domyœlnie 10 sekund
enum h_y_event {
	winreed, 
	hay[101], 
	bool:statees, 
	bool:started, 
	Timer, 
	 
}
new script_hy[h_y_event];
new Iterator:h_y_players<MAX_PLAYERS+2>;


 

 

#define _OneShoot 2
#define o_s_start_players 2
#define o_s_start_players_max 50

enum o_s_event {
	winreed,
	OneShoot[101],
	bool:statees,
	bool:started,
	Timer,
	
}
new script_os[o_s_event];
new Iterator:o_s_players<MAX_PLAYERS+2>;







CMD:osexit(playerid, params[])
{
	if(removeIsEvent(playerid) == 0)return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Nie jesteœ zapisany(a) na ¿aden event.");
	SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} ›››{/b}  Wypisa³eœ(aœ) siê z OneShoot.");
	return 1;
}

CMD:os(playerid, params[])
{
	if(Iter_Contains(o_s_players, playerid))return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Jesteœ ju¿ zapisany(a) na OneShoot.");
	if(Iter_Count(o_s_players) >= o_s_start_players_max) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Na OneShoot zapisa³o siê zbyt du¿o osób, spróbuj w nastêpnej kolejce.");
	if(script_os[statees] == true) 
		return SendClientMessage(playerid, COLOR_ERROR, "Os aktualnie trwa");
	//if(removeIsEvent(playerid) == 1) SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} ›››{/b}  By³eœ(aœ), zapisany(a), na inny event zosta³eœ(aœ) z niego wypisany(a).");
	removeIsEvent(playerid);
	
	Iter_Add(o_s_players, playerid);
	if(Iter_Count(o_s_players) == o_s_start_players && script_os[statees] == false  && script_os[started] == false)
	{
		SetTimer("script_os_Go", 20000, 0);
		SendClientMessageToAll(-1, "››› {008ae6}OneShoot {/b}wystartuje za {008ae6}20 sekund {/b}Zapisy nadal trwaj¹ {008ae6}(/os)");
		TextDrawUpdateEventStart("OneShoot", "/os");
		script_os[started] = true;
	}
	SendClientMessage(playerid, -1, "{FFFFFF} ›››{/b}  Zapisa³eœ(aœ) siê na {008ae6}OneShoot.");
	return 1;
}

forward script_os_Go();
public script_os_Go()
{
	script_os[started] = false;
	if(Iter_Count(o_s_players) <= 1)
	{
		
		
		Iter_Clear(o_s_players);
		script_os[statees] = false;
		SendClientMessageToAll(-1, " ››› {008ae6}OneShoot{/b} nie wystartowa³y z powodu braku graczy.");
		return 1;
	}
	 
	script_os[winreed] = INVALID_PLAYER_ID;
	script_os[statees] = true;
	
	SendClientMessageToAll(-1, "{FFFFFF} ››› {008ae6}OneShoot{/b] wystartowa³o!");
	
	
	foreach (new p : o_s_players)
	{
		if(!IsPlayerConnected(p)) continue;
		SetPlayerArmour(p, 0.0);
		
		FreezePlayerTime(p, 3);
		ResetPlayerWeapons(p);
	
		SetPlayerHealth(p, 10.000000);
		SetPlayerArmour(p, 0.0);
		GivePlayerWeapon(p, 24, 9999);
		switch(random(10))
		{
			case 0:
			{
				SetPlayerPos(p, 298.277008, 173.203994, 1007.169982);
				SetPlayerInterior(p, 3);
				SetPlayerVirtualWorld(p, 200);
			}
			case 1:
			{
				SetPlayerPos(p, 276.273010, 186.367996, 1007.169982);
				SetPlayerInterior(p, 3);
				SetPlayerVirtualWorld(p, 200);
			}
			case 2:
			{
				SetPlayerPos(p, 246.565002, 176.500000, 1003.030029);
				SetPlayerInterior(p, 3);
				SetPlayerVirtualWorld(p, 200);
			}
			case 3:
			{
				SetPlayerPos(p, 230.483001, 161.380996, 1003.020019);
				SetPlayerInterior(p, 3);
				SetPlayerVirtualWorld(p, 200);
			}
			case 4:
			{
				SetPlayerPos(p, 231.630996, 141.561996, 1003.020019);
				SetPlayerInterior(p, 3);
				SetPlayerVirtualWorld(p, 200);
			}
			case 5:
			{
				SetPlayerPos(p, 221.617996, 146.522994, 1003.020019);
				SetPlayerInterior(p, 3);
				SetPlayerVirtualWorld(p, 200);
			}
			case 6:
			{
				SetPlayerPos(p, 211.166000, 146.794006, 1003.020019);
				SetPlayerInterior(p, 3);
				SetPlayerVirtualWorld(p, 200);
			}
			case 7:
			{
				SetPlayerPos(p, 214.261001, 165.919998, 1003.020019);
				SetPlayerInterior(p, 3);
				SetPlayerVirtualWorld(p, 200);
			}
			case 8:
			{
				SetPlayerPos(p, 193.046997, 178.776992, 1003.020019);
				SetPlayerInterior(p, 3);
				SetPlayerVirtualWorld(p, 200);
			}
			case 9:
			{
				SetPlayerPos(p, 193.152999, 157.944000, 1003.020019);
				SetPlayerInterior(p, 3);
				SetPlayerVirtualWorld(p, 200);
			}
			case 10:
			{
				SetPlayerPos(p, 218.279006, 182.927001, 1003.030029);
				SetPlayerInterior(p, 3);
				SetPlayerVirtualWorld(p, 200);
			}
		}
		
		SetPlayerVirtualWorld(p, 225);
		SetCameraBehindPlayer(p);
		
	}
	
	SetTimer("script_os_rlg", 1000, 0);
	return 1;
}

 

forward script_os_update();
public script_os_update()
{
	if(script_os[statees] != true) return 1;
	
	if(Iter_Count(o_s_players) == 0)
	{
		
		Iter_Clear(o_s_players);
		script_os[statees] = false;
		SendClientMessageToAll(-1, "{FFFFFF} ›››{/b} {008ae6}OneShoot{/b} zosta³o zakoñczone z powodu braku graczy.");
		return 1;
	}
	
	if(Iter_Count(o_s_players) == 1) //tutaaj jesli jest jeden
	{
		
		new p = Iter_First(o_s_players);
		if(IsPlayerConnected(p))
		{
			
			
			SetPlayerVirtualWorld(p, 0);
			TogglePlayerControllable(p, 1);
			SetPlayerHealth(p, 100.0);
			ResetPlayerWeapons(p);
			#if defined ADUIO_PLUGIN
			PlayCompleteMissionSound(p);
			#endif
			OnPlayerSpawn(p);
			
			new kasy = random(10000), score = random(300);
			GivePlayerScore(p, score);
			GivePlayerMoney(p, kasy);
			SendClientMessageToAll(-1, " {008ae6}%s (%d) {/b}po raz {008ae6}%d{/b} wygra³ {008ae6}/OS{/b}. I otrzymuje {008ae6}%d Score i %d${/b} ", pInfo[p][player_name], p, addPointEvent(p, stats_os), score, kasy);
			Iter_Remove(o_s_players, p);
		}
		
		Iter_Clear(o_s_players);
		script_os[statees] = false;
		return 1;
	}
	
	if(script_os[winreed] != INVALID_PLAYER_ID)
	{
		
		GivePlayerMoney(script_os[winreed], 10000);
		
		new kasy = random(10000), score = random(300);
		
		GivePlayerScore(script_os[winreed] , score);
		GivePlayerMoney(script_os[winreed] , kasy);
		
		#if defined ADUIO_PLUGIN
		PlayCompleteMissionSound(script_os[winreed]);
		#endif
		SendClientMessageToAll(-1, " {008ae6}%s (%d){/b} po raz {008ae6}%d{/b} wygra³ {008ae6}/OS{/b}. I otrzymuje {008ae6}%d Score i %d${/b} ", pInfo[script_os[winreed]][player_name], script_os[winreed], addPointEvent(script_os[winreed], stats_os), score, kasy);
		
		script_os[statees] = false;
		foreach (new ply : o_s_players){
			OnPlayerSpawn(ply);
		}
		Iter_Clear(o_s_players);
		return 1;
	}
	new next;
	if(Iter_Count(o_s_players) > 0){
		
		foreach (new ply : o_s_players)
		{
			
			
			
			if(IsPlayerInAnyVehicle(ply))
			{
				OnPlayerSpawn(ply);
				Iter_SafeRemove(o_s_players, ply, next);
				ply = next;
				
				continue;
				
			}
			if(pInfo[ply][player_afk] > 3)
			{
				OnPlayerSpawn(ply);
				Iter_SafeRemove(o_s_players, ply, next);
				ply = next;
				
				continue;
				
			}
			
			
			
		}
	}
	return 1;
} 
CMD:hyexit(playerid, params[])
{
	if(removeIsEvent(playerid) == 0)
		return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Nie jesteœ zapisany(a) na ¿aden event.");
 	SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} ›››{/b}  Wypisa³eœ(aœ) siê z Hay.");
	return 1;
}

CMD:hy(playerid, params[])
{
 	if(Iter_Contains(h_y_players, playerid))
 		return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Jesteœ ju¿ zapisany(a) na Hay.");
	if(Iter_Count(h_y_players) >= h_y_start_players_max) 
		return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Na Hay zapisa³o siê zbyt du¿o osób, spróbuj w nastêpnej kolejce."); 
	//if(removeIsEvent(playerid) == 1) SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} ›››{/b}  By³eœ(aœ), zapisany(a), na inny event zosta³eœ(aœ) z niego wypisany(a).");
 	
	if(pInfo[playerid][player_objected])
		return InfoBox(playerid, "Nie mozesz zapisac sie na event poniewaz masz wylaczone obiekty");
	
	removeIsEvent(playerid);

	Iter_Add(h_y_players, playerid);
	if(Iter_Count(h_y_players) == h_y_start_players && script_hy[statees] == false  && script_hy[started] == false)
	{
   		SetTimer("script_hy_Go", 20000, 0);
   		SendClientMessageToAll(-1, "›››{008ae6} Hay {/b}wystartuje za {008ae6}20 sekund {/b}Zapisy nadal trwaj¹ {008ae6}(/HY)");
		TextDrawUpdateEventStart("Hay", "/HY");
 		script_hy[started] = true;
	}
 	SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} ›››{/b}  Zapisa³eœ(aœ) siê na Hay.");
 	return 1;
}

new randtimer, normtimer;

Public:script_hy_Go()
{
	script_hy[started] = false;
	if(Iter_Count(h_y_players) <= 1)
	{
		Iter_Clear(h_y_players);
	    script_hy[statees] = false;
		SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Hay nie wystartowa³y z powodu braku graczy.");
	    return 1;
	}
	hay_object();
	script_hy[winreed] = INVALID_PLAYER_ID;
	 
	SendClientMessageToAll(-1, "{FFFFFF} ›››{/b} {008ae6}Hay{/b} wystartowa³o!");
	script_hy[statees] = true;
	new Float:script_object_possek[3];
  	foreach (new p : h_y_players)
   	{
   	    if(!IsPlayerConnected(p)) continue;
		SetPlayerArmour(p, 60.0);
 		GetDynamicObjectPos(script_hy[hay][random(25) + 2], script_object_possek[0], script_object_possek[1], script_object_possek[2]);
		
		FreezePlayerTime(p, 3);
        ResetPlayerWeapons(p);
		SetPlayerVirtualWorld(p, 123);
        SetPlayerPos(p, script_object_possek[0], script_object_possek[1], script_object_possek[2] + 4);
        SetPlayerFacingAngle(p, 180.0);
		SetPlayerHealth(p, 100.0);
 		SetCameraBehindPlayer(p);
		 
	}
 	 
 	SetTimer("script_hy_rlg", 1000, 0);
	randtimer = SetTimer("script_hy_rando",5000,1);
	return 1;
}

forward script_hy_rlg();
public script_hy_rlg()
{
	if(script_hy[statees] != true) return 1;


	foreach (new i : h_y_players)
   	{
   	    if(!IsPlayerConnected(i)) continue;
    		
		ResetPlayerWeapons(i);
	}
	SetTimer("script_hy_weapon", 1000*hy_sek_weapon, 0);
 	return 1;
}


forward script_hy_normalize();

public script_hy_normalize()
{
	for(new x = 0; x < 41; x++)
	{
		new Float:hx, Float:hy, Float:hz;
		GetDynamicObjectPos(script_hy[hay][x], hx, hy, hz); 
		MoveDynamicObject(script_hy[hay][x], hx+0.002, hy+0.002, hz, 0.003, 0, 0, 0 );
	}
	randtimer = SetTimer("script_hy_rando",5000,1);
	return 1;
}


forward script_hy_rando();
public script_hy_rando()
{
	for(new x = 0; x < 41; x++)
	{
		new rx = random(35)+15; 
		new ry = random(55)+15; 
			//new rx = 30, ry = 140;
		new Float:hx, Float:hy, Float:hz;
		GetDynamicObjectPos(script_hy[hay][x], hx, hy, hz); 
		MoveDynamicObject(script_hy[hay][x], hx+0.002, hy+0.002, hz, 0.005, rx, ry, 0 );
	}
	return 1;
}
forward script_hy_weapon();
public script_hy_weapon()
{

	if(script_hy[statees] != true) return;
	foreach (new x : h_y_players) { ResetPlayerWeapons(x); }
	GivePlayerWeapon(Iter_Random(h_y_players), 24, 1);	
	
	DestroyDynamicObject(script_hy[hay][random(41)]);
	DestroyDynamicObject(script_hy[hay][random(41)]);
	SetTimer("script_hy_weapon", 1000*hy_sek_weapon, 0);

}

forward script_hy_update();
public script_hy_update()
{
	if(script_hy[statees] != true) return 1;
	
	if(Iter_Count(h_y_players) == 0)
	{
		script_destory_hy_v();
 		Iter_Clear(h_y_players);
		script_hy[statees] = false;
		SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Hay zosta³o zakoñczone z powodu braku graczy.");
		KillTimer(randtimer);
		KillTimer(normtimer);
		return 1;
	}
 	
	if(Iter_Count(h_y_players) == 1) //tutaaj jesli jest jeden
	{
		 
 		new p = Iter_First(h_y_players);
		if(IsPlayerConnected(p))
		{
			 
			 
			SetPlayerVirtualWorld(p, 0);
			TogglePlayerControllable(p, 1);
			SetPlayerHealth(p, 100.0);
			ResetPlayerWeapons(p);
			
			#if defined ADUIO_PLUGIN
			PlayCompleteMissionSound(p);
			#endif
			OnPlayerSpawn(p);
			 
			new kasy = random(10000), score = random(300);
 			GivePlayerScore(p, score);
			GivePlayerMoney(p, kasy);
			SendClientMessageToAll(-1, " {008ae6}%s (%d) {/b}po raz {008ae6}%d{/b} wygra³ {008ae6}/HY{/b}. I otrzymuje {008ae6}%d Score i %d${/b} ", pInfo[p][player_name], p, addPointEvent(p, stats_hy), score, kasy);
			Iter_Remove(h_y_players, p);
		}
		script_destory_hy_v();
		Iter_Clear(h_y_players);
		script_hy[statees] = false;
		KillTimer(randtimer);
		KillTimer(normtimer);
		return 1;
	}
	
	if(script_hy[winreed] != INVALID_PLAYER_ID)
	{
		
 		GivePlayerMoney(script_hy[winreed], 10000);
		
		new kasy = random(10000), score = random(300);
 	
    	GivePlayerScore(script_hy[winreed] , score);
		GivePlayerMoney(script_hy[winreed] , kasy);
			
		#if defined ADUIO_PLUGIN
		PlayCompleteMissionSound(script_hy[winreed]);
		#endif
		SendClientMessageToAll(-1, " {008ae6}%s (%d){/b} po raz {008ae6}%d{/b} wygra³ {008ae6}/HY{/b}. I otrzymuje {008ae6}%d Score i %d${/b} ", pInfo[script_hy[winreed]][player_name], script_hy[winreed], addPointEvent(script_hy[winreed], stats_hy), score, kasy);
		script_destory_hy_v();
		script_hy[statees] = false;
		KillTimer(randtimer);
		KillTimer(normtimer);
		foreach (new ply : h_y_players){
			OnPlayerSpawn(ply);
		}
		Iter_Clear(h_y_players);
		return 1;
	}
	new next;
	if(Iter_Count(h_y_players) > 0){
		new Float:position_[6];
		foreach (new ply : h_y_players)
		{
			
			GetPlayerPos(ply, position_[0], position_[1], position_[2]);
			if(position_[2] < 110.0){
				OnPlayerSpawn(ply);
			
				Iter_SafeRemove(h_y_players, ply, next);
				ply = next;
				
				continue;
			}
			
			if(IsPlayerInAnyVehicle(ply))
			{
				OnPlayerSpawn(ply);
				Iter_SafeRemove(h_y_players, ply, next);
				ply = next;
				
				continue;
				
			} 
			if(pInfo[ply][player_afk] > 3)
			{
				OnPlayerSpawn(ply);
				Iter_SafeRemove(h_y_players, ply, next);
				ply = next;
				
				continue;
				
			} 
		}
	}
 	return 1;
}
Public:script_destory_hy_v()
{
	for(new x = 0; x < 41; x++)
	{
		DestroyDynamicObject(script_hy[hay][x]);
		
	}

}
forward hay_object();
public hay_object(){
	
	script_hy[hay][0] = CreateDynamicObject(3374, 1749.74792, -8.52000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][1] = CreateDynamicObject(3374, 1753.74792, -8.52000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][2] = CreateDynamicObject(3374, 1757.74792, -8.52000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][3] = CreateDynamicObject(3374, 1761.74792, -8.52000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][4] = CreateDynamicObject(3374, 1765.74792, -8.52000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][5] = CreateDynamicObject(3374, 1769.74792, -8.52000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][6] = CreateDynamicObject(3374, 1749.74792, -4.52000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][7] = CreateDynamicObject(3374, 1753.74792, -4.52000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][8] = CreateDynamicObject(3374, 1757.74792, -4.52000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][9] = CreateDynamicObject(3374, 1765.74792, -4.52000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][10] = CreateDynamicObject(3374, 1769.74792, -4.52000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][11] = CreateDynamicObject(3374, 1749.74792, -0.52000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][12] = CreateDynamicObject(3374, 1753.74792, -0.52000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][13] = CreateDynamicObject(3374, 1757.74792, -0.52000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][14] = CreateDynamicObject(3374, 1761.74792, -0.52000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][15] = CreateDynamicObject(3374, 1765.74792, -0.52000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][16] = CreateDynamicObject(3374, 1769.74792, -0.52000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][17] = CreateDynamicObject(3374, 1749.74792, 3.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][18] = CreateDynamicObject(3374, 1753.74792, 3.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][19] = CreateDynamicObject(3374, 1757.74792, 3.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][20] = CreateDynamicObject(3374, 1761.74792, 3.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][21] = CreateDynamicObject(3374, 1765.74792, 3.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][22] = CreateDynamicObject(3374, 1769.74792, 3.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][23] = CreateDynamicObject(3374, 1749.74792, 7.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][24] = CreateDynamicObject(3374, 1753.74792, 7.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][25] = CreateDynamicObject(3374, 1757.74792, 7.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][26] = CreateDynamicObject(3374, 1761.74792, 7.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][27] = CreateDynamicObject(3374, 1765.74792, 7.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][28] = CreateDynamicObject(3374, 1769.74792, 7.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][29] = CreateDynamicObject(3374, 1749.74792, 11.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][30] = CreateDynamicObject(3374, 1753.74792, 11.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][31] = CreateDynamicObject(3374, 1757.74792, 11.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][32] = CreateDynamicObject(3374, 1761.74792, 11.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][33] = CreateDynamicObject(3374, 1765.74792, 11.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][34] = CreateDynamicObject(3374, 1769.74792, 11.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][35] = CreateDynamicObject(3374, 1749.74792, 15.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][36] = CreateDynamicObject(3374, 1753.74792, 15.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][37] = CreateDynamicObject(3374, 1757.74792, 15.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][38] = CreateDynamicObject(3374, 1761.74792, 15.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][39] = CreateDynamicObject(3374, 1765.74792, 15.48000, 120.03070,   0.00000, 0.00000, 0.00000);
	script_hy[hay][40] = CreateDynamicObject(3374, 1769.74792, 15.48000, 120.03070,   0.00000, 0.00000, 0.00000);


}


//#define _defence 2
#define d_f_start_players 6
#define d_f_start_players_max 50 

#define df_atakujacy 0
#define df_obroncy 1
enum d_f_event 
{
	winreed, 
	defence[101], 
	df_team[MAX_PLAYERS],
	df_lastteam,
	bool:statees, 
	bool:started, 
	df_Pickup,
	Timer, 
	 
}
new script_DF[d_f_event];
 
 

 
 
CMD:dfexit(playerid, params[])
{
	if(removeIsEvent(playerid) == 0)return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Nie jesteœ zapisany(a) na ¿aden event.");
 	SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} ›››{/b}  Wypisa³eœ(aœ) siê z Defence.");
	ResetPlayerWeapons(playerid);
	return 1;
}

CMD:df(playerid, params[])
{
	return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Komenda zablokowana");
 	/*if(Iter_Contains(d_f_players, playerid))return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Jesteœ ju¿ zapisany(a) na Defence.");
	if(Iter_Count(d_f_players) >= d_f_start_players_max) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Na Defence zapisa³o siê zbyt du¿o osób, spróbuj w nastêpnej kolejce."); 
	//if(removeIsEvent(playerid) == 1) SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} ›››{/b}  By³eœ(aœ), zapisany(a), na inny event zosta³eœ(aœ) z niego wypisany(a).");
	if(pInfo[playerid][player_objected])
		return InfoBox(playerid, "Nie mozesz zapisac sie na event poniewaz masz wylaczone obiekty");
	
	removeIsEvent(playerid);

	Iter_Add(d_f_players, playerid);
	if(Iter_Count(d_f_players) == d_f_start_players && script_DF[statees] == false  && script_DF[started] == false)
	{
   		SetTimer("script_DF_Go", 20000, 0);
   		SendClientMessageToAll(COLOR_EVENT_STARTED, "››› Defence wystartuje za {b}20 sekund {/b}Zapisy nadal trwaj¹ (/DF)");
 		script_DF[started] = true;
		TextDrawUpdateEventStart("Defence", "/DF");
	}
 	SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} ›››{/b}  Zapisa³eœ(aœ) siê na Defence.");
 	return 1;*/
}

forward script_DF_Go();
public script_DF_Go()
{
	script_DF[started] = false;
	if(Iter_Count(d_f_players) <= 1)
	{
		
		
		Iter_Clear(d_f_players);
		script_DF[statees] = false;
		SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Defence nie wystartowa³y z powodu braku graczy.");
		return 1;
	}
	script_DF[winreed] = INVALID_PLAYER_ID;
	
	SendClientMessageToAll(COLOR_INFO, "{FFFFFF} ›››{/b} Defence wystartowa³o!");
 	foreach (new p : d_f_players)
	{
		if(!IsPlayerConnected(p)) continue;
		
		ResetPlayerWeapons(p);
		#define i p
		if(script_DF[df_lastteam])
		{
			script_DF[df_team][p] = df_obroncy;
			script_DF[df_lastteam] = 0;
			
			ShowPlayerDialog(i, 9999, DIALOG_STYLE_MSGBOX,"Dru¿yna broni¹ca.","Jesteœ w dru¿ynie obroñców wyspy! Zajmij dogodne miejsce do ostrza³u nadlatuj¹cych agresorów i zestrzel jak najwiêcej z nich!\nPamiêtaj ¿e jeœli przejm¹ checkpoint w czasie 3 minut wygraj¹. \nPowodzenia!", "Ok", "Kontynuuj");
			SetPlayerColor(i, COLOR_BLUE);
			SetPlayerSkin(i, 125);
			
			SetPlayerTeam(i, 1212);
			 
 		}
		else
		{
			script_DF[df_team][p] = df_atakujacy;
			script_DF[df_lastteam] = 1;
			
			ShowPlayerDialog(i, 9999, DIALOG_STYLE_MSGBOX,"Dru¿yna atakuj¹ca.","Jesteœ w dru¿ynie atakuj¹cej! Wpisz /dfrustler lub /dfsparrow, by wsi¹œæ do samolotu lub œmig³owca. \nLeæ nastêpnie na wyspê (czerwony punkt na radarze) i zabij jak najwiêcej obroñców! Je¿eli zd¹¿ycie zdobyæ czerwony punkt (checkpoint) w ci¹gu minuty wygracie. \nPowodzenia!", "Ok", "Kontynuuj");
			
			SendClientMessage(i, COLOR_INFO2, ""chat" Wpisz {b}/dfrustler{/b} lub {b}/dfsparrow{/b}, by wsi¹œæ do samolotu lub œmig³owca.");
			SetPlayerCheckpoint(i, -3101.5735,1681.6493,50.9155,4);
			SetPlayerColor(i, COLOR_GREEN);
			SetPlayerSkin(i, 165);
			
			SetPlayerTeam(i, 1213);
		 
		}
		OnPlayerSpawnToDF(i,true);
		OnPlayerSpawnToDF(i,true);
		#undef i
		FreezePlayerTime(p, 2);
		
	} 
	script_DF[statees] = true;
	SetTimer("script_DF_rlg", 1000, 0);
	return 1;
}

stock OnPlayerSpawnToDF(i, bool:isstart = false)
{
	if(script_DF[Timer] < 1 && isstart == false) return 1;
	ResetPlayerWeapons(i);
	if(script_DF[df_team][i] == df_atakujacy)
	{
		if(random(2) == 1) 
			SetPlayerPos(i, -3551.7351,1313.2231,17.6246);
		else 
			SetPlayerPos(i, -3378.4170,1295.4888,17.6141);
			
		DisablePlayerCheckpoint(i);
		SetPlayerCheckpoint(i, -3101.5735,1681.6493,50.9155,4);
		
		GivePlayerWeapon(i, 16, 500);
		GivePlayerWeapon(i, 31, 500);
		GivePlayerWeapon(i, 24, 500);
	}
	else 
	{
		new cr = random(4);
		if(cr == 1) 
			SetPlayerPos(i,-3119.9084,1684.3373,52.8230);
		else if(cr == 2) 
			SetPlayerPos(i,-3132.3218,1705.8818,70.4529);
		else if(cr== 3) 
			SetPlayerPos(i,-3095.0986,1762.9695,76.8844);
		else 
			SetPlayerPos(i,-3109.8167,1711.0704,39.8355);
			
		GivePlayerWeapon(i, 35, 500);
		GivePlayerWeapon(i, 31, 500);
		GivePlayerWeapon(i, 24, 500);
	}
	FreezePlayerTime(i,2);
	SetPlayerVirtualWorld(i, 123);
	SetPlayerFacingAngle(i, 180.0);
	SetPlayerHealth(i, 100.0);
	
	return 1;
}
 
forward script_DF_rlg();
public script_DF_rlg()
{
	if(script_DF[statees] != true) return 1;

 
	script_DF[Timer] = 183;
	
 	return 1;
}
CMD:dfrustler(playerid, params[])
{
	if(script_DF[df_team][playerid] != df_atakujacy)return 0;
	
	SetVehicleVirtualWorld(CreatePlayerVehicle(playerid, 476), GetPlayerVirtualWorld(playerid));
	return 1;
}

CMD:dfsparrow(playerid, params[])
{
	if(script_DF[df_team][playerid] != df_atakujacy)return 0;
	
	SetVehicleVirtualWorld(CreatePlayerVehicle(playerid, 447), GetPlayerVirtualWorld(playerid));
	return 1;
}

forward script_DF_update();
public script_DF_update()
{
	if(script_DF[statees] != true) return 1;
	
	if(Iter_Count(d_f_players) == 0)
	{
  		Iter_Clear(d_f_players);
		script_DF[statees] = false;
		SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Defence zosta³o zakoñczone z powodu braku graczy.");
		return 1;
	}
 	

	if(script_DF[Timer]-- < 0)
	{
		foreach(new p : d_f_players)
		{
			if(script_DF[df_team][p] == df_obroncy)
			{
				script_DF[winreed] = p;
				break;
			}
		}
	}
	if(script_DF[winreed] != INVALID_PLAYER_ID)
	{
		new kasy = random(10000), score = random(300);
		
		new teamwin = script_DF[df_team][script_DF[winreed]];
		foreach(new p : d_f_players)
		{
			if(script_DF[df_team][p] == teamwin)
			{
				GivePlayerScore(p , score);
				GivePlayerMoney(p , kasy);
				#if defined ADUIO_PLUGIN
				PlayCompleteMissionSound(p);
				#endif
				addPointEvent(p, stats_df);
			}
			
			OnPlayerSpawn(p);
		}
    	  
 		script_DF[statees] = false;
		if(teamwin == df_obroncy)
			SendClientMessageToAll(COLOR_GREEN, ""chat" Defence wygra³a dru¿yna obroñców. Zapisany na nastêpn¹ kolejkê rozpoczête.");
		else 
			SendClientMessageToAll(COLOR_BLUE, ""chat" Defence wygra³a dru¿yna atakuj¹cych. Zapisany na nastêpn¹ kolejkê rozpoczête.");
		 
		Iter_Clear(d_f_players);
		return 1;
	}
	
	new str[64];
	format(str, sizeof(str), "Czas na zdobycie czerwonego punktu %d sekund!", script_DF[Timer]);
	
	foreach(new p : d_f_players)
	{
		PlayerEventTDSet(p, str, "Deffence");
		if(IsPlayerInRangeOfPoint(p, 3.5, -3101.5735,1681.6493,50.9155) && script_DF[df_team][p] == df_atakujacy)
		{
			script_DF[winreed] = p;
		}
	}
	/*
	new next;
	if(Iter_Count(d_f_players) > 0){
		new Float:position_[6];
		foreach (new ply : d_f_players)
		{
			
			GetPlayerPos(ply, position_[0], position_[1], position_[2]);
			if(position_[2] < 110.0){
				OnPlayerSpawn(ply);
			
				Iter_SafeRemove(d_f_players, ply, next);
				ply = next;
			}
			
			if(IsPlayerInAnyVehicle(ply))
			{
				OnPlayerSpawn(ply);
				Iter_SafeRemove(d_f_players, ply, next);
				ply = next;
				
			}
			
		}
	}*/
 	return 1;
}

#define _zbb 2
#define z_b_start_players 3
#define z_b_start_players_max 50 

#define zb_sek_weapon 7 //co ile sekund ma dawaæ broñ //domyœlnie 10 sekund
enum z_b_event 
{
	winreed, 
	zbb[101], 
	bool:statees, 
	bool:started, 
	Timer, 
	b_object,
	b_time,
	bot_id
	 
};
new script_zb[z_b_event];
new Iterator:z_b_players<MAX_PLAYERS+2>;

CMD:zbexit(playerid, params[])
{
	if(removeIsEvent(playerid) == 0)
		return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Nie jesteœ zapisany(a) na ¿aden event.");
 	SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} ›››{/b}  Wypisa³eœ(aœ) siê z Zabij bossa.");
	return 1;
}

CMD:zb(playerid, params[])
{
 	if(Iter_Contains(z_b_players, playerid))
 		return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Jesteœ ju¿ zapisany(a) na Zabij bossa.");
	if(Iter_Count(z_b_players) >= z_b_start_players_max) 
		return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Na Zabij bossa zapisa³o siê zbyt du¿o osób, spróbuj w nastêpnej kolejce."); 
	//if(removeIsEvent(playerid) == 1) SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} ›››{/b}  By³eœ(aœ), zapisany(a), na inny event zosta³eœ(aœ) z niego wypisany(a).");
	if(script_zb[statees] == true) 
		return SendClientMessage(playerid, COLOR_ERROR, "Os aktualnie trwa");
 	removeIsEvent(playerid);

	Iter_Add(z_b_players, playerid);
	if(Iter_Count(z_b_players) == z_b_start_players && script_zb[statees] == false  && script_zb[started] == false)
	{
   		SetTimer("script_zb_Go", 20000, 0);
   		SendClientMessageToAll(-1, "›››{008ae6} Zabij bossa{/b} wystartuje za {008ae6}20 sekund {/b}Zapisy nadal trwaj¹ {008ae6}(/zb)");
 		script_zb[started] = true;
		TextDrawUpdateEventStart("Zabij bossa", "/ZB");
	}
 	SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} ›››{/b}  Zapisa³eœ(aœ) siê na Zabij bossa.");
 	return 1;
}
Public:script_zb_Go()
{
	script_zb[started] = false;
	if(Iter_Count(z_b_players) <= 1)
	{
		Iter_Clear(z_b_players);
	    script_zb[statees] = false;
		SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Zabij bossa nie wystartowa³o z powodu braku graczy.");
	    return 1;
	}
	script_zb[winreed] = INVALID_PLAYER_ID;
	SendClientMessageToAll(-1, "{FFFFFF} ›››{/b} {008ae6}Zabij bossa{/b} wystartowa³o!");
   	foreach (new p : z_b_players)
   	{
   	    if(!IsPlayerConnected(p)) continue;
		SetPlayerArmour(p, 0.0);
 		SetPlayerHealth(p, 100.0);
		
		SetPlayerPos(p,-969.4065,1033.1636,1345.0685);
		SetPlayerInterior(p, 10);
		SetPlayerVirtualWorld(p, 666);
        SetPlayerFacingAngle(p, 180.0);
		
		SetPlayerTeam(p, MAX_PLAYERS + 50);
		
		FreezePlayerTime(p, 3);
 		SetCameraBehindPlayer(p);
		InfoBox(p, "Pamiêtaj! BOSS ma 500.0 HP oraz 200.0 Armor ka¿dy cz³onek zabawy ma za zadanie go zabiæ\n\nJest nad nim obiekt!");
		 
	}
	script_zb[bot_id] = Iter_Random(z_b_players);
 	script_zb[statees] = true;
	script_zb[b_time] = 120;
	AttachObjectToPlayer(script_zb[b_object], script_zb[bot_id], 0.0, 0.0, 2.65, 0.0, 0.0, 0.0);
	SetPlayerTeam(script_zb[bot_id], MAX_PLAYERS + 80 + random(30));
		
	 
 	SetTimer("script_zb_rlg", 1000, 0);
	return 1;
}
Public:script_zb_rlg()
{
	if(script_zb[statees] != true) return 1;
	foreach (new i : z_b_players)
   	{
   	    if(!IsPlayerConnected(i)) continue;
    		
		ResetPlayerWeapons(i);
		
		GivePlayerWeapon(i, 4, 5000);
		GivePlayerWeapon(i, 24, 1000);
		GivePlayerWeapon(i, 25, 100);
		GivePlayerWeapon(i, 34, 5000);
		GivePlayerWeapon(i, 30, 5000);
		GivePlayerWeapon(i, 28, 5000);
		
	}
	SetPlayerHealth(script_zb[bot_id], 500.0);
	SetPlayerArmour(script_zb[bot_id], 200.0);
	
	AttachObjectToPlayer(script_zb[b_object], script_zb[bot_id], 0.0, 0.0, 2.65, 0.0, 0.0, 0.0);
 	return 1;
}


forward script_zb_update();
public script_zb_update()
{
	if(script_zb[statees] != true) return 1;
	
	if(Iter_Count(z_b_players) == 0)
	{
  		Iter_Clear(z_b_players);
		script_zb[statees] = false;
		SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Zabij bossa zosta³o zakoñczone z powodu braku graczy.");
		return 1;
	}
 	
	if(Iter_Count(z_b_players) == 1) //tutaaj jesli jest jeden
	{
		script_zb[winreed] = Iter_First(z_b_players);
	}
	
 
	if(--script_zb[b_time] < 0)
	{
		script_zb[winreed] = script_zb[bot_id];
	}
	
	if(script_zb[winreed] != INVALID_PLAYER_ID)
	{
	
		AttachObjectToObject(script_zb[b_object], 20, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 1);
		if(script_zb[winreed] == 501 || script_zb[winreed] != script_zb[bot_id])
		{
			foreach (new ply : z_b_players)
			{
				OnPlayerSpawn(ply);
				
				new kasy = random(10000), score = random(300);
 	
				GivePlayerScore(ply , score, "wygranie /ZB");
				GivePlayerMoney(ply , kasy);
				addPointEvent(ply, stats_zb);
				
				
			}
			SendClientMessageToAll(-1, ""chat" {008ae6}Zabij bossa {/b}wygrywaj¹ atakuj¹cy...");
		}
		else 
		{
			OnPlayerSpawn(script_zb[winreed]);
			
			new kasy = random(10000), score = random(300);
 	
			GivePlayerScore(script_zb[winreed] , score, "wygranie /ZB");
			GivePlayerMoney(script_zb[winreed] , kasy);
			addPointEvent(script_zb[winreed], stats_zb);
				
			SendClientMessageToAll(-1, ""chat" {008ae6}Zabij bossa {/b}wygrywa BOSS...");
		}
		 
 		script_zb[statees] = false;
		Iter_Clear(z_b_players);
		return 1;
	}
	new next;
	if(Iter_Count(z_b_players) > 0)
	{
		foreach (new ply : z_b_players)
		{
			
	
			if(IsPlayerInAnyVehicle(ply))
			{
				OnPlayerSpawn(ply);
				Iter_SafeRemove(z_b_players, ply, next);
				ply = next;

				continue;
				
			}
			if(pInfo[ply][player_afk] > 5)
			{
				OnPlayerSpawn(ply);
				Iter_SafeRemove(z_b_players, ply, next);
				ply = next;

				continue;
				
			}
		}
	}
 	return 1;
}

//********************************************************************
//********************** Test Reakcji *******************************

stock ClearWinTR()
{
	for(new i;i<MAX_PLAYERS;i++) script_tr[iswin][i] = false;
}

stock ShowStatsTR()
{
	 
	
	new rundastring2[512] = "Wyniki rundy: \n";
	new kasy = random(10000), score = random(150);
		
	foreach (new i : t_r_players) 
	{
		if(script_tr[iswin][i])
		{
			format(rundastring2, sizeof(rundastring2), "%s%s (%d)\n", rundastring2, playerNick(i), i);
			 
			GivePlayerScore(i , score, "wygranie /tr");
			GivePlayerMoney(i , kasy);
			addPointEvent(i, stats_tr);
			achievement(i, 18); 
		}
	}
	foreach (new i : t_r_players) 
	{
		InfoBox(i, rundastring2);
		SpawnToTR(i);
	}
	ClearWinTR();
	script_tr[t_zadanieid]++;
}
stock SetTaskTR()
{
	foreach (new i : t_r_players) PlayerEventTDSet(i, "WYBIERANIE TESTU", "Test Reakcji"); 
	
	switch(random(5) + 1)
	{
		case 1:
		{
			script_tr[t_zadanie] = 1;
			
			new result[2];
			
			result[0] = random(150) + random(15) +1;
			result[1] = random(350) + 20;
					
			format(script_tr[t_result], 20, "%d", (result[0] + result[1]));
			
			 
			format(string2, sizeof(string2), "Oblicz!:~n~%d + %d = ?", result[0], result[1]);
			//printf(string2);
			foreach (new i : t_r_players) 
			{
				PlayerEventTDSet(i, string2, "Test Reakcji ~r~Oblicz"); 
				//SendClientMessage(i, -1, "%s, %s", script_tr[t_result], string2);
			}
			
			SetProgressBarValue(script_tr[tr_bar], 50.0);
		}
		case 2:
		{
			script_tr[t_zadanie] = 2;
	
			 
			foreach (new i : t_r_players) 
			{
				SetPlayerInterior(i, 0);
				CreatePlayerVehicle(i, 541, 179.2071);
				SetPlayerVirtualWorld(i, t_r_vw + i);
				SetVehicleVirtualWorld(pInfo[i][player_vehicle], t_r_vw + i);
				
				SetVehiclePos(pInfo[i][player_vehicle], -1900.1260,-282.7086,37.8673);
 				
				SetPlayerPos(i, -1900.1260, -282.7086, 41.8673);
				PutPlayerInVehicle(i, pInfo[i][player_vehicle], 0);
				
				SetVehicleSpeed(pInfo[i][player_vehicle], 310.0);
				PlayerEventTDSet(i, "Zatrzymaj pojazd!", "Test Reakcji"); 
			}
			
			SetProgressBarValue(script_tr[tr_bar], 39.0);
		}
		case 3:
		{
			script_tr[t_zadanie] = 3;
	
			 
			foreach (new i : t_r_players) 
			{
				SetPlayerInterior(i, 0);
				CreatePlayerVehicle(i, 443, 293.2071);
				SetPlayerVirtualWorld(i, t_r_vw + i);
				SetVehicleVirtualWorld(pInfo[i][player_vehicle], t_r_vw + i);
				
				SetVehiclePos(pInfo[i][player_vehicle], -1745.4596,-1674.2181,36.6791);
 				
				SetPlayerPos(i, -1900.1260, -282.7086, 41.8673);
				PutPlayerInVehicle(i, pInfo[i][player_vehicle], 0);
				
				SetVehicleSpeed(pInfo[i][player_vehicle], 10.0);
				PlayerEventTDSet(i, "Dojedz do czerwonego punktu!", "Test Reakcji"); 
				
				SetPlayerRaceCheckpoint(i, 1, -1594.6853,-1610.6554,36.8931, 0.0, 0.0, 0.0, 10.0);
			}
			
			SetProgressBarValue(script_tr[tr_bar], 45.0);
		}
		case 4:
		{
			script_tr[t_zadanie] = 4;
	
			 
			foreach (new i : t_r_players) 
			{
				SetPlayerInterior(i, 0);
				CreatePlayerVehicle(i, 562, 354.2071);
				SetPlayerVirtualWorld(i, t_r_vw + i);
				SetVehicleVirtualWorld(pInfo[i][player_vehicle], t_r_vw + i);
				
				SetVehiclePos(pInfo[i][player_vehicle], -1745.4596,-1674.2181,36.6791);
 				
				SetPlayerPos(i, 2314.4153,1442.7601,42.4783);
				PutPlayerInVehicle(i, pInfo[i][player_vehicle], 0);
				
				SetVehicleSpeed(pInfo[i][player_vehicle], 10.0);
				PlayerEventTDSet(i, "Zadriftuj..."); 
				pInfo[i][player_driftcouter] = true;
				
			}
			
			SetProgressBarValue(script_tr[tr_bar], 90.0);
		}
		case 5..6:
		{
			script_tr[t_zadanie] = 5;
	
			 
			foreach (new i : t_r_players) 
			{
				SetPlayerInterior(i, 0);
				SetPlayerVirtualWorld(i, t_r_vw);
				
			
				SetPlayerPos(i, 1218.5726,556.2960,18.9747);
				
				PlayerEventTDSet(i, "Przeplyn do czerwonego punktu!", "Test Reakcji"); 
				
				SetPlayerRaceCheckpoint(i, 1, 1247.1793,663.7476,5.7348, 0.0, 0.0, 0.0, 10.0);
			}
			
			SetProgressBarValue(script_tr[tr_bar], 2500.0);
		}
	}
}
 

  

 
CMD:trexit(playerid, params[])
{
	if(removeIsEvent(playerid) == 0)return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Nie jesteœ zapisany(a) na ¿aden event.");
 	SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} ›››{/b}  Wypisa³eœ(aœ) siê z Test reakcji.");
	return 1;
}

CMD:tr(playerid, params[])
{
 	if(Iter_Contains(t_r_players, playerid))return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Jesteœ ju¿ zapisany(a) na Test reakcji.");
	if(Iter_Count(t_r_players) >= t_r_start_players_max) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Na Test reakcji zapisa³o siê tryt du¿o osób, spróbuj w nastêpnej kolejce."); 
	//if(removeIsEvent(playerid) == 1) SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} ›››{/b}  By³eœ(aœ), zapisany(a), na inny event zosta³eœ(aœ) z niego wypisany(a).");
 	removeIsEvent(playerid);

	Iter_Add(t_r_players, playerid);
	if(Iter_Count(t_r_players) == t_r_start_players && script_tr[statees] == false  && script_tr[started] == false)
	{
   		SetTimer("script_tr_Go", 20000, 0);
   		SendClientMessageToAll(-1, "››› {008ae6}Test reakcji{/b}wystartuje za {008ae6}20 sekund {/b}Zapisy nadal trwaj¹ {008ae6}(/tr)");
 		script_tr[started] = true;
		TextDrawUpdateEventStart("Test Reakcji", "/TR");
	}
	UpdateEvStat();
	SendClientMessage(playerid, -1, "{FFFFFF} ›››{/b}  {008ae6}Zapisa³eœ(aœ) siê na Test reakcji.");
 	return 1;
}

stock SpawnToTR(p)
{
	FreezePlayerTime(p, 3);
	
	SetPlayerArmour(p, 1000.0);
	SetPlayerHealth(p, 1000.0);
	
	SetPlayerPos(p,2861.2927,623.7225,806.4923);
	SetPlayerInterior(p, 10);
	SetPlayerVirtualWorld(p, t_r_vw);
	SetPlayerFacingAngle(p, 180.0);
	
	DisablePlayerRaceCheckpoint(p);
	SetCameraBehindPlayer(p);
	
}
forward script_tr_Go();
public script_tr_Go()
{
	script_tr[started] = false;
	script_tr[t_zadanieid] = 0;
	if(Iter_Count(t_r_players) < t_r_start_players)
	{
	 
		Iter_Clear(t_r_players);
	    script_tr[statees] = false;
		SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Test reakcji nie wystartowa³ z powodu braku graczy.");
	    return 1;
	}
	script_tr[winreed] = INVALID_PLAYER_ID;
	 
	SendClientMessageToAll(-1, "{FFFFFF} ›››{/b} {008ae6}Test reakcji {/b}wystartowa³!");
   	foreach (new p : t_r_players)
   	{
   	    if(!IsPlayerConnected(p)) continue;
		SpawnToTR(p);
	 
	}
	ClearWinTR();
	 
 	SetTimer("script_tr_rlg", 1000, 0);
	return 1;
}

forward script_tr_rlg();
public script_tr_rlg()
{
	script_tr[statees] = true;
	foreach (new i : t_r_players)
   	{
   	    if(!IsPlayerConnected(i)) continue;
   		
		ResetPlayerWeapons(i);
		
	}
	script_tr[b_time] = 5;
 	return 1;
}


forward script_tr_update();
public script_tr_update()
{
	if(script_tr[statees] != true) return 1;
	
	if(Iter_Count(t_r_players) == 0)
	{
  		Iter_Clear(t_r_players);
		script_tr[statees] = false;
		SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Test reakcji zosta³ zakoñczony z powodu braku graczy.");
		return 1;
	}
	UpdateEvStat();
	
	if(Iter_Count(t_r_players) == 1) //tutaaj jesli jest jeden
	{
	//	script_tr[winreed] = Iter_First(t_r_players);
	}
	
	
	if(script_tr[t_zadanieid] >= 3)
	{
	
		foreach(new i : t_r_players)
		{
			SetPlayerVirtualWorld(i, 0);
			OnPlayerSpawn(i);
		}
		SendClientMessageToAll(COLOR_GOLD, "{FF0000} ›››{/b} Test reakcji zosta³ zakoñczony. Zapisy wznowione.");
		script_tr[statees] = false;
		Iter_Clear(t_r_players);
		return 1;
	}
	if(script_tr[b_time]-- > 0 && !script_tr[t_zadanie])
	{
		format(string2, sizeof(string2), "~n~~g~~h~Zadanie ~h~za~w~ %d s", script_tr[b_time]);
		
		foreach (new i : t_r_players)
		{
			PlayerEventTDSet(i, string2, "Test Reakcji");
		}
	}
	else if(!script_tr[t_zadanie])
	{
		foreach (new i : t_r_players)
		{
			PlayerEventTDSet(i, "Wait~r~.~h~.~h~.", "Test Reakcji");
		}
		SetTaskTR();
	}
	
 
 /*
	new next;
	if(Iter_Count(t_r_players) > 0)
	{
		foreach (new ply : t_r_players)
		{
			
	
			if(IsPlayerInAnyVehicle(ply))
			{
				OnPlayerSpawn(ply);
				Iter_SafeRemove(t_r_players, ply, next);
				ply = next;
				
			}
			
		}
	}*/
	UpdateEvStat();
	return 1;
}

#define _wg 4
#define w_g_start_players 2
#define w_g_start_players_max 100 //mo¿na zmieniæ na wiêcej tylko w tedy gdy doda siê spawny w zmiennej script_wg_spawn[script_wg[arena]].


enum w_g_event {
	winreed, 
	bool:statees, 
	bool:starting, 
	Timer, 
	team[2], 
	punkty[2], 
	wg_currentteam, 
	team_player[MAX_PLAYERS], 
	arena, 
	load_aren
}
new script_wg[w_g_event];
new Iterator:w_g_players<MAX_PLAYERS>;
 
 
#define MAX_wg_AREN 55
#define MAX_wg_AREN_SP 200

new wg_losowanie[MAX_wg_AREN];

enum wg_arens{

	wg_name[60], 
	uid, 
	Interior, 
	loades, 
	wg_zone,
	wg_stream,
	bool:active, 
	Float:wg_pos1[4], 
	Float:wg_pos2[4]
};
new script_wg_aren[MAX_wg_AREN][wg_arens];

/*
enum wg_arens_{
	Float:possek1[4], 
	Float:possek2[4]
};
new script_wg_spawn[MAX_wg_AREN][MAX_wg_AREN_SP][wg_arens_];
*/

 
 

 
 
CMD:wgexit(playerid, params[])
{
	if(removeIsEvent(playerid) == 0)return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Nie jesteœ zapisany(a) na ¿aden event.");
 
	SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} ›››{/b}  Wypisa³eœ(aœ) siê z Wojny Gangów.");
	return 1;
}

CMD:wg(playerid, params[])
{
 	if(Iter_Contains(w_g_players, playerid))return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Jesteœ ju¿ zapisany(a) na Wojna Gangów.");
	if(Iter_Count(w_g_players) >= script_wg_aren[script_wg[arena]][loades] && script_wg[statees] == true) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Na Wojna Gangów zapisa³o siê zbyt du¿o osób, spróbuj w nastêpnej kolejce."); 
	if(script_wg[statees] == true) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Wojna gangów aktualnie trwa");
 	removeIsEvent(playerid);

	Iter_Add(w_g_players, playerid);
	if(Iter_Count(w_g_players) == w_g_start_players && script_wg[statees] == false && script_wg[starting] == false)
	{

		StartWG();
		script_wg[starting] = true;
	}
	statsUpdate = 11;
	UpdateEvStat();
	SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} ›››{/b}  Zapisa³eœ(aœ) siê na Wojna Gangów.");
 	return 1;
}
 
stock StartWG()
{
	if(!script_wg[load_aren]) 
	{
		Iter_Clear(w_g_players);
		UpdateEvStat();
		
		script_wg[starting] = false;
		SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Wojna Gangów nie mog³a wystartowaæ z powodu braku areny");
		return 1;
	}
	if(!script_wg[starting])
	{
		new ArenaId = wg_losowanie[random(script_wg[load_aren])];
		if(script_wg_aren[ArenaId][active] == false) return StartWG();
		script_wg[arena] = ArenaId;
		SetTimer("script_wg_Go", 20000, 0);
		TextDrawUpdateEventStart("Wojna Gangow", "/WG");
		SendClientMessageToAll(-1, "››› {008ae6}Wojna gangów{/b} wystartuje za {008ae6}20 sekund {/b}Zapisy nadal trwaj¹ {008ae6}(/WG)");
	}
	
	return 1;
}
 
forward script_wg_Go();
public script_wg_Go()
{
	script_wg[starting] = false;
 
	script_wg[winreed] = INVALID_PLAYER_ID;
	script_wg[team][0] = 0;
	script_wg[team][1] = 0;
	
	script_wg[punkty][0] = 0;
	script_wg[punkty][1] = 0;
	
	UpdateEvStat();
	SendClientMessageToAll(COLOR_EVENT_STARTED, "››› Wojna Gangów wystartowa³a!");
	
	new ar, Float:CameraWg[3];
	
	if(!script_wg_aren[script_wg[arena]][Interior])
	{
		for(new i;i<3;i++)
			CameraWg[i] = (script_wg_aren[script_wg[arena]][wg_pos1][i] + script_wg_aren[script_wg[arena]][wg_pos2][i]) / 2;
  	}
	
	foreach (new p : w_g_players)
   	{
   	    if(!IsPlayerConnected(p)) continue;
		
		PlayerEventTDSet(p, "Startuje", "~b~Wojna ~g~Gangow");
		 
		script_wg[team_player][p] = -1;
		pInfo[p][player_awarn] = 0;
		
        ResetPlayerWeapons(p);
		SetPlayerArmour(p, 0.0);
		SetPlayerInterior(p, script_wg_aren[script_wg[arena]][Interior]);
		SetPlayerVirtualWorld(p, 147);
		TogglePlayerControllable(p, 0);
		GangZoneShowForPlayer(p, script_wg_aren[script_wg[arena]][wg_zone], 0x00cc1160);
		SetCameraBehindPlayer(p);
		 
		pInfo[p][player_awarn] = 0;
		if(!script_wg_aren[script_wg[arena]][Interior])
		{
			SetPlayerCameraPos(p, CameraWg[0], CameraWg[1], CameraWg[2] + 75.0);
			SetPlayerCameraLookAt(p, CameraWg[0], CameraWg[1], CameraWg[2]);
		}
		if(script_wg[wg_currentteam] == 0)
		{
			SetPlayerSkin(p, 170);
			script_wg[wg_currentteam] = 1;
			script_wg[team][0]++; //ZIELONI
			script_wg[team_player][p] = 0;
			
			SetPlayerPos(p, script_wg_aren[script_wg[arena]][wg_pos1][0], script_wg_aren[script_wg[arena]][wg_pos1][1], script_wg_aren[script_wg[arena]][wg_pos1][2]);
			SetPlayerFacingAngle(p, script_wg_aren[script_wg[arena]][wg_pos1][3]);

			SendClientMessage(p, COLOR_GREEN, "{FFFFFF} ›››{/b} *(Green)› Startujesz w dru¿ynie Zielonych!");
			SetPlayerTeam(p, 700);
			SetPlayerColor(p, 0x00FF00FF);
			
		}
		else if(script_wg[wg_currentteam] == 1)
		{
			SetPlayerSkin(p, 177);
			script_wg[wg_currentteam] = 0;
			script_wg[team][1]++; //NIEBISCY
			script_wg[team_player][p] = 1;
			
			SetPlayerPos(p, script_wg_aren[script_wg[arena]][wg_pos2][0], script_wg_aren[script_wg[arena]][wg_pos2][1], script_wg_aren[script_wg[arena]][wg_pos2][2]);
			SetPlayerFacingAngle(p, script_wg_aren[script_wg[arena]][wg_pos2][3]);
			 
			SendClientMessage(p, COLOR_ERROR, "{FF0000} ›››{/b} *(Blue)› Startujesz w dru¿ynie Niebieskich!");
			
			SetPlayerColor(p, 0x0000FFFF);
			SetPlayerTeam(p, 701);
			
		}
 
		ar++;
		SetPlayerHealth(p, 100.0);
		SetPlayerArmour(p, 0.0);
		
		SetPlayerInterior(p, script_wg_aren[script_wg[arena]][Interior]);
		
		GivePlayerWeapon(p, 4, 500);
		GivePlayerWeapon(p, 24, 1000);
		GivePlayerWeapon(p, 25, 100);
		GivePlayerWeapon(p, 34, 500);
 
		 
		 
	}
	UpdateEvStat();
 	
 	SetTimer("script_wg_rlg", 1500, 0);
	return 1;
}

stock IsPlayerInWgArena(playerid)
{
	return IsPlayerInDynamicArea(playerid, script_wg_aren[script_wg[arena]][wg_stream]);
}
stock SetPlayerSpawnWG(p)
{
	if(!script_wg[team_player][p])
	{
		SetPlayerPos(p, script_wg_aren[script_wg[arena]][wg_pos1][0], script_wg_aren[script_wg[arena]][wg_pos1][1], script_wg_aren[script_wg[arena]][wg_pos1][2]);
		SetPlayerFacingAngle(p, script_wg_aren[script_wg[arena]][wg_pos1][3]);
		
	}
	else
	{
		SetPlayerPos(p, script_wg_aren[script_wg[arena]][wg_pos2][0], script_wg_aren[script_wg[arena]][wg_pos2][1], script_wg_aren[script_wg[arena]][wg_pos2][2]);
		SetPlayerFacingAngle(p, script_wg_aren[script_wg[arena]][wg_pos2][3]);
	}
	return 1;
}
forward script_wg_rlg();
public script_wg_rlg()
{
	script_wg[statees] = true;
	
	foreach (new i : w_g_players)
   	{
   	    if(!IsPlayerConnected(i)) continue;
		TogglePlayerControllable(i, 1);
		SetPlayerSpawnWG(i);
		SetCameraBehindPlayer(i);
		
   		PlayerEventTDSet(i, "Trwa", "~b~Wojna ~g~Gangow");
	}

 	return 1;
}

forward script_wg_update();
public script_wg_update()
{

	if(!script_wg[statees]) return 1;
    if(Iter_Count(w_g_players) == 0)
	{
		 
 		Iter_Clear(w_g_players);
	    script_wg[statees] = false;
		SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Wojna Gangów zosta³y zakoñczona z powodu braku graczy.");
	    return 1;
	}

	if(Iter_Count(w_g_players) == 1)
	{	
 		foreach (new p : w_g_players)
		{
			if(!IsPlayerConnected(p)) continue;
			script_wg[winreed] = p;
	    	break;
		}
	}
	
	script_wg[Timer]++;

	if(script_wg[winreed] != INVALID_PLAYER_ID)
	{
		 
 	    GivePlayerMoney(script_wg[winreed], 10000);
     	SetPlayerColorEx(script_wg[winreed]);
 
    	SendClientMessageToAll((script_wg[team_player][script_wg[winreed]] == 0) ? (-1): (-1), "{008ae6}Wojne gangów{/b} wygrywa dru¿yna {008ae6}%s{/b} ", (script_wg[team_player][script_wg[winreed]] == 0) ? ("Zielonych"): ("Niebieskich"));
		
	    script_wg[statees] = false;
		foreach (new p : w_g_players)
		{
			if(script_wg[team_player][p] == script_wg[team_player][script_wg[winreed]])
			{
				addPointEvent(p, stats_wg);
			}
			OnPlayerSpawn(p);
		}
		Iter_Clear(w_g_players);
		UpdateEvStat();
	    return 1;
	}
//	new Float:player_possek[3];
	new c_team[2], next;
	foreach (new p : w_g_players)
	{
	   if(!IsPlayerConnected(p)) continue;
	   
	   if(script_wg[team_player][p] == 0)
			c_team[0]++;
		else
			c_team[1]++;
			
	}
	if(c_team[0] == 0 || c_team[1] == 0)  script_wg[winreed] = Iter_Random(w_g_players);
	if(c_team[0] == 1 && c_team[1] == 0)  script_wg[winreed] = Iter_Random(w_g_players);
	if(c_team[0] == 0 && c_team[1] == 1)  script_wg[winreed] = Iter_Random(w_g_players);
	
	format(ee_stri, sizeof(ee_stri), "~w~Gracze: ~g~~h~%d, ~b~~h~%d~n~~w~Punkty: ~g~~h~%d, ~b~~h~%d", c_team[0], c_team[1], script_wg[punkty][1], script_wg[punkty][0]);
	foreach (new p : w_g_players)
	{
		if(!IsPlayerConnected(p)) continue;
		PlayerEventTDSet(p, ee_stri, "~b~Wojna ~g~Gangow");
		
		//  GetPlayerPos(p, player_possek[0], player_possek[1], player_possek[2]);
		if(!IsPlayerInRangeOfPoint(p, 400.0, script_wg_aren[script_wg[arena]][wg_pos2][0], script_wg_aren[script_wg[arena]][wg_pos2][1], script_wg_aren[script_wg[arena]][wg_pos2][2])){
			SetPlayerColorEx(p);
			
			SetPlayerColorEx(p);
			OnPlayerSpawn(p);
			Iter_SafeRemove(w_g_players, p, next);
			p = next;

			continue;
		}
		if(IsPlayerInAnyVehicle(p))
		{
 			
			SetPlayerColorEx(p);
			OnPlayerSpawn(p);
			Iter_SafeRemove(w_g_players, p, next);
			p = next;

			continue;
		}
		if(!IsPlayerInWgArena(p) && script_wg_aren[script_wg[arena]][Interior] == 0)
		{
			
			SendClientMessage(p, 0xFF0000FF, ""chat" Nie wolno wychodziæ po za strefe zabawy!");
			
			if(script_wg[Timer] > 10)
			{
				pInfo[p][player_awarn]++;
				
				if(pInfo[p][player_awarn] > 15)
				{
						SetPlayerColorEx(p);
						OnPlayerSpawn(p);
						Iter_SafeRemove(w_g_players, p, next);
						p = next;

						continue;
				}
				else 
				{
					new str[64];
					format(str, sizeof(str), "~n~~n~~n~~n~Wroc na teren zabawy! warn %i / 15", pInfo[p][player_awarn]);
					GameTextForPlayer(p, str, 1500, 3);
				}
			}
		}
		else {
			//GetPlayerPos(p, pInfo[p][player_lastpos][0], pInfo[p][player_lastpos][1], pInfo[p][player_lastpos][2]);
			 
			pInfo[p][player_awarn] = 0;
		}
	}
 
	UpdateEvStat();
 
    return 1;
}
 
 

LoadEvent_WG()
{
	new czas = GetTickCount();
	 
	mysql_query("SELECT * FROM "prefix"_wg limit "#MAX_wg_AREN"");
	mysql_store_result();
	new f[20], cord0[128], Float:wpos[4];
	for(new i;i<mysql_num_rows();i++)
	{
		mysql_data_seek(i);//
		mysql_fetch_row_data();
		 
		new int;
		
		mysql_fetch_field("Interior", f);	
		int = strval(f);
		
		mysql_fetch_field("id", f);	
		script_wg_aren[strval(f)][uid] = strval(f);
		script_wg_aren[strval(f)][Interior] = int;
		 
		
		mysql_fetch_field("spawn1", cord0);	
		if(sscanf(cord0, "p<,>a<f>[4]", script_wg_aren[strval(f)][wg_pos1])) printf("b³¹d rodzielania areny WG ");
		
		mysql_fetch_field("spawn2", cord0);	
		if(sscanf(cord0, "p<,>a<f>[4]", script_wg_aren[strval(f)][wg_pos2])) printf("b³¹d rodzielania areny WG ");
		
		mysql_fetch_field("Strefa", cord0);	
		if(sscanf(cord0, "p<,>a<f>[4]", wpos)) printf("b³¹d rodzielania areny WG ");
		
		if(script_wg_aren[strval(f)][Interior]==0)
		{
			script_wg_aren[strval(f)][wg_zone] = GangZoneCreate(wpos[0], wpos[1], wpos[2], wpos[3]);
			script_wg_aren[strval(f)][wg_stream] = CreateDynamicRectangle(wpos[0], wpos[1], wpos[2], wpos[3]);		
		}
		 
		
		script_wg_aren[strval(f)][active] = true;
		
		wg_losowanie[i] = strval(f);
		
	 
		script_wg[load_aren]++;
		
		 
	}
	printf("[load] wczytanych aren wg:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	mysql_free_result();

}  
CMD:arena_wg(playerid, params[])
{
	
	return 1;
}
//ctf

#define _ctf 0
enum event_CTF
{
	ctf_timer, 
	bool:ctf_member[MAX_PLAYERS], 
	ctf_team[MAX_PLAYERS], 
	ctf_liczba, 
	ctf_liczba2, 
	ctf_up[30], 
	ctf_on, 
 
	ctf_team_liczba[10], 
	ctf_score[10], 
	ctf_freeze[MAX_PLAYERS], 
	ctf_flag, 
	ctf_flag_carry, 
	ctf_flag_carry_slot, 
	Text:ctf_td, 
	ctf_interior, 
	ctf_arena
}
new CTF[event_CTF];

new Float:CTFFlagpossek[4][3];
new Float:CTFSpawnpossek[4][2][3];

#define MIN_CTF_PLAYERS 2
#define MIN_CTF_PLAYERS_TEAM 0
#define CTF_FLAG 2
//ctf

 

 

 
forward CTFUpdate();
public CTFUpdate()
{
	
	if(!CTF[ctf_on]) return 1;
	
	//new string[50];
	format(string2, sizeof(string2), "~b~~h~~h~Niebiescy:~w~ %d/"#CTF_FLAG"~n~~g~ Zieloni:~w~ %d/"#CTF_FLAG"", CTF[ctf_score][0], CTF[ctf_score][1]);
	TextDrawSetString(CTF[ctf_td], string2);
	
	CTF[ctf_team_liczba][0] = 0;
	CTF[ctf_team_liczba][1] = 0;
	foreach(new x : Player)
	{
		if(CTF[ctf_team][x] == 1)
		{
			CTF[ctf_team_liczba][0] ++;
		}
		else if(CTF[ctf_team][x] == 2)
		{
			CTF[ctf_team_liczba][1] ++;
		}
	}

	if(CTF[ctf_team_liczba][0] <= 0)
	{
		win_ctf(1);
	}else if(CTF[ctf_team_liczba][1] <= 0)
	{
		win_ctf(0);
	}
 	return 1;
}

LoadEvent_CtfSpawn(){
	new czas = GetTickCount();
	 
	mysql_query("SELECT flaga_x, flaga_y, flaga_z, x0, y0, z0, x1, y1, z1 FROM "prefix"_ctf");
	mysql_store_result();
	 
//	new string2[200];
	for(new i;i<mysql_num_rows();i++)
	{
		mysql_fetch_row(string2, "|");
		
		if(sscanf(string2, "p<|>a<f>[3]a<f>[3]a<f>[3]", CTFFlagpossek[i], CTFSpawnpossek[i][0], CTFSpawnpossek[i][1])) printf("blad rodzielania");
		
	//	printf("%s", string2);
	}
	printf("[load] wczytanych spawnów ctf:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	mysql_free_result();

}
forward CTFStart();
public CTFStart()
{
	
	TextDrawSetString(CTF[ctf_td], "Load...");
 	CTF[ctf_liczba] = 0;
	format(CTF[ctf_up], 30, "~r~~h~Trwa");
	
	CTF[ctf_on] = true;
	CTF[ctf_team_liczba][0] = 0;
	CTF[ctf_team_liczba][1] = 0;
	CTF[ctf_flag_carry] = -1;
	CTF[ctf_score][0] = 0;
	CTF[ctf_score][1] = 0;
	DestroyObject(CTF[ctf_flag]);
	
	CTF[ctf_arena] = random(3);

		
  
	CTF[ctf_interior] = 0; 
	
	CTF[ctf_flag] = CreateObject(11245, CTFFlagpossek[CTF[ctf_arena]][0], CTFFlagpossek[CTF[ctf_arena]][1], CTFFlagpossek[CTF[ctf_arena]][2], 0, 288.53997802734, 328.23999023438);
 	new bool:TeamCount = false;
	foreach(new i : Player)
	{
		
		if(CTF[ctf_member][i]){
			 
			
			TextDrawShowForPlayer(i, CTF[ctf_td]);
			if(TeamCount == false){
				CTF[ctf_team][i] = 1;
				SendClientMessage(i, COLOR_BLUE, "Startujesz w dru¿ynie {b}niebieskich{/b}, biegnij po flage !");
				CTFSpawn(i);
				SetPlayerTeam(i, 1);
				TeamCount = true;
			}
			else
			{
				CTF[ctf_team][i] = 2;
				SendClientMessage(i, COLOR_GREEN, "{FFFFFF} ›››{/b} Startujesz w dru¿ynie zielonych, biegnij po flage !");
				CTFSpawn(i);
				SetPlayerTeam(i, 2);
				TeamCount = false;
			}
			
		}
	}

     
	CTFUpdate();
	return 1;
}
 
stock DetachObject(objectid, modelid)
{
	new Float:poxs[3];
	GetObjectPos(objectid, poxs[0], poxs[1], poxs[2]);
	DestroyObject(objectid);
	CTF[ctf_flag] = CreateObject(modelid, poxs[0], poxs[1], poxs[2], 0, 288.53997802734, 328.23999023438);
	return 1;
}




forward CTFSpawn(playerid);
public CTFSpawn(playerid)
{
	
	TogglePlayerControllable(playerid, 0);
	FreezePlayerTime(playerid, 1);
	
	SetPlayerVirtualWorld(playerid, 11);
	if(CTF[ctf_flag_carry] == -1){
		SetPlayerRaceCheckpoint (playerid, 2, CTFFlagpossek[CTF[ctf_arena]][0], CTFFlagpossek[CTF[ctf_arena]][1], CTFFlagpossek[CTF[ctf_arena]][2], CTFFlagpossek[CTF[ctf_arena]][0], CTFFlagpossek[CTF[ctf_arena]][1], CTFFlagpossek[CTF[ctf_arena]][2], 2);
	}
	
	if(CTF[ctf_team][playerid] == 1)
	{ // niebiescy
		SetPlayerPos(playerid, CTFSpawnpossek[CTF[ctf_arena]][0][0], CTFSpawnpossek[CTF[ctf_arena]][0][1], CTFSpawnpossek[CTF[ctf_arena]][0][2]);

		SetPlayerVirtualWorld(playerid, 11);
		SetPlayerInterior(playerid, CTF[ctf_interior]);
		SetPlayerColor(playerid, 0x0482FFFF);
		SetPlayerHealth(playerid, 100);
		SetPlayerArmour(playerid, 0);
		ResetPlayerWeapons(playerid);
		GivePlayerWeapon(playerid, 4, 1);
		GivePlayerWeapon(playerid, 24, 1000);
		GivePlayerWeapon(playerid, 31, 3000);
		GivePlayerWeapon(playerid, 34, 3000);
		
		return 1;
	}
	if(CTF[ctf_team][playerid] == 2)
	{// zieloni
		SetPlayerPos(playerid, CTFSpawnpossek[CTF[ctf_arena]][1][0], CTFSpawnpossek[CTF[ctf_arena]][1][1], CTFSpawnpossek[CTF[ctf_arena]][1][2]);

		SetPlayerVirtualWorld(playerid, 11);
		SetPlayerInterior(playerid, CTF[ctf_interior]);
		SetPlayerColor(playerid, 0x00CC00FF);
		SetPlayerHealth(playerid, 100);
		SetPlayerArmour(playerid, 0);
		ResetPlayerWeapons(playerid);
		GivePlayerWeapon(playerid, 4, 1);
		GivePlayerWeapon(playerid, 24, 1000);
		GivePlayerWeapon(playerid, 31, 3000);
		GivePlayerWeapon(playerid, 34, 3000);
		
		return 1;
	}
	return 1;
}

 

forward RespawnFlaga();
public RespawnFlaga()
{
	
	CTF[ctf_flag] = CreateObject(11245, CTFFlagpossek[CTF[ctf_arena]][0], CTFFlagpossek[CTF[ctf_arena]][1], CTFFlagpossek[CTF[ctf_arena]][2], 0, 288.53997802734, 328.23999023438);
	CTF[ctf_flag_carry] = -1;
	
	foreach( new i : Player)
	{
		if(CTF[ctf_team][i] > 0)
		{
			SetPlayerRaceCheckpoint (i, 2, CTFFlagpossek[CTF[ctf_arena]][0], CTFFlagpossek[CTF[ctf_arena]][1], CTFFlagpossek[CTF[ctf_arena]][2], CTFFlagpossek[CTF[ctf_arena]][0], CTFFlagpossek[CTF[ctf_arena]][1], CTFFlagpossek[CTF[ctf_arena]][2], 2);
			SendClientMessage(i, COLOR_PINK, "[CTF] Flaga na respawnie!");
		}
	}
	
	return 1;
}



forward przeczepflaa(playerid);
public przeczepflaa(playerid)
{
	DestroyObject(CTF[ctf_flag]);
	return 1;
}

forward CTFFlagDown(playerid);
public CTFFlagDown(playerid)
{
	
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	DetachObject(CTF[ctf_flag], 11245);
	MoveObject(CTF[ctf_flag], x, y, z, 999);
	CTF[ctf_flag_carry] = -2;
	OnPlayerSpawn(playerid);
	for(new i; i <MAX_PLAYERS; i++)
	{
		if(CTF[ctf_team][i] > 0)
		{
			SetPlayerRaceCheckpoint (i, 2, x, y, z, x, y, z, 2);
			SendClientMessage(i, COLOR_PINK, "Flaga na ziemi!");
		}
	}
	
	return 1;
}

forward win_ctf(Team);
public win_ctf(Team)
{
	DestroyObject(CTF[ctf_flag]);
	CTF[ctf_liczba2] = 0;
	if(Team == 0){
		
		
		foreach(new x : Player){
			//if(CTF[ctf_team][x] != 0)
			if(IsPlayerConnected(x)){
				SendClientMessage(x, COLOR_BLUE, "CTF wygrywaja {b}Niebiescy");
			}
		}
		
		
		
	}else if(Team == 1){
		
		
		foreach(new x : Player){
			//if(CTF[ctf_team][x] != 2)
			if(IsPlayerConnected(x)){
				SendClientMessage(x, COLOR_GREEN, "{FFFFFF} ›››{/b} CTF wygrywaja {b}Zieloni");		 
			}
		}
		
	}else if(Team == 3){
		SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Admin przerywa CTF");
	}
	
	foreach(new x : Player){
		
		if(CTF[ctf_member][x] == true){
			//SetPlayerColorEx(x);
			OnPlayerSpawn(x);
			DisablePlayerRaceCheckpoint(x);
		}
		CTF[ctf_member][x] = false;
		CTF[ctf_team][x] = 0;
 
	}
	
	
 	CTF[ctf_liczba] = 0;
	format(CTF[ctf_up], 30, "~w~%d/"#MIN_CTF_PLAYERS"", CTF[ctf_liczba]);
	
	CTF[ctf_on] = false;
	CTF[ctf_team_liczba][0] = 0;
	CTF[ctf_team_liczba][1] = 0;
	CTF[ctf_flag_carry] = -1;
	CTF[ctf_score][0] = 0;
	CTF[ctf_score][1] = 0;
	DestroyObject(CTF[ctf_flag]);
	TextDrawHideForAll(CTF[ctf_td]);
   
	UpdateEvStat();
	return 1;
}

/*
CMD:ctfexit(playerid, cmdtext[])
{
	if(removeIsEvent(playerid) == 0)return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Nie jesteœ zapisany(a) na ¿aden event.");

	if(CTF[ctf_flag_carry] == playerid)
	{
		CTFFlagDown(playerid);
	}
	CTF[ctf_team][playerid] = 0;
	CTF[ctf_member][playerid] = false;
	TextDrawHideForPlayer(playerid, CTF[ctf_td]);
	OnPlayerSpawn(playerid);
	DisablePlayerRaceCheckpoint(playerid);
	SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Wypisa³eœ(aœ) siê z CTF");
	CTF[ctf_liczba2]--;
	UpdateEvStat();
	return 1;
}
CMD:ctf(playerid, params[]){
 	if(CTF[ctf_on] == 1){
		SendClientMessage(playerid, COLOR_INFO, "{FFFFFF} ›››{/b} Capture The Flag juz wystartowala");
		return 1;
	}
	if(CTF[ctf_member][playerid]){
		SendClientMessage(playerid, COLOR_INFO, "{FFFFFF} ›››{/b} Jestes juz zapisany(a) na Capture The Flag!");
		return 1;
	}
 	
	removeIsEvent(playerid);
	CTF[ctf_liczba] ++;
	CTF[ctf_member][playerid] = true;
 
	SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Zapisales(as) sie na Capture The Flag!");
 
	CTF[ctf_liczba2]++;
	format(CTF[ctf_up], 30, "~w~%d/"#MIN_CTF_PLAYERS"", CTF[ctf_liczba]);
 	
	if(CTF[ctf_liczba] == MIN_CTF_PLAYERS){
		CTF[ctf_member][playerid] = true;
		SetTimer("CTFStart", 20000, 0);
		SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Capture The Flag wystartuje za 20 sek. /ctf (Nadal Trwaja zapisy!)");
 		format(CTF[ctf_up], 30, "~y~~h~Startuje");
		TextDrawUpdateEventStart("Capture The Flag", "/CTF");
   		return 1;
	}
	statsUpdate = 11;
	UpdateEvStat();
	
	return 1;
}
 
*/

#define _ch 7
#define c_h_start_players 3
#define c_h_start_players_max 100 


enum c_h_eventx {
	winreed, 
	bool:statees, 
	bool:starting, 
	Timer, 
	team[2], 
	punkty[2], 
	wg_currentteam, 
	team_player[MAX_PLAYERS], 
	warn_player[MAX_PLAYERS],
	arena, 
	load_aren
}
new script_ch[c_h_eventx];
 
 
#define MAX_ch_AREN 30

new ch_losowanie[MAX_ch_AREN];

enum ch_arens{

	ch_name[60], 
	uid, 
	Interior, 
	loades, 
	bool:active, 
	Float:ch_pos1[4], 
	Float:ch_pos2[4]
};
new script_ch_aren[MAX_ch_AREN][ch_arens];
 
 
 
 

 
CMD:chexit(playerid, params[])
{
	if(removeIsEvent(playerid) == 0)return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Nie jesteœ zapisany(a) na ¿aden event.");
	UpdateEvStat();
	SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} ›››{/b}  Wypisa³eœ(aœ) siê z Chowany.");
	return 1;
}

CMD:ch(playerid, params[])
{
 	if(Iter_Contains(c_h_players, playerid))return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Jesteœ ju¿ zapisany(a) na Chowany.");
	if(Iter_Count(c_h_players) >= script_ch_aren[script_ch[arena]][loades] && script_ch[statees] == true) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Na Chowany zapisa³o siê zbyt du¿o osób, spróbuj w nastêpnej kolejce."); 
	if(script_ch[statees] == true) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Chowany aktualnie trwa");
 	removeIsEvent(playerid);

	Iter_Add(c_h_players, playerid);
	if(Iter_Count(c_h_players) == c_h_start_players && script_ch[statees] == false && script_ch[starting] == false)
	{
		//script_ch[arena] = random(script_ch[load_aren]);
   		//SetTimer("script_ch_Go", 10000, 0);
   		//SendClientMessageToAll(COLOR_EVENT_STARTED, "››› Chowany wystartuje za 10 sekund. aby siê zapisaæ  u¿yj /ch  ");
		start_ch();
		script_ch[starting] = true;
		 
	}
	statsUpdate = 11;
	UpdateEvStat();
	SendClientMessage(playerid, COLOR_ORANGE, "{FFFFFF} ›››{/b}  Zapisa³eœ(aœ) siê na Chowany.");
 	return 1;
}
stock start_ch()
{
	if(script_ch[load_aren] == 0) 
	{
		Iter_Clear(c_h_players);
		UpdateEvStat();
		script_ch[starting] = false;
		return SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Chowany, nie móg³ wystartowaæ z powodu braku areny");
	}
	if(script_ch[starting] == true) return 1;
	new losuj = ch_losowanie[random(script_ch[load_aren])];
	if(script_ch_aren[losuj][active] == false) return start_ch();
	script_ch[arena] = losuj;
   	SetTimer("script_ch_Go", 20000, 0);
	TextDrawUpdateEventStart("Chowany", "/CH");
   	SendClientMessageToAll(-1, "››› {008ae6}Chowany {/b}wystartuje za {008ae6}20 sekund {/b}Zapisy nadal trwaj¹ {008ae6}(/ch)");
	return 1;
}
forward script_ch_Go();
public script_ch_Go()
{
	script_ch[starting] = false;
	if(Iter_Count(c_h_players) <= 1)
	{
	 
 		Iter_Clear(c_h_players);
	    script_ch[statees] = false;
		SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Chowany nie wystartowa³a z powodu braku graczy.");
	    return 1;
	}
	 
	script_ch[winreed] = INVALID_PLAYER_ID;
	script_ch[team][0] = 0;
	script_ch[team][1] = 0;
	
	UpdateEvStat();
	SendClientMessageToAll(-1, "››› {008ae6}Chowany{/b} wystartowa³a!");
	
 
	
	new ar, szukajacy;
  	foreach (new p : c_h_players)
   	{
		PlayerEventTDSet(p, "Startuje", "Chowany");
   	    if(!IsPlayerConnected(p)) continue;
		SetPlayerArmour(p, 0.0);
		script_ch[team_player][p] = -1;
		//if(p > sizeof(script_ch_aren[script_ch[arena]]))break; 
        ResetPlayerWeapons(p);
		SetPlayerInterior(p, script_ch_aren[script_ch[arena]][Interior]);
		SetPlayerVirtualWorld(p, 147);
		if(script_ch[wg_currentteam] == 0){
			script_ch[wg_currentteam] = 1;
			script_ch[team][0]++; //szukaj¹cy
			script_ch[team_player][p] = 0;
			SetPlayerPos(p, script_ch_aren[script_ch[arena]][ch_pos1][0], script_ch_aren[script_ch[arena]][ch_pos1][1], script_ch_aren[script_ch[arena]][ch_pos1][2]);
			SetPlayerFacingAngle(p, script_ch_aren[script_ch[arena]][ch_pos1][3]);
			TogglePlayerControllable(p, 0);
			SendClientMessage(p, COLOR_ERROR, "{FF0000} ›››{/b} Zosta³eœ szukaj¹cym!");
			SetPlayerColor(p, 0xFFFFFF00);
			GivePlayerWeapon(p, 38, 50000);
			SetPlayerTeam(p, 1);
			
		}else if(script_ch[wg_currentteam] == 1){
			if(szukajacy >= ar){
				script_ch[wg_currentteam] = 0;
				szukajacy += 4;
			}else script_ch[wg_currentteam] = 1;
			 
			script_ch[team][1]++; //NIEBISCY
			script_ch[team_player][p] = 1;
			SetPlayerPos(p, script_ch_aren[script_ch[arena]][ch_pos2][0], script_ch_aren[script_ch[arena]][ch_pos2][1], script_ch_aren[script_ch[arena]][ch_pos2][2]);
			SetPlayerFacingAngle(p, script_ch_aren[script_ch[arena]][ch_pos2][3]);
			TogglePlayerControllable(p, 1);
			SendClientMessage(p, COLOR_ERROR, "{FF0000} ›››{/b} Zosta³eœ chowaj¹cym. Ukryj siê dobrze!");
			SetPlayerColor(p, 0xFFFFFF00);
			SetPlayerTeam(p, 2);
			
		}
		script_ch[warn_player][p] = 0;
		SetPlayerInterior(p, script_ch_aren[script_ch[arena]][Interior]);
		ar++;
		SetPlayerHealth(p, 100.0);
		SetPlayerArmour(p, 0.0);
	  
		SetCameraBehindPlayer(p);
		 
	}
 
 	UpdateEvStat();
	script_ch[statees] = true;
 	SetTimer("script_ch_rlg", 1000, 0);
	ch_gt_update(60);
	return 1;
}
Public:ch_gt_update(czas)
{
	if(script_ch[statees] != true) return 1;
	if(czas > 0){
		foreach (new i : c_h_players)
		{
			SetPlayerInterior(i, script_ch_aren[script_ch[arena]][Interior]);
			if(script_ch[team_player][i] == 1)format(string2, sizeof(string2), "~n~~g~~h~Chowac sie ~w~!~n~~w~%d s", czas);
			else{
				format(string2, sizeof(string2), "~n~~g~~h~Szukasz za ~w~!~n~~w~%d s", czas);
				SetPlayerHealth(i, 100.0);
				TogglePlayerControllable(i, 0);
			}
			PlayerEventTDSet(i, string2, "Chowany ");
		}
		SetTimerEx("ch_gt_update", 1000, 0, "d", czas-1);
		return 1;		
	}
	foreach (new i : c_h_players){
		TogglePlayerControllable(i, 1);
		PlayerEventTD(i, false);
	}
	
	return 1;
}
forward script_ch_rlg();
public script_ch_rlg()
{
	if(script_ch[statees] != true) return 1;


	foreach (new i : c_h_players)
   	{
   	    if(!IsPlayerConnected(i)) continue;
		//TogglePlayerControllable(i, 1);
   		//GameTextForPlayer(i, "~r~Start", 500, 1);
	}

 	return 1;
}

forward script_ch_update();
public script_ch_update()
{
    if(script_ch[statees] != true) return 1;

    if(Iter_Count(c_h_players) == 0 || script_ch[winreed] == INVALID_PLAYER_ID+1)
	{
		 
 		Iter_Clear(c_h_players);
	    script_ch[statees] = false;
		SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Chowany zosta³y zakoñczona z powodu braku graczy.");
	    return 1;
	}

	if(Iter_Count(c_h_players) == 1)
	{	
 		foreach (new p : c_h_players)
		{
			if(!IsPlayerConnected(p)) continue;

	    	
			SetPlayerColorEx(p);
 
	    	SetPlayerVirtualWorld(p, 0);
	    	TogglePlayerControllable(p, 1);
	    	SetPlayerHealth(p, 100.0);
	    	ResetPlayerWeapons(p);
		//	OnPlayerSpawn(playerid);
	    	OnPlayerSpawn(p);
 			addPointEvent(p, stats_ch);
	    	SendClientMessageToAll(-1, "{008ae6}Chowanego{/b} wygrywaj¹ {008ae6}%s ", (script_ch[team_player][p] == 0) ? ("szukaj¹cy"): ("chowaj¹cy"));
			
			GivePlayerScore(p, 50);
			GivePlayerMoney(p, 5000);
			
	    	Iter_Remove(c_h_players, p);
			break;
		}
		
		Iter_Clear(c_h_players);
	    script_ch[statees] = false;
	    return 1;
	}

	
	if(script_ch[winreed] != INVALID_PLAYER_ID && script_ch[winreed] != INVALID_PLAYER_ID+1)
	{
		 
 	    GivePlayerMoney(script_ch[winreed], 1000);
    
			
    	//format(ee_stri, sizeof(ee_stri), "na  /ch wygra³  {FFFFFF}%s (%d)", playerNick(script_ch[winreed]), script_ch[winreed]);
		new score = random(300), kasy = random(((10*10)*10)*10);
	 
		
    	SendClientMessageToAll(-1, " {008ae6}%s (%d){/b} po raz {008ae6}%d{/b} wygra³ {008ae6}/CH{/b}. I otrzymuje {008ae6}%d Score i %d${/b} ", pInfo[script_ch[winreed]][player_name], script_ch[winreed], addPointEvent(script_ch[winreed], stats_ch), score, kasy);
		GivePlayerScore(script_ch[winreed], score);
		GivePlayerMoney(script_ch[winreed], kasy);
		#if defined ADUIO_PLUGIN
		PlayCompleteMissionSound(script_ch[winreed]);
		#endif
		OnPlayerSpawn(script_ch[winreed]);
 	    script_ch[statees] = false;
		foreach (new p : c_h_players){
			OnPlayerSpawn(p);
			 
		}
		Iter_Clear(c_h_players);
		UpdateEvStat();
	    return 1;
	}
	new c_team[2], next;
	foreach (new p : c_h_players)
	{
		if(!IsPlayerConnected(p)) continue;
		if(script_ch[team_player][p] == 0)
			c_team[0]++;
		else
			c_team[1]++;
		if(!IsPlayerInRangeOfPoint(p, 300.0, script_ch_aren[script_ch[arena]][ch_pos1][0], script_ch_aren[script_ch[arena]][ch_pos1][1], script_ch_aren[script_ch[arena]][ch_pos1][2])){
			
			SetPlayerColorEx(p);
			OnPlayerSpawn(p);
			Iter_SafeRemove(c_h_players, p, next);
			p = next;

			continue;
		}
	
		if(IsPlayerInAnyVehicle(p))
		{
			
			SetPlayerColorEx(p);
			OnPlayerSpawn(p);
			Iter_SafeRemove(c_h_players, p, next);
			p = next;

			continue;
		}
		if(pInfo[p][player_afk] > 10)
		{
			
			SetPlayerColorEx(p);
			OnPlayerSpawn(p);
			Iter_SafeRemove(c_h_players, p, next);
			p = next;

			continue;
		}
		
	}
	
	if(c_team[0] == 0 || c_team[1] == 0)  script_ch[winreed] = INVALID_PLAYER_ID + 1;
	

	if(c_team[1] == 1) 
	{
		foreach(new i : c_h_players)
		{
			if(script_ch[team_player][i] == 1) script_ch[winreed] = i;
		}
		 
	}
 
    return 1;
}
stock IsPlayerInArea(playerid, Float:maxx, Float:minx, Float:maxy, Float:miny) // Autor: Y_Less
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	if (x > minx && x < maxx && y > miny && y < maxy) return 1;
	
	return 0;
	
}


LoadEvent_CH()
{
	new czas = GetTickCount();
	 
	mysql_query("SELECT * FROM "prefix"_ch");
	mysql_store_result();
	new f[20], cord0[256];
	for(new i;i<mysql_num_rows();i++)
	{
		mysql_data_seek(i);//
		mysql_fetch_row_data();
		new int;
		
		mysql_fetch_field("Interior", f);	
		 
		int = strval(f);
		
		mysql_fetch_field("id", f);	
		script_ch_aren[strval(f)][uid] = strval(f);
		
		script_ch_aren[strval(f)][Interior] = int;
		
		script_ch_aren[strval(f)][active] = true;
		ch_losowanie[i] = script_ch_aren[strval(f)][uid];
	
		mysql_fetch_field("spawn1", cord0);	
		sscanf(cord0, "p<,>a<f>[4]", script_ch_aren[strval(f)][ch_pos1]);
		
		mysql_fetch_field("spawn2", cord0);	
		sscanf(cord0, "p<,>a<f>[4]", script_ch_aren[strval(f)][ch_pos2]);
		
	  
		script_ch[load_aren]++;
		
		 
	}
	printf("[load] wczytanych aren ch:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	mysql_free_result();

}

CMD:sw(playerid,params[])
{
	new swcar;
	SetPlayerPos(playerid,9.1152,-2635.4585,39.4260);
	swcar = CreateVehicle(571,9.1152,-2635.4585,39.4260,1.1683,0,0,-1,0 );
	new objsw = CreateDynamicObject(1349,9.1152,-2635.4585,39.4260,0,0,0,300);
	AttachObjectToVehicle(objsw, swcar, 0.000000, 0.000000, 0.274999, 0.000000, 0.000000, 90.449951); //Object Model: 1349 | 
	PutPlayerInVehicle(playerid, swcar, 0);
	LinkVehicleToInterior(swcar, 6);
	return 1;
}


#define _wyscig 8
#define w_s_start_players 2
#define w_s_start_players_max 100 //mo¿na zmieniæ na wiêcej tylko w tedy gdy doda siê spawny w zmiennej script_ws_spawn[script_ws[arena]].


enum w_s_event {
	winreed, 
	bool:statees, 
	bool:starting, 
	Timer, 
	autho[MAX_PLAYERS], 
	ply_cp[MAX_PLAYERS], 
	_spawn[MAX_PLAYERS],
	arena, 
	load_aren,
	startTime,
	recordTime,
	mete_player,
	off_event,
	toupdate,
	recorder[25]
}
new script_ws[w_s_event];
new Iterator:w_s_players<MAX_PLAYERS>;
 
 

 
#define MAX_ws_AREN 15
#define MAX_ws_AREN_SP 100

new ws_losowanie[MAX_ws_AREN];

enum ws_arens{

	ws_veh, 
	uid, 
	loades, 
	loadcp, 
	bool:active,
	ws_name[60]
	 
};
new script_ws_aren[MAX_ws_AREN][ws_arens];

enum ws_arens_{
	Float:pos_sp[4], 
	Float:pos_cp[4]
};
new script_ws_spawn[MAX_ws_AREN][MAX_ws_AREN_SP][ws_arens_];



 
 
CMD:wsexit(playerid, params[])
{
	if(removeIsEvent(playerid) == 0)return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Nie jesteœ zapisany(a) na ¿aden event");
	UpdateEvStat();
	SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Wypisa³eœ(aœ) siê z wyœcigu.");
	return 1;
}

CMD:swexit(playerid,params[])
{
	
	return 1;
}

CMD:ws(playerid, params[])
{
 	if(Iter_Contains(w_s_players, playerid))return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Jesteœ ju¿ zapisany(a) na Wyœcig");
	if(Iter_Count(w_s_players) >= script_ws_aren[script_ws[arena]][loades] && script_ws[starting] == true) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Na Wyœcig zapisa³o siê zbyt du¿o osób, spróbuj w nastêpnej kolejce."); 
	if(script_ws[statees] == true) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Wyœcig aktualnie trwa");
	if(pInfo[playerid][player_objected])
		return InfoBox(playerid, "Nie mozesz zapisac sie na event poniewaz masz wylaczone obiekty");
	
	removeIsEvent(playerid);

	Iter_Add(w_s_players, playerid);
	if(Iter_Count(w_s_players) == w_s_start_players && script_ws[statees] == false && script_ws[starting] == false)
	{
		start_ws();
		script_ws[starting] = true;
		 
	}
	UpdateEvStat();
	SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} ›››{/b} Zapisa³eœ(aœ) siê na Wyœcig.");
 	return 1;
}
stock start_ws()
{
	if(script_ws[load_aren] == 0) 
	{
		Iter_Clear(w_s_players);
		UpdateEvStat();
		script_ws[starting] = false;
		return SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Wyœcig nie mog³ wystartowaæ z powodu braku areny");
	}
	if(script_ws[starting] == true) return 1;
	
	new losuj = ws_losowanie[random(script_ws[load_aren])];
	if(script_ws_aren[losuj][active] == false) return start_ws();
	script_ws[arena] = losuj;
   	SetTimer("script_ws_Go", 20000, 0);
	TextDrawUpdateEventStart("Wyscig", "/WS");
    SendClientMessageToAll(-1, "››› {008ae6}Wyœcig{/b} wystartuje za {008ae6}20 sekund {/b} Zapisy nadal trwaj¹ {008ae6}(/ws)");
	return 1;
}
stock Float:absoluteangle(Float:angle)
{
	while(angle < 0.0)angle += 360.0;
	while(angle > 360.0)angle -= 360.0;
	return angle;
}
stock Float:GetAngleToPoint(Float:fPointX, Float:fPointY, Float:fDestX, Float:fDestY)
	return absoluteangle(-(90-(atan2((fDestY - fPointY), (fDestX - fPointX)))));
	
stock raceRecords(playerid)
{	
	new xtime = (gettime()-script_ws[startTime]);
	if(script_ws[recordTime] > xtime)
	{
		raceUpdateRecord(script_ws[arena], xtime, playerid);
		Time_Convert(xtime, rmin, rsekund);
		SendClientMessageToAll(COLOR_INFO, ""chat" Gracz %s ustanowi³ nowy rekord trasy %s (/WS) - %02d:%02d", pInfo[playerid][player_name], script_ws_aren[script_ws[arena]][ws_name], rmin, rsekund);
		return xtime;
	}
	return 0;
}
forward script_ws_Go();
public script_ws_Go()
{
	script_ws[starting] = false;
	 
  	script_ws[mete_player] = 0;
	script_ws[off_event] = 0;
	
	if(Iter_Count(w_s_players) <= 1)
	{
	 
	    //KillTimer(script_ws[Timer]);
		Iter_Clear(w_s_players);
	    script_ws[statees] = false;
		SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Wyœcig nie wystartowa³ z powodu braku graczy.");
	    return 1;
	}
	 
	script_ws[winreed] = INVALID_PLAYER_ID;
	UpdateEvStat();
	SendClientMessageToAll(-1, "››› {008ae6}Wyœcig{/b} wystartowa³!");
 
	sscanf(raceRecord(script_ws[arena]), "P<|>ds[24]", script_ws[recordTime], script_ws[recorder]);
	
	Time_Convert(script_ws[recordTime], rmin, rsekund);
	
	new spawn;
  	foreach (new p : w_s_players)
   	{
   	    if(!IsPlayerConnected(p)) continue;
		
		if(!isnull(script_ws[recorder]))
		{
			SendClientMessage(p, COLOR_ORANGE, "-------------------------Wyœcig------------------------");
			SendClientMessage(p, COLOR_GREEN, "* - Rekord tej trasy to %02d:%02d by %s - *", rmin, rsekund, script_ws[recorder]);
			SendClientMessage(p, COLOR_ORANGE, "-------------------------Wyœcig------------------------");
		}
		PlayerEventTDSet(p, "Startuje", "Wyscig");
		
		Streamer_ToggleIdleUpdate(p, 0);
		Streamer_ToggleItemUpdate(p, 0, 0);
	
        ResetPlayerWeapons(p);
		SetPlayerVirtualWorld(p, 147);
		script_ws[ply_cp][p] = 0;
		
		SetPlayerPos(p, script_ws_spawn[script_ws[arena]][spawn][pos_sp][0], script_ws_spawn[script_ws[arena]][spawn][pos_sp][1], script_ws_spawn[script_ws[arena]][spawn][pos_sp][2]);
    	SetPlayerFacingAngle(p, script_ws_spawn[script_ws[arena]][spawn][pos_sp][3]);
		
	 
		SetCameraBehindPlayer(p);
		TogglePlayerControllable(p, 0);
		SetPlayerRaceCheckpoint(p, 0, script_ws_spawn[script_ws[arena]][script_ws[ply_cp][p]][pos_cp][0], script_ws_spawn[script_ws[arena]][script_ws[ply_cp][p]][pos_cp][1], script_ws_spawn[script_ws[arena]][script_ws[ply_cp][p]][pos_cp][2], script_ws_spawn[script_ws[arena]][script_ws[ply_cp][p]][pos_cp][0], script_ws_spawn[script_ws[arena]][script_ws[ply_cp][p]][pos_cp][1], script_ws_spawn[script_ws[arena]][script_ws[ply_cp][p]][pos_cp][2], 10);
		
		script_ws[_spawn][p] = spawn;
		spawn++;
		 
	}
 	script_ws[statees] = true;
	script_ws[toupdate] = 6;

 	SetTimer("script_ws_veh", 1000, 0);
	return 1;
}
forward script_ws_veh();
public script_ws_veh()
{
	#define spawn script_ws[_spawn][p]
	foreach (new p : w_s_players)
   	{
		SetPlayerPos(p, script_ws_spawn[script_ws[arena]][spawn][pos_sp][0], script_ws_spawn[script_ws[arena]][spawn][pos_sp][1], script_ws_spawn[script_ws[arena]][spawn][pos_sp][2] + 0.5);
    	SetPlayerFacingAngle(p, script_ws_spawn[script_ws[arena]][spawn][pos_sp][3]);
		
		script_ws[autho][p] = CreatePlayerVehicle(p, script_ws_aren[script_ws[arena]][ws_veh], script_ws_spawn[script_ws[arena]][spawn][pos_sp][3]);  
 		
		SetVehiclePos(script_ws[autho][p], script_ws_spawn[script_ws[arena]][spawn][pos_sp][0], script_ws_spawn[script_ws[arena]][spawn][pos_sp][1], script_ws_spawn[script_ws[arena]][spawn][pos_sp][2] + 0.5);
		SetVehicleVirtualWorld(script_ws[autho][p], 147);
		SetPlayerHealth(p, 100.0);
		PutPlayerInVehicle(p, script_ws[autho][p], 0);
	}
	#undef spawn
	SetTimerEx("script_ws_rlg", 1000, 0, "d", 3);
}
forward script_ws_rlg(czas);
public script_ws_rlg(czas)
{
	if(script_ws[statees] != true) return 1;
	
	if(czas > 0){
		format(string2, sizeof(string2), "~g~%s: ~r~%d", (czas == 1)? ("Do startu"): ("Przygotowany"), czas);
		foreach (new i : w_s_players){
			PlayerEventTDSet(i, string2, "Wyscig");
		}
		SetTimerEx("script_ws_rlg", 1000, 0, "d", czas - 1);
		return 1;
	}

	foreach (new i : w_s_players)
   	{
   	    if(!IsPlayerConnected(i)) continue;
		TogglePlayerControllable(i, 1);
   		PlayerEventTDSet(i, "Trwa", "Wyscig");
		script_ws[startTime] = gettime();
	}

    //script_ws[Timer] = SetTimer("script_ws_update", 1000, 1);
	return 1;
}

forward script_ws_update();
public script_ws_update()
{
    if(script_ws[statees] != true) return 1;
	if(script_ws[toupdate] > 0) 
	{
		script_ws[toupdate]--;
		return 1;
	}
	
	if(script_ws[off_event] > 0)
	{
		script_ws[off_event]--;
		
		if(script_ws[off_event] == 0)
		{
			foreach(new playerid : w_s_players)
			{
				DisablePlayerRaceCheckpoint(playerid);
				OnPlayerSpawn(playerid);
			}
			Iter_Clear(w_s_players);
			script_ws[statees] = false;
			
			SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Wyœcig zosta³ zakoñczony.");
		}
	}
	
    if(Iter_Count(w_s_players) == 0)
	{
		Iter_Clear(w_s_players);
	    script_ws[statees] = false;
		
		if(script_ws[mete_player])
		{
			SendClientMessageToAll(-1, "{FF0000} ›››{/b} {008ae6}Wyœcig{/b} zosta³ zakoñczony.");
		}
		else 
		{
			SendClientMessageToAll(COLOR_ERROR, "{FF0000} ›››{/b} Wyœcig zosta³ zakoñczony z powodu braku graczy.");
	    }
		return 1;
	}

	/*
	if(script_ws[winreed] != INVALID_PLAYER_ID)
	{
		 
     	//KillTimer(script_ws[Timer]);
	   
     	new kasy = random(10000), score = random(10);
		GivePlayerMoney(script_ws[winreed], kasy);
		GivePlayerScore(script_ws[winreed], score);
 		raceRecords(script_ws[winreed]);
    	SendClientMessageToAll(COLOR_ORANGE,  " %s (%d) po raz %d wygra³ {b}/ws{/b}. I otrzymuje {b}%d Score i %d${/b} ", pInfo[script_ws[winreed]][player_name], script_ws[winreed], addPointEvent(script_ws[winreed], stats_ws), score, kasy);
 	  
		script_ws[statees] = false;
		foreach (new p : w_s_players)
		{
			DisablePlayerRaceCheckpoint(p);
			OnPlayerSpawn(p);
		}
		Iter_Clear(w_s_players);
		UpdateEvStat();
		DisablePlayerRaceCheckpoint(script_ws[winreed]);
	  
		return 1;
	}
*/
	
	new next;
 
	foreach (new p : w_s_players)
	{
	   new Float:next_cp = GetPlayerDistanceFromPoint(p, script_ws_spawn[script_ws[arena]][script_ws[ply_cp][p]][pos_cp][0], script_ws_spawn[script_ws[arena]][script_ws[ply_cp][p]][pos_cp][1], script_ws_spawn[script_ws[arena]][script_ws[ply_cp][p]][pos_cp][2]);
	   new Float:finish = GetPlayerDistanceFromPoint(p, script_ws_spawn[script_ws[arena]][script_ws_aren[script_ws[arena]][loadcp] -1][pos_cp][0], script_ws_spawn[script_ws[arena]][script_ws_aren[script_ws[arena]][loadcp] -1][pos_cp][1], script_ws_spawn[script_ws[arena]][script_ws_aren[script_ws[arena]][loadcp] -1][pos_cp][2]);
	
	   format(ee_stri, sizeof(ee_stri), "Nastepny CP: %.2fm~n~Do konca: %.2fkm (%.1fm)~n~CP: %d/%d", next_cp, (finish / 1000), finish, script_ws[ply_cp][p], script_ws_aren[script_ws[arena]][loadcp]);
	   PlayerEventTDSet(p, ee_stri, "Wyscig");
 	   if(!IsPlayerInAnyVehicle(p))
	   {
			SendClientMessage(p, COLOR_CORAL, ""chat" Zosta³eœ wypisany z wyœcigu z powod tego i¿ nie by³eœ w pojedzie.");
 			OnPlayerSpawn(p);
			DisablePlayerRaceCheckpoint(p);
			Iter_SafeRemove(w_s_players, p, next);
			p = next;

			continue;
	   }
	} 
    return 1;
}
  

LoadEvent_Ws()
{
	new czas = GetTickCount();
	 
	mysql_query("SELECT * FROM "prefix"_race");
	mysql_store_result();
	new f[20];
	for(new i;i<mysql_num_rows();i++)
	{
		mysql_data_seek(i);//
		mysql_fetch_row_data();
		
		mysql_fetch_field("id", f);	
		script_ws_aren[strval(f)][uid] = strval(f);
		script_ws_aren[strval(f)][active] = true;
		ws_losowanie[i] = strval(f);
		
		mysql_fetch_field("modelpojazdu", f);	
		script_ws_aren[ws_losowanie[i]][ws_veh] = strval(f);
		
		mysql_fetch_field("name", script_ws_aren[ws_losowanie[i]][ws_name]);	
		 
		 
		script_ws[load_aren]++;
		
		 
	}
	printf("[load] wczytanych aren ws:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	mysql_free_result();

}
stock raceRecord(race)
{
	m_query("select r.record, xp.nick from mreg_race_records r left join mreg_players xp on xp.id=r.recordaccount where r.id=%d limit 1", race);
	
	mysql_store_result();
	
	new str[62];
	mysql_fetch_row(str, "|");
	
	mysql_free_result();
	
	return str;
}
stock raceUpdateRecord(race, time, playerid)
{
	m_query("update mreg_race_records set recordaccount=%d, record=%d where id=%d", pInfo[playerid][player_id], time, race);
}
LoadEvent_WsSp(){
	new czas = GetTickCount();
	 
	mysql_query("SELECT * FROM "prefix"_races_pos where typ = 'SP' order by id asc");
	mysql_store_result();
	new cord[128];
	new f[20], f2, glob, spawn;
	for(new i;i<mysql_num_rows();i++)
	{
		mysql_data_seek(i);//
		mysql_fetch_row_data();
		
		mysql_fetch_field("race_id", f);	
		 
		f2 = strval(f);
		if(script_ws_aren[f2][active]!=true) continue;
		if(f2 != glob) {spawn = 0;}
		
		mysql_fetch_field("spawn", cord);	
		if(sscanf(cord, "p<,>a<f>[4]", script_ws_spawn[f2][spawn][pos_sp])) printf("blad rodzielania");
		script_ws_aren[f2][loades]++; 
		 
	 
		spawn++;
		glob = f2;
	}
	printf("[load] wczytanych spawnów ws:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	mysql_free_result();

}
LoadEvent_WsCp(){
	new czas = GetTickCount();
	 
	mysql_query("SELECT * FROM "prefix"_races_pos where typ = 'CP' order by id asc");
	mysql_store_result();
	new cord[128];
	new f[20], f2, glob, spawn;
	for(new i;i<mysql_num_rows();i++)
	{
		mysql_data_seek(i);//
		mysql_fetch_row_data();
		
		mysql_fetch_field("race_id", f);	
		f2 = strval(f);
		if(script_ws_aren[f2][active]!=true) continue;
		if(f2 != glob) {spawn = 0;}
		mysql_fetch_field("spawn", cord);	
		if(sscanf(cord, "p<,>a<f>[4]", script_ws_spawn[f2][spawn][pos_cp])) printf("blad rodzielania");
		script_ws_aren[f2][loadcp]++; 
		 
	 
		spawn++;
		glob = f2;
	}
	printf("[load] wczytanych cp ws:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	mysql_free_result();

}
 

 

stock TextDrawUpdateEventStart(evname[], evcmd[], time = 20)
{
	if(time != 21 && aEData[ev_started]) return;
	format(stev_name, sizeof(stev_name), "%s", evname);
	format(stev_cmd, sizeof(stev_cmd), "%s", evcmd);
	stev_time = time;
 
}
Public:UpdateEvStat()
{
	ee_stri = "";
	z_ee_stri = "";
	
	if(stev_time > 0)
	{
		new ee_ustri[128];
		format(ee_ustri, sizeof(ee_ustri), "~g~~h~%s ~w~~h~startuje za ~y~~h~%d sekund!~n~Aby dolaczyc wpisz ~r~~h~%s", stev_name, stev_time, stev_cmd);
		TextDrawSetString(TextDrawEventStart, ee_ustri);
		TextDrawShowForAll(TextDrawEventStart);
		
		stev_time--;
		if(stev_time == 0)
		{
			TextDrawHideForAll(TextDrawEventStart);
		}
	} 
	if(statsUpdate++ > 5)
	{
		statsUpdate = 0;
	 
		#if defined _derby   
			 
			if(script_dd[statees] == true)
				format(z_ee_stri, sizeof(z_ee_stri), "~r~Trwa ~y~%d~w~os", Iter_Count(d_d_players));
			else if(Iter_Count(d_d_players) >= d_d_start_players)
				format(z_ee_stri, sizeof(z_ee_stri), "~y~%d/%d", Iter_Count(d_d_players), script_dd_aren[script_dd[arena]][loades]);
			else
				format(z_ee_stri, sizeof(z_ee_stri), "%d/%d", Iter_Count(d_d_players), d_d_start_players);
			//strcat(ee_stri, "~n~/dd: ");
			strcat(ee_stri, z_ee_stri);
			strcat(ee_stri, "~n~");
		#endif
		
		#if defined _hay  
			
			if(script_hy[statees] == true)
				format(z_ee_stri, sizeof(z_ee_stri), "~r~Trwa ~y~%d~w~os", Iter_Count(h_y_players));
			else if(Iter_Count(h_y_players) >= h_y_start_players)
				format(z_ee_stri, sizeof(z_ee_stri), "~y~%d/%d", Iter_Count(h_y_players), h_y_start_players_max);
			else
				format(z_ee_stri, sizeof(z_ee_stri), "%d/%d", Iter_Count(h_y_players), h_y_start_players);
			//strcat(ee_stri, "~n~/HY: ");
			strcat(ee_stri, z_ee_stri);
			strcat(ee_stri, "~n~");
		#endif
		#if defined _defence  
			
			if(script_DF[statees] == true)
				format(z_ee_stri, sizeof(z_ee_stri), "~r~Trwa ~y~%d~w~os", Iter_Count(d_f_players));
			else if(Iter_Count(d_f_players) >= d_f_start_players)
				format(z_ee_stri, sizeof(z_ee_stri), "~y~%d/%d", Iter_Count(d_f_players), d_f_start_players_max);
			else
				format(z_ee_stri, sizeof(z_ee_stri), "%d/%d", Iter_Count(d_f_players), d_f_start_players);
			//strcat(ee_stri, "~n~/DF: ");
			strcat(ee_stri, z_ee_stri);
			strcat(ee_stri, "~n~");
		#endif
		#if defined _zbb  
			
			if(script_zb[statees] == true)
				format(z_ee_stri, sizeof(z_ee_stri), "~r~Trwa ~y~%d~w~os", Iter_Count(z_b_players));
			else if(Iter_Count(z_b_players) >= z_b_start_players)
				format(z_ee_stri, sizeof(z_ee_stri), "~y~%d/%d", Iter_Count(z_b_players), z_b_start_players_max);
			else
				format(z_ee_stri, sizeof(z_ee_stri), "%d/%d", Iter_Count(z_b_players), z_b_start_players);
			//strcat(ee_stri, "~n~/zb: ");
			strcat(ee_stri, z_ee_stri);
			strcat(ee_stri, "~n~");
		#endif
		#if defined _trr  
			
			if(script_tr[statees] == true)
				format(z_ee_stri, sizeof(z_ee_stri), "~r~Trwa ~y~%d~w~os", Iter_Count(t_r_players));
			else if(Iter_Count(t_r_players) >= t_r_start_players)
				format(z_ee_stri, sizeof(z_ee_stri), "~y~%d/%d", Iter_Count(t_r_players), t_r_start_players_max);
			else
				format(z_ee_stri, sizeof(z_ee_stri), "%d/%d", Iter_Count(t_r_players), t_r_start_players);
			//strcat(ee_stri, "~n~/tr: ");
			strcat(ee_stri, z_ee_stri);
			strcat(ee_stri, "~n~");
		#endif
		#if defined _wg   
			 
			if(script_wg[statees] == true)
				format(z_ee_stri, sizeof(z_ee_stri), "~r~Trwa ~y~%d~w~os", Iter_Count(w_g_players));
			else if(Iter_Count(w_g_players) >= w_g_start_players)
				format(z_ee_stri, sizeof(z_ee_stri), "~y~%d/%d", Iter_Count(w_g_players), w_g_start_players_max);
			else
				format(z_ee_stri, sizeof(z_ee_stri), "%d/%d", Iter_Count(w_g_players), w_g_start_players);
			//strcat(ee_stri, "~n~/WG: ");
			strcat(ee_stri, z_ee_stri);
			strcat(ee_stri, "~n~");
		#endif
		
	 
		#if defined _quest 
		
			if(Quest[started] == true)
				format(z_ee_stri, sizeof(z_ee_stri), "~r~Trwa ~y~%d~w~os", Quest[QPlayers]);
			else if(Quest[PlayersS] >= QUEST_MIN_PLAYERS)
				format(z_ee_stri, sizeof(z_ee_stri), "~y~%d", Quest[PlayersS]);
			else
				format(z_ee_stri, sizeof(z_ee_stri), "%d/%d", Quest[PlayersS], QUEST_MIN_PLAYERS);
			//strcat(ee_stri, "~n~/CTF: ");
			strcat(ee_stri, z_ee_stri);
			strcat(ee_stri, "~n~");
		#endif
	 
		
		#if defined _ch  
			 
			if(script_ch[statees] == true)
				format(z_ee_stri, sizeof(z_ee_stri), "~r~Trwa ~y~%d~w~os", Iter_Count(c_h_players));
			else if(Iter_Count(c_h_players) >= c_h_start_players)
				format(z_ee_stri, sizeof(z_ee_stri), "~y~%d/%d", Iter_Count(c_h_players), c_h_start_players_max);
			else
				format(z_ee_stri, sizeof(z_ee_stri), "%d/%d", Iter_Count(c_h_players), c_h_start_players);
 			strcat(ee_stri, z_ee_stri);
			strcat(ee_stri, "~n~");
		#endif
		
		#if defined _wyscig
			 
			if(script_ws[statees] == true)
				format(z_ee_stri, sizeof(z_ee_stri), "~r~Trwa ~y~%d~w~os", Iter_Count(w_s_players));
			else if(Iter_Count(w_s_players) >= w_s_start_players)
				format(z_ee_stri, sizeof(z_ee_stri), "~y~%d/%d", Iter_Count(w_s_players), script_ws_aren[script_ws[arena]][loades]);
			else
				format(z_ee_stri, sizeof(z_ee_stri), "%d/%d", Iter_Count(w_s_players), w_s_start_players);
		//	strcat(ee_stri, "~n~/ws: ");
			strcat(ee_stri, z_ee_stri);
			strcat(ee_stri, "~n~");
		 
	 
	 		if(script_os[statees] == true)
				format(z_ee_stri, sizeof(z_ee_stri), "~r~Trwa ~y~%d~w~os", Iter_Count(o_s_players));
			else if(Iter_Count(o_s_players) >= o_s_start_players)
				format(z_ee_stri, sizeof(z_ee_stri), "~y~%d/%d", Iter_Count(o_s_players), o_s_start_players_max);
			else
				format(z_ee_stri, sizeof(z_ee_stri), "%d/%d", Iter_Count(o_s_players), o_s_start_players);
			//strcat(ee_stri, "~n~/os: ");
			strcat(ee_stri, z_ee_stri);
			strcat(ee_stri, "~n~");
		#endif
		
		TextDrawSetString(EventTD[0], ee_stri);
	} 
	//TextDrawShowForAll(EventTD[0]);

}

removeIsEvent(remove_id){
	
 
	#if defined _derby
		if(Iter_Contains(d_d_players, remove_id))
		{
			Iter_Remove(d_d_players, remove_id);
			if(script_dd[statees] == true){
				OnPlayerSpawn(remove_id);
			}
			UpdateEvStat();
			return 1;
		}		
	#endif
	#if defined _hay
		if(Iter_Contains(h_y_players, remove_id))
		{
			Iter_Remove(h_y_players, remove_id);
			if(script_hy[statees] == true){
				OnPlayerSpawn(remove_id);
			}
			UpdateEvStat();
			return 1;
		}	
		if(Iter_Contains(o_s_players, remove_id))
		{
			Iter_Remove(o_s_players, remove_id);
			if(script_os[statees] == true){
				OnPlayerSpawn(remove_id);
			}
			UpdateEvStat();
			return 1;
		}				
	#endif
	//#if defined _defence
		if(Iter_Contains(d_f_players, remove_id))
		{
			Iter_Remove(d_f_players, remove_id);
			if(script_DF[statees] == true){
				OnPlayerSpawn(remove_id);
			}
			UpdateEvStat();
			return 1;
		}		
	//#endif
 
	#if defined _zbb
		if(Iter_Contains(z_b_players, remove_id))
		{
			Iter_Remove(z_b_players, remove_id);
			if(script_zb[statees] == true){
				OnPlayerSpawn(remove_id);
			}
			UpdateEvStat();
			return 1;
		}		
	#endif
	#if defined _trr
		if(Iter_Contains(t_r_players, remove_id))
		{
			Iter_Remove(t_r_players, remove_id);
			if(script_tr[statees] == true){
				OnPlayerSpawn(remove_id);
			}
			UpdateEvStat();
			return 1;
		}		
	#endif
	#if defined _wg
		if(Iter_Contains(w_g_players, remove_id))
		{
			Iter_Remove(w_g_players, remove_id);
			if(script_wg[statees] == true){
				OnPlayerSpawn(remove_id);
			}
			UpdateEvStat();
			return 1;
		}		
	#endif
	#if defined _wc
		if(Iter_Contains(w_c_players, remove_id))
		{
			Iter_Remove(w_c_players, remove_id);
			if(script_wc[statees] == true){
				OnPlayerSpawn(remove_id);
			}
			UpdateEvStat();
			return 1;
		}		
	#endif
	#if defined _ctf
		if(CTF[ctf_member][remove_id]){
			CTF[ctf_member][remove_id] = false;
			CTF[ctf_team][remove_id] = 0;
	 
			CTF[ctf_liczba2]--;
			CTF[ctf_liczba]--;
		
			if(CTF[ctf_on] == 1){
				OnPlayerSpawn(remove_id);
			}
			UpdateEvStat();
			return 1;
		}
		
	#endif
	
	#if defined _quest
	
		if(qInfo[remove_id][zapisany])
		{
			FlushPlayerVariables(remove_id);
			if(Quest[started])
			{
				Quest[QPlayers]--;
				RemovePlayerFromQuest(remove_id);
			}
			else
			{
				Quest[PlayersS]--;
			}
			UpdateEvStat();
			return 1;
		}
	
	#endif
 
	#if defined _ch
		if(Iter_Contains(c_h_players, remove_id))
		{
			Iter_Remove(c_h_players, remove_id);
			if(script_ch[statees] == true){
				ResetPlayerWeapons(remove_id);
				OnPlayerSpawn(remove_id);
			}
			UpdateEvStat();
			return 1;
		}		
	#endif
	#if defined _wyscig
		if(Iter_Contains(w_s_players, remove_id))
		{
			Iter_Remove(w_s_players, remove_id);
			if(script_ws[statees] == true){
				OnPlayerSpawn(remove_id);
			}
			UpdateEvStat();
			return 1;
		}		
	#endif
	
 
	return 0;

}

CMD:wypisz(playerid, params [])
{
	if(Iter_Contains(EventPlayers, playerid))
	{
		Iter_Remove(EventPlayers, playerid);
		OnPlayerSpawn(playerid);
		SendClientMessage(playerid, COLOR_ORANGE, "* Wypisa³eœ siê z zapisanego eventu");
	}
	if(ReturnFromEvent(playerid)) return 1;
	if(is_event(playerid, false) == 0) 
		return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} ›››{/b} Nie jesteœ zapisany(a) na ¿aden event!");
	
	new spawnPlayer = is_event(playerid, true);
	removeIsEvent(playerid);
	
	if(spawnPlayer)
		SetPlayerSpawn(playerid);
	SendClientMessage(playerid, COLOR_ORANGE, "* Wypisa³eœ siê z zapisanego eventu");
	 
	return 1;
}
stock is_event(remove_id, bool:event_on = true)
{
	if(Iter_Contains(EventPlayers,remove_id) && !aEData[ev_started] && aEData[ev_lider] != remove_id) return 1;
 	if(Iter_Contains(e1v1_players, remove_id))
	{
		if(event_on == true){
			if(e1v1_status() == 1){
					return 1;
			}
		} else return 1;
	}	
	#if defined _derby
		if(Iter_Contains(d_d_players, remove_id))
		{
			if(event_on == true){
				if(script_dd[statees] == true){
					return 1;
				}
			} else return 1;
		}		
	#endif
	//#if defined _defence
		if(Iter_Contains(d_f_players, remove_id))
		{
			if(event_on == true){ 
				if(script_DF[statees] == true){
					return 1;
				}
			} else return 1;
		}		
	//#endif
	#if defined _hay
		if(Iter_Contains(h_y_players, remove_id))
		{
			if(event_on == true){
				if(script_hy[statees] == true){
					return 1;
				}
			} else return 1;
		}	

		if(Iter_Contains(o_s_players, remove_id))
		{
			if(event_on == true){
				if(script_os[statees] == true){
					return 1;
				}
			} else return 1;
		}			
	#endif
	#if defined _zbb 
		if(Iter_Contains(z_b_players, remove_id))
		{
			if(event_on == true){
				if(script_zb[statees] == true){
					return 1;
				}
			} else return 1;
		}		
	#endif
	#if defined _trr
		if(Iter_Contains(t_r_players, remove_id))
		{
			if(event_on == true){
				if(script_tr[statees] == true){
					return 1;
				}
			} else return 1;
		}		
	#endif
	#if defined _wg
		if(Iter_Contains(w_g_players, remove_id))
		{
			if(event_on == true){
				if(script_wg[statees] == true){
					return 1;
				}
			} else return 1;
		}		
	#endif
	#if defined _wc
		if(Iter_Contains(w_c_players, remove_id))
		{
			 
			if(event_on == true){
				if(script_wc[statees] == true){
					return 1;
				}
			} else return 1;
		}		
	#endif
	#if defined _ctf
		if(CTF[ctf_member][remove_id]){
			if(event_on == true){
				if(CTF[ctf_on] == 1){
					return 1;
				}
			} else return 1;
		}
		
	#endif
	#if defined _op
		if(Iter_Contains(o_players, remove_id))
		{
			if(event_on == true){
				if(script_op[statees] == true){
					return 1;
				}
			} else return 1;
		}		
	#endif
	#if defined _ch
		if(Iter_Contains(c_h_players, remove_id))
		{
			
			if(event_on == true){
				if(script_ch[statees] == true){
					return 1;
				}
			} else return 1;
		}		
	#endif
	#if defined _drift
		if(Iter_Contains(d_r_players, remove_id))
		{
			if(event_on == true){
				if(script_dr[statees] == true){
					return 1;
				}
			} else return 1;
		}		
	#endif
	#if defined _wyscig
		if(Iter_Contains(w_s_players, remove_id))
		{
			if(event_on == true){
				if(script_ws[statees] == true){
					return 1;
				}
			} else return 1;
		}		
	#endif
	return 0;

}

public OnPlayerEnterRaceCheckpoint(playerid)
{

	if(!script_tr[iswin][playerid] && Iter_Contains(t_r_players, playerid) && script_tr[t_zadanie])
	{
		script_tr[iswin][playerid] = true;
		InfoBox(playerid, "Zaliczono!");
		DisablePlayerRaceCheckpoint(playerid);
		return 1;
	}
		
	#if defined _wyscig
		if(Iter_Contains(w_s_players, playerid) && script_ws[statees] == true)
		{
			script_ws[ply_cp][playerid] ++;
			if(script_ws[ply_cp][playerid] == script_ws_aren[script_ws[arena]][loadcp])
			{
				script_ws[mete_player]++;
				script_ws[off_event] = 30;
				#if defined ADUIO_PLUGIN
				PlayCompleteMissionSound(playerid);
				#endif
				SendClientMessageToAll(-1, ""chat" {008ae6}%s (%d) {/b} dotar³(a) (/WS) na metê wyœcigu na {008ae6}%d{/b} Miejscu", playerNick(playerid),playerid,script_ws[mete_player]);
				Streamer_ToggleIdleUpdate(playerid, 1);
				Streamer_ToggleItemUpdate(playerid, 0, 1);
	
				DisablePlayerRaceCheckpoint(playerid);
				OnPlayerSpawn(playerid);
				 
				if(script_ws[mete_player] == 1)
				{
					SendClientMessageToAll(COLOR_ORANGERED, ""chat" Wyœcig automatycznie zostanie zakoñczony za 30 sekund.");
					GivePlayerMoney(playerid, 20000);
					GivePlayerScore(playerid, 300, "wyœcig");
					
					addPointEvent(playerid, stats_ws);
				}
				else 
				if(script_ws[mete_player] == 2)
				{
					GivePlayerMoney(playerid, 10000);
					GivePlayerScore(playerid, 200, "wyœcig");
					
					addPointEvent(playerid, stats_ws);
				}
				else 
				if(script_ws[mete_player] == 3)
				{
					GivePlayerMoney(playerid, 5000);
					GivePlayerScore(playerid, 150, "wyœcig");
					
					Iter_Clear(w_s_players);
					addPointEvent(playerid, stats_ws);
					
					return 1;
				}
				Iter_Remove(w_s_players, playerid);
				
 			 
			
			}
			else if(script_ws[ply_cp][playerid] == script_ws_aren[script_ws[arena]][loadcp] -1)
			{ 
				SetPlayerRaceCheckpoint(playerid, 1, script_ws_spawn[script_ws[arena]][script_ws[ply_cp][playerid]][pos_cp][0], script_ws_spawn[script_ws[arena]][script_ws[ply_cp][playerid]][pos_cp][1], 
				script_ws_spawn[script_ws[arena]][script_ws[ply_cp][playerid]][pos_cp][2], script_ws_spawn[script_ws[arena]][script_ws[ply_cp][playerid]][pos_cp][0], script_ws_spawn[script_ws[arena]][script_ws[ply_cp][playerid]][pos_cp][1], script_ws_spawn[script_ws[arena]][script_ws[ply_cp][playerid]][pos_cp][2], 10);
			}
			else SetPlayerRaceCheckpoint(playerid, 0, script_ws_spawn[script_ws[arena]][script_ws[ply_cp][playerid]][pos_cp][0], 
			script_ws_spawn[script_ws[arena]][script_ws[ply_cp][playerid]][pos_cp][1], script_ws_spawn[script_ws[arena]][script_ws[ply_cp][playerid]][pos_cp][2], script_ws_spawn[script_ws[arena]][script_ws[ply_cp][playerid] + 1][pos_cp][0], script_ws_spawn[script_ws[arena]][script_ws[ply_cp][playerid] +1][pos_cp][1], script_ws_spawn[script_ws[arena]][script_ws[ply_cp][playerid] +1][pos_cp][2], 10);

		}
	#endif
	
	#if defined _ctf
		if(CTF[ctf_team][playerid] > 0)
		{
			if(CTF[ctf_flag_carry] < 0)
			{
				CTF[ctf_flag_carry]= playerid;
				CTF[ctf_flag_carry_slot] = GetPlayerObjectFreeSlot(playerid);
				SetPlayerAttachedObject(playerid, CTF[ctf_flag_carry_slot], 11245, 5, 0.087999, -0.006000, -0.091000, 1.400007, -77.000030, -160.900085, 0.090000, 0.187998, 0.062999);
				DestroyObject(CTF[ctf_flag]);
				SetPlayerHealth(playerid, 10);

				if(CTF[ctf_team][playerid] == 1)
				{
					for(new x; x <MAX_PLAYERS; x++){
						if(CTF[ctf_team][x] > 0){
							SendClientMessage(x, COLOR_BLUE, "Niebiescy przejmuja flage!");
							DisablePlayerRaceCheckpoint(x);
						}
					}
					SetPlayerRaceCheckpoint (playerid, 2, CTFSpawnpossek[CTF[ctf_arena]][0][0], CTFSpawnpossek[CTF[ctf_arena]][0][1], CTFSpawnpossek[CTF[ctf_arena]][0][2], CTFSpawnpossek[CTF[ctf_arena]][0][0], CTFSpawnpossek[CTF[ctf_arena]][0][1], CTFSpawnpossek[CTF[ctf_arena]][0][2], 2);
				}
				else if(CTF[ctf_team][playerid] == 2)
				{
					for(new x; x <MAX_PLAYERS; x++){
						if(CTF[ctf_team][x] > 0){
							SendClientMessage(x, COLOR_GREEN, "{FFFFFF} ›››{/b} Zieloni przejmuja flage!");

							DisablePlayerRaceCheckpoint(x);
						}
					}
					SetPlayerRaceCheckpoint (playerid, 2, CTFSpawnpossek[CTF[ctf_arena]][1][0], CTFSpawnpossek[CTF[ctf_arena]][1][1], CTFSpawnpossek[CTF[ctf_arena]][1][2], CTFSpawnpossek[CTF[ctf_arena]][1][0], CTFSpawnpossek[CTF[ctf_arena]][1][1], CTFSpawnpossek[CTF[ctf_arena]][1][2], 2);
				}
				return 1;
			}
			else if(CTF[ctf_flag_carry] == playerid)
			{
				RemovePlayerAttachedObject(CTF[ctf_flag_carry], CTF[ctf_flag_carry_slot]);
				SetTimer("RespawnFlaga", 7000, 0);
				CTF[ctf_flag_carry] = -1;
				SetPlayerHealth(playerid, 100);
			
				if(CTF[ctf_team][playerid]== 1){
					CTF[ctf_score][0] ++;
					if(CTF[ctf_score][0] >= CTF_FLAG){
						win_ctf(0);
						return 1;
					}
					
				}else if(CTF[ctf_team][playerid] == 2){
					CTF[ctf_score][1] ++;
					//printf("DEBUG: MR%d:%d", CTF[ctf_score][0], CTF[ctf_score][1]);
					if(CTF[ctf_score][1] >= CTF_FLAG){
						win_ctf(1);
						return 1;
					}
				}
				
				foreach(new x : Player){
					if(CTF[ctf_team][x] > 0){
						DisablePlayerRaceCheckpoint(x);
						SendClientMessage(x, COLOR_INFO, "{FFFFFF} ›››{/b} Respawn Flagi za kilka sekund!");
					}
				}
				
			}
			return 1;
		}
	#endif
	Tir_OnPlayerEnterRaceCheckpoint(playerid);
	return 1;
}
 
  
new e1and1brama;
 
//by mrdrifter
CMD:rapo(playerid, params[]){
    
    RankAdmin(playerid, R_MODERATOR);
    
    GameTextForPlayer(playerid, "~b~Otwieranie", 2500, 5);
    MoveDynamicObject(e1and1brama, 33.9000015, 1577.5999756, 11.8000002, 4);
    return 1;    
}
CMD:rapc(playerid, params[]){
    
    RankAdmin(playerid, R_MODERATOR);
    GameTextForPlayer(playerid, "~b~Zamykanie", 2500, 5);

    MoveDynamicObject(e1and1brama, 33.5000000, 1571.8000488, 11.8000002, 4); 
    return 1;    
}


stock addPointEvent(playerid, event)
{

	pInfo[playerid][player_eventpoints][event]++;
    if(!pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Nie jesteœ zarejestrowany(a) twoje statystyki nie zostaj¹ zapisane.");
	}
	return pInfo[playerid][player_eventpoints][event];
}
 
stock InitEventData()
{

	script_DF[df_Pickup] = CreatePickup(1242, 2, 1503.3359, 1432.3585, 10.1191, 123);
	new Text:lol;
	lol = TextDrawCreate(73.599998, 274.026763, "dupa");
	TextDrawLetterSize(lol, 0.338000, 1.002666);
	
	CTF[ctf_td] = TextDrawCreate(73.599998, 274.026763, "~b~~h~Niebiescy ~w~ - 2/3~n~~g~~h~Zieloni ~w~ - 2/3");
	TextDrawLetterSize(CTF[ctf_td], 0.338000, 1.002666);
	TextDrawAlignment(CTF[ctf_td], 1);
	TextDrawColor(CTF[ctf_td], -1);
	TextDrawSetShadow(CTF[ctf_td], 0);
	TextDrawSetOutline(CTF[ctf_td], 1);
	TextDrawBackgroundColor(CTF[ctf_td], 51);
	TextDrawFont(CTF[ctf_td], 2);
	TextDrawSetProportional(CTF[ctf_td], 1);
		
	CTF[ctf_flag_carry] = -1;

	
	EventTD[0]  = TextDrawCreate(27.999988, 341.973205, "0/2~n~0/2~n~0/6~n~0/3~n~0/2~n~0/2~n~0/3~n~0/2~n~0/2");
	TextDrawLetterSize(EventTD[0],0.199000, 0.897710 );
	TextDrawAlignment(EventTD[0] , 2);
	TextDrawColor(EventTD[0] , -26113);
	TextDrawSetShadow(EventTD[0] , 0);
	TextDrawSetOutline(EventTD[0] , -1);
	TextDrawBackgroundColor(EventTD[0] , 80);
	TextDrawFont(EventTD[0] , 1);
	TextDrawSetProportional(EventTD[0] , 1);

/*
	EventTD[1] = TextDrawCreate(3.999969, 287.920166, "/DD~n~~n~/HY~n~~n~/DF~n~~n~/ZB~n~~n~/TR~n~~n~/WG~n~~n~/ST~n~~n~/CH~n~~n~/WS~n~~n~/OS");
	TextDrawLetterSize(EventTD[1], 0.237999, 0.995199);
	TextDrawAlignment(EventTD[1], 1);
	TextDrawColor(EventTD[1], -1061109505);
	TextDrawSetShadow(EventTD[1], 0);	
	TextDrawSetOutline(EventTD[1], 1);
	TextDrawBackgroundColor(EventTD[1], 51);
	TextDrawFont(EventTD[1], 1);
	TextDrawSetProportional(EventTD[1], 1);
*/


	EventTD[1] = TextDrawCreate(3.111129, 341.973114, "/DD~n~/HY~n~/ZB~n~/TR~n~/WG~n~/ST~n~/CH~n~/WS~n~/OS");
	TextDrawLetterSize(EventTD[1], 0.199000, 0.893000);
	TextDrawAlignment(EventTD[1], 1);
	TextDrawColor(EventTD[1], 1143118335);
	TextDrawSetShadow(EventTD[1], 0);
	TextDrawSetOutline(EventTD[1], -1);
	TextDrawBackgroundColor(EventTD[1], 80);
	TextDrawFont(EventTD[1], 1);
	TextDrawSetProportional(EventTD[1], 1);

/*
	EventTD[0] = TextDrawCreate(21.199968, 290.666839, "/PB~n~/WG~n~/CH~n~/HY~n~/WS~n~/DD~n~/PK~n~/WC~n~/UT~n~/LB~n~/ST~n~/SK");
	TextDrawLetterSize(EventTD[0], 0.237999, 0.995199);
	TextDrawAlignment(EventTD[0], 1);
	TextDrawColor(EventTD[0], -1);
	TextDrawSetShadow(EventTD[0], 0);
	TextDrawSetOutline(EventTD[0], 1);
	TextDrawBackgroundColor(EventTD[0], 51);
	TextDrawFont(EventTD[0], 1);
	TextDrawSetProportional(EventTD[0], 1);
 */
	TextDrawEventStart = TextDrawCreate(323.000000, 339.000000, "~g~~h~Wojna Gangow ~w~~h~startuje za ~y~~h~30 sekund!~n~Aby dolaczyc wpisz ~r~~h~/WG");
	TextDrawAlignment(TextDrawEventStart, 2);
	TextDrawBackgroundColor(TextDrawEventStart, 48);
	TextDrawFont(TextDrawEventStart, 1);
	TextDrawLetterSize(TextDrawEventStart, 0.259999, 1.299998);
	TextDrawColor(TextDrawEventStart, -1);
	TextDrawSetOutline(TextDrawEventStart, 1);
	TextDrawSetProportional(TextDrawEventStart, 1);
	TextDrawSetSelectable(TextDrawEventStart, 0);

/*
	TextDrawEventStart = TextDrawCreate(310.500000, 306.755645, "~g~~h~Chowany ~w~~h~startuje za ~y~~h~10 sekund!~n~Aby dolaczyc wpisz ~r~~h~/CH");
	TextDrawLetterSize(TextDrawEventStart, 0.232500, 1.724444);
	TextDrawAlignment(TextDrawEventStart, 2);
	TextDrawColor(TextDrawEventStart, -1);
	TextDrawSetShadow(TextDrawEventStart, 0);
	TextDrawSetOutline(TextDrawEventStart, 1);
	TextDrawBackgroundColor(TextDrawEventStart, 51);
	TextDrawFont(TextDrawEventStart, 1);
	TextDrawSetProportional(TextDrawEventStart, 1);
*/
	e1and1brama = CreateDynamicObject(974,33.5000000,1571.8000488,11.8000002,0.0000000,0.0000000,86.7500000);
	CreateDynamicObject(14795,1461.1999512,-2193.6999512,1171.5000000,0.0000000,0.0000000,0.0000000); //object(genint3_smashtv) (1)
	CreateDynamicObject(974,1465.6999512,-2165.1999512,1169.0000000,0.0000000,0.0000000,0.0000000); //object(tall_fence) (1)
	CreateDynamicObject(974,1465.6999512,-2165.1000977,1169.0000000,0.0000000,0.0000000,0.0000000); //object(tall_fence) (2)
	CreateDynamicObject(974,1465.6999512,-2165.0000000,1169.0000000,0.0000000,0.0000000,0.0000000); //object(tall_fence) (3)
	CreateDynamicObject(974,1465.6999512,-2164.8999023,1169.0000000,0.0000000,0.0000000,0.0000000); //object(tall_fence) (4)
	CreateDynamicObject(974,1465.6999512,-2164.8000488,1169.0000000,0.0000000,0.0000000,0.0000000); //object(tall_fence) (5)
	CreateDynamicObject(974,1465.6999512,-2164.8000488,1169.3000488,0.0000000,0.0000000,0.0000000); //object(tall_fence) (6)
	CreateDynamicObject(974,1465.6999512,-2164.8999023,1169.3000488,0.0000000,0.0000000,0.0000000); //object(tall_fence) (7)
	CreateDynamicObject(974,1465.6999512,-2165.0000000,1169.3000488,0.0000000,0.0000000,0.0000000); //object(tall_fence) (8)
	CreateDynamicObject(974,1465.6999512,-2165.1000977,1169.3000488,0.0000000,0.0000000,0.0000000); //object(tall_fence) (9)
	CreateDynamicObject(974,1465.9000244,-2164.8000488,1168.4000244,0.0000000,0.0000000,0.0000000); //object(tall_fence) (10)
	CreateDynamicObject(974,1465.9000244,-2164.6999512,1168.4000244,0.0000000,0.0000000,0.0000000); //object(tall_fence) (11)
	CreateDynamicObject(974,1465.9000244,-2164.6000977,1168.4000244,0.0000000,0.0000000,0.0000000); //object(tall_fence) (12)
	CreateDynamicObject(974,1465.9000244,-2164.3999023,1168.4000244,0.0000000,0.0000000,0.0000000); //object(tall_fence) (13)
	CreateDynamicObject(974,1465.9000244,-2164.5000000,1168.4000244,0.0000000,0.0000000,0.0000000); //object(tall_fence) (14)
	CreateDynamicObject(974,1465.9000244,-2164.3999023,1168.4000244,0.0000000,0.0000000,0.0000000); //object(tall_fence) (15)
	CreateDynamicObject(974,1489.4000244,-2165.3000488,1174.4000244,0.0000000,0.0000000,0.0000000); //object(tall_fence) (16)
	CreateDynamicObject(974,1489.4000244,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (17)
	CreateDynamicObject(974,1484.5000000,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (18)
	CreateDynamicObject(974,1484.5000000,-2165.2998047,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (19)
	CreateDynamicObject(974,1478.1999512,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (20)
	CreateDynamicObject(974,1471.5000000,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (21)
	CreateDynamicObject(974,1471.5000000,-2165.2998047,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (22)
	CreateDynamicObject(974,1465.0999756,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (23)
	CreateDynamicObject(974,1458.4000244,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (24)
	CreateDynamicObject(974,1458.3994141,-2165.2998047,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (25)
	CreateDynamicObject(974,1452.4000244,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (26)
	CreateDynamicObject(974,1445.8000488,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (27)
	CreateDynamicObject(974,1439.5000000,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (28)
	CreateDynamicObject(974,1433.0000000,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (29)
	CreateDynamicObject(974,1430.5000000,-2168.3999023,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (30)
	CreateDynamicObject(974,1430.5000000,-2174.6999512,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (31)
	CreateDynamicObject(974,1430.5000000,-2181.0000000,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (32)
	CreateDynamicObject(974,1430.5000000,-2187.3000488,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (33)
	CreateDynamicObject(974,1430.5000000,-2193.8000488,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (34)
	CreateDynamicObject(974,1430.5000000,-2200.1999512,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (38)
	CreateDynamicObject(974,1430.5000000,-2206.6000977,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (35)
	CreateDynamicObject(974,1430.5000000,-2213.3000488,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (36)
	CreateDynamicObject(974,1430.5000000,-2219.5000000,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (37)
	CreateDynamicObject(974,1433.4000244,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (39)
	CreateDynamicObject(974,1439.1999512,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (40)
	CreateDynamicObject(974,1445.0000000,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (41)
	CreateDynamicObject(974,1451.5999756,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (42)
	CreateDynamicObject(974,1458.0999756,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (43)
	CreateDynamicObject(974,1463.8000488,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (44)
	CreateDynamicObject(974,1470.0999756,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (45)
	CreateDynamicObject(974,1476.1999512,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (46)
	CreateDynamicObject(974,1482.5000000,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (47)
	CreateDynamicObject(974,1488.8000488,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (48)
	CreateDynamicObject(974,1492.0000000,-2219.5000000,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (49)
	CreateDynamicObject(974,1492.0000000,-2213.0000000,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (50)
	CreateDynamicObject(974,1492.0000000,-2206.6999512,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (51)
	CreateDynamicObject(974,1492.0000000,-2200.6999512,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (52)
	CreateDynamicObject(974,1492.0000000,-2194.1999512,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (53)
	CreateDynamicObject(974,1492.0000000,-2188.1999512,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (54)
	CreateDynamicObject(974,1492.0000000,-2182.1999512,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (55)
	CreateDynamicObject(974,1492.0000000,-2176.1999512,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (56)
	CreateDynamicObject(974,1492.0000000,-2169.6000977,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (57)
	CreateDynamicObject(974,1492.0000000,-2167.6000977,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (58)
	CreateDynamicObject(974,1492.9000244,-2222.1000977,1168.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (60)
	CreateDynamicObject(974,1492.9000244,-2222.1000977,1169.5000000,0.0000000,0.0000000,0.0000000); //object(tall_fence) (61)
	CreateDynamicObject(16637,21.2000008,1576.5999756,13.3000002,0.0000000,0.0000000,84.0000000); //object(ghostgardoor) (1)
	CreateDynamicObject(16637,24.8999996,1576.1999512,13.3000002,0.0000000,0.0000000,83.9959717); //object(ghostgardoor) (2)
	CreateDynamicObject(16637,17.3999996,1577.0000000,13.3000002,0.0000000,0.0000000,83.9959717); //object(ghostgardoor) (3)
	CreateDynamicObject(16637,28.6000004,1575.8000488,13.3000002,0.0000000,0.0000000,83.9959717); //object(ghostgardoor) (4)
	CreateDynamicObject(16637,31.8999996,1575.5000000,13.3000002,0.0000000,0.0000000,83.9959717); //object(ghostgardoor) (5)
	CreateDynamicObject(16637,13.6000004,1577.4000244,13.3000002,0.0000000,0.0000000,83.9959717); //object(ghostgardoor) (6)
	CreateDynamicObject(16637,9.8999996,1577.8000488,13.3000002,0.0000000,0.0000000,83.9959717); //object(ghostgardoor) (7)
	CreateDynamicObject(16385,50.2999992,1559.0000000,11.8000002,0.0000000,0.0000000,357.0000000); //object(desh2_weefact2_) (1)
	CreateDynamicObject(991,48.4000015,1570.9000244,13.0000000,0.0000000,0.0000000,88.0000000); //object(bar_barriergate1) (1)
	CreateDynamicObject(991,48.4000015,1570.9000244,14.0000000,0.0000000,0.0000000,87.9949951); //object(bar_barriergate1) (2)
	CreateDynamicObject(16500,18.3999996,1548.9000244,13.6999998,0.0000000,0.0000000,54.0000000); //object(cn2_savgardr1_) (1)
	CreateDynamicObject(16775,15.1000004,1515.5000000,15.6999998,0.0000000,0.0000000,183.9999847); //object(door_savhangr2) (1)
	CreateDynamicObject(16775,25.3999996,1522.5999756,15.6999998,0.0000000,0.0000000,245.0000000); //object(door_savhangr2) (2)
	CreateDynamicObject(16775,4.9000001,1521.6999512,15.6999998,0.0000000,0.0000000,113.9999695); //object(door_savhangr2) (3)
	CreateDynamicObject(16775,26.7999992,1536.1999512,15.6999998,0.0000000,0.0000000,282.9951172); //object(door_savhangr2) (4)
	CreateDynamicObject(16775,2.9000001,1535.5999756,15.6999998,0.0000000,0.0000000,81.9996338); //object(door_savhangr2) (5)
	CreateDynamicObject(16775,10.1000004,1546.5999756,15.6999998,0.0000000,0.0000000,30.9913330); //object(door_savhangr2) (6)
	CreateDynamicObject(16500,18.3999996,1548.9000244,17.7000008,0.0000000,0.0000000,53.9978027); //object(cn2_savgardr1_) (4)
	CreateDynamicObject(1491,24.2999992,1544.5999756,11.8000002,0.0000000,0.0000000,308.0000000); //object(gen_doorint01) (1)
	CreateDynamicObject(16500,22.2999992,1546.0999756,13.6999998,0.0000000,0.0000000,53.9978027); //object(cn2_savgardr1_) (5)
	CreateDynamicObject(16500,22.2999992,1546.0999756,17.7000008,0.0000000,0.0000000,53.9978027); //object(cn2_savgardr1_) (6)
	CreateDynamicObject(1967,24.2999992,1544.5999756,15.8000002,0.0000000,0.0000000,34.7500000); //object(imcmptrkdrr_las) (1)
	CreateDynamicObject(1967,24.2999992,1544.5999756,18.2000008,0.0000000,0.0000000,34.7497559); //object(imcmptrkdrr_las) (2)
	CreateDynamicObject(974,33.9000015,1577.5999756,11.8000002,0.0000000,0.0000000,86.7500000); //object(tall_fence) (59)



	CreateObject(14795,1461.1999512,-2193.6999512,1171.5000000,0.0000000,0.0000000,0.0000000); //object(genint3_smashtv) (1)
	CreateObject(974,1465.6999512,-2165.1999512,1169.0000000,0.0000000,0.0000000,0.0000000); //object(tall_fence) (1)
	CreateObject(974,1465.6999512,-2165.1000977,1169.0000000,0.0000000,0.0000000,0.0000000); //object(tall_fence) (2)
	CreateObject(974,1465.6999512,-2165.0000000,1169.0000000,0.0000000,0.0000000,0.0000000); //object(tall_fence) (3)
	CreateObject(974,1465.6999512,-2164.8999023,1169.0000000,0.0000000,0.0000000,0.0000000); //object(tall_fence) (4)
	CreateObject(974,1465.6999512,-2164.8000488,1169.0000000,0.0000000,0.0000000,0.0000000); //object(tall_fence) (5)
	CreateObject(974,1465.6999512,-2164.8000488,1169.3000488,0.0000000,0.0000000,0.0000000); //object(tall_fence) (6)
	CreateObject(974,1465.6999512,-2164.8999023,1169.3000488,0.0000000,0.0000000,0.0000000); //object(tall_fence) (7)
	CreateObject(974,1465.6999512,-2165.0000000,1169.3000488,0.0000000,0.0000000,0.0000000); //object(tall_fence) (8)
	CreateObject(974,1465.6999512,-2165.1000977,1169.3000488,0.0000000,0.0000000,0.0000000); //object(tall_fence) (9)
	CreateObject(974,1465.9000244,-2164.8000488,1168.4000244,0.0000000,0.0000000,0.0000000); //object(tall_fence) (10)
	CreateObject(974,1465.9000244,-2164.6999512,1168.4000244,0.0000000,0.0000000,0.0000000); //object(tall_fence) (11)
	CreateObject(974,1465.9000244,-2164.6000977,1168.4000244,0.0000000,0.0000000,0.0000000); //object(tall_fence) (12)
	CreateObject(974,1465.9000244,-2164.3999023,1168.4000244,0.0000000,0.0000000,0.0000000); //object(tall_fence) (13)
	CreateObject(974,1465.9000244,-2164.5000000,1168.4000244,0.0000000,0.0000000,0.0000000); //object(tall_fence) (14)
	CreateObject(974,1465.9000244,-2164.3999023,1168.4000244,0.0000000,0.0000000,0.0000000); //object(tall_fence) (15)
	CreateObject(974,1489.4000244,-2165.3000488,1174.4000244,0.0000000,0.0000000,0.0000000); //object(tall_fence) (16)
	CreateObject(974,1489.4000244,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (17)
	CreateObject(974,1484.5000000,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (18)
	CreateObject(974,1484.5000000,-2165.2998047,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (19)
	CreateObject(974,1478.1999512,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (20)
	CreateObject(974,1471.5000000,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (21)
	CreateObject(974,1471.5000000,-2165.2998047,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (22)
	CreateObject(974,1465.0999756,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (23)
	CreateObject(974,1458.4000244,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (24)
	CreateObject(974,1458.3994141,-2165.2998047,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (25)
	CreateObject(974,1452.4000244,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (26)
	CreateObject(974,1445.8000488,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (27)
	CreateObject(974,1439.5000000,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (28)
	CreateObject(974,1433.0000000,-2165.3000488,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (29)
	CreateObject(974,1430.5000000,-2168.3999023,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (30)
	CreateObject(974,1430.5000000,-2174.6999512,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (31)
	CreateObject(974,1430.5000000,-2181.0000000,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (32)
	CreateObject(974,1430.5000000,-2187.3000488,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (33)
	CreateObject(974,1430.5000000,-2193.8000488,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (34)
	CreateObject(974,1430.5000000,-2200.1999512,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (38)
	CreateObject(974,1430.5000000,-2206.6000977,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (35)
	CreateObject(974,1430.5000000,-2213.3000488,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (36)
	CreateObject(974,1430.5000000,-2219.5000000,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (37)
	CreateObject(974,1433.4000244,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (39)
	CreateObject(974,1439.1999512,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (40)
	CreateObject(974,1445.0000000,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (41)
	CreateObject(974,1451.5999756,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (42)
	CreateObject(974,1458.0999756,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (43)
	CreateObject(974,1463.8000488,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (44)
	CreateObject(974,1470.0999756,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (45)
	CreateObject(974,1476.1999512,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (46)
	CreateObject(974,1482.5000000,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (47)
	CreateObject(974,1488.8000488,-2222.1000977,1176.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (48)
	CreateObject(974,1492.0000000,-2219.5000000,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (49)
	CreateObject(974,1492.0000000,-2213.0000000,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (50)
	CreateObject(974,1492.0000000,-2206.6999512,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (51)
	CreateObject(974,1492.0000000,-2200.6999512,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (52)
	CreateObject(974,1492.0000000,-2194.1999512,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (53)
	CreateObject(974,1492.0000000,-2188.1999512,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (54)
	CreateObject(974,1492.0000000,-2182.1999512,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (55)
	CreateObject(974,1492.0000000,-2176.1999512,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (56)
	CreateObject(974,1492.0000000,-2169.6000977,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (57)
	CreateObject(974,1492.0000000,-2167.6000977,1176.6999512,0.0000000,0.0000000,90.0000000); //object(tall_fence) (58)
	CreateObject(974,1492.9000244,-2222.1000977,1168.6999512,0.0000000,0.0000000,0.0000000); //object(tall_fence) (60)
	CreateObject(974,1492.9000244,-2222.1000977,1169.5000000,0.0000000,0.0000000,0.0000000); //object(tall_fence) (61)

	CreateObject(14404, 1891.504150, -8159.505371, 3.197141, 0.0000, 0.0000, 0.0000);
	CreateObject(14405, 1891.563843, -8159.571777, 2.037500, 0.0000, 0.0000, 0.0000);
	CreateObject(14405, 1891.538452, -8170.821777, 2.037498, 0.0000, 0.0000, 0.0000);
	CreateObject(14405, 1891.552856, -8169.589844, 2.056684, 0.0000, 0.0000, 0.0000);
	CreateObject(14405, 1891.562378, -8168.301270, 2.043864, 0.0000, 0.0000, 0.0000);
	CreateObject(14405, 1891.554321, -8167.053711, 2.050836, 0.0000, 0.0000, 0.0000);
	CreateObject(14405, 1891.568481, -8165.810547, 2.056400, 0.0000, 0.0000, 0.0000);
	CreateObject(14405, 1891.559570, -8164.451660, 2.065336, 0.0000, 0.0000, 0.0000);
	CreateObject(1518, 1892.578003, -8158.128906, 3.474201, 0.0000, 0.0000, 0.0000);
	CreateObject(1518, 1890.467773, -8158.104004, 3.466745, 0.0000, 0.0000, 0.0000);
	CreateObject(1523, 1890.730835, -8155.586426, 1.459633, 0.0000, 0.0000, 0.0000);
	CreateObject(1796, 1890.952271, -8166.693359, 1.418374, 0.0000, 0.0000, 268.8998);
	CreateObject(955, 1890.441895, -8167.008301, 1.850188, 0.0000, 0.0000, 90.0000);
	CreateObject(1649, 1891.415771, -8153.192383, 3.096034, 0.0000, 0.0000, 0.0000);
	CreateObject(2406, 1890.376221, -8164.333984, 4.256859, 18.9076, 91.9597, 91.7189);
	CreateObject(2404, 1890.386719, -8161.762695, 4.292717, 15.4699, 90.2409, 91.6415);
	CreateObject(2405, 1890.479004, -8159.889160, 4.294949, 0.8594, 91.9597, 83.9066);
	CreateObject(1742, 1889.848511, -8157.031738, 1.442635, 0.0000, 0.0000, 90.0000);
	
	//BUS
	CreateDynamicObject(1257, 1756.30005, -1813.59998, 13.8, 0, 0, 74);
	CreateDynamicObject(1257, -1981.5, 181.89999, 28, 0, 0, 0);
	CreateDynamicObject(1257, 2212.19995, 964.70001, 11.4, 0, 0, 272);

	//minigun 
	/*
	CreateDynamicObject(13749, -1054.3447265625, -646.1650390625, 38.171485900879, 0.000000, 0.000000, 65.549926757813); //
	CreateDynamicObject(986, -1034.2436523438, -588.34155273438, 31.0078125, 0.000000, 0.000000, 358.75); //
	CreateDynamicObject(986, -1042.4031982422, -588.05310058594, 31.0078125, 0.000000, 0.000000, 358.23254394531); //
	CreateDynamicObject(4602, -992.57434082031, -640.62060546875, 102.11827087402, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(6295, -1009.4197998047, -679.49755859375, 54.940200805664, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(3620, -1006.32421875, -693.79901123047, 80.23819732666, 335.83996582031, 359.95495605469, 15.5); //
	CreateDynamicObject(7980, -1027.1905517578, -651.87231445313, 32.994777679443, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(7980, -1024.8337402344, -624.16271972656, 32.994777679443, 0.000000, 0.000000, 89.820007324219); //
	CreateDynamicObject(13648, -1091.42578125, -656.63067626953, 56.620193481445, 0.000000, 0.000000, 93.295013427734); //
	CreateDynamicObject(13648, -1091.4030761719, -657.30596923828, 56.620193481445, 0.000000, 0.000000, 93.290405273438); //
	CreateDynamicObject(16302, -1092.8508300781, -620.72003173828, 49.308448791504, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(5463, -1087.5103759766, -675.63830566406, 76.92106628418, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(4882, -1076.6485595703, -737.04193115234, 63.100799560547, 0.000000, 0.000000, 321.23999023438); //
	CreateDynamicObject(4882, -1029.8232421875, -735.3544921875, 62.625801086426, 0.000000, 0.000000, 329.20080566406); //
	CreateDynamicObject(12839, -1077.9112548828, -659.50122070313, 60.86217880249, 0.000000, 0.000000, 271.83499145508); //
	CreateDynamicObject(13011, -1080.2276611328, -664.61981201172, 64.039085388184, 0.000000, 0.000000, 268.68997192383); //
	CreateDynamicObject(13011, -1080.2275390625, -664.619140625, 69.114074707031, 0.000000, 0.000000, 268.68713378906); //
	CreateDynamicObject(13011, -1080.2275390625, -664.619140625, 74.114074707031, 0.000000, 0.000000, 268.68713378906); //
	CreateDynamicObject(13011, -1080.2275390625, -664.619140625, 79.064025878906, 0.000000, 0.000000, 268.68713378906); //
	CreateDynamicObject(13011, -1080.2275390625, -664.619140625, 84.089042663574, 0.000000, 0.000000, 268.68713378906); //
	CreateDynamicObject(1471, -1081.9666748047, -664.59216308594, 82.03311920166, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(1471, -1081.9658203125, -664.591796875, 77.033088684082, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(1471, -1081.9658203125, -664.591796875, 72.033103942871, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(1471, -1081.9658203125, -664.591796875, 67.033042907715, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(2960, -1056.0544433594, -621.74353027344, 134.58570861816, 0.000000, 0.000000, 87.340026855469); //
	CreateDynamicObject(2960, -1056.2156982422, -626.26940917969, 134.58570861816, 0.000000, 0.000000, 87.335815429688); //
	CreateDynamicObject(2960, -1056.4266357422, -630.79113769531, 134.58570861816, 0.000000, 0.000000, 87.335815429688); //
	CreateDynamicObject(3502, -1081.1881103516, -671.83062744141, 88.802833557129, 356.0299987793, 0.000000, 20.064025878906); //
	CreateDynamicObject(7950, -1055.6904296875, -735.32421875, 45.549583435059, 13.892211914063, 1.9830322265625, 334.67651367188); //
	CreateDynamicObject(11495, -1070.8193359375, -666.2021484375, 95.157852172852, 47.433471679688, 355.02868652344, 292.24182128906);
	CreateDynamicObject(11495, -1057.052734375, -660.5732421875, 111.35787963867, 47.433471679688, 355.02319335938, 292.24182128906);
	CreateDynamicObject(11495, -1029.5972900391, -649.37298583984, 143.75267028809, 47.433471679688, 355.02868652344, 292.24182128906);
	CreateDynamicObject(11495, -1002.1229248047, -638.14868164063, 174.80763244629, 27.581085205078, 355.02319335938, 292.24182128906);
	*/
	//solo 
	CreateDynamicObject(13599, -1309.6640625, 77.796051025391, 1003.2754516602, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(13599, -1486.8074951172, 81.269966125488, 1048.6348876953, 0.000000, 181.00500488281, 0.000000); //
	CreateDynamicObject(13607, -1273.1549072266, 121.2758026123, 1018.4644165039, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(13607, -1274.2530517578, 38.995250701904, 1018.4644165039, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(13607, -1370.5073242188, 35.150814056396, 1018.4644165039, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(13607, -1373.345703125, 121.2646484375, 1018.5593261719, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(13607, -1472.3677978516, 115.43854522705, 1018.4644165039, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(13607, -1478.7532958984, 31.060604095459, 1018.4644165039, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(13623, -1373.3422851563, 121.10623931885, 1028.5892333984, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(13623, -1370.2102050781, 35.354625701904, 1028.5892333984, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(13623, -1274.2877197266, 38.952285766602, 1028.5892333984, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(13623, -1273.2330322266, 121.20650482178, 1028.5892333984, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(13623, -1472.3218994141, 115.45101928711, 1028.5892333984, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(13623, -1478.6864013672, 30.988784790039, 1028.5892333984, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(3578, -1473.7280273438, -12.558610916138, 1037.4328613281, 0.000000, 89.780029296875, 97.625); //
	CreateDynamicObject(3578, -1362.9593505859, 167.09585571289, 1037.4328613281, 0.000000, 89.769287109375, 248.5693359375); //
	CreateDynamicObject(3578, -1366.3482666016, 168.15478515625, 1037.4328613281, 0.000000, 89.763793945313, 248.56567382813); //
	CreateDynamicObject(3578, -1369.4500732422, 169.12390136719, 1037.4328613281, 0.000000, 89.763793945313, 248.56567382813); //
	CreateDynamicObject(3578, -1358.5167236328, -6.3772945404053, 1037.4328613281, 1, 89.763793945313, 92.02587890625); //
	CreateDynamicObject(3578, -1363.4140625, -7.3790645599365, 1037.4328613281, 23.820007324219, 89.75830078125, 92.021484375); //
	CreateDynamicObject(3578, -1367.6986083984, -8.2557563781738, 1037.2076416016, 334.193359375, 89.752807617188, 92.021484375); //
	CreateDynamicObject(3578, -1272.1108398438, -10.502489089966, 1037.4328613281, 23.818359375, 89.752807617188, 92.021484375); //
	CreateDynamicObject(3578, -1275.9918212891, -11.091917037964, 1037.4328613281, 155.2333984375, 89.752807617188, 92.021484375); //
	CreateDynamicObject(3578, -1264.5635986328, 166.72087097168, 1037.4328613281, 155.23132324219, 89.747314453125, 263.40649414063); //
	CreateDynamicObject(3578, -1269.2299804688, 167.60987854004, 1037.4328613281, 209.00085449219, 89.747314453125, 263.40270996094); //
	CreateDynamicObject(3578, -1258.9140625, 165.6438293457, 1037.4328613281, 179.22338867188, 89.747314453125, 263.40270996094); //
	CreateDynamicObject(3578, -1478.830078125, 161.90385437012, 1037.4328613281, 0.000000, 89.774780273438, 276.62994384766); //
	CreateDynamicObject(3578, -1475.1510009766, 162.78115844727, 1037.4328613281, 0.000000, 89.769287109375, 276.62475585938); //
	CreateDynamicObject(13607, -1373.345703125, 121.2646484375, 1008.9582519531, 180.63500976563, 0.000000, 0.000000); //
	CreateDynamicObject(13607, -1370.2966308594, 35.410255432129, 1008.6079101563, 180.63171386719, 0.000000, 0.000000); //
	CreateDynamicObject(13607, -1478.8203125, 31.263660430908, 1008.6079101563, 180.63171386719, 0.000000, 0.000000); //
	CreateDynamicObject(13607, -1472.3784179688, 115.46207427979, 1008.6079101563, 180.63171386719, 0.000000, 0.000000); //
	CreateDynamicObject(13607, -1273.1754150391, 121.40467834473, 1008.6079101563, 180.63171386719, 0.000000, 0.000000); //
	CreateDynamicObject(13607, -1274.2294921875, 39.042327880859, 1008.4327392578, 180.63171386719, 0.000000, 0.000000); //
	
	// labirynt
	CreateDynamicObject(2935, 1130.6676025391, 1351.8959960938, 11.272232055664, 0, 0, 1.9849853515625);
	CreateDynamicObject(2935, 1130.974609375, 1344.734375, 11.272232055664, 0, 0, 1.9830322265625);
	CreateDynamicObject(2935, 1130.0234375, 1329.16015625, 11.272232055664, 0, 0, 93.290405273438);
	CreateDynamicObject(2935, 1135.3402099609, 1327.4732666016, 11.272232055664, 0, 0, 1.9767150878906);
	CreateDynamicObject(2935, 1124.3046875, 1341.470703125, 11.272232055664, 0, 0, 1.9720458984375);
	CreateDynamicObject(2935, 1119.1271972656, 1343.4956054688, 11.272232055664, 0, 0, 91.301727294922);
	CreateDynamicObject(2935, 1108.1859130859, 1355.8107910156, 11.272232055664, 0, 0, 91.301727294922);
	CreateDynamicObject(2935, 1130.3421630859, 1359.0383300781, 11.272232055664, 0, 0, 1.9830322265625);
	CreateDynamicObject(2935, 1122.6195068359, 1350.8549804688, 11.272232055664, 0, 0, 91.308044433594);
	CreateDynamicObject(2935, 1115.4226074219, 1350.7299804688, 11.272232055664, 0, 0, 90.808044433594);
	CreateDynamicObject(2935, 1110.3636474609, 1350.6859130859, 11.272232055664, 0, 0, 182.11755371094);
	CreateDynamicObject(2935, 1110.7700195313, 1343.6958007813, 11.272232055664, 0, 0, 182.11486816406);
	CreateDynamicObject(2935, 1111.171875, 1336.3916015625, 11.272232055664, 0, 0, 182.58178710938);
	CreateDynamicObject(2935, 1123.4718017578, 1336.2750244141, 11.197217941284, 0, 0, 272.85046386719);
	CreateDynamicObject(2935, 1124.3702392578, 1355.8470458984, 11.272232055664, 0, 0, 1.2666015625);
	CreateDynamicObject(2935, 1119.349609375, 1357.794921875, 11.272232055664, 0, 0, 271.84020996094);
	CreateDynamicObject(2935, 1102.1037597656, 1347.1190185547, 11.272232055664, 0, 0, 91.29638671875);
	CreateDynamicObject(2935, 1102.3104248047, 1340.4577636719, 11.272232055664, 0, 0, 91.29638671875);
	CreateDynamicObject(2935, 1106.263671875, 1334.1162109375, 11.272232055664, 0, 0, 92.537841796875);
	CreateDynamicObject(2935, 1121.697265625, 1330.9814453125, 11.197217941284, 0, 0, 3.3837890625);
	CreateDynamicObject(2935, 1145.8540039063, 1327.6290283203, 11.272232055664, 0, 0, 1.9720458984375);
	CreateDynamicObject(2935, 1147.7854003906, 1332.9241943359, 11.172233581543, 0, 0, 92.097045898438);
	CreateDynamicObject(2935, 1152.8466796875, 1335.1630859375, 11.172233581543, 0, 0, 181.41723632813);
	CreateDynamicObject(2935, 1154.0321044922, 1352.4732666016, 11.172233581543, 0, 0, 270.96710205078);
	CreateDynamicObject(2935, 1146.9072265625, 1352.3232421875, 11.172233581543, 0, 0, 270.96130371094);
	CreateDynamicObject(2935, 1145.7928466797, 1337.6651611328, 11.172233581543, 0, 0, 358.57653808594);
	CreateDynamicObject(2935, 1145.7919921875, 1337.6650390625, 11.172233581543, 0, 0, 358.57177734375);
	CreateDynamicObject(2935, 1142.6000976563, 1342.1566162109, 11.172233581543, 0, 0, 182.64245605469);
	CreateDynamicObject(2935, 1137.0224609375, 1332.6904296875, 11.172233581543, 0, 0, 91.373291015625);
	CreateDynamicObject(2935, 1151.080078125, 1342.8161621094, 11.172233581543, 0, 0, 271.28723144531);
	CreateDynamicObject(2935, 1152.3466796875, 1324.1591796875, 11.172233581543, 0, 0, 181.41174316406);
	CreateDynamicObject(2935, 1144.06640625, 1322.494140625, 11.172233581543, 0, 0, 271.92211914063);
	CreateDynamicObject(2935, 1135.6938476563, 1320.3422851563, 11.172233581543, 0, 0, 3.2264404296875);
	CreateDynamicObject(2935, 1128.359375, 1323.8984375, 11.172233581543, 0, 0, 3.218994140625);
	CreateDynamicObject(2935, 1104.2835693359, 1328.9320068359, 11.272232055664, 0, 0, 180.06335449219);
	CreateDynamicObject(2935, 1102.3432617188, 1323.5751953125, 11.272232055664, 0, 0, 271.60534667969);
	CreateDynamicObject(2935, 1113.6154785156, 1323.8190917969, 11.272232055664, 0, 0, 271.60400390625);
	CreateDynamicObject(2935, 1122.1141357422, 1323.7144775391, 11.272232055664, 0, 0, 182.27905273438);
	CreateDynamicObject(2935, 1115.8775634766, 1318.8695068359, 11.272232055664, 0, 0, 182.27416992188);
	CreateDynamicObject(2935, 1126.7027587891, 1318.7047119141, 11.172233581543, 0, 0, 270.72793579102);
	CreateDynamicObject(2935, 1132.7414550781, 1339.6733398438, 11.272232055664, 0, 0, 272.41040039063);
	CreateDynamicObject(2935, 1104.517578125, 1318.51953125, 11.272232055664, 0, 0, 182.26867675781);
	CreateDynamicObject(2935, 1106.5614013672, 1313.4114990234, 11.272232055664, 0, 0, 271.59906005859);
	CreateDynamicObject(2935, 1117.9757080078, 1313.9437255859, 11.272232055664, 0, 0, 271.59851074219);
	CreateDynamicObject(2935, 1141.5822753906, 1354.0266113281, 11.172233581543, 0, 0, 2.450927734375);
	CreateDynamicObject(2935, 1132.3869628906, 1353.86328125, 11.172233581543, 0, 0, 271.88488769531);
	CreateDynamicObject(2935, 1123.353515625, 1313.4619140625, 11.272232055664, 0, 0, 3.0377197265625);
	CreateDynamicObject(2935, 1128.5404052734, 1311.6000976563, 11.272232055664, 0, 0, 92.362731933594);
	CreateDynamicObject(2935, 1137.9422607422, 1315.2397460938, 11.272232055664, 0, 0, 92.362060546875);
	CreateDynamicObject(2935, 1151.1713867188, 1315.4583740234, 11.272232055664, 0, 0, 92.362060546875);
	CreateDynamicObject(2935, 1139.9718017578, 1310.3360595703, 11.272232055664, 0, 0, 182.23706054688);
	CreateDynamicObject(2935, 1146.2719726563, 1313.3770751953, 11.272232055664, 0, 0, 182.23571777344);
	CreateDynamicObject(2935, 1142.033203125, 1305.208984375, 11.272232055664, 0, 0, 272.54333496094);
	CreateDynamicObject(2935, 1149.5953369141, 1307.3377685547, 11.272232055664, 0, 0, 2.867431640625);
	CreateDynamicObject(2935, 1157.4143066406, 1326.341796875, 11.172233581543, 0, 0, 270.73608398438);
	CreateDynamicObject(2935, 1156.3509521484, 1310.7384033203, 11.172233581543, 0, 0, 0.81591796875);
	CreateDynamicObject(2935, 1130.8518066406, 1306.767578125, 11.272232055664, 0, 0, 2.867431640625);
	CreateDynamicObject(2935, 1117.5712890625, 1306.0009765625, 11.272232055664, 0, 0, 2.846923828125);
	CreateDynamicObject(2935, 1122.7877197266, 1304.2496337891, 11.272232055664, 0, 0, 92.685485839844);
	CreateDynamicObject(2935, 1112.8900146484, 1303.8046875, 11.247228622437, 0, 0, 272.30053710938);
	CreateDynamicObject(2935, 1110.7100830078, 1301.6921386719, 11.272232055664, 0, 0, 2.2557373046875);
	CreateDynamicObject(2935, 1104.7014160156, 1308.4488525391, 11.272232055664, 0, 0, 2.501708984375);
	CreateDynamicObject(2935, 1102.3134765625, 1301.5327148438, 11.272232055664, 0, 0, 271.92437744141);
	CreateDynamicObject(2935, 1130.9411621094, 1303.3022460938, 11.272232055664, 0, 0, 2.8619384765625);
	CreateDynamicObject(2935, 1114.5623779297, 1332.4392089844, 11.272232055664, 0, 0, 182.58178710938);
	CreateDynamicObject(2935, 1110.6568603516, 1311.5872802734, 11.272232055664, 0, 0, 2.9078369140625);
	CreateDynamicObject(2935, 1158.0258789063, 1333.1899414063, 11.172233581543, 0, 0, 270.73608398438);
	CreateDynamicObject(2935, 1163.275390625, 1335.2786865234, 11.172233581543, 0, 0, 180.39617919922);
	CreateDynamicObject(2935, 1171.3840332031, 1341.7587890625, 11.172233581543, 0, 0, 179.1455078125);
	CreateDynamicObject(2935, 1171.291015625, 1326.65625, 11.172233581543, 0, 0, 179.13757324219);
	CreateDynamicObject(2935, 1162.7292480469, 1324.3828125, 11.172233581543, 0, 0, 180.64306640625);
	CreateDynamicObject(2935, 1172.7102050781, 1321.3707275391, 11.172233581543, 0, 0, 269.96704101563);
	CreateDynamicObject(2935, 1158.4985351563, 1315.8835449219, 11.172233581543, 0, 0, 269.96704101563);
	CreateDynamicObject(2935, 1169.7670898438, 1316.0266113281, 11.172233581543, 0, 0, 1.2763671875);
	CreateDynamicObject(2935, 1169.9229736328, 1308.7406005859, 11.172233581543, 0, 0, 1.2744140625);
	CreateDynamicObject(2935, 1163.8000488281, 1313.8581542969, 11.172233581543, 0, 0, 1.2744140625);
	CreateDynamicObject(2935, 1158.4473876953, 1305.5712890625, 11.172233581543, 0, 0, 90.779418945313);
	CreateDynamicObject(2935, 1165.8566894531, 1303.4130859375, 11.172233581543, 0, 0, 90.774536132813);
	CreateDynamicObject(2935, 1149.9776611328, 1300.1497802734, 11.272232055664, 0, 0, 3.1326904296875);
	CreateDynamicObject(2935, 1144.9083251953, 1297.9377441406, 11.272232055664, 0, 0, 272.54333496094);
	CreateDynamicObject(2935, 1137.7446289063, 1297.6179199219, 11.272232055664, 0, 0, 272.54333496094);
	CreateDynamicObject(2935, 1130.4895019531, 1298.2375488281, 11.272232055664, 0, 0, 272.54333496094);
	CreateDynamicObject(2935, 1112.9356689453, 1296.6744384766, 11.272232055664, 0, 0, 272.54333496094);
	CreateDynamicObject(2935, 1105.7915039063, 1296.3825683594, 11.272232055664, 0, 0, 272.54333496094);
	CreateDynamicObject(2935, 1103.9484863281, 1291.2821044922, 11.272232055664, 0, 0, 2.3430786132813);
	CreateDynamicObject(2935, 1104.1984863281, 1284.1014404297, 11.272232055664, 0, 0, 2.340087890625);
	CreateDynamicObject(2935, 1104.4879150391, 1276.8839111328, 11.272232055664, 0, 0, 2.340087890625);
	CreateDynamicObject(2935, 1109.5322265625, 1275.1723632813, 11.272232055664, 0, 0, 272.44006347656);
	CreateDynamicObject(2935, 1121.3000488281, 1291.5537109375, 11.272232055664, 0, 0, 272.43896484375);
	CreateDynamicObject(2935, 1128.9190673828, 1276.0755615234, 11.272232055664, 0, 0, 272.43896484375);
	CreateDynamicObject(2935, 1116.8729248047, 1268.9896240234, 11.272232055664, 0, 0, 272.43896484375);
	CreateDynamicObject(2935, 1109.6784667969, 1268.6782226563, 11.272232055664, 0, 0, 272.43896484375);
	CreateDynamicObject(2935, 1102.4373779297, 1268.3992919922, 11.272232055664, 0, 0, 271.93896484375);
	CreateDynamicObject(2935, 1114.1342773438, 1291.203125, 11.272232055664, 0, 0, 272.43896484375);
	CreateDynamicObject(2935, 1109.0787353516, 1285.3931884766, 11.272232055664, 0, 0, 272.43896484375);
	CreateDynamicObject(2935, 1119.6007080078, 1285.7943115234, 11.272232055664, 0, 0, 272.43896484375);
	CreateDynamicObject(2935, 1126.7653808594, 1289.7540283203, 11.272232055664, 0, 0, 182.97906494141);
	CreateDynamicObject(2935, 1126.65234375, 1281.0874023438, 11.272232055664, 0, 0, 182.97729492188);
	CreateDynamicObject(2935, 1112.0704345703, 1280.5985107422, 11.272232055664, 0, 0, 272.48217773438);
	CreateDynamicObject(2935, 1116.8898925781, 1275.5034179688, 11.272232055664, 0, 0, 272.47741699219);
	CreateDynamicObject(2935, 1119.2924804688, 1280.8840332031, 11.272232055664, 0, 0, 272.47741699219);
	CreateDynamicObject(2935, 1131.6307373047, 1283.3170166016, 11.272232055664, 0, 0, 272.47741699219);
	CreateDynamicObject(2935, 1136.0909423828, 1276.4641113281, 11.272232055664, 0, 0, 272.47741699219);
	CreateDynamicObject(2935, 1139.4514160156, 1281.7795410156, 11.272232055664, 0, 0, 3.4820556640625);
	CreateDynamicObject(2935, 1133.1876220703, 1292.2716064453, 11.272232055664, 0, 0, 3.4771728515625);
	CreateDynamicObject(2935, 1138.5782470703, 1289.7491455078, 11.272232055664, 0, 0, 93.262176513672);
	CreateDynamicObject(2935, 1147.6376953125, 1292.8757324219, 11.272232055664, 0, 0, 182.60247802734);
	CreateDynamicObject(2935, 1148.0861816406, 1282.0755615234, 11.272232055664, 0, 0, 182.59826660156);
	CreateDynamicObject(2935, 1138.4439697266, 1271.4395751953, 11.272232055664, 0, 0, 182.59826660156);
	CreateDynamicObject(2935, 1153.0921630859, 1291.1003417969, 11.272232055664, 0, 0, 93.798248291016);
	CreateDynamicObject(2935, 1153.3037109375, 1284.3225097656, 11.272232055664, 0, 0, 93.295776367188);
	CreateDynamicObject(2935, 1162.5112304688, 1286.4692382813, 11.272232055664, 0, 0, 183.48541259766);
	CreateDynamicObject(2935, 1162.0692138672, 1293.6759033203, 11.272232055664, 0, 0, 183.48266601563);
	CreateDynamicObject(2935, 1156.7005615234, 1300.5329589844, 11.272232055664, 0, 0, 181.48266601563);
	CreateDynamicObject(2935, 1148.8491210938, 1272.0178222656, 11.272232055664, 0, 0, 2.6929321289063);
	CreateDynamicObject(2935, 1153.5539550781, 1277.392578125, 11.272232055664, 0, 1.75, 92.886657714844);
	CreateDynamicObject(2935, 1154.4855957031, 1270.2503662109, 11.272232055664, 0, 0, 92.528747558594);
	CreateDynamicObject(2935, 1161.6644287109, 1270.5777587891, 11.272232055664, 0, 0, 92.52685546875);
	CreateDynamicObject(2935, 1163.5423583984, 1275.9002685547, 11.272232055664, 0, 0, 182.03686523438);
	CreateDynamicObject(2935, 1164.859375, 1281.2847900391, 11.272232055664, 0, 0, 273.83239746094);
	CreateDynamicObject(2935, 1123.9929199219, 1269.3090820313, 11.272232055664, 0, 0, 272.43896484375);
	CreateDynamicObject(2935, 1131.1723632813, 1269.642578125, 11.272232055664, 0, 0, 272.43896484375);
	CreateDynamicObject(2935, 1133.5864257813, 1264.6456298828, 11.272232055664, 0, 0, 2.994140625);
	CreateDynamicObject(2935, 1138.8729248047, 1262.8347167969, 11.272232055664, 0, 0, 92.833801269531);
	CreateDynamicObject(2935, 1146.0968017578, 1263.1689453125, 11.272232055664, 0, 0, 92.648986816406);
	CreateDynamicObject(2935, 1151.1345214844, 1265.1195068359, 11.272232055664, 0, 0, 182.59271240234);
	CreateDynamicObject(2935, 1167.0899658203, 1295.9385986328, 11.272232055664, 0, 0, 272.41760253906);
	CreateDynamicObject(2935, 1169.4265136719, 1290.9020996094, 11.272232055664, 0, 0, 2.0718383789063);
	CreateDynamicObject(2935, 1170.2711181641, 1279.7366943359, 11.272232055664, 0, 0, 3.5709228515625);
	CreateDynamicObject(2935, 1170.7307128906, 1272.5004882813, 11.272232055664, 0, 0, 3.570556640625);
	CreateDynamicObject(2935, 1170.6719970703, 1263.9294433594, 11.272232055664, 0, 358.01501464844, 92.030578613281);
	CreateDynamicObject(2935, 1163.5382080078, 1263.6506347656, 11.272232055664, 0, 358.01147460938, 92.026977539063);
	CreateDynamicObject(2935, 1158.4272460938, 1261.3818359375, 11.272232055664, 0, 358.01147460938, 183.33703613281);
	CreateDynamicObject(2935, 1174.6346435547, 1258.8740234375, 11.272232055664, 0, 358.01147460938, 182.35198974609);
	CreateDynamicObject(2935, 1158.8425292969, 1254.2502441406, 11.272232055664, 0, 358.01147460938, 183.33435058594);
	CreateDynamicObject(2935, 1151.5623779297, 1257.9100341797, 11.272232055664, 0, 358.01147460938, 183.33435058594);
	CreateDynamicObject(2935, 1151.9914550781, 1250.7409667969, 11.272232055664, 0, 358.01147460938, 183.33435058594);
	CreateDynamicObject(2935, 1161.0512695313, 1248.875, 11.272232055664, 0, 358.01147460938, 271.85424804688);
	CreateDynamicObject(2935, 1147.0600585938, 1248.4122314453, 11.272232055664, 0, 358.01147460938, 272.35119628906);
	CreateDynamicObject(2935, 1145.3571777344, 1243.2614746094, 11.272232055664, 0, 358.01147460938, 2.2613525390625);
	CreateDynamicObject(2935, 1147.5067138672, 1238.0709228516, 11.272232055664, 0, 358.01147460938, 91.582702636719);
	CreateDynamicObject(2935, 1154.7406005859, 1238.2661132813, 11.272232055664, 0, 358.01147460938, 91.58203125);
	CreateDynamicObject(2935, 1161.9226074219, 1238.4692382813, 11.272232055664, 0, 358.01147460938, 91.58203125);
	CreateDynamicObject(2935, 1163.580078125, 1243.783203125, 11.272232055664, 0, 358.01147460938, 181.65704345703);
	CreateDynamicObject(8210, 1125.1065673828, 1362.6666259766, 12.862020492554, 0, 0, 0);
	CreateDynamicObject(8210, 1098.2349853516, 1334.7160644531, 12.862020492554, 0, 0, 90.045013427734);
	CreateDynamicObject(8210, 1098.2178955078, 1279.2438964844, 12.862020492554, 0, 0, 90.0439453125);
	CreateDynamicObject(8210, 1176.5612792969, 1317.4401855469, 12.862020492554, 0, 0, 270.09387207031);
	CreateDynamicObject(8210, 1176.6618652344, 1261.8002929688, 12.862020492554, 0, 0, 270.09338378906);
	CreateDynamicObject(8210, 1173.0123291016, 1317.8265380859, 13.162019729614, 89.530029296875, 0, 269.84338378906);
	CreateDynamicObject(8210, 1164.162109375, 1317.8875732422, 13.387016296387, 89.527587890625, 0, 269.84069824219);
	CreateDynamicObject(8210, 1155.3023681641, 1317.3204345703, 13.387016296387, 89.527587890625, 0, 269.84069824219);
	CreateDynamicObject(8210, 1146.3553466797, 1317.2684326172, 13.387016296387, 89.527587890625, 0, 269.84069824219);
	CreateDynamicObject(8210, 1137.4168701172, 1317.4167480469, 13.387016296387, 89.527587890625, 0, 269.84069824219);
	CreateDynamicObject(8210, 1128.5068359375, 1317.6838378906, 13.387016296387, 89.527587890625, 0, 269.84069824219);
	CreateDynamicObject(8210, 1119.6306152344, 1317.697265625, 13.387016296387, 89.527587890625, 0, 269.84069824219);
	CreateDynamicObject(8210, 1110.7281494141, 1317.7095947266, 13.387016296387, 89.527587890625, 0, 269.84069824219);
	CreateDynamicObject(8210, 1103.5187988281, 1317.6652832031, 13.387016296387, 89.527587890625, 0, 269.84069824219);
	CreateDynamicObject(8210, 1126.6407470703, 1359.1820068359, 13.387016296387, 89.527587890625, 0, 359.9150390625);
	CreateDynamicObject(8210, 1126.4736328125, 1350.4973144531, 13.387016296387, 89.522094726563, 0, 359.912109375);
	CreateDynamicObject(8210, 1126.5693359375, 1286.5830078125, 13.387016296387, 89.522094726563, 0, 359.912109375);
	CreateDynamicObject(8210, 1126.4530029297, 1277.7274169922, 13.387016296387, 89.522094726563, 0, 359.912109375);
	CreateDynamicObject(8210, 1126.4207763672, 1268.7730712891, 13.287017822266, 89.522094726563, 0, 359.912109375);
	CreateDynamicObject(8210, 1157.3531494141, 1262.1767578125, 13.437015533447, 89.522094726563, 358.01501464844, 91.956420898438);
	CreateDynamicObject(8210, 1166.2464599609, 1262.2025146484, 13.437015533447, 89.5166015625, 358.01147460938, 91.95556640625);
	CreateDynamicObject(8210, 1170.8836669922, 1262.7801513672, 13.437015533447, 89.5166015625, 358.01147460938, 92.45556640625);
	CreateDynamicObject(8210, 1148.7265625, 1261.6923828125, 13.437015533447, 89.511108398438, 358.01147460938, 92.455444335938);
	CreateDynamicObject(969, 1154.1966552734, 1354.2972412109, 13.070320129395, 89.763793945313, 0.000000, 89.480590820313); //
	CreateDynamicObject(969, 1154.2724609375, 1345.1744384766, 13.070320129395, 89.765014648438, 0, 90.735015869141);
	
	//obiekty od /dt
	
	CreateDynamicObject(10771, -3504.2033691406, 1302.7453613281, 4.8450541496277, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(10771, -3430.1333007813, 1302.736328125, 4.8250036239624, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(10770, -3522.267578125, 1295.0230712891, 37.957389831543, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(10770, -3465.421875, 1295.0545654297, 37.932479858398, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(11237, -3519.6340332031, 1295.2952880859, 37.939331054688, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(11145, -3567.037109375, 1303.1910400391, 3.6300020217896, 0.000000, 0.000000, 0.4547119140625); //
	CreateDynamicObject(11146, -3513.1787109375, 1303.322265625, 11.680879592896, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(1682, -3462.5732421875, 1297.27734375, 35.886379241943, 0.000000, 0.000000, 330.49499511719); //
	CreateDynamicObject(3114, -3395.5798339844, 1295.3189697266, 16.055572509766, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(10772, -3502.9626464844, 1302.6827392578, 16.652696609497, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(10772, -3430.072265625, 1302.5607910156, 16.677696228027, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(3115, -3603.2104492188, 1302.7017822266, 9.2967758178711, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(3114, -3561.0280761719, 1317.3721923828, 9.0476732254028, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(3055, -3396.8039550781, 1316.7593994141, 11.375801086426, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(3055, -3407.3591308594, 1288.8436279297, 11.375801086426, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(2944, -3533.2790527344, 1299.0515136719, 2.9810998439789, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(2944, -3458.0803222656, 1300.5207519531, 18.108764648438, 0.000000, 0.000000, 269.39001464844); //
	CreateDynamicObject(2944, -3514.8972167969, 1300.4605712891, 18.108764648438, 0.000000, 0.000000, 269.64999389648); //
	CreateDynamicObject(2944, -3533.2722167969, 1298.0255126953, 2.9810998439789, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(8613, -3597.9392089844, 1308.1197509766, 13.249565124512, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(8613, -3554.5986328125, 1317.1508789063, 13.249565124512, 0.000000, 0.000000, 270.67504882813); //
	CreateDynamicObject(3115, -3560.2431640625, 1297.8765869141, 22.472982406616, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(12839, -3571.3098144531, 1293.603515625, 20.060266494751, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(3115, -3584.2509765625, 1297.7958984375, 22.472982406616, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(12839, -3573.1945800781, 1302.7395019531, 20.060266494751, 0.000000, 0.000000, 179.58502197266); //
	CreateDynamicObject(16092, -3583.4631347656, 1289.4490966797, 14.464084625244, 0.000000, 0.000000, 90.345031738281); //
	CreateDynamicObject(16092, -3560.8200683594, 1289.3856201172, 14.464084625244, 0.000000, 0.000000, 90.340576171875); //
	CreateDynamicObject(971, -3572.2392578125, 1298.3311767578, 22.689601898193, 89.900024414063, 0.000000, 0.000000); //
	CreateDynamicObject(3115, -3422.3186035156, 1290.7448730469, 22.472982406616, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(3115, -3393.533203125, 1290.9387207031, 22.472982406616, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(3115, -3363.76953125, 1290.9732666016, 22.472982406616, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(16092, -3419.7687988281, 1288.1164550781, 14.464084625244, 0.000000, 0.000000, 269.53558349609); //
	CreateDynamicObject(16092, -3393.9836425781, 1288.1293945313, 14.464084625244, 0.000000, 0.000000, 271.14044189453); //
	CreateDynamicObject(16092, -3361.4604492188, 1288.7434082031, 14.414085388184, 0.000000, 0.000000, 90.985473632813); //
	CreateDynamicObject(971, -3407.6831054688, 1290.9040527344, 22.689601898193, 89.895629882813, 0.000000, 0.000000); //
	CreateDynamicObject(971, -3378.5832519531, 1292.5854492188, 22.689601898193, 89.895629882813, 0.000000, 0.000000); //
	CreateDynamicObject(12839, -3404.6147460938, 1286.5556640625, 20.035266876221, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(12839, -3374.8190917969, 1289.1439208984, 20.035266876221, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(12839, -3382.498046875, 1295.8186035156, 20.035266876221, 0.000000, 0.000000, 179.75); //
	CreateDynamicObject(12839, -3411.2856445313, 1295.7449951172, 20.035266876221, 0.000000, 0.000000, 179.74731445313); //
	CreateDynamicObject(16192, -3123.1584472656, 1772.6313476563, -5.950569152832, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(16207, -3155.3679199219, 1616.2087402344, 5.4891662597656, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(3605, -3147.1560058594, 1733.1114501953, 42.230735778809, 0.000000, 0.000000, 312.08999633789); //
	CreateDynamicObject(3641, -3109.7739257813, 1708.7252197266, 40.513687133789, 0.000000, 0.000000, 338.16500854492); //
	CreateDynamicObject(5520, -3105.8383789063, 1667.2703857422, 53.195892333984, 0.000000, 0.000000, 268.68994140625); //
	CreateDynamicObject(5986, -3107.525390625, 1762.8669433594, 54.646537780762, 0.000000, 0.000000, 338.1650390625); //
	CreateDynamicObject(6522, -3096.2829589844, 1646.6672363281, 51.502136230469, 0.000000, 0.000000, 7.9400024414063); //
	CreateDynamicObject(7885, -3096.3251953125, 1621.3010253906, 33.67338180542, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(3113, -3078.6882324219, 1591.8601074219, 33.629833221436, 0.000000, 285.08499145508, 0.000000); //
	CreateDynamicObject(3113, -3089.9497070313, 1592.2095947266, 33.629833221436, 0.000000, 285.08422851563, 0.000000); //
	CreateDynamicObject(3113, -3101.0004882813, 1594.4887695313, 33.629833221436, 0.000000, 285.08422851563, 0.000000); //
	CreateDynamicObject(3113, -3112.1303710938, 1594.4655761719, 33.629833221436, 0.000000, 285.08422851563, 0.000000); //
	CreateDynamicObject(3113, -3085.8776855469, 1609.8967285156, 33.629833221436, 0.000000, 285.08422851563, 89.325012207031); //
	CreateDynamicObject(3113, -3108.1069335938, 1611.875, 33.604831695557, 0.000000, 285.08422851563, 89.324340820313); //
	CreateDynamicObject(3279, -3130.5495605469, 1704.9627685547, 36.854732513428, 0.000000, 0.000000, 247.91497802734); //
	CreateDynamicObject(3279, -3132.4833984375, 1705.7633056641, 52.374729156494, 0.000000, 0.000000, 336.47137451172); //
	CreateDynamicObject(3279, -3097.5893554688, 1686.5799560547, 33.819774627686, 0.000000, 0.000000, 270.96276855469); //
	CreateDynamicObject(3279, -3120.2568359375, 1685.9371337891, 34.819774627686, 0.000000, 3.9700012207031, 282.87121582031); //
	CreateDynamicObject(3279, -3112.8723144531, 1590.8802490234, 33.594745635986, 0.000000, 3.966064453125, 275.12048339844); //
	CreateDynamicObject(3279, -3110.8403320313, 1592.9494628906, 49.594776153564, 0.000000, 3.966064453125, 275.11962890625); //
	CreateDynamicObject(8615, -3123.9689941406, 1786.4890136719, 59.349922180176, 0.000000, 0.000000, 248.13497924805); //
	CreateDynamicObject(10009, -3119.0393066406, 1757.720703125, 38.121337890625, 0.000000, 0.000000, 65.330017089844); //
	CreateDynamicObject(5020, -3109.6081542969, 1768.6875, 50.150093078613, 0.000000, 0.000000, 281.58499145508); //
	CreateDynamicObject(5020, -3114.7023925781, 1769.5675048828, 47.500144958496, 0.000000, 0.000000, 247.84979248047); //
	CreateDynamicObject(5020, -3120.5444335938, 1771.9243164063, 47.500144958496, 0.000000, 0.000000, 247.84606933594); //
	CreateDynamicObject(5020, -3126.373046875, 1774.3243408203, 47.500144958496, 0.000000, 0.000000, 247.84606933594); //
	CreateDynamicObject(5020, -3127.7299804688, 1774.8950195313, 47.500144958496, 0.000000, 0.000000, 247.84606933594); //
	CreateDynamicObject(5020, -3129.0747070313, 1778.6424560547, 47.475143432617, 0.000000, 0.000000, 156.53607177734); //
	CreateDynamicObject(3037, -3120.8618164063, 1785.6333007813, 61.399921417236, 0.25, 268.95498657227, 338.16500854492); //
	CreateDynamicObject(3277, -3094.0866699219, 1765.1198730469, 74.392127990723, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(3277, -3094.1254882813, 1765.1583251953, 72.492149353027, 0.000000, 0.000000, 0.000000); //
	CreateDynamicObject(982, -3107.4475097656, 1605.9365234375, 41.106922149658, 22.304992675781, 270.95498657227, 0.000000); //
	CreateDynamicObject(982, -3128.2861328125, 1614.4490966797, 29.081930160522, 24.522247314453, 272.93530273438, 233.79498291016); //
	CreateDynamicObject(982, -3128.9321289063, 1613.2813720703, 28.931932449341, 24.521484375, 272.93334960938, 233.79455566406); //
	CreateDynamicObject(982, -3113.7351074219, 1764.7249755859, 46.232234954834, 325.97500610352, 271.18997192383, 67.490020751953); //
	CreateDynamicObject(982, -3114.1220703125, 1763.6101074219, 46.232234954834, 325.96984863281, 271.1865234375, 67.489013671875); //
	CreateDynamicObject(16133, -3149.3940429688, 1689.1546630859, 15.75329208374, 0.000000, 0.000000, 338.1591796875); //
	CreateDynamicObject(16133, -3152.1811523438, 1686.2193603516, 4.7532920837402, 0.000000, 306.4049987793, 350.07458496094); //
	CreateDynamicObject(16133, -3153.5466308594, 1683.7797851563, -7.4967079162598, 0.000000, 306.40319824219, 350.07385253906); //
	CreateDynamicObject(16133, -3152.5844726563, 1688.8833007813, 14.75329208374, 0.000000, 0.000000, 338.1591796875); //
 //arena gang
	CreateDynamicObject(4106, -28.45738, 2256.07617, 119.8243, 0, 0, 78.75);
	CreateDynamicObject(4106, -29.22698, 2252.17725, 119.82968, 0, 0, -101.25);
	CreateDynamicObject(2790, -59.64593, 2259.59473, 120.53958, 117.743, 0, -101.25);
	CreateDynamicObject(2790, -61.73703, 2260.00244, 119.39381, 117.743, 0, -101.25);
	CreateDynamicObject(2790, -59.76674, 2258.84912, 120.52126, 117.743, 0, -101.25);
	CreateDynamicObject(2790, -62.38736, 2259.37085, 119.12058, 117.743, 0, -101.25);
	CreateDynamicObject(11496, -4.85489, 2252.28589, 116.90974, 0, 0, -281.25);
	CreateDynamicObject(11496, -5.84553, 2247.40137, 116.89033, 0, 0, -461.25);
	CreateDynamicObject(11496, -21.51687, 2250.53442, 116.89025, 0, 0, -461.25);
	CreateDynamicObject(11496, -20.53172, 2255.40894, 116.89025, 0, 0, -281.25);
	CreateDynamicObject(11496, -37.18818, 2253.65381, 116.89016, 0, 0, -461.25);
	CreateDynamicObject(11496, -36.21091, 2258.53052, 116.89021, 0, 0, -281.25);
	CreateDynamicObject(11496, -52.86597, 2256.76856, 116.87514, 0, 0, -461.25);
	CreateDynamicObject(11496, -51.90058, 2261.64673, 116.88867, 0, 0, -281.25);
	CreateDynamicObject(2789, -62.56345, 2256.72315, 116.95972, 90.241, 0, -101.25);
	CreateDynamicObject(2789, -61.54149, 2261.82544, 116.95981, 90.241, 0, -101.25);
	CreateDynamicObject(3578, 6.25688, 2247.18237, 123.23832, 0, 0, 78.75);
	CreateDynamicObject(3578, 5.35075, 2255.70557, 121.88458, 0, 0, 46.719);
	CreateDynamicObject(3578, 12.40981, 2263.19092, 121.87702, 0, 0, 46.719);
	CreateDynamicObject(3578, -0.15186, 2241.00269, 121.95289, 0, 0, 79.609);
	CreateDynamicObject(3578, -68.27567, 2261.05054, 121.2164, 0, 0, 78.75);
	CreateDynamicObject(3578, -64.83968, 2251.91162, 119.36121, 0, 2.578, 68.437);
	CreateDynamicObject(3578, -59.29515, 2267.4353, 118.64912, 0, 2.578, 71.797);
	CreateDynamicObject(3578, -57.97251, 2271.44873, 118.48215, 0, 2.578, 71.797);
	CreateDynamicObject(3578, -0.91424, 2236.92944, 121.93312, 0, 0, 79.609);
	CreateDynamicObject(944, -58.54416, 2264.70679, 117.97346, 0, 0, 71.875);
	CreateDynamicObject(944, -12.36075, 2255.94775, 117.97504, 0, 0, 78.75);
	CreateDynamicObject(1685, -17.93713, 2249.79272, 117.84025, 0, 0, -33.75);
	CreateDynamicObject(3631, -43.33184, 2258.02539, 117.6685, 0, 0, -123.75);
	CreateDynamicObject(1431, -0.76829, 2244.15186, 117.63794, 0, 0, -101.25);
	CreateDynamicObject(1421, -38.30127, 2253.3501, 117.85272, 0, 0, 101.25);
	CreateDynamicObject(1762, -18.35554, 2257.13574, 117.09808, 0, 0, -135);
	CreateDynamicObject(1769, -19.30499, 2255.97559, 117.09123, 0, 0, -78.75);
	CreateDynamicObject(2094, -8.96045, 2248.89087, 117.0891, 0, 0, -112.5);
	CreateDynamicObject(1685, -50.10568, 2261.5669, 117.83867, 0, 0, 56.25);
	CreateDynamicObject(1368, -28.48724, 2254.40674, 117.77998, 0, 0, 78.75);
	CreateDynamicObject(1368, -29.19441, 2254.5564, 117.77989, 0, 0, -101.25);
	CreateDynamicObject(1454, -36.24336, 2259.34912, 117.88841, 0, 0, -22.5);
	CreateDynamicObject(11496, -186.0546, 2301.21924, 102.66021, 0, 0, 76.172);
	CreateDynamicObject(11496, -187.23871, 2296.3855, 102.67063, 0, 0, 256.172);
	CreateDynamicObject(14416, -195.01622, 2306.01636, 99.63988, 0, 0, -103.828);
	CreateDynamicObject(14416, -195.92984, 2302.31787, 99.6542, 0, 0, -103.828);
	CreateDynamicObject(14416, -196.87051, 2298.479, 99.6516, 0, 0, -103.828);
	CreateDynamicObject(14416, -197.41067, 2296.23731, 99.65364, 0, 0, -103.828);
	CreateDynamicObject(4106, -150.55664, 2287.87012, 107.63801, 12.03, 0, 256.168);
	CreateDynamicObject(4106, -149.61099, 2291.72656, 107.65362, -12.032, 0, -283.828);
	CreateDynamicObject(11496, -113.56073, 2283.3833, 115.20159, 0, 0, 76.172);
	CreateDynamicObject(11496, -114.74609, 2278.54297, 115.18517, 0, 0, 256.168);
	CreateDynamicObject(14416, -111.60442, 2280.15894, 114.79696, 0, 0, -103.828);
	CreateDynamicObject(2789, -110.19732, 2282.01367, 116.33624, 0, 0, -13.906);
	CreateDynamicObject(2789, -111.20141, 2277.92432, 116.48628, 0, 0, 166.094);
	CreateDynamicObject(2789, -171.53361, 2292.021, 101.88034, 0, 0, 76.172);
	CreateDynamicObject(2789, -127.5582, 2287.5564, 111.33617, 0, 0, -103.828);
	CreateDynamicObject(18368, 66.22677, 2251.50146, 117.56864, 0, 0, 27.734);
	CreateDynamicObject(944, -121.77416, 2278.56812, 116.26996, 0, 0, 67.5);
	CreateDynamicObject(2094, -117.72276, 2284.44995, 115.40037, 0, 0, -33.75);
	CreateDynamicObject(1421, -186.30472, 2294.76953, 103.63319, 0, 0, 101.25);
	CreateDynamicObject(944, -190.28287, 2302.63477, 103.745, 0, 0, 67.5);
	CreateDynamicObject(1685, -182.28325, 2301.54297, 103.61021, 0, 0, 56.25);
	CreateDynamicObject(3572, 49.17594, 2223.8523, 123.89856, 0, 0, 33.75);
	CreateDynamicObject(3799, 33.02564, 2261.74316, 123.0249, 0, 0, 56.25);
	CreateDynamicObject(12930, 23.31533, 2224.91357, 125.04083, 6.016, -9.454, 45);
	CreateDynamicObject(3287, 32.74458, 2247.03784, 130.19379, 0, 0, 0);
	CreateDynamicObject(3425, -120.30795, 2265.34375, 117.03968, -276.738, -110.008, 13.906);
	CreateDynamicObject(2789, -197.46249, 2294.08911, 100.35923, 90.241, 0, -149.688);
	CreateDynamicObject(2789, -196.70401, 2293.93115, 101.37632, 0, 0, -193.906);
	CreateDynamicObject(2789, -194.56729, 2308.09399, 101.34603, 0, 0, -373.906);
	CreateDynamicObject(3578, -201.11185, 2291.00171, 101.02087, 0, 0, 30.312);
	CreateDynamicObject(3578, -193.24451, 2312.55689, 99.25022, 0, 0, 92.733);
	CreateDynamicObject(2789, -194.57912, 2308.08618, 99.88205, 0, 0, -373.906);
	CreateDynamicObject(3578, -108.2488, 2272.31274, 119.40081, 0, 5.157, 90.937);
	CreateDynamicObject(944, -109.3294, 2283.28931, 118.75652, -8.594, 7.735, 97.812);
	CreateDynamicObject(3502, -73.44857, 2282.07495, 121.68625, 10.313, 20.626, -135.859);
	CreateDynamicObject(3865, -80.98199, 2289.68848, 119.05898, -8.594, 0, 45);
	CreateDynamicObject(11486, -105.26919, 2326.86621, 96.0649, 0, 0, 22.5);
	CreateDynamicObject(3279, -216.67654, 2277.22461, 101.60348, 0, 0, 125.469);
	CreateDynamicObject(11496, -219.52478, 2276.146, 101.43689, 0, 0, -54.608);
	CreateDynamicObject(751, -94.65365, 2243.90747, 120.4286, 0, 0, 0);
	CreateDynamicObject(746, -94.73268, 2270.56079, 122.06959, 0, 17.189, 135);
	CreateDynamicObject(3359, -248.62875, 2378.77637, 107.87787, 0, 0, 33.75);
	CreateDynamicObject(2745, -192.77542, 2295.02222, 104.07925, 0, 0, 101.25);
	CreateDynamicObject(1454, -241.2706, 2379.90894, 108.88091, 0, 0, 33.75);
	CreateDynamicObject(1457, -84.60646, 2262.20752, 125.99931, 0, 0, -146.25);
	CreateDynamicObject(3279, 96.84348, 2240.07422, 122.84399, 0, 0, 181.719);
	CreateDynamicObject(1431, 94.84804, 2239.40991, 139.46973, 0, 0, -90);
	CreateDynamicObject(13367, -280.55447, 2139.01147, 122.59917, 0, 0, 0);
	CreateDynamicObject(1457, -292.41113, 2153.66382, 113.2279, 0, 0, 123.75);
	CreateDynamicObject(1483, -254.52451, 2372.98071, 109.52995, 0, 0, 33.75);
	CreateDynamicObject(7981, -302.06445, 2353.72559, 115.31476, 0, 0, 90);
	CreateDynamicObject(1685, -297.30081, 2345.7854, 111.31683, 0, 0, 90);
	CreateDynamicObject(1685, -297.29553, 2348.95386, 111.4417, 0, 0, 90);
	CreateDynamicObject(1685, -297.30576, 2348.94092, 112.9417, 0, 0, 90);
	CreateDynamicObject(922, -280.09024, 2362.39063, 109.82539, 0, 0, -67.5);
	CreateDynamicObject(923, -280.20493, 2345.33569, 109.57309, 0, 0, -22.5);
	CreateDynamicObject(1365, -304.02093, 2336.42627, 111.39681, 0, 0, -180);
	CreateDynamicObject(11093, -245.6187, 2326.22021, 111.26101, 0, 0, -112.5);
	CreateDynamicObject(3287, -259.09265, 2353.00537, 111.8729, 0, 0, 11.25);
	CreateDynamicObject(3631, -241.98019, 2314.11646, 114.58809, 0, 0, -112.5);
	CreateDynamicObject(3399, -251.18895, 2312.3523, 112.0938, 0, 0, -202.5);
	CreateDynamicObject(3271, -280.83984, 2174.16602, 111.35194, 0, 0, 123.745);
	CreateDynamicObject(3799, -262.27832, 2323.74756, 114.0098, 0, 0, 123.75);
	CreateDynamicObject(3572, 88.1759, 2241.12964, 120.8723, 0, 0, 168.75);
	CreateDynamicObject(1225, -84.34077, 2261.60425, 124.74748, 0, 0, 0);
	CreateDynamicObject(3374, 51.32349, 2255.12109, 124.28543, 0, 0, 11.25);
	CreateDynamicObject(16778, -94.43849, 2244.39209, 125.49921, 0, 0, -112.5);
	CreateDynamicObject(3569, -274.28018, 2376.02271, 111.74607, 0, 0, -270);
	CreateDynamicObject(10814, -216.65852, 2340.25659, 109.48126, 15.47, 0, 93.438);
	CreateDynamicObject(13025, -265.98282, 2411.0105, 110.3148, 0, 0, 11.25);
	CreateDynamicObject(16337, -212.87524, 2393.47217, 107.3744, 0, 0, 45);
	CreateDynamicObject(3615, -253.41995, 2226.55957, 110.98059, 0, 0, -108.985);
	CreateDynamicObject(11496, -251.66577, 2223.85376, 108.78673, 0, 0, 251.015);
	CreateDynamicObject(11496, -250.03467, 2228.57153, 108.78706, 0, 0, 71.015);
	CreateDynamicObject(3578, -243.9243, 2223.85669, 109.18701, 0, 0, 70.938);
	CreateDynamicObject(944, -246.36719, 2228.42554, 109.87185, 0, 0, 101.25);
	CreateDynamicObject(8131, -255.92499, 2165.84375, 118.19248, 0, 0, -11.25);
	CreateDynamicObject(8493, -224.02026, 2409.0022, 122.89734, 0, 0, -119.453);
	CreateDynamicObject(11426, -228.48636, 2360.30078, 108.62723, 0, 0, -157.5);
	CreateDynamicObject(11442, -257.32849, 2289.76733, 108.67109, 0, 0, -78.75);
	CreateDynamicObject(11444, -226.56293, 2300.75708, 104.59162, 0, 0, -56.25);
	CreateDynamicObject(11457, -248.69144, 2323.58154, 113.61102, 0, 0, -202.5);
	CreateDynamicObject(14416, -241.90007, 2328.24536, 113.08012, 0, 0, -203.359);
	CreateDynamicObject(944, -236.47476, 2333.09326, 114.89459, 0, 0, 101.25);
	CreateDynamicObject(944, -249.07982, 2323.52344, 117.59737, 0, 0, 135);
	CreateDynamicObject(1421, -245.36508, 2330.40332, 120.45171, 0, 0, 22.5);
	CreateDynamicObject(944, -252.91188, 2262.97485, 108.5211, 0, 0, 157.5);
	CreateDynamicObject(1431, -86.35982, 2277.42114, 122.29134, 6.016, -12.892, -155.781);
	CreateDynamicObject(1346, -76.91817, 2240.71411, 120.65383, -14.61, 0, -146.25);
	CreateDynamicObject(6299, -277.61713, 2357.49512, 110.2419, 0, 0, -123.75);
	CreateDynamicObject(6289, -279.57178, 2316.08008, 110.70169, 0, 0, -146.25);
	CreateDynamicObject(1365, -286.44687, 2391.73218, 110.20632, 0, 0, 0);
	CreateDynamicObject(1358, -286.46808, 2391.67383, 112.56273, 0, 0, 0);
	CreateDynamicObject(1371, -245.36616, 2335.78882, 120.4724, 0, 0, 0);
	CreateDynamicObject(12957, -244.32394, 2359.78027, 109.20809, 0, 0, 0);
	CreateDynamicObject(944, -271.49756, 2195.41333, 111.59154, 0, 0, 191.25);
	CreateDynamicObject(744, 16.41836, 2245.94214, 125.02426, 1.719, -11.173, 0);
	CreateDynamicObject(3256, -302.5549, 2357.57202, 120.57747, 0, 0, -281.25);
	CreateDynamicObject(14409, -236.07848, 2408.7627, 107.4073, 0, 0, -208.516);
	CreateDynamicObject(14409, -256.40588, 2419.64941, 110.87277, 0, 0, -213.673);
	CreateDynamicObject(14409, -218.7346, 2399.92285, 109.13757, 0, 0, -196.329);
	CreateDynamicObject(16093, -276.79999, 2152.19995, 115.8, 0, 0, 158);
	//arena wojen gangu
	
	CreateDynamicObject(10398, -882.06506, 1707.31299, 1363.84705,   0.00000, 0.00000, 3.18000);
	CreateDynamicObject(19340, -856.79059, 1730.06409, 1331.59204,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19340, -767.77795, 1730.07275, 1331.59204,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19340, -945.75037, 1730.12000, 1331.59204,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19340, -945.78632, 1903.81482, 1331.59204,   0.00000, 0.00000, 180.17998);
	CreateDynamicObject(19340, -856.87207, 1903.82092, 1331.59204,   0.00000, 0.00000, 180.17998);
	CreateDynamicObject(19340, -768.08136, 1903.84094, 1331.59204,   0.00000, 0.00000, 180.17998);
	CreateDynamicObject(16121, -1004.08783, 1669.78040, 1335.20361,   0.00000, 0.00000, -20.28000);
	CreateDynamicObject(16121, -1007.10052, 1706.16931, 1335.20361,   0.00000, 0.00000, -20.28000);
	CreateDynamicObject(16121, -1009.08002, 1748.22827, 1335.20361,   0.00000, 0.00000, -20.28000);
	CreateDynamicObject(16121, -1007.80420, 1777.59106, 1335.20361,   0.00000, 0.00000, -20.28000);
	CreateDynamicObject(16121, -1001.12250, 1817.48865, 1335.20361,   0.00000, 0.00000, -20.28000);
	CreateDynamicObject(16121, -1002.07690, 1856.87305, 1335.20361,   0.00000, 0.00000, -20.28000);
	CreateDynamicObject(16121, -978.71234, 1901.51343, 1335.20361,   0.00000, 0.00000, -64.50000);
	CreateDynamicObject(16121, -960.60608, 1936.09119, 1335.20361,   0.00000, 0.00000, -51.05999);
	CreateDynamicObject(16121, -916.86493, 1950.89990, 1335.20361,   0.00000, 0.00000, -118.31998);
	CreateDynamicObject(16121, -877.06750, 1931.48865, 1335.20361,   0.00000, 0.00000, -114.00001);
	CreateDynamicObject(16121, -867.61053, 1965.01990, 1335.20361,   0.00000, 0.00000, -30.42001);
	CreateDynamicObject(16121, -835.73340, 1986.99146, 1335.20361,   0.00000, 0.00000, -102.83999);
	CreateDynamicObject(16121, -806.45349, 1958.72363, 1335.20361,   0.00000, 0.00000, -192.89999);
	CreateDynamicObject(16121, -788.79907, 1931.27490, 1335.20361,   0.00000, 0.00000, -112.91998);
	CreateDynamicObject(16121, -770.63220, 1964.62085, 1335.20361,   0.00000, 0.00000, -28.85999);
	CreateDynamicObject(16121, -746.16058, 1984.68542, 1335.20361,   0.00000, 0.00000, -101.40002);
	CreateDynamicObject(16121, -720.06079, 1955.30688, 1335.20361,   0.00000, 0.00000, -192.36005);
	CreateDynamicObject(16121, -715.00940, 1908.27112, 1335.20361,   0.00000, 0.00000, -206.34003);
	CreateDynamicObject(16121, -715.50031, 1867.63196, 1335.20361,   0.00000, 0.00000, -212.34003);
	CreateDynamicObject(16121, -716.22729, 1822.91321, 1335.20361,   0.00000, 0.00000, -203.52005);
	CreateDynamicObject(16121, -714.52679, 1782.59937, 1335.20361,   0.00000, 0.00000, -203.52005);
	CreateDynamicObject(16121, -715.74426, 1741.28723, 1335.20361,   0.00000, 0.00000, -203.52005);
	CreateDynamicObject(16121, -739.34180, 1719.19751, 1335.20361,   0.00000, 0.00000, -286.32010);
	CreateDynamicObject(16121, -757.00397, 1686.59839, 1335.20361,   0.00000, 0.00000, -206.10011);
	CreateDynamicObject(16121, -790.71588, 1677.24426, 1335.20361,   0.00000, 0.00000, -283.44016);
	CreateDynamicObject(16121, -975.98987, 1685.45398, 1335.20361,   0.00000, 0.00000, 91.62001);
	CreateDynamicObject(16118, -814.68951, 1665.64600, 1342.68994,   0.00000, 0.00000, -107.03999);
	CreateDynamicObject(16118, -782.02155, 1665.79834, 1348.63940,   0.00000, 0.00000, -67.14001);
	CreateDynamicObject(16118, -736.81641, 1706.53076, 1342.68994,   0.00000, 0.00000, 124.85999);
	CreateDynamicObject(16118, -704.14868, 1743.18799, 1342.68994,   0.00000, 0.00000, 155.33995);
	CreateDynamicObject(16118, -707.13672, 1780.07568, 1342.68994,   0.00000, 0.00000, 190.91997);
	CreateDynamicObject(16118, -704.55872, 1825.49280, 1342.68994,   0.00000, 0.00000, 173.81998);
	CreateDynamicObject(16118, -707.48431, 1868.27515, 1342.68994,   0.00000, 0.00000, 173.81998);
	CreateDynamicObject(16118, -707.90216, 1912.59314, 1342.68994,   0.00000, 0.00000, 173.81998);
	CreateDynamicObject(16118, -710.99384, 1949.48108, 1342.68994,   0.00000, 0.00000, 184.79997);
	CreateDynamicObject(16118, -728.97577, 1987.18005, 1342.68994,   0.00000, 0.00000, 217.43997);
	CreateDynamicObject(16118, -765.65674, 1987.18347, 1342.68994,   0.00000, 0.00000, 310.98004);
	CreateDynamicObject(16118, -782.62848, 1954.54321, 1342.68994,   0.00000, 0.00000, 343.20007);
	CreateDynamicObject(16118, -797.30420, 1969.35815, 1342.68994,   0.00000, 0.00000, 539.81982);
	CreateDynamicObject(16118, -831.33850, 1994.97327, 1342.68994,   0.00000, 0.00000, 621.83978);
	CreateDynamicObject(16118, -871.38110, 1977.63672, 1342.68994,   0.00000, 0.00000, 677.33972);
	CreateDynamicObject(16118, -881.69141, 1953.17615, 1339.77087,   0.00000, 0.00000, 694.01971);
	CreateDynamicObject(16118, -920.87140, 1958.61548, 1339.77087,   0.00000, 0.00000, 615.11981);
	CreateDynamicObject(16118, -961.46594, 1944.18140, 1339.55823,   0.00000, 0.00000, 668.99982);
	CreateDynamicObject(16118, -982.79370, 1913.68579, 1339.77087,   0.00000, 0.00000, 677.15948);
	CreateDynamicObject(16118, -1003.42828, 1877.60352, 1339.77087,   0.00000, 0.00000, 687.71948);
	CreateDynamicObject(16118, -1008.50989, 1837.49683, 1339.77087,   0.00000, 0.00000, 715.79950);
	CreateDynamicObject(16118, -1012.54956, 1791.97375, 1339.77087,   0.00000, 0.00000, 696.65961);
	CreateDynamicObject(16118, -1012.85999, 1748.55225, 1339.77087,   0.00000, 0.00000, 721.61963);
	CreateDynamicObject(16118, -972.55524, 1677.34851, 1339.77087,   0.00000, 0.00000, 820.13947);
	CreateDynamicObject(16118, -952.25598, 1691.74634, 1339.77087,   0.00000, 0.00000, 849.17944);
	CreateDynamicObject(18751, -779.25983, 1718.25696, 1335.23572,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18751, -749.13635, 1766.71875, 1335.23572,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18751, -803.85809, 1772.86169, 1332.61572,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18751, -849.39380, 1722.80493, 1332.57629,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18751, -881.89838, 1806.25244, 1333.57202,   0.00000, 0.00000, -108.06004);
	CreateDynamicObject(18751, -928.30237, 1729.37402, 1335.23572,   0.00000, 0.00000, 65.39999);
	CreateDynamicObject(18751, -952.71649, 1711.28040, 1335.23572,   0.00000, 0.00000, 18.54000);
	CreateDynamicObject(18751, -952.15601, 1828.39893, 1335.23572,   0.00000, 0.00000, 18.54000);
	CreateDynamicObject(18751, -960.15894, 1891.57532, 1335.23572,   0.00000, 0.00000, 18.54000);
	CreateDynamicObject(18751, -908.34363, 1922.72388, 1335.23572,   0.00000, 0.00000, 18.54000);
	CreateDynamicObject(18751, -895.23254, 1853.92749, 1335.23572,   0.00000, 0.00000, 18.54000);
	CreateDynamicObject(18751, -967.92767, 1773.90405, 1334.05969,   0.00000, 0.00000, 18.54000);
	CreateDynamicObject(18751, -826.62213, 1828.95325, 1332.35303,   0.00000, 0.00000, -83.75999);
	CreateDynamicObject(18751, -747.62024, 1817.95190, 1335.23572,   0.00000, 0.00000, -58.02000);
	CreateDynamicObject(18751, -759.86200, 1877.83789, 1335.23572,   0.00000, 0.00000, -58.02000);
	CreateDynamicObject(18751, -742.56476, 1932.83691, 1335.23572,   0.00000, 0.00000, -58.02000);
	CreateDynamicObject(18751, -805.27020, 1923.61694, 1335.23572,   0.00000, 0.00000, -58.02000);
	CreateDynamicObject(18751, -850.30103, 1895.97034, 1335.23572,   0.00000, 0.00000, -58.02000);
	CreateDynamicObject(18751, -833.70679, 1949.03040, 1335.23572,   0.00000, 0.00000, -58.02000);
	CreateDynamicObject(6965, -848.31885, 1753.18689, 1331.94153,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(6052, -926.80591, 1782.24939, 1337.76929,   0.00000, 0.00000, 125.39999);
	CreateDynamicObject(6052, -922.81946, 1807.45471, 1337.76929,   0.00000, 0.00000, 306.84006);
	CreateDynamicObject(3279, -909.09698, 1882.60376, 1336.22534,   0.00000, 0.00000, -157.37999);
	CreateDynamicObject(3279, -813.61060, 1863.39905, 1335.02197,   0.00000, 0.00000, -351.47989);
	CreateDynamicObject(11427, -870.02313, 1827.48950, 1343.10840,   0.00000, 0.00000, 112.85999);
	CreateDynamicObject(11445, -859.29218, 1818.84326, 1336.05933,   0.00000, 0.00000, 129.47993);
	CreateDynamicObject(11445, -900.62549, 1787.14221, 1336.60938,   0.00000, 0.00000, 27.53993);
	CreateDynamicObject(11445, -924.01862, 1825.86279, 1338.55859,   0.00000, 0.00000, 228.11993);
	CreateDynamicObject(4602, -835.93097, 1950.16187, 1408.04663,   0.00000, 0.00000, 77.82000);
	CreateDynamicObject(5740, -1003.22699, 1865.77539, 1325.79797,   0.00000, 0.00000, -27.78000);
	CreateDynamicObject(9361, -828.74628, 1784.01196, 1338.55920,   0.00000, 0.00000, 135.96008);
	CreateDynamicObject(10444, -791.81403, 1845.65674, 1335.63000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(10444, -806.22748, 1840.03198, 1335.63000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(10444, -802.15118, 1866.91455, 1335.63000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(10444, -816.34210, 1855.03210, 1335.63000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(10444, -830.37677, 1857.54114, 1335.63000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(10444, -843.97681, 1852.55212, 1335.63000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(10444, -800.49310, 1798.83215, 1335.63000,   0.00000, 0.00000, 25.55996);
	CreateDynamicObject(10444, -814.24884, 1794.39526, 1335.63000,   0.00000, 0.00000, 25.55996);
	CreateDynamicObject(10444, -827.34406, 1796.09729, 1335.63000,   0.00000, 0.00000, 25.55996);
	CreateDynamicObject(10444, -839.57159, 1788.23877, 1335.63000,   0.00000, 0.00000, 25.55996);
	CreateDynamicObject(10444, -837.65796, 1762.39258, 1335.63000,   0.00000, 0.00000, 129.05998);
	CreateDynamicObject(10444, -833.62848, 1756.64368, 1335.63000,   0.00000, 0.00000, 154.61992);
	CreateDynamicObject(10444, -851.65472, 1743.34607, 1335.63000,   0.00000, 0.00000, 87.35994);
	CreateDynamicObject(10444, -925.04230, 1788.81970, 1335.55701,   0.00000, 0.00000, 220.49989);
	CreateDynamicObject(10444, -837.65796, 1762.39258, 1335.63000,   0.00000, 0.00000, 129.05998);
	CreateDynamicObject(619, -800.15448, 1807.93872, 1336.24597,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(619, -803.56519, 1788.01672, 1336.24597,   0.00000, 0.00000, -50.46000);
	CreateDynamicObject(619, -828.86469, 1807.27234, 1336.24597,   0.00000, 0.00000, 94.61999);
	CreateDynamicObject(619, -846.14795, 1766.39343, 1336.24597,   0.00000, 0.00000, 94.61999);
	CreateDynamicObject(619, -827.53284, 1746.84607, 1336.24597,   0.00000, 0.00000, 261.95999);
	CreateDynamicObject(619, -840.35931, 1857.71912, 1336.24597,   0.00000, 0.00000, 94.61999);
	CreateDynamicObject(619, -807.16028, 1854.02148, 1336.24597,   0.00000, 0.00000, 94.61999);
	CreateDynamicObject(619, -810.24884, 1832.03198, 1336.24597,   0.00000, 0.00000, 190.01999);
	CreateDynamicObject(619, -938.48914, 1791.96045, 1336.24597,   0.00000, 0.00000, 143.70000);
	CreateDynamicObject(10444, -846.77344, 1780.30078, 1335.63000,   0.00000, 0.00000, 37.73995);
	CreateDynamicObject(10444, -859.40234, 1772.85632, 1335.63000,   0.00000, 0.00000, 39.65996);
	CreateDynamicObject(10444, -858.56201, 1756.97266, 1335.63000,   0.00000, 0.00000, 39.65996);
	CreateDynamicObject(10444, -875.03491, 1747.79578, 1335.63000,   0.00000, 0.00000, 89.15993);
	CreateDynamicObject(10444, -877.54645, 1760.39392, 1335.63000,   0.00000, 0.00000, 47.27995);
	CreateDynamicObject(10444, -792.72095, 1804.57080, 1335.63000,   0.00000, 0.00000, 25.55996);
	CreateDynamicObject(10444, -802.27887, 1819.82971, 1335.63000,   0.00000, 0.00000, 25.55996);
	CreateDynamicObject(10444, -895.47467, 1763.84351, 1335.63000,   0.00000, 0.00000, 69.47995);
	CreateDynamicObject(10444, -912.97638, 1772.76489, 1335.63000,   0.00000, 0.00000, 69.47995);
	CreateDynamicObject(10444, -856.33429, 1786.29504, 1335.63000,   0.00000, 0.00000, 26.09996);
	CreateDynamicObject(10444, -887.01532, 1773.67883, 1335.63000,   0.00000, 0.00000, 69.47995);
	CreateDynamicObject(10444, -929.66229, 1775.64124, 1335.55701,   0.00000, 0.00000, 220.49989);
	CreateDynamicObject(3217, -821.19537, 1831.48938, 1337.91174,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3271, -818.74231, 1828.16382, 1336.70349,   2.10000, 5.22000, 32.64000);
	CreateDynamicObject(11496, -830.18988, 1788.31604, 1335.87451,   0.00000, 0.00000, 182.28000);
	CreateDynamicObject(19473, -797.28943, 1819.39001, 1335.09399,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19473, -788.15155, 1807.40332, 1335.09399,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19473, -787.08905, 1793.58289, 1335.09399,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19473, -803.76459, 1804.85254, 1335.09399,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19473, -814.62732, 1788.37317, 1335.09399,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19473, -828.75824, 1797.03723, 1335.09399,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19473, -863.95007, 1771.91150, 1335.09399,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19473, -874.19775, 1747.71069, 1335.09399,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11445, -913.01160, 1853.44495, 1338.55859,   0.00000, 0.00000, 76.55997);
	CreateDynamicObject(4682, -969.72479, 1728.03931, 1321.04456,   0.00000, 0.00000, -26.52001);
	CreateDynamicObject(4682, -969.81696, 1727.62512, 1321.98010,   279.94000, -0.48000, -27.00000);
	CreateDynamicObject(4682, -982.66553, 1700.18042, 1344.73230,   -88.79997, -0.42000, -27.00000);
	CreateDynamicObject(16121, -1002.87402, 1751.70410, 1335.20361,   0.00000, 0.00000, -39.77999);
	CreateDynamicObject(6965, -840.96545, 1762.77783, 1331.94153,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3671, -934.95917, 1715.99951, 1344.06482,   0.00000, 0.00000, 64.50002);
	CreateDynamicObject(6965, -842.82684, 1786.74207, 1332.15259,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(6965, -805.16290, 1796.36938, 1331.88611,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(6965, -803.45618, 1841.41003, 1331.84863,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3749, -963.74628, 1740.75037, 1346.55042,   0.00000, 0.00000, -26.33999);
	CreateDynamicObject(987, -944.28802, 1732.85571, 1340.79419,   0.00000, 0.00000, 152.52005);
	CreateDynamicObject(987, -970.49011, 1745.94275, 1340.79419,   0.00000, 0.00000, 152.52005);
	CreateDynamicObject(987, -980.99402, 1751.46924, 1340.79419,   0.00000, 0.00000, 242.82014);
	CreateDynamicObject(987, -986.44775, 1740.84766, 1340.79419,   0.00000, 0.00000, 245.70006);
	CreateDynamicObject(987, -991.42188, 1729.98083, 1340.79419,   0.00000, 0.00000, 245.70006);
	CreateDynamicObject(2404, -833.14001, 1785.40137, 1337.15649,   -5.94000, 0.54000, 273.78003);
	CreateDynamicObject(1637, -844.50452, 1797.23340, 1337.07727,   0.00000, 0.00000, -1.38000);
	CreateDynamicObject(1637, -891.00220, 1758.96179, 1336.74231,   0.00000, 0.00000, -138.78012);
	CreateDynamicObject(1637, -818.24524, 1846.83777, 1336.48682,   0.00000, 0.00000, 36.05987);
	CreateDynamicObject(1391, -980.63647, 1817.79089, 1383.28186,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1391, -974.60022, 1849.37292, 1409.86365,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1391, -1002.62708, 1861.01526, 1438.42114,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(17001, -776.43176, 1715.80725, 1335.50598,   0.00000, 0.00000, 15.05999);
	CreateDynamicObject(16200, -1108.45764, 1711.16748, 1406.67432,   0.00000, 0.00000, 194.93997);
	CreateDynamicObject(16200, -1115.91187, 1873.70605, 1406.67432,   0.00000, 0.00000, 167.69998);
	CreateDynamicObject(16200, -991.80591, 2019.59326, 1406.67432,   0.00000, 0.00000, 120.78005);
	CreateDynamicObject(16200, -846.84937, 2070.31372, 1416.72693,   0.00000, 0.00000, 99.84006);
	CreateDynamicObject(16200, -672.43127, 2047.69019, 1416.72693,   0.00000, 0.00000, 52.56005);
	CreateDynamicObject(16200, -619.91766, 1937.84595, 1416.72693,   0.00000, 0.00000, 17.64005);
	CreateDynamicObject(16200, -606.95789, 1781.43115, 1416.72693,   0.00000, 0.00000, -2.63995);
	CreateDynamicObject(16200, -639.62311, 1678.56580, 1416.72693,   0.00000, 0.00000, -29.33995);
	CreateDynamicObject(16200, -752.16052, 1581.57458, 1416.72693,   0.00000, 0.00000, -84.47997);
	CreateDynamicObject(16200, -869.27399, 1595.05469, 1416.72693,   0.00000, 0.00000, -84.47997);
	CreateDynamicObject(16200, -982.37415, 1612.21301, 1416.72693,   0.00000, 0.00000, -104.51994);
	CreateDynamicObject(16200, -1078.51392, 1614.28760, 1416.72693,   0.00000, 0.00000, -145.85994);
	CreateDynamicObject(16200, -1088.00317, 1664.36548, 1416.72693,   0.00000, 0.00000, -145.85994);
	CreateDynamicObject(16200, -567.28436, 1788.04504, 1474.93530,   0.00000, 0.00000, -2.63995);
	CreateDynamicObject(16200, -578.36328, 1680.48120, 1474.93530,   0.00000, 0.00000, -13.79996);
	CreateDynamicObject(16200, -721.96466, 1538.64050, 1474.93530,   0.00000, 0.00000, -59.45995);
	CreateDynamicObject(16200, -886.94470, 1556.03235, 1474.93530,   0.00000, 0.00000, -104.33994);
	CreateDynamicObject(16200, -963.19086, 1590.76660, 1474.93530,   0.00000, 0.00000, -89.51994);
	CreateDynamicObject(16200, -1132.89734, 1659.30981, 1474.93530,   0.00000, 0.00000, -137.39995);
	CreateDynamicObject(16200, -1154.53503, 1824.14978, 1474.93530,   0.00000, 0.00000, -171.29994);
	CreateDynamicObject(16200, -1101.79736, 2014.74536, 1474.93530,   0.00000, 0.00000, -229.97992);
	CreateDynamicObject(16200, -1023.64166, 2068.66431, 1474.93530,   0.00000, 0.00000, -229.97992);
	CreateDynamicObject(16200, -861.08856, 2096.78931, 1474.93530,   0.00000, 0.00000, -257.75989);
	CreateDynamicObject(16200, -673.69574, 2080.78223, 1474.93530,   0.00000, 0.00000, -299.39984);
	CreateDynamicObject(16200, -589.54602, 1970.85388, 1474.93530,   0.00000, 0.00000, -334.19977);
	CreateDynamicObject(16200, -579.00146, 1825.20801, 1474.93530,   0.00000, 0.00000, -343.31973);
	CreateDynamicObject(16121, -684.71112, 1887.81445, 1375.09473,   -40.68000, 39.71999, -206.34003);
	CreateDynamicObject(5130, -960.24121, 1748.18896, 1337.79614,   0.00000, 0.00000, 17.76000);
	CreateDynamicObject(970, -966.36023, 1744.51196, 1341.24329,   0.00000, 0.00000, -26.46000);
	CreateDynamicObject(970, -959.59729, 1741.16528, 1341.24329,   0.00000, 0.00000, -26.46000);
	CreateDynamicObject(970, -956.09320, 1739.05542, 1341.24329,   0.00000, 0.00000, -35.76000);
	CreateDynamicObject(7073, -955.35828, 1722.86841, 1359.17224,   0.00000, 0.00000, -36.84001);
	CreateDynamicObject(4682, -744.85291, 1931.96021, 1322.38867,   0.00000, 0.00000, -24.54000);
	CreateDynamicObject(4682, -754.38477, 1910.80298, 1317.57935,   22.38001, 0.00000, -23.81999);
	CreateDynamicObject(4682, -731.87927, 1961.49561, 1340.28296,   -280.00000, 0.00000, -25.00000);
	CreateDynamicObject(4682, -772.19958, 1954.54468, 1340.28296,   -280.00000, 0.00000, 54.01999);
	CreateDynamicObject(4682, -710.21338, 1922.91284, 1340.28296,   -280.00000, 0.00000, 249.67999);
	CreateDynamicObject(16121, -706.62579, 1912.84863, 1339.27014,   0.00000, 0.00000, -221.10002);
	CreateDynamicObject(16200, -620.49042, 1938.15662, 1416.72693,   0.00000, 0.00000, 17.64005);
	CreateDynamicObject(3749, -749.85132, 1919.60425, 1347.68567,   0.00000, 0.00000, -23.93999);
	CreateDynamicObject(987, -741.62054, 1915.30237, 1341.92627,   0.00000, 0.00000, -22.14000);
	CreateDynamicObject(987, -769.06799, 1927.90369, 1341.92627,   0.00000, 0.00000, -26.82000);
	CreateDynamicObject(3671, -943.75641, 1722.68945, 1344.06482,   0.00000, 0.00000, 64.50002);
	CreateDynamicObject(14400, -822.99951, 1849.50000, 1336.00500,   0.00000, 0.00000, 39.60000);
	CreateDynamicObject(14400, -850.78680, 1846.40820, 1336.00500,   0.00000, 0.00000, 77.46000);
	CreateDynamicObject(19338, -865.15973, 1824.59619, 1418.09265,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(16121, -777.88318, 1947.69055, 1346.20544,   0.00000, 0.00000, -187.13995);
	CreateDynamicObject(16118, -767.53552, 1947.71252, 1342.68994,   0.00000, 0.00000, 321.66010);
	CreateDynamicObject(16118, -765.96490, 1967.93445, 1342.68994,   0.00000, 0.00000, 267.24014);
	CreateDynamicObject(16118, -732.87329, 1971.35815, 1342.68994,   0.00000, 0.00000, 232.56017);
	CreateDynamicObject(16118, -745.55383, 1967.36084, 1342.68994,   0.00000, 0.00000, 232.56017);
	CreateDynamicObject(16118, -734.66675, 1958.75879, 1342.68994,   0.00000, 0.00000, 232.56017);
	CreateDynamicObject(16118, -756.14410, 1961.83618, 1342.68994,   0.00000, 0.00000, 246.06007);
	CreateDynamicObject(16118, -743.03644, 1959.84521, 1342.68994,   0.00000, 0.00000, 229.98007);
	CreateDynamicObject(16118, -734.79559, 1955.25842, 1342.68994,   0.00000, 0.00000, 229.98007);
	CreateDynamicObject(16118, -713.67108, 1944.18860, 1343.66003,   0.00000, 0.00000, 521.52008);
	CreateDynamicObject(16118, -714.34094, 1917.67407, 1340.48193,   0.00000, 0.00000, 537.96008);
	CreateDynamicObject(16118, -714.19659, 1937.62659, 1340.48193,   0.00000, 0.00000, 526.56030);
	CreateDynamicObject(16118, -718.00714, 1925.88489, 1335.57275,   0.00000, 0.00000, 526.56030);
	CreateDynamicObject(16118, -714.54309, 1929.27661, 1335.57275,   0.00000, 0.00000, 505.50070);
	CreateDynamicObject(16118, -713.01300, 1937.15088, 1343.14648,   0.00000, 0.00000, 509.28076);
	CreateDynamicObject(16118, -713.45203, 1906.08813, 1343.14648,   0.00000, 0.00000, 587.16107);
	CreateDynamicObject(16118, -709.20300, 1901.53333, 1343.14648,   0.00000, 0.00000, 587.16107);
	CreateDynamicObject(16118, -717.02142, 1928.22729, 1340.86292,   0.00000, 0.00000, 507.54227);
	CreateDynamicObject(16118, -709.19733, 1915.07874, 1335.33569,   0.00000, 0.00000, 471.66223);
	CreateDynamicObject(16118, -704.37079, 1911.46729, 1335.33569,   0.00000, 0.00000, 471.66223);
	CreateDynamicObject(1683, -713.69403, 1849.55188, 1363.36926,   3.78000, 56.88003, -173.45979);
	CreateDynamicObject(3509, -768.01544, 1876.77539, 1340.80017,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3509, -762.29803, 1825.64661, 1337.65283,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3509, -786.74664, 1745.01160, 1335.20837,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3509, -840.14966, 1729.75464, 1335.20837,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3509, -908.93213, 1738.79553, 1335.20837,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3509, -964.88147, 1771.27234, 1339.20374,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3509, -953.42297, 1888.26965, 1340.67969,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3509, -887.83264, 1866.84021, 1338.99182,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3509, -846.18121, 1899.45435, 1340.15723,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(16122, -716.37714, 1786.38501, 1332.66724,   0.00000, 0.00000, -170.82005);
	CreateDynamicObject(13591, -947.11224, 1738.13000, 1337.42908,   0.00000, 0.00000, -34.43999);
	CreateDynamicObject(7916, -856.53107, 1773.08154, 1334.99231,   -25.62000, 0.54000, -110.40000);
	CreateDynamicObject(7916, -839.18915, 1775.64685, 1334.99231,   -25.62000, 0.54000, -100.13998);
	CreateDynamicObject(2068, -841.50592, 1896.37012, 1345.07813,   0.00000, 0.00000, 22.44000);
	CreateDynamicObject(8644, -925.30322, 1795.03442, 1342.96350,   0.00000, 0.00000, 52.31999);
	CreateDynamicObject(8644, -924.78564, 1795.17468, 1342.96350,   0.00000, 0.00000, 230.69998);
	CreateDynamicObject(16401, -884.26013, 1805.47314, 1337.73389,   6.90000, 2.34000, 23.46000);
	CreateDynamicObject(3363, -769.19025, 1766.92371, 1337.96460,   0.00000, 0.00000, -75.96001);
	CreateDynamicObject(4988, -883.53015, 1714.15857, 1359.41711,   0.00000, 0.00000, 13.08000);
	CreateDynamicObject(12943, -926.05731, 1899.36243, 1337.28503,   0.00000, 0.00000, 207.17999);
	
	//arena derbow 1:
	CreateDynamicObject(13607, 2379.2565917969, -2048.6943359375, 5867.4897460938, 339.75, 0, 0);
 

	//arena derbow 2:
	CreateDynamicObject(4246, 259.43194580078, 1508.2989501953, 4013.3315429688, 0, 0, 0);
	CreateDynamicObject(5126, 292.27465820313, 1546.4672851563, 4028.4558105469, 0, 0, 0);
	CreateDynamicObject(5126, 340.38726806641, 1561.9197998047, 4028.4558105469, 0, 0, 266.71020507813);
	CreateDynamicObject(3474, 328.33773803711, 1455.0915527344, 4020.2514648438, 0, 0, 0);
	CreateDynamicObject(1395, 234.34246826172, 1507.7618408203, 4045.412109375, 0, 0, 0);
	CreateDynamicObject(1395, 191.09526062012, 1437.4802246094, 4024.7868652344, 307.94692993164, 0, 0);
	CreateDynamicObject(1394, 211.74478149414, 1463.3361816406, 4013.3315429688, 28.763244628906, 0, 0);
	CreateDynamicObject(1394, 214.19030761719, 1463.3031005859, 4013.3315429688, 28.76220703125, 0, 0);
	CreateDynamicObject(1392, 175.98803710938, 1580.0246582031, 4013.6779785156, 0, 0, 0);
	CreateDynamicObject(1391, 183.87420654297, 1580.5812988281, 4045.7119140625, 0, 0, 0);
	CreateDynamicObject(1380, 160.42840576172, 1568.2508544922, 4037.5515136719, 0, 0, 0);
	CreateDynamicObject(1380, 217.88362121582, 1544.4310302734, 4037.5515136719, 0, 0, 0);
	CreateDynamicObject(1378, 261.68008422852, 1480.2945556641, 4037.7233886719, 0, 0, 332);
	CreateDynamicObject(1378, 304.44934082031, 1505.6643066406, 4037.7233886719, 0, 0, 70.759155273438);
	CreateDynamicObject(16337, 294.51718139648, 1477.6586914063, 4013.1821289063, 0, 0, 0);
	CreateDynamicObject(16337, 297.26797485352, 1477.5532226563, 4012.2822265625, 0, 0, 0);
	CreateDynamicObject(16337, 299.87451171875, 1477.6008300781, 4011.3068847656, 0, 0, 0);
	CreateDynamicObject(16337, 291.7956237793, 1477.3967285156, 4013.78125, 0, 0, 0);
	CreateDynamicObject(16328, 293.70574951172, 1439.982421875, 4013.3315429688, 0, 0, 0);
	CreateDynamicObject(2918, 290.70013427734, 1477.3934326172, 4015.220703125, 0, 0, 0);
	CreateDynamicObject(2918, 188.93185424805, 1579.7370605469, 4015.220703125, 0, 0, 0);
	CreateDynamicObject(2918, 224.92999267578, 1550.4443359375, 4015.220703125, 0, 0, 0);
	CreateDynamicObject(2918, 223.87586975098, 1539.6173095703, 4015.220703125, 0, 0, 0);
	CreateDynamicObject(2918, 213.16744995117, 1464.3350830078, 4015.5327148438, 0, 0, 0);
	CreateDynamicObject(2918, 192.3938293457, 1426.36328125, 4015.1184082031, 0, 0, 0);
	CreateDynamicObject(3786, 212.90896606445, 1457.7125244141, 4017.1904296875, 0, 0, 0.76327514648438);
	CreateDynamicObject(3786, 298.39965820313, 1540.4097900391, 4014.6508789063, 0, 0, 0.758056640625);
	CreateDynamicObject(3786, 291.81399536133, 1540.1297607422, 4014.5803222656, 0, 0, 168.99871826172);
	CreateDynamicObject(3786, 295.03509521484, 1538.3862304688, 4014.6372070313, 0, 0, 89.707397460938);
	CreateDynamicObject(3797, 294.96444702148, 1539.0550537109, 4014.8156738281, 0, 0, 0);
	CreateDynamicObject(3797, 291.72274780273, 1540.1577148438, 4014.7587890625, 0, 0, 0);
	CreateDynamicObject(3797, 298.52621459961, 1540.2933349609, 4014.8293457031, 0, 0, 0);
	CreateDynamicObject(3797, 290.38986206055, 1477.6458740234, 4015.8991699219, 0, 0, 0);
	CreateDynamicObject(3797, 293.12811279297, 1440.9581298828, 4014.0561523438, 0, 0, 0);
	CreateDynamicObject(3797, 327.25830078125, 1451.6101074219, 4019.5720214844, 0, 0, 0);
	CreateDynamicObject(3797, 191.52372741699, 1423.5216064453, 4015.5317382813, 0, 0, 0);
	CreateDynamicObject(3797, 213.11915588379, 1457.5454101563, 4017.015625, 0, 0, 0);
	CreateDynamicObject(3797, 188.97941589355, 1498.8853759766, 4014.5307617188, 0, 0, 0);
	CreateDynamicObject(3797, 248.35319519043, 1523.0823974609, 4015.2058105469, 0, 0, 0);
	CreateDynamicObject(3797, 291.64361572266, 1595.1574707031, 4015.1313476563, 0, 0, 0);
	CreateDynamicObject(12911, 350.56503295898, 1594.1824951172, 4013.3315429688, 0, 0, 0);
	CreateDynamicObject(12911, 368.6037902832, 1604.0717773438, 4013.3315429688, 0, 0, 100.02862548828);
	CreateDynamicObject(12911, 335.34295654297, 1604.0626220703, 4013.3315429688, 0, 0, 282.8694152832);
	CreateDynamicObject(12911, 307.50378417969, 1603.7999267578, 4013.3315429688, 0, 0, 279.81188964844);
	CreateDynamicObject(12911, 279.1513671875, 1603.4770507813, 4013.3315429688, 0, 0, 279.81079101563);
	CreateDynamicObject(12911, 249.20845031738, 1603.9653320313, 4013.3315429688, 0, 0, 279.81079101563);
	CreateDynamicObject(12911, 221.50512695313, 1604.0892333984, 4013.3315429688, 0, 0, 279.81079101563);
	CreateDynamicObject(12911, 191.22885131836, 1603.5034179688, 4013.3315429688, 0, 0, 279.81079101563);
	CreateDynamicObject(12911, 162.48785400391, 1602.6811523438, 4013.3315429688, 0, 0, 279.81079101563);
	CreateDynamicObject(12911, 140.73977661133, 1590.7177734375, 4013.3315429688, 0, 0, 6.7333374023438);
	CreateDynamicObject(12911, 139.76678466797, 1562.3553466797, 4013.3315429688, 0, 0, 6.7291259765625);
	CreateDynamicObject(12911, 141.1340637207, 1534.1000976563, 4013.3315429688, 0, 0, 6.7291259765625);
	CreateDynamicObject(12911, 138.7931060791, 1504.4136962891, 4013.3315429688, 0, 0, 6.7291259765625);
	CreateDynamicObject(12911, 136.29170227051, 1476.5489501953, 4013.3315429688, 0, 0, 6.7291259765625);
	CreateDynamicObject(12911, 136.97055053711, 1449.0284423828, 4013.3315429688, 0, 0, 6.7291259765625);
	CreateDynamicObject(12911, 137.25100708008, 1421.9685058594, 4013.3315429688, 0, 0, 15.888305664063);
	CreateDynamicObject(12911, 155.26629638672, 1412.3461914063, 4013.3315429688, 0, 0, 101.41485595703);
	CreateDynamicObject(12911, 185.56378173828, 1413.0609130859, 4013.3315429688, 0, 0, 101.41479492188);
	CreateDynamicObject(12911, 215.96405029297, 1413.755859375, 4013.3315429688, 0, 0, 101.41479492188);
	CreateDynamicObject(12911, 244.35601806641, 1413.2706298828, 4013.3315429688, 0, 0, 101.41479492188);
	CreateDynamicObject(12911, 271.87002563477, 1412.4675292969, 4013.3315429688, 0, 0, 101.41479492188);
	CreateDynamicObject(12911, 300.91851806641, 1412.5621337891, 4013.3315429688, 0, 0, 101.41479492188);
	CreateDynamicObject(12911, 329.53018188477, 1413.2150878906, 4013.3315429688, 0, 0, 101.41479492188);
	CreateDynamicObject(12911, 357.84591674805, 1413.7492675781, 4013.3315429688, 0, 0, 101.41479492188);
	CreateDynamicObject(12911, 377.31921386719, 1425.630859375, 4013.3315429688, 0, 0, 184.52087402344);
	CreateDynamicObject(12911, 379.14529418945, 1453.8186035156, 4013.3315429688, 0, 0, 184.51538085938);
	CreateDynamicObject(3115, 252.09201049805, 1548.701171875, 4014.2204589844, 347.39593505859, 0, 0);
	CreateDynamicObject(3115, 252.13096618652, 1534.3739013672, 4018.1877441406, 342.05029296875, 0, 0);
 
	//arena derbow 3:
	CreateDynamicObject(8558, -1704.4621582031, 1453.7590332031, 4275.81640625, 0, 0, 0);
	CreateDynamicObject(8558, -1743.8470458984, 1453.7537841797, 4275.783203125, 0, 0, 0);
	CreateDynamicObject(8558, -1783.6077880859, 1453.76171875, 4275.75, 0, 0, 0);
	CreateDynamicObject(8558, -1801.5944824219, 1453.162109375, 4275.720703125, 0, 0, 90.738830566406);
	CreateDynamicObject(8558, -1801.0306396484, 1413.6722412109, 4275.7626953125, 0, 0, 90.736083984375);
	CreateDynamicObject(8558, -1783.2420654297, 1396.3978271484, 4275.66015625, 0, 0, 180.97283935547);
	CreateDynamicObject(8558, -1742.9200439453, 1397.0697021484, 4275.634765625, 0, 0, 180.97229003906);
	CreateDynamicObject(8558, -1702.8940429688, 1397.806640625, 4275.607421875, 0, 0, 180.97229003906);
	CreateDynamicObject(8558, -1685.5341796875, 1415.6723632813, 4275.57421875, 0, 0, 270.94787597656);
	CreateDynamicObject(8558, -1686.1903076172, 1455.7053222656, 4275.6240234375, 0, 0, 270.94482421875);
	CreateDynamicObject(8558, -1703.9327392578, 1479.8129882813, 4275.5986328125, 0, 0, 341.70812988281);
	CreateDynamicObject(8558, -1734.0245361328, 1499.9255371094, 4275.5693359375, 0, 0, 311.41796875);
	CreateDynamicObject(8558, -1758.7403564453, 1501.3874511719, 4275.5419921875, 0, 0, 41.890869140625);
	CreateDynamicObject(8558, -1786.6600341797, 1480.8386230469, 4275.5107421875, 0, 0, 31.199645996094);
	CreateDynamicObject(3378, -1680.8356933594, 1435.0025634766, 4277.0693359375, 0, 337.10202026367, 0);
	CreateDynamicObject(3378, -1681.4859619141, 1464.7469482422, 4277.0439453125, 0, 337.09899902344, 0);
	CreateDynamicObject(3378, -1702.5655517578, 1392.7955322266, 4277.1025390625, 0, 337.09899902344, 271.55096435547);
	CreateDynamicObject(3378, -1744.8726806641, 1392.0111083984, 4277.0546875, 0, 337.09350585938, 271.54907226563);
	CreateDynamicObject(3378, -1789.4071044922, 1391.3646240234, 4276.9296875, 0, 337.09350585938, 271.54907226563);
	CreateDynamicObject(3378, -1805.6458740234, 1428.7789306641, 4277.107421875, 0, 337.09350585938, 180.81036376953);
	CreateDynamicObject(3378, -1759.7293701172, 1505.7655029297, 4277.037109375, 0, 337.09350585938, 130.54229736328);
	CreateDynamicObject(3378, -1766.9055175781, 1457.955078125, 4277.169921875, 0, 337.09350585938, 90.588470458984);
	CreateDynamicObject(3378, -1675.9466552734, 1435.0152587891, 4278.1181640625, 0, 0, 0);
	CreateDynamicObject(3378, -1676.5576171875, 1464.7315673828, 4278.07421875, 0, 0, 0);
	CreateDynamicObject(3378, -1702.3995361328, 1387.8100585938, 4278.1318359375, 0, 0, 271.55096435547);
	CreateDynamicObject(3378, -1744.7926025391, 1387.0568847656, 4278.0400390625, 0, 0, 271.54907226563);
	CreateDynamicObject(3378, -1789.2943115234, 1386.3991699219, 4277.9340820313, 0, 0, 271.54907226563);
	CreateDynamicObject(3378, -1766.9530029297, 1462.7624511719, 4278.1689453125, 0, 0, 271.54907226563);
	CreateDynamicObject(3378, -1762.9732666016, 1509.5439453125, 4278.03125, 0, 0, 310.36535644531);
	CreateDynamicObject(3378, -1810.6552734375, 1428.6365966797, 4278.1049804688, 0, 0, 0.6292724609375);


	//derby (arena - do zabawy - bez puszek czerwonych):
	CreateDynamicObject(8171, -10923.173828125, -37.090618133545, 57.413055419922, 0, 0, 91.620483398438);
	CreateDynamicObject(8171, -10917.471679688, -273.41787719727, 57.413055419922, 0, 0, 91.625);
	CreateDynamicObject(8171, -10829.874023438, -220.74736022949, 57.413055419922, 0, 0, 181.3955078125);
	CreateDynamicObject(8171, -10833.166015625, -83.718307495117, 57.413055419922, 0, 0, 181.3955078125);
	CreateDynamicObject(8171, -10863.091796875, -182.30317687988, 41.853057861328, 0, 51.610046386719, 181.39526367188);
	CreateDynamicObject(8171, -10866.495117188, -44.676204681396, 41.731861114502, 0, 51.610046386719, 181.39526367188);
	CreateDynamicObject(8171, -11007.431640625, -226.72734069824, 57.413055419922, 0, 0, 181.39526367188);
	CreateDynamicObject(8171, -11010.827148438, -88.713401794434, 57.413055419922, 0, 0, 181.39526367188);
	CreateDynamicObject(8171, -10922.377929688, -68.973808288574, 41.863037109375, 0, 51.608276367188, 271.91735839844);
	CreateDynamicObject(8171, -10977.625, -127.53714752197, 41.777523040771, 0, 51.608276367188, 1.4028930664063);
	CreateDynamicObject(8171, -10974.145507813, -265.39846801758, 41.825428009033, 0, 51.608276367188, 1.4007568359375);
	CreateDynamicObject(8171, -10917.5625, -241.15835571289, 41.790103912354, 0, 51.608276367188, 91.729339599609);


	//derby-miejsce 2:
	CreateDynamicObject(3378, 8164.8959960938, -2928.6049804688, 15.114748001099, 0, 0, 0);
	CreateDynamicObject(3378, 8164.9213867188, -2948.8142089844, 9.2587699890137, 32.487762451172, 0, 0);
	CreateDynamicObject(3378, 8164.818359375, -2908.9499511719, 8.6411209106445, 323.53674316406, 0, 0);
	CreateDynamicObject(3378, 8166.5703125, -2889.2497558594, 1.8446942567825, 0, 0, 349.73266601563);
	CreateDynamicObject(3378, 8170.5424804688, -2867.1870117188, 1.8219132423401, 0, 0, 349.72778320313);
	CreateDynamicObject(3378, 8174.4580078125, -2845.1362304688, 1.8218632936478, 0, 0, 349.72778320313);
	CreateDynamicObject(3378, 8189.3256835938, -2839.6350097656, 0.16040816903114, 8.687744140625, 0, 77.687072753906);
	CreateDynamicObject(3378, 8196.0380859375, -2841.0642089844, 0, 0, 0, 77.687072753906);
	CreateDynamicObject(3378, 8218.0224609375, -2845.8442382813, 0, 0, 0, 77.684326171875);
	CreateDynamicObject(3378, 8229.9228515625, -2857.0915527344, 0, 0, 0, 167.17004394531);
	CreateDynamicObject(3378, 8225.0693359375, -2878.7072753906, -1.3634694814682, 352.89184570313, 0, 167.16796875);
	CreateDynamicObject(3378, 8223.5361328125, -2885.5532226563, -1.3634694814682, 0, 0, 167.16796875);
	CreateDynamicObject(3378, 8218.8076171875, -2906.6496582031, -0.24061225354671, 6.318359375, 0, 167.16796875);
	CreateDynamicObject(3378, 8214.513671875, -2925.7028808594, 4.4769077301025, 19.743682861328, 0, 167.16796875);
	CreateDynamicObject(3378, 8210.376953125, -2943.962890625, 1.8816063404083, 324.24447631836, 0, 167.16796875);
	CreateDynamicObject(3378, 8164.9946289063, -2964.8828125, -0.9485998749733, 32.486572265625, 0, 0);
	CreateDynamicObject(3378, 8165.05078125, -2977.3781738281, -1.8446941375732, 0, 0, 0);
	CreateDynamicObject(3378, 8165.0546875, -2988.5974121094, 0, 344.09796142578, 0, 0);
	CreateDynamicObject(3378, 8165.2084960938, -3010.3366699219, 3.1310205459595, 0, 0, 0);
	CreateDynamicObject(3378, 8173.607421875, -3018.9997558594, 3.0107936859131, 0, 0, 116.39181518555);
	CreateDynamicObject(3378, 8186.78125, -3006.7534179688, 7.854061126709, 333.83056640625, 0.789794921875, 147.19116210938);
	CreateDynamicObject(3378, 8195.8994140625, -2992.6599121094, 5.1019268035889, 44.308166503906, 0.7855224609375, 146.39953613281);
	CreateDynamicObject(3378, 8200.6484375, -2978.1091308594, 0, 0, 0, 349.72778320313);
	CreateDynamicObject(3378, 8206.140625, -2956.9990234375, 0, 0, 0, 340.25024414063);
	CreateDynamicObject(3378, 8163.990234375, -2834.2556152344, 7.1443119049072, 29.381652832031, 0, 77.713623046875);
	CreateDynamicObject(3378, 8159.6196289063, -3026.4289550781, 5.361608505249, 25.429046630859, 0, 118.94039916992);
	CreateDynamicObject(3378, 8150.94140625, -2924.1462402344, 15.300054550171, 0.86517333984375, 0, 91.191345214844);
	CreateDynamicObject(3378, 8142.5561523438, -2923.1730957031, 15.394884109497, 0.0726318359375, 0, 179.90893554688);
	CreateDynamicObject(3378, 8141.4770507813, -3036.8469238281, 10.309072494507, 0.8624267578125, 0, 120.54165649414);
	CreateDynamicObject(3378, 8133.5390625, -3039.9794921875, 10.388366699219, 0.0726318359375, 0, 212.36499023438);
	CreateDynamicObject(3378, 8144.015625, -2829.7585449219, 12.700291633606, 0.8624267578125, 0, 76.97021484375);
	CreateDynamicObject(3378, 8136.36328125, -2825.7985839844, 12.850516319275, 0.0714111328125, 0, 167.24334716797);
	CreateDynamicObject(3378, 8242.3779296875, -2851.0891113281, 3.3934674263, 337.75305175781, 0, 77.684326171875);
	CreateDynamicObject(3378, 8263.068359375, -2855.5366210938, 7.552357673645, 0, 0, 77.684326171875);
	CreateDynamicObject(3378, 8271.4716796875, -2856.9323730469, 7.497052192688, 0, 0, 167.16796875);
	CreateDynamicObject(3378, 8211.369140625, -2964.3916015625, 2.3508150577545, 332.35711669922, 0, 71.338500976563);
	CreateDynamicObject(3378, 8230.9228515625, -2971.0190429688, 7.4481401443481, 0, 0, 70.576171875);
	CreateDynamicObject(3378, 8238.8818359375, -2974.3312988281, 7.3928346633911, 0, 0, 160.85168457031);
	CreateDynamicObject(3378, 8170.2495117188, -3029.7490234375, 5.6848268508911, 25.427856445313, 0, 205.23791503906);
	CreateDynamicObject(3378, 8179.35546875, -3048.5283203125, 10.388298988342, 0, 0, 26.169403076172);
	CreateDynamicObject(3378, 8183.5004882813, -3055.9562988281, 10.252789497375, 0, 0, 115.72927856445);
	CreateDynamicObject(1225, 8233.50390625, -2852.1977539063, 1.5866456031799, 0, 0, 0);
	CreateDynamicObject(1225, 8234.53125, -2846.5061035156, 1.5396082401276, 0, 0, 0);
	CreateDynamicObject(1225, 8228.5771484375, -2850.9423828125, 1.5866456031799, 0, 0, 0);
	CreateDynamicObject(1225, 8229.4716796875, -2845.5786132813, 1.5866456031799, 0, 0, 0);
	CreateDynamicObject(1225, 8172.9692382813, -2839.0166015625, 3.4085087776184, 0, 0, 0);
	CreateDynamicObject(1225, 8174.0668945313, -2833.5747070313, 3.4430961608887, 0, 0, 0);
	CreateDynamicObject(1225, 8179.1162109375, -2834.640625, 3.4085087776184, 0, 0, 0);
	CreateDynamicObject(1225, 8178.26171875, -2840.0078125, 3.4085087776184, 0, 0, 0);
	CreateDynamicObject(1225, 8162.1103515625, -2920.8974609375, 16.701393127441, 0, 0, 0);
	CreateDynamicObject(1225, 8162.1586914063, -2926.5830078125, 16.718240737915, 0, 0, 0);
	CreateDynamicObject(1225, 8167.6733398438, -2926.3330078125, 16.701393127441, 0, 0, 0);
	CreateDynamicObject(1225, 8167.7734375, -2920.7668457031, 16.701393127441, 0, 0, 0);
	CreateDynamicObject(1225, 8165.1791992188, -3026.3000488281, 4.7322292327881, 0, 0, 0);
	CreateDynamicObject(1225, 8162.68359375, -3021.2778320313, 4.7176661491394, 0, 0, 0);
	CreateDynamicObject(1225, 8168.208984375, -3018.7658691406, 4.597439289093, 0, 0, 0);
	CreateDynamicObject(1225, 8170.3046875, -3023.3081054688, 4.6392827033997, 0, 0, 0);
	CreateDynamicObject(1225, 8207.4951171875, -2960.2807617188, 1.5866456031799, 0, 0, 0);
	CreateDynamicObject(1225, 8205.7763671875, -2965.896484375, 1.5866456031799, 0, 0, 0);
	CreateDynamicObject(1225, 8200.7900390625, -2963.9291992188, 1.5866456031799, 0, 0, 0);
	CreateDynamicObject(1225, 8202.9775390625, -2957.7749023438, 1.5866456031799, 0, 0, 0);
	CreateDynamicObject(1225, 8164.8623046875, -2939.9482421875, 19.838001251221, 0, 0, 0);
	CreateDynamicObject(1225, 8164.6674804688, -2917.6306152344, 19.749145507813, 0, 0, 0);
/*
 
*/
	//object to...
	CreateDynamicObject(18783, 2862.45068, 629.51282, 800.99231,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19446, 2863.87183, 619.48199, 29.54388,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19446, 2872.38232, 634.73065, 805.07928,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19446, 2872.37598, 625.10596, 805.07928,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19446, 2867.63477, 620.41376, 805.07928,   0.00000, 0.00000, -90.41998);
	CreateDynamicObject(19446, 2858.00098, 620.47675, 805.07928,   0.00000, 0.00000, -90.35989);
	CreateDynamicObject(19446, 2853.22266, 625.23773, 805.07928,   0.00000, 0.00000, -179.87997);
	CreateDynamicObject(19446, 2853.20288, 634.83368, 805.07928,   0.00000, 0.00000, -179.87997);
	CreateDynamicObject(19446, 2857.88379, 639.33185, 805.07928,   0.00000, 0.00000, -269.99991);
	CreateDynamicObject(19446, 2872.38232, 634.73065, 808.53430,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19446, 2872.37598, 625.10596, 808.54333,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19446, 2867.63477, 620.41376, 808.53290,   0.00000, 0.00000, -90.41998);
	CreateDynamicObject(19446, 2858.01489, 620.49109, 808.53168,   0.00000, 0.00000, -90.35989);
	CreateDynamicObject(19446, 2853.22266, 625.23773, 808.53186,   0.00000, 0.00000, -179.87997);
	CreateDynamicObject(19446, 2853.20288, 634.83368, 808.53418,   0.00000, 0.00000, -179.87997);
	CreateDynamicObject(19446, 2857.88379, 639.33185, 808.52612,   0.00000, 0.00000, -269.99991);
	CreateDynamicObject(19446, 2867.46826, 639.33234, 808.51617,   0.00000, 0.00000, -270.11990);
	CreateDynamicObject(19446, 2867.46826, 639.33234, 805.07281,   0.00000, 0.00000, -270.11990);
	CreateDynamicObject(19446, 2860.84888, 637.78430, 805.07928,   0.00000, 0.00000, -360.12015);
	CreateDynamicObject(19446, 2860.83105, 637.78815, 808.53833,   0.00000, 0.00000, -360.12015);
	CreateDynamicObject(18783, 2862.75024, 630.01520, 812.72949,   180.00000, 0.00000, 0.00000);
	CreateDynamicObject(19172, 2870.17432, 639.22784, 805.69049,   0.00000, 0.00000, 0.95999);
	CreateDynamicObject(19175, 2872.28906, 626.91583, 805.76654,   0.00000, 0.00000, -90.00007);
	CreateDynamicObject(14467, 2854.61377, 638.42529, 805.51031,   0.00000, 0.00000, 54.24004);
	CreateDynamicObject(3528, 2870.80688, 638.13184, 808.66089,   -2.42000, 6.68000, 235.00000);
	CreateDynamicObject(18075, 2856.96240, 633.39948, 810.20776,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18075, 2866.05225, 633.74493, 810.20776,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18075, 2862.91382, 624.18683, 810.27020,   0.00000, 0.00000, -90.78001);
	CreateDynamicObject(2707, 2863.36694, 629.47272, 810.24561,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2707, 2863.38672, 633.77246, 810.24561,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2707, 2863.56396, 637.96973, 810.24561,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2707, 2868.75415, 637.97791, 810.24561,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2707, 2868.68994, 633.56671, 810.24561,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2707, 2868.70752, 629.65771, 810.24561,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2707, 2867.21313, 626.88562, 810.24561,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2707, 2867.20508, 621.39203, 810.24561,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2707, 2862.97632, 621.55176, 810.24561,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2707, 2858.66602, 621.59900, 810.24561,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2707, 2858.74438, 626.90100, 810.24561,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2707, 2859.75024, 628.88159, 810.24561,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2707, 2854.26685, 629.05219, 810.24561,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2707, 2854.29468, 633.18030, 810.24561,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2707, 2854.36084, 637.52551, 810.24561,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2707, 2859.62695, 637.57983, 810.24561,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2707, 2859.58057, 633.52405, 810.24561,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14762, 2853.35278, 633.68079, 805.10236,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14762, 2861.85718, 639.19073, 805.10236,   0.00000, 0.00000, -90.30000);
	CreateDynamicObject(14762, 2872.26318, 633.58026, 805.10236,   0.00000, 0.00000, -179.99995);
	CreateDynamicObject(14762, 2863.05957, 620.57239, 805.10236,   0.00000, 0.00000, -270.17990);
	CreateDynamicObject(1827, 2870.48706, 637.42145, 803.47229,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2179, 2860.95508, 632.72754, 804.90631,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2179, 2860.95508, 632.72754, 809.17230,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1763, 2869.73096, 638.70569, 803.43750,   0.00000, 0.00000, 0.24000);
	CreateDynamicObject(1763, 2871.75220, 638.19812, 803.43750,   0.00000, 0.00000, -89.39999);
	CreateDynamicObject(2778, 2861.48096, 633.82782, 803.48846,   0.00000, 0.00000, 90.84001);
	CreateDynamicObject(2778, 2861.48853, 637.86841, 803.48846,   0.00000, 0.00000, 90.84001);
	CreateDynamicObject(2640, 2861.65259, 635.60504, 804.36566,   0.00000, 0.00000, 89.88005);
	CreateDynamicObject(1746, 2868.71069, 636.66486, 803.49036,   0.00000, 0.00000, -63.54002);
	CreateDynamicObject(1746, 2870.48657, 635.51306, 803.49036,   0.00000, 0.00000, -0.72002);
	CreateDynamicObject(2611, 2855.87402, 639.19434, 805.37952,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2164, 2863.56006, 639.23572, 803.47357,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2614, 2863.86670, 639.12854, 806.06110,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1808, 2860.53784, 633.28656, 803.47070,   0.00000, 0.00000, -89.15999);
	CreateDynamicObject(1665, 2870.94629, 637.81018, 803.91797,   0.00000, 0.00000, 35.94001);
	CreateDynamicObject(3027, 2870.94897, 637.84344, 803.89899,   -6.60000, -37.80000, 1.02000);
	CreateDynamicObject(3027, 2870.90649, 637.87958, 803.89899,   -6.60000, -37.80000, -170.58006);
	CreateDynamicObject(1775, 2860.37549, 634.59717, 804.24762,   0.00000, 0.00000, -90.47999);
	CreateDynamicObject(2453, 2860.26245, 634.27545, 805.67749,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2839, 2870.20532, 637.12256, 803.89954,   0.00000, 0.00000, -2.70000);
	CreateDynamicObject(2624, 2870.18896, 623.08344, 805.04321,   0.00000, 0.00000, -90.36002);
	CreateDynamicObject(2229, 2853.15479, 625.57245, 803.48889,   0.00000, 0.00000, 94.86001);
	CreateDynamicObject(2229, 2853.04150, 628.95856, 803.48889,   0.00000, 0.00000, 94.86001);
	CreateDynamicObject(2296, 2853.29443, 626.01599, 803.39142,   0.00000, 0.00000, 90.78002);
	CreateDynamicObject(2229, 2853.15479, 625.57245, 804.82654,   0.00000, 0.00000, 94.86001);
	CreateDynamicObject(2229, 2853.04150, 628.95856, 804.82629,   0.00000, 0.00000, 94.86001);
	CreateDynamicObject(1839, 2853.79395, 624.47009, 803.95673,   0.00000, 0.00000, -177.35991);
	CreateDynamicObject(14782, 2858.93213, 620.99817, 804.44220,   0.00000, 0.00000, -180.42000);
	CreateDynamicObject(2321, 2853.90845, 622.87738, 803.47052,   0.00000, 0.00000, 93.12001);
	CreateDynamicObject(2277, 2853.82593, 623.24341, 805.76880,   0.00000, 0.00000, -269.15958);
	CreateDynamicObject(2255, 2860.27173, 636.64258, 805.04645,   0.00000, 0.00000, -90.48008);
	CreateDynamicObject(2225, 2853.55640, 623.97028, 803.92542,   0.00000, 0.00000, 92.52001);
	CreateDynamicObject(1790, 2854.00586, 622.85229, 804.03992,   0.00000, 0.00000, -84.71996);
	CreateDynamicObject(2028, 2853.99561, 623.40326, 803.57324,   0.00000, 0.00000, 93.00002);
	CreateDynamicObject(2104, 2872.15137, 624.01727, 803.49384,   0.00000, 0.00000, 271.25989);
	CreateDynamicObject(1886, 2872.05396, 620.67316, 810.36249,   8.64000, 0.36000, 227.69998);
	CreateDynamicObject(1828, 2870.63721, 637.47388, 803.49023,   0.00000, 0.00000, -20.82000);
	CreateDynamicObject(1828, 2854.67407, 627.23853, 803.47028,   0.00000, 0.00000, 94.31999);
	CreateDynamicObject(627, 2854.39331, 621.38623, 805.13196,   0.00000, 0.00000, -18.42000);
	CreateDynamicObject(2274, 2854.17749, 622.15674, 803.48737,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2203, 2854.00342, 632.35101, 803.67438,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14804, 2860.18433, 638.30151, 804.43542,   0.00000, 0.00000, -13.26000);
	CreateDynamicObject(3802, 2868.17212, 638.63672, 805.95685,   0.00000, 0.00000, -72.06000);
	CreateDynamicObject(2251, 2861.67456, 620.90015, 806.16156,   0.00000, 0.00000, 0.00000);
	
	LoadEvent_DD();
	LoadEvent_DDSpawn();
	
	LoadEvent_CH();
	LoadEvent_WG();
	
	LoadEvent_CtfSpawn();
	
	LoadEvent_Ws();
	LoadEvent_WsCp();
	LoadEvent_WsSp();
	
	
	script_zb[b_object] = CreateObject(19198, 500.0, -500.0, 200.0, 0.0, 0.0, 0.0, 150.0);
	script_tr[tr_bar]   = CreateProgressBar(243.00, 310.00, 163.50, 9.19, 16711884, 100.0);
	
}

stock PlayerEventTD(playerid, bool:show = true)
{
	if(show)
	{
		PlayerTextDrawShow(playerid, pInfo[playerid][player_TdAnn][0]);
		PlayerTextDrawShow(playerid, pInfo[playerid][player_TdAnn][1]);
		TextDrawShowForPlayer(playerid, PlayerEventBox);
	}
	else 
	{
		PlayerTextDrawHide(playerid, pInfo[playerid][player_TdAnn][0]);	
		PlayerTextDrawHide(playerid, pInfo[playerid][player_TdAnn][1]);	
		TextDrawHideForPlayer(playerid, PlayerEventBox);
	}
}
stock PlayerEventTDSet(playerid, td2[], title[] = "-")
{
	PlayerTextDrawSetString(playerid, pInfo[playerid][player_TdAnn][1], td2);
	PlayerTextDrawSetString(playerid, pInfo[playerid][player_TdAnn][0], title);
	 
	PlayerEventTD(playerid, true);
}
stock OPTEvent()
{
	TextDrawHideForAll(EventTD0[0]);
	TextDrawHideForAll(EventTD0[1]);
	
	OPTCheck = 0;
	for(new i;i<sizeof(OPTIDs);i++) OPTIDs[i] = -1;
	switch(++gmData[opt_event])
	{
		case 1:
		{
			if(OPTResult[0] != EOS)
			{
				SendClientMessageToAll(COLOR_INFO, "{FFFFFF}» {00B3FF}Nikomu nie uda³o siê obliczyæ wyniku matematycznego. Wynik to %d.", strval(OPTResult));  
			}
			OPTResult[0] = EOS;
			for(new i=0; i<9; i++)
				format(OPTResult, sizeof(OPTResult), "%s%s", OPTResult, Characters[random(sizeof(Characters))][0]);
			
			TextDrawSetString(EventTD0[0], splitf("~g~Przepisz ~g~kod: ~w~%s",OPTResult)); 
			TextDrawShowForAll(EventTD0[0]);
		}
		case 2:
		{
			if(OPTResult[0] != EOS)
			{
				SendClientMessageToAll(COLOR_INFO, "{FFFFFF}» {33FF00}Nikomu nie uda³o siê przepisaæ kodu.");  
			}
			
			OPTResult[0] = EOS;
			
			new rand = random(sizeof(PlaceChars));
			
			format(OPTResult, sizeof(OPTResult), "%s", PlaceChars[rand]);
			
			new str[50];
			mix_string(PlaceChars[rand], str);
			TextDrawSetString(EventTD0[1], splitf("~r~Uloz wyraz: ~w~%s",str)); 
			TextDrawShowForAll(EventTD0[1]);
 		}
		case 3:
		{
			OPTResult[0] = EOS;
			
			new znaki[3] = {'+', '-', '*'};
			new l[3];
			new znak[2];
			
			znak[0] = znaki[random(3)];
			znak[1] = znaki[random(3)];
			new Result;
			switch(znak[1])
			{
				case '+': {
					if(znak[0] == '+') { l[0] = random(90); l[1] = random(100); l[2] = random(95); Result = (l[0]+l[1]+l[2]); }
					if(znak[0] == '-') { l[0] = random(90); l[1] = random(100); l[2] = random(95); Result = (l[0]-l[1]+l[2]); }
					if(znak[0] == '*') { l[0] = random(20); l[1] = random(14); l[2] = random(15); Result = (l[0]*l[1]+l[2]); }
				}
				case '-': {
					if(znak[0] == '+') { l[0] = random(90); l[1] = random(100); l[2] = random(95); Result = (l[0]+l[1]-l[2]); }
					if(znak[0] == '-') { l[0] = random(90); l[1] = random(100); l[2] = random(95); Result = (l[0]-l[1]-l[2]); }
					if(znak[0] == '*') { l[0] = random(20); l[1] = random(14); l[2] = random(15); Result = (l[0]*l[1]-l[2]); }
				}
				case '*': {
					if(znak[0] == '+') { l[0] = random(100); l[1] = random(20); l[2] = random(20); Result = (l[0]+l[1]*l[2]); }
					if(znak[0] == '-') { l[0] = random(100); l[1] = random(20); l[2] = random(20); Result = (l[0]-l[1]*l[2]); }
					if(znak[0] == '*') { l[0] = random(14); l[1] = random(10); l[2] = random(12); Result = (l[0]*l[1]*l[2]); }
				}
			}
			format(OPTResult, sizeof(OPTResult), "%d", Result);
			SendClientMessageToAll(COLOR_INFO, "{FFFFFF}» {66CC00}Oblicz: {66B3FF}%d %c %d %c %d {66CC00}a dostaniesz nagrodê!", l[0], znak[0], l[1], znak[1], l[2]);  
			gmData[opt_event] = 0;
		}
	}
	gmData[opt_gamestart] = 0;
	gmData[opt_gamestart] = GetTickCount();
}

 
CMD:start1v1( playerid, params[] ){
	
	if( pInfo[playerid][player_admin] )
	{
		new fsfsf;
		if( !e1v1[e1v1_trwa] && fsfsf > 10 )
		{
			if( sscanf(params, "d", e1v1[e1v1_gun]) ) return SendClientMessage(playerid, COLOR_ERROR, ""chat" U¿yj /start1v1 [id broni]");
			if( !DuelWeapon(e1v1[e1v1_gun]) ) return SendClientMessage(playerid, 0xFF4444FF, "» Wybrana broñ jest nie dozwolona. Dozwolone bronie /soloweapons.");  
			
	
			e1v1[e1v1_trwa] = true;
			e1v1[e1v1_started] = false;
			e1v1[e1v1_admin] = playerid;
			
			//defer e1v1_Go();
			SetTimer("e1v1_Go", 20000, 0);
			TextDrawUpdateEventStart("1 vs 1", "/e1v1");
			SendClientMessageToAll(COLOR_EVENT_STARTED, "››› 1 vs 1 wystartuj¹ za {b}20 sekund{/b} (by %s) aby siê zpisaæ u¿yj /e1v1.", playerNick(playerid));
	
			
		}else{
			SendClientMessage(playerid, COLOR_ERROR, "Nie mo¿esz odpaliæ 1vs1 poniewa¿ ju¿ trwa...");
			
		}
		
	}
	return 1;
}

CMD:1v1( playerid, params[] ){
	if( Iter_Contains(e1v1_players, playerid) ) return SendClientMessage(playerid, COLOR_ERROR, " Jesteœ ju¿ zapisany(a) na 1 vs 1");
	if( e1v1[e1v1_started] ) return SendClientMessage(playerid, COLOR_ERROR, " 1 vs 1 juz wystartowalo.");
	
	new sdfsd4;
	if( e1v1[e1v1_trwa] && sdfsd4 > 10)
	{
		if(Iter_Count(e1v1_players) < 20)
		{
			Iter_Add(e1v1_players, playerid);
			SendClientMessage(playerid, COLOR_ERROR, "Zapisa³eœ siê na 1 vs 1 :)");
		}
		else 
		{
			SendClientMessage(playerid, COLOR_ERROR, "Brak miejsc na 1 vs 1 :(");
		}
	}
	else{
		SendClientMessage(playerid, COLOR_ERROR, "1 vs 1 aktualnie nie trwa...");
	}
	return 1;
}
 
Public:e1v1_Go()
{
   //SendClientMessage(playerid, COLOR_ORANGE, "››› 1 vs 1 wystartowa³o! ");
	e1v1[e1v1_started] = true;
	
	new getUser;
	foreach(new playerid : e1v1_players)
	{
		if(getUser >= 20) break;
		
		SetPlayerPos(playerid, e1v1___pos__[getUser][0], e1v1___pos__[getUser][1], e1v1___pos__[getUser][2] + 0.5);
		SetPlayerFacingAngle(playerid, e1v1___pos__[getUser][3]);
		
		ResetPlayerWeapons(playerid);
 		SetPlayerVirtualWorld(playerid, 995);
		TogglePlayerControllable(playerid, 0);
 		SetCameraBehindPlayer(playerid);
		 
		SetPlayerCameraPos(playerid, 2440.3992,1040.8788,59.5016);
		SetPlayerCameraLookAt(playerid, 2464.6667,1043.5074,57.5016);
		
		SetPlayerArmour(playerid, 100.0);
		SetPlayerHealth(playerid, 100.0);
		getUser++;
	}
	
}

CMD:1v1fight(playerid, cmdtext[])
{
	RankAdmin(playerid, R_JADMIN);
	
	new id, id2;
	if(sscanf(cmdtext, "uu", id, id2) && id > 555) return SendClientMessage(playerid, COLOR_ORANGE, "» U¿yj: /1v1fight <id/nick gracza> <id/nick gracza>"); //wygenerowany
	
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Pierwszy Gracz nie jest pod³¹czony!"); //wygenerowany
	if(!IsPlayerConnected(id2)) return SendClientMessage(playerid, COLOR_ERROR, "» Drugi Gracz nie jest pod³¹czony!"); //wygenerowany
	
	if(!Iter_Contains(e1v1_players, id)) return SendClientMessage(playerid, COLOR_ERROR, "» Pierwszy Gracz nie jest na 1 vs 1!"); //wygenerowany
	if(!Iter_Contains(e1v1_players, id2)) return SendClientMessage(playerid, COLOR_ERROR, "» Drugi Gracz nie jest na 1 vs 1!"); //wygenerowany
 
	e1v1[e1v1_soloplayers][0] = id;
	e1v1[e1v1_soloplayers][1] = id;
	
	SendClientMessageToAll(COLOR_GREEN, "{FFFFFF} »[1Z1] Solo {b}%s (%d){/b} z {b}%s (%d){/b} rozpoczête.", playerNick(playerid), playerid, playerNick(id), id); //wygenerowany
	return 1;
}

stock 
	e1v1_status()
		return e1v1[e1v1_trwa];
		

 

CMD:evstart(playerid, params[])
{
 	RankAdmin(playerid, R_MODERATOR);
	if( aEData[ev_on] ){
		if(!IsPlayerConnected( aEData[ev_lider] ) )
			aEData[ev_on] = true;
		else
			return SendClientMessage(playerid, COLOR_ERROR, "Aktualnie trwa ju¿ event");
	}
	
	new id, maxu, evnetn[64];
	if(sscanf(params, "dds[64]", id, maxu, evnetn)) return SendClientMessage(playerid, COLOR_ORANGE, "» U¿yj: /evstart <id/nick gracza> <max osob> <nazwa>"); //wygenerowany
	
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_ERROR, "» Pierwszy Gracz nie jest pod³¹czony!"); //wygenerowany
	if(maxu > 100 && maxu < 5)  return SendClientMessage(playerid, COLOR_ERROR, "» Na event mo¿e zostaæ zapisanych maksymalnie 100 osób a minimalnie 5 osób!"); //wygenerowany
	
	format(aEData[ev_name], 64, "%s", evnetn);
	aEData[ev_lider] = id;
	aEData[ev_on] = true;
	aEData[ev_started] = true;
	aEData[ev_dropweapon] = true;
	aEData[ev_gun] = 0;
	aEData[ev_car] = 0;
	aEData[ev_freezer] = false;
	aEData[ev_maxplayers] = maxu;
	aEData[ev_internior] = GetPlayerInterior(playerid);
  
	Iter_Add(EventPlayers, id);
	GetPlayerPos(playerid, aEData[ev_pos][0], aEData[ev_pos][1], aEData[ev_pos][2]);
	TextDrawUpdateEventStart(aEData[ev_name], "/evdolacz", 21);
	
	SendClientMessage(aEData[ev_lider], COLOR_ERROR, "» Zosta³eœ liderem eventu zapoznaj siê z {b}/evgui oraz /evhelp{/b}!"); 
	
	SetTimer("StartEvent", 22000, 0);
	return 1;
}
CMD:evgui(playerid, params[])
{
	if(pInfo[playerid][player_admin] || aEData[ev_lider] == playerid){
		Dialog_Show(playerid, DIALOG_EV_LIDER, DIALOG_STYLE_LIST, "• EventSystem •", "Ustaw broñ\nUstaw spawn\nUstaw pojazd\nZamroŸ / odmroŸ wszystkich\nUprawnienia broni\nUzupe³nij wszystkim ¿ycie\nUzupe³nij wszystkim kamizelkê", "Wybierz", "Zamknij");
	} else if(Iter_Contains(EventPlayers,playerid)) {
		
	}
	return 1;
}
CMD:evcar(playerid, params[])
{
	if(Iter_Contains(EventPlayers,playerid) && aEData[ev_on] && aEData[ev_car]) 
	{
		CreatePlayerVehicle(playerid, aEData[ev_car]);
		PutPlayerInVehicle(playerid, pInfo[playerid][player_vehicle], 0);
		SendClientMessage(playerid, COLOR_INFO2, ""chat" <Event> zespawnowa³eœ pojazd eventowy");
		return 1;
	}	else SendClientMessage(playerid, COLOR_INFO2, ""chat" <Event> Nie mo¿esz teraz tego zrobiæ!");
	return 1;
}

CMD:evhelp(playerid, params[])
{
	static tb12[2048];
	
	tb12[0] = EOS;
	
	strcat(tb12, "Gracz\n\n/evcar - spawnujesz pojazd eventowy.  \n/evdolacz - zapisujesz sie na event. \n");
	strcat(tb12, "/evsend - prosisz o dodanie do eventu (je¿eli ju¿ wystartowa³...) \n\nModerator / EventLider\n\n");
	strcat(tb12, "/evstart - tworzysz event. \n/evgui - panel eventu.  \n/evzakoncz - konczysz event.  \n/evfreeze - zamra¿asz wybranego gracza. \n/evunfreeze - odmra¿asz wybranego gracza. \n");
	strcat(tb12, "/evbonus - dajesz bonus wybranemu graczu. \n/evdodaj - dodajesz gracza do eventu (jezeli zlozyl prosbe /evsend). \n/evwyrzuc - wyrzucasz gracza z eventu\n");
	strcat(tb12, "/ev100arall - dajesz armor ka¿demu graczu na evencie\n/ev100hpall - dajesz zycie ka¿demu graczu na evencie\n/evgodall - dajesz goda ka¿demu graczu na evencie\n/evggall  - dajesz bron kazdemu graczu na evencie. \n");
	strcat(tb12, "/evtp - teleportujesz graczy bedacych na evencie\n");

	InfoBox(playerid, tb12);
	return 1;
}

CMD:evunfreeze(playerid, cmdtext[])
{
	if(pInfo[playerid][player_admin] == 0 && aEData[ev_lider] != playerid) return SendClientMessage(playerid, COLOR_ERROR, "#Brak uprawnieñ");
	
	new player;if(sscanf(cmdtext, "d", player)) 
	{
		SendClientMessage(playerid, 0xFF0000FF, "U¿yj /evunfreeze <id gracza>");
		return 1;
	}
	
	if(!IsPlayerConnected(player) || !Iter_Contains(EventPlayers, player))
	{
		SendClientMessage(playerid, 0xFF0000FF, "Podany gracz jest niepod³¹czony lub nie jest na evencie");
		return 1;
	}
	TogglePlayerControllable(playerid, 1);
	SendMessageEventPlayers("{b}%s (%d){/b} odmrozi³ %s (%d)", playerNick(playerid), playerid, playerNick(player), player);
	return 1;
}

CMD:evfreeze(playerid, cmdtext[])
{
	if(pInfo[playerid][player_admin] == 0 && aEData[ev_lider] != playerid) 
		return SendClientMessage(playerid, COLOR_ERROR, "#Brak uprawnieñ");
	
	new player;if(sscanf(cmdtext, "d", player)) 
		return SendClientMessage(playerid, 0xFF0000FF, "U¿yj /evfreeze <id gracza>");
	
	if(!IsPlayerConnected(player) || !Iter_Contains(EventPlayers, player))
		return SendClientMessage(playerid, 0xFF0000FF, "Podany gracz jest niepod³¹czony lub nie jest na evencie");

	TogglePlayerControllable(player, 0);
	SendMessageEventPlayers("{b}%s (%d){/b} zamrozi³ %s (%d)", playerNick(playerid), playerid, playerNick(player), player);
	return 1;
}
CMD:evbonus(playerid, cmdtext[])
{
	if(pInfo[playerid][player_admin] == 0 && aEData[ev_lider] != playerid) return SendClientMessage(playerid, COLOR_ERROR, "#Brak uprawnieñ");
	
	new player;if(sscanf(cmdtext, "d", player)) 
	{
		SendClientMessage(playerid, 0xFF0000FF, "U¿yj /evbonus <id gracza>");
		return 1;
	}
	
	if(!IsPlayerConnected(player) || !Iter_Contains(EventPlayers, player))
	{
		SendClientMessage(playerid, 0xFF0000FF, "Podany gracz jest niepod³¹czony lub nie jest na evencie");
		return 1;
	}
	
	GivePlayerMoney(player, 1000+random(2000));
	GivePlayerScore(player, 10+random(20), "bonus");
	
	SendMessageEventPlayers("{b}%s (%d){/b} da³ bonus graczu %s (%d)", playerNick(playerid), playerid, playerNick(player), player);
	return 1;
}


CMD:evgod(playerid, cmdtext[])
{
	if(pInfo[playerid][player_admin] == 0 && aEData[ev_lider] != playerid) return SendClientMessage(playerid, COLOR_ERROR, "#Brak uprawnieñ");
	
	new player;if(sscanf(cmdtext, "d", player)) 
	{
		SendClientMessage(playerid, 0xFF0000FF, "U¿yj /evgod <id gracza>");
		return 1;
	}
	
	if(!IsPlayerConnected(player) || !Iter_Contains(EventPlayers, player))
	{
		SendClientMessage(playerid, 0xFF0000FF, "Podany gracz jest niepod³¹czony lub nie jest na evencie");
		return 1;
	}
	
	SetPlayerHealth(player, 1000.0);
	
	SendMessageEventPlayers("{b}%s (%d){/b} da³ goda graczu %s (%d)", playerNick(playerid), playerid, playerNick(player), player);
	return 1;
}

CMD:evgodall(playerid, params[])
{
	if(pInfo[playerid][player_admin] == 0 && aEData[ev_lider] != playerid) return SendClientMessage(playerid, COLOR_ERROR, "#Brak uprawnieñ");
	

	foreach(new i : EventPlayers) SetPlayerHealth(i, 1000.0);
	
	SendMessageEventPlayers("{b}%s (%d){/b} da³ goda {ffff00}wszystkim graczom{/b}.", playerNick(playerid), playerid);
	return 1;
}

CMD:evgg(playerid, cmdtext[])
{
	if(pInfo[playerid][player_admin] == 0 && aEData[ev_lider] != playerid) return SendClientMessage(playerid, COLOR_ERROR, "#Brak uprawnieñ");
	
	new player, gunid, ammo;if(sscanf(cmdtext, "ddd", player, gunid, ammo)) 
	{
		SendClientMessage(playerid, 0xFF0000FF, "U¿yj /evgg <id gracza> <id broni> <amunicji>");
		return 1;
	}
	
	if(!IsPlayerConnected(player) || !Iter_Contains(EventPlayers, player))
	{
		SendClientMessage(playerid, 0xFF0000FF, "Podany gracz jest niepod³¹czony lub nie jest na evencie");
		return 1;
	}
	if(gunid < 1 && gunid > 39)
	{
		SendClientMessage(playerid, 0xFF0000FF, "Nie prawid³owa broñ - dozwolone bronie /soloweapons");
		return 1;
	}
	
	if(ammo < 0 || ammo > 10000)
	{	
		SendClientMessage(playerid, 0xFF0000FF, "B³êdna iloœæ amunicji");
		return 1;
	}
	
	GivePlayerWeapon(player, gunid, ammo);
	
	SendMessageEventPlayers("{b}%s (%d){/b} da³ broñ %s graczu %s (%d)", playerNick(playerid), playerid, GetWeaponNameEx(gunid), playerNick(player), player);
	return 1;
}

CMD:evggall(playerid, cmdtext[])
{
	if(pInfo[playerid][player_admin] == 0 && aEData[ev_lider] != playerid) return SendClientMessage(playerid, COLOR_ERROR, "#Brak uprawnieñ");
	
	new gunid, ammo;if(sscanf(cmdtext, "dd", gunid, ammo)) 
	{
		SendClientMessage(playerid, 0xFF0000FF, "U¿yj /evggall <id broni> <amunicji>");
		return 1;
	}
	
	if(gunid < 1 && gunid > 39)
	{
		SendClientMessage(playerid, 0xFF0000FF, "Nie prawid³owa broñ - dozwolone bronie /soloweapons");
		return 1;
	}
	
	
	if(ammo < 0 || ammo > 10000)
		return SendClientMessage(playerid, 0xFF0000FF, "B³êdna iloœæ amunicji");
	
	foreach(new i : EventPlayers)	GivePlayerWeapon(i, gunid, ammo);
	
	SendMessageEventPlayers("{b}%s (%d){/b} da³ broñ %s {ff0000}wszystkim graczom{/b}.", playerNick(playerid), playerid, GetWeaponNameEx(gunid));
	return 1;
}

CMD:evann(playerid, params[])
{
	if(pInfo[playerid][player_admin] == 0 && aEData[ev_lider] != playerid) return SendClientMessage(playerid, COLOR_ERROR, "#Brak uprawnieñ");
	
	if(!params[0])
	{
		SendClientMessage(playerid, 0xFF0000FF, "U¿yj /evann <tekst>");
		return 1;
	}
	
	if(strlen(params) > 82)
	{
		SendClientMessage(playerid, 0xFF0000FF, "Tekst jest za d³ugi ;|");
		return 1;
	}
	
	 
	new anncnt;
	for(new i=0; i<strlen(params); i++)
	{
		if(params[i] == '~') anncnt++;
	}
	if(anncnt%2 != 0) 
		return SendClientMessage(playerid, COLOR_ERROR, ""chat" W tekœcie znajduje siê {b}nieparzysta{/b} liczba znaków ~ co spowoduje b³¹d!");  
	
	new players[MAX_PLAYERS] = {-1,...}, c;
	
	foreach(new i : EventPlayers)
	{
		players[c]=i;
		c++;
	}
	ShowAnnForPlayers(params, 15, players, c);
	SendMessageEventPlayers("{b}%s (%d){/b} w³¹czy³(a) tekst na ekranie!", playerNick(playerid), playerid);
	return 1;
}

CMD:ev100hp(playerid, cmdtext[])
{
	if(pInfo[playerid][player_admin] == 0 && aEData[ev_lider] != playerid) return SendClientMessage(playerid, COLOR_ERROR, "#Brak uprawnieñ");
	
	new player;if(sscanf(cmdtext, "d", player)) 
	{
		SendClientMessage(playerid, 0xFF0000FF, "U¿yj /ev100hp <id gracza>");
		return 1;
	}
	
	if(!IsPlayerConnected(player) || !Iter_Contains(EventPlayers, player))
	{
		SendClientMessage(playerid, 0xFF0000FF, "Podany gracz jest niepod³¹czony lub nie jest na evencie");
		return 1;
	}
	
	SetPlayerHealth(player, 100.0);
	
	SendMessageEventPlayers("{b}%s (%d){/b} ustawi³ 100 HP graczu %s (%d)", playerNick(playerid), playerid, playerNick(player), player);
	return 1;
}

CMD:ev100hpall(playerid, params[])
{
	if(pInfo[playerid][player_admin] == 0 && aEData[ev_lider] != playerid) return SendClientMessage(playerid, COLOR_ERROR, "#Brak uprawnieñ");
	
	
	foreach(new i : EventPlayers) SetPlayerHealth(i, 100.0);
	
	SendMessageEventPlayers("{b}%s (%d){/b} ustawi³ 100 HP {ff0000}wszystkim graczom{/b}.", playerNick(playerid), playerid);
	return 1;
}
CMD:ev100arall(playerid, params[])
{
	if(pInfo[playerid][player_admin] == 0 && aEData[ev_lider] != playerid) return SendClientMessage(playerid, COLOR_ERROR, "#Brak uprawnieñ");
	
	
	foreach(new i : EventPlayers) SetPlayerArmour(i, 100.0);
	
	SendMessageEventPlayers("{b}%s (%d){/b} ustawi³ 100 AR {ff0000}wszystkim graczom{/b}.", playerNick(playerid), playerid);
	return 1;
}
CMD:evtp(playerid, cmdtext[])
{
	if(pInfo[playerid][player_admin] == 0 && aEData[ev_lider] != playerid) return SendClientMessage(playerid, COLOR_ERROR, "#Brak uprawnieñ");
	
	new player, player2;if(sscanf(cmdtext, "dd", player, player2)) 
		
	if(!IsPlayerConnected(player) || !Iter_Contains(EventPlayers, player))
	{
		SendClientMessage(playerid, 0xFF0000FF, "Pierwszy gracz jest niepod³¹czony lub nie jest na evencie");
		return 1;
	}
	
	if(!IsPlayerConnected(player2) || !Iter_Contains(EventPlayers, player2))
	{
		SendClientMessage(playerid, 0xFF0000FF, "Drugi gracz jest niepod³¹czony lub nie jest na evencie");
		return 1;
	}
	 
	if(pInfo[player][player_gangWarTeam] != 0)
	{	
		SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} »{/b}  Ten gracz aktualnie jest na wojnie gangów");  
		return 1;
	}
	if(pInfo[player2][player_gangWarTeam] != 0)
	{	
		SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} »{/b}  Ten gracz aktualnie jest na wojnie gangów");  
		return 1;
	}
 
	 
	TeleportPlayerToPlayer(player, player2);
	
	SendClientMessage(playerid, COLOR_INFO, "{FFFFFF} »{/b} Teleportowa³eœ gracza {b}%s (%d){/b} do gracza {b}%s (%d){/b}.", playerNick(player), player, playerNick(player2), player2);  
	SendClientMessage(player, COLOR_GREEN, "{FFFFFF} » {b}%s (%d){/b} teleportowa³ Ciê do gracza {b}%s (%d){/b}.", playerNick(playerid), playerid, playerNick(player2), player2);  
	SendClientMessage(player2, COLOR_GREEN, "{FFFFFF} » {b}%s (%d){/b} teleportowa³ do Ciebie gracza {b}%s (%d){/b}.", playerNick(playerid), playerid, playerNick(player), player);  
	return 1;
}

CMD:ev100ar(playerid, cmdtext[])
{
	if(pInfo[playerid][player_admin] == 0 && aEData[ev_lider] != playerid) return SendClientMessage(playerid, COLOR_ERROR, "#Brak uprawnieñ");
	
	new player;if(sscanf(cmdtext, "d", player)) 
	{
		SendClientMessage(playerid, 0xFF0000FF, "U¿yj /ev100hp <id gracza>");
		return 1;
	}
	
	if(!IsPlayerConnected(player) || !Iter_Contains(EventPlayers, player))
	{
		SendClientMessage(playerid, 0xFF0000FF, "Podany gracz jest niepod³¹czony lub nie jest na evencie");
		return 1;
	}
	
	SetPlayerArmour(player, 100.0);
	
	SendMessageEventPlayers("{b}%s (%d){/b} ustawi³ 100 Armora graczu %s (%d)", playerNick(playerid), playerid, playerNick(player), player);
	return 1;
}
 

CMD:evzakoncz(playerid, params[])
{
	if(pInfo[playerid][player_admin] || aEData[ev_lider] == playerid){
	 
		ClearEvent(playerid, 1);
	
	} else SendClientMessage(playerid, COLOR_ERROR, "#Brak uprawnieñ");
	return 1;
}

CMD:evsend(playerid, params[])
{
	if(Iter_Count(EventPlayers) > aEData[ev_maxplayers])
	{
		SendClientMessage(playerid, COLOR_INFO2, ""chat" <Event> Nie mo¿esz do³¹czyæ na evnet poniewa¿ wyczerpa³ siê limit graczy...");
		return 1;
	}
	if(!aEData[ev_on])
	{
		SendClientMessage(playerid, COLOR_INFO2, ""chat" <Event> Event aktualnie nie trwa...");
		return 1;
	}
	
	if(pInfo[playerid][player_objected])
		return InfoBox(playerid, "Nie mozesz zapisac sie na event poniewaz masz wylaczone obiekty");
	
	if(pInfo[playerid][player_toev])
	{
		SendClientMessage(playerid, COLOR_INFO2, ""chat" <Event> Poprosi³eœ ju¿ o dodanie do eventu! ");
		return 1;
	}

	if(!Iter_Contains(EventPlayers,playerid) && aEData[ev_on] && !aEData[ev_started]) 
	{
		//Iter_Add(EventPlayers, playerid);
		pInfo[playerid][player_toev] = true;
		
		SendMessageEventPlayers("{b}%s (%d){/b} prosi o dodanie do eventu, wpisz {b}/evdodaj %d{/b} aby go dodaæ... ", playerNick(playerid), playerid, playerid);
		SendClientMessage(playerid, COLOR_INFO2, ""chat" <Event> Proœba o zapisanie na event wys³ana");
		return 1;
	}	
	SendClientMessage(playerid, COLOR_INFO2, ""chat" <Event> Proœba o zapisanie na event nie zosta³a wys³ana");
	return 1;
}
CMD:evdolacz(playerid, params[])
{
	if(Iter_Count(EventPlayers) > aEData[ev_maxplayers])
	{
		SendClientMessage(playerid, COLOR_INFO2, ""chat" <Event> Nie mo¿esz do³¹czyæ na evnet poniewa¿ wyczerpa³ siê limit graczy...");
		return 1;
	}
	if(aEData[ev_on] && !aEData[ev_started])
	{
		SendClientMessage(playerid, COLOR_INFO2, ""chat" <Event> Event aktualnie trwa, wyœlij proœbe o dodanie {b}/evsend{/b}");
		return 1;
	}

	if(pInfo[playerid][player_objected])
		return InfoBox(playerid, "Nie mozesz zapisac sie na event poniewaz masz wylaczone obiekty");
	
	if(!Iter_Contains(EventPlayers,playerid) && aEData[ev_on] && aEData[ev_started]) 
	{
		Iter_Add(EventPlayers, playerid);
		SendClientMessage(playerid, COLOR_INFO2, ""chat" <Event> Zapisa³eœ siê na event");
		return 1;
	}
	SendClientMessage(playerid, COLOR_ERROR, ""chat" <Event> Wyst¹pi³ b³¹d i nie zosta³eœ zapisany na event");
	return 1;
}
CMD:evdodaj(playerid, cmdtext[])
{
	if(pInfo[playerid][player_admin] == 0 && aEData[ev_lider] != playerid) return SendClientMessage(playerid, COLOR_ERROR, "#Brak uprawnieñ");
	
	new player;if(sscanf(cmdtext, "d", player)) 
	{
		SendClientMessage(playerid, 0xFF0000FF, "U¿yj /evdodaj <id gracza>");
		return 1;
	}
	
	if(!IsPlayerConnected(player))
	{
		SendClientMessage(playerid, 0xFF0000FF, "Podany gracz jest niepod³¹czony");
		return 1;
	}
	if(Iter_Contains(EventPlayers, player))
	{
		SendClientMessage(playerid, 0xFF0000FF, "Ten gracz aktualnie jest na evencie!");
		return 1;
	}
	if(!pInfo[(player)][player_toev])
	{
		SendClientMessage(playerid, 0xFF0000FF, "Podany gracz nie sk³ada³ proœby o dodanie do eventu (/evsend)");
		return 1;
	}
	SetPlayerEvent(player);
	Iter_Add(EventPlayers, player);
	SendMessageEventPlayers("{b}%s (%d){/b} doda³ do eventu %s (%d)", playerNick(playerid), playerid, playerNick(player), player);
	return 1;
}

CMD:evwyrzuc(playerid, cmdtext[])
{
	if(pInfo[playerid][player_admin] == 0 && aEData[ev_lider] != playerid) return SendClientMessage(playerid, COLOR_ERROR, "#Brak uprawnieñ");
	
	new player;if(sscanf(cmdtext, "d", player)) 
	{
		SendClientMessage(playerid, 0xFF0000FF, "U¿yj /evwyrzuc <id gracza>");
		return 1;
	}
	
	if(!IsPlayerConnected(player) || !Iter_Contains(EventPlayers, player))
	{
		SendClientMessage(playerid, 0xFF0000FF, "Podany gracz jest niepod³¹czony lub nie jest na evencie");
		return 1;
	}
	
	SendMessageEventPlayers("{b}%s (%d){/b} wyrzuci³ z eventu %s (%d)", playerNick(playerid), playerid, playerNick(player), player);
	Iter_Remove(EventPlayers, player);
	OnPlayerSpawn(player);
	return 1;
}
 

stock ClearEvent(by = INVALID_PLAYER_ID, reason = 0)
{
	if(reason == 1)
	{
		if(IsPlayerConnected(by))
			SendMessageEventPlayers("{b}%s (%d){/b} zakoñczy³ event", playerNick(by), by);
	}
	else if(reason == 0)
	{
			SendMessageEventPlayers("Event zosta³ zakoñczony z powodu braku prowadz¹cego");
	}
	
	SendClientMessageToAll(COLOR_INFO3, "Event zosta³ zakoñczony");
	format(aEData[ev_name], 64, "%s", "-");
	aEData[ev_lider] = -1;
	aEData[ev_on] = false;
	aEData[ev_started] = false;
	aEData[ev_dropweapon] = false;
	aEData[ev_gun] = 0;
	aEData[ev_car] = 0;
	aEData[ev_freezer] = false;
	foreach(new i : EventPlayers) 
	{
		GivePlayerScore(i, 20, "udzia³ w evecie");
		SetPlayerVirtualWorld(i, 0);
		OnPlayerSpawn(i);
	}
	Iter_Clear(EventPlayers);
}

stock ReturnFromEvent( playerid )
{
	if(Iter_Contains(EventPlayers,playerid) && aEData[ev_on]) return Iter_Remove(EventPlayers, playerid), 1;
	
	return 0;
	
}
Public:StartEvent()
{
	aEData[ev_started] = false;
	SendMessageEventPlayers("Zaczynamy zabawê!");
	SendClientMessageToAll(-1, "{008ae6}Event{/b} zosta³ rozpoczêty");
	foreach(new xplayerid : EventPlayers)
	{
		SetPlayerEvent(xplayerid);
	}
	return 1;
}
 
 
stock SetPlayerEvent(xplayerid)
{
	ResetPlayerWeapons(xplayerid);
	SetPlayerPos(xplayerid, aEData[ev_pos][0] + random(3), aEData[ev_pos][1] + random(2), aEData[ev_pos][2] + 1.0);
	SetPlayerVirtualWorld(xplayerid, 1);
	SetPlayerInterior(xplayerid, aEData[ev_internior]);
	if(aEData[ev_lider] == xplayerid)
	{
		SetPlayerHealth(xplayerid,99999);
		GivePlayerWeapon(xplayerid,38,999999);
	}
	return 1;
}
 
 
Dialog:DIALOG_EV_LIDER(playerid, response, listitem, inputtext[])
{
	if(response){
		evPlayerSett[playerid] = listitem;
		new str512[512];
		switch(listitem)
		{
			case 0:
			{
				for(new i = 20,d; i < 40;i++)
				{
					if(!DuelWeapon(i)) continue;
					pInfo[playerid][player_dialog_data][d] = i;
					d++;
					
					format(str512, sizeof str512, "%s%d\t %s\n", str512, i, GetWeaponNameEx(i));
				}
				Dialog_Show(playerid, DIALOG_EV_SELECT, DIALOG_STYLE_LIST, "• EventSystem •", str512, "Wybierz", "Zamknij");
			}
			case 1:
			{
				GetPlayerPos(playerid, aEData[ev_pos][0], aEData[ev_pos][1], aEData[ev_pos][2]);
				SendMessageEventPlayers("{b}%s (%d){/b} ustawi³ nowy spawn", playerNick(playerid), playerid);
				
				Dialog_Show(playerid, DIALOG_EV_SELECT, DIALOG_STYLE_MSGBOX, "• EventSystem •", "Ustawi³eœ nowy spawn czy chcesz teleportowaæ do niego wszystkich uczestników?", "Tak", "Nie");
			}
			case 2:
			{
				Dialog_Show(playerid, DIALOG_EV_SELECT, DIALOG_STYLE_INPUT, "• EventSystem •", "Wpisz model pojazdu (400-611)\n0 - blokowanie spawnu pojazdu.", "Wybierz", "Zamknij");
			}
			case 3:
			{
				if(aEData[ev_freezer])
				{
					foreach(new plx : EventPlayers) TogglePlayerControllable(plx, 1);
					
					SendMessageEventPlayers("{b}%s (%d){/b} odmrozi³ wszystkich", playerNick(playerid), playerid);
					aEData[ev_freezer] = false;
				}
				else {
					foreach(new plx : EventPlayers) TogglePlayerControllable(plx, 0);
					
					SendMessageEventPlayers("{b}%s (%d){/b} zamrozi³ wszystkich", playerNick(playerid), playerid);
					aEData[ev_freezer] = true;
				}
			}
			case 4:
			{
				if(aEData[ev_dropweapon])
				{
					 
					SendMessageEventPlayers("{b}%s (%d){/b} da³ mo¿liwoœæ u¿ywania broni na evecie", playerNick(playerid), playerid);
					aEData[ev_dropweapon] = false;
				}
				else {
					foreach(new plx : EventPlayers) ResetPlayerWeapons(plx);
					
					SendMessageEventPlayers("{b}%s (%d){/b} zabroni³ u¿ywania broni na evecie", playerNick(playerid), playerid);
					aEData[ev_dropweapon] = true;
				}
			}
			case 5:
			{
				foreach(new plx : EventPlayers) SetPlayerHealth(plx, 100.0);
					
				SendMessageEventPlayers("{b}%s (%d){/b} uzdrowi³ wszystkich", playerNick(playerid), playerid);
					
			}	
			case 6:
			{
				foreach(new plx : EventPlayers) SetPlayerArmour(plx, 100.0);
					
				SendMessageEventPlayers("{b}%s (%d){/b} uzdrowi³ wszystkich (kamizelka)", playerNick(playerid), playerid);
					
			}
			
		}
	}
	return 1;
}


Dialog:DIALOG_EV_SELECT(playerid, response, listitem, inputtext[])
{
	if(response){
	 
		switch(evPlayerSett[playerid])
		{
			case 0:
			{
 				aEData[ev_gun] = pInfo[playerid][player_dialog_data][listitem];
				aEData[ev_dropweapon] = false;
				
				foreach(new pl : EventPlayers)
				{
					ResetPlayerWeapons(pl);
					GivePlayerWeapon(pl, aEData[ev_gun], 555);
				}
				SendMessageEventPlayers("{b}%s (%d){/b} zmieni³ broñ na evencie {b}%s{/b}", playerNick(playerid), playerid, GetWeaponNameEx(pInfo[playerid][player_dialog_data][listitem]));
			}
			case 1:
			{
				foreach(new xplayerid : EventPlayers) SetPlayerPos(xplayerid, aEData[ev_pos][0] + random(3), aEData[ev_pos][1] + random(2), aEData[ev_pos][2] + 1.0);
				SendMessageEventPlayers("{b}%s (%d){/b} teleportowa³ wszystkich na spawn", playerNick(playerid), playerid);
			}
			case 2:
			{
				new model = strval(inputtext);
				
				if(model == 0)
				{
					aEData[ev_car] = 0;
					SendMessageEventPlayers("{b}%s (%d){/b} zablokowa³ mo¿liwoœæ spawnowania pojazdów na evencie", playerNick(playerid), playerid);
					return 1;
				}
				if(model > 611 || model < 400)
				{
					SendClientMessage(playerid, COLOR_ERROR, "Poda³eœ b³êdny model pojazdu");
					DialogFunc:DIALOG_EV_LIDER(playerid, 1, 2, inputtext);
					return 1;
				}
				aEData[ev_car] = model;
				SendMessageEventPlayers("{b}%s (%d){/b} zmieni³ model pojazdu na evencie {b}%s{/b} (spawn: /evcar)", playerNick(playerid), playerid, VehicleNames[model-400]);
			}
		}
	}
	return 1;
}

stock hookevent_OnPlayerConnect(playerid)
{
	if(Iter_Contains(d_d_players, playerid))
	{
		Iter_Remove(d_d_players, playerid);
 
	}
	if(Iter_Contains(h_y_players, playerid))
		Iter_Remove(h_y_players, playerid);
		
	if(Iter_Contains(d_f_players, playerid))
		Iter_Remove(d_f_players, playerid);
		
	ResetPlayerWeapons(playerid);
	 
	if(Iter_Contains(d_f_players, playerid))
	{
	    Iter_Remove(d_f_players, playerid);
		ResetPlayerWeapons(playerid);
		
 		SetPlayerVirtualWorld(playerid, 0);
  		TogglePlayerControllable(playerid, 1);
		 
  		if(Iter_Count(d_f_players) == 1)
  		{
			foreach (new u : d_f_players)
  		    {
  		        if(!IsPlayerConnected(u)) continue;
  		    	script_DF[winreed] = u;
  		    	break;
			}
  		}
 	}
	
	if(Iter_Contains(z_b_players, playerid))
		Iter_Remove(z_b_players, playerid);
		
		
	if(Iter_Contains(t_r_players, playerid))
		Iter_Remove(t_r_players, playerid);
		
		
	if(Iter_Contains(w_g_players, playerid)){
		Iter_Remove(w_g_players, playerid);
		 
	}
	
	if(Iter_Contains(c_h_players, playerid)){
		Iter_Remove(c_h_players, playerid);
		 
	}
	
	if(Iter_Contains(w_s_players, playerid))
	{
		Iter_Remove(w_s_players, playerid);
 	}
	return 1;
}

stock hookevent_OnPlayerDeath(playerid, killerid, reason)
{
	#pragma unused killerid
	#pragma unused reason
	duel_OnPlayerDeath(playerid, killerid);
	if(script_dd[statees] == true && Iter_Contains(d_d_players, playerid))
	{
		Iter_Remove(d_d_players, playerid);
 		SetPlayerVirtualWorld(playerid, 0);
  		TogglePlayerControllable(playerid, 1);
		
 		
		SetPlayerColorEx(playerid);
  		if(Iter_Count(d_d_players) == 1)
  		{ 
  		    foreach (new u : d_d_players)
  		    {
  		        if(!IsPlayerConnected(u)) continue;
  		    	script_dd[winreed] = u;
  		    	break;
			}
  		}
		  
  		return 1;
	}
	if(script_hy[statees] == true && Iter_Contains(h_y_players, playerid))
	{
		Iter_Remove(h_y_players, playerid);
 		SetPlayerVirtualWorld(playerid, 0);
  		TogglePlayerControllable(playerid, 1);
 
  		if(Iter_Count(h_y_players) == 1)
  		{ 
  		    foreach (new u : h_y_players)
  		    {
  		        if(!IsPlayerConnected(u)) continue;
  		    	script_hy[winreed] = u;
  		    	break;
			}
  		}
   		return 1;
	}
	if(script_os[statees] == true && Iter_Contains(o_s_players, playerid))
	{
		Iter_Remove(o_s_players, playerid);
 		SetPlayerVirtualWorld(playerid, 0);
  		TogglePlayerControllable(playerid, 1);
 
  		if(Iter_Count(o_s_players) == 1)
  		{ 
  		    foreach (new u : o_s_players)
  		    {
  		        if(!IsPlayerConnected(u)) continue;
  		    	script_os[winreed] = u;
  		    	break;
			}
  		}
   		return 1;
	}
	if(script_zb[statees] == true && Iter_Contains(z_b_players, playerid))
	{
		Iter_Remove(z_b_players, playerid);
 		SetPlayerVirtualWorld(playerid, 0);
  		TogglePlayerControllable(playerid, 1);
 
  		if(script_zb[bot_id] == playerid)
		{
			script_zb[winreed] = 501;
		}
   		return 1;
	}
	
	if(script_tr[statees] == true && Iter_Contains(t_r_players, playerid))
	{
		Iter_Remove(t_r_players, playerid);
		
   		return 1;
	}
	if(script_wg[statees] == true && Iter_Contains(w_g_players, playerid))
	{
		Iter_Remove(w_g_players, playerid);
		script_wg[team][script_wg[team_player][playerid]]--;
		SetPlayerColorEx(playerid);
		if(script_wg[team_player][playerid] == 0) script_wg[punkty][1]++;else script_wg[punkty][0]++;
 		SetPlayerVirtualWorld(playerid, 0);
  		TogglePlayerControllable(playerid, 1);
  
  		if(Iter_Count(w_g_players) == 1)
  		{ 
  		    foreach (new u : w_g_players)
  		    {
  		        if(!IsPlayerConnected(u)) continue;
  		    	script_wg[winreed] = u;
  		    	break;
			}
  		}
		UpdateEvStat();
  		return 1;
	}
	if(CTF[ctf_flag_carry] == playerid)
	{
		CTFFlagDown(playerid);
		SendClientMessageToAll(COLOR_INFO, "{FFFFFF} ›››{/b} Flaga na ziemi!");
	}
	if(script_ch[statees] == true && Iter_Contains(c_h_players, playerid))
	{
		Iter_Remove(c_h_players, playerid);
		script_ch[team][script_ch[team_player][playerid]]--;
			 
		if(script_ch[team_player][playerid] == 0) script_ch[punkty][1]++;else script_ch[punkty][0]++;
 		SetPlayerVirtualWorld(playerid, 0);
  		TogglePlayerControllable(playerid, 1);
 
		SetPlayerColorEx(playerid);
  		/*if(Iter_Count(c_h_players) == 1)
  		{ 
  		    foreach (new u : c_h_players)
  		    {
  		        if(!IsPlayerConnected(u)) continue;
  		    	script_ch[winreed] = u;
  		    	break;
			}
  		}*/
		statsUpdate = 11;
		UpdateEvStat();
  		return 1;
	}
	
	if(script_ws[statees] == true && Iter_Contains(w_s_players, playerid))
	{
	
 		Iter_Remove(w_s_players, playerid);
 		SetPlayerVirtualWorld(playerid, 0);
  		TogglePlayerControllable(playerid, 1);
 		DisablePlayerRaceCheckpoint(playerid);
  		return 1;
	}
	if(aEData[ev_lider] == playerid) return 1;
	if(Iter_Contains(EventPlayers, playerid))
	{
		SendMessageEventPlayers("{b}%s (%d){/b} zosta³ wyrzucony z eventu poniewa¿ zgin¹³", playerNick(playerid), playerid);
		
		Iter_Remove(EventPlayers, playerid);
 		SetPlayerVirtualWorld(playerid, 0);
  		TogglePlayerControllable(playerid, 1);
		
 		
		SetPlayerColorEx(playerid);
  		return 1;
	}
	#pragma unused reason
	return 1;
}

hookevent_OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason
	if(Iter_Contains(d_d_players, playerid))
	{
	    Iter_Remove(d_d_players, playerid);
 		SetPlayerVirtualWorld(playerid, 0);
  		TogglePlayerControllable(playerid, 1);
 	 
  		if(Iter_Count(d_d_players) == 1)
  		{
			foreach (new u : d_d_players)
  		    {
  		        if(!IsPlayerConnected(u)) continue;
  		    	script_dd[winreed] = u;
  		    	break;
			}
  		}
	}
	
	if(Iter_Contains(h_y_players, playerid))
	{
	    Iter_Remove(h_y_players, playerid);
		
 		SetPlayerVirtualWorld(playerid, 0);
  		TogglePlayerControllable(playerid, 1);
		 
  		if(Iter_Count(h_y_players) == 1)
  		{
			foreach (new u : h_y_players)
  		    {
  		        if(!IsPlayerConnected(u)) continue;
  		    	script_hy[winreed] = u;
  		    	break;
			}
  		}
 	}
	
	
	if(Iter_Contains(o_s_players, playerid))
	{
	    Iter_Remove(o_s_players, playerid);
		
 		SetPlayerVirtualWorld(playerid, 0);
  		TogglePlayerControllable(playerid, 1);
		 
  		if(Iter_Count(o_s_players) == 1)
  		{
			foreach (new u : o_s_players)
  		    {
  		        if(!IsPlayerConnected(u)) continue;
  		    	script_os[winreed] = u;
  		    	break;
			}
  		}
 	}
	
	if(Iter_Contains(z_b_players, playerid))
	{
	    Iter_Remove(z_b_players, playerid);
		
 		SetPlayerVirtualWorld(playerid, 0);
  		TogglePlayerControllable(playerid, 1);
		if(script_zb[bot_id] == playerid)
		{
			script_zb[winreed] = 501;
		}	 

 	}
	
	if(Iter_Contains(t_r_players, playerid))
	{
	    Iter_Remove(t_r_players, playerid);
 	}
	
	if(Iter_Contains(w_g_players, playerid))
	{
	    Iter_Remove(w_g_players, playerid);
		script_wg[team][script_wg[team_player][playerid]]--;
		SetPlayerVirtualWorld(playerid, 0);
  		TogglePlayerControllable(playerid, 1);
		if(script_wg[team_player][playerid] == 0) script_wg[punkty][1]++;else script_wg[punkty][0]++;
  		if(Iter_Count(w_g_players) == 1)
  		{
			foreach (new u : w_g_players)
  		    {
  		        if(!IsPlayerConnected(u)) continue;
  		    	script_wg[winreed] = u;
  		    	break;
			}
  		}
		UpdateEvStat();
	}
	
	if(CTF[ctf_flag_carry] == playerid)
	{
		CTFFlagDown(playerid);
		SendClientMessageToAll(-1, "{008ae6} ›››{/b} Flaga na ziemi!");
	}
	CTF[ctf_team][playerid] = 0;
	CTF[ctf_member][playerid] = false;
	
	if(Iter_Contains(c_h_players, playerid))
	{
	    Iter_Remove(c_h_players, playerid);
		script_ch[team][script_ch[team_player][playerid]]--;
		SetPlayerVirtualWorld(playerid, 0);
  		TogglePlayerControllable(playerid, 1);
		if(script_ch[team_player][playerid] == 0) script_ch[punkty][1]++;else script_ch[punkty][0]++;
  		/*if(Iter_Count(c_h_players) == 1)
  		{
			foreach (new u : c_h_players)
  		    {
  		        if(!IsPlayerConnected(u)) continue;
  		    	script_ch[winreed] = u;
  		    	break;
			}
  		}*/
 	}
	
	if(script_ws[statees] == true && Iter_Contains(w_s_players, playerid))
	{
 		Iter_Remove(w_s_players, playerid);
 		SetPlayerVirtualWorld(playerid, 0);
  		TogglePlayerControllable(playerid, 1);
 		DisablePlayerRaceCheckpoint(playerid);
  		return 1;
	}
	
	
	
	
	if(aEData[ev_lider] == playerid)
		ClearEvent();
	if(Iter_Contains(EventPlayers, playerid))
	{
		SendMessageEventPlayers("{b}%s (%d){/b} zosta³/a wyrzucony z eventu poniewa¿ wyszed³/a z serwera", playerNick(playerid), playerid);
		
		Iter_Remove(EventPlayers, playerid);
 		SetPlayerVirtualWorld(playerid, 0);
  		TogglePlayerControllable(playerid, 1);
		
 		
		SetPlayerColorEx(playerid);
  		return 1;
	}
	
	
	
	UpdateEvStat();
	return 1;
}

stock hookevent_OnPlayerSpawn(playerid)
{
	g_OnPlayerSpawn(playerid);
	TextDrawShowForPlayer(playerid, AnnDraw2);
	if(script_zb[bot_id] == playerid && playerid != 0) 
	{
		AttachObjectToPlayer(script_zb[b_object], 0, 0.0, 0.0, 12.65, 0.0, 0.0, 0.0);
		script_zb[bot_id] = 0;
	}
	if(aEData[ev_lider] == playerid && aEData[ev_started]) return SetPlayerEvent(playerid),1;
 
 
	return 1;
}

 
 