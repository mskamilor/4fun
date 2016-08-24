/*
          Business [NOT VERSION]
      (c) Copyright 2013-2014 by mrdrifter
 
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
	  @date      : 16 grudnia 2013
	  @update    : 3 stycznia 2014
  
 */ 

#define MAX_PLAYER_BIZNES 3
#define MAX_BUSINESS 155

enum business_
{
	sql_id,
	b_name[80],
	b_price,
	b_owner_name[30],
	b_owner_id,
	Float:b_pos[3],
	Text3D:label,
	pickup,
	mapicon,
	bool:b_active,
	buytime
}
new Business[MAX_BUSINESS][business_], load_Business, lastbiznes_cash;

loadDynamicBusiness()
{
	new ParameterValue[128];
	new czas = GetTickCount();
	
	load_Business = 0;
	
	mysql_query("SELECT h.* , ifnull(IF(owner !=0, p.nick, 'Brak'), 'Brak') owner_nick FROM "prefix"_business h LEFT JOIN "prefix"_players p ON p.id = h.owner limit "#MAX_BUSINESS"");
	mysql_store_result();
	new i = 0; 
	 
	for(new x;x<mysql_num_rows();x++)
	{
		 
		load_Business++;
		if(x >= MAX_BUSINESS) break;
		if(load_Business >= MAX_BUSINESS) break;
		
		mysql_data_seek(x);//globalInterior
		mysql_fetch_row_data();
		
		mysql_fetch_field("id", ParameterValue);
		Business[i][sql_id] = strval(ParameterValue);
		
		mysql_fetch_field("name", Business[i][b_name]);
		
		mysql_fetch_field("price", ParameterValue);
		Business[i][b_price] = strval(ParameterValue);
		
		
		mysql_fetch_field("owner_nick", Business[i][b_owner_name]);
		
		mysql_fetch_field("owner", ParameterValue);
		Business[i][b_owner_id] = strval(ParameterValue);
		
		
		mysql_fetch_field("business_cord", ParameterValue);
		sscanf(ParameterValue, "p<,>a<f>[3]", Business[i][b_pos]);
		Business[i][b_active] = true;
		
		Biznes_Create(i);
		i++;
	}
	printf("[load] wczytanych biznesów:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	mysql_free_result();
	
	if(load_Business >= MAX_BUSINESS)
		load_Business = MAX_BUSINESS - 1;
	return 1;
	
}

stock Biznes_Cash()
{
	if(lastbiznes_cash < gettime())
	{
		for(new i;i<load_Business+1;i++)
		{
			if(Business[i][b_active] == false) continue;
			if(Business[i][b_owner_id] == 0) continue;
			
			foreach(new player : Player)
			{
				if(pInfo[player][player_id] == Business[i][b_owner_id]){
					SendClientMessage(player, COLOR_INFO, ""chat" Otrzymujesz {b}%s${/b} z swojej posiad³oœci {b}%s{/b}.",FormatNumber(Business[i][b_price]), Business[i][b_name]);
					GivePlayerMoney(player, Business[i][b_price]);
				}
			}
		}
		lastbiznes_cash = gettime() + (60*10);
	}
}
stock Biznes_Save(i)
{
	m_query("update "prefix"_business set owner=%d where id=%d limit 1;", Business[i][b_owner_id], Business[i][sql_id]);
}

stock Biznes_Create(i)
{
	
	DestroyDynamicPickup(Business[i][pickup]);
	DestroyDynamic3DTextLabel(Text3D:Business[i][label]);
	
	Business[i][label] = CreateDynamic3DTextLabel("Biznes", 0xFFFFFFFF, Business[i][b_pos][0], Business[i][b_pos][1], Business[i][b_pos][2], 100.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID, 1, 0, 0, -1,100.0);
	Business[i][pickup] = CreateDynamicPickup(1274, 23, Business[i][b_pos][0], Business[i][b_pos][1], Business[i][b_pos][2],0,0);
	
	Business[i][mapicon] = CreateDynamicMapIcon(Business[i][b_pos][0], Business[i][b_pos][1], Business[i][b_pos][2],8, 0x33AA3390, 0, 0, -1, 200.0);
	
	Business_UpdateLabel(i);
	
}

stock Business_UpdateLabel(id)
{
	
	if(Business[id][b_owner_id] == 0)
	{
		format(string2, sizeof(string2), "Biznes\n{CCDDDD}%s - %s$\n{FFCCDD}Na sprzeda¿.", Business[id][b_name], FormatNumber( Business[id][b_price]));
	}
	else
	{
		format(string2, sizeof(string2), "Biznes\n{CCDDDD}%s - %s$\n{FFCCDD}W³aœciciel: %s.", Business[id][b_name], FormatNumber( Business[id][b_price]), Business[id][b_owner_name]);
	}
	UpdateDynamic3DTextLabelText(Business[id][label], 0xFFFFFFFF, string2);
}
stock Biznes_GetPlayerBiznesCount(playerid)
{
	
	new b;
	for(new i=0;i<load_Business+1;i++)
	{
		if(Business[i][b_active] == false) continue;
		
		if(Business[i][b_owner_id] == pInfo[playerid][player_id])
		{
			b++;
		}
	}
	return b;
}


b_OnPlayerDynamicPickup(playerid, pickupid)
{
	
	for(new i=0;i<load_Business+1;i++)
	{
		
		if(Business[i][b_active] == false) continue;
		
		if(Business[i][pickup] == pickupid)
		{
			if(pInfo[playerid][player_lasthouse_dialogshow] > gettime()) return 1;
			
			pInfo[playerid][player_lasthouse_dialogshow] = gettime() + 5;
			pInfo[playerid][player_action_houseid] = i;
			
			if(Business[i][b_owner_id] == 0)
			{
				format(string2, sizeof(string2), "Ten biznes jest wolny\n\nCzy chcesz go kupiæ za %s$? bêdziesz regularnie dostawa³ %s$\nDo czasu a¿ ktoœ go nie kupi.",  FormatNumber( Business[i][b_price]),  FormatNumber( Business[i][b_price]));
				Dialog_Show(playerid, DIALOG_BIZNES_BUY, DIALOG_STYLE_MSGBOX, "Biznes", string2, "Kup", "Anuluj");
			}
			else if(Business[i][b_owner_id] == pInfo[playerid][player_id])
			{
				format(string2, sizeof(string2), "Ten biznes nale¿y do Ciebie.\n\nCzy chcesz go sprzedaæ za %s$?",  FormatNumber((Business[i][b_price]/2)));
				Dialog_Show(playerid, DIALOG_BIZNES_SELL, DIALOG_STYLE_MSGBOX, "Biznes", string2, "Sprzedaj", "Anuluj");
			}
			else
			{
				format(string2, sizeof(string2), "Ten biznes jest zajêty przez %s\n\nCzy chcesz go odkupiæ za %s$? bêdziesz regularnie dostawa³ %s$\nDo czasu a¿ ktoœ go nie kupi.", Business[i][b_owner_name], FormatNumber( Business[i][b_price]), FormatNumber( Business[i][b_price]));
				Dialog_Show(playerid, DIALOG_BIZNES_BUY, DIALOG_STYLE_MSGBOX, "Biznes", string2, "Kup", "Anuluj");
			}
			
			break;
		}
		
	}
	return 1;
}

stock Biznes_Buy(playerid, biznesid)
{
	if(!pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, " Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do tej komendy.");
		return 1;
	}
	
	if(Business[biznesid][buytime] > gettime())
	{
		SendClientMessage(playerid, COLOR_ERROR, "{FF0000}*{/b} Ten biznes bêdzie mo¿na kupiæ za %dm.", ((Business[biznesid][buytime] - gettime())/60));
		return 1;
	}
	new bcount = Biznes_GetPlayerBiznesCount(playerid);
	
	if(bcount >= MAX_PLAYER_BIZNES)
	{
		SendClientMessage(playerid, COLOR_ERROR, "{FF0000}*{/b} Posiadasz maxymaln¹ liczbê biznesów (%d).", bcount);
		return 1;
	}
	if(GetPlayerMoney(playerid) < Business[biznesid][b_price])
	{
		SendClientMessage(playerid, COLOR_ERROR, "{FF0000}*{/b} Nie staæ Ciê na ten biznes! potrzebujesz jeszcze {b}%s${/b}.", FormatNumber(Business[biznesid][b_price] - GetPlayerMoney(playerid)));
		return 1;
	}
	if(Business[biznesid][b_owner_id] == 0)
	{
		SendClientMessage(playerid, COLOR_GREEN, "* Kupi³eœ biznes {b}%s{/b}! Bêdziesz regularnie dostawaæ {b}%s${/b} do banku.", Business[biznesid][b_name], FormatNumber(Business[biznesid][b_price]));
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREEN, "* Odkupieœ biznes %s! Bêdziesz regularnie dostawaæ {b}%s${/b} do banku.", Business[biznesid][b_name], FormatNumber(Business[biznesid][b_price]));
		
		foreach(new player : Player)
		{
			if(pInfo[player][player_id] == Business[biznesid][b_owner_id])
			{
				SendClientMessage(player, COLOR_INFO, "* {b}%s (%d){/b} odkupi³ Twój biznes.", playerNick(playerid), playerid);
				break;
			}
		}
	}
	
	achievement(playerid, 16);
	Business[biznesid][buytime] = gettime() + ((60*10)*3);
	GivePlayerMoney(playerid, (-Business[biznesid][b_price]));
	Business[biznesid][b_owner_id] = pInfo[playerid][player_id];
	format(Business[biznesid][b_owner_name], MAX_PLAYER_NAME, playerNick(playerid));
	
	Business_UpdateLabel(biznesid);
	Biznes_Save(biznesid);
	return 1;
}

stock Biznes_Sell(playerid){
	
	if(!pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, " Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do tej komendy.");
		return 1;
	}
	
	for(new i;i<load_Business+1;i++)
	{
		if(Business[i][b_active] == false) continue;
		
		if(pInfo[playerid][player_id] == Business[i][b_owner_id])
		{
			SendClientMessage(playerid, COLOR_INFO, ""chat" Sprzeda³eœ swój biznes za %s$.", FormatNumber(Business[i][b_price]/2));
			
			
			GivePlayerMoney(playerid, (Business[i][b_price]/2));
			
			Business[i][b_owner_id] = 0;
			format(Business[i][b_owner_name], MAX_PLAYER_NAME, "Brak");
			Biznes_Save(i);
			Business_UpdateLabel(i);
			break;
		}
	}
	return 1;
}
stock Biznes_Add(playerid, price, name[]){
	
	for(new i;i<MAX_BUSINESS;i++)
	{
		if(Business[i][b_active] == false)
		{
			 
			GetPlayerPos(playerid, Business[i][b_pos][0], Business[i][b_pos][1], Business[i][b_pos][2]);
			
			mysql_real_escape_string(name, Business[i][b_name]);
			
			m_query("INSERT INTO `"prefix"_business` (`name`, `price`, `owner`, `business_cord`) VALUES ('%s', '%d', '0', '%f, %f, %f');", Business[i][b_name], price, Business[i][b_pos][0], Business[i][b_pos][1], Business[i][b_pos][2]);
			mysql_store_result();
			Business[i][sql_id] = mysql_insert_id();
			mysql_free_result();
			
			format(Business[i][b_owner_name], 60, "Brak");
			
			Business[i][b_price] = price;
			
			Business[i][b_active] = true;
			
			Biznes_Create(i);
			
			return 1;
			
		}
	}
	return 0;
	
}



CMD:nowybiznes(playerid, params[])
{
	
	RankAdmin(playerid, R_VICEHEADADMIN);
	
	if(load_Business+1 >= MAX_BUSINESS - 1)
	{
		SendClientMessage(playerid, COLOR_RED, "* Wykorzystano limit biznesów.");
		return 1;
	}
	
	if(GetPlayerInterior(playerid) != 0)
	{
		SendClientMessage(playerid, COLOR_RED, "* Nie mo¿esz tworzyæ biznesu w interiorze.");
		return 1;
	}
	
	SendClientMessage(playerid, COLOR_GREEN, "* Rozpoczêto tworzenie biznesu.");
	
	Dialog_Show(playerid, DIALOG_NEW_BIZNES1, DIALOG_STYLE_INPUT, "Biznes koszt", "Podaj koszt nowego biznesu", "Dalej", "Anuluj");
	return 1;
}


CMD:mybiznes(playerid, parmas[])
{
	
	if(!pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, " Musisz siê {b}zarejestrowaæ{/b} aby mieæ dostêp do tej komendy.");
		return 1;
	}
	
	
	if(!Biznes_GetPlayerBiznesCount(playerid))
	{
		SendClientMessage(playerid, COLOR_ERROR, " Nie posiadasz ¿adnego biznesu!");
		return 1;
	}
	SendClientMessage(playerid, COLOR_GREEN, " Twoje biznesy!");
	
	new bplayer[255],ac;
	for(new i=0;i<load_Business+1;i++)
	{
		if(Business[i][b_active] == false) continue;
		if(ac>MAX_PLAYER_BIZNES)break;
		if(Business[i][b_owner_id] == pInfo[playerid][player_id])
		{
			format(bplayer, sizeof(bplayer), "%s%s - %d$\n", bplayer, Business[i][b_name], Business[i][b_price]);
			pInfo[playerid][player_dialog_data][ac] = i;
			ac++;
		}
	}
	
	Dialog_Show(playerid, DIALOG_BIZNES_TP, DIALOG_STYLE_LIST, "Twoje biznesy", bplayer, "Teleportuj", "Anuluj");
	
	return 1;
}

Dialog:DIALOG_BIZNES_BUY(playerid, response, listitem, inputtext[]){
	
	if(response)
	{
		Biznes_Buy(playerid, pInfo[playerid][player_action_houseid]);
	}
	return 1;
}
Dialog:DIALOG_BIZNES_SELL(playerid, response, listitem, inputtext[]){
	
	if(response)
	{
		Biznes_Sell(playerid);
	}
	return 1;
}
Dialog:DIALOG_NEW_BIZNES1(playerid, response, listitem, inputtext[]){
	
	if(!response)
	{
		SendClientMessage(playerid, COLOR_GREEN, "* Anulowano tworzenie biznesu.");
		return 1;
	}
	if(!inputtext[0]){
		Dialog_Show(playerid, DIALOG_NEW_BIZNES1, DIALOG_STYLE_INPUT, "Biznes koszt", "{FF0000}Nie poda³eœ kosztu biznesu{Ffffff}\n\nPodaj koszt nowego biznesu", "Dalej", "Anuluj");
		return 1;
	}
	
	new koszt = strval(inputtext);
	if(koszt < 50000)
	{
		Dialog_Show(playerid, DIALOG_NEW_BIZNES1, DIALOG_STYLE_INPUT, "Biznes koszt", "{FF0000}Minimalny koszt biznesu to 50.000{Ffffff}\n\nPodaj koszt nowego biznesu", "Dalej", "Anuluj");
		return 1;
	}
	if(koszt > 100000)
	{
		Dialog_Show(playerid, DIALOG_NEW_BIZNES1, DIALOG_STYLE_INPUT, "Biznes koszt", "{FF0000}Maksymalny koszt biznesu to 100.000{Ffffff}\n\nPodaj koszt nowego biznesu", "Dalej", "Anuluj");
		return 1;
	}
	pInfo[playerid][player_businessprice] = koszt;
	Dialog_Show(playerid, DIALOG_NEW_BIZNES2, DIALOG_STYLE_INPUT, "Biznes nazwa", "{0000FF}Ustawi³eœ koszt biznesu{Ffffff}\n\nPodaj nazwê biznesu.", "Dalej", "Anuluj");
	return 1;
}
Dialog:DIALOG_NEW_BIZNES2(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SendClientMessage(playerid, COLOR_GREEN, "* Anulowano tworzenie biznesu.");
		return 1;
	}
	
	if(!inputtext[0])
	{
		Dialog_Show(playerid, DIALOG_NEW_BIZNES2, DIALOG_STYLE_INPUT, "Biznes koszt", "{FF0000}Nie poda³eœ nazwy biznesu{Ffffff}\n\nPodaj nazwê biznesu", "Dalej", "Anuluj");
		return 1;
	}
	
	if(Biznes_Add(playerid, pInfo[playerid][player_businessprice], inputtext))
	{
		SendClientMessage(playerid, COLOR_GREEN, "* Doda³eœ/aœ nowy biznes %s (%s$).", inputtext, FormatNumber(pInfo[playerid][player_businessprice]));
		return 1;
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREEN, "* Biznes %s (%d$) nie móg³ zostaæ dodany z nie znanych przyczyn.", inputtext, pInfo[playerid][player_businessprice]);
		return 1;
	}
}
Dialog:DIALOG_BIZNES_TP(playerid, response, listitem, inputtext[])
{
	
	if(response)
	{
		new i = pInfo[playerid][player_dialog_data][listitem];
		SetPlayerPos(playerid, Business[i][b_pos][0], Business[i][b_pos][1], Business[i][b_pos][2]);
	}
	return 1;
}