public showRank(id){
	#if ADVANCED_DEBUG == 1
		writeDebugInfo("showRank",id)
	#endif

	if(!p_data[id][P_SPECMODE] || !warcraft3 || !iCvar[FT_SPEC_INFO])
		return PLUGIN_CONTINUE

	new a = read_data(2)

	if (!p_data_b[a][PB_ISCONNECTED])
		return PLUGIN_CONTINUE		// not valid target 

	WAR3_Show_Spectator_Info(id, a)
	
	return PLUGIN_CONTINUE
}

#if MOD == 0
	public setSpecMode(id) {
		#if ADVANCED_DEBUG == 1
			writeDebugInfo("setSpecMode",0)
		#endif

		new arg[12] 
		read_data( 2 , arg , 11 ) 
		p_data[id][P_SPECMODE] = ( arg[10] == '2' ) ? 1 : 0 
	}
#endif

public checkmap(){
	#if ADVANCED_DEBUG == 1
		writeDebugInfo("checkmap",0)
	#endif

	#if MOD ==0
		new mapname[32]
		get_mapname(mapname,31) 
		if (containi(mapname,"ka_")!=-1 || containi(mapname,"scoutzknivez")!=-1){
			g_givePistol=false
			if (iCvar[FT_NO_GLOVES_ON_KA])
				g_giveHE=false
			else
				g_giveHE=true
		}
		else{
			g_giveHE=true
			g_givePistol=true
		}
		if(iCvar[FT_NO_ORCNADES]){
			if (containi(mapname,"ka_")!=-1 || containi(mapname,"jail_riot")!=-1 || containi(mapname,"fy_")!=-1) 
				g_notAllowHE=true
			else
				g_notAllowHE=false
		}
	#endif
	
	return PLUGIN_CONTINUE
}

public changeskin(id,reset){							// Function changes your skin for ITEM_MOLE and Chameleon
	#if ADVANCED_DEBUG == 1
		writeDebugInfo("changeskin",id)
	#endif
#if MOD == 0
	new num = 0, newSkin[32]
	if (is_running("cstrike"))
		num = random_num(0,3)
	else if (is_running("czero"))
		num = random_num(0,4)

	
	if (reset==SKIN_RESET && (p_data[id][P_SKINCHANGED] == SKIN_HEX || p_data[id][P_SKINCHANGED]==SKIN_SWITCH)){
		cs_reset_user_model(id)
		p_data[id][P_SKINCHANGED]=SKIN_RESET
		//console_print(id,"### Skin reset", newSkin)
	}
	else if (reset==SKIN_HEX){ 
		if(!g_mapDisabled)
			cs_set_user_model(id,"alien4")
		p_data[id][P_SKINCHANGED]=SKIN_HEX
		//console_print(id,"### You should look like an alien", newSkin)
	}
	else if (reset==SKIN_SWITCH){
		if (get_user_team(id)==TS)
			add(newSkin,31,CTSkins[num])
		else
			add(newSkin,31,TSkins[num])

		cs_set_user_model(id,newSkin)
		//console_print(id,"### You should look like: %s", newSkin)
		p_data[id][P_SKINCHANGED]=SKIN_SWITCH
	}
#endif
	return PLUGIN_CONTINUE
}


public clear_all_icons(id){
	#if ADVANCED_DEBUG == 1
		writeDebugInfo("clear_all_icons",id)
	#endif
	#if MOD == 0
		if(id==0)
			return PLUGIN_CONTINUE

		new string[8][32] = {"dmg_rad","item_longjump","dmg_shock","item_healthkit","dmg_heat","suit_full","cross","dmg_gas"}
		for(new i=0;i<8;i++){
			Create_StatusIcon(id, ICON_HIDE, string[i], 0, 0, 0)
		}
	#endif
	return PLUGIN_CONTINUE
}

public icon_controller(id, value){
	#if ADVANCED_DEBUG == 1
		writeDebugInfo("icon_controller",id)
	#endif

	if (!iCvar[FT_SHOW_ICONS])
		return PLUGIN_HANDLED
	if(!p_data[id][P_ULTIMATE])
		return PLUGIN_HANDLED
	if (g_ultimateDelay > 0.0)
		return PLUGIN_HANDLED
	if(p_data_b[id][PB_ULTIMATEUSED] && value!=ICON_HIDE)
		return PLUGIN_HANDLED
	if(id==0)
		return PLUGIN_HANDLED
#if MOD == 0
	new string[32], r, g, b, switchValue
	if(p_data[id][P_RACE] == 9)
		switchValue = race9Options[4]
	else
		switchValue = p_data[id][P_RACE]

	switch(switchValue){
		case 1:format(string,31,"dmg_rad"),			r=255,	g=0,	b=0			// Undead
		case 2:format(string,31,"item_longjump"),	r=0,	g=120,	b=120		// Human
		case 3:format(string,31,"dmg_shock"),		r=255,	g=255,	b=255		// Orc
		case 4:format(string,31,"item_healthkit"),	r=0,	g=0,	b=255		// Night Elf
		case 5:format(string,31,"dmg_heat"),		r=255,	g=0,	b=0			// Blood Mage
		case 6:format(string,31,"suit_full"),		r=0,	g=200,	b=200		// Shadow Hunter
		case 7:format(string,31,"cross"),			r=255,	g=0,	b=0			// Warden
		case 8:format(string,31,"dmg_gas"),			r=0,	g=255,	b=0			// Crypt Lord
	}

	if(!is_user_alive(id))			// If the user is dead then hide the icon
		value = ICON_HIDE

	if(value==ICON_FLASH){
		if( Verify_Skill(id, RACE_UNDEAD, SKILL4) )
			r=255,g=255,b=255
	}

	Create_StatusIcon(id, value, string, r, g, b)
#endif
	return PLUGIN_CONTINUE
}

public FT_controller(){
	#if ADVANCED_DEBUG == 1
		writeDebugInfo("FT_controller",0)
	#endif

	FT_control = get_cvar_num("FT_control")
	FT_start = get_cvar_num("FT_start")
	FT_stop = get_cvar_num("FT_stop")
	FT_message = get_cvar_num("FT_message")

	new stime[4],sminute[4]
	get_time("%M",sminute,3)
	get_time("%H",stime,3)
	new minutes = str_to_num(sminute)
	new hours  = str_to_num(stime)
	new nextmap[32]
	get_cvar_string("amx_nextmap",nextmap,31)
	new timeleft = get_timeleft()
	set_hudmessage(50, 50, 200, 0.13, 0.01, 2, 1.5, 12.0, 0.02, 5.0,15)
	new bool:okidoki = false
	new message[128]
	if (FT_control){
		if(FT_start > FT_stop){
			if (((hours >= FT_start) && (hours > FT_stop)) || ((hours < FT_start) && (hours < FT_stop)))
				okidoki = true
		}
		if (FT_stop > FT_start){
			if ((hours >= FT_start) && (hours < FT_stop))
				okidoki = true
		}	
		if (FT_start == FT_stop)
			okidoki = true
		if(okidoki){
			set_cvar_num("sv_warcraft3",1)
			if (FT_start == FT_stop)
				format(message,127,"")
			else{			
				format(message,127,"%L",LANG_PLAYER,"BETWEEN",FT_start,FT_stop)
			}
		}		
		else{
			set_cvar_num("sv_warcraft3",0)
			format(message,127,"de %dh a %dh",FT_stop,FT_start)
		}
		if (!get_cvar_num("sv_warcraft3") && FT_message){
			show_hudmessage(0,"%L",LANG_PLAYER,"INACTIVE",WC3NAME,WC3VERSION,message,hours,minutes,timeleft / 60, timeleft % 60,nextmap)
		}
		if (get_cvar_num("sv_warcraft3") && FT_message){
			show_hudmessage(0,"%L",LANG_PLAYER,"ACTIVE",WC3NAME,WC3VERSION,message,hours,minutes,timeleft / 60, timeleft % 60,nextmap)
		}
		set_hudmessage(200, 100, 0, -1.0, 0.3, 0, 1.0, 10.0, 0.1, 0.2, 17)
		if ((g_lastAnnounce != minutes) && (hours == (FT_start - 1)) && ((minutes == 30) || (minutes == 45)|| (minutes == 55))){
			g_lastAnnounce = minutes
			show_hudmessage(0,"%L",LANG_PLAYER,"IS_ACTIVATED",WC3NAME,60 - minutes)			
		}
		if ((g_lastAnnounce != minutes) && (hours == (FT_stop - 1)) && ((minutes == 30) || (minutes == 45) || (minutes == 55))){
			g_lastAnnounce = minutes
			show_hudmessage(0,"%L",LANG_PLAYER,"WILL_BE_DEACTIVATED_IN",WC3NAME,60 - minutes)
		}
	}
	else
	{
		if (warcraft3==false && FT_message)	{	
			show_hudmessage(0,"%L",LANG_PLAYER,"INACTIVE_ELSE",WC3NAME,WC3VERSION,hours,minutes,timeleft / 60, timeleft % 60,nextmap)	
		}
		if (warcraft3==true && FT_message){
			show_hudmessage(0,"%L",LANG_PLAYER,"ACTIVE_ELSE",WC3NAME,WC3VERSION,hours,minutes,timeleft / 60, timeleft % 60,nextmap)
		}
	}		
	return PLUGIN_CONTINUE
}

public getuserinput(parm[1]){
	#if ADVANCED_DEBUG == 1
		writeDebugInfo("getuserinput",parm[0])
	#endif

	new id = parm[0]

	if(!p_data_b[id][PB_ISCONNECTED])
		return PLUGIN_CONTINUE

	new skillsused = p_data[id][P_SKILL1]+p_data[id][P_SKILL2]+p_data[id][P_SKILL3]+p_data[id][P_ULTIMATE]
	if (p_data[id][P_RACE] == 0){
		WAR3_chooserace(id)
	}
	else if (skillsused < p_data[id][P_LEVEL])
		menu_Select_Skill(id,0)
	else
		WAR3_Display_Level(id, DISPLAYLEVEL_NONE)

	return PLUGIN_HANDLED
}

public weapon_controller( parm[2]  ){
	#if ADVANCED_DEBUG == 1
		writeDebugInfo("weapon_controller",parm[0])
	#endif

	if (warcraft3==false)
		return PLUGIN_CONTINUE

	#if MOD == 0
		new id = parm[0]
		
		if(!p_data_b[id][PB_ISCONNECTED])
			return PLUGIN_CONTINUE

		new bool:reincarnate = false
		
		// Give items because of respawning...
		if(p_data_b[id][PB_GIVEITEMS]){
			reincarnate = true
			p_data_b[id][PB_GIVEITEMS]=false
		}
									
		// Equipement & Eligibility Check for Re-Incarnation
		if (p_data_b[id][PB_DIEDLASTROUND]){	// DIED LAST ROUND		
			new Float:randomnumber = random_float(0.0,1.0)   
			if ( Verify_Skill(id, RACE_ORC, SKILL3) ){
				if( randomnumber <= p_ankh[p_data[id][P_SKILL3]-1] ){
					reincarnate = true				
				}
			}
			if (p_data[id][P_ITEM]==ITEM_ANKH){
				reincarnate=true
			}	
		}

		if (reincarnate){
				client_cmd(id, "speak warcraft3/soundpack/reincarnation.wav")

				if (iglow[id][1] < 1){
					parm[0] = id
					set_task(0.1,"glow_change",TASK_GLOW+id,parm,2)
				} 
				iglow[id][1] += 100
				iglow[id][0] = 0
				iglow[id][2] = 0
				iglow[id][3] = 0
				if (iglow[id][1]>MAXGLOW)
					iglow[id][1]=MAXGLOW

				// Screen fade green
				Create_ScreenFade(id, (1<<10), (1<<10), (1<<12), 0, 255, 0, iglow[id][1])

				_Skill_Reincarnation_Drop(id)
				_Skill_Reincarnation_Give(id)
		}else{
			if(!cs_get_user_nvg(id))
				p_data_b[id][PB_NIGHTVISION]=false
			/**if(!cs_get_user_defuse(id))
				p_data_b[id][PB_DEFUSE]=false*/
		}
	#endif

	Item_Check(parm)

	return PLUGIN_HANDLED	
}	

public saveweapons(id){
	#if ADVANCED_DEBUG == 1
		writeDebugInfo("saveweapons",id)
	#endif

	#if MOD == 0
		p_data[id][P_ARMORONDEATH]=get_user_armor(id)
	#endif
	for (new i=0; i<32; ++i){		// Equipment Reincarnation
		savedweapons[id][i]=0
	}
	p_data[id][P_SAVEDNUMBER]=0
	get_user_weapons(id,savedweapons[id],p_data[id][P_SAVEDNUMBER])
	return PLUGIN_CONTINUE
}

public glow_change(parm[]){
	#if ADVANCED_DEBUG == 1
		writeDebugInfo("glow_change",parm[0])
	#endif

	new id = parm[0]

	if(!p_data_b[id][PB_ISCONNECTED])
		return PLUGIN_CONTINUE

	if ( Verify_Skill(id, RACE_HUMAN, SKILL1) ){	// Don't glow if player is invisible
		iglow[id][0] = 0
		iglow[id][1] = 0
		iglow[id][2] = 0
		iglow[id][3] = 0
	}
	else if ( p_data[id][P_ITEM]==ITEM_CLOAK ){		// Don't glow if player is invisible
		iglow[id][0] = 0
		iglow[id][1] = 0
		iglow[id][2] = 0
		iglow[id][3] = 0
	}
	else if (iglow[id][0] > 5){
		set_user_rendering(id,kRenderFxGlowShell,iglow[id][0],0,0, kRenderNormal, 16)
		iglow[id][0] -= 5
		set_task(0.2,"glow_change",TASK_GLOW+id,parm,2)
	}
	else if (iglow[id][1] > 5){
		set_user_rendering(id,kRenderFxGlowShell,0,iglow[id][1],0, kRenderNormal, 16)
		iglow[id][1] -= 5
		set_task(0.2,"glow_change",TASK_GLOW+id,parm,2)
	}
	else if (iglow[id][2] > 5){
		set_user_rendering(id,kRenderFxGlowShell,0,0,iglow[id][2], kRenderNormal, 16)
		iglow[id][2] -= 5
		set_task(0.2,"glow_change",TASK_GLOW+id,parm,2)
	}
	else if (iglow[id][3] > 5){
		set_user_rendering(id,kRenderFxGlowShell,iglow[id][3],iglow[id][3],iglow[id][3], kRenderNormal, 16)
		iglow[id][3] -= 5
		set_task(0.2,"glow_change",TASK_GLOW+id,parm,2)
	}
	else{
		iglow[id][0] = 0
		iglow[id][1] = 0
		iglow[id][2] = 0
		iglow[id][3] = 0
		set_user_rendering(id)
	}
	return PLUGIN_CONTINUE
}

public reset_maxspeed(parm[]){
	#if ADVANCED_DEBUG == 1
		writeDebugInfo("reset_maxspeed",parm[0])
	#endif

	new enemy = parm[0]

	if(!p_data_b[enemy][PB_ISCONNECTED])
		return PLUGIN_CONTINUE

	new normalspeed = parm[1]
	p_data_b[enemy][PB_STUNNED]=false
	p_data_b[enemy][PB_SLOWED]=false
	set_user_maxspeed(enemy, float(normalspeed))
	return PLUGIN_CONTINUE
}

public unholyspeed(parm[1]){
	#if ADVANCED_DEBUG == 1
		writeDebugInfo("unholyspeed",parm[0])
	#endif

	if (warcraft3==false)
		return PLUGIN_CONTINUE

	new id = parm[0]

	if(!p_data_b[id][PB_ISCONNECTED])
		return PLUGIN_CONTINUE

	if (p_data_b[id][PB_STUNNED]){
		set_user_maxspeed(id,1.0)
		return PLUGIN_HANDLED
	}
	else if (p_data_b[id][PB_SLOWED]){
		set_user_maxspeed(id,fCvar[FT_FROST_SPEED])
		return PLUGIN_HANDLED
	}
#if MOD == 1
	else if(entity_get_int(id,EV_INT_iuser3)){	// User is in prone position, don't change speed
		if(get_user_maxspeed(id) > 500.0)
			set_user_maxspeed(id, 50.0)

		return PLUGIN_HANDLED
	}
	else if(get_user_maxspeed(id) == 50.0){		// User has a rocket launcher "mounted"
		set_user_maxspeed(id, 600.0)
	}
#endif
#if MOD == 0
	else if (get_user_maxspeed(id)>5 && Verify_Skill(id, RACE_UNDEAD, SKILL2) && !g_freezetime){              // Unholy Aura
		if (get_user_maxspeed(id)>5 && get_user_maxspeed(id)!=p_unholy[p_data[id][P_SKILL2]-1])
			set_user_maxspeed(id,(p_unholy[p_data[id][P_SKILL2]-1]))
	}
	else if (get_user_maxspeed(id)>5 && p_data[id][P_ITEM]==ITEM_BOOTS && !g_freezetime){			// Boots of Speed
		if (get_user_maxspeed(id)!=fCvar[FT_BOOTSPEED])
			set_user_maxspeed(id,fCvar[FT_BOOTSPEED])
	}
#endif

	return PLUGIN_CONTINUE
}

public func_spawn(parm[2]){
	#if ADVANCED_DEBUG == 1
		writeDebugInfo("func_spawn",parm[0])
	#endif

	if (endround){
		set_user_money(parm[0],get_user_money(parm[0])+itemcost2[0],1)
		return PLUGIN_HANDLED
	}

	new id = parm[0]

	if(!p_data_b[id][PB_ISCONNECTED])
		return PLUGIN_CONTINUE

	if(get_user_team(id)==UNASSIGNED)
		return PLUGIN_CONTINUE

	p_data[id][P_ITEM]=0
	p_data[id][P_ITEM2]=0
	
	if (is_user_alive(id))
		return PLUGIN_CONTINUE

	new team[32]
	get_user_team(id,team,31)
	p_data_b[id][PB_PLAYERSPAWNED]=true
	icon_controller(id,ICON_SHOW)
	spawn(id)
	p_data_b[id][PB_SLOWED]=false
	p_data_b[id][PB_STUNNED]=false
	spawn(id)
	set_task(0.3,"spawn_player",TASK_SPAWNPLAYER+id,parm,2)
	set_task(0.5,"player_giveitems",TASK_GIVEITEMS+id,parm,2)

#if MOD == 0
	give_item(id, "weapon_knife")
#endif
	
	new money = get_user_money(id)

	#if MOD == 0
		if (money < get_cvar_num("mp_startmoney"))
			set_user_money(id,get_cvar_num("mp_startmoney"),0)
	#endif
	#if MOD == 1
		if (money < iCvar[DOD_STARTMONEY])
			set_user_money(id,iCvar[DOD_STARTMONEY],0)

	#endif
	return PLUGIN_CONTINUE
}


public player_giveitems(parm[2]){
	#if ADVANCED_DEBUG == 1
		writeDebugInfo("player_giveitems",parm[0])
	#endif

	new id = parm[0]

	if(!p_data_b[id][PB_ISCONNECTED])
		return PLUGIN_CONTINUE

	// Vengeance
	if( Verify_Skill(id, RACE_WARDEN, SKILL4) && !p_data_b[id][PB_SPAWNEDFROMITEM])
		set_user_health(id,50)

	// Evasion
	else if ( Verify_Skill(id, RACE_ELF, SKILL1) && p_data_b[id][PB_EVADENEXTSHOT])
		set_user_health(id,1124)

	// Devotion Aura
	else if ( Verify_Skill(id, RACE_HUMAN, SKILL2))							
		set_user_health(id,p_devotion[p_data[id][P_SKILL2]-1])

	p_data_b[id][PB_GIVEITEMS]=true
	set_task(0.1, "weapon_controller", TASK_REINCARNATION+id, parm, 2)							// Give weapons back

	give_item(id, "item_suit")

	#if MOD == 0
		give_item(id, "weapon_knife")
	#endif

	// The following code decides if pistols should be given
	#if MOD == 0
		if (!g_givePistol)
			return PLUGIN_CONTINUE

		new wpnList[32] = 0, number = 0, foundGlock = false, foundUSP = false 
		get_user_weapons(id,wpnList,number)
		for (new i = 0;i < number;i++) { 
			if (wpnList[i] == CSW_GLOCK18) 
				foundGlock = true 
			if (wpnList[i] == CSW_USP) 
				foundUSP = true 
		} 
		if (get_user_team(id)==TS){
			if(foundGlock)
				return PLUGIN_CONTINUE
			else{
				give_item(id,"weapon_glock18")
				give_item(id,"ammo_9mm")
				give_item(id,"ammo_9mm")
				give_item(id,"ammo_9mm")
			}

		}
		if (get_user_team(id)==CTS){
			if(foundUSP)
				return PLUGIN_CONTINUE
			else{
				give_item(id,"weapon_usp")
				give_item(id,"ammo_45acp")
				give_item(id,"ammo_45acp")
				give_item(id,"ammo_45acp")
				give_item(id,"ammo_45acp")
				give_item(id,"ammo_45acp")
				give_item(id,"ammo_45acp")
				give_item(id,"ammo_45acp")
			}
		}
	#endif
	return PLUGIN_CONTINUE

}

public spawn_player(parm[2]){
	#if ADVANCED_DEBUG == 1
		writeDebugInfo("spawn_player",parm[0])
	#endif

	new id = parm[0]

	if(!p_data_b[id][PB_ISCONNECTED])
		return PLUGIN_CONTINUE

	p_data_b[id][PB_PLAYERSPAWNED]=true
	spawn(id)
	give_item(id, "item_suit")
#if MOD == 0
	give_item(id, "weapon_knife")
#endif
	return PLUGIN_CONTINUE

}

public set_user_money(id,money,show){
	#if ADVANCED_DEBUG == 1
		writeDebugInfo("set_user_money",id)
	#endif

	if(!p_data_b[id][PB_ISCONNECTED])
		return PLUGIN_CONTINUE

	#if MOD == 0
		cs_set_user_money(id,money,show)
	#endif
	#if MOD == 1
		new parm[3]
		parm[0] = id
		parm[1] = 1
		parm[2] = money - get_user_money(id)

		p_data[id][P_MONEY]=money
		_DOD_showMoney(parm)
	#endif
	return PLUGIN_CONTINUE
}

public get_user_money(id){
	#if ADVANCED_DEBUG == 1
		writeDebugInfo("get_user_money",id)
	#endif

	if(!p_data_b[id][PB_ISCONNECTED])
		return PLUGIN_CONTINUE

	#if MOD == 0
		return cs_get_user_money(id)
	#endif
	#if MOD == 1
		return p_data[id][P_MONEY]
	#endif
}
