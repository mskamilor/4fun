/*
          Achievement [v1.5]
      (c) Copyright 2013-2014 by Game, mrdrifter
 
	  @author    : Game (http://4fun-serv.pl) 
				   mrdrifter (http://4fun-serv.pl/__drifter__/) (Optimal version)
	  @date      : 16 grudnia 2013
	  @update    : 3 stycznia 2014
  
 */ 
 
#define MAX_BANK 20
enum _bank
{
	bank_id,
	Bank_cp,
	Float:Ban_x,
	Float:Ban_y,
	Float:Ban_z
}
new Bank[MAX_BANK][_bank],
BankCount = 0
;
stock LoadBanks()
{
	new czas = GetTickCount(), Float:rotz[3];
	BankCount = 0;
	mysql_query("select * from "prefix"_banks limit "#MAX_BANK"");
	mysql_store_result();
	if(!mysql_num_rows())
		print("Nie odnaleziono �adnego banku!!");
	else
	{
		string2[0] = EOS;
		while(mysql_fetch_row (string2))
		{
			sscanf(string2, "p<|>dffffff", Bank[BankCount][bank_id], Bank[BankCount][Ban_x], Bank[BankCount][Ban_y], Bank[BankCount][Ban_z],rotz[0],rotz[1],rotz[2]);
			
			if(Bank[BankCount][Bank_cp])
			{
				DestroyDynamicCP(Bank[BankCount][Bank_cp]);
			}
			CreateDynamicMapIcon(Bank[BankCount][Ban_x], Bank[BankCount][Ban_y], Bank[BankCount][Ban_z], 52, 0xFFFFFFFF, 0, -1, -1, 350);
			CreateDynamicObject(2618, Bank[BankCount][Ban_x], Bank[BankCount][Ban_y], Bank[BankCount][Ban_z], rotz[0],rotz[1],rotz[2]);
			
			Bank[BankCount][Bank_cp] = CreateDynamicCP(Bank[BankCount][Ban_x], Bank[BankCount][Ban_y], Bank[BankCount][Ban_z], 1.6, 0,0,-1,30.0);
			BankCount++;
		}
		printf("[load] wczytanych bank�w:\t%d \t\t[czas trwania: %d ms]", mysql_num_rows(), GetTickCount()-czas);
	}
	mysql_free_result();
}

Dialog:D_BANK(playerid, response, listitem, inputtext[])
{
	if(response == 0)
		return 1;
	switch(listitem)
	{
		case 0: Dialog_Show(playerid, D_BANK_WPLAC, DIALOG_STYLE_INPUT, "Bank � Wp�a�", "Podaj kwote kt�r� chcesz wp�aci� na konto:", "Wp�a�", "Wyjd�");
		case 1: Dialog_Show(playerid, D_BANK_WYPLAC, DIALOG_STYLE_INPUT, "Bank � Wyplac", "Podaj kwote kt�r� chcesz wyp�aci� z konta:", "Wyp�a�", "Wyjd�");
		case 2:
		{
			format(string2, sizeof(string2), "{FFE5A1}Stan twojego konta bankowego wynosi {EAB171}%s$", FormatNumber(pInfo[playerid][player_bank]));
			Dialog_Show(playerid, D_BANK_STAN, DIALOG_STYLE_MSGBOX, "Stan Konta", string2, "Cofnij", "");
	
			return 1;
		}
		case 3: Dialog_Show(playerid, D_BANK_PRZELEW, DIALOG_STYLE_INPUT, "Bank � Przelew", "Podaj kwote kt�r� chcesz przela� na konto innego gracza:", "Przelej", "Wyjd�");
	}
	return 1;
}
stock Dialog_BankMenu(playerid)
{
	if(!pInfo[playerid][player_register])
	{
		SendClientMessage(playerid, COLOR_ERROR, " Musisz si� {b}zarejestrowa�{/b} aby mie� dost�p do banku.");
		return 1;
	}
	Dialog_Show(playerid, D_BANK, DIALOG_STYLE_LIST, "{EAB171}Bank", "{AC3E00}Wp�a�\n{EAB171}Wyp�a�\n{AC3E00}Stan konta\n{EAB171}Przelew", "Wybierz", "Wyjd�");
	return 1;
}
Dialog:D_BANK_STAN(playerid, response, listitem, inputtext[])
{
	Dialog_BankMenu(playerid);
	return 1;
}
Dialog:D_BANK_WPLAC(playerid, response, listitem, inputtext[])
{
	if(response == 0)
		return 1;
	new kwota = strval(inputtext);
	if(GetPlayerMoney(playerid) < kwota)
	{
		Dialog_Show(playerid, D_BANK_WPLAC, 1, "Bank � Wp�a�", ""HEX_ERROR"Nie posiadasz takiej ilo�ci pieni�dzy\n"HEX_SAMP"Podaj kwote kt�r� chcesz wp�aci�", "Dalej", "Wyjd�");
		return 1;
	}
	if(kwota > 15000000)
	{
		Dialog_Show(playerid, D_BANK_WPLAC, 1, "Bank � Wp�a�", ""HEX_ERROR"Maximum 15.000.000$!\n"HEX_SAMP"Podaj kwote kt�r� chcesz wp�aci� na konto:", "Dalej", "Wyjd�");
		return 1;
	}
	if(kwota < 1)
	{
		Dialog_Show(playerid, D_BANK_WPLAC, 1, "Bank � Wp�a�", ""HEX_ERROR"Minimum 1$!\n"HEX_SAMP"Podaj kwote kt�r� chcesz wp�aci� na konto:", "Dalej", "Wyjd�");
		return 1;
	}
	pInfo[playerid][player_bank] = (pInfo[playerid][player_bank] + kwota);
	
	SendClientMessage(playerid, COLOR_ERROR, " Wp�aci�e� do banku %d$. Obecny stan konta: %d$", kwota, pInfo[playerid][player_bank]);
	GivePlayerMoney(playerid, -kwota);
	
	return 1;
}
Dialog:D_BANK_WYPLAC(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new kwota = strval(inputtext);
		if(pInfo[playerid][player_bank] < kwota)
		{
			Dialog_Show(playerid, D_BANK_WYPLAC, 1, "Bank � Wyp�a�", ""HEX_ERROR"Nie posiadasz takiej ilo�ci pieni�dzy\n"HEX_SAMP"Podaj kwote kt�r� chcesz wyp�aci�", "Dalej", "Wyjd�");
			return 1;
		}
		if(kwota > 15000000)
		{
			Dialog_Show(playerid, D_BANK_WYPLAC, 1, "Bank � Wyp�a�", ""HEX_ERROR"Maximum 15.000.000$!\n"HEX_SAMP"Podaj kwote kt�r� chcesz wyp�aci� na konto:", "Dalej", "Wyjd�");
			return 1;
		}
		if(kwota < 1)
		{
			Dialog_Show(playerid, D_BANK_WYPLAC, 1, "Bank � Wyp�a�", ""HEX_ERROR"Minimum 1$!\n"HEX_SAMP"Podaj kwote kt�r� chcesz wyp�aci� na konto:", "Dalej", "Wyjd�");
			return 1;
		}
		pInfo[playerid][player_bank] = (pInfo[playerid][player_bank] - kwota);
		
		SendClientMessage(playerid, COLOR_ERROR, " Wyp�aci�e� z banku %d$. Obecny stan konta: %d$", kwota, pInfo[playerid][player_bank]);
		GivePlayerMoney(playerid, kwota);
	}
	else 
	{
		Dialog_BankMenu(playerid);
	}
	return 1;
}
Dialog:D_BANK_PRZELEW(playerid, response, listitem, inputtext[])
{
	if(response == 0)
		return Dialog_BankMenu(playerid);

	new kwota = strval(inputtext);
	if(pInfo[playerid][player_bank] < kwota)
	{
		Dialog_Show(playerid, D_BANK_PRZELEW, 1, "Bank � Przelew", ""HEX_ERROR"Nie posiadasz takiej ilo�ci pieni�dzy\n"HEX_SAMP"Podaj kwote kt�r� chcesz przela� na konto innego gracza:", "Przelej", "Wyjd�");
		return 1;
	}
	if(kwota > 15000000)
	{
		Dialog_Show(playerid, D_BANK_PRZELEW, 1, "Bank � Wp�a�", ""HEX_ERROR"Maximum 15.000.000$!\n"HEX_SAMP"Podaj kwote kt�r� chcesz wp�aci� na konto:", "Wp�a�", "Wyjd�");
		return 1;
	}
	if(kwota < 1)
	{
		Dialog_Show(playerid, D_BANK_PRZELEW, 1, "Bank � Wp�a�", ""HEX_ERROR"Minimum 1$!\n"HEX_SAMP"Podaj kwote kt�r� chcesz wp�aci� na konto:", "Wp�a�", "Wyjd�");
		return 1;
	}
	SetPVarInt(playerid, "bank_kwota", kwota);
	format(string2, sizeof(string2), "Podaj ID Gracza kt�remu chcesz przes�a� "HEX_GRAY"%d$"HEX_SAMP".", kwota);
 	Dialog_Show(playerid, D_BANK_PRZELEW2, DIALOG_STYLE_INPUT, "Bank � Przelew", string2, "Przelej", "Wyjd�");
	return 1;
}


Dialog:D_BANK_PRZELEW2(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new id = strval(inputtext);
		if(!IsPlayerConnected(id))
		{
			SendClientMessage(playerid, COLOR_ERROR, "Nie ma takiego gracza!");
			format(string2, sizeof(string2), "Podaj ID Gracza kt�remu chcesz przes�a� "HEX_GRAY"%d$"HEX_SAMP".", GetPVarInt(playerid, "bank_kwota"));
			Dialog_Show(playerid, D_BANK_PRZELEW2, DIALOG_STYLE_INPUT, "Bank � Przelew", string2, "Przelej", "Wyjd�");
		
			return 1;
		}
		if(id == playerid)
		{
			SendClientMessage(playerid, COLOR_ERROR, " Nie mo�esz sobie przela� kasy!");
			format(string2, sizeof(string2), "Podaj ID Gracza kt�remu chcesz przes�a� "HEX_GRAY"%d$"HEX_SAMP".", GetPVarInt(playerid, "bank_kwota"));
			Dialog_Show(playerid, D_BANK_PRZELEW2, DIALOG_STYLE_INPUT, "Bank � Przelew", string2, "Przelej", "Wyjd�");
		
			return 1;
		}
		if(!pInfo[id][player_register])
		{
			SendClientMessage(playerid, COLOR_ERROR, " Gracz kt�remu pr�bujesz przes�a� pieni�dze jest niezarejestrowany.");
			format(string2, sizeof(string2), "Podaj ID Gracza kt�remu chcesz przes�a� "HEX_GRAY"%d$"HEX_SAMP".", GetPVarInt(playerid, "bank_kwota"));
			Dialog_Show(playerid, D_BANK_PRZELEW2, DIALOG_STYLE_INPUT, "Bank � Przelew", string2, "Przelej", "Wyjd�");
		
			return 1;
		}
		
		pInfo[id][player_bank] = (pInfo[id][player_bank] + GetPVarInt(playerid, "bank_kwota"));
		pInfo[playerid][player_bank] = (pInfo[playerid][player_bank] - GetPVarInt(playerid, "bank_kwota"));
		SendClientMessage(playerid, COLOR_GOLD, " Przela�e� graczowi %s na jego konto kwot� %d$. Obecny stan twojego konta %s$", playerNick(id), GetPVarInt(playerid, "bank_kwota"), FormatNumber(pInfo[playerid][player_bank]));
		SendClientMessage(id, COLOR_INFO, " %s przela� na twoje konto kwot� %d$. Obecny stan konta: %s$", playerNick(playerid), GetPVarInt(playerid, "bank_kwota"), FormatNumber(pInfo[id][player_bank]));
		Dialog_BankMenu(playerid);
	}
	return 1;
}
