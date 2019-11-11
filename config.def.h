/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 0;   /* border pixel of windows */
static const unsigned int snap           = 25;  /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;   /* 0 means no systray */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const char *fonts[]               = { "monospace:size=10" };
static const char dmenufont[]            = "monospace:size=10";
static const char col_gray1[]            = "#222222";
static const char col_gray2[]            = "#444444";
static const char col_gray3[]            = "#bbbbbb";
static const char col_gray4[]            = "#eeeeee";
static const char col_cyan[]             = "#005577";
static const char col_cyan1[]            = "#00709d";
static const char col_bg[]               = "#161819";
static const char col_bgalt[]            = "#1C1E1F";
static const char *colors[][3]           = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_bg, col_gray2 },
	[SchemeSel]  = { col_gray4, col_bg,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[]=",      tile },    /* first entry is default */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const char TERMINAL[] = "st";

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]    = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *menucmd[]     = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]     = { TERMINAL, NULL };
static const char *ranger[]      = { TERMINAL,  "-e", "ranger", NULL };
static const char *literature[]  = { TERMINAL,  "-e", "ranger", "/home/tim/Literatur/", NULL };
static const char *studying[]    = { TERMINAL,  "-e", "ranger", "/home/tim/Studium/", NULL };
static const char *julia[]       = { TERMINAL, "-e", "julia", NULL };
static const char *python[]      = { TERMINAL, "-e", "ipython", NULL };
static const char *battop[]      = { TERMINAL, "-e", "battop", NULL};
static const char *htop[]        = { TERMINAL, "-e", "htop", "-t", NULL};
static const char *screenshot[]  = { "spectacle",  NULL };
static const char *lum_up[]      = { "light", "-A", "5", NULL};
static const char *lum_down[]    = { "light", "-U", "5", NULL};
static const char *vol_up[]      = { "amixer", "set", "Master", "unmute", "3%+", "-q", NULL };
static const char *vol_down[]    = { "amixer", "set", "Master", "unmute", "3%-", "-q", NULL };
static const char *vol_mute[]    = { "amixer", "set", "Master", "toggle", "-q", NULL };
static const char *lockscreen[]  = { "betterlockscreen", "-l", "-t", "Passwort eingeben", NULL };
static const char *R[]           = { TERMINAL, "-e", "R", "-q", "--no-save", NULL };
static const char *SU[]          = { "sh", "/home/tim/scripts/TF/SU", NULL };
static const char *SD[]          = { "sh", "/home/tim/scripts/TF/SD", NULL };
static const char *SR[]          = { "sh", "/home/tim/scripts/TF/SR", NULL };
static const char *SL[]          = { "sh", "/home/tim/scripts/TF/SL", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
    { 0x000000,                     0x1008ff13,spawn,          {.v = vol_up } },
    { 0x000000,                     0x1008ff11,spawn,          {.v = vol_down } },
    { 0x000000,                     0x1008ff02,spawn,          {.v = lum_up } },
    { 0x000000,                     0x1008ff03,spawn,          {.v = lum_down } },
    { 0x000000,                     0x1008ff12,spawn,          {.v = vol_mute } },
    { 0x000000,                     XK_Print,  spawn,          {.v = screenshot } },
	{ MODKEY,                       XK_d,      spawn,          {.v = menucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_r,      spawn,          {.v = ranger } },
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = R } },
	{ MODKEY,                       XK_s,      spawn,          {.v = studying } },
	{ MODKEY,                       XK_l,      spawn,          {.v = literature } },
	{ MODKEY,                       XK_Escape, spawn,          {.v = lockscreen } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = battop } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,      spawn,          {.v = julia } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = python } },
	{ MODKEY,                       XK_h,      spawn,          {.v = htop } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_c,      center,         {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY|ShiftMask,             XK_Up,     spawn,          {.v = SU } },
    { MODKEY|ShiftMask,             XK_Down,   spawn,          {.v = SD } },
    { MODKEY|ShiftMask,             XK_Right,  spawn,          {.v = SR } },
    { MODKEY|ShiftMask,             XK_Left,   spawn,          {.v = SL } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} }, // Exit dwm
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
