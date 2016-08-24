/*
          Gangs [2.2]
      (c) Copyright 2013-2014 by mrdrifter
 
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
	  @date      : 16 grudnia 2013
	  @update    : 3 stycznia 2014
  
  
  
  //TODO:
	-dodac date stworzenia do sql

 */  
 
#define GANGS_WOJNA_MINPLAYERS 1
 
stock LoadGangs()
{
	
	Iter_Clear(Gangs);
	loaded_gang_glob = 0;
 
	if(this->config::loadsql_int("resetgangs") < gettime() && GetServerVarAsInt("port") == server_port)
	{
		ClearGangsRespect();
	}
	
	strcat(gInfo[0][gangNazwa], "Brak");
	
	mysql_query("SELECT *, (SELECT COUNT( * ) FROM "prefix"_players WHERE gang = g.id) AS gUsers FROM "prefix"_gangs g ORDER BY g.Points DESC");
	mysql_store_result();
	new gang = 0, czas = GetTickCount(), color[32];
	for(new i;i<mysql_num_rows();i++)
	{
		mysql_data_seek(i);//
		mysql_fetch_row_data();
		
		gang++;
		//gang = mysql_fetch_field_int("id");
		
		Iter_Add(Gangs, gang);
		
		gInfo[gang][gangid] = mysql_fetch_field_int("id");
		gInfo[gang][gangSpawn][0] = mysql_fetch_field_float("spX");
		gInfo[gang][gangSpawn][1] = mysql_fetch_field_float("SPY");
		gInfo[gang][gangSpawn][2] = mysql_fetch_field_float("spZ");
		
		gInfo[gang][gangPoints] = mysql_fetch_field_int("Points");
		gInfo[gang][gangSlots] = mysql_fetch_field_int("max_users");
		gInfo[gang][gangUsers] = mysql_fetch_field_int("gUsers");
		gInfo[gang][gangCv] = mysql_fetch_field_int("Cv");
		gInfo[gang][gangPojazd] = mysql_fetch_field_int("Pojazd");
		gInfo[gang][gangSkin] = mysql_fetch_field_int("Skin");
		gInfo[gang][gangColor] = mysql_fetch_field_int("Color");
 		 
		LoadGangObjects(gang, gInfo[gang][gangid]);
		
		mysql_fetch_field("Color", color);
		sscanf(color, "x", gInfo[gang][gangColor]);
	
		mysql_fetch_field("Nazwa", gInfo[gang][gangNazwa]);
		mysql_fetch_field("StronaWWW", gInfo[gang][gangWww]);
 		mysql_fetch_field("Tag", gInfo[gang][gangTag]);
		mysql_fetch_field("Time_Created", gInfo[gang][gangDateCreated]);
		
		if(GangStringValidate(gInfo[gang][gangNazwa])) GangRemoveValidateString(gInfo[gang][gangNazwa]);
		if(GangStringValidate(gInfo[gang][gangTag])) GangRemoveValidateString(gInfo[gang][gangTag]);
		if(GangStringValidate(gInfo[gang][gangWww])) GangRemoveValidateString(gInfo[gang][gangWww]);
		
		
		CreateGangTextdraws(gang);


		gInfo[gang][active] = true;
		
		loaded_gang_glob++;
	}
	printf("[load] wczytanych gangów:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	mysql_free_result();
	//clearDynamicGangs();
	
	foreach(new i : Gangs)
	{
		new o = GetPlayerAbsentDays(gangSzefLastOnline(gInfo[i][gangid]));
		if(o > 7) 
		{
			i = DeleteGang(i);
			continue;
		}
	}
	
	foreach(new playerid : Player)
	{
		GangPlayer(playerid);
	}
	return 1;
}

stock CreateGangTextdraws(gang)
{
	gInfo[gang][gangTextdraw] = TextDrawCreate(546.888977, 267.804565, "Online: ~n~~g~~h~VisztaPL~n~~g~~h~Lady.M~n~~g~~h~pnkz~n~~r~~h~UFO~n~~h~~r~~h~tdw.lyszka~n~~r~~h~1234567890abcdefghij");
	TextDrawLetterSize(gInfo[gang][gangTextdraw], 0.147773, 0.728886);
	TextDrawTextSize(gInfo[gang][gangTextdraw], 638.222595, 11.448945);
	TextDrawAlignment(gInfo[gang][gangTextdraw], 1);
	TextDrawColor(gInfo[gang][gangTextdraw], -1);
	TextDrawUseBox(gInfo[gang][gangTextdraw], true);
	TextDrawBoxColor(gInfo[gang][gangTextdraw], 80);
	TextDrawSetShadow(gInfo[gang][gangTextdraw], 0);
	TextDrawSetOutline(gInfo[gang][gangTextdraw], 0);
	TextDrawBackgroundColor(gInfo[gang][gangTextdraw], 16);
	TextDrawFont(gInfo[gang][gangTextdraw], 1);
	TextDrawSetProportional(gInfo[gang][gangTextdraw], 1);	
}
stock ClearGangsRespect()
{
	printf("clear exp");
 
	if(this->config::loadsql_int("resetgangs") > gettime()) return 1;
 
	this->config::savesql_int("resetgangs", gettime() + 5356800);
	
	printf("clear exp");
	Iter_Clear(Gangs);
	loaded_gang_glob = 0;
	
	mysql_query("SELECT *, (SELECT COUNT( * ) FROM "prefix"_players WHERE gang = g.id) AS gUsers FROM "prefix"_gangs g order by g.Points desc");
	mysql_store_result();
	new gang = 0, giversp = 3000;
	printf("clear exp");
	new queres[MAX_GANG2][2][256];
	
	for(new i;i<mysql_num_rows();i++)
	{
		mysql_data_seek(i);//
		mysql_fetch_row_data();
		
		gang++;
		//gang = mysql_fetch_field_int("id");
		
		Iter_Add(Gangs, gang);
		
		gInfo[gang][gangid] = mysql_fetch_field_int("id");
		 
		gInfo[gang][gangPoints] = mysql_fetch_field_int("Points");
		gInfo[gang][gangUsers] = mysql_fetch_field_int("gUsers");
		
		new scorePlayers;
		scorePlayers = gInfo[gang][gangPoints]/gInfo[gang][gangUsers];
		if(giversp>0) scorePlayers += giversp;
		
		if(scorePlayers <= 0) scorePlayers = 1;
		
		format(queres[gang][0], 254, "update "prefix"_gangs set Points=0, SumPoints=SumPoints+%d where id=%d", gInfo[gang][gangPoints], gInfo[gang][gangid]);
		format(queres[gang][1], 254, "update "prefix"_players set score=score+%d where gang=%d", scorePlayers, gInfo[gang][gangid]);
		if(giversp>0) giversp -= 1000;
		 

	}
	printf("clear exp11");
	for(new i;i<gang;i++){
		
		printf(queres[i][0]);
		printf(queres[i][1]);
		mysql_query(queres[i][0]);
		mysql_query(queres[i][1]);
	}

	return 1;
}
stock LoadGangsZones()
{
	mysql_query("SELECT * FROM "prefix"_gangs_zone limit "#MAX_GANGS_ZONES"");
	mysql_store_result();
	
	foreach(new zones : GangsZones)
	{
		DestroyDynamicArea(gZone[zones][zonestream]); 
		GangZoneDestroy(gZone[zones][zonegz]);
	}
	Iter_Clear(GangsZones);
	#define zone z0@ne
	new zone = 0, czas = GetTickCount(), tgid, zoneid;
	for(new i;i<mysql_num_rows();i++)
	{
		mysql_data_seek(i);//
		mysql_fetch_row_data();
		
		gZone[zone][zonegangid] = mysql_fetch_field_int("gang");
		zoneid = mysql_fetch_field_int("id");
		gZone[zone][zone_id] = zoneid;
		tgid = GetGangFromUid(gZone[zone][zonegangid]);
		
		if(!tgid) 
		{
			printf("GangZones removed zone undefined gang");
			m_query("delete from "prefix"_gangs_zone where id=%d limit 1;", zoneid);
			
			continue;
		}
		Iter_Add(GangsZones, zone);
		
		mysql_fetch_field("zone", string2);
		sscanf(string2, "p<,>a<f>[4]", gZone[zone][zonegangSpawn]);
		
		gZone[zone][zonestream] = CreateDynamicRectangle(gZone[zone][zonegangSpawn][0], gZone[zone][zonegangSpawn][1], gZone[zone][zonegangSpawn][2], gZone[zone][zonegangSpawn][3]);		
		gZone[zone][zonegz] = GangZoneCreate(gZone[zone][zonegangSpawn][0], gZone[zone][zonegangSpawn][1], gZone[zone][zonegangSpawn][2], gZone[zone][zonegangSpawn][3]);
		
		gZone[zone][zonecolor] = SetAlpha(gInfo[GetGangFromUid(gZone[zone][zonegangid])][gangColor], 190);
		
		zone++;
		
	}
	#undef zone
	
	foreach(new zones : GangsZones)
	{
		foreach(new playerid : Player)
			GangZoneShowForPlayer(playerid, gZone[zones][zonegz], gZone[zones][zonecolor]);
 	}
	
	printf("[load] wczytanych stref gangów:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	mysql_free_result();

	return 1;
}
	
stock LoadGangObjects(gid, obj)
{
	new xfile[64];
	format(xfile, sizeof(xfile), "happy_fun/object/gbases/%d.txt", obj);
	clarsplitf;
	
	if (!fexist("happy_fun/object/gbases")) 
	{
		printf("brak folderu: happy_fun/object/gbases ");
		return 1;
	}
	
	if (!fexist(xfile)) 
	{
		return 1;
	}
	new File:cfg=fopen(xfile, io_read);
    new string[256], load=0;
	new str[2][64+16];
	if(cfg)
	{
		while(fread(cfg, string)) 
		{
			if(load > 501) 
			{
				printf("Limit obiektów w pliku %s przekroczony!", splitf("happy_fun/object/gbases/%d", obj));
				break;
			}
			if (this->obiect::check(string)) load++;
		
			if(strfind(string, "=") != -1)
			{
				if (!sscanf(string, "p<=>s[32]s[80]", str[0], str[1]))
				{
					
					if (!strcmp(str[0], "komenda")) 
					{
						new find = strfind(str[1], "||");
						if(find != -1){
							strdel(str[1], find, strlen(str[1]));
							format(gInfo[gid][gangBaza_Cmd], 16, "%s", str[1]);
							
							format(string2, sizeof(string2), "gangbaza/%s", gInfo[gid][gangBaza_Cmd]);
							Plugin_SaveIntData(MAP_VEHICLES, string2, gid);
						}
					}
					
					if (!strcmp(str[0], "brama_closed")) sscanf(str[1], "p<,>a<f>[6]", gInfo[gid][gangBaza_Close]);
					if (!strcmp(str[0], "brama_open")) sscanf(str[1], "p<,>a<f>[6]", gInfo[gid][gangBaza_Open]);
					if (!strcmp(str[0], "brama_model")) gInfo[gid][gangBaza_Model] = strval(str[1]);
					 
				}
			}
			
		}
	}// else printf("[load::gbazy] not cfg");
	if(gInfo[gid][gangBaza_Close][0] && gInfo[gid][gangBaza_Close][1] && gInfo[gid][gangBaza_Close][2] && gInfo[gid][gangBaza_Model])
		gInfo[gid][gangBaza_ID] = CreateDynamicObject(gInfo[gid][gangBaza_Model], gInfo[gid][gangBaza_Close][0], gInfo[gid][gangBaza_Close][1], gInfo[gid][gangBaza_Close][2], gInfo[gid][gangBaza_Close][3], gInfo[gid][gangBaza_Close][4], gInfo[gid][gangBaza_Close][5], -1, 0, -1, 300.0);
	
	//printf("za³adowano obiekty gangu id %d wczytanych obiektów %d brama %d. komenda %s", gInfo[gid][gangid], load, gInfo[gid][gangBaza_ID], gInfo[gid][gangBaza_Cmd]);
	return 1;
}


stock CheckGangCmd(playerid, cmdtext[])
{
	new id;
	#define gid id
	
	format(string2, sizeof(string2), "gangbaza/%s", cmdtext);
	if( (id=Plugin_GetIntData(MAP_VEHICLES, string2), id) )
	{
		if( !gInfo[id][gangBaza_ID] ) return 0;
		
		if(pInfo[playerid][player_gang] != id) return SendClientMessage(playerid, COLOR_ERROR, "Nie masz uprawieñ do otwierania tej bazy!");
		if(!gInfo[id][gangBaza_Status])
		{
			MoveDynamicObject(gInfo[id][gangBaza_ID], gInfo[gid][gangBaza_Open][0], gInfo[gid][gangBaza_Open][1], gInfo[gid][gangBaza_Open][2], 2.0, gInfo[gid][gangBaza_Open][3], gInfo[gid][gangBaza_Open][4], gInfo[gid][gangBaza_Open][5]);
			
			gInfo[id][gangBaza_Status]=true;
			SendClientMessage(playerid, COLOR_INFO, "Brama zostala otwarta");
		} else {
			MoveDynamicObject(gInfo[id][gangBaza_ID], gInfo[gid][gangBaza_Close][0], gInfo[gid][gangBaza_Close][1], gInfo[gid][gangBaza_Close][2], 2.0, gInfo[gid][gangBaza_Close][3], gInfo[gid][gangBaza_Close][4], gInfo[gid][gangBaza_Close][5]);
			
			gInfo[id][gangBaza_Status]=false;
			SendClientMessage(playerid,COLOR_INFO2,"Brama zostala zamknieta");
		}
		return 1;
	} 
	#undef gid
	return 0;
}

/** Testowe komendy do tworzenia zonów! oficjalnie prawdopodobnie bêdzie ka¿dy móg³ zrobiæ gangzone **/ 

CMD:cgangzonestop(playerid, pl[])
{
	if(zone_create[zone_step] == 0)
	{
		SendClientMessage(playerid, 0xFF0000FF, "Wpisz /cgangzone aby dodaæ zone");
		return 1;
	}
	zone_create[zone_minx]=0;
	zone_create[zone_miny]=0;
	zone_create[zone_maxx]=0;
	zone_create[zone_maxy]=0;
	zone_create[zone_step]=0;	
	
	SendClientMessage(playerid, COLOR_GOLD, " Anulowa³eœ tworzenie strefy.");
	return 1;
}
CMD:cgangzone(playerid, pl[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	if(zone_create[zone_step] > 0)
	{
	    SendClientMessage(playerid, 0xFF0000FF, "Aktualnie dodawana jest ju¿ strefa, poczekaj!");
		return 1;
	}
		
	new Float:pos_z;
	GetPlayerPos(playerid, zone_create[zone_minx], zone_create[zone_miny], pos_z);
	zone_create[zone_step]++;
	
	Dialog_Show(playerid, DIALOG_GANG_ZONE, DIALOG_STYLE_TABLIST_HEADERS, "Wybierz gang dla którego bêdziesz robi³ strefê", ShowGangs(playerid), "Wybierz", "Anuluj");
	
	SendClientMessage(playerid, 0xFF8000FF, "Wybierz gang któremu tworzysz strefê a nastêpnie idŸ do drugiego koñca strefy(na ukos) i wpisz /cgangzoneend");
	return 1;
}
CMD:cgangzoneend(playerid, pl[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	if(zone_create[zone_step] == 0)
	{
		SendClientMessage(playerid, 0xFF0000FF, "Wpisz /cgangzone aby dodaæ zone");
		return 1;
	}
	new Float:pos_z,buff[256];
	GetPlayerPos(playerid, zone_create[zone_maxx], zone_create[zone_maxy], pos_z);
	
	if(zone_create[zone_minx] > zone_create[zone_maxx]){
		SendClientMessage(playerid, COLOR_ERROR, "[GANGS::ERROR->Zone] MINX Musi byæ mniejsze od MAX{b}X{/b} (roznica %.1f)", zone_create[zone_minx] - zone_create[zone_maxx]);
		return 1;
	}
	
	if(zone_create[zone_miny] > zone_create[zone_maxy]){
		SendClientMessage(playerid, COLOR_ERROR, "[GANGS::ERROR->Zone] MINY Musi byæ mniejsze od MAX{b}Y{/b} (roznica %.1f)", zone_create[zone_miny] - zone_create[zone_maxy]);
		return 1;
	}
	
	format(buff, sizeof buff, "INSERT INTO `mreg_gangs_zone` (`id`, `gang`, `zone`, `ts`) VALUES (NULL, '%d', '%.2f, %.2f, %.2f, %.2f', CURRENT_TIMESTAMP);", zone_create[zone_gid], zone_create[zone_minx], zone_create[zone_miny], zone_create[zone_maxx], zone_create[zone_maxy]);
	mysql_query(buff);
	
	zone_create[zone_minx]=0;
	zone_create[zone_miny]=0;
	zone_create[zone_maxx]=0;
	zone_create[zone_maxy]=0;
	zone_create[zone_step]=0;	
	
	LoadGangsZones();
	
	SendClientMessage(playerid, 0x008000FF, ""chat" Doda³eœ now¹ strefê gangu!");
	return 1;
}
 

stock GetGangFromUid(duid)
{
	new gc = 0;
	foreach(new g : Gangs)
	{
		if(gInfo[g][gangid] == duid) gc = g;
	}
	return gc;
}

stock gangExists(gang_id)
{
 
	m_query("SELECT id FROM "prefix"_gangs WHERE id=%d LIMIT 1", gang_id);
	mysql_store_result();
	
	if(!mysql_num_rows()) return 0;
	new gid;
	gid = mysql_fetch_int();
	mysql_free_result();
    return gid;
}

stock DeleteGang(gid)
{
	//Backuping!
	
	BackupRecord(splitf("id,Nazwa,StronaWWW,Tag,Color,spX,SPY,spZ,Points,SumPoints,Cv,Pojazd,Skin,Last_Save,Time,Time_Created,kills,deaths,max_users,BazaFile from mreg_gangs where id=%d", gInfo[gid][gangid]), "GangBackup", false);
	BackupRecord(splitf("gang,gang_ranga,id from mreg_players where gang=%d ", gInfo[gid][gangid]), "GangMembersBackup", true);
	
	//Deleteing!
	m_query("delete from "prefix"_gangs where id=%d", gInfo[gid][gangid]);
	m_query("update "prefix"_players set gang = 0 where gang=%d", gInfo[gid][gangid]);
	m_query("DELETE FROM `mreg_gangs_wars` WHERE g1 = %d or g2 = %d", gInfo[gid][gangid], gInfo[gid][gangid]);
	
	return clearGang(gid);
}
stock gangSzefLastOnline(gang_id)
{
 
	m_query("SELECT UNIX_TIMESTAMP( date_last ) FROM "prefix"_players WHERE gang=%d and gang_ranga=3 order by date_last desc", gang_id);
	mysql_store_result();
	
	if(!mysql_num_rows()) return 0;
	new gid;
	gid = mysql_fetch_int();
	mysql_free_result();
    return gid;
}

stock clearGang(gang)
{
	gInfo[gang][gangid] = 0;
	gInfo[gang][gangSpawn][0] = 0.0;
	gInfo[gang][gangSpawn][1] = 0.0;
	gInfo[gang][gangSpawn][2] = 0.0;
	
	gInfo[gang][gangPoints] = 0;
	gInfo[gang][gangCv] = 0;
	gInfo[gang][gangPojazd] = 0;
	gInfo[gang][gangSkin] = 0;
	gInfo[gang][gangColor] = 0;
 	
	format(gInfo[gang][gangNazwa], 2, " ");
	format(gInfo[gang][gangWww], 2, " ");
	 
	format(gInfo[gang][gangTag], 2, " ");
	
	gInfo[gang][active] = false;

	new next;
	Iter_SafeRemove(Gangs, gang, next);
	
	return next;
}

CMD:gang(playerid, params[])
{
	
	if(!pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, "{CCFFFF}*{b} Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do tej komendy.");
		return 1;
	}
	ShowPlayerGangMenu(playerid);
	return 1;
}

CMD:ausunstrefe(playerid, params[])
{

	RankAdmin(playerid, R_VICEHEADADMIN);
	if(!pInfo[playerid][player_zonearea])
	{
		SendClientMessage(playerid, COLOR_ERROR, "{CCFFFF}*{b} Nie jesteœ w ¿adnej strefie.");
		return 1;
	}
	new gzone=0;
	foreach(new zones : GangsZones)
	{	
		if(gZone[zones][zonestream] == pInfo[playerid][player_zonearea])
		{
			gzone = zones;
			break;
		}
	}	
	if(!gzone)
	{
		SendClientMessage(playerid, COLOR_ERROR, "{CCFFFF}*{b} Nie jesteœ na strefie ¿adnego gangu.");
		return 1;
	}
	
	new tgid = GetGangFromUid(gZone[gzone][zonegangid]);
	if(!tgid)
	{
		SendClientMessage(playerid, COLOR_ERROR, "{CCFFFF}*{b} Nie znany b³¹d. Strefa nie usuniêta - to nie powinno siê wyda¿yæ.");
		return 1;
	}	
	 
	zone_create[zone_gid] = gZone[gzone][zone_id]; //tak wybra³em zajebist¹ zmienn¹ - ale po co robic now¹?
	Dialog_Show(playerid, DIALOG_GANG_DROPZONE, DIALOG_STYLE_MSGBOX, "Delete zone", splitf("Czy napewno chcesz usun¹æ strefe gangu %s?", gInfo[tgid][gangNazwa]), "Tak", "Nie");
 	return 1;
}
 
Dialog:DIALOG_GANG_DROPZONE(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		m_query("delete from "prefix"_gangs_zone where id=%d", zone_create[zone_gid]);
		
		LoadGangsZones();
		 
		InfoBox(playerid, splitf("Usun¹³eœ strefe. (%d)", zone_create[zone_gid]));
		
		zone_create[zone_gid] = 0;
		pInfo[playerid][player_zonearea] = 0;
		
	}
	else 
	{
		InfoBox(playerid, "Anulowa³eœ usuniêcie strefy");
	}
}	
 
Dialog:DIALOG_GANG_ZONE(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		foreach(new zones : GangsZones)
		{ 
			if(gZone[zones][zonegangid] == gInfo[pInfo[playerid][player_dialog_data][listitem]][gangid]) 
			{
				InfoBox(playerid, "Ten gang ma ju¿ strefe gangu!");
				return 1;
			}
		}
		InfoBox(playerid, "Wybra³eœ gang! \n\nTeraz idŸ do drugiego koñca strefy(na ukos) i wpisz {ff0000}/cgangzoneend");
		zone_create[zone_gid] = gInfo[pInfo[playerid][player_dialog_data][listitem]][gangid];
	}
	else 
	{
		zone_create[zone_minx]=0;
		zone_create[zone_miny]=0;
		zone_create[zone_maxx]=0;
		zone_create[zone_maxy]=0;
		zone_create[zone_step]=0;	

		SendClientMessage(playerid, 0x008000FF, ""chat" Anulowa³eœ tworzenie strefy gangu!");
	}
	return 1;
}
Dialog:DIALOG_GANG_SELECTED(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		switch(listitem)
		{
			
			case 0:
			{
 				if(!Iter_Count(Gangs)) return InfoBox(playerid, "Brak gangów na serwerze :X");
				if(pInfo[playerid][player_isGang]) 
				{
					InfoBox(playerid, ShowGangs(playerid));
				}
				else
				{
					Dialog_Show(playerid, DIALOG_GANG_INVITE_USER, DIALOG_STYLE_TABLIST_HEADERS, "Lista gangów / Gangs Lists", ShowGangs(playerid), "Do³¹cz", "Anuluj");
				}
			}
			case 1:
			{
				if(!Iter_Count(Gangs)) return InfoBox(playerid, "Brak gangów na serwerze :X");
				if(pInfo[playerid][player_isGang]) 
				{
					InfoBox(playerid, ShowGangs(playerid));
				}
				else
				{
					Dialog_Show(playerid, DIALOG_GANG_STATS, DIALOG_STYLE_TABLIST_HEADERS, "Lista gangów / Gangs Lists", ShowGangs(playerid), "Wyœwietl", "Anuluj");
				}
			}
			case 2:
			{
				Dialog_Show(playerid, DIALOG_GANG_CREATE, DIALOG_STYLE_MSGBOX, "Tworzenie gangu", "Witamy w kreatorze tworzenia gangów!\n\
				Aby stworzyæ gang musisz zap³aciæ:\n\
				\t•50.000 Respektu\n\
				lub \n\
				\t•15 z³\n\n\ 
				Je¿eli nadal chcesz kontynuowaæ kliknij \"Dalej\" je¿eli ju¿ nie, wybierz \"Anuluj\".", "Dalej", "Anluluj");
			}
			
			
			
		}
	}
	return 1;
}
 
Dialog:DIALOG_GANG_STATS(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		pInfo[playerid][player_dialog_data][0] = pInfo[playerid][player_dialog_data][listitem];
		
		Dialog_Show(playerid, DIALOG_GANG_STATS2, DIALOG_STYLE_LIST, "Lista gangów / Gangs Lists", "Statystyki Gangu\nCz³onkowie gangu (On-Line)", "Wyœwietl", "Anuluj");
		
	} 
	
	
	return 1;
}

 
Dialog:DIALOG_GANG_STATS2(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new gang = pInfo[playerid][player_dialog_data][0];
		static	ginfo[2248];
		ginfo[0] = EOS;
		switch(listitem)
		{
			case 0:
			{
				if(gInfo[gang][gangPojazd] < 400) gInfo[gang][gangPojazd] = 411;
				new gangranga[32], str12[1600], name[24], p_online, gang_r,x;
				
				#define formatginfo(%0,%1); format(ginfo, sizeof(ginfo), "%s"%0"", ginfo, %1);
				
				format(ginfo, sizeof(ginfo), "{%06x}%s %s"HEX_SAMP"\n\n", gInfo[gang][gangColor]>>>8, gInfo[gang][gangNazwa], gInfo[gang][gangTag]);
				formatginfo("Data za³o¿enia: %s\n", gInfo[gang][gangDateCreated]);
				formatginfo("Wygranych wojen gang owych: %d\n", gInfo[gang][gangCv]);
				formatginfo("Punktów: %d\n", gInfo[gang][gangPoints]);
				formatginfo("Pojazd gangu: %s\n", VehicleNames[gInfo[gang][gangPojazd]-400]);
				formatginfo("Skin Gangu: %d\n\nCz³onkowie:\n", gInfo[gang][gangSkin]);
				
				
				m_query("select nick,isonline,gang_ranga from mreg_players where gang=%d order by gang_ranga desc limit 32", gInfo[gang][gangid]);
			
				mysql_store_result();
				while(mysql_fetch_row(str12))
				{
					x++;
					sscanf(str12, "p<|>s[24]dd", name, p_online, gang_r);
					switch(gang_r){
						case 0: gangranga = "Cz³onek";
						case 1: gangranga = "Cz³onek";
						case 2: gangranga = "{ffff00}Zastêpca szefa"HEX_SAMP"";
						case 3: gangranga = "{FF0000}Szef"HEX_SAMP"";
					}
					if(p_online)
						formatginfo("%d. %s - %s ("HEX_GREEN_YELLOW"Online"HEX_SAMP")\n", x, name, gangranga);
					else 
						formatginfo("%d. %s - %s ("HEX_ERROR"Offline"HEX_SAMP")\n", x, name, gangranga);
					
				}
				if(!x) formatginfo("Brak\n", x, name, gangranga);
				mysql_free_result();
				
				InfoBox(playerid, ginfo);
			}
			case 1:
			{
				new c;
				foreach(new i : Player)
				{
					if(pInfo[i][player_gang] == gang) 
					{
						formatginfo("%s\n", playerNick(i));
						c++;
					}
				}
				if(c)
				{
					InfoBox(playerid, ginfo);
				}
				else 
				{
					InfoBox(playerid, "Brak cz³onków On-Line");
				}
			}
		}
	}
	return 1;
}

Dialog:DIALOG_GANG_INVITE_USER(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		if(pInfo[playerid][player_isGang] == true) return SendClientMessage(playerid, COLOR_INFO, "{FFFFFF} *{/b} Jesteœ ju¿ w jakimœ gangu!"); //wygenerowany
		
		if(listitem > -1)
		{
			new gang = pInfo[playerid][player_dialog_data][listitem];
			
			if(gInfo[gang][active] == false)
			{
				InfoBox(playerid, "Wyst¹pi³ b³¹d. Spróbuj ponownie.");
				return 1;
			}
			SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} *{/b} Z³o¿y³eœ podanie gangu {b}%s{/b} Czekaj na akceptacje podania.", gInfo[gang][gangNazwa]); //wygenerowany
			newAppelationToGang(playerid, gang);
			sendGangMessage(gang, COLOR_INFO, "{FFFFFF} *{/b} Nowe podanie do gangu by je zobaczyc wpisz /Gang > Podania", gRank_szef);
		}
	}
	return 1;
}

CMD:gspawn(playerid, params[])
{
	if(!pInfo[playerid][player_gang])
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz byæ cz³onkiem gangu aby teleportowaæ siê do bazy.");
	 
	}
	DialogFunc:DIALOG_GANG(playerid, 1, 1, "B gf");
	return 1;
}
CMD:gcolor(playerid, params[])
{
	if(!pInfo[playerid][player_gang])
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz byæ cz³onkiem gangu aby ustawic kolor gangu");
		 
	}
	if(gInfo[pInfo[playerid][player_gang]][gangColor] != 0)
	{
		SendClientMessage(playerid, COLOR_INFO2, " Ustawi³eœ kolor gangu.");
		pInfo[playerid][player_color] = gInfo[pInfo[playerid][player_gang]][gangColor];
		SetPlayerColorEx(playerid);
		
		UpdatePlayerNick(playerid);
	}
	return 1;
}

CMD:gonline(playerid, params[])
{
	if(!pInfo[playerid][player_gang])
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz byæ cz³onkiem gangu");
		 
	}
	pInfo[playerid][player_dialog_data][0] = pInfo[playerid][player_gang];
	DialogFunc:DIALOG_GANG_STATS2(playerid, 1, 1, "B gf");
	return 1;
}
stock ShowPlayerGangMenu(playerid)
{
	if(!pInfo[playerid][player_isGang])
	{
		Dialog_Show(playerid, DIALOG_GANG_SELECTED, DIALOG_STYLE_LIST, "Gang", "Do³¹cz do gangu\nLista gangów\nStwórz w³asny gang (Kosztuje 50.000 respektu / 8z³)", "Do³¹cz", "Anuluj");
		return 1;
	}
	
	if(pInfo[playerid][player_gang] == 0 || pInfo[playerid][player_gangID] == 0)
		pInfo[playerid][player_isGang] = false;
	
	
	#define gang_useroption "{000000}L {ffffff}Lista Gangów\n{000000}B {ffffff}Baza Gangu\n{000000}V {ffffff}Pojazd Gangu\n{000000}S {ffffff}Skin Gangu"
	#define gang_viceszefoption ""gang_useroption"\n{000000}N {ffffff}Zmien pojazd gangu\n{000000}I  {ffffff}Zmieñ skin gangu\n{000000}K {ffffff}Zmieñ kolor gangu\n{000000}3 {dd0000}Sparing"
	#define gang_szefoption ""gang_viceszefoption"\n{000000}P {ffffff}Podania do gangu\n{000000}1 {ffffff}Spawn Gangu\n{000000}2 {ffffff}Cz³onkowie"
	
	else if((pInfo[playerid][player_isGang] == true && pInfo[playerid][player_gangrank] == gRank_user) && gInfo[pInfo[playerid][player_gang]][active] == true)
	{
		Dialog_Show(playerid, DIALOG_GANG, DIALOG_STYLE_LIST, "Gang", gang_useroption, "Dalej", "Anuluj");
		return 1;
	}
	else if((pInfo[playerid][player_isGang] == true && pInfo[playerid][player_gangrank] == gRank_vice) && gInfo[pInfo[playerid][player_gang]][active] == true)
	{
		Dialog_Show(playerid, DIALOG_GANG, DIALOG_STYLE_LIST, "Gang", gang_viceszefoption, "Dalej", "Anuluj");
		return 1;
	}
	else if((pInfo[playerid][player_isGang] == true && pInfo[playerid][player_gangrank] >= gRank_szef || pInfo[playerid][player_gangrank] == gRank_szef) && gInfo[pInfo[playerid][player_gang]][active] == true)
	{
		Dialog_Show(playerid, DIALOG_GANG, DIALOG_STYLE_LIST, "Gang",  gang_szefoption, "Dalej", "Anuluj");
		return 1;
	}
	Dialog_Show(playerid, DIALOG_GANG_SELECTED, DIALOG_STYLE_LIST, "Gang", "Do³¹cz do gangu\nLista gangów\nStwórz w³asny gang", "Do³¹cz", "Anuluj");
	return 1;
}

Dialog:DIALOG_GANG(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		switch(inputtext[0])
		{
			
			case 'L':
			{
				if(!Iter_Count(Gangs)) return InfoBox(playerid, "Brak gangów na serwerze :X");
			  
				if(pInfo[playerid][player_isGang]) 
				{			
					Dialog_Show(playerid, DIALOG_GANG_STATS, DIALOG_STYLE_TABLIST_HEADERS, "Lista gangów / Gangs Lists", ShowGangs(playerid), "Wyœwietl", "Anuluj");	
				}
				else if(!pInfo[playerid][player_isGang]) 
				{
					Dialog_Show(playerid, DIALOG_GANG_INVITE_USER, DIALOG_STYLE_TABLIST_HEADERS, "Lista gangów / Gangs Lists", ShowGangs(playerid), "Do³¹cz", "Anuluj");
				}
			}
			case 'B':
			{
				if(gInfo[pInfo[playerid][player_gang]][gangSpawn][0] == 0.0) 
					return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Twój gang nie ma ustalonej bazy"); 
				SetPlayerPos(playerid, gInfo[pInfo[playerid][player_gang]][gangSpawn][0], gInfo[pInfo[playerid][player_gang]][gangSpawn][1], gInfo[pInfo[playerid][player_gang]][gangSpawn][2]);
				SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Teleportowa³eœ siê na ziemie gangu"); 
				FreezePlayerTime(playerid, 2);
			}
			case 'V':
			{
				if(gInfo[pInfo[playerid][player_gang]][gangPojazd] < 400 || gInfo[pInfo[playerid][player_gang]][gangPojazd] > 611) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Twój gang nie ma ustawionego pojazdu"); //wygenerowany
				
				CreatePlayerVehicle(playerid, gInfo[pInfo[playerid][player_gang]][gangPojazd]);
				
				SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Stworzy³eœ pojazd gangu"); //wygenerowany
			}
			case 'S':
			{
				SetPlayerSkin(playerid, gInfo[pInfo[playerid][player_gang]][gangSkin]);
				SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Ubra³eœ siê w skin gangu"); //wygenerowany
			}
			
			case 'N':
			{
				Dialog_Show(playerid, D_GANG_CHVEHICLE, DIALOG_STYLE_INPUT, "Change Vehicle", "Podaj ID pojazdu", "Dalej", "Anuluj");
			}
			case 'I':
			{
				Dialog_Show(playerid, DIALOG_GANG_CHANGE_SKIN, DIALOG_STYLE_INPUT, "Change Skin", "Podaj ID skinu", "Dalej", "Anuluj");
			}
			case 'K':
			{
				static listakolorow[5600];
				new colorgangu[10];
				for(new i=0; i<sizeof(GangColors)-1; i++)
				{
					format(colorgangu, sizeof(colorgangu), "{%06x}", GangColors[i]>>>8);
					format(listakolorow, sizeof(listakolorow), "%s%s%d. Wybierz kolor\n", listakolorow, colorgangu, i);
				}
				Dialog_Show(playerid, D_GANGCHANGE_COLOR, DIALOG_STYLE_LIST, "Zmieñ kolor gangu", listakolorow, "Zmieñ", "Cofnij");
				
			}
			case 'P':
			{
				new st@r[464];
				format(st@r, sizeof(st@r), "%s", GetApelationtoplayer_gang(playerid));
				
				if(!st@r[0]) InfoBox(playerid, "Brak podañ");
				else Dialog_Show(playerid, GANG_INVUSER_OPERAT, DIALOG_STYLE_LIST, "Podania", st@r, "Akceptuj", "Wroc");
			}
			case '1':
			{
				if(IsPlayerInRangeOfPoint(playerid,300.0,1104.2842,-1334.5215,13.7878) && Rob[Active])return SendClientMessage(playerid,COLOR_ERROR,"Dobrze siê czujesz?");
				GetPlayerPos(playerid, gInfo[pInfo[playerid][player_gang]][gangSpawn][0], gInfo[pInfo[playerid][player_gang]][gangSpawn][1], gInfo[pInfo[playerid][player_gang]][gangSpawn][2]);
				SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Ustawi³eœ spawn gangu"); //wygenerowany
				saveGang(pInfo[playerid][player_gang]);
			}
			case '2':
			{
				 
				new Query[512], buff[2048]="{FF6600}Cz³onkowie twojego gangu", x=0, ranga_[25];
				new ac_id, name[24], g_id, gang_r, id;
				m_query("select id, nick, gang, gang_ranga from "prefix"_players where gang = %d limit 128", gInfo[pInfo[playerid][player_gang]][gangid]);
				mysql_store_result();
				while(mysql_fetch_row(Query))
				{
					x++;
					sscanf(Query, "p<|>ds[24]dd", ac_id, name, g_id, gang_r);
					switch(gang_r){
						case 0: ranga_ = "Cz³onek";
						case 1: ranga_ = "Cz³onek";
						case 2: ranga_ = "Zastêpca szefa";
						case 3: ranga_ = "Szef";
					}
					format(buff, sizeof buff, "%s\n%d.%s [%s] : %d", buff, x, name, ranga_, ac_id);
					id++;
					pInfo[playerid][player_dialog_data][id] = ac_id;
					
					
				}
				mysql_free_result();
				Dialog_Show(playerid, DIALOG_SET_USER_GANG, DIALOG_STYLE_LIST, "Zarz¹dzanie cz³onkami", buff, "Zarz¹dzaj", "Anuluj");
			}
			case '3':
			{
				new g_string[1056] = "", g_count;
				
				foreach(new i : Gangs)
				{
					if(strlen(gInfo[i][gangNazwa]) == 0 || gInfo[i][gangid] == pInfo[playerid][player_gangID]) continue;
					new online;
					foreach(new ply : Player)
						if(pInfo[ply][player_gang] == i) online++;
					
					printf("online: %d", online);
					if(online >= 1) { 
						format(g_string, sizeof(g_string), "%s[G#%d] %s | %i On-Line\n", g_string, gInfo[i][gangid], gInfo[i][gangNazwa], online);
						pInfo[playerid][player_dialog_data][g_count] = i;
						g_count++;
					}
				}
				if(!strlen(g_string)) g_string = "Brak gangów do wojny";
				Dialog_Show(playerid, DIALOG_GANG_WG_WYZWIJ, DIALOG_STYLE_LIST, "Lista gangów / Gangs Lists", g_string, "Wyzwij", "Anuluj");
			}
		}
	}
	return 1;
}


Dialog:DIALOG_GANG_CREATE(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		if(loaded_gang_glob > (MAX_GANGS_CREATE-1)) return InfoBox(playerid, "Aktualnie server przekroczy³ maksymaln¹ iloœæ gangów. Nie mo¿na utworzyæ kolejnego...");
		
		Dialog_Show(playerid, DIALOG_GANG_CREATE3, DIALOG_STYLE_MSGBOX, "Tworzenie gangu", "Prosimy wybieraæ metodê op³aty za gang", "Respekt (50k)", "Portfel (15zl)");
	}
	return 1;
}


Dialog:DIALOG_GANG_CREATE3(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		if(50000 > GetPlayerScore(playerid)) return InfoBox(playerid, "Niestety masz za ma³o punktów respektu.");
			
		pInfo[playerid][player_gang_createopcion] = 1;
		Dialog_Show(playerid, DIALOG_GANG_CREATE4, DIALOG_STYLE_INPUT, "Kreator gangu", "Prosimy o podanie nazwy gangu:", "Dalej", "");
		
		
	}
	else
	{
		if(15 > pInfo[playerid][player_portfel]) return InfoBox(playerid, "Niestety masz za ma³o pieniêdzy w wirtualnym portfelu.");
		pInfo[playerid][player_gang_createopcion] = 0;
		
		Dialog_Show(playerid, DIALOG_GANG_CREATE4, DIALOG_STYLE_INPUT, "Kreator gangu", "Prosimy o podanie nazwy gangu:", "Dalej", "");
	}
	return 1;
}

Dialog:DIALOG_GANG_CREATE4(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	
		if(GangStringValidate(inputtext))
			return Dialog_Show(playerid, DIALOG_GANG_CREATE5, DIALOG_STYLE_INPUT, "Kreator gangu", "Prosimy o podanie nazwy gangu:\n\
		{FF0000}Nazwa gangu mo¿e sk³adaæ siê z znaków A-Z, a-z, 0-9", "Dalej", "");
		
		
		if(strlen(inputtext) > 36 || strlen(inputtext) < 3)
			return Dialog_Show(playerid, DIALOG_GANG_CREATE5, DIALOG_STYLE_INPUT, "Kreator gangu", "Prosimy o podanie nazwy gangu:\n\
		{FF0000}Nazwa gangu nie moze mieæ wiecej ni¿ 40 a mniej ni¿ 3 znaków", "Dalej", "");
		
		
 
		format(pInfo[playerid][player_gang_createname], 36, "%s", inputtext);
		//mysql_real_escape_string(inputtext, pInfo[playerid][player_gang_createname]); 
		
		Dialog_Show(playerid, DIALOG_GANG_CREATE5, DIALOG_STYLE_INPUT, "Kreator gangu", "Wpisz tag gangu bez nawiasów serwer sam je doda.\n\nPrzyk³ad: IMM", "Dalej", "");
	}
	return 1;
}
Dialog:DIALOG_GANG_CREATE5(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	
			
		if(strlen(pInfo[playerid][player_gang_createname]) > 36 || strlen(pInfo[playerid][player_gang_createname]) < 3)
				return Dialog_Show(playerid, DIALOG_GANG_CREATE5, DIALOG_STYLE_INPUT, "Kreator gangu", "Prosimy o podanie nazwy gangu:\n\
		{FF0000}Nazwa gangu nie moze mieæ wiecej ni¿ 40 a mniej ni¿ 3 znaków", "Dalej", "Anuluj"); 
	
		if(GangStringValidate(inputtext))
			return Dialog_Show(playerid, DIALOG_GANG_CREATE5, DIALOG_STYLE_INPUT, "Kreator gangu", "Wprowadzono nie dozwolone znaki. Dostêpne \n\nWpisz tag gangu bez nawiasów serwer sam je doda.\n\nPrzyk³ad: IMM", "Dalej", "");
		
		
		if(strlen(inputtext) < 2 || strlen(inputtext) > 6)
		{
			SendClientMessage(playerid, COLOR_RED, ""chat" Tag gangu musi mieæ od 2 do 4 znaków.");
			return Dialog_Show(playerid, DIALOG_GANG_CREATE5, DIALOG_STYLE_INPUT, "Kreator gangu", "Wpisz tag gangu bez nawiasów serwer sam je doda.\n\nPrzyk³ad: IMM", "Dalej", "");
		}
	 
		new tag_ec[20];
		mysql_real_escape_string(inputtext, tag_ec);
		
		new c = GangColors[random(sizeof(GangColors))];
		format(string2, sizeof(string2), "INSERT INTO `"prefix"_gangs` (`id`, `Nazwa`, `StronaWWW`, `Tag`, `Color`, `spX`, `SPY`, `spZ`, `Points`, `Cv`, `Pojazd`, `Skin`, `Last_Save`) VALUES (NULL, '%s', 'Brak', '%s', '0x%08x', '0.0', '0.0', '0.0', '0', '0', '0', '0', '2013-07-15 00:00:00');", pInfo[playerid][player_gang_createname], tag_ec, c);
		
		mysql_query(string2);
		printf(string2);
		
		mysql_store_result();
		
		new gang_id = mysql_insert_id();
		
		mysql_free_result();
		
	 
		if(!gang_id)
		{	
			InfoBox(playerid, "Wyst¹pi³ b³¹d i twój gang nie zosta³ dodany. \nOp³ata nie zosta³a pobrana.");
			return 1;
		}
		
		if(pInfo[playerid][player_gang_createopcion] == 0)
			GivePlayerPortfel(playerid, -15);
		else
			GivePlayerScore(playerid, -50000);
		
		pInfo[playerid][player_gangID] = gang_id;
		pInfo[playerid][player_gangrank] = gRank_szef;
		pInfo[playerid][player_isGang] = true;
		
		SendClientMessage(playerid, COLOR_ERROR, " Gratulacjê! za³o¿y³eœ w³asny gang. Wpisz /Gang by nim zarz¹dzaæ!"); //wygenerowany
		
		new gang = loaded_gang_glob;
		gang++;
		loaded_gang_glob++;
		Iter_Add(Gangs, gang);
		
		gInfo[gang][gangColor] = c;
		gInfo[gang][gangid] = gang_id;
		gInfo[gang][gangSpawn][0] = 0.0;
		gInfo[gang][gangSpawn][1] = 0.0;
		gInfo[gang][gangSpawn][2] = 0.0;
		
		gInfo[gang][gangPoints] = 0;
		gInfo[gang][gangCv] = 0;
		gInfo[gang][gangPojazd] = 0;
		gInfo[gang][gangSlots] = 25;
	
		format(gInfo[gang][gangNazwa], 32, "%s", pInfo[playerid][player_gang_createname]);
		format(gInfo[gang][gangTag], 32, "%s", tag_ec);
		
		gInfo[gang][active] = true;
				
		CreateGangTextdraws(gang);
		
		GangPlayer(playerid);
		SavePlayer(playerid);
	}
	else 
	{
		ShowPlayerGangMenu(playerid);
	}
	return 1;
}
Dialog:DIALOG_SET_USER_GANG(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		if(listitem == 0) return 1;
		pInfo[playerid][player_actionplayer] = pInfo[playerid][player_dialog_data][listitem];

		Dialog_Show(playerid, DIALOG_SELECT_USER_GANG, DIALOG_STYLE_LIST, "Zarz¹dzanie graczem", "Wyrzuæ gracza z gangu\nZmieñ graczowi rangê", "Wybierz", "Anuluj");
	}
	else 
	{
		ShowPlayerGangMenu(playerid);
	}
	return 1;
}
Dialog:DIALOG_SELECT_USER_GANG(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		switch(listitem){
			case 0:
			{
				Dialog_Show(playerid, D_DELETE_USERFromGANG, DIALOG_STYLE_MSGBOX, "Wyrzucanie", "Czy na-pewno chcesz wyrzuciæ gracza z gangu?", "Tak", "Nie");
			}
			case 1:
			{
				Dialog_Show(playerid, DIALOG_USER_RANK_NOW, DIALOG_STYLE_LIST, "Wybierz rangê dla gracza", "Cz³onek\nZastêpca Szefa\nSzef", "Zmieñ rangê", "Anuluj");
			}
		}
	}
	else 
	{
		ShowPlayerGangMenu(playerid);
	}
	return 1;
}
 

Dialog:D_DELETE_USERFromGANG(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		if(!response) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Anulowa³eœ wyrzucenie gracza z gangu!"); //wygenerowany
		if(pInfo[playerid][player_actionplayer] == 0) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Przepraszamy! nie mo¿emy zweryfikowaæ ID gracza do wyrzucenia!"); //wygenerowany
		
		new str[50], player;
		format(string2, sizeof(string2), "SELECT id, nick from "prefix"_players where id = %d ", pInfo[playerid][player_actionplayer]);
		mysql_query(string2);
		mysql_store_result();
		
		if(mysql_num_rows() == 0) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Wyst¹pi³ b³¹d podczas weryfikacji gracza! prosimy spróbowaæ ponownie!"); //wygenerowany
		
		string2[0] = EOS;
		
		mysql_fetch_row(string2, "|");
		sscanf(	string2, "p<|>ds[50]", player, str);
		
		SendClientMessage(playerid, COLOR_INFO, "Pomyœlnie wyrzuci³eœ gracza %s z gangu", str);
		gInfo[pInfo[playerid][player_gang]][gangUsers]--;
		m_query("update "prefix"_players set gang = 0, gang_ranga = 0 where id = %d;", player);
		
		new in_game_id = findPlayer(str);
		if(in_game_id != INVALID_PLAYER_ID)
		{
			
			format(string2, sizeof(string2), "Zosta³eœ wyrzucony z gangu przez %s", playerNick(playerid));
			SendClientMessage(in_game_id, COLOR_INFO, string2); //wygenerowany
			pInfo[in_game_id][player_isGang] = false;
			pInfo[in_game_id][player_gang] = 0;
			pInfo[in_game_id][player_gangID] = 0;
			pInfo[in_game_id][player_gangrank] = 0;
			
		}
		
		SetTimerEx("Gang_CallRefleshOnline", 1000, 0, "dd", pInfo[playerid][player_gang], pInfo[playerid][player_gangID]);
		
	}
	else 
	{
		ShowPlayerGangMenu(playerid);
	}
	return 1;
}

Dialog:DIALOG_USER_RANK_NOW(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		if(!response) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Anulowa³eœ zmiane rangi graczowi!"); //wygenerowany
		if(pInfo[playerid][player_actionplayer] == 0) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Przepraszamy! nie mo¿emy zwerdyfikowaæ ID gracza do wyrzucenia!"); //wygenerowany
		new typ = listitem + 1, ranga_[30];
		
		switch(typ){
			case 0: ranga_ = "Cz³onek";
			case 1: ranga_ = "Cz³onek";
			case 2: ranga_ = "Zastêpca szefa";
			case 3: ranga_ = "Szef";
		}
		
		new str[50], player;
		format(string2, sizeof(string2), "SELECT id, nick from "prefix"_players where id = %d ", pInfo[playerid][player_actionplayer]);
		mysql_query(string2);
		mysql_store_result();
		
		if(mysql_num_rows() == 0) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Wyst¹pi³ b³¹d podczas weryfikacji gracza! prosimy spróbowaæ ponownie!"); //wygenerowany
		
		string2[0] = EOS;
		
		mysql_fetch_row(string2, "|");
		sscanf(	string2, "p<|>ds[50]", player, str);
	
		SendClientMessage(playerid, COLOR_INFO, "Pomyœlnie zmieni³eœ rangê gracza %s na %s", str, ranga_);
		m_query("update "prefix"_players set gang_ranga = %d where id = %d", typ, player);
		
		new in_game_id = findPlayer(str);
		if(in_game_id != INVALID_PLAYER_ID)
		{
  
			SendClientMessage(in_game_id, COLOR_INFO, "%s zmieni³ Ci rangê w gangu na %s", playerNick(playerid), ranga_);
			pInfo[in_game_id][player_gangrank] = typ;
			
		}
	}
	return 1;
}
Dialog:D_GANG_CHVEHICLE(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new vid=strval(inputtext);
		if(vid < 400 || vid > 611) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Poda³eœ b³êdne ID pojazdu"); //wygenerowany
		if(!IsNumeric(inputtext)) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Poda³eœ b³êdne ID pojazdu"); //wygenerowany
		
		gInfo[pInfo[playerid][player_gang]][gangPojazd] = vid;
		saveGang(pInfo[playerid][player_gang]);
		
		SendClientMessage(playerid, COLOR_INFO, "{FFFFFF} *{/b} Zmieni³eœ model {b}pojazdu{/b} na: {b}%s{/b}", VehicleNames[vid-400]); //wygenerowany
	}
	
	ShowPlayerGangMenu(playerid);
	return 1;
}

Dialog:DIALOG_GANG_CHANGE_SKIN(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		if(strval(inputtext) > 300) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Poda³eœ b³êdne ID skinu"); //wygenerowany
		
		gInfo[pInfo[playerid][player_gang]][gangSkin] = strval(inputtext);
		saveGang(pInfo[playerid][player_gang]);
		SendClientMessage(playerid, COLOR_INFO, "{FFFFFF} *{/b} Zmieni³eœ skin gangu na: %d", strval(inputtext)); //wygenerowany
	}
	
	ShowPlayerGangMenu(playerid);
	return 1;
}
Dialog:D_GANGCHANGE_COLOR(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		
		gInfo[pInfo[playerid][player_gang]][gangColor] = GangColors[listitem];
		saveGang(pInfo[playerid][player_gang]);
		
		
		foreach(new xplayerid : Player)
		{

			if(pInfo[xplayerid][player_gang] == pInfo[playerid][player_gang])
			{
				SetPlayerColor(xplayerid, gInfo[pInfo[playerid][player_gang]][gangColor]);
			}
		}
		sendGangMessage(pInfo[playerid][player_gang], COLOR_INFO3, splitf("{FF0000} "chat"{/b} %s (%d) zmieni³ kolor gangu na {%06x} %x", playerNick(playerid), playerid, GangColors[listitem]>>>8,GangColors[listitem]>>>8));
		SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} {%06x}Zmieni³eœ kolor gangu", GangColors[listitem]>>>8);
	}
	
	ShowPlayerGangMenu(playerid);
	return 1;
}
CMD:gangblackcolortara(playerid,params[])
{
	gInfo[pInfo[playerid][player_gang]][gangColor] = 0xFFFFFF00;
	saveGang(pInfo[playerid][player_gang]);
	
	return 1;
}
Dialog:GANG_INVUSER_OPERAT(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		clickToPlayerApelation(playerid, listitem, response);
	}
	else 
	{
		ShowPlayerGangMenu(playerid);
	}
	return 1;
}



Dialog:DIALOG_GANG_WG0(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new g_string[1056] = "", g_count;
		
		foreach( new i : Gangs)
		{
			if(strlen(gInfo[i][gangNazwa]) == 0) continue;
			new online;
			foreach( new ply : Player)
			{
				if( pInfo[ply][player_gang] == i ) online++;
			}
			if( online <= GANGS_WOJNA_MINPLAYERS ) continue; //XDJP
			format(g_string, sizeof(g_string), "%s[G#%d] %s | %i\n", g_string, gInfo[i][gangid], gInfo[i][gangNazwa], gInfo[i][gangid]);
			pInfo[playerid][player_dialog_data][g_count] = i;
			g_count++;
		}
		if(!strlen(g_string)) g_string = "Brak gangów! do wojny";
		//printf(g_string);
		Dialog_Show(playerid, DIALOG_GANG_WG_WYZWIJ, DIALOG_STYLE_LIST, "Lista gangów / Gangs Lists", g_string, "Wyzwij", "Anuluj");
	}
	else 
	{
		ShowPlayerGangMenu(playerid);
	}
	return 1;
}
Dialog:DIALOG_GANG_WG_WYZWIJ(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		pInfo[playerid][player_gang_createopcion] = pInfo[playerid][player_dialog_data][listitem];
		
		new online;
		foreach(new ply : Player)
				if(pInfo[ply][player_gang] == pInfo[playerid][player_gang_createopcion]) online++;
					
		if(online < 1) return SendClientMessage(playerid, COLOR_ERROR, "* W tym gangu jest zbyt ma³o osób by rozpocz¹œæ sparing");
		
		new aList[512];
		
		for(new i;i<add_SparCount;i++){
			format(aList, sizeof(aList), "%s"chat" %s (interior %d); \n", aList, add_Spar[i][add_name], add_Spar[i][add_interior]);
		}
		strdel(aList, strlen(aList)-2, strlen(aList));
		
		Dialog_Show(playerid, DIALOG_GANG_WG_WYZWIJ_A, DIALOG_STYLE_LIST, "Wybierz arene:", aList, "Dalej", "Anuluj");
	}
	else 
	{
		ShowPlayerGangMenu(playerid);
	}
	return 1;
}

Dialog:DIALOG_GANG_WG_WYZWIJ_A(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		SendClientMessage(playerid, COLOR_GREEN, " Wybra³eœ arenê {b}%s (interior %d){/b}, wybierz maksymaln¹ liczbê osób na sparingu;", add_Spar[listitem][add_name], add_Spar[listitem][add_interior]);
		pInfo[playerid][player_reportID][0] = listitem;
		
		new online[2];
		foreach(new ply : Player)
			if(pInfo[ply][player_gang] == pInfo[playerid][player_gang_createopcion]) online[0]++;
		
		foreach(new ply : Player)
			if(pInfo[ply][player_gang] == pInfo[playerid][player_gang]) online[1]++;
				
		if(online[0] < 1 || online[1] < 1) return SendClientMessage(playerid, COLOR_ERROR, "* W tym gang jest zbyt ma³o osób by rozpocz¹œæ sparing");
		
		if(online[0] > online[1]) online[0] = online[1];
		
		new str[64];
		for(new i=1;i<online[0]+1;i++){
		
			format(str, sizeof(str), "%s %d vs %d; \n", str, i, i);
		}
		strdel(str, strlen(str)-2, strlen(str));
		
		Dialog_Show(playerid, DIALOG_GANG_WG_WYZWIJ_B, DIALOG_STYLE_LIST, "Wybierz liczbe uczestników:", str, "Dalej", "Anuluj");
	}
	else 
	{
		ShowPlayerGangMenu(playerid);
	}
	return 1;
}
Dialog:DIALOG_GANG_WG_WYZWIJ_B(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		 
		wyzwijGang(playerid, pInfo[playerid][player_gang], pInfo[playerid][player_gang_createopcion], pInfo[playerid][player_reportID][0], listitem+1);
	}
	else 
	{
		ShowPlayerGangMenu(playerid);
	}
	return 1;
}

/*
Dialog:DIALOG_GANG_WG_WYZWIJ(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		wyzwijGang(playerid, pInfo[playerid][player_gang], pInfo[playerid][player_dialog_data][listitem]);
	}
	else 
	{
		ShowPlayerGangMenu(playerid);
	}
	return 1;
}
*/
 
stock getLastGang()
{
	
	mysql_query("select id from "prefix"_gangs order by id desc");
	mysql_store_result();
	new id;
	if(mysql_num_rows()) {
		id = mysql_fetch_int();
		mysql_free_result();
		return id;
	}
	mysql_free_result();
	return -1;
}
sendGangMessage(idgangs, colorex, src[], rank = 0)
{
	foreach(new playerid : Player)
	{
		if(pInfo[playerid][player_gang] != idgangs) continue;
		
		if(pInfo[playerid][player_gangrank] >= rank)
		{
			SendClientMessage(playerid, colorex, src);
		}
	}
	return true;
}
newAppelationToGang(playerid, idgangs)
{
	
	if(	gangPodania[playerid][idgangs] == playerid ) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Z³o¿y³eœ ju¿ podanie do tego gangu. Zaczekaj na akceptacje podania"); //wygenerowany
	gangPodania[playerid][idgangs] = playerid;
	 
	SendClientMessage(playerid, COLOR_GOLD, "{FF0000} "chat"{/b} Z³o¿y³eœ podanie do gangu");
	sendGangMessage(idgangs, COLOR_INFO, "{FFFFFF} *{/b} Nowe podanie do gangu by je zobaczyæ wpisz /Gang » Podania.", gRank_vice);
	
	return 1;
}

GetApelationtoplayer_gang(playerid)
{
	new strp[426];
	strp[0] = EOS;
	
	new c;
	foreach(new x : Player)
	{
		if(gangPodania[x][pInfo[playerid][player_gang]] == -1) continue;
		
		pInfo[playerid][player_dialog_data][c] = x;
		
		format(strp, sizeof(strp), "%s%s - %d\n", strp, playerNick(gangPodania[x][pInfo[playerid][player_gang]]), gangPodania[x][pInfo[playerid][player_gang]]);
		
		c++;
	}
	return strp;
}
ClearAllGangsApelation()
{
	
	for(new x; x<MAX_PLAYERS;x++)
	{
		for(new c; c<MAX_GANG2;c++)
		{
			gangPodania[x][c] = -1;
		}
	}
}
clickToPlayerApelation(playerid, listitem, response)
{
	
	new player = pInfo[playerid][player_dialog_data][listitem];

	
	if(!IsPlayerConnected(player)) return;
	if(gangPodania[player][pInfo[playerid][player_gang]] == -1) return;
	
	if(!response)
	{
		GangPlayer(playerid);
		gangPodania[player][pInfo[playerid][player_gang]] = -1;
		SendClientMessage(player, COLOR_INFO, "{FFFFFF} *{/b} %s Szef gangu %s nie przyj¹³ Cie do gangu", playerNick(playerid), gInfo[pInfo[playerid][player_gang]][gangNazwa]); //wygenerowany
	}	
	else 
	if(response)
	{
		if(pInfo[player][player_gang]>=1){
			SendClientMessage(playerid, COLOR_ERROR, ""chat" Podany Gracz ju¿ jest w Gangu.");
			return;
		}
		if(gInfo[pInfo[playerid][player_gang]][gangUsers] >= gInfo[pInfo[playerid][player_gang]][gangSlots])
		{
			SendClientMessage(playerid, COLOR_ERROR, ""chat" Wyczerpa³eœ limit slotów (%d/%d) nie mo¿esz przyjmowaæ kolejnych cz³onków gangu...", gInfo[pInfo[playerid][player_gang]][gangUsers], gInfo[pInfo[playerid][player_gang]][gangSlots]);
			return;
		}
		for(new c; c<MAX_GANG2;c++)
		{
			gangPodania[player][c] = -1;
		}
		
		pInfo[player][player_gang] = pInfo[playerid][player_gang];
		pInfo[player][player_gangrank] = gRank_user;
		pInfo[player][player_gangID] = pInfo[playerid][player_gangID];
		pInfo[player][player_isGang] = true;
		
		GangPlayer(playerid);
		SavePlayer(playerid);
		
		Gang_OnPlayerLogin(playerid);

		gInfo[pInfo[playerid][player_gang]][gangUsers]++;
		
		SendClientMessage(playerid, COLOR_INFO, "{FFFFFF} *{/b} Akceptowa³eœ podanie gracza %s do gangu", playerNick(player)); //wygenerowany
		SendClientMessage(player, COLOR_INFO, "{FFFFFF} *{/b} %s Szef gangu %s przyj¹³ Cie do gangu %d", playerNick(playerid), gInfo[pInfo[playerid][player_gang]][gangNazwa], pInfo[player][player_gangID]); //wygenerowany
	}
	ShowPlayerGangMenu(playerid);
}

 
saveGang(tgangid)
{
	
	if(gInfo[tgangid][active] == false) return;
	if(gInfo[tgangid][gangSaveTime] > gettime() - (60*5)) return; //zapisujemy gang co ~5 minut z tego powodu iz nie chcemy duzo zapytan, co nie?
	
	new gangSave[3][956];
	#define save(%0,%1,%2) format(gangSave[0], 256, ","%0"="%2"",%1); strcat(gangSave[1], gangSave[0])
		
	//save("Nazwa", gInfo[tgangid][gangNazwa], "'%s'");
	//save("StronaWWW", gInfo[tgangid][gangWww], "'%s'");

	if(gInfo[tgangid][gangColor] > 0) save("Color", gInfo[tgangid][gangColor], "'0x%x'");
	if(gInfo[tgangid][gangSpawn][0] > 0) save("spX", gInfo[tgangid][gangSpawn][0], "%.1f");
	if(gInfo[tgangid][gangSpawn][1]	> 0) save("SPY", gInfo[tgangid][gangSpawn][1], "%.1f");
	if(gInfo[tgangid][gangSpawn][2] > 0) save("spZ", gInfo[tgangid][gangSpawn][2], "%.1f");
	if(gInfo[tgangid][gangPoints] > 0) save("Points", gInfo[tgangid][gangPoints], "%d");
	if(gInfo[tgangid][gangCv] > 0) save("Cv", 	gInfo[tgangid][gangCv], "%d");
	if(gInfo[tgangid][gangPojazd] > 0) save("Pojazd", 	gInfo[tgangid][gangPojazd], "%d");
	if(gInfo[tgangid][gangSkin] > 0) save("Skin", gInfo[tgangid][gangSkin], "%d");
	
 	format (gangSave[2], 256, "Update "prefix"_gangs SET Last_Save=now() %s where id=%d", gangSave[1], gInfo[tgangid][gangid]);
	mysql_query (gangSave[2]);
	
	gInfo[tgangid][gangSaveTime] = gettime();
	//printf ("Saved gang! %s", gangSave[2]);
	
}
 

CMD:godejdz(playerid, cmdtext[])
{
	if(pInfo[playerid][player_isGang] == false) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Nie jesteœ w ¿adnym gangu!"); //wygenerowany
	
	format(string2, sizeof(string2), " {b}%s{/b} opuszcza nasz gang!", playerNick(playerid));
	sendGangMessage(playerid, COLOR_INFO, string2);
	TextDrawHideForPlayer(playerid, gInfo[ pInfo[playerid][player_gang] ][gangTextdraw]);

	new xgang = pInfo[playerid][player_gang], xgangid = pInfo[playerid][player_gangID];
	pInfo[playerid][player_isGang] = false;
	pInfo[playerid][player_gang] = 0;
	pInfo[playerid][player_gangID] = 0;
	pInfo[playerid][player_gangrank] = 0;
	SavePlayer(playerid);

	SetTimerEx("Gang_CallRefleshOnline", 1000, 0, "dd", xgang, xgangid);

	SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Opuœci³eœ Gang!"); //wygenerowany
	return 1;
}

CMD:gpodanie(playerid, cmdtext[]){
	
	if(!pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, "{CCFFFF}*{b} Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do tej komendy.");
		return 1;
	}
	if(isnull(cmdtext)) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} U¿yj /GPodanie [Nazwa / Tag gangu]!"); //wygenerowany
	
	if(pInfo[playerid][player_isGang] == false) GangPlayer(playerid);
	
	if(pInfo[playerid][player_isGang] == true) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Jesteœ ju¿ w gangu!"); //wygenerowany
	new bool:zlozyl;
	new g;
	foreach(new gang : Gangs)
	{
		g = strfind(gInfo[gang][gangNazwa], cmdtext);
		
		if(g != (-1)) 
		{
			SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} *{/b} Z³o¿y³eœ podanie gangu {b}%s{/b} Czekaj na akceptacje podania.", gInfo[gang][gangNazwa]); //wygenerowany
			newAppelationToGang(playerid, gang);
			 
			zlozyl = true;
			break;
		} 
		else 
		{
			g = strfind(gInfo[gang][gangTag], cmdtext);
			
			if(g != (-1)) 
			{
				SendClientMessage(playerid, COLOR_GREEN, "{FFFFFF} *{/b} Z³o¿y³eœ podanie gangu {b}%s{/b} Czekaj na akceptacje podania.", gInfo[gang][gangNazwa]); //wygenerowany
				newAppelationToGang(playerid, gang);
				sendGangMessage(gang, COLOR_INFO, "{FFFFFF} *{/b} Nowe podanie do gangu by je zobaczyæ wpisz /gang > podania", gRank_vice);
				zlozyl = true;
				break;
			}
		}
	}
	if(zlozyl == false) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Nie odnaleziono gangu!"); //wygenerowany
	
	return 1;
}

stock GangPlayer(playerid)
{
	foreach(new gang : Gangs)
	{
		if(gInfo[gang][gangid] == pInfo[playerid][player_gangID]) 
		{	
			pInfo[playerid][player_isGang] = true;
			pInfo[playerid][player_gang] = gang; 
			return gang;
		}
	}
	return 0;
}
 

//wojny
 
 
stock wyzwijGang(playerid, g1, g2, a@rena, players)
{  
	if( g1 == g2 ) return 0;
	
	
	gangInfo(g1, gangWojnaArena) = a@rena;
	gangInfo(g2, gangWojnaArena) = a@rena;
	
	gangInfo(g1, gangWojnaMaxPlayers) = players;
	gangInfo(g2, gangWojnaMaxPlayers) = players;
	
	if( gangInfo(g2, gangWojnaZaproTime) > gettime() ) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Ten gang ma ju¿ zaproszenie na sparing. Spróbuj ponownie za 30 sekund");
	if( gangInfo(g1, gangWojnaZaproTime) > gettime() ) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Aktualnie macie zaproszenie na sparing. Nie mozecie wyzwac innego gangu.");
	
	if( gangInfo(g2, gangWojnaTrwa) ) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} W tym gangu trwa ju¿ jakiœ sparing");
	
	gangInfo(g2, gangWojnaZaproTime) = gettime() + 31;
	gInfo[g1][gangWojnaZapro] = g2;
	gInfo[g2][gangWojnaZapro] = g1;
		
	format(string2, sizeof( string2 ), ""chat" Gang %s wyzywa was na sparing (%d/%d). Aby akceptowaæ nale¿y wpisaæ /gwakceptuje", gangInfo(g1, gangNazwa), players, players);
	sendGangMessage(g2, COLOR_RED, string2);
	sendGangMessage(g2, COLOR_RED, "{FF0000} "chat"{/b} Macie na to 30 sekund");
	
	format(string2, sizeof( string2 ), ""chat" Wyzwaliœcie gang %s na sparing!", gangInfo(g2, gangNazwa), g2);
	sendGangMessage(g1, COLOR_RED, string2);
	return 1;
}

CMD:gwakceptuje(playerid, params[])
{
	if( pInfo[ playerid ][ player_isGang ] == false ) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Nie jesteœ w ¿adnym gangu!");
	if( pInfo[ playerid ][ player_gangrank ] <= 1 ) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Nie masz odpowiednich uprawieñ!");
	if( player_gangInfo(playerid, gangWojnaZaproTime) < gettime() ) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Czas na akceptacje wojny min¹³ b¹dŸ nie mieliœcie zaproszenia");
	if( player_gangInfo(playerid, gangWojnaTrwa) == true ) return 1;
	player_gangInfo(playerid, gangWojnaTrwa) = true;
	gInfo[player_gangInfo(playerid, gangWojnaZapro)][gangWojnaTrwa] = true;
	
	format(string2, sizeof( string2 ), ""chat" Wojna gangów %s vs %s rozpocznie siê za 20 sekund!", player_gangInfo(playerid, gangNazwa), gInfo[player_gangInfo(playerid, gangWojnaZapro)][gangNazwa]);
	SendClientMessageToAll(COLOR_GREEN, string2, string2);
	
	foreach(new i : Player){
		if(pInfo[i][player_gang] == pInfo[ playerid ][player_gang] || pInfo[i][player_gang] == player_gangInfo(playerid, gangWojnaZapro))
		{
			SendClientMessage(i, COLOR_GOLD, "{FF0000} *{/b} Aby zapisaæ siê na sparing wpisz /sparsave."),SendClientMessage(i, COLOR_GOLD, "{FF0000} *{/b} Aby zapisaæ siê na sparing wpisz /sparsave.");
			pInfo[ playerid ][ player_sparmember ]  = false;
		}
	}
	player_gangInfo(playerid, gangWojnaPlayers)=0;
	gInfo[player_gangInfo(playerid, gangWojnaZapro)][gangWojnaPlayers] = 0;
	SetTimerEx(fmake->gangs::sparingstart(), 20*1000, 0, "dd", pInfo[ playerid ][player_gang], player_gangInfo(playerid, gangWojnaZapro));
	
	return 1;
}
CMD:sparsave(playerid, params[]){

	
	if( pInfo[ playerid ][ player_isGang ] == false ) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Nie jesteœ w ¿adnym gangu!");
	if( pInfo[ playerid ][ player_sparmember ] == true ) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Zapisa³eœ siê ju¿ #niepi³em");
	if( player_gangInfo(playerid, gangWojnaTrwa) != true ){
		SendClientMessage(playerid, COLOR_ERROR, " Twój gang aktualnie ma sparingu");
		return 1;
	}
	if( player_gangInfo(playerid, gangWojnaPlayers) >= player_gangInfo(playerid, gangWojnaMaxPlayers))
	{
		SendClientMessage(playerid, COLOR_ERROR, " Nie ma miejsc by zapisaæ siê na sparing...");
		return 1;
	}
	
	SendClientMessage(playerid, COLOR_ERROR, " Zapisa³eœ siê na sparing");
	SendClientMessage(playerid, COLOR_ERROR, " Chcesz siê wypisaæ? Wpisz /sparremove ");
	
 
	pInfo[playerid][player_sparmember] = true; 
	pInfo[playerid][player_sparmember2] = true;
	
	player_gangInfo(playerid, gangWojnaPlayers)++;
	
	foreach(new splayerid : Player)
	{
		if(splayerid == playerid) continue;
		if(pInfo[splayerid][player_gang] == pInfo[splayerid][player_gang] && pInfo[splayerid][player_sparmember] == true)
		{
			pInfo[playerid][player_gangWarTeam] = pInfo[splayerid][player_gangWarTeam];
			break;
		}
	}
	if(player_gangInfo(playerid, gangWojnaTrwa))
	{
		this->gangs::spawn(playerid);
	}
	
	 
	return 1;
}
CMD:sparremove(playerid, params[]){

	
	if( pInfo[ playerid ][ player_isGang ] == false ) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Nie jesteœ w ¿adnym gangu!");
	if( pInfo[ playerid ][ player_sparmember ] == false ) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} "chat"{/b} Jeszcze sie nie zapisa³eœ na spara ");
	if( player_gangInfo(playerid, gangWojnaTrwa) != true ){
		SendClientMessage(playerid, COLOR_ERROR, " Twój gang aktualnie ma sparingu.");
		return 1;
	}
 
	
	SendClientMessage(playerid, COLOR_ERROR, " Wypisa³eœ siê z sparingu. Teraz ktoœ inny mo¿e siê zapisaæ.");
	
	pInfo[playerid][player_sparmember] = false; 
	pInfo[playerid][player_gangWarTeam] = 0;
			
	if(player_gangInfo(playerid, gangWojnaTrwa)) SetPlayerHealth(playerid, 0.0); //wypisanie z sparingu 
	player_gangInfo(playerid, gangWojnaPlayers)--;
	if(player_gangInfo(playerid, gangWojnaPlayers) < 0) player_gangInfo(playerid, gangWojnaPlayers) = 0;
	
	SetPlayerHealth(playerid, 0.0);
	return 1;
}
fmethod gangs::sparingstart(g1, g2)
{
	gangInfo(g1, gangWojnaPoint) = 0; 
	gangInfo(g2, gangWojnaPoint) = 0;

	gangInfo(g1, gangWojnaVV) = random(8888)+700; 
	gangInfo(g2, gangWojnaVV) = gangInfo(g1, gangWojnaVV);
	
	
//	gangInfo(g1, gangWojnaArena) = random(add_SparCount); 
	//gangInfo(g2, gangWojnaArena) = gangInfo(g1, gangWojnaArena);
	
	gangInfo(g1, gangWojnaKill) = 0; 
	gangInfo(g2, gangWojnaKill) = 0;
	
	
	//GivePlayerHealth
	new onlin@e[2];
	new g_@info[128];
	format(g_@info, sizeof( g_@info ), "Gang [%s] - %d~n~Gang [%s] - %d", gangInfo(g1, gangTag), gangInfo(g1, gangWojnaPoint), gangInfo(g2, gangTag), gangInfo(g2, gangWojnaPoint));
	foreach( new i : Player)
	{
		if(!pInfo[i][player_sparmember]) continue;
		
		pInfo[i][player_sparmember2] = true;
	    if(pInfo[i][player_gang] == g1)
	    {
			PlayerEventTDSet(i, g_@info);
			pInfo[i][player_gangWarTeam] = 1;
			player_gangInfo(i, gangWojnaTrwa) = true;
			this->gangs::spawn(i);
			
			pInfo[i][player_spardmg] = 0;
			onlin@e[0]++;
	    }
	    else if(pInfo[i][player_gang] == g2)
	    {
			PlayerEventTDSet(i, g_@info);
			player_gangInfo(i, gangWojnaTrwa) = true;
			pInfo[i][player_gangWarTeam] = 2;
			
			this->gangs::spawn(i);
			
			pInfo[i][player_spardmg] = 0;
			onlin@e[1]++;
	    }
		pInfo[i][player_spardmg] = 0.0;
		pInfo[i][player_sparkill] = 0;
		
		
	}
	SendClientMessageToAll(0x0066FFFF, ""chat" Sparing gangów {FFFFFF}%s {0066FF}vs {FFFFFF}%s{0066FF} zosta³ rozpoczêty!", gangInfo(g1, gangNazwa), gangInfo(g2, gangNazwa));
	if(onlin@e[0] > 0 && onlin@e[1] > 0) this->gangs::sparupdate(g1, g2, 60*3);
	else  this->gangs::sparupdate(g1, g2, -2);
}
method gangs::death(playerid, killerid)
{
	if(killerid == INVALID_PLAYER_ID) return 0;

	if(!pInfo[playerid][player_sparmember] && !pInfo[killerid][player_sparmember]) return 1;
	if(player_gangInfo(playerid, gangWojnaTrwa) == true && pInfo[playerid][player_gangWarTeam] != 0)
	{
		if(pInfo[playerid][player_gangWarTeam] == 1)
		{
			//this->gangs::spawn(playerid);
			
			if(IsPlayerConnected(killerid))
			{
				pInfo[killerid][player_sparkill]++;
				player_gangInfo(killerid, gangWojnaPoint)++;
			}
		}
		else if(pInfo[playerid][player_gangWarTeam] == 2)
		{
			//this->gangs::spawn(playerid);
			
			if(IsPlayerConnected(killerid))
			{
				pInfo[killerid][player_sparkill]++;
				player_gangInfo(killerid, gangWojnaPoint)++;
			}
		}
		
		 
		return 1;
	}
	return 0;
}
method gangs::spawn(playerid)
{
	if(!pInfo[playerid][player_sparmember]) return 0;
	if(pInfo[playerid][player_gangWarTeam] == 1)
	{
		SetPlayerTeam(playerid, (MAX_PLAYERS + MAX_PLAYERS)  + pInfo[playerid][player_gang]);
		
		new id = player_gangInfo(playerid, gangWojnaArena);
		
		 
		SetPlayerPos(playerid, add_Spar[id][aad_spawn1][0] + random(3), add_Spar[id][aad_spawn1][1] + random(3), add_Spar[id][aad_spawn1][2] + 1.0);
		
		SetPlayerInterior(playerid, add_Spar[id][add_interior]);
		SetPlayerVirtualWorld(playerid, (player_gangInfo(playerid, gangWojnaVV)));
		
		SetCameraBehindPlayer(playerid);
		ResetPlayerWeapons(playerid);
		
	//	FreezePlayerTime(playerid, 2);
		
		SetPlayerHealth(playerid, 100.0);
		SetPlayerArmour(playerid, 100.0);
		
		Dialog_Show(playerid, DIAL_WG_WEAPON, DIALOG_STYLE_LIST, "Wybierz zestaw broni", ""chat" Deagle + MP5\n"chat" Deagle + Shotgun\n"chat" Deagle + Sniper\n"chat" Deagle + M4\n"chat" Shotgun + Sniper\n"chat" Deagle + Rifle\n"chat" M4 + MP5\n"chat" Deagle + AK47\n"chat" Shotgun + Rifle\n"chat" Shotgun + MP5", "Wybierz", "Anuluj");
		GangZoneShowForPlayer(playerid, add_Spar[id][add_zone], 0xdd000050);
		return 1;
		
	}
	else if(pInfo[playerid][player_gangWarTeam] == 2)
	{
		SetPlayerTeam(playerid, (MAX_PLAYERS) + pInfo[playerid][player_gang]);
		new id = player_gangInfo(playerid, gangWojnaArena);
		
		SetPlayerPos(playerid, add_Spar[id][aad_spawn2][0] + random(3), add_Spar[id][aad_spawn2][1] + random(3), add_Spar[id][aad_spawn2][2] + 1.0);
		SetPlayerInterior(playerid, add_Spar[id][add_interior]);
		SetCameraBehindPlayer(playerid);
		ResetPlayerWeapons(playerid);
		SetPlayerVirtualWorld(playerid, ((player_gangInfo(playerid, gangWojnaVV))));
		
		Dialog_Show(playerid, DIAL_WG_WEAPON, DIALOG_STYLE_LIST, "Wybierz zestaw broni", ""chat" Deagle + MP5\n"chat" Deagle + Shotgun\n"chat" Deagle + Sniper\n"chat" Deagle + M4\n"chat" Shotgun + Sniper\n"chat" Deagle + Rifle\n"chat" M4 + MP5\n"chat" Deagle + AK47\n"chat" Shotgun + Rifle\n"chat" Shotgun + MP5", "Wybierz", "Anuluj");
		//FreezePlayerTime(playerid, 2);
 		SetPlayerHealth(playerid, 100.0);
		SetPlayerArmour(playerid, 100.0);
		
		GangZoneShowForPlayer(playerid, add_Spar[id][add_zone], 0xdd000050);
		return 1;
	}
	
	 
	return 0;
}
 

Dialog:DIAL_WG_WEAPON(playerid, response, listitem, inputtext[])
{
	switch(listitem)
	{
		case 0: //Deagle + MP5
		{
			GivePlayerWeapon(playerid, 24, 10000);
			GivePlayerWeapon(playerid, 29, 10000);
		}
		case 1: //Deagle + Shotgun
		{
			GivePlayerWeapon(playerid, 24, 10000);
			GivePlayerWeapon(playerid, 25, 10000);
		}
		case 2: //Deagle + Sniper
		{
			GivePlayerWeapon(playerid, 24, 10000);
			GivePlayerWeapon(playerid, 34, 10000);
		}
		case 3: //Deagle + M4
		{
			GivePlayerWeapon(playerid, 24, 10000);
			GivePlayerWeapon(playerid, 31, 10000);
		}
		case 4: //Shotgun + Sniper
		{
			GivePlayerWeapon(playerid, 25, 10000);
			GivePlayerWeapon(playerid, 34, 10000);
		}
		case 5: //Deagle + Rifle
		{
			GivePlayerWeapon(playerid, 24, 10000);
			GivePlayerWeapon(playerid, 33, 10000);
		}
		case 6: //M4 + MP5
		{
			GivePlayerWeapon(playerid, 31, 10000);
			GivePlayerWeapon(playerid, 29, 10000);
		}
		case 7: //Deagle + AK47
		{
			GivePlayerWeapon(playerid, 24, 10000);
			GivePlayerWeapon(playerid, 30, 10000);
		}
		case 8: //Shotgun + Rifle
		{
			GivePlayerWeapon(playerid, 25, 10000);
			GivePlayerWeapon(playerid, 33, 10000);
		}
		case 9: //Shotgun + MP5
		{
			GivePlayerWeapon(playerid, 25, 10000);
			GivePlayerWeapon(playerid, 29, 10000);
		}
	}
	return 1;
}
fmethod gangs::sparupdate(g1, g2, time){

	if( time > 0 )
	{
		new online@[2];
		format(string2, sizeof( string2 ), "Gang [%s] - %d~n~Gang [%s] - %d~n~Pozostalo %d sekund", gangInfo(g1, gangTag), gangInfo(g1, gangWojnaPoint), gangInfo(g2, gangTag), gangInfo(g2, gangWojnaPoint), time);
		foreach( new i : Player)
		{
			if(!pInfo[i][player_sparmember]) continue;
			if( (pInfo[i][player_gang] == g1 || pInfo[i][player_gang] == g2) && pInfo[i][player_gangWarTeam] > 0 )
			{
				PlayerEventTDSet(i, string2);
			 
				if(pInfo[i][player_gang] == g2) online@[0] ++;
				else if(pInfo[i][player_gang] == g1) online@[1] ++;
				
				if(!IsPlayerInDynamicArea(i, add_Spar[player_gangInfo(i, gangWojnaArena)][add_stream]) && add_Spar[player_gangInfo(i, gangWojnaArena)][add_interior] == 0)
				{
						SendClientMessage(i, 0xFF0000FF, ""chat" Nie wolno wychodziæ po za strefe zabawy!");
				
						GivePlayerHealth(i, -10.0);
						GameTextForPlayer(i, "~n~~n~~n~~n~Wroc na teren wojny!", 1500, 3);
						
				}
			}
		}
		if(!online@[0] || !online@[1])
		{
			if(!online@[0] && gangInfo(g2, gangWojnaPoint) > gangInfo(g1, gangWojnaPoint)) gangInfo(g2, gangWojnaPoint)=gangInfo(g1, gangWojnaPoint)-1;
			else if(!online@[1] && gangInfo(g1, gangWojnaPoint) > gangInfo(g2, gangWojnaPoint)) gangInfo(g1, gangWojnaPoint)=gangInfo(g2, gangWojnaPoint)-1;
			
			SetTimerEx(fmake->gangs::sparupdate(), 1000, 0, "ddd", g1, g2, 0);
				
			return 0;
		}
		SetTimerEx(fmake->gangs::sparupdate(), 1000, 0, "ddd", g1, g2, time -1);
	} 
	else 
	{
		if(time != -2)
		{
			new
				playerScores[MAX_PLAYERS][gangspar_rankingEnum],
				index,
				p
			;
		
			foreach( new i : Player)
			{
				if(pInfo[i][player_sparmember2]) 
				{
					printf("-----------------------------------------------\n%s dmg: %.1f", playerNick(i), pInfo[i][player_spardmg]);
					playerScores[index][player_Score] = floatround(pInfo[i][player_spardmg], floatround_round);
					playerScores[index++][player_ID] = i;
					printf("playerScores: %d\n-----------------------------------------------", playerScores[index][player_Score]);
					
					p++;
				}
			
			}
			
			GetPlayerHighestScores(playerScores, 0, index-1);
			static TdData[6][1024];
		 
			 
			for(new elo;elo<6;elo++){
				
				for(new elo3;elo3<1024;elo3++){
					TdData[elo][elo3] = EOS;
				}
				
			}
			new playerId, outdb[1024];
			
			 
		 
			if( gangInfo(g1, gangWojnaPoint) == gangInfo(g2, gangWojnaPoint) )
				format(string2, sizeof( string2 ), ""chat" Sparing gangów {FFFFFF}%s {0066ff}vs {FFFFFF}%s {0066ff}zosta³ zakoñczony remisem! (%d:%d)", gangInfo(g1, gangNazwa), gangInfo(g2, gangNazwa), gangInfo(g1, gangWojnaPoint), gangInfo(g2, gangWojnaPoint));
			else if( gangInfo(g1, gangWojnaPoint) > gangInfo(g2, gangWojnaPoint) )
			{
				format(string2, sizeof( string2 ), ""chat" Sparing gangów {FFFFFF}%s {0066ff}vs {FFFFFF}%s {0066ff}wygrywa {FFFFFF}%s {0066ff}(%d:%d)!", gangInfo(g1, gangNazwa), gangInfo(g2, gangNazwa), gangInfo(g1, gangNazwa), gangInfo(g1, gangWojnaPoint), gangInfo(g2, gangWojnaPoint));  
				 
				gInfo[g1][gangPoints]+=25;
				gInfo[g1][gangCv]++;
			}
			else if( gangInfo(g1, gangWojnaPoint) < gangInfo(g2, gangWojnaPoint) )
			{
				format(string2, sizeof( string2 ), ""chat" Sparing gangów {FFFFFF}%s {0066ff}vs {FFFFFF}%s {0066ff}wygrywa {FFFFFF}%s {0066ff}(%d:%d)!", gangInfo(g1, gangNazwa), gangInfo(g2, gangNazwa), gangInfo(g2, gangNazwa), gangInfo(g2, gangWojnaPoint), gangInfo(g1, gangWojnaPoint));
				
				gInfo[g1][gangPoints]+=25;
				gInfo[g2][gangCv]++;
			}
			
			SendClientMessageToAll(0x0066FFFF, string2);
			 
			new gscore[2];
			
			for(new i = 0; i != p; ++i) {
				
				playerId = playerScores[i][player_ID];
				if(!pInfo[playerId][player_sparmember2]) continue;
				
				 
				if( pInfo[playerId][player_gang] == g1 ||  pInfo[playerId][player_gang] == g2 ) 
				{
					 
					strcat(outdb,splitf("@$@%s,%d,%d,%d,%d", playerNick(playerId), pInfo[playerId][player_id], pInfo[playerId][player_sparkill], playerScores[i][player_Score], pInfo[playerId][player_gangID]));
				}
			
				if( pInfo[playerId][player_gang] == g1 ) 
				{
					if(gscore[0] == 0){
						GivePlayerScore(playerId, 150, "1 miejsce w sparingu");
					}else if(gscore[0] == 1){
						GivePlayerScore(playerId, 80, "2 miejsce w sparingu");
					} else 
					if(gscore[0] == 2){
						GivePlayerScore(playerId, 40, "3 miejsce w sparingu");
					} 
					else GivePlayerScore(playerId, 10, "udzia³ w sparingu");
					
					gscore[0]++;
					
					format(TdData[0], 1024, "%s %s~n~", TdData[0], playerNick(playerId));
					format(TdData[2], 1024, "%s %d~n~", TdData[2], pInfo[playerId][player_sparkill]);
					format(TdData[4], 1024, "%s %d~n~", TdData[4], playerScores[i][player_Score]);
					
					 
					
				} else if( pInfo[playerId][player_gang] == g2 ){
				
					if(gscore[1] == 0){
						GivePlayerScore(playerId, 150, "1 miejsce w sparingu");
					}else if(gscore[1] == 1){
						GivePlayerScore(playerId, 80, "2 miejsce w sparingu");
					} else 
					if(gscore[1] == 2){
						GivePlayerScore(playerId, 40, "3 miejsce w sparingu");
					} 
					else GivePlayerScore(playerId, 10, "udzia³ w sparingu");
					
					gscore[1]++;
					
					format(TdData[1], 1024, "%s %s~n~", TdData[1], playerNick(playerId));
					format(TdData[3], 1024, "%s %d~n~", TdData[3], pInfo[playerId][player_sparkill]);
					format(TdData[5], 1024, "%s %d~n~", TdData[5], playerScores[i][player_Score]);
					
				}
				
			}
			 
			m_query("INSERT INTO `"prefix"_gangs_wars` (`id`, `g1`, `g2`, `g1point`, `g2point`, `gfile`, `playerscores`) VALUES (NULL, '%d', '%d', '%d', '%d', '---', '%s');", gInfo[g1][gangid], gInfo[g2][gangid], gangInfo(g1, gangWojnaPoint), gangInfo(g2, gangWojnaPoint), outdb);
			
		}
		gInfo[g2][gangWojnaTrwa] = false;
		gInfo[g1][gangWojnaTrwa] = false;
		
		
		foreach( new i : Player)
		{
			if(!pInfo[i][player_sparmember2]) continue;
			 
			if( pInfo[i][player_gang] == g1 || pInfo[i][player_gang] == g2 ) 
			{
				pInfo[i][player_sparmember2] = false;
			
				if(time != -2)
				{
					#define playerid i
					PlayerTextDrawSetString(playerid, GangSparTd[0][playerid], gangInfo(g1, gangNazwa));
					PlayerTextDrawSetString(playerid, GangSparTd[1][playerid], splitf("%d-%d", gangInfo(g1, gangWojnaPoint) , gangInfo(g2, gangWojnaPoint)) );
					PlayerTextDrawSetString(playerid, GangSparTd[2][playerid], gangInfo(g2, gangNazwa));
					PlayerTextDrawSetString(playerid, GangSparTd[3][playerid], TdData[0]);
					PlayerTextDrawSetString(playerid, GangSparTd[4][playerid], TdData[2]);
					PlayerTextDrawSetString(playerid, GangSparTd[5][playerid], TdData[4]);
					PlayerTextDrawSetStringEx(playerid, GangSparTd[6][playerid], TdData[3]);
					PlayerTextDrawSetString(playerid, GangSparTd[7][playerid], TdData[5]);
					PlayerTextDrawSetString(playerid, GangSparTd[8][playerid], TdData[1]);
					
					
					pInfo[playerid][player_hidespartd] = 20;
				 
					for(new el;el<9;el++) TextDrawShowForPlayer(playerid, GangSparTd0[el]);
					for(new el;el<9;el++) PlayerTextDrawShow(playerid, GangSparTd[el][playerid]);//osobna petla zeby najpierw pojawily sie boxy
					#undef playerid
					 
				}
					 
				pInfo[i][player_gangWarTeam] = 0;
				PlayerEventTD(i, false);
				SetPlayerTeam(i, 10 + i);
				
				pInfo[i][player_sparmember] = false;
				OnPlayerSpawn(i);
			}
		 
		}
	}
	return 1;
}

g_OnPlayerSpawn(playerid)
{
	
	foreach(new zones : GangsZones)
	{
		GangZoneShowForPlayer(playerid, gZone[zones][zonegz], gZone[zones][zonecolor]);
 	}
	return 1;
}
stock ShowGangs(playerid)
{
	static g_string[1024 + (40*MAX_GANGS_CREATE)], g_count;
	g_string[0] = EOS;	
	g_count = 0;
	
	new str[1024 + (40*MAX_GANGS_CREATE)];
	
	
	foreach(new i : Gangs)
	{
		if(strlen(gInfo[i][gangNazwa]) == 0) continue;
		
		format(g_string, sizeof(g_string), "%s{%06x}%s\t{%06x}%s\t%i\n", g_string, gInfo[i][gangColor]>>>8,gInfo[i][gangTag],gInfo[i][gangColor]>>>8, gInfo[i][gangNazwa], gInfo[i][gangPoints]);
					
		pInfo[playerid][player_dialog_data][g_count] = i;
					
		g_count++;
	}
	if(!g_count) g_string = "Brak gangów!";
	
	
	format(str,1024 + (40*MAX_GANGS_CREATE),"Tag\tNazwa gangu\tPunkty\n%s", g_string);
	return str;
}


new brama_ms1;
new brama_ms2;
new brama_ms3;
new garaz_ms;
new Reklama_ms;

 
CMD:bramamso(playerid,cmdtext[])
{
	if(GetGangFromUid(291) != pInfo[playerid][player_gang]) return SendClientMessage(playerid, -1, "No permission");
	MoveObject(brama_ms1,2709.14404,666.42902,8.07662,3);
	return 1;
}
CMD:bramamsz(playerid,cmdtext[])
{
	if(GetGangFromUid(291) != pInfo[playerid][player_gang]) return SendClientMessage(playerid, -1, "No permission");

	MoveObject(brama_ms1,2709.14404,666.42902,11.63500,3);
	return 1;
}
//
CMD:dommso(playerid,cmdtext[])
{
	if(GetGangFromUid(291) != pInfo[playerid][player_gang]) return SendClientMessage(playerid, -1, "No permission");

	MoveObject(brama_ms2,2716.56079,636.71588,9.95900,3);
	MoveObject(brama_ms3,2716.64893,624.10352,16.02900,3);
	MoveObject(garaz_ms,2705.74585,629.03162,11.60300,3);
	return 1;
}
CMD:dommsz(playerid,cmdtext[])
{
	if(GetGangFromUid(291) != pInfo[playerid][player_gang]) return SendClientMessage(playerid, -1, "No permission");

	MoveObject(brama_ms2,2716.57593,635.05200,9.95900,3);
	MoveObject(brama_ms3,2716.60107,622.30798,16.02900,3);
	MoveObject(garaz_ms,2710.68091,632.41699,11.60300,3);
	return 1;
}
stock gbazy_removeBuildingSelect(playerid)
{
	 
	return playerid;
	/*

	//baza u
	RemoveBuildingForPlayer(playerid, 705, -1128.7734, -1758.1953, 113.3047, 0.25);
	
	
	//
	RemoveBuildingForPlayer(playerid, 698, -2863.9922, 2648.0781, 255.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 698, -2852.5859, 2687.7813, 252.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 9277, -2870.9766, 2694.0625, 275.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 9278, -2883.7813, 2560.2422, 262.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 658, -2887.1563, 2535.3984, 253.9219, 0.25);
	RemoveBuildingForPlayer(playerid, 658, -2879.4063, 2567.1484, 257.8750, 0.25);
	RemoveBuildingForPlayer(playerid, 658, -2876.9609, 2599.6328, 263.4922, 0.25);
	RemoveBuildingForPlayer(playerid, 658, -2870.5781, 2649.5000, 268.4531, 0.25);
	RemoveBuildingForPlayer(playerid, 1461, -2716.3359, 1375.9609, 6.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 1232, -2716.0938, 1415.7969, 8.8203, 0.25);
	
	
	
	//thc
	RemoveBuildingForPlayer(playerid, 13137, 646.1641, -527.8984, 28.0703, 0.25);
	RemoveBuildingForPlayer(playerid, 708, -998.1094, -1739.0313, 76.3984, 0.25);
	RemoveBuildingForPlayer(playerid, 3260, -1113.7969, -1668.7891, 76.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3260, -1111.4844, -1669.1641, 76.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 703, -1087.3125, -1674.9219, 75.2969, 0.25);
	RemoveBuildingForPlayer(playerid, 691, -1068.5859, -1662.5781, 75.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 3374, -1088.3906, -1663.7344, 76.8906, 0.25);
	RemoveBuildingForPlayer(playerid, 3374, -1094.5469, -1663.5234, 76.8359, 0.25);
	RemoveBuildingForPlayer(playerid, 691, -982.2266, -1736.2813, 76.4141, 0.25);
	RemoveBuildingForPlayer(playerid, 705, -952.1016, -1694.8594, 75.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 691, -984.1094, -1663.9844, 75.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 708, -948.2578, -1665.0000, 75.3828, 0.25);
	RemoveBuildingForPlayer(playerid, 3425, -1124.7344, -1637.4922, 86.5078, 0.25);
	RemoveBuildingForPlayer(playerid, 3260, -1103.1016, -1635.4219, 76.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3260, -1102.5859, -1637.5938, 76.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 1454, -1089.2031, -1608.7344, 76.1484, 0.25);
	RemoveBuildingForPlayer(playerid, 1454, -1093.1563, -1608.7344, 76.1484, 0.25);
	RemoveBuildingForPlayer(playerid, 1454, -1097.1094, -1608.7344, 76.1484, 0.25);
	RemoveBuildingForPlayer(playerid, 1454, -1101.0625, -1608.7344, 76.1484, 0.25);
	RemoveBuildingForPlayer(playerid, 1454, -1085.2500, -1608.7344, 76.1484, 0.25);
	RemoveBuildingForPlayer(playerid, 1454, -1078.3125, -1608.7344, 76.1484, 0.25);
	RemoveBuildingForPlayer(playerid, 1454, -1074.3594, -1608.7344, 76.1484, 0.25);
	RemoveBuildingForPlayer(playerid, 1454, -1070.4063, -1608.7344, 76.1484, 0.25);
	RemoveBuildingForPlayer(playerid, 1454, -1066.4531, -1608.7344, 76.1484, 0.25);
	RemoveBuildingForPlayer(playerid, 1454, -1062.5000, -1608.7344, 76.1484, 0.25);
	RemoveBuildingForPlayer(playerid, 1413, -1036.0625, -1603.2500, 76.6875, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, -1041.2734, -1603.3516, 76.6719, 0.25);
	RemoveBuildingForPlayer(playerid, 1447, -1046.5391, -1603.3594, 76.7188, 0.25);
	RemoveBuildingForPlayer(playerid, 705, -973.6016, -1646.1016, 75.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1447, -1005.1094, -1602.4375, 76.6484, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, -1010.1641, -1602.6250, 76.6719, 0.25);
	RemoveBuildingForPlayer(playerid, 1413, -1020.4922, -1602.8594, 76.6875, 0.25);
	RemoveBuildingForPlayer(playerid, 1447, -1015.4297, -1602.6328, 76.7188, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, -1025.7344, -1603.0156, 76.6719, 0.25);
	RemoveBuildingForPlayer(playerid, 1447, -1031.0000, -1603.0234, 76.7188, 0.25);
	RemoveBuildingForPlayer(playerid, 1447, -994.7422, -1601.5625, 76.7578, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, -989.4766, -1601.5547, 76.7578, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, -984.4297, -1601.3203, 76.6719, 0.25);
	RemoveBuildingForPlayer(playerid, 1413, -999.8047, -1601.7891, 76.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 1447, -979.2109, -1601.1875, 76.4375, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, -969.1094, -1601.3203, 76.7109, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, -974.1563, -1601.5547, 76.6016, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, -948.7656, -1640.6563, 79.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1023.1328, -1632.4609, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1062.1406, -1631.7188, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1023.1328, -1629.2813, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1023.1328, -1626.1016, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1023.1328, -1622.9766, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1052.3594, -1631.7188, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1042.4375, -1631.7188, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1032.7031, -1622.9766, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1032.6719, -1631.7188, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1032.7031, -1629.2813, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1032.7031, -1626.1016, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1032.7031, -1632.4609, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1032.7031, -1619.9063, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1023.1328, -1631.7188, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1062.1406, -1622.2031, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1052.3594, -1622.2031, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1042.4375, -1622.2031, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1032.6719, -1622.2031, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1023.1328, -1622.2031, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -991.9531, -1688.1875, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -991.9219, -1703.1094, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -991.9531, -1700.6797, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -991.9531, -1697.5000, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -991.9531, -1703.8594, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -991.9531, -1691.3047, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -991.9531, -1694.3750, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -991.9531, -1685.0781, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -982.3828, -1703.1094, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -991.9219, -1693.6016, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -982.3828, -1693.6016, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -991.9219, -1684.1719, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -982.3828, -1684.1719, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1011.9297, -1655.8672, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1011.8984, -1667.6719, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1011.9297, -1665.2422, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1011.9297, -1662.0625, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1011.9297, -1668.4219, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1011.9297, -1652.7500, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1011.9297, -1658.9375, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1011.9297, -1649.6406, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1011.8984, -1658.1563, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1011.8984, -1648.7344, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1000.7500, -1652.7500, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1000.7266, -1667.6719, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1000.7500, -1665.2422, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1000.7500, -1662.0625, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1000.7500, -1668.4219, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1000.7500, -1655.8672, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1000.7500, -1658.9375, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1000.7500, -1649.6406, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1000.7266, -1658.1563, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1000.7266, -1648.7344, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1052.3828, -1632.4609, 75.3672, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1052.3828, -1629.2813, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1052.3828, -1626.1016, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1052.3828, -1622.9766, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1042.4531, -1631.9375, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3261, -1042.4531, -1635.0547, 75.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1023.1328, -1636.3906, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -991.9219, -1688.8438, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -982.3828, -1688.8438, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -982.3828, -1698.2734, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -991.9219, -1698.2734, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -982.3828, -1707.7813, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1011.8984, -1662.8281, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1000.7266, -1672.3438, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1011.8984, -1653.4063, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1032.6719, -1636.3906, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1052.3594, -1636.3906, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1042.4375, -1636.3906, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1062.1406, -1626.8750, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1023.1328, -1626.8750, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1000.7266, -1662.8281, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1000.7266, -1653.4063, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1032.6719, -1626.8750, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1042.4375, -1626.8750, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1052.3594, -1626.8750, 75.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3409, -1062.1406, -1636.3906, 75.3359, 0.25);*/
}
stock gbazy_OnGameModeInit()
{
	Reklama_ms=CreateObject(4238, 2696.7280273438, 658.10601806641, 26.503000259399, 0, 0, 260.25); //reklama
	SetObjectMaterialText(Reklama_ms, "{FFFFFF}www.ms.xaa.pl", 0, OBJECT_MATERIAL_SIZE_256x128,     //reklama
      "Arial", 28, 0, 0xFFFF8200, 0xFF000000, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);                     //reklama
    garaz_ms = CreateObject(4084, 2710.68091, 632.41699, 11.60300,0.00000, 0.00000, 270.25000);    //gara¿
    brama_ms1 = CreateObject(19446, 2709.14404, 666.42902, 11.63500,0.00000, 0.00000, 266.00000);   //brama1
    brama_ms2 = CreateObject(2949, 2716.57593, 635.05200, 9.95900,0.00000, 0.00000, 0.00000);       //brama2
    brama_ms3 = CreateObject(2930, 2716.60107, 622.30798, 16.02900,0.00000, 0.00000, 0.00000);      //brama
    //AUTA//
    AddStaticVehicleEx(487,2711.0859375,628.9849854,14.3999996,0.0000000,-1,-1,15); //Maverick
    AddStaticVehicleEx(411,2708.6279297,625.2940063,10.9069996,0.0000000,-1,-1,15); //Infernus
    AddStaticVehicleEx(411,2712.7338867,625.8939819,10.9069996,0.0000000,-1,-1,15); //Infernus
  	AddStaticVehicleEx(522,2713.8789062,646.5520020,10.5450001,0.0000000,-1,-1,15); //NRG-500
    AddStaticVehicleEx(437,2719.9489746,652.3920288,11.1350002,92.0000000,-1,-1,15); //Coach
	  
	CreateObject(12814, 2717.68750, 641.94141, 9.87700,   0.00000, 0.00000, 0.00000);
	CreateObject(19453, 2706.10156, 624.43750, 11.63500,   0.00000, 0.00000, 0.00000);
	CreateObject(19453, 2710.91504, 619.69397, 11.63500,   0.00000, 0.00000, 270.00000);
	CreateObject(19361, 2706.09204, 630.84601, 11.63500,   0.00000, 0.00000, 0.00000);
	CreateObject(19434, 2706.93701, 632.39099, 11.63500,   0.00000, 0.00000, 270.75000);
	CreateObject(19434, 2714.39111, 632.46600, 11.63500,   0.00000, 0.00000, 272.00000);
	CreateObject(19434, 2715.93799, 632.53998, 11.63500,   0.00000, 0.00000, 272.00000);
	CreateObject(19458, 2716.66797, 627.85999, 11.63500,   0.00000, 0.00000, 0.00000);
	CreateObject(19458, 2720.47412, 619.87097, 11.63500,   0.00000, 0.00000, 272.00000);
	CreateObject(19386, 2716.70508, 621.44702, 11.63500,   0.00000, 0.00000, 0.00000);
	CreateObject(19458, 2725.06641, 624.76172, 11.62700,   0.00000, 0.00000, 1.49963);
	CreateObject(19412, 2724.87695, 631.06299, 11.63500,   0.00000, 0.00000, 1.50000);
	CreateObject(19378, 2724.83984, 637.07422, 15.13600,   0.00000, 0.00000, 0.00000);
	CreateObject(19379, 2711.38403, 627.73901, 10.01100,   0.00000, 90.00000, 0.50000);
	CreateObject(19379, 2711.41699, 624.33600, 10.02100,   0.00000, 90.00000, 0.49988);
	CreateObject(19379, 2719.60498, 633.10101, 9.87300,   0.00000, 90.00000, 0.49988);
	CreateObject(19379, 2719.90503, 624.70697, 9.86100,   0.00000, 90.00000, 0.99988);
	CreateObject(19387, 2716.66602, 634.28003, 11.70900,   0.00000, 0.00000, 0.00000);
	CreateObject(19357, 2716.66504, 637.49799, 11.70900,   0.00000, 0.00000, 0.00000);
	CreateObject(19357, 2717.68994, 640.13098, 11.69700,   0.00000, 0.00000, 318.00000);
	CreateObject(19357, 2720.31006, 641.38599, 11.69700,   0.00000, 0.00000, 274.00000);
	CreateObject(19357, 2723.25781, 641.51563, 11.69700,   0.00000, 0.00000, 270.99976);
	CreateObject(14416, 2721.65308, 639.19702, 9.94700,   0.00000, 0.00000, 271.25000);
	CreateObject(19359, 2723.02197, 637.21503, 11.70900,   0.00000, 0.00000, 270.00000);
	CreateObject(19359, 2720.32910, 637.21399, 11.70900,   0.00000, 0.00000, 270.25000);
	CreateObject(19379, 2720.10107, 631.93701, 13.11000,   0.00000, 90.00000, 270.49438);
	CreateObject(19379, 2720.12402, 625.05566, 13.19700,   0.00000, 90.00000, 271.74683);
	CreateObject(19379, 2711.50806, 627.75098, 13.20800,   0.00000, 90.00000, 0.49988);
	CreateObject(19379, 2711.34106, 624.47198, 13.13600,   0.00000, 90.00000, 0.49988);
	CreateObject(19386, 2716.68701, 621.44202, 15.13500,   0.00000, 0.00000, 0.00000);
	CreateObject(19412, 2725.20410, 621.57703, 15.12700,   0.00000, 0.00000, 0.00000);
	CreateObject(19458, 2720.51172, 619.88770, 15.03300,   0.00000, 0.00000, 271.99951);
	CreateObject(19458, 2725.02637, 627.78027, 14.97200,   0.00000, 0.00000, 1.99951);
	CreateObject(19358, 2716.72510, 624.61298, 15.13500,   0.00000, 0.00000, 0.00000);
	CreateObject(19450, 2716.74097, 631.04700, 15.13500,   0.00000, 0.00000, 0.00000);
	CreateObject(19358, 2716.70605, 637.42798, 15.13400,   0.00000, 0.00000, 358.00000);
	CreateObject(19358, 2723.24097, 641.43701, 15.19300,   0.00000, 0.00000, 272.00000);
	CreateObject(19358, 2720.32690, 641.37701, 15.19600,   0.00000, 0.00000, 272.00000);
	CreateObject(19358, 2717.82202, 640.16901, 15.09600,   0.00000, 0.00000, 319.75000);
	CreateObject(19375, 2720.22363, 637.00195, 18.35900,   0.00000, 64.99512, 0.00000);
	CreateObject(19375, 2718.90332, 627.53613, 21.38400,   0.00000, 24.99939, 0.00000);
	CreateObject(19375, 2723.00781, 627.49219, 21.29100,   0.00000, 154.99512, 0.00000);
	CreateObject(19375, 2720.89209, 632.43298, 21.47200,   0.00000, 0.00000, 270.00000);
	CreateObject(19375, 2721.29810, 622.60400, 20.98400,   0.00000, 0.00000, 268.25000);
	CreateObject(19448, 2720.73926, 621.08496, 16.93900,   0.00000, 90.00000, 268.24768);
	CreateObject(19448, 2720.94189, 641.56897, 17.27900,   20.00000, 0.00000, 272.00000);
	CreateObject(2773, 2717.79297, 637.08502, 13.71300,   0.00000, 0.00000, 266.00000);
	CreateObject(2773, 2720.03101, 636.98700, 13.71300,   0.00000, 0.00000, 270.00000);
	CreateObject(2773, 2722.11304, 637.04700, 13.71300,   0.00000, 0.00000, 270.00000);
	CreateObject(3499, 2724.34009, 626.88702, 15.43900,   0.00000, 0.00000, 0.00000);
	CreateObject(19355, 2723.28711, 623.21802, 11.42200,   0.00000, 0.00000, 272.25000);
	CreateObject(19387, 2721.73291, 621.64203, 11.49700,   0.00000, 0.00000, 0.00000);
	CreateObject(1523, 2721.64990, 622.40997, 9.94700,   0.00000, 0.00000, 276.00000);
	CreateObject(1523, 2716.66602, 622.25299, 9.95700,   0.00000, 0.00000, 276.00000);
	CreateObject(2514, 2724.43506, 620.43903, 9.94700,   0.00000, 0.00000, 270.00000);
	CreateObject(2526, 2723.18506, 622.64801, 9.94700,   0.00000, 0.00000, 0.00000);
	CreateObject(1208, 2722.79492, 620.40100, 9.94700,   0.00000, 0.00000, 0.00000);
	CreateObject(2200, 2719.59692, 637.09998, 9.95900,   0.00000, 0.00000, 0.00000);
	CreateObject(2191, 2721.88110, 636.37299, 9.95900,   0.00000, 0.00000, 0.00000);
	CreateObject(14720, 2724.49512, 624.79102, 9.94700,   0.00000, 0.00000, 182.00000);
	CreateObject(3533, 2722.89111, 626.65601, 8.01700,   0.00000, 0.00000, 0.00000);
	CreateObject(3533, 2720.90088, 626.93597, 8.19200,   0.00000, 0.00000, 0.00000);
	CreateObject(1649, 2724.85010, 631.57599, 11.55100,   0.00000, 0.00000, 90.00000);
	CreateObject(1649, 2725.18311, 622.25500, 15.04300,   0.00000, 0.00000, 90.00000);
	CreateObject(3440, 2715.93311, 636.83002, 10.73500,   0.00000, 0.00000, 0.00000);
	CreateObject(3440, 2716.41211, 633.03699, 10.71000,   0.00000, 0.00000, 0.00000);
	CreateObject(3440, 2706.32593, 632.29700, 10.79800,   0.00000, 0.00000, 0.00000);
	CreateObject(3440, 2716.52710, 620.02899, 10.80800,   0.00000, 0.00000, 0.00000);
	CreateObject(3440, 2706.53296, 620.16602, 10.80800,   0.00000, 0.00000, 0.00000);
	CreateObject(3440, 2716.40796, 632.35602, 10.84800,   0.00000, 0.00000, 0.00000);
	CreateObject(2239, 2724.14990, 636.62201, 9.95900,   0.00000, 0.00000, 0.00000);
	CreateObject(2239, 2717.36597, 636.47699, 13.19600,   0.00000, 0.00000, 0.00000);
	CreateObject(2239, 2724.11401, 634.34399, 13.19600,   0.00000, 0.00000, 0.00000);
	CreateObject(2296, 2724.52002, 635.42798, 9.95900,   0.00000, 0.00000, 270.50000);
	CreateObject(1701, 2720.32300, 631.51300, 9.95900,   0.00000, 0.00000, 94.00000);
	CreateObject(1701, 2720.31006, 628.33502, 9.94700,   0.00000, 0.00000, 92.75000);
	CreateObject(2163, 2716.71997, 634.50702, 13.19600,   0.00000, 0.00000, 90.00000);
	CreateObject(2608, 2716.90894, 633.00403, 13.90700,   0.00000, 0.00000, 90.00000);
	CreateObject(1827, 2722.78394, 629.27802, 9.95900,   0.00000, 0.00000, 0.00000);
	CreateObject(18729, 2721.46899, 622.68402, 17.42500,   0.00000, 0.00000, 0.00000);
	CreateObject(18729, 2724.12109, 625.14502, 13.33300,   0.00000, 0.00000, 0.00000);
	CreateObject(18729, 2717.35693, 626.51501, 13.33300,   0.00000, 0.00000, 0.00000);
	CreateObject(19076, 2721.26758, 643.96875, 9.88500,   0.00000, 0.00000, 0.00000);
	CreateObject(3528, 2721.61597, 634.07501, 23.22400,   0.00000, 0.00000, 80.00000);
	CreateObject(3462, 2707.20410, 634.50500, 11.39900,   0.00000, 0.00000, 280.00000);
	CreateObject(3279, 2717.12695, 661.60352, 9.88500,   0.00000, 0.00000, 271.99402);
	CreateObject(980, 2704.93701, 636.55200, 12.59400,   0.00000, 0.00000, 281.50000);
	CreateObject(980, 2703.56006, 647.79401, 12.59400,   0.00000, 0.00000, 274.00000);
	CreateObject(980, 2703.09473, 659.07227, 12.65800,   0.00000, 0.00000, 90.24719);
	CreateObject(3049, 2707.01611, 666.89899, 12.12700,   0.00000, 0.00000, 0.00000);
	CreateObject(3049, 2702.90088, 666.87799, 12.12700,   0.00000, 0.00000, 94.00000);
	CreateObject(3049, 2720.52002, 666.44000, 12.12700,   0.00000, 0.00000, 0.00000);
	CreateObject(3049, 2716.03101, 666.49103, 12.12700,   0.00000, 0.00000, 0.00000);
	CreateObject(2909, 2718.80176, 663.26172, 17.98225,   0.00000, 0.00000, 0.00000);
	CreateObject(2909, 2706.18799, 626.70001, 14.69100,   0.00000, 0.00000, 0.00000);
	CreateObject(980, 2711.55103, 621.30902, 15.99500,   0.00000, 0.00000, 340.75000);
	CreateObject(19076, 2706.18091, 621.69299, 13.38500,   0.00000, 0.00000, 0.00000);
	CreateObject(980, 2714.74292, 666.38300, 15.80800,   0.00000, 0.00000, 0.00000);
	CreateObject(19429, 2707.49097, 666.71002, 13.83500,   90.00000, 0.00000, 260.50000);
	CreateObject(19429, 2704.18408, 666.89203, 13.91000,   90.00000, 0.00000, 272.75000);
	CreateObject(19429, 2702.78394, 665.11798, 13.88500,   90.00000, 0.00000, 0.00000);
	CreateObject(1259, 2696.85498, 658.75800, 20.96900,   0.00000, 0.00000, 320.00000);
	CreateObject(3508, 2713.64697, 674.12500, 9.77114,   0.00000, 0.00000, 0.00000);
	CreateObject(3508, 2704.56689, 673.93799, 9.82000,   0.00000, 0.00000, 0.00000);
	CreateObject(3508, 2709.04297, 684.12299, 9.82200,   0.00000, 0.00000, 0.00000);
	CreateObject(3508, 2699.81006, 681.86902, 9.82000,   0.00000, 0.00000, 0.00000);
	CreateObject(3508, 2703.27710, 691.88202, 9.84100,   0.00000, 0.00000, 0.00000);
	CreateObject(3508, 2695.60693, 686.79901, 9.81800,   0.00000, 0.00000, 0.00000);
	CreateObject(3508, 2697.32593, 696.64502, 9.82000,   0.00000, 0.00000, 0.00000);
	CreateObject(3508, 2691.87402, 689.54999, 9.81700,   0.00000, 0.00000, 0.00000);
	CreateObject(3508, 2711.92505, 678.97498, 9.82000,   0.00000, 0.00000, 0.00000);
	CreateObject(3508, 2715.16504, 669.82202, 9.82000,   0.00000, 0.00000, 0.00000);
	CreateObject(3508, 2701.95093, 677.69299, 9.82000,   0.00000, 0.00000, 0.00000);
	CreateObject(3508, 2705.57910, 669.32501, 9.82000,   0.00000, 0.00000, 0.00000);
	CreateObject(9237, 2725.59106, 661.28497, 17.87000,   0.00000, 0.00000, 83.99866);
	CreateObject(617, 2721.17212, 648.01703, 9.88500,   0.00000, 0.00000, 0.00000);
	CreateObject(19076, 2706.35303, 639.72101, 9.88500,   0.00000, 0.00000, 0.00000);
	CreateObject(19076, 2705.29712, 648.36902, 9.88500,   0.00000, 0.00000, 0.00000);
	CreateObject(19076, 2704.56592, 659.27002, 9.88500,   0.00000, 0.00000, 0.00000);
	CreateObject(1775, 2717.28711, 629.99402, 14.64600,   0.00000, 0.00000, 88.00000);
	CreateObject(1824, 2723.50708, 630.91498, 13.70700,   0.00000, 0.00000, 270.00000);
	CreateObject(19128, 2718.80688, 627.40399, 13.34500,   0.00000, 0.00000, 0.00000);
	CreateObject(19128, 2722.78589, 627.41498, 13.34500,   0.00000, 0.00000, 0.00000);
	CreateObject(19128, 2718.84009, 631.24799, 13.33300,   0.00000, 0.00000, 0.00000);
	CreateObject(19128, 2722.86206, 631.24200, 13.31300,   0.00000, 0.00000, 0.00000);
	CreateObject(2099, 2723.05688, 625.59198, 13.35800,   0.00000, 0.00000, 0.00000);
	CreateObject(2099, 2721.85303, 625.58301, 13.41500,   0.00000, 0.00000, 0.00000);
	CreateObject(2099, 2724.21899, 625.52502, 13.41500,   0.00000, 0.00000, 0.00000);
	CreateObject(2099, 2720.55493, 624.83398, 13.28300,   0.00000, 0.00000, 50.50000);
	CreateObject(19128, 2718.80396, 623.38800, 13.34500,   0.00000, 0.00000, 0.00000);
	CreateObject(1840, 2717.95190, 625.16901, 13.41500,   0.00000, 0.00000, 0.00000);
	CreateObject(2232, 2717.12402, 627.63397, 14.01300,   0.00000, 0.00000, 88.00000);
	CreateObject(2232, 2719.86011, 620.28198, 13.86300,   0.00000, 0.00000, 180.00000);
	CreateObject(11431, 2733.56909, 662.34900, 11.26500,   0.00000, 0.00000, 94.00000);
	CreateObject(11431, 2732.85596, 624.33600, 11.26300,   0.00000, 0.00000, 92.00000);
	CreateObject(11431, 2732.92798, 633.89600, 11.27000,   0.00000, 0.00000, 0.00000);
	CreateObject(11566, 2727.23608, 646.79999, 11.27100,   0.00000, 0.00000, 0.00000);
	CreateObject(8535, 2745.60693, 646.17297, 16.20200,   0.00000, 0.00000, 0.00000);
	CreateObject(980, 2735.90698, 670.38000, 12.67200,   0.00000, 0.00000, 0.00000);
	CreateObject(980, 2725.54907, 668.64099, 12.62200,   0.00000, 0.00000, 20.00000);
	CreateObject(980, 2747.00903, 669.48401, 12.67200,   0.00000, 0.00000, 348.00000);
	CreateObject(980, 2730.85693, 620.06702, 12.65800,   0.00000, 0.00000, 0.00000);
	CreateObject(980, 2742.21606, 620.04999, 12.67200,   0.00000, 0.00000, 0.00000);
	CreateObject(980, 2752.63403, 622.86298, 12.67200,   0.00000, 0.00000, 30.00000);
	CreateObject(19076, 2738.35010, 628.21899, 9.89800,   0.00000, 0.00000, 0.00000);

	//baza GJ
	/*
	CreateDynamicObject(3279, 1190.51611, 2570.04492, 9.37561,   0.00000, 0.00000, 181.53404);
	CreateDynamicObject(3279, 1191.02161, 2531.02881, 9.37561,   0.00000, 0.00000, 181.53404);
	CreateDynamicObject(3279, 1111.81470, 2529.23535, 9.37561,   0.00000, 0.00000, 64.31743);
	CreateDynamicObject(3279, 1119.44019, 2598.39429, 9.37561,   0.00000, 0.00000, 329.67181);
	CreateDynamicObject(18850, 1184.31616, 2549.48926, 12.88968,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3601, 1131.86768, 2536.69507, 9.76286,   0.00000, 0.00000, 80.80857);
	CreateDynamicObject(17324, 1145.94214, 2593.23853, 9.80452,   0.00000, 0.00000, 356.05917);
	CreateDynamicObject(3601, 1157.35840, 2532.59985, 9.76286,   0.00000, 0.00000, 79.85696);
	CreateDynamicObject(17324, 1175.82214, 2583.16309, 9.80452,   0.00000, 0.00000, 328.50870);
	CreateDynamicObject(17324, 1161.33960, 2589.69531, 9.80452,   0.00000, 0.00000, 341.56909);
	CreateDynamicObject(3749, 1105.89038, 2564.64014, 15.23240,   0.00000, 0.00000, 262.15295);
	CreateDynamicObject(10828, 1128.91675, 2619.06152, 16.91753,   0.00000, 0.00000, 172.07161);
	CreateDynamicObject(10828, 1108.63574, 2591.11841, 16.91753,   0.00000, 0.00000, 262.66257);
	CreateDynamicObject(10828, 1110.62292, 2604.81763, 16.91753,   0.00000, 0.00000, 262.66257);
	CreateDynamicObject(10828, 1154.95435, 2517.13770, 16.91753,   0.00000, 0.00000, 174.50844);
	CreateDynamicObject(10828, 1162.79541, 2614.18018, 16.91753,   0.00000, 0.00000, 172.07161);
	CreateDynamicObject(10828, 1189.66589, 2598.51953, 16.91753,   0.00000, 0.00000, 126.69746);
	CreateDynamicObject(10828, 1201.24316, 2567.68848, 16.91753,   0.00000, 0.00000, 94.79129);
	CreateDynamicObject(10828, 1203.93091, 2534.79321, 16.91753,   0.00000, 0.00000, 94.79129);
	CreateDynamicObject(10828, 1189.14246, 2516.94336, 16.91753,   0.00000, 0.00000, 184.74408);
	CreateDynamicObject(10828, 1104.39209, 2538.45264, 16.91753,   0.00000, 0.00000, 270.00131);
	CreateDynamicObject(10828, 1121.05432, 2520.43286, 16.91753,   0.00000, 0.00000, 174.50844);
	CreateDynamicObject(3601, 1144.29126, 2536.05615, 9.76286,   0.00000, 0.00000, 170.58473);
	bramaganjamafia = CreateDynamicObject(980, 1105.44531, 2564.65137, 12.32633,   0.00000, 0.00000, 84.87215);
	statusbramy=true;
	CreateVehicle(567, 1174.4581, 2589.2671, 10.7308, 151.9406, -1, -1, 100);
	CreateVehicle(567, 1142.1855, 2597.4595, 10.7308, 174.2074, -1, -1, 100);
	CreateVehicle(567, 1158.6335, 2594.8076, 10.7308, 164.4689, -1, -1, 100);

	//baza U
		 
	CreateDynamicObject(8661, -1106.48169, -1764.64954, 114.73262,   0.00000, 0.00000, -38.28002);
	CreateDynamicObject(8661, -1115.02112, -1756.28296, 112.54593,   0.00000, 180.00000, -34.08000);
	CreateDynamicObject(18981, -1090.53174, -1799.17358, 114.24749,   0.00000, 90.00000, -108.00005);
	CreateDynamicObject(18981, -1139.92334, -1800.97876, 114.24749,   0.00000, 90.00000, -55.38005);
	CreateDynamicObject(18762, -1080.04871, -1788.26538, 114.24402,   0.00000, 90.00000, -56.16001);
	CreateDynamicObject(18762, -1082.82739, -1784.10645, 114.24402,   0.00000, 90.00000, -56.16001);
	CreateDynamicObject(18762, -1085.59290, -1779.96423, 114.24402,   0.00000, 90.00000, -56.40001);
	CreateDynamicObject(18762, -1088.36023, -1775.82202, 114.24402,   0.00000, 90.00000, -56.16001);
	CreateDynamicObject(18980, -1085.31763, -1769.26453, 102.24111,   0.00000, 0.00000, -38.27999);
	CreateDynamicObject(18980, -1115.90942, -1745.12000, 102.24111,   0.00000, 0.00000, -38.27999);
	CreateDynamicObject(18980, -1075.42310, -1791.49329, 101.44189,   0.00000, 0.00000, -17.75998);
	CreateDynamicObject(18980, -1082.85291, -1814.27283, 101.44189,   0.00000, 0.00000, -17.75998);
	CreateDynamicObject(3279, -1139.45557, -1767.15771, 108.09219,   0.00000, 0.00000, -69.90002);
	CreateDynamicObject(3279, -1119.71277, -1801.54370, 108.48830,   0.00000, 0.00000, 74.69999);
	CreateDynamicObject(19313, -1090.45923, -1828.76440, 110.90848,   0.00000, 0.00000, -162.35992);
	CreateDynamicObject(19313, -1104.04749, -1831.05652, 110.90848,   0.00000, 0.00000, -178.67987);
	CreateDynamicObject(19313, -1104.04749, -1831.05652, 104.37546,   0.00000, 0.00000, -178.67987);
	CreateDynamicObject(19313, -1117.54797, -1828.66650, 110.90848,   0.00000, 0.00000, -201.35989);
	CreateDynamicObject(19313, -1130.57080, -1823.58972, 110.90848,   0.00000, 0.00000, -201.35989);
	CreateDynamicObject(19313, -1143.60181, -1818.51733, 110.90848,   0.00000, 0.00000, -201.35989);
	CreateDynamicObject(19313, -1154.09595, -1810.24280, 110.90848,   0.00000, 0.00000, -235.25990);
	CreateDynamicObject(19313, -1158.07556, -1797.53467, 110.90848,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1158.03162, -1783.51025, 110.90848,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1157.98804, -1769.60986, 110.90848,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1157.93286, -1755.64771, 110.90848,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1151.16479, -1746.89465, 110.90848,   0.00000, 0.00000, -345.29968);
	CreateDynamicObject(19313, -1137.43518, -1744.28955, 110.90848,   0.00000, 0.00000, -353.27939);
	CreateDynamicObject(19313, -1123.55957, -1743.82104, 110.90848,   0.00000, 0.00000, -363.11902);
	CreateDynamicObject(19313, -1110.53711, -1747.45117, 110.90848,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(19313, -1098.22815, -1754.09619, 110.90848,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(19313, -1085.88171, -1760.65076, 110.90848,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(19313, -1076.43530, -1770.10925, 110.90848,   0.00000, 0.00000, -421.73904);
	CreateDynamicObject(19313, -1070.67151, -1782.77148, 110.90848,   0.00000, 0.00000, -430.01871);
	CreateDynamicObject(19313, -1070.65283, -1795.87866, 110.90848,   0.00000, 0.00000, -469.97879);
	CreateDynamicObject(19313, -1075.43542, -1809.02979, 110.90848,   0.00000, 0.00000, -469.97879);
	CreateDynamicObject(19313, -1080.55090, -1820.43286, 110.90848,   0.00000, 0.00000, -477.65933);
	CreateDynamicObject(19313, -1075.43542, -1809.02979, 104.49189,   0.00000, 0.00000, -469.97879);
	CreateDynamicObject(19313, -1070.65283, -1795.87866, 104.41441,   0.00000, 0.00000, -469.97879);
	CreateDynamicObject(19313, -1070.65222, -1782.76636, 104.45045,   0.00000, 0.00000, -430.01871);
	CreateDynamicObject(19313, -1076.43530, -1770.10925, 117.39272,   0.00000, 0.00000, -421.73904);
	CreateDynamicObject(19313, -1076.43530, -1770.10925, 104.31656,   0.00000, 0.00000, -421.73904);
	CreateDynamicObject(19313, -1076.43530, -1770.10925, 97.84059,   0.00000, 0.00000, -421.73904);
	CreateDynamicObject(19313, -1070.65222, -1782.76636, 97.91663,   0.00000, 0.00000, -430.01871);
	CreateDynamicObject(19313, -1085.88171, -1760.65076, 104.45344,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(19313, -1085.88171, -1760.65076, 97.94246,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(19313, -1098.22815, -1754.09619, 104.52778,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(19313, -1098.22815, -1754.09619, 98.09131,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(19313, -1110.53711, -1747.45117, 104.30881,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(19313, -1110.53711, -1747.45117, 97.97603,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(19313, -1123.55957, -1743.82104, 104.36230,   0.00000, 0.00000, -363.11902);
	CreateDynamicObject(19313, -1123.55957, -1743.82104, 117.40333,   0.00000, 0.00000, -363.11902);
	CreateDynamicObject(19313, -1098.22815, -1754.09619, 117.48292,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(19313, -1137.43518, -1744.28955, 104.43966,   0.00000, 0.00000, -353.27939);
	CreateDynamicObject(19313, -1137.43518, -1744.28955, 117.41430,   0.00000, 0.00000, -353.27939);
	CreateDynamicObject(19313, -1151.16479, -1746.89465, 117.42165,   0.00000, 0.00000, -345.29968);
	CreateDynamicObject(19313, -1157.93286, -1755.64771, 117.40990,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1157.98804, -1769.60986, 117.42845,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1158.03162, -1783.51025, 117.44130,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1158.03162, -1783.51025, 104.38235,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1158.07556, -1797.53467, 104.44791,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1158.07556, -1797.53467, 117.44694,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1154.09595, -1810.24280, 104.50075,   0.00000, 0.00000, -235.25990);
	CreateDynamicObject(19313, -1154.09595, -1810.24280, 97.87093,   0.00000, 0.00000, -235.25990);
	CreateDynamicObject(19313, -1158.07556, -1797.53467, 97.91331,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1143.60181, -1818.51733, 104.39404,   0.00000, 0.00000, -201.35989);
	CreateDynamicObject(19313, -1143.60181, -1818.51733, 97.97987,   0.00000, 0.00000, -201.35989);
	CreateDynamicObject(19313, -1130.57080, -1823.58972, 104.36393,   0.00000, 0.00000, -201.35989);
	CreateDynamicObject(19313, -1143.60181, -1818.51733, 117.38379,   0.00000, 0.00000, -201.35989);
	CreateDynamicObject(19313, -1130.57080, -1823.58972, 117.37494,   0.00000, 0.00000, -201.35989);
	CreateDynamicObject(19313, -1117.54797, -1828.66650, 104.42890,   0.00000, 0.00000, -201.35989);
	CreateDynamicObject(19313, -1117.54797, -1828.66650, 117.37066,   0.00000, 0.00000, -201.35989);
	CreateDynamicObject(19313, -1104.04749, -1831.05652, 117.39453,   0.00000, 0.00000, -178.67987);
	CreateDynamicObject(19313, -1090.45923, -1828.76440, 117.40215,   0.00000, 0.00000, -162.35992);
	CreateDynamicObject(19313, -1080.55090, -1820.43286, 117.43976,   0.00000, 0.00000, -477.65933);
	CreateDynamicObject(19313, -1070.65283, -1795.87866, 117.45724,   0.00000, 0.00000, -469.97879);
	CreateDynamicObject(19313, -1070.65283, -1795.87866, 124.05542,   0.00000, 0.00000, -469.97879);
	CreateDynamicObject(19313, -1070.65283, -1795.87866, 130.68764,   0.00000, 0.00000, -469.97879);
	CreateDynamicObject(19313, -1076.43530, -1770.10925, 123.96111,   0.00000, 0.00000, -421.73904);
	CreateDynamicObject(19313, -1076.43530, -1770.10925, 130.47409,   0.00000, 0.00000, -421.73904);
	CreateDynamicObject(19313, -1098.22815, -1754.09619, 123.90877,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(19313, -1098.22815, -1754.09619, 130.45534,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(19313, -1123.55957, -1743.82104, 123.86132,   0.00000, 0.00000, -363.11902);
	CreateDynamicObject(19313, -1123.55957, -1743.82104, 130.29948,   0.00000, 0.00000, -363.11902);
	CreateDynamicObject(19313, -1137.43518, -1744.28955, 123.83718,   0.00000, 0.00000, -353.27939);
	CreateDynamicObject(19313, -1137.43518, -1744.28955, 130.25302,   0.00000, 0.00000, -353.27939);
	CreateDynamicObject(19313, -1151.16479, -1746.89465, 123.76122,   0.00000, 0.00000, -345.29968);
	CreateDynamicObject(19313, -1151.16479, -1746.89465, 130.20387,   0.00000, 0.00000, -345.29968);
	CreateDynamicObject(19313, -1157.93286, -1755.64771, 123.88219,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1157.93286, -1755.64771, 130.29527,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1157.98804, -1769.60986, 123.93054,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1157.98804, -1769.60986, 130.21532,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1158.03162, -1783.51025, 123.82184,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1158.03162, -1783.51025, 130.32204,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1158.07556, -1797.53467, 123.98643,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1158.07556, -1797.53467, 130.38582,   0.00000, 0.00000, -270.23962);
	CreateDynamicObject(19313, -1154.09595, -1810.24280, 123.90125,   0.00000, 0.00000, -235.25990);
	CreateDynamicObject(19313, -1154.09595, -1810.24280, 130.40218,   0.00000, 0.00000, -235.25990);
	CreateDynamicObject(19313, -1130.57080, -1823.58972, 123.84741,   0.00000, 0.00000, -201.35989);
	CreateDynamicObject(19313, -1130.57080, -1823.58972, 130.35579,   0.00000, 0.00000, -201.35989);
	CreateDynamicObject(19313, -1143.60181, -1818.51733, 123.74853,   0.00000, 0.00000, -201.35989);
	CreateDynamicObject(19313, -1143.60181, -1818.51733, 130.31973,   0.00000, 0.00000, -201.35989);
	CreateDynamicObject(19313, -1117.54797, -1828.66650, 123.89468,   0.00000, 0.00000, -201.35989);
	CreateDynamicObject(19313, -1117.54797, -1828.66650, 130.37889,   0.00000, 0.00000, -201.35989);
	CreateDynamicObject(19313, -1104.04749, -1831.05652, 123.81182,   0.00000, 0.00000, -178.67987);
	CreateDynamicObject(19313, -1104.04749, -1831.05652, 130.31316,   0.00000, 0.00000, -178.67987);
	CreateDynamicObject(19313, -1090.45923, -1828.76440, 123.80958,   0.00000, 0.00000, -162.35992);
	CreateDynamicObject(19313, -1090.45923, -1828.76440, 130.18147,   0.00000, 0.00000, -162.35992);
	CreateDynamicObject(19313, -1080.55090, -1820.43286, 123.98987,   0.00000, 0.00000, -477.65933);
	CreateDynamicObject(19313, -1080.55090, -1820.43286, 130.47327,   0.00000, 0.00000, -477.65933);
	CreateDynamicObject(19313, -1075.43542, -1809.02979, 124.05777,   0.00000, 0.00000, -469.97879);
	CreateDynamicObject(19313, -1075.43542, -1809.02979, 130.52618,   0.00000, 0.00000, -469.97879);
	CreateDynamicObject(19313, -1070.67151, -1782.77148, 124.13228,   0.00000, 0.00000, -430.01871);
	CreateDynamicObject(19313, -1070.67151, -1782.77148, 130.47919,   0.00000, 0.00000, -430.01871);
	CreateDynamicObject(19313, -1085.88171, -1760.65076, 123.90602,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(19313, -1085.88171, -1760.65076, 130.43509,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(19313, -1110.53711, -1747.45117, 123.84270,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(19313, -1110.53711, -1747.45117, 130.35698,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(18753, -1130.86633, -1802.46204, 133.08508,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19313, -1110.53711, -1747.45117, 120.16118,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(19313, -1085.88171, -1760.65076, 120.22165,   0.00000, 0.00000, -388.49884);
	CreateDynamicObject(19313, -1070.67151, -1782.77148, 119.94620,   0.00000, 0.00000, -430.01871);
	CreateDynamicObject(19313, -1075.43542, -1809.02979, 119.74371,   0.00000, 0.00000, -469.97879);
	CreateDynamicObject(19313, -1154.09595, -1810.24280, 119.76409,   0.00000, 0.00000, -235.25990);
	CreateDynamicObject(3383, -1101.45630, -1756.78137, 114.68969,   0.00000, 0.00000, 141.41986);
	CreateDynamicObject(348, -1100.91431, -1757.42419, 115.74409,   0.00000, 0.00000, -3.48000);
	CreateDynamicObject(358, -1101.95374, -1756.78625, 115.74403,   0.00000, 0.00000, 49.02000);
	CreateDynamicObject(358, -1102.53088, -1756.28821, 115.74403,   0.00000, 0.00000, 49.02000);
	CreateDynamicObject(358, -1102.17896, -1756.58655, 115.74403,   0.00000, 0.00000, 49.02000);
	CreateDynamicObject(348, -1101.53308, -1756.68579, 115.74409,   0.00000, 0.00000, -3.48000);
	CreateDynamicObject(348, -1101.57825, -1757.32190, 115.74409,   0.00000, 0.00000, -3.48000);
	CreateDynamicObject(358, -1100.54602, -1758.09436, 115.74403,   0.00000, 0.00000, 49.02000);
	CreateDynamicObject(1481, -1098.16638, -1759.45642, 115.42018,   0.00000, 0.00000, -40.97998);
	CreateDynamicObject(1432, -1104.99341, -1755.36804, 114.84721,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1255, -1115.88770, -1746.68567, 115.25353,   0.00000, 0.00000, 22.08000);
	CreateDynamicObject(1255, -1115.42126, -1749.27002, 115.25353,   0.00000, 0.00000, 41.52001);
	CreateDynamicObject(1255, -1108.38513, -1754.31885, 115.25353,   0.00000, 0.00000, 61.98002);
	CreateDynamicObject(1255, -1110.63379, -1753.14709, 115.25353,   0.00000, 0.00000, 56.46002);
	CreateDynamicObject(1255, -1095.16296, -1763.58398, 115.25353,   0.00000, 0.00000, 31.32002);
	CreateDynamicObject(1255, -1091.79785, -1767.53394, 115.25353,   0.00000, 0.00000, 60.12003);
	CreateDynamicObject(1255, -1088.12402, -1769.64917, 115.25353,   0.00000, 0.00000, 72.66003);
	CreateDynamicObject(762, -1098.21863, -1788.84546, 116.64216,   0.00000, 0.00000, -37.32000);
	CreateDynamicObject(762, -1099.08740, -1796.78577, 115.97783,   0.00000, 0.00000, -87.71998);
	CreateDynamicObject(762, -1102.38416, -1800.37781, 116.10855,   0.00000, 0.00000, -87.71998);
	CreateDynamicObject(3608, -1132.53979, -1785.59790, 112.00104,   0.00000, 0.00000, 91.07999);
	CreateDynamicObject(3641, -1112.49194, -1768.21594, 116.93047,   0.00000, 0.00000, 52.07996);

	 //
 
	CreateDynamicObject(18981, -2855.80713, 2631.40356, 271.76633,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(18981, -2855.81738, 2656.39868, 271.76633,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(18981, -2830.80859, 2631.39648, 271.76633,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(18981, -2830.82935, 2656.39160, 271.76633,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(18981, -2830.82080, 2606.39673, 271.76633,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(18981, -2855.80054, 2606.39502, 271.76633,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(18770, -2870.21387, 2594.98779, 185.71785,   0.08000, 30.68001, 0.00000);
	CreateDynamicObject(18770, -2870.12134, 2632.09766, 185.71785,   0.08000, 30.68001, 0.00000);
	CreateDynamicObject(18770, -2870.26050, 2667.96826, 185.71785,   0.08000, 30.68001, 0.00000);
	CreateDynamicObject(18791, -2907.22827, 2598.07178, 271.89783,   0.06000, 0.00000, -158.22044);
	CreateDynamicObject(18791, -2963.02686, 2543.67090, 271.89783,   0.06000, 0.00000, -113.22053);
	CreateDynamicObject(18789, -2971.85840, 2434.66064, 245.75391,   0.00000, 20.44001, -90.53999);
	CreateDynamicObject(18766, -2823.34229, 2668.39502, 274.71976,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3858, -2818.76758, 2650.84473, 274.33530,   0.00000, 0.00000, -225.03996);
	CreateDynamicObject(18766, -2833.31201, 2668.39746, 274.71976,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, -2843.28882, 2668.39551, 274.71976,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3858, -2818.79639, 2636.29932, 274.33530,   0.00000, 0.00000, -225.03996);
	CreateDynamicObject(18766, -2853.17114, 2668.39136, 274.71976,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, -2857.67822, 2662.91455, 274.71976,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2857.68115, 2652.94067, 274.71976,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2852.28125, 2648.42944, 274.71976,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, -2847.76050, 2642.93262, 274.71976,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2823.38086, 2608.67944, 274.71976,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, -2833.26880, 2608.65308, 274.71976,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, -2843.25708, 2608.66260, 274.71976,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, -2847.75854, 2632.93604, 274.71976,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2847.76807, 2622.95801, 274.71976,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(18762, -2818.82788, 2643.52783, 274.72250,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2847.77271, 2617.45654, 274.72250,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2847.75977, 2609.62207, 274.72250,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1491, -2848.09399, 2615.39844, 272.26276,   0.00000, 0.00000, 88.80000);
	CreateDynamicObject(18762, -2847.81494, 2614.91553, 274.72250,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1491, -2848.11694, 2612.87891, 272.26276,   0.00000, 0.00000, 88.80000);
	CreateDynamicObject(18762, -2847.83691, 2612.37451, 274.72250,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1491, -2848.15894, 2610.35742, 272.26276,   0.00000, 0.00000, 88.80000);
	CreateDynamicObject(18762, -2847.76514, 2609.92334, 274.72250,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2847.80493, 2614.45605, 275.22150,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2847.80493, 2614.45605, 276.18097,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2847.80493, 2614.45605, 277.16043,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2847.66504, 2610.74976, 275.22150,   90.00000, 0.00000, -0.78000);
	CreateDynamicObject(18762, -2847.66504, 2610.74976, 276.19797,   90.00000, 0.00000, -0.78000);
	CreateDynamicObject(18762, -2847.71167, 2610.67285, 277.17444,   90.00000, 0.00000, -0.30000);
	CreateDynamicObject(18981, -2830.82935, 2656.39160, 277.66550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(18981, -2830.83057, 2631.40234, 277.66550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(18766, -2820.83374, 2613.95581, 277.67572,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2825.84033, 2613.94458, 276.84265,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2830.82275, 2613.90039, 276.82642,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2835.82080, 2613.95972, 277.70294,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2840.80469, 2613.95947, 277.67572,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2845.69141, 2613.93994, 277.67572,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2845.70874, 2623.92432, 277.67572,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2845.68872, 2633.88672, 277.67572,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2845.71045, 2643.89282, 277.67572,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2845.71094, 2653.86548, 277.67572,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2845.71802, 2663.83032, 277.67572,   90.00000, 0.00000, -89.94000);
	CreateDynamicObject(18766, -2850.67871, 2663.82422, 277.67572,   90.00000, 0.00000, -89.94000);
	CreateDynamicObject(18766, -2850.69653, 2653.86987, 277.67572,   90.00000, 0.00000, -89.94000);
	CreateDynamicObject(18762, -2820.83667, 2608.65137, 277.67401,   90.00000, 0.00000, 90.00001);
	CreateDynamicObject(18762, -2825.80273, 2608.65674, 277.65799,   90.00000, 0.00000, 90.00001);
	CreateDynamicObject(18762, -2830.78809, 2608.65649, 277.66171,   90.00000, 0.00000, 90.00001);
	CreateDynamicObject(18762, -2835.79272, 2608.66260, 277.66171,   90.00000, 0.00000, 90.00001);
	CreateDynamicObject(18762, -2840.78101, 2608.67114, 277.66171,   90.00000, 0.00000, 90.00001);
	CreateDynamicObject(18762, -2845.69409, 2608.67700, 277.66171,   90.00000, 0.00000, 90.00001);
	CreateDynamicObject(18762, -2850.69360, 2648.45166, 277.66171,   90.00000, 0.00000, 90.00001);
	CreateDynamicObject(18762, -2855.67480, 2648.45410, 277.66171,   90.00000, 0.00000, 90.00001);
	CreateDynamicObject(18762, -2855.67529, 2668.34229, 277.66171,   90.00000, 0.00000, 90.00001);
	CreateDynamicObject(18762, -2857.67969, 2665.36963, 277.67569,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2857.68213, 2660.38501, 277.67569,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, -2815.83569, 2643.37207, 277.67572,   90.00000, 0.00000, -89.94000);
	CreateDynamicObject(18762, -2813.90869, 2647.87695, 280.60989,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2813.91772, 2638.86182, 280.60989,   0.00000, 0.00000, 0.06000);
	CreateDynamicObject(18766, -2815.91577, 2643.37598, 283.59247,   90.00000, 0.00000, -89.94000);
	CreateDynamicObject(3858, -2818.33545, 2656.50269, 280.19455,   0.00000, 0.00000, -225.03996);
	CreateDynamicObject(18766, -2818.83203, 2662.90527, 274.71976,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(18762, -2818.83008, 2664.25537, 280.60989,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2818.83447, 2648.85669, 280.60989,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2818.84180, 2637.86523, 280.60989,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3858, -2818.34204, 2630.18652, 280.19455,   0.00000, 0.00000, -225.03996);
	CreateDynamicObject(18762, -2818.83667, 2622.44043, 280.60989,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2818.84546, 2665.23706, 280.60989,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2818.83252, 2666.23950, 280.60989,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2818.81982, 2667.24121, 280.60989,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2818.82544, 2668.22217, 280.60989,   0.00000, 0.00000, -0.18000);
	CreateDynamicObject(3858, -2826.59961, 2668.68799, 280.19455,   0.00000, 0.00000, -314.92001);
	CreateDynamicObject(18762, -2834.37134, 2668.22852, 280.60989,   0.00000, 0.00000, -0.18000);
	CreateDynamicObject(3858, -2842.09985, 2668.66943, 280.19455,   0.00000, 0.00000, -314.92001);
	CreateDynamicObject(18766, -2853.21387, 2668.20605, 280.67001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, -2857.67822, 2662.91455, 280.63873,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2857.63989, 2652.97363, 280.63873,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2853.09937, 2648.48193, 280.67001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, -2847.61450, 2643.98047, 280.69067,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(18762, -2847.60913, 2638.48267, 280.68973,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3858, -2847.99292, 2630.71924, 280.19455,   0.00000, 0.00000, -225.03996);
	CreateDynamicObject(18762, -2847.62964, 2623.00293, 280.60989,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3858, -2840.03076, 2621.86523, 280.19455,   0.00000, 0.00000, -314.92001);
	CreateDynamicObject(18762, -2847.63306, 2622.28198, 280.60989,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2832.26172, 2622.30859, 280.60989,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18981, -2830.89648, 2656.27515, 283.55264,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(18981, -2830.77490, 2634.28564, 283.57260,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(18766, -2845.66919, 2626.73096, 283.58630,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2845.64355, 2637.67310, 283.58630,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2845.64355, 2647.62305, 283.58630,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2845.64282, 2657.61890, 283.58630,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2850.62524, 2652.96436, 283.58630,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2855.61353, 2652.97095, 283.58630,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2855.60205, 2662.95728, 283.58630,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2850.61084, 2662.95898, 283.58630,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2845.89429, 2663.81714, 283.58578,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(18762, -2855.58838, 2668.29028, 283.57913,   90.00000, 0.00000, 90.00001);
	CreateDynamicObject(18762, -2850.71387, 2668.30762, 283.57913,   90.00000, 0.00000, 90.00001);
	CreateDynamicObject(18762, -2845.63452, 2632.22803, 283.58392,   90.00000, 0.00000, 90.00001);
	CreateDynamicObject(18762, -2818.90430, 2668.26294, 286.50473,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18981, -2823.57080, 2657.57446, 295.30841,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(18800, -2841.56494, 2698.67480, 283.25220,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(18762, -2818.90430, 2668.26294, 289.57330,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2818.90430, 2668.26294, 292.51614,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2819.10205, 2646.03638, 293.24710,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2819.10205, 2646.03638, 288.43073,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2819.10205, 2646.03638, 286.19702,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2835.56641, 2645.59644, 293.24710,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2835.56641, 2645.59644, 288.33707,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2835.56641, 2645.59644, 286.06604,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2835.17554, 2668.24365, 286.04010,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2835.17554, 2668.24365, 291.05478,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2835.17554, 2668.24365, 293.06229,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18981, -2830.79883, 2581.40430, 271.76633,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(18981, -2855.78906, 2581.40308, 271.76633,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(18770, -2870.23926, 2570.07446, 185.71785,   0.08000, 30.68001, 0.00000);
	CreateDynamicObject(18770, -2867.27588, 2569.93042, 171.80443,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(984, -2811.10864, 2663.65063, 296.42374,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(984, -2811.10425, 2651.48730, 296.42374,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(984, -2836.02930, 2651.49512, 296.42374,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(984, -2836.04370, 2663.66382, 296.42374,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(984, -2829.60425, 2645.09448, 296.42374,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(984, -2817.49707, 2645.10010, 296.42374,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(983, -2832.81543, 2670.03149, 296.46979,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(983, -2829.60254, 2670.01514, 296.46979,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(983, -2832.82251, 2649.89111, 296.46979,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(983, -2832.77393, 2654.69116, 296.46979,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(983, -2832.83032, 2659.56812, 296.46979,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(983, -2832.84497, 2664.74512, 296.46979,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1223, -2811.26538, 2668.41748, 295.80029,   0.00000, 0.00000, -179.99982);
	CreateDynamicObject(1223, -2826.62134, 2668.55103, 295.80029,   0.00000, 0.00000, -357.05869);
	CreateDynamicObject(1238, -2811.36670, 2654.06470, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2811.73486, 2653.31689, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2812.19873, 2652.69238, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2812.68188, 2652.08862, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2813.18213, 2651.56567, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2813.68018, 2651.10278, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2814.22534, 2650.63086, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2814.75513, 2650.17163, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2815.34326, 2649.68848, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2815.89551, 2649.31616, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2816.46484, 2648.90259, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2817.06250, 2648.49121, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2817.72778, 2648.12817, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2818.38721, 2647.84912, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2819.09229, 2647.53003, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2819.76514, 2647.26587, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2820.45313, 2646.98755, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2821.14111, 2646.70972, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2821.81567, 2646.41772, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2822.50098, 2646.19800, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2823.31104, 2645.97070, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2824.07666, 2645.73853, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2824.83716, 2645.55029, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1238, -2825.51563, 2645.36987, 296.11899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3471, -2813.60303, 2647.75464, 297.02960,   0.00000, 0.00000, 130.38007);
	CreateDynamicObject(18789, -2973.15820, 2294.37134, 193.46123,   0.00000, 20.44001, -90.53999);
	CreateDynamicObject(18789, -2974.47168, 2154.69971, 141.40477,   0.00000, 20.44001, -90.53999);
	CreateDynamicObject(18789, -2975.78760, 2016.01074, 89.73623,   0.00000, 20.44001, -90.53999);
	CreateDynamicObject(18789, -2977.04858, 1882.97583, 40.15790,   0.00000, 20.44001, -90.53999);
	CreateDynamicObject(14414, -2855.21436, 2655.89233, 274.96735,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, -2852.23535, 2651.43188, 277.68423,   90.00000, 0.00000, -181.02000);
	CreateDynamicObject(18762, -2857.69531, 2655.41626, 277.67569,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2857.66797, 2650.80542, 277.67569,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, -2852.68042, 2652.93945, 274.71976,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2824.31226, 2643.53564, 274.71976,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, -2834.26196, 2643.50244, 274.71976,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, -2839.69482, 2639.03882, 274.71976,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2839.69702, 2629.07959, 274.71976,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(18766, -2839.70483, 2619.09790, 274.71976,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(18762, -2818.80933, 2629.04272, 274.72250,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3858, -2818.67969, 2621.30371, 274.33530,   0.00000, 0.00000, -225.03996);
	CreateDynamicObject(18762, -2818.82715, 2613.51978, 274.72250,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2818.83496, 2612.53687, 274.72250,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2818.84375, 2611.53418, 274.72250,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2818.84619, 2610.55103, 274.72250,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2818.86133, 2609.58936, 274.72250,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(982, -2835.90063, 2630.30688, 272.60205,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2838.39014, 2642.86987, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2836.64404, 2640.80762, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2838.08154, 2639.57935, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2837.71826, 2640.51636, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2836.78833, 2637.14209, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2836.66992, 2634.75244, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2837.17041, 2633.31104, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2837.99487, 2631.56982, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2836.77759, 2629.54883, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2838.38403, 2635.56226, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2838.02930, 2636.83008, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2837.99683, 2626.15259, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2836.98999, 2626.66455, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2836.98999, 2626.66455, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2836.98999, 2626.66455, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2837.99683, 2626.15259, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2837.99683, 2626.15259, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2836.77759, 2629.54883, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2836.77759, 2629.54883, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2837.99487, 2631.56982, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2837.99487, 2631.56982, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2837.17041, 2633.31104, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2837.17041, 2633.31104, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2838.02930, 2636.83008, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2838.02930, 2636.83008, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2836.66992, 2634.75244, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2836.66992, 2634.75244, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2838.38403, 2635.56226, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2838.38403, 2635.56226, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2838.08154, 2639.57935, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2838.08154, 2639.57935, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2836.78833, 2637.14209, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2836.78833, 2637.14209, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2837.71826, 2640.51636, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2837.71826, 2640.51636, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2836.64404, 2640.80762, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2836.64404, 2640.80762, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2838.39014, 2642.86987, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2838.39014, 2642.86987, 272.19266,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(982, -2832.59546, 2630.32129, 272.64194,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2835.09106, 2642.09399, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2835.09106, 2642.09399, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2835.09106, 2642.09399, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2833.67529, 2641.61011, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2833.67529, 2641.61011, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2833.67529, 2641.61011, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2833.67529, 2641.61011, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2835.03589, 2639.29248, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2835.03589, 2639.29248, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2835.03589, 2639.29248, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2835.03589, 2639.29248, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2835.01416, 2637.83032, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2835.01416, 2637.83032, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2835.01416, 2637.83032, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2835.01416, 2637.83032, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2834.23657, 2633.43652, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2834.23657, 2633.43652, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2834.23657, 2633.43652, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2834.23657, 2633.43652, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2834.82813, 2635.35938, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2834.82813, 2635.35938, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2834.82813, 2635.35938, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2834.82813, 2635.35938, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2834.97778, 2630.89111, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2834.97778, 2630.89111, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2834.97778, 2630.89111, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2834.97778, 2630.89111, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2833.66577, 2628.83984, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2833.66577, 2628.83984, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2833.66577, 2628.83984, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2833.66577, 2628.83984, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2835.16821, 2625.55908, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2835.16821, 2625.55908, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2835.16821, 2625.55908, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2835.16821, 2625.55908, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2833.86060, 2623.68799, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2833.86060, 2623.68799, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2833.86060, 2623.68799, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2833.86060, 2623.68799, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2834.44824, 2621.51074, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2834.44824, 2621.51074, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2834.44824, 2621.51074, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2834.44824, 2621.51074, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2833.48975, 2619.68335, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2833.48975, 2619.68335, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2833.48975, 2619.68335, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2833.48975, 2619.68335, 272.26031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(982, -2824.25366, 2630.36523, 272.64194,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2830.70044, 2641.68091, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2826.05054, 2641.08203, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2826.05054, 2641.08203, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2826.05054, 2641.08203, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2826.05054, 2641.08203, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2827.91968, 2635.49048, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2827.91968, 2635.49048, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2827.91968, 2635.49048, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2827.91968, 2635.49048, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2825.75879, 2633.34204, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2825.75879, 2633.34204, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2825.75879, 2633.34204, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2825.75879, 2633.34204, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2828.90479, 2626.03198, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2828.90479, 2626.03198, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2828.90479, 2626.03198, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2828.90479, 2626.03198, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2831.52563, 2628.55518, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2831.52563, 2628.55518, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2831.52563, 2628.55518, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2831.52563, 2628.55518, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2831.11475, 2620.19800, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2831.11475, 2620.19800, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2831.11475, 2620.19800, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1584, -2831.11475, 2620.19800, 272.26215,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2830.70044, 2641.68091, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2830.70044, 2641.68091, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2830.70044, 2641.68091, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2831.79321, 2633.92700, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2831.79321, 2633.92700, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2831.79321, 2633.92700, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2831.79321, 2633.92700, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2829.05615, 2630.75415, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2829.05615, 2630.75415, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2829.05615, 2630.75415, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2829.05615, 2630.75415, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2831.39697, 2624.86694, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2831.39697, 2624.86694, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2831.39697, 2624.86694, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2831.39697, 2624.86694, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2826.41650, 2623.43140, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2826.41650, 2623.43140, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2826.41650, 2623.43140, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2826.41650, 2623.43140, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2830.22339, 2622.44702, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2830.22339, 2622.44702, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2830.22339, 2622.44702, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1583, -2830.22339, 2622.44702, 272.19046,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(10444, -2826.76245, 2623.74194, 278.04028,   0.00000, 0.00000, -179.75978);
	CreateDynamicObject(10444, -2826.11450, 2623.87500, 277.96597,   180.00000, 0.00000, -179.75978);
	CreateDynamicObject(2099, -2847.11719, 2640.24121, 278.17111,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2229, -2847.14673, 2639.76294, 278.17365,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2229, -2847.14526, 2641.58643, 278.17365,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2229, -2847.13379, 2642.00684, 278.17365,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2229, -2847.13281, 2639.36230, 278.17365,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2624, -2821.94458, 2659.95190, 273.87082,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2685, -2855.49463, 2649.01782, 279.47366,   0.00000, 0.00000, 178.19981);
	CreateDynamicObject(2691, -2848.30029, 2609.25928, 275.08942,   0.00000, 0.00000, -89.76002);
	CreateDynamicObject(1255, -2834.63281, 2610.10669, 278.76743,   0.00000, 0.00000, 21.71999);
	CreateDynamicObject(1255, -2835.09741, 2611.86475, 278.76743,   0.00000, 0.00000, 8.93999);
	CreateDynamicObject(1255, -2835.11719, 2615.52271, 278.76743,   0.00000, 0.00000, -7.98001);
	CreateDynamicObject(1255, -2834.59619, 2617.09009, 278.76743,   0.00000, 0.00000, -19.20001);
	CreateDynamicObject(1255, -2822.17529, 2610.47144, 278.76743,   0.00000, 0.00000, 149.09993);
	CreateDynamicObject(1255, -2821.71533, 2613.15698, 278.76743,   0.00000, 0.00000, 178.07994);
	CreateDynamicObject(1597, -2847.29199, 2615.33716, 280.72391,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1597, -2840.92236, 2608.97437, 280.72391,   0.00000, 0.00000, 89.93998);
	CreateDynamicObject(18090, -2845.94946, 2628.05444, 280.67950,   0.00000, 0.00000, 180.05981);
	CreateDynamicObject(19462, -2847.93384, 2627.01904, 279.85193,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19462, -2847.89136, 2636.58960, 279.85193,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2844.32935, 2625.74878, 279.29749,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2844.65112, 2625.98071, 279.29749,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2844.77783, 2626.62988, 279.29749,   0.00000, 0.00000, -0.30000);
	CreateDynamicObject(1486, -2844.53735, 2626.40503, 279.29749,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2844.76709, 2627.66650, 279.29749,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2844.48926, 2627.46851, 279.29749,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2844.96216, 2624.53076, 279.29749,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2846.16748, 2623.84595, 279.29749,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2844.40015, 2625.06836, 279.29749,   0.00000, 0.00000, 0.06000);
	CreateDynamicObject(1486, -2844.70654, 2625.20044, 279.29749,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2844.86450, 2630.53711, 279.29749,   0.00000, 0.00000, -0.12000);
	CreateDynamicObject(1486, -2844.92090, 2628.55347, 279.29749,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2844.58569, 2631.51904, 279.29749,   0.00000, 0.00000, -0.06000);
	CreateDynamicObject(1486, -2844.49829, 2628.13647, 279.29749,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2844.45288, 2626.74316, 279.29749,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2844.55029, 2629.18433, 279.29749,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2844.34766, 2630.37378, 279.29749,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2844.85693, 2629.89185, 279.29749,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2844.94263, 2632.14453, 279.29749,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2847.34253, 2630.81226, 279.93716,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2847.42725, 2630.69507, 280.47687,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2847.47900, 2630.91821, 281.05655,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2847.43481, 2630.51563, 281.05655,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2847.45313, 2631.05688, 280.47687,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1486, -2847.38037, 2630.87354, 280.47687,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1488, -2846.87280, 2626.28149, 280.20868,   0.00000, 0.00000, 86.40005);
	CreateDynamicObject(1488, -2846.86621, 2629.95093, 280.20868,   0.00000, 0.00000, 86.40005);
	CreateDynamicObject(1512, -2847.50391, 2627.18164, 279.96872,   0.00000, 0.00000, -96.36005);
	CreateDynamicObject(1512, -2847.32861, 2628.95801, 279.96872,   0.00000, 0.00000, -124.26004);
	CreateDynamicObject(1512, -2847.39746, 2628.13794, 280.50851,   0.00000, 0.00000, -109.92004);
	CreateDynamicObject(1512, -2847.46240, 2627.73828, 280.50851,   0.00000, 0.00000, -105.48000);
	CreateDynamicObject(1512, -2847.81226, 2626.96167, 281.08841,   0.00000, 0.00000, -105.48000);
	CreateDynamicObject(1512, -2847.20605, 2629.23682, 281.08841,   0.00000, 0.00000, -105.48000);
	CreateDynamicObject(1512, -2847.23145, 2628.79663, 281.08841,   0.00000, 0.00000, -105.48000);
	CreateDynamicObject(1512, -2847.36182, 2627.89722, 281.08841,   0.00000, 0.00000, -105.48000);
	CreateDynamicObject(1520, -2847.31958, 2627.75024, 279.84851,   0.00000, 0.00000, 108.54014);
	CreateDynamicObject(1520, -2847.37964, 2628.55103, 279.84851,   0.00000, 0.00000, 108.54014);
	CreateDynamicObject(1520, -2847.37964, 2628.15063, 279.84851,   0.00000, 0.00000, 108.54014);
	CreateDynamicObject(1520, -2847.43970, 2629.25171, 280.36859,   0.00000, 0.00000, 108.54014);
	CreateDynamicObject(1520, -2847.51978, 2628.91138, 280.36859,   0.00000, 0.00000, 108.54014);
	CreateDynamicObject(1520, -2847.53979, 2628.63110, 280.36859,   0.00000, 0.00000, 108.54014);
	CreateDynamicObject(1512, -2847.36230, 2625.47607, 280.50851,   0.00000, 0.00000, -105.48000);
	CreateDynamicObject(1512, -2847.40234, 2625.25586, 280.50851,   0.00000, 0.00000, -105.48000);
	CreateDynamicObject(1520, -2847.47974, 2625.20776, 279.84851,   0.00000, 0.00000, 108.54014);
	CreateDynamicObject(1512, -2847.40381, 2625.54004, 279.96872,   0.00000, 0.00000, -96.36005);
	CreateDynamicObject(1486, -2847.13892, 2625.95483, 281.05655,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1598, -2827.82397, 2616.05884, 278.04178,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1598, -2830.16943, 2612.89355, 278.04178,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1616, -2847.59204, 2621.35376, 283.79025,   0.00000, 0.00000, 84.60003);
	CreateDynamicObject(1616, -2848.53174, 2622.19995, 283.79025,   0.00000, 0.00000, 13.62000);
	CreateDynamicObject(1616, -2818.72363, 2621.43335, 283.79025,   0.00000, 0.00000, 84.60003);
	CreateDynamicObject(1622, -2848.69360, 2613.46313, 278.22375,   0.00000, 0.00000, -6.05997);
	CreateDynamicObject(1645, -2821.64819, 2618.32642, 278.43109,   0.00000, 0.00000, -82.80002);
	CreateDynamicObject(1645, -2821.59912, 2616.73706, 278.43109,   0.00000, 0.00000, -90.96004);
	CreateDynamicObject(1645, -2821.68237, 2615.27539, 278.43109,   0.00000, 0.00000, -104.94009);
	CreateDynamicObject(1687, -2821.46021, 2668.12720, 284.81488,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1687, -2825.16895, 2668.12134, 284.81488,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1689, -2819.55151, 2663.46509, 284.91937,   0.00000, 0.00000, -90.60004);
	CreateDynamicObject(1689, -2819.59619, 2655.84009, 284.91937,   0.00000, 0.00000, -90.60004);
	CreateDynamicObject(1689, -2827.77954, 2655.94702, 284.91937,   0.00000, 0.00000, -90.60004);
	CreateDynamicObject(1689, -2836.13159, 2655.94434, 284.91937,   0.00000, 0.00000, -90.60004);
	CreateDynamicObject(1689, -2847.05273, 2625.17114, 284.91937,   0.00000, 0.00000, -90.00007);
	CreateDynamicObject(1694, -2832.86499, 2629.34521, 292.68457,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1703, -2819.90576, 2647.92334, 272.26175,   0.00000, 0.00000, -219.53995);
	CreateDynamicObject(1817, -2820.53687, 2650.80176, 272.26337,   0.00000, 0.00000, -89.94000);
	CreateDynamicObject(1703, -2821.51099, 2651.47925, 272.26175,   0.00000, 0.00000, -310.07974);
	CreateDynamicObject(1824, -2836.16748, 2624.80762, 278.66617,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1828, -2836.02026, 2633.18848, 278.14984,   0.00000, 0.00000, -0.30005);
	CreateDynamicObject(1824, -2836.05249, 2630.46704, 278.66617,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1886, -2820.07202, 2667.60986, 283.08725,   0.00000, 0.00000, -25.19998);
	CreateDynamicObject(1897, -2847.66406, 2635.49756, 279.27194,   0.00000, 0.00000, 92.58013);
	CreateDynamicObject(1895, -2847.43237, 2635.50415, 280.35590,   0.00000, 0.00000, 89.82003);
	CreateDynamicObject(1896, -2847.05786, 2635.71924, 279.14059,   0.00000, 0.00000, 90.06001);
	CreateDynamicObject(1978, -2835.96851, 2636.07349, 279.25986,   0.00000, 0.00000, 89.70004);
	CreateDynamicObject(1828, -2835.86816, 2627.66943, 278.14984,   0.00000, 0.00000, -0.30005);
	CreateDynamicObject(2011, -2819.85620, 2637.85498, 278.16388,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2011, -2819.77148, 2622.44531, 278.16339,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2011, -2832.25317, 2623.40015, 278.16281,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2011, -2819.83936, 2668.15771, 278.16281,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2011, -2819.88599, 2664.14233, 278.16281,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2180, -2819.63721, 2666.66138, 278.16290,   0.00000, 0.00000, -90.41998);
	CreateDynamicObject(1839, -2819.79761, 2666.18042, 278.96338,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1840, -2819.81812, 2665.59888, 278.96326,   0.00000, 0.00000, -8.46000);
	CreateDynamicObject(1840, -2819.83569, 2666.76196, 278.96326,   0.00000, 0.00000, 5.63999);
	CreateDynamicObject(19174, -2847.11499, 2646.25537, 281.36142,   0.00000, 0.00000, 89.88012);
	CreateDynamicObject(19172, -2819.33252, 2666.16064, 281.17868,   0.00000, 0.00000, -90.72015);
	CreateDynamicObject(19173, -2857.17896, 2659.07715, 280.72964,   0.00000, 0.00000, 89.64014);
	CreateDynamicObject(18647, -2847.12695, 2646.31592, 282.16119,   0.00000, 0.00000, -0.06000);
	CreateDynamicObject(1775, -2852.15894, 2667.22070, 279.25613,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1775, -2850.29639, 2667.18921, 279.25613,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, -2824.08032, 2662.58691, 274.71976,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, -2834.06152, 2662.59033, 274.71976,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14455, -2839.20435, 2662.94482, 273.85117,   0.00000, 0.00000, 89.88004);
	CreateDynamicObject(18762, -2838.56519, 2663.59082, 274.76065,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2838.56396, 2664.58691, 274.76065,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2838.57617, 2665.57227, 274.76065,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2838.57129, 2666.49390, 274.76065,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2838.52539, 2665.55176, 276.70001,   90.00000, 0.00000, -0.30000);
	CreateDynamicObject(18762, -2838.52539, 2665.55176, 275.76053,   90.00000, 0.00000, -0.30000);
	CreateDynamicObject(18762, -2838.52539, 2665.55176, 274.80429,   90.00000, 0.00000, -0.30000);
	CreateDynamicObject(3383, -2820.12183, 2665.48193, 272.26096,   0.00000, 0.00000, 90.00004);
	CreateDynamicObject(348, -2820.26025, 2664.12817, 273.33517,   94.49973, 19.92000, -177.59991);
	CreateDynamicObject(348, -2820.82544, 2664.27686, 273.31512,   89.93990, 5.76000, 0.00000);
	CreateDynamicObject(358, -2820.47510, 2664.96826, 273.29544,   97.02000, 79.01994, -10.38001);
	CreateDynamicObject(1828, -2829.69946, 2665.47559, 272.24475,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2691, -2838.03296, 2665.39819, 273.30518,   0.00000, 0.00000, 90.30004);
	CreateDynamicObject(1778, -2853.42407, 2649.35083, 272.24799,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1778, -2853.41235, 2649.80176, 272.24799,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1829, -2837.39648, 2663.69995, 272.73856,   0.00000, 0.00000, -269.99960);
	CreateDynamicObject(1852, -2838.21069, 2664.06836, 276.28882,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1852, -2838.21069, 2664.06836, 276.58820,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1852, -2838.21069, 2664.06836, 276.00940,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1852, -2838.21069, 2664.06836, 275.72998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1852, -2838.21069, 2664.06836, 275.43060,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1852, -2838.18848, 2664.35083, 276.00940,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1852, -2838.18848, 2664.68042, 276.28882,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1852, -2838.19702, 2664.99121, 276.58820,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1852, -2838.18872, 2664.68018, 275.72998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1852, -2838.19238, 2665.00879, 275.43060,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1852, -2838.18530, 2666.91968, 276.58820,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1852, -2838.18091, 2666.59839, 276.58813,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1852, -2838.17407, 2666.29688, 276.26999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1852, -2838.18726, 2665.99731, 275.99167,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1852, -2838.17407, 2666.29688, 275.71350,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1852, -2838.18091, 2666.59839, 275.39532,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1852, -2838.18530, 2666.91968, 275.38892,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1518, -2827.37061, 2663.05005, 275.76709,   0.00000, 0.00000, 179.93976);
	CreateDynamicObject(1518, -2827.99243, 2663.05542, 275.76709,   0.00000, 0.00000, 179.93976);
	CreateDynamicObject(1518, -2828.61377, 2663.05811, 275.76709,   0.00000, 0.00000, 179.93976);
	CreateDynamicObject(1518, -2828.61377, 2663.05811, 275.18475,   0.00000, 0.00000, 179.93976);
	CreateDynamicObject(1518, -2827.99243, 2663.05542, 275.17990,   0.00000, 0.00000, 179.93976);
	CreateDynamicObject(1518, -2827.37061, 2663.05005, 275.17560,   0.00000, 0.00000, 179.93976);
	CreateDynamicObject(358, -2819.96924, 2666.22461, 273.29544,   97.02000, 79.01994, -194.70003);
	CreateDynamicObject(18789, -2977.69751, 1739.44434, 14.48612,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(18789, -2977.69995, 1589.57678, 14.48612,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(18791, -2970.20825, 1476.17078, 14.48666,   0.00000, 0.00000, -67.92000);
	CreateDynamicObject(18791, -2916.20288, 1419.72119, 14.48666,   0.00000, 0.00000, -24.59999);
	CreateDynamicObject(18789, -2803.69141, 1403.88281, 14.48612,   0.00000, 0.00000, -185.15997);
	CreateDynamicObject(18789, -2659.15894, 1390.96106, -11.70017,   0.00000, 20.44001, -5.03998);
	CreateDynamicObject(3858, -2826.33032, 2648.84839, 280.19455,   0.00000, 0.00000, -314.92001);
	CreateDynamicObject(18762, -2833.46875, 2648.82983, 280.60989,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3858, -2826.33032, 2648.84839, 280.19455,   0.00000, 0.00000, -314.92001);
	CreateDynamicObject(3858, -2826.33032, 2648.84839, 280.19455,   0.00000, 0.00000, -314.92001);
	CreateDynamicObject(3858, -2826.33032, 2648.84839, 280.19455,   0.00000, 0.00000, -314.92001);
	CreateDynamicObject(3858, -2834.34961, 2660.57959, 280.19455,   0.00000, 0.00000, -225.03996);
	CreateDynamicObject(18762, -2834.37329, 2653.75073, 280.60989,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3858, -2834.34961, 2660.57959, 280.19455,   0.00000, 0.00000, -225.03996);
	CreateDynamicObject(3858, -2834.34961, 2660.57959, 280.19455,   0.00000, 0.00000, -225.03996);
	CreateDynamicObject(3858, -2834.34961, 2660.57959, 280.19455,   0.00000, 0.00000, -225.03996);
	CreateDynamicObject(3858, -2826.33032, 2648.84839, 280.19455,   0.00000, 0.00000, -314.92001);
	CreateDynamicObject(18762, -2844.75244, 2633.21362, 280.60989,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1985, -2820.93091, 2651.03540, 281.02155,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2820.89307, 2651.04150, 283.51053,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18762, -2820.85498, 2656.87158, 283.51053,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1985, -2820.78882, 2656.92822, 281.02155,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14791, -2826.53394, 2665.63159, 280.11038,   0.00000, 0.00000, -89.75997);
	CreateDynamicObject(2627, -2819.39795, 2662.73389, 278.16364,   0.00000, 0.00000, -90.48002);
	CreateDynamicObject(2627, -2819.40771, 2660.13379, 278.16364,   0.00000, 0.00000, -90.48002);
	CreateDynamicObject(2628, -2833.16528, 2655.70093, 278.16125,   0.00000, 0.00000, 89.69996);
	CreateDynamicObject(2630, -2833.30835, 2657.28076, 278.16104,   0.00000, 0.00000, 90.17998);
	CreateDynamicObject(2628, -2833.15161, 2658.74487, 278.16125,   0.00000, 0.00000, 89.69996);
	CreateDynamicObject(2630, -2833.21655, 2660.26221, 278.16104,   0.00000, 0.00000, 90.17998);
	CreateDynamicObject(2632, -2820.59448, 2653.84204, 278.16187,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1598, -2842.98462, 2613.76538, 278.40176,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1598, -2842.93384, 2614.36670, 278.40176,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1598, -2842.88818, 2614.96558, 278.40176,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1598, -2842.93701, 2614.06616, 278.92026,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1598, -2842.77905, 2614.61938, 278.92026,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1598, -2842.93384, 2614.36670, 279.43781,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3383, -2819.23120, 2632.14795, 278.14197,   0.00000, 0.00000, 90.00004);
	CreateDynamicObject(19164, -2819.23535, 2631.85229, 279.25336,   0.00000, 0.00000, -90.24002);
	CreateDynamicObject(3858, -2813.57959, 2643.46777, 278.11301,   44.94003, -89.39989, -90.60002);
	CreateDynamicObject(18770, -2856.46191, 2643.68237, 191.59784,   0.08000, 30.68001, 0.00000);
	CreateDynamicObject(3858, -2813.57959, 2643.46777, 278.11301,   44.94003, -89.39989, -90.60002);
	CreateDynamicObject(3858, -2813.57959, 2643.46777, 278.11301,   44.94003, -89.39989, -90.60002);
	CreateDynamicObject(3858, -2813.57959, 2643.46777, 278.11301,   44.94003, -89.39989, -90.60002);
	CreateDynamicObject(19144, -2833.88672, 2667.75781, 283.03168,   0.00000, 0.00000, -125.82001);
	CreateDynamicObject(19144, -2833.88672, 2667.75781, 282.41324,   0.00000, 0.00000, -125.82001);
	CreateDynamicObject(19144, -2833.88672, 2667.75781, 281.76285,   0.00000, 0.00000, -125.82001);
	CreateDynamicObject(19144, -2833.88672, 2667.75781, 281.11136,   0.00000, 0.00000, -125.82001);
	CreateDynamicObject(19144, -2833.88672, 2667.75781, 280.41165,   0.00000, 0.00000, -125.82001);
	CreateDynamicObject(19144, -2833.88672, 2667.75781, 279.82938,   0.00000, 0.00000, -125.82001);
	CreateDynamicObject(19144, -2833.88672, 2667.75781, 279.26004,   0.00000, 0.00000, -125.82001);
	CreateDynamicObject(18850, -2873.53320, 2551.04541, 261.50085,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18770, -2865.22144, 2560.00562, 151.30058,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18770, -2865.16870, 2542.18140, 151.30058,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18655, -2847.23657, 2622.13086, 279.86255,   0.00000, 0.00000, -170.81956);
	CreateDynamicObject(3038, -2832.37354, 2661.93774, 276.94031,   0.00000, 0.00000, -90.00007);
	CreateDynamicObject(3038, -2824.48071, 2661.90845, 276.94031,   0.00000, 0.00000, -90.00007);
	CreateDynamicObject(2727, -2840.31860, 2637.89941, 274.81277,   90.00000, 180.00000, 90.90001);
	CreateDynamicObject(2697, -2847.24463, 2632.83862, 274.58133,   0.00000, 0.00000, 89.88007);
	CreateDynamicObject(19174, -2847.26807, 2622.26416, 274.63403,   0.00000, 0.00000, 90.54005);
	CreateDynamicObject(19175, -2840.19995, 2624.21802, 274.96683,   0.00000, 0.00000, -89.94003);
	CreateDynamicObject(11665, -2829.28125, 2645.61548, 272.95099,   0.00000, 0.00000, -89.10000);
	CreateDynamicObject(16378, -2850.40894, 2651.13818, 272.95944,   0.00000, 0.00000, -89.40007);
	CreateDynamicObject(2270, -2837.34033, 2661.59814, 274.07599,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2267, -2845.66553, 2667.87598, 274.16608,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2255, -2852.13452, 2667.40479, 273.86411,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1741, -2849.48584, 2666.42285, 272.24716,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1742, -2841.58813, 2667.98657, 272.26364,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2573, -2835.00073, 2644.48926, 272.26126,   0.00000, 0.00000, -179.87990);
	CreateDynamicObject(14813, -2821.35547, 2610.84595, 272.73401,   0.00000, 0.00000, -180.00002);

	//thc
	
		
	AddStaticVehicle(470,-1117.0328,-1616.5775,76.3588,269.5528,128,128); // Pojazd 1
	AddStaticVehicle(541,-1117.0291,-1625.6478,75.9990,269.4156,128,128); // Pojazd 2
	AddStaticVehicle(490,-1117.0884,-1621.3834,76.5023,269.6574,128,128); // Pojazd 3
	AddStaticVehicle(522,-1095.6011,-1627.3599,76.0260,266.3663,128,128); // Pojazd 4
	AddStaticVehicle(522,-1095.6093,-1614.7683,76.0273,270.1221,128,128); // Pojazd 5
	AddStaticVehicle(487,-1109.0895,-1620.9365,86.1136,270.1330,128,128); // Pojazd 6

	CreateDynamicObject(8240, -1011.45331, -1619.89722, 84.44095,   0.00000, 0.00000, 139.19371);
	CreateDynamicObject(3749, -944.01044, -1720.53296, 82.66566,   0.00000, 0.00000, 270.50281);
	CreateDynamicObject(12959, -988.61237, -1617.86279, 75.08562,   0.00000, 0.00000, 320.30316);
	CreateDynamicObject(10631, -1008.97583, -1605.25964, 79.77780,   0.00000, 0.00000, 179.72380);
	CreateDynamicObject(1412, -946.26984, -1637.97961, 80.05447,   3.00629, 0.00000, 281.17264);
	CreateDynamicObject(1447, -969.16144, -1600.61499, 76.98438,   3.03798, 0.00078, 0.00753);
	CreateDynamicObject(1447, -974.18121, -1599.97510, 76.98438,   3.03798, 0.00078, 0.00753);
	CreateDynamicObject(1447, -979.22351, -1600.29724, 76.16021,   3.03798, 0.00078, 201.78789);
	CreateDynamicObject(19486, -1098.88440, -1669.48535, 77.39548,   0.00000, 0.00000, 270.36465);
	CreateDynamicObject(8661, -1098.91016, -1668.05811, 75.37498,   0.00000, 0.00000, 89.42492);
	CreateDynamicObject(709, -990.71356, -1687.51807, 72.79990,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18267, -992.20728, -1693.77600, 92.09307,   0.00000, 0.00000, 355.13138);
	CreateDynamicObject(708, -995.45465, -1710.11755, 70.49087,   3.14159, 0.00000, 54.90347);
	CreateDynamicObject(1893, -992.02380, -1687.57361, 95.43092,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, -992.17035, -1690.69373, 95.43092,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, -992.72241, -1694.36011, 95.43092,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(16782, -987.85474, -1696.27026, 93.58652,   0.00000, 0.00000, 178.36491);
	CreateDynamicObject(2110, -991.83807, -1698.72583, 92.16969,   0.00000, 0.00000, 357.45901);
	CreateDynamicObject(3111, -991.33936, -1698.42542, 93.03253,   0.00000, 0.00000, 354.69482);
	CreateDynamicObject(2110, -991.79889, -1697.98462, 92.16969,   0.00000, 0.00000, 357.45901);
	CreateDynamicObject(3383, -994.83997, -1699.34509, 92.24306,   0.00000, 0.00000, 354.46967);
	CreateDynamicObject(358, -994.25305, -1699.79749, 93.26850,   0.00000, 0.00000, 359.29492);
	CreateDynamicObject(358, -996.14001, -1699.59436, 93.26850,   0.00000, 0.00000, 359.29492);
	CreateDynamicObject(359, -995.01080, -1699.31213, 93.29710,   0.00000, 0.00000, 267.06912);
	CreateDynamicObject(359, -994.73871, -1699.32092, 93.29710,   0.00000, 0.00000, 267.06912);
	CreateDynamicObject(356, -995.67767, -1699.27576, 93.38921,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(356, -993.99670, -1699.49377, 93.38921,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(349, -994.14142, -1699.26807, 93.40862,   0.00000, 0.00000, 2.98948);
	CreateDynamicObject(349, -995.82867, -1699.00452, 93.40862,   0.00000, 0.00000, 2.98948);
	CreateDynamicObject(348, -994.06512, -1699.01355, 93.48495,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(348, -993.54053, -1699.08838, 93.48495,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(348, -995.38501, -1698.79309, 93.48495,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(348, -995.91473, -1698.61084, 93.48495,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(9819, -992.14795, -1685.71777, 93.06683,   0.00000, 0.00000, 85.42474);
	CreateDynamicObject(1595, -1023.98627, -1573.91821, 96.62746,   0.00000, 0.00000, 228.58113);
	CreateDynamicObject(1595, -1032.70825, -1583.57434, 96.62746,   0.00000, 0.00000, 228.58113);
	CreateDynamicObject(1595, -1039.68945, -1591.92236, 96.62746,   0.00000, 0.00000, 228.58113);
	CreateDynamicObject(1595, -1047.26392, -1600.42334, 96.62746,   0.00000, 0.00000, 228.58113);
	CreateDynamicObject(2592, -1098.93311, -1679.70508, 76.11925,   0.00000, 0.00000, 180.54683);
	CreateDynamicObject(1829, -987.48492, -1685.70142, 92.58636,   0.00000, 0.00000, 356.09790);
	CreateDynamicObject(3361, -997.48865, -1679.16077, 88.25890,   0.00000, 0.00000, 84.76546);
	CreateDynamicObject(3361, -987.95990, -1675.62427, 80.53677,   0.00000, 0.00000, 355.71356);
	CreateDynamicObject(3361, -996.25513, -1671.00208, 88.24471,   0.00000, 0.00000, 252.40776);
	CreateDynamicObject(3361, -993.42242, -1675.20081, 84.18497,   0.00000, 0.00000, 356.08698);
	CreateDynamicObject(3361, -982.55383, -1676.01929, 76.71745,   0.00000, 0.00000, 355.71356);
	CreateDynamicObject(3361, -995.23096, -1667.75757, 89.38132,   0.00000, 0.00000, 252.40776);
	CreateDynamicObject(9618, -1000.87982, -1672.06995, 77.92133,   0.00000, 0.00000, 355.20981);
	CreateDynamicObject(9618, -1000.22498, -1664.69958, 77.92133,   0.00000, 0.00000, 355.20981);
	CreateDynamicObject(2985, -984.12469, -1700.91406, 92.16678,   0.00000, 0.00000, 338.86255);
	CreateDynamicObject(2985, -983.47620, -1693.98132, 92.16678,   0.00000, 0.00000, 317.22729);
	CreateDynamicObject(2064, -985.26538, -1701.33630, 92.60098,   0.00000, 0.00000, 64.18065);
	CreateDynamicObject(3580, -989.27649, -1634.82312, 79.44244,   0.00000, 0.00000, 45.28322);
	CreateDynamicObject(3640, -998.81042, -1646.41125, 79.24770,   0.00000, 0.00000, 229.11646);
	CreateDynamicObject(3279, -1062.22559, -1627.76843, 74.75763,   0.00000, 0.00000, 86.80173);
	CreateDynamicObject(2985, -1012.58124, -1672.56030, 90.83037,   0.00000, 0.00000, 281.19260);
	CreateDynamicObject(2985, -1010.13629, -1671.89258, 90.83037,   0.00000, 0.00000, 281.19260);
	CreateDynamicObject(2985, -1060.39771, -1629.35925, 90.82233,   0.00000, 0.00000, 314.74634);
	CreateDynamicObject(2985, -1063.50610, -1629.83948, 90.82233,   0.00000, 0.00000, 314.74634);
	CreateDynamicObject(3279, -1012.03101, -1670.08081, 74.75763,   0.00000, 0.00000, 102.82538);
	CreateDynamicObject(3557, -1026.12231, -1598.49243, 77.90411,   0.00000, 0.00000, 179.38820);
	CreateDynamicObject(3641, -1057.14563, -1675.62573, 78.09596,   0.00000, 0.00000, 88.64110);
	CreateDynamicObject(3939, -1021.42529, -1591.05090, 76.72313,   0.00000, 0.00000, 266.51147);
	CreateDynamicObject(1828, -992.00830, -1692.06836, 92.17067,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1828, -991.56708, -1688.19983, 92.17067,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1828, -992.16669, -1695.86462, 92.17067,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18765, -1052.93445, -1674.28772, 73.72768,   0.00000, 0.00000, 355.70978);
	CreateDynamicObject(18765, -1062.65845, -1673.93933, 73.72768,   0.00000, 0.00000, 355.70978);
	CreateDynamicObject(18765, -1070.76733, -1671.62720, 73.72768,   0.00000, 0.00000, 355.70978);
	CreateDynamicObject(18765, -1071.16809, -1678.41907, 73.72768,   0.00000, 0.00000, 355.70978);
	CreateDynamicObject(18765, -1080.98560, -1677.69312, 73.72768,   0.00000, 0.00000, 355.70978);
	CreateDynamicObject(18765, -1080.63757, -1670.91870, 73.72768,   0.00000, 0.00000, 355.70978);
	CreateDynamicObject(18765, -1083.03955, -1670.72314, 73.72768,   0.00000, 0.00000, 355.70978);
	CreateDynamicObject(18765, -1083.51062, -1677.45923, 73.72768,   0.00000, 0.00000, 355.70978);
	CreateDynamicObject(18766, -1070.43408, -1667.17419, 76.22198,   0.00000, 0.00000, 355.63568);
	CreateDynamicObject(18766, -1080.29138, -1666.42310, 76.22198,   0.00000, 0.00000, 355.63568);
	CreateDynamicObject(18766, -1087.47937, -1670.36646, 76.22198,   0.00000, 0.00000, 85.15143);
	CreateDynamicObject(18766, -1082.62488, -1666.24060, 76.22198,   0.00000, 0.00000, 355.63568);
	CreateDynamicObject(18766, -1087.96851, -1677.12354, 76.22198,   0.00000, 0.00000, 85.15143);
	CreateDynamicObject(18766, -1083.83691, -1682.03394, 76.22198,   0.00000, 0.00000, 354.72266);
	CreateDynamicObject(18766, -1073.96753, -1682.96033, 76.22198,   0.00000, 0.00000, 354.72266);
	CreateDynamicObject(18766, -1070.85913, -1683.25916, 76.22198,   0.00000, 0.00000, 354.72266);
	CreateDynamicObject(2898, -1069.99438, -1680.09656, 76.22243,   0.00000, 0.00000, 356.30331);
	CreateDynamicObject(2898, -1069.63147, -1674.77417, 76.22243,   0.00000, 0.00000, 356.30331);
	CreateDynamicObject(2898, -1069.29089, -1669.55493, 76.22243,   0.00000, 0.00000, 356.30331);
	CreateDynamicObject(2898, -1067.40393, -1669.89941, 76.22243,   0.00000, 0.00000, 356.30331);
	CreateDynamicObject(2898, -1067.08862, -1674.91858, 76.22243,   0.00000, 0.00000, 356.30331);
	CreateDynamicObject(2898, -1067.46863, -1680.27551, 76.22243,   0.00000, 0.00000, 356.30331);
	CreateDynamicObject(3409, -961.69165, -1620.89575, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -964.59070, -1624.36548, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -967.43359, -1627.82849, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -970.31250, -1625.56384, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -967.58380, -1621.98633, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -964.68829, -1618.48877, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -967.67755, -1616.13904, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -970.61694, -1619.62805, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -973.34570, -1623.20557, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -976.23090, -1620.88538, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -973.47931, -1617.37549, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -970.47400, -1613.64917, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -973.70380, -1611.18970, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -976.71362, -1614.81201, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -979.59302, -1618.25293, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -982.67462, -1615.96387, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -979.69531, -1612.36230, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -976.74854, -1608.90491, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -979.06799, -1605.93872, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -982.02075, -1609.44446, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -984.08948, -1611.99768, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -987.03729, -1609.64697, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -984.17816, -1606.14246, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -982.01672, -1603.54053, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -975.96179, -1608.26318, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -984.81610, -1601.04260, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -987.80505, -1604.59070, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -990.89044, -1607.99817, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -992.21075, -1612.89258, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -992.19800, -1603.77417, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -989.31586, -1600.51685, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -987.71643, -1598.55945, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -990.74573, -1595.98083, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -993.20306, -1599.68311, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -993.74091, -1593.51282, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -996.74902, -1590.75110, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -996.67365, -1596.74438, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -999.82654, -1594.18726, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1002.15973, -1597.96436, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1002.86542, -1591.64026, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1005.36029, -1595.37085, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -999.83075, -1588.25305, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1002.81915, -1585.63916, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1005.75989, -1589.20276, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1008.54803, -1592.89575, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1010.92535, -1596.41296, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1011.55890, -1590.36389, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1008.53894, -1586.76062, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1005.65283, -1582.97278, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1008.55359, -1580.74414, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1010.46094, -1579.03589, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1013.09406, -1582.82642, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1011.09406, -1584.49915, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1014.06885, -1587.76746, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1016.26208, -1586.29480, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1016.30774, -1589.09619, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1019.81976, -1589.52356, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1022.00446, -1593.64063, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1015.54547, -1590.19348, 75.42670,   0.00000, 0.00000, 359.65009);
	CreateDynamicObject(3409, -1014.40588, -1590.23657, 75.42670,   0.00000, 0.00000, 359.65009);
	CreateDynamicObject(3409, -1015.37585, -1594.45520, 75.42670,   0.00000, 0.00000, 359.65009);
	CreateDynamicObject(1583, -1074.00708, -1681.54382, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1075.31201, -1680.62317, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1077.86658, -1681.33081, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1079.37476, -1680.18323, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1079.86084, -1681.30737, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1076.46655, -1681.52405, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1075.35474, -1681.65491, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1077.32166, -1680.01294, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1081.72803, -1680.07727, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1083.05212, -1681.07129, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1084.74805, -1680.54175, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1086.25671, -1680.15125, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1084.01660, -1680.05212, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1074.38391, -1680.33813, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1584, -1074.13074, -1677.75891, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1074.48193, -1676.83032, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1074.55444, -1675.66211, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1074.55774, -1674.31641, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1073.77368, -1674.98645, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1076.74280, -1673.12024, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1074.18250, -1672.76318, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1583, -1077.28992, -1678.04871, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1076.04114, -1677.99744, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1076.82080, -1676.36304, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1584, -1076.69946, -1674.71094, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1078.05090, -1675.71582, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1583, -1078.44360, -1677.24548, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1080.20020, -1675.04858, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1584, -1080.54504, -1676.80225, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1079.27759, -1676.32971, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1078.72144, -1674.43164, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1583, -1079.25903, -1672.88623, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1082.79089, -1675.17505, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1081.42029, -1675.34607, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1080.88391, -1673.44470, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1082.81738, -1673.24756, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1082.99695, -1676.64087, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1583, -1084.37659, -1676.26599, 76.22363,   0.00000, 0.00000, 91.66203);
	CreateDynamicObject(1584, -1084.34705, -1674.56787, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1085.57629, -1674.56775, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1086.08398, -1676.13354, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1085.47925, -1673.22839, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1083.87354, -1673.27795, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1075.57202, -1670.39990, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1076.62097, -1668.63672, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1077.97620, -1670.11816, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1078.86938, -1668.14636, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1080.16846, -1669.93335, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1081.60742, -1668.80212, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1081.74060, -1667.38831, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1083.18396, -1669.76575, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1084.24133, -1668.06421, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1085.90955, -1669.48572, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1086.46863, -1667.55969, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(1584, -1073.91370, -1668.89197, 76.22014,   0.00000, 0.00000, 91.69023);
	CreateDynamicObject(983, -1074.64929, -1671.57886, 76.61079,   0.00000, 0.00000, 86.79547);
	CreateDynamicObject(983, -1080.99768, -1671.22070, 76.61079,   0.00000, 0.00000, 86.79547);
	CreateDynamicObject(983, -1084.20129, -1671.05774, 76.61079,   0.00000, 0.00000, 86.79547);
	CreateDynamicObject(983, -1075.17737, -1679.01733, 76.61079,   0.00000, 0.00000, 86.79547);
	CreateDynamicObject(983, -1081.56909, -1678.66553, 76.61079,   0.00000, 0.00000, 86.79547);
	CreateDynamicObject(983, -1084.76929, -1678.48035, 76.61079,   0.00000, 0.00000, 86.79547);
	CreateDynamicObject(10832, -951.12262, -1696.08081, 77.09561,   0.00000, 0.00000, 282.02179);
	CreateDynamicObject(2627, -1091.92383, -1682.08447, 75.36892,   0.00000, 0.00000, 182.46338);
	CreateDynamicObject(2627, -1093.78162, -1682.19531, 75.36892,   0.00000, 0.00000, 182.46338);
	CreateDynamicObject(2627, -1095.73328, -1682.43103, 75.36892,   0.00000, 0.00000, 182.46338);
	CreateDynamicObject(2628, -1101.41028, -1684.32349, 75.36842,   0.00000, 0.00000, 180.86459);
	CreateDynamicObject(2628, -1103.79224, -1684.01282, 75.36842,   0.00000, 0.00000, 180.86459);
	CreateDynamicObject(2628, -1106.50867, -1684.45166, 75.36842,   0.00000, 0.00000, 180.86459);
	CreateDynamicObject(2629, -1092.17334, -1667.29944, 75.37202,   0.00000, 0.00000, 269.73917);
	CreateDynamicObject(2629, -1092.22754, -1673.77808, 75.37202,   0.00000, 0.00000, 269.73917);
	CreateDynamicObject(2913, -1091.70154, -1666.87122, 76.42879,   -9.77998, 90.47997, 273.53235);
	CreateDynamicObject(2913, -1091.72046, -1673.35193, 76.42879,   -9.77998, 90.47997, 273.53235);
	CreateDynamicObject(2630, -1093.01453, -1664.92358, 75.37174,   0.00000, 0.00000, 267.52933);
	CreateDynamicObject(2630, -1093.27136, -1670.64380, 75.37174,   0.00000, 0.00000, 267.52933);
	CreateDynamicObject(2630, -1093.10278, -1676.90662, 75.37174,   0.00000, 0.00000, 267.52933);
	CreateDynamicObject(14791, -1103.71130, -1657.87646, 77.10168,   0.00000, 0.00000, 0.45074);
	CreateDynamicObject(14782, -1094.27222, -1661.74487, 76.42842,   0.00000, 0.00000, 180.66293);
	CreateDynamicObject(14782, -1094.56787, -1654.53650, 76.42842,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2632, -1105.17383, -1676.62524, 75.36986,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2632, -1105.22717, -1678.97644, 75.36986,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2915, -1106.40186, -1678.75354, 75.49092,   0.00000, 0.00000, 272.46970);
	CreateDynamicObject(2915, -1106.34863, -1679.69348, 75.49092,   0.00000, 0.00000, 272.46970);
	CreateDynamicObject(2915, -1106.40417, -1677.21448, 75.49092,   0.00000, 0.00000, 272.46970);
	CreateDynamicObject(2915, -1106.39673, -1676.31421, 75.49092,   0.00000, 0.00000, 272.46970);
	CreateDynamicObject(2916, -1105.56152, -1679.10498, 75.56639,   0.00000, 0.00000, 274.79385);
	CreateDynamicObject(2916, -1105.62207, -1678.52795, 75.56639,   0.00000, 0.00000, 274.79385);
	CreateDynamicObject(2916, -1105.53027, -1676.85742, 75.56639,   0.00000, 0.00000, 274.79385);
	CreateDynamicObject(2916, -1105.52625, -1676.33545, 75.56639,   0.00000, 0.00000, 274.79385);
	CreateDynamicObject(1985, -1103.62280, -1664.63892, 78.03841,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1985, -1103.56018, -1667.37842, 77.91394,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1985, -1103.38599, -1670.37903, 77.91394,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3503, -1103.56677, -1664.23132, 78.11714,   -89.58005, 14.58002, 14.67157);
	CreateDynamicObject(3503, -1103.48950, -1666.84473, 78.11714,   -89.58005, 14.58002, 14.67157);
	CreateDynamicObject(3503, -1104.62561, -1670.72400, 78.11714,   -89.58005, 14.58002, 105.92623);
	CreateDynamicObject(3503, -1103.37146, -1669.42371, 78.11714,   -89.58005, 14.58002, 14.67157);
	CreateDynamicObject(3503, -1105.81116, -1670.74988, 78.11714,   -89.58005, 14.58002, 105.92623);
	CreateDynamicObject(3409, -1008.55359, -1580.74414, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1010.46094, -1579.03589, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1013.09406, -1582.82642, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1011.09406, -1584.49915, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1016.26208, -1586.29480, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1014.06885, -1587.76746, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1019.81976, -1589.52356, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1022.00446, -1593.64063, 75.42670,   0.00000, 0.00000, 322.94601);
	CreateDynamicObject(3409, -1015.54547, -1590.19348, 75.42670,   0.00000, 0.00000, 359.65009);
	CreateDynamicObject(14467, -1024.30688, -1631.01550, 77.64423,   0.00000, 0.00000, 134.06493);
	CreateDynamicObject(14467, -1023.56061, -1632.73047, 77.64423,   0.00000, 0.00000, 35.61744);
	CreateDynamicObject(14467, -1025.14929, -1633.47205, 77.64423,   0.00000, 0.00000, 293.32642);
	CreateDynamicObject(14467, -1025.83887, -1631.84814, 77.64423,   0.00000, 0.00000, 217.88791);
	CreateDynamicObject(16480, -973.28979, -1733.98438, 78.85103,   0.00000, 0.00000, 103.44469);
	CreateDynamicObject(3521, -992.95941, -1619.92480, 81.29685,   0.00000, 0.00000, 319.39908);
	CreateDynamicObject(3521, -989.36664, -1622.69141, 81.29685,   0.00000, 0.00000, 319.39908);
	CreateDynamicObject(2790, -1008.60614, -1615.47644, 82.35584,   0.00000, 0.00000, 1.38481);
	CreateDynamicObject(3515, -1024.56152, -1632.24768, 74.41803,   0.00000, 0.00000, 356.78708);
	CreateDynamicObject(983, -1024.50867, -1630.41284, 75.58149,   0.00000, 0.00000, 87.50215);
	CreateDynamicObject(983, -1026.03442, -1633.13562, 75.58149,   0.00000, 0.00000, 25.03427);
	CreateDynamicObject(983, -1023.10516, -1633.23889, 75.58149,   0.00000, 0.00000, 150.81352);
	CreateDynamicObject(11497, -1036.73572, -1608.75940, 75.35104,   0.00000, 0.00000, 287.46201);
	CreateDynamicObject(16146, -1036.16125, -1696.36816, 79.75047,   0.00000, 0.00000, 215.42468);
	CreateDynamicObject(16778, -1035.19421, -1690.10828, 80.74396,   0.00000, 0.00000, 209.20807);
	CreateDynamicObject(3092, -983.50006, -1699.84460, 91.64962,   0.00000, 0.00000, 261.44995);
	CreateDynamicObject(3092, -981.44006, -1696.32788, 90.20692,   0.00000, 0.00000, 159.17825);
	CreateDynamicObject(3092, -982.59637, -1696.29907, 90.20692,   0.00000, 0.00000, 159.17825);
	CreateDynamicObject(3092, -983.32104, -1696.26282, 91.64962,   0.00000, 0.00000, 261.44995);
	CreateDynamicObject(3092, -983.37329, -1697.30774, 91.64962,   0.00000, 0.00000, 261.44995);
	CreateDynamicObject(3092, -983.43103, -1698.46301, 91.64962,   0.00000, 0.00000, 261.44995);
	CreateDynamicObject(3642, -1007.69562, -1658.78308, 77.77647,   0.00000, 0.00000, 48.27474);
	CreateDynamicObject(3646, -1047.42371, -1619.60266, 77.21400,   0.00000, 0.00000, 106.08820);
*/
}

stock GangStringValidate(str[])
{
	
	for(new i, p = strlen(str);i<p;i++)
	{
		switch(str[i])
		{
			case 'a' .. 'z': continue;
			case 'A' .. 'Z': continue;
			case '0' .. '9': continue;
			case ' ', '.', '-', '[', ']': continue;
		//	case '!': continue;
			default: return 1;
 		}
	}
	return 0;
}

stock GangRemoveValidateString(str[])
{
	for(new i, p = strlen(str);i<p;i++)
	{
		switch(str[i])
		{
			case 'a' .. 'z': continue;
			case 'A' .. 'Z': continue;
			case '0' .. '9': continue;
		//	case '!': continue;
			default: str[i] = '-';
 		}
	}
}


LoadGangs_Spar()
{
	new czas = GetTickCount();
	 
	mysql_query("SELECT * FROM "prefix"_gangs_spar limit "#MAX_SPAR_ARENS"");
	mysql_store_result();
	new data[64], id;
	add_SparCount=0;
	for(new i;i<mysql_num_rows();i++)
	{
		mysql_data_seek(i);//
		mysql_fetch_row_data();
		
		mysql_fetch_field("aad_Interior", data);	
		add_Spar[id][add_interior] = strval(data);
		
		mysql_fetch_field("add_name", add_Spar[id][add_name]);	
	
		mysql_fetch_field("aad_Spawn1", data);	
		if(sscanf(data, "p<,>a<f>[3]", add_Spar[id][aad_spawn1])) printf("b³¹d rodzielania areny WG ");
		
		mysql_fetch_field("aad_Spawn2", data);	
		if(sscanf(data, "p<,>a<f>[3]", add_Spar[id][aad_spawn2])) printf("b³¹d rodzielania areny WG ");
		
		mysql_fetch_field("add_Zone", data);	
		if(sscanf(data, "p<,>a<f>[4]", add_Spar[id][aad_zone])) printf("b³¹d rodzielania areny WG ");
		
		if(add_Spar[id][add_interior] == 0)
		{
			add_Spar[id][add_zone] = GangZoneCreate(add_Spar[id][aad_zone][0], add_Spar[id][aad_zone][1], add_Spar[id][aad_zone][2], add_Spar[id][aad_zone][3]);
			add_Spar[id][add_stream] = CreateDynamicRectangle(add_Spar[id][aad_zone][0], add_Spar[id][aad_zone][1], add_Spar[id][aad_zone][2], add_Spar[id][aad_zone][3]);	

 			
		//	printf("%f, %f, %f, %f", add_Spar[id][aad_zone][0], add_Spar[id][aad_zone][1], add_Spar[id][aad_zone][2], add_Spar[id][aad_zone][3]);
		}
		 
		id++;
		add_SparCount++;
		 
	}
	
 
	printf("[load] wczytanych aren sparowych:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	mysql_free_result();

}  

stock Gang_RefleshOnline(cgang, cgangid)
{
	if(cgang)
	{
		//gInfo[gang][gangTextdraw]
		m_query("SELECT isonline, nick FROM mreg_players where gang=%d order by isonline desc;", cgangid);
		mysql_store_result();
		new data[26], online, mnr, count;
		new tdstr[2048];
		if((mnr=mysql_num_rows(),mnr))
		{
			while(mysql_fetch_row(data))
			{
				if(count++ > 10) break;
				online = ((data[0] << 6) >>> 6) - '0';
				
				if( online )
				{
					online = findPlayer(data[0x02]);
					if(online == INVALID_PLAYER_ID)
						format(tdstr, sizeof(tdstr), "%s~w~%d. ~r~~h~%s~n~", tdstr, count, data[0x02]);
					else 
						format(tdstr, sizeof(tdstr), "%s~w~%d. ~g~~h~%s - %d~n~", tdstr, count, data[0x02], online);
				}
				else 
				{
					format(tdstr, sizeof(tdstr), "%s~w~%d. ~r~~h~%s~n~", tdstr, count, data[ 0x02 ]);
				}
				 
			}
		//Online: ~n~~g~~h~Lady.M~n~~g~~h~pnkz~n~~r~~h~UFO~n~~h~~r~~h~tdw.lyszka~n~~r~~h~1234567890abcdefghij
			if( (count = (mnr - count), count ) > 0 )
				format(tdstr, sizeof(tdstr), "%s i jeszcze ~g~%d~w~...", tdstr, count);
				
	//		printf("settd %d str; %s", gInfo[ cgang ][gangTextdraw], tdstr);
			TextDrawSetString2(gInfo[ cgang ][gangTextdraw], tdstr);
			foreach(new p : Player)
			{
				if(!IsTextDrawShowForPlayer(p, gInfo[ cgang ][gangTextdraw])) continue;
				if(pInfo[p][player_gang] == cgang) 
				{
					TextDrawShowForPlayer(p, gInfo[ cgang ][gangTextdraw]);
				}
			}
		}
	}
}

forward Gang_CallRefleshOnline(xgang, xgangid);
public Gang_CallRefleshOnline(xgang, xgangid)
{
	Gang_RefleshOnline(xgang, xgangid);
}
stock Gang_OnPlayerLogin(playerid)
{
	SetTimerEx("Gang_CallRefleshOnline", 1000, 0, "dd", pInfo[playerid][player_gang], pInfo[playerid][player_gangID]);
	Gang_RefleshOnline(pInfo[playerid][player_gang], pInfo[playerid][player_gangID]);
	return 1;
}
stock Gang_OnPlayerDisconnect(playerid)
{
	SetTimerEx("Gang_CallRefleshOnline", 1000, 0, "dd", pInfo[playerid][player_gang], pInfo[playerid][player_gangID]);

	Gang_RefleshOnline(pInfo[playerid][player_gang], pInfo[playerid][player_gangID]);
	return 1;
}
