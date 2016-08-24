/*
          Private vehicles [1.0]
      (c) Copyright 2013-2014 by mrdrifter, Game
 
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/), Game
	  @date      : 16 grudnia 2013
	  @update    : 8 stycznia 2014
  
 */  
 
#define PRIV_CAR_PRICE 75
new string9[4200];
LoadPlayerVehicle(playerid)
{
	switch(pInfo[playerid][player_car_model])
	{
		case 400..611:
		{
			pInfo[playerid][player_car_have] = true;
			if(GetVehicleModel(gmData[player_vehicleid][playerid]))
			{
				DestroyVehicleEx(gmData[player_vehicleid][playerid]);
				gmData[player_vehicleid][playerid] = 0;
			}
			
			pInfo[playerid][player_car_have] = true;
			gmData[player_vehicleid][playerid] = CreateVehicle(pInfo[playerid][player_car_model], pInfo[playerid][player_car_pos][0], pInfo[playerid][player_car_pos][1], pInfo[playerid][player_car_pos][2], pInfo[playerid][player_car_pos][3], pInfo[playerid][player_car_color][0] == 0 ? (-1):(pInfo[playerid][player_car_color][0]), pInfo[playerid][player_car_color][1] == 0 ? (-1):(pInfo[playerid][player_car_color][1]), 90*90);
			 
			
			for(new i=0;i<15;i++)
				if(pInfo[playerid][player_car_component][i] > 0)
					AddVehicleComponent(gmData[player_vehicleid][playerid], pInfo[playerid][player_car_component][i]);
			
			if(pInfo[playerid][player_car_paintjob] > 0)
			{
				ChangeVehiclePaintjob(gmData[player_vehicleid][playerid], pInfo[playerid][player_car_paintjob]);
			}
			format(string2, sizeof(string2), "{E53E01}%s\n{E53E01}W³aœciciel: {FCAD43}%s\n{E53E01}Przebieg: {FCAD43}%.1f KM", (pInfo[playerid][player_car_date] < gettime())?("Zawieszony pojazd"):("Prywatny pojazd"), playerNick(playerid), pInfo[playerid][player_car_przebieg]);
			
			Update3DTextLabelText(gmData[player_vehicle][playerid], 0xFFFFFFFF, string2);
			Attach3DTextLabelToVehicle(gmData[player_vehicle][playerid] , gmData[player_vehicleid][playerid], 0.0, 0.0, 0.3);
			
			
			pInfo[playerid][player_car_lastload] = gettime() + 45;
		}
	}
	return 1;
}
stock DestroyPrivcar(playerid)
{
	if(gmData[player_vehicleid][playerid])
	{
		DestroyVehicleEx(gmData[player_vehicleid][playerid]);
		gmData[player_vehicleid][playerid] = 0;
	}	
	Update3DTextLabelText(gmData[player_vehicle][playerid], 0xFFFFFF00, "-");
 
}
Dialog:DIALOG_PLAYER_VEHICLE(playerid, response, listitem, inputtext[])
{
	if(response)
	{	
		switch(listitem)
		{
			case 0://Przywo³aj pojazd!
			{
				new Float:pos[4];
				
				GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
				GetPlayerFacingAngle(playerid, pos[3]);
				
				if(IsPlayerInAnyVehicle(playerid)) SetPlayerPos(playerid, pos[0] + 1.0, pos[1], pos[2]);
				
				SetVehiclePos(gmData[player_vehicleid][playerid], pos[0] - 1.0, pos[1], pos[2] + 1.0);
				SetVehicleZAngle(gmData[player_vehicleid][playerid], pos[3]);
				
				
				SendClientMessage(playerid, COLOR_INFO, ""chat" Przywo³a³eœ swój prywatny pojazd. ");
				return 1;
			}
			case 1: //Zmieñ kolor
			{
				
				string9[0] = EOS;
				
				for(new i;i<sizeof(VehicleColoursTableRGBA);i++)
					format(string9, sizeof(string9), "%s"chat" {%06x}Wybierz kolor\n", string9, VehicleColoursTableRGBA[i]>>>8);
				
				Dialog_Show(playerid, DIALOG_PCOLOR, DIALOG_STYLE_LIST, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Zmieñ Kolor (Step 1/2) •", string9, "Wybierz", "WyjdŸ");
				
			}
			case 2: Dialog_Show(playerid, DIALOG_EXTENSION_CAR, DIALOG_STYLE_INPUT, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Przed³u¿enie • ", "{F5DEB3}Podaj iloœæ dni do przed³u¿enia", "Przed³u¿", "Zamknij");
			case 3:
			{
				new Float:pos[4];
				
				GetVehiclePos(gmData[player_vehicleid][playerid], pos[0], pos[1], pos[2]);
				SetPlayerPos(playerid, pos[0] + 1.0, pos[1], pos[2]);
				
				SendClientMessage(playerid, COLOR_INFO, "Teleportowa³eœ siê pod swój prywatny pojazd. {F5DEB3}%d", gmData[player_vehicleid][playerid]);
				return 1;
			}
			case 4:
			{
				if(GetPlayerScore(playerid) < 1000) 
					return SendClientMessage(playerid, COLOR_INFO, "{FFFFFF} *{/b} Zmiana modelu kosztuje 1000 respektu. Aktualnie tylu nie posiadasz.");
				
				Dialog_Show(playerid, DIALOG_EDITCAR1, DIALOG_STYLE_LIST, "{D2691E}• •", "{FFFFFF}Czy chcesz przenieœæ przebieg aktualnego pojazdu do nowego?\n\nKoszt:\nGracz: 10.000 XP\nVIP: 2.000 XP ", "Tak", "Nie");
			}
		}
	}
	return 1;
}
Dialog:DIALOG_EDITCAR1(playerid, response, listitem, inputtext[])
{
	if(response)//tak
	{
		static buffs[4200];
		buffs[0] = EOS;
		for(new i;i < sizeof(VehicleNames);i++)
		{
			format(buffs, sizeof(buffs), "%s(%d) %s\n", buffs, i+400, VehicleNames[i]);
		}
		Dialog_Show(playerid, DIALOG_EDITCAR2, DIALOG_STYLE_LIST, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Wybierz model •", buffs, "Anuluj", "");
		
	} else {//nie
		static buffs[4200];
		buffs[0] = EOS;
		for(new i;i < sizeof(VehicleNames);i++)
		{
			format(buffs, sizeof(buffs), "%s(%d) %s\n", buffs, i+400, VehicleNames[i]);
		}
		Dialog_Show(playerid, DIALOG_EDITCAR, DIALOG_STYLE_LIST, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Wybierz model •", buffs, "Anuluj", "");
	}
	
	return 1;
}


Dialog:DIALOG_EDITCAR(playerid, response, listitem, inputtext[])
{
	if(!response) return 0;
	new car_id = listitem + 400;
	if(car_id < 400 || car_id > 611)
	{
						
		static buffs[4200];
		buffs[0] = EOS;
		for(new i;i < sizeof(VehicleNames);i++)
		{
			format(buffs, 4600, "%s(%d) %s\n", buffs, i+400, VehicleNames[i]);
		}
		return Dialog_Show(playerid, DIALOG_BUYCAR, DIALOG_STYLE_LIST, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Kup pojazd", buffs, "Anuluj", "");
	}
	if(IsBlockVehicle(car_id))
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Pojazd który wybra³eœ jest niedozwolony i dlatego go nie mo¿na go kupiæ.");
		new buffs[4600];
		for(new i;i < sizeof(VehicleNames);i++)
		{
			format(buffs, 4600, "%s(%d) %s\n", buffs, i+400, VehicleNames[i]);
		}
		return Dialog_Show(playerid, DIALOG_BUYCAR, DIALOG_STYLE_LIST, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Kup pojazd", buffs, "Anuluj", "");
	}
	pInfo[playerid][player_car_modelbuy] = car_id;
	
	
	new buffs[256];
	format(buffs, sizeof buffs, "{D2691E}Czy chcesz zmieniæ model pojazdu na  {F5DEB3}%s {D2691E}za 1000 respektu?\n\n{D2691E}UWAGA: Wraz z zmian¹ modelu pojazdu zostaje cofniêty przebieg.", VehicleNames[pInfo[playerid][player_car_modelbuy]-400]);
	Dialog_Show(playerid, DIALOG_EDITCARACCEPT, DIALOG_STYLE_MSGBOX, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Zmiana Pojazdu! •", buffs, "TAK", "Anuluj");
	
	return 1;
}

Dialog:DIALOG_EDITCAR2(playerid, response, listitem, inputtext[])
{
	if(!response) return 0;
	new car_id = listitem + 400;
	if(car_id < 400 || car_id > 611)
	{
						
		static buffs[4200];
		buffs[0] = EOS;
		for(new i;i < sizeof(VehicleNames);i++)
		{
			format(buffs, 4600, "%s(%d) %s\n", buffs, i+400, VehicleNames[i]);
		}
		return Dialog_Show(playerid, DIALOG_BUYCAR, DIALOG_STYLE_LIST, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Kup pojazd", buffs, "Anuluj", "");
	}
	if(IsBlockVehicle(car_id))
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Pojazd który wybra³eœ jest niedozwolony i dlatego go nie mo¿na go kupiæ.");
		new buffs[4600];
		for(new i;i < sizeof(VehicleNames);i++)
		{
			format(buffs, 4600, "%s(%d) %s\n", buffs, i+400, VehicleNames[i]);
		}
		return Dialog_Show(playerid, DIALOG_BUYCAR, DIALOG_STYLE_LIST, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Kup pojazd", buffs, "Anuluj", "");
	}
	pInfo[playerid][player_car_modelbuy] = car_id;
	
	
	new buffs[256];
	format(buffs, sizeof buffs, "{D2691E}Czy chcesz zmieniæ model pojazdu na  {F5DEB3}%s {D2691E}za 1000 respektu?\n\n{D2691E}UWAGA: Wraz z zmian¹ modelu pojazdu zostaje cofniêty przebieg.", VehicleNames[pInfo[playerid][player_car_modelbuy]-400]);
	Dialog_Show(playerid, DIALOG_EDITCARACCEPT2, DIALOG_STYLE_MSGBOX, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Zmiana Pojazdu! •", buffs, "TAK", "Anuluj");
	
	return 1;
}

Dialog:DIALOG_EDITCARACCEPT(playerid, response, listitem, inputtext[])
{
	if(!response) return 0;
	GivePlayerScore(playerid, -1000);
	pInfo[playerid][player_car_model] = pInfo[playerid][player_car_modelbuy];
	pInfo[playerid][player_car_przebieg] = 0.00;
	LoadPlayerVehicle(playerid);
	InfoBox(playerid, "{D2691E}Zmieni³eœ model prywatnego pojazdu");
	return 1;
	
}

Dialog:DIALOG_EDITCARACCEPT2(playerid, response, listitem, inputtext[])
{
	if(!response) return 0;
	GivePlayerScore(playerid, -1000);
	pInfo[playerid][player_car_model] = pInfo[playerid][player_car_modelbuy];
	LoadPlayerVehicle(playerid);
	InfoBox(playerid, "{D2691E}Zmieni³eœ model prywatnego pojazdu");
	return 1;
	
}
Dialog:DIALOG_PCOLOR(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	
	pInfo[playerid][player_car_color][0] = listitem + 128;
	
	ChangeVehicleColor(gmData[player_vehicleid][playerid], pInfo[playerid][player_car_color][0], pInfo[playerid][player_car_color][1]);
	
	
	string9[0] = EOS;
	
	for(new i;i<sizeof(VehicleColoursTableRGBA);i++)
		format(string9, sizeof(string9), "%s{%06x}Wybierz kolor\n", string9, VehicleColoursTableRGBA[i]>>>8);
	
	Dialog_Show(playerid, DIALOG_PCOLOR2, DIALOG_STYLE_LIST, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Zmieñ Kolor (Step 2/2)", string9, "Wybierz", "WyjdŸ");
	
	return 1;
}

Dialog:DIALOG_PCOLOR2(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	
	
	pInfo[playerid][player_car_color][1] = listitem + 128;
	ChangeVehicleColor(gmData[player_vehicleid][playerid], pInfo[playerid][player_car_color][0], pInfo[playerid][player_car_color][1]);
	
	
	InfoBox(playerid, "\n{E17100}Zmieni³eœ kolor pojazdu!\n");
	return 1;
}

Dialog:DIALOG_EXTENSION_CAR(playerid, response, listitem, inputtext[])
{
	if(!response) return 0;
	new days = strval(inputtext);
	if((3 > days) || (days > 30)) 
		return Dialog_Show(playerid, DIALOG_EXTENSION_CAR, DIALOG_STYLE_INPUT, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Przed³u¿enie {D2691E}» {CD853F}B³¹d", "Podaj iloœæ dni do przed³u¿enia\n\n\t{FF0000}Minimum 3 dni, maximum 30", "Przedló¿", "Zamknij");
	
	new score_ = (days * PRIV_CAR_PRICE);
	format(string2, sizeof(string2), "{DEB887}Czy na-pewno chcesz przed³u¿yæ pojazd o {F5DEB3}%d {DEB887}dni za {F5DEB3}%d {DEB887}respektu?", days, score_);
	
	if(score_ > GetPlayerScore(playerid)) 
		return InfoBox(playerid, "\n\n\t{DEB887}Nie masz tyle respektu aby kupiæ prywatny pojazd ("#PRIV_CAR_PRICE")\n\n{DEB887}Respekt mo¿esz zakupiæw portfelu CMD:/Portfelu b¹dŸ po prostu go zdob¹dŸ\n\n");
	
	pInfo[playerid][player_car_extension_days] = days;
	Dialog_Show(playerid, DIALOG_EXTENSION_CAR2, DIALOG_STYLE_MSGBOX, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Potwierdzenie", string2, "Przed³u¿", "Zamknij");
	
	return 1;
}
Dialog:DIALOG_EXTENSION_CAR2(playerid, response, listitem, inputtext[])
{
	if(!response) return 0;
	new score_ = (pInfo[playerid][player_car_extension_days] * PRIV_CAR_PRICE);
	if(score_ > GetPlayerScore(playerid)) 
		return InfoBox(playerid, "\n\n\t{DEB887}Nie masz tyle respektu aby kupiæ prywatny pojazd ("#PRIV_CAR_PRICE")\n\n{DEB887}Respekt mo¿esz zakupiæw portfelu CMD:/Portfelu b¹dŸ po prostu go zdob¹dŸ\n\n");
	if((3 > pInfo[playerid][player_car_extension_days]) || (pInfo[playerid][player_car_extension_days] > 30)) 
		return Dialog_Show(playerid, DIALOG_EXTENSION_CAR, DIALOG_STYLE_INPUT, "Prywatny Pojazd » Przed³u¿enie » b³¹d", "Podaj iloœæ dni do przed³u¿enia\n\n\t{FF0000}Minimum 3 dni, maximum 30", "Przed³u¿", "Zamknij");
	
	AddVehicleDate(playerid, pInfo[playerid][player_car_extension_days]);
	GivePlayerScore(playerid, -score_);
	new wazny_do[50];
	format(wazny_do, sizeof(wazny_do), "%s", DateFormat(pInfo[playerid][player_car_date]));
	
	format(string2, sizeof(string2), "{DEB887}Przed³u¿y³eœ swój Prywatny Pojazd:\n\n{F5DEB3}*\t{DEB887}Koszt: {F5DEB3}%d\n{F5DEB3}*\t{DEB887}Iloœæ dni: {F5DEB3}%d\n*\t{DEB887}Pojazd wa¿ny do: {F5DEB3}%s\n", score_, pInfo[playerid][player_car_extension_days], wazny_do);
	InfoBox(playerid, string2);
	return 1;
}
Dialog:DIALOG_CHANGEMODEL(playerid, response, listitem, inputtext[])
{
	if(response) return 1;
	new buffs[4600];
	for(new i;i < sizeof(VehicleNames);i++)
	{
		if(IsBlockVehicle(i + 400)) continue;
		format(buffs, 4600, "%s(%d) %s\n", buffs, i+400, VehicleNames[i]);
	}
	Dialog_Show(playerid, DIALOG_CHANGEMODEL, DIALOG_STYLE_LIST, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Lista pojazdów", buffs, "Anuluj", "");
	return 1;
}

Dialog:DIALOG_ACCEPTPC(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		//	new str[162];
		GetPlayerPos(playerid, pInfo[playerid][player_car_pos][0], pInfo[playerid][player_car_pos][1], pInfo[playerid][player_car_pos][2]);
		GetPlayerFacingAngle(playerid, pInfo[playerid][player_car_pos][3]);
		AddVehicleDate(playerid, 2);
		GivePlayerScore(playerid, -PRIV_CAR_PRICE);
		new wazny_do[50];
		format(wazny_do, sizeof(wazny_do), "%s", DateFormat(pInfo[playerid][player_car_date]));
		
		format(string2, sizeof(string2), "{DEB887}Gratulacje!\n{DEB887}Kupi³eœ swój Prywatny Pojazd:\n\n{F5DEB3}*\t{DEB887}Koszt: {F5DEB3}2000\n{F5DEB3}*\t{DEB887}Iloœæ dni: {F5DEB3}2\n{F5DEB3}*\t{DEB887}Pojazd wa¿dy do:{F5DEB3} %s\n\n", wazny_do);
		InfoBox(playerid, string2);
		
		pInfo[playerid][player_car_przebieg] = 0.0;
		
		LoadPlayerVehicle(playerid);
		
	}
	else
		return InfoBox(playerid, "{DEB887}Anulowano kupno Prywatnego Pojazdu");
		
	return 1;
}
Dialog:DIALOG_CARSPRIV(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0://KUP
		{
			if(PRIV_CAR_PRICE > GetPlayerScore(playerid)) 
				return InfoBox(playerid, "\n\n\t{DEB887}Nie masz tyle respektu aby kupiæ prywatny pojazd ("#PRIV_CAR_PRICE")\n\n{DEB887}Respekt mo¿esz zakupiæw portfelu CMD:/Portfelu b¹dŸ po prostu go zdob¹dŸ\n\n");
			new buffs[4600];
			for(new i;i < sizeof(VehicleNames);i++)
			{
				format(buffs, sizeof(buffs), "%s(%d) %s\n", buffs, i+400, VehicleNames[i]);
			}
			Dialog_Show(playerid, DIALOG_BUYCAR, DIALOG_STYLE_LIST, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Kup pojazd", buffs, "Anuluj", "");
			
		}
		case 1://LISTA
		{
			new buffs[3072], d;
			for(new i;i < sizeof(VehicleNames);i++)
			{
				format(buffs, 3072, "%s %s (id %d) ", buffs, VehicleNames[i], i+400);
				
				if(d++ >= 5) {
					strcat(buffs, "\n");
					d=0;
				}
			}
			InfoBox(playerid, buffs);
			return 1;
		}
		
	}
	return 1;
}
Dialog:DIALOG_BUYCAR(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(PRIV_CAR_PRICE > GetPlayerScore(playerid)) 
		return InfoBox(playerid, "\n\n\t{DEB887}Nie masz tyle respektu aby kupiæ prywatny pojazd ("#PRIV_CAR_PRICE")\n\n{DEB887}Respekt mo¿esz zakupiæw portfelu CMD:/Portfelu b¹dŸ po prostu go zdob¹dŸ\n\n");

	new car_id = listitem + 400;
	if(car_id < 400 || car_id > 611)
	{
		new buffs[4600];
		for(new i;i < sizeof(VehicleNames);i++)
		{
			format(buffs, 4600, "%s(%d) %s\n", buffs, i+400, VehicleNames[i]);
		}
		return Dialog_Show(playerid, DIALOG_BUYCAR, DIALOG_STYLE_LIST, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Kup pojazd", buffs, "Anuluj", "");
	}
	if(IsBlockVehicle(car_id))
	{
		SendClientMessage(playerid, COLOR_ERROR, "Nie mo¿na kupiæ tego pojazdu...");
		new buffs[4600];
		for(new i;i < sizeof(VehicleNames);i++)
		{
			format(buffs, 4600, "%s(%d) %s\n", buffs, i+400, VehicleNames[i]);
		}
		return Dialog_Show(playerid, DIALOG_BUYCAR, DIALOG_STYLE_LIST, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Kup pojazd", buffs, "Anuluj", "");
	}
	pInfo[playerid][player_car_model] = car_id;
	

	new buffs[128];
	format(buffs, sizeof buffs, "{DEB887}Czy chcesz kupiæ prywatny pojazd o nazwie: {F5DEB3}%s {DEB887}za {F5DEB3}"#PRIV_CAR_PRICE" {DEB887}Score na {F5DEB3}2 {DEB887}Dni?", VehicleNames[pInfo[playerid][player_car_model]-400]);
	Dialog_Show(playerid, DIALOG_ACCEPTPC, DIALOG_STYLE_MSGBOX, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Kupno pojazdu!", buffs, "TAK", "Anuluj");
	return 1;
}
CMD:vehiclelist(playerid, params[])
{
	new buffs[3072], d;
	for(new i;i < sizeof(VehicleNames);i++)
	{
		format(buffs, 3072, "%s %s (id %d) ", buffs, VehicleNames[i], i+400);
				
		if(d++ >= 5) {
			strcat(buffs, "\n");
			d=0;
		}
	}
	InfoBox(playerid, buffs);
	return 1;
}
CMD:privcar(playerid, paramrs[])
{
	if(!pInfo[playerid][player_register])
		return SendClientMessage(playerid, COLOR_ERROR, " Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do tej komendy.");
	
	if(PRIV_CAR_PRICE > GetPlayerScore(playerid) && pInfo[playerid][player_car_have] == false) 
		return SendClientMessage(playerid, COLOR_INFO, "{FFFFFF} *{/b} Aby kupiæ Prywatny Pojazd musisz mieæ "#PRIV_CAR_PRICE" respektu");
	
	if(pInfo[playerid][player_car_date] < gettime() && pInfo[playerid][player_car_have] == true)
		return Dialog_Show(playerid, DIALOG_EXTENSION_CAR, DIALOG_STYLE_INPUT, "{D2691E}• {CD853F}Prywatny Pojazd{D2691E} » {CD853F}Przed³u¿enie ", "{DEB887}Twój prywatny pojazd straci³ wa¿noœæ.\n{DEB887}Aby nim zarz¹dzaæ musisz go przed³o¿yæ. \n{DEB887}Podaj iloœæ dni do przed³u¿enia", "Przed³u¿", "Zamknij");
	
	if(pInfo[playerid][player_car_have] == false)
		return Dialog_Show(playerid, DIALOG_CARSPRIV, DIALOG_STYLE_LIST, "{D2691E}• {CD853F}Prywatny Pojazd {D2691E}» {CD853F}Kupno Pojazdu", "{DEB887}Kup prywatny pojazd\n{F5DEB3}Lista pojazdów z ich ID", "Wybierz", "WyjdŸ;");
	
	Dialog_Show(playerid, DIALOG_PLAYER_VEHICLE, DIALOG_STYLE_LIST, "{D2691E}• {CD853F}Prywatny Pojazd ", "{F5DEB3}Przywo³aj pojazd\n{DEB887}Zmien Kolor\n{F5DEB3}Przed³u¿\n{DEB887}Teleportuj do pojazdu\n{F5DEB3}Zmieñ Model", "Wybierz", "WyjdŸ;");
	return 1;
}

stock IsBlockVehicle(modelid)
{
	switch(modelid)
	{
	 	case 406..408, 425, 427, 428, 430, 431..433, 435, 437, 441, 443, 446, 447..450, 452..454, 464, 459, 460, 465, 472, 473,  485, 486, 493, 497,  499, 501, 512, 513, 514, 515, 520, 523, 524, 530, 531, 532, 537, 538, 539, 544, 548, 553, 563, 564, 569, 570..574, 577, 578, 590..601, 606..611: return true;
	}
	return false;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	if(pInfo[playerid][player_car_have] == true && gmData[player_vehicleid][playerid] == vehicleid)
	{
		pInfo[playerid][player_car_paintjob] = paintjobid;
	}
	return 1;
}
stock AddVehicleDate(playerid, days)
{
	new add = 0;
	if(pInfo[playerid][player_car_date] > gettime()){
		add = (pInfo[playerid][player_car_date] - gettime());
	}
	if(add > 0)
		pInfo[playerid][player_car_date] = (gettime() + ((add) + (60*60*24*days)));
	else
		pInfo[playerid][player_car_date] = (gettime() + (60*60*24*days));
	
	return 1;
}
stock Vehicle_PrivClear(vehicleid)
{
	for(new fi;fi<MAX_PLAYERS;fi++)
	{
		if(pInfo[fi][player_car_have] == false) continue;
		
		if(gmData[player_vehicleid][fi] == vehicleid)
		{
			pInfo[fi][player_car_have] = false;
			gmData[player_vehicleid][fi] = -1;
			Update3DTextLabelText(gmData[player_vehicle][fi], 0xFFFFFF00, "-");
		}
	}
	return vehicleid;
}
stock Vehicle_IsPriv(vehicleid)
{
	foreach(new c : Player)
	{
		if(pInfo[c][player_car_have] == false) continue;
		
		if(gmData[player_vehicleid][c] == vehicleid)
		{
			return 1;
		}
	}
	return 0;
}

stock Vehicle_IsWp(vehicleid)
{
	for(new x; x < WHighestID; x++)
	{
		if(Wp[x][vehicle] == vehicleid)
			return 1;
	}
	return 0;
}

public OnVehicleDeath(vehicleid, killerid)
{
	WyjebDoczepianeObiekty(vehicleid);
	
	foreach(new fi : Player)
	{
		if(pInfo[fi][player_car_have] == false) continue;
		
		if(gmData[player_vehicleid][fi] == vehicleid)
		{
			SetVehiclePos(gmData[player_vehicleid][fi], pInfo[fi][player_car_pos][0], pInfo[fi][player_car_pos][1], pInfo[fi][player_car_pos][2]);
			SetPlayerFacingAngle(gmData[player_vehicleid][fi], pInfo[fi][player_car_pos][3]);
			break;
		}
	}
	return 1;
}
