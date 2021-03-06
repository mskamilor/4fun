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
		Dialog_Show(playerid, DIALOG_KUPNASIONA, DIALOG_STYLE_INPUT,"Wpisz ilo�� nasion","{FFFFFF}Wpisz ilo�� nasion do kupienia: ","Kup","Anuluj");		
	} else return SendClientMessage(playerid,COLOR_ERROR,"Teleportuj si� do jednego z seedshop�w aby zakupi� nasiona marihuany. (/seedshopls, /seedshoplv, /seedshopsf)");
	return 1;
}

Dialog:DIALOG_KUPNASIONA(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(!IsNumeric(inputtext))return SendClientMessage(playerid,COLOR_ERROR,"Wpisa�e�(a�) b�edn� ilo�� nasion.");
		new ilosc = strval(inputtext);
		new scor = GetPlayerScore(playerid);
		if(Iter_Contains(Vips, playerid)) {
			if(scor < 250*ilosc )return SendClientMessage(playerid,COLOR_ERROR,"Masz za ma�o EXP �eby kupi� tyle nasion.");
		}
		else if(scor < 450*ilosc )
		{ 
			return SendClientMessage(playerid,COLOR_ERROR,"Masz za ma�o EXP �eby kupi� tyle nasion. Potrzebujesz 450XP na jedno nasionko(Vip 250XP)");
		}	
		pInfo[playerid][player_nasionka] += 1*ilosc;
		if(Iter_Contains(Vips, playerid)) { GivePlayerScore(playerid,-250*ilosc); }
		else { GivePlayerScore(playerid,-450*ilosc); }
		SendClientMessage(playerid,0x66ff1aFF,"Kupi�e� w�a�nie nasionka marihuany. Wpisz /sadz aby posadzi� je w miejscu w kt�rym stoisz."); 
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
				SendClientMessage(playerid,0x66ff1aFF,"Zebra�e� zio�o za co dostajesz 600 XP! Mo�esz je teraz tak�e spali� u�ywaj�c komendy /skun. ");
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
		SendClientMessage(playerid,-1,"Nie jeste� w pobli�u �adnego zio�a");
	}
	return 1;
}

CMD:sadz(playerid,params[])
{
	if(pInfo[playerid][player_nasionka] < 1)return SendClientMessage(playerid,COLOR_ERROR,"Nie posiadasz �adnych nasion. /ziolohelp");
	if(IsPlayerInAnyVehicle(playerid))return SendClientMessage(playerid,COLOR_ERROR,"Nie mo�esz u�ywa� tej komendy w poje�dzie.");
//	if(GetPlayerInterior(playerid) != 0)return SendClientMessage(playerid,COLOR_ERROR,"Nie mo�esz sadzi� zio�a w budynkach");
	
	new CrtStr[356];
	format(CrtStr,356,"SELECT ID FROM "prefix"_bushes WHERE `owner` = '%d'",pInfo[playerid][player_id]);
	m_query(CrtStr);
	mysql_store_result();
	if(mysql_num_rows() >= 7 && !Iter_Contains(Vips, playerid))return SendClientMessage(playerid,COLOR_ERROR,"Posiadasz ju� 7 krzak�w. (VIP mo�e sadzi� 12 krzak�w)");
	else if(mysql_num_rows() >= 12 && Iter_Contains(Vips, playerid))return SendClientMessage(playerid,COLOR_ERROR,"Posiadasz ju� 12 krza�w.");
	mysql_free_result();
	
	new Float:pos[3];
	GetPlayerPos(playerid,pos[0], pos[1], pos[2]);
	
	CreateMarihuana(pInfo[playerid][player_id], pos[0], pos[1], pos[2]);
	pInfo[playerid][player_nasionka] -= 1;
	pInfo[playerid][posadzonych_krzakow]++;

	SendClientMessage(playerid,0x66ff1aFF,""chat"Zasadzi�e� krzak zio�a. Czas w jakim b�dzie gotowy do zebrania to od kilkunastu minut do kilku godzin. Nie zapomnij o nim bo kto� mo�e ci go zebra� gdy b�dzie ju� dojrza�y");
	
	return 1;
}

CMD:sadz5(playerid,params[])
{
	if(pInfo[playerid][player_nasionka] < 1)return SendClientMessage(playerid,COLOR_ERROR,"Nie posiadasz �adnych nasion. /ziolohelp");
	if(IsPlayerInAnyVehicle(playerid))return SendClientMessage(playerid,COLOR_ERROR,"Nie mo�esz u�ywa� tej komendy w poje�dzie.");
//	if(GetPlayerInterior(playerid) != 0)return SendClientMessage(playerid,COLOR_ERROR,"Nie mo�esz sadzi� zio�a w budynkach");
	
	new CrtStr[356];
	format(CrtStr,356,"SELECT ID FROM "prefix"_bushes WHERE `owner` = '%d'",pInfo[playerid][player_id]);
	m_query(CrtStr);
	mysql_store_result();
	if(mysql_num_rows()+5 >= 7 && !Iter_Contains(Vips, playerid))return SendClientMessage(playerid,COLOR_ERROR,"Posiadasz ju� 7 krzak�w. (VIP mo�e sadzi� 12 krzak�w)");
	else if(mysql_num_rows()+5 >= 12 && Iter_Contains(Vips, playerid))return SendClientMessage(playerid,COLOR_ERROR,"Posiadasz ju� 12 krza�w.");
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

	SendClientMessage(playerid,0x66ff1aFF,""chat"Zasadzi�e� 5 krzak�w zio�a. Czas w jakim b�d� gotowe do zebrania to oko�o 30 minut. Nie zapomnij o nich bo kto� mo�e ci je zebra� gdy b�dzie ju� dojrza�y.");
	
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
	if(pInfo[playerid][player_marihuana] < 1)return SendClientMessage(playerid,COLOR_ERROR,""chat"Nie posiadasz �adnego zio�a");
	
	pInfo[playerid][player_marihuana] --;
	SetPlayerWeather(playerid,-68);
	SetPlayerTime(playerid,22,0);
	SetPlayerDrunkLevel(playerid,50000);
	SetTimerEx("SkunNormal",60000,0,"d",playerid);
	SendClientMessage(playerid,0x66ff1aFF,"Spali�e� zio�o. ");
	pInfo[playerid][spalonego_skuna]++;
	return 1;
}

CMD:ziolohelp(playerid, params[])
{
	new zstr[1028];
	strcat(zstr, "{66ff1a}Je�eli chcesz zasadzi� krzak zio�a musisz najpierw uda� si� do pobliskiego seedshopu.\nSeedshopy znajdziesz pod teleportami (/seedshopls) (/seedshoplv) (/seedshopsf)\nAby kupi� jedno nasionko zio�a musisz wpisa� komend� /kupnasiona w odpowiednim miejscu przy seedshopie.\n\n");
	strcat(zstr,"{66ff1a}Jedno nasionko zio�a kosztuje 450 XP. Je�eli posiadasz rang� VIP kosztuje ono 250 XP.\n\nGdy ju� zakupisz nasionko w jednym z trzech seedshop�w nadszed� czas by je zasadzi�. \nAby to zrobi� wpisz komend� /sadz lub /sadz5 aby posadzi� 5 krzak�w na raz. \nUwa�nie wybierz miejsce w kt�rym zasadzisz sw�j krzak.\n");
	strcat(zstr, "Gdy tw�j krzak osi�gnie status 100% b�dzie on gotowy do zebrania za co dostaje si� 600 XP. \nAle uwa�aj! Ka�dy inny gracz mo�e zebra� tw�j krzak zio�a tak�e b�d� pewien by go pilnowa� i zebra� gdy tylko osi�gnie 100%.\n\nZebranie krzaku zio�a da ci 1 punkt marihuany (/stats -> na samym dole)\n");
	strcat(zstr, "Marihuan� mo�esz pali� u�ywaj�c komendy /skun\n\n");
	ShowPlayerDialog(playerid, 9412, DIALOG_STYLE_MSGBOX,"Zio�o help",zstr,"OK","");
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
	Skun[skunid][mlabel] = Create3DTextLabel("Zio�o status: 0%\nPoczekaj a� uro�nie!\n",0x33ff33FF,sx, sy, sz,100.0,0,0);
	
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
			format(skunstr,170,"Zio�o status: Gotowe do zebrania\nWpisz /zbierz by zebra�\n\nID: %d",Skun[x][skun_id]); 
		} else {
			format(skunstr,170,"Zio�o status: %0.2f/100\nPoczekaj a� uro�nie!\n\nID: %d",Skun[x][skun_percentage],Skun[x][skun_id]); 
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
			format(skunstr,170,"Zio�o status: %0.2f/100\nPoczekaj a� uro�nie!",Skun[i][skun_percentage]); 
			if(Skun[i][skun_percentage] >= 100.0)
			{
				Skun[i][skun_percentage] = 100.0;
				format(skunstr,170,"Zio�o status: Gotowe do zebrania\nWpisz /zbierz by zebra�\n\nID: %d",Skun[i][skun_id]); 
			}
		} else {
			format(skunstr,170,"Zio�o status: 0%\nPoczekaj a� uro�nie!\n"); 
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
