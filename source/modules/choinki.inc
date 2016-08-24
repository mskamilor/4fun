/*
	Autor: Lagowy
	23.12.2015
	Polski 4Fun Serwer
	www.4fun-serv.eu
*/

#define MAX_CHRISTMASS_TREE 200

enum e_ct
{
	IDch,
	Objectxdddd,
	Text3D: Labelch
};

new Christmass@Tree[MAX_CHRISTMASS_TREE][e_ct], ChristmassTreeCount;

LoadChristmassTree()
{
	for(new i; i < MAX_CHRISTMASS_TREE; i ++) Christmass@Tree[i][IDch] = -1;
	
	if(ChristmassTreeCount >= MAX_CHRISTMASS_TREE) return false;

	if(ChristmassTreeCount != 0)
	{
		for(new i; i != ChristmassTreeCount; i++) DestroyObject(Christmass@Tree[i][Objectxdddd]), Delete3DTextLabel(Christmass@Tree[i][Labelch]);
	}

	ChristmassTreeCount = 0;

	mysql_query("SELECT * FROM `Choinki` LIMIT "#MAX_CHRISTMASS_TREE"");
	mysql_store_result();

	if(!mysql_num_rows()) return mysql_free_result(), printf("Nie ma choinek do za³adowania!");

	new tmp[100], id, Float: x[3], text[60];
	while(mysql_fetch_row(tmp, "|"))
	{
	    sscanf(tmp, "p<|>dfffs[60]", id, x[0], x[1], x[2], text);

		format(tmp, sizeof(tmp), "%s\n\n"GOLD"ID: "YELLOW"%d", text, id);
		
		Christmass@Tree[IDch][IDch] = id;
		Christmass@Tree[IDch][Objectxdddd] = CreateObject(19076, x[0] - 5, x[1] + 5, x[2] - 1, 0.0, 0.0, 96.0);
		Christmass@Tree[IDch][Labelch] = Create3DTextLabel(tmp, 0x00FFFF00, x[0] - 5, x[1] + 5, x[2] + 4, 96.0, 0, 0);

	 	ChristmassTreeCount ++;
	}

	mysql_free_result();

	printf("Za³adowano %d Choinek!", ChristmassTreeCount);

	return true;
}

DeleteChristmassTree(id)
{
	if(Christmass@Tree[IDch][IDch] == -1) return false;

	DestroyObject(Christmass@Tree[IDch][Objectxdddd]);
	Delete3DTextLabel(Christmass@Tree[IDch][Labelch]);
	
	Christmass@Tree[IDch][IDch] = -1;
	ChristmassTreeCount --;
	
	m_query("DELETE FROM `Choinki` WHERE `id` = '%d'", id);
	
	LoadChristmassTree();
	
	return true;
}

CMD:createchoinka(playerid, cmdtext[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	
	Dialog_Show(playerid, TworzChoinke, DIALOG_STYLE_INPUT, "Tworzenie Choinki", "Wpisz tekst który ma byæ obok choinki\n\nMo¿na u¿ywaæ kolorów { 0080FF }", "Stwórz", "Anuluj");

	return 1;
}

CMD:deletechoinka(playerid, params[])
{
	RankAdmin(playerid, R_VICEHEADADMIN);
	
	new id;
	if(sscanf(params, "d", id)) return 1;

	switch(DeleteChristmassTree(id))
	{
	    case 0: SendClientMessage(playerid, COLOR_ERROR, "Nie ma takiej Choinki!");
	    case 1: SendClientMessage(playerid, COLOR_GREEN, "Choinka usuniêta!");
	}
	
	return 1;
}

Dialog:TworzChoinke(playerid, response, listitem, inputtext[])
{
	new Limit = !(ChristmassTreeCount >= MAX_CHRISTMASS_TREE);
  	//SendClientMessage(playerid, (Limit ? COLOR_ERROR : COLOR_GREEN), (Limit ? ("Choinka Utworzona!") : ("Nie mo¿na utworzyæ Choinki poniewa¿ jest ich za du¿o!")));

	if(!Limit) return 1;
		
	new Float:X[3];
	GetPlayerPos(playerid, X[0], X[1], X[2]);
		
    m_query("INSERT INTO `Choinki` (x, y, z, text) VALUES ('%f', '%f', '%f', '%s')", X[0], X[1], X[2], inputtext);
		
	return LoadChristmassTree();
}

Choinki_Init()
{
	m_query("CREATE TABLE IF NOT EXISTS `Choinki` (`id` int(5) NOT NULL AUTO_INCREMENT, `x` float NOT NULL, `y` float NOT NULL, `z` float NOT NULL, `text` varchar(60) NOT NULL, PRIMARY KEY (`id`)) ENGINE = InnoDB  DEFAULT CHARSET = latin1 AUTO_INCREMENT = 0;");

    LoadChristmassTree();
}
