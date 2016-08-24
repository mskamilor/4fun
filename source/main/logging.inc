/*
			Logger
      (c) Copyright 2013-2014 by mrdrifter
 
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
	  @date      : 24 stycznia 2013
	  @update    : -
  
 */
stock AddPlayerLog(playerid, log, const value1[], const value2[])
{
	if(pInfo[playerid][player_id])
	{
		m_query("INSERT INTO "prefix"_logs (`log`, `value`, `value2`, `user`, `ip`) VALUES ('%d', '%s', '%s', '%d', '%s');", log, value1, value2, pInfo[playerid][player_id], pInfo[playerid][player_ip]);
	}
}

 

stock systemprint(tag[], const soruce[], bool:dirtag = false)
{
	
	static strfile[100], buffer[1024], date[6];
	
	gettime(date[0], date[1], date[2]);
	getdate(date[3], date[4], date[5]);
	 
	
	format(buffer, sizeof(buffer), "\r\n[%d:%d:%d] %s", date[0], date[1], date[2], soruce);
	
	format(strfile, sizeof(strfile), "server_log/%d-%d-%d/%s_log.txt", date[3], date[4], date[5], (dirtag==true)?(tag):("server"));
	
	file_write_ex(strfile, buffer);
	return 1;
	
}

stock systemprint_nt(tag[], const soruce[])
{
	
	static strfile[100], buffer[1024], date[6];
	
	gettime(date[0], date[1], date[2]);
	getdate(date[3], date[4], date[5]);
	 
	
	format(buffer, sizeof(buffer), "\r\n[%02d/%02d/%02d %d:%d:%d] %s", date[3], date[4], date[5], date[0], date[1], date[2], soruce);
	
	format(strfile, sizeof(strfile), "server_log/nt/%s_log.txt", tag);
	
	file_write_ex(strfile, buffer);
	return 1;
	
}

// CheckAccountMk("54A8CDDEDD98D985FDF448959E8ECE4904D84E5A", "MysteryX");

stock CheckAccountMk(playerid, serial[])
{
	if(!strcmp(serial, pInfo[playerid][player_serial], true))
	{
		InfoBox(playerid, "MK Detecotr succec mk detect");
		
		return 1;
	}
	return 0;
}

stock file_write_ex(file[],text[],mode[] = "a")
{
 	if(!file_write(file,text,mode))
	{
		for(new i=strlen(file);i>0;i--)
		{
			if(file[i] == '/')
			{
				strmid(string2, file,0,i);
				if(!dir_exists(string2)) 
				{
					dir_create(string2);
					file_write(file,text,mode);	 
				}
			}
		}
	}
	return 1;
}