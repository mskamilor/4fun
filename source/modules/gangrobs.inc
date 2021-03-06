/*

	Rabunki gang�w
	2016
	(c) Msk.

*/

#define 	MAX_ROBERS		15	//Maksymalna liczba os�b uczestnicz�cych


enum GangRobenum
{
	bool:CanRob,
	bool:Active,
	Robers,
	Hacker,
	Muscle,
	Heli,
	Car1,
	Medic,
	Car3,
	Truck,
	MainCar,
	GangID,
	Win,
	PlayersInCp,
	Hakowanie,
	HackStr[190],
	HackLength,
	bool:Ladowanie
}
new Rob[GangRobenum];

new Text3D:hlabel;
new Text3D:Llabel;
new Text3D:Mlabel;
new Text3D:Tlabel;

new LoadTimer;
new rEndTimer;

enum pGangRob
{
	bool:playing,
	Healed,
	Died,
	Role // 1 - soldier, 2- hacker, 3 - muscle
}
new pRob[MAX_PLAYERS][pGangRob];

CMD:hackuj(playerid,params[])
{
	if(!Rob[Active])return SendClientMessage(playerid,COLOR_ERROR,"Aktualnie nie trwa �aden napad.");
	if(pRob[playerid][Role] != 2)return SendClientMessage(playerid,COLOR_ERROR,"Nie jeste� hackerem.");
	if(!IsPlayerInRangeOfPoint(playerid,3.0,1104.2842,-1334.5215,13.7878))return SendClientMessage(playerid,COLOR_ERROR,"Nie jeste� przy panelu do hackowania.");
	
	format(Rob[HackStr], sizeof(Rob[HackStr]),"");
	
	new LetterList[26][] =
	{
		"A", "z", "C", "f", "E", "F", "p", "H", "L", "y", "K", "i", "s", "b", "O", "P", "Q", "h", "S", "T", "U", "V", "W", "X", "Y", "Z"
	};
	for(new x = 0; x < Rob[HackLength]; x++)
	{
		format(Rob[HackStr],190,"%s%s%d",Rob[HackStr], LetterList[random(sizeof(LetterList))], random(9)+1);	
	}
	printf("HackStr: %s",Rob[HackStr]);
	new dstr[256];
	format(dstr,256,"{FFFFFF}Wprowad� poni�ej podany kod by otworzy� drzwi i rozpocz�� �adowanie!\nJe�eli przepiszesz kod w b��dny spos�b napad zostanie przerwany!\n\nKOD:\n %s",Rob[HackStr]);
	Dialog_Show(playerid,DIALOG_HACK,DIALOG_STYLE_INPUT,"Hackowanie",dstr,"WPISZ","");
	
	new gStr[256];
	format(gStr,256,"{3399ff}"chat" UWAGA!! Gang {FFFFFF}%s {3399ff}rozpoczyna hackowanie w napadzie. Zabicie jednego z nick da ci 350 XP.",gInfo[Rob[GangID]][gangNazwa]);
	SendClientMessageToAll(-1,gStr);
	SendClientMessageToAll(COLOR_ERROR,"{3399ff}"chat" Gracze bior�cy udzia� w napadzie posiadaj� czarne nicki.");
	
	
	return 1;
}

CMD:laduj(playerid,params[])
{
	if(!Rob[Active])return SendClientMessage(playerid,COLOR_ERROR,"Aktualnie nie trwa �aden napad.");
	if(!pRob[playerid][playing]) return SendClientMessage(playerid,COLOR_ERROR,"Nie bierzesz udzia�u w napadzie.");
	if(Rob[Hakowanie] != 1)return SendClientMessage(playerid,COLOR_ERROR,"Hacker nie z�ama� jeszcze zabezpiecze� drzwi.");
	if(!IsPlayerInVehicle(playerid,Rob[MainCar])) return SendClientMessage(playerid,COLOR_ERROR,"Nie jeste� w transporterze.");
	if(GetPlayerVehicleSeat(playerid) != 0)return SendClientMessage(playerid,COLOR_ERROR,"Nie jeste� kierowc�.");
	if(!IsPlayerInRangeOfPoint(playerid,4.0,1097.6219,-1331.5980,13.1564))return SendClientMessage(playerid,COLOR_ERROR,"Jeste� za daleko punktu /laduj.");
	if(Rob[Ladowanie]) return SendClientMessage(playerid,COLOR_ERROR,"�adowanie ju� trwa.");
	
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
	{
		if(pRob[i][playing])
		{
			SendClientMessage(i,COLOR_ERROR,"�adowanie rozpocz�o si�! Chro� ci�ar�wk�!");
		}
	}
	Rob[Ladowanie] = true;
	LoadTimer = SetTimer("LoadedRob",60000,0);
	return 1;
}

forward LoadedRob();
public LoadedRob()
{
	// vehicle pos
	
	
	
	
	new Float:xyz = GetVehicleDistanceFromPoint(Rob[MainCar],1097.6219,-1331.5980,13.1564);
	if(xyz > 6.0)
	{
		for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
		{
			if(pRob[i][playing])
			{
				SendClientMessage(i , COLOR_ERROR, "Ci�ar�wka zosta�a przemieszczona i �adowanie musi zosta� rozpocz�te od nowa!");
				Rob[Ladowanie] = false;
			}
		}
		return 1;
	}
	new rstr[256];
	format(rstr,256,"{3399ff}Gang {FFFFFF}%s {3399ff}sko�czy� �adowanie do ci�ar�wki. Zabij jednego z nich by zyska� 350 XP. Gracze posiadaj� czarne nicki i znajduj� si� w okolicach Vinewood.",gInfo[Rob[GangID]][gangNazwa]);
	SendClientMessageToAll(-1,rstr);
	Rob[Hakowanie] = 2;
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
	{
		if(pRob[i][playing])
		{
			SetPlayerCheckpoint(i,1112.0923,-307.3483,73.9922,5.0);
		}
	}
	return 1;
}

Dialog:DIALOG_HACK(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(!strcmp(inputtext, Rob[HackStr], true))
        {
			if(strlen(inputtext) < Rob[HackLength])return Kick(playerid);
			new rstr[256];
			format(rstr,256,"{3399ff}Gang {FFFFFF}%s {3399ff}sko�czy� hackowa� drzwi i za chwil� rozpocznie �adowanie do ci�ar�wki. Zabij ich by zyska� XP.",gInfo[Rob[GangID]][gangNazwa]);
			SendClientMessageToAll(-1,rstr);
			Rob[Hakowanie] = 1;
			for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
			{
				if(pRob[i][playing])
				{
					SendClientMessage(i,COLOR_ERROR,"Hakowanie udane! Teraz trzeba podjecha� ci�ar�wk� w miejsce �adowania i wpisa� /laduj");
				}
			}
			
		} else {
			GangRobEnd(3);
		}
	}
	
	return 1;
}
CMD:zapisz(playerid,params[])
{
	if(!Rob[Active])return SendClientMessage(playerid,COLOR_ERROR,"Aktualnie nie trwa �aden napad.");
	if(pInfo[playerid][player_gang] != Rob[GangID])return SendClientMessage(playerid,COLOR_ERROR,"Nie jeste� cz�onkiem gangu rabuj�cego.");
	if(pRob[playerid][Died])return SendClientMessage(playerid,COLOR_ERROR,"Nie mo�esz si� zapisa� do tego napadu poniewa� ju� zgin��e�.");
	
	pRob[playerid][playing] = true;
	pRob[playerid][Healed] = 0;
	pRob[playerid][Died] = 0;
	pRob[playerid][Role] = 0;
	SetPlayerPos(playerid,2774.4275,-2531.7104,13.6383);
	SetPlayerInterior(playerid,0);
	ResetPlayerWeapons(playerid);
	SetPlayerColor(playerid,0x000000FF);
	if(Rob[Hacker] == 0) { SendClientMessage(playerid,0x99ccffFF,""chat" Hacker nie zosta� jeszcze wybrany. Wpisz /hacker �eby nim zosta� "); }
	if(Rob[Muscle] == 0) { SendClientMessage(playerid,0x99ccffFF,""chat" Do�wiadczony �o�nierz nie zosta� jeszcze wybrany. Wpisz /muscle �eby nim zosta�"); }
	SendClientMessage(playerid,0x99ccffFF,""chat" Wpisz /soldier �eby zosta� �o�nierzem i bra� udzia� w napadzie");
	return 1;
}
CMD:hacker(playerid,params[])
{
	new id = playerid;
	if(pRob[id][playing] == false)return SendClientMessage(playerid,COLOR_ERROR,"Nie jeste� zapisany na �aden napad.");
	if(pRob[id][Role] != 0)return SendClientMessage(playerid,COLOR_ERROR,"Ju� masz wybrana rol� w tym napadzie.");
	if(Rob[Hacker] >= 1) {
		SendClientMessage(playerid,COLOR_ERROR,"Hacker ju� zosta� wybrany. Wybierz inn� funkcj� w napadzie: ");
		if(Rob[Muscle] == 0) { SendClientMessage(playerid,0x99ccffFF,""chat" Do�wiadczony �o�nierz nie zosta� jeszcze wybrany. Wpisz /muscle �eby nim zosta�"); }
		SendClientMessage(playerid,0x99ccffFF,""chat" Wpisz /soldier �eby zosta� �o�nierzem i bra� udzia� w napadzie");
	}	
	
	Rob[Hacker] = 1;
	Rob[Robers] ++;
	pRob[id][Role] = 2;
	SetUpRobPlayer(playerid);
	new Hstr[128];
	format(Hstr,128,""chat" Gracz %s wybra� funkcj� hackera w napadzie!",playerNick(playerid));
	SendClientMessage(playerid,0x99ccffFF,""chat" Twoim zadaniem b�dzie zhakowanie drzwi komend� /hackuj");
	for(new x =0; x < MAX_PLAYERS; x++)
	{
		if(pInfo[x][player_gang] == Rob[GangID])
		{	
			SendClientMessage(x,COLOR_ERROR,Hstr);
		}
	}
	return 1;
}
CMD:muscle(playerid,params[])
{
	new id =playerid;
	if(pRob[id][playing] == false)return SendClientMessage(playerid,COLOR_ERROR,"Nie jeste� zapisany na �aden napad.");
	if(pRob[id][Role] != 0)return SendClientMessage(playerid,COLOR_ERROR,"Ju� masz wybrana rol� w tym napadzie.");
	if(Rob[Muscle] >= 1) {
		SendClientMessage(playerid,COLOR_ERROR,"Doswiadczony �o�nierz ju� zosta� wybrany. Wybierz inn� funkcj� w napadzie: ");
		if(Rob[Hacker] == 0) { SendClientMessage(playerid,0x99ccffFF,""chat" Hacker nie zosta� jeszcze wybrany. Wpisz /hacker �eby nim zosta� "); }
		SendClientMessage(playerid,0x99ccffFF,""chat" Wpisz /soldier �eby zosta� �o�nierzem i bra� udzia� w napadzie");
		return 1;
	}	
	
	Rob[Muscle] = 1;
	Rob[Robers] ++;
	pRob[id][Role] = 3;
	SetUpRobPlayer(playerid);
	new Hstr[128];
	format(Hstr,128,""chat" Gracz %s wybra� funkcj� do�wiadczonego �o�nierza w napadzie!",playerNick(playerid));
	for(new x =0; x < MAX_PLAYERS; x++)
	{
		if(pInfo[x][player_gang] == Rob[GangID])
		{	
			SendClientMessage(x,COLOR_ERROR,Hstr);
		}
		
	}
	return 1;
}
CMD:soldier(playerid,params[])
{
	new id = playerid;
	if(pRob[id][playing] == false)return SendClientMessage(playerid,COLOR_ERROR,"Nie jeste� zapisany na �aden napad.");
	if(pRob[id][Role] != 0)return SendClientMessage(playerid,COLOR_ERROR,"Ju� masz wybrana rol� w tym napadzie.");

	
	Rob[Muscle] = pInfo[playerid][player_id];
	Rob[Robers] ++;
	pRob[id][Role] = 1;
	SetUpRobPlayer(playerid);
	new Hstr[128];
	format(Hstr,128,""chat" Gracz %s wybra� funkcj� �o�nierza w napadzie!",playerNick(playerid));
	for(new x =0; x < MAX_PLAYERS; x++)
	{
		if(pInfo[x][player_gang] == Rob[GangID])
		{	
			SendClientMessage(x,COLOR_ERROR,Hstr);
		}
	}
	return 1;
}

stock SetUpRobPlayer(playerid)
{
	new id = playerid;
	switch(pRob[id][Role])
	{
		case 1: { //Soldier
			SetPlayerSkin(playerid,124);
			SetPlayerHealth(playerid,100.0);
			SetPlayerArmour(playerid,100.0);
			GivePlayerWeapon(playerid,24,600);
			GivePlayerWeapon(playerid,31,1300);
			GivePlayerWeapon(playerid,26,1300);
			GivePlayerWeapon(playerid,34,300);
		}
		case 2: { //Hacker
			SetPlayerSkin(playerid,289);
			SetPlayerHealth(playerid,100.0);
			SetPlayerArmour(playerid,100.0);
			GivePlayerWeapon(playerid,24,350);
			GivePlayerWeapon(playerid,26,100);
			GivePlayerWeapon(playerid,31,350);
		}
		case 3: { //Muscle
			SetPlayerSkin(playerid,149);
			SetPlayerHealth(playerid,150.0);
			SetPlayerArmour(playerid,250.0);
			SendClientMessage(playerid,COLOR_ERROR,"Posiadasz teraz 150 HP oraz 250 Armor.");
			GivePlayerWeapon(playerid,16,15);
			GivePlayerWeapon(playerid,24,350);
			GivePlayerWeapon(playerid,26,350);
			GivePlayerWeapon(playerid,31,650);
			GivePlayerWeapon(playerid,35,5);
		}
	}
	
	return 1;
}
stock GangRobStart()
{
	for(new x = 0; x < MAX_PLAYERS; x++)
	{
		if(pInfo[x][player_gang] == Rob[GangID])
		{
			SendClientMessage(x, COLOR_ERROR,"=================================================================");
			SendClientMessage(x, COLOR_ERROR,"-> Tw�j gang rozpoczyna napad.. Zapisz si� poprzez komend� /zapisz");
			SendClientMessage(x, COLOR_ERROR,"-----> Nie ma mo�liwo�ci wypisania si� z napadu a� do samego ko�ca!");
			SendClientMessage(x, COLOR_ERROR,"=================================================================");
		}
	}
	Rob[CanRob] = false;
	Rob[Active] = true;
	Rob[Hacker] = 0;
	Rob[Muscle] = 0;
	Rob[PlayersInCp] = 0;
	Rob[Hakowanie] = 0;
	
	rEndTimer = SetTimerEx("GangRobEnd",60000*20,0,"d",7);
	
	Rob[Car1] = CreateVehicle(402, 2785.0012, -2559.6243, 13.3152, 0.0000, 0, 0, -1);
	Rob[Medic] = CreateVehicle(416, 2790.0437, -2559.6875, 13.3152, 0.0000, 0, 0, -1);
	Rob[Car3] = CreateVehicle(560, 2794.9766, -2560.0029, 13.2190, 0.0000, 0, 0, -1);
	Rob[Truck] = CreateVehicle(578, 2799.8069, -2557.4717, 14.1779, 0.0000, 0, 0, -1);
	Rob[MainCar] = CreateVehicle(428, 2791.4958, -2545.2898, 13.6558, 90, 0, 0, -1);
	Rob[Heli] = CreateVehicle(487, 2777.0842, -2550.3550, 13.8560, 0.0000, 0, 0, -1);
	
	hlabel = Create3DTextLabel("/hackuj",0x00FF00FF,1104.2842,-1334.5215,13.7878,20.0,0,0);
	Llabel = Create3DTextLabel("/laduj",0x00FF00FF,1097.6219,-1331.5980,13.1564,20.0,0,0);
	Mlabel = Create3DTextLabel("/ulecz",0x00FF00FF,2790.0437, -2559.6875, 13.3152,20.0,0,0);
	Tlabel = Create3DTextLabel("--> Transporter <--",0x00FF00FF,2790.0437, -2559.6875, 13.3152,20.0,0,0);
	Attach3DTextLabelToVehicle(Mlabel,Rob[Medic],0,0,0);
	Attach3DTextLabelToVehicle(Tlabel,Rob[MainCar],0,0,0);
	
	return 1;
}

stock GangRobEnd(reason)
{
	new fstr[256];
	switch(reason)
	{
		case 1: { // All dead
			format(fstr,256,"{3399ff}Napad gangu {FFFFFF}%s{3399ff} zosta� zako�czony poniewa� wszyscy zgineli!",gInfo[Rob[GangID]][gangNazwa]);
			SendClientMessageToAll(-1,fstr);
		}
		case 2: { //they did it
			format(fstr,256,"{3399ff}Napad gangu {FFFFFF}%s{3399ff} zosta� zako�czony sukcesem! Ka�dy z �yj�cych cz�onk�w dostaje po %d XP",gInfo[Rob[GangID]][gangNazwa], Rob[Win]);
			SendClientMessageToAll(-1,fstr);	
			for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
			{
				if(pRob[i][playing])
				{
					GivePlayerScore(i, Rob[Win]);
				}
			}
		}
		case 3: { // zly kod w hackowaniu
			format(fstr,256,"{3399ff}Napad gangu {FFFFFF}%s{3399ff} zosta� zako�czony poniewa� ich hacker nie z�ama� zabezpiecze�!",gInfo[Rob[GangID]][gangNazwa]);
			SendClientMessageToAll(-1,fstr);
		}
			
		case 4: { // Admin przerwa�
			format(fstr,256,"{3399ff}Napad gangu {FFFFFF}%s{3399ff} zosta� zako�czony przez Vice/Head Administratora",gInfo[Rob[GangID]][gangNazwa]);
			SendClientMessageToAll(-1,fstr);	
		}
		case 5: {
			format(fstr,256,"{3399ff}Napad gangu {FFFFFF}%s{3399ff} zosta� zako�czony poniewa� ich hacker zosta� zabity!",gInfo[Rob[GangID]][gangNazwa]);
			SendClientMessageToAll(-1,fstr);
		}
		case 6: { // wszyscy wyszli z serwera
			format(fstr,256,"{3399ff}Napad gangu {FFFFFF}%s{3399ff} zosta� zako�czony poniewa� wszyscy cz�onkowie wyszli z serwera!",gInfo[Rob[GangID]][gangNazwa]);
			SendClientMessageToAll(-1,fstr);
		}
		case 7: { // czas minal
			format(fstr,256,"{3399ff}Napad gangu {FFFFFF}%s{3399ff} zosta� zako�czony poniewa� czas min�� (20 minut)!",gInfo[Rob[GangID]][gangNazwa]);
			SendClientMessageToAll(-1,fstr);	
		}
	}
	Rob[CanRob] = false;
	Rob[Active] = false;
	Rob[Ladowanie] = false;
	KillTimer(LoadTimer);
	Rob[Robers] = 0;
	Rob[Hacker] = -1;
	Rob[Muscle] = -1;
	Rob[HackLength] = 0;
	Rob[GangID] = -1;
	Rob[PlayersInCp] = -1;
	Rob[Hakowanie] = -1;
	
	KillTimer(rEndTimer);
	
	for(new a = 0; a < MAX_PLAYERS; a++)
	{
		if(pRob[a][playing]) { 
			OnPlayerSpawn(a);
		}
		pRob[a][playing] = false;
		pRob[a][Died] = -1;
		pRob[a][Role] = -1;
		pRob[a][Healed] = -1;			
	}
	SetTimer("CanRobr",1000,0);
	
	DestroyVehicle(Rob[Car1]);
	DestroyVehicle(Rob[Medic]);
	DestroyVehicle(Rob[Car3]);
	DestroyVehicle(Rob[Truck]);
	DestroyVehicle(Rob[MainCar]);
	DestroyVehicle(Rob[Heli]);
	Delete3DTextLabel(hlabel);
	Delete3DTextLabel(Mlabel);
	Delete3DTextLabel(Llabel);
	Delete3DTextLabel(Tlabel);
	return 1;
}

forward CanRobr();
public CanRobr()
{
	Rob[CanRob] = true;
	return 1;
}

CMD:napady(playerid,params[])
{
	new nstr[3000];
	strcat(nstr,"{FFFFFF}Regulamin napad�w:\n\n \
	Klasa Do�wiadczony �o�nierz\n\
	{FF0000}- U�ywanie RPG jest dozwolone tylko i wy��cznie w celu obrony pojazdu do transportu lub gracza z klas� Haker.\n\
	- U�ywanie RPG jest dozwolone w pobli�u miejsca gdzie haker wype�nia swoje zadanie oraz podczas jazdy transporterem. \n\
	- Zezwala si� strzelania do graczy, kt�rzy pr�buj� przeszkodzi� w napadzie oraz pojazd�w, kt�rymi ci gracze si� poruszaj�\n\n\
	- Przy znalezieniu jakiegokolwiek buga zwi�zanego z systemem napad�w gracz zobowi�zany jest do zg�oszenia go na forum serwera\n \
		w innym wypadku mo�e on zosta� zbanowany za bug using.\n\n \
	- Pomaganie swojemu gangowi (Zalicza si� do tego r�wnie� osoba, kt�ra specjalnie wypisze si� z gangu na czas napadu) bez zapisania si�\n \
		do napadu poprzez komend� /zapisz b�dzie karane banem na 3 godziny.\n\n\n\
	{FFFFFF}Co i jak?\n\n\
	Je�eli jeste� liderem gangu i zebra�e� swoich ludzi oraz om�wi�e� z nimi plan napadu to wpisz /gnapad.\n \
	Nast�pnie wszyscy ch�tni cz�onkowie gangu musz� wpisa� /zapisz by bra� udzia� w napadzie.\n\n \
	W napadzie dost�pne s� 3 role:\n\
		- Haker: Haker jest g��wn� osob� bez, kt�rej napad nie ma szans powodzenia. \n To on hackuje drzwi dzi�ki czemu mo�na rozpocz�� �adowanie do transportera. \n\
		- Do�wiadczony �o�nierz: Osoba, kt�ra posiada 250 Armor i 150 HP do tego 5 strza��w RPG oraz granaty. \n Jego celem jest likwidowanie pojazd�w graczy podczas ewentualnego po�cigu oraz ochrona hakera.\n\
		- �o�nierz: Jest to ca�a reszta graczy bior�cych udzia� w napadzie, kt�rzy wspomagaj� ca�y napad swoimi umiej�tno�ciami.\n\n\
	Po wybraniu swojej roli korzystacie z cz�onkami swojego gangu z danych wam pojazd�w. \nNajpierw trzeba dojecha� transporterem w wyznaczone miejsce na mapie.\n\
	W tym miejscu haker rozpoczyna hakowanie drzwi i gdy mu si� powiedzie \nnalezy podjecha� transporterem w miejsce, w kt�rym widnieje napis /laduj.\
	\n\n\
	W tym momencie kierowca transportera wpisuje komende /laduj\n i w tej chwili nale�y broni� transportera przez minut�. \n\
	Po minucie gdy transporter nie zosta� przemieszczony z miejsca \n�adunku wszystkim graczom bior�cym udzia� w napadzie uka�e si� checkpoint na mapie.\n\
	Teraz celem wszystkich cz�onk�w napadu jest chroni� transporter oraz\n jego kierowc� i dowie�d� transporter w wyznaczone miejsce.\n\
	Je�eli zadanie powiedzie si� wszyscy �yj�cy cz�onkowie napadu zostan� nagrodzeni XP.\n\n\n\
	Dodatkowe informacje\n\n\
	Dost�pny jest r�wnie� pojazd(karetka) w kt�rym ka�dy \ncz�onek napadu mo�e uleczy� si� 2 razy(!)\n\
	Dlatego dobr� my�l� b�dzie zabranie karetki ze sob� do\n miejsca gdzie nast�puje hakowanie oraz za�adunek transportera.\n\n\
	W momencie gdy haker umiera napad zostaje przerwany.");
	Dialog_Show(playerid,DIALOG_NAPADYY,DIALOG_STYLE_MSGBOX,"Regulamin, FAQ",nstr,"OK","");
	return 1;
}

CMD:przerwijnapad(playerid,params[])
{
	RankAdmin(playerid, R_JADMIN);
	
	GangRobEnd(4);
	return 1;
}

CMD:ulecz(playerid,params[])
{
	new id = playerid;
	if(!Rob[Active])return SendClientMessage(playerid,COLOR_ERROR,"Aktualnie nie trwa �aden napad.");
	if(!pRob[id][playing]) return SendClientMessage(playerid,COLOR_ERROR,"Nie bierzesz udzia�u w napadzie.");
	if(pRob[id][Healed] >=2)return SendClientMessage(playerid,COLOR_ERROR,"Ju� uleczy�e� si� 2 razy!");
	if(!IsPlayerInVehicle(playerid,Rob[Medic]))return SendClientMessage(playerid,COLOR_ERROR,"Musisz by� w karetce!");
	
	pRob[id][Healed]++;
	switch(pRob[id][Role])
	{
		case 1,2 : {
			SetPlayerArmour(playerid,100.0);
			SetPlayerHealth(playerid,100.0);
		}
		case 3: {
			SetPlayerArmour(playerid,250.0);
			SetPlayerHealth(playerid,150.0);
		}
	}
	SendClientMessage(playerid,COLOR_ERROR,"Uleczy�e� si�! Pami�taj, �e mo�esz uleczy� si� maksymalnie 2 razy!");
	
	return 1;
}


CMD:gnapad(playerid,params[])
{
	if(pInfo[playerid][player_gangrank] < gRank_szef)return SendClientMessage(playerid,COLOR_ERROR,"Nie jeste� liderem �adnego gangu.");
	if(!Rob[CanRob])return SendClientMessage(playerid,COLOR_ERROR,"Napad gangowy mo�na przeprowadza� co 15 minut. Jeszcze nie mo�na przeprowadzi� napadu.");
	new czh, czm;
	gettime(czh, czm);
	
	if(!(czh > 6 && czh < 23)) 
		return SendClientMessage(playerid, COLOR_ERROR, "� Dost�p do uzywanie komendy dostepny w godzinach {b}od 6 do 23{/b}.");
	
	
	new Countt, MinPlayers, Query[256];
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
    {
		if(IsPlayerConnected(i))
		{
			Countt ++;
			pRob[i][Died] = 0;
			pRob[i][playing] = false;
			pRob[i][Healed] = 0;
			pRob[i][Role] = 0;
		}
	}
	m_query("SELECT MinPlayers,Win,Hacklength FROM "prefix"_gangrob WHERE ID=0 LIMIT 1");
	mysql_store_result();
	if(mysql_num_rows())
	{
		mysql_fetch_row(Query, "|");
		sscanf(Query, "p<|>ddd", MinPlayers, Rob[Win], Rob[HackLength]);
	} else {
		SendClientMessage(playerid,-1,"B��D KRYTYCZNY. ZG�O� TO NA FORUM SERWERA.");
		return 0;
	}
	
	if(Countt < MinPlayers)return SendClientMessage(playerid,COLOR_ERROR,"Na serwerze znajduje si� za ma�o graczy.");
	
	Rob[GangID] = pInfo[playerid][player_gang];
	Rob[CanRob] = false;
	GangRobStart();
	return 1;
}

stock GangRobInit()
{
	Rob[CanRob] = true;
	Rob[Active] = false;
	return 1;
}

stock GangRobExit()
{
	return 1;
}
