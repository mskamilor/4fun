/*
			Object loader
      (c) Copyright 2013-2014 by mrdrifter
 
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
	  @date      : 29 grudnia 2013
	  @update    : 2 luty 2014
  
 */
 
#define MAX_DELETE_OBJECT 1500
enum removeobject
{
	Models, 
	Float:rPos[4],
	bool:Used
}
new RemoveBuilding[MAX_DELETE_OBJECT][removeobject];
new LoadedObjects[2];
stock LoadedObjectType[2];

method obiect::load()
{
	new objp[][] = 
	{
		{"bank.txt"},
		{"fun.txt"},
		{"half_pipe.txt"},
		{"jail.txt"},
		{"vehicles.txt"},
		{"monster_parkour.txt"},
		{"drafter_stunt.txt"},
		{"ls_i_salon_pustynia.txt"},
		{"tabi/tabi.txt"},
		{"tabi/tabi_mrdrifter.txt"}
	};
	for(new i;i<sizeof(objp);i++) this->obiect::loadFile(objp[i]);
}
 
method obiect::loadFile(obj[])
{

	new czas = GetTickCount();
	if (!fexist("happy_fun/object")) 
	{
		printf("[obiect::loadFile] Brak folderu: happy_fun/object ");
		return 1;
	}
	
	/*if (!fexist(splitf("happy_fun/object/%s", obj))) 
	{
		printf("brak pliku %s", splitf("happy_fun/object/%s", obj));
		return 1;
	}*/
	
	 
	
	new File:cfg=fopen(splitf("happy_fun/object/%s", obj), io_read);
    new string[256], load, lx;
	if(cfg)
	{
		while(fread(cfg, string)) 
		{
			lx = LoadedObjects[0] > 0 ? (1):(0);
			if((lx = this->obiect::check(string), lx)) 
			{
				load++;
			}
		}
	}
	printf("[load] wczytanych obiektów(%s):\t%d \t\t[czas trwania: %d ms]", load, obj, GetTickCount()-czas);

//	printf("load %d obj", load);
	return 1;
}
method obiect::check(string[])
{
	new cx = strfind(string, ");");
	if(cx != -1) string[cx] = EOS;
	
	new pstr[30];
	

	format(pstr, sizeof(pstr), "%s", string);
	if(strfind(pstr, "//", true) != -1)
	{
		return 0;
	}
	if(strfind(string, "AddStaticVehicle(") != -1)
	{
		
		
		new d[3], Float:f[4];
		sscanf(string, "{p<(>s[128]}p<,>iffffii", d[0], f[0], f[1], f[2], f[3], d[1], d[2]);
		//if(f[2]>60.0)continue;
		
		switch(d[0])
		{
			case 425, 432, 520: return 0;
		}
		AddStaticVehicle(d[0], f[0], f[1], f[2], f[3], d[1], d[2]);
 		return 1;
	}
	if(strfind(string, "AddStaticVehicleEx(") != -1)
	{
		new d[4], Float:f[4];
		sscanf(string, "{p<(>s[128]}p<,>iffffiii", d[0], f[0], f[1], f[2], f[3], d[1], d[2], d[3]);
		switch(d[0])
		{
			case 425, 432, 520: return 0;
		}
		AddStaticVehicleEx(d[0], f[0], f[1], f[2], f[3], d[1], d[2], d[3]);
 		return 1;
	}
	if(strfind(string, "CreateVehicle(") != -1)
	{
		new d[4], Float:f[4];
		sscanf(string, "{p<(>s[128]}p<,>iffffiii", d[0], f[0], f[1], f[2], f[3], d[1], d[2], d[3]);
		
		switch(d[0]){
			case 425, 432, 520: return 0;
		}
		
		CreateVehicle(d[0], f[0], f[1], f[2], f[3], d[1], d[2], d[3]);
 		return 1;
	}
	if((strfind(string, "CreateDynamicObject(") != -1))
	{
		new d[1], Float:f[6];
		sscanf(string, "{p<(>s[128]}p<,>iffffff", d[0], f[0], f[1], f[2], f[3], f[4], f[5]);
		return CreateDynamicObject(d[0], f[0], f[1], f[2], f[3], f[4], f[5], -1, 0, -1, 300.0);
		 
	}
	
	if((strfind(string, "CreateObject(") != -1))
	{
		new d[1], Float:f[6];
		sscanf(string, "{p<(>s[128]}p<,>iffffff", d[0], f[0], f[1], f[2], f[3], f[4], f[5]);
		return CreateDynamicObject(d[0], f[0], f[1], f[2], f[3], f[4], f[5], -1, -1, -1, 300.0);
		 
	}
	if((strfind(string, "RemoveBuildingForPlayer(") != -1))
	{
		strdel(string, 24, 24+9);
		new d[1], Float:f[4];
		sscanf(string, "{p<(>s[128]}p<,>dffff", d[0], f[0], f[1], f[2], f[3]);
		
		this->obiect::removeBuilding(d[0], f);
		return 1;
	}
	return 0;
}

method obiect::removeBuilding(model, Float:Pozycjaa[4])
{
	for(new i;i<MAX_DELETE_OBJECT;i++)
	{
		if(RemoveBuilding[i][Used]==false)
		{
			RemoveBuilding[i][Models] = model;
			RemoveBuilding[i][rPos][0] = Pozycjaa[0];
			RemoveBuilding[i][rPos][1] = Pozycjaa[1];
			RemoveBuilding[i][rPos][2] = Pozycjaa[2];
			RemoveBuilding[i][rPos][3] = Pozycjaa[3];
			RemoveBuilding[i][Used] = true;
			break;
		}
	}
}
 
method obiect::removeBuildingSelect(playerid)
{

	for(new i;i<MAX_DELETE_OBJECT;i++)
	{
		if(RemoveBuilding[i][Used]==true)
		{
			RemoveBuildingForPlayer(playerid, RemoveBuilding[i][Models], RemoveBuilding[i][rPos][0], RemoveBuilding[i][rPos][1], RemoveBuilding[i][rPos][2], RemoveBuilding[i][rPos][3]);
			#if defined BuildingDebug
			printf("[debug] %d, %d, %f, %f, %f, %f", playerid, RemoveBuilding[i][Models], RemoveBuilding[i][rPos][0], RemoveBuilding[i][rPos][1], RemoveBuilding[i][rPos][2], RemoveBuilding[i][rPos][3]);
			#endif
		}
	}
	
}
