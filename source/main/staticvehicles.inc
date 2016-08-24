#define max_Cars	1500

new Cars;

enum stat_cars
{
	scar_id,
	Veh,
	car_model,
	Float:car_x,
	Float:car_y,
	Float:car_z,
	Float:car_angle,
	car_col1,
	car_col2	
};
new Car[max_Cars][stat_cars];


stock static_vehicles_init()
{
	Cars = 0;
	LoadVehicles();	
}

stock LoadVehicles()
{
	new count = GetTickCount();
	
	new Query[256];
	new xStr[50];
	new yStr[50];
	new zStr[50];
	new aStr[50];
	m_query("SELECT ID, col1, col2, model, x, y, z, angle FROM "prefix"_staticvehicles");
	mysql_store_result();
	for(new i=0 ;i<mysql_num_rows();i++)
	{
		mysql_fetch_row(Query, "|");
		sscanf(Query, "p<|>dddds[50]s[50]s[50]s[50]",Car[i][scar_id], Car[i][car_col1], Car[i][car_col2], Car[i][car_model], xStr, yStr, zStr, aStr );
		printf("%s",Query);
		
		Car[i][car_x] = floatstr(xStr);
		Car[i][car_y] = floatstr(yStr);
		Car[i][car_z] = floatstr(zStr);
		Car[i][car_angle] = floatstr(aStr);
		
		printf("%f %f %f %f",Car[i][car_x],Car[i][car_y],Car[i][car_z],Car[i][car_angle]);
		
		Car[i][Veh] = CreateVehicle(Car[i][car_model], Car[i][car_x], Car[i][car_y], Car[i][car_z], Car[i][car_angle], Car[i][car_col1], Car[i][car_col2], -1,0);
		Cars++;
	}
	
	mysql_free_result();
	
	return printf("[load] Wczytywanie pojazdow skonczone:\t Cars: %d \t\t[czas trwania: %d ms]", Cars, GetTickCount()-count);
}

CMD:delcar(playerid,params[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	
	if(!IsPlayerInAnyVehicle(playerid))return SendClientMessage(playerid,COLOR_ERROR,"Musisz byæ w pojeŸdzie.");
	
	for(new x; x < max_Cars; x++)
	{
		if(Car[x][Veh] == GetPlayerVehicleID(playerid))
		{
			new Qstr[256];
			format(Qstr,256,"DELETE FROM `4fun_samp`.`mreg_staticvehicles` WHERE `mreg_staticvehicles`.`ID` = %d",Car[x][scar_id]);
			printf("%s",Qstr);
			SendClientMessage(playerid,COLOR_ERROR,"Pojazd usuniêty. Zniknie on po restarcie serwera.");
		}
	}

	return 1;
}

CMD:createcar(playerid,params[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	
	if(!IsPlayerInAnyVehicle(playerid))return SendClientMessage(playerid,COLOR_ERROR,"Musisz byæ w pojeŸdzie.");
	if(Cars > max_Cars)return SendClientMessage(playerid,COLOR_ERROR,"Osi¹gniêto limit. Zg³oœ to programiœcie.");
	
	new currentveh;
    new Float:z_rot, Float:y, Float:z, Float:x;
 
    currentveh = GetPlayerVehicleID(playerid);
	GetVehicleZAngle(currentveh, z_rot);
	GetVehiclePos(currentveh, x,y,z);
	
	new rand1 = random(56-0)+0;    
	new rand2 = random(56-0)+0;    
	
	new strq[255];
	format(strq,255,"INSERT INTO `mreg_staticvehicles`(`ID`, `x`, `y`, `z`, `angle`, `col1`, `col2`, `model`) VALUES (NULL, '%f', '%f', '%f', '%f', %d, %d, %d )",x, y,z, z_rot, rand1, rand2, GetVehicleModel(currentveh));
	m_query(strq);
	
	SendClientMessage(playerid,COLOR_ERROR,"Dodano pojazd do bazy.");
	
	return 1;
}
