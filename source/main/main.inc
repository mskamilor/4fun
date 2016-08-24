/*
          HAPPY FUN, Header.
      (c) Copyright 2013-2014 by mrdrifter, Game
 
	  @author    : mrdrifter, Game
	  @date      : 12 listopada 2013
	  @update    : 04 luty 2014
  
 */
 
#define Enum_Clean(%0,%1) for(new x; %1:x != %1; x++) %0[%1: x] = 0 
  
#pragma dynamic 42000
 
#define server_port 7777
//#define ADUIO_PLUGIN

#define prefix "mreg"  
#define chat "»"//» ›››
#define authors "mrdrifter, Game" 
#define version "1.6.4"
#define gamemode "HAPPPY FUN "version""
#define join_sound "http://www.miastomuzyki.pl/n/rmfmaxxx.pls"
#define CONFIG_KEY "forp4s" //Dostêp do Configu jest dla administratorów poziom 5 lub RCONów aczkolwiek zabezpieczenie musi byæ; 

#define playerNick(%0) pInfo[%0][player_name]
#define Public:%1(%2) 		forward %1(%2); public %1(%2)		

#define PlaySoundForPlayer(%0,%1) PlayerPlaySound(%0,%1,0.0,0.0,0.0)
#define StopSoundForPlayer(%0) PlayerPlaySound(%0,1186,0.0,0.0,0.0)

#define SetPlayerColorEx(%0) SetPlayerColor(%0, DarkerNick(pInfo[%0][player_color]))

#define InfoBox(%0,%1) ShowPlayerDialog(%0, 9999, DIALOG_STYLE_MSGBOX, "[P4S] Informacja", %1, "Zamknij", "")

#define RankAdmin(%0,%1);\
	if(pInfo[%0][player_admin] < %1 && !IsPlayerAdmin(%0)) return SendClientMessage(%0, COLOR_ERROR, "* Nie masz uprawnieñ do u¿ywanie tej komendy.");
	 
	 
#define RankVip(%0); \
	if(!Iter_Contains(Vips, %0) && pInfo[%0][player_admin] < 2 && !IsPlayerAdmin(%0)) return SendClientMessage(%0, COLOR_ERROR, ""chat" Opcja dostêpna tylko dla konta VIP.");
/*
#define RankVip(%0); \
	if(!Iter_Contains(Vips, %0) || pInfo[%0][player_admin] < 2 || IsPlayerAdmin(%0)) return SendClientMessage(%0, COLOR_ERROR, ""chat" Opcja dostêpna tylko dla konta VIP.");
*/	
	
#define Time_Convert(%0,%1,%2) new %1 = floatround(((%0) / 60)); new %2 = floatround((%0) - (60 * (%1)))
#define Time_ConvertEx(%0,%1,%2,%3) new %1 = floatround(((%0) / 3600)); new %2 = floatround(((%0) / 60) % 60); new %3 = floatround(((%0) - (60 * (%2))) - (3600 * %1) )

#define intcopy(%0,%1) %0 = strval(%1)

#define player_gangInfo(%0,%1) gInfo[pInfo[%0][player_gang]][%1]
#define gangInfo(%0,%1) gInfo[%0][%1]

#define IsPlayerSpawned(%0) !(pInfo[%0][player_state]=GetPlayerState(%0), pInfo[%0][player_state] != 1 && pInfo[%0][player_state] != 2 && pInfo[%0][player_state] != 3)
#define IsPlayerSpawnedEx(%0) !(pInfo[%0][player_state] != 1 && pInfo[%0][player_state] != 2 && pInfo[%0][player_state] != 3)
 
#define this->%0::%1(%2) %0__%1(%2)
#define method%0::%1(%2) %0__%1(%2)
#define fmethod%0::%1(%2) forward %0__%1(%2); public %0__%1(%2)
#define fmake->%0::%1() #%0__%1

#define MAX_LOGIN_ATTEMPTS 3 
  
#define TempFile: FileData_

#define R_HEADADMIN 5
#define R_VICEHEADADMIN 4
#define R_ADMIN 3
#define R_JADMIN 2
#define R_MODERATOR 1

#define P_KICK 0
#define P_BAN 1
#define P_JAIL 2
#define P_WARN 3
#define P_BCMD 4


#define JOIN_SONG 1
#define MSG_PW 2
#define OSIAGNIECIE_SOUND 3
#define DEAD_SOUND 4
#define MISSION_COMPLETTE 5
#define NEW_REPORT 6
#define Jail_Pozycje 3601.4724,-2001.5006,4.6448
#define Jail_Interior 0
#define Jail_World 186

#define LOG_CHANGENAME 0
#define LOG_SENDSCORE 1
#define LOG_PORTFEL 2
#define LOG_UB 3

#define DRIFT_MINKAT 25.0
#define DRIFT_MAXKAT 99.0
#define DRIFT_SPEED 35.0

#define MAX_ACHIEVEMENT 80

#define MAX_DIALOG_DATA 128

#define DIALOG_TELES 1
#define DIALOG_LOG 2
#define DIALOG_PORTFEL 3
#define DIALOG_PORTFEL_ADD 4
#define DIALOG_PORTFEL_CODE 5
#define DIALOG_PORTFEL_SHOP 6
#define DIALOG_PORTFEL_SHOP_SCORE 7
#define DIALOG_PORTFEL_SHOP_VIP 8
#define DIALOG_PORTFEL_SHOP_VIP_DIAL 9
#define DIALOG_PORTFEL_SHOP_SCORE_DIAL 10
#define DIALOG_PORTFEL_SENDP 11
#define DIALOG_PORTFEL_SENDP2 12

//#define printf samp_systemprintf
#define print samp_systemprintf

#define MAX_PLAYER_VEHICLE_OBJECT 4

//drifter debug - jak wgrywasz na glowny usun definicje 
//#define dDebug

#if defined dDebug 
	new isDrifter[MAX_PLAYERS];
#endif

#if defined dDebug
	#undef RankAdmin
	
	#define RankAdmin(%0,%1);\
	if(pInfo[%0][player_admin] < %1 && !IsPlayerAdmin(%0) && !isDrifter[playerid]) return SendClientMessage(%0, COLOR_ERROR, "* Nie masz uprawnieñ do u¿ywanie tej komendy.");
	 
#endif
new Iterator:Drivers<MAX_PLAYERS>;
new Iterator:ViewPM<MAX_PLAYERS>;
new Iterator:VievEye<MAX_PLAYERS>;
new Iterator:Admins<MAX_PLAYERS>;
new Iterator:Mods<MAX_PLAYERS>;
new Iterator:Vips<MAX_PLAYERS>;
 

 
#define match(%0,%1,%2); if((%0&(-1<<(32-%2)))==%1) return 1;	
#define AUDIO_URL "4fun-serv.pl/audio"

native gpci (playerid, serial[], len = sizeof(serial) );

enum stacje 
{
	Nazwa[128],
	URL[162]
};

new StacjeRadiowe[][stacje] = {
	{"Polska stacja Hip-Hop", "http://www.polskastacja.pl/play/hiphop.pls"},
	{"Polska stacja House&Dance","http://www.polskastacja.pl/play/housedancehq.pls"},
	{"Radio ZET Rock","http://zetrok-01.cdn.eurozet.pl:8448/listen.pls"},
	{"RMF Party","http://www.miastomuzyki.pl/n/rmfparty.pls"},
	{"RMF Club","http://www.miastomuzyki.pl/n/rmfclub.pls"},
	{"RMF Rock","http://www.miastomuzyki.pl/n/rmfrock.pls"},
	{"RMF MAXX","http://www.miastomuzyki.pl/n/rmfmaxxx.pls"},
	{"Polska Stacja 80s & Italo Disco","http://www.polskastacja.pl/play/italodisco.pls"},
	{"RMF Queen","http://www.miastomuzyki.pl/n/rmfqueen.pls"},
	{"Eska Olsztyn","http://acdn.smcloud.net/t060-1_mp3.pls"},
	{"Polska Stacja Disco Polo","http://www.polskastacja.pl/play/discopolohq.pls"}
};


#define portfel_prefix "P4S"

enum _API_sms
{
	Netto, 
	Numer, 
	Doladowanie, 
	Brutto[10],
	Tesc[9]
};
/*

new API_sms[][_API_sms] = {
	{ 1, 7143, 1, {"1,23"}}, 
	{ 2, 72550, 2, {"2,46"}}, 
	{ 3, 73550, 4, {"3,69"}}, 
	{ 4, 74550, 5, {"4,92"}}, 
	{ 5, 75550, 6, {"6,15"}}, 
	{ 6, 76550, 8, {"7,38"}}, 
	{ 9, 79550, 14, {"11,07"}}, 
	{ 19, 91909, 30, {"23,37"}}, 
	{ 25, 92505, 40, {"30,35"}}
};
*/
/*
enum _API_sms
{
	Netto, 
	Numer, 
	Doladowanie, 
	Brutto[10]
};
 
	
#define portfel_tresc "HPAY.BH"
new API_sms[][_API_sms] = {
	{ 1, 7155, 1, {"1.23"}}, 
	{ 2, 7255, 2, {"2.46"}}, 
	{ 3, 7355, 4, {"3.69"}}, 
	{ 5, 7555, 6, {"6.15"}}, 	
	{ 6, 76660, 8, {"7.38"}}, 
	{ 9, 7955, 12, {"11.07"}}, 
	{ 19, 91955, 28, {"23.37"}}, 
	{ 25, 92520, 40, {"30.75"}}
};*/

//#define portfel_tresc "AA.SP"
//SMS Netto,Numer,do³adowanie,koszt smsa,treœæ
new API_sms[][_API_sms] = {
	{ 1, 7143, 1, {"1,23"},{"SH1.P4S"}}, 
	{ 2, 72550, 2, {"2,46"},{"SH2.P4S"}}, 
	{ 3, 73550, 4, {"3,69"},{"SH3.P4S"}}, 
	{ 4, 74550, 5, {"4,92"},{"SH4.P4S"}}, 
	{ 5, 75550, 6, {"6,15"},{"SH5.P4S"}}, 
	{ 6, 76550, 8, {"7,38"},{"SH6.P4S"}}, 
	{ 9, 79550, 12, {"11,07"},{"SH9.P4S"}}, 
	{ 19, 91909, 28, {"23,37"},{"SH19.P4S"}}, 
	{ 25, 92505, 40, {"30,75"},{"SH25.P4S"}}
};
	/*Treœæ: Numer: Koszt:
SH1.P4S 7143 1z³ (1,23z³ z VAT)
SH2.P4S 72550 2z³ (2,46z³ z VAT)
SH3.P4S 73550 3z³ (3,69z³ z VAT)
SH4.P4S 74550 4z³ (4,92z³ z VAT)
SH5.P4S 75550 5z³ (6,15z³ z VAT)
SH6.P4S 76550 6z³ (7,38z³ z VAT)
SH9.P4S 79550 9z³ (11,07z³ z VAT)
SH19.P4S 91909 19z³ (23,37z³ z VAT)
SH25.P4S 92505 25z³ (30,75z³ z VAT)
*/
new API_erros[][]={
	{"Nieznany b³¹d - napisz na helpdesk.4fun-serv.pl kod b³êdu #01"},
	{"nieprawid³owy klucz API"},
	{"nieprawid³owa kwota netto SMS'a"},
	{"nieprawid³owy kod do³adowuj¹cy (nie podano lub z³a iloœæ znaków)"},
	{"nieprawid³owy opis (maksymalnie 20 znaków)"},
	{"b³¹d wewnêtrzny, problem zg³oœ do BOKu"},
	{"z³y kod do³adowuj¹cy (wykorzystany lub nieprawid³owy)	"}
};


enum scx
{
	sc,
	zl
};
new protfel_sc[][scx] = {
	{200, 1},
	{500, 6},
	{3000, 12},
	{6000, 21},
	{8000, 25},
	{9000, 30}
	
};
enum scxv
{
	dni,
	zl
};
new protfel_vip[][scxv] = {
	{7, 3},
	{14, 5},
	{30, 8},
	{45, 12},
	{60, 15},
	{90, 20}
	
};
new vote_string[150], bool:vote_trwa, bool:vote_kick, vote_kickid, glosy[2], bool:vote_oddal_glos[MAX_PLAYERS];
//new Text3D:LabelTancerki[MAX_PLAYERS];
enum enum_gmdata
{
	opt_event,
	last_vehicle,
	server_tag[6],
	server_www[32],
	mysql_host[32],
	mysql_user[32],
	mysql_db[32],
	mysql_pass[64],
	pass_admin[64],
	mod_pass[64],
	gmText[46],
	gm_skins[333],
	Float:gmFloat[3],
	gm_skinscount,
	max_ping,
	opt_gamestart,
	Float:opt_gamematematyk,
	Float:opt_gamecodes,
	Float:opt_gamescrable,
	Float:notfloat,
	Float:topGlitch,
	bool:timer_message,
	bool:antiMacro,
	timer_ann,
		timer_ann2,
	timer_evann,
	timer_vip_ann,
	timer_hideann,
	server_record, 
	server_dayrecord, 
	server_registered,
	server_kicks,
	server_banscz,
	server_bansp,
	gm_port,
	server_largest_drift,
	server_hostname,
	server_gunday,
	bool:animatelogo_running,
	animatelogo_step,
	bool:server_infolevel,
	
	vehicles_respawn,
	server_arenaplayers[32],
	bool:anty_autocbug,
	//Text3D:player_label[MAX_PLAYERS],
	Text3D:player_vehicle[MAX_PLAYERS],
	player_vehicleid[MAX_PLAYERS],
	player_object[MAX_PLAYERS],
	player_objectToPlayer[MAX_PLAYERS],
	
	npc_bus[4],
	Text3D:one_de,
	impreza_zone,
	impreza_sound[255],
	last_vote_kick,
	bool:gm_running
};
new gmData[enum_gmdata];
new player_vehicle_object[MAX_PLAYERS][MAX_PLAYER_VEHICLE_OBJECT];
new server_name[4][72];

enum hide_huds
{
	hud_all = 0,
	hud_pasek,
	hud_licznik, 
	hud_ann,
	hud_fps,
	hud_gangmembers,
	hud_events,
	hud_onlinecount,
	xxxxxxxxxx
}
enum enum_pInfo
{
	player_id,
	player_name[25],
	player_showname[128],
	player_password[44],
	player_apassword[44],
	player_loginpass[120],
	player_chpassword,
	player_email[44],
	player_ucode[44],
	player_serial[45],
	bool:player_weapons[50],
	player_ip[32],
	Float:player_save_pos[3],
	Float:player_bombpos[3],
	player_score,
	player_mailstatus,
	player_dialog_data[MAX_DIALOG_DATA],
	player_dialog_data_ex[62],
	player_lastlogin[24],
	player_lastip[24],
	player_cash, 
	setrangerang[12],
	player_state,
 	player_portfel,
	bool:player_sparmember,
	bool:player_sparmember2,
	bool:player_teleports,
	bool:player_pm,
	bool:player_nopduel,
	bool:player_register,
	bool:player_logged,
	bool:player_fps,
	bool:player_class,
	bool:player_tag,
	bool:player_hidehud[hide_huds],
	bool:player_ac,
	bool:player_sync,
	bool:player_toev,
	bool:player_evbl,
	bool:player_zw,
	bool:player_sparmembers,
	bool:player_kickOnlySobeit,
	player_zonearea,
	Float:player_gamematematyk,
	Float:player_gamecodes,
	Float:player_gamescrable,
	Float:player_spardmg, 
	player_objected,
	player_sqlonline,
	player_onupdate,
	//player_dblastwarn,
	player_sparkill,
	player_bounty,
	player_lastfps,
	player_lastfpsupdate,
	player_1spawn,
	player_spawned,
	player_level,
//	player_lastshoot,
	player_autocBug,
	bool:player_autocBugWarned,
	player_next_level, 
	player_vip,
	player_login_attempts,
	player_messages,
	player_warns,
	player_targetplayer,
	player_warns_censored,
	player_selectobject,
	player_acolor,
	player_blockcmd,
	player_spawnkill,
	player_spec,
	player_userank,
	player_bank,
	player_bomb,
	player_skin,
	player_lastKeyFire,
	player_loadskin,
	player_connected,
	player_timeplay,
	player_jail,
	player_carge,
	player_carge_object,
	player_arena,
	player_mute,
	player_afk,
	player_admin,
	player_adminblock,
	player_glitchTest,
	Float:player_glitchCount[4],
	bool:player_glitchDisply,
	player_glitchSaved,
	player_admin_login,
	player_kills,
	player_deaths,
	player_suicide,
	player_vehicle,
	player_tp_to,
	player_loteria,
	player_lastshowreport,
	player_reportID[50],
	player_last_damage,
	player_businessprice,
	player_lastkillerid,
	player_skill,
	player_killstreak,
	player_chatspam,
	player_lot,
	player_cmdspam,
	player_savestats,
	player_awarn,
	player_bomb_object,
	player_score_drawhide,
	player_achievements[MAX_ACHIEVEMENT],
	player_achievements_count,
	player_achievements_page,
	player_sobeitStep,
	player_unfreeze,
	player_nichchange,
	player_color,
	player_clickedplayer,
	player_dbwarn,
	player_balontime,
	player_mandats,
	player_mandatcash,
	player_inlabirynt,
	player_drawupdate,
	player_hourgame,
	player_deathcamera,
	player_deathobject,
	player_frpsset,
	player_classExplode,
	player_usevehicle,
	player_lastvehicle,
	player_launcher, 
	//
	//player_labeltime,
	//player_labelstr[20],
	//player_labelt[64],
	//ping
	player_pingupdate,
	player_averageping, 
	player_pingsum,
	player_pingcheck,
	player_pingwarnings,
	player_tirfrom,
	player_tir_warntime,
	Text3D:player_tir3dt,
	player_tirminssion,
	Float:player_tirkm,
	Float:player_stats_tirkm,
	player_tirid[2],
	bool:player_ban,
	//duel
	player_duel_toplayer,
	player_duel_weapon[2],
	player_duel_vw,
	player_duel_arena,
	player_camera,
	player_duel_timer,
	player_cbchannel,
	bool:player_duel,
	//ramp
	bool:player_rampcreated,
	player_ramp_pers,
	player_ramp,
	player_ramp_timer,
	//fishing
	player_fishing,
	player_last_fishing,
	//houses
	player_house,
	player_thouse,
	player_action_houseid,
	player_lasthouse_dialogshow,
	bool:player_ishouse,
	bool:vip_dot,
	//houses
	//gangs
	player_gangID,
	player_gang,
	player_gangrank,
	bool:player_isGang,
	player_gang_createopcion,
	player_gang_createname[42],
	player_gangWarTeam,
	//gang
	//vehicles
 	player_car_color[2],
	bool:player_car_have,
	player_car_lastload,
	player_car_extension_days,
	player_car_model,
	player_car_paintjob,
	player_car_date,
	player_car_modelbuy,
	player_car_licznik,
	player_hidespartd,
	player_class_skin[3],
	Float:player_car_przebieg,
	Float:player_car_pos[4],
	player_car_component[36],
	//drift
	Float:player_drift_pos[3],
	Float:player_driftpos[3],
	Float:player_lastpos[3],
	bool:player_driftcouter,
	player_drift_step,
	player_drift_timer,
	player_drift_newpoints,
	player_drifttd[62],
	player_largest_drift,
	//Audio
	player_stacja, 
	player_sound,
	player_impreza,
	bool:player_dj,
	bool:player_pause,
	//ZoneNoDM
	bool:player_no_dm,
	player_nodm_shoottime,
	player_warn_no_dm,
	//cargod
	bool:player_car_god,
	player_cheats,	
	//anty 
	anty_fakekill_warn,
	anty_fastkill_warn,
	anty_fakekill_lasttc,
	player_aimwarn,
	player_lastshottime,
	player_ac_nopspawn,
	player_loggaingcrash[4],
	
	player_actionplayer,
	player_textdrawcolor[PlayerText:MAX_PLAYER_TEXT_DRAWS],
	player_textdrawboxcolor[PlayerText:MAX_PLAYER_TEXT_DRAWS],
	player_textdrawbgcolor[PlayerText:MAX_PLAYER_TEXT_DRAWS],
	player_eventpoints[31],
	//PlayerText:player_TdNT,
	PlayerText:player_TdAnn2,
	PlayerText:player_TdStats[6],
	PlayerText:player_TdAnn[2],
 	PlayerText:player_TextureVeh,
	//PlayerText:player_TextureSkin,
	PlayerText:player_TdLicznik[4],
	PlayerText:player_tdEvent[2],
	PlayerText:player_achievement,
	player_TdHidden[PlayerText:257],
	bool:player_turbo,
	wybrany_spawn,
	player_nasionka,
	player_marihuana,
	posadzonych_krzakow,
	zebranych_krzakow,
	spalonego_skuna,
	cut_tree,
	bool:gavedmg,
	fpswkickerwarn,
	player_ks
}
new pInfo[MAX_PLAYERS][enum_pInfo];
new Text:Logo_P4S[7];
new Text:AdminTDInfo;
new string2[1024];
new Text:OnlineBelt;
new VehicleNeon[MAX_VEHICLES][2];
new TuneObjekty[MAX_VEHICLES][2];
new PickupDyskoteka[6];
new MuzaNaDysce;

new VehicleNames[212][32] = {
   "/Landstalker", 
   "/Bravura", 
   "/Buffalo", 
   "/Linerunner", 
   "/Pereniel", 
   "/Sentinel", 
   "/Dumper", 
   "/Firetruck", 
   "/Trashmaster", 
   "/Stretch", 
   "/Manana", 
   "/Infernus", 
   "/Voodoo", 
   "/Pony", 
   "/Mule", 
   "/Cheetah", 
   "/Ambulance", 
   "/Leviathan", 
   "/Moonbeam", 
   "/Esperanto", 
   "/Taxi", 
   "/Washington", 
   "/Bobcat", 
   "/Mr Whoopee", 
   "/BF Injection", 
   "/Hunter", 
   "/Premier", 
   "/Enforcer", 
   "/Securicar", 
   "/Banshee", 
   "/Predator", 
   "/Bus", 
   "/Rhino", 
   "/Barracks", 
   "/Hotknife", 
   "/Trailer", 
   "/Previon", 
   "/Coach", 
   "/Cabbie", 
   "/Stallion", 
   "/Rumpo", 
   "/RC Bandit", 
   "/Romero", 
   "/Packer", 
   "/Monster", 
   "/Admiral", 
   "/Squalo", 
   "/Seasparrow", 
   "/Pizzaboy", 
   "/Tram", 
   "/Trailer", 
   "/Turismo", 
   "/Speeder", 
   "/Reefer", 
   "/Tropic", 
   "/Flatbed", 
   "/Yankee", 
   "/Caddy", 
   "/Solair", 
   "/Berkley's RC Van", 
   "/Skimmer", 
   "/PCJ-600", 
   "/Faggio", 
   "/Freeway", 
   "/RC Baron", 
   "/RC Raider", 
   "/Glendale", 
   "/Oceanic", 
   "/Sanchez", 
   "/Sparrow", 
   "/Patriot", 
   "/Quad", 
   "/Coastguard", 
   "/Dinghy", 
   "/Hermes", 
   "/Sabre", 
   "/Rustler", 
   "/ZR 350", 
   "/Walton", 
   "/Regina", 
   "/Comet", 
   "/BMX", 
   "/Burrito", 
   "/Camper", 
   "/Marquis", 
   "/Baggage", 
   "/Dozer", 
   "/Maverick", 
   "/News Chopper", 
   "/Rancher", 
   "/FBI Rancher", 
   "/Virgo", 
   "/Greenwood", 
   "/Jetmax", 
   "/Hotring", 
   "/Sandking", 
   "/Blista Compact", 
   "/Police Maverick", 
   "/Boxville", 
   "/Benson", 
   "/Mesa", 
   "/RC Goblin", 
   "/Hotring Racer", 
   "/Hotring Racer", 
   "/Bloodring Banger", 
   "/Rancher", 
   "/Super GT", 
   "/Elegant", 
   "/Journey", 
   "/Bike", 
   "/Mountain Bike", 
   "/Beagle", 
   "/Cropdust", 
   "/Stunt", 
   "/Tanker", 
   "/RoadTrain", 
   "/Nebula", 
   "/Majestic", 
   "/Buccaneer", 
   "/Shamal", 
   "/Hydra", 
   "/FCR", 
   "/NRG", 
   "/HPV1000", 
   "/Cement Truck", 
   "/Tow Truck", 
   "/Fortune", 
   "/Cadrona", 
   "/FBI Truck", 
   "/Willard", 
   "/Forklift", 
   "/Tractor", 
   "/Combine", 
   "/Feltzer", 
   "/Remington", 
   "/Slamvan", 
   "/Blade", 
   "/Freight", 
   "/Streak", 
   "/Vortex", 
   "/Vincent", 
   "/Bullet", 
   "/Clover", 
   "/Sadler", 
   "/Firetruck", 
   "/Hustler", 
   "/Intruder", 
   "/Primo", 
   "/Cargobob", 
   "/Tampa", 
   "/Sunrise", 
   "/Merit", 
   "/Utility", 
   "/Nevada", 
   "/Yosemite", 
   "/Windsor", 
   "/Monster", 
   "/Monster", 
   "/Uranus", 
   "/Jester", 
   "/Sultan", 
   "/Stratum", 
   "/Elegy", 
   "/Raindance", 
   "/RC Tiger", 
   "/Flash", 
   "/Tahoma", 
   "/Savanna", 
   "/Bandito", 
   "/Freight", 
   "/Trailer", 
   "/Kart", 
   "/Mower", 
   "/Duneride", 
   "/Sweeper", 
   "/Broadway", 
   "/Tornado", 
   "/AT-400", 
   "/DFT-30", 
   "/Huntley", 
   "/Stafford", 
   "/BF-400", 
   "/Newsvan", 
   "/Tug", 
   "/Trailer", 
   "/Emperor", 
   "/Wayfarer", 
   "/Euros", 
   "/Hotdog", 
   "/Club", 
   "/Trailer", 
   "/Trailer", 
   "/Andromada", 
   "/Dodo", 
   "/RC Cam", 
   "/Launch", 
   "/Police Car (LSPD)", 
   "/Police Car (SFPD)", 
   "/Police Car (LVPD)", 
   "/Police Ranger", 
   "/Picador", 
   "/S.W.A.T. Van", 
   "/Alpha", 
   "/Phoenix", 
   "/Glendale", 
   "/Sadler", 
   "/Luggage Trailer", 
   "/Luggage Trailer", 
   "/Stair Trailer", 
   "/Boxville", 
   "/Farm Plow", 
   "/Utility Trailer"
};

new gweaponName[][22]={
	"Piêœci",	// 0
	"Kastet",
	"Kij golfowy",
	"Pa³ka policyjna",
	"Nó¿",		// 4
	"Kij baseballowy",
	"£opata",
	"Kij bilardowy",
	"Katana",
	"Pi³a mechaniczna",
	"Fioletowe dildo",
	"Bia³e dildo",
	"D³ugie bia³e dildo",
	"Bia³e dildo",
	"Kwiaty",
	"Laska",	// 15
	"Granaty",
	"Gas ³zawi¹cy",
	"Koktail molotova",
	"none",
	"none",
	"none",
	"Pistolet 9mm",
	"Pistolet z t³umikiem",
	"Desert Eagle",
	"Shotgun",
	"Sawn-off Shotgun",
	"Combat Shotgun",
	"Micro Uzi",
	"MP5",
	"AK-47",
	"M4",
	"Tec9",
	"Strzelba",
	"Sniper Rifle",
	"RPG",
	"Wyrzutnia rakiet",
	"Miotacz ognia",
	"Minigun",
	"£adunki wybuchowe",
	"Detonator",
	"Spray",
	"Gaœnica",
	"Aparat",
	"Gogle noktowizyjne",
	"Gogle termiczne",
	"Spadochron"
};


#define MAX_RAPORTOW 50

enum reportData
{
	rZglaszajacy,
	rZgloszony,
	rReason[60],
	rSprawdza,
	bool:rMessage,
	bool:rUsed
};
new rData[MAX_RAPORTOW][reportData];
//
new Float:SavePos[3];

//Zone NO DM!
#define MAX_ZONE 30

enum _zone
{
	zone_id, 
	Float:min_x, 
	Float:min_y, 
	Float:max_x, 
	Float:max_y
}
enum _zone_create
{
	Float:zone_minx, 
	Float:zone_miny, 
	Float:zone_maxx, 
	Float:zone_maxy, 
	zone_step,
	zone_gid
}
new zone[MAX_ZONE][_zone], 
	zone_created[MAX_ZONE], 
	zone_create[_zone_create],
	zone_count=1
;
//gangs

#define MAX_GANG2 55
#define MAX_GANGS 50
#define MAX_GANGS_CREATE 45
#define MAX_GANGS_ZONES 100

#define gRank_user 1
#define gRank_vice 2
#define gRank_szef 3

#define MAX_SPAR_ARENS 80
enum spar_AAD
{
	Float:aad_spawn1[3],
	Float:aad_spawn2[3],
	Float:aad_zone[4],
	add_interior,
	add_zone,
	add_stream,
	add_name[32]
}
new add_Spar[MAX_SPAR_ARENS][spar_AAD];
new add_SparCount;

enum gangEnum_
{
	gangid, 
	gangNazwa[50], 
	gangWww[30], 
	gangColor, 
	gangTag[20], 
	gangDateCreated[34],
	Float:gangSpawn[3], 
	gangPoints, 
	gangCv, 
	gangPojazd, 
	gangSkin, 
	//gangWojnaArena,
	gangWojnaPlayers,
	gangWojnaMaxPlayers,
	bool:active, 
	gangSlots,
	gangUsers,
	gangWojnaZapro, 
	gangWojnaVV,
	gangSaveTime,
	gangWojnaZaproTime, 
	bool:gangWojnaTrwa, 
	bool:gangWojnaStarted,
	gangWojnaArena,
	gangWojnaKill,
	gangWojnaPoint,
	Text:gangTextdraw,
	gangBaza_Cmd[16],
	Float:gangBaza_Open[6],
	Float:gangBaza_Close[6],
	gangBaza_Model,
	bool:gangBaza_Status,
	gangBaza_ID
	
};

enum zonegangEnum_
{
	zonegangid, 
	zone_id,
	Float:zonegangSpawn[4],
	zonestream,
	zonegz,
	zonecolor
};
/*
enum gState_Enum
{
	g1,
	g2,
	type
};
*/
new gInfo[MAX_GANG2][gangEnum_],
	gZone[MAX_GANGS_ZONES][zonegangEnum_],
	//gState[MAX_GANG2][MAX_GANG2][gState_Enum];
	Iterator:Gangs<MAX_GANG2 + 5>,
	Iterator:GangsZones<MAX_GANGS_ZONES + 5>,
	gangPodania[MAX_PLAYERS][MAX_GANG2],
	loaded_gang_glob;

new VehicleColoursTableRGBA[256] = {
// SA-MP extended colours (0.3x)
	0x177517FF, 0x210606FF, 0x125478FF, 0x452A0DFF, 0x571E1EFF, 0x010701FF, 0x25225AFF, 0x2C89AAFF, 0x8A4DBDFF, 0x35963AFF,
	0xB7B7B7FF, 0x464C8DFF, 0x84888CFF, 0x817867FF, 0x817A26FF, 0x6A506FFF, 0x583E6FFF, 0x8CB972FF, 0x824F78FF, 0x6D276AFF,
	0x1E1D13FF, 0x1E1306FF, 0x1F2518FF, 0x2C4531FF, 0x1E4C99FF, 0x2E5F43FF, 0x1E9948FF, 0x1E9999FF, 0x999976FF, 0x7C8499FF,
	0x992E1EFF, 0x2C1E08FF, 0x142407FF, 0x993E4DFF, 0x1E4C99FF, 0x198181FF, 0x1A292AFF, 0x16616FFF, 0x1B6687FF, 0x6C3F99FF,
	0x481A0EFF, 0x7A7399FF, 0x746D99FF, 0x53387EFF, 0x222407FF, 0x3E190CFF, 0x46210EFF, 0x991E1EFF, 0x8D4C8DFF, 0x805B80FF,
	0x7B3E7EFF, 0x3C1737FF, 0x733517FF, 0x781818FF, 0x83341AFF, 0x8E2F1CFF, 0x7E3E53FF, 0x7C6D7CFF, 0x020C02FF, 0x072407FF,
	0x163012FF, 0x16301BFF, 0x642B4FFF, 0x368452FF, 0x999590FF, 0x818D96FF, 0x99991EFF, 0x7F994CFF, 0x839292FF, 0x788222FF,
	0x2B3C99FF, 0x3A3A0BFF, 0x8A794EFF, 0x0E1F49FF, 0x15371CFF, 0x15273AFF, 0x375775FF, 0x060820FF, 0x071326FF, 0x20394BFF,
	0x2C5089FF, 0x15426CFF, 0x103250FF, 0x241663FF, 0x692015FF, 0x8C8D94FF, 0x516013FF, 0x090F02FF, 0x8C573AFF, 0x52888EFF,
	0x995C52FF, 0x99581EFF, 0x993A63FF, 0x998F4EFF, 0x99311EFF, 0x0D1842FF, 0x521E1EFF, 0x42420DFF, 0x4C991EFF, 0x082A1DFF,
	0x96821DFF, 0x197F19FF, 0x3B141FFF, 0x745217FF, 0x893F8DFF, 0x7E1A6CFF, 0x0B370BFF, 0x27450DFF, 0x071F24FF, 0x784573FF,
	0x8A653AFF, 0x732617FF, 0x319490FF, 0x56941DFF, 0x59163DFF, 0x1B8A2FFF, 0x38160BFF, 0x041804FF, 0x355D8EFF, 0x2E3F5BFF,
	0x561A28FF, 0x4E0E27FF, 0x706C67FF, 0x3B3E42FF, 0x2E2D33FF, 0x7B7E7DFF, 0x4A4442FF, 0x28344EFF
};
new GangColors[202] = {
	0xFF8C13FF, 0xC715FFFF, 0x20B2AAFF, 0xDC143CFF, 0x6495EDFF, 0x80cc00ff, 0x778899FF, 0xFF1493FF, 0xF4A460FF, 
	0xEE82EEFF, 0xFFD720FF, 0x8b4513FF, 0x4949A0FF, 0x148b8bFF, 0x14ff7fFF, 0x556b2fFF, 0x0FD9FAFF, 0x10DC29FF, 
	0x534081FF, 0x0495CDFF, 0xEF6CE8FF, 0xBD34DAFF, 0x247C1BFF, 0x0C8E5DFF, 0x635B03FF, 0xCB7ED3FF, 0x65ADEBFF, 
	0x5C1ACCFF, 0xF2F853FF, 0x11F891FF, 0x7B39AAFF, 0x53EB10FF, 0x54137DFF, 0x275222FF, 0xF09F5BFF, 0x3D0A4FFF, 
	0x22F767FF, 0xD63034FF, 0x9A6980FF, 0xDFB935FF, 0x3793FAFF, 0x90239DFF, 0xE9AB2FFF, 0xAF2FF3FF, 0x057F94FF, 
	0xB98519FF, 0x388EEAFF, 0x028151FF, 0xA55043FF, 0x0DE018FF, 0x93AB1CFF, 0x95BAF0FF, 0x369976FF, 0x18F71FFF, 
	0x4B8987FF, 0x491B9EFF, 0x829DC7FF, 0xBCE635FF, 0xCEA6DFFF, 0x20D4ADFF, 0x2D74FDFF, 0x3C1C0DFF, 0x12D6D4FF, 
	0x48C000FF, 0x2A51E2FF, 0xE3AC12FF, 0xFC42A8FF, 0x2FC827FF, 0x1A30BFFF, 0xB740C2FF, 0x42ACF5FF, 0x2FD9DEFF, 
	0xFAFB71FF, 0x05D1CDFF, 0xC471BDFF, 0x94436EFF, 0xC1F7ECFF, 0xCE79EEFF, 0xBD1EF2FF, 0x93B7E4FF, 0x3214AAFF, 
	0x184D3BFF, 0xAE4B99FF, 0x7E49D7FF, 0x4C436EFF, 0xFA24CCFF, 0xCE76BEFF, 0xA04E0AFF, 0x9F945CFF, 0xDCDE3DFF, 
	0x10C9C5FF, 0x70524DFF, 0x0BE472FF, 0x8A2CD7FF, 0x6152C2FF, 0xCF72A9FF, 0xE59338FF, 0xEEDC2DFF, 0xD8C762FF, 
	0xD8C762FF, 0xFF8C13FF, 0xC715FFFF, 0x20B2AAFF, 0xDC143CFF, 0x6495EDFF, 0xf0e68cFF, 0x778899FF, 0xFF1493FF, 
	0xF4A460FF, 0xEE82EEFF, 0xFFD720FF, 0x8b4513FF, 0x4949A0FF, 0x148b8bFF, 0x14ff7fFF, 0x556b2fFF, 0x0FD9FAFF, 
	0x10DC29FF, 0x534081FF, 0x0495CDFF, 0xEF6CE8FF, 0xBD34DAFF, 0x247C1BFF, 0x0C8E5DFF, 0x635B03FF, 0xCB7ED3FF, 
	0x65ADEBFF, 0x5C1ACCFF, 0xF2F853FF, 0x11F891FF, 0x7B39AAFF, 0x53EB10FF, 0x54137DFF, 0x275222FF, 0xF09F5BFF, 
	0x3D0A4FFF, 0x22F767FF, 0xD63034FF, 0x9A6980FF, 0xDFB935FF, 0x3793FAFF, 0x90239DFF, 0xE9AB2FFF, 0xAF2FF3FF, 
	0x057F94FF, 0xB98519FF, 0x388EEAFF, 0x028151FF, 0xA55043FF, 0x0DE018FF, 0x93AB1CFF, 0x95BAF0FF, 0x369976FF, 
	0x18F71FFF, 0x4B8987FF, 0x491B9EFF, 0x829DC7FF, 0xBCE635FF, 0xCEA6DFFF, 0x20D4ADFF, 0x2D74FDFF, 0x3C1C0DFF, 
	0x12D6D4FF, 0x48C000FF, 0x2A51E2FF, 0xE3AC12FF, 0xFC42A8FF, 0x2FC827FF, 0x1A30BFFF, 0xB740C2FF, 0x42ACF5FF, 
	0x2FD9DEFF, 0xFAFB71FF, 0x05D1CDFF, 0xC471BDFF, 0x94436EFF, 0xC1F7ECFF, 0xCE79EEFF, 0xBD1EF2FF, 0x93B7E4FF, 
	0x3214AAFF, 0x184D3BFF, 0xAE4B99FF, 0x7E49D7FF, 0x4C436EFF, 0xFA24CCFF, 0xCE76BEFF, 0xA04E0AFF, 0x9F945CFF, 
	0xDCDE3DFF, 0x10C9C5FF, 0x70524DFF, 0x0BE472FF, 0x8A2CD7FF, 0x6152C2FF, 0xCF72A9FF, 0xE59338FF, 0xEEDC2DFF, 
	0xD8C762FF, 0xD8C762FF, 0xFFFFFFFF,0xFFFFFFFF
};

//data eventow
#define stats_wg 0
#define stats_ch 1
#define stats_hy 2
#define stats_ws 3
#define stats_dd 4
#define stats_ctf 5
#define stats_onede 6
#define stats_sawn 7
#define stats_minigun 8
#define stats_snajper 9
#define stats_matematyk 10
#define stats_codes 11
#define stats_scrable 12
#define stats_duel_win 13
#define stats_duel_lost 14
#define stats_tir 15
#define stats_zb 16
#define stats_tr 17
#define stats_walizki 18
#define stats_prezenty 19
#define stats_figurki 20
#define stats_zauta 21
#define stats_arenagang 22
#define stats_df 23
#define stats_os 24
#define stats_dm1 25
#define stats_dm2 26
#define stats_dm3 27
#define stats_onede2 28
#define stats_skupcount 29

new CategoryAirplanes[] = {60, 111, 112, 113, 119, 153, 177, 192, 193};
new CategoryHelis[] = {17, 87, 88, 97, 148, 163};
new CategoryMotorsAndBikes[] = {48, 61, 62, 63, 68, 71, 81, 109, 110, 121, 122, 123, 181, 186};
new CategoryCabriolets[] = {39, 80, 133, 155};
new CategoryIndustrials[] = {22, 82, 98, 99, 209, 124, 178, 55, 3, 14, 182, 43, 114, 200, 13, 115, 40, 143, 205, 59, 131, 8, 152, 78, 56, 154};
new CategoryLowriders[] = {12, 134, 135, 136, 166, 167, 175, 176};
new CategoryOffroad[] = {0, 24, 44, 70, 89, 95, 100, 105, 156, 157, 168, 173, 179};
new CategoryPublic[] = {7, 16, 20, 27, 31, 33, 37, 38, 90, 128, 144, 196, 197, 198, 199, 201};
new CategorySaloon[] = {45, 104, 1, 118, 127, 142, 107, 162, 185, 19, 126, 204, 66, 92, 74, 146, 117, 10, 151, 116, 67, 26, 36, 147, 5, 180, 160, 150, 189, 140, 91, 129, 21};
new CategorySport[] = {2, 11, 15, 29, 51, 75, 77, 94, 96, 102, 103, 106, 141, 158, 159, 165, 187, 189, 202, 203};
new CategoryBoats[] = {30, 46, 52, 53, 54, 72, 73, 84, 93, 195};
new CategoryUnicals[] = {85, 57, 83, 108, 132, 86, 6, 130, 34, 145, 188, 171, 172, 23, 42, 28, 9, 174, 125, 183, 139};

enum AttachmentEnum
{
	attachmodel,
	attachname[24]
}

new AttachmentObjects[][AttachmentEnum] = {
	{18632, "Wêtkarz"},
	{18633, "Klucz"},
	{18635, "M³otek"},
	{18636, "Che³n"},
	{18640, "W³osy"},
	{18641, "Flesh 1"},
	{18643, "Laser 1"},
	{19080, "Laser 2"},
	{18644, "Œrubokrêt1"},
	{18645, "Kask 1"},
	{18865, "Telefon 1"},
	{18866, "Telefon 2"},
	{18890, "Grabie1"},
	{18891, "Chustka1"},
	{18911, "Maska1"},
	{18920, "Maska10"},
	{18921, "Beret 1"},
	{18922, "Beret 2"},
	{18926, "Kapelusz "},
	{18936, "Kask 1"},
	{18952, "Boxeski kask"},
	{18953, "Czapka z dzianiny1"},
	{18955, "Czapka Nad Okiem "},
	{18967, "Mêski kapelusz1"},
	{18970, "Kapelusz"},
	{18974, "Maskaa Zorro1"},
	{19006, "Okulary Typ 1"},
	{19095, "Kowbojski kapelusz 1"},
	{19099, "Czapka policyjna 2"},
	{19100, "Czapka policyjna 3"},
	{19101, "Wojskowy he³m 1"},
	{19102, "Wojskowy he³m 2"}
};

enum AttachmentVehEnum
{
	vattachmodel,
	vattachname[46]
}
new AttachmentVehObjects[][AttachmentVehEnum] = {
	
	{902, "rozgwiazda"},
	{953, "ostryga"},
	{1599, "ryba"},
	{1600, "ryba"},
	{1604, "ryba"},
	{954, "podkowa"},
	{1248, "znak GTA3"},
	{1254, "czaszka"},
	{1644, "ketchup"},
	{14673, "dildo"},
	{2709, "s³oik"},
	{3525, "pochodnia"},
	{19317, "gitara1"},
	{19318, "gitara2"},
	{19319, "gitara3"},
	{19308, "¿ó³ta tabliczka TAXI"},
	{19309, "czarno-bia³a tabliczka TAXI"},
	{19310, "bia³a tabliczka TAXI"},
	{19311, "czarno-¿ó³ta tabliczka TAXI"},
	{19320, "dynia"},
	{19346, "du¿y hot-dog"},
	{19347, "gwiazda"},
	{19419, "w³¹czona syrena"},
	{19420, "wy³¹czona syrena"},
	{19470, "tabliczka For Sale"}
};

new AttachmentBones[][24] = {
	{"Krêgos³up"},
	{"G³owa"},
	{"Lewe ramiê"},
	{"Prawe ramiê"},
	{"Lewa rêka"},
	{"Prawa rêka"},
	{"Lewege udo"},
	{"Prawe udo"},
	{"Lewa stopa"},
	{"Prawa noga"},
	{"Prawa ³ydka"},
	{"Lewa ³ydka"},
	{"Lewe przedramienie"},
	{"Prawe przedramienie"},
	{"Lewy obojczyk"},
	{"Prawy obojczyk"},
	{"Szyja"},
	{"Szczêka"}
};
new m_engine, m_elights, m_alarm, m_doors, m_bonnet, m_boot, m_objective;

#define MAX_FISHINGS 10

enum Fishing_Enum
{
	Float:fishing_pos[3],
	bool:fishing_used
};
new fData[MAX_FISHINGS][Fishing_Enum], fCount;


enum Achventes_
{
	Nazwa[50], 
	Opis[150], 
	Score
}
new AchventesCount;
new Osiagniecia[MAX_ACHIEVEMENT][Achventes_];
/* = 
{
 	{"Witamy!", "Zarejestruj swoje  konto.", 1},
	{"Pierwsze zgniecie", "Zgiñ.", 1}, //1
	{"Hitman", "Zabij 25 razy gracza za \nktórego jest wystawiona nagroda respektu.", 25}, //2
	{"W³amywacz", "Sprobuj w³amaæ siê do czyjegoœ prywatnego pojazdu", 1}, //3
	{"Zawodowy kierowca", "Wykonaj misjê (/tr1) 50 razy z\ntras¹ d³u¿sz¹ ni¿ 23.9 km.", 50}, //4
	{"Wêdkarz", "Z³ów 100 razy rybê.", 100}, //5
	{"Kierowca", "Wsi¹dŸ do pojazdu", 1}, //6
	{"Sta³y Gracz", "Zaloguj siê codziennie przez 10 dni.", 10}, //7
	{""}
};
*/

new OPTResult[24];
new OPTCheck, OPTIDs[3];
new OPTWins[][] = {{"pierwszy"}, {"drugi"}, {"trzeci"}};

new Characters[][] =
{
	"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", 
	"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", 
	"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", 
	"n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", 
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
};

new PlaceChars[][] = 
{
	{"Robaczek"},
	{"Rodzina"},
	{"Sylwester"},
	{"Uzytkownik"},
	{"Zdjecia"},
	{"Wyznanie"},
	{"Anonim"},
	{"Sowa"},
	{"Cytryna"},
	{"Kamera"},
	{"Reklama"},
	{"Pomoc"},
	{"Burza"},
	{"Sklep"},
	{"Album"},
	{"Lipiec"},
	{"Czwartek"},
	{"Bydgoszcz"},
	{"Wroclaw"},
	{"Polska"},
	{"Tatry"},
	{"Ucho"},
	{"Usta"},
	{"Stopa"},
	{"Trampki"},
	{"Baton"},
	{"Aplikacja"},
	{"Jezioro"},
	{"Przeciwienstwo"},
	{"Samp"},
	{"Poeta"},
	{"Kolega"},
	{"Przyjaciel"},
	{"Czarny"},
	{"Slownik"},
	{"Golab"},
	{"Hustawka"},
	{"Gruszka"},
	{"Komentarz"},
	{"Komputer"},
	{"Hiszpania"},
	{"Film"},
	{"Czat"},
	{"Podworko"},
	{"Szachy"},
	{"Taczka"},
	{"Kura"},
	{"Woda"},
	{"Pirat"},
	{"Droga"},
	{"Statek"},
	{"Misiek"},
	{"Absolwent"},
	{"Terazniejszosc"},
	{"Laptop"},
	{"Koszulka"},
	{"Serce"},
	{"Kwiatki"},
	{"Folder"},
	{"Park"},
	{"Notatnik"},
	{"Dokument"},
	{"Grenlandia"},
	{"Portugalczyk"},
	{"Znieczulenie"},
	{"Lekarstwo"},
	{"Tabletka"},
	{"Plecak"},
	{"Dlugopis"},
	{"Lektura"},
	{"Palec"},
	{"Grzejnik"},
	{"Dach"},
	{"Komin"},
	{"Znak"},
	{"Wisnia"},
	{"Papuga"},
	{"Klatka"},
	{"Przecinek"},
	{"Kropka"},
	{"Przepis"},
	{"Italia"},
	{"Teletubisie"},
	{"Pszczelarz"},
	{"Ornitolog"},
	{"Stomatolog"},
	{"Onomatopeja"},
	{"Trylogia"},
	{"Blokada"},
	{"Rekwizyt"},
	{"Abstynent"},
	{"Rywalizacja"},
	{"Lekkoatletyka"},
	{"Majonez"},
	{"Gitara"},
	{"Frytki"},
	{"Widelec"},
	{"Szubienica"},
	{"Rosja"},
	{"Kolonia"},
	{"Ocean"},
	{"Ptaszek"},
	{"Stokrotka"},
	{"Bekon"},
	{"Gniazdko"},
	{"Microsoft"},
	{"Pokemon"},
	{"Kobieta"},
	{"Diagnostyka"},
	{"Edytor"},
	{"Kreator"},
	{"Rentgen"},
	{"Blondynka"},
	{"Pisarz"},
	{"Skrzypek"},
	{"Fontanna"},
	{"Rynek"},
	{"Hotel"},
	{"Miejscowosc"},
	{"Koper"},
	{"Reinkarnacja"},
	{"Realista"},
	{"Optymista"},
	{"Slonce"},
	{"Chinczyk"},
	{"Regulamin"},
	{"Druzyna"},
	{"Termometr"},
	{"Teleskop"},
	{"Termos"},
	{"Szminka"},
	{"Propozycja"},
	{"Globalizacja"},
	{"Marchewka"},
	{"Terytorium"},
	{"Wierzba"},
	{"Farmaceuta"},
	{"Lekarz"},
	{"Czopek"},
	{"Chleb"},
	{"Hybryda"},
	{"Pietnascie"},
	{"Autostrada"},
	{"Tapeta"},
	{"Robal"},
	{"Parkour"},
	{"Fujara"}
};

new censore_[][50] = 
{
        "chuj", 
        "cipa", "cip¹", "cipê", "cipie", "cipom", "cipy", "dojeb", "dopierdoli³am", "dopierdoli³aœ", "dopierdoli³by", "dopierdoli³bym", 
        "dupa", "dupach", "dupami", "dup¹", "dupê", "dupie", "dupom", "dupy", "fuck", "fucker", "jeba", 
        "kurestwa", "kurestwachchuj",  "dopierdoli³am", "dopierdoli³aœ", "dopierdoli³by", "dopierdoli³bym", "dopierdoli³byœ", "dopierdoli³em", 
		"dopierdoli³eœ", "zjeb", "kurwa", "idiota", "peda³"
};
new PlayerText:GangSparTd[9][MAX_PLAYERS];
new Text:PasekBelt[11],
	Text:LicznikBelt,
	Text:PlayerEventBox,
	Text:RespectAddBox,
	Text:EventTD0[2],
	Text:GangSparTd0[9],
 	Text:Panorama[6],
	Text:w_olg[3],
 	Text:recommend_box,
	Text:EventTD[2],
	Text:AnnDraw,
	Text:AnnDraw2,
	Text:AnnDraw3,
	Text:__walizka[2],
	Text:SpawnOchrona,
	Text:glosowanie[5], 
	Text:FlashTextdraw,
	Text:Areny,
	Text:ClassSkinInfo,
	PlayerText:SelectSkin_[10],
	PlayerText:playerdraw_respect, 
	PlayerText:GangZoneDraw,
	Text:StrefaBezDM;

#define _trr 2
#define t_r_start_players 3
#define t_r_start_players_max 30
#define t_r_vw 170

enum t_r_event 
{
	winreed, 
	trr[101], 
	bool:statees, 
	bool:started, 
	bool:iswin[MAX_PLAYERS],
	Timer, 
	b_object,
	tr_checkpoint,
	b_time,
	t_result[20],
	Bar:tr_bar,
	t_zadanie,
	t_zadanieid
	 
};
new script_tr[t_r_event];
new Iterator:t_r_players<MAX_PLAYERS+2>;



enum _pickup
{
	Nazwa[64],
	ID
}
new pickupTemp[][_pickup] = {
	 
	{"Spadochron", 371},
	{"Kamizelka", 1242},
	{"¯ycie", 1240}
};


#define MAX_Figure 600
enum FigureEnum
{
	Figureid, 
	Figureid_sql, 
	Text3D:Figureid_label, 
	Float:Figurex, 
	Float:Figurey, 
	Float:Figurez, 
}
new FigureInfo[MAX_Figure][FigureEnum], 
	FigureCount = 0
;


enum _create
{
	Float:x_,
	Float:y_,
	Float:z_,
	Float:tp_x,
	Float:tp_y,
	Float:tp_z,
	Float:tp_a,
	e_gang,
	e_int,
	description[64],
	step
}
new telepickup_create[MAX_PLAYERS][_create];


#define MAX_CATEGORIES 4
#define MAX_TOPLIST 25
enum e_top
{
	ename[64],
	esql[36]
}
new topInfo[MAX_CATEGORIES][MAX_TOPLIST][e_top],
	topCount[MAX_CATEGORIES];
	
#define MAX_RADAR 50
enum RadarEnum{
	RADid, 
	Float:RADx, 
	Float:RADy, 
	Float:RADz, 
	Float:RADrange, 
	RADlimit,
	RADStrefa
}
new RadarInfo[MAX_RADAR][RadarEnum], 
	RadarsCount;

new Float:LabyrinthFinish[][] = {
	{1136.3619,1284.9497,10.8203},
	{1142.8258,1283.1801,10.8203},
	{1153.0541,1281.0558,10.8203},
	{1159.0054,1275.1985,10.8203},
	{1166.7166,1269.5316,10.8203},
	{1173.2968,1267.5720,10.8203},
	{1174.1807,1275.7314,10.8203},
	{1155.6266,1256.1273,10.8203}
};

new Iterator:c_h_players<MAX_PLAYERS>;
new Iterator:d_f_players<MAX_PLAYERS+2>;

#define TIR_MAX_CP 3

#define TIR_CP_TIR 0
#define TIR_CP_WAN 1
#define TIR_CP_TIR2 2

#define TIR_CP_TIR_POS 991.1223, 2150.0063, 10.8203
#define TIR_CP_WAN_POS -536.4885,-501.8340,25.5178
#define TIR_CP_TIR2_POS 1637.3320,960.6310,10.7919
 
new Tir_CP[TIR_MAX_CP];


/*
	echo "1"
			else
				echo "0"
			fi
		else
			echo "0"
						
*/
enum enum_arenasolo {
	arr_nazwa[32],
	arr_uid,
	arr_interior,
	Float:arr_ar,
	Float:arr_spawn1[4],
	Float:arr_spawn2[4]
};
 
new ArenySolo_Data[][enum_arenasolo] =
{
	
	{ "WH", 2, 1, 99.0, 
		{ 1413.93, 3.22, 1000.92, 135.0 },
		{ 1372.25, -35.94, 1000.92, 315.0 } 
	},
	{ "Klatka", 3, 0, 99.0, 
		{ 139.1815, 1718.7133, 1509.8470, 358.6994 },
		{ 139.1072, 1757.3245, 1509.8470, 180.4111 } 
	}

};
 
enum enum_e1v1{
	bool:e1v1_trwa,
	bool:e1v1_started,
	e1v1_admin,
	e1v1_gun,
	e1v1_soloplayers[2]
}

new e1v1[enum_e1v1], Iterator:e1v1_players<MAX_PLAYERS>;

new Float:e1v1___pos__[][] = {
	{2439.6699,1024.8829,56.6029,268.8553}, // pos1
	{2439.6846,1025.6826,56.6029,268.8553}, // pos2
	{2439.6846,1026.4602,56.6029,268.8553}, // pos3
	{2439.6846,1027.3224,56.6029,268.8553}, // pos4
	{2439.6846,1028.1764,56.6029,268.8553} , // pos5
	{2439.6846,1029.0234,56.6029,268.8553}, // pos6
	{2439.6846,1029.8031,56.6029,268.8553}, // pos7
	{2439.6846,1030.5743,56.6029,268.8553}, // pos8
	{2439.6846,1031.3834,56.6029,268.8553}, // pos9
	{2439.6846,1032.1779,56.6029,268.8553}, // pos10
	{2439.6846,1032.9646,56.6029,268.8553}, // pos11
	{2439.6846,1033.9159,56.6029,268.8553}, // pos12
	{2439.6846,1034.6736,56.6029,268.8553}, // pos13
	{2439.6846,1035.3987,56.6029,268.8553}, // pos14
	{2439.6846,1036.1417,56.6029,268.8553}, // pos15
	{2439.6846,1036.9069,56.6029,268.8553}, // pos16
	{2439.6846,1037.6243,56.6029,268.8553}, // pos17
	{2439.6846,1038.2961,56.6029,268.8553}, // pos18
	{2439.6846,1039.0753,56.6029,268.8553}, // pos19
	{2439.6846,1039.8163,56.6029,268.8553} // pos20
};

new evPlayerSett[MAX_PLAYERS];
enum adminEvent{
	ev_name[64],
	bool:ev_on,
	bool:ev_started, 
	bool:ev_dropweapon,
	bool:ev_freezer,
	Float:ev_pos[3],
	ev_gun,
	ev_maxplayers, 
	ev_car,
	ev_internior,
	ev_lider
	
};
new aEData[adminEvent];
new Iterator:EventPlayers<MAX_PLAYERS>;

enum gangspar_rankingEnum {
    player_Score,
    player_ID
}

new update@warn[MAX_PLAYERS];

enum e_intro
{
	i_step,
	i_camerastep,
	i_airobj[3],
	bool:i_attachcamera
};
new Intro[MAX_PLAYERS][e_intro];


/*
stock Float:IntroPositions[4][6] = {
	{1867.0000, -1761.0000, 72.0000, 1500.0000, -1250.0000, 65.0000},		// Los Santos
	{-2233.0591, 997.9387, 140.0078, 2176.6233, 78.4012, 100.0078},			// San Fierro
	{1940.0631, 1629.4506, 150.2578, 2117.1104, 1683.2452, 13.0060},		// Las Venturas
	{1483.5476, -1218.5514, 73.7567, 1405.6055, -790.4913, 84.8043}			// Vinewood Sign
};

// {IntroData posx, y, z, facing angle, camera pos x, y, z, interior}
stock Float:CamPositions[6][8] = {
	{220.5151, 1822.9080, 7.5400, 270.3133, 226.688491, 1822.708251, 7.414062, 0.0 },	// Area 51 radar bg
	{487.5913,-3.0521,1002.3828,179.8082, 487.4378,-6.0787,1003.6719, 17.0 },			// Dancing club
	{1221.4973,-6.3550,1001.3281,88.1925,1216.2343,-6.3932,1001.6281,2.0},				// ILL Repude, hearts in the background
	{2324.4299,-1140.8053,1050.4922,179.3733,2324.4299,-1145.7411,1050.7101,12.0},		// CJ behind table, stairs in backgrund
	{292.2432, -81.5983, 1002.5341, 90.0, 289.2432, -79.5983, 1002.5341, 4.0},			// gun shop
	{380.880096,-2020.602294,10.250000,93.0, 375.2686,-2021.1587,10.8925, 0.0}	// Santa maria pier
};
#define INTRO_CAMERA_TIME 3000
enum p_info
{							// team the IntroData is on
	inIntro,
	bool:justConn,
	
	IntroCameraPos,
	ClassCameraPos
};

new IntroData[MAX_PLAYERS][p_info];
*/