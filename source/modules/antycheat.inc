/*
Anty cheat


@author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
@date      : 03 luty 2013
@update    : 03 luty 2013

*/

//NOTE: not used reason banned as connect
//#define antycheat_USESendClientCheck
#define ACDEBUG

#if defined ACDEBUG0
	#define AC_LOG(%0) 	systemprintf("anticheat", true, %0), SendAdminsMessage(0xff0000ff, %0)
#else
	#define AC_LOG(%0) 	systemprintf("anticheat", true, %0)
#endif
#define ac_xyz(%0) %0[0],%0[1],%0[2]

enum e_AC_Cheats
{
	ac_AirBrk,
	ac_FlyHack,
	ac_FastWalk,
	ac_VehicleHack,
	ac_NoFPSLimit,
	ac_ParkourMod,
};

enum e_AC_Data
{
	Float:ac_lastPos[4],
	ac_cleanData,
	ac_warn[e_AC_Cheats],	
	ac_warn_time[e_AC_Cheats]

};
new AC_Data[MAX_PLAYERS][e_AC_Data];


stock AC_Timer(playerid)
{
	static anim_id,
		Float:PosX, Float:PosY, Float:PosZ,
		loop_player_weapon,
		loop_player_speed,
		distance,
		loop_player_vehid;
		
	static animlib[32];
	static animname[32];
	if(AC_Data[playerid][ac_cleanData] > gettime())
	{
		AC_Data[playerid][ac_cleanData] = gettime()+59;
	
		for(new x; e_AC_Cheats:x != e_AC_Cheats; x++) 
			if(AC_Data[playerid][ac_warn][e_AC_Cheats: x] > 0) AC_Data[playerid][ac_warn][e_AC_Cheats: x]--; 	
	}
	if(!IsPlayerSpawned(playerid))
		return;
	
	anim_id = GetPlayerAnimationIndex(playerid);
	loop_player_weapon = GetPlayerWeapon(playerid);
	loop_player_vehid = GetPlayerVehicleID(playerid);
	
	if(loop_player_vehid)
		GetVehicleVelocity(loop_player_vehid, PosX, PosY, PosZ);
	else 
		GetPlayerVelocity(playerid, PosX, PosY, PosZ);
	
	loop_player_speed = floatround(floatsqroot((PosX*PosX+PosY*PosY+PosZ*PosZ))*(100.0)*1.6);
	
	if(loop_player_vehid)
		GetVehiclePos(loop_player_vehid, PosX, PosY, PosZ);
	else
		GetPlayerPos(playerid, PosX, PosY, PosZ);
			
	distance = floatround(GetPlayerDistanceFromPoint(playerid, AC_Data[playerid][ac_lastPos][0], AC_Data[playerid][ac_lastPos][1], AC_Data[playerid][ac_lastPos][2]));
		
	if(pInfo[playerid][player_kickOnlySobeit] && pInfo[playerid][player_connected] > 40)
	{
		AddPlayerPenalty(playerid, P_KICK, INVALID_PLAYER_ID, 90, "d3d9.dll (SOBEIT!!)");
		InfoBox(playerid, "d3d9.dll detected\n\n----------------------------\n\n\nProsimy o usuniecie s0beita!");
		
		return;
	}
		
				
	if(AC_Data[playerid][ac_lastPos][0] != 0.0 && AC_Data[playerid][ac_lastPos][1] != 0.0)
	{
		if(GetPlayerSurfingVehicleID(playerid) == INVALID_VEHICLE_ID)
		{
 			if(distance >= 35 && distance < 250 && loop_player_speed < 30)
			{
				AC_LOG("[AirBrk:%d/%d] %s status: %d distance: %d speed: %d", pInfo[playerid][player_id], AC_Data[playerid][ac_warn][ac_AirBrk], pInfo[playerid][player_name], pInfo[playerid][player_state], distance, loop_player_speed);
				AC_WarnCheat(playerid, ac_AirBrk);
			}
		}
	}
 
	
	if(loop_player_vehid != pInfo[playerid][player_usevehicle] && loop_player_vehid)
	{
		AC_LOG("[VehicleHack:%d] %s status: %d loop_player_vehid: %d player_usevehicle: %d anim_id: %d", pInfo[playerid][player_id], pInfo[playerid][player_name], pInfo[playerid][player_state], loop_player_vehid, pInfo[playerid][player_usevehicle], anim_id);
		SetPlayerPos(playerid, PosX, PosY, PosZ + 2); 			
		pInfo[playerid][player_usevehicle] = 0;
		
		if(PosZ > AC_Data[playerid][ac_lastPos][2])
			AC_WarnCheat(playerid, ac_VehicleHack);
		else if((AC_Data[playerid][ac_lastPos][2] - PosZ) < 5.0)
			AC_WarnCheat(playerid, ac_VehicleHack);
	}
	  
	if(!loop_player_vehid)
	{
		GetAnimationName(anim_id,animlib,32,animname,32);
		
		switch(anim_id)
		{
			case -1:
			{
				AC_WarnCheat(playerid, ac_ParkourMod);
				AC_LOG("[ac_FlyHack:%d] %s status: %d loop_player_speed: %d anim_id: %d pozZ: %.2f (%s, %s)", pInfo[playerid][player_id], pInfo[playerid][player_name], pInfo[playerid][player_state], loop_player_speed, anim_id, PosZ, animlib, animname);
			}
			case 958..979:
			{
				if(loop_player_weapon != 46)
				{
					AC_WarnCheat(playerid, ac_FlyHack);//7
					AC_LOG("[ac_FlyHack:%d] %s status: %d loop_player_speed: %d anim_id: %d pozZ: %.2f (%s, %s)", pInfo[playerid][player_id], pInfo[playerid][player_name], pInfo[playerid][player_state], loop_player_speed, anim_id, PosZ, animlib, animname);
				}
			}
			case 1058:
			{
				AC_WarnCheat(playerid, ac_FlyHack);
				AC_LOG("[ac_FlyHack:%d] %s status: %d loop_player_speed: %d anim_id: %d pozZ: %.2f (%s, %s)", pInfo[playerid][player_id], pInfo[playerid][player_name], pInfo[playerid][player_state], loop_player_speed, anim_id, PosZ, animlib, animname);

			}
			case 1231:
			{
				 
			}
		}
		if(loop_player_speed > 30.0 && 1537 < anim_id < 1545)
		{
			AC_WarnCheat(playerid, ac_FlyHack);
			AC_LOG("[vehac_FlyHack:%d] %s status: %d loop_player_speed: %d anim_id: %d pozZ: %.2f (%s, %s)", pInfo[playerid][player_id], pInfo[playerid][player_name], pInfo[playerid][player_state], loop_player_speed, anim_id, PosZ, animlib, animname);
		}
		 
	}
 

	if(GetPlayerFPS(playerid) > 108 && pInfo[playerid][player_afk] < 2 && distance > 2 && IsPlayerSpawned(playerid))
	{
		GetAnimationName(anim_id,animlib,32,animname,32);
		
		

		AC_LOG("[ac_NoFPSLimit:%d] %s fps: %d anim_id: %d (%s, %s)", pInfo[playerid][player_id], pInfo[playerid][player_name], GetPlayerFPS(playerid), anim_id, animlib, animname);
		
		if( (pInfo[playerid][player_loggaingcrash][0] + 4) < gettime() )
			AC_WarnCheat(playerid, ac_NoFPSLimit);
	}
		
	
	 
	AC_Data[playerid][ac_lastPos][0] = PosX;
	AC_Data[playerid][ac_lastPos][1] = PosY;
	AC_Data[playerid][ac_lastPos][2] = PosZ;
}

stock AC_SetPlayerPos(playerid, Float:x, Float:y, Float:z)
{
	AC_Data[playerid][ac_lastPos][0] = x;
	AC_Data[playerid][ac_lastPos][1] = y;
	AC_Data[playerid][ac_lastPos][2] = z;
}

stock AC_PutPlayerInVehicleEx(playerid)
{
	AC_Data[playerid][ac_lastPos][0] = 0.0;
	AC_Data[playerid][ac_lastPos][1] = 0.0;
	AC_Data[playerid][ac_lastPos][2] = 0.0;//samo sobie pobierze potem nowe pozycje 
}
 
stock AC_WarnCheat(playerid, e_AC_Cheats:cheat)
{
//	if(AC_Data[playerid][ac_warn_time][cheat] > gettime())  
		//return;
	
	AC_Data[playerid][ac_warn_time][cheat] = gettime() + 4;
	
	if(cheat == e_AC_Cheats:-1)
		if(AC_Data[playerid][ac_warn_time][cheat] > gettime())  
			return;
		
	AC_Data[playerid][ac_warn][cheat]++;
	
	new warns = 3;
	
	if(cheat == ac_NoFPSLimit) warns = 6;
	
	if(AC_Data[playerid][ac_warn][cheat] > warns)
	{
		AC_Data[playerid][ac_warn][cheat] = 0;
		
		
		if(cheat == ac_AirBrk)
		{
			ReportTextdrawForAdmin(splitf("AirBrk %s (%d)", playerNick(playerid), playerid));
		}
		else if(cheat == ac_FlyHack)
		{
			ReportTextdrawForAdmin(splitf("FlyHack %s (%d)", playerNick(playerid), playerid));
		}
		else if(cheat == ac_FastWalk)
		{
			ReportTextdrawForAdmin(splitf("FastWalk %s (%d)", playerNick(playerid), playerid));
		}
		else if(cheat == ac_VehicleHack)
		{
			ReportTextdrawForAdmin(splitf("VehicleHack %s (%d)", playerNick(playerid), playerid));
		}
		else if(cheat == ac_NoFPSLimit)
		{
		//	AddPlayerPenalty(playerid, P_KICK, INVALID_PLAYER_ID, 90, splitf("FPS: %d/103", GetPlayerFPS(playerid)));
		}
		else 
			ReportTextdrawForAdmin(splitf("Unknow cheat %s (%d)", playerNick(playerid), playerid));
		
		
	}

}

new NOP_Spawn[MAX_PLAYERS];
forward ACSpawnNOPForDetect(playerid, nop);
public ACSpawnNOPForDetect(playerid, nop)
{
	NOP_Spawn[playerid] = nop;
	return 1;
} 

forward OnSobeitDetect(playerid, set);
public OnSobeitDetect(playerid, set)
{
	if(set == 3)
	{
		AddPlayerPenalty(playerid, P_BAN, INVALID_PLAYER_ID, gettime() + 60*60, "GOD (SOBEIT!!)");
		InfoBox(playerid, "GOD\n\n----------------------------\n\n\nProsimy o usuniecie s0beita!");
	}
	if(set == 2)
	{
		pInfo[playerid][player_kickOnlySobeit] = true;
	}
	pInfo[playerid][player_sobeitStep] = set;
}


new ids[MAX_PLAYERS]; 
public OnPlayerSuspectedForAimbot(playerid,hitid,weaponid,warnings)
{
	#define wname GetWeaponNameEx(weaponid)
	#define nme playerNick(playerid)
	new Float:Wstats[BUSTAIM_WSTATS_SHOTS];
	
	ids[playerid]++; 
	if(warnings & WARNING_OUT_OF_RANGE_SHOT)
	{
	    SendAdminsMessage(COLOR_ERROR, "[ANTI AIM] [%d]%s(%d) strzela z odleg³oœci wiêkszej ni¿ normalny zakres broni %s (normalnie %d)",ids[playerid],nme,playerid,wname,BustAim::GetNormalWeaponRange(weaponid));
	
		BustAim::GetRangeStats(playerid,Wstats);
		systemprintf("aim", true, "[%d]%s(%d) %s Shooter to Victim Distance(SA Units): 1)%f 2)%f 3)%f",ids[playerid],nme,playerid,wname, Wstats[0],Wstats[1],Wstats[2]);
 		
	}
	if(warnings & WARNING_PROAIM_TELEPORT)
	{
	    SendAdminsMessage(COLOR_ERROR, "[ANTI AIM] [%d]%s(%d) Prawdopodobnie u¿ywa ProAIM",ids[playerid],nme,playerid);
		 
		BustAim::GetTeleportStats(playerid,Wstats);
		systemprintf("aim", true, "[%d]%s(%d) Bullet to Victim Distance(SA Units): 1)%f 2)%f 3)%f",ids[playerid],nme,playerid, Wstats[0],Wstats[1],Wstats[2]);
	}
	if(warnings & WARNING_RANDOM_AIM)
	{
	    SendAdminsMessage(COLOR_ERROR, "[%d]%s(%d) Prawdopodobnie u¿ywa AIM-BOTa prosimy obserorwaæ go. ",ids[playerid],nme,playerid,wname);
		 
		BustAim::GetRandomAimStats(playerid,Wstats);
		systemprintf("aim", true, "[%d]%s(%d) %s Random Aim Offsets: 1)%f 2)%f 3)%f",ids[playerid],nme,playerid,wname, Wstats[0],Wstats[1],Wstats[2]);
	}
	if(warnings & WARNING_CONTINOUS_SHOTS)
	{
	    SendAdminsMessage(COLOR_ERROR, "[%d]%s(%d) wystrzeli³ 10 razy w sposób ci¹g³y z broni %s(%d)",ids[playerid],nme,playerid,wname,weaponid);
		systemprintf("aim", true, "[%d]%s(%d) has fired 10 shots continously with %s(%d)",ids[playerid],nme,playerid,wname,weaponid);

	}
	return 0;
}
		
stock CheckPlayerAntyCheat(playerid)
{
	
	ids[playerid]=0;
	
	
	new connectd;
	foreach(new i : Player)
	{
		if(i == playerid) continue;
		if(!pInfo[playerid][player_ip][0]) continue;
		if(!strcmp(pInfo[playerid][player_ip], pInfo[i][player_ip], true))
		{
			connectd++;
		}
	}
	if(connectd >= 5)
	{
		if(!strcmp(pInfo[playerid][player_ip], "185.49.12.44")) return 1;
		SendAdminsMessage(COLOR_RED, splitf("[BAN] Zbanowano %s (IP %s) PRAWDOPDOBNY ATAK BOTÓW. Z jego IP zarejestrowano %d kont. ", pInfo[playerid][player_name], pInfo[playerid][player_ip], connectd));
		BanEx(playerid, "Flood");
		return 1;
	}
	return 0;
}

#define ANTIMACRO_MAX_WARNINGS			3		// Maximum warnings, punishment after that
#define ANTIMACRO_MIN_SPEED				40		// We don't need to check a player for macros if he's sprinting with such a speed
#define ANTIMACRO_MIN_SPEED_DIFF		0		// A player may not be checked for macros if the difference between his old speed and new speed is below this
#define ANTIMACRO_SPRINT_KEY_LIMIT		65		// Least acceptable time difference between each sprint key hit (in milliseconds)
#define ANTIMACRO_FORGET_WARNING_AFTER	1000	// Reset macro check variables after this time (milliseconds). 0 to forget immediately

// Options
#define ANTIMACRO_BADNET_CHECK			1		// 0 disable. If set to 1, antimacro will check player's net before checking sprint macros
#define ANTIMACRO_DEBUG					0		// 0 disable. If set to 1, server will send debug messages to all the online players

#if ANTIMACRO_BADNET_CHECK == 1
// Net check settings
#define ANTIMACRO_PACKETLOSS			1.5		// Dangerous packetloss, could cause false positive	
#endif

enum ANTIMACRO_DATA_STRUCTURE
{
	LastTimeSprinted, // Last time (tick count?) player pressed the sprint key
	LastMonitoredSpeed, // Last monitored speed by the server
	TimesWarned, // How many times warned
	LastTimeWarned // When the last warning was
}

new AntimacroData[MAX_PLAYERS][ANTIMACRO_DATA_STRUCTURE];

#define KEY_PRESSED(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define KEY_RELEASED(%0) (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

UpdatePlayerSprintMacroData(playerid, speed, tickcount, bool:forget) //z gamemodu AD
{
	AntimacroData[playerid][LastTimeSprinted] = tickcount;
	AntimacroData[playerid][LastMonitoredSpeed] = speed;
	if(forget && AntimacroData[playerid][TimesWarned] > 0)
	{
		if((tickcount - AntimacroData[playerid][LastTimeWarned]) >= (ANTIMACRO_FORGET_WARNING_AFTER - GetPlayerPing(playerid)))  // Has it been a while since they last got suspected?
			AntimacroData[playerid][TimesWarned] = 0; // forgive them and forget their bad history.
	}
	return 1;
}

bool:CheckPlayerSprintMacro(playerid, newkeys, oldkeys)
{	
	if(KEY_PRESSED(KEY_SPRINT)) // if pressed the sprint key
	{
		// Avoiding false positive...
		#if ANTIMACRO_BADNET_CHECK == 1
		if(NetStats_PacketLossPercent(playerid) >= ANTIMACRO_PACKETLOSS) // Is the packetloss dangerous?
		{
			//UpdatePlayerSprintMacroData(playerid, speed, tick, true);
			return false;
		}
		if(pInfo[playerid][player_afk]>2)
		{
			//UpdatePlayerSprintMacroData(playerid, speed, tick, true);
			return false;
		}
		#endif
		
		new Float:velocity[4];
		GetPlayerVelocity(playerid,velocity[0],velocity[1],velocity[2]);
		velocity[3] = floatsqroot(floatpower(floatabs(velocity[0]), 2.0) + floatpower(floatabs(velocity[1]), 2.0) + floatpower(floatabs(velocity[2]), 2.0)) * 179.28625;
	 
	
		new speed = floatround(velocity[3]); // player speed
		new tick = GetTickCount(); // current tick count
		if(GetPlayerVehicleID(playerid) != 0) // It's dumb to check for sprint macros if they're in a vehicle
		{
			UpdatePlayerSprintMacroData(playerid, speed, tick, true);
			return false;
		}
		if(GetPlayerSurfingVehicleID(playerid) != INVALID_VEHICLE_ID) // If player is surfing a vehicle, his speed is affected by the vehicle speed
		{
			UpdatePlayerSprintMacroData(playerid, speed, tick, true);
			return false;
		}
	
		if(speed < ANTIMACRO_MIN_SPEED) // If player's speed is less than the pre-defined speed, then he's harmless with that speed.
		{
			UpdatePlayerSprintMacroData(playerid, speed, tick, true);
			return false;
		}
		// Doing advanced checks now...
		if((speed - AntimacroData[playerid][LastMonitoredSpeed]) < ANTIMACRO_MIN_SPEED_DIFF) 
		{
			// We may not suspect them if their speed progress is less than this!
			UpdatePlayerSprintMacroData(playerid, speed, tick, true);
			return false;
		}
		new diff = tick - AntimacroData[playerid][LastTimeSprinted];
		if(diff >= ANTIMACRO_SPRINT_KEY_LIMIT || diff == 0)
		{
			// The time that's passed since they last pressed sprint key is okay
			UpdatePlayerSprintMacroData(playerid, speed, tick, true);
			return false;
		}
		AntimacroData[playerid][TimesWarned] ++;
		AntimacroData[playerid][LastTimeWarned] = tick;
		
		if(AntimacroData[playerid][TimesWarned] == ANTIMACRO_MAX_WARNINGS) // Have they been warned/suspected for sprint macros enough?
		{
			// Enough is enough. They don't learn, punish them now!
			
			AntimacroData[playerid][TimesWarned] = 0;
			AntimacroData[playerid][LastTimeWarned] = 0; 
		 
		 	ReportTextdrawForAdmin(splitf("~r~Macro %s (%d)~w~", playerNick(playerid), playerid));

			TogglePlayerControllable(playerid, false);
			TogglePlayerControllable(playerid, true);
			return true; // PUNISHED
		}
		UpdatePlayerSprintMacroData(playerid, speed, tick, false);
	}
	return false;
}
#undef KEY_PRESSED
#undef KEY_RELEASED