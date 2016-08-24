#define MAX_MARIHUANA		2000

enum EnumSkun
{
	skun_id,
	skun_owner,
	Float:skun_percentage,
	Float:skun_x,
	Float:skun_y,
	Float:skun_z,
	object,
	Text3D:mlabel
};
new Skun[MAX_MARIHUANA][EnumSkun];

new SkunTimer[MAX_PLAYERS];
new HighestID;

stock marihuana_init()
{
	LoadMarihuana();
	UpdateMarihuana();
	SetTimer("UpdateMarihuana", 60000,1);
	SetTimer("MMsg",60000*15, 1);
	Create3DTextLabel("/kupnasiona",0x33ff33FF,2104.4724,-1555.4324,13.5195,22.0,0,0);
	Create3DTextLabel("/kupnasiona",0x33ff33FF,1682.9410,1748.1598,10.9437,22.0,0,0);
	Create3DTextLabel("/kupnasiona",0x33ff33FF,-1818.7274,-159.6931,9.6112,22.0,0,0);
	return 1;
}

stock marihuana_exit()
{
	SaveMarihuana();
	return 1;
}

CMD:kupnasiona(playerid, params[])
{
	if(IsPlayerInRangeOfPoint(playerid,5.0,2104.4724,-1555.4324,13.5195)  || IsPlayerInRangeOfPoint(playerid,5.0,1682.9410,1748.1598,10.9437)  || IsPlayerInRangeOfPoint(playerid,5.0,-1818.7274,-159.6931,9.6112))
	{
		Dialog_Show(playerid, DIALOG_KUPNASIONA, DIALOG_STYLE_INPUT,"Wpisz iloœæ nasion","{FFFFFF}Wpisz iloœæ nasion do kupienia: ","Kup","Anuluj");		
	} else return SendClientMessage(playerid,COLOR_ERROR,"Teleportuj siê do jednego z seedshopów aby zakupiæ nasiona marihuany. (/seedshopls, /seedshoplv, /seedshopsf)");
	return 1;
}

Dialog:DIALOG_KUPNASIONA(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(!IsNumeric(inputtext))return SendClientMessage(playerid,COLOR_ERROR,"Wpisa³eœ(aœ) b³edn¹ iloœæ nasion.");
		new ilosc = strval(inputtext);
		new scor = GetPlayerScore(playerid);
		if(Iter_Contains(Vips, playerid)) {
			if(scor < 250*ilosc )return SendClientMessage(playerid,COLOR_ERROR,"Masz za ma³o EXP ¿eby kupiæ tyle nasion.");
		}
		else if(scor < 450*ilosc )
		{ 
			return SendClientMessage(playerid,COLOR_ERROR,"Masz za ma³o EXP ¿eby kupiæ tyle nasion. Potrzebujesz 450XP na jedno nasionko(Vip 250XP)");
		}	
		pInfo[playerid][player_nasionka] += 1*ilosc;
		if(Iter_Contains(Vips, playerid)) { GivePlayerScore(playerid,-250*ilosc); }
		else { GivePlayerScore(playerid,-450*ilosc); }
		SendClientMessage(playerid,0x66ff1aFF,"Kupi³eœ w³aœnie nasionka marihuany. Wpisz /sadz aby posadziæ je w miejscu w którym stoisz."); 
	}

	return 1;
}
CMD:zbierz(playerid,params[])
{
	new bool: skunobjt ;
	for(new x=0; x<=HighestID; x++)
	{
		if(IsPlayerInRangeOfPoint(playerid,2.0,Skun[x][skun_x], Skun[x][skun_y], Skun[x][skun_z]))
		{
			if(Skun[x][skun_percentage] >= 100.0)
			{
				skunobjt = true;
				SendClientMessage(playerid,0x66ff1aFF,"Zebra³eœ zio³o za co dostajesz 600 XP! Mo¿esz je teraz tak¿e spaliæ u¿ywaj¹c komendy /skun. ");
				GivePlayerScore(playerid,600);
				pInfo[playerid][player_marihuana]+=1;
				pInfo[playerid][zebranych_krzakow]++;
				DestroyMarihuana(x);
				break;
				
			} else skunobjt = false;
		}
		
	}
	if(!skunobjt)
	{
		SendClientMessage(playerid,-1,"Nie jesteœ w pobli¿u ¿adnego zio³a");
	}
	return 1;
}

CMD:sadz(playerid,params[])
{
	if(pInfo[playerid][player_nasionka] < 1)return SendClientMessage(playerid,COLOR_ERROR,"Nie posiadasz ¿adnych nasion. /ziolohelp");
	if(IsPlayerInAnyVehicle(playerid))return SendClientMessage(playerid,COLOR_ERROR,"Nie mo¿esz u¿ywaæ tej komendy w pojeŸdzie.");
//	if(GetPlayerInterior(playerid) != 0)return SendClientMessage(playerid,COLOR_ERROR,"Nie mo¿esz sadziæ zio³a w budynkach");
	
	new CrtStr[356];
	format(CrtStr,356,"SELECT ID FROM "prefix"_bushes WHERE `owner` = '%d'",pInfo[playerid][player_id]);
	m_query(CrtStr);
	mysql_store_result();
	if(mysql_num_rows() >= 7 && !Iter_Contains(Vips, playerid))return SendClientMessage(playerid,COLOR_ERROR,"Posiadasz ju¿ 7 krzaków. (VIP mo¿e sadziæ 12 krzaków)");
	else if(mysql_num_rows() >= 12 && Iter_Contains(Vips, playerid))return SendClientMessage(playerid,COLOR_ERROR,"Posiadasz ju¿ 12 krzaów.");
	mysql_free_result();
	
	new Float:pos[3];
	GetPlayerPos(playerid,pos[0], pos[1], pos[2]);
	
	CreateMarihuana(pInfo[playerid][player_id], pos[0], pos[1], pos[2]);
	pInfo[playerid][player_nasionka] -= 1;
	pInfo[playerid][posadzonych_krzakow]++;

	SendClientMessage(playerid,0x66ff1aFF,""chat"Zasadzi³eœ krzak zio³a. Czas w jakim bêdzie gotowy do zebrania to od kilkunastu minut do kilku godzin. Nie zapomnij o nim bo ktoœ mo¿e ci go zebraæ gdy bêdzie ju¿ dojrza³y");
	
	return 1;
}

CMD:sadz5(playerid,params[])
{
	if(pInfo[playerid][player_nasionka] < 1)return SendClientMessage(playerid,COLOR_ERROR,"Nie posiadasz ¿adnych nasion. /ziolohelp");
	if(IsPlayerInAnyVehicle(playerid))return SendClientMessage(playerid,COLOR_ERROR,"Nie mo¿esz u¿ywaæ tej komendy w pojeŸdzie.");
//	if(GetPlayerInterior(playerid) != 0)return SendClientMessage(playerid,COLOR_ERROR,"Nie mo¿esz sadziæ zio³a w budynkach");
	
	new CrtStr[356];
	format(CrtStr,356,"SELECT ID FROM "prefix"_bushes WHERE `owner` = '%d'",pInfo[playerid][player_id]);
	m_query(CrtStr);
	mysql_store_result();
	if(mysql_num_rows()+5 >= 7 && !Iter_Contains(Vips, playerid))return SendClientMessage(playerid,COLOR_ERROR,"Posiadasz ju¿ 7 krzaków. (VIP mo¿e sadziæ 12 krzaków)");
	else if(mysql_num_rows()+5 >= 12 && Iter_Contains(Vips, playerid))return SendClientMessage(playerid,COLOR_ERROR,"Posiadasz ju¿ 12 krzaów.");
	mysql_free_result();
	
	new Float:pos[3];
	GetPlayerPos(playerid,pos[0], pos[1], pos[2]);
	
	CreateMarihuana(pInfo[playerid][player_id], pos[0], pos[1], pos[2]);
	CreateMarihuana(pInfo[playerid][player_id], pos[0]+0.3, pos[1]+0.3, pos[2]);
	CreateMarihuana(pInfo[playerid][player_id], pos[0]-0.3, pos[1]-0.3, pos[2]);
	CreateMarihuana(pInfo[playerid][player_id], pos[0]+0.6, pos[1]+0.6, pos[2]);
	CreateMarihuana(pInfo[playerid][player_id], pos[0]-0.6, pos[1]-0.6, pos[2]);
	pInfo[playerid][player_nasionka] -= 5;
	pInfo[playerid][posadzonych_krzakow]+=5;

	SendClientMessage(playerid,0x66ff1aFF,""chat"Zasadzi³eœ 5 krzaków zio³a. Czas w jakim bêd¹ gotowe do zebrania to oko³o 30 minut. Nie zapomnij o nich bo ktoœ mo¿e ci je zebraæ gdy bêdzie ju¿ dojrza³y.");
	
	return 1;
}

CMD:ziolo(playerid,params[])
{
	new diid[2048], iddd[50], lal;
	for(new x = 0; x < sizeof(Skun); x++)
	{
		if(Skun[x][skun_owner] == pInfo[playerid][player_id])
		{
			lal++;
			if(lal < 7)
			{
				format(iddd,50,"ID: %d ",Skun[x][skun_id]);
			}
			else if(lal == 7)
			{
				lal = 0;
				format(iddd,50,"ID: %d\n",Skun[x][skun_id]);
			}
			strcat(diid,iddd); 
		}
	}
	Dialog_Show(playerid, DIALOG_ZIOLO, DIALOG_STYLE_MSGBOX, "Twoje krzaki",diid,"OK","");
	return 1;
}



CMD:skun(playerid,params[])
{
	if(pInfo[playerid][player_marihuana] < 1)return SendClientMessage(playerid,COLOR_ERROR,""chat"Nie posiadasz ¿adnego zio³a");
	
	pInfo[playerid][player_marihuana] --;
	SetPlayerWeather(playerid,-68);
	SetPlayerTime(playerid,22,0);
	SetPlayerDrunkLevel(playerid,50000);
	SetTimerEx("SkunNormal",60000,0,"d",playerid);
	SendClientMessage(playerid,0x66ff1aFF,"Spali³eœ zio³o. ");
	pInfo[playerid][spalonego_skuna]++;
	return 1;
}

CMD:ziolohelp(playerid, params[])
{
	new zstr[1028];
	strcat(zstr, "{66ff1a}Je¿eli chcesz zasadziæ krzak zio³a musisz najpierw udaæ siê do pobliskiego seedshopu.\nSeedshopy znajdziesz pod teleportami (/seedshopls) (/seedshoplv) (/seedshopsf)\nAby kupiæ jedno nasionko zio³a musisz wpisaæ komendê /kupnasiona w odpowiednim miejscu przy seedshopie.\n\n");
	strcat(zstr,"{66ff1a}Jedno nasionko zio³a kosztuje 450 XP. Je¿eli posiadasz rangê VIP kosztuje ono 250 XP.\n\nGdy ju¿ zakupisz nasionko w jednym z trzech seedshopów nadszed³ czas by je zasadziæ. \nAby to zrobiæ wpisz komendê /sadz lub /sadz5 aby posadziæ 5 krzaków na raz. \nUwa¿nie wybierz miejsce w którym zasadzisz swój krzak.\n");
	strcat(zstr, "Gdy twój krzak osi¹gnie status 100% bêdzie on gotowy do zebrania za co dostaje siê 600 XP. \nAle uwa¿aj! Ka¿dy inny gracz mo¿e zebraæ twój krzak zio³a tak¿e b¹dŸ pewien by go pilnowaæ i zebraæ gdy tylko osi¹gnie 100%.\n\nZebranie krzaku zio³a da ci 1 punkt marihuany (/stats -> na samym dole)\n");
	strcat(zstr, "Marihuanê mo¿esz paliæ u¿ywaj¹c komendy /skun\n\n");
	ShowPlayerDialog(playerid, 9412, DIALOG_STYLE_MSGBOX,"Zio³o help",zstr,"OK","");
	return 1;
}
	
forward SkunNormal(playerid);
public SkunNormal(playerid)
{
	SetPlayerDrunkLevel(playerid,0);
	SetPlayerWeather(playerid,1);
	return 1;
}
	
stock CreateMarihuana(owner, Float:sx, Float:sy, Float:sz)
{
	new skunid = HighestID+1;
	HighestID += 1;
	Skun[skunid][skun_owner] = owner;
	Skun[skunid][skun_percentage] = 0.0;
	Skun[skunid][skun_x] = sx;
	Skun[skunid][skun_y] = sy;
	Skun[skunid][skun_z] = sz-1.3;
	
	Skun[skunid][object] = CreateDynamicObject(19473,Skun[skunid][skun_x], Skun[skunid][skun_y], Skun[skunid][skun_z],0,0,0);
	Skun[skunid][mlabel] = Create3DTextLabel("Zio³o status: 0%\nPoczekaj a¿ uroœnie!\n",0x33ff33FF,sx, sy, sz,100.0,0,0);
	
	new CrtStr[356];
	format(CrtStr,356,"INSERT INTO `4fun_samp`.`mreg_bushes` (`ID`, `owner`, `percentage`, `positionX`, `positionY`, `positionZ`) VALUES (NULL, '%d', '%0.2f', '%0.2f', '%0.2f', '%0.2f')",Skun[skunid][skun_owner],Skun[skunid][skun_percentage],Skun[skunid][skun_x],Skun[skunid][skun_y],Skun[skunid][skun_z]);

	mysql_query(CrtStr);
	
	Skun[skunid][skun_id] = mysql_insert_id();
	printf("CREATEMARIHUANA: id: %s, owner: %d",Skun[skunid][skun_id],owner);
	return 1;
}


forward UpdateMarihuana();
public UpdateMarihuana()
{
	new skunstr[170];
	for(new x; x<=HighestID; x++)
	{
		
		new value = random(6);
		switch(value)
		{
			case 0: {
				Skun[x][skun_percentage] += 0.3;
			}
			case 1: {
				Skun[x][skun_percentage] += 1.3;
			}
			case 2: {
				Skun[x][skun_percentage] += 0.7;
			}
			case 3: {
				Skun[x][skun_percentage] += 5.3;
			}
			case 4: {
				Skun[x][skun_percentage] += 3.3;
			}
			case 5: {	
				Skun[x][skun_percentage] += 6.5;		
			}
			case 6: {	
				Skun[x][skun_percentage] += 0.9;			
			}
		}
		if(Skun[x][skun_percentage] >= 100.0)
		{
			Skun[x][skun_percentage] = 100.0;
			format(skunstr,170,"Zio³o status: Gotowe do zebrania\nWpisz /zbierz by zebraæ\n\nID: %d",Skun[x][skun_id]); 
		} else {
			format(skunstr,170,"Zio³o status: %0.2f/100\nPoczekaj a¿ uroœnie!\n\nID: %d",Skun[x][skun_percentage],Skun[x][skun_id]); 
		}
		if(Skun[x][skun_id] > 1) {
			Update3DTextLabelText(Skun[x][mlabel],0x33ff33FF, skunstr);
		}
	}
	SaveMarihuana();
	return 1;
}

stock DestroyMarihuana(id)
{
	new str[256];
	format(str,256,"DELETE FROM `mreg_bushes` WHERE `ID`='%d'",Skun[id][skun_id]);
	m_query(str);
	DestroyDynamicObject(Skun[id][object]);
	Delete3DTextLabel(Skun[id][mlabel]);
	Skun[id][skun_id] = -1;
	Skun[id][skun_owner] = -1;
	Skun[id][skun_percentage] = -1;
	Skun[id][skun_x] = -1;
	Skun[id][skun_y] = -1;
	Skun[id][skun_z] = -1;
	return printf("Zniszczony krzak marihuany: %d",id);
}
	
stock LoadMarihuana()
{
	new count = GetTickCount();
	
	new Query[256];
	m_query("SELECT ID, owner, percentage, positionX, positionY, positionZ FROM "prefix"_bushes");
	mysql_store_result();
	printf("num_rows: %d",mysql_num_rows());
	for(new i=1 ;i<mysql_num_rows();i++)
	{
		mysql_fetch_row(Query, "|");
		sscanf(Query, "p<|>ddffff", Skun[i][skun_id],Skun[i][skun_owner], Skun[i][skun_percentage], Skun[i][skun_x], Skun[i][skun_y], Skun[i][skun_z]);
		new skunstr[170];
		if(Skun[i][skun_percentage] > 1.0) {
			format(skunstr,170,"Zio³o status: %0.2f/100\nPoczekaj a¿ uroœnie!",Skun[i][skun_percentage]); 
			if(Skun[i][skun_percentage] >= 100.0)
			{
				Skun[i][skun_percentage] = 100.0;
				format(skunstr,170,"Zio³o status: Gotowe do zebrania\nWpisz /zbierz by zebraæ\n\nID: %d",Skun[i][skun_id]); 
			}
		} else {
			format(skunstr,170,"Zio³o status: 0%\nPoczekaj a¿ uroœnie!\n"); 
		}
		Skun[i][object] = CreateDynamicObject(19473,Skun[i][skun_x], Skun[i][skun_y], Skun[i][skun_z],0,0,0);
		Skun[i][mlabel] = Create3DTextLabel(skunstr,0x33ff33FF,Skun[i][skun_x], Skun[i][skun_y], Skun[i][skun_z],100.0,0,0);
		HighestID += 1;
	}
	
	printf("[load] wczytanie drzewek marihuany:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-count);
	mysql_free_result();
	return 1;
}
	
stock SaveMarihuana()
{
	new saveStr[256];
	for(new x; x<HighestID; x++)
	{
		if(Skun[x][skun_id]!= -1) {
			format(saveStr,sizeof(saveStr),"Update "prefix"_bushes SET percentage='%f' where ID='%d' ",Skun[x][skun_percentage], Skun[x][skun_id]);
			mysql_query(saveStr);	
		}
	}
	
	return 1;
}
