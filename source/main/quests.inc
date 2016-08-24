/*
          Player quests [1.0]
      (c) Copyright 2016 by Msk.
 
	  @author    : Msk.
	  @date      : 13 sierpnia 2016
	  @update    : 
  
 */  

#define MAX_ZAGADEK	100


enum QuestEnum
{
	opis[500],
	Zid,
	object,
	Text3D:zlabel,
	Float:Zpos[3],
	nagroda
}
new Zag[MAX_ZAGADEK][QuestEnum];

stock LoadZagadki()
{
	new LoadStr[256], Pos[64];
	m_query("SELECT ID,nagroda,opis,position FROM "prefix"_quests WHERE zebrane=0");
	mysql_store_result();
	for(new x; x<=mysql_num_rows();++x)
	{
		mysql_fetch_row(LoadStr,"|");
		sscanf(LoadStr, "p<|>dds[500]s[64]",Zag[x][Zid], Zag[x][nagroda], Zag[x][opis], Pos);
		sscanf(Pos, "p<,>a<f>[3]", Zag[x][Zpos]);
		
		printf("Zaladowano zagadke: %d - %d, %d, %f, %f, %f",x, Zag[x][Zid],Zag[x][nagroda], Zag[x][Zpos][0], Zag[x][Zpos][1], Zag[x][Zpos][2]);
	}
	mysql_free_result();
	
	return 1;
}

CMD:quest(playerid,params[])
{
	
	return 1;
}






stock zagadki_init()
{
	LoadZagadki();
	return 1;
}
