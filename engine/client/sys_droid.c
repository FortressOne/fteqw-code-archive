#include <jni.h>
#include <errno.h>

#include <android/log.h>

#include "quakedef.h"
#include <unistd.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pthread.h>
#include "glquake.h"

#ifndef ANDROID
#error ANDROID wasnt defined
#endif

#if 0
//FIXME: remove the nativeactivity shit. android's standard NativeActivity class is buggy and basically fucked.
#include <android/keycodes.h>
#include <android/native_window_jni.h>
// ANativeWindow_fromSurface((jobject)getSurfaceHolder().getSurface())
#else
//NOTE: This is apache 2.0, which means GPL3.0+ ONLY, no gpl2.
#include <../../../../../sources/android/native_app_glue/android_native_app_glue.h>	//Fucking frameworks suck big hairy donkey balls.
JNIEXPORT void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize);
#include <../../../../../sources/android/native_app_glue/android_native_app_glue.c>	//Fucking frameworks suck big hairy donkey balls.
#endif

#ifndef isDedicated
#ifdef SERVERONLY
qboolean isDedicated = true;
#else
qboolean isDedicated = false;
#endif
#endif
extern int r_blockvidrestart;
float sys_dpi_x, sys_dpi_y;
static void *sys_memheap;
//static unsigned int vibrateduration;
static char sys_basedir[MAX_OSPATH];
static char sys_basepak[MAX_OSPATH];
extern  jmp_buf 	host_abort;
extern qboolean r_forceheadless;
static qboolean r_forcevidrestart;
ANativeWindow *sys_nativewindow;
static struct android_app *android_app_state; //basically used only for errors.

//cvar_t sys_vibrate = CVARFD("sys_vibrate", "1", CVAR_ARCHIVE, "Enables the system vibrator for damage events and such things. The value provided is a duration scaler.");
cvar_t sys_osk = CVAR("sys_osk", "0");	//to be toggled
cvar_t sys_keepscreenon = CVARFD("sys_keepscreenon", "1", CVAR_ARCHIVE, "If set, the screen will never darken. This might cost some extra battery power, but then so will running a 3d engine.");	//to be toggled
cvar_t sys_orientation = CVARFD("sys_orientation", "landscape", CVAR_ARCHIVE, "Specifies what angle to render quake at.\nValid values are: sensor (autodetect), landscape, portrait, reverselandscape, reverseportrait");
extern cvar_t vid_conautoscale;
void VID_Register(void);

#undef LOGI
#undef LOGW
#undef LOGE
#ifndef LOGI
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, DISTRIBUTION"Droid", __VA_ARGS__))
#endif
#ifndef LOGW
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, DISTRIBUTION"Droid", __VA_ARGS__))
#endif
#ifndef LOGE
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, DISTRIBUTION"Droid", __VA_ARGS__))
#endif

void INS_Move(void)
{
}
void INS_Commands(void)
{
}
void INS_EnumerateDevices(void *ctx, void(*callback)(void *ctx, const char *type, const char *devicename, unsigned int *qdevid))
{
}
void INS_Init(void)
{
}
void INS_ReInit(void)
{
}
void INS_Shutdown(void)
{
}
void Sys_Vibrate(float count)
{
//	if (count < 0)
//		count = 0;
//	vibrateduration += count*10*sys_vibrate.value;
}

static int mapkey(int androidkey)
{
	switch(androidkey)
	{
//	case AKEYCODE_SOFT_LEFT: return K_;
//	case AKEYCODE_SOFT_RIGHT: return K_;
//	case AKEYCODE_HOME: return K_;
//	case AKEYCODE_BACK: return K_;
//	case AKEYCODE_CALL: return K_;
//	case AKEYCODE_ENDCALL: return K_;
	case AKEYCODE_0: return '0';
	case AKEYCODE_1: return '1';
	case AKEYCODE_2: return '2';
	case AKEYCODE_3: return '3';
	case AKEYCODE_4: return '4';
	case AKEYCODE_5: return '5';
	case AKEYCODE_6: return '6';
	case AKEYCODE_7: return '7';
	case AKEYCODE_8: return '8';
	case AKEYCODE_9: return '9';
//	case AKEYCODE_STAR: return K_;
//	case AKEYCODE_POUND: return K_;	//americans don't know what a pound symbol looks like.
	case AKEYCODE_DPAD_UP: return K_GP_DPAD_UP;
	case AKEYCODE_DPAD_DOWN: return K_GP_DPAD_DOWN;
	case AKEYCODE_DPAD_LEFT: return K_GP_DPAD_LEFT;
	case AKEYCODE_DPAD_RIGHT: return K_GP_DPAD_RIGHT;
	case AKEYCODE_DPAD_CENTER: return K_ENTER;
	case AKEYCODE_VOLUME_UP: return K_VOLUP;
	case AKEYCODE_VOLUME_DOWN: return K_VOLDOWN;
	case AKEYCODE_POWER: return K_POWER;
//	case AKEYCODE_CAMERA: return K_CAMERA;
//	case AKEYCODE_CLEAR: return K_;
	case AKEYCODE_A: return 'a';
	case AKEYCODE_B: return 'b';
	case AKEYCODE_C: return 'c';
	case AKEYCODE_D: return 'd';
	case AKEYCODE_E: return 'e';
	case AKEYCODE_F: return 'f';
	case AKEYCODE_G: return 'g';
	case AKEYCODE_H: return 'h';
	case AKEYCODE_I: return 'i';
	case AKEYCODE_J: return 'j';
	case AKEYCODE_K: return 'k';
	case AKEYCODE_L: return 'l';
	case AKEYCODE_M: return 'm';
	case AKEYCODE_N: return 'n';
	case AKEYCODE_O: return 'o';
	case AKEYCODE_P: return 'p';
	case AKEYCODE_Q: return 'q';
	case AKEYCODE_R: return 'r';
	case AKEYCODE_S: return 's';
	case AKEYCODE_T: return 't';
	case AKEYCODE_U: return 'u';
	case AKEYCODE_V: return 'v';
	case AKEYCODE_W: return 'w';
	case AKEYCODE_X: return 'x';
	case AKEYCODE_Y: return 'y';
	case AKEYCODE_Z: return 'z';
	case AKEYCODE_COMMA: return ',';
	case AKEYCODE_PERIOD: return '.';
	case AKEYCODE_ALT_LEFT: return K_LALT;
	case AKEYCODE_ALT_RIGHT: return K_RALT;
	case AKEYCODE_SHIFT_LEFT: return K_LSHIFT;
	case AKEYCODE_SHIFT_RIGHT: return K_RSHIFT;
	case AKEYCODE_TAB : return K_TAB;
	case AKEYCODE_SPACE: return K_SPACE;
//	case AKEYCODE_SYM: return K_;
//	case AKEYCODE_EXPLORER : return K_;
//	case AKEYCODE_ENVELOPE: return K_;
	case AKEYCODE_ENTER: return K_ENTER;
	case AKEYCODE_DEL: return K_BACKSPACE;
	case AKEYCODE_GRAVE: return '`';
	case AKEYCODE_MINUS: return '-';
	case AKEYCODE_EQUALS: return '=';
	case AKEYCODE_LEFT_BRACKET: return '[';
	case AKEYCODE_RIGHT_BRACKET: return ']';
	case AKEYCODE_BACKSLASH: return '#';	//this kinda sums up keymaps like this.
	case AKEYCODE_SEMICOLON: return ';';
	case AKEYCODE_APOSTROPHE: return '\'';
	case AKEYCODE_SLASH: return '/';
//	case AKEYCODE_AT: return K_;
//	case AKEYCODE_NUM: return K_;
//	case AKEYCODE_HEADSETHOOK: return K_;
//	case AKEYCODE_FOCUS: return K_;
//	case AKEYCODE_PLUS: return K_;
	case AKEYCODE_MENU: return K_APP;
//	case AKEYCODE_NOTIFICATION: return K_;
	case AKEYCODE_SEARCH: return K_SEARCH;
//	case AKEYCODE_MEDIA_PLAY_PAUSE: return K_;
//	case AKEYCODE_MEDIA_STOP: return K_;
//	case AKEYCODE_MEDIA_NEXT: return K_;
//	case AKEYCODE_MEDIA_PREVIOUS: return K_;
//	case AKEYCODE_MEDIA_REWIND: return K_;
//	case AKEYCODE_MEDIA_FAST_FORWARD: return K_;
//	case AKEYCODE_MUTE: return K_;
	case AKEYCODE_PAGE_UP: return K_PGUP;
	case AKEYCODE_PAGE_DOWN: return K_PGDN;
//	case AKEYCODE_PICTSYMBOLS: return K_;
//	case AKEYCODE_SWITCH_CHARSET: return K_;
	case AKEYCODE_BUTTON_A: return K_GP_A;
	case AKEYCODE_BUTTON_B: return K_GP_B;
//	case AKEYCODE_BUTTON_C: return K_GP_C;
	case AKEYCODE_BUTTON_X: return K_GP_X;
	case AKEYCODE_BUTTON_Y: return K_GP_Y;
//	case AKEYCODE_BUTTON_Z: return K_GP_Z;
	case AKEYCODE_BUTTON_L1: return K_GP_LEFT_SHOULDER;
	case AKEYCODE_BUTTON_R1: return K_GP_RIGHT_SHOULDER;
	case AKEYCODE_BUTTON_L2: return K_GP_LEFT_TRIGGER;
	case AKEYCODE_BUTTON_R2: return K_GP_RIGHT_TRIGGER;
	case AKEYCODE_BUTTON_THUMBL: return K_GP_LEFT_THUMB;
	case AKEYCODE_BUTTON_THUMBR: return K_GP_RIGHT_THUMB;
	case AKEYCODE_BUTTON_START: return K_GP_START;
	case AKEYCODE_BUTTON_SELECT: return K_GP_BACK;
	case AKEYCODE_BUTTON_MODE: return K_GP_GUIDE;

//And this is the part where you start to see quite why I hate android so much
	case 111: return K_ESCAPE;
	case 112: return K_DEL;
	case 113: return K_LCTRL;
	case 114: return K_RCTRL;
	case 115: return K_CAPSLOCK;
	case 116: return K_SCRLCK;
	case 117: return K_LWIN;
	case 118: return K_RWIN;
//	case 119: return K_FUNCTION;
//	case 120: return K_SYSRQ;
	case 121: return K_PAUSE;
	case 122: return K_HOME;
	case 123: return K_END;
	case 124: return K_INS;
//	case 125: return K_FORWARD;
//	case 126: return K_MEDIA_PLAY;
//	case 127: return K_MEDIA_PAUSE;
//	case 128: return K_MEDIA_CLOSE;
//	case 129: return K_MEDIA_EJECT;
//	case 130: return K_MEDIA_RECORD;
	case 131: return K_F1;
	case 132: return K_F2;
	case 133: return K_F3;
	case 134: return K_F4;
	case 135: return K_F5;
	case 136: return K_F6;
	case 137: return K_F7;
	case 138: return K_F8;
	case 139: return K_F9;
	case 140: return K_F10;
	case 141: return K_F11;
	case 142: return K_F12;
	case 143: return K_KP_NUMLOCK;
	case 144: return K_KP_INS;
	case 145: return K_KP_END;
	case 146: return K_KP_DOWNARROW;
	case 147: return K_KP_PGDN;
	case 148: return K_KP_LEFTARROW;
	case 149: return K_KP_5;
	case 150: return K_KP_RIGHTARROW;
	case 151: return K_KP_HOME;
	case 152: return K_KP_UPARROW;
	case 153: return K_KP_PGUP;
	case 154: return K_KP_SLASH;
	case 155: return K_KP_STAR;
	case 156: return K_KP_MINUS;
	case 157: return K_KP_PLUS;
	case 158: return K_KP_DEL;
	case 160: return K_KP_ENTER;

	default:
		Con_DPrintf("Android keycode %i is not supported\n", androidkey);
	}
	return 0;
}

static int32_t engine_handle_input(struct android_app *app, AInputEvent *event)
{
	switch(AInputEvent_getType(event))
	{
	case AINPUT_EVENT_TYPE_MOTION:
	case AINPUT_EVENT_TYPE_KEY:
		return 0;	//we handle these in the java code, so shouldn't ever see them.
	}
	return 0; //no idea what sort of event it is.
}
static void engine_handle_cmd(struct android_app *app, int32_t cmd)
{
	switch(cmd)
	{
	case APP_CMD_SAVE_STATE:
		//FIXME: implement save-game-to-memory...
		break;
	case APP_CMD_INIT_WINDOW:
		if (sys_nativewindow != app->window)
		{
			sys_nativewindow = app->window;	
			r_forceheadless = (sys_nativewindow==NULL);

			r_forcevidrestart = true;
		}
		break;
	case APP_CMD_TERM_WINDOW:
		r_forceheadless = true;
		if (qrenderer && !r_forcevidrestart && sys_nativewindow)
			R_RestartRenderer_f();
		sys_nativewindow = NULL;
		break;
	case APP_CMD_GAINED_FOCUS:
		vid.activeapp = true;
		break;
	case APP_CMD_LOST_FOCUS:
		vid.activeapp = false;
		break;
	}
}

static void run_intent_url(struct android_app *app)
{
	jobject act = app->activity->clazz;
	JNIEnv *jni;
	if (JNI_OK == (*app->activity->vm)->AttachCurrentThread(app->activity->vm, &jni, NULL))
	{
		jobject intent = (*jni)->CallObjectMethod(jni, act, (*jni)->GetMethodID(jni, (*jni)->GetObjectClass(jni, act), "getIntent", "()Landroid/content/Intent;"));
		if (intent)
		{
			jstring data = (*jni)->CallObjectMethod(jni, intent, (*jni)->GetMethodID(jni, (*jni)->GetObjectClass(jni, intent), "getDataString", "()Ljava/lang/String;"));
			if (data)
			{
				const char *url = (*jni)->GetStringUTFChars(jni, data, NULL);
				if (url)
				{
					if (!strncmp(url, "content:", 8))
					{
						/*Java:
						Cursor cursor = this.getContentResolver().query(data, null, null, null, null);
						cursor.moveToFirst();   
						String myloc = cursor.getString(0);
						cursor.close();
						*/
					}
					else
						Host_RunFile(url, strlen(url), NULL);
					(*jni)->ReleaseStringUTFChars(jni, data, url);
				}
			}
		}
		//FIXME: do we need to release methodids/objects?
		(*app->activity->vm)->DetachCurrentThread(app->activity->vm);
	}
}

static qboolean read_apk_path(struct android_app *app, char *out, size_t outsize)
{
	qboolean res = false;
	jobject act = app->activity->clazz;
	JNIEnv *jni;
	if (JNI_OK == (*app->activity->vm)->AttachCurrentThread(app->activity->vm, &jni, NULL))
	{
		jstring result = (*jni)->CallObjectMethod(jni, act, (*jni)->GetMethodID(jni, (*jni)->GetObjectClass(jni, act), "getPackageCodePath", "()Ljava/lang/String;"));
		const char *tmp = (*jni)->GetStringUTFChars(jni, result, NULL);
		if (tmp)
		{
			res = true;
			Q_strncpyz(out, tmp, outsize);
			(*jni)->ReleaseStringUTFChars(jni, result, tmp);
		}

		//FIXME: do we need to release methodids/objects?
		(*app->activity->vm)->DetachCurrentThread(app->activity->vm);
	}

	return res;
}

static void setsoftkeyboard(struct android_app *app, int flags)
{	//the NDK is unusably buggy when it comes to keyboards, so call into java.
	jobject act = app->activity->clazz;
	JNIEnv *jni;
	if (JNI_OK == (*app->activity->vm)->AttachCurrentThread(app->activity->vm, &jni, NULL))
	{
		jmethodID func = (*jni)->GetMethodID(jni, (*jni)->GetObjectClass(jni, act), "showKeyboard", "(I)V" );
		if (func)
			(*jni)->CallVoidMethod(jni, act, func, flags);

		(*app->activity->vm)->DetachCurrentThread(app->activity->vm);
	}
}
static void showMessageAndQuit(struct android_app *app, const char *errormsg)
{	//no nice way to do this from native.
	jobject act = app->activity->clazz;
	JNIEnv *jni;
	if (JNI_OK == (*app->activity->vm)->AttachCurrentThread(app->activity->vm, &jni, NULL))
	{
		jmethodID func = (*jni)->GetMethodID(jni, (*jni)->GetObjectClass(jni, act), "showMessageAndQuit", "(Ljava/lang/String;)V" );
		if (func)
			(*jni)->CallVoidMethod(jni, act, func, (*jni)->NewStringUTF(jni, errormsg));
		(*app->activity->vm)->DetachCurrentThread(app->activity->vm);
	}
}
static void updateOrientation(struct android_app *app, const char *neworientation)
{	//no nice way to do this from native.
	jobject act = app->activity->clazz;
	JNIEnv *jni;
	if (JNI_OK == (*app->activity->vm)->AttachCurrentThread(app->activity->vm, &jni, NULL))
	{
		jmethodID func = (*jni)->GetMethodID(jni, (*jni)->GetObjectClass(jni, act), "updateOrientation", "(Ljava/lang/String;)V" );
		if (func)
			(*jni)->CallVoidMethod(jni, act, func, (*jni)->NewStringUTF(jni, neworientation));
		(*app->activity->vm)->DetachCurrentThread(app->activity->vm);
	}
}
static void updateScreenKeepOn(struct android_app *app, jboolean keepon)
{	//the NDK is unusably buggy when it comes to keyboards, so call into java.
	jobject act = app->activity->clazz;
	JNIEnv *jni;
	if (JNI_OK == (*app->activity->vm)->AttachCurrentThread(app->activity->vm, &jni, NULL))
	{
		jmethodID func = (*jni)->GetMethodID(jni, (*jni)->GetObjectClass(jni, act), "updateScreenKeepOn", "(Z)V" );
		if (func)
			(*jni)->CallVoidMethod(jni, act, func, keepon);

		(*app->activity->vm)->DetachCurrentThread(app->activity->vm);
	}
}

static void setCursorVisibility(struct android_app *app, jboolean visible)
{	//this is meant to use the nvidia-added setCursorVisibility function
	//but its fatal if it doesn't exist, and it doesn't seem to exist.
#if 0
	jobject act = app->activity->clazz;
	JNIEnv *jni;
	if (JNI_OK == (*app->activity->vm)->AttachCurrentThread(app->activity->vm, &jni, NULL))
	{
		jobject inputManager = NULL;
		jmethodID setvis = NULL;
		jmethodID func = (*jni)->GetMethodID(jni, (*jni)->GetObjectClass(jni, act), "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;" );
		if (func)
			inputManager = (*jni)->CallObjectMethod(jni, act, func, (*jni)->NewStringUTF(jni, "input"));
		if (inputManager)
			setvis = (*jni)->GetMethodID(jni, (*jni)->GetObjectClass(jni, inputManager), "setCursorVisibility", "(Z)V" );
		if (setvis)
			(*jni)->CallVoidMethod(jni, inputManager, setvis, visible);

		(*app->activity->vm)->DetachCurrentThread(app->activity->vm);
	}
#endif
}

static void FTENativeActivity_keypress(JNIEnv *env, jobject this, jint devid, jboolean down, jint keycode, jint unicode)
{
	int qkeycode = mapkey(keycode);
//	Sys_Printf("FTENativeActivity_keypress: d=%i s=%i a=%i,q=%i u=%i\n", devid, down, keycode, qkeycode, unicode);
	IN_KeyEvent(devid, down, qkeycode, unicode);
}
static jboolean FTENativeActivity_wantrelative(JNIEnv *env, jobject this)
{
	if (!in_windowed_mouse.ival)	//emulators etc have no grabs so we're effectively always windowed in such situations.
		return false;
	return !Key_MouseShouldBeFree();
}
static void FTENativeActivity_mousepress(JNIEnv *env, jobject this, jint devid, jint buttonbits)
{
	static int heldbuttons;
	jint changed = buttonbits^heldbuttons;
//	Sys_Printf("FTENativeActivity_mousepress: d=%i bits=%x (changed=%x)\n", devid, buttonbits, changed);
	static int qbutton[] = {
		K_MOUSE1,	//primary
		K_MOUSE2,	//secondary
		K_MOUSE3,	//tertiary
		K_MOUSE4,	//back
		K_MOUSE5,	//forward
		K_MOUSE1,	//stylus_primary
		K_MOUSE2,	//stylus_secondary
	};
	size_t i;
	heldbuttons = buttonbits;
	if (changed)
	for (i = 0; i < countof(qbutton); i++)
	{
		if (changed&(1<<i))
			IN_KeyEvent(devid, buttonbits&(1<<i), qbutton[i], 0);
	}
}
static void FTENativeActivity_motion(JNIEnv *env, jobject this, jint ptrid, jint act, jfloat x, jfloat y, jfloat z, jfloat size)
{
//	Sys_Printf("FTENativeActivity_motion: d=%i a=%i x=%f y=%f z=%f s=%f\n", ptrid, act, x, y, z, size);
	switch(act)
	{
	case 2:	//mouse down
	case 3:	//mouse up
		IN_KeyEvent(ptrid, act==2, K_MOUSE1, 0);
		break;
	case 1:	//relative motion
	case 0: //absolute motion (android sucks)
		IN_MouseMove(ptrid, act==0, x, y, z, size);
		break;
	};
}
static void FTENativeActivity_axis(JNIEnv *env, jobject this, jint devid, jint axis, jfloat value)
{
	IN_JoystickAxisEvent(devid, axis, value);
}
//static void FTENativeActivity_accelerometer(JNIEnv *env, jobject obj, jint devid, jfloat x, jfloat y, jfloat z)
//{
//	IN_Accelerometer(devid, x, y, z);
//}
//static void FTENativeActivity_gryoscope(JNIEnv *env, jobject obj, jint devid, jfloat pitch, jfloat yaw, jfloat roll)
//{
//	IN_Gyroscope(devid, pitch, yaw, roll);
//}
static JNINativeMethod methods[] = {
	{"keypress",		"(IZII)V", 		FTENativeActivity_keypress},
	{"mousepress",		"(II)V", 		FTENativeActivity_mousepress},
	{"motion",			"(IIFFFF)V", 	FTENativeActivity_motion},
	{"wantrelative",	"()Z", 			FTENativeActivity_wantrelative},	//so the java code knows if it should use (often buggy) relative mouse movement or (limited) abs cursor coords.
	{"axis",			"(IIF)V", 		FTENativeActivity_axis},
//	{"accelerometer",	"(IFFF)V",		FTENativeActivity_accelerometer},
//	{"gyroscope",		"(IFFF)V",		FTENativeActivity_gyroscope},
};
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
	JNIEnv *jni;
	if (JNI_OK == (*vm)->GetEnv(vm, (void**)&jni, JNI_VERSION_1_2))
	{
		jclass naclass = (*jni)->FindClass(jni, "com.fteqw.FTENativeActivity");
		if (naclass)
		{
			(*jni)->RegisterNatives(jni, naclass, methods, countof(methods));
			return JNI_VERSION_1_2;
		}
	}
	return -1;
}

void android_main(struct android_app *state)
{
	static pthread_mutex_t onemainthread = PTHREAD_MUTEX_INITIALIZER;	//android likes spawning multiple 'main' threads
	int osk = 0, wantgrabs = 0, t;
	double ltime,ctime,tdelta;
	pthread_mutex_lock(&onemainthread);
	android_app_state = state;
	state->userData = NULL;
	state->onAppCmd = engine_handle_cmd;
	state->onInputEvent = engine_handle_input;
	r_forceheadless = true;
	sys_nativewindow = NULL;

	if (!host_initialized)
	{
		static const char *args [] =
		{
			"ftedroid",	/*binary name, not really meaningful*/
			"-basepack",
			sys_basepak,	/*filled in later*/
			"",
			""
		};
		static quakeparms_t parms;
		if (sys_memheap)
			free(sys_memheap);
		memset(&parms, 0, sizeof(parms));
		parms.basedir = sys_basedir;	/*filled in later*/
		parms.argc = read_apk_path(state, sys_basepak, sizeof(sys_basepak))?3:1;
		parms.argv = args;
#ifdef CONFIG_MANIFEST_TEXT
		parms.manifest = CONFIG_MANIFEST_TEXT;
#endif
		sys_dpi_x = 72;	//no idea
		sys_dpi_y = 72;	//no idea

#if 0	//google made this a fucking pain. 
		Q_strncpyz(sys_basedir, getenv("EXTERNAL_STORAGE"), sizeof(sys_basedir));
		Q_strncatz(sys_basedir, "/fte", sizeof(sys_basedir));
#else	//so now users have to use some big long path to install stuff instead
		Q_strncatz(sys_basedir, state->activity->externalDataPath, sizeof(sys_basedir));
#endif

		Sys_Printf("Starting up (apk=%s, usr=%s)\n", sys_basepak, parms.basedir);

		VID_Register();
		COM_InitArgv(parms.argc, parms.argv);
		TL_InitLanguages(sys_basedir);

		Host_Init(&parms);
		Sys_Printf("Host Inited\n");
	}
	else
		Sys_Printf("Restarting up!\n");
	ltime = Sys_DoubleTime();

	sys_orientation.modified = false;
	updateOrientation(state, sys_orientation.string);
	sys_keepscreenon.modified = false;
	updateScreenKeepOn(state, sys_keepscreenon.ival);

	run_intent_url(state);
	if (state->savedState != NULL)
	{	//oh look, we're pretending to already be running...
		//oh.
	}

	for(;;)
	{
		int ident, events;
		struct android_poll_source *source;
		while((ident=ALooper_pollAll(vid.activeapp?0:250, NULL, &events, (void**)&source)) >= 0)
		{
			if (source != NULL)
				source->process(state, source);

			//FIXME: sensor crap

			if (state->destroyRequested != 0)
			{
				Sys_Printf("Shutdown requested\n");
				Host_Shutdown ();
				
				pthread_mutex_unlock(&onemainthread);
				return;
			}
		}
		if (host_initialized)
		{
			if (r_forcevidrestart)
			{
				if (qrenderer)
					R_RestartRenderer_f();
				r_forcevidrestart = false;
			}
			if (sys_nativewindow)
			{
				ctime = Sys_DoubleTime();
				tdelta = ctime-ltime;
				ltime = ctime;
				Host_Frame(tdelta);
			}
		}


		t = 0;
		if (Key_Dest_Has(kdm_console|kdm_message))
			t |= ANATIVEACTIVITY_SHOW_SOFT_INPUT_IMPLICIT;
		if (!Key_Dest_Has(~kdm_game) && cls.state == ca_disconnected)
			t |= ANATIVEACTIVITY_SHOW_SOFT_INPUT_IMPLICIT;
		if (sys_osk.ival)
			t |= ANATIVEACTIVITY_SHOW_SOFT_INPUT_FORCED;
		if (osk != t)
		{
			setsoftkeyboard(state, t);
			osk = t;
		}
	
		if (sys_orientation.modified)
		{
			sys_orientation.modified = false;
			updateOrientation(state, sys_orientation.string);
		}
	
		if (sys_keepscreenon.modified)
		{
			sys_keepscreenon.modified = false;
			updateScreenKeepOn(state, sys_keepscreenon.ival);
		}

		t = FTENativeActivity_wantrelative(NULL,NULL);
		if (wantgrabs != t)
		{
			wantgrabs = t;
			setCursorVisibility(state, wantgrabs);
		}
	}
}

static int secbase;

#ifdef _POSIX_TIMERS
double Sys_DoubleTime(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);

	if (!secbase)
	{
		secbase = ts.tv_sec;
		return ts.tv_nsec/1000000000.0;
	}
	return (ts.tv_sec - secbase) + ts.tv_nsec/1000000000.0;
}
unsigned int Sys_Milliseconds(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);

	if (!secbase)
	{
		secbase = ts.tv_sec;
		return ts.tv_nsec/1000000;
	}
	return (ts.tv_sec - secbase)*1000 + ts.tv_nsec/1000000;
}
#else
double Sys_DoubleTime(void)
{
	struct timeval tp;
	struct timezone tzp;

	gettimeofday(&tp, &tzp);

	if (!secbase)
	{
			secbase = tp.tv_sec;
			return tp.tv_usec/1000000.0;
	}

	return (tp.tv_sec - secbase) + tp.tv_usec/1000000.0;
}
unsigned int Sys_Milliseconds(void)
{
	struct timeval tp;
	struct timezone tzp;

	gettimeofday(&tp, &tzp);

	if (!secbase)
	{
		secbase = tp.tv_sec;
		return tp.tv_usec/1000;
	}

	return (tp.tv_sec - secbase)*1000 + tp.tv_usec/1000;
}
#endif

void Sys_Shutdown(void)
{
	free(sys_memheap);
}
void Sys_Quit(void)
{
#ifndef SERVERONLY
	Host_Shutdown ();
#else
	SV_Shutdown();
#endif

	LOGI("%s", "quitting");
	showMessageAndQuit(android_app_state, "");

	longjmp(host_abort, 1);
	exit(0);
}
void Sys_Error (const char *error, ...)
{
	va_list         argptr;
	char             string[1024];

	va_start (argptr, error);
	vsnprintf (string,sizeof(string)-1, error,argptr);
	va_end (argptr);
	COM_WorkerAbort(string);
	if (!*string)
		strcpy(string, "no error");

	LOGE("e: %s", string);
	showMessageAndQuit(android_app_state, string);

	host_initialized = false;	//don't keep calling Host_Frame, because it'll screw stuff up more. Can't trust Host_Shutdown either. :(
	vid.activeapp = false;		//make sure we don't busyloop.
	longjmp(host_abort, 1);
	exit(1);
}
void Sys_Printf (char *fmt, ...)
{
	va_list         argptr;
	char *e;

	//android doesn't do \ns properly *sigh*
	//this means we have to buffer+split it ourselves.
	//and because of lots of threads, we have to mutex it too.
	static char linebuf[2048];
	static char *endbuf = linebuf;
	static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&lock);

	//append the new data
	va_start (argptr, fmt);
	vsnprintf (endbuf,sizeof(linebuf)-(endbuf-linebuf)-1, fmt,argptr);
	va_end (argptr);
	endbuf += strlen(endbuf);

	//split it on linebreaks
	while ((e = strchr(linebuf, '\n')))
	{
		*e = 0;
		LOGI("%s", linebuf);
		memmove(linebuf, e+1, endbuf-(e+1));
		linebuf[endbuf-(e+1)] = 0;
		endbuf -= (e+1)-linebuf;
	}

	pthread_mutex_unlock(&lock);
}
void Sys_Warn (char *fmt, ...)
{
	va_list         argptr;
	char             string[1024];

	va_start (argptr, fmt);
	vsnprintf (string,sizeof(string)-1, fmt,argptr);
	va_end (argptr);

	LOGW("w: %s", string);
}

void Sys_CloseLibrary(dllhandle_t *lib)
{
	if (lib)
		dlclose(lib);
}
void *Sys_GetAddressForName(dllhandle_t *module, const char *exportname)
{
	return dlsym(module, exportname);
}
dllhandle_t *Sys_LoadLibrary(const char *name, dllfunction_t *funcs)
{
	size_t i;
	dllhandle_t *h;
	h = dlopen(va("%s.so", name), RTLD_LAZY|RTLD_LOCAL);
	if (!h)
		h = dlopen(name, RTLD_LAZY|RTLD_LOCAL);

	if (h && funcs)
	{
		for (i = 0; funcs[i].name; i++)
		{
			*funcs[i].funcptr = dlsym(h, funcs[i].name);
			if (!*funcs[i].funcptr)
				break;
		}
		if (funcs[i].name)
		{
			Sys_CloseLibrary(h);
			h = NULL;
		}
	}
	return h;
}
char *Sys_ConsoleInput (void)
{
	return NULL;
}
void Sys_mkdir (const char *path)    //not all pre-unix systems have directories (including dos 1)
{
	mkdir(path, 0755);
}
qboolean Sys_rmdir (const char *path)
{
	if (rmdir (path) == 0)
		return true;
	if (errno == ENOENT)
		return true;
	return false;
}
qboolean Sys_remove (const char *path)
{
	return !unlink(path);
}
qboolean Sys_Rename (const char *oldfname, const char *newfname)
{
	return !rename(oldfname, newfname);
}
void Sys_SendKeyEvents(void)
{
}
void Sys_Init(void)
{
	Cvar_Register(&sys_keepscreenon, "android stuff");
	Cvar_Register(&sys_orientation, "android stuff");
	Cvar_Register(&sys_osk, "android stuff");
}

qboolean Sys_GetDesktopParameters(int *width, int *height, int *bpp, int *refreshrate)
{
	*width = 320;
	*height = 240;
	*bpp = 16;
	*refreshrate = 60;
	return false;
}
qboolean Sys_RandomBytes(qbyte *string, int len)
{
	qboolean res = false;
	int fd = open("/dev/urandom", 0);
	if (fd >= 0)
	{
		res = (read(fd, string, len) == len);
		close(fd);
	}

	return res;
}

void Sys_ServerActivity(void)
{
	/*FIXME: flash window*/
}

#ifdef WEBCLIENT
qboolean Sys_RunInstaller(void)
{       //not implemented
	return false;
}
#endif

#ifndef MULTITHREAD
void Sys_Sleep (double seconds)
{
	struct timespec ts;

	ts.tv_sec = (time_t)seconds;
	seconds -= ts.tv_sec;
	ts.tv_nsec = seconds * 1000000000.0;

	nanosleep(&ts, NULL);
}
#endif
qboolean Sys_InitTerminal(void)
{
	/*switching to dedicated mode, show text window*/
	return false;
}
void Sys_CloseTerminal(void)
{
}

#define SYS_CLIPBOARD_SIZE  256
static char clipboard_buffer[SYS_CLIPBOARD_SIZE] = {0};
void Sys_Clipboard_PasteText(clipboardtype_t cbt, void (*callback)(void *cb, char *utf8), void *ctx)
{
	callback(ctx, clipboard_buffer);
}
void Sys_SaveClipboard(clipboardtype_t cbt, const char *text)
{
 	Q_strncpyz(clipboard_buffer, text, SYS_CLIPBOARD_SIZE);
}

int Sys_EnumerateFiles (const char *gpath, const char *match, int (*func)(const char *, qofs_t, time_t mtime, void *, searchpathfuncs_t *), void *parm, searchpathfuncs_t *spath)
{
	DIR *dir;
	char apath[MAX_OSPATH];
	char file[MAX_OSPATH];
	char truepath[MAX_OSPATH];
	char *s;
	struct dirent *ent;
	struct stat st;

	//printf("path = %s\n", gpath);
	//printf("match = %s\n", match);

	if (!gpath)
		gpath = "";
	*apath = '\0';

	Q_strncpyz(apath, match, sizeof(apath));
	for (s = apath+strlen(apath)-1; s >= apath; s--)
	{
		if (*s == '/')
		{
			s[1] = '\0';
			match += s - apath+1;
			break;
		}
	}
	if (s < apath)  //didn't find a '/' 
		*apath = '\0'; 

	Q_snprintfz(truepath, sizeof(truepath), "%s/%s", gpath, apath); 


	//printf("truepath = %s\n", truepath); 
	//printf("gamepath = %s\n", gpath); 
	//printf("apppath = %s\n", apath); 
	//printf("match = %s\n", match); 
	dir = opendir(truepath); 
	if (!dir) 
	{ 
		Con_DPrintf("Failed to open dir %s\n", truepath); 
		return true; 
	} 
	do 
	{ 
		ent = readdir(dir); 
		if (!ent) 
			break; 
		if (*ent->d_name != '.') 
		{ 
			if (wildcmp(match, ent->d_name)) 
			{ 
				Q_snprintfz(file, sizeof(file), "%s/%s", truepath, ent->d_name); 

				if (stat(file, &st) == 0) 
				{ 
					Q_snprintfz(file, sizeof(file), "%s%s%s", apath, ent->d_name, S_ISDIR(st.st_mode)?"/":""); 

					if (!func(file, st.st_size, st.st_mtime, parm, spath)) 
					{ 
						closedir(dir); 
						return false; 
					} 
				} 
				else 
					printf("Stat failed for \"%s\"\n", file); 
			} 
		} 
	} while(1); 
	closedir(dir); 

	return true; 
}

