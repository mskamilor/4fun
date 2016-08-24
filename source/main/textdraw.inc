/*
          Textdraws 4.0
      (c) Copyright 2013-2014 by mrdrifter, Game
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
				   Game (http://4fun-serv.pl/)
	  @date      : 16 listopada 2013
	  @update    : 3 stycznia 2014
  
 */ 
 
new Text:TimeTD;
new Text:DateTD;
new PlayerText:CzasGry[MAX_PLAYERS];
new Text:EnterExitTD[7];
 
stock PlayerText_Create(playerid)
{
 
	//format(string2, sizeof(string2), "%s (%d)", SetTextdrawGranient(pInfo[playerid][player_name], strlen(pInfo[playerid][player_name]), "~b~"), playerid);
 	
	
	for(new i;i<MAX_PLAYER_TEXT_DRAWS;i++) PlayerTextDrawDestroy(playerid, PlayerText:i);
	GangSparTd[0][playerid] = CreatePlayerTextDraw(playerid, 147.199966, 136.639999, "Polish Warriors");
	PlayerTextDrawLetterSize(playerid, GangSparTd[0][playerid], 0.293998, 1.786666);
	PlayerTextDrawAlignment(playerid, GangSparTd[0][playerid], 1);
	PlayerTextDrawColor(playerid, GangSparTd[0][playerid], -2139062017);
	PlayerTextDrawSetShadow(playerid, GangSparTd[0][playerid], 0);
	PlayerTextDrawSetOutline(playerid, GangSparTd[0][playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, GangSparTd[0][playerid], 51);
	PlayerTextDrawFont(playerid, GangSparTd[0][playerid], 3);
	PlayerTextDrawSetProportional(playerid, GangSparTd[0][playerid], 1);

	GangSparTd[1][playerid] = CreatePlayerTextDraw(playerid, 312.800048, 133.653396, "5-0");
	PlayerTextDrawLetterSize(playerid, GangSparTd[1][playerid], 0.910000, 3.354665);
	PlayerTextDrawAlignment(playerid, GangSparTd[1][playerid], 2);
	PlayerTextDrawColor(playerid, GangSparTd[1][playerid], -65281);
	PlayerTextDrawSetShadow(playerid, GangSparTd[1][playerid], 0);
	PlayerTextDrawSetOutline(playerid, GangSparTd[1][playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, GangSparTd[1][playerid], 51);
	PlayerTextDrawFont(playerid, GangSparTd[1][playerid], 3);
	PlayerTextDrawSetProportional(playerid, GangSparTd[1][playerid], 1);

	GangSparTd[2][playerid] = CreatePlayerTextDraw(playerid, 479.199951, 137.906646, "Polish warrios eee xd");
	PlayerTextDrawLetterSize(playerid, GangSparTd[2][playerid], 0.293998, 1.786666);
	PlayerTextDrawAlignment(playerid, GangSparTd[2][playerid], 3);
	PlayerTextDrawColor(playerid, GangSparTd[2][playerid], -2139062017);
	PlayerTextDrawSetShadow(playerid, GangSparTd[2][playerid], 0);
	PlayerTextDrawSetOutline(playerid, GangSparTd[2][playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, GangSparTd[2][playerid], 51);
	PlayerTextDrawFont(playerid, GangSparTd[2][playerid], 3);
	PlayerTextDrawSetProportional(playerid, GangSparTd[2][playerid], 1);

	GangSparTd[3][playerid] = CreatePlayerTextDraw(playerid, 147.199905, 186.666641, "mrdrifter~n~mrdrifter~n~mrdrifter~n~mrdrifter~n~mrdrifter~n~mrdrifter~n~mrdrifter~n~");
	PlayerTextDrawLetterSize(playerid, GangSparTd[3][playerid], 0.182797, 1.099732);
	PlayerTextDrawAlignment(playerid, GangSparTd[3][playerid], 1);
	PlayerTextDrawColor(playerid, GangSparTd[3][playerid], -1);
	PlayerTextDrawSetShadow(playerid, GangSparTd[3][playerid], 0);
	PlayerTextDrawSetOutline(playerid, GangSparTd[3][playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, GangSparTd[3][playerid], 51);
	PlayerTextDrawFont(playerid, GangSparTd[3][playerid], 1);
	PlayerTextDrawSetProportional(playerid, GangSparTd[3][playerid], 1);

	GangSparTd[4][playerid] = CreatePlayerTextDraw(playerid, 211.199905, 184.199951, "50~n~10~n~50~n~10~n~50~n~10~n~50~n~10~n~");
	PlayerTextDrawLetterSize(playerid, GangSparTd[4][playerid], 0.182797, 1.099732);
	PlayerTextDrawAlignment(playerid, GangSparTd[4][playerid], 1);
	PlayerTextDrawColor(playerid, GangSparTd[4][playerid], -1);
	PlayerTextDrawSetShadow(playerid, GangSparTd[4][playerid], 0);
	PlayerTextDrawSetOutline(playerid, GangSparTd[4][playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, GangSparTd[4][playerid], 51);
	PlayerTextDrawFont(playerid, GangSparTd[4][playerid], 1);
	PlayerTextDrawSetProportional(playerid, GangSparTd[4][playerid], 1);

	GangSparTd[5][playerid] = CreatePlayerTextDraw(playerid, 251.199890, 185.466644, "50~n~10~n~50~n~10~n~50~n~10~n~50~n~10~n~");
	PlayerTextDrawLetterSize(playerid, GangSparTd[5][playerid], 0.182797, 1.099732);
	PlayerTextDrawAlignment(playerid, GangSparTd[5][playerid], 1);
	PlayerTextDrawColor(playerid, GangSparTd[5][playerid], -1);
	PlayerTextDrawSetShadow(playerid, GangSparTd[5][playerid], 0);
	PlayerTextDrawSetOutline(playerid, GangSparTd[5][playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, GangSparTd[5][playerid], 51);
	PlayerTextDrawFont(playerid, GangSparTd[5][playerid], 1);
	PlayerTextDrawSetProportional(playerid, GangSparTd[5][playerid], 1);

	GangSparTd[6][playerid] = CreatePlayerTextDraw(playerid, 411.199890, 186.733276, "50~n~10~n~50~n~10~n~50~n~10~n~50~n~10~n~");
	PlayerTextDrawLetterSize(playerid, GangSparTd[6][playerid], 0.182797, 1.099732);
	PlayerTextDrawAlignment(playerid, GangSparTd[6][playerid], 1);
	PlayerTextDrawColor(playerid, GangSparTd[6][playerid], -1);
	PlayerTextDrawSetShadow(playerid, GangSparTd[6][playerid], 0);
	PlayerTextDrawSetOutline(playerid, GangSparTd[6][playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, GangSparTd[6][playerid], 51);
	PlayerTextDrawFont(playerid, GangSparTd[6][playerid], 1);
	PlayerTextDrawSetProportional(playerid, GangSparTd[6][playerid], 1);

	GangSparTd[7][playerid] = CreatePlayerTextDraw(playerid, 463.199890, 187.999923, "50~n~10~n~50~n~10~n~50~n~10~n~50~n~10~n~");
	PlayerTextDrawLetterSize(playerid, GangSparTd[7][playerid], 0.182797, 1.099732);
	PlayerTextDrawAlignment(playerid, GangSparTd[7][playerid], 1);
	PlayerTextDrawColor(playerid, GangSparTd[7][playerid], -1);
	PlayerTextDrawSetShadow(playerid, GangSparTd[7][playerid], 0);
	PlayerTextDrawSetOutline(playerid, GangSparTd[7][playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, GangSparTd[7][playerid], 51);
	PlayerTextDrawFont(playerid, GangSparTd[7][playerid], 1);
	PlayerTextDrawSetProportional(playerid, GangSparTd[7][playerid], 1);

	GangSparTd[8][playerid] = CreatePlayerTextDraw(playerid, 347.199890, 187.933273, "mrdrifter~n~mrdrifter~n~mrdrifter~n~mrdrifter~n~mrdrifter~n~mrdrifter~n~mrdrifter~n~");
	PlayerTextDrawLetterSize(playerid, GangSparTd[8][playerid], 0.182797, 1.099732);
	PlayerTextDrawAlignment(playerid, GangSparTd[8][playerid], 1);
	PlayerTextDrawColor(playerid, GangSparTd[8][playerid], -1);
	PlayerTextDrawSetShadow(playerid, GangSparTd[8][playerid], 0);
	PlayerTextDrawSetOutline(playerid, GangSparTd[8][playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, GangSparTd[8][playerid], 51);
	PlayerTextDrawFont(playerid, GangSparTd[8][playerid], 1);
	PlayerTextDrawSetProportional(playerid, GangSparTd[8][playerid], 1);
/*
	pInfo[playerid][player_TdNick] = CreatePlayerTextDraw(playerid, 4.031477, 432.667053, splitf("%s (%d)", playerNick(playerid), playerid));
	PlayerTextDrawLetterSize(playerid, pInfo[playerid][player_TdNick], 0.298500, 1.007500);
	PlayerTextDrawAlignment(playerid, pInfo[playerid][player_TdNick], 1);
	PlayerTextDrawColor(playerid, pInfo[playerid][player_TdNick], 520093824);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_TdNick], 0);
	PlayerTextDrawSetOutline(playerid, pInfo[playerid][player_TdNick], 0);
	PlayerTextDrawBackgroundColor(playerid, pInfo[playerid][player_TdNick], 520093840);
	PlayerTextDrawFont(playerid, pInfo[playerid][player_TdNick], 1);
	PlayerTextDrawSetProportional(playerid, pInfo[playerid][player_TdNick], 1);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_TdNick], 0);
*/
	pInfo[playerid][player_TdStats][0] = CreatePlayerTextDraw(playerid, 319.222167, 427.591247, splitf("%d' %s", playerid, playerNick(playerid)));
	PlayerTextDrawLetterSize(playerid, pInfo[playerid][player_TdStats][0], 0.377999, 1.614933);
	PlayerTextDrawAlignment(playerid, pInfo[playerid][player_TdStats][0], 2);
	PlayerTextDrawColor(playerid, pInfo[playerid][player_TdStats][0], -1);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_TdStats][0], 0);
	PlayerTextDrawSetOutline(playerid, pInfo[playerid][player_TdStats][0], -1);
	PlayerTextDrawBackgroundColor(playerid, pInfo[playerid][player_TdStats][0], 80);
	PlayerTextDrawFont(playerid, pInfo[playerid][player_TdStats][0], 1);
	PlayerTextDrawSetProportional(playerid, pInfo[playerid][player_TdStats][0], 1);

	pInfo[playerid][player_TdStats][1] = CreatePlayerTextDraw(playerid, 20.444429, 435.555694, "5262");
	PlayerTextDrawLetterSize(playerid, pInfo[playerid][player_TdStats][1], 0.178000, 1.009999);
	PlayerTextDrawAlignment(playerid, pInfo[playerid][player_TdStats][1], 2);
	PlayerTextDrawColor(playerid, pInfo[playerid][player_TdStats][1], -1);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_TdStats][1], 1);
	PlayerTextDrawSetOutline(playerid, pInfo[playerid][player_TdStats][1], 0);
	PlayerTextDrawBackgroundColor(playerid, pInfo[playerid][player_TdStats][1], 80);
	PlayerTextDrawFont(playerid, pInfo[playerid][player_TdStats][1], 2);
	PlayerTextDrawSetProportional(playerid, pInfo[playerid][player_TdStats][1], 1);

	CzasGry[playerid] = CreatePlayerTextDraw(playerid, 502.333404, 99.140754, "Czas gry: 01H 12M");
	PlayerTextDrawLetterSize(playerid, CzasGry[playerid], 0.196666, 1.122962);
	PlayerTextDrawAlignment(playerid, CzasGry[playerid], 1);
	PlayerTextDrawColor(playerid, CzasGry[playerid], -1);
	PlayerTextDrawSetShadow(playerid, CzasGry[playerid], 0);
	PlayerTextDrawSetOutline(playerid, CzasGry[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, CzasGry[playerid], 51);
	PlayerTextDrawFont(playerid, CzasGry[playerid], 1);
	PlayerTextDrawSetProportional(playerid, CzasGry[playerid], 1);

	pInfo[playerid][player_TdStats][2] = CreatePlayerTextDraw(playerid, 154.333282, 435.555541, "120140620/150250310");
	PlayerTextDrawLetterSize(playerid, pInfo[playerid][player_TdStats][2], 0.178000, 1.009999);
	PlayerTextDrawAlignment(playerid, pInfo[playerid][player_TdStats][2], 2);
	PlayerTextDrawColor(playerid, pInfo[playerid][player_TdStats][2], -1);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_TdStats][2], 1);
	PlayerTextDrawSetOutline(playerid, pInfo[playerid][player_TdStats][2], 0);
	PlayerTextDrawBackgroundColor(playerid, pInfo[playerid][player_TdStats][2], 80);
	PlayerTextDrawFont(playerid, pInfo[playerid][player_TdStats][2], 2);
	PlayerTextDrawSetProportional(playerid, pInfo[playerid][player_TdStats][2], 1);

	pInfo[playerid][player_TdStats][3] = CreatePlayerTextDraw(playerid, 67.222213, 435.555572, "~y~0~w~pln");
	PlayerTextDrawLetterSize(playerid, pInfo[playerid][player_TdStats][3], 0.178000, 1.009999);
	PlayerTextDrawAlignment(playerid, pInfo[playerid][player_TdStats][3], 2);
	PlayerTextDrawColor(playerid, pInfo[playerid][player_TdStats][3], -1);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_TdStats][3], 1);
	PlayerTextDrawSetOutline(playerid, pInfo[playerid][player_TdStats][3], 0);
	PlayerTextDrawBackgroundColor(playerid, pInfo[playerid][player_TdStats][3], 80);
	PlayerTextDrawFont(playerid, pInfo[playerid][player_TdStats][3], 2);
	PlayerTextDrawSetProportional(playerid, pInfo[playerid][player_TdStats][3], 1);

	pInfo[playerid][player_TdStats][4] = CreatePlayerTextDraw(playerid, 464.666534, 435.555786, "~r~~h~~h~300 ~w~/ ~y~~h~200 ~w~/ ~g~~h~100");//zabic itp
	PlayerTextDrawLetterSize(playerid, pInfo[playerid][player_TdStats][4], 0.178000, 1.009999);
	PlayerTextDrawAlignment(playerid, pInfo[playerid][player_TdStats][4], 2);
	PlayerTextDrawColor(playerid, pInfo[playerid][player_TdStats][4], -1);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_TdStats][4], 1);
	PlayerTextDrawSetOutline(playerid, pInfo[playerid][player_TdStats][4], 0);
	PlayerTextDrawBackgroundColor(playerid, pInfo[playerid][player_TdStats][4], 80);
	PlayerTextDrawFont(playerid, pInfo[playerid][player_TdStats][4], 2);
	PlayerTextDrawSetProportional(playerid, pInfo[playerid][player_TdStats][4], 1);

	pInfo[playerid][player_TdStats][5] = CreatePlayerTextDraw(playerid, 590.666687, 435.555603, "0.00 / ~y~~h~90 ~w~/ ~p~~h~68ms");
	PlayerTextDrawLetterSize(playerid, pInfo[playerid][player_TdStats][5], 0.178000, 1.009999);
	PlayerTextDrawAlignment(playerid, pInfo[playerid][player_TdStats][5], 2);
	PlayerTextDrawColor(playerid, pInfo[playerid][player_TdStats][5], -858993409);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_TdStats][5], 1);
	PlayerTextDrawSetOutline(playerid, pInfo[playerid][player_TdStats][5], 0);
	PlayerTextDrawBackgroundColor(playerid, pInfo[playerid][player_TdStats][5], 80);
	PlayerTextDrawFont(playerid, pInfo[playerid][player_TdStats][5], 2);
	PlayerTextDrawSetProportional(playerid, pInfo[playerid][player_TdStats][5], 1);
	 
	for(new i=1;i<6;i++)
		PlayerTextDrawSetString2(playerid, pInfo[playerid][player_TdStats][i], "~r~---");


	pInfo[playerid][player_TdAnn][0] = CreatePlayerTextDraw(playerid, 285.500000, 381.467315, "Derby");
	PlayerTextDrawLetterSize(playerid, pInfo[playerid][player_TdAnn][0], 0.453000, 1.780833);
	PlayerTextDrawAlignment(playerid, pInfo[playerid][player_TdAnn][0], 1);
	PlayerTextDrawColor(playerid, pInfo[playerid][player_TdAnn][0], -1);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_TdAnn][0], 0);
	PlayerTextDrawSetOutline(playerid, pInfo[playerid][player_TdAnn][0], 1);
	PlayerTextDrawBackgroundColor(playerid, pInfo[playerid][player_TdAnn][0], 32);
	PlayerTextDrawFont(playerid, pInfo[playerid][player_TdAnn][0], 0);
	PlayerTextDrawSetProportional(playerid, pInfo[playerid][player_TdAnn][0], 1);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_TdAnn][0], 0);

	pInfo[playerid][player_TdAnn][1] = CreatePlayerTextDraw(playerid, 290.000000, 400.717315, "Startuje za ~r~5~w~s");
	PlayerTextDrawLetterSize(playerid, pInfo[playerid][player_TdAnn][1], 0.210500, 1.063331);
	PlayerTextDrawAlignment(playerid, pInfo[playerid][player_TdAnn][1], 1);
	PlayerTextDrawColor(playerid, pInfo[playerid][player_TdAnn][1], -1);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_TdAnn][1], 0);
	PlayerTextDrawSetOutline(playerid, pInfo[playerid][player_TdAnn][1], 1);
	PlayerTextDrawBackgroundColor(playerid, pInfo[playerid][player_TdAnn][1], 32);
	PlayerTextDrawFont(playerid, pInfo[playerid][player_TdAnn][1], 1);
	PlayerTextDrawSetProportional(playerid, pInfo[playerid][player_TdAnn][1], 1);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_TdAnn][1], 0);
 

	pInfo[playerid][player_achievement] = CreatePlayerTextDraw(playerid, 199.000000, 269.422241, "~y~Nowe osiagniecie! ~n~~w~~h~Dosc Tego!");
	PlayerTextDrawLetterSize(playerid, pInfo[playerid][player_achievement], 0.209998, 0.822221);
	PlayerTextDrawTextSize(playerid, pInfo[playerid][player_achievement], -8.500000, -428.711364);
	PlayerTextDrawAlignment(playerid, pInfo[playerid][player_achievement], 3);
	PlayerTextDrawColor(playerid, pInfo[playerid][player_achievement], -1);
	PlayerTextDrawUseBox(playerid, pInfo[playerid][player_achievement], true);
	PlayerTextDrawBoxColor(playerid, pInfo[playerid][player_achievement], 96);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_achievement], 0);
	PlayerTextDrawSetOutline(playerid, pInfo[playerid][player_achievement], 1);
	PlayerTextDrawBackgroundColor(playerid, pInfo[playerid][player_achievement], 51);
	PlayerTextDrawFont(playerid, pInfo[playerid][player_achievement], 1);
	PlayerTextDrawSetProportional(playerid, pInfo[playerid][player_achievement], 1);
 
	GangZoneDraw = CreatePlayerTextDraw(playerid, 82.194664, 315.214447, "Strefa Gangu:~n~ZwR");
	PlayerTextDrawLetterSize(playerid, GangZoneDraw, 0.237222, 1.233952);
	PlayerTextDrawAlignment(playerid, GangZoneDraw, 2);
	PlayerTextDrawColor(playerid, GangZoneDraw, -1);
	PlayerTextDrawSetShadow(playerid, GangZoneDraw, 0);
	PlayerTextDrawSetOutline(playerid, GangZoneDraw, 1);
	PlayerTextDrawBackgroundColor(playerid, GangZoneDraw, 255);
	PlayerTextDrawFont(playerid, GangZoneDraw, 1);
	PlayerTextDrawSetProportional(playerid, GangZoneDraw, 1);

	// In OnPlayerConnect prefferably, we procced to create our textdraws:
	SelectSkin_[0] = CreatePlayerTextDraw(playerid,115.000000 - 10.0, 123.000000, "511");
	PlayerTextDrawBackgroundColor(playerid,SelectSkin_[0], 0);
	PlayerTextDrawFont(playerid,SelectSkin_[0], 5);
	PlayerTextDrawLetterSize(playerid,SelectSkin_[0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,SelectSkin_[0], -1);
	PlayerTextDrawSetOutline(playerid,SelectSkin_[0], 0);
	PlayerTextDrawSetProportional(playerid,SelectSkin_[0], 1);
	PlayerTextDrawSetShadow(playerid,SelectSkin_[0], 1);
	PlayerTextDrawUseBox(playerid,SelectSkin_[0], 1);
	PlayerTextDrawBoxColor(playerid,SelectSkin_[0], 0);
	PlayerTextDrawTextSize(playerid,SelectSkin_[0], 130.000000, 189.000000);
	PlayerTextDrawSetPreviewModel(playerid, SelectSkin_[0], 297);
	PlayerTextDrawSetPreviewRot(playerid, SelectSkin_[0], 0.000000, 0.000000, 10.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,SelectSkin_[0], 1);

	SelectSkin_[1] = CreatePlayerTextDraw(playerid,242.000000, 149.000000, "?rodkowy");
	PlayerTextDrawBackgroundColor(playerid,SelectSkin_[1], 0);
	PlayerTextDrawFont(playerid,SelectSkin_[1], 5);
	PlayerTextDrawLetterSize(playerid,SelectSkin_[1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,SelectSkin_[1], -1);
	PlayerTextDrawSetOutline(playerid,SelectSkin_[1], 0);
	PlayerTextDrawSetProportional(playerid,SelectSkin_[1], 1);
	PlayerTextDrawSetShadow(playerid,SelectSkin_[1], 1);
	PlayerTextDrawUseBox(playerid,SelectSkin_[1], 1);
	PlayerTextDrawBoxColor(playerid,SelectSkin_[1], 0);
	PlayerTextDrawTextSize(playerid,SelectSkin_[1], 130.000000, 189.000000);
	PlayerTextDrawSetPreviewModel(playerid, SelectSkin_[1], 0);
	PlayerTextDrawSetPreviewRot(playerid, SelectSkin_[1], 0.000000, 0.000000, -5.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,SelectSkin_[1], 1);

	SelectSkin_[2] = CreatePlayerTextDraw(playerid,364.000000 + 10.0, 123.000000, "trzeci");
	PlayerTextDrawBackgroundColor(playerid,SelectSkin_[2], 0);
	PlayerTextDrawFont(playerid,SelectSkin_[2], 5);
	PlayerTextDrawLetterSize(playerid,SelectSkin_[2], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,SelectSkin_[2], -1);
	PlayerTextDrawSetOutline(playerid,SelectSkin_[2], 0);
	PlayerTextDrawSetProportional(playerid,SelectSkin_[2], 1);
	PlayerTextDrawSetShadow(playerid,SelectSkin_[2], 1);
	PlayerTextDrawUseBox(playerid,SelectSkin_[2], 1);
	PlayerTextDrawBoxColor(playerid,SelectSkin_[2], 0);
	PlayerTextDrawTextSize(playerid,SelectSkin_[2], 130.000000, 189.000000);
	PlayerTextDrawSetPreviewModel(playerid, SelectSkin_[2], 297);
	PlayerTextDrawSetPreviewRot(playerid, SelectSkin_[2], 10.000000, 0.000000, -11.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,SelectSkin_[2], 1);
	
	SelectSkin_[3] = CreatePlayerTextDraw(playerid,523.000000, 244.000000, "/mojskin");
	PlayerTextDrawBackgroundColor(playerid,SelectSkin_[3], 0);
	PlayerTextDrawFont(playerid,SelectSkin_[3], 5);
	PlayerTextDrawLetterSize(playerid,SelectSkin_[3], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,SelectSkin_[3], -1);
	PlayerTextDrawSetOutline(playerid,SelectSkin_[3], 0);
	PlayerTextDrawSetProportional(playerid,SelectSkin_[3], 1);
	PlayerTextDrawSetShadow(playerid,SelectSkin_[3], 1);
	PlayerTextDrawUseBox(playerid,SelectSkin_[3], 1);
	PlayerTextDrawBoxColor(playerid,SelectSkin_[3], 0);
	PlayerTextDrawTextSize(playerid,SelectSkin_[3], 150.000000, 189.000000);
	PlayerTextDrawSetPreviewModel(playerid, SelectSkin_[3], 297);
	PlayerTextDrawSetPreviewRot(playerid, SelectSkin_[3], 10.000000, 0.000000, -11.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,SelectSkin_[3], 1);

	SelectSkin_[4] = CreatePlayerTextDraw(playerid, 181.500000, 308.622253, "25");
	PlayerTextDrawLetterSize(playerid, SelectSkin_[4], 0.449999, 1.600000);
	PlayerTextDrawAlignment(playerid, SelectSkin_[4], 1);
	PlayerTextDrawColor(playerid, SelectSkin_[4], 572661584);
	PlayerTextDrawSetShadow(playerid, SelectSkin_[4], 0);
	PlayerTextDrawSetOutline(playerid, SelectSkin_[4], 1);
	PlayerTextDrawBackgroundColor(playerid, SelectSkin_[4], 572661520);
	PlayerTextDrawFont(playerid, SelectSkin_[4], 1);
	PlayerTextDrawSetProportional(playerid, SelectSkin_[4], 1);

	SelectSkin_[5] = CreatePlayerTextDraw(playerid, 305.000000, 332.266723, "25");
	PlayerTextDrawLetterSize(playerid, SelectSkin_[5], 0.449999, 1.600000);
	PlayerTextDrawAlignment(playerid, SelectSkin_[5], 1);
	PlayerTextDrawColor(playerid, SelectSkin_[5], 572661584);
	PlayerTextDrawSetShadow(playerid, SelectSkin_[5], 0);
	PlayerTextDrawSetOutline(playerid, SelectSkin_[5], 1);
	PlayerTextDrawBackgroundColor(playerid, SelectSkin_[5], 572661520);
	PlayerTextDrawFont(playerid, SelectSkin_[5], 1);
	PlayerTextDrawSetProportional(playerid, SelectSkin_[5], 1);

	SelectSkin_[6] = CreatePlayerTextDraw(playerid, 429.000000, 308.622253, "25");
	PlayerTextDrawLetterSize(playerid, SelectSkin_[6], 0.449999, 1.600000);
	PlayerTextDrawAlignment(playerid, SelectSkin_[6], 1);
	PlayerTextDrawColor(playerid, SelectSkin_[6], 572661584);
	PlayerTextDrawSetShadow(playerid, SelectSkin_[6], 0);
	PlayerTextDrawSetOutline(playerid, SelectSkin_[6], 1);
	PlayerTextDrawBackgroundColor(playerid, SelectSkin_[6], 572661520);
	PlayerTextDrawFont(playerid, SelectSkin_[6], 1);
	PlayerTextDrawSetProportional(playerid, SelectSkin_[6], 1);

    SelectSkin_[7] = CreatePlayerTextDraw(playerid, 248.500, 355.000, "LD_BEAT:left");
    PlayerTextDrawFont(playerid, SelectSkin_[7], 4);
    PlayerTextDrawTextSize(playerid, SelectSkin_[7], 28.000, 25.000);
    PlayerTextDrawColor(playerid, SelectSkin_[7], -1);

    SelectSkin_[8] = CreatePlayerTextDraw(playerid, 302.500, 356.500, "LD_BEAT:cross");
    PlayerTextDrawFont(playerid, SelectSkin_[8], 4);
    PlayerTextDrawTextSize(playerid, SelectSkin_[8], 22.000, 23.500);
    PlayerTextDrawColor(playerid, SelectSkin_[8], -1);

    SelectSkin_[9] = CreatePlayerTextDraw(playerid, 352.000, 355.000, "LD_BEAT:right");
    PlayerTextDrawFont(playerid, SelectSkin_[9], 4);
    PlayerTextDrawTextSize(playerid, SelectSkin_[9], 28.000, 25.000);
    PlayerTextDrawColor(playerid, SelectSkin_[9], -1);


	PlayerTextDrawSetSelectable(playerid,SelectSkin_[7], 1);
	PlayerTextDrawSetSelectable(playerid,SelectSkin_[8], 1);
	PlayerTextDrawSetSelectable(playerid,SelectSkin_[9], 1);
	/*
	playerdraw_respect = CreatePlayerTextDraw(playerid, 463.500000, 321.013153, "Respekt += 150");
	PlayerTextDrawLetterSize(playerid, playerdraw_respect, 0.308124, 3.475996);
	PlayerTextDrawAlignment(playerid, playerdraw_respect, 2);
	PlayerTextDrawColor(playerid, playerdraw_respect, 96);
	PlayerTextDrawSetShadow(playerid, playerdraw_respect, 1);
	PlayerTextDrawSetOutline(playerid, playerdraw_respect, 0);
	PlayerTextDrawBackgroundColor(playerid, playerdraw_respect, 255);
	PlayerTextDrawFont(playerid, playerdraw_respect, 2);
	PlayerTextDrawSetProportional(playerid, playerdraw_respect, 1);
	*/
	
	
	playerdraw_respect = CreatePlayerTextDraw(playerid, 124.000000, 417.634063, "Otrzymales raport! sprawdz go!");
	PlayerTextDrawLetterSize(playerid, playerdraw_respect, 0.214000, 0.958332);
	PlayerTextDrawAlignment(playerid, playerdraw_respect, 1);
	PlayerTextDrawColor(playerid, playerdraw_respect, -1);
	PlayerTextDrawSetShadow(playerid, playerdraw_respect, 0);
	PlayerTextDrawSetOutline(playerid, playerdraw_respect, 1);
	PlayerTextDrawBackgroundColor(playerid, playerdraw_respect, 32);
	PlayerTextDrawFont(playerid, playerdraw_respect, 1);
	PlayerTextDrawSetProportional(playerid, playerdraw_respect, 1);
	PlayerTextDrawSetShadow(playerid, playerdraw_respect, 0);

	 
	pInfo[playerid][player_TdLicznik][1]  = CreatePlayerTextDraw(playerid, 584.110351, 379.306762, "/bullet");
	PlayerTextDrawLetterSize(playerid, pInfo[playerid][player_TdLicznik][1] , 0.155777, 0.848353);
	PlayerTextDrawAlignment(playerid, pInfo[playerid][player_TdLicznik][1] , 2);
	PlayerTextDrawColor(playerid, pInfo[playerid][player_TdLicznik][1] , -1);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_TdLicznik][1] , 1);
	PlayerTextDrawSetOutline(playerid, pInfo[playerid][player_TdLicznik][1] , 0);
	PlayerTextDrawBackgroundColor(playerid, pInfo[playerid][player_TdLicznik][1] , 80);
	PlayerTextDrawFont(playerid, pInfo[playerid][player_TdLicznik][1] , 2);
	PlayerTextDrawSetProportional(playerid, pInfo[playerid][player_TdLicznik][1] , 1);

	pInfo[playerid][player_TdLicznik][3] = CreatePlayerTextDraw(playerid, 562.666564, 409.671203, "~g~~h~]]]]~l~]");
	PlayerTextDrawLetterSize(playerid, pInfo[playerid][player_TdLicznik][3], 0.277999, 1.072355);
	PlayerTextDrawAlignment(playerid, pInfo[playerid][player_TdLicznik][3], 1);
	PlayerTextDrawColor(playerid, pInfo[playerid][player_TdLicznik][3], -1);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_TdLicznik][3], 0);
	PlayerTextDrawSetOutline(playerid, pInfo[playerid][player_TdLicznik][3], -1);
	PlayerTextDrawBackgroundColor(playerid, pInfo[playerid][player_TdLicznik][3], 16);
	PlayerTextDrawFont(playerid, pInfo[playerid][player_TdLicznik][3], 2);
	PlayerTextDrawSetProportional(playerid, pInfo[playerid][player_TdLicznik][3], 1);

	pInfo[playerid][player_TdLicznik][0] = CreatePlayerTextDraw(playerid, 591.556579, 386.275543, "102");
	PlayerTextDrawLetterSize(playerid, pInfo[playerid][player_TdLicznik][0], 0.446444, 2.630398);
	PlayerTextDrawAlignment(playerid, pInfo[playerid][player_TdLicznik][0], 3);
	PlayerTextDrawColor(playerid, pInfo[playerid][player_TdLicznik][0], -1);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_TdLicznik][0], 0);
	PlayerTextDrawSetOutline(playerid, pInfo[playerid][player_TdLicznik][0], -1);
	PlayerTextDrawBackgroundColor(playerid, pInfo[playerid][player_TdLicznik][0], 51);
	PlayerTextDrawFont(playerid, pInfo[playerid][player_TdLicznik][0], 2);
	PlayerTextDrawSetProportional(playerid, pInfo[playerid][player_TdLicznik][0], 1);
	
	pInfo[playerid][player_TdLicznik][2] = CreatePlayerTextDraw(playerid, 556.000000, 395.117553, " ");
	PlayerTextDrawLetterSize(playerid, pInfo[playerid][player_TdLicznik][2], 0.196000, 0.736667);
	PlayerTextDrawAlignment(playerid, pInfo[playerid][player_TdLicznik][2], 1);
	PlayerTextDrawColor(playerid, pInfo[playerid][player_TdLicznik][2], -1);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_TdLicznik][2], 0);
	PlayerTextDrawSetOutline(playerid, pInfo[playerid][player_TdLicznik][2], 1);
	PlayerTextDrawBackgroundColor(playerid, pInfo[playerid][player_TdLicznik][2], 32);
	PlayerTextDrawFont(playerid, pInfo[playerid][player_TdLicznik][2], 1);
	PlayerTextDrawSetProportional(playerid, pInfo[playerid][player_TdLicznik][2], 1);
	PlayerTextDrawSetShadow(playerid, pInfo[playerid][player_TdLicznik][2], 0);
	
	


}

CMD:hud(playerid, params[])
{
	/*if(pInfo[playerid][player_hidehud][hud_all])
	{
		pInfo[playerid][player_hidehud][hud_all] = false;
		PlayerText_Stats(playerid, true);
		
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) PlayerText_Licznik(playerid, true);
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Pomyœlnie w³¹czy³eœ HUD");
	}
	else 
	{
		pInfo[playerid][player_hidehud][hud_all] = true;
		PlayerText_Stats(playerid, false);
		PlayerText_Licznik(playerid, false);
		
		SendClientMessage(playerid, COLOR_GREEN, ""chat" Pomyœlnie wy³¹czy³eœ HUD");
	}*/
	
	new str[512], tstate[][] = {"{00FF00}(ON)", "{FF0000}(OFF)"};
	
	
	strcat(str, splitf("%s Wszystkie textdrawy (pasek stanu, licznik)\n", tstate[pInfo[playerid][player_hidehud][hud_all]]));
	strcat(str, splitf("%s Pasek stanu\n", tstate[pInfo[playerid][player_hidehud][hud_pasek]]));
	strcat(str, splitf("%s Licznik\n", tstate[pInfo[playerid][player_hidehud][hud_licznik]]));
	strcat(str, splitf("%s Licznik FPS, Pingu i P-Loss\n", tstate[pInfo[playerid][player_hidehud][hud_fps]]));
	strcat(str, splitf("%s Lista cz³onków gangu\n", tstate[pInfo[playerid][player_hidehud][hud_gangmembers]]));
	strcat(str, splitf("%s Eventy\n", tstate[pInfo[playerid][player_hidehud][hud_events]]));
	strcat(str, splitf("%s Liczba Graczy\n", tstate[pInfo[playerid][player_hidehud][hud_onlinecount]]));
	
	Dialog_Show(playerid, HudSelect, DIALOG_STYLE_LIST, "• Textdraws » wybierz textdrawy •", str, "Prze³¹cz", "WyjdŸ");

	return 1;
}

Dialog:HudSelect(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new tstate[][] = {"{00FF00}(W³¹czy³eœ){/b}", "{FF0000}(Wy³¹czy³eœ){/b}"};
		
		switch( listitem )
		{
			case 0:
			{
			
				pInfo[playerid][player_hidehud][hud_all] = !pInfo[playerid][player_hidehud][hud_all];
				SendClientMessage(playerid, COLOR_INFO3, "* %s wszystkie textdrawy", tstate[pInfo[playerid][player_hidehud][hud_all]]);
			}
			case 1:
			{
			
				pInfo[playerid][player_hidehud][hud_pasek] = !pInfo[playerid][player_hidehud][hud_pasek];
				SendClientMessage(playerid, COLOR_INFO3, "* %s Pasek stanu", tstate[pInfo[playerid][player_hidehud][hud_pasek]]);
			}
			case 2:
			{
			
				pInfo[playerid][player_hidehud][hud_licznik] = !pInfo[playerid][player_hidehud][hud_licznik];
				SendClientMessage(playerid, COLOR_INFO3, "* %s Licznik", tstate[pInfo[playerid][player_hidehud][hud_licznik]]);
				
				
				PlayerText_Licznik(playerid, true);
			}	
			case 3:
			{
			
				pInfo[playerid][player_hidehud][hud_fps] = !pInfo[playerid][player_hidehud][hud_fps];
				SendClientMessage(playerid, COLOR_INFO3, "* %s Licznik FPS, Pingu i P-Loss", tstate[pInfo[playerid][player_hidehud][hud_fps]]);
			}			
			case 4:
			{
			
				pInfo[playerid][player_hidehud][hud_gangmembers] = !pInfo[playerid][player_hidehud][hud_gangmembers];
				SendClientMessage(playerid, COLOR_INFO3, "* %s Listê cz³onków gangu", tstate[pInfo[playerid][player_hidehud][hud_gangmembers]]);
			}	
			case 5:
			{
			
				pInfo[playerid][player_hidehud][hud_events] = !pInfo[playerid][player_hidehud][hud_events];
				SendClientMessage(playerid, COLOR_INFO3, "* %s textdraw z eventami", tstate[pInfo[playerid][player_hidehud][hud_events]]);
			}
			case 6:
			{
			
				pInfo[playerid][player_hidehud][hud_onlinecount] = !pInfo[playerid][player_hidehud][hud_onlinecount];
				SendClientMessage(playerid, COLOR_INFO3, "* %s Liczbe Graczy", tstate[pInfo[playerid][player_hidehud][hud_onlinecount]]);
			}
		}
		PlayerText_Stats(playerid, true);
		cmd_hud(playerid, "");
	}
	return 1;
}
stock PlayerText_Stats(playerid, bool: show)
{
	if(show)
	{
		TextDrawShowForPlayer(playerid,TimeTD);
		TextDrawShowForPlayer(playerid,DateTD);
		PlayerTextDrawShow(playerid,CzasGry[playerid]);
		if(pInfo[playerid][player_hidehud][hud_fps])
		{
			if(IsPlayerTextDrawShow(playerid, pInfo[playerid][player_TdStats][5])) PlayerTextDrawHide(playerid, pInfo[playerid][player_TdStats][5]); 
		} 
		else 
			PlayerTextDrawShow(playerid, pInfo[playerid][player_TdStats][5]); 

		if(pInfo[playerid][player_hidehud][hud_all]) return PlayerText_Stats(playerid, false);
		//PlayerTextDrawShow(playerid, pInfo[playerid][player_TdNick]);
		//PlayerTextDrawShow(playerid, pInfo[playerid][player_TextureSkin]);
	
		if(pInfo[playerid][player_hidehud][hud_pasek])
		{
			for(new i;i<6;i++)
			{
				if(!pInfo[playerid][player_hidehud][hud_fps])
				{
					if( i == 5 ) continue;
				}
				if(IsPlayerTextDrawShow(playerid, pInfo[playerid][player_TdStats][i])) PlayerTextDrawHide(playerid, pInfo[playerid][player_TdStats][i]); 
			}
			for(new i;i<11;i++)
			{
				if(!pInfo[playerid][player_hidehud][hud_fps])
					if( i == 8 ) continue;
				if(IsTextDrawShowForPlayer(playerid, PasekBelt[i])) TextDrawHideForPlayer(playerid, PasekBelt[i]); 
			}
		}
		else 
		{
			for(new i;i<6;i++)
			{
				if(pInfo[playerid][player_hidehud][hud_fps])
				{
					if( i == 5 ) continue;
				}
				
				PlayerTextDrawShow(playerid, pInfo[playerid][player_TdStats][i]); 
			}
			for(new i;i<11;i++)
			{
				if(pInfo[playerid][player_hidehud][hud_fps])
					if( i == 8 ) continue;
				TextDrawShowForPlayer(playerid, PasekBelt[i]); 
				for(new x; x < 7; x++)	
					TextDrawShowForPlayer(playerid, EnterExitTD[x]);
			}
			

		}
		
		if(pInfo[playerid][player_hidehud][hud_events])
		{
			if(IsTextDrawShowForPlayer(playerid, EventTD[0])) TextDrawHideForPlayer(playerid, EventTD[0]);
			if(IsTextDrawShowForPlayer(playerid, EventTD[1])) TextDrawHideForPlayer(playerid, EventTD[1]);
		}
		else 
		{
			TextDrawShowForPlayer(playerid, EventTD[0]);
			TextDrawShowForPlayer(playerid, EventTD[1]);
		}
		
		if(pInfo[playerid][player_hidehud][hud_onlinecount])
		{
			if(IsTextDrawShowForPlayer(playerid, OnlineBelt)) TextDrawHideForPlayer(playerid, OnlineBelt);
		}
		else 
		{
			TextDrawShowForPlayer(playerid, OnlineBelt);
		}
		//TextDrawShowForPlayer(playerid, Areny);
		TextDrawShowForPlayer(playerid, recommend_box);
		  
		
		
		if(pInfo[playerid][player_gang] && !pInfo[playerid][player_hidehud][hud_gangmembers])
		{
			TextDrawShowForPlayer(playerid, gInfo[ pInfo[playerid][player_gang] ][gangTextdraw]);
		}
		else 
		{
			if(IsTextDrawShowForPlayer(playerid, gInfo[ pInfo[playerid][player_gang] ][gangTextdraw])) TextDrawHideForPlayer(playerid, gInfo[ pInfo[playerid][player_gang] ][gangTextdraw]);
		}
 	}
	else
	{
		//PlayerTextDrawHide(playerid, pInfo[playerid][player_TdNick]);
		//PlayerTextDrawHide(playerid, pInfo[playerid][player_TextureSkin]);
		TextDrawHideForPlayer(playerid,TimeTD);
		TextDrawHideForPlayer(playerid,DateTD);
		PlayerTextDrawHide(playerid,CzasGry[playerid]);
		for(new i;i<6;i++)
		{
			if(!pInfo[playerid][player_hidehud][hud_fps])
			{
				if( i == 5 ) continue;
			}
				
			PlayerTextDrawHide(playerid, pInfo[playerid][player_TdStats][i]); 
		}
		
		for(new i;i<11;i++)
			TextDrawHideForPlayer(playerid, PasekBelt[i]); 
		
		for(new x; x < 7; x++)	
			TextDrawShowForPlayer(playerid, EnterExitTD[x]);
		
		TextDrawHideForPlayer(playerid, EventTD[0]);
		TextDrawHideForPlayer(playerid, EventTD[1]);
		//TextDrawHideForPlayer(playerid, Areny);
		TextDrawHideForPlayer(playerid, recommend_box);
		
		TextDrawHideForPlayer(playerid, OnlineBelt);
		
			
		//if(pInfo[playerid][player_gang])
		TextDrawHideForPlayer(playerid, gInfo[ pInfo[playerid][player_gang] ][gangTextdraw]);
		
  	}
	return 1;
}
stock UpdatePlayerSkin(playerid)
{
	#pragma unused playerid
	//PlayerTextDrawSetPreviewModel(playerid, pInfo[playerid][player_TextureSkin], pInfo[playerid][player_skin]);
	//PlayerTextDrawShow(playerid, pInfo[playerid][player_TextureSkin]);
}
 

stock TDPanorama(playerid, bool:show = true, bool:connect = false)
{
	if(connect) return;
	if(show)
	{
		TextDrawShowForPlayer(playerid, Panorama[0]);
		TextDrawShowForPlayer(playerid, Panorama[1]);
		TextDrawShowForPlayer(playerid, Panorama[2]);
		TextDrawShowForPlayer(playerid, Panorama[3]);
		TextDrawShowForPlayer(playerid, Panorama[4]);
		TextDrawShowForPlayer(playerid, Panorama[5]);
		
		TextDrawShowForPlayer(playerid, Logo_P4S[0]);
		TextDrawShowForPlayer(playerid, Logo_P4S[1]);
		TextDrawShowForPlayer(playerid, Logo_P4S[2]);
		TextDrawShowForPlayer(playerid, Logo_P4S[3]);
		TextDrawShowForPlayer(playerid, Logo_P4S[4]);
		TextDrawShowForPlayer(playerid, Logo_P4S[5]);
		TextDrawShowForPlayer(playerid, Logo_P4S[6]);	
 
 	}
	else 
	{
		TextDrawHideForPlayer(playerid, Panorama[0]);
		TextDrawHideForPlayer(playerid, Panorama[1]);
		TextDrawHideForPlayer(playerid, Panorama[2]);
		TextDrawHideForPlayer(playerid, Panorama[3]);
		TextDrawHideForPlayer(playerid, Panorama[4]);
		TextDrawHideForPlayer(playerid, Panorama[5]);
	
		TextDrawHideForPlayer(playerid, Logo_P4S[0]);
		TextDrawHideForPlayer(playerid, Logo_P4S[1]);
		TextDrawHideForPlayer(playerid, Logo_P4S[2]);
		TextDrawHideForPlayer(playerid, Logo_P4S[3]);
		TextDrawHideForPlayer(playerid, Logo_P4S[4]);
		TextDrawHideForPlayer(playerid, Logo_P4S[5]);
		TextDrawHideForPlayer(playerid, Logo_P4S[6]);
 
		
	}
}

 
stock PlayerText_Licznik(playerid, bool:show)
{
	if(show)
	{
		if(pInfo[playerid][player_hidehud][hud_all]) return PlayerText_Licznik(playerid, false);
		
		if(pInfo[playerid][player_hidehud][hud_licznik])
		{
			for(new i;i<4;i++)
			{
				if(IsPlayerTextDrawShow(playerid, pInfo[playerid][player_TdLicznik][i]))  PlayerTextDrawHide(playerid, pInfo[playerid][player_TdLicznik][i]);
			}
			if(IsTextDrawShowForPlayer(playerid, LicznikBelt)) TextDrawHideForPlayer(playerid, LicznikBelt); 
		}
		else
		{
			if(!Iter_Contains(Drivers, playerid)) return 0;
			for(new i;i<4;i++)
			{
				PlayerTextDrawShow(playerid, pInfo[playerid][player_TdLicznik][i]);
			}
			TextDrawShowForPlayer(playerid, LicznikBelt); 

		} 
		 
	}
	else
	{
		for(new i;i<4;i++)
		{
			PlayerTextDrawHide(playerid, pInfo[playerid][player_TdLicznik][i]); 
			 
		} 
		TextDrawHideForPlayer(playerid, LicznikBelt);
		 
	}
	return 1;
}
stock Text_Create()
{


	__walizka[1] = TextDrawCreate(133.777679, 327.040039, "~r~~h~Przepisz kod: ~w~vq913glxclh4");
	TextDrawLetterSize(__walizka[1], 0.252000, 1.126999);
	TextDrawAlignment(__walizka[1], 3);
	TextDrawColor(__walizka[1], -1);
	TextDrawUseBox(__walizka[1], true);
	TextDrawBoxColor(__walizka[1], 32);
	TextDrawSetShadow(__walizka[1], 0);
	TextDrawSetOutline(__walizka[1], -1);
	TextDrawBackgroundColor(__walizka[1], 80);
	TextDrawFont(__walizka[1], 1);
	TextDrawSetProportional(__walizka[1], 1);

	__walizka[0] = TextDrawCreate(133.777755, 310.613372, "~b~~h~~h~Walizka: ~w~/tama");
	TextDrawLetterSize(__walizka[0], 0.252000, 1.126999);
	TextDrawAlignment(__walizka[0], 3);
	TextDrawColor(__walizka[0], -1);
	TextDrawUseBox(__walizka[0], true);
	TextDrawBoxColor(__walizka[0], 32);
	TextDrawSetShadow(__walizka[0], 0);
	TextDrawSetOutline(__walizka[0], -1);
	TextDrawBackgroundColor(__walizka[0], 80);
	TextDrawFont(__walizka[0], 1);
	TextDrawSetProportional(__walizka[0], 1);

	GangSparTd0[0] = TextDrawCreate(483.600006, 138.886672, "usebox");
	TextDrawLetterSize(GangSparTd0[0], 0.000000, 17.437408);
	TextDrawTextSize(GangSparTd0[0], 140.399993, 0.000000);
	TextDrawAlignment(GangSparTd0[0], 1);
	TextDrawColor(GangSparTd0[0], 0);
	TextDrawUseBox(GangSparTd0[0], true);
	TextDrawBoxColor(GangSparTd0[0], 16);
	TextDrawSetShadow(GangSparTd0[0], 0);
	TextDrawSetOutline(GangSparTd0[0], 0);
	TextDrawFont(GangSparTd0[0], 0);

	GangSparTd0[1] = TextDrawCreate(148.799911, 167.999954, "Nick:_______Kills_____DMG");
	TextDrawLetterSize(GangSparTd0[1], 0.261999, 1.413333);
	TextDrawAlignment(GangSparTd0[1], 1);
	TextDrawColor(GangSparTd0[1], -1);
	TextDrawSetShadow(GangSparTd0[1], 0);
	TextDrawSetOutline(GangSparTd0[1], 1);
	TextDrawBackgroundColor(GangSparTd0[1], 51);
	TextDrawFont(GangSparTd0[1], 2);
	TextDrawSetProportional(GangSparTd0[1], 1);

	GangSparTd0[2] = TextDrawCreate(483.600006, 143.886672, "usebox");
	TextDrawLetterSize(GangSparTd0[2], 0.000000, 17.437408);
	TextDrawTextSize(GangSparTd0[2], 140.399993, 0.000000);
	TextDrawAlignment(GangSparTd0[2], 1);
	TextDrawColor(GangSparTd0[2], 0);
	TextDrawUseBox(GangSparTd0[2], true);
	TextDrawBoxColor(GangSparTd0[2], 16);
	TextDrawSetShadow(GangSparTd0[2], 0);
	TextDrawSetOutline(GangSparTd0[2], 0);
	TextDrawFont(GangSparTd0[2], 0);

	GangSparTd0[3] = TextDrawCreate(483.600006, 148.886672, "usebox");
	TextDrawLetterSize(GangSparTd0[3], 0.000000, 17.437408);
	TextDrawTextSize(GangSparTd0[3], 140.399993, 0.000000);
	TextDrawAlignment(GangSparTd0[3], 1);
	TextDrawColor(GangSparTd0[3], 0);
	TextDrawUseBox(GangSparTd0[3], true);
	TextDrawBoxColor(GangSparTd0[3], 16);
	TextDrawSetShadow(GangSparTd0[3], 0);
	TextDrawSetOutline(GangSparTd0[3], 0);
	TextDrawFont(GangSparTd0[3], 0);

	GangSparTd0[4] = TextDrawCreate(483.600006, 153.886672, "usebox");
	TextDrawLetterSize(GangSparTd0[4], 0.000000, 17.437408);
	TextDrawTextSize(GangSparTd0[4], 140.399993, 0.000000);
	TextDrawAlignment(GangSparTd0[4], 1);
	TextDrawColor(GangSparTd0[4], 0);
	TextDrawUseBox(GangSparTd0[4], true);
	TextDrawBoxColor(GangSparTd0[4], 16);
	TextDrawSetShadow(GangSparTd0[4], 0);
	TextDrawSetOutline(GangSparTd0[4], 0);
	TextDrawFont(GangSparTd0[4], 0);

	GangSparTd0[5] = TextDrawCreate(483.600006, 158.886672, "usebox");
	TextDrawLetterSize(GangSparTd0[5], 0.000000, 17.437408);
	TextDrawTextSize(GangSparTd0[5], 140.399993, 0.000000);
	TextDrawAlignment(GangSparTd0[5], 1);
	TextDrawColor(GangSparTd0[5], 0);
	TextDrawUseBox(GangSparTd0[5], true);
	TextDrawBoxColor(GangSparTd0[5], 16);
	TextDrawSetShadow(GangSparTd0[5], 0);
	TextDrawSetOutline(GangSparTd0[5], 0);
	TextDrawFont(GangSparTd0[5], 0);

	GangSparTd0[6] = TextDrawCreate(483.600006, 163.886672, "usebox");
	TextDrawLetterSize(GangSparTd0[6], 0.000000, 17.437408);
	TextDrawTextSize(GangSparTd0[6], 140.399993, 0.000000);
	TextDrawAlignment(GangSparTd0[6], 1);
	TextDrawColor(GangSparTd0[6], 0);
	TextDrawUseBox(GangSparTd0[6], true);
	TextDrawBoxColor(GangSparTd0[6], 16);
	TextDrawSetShadow(GangSparTd0[6], 0);
	TextDrawSetOutline(GangSparTd0[6], 0);
	TextDrawFont(GangSparTd0[6], 0);

	GangSparTd0[7] = TextDrawCreate(483.600006, 168.886672, "usebox");
	TextDrawLetterSize(GangSparTd0[7], 0.231997, 1.384070);
	TextDrawTextSize(GangSparTd0[7], 140.399993, 0.000000);
	TextDrawAlignment(GangSparTd0[7], 1);
	TextDrawColor(GangSparTd0[7], 0);
	TextDrawUseBox(GangSparTd0[7], true);
	TextDrawBoxColor(GangSparTd0[7], 520093776);
	TextDrawSetShadow(GangSparTd0[7], 0);
	TextDrawSetOutline(GangSparTd0[7], 0);
	TextDrawFont(GangSparTd0[7], 0);

	GangSparTd0[8] = TextDrawCreate(349.265869, 168.519912, "Nick:_______Kills_____DMG");
	TextDrawLetterSize(GangSparTd0[8], 0.261999, 1.413333);
	TextDrawAlignment(GangSparTd0[8], 1);
	TextDrawColor(GangSparTd0[8], -1);
	TextDrawSetShadow(GangSparTd0[8], 0);
	TextDrawSetOutline(GangSparTd0[8], 1);
	TextDrawBackgroundColor(GangSparTd0[8], 51);
	TextDrawFont(GangSparTd0[8], 2);
	TextDrawSetProportional(GangSparTd0[8], 1);

	StrefaBezDM = TextDrawCreate(372.500000, 11.200046, "BEZ_DM!");
	TextDrawLetterSize(StrefaBezDM, 0.538749, 1.600000);
	TextDrawTextSize(StrefaBezDM, 306.875000, -70.933326);
	TextDrawAlignment(StrefaBezDM, 2);
	TextDrawColor(StrefaBezDM, -268435312);
	TextDrawUseBox(StrefaBezDM, 1);
	TextDrawBoxColor(StrefaBezDM, -1073741744);
	TextDrawSetShadow(StrefaBezDM, 0);
	TextDrawSetOutline(StrefaBezDM, 1);
	TextDrawBackgroundColor(StrefaBezDM, 51);
	TextDrawFont(StrefaBezDM, 3);
	TextDrawSetProportional(StrefaBezDM, 1);
	
	ClassSkinInfo = TextDrawCreate(598.500000, 240.799865, "Ostatnio uzywany~n~skin.");
	TextDrawLetterSize(ClassSkinInfo, 0.185000, 1.102222);
	TextDrawAlignment(ClassSkinInfo, 2);
	TextDrawColor(ClassSkinInfo, 572661584);
	TextDrawSetShadow(ClassSkinInfo, 0);
	TextDrawSetOutline(ClassSkinInfo, 1);
	TextDrawBackgroundColor(ClassSkinInfo, 572661520);
	TextDrawFont(ClassSkinInfo, 1);
	TextDrawSetProportional(ClassSkinInfo, 1);
	//	AdminTDInfo = TextDrawCreate(497.000000, 99.717231, "[21:36] Prawdopodobny AIRBRK mrdrifter. (36)~n~[21:36] Prawdopodobny AIRBRK mrdrifter. (36)~n~[21:36] Prawdopodobny AIRBRK mrdri");

	AdminTDInfo = TextDrawCreate(497.000000, 99.717231, "---");
	TextDrawLetterSize(AdminTDInfo, 0.114500, 0.730833);
	TextDrawAlignment(AdminTDInfo, 1);
	TextDrawColor(AdminTDInfo, -1);
	TextDrawSetShadow(AdminTDInfo, 0);
	TextDrawSetOutline(AdminTDInfo, 1);
	TextDrawBackgroundColor(AdminTDInfo, 32);
	TextDrawFont(AdminTDInfo, 1);
	TextDrawSetProportional(AdminTDInfo, 1);
	TextDrawSetShadow(AdminTDInfo, 0);
	PasekBelt[0] = TextDrawCreate(641.555541, 426.602233, "usebox");
	TextDrawLetterSize(PasekBelt[0], 0.000000, 2.006297);
	TextDrawTextSize(PasekBelt[0], -2.000000, 0.000000);
	TextDrawAlignment(PasekBelt[0], 1);
	TextDrawColor(PasekBelt[0], 0);
	TextDrawUseBox(PasekBelt[0], true);
	TextDrawBoxColor(PasekBelt[0], 37);
	TextDrawSetShadow(PasekBelt[0], 0);
	TextDrawSetOutline(PasekBelt[0], 0);
	TextDrawFont(PasekBelt[0], 0);

	PasekBelt[1] = TextDrawCreate(641.555541, 427.597778, "usebox");
	TextDrawLetterSize(PasekBelt[1], 0.000000, 1.785061);
	TextDrawTextSize(PasekBelt[1], -2.000000, 0.000000);
	TextDrawAlignment(PasekBelt[1], 1);
	TextDrawColor(PasekBelt[1], 0);
	TextDrawUseBox(PasekBelt[1], true);
	TextDrawBoxColor(PasekBelt[1], 37);
	TextDrawSetShadow(PasekBelt[1], 0);
	TextDrawSetOutline(PasekBelt[1], 0);
	TextDrawFont(PasekBelt[1], 0);

	PasekBelt[2] = TextDrawCreate(641.555541, 437.553344, "usebox");
	TextDrawLetterSize(PasekBelt[2], 0.000000, 0.678887);
	TextDrawTextSize(PasekBelt[2], -2.000000, 0.000000);
	TextDrawAlignment(PasekBelt[2], 1);
	TextDrawColor(PasekBelt[2], 0);
	TextDrawUseBox(PasekBelt[2], true);
	TextDrawBoxColor(PasekBelt[2], 21);
	TextDrawSetShadow(PasekBelt[2], 0);
	TextDrawSetOutline(PasekBelt[2], 0);
	TextDrawFont(PasekBelt[2], 0);

	 

	PasekBelt[3] = TextDrawCreate(20.555580, 426.097961, "~y~Level:");
	TextDrawLetterSize(PasekBelt[3], 0.228000, 0.953000);
	TextDrawAlignment(PasekBelt[3], 2);
	TextDrawColor(PasekBelt[3], -1);
	TextDrawSetShadow(PasekBelt[3], 0);
	TextDrawSetOutline(PasekBelt[3], -1);
	TextDrawBackgroundColor(PasekBelt[3], 51);
	TextDrawFont(PasekBelt[3], 1);
	TextDrawSetProportional(PasekBelt[3], 1);

	PasekBelt[4] = TextDrawCreate(155.555664, 426.097686, "~b~~h~Respekt:");
	TextDrawLetterSize(PasekBelt[4], 0.228000, 0.953000);
	TextDrawAlignment(PasekBelt[4], 2);
	TextDrawColor(PasekBelt[4], -1);
	TextDrawSetShadow(PasekBelt[4], 0);
	TextDrawSetOutline(PasekBelt[4], -1);
	TextDrawBackgroundColor(PasekBelt[4], 51);
	TextDrawFont(PasekBelt[4], 1);
	TextDrawSetProportional(PasekBelt[4], 1);

	PasekBelt[5] = TextDrawCreate(461.333160, 426.097717, "~r~~h~~h~Zabojstw: ~w~' ~y~~h~Skill: ~w~' ~g~~h~Smierci:");
	TextDrawLetterSize(PasekBelt[5], 0.228000, 0.953000);
	TextDrawAlignment(PasekBelt[5], 2);
	TextDrawColor(PasekBelt[5], -1);
	TextDrawSetShadow(PasekBelt[5], 0);
	TextDrawSetOutline(PasekBelt[5], -1);
	TextDrawBackgroundColor(PasekBelt[5], 51);
	TextDrawFont(PasekBelt[5], 1);
	TextDrawSetProportional(PasekBelt[5], 1);

	PasekBelt[6] = TextDrawCreate(67.556304, 426.097686, "~g~~h~Portfel:");
	TextDrawLetterSize(PasekBelt[6], 0.228000, 0.953000);
	TextDrawAlignment(PasekBelt[6], 2);
	TextDrawColor(PasekBelt[6], -1);
	TextDrawSetShadow(PasekBelt[6], 0);
	TextDrawSetOutline(PasekBelt[6], -1);
	TextDrawBackgroundColor(PasekBelt[6], 51);
	TextDrawFont(PasekBelt[6], 1);
	TextDrawSetProportional(PasekBelt[6], 1);

	PasekBelt[7] = TextDrawCreate(403.777770, 427.597778, "usebox");
	TextDrawLetterSize(PasekBelt[7], 0.000000, 1.785061);
	TextDrawTextSize(PasekBelt[7], 232.222229, 0.000000);
	TextDrawAlignment(PasekBelt[7], 1);
	TextDrawColor(PasekBelt[7], 0);
	TextDrawUseBox(PasekBelt[7], true);
	TextDrawBoxColor(PasekBelt[7], -251);
	TextDrawSetShadow(PasekBelt[7], 0);
	TextDrawSetOutline(PasekBelt[7], 0);
	TextDrawFont(PasekBelt[7], 0);

	PasekBelt[8] = TextDrawCreate(584.888977, 426.097656, "P-Loss: ~w~' ~y~FPS: ~w~' ~p~Ping:");
	TextDrawLetterSize(PasekBelt[8], 0.228000, 0.953000);
	TextDrawAlignment(PasekBelt[8], 2);
	TextDrawColor(PasekBelt[8], -1717986817);
	TextDrawSetShadow(PasekBelt[8], 0);
	TextDrawSetOutline(PasekBelt[8], -1);
	TextDrawBackgroundColor(PasekBelt[8], 51);
	TextDrawFont(PasekBelt[8], 1);
	TextDrawSetProportional(PasekBelt[8], 1);


	PasekBelt[9] = TextDrawCreate(635.500000, 439.083374, "15/02/16 21:55");
	TextDrawLetterSize(PasekBelt[9], 0.248500, 0.584999);
	TextDrawAlignment(PasekBelt[9], 3);
	TextDrawColor(PasekBelt[9], -1);
	TextDrawSetShadow(PasekBelt[9], 256);
	TextDrawSetOutline(PasekBelt[9], 2);
	TextDrawBackgroundColor(PasekBelt[9], 32);
	TextDrawFont(PasekBelt[9], 1);
	TextDrawSetProportional(PasekBelt[9], 1);
	TextDrawSetShadow(PasekBelt[9], 256);

	PasekBelt[10] = TextDrawCreate(59.110961, 416.141998, "www.4fun-serv.eu");
	TextDrawLetterSize(PasekBelt[10], 0.193553, 0.853331);
	TextDrawAlignment(PasekBelt[10], 1);
	TextDrawColor(PasekBelt[10], -1);
	TextDrawSetShadow(PasekBelt[10], 0);
	TextDrawSetOutline(PasekBelt[10], -1);
	TextDrawBackgroundColor(PasekBelt[10], 51);
	TextDrawFont(PasekBelt[10], 1);
	TextDrawSetProportional(PasekBelt[10], 1);

	OnlineBelt = TextDrawCreate(638.000427, 386.275665, "~w~25 I~n~~y~5 I~n~~g~~h~1 I~n~~r~~h~2 I~n~");
	TextDrawLetterSize(OnlineBelt, 0.185552, 0.987733);
	TextDrawAlignment(OnlineBelt, 3);
	TextDrawColor(OnlineBelt, -1);
	TextDrawSetShadow(OnlineBelt, 0);
	TextDrawSetOutline(OnlineBelt, -1);
	TextDrawBackgroundColor(OnlineBelt, 51);
	TextDrawFont(OnlineBelt, 2);
	TextDrawSetProportional(OnlineBelt, 1);

	AnnDraw2 = TextDrawCreate(640.0/2, 480.0/2 - 115, "_");
	TextDrawColor(AnnDraw2, 0xFFFFFFFF);
	TextDrawBackgroundColor(AnnDraw2, 0x00000040);
	TextDrawFont(AnnDraw2, 1);
	TextDrawTextSize(AnnDraw2, 300, 300);
	TextDrawLetterSize(AnnDraw2, 0.36*1.2, 1.8*1.2);
	TextDrawSetProportional(AnnDraw2, 1);
	TextDrawAlignment(AnnDraw2, 2);
    TextDrawSetOutline(AnnDraw2, 1);
	
	EnterExitTD[0] = TextDrawCreate(230.333389, 383.544525, "usebox");
	TextDrawLetterSize(EnterExitTD[0], 0.000000, 3.739302);
	TextDrawTextSize(EnterExitTD[0], 141.333389, 0.000000);
	TextDrawAlignment(EnterExitTD[0], 1);
	TextDrawColor(EnterExitTD[0], 0);
	TextDrawUseBox(EnterExitTD[0], true);
	TextDrawBoxColor(EnterExitTD[0], 102);
	TextDrawSetShadow(EnterExitTD[0], 0);
	TextDrawSetOutline(EnterExitTD[0], 0);
	TextDrawFont(EnterExitTD[0], 0);

	EnterExitTD[1] = TextDrawCreate(232.333328, 375.248168, "usebox");
	TextDrawLetterSize(EnterExitTD[1], 0.000000, 0.559052);
	TextDrawTextSize(EnterExitTD[1], 140.000000, 0.000000);
	TextDrawAlignment(EnterExitTD[1], 1);
	TextDrawColor(EnterExitTD[1], 0);
	TextDrawUseBox(EnterExitTD[1], true);
	TextDrawBoxColor(EnterExitTD[1], -5963521);
	TextDrawSetShadow(EnterExitTD[1], 0);
	TextDrawSetOutline(EnterExitTD[1], 0);
	TextDrawFont(EnterExitTD[1], 0);

	EnterExitTD[2] = TextDrawCreate(144.333328, 382.459381, "------------------------");
	TextDrawLetterSize(EnterExitTD[2], 0.096999, 1.031703);
	TextDrawAlignment(EnterExitTD[2], 1);
	TextDrawColor(EnterExitTD[2], -1);
	TextDrawSetShadow(EnterExitTD[2], 0);
	TextDrawSetOutline(EnterExitTD[2], 1);
	TextDrawBackgroundColor(EnterExitTD[2], 51);
	TextDrawFont(EnterExitTD[2], 1);
	TextDrawSetProportional(EnterExitTD[2], 1);

	EnterExitTD[3] = TextDrawCreate(144.333328, 390.755462, "------------------------");
	TextDrawLetterSize(EnterExitTD[3], 0.096666, 1.010962);
	TextDrawAlignment(EnterExitTD[3], 1);
	TextDrawColor(EnterExitTD[3], -1);
	TextDrawSetShadow(EnterExitTD[3], 0);
	TextDrawSetOutline(EnterExitTD[3], 1);
	TextDrawBackgroundColor(EnterExitTD[3], 51);
	TextDrawFont(EnterExitTD[3], 1);
	TextDrawSetProportional(EnterExitTD[3], 1);

	EnterExitTD[4] = TextDrawCreate(144.333358, 398.637054, "------------------------");
	TextDrawLetterSize(EnterExitTD[4], 0.096666, 0.998518);
	TextDrawAlignment(EnterExitTD[4], 1);
	TextDrawColor(EnterExitTD[4], -1);
	TextDrawSetShadow(EnterExitTD[4], 0);
	TextDrawSetOutline(EnterExitTD[4], 1);
	TextDrawBackgroundColor(EnterExitTD[4], 51);
	TextDrawFont(EnterExitTD[4], 1);
	TextDrawSetProportional(EnterExitTD[4], 1);

	EnterExitTD[5] = TextDrawCreate(144.333267, 406.933380, "------------------------");
	TextDrawLetterSize(EnterExitTD[5], 0.096666, 0.898962);
	TextDrawAlignment(EnterExitTD[5], 1);
	TextDrawColor(EnterExitTD[5], -1);
	TextDrawSetShadow(EnterExitTD[5], 0);
	TextDrawSetOutline(EnterExitTD[5], 1);
	TextDrawBackgroundColor(EnterExitTD[5], 51);
	TextDrawFont(EnterExitTD[5], 1);
	TextDrawSetProportional(EnterExitTD[5], 1);

	EnterExitTD[6] = TextDrawCreate(144.666687, 373.748229, "Wyjscia i wejscia na serwerze");
	TextDrawLetterSize(EnterExitTD[6], 0.122999, 0.712296);
	TextDrawAlignment(EnterExitTD[6], 1);
	TextDrawColor(EnterExitTD[6], 255);
	TextDrawSetShadow(EnterExitTD[6], 0);
	TextDrawSetOutline(EnterExitTD[6], 0);
	TextDrawBackgroundColor(EnterExitTD[6], 51);
	TextDrawFont(EnterExitTD[6], 2);
	TextDrawSetProportional(EnterExitTD[6], 1);
 
 	AnnDraw = TextDrawCreate(320.0, 140.0, " ");	
	TextDrawLetterSize(AnnDraw, 0.45, 1.6);
	TextDrawColor(AnnDraw, 0xFFFFD0FF);
	TextDrawFont(AnnDraw, 1);
	TextDrawSetShadow(AnnDraw, 0);
	TextDrawSetOutline(AnnDraw, 1);
	TextDrawBackgroundColor(AnnDraw, 0x00000070);
	TextDrawAlignment(AnnDraw, 2);
	TextDrawTextSize(AnnDraw, 250.0, 250.0);

	AnnDraw3 = TextDrawCreate(488.000000, 270.000000, "_");
	TextDrawAlignment(AnnDraw3, 2);
	TextDrawBackgroundColor(AnnDraw3, 144);
	TextDrawFont(AnnDraw3, 1);
	TextDrawLetterSize(AnnDraw3, 0.300000, 1.300000);
	TextDrawColor(AnnDraw3, -1);
	TextDrawSetOutline(AnnDraw3, 0);
	TextDrawSetProportional(AnnDraw3, 1);
	TextDrawSetShadow(AnnDraw3, 1);
	TextDrawUseBox(AnnDraw3, 1);
	TextDrawBoxColor(AnnDraw3, 0);
	TextDrawTextSize(AnnDraw3, 0.000000, 298.000000);
  
	Logo_P4S[0] = TextDrawCreate(32.888881, 218.026641, "Polski");
	TextDrawLetterSize(Logo_P4S[0], 0.449999, 1.600000);
	TextDrawAlignment(Logo_P4S[0], 1);
	TextDrawColor(Logo_P4S[0], -16776961);
	TextDrawSetShadow(Logo_P4S[0], 0);
	TextDrawSetOutline(Logo_P4S[0], 4);
	TextDrawBackgroundColor(Logo_P4S[0], 51);
	TextDrawFont(Logo_P4S[0], 1);
	TextDrawSetProportional(Logo_P4S[0], 1);

	Logo_P4S[1] = TextDrawCreate(52.888877, 230.968902, "4Fun");
	TextDrawLetterSize(Logo_P4S[1], 0.449999, 1.600000);
	TextDrawAlignment(Logo_P4S[1], 1);
	TextDrawColor(Logo_P4S[1], -1);
	TextDrawSetShadow(Logo_P4S[1], 0);
	TextDrawSetOutline(Logo_P4S[1], 4);
	TextDrawBackgroundColor(Logo_P4S[1], 51);
	TextDrawFont(Logo_P4S[1], 1);
	TextDrawSetProportional(Logo_P4S[1], 1);

	Logo_P4S[2] = TextDrawCreate(76.888923, 241.920059, "Server");
	TextDrawLetterSize(Logo_P4S[2], 0.449999, 1.600000);
	TextDrawAlignment(Logo_P4S[2], 1);
	TextDrawColor(Logo_P4S[2], -16776961);
	TextDrawSetShadow(Logo_P4S[2], 0);
	TextDrawSetOutline(Logo_P4S[2], 3);
	TextDrawBackgroundColor(Logo_P4S[2], 51);
	TextDrawFont(Logo_P4S[2], 1);
	TextDrawSetProportional(Logo_P4S[2], 1);

	Logo_P4S[3] = TextDrawCreate(17.333358, 250.382049, " ");//GRA
	TextDrawLetterSize(Logo_P4S[3], 0.297554, 0.793599);
	TextDrawAlignment(Logo_P4S[3], 1);
	TextDrawColor(Logo_P4S[3], -1);
	TextDrawSetShadow(Logo_P4S[3], 0);
	TextDrawSetOutline(Logo_P4S[3], 2);
	TextDrawBackgroundColor(Logo_P4S[3], 51);
	TextDrawFont(Logo_P4S[3], 1);
	TextDrawSetProportional(Logo_P4S[3], 1);

	Logo_P4S[4] = TextDrawCreate(113.333320, 238.435714, splitf("r%s.%s",version,build));
	TextDrawLetterSize(Logo_P4S[4], 0.275332, 0.669155);
	TextDrawAlignment(Logo_P4S[4], 1);
	TextDrawColor(Logo_P4S[4], -1);
	TextDrawSetShadow(Logo_P4S[4], 0);
	TextDrawSetOutline(Logo_P4S[4], 1);
	TextDrawBackgroundColor(Logo_P4S[4], 51);
	TextDrawFont(Logo_P4S[4], 1);
	TextDrawSetProportional(Logo_P4S[4], 1);

	Logo_P4S[5] = TextDrawCreate(26.222209, 259.342346, " ");//O
	TextDrawLetterSize(Logo_P4S[5], 0.356222, 0.803555);
	TextDrawAlignment(Logo_P4S[5], 1);
	TextDrawColor(Logo_P4S[5], -1);
	TextDrawSetShadow(Logo_P4S[5], 0);
	TextDrawSetOutline(Logo_P4S[5], -2);
	TextDrawBackgroundColor(Logo_P4S[5], 51);
	TextDrawFont(Logo_P4S[5], 1);
	TextDrawSetProportional(Logo_P4S[5], 1);

	Logo_P4S[6] = TextDrawCreate(39.111125, 266.311126, " ");//TRON
	TextDrawLetterSize(Logo_P4S[6], 0.338889, 0.967822);
	TextDrawAlignment(Logo_P4S[6], 1);
	TextDrawColor(Logo_P4S[6], -1);
	TextDrawSetShadow(Logo_P4S[6], 0);
	TextDrawSetOutline(Logo_P4S[6], 2);
	TextDrawBackgroundColor(Logo_P4S[6], 51);
	TextDrawFont(Logo_P4S[6], 1);
	TextDrawSetProportional(Logo_P4S[6], 1);




	SpawnOchrona = TextDrawCreate(550.000000, 63.000000, "Spawn-ochrona");
	TextDrawAlignment(SpawnOchrona, 0);
	TextDrawBackgroundColor(SpawnOchrona, 0x000000ff);
	TextDrawFont(SpawnOchrona, 1);
	TextDrawLetterSize(SpawnOchrona, 0.199999, 0.799999);
	TextDrawColor(SpawnOchrona, 0xff0000ff);
	TextDrawSetOutline(SpawnOchrona, 1);
	TextDrawSetProportional(SpawnOchrona, 1);
	TextDrawSetShadow(SpawnOchrona, 1);

	LicznikBelt = TextDrawCreate(624.221923, 389.268890, "usebox");
	TextDrawLetterSize(LicznikBelt, 0.000000, 3.333703);
	TextDrawTextSize(LicznikBelt, 544.666381, 0.000000);
	TextDrawAlignment(LicznikBelt, 1);
	TextDrawColor(LicznikBelt, 0);
	TextDrawUseBox(LicznikBelt, true);
	TextDrawBoxColor(LicznikBelt, 80);
	TextDrawSetShadow(LicznikBelt, 0);
	TextDrawSetOutline(LicznikBelt, 0);
	TextDrawFont(LicznikBelt, 0);
 


	
	glosowanie[0] = TextDrawCreate(27.199550, 230.733230, "LD_POKE:cd9s");
	TextDrawLetterSize(glosowanie[0], -0.139197, -0.627199);
	TextDrawTextSize(glosowanie[0], 180.799957, 60.493324);
	TextDrawAlignment(glosowanie[0], 3);
	TextDrawColor(glosowanie[0], 16);
	TextDrawSetShadow(glosowanie[0], 0);
	TextDrawSetOutline(glosowanie[0], 0);
	TextDrawFont(glosowanie[0], 4);

	glosowanie[1] = TextDrawCreate(30.800008, 235.206481, " ");

	glosowanie[2] = TextDrawCreate(63.999992, 229.973403, "Glosowanie!");
	TextDrawLetterSize(glosowanie[2], 0.386000, 1.674666);
	TextDrawAlignment(glosowanie[2], 1);
	TextDrawColor(glosowanie[2], -1);
	TextDrawSetShadow(glosowanie[2], 0);
	TextDrawSetOutline(glosowanie[2], 2);
	TextDrawBackgroundColor(glosowanie[2], 51);
	TextDrawFont(glosowanie[2], 2);
	TextDrawSetProportional(glosowanie[2], 1);

	glosowanie[3] = TextDrawCreate(27.200000, 242.666671, "Czy chcecie aby mrdrifter dalej byl administart...~n~orem czy nie?");
	TextDrawLetterSize(glosowanie[3], 0.206000, 1.039999);
	TextDrawAlignment(glosowanie[3], 1);
	TextDrawColor(glosowanie[3], -1);
	TextDrawSetShadow(glosowanie[3], 0);
	TextDrawSetOutline(glosowanie[3], 1);
	TextDrawBackgroundColor(glosowanie[3], 51);
	TextDrawFont(glosowanie[3], 1);
	TextDrawSetProportional(glosowanie[3], 1);

	glosowanie[4] = TextDrawCreate(36.799983, 272.533355, "~g~~h~/Tak ~w~(4)___~g~Tak = 4___~r~~h~Nie (3)");
	TextDrawLetterSize(glosowanie[4], 0.301027, 1.435966);
	TextDrawAlignment(glosowanie[4], 1);
	TextDrawColor(glosowanie[4], -1);
	TextDrawSetShadow(glosowanie[4], 0);
	TextDrawSetOutline(glosowanie[4], 1);
	TextDrawBackgroundColor(glosowanie[4], 51);
	TextDrawFont(glosowanie[4], 1);
	TextDrawSetProportional(glosowanie[4], 1);
	
	w_olg[0] = TextDrawCreate(36.355556, 197.617935, "LD_POKE:cd9s");
	TextDrawLetterSize(w_olg[0], -0.061599, -1.164798);
	TextDrawTextSize(w_olg[0], 166.844390, 31.857797);
	TextDrawAlignment(w_olg[0], 1);
	TextDrawColor(w_olg[0], 80);
	TextDrawSetShadow(w_olg[0], 0);
	TextDrawSetOutline(w_olg[0], 0);
	TextDrawFont(w_olg[0], 4);
	TextDrawSetProportional(w_olg[0], 1);

	w_olg[1] = TextDrawCreate(84.177764, 191.893569, "Ogloszenie VIP!");
	TextDrawLetterSize(w_olg[1], 0.210795, 0.815998);
	TextDrawAlignment(w_olg[1], 1);
	TextDrawColor(w_olg[1], -1);
	TextDrawSetShadow(w_olg[1], 0);
	TextDrawSetOutline(w_olg[1], 2);
	TextDrawBackgroundColor(w_olg[1], 51);
	TextDrawFont(w_olg[1], 1);
	TextDrawSetProportional(w_olg[1], 1);

	w_olg[2] = TextDrawCreate(40.022235, 201.604598, "~y~Game(69): ~w~Kocham was!");
	TextDrawLetterSize(w_olg[2], 0.210795, 0.815998);
	TextDrawAlignment(w_olg[2], 1);
	TextDrawColor(w_olg[2], -1);
	TextDrawSetShadow(w_olg[2], 0);
	TextDrawSetOutline(w_olg[2], 1);
	TextDrawBackgroundColor(w_olg[2], 51);
	TextDrawFont(w_olg[2], 1);
	TextDrawSetProportional(w_olg[2], 1);
	TextDrawSetSelectable(w_olg[2], true);

	EventTD0[1] = TextDrawCreate(148.500000, 358.000213, "~r~~h~Uloz Wyraz: ~w~~h~xxxxxx");
	TextDrawLetterSize(EventTD0[1], 0.164500, 1.403332);
	TextDrawTextSize(EventTD0[1], 234.000000, 0.000000);
	TextDrawAlignment(EventTD0[1], 1);
	TextDrawColor(EventTD0[1], -1);
	TextDrawUseBox(EventTD0[1], 1);
	TextDrawBoxColor(EventTD0[1], 32);
	TextDrawSetShadow(EventTD0[1], 0);
	TextDrawSetOutline(EventTD0[1], 0);
	TextDrawBackgroundColor(EventTD0[1], 255);
	TextDrawFont(EventTD0[1], 1);
	TextDrawSetProportional(EventTD0[1], 1);
	TextDrawSetShadow(EventTD0[1], 0);

 	EventTD0[0] = TextDrawCreate(148.000000, 358.000213, "Przepisz kod: dS4z5qS54sQ");
	TextDrawLetterSize(EventTD0[0], 0.154500, 1.303332);
	TextDrawTextSize(EventTD0[0], 224.000000, 0.000000);
	TextDrawAlignment(EventTD0[0], 1);
	TextDrawColor(EventTD0[0], -1);
	TextDrawUseBox(EventTD0[0], 1);
	TextDrawBoxColor(EventTD0[0], 32);
	TextDrawSetShadow(EventTD0[0], 0);
	TextDrawSetOutline(EventTD0[0], 0);
	TextDrawBackgroundColor(EventTD0[0], 255);
	TextDrawFont(EventTD0[0], 1);
	TextDrawSetProportional(EventTD0[0], 1);
	TextDrawSetShadow(EventTD0[0], 0);

	Panorama[0] = TextDrawCreate(734.000000, 348.700012, "usebox");
	TextDrawLetterSize(Panorama[0], 0.000000, 13.542593);
	TextDrawTextSize(Panorama[0], -47.000000, 0.000000);
	TextDrawAlignment(Panorama[0], 1);
	TextDrawColor(Panorama[0], 799);
	TextDrawUseBox(Panorama[0], true);
	TextDrawBoxColor(Panorama[0], 0x000000FF);
	TextDrawSetShadow(Panorama[0], 0);
	TextDrawSetOutline(Panorama[0], 0);
	TextDrawFont(Panorama[0], 0);

	recommend_box = TextDrawCreate(258.212860, 412.657775, "______");
	TextDrawLetterSize(recommend_box, 0.189555, 0.813511);
	TextDrawAlignment(recommend_box, 1);
	TextDrawColor(recommend_box, -1);
	TextDrawSetShadow(recommend_box, 0);
	TextDrawSetOutline(recommend_box, -1);
	TextDrawBackgroundColor(recommend_box, 51);
	TextDrawFont(recommend_box, 1);
	TextDrawSetProportional(recommend_box, 1);

	RespectAddBox = TextDrawCreate(501.405609, 268.749786, "box");
	TextDrawLetterSize(RespectAddBox, 0.000000, 1.449999);
	TextDrawTextSize(RespectAddBox, 644.000000, 0.000000);
	TextDrawAlignment(RespectAddBox, 1);
	TextDrawColor(RespectAddBox, -1);
	TextDrawUseBox(RespectAddBox, 1);
	TextDrawBoxColor(RespectAddBox, 80);
	TextDrawSetShadow(RespectAddBox, 0);
	TextDrawSetOutline(RespectAddBox, 0);
	TextDrawBackgroundColor(RespectAddBox, 255);
	TextDrawFont(RespectAddBox, 1);
	TextDrawSetProportional(RespectAddBox, 1);
	TextDrawSetShadow(RespectAddBox, 0); //tlo od respekt++

	PlayerEventBox = TextDrawCreate(287.500000, 394.350189, "box");//od eventow
	TextDrawLetterSize(PlayerEventBox, 0.000000, 3.349996);
	TextDrawTextSize(PlayerEventBox, 441.000000, 0.000000);
	TextDrawAlignment(PlayerEventBox, 1);
	TextDrawColor(PlayerEventBox, -1);
	TextDrawUseBox(PlayerEventBox, 1);
	TextDrawBoxColor(PlayerEventBox, 80);
	TextDrawSetShadow(PlayerEventBox, 0);
	TextDrawSetOutline(PlayerEventBox, 0);
	TextDrawBackgroundColor(PlayerEventBox, 255);
	TextDrawFont(PlayerEventBox, 1);
	TextDrawSetProportional(PlayerEventBox, 1);
	TextDrawSetShadow(PlayerEventBox, 0);

	Panorama[1] = TextDrawCreate(769.000000, 348.700012, "usebox");
	TextDrawLetterSize(Panorama[1], 0.000000, -0.207406);
	TextDrawTextSize(Panorama[1], -47.000000, 0.000000);
	TextDrawAlignment(Panorama[1], 1);
	TextDrawColor(Panorama[1], 799);
	TextDrawUseBox(Panorama[1], true);
	TextDrawBoxColor(Panorama[1], 0xF7741030);
	TextDrawSetShadow(Panorama[1], 0);
	TextDrawSetOutline(Panorama[1], 0);
	TextDrawFont(Panorama[1], 0);

	Panorama[2] = TextDrawCreate(769.000000, 346.700012, "usebox");
	TextDrawLetterSize(Panorama[2], 0.000000, -0.207406);
	TextDrawTextSize(Panorama[2], -47.000000, 0.000000);
	TextDrawAlignment(Panorama[2], 1);
	TextDrawColor(Panorama[2], 799);
	TextDrawUseBox(Panorama[2], true);
	TextDrawBoxColor(Panorama[2], 0xF7741030);
	TextDrawSetShadow(Panorama[2], 0);
	TextDrawSetOutline(Panorama[2], 0);
	TextDrawFont(Panorama[2], 0);

	Panorama[3] = TextDrawCreate(719.000000, -20.411106, "usebox");
	TextDrawLetterSize(Panorama[3], 0.000000, 13.542593);
	TextDrawTextSize(Panorama[3], -62.000000, 0.000000);
	TextDrawAlignment(Panorama[3], 1);
	TextDrawColor(Panorama[3], 799);
	TextDrawUseBox(Panorama[3], true);
	TextDrawBoxColor(Panorama[3], 0x000000FF);
	TextDrawSetShadow(Panorama[3], 0);
	TextDrawSetOutline(Panorama[3], 0);
	TextDrawFont(Panorama[3], 0);

	Panorama[4] = TextDrawCreate(756.500000, 104.033195, "usebox");
	TextDrawLetterSize(Panorama[4], 0.000000, -0.207406);
	TextDrawTextSize(Panorama[4], -59.500000, 0.000000);
	TextDrawAlignment(Panorama[4], 1);
	TextDrawColor(Panorama[4], 799);
	TextDrawUseBox(Panorama[4], true);
	TextDrawBoxColor(Panorama[4], 0xF7741040);
	TextDrawSetShadow(Panorama[4], 0);
	TextDrawSetOutline(Panorama[4], 0);
	TextDrawFont(Panorama[4], 1);

	Panorama[5] = TextDrawCreate(756.500000, 106.033195, "usebox");
	TextDrawLetterSize(Panorama[5], 0.000000, -0.207406);
	TextDrawTextSize(Panorama[5], -59.500000, 0.000000);
	TextDrawAlignment(Panorama[5], 1);
	TextDrawColor(Panorama[5], 799);
	TextDrawUseBox(Panorama[5], true);
	TextDrawBoxColor(Panorama[5], 0xF7741040);
	TextDrawSetShadow(Panorama[5], 0);
	TextDrawSetOutline(Panorama[5], 0);
	TextDrawFont(Panorama[5], 1);

 	 
	
	FlashTextdraw = TextDrawCreate(0.0, 0.0, "~n~~n~~n~~n~~n~~n~~n~");
 	TextDrawLetterSize(FlashTextdraw, 0.0, 10.0);
 	TextDrawUseBox(FlashTextdraw, 1);
 	TextDrawBoxColor(FlashTextdraw, 0xFFFFFFBB);

	Areny = TextDrawCreate(2.000000, 386.000000, "/Onede ~y~(0)~n~/Onede ~y~(0)~n~/Onede ~y~(0)~n~/Onede ~y~(0)~n~/Onede ~y~(0)~n~/Onede ~y~(0)~n~");
	TextDrawBackgroundColor(Areny, 255);
	TextDrawFont(Areny, 1);
	TextDrawLetterSize(Areny, 0.180000, 0.599999);
	TextDrawColor(Areny, -1);
	TextDrawSetOutline(Areny, 1);
	TextDrawSetProportional(Areny, 1);
	TextDrawSetSelectable(Areny, 0);
	
	TimeTD = TextDrawCreate(545.777587, 22.897785, "19:28:42");
	TextDrawLetterSize(TimeTD, 0.339332, 1.923552);
	TextDrawAlignment(TimeTD, 1);
	TextDrawColor(TimeTD, -1);
	TextDrawSetShadow(TimeTD, 2);
	TextDrawSetOutline(TimeTD, -1);
	TextDrawBackgroundColor(TimeTD, 255);
	TextDrawFont(TimeTD, 2);
	TextDrawSetProportional(TimeTD, 1);

	DateTD = TextDrawCreate(568.444824, 12.942254, "04.06.2014");
	TextDrawLetterSize(DateTD, 0.163332, 0.768710);
	TextDrawAlignment(DateTD, 1);
	TextDrawColor(DateTD, -1);
	TextDrawSetShadow(DateTD, 1);
	TextDrawSetOutline(DateTD, -1);
	TextDrawBackgroundColor(DateTD, 255);
	TextDrawFont(DateTD, 2);
	TextDrawSetProportional(DateTD, 1);

	/*
	IntroTD[0] = TextDrawCreate(480.750000, 152.326660, "usebox");
	TextDrawLetterSize(IntroTD[0], 0.000000, 16.524814);
	TextDrawTextSize(IntroTD[0], 160.500000, 0.000000);
	TextDrawAlignment(IntroTD[0], 1);
	TextDrawColor(IntroTD[0], 0);
	TextDrawUseBox(IntroTD[0], true);
	TextDrawBoxColor(IntroTD[0], 102);
	TextDrawSetShadow(IntroTD[0], 0);
	TextDrawSetOutline(IntroTD[0], 0);
	TextDrawFont(IntroTD[0], 0);

	IntroTD[1] = TextDrawCreate(245.000000, 153.813278, "Polski 4Fun Server");
	TextDrawLetterSize(IntroTD[1], 0.449999, 1.600000);
	TextDrawAlignment(IntroTD[1], 1);
	TextDrawColor(IntroTD[1], -1);
	TextDrawSetShadow(IntroTD[1], 0);
	TextDrawSetOutline(IntroTD[1], 1);
	TextDrawBackgroundColor(IntroTD[1], 51);
	TextDrawFont(IntroTD[1], 1);
	TextDrawSetProportional(IntroTD[1], 1);

	IntroTD[2] = TextDrawCreate(188.125000, 171.733276, "~r~~h~Pol~w~ski ~y~~h~Drift~w~/~r~DM~w~/~g~Stunt~w~/~y~RP~w~/~g~Race~w~/~r~Truck");
	TextDrawLetterSize(IntroTD[2], 0.449999, 1.600000);
	TextDrawAlignment(IntroTD[2], 1);
	TextDrawColor(IntroTD[2], -1);
	TextDrawSetShadow(IntroTD[2], 0);
	TextDrawSetOutline(IntroTD[2], 1);
	TextDrawBackgroundColor(IntroTD[2], 51);
	TextDrawFont(IntroTD[2], 1);
	TextDrawSetProportional(IntroTD[2], 1);

	IntroTD[3] = TextDrawCreate(348.125000, 282.240081, "~g~4~y~Fun~r~-~g~Serv~y~.~w~p~r~l");
	TextDrawLetterSize(IntroTD[3], 0.584375, 2.122666);
	TextDrawAlignment(IntroTD[3], 1);
	TextDrawColor(IntroTD[3], -1);
	TextDrawSetShadow(IntroTD[3], 0);
	TextDrawSetOutline(IntroTD[3], 1);
	TextDrawBackgroundColor(IntroTD[3], 51);
	TextDrawFont(IntroTD[3], 1);
	TextDrawSetProportional(IntroTD[3], 1);


	IntroTD[4] = TextDrawCreate(192.000000, 204.000000, "skocznia");
	TextDrawBackgroundColor(IntroTD[4], 0);
	TextDrawFont(IntroTD[4], 5);
	TextDrawLetterSize(IntroTD[4], 0.500000, 1.000000);
	TextDrawColor(IntroTD[4], -1);
	TextDrawSetOutline(IntroTD[4], 0);
	TextDrawSetProportional(IntroTD[4], 1);
	TextDrawSetShadow(IntroTD[4], 1);
	TextDrawUseBox(IntroTD[4], 1);
	TextDrawBoxColor(IntroTD[4], 255);
	TextDrawTextSize(IntroTD[4], 100.000000, 100.000000);
	TextDrawSetPreviewModel(IntroTD[4], 19005);
	TextDrawSetPreviewRot(IntroTD[4], 0.000000, 0.000000, -180.000000, 0.800000);
	TextDrawSetSelectable(IntroTD[4], 0);

	IntroTD[5] = TextDrawCreate(191.000000, 206.000000, "inf");
	TextDrawBackgroundColor(IntroTD[5], 0);
	TextDrawFont(IntroTD[5], 5);
	TextDrawLetterSize(IntroTD[5], 0.500000, 1.000000);
	TextDrawColor(IntroTD[5], -1);
	TextDrawSetOutline(IntroTD[5], 0);
	TextDrawSetProportional(IntroTD[5], 1);
	TextDrawSetShadow(IntroTD[5], 1);
	TextDrawUseBox(IntroTD[5], 1);
	TextDrawBoxColor(IntroTD[5], 255);
	TextDrawTextSize(IntroTD[5], 100.000000, 100.000000);
	TextDrawSetPreviewModel(IntroTD[5], 411);
	TextDrawSetPreviewRot(IntroTD[5], -30.000000, 0.000000, 180.000000, 1.500000);
	TextDrawSetSelectable(IntroTD[5], 0);

	IntroTD[6] = TextDrawCreate(192.000000, 201.000000, "kogut");
	TextDrawBackgroundColor(IntroTD[6], 0);
	TextDrawFont(IntroTD[6], 5);
	TextDrawLetterSize(IntroTD[6], 0.500000, 1.000000);
	TextDrawColor(IntroTD[6], -1);
	TextDrawSetOutline(IntroTD[6], 0);
	TextDrawSetProportional(IntroTD[6], 1);
	TextDrawSetShadow(IntroTD[6], 1);
	TextDrawUseBox(IntroTD[6], 1);
	TextDrawBoxColor(IntroTD[6], 255);
	TextDrawTextSize(IntroTD[6], 100.000000, 100.000000);
	TextDrawSetPreviewModel(IntroTD[6], 19419);
	TextDrawSetPreviewRot(IntroTD[6], -30.000000, 0.000000, 180.000000, 4.000000);
	TextDrawSetSelectable(IntroTD[6], 0);*/

}

#define MAX_TEXTDRAWS _:2048

new TimerOpac[MAX_TEXTDRAWS];
new colorText[MAX_TEXTDRAWS][2];
new colorBox[MAX_TEXTDRAWS][2];
new colorBack[MAX_TEXTDRAWS][2];
 
stock ShowAnn(ann[], time)
{
	if(gmData[timer_ann]>0) 
	{
		TDHide_Ann(0);
		KillTimer(gmData[timer_ann]);
	}
 	TextDrawSetString(AnnDraw, ann);
	TDShowForAll(AnnDraw, ann, 0xFFFFD1FF, 0, 0x00000035, 11, 11, 11);
	gmData[timer_ann] = SetTimerEx("TDHide_Ann", 1000*time, false, "d", 0);	
}

stock ShowAnn2(ann[], time)
{
	if(gmData[timer_ann2]>0) 
	{
		TDHide_Ann(0);
		KillTimer(gmData[timer_ann2]);
	}
 	TextDrawSetString(AnnDraw3, ann);
	TDShowForAll(AnnDraw3, ann, 0xFFFFD1FF, 0, 0x00000035, 11, 11, 11);
	gmData[timer_ann2] = SetTimerEx("TDHide_Ann", 1000*time, false, "d", 3);	
}


stock ShowAnnForPlayers(ann[], time, players[], count, size = sizeof(players)){

	if(count > size) count = size;
	
	TextDrawHideForAll(AnnDraw2);
	TextDrawSetString(AnnDraw2, ann);
	for(new i;i<count;i++)
	{
		if(players[i] <= -1 || !IsPlayerConnected(players[i])) continue; 
		
		TextDrawShowForPlayer(players[i], AnnDraw2);
	}
	if(gmData[timer_evann]>0) 
	{
		KillTimer(gmData[timer_evann]);
	}
	gmData[timer_evann] = SetTimerEx("TDHide_Ann", 1000*time, false, "d", 2);	
}



stock ShowVipAnn(playerid, ann[])
{
	if(gmData[timer_vip_ann] > 0) KillTimer(gmData[timer_vip_ann]);
	new text[MAX_PLAYER_NAME + 256];
	format(text, sizeof(text), "~y~ %s |%d|: ~w~%s", playerNick(playerid), playerid,ann);
 	TDShowForAll(w_olg[2], text, 0xFFFFFFFF, 0, 0, 10, 10, 10);
	
	
	TDShowForAll(w_olg[1], "Ogloszenie VIP!", 0xFFFFFFFF);
	TDShowForAll(w_olg[0], "LD_POKE:cd9s", 0x00000090);
	
	gmData[timer_vip_ann] = SetTimerEx("TDHide_Ann", 1000*15, false, "d", 1);	
}

Public:TDHide_Ann(id) 
{
	switch(id)
	{
		
		case 0:
		{
			KillTimer(gmData[timer_ann]);
			gmData[timer_ann] = 0;
			
			TDHideForAll(AnnDraw);
		}
	
		case 1:
		{
			TextDrawHideForAll(w_olg[0]);
			TextDrawHideForAll(w_olg[1]);
			TextDrawHideForAll(w_olg[2]);
			
			gmData[timer_vip_ann] = 0;
		}
		case 2:
		{
			TextDrawSetString(AnnDraw2, "_");
			TextDrawHideForAll(AnnDraw2);
			gmData[timer_evann] = 0;
		}
		case 3:
		{
			KillTimer(gmData[timer_ann2]);
			gmData[timer_ann] = 0;
			
			TDHideForAll(AnnDraw3);
		}
	}
}
stock TDHideForPlayer(playerid, Text:TextDraw, SpeedText = 8, SpeedBox = 0, SpeedBack = 0)
{
	KillTimer(TimerOpac[_:TextDraw]);
	new OpText, OpBox, OpBack;
	if(SpeedText != 0)
	{
		OpText = colorText[_:TextDraw][1]%256;
		colorText[_:TextDraw][0] = colorText[_:TextDraw][1] - OpText;
	}
	if(SpeedBox != 0)
	{
		OpBox = colorBox[_:TextDraw][1]%256;
		colorBox[_:TextDraw][0] = colorBox[_:TextDraw][1]- OpBox;
	}
	if(SpeedBack != 0)
	{
		OpBack = colorBack[_:TextDraw][1]%256;
		colorBack[_:TextDraw][0] = colorBack[_:TextDraw][1] - OpBack;
	}
	TimerOpac[_:TextDraw] = SetTimerEx("TDForPlayer", 40, true, "uddddb", playerid, _:TextDraw, SpeedText, SpeedBox, SpeedBack, false);
	return 1;
}

stock TDShowForPlayer(playerid, Text:TextDraw, Color, ColorBox = 0, ColorBack = 0, SpeedText = 8, SpeedBox = 0, SpeedBack = 0)
{
	KillTimer(TimerOpac[_:TextDraw]);
	TextDrawHideForPlayer(playerid, TextDraw);
	colorText[_:TextDraw][0] = Color;
	colorBox[_:TextDraw][0] = ColorBox;
	colorBack[_:TextDraw][0] = ColorBack;
	new OpText, OpBox, OpBack;
	if(Color != 0)
	{
		OpText = Color%256;
		colorText[_:TextDraw][1] = Color - OpText;
	}
	if(ColorBox != 0)
	{
		OpBox = ColorBox%256;
		colorBox[_:TextDraw][1] = ColorBox - OpBox;
	}
	if(ColorBack != 0)
	{
		OpBack = ColorBack%256;
		colorBack[_:TextDraw][1] = ColorBack - OpBack;
	}
	TimerOpac[_:TextDraw] = SetTimerEx("TDForPlayer", 40, true, "uddddb", playerid, _:TextDraw, SpeedText, SpeedBox, SpeedBack, true);
	return 1;
}
forward TDForPlayer(playerid, Text:TextDraw, SpeedText, SpeedBox, SpeedBack, bool:Show);
public TDForPlayer(playerid, Text:TextDraw, SpeedText, SpeedBox, SpeedBack, bool:Show)
{
	if(Show)
	{
		if(SpeedText != 0)
		{
			if(colorText[_:TextDraw][0] > colorText[_:TextDraw][1])
			{
				colorText[_:TextDraw][1] += SpeedText;
				if(colorText[_:TextDraw][0] <= colorText[_:TextDraw][1])
				{
					colorText[_:TextDraw][1] = colorText[_:TextDraw][0];
				}
				TextDrawColor(TextDraw, colorText[_:TextDraw][1]);
			}
		}
		if(SpeedBox != 0)
		{
			if(colorBox[_:TextDraw][0] > colorBox[_:TextDraw][1])
			{
				colorBox[_:TextDraw][1] += SpeedBox;
				if(colorBox[_:TextDraw][0] <= colorBox[_:TextDraw][1])
				{
					colorBox[_:TextDraw][1] = colorBox[_:TextDraw][0];
				}
				TextDrawBoxColor(TextDraw, colorBox[_:TextDraw][1]);
			}
		}
		if(SpeedBack != 0)
		{
			if(colorBack[_:TextDraw][0] > colorBack[_:TextDraw][1])
			{
				colorBack[_:TextDraw][1] += SpeedBack;
				if(colorBack[_:TextDraw][0] <= colorBack[_:TextDraw][1])
				{
					colorBack[_:TextDraw][1] = colorBack[_:TextDraw][0];
				}
				TextDrawBackgroundColor(TextDraw, colorBack[_:TextDraw][1]);
			}
		}
		TextDrawShowForPlayer(playerid, TextDraw);
		if(colorText[_:TextDraw][1] == colorText[_:TextDraw][0] && colorBox[_:TextDraw][1] == colorBox[_:TextDraw][0] && colorBack[_:TextDraw][1] == colorBack[_:TextDraw][0])
		{
			KillTimer(TimerOpac[_:TextDraw]);
		}
	}
	else
	{
		if(SpeedText != 0)
		{
			if(colorText[_:TextDraw][0] < colorText[_:TextDraw][1])
			{
				colorText[_:TextDraw][1] -= SpeedText;
				if(colorText[_:TextDraw][0] >= colorText[_:TextDraw][1])
				{
					colorText[_:TextDraw][1] = colorText[_:TextDraw][0];
				}
				TextDrawColor(TextDraw, colorText[_:TextDraw][1]);
			}
		}
		if(SpeedBox != 0)
		{
			if(colorBox[_:TextDraw][0] < colorBox[_:TextDraw][1])
			{
				colorBox[_:TextDraw][1] -= SpeedBox;
				if(colorBox[_:TextDraw][0] >= colorBox[_:TextDraw][1])
				{
					colorBox[_:TextDraw][1] = colorBox[_:TextDraw][0];
				}
				TextDrawBoxColor(TextDraw, colorBox[_:TextDraw][1]);
			}
		}
		if(SpeedBack != 0)
		{
			if(colorBack[_:TextDraw][0] < colorBack[_:TextDraw][1])
			{
				colorBack[_:TextDraw][1] -= SpeedBack;
				if(colorBack[_:TextDraw][0] >= colorBack[_:TextDraw][1])
				{
					colorBack[_:TextDraw][1] = colorBack[_:TextDraw][0];
				}
				TextDrawBackgroundColor(TextDraw, colorBack[_:TextDraw][1]);
			}
		}
		TextDrawShowForPlayer(playerid, TextDraw);
		if(colorText[_:TextDraw][1] == colorText[_:TextDraw][0] && colorBox[_:TextDraw][1] == colorBox[_:TextDraw][0] && colorBack[_:TextDraw][1] == colorBack[_:TextDraw][0])
		{
			KillTimer(TimerOpac[_:TextDraw]);
			TextDrawHideForPlayer(playerid, TextDraw);
		}
	}
	return 1;
}
//for playerText
#define MAX_TEXTDRAWS2 PlayerText:256
new PlayerTimerOpac[MAX_TEXTDRAWS2];
new PlayercolorText[MAX_TEXTDRAWS2][2];
new PlayercolorBox[MAX_TEXTDRAWS2][2];
new PlayercolorBack[MAX_TEXTDRAWS2][2];
stock PlayerTDHideForPlayer(playerid, PlayerText:TextDraw, SpeedText = 8, SpeedBox = 0, SpeedBack = 0)
{
	KillTimer(PlayerTimerOpac[PlayerText:TextDraw]);
	new OpText, OpBox, OpBack;
	if(SpeedText != 0)
	{
		OpText = PlayercolorText[PlayerText:TextDraw][1]%256;
		PlayercolorText[PlayerText:TextDraw][0] = PlayercolorText[PlayerText:TextDraw][1] - OpText;
	}
	if(SpeedBox != 0)
	{
		OpBox = PlayercolorBox[PlayerText:TextDraw][1]%256;
		PlayercolorBox[PlayerText:TextDraw][0] = PlayercolorBox[PlayerText:TextDraw][1]- OpBox;
	}
	if(SpeedBack != 0)
	{
		OpBack = PlayercolorBack[PlayerText:TextDraw][1]%256;
		PlayercolorBack[PlayerText:TextDraw][0] = PlayercolorBack[PlayerText:TextDraw][1] - OpBack;
	}
	PlayerTimerOpac[PlayerText:TextDraw] = SetTimerEx("PlayerTDForPlayer", 40, true, "uddddb", playerid, _:TextDraw, SpeedText, SpeedBox, SpeedBack, false);
	return 1;
}

forward UpdateTimeTD();
public UpdateTimeTD()
{
	new v1, v2, v3, strs[50];
	gettime(v1,v2,v3);
	if(v1 < 10)
	{
		format(strs,50,"0%d.",v1);
	}
	else { 
		format(strs,50,"%d.",v1);
	}
	if(v2 < 10)
	{
		format(strs,50,"%s0%d.",strs,v2);
	}
	else { 
		format(strs,50,"%s%d.",strs,v2);
	}
	if(v3 < 10)
	{
		format(strs,50,"%s0%d",strs,v3);
	}
	else { 
		format(strs,50,"%s%d",strs,v3);
	}
	TextDrawSetString(TimeTD,strs);

	getdate(v3,v2,v1);
	if(v1 < 10)
	{
		format(strs,50,"0%d.",v1);
	}
	else { 
		format(strs,50,"%d.",v1);
	}
	if(v2 < 10)
	{
		format(strs,50,"%s0%d.",strs,v2);
	}
	else { 
		format(strs,50,"%s%d.",strs,v2);
	}
	format(strs,50,"%s%d",strs,v3);
	
	TextDrawSetString(DateTD,strs);
	
	
	return 1;
}

stock PlayerTDShowForPlayer(playerid, PlayerText:TextDraw, Color, PlayercolorBox3 = 0, PlayercolorBack1 = 0, SpeedText = 8, SpeedBox = 0, SpeedBack = 0)
{
	KillTimer(PlayerTimerOpac[PlayerText:TextDraw]);
	PlayerTextDrawHide(playerid, TextDraw);
	PlayercolorText[PlayerText:TextDraw][0] = Color;
	PlayercolorBox[PlayerText:TextDraw][0] = PlayercolorBox3;
	PlayercolorBack[PlayerText:TextDraw][0] = PlayercolorBack1;
	new OpText, OpBox, OpBack;
	if(Color != 0)
	{
		OpText = Color%256;
		PlayercolorText[PlayerText:TextDraw][1] = Color - OpText;
	}
	if(PlayercolorBox3 != 0)
	{
		OpBox = PlayercolorBox3%256;
		PlayercolorBox[PlayerText:TextDraw][1] = PlayercolorBox3 - OpBox;
	}
	if(PlayercolorBack1 != 0)
	{
		OpBack = PlayercolorBack1%256;
		PlayercolorBack[PlayerText:TextDraw][1] = PlayercolorBack1 - OpBack;
	}
	PlayerTimerOpac[PlayerText:TextDraw] = SetTimerEx("PlayerTDForPlayer", 40, true, "uddddb", playerid, _:TextDraw, SpeedText, SpeedBox, SpeedBack, true);
	return 1;
}
forward PlayerTDForPlayer(playerid, PlayerText:TextDraw, SpeedText, SpeedBox, SpeedBack, bool:Show);
public PlayerTDForPlayer(playerid, PlayerText:TextDraw, SpeedText, SpeedBox, SpeedBack, bool:Show)
{	 
	if(Show)
	{
		if(SpeedText != 0)
		{
			if(PlayercolorText[PlayerText:TextDraw][0] > PlayercolorText[PlayerText:TextDraw][1])
			{
				PlayercolorText[PlayerText:TextDraw][1] += SpeedText;
				if(PlayercolorText[PlayerText:TextDraw][0] <= PlayercolorText[PlayerText:TextDraw][1])
				{
					PlayercolorText[PlayerText:TextDraw][1] = PlayercolorText[PlayerText:TextDraw][0];
				}
				PlayerTextDrawColor(playerid, TextDraw, PlayercolorText[PlayerText:TextDraw][1]);
			}
		}
		if(SpeedBox != 0)
		{
			if(PlayercolorBox[PlayerText:TextDraw][0] > PlayercolorBox[PlayerText:TextDraw][1])
			{
				PlayercolorBox[PlayerText:TextDraw][1] += SpeedBox;
				if(PlayercolorBox[PlayerText:TextDraw][0] <= PlayercolorBox[PlayerText:TextDraw][1])
				{
					PlayercolorBox[PlayerText:TextDraw][1] = PlayercolorBox[PlayerText:TextDraw][0];
				}
				PlayerTextDrawBoxColor(playerid, TextDraw, PlayercolorBox[PlayerText:TextDraw][1]);
			}
		}
		if(SpeedBack != 0)
		{
			if(PlayercolorBack[PlayerText:TextDraw][0] > PlayercolorBack[PlayerText:TextDraw][1])
			{
				PlayercolorBack[PlayerText:TextDraw][1] += SpeedBack;
				if(PlayercolorBack[PlayerText:TextDraw][0] <= PlayercolorBack[PlayerText:TextDraw][1])
				{
					PlayercolorBack[PlayerText:TextDraw][1] = PlayercolorBack[PlayerText:TextDraw][0];
				}
				PlayerTextDrawBackgroundColor(playerid, TextDraw, PlayercolorBack[PlayerText:TextDraw][1]);
			}
		}
		PlayerTextDrawShow(playerid, TextDraw);
		if(PlayercolorText[PlayerText:TextDraw][1] == PlayercolorText[PlayerText:TextDraw][0] && PlayercolorBox[PlayerText:TextDraw][1] == PlayercolorBox[PlayerText:TextDraw][0] && PlayercolorBack[PlayerText:TextDraw][1] == PlayercolorBack[PlayerText:TextDraw][0]) KillTimer(PlayerTimerOpac[PlayerText:TextDraw]);
	}
	else
	{
		if(SpeedText != 0)
		{
			if(PlayercolorText[PlayerText:TextDraw][0] < PlayercolorText[PlayerText:TextDraw][1])
			{
				PlayercolorText[PlayerText:TextDraw][1] -= SpeedText;
				if(PlayercolorText[PlayerText:TextDraw][0] >= PlayercolorText[PlayerText:TextDraw][1])
				{
					PlayercolorText[PlayerText:TextDraw][1] = PlayercolorText[PlayerText:TextDraw][0];
				}
				PlayerTextDrawColor(playerid, TextDraw, PlayercolorText[PlayerText:TextDraw][1]);
			}
		}
		if(SpeedBox != 0)
		{
			if(PlayercolorBox[PlayerText:TextDraw][0] < PlayercolorBox[PlayerText:TextDraw][1])
			{
				PlayercolorBox[PlayerText:TextDraw][1] -= SpeedBox;
				if(PlayercolorBox[PlayerText:TextDraw][0] >= PlayercolorBox[PlayerText:TextDraw][1])
				{
					PlayercolorBox[PlayerText:TextDraw][1] = PlayercolorBox[PlayerText:TextDraw][0];
				}
				PlayerTextDrawBoxColor(playerid, TextDraw, PlayercolorBox[PlayerText:TextDraw][1]);
			}
		}
		if(SpeedBack != 0)
		{
			if(PlayercolorBack[PlayerText:TextDraw][0] < PlayercolorBack[PlayerText:TextDraw][1])
			{
				PlayercolorBack[PlayerText:TextDraw][1] -= SpeedBack;
				if(PlayercolorBack[PlayerText:TextDraw][0] >= PlayercolorBack[PlayerText:TextDraw][1])
				{
					PlayercolorBack[PlayerText:TextDraw][1] = PlayercolorBack[PlayerText:TextDraw][0];
				}
				PlayerTextDrawBackgroundColor(playerid, TextDraw, PlayercolorBack[PlayerText:TextDraw][1]);
			}
		}
		PlayerTextDrawShow(playerid, TextDraw);
		if(PlayercolorText[PlayerText:TextDraw][1] == PlayercolorText[PlayerText:TextDraw][0] && PlayercolorBox[PlayerText:TextDraw][1] == PlayercolorBox[PlayerText:TextDraw][0] && PlayercolorBack[PlayerText:TextDraw][1] == PlayercolorBack[PlayerText:TextDraw][0])
		{
			KillTimer(PlayerTimerOpac[PlayerText:TextDraw]);
			PlayerTextDrawHide(playerid, TextDraw);
		}
	}
	return 1;
}
stock TDShowForAll(Text:TextDraw, str[], Color, ColorBox = 0, ColorBack = 0, SpeedText = 8, SpeedBox = 8, SpeedBack = 8)
{ 
	KillTimer(TimerOpac[_:TextDraw]);
	TextDrawHideForAll(TextDraw);
	TextDrawSetString(TextDraw, str);
	colorText[_:TextDraw][0] = Color;
	colorBox[_:TextDraw][0] = ColorBox;
	colorBack[_:TextDraw][0] = ColorBack;
	new OpText, OpBox, OpBack;
	if(Color != 0)
	{
		OpText = Color%256;
		colorText[_:TextDraw][1] = Color - OpText;
	}
	if(ColorBox != 0)
	{
		OpBox = ColorBox%256;
		colorBox[_:TextDraw][1] = ColorBox - OpBox;
	}
	if(ColorBack != 0)
	{
		OpBack = ColorBack%256;
		colorBack[_:TextDraw][1] = ColorBack - OpBack;
	}
	TimerOpac[_:TextDraw] = SetTimerEx("TDForAll", 40, true, "ddddb", _:TextDraw, SpeedText, SpeedBox, SpeedBack, true);
	return 1;
}

stock TDHideForAll(Text:TextDraw, SpeedText = 8, SpeedBox = 0, SpeedBack = 0)
{
	KillTimer(TimerOpac[_:TextDraw]);
	new OpText, OpBox, OpBack;
	if(SpeedText != 0)
	{
		OpText = colorText[_:TextDraw][1]%256;
		colorText[_:TextDraw][0] = colorText[_:TextDraw][1] - OpText;
	}
	if(SpeedBox != 0)
	{
		OpBox = colorBox[_:TextDraw][1]%256;
		colorBox[_:TextDraw][0] = colorBox[_:TextDraw][1]- OpBox;
	}
	if(SpeedBack != 0)
	{
		OpBack = colorBack[_:TextDraw][1]%256;
		colorBack[_:TextDraw][0] = colorBack[_:TextDraw][1] - OpBack;
	}
	TimerOpac[_:TextDraw] = SetTimerEx("TDForAll", 60, true, "ddddb", _:TextDraw, SpeedText, SpeedBox, SpeedBack, false);
	return 1;
}
forward TDForAll(Text:TextDraw, SpeedText, SpeedBox, SpeedBack, bool:Show);
public TDForAll(Text:TextDraw, SpeedText, SpeedBox, SpeedBack, bool:Show)
{
	if(Show)
	{
		if(SpeedText != 0)
		{
			if(colorText[_:TextDraw][0] > colorText[_:TextDraw][1])
			{
				colorText[_:TextDraw][1] += SpeedText;
				if(colorText[_:TextDraw][0] <= colorText[_:TextDraw][1])
				{
					colorText[_:TextDraw][1] = colorText[_:TextDraw][0];
				}
				
				//printf("%x",colorText[_:TextDraw][1]);
				TextDrawColor(TextDraw, colorText[_:TextDraw][1]);
			}
		}
		if(SpeedBox != 0)
		{
			if(colorBox[_:TextDraw][0] > colorBox[_:TextDraw][1])
			{
				colorBox[_:TextDraw][1] += SpeedBox;
				if(colorBox[_:TextDraw][0] <= colorBox[_:TextDraw][1])
				{
					colorBox[_:TextDraw][1] = colorBox[_:TextDraw][0];
				}
				TextDrawBoxColor(TextDraw, colorBox[_:TextDraw][1]);
			}
		}
		if(SpeedBack != 0)
		{
			if(colorBack[_:TextDraw][0] > colorBack[_:TextDraw][1])
			{
				colorBack[_:TextDraw][1] += SpeedBack;
				if(colorBack[_:TextDraw][0] <= colorBack[_:TextDraw][1])
				{
					colorBack[_:TextDraw][1] = colorBack[_:TextDraw][0];
				}
				TextDrawBackgroundColor(TextDraw, colorBack[_:TextDraw][1]);
			}
		}
		if(TextDraw == AnnDraw || TextDraw == AnnDraw3)
		{
			for(new _i_, _x_ = MAX_PLAYERS;_i_<_x_; _i_++)
			{
				if(pInfo[_i_][player_hidehud][hud_ann])
				{
					if(IsTextDrawShowForPlayer(_i_, TextDraw)) TextDrawHideForPlayer(_i_, TextDraw);
				}
				else 
				{
					TextDrawShowForPlayer(_i_, TextDraw);
				}
			}
		}
		else 
			TextDrawShowForAll(TextDraw);
			
		if(colorText[_:TextDraw][1] == colorText[_:TextDraw][0] && colorBox[_:TextDraw][1] == colorBox[_:TextDraw][0] && colorBack[_:TextDraw][1] == colorBack[_:TextDraw][0])
			KillTimer(TimerOpac[_:TextDraw]);
	}
	else
	{
		if(SpeedText != 0)
		{
			if(colorText[_:TextDraw][0] < colorText[_:TextDraw][1])
			{
				colorText[_:TextDraw][1] -= SpeedText;
				if(colorText[_:TextDraw][0] >= colorText[_:TextDraw][1])
				{
					colorText[_:TextDraw][1] = colorText[_:TextDraw][0];
				}
				TextDrawColor(TextDraw, colorText[_:TextDraw][1]);
			}
		}
		if(SpeedBox != 0)
		{
			if(colorBox[_:TextDraw][0] < colorBox[_:TextDraw][1])
			{
				colorBox[_:TextDraw][1] -= SpeedBox;
				if(colorBox[_:TextDraw][0] >= colorBox[_:TextDraw][1])
				{
					colorBox[_:TextDraw][1] = colorBox[_:TextDraw][0];
				}
				TextDrawBoxColor(TextDraw, colorBox[_:TextDraw][1]);
			}
		}
		if(SpeedBack != 0)
		{
			if(colorBack[_:TextDraw][0] < colorBack[_:TextDraw][1])
			{
				colorBack[_:TextDraw][1] -= SpeedBack;
				if(colorBack[_:TextDraw][0] >= colorBack[_:TextDraw][1])
				{
					colorBack[_:TextDraw][1] = colorBack[_:TextDraw][0];
				}
				TextDrawBackgroundColor(TextDraw, colorBack[_:TextDraw][1]);
			}
		}
		
		if(TextDraw == AnnDraw || TextDraw == AnnDraw3)
		{
			for(new _i_, _x_ = MAX_PLAYERS;_i_<_x_; _i_++)
			{
				if(pInfo[_i_][player_hidehud][hud_ann])
				{
					if(IsTextDrawShowForPlayer(_i_, TextDraw)) TextDrawHideForPlayer(_i_, TextDraw);
				}
				else 
				{
					TextDrawShowForPlayer(_i_, TextDraw);
				}
			}
		}
		else 
			TextDrawShowForAll(TextDraw);
			
 		if(colorText[_:TextDraw][1] == colorText[_:TextDraw][0] && colorBox[_:TextDraw][1] == colorBox[_:TextDraw][0] && colorBack[_:TextDraw][1] == colorBack[_:TextDraw][0])
		{
			KillTimer(TimerOpac[_:TextDraw]);
			TextDrawHideForAll(TextDraw);
		}
	}
	return 1;
}
new fleashScreen[ MAX_PLAYERS ];
FlashScreen(playerid)
{
	TextDrawShowForPlayer(playerid, FlashTextdraw);

	if(fleashScreen[playerid]) KillTimer(fleashScreen[playerid]);
	fleashScreen[playerid] = SetTimerEx("FlashScreen_End", 70, false, "i", playerid);
}

forward FlashScreen_End(playerid);
public FlashScreen_End(playerid)
{
	TextDrawHideForPlayer(playerid, FlashTextdraw);
	fleashScreen[playerid] = 0;
}

/*
forward UpdatePlayerIntro(playerid, td_step);
public UpdatePlayerIntro(playerid, td_step)
{
	switch(td_step)
	{
		case -10:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~______Server");
		case -9:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~______Server");
		case -8:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~______Server");
		case -7:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~______Server");
		case -6:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~______Server");
		case -5:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~______Server");
		case -4:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~______Server");
		case -3:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~______Server");
		case -2:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~______Server");
		case -1:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~______Server");
		case 0:PlayerTextDrawSetString(playerid, IntroPlayerTD, "~r~N~w~ajlepszy Polski ~n~______Server");
		case 1:PlayerTextDrawSetString(playerid, IntroPlayerTD, "~r~~h~N~r~a~w~jlepszy Polski ~n~______Server");
		case 2:PlayerTextDrawSetString(playerid, IntroPlayerTD, "~r~~h~~h~N~r~~h~a~r~j~w~lepszy Polski ~n~______Server");
		case 3:PlayerTextDrawSetString(playerid, IntroPlayerTD, "~r~~h~~h~~h~N~r~~h~~h~a~r~~h~j~r~l~w~epszy Polski ~n~______Server");
		case 4:PlayerTextDrawSetString(playerid, IntroPlayerTD, "~r~~h~~h~~h~~h~N~r~~h~~h~~h~a~r~~h~~h~j~r~~h~l~r~e~w~pszy Polski ~n~______Server");
		case 5:PlayerTextDrawSetString(playerid, IntroPlayerTD, "~r~~h~~h~~h~~h~~h~N~r~~h~~h~~h~~h~a~r~~h~~h~~h~j~r~~h~~h~l~r~~h~e~r~p~w~szy Polski ~n~______Server");
		case 6:PlayerTextDrawSetString(playerid, IntroPlayerTD, "N~r~~h~~h~~h~~h~~h~a~r~~h~~h~~h~~h~j~r~~h~~h~~h~l~r~~h~~h~e~r~~h~p~r~s~w~zy Polski ~n~______Server");
		case 7:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Na~r~~h~~h~~h~~h~~h~j~r~~h~~h~~h~~h~l~r~~h~~h~~h~e~r~~h~~h~p~r~~h~s~r~z~w~y Polski ~n~______Server");
		case 8:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Naj~r~~h~~h~~h~~h~~h~l~r~~h~~h~~h~~h~e~r~~h~~h~~h~p~r~~h~~h~s~r~~h~z~r~y~w~ Polski ~n~______Server");
		case 9:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najl~r~~h~~h~~h~~h~~h~e~r~~h~~h~~h~~h~p~r~~h~~h~~h~s~r~~h~~h~z~r~~h~y~r~ ~w~Polski ~n~______Server");
		case 10:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najle~r~~h~~h~~h~~h~~h~p~r~~h~~h~~h~~h~s~r~~h~~h~~h~z~r~~h~~h~y~r~~h~ ~r~P~w~olski ~n~______Server");
		case 11:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlep~r~~h~~h~~h~~h~~h~s~r~~h~~h~~h~~h~z~r~~h~~h~~h~y~r~~h~~h~ ~r~~h~P~r~o~w~lski ~n~______Server");
		case 12:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najleps~r~~h~~h~~h~~h~~h~z~r~~h~~h~~h~~h~y~r~~h~~h~~h~ ~r~~h~~h~P~r~~h~o~r~l~w~ski ~n~______Server");
		case 13:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepsz~r~~h~~h~~h~~h~~h~y~r~~h~~h~~h~~h~ ~r~~h~~h~~h~P~r~~h~~h~o~r~~h~l~r~s~w~ki ~n~______Server");
		case 14:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy~r~~h~~h~~h~~h~~h~ ~r~~h~~h~~h~~h~P~r~~h~~h~~h~o~r~~h~~h~l~r~~h~s~r~k~w~i ~n~______Server");
		case 15:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy ~r~~h~~h~~h~~h~~h~P~r~~h~~h~~h~~h~o~r~~h~~h~~h~l~r~~h~~h~s~r~~h~k~r~i~w~ ~n~______Server");
		case 16:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy P~r~~h~~h~~h~~h~~h~o~r~~h~~h~~h~~h~l~r~~h~~h~~h~s~r~~h~~h~k~r~~h~i~r~ ~w~~n~______Server");
		case 17:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~_~r~~h~~h~~h~~h~~h~_~r~~h~~h~~h~~h~_~r~~h~~h~~h~_~r~~h~~h~_~r~~h~_~r~S~w~erver");
		case 18:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~__~r~~h~~h~~h~~h~~h~_~r~~h~~h~~h~~h~_~r~~h~~h~~h~_~r~~h~~h~_~r~~h~S~r~e~w~rver");
		case 19:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~___~r~~h~~h~~h~~h~~h~_~r~~h~~h~~h~~h~_~r~~h~~h~~h~_~r~~h~~h~S~r~~h~e~r~r~w~ver");
		case 20:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~____~r~~h~~h~~h~~h~~h~_~r~~h~~h~~h~~h~_~r~~h~~h~~h~S~r~~h~~h~e~r~~h~r~r~v~w~er");
		case 21:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~_____~r~~h~~h~~h~~h~~h~_~r~~h~~h~~h~~h~S~r~~h~~h~~h~e~r~~h~~h~r~r~~h~v~r~e~w~r");
		case 22:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~______~r~~h~~h~~h~~h~~h~S~r~~h~~h~~h~~h~e~r~~h~~h~~h~r~r~~h~~h~v~r~~h~e~r~r");
		case 23:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~______S~r~~h~~h~~h~~h~~h~e~r~~h~~h~~h~~h~r~r~~h~~h~~h~v~r~~h~~h~e~r~~h~r");
		case 24:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~______Se~r~~h~~h~~h~~h~~h~r~r~~h~~h~~h~~h~v~r~~h~~h~~h~e~r~~h~~h~r");
		case 25:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~______Ser~r~~h~~h~~h~~h~~h~v~r~~h~~h~~h~~h~e~r~~h~~h~~h~r");
		case 26:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~______Serv~r~~h~~h~~h~~h~~h~e~r~~h~~h~~h~~h~r");
		case 27:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~______Serve~r~~h~~h~~h~~h~~h~r");
		case 28:PlayerTextDrawSetString(playerid, IntroPlayerTD, "Najlepszy Polski ~n~______Server");
	}
	
	if(td_step != 28)
	{	
		SetTimerEx("UpdatePlayerIntro", 150, false, "dd", playerid, td_step + 1);
		//SendClientMessage(playerid, -1, "step %d", td_step+1);
	}
	else
	{ 
		
		if(pInfo[playerid][player_id]>0)ShowPlayerDialogLogin(playerid, "");
		else 
		{
			Dialog_Show(playerid, Register_1, DIALOG_STYLE_PASSWORD, "Rejestracja (1/3)", ""HEX_ERROR"Rejestracja nie jest i nigdy nie bêdzie obowi¹zkowa!"HEX_SAMP"\n\n\nCzy chcesz siê zarejestrowaæ na serwerze? dziêki rejestracji Twoje statystyki bêd¹ zapisywane\
			\nJe¿eli chcesz siê zarejestrowaæ na serwerze wpisz poni¿ej swoje has³o:", "Dalej", "Zamknij");
		}
		for(new i;i<7;i++) TextDrawHideForPlayer(playerid, IntroTD[i]);
		PlayerTextDrawHide(playerid, IntroPlayerTD);
	}
}*/

new ce_stage = 0x72;
new ce_color = 0x00000035;

#define SPEED 8
forward coloredEffect();
public coloredEffect()
{
	new bit[1];
	bit[0] = ce_color;
	
	#define bit_r bit{0}
	#define bit_g bit{1}
	#define bit_b bit{2}
	
	switch(ce_stage)
	{
		case 0x72: //(r)
		{ 
			if((bit_r + SPEED) >= 255)
			{
				ce_stage = 0x68;
				bit_r = 255;
			} else 
				bit_r += SPEED;
		
		}		
		case 0x68: //(g)
		{
		 
			
			if((bit_r - SPEED) <= 0)
			{
				bit_r = 0;
			} else bit_r -= SPEED;
			
			if((bit_g + SPEED) >= 255)
			{
				ce_stage = 0x63;
				bit_g = 255;
			} else 	bit_g += SPEED;
			 
		}
		case 0x63: //(b)
		{
			if((bit_g - SPEED) <= 0)
			{
				bit_g = 0;
			} else bit_g -= SPEED;
			
			if((bit_b + SPEED) >= 255)
			{
				ce_stage = 0x73;
				bit_b = 255;
			} else 	bit_b += SPEED;
		}
		case 0x73: //(r+b)
		{
			if((bit_b - SPEED) <= 0)
			{
				bit_b = 0;
			} else bit_b -= SPEED;
			
			if((bit_r + SPEED) >= 255)
			{
				ce_stage = 0x68;
				bit_r = 255;
			} else 	bit_r += SPEED;
			
		}
	}
	ce_color = bit[0];
	TextDrawBoxColor(PasekBelt[0], ce_color);
	
	foreach(new playerid : Player) if(IsTextDrawShowForPlayer(playerid, PasekBelt[0])) TextDrawShowForPlayer(playerid, PasekBelt[0]), TextDrawShowForPlayer(playerid, PasekBelt[1]); 

	//printf("Color: %08x stage %c (0x%x)", ce_color, ce_stage, ce_stage);
}
