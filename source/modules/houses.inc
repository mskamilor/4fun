/*
          Houses [2.2]
      (c) Copyright 2013-2014 by mrdrifter
 
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
	  @date      : 16 grudnia 2013
	  @update    : 3 stycznia 2014
  
 */  
 
 
#define MAX_HOUSE 1500
#define MAX_HOUSE_INT 25

#define     SELECT_MODE_EDIT    (0)
#define     SELECT_MODE_SELL    (1)

enum house_
{
	sql_id, 
	h_name[80], 
	h_price, 
	h_price_portfel,
	h_owner_name[30], 
	h_owner_id, 
	Float:h_pos[3], 
	h_int, 
	h_furnitures,
	h_vw,
	bool:h_owned, 
	bool:l_tenants, 
	l_tenants_price, 
	Text3D:label, 
	pickup, 
	paid_to, 
	mapicon, 
	h_password[50], 
	//bool:h_veh, 
	h_v_id
}
new House[MAX_HOUSE][house_];
 
new load_houses;
enum THouseInterior//HouseInterior
{
	InteriorName[50], 
	InteriorID, 
	PriceInterior, 
	PriceInteriorPortfel,
	Float:IntX, 
	Float:IntY, 
	Float:IntZ, 
	bool:int_
}

enum    e_furniture
{
	ef_SQLID,
	ef_HouseID,
	ef_ArrayID,
	Float: furnitureX,
	Float: furnitureY,
	Float: furnitureZ,
	Float: furnitureRX,
	Float: furnitureRY,
	Float: furnitureRZ
};

enum    e_furnituredata
{
	ef_modelID,
	ef_name[32],
	ef_Price
};

new HouseFurnitures[][e_furnituredata] =
{
   // ID Obiektu, Nazwa, Cena EXP
   {19787, "Telewizor LCD 42 cale", 750},
   {19786, "Telewizor LCD 60 cali", 1000},
   {2627, "Bie¿nia", 300},
   {1736, "Poro¿e", 100},
   {2630, "Rowerek", 200},
   {2226, "BumBox", 100},
   {1841, "Ma³y g³oœnik", 50},
   {2231, "G³oœnik", 100},
   {2631, "Mata do cwiczen", 30},
   {1985, "Worek bokserski", 90},
   {14820, "DJ'ka", 100},
   {2358, "Skrzynia z amunicj¹", 80},
   {2164, "Rega³", 30},
   {2964, "Billard", 300},
   {2229, "Du¿y g³oœnik", 200},
   {2514, "Kibel", 150},
   {1208, "Pralka", 300},
   {1828, "Dywan z tygryska", 100},
   {1778, "Wiaderko z mopem", 50},
   {1701, "Du¿e ³o¿e ma³¿eñskie", 500},
   {1795, "£ó¿ko z materacem", 250},
   {2134, "Szafka", 100},
   {1741, "Komoda", 150},
   {1762, "Fotel", 100},
   {3111, "Plan budynku", 50},
   {2894, "Ksi¹¿ka", 100},
   {2277, "Obraz kota", 100},
   {1753, "Skórzana sofa", 1200},
   {1754, "Skórzany fotel", 350},
   {1703, "Zwyk³a sofa", 600},
   {1255, "Drewniany le¿ak", 50},
   {19581, "Patelnia", 30},
   {19584, "Rondel", 30},
   {19609, "Perkusja", 500},
   {19590, "Miecz", 50},
   {19525, "Tort weselny", 100},
   {1742, "Rega³ na ksi¹¿ki", 800},
   {1518, "Telewizor kineskopowy", 250},
   {1775, "Automat z fant¹", 350},
   {1809, "Kino domowe (bez g³oœników)", 100},
   {1806, "Krzes³o obrotowe", 100},
   {1810, "Krzes³o", 50},
   {1814, "£awa", 120},
   {1815, "Okr¹g³a ³awa", 150},
   {1817, "£awa ze szk³em", 180},
   {1821, "Rega³ na buty", 100},
   {1829, "Sejf", 600},
   {1946, "Pi³ka do kosza", 30},
   {1950, "Butelka denaturatu", 50},
   {2001, "Drzewko doniczkowe", 70},
   {2011, "Palma doniczkowa", 80},
   {2023, "Du¿a lampa nocna", 120},
   {2025, "Du¿a szafa na ubrania", 300},
   {2047, "Plakat na œciane", 20},
   {2064, "Zabytkowa armata", 400},
   {2070, "Lampka nocna", 20},
   {2100, "Kino domowe", 200},
   {2133, "Komoda", 100},
   {2135, "Kuchnia (zestaw 1/5)", 200},
   {2136, "Kuchnia (zestaw 2/5)", 180},
   {2137, "Kuchnia (zestaw 3/5)", 150},
   {2138, "Kuchnia zmywarka (zestaw 4/5)", 180},
   {2139, "Kuchnia dodatkowa szafka (5/5)", 100},
   {2149, "Mikrofalówka", 100},
   {2194, "Kaktus ozdobny", 10},
   {2195, "Kwiat doniczkowy", 30},
   {2244, "Drewniana doniczka z kwiatkiem", 20},
   {2247, "Szklana doniczka z kwiatkami", 20},
   {2228, "£opata", 20},
   {2254, "Obraz taxi 4", 30},
   {2255, "Obraz +18", 50},
   {2256, "Obraz hawaje", 20},
   {2294, "Kuchenka z okapem", 110},
   {2313, "Rega³ pod TV", 60},
   {2314, "Reag³ pod TV kwadratowy", 80},
   {2526, "Wanna", 130},
   {2527, "Prysznic", 100},
   {2571, "Skórzane dwa fotele z ³aw¹", 700},
   {2600, "Luneta", 140},
   {2613, "Kosz", 30}
};
	
new HouseInterior[MAX_HOUSE_INT][THouseInterior]; 
new globalInterior,
	Iterator:hInteriors<MAX_HOUSE_INT>,
	Iterator:domy<MAX_HOUSE>;
	
LoadHouses(h_id = -1)
{
	m_query("update "prefix"_houses set owned = 0, owner = 0 where paid_to2 < now()");
	new ParameterValue[128];
	new czas = GetTickCount();
	 
	if(h_id == -1)
		mysql_query("SELECT h . * , IF(owner !=0, p.nick, 'Brak') owner_nick, IFNULL(DATEDIFF(paid_to2, NOW()), -1) timeend FROM "prefix"_houses h LEFT JOIN "prefix"_players p ON p.id = h.owner limit "#MAX_HOUSE"");
	else 
		m_query("SELECT h . * , IF(owner !=0, p.nick, 'Brak') owner_nick, IFNULL(DATEDIFF(paid_to2, NOW()), -1) timeend FROM "prefix"_houses h LEFT JOIN "prefix"_players p ON p.id = h.owner where h.id = %d", House[h_id][sql_id]);
	mysql_store_result();

	new id;
	Iter_Clear(domy); 
	
	for(new i;i<mysql_num_rows();i++)
	{
		if(i > MAX_HOUSE - 2) break;
		
		mysql_data_seek(i);
		mysql_fetch_row_data();
		
		mysql_fetch_field("id", ParameterValue);
		id = strval(ParameterValue);
	
		Iter_Add(domy, i);
		House[i][sql_id] = id;
		
		mysql_fetch_field("timeend", ParameterValue);
		
		House[i][paid_to] = strval(ParameterValue);		 
		House[i][h_price_portfel] = HouseInterior[House[i][h_int]][PriceInteriorPortfel]; //strval(ParameterValue);
	
		mysql_fetch_field("name", House[i][h_name]);	

		mysql_fetch_field("inte", ParameterValue);
		House[i][h_int] = strval(ParameterValue);
		
		mysql_fetch_field("owner_nick", House[i][h_owner_name]);
		
		mysql_fetch_field("password", House[i][h_password]);
		
		mysql_fetch_field("owner", ParameterValue);
		House[i][h_owner_id] = strval(ParameterValue);
		
		mysql_fetch_field("furnitures", ParameterValue);
		House[i][h_furnitures] = strval(ParameterValue);
		 
		 
		  
		mysql_fetch_field("owned", ParameterValue);
		House[i][h_owned] = (strval(ParameterValue) == 1) ? (true):(false);
		 
		mysql_fetch_field("tenants", ParameterValue);
		House[i][l_tenants] = (strval(ParameterValue) == 1) ? (true):(false);
		 
		 
		mysql_fetch_field("house_cord", ParameterValue);
		sscanf(ParameterValue, "p<,>a<f>[3]", House[i][h_pos]);
		
		House[i][h_price] = HouseInterior[House[i][h_int]][PriceInterior];	 
		 
		House[i][h_vw] = House[i][sql_id] + 675 + MAX_HOUSE;
		
		if(House[i][paid_to] <= 0)
		{
			House[i][h_owned] = false;
			House[i][h_owner_id] = 0;
		}
		DestroyDynamicPickup(House[i][pickup]);
		DestroyDynamic3DTextLabel(Text3D:House[i][label]);
		
		House[i][label] = CreateDynamic3DTextLabel("Dom", 0xFFFFFFFF, House[i][h_pos][0], House[i][h_pos][1], House[i][h_pos][2], 10.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,-1,-1, 100.0);
		House[i][pickup] = CreateDynamicPickup((House[i][h_owned] == true)? (1272):(1273), 23, House[i][h_pos][0], House[i][h_pos][1], House[i][h_pos][2],0);
		House[i][mapicon] = CreateDynamicMapIcon(House[i][h_pos][0], House[i][h_pos][1], House[i][h_pos][2], (House[i][h_owned] == true)? (32):(31), 0xFFFFFFFF, 0, -1, -1, 200.0);

		House_UpdateLabel(i);
		load_houses++;
		 
	}
	
	printf("[load] wczytanych domków:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	mysql_free_result();

	load_houses++;
	
	LoadHousesFurnitures();
	return 1;
	
}

LoadHousesInteriors()
{
	new ParameterValue[50];
	new czas = GetTickCount();
	new intID;
	globalInterior = 0;
	mysql_query("SELECT * FROM "prefix"_houses_interiors");
	mysql_store_result();
	for(new i;i<mysql_num_rows();i++)
	{
		mysql_data_seek(i);//globalInterior
		mysql_fetch_row_data();
		intID++;
		
		mysql_fetch_field("id", ParameterValue);
		intID = strval(ParameterValue);
		
		Iter_Add(hInteriors, intID);
		globalInterior++;
		
		mysql_fetch_field("name", HouseInterior[intID][InteriorName]);	
		
		mysql_fetch_field("cost", ParameterValue);
		HouseInterior[intID][PriceInterior] = strval(ParameterValue);	
		
		mysql_fetch_field("intid", ParameterValue);
		HouseInterior[intID][InteriorID] = strval(ParameterValue);
		 
		HouseInterior[intID][int_] = true;
		
		mysql_fetch_field("cost_portfel", ParameterValue); 
		HouseInterior[intID][PriceInteriorPortfel] = strval(ParameterValue);
		
		mysql_fetch_field("pos", ParameterValue);
		 
		if(sscanf(ParameterValue, "p<,>fff", HouseInterior[intID][IntX], HouseInterior[intID][IntY], HouseInterior[intID][IntZ])) 
			printf("[HousesInteriors] B³¹d rozdzielania pozycji interioru {'id' = '%d', 'pozycje' = '%s'}", intID, ParameterValue);
		 
	}
	printf("[load] wczytanych interiorów:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	mysql_free_result();
	return 1;
	
}


stock LoadHousesFurnitures()
{
	new hid, id, czas = GetTickCount();
	new data[e_furniture];

	mysql_query("SELECT * FROM "prefix"_houses_furnitures");
	mysql_store_result();
	for(new i;i<mysql_num_rows();i++)
	{
		mysql_data_seek(i);
		mysql_fetch_row_data();
		
       	data[ef_SQLID] = mysql_fetch_field_int("id");
       	data[ef_HouseID] = mysql_fetch_field_int("ef_HouseID");
       	data[ef_ArrayID] = mysql_fetch_field_int("FurnitureID");
       	data[furnitureX] = mysql_fetch_field_float("FurnitureX");
       	data[furnitureY] = mysql_fetch_field_float("FurnitureY");
        data[furnitureZ] = mysql_fetch_field_float("FurnitureZ");
        data[furnitureRX] = mysql_fetch_field_float("FurnitureRX");
        data[furnitureRY] = mysql_fetch_field_float("FurnitureRY");
        data[furnitureRZ] = mysql_fetch_field_float("FurnitureRZ");
		
		hid = GetHouseID(data[ef_HouseID]);
		
		//printf("tworzenie %d dla domu %d", 	data[ef_SQLID], hid);
		if( !hid )
			continue;
		
		id = CreateDynamicObject(
   			HouseFurnitures[ data[ef_ArrayID] ][ef_modelID],
       		data[furnitureX], data[furnitureY], data[furnitureZ],
          	data[furnitureRX], data[furnitureRY], data[furnitureRZ],
			House[hid][h_vw], HouseInterior[House[hid][h_int]][InteriorID]
		);
		//printf("stworzono id %d dla domu %d", 	id, hid);

		Streamer_SetArrayData(STREAMER_TYPE_OBJECT, id, E_STREAMER_EXTRA_ID, data);
 	}
//	Streamer_GetArrayData(STREAMER_TYPE_OBJECT, id, E_STREAMER_EXTRA_ID, data); //przed aktualizacja streamera to nie dzialalo ;o
	//printf("lastHouse %d", data[ef_HouseID]);
	
	printf("[load] wczytanych obiektów domowych:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
   	mysql_free_result();

   	
	return 1;
}
stock save_house(i) 
{
	m_query("update "prefix"_houses set password='%s', furnitures=%d, inte=%d, name='%s' where id=%d", House[i][h_password], House[i][h_furnitures], House[i][h_int], House[i][h_name], House[i][sql_id]);
	House_UpdateLabel(i);
}
stock House_UpdateIcon(i)
{
	DestroyDynamicPickup(House[i][pickup]);
	House[i][pickup] = CreateDynamicPickup((House[i][h_owned] == true)? (1272):(1273), 23, House[i][h_pos][0], House[i][h_pos][1], House[i][h_pos][2]);
		
	DestroyDynamicMapIcon(House[i][mapicon]);
	House[i][mapicon] = CreateDynamicMapIcon(House[i][h_pos][0], House[i][h_pos][1], House[i][h_pos][2], (House[i][h_owned] == true)? (32):(31), 0xFFFFFFFF, -1, -1, -1, 200.0);
}
stock House_UpdateLabel(i)
{
	if(!HouseInterior[House[i][h_int]][int_])
	{
		House[i][h_int] = Iter_Random(hInteriors);
		return House_UpdateLabel(i);
	}
	if(!House[i][h_owned])
		format(string2, sizeof(string2), "(Dom do kupna)\nKoszt domu: %d exp\nInterior: %s\nUID: %d", House[i][h_price], HouseInterior[House[i][h_int]][InteriorName], House[i][sql_id]);
	
	else 
		format(string2, sizeof(string2), "%s\nW³aœciel %s\nKoszt domu: %d exp\nInterior: %s\nUID: %d ", House[i][h_name], House[i][h_owner_name], House[i][h_price], HouseInterior[House[i][h_int]][InteriorName], House[i][sql_id]);
	
	UpdateDynamic3DTextLabelText(House[i][label], 0xFFFFFFFF, string2);
	
	return 1;
}
 
stock hOnPlayerPickUpDynamicPickup(playerid, pickupid)
{
	foreach(new i : domy)
	{
		if(House[i][pickup] == pickupid)
		{
			if(pInfo[playerid][player_lasthouse_dialogshow] > gettime()) return 1;
			
			pInfo[playerid][player_action_houseid] = i;
			
			if(House[i][h_owned] == false)
			{
				Dialog_Show(playerid, HOUSE_CLICKED, DIALOG_STYLE_LIST, "Panel domu", "Zobacz\nKup", "Wybierz", "Anuluj");
				pInfo[playerid][player_action_houseid] = i;
			}
			else 
			if(pInfo[playerid][player_house] == House[i][sql_id])
			{
				HousePanel(playerid);
			}
			else 
			if(strcmp(House[i][h_password], "brak", true, 5))
			{
				Dialog_Show(playerid, HOUSE_LOGIN, DIALOG_STYLE_PASSWORD, "Panel domu", "WprowadŸ has³o do domu!", "Wybierz", "Anuluj");
			}
			else 
			{	
				Dialog_Show(playerid, HOUSE_CLICKED, DIALOG_STYLE_LIST, "Panel domu", "WejdŸ", "Wybierz", "Anuluj");
			}
			pInfo[playerid][player_lasthouse_dialogshow] = gettime() + 11;
			break;
		}
		 
	}
	return 1;
}
stock buy_house(playerid, i)
{
	if(pInfo[playerid][player_house] > 0) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Niestety mo¿esz posiadaæ tylko jeden dom!");
	
	if(!pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz siê {b}zarejestrowaæ{/b} aby kupiæ dom.");
		return 1;
	}
	if(House[i][h_owned] == false)
	{
		if(GetPlayerScore(playerid) < House[i][h_price]) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Nie, masz nawet na op³acenie jednego dnia domu!");
 
 

		m_query("update "prefix"_houses set paid_to2 = IF(paid_to2 >NOW(), paid_to2 , NOW())+INTERVAL 2 DAY, owned = 1, owner = %d where id = %d ", pInfo[playerid][player_id], House[i][sql_id]);
		
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Gratulacjê! kupi³eœ w³asny dom jest on wa¿ny przez 2 dni! potem musisz go przed³o¿yæ lub zostanie usuniêty.");
		
		GivePlayerScore(playerid, -House[i][h_price]);
		
		pInfo[playerid][player_house] = House[i][sql_id];
		pInfo[playerid][player_thouse] = i;
		House[i][paid_to] = 2;
		House[i][h_owned] = true;
		House[i][h_owner_id] = pInfo[playerid][player_id];
		
		format(House[i][h_owner_name], 30, "%s", playerNick(playerid));
		House_UpdateLabel(i);
		achievement(playerid, 12);
		//LoadHouses();
		SavePlayer(playerid);
		House_UpdateIcon(i);
	}
	return 1;
}
CMD:wyjdz(playerid, params[])
{

	if(pInfo[playerid][player_ishouse] == false) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Nie jesteœ w ¿adnym domu!");
	
	exitPlayerHouse(playerid, pInfo[playerid][player_action_houseid]);
	SendClientMessage(playerid, COLOR_GREEN, " Opuœci³eœ dom!");
	pInfo[playerid][player_lasthouse_dialogshow] = gettime() + 2;
	return 1;
}

CMD:domtp(playerid, params[])
{

	if(pInfo[playerid][player_house] == 0) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Nie posiadasz domu!");
	
	exitPlayerHouse(playerid, pInfo[playerid][player_thouse]);
	SendClientMessage(playerid, COLOR_GREEN, " Teleportowa³eœ siê do domu!");
	return 1;
}

CMD:dompanel(playerid, params[])
{

	if(pInfo[playerid][player_house] == 0) 
		return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Nie posiadasz domu!");
	
	if(pInfo[playerid][player_ishouse] && pInfo[playerid][player_action_houseid] != pInfo[playerid][player_thouse])
		return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Nie mo¿esz u¿yæ tej komendy bêd¹c w nie swoim domu!");
	
	pInfo[playerid][player_action_houseid] = pInfo[playerid][player_thouse];

	HousePanel(playerid);
	return 1;
}
 
 
CMD:nh(playerid, params[])
{

	RankAdmin(playerid, R_VICEHEADADMIN);
	
	string2[0] = EOS;
	
	for(new i, x;i<MAX_HOUSE_INT;i++)
	{
		if(!HouseInterior[i][int_]) continue;
		pInfo[playerid][player_dialog_data][x] = i;
		format(string2, sizeof(string2), "%s%s\n", string2, HouseInterior[i][InteriorName]);
		x++;
	}	
	Dialog_Show(playerid, DIALOG_NH_INTERIOR, DIALOG_STYLE_LIST, "Panel Domu -› Dodaj dom -› Interior", string2, "Dodaj", "Anuluj");
	
	pInfo[playerid][player_lasthouse_dialogshow] = gettime() + 20;
	
	SendClientMessage(playerid, COLOR_GREEN, "{FF0000}"chat"{/b} Rozpocz¹³eœ tworzenie domu wybierz interior domu. Pamiêtaj po klikniêciu dodaj dom zostanie stworzony.");
	return 1;
}
Dialog:DIALOG_NH_INTERIOR(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(inputtext[0])
		{
			new c = pInfo[playerid][player_dialog_data][listitem];
			 
			new Float:pos[3];
			GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
			
			m_query("INSERT INTO `"prefix"_houses` (`id`, `owner`, `name`, `price`, `inte`, `owned`, `tenants`, `house_cord`, `paid_to`, `houseautor`, `houseautorid`) VALUES (NULL, '0', 'Brak Nazwy :(', '%d', '%d', '0', '1', '%f,%f,%f', '0', '%s', '%d');", HouseInterior[c][PriceInterior], c, pos[0], pos[1], pos[2], pInfo[playerid][player_name], pInfo[playerid][player_id]);
				
			LoadHouses();
	
			SendClientMessage(playerid, COLOR_GREEN, ""chat" Dom zosta³ dodany. :)");
		}
	}
	return 1;
}

CMD:nowydomint(playerid, params[])
{

	RankAdmin(playerid, R_HEADADMIN);
	new nazwa[50], cena, int; 
	if(sscanf(params, "s[50]d", nazwa, cena)) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} U¿yj: /nowydom [nazwa] [cena]");

	int = GetPlayerInterior(playerid);
	new Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	m_query("INSERT INTO `"prefix"_houses_Interiors` (`name`, `pos`, `cost`, `intid`) VALUES ('%s', '%f,%f,%f', '%d', '%d');", nazwa, pos[0], pos[1], pos[2], cena, int);
	
	LoadHousesInteriors();
	SendClientMessage(playerid, COLOR_GREEN, " Poprawnie doda³eœ nowy interior do domu!");
	return 1;
}

CMD:usundom(playerid, params[])
{

	RankAdmin(playerid, R_VICEHEADADMIN);
	
	new bool:deleted = false;
	
	foreach(new houseid : domy)
	{
		if(IsPlayerInRangeOfPoint(playerid, 1.0, House[houseid][h_pos][0], House[houseid][h_pos][1] , House[houseid][h_pos][2]))
		{
			m_query("delete from "prefix"_houses where id=%d", House[houseid][sql_id]);
			
			DestroyDynamic3DTextLabel(House[houseid][label]);
			DestroyDynamicMapIcon(House[houseid][mapicon]);
			DestroyDynamicPickup(House[houseid][pickup]);
			Enum_Clean(House[houseid], house_);
			
			Iter_Remove(domy, houseid);
			 
			deleted = true;
			break;
		}
	}
		
	SendClientMessage(playerid, COLOR_GREEN, ""chat" %s", deleted == true ? ("Dom zosta³ usuniêty pomyœlnie."):("Musisz byæ w PickUpie domu") );
	return 1;
}
 
stock HousePanel(playerid)
{
	if(pInfo[playerid][player_ishouse] && pInfo[playerid][player_action_houseid] == pInfo[playerid][player_thouse])
	{
		Dialog_Show(playerid, HOUSE_PANEL, DIALOG_STYLE_LIST, "Panel domu", "WejdŸ\nPrzed³u¿ wa¿noœæ\nZmieñ nazwê\nZmieñ has³o\nSprzedaj Dom\n{CC0000}Przedló¿ za pieni¹dze z /Portfel\n{00ff01}Meble", "Wybierz", "Anuluj");
	}
	else 
	{
		Dialog_Show(playerid, HOUSE_PANEL, DIALOG_STYLE_LIST, "Panel domu", "WejdŸ\nPrzed³u¿ wa¿noœæ\nZmieñ nazwê\nZmieñ has³o\nSprzedaj Dom\n{CC0000}Przedló¿ za pieni¹dze z /Portfel", "Wybierz", "Anuluj");
	}
}

stock setPlayerHouse(playerid, houseid) 
{
	//new xh_int = House[houseid][h_int];
	SetPlayerPos(playerid, HouseInterior[ House[houseid][h_int] ][IntX], HouseInterior[House[houseid][h_int]][IntY], HouseInterior[House[houseid][h_int]][IntZ]);
	SetPlayerInterior(playerid, HouseInterior[House[houseid][h_int]][InteriorID]);
	SetPlayerVirtualWorld(playerid, House[houseid][h_vw]);
	pInfo[playerid][player_ishouse] = true;
	pInfo[playerid][player_action_houseid] = houseid;
}
 
stock exitPlayerHouse(playerid, houseid)
{
	SetPlayerPos(playerid, House[houseid][h_pos][0], House[houseid][h_pos][1] , House[houseid][h_pos][2]);
	SetPlayerInterior(playerid, 0); 
	SetPlayerVirtualWorld(playerid, 0);

	pInfo[playerid][player_action_houseid] = 0; 
	pInfo[playerid][player_ishouse] = false;


}


Dialog:HOUSE_CLICKED(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(pInfo[playerid][player_action_houseid] == 0) return SendClientMessage(playerid, COLOR_GREEN, " Wyst¹pi³ b³¹d spróbuj ponownie");
		
		if(!listitem)
		{
			SendClientMessage(playerid, COLOR_GREEN, " Jesteœ w domu! aby wyjœæ u¿yj {b}/Wyjdz{/b}");
			setPlayerHouse(playerid, pInfo[playerid][player_action_houseid]);
		}
		else if(House[pInfo[playerid][player_action_houseid]][h_owned] == false)
		{
			buy_house(playerid, pInfo[playerid][player_action_houseid]);
		}
	}
	return 1;
}
Dialog:HOUSE_PANEL(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0: 
			{
				SendClientMessage(playerid, COLOR_GREEN, " Jesteœ w domu! aby wyjœæ u¿yj {b}/Wyjdz{/b}");
				setPlayerHouse(playerid, pInfo[playerid][player_action_houseid]);
			}
			case 1:
			{
				format(string2, sizeof(string2), "Wprowaæ iloœæ dni do przed³u¿enia\nTwój dom aktualnie jest wa¿ny %d dni a koszt przed³u¿enia\nJednego dnia to %d respektu", House[pInfo[playerid][player_thouse]][paid_to], House[pInfo[playerid][player_thouse]][h_price]);
				Dialog_Show(playerid, DIALOG_PANEL_NEXT_TIME, DIALOG_STYLE_INPUT, "Panel Domu -› Przed³u¿anie ", string2, "Przed³u¿", "Anuluj");
			}
			case 2:
			{
				
				format(string2, sizeof(string2), "Zmieñ nazwê domu! \nAktualna nazwa: %s", House[pInfo[playerid][player_thouse]][h_name]);
				Dialog_Show(playerid, DIALOG_HOUSETIME, DIALOG_STYLE_INPUT, "Panel Domu -› Zmieñ nazwê ", string2, "Zmieñ", "Anuluj");
			}
			case 3:
			{
				format(string2, sizeof(string2), "Zmieñ has³o domu! \nAktualne has³o: %s\n{FF0000}Uwaga:\n{CC0000} jeœli chcesz usun¹æ to has³o pozostaw\nTo pole puste lub wpisz 'brak'!", House[pInfo[playerid][player_thouse]][h_password]);
				Dialog_Show(playerid, DIALOG_HOUSEPASSWORD, DIALOG_STYLE_INPUT, "Panel Domu -› Zmieñ has³o ", string2, "Zmieñ", "Anuluj");
			}
			
			case 4:
			{
				new zwrot = (House[pInfo[playerid][player_thouse]][h_price] * House[pInfo[playerid][player_thouse]][paid_to]) * 5;
				
				format(string2, sizeof(string2), "Czy chcesz sprzedaæ dom za %d$?", zwrot);
				Dialog_Show(playerid, DIALOG_PANEL_SELL, DIALOG_STYLE_INPUT, "Panel Domu -› Sprzedawanie ", string2, "Sprzedaj", "Anuluj");
			}
			case 5:
			{
				format(string2, sizeof(string2), "Wprowaæ iloœæ dni do przed³u¿enia\nTwój dom aktualnie jest wa¿ny %d dni a koszt przed³u¿enia\nKoszt przed³u¿enia to %d\n\n{FF0000}Uwaga: przy przed³u¿eniu kosztu dostajesz 3x tyle czyli jeœli\nPrzed³u¿ysz wa¿noœæ o 5 dni dostaniesz 15!", House[pInfo[playerid][player_thouse]][paid_to], House[pInfo[playerid][player_thouse]][h_price_portfel]);
				Dialog_Show(playerid, DIALOG_PAT_TIME_PORTFEL, DIALOG_STYLE_INPUT, "Panel Domu -› Przed³u¿anie ", string2, "Przed³u¿", "Anuluj");
			}
			case 6:
			{
				
				if(!pInfo[playerid][player_ishouse]) return SendClientMessage(playerid, 0xE74C3CFF, "Musisz byæ w domu by zarz¹dzaæ meblami!");
				
				Dialog_Show(playerid, DIALOG_HOUSE_FURNITURE, DIALOG_STYLE_LIST, "Panel Domu -› Meble ", "Kup meble\nEdytuj Meble\nUsuñ Meble", "Wybierz", "Anuluj");
				 
			}
			
		}
	}
	return 1;
}

 
 
Dialog:DIALOG_PANEL_SELL(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new zwrot = (House[pInfo[playerid][player_thouse]][h_price] * (House[pInfo[playerid][player_thouse]][paid_to])) * 5;
		GivePlayerMoney(playerid, zwrot);
		
		SendClientMessage(playerid, COLOR_GREEN, " "chat" Pomyœlnie sprzeda³eœ swój dom za {b}%d${/b}", zwrot);
		new houseid = pInfo[playerid][player_thouse];
		
		pInfo[playerid][player_house] = 0;
		House[houseid][h_owned] = false;
		House[houseid][paid_to] = 0;
		House_UpdateIcon( houseid );
		House_UpdateLabel( houseid );
	}
	return 1;
}

stock House_OnPlayerLoad(playerid)
{
	if(!pInfo[playerid][player_house])
	{
		foreach(new i : domy)
			if(House[i][h_owner_id] == pInfo[playerid][player_id])
				pInfo[playerid][player_house] = House[i][sql_id];
	}	
	if(pInfo[playerid][player_house])
	{
		new houseid = pInfo[playerid][player_house];
		
		pInfo[playerid][player_thouse] = GetHouseID(houseid);
		houseid = pInfo[playerid][player_thouse];
		
		if(House[houseid][paid_to] <= 0 || pInfo[playerid][player_id] != House[houseid][h_owner_id])
		{
			SendClientMessage(playerid, COLOR_ERROR, ""chat" Twój dom straci³ czynsz i zosta³eœ(aœ) z niego wyeksmitowany(a)");
			
			pInfo[playerid][player_house] = 0;
			if(pInfo[playerid][player_id] != House[houseid][h_owner_id] && House[houseid][paid_to] > gettime()) return 1;
			
			House[houseid][paid_to] = 0;
			House[houseid][h_owned] = false;
			return 1;
		}
		 
		SendClientMessage(playerid, -1, ""chat" Twój dom jest op³acony na {008ae6}%d dni", House[houseid][paid_to]);
	}
	return 1;
}
Dialog:DIALOG_PANEL_NEXT_TIME(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(!IsNumeric(inputtext))
		{
			format(string2, sizeof(string2), "WprowadŸ iloœæ dni do przed³u¿enia\nTwój dom aktualnie jest wa¿ny %d dni a koszt przed³u¿enia\nJednego dnia to %d respektu", House[pInfo[playerid][player_thouse]][paid_to], House[pInfo[playerid][player_thouse]][h_price]);
			Dialog_Show(playerid, DIALOG_PANEL_NEXT_TIME, DIALOG_STYLE_INPUT, "PANEL domu -› Przed³u¿anie ", string2, "Przed³u¿", "Anuluj");
			return SendClientMessage(playerid, COLOR_GREEN, " Dom mo¿na przed³u¿yæ minimum o {b}2{/b} dni!");
		}
		new time = strval(inputtext);
		
		if(time < 2) 
		{
			format(string2, sizeof(string2), "WprowadŸ iloœæ dni do przed³u¿enia\nTwój dom aktualnie jest wa¿ny %d dni a koszt przed³u¿enia\nJednego dnia to %d respektu", House[pInfo[playerid][player_thouse]][paid_to], House[pInfo[playerid][player_thouse]][h_price]);
			Dialog_Show(playerid, DIALOG_PANEL_NEXT_TIME, DIALOG_STYLE_INPUT, "Panel Domu -› Przed³u¿anie ", string2, "Przed³u¿", "Anuluj");
			
			SendClientMessage(playerid, COLOR_GREEN, " Dom mo¿na przed³u¿yæ minimum o {b}2{/b} dni!");
			return 1;
		}
		if(time > 30) 
		{
			format(string2, sizeof(string2), "WprowadŸ iloœæ dni do przed³u¿enia\nTwój dom aktualnie jest wa¿ny %d dni a koszt przed³u¿enia\nJednego dnia to %d respektu", House[pInfo[playerid][player_thouse]][paid_to], House[pInfo[playerid][player_thouse]][h_price]);
			Dialog_Show(playerid, DIALOG_PANEL_NEXT_TIME, DIALOG_STYLE_INPUT, "Panel Domu -› Przed³u¿anie ", string2, "Przed³u¿", "Anuluj");
			
			SendClientMessage(playerid, COLOR_GREEN, " Dom mo¿na przed³u¿yæ maximum o {b}30{/b} dni!");
			return 1;
		}
		if(pInfo[playerid][player_house] == 0)
		{
			return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Nie posiadasz domu!");
		}
		new koszt = House[pInfo[playerid][player_thouse]][h_price] * time;
		
		if(GetPlayerScore(playerid) < koszt)
		{
			format(string2, sizeof(string2), "WprowadŸ iloœæ dni do przed³u¿enia\nTwój dom aktualnie jest wa¿ny %d dni a koszt przed³u¿enia\nJednego dnia to %d respektu", House[pInfo[playerid][player_thouse]][paid_to], House[pInfo[playerid][player_thouse]][h_price]);
			Dialog_Show(playerid, DIALOG_PANEL_NEXT_TIME, DIALOG_STYLE_INPUT, "Panel Domu -› Przed³u¿anie ", string2, "Przed³u¿", "Anuluj");
			return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Masz za ma³o respektu. Dobij trochê b¹dŸ kup w {b}/Portfel{/b} !");
		}
		
 		format(string2, sizeof(string2), "update "prefix"_houses set paid_to2 = IF(paid_to2>NOW(), paid_to2, NOW())+INTERVAL %d DAY where id=%d ", time, House[pInfo[playerid][player_thouse]][sql_id]);
		mysql_query(string2);
		
 
		House[pInfo[playerid][player_thouse]][paid_to] += time;
		GivePlayerScore(playerid, -koszt, "przed³o¿enie domu");
		
		
		SendClientMessage(playerid, COLOR_GREEN, " Przed³o¿y³eœ wa¿noœæ domu. Jest on teraz wa¿ny jeszcze %d dni", House[pInfo[playerid][player_thouse]][paid_to]);
		 
	}
	return 1;
	
}

Dialog:DIALOG_PAT_TIME_PORTFEL(playerid, response, listitem, inputtext[])
{
	if(response != 00754) return InfoBox(playerid, "Opcja zablokowana :)");
	if(response)
	{
		
		if(!IsNumeric(inputtext))
		{
			format(string2, sizeof(string2), "Wprowaæ iloœæ dni do przed³u¿enia\nTwój dom aktualnie jest wa¿ny %d dni a koszt przed³u¿enia\nKoszt przed³u¿enia to %d\n\n{FF0000}Uwaga: przy przed³u¿eniu kosztu dostajesz 3x tyle czyli jeœli\nPrzed³u¿ysz wa¿noœæ o 5 dni dostaniesz 15!", House[pInfo[playerid][player_thouse]][paid_to], House[pInfo[playerid][player_thouse]][h_price_portfel]);
			Dialog_Show(playerid, DIALOG_PANEL_NEXT_TIME, DIALOG_STYLE_INPUT, "PANEL domu -› Przed³u¿anie ", string2, "Przed³u¿", "Anuluj");
			return SendClientMessage(playerid, COLOR_GREEN, " Dom mo¿na przed³u¿yæ minimum o {b}2{/b} dni!");
		}
		new time = strval(inputtext) * 3;
		
		if(time < 2) 
		{
			format(string2, sizeof(string2), "Wprowaæ iloœæ dni do przed³u¿enia\nTwój dom aktualnie jest wa¿ny %d dni a koszt przed³u¿enia\nKoszt przed³u¿enia to %d\n\n{FF0000}Uwaga: przy przed³u¿eniu kosztu dostajesz 3x tyle czyli jeœli\nPrzed³u¿ysz wa¿noœæ o 5 dni dostaniesz 15!", House[pInfo[playerid][player_thouse]][paid_to], House[pInfo[playerid][player_thouse]][h_price_portfel]);
			Dialog_Show(playerid, DIALOG_PANEL_NEXT_TIME, DIALOG_STYLE_INPUT, "Panel Domu -› Przed³u¿anie ", string2, "Przed³u¿", "Anuluj");
			
			SendClientMessage(playerid, COLOR_GREEN, " Dom mo¿na przed³u¿yæ minimum o {b}2{/b} dni!");
			return 1;
		}
		if(time > 30) 
		{
			format(string2, sizeof(string2), "Wprowaæ iloœæ dni do przed³u¿enia\nTwój dom aktualnie jest wa¿ny %d dni a koszt przed³u¿enia\nKoszt przed³u¿enia to %d\n\n{FF0000}Uwaga: przy przed³u¿eniu kosztu dostajesz 3x tyle czyli jeœli\nPrzed³u¿ysz wa¿noœæ o 5 dni dostaniesz 15!", House[pInfo[playerid][player_thouse]][paid_to], House[pInfo[playerid][player_thouse]][h_price_portfel]);
			Dialog_Show(playerid, DIALOG_PANEL_NEXT_TIME, DIALOG_STYLE_INPUT, "Panel Domu -› Przed³u¿anie ", string2, "Przed³u¿", "Anuluj");
			
			SendClientMessage(playerid, COLOR_GREEN, " Dom mo¿na przed³u¿yæ maximum o {b}30{/b} dni!");
			return 1;
		}
		if(pInfo[playerid][player_thouse] == 0)
		{
			return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Nie posiadasz domu!");
		}
		new koszt = House[pInfo[playerid][player_thouse]][h_price_portfel] * time;
		
	 
		if(koszt > pInfo[playerid][player_portfel])
		{
			format(string2, sizeof(string2), "Wprowaæ iloœæ dni do przed³u¿enia\nTwój dom aktualnie jest wa¿ny %d dni a koszt przed³u¿enia\nKoszt przed³u¿enia to %d\n\n{FF0000}Uwaga: przy przed³u¿eniu kosztu dostajesz 3x tyle czyli jeœli\nPrzed³u¿ysz wa¿noœæ o 5 dni dostaniesz 15!", House[pInfo[playerid][player_thouse]][paid_to], House[pInfo[playerid][player_thouse]][h_price_portfel]);
			Dialog_Show(playerid, DIALOG_PANEL_NEXT_TIME, DIALOG_STYLE_INPUT, "Panel Domu -› Przed³u¿anie ", string2, "Przed³u¿", "Anuluj");
			return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Masz za ma³o kasy kup w {b}/Portfel{/b} !");
		}
		if(0 == pInfo[playerid][player_portfel])
		{
			format(string2, sizeof(string2), "Wprowaæ iloœæ dni do przed³u¿enia\nTwój dom aktualnie jest wa¿ny %d dni a koszt przed³u¿enia\nKoszt przed³u¿enia to %d\n\n{FF0000}Uwaga: przy przed³u¿eniu kosztu dostajesz 3x tyle czyli jeœli\nPrzed³u¿ysz wa¿noœæ o 5 dni dostaniesz 15!", House[pInfo[playerid][player_thouse]][paid_to], House[pInfo[playerid][player_thouse]][h_price_portfel]);
			Dialog_Show(playerid, DIALOG_PANEL_NEXT_TIME, DIALOG_STYLE_INPUT, "Panel Domu -› Przed³u¿anie ", string2, "Przed³u¿", "Anuluj");
			return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Masz za ma³o kasy kup w {b}/Portfel{/b} !");
		}
		
 		format(string2, sizeof(string2), "update "prefix"_houses set paid_to2 = IF(paid_to2>NOW(), paid_to2, NOW())+INTERVAL %d DAY where id=%d ", time, House[GetHouseID(pInfo[playerid][player_thouse])][sql_id]);
		mysql_query(string2);
		
 
		House[pInfo[playerid][player_thouse]][paid_to] += time;
		GivePlayerPortfel(playerid, (-koszt));
		
		
		SendClientMessage(playerid, COLOR_GREEN, " Przed³o¿y³eœ wa¿noœæ domu. Jest on teraz wa¿ny jeszcze %d dni", House[pInfo[playerid][player_thouse]][paid_to]);
		 
	}
	return 1;
	
}
/* 
stock UnixToDay(t)
{
	new days = floatround(((t - gettime()) / 86400));
	if(days < 0) days = 0;
	return days;
}*/
Dialog:DIALOG_HOUSETIME(playerid, response, listitem, inputtext[])
{
	printf("[PAWN] %d %d %d [%s]", playerid, response, listitem, inputtext);
	if(response)
	{
		if(strlen(inputtext) < 3 || strlen(inputtext) > 20)
		{
			format(string2, sizeof(string2), "Zmieñ nazwê domu! \nAktualna nazwa: %s->1", House[pInfo[playerid][player_thouse]][h_name]);
			Dialog_Show(playerid, DIALOG_HOUSETIME, DIALOG_STYLE_INPUT, "Panel Domu -› Zmieñ nazwê ", string2, "Zmieñ", "Anuluj");
			return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Podaj nazwê domu!");
		}
		new escape[50];
		if(!escape[0]) escape = "-";
		mysql_real_escape_string(inputtext, escape);
		
		if(!escape[0]) escape = "-";
		format(House[pInfo[playerid][player_thouse]][h_name], 20, "%s", escape);
		SendClientMessage(playerid, COLOR_GREEN, " Zmieni³eœ nazwê domu!");
		save_house(pInfo[playerid][player_thouse]);
	}
	return 1;
}
Dialog:DIALOG_HOUSEPASSWORD(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(isnull(inputtext))
		{
			format(House[pInfo[playerid][player_thouse]][h_password], 40, "%s", "brak");
			save_house(pInfo[playerid][player_thouse]);
			return SendClientMessage(playerid, COLOR_GREEN, " Usun¹³eœ has³o do twojego domu. Od tej pory ka¿dy do niego mo¿e wejœæ");
		}
		if(!strcmp(inputtext, "brak", true, 5))
		{
			format(House[pInfo[playerid][player_thouse]][h_password], 40, "%s", "brak");
			save_house(pInfo[playerid][player_thouse]);
			return SendClientMessage(playerid, COLOR_GREEN, " Usun¹³eœ has³o do twojego domu. Od tej pory ka¿dy do niego mo¿e wejœæ");
		}
		
		if(strlen(inputtext) < 3 || strlen(inputtext) > 40) 
		{
			format(string2, sizeof(string2), "Zmieñ has³o domu! \nAktualne has³o: %s\n{FF0000}Uwaga:\n{CC0000} jeœli chcesz usun¹æ to has³o pozostaw\nTo pole puste lub wpisz 'brak'!", House[pInfo[playerid][player_thouse]][h_password]);
			Dialog_Show(playerid, DIALOG_HOUSEPASSWORD, DIALOG_STYLE_INPUT, "Panel Domu -› Zmieñ has³o ", string2, "Zmieñ", "Anuluj");
			return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Has³o mo¿e mieæ minimum {b}3{/b} znaki a maximum {b}40{/b}");
		}
		new escape[50];
		mysql_real_escape_string(inputtext, escape);
		format(House[pInfo[playerid][player_thouse]][h_password], 40, "%s", escape);
		SendClientMessage(playerid, COLOR_GREEN, " Zmieni³eœ has³o domu! nowa nazwa {b}%s{/b}", escape);
		save_house(pInfo[playerid][player_thouse]);
	
	}
	return 1;
	
}
Dialog:HOUSE_LOGIN(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(pInfo[playerid][player_action_houseid] == 0) return SendClientMessage(playerid, COLOR_GREEN, " Wyst¹pi³ b³¹d, spróbuj ponownie");
		if(!strlen(inputtext)) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Poda³eœ b³êdne has³o");
		if(strcmp(House[pInfo[playerid][player_action_houseid]][h_password], inputtext)  != 0) return SendClientMessage(playerid, COLOR_ERROR, "{FF0000} *{/b} Poda³eœ b³êdne has³o");
		
		SendClientMessage(playerid, COLOR_GREEN, " Jesteœ w domu! aby wyjœæ u¿yj {b}/Wyjdz{/b}");
		setPlayerHouse(playerid, pInfo[playerid][player_action_houseid]);
	}
	return 1;
}
 

stock GetHouseUID(hid)
{
	if(!(0 <= hid <= MAX_HOUSE)) return 0;
	
	return House[hid][sql_id];
}


stock GetHouseID(hid)
{
	foreach(new i : domy)
		if(House[i][sql_id] == hid)
			return i;
		
	return 0;
}

Dialog:DIALOG_HOUSE_FURNITURE(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				new list[2500];
				format(list, sizeof(list), "#\tNazwa\tCena\n");
				for(new i; i < sizeof(HouseFurnitures); ++i)
				{
					format(list, sizeof(list), "%s%d\t%s\t%d Respektu\n", list, i+1, HouseFurnitures[i][ef_name], HouseFurnitures[i][ef_Price]);
				}

				Dialog_Show(playerid, DIALOG_H_FR_BUY, DIALOG_STYLE_TABLIST_HEADERS, "Panel Domu › Meble › Kup", list, "Kup", "Anuluj");
			}
			case 1:
			{
				pInfo[playerid][player_dialog_data_ex][1] = SELECT_MODE_EDIT;
				SelectObject(playerid);
			}
			case 2:
			{
				pInfo[playerid][player_dialog_data_ex][1] = SELECT_MODE_SELL;
				SelectObject(playerid);
			}
		}
	}
	return 1;
}

Dialog:DIALOG_H_FR_BUY(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new id = pInfo[playerid][player_thouse];
		
		if(!(0 <= listitem <= sizeof(HouseFurnitures)))
		{
			DialogFunc:DIALOG_HOUSE_FURNITURE(playerid, 1, 0, #EOS);
			return SendClientMessage(playerid, 0xE74C3CFF, "Nie mo¿esz wybraæ tego obiektu");
		}
		
		if(House[id][h_furnitures] > 35)
		{
			DialogFunc:DIALOG_HOUSE_FURNITURE(playerid, 1, 0, #EOS);
			return SendClientMessage(playerid, 0xE74C3CFF, "Limit mebli wynosi 35 obiektów! usuñ zbêdne meble i dopiero dodaj kolejne.");
		}
		if(HouseFurnitures[listitem][ef_Price] > GetPlayerScore(playerid)) 
		{
			DialogFunc:DIALOG_HOUSE_FURNITURE(playerid, 1, 0, #EOS);
			return SendClientMessage(playerid, 0xE74C3CFF, "Nie masz tyle respektu by kupiæ ten mebel");
		}
		
		GivePlayerScore(playerid, -HouseFurnitures[listitem][ef_Price]);
		 
		new Float: x, Float: y, Float: z;
		GetPlayerPos(playerid, x, y, z);
        GetXYInFrontOfPlayer(playerid, x, y, 3.0);
		
		House[id][h_furnitures]++;
		
		m_query("INSERT INTO "prefix"_houses_furnitures SET ef_HouseID=%d, FurnitureID=%d, FurnitureX=%f, FurnitureY=%f, FurnitureZ=%f", GetHouseUID(id), listitem, x, y, z);

		 
        new objectid = CreateDynamicObject(HouseFurnitures[listitem][ef_modelID], x, y, z, 0.0, 0.0, 0.0, House[id][h_vw], HouseInterior[House[id][h_int]][InteriorID]);
	
		new data[e_furniture];
        data[ef_SQLID] = mysql_insert_id();
		data[ef_HouseID] = pInfo[playerid][player_house];
        data[ef_ArrayID] = listitem;
		data[furnitureX] = x;
		data[furnitureY] = y;
		data[furnitureZ] = z;
		data[furnitureRX] = 0.0;
		data[furnitureRY] = 0.0;
		data[furnitureRZ] = 0.0;

		Streamer_SetArrayData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID, data);
		EditDynamicObject(playerid, objectid);
		
		save_house(id);
	}
	return 1;
}


Dialog:DIALOG_H_FR_SELL(playerid, response, listitem, inputtext[])
{
	new objectid = pInfo[playerid][player_dialog_data_ex][0], data[e_furniture];
	Streamer_GetArrayData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID, data);
	if(data[ef_HouseID] != pInfo[playerid][player_house]) return 0;

	if(response)
	{
		GivePlayerScore(playerid, (HouseFurnitures[ data[ef_ArrayID] ][ef_Price]/2)/2);
		m_query("DELETE FROM "prefix"_houses_furnitures WHERE id=%d;", data[ef_SQLID]);
	
		DestroyDynamicObject(objectid); 
		
		new id = GetHouseID(data[ef_HouseID]);
		House[id][h_furnitures]--;
		save_house(id);
		SendClientMessage(playerid, COLOR_INFO2, "Usun¹³eœ obiekt (mebel) {b}%s{/b} zwróciliœmy Ci za niego {b}%d{/b} respektu", HouseFurnitures[ data[ef_ArrayID] ][ef_name], (HouseFurnitures[ data[ef_ArrayID] ][ef_Price]/2)/2);
	}
	else
		SendClientMessage(playerid, COLOR_INFO2, "Anulowa³eœ usuwanie obiektu {b}%s{/b}.", HouseFurnitures[ data[ef_ArrayID] ][ef_name]);

	DialogFunc:HOUSE_PANEL(playerid, 1, 6, #EOS);

	return 1;
}

public OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float: x, Float: y, Float: z)
{
	switch(pInfo[playerid][player_dialog_data_ex][1])
	{
	    case SELECT_MODE_EDIT: EditDynamicObject(playerid, objectid);
	    case SELECT_MODE_SELL:
	    {
	        CancelEdit(playerid);
			new data[e_furniture];
			
			pInfo[playerid][player_dialog_data_ex][0] = objectid;
			Streamer_GetArrayData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID, data);
			if(data[ef_HouseID] != pInfo[playerid][player_house]) return 0;
			
			Dialog_Show(playerid, DIALOG_H_FR_SELL, DIALOG_STYLE_MSGBOX, "Panel Domu › Meble › Usuñ", splitf("Czy chcesz usun¹æ obiekt {b}%s{/b}?", HouseFurnitures[ data[ef_ArrayID] ][ef_name]), "Usuñ", "Anuluj");
		}
	}
	
	return 1;
}

stock house_OnPlayerEditDynamicObject(playerid, objectid, response, Float: x, Float: y, Float: z, Float: rx, Float: ry, Float: rz)
{
	switch(response)
	{
	    case EDIT_RESPONSE_CANCEL:
	    {
	        new data[e_furniture];
	        Streamer_GetArrayData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID, data);
			
			if(data[ef_HouseID] != pInfo[playerid][player_house]) return 0;
			
	        SetDynamicObjectPos(objectid, data[furnitureX], data[furnitureY], data[furnitureZ]);
	        SetDynamicObjectRot(objectid, data[furnitureRX], data[furnitureRY], data[furnitureRZ]);
	    }
	    
		case EDIT_RESPONSE_FINAL:
		{
		    new data[e_furniture];
		    Streamer_GetArrayData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID, data);
			
			if(data[ef_HouseID] != pInfo[playerid][player_house]) return 0;
			
		    data[furnitureX] = x;
		    data[furnitureY] = y;
		    data[furnitureZ] = z;
            data[furnitureRX] = rx;
            data[furnitureRY] = ry;
            data[furnitureRZ] = rz;
            SetDynamicObjectPos(objectid, data[furnitureX], data[furnitureY], data[furnitureZ]);
	        SetDynamicObjectRot(objectid, data[furnitureRX], data[furnitureRY], data[furnitureRZ]);
	        Streamer_SetArrayData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID, data);

		//	printf("UPDATE "prefix"_houses_furnitures SET FurnitureX=%f, FurnitureY=%f, FurnitureZ=%f, FurnitureRX=%f, FurnitureRY=%f, FurnitureRZ=%f WHERE id=%d;", data[furnitureX], data[furnitureY], data[furnitureZ], data[furnitureRX], data[furnitureRY], data[furnitureRZ], data[ef_SQLID]);

	        m_query("UPDATE "prefix"_houses_furnitures SET FurnitureX=%f, FurnitureY=%f, FurnitureZ=%f, FurnitureRX=%f, FurnitureRY=%f, FurnitureRZ=%f WHERE id=%d;", data[furnitureX], data[furnitureY], data[furnitureZ], data[furnitureRX], data[furnitureRY], data[furnitureRZ], data[ef_SQLID]);
		}
	}
	
	return 1;
}