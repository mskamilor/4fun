#define 		COL		0x008ae6FF



stock addons_init()
{
	// Najlepszy admin serwera obiekty
	CreateObject(18764, 1763.45178, 818.41437, 7.85576,   0.00000, 0.00000, 0.00000);
	CreateObject(11489, 1763.47351, 816.67426, 10.02139,   0.00000, 0.00000, -180.00000);
	CreateObject(18764, 1768.44507, 818.42065, 7.85576,   0.00000, 0.00000, 0.00000);
	CreateObject(18764, 1758.46558, 818.41492, 7.85576,   0.00000, 0.00000, 0.00000);

	Create3DTextLabel("Najlepsi administratorzy serwera\nMiesi¹c: Sierpieñ!",0x66ff1aFF,1763.4030,817.5320,15.6464,150.0,0,0);
	Create3DTextLabel("1. Msk.",0x66ff1aFF,1763.4030,817.5320,13.6464,150.0,0,0);
	Create3DTextLabel("3. GRanDI_",0xff3333FF,1759.6982,819.1105,11.3558,150.0,0,0);
	Create3DTextLabel("2. Magik",0xff9900FF,1766.9011,818.9125,11.3558,150.0,0,0);
	
	return 1;
}

CMD:setpos(playerid,params[])
{
	new Float:ff[3];
	sscanf(params, "p<,>a<f>[3]", ff);
	SetPlayerPos(playerid,ff[0], ff[1], ff[2]);
	return 1;
}


forward MMsg();
public MMsg()
{
	new mstr[256];
	
	SendClientMessageToAll(0x66ffffFF,""chat" ==========================================]  /NOWOŒCI  [==========================================");
	SendClientMessageToAll(0x66ffffFF,""chat" Na serwerze istnieje mo¿liwoœæ sadzenia oraz palenia marihuany "chat"{FFFFFF} /ziolohelp ");
	format(mstr,256,""chat" Aktualna broñ dnia to {FFFFFF}%s (%d)", GetWeaponNameEx(gmData[server_gunday]), gmData[server_gunday]);
	SendClientMessageToAll(0x66ffffFF,mstr);
	SendClientMessageToAll(0x66ffffFF,""chat" Chcesz pokazaæ jak bardzo bogaty jesteœ? Kup Wyj¹tkowy pojazd prywatny!! "chat" {FFFFFF}/wpp");
	SendClientMessageToAll(0x66ffffFF,""chat" Na serwerze jest nowy innowacyjny system drwala! "chat" {FFFFFF}/drwal");
	SendClientMessageToAll(0x66ffffFF,""chat" ================================================================================================ ");
	
	new Hour, Minute, Second;
	gettime(Hour, Minute, Second);
	if(Hour == 03 && Minute == 15)
	{
		m_query("UPDATE `mreg_trees` SET `collected`=1");
		SendRconCommand("gmx");
	}
	return 1;
}

CMD:nowosci(playerid,params[])
{
	new mstr[256];
	
	SendClientMessage(playerid, 0x66ffffFF,""chat" ==========================================]  /NOWOŒCI  [==========================================");
	SendClientMessage(playerid, 0x66ffffFF,""chat" Na serwerze istnieje mo¿liwoœæ sadzenia oraz palenia marihuany "chat" {FFFFFF}/ziolohelp ");
	format(mstr,256,""chat" Aktualna broñ dnia to {FFFFFF}%s (%d)", GetWeaponNameEx(gmData[server_gunday]), gmData[server_gunday]);
	SendClientMessage(playerid, 0x66ffffFF,mstr);
	SendClientMessageToAll(0x66ffffFF,""chat" Chcesz pokazaæ jak bardzo bogaty jesteœ? Kup Wyj¹tkowy pojazd prywatny!! "chat" {FFFFFF}/wpp");
	SendClientMessage(playerid, 0x66ffffFF,""chat" Na serwerze jest nowy innowacyjny system drwala! "chat" {FFFFFF}/drwal");
	SendClientMessage(playerid, 0x66ffffFF,""chat" ================================================================================================ ");
	
	return 1;
}

stock AddKillStreak(playerid)
{
	pInfo[playerid][player_ks]++;
	new ks = pInfo[playerid][player_ks];
	new kStr[128];
	format(kStr,128,"Twój killstreak to {008ae6}%d{/b} zabójstw! Osi¹gaj wysokie killstreaki by zdobywaæ {008ae6}nagrody!{/b} (pomoc - /kinfo)",pInfo[playerid][player_ks]);
	SendClientMessage(playerid,-1,kStr);
	if(ks > 7)
	{
		GivePlayerScore(playerid,15);
	}
	switch(ks)
	{
		case 7: { // 7
			new Float:ff[3];
			GetPlayerPos(playerid,ff[0], ff[1], ff[2]);
			CreateExplosion(ff[0], ff[1], ff[2], 11, 5.0);
			SetPlayerHealth(playerid,100);
			SetPlayerArmour(playerid,100);
			format(kStr,128,""chat" {008ae6}%s{/b} osi¹gn¹³(a) killstreak {008ae6}%d{/b} zabójstw! Dostaje on(a) maskê rzeŸnika.",playerNick(playerid), ks);
			SendClientMessageToAll(-1,kStr);
			SetPlayerAttachedObject(playerid,0,19036,2,0.110000,0.022000,0.000000,0.000000,91.700004,86.400047,1.000000,1.000000,1.000000);			
		}
		case 15: { //15
			new Float:ff[3];
			GetPlayerPos(playerid,ff[0], ff[1], ff[2]);
			CreateExplosion(ff[0], ff[1], ff[2], 11, 5.0);
			SetPlayerHealth(playerid,100);
			SetPlayerArmour(playerid,100);
			format(kStr,128,""chat" {008ae6}%s{/b} osi¹gn¹³(a) killstreak {008ae6}%d{/b} zabójstw! Dostaje on(a) miniguna z 10 strza³ami.",playerNick(playerid), ks);
			SendClientMessageToAll(-1,kStr);	
			GivePlayerWeapon(playerid,38, 10);
		}
		case 22: { //22
			new Float:ff[3];
			GetPlayerPos(playerid,ff[0], ff[1], ff[2]);
			CreateExplosion(ff[0], ff[1], ff[2], 11, 5.0);
			SetPlayerHealth(playerid,100);
			SetPlayerArmour(playerid,100);
			format(kStr,128,""chat" {008ae6}%s{/b} osi¹gn¹³(a) killstreak {008ae6}%d{/b} zabójstw! Dostaje on(a) niewidzialny kolor nicku.",playerNick(playerid), ks);
			SendClientMessageToAll(-1,kStr);
			SetPlayerColor(playerid, 0xFFFFFF00);
			achievement(playerid,33);			
		}
		case 33: { //35
			new Float:ff[3];
			GetPlayerPos(playerid,ff[0], ff[1], ff[2]);
			CreateExplosion(ff[0], ff[1], ff[2], 11, 5.0);
			SetPlayerHealth(playerid,100);
			SetPlayerArmour(playerid,100);
			format(kStr,128,""chat" {008ae6}%s{/b} osi¹gn¹³(a) killstreak {008ae6}%d{/b} zabójstw! Odblokowuje on(a) ustawienie rangi{008ae6} * Unstoppable *.",playerNick(playerid), ks);
			SendClientMessageToAll(-1,kStr);	
		}
	}
	return 1;
}

CMD:kinfo(playerid,params[])
{
	new strk[1000];
	strcat(strk,"{FFFFFF}Zabijaj¹c graczy bêdziesz otrzymywa³ punkty do {008ae6}killstreaka\n{FFFFFF}Gdy zginiesz te punkty s¹ {008ae6}zerowane{FFFFFF}. Za odpowiedni¹ iloœæ zabójstw bez œmierci gracz otrzymuje nastêpuj¹ce {008ae6}nagrody: \n\n\n");
	strcat(strk,"{008ae6}7 zabójstw: {FFFFFF}Gracz dostaje maskê rzeŸnika!\n");
	strcat(strk,"{008ae6}15 zabójstw: {FFFFFF}Gracz dostaje miniguna z 10 strza³ami!\n");
	strcat(strk,"{008ae6}22 zabójstw: {FFFFFF}Gracz dostaje niewidzialny kolor nicku! Oraz osi¹gniêcie Unstoppable\n");
	strcat(strk,"{008ae6}33 zabójstw: {FFFFFF}Gracz mo¿e w tym momencie ustawiæ rangê * Unstoppable * w /ranga\n\n\nOd killstreaka 7 zabójstw gracz dostaje równie¿ nagrodê za ka¿de \nkolejne zabójstwo w wysokoœci 15 XP");
	Dialog_Show(playerid,DIALOG_JOBNHNOHN,DIALOG_STYLE_MSGBOX,"Killstreak",strk,"OK","");
	return 1;
}