/*
       
	  @author    : Emilijo "Correlli" Lovrich
	  @modyfiket : mrdrifter
  
 */ 
 
#if !defined MAX_HOT_AIR_BALLOONS
	#define MAX_HOT_AIR_BALLOONS (5)
#endif

#if !defined MAX_HOT_AIR_BALLOON_SPEED
	#define MAX_HOT_AIR_BALLOON_SPEED (10.0)
#endif
sf
#if !defined INVALID_HOT_AIR_BALLOON_ID
	#define INVALID_HOT_AIR_BALLOON_ID (-1)
#endif

new pData_BalonID[MAX_PLAYERS];
static
		bool:gOPF[3] = false;

/* ----- */

enum dataBalloon
{
	modelID,
	objectID,
	vehicleID,
	Float:speed,
	Float:position[8]
}

new
		balloonID = INVALID_HOT_AIR_BALLOON_ID, balloonData[MAX_HOT_AIR_BALLOONS][dataBalloon],
		Float:balloonGoTo[MAX_HOT_AIR_BALLOONS][3],
		bCount,
		bObjectload[MAX_HOT_AIR_BALLOONS];

/* ----- */

stock CreateHotAirBalloon(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz = 0.0)
{
	balloonID++;
	if(balloonID == MAX_HOT_AIR_BALLOONS)
	{
		printf("Limit of hot air balloons exceeded. Open the hab.inc and change the \"MAX_HOT_AIR_BALLOONS\" define to bigger value if you want to have more hot air balloons.\
				\nDon't forget that object limit in the current SA:MP version (0.3e) is 1000, so it's a good thing to use an object-streamer if you're having many hot air balloons on server.");
		balloonID--;
		return INVALID_HOT_AIR_BALLOON_ID;
	}
	new
			toBalloonID = GetFreeHotAirBalloonID();
	if(toBalloonID == INVALID_HOT_AIR_BALLOON_ID)
	{
		print("Error: There are no hot air balloon IDs free.");
		balloonID--;
		return INVALID_HOT_AIR_BALLOON_ID;
	}
	if(modelid < 1 || modelid > 7)
	{
		printf("Invalid model-ID at function \"CreateHotAirBalloon\". Valid model-IDs are from 1 to 7.");
		balloonID--;
		return INVALID_HOT_AIR_BALLOON_ID;
	}
	balloonData[toBalloonID][modelID] = modelid;
	balloonData[toBalloonID][position][0] = x;
	balloonData[toBalloonID][position][1] = y;
	balloonData[toBalloonID][position][2] = z;
	balloonData[toBalloonID][position][3] = rx;
	balloonData[toBalloonID][position][4] = ry;
	balloonData[toBalloonID][position][5] = rz;
	balloonData[toBalloonID][position][6] = z;
	balloonData[toBalloonID][position][7] = rz;
	balloonData[toBalloonID][speed] = 0.0;
	balloonData[toBalloonID][objectID] = CreateObject(19331 + modelid, x, y, z, rx, ry, rz);
	balloonData[toBalloonID][vehicleID] = CreateVehicle(465, x, y, z, 0.0, 1, 1, -1);
	
	AttachObjectToVehicle(balloonData[toBalloonID][objectID], balloonData[toBalloonID][vehicleID], 0.0, 0.0, -10.0, 0.0, 0.0, 0.0);
	
	CreateDynamic3DTextLabel("Wpisz /BalonInfo aby dowiedzieæ siê wiêcej o Balonach!\n"HEX_INFO"Aby lecieæ Balonem wpisz /Balon (koszt 500 respektu 4 minuty)\nAby zatrzymaæ lot wpisz ponownie /Balon!", -1, x, y, z + 1.5, 20.0);
	
	bObjectload[bCount] = balloonData[toBalloonID][objectID];
	bCount++;
	return toBalloonID;
}
CMD:igbalon(playerid, cmdtext[])
{
	return 1;
}
stock LoadBalons()
{
	CreateHotAirBalloon(1, 1461.8, -2544.3, 12.51, 0.0, 0.0, 0.0);
	CreateHotAirBalloon(2, 1511.8, -2544.3, 12.51, 0.0, 0.0, 0.0);
	CreateHotAirBalloon(5, 1561.8, -2544.3, 12.51, 0.0, 0.0, 0.0);
	CreateHotAirBalloon(3, 1731.8, -2544.3, 12.51, 0.0, 0.0, 0.0);
	CreateHotAirBalloon(7, 1791.8, -2544.3, 12.51, 0.0, 0.0, 0.0);
	
	new b = GetFreeHotAirBalon();
	
	printf("balony wczytane wolny %d", b);
}
stock GetFreeHotAirBalon()
{
	
	for(new a = 1; a < bCount; a++)
	{
		if(IsHotAirBalloonOccupied(a)==INVALID_PLAYER_ID)
		{
			return bObjectload[a-1];
		}
	}
	return 0;
}
stock DestroyHotAirBalloon(habid)
{
	if(habid >= MAX_HOT_AIR_BALLOONS || habid < 0) return true;
	if(IsHotAirBalloonCreated(habid))
	{
		balloonID--;
		balloonData[habid][modelID] = 0;
		balloonData[habid][position][0] = 0.0;
		balloonData[habid][position][1] = 0.0;
		balloonData[habid][position][2] = 0.0;
		balloonData[habid][position][3] = 0.0;
		balloonData[habid][position][4] = 0.0;
		balloonData[habid][position][5] = 0.0;
		balloonData[habid][position][6] = 0.0;
		balloonData[habid][position][7] = 0.0;
		balloonData[habid][speed] = 0.0;
		DestroyObject(balloonData[habid][objectID]);
		DestroyVehicleEx(balloonData[habid][vehicleID]);
		if(balloonID == INVALID_HOT_AIR_BALLOON_ID)
		{
			firstBalloon = false;
 		}
		foreach(new u : Player)
		{
			if((pData_BalonID[u] - 1) == habid)
			{
				pData_BalonID[u] = 0;
				ClearAnimations(u);
				SetPlayerPosFindZ(u, GetPlayerPosX(u), GetPlayerPosY(u), GetPlayerPosZ(u));
				break;
			}
		}
		return true;
	}
	return false;
}

stock IsHotAirBalloonCreated(habid)
{
	if(habid >= MAX_HOT_AIR_BALLOONS || habid < 0) return false;
	if(balloonData[habid][modelID]) return true;
	return false;
}

stock GetNumberOfHotAirBalloons() return balloonID;

stock GetFreeHotAirBalloonID()
{
	new
			habid = INVALID_HOT_AIR_BALLOON_ID;
	for(new a = 0; a < MAX_HOT_AIR_BALLOONS; a++)
	{
		if(!IsHotAirBalloonCreated(a))
		{
			habid = a;
			break;
		}
	}
	return habid;
}

stock StopHotAirBalloon(habid)
{
	if(habid >= MAX_HOT_AIR_BALLOONS || habid < 0) return true;
	if(!IsHotAirBalloonCreated(habid)) return false;
	balloonData[habid][speed] = 0.0;
	StopObject(balloonData[habid][objectID]);
	return true;
}

stock RespawnHotAirBalloon(habid)
{
	if(habid >= MAX_HOT_AIR_BALLOONS || habid < 0) return true;
	if(!IsHotAirBalloonCreated(habid)) return false;
	DestroyObject(balloonData[habid][objectID]);
	DestroyVehicleEx(balloonData[habid][vehicleID]);
	balloonData[habid][position][2] = balloonData[habid][position][6];
	balloonData[habid][position][5] = balloonData[habid][position][7];
	balloonData[habid][objectID] = CreateObject(19331 + balloonData[habid][modelID], balloonData[habid][position][0], balloonData[habid][position][1], balloonData[habid][position][2], balloonData[habid][position][3], balloonData[habid][position][4], balloonData[habid][position][5]);
	
	balloonData[habid][vehicleID] = CreateVehicle(465, balloonData[habid][position][0], balloonData[habid][position][1], balloonData[habid][position][2], 0.0, 1, 1, -1);
	
	AttachObjectToVehicle(balloonData[habid][objectID], balloonData[habid][vehicleID], 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	
	return true;
}

stock SetHotAirBalloonSpeed(habid, Float:balloonspeed = MAX_HOT_AIR_BALLOON_SPEED)
{
	if(habid >= MAX_HOT_AIR_BALLOONS || habid < 0) return true;
	if(!IsHotAirBalloonCreated(habid)) return false;
	if(balloonspeed > MAX_HOT_AIR_BALLOON_SPEED) balloonData[habid][speed] = MAX_HOT_AIR_BALLOON_SPEED;
	else balloonData[habid][speed] = balloonspeed;
	return true;
}

stock IsPlayerAtHotAirBalloon(playerid, habid)
{
	if(habid >= MAX_HOT_AIR_BALLOONS || habid < 0) return false;
	new
			Float:pos[3];
	GetObjectPos(balloonData[habid][objectID], pos[0], pos[1], pos[2]);
	if(IsPlayerInRangeOfPoint(playerid, 3.0, pos[0], pos[1], pos[2])) return true;
	return false;
}

stock IsPlayerAtAnyHotAirBalloon(playerid)
{
	new
			a = 0;
	for(a = 0; a < MAX_HOT_AIR_BALLOONS; a++)
	{
		if(IsPlayerAtHotAirBalloon(playerid, a)) return a;
	}
	return INVALID_HOT_AIR_BALLOON_ID;
}

stock IsHotAirBalloonOccupied(habid)
{
	if(habid >= MAX_HOT_AIR_BALLOONS || habid < 0) return INVALID_PLAYER_ID;
	if(!IsHotAirBalloonCreated(habid)) return INVALID_PLAYER_ID;
	foreach(new u : Player)
	{
		if((pData_BalonID[u] - 1) == habid) return u;
	}
	return INVALID_PLAYER_ID;
}

/* ----- */
 
forward Float:GetPlayerPosX(playerid);
Float:GetPlayerPosX(playerid)
{
	new
			Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	return Float:pos[0];
}

forward Float:GetPlayerPosY(playerid);
Float:GetPlayerPosY(playerid)
{
	new
			Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	return Float:pos[1];
}

forward Float:GetPlayerPosZ(playerid);
Float:GetPlayerPosZ(playerid)
{
	new
			Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	return Float:pos[2];
}

stock BalonStop(u)
{
	StopHotAirBalloon(pData_BalonID[u]-1);
	RespawnHotAirBalloon(pData_BalonID[u]-1);
	pData_BalonID[u] = 0;
	ClearAnimations(u);
	SetPlayerPosFindZ(u, GetPlayerPosX(u), GetPlayerPosY(u), GetPlayerPosZ(u));
}
/* ----- */

forward hab_Timer(u);
public hab_Timer(u)
{
	 
	if(pData_BalonID[u] - 1 != INVALID_HOT_AIR_BALLOON_ID)
	{
		if(!IsPlayerAtHotAirBalloon(u, pData_BalonID[u] - 1))
		{
			StopHotAirBalloon(pData_BalonID[u] - 1);
			RespawnHotAirBalloon(pData_BalonID[u] - 1);
			pData_BalonID[u] = 0;
			ClearAnimations(u);
			SendClientMessage(u, 0xFFFFFFFF, ""chat" Wypad³eœ z balonu zosta³ on zrespawniony.");
			SetPlayerPosFindZ(u, GetPlayerPosX(u), GetPlayerPosY(u), GetPlayerPosZ(u));
		}
	}
	
	return true;
}

/* ----- */
CMD:balontp(playerid, params[])
{

	if(GetPlayerScore(playerid) < 5) return SendClientMessage(playerid, COLOR_ERROR, ""chat" Teleportowanie do balonu kosztuje 5 punktów respektu.");
	new b = GetFreeHotAirBalon();
	
	if(!b) return SendClientMessage(playerid, COLOR_ERROR, ""chat" Chwilowo nie ma ¿adnego wolnego balonu. Spróbuj za jakiœ czas.");
	
	new
			Float:pos[3];
	GetObjectPos(bObjectload[b], pos[0], pos[1], pos[2]);
	SetPlayerPos(playerid, pos[0], pos[1], pos[2] + 0.5);
	
	SendClientMessage(playerid, COLOR_GOLD, ""chat" Teleportowa³eœ siê do balonu koszt 5 punktów respektu.");
	GivePlayerScore(playerid, (-5));
	return 1;
}

 
CMD:balon(playerid, params[])
{
	
	
	if(GetPlayerScore(playerid) < 500 && !pInfo[playerid][player_balontime]) return SendClientMessage(playerid, COLOR_ERROR, ""chat" Lot balonem kosztuje 500 punktów respektu.");
	new
			Float:objPos[3];
	if(!pData_BalonID[playerid])
	{
		new
				habid = IsPlayerAtAnyHotAirBalloon(playerid);
				
		if(habid >= MAX_HOT_AIR_BALLOONS || habid < 0) return true;
		if(habid != INVALID_HOT_AIR_BALLOON_ID)
		{
			new
					isOccupied = IsHotAirBalloonOccupied(habid);
			if(isOccupied != INVALID_PLAYER_ID) return SendClientMessage(playerid, 0xFFFFFFFF, ""chat" Nie mo¿esz lecieæ tym balonem poniewa¿ ktoœ ju¿ nim lata.");
			pData_BalonID[playerid] = habid + 1;
			GetObjectPos(balloonData[habid][objectID], objPos[0], objPos[1], objPos[2]);
			SetPlayerPos(playerid, objPos[0], objPos[1], objPos[2] + 1.0);
			SetPlayerFacingAngle(playerid, balloonData[habid][position][5]);
			ApplyAnimation(playerid, "ped", "DRIVE_BOAT", 4.0, 1, 0, 0, 0, 0);
			SendClientMessage(playerid, COLOR_GOLD, ""chat" Lecisz balonem wpisz \"/Balon\" aby zatrzymaæ balon. Twój balon jest aktywny na 4 minuty..");
			PutPlayerInVehicle(playerid, balloonData[habid][vehicleID], 0);
			
			if(!pInfo[playerid][player_balontime]) 
			{
				pInfo[playerid][player_balontime] = 180*2;
				//SendClientMessage(playerid, COLOR_GREEN, ""chat" Aktywowa³eœ komende {b}/Balon{/b} przez 4 minuty nie bêdzie Cie kosztowa³o nic jej u¿ycie!");
				GivePlayerScore(playerid, (-500));
			}
		}
		else SendClientMessage(playerid, COLOR_ERROR, ""chat" Nie jesteœ w pobli¿u ka¿dej balonem lub nie jesteœ wystarczaj¹co blisko.");
	}
	else
	{
		StopHotAirBalloon(pData_BalonID[playerid] - 1);
		pData_BalonID[playerid] = 0;
		ClearAnimations(playerid);
		SendClientMessage(playerid, 0xFFFFFFFF, ""chat" Zatrzyma³eœ Balon! :)");
	}
	return true;
}

/* ----- */

public OnPlayerConnect(playerid)
{
	ApplyAnimation(playerid, "ped", "null", 0.0, 0, 0, 0, 0, 0);
	pData_BalonID[playerid] = 0;
	if(gOPF[0]) CallLocalFunction("hab_OnPlayerConnect", "i", playerid);
	return true;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect hab_OnPlayerConnect

forward hab_OnPlayerConnect(playerid);



stock hab_OnPlayerDisconnect(playerid)
{
	new
			habid = pData_BalonID[playerid] - 1;
			
	if(habid >= MAX_HOT_AIR_BALLOONS || habid < 0) return true;
	if(habid != INVALID_HOT_AIR_BALLOON_ID)
	{
		StopHotAirBalloon(habid);
		RespawnHotAirBalloon(habid);
	}
	pData_BalonID[playerid] = 0;
	return true;
}



CMD:baloninfo(playerid, params[])
{
	ShowPlayerDialog(playerid, 9999, DIALOG_STYLE_MSGBOX, "Lot balonem", "Na serwerze mo¿na lataæ balonem które s¹ na lotniskach oraz pla¿y\nDo balonu mo¿na teleportowaæ siê komend¹ /balontp "HEX_ERROR"(koszt 10 rsp)"HEX_SAMP"\
	\nAby lecieæ balonem wystarczy w pobli¿u balonu wpisaæ wpisaæ "HEX_GOLD"/balon"HEX_SAMP" 4 minuty lotu kosztuje 500 respektu.\n\nStarowanie: \nShift - Balon leci w górê\nSpacja - Balon leci w dó³\nStrza³ki\
	, W, A, S, D - kierowanie balonem", "Zamknij", "");
	return 1;
}



stock hab_OnGameModeInit()
{
	gOPF[0] = (funcidx("hab_OnPlayerConnect") != -1);
	gOPF[1] = (funcidx("hab_OnPlayerDisconnect") != -1);
}

 