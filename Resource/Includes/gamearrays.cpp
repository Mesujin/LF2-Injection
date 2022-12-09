#include "gamearrays.h"
#include <string>

template < int offset > void *get_property(void *self){return (void*)((char*)self + offset);} // AngelScript does not support offsets larger than 0x7fff, and when that is the case we use this function instead.
char        *CharArray::opIndex(unsigned int x)      {return (((char*)this) + x);}
template < int size > CharArray   *CharArrayArray::opIndex(unsigned int x){return (CharArray*)(((char*)this) + x * size);}
int         *IntArray::opIndex(unsigned int x)       {return (((int*)this) + x);}
bool        *BoolArray::opIndex(unsigned int x)      {return (((bool*)this) + x);}
sItr        *ItrArray::opIndex(unsigned int x)       {return ((sItr*)this) + x;}
sBdy        *BdyArray::opIndex(unsigned int x)       {return ((sBdy*)this) + x;}
sDataFile   *DataFileArray::opIndex(unsigned int x)  {return *(((sDataFile**)this) + x);}
sObject     *ObjectArray::opIndex(unsigned int x)    {return *(((sObject**)this) + x);}
sFrame      *FrameArray::opIndex(unsigned int x)     {return ((sFrame*)this) + x;}
sBackground *BackgroundArray::opIndex(unsigned int x){return ((sBackground*)this) + x;}
sSpawn      *SpawnArray::opIndex(unsigned int x)     {return ((sSpawn*)this) + x;}
sPhase      *PhaseArray::opIndex(unsigned int x)     {return ((sPhase*)this) + x;}
sStage      *StageArray::opIndex(unsigned int x)     {return ((sStage*)this) + x;}

void RegisterGameArrays(asIScriptEngine *ScriptEngine, bool Vrab01)
{
 std::string Temp01 = "const ";
 if(Vrab01) Temp01 = "";
 ScriptEngine->RegisterObjectType("BoolArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectType("CharArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectType("CharArrayArray30", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectType("CharArrayArray40", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectType("IntArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectType("ItrArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectType("BdyArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectType("DataFileArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectType("ObjectArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectType("FrameArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectType("BackgroundArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectType("SpawnArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectType("PhaseArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectType("StageArray", 0, asOBJ_REF | asOBJ_NOCOUNT);

 ScriptEngine->RegisterObjectType("Opoint", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectProperty("Opoint", (Temp01 + "int kind").c_str(), asOFFSET(sOpoint, kind));
 ScriptEngine->RegisterObjectProperty("Opoint", (Temp01 + "int x").c_str(), asOFFSET(sOpoint, x));
 ScriptEngine->RegisterObjectProperty("Opoint", (Temp01 + "int y").c_str(), asOFFSET(sOpoint, y));
 ScriptEngine->RegisterObjectProperty("Opoint", (Temp01 + "int action").c_str(), asOFFSET(sOpoint, action));
 ScriptEngine->RegisterObjectProperty("Opoint", (Temp01 + "int dvx").c_str(), asOFFSET(sOpoint, dvx));
 ScriptEngine->RegisterObjectProperty("Opoint", (Temp01 + "int dvy").c_str(), asOFFSET(sOpoint, dvy));
 ScriptEngine->RegisterObjectProperty("Opoint", (Temp01 + "int oid").c_str(), asOFFSET(sOpoint, oid));
 ScriptEngine->RegisterObjectProperty("Opoint", (Temp01 + "int facing").c_str(), asOFFSET(sOpoint, facing));
    
 ScriptEngine->RegisterObjectType("Bpoint", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectProperty("Bpoint", (Temp01 + "int x").c_str(), asOFFSET(sBpoint, x));
 ScriptEngine->RegisterObjectProperty("Bpoint", (Temp01 + "int y").c_str(), asOFFSET(sBpoint, y));

 ScriptEngine->RegisterObjectType("Cpoint", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectProperty("Cpoint", (Temp01 + "int kind").c_str(), asOFFSET(sCpoint, kind));
 ScriptEngine->RegisterObjectProperty("Cpoint", (Temp01 + "int x").c_str(), asOFFSET(sCpoint, x));
 ScriptEngine->RegisterObjectProperty("Cpoint", (Temp01 + "int y").c_str(), asOFFSET(sCpoint, y));
 ScriptEngine->RegisterObjectProperty("Cpoint", (Temp01 + "int injury").c_str(), asOFFSET(sCpoint, injury)); // If its kind 2 this is fronthurtact.
 ScriptEngine->RegisterObjectProperty("Cpoint", (Temp01 + "int cover").c_str(), asOFFSET(sCpoint, cover));   // If its kind 2 this is backhurtact.
 ScriptEngine->RegisterObjectProperty("Cpoint", (Temp01 + "int vaction").c_str(), asOFFSET(sCpoint, vaction));
 ScriptEngine->RegisterObjectProperty("Cpoint", (Temp01 + "int aaction").c_str(), asOFFSET(sCpoint, aaction));
 ScriptEngine->RegisterObjectProperty("Cpoint", (Temp01 + "int jaction").c_str(), asOFFSET(sCpoint, jaction));
 ScriptEngine->RegisterObjectProperty("Cpoint", (Temp01 + "int daction").c_str(), asOFFSET(sCpoint, daction));
 ScriptEngine->RegisterObjectProperty("Cpoint", (Temp01 + "int throwvx").c_str(), asOFFSET(sCpoint, throwvx));
 ScriptEngine->RegisterObjectProperty("Cpoint", (Temp01 + "int throwvy").c_str(), asOFFSET(sCpoint, throwvy));
 ScriptEngine->RegisterObjectProperty("Cpoint", (Temp01 + "int hurtable").c_str(), asOFFSET(sCpoint, hurtable));
 ScriptEngine->RegisterObjectProperty("Cpoint", (Temp01 + "int decrease").c_str(), asOFFSET(sCpoint, decrease));
 ScriptEngine->RegisterObjectProperty("Cpoint", (Temp01 + "int dircontrol").c_str(), asOFFSET(sCpoint, dircontrol));
 ScriptEngine->RegisterObjectProperty("Cpoint", (Temp01 + "int taction").c_str(), asOFFSET(sCpoint, taction));
 ScriptEngine->RegisterObjectProperty("Cpoint", (Temp01 + "int throwinjury").c_str(), asOFFSET(sCpoint, throwinjury));
 ScriptEngine->RegisterObjectProperty("Cpoint", (Temp01 + "int throwvz").c_str(), asOFFSET(sCpoint, throwvz));

 ScriptEngine->RegisterObjectType("Wpoint", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectProperty("Wpoint", (Temp01 + "int kind").c_str(), asOFFSET(sWpoint, kind));
 ScriptEngine->RegisterObjectProperty("Wpoint", (Temp01 + "int x").c_str(), asOFFSET(sWpoint, x));
 ScriptEngine->RegisterObjectProperty("Wpoint", (Temp01 + "int y").c_str(), asOFFSET(sWpoint, y));
 ScriptEngine->RegisterObjectProperty("Wpoint", (Temp01 + "int weaponact").c_str(), asOFFSET(sWpoint, weaponact));
 ScriptEngine->RegisterObjectProperty("Wpoint", (Temp01 + "int attacking").c_str(), asOFFSET(sWpoint, attacking));
 ScriptEngine->RegisterObjectProperty("Wpoint", (Temp01 + "int cover").c_str(), asOFFSET(sWpoint, cover));
 ScriptEngine->RegisterObjectProperty("Wpoint", (Temp01 + "int dvx").c_str(), asOFFSET(sWpoint, dvx));
 ScriptEngine->RegisterObjectProperty("Wpoint", (Temp01 + "int dvy").c_str(), asOFFSET(sWpoint, dvy));
 ScriptEngine->RegisterObjectProperty("Wpoint", (Temp01 + "int dvz").c_str(), asOFFSET(sWpoint, dvz));

 ScriptEngine->RegisterObjectType("Itr", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int kind").c_str(), asOFFSET(sItr, kind));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int x").c_str(), asOFFSET(sItr, x));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int y").c_str(), asOFFSET(sItr, y));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int w").c_str(), asOFFSET(sItr, w));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int h").c_str(), asOFFSET(sItr, h));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int dvx").c_str(), asOFFSET(sItr, dvx));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int dvy").c_str(), asOFFSET(sItr, dvy));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int fall").c_str(), asOFFSET(sItr, fall));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int arest").c_str(), asOFFSET(sItr, arest));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int vrest").c_str(), asOFFSET(sItr, vrest));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int unkwn1").c_str(), asOFFSET(sItr, unkwn1));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int effect").c_str(), asOFFSET(sItr, effect));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int catchingact1").c_str(), asOFFSET(sItr, catchingact1));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int catchingact2").c_str(), asOFFSET(sItr, catchingact2));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int caughtact1").c_str(), asOFFSET(sItr, caughtact1));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int caughtact2").c_str(), asOFFSET(sItr, caughtact2));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int bdefend").c_str(), asOFFSET(sItr, bdefend));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int injury").c_str(), asOFFSET(sItr, injury));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int zwidth").c_str(), asOFFSET(sItr, zwidth));
 ScriptEngine->RegisterObjectProperty("Itr", (Temp01 + "int unkwn2").c_str(), asOFFSET(sItr, unkwn2));

 ScriptEngine->RegisterObjectType("Bdy", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectProperty("Bdy", (Temp01 + "int kind").c_str(), asOFFSET(sBdy, kind));
 ScriptEngine->RegisterObjectProperty("Bdy", (Temp01 + "int x").c_str(), asOFFSET(sBdy, x));
 ScriptEngine->RegisterObjectProperty("Bdy", (Temp01 + "int y").c_str(), asOFFSET(sBdy, y));
 ScriptEngine->RegisterObjectProperty("Bdy", (Temp01 + "int w").c_str(), asOFFSET(sBdy, w));
 ScriptEngine->RegisterObjectProperty("Bdy", (Temp01 + "int h").c_str(), asOFFSET(sBdy, h));
 ScriptEngine->RegisterObjectProperty("Bdy", (Temp01 + "int unkwn1").c_str(), asOFFSET(sBdy, unkwn1));
 ScriptEngine->RegisterObjectProperty("Bdy", (Temp01 + "int unkwn2").c_str(), asOFFSET(sBdy, unkwn2));
 ScriptEngine->RegisterObjectProperty("Bdy", (Temp01 + "int unkwn3").c_str(), asOFFSET(sBdy, unkwn3));
 ScriptEngine->RegisterObjectProperty("Bdy", (Temp01 + "int unkwn4").c_str(), asOFFSET(sBdy, unkwn4));
 ScriptEngine->RegisterObjectProperty("Bdy", (Temp01 + "int unkwn5").c_str(), asOFFSET(sBdy, unkwn5));

 ScriptEngine->RegisterObjectType("Frame", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "bool exists").c_str(), asOFFSET(sFrame, exists));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int pic").c_str(), asOFFSET(sFrame, pic));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int state").c_str(), asOFFSET(sFrame, state));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int wait").c_str(), asOFFSET(sFrame, wait));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int next").c_str(), asOFFSET(sFrame, next));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int dvx").c_str(), asOFFSET(sFrame, dvx));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int dvy").c_str(), asOFFSET(sFrame, dvy));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int dvz").c_str(), asOFFSET(sFrame, dvz));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn1").c_str(), asOFFSET(sFrame, unkwn1));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int hit_a").c_str(), asOFFSET(sFrame, hit_a));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int hit_d").c_str(), asOFFSET(sFrame, hit_d));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int hit_j").c_str(), asOFFSET(sFrame, hit_j));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int hit_Fa").c_str(), asOFFSET(sFrame, hit_Fa));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int hit_Ua").c_str(), asOFFSET(sFrame, hit_Ua));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int hit_Da").c_str(), asOFFSET(sFrame, hit_Da));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int hit_Fj").c_str(), asOFFSET(sFrame, hit_Fj));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int hit_Uj").c_str(), asOFFSET(sFrame, hit_Uj));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int hit_Dj").c_str(), asOFFSET(sFrame, hit_Dj));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int hit_ja").c_str(), asOFFSET(sFrame, hit_ja));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int mp").c_str(), asOFFSET(sFrame, mp));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int centerx").c_str(), asOFFSET(sFrame, centerx));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int centery").c_str(), asOFFSET(sFrame, centery));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "Opoint opoint").c_str(), asOFFSET(sFrame, opoint));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn2").c_str(), asOFFSET(sFrame, unkwn2));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn3").c_str(), asOFFSET(sFrame, unkwn3));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "Bpoint bpoint").c_str(), asOFFSET(sFrame, bpoint));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "Cpoint cpoint").c_str(), asOFFSET(sFrame, cpoint));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn4").c_str(), asOFFSET(sFrame, unkwn4));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn5").c_str(), asOFFSET(sFrame, unkwn5));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn6").c_str(), asOFFSET(sFrame, unkwn6));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "Wpoint wpoint").c_str(), asOFFSET(sFrame, wpoint));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn7").c_str(), asOFFSET(sFrame, unkwn7));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn8").c_str(), asOFFSET(sFrame, unkwn8));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn9").c_str(), asOFFSET(sFrame, unkwn9));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn10").c_str(), asOFFSET(sFrame, unkwn10));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn11").c_str(), asOFFSET(sFrame, unkwn11));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn12").c_str(), asOFFSET(sFrame, unkwn12));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn13").c_str(), asOFFSET(sFrame, unkwn13));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn14").c_str(), asOFFSET(sFrame, unkwn14));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn15").c_str(), asOFFSET(sFrame, unkwn15));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn16").c_str(), asOFFSET(sFrame, unkwn16));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn17").c_str(), asOFFSET(sFrame, unkwn17));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int itr_count").c_str(), asOFFSET(sFrame, itr_count));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int bdy_count").c_str(), asOFFSET(sFrame, bdy_count));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "ItrArray @itrs").c_str(), asOFFSET(sFrame, itrs));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "BdyArray @bdys").c_str(), asOFFSET(sFrame, bdys));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int itr_x").c_str(), asOFFSET(sFrame, itr_x));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int itr_y").c_str(), asOFFSET(sFrame, itr_y));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int itr_w").c_str(), asOFFSET(sFrame, itr_w));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int itr_h").c_str(), asOFFSET(sFrame, itr_h));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int bdy_x").c_str(), asOFFSET(sFrame, bdy_x));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int bdy_y").c_str(), asOFFSET(sFrame, bdy_y));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int bdy_w").c_str(), asOFFSET(sFrame, bdy_w));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int bdy_h").c_str(), asOFFSET(sFrame, bdy_h));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn18").c_str(), asOFFSET(sFrame, unkwn18));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "CharArray fname").c_str(), asOFFSET(sFrame, fname));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "CharArray @sound").c_str(), asOFFSET(sFrame, sound));
 ScriptEngine->RegisterObjectProperty("Frame", (Temp01 + "int unkwn19").c_str(), asOFFSET(sFrame, unkwn19));

 ScriptEngine->RegisterObjectType("DataFile", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "int walking_frame_rate").c_str(), asOFFSET(sDataFile, walking_frame_rate));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "int unkwn1").c_str(), asOFFSET(sDataFile, unkwn1));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "double walking_speed").c_str(), asOFFSET(sDataFile, walking_speed));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "double walking_speedz").c_str(), asOFFSET(sDataFile, walking_speedz));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "int running_frame_rate").c_str(), asOFFSET(sDataFile, running_frame_rate));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "double running_speed").c_str(), asOFFSET(sDataFile, running_speed));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "double running_speedz").c_str(), asOFFSET(sDataFile, running_speedz));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "double heavy_walking_speed").c_str(), asOFFSET(sDataFile, heavy_walking_speed));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "double heavy_walking_speedz").c_str(), asOFFSET(sDataFile, heavy_walking_speedz));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "double heavy_running_speed").c_str(), asOFFSET(sDataFile, heavy_running_speed));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "double heavy_running_speedz").c_str(), asOFFSET(sDataFile, heavy_running_speedz));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "double jump_height").c_str(), asOFFSET(sDataFile, jump_height));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "double jump_distance").c_str(), asOFFSET(sDataFile, jump_distance));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "double jump_distancez").c_str(), asOFFSET(sDataFile, jump_distancez));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "double dash_height").c_str(), asOFFSET(sDataFile, dash_height));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "double dash_distance").c_str(), asOFFSET(sDataFile, dash_distance));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "double dash_distancez").c_str(), asOFFSET(sDataFile, dash_distancez));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "double rowing_height").c_str(), asOFFSET(sDataFile, rowing_height));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "double rowing_distance").c_str(), asOFFSET(sDataFile, rowing_distance));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "int weapon_hp").c_str(), asOFFSET(sDataFile, weapon_hp));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "int weapon_drop_hurt").c_str(), asOFFSET(sDataFile, weapon_drop_hurt));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "CharArray unkwn2").c_str(), asOFFSET(sDataFile, unkwn2));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "int pic_count").c_str(), asOFFSET(sDataFile, pic_count));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "CharArrayArray40 pic_bmps").c_str(), asOFFSET(sDataFile, pic_bmps));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "IntArray pic_index").c_str(), asOFFSET(sDataFile, pic_index));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "IntArray pic_width").c_str(), asOFFSET(sDataFile, pic_width));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "IntArray pic_height").c_str(), asOFFSET(sDataFile, pic_height));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "IntArray pic_row").c_str(), asOFFSET(sDataFile, pic_row));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "IntArray pic_col").c_str(), asOFFSET(sDataFile, pic_col));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "int id").c_str(), asOFFSET(sDataFile, id));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "int type").c_str(), asOFFSET(sDataFile, type));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "int unkwn3").c_str(), asOFFSET(sDataFile, unkwn3));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "CharArray small_bmp").c_str(), asOFFSET(sDataFile, small_bmp));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "int unkwn4").c_str(), asOFFSET(sDataFile, unkwn4));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "CharArray face_bmp").c_str(), asOFFSET(sDataFile, face_bmp));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "IntArray unkwn5").c_str(), asOFFSET(sDataFile, unkwn5));
 ScriptEngine->RegisterObjectProperty("DataFile", (Temp01 + "FrameArray frames").c_str(), asOFFSET(sDataFile, frames));
 ScriptEngine->RegisterObjectMethod  ("DataFile", (Temp01 + "CharArray &get_name() const").c_str(), asFUNCTION(get_property < asOFFSET(sDataFile, name) >), asCALL_CDECL_OBJLAST);

 ScriptEngine->RegisterObjectType("Object", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int move_counter").c_str(), asOFFSET(sObject, move_counter));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int run_counter").c_str(), asOFFSET(sObject, run_counter));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int blink").c_str(), asOFFSET(sObject, blink));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int unkwn1").c_str(), asOFFSET(sObject, unkwn1));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int x").c_str(), asOFFSET(sObject, x));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int y").c_str(), asOFFSET(sObject, y));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int z").c_str(), asOFFSET(sObject, z));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn2").c_str(), asOFFSET(sObject, unkwn2));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "double x_acceleration").c_str(), asOFFSET(sObject, x_acceleration));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "double y_acceleration").c_str(), asOFFSET(sObject, y_acceleration));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "double z_acceleration").c_str(), asOFFSET(sObject, z_acceleration));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "double x_velocity").c_str(), asOFFSET(sObject, x_velocity));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "double y_velocity").c_str(), asOFFSET(sObject, y_velocity));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "double z_velocity").c_str(), asOFFSET(sObject, z_velocity));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "double x_real").c_str(), asOFFSET(sObject, x_real));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "double y_real").c_str(), asOFFSET(sObject, y_real));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "double z_real").c_str(), asOFFSET(sObject, z_real));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int frame1").c_str(), asOFFSET(sObject, frame1));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int frame2").c_str(), asOFFSET(sObject, frame2));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int frame3").c_str(), asOFFSET(sObject, frame3));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int frame4").c_str(), asOFFSET(sObject, frame4));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "bool facing").c_str(), asOFFSET(sObject, facing));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn3").c_str(), asOFFSET(sObject, unkwn3));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int wait_counter").c_str(), asOFFSET(sObject, wait_counter));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int ccatcher").c_str(), asOFFSET(sObject, ccatcher));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int ctimer").c_str(), asOFFSET(sObject, ctimer));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int weapon_type").c_str(), asOFFSET(sObject, weapon_type));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int weapon_held").c_str(), asOFFSET(sObject, weapon_held));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int weapon_holder").c_str(), asOFFSET(sObject, weapon_holder));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int unkwn4").c_str(), asOFFSET(sObject, unkwn4));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn5").c_str(), asOFFSET(sObject, unkwn5));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int fall").c_str(), asOFFSET(sObject, fall));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int shake").c_str(), asOFFSET(sObject, shake));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int bdefend").c_str(), asOFFSET(sObject, bdefend));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn6").c_str(), asOFFSET(sObject, unkwn6));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "bool holding_up").c_str(), asOFFSET(sObject, holding_up));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "bool holding_down").c_str(), asOFFSET(sObject, holding_down));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "bool holding_left").c_str(), asOFFSET(sObject, holding_left));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "bool holding_right").c_str(), asOFFSET(sObject, holding_right));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "bool holding_a").c_str(), asOFFSET(sObject, holding_a));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "bool holding_j").c_str(), asOFFSET(sObject, holding_j));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "bool holding_d").c_str(), asOFFSET(sObject, holding_d));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "bool up").c_str(), asOFFSET(sObject, up));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "bool down").c_str(), asOFFSET(sObject, down));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "bool left").c_str(), asOFFSET(sObject, left));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "bool right").c_str(), asOFFSET(sObject, right));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "bool A").c_str(), asOFFSET(sObject, A));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "bool J").c_str(), asOFFSET(sObject, J));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "bool D").c_str(), asOFFSET(sObject, D));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int8 DrA").c_str(), asOFFSET(sObject, DrA));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int8 DlA").c_str(), asOFFSET(sObject, DlA));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int8 DuA").c_str(), asOFFSET(sObject, DuA));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int8 DdA").c_str(), asOFFSET(sObject, DdA));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int8 DrJ").c_str(), asOFFSET(sObject, DrJ));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int8 DlJ").c_str(), asOFFSET(sObject, DlJ));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int8 DuJ").c_str(), asOFFSET(sObject, DuJ));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int8 DdJ").c_str(), asOFFSET(sObject, DdJ));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int8 DJA").c_str(), asOFFSET(sObject, DJA));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn7").c_str(), asOFFSET(sObject, unkwn7));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int arest").c_str(), asOFFSET(sObject, arest));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "CharArray vrests").c_str(), asOFFSET(sObject, vrests));
	// Backwards compatibility for when vrests was called vrest + unkwn8.
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int vrest").c_str(), asOFFSET(sObject, vrests));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn8").c_str(), asOFFSET(sObject, vrests) + sizeof(int));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int attacked_object_num").c_str(), asOFFSET(sObject, attacked_object_num));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn9").c_str(), asOFFSET(sObject, unkwn9));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int clone").c_str(), asOFFSET(sObject, clone));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int weapon_thrower").c_str(), asOFFSET(sObject, weapon_thrower));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int hp").c_str(), asOFFSET(sObject, hp));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int dark_hp").c_str(), asOFFSET(sObject, dark_hp));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int max_hp").c_str(), asOFFSET(sObject, max_hp));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int mp").c_str(), asOFFSET(sObject, mp));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int reserve").c_str(), asOFFSET(sObject, reserve));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int unkwn10").c_str(), asOFFSET(sObject, unkwn10));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int unkwn11").c_str(), asOFFSET(sObject, unkwn11));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int pic_gain").c_str(), asOFFSET(sObject, pic_gain));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int bottle_hp").c_str(), asOFFSET(sObject, bottle_hp));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int throwinjury").c_str(), asOFFSET(sObject, throwinjury));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn12").c_str(), asOFFSET(sObject, unkwn12));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int firzen_counter").c_str(), asOFFSET(sObject, firzen_counter));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int unkwn13").c_str(), asOFFSET(sObject, unkwn13));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int armour_multiplier").c_str(), asOFFSET(sObject, armour_multiplier));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int unkwn14").c_str(), asOFFSET(sObject, unkwn14));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int total_attack").c_str(), asOFFSET(sObject, total_attack));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int hp_lost").c_str(), asOFFSET(sObject, hp_lost));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int mp_usage").c_str(), asOFFSET(sObject, mp_usage));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn15").c_str(), asOFFSET(sObject, unkwn15));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int kills").c_str(), asOFFSET(sObject, kills));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int weapon_picks").c_str(), asOFFSET(sObject, weapon_picks));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int enemy").c_str(), asOFFSET(sObject, enemy));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "int team").c_str(), asOFFSET(sObject, team));
 ScriptEngine->RegisterObjectProperty("Object", (Temp01 + "DataFile @data").c_str(), asOFFSET(sObject, data));
	
 ScriptEngine->RegisterObjectType("Spawn", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectProperty("Spawn", (Temp01 + "IntArray unkwn1").c_str(), asOFFSET(sSpawn, unkwn1));
 ScriptEngine->RegisterObjectProperty("Spawn", (Temp01 + "int id").c_str(), asOFFSET(sSpawn, id));
 ScriptEngine->RegisterObjectProperty("Spawn", (Temp01 + "int x").c_str(), asOFFSET(sSpawn, x));
 ScriptEngine->RegisterObjectProperty("Spawn", (Temp01 + "int hp").c_str(), asOFFSET(sSpawn, hp));
 ScriptEngine->RegisterObjectProperty("Spawn", (Temp01 + "int times").c_str(), asOFFSET(sSpawn, times));
 ScriptEngine->RegisterObjectProperty("Spawn", (Temp01 + "int reserve").c_str(), asOFFSET(sSpawn, reserve));
 ScriptEngine->RegisterObjectProperty("Spawn", (Temp01 + "int join").c_str(), asOFFSET(sSpawn, join));
 ScriptEngine->RegisterObjectProperty("Spawn", (Temp01 + "int join_reserve").c_str(), asOFFSET(sSpawn, join_reserve));
 ScriptEngine->RegisterObjectProperty("Spawn", (Temp01 + "int act").c_str(), asOFFSET(sSpawn, act));
 ScriptEngine->RegisterObjectProperty("Spawn", (Temp01 + "int unkwn2").c_str(), asOFFSET(sSpawn, unkwn2));
 ScriptEngine->RegisterObjectProperty("Spawn", (Temp01 + "double ratio").c_str(), asOFFSET(sSpawn, ratio));
 ScriptEngine->RegisterObjectProperty("Spawn", (Temp01 + "int role").c_str(), asOFFSET(sSpawn, role));
 ScriptEngine->RegisterObjectProperty("Spawn", (Temp01 + "int unkwn3").c_str(), asOFFSET(sSpawn, unkwn3));
		
 ScriptEngine->RegisterObjectType("Phase", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectProperty("Phase", (Temp01 + "int bound").c_str(), asOFFSET(sPhase,bound));
 ScriptEngine->RegisterObjectProperty("Phase", (Temp01 + "CharArray music").c_str(), asOFFSET(sPhase, music));
 ScriptEngine->RegisterObjectProperty("Phase", (Temp01 + "SpawnArray spawns").c_str(), asOFFSET(sPhase, spawns));
 ScriptEngine->RegisterObjectProperty("Phase", (Temp01 + "int when_clear_goto_phase").c_str(), asOFFSET(sPhase, when_clear_goto_phase));
		
 ScriptEngine->RegisterObjectType("Stage", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectProperty("Stage", (Temp01 + "int phase_count").c_str(), asOFFSET(sStage, phase_count));
 ScriptEngine->RegisterObjectProperty("Stage", (Temp01 + "PhaseArray phases").c_str(), asOFFSET(sStage, phases));

 ScriptEngine->RegisterObjectType("Background", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectProperty("Background", (Temp01 + "int bg_width").c_str(), asOFFSET(sBackground, bg_width));
 ScriptEngine->RegisterObjectProperty("Background", (Temp01 + "int bg_zwidth1").c_str(), asOFFSET(sBackground, bg_zwidth1));
 ScriptEngine->RegisterObjectProperty("Background", (Temp01 + "int bg_zwidth2").c_str(), asOFFSET(sBackground, bg_zwidth2));
 ScriptEngine->RegisterObjectProperty("Background", (Temp01 + "int perspective1").c_str(), asOFFSET(sBackground, perspective1));
 ScriptEngine->RegisterObjectProperty("Background", (Temp01 + "int perspective2").c_str(), asOFFSET(sBackground, perspective2));
 ScriptEngine->RegisterObjectProperty("Background", (Temp01 + "int shadow1").c_str(), asOFFSET(sBackground, shadow1));
 ScriptEngine->RegisterObjectProperty("Background", (Temp01 + "int shadow2").c_str(), asOFFSET(sBackground, shadow2));
 ScriptEngine->RegisterObjectProperty("Background", (Temp01 + "int layer_count").c_str(), asOFFSET(sBackground, layer_count));
 ScriptEngine->RegisterObjectProperty("Background", (Temp01 + "CharArrayArray30 layer_bmps").c_str(), asOFFSET(sBackground, layer_bmps));
 ScriptEngine->RegisterObjectProperty("Background", (Temp01 + "CharArray shadow_bmp").c_str(), asOFFSET(sBackground, shadow_bmp));
 ScriptEngine->RegisterObjectProperty("Background", (Temp01 + "CharArray name").c_str(), asOFFSET(sBackground, name));
 ScriptEngine->RegisterObjectProperty("Background", (Temp01 + "IntArray transparency").c_str(), asOFFSET(sBackground, transparency));
 ScriptEngine->RegisterObjectProperty("Background", (Temp01 + "IntArray layer_width").c_str(), asOFFSET(sBackground, layer_width));
 ScriptEngine->RegisterObjectProperty("Background", (Temp01 + "IntArray layer_x").c_str(), asOFFSET(sBackground, layer_x));
 ScriptEngine->RegisterObjectProperty("Background", (Temp01 + "IntArray layer_y").c_str(), asOFFSET(sBackground, layer_y));
 ScriptEngine->RegisterObjectProperty("Background", (Temp01 + "IntArray layer_height").c_str(), asOFFSET(sBackground, layer_height));
 ScriptEngine->RegisterObjectProperty("Background", (Temp01 + "CharArray unkwn1").c_str(), asOFFSET(sBackground, unkwn1));

 ScriptEngine->RegisterObjectType("FileManager", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectProperty("FileManager", (Temp01 + "DataFileArray datas").c_str(), asOFFSET(sFileManager, datas));
 ScriptEngine->RegisterObjectProperty("FileManager", "const IntArray data_ptrs", asOFFSET(sFileManager, datas));  // Allows to check whether or not a datafile exists. If it's != 0, the datafile exists.
 ScriptEngine->RegisterObjectProperty("FileManager", "const StageArray stages", asOFFSET(sFileManager, stages));
 ScriptEngine->RegisterObjectMethod  ("FileManager", "const BackgroundArray &get_backgrounds() const", asFUNCTION(get_property < asOFFSET(sFileManager, backgrounds) >), asCALL_CDECL_OBJLAST);

 ScriptEngine->RegisterObjectType("Game", 0, asOBJ_REF | asOBJ_NOCOUNT);
 ScriptEngine->RegisterObjectProperty("Game", "const int state", asOFFSET(sGame, state));
 ScriptEngine->RegisterObjectProperty("Game", "const BoolArray exists", asOFFSET(sGame, exists));
 ScriptEngine->RegisterObjectProperty("Game", (Temp01 + "ObjectArray objects").c_str(), asOFFSET(sGame, objects));
 ScriptEngine->RegisterObjectProperty("Game", "const FileManager @files", asOFFSET(sGame, files));

 ScriptEngine->RegisterObjectMethod("IntArray", (Temp01 + "int32 &opIndex(uint x) const").c_str(), asMETHOD(IntArray, opIndex), asCALL_THISCALL);
 ScriptEngine->RegisterObjectMethod("BoolArray", (Temp01 + "bool &opIndex(uint x) const").c_str(), asMETHOD(BoolArray, opIndex), asCALL_THISCALL);
 ScriptEngine->RegisterObjectMethod("CharArray", (Temp01 + "int8 &opIndex(uint x) const").c_str(), asMETHOD(CharArray, opIndex), asCALL_THISCALL);
 ScriptEngine->RegisterObjectMethod("CharArrayArray30", (Temp01 + "CharArray &opIndex(uint x) const").c_str(), asMETHOD(CharArrayArray, opIndex < 30 >), asCALL_THISCALL);
 ScriptEngine->RegisterObjectMethod("CharArrayArray40", (Temp01 + "CharArray &opIndex(uint x) const").c_str(), asMETHOD(CharArrayArray, opIndex < 40 >), asCALL_THISCALL);
 ScriptEngine->RegisterObjectMethod("DataFileArray", (Temp01 + "DataFile &opIndex(uint x) const").c_str(), asMETHOD(DataFileArray, opIndex), asCALL_THISCALL);
 ScriptEngine->RegisterObjectMethod("ObjectArray", (Temp01 + "Object &opIndex(uint x) const").c_str(), asMETHOD(ObjectArray, opIndex), asCALL_THISCALL);
 ScriptEngine->RegisterObjectMethod("FrameArray", (Temp01 + "Frame &opIndex(uint x) const").c_str(), asMETHOD(FrameArray, opIndex), asCALL_THISCALL);
 ScriptEngine->RegisterObjectMethod("BackgroundArray", (Temp01 + "Background &opIndex(uint x) const").c_str(), asMETHOD(BackgroundArray, opIndex), asCALL_THISCALL);
 ScriptEngine->RegisterObjectMethod("SpawnArray", (Temp01 + "Spawn &opIndex(uint x) const").c_str(), asMETHOD(SpawnArray, opIndex), asCALL_THISCALL);
 ScriptEngine->RegisterObjectMethod("PhaseArray", (Temp01 + "Phase &opIndex(uint x) const").c_str(), asMETHOD(PhaseArray, opIndex), asCALL_THISCALL);
 ScriptEngine->RegisterObjectMethod("StageArray", (Temp01 + "Stage &opIndex(uint x) const").c_str(), asMETHOD(StageArray, opIndex), asCALL_THISCALL);
 ScriptEngine->RegisterObjectMethod("ItrArray", (Temp01 + "Itr &opIndex(uint x) const").c_str(), asMETHOD(ItrArray, opIndex), asCALL_THISCALL);
 ScriptEngine->RegisterObjectMethod("BdyArray", (Temp01 + "Bdy &opIndex(uint x) const").c_str(), asMETHOD(BdyArray, opIndex), asCALL_THISCALL);
}