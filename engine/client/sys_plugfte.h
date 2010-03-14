#ifndef __QUAKEDEF_H__
typedef enum qboolean;
typedef void *vfsfile_t;
#endif


struct pipetype
{
	int dead;
};

struct browserfuncs
{
	qboolean (*RequestDownload)(void *ctx, struct pipetype *ftype, char *url);
};

/*the conext structure contains this at the start*/
struct contextpublic
{
	qboolean running;	/*set if the plugin context is actually active*/
	float availver;	/*this is the version of the plugin that is available, if current is better, use 0*/

#if defined(_WIN32) && defined(__QUAKEDEF_H__)
	/*the npapi stuff is lazy and uses this*/
	void *oldwnd;	/*not used in the plugin itself*/
	void *oldproc;	/*not used in the plugin itself*/
#endif
};

#include <windows.h>
static void VS_DebugLocation(char *fname, int line, char *fmt, ...)
{
	char buffer[640];
	va_list va;

	sprintf(buffer, "%s(%i) : ", fname, line);
	OutputDebugStringA(buffer);

	va_start(va, fmt);
	vsprintf(buffer, fmt, va);
	va_end(va);
	OutputDebugStringA(buffer);
	OutputDebugStringA("\n");
}









struct context;
struct pscript_property;

struct context *Plug_CreateContext(void *sysctx, const struct browserfuncs *funcs);
void Plug_DestroyContext(struct context *ctx);
void Plug_LockPlugin(struct context *ctx, qboolean lockstate);
qboolean Plug_StartContext(struct context *ctx);
void Plug_StopContext(struct context *ctx);
qboolean Plug_ChangeWindow(struct context *ctx, void *whnd, int width, int height);

struct pscript_property *Plug_FindProp(struct context *ctx, const char *field);
qboolean Plug_SetString(struct context *ctx, struct pscript_property *field, const char *value);
qboolean Plug_GetString(struct context *ctx, struct pscript_property *field, const char **value);
void Plug_GotString(const char *value);
qboolean Plug_SetInteger(struct context *ctx, struct pscript_property *field, int value);
qboolean Plug_GetInteger(struct context *ctx, struct pscript_property *field, int *value);
qboolean Plug_SetFloat(struct context *ctx, struct pscript_property *field, float value);
qboolean Plug_GetFloat(struct context *ctx, struct pscript_property *field, float *value);

#ifdef _WIN32
void *Plug_GetSplashBack(struct context *ctx, void *hdc, int *width, int *height);/*returns an HBITMAP*/
void Plug_ReleaseSplashBack(struct context *ctx, void *bmp);
#endif

struct plugfuncs
{
	struct context *(*CreateContext)(void *sysctx, const struct browserfuncs *funcs);
	void (*DestroyContext)(struct context *ctx);
	void (*LockPlugin)(struct context *ctx, qboolean lockstate);
	qboolean (*StartContext)(struct context *ctx);
	void (*StopContext)(struct context *ctx);
	qboolean (*ChangeWindow)(struct context *ctx, void *whnd, int width, int height);

	struct pscript_property *(*FindProp)(struct context *ctx, const char *field);
	qboolean (*SetString)(struct context *ctx, struct pscript_property *field, const char *value);
	qboolean (*GetString)(struct context *ctx, struct pscript_property *field, const char **value);
	void (*GotString)(const char *value);
	qboolean (*SetInteger)(struct context *ctx, struct pscript_property *field, int value);
	qboolean (*GetInteger)(struct context *ctx, struct pscript_property *field, int *value);
	qboolean (*SetFloat)(struct context *ctx, struct pscript_property *field, float value);
	qboolean (*GetFloat)(struct context *ctx, struct pscript_property *field, float *value);

#ifdef _WIN32
	void *(*GetSplashBack)(struct context *ctx, void *hdc, int *width, int *height);/*returns an HBITMAP*/
	void (*ReleaseSplashBack)(struct context *ctx, void *bmp);
#endif
};

#define PLUG_APIVER 1
const struct plugfuncs *Plug_GetFuncs(int ver);
