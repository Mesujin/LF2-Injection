#ifndef _MD_SGAME_H_DECL
 #define _MD_SGAME_H_DECL


 #define _MD_OLD_SCRIPT
 
 constexpr int MaximumObject = 400;
 constexpr int MaximumFrames = 400;
 constexpr int MaximumManaPoint = 500;
 
 #ifdef _MD_OLD_SCRIPT
 typedef struct 
 {
  int kind;
  int x;
  int y;
  int action;
  int dvx;
  int dvy;
  int oid;
  int facing;
 } sOpoint;
 typedef struct
 {
  int x;
  int y;
 } sBpoint;
 typedef struct
 {
  int kind;
  int x;
  int y;
  int injury; // If its kind 2 this is fronthurtact.
  int cover;  // If its kind 2 this is backhurtact.
  int vaction;
  int aaction;
  int jaction;
  int daction;
  int throwvx;
  int throwvy;
  int hurtable;
  int decrease;
  int dircontrol;
  int taction;
  int throwinjury;
  int throwvz;
 } sCpoint;
 typedef struct
 {
  int kind;
  int x;
  int y;
  int weaponact;
  int attacking;
  int cover;
  int dvx;
  int dvy;
  int dvz;
 } sWpoint;
 typedef struct
 {
  int kind;
  int x;
  int y;
  int w;
  int h;
  int dvx;
  int dvy;
  int fall;
  int arest;
  int vrest;
  int unkwn1; // Named "respond" by xsoameix.
  int effect;
  int catchingact1;
  int catchingact2;
  int caughtact1;
  int caughtact2;
  int bdefend;
  int injury;
  int zwidth;
  int unkwn2;
 } sItr;
 typedef struct
 {
  int kind;
  int x;
  int y;
  int w;
  int h;
  int unkwn1;
  int unkwn2;
  int unkwn3;
  int unkwn4;
  int unkwn5;
 } sBdy;
 typedef struct
 {
  char exists;
  int pic;
  int state;
  int wait;
  int next;
  int dvx;
  int dvy;
  int dvz;
  int unkwn1;
  int hit_a;
  int hit_d;
  int hit_j;
  int hit_Fa;
  int hit_Ua;
  int hit_Da;
  int hit_Fj;
  int hit_Uj;
  int hit_Dj;
  int hit_ja;
  int mp;
  int centerx;
  int centery;
  sOpoint opoint;
  int unkwn2;
  int unkwn3;
  sBpoint bpoint;
  sCpoint cpoint;
  int unkwn4;
  int unkwn5;
  int unkwn6;
  sWpoint wpoint;
  int unkwn7;
  int unkwn8;
  int unkwn9;
  int unkwn10;
  int unkwn11;
  int unkwn12;
  int unkwn13;
  int unkwn14;
  int unkwn15;
  int unkwn16;
  int unkwn17;
  int itr_count;
  int bdy_count;
  //vv these are pointers to arrays.
  sItr *itrs;
  sBdy *bdys;
  //vv these values form a rectangle that holds all itrs/bdys within it.
  int itr_x;
  int itr_y;
  int itr_w;
  int itr_h;
  int bdy_x;
  int bdy_y;
  int bdy_w;
  int bdy_h;
  //----------------------------------------
  int unkwn18;
  char fname[20];
  char (*sound)[20]; // Maximum sound path is unknown actually.
  int unkwn19;
 } sFrame;
 typedef struct 
 {
  int walking_frame_rate;
  int unkwn1;
  double walking_speed;
  double walking_speedz;
  int running_frame_rate;
  double running_speed;
  double running_speedz;
  double heavy_walking_speed;
  double heavy_walking_speedz;
  double heavy_running_speed;
  double heavy_running_speedz;
  double jump_height;
  double jump_distance;
  double jump_distancez;
  double dash_height;
  double dash_distance;
  double dash_distancez;
  double rowing_height;
  double rowing_distance;
  int weapon_hp;
  int weapon_drop_hurt;
  char unkwn2[1024];
  int pic_count;
  char pic_bmps[40][10];
  int pic_index[10];
  int pic_width[10];
  int pic_height[10];
  int pic_row[10];
  int pic_col[10];
  int id;
  int type;
  int unkwn3;
  char small_bmp[40]; // I believe at least some of this has to do with small image.
  int unkwn4;
  char face_bmp[40];  // I believe at least some of this has to do with small image.
  int unkwn5[20];
  sFrame frames[MaximumFrames];
  char name[12];      // Not actually certain that the length is 12, seems like voodoo magic.
 } sDataFile;
 typedef struct 
 {
  int move_counter;           // Walk Animation | Counter
  int run_counter;            // Run Animation  | Counter
  int blink;                  // Invisibility   | Value
  int unkwn1;                 //
  int x;                      // X-Axis Display Position | Value
  int y;                      // Y-Axis Display Postiion | Value
  int z;                      // Z-Axis Display Postiion | Value
  char unkwn2[12];            //
  double x_acceleration;      // X-Axis Velocity Accumulation | Value
  double y_acceleration;      // Y-Axis Velocity Accumulation | Value
  double z_acceleration;      // Z-Axis Velocity Accumulation | Value
  double x_velocity;          // X-Axis Velocity              | Value
  double y_velocity;          // Y-Axis Velocity              | Value
  double z_velocity;          // Z-Axis Velocity              | Value
  double x_real;              // X-Axis Position              | Value
  double y_real;              // Y-Axis Position              | Value
  double z_real;              // Z-Axis Position              | Value
  int frame1;                 // Main Frame                   | Value
  int frame2;                 // Frame Before Hit             | Value
  int frame3;                 // Calc Frame                   | Value
  int frame4;                 // Last Frame                   | Value
  char facing;                // Facing                       | Value
  char unkwn3[7];             //
  int wait_counter;           // Frame Wait Counter   | Counter
  int ccatcher;               // Catching             | ObjNum
  int ctimer;                 // Caught by            | ObjNum
  int catch_decrease;         // Catching Decrease    | Counter
  int weapon_type;            // Held Object's Type   | Value
  int weapon_held;            // Held Object's ObjNum | ObjNum
  int weapon_holder;          // Held by              | ObjNum
  int unkwn4;                 //
  char unkwn5[8];             //
  int fall;                   // Fall / Injury Effect | Value
  int shake;                  // Hitlag               | Value
  int bdefend;                // Defend Breakness     | Value
  char unkwn6[10];            //
  char holding_up;            // Hold Input  | Value
  char holding_down;          // Hold Input  | Value
  char holding_left;          // Hold Input  | Value
  char holding_right;         // Hold Input  | Value
  char holding_a;             // Hold Input  | Value
  char holding_j;             // Hold Input  | Value
  char holding_d;             // Hold Input  | Value
  char up;                    // Press Input | Value
  char down;                  // Press Input | Value
  char left;                  // Press Input | Value
  char right;                 // Press Input | Value
  char A;                     // Press Input | Value
  char J;                     // Press Input | Value
  char D;                     // Press Input | Value
  char DrA;                   // Cast Input  | Value
  char DlA;                   // Cast Input  | Value
  char DuA;                   // Cast Input  | Value
  char DdA;                   // Cast Input  | Value
  char DrJ;                   // Cast Input  | Value
  char DlJ;                   // Cast Input  | Value
  char DuJ;                   // Cast Input  | Value
  char DdJ;                   // Cast Input  | Value
  char DJA;                   // Cast Input  | Value
  char unkwn7[15];            //
  int arest;                  // Applied arest | Counter
  char vrests[MaximumObject]; // vrest Counter | Counter
  int attacked_object_num;    // Last Hit by   | ObjNum
                              // Skip unkwn8 for backwards compatibility reasons.
  char unkwn9[112];           //
  int clone;                  // Clone by               | ObjNum
  int weapon_thrower;         // Thrown by              | ObjNum
  int hp;                     // Health Point           | Value
  int dark_hp;                // Potential Health Point | Value
  int max_hp;                 // Maximum Health Point   | Value
  int mp;                     // Mana Point             | Value
  int reserve;                // Reserve Counter        | Counter
  int unkwn10;                //
  int unkwn11;                //
  int pic_gain;               // pic Offside        | Value
  int bottle_hp;              // Drink Point        | Value
  int throwinjury;            // Thrown Drop Damage | Value
  char unkwn12[20];           // 
  int firzen_counter;         // Firzen Transforming Counter | Counter
  int unkwn13;                //
  int armour_multiplier;      // Defense / Damage Taken Ratio | Value
  int unkwn14;                //
  int total_attack;           // Summary - Damage Dealt     | Value
  int hp_lost;                // Summary - Damage Taken     | Value
  int mp_usage;               // Summary - Mana Point Usage | Value
  int unkwn15;                // Summary - Host             | ObjNum
  int kills;                  // Summary - Total Kill       | Value
  int weapon_picks;           // Summary - Total Pick       | Value
  int enemy;                  // Target                     | ObjNum
  int team;                   // Team                       | Value
  sDataFile *data;            // Address to data.
 } sObject;
 typedef struct 
 {
  int unkwn1[43]; // Seems to have something to do with bosses, is changed during game so I believe it keeps track of whether or not soldiers should respawn.
  int id;
  int x;
  int hp;
  int times;
  int reserve;
  int join;
  int join_reserve;
  int act;
  int unkwn2;
  double ratio;
  int role;       // 0 = Normal; 1 = "soldier"; 2 = "boss".
  int unkwn3;
 } sSpawn;
 typedef struct
 {
  int bound;
  char music[52];
  sSpawn spawns[60];
  int when_clear_goto_phase;
 } sPhase;
 typedef struct
 {
  int phase_count;
  sPhase phases[100]; //
 } sStage;
 typedef struct
 {
  int  transparency[30]; // 0x445 | Value   : game.files.get_backgrounds()[].layer[].transparency \ Game.Database.Background()[].layer[].transparency
  int  width[30];        // 0x4BD | Value   : game.files.get_backgrounds()[].layer[].width        \ Game.Database.Background()[].layer[].width
  int  x[30];            // 0x535 | Value   : game.files.get_backgrounds()[].layer[].x            \ Game.Database.Background()[].layer[].x
  int  y[30];            // 0x5AD | Value   : game.files.get_backgrounds()[].layer[].y            \ Game.Database.Background()[].layer[].y
  int  height[30];       // 0x625 | Value   : game.files.get_backgrounds()[].layer[].height       \ Game.Database.Background()[].layer[].height
  int  loop[30];         // 0x69D | Value   : game.files.get_backgrounds()[].layer[].loop         \ Game.Database.Background()[].layer[].loop
  int  c1[30];           // 0x715 | Value   : game.files.get_backgrounds()[].layer[].c1           \ Game.Database.Background()[].layer[].c1
  int  c2[30];           // 0x78D | Value   : game.files.get_backgrounds()[].layer[].c2           \ Game.Database.Background()[].layer[].c2
  int  cc[30];           // 0x805 | Value   : game.files.get_backgrounds()[].layer[].cc           \ Game.Database.Background()[].layer[].cc
  int  animation[30];    // 0x87D | Counter : game.files.get_backgrounds()[].layer[].animation    \ Game.Database.Background()[].layer[].Animation
  int  rect[30];         // 0x8F5 | Value   : game.files.get_backgrounds()[].layer[].rect         \ Game.Database.Background()[].layer[].rect
 } sLayer;
 typedef struct 
 {
  int  bg_width;            // [+0x000] | Value   : game.files.get_backgrounds()[].bg_width       \ Game.Database.Background()[].width
  int  bg_zwidth1;          // [+0x004] | Value   : game.files.get_backgrounds()[].bg_zwidth1     \ Game.Database.Background()[].zboundary[]
  int  bg_zwidth2;          // [+0x008] | Value   : game.files.get_backgrounds()[].bg_zwidth2     \ 
  int  perspective1;        // [+0x00C]           : game.files.get_backgrounds()[].perspective1   \ Game.Database.Background()[].Unknown_1[]
  int  perspective2;        // [+0x010]           : game.files.get_backgrounds()[].perspective2   \ 
  int  shadow1;             // [+0x014] | Value   : game.files.get_backgrounds()[].shadow1        \ Game.Database.Background()[].shadowsize[]
  int  shadow2;             // [+0x018] | Value   : game.files.get_backgrounds()[].shadow2        \ 
  int  layer_count;         // [+0x01C] | Value   : game.files.get_backgrounds()[].layer_count    \ Game.Database.Background()[].layer_Count
  char layer_bmps[30][30];  // [+0x020] | File    : game.files.get_backgrounds()[].layer_bmps[][] \ Game.Database.Background()[].layer_Image[][]
  char shadow_bmp[30];      // [+0x3A4] | File    : game.files.get_backgrounds()[].shadow_bmp[]   \ Game.Database.Background()[].shadow[]
  char unknown_1[10];       // [+0x41C]           : game.files.get_backgrounds()[].unkwn1[]       \ Game.Database.Background()[].Unknown_2[]
  char name[30];            // [+0x426] | String  : game.files.get_backgrounds()[].name[]         \ Game.Database.Background()[].name[]
  char unknown_2;           // [+0x444]           : game.files.get_backgrounds()[].unkwn2[]       \ Game.Database.Background()[].Unknown_3[]
  sLayer layer;             // [+0x445] | Struct  : game.files.get_backgrounds()[].layer[]        \ Game.Database.Background()[].layer[]
  int  layer_ptrs[30];      // [+0x96D] | Address : game.files.get_backgrounds()[].layer_ptrs[]   \ Game.Database.Background()[].layer_Ptr[]
  int  ptrs;                // [+0x9E5] | Address : game.files.get_backgrounds()[].ptrs           \ Game.Database.Background()[].Ptr
 } sBackground;             
 typedef struct 
 {
  sDataFile *datas[MaximumObject + 100]; // [] | Pointer : game.files.datas[]             \ Game.Database.Data[]
  sStage stages[60];                     // [] | Struct  : game.files.stages[]            \ Game.Database.Stage[]
  sBackground backgrounds[50];           // [] | Struct  : game.files.get_backgrounds()[] \ Game.Database.Background()[]
 } sFileManager;
 typedef struct
 {
  int state;                       // [+0x004] | Value   : game.state     \ Game.State
  char exists[MaximumObject];      // [+0x194] | Value   : game.exists[]  \ Game.Object_Exist[]
  sObject *objects[MaximumObject]; // [+0x7D4] | Pointer : game.objects[] \ Game.Object[]
  sFileManager *files;             // [+0xFA4] | Pointer : game.files     \ Game.Database
 } sGame;
 #endif

 typedef struct
 {
  int  kind;
  int  x;
  int  y;
  int  w;
  int  h;
  char Unknown_1[20];
 } MD_BDY;
 typedef struct
 {
  int  kind;
  int  x;
  int  y;
  int  w;
  int  h;
  int  dvx;
  int  dvy;
  int  fall;
  int  arest;
  int  vrest;
  int  respond;
  int  effect;
  int  catchingact[2];
  int  caughtact[2];
  int  bdefend;
  int  injury;
  int  zwidth;
  char Unknown_1[4];
 } MD_ITR;
 typedef struct 
 {
  int kind;
  int x;
  int y;
  int action;
  int dvx;
  int dvy;
  int oid;
  int facing;
 } MD_OPOINT;
 typedef struct
 {
  int kind;
  int x;
  int y;
  int weaponact;
  int attacking;
  int cover;
  int dvx;
  int dvy;
  int dvz;
 } MD_WPOINT;
 typedef struct
 {
  int kind;
  int x;
  int y;
  int injury_fronthurtact;
  int cover_backhurtact;
  int vaction;
  int aaction;
  int jaction;
  int daction;
  int throwvx;
  int throwvy;
  int hurtable;
  int decrease;
  int dircontrol;
  int taction;
  int throwinjury;
  int throwvz;
 } MD_CPOINT;
 typedef struct
 {
  int x;
  int y;
 } MD_BPOINT;
 typedef struct
 {
  int X;
  int Y;
  int W;
  int H;
 } MD_RECTANGLE;
 typedef struct
 {
  char Exist;
  int  pic;
  int  state;
  int  wait;
  int  next;
  int  dvx;
  int  dvy;
  int  dvz;
  char Unknown_1[4];
  int  hit_a;
  int  hit_d;
  int  hit_j;
  int  hit_Fa;
  int  hit_Ua;
  int  hit_Da;
  int  hit_Fj;
  int  hit_Uj;
  int  hit_Dj;
  int  hit_ja;
  int  mp;
  int  centerx;
  int  centery;
  MD_OPOINT opoint;
  char Unknown_2[8];
  MD_BPOINT bpoint;
  MD_CPOINT cpoint;
  char Unknown_3[12];
  MD_WPOINT wpoint;
  char Unknown_4[44];
  int  itr_Count;
  int  bdy_Count;
  //vv these are pointers to arrays.
  MD_ITR *itr;
  MD_BDY *bdy;
  //vv these values form a rectangle that holds all itrs/bdys within it.
  MD_RECTANGLE itr_Rectangle;
  MD_RECTANGLE bdy_Rectangle;
  //----------------------------------------
  char Unknown_5[4];
  char Name[20];
  char (*sound)[20]; // Maximum sound path is unknown actually.
  char Unknown_6[4];
 } MD_FRAME;
 typedef struct
 {
  int  dvx;
  int  dvy;
  int  fall;
  int  arest;
  int  vrest;
  int  respond;
  int  effect;
  char Unknown_1[20];
  int  bdefend;
  int  injury;
  int  zwidth;
  char Unknown_2[20];
 }
 MD_ENTRY;
 typedef struct
 {
  MD_ENTRY entry[9];
  char entry_Name[5][30]; // The size was actually [10][30], but considering you'll use "file_Address" or etc, then it supposed to be [6][30].
  char Unknown_1[30];
 } MD_STRENGTH;
 typedef struct
 {
  int Index[10];
  int w[10];
  int h[10];
  int row[10];
  int col[10];
 } MD_FILE;
 typedef struct 
 {
  int    walking_frame_rate;
  char   Unknown_1[4];
  double walking_speed;
  double walking_speedz;
  int    running_frame_rate;
  double running_speed;
  double running_speedz;
  double heavy_walking_speed;
  double heavy_walking_speedz;
  double heavy_running_speed;
  double heavy_running_speedz;
  double jump_height;
  double jump_distance;
  double jump_distancez;
  double dash_height;
  double dash_distance;
  double dash_distancez;
  double rowing_height;
  double rowing_distance;
  int    weapon_hp;
  int    weapon_drop_hurt;
  char   Unknown_2[124];
  MD_STRENGTH Strength;
  int    file_Count;            // This is just a redudant, changing it won't affect anything.
  char   file_Address[10][40];  // This is just a redudant, changing it won't affect anything.
  MD_FILE file[1];              // This is just a redudant, changing it won't affect anything.
  int    id;
  int    type;
  char   Unknown_3[4];
  char   small_[40];
  char   Unknown_4[4];
  char   head[40];
  char   Unknown_5[80];
  MD_FRAME Frame[MaximumFrames];
  char   name[12];
 } MD_DATA;
 typedef struct 
 {
  int    Walk_Animation;           // Walk Animation | Counter
  int    Run_Animation;            // Run Animation  | Counter
  int    Invisibility;             // Invisibility   | Counter
  char   Unknown_1[4];
  int    X_Display;                      // X-Axis Display Position | Value
  int    Y_Display;                      // Y-Axis Display Postiion | Value
  int    Z_Display;                      // Z-Axis Display Postiion | Value
  char   Unknown_2[12];
  double X_Acceleration;      // X-Axis Velocity Accumulation | Value
  double Y_Acceleration;      // Y-Axis Velocity Accumulation | Value
  double Z_Acceleration;      // Z-Axis Velocity Accumulation | Value
  double X_Velocity;          // X-Axis Velocity              | Value
  double Y_Velocity;          // Y-Axis Velocity              | Value
  double Z_Velocity;          // Z-Axis Velocity              | Value
  double X;              // X-Axis Position              | Value
  double Y;              // Y-Axis Position              | Value
  double Z;              // Z-Axis Position              | Value
  int    Frame;                 // Main Frame                   | Value
  int    Frame_Hit;                 // Frame Before Hit             | Value
  int    Frame_Calculation;                 // Calc Frame                   | Value
  int    Frame_Last;                 // Last Frame                   | Value
  char   Facing;                // Facing                       | Value
  char   Unknown_3[7];
  int    Wait;           // Frame Wait Counter   | Counter
  int    Catch;               // Catching             | ObjNum
  int    Caught;                 // Caught by            | ObjNum
  int    Catch_Decrease;         // Catching Decrease    | Value / Counter
  int    Held_Type;            // Held Object's Type   | Value
  int    Held;            // Held Object's ObjNum | ObjNum
  int    Holder;          // Held by              | ObjNum
  char   Unknown_4[12];
  int    Fall;                   // Fall / Injury Effect | Value
  int    Hitlag;                  // Hitlag               | Value
  int    Defend;                // Defend Breakness     | Value
  char   Unknown_5[10];            //
  char   Up_Hold;            // Hold Input  | Value
  char   Down_Hold;          // Hold Input  | Value
  char   Left_Hold;          // Hold Input  | Value
  char   Right_Hold;         // Hold Input  | Value
  char   A_Hold;             // Hold Input  | Value
  char   J_Hold;             // Hold Input  | Value
  char   D_Hold;             // Hold Input  | Value
  char   Up;                    // Press Input | Value
  char   Down;                  // Press Input | Value
  char   Left;                  // Press Input | Value
  char   Right;                 // Press Input | Value
  char   A;                     // Press Input | Value
  char   J;                     // Press Input | Value
  char   D;                     // Press Input | Value
  char   Cast_DRA;                   // Cast Input  | Value
  char   Cast_DLA;                   // Cast Input  | Value
  char   Cast_DUA;                   // Cast Input  | Value
  char   Cast_DDA;                   // Cast Input  | Value
  char   Cast_DRJ;                   // Cast Input  | Value
  char   Cast_DLJ;                   // Cast Input  | Value
  char   Cast_DUJ;                   // Cast Input  | Value
  char   Cast_DDJ;                   // Cast Input  | Value
  char   Cast_DJA;                   // Cast Input  | Value
  char   Unknown_6[3];            //
  int    Heal;            //
  char   Unknown_7[8];            //
  int    Attack_Rest;                  // Applied arest | Counter
  char   Hit_Rest[MaximumObject]; // vrest Counter | Counter
  int    Last_Hit;    // Last Hit by   | ObjNum
  char   Unknown_8[112];           //
  int    Cloner;                  // Clone by               | ObjNum
  int    Thrower;         // Thrown by              | ObjNum
  int    Health;                     // Health Point           | Value
  int    Potential_Health;                // Potential Health Point | Value
  int    Max_Health;                 // Maximum Health Point   | Value
  int    Mana;                     // Mana Point             | Value
  int    Reserve;                // Reserve Counter        | Counter
  char   Unknown_9[8];           //
  int    Pic_Offset;               // pic Offset        | Value
  int    Drink_Health;              // Drink Point        | Value
  int    Thrown_Drop_Damage;            // Thrown Drop Damage | Value
  char   Unknown_10[20];           // 
  int    Fusion;         // Firzen Transforming Counter | Counter
  char   Unknown_11[4];           //
  int    Defense;      // Defense / Damage Taken Ratio | Value
  char   Unknown_12[4];           //
  int    Summary_Attack;           // Summary - Damage Dealt     | Value
  int    Summary_HP_Lost;                // Summary - Damage Taken     | Value
  int    Summary_MP_Usage;               // Summary - Mana Point Usage | Value
  int    Summary_Host;                // Summary - Host             | ObjNum
  int    Summary_Kill;                  // Summary - Total Kill       | Value
  int    Summary_Picking;           // Summary - Total Pick       | Value
  int    Target;                  // Target                     | ObjNum
  int    Team;                   // Team                       | Value
  MD_DATA *Data;            // Address to data.
 } MD_OBJECT;
 typedef struct 
 {
  char   Unknown_1[172]; // Seems to have something to do with bosses, is changed during game so I believe it keeps track of whether or not soldiers should respawn.
  int    id;
  int    x;
  int    hp;
  int    times;
  int    reserve;
  int    join;
  int    join_reserve;
  int    act;
  int    y;
  double ratio;
  int    Role;       // 0 = Normal; 1 = "soldier"; 2 = "boss".
  char   Unknown_2[4];
 } MD_SPAWN;
 typedef struct
 {
  int  bound;
  char music[52];
  MD_SPAWN Spawn[60];
  int  when_clear_goto_phase;
 } MD_PHASE;
 typedef struct
 {
  int Phase_Count;
  MD_PHASE Phase[100]; //
 } MD_STAGE;
 typedef struct
 {
  int  transparency[30]; // 0x445 | Value   : game.files.get_backgrounds()[].layer[].transparency \ Game.Database.Background()[].layer[].transparency
  int  width[30];        // 0x4BD | Value   : game.files.get_backgrounds()[].layer[].width        \ Game.Database.Background()[].layer[].width
  int  x[30];            // 0x535 | Value   : game.files.get_backgrounds()[].layer[].x            \ Game.Database.Background()[].layer[].x
  int  y[30];            // 0x5AD | Value   : game.files.get_backgrounds()[].layer[].y            \ Game.Database.Background()[].layer[].y
  int  height[30];       // 0x625 | Value   : game.files.get_backgrounds()[].layer[].height       \ Game.Database.Background()[].layer[].height
  int  loop[30];         // 0x69D | Value   : game.files.get_backgrounds()[].layer[].loop         \ Game.Database.Background()[].layer[].loop
  int  c1[30];           // 0x715 | Value   : game.files.get_backgrounds()[].layer[].c1           \ Game.Database.Background()[].layer[].c1
  int  c2[30];           // 0x78D | Value   : game.files.get_backgrounds()[].layer[].c2           \ Game.Database.Background()[].layer[].c2
  int  cc[30];           // 0x805 | Value   : game.files.get_backgrounds()[].layer[].cc           \ Game.Database.Background()[].layer[].cc
  int  Animation[30];    // 0x87D | Counter : game.files.get_backgrounds()[].layer[].animation    \ Game.Database.Background()[].layer[].Animation
  int  rect[30];         // 0x8F5 | Value   : game.files.get_backgrounds()[].layer[].rect         \ Game.Database.Background()[].layer[].rect
 } MD_LAYER;
 typedef struct 
 {
  int  width;            // [+0x000] | Value   : game.files.get_backgrounds()[].bg_width       \ Game.Database.Background()[].width
  int  zboundary[2];          // [+0x004] | Value   : game.files.get_backgrounds()[].bg_zwidth1     \ Game.Database.Background()[].zboundary[]
  int  perspective[2];        // [+0x00C]           : game.files.get_backgrounds()[].perspective1   \ Game.Database.Background()[].Unknown_1[]
  int  shadowsize[2];             // [+0x014] | Value   : game.files.get_backgrounds()[].shadow1        \ Game.Database.Background()[].shadowsize[]
  int  layer_Count;         // [+0x01C] | Value   : game.files.get_backgrounds()[].layer_count    \ Game.Database.Background()[].layer_Count
  char layer_Pic[30][30];
  char shadow[30];
  char Unknown_1[10];
  char name[30];
  char Unknown_2;
  MD_LAYER layer;             // [+0x445] | Struct  : game.files.get_backgrounds()[].layer[]        \ Game.Database.Background()[].layer[]
  int  layer_Ptr[30];      // [+0x96D] | Address : game.files.get_backgrounds()[].layer_ptrs[]   \ Game.Database.Background()[].layer_Ptr[]
  int  Ptr;                // [+0x9E5] | Address : game.files.get_backgrounds()[].ptrs           \ Game.Database.Background()[].Ptr
 } MD_BACKGROUND;             
 typedef struct 
 {
  MD_DATA *Data[MaximumObject + 100]; // [] | Pointer : game.files.datas[]             \ Game.Database.Data[]
  MD_STAGE Stage[60];                     // [] | Struct  : game.files.stages[]            \ Game.Database.Stage[]
  MD_BACKGROUND Background[50];           // [] | Struct  : game.files.get_backgrounds()[] \ Game.Database.Background()[]
 } MD_DATABASE;
 typedef struct
 {
  char Unknown_1[1];
 } MD_BASES;
 typedef struct
 {
  //MD_BASES Data;
  //char Unknown_1[1];
  int  State;                       // [+0x004] | Value   : game.state     \ Game.State
  char Object_Exist[MaximumObject];      // [+0x194] | Value   : game.exists[]  \ Game.Object_Exist[]
  MD_OBJECT *Object[MaximumObject]; // [+0x7D4] | Pointer : game.objects[] \ Game.Object[]
  MD_DATABASE *Database;             // [+0xFA4] | Pointer : game.files     \ Game.Database
 } MD_GAME;
#endif
