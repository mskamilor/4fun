/*

	Rabunki gangów
	2016
	(c) Msk.

*/

#define 	MAX_ROBERS		15	//Maksymalna liczba osób uczestnicz¹cych


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
	if(!Rob[Active])return SendClientMessage(playerid,COLOR_ERROR,"Aktualnie nie trwa ¿aden napad.");
	if(pRob[playerid][Role] != 2)return SendClientMessage(playerid,COLOR_ERROR,"Nie jesteœ hackerem.");
	if(!IsPlayerInRangeOfPoint(playerid,3.0,1104.2842,-1334.5215,13.7878))return SendClientMessage(playerid,COLOR_ERROR,"Nie jesteœ przy panelu do hackowania.");
	
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
	format(dstr,256,"{FFFFFF}WprowadŸ poni¿ej podany kod by otworzyæ drzwi i rozpocz¹æ ³adowanie!\nJe¿eli przepiszesz kod w b³êdny sposób napad zostanie przerwany!\n\nKOD:\n %s",Rob[HackStr]);
	Dialog_Show(playerid,DIALOG_HACK,DIALOG_STYLE_INPUT,"Hackowanie",dstr,"WPISZ","");
	
	new gStr[256];
	format(gStr,256,"{3399ff}"chat" UWAGA!! Gang {FFFFFF}%s {3399ff}rozpoczyna hackowanie w napadzie. Zabicie jednego z nick da ci 350 XP.",gInfo[Rob[GangID]][gangNazwa]);
	SendClientMessageToAll(-1,gStr);
	SendClientMessageToAll(COLOR_ERROR,"{3399ff}"chat" Gracze bior¹cy udzia³ w napadzie posiadaj¹ czarne nicki.");
	
	
	return 1;
}

CMD:laduj(playerid,params[])
{
	if(!Rob[Active])return SendClientMessage(playerid,COLOR_ERROR,"Aktualnie nie trwa ¿aden napad.");
	if(!pRob[playerid][playing]) return SendClientMessage(playerid,COLOR_ERROR,"Nie bierzesz udzia³u w napadzie.");
	if(Rob[Hakowanie] != 1)return SendClientMessage(playerid,COLOR_ERROR,"Hacker nie z³ama³ jeszcze zabezpieczeñ drzwi.");
	if(!IsPlayerInVehicle(playerid,Rob[MainCar])) return SendClientMessage(playerid,COLOR_ERROR,"Nie jesteœ w transporterze.");
	if(GetPlayerVehicleSeat(playerid) != 0)return SendClientMessage(playerid,COLOR_ERROR,"Nie jesteœ kierowc¹.");
	if(!IsPlayerInRangeOfPoint(playerid,4.0,1097.6219,-1331.5980,13.1564))return SendClientMessage(playerid,COLOR_ERROR,"Jesteœ za daleko punktu /laduj.");
	if(Rob[Ladowanie]) return SendClientMessage(playerid,COLOR_ERROR,"£adowanie ju¿ trwa.");
	
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
	{
		if(pRob[i][playing])
		{
			SendClientMessage(i,COLOR_ERROR,"£adowanie rozpoczê³o siê! Chroñ ciê¿arówkê!");
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
				SendClientMessage(i , COLOR_ERROR, "Ciê¿arówka zosta³a przemieszczona i ³adowanie musi zostaæ rozpoczête od nowa!");
				Rob[Ladowanie] = false;
			}
		}
		return 1;
	}
	new rstr[256];
	format(rstr,256,"{3399ff}Gang {FFFFFF}%s {3399ff}skoñczy³ ³adowanie do ciê¿arówki. Zabij jednego z nich by zyskaæ 350 XP. Gracze posiadaj¹ czarne nicki i znajduj¹ siê w okolicach Vinewood.",gInfo[Rob[GangID]][gangNazwa]);
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
			format(rstr,256,"{3399ff}Gang {FFFFFF}%s {3399ff}skoñczy³ hackowaæ drzwi i za chwilê rozpocznie ³adowanie do ciê¿arówki. Zabij ich by zyskaæ XP.",gInfo[Rob[GangID]][gangNazwa]);
			SendClientMessageToAll(-1,rstr);
			Rob[Hakowanie] = 1;
			for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
			{
				if(pRob[i][playing])
				{
					SendClientMessage(i,COLOR_ERROR,"Hakowanie udane! Teraz trzeba podjechaæ ciê¿arówk¹ w miejsce ³adowania i wpisaæ /laduj");
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
	if(!Rob[Active])return SendClientMessage(playerid,COLOR_ERROR,"Aktualnie nie trwa ¿aden napad.");
	if(pInfo[playerid][player_gang] != Rob[GangID])return SendClientMessage(playerid,COLOR_ERROR,"Nie jesteœ cz³onkiem gangu rabuj¹cego.");
	if(pRob[playerid][Died])return SendClientMessage(playerid,COLOR_ERROR,"Nie mo¿esz siê zapisaæ do tego napadu poniewa¿ ju¿ zgin¹³eœ.");
	
	pRob[playerid][playing] = true;
	pRob[playerid][Healed] = 0;
	pRob[playerid][Died] = 0;
	pRob[playerid][Role] = 0;
	SetPlayerPos(playerid,2774.4275,-2531.7104,13.6383);
	SetPlayerInterior(playerid,0);
	ResetPlayerWeapons(playerid);
	SetPlayerColor(playerid,0x000000FF);
	if(Rob[Hacker] == 0) { SendClientMessage(playerid,0x99ccffFF,""chat" Hacker nie zosta³ jeszcze wybrany. Wpisz /hacker ¿eby nim zostaæ "); }
	if(Rob[Muscle] == 0) { SendClientMessage(playerid,0x99ccffFF,""chat" Doœwiadczony ¿o³nierz nie zosta³ jeszcze wybrany. Wpisz /muscle ¿eby nim zostaæ"); }
	SendClientMessage(playerid,0x99ccffFF,""chat" Wpisz /soldier ¿eby zostaæ ¿o³nierzem i braæ udzia³ w napadzie");
	return 1;
}
CMD:hacker(playerid,params[])
{
	new id = playerid;
	if(pRob[id][playing] == false)return SendClientMessage(playerid,COLOR_ERROR,"Nie jesteœ zapisany na ¿aden napad.");
	if(pRob[id][Role] != 0)return SendClientMessage(playerid,COLOR_ERROR,"Ju¿ masz wybrana rolê w tym napadzie.");
	if(Rob[Hacker] >= 1) {
		SendClientMessage(playerid,COLOR_ERROR,"Hacker ju¿ zosta³ wybrany. Wybierz inn¹ funkcjê w napadzie: ");
		if(Rob[Muscle] == 0) { SendClientMessage(playerid,0x99ccffFF,""chat" Doœwiadczony ¿o³nierz nie zosta³ jeszcze wybrany. Wpisz /muscle ¿eby nim zostaæ"); }
		SendClientMessage(playerid,0x99ccffFF,""chat" Wpisz /soldier ¿eby zostaæ ¿o³nierzem i braæ udzia³ w napadzie");
	}	
	
	Rob[Hacker] = 1;
	Rob[Robers] ++;
	pRob[id][Role] = 2;
	SetUpRobPlayer(playerid);
	new Hstr[128];
	format(Hstr,128,""chat" Gracz %s wybra³ funkcjê hackera w napadzie!",playerNick(playerid));
	SendClientMessage(playerid,0x99ccffFF,""chat" Twoim zadaniem bêdzie zhakowanie drzwi komend¹ /hackuj");
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
	if(pRob[id][playing] == false)return SendClientMessage(playerid,COLOR_ERROR,"Nie jesteœ zapisany na ¿aden napad.");
	if(pRob[id][Role] != 0)return SendClientMessage(playerid,COLOR_ERROR,"Ju¿ masz wybrana rolê w tym napadzie.");
	if(Rob[Muscle] >= 1) {
		SendClientMessage(playerid,COLOR_ERROR,"Doswiadczony ¿o³nierz ju¿ zosta³ wybrany. Wybierz inn¹ funkcjê w napadzie: ");
		if(Rob[Hacker] == 0) { SendClientMessage(playerid,0x99ccffFF,""chat" Hacker nie zosta³ jeszcze wybrany. Wpisz /hacker ¿eby nim zostaæ "); }
		SendClientMessage(playerid,0x99ccffFF,""chat" Wpisz /soldier ¿eby zostaæ ¿o³nierzem i braæ udzia³ w napadzie");
		return 1;
	}	
	
	Rob[Muscle] = 1;
	Rob[Robers] ++;
	pRob[id][Role] = 3;
	SetUpRobPlayer(playerid);
	new Hstr[128];
	format(Hstr,128,""chat" Gracz %s wybra³ funkcjê doœwiadczonego ¿o³nierza w napadzie!",playerNick(playerid));
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
	if(pRob[id][playing] == false)return SendClientMessage(playerid,COLOR_ERROR,"Nie jesteœ zapisany na ¿aden napad.");
	if(pRob[id][Role] != 0)return SendClientMessage(playerid,COLOR_ERROR,"Ju¿ masz wybrana rolê w tym napadzie.");

	
	Rob[Muscle] = pInfo[playerid][player_id];
	Rob[Robers] ++;
	pRob[id][Role] = 1;
	SetUpRobPlayer(playerid);
	new Hstr[128];
	format(Hstr,128,""chat" Gracz %s wybra³ funkcjê ¿o³nierza w napadzie!",playerNick(playerid));
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
			SendClientMessage(x, COLOR_ERROR,"-> Twój gang rozpoczyna napad.. Zapisz siê poprzez komendê /zapisz");
			SendClientMessage(x, COLOR_ERROR,"-----> Nie ma mo¿liwoœci wypisania siê z napadu a¿ do samego koñca!");
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
			format(fstr,256,"{3399ff}Napad gangu {FFFFFF}%s{3399ff} zosta³ zakoñczony poniewa¿ wszyscy zgineli!",gInfo[Rob[GangID]][gangNazwa]);
			SendClientMessageToAll(-1,fstr);
		}
		case 2: { //they did it
			format(fstr,256,"{3399ff}Napad gangu {FFFFFF}%s{3399ff} zosta³ zakoñczony sukcesem! Ka¿dy z ¿yj¹cych cz³onków dostaje po %d XP",gInfo[Rob[GangID]][gangNazwa], Rob[Win]);
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
			format(fstr,256,"{3399ff}Napad gangu {FFFFFF}%s{3399ff} zosta³ zakoñczony poniewa¿ ich hacker nie z³ama³ zabezpieczeñ!",gInfo[Rob[GangID]][gangNazwa]);
			SendClientMessageToAll(-1,fstr);
		}
			
		case 4: { // Admin przerwa³
			format(fstr,256,"{3399ff}Napad gangu {FFFFFF}%s{3399ff} zosta³ zakoñczony przez Vice/Head Administratora",gInfo[Rob[GangID]][gangNazwa]);
			SendClientMessageToAll(-1,fstr);	
		}
		case 5: {
			format(fstr,256,"{3399ff}Napad gangu {FFFFFF}%s{3399ff} zosta³ zakoñczony poniewa¿ ich hacker zosta³ zabity!",gInfo[Rob[GangID]][gangNazwa]);
			SendClientMessageToAll(-1,fstr);
		}
		case 6: { // wszyscy wyszli z serwera
			format(fstr,256,"{3399ff}Napad gangu {FFFFFF}%s{3399ff} zosta³ zakoñczony poniewa¿ wszyscy cz³onkowie wyszli z serwera!",gInfo[Rob[GangID]][gangNazwa]);
			SendClientMessageToAll(-1,fstr);
		}
		case 7: { // czas minal
			format(fstr,256,"{3399ff}Napad gangu {FFFFFF}%s{3399ff} zosta³ zakoñczony poniewa¿ czas min¹³ (20 minut)!",gInfo[Rob[GangID]][gangNazwa]);
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
	strcat(nstr,"{FFFFFF}Regulamin napadów:\n\n \
	Klasa Doœwiadczony ¿o³nierz\n\
	{FF0000}- U¿ywanie RPG jest dozwolone tylko i wy³¹cznie w celu obrony pojazdu do transportu lub gracza z klas¹ Haker.\n\
	- U¿ywanie RPG jest dozwolone w pobli¿u miejsca gdzie haker wype³nia swoje zadanie oraz podczas jazdy transporterem. \n\
	- Zezwala siê strzelania do graczy, którzy próbuj¹ przeszkodziæ w napadzie oraz pojazdów, którymi ci gracze siê poruszaj¹\n\n\
	- Przy znalezieniu jakiegokolwiek buga zwi¹zanego z systemem napadów gracz zobowi¹zany jest do zg³oszenia go na forum serwera\n \
		w innym wypadku mo¿e on zostaæ zbanowany za bug using.\n\n \
	- Pomaganie swojemu gangowi (Zalicza siê do tego równie¿ osoba, która specjalnie wypisze siê z gangu na czas napadu) bez zapisania siê\n \
		do napadu poprzez komendê /zapisz bêdzie karane banem na 3 godziny.\n\n\n\
	{FFFFFF}Co i jak?\n\n\
	Je¿eli jesteœ liderem gangu i zebra³eœ swoich ludzi oraz omówi³eœ z nimi plan napadu to wpisz /gnapad.\n \
	Nastêpnie wszyscy chêtni cz³onkowie gangu musz¹ wpisaæ /zapisz by braæ udzia³ w napadzie.\n\n \
	W napadzie dostêpne s¹ 3 role:\n\
		- Haker: Haker jest g³ówn¹ osob¹ bez, której napad nie ma szans powodzenia. \n To on hackuje drzwi dziêki czemu mo¿na rozpocz¹æ ³adowanie do transportera. \n\
		- Doœwiadczony ¿o³nierz: Osoba, która posiada 250 Armor i 150 HP do tego 5 strza³ów RPG oraz granaty. \n Jego celem jest likwidowanie pojazdów graczy podczas ewentualnego poœcigu oraz ochrona hakera.\n\
		- ¯o³nierz: Jest to ca³a reszta graczy bior¹cych udzia³ w napadzie, którzy wspomagaj¹ ca³y napad swoimi umiejêtnoœciami.\n\n\
	Po wybraniu swojej roli korzystacie z cz³onkami swojego gangu z danych wam pojazdów. \nNajpierw trzeba dojechaæ transporterem w wyznaczone miejsce na mapie.\n\
	W tym miejscu haker rozpoczyna hakowanie drzwi i gdy mu siê powiedzie \nnalezy podjechaæ transporterem w miejsce, w którym widnieje napis /laduj.\
	\n\n\
	W tym momencie kierowca transportera wpisuje komende /laduj\n i w tej chwili nale¿y broniæ transportera przez minutê. \n\
	Po minucie gdy transporter nie zosta³ przemieszczony z miejsca \n³adunku wszystkim graczom bior¹cym udzia³ w napadzie uka¿e siê checkpoint na mapie.\n\
	Teraz celem wszystkich cz³onków napadu jest chroniæ transporter oraz\n jego kierowcê i dowieŸdŸ transporter w wyznaczone miejsce.\n\
	Je¿eli zadanie powiedzie siê wszyscy ¿yj¹cy cz³onkowie napadu zostan¹ nagrodzeni XP.\n\n\n\
	Dodatkowe informacje\n\n\
	Dostêpny jest równie¿ pojazd(karetka) w którym ka¿dy \ncz³onek napadu mo¿e uleczyæ siê 2 razy(!)\n\
	Dlatego dobr¹ myœl¹ bêdzie zabranie karetki ze sob¹ do\n miejsca gdzie nastêpuje hakowanie oraz za³adunek transportera.\n\n\
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
	if(!Rob[Active])return SendClientMessage(playerid,COLOR_ERROR,"Aktualnie nie trwa ¿aden napad.");
	if(!pRob[id][playing]) return SendClientMessage(playerid,COLOR_ERROR,"Nie bierzesz udzia³u w napadzie.");
	if(pRob[id][Healed] >=2)return SendClientMessage(playerid,COLOR_ERROR,"Ju¿ uleczy³eœ siê 2 razy!");
	if(!IsPlayerInVehicle(playerid,Rob[Medic]))return SendClientMessage(playerid,COLOR_ERROR,"Musisz byæ w karetce!");
	
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
	SendClientMessage(playerid,COLOR_ERROR,"Uleczy³eœ siê! Pamiêtaj, ¿e mo¿esz uleczyæ siê maksymalnie 2 razy!");
	
	return 1;
}


CMD:gnapad(playerid,params[])
{
	if(pInfo[playerid][player_gangrank] < gRank_szef)return SendClientMessage(playerid,COLOR_ERROR,"Nie jesteœ liderem ¿adnego gangu.");
	if(!Rob[CanRob])return SendClientMessage(playerid,COLOR_ERROR,"Napad gangowy mo¿na przeprowadzaæ co 15 minut. Jeszcze nie mo¿na przeprowadziæ napadu.");
	new czh, czm;
	gettime(czh, czm);
	
	if(!(czh > 6 && czh < 23)) 
		return SendClientMessage(playerid, COLOR_ERROR, "» Dostêp do uzywanie komendy dostepny w godzinach {b}od 6 do 23{/b}.");
	
	
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
		SendClientMessage(playerid,-1,"B£¥D KRYTYCZNY. ZG£OŒ TO NA FORUM SERWERA.");
		return 0;
	}
	
	if(Countt < MinPlayers)return SendClientMessage(playerid,COLOR_ERROR,"Na serwerze znajduje siê za ma³o graczy.");
	
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
