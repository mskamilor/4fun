/*
		Fishing <2.0>
	(c) Copyright 2013-2014 by mrdrifter

	@author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
	@date      : 04 marca 2013
	@update    : ---

*/

 
stock AddNewFishingPos(Float:fX, Float:fY, Float:fZ)
{
	fData[fCount][fishing_pos][0] = fX;
	fData[fCount][fishing_pos][1] = fY;
	fData[fCount][fishing_pos][2] = fZ;
	
	fData[fCount][fishing_used] = true;
	
	Create3DTextLabel("{FF0000}Jesli chcesz lowic ryby kliknij {FFFFFF}ENTER{FF0000}\n{FF0000}Jesli chcesz przestac, kliknij {FFFFFF}ENTER\n{FF8000}aby wylowic rybe {FFFFFF}SPRINT", 0xFFFFFFFF+90, fData[fCount][fishing_pos][0], fData[fCount][fishing_pos][1], fData[fCount][fishing_pos][2] + 1.5, 30.0, 0);
	CreateDynamicPickup(1239, 1, fData[fCount][fishing_pos][0], fData[fCount][fishing_pos][1], fData[fCount][fishing_pos][2], 0);
		
	fCount++;
}
stock IsPlayerInFishingPos(playerid)
{
	for(new i;i<fCount;i++)
		if(IsPlayerInRangeOfPoint(playerid, 2.5, fData[i][fishing_pos][0], fData[i][fishing_pos][1], fData[i][fishing_pos][2])) return 1;
		
	return 0;
}
stock fishing_OnGameModeInit()
{
	AddNewFishingPos(716.1619, -1702.7205, 2.4297); 
	AddNewFishingPos(716.0861, -1636.9779, 2.4297); 
	AddNewFishingPos(716.1090, -1628.5979, 2.4297); 
	AddNewFishingPos(716.0911, -1694.2964, 2.4297); 
	AddNewFishingPos(723.1884, -1496.0131, 1.9343); 
	AddNewFishingPos(-69.3166, -577.2592, 1.3892); 
	AddNewFishingPos(-803.2867, -1933.9380, 6.3065); 
	AddNewFishingPos(1893.8712, 1562.7358, 10.8203); 
	AddNewFishingPos(1924.4570, 1555.6299, 10.8203);
}
