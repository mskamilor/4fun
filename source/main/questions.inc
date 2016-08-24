
#define ANSWER_TRUE			1
#define ANSWER_FALSE		0

#define ANSWERS_VW			94

#define _quest 7

#define QUEST_MIN_PLAYERS	2

#define questions_to_end	10

#define TRUE_MINX 2048.2612
#define TRUE_MAXX 2054.6768
#define TRUE_MINY 2426.1934
#define TRUE_MAXY 2438.1255
//IsPlayerInArea(playerid, Float:MinX, Float:MinY, Float:MaxX, Float:MaxY)
#define FALSE_MINX 2061.8418
#define FALSE_MAXX 2068.2222
#define FALSE_MINY 2426.1514
#define FALSE_MAXY 2438.1140

enum QuestionGame 
{
	Question[256], //pytanie
	Qused, // ile razy uzyte
	Qanswer, //odpowiedz
	bool:starting, //czy startuje
	bool:started, // czy wystartowalo
	QPlayers, // ilosc graczy
	Qstate,	// co sie aktualnie dzieje  
	PlayersS, // zapisanych graczy
	Starting,
	Questions
};

new Qobj[9];

new Quest[QuestionGame];
//- 0_nie wystartowalo, 1_gracze w lobby czekaja na pytanie, 2_graczom wyswietla sie pytanie i maja czas na wybranie odpowiedzi, 3_sprawdzanie odpowiedzi
enum PlayerQuestion
{
	bool:zapisany,
	bool:gra,
	punkty,
	answer
}
new qInfo[MAX_PLAYERS][PlayerQuestion];

new Text:QuestionTD;
new StartTimer;

forward QuestStarting();
public QuestStarting()
{
	Quest[Starting]++;
	if(Quest[PlayersS] < QUEST_MIN_PLAYERS) {
		KillTimer(StartTimer);
		SendClientMessageToAll(COLOR_EVENT_STARTED, "››› Stwierdzenia {b}(/st){/b} zosta³o przerwane poniewa¿ wszyscy gracze siê wypisali.");
		FlushVarbiales();
		for(new playerid = 0, j = GetPlayerPoolSize(); playerid <= j; playerid++) {
			FlushPlayerVariables(playerid);
		}
		FlushVarbiales();
		KillTimer(StartTimer);
	}
	switch(Quest[Starting])
	{
		case 20: {
			Quest[started] = true;
			Quest[starting] = false;
			KillTimer(StartTimer);
			SendClientMessageToAll(COLOR_EVENT_STARTED, "››› Stwierdzenia {b}(/st){/b} wystartowa³o!");
			Quest[Questions] = 0;
			Quest[QPlayers] = 0;
			Qobj[0] = CreateDynamicObject(984, 2068.62695, 2432.13940, 165.21043,   0.00000, 0.00000, 0.00000);
			Qobj[1] = CreateDynamicObject(984, 2047.84363, 2432.14160, 165.20784,   0.00000, 0.00000, 0.00000);
			Qobj[2] = CreateDynamicObject(984, 2062.23730, 2425.74683, 165.21043,   0.00000, 0.00000, -90.11999);
			Qobj[3] = CreateDynamicObject(984, 2054.23340, 2425.77710, 165.21043,   0.00000, 0.00000, -90.11999);
			Qobj[4] = CreateDynamicObject(984, 2054.26880, 2438.54395, 165.21043,   0.00000, 0.00000, -90.11999);
			Qobj[5] = CreateDynamicObject(984, 2062.25195, 2438.54321, 165.21043,   0.00000, 0.00000, -90.11999);
			Qobj[6] = CreateDynamicObject(984, 2062.24536, 2432.14819, 165.21043,   0.00000, 0.00000, 0.00000);
			Qobj[7] = CreateDynamicObject(984, 2054.24609, 2432.13062, 165.20784,   0.00000, 0.00000, 0.00000);
			Qobj[8] = CreateDynamicObject(18981, 2059.16260, 2434.74121, 164.31240,   0, -90, 0.00000);
			for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
			{
				if(qInfo[i][zapisany])
				{
					qInfo[i][gra] = true;
					qInfo[i][punkty] = 0;
					qInfo[i][answer] = -1;
					Quest[QPlayers] ++;
				}
			}
			SetPlayersToLobby();
		}
	}
	
	return 1;
}

CMD:st(playerid,params[])
{
	if(qInfo[playerid][zapisany])return SendClientMessage(playerid,-1,"{bfff80}Jesteœ ju¿ zapisany na zabawê w {a6ff4d}stwierdzenia!");
	if(Quest[started])return SendClientMessage(playerid,-1,"{bfff80}Zabawa w stwierdzenia ju¿ wystartowa³a. {a6ff4d}Poczekaj na jej koniec i zapisz siê na nastêpn¹ rundê.");
	
	removeIsEvent(playerid);
	
	AddPlayerToQuest(playerid);
	return 1;
}

CMD:stexit(playerid,params[])
{
	if(qInfo[playerid][zapisany] != true)return SendClientMessage(playerid,-1,"{bfff80}Nie jesteœ zapisany na zabawê w {a6ff4d}stwierdzenia!");
	
	RemovePlayerFromQuest(playerid);
	return 1;
}

stock AddPlayerToQuest(playerid)
{
	SendClientMessage(playerid,-1,"{bfff80}Zapisa³eœ siê na /st. {a6ff4d}Je¿eli chcesz siê wypisaæ wpisz /stexit");
	FlushPlayerVariables(playerid);
	qInfo[playerid][zapisany] = true;
	Quest[PlayersS]++;
	if(Quest[PlayersS] == QUEST_MIN_PLAYERS)
	{
		Quest[starting] = true;
		StartTimer = SetTimer("QuestStarting",1000,1);
		SendClientMessageToAll(COLOR_EVENT_STARTED, "››› Stwierdzenia wystartuje za {b}20 sekund {/b}Zapisy nadal trwaj¹ (/st)");
	}
	UpdateEvStat();
	return 1;
}

stock RemovePlayerFromQuest(playerid)
{
	SendClientMessage(playerid,-1,"{bfff80}Wypisa³eœ siê z /st");
	TextDrawHideForPlayer(playerid,QuestionTD);
	switch(Quest[Qstate])
	{
		case 0: {
			FlushPlayerVariables(playerid);
			Quest[PlayersS]--;
		}
		case 1,2,3:
		{
			FlushPlayerVariables(playerid);
			OnPlayerSpawn(playerid);
			Quest[QPlayers] --;
		}		
	}
	if(Quest[PlayersS] < 0)Quest[PlayersS] = 0;
	if(Quest[QPlayers] <= 0 && Quest[started])
	{
		ZakonczQuest();
	}
	UpdateEvStat();
	TextDrawHideForPlayer(playerid,QuestionTD);
	
	return 1;
}

stock FlushVarbiales()
{
	Quest[Question] = -1;
	Quest[Qused] = -1;
	Quest[Qanswer] = -1;
	Quest[starting] = false;
	Quest[started] = false;
	Quest[QPlayers] = 0;
	Quest[PlayersS] = 0;
	Quest[Qstate] = 0;
	Quest[Starting] = 0;
	return 1;
}

stock FlushPlayerVariables(x)
{
	qInfo[x][zapisany] = false;
	qInfo[x][gra] = false;
	qInfo[x][punkty] = -1;
	qInfo[x][answer] = -1;
	return 1;
}

stock SetPlayersToLobby()
{
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
	{
		if(qInfo[i][gra])
		{
			SetPlayerPos(i,2058.24756, 2431.93872, 164.95654);
			SetPlayerVirtualWorld(i,ANSWERS_VW);
			SetPlayerInterior(i,0);
			SetPlayerHealth(i,100.0);
			SetPlayerArmour(i,100.0);
			TextDrawHideForPlayer(i,QuestionTD);
			SendClientMessage(i,-1,"{bfff80}Za 5 sekund wyœwietli siê stwierdzenie na ekranie. {a6ff4d}Stan w strefie PRAWDA lub FALSZ by udzielic odpowiedzi!");
			ResetPlayerWeapons(i);
		}
	}
	Quest[Qstate] = 1;
	SetTimer("WyswietlPytanie",5000,0);
	return 1;
}

forward SprawdzOdpowiedzi();

public SprawdzOdpowiedzi()
{
	printf("state: %d. started: %d. Qanswer: %d. Question: %s",Quest[Qstate], Quest[started], Quest[Qanswer], Quest[Question]);
	if(Quest[started])
	{
		Quest[Qstate] = 3;
		switch(Quest[Qanswer])
		{
			case 0: { // fa³sz
				for(new playerid = 0, j = GetPlayerPoolSize(); playerid <= j; playerid++) {
					if(IsPlayerInArea(playerid, FALSE_MAXX, FALSE_MINX, FALSE_MAXY,FALSE_MINY ))
					{
						if(qInfo[playerid][gra])
						{
							qInfo[playerid][punkty]++;
							SendClientMessage(playerid,-1,"{bfff80}Twoja odpowiedŸ na pytanie to: {FF0000}FA£SZ. {a6ff4d}Nie powiemy czy to prawid³owa odpowiedŸ, przekonasz siê na koniec gdy podliczymy twoje punkty!");
						}
						
					}
					else 
					{
						if(qInfo[playerid][gra])
						{
							SendClientMessage(playerid,-1,"{bfff80}Twoja odpowiedŸ na pytanie to: {00FF00}PRAWDA. {a6ff4d}Nie powiemy czy to prawid³owa odpowiedŸ, przekonasz siê na koniec gdy podliczymy twoje punkty!");
						}
					}
				}
			}
			case 1: { // prawda
				for(new playerid = 0, j = GetPlayerPoolSize(); playerid <= j; playerid++) {	
					if(IsPlayerInArea(playerid, TRUE_MAXX, TRUE_MINX, TRUE_MAXY,TRUE_MINY))
					{
						if(qInfo[playerid][gra])
						{
							qInfo[playerid][punkty]++;
							SendClientMessage(playerid,-1,"{bfff80}Twoja odpowiedŸ na pytanie to: {00FF00}PRAWDA. {a6ff4d}Nie powiemy czy to prawid³owa odpowiedŸ, przekonasz siê na koniec gdy podliczymy twoje punkty!");
						}
					}
					else 
					{
						if(qInfo[playerid][gra])
						{
							SendClientMessage(playerid,-1,"{bfff80}Twoja odpowiedŸ na pytanie to: {FF0000}FA£SZ. {a6ff4d}Nie powiemy czy to prawid³owa odpowiedŸ, przekonasz siê na koniec gdy podliczymy twoje punkty!");
						}
					}	
				}
			}
		}
		if(Quest[Questions] >= questions_to_end)
		{
			ZakonczQuest();
		} else {
			SetPlayersToLobby();
		}
	}
	return 1;
}

stock ZakonczQuest()
{
	SendClientMessageToAll(COLOR_EVENT_STARTED, "››› Stwierdzenia (/st) zosta³o zakoñczone!");
	FlushVarbiales();
	for(new playerid = 0, j = GetPlayerPoolSize(); playerid <= j; playerid++) {
		if(qInfo[playerid][gra]) {
			new str[222];
			format(str,222,"{bfff80}Wybra³eœ %d dobrych odpowiedzi. Dostajesz za to %d XP oraz %d $",qInfo[playerid][punkty],qInfo[playerid][punkty]*25,qInfo[playerid][punkty]*2000 );
			SendClientMessage(playerid,-1,str);
			GivePlayerScore(playerid,qInfo[playerid][punkty]*25);
			GivePlayerMoney(playerid,qInfo[playerid][punkty]*2000);
			
			FlushPlayerVariables(playerid);
			TextDrawHideForPlayer(playerid,QuestionTD);
			OnPlayerSpawn(playerid);
		}
	}
	for(new x = 0; x < 9; x ++)
	{
		DestroyDynamicObject(Qobj[x]);
	}
	KillTimer(StartTimer);
	
	return 1; 
}

forward WyswietlPytanie();
public WyswietlPytanie()
{
	LosujPytanie();
	for(new playerid = 0, j = GetPlayerPoolSize(); playerid <= j; playerid++) {
		if(qInfo[playerid][gra])
		{
			TextDrawShowForPlayer(playerid,QuestionTD);
		}
	}
	SetTimer("SprawdzOdpowiedzi", 10000,0);
	return 1;
}

stock LosujPytanie()
{
	Quest[Questions] ++;
	new Query[256],IDD;
	m_query("SELECT ID,answer, used, question FROM "prefix"_questions WHERE used=0 ORDER BY RAND() LIMIT 1");
	mysql_store_result();
	mysql_insert_id();
	
	if(mysql_num_rows() == 0)
	{
		m_query("UPDATE `mreg_questions` SET `used`=0");
		m_query("SELECT ID,answer, used, question FROM "prefix"_questions WHERE used=0 ORDER BY RAND() LIMIT 1");
		mysql_store_result();
		mysql_insert_id();
	}
	
	if(mysql_num_rows())
	{
		mysql_fetch_row(Query, "|");
		sscanf(Query, "p<|>ddds[256]", IDD,Quest[Qanswer], Quest[Qused], Quest[Question]);
	}
	new qstr[256];
	format(qstr,256,"Pytanie nr. %d~n~%s~n~~n~~w~Stan w polu ~h~~g~PRAWDA ~w~lub ~h~~r~FALSZ", Quest[Questions], Quest[Question]);
	TextDrawSetString(QuestionTD, qstr);
	mysql_free_result();
	format(qstr,256,"UPDATE `mreg_questions` SET `used`=1 WHERE ID=%d",IDD);
	printf("%s",qstr);
	m_query(qstr);
	Quest[Qstate] =2;
	return 1;
}


stock news_init()
{
	Create3DTextLabel("_",0x00FF00FF,2050.6577,2432.3369,-165.6172,25.0,ANSWERS_VW,0);
	Create3DTextLabel("_",0xFF0000FF,2065.8625,2432.2065,-165.6172,25.0,ANSWERS_VW,0);
	Create3DTextLabel("PRAWDA",0x00FF00FF,2050.6577,2432.3369,165.6172,25.0,ANSWERS_VW,0);
	Create3DTextLabel("FA£SZ",0xFF0000FF,2065.8625,2432.2065,165.6172,25.0,ANSWERS_VW,0);
	
	QuestionTD = TextDrawCreate(314.222198, 173.724456, "Pytanie nr. 1~n~~n~Magnetofon zostal wynaleziony przez nazistow~n~~n~~w~Stan w polu ~h~~g~PRAWDA ~w~lub ~h~~r~FALSZ");
	TextDrawLetterSize(QuestionTD, 0.421110, 1.824000); 
	TextDrawTextSize(QuestionTD, 753.333679, 652.089172);
	TextDrawAlignment(QuestionTD, 2);
	TextDrawColor(QuestionTD, -1);
	TextDrawUseBox(QuestionTD, true);
	TextDrawBoxColor(QuestionTD, -224);
	TextDrawSetShadow(QuestionTD, 0);
	TextDrawSetOutline(QuestionTD, -1);
	TextDrawBackgroundColor(QuestionTD, 51);
	TextDrawFont(QuestionTD, 1);
	TextDrawSetProportional(QuestionTD, 1);
	
	return 1;
}
/*
IsPlayerInArea(playerid, Float:MinX, Float:MinY, Float:MaxX, Float:MaxY)
{
	new Float:X, Float:Y, Float:Z;

	GetPlayerPos(playerid, X, Y, Z);
	if(X >= MinX && X <= MaxX && Y >= MinY && Y <= MaxY) {
		return 1;
	}
	return 0;
}*/