/*
		labels.inc
	(c) Copyright 2013-2014 by mrdrifter

	@author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
	@date      : 6 luty 2014
	@update    : -

*/

#define MAX_LABELS 20
enum _@lebel
{
	ltype,
	lcat,
	lsql[5],
	bool:lisFloat,
	Text3D:llabel
}; 
new LabelInfo[MAX_LABELS][_@lebel], LebelCount;

stock label_OnGameModeInit()
{
	/*AddNewLabel(228.6938, 148.4165, 1005.0034, 0, 2); //Onede
	AddNewLabel(2194.8052,1012.4868,13.8203, 0, 0); //LV Najwiêcej respektu
	AddNewLabel(2195.0505,997.4149,13.8203, 5, 0); //LV Najwiêcej osi¹gniêæ
	AddNewLabel(2215.4819,995.8912,12.7824, 18, 0); //LV Najwiêcej wiadomoœci 
	AddNewLabel(2218.8137,1014.5066,12.0052, 20, 0); //LV Najwiêcej czasu gry
	*/
	AddNewLabel(2104.2761,1002.6618,13.8592, 6, 0); // Najwiêcej wygranych solowek
	AddNewLabel(2110.2788,1002.2869,13.8035, 7, 0); //  Najwiêcej przeg solowek
	AddNewLabel(2145.3909,984.4398,15.0091, 21, 0); // Najwiêcej skillu
	AddNewLabel(2189.3013,969.3480,18.6232, 2, 0); // Najwiêcej zabic

	Create3DTextLabel("{46FF39}>>> {FF0100}Dyskoteka {46FF39}<<<", -1, 1837.0372,-1684.6309,13.3229, 20.0, 0, 0);
	Create3DTextLabel("{46FF39}>>> {FF0100}Wyjœcie {46FF39}<<<", -1, 1673.9917,-1341.0393,801.2811, 20.0, 0, 0);
	Create3DTextLabel("{46FF39}>>> {FF0100}DJ'ka {46FF39}<<<", -1, 1682.6635,-1344.6465,804.6904, 20.0, 0, 0);
	Create3DTextLabel("{46FF39}>>> {FF0100}BAR {46FF39}<<<", -1, 1680.8680,-1349.4545,801.2811, 20.0, 0, 0);
    CreateDynamic3DTextLabel("{46FF39}>>> Wejscie {46FF39}<<<", 0x00A1DCFF, 1688.7909,-1347.5448,804.0911, 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, -1, -1, 100.0);
 
	PickupDyskoteka[0] = CreateDynamicPickup(19132, 1, 1837.0372,-1684.6309,13.3229, 0);
	PickupDyskoteka[1] = CreateDynamicPickup(19132, 1, 1673.9917,-1341.0393,801.2811, 0);
	PickupDyskoteka[2] = CreateDynamicPickup(19132, 1, 1682.6635,-1344.6465,804.6904, 0);
	PickupDyskoteka[3] = CreateDynamicPickup(19132, 1, 1680.8680,-1349.4545,801.2811, 0);

    PickupDyskoteka[4] = CreateDynamicPickup(19132, 1, 1688.7909,-1347.5448,804.0911, 0);
	PickupDyskoteka[5] = CreateDynamicPickup(19132, 1, 1688.7234,-1346.1604,804.5147, 0);

	
	UpdateLabels();
	
}

stock AddNewLabel(Float:posX, Float:posY, Float:posZ, type, cat, bool:isFloat = false, orderby[] = "desc", VWs=0)
{
	if(LebelCount > MAX_LABELS)
	{
		printf("[LABEL:ERROR] Stworzono maksymaln¹ iloœæ labeli %d/"#MAX_LABELS"", LebelCount);
		return 0;
	}
	
	if(isFloat) LabelInfo[LebelCount][lisFloat] = true;
	
	format(LabelInfo[LebelCount][lsql], 5, "%s", orderby);
	LabelInfo[LebelCount][ltype] = type; 
	LabelInfo[LebelCount][lcat] = cat; 
	
	LabelInfo[LebelCount][llabel] = CreateDynamic3DTextLabel("Tu na razie jest œciernisko!\nAle bêdzie san Francisco:D", -1, posX, posY, posZ + 1.5, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, VWs);
	
	LebelCount++;
	return 1;
}

stock UpdateLabels()
{
	new str[1024],Query[512], user[32], value, Float:value2, id=1, show[64];
	
	for(new i;i<LebelCount;i++)
	{
		m_query("select nick,%s from "prefix"_players order by %s %s limit 10", topInfo[LabelInfo[i][lcat]][LabelInfo[i][ltype]][esql], topInfo[LabelInfo[i][lcat]][LabelInfo[i][ltype]][esql], LabelInfo[i][lsql]);
		mysql_store_result();
		format(str,sizeof str,"%s\n", topInfo[LabelInfo[i][lcat]][LabelInfo[i][ltype]][ename]);
		while(mysql_fetch_row(Query))
		{
			if(LabelInfo[i][lisFloat])
			{
				sscanf(Query,"p<|>s[32]f", user, value2);
				format(show, sizeof(show), "%.2f", value2);
			}
			else
			{
				sscanf(Query,"p<|>s[32]d", user, value);
				format(show, sizeof(show), "%d", value);
			}
			if(!strcmp(topInfo[LabelInfo[i][lcat]][LabelInfo[i][ltype]][esql], "timeplay", true, 3))
			{
				new days = floatround(((value) / 86400)), 
					godz = floatround(((value) / 3600) - (24 * days)), 
					minut = floatround(((value) / 60) % 60), 
					sek = floatround(((value) - (60 * (minut))) - (3600 * godz) - (86400 * days) );
				format(str,sizeof(str),"%s"HEX_INFO"%d{FFFFFF}. %24s      "HEX_INFO"      %02dd %02dh %02dm %02ds\n",str, id++, user, days, godz, minut, sek);
				continue;
			}
			 
			if(!strcmp(show, "99.9", true)) show = "--";
			if(!strcmp(show, "0", true)) show = "--";
			format(str,sizeof(str),"%s"HEX_INFO"%d{FFFFFF}. %24s      "HEX_INFO"      %64s\n",str, id++, user, show);
		}
		format(str,sizeof(str),"%s{EAB171}Aktualizacja co godzinê!",str);
		UpdateDynamic3DTextLabelText(LabelInfo[i][llabel], -1, str);
		
		id=1;
		str[0] = EOS;
		user[0] = EOS;
		show[0] = EOS;
		Query[0] = EOS;
	}
	printf("labels updates");
	
}

