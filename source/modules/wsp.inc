/*
          Private special vehicles [1.0]
      (c) Copyright 2016 by Msk.
 
	  @author    : Msk.
	  @date      : 12 sierpnia 2016
	  @update    : 
 
	Wymagania: 1500km przebiegu w /pp, 75k exp
	Paliwe}
 */  
 
 // SPRZEDAWANIE!!!!!!!
 
#define		WPP_PRICE		 75000
#define		WPP_PRZEBIEG		1500
//#define     WPP_DEBUG //zakomentowac jesli debug off

#define 	TESTINGOFF	//odkomentowac jezeli ma zabierac xp

#define		UPDATEPALIWOTIME	15000

enum WppEnum
{
	vehicle,
	vehicle_id,
	Text3D:wlabel,
	owner,
	Float:paliwo,
	
	model,
	col1,
	col2,
	Float:wpos[4],
	obj[10]
}
new Wp[200][WppEnum];

new WHighestID;

#define 	MAX_STACJE		14

new Float:Stacje[MAX_STACJE][3] = {
	{-1663.8837, 415.1206, 7.1797}, 
	{-93.6236, -1161.1252, 2.1974}, 
	{1940.9291, -1772.9735, 13.6406}, 
	{1590.5996, 2205.8291, 10.8203}, 
	{2120.9756, 927.8674, 10.4663}, 
	{2198.8281, 2470.1577, 10.8203}, 
	{2634.7778, 1099.0471, 10.8203}, 
	{-1326.8135, 2687.6401, 50.0625}, 
	{-2408.9673, 981.5038, 45.2969}, 
	{-2239.9453, -2562.9939, 31.9219}, 
	{-1611.3301, -2722.0349, 48.5391}, 
	{602.2114, 1708.9861, 6.9922}, 
	{653.7541, -571.2383, 16.3359}, 
	{1386.0493, 459.7520, 20.0952}
};

#define		WPP_MENU		"Przywo³aj pojazd\nZaparkuj pojazd\nTeleportuj do pojazdu\nSprzedaj"
#define		WPP_KUP			"{FF0000}ADMIN DEBUG CAR - 1.000XP{FFFFFF}\nHell's Hotknife - 175.000 XP\nShitty Tampa - 120.00 XP"

CMD:wpp(playerid,params[])
{
	for(new x; x<WHighestID;x++)
	{
		if(Wp[x][owner] == pInfo[playerid][player_id])
		{
			return Dialog_Show(playerid,DIALOG_WPP,DIALOG_STYLE_LIST,"Wyj¹tkowy pojazd prywatny",WPP_MENU,"Wybierz","Anuluj");
		}
	}
	if(pInfo[playerid][player_car_przebieg] < WPP_PRZEBIEG)return SendClientMessage(playerid,COLOR_ERROR,"Aby kupiæ wyj¹tkowy pojazd specjalny twój /pp musi posiadaæ minimum 1500km przebiegu.");
	
	Dialog_Show(playerid,DIALOG_KUP,DIALOG_STYLE_LIST,"Kup wpp",WPP_KUP,"Kup","Anuluj");
	return 1;
}

Dialog:DIALOG_KUP(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0: { //debug car
				#if defined TESTINGOFF
				if(pInfo[playerid][player_admin] < 4)return SendClientMessage(playerid,COLOR_ERROR,"Pojazd dostêpny tylko dla Administratora poz. 3");
				#endif
				new Float:f[3], Qstr[256];
				GetPlayerPos(playerid,f[0], f[1], f[2]);
				
				Wp[WHighestID][owner] = pInfo[playerid][player_id];
				Wp[WHighestID][model] = 1;
				Wp[WHighestID][col1] = 0;
				Wp[WHighestID][col2] = 0;
				Wp[WHighestID][wpos][0] = f[0];
				Wp[WHighestID][wpos][1] = f[1];
				Wp[WHighestID][wpos][2] = f[2];
				Wp[WHighestID][wpos][3] = 0;
				Wp[WHighestID][paliwo] = 40.0;
				#if defined TESTINGOFF
				GivePlayerScore(playerid,-1000);
				#endif
				new labelstr[256];
				format(labelstr,256,"{ff661a}Wyj¹tkowy pojazd prywatny (/wpp)\nW³aœciciel: {FFFFFF}%s\n{ff661a}Paliwo: {FFFFFF}---/40 L",GetWppOwner(Wp[WHighestID][owner]));
				Wp[WHighestID][wlabel] = Create3DTextLabel(labelstr,0xFFFFFFFF,Wp[WHighestID][wpos][0],Wp[WHighestID][wpos][1],Wp[WHighestID][wpos][2], 35.0,0,0);
				
				new sstr[128];
				format(sstr,128,"%0.3f,%0.3f,%0.3f,%0.3f",Wp[WHighestID][wpos][0], Wp[WHighestID][wpos][1], Wp[WHighestID][wpos][2], Wp[WHighestID][wpos][3]);
				
				format(Qstr,256,"INSERT INTO `mreg_wpp`(`ID`, `owner`, `model`, `col1`, `col2`, `position`, `paliwo`) VALUES (NULL,%d, %d,%d,%d,'%s','%f')",Wp[WHighestID][owner], Wp[WHighestID][model], Wp[WHighestID][col1], Wp[WHighestID][col2],sstr, Wp[WHighestID][paliwo] );
				m_query(Qstr);
				SendClientMessage(playerid,COLOR_ERROR,"W³aœnie zakupi³eœ /wpp!");
				
				CreateWpVehicle(WHighestID);
			}
			case 1: { // hell's hotknife
				#if defined TESTINGOFF
				if(GetPlayerScore(playerid) < 175000)return SendClientMessage(playerid,COLOR_ERROR,"Potrzebujesz 275.000 XP");
				#endif
				new Float:f[3], Qstr[256];
				GetPlayerPos(playerid,f[0], f[1], f[2]);
				
				Wp[WHighestID][owner] = pInfo[playerid][player_id];
				Wp[WHighestID][model] = 2;
				Wp[WHighestID][col1] = 0;
				Wp[WHighestID][col2] = 0;
				Wp[WHighestID][wpos][0] = f[0];
				Wp[WHighestID][wpos][1] = f[1];
				Wp[WHighestID][wpos][2] = f[2];
				Wp[WHighestID][wpos][3] = 0;
				Wp[WHighestID][paliwo] = 40.0;
				#if defined TESTINGOFF
				GivePlayerScore(playerid,-175000);
				#endif
				new labelstr[256];
				format(labelstr,256,"{ff661a}Wyj¹tkowy pojazd prywatny (/wpp)\nW³aœciciel: {FFFFFF}%s\n{ff661a}Paliwo: {FFFFFF}---/40 L",GetWppOwner(Wp[WHighestID][owner]));
				Wp[WHighestID][wlabel] = Create3DTextLabel(labelstr,0xFFFFFFFF,Wp[WHighestID][wpos][0],Wp[WHighestID][wpos][1],Wp[WHighestID][wpos][2], 35.0,0,0);
				Attach3DTextLabelToVehicle(Wp[WHighestID][wlabel], Wp[WHighestID][vehicle],0,0,0);
				
				new sstr[128];
				format(sstr,128,"%0.3f,%0.3f,%0.3f,%0.3f",Wp[WHighestID][wpos][0], Wp[WHighestID][wpos][1], Wp[WHighestID][wpos][2], Wp[WHighestID][wpos][3]);
				
				format(Qstr,256,"INSERT INTO `mreg_wpp`(`ID`, `owner`, `model`, `col1`, `col2`, `position`, `paliwo`) VALUES (NULL,%d, %d,%d,%d,'%s','%f')",Wp[WHighestID][owner], Wp[WHighestID][model], Wp[WHighestID][col1], Wp[WHighestID][col2],sstr, Wp[WHighestID][paliwo] );
				m_query(Qstr);
				SendClientMessage(playerid,COLOR_ERROR,"W³aœnie zakupi³eœ /wpp!");
				
				CreateWpVehicle(WHighestID);
			}
			
			case 2: { // shitty tampa 220k
				#if defined TESTINGOFF
				if(GetPlayerScore(playerid) < 120000)return SendClientMessage(playerid,COLOR_ERROR,"Potrzebujesz 220.000 XP");
				#endif
				new Float:f[3], Qstr[256];
				GetPlayerPos(playerid,f[0], f[1], f[2]);
				
				Wp[WHighestID][owner] = pInfo[playerid][player_id];
				Wp[WHighestID][model] = 3;
				Wp[WHighestID][col1] = 0;
				Wp[WHighestID][col2] = 0;
				Wp[WHighestID][wpos][0] = f[0];
				Wp[WHighestID][wpos][1] = f[1];
				Wp[WHighestID][wpos][2] = f[2];
				Wp[WHighestID][wpos][3] = 0;
				Wp[WHighestID][paliwo] = 40.0;
				
				#if defined TESTINGOFF
				GivePlayerScore(playerid,-175000);
				#endif
				new labelstr[256];
				format(labelstr,256,"{ff661a}Wyj¹tkowy pojazd prywatny (/wpp)\nW³aœciciel: {FFFFFF}%s\n{ff661a}Paliwo: {FFFFFF}---/40 L",GetWppOwner(Wp[WHighestID][owner]));
				Wp[WHighestID][wlabel] = Create3DTextLabel(labelstr,0xFFFFFFFF,Wp[WHighestID][wpos][0],Wp[WHighestID][wpos][1],Wp[WHighestID][wpos][2], 35.0,0,0);
				Attach3DTextLabelToVehicle(Wp[WHighestID][wlabel], Wp[WHighestID][vehicle],0,0,0);
				
				new sstr[128];
				format(sstr,128,"%0.3f,%0.3f,%0.3f,%0.3f",Wp[WHighestID][wpos][0], Wp[WHighestID][wpos][1], Wp[WHighestID][wpos][2], Wp[WHighestID][wpos][3]);
				
				format(Qstr,256,"INSERT INTO `mreg_wpp`(`ID`, `owner`, `model`, `col1`, `col2`, `position`, `paliwo`) VALUES (NULL,%d, %d,%d,%d,'%s','%f')",Wp[WHighestID][owner], Wp[WHighestID][model], Wp[WHighestID][col1], Wp[WHighestID][col2],sstr, Wp[WHighestID][paliwo] );
				m_query(Qstr);
				SendClientMessage(playerid,COLOR_ERROR,"W³aœnie zakupi³eœ /wpp!");
				
				CreateWpVehicle(WHighestID);
			}
		}
	}
	return 1;
}

new selling;

Dialog:DIALOG_WPP(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0: {
				if(IsPlayerInAnyVehicle(playerid))return SendClientMessage(playerid,COLOR_ERROR,"Nie mo¿esz przywo³aæ wpp bêd¹c w pojeŸdzie");
				
				new Float:f[3];
				GetPlayerPos(playerid,f[0], f[1], f[2]);
				
				for(new x; x<WHighestID;x++)
				{
					if(Wp[x][owner] == pInfo[playerid][player_id])
						SetVehiclePos(Wp[x][vehicle], f[0]+2, f[1]+2, f[2]);
				}
			}
			case 1: {
				new suc;
				suc = 0;
				for(new x; x<WHighestID;x++)
				{
					if(IsPlayerInVehicle(playerid, Wp[x][vehicle]))
					{
						if(Wp[x][owner] == pInfo[playerid][player_id]) {
							new Float:tpos[4];
							GetVehiclePos(Wp[x][vehicle],tpos[0], tpos[1], tpos[2]);
							GetVehicleZAngle(Wp[x][vehicle], tpos[3]);
							new Qstr[256], sstr[128];
							format(sstr,128,"%0.3f,%0.3f,%0.3f,%0.3f",tpos[0], tpos[1], tpos[2], tpos[3] );
							format(Qstr,256,"UPDATE `mreg_wpp` SET `position`='%s' WHERE `owner` = %d",sstr,Wp[x][owner]);
							m_query(Qstr);
							SendClientMessage(playerid,COLOR_ERROR,"Twój pojazd zosta³ zaparkowany!");
							Wp[x][wpos][0] = tpos[0];
							Wp[x][wpos][1] = tpos[1];
							Wp[x][wpos][2] = tpos[2];
							Wp[x][wpos][3] = tpos[3];
							suc = 1;
						}
					} 
				}
				if(suc != 1) SendClientMessage(playerid,COLOR_ERROR,"Musisz byæ w pojeŸdzie!");
			}
			case 2: {
				new Float:f[3];
				
				for(new x; x<WHighestID;x++)
				{
					if(Wp[x][vehicle] == -1) {}
					if(Wp[x][owner] == pInfo[playerid][player_id])
						GetVehiclePos(Wp[x][vehicle],f[0], f[1], f[2]);
				}
				SetPlayerPos(playerid,f[0], f[1], f[2]);
			}
			case 3: { //sprzedaj
				for(new x; x <WHighestID; x++)
				{
					if(Wp[x][vehicle] == -1) {}
					if(Wp[x][owner] == pInfo[playerid][player_id])
					{
						switch(Wp[x][model])
						{
							case 1: { 
								selling = 33; 
								Dialog_Show(playerid,DIALOG_SPRZEDAJ,DIALOG_STYLE_MSGBOX,"Sprzedaj wpp","Czy na pewno chcesz sprzedaæ swój wpp za 1000 XP?","Sprzedaj","Anuluj");
							}
							case 2: {//hotknife
								selling = 12; 
								Dialog_Show(playerid,DIALOG_SPRZEDAJ,DIALOG_STYLE_MSGBOX,"Sprzedaj wpp","Czy na pewno chcesz sprzedaæ swój wpp za 50.000 XP?","Sprzedaj","Anuluj");	
							}
							case 3:  { //tampoa
								selling = 24; 
								Dialog_Show(playerid,DIALOG_SPRZEDAJ,DIALOG_STYLE_MSGBOX,"Sprzedaj wpp","Czy na pewno chcesz sprzedaæ swój wpp za 30.000 XP?","Sprzedaj","Anuluj");	
							}
						}
					}
				}
			}
		}
	}
	return 1;
}

Dialog:DIALOG_SPRZEDAJ(playerid, response, listitem, inputtext[])
{
	if(selling == 33 && response)
	{
		for(new x; x<WHighestID;x++)
		{
			if(Wp[x][vehicle] == -1) {}
			if(Wp[x][owner] == pInfo[playerid][player_id])
			{
				new Qstr[256];
				format(Qstr,256,"DELETE FROM `mreg_wpp` WHERE `owner`=%d",Wp[x][owner]);
				m_query(Qstr);
					
				DestroyVehicle(Wp[x][vehicle]);
				Delete3DTextLabel(Wp[x][wlabel]);
				Wp[x][vehicle_id] = -1;
				Wp[x][vehicle] = -1;
				Wp[x][owner] = -1;
				Wp[x][model] = -1;
				Wp[x][col1] = -1;
				Wp[x][col2] = -1;
				Wp[x][wpos][0] = -1;
				Wp[x][wpos][1] = -1;
				Wp[x][wpos][2] = -1;
				Wp[x][wpos][3] = -1;
				Wp[x][paliwo] = -1;
				for(new i; i < 10; i++)
				{
					DestroyObject(Wp[x][obj][i]);
				}
			}
		}
		#if defined TESTINGOFF
		GivePlayerScore(playerid,10000);
		#endif
		SendClientMessage(playerid,COLOR_ERROR,"Sprzedany!");
	}
	if(selling == 12 && response)//hotknife
	{
		for(new x; x<WHighestID;x++)
		{
			if(Wp[x][vehicle] == -1) {}
			if(Wp[x][owner] == pInfo[playerid][player_id])
			{
				new Qstr[256];
				format(Qstr,256,"DELETE FROM `mreg_wpp` WHERE `owner`=%d",Wp[x][owner]);
				m_query(Qstr);
					
				DestroyVehicle(Wp[x][vehicle]);
				Delete3DTextLabel(Wp[x][wlabel]);
				Wp[x][vehicle_id] = -1;
				Wp[x][vehicle] = -1;
				Wp[x][owner] = -1;
				Wp[x][model] = -1;
				Wp[x][col1] = -1;
				Wp[x][col2] = -1;
				Wp[x][wpos][0] = -1;
				Wp[x][wpos][1] = -1;
				Wp[x][wpos][2] = -1;
				Wp[x][wpos][3] = -1;
				Wp[x][paliwo] = -1;
				for(new i; i < 10; i++)
				{
						DestroyObject(Wp[x][obj][i]);
				}
			}
		}
		#if defined TESTINGOFF
		GivePlayerScore(playerid,50000);
		#endif
		SendClientMessage(playerid,COLOR_ERROR,"Sprzedany!");
	}
	
	if(selling == 24 && response)//tampa
	{
		for(new x; x<WHighestID;x++)
		{
			if(Wp[x][vehicle] == -1) {}
			if(Wp[x][owner] == pInfo[playerid][player_id])
			{
				new Qstr[256];
				format(Qstr,256,"DELETE FROM `mreg_wpp` WHERE `owner`=%d",Wp[x][owner]);
				m_query(Qstr);
					
				DestroyVehicle(Wp[x][vehicle]);
				Delete3DTextLabel(Wp[x][wlabel]);
				Wp[x][vehicle_id] = -1;
				Wp[x][vehicle] = -1;
				Wp[x][owner] = -1;
				Wp[x][model] = -1;
				Wp[x][col1] = -1;
				Wp[x][col2] = -1;
				Wp[x][wpos][0] = -1;
				Wp[x][wpos][1] = -1;
				Wp[x][wpos][2] = -1;
				Wp[x][wpos][3] = -1;
				Wp[x][paliwo] = -1;
				for(new i; i < 10; i++)
				{
						DestroyObject(Wp[x][obj][i]);
				}
			}
		}
		#if defined TESTINGOFF
		GivePlayerScore(playerid,3000);
		#endif
		SendClientMessage(playerid,COLOR_ERROR,"Sprzedany!");
	}



	return 1;
}
CMD:tankuj(playerid,params[])
{
	new bool:isonstat;
	isonstat = false;
	for(new x; x<MAX_STACJE;x++)
		if(IsPlayerInRangeOfPoint(playerid,4.0,Stacje[x][0],Stacje[x][1],Stacje[x][2])) isonstat = true;
	if(!isonstat)return SendClientMessage(playerid,COLOR_ERROR,"Nie jesteœ na ¿adnej stacji benzynowej!");
	
	new id;
	for(new x; x <WHighestID; x++)
		if(Wp[x][owner] == pInfo[playerid][player_id]) id = x;
	
	new Float:totank = 40.0 - Wp[id][paliwo];
	new Float:kosztperunit = 20.0;
	new topay = floatround(kosztperunit,floatround_ceil) * floatround(totank,floatround_ceil);
	GivePlayerScore(playerid,-topay);
	Wp[id][paliwo] = 40;

	new engine,lights,alarm,doors,bonnet,boot,objective;
	GetVehicleParamsEx(id,engine,lights,alarm,doors,bonnet,boot,objective);
	SetVehicleParamsEx(id,1,lights,alarm,doors,bonnet,boot,objective);
	
	SendClientMessage(playerid,0xFFFFFFFF,"Pojazd zatankowany!");
	
	return 1;
}

stock CreateGasStations()
{
	for(new x; x < MAX_STACJE; x++)
	{
		Create3DTextLabel("/tankuj",0xFFFFFFFF,Stacje[x][0],Stacje[x][1],Stacje[x][2],50.0,0,1  );
	}
	return 1;
}

stock CreateWpVehicle(x)
{
	new id;
	switch(Wp[x][model])
	{
		case 1: { // buffalo testowy
			Wp[x][vehicle] = CreateVehicle(402,Wp[x][wpos][0],Wp[x][wpos][1],Wp[x][wpos][2],Wp[x][wpos][3], Wp[x][col1], Wp[x][col2], -1, 0 );
			
			Attach3DTextLabelToVehicle(Wp[x][wlabel], Wp[x][vehicle],0,0,0);
			
			#if defined WPP_DEBUG
			printf("Stworzono pojazd model (%d) %d i id %d", x,GetVehicleModel(Wp[x][vehicle]), Wp[x][vehicle]);
			#endif
			//new obj[4];
			Wp[x][obj][1] = CreateObject(2064, 0,0,0,0,0,0,300);
			Wp[x][obj][2] = CreateObject(19307, 0,0,0,0,0,0,300);
			Wp[x][obj][3] = CreateObject(19307, 0,0,0,0,0,0,300);
			
			//AttachObjectToVehicle(obj[0], Wp[x][vehicle] , -0.095000, 1.564998, -0.344999, 0.000000, 0.000000, 0.000000); //Object Model: 759 | 
			AttachObjectToVehicle(Wp[x][obj][1], Wp[x][vehicle] , 0.014999, -0.454999, 1.259999, -6.030000, 0.000000, -180.900100); //Object Model: 2064 | 
			AttachObjectToVehicle(Wp[x][obj][2], Wp[x][vehicle] , -0.884999, -2.540010, 0.175000, -6.030000, 0.000000, -180.900100); //Object Model: 19307 | 
			AttachObjectToVehicle(Wp[x][obj][3], Wp[x][vehicle], 0.894999, -2.540010, 0.175000, 6.030000, 0.000000, -360.795959); //Object Model: 19307 | 
		}
		case 2: { // hotknife
			Wp[x][vehicle] = CreateVehicle(434,Wp[x][wpos][0],Wp[x][wpos][1],Wp[x][wpos][2],Wp[x][wpos][3], Wp[x][col1], Wp[x][col2], -1, 0 );
			#if defined WPP_DEBUG
			printf("Stworzono pojazd model (%d) %d i id %d", x,GetVehicleModel(Wp[x][vehicle]), Wp[x][vehicle]);
			#endif
			Attach3DTextLabelToVehicle(Wp[x][wlabel], Wp[x][vehicle],0,0,0);
			
			//new obj[9];
			Wp[x][obj][0] = CreateObject(1008, 0,0,0,0,0,0,300);
			Wp[x][obj][1] = CreateObject(1008, 0,0,0,0,0,0,300);
			Wp[x][obj][2] = CreateObject(1003, 0,0,0,0,0,0,300);
			Wp[x][obj][3] = CreateObject(1044, 0,0,0,0,0,0,300);
			Wp[x][obj][4] = CreateObject(1044, 0,0,0,0,0,0,300);
			Wp[x][obj][5] = CreateObject(1044, 0,0,0,0,0,0,300);
			Wp[x][obj][6] = CreateObject(1044, 0,0,0,0,0,0,300);
			Wp[x][obj][7] = CreateObject(1111, 0,0,0,0,0,0,300);
			Wp[x][obj][8] = CreateObject(1115, 0,0,0,0,0,0,300);
			
			AttachObjectToVehicle(Wp[x][obj][0], Wp[x][vehicle], 0.504999, -0.539999, 0.774999, 0.000000, -5.025000, -90.449951); //Object Model: 1008 |
			AttachObjectToVehicle(Wp[x][obj][1], Wp[x][vehicle], -0.504999, -0.539999, 0.774999, 0.000000, -5.025000, -90.449951); //Object Model: 1008 | 
			AttachObjectToVehicle(Wp[x][obj][2], Wp[x][vehicle], 0.000000, -1.079999, 0.774999, 0.000000, 0.000000, -0.000000); //Object Model: 1003 | 
			AttachObjectToVehicle(Wp[x][obj][3], Wp[x][vehicle], -0.619999, -1.954998, -0.314999, -30.149990, 0.000000, -0.000000); //Object Model: 1044 | 
			AttachObjectToVehicle(Wp[x][obj][4], Wp[x][vehicle], 0.614999, -1.954998, -0.314999, -30.149990, 0.000000, -0.000000); //Object Model: 1044 | 
			AttachObjectToVehicle(Wp[x][obj][5], Wp[x][vehicle], 0.404999, -1.954998, -0.314999, -30.149990, 0.000000, -0.000000); //Object Model: 1044 | 
			AttachObjectToVehicle(Wp[x][obj][6], Wp[x][vehicle], -0.404999, -1.954998, -0.314999, -30.149990, 0.000000, -0.000000); //Object Model: 1044 | 
			AttachObjectToVehicle(Wp[x][obj][7], Wp[x][vehicle], 0.000000, 0.224999, 0.664999, -30.149990, 0.000000, -0.000000); //Object Model: 1111 | 
			AttachObjectToVehicle(Wp[x][obj][8], Wp[x][vehicle], 0.000000, 0.519999, 0.095000, 28.139991, 0.000000, -0.000000); //Object Model: 1115 | 
				
		}
		case 3: { // tampa
			Wp[x][vehicle] = CreateVehicle(549,Wp[x][wpos][0],Wp[x][wpos][1],Wp[x][wpos][2],Wp[x][wpos][3], Wp[x][col1], Wp[x][col2], -1, 0 );
			#if defined WPP_DEBUG
			printf("Stworzono pojazd model (%d) %d i id %d", x,GetVehicleModel(Wp[x][vehicle]), Wp[x][vehicle]);
			#endif
			
			Attach3DTextLabelToVehicle(Wp[x][wlabel], Wp[x][vehicle],0,0,0);
			
			//new obj[7];
			Wp[x][obj][0] = CreateObject(1001, 0,0,0,0,0,0,300);
			Wp[x][obj][1] = CreateObject(1001, 0,0,0,0,0,0,300);
			Wp[x][obj][2] = CreateObject(1001, 0,0,0,0,0,0,300);
			Wp[x][obj][3] = CreateObject(1006, 0,0,0,0,0,0,300);
			Wp[x][obj][4] = CreateObject(1006, 0,0,0,0,0,0,300);
			Wp[x][obj][5] = CreateObject(1008, 0,0,0,0,0,0,300);
			Wp[x][obj][6] = CreateObject(1008, 0,0,0,0,0,0,300);
			
			AttachObjectToVehicle(Wp[x][obj][0], Wp[x][vehicle], 0.000000, -0.749999, 0.614999, 0.000000, 0.000000, 0.000000); //Object Model: 1001 |
			AttachObjectToVehicle(Wp[x][obj][1], Wp[x][vehicle], 0.000000, -2.535010, 0.214999, 0.000000, 0.000000, 0.000000); //Object Model: 1001 |
			AttachObjectToVehicle(Wp[x][obj][2], Wp[x][vehicle], 0.000000, -2.655013, 0.419999, 0.000000, 0.000000, 0.000000); //Object Model: 1001 |
			AttachObjectToVehicle(Wp[x][obj][3], Wp[x][vehicle], -0.199999, 1.904998, 0.294999, 0.000000, 0.000000, 0.000000); //Object Model: 1006 |
			AttachObjectToVehicle(Wp[x][obj][4], Wp[x][vehicle], 0.199999, 1.904998, 0.294999, 0.000000, 0.000000, 0.000000); //Object Model: 1006 |
			AttachObjectToVehicle(Wp[x][obj][5], Wp[x][vehicle], 0.559999, 1.904998, 0.294999, 0.000000, 0.000000, -90.449951); //Object Model: 1008 |
			AttachObjectToVehicle(Wp[x][obj][6], Wp[x][vehicle], -0.559999, 1.904998, 0.294999, 0.000000, 0.000000, -90.449951); //Object Model: 1008 |
		}
	}
	
	WHighestID += 1;
	return id;
}

stock LoadWppVehicles()
{
	new LoadString[256], Pos[64];
	m_query("SELECT ID, owner, model, col1, col2, paliwo, position FROM "prefix"_wpp");
	mysql_store_result();
	for(new x=0; x <mysql_num_rows(); x++)
	{
		mysql_fetch_row(LoadString,"|");
		sscanf(LoadString,"p<|>dddddfs[64]",Wp[WHighestID][vehicle_id], Wp[WHighestID][owner], Wp[WHighestID][model], Wp[WHighestID][col1], Wp[WHighestID][col2],Wp[WHighestID][paliwo], Pos);
		sscanf(Pos, "p<,>a<f>[4]", Wp[WHighestID][wpos]);
		
		#if defined WPP_DEBUG
			printf("CREATED %f %f %f %f ",Wp[WHighestID][wpos][0],Wp[WHighestID][wpos][1],Wp[WHighestID][wpos][2],Wp[WHighestID][wpos][3]);
		#endif
		
		#if defined WPP_DEBUG
		printf("[WPP LOAD]: %d - %d - %d - %d - %d - %f - %f - %f - %f",Wp[WHighestID][vehicle_id], Wp[WHighestID][owner], Wp[WHighestID][model], Wp[WHighestID][col1], Wp[WHighestID][col2], Wp[WHighestID][wpos][0],Wp[WHighestID][wpos][1],Wp[WHighestID][wpos][2],Wp[WHighestID][wpos][3]);
		#endif
		CreateWpVehicle(WHighestID);
		#if defined WPP_DEBUG
		printf("model%d", GetVehicleModel(Wp[x][vehicle]));
		#endif
		 
	}
	UpdateWpp();
	mysql_free_result();
	SetTimer("SetWppLabels",1000,0);
	SetTimer("UpdateWpp",UPDATEPALIWOTIME,1);
	return 1;
}
stock GetWppOwner(id)
{
	new OwnerName[60], qquery[256];
	format(qquery, 256,"SELECT nick FROM "prefix"_players WHERE id=%d",id);
	m_query(qquery);
	mysql_store_result();
	mysql_fetch_row(OwnerName);
	mysql_free_result();
	return OwnerName;
}

stock GetVehicleDriver(vehicleid)
{
	for(new i; i < 500; i++) 
	{
		if(!IsPlayerConnected(i)) continue;
		if(GetPlayerState(i) != PLAYER_STATE_DRIVER) continue;
		if(GetPlayerVehicleID(i) == vehicleid) 
		{
			return i;
		}
	}
	return -1;
}

forward UpdateWpp();
public UpdateWpp()
{
	for(new x; x < WHighestID; x++) {

		if(Wp[x][vehicle] == -1) continue;
		new driv = GetVehicleDriver(Wp[x][vehicle]);
		if(driv == -1) continue;
		if(pInfo[driv][player_id] == Wp[x][owner])
		{
			Wp[x][paliwo] -= 0.33;
		}
		if(Wp[x][paliwo] >= 0.1) {
			new labelstr[256];
			format(labelstr,256,"{ff661a}Wyj¹tkowy pojazd prywatny (/wpp)\nW³aœciciel: {FFFFFF}%s\n{ff661a}Paliwo: {FFFFFF}%.1f/40 L",GetWppOwner(Wp[x][owner]),Wp[x][paliwo]);
			Update3DTextLabelText(Wp[x][wlabel],0xFFFFFFFF,labelstr);
			new Qstr[256];
			format(Qstr,256,"UPDATE `mreg_wpp` SET `paliwo`='%f' WHERE `owner`=%d",Wp[x][paliwo],Wp[x][owner]);
			m_query(Qstr);
		} else {
			new labelstr[256];
			format(labelstr,256,"{ff661a}Wyj¹tkowy pojazd prywatny (/wpp)\nW³aœciciel: {FFFFFF}%s\n{ff661a}Paliwo: {FFFFFF}0.0/40 L",GetWppOwner(Wp[x][owner]));
			Update3DTextLabelText(Wp[x][wlabel],0xFFFFFFFF,labelstr);
		}
	}
	return 1;
}

forward SetWppLabels();
public SetWppLabels()
{
	for(new x; x < WHighestID; x++) {
		if(Wp[x][vehicle] == -1) {}
		new labelstr[256];
		format(labelstr,256,"{ff661a}WyjÄ…tkowy pojazd prywatny (/wpp)\nWÅ‚aÅ›ciciel: {FFFFFF}%s\n{ff661a}Paliwo: {FFFFFF}0.0/40 L",GetWppOwner(Wp[x][owner]));
		Wp[x][wlabel] = Create3DTextLabel(labelstr,0xFFFFFFFF,Wp[x][wpos][0],Wp[x][wpos][1],Wp[x][wpos][2], 35.0,0,0);
		Attach3DTextLabelToVehicle(Wp[x][wlabel], Wp[x][vehicle],0,0,0);
	}
	return 1;
}

stock wsp_init()
{
	WHighestID = 1;
	LoadWppVehicles();
	CreateGasStations();
	return 1;
}
