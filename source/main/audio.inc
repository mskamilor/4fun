#if defined ADUIO_PLUGIN
CMD:pdj(playerid,params[])
{
	if(!pInfo[playerid][player_dj])
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Nie posiadasz uprawnieñ do korzystania z tej komendy.");
		return 1;
	}
	if(!Audio_IsClientConnected(playerid))
	{
		ShowPlayerDialog(playerid,9999,DIALOG_STYLE_MSGBOX,"{FF0000}Audio Plugin - B³¹d!","{0397EF}Nie posiadasz audio pluginu!\n{0397EF}Mo¿esz go pobraæ z naszej strony:\n\t{16C60D}"AUDIO_URL"\n{0397EF}Audio plugin daje Ci sporo mo¿liwoœci np:\n\t{0397EF}Otwarzanie swoich ulubionych stacji radiowych\n\t{0397EF}Dostawania powiadomieñ g³osowych przy osi¹gniêciach, prywatnych wiadomoœciach itp...","Zamknij","");
		return 1;
	}
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, 2225.9233, 1025.3739, 11.9559))
	{
		SendClientMessage(playerid, COLOR_ERROR, ""chat" Musisz byæ przy konsoli dja!.");
		return 1;
	}
	Dialog_Show(playerid, DIALOG_DJ, DIALOG_STYLE_LIST, "{16C60D}R{0397EF}a{16C60D}d{0397EF}i{16C60D}o", "{0397EF}Wybierz stacje\n{0397EF}URL", "Wybierz", "Anuluj");
	return 1;
}
CMD:radio2(playerid,cmdtext[])
{
	if(!Audio_IsClientConnected(playerid))
	{
		ShowPlayerDialog(playerid,9999,DIALOG_STYLE_MSGBOX,"{FF0000}Audio Plugin - B³¹d!","{0397EF}Nie posiadasz audio pluginu!\n{0397EF}Mo¿esz go pobraæ z naszej strony:\n\t{16C60D}"AUDIO_URL"\n{0397EF}Audio plugin daje Ci sporo mo¿liwoœci np:\n\t{0397EF}Otwarzanie swoich ulubionych stacji radiowych\n\t{0397EF}Dostawania powiadomieñ g³osowych przy osi¹gniêciach, prywatnych wiadomoœciach itp...","Zamknij","");
		return 1;
	}
	achievement(playerid, 14);
	Dialog_Show(playerid, DIALOG_RADIO, DIALOG_STYLE_LIST, "{16C60D}R{0397EF}a{16C60D}d{0397EF}i{16C60D}o", "{0397EF}Wybierz stacje\n{0397EF}Ustaw G³oœnoœæ\n{16C60D}Wylacz radio", "Wybierz", "Anuluj");
	return 1;
}
Dialog:DIALOG_STACJE_DJ(playerid, response, listitem, inputtext[])
{
	if(!response) 
		return 0;
	format(gmData[impreza_sound], sizeof(gmData[impreza_sound]),"%s",StacjeRadiowe[listitem][URL]);
	foreach(new i:Player)
	{
		if(IsPlayerInDynamicArea(i, gmData[impreza_zone]))
		{
			if(Audio_IsClientConnected(i))
			{
				if( pInfo[i][player_impreza])
				{
					Audio_Pause(i, pInfo[i][player_impreza]);
				}
				pInfo[i][player_impreza] = Audio_PlayStreamed(i, gmData[impreza_sound]);
				Audio_Set3DPosition(i, pInfo[i][player_impreza], 2235.1514,1025.7859,10.8892, 25.0);
				SendClientMessage(i,COLOR_GOLDENROD,""chat" DJ {b}%s{/b} zmieni³ stacjê radiow¹ na: {b}%s",pInfo[playerid][player_name],StacjeRadiowe[listitem][Nazwa]);
			}
		}
	}
	return 1;
}
Dialog:DIALOG_DJ_URL(playerid, response, listitem, inputtext[])
{
	if(!response) 
		return 0;
	if(!inputtext[0])
	{
		Dialog_Show(playerid, DIALOG_DJ_URL, DIALOG_STYLE_INPUT, "{16C60D}Podaj bezpoœredni link!", "#1\nPodaj bezpoœredni adres do piosenki/utworu\nNP: http://s.4fun-serv.pl/join.mp3", "Wybieram", "Anuluj...");
		return 1;	
	}
	if(!IsValidUrl(inputtext))
	{
		Dialog_Show(playerid, DIALOG_DJ_URL, DIALOG_STYLE_INPUT, "{16C60D}Podaj bezpoœredni link!", "#2\nPodaj bezpoœredni adres do piosenki/utworu\nNP: http://s.4fun-serv.pl/join.mp3", "Wybieram", "Anuluj...");
		return 1;
	}
	format(gmData[impreza_sound], sizeof(gmData[impreza_sound]),"%s",inputtext);
	foreach(new i:Player)
	{
		if(IsPlayerInDynamicArea(i, gmData[impreza_zone]))
		{
			if(Audio_IsClientConnected(i))
			{
				if( pInfo[i][player_impreza])
				{
					Audio_Pause(i, pInfo[i][player_impreza]);
				}
				pInfo[i][player_impreza] = Audio_PlayStreamed(i, gmData[impreza_sound], false, true, false);
				Audio_Set3DPosition(i, pInfo[i][player_impreza], 2235.1514, 1025.7859, 10.8892, 25.0);
			}
		}
	}
	SendClientMessage(playerid,COLOR_GOLDENROD,"Zmieniles na: %s",gmData[impreza_sound]);
	return 1;
}
Dialog:DIALOG_DJ(playerid, response, listitem, inputtext[])
{
	if(!response) 
		return 0;
	switch(listitem)
	{
		case 0:
		{
			string2[0] = EOS;
			for(new i = 0;i<sizeof(StacjeRadiowe);i++)
			{
				format(string2,sizeof(string2),"%s%s\n",string2, StacjeRadiowe[i][Nazwa]);
			}
			Dialog_Show(playerid, DIALOG_STACJE_DJ, DIALOG_STYLE_LIST, "{16C60D}Wybierz stacje radiow¹", string2, "Wybieram", "Anuluj...");
			return 1;
		}
		case 1:
		{
			Dialog_Show(playerid, DIALOG_DJ_URL, DIALOG_STYLE_INPUT, "{16C60D}Podaj bezpoœredni link!", "Podaj bezpoœredni adres do piosenki/utworu\nNP: http://s.4fun-serv.pl/join.mp3", "Wybieram", "Anuluj...");
			return 1;
		}
	}
	return 1;
}
Dialog:DIALOG_STACJE(playerid, response, listitem, inputtext[])
{
	if(!response) 
		return 0;
	SendClientMessage(playerid, COLOR_NAVAJO_WHITE, "» Wybra³eœ %s", StacjeRadiowe[listitem][Nazwa]);
	Audio_PlayStreamedEx(playerid,StacjeRadiowe[listitem][URL]);
	return 1;
}
Dialog:DIALOG_RADIO(playerid, response, listitem, inputtext[])
{
	if(!response) 
		return 0;
	switch(listitem)
	{
		case 0:
		{
			string2[0] = EOS;
			for(new i = 0;i<sizeof(StacjeRadiowe);i++)
			{
				format(string2,sizeof(string2),"%s%s\n",string2, StacjeRadiowe[i][Nazwa]);
			}
			Dialog_Show(playerid, DIALOG_STACJE, DIALOG_STYLE_LIST, "{16C60D}Wybierz stacje radiow¹", string2, "Wybieram", "Anuluj...");
			return 1;
		}
		case 1:
		{
			static buffer[1024];
			buffer[0] = EOS;
			for(new i = 0;i<101;i++)
			{
				format(buffer,sizeof buffer,"%s%i %\n",buffer,i);
			}
			Dialog_Show(playerid, DIALOG_GLOSNOSC, DIALOG_STYLE_LIST, "{16C60D}Ustaw G³oœnoœæ", buffer, "Wybieram", "Anuluj...");
			return 1;
		}
		case 2:
		{
			Audio_StreamedStopEx(playerid);
			SendClientMessage(playerid, COLOR_NAVAJO_WHITE, ""chat"  Radio zosta³o {b}wy³¹czone!");
			return 1;
		}
	}
	return 1;
}
 

/*
CMD:audiot(playerid,params[]) 
{
	if(!Audio_IsClientConnected(playerid)) 
		return 0;
	SendClientMessage(playerid,COLOR_DARK_GREEN, "MASZ AUDIO PLUGSA!.");
	Audio_TransferPack(playerid);
	return 1;
}
CMD:t(p,params[]) {
	if(Audio_IsClientConnected(p)) SendClientMessage(p, -1, "polaczony!");
	else SendClientMessage(p, -1, "nie polaczony!");
	return 1;
}
CMD:radiotest(playerid, params[])
{
    Audio_TransferPack(playerid);
	Audio_Play(playerid, 1, false, true, false);
	return 1;
}
*/
#endif