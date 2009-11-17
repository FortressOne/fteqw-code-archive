/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

/* file generated by qcc, do not modify */

typedef struct globalvars_s
{
	int null;
	union {
		vec3_t vec;
		float f;
		int i;
	} ret;
	union {
		vec3_t vec;
		float f;
		int i;
	} param[8];
} globalvars_t;

typedef struct nqglobalvars_s
{
	int	*self;
	int	*other;
	int	*world;
	float	*time;
	float	*frametime;	
	int		*newmis;
	float	*force_retouch;
	string_t	*mapname;
	float	*deathmatch;
	float	*coop;
	float	*teamplay;
	float	*serverflags;
	float	*total_secrets;
	float	*total_monsters;
	float	*found_secrets;
	float	*killed_monsters;
	vec3_t	*V_v_forward;
	vec3_t	*V_v_up;
	vec3_t	*V_v_right;
	float	*trace_allsolid;
	float	*trace_startsolid;
	float	*trace_fraction;
	float	*trace_surfaceflags;
	float	*trace_endcontents;
	vec3_t	*V_trace_endpos;
	vec3_t	*V_trace_plane_normal;
	float	*trace_plane_dist;
	int	*trace_ent;
	float	*trace_inopen;
	float	*trace_inwater;
	int	*msg_entity;
	func_t	*main;
	func_t	*StartFrame;
	func_t	*PlayerPreThink;
	func_t	*PlayerPostThink;
	func_t	*ClientKill;
	func_t	*ClientConnect;
	func_t	*PutClientInServer;
	func_t	*ClientDisconnect;
	func_t	*SetNewParms;
	func_t	*SetChangeParms;
	float *cycle_wrapped;
	float *dimension_send;


	float *clientcommandframe;
	float *input_timelength;
	vec3_t *input_angles;
	vec3_t *input_movevalues;
	float *input_buttons;
} nqglobalvars_t;

#define P_VEC(v) (pr_global_struct->V_##v)


/*my hands are tied when it comes to the layout of this structure
On the server side, the structure *must* match original quakeworld, or we break compatibility with mvdsv's qvm api
On the client, it really doesn't matter what order fields are in, qclib will remap.
But fields that are actually useful on both sides need to be in the same locations.
But if we include all, that's a waste for csqc...
But we can overlap useful csqc-only ones with ssqc ones that are not going to be used on the client, so long as the types match.
This list isn't shared with the menu.

If the left has an underscore, it means we don't use in for ssqc at all, its dead, purely for the ssqc mod
If the middle has an underscore, then we don't use it in shared code.
If the right has an underscore, then we don't use it in csqc (yet)

if the middle has a valid name, both left+right must have valid names too.

so the base fields are a fixed size
and the extension fields are added on the end and can have extra vm-specific stuff added on the end
*/
/*DO NOT ADD TO THIS STRUCTURE*/
#define comqcfields	\
	comfieldfloat(modelindex,modelindex,modelindex);\
	comfieldvector(absmin,absmin,absmin);\
	comfieldvector(absmax,absmax,absmax);\
	comfieldfloat(ltime,_ltime,_ltime);\
	comfieldfloat(lastruntime,_lastruntime,_lastruntime);	/*type doesn't match the qc, we use a hidden double instead. this is dead.*/ 	\
	comfieldfloat(movetype,movetype,movetype);\
	comfieldfloat(solid,solid,solid);\
	comfieldvector(origin,origin,origin);\
	comfieldvector(oldorigin,_oldorigin,_oldorigin);\
	comfieldvector(velocity,velocity,velocity);\
	comfieldvector(angles,angles,angles);\
	comfieldvector(avelocity,avelocity,avelocity);\
	comfieldstring(classname,classname,classname);\
	comfieldstring(model,model,model);\
	comfieldfloat(frame,frame,frame);\
	comfieldfloat(skin,skin,skin);\
	comfieldfloat(effects,_effects,_effects);\
	comfieldvector(mins,mins,mins);\
	comfieldvector(maxs,maxs,maxs);\
	comfieldvector(size,size,size);\
	comfieldfunction(touch,touch,touch);\
	comfieldfunction(_use,_use,_use);\
	comfieldfunction(think,_think,think);\
	comfieldfunction(blocked,_blocked,_blocked);\
	comfieldfloat(nextthink,_nextthink,nextthink);\
	comfieldentity(groundentity,groundentity,groundentity);\
	comfieldfloat(health,_health,_health);\
	comfieldfloat(frags,_frags,_frags);\
	comfieldfloat(weapon,_weapon,_weapon);\
	comfieldstring(weaponmodel,_weaponmodel,_weaponmodel);\
	comfieldfloat(weaponframe,_weaponframe,_weaponframe);\
	comfieldfloat(currentammo,_currentammo,_currentammo);\
	comfieldfloat(ammo_shells,_ammo_shells,_ammo_shells);\
	comfieldfloat(ammo_nails,_ammo_nails,_ammo_nails);\
	comfieldfloat(ammo_rockets,_ammo_rockets,_ammo_rockets);\
	comfieldfloat(ammo_cells,_ammo_cells,_ammo_cells);\
	comfieldfloat(items,_items,_items);\
	comfieldfloat(takedamage,_takedamage,_takedamage);\
	comfieldentity(chain,chain,chain);\
	comfieldfloat(_deadflag,_deadflag,_deadflag);\
	comfieldvector(view_ofs,_view_ofs,_view_ofs);\
	comfieldfloat(button0,_button0,_button0);\
	comfieldfloat(button1,_button1,_button1);	/*dead field in nq mode*/	\
	comfieldfloat(button2,_button2,_button2);\
	comfieldfloat(impulse,_impulse,_impulse);\
	comfieldfloat(fixangle,_fixangle,_fixangle);\
	comfieldvector(v_angle,_v_angle,_v_angle);\
	comfieldstring(netname,_netname,_netname);\
	comfieldentity(enemy,enemy,enemy);\
	comfieldfloat(flags,flags,flags);\
	comfieldfloat(colormap,colormap,colormap);\
	comfieldfloat(team,_team,_team);\
	comfieldfloat(_max_health,_max_health,_max_health);\
	comfieldfloat(teleport_time,_teleport_time,_teleport_time);\
	comfieldfloat(_armortype,_armortype,_armortype);\
	comfieldfloat(armorvalue,_armorvalue,_armorvalue);\
	comfieldfloat(waterlevel,_waterlevel,_waterlevel);\
	comfieldfloat(watertype,_watertype,_watertype);\
	comfieldfloat(ideal_yaw,ideal_yaw,ideal_yaw);\
	comfieldfloat(yaw_speed,yaw_speed,yaw_speed);\
	comfieldentity(aiment,aiment,aiment);\
	comfieldentity(goalentity,goalentity,goalentity);\
	comfieldfloat(_spawnflags,_spawnflags,_spawnflags);\
	comfieldstring(_target,_target,_target);\
	comfieldstring(targetname,_targetname,_targetname);\
	comfieldfloat(dmg_take,_dmg_take,_dmg_take);\
	comfieldfloat(dmg_save,_dmg_save,_dmg_save);\
	comfieldentity(dmg_inflictor,_dmg_inflictor,_dmg_inflictor);\
	comfieldentity(owner,owner,owner);\
	comfieldvector(movedir,movedir,movedir);\
	comfieldstring(message,_message,_message);	/*not used directly, hexen2 uses floats, so we go via qclib for message*/\
	comfieldfloat(sounds,_sounds,_sounds);\
	comfieldstring(_noise,_noise,_noise);\
	comfieldstring(_noise1,_noise1,_noise1);\
	comfieldstring(_noise2,_noise2,_noise2);\
	comfieldstring(_noise3,_noise3,_noise3);
/*DO NOT ADD TO THE ABOVE STRUCTURE*/

#define comextqcfields	\
	comfieldfloat(gravity);	/*added in quake 1.09 (for hipnotic)*/\
	comfieldfloat(hull);/*PEXT_HEXEN2*/\
	comfieldfloat(dimension_solid);/*EXT_DIMENSION_PHYSICS*/\
	comfieldfloat(dimension_hit);/*EXT_DIMENSION_PHYSICS*/\
	comfieldfloat(scale);/*DP_ENT_SCALE*/\
	comfieldfloat(fatness);/*FTE_PEXT_FATNESS*/\
	comfieldfloat(alpha);/*DP_ENT_ALPHA*/\
	comfieldfloat(pmove_flags);/*EXT_CSQC_1*/\
	comfieldfloat(jointtype);/*DP_...PHYSICS*/\
	comfieldfloat(mass);/*DP_...PHYSICS*/\
	comfieldfloat(bouncefactor);/*DP_...PHYSICS*/\
	comfieldfloat(bouncestop);/*DP_...PHYSICS*/

#define svextqcfields \
	comfieldfloat(maxspeed);/*added in quake 1.09*/\
	comfieldfloat(items2);		/*added in quake 1.09 (for hipnotic)*/\
	comfieldvector(punchangle); /*std in nq*/\
	comfieldentity(view2);/*FTE_PEXT_VIEW2*/\
	comfieldvector(movement);\
	comfieldfloat(vw_index);\
	comfieldentity(nodrawtoclient);\
	comfieldentity(drawonlytoclient);\
	comfieldentity(viewmodelforclient);/*DP_ENT_VIEWMODEL*/\
	comfieldentity(exteriormodeltoclient);\
	comfieldfloat(button3);	/*DP_INPUTBUTTONS (note in qw, we set 1 to equal 3, to match zquake/fuhquake/mvdsv)*/\
	comfieldfloat(button4);\
	comfieldfloat(button5);\
	comfieldfloat(button6);\
	comfieldfloat(button7);\
	comfieldfloat(button8);\
	comfieldfloat(viewzoom);/*DP_VIEWZOOM*/\
	comfieldentity(tag_entity);\
	comfieldfloat(tag_index);\
	comfieldfloat(glow_size);\
	comfieldfloat(glow_color);\
	comfieldfloat(glow_trail);\
	comfieldvector(color);\
	comfieldvector(colormod);\
	comfieldfloat(light_lev);\
	comfieldfloat(style);\
	comfieldfloat(pflags);\
	comfieldfloat(clientcolors);\
	comfieldfloat(dimension_see);/*EXT_DIMENSION_VISIBLE*/\
	comfieldfloat(dimension_seen);/*EXT_DIMENSION_VISIBLE*/\
	comfieldfloat(dimension_ghost);/*EXT_DIMENSION_GHOST*/\
	comfieldfloat(dimension_ghost_alpha);/*EXT_DIMENSION_GHOST*/\
	comfieldfloat(playerclass);/*hexen2 requirements*/\
	comfieldfloat(drawflags);/*hexen2*/\
	comfieldentity(movechain);/*hexen2*/\
	comfieldfunction(chainmoved);/*hexen2*/\
	comfieldfloat(hasted);/*hexen2 uses this AS WELL as maxspeed*/\
	comfieldfloat(light_level);/*hexen2's grabbing light level from client*/\
	comfieldfloat(abslight);/*hexen2's force a lightlevel*/\
	comfieldfunction(SendEntity);/*EXT_CSQC*/\
	comfieldfloat(SendFlags);/*EXT_CSQC_1 (one of the DP guys came up with it)*/\
	comfieldfloat(Version);/*EXT_CSQC (obsolete)*/\
	comfieldfloat(pvsflags);/*EXT_CSQC_1*/\
	comfieldfloat(uniquespawnid);/*FTE_ENT_UNIQUESPAWNID*/\
	comfieldfunction(customizeentityforclient);

typedef struct stdentvars_s //standard = standard for qw
{
#define comfieldfloat(ssqcname,sharedname,csqcname) float ssqcname
#define comfieldvector(ssqcname,sharedname,csqcname) vec3_t ssqcname
#define comfieldentity(ssqcname,sharedname,csqcname) int ssqcname
#define comfieldstring(ssqcname,sharedname,csqcname) string_t ssqcname
#define comfieldfunction(ssqcname,sharedname,csqcname) func_t ssqcname
comqcfields
#undef comfieldfloat
#undef comfieldvector
#undef comfieldentity
#undef comfieldstring
#undef comfieldfunction
#ifdef VM_Q1
} stdentvars_t;

typedef struct extentvars_s
{
#endif
#define comfieldfloat(name) float name
#define comfieldvector(name) vec3_t name
#define comfieldentity(name) int name
#define comfieldstring(name) string_t name
#define comfieldfunction(name) func_t name
comextqcfields
svextqcfields
#undef comfieldfloat
#undef comfieldvector
#undef comfieldentity
#undef comfieldstring
#undef comfieldfunction

#ifdef VM_Q1
} extentvars_t;
#else
} stdentvars_t;
#endif

typedef struct {
#define comfieldfloat(ssqcname,sharedname,csqcname) float sharedname
#define comfieldvector(ssqcname,sharedname,csqcname) vec3_t sharedname
#define comfieldentity(ssqcname,sharedname,csqcname) int sharedname
#define comfieldstring(ssqcname,sharedname,csqcname) string_t sharedname
#define comfieldfunction(ssqcname,sharedname,csqcname) func_t sharedname
comqcfields
#undef comfieldfloat
#undef comfieldvector
#undef comfieldentity
#undef comfieldstring
#undef comfieldfunction

#ifdef VM_Q1
} comentvars_t;
typedef struct {
#endif

#define comfieldfloat(name) float name
#define comfieldvector(name) vec3_t name
#define comfieldentity(name) int name
#define comfieldstring(name) string_t name
#define comfieldfunction(name) func_t name
comextqcfields
#undef comfieldfloat
#undef comfieldvector
#undef comfieldentity
#undef comfieldstring
#undef comfieldfunction

#ifdef VM_Q1
} comextentvars_t;
#else
} comentvars_t;
#endif

#define	MAX_ENT_LEAFS	16



#if defined(ODE_STATIC) || defined(ODE_DYNAMIC)
#define USEODE 1
#endif

#ifdef USEODE
typedef struct {
	// physics parameters
	qboolean ode_physics;
	void *ode_body;
	void *ode_geom;
	void *ode_joint;
	float *ode_vertex3f;
	int *ode_element3i;
	int ode_numvertices;
	int ode_numtriangles;
	vec3_t ode_mins;
	vec3_t ode_maxs;
	vec_t ode_mass;
	vec3_t ode_origin;
	vec3_t ode_velocity;
	vec3_t ode_angles;
	vec3_t ode_avelocity;
	qboolean ode_gravity;
	int ode_modelindex;
	vec_t ode_movelimit; // smallest component of (maxs[]-mins[])
	float ode_offsetmatrix[16];
	float ode_offsetimatrix[16];
	int ode_joint_type;
	int ode_joint_enemy;
	int ode_joint_aiment;
	vec3_t ode_joint_origin; // joint anchor
	vec3_t ode_joint_angles; // joint axis
	vec3_t ode_joint_velocity; // second joint axis
	vec3_t ode_joint_movedir; // parameters
	void *ode_massbuf;
} entityode_t;

typedef struct
{
	// for ODE physics engine
	qboolean ode; // if true then ode is activated
	void *ode_world;
	void *ode_space;
	void *ode_contactgroup;
	// number of constraint solver iterations to use (for dWorldStepFast)
	int ode_iterations;
	// actual step (server frametime / ode_iterations)
	vec_t ode_step;
	// max velocity for a 1-unit radius object at current step to prevent
	// missed collisions
	vec_t ode_movelimit;
} worldode_t;
#endif
