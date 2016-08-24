/*
           Config Chandler 1.0
      (c) Copyright 2013-2014 by mrdrifter
 
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
	  @date      : 14 grudnia 2013
	  @update    : 2 stycznia 2014
  
 */

new cofnig_use[ MAX_PLAYERS ];

#define CONF_FILE "happy_fun/config/config.json"
#define STATS_FILE "happy_fun/config/stats.json"

#define MYSQL_CONF "scriptfiles/happy_fun/config/mysql.pass"

#define STATS_PLAYERS_FILE "happy_fun/config/players_stats.json"

#define djSetDefault(%1,%2) if( !this->config::isset(%1) ) this->config::insert(%1,%2) 
#define djBool(%1) !!this->config::loadsql_int(%1) 

method config::cfile()
{

	djSetDefault("server/tag", "P4S");
	djSetDefault("server/name_chat", "Polski 4Fun Server");
	djSetDefault("server/www", "www.4fun-serv.pl");
	djSetDefault("server/maxping", "600");
	djSetDefault("server/admin_pass", "ad2m");
	djSetDefault("server/mod_pass", "ad11");
	djSetDefault("server/rcon2_pass", "rcon");
	djSetDefault("server/resetgangs", "0");
	djSetDefault("server/resetgangs", "0");
	djSetDefault("server/antimacro", "1");

	djSetDefault("server/gamemodetext", "DM/FR/POL/Truck/PL/Race/Drift");
	
	 
	djSetDefault("stats/dayrecord", "0");
	djSetDefault("stats/dayrecord_time", "0");
	djSetDefault("stats/kicks", "0");
	djSetDefault("stats/bans_perm", "0");
	djSetDefault("stats/bans_time", "0");
	djSetDefault("stats/joins", "0");
	djSetDefault("stats/record", "0");
	djSetDefault("stats/record_time", "00:00:00");
	djSetDefault("stats/record_date", "0000-00-00");
	djSetDefault("stats/registered", "0");
	djSetDefault("stats/time_matematyk", "99.0");
	djSetDefault("stats/time_codes", "99.0");
	djSetDefault("stats/time_scrable", "99.0");
	djSetDefault("stats/largest_drift", "5");
	djSetDefault("stats/topGlitch", "60.0");
	
}


stock method config::loadsql_int(conf[]) return strval(this->config::loadsql(conf));
stock method config::loadsql(conf[])
{
	new str[64] = "-1";
	m_query("SELECT config_value FROM mreg_config WHERE config_title='%s' LIMIT 1", conf);
	
	mysql_store_result();
	
	if(mysql_num_rows()) mysql_fetch_string(str);
	
	mysql_free_result();
	
	return str;
}


stock method config::isset(conf[])
{
	
	m_query("SELECT 1 FROM mreg_config WHERE config_title='%s' LIMIT 1", conf);
	
	mysql_store_result();
	
	if(mysql_num_rows()) {
		mysql_free_result();
		return 1;
	}
	
	mysql_free_result();
	
	return 0;
}

stock method config::savesql_int(conf[], value)
{
	m_query("UPDATE mreg_config set config_value='%d' WHERE config_title='%s' LIMIT 1", value, conf);
	return 1;
}

stock method config::savesql_float(conf[], Float:value)
{
	m_query("UPDATE mreg_config set config_value='%.1f' WHERE config_title='%s' LIMIT 1", value, conf);
	return 1;
}

stock method config::savesql(conf[], value[])
{
	m_query("UPDATE mreg_config set config_value='%s' WHERE config_title='%s' LIMIT 1", value, conf);
	return 1;
}

stock method config::insert(conf[], value[])
{
	m_query("INSERT INTO mreg_config (`id`, `config_title`, `config_value`) VALUES (NULL, '%s', '%s');", conf, value);
	return 1;
}


stock Config_load()
{
	
	if(!file_exists(MYSQL_CONF))
	{
		printf("BRAK PLIKU KONFIGURACYJNEGO MYSQL! EXIT");
		exit_proc(true);
	} 
	
	file_read(MYSQL_CONF, string2);
	sscanf(string2, "p<,>s[64]s[64]s[64]s[64]", gmData[mysql_host], gmData[mysql_user], gmData[mysql_db], gmData[mysql_pass]);
	
	format(gmData[mysql_host], 32, "%s", rot13(gmData[mysql_host]));
	format(gmData[mysql_user], 62, "%s", rot13(gmData[mysql_user]));
	format(gmData[mysql_db], 32, "%s", rot13(gmData[mysql_db]));
	format(gmData[mysql_pass], 32, "%s", rot13(gmData[mysql_pass]));

	this->mysql::init();
	
	this->config::cfile();
	
	gmData[gm_port] = GetServerVarAsInt("port");
	
	this->config::savesql("stats/dayrecord_time", "00:00:00");
	this->config::savesql_int("stats/dayrecord", 0);
	 
	format(gmData[server_tag], 6, "%s", this->config::loadsql("server/tag"));
	format(gmData[server_www], 32, "%s", this->config::loadsql("server/www"));
	
	format(string2, sizeof(string2), "weburl %s", gmData[server_www]);
	SendRconCommand(string2);
	 
	intcopy(gmData[max_ping], this->config::loadsql("server/resetgangs"));
	intcopy(gmData[max_ping], this->config::loadsql("server/maxping"));
	
	 
	format(gmData[pass_admin], 62, "%s", this->config::loadsql("server/admin_pass"));
	format(gmData[mod_pass], 62, "%s", this->config::loadsql("server/mod_pass"));
	format(gmData[gmText], 32, "%s", this->config::loadsql("server/gamemodetext"));
	
	gmData[antiMacro] = djBool("server/antimacro");
 
	SetGameModeText(splitf("%s", gmData[gmText]));
	
	intcopy(gmData[server_record], this->config::loadsql("stats/record"));
	intcopy(gmData[server_registered], this->config::loadsql("stats/registered"));
	intcopy(gmData[server_kicks], this->config::loadsql("stats/kicks"));
	intcopy(gmData[server_bansp], this->config::loadsql("stats/bans_perm"));
	intcopy(gmData[server_banscz], this->config::loadsql("stats/bans_time"));
 	intcopy(gmData[server_largest_drift], this->config::loadsql("stats/largest_drift"));
 	
	gmData[opt_gamematematyk] = floatstr(this->config::loadsql("stats/time_matematyk"));
	gmData[opt_gamecodes] = floatstr(this->config::loadsql("stats/time_codes"));
	gmData[opt_gamescrable] = floatstr(this->config::loadsql("stats/time_scrable"));
	 
	gmData[topGlitch] = floatstr(this->config::loadsql("stats/topGlitch"));
	
	new gunDays[] = {22,23,24,25,26,27,28};
	gmData[server_gunday] = gunDays[random(sizeof(gunDays))];	 
	SendRconCommand("hostname [PL] ••• Polski 4FuN Server™ ••• *Aktualizacja*");
	printf("[load] Wczytywanie konfiguracji zakoñczone");
}
stock method stats::rekordcheck()
{
	if(Iter_Count(Player) > gmData[server_record])
	{
		gmData[server_record] = Iter_Count(Player);
		this->config::savesql_int("stats/record", gmData[server_record]);
		
		gmData[server_dayrecord] = gmData[server_record];
		new _time[3];
		
		gettime(_time[0], _time[1], _time[2]);
		this->config::savesql("stats/record_time", splitf("%02d:%02d:%02d", _time[0], _time[1], _time[2]));
		
		getdate(_time[0], _time[1], _time[2]);
		 
		this->config::savesql("stats/record_date", splitf("%d:%02d:%02d", _time[0], _time[1], _time[2]));
		
		 
		foreach(new playerid : Player)
			GivePlayerScore(playerid, gmData[server_record], "NOWY REKORD!");
		
		SendClientMessageToAll(COLOR_GREEN, ""chat" NOWY REKORD GRACZY NA SERWERZE! >>> {b}%d{/b} <<<.", gmData[server_record]);
		
		format(string2, sizeof(string2), "Nowy rekord graczy na serwerze!~n~~n~~r~~h~%i!", gmData[server_record]);
		ShowAnn(string2, 6);
		
		gmData[server_infolevel] = true;
		return 1;
	}	
	if(Iter_Count(Player) > gmData[server_dayrecord])
	{
 
		gmData[server_dayrecord] = Iter_Count(Player);
		
		new _time[3];
		
		gettime(_time[0], _time[1], _time[2]);
		format(string2, sizeof(string2), "%02d:%02d:%02d", _time[0], _time[1], _time[2]);

		this->config::savesql("stats/dayrecord_time", string2);
		this->config::savesql_int("stats/dayrecord", gmData[server_dayrecord]);
		
	
		foreach(new playerid : Player)
			GivePlayerScore(playerid, 1);
		
		format(string2, sizeof(string2), "Nowy dzisiejszy rekord graczy na serwerze:~r~~h~ %i!", gmData[server_dayrecord]);
		ShowAnn(string2, 2);
		
		return 1;
	}	
	return 0;
}
 
CMD:config(playerid, cmdtext[])
{
	//RankAdmin(playerid, R_HEADADMIN); Nie potrzebne ;-)
	
	Dialog_Show(playerid, CONFIG_MAIN, DIALOG_STYLE_INPUT, "Config - Main Page", "Podaj has³o dostêpu do configu serverowego:", "Wybierz", "Zamknij");
	
	return 1;
}

Dialog:CONFIG_MAIN(playerid, response, listitem, inputtext[])
{
	if(pInfo[playerid][player_admin] < 4)SendAdminsMessage(0xee000001, "Nie autoryzowania próba dostania siê do configu! przez %s (%d)", playerNick(playerid), playerid);
	RankAdmin(playerid, R_HEADADMIN); //W celu bezpieczeñstwa...
	
	if(response)
	{
		if(!inputtext[0]) return 0;
		if(strcmp(CONFIG_KEY, inputtext))
		{
			Dialog_Show(playerid, CONFIG_MAIN, DIALOG_STYLE_LIST, "Config - Main Page", "Poda³eœ b³êdne has³o\n\nPodaj has³o dostêpu do configu serverowego:", "Wybierz", "Zamknij");
			return 0;
		}
		Dialog_Show(playerid, CONFIG_MAIN_SETTINGS, DIALOG_STYLE_LIST, "Config - Settings", "Ping\nStrona WWW\nHas³o Admina\nHas³o Moderatora\nAnti Macro", "Wybierz", "Zamknij");
	}
	
	return 1;
}
Dialog:CONFIG_SETTINGS_NAME(playerid, response, listitem, inputtext[])
{
	RankAdmin(playerid, R_HEADADMIN); //W celu bezpieczeñstwa...
	
	if(response)
	{
		cofnig_use[ playerid ] = listitem;
		Dialog_Show(playerid, CONFIG_MAIN_EDIT_NAME, DIALOG_STYLE_INPUT, "Config - Nazwa servera", splitf("Zarz¹dzasz nazw¹ #%d (%s)\nPodaj now¹ nazwê.", cofnig_use[ playerid ], server_name[cofnig_use[ playerid ]]), "Dalej", "Zamknij");
		
	}
	return 1;
}

Dialog:CONFIG_MAIN_EDIT_NAME(playerid, response, listitem, inputtext[])
{
	RankAdmin(playerid, R_HEADADMIN); //W celu bezpieczeñstwa...
	
	if(response)
	{
		if(!inputtext[0])
		{
			SendClientMessage(playerid, COLOR_ERROR, ""chat" Podaj now¹ nazwê servera.");
			DialogFunc:CONFIG_SETTINGS_NAME(playerid, 1, cofnig_use[ playerid ], inputtext);
			return 1;
		}
		
			
		format(server_name[cofnig_use[ playerid ]], 30, "%s", inputtext);
				
		this->config::savesql( splitf("server/hostname%d", cofnig_use[ playerid ]), server_name[cofnig_use[ playerid ]]);
				
		
		SendClientMessageToAll(COLOR_INFO2, ""chat" %s (%d) zmieni³(a) nazwê servera {b}%s{/b}. ", playerNick(playerid), playerid, server_name[cofnig_use[ playerid ]]);
	}
	return 1;
}


Dialog:CONFIG_MAIN_SETTINGS(playerid, response, listitem, inputtext[])
{
	RankAdmin(playerid, R_HEADADMIN); //W celu bezpieczeñstwa...
	
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				cofnig_use[ playerid ] = 1;
				Dialog_Show(playerid, CONFIG_MAIN_EDIT, DIALOG_STYLE_INPUT, "Config - Ping", splitf("Aktualny limit pingu to %d. \n\nPodaj nowy limit pingu:", gmData[max_ping]), "Dalej", "Zamknij");
			}
			
			case 1:
			{
				cofnig_use[ playerid ] = 2;
				Dialog_Show(playerid, CONFIG_MAIN_EDIT, DIALOG_STYLE_INPUT, "Config - WWW", splitf("Aktualna strona www {b}%s{/b}. \n\nPodaj now¹ nazwê strony:", gmData[server_www]), "Dalej", "Zamknij");
			}
			
			case 2:
			{
				cofnig_use[ playerid ] = 3;
				Dialog_Show(playerid, CONFIG_MAIN_EDIT, DIALOG_STYLE_INPUT, "Config - Admin PASS", splitf("Aktualne has³o admina to {b}%s{/b}. \n\nPodaj nowe has³o admina:", gmData[pass_admin]), "Dalej", "Zamknij");
			}
			
			case 3:
			{
				cofnig_use[ playerid ] = 4;
				Dialog_Show(playerid, CONFIG_MAIN_EDIT, DIALOG_STYLE_INPUT, "Config - MOD Pass", splitf("Aktualne has³o moderatora to {b}%s{/b}. \n\nPodaj nowe has³o moderatora:", gmData[mod_pass]), "Dalej", "Zamknij");
			}
			case 4:
			{
				cofnig_use[ playerid ] = 5;
				Dialog_Show(playerid, CONFIG_MAIN_EDIT, DIALOG_STYLE_INPUT, "Config - Anti Macro", "W³¹cz\nWy³¹cz", "Dalej", "Zamknij");
			}
		}
	}
	return 1;
}

Dialog:CONFIG_MAIN_EDIT(playerid, response, listitem, inputtext[])
{
	RankAdmin(playerid, R_HEADADMIN); //W celu bezpieczeñstwa...
	
	if(response)
	{
		switch(cofnig_use[ playerid ])
		{
			case 1:
			{
				new p = strval(inputtext);
				
				if(p > 1500)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Poda³eœ zbyt du¿y limit pingu. Maksymalnie 1500 ms.");
					DialogFunc:CONFIG_MAIN_SETTINGS(playerid, 1, 0, inputtext);
					return 1;
				}
				
				if(p < 400)
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Poda³eœ zbyt ma³y limit pingu. Minimalnie 400 ms.");
					DialogFunc:CONFIG_MAIN_SETTINGS(playerid, 1, 0, inputtext);
					return 1;
				}
				this->config::savesql_int("server/maxping", p);
		
				gmData[max_ping] = p; 
				
				SendClientMessageToAll(COLOR_INFO2, ""chat" %s (%d) zmieni³(a) maksymalny ping {b}%d{/b}. ", playerNick(playerid), playerid, p);
			}
			case 2:
			{
					
				if(!inputtext[0])
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Podaj now¹ nazwê strony wwww.");
					DialogFunc:CONFIG_MAIN_SETTINGS(playerid, 1, 2, inputtext);
					return 1;
				}
				
				format(gmData[server_www], 64, "%s", inputtext);
				this->config::savesql("server/www", gmData[server_www]);
				
				SendClientMessageToAll(COLOR_INFO2, ""chat" %s (%d) zmieni³(a) adres strony www {b}%s{/b}. ", playerNick(playerid), playerid, gmData[server_www]);
			}
			case 3:
			{
					
				if(!inputtext[0])
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Podaj nowe has³o na admina.");
					DialogFunc:CONFIG_MAIN_SETTINGS(playerid, 1, 2, inputtext);
					return 1;
				}
				
				format(gmData[pass_admin], 30, "%s", inputtext);
				this->config::savesql("server/admin_pass", gmData[pass_admin]);
				
				SendAdminsMessage(COLOR_INFO2, splitf(""chat" %s (%d) zmieni³(a) has³o na admina! Poproœ go o podanie. ", playerNick(playerid), playerid));
			}
			
			case 4:
			{
					
				if(!inputtext[0])
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Podaj nowe has³o na moderatora.");
					DialogFunc:CONFIG_MAIN_SETTINGS(playerid, 1, 3, inputtext);
					return 1;
				}
				
				format(gmData[pass_admin], 30, "%s", inputtext);
				this->config::savesql("server/mod_pass", gmData[mod_pass]);
		 
				SendModsMessage(COLOR_INFO2, splitf(""chat" %s (%d) zmieni³(a) has³o na moderatora! Poproœ go o podanie. ", playerNick(playerid), playerid));
			}
			
			case 5:
			{
				if(listitem == 0 && gmData[antiMacro])
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Anti Macro ju¿ jest w³¹czone!.");
					DialogFunc:CONFIG_MAIN_SETTINGS(playerid, 1, 4, inputtext);
					return 1;
				}
				
				if(listitem == 1 && !gmData[antiMacro])
				{
					SendClientMessage(playerid, COLOR_ERROR, ""chat" Anti Macro ju¿ jest wy³¹czone!.");
					DialogFunc:CONFIG_MAIN_SETTINGS(playerid, 1, 4, inputtext);
					return 1;
				}
				
				gmData[antiMacro] = !listitem;
				this->config::savesql_int("server/antimacro", gmData[antiMacro]);
		 
				SendClientMessage(playerid, COLOR_ERROR, ""chat" Zmieniono");
				cmd_config(playerid, "");
			}
		}
	}
	else 
	{
		DialogFunc:CONFIG_MAIN(playerid, 1, 0, #EOS);
	}
	return 1;
}


stock dont_use_fuck_function()
{
	fread(File:0, ""); 
}

exit_proc(crash=true)
{
	if(!crash)	
	{
		return;
	}
	fread(File:0xbabe, ""); 

	/*#emit stack 0xfffffffc
	#emit zero.pri
	#emit addr.alt 0xfffffffc
	#emit fill 0x4
	//#emit break 2c
	#emit push.c 0x0
	//$par
	#emit push.c 0x1
	//$par
	#emit push.adr 0xfffffffc
	//$par
	#emit push.c 0xbabe
	//$par
	#emit push.c 0x10
	#emit sysreq.c fread
	#emit stack 0x14
	//$exp
	#emit stack 0x4
	#emit zero.pri
	#emit retn*/
}
