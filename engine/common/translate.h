#ifdef TRANSLATE_H
	NAME(STL_LANGUAGENAME)

	NAME(TL_NL)
	NAME(TL_ST)
	NAME(TL_STNL)

	NAME(STL_CLIENTCONNECTED)
	NAME(STL_SPECTATORCONNECTED)
	NAME(STL_RECORDEDCLIENTCONNECTED)
	NAME(STL_RECORDEDSPECTATORCONNECTED)
	NAME(STL_CLIENTWASBANNED)
	NAME(STL_YOUWEREBANNED)
	NAME(STL_YOUAREBANNED)
	NAME(STL_CLIENTTIMEDOUT)
	NAME(STL_LOADZOMIBETIMEDOUT)
	NAME(STL_CLIENTWASKICKED)
	NAME(STL_YOUWEREKICKED)
	NAME(STL_YOUWEREKICKEDNAMESPAM)
	NAME(STL_CLIENTKICKEDNAMESPAM)
	NAME(STL_GODON)
	NAME(STL_GODOFF)
	NAME(STL_NOCLIPON)
	NAME(STL_NOCLIPOFF)

	NAME(STL_CLIENTISCUFFEDPERMANENTLY)
	NAME(STL_CLIENTISCUFFED)
	NAME(STL_CLIENTISSTILLCUFFED)
	NAME(STL_YOUWERECUFFED)
	NAME(STL_YOUARNTCUFFED)

	NAME(STL_CLIENTISCRIPPLEDPERMANENTLY)
	NAME(STL_CLIENTISCRIPPLED)
	NAME(STL_CLIENTISSTILLCRIPPLED)
	NAME(STL_YOUWERECLIPPLED)
	NAME(STL_YOUARNTCRIPPLED)

	NAME(STL_CLIENTISMUTEDPERMANENTLY)
	NAME(STL_CLIENTISMUTED)
	NAME(STL_CLIENTISSTILLMUTED)
	NAME(STL_YOUAREMUTED)
	NAME(STL_YOUARNTMUTED)
	NAME(STL_NONAMEASMUTE)
	NAME(STL_MUTEDVOTE)
	NAME(STL_MUTEDCHAT)
	NAME(STL_FLOODPROTACTIVE)
	NAME(STL_FLOODPROTTIME)

	NAME(STL_BUFFERPROTECTION)

	NAME(STL_FIRSTGREETING)
	NAME(STL_SHORTGREETING)
	NAME(STL_BIGGREETING)

	NAME(STL_POSSIBLEMODELCHEAT)
	NAME(STL_MAPCHEAT)
	NAME(STL_INVALIDTRACKCLIENT)
	NAME(STL_BADNAME)
	NAME(STL_CLIENTNAMECHANGE)
	NAME(STL_SERVERPAUSED)
	NAME(STL_UPLOADDENIED)
	NAME(STL_NAMEDCLIENTDOESNTEXIST)
	NAME(STL_NOSUISIDEWHENDEAD)
	NAME(STL_CANTPAUSE)
	NAME(STL_CANTPAUSESPEC)
	NAME(STL_CLIENTPAUSED)
	NAME(STL_CLIENTUNPAUSED)
	NAME(STL_CLIENTLESSUNPAUSE)	
	NAME(STL_CURRENTRATE)
	NAME(STL_RATESETTO)
	NAME(STL_CURRENTMSGLEVEL)
	NAME(STL_MSGLEVELSET)
	NAME(STL_GAMESAVED)

	NAME(STL_CLIENTDROPPED)
	NAME(STL_SNAPREFUSED)
	NAME(STL_FINALVOTE)
	NAME(STL_VOTE)

	NAME(STL_SPEEDCHEATKICKED)
	NAME(STL_SPEEDCHEATPOSSIBLE)

	NAME(STL_INITED)
	NAME(STL_BACKBUFSET)
	NAME(STL_MESSAGEOVERFLOW)


	
	NAME(STL_BUILDINGPHS)
	NAME(STL_PHSINFO)

	NAME(STL_BREAKSTATEMENT)
	NAME(STL_BADSPRINT)
	NAME(STL_NOPRECACHE)
	NAME(STL_CANTFREEWORLD)
	NAME(STL_CANTFREEPLAYERS)
	NAME(STL_COMPILEROVER)
	NAME(STL_EDICTWASFREE)
	NAME(STL_NOFREEEDICTS)

	NAME(STL_NEEDCHEATPARM)
	NAME(STL_USERDOESNTEXIST)

	NAME(STL_MAPCOMMANDUSAGE)

	NAME(STL_NOVOTING)
	NAME(STL_BADVOTE)
	NAME(STL_VOTESREMOVED)
	NAME(STL_OLDVOTEREMOVED)

	
	NAME(TL_EXECING)
	NAME(TL_EXECCOMMANDUSAGE)
	NAME(TL_EXECFAILED)
	NAME(TL_FUNCOVERFLOW)

	NAME(TL_CURRENTALIASCOMMANDS)
	NAME(TL_ALIASNAMETOOLONG)
	NAME(TL_ALIASRESTRICTIONLEVELERROR)
	NAME(TL_ALIASLEVELCOMMANDUSAGE)
	NAME(TL_ALIASNOTFOUND)
	NAME(TL_ALIASRAISELEVELERROR)
	NAME(TL_ALIASRESTRICTIONLEVELWARN)
	NAME(TL_ALIASRESTRICTLEVEL)

	NAME(TL_ALIASLIST)
	NAME(TL_COMMANDLISTHEADER)
	NAME(TL_CVARLISTHEADER)

	NAME(TL_RESTRICTCOMMANDRAISE)
	NAME(TL_RESTRICTCOMMANDTOOHIGH)
	NAME(TL_RESTRICTCURRENTLEVEL)
	NAME(TL_RESTRICTCURRENTLEVELDEFAULT)
	NAME(TL_RESTRICTNOTDEFINED)
	NAME(TL_WASRESTIRCTED)
	NAME(TL_COMMANDNOTDEFINED)

	NAME(TL_IFSYNTAX)
	NAME(TL_IFSYNTAXERROR)

	NAME(TL_SETSYNTAX)

	NAME(TL_CANTXNOTCONNECTED)



	NAME(TL_SHAREWAREVERSION)
	NAME(TL_REGISTEREDVERSION)

	NAME(TL_CURRENTSEARCHPATH)
	NAME(TL_SERACHPATHISPACK)
	NAME(TL_SERACHPATHISZIP)

	NAME(TL_COMPRESSEDFILEOPENFAILED)
	NAME(TL_ADDEDPACKFILE)
	NAME(TL_COULDNTOPENZIP)

	NAME(TL_ADDEDZIPFILE)
	NAME(TL_GAMEDIRAINTPATH)
	NAME(TL_KEYHASSLASH)
	NAME(TL_KEYHASQUOTE)
	NAME(TL_KEYTOOLONG)
	NAME(TL_INFOSTRINGTOOLONG)
	NAME(TL_STARKEYPROTECTED)
	NAME(TL_KEYHASNOVALUE)


	NAME(TL_OVERSIZEPACKETFROM)
	NAME(TL_CONNECTIONLOSTORABORTED)
	NAME(TL_NETGETPACKETERROR)
	NAME(TL_NETSENDERROR)
	NAME(TL_NETBINDINTERFACE)
	NAME(TL_IPADDRESSIS)
	NAME(TL_UDPINITED)
	NAME(TL_SERVERPORTINITED)
	NAME(TL_CLIENTPORTINITED)

	NAME(TL_OUTMESSAGEOVERFLOW)
	NAME(TL_OUTOFORDERPACKET)
	NAME(TL_DROPPEDPACKETCOUNT)

	NAME(STL_SERVERUNSPAWNED)
	NAME(STL_SERVERSPAWNED)

	NAME(TL_EXEDATETIME)
	NAME(TL_HEAPSIZE)
#ifdef	VERSION3PART
	NAME(TL_VERSION3)
	NAME(TL_SERVERVERSION3)
#else
	NAME(TL_VERSION2)
	NAME(TL_SERVERVERSION2)
#endif

//savegame.c
	NAME(STL_SAVESYNTAX)
	NAME(STL_NORELATIVEPATHS)
	NAME(STL_SAVEGAMETO)
	NAME(STL_ERRORCOULDNTOPEN)
	NAME(STL_SAVEDONE)
	NAME(STL_LOADSYNTAX)
	NAME(STL_LOADGAMEFROM)
	NAME(STL_BADSAVEVERSION)
	NAME(STL_LOADFAILED)

//sv_ccmds.c
	NAME(STL_NOMASTERMODE)
	NAME(STL_MASTERAT)
	NAME(STL_SENDINGPING)
	NAME(STL_SHUTTINGDOWN)
	NAME(STL_LOGGINGOFF)
	NAME(STL_LOGGINGTO)
	NAME(STL_FLOGGINGOFF)
	NAME(STL_FLOGGINGFAILED)
	NAME(STL_FLOGGINGTO)
	NAME(STL_USERIDNOTONSERVER)
	NAME(STL_CANTFINDMAP)
	NAME(STL_SERVERINFOSETTINGS)
	NAME(STL_SERVERINFOSYNTAX)
	NAME(STL_LOCALINFOSETTINGS)
	NAME(STL_LOCALINFOSYNTAX)
	NAME(STL_USERINFOSYNTAX)
	NAME(STL_FLOODPROTSETTINGS)
	NAME(STL_FLOODPROTNOTON)
	NAME(STL_FLOODPROTSYNTAX)
	NAME(STL_NONEGATIVEVALUES)
	NAME(STL_TRACK10PLUSSMESSAGES)
	NAME(STL_FLOODPROTCURRENTMESSAGE)
	NAME(STL_FLOODPROTMESSAGESYNTAX)
	NAME(STL_CURRENTGAMEDIR)
	NAME(STL_SVGAMEDIRUSAGE)
	NAME(STL_GAMEDIRCANTBEPATH)
	NAME(STL_GAMEDIRUSAGE)
	NAME(STL_SNAPTOOMANYFILES)
	NAME(STL_SNAPREQUEST)
	NAME(STL_SNAPUSAGE)


	NAME(TLC_VERSIONST3)
	NAME(TLC_VERSIONST2)
	NAME(TLC_VERSION2)
	NAME(TLC_BADSERVERADDRESS)
	NAME(TLC_ILLEGALSERVERADDRESS)
	NAME(TLC_CONNECTINGTO)
	NAME(TLC_SYNTAX_CONNECT)
	NAME(TLC_NORCONPASSWORD)
	NAME(TLC_NORCONDEST)
	NAME(TLC_SYNTAX_USER)
	NAME(TLC_USER_NOUSER)
	NAME(TLC_USERBANNER)
	NAME(TLC_USERBANNER2)
	NAME(TLC_USERLINE)
	NAME(TLC_USERTOTAL)
	NAME(TLC_COLOURCURRENT)
	NAME(TLC_SYNTAX_COLOUR)
	NAME(TLC_SYNTAX_FULLSERVERINFO)
	NAME(TLC_SERVER_VERSION)
	NAME(TLC_SYNTAX_FULLINFO)
	NAME(TLC_SYNTAX_SETINFO)
	NAME(TLC_PACKET_SYNTAX)
	NAME(TLC_BADADDRESS)
	NAME(TLC_CHANGINGMAP)
	NAME(TLC_RECONNECTING)
	NAME(TLC_RECONNECT_NOSERVER)
	NAME(TL_ST_COLON)
	NAME(TLC_GOTCONNECTION)
	NAME(TLC_DUPCONNECTION)
	NAME(TLC_CONNECTED)
	NAME(TLC_CONLESS_CONCMD)
	NAME(TLC_CMDFROMREMOTE)
	NAME(TL_LINEBREAK_EQUALS)
	NAME(TLC_LOCALID_NOTSET)
	NAME(TLC_LOCALID_BAD)
	NAME(TLC_A2C_PRINT)
	NAME(TLC_A2A_PING)
	NAME(TLC_S2C_CHALLENGE)
	NAME(TLC_CONLESSPACKET_UNKNOWN)
	NAME(TL_RUNTPACKET)
	NAME(TLC_SERVERTIMEOUT)
	NAME(TLC_CONNECTFIRST)
	NAME(TLC_SYNTAX_DOWNLOAD)
	NAME(TLC_REQUIRESSERVERMOD)
	NAME(TLC_CLIENTCON_ERROR_ENDGAME)
	NAME(TLC_HOSTFATALERROR)
	NAME(TLC_CONFIGCFG_WRITEFAILED)
	NAME(TLC_HOSTSPEEDSOUTPUT)
	NAME(TLC_QUAKEWORLD_INITED)
	NAME(TLC_DEDICATEDCANNOTCONNECT)
	NAME(TLC_Q2CONLESSPACKET_UNKNOWN)

	NAME(TL_NORELATIVEPATHS)
	NAME(TL_NODOWNLOADINDEMO)
	NAME(TL_DOWNLOADINGFILE)
	NAME(TLC_CHECKINGMODELS)
	NAME(TLC_CHECKINGSOUNDS)
	NAME(TL_FILENOTFOUND)
	NAME(TL_CLS_DOWNLOAD_ISSET)
	NAME(TL_FAILEDTOOPEN)
	NAME(TL_RENAMEFAILED)
	NAME(TL_UPLOADCOMPLEATE)
	NAME(TL_FTEEXTENSIONS)
	NAME(TLC_LINEBREAK_NEWLEVEL)
	NAME(TLC_PC_PS_NL)
	NAME(TLC_NOQ2CINEMATICSSUPPORT)
	NAME(TLC_GOTSVDATAPACKET)
	NAME(TLC_BAD_MAXCLIENTS)
	NAME(TLC_TOOMANYMODELPRECACHES)
	NAME(TLC_TOOMANYSOUNDPRECACHES)
	NAME(TLC_PARSESTATICWITHNOMAP)
	NAME(TL_FILE_X_MISSING)
	NAME(TL_GETACLIENTPACK)
	NAME(TLC_LINEBREAK_MINUS)
	NAME(TL_CSPECIALPRINT)
	NAME(TL_INT_SPACE)

#else

#define TRANSLATE_H

typedef enum {
#define NAME(s) s,
#include "translate.h"
#undef NAME
	STL_MAXSTL
} translation_t;

#define MAX_LANGUAGES 64

void TranslateInit(void);

extern char *languagetext[STL_MAXSTL][MAX_LANGUAGES];

void SV_InitLanguages(void);

#define langtext(t,l) languagetext[t][l]

#ifdef	VERSION3PART
#define TL_VERSION TL_VERSION3
#define TL_SERVERVERSION TL_SERVERVERSION3
#else
#define TL_VERSION TL_VERSION2
#define TL_SERVERVERSION TL_SERVERVERSION2
#endif

#define LANGDEFAULT 1





#endif
