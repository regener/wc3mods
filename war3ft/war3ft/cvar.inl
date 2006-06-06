
// Half-Life CVARs
new CVAR_mp_friendlyfire;

// Miscellaneous Configuration CVARs
new CVAR_wc3_query_client;
new CVAR_wc3_show_player;
new CVAR_wc3_buy_dead;
new CVAR_wc3_buy_time;
new CVAR_wc3_buy_zone;
new CVAR_wc3_races;
new CVAR_wc3_spec_position;
new CVAR_wc3_grenade_protection;

// Icon CVARs
new CVAR_wc3_race_icon;
new CVAR_wc3_level_icon;

// Admin CVARs
new CVAR_wc3_admin_flag;

// XP CVARs
new CVAR_wc3_xp_radius;
new CVAR_wc3_win_round;
new CVAR_wc3_headshot;
new CVAR_wc3_kill_defuser;
new CVAR_wc3_vip_escape;
new CVAR_wc3_kill_bomb_carrier;
new CVAR_wc3_kill_bomb_planter;
new CVAR_wc3_defuse_bomb;
new CVAR_wc3_rescue_hostage;
new CVAR_wc3_kill_rescuer;
new CVAR_wc3_kill_vip;
new CVAR_wc3_min_players;
new CVAR_wc3_xp_multiplier;
new CVAR_wc3_xp_weap_multiplier;
new CVAR_wc3_xp_auto_average;
new CVAR_wc3_show_kill_obj;
new CVAR_wc3_show_objectives;

// XP Saving CVARs
new CVAR_wc3_save_xp;
new CVAR_wc3_save_pruning;
new CVAR_wc3_days_before_delete;
new CVAR_wc3_save_by;
new CVAR_wc3_save_xp_sql;

// Database CVARs
new CVAR_wc3_sql_tbname;
new CVAR_wc3_sql_dbhost;
new CVAR_wc3_sql_dbuser;
new CVAR_wc3_sql_dbpass;
new CVAR_wc3_sql_dbname;
new CVAR_wc3_save_end_round;

// Ultimate CVARs
new CVAR_wc3_entangle_drop;
new CVAR_wc3_ult_delay;
new CVAR_wc3_ult_cooldown;
new CVAR_wc3_blink_protection;
new CVAR_wc3_blink_dizziness;

// Items
new CVAR_wc3_tome;
new CVAR_wc3_claw;
new CVAR_wc3_health;
new CVAR_wc3_frost;
new CVAR_wc3_mask;
new CVAR_wc3_cloak;
new CVAR_wc3_sock;
new CVAR_wc3_glove_timer;
new CVAR_wc3_glove_orc_damage;

// Chameleon
new CVAR_wc3_cham_random;
new CVAR_wc3_cham_skill1;
new CVAR_wc3_cham_skill2;
new CVAR_wc3_cham_skill3;
new CVAR_wc3_cham_ultimate;

// Bot CVARs
new CVAR_wc3_bot_buy_item;

// DOD CVARs
new CVAR_wc3_dod_start_money;

// Cstrike/Czero CVARs
new CVAR_wc3_boots;

public CVAR_Init()
{
	// Plugin Information CVARs

	new szAmxCvar[32];
	format( szAmxCvar, 31 , "%s %s", WC3NAME, WC3VERSION );

									 register_cvar( "War3: Frozen Throne"		, WC3VERSION	, FCVAR_SERVER );
									 register_cvar( "amx_war3_version"			, szAmxCvar		, FCVAR_SERVER );
									 register_cvar( "amx_war3_date"				, WC3DATE		, FCVAR_SERVER );


	// Admin CVARs

	CVAR_wc3_admin_flag				= register_cvar( "wc3_admin_flag"			, "m"							);

	// Miscellaneous Configuration CVARs

	CVAR_wc3_query_client			= register_cvar( "wc3_query_client"			, "1"							);
	CVAR_wc3_show_player			= register_cvar( "wc3_show_player"			, "1"							);
	CVAR_wc3_buy_dead				= register_cvar( "wc3_buy_dead"				, "1"							);
	CVAR_wc3_buy_time				= register_cvar( "wc3_buy_time"				, "0"							);
	CVAR_wc3_buy_zone				= register_cvar( "wc3_buy_zone"				, "0"							);
	CVAR_wc3_races					= register_cvar( "wc3_races"				, "8"		, FCVAR_SERVER		);
	CVAR_wc3_spec_position			= register_cvar( "wc3_spec_position"		, "0"							);
	CVAR_wc3_grenade_protection		= register_cvar( "wc3_grenade_protection"	, "0"							);

	// Icon CVARs

	CVAR_wc3_race_icon				= register_cvar( "wc3_race_icon"			, "1"							);
	CVAR_wc3_level_icon				= register_cvar( "wc3_level_icon"			, "1"							);

	// Saving CVARs

	CVAR_wc3_save_xp				= register_cvar( "wc3_save_xp"				, "0"		, FCVAR_SERVER		);
	CVAR_wc3_save_pruning			= register_cvar( "wc3_save_pruning"			, "0"		, FCVAR_SERVER		);
	CVAR_wc3_days_before_delete		= register_cvar( "SAVE_Expire_Time"			, "31"							);
	CVAR_wc3_save_end_round			= register_cvar( "wc3_save_end_round"		, "1"							);
	CVAR_wc3_save_xp_sql			= register_cvar( "wc3_save_xp_sql"			, "0"							);
	CVAR_wc3_save_by				= register_cvar( "wc3_save_by"				, "0"							);


	// Ultimate CVARs

	CVAR_wc3_entangle_drop			= register_cvar( "wc3_entangle_drop"		, "0"							);
	CVAR_wc3_ult_delay				= register_cvar( "wc3_ult_delay"			, "15.0"						);
	CVAR_wc3_ult_cooldown			= register_cvar( "wc3_ult_cooldown"			, "35.0"						);
	CVAR_wc3_blink_protection		= register_cvar( "wc3_blink_protection"		, "1"							);
	CVAR_wc3_blink_dizziness		= register_cvar( "wc3_blink_dizziness"		, "0"							);

	// Item CVARs

	CVAR_wc3_tome					= register_cvar( "wc3_tome"					, "50"							);
	CVAR_wc3_claw					= register_cvar( "wc3_claw"					, "6"							);
	CVAR_wc3_health					= register_cvar( "wc3_health"				, "15"							);
	CVAR_wc3_frost					= register_cvar( "wc3_frost"				, "125"							);
	CVAR_wc3_mask					= register_cvar( "wc3_mask"					, "0.3"							);
	CVAR_wc3_cloak					= register_cvar( "wc3_cloak"				, "150"							);
	CVAR_wc3_sock					= register_cvar( "wc3_sock"					, "0.5"							);
	CVAR_wc3_glove_timer			= register_cvar( "wc3_glove_timer"			, "10"							);
	CVAR_wc3_glove_orc_damage		= register_cvar( "wc3_glove_orc_damage"		, "0"							);

	// Chameleon Race CVARs

	CVAR_wc3_cham_random			= register_cvar( "wc3_cham_random"			, "1"							);
	CVAR_wc3_cham_skill1			= register_cvar( "wc3_cham_skill1"			, "1"							);
	CVAR_wc3_cham_skill2			= register_cvar( "wc3_cham_skill2"			, "1"							);
	CVAR_wc3_cham_skill3			= register_cvar( "wc3_cham_skill3"			, "1"							);
	CVAR_wc3_cham_ultimate			= register_cvar( "wc3_cham_ultimate"		, "1"							);
	
	// Database CVARs

	CVAR_wc3_sql_tbname				= register_cvar( "wc3_sql_tbname"			, "war3users"					);
	CVAR_wc3_sql_dbhost				= register_cvar( "wc3_sql_dbhost"			, "127.0.0.1"					);
	CVAR_wc3_sql_dbuser				= register_cvar( "wc3_sql_dbuser"			, "root"						);
	CVAR_wc3_sql_dbpass				= register_cvar( "wc3_sql_dbpass"			, ""							);
	CVAR_wc3_sql_dbname				= register_cvar( "wc3_sql_dbname"			, "amx"							);

	// XP Modifier CVARs

	CVAR_wc3_min_players			= register_cvar( "wc3_min_players"			, "2"							);
	CVAR_wc3_xp_radius 				= register_cvar( "wc3_xp_radius"			, "750"							);
	CVAR_wc3_win_round				= register_cvar( "wc3_win_round"			, "35"							);
	CVAR_wc3_headshot				= register_cvar( "wc3_headshot"				, "9"							);
	CVAR_wc3_kill_defuser			= register_cvar( "wc3_kill_defuser"			, "25"							);
	CVAR_wc3_vip_escape				= register_cvar( "wc3_vip_escape"			, "30"							);
	CVAR_wc3_kill_bomb_carrier		= register_cvar( "wc3_kill_bomb_carrier"	, "25"							);
	CVAR_wc3_kill_bomb_planter		= register_cvar( "wc3_kill_bomb_planter"	, "15"							);
	CVAR_wc3_defuse_bomb			= register_cvar( "wc3_defuse_bomb"			, "30"							);
	CVAR_wc3_rescue_hostage			= register_cvar( "wc3_rescue_hostage"		, "25"							);
	CVAR_wc3_kill_rescuer			= register_cvar( "wc3_kill_rescuer"			, "25"							);
	CVAR_wc3_kill_vip				= register_cvar( "wc3_kill_vip"				, "25"							);
	CVAR_wc3_show_kill_obj			= register_cvar( "wc3_show_kill_obj"		, "0"							);
	CVAR_wc3_show_objectives		= register_cvar( "wc3_show_objectives"		, "1"							);
	CVAR_wc3_xp_multiplier			= register_cvar( "wc3_xp_multiplier"		, "1.0"		, FCVAR_SERVER		);
	CVAR_wc3_xp_weap_multiplier		= register_cvar( "wc3_xp_weap_multiplier"	, "1"							);
	CVAR_wc3_xp_auto_average		= register_cvar( "CVAR_wc3_xp_auto_average"	, "0"							);
	
	// Bot CVARs

	CVAR_wc3_bot_buy_item			= register_cvar( "wc3_bot_buy_item"			, "0.33"						);

	// MOD specific CVARs
	CVAR_wc3_dod_start_money	= register_cvar( "wc3_dod_start_money"			, "800"							);
	CVAR_wc3_boots				= register_cvar( "wc3_boots"					, "275"							);

}

// Function will configure the various CVARs
public CVAR_Configure()
{
	// We will only change the bonus' if we are saving XP
	if ( get_pcvar_num( CVAR_wc3_save_xp ) )
	{
		new iXPDivisor = 5;
	
		set_pcvar_num( CVAR_wc3_win_round			, (get_pcvar_num( CVAR_wc3_win_round ) / iXPDivisor)			);
		set_pcvar_num( CVAR_wc3_headshot			, (get_pcvar_num( CVAR_wc3_headshot ) / iXPDivisor)				);
		set_pcvar_num( CVAR_wc3_kill_defuser		, (get_pcvar_num( CVAR_wc3_kill_defuser ) / iXPDivisor)			);
		set_pcvar_num( CVAR_wc3_vip_escape			, (get_pcvar_num( CVAR_wc3_vip_escape ) / iXPDivisor)			);
		set_pcvar_num( CVAR_wc3_kill_bomb_carrier	, (get_pcvar_num( CVAR_wc3_kill_bomb_carrier ) / iXPDivisor)	);
		set_pcvar_num( CVAR_wc3_kill_bomb_planter	, (get_pcvar_num( CVAR_wc3_kill_bomb_planter ) / iXPDivisor)	);
		set_pcvar_num( CVAR_wc3_defuse_bomb			, (get_pcvar_num( CVAR_wc3_defuse_bomb ) / iXPDivisor)			);
		set_pcvar_num( CVAR_wc3_rescue_hostage		, (get_pcvar_num( CVAR_wc3_rescue_hostage ) / iXPDivisor)		);
		set_pcvar_num( CVAR_wc3_kill_rescuer		, (get_pcvar_num( CVAR_wc3_kill_rescuer ) / iXPDivisor)			);
		set_pcvar_num( CVAR_wc3_kill_vip			, (get_pcvar_num( CVAR_wc3_kill_vip ) / iXPDivisor)				);
		set_pcvar_num( CVAR_wc3_tome				, (get_pcvar_num( CVAR_wc3_tome ) / iXPDivisor)					);
	}

	// Configure the Chameleon Race
	if ( !get_pcvar_num( CVAR_wc3_cham_random ) )
	{
		g_ChamSkills[1] = get_pcvar_num( CVAR_wc3_cham_skill1 );
		g_ChamSkills[2] = get_pcvar_num( CVAR_wc3_cham_skill2 );
		g_ChamSkills[3] = get_pcvar_num( CVAR_wc3_cham_skill3 );
		g_ChamSkills[4] = get_pcvar_num( CVAR_wc3_cham_ultimate );
	}
}

public plugin_cfg()
{
	// Get Half-Life CVAR Pointers
	CVAR_mp_friendlyfire = get_cvar_pointer( "mp_friendlyfire" );
}