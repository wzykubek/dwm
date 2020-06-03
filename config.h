/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;  /* border pixel of windows */
static const unsigned int snap      = 32; /* snap pixel */
static const int rmaster            = 0;  /* 1 means master-area is initially on the right */
static const int showbar            = 1;  /* 0 means no bar */
static const int topbar             = 1;  /* 0 means bottom bar */

/*   Display modes of the tab bar: never shown, always shown, shown only in */
/*   monocle mode in presence of several windows.                           */
/*   Modes after showtab_nmodes are disabled                                */
enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always};
static const int showtab            = showtab_auto; /* Default tab bar show mode */
static const int toptab             = False;    /* False means bottom tab bar */

static const char *fonts[]          = { "monospace:size=9" };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#1b1b1b";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#5e3059";
static char selbgcolor[]            = "#5e3059";
static char *colors[][3]            = {
  /*              fg             bg           border   */
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor},
  [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] =          { "", "", "", "", "5", "6", "7", "8", "" };
static const char *tagsalt[] =       { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   */
  /* class            instance      title       tags mask     isfloating   monitor */
  { "TelegramDesktop",  NULL,       NULL,       1 << 3,       0,           -1 },
  { "firefox",          NULL,       NULL,       1 << 2,       0,           -1 },
  { "KeePassXC",        NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
  /* symbol arrange function */
  { "| ", tile },    /* first entry is default */
  { "| ", NULL },    /* no layout function means floating behavior */
  { "| ", monocle },
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

static Key keys[] = {
  /* modifier                 key           function           argument */
  { MODKEY|ControlMask,       XK_r,         xrdb,              {.v = NULL } },
  { MODKEY|ShiftMask,         XK_b,         togglebar,         {0} },
  { MODKEY|ShiftMask,         XK_w,         tabmode,           {-1} },
  { MODKEY|ControlMask,       XK_n,         togglealttag,      {0} },
  { MODKEY,                   XK_r,         togglermaster,     {0} },
  { MODKEY,                   XK_v,         togglescratch,     {.v = scratchpadcmd } },
  { MODKEY|ControlMask,       XK_s,         togglesticky,      {0} },
  { MODKEY,                   XK_j,         focusstack,        {.i = +1 } },
  { MODKEY,                   XK_period,    shiftview,         {.i = +1 } },
  { MODKEY,                   XK_comma,     shiftview,         {.i = -1 } },
  { MODKEY|ShiftMask,         XK_j,         rotatestack,       {.i = +1 } },
  { MODKEY|ShiftMask,         XK_k,         rotatestack,       {.i = -1 } },
  { MODKEY,                   XK_k,         focusstack,        {.i = -1 } },
  { MODKEY,                   XK_i,         incnmaster,        {.i = +1 } },
  { MODKEY,                   XK_o,         incnmaster,        {.i = -1 } },
  { MODKEY,                   XK_h,         setmfact,          {.f = -0.05} },
  { MODKEY,                   XK_l,         setmfact,          {.f = +0.05} },
  { MODKEY,                   XK_space,     zoom,              {0} },
  { MODKEY,                   XK_Tab,       view,              {0} },
  { MODKEY,                   XK_q,         killclient,        {0} },
  { MODKEY,                   XK_t,         setlayout,         {.v = &layouts[0]} },
  { MODKEY,                   XK_f,         setlayout,         {.v = &layouts[1]} },
  { MODKEY|ShiftMask,         XK_f,         togglefloating,    {0} },
  { MODKEY,                   XK_y,         setlayout,         {.v = &layouts[2]} },
  { MODKEY,                   XK_0,         view,              {.ui = ~0 } },
  { MODKEY|ShiftMask,         XK_0,         tag,               {.ui = ~0 } },
  TAGKEYS(                    XK_1,                            0)
  TAGKEYS(                    XK_2,                            1)
  TAGKEYS(                    XK_3,                            2)
  TAGKEYS(                    XK_4,                            3)
  TAGKEYS(                    XK_5,                            4)
  TAGKEYS(                    XK_6,                            5)
  TAGKEYS(                    XK_7,                            6)
  TAGKEYS(                    XK_8,                            7)
  TAGKEYS(                    XK_9,                            8)
  { MODKEY|ShiftMask,         XK_q,         quit,              {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
  { ClkTabBar,            0,              Button1,        focuswin,       {0} },
};
