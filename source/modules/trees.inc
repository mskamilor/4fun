

#define MAX_TREES	5000

#define TREE_OBJECT			776
#define TREE_COLOR			0xac7339FF
#define TREE_ROTATION		80.0	// Druga wartoœæ rotacji


enum TreesEnum
{
	tree_id,
	tree_owner,
	ownername[24],
	Float:tree_pos[3],
	percentage,
	object,
	Text3D:tlabel,
	lying
}
new Tree[MAX_TREES][TreesEnum];

new tHighestID;
//new Text3D: TreeTopLabel;
enum TreeSettings
{
	Time,
	DistanceBetween,
	TreePerPlayer,
	Enabled,
	Xp
}
new TreeS[TreeSettings];

new TreeTimer;

stock GetTreeOwner(tid,id)
{
	return Tree[tid][ownername];
}

stock LoadTrees()
{
	printf("LoadTrees() start %d",0);
	new LoadStr[256], Pos[128], labelStr[128];
	
	/*
		SQL query left join to players table and fetch nicksl.
		
		SELECT t.ID, t.owner, t.percentage, IFNULL( p.nick,  'Brak' ) pnicks, t.position
		FROM mreg_trees t
		LEFT JOIN mreg_players p ON p.id = t.owner
		WHERE collected =0
		LIMIT 0 , 30
	*/
	m_query("SELECT t.ID, t.owner, t.percentage, IFNULL( p.nick,  'Brak' ) pnicks, t.position FROM mreg_trees t LEFT JOIN mreg_players p ON p.id = t.owner WHERE collected =0");
	mysql_store_result();
	printf("num_rows: %d",mysql_num_rows());
	tHighestID = mysql_num_rows();
	for(new x; x<=mysql_num_rows();x++)
	{
			//mysql_data_seek(x);
			mysql_fetch_row(LoadStr,"|");
			sscanf(LoadStr, "p<|>ddds[24]s[128]",Tree[x][tree_id], Tree[x][tree_owner], Tree[x][percentage],Tree[x][ownername], Pos);
			sscanf(Pos, "p<,>a<f>[3]", Tree[x][tree_pos]);
			if(Tree[x][percentage] >= 100)
			{
				format(labelStr,128,"Drzewo u¿ytkownika: -\nGotowe do wycinki!");
			} else {
				format(labelStr,128,"Drzewo u¿ytkownika: -\n%d/100", Tree[x][percentage]);
			}	
			Tree[x][object] = CreateDynamicObject(TREE_OBJECT, Tree[x][tree_pos][0],Tree[x][tree_pos][1],Tree[x][tree_pos][2]-1,0,0,0);
			Tree[x][tlabel] = Create3DTextLabel(labelStr,TREE_COLOR,Tree[x][tree_pos][0],Tree[x][tree_pos][1],Tree[x][tree_pos][2],20.0,0,0);

			printf("[TREE LOADED]: %d - %d - %d - %s",Tree[x][tree_id], Tree[x][tree_owner], Tree[x][percentage], Pos);
			// += 1;
	}
	mysql_free_result();
	printf("LoadTrees() exit %d",0);
	return 1;
}

stock UpdateTreeObject(Treeid) //-17 Z = 0 percent. -1 Z = 100 percent.
{
	switch(Tree[Treeid][percentage])
	{
		case 0..10: {
			MoveDynamicObject(Tree[Treeid][object], Tree[Treeid][tree_pos][0]+0.002,Tree[Treeid][tree_pos][1]+0.002,Tree[Treeid][tree_pos][2]-17.0, 1.0, 0,0,0);
		}
		case 11..25: {
			MoveDynamicObject(Tree[Treeid][object], Tree[Treeid][tree_pos][0]+0.002,Tree[Treeid][tree_pos][1]+0.002,Tree[Treeid][tree_pos][2]-14.0, 1.0, 0,0,0);
		}
		case 26..40: {
			MoveDynamicObject(Tree[Treeid][object], Tree[Treeid][tree_pos][0]+0.002,Tree[Treeid][tree_pos][1]+0.002,Tree[Treeid][tree_pos][2]-11.0, 1.0, 0,0,0);
		}
		case 41..60: {
			MoveDynamicObject(Tree[Treeid][object], Tree[Treeid][tree_pos][0]+0.002,Tree[Treeid][tree_pos][1]+0.002,Tree[Treeid][tree_pos][2]-8.0, 1.0, 0,0,0);
		}
		case 61..80: {
			MoveDynamicObject(Tree[Treeid][object], Tree[Treeid][tree_pos][0]+0.002,Tree[Treeid][tree_pos][1]+0.002,Tree[Treeid][tree_pos][2]-5.0, 1.0, 0,0,0);
		}
		case 81..999: {
			MoveDynamicObject(Tree[Treeid][object], Tree[Treeid][tree_pos][0]+0.002,Tree[Treeid][tree_pos][1]+0.002,Tree[Treeid][tree_pos][2]-1.0, 1.0, 0,0,0);
		}
	}
	return 1;
}

stock CreateTree(owner,playerid, Float:sx, Float:sy, Float:sz)
{
	
	printf("[TREE]: createtree %d $f $f $f wykonuje",owner, sx, sy, sz);
	new treeid = tHighestID+1;
	new labelStr[128];
	tHighestID += 1;
	Tree[treeid][tree_owner] = owner;
	Tree[treeid][percentage] = 0;
	Tree[treeid][tree_pos][0] = sx;
	Tree[treeid][tree_pos][1] = sy;
	Tree[treeid][tree_pos][2] = sz;
	
	new CrtStr[356], postiion[128];
	format(postiion,128,"%0.2f,%0.2f,%0.2f",sx,sy,sz);
	format(CrtStr,356,"INSERT INTO `4fun_samp`.`mreg_trees` (`ID`, `owner`, `percentage`, `position`, `collected`) VALUES (NULL, '%d', '%d', '%s', '%d')",owner,0,postiion,0);
	mysql_query(CrtStr);
	
	format(Tree[treeid][ownername],24,"%s",playerNick(playerid));
	
	Tree[treeid][tree_id] = mysql_insert_id();
	
	format(labelStr,128,"Drzewo u¿ytkownika: %s\n0/100",Tree[treeid][ownername]);
	
	Tree[treeid][object] = CreateDynamicObject(TREE_OBJECT, Tree[treeid][tree_pos][0],Tree[treeid][tree_pos][1],Tree[treeid][tree_pos][2]-17,0,0,0);
	Tree[treeid][tlabel] = Create3DTextLabel(labelStr,TREE_COLOR,Tree[treeid][tree_pos][0],Tree[treeid][tree_pos][1],Tree[treeid][tree_pos][2],20.0,0,0);	
	
	printf("[TREE CREATED]: id: %d, owner: %d",Tree[treeid][tree_id],owner);
	return 1;
}

stock DestroyTree(id)
{
	printf("[TREE]: destroytree %d wykonuje",id);
	new dstr[256];
	format(dstr,256,"Update "prefix"_trees SET collected=1 where ID='%d' ",Tree[id][tree_id]);
	m_query(dstr);
	DestroyDynamicObject(Tree[id][object]);
	Delete3DTextLabel(Tree[id][tlabel]);
	Tree[id][tree_id] = -1;
	Tree[id][tree_owner] = -1;
	Tree[id][tree_pos][0] = -1;
	Tree[id][tree_pos][1] = -1;
	Tree[id][tree_pos][2] = -1;
	Tree[id][percentage] = -1;
	return printf("Zniszczone drzewo: %d",id);
}

stock LieDownTree(tID, pID)
{
	printf("[TREE]: liedowntree %d  %d wykonuje",tID, pID);
	switch(Tree[tID][lying])
	{
		case 0..10: {
			MoveDynamicObject(Tree[tID][object], Tree[tID][tree_pos][0]+0.002,Tree[tID][tree_pos][1]+0.002,Tree[tID][tree_pos][2]+0.002, 10.0, 0,10,0);
		}
		case 11..20: {
			MoveDynamicObject(Tree[tID][object], Tree[tID][tree_pos][0]+0.002,Tree[tID][tree_pos][1]+0.002,Tree[tID][tree_pos][2]+0.002, 10.0, 0,20,0);
		}
		case 21..30: {
			MoveDynamicObject(Tree[tID][object], Tree[tID][tree_pos][0]+0.002,Tree[tID][tree_pos][1]+0.002,Tree[tID][tree_pos][2]+0.002, 10.0, 0,30,0);
		}
		case 31..40: {
			MoveDynamicObject(Tree[tID][object], Tree[tID][tree_pos][0]+0.002,Tree[tID][tree_pos][1]+0.002,Tree[tID][tree_pos][2]+0.002, 10.0, 0,40,0);
		}
		case 41..50: {
			MoveDynamicObject(Tree[tID][object], Tree[tID][tree_pos][0]+0.002,Tree[tID][tree_pos][1]+0.002,Tree[tID][tree_pos][2]+0.002, 10.0, 0,50,0);
		}
		case 51..60: {
			MoveDynamicObject(Tree[tID][object], Tree[tID][tree_pos][0]+0.002,Tree[tID][tree_pos][1]+0.002,Tree[tID][tree_pos][2]+0.002, 10.0, 0,60,0);
		}
		case 61..70: {
			MoveDynamicObject(Tree[tID][object], Tree[tID][tree_pos][0]+0.002,Tree[tID][tree_pos][1]+0.002,Tree[tID][tree_pos][2]+0.002, 10.0, 0,70,0);			
		}
		case 71..9999: {
			MoveDynamicObject(Tree[tID][object], Tree[tID][tree_pos][0]+0.002,Tree[tID][tree_pos][1]+0.002,Tree[tID][tree_pos][2]+0.002, 10.0, 0,80,0);		
			DestroyTree(tID);
			GivePlayerScore(pID,100);
			SendClientMessage(pID,TREE_COLOR,"W³aœnie sci¹³eœ swoje drzewo. Zyskujesz {b}100 XP{/b}!");
			pInfo[pID][cut_tree]+=1;
			achievement(pID,7);
			//UpdateTopTree();
			
		}
	}
	Tree[tID][lying] += 3;
	
	printf("[TREE]: liedowntree %d  %d zakonczone",tID, pID);
	return 1;
}
/*
stock UpdateTopTree()
{
	new TopPlayer[5][56], trees[5], uStr[256];
	m_query("SELECT `cut_tree`,`nick` FROM `mreg_players` ORDER BY `cut_tree` DESC LIMIT 5");
	mysql_store_result();
	for(new x; x<=mysql_num_rows();x++)
	{
			mysql_fetch_row(uStr,"|");
			sscanf(uStr, "p<|>ds[56]",trees[x], TopPlayer[x]);
			printf("uStr: %s, top: %s",uStr, TopPlayer[x]);
	}
	new toplabelstr[300];
	format(toplabelstr,300,"Najwiêcej œciêtych drzew\n{e65c00}1{FFFFFF}. %s    {e65c00}%d\n{e65c00}2{FFFFFF}. %s    {e65c00}%d\n{e65c00}3{FFFFFF}. %s    {e65c00}%d\n{e65c00}4{FFFFFF}. %s    {e65c00}%d\n{e65c00}5{FFFFFF}. %s    {e65c00}%d\n",TopPlayer[0],trees[0],TopPlayer[1],trees[1],TopPlayer[2],trees[2],TopPlayer[3],trees[3],TopPlayer[4],trees[4]);
	Update3DTextLabelText(TreeTopLabel,0xFFFFFFFF,toplabelstr);
	return 1;
}
*/
new treesSaveTick;
stock SaveTrees()
{
	if(treesSaveTick > gettime()) return 0;
	treesSaveTick = gettime() + 60*5;
	printf("[TREE]: savetrees wykonuje");
	new tSaveStr[256];
	for(new x; x <=tHighestID; x++)
	{
		if(Tree[x][tree_id] != -1)
		{
			format(tSaveStr,sizeof(tSaveStr),"Update "prefix"_trees SET percentage='%d' where ID='%d' ",Tree[x][percentage], Tree[x][tree_id]);
			mysql_query(tSaveStr);
		}
	}
	printf("[TREE]: savetrees zakonczone");
	return 1;
}

forward UpdateTree();
public UpdateTree()
{
	printf("[TREE]: updatetree wykonuje ");
	new treeStr[170];
	for(new x=0; x <=tHighestID; x++)
	{
		if(Tree[x][tree_id] != -1)
		{
			if(Tree[x][percentage] >= 100)
			{
				format(treeStr,170,"Drzewo u¿ytkownika: %s\nGotowe do wycinki!\n\n{FFFFFF}ID: %d\nB_ID: %d", Tree[x][ownername], x,  Tree[x][tree_id]);
			} else {
				Tree[x][percentage] += 2;
				Tree[x][lying] = 0;
				format(treeStr,170,"Drzewo u¿ytkownika: %s\n%d/100\n\n{FFFFFF}ID: %d\nB_ID: %d",Tree[x][ownername], Tree[x][percentage], x, Tree[x][tree_id]);
				UpdateTreeObject(x);
			}
			Update3DTextLabelText(Tree[x][tlabel], TREE_COLOR, treeStr);
		}
	}
	SaveTrees();
	printf("[TREE]: updatetree zakonczone ");
	return 1;
}

CMD:drwal(playerid,params[])
{
	new dStr[1000];
	strcat(dStr,"{FFFFFF}[===============================================] DRWAL [===============================================]\n\n\n");
	strcat(dStr,"Myœla³eœ kiedyœ o tym ¿eby posadziæ w³asne drzewo? Teraz mo¿esz to zrobiæ.\nTeleportuj siê na polane komend¹ /polana\n");
	strcat(dStr,"Nastêpnie znajdŸ dogodne miejsce na twoje drzewo na polu w strefie bez-dm obok teleportu /polana\n\n");
	strcat(dStr,"Teraz wpisz komendê /posadz i czekaj a¿ twoje drzewo uroœnie!\nGdy drzewo osi¹gnie 100/100 punktów mo¿na je wtedy œci¹æ.\n");
	strcat(dStr,"Aby œci¹æ drzewo wystarczy, ¿e staniesz obok niego z pi³¹ mechaniczn¹ i bêdziesz naciska³ lewy przycisk myszy.\n");
	strcat(dStr,"Gdy drzewo zostanie œciête zostaniesz nagrodzony 100 XP\n\nŒciêcie 150 drzew daje nam osi¹gniêcie `Drwal` oraz rangê (/ranga) Drwal");
	
	Dialog_Show(playerid,DIALOG_DRWALINF,DIALOG_STYLE_MSGBOX,"Drwal",dStr,"OK","");
	return 1;
}


CMD:posadz(playerid,params[]) //odleglosc 1,5m
{
	printf("[TREE]: posadz %s wykonuje ",params);
	if(TreeS[Enabled] == 2)return SendClientMessage(playerid,COLOR_ERROR,"Komenda wy³¹czona przez Administratora.");
	if(!IsPlayerInArea(playerid,1004.25, 910.701, -283.491, -386.749))return SendClientMessage(playerid,COLOR_ERROR,"Musisz znajdowaæ siê na polu w pobli¿u /polana w strefie bez dm.");
	if(GetPlayerScore(playerid) < 25)return SendClientMessage(playerid,COLOR_ERROR,"Potrzebujesz 25XP ¿eby posadziæ drzewo.");
	if(!pInfo[playerid][player_register])return SendClientMessage(playerid,COLOR_ERROR,"¯eby posadziæ drzewo musisz siê zarejestrowaæ! /register");
	
	new CrtStr[356];
	format(CrtStr,356,"SELECT ID FROM "prefix"_trees WHERE `owner` = '%d' AND `collected`=0",pInfo[playerid][player_id]);
	m_query(CrtStr);
	mysql_store_result();
	if(mysql_num_rows() >= 10)return SendClientMessage(playerid,COLOR_ERROR,"Mo¿esz posiadaæ maksymalnie 10 drzew.");
	
	for(new x; x <= tHighestID; x++)
	{
		if(IsPlayerInRangeOfPoint(playerid,2.5,Tree[x][tree_pos][0],Tree[x][tree_pos][1],Tree[x][tree_pos][2]))return SendClientMessage(playerid,COLOR_ERROR,"Jesteœ zbyt blisko innego drzewa. Minimalny odstêp do 2,5 metra.");
	}
	new Float:tPos[3];
	GetPlayerPos(playerid,tPos[0], tPos[1], tPos[2]);
	CreateTree(pInfo[playerid][player_id],playerid, tPos[0], tPos[1], tPos[2]);
	GivePlayerScore(playerid,-25);
	SendClientMessage(playerid,TREE_COLOR,"Posadzi³eœ drzewo! {b}( -25XP ){/b} Czekaj teraz a¿ uroœnie i zetnij je pi³¹ mechaniczn¹");
	printf("[TREE]: posadz %s zakonczone ",params);
	return 1;
}

stock trees_init()
{
	LoadSettings();
	LoadTrees();
	//TreeTopLabel = Create3DTextLabel("_",0xFFFFFFFF,2157.3406,979.2410,12.8125,7.0,0,1);
//	UpdateTopTree();
	new tt = 1000*TreeS[Time];
	printf("Tree Timer: %d",tt);
	TreeTimer = SetTimer("UpdateTree",tt,1);
	return 1;
}


stock trees_exit()
{
	return 1;
}

stock LoadSettings()
{
	new Settings[256];
	m_query("SELECT Time,DistanceBetween,TreePerPlayer,Enabled,Xp FROM "prefix"_trees_settings LIMIT 1");
	mysql_store_result();
	for(new x; x<mysql_num_rows();x++)
	{
			mysql_fetch_row(Settings,"|");
			sscanf(Settings, "p<|>ddddd",TreeS[Time], TreeS[DistanceBetween], TreeS[TreePerPlayer], TreeS[Enabled], TreeS[Xp]);
			printf("[TREE SETTINGS LOADED]: %d - %d - %d - %d - %d",TreeS[Time], TreeS[DistanceBetween], TreeS[TreePerPlayer], TreeS[Enabled], TreeS[Xp]);
	}
	mysql_free_result();
	return 1;
}


stock OnSettingsChange(player, id, value)
{
	switch(id)
	{
		case 1: { // Time
			KillTimer(TreeTimer);
			new tt = 1000*TreeS[Time];
		}
		case 2: { // DistanceBetween
			
		}
		case 3: { // Treeperplayer
		
			
		}
		case 4: { //Enabled
			
		}
		case 5: { // XP
			
		}
	}
	TreeTimer = SetTimer("UpdateTree",tt,1);
	return printf("[TREE SETTINGS CHANGE]: %s - %s - %s",playerNick(playerid),id,value);
}