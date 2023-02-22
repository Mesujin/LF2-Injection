#include "gamearrays.h"
#include <string>

#ifdef _MD_OLD_SCRIPT
 template < int offset > void    *get_property(void *self)                 noexcept {return (void*)((char*)self + offset);} // AngelScript does not support offsets larger than 0x7fff, and when that is the case, we use this function instead.
 char                            *CharArray::opIndex(unsigned int x)       noexcept {return (((char*)this) + x);}
 template < int size > CharArray *CharArrayArray::opIndex(unsigned int x)  noexcept {return (CharArray*)(((char*)this) + x * size);}
 int                             *IntArray::opIndex(unsigned int x)        noexcept {return (((int*)this) + x);}
 bool                            *BoolArray::opIndex(unsigned int x)       noexcept {return (((bool*)this) + x);}
 sItr                            *ItrArray::opIndex(unsigned int x)        noexcept {return ((sItr*)this) + x;}
 sBdy                            *BdyArray::opIndex(unsigned int x)        noexcept {return ((sBdy*)this) + x;}
 sDataFile                       *DataFileArray::opIndex(unsigned int x)   noexcept {return *(((sDataFile**)this) + x);}
 sObject                         *ObjectArray::opIndex(unsigned int x)     noexcept {return *(((sObject**)this) + x);}
 sFrame                          *FrameArray::opIndex(unsigned int x)      noexcept {return ((sFrame*)this) + x;}
 sLayer                          *LayerArray::opIndex(unsigned int x)      noexcept {return (sLayer*)(((int*)this) + x);}
 sBackground                     *BackgroundArray::opIndex(unsigned int x) noexcept {return ((sBackground*)this) + x;}
 sSpawn                          *SpawnArray::opIndex(unsigned int x)      noexcept {return ((sSpawn*)this) + x;}
 sPhase                          *PhaseArray::opIndex(unsigned int x)      noexcept {return ((sPhase*)this) + x;}
 sStage                          *StageArray::opIndex(unsigned int x)      noexcept {return ((sStage*)this) + x;}
#endif

#pragma warning (disable : 26481) // We're safe to access any offset in this case.
 template < int Vrab01 > void          *Property(void *Vrab02)                            noexcept {return (void*)((char*)Vrab02 + Vrab01);} // AngelScript does not support offsets larger than 0x7fff, and when that is the case, we use this function instead.
 bool                                  *MD_ARRAY_INT1::opIndex(unsigned int Vrab01)       noexcept {return (((bool*)this) + Vrab01);}
 char                                  *MD_ARRAY_INT8::opIndex(unsigned int Vrab01)       noexcept {return (((char*)this) + Vrab01);}
 int                                   *MD_ARRAY_INT32::opIndex(unsigned int Vrab01)      noexcept {return (((int*)this) + Vrab01);}
 template < int Vrab01 > MD_ARRAY_INT8 *MD_ARRAY_ARRAY_INT8::opIndex(unsigned int Vrab02) noexcept {return (MD_ARRAY_INT8*)(((char*)this) + (Vrab02 * Vrab01));}
 MD_OBJECT                             *MD_ARRAY_OBJECT::opIndex(unsigned int Vrab01)     noexcept {return *(((MD_OBJECT**)this) + Vrab01);}
 MD_DATA                               *MD_ARRAY_DATA::opIndex(unsigned int Vrab01)       noexcept {return *(((MD_DATA**)this) + Vrab01);}
 MD_FILE                               *MD_ARRAY_FILE::opIndex(unsigned int Vrab01)       noexcept {return (MD_FILE*)(((int*)this) + Vrab01);}
 MD_ENTRY                              *MD_ARRAY_ENTRY::opIndex(unsigned int Vrab01)      noexcept {return ((MD_ENTRY*)this) + Vrab01;}
 MD_FRAME                              *MD_ARRAY_FRAME::opIndex(unsigned int Vrab01)      noexcept {return ((MD_FRAME*)this) + Vrab01;}
 MD_ITR                                *MD_ARRAY_ITR::opIndex(unsigned int Vrab01)        noexcept {return ((MD_ITR*)this) + Vrab01;}
 MD_BDY                                *MD_ARRAY_BDY::opIndex(unsigned int Vrab01)        noexcept {return ((MD_BDY*)this) + Vrab01;}
 MD_BACKGROUND                         *MD_ARRAY_BACKGROUND::opIndex(unsigned int Vrab01) noexcept {return ((MD_BACKGROUND*)this) + Vrab01;}
 MD_LAYER                              *MD_ARRAY_LAYER::opIndex(unsigned int Vrab01)      noexcept {return (MD_LAYER*)(((int*)this) + Vrab01);}
 MD_STAGE                              *MD_ARRAY_STAGE::opIndex(unsigned int Vrab01)      noexcept {return ((MD_STAGE*)this) + Vrab01;}
 MD_PHASE                              *MD_ARRAY_PHASE::opIndex(unsigned int Vrab01)      noexcept {return ((MD_PHASE*)this) + Vrab01;}
 MD_SPAWN                              *MD_ARRAY_SPAWN::opIndex(unsigned int Vrab01)      noexcept {return ((MD_SPAWN*)this) + Vrab01;}

void RegisterGameArrays(asIScriptEngine *Engi01, bool Vrab01)
{
 std::string Temp01 = "const ";
 if(Vrab01) Temp01 = "";
 
 #ifdef _MD_OLD_SCRIPT
 Engi01->RegisterObjectType("BoolArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("CharArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("CharArrayArray30", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("CharArrayArray40", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("IntArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("ItrArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("BdyArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("DataFileArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("ObjectArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("FrameArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("LayerArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("BackgroundArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("SpawnArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("PhaseArray", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("StageArray", 0, asOBJ_REF | asOBJ_NOCOUNT);

 Engi01->RegisterObjectType("Opoint", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectProperty("Opoint", (Temp01 + "int kind").c_str(), asOFFSET(sOpoint, kind));
 Engi01->RegisterObjectProperty("Opoint", (Temp01 + "int x").c_str(), asOFFSET(sOpoint, x));
 Engi01->RegisterObjectProperty("Opoint", (Temp01 + "int y").c_str(), asOFFSET(sOpoint, y));
 Engi01->RegisterObjectProperty("Opoint", (Temp01 + "int action").c_str(), asOFFSET(sOpoint, action));
 Engi01->RegisterObjectProperty("Opoint", (Temp01 + "int dvx").c_str(), asOFFSET(sOpoint, dvx));
 Engi01->RegisterObjectProperty("Opoint", (Temp01 + "int dvy").c_str(), asOFFSET(sOpoint, dvy));
 Engi01->RegisterObjectProperty("Opoint", (Temp01 + "int oid").c_str(), asOFFSET(sOpoint, oid));
 Engi01->RegisterObjectProperty("Opoint", (Temp01 + "int facing").c_str(), asOFFSET(sOpoint, facing));
    
 Engi01->RegisterObjectType("Bpoint", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectProperty("Bpoint", (Temp01 + "int x").c_str(), asOFFSET(sBpoint, x));
 Engi01->RegisterObjectProperty("Bpoint", (Temp01 + "int y").c_str(), asOFFSET(sBpoint, y));

 Engi01->RegisterObjectType("Cpoint", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectProperty("Cpoint", (Temp01 + "int kind").c_str(), asOFFSET(sCpoint, kind));
 Engi01->RegisterObjectProperty("Cpoint", (Temp01 + "int x").c_str(), asOFFSET(sCpoint, x));
 Engi01->RegisterObjectProperty("Cpoint", (Temp01 + "int y").c_str(), asOFFSET(sCpoint, y));
 Engi01->RegisterObjectProperty("Cpoint", (Temp01 + "int injury").c_str(), asOFFSET(sCpoint, injury)); // If its kind 2 this is fronthurtact.
 Engi01->RegisterObjectProperty("Cpoint", (Temp01 + "int cover").c_str(), asOFFSET(sCpoint, cover));   // If its kind 2 this is backhurtact.
 Engi01->RegisterObjectProperty("Cpoint", (Temp01 + "int vaction").c_str(), asOFFSET(sCpoint, vaction));
 Engi01->RegisterObjectProperty("Cpoint", (Temp01 + "int aaction").c_str(), asOFFSET(sCpoint, aaction));
 Engi01->RegisterObjectProperty("Cpoint", (Temp01 + "int jaction").c_str(), asOFFSET(sCpoint, jaction));
 Engi01->RegisterObjectProperty("Cpoint", (Temp01 + "int daction").c_str(), asOFFSET(sCpoint, daction));
 Engi01->RegisterObjectProperty("Cpoint", (Temp01 + "int throwvx").c_str(), asOFFSET(sCpoint, throwvx));
 Engi01->RegisterObjectProperty("Cpoint", (Temp01 + "int throwvy").c_str(), asOFFSET(sCpoint, throwvy));
 Engi01->RegisterObjectProperty("Cpoint", (Temp01 + "int hurtable").c_str(), asOFFSET(sCpoint, hurtable));
 Engi01->RegisterObjectProperty("Cpoint", (Temp01 + "int decrease").c_str(), asOFFSET(sCpoint, decrease));
 Engi01->RegisterObjectProperty("Cpoint", (Temp01 + "int dircontrol").c_str(), asOFFSET(sCpoint, dircontrol));
 Engi01->RegisterObjectProperty("Cpoint", (Temp01 + "int taction").c_str(), asOFFSET(sCpoint, taction));
 Engi01->RegisterObjectProperty("Cpoint", (Temp01 + "int throwinjury").c_str(), asOFFSET(sCpoint, throwinjury));
 Engi01->RegisterObjectProperty("Cpoint", (Temp01 + "int throwvz").c_str(), asOFFSET(sCpoint, throwvz));

 Engi01->RegisterObjectType("Wpoint", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectProperty("Wpoint", (Temp01 + "int kind").c_str(), asOFFSET(sWpoint, kind));
 Engi01->RegisterObjectProperty("Wpoint", (Temp01 + "int x").c_str(), asOFFSET(sWpoint, x));
 Engi01->RegisterObjectProperty("Wpoint", (Temp01 + "int y").c_str(), asOFFSET(sWpoint, y));
 Engi01->RegisterObjectProperty("Wpoint", (Temp01 + "int weaponact").c_str(), asOFFSET(sWpoint, weaponact));
 Engi01->RegisterObjectProperty("Wpoint", (Temp01 + "int attacking").c_str(), asOFFSET(sWpoint, attacking));
 Engi01->RegisterObjectProperty("Wpoint", (Temp01 + "int cover").c_str(), asOFFSET(sWpoint, cover));
 Engi01->RegisterObjectProperty("Wpoint", (Temp01 + "int dvx").c_str(), asOFFSET(sWpoint, dvx));
 Engi01->RegisterObjectProperty("Wpoint", (Temp01 + "int dvy").c_str(), asOFFSET(sWpoint, dvy));
 Engi01->RegisterObjectProperty("Wpoint", (Temp01 + "int dvz").c_str(), asOFFSET(sWpoint, dvz));

 Engi01->RegisterObjectType("Itr", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int kind").c_str(), asOFFSET(sItr, kind));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int x").c_str(), asOFFSET(sItr, x));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int y").c_str(), asOFFSET(sItr, y));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int w").c_str(), asOFFSET(sItr, w));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int h").c_str(), asOFFSET(sItr, h));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int dvx").c_str(), asOFFSET(sItr, dvx));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int dvy").c_str(), asOFFSET(sItr, dvy));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int fall").c_str(), asOFFSET(sItr, fall));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int arest").c_str(), asOFFSET(sItr, arest));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int vrest").c_str(), asOFFSET(sItr, vrest));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int unkwn1").c_str(), asOFFSET(sItr, unkwn1));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int effect").c_str(), asOFFSET(sItr, effect));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int catchingact1").c_str(), asOFFSET(sItr, catchingact1));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int catchingact2").c_str(), asOFFSET(sItr, catchingact2));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int caughtact1").c_str(), asOFFSET(sItr, caughtact1));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int caughtact2").c_str(), asOFFSET(sItr, caughtact2));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int bdefend").c_str(), asOFFSET(sItr, bdefend));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int injury").c_str(), asOFFSET(sItr, injury));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int zwidth").c_str(), asOFFSET(sItr, zwidth));
 Engi01->RegisterObjectProperty("Itr", (Temp01 + "int unkwn2").c_str(), asOFFSET(sItr, unkwn2));

 Engi01->RegisterObjectType("Bdy", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectProperty("Bdy", (Temp01 + "int kind").c_str(), asOFFSET(sBdy, kind));
 Engi01->RegisterObjectProperty("Bdy", (Temp01 + "int x").c_str(), asOFFSET(sBdy, x));
 Engi01->RegisterObjectProperty("Bdy", (Temp01 + "int y").c_str(), asOFFSET(sBdy, y));
 Engi01->RegisterObjectProperty("Bdy", (Temp01 + "int w").c_str(), asOFFSET(sBdy, w));
 Engi01->RegisterObjectProperty("Bdy", (Temp01 + "int h").c_str(), asOFFSET(sBdy, h));
 Engi01->RegisterObjectProperty("Bdy", (Temp01 + "int unkwn1").c_str(), asOFFSET(sBdy, unkwn1));
 Engi01->RegisterObjectProperty("Bdy", (Temp01 + "int unkwn2").c_str(), asOFFSET(sBdy, unkwn2));
 Engi01->RegisterObjectProperty("Bdy", (Temp01 + "int unkwn3").c_str(), asOFFSET(sBdy, unkwn3));
 Engi01->RegisterObjectProperty("Bdy", (Temp01 + "int unkwn4").c_str(), asOFFSET(sBdy, unkwn4));
 Engi01->RegisterObjectProperty("Bdy", (Temp01 + "int unkwn5").c_str(), asOFFSET(sBdy, unkwn5));

 Engi01->RegisterObjectType("Frame", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "bool exists").c_str(), asOFFSET(sFrame, exists));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int pic").c_str(), asOFFSET(sFrame, pic));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int state").c_str(), asOFFSET(sFrame, state));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int wait").c_str(), asOFFSET(sFrame, wait));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int next").c_str(), asOFFSET(sFrame, next));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int dvx").c_str(), asOFFSET(sFrame, dvx));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int dvy").c_str(), asOFFSET(sFrame, dvy));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int dvz").c_str(), asOFFSET(sFrame, dvz));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn1").c_str(), asOFFSET(sFrame, unkwn1));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int hit_a").c_str(), asOFFSET(sFrame, hit_a));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int hit_d").c_str(), asOFFSET(sFrame, hit_d));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int hit_j").c_str(), asOFFSET(sFrame, hit_j));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int hit_Fa").c_str(), asOFFSET(sFrame, hit_Fa));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int hit_Ua").c_str(), asOFFSET(sFrame, hit_Ua));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int hit_Da").c_str(), asOFFSET(sFrame, hit_Da));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int hit_Fj").c_str(), asOFFSET(sFrame, hit_Fj));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int hit_Uj").c_str(), asOFFSET(sFrame, hit_Uj));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int hit_Dj").c_str(), asOFFSET(sFrame, hit_Dj));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int hit_ja").c_str(), asOFFSET(sFrame, hit_ja));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int mp").c_str(), asOFFSET(sFrame, mp));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int centerx").c_str(), asOFFSET(sFrame, centerx));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int centery").c_str(), asOFFSET(sFrame, centery));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "Opoint opoint").c_str(), asOFFSET(sFrame, opoint));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn2").c_str(), asOFFSET(sFrame, unkwn2));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn3").c_str(), asOFFSET(sFrame, unkwn3));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "Bpoint bpoint").c_str(), asOFFSET(sFrame, bpoint));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "Cpoint cpoint").c_str(), asOFFSET(sFrame, cpoint));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn4").c_str(), asOFFSET(sFrame, unkwn4));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn5").c_str(), asOFFSET(sFrame, unkwn5));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn6").c_str(), asOFFSET(sFrame, unkwn6));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "Wpoint wpoint").c_str(), asOFFSET(sFrame, wpoint));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn7").c_str(), asOFFSET(sFrame, unkwn7));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn8").c_str(), asOFFSET(sFrame, unkwn8));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn9").c_str(), asOFFSET(sFrame, unkwn9));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn10").c_str(), asOFFSET(sFrame, unkwn10));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn11").c_str(), asOFFSET(sFrame, unkwn11));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn12").c_str(), asOFFSET(sFrame, unkwn12));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn13").c_str(), asOFFSET(sFrame, unkwn13));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn14").c_str(), asOFFSET(sFrame, unkwn14));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn15").c_str(), asOFFSET(sFrame, unkwn15));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn16").c_str(), asOFFSET(sFrame, unkwn16));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn17").c_str(), asOFFSET(sFrame, unkwn17));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int itr_count").c_str(), asOFFSET(sFrame, itr_count));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int bdy_count").c_str(), asOFFSET(sFrame, bdy_count));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "ItrArray @itrs").c_str(), asOFFSET(sFrame, itrs));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "BdyArray @bdys").c_str(), asOFFSET(sFrame, bdys));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int itr_x").c_str(), asOFFSET(sFrame, itr_x));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int itr_y").c_str(), asOFFSET(sFrame, itr_y));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int itr_w").c_str(), asOFFSET(sFrame, itr_w));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int itr_h").c_str(), asOFFSET(sFrame, itr_h));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int bdy_x").c_str(), asOFFSET(sFrame, bdy_x));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int bdy_y").c_str(), asOFFSET(sFrame, bdy_y));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int bdy_w").c_str(), asOFFSET(sFrame, bdy_w));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int bdy_h").c_str(), asOFFSET(sFrame, bdy_h));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn18").c_str(), asOFFSET(sFrame, unkwn18));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "CharArray fname").c_str(), asOFFSET(sFrame, fname));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "CharArray @sound").c_str(), asOFFSET(sFrame, sound));
 Engi01->RegisterObjectProperty("Frame", (Temp01 + "int unkwn19").c_str(), asOFFSET(sFrame, unkwn19));

 Engi01->RegisterObjectType("DataFile", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "int walking_frame_rate").c_str(), asOFFSET(sDataFile, walking_frame_rate));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "int unkwn1").c_str(), asOFFSET(sDataFile, unkwn1));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "double walking_speed").c_str(), asOFFSET(sDataFile, walking_speed));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "double walking_speedz").c_str(), asOFFSET(sDataFile, walking_speedz));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "int running_frame_rate").c_str(), asOFFSET(sDataFile, running_frame_rate));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "double running_speed").c_str(), asOFFSET(sDataFile, running_speed));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "double running_speedz").c_str(), asOFFSET(sDataFile, running_speedz));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "double heavy_walking_speed").c_str(), asOFFSET(sDataFile, heavy_walking_speed));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "double heavy_walking_speedz").c_str(), asOFFSET(sDataFile, heavy_walking_speedz));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "double heavy_running_speed").c_str(), asOFFSET(sDataFile, heavy_running_speed));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "double heavy_running_speedz").c_str(), asOFFSET(sDataFile, heavy_running_speedz));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "double jump_height").c_str(), asOFFSET(sDataFile, jump_height));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "double jump_distance").c_str(), asOFFSET(sDataFile, jump_distance));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "double jump_distancez").c_str(), asOFFSET(sDataFile, jump_distancez));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "double dash_height").c_str(), asOFFSET(sDataFile, dash_height));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "double dash_distance").c_str(), asOFFSET(sDataFile, dash_distance));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "double dash_distancez").c_str(), asOFFSET(sDataFile, dash_distancez));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "double rowing_height").c_str(), asOFFSET(sDataFile, rowing_height));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "double rowing_distance").c_str(), asOFFSET(sDataFile, rowing_distance));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "int weapon_hp").c_str(), asOFFSET(sDataFile, weapon_hp));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "int weapon_drop_hurt").c_str(), asOFFSET(sDataFile, weapon_drop_hurt));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "CharArray unkwn2").c_str(), asOFFSET(sDataFile, unkwn2));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "int pic_count").c_str(), asOFFSET(sDataFile, pic_count));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "CharArrayArray40 pic_bmps").c_str(), asOFFSET(sDataFile, pic_bmps));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "IntArray pic_index").c_str(), asOFFSET(sDataFile, pic_index));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "IntArray pic_width").c_str(), asOFFSET(sDataFile, pic_width));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "IntArray pic_height").c_str(), asOFFSET(sDataFile, pic_height));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "IntArray pic_row").c_str(), asOFFSET(sDataFile, pic_row));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "IntArray pic_col").c_str(), asOFFSET(sDataFile, pic_col));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "int id").c_str(), asOFFSET(sDataFile, id));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "int type").c_str(), asOFFSET(sDataFile, type));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "int unkwn3").c_str(), asOFFSET(sDataFile, unkwn3));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "CharArray small_bmp").c_str(), asOFFSET(sDataFile, small_bmp));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "int unkwn4").c_str(), asOFFSET(sDataFile, unkwn4));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "CharArray face_bmp").c_str(), asOFFSET(sDataFile, face_bmp));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "IntArray unkwn5").c_str(), asOFFSET(sDataFile, unkwn5));
 Engi01->RegisterObjectProperty("DataFile", (Temp01 + "FrameArray frames").c_str(), asOFFSET(sDataFile, frames));
 Engi01->RegisterObjectMethod  ("DataFile", (Temp01 + "CharArray &get_name() const").c_str(), asFUNCTION(get_property < asOFFSET(sDataFile, name) >), asCALL_CDECL_OBJLAST);

 Engi01->RegisterObjectType("Object", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int move_counter").c_str(), asOFFSET(sObject, move_counter));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int run_counter").c_str(), asOFFSET(sObject, run_counter));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int blink").c_str(), asOFFSET(sObject, blink));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int unkwn1").c_str(), asOFFSET(sObject, unkwn1));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int x").c_str(), asOFFSET(sObject, x));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int y").c_str(), asOFFSET(sObject, y));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int z").c_str(), asOFFSET(sObject, z));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn2").c_str(), asOFFSET(sObject, unkwn2));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "double x_acceleration").c_str(), asOFFSET(sObject, x_acceleration));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "double y_acceleration").c_str(), asOFFSET(sObject, y_acceleration));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "double z_acceleration").c_str(), asOFFSET(sObject, z_acceleration));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "double x_velocity").c_str(), asOFFSET(sObject, x_velocity));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "double y_velocity").c_str(), asOFFSET(sObject, y_velocity));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "double z_velocity").c_str(), asOFFSET(sObject, z_velocity));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "double x_real").c_str(), asOFFSET(sObject, x_real));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "double y_real").c_str(), asOFFSET(sObject, y_real));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "double z_real").c_str(), asOFFSET(sObject, z_real));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int frame1").c_str(), asOFFSET(sObject, frame1));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int frame2").c_str(), asOFFSET(sObject, frame2));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int frame3").c_str(), asOFFSET(sObject, frame3));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int frame4").c_str(), asOFFSET(sObject, frame4));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "bool facing").c_str(), asOFFSET(sObject, facing));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn3").c_str(), asOFFSET(sObject, unkwn3));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int wait_counter").c_str(), asOFFSET(sObject, wait_counter));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int ccatcher").c_str(), asOFFSET(sObject, ccatcher));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int ctimer").c_str(), asOFFSET(sObject, catch_decrease));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int catch_by").c_str(), asOFFSET(sObject, ctimer));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int catch_decrease").c_str(), asOFFSET(sObject, catch_decrease));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int weapon_type").c_str(), asOFFSET(sObject, weapon_type));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int weapon_held").c_str(), asOFFSET(sObject, weapon_held));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int weapon_holder").c_str(), asOFFSET(sObject, weapon_holder));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int unkwn4").c_str(), asOFFSET(sObject, unkwn4));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn5").c_str(), asOFFSET(sObject, unkwn5));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int fall").c_str(), asOFFSET(sObject, fall));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int shake").c_str(), asOFFSET(sObject, shake));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int bdefend").c_str(), asOFFSET(sObject, bdefend));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn6").c_str(), asOFFSET(sObject, unkwn6));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "bool holding_up").c_str(), asOFFSET(sObject, holding_up));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "bool holding_down").c_str(), asOFFSET(sObject, holding_down));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "bool holding_left").c_str(), asOFFSET(sObject, holding_left));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "bool holding_right").c_str(), asOFFSET(sObject, holding_right));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "bool holding_a").c_str(), asOFFSET(sObject, holding_a));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "bool holding_j").c_str(), asOFFSET(sObject, holding_j));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "bool holding_d").c_str(), asOFFSET(sObject, holding_d));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "bool up").c_str(), asOFFSET(sObject, up));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "bool down").c_str(), asOFFSET(sObject, down));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "bool left").c_str(), asOFFSET(sObject, left));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "bool right").c_str(), asOFFSET(sObject, right));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "bool A").c_str(), asOFFSET(sObject, A));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "bool J").c_str(), asOFFSET(sObject, J));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "bool D").c_str(), asOFFSET(sObject, D));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int8 DrA").c_str(), asOFFSET(sObject, DrA));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int8 DlA").c_str(), asOFFSET(sObject, DlA));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int8 DuA").c_str(), asOFFSET(sObject, DuA));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int8 DdA").c_str(), asOFFSET(sObject, DdA));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int8 DrJ").c_str(), asOFFSET(sObject, DrJ));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int8 DlJ").c_str(), asOFFSET(sObject, DlJ));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int8 DuJ").c_str(), asOFFSET(sObject, DuJ));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int8 DdJ").c_str(), asOFFSET(sObject, DdJ));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int8 DJA").c_str(), asOFFSET(sObject, DJA));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn7").c_str(), asOFFSET(sObject, unkwn7));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int arest").c_str(), asOFFSET(sObject, arest));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "CharArray vrests").c_str(), asOFFSET(sObject, vrests));
	// Backwards compatibility for when vrests was called vrest + unkwn8.
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int vrest").c_str(), asOFFSET(sObject, vrests));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn8").c_str(), asOFFSET(sObject, vrests) + sizeof(int));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int attacked_object_num").c_str(), asOFFSET(sObject, attacked_object_num));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn9").c_str(), asOFFSET(sObject, unkwn9));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int clone").c_str(), asOFFSET(sObject, clone));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int weapon_thrower").c_str(), asOFFSET(sObject, weapon_thrower));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int hp").c_str(), asOFFSET(sObject, hp));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int dark_hp").c_str(), asOFFSET(sObject, dark_hp));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int max_hp").c_str(), asOFFSET(sObject, max_hp));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int mp").c_str(), asOFFSET(sObject, mp));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int reserve").c_str(), asOFFSET(sObject, reserve));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int unkwn10").c_str(), asOFFSET(sObject, unkwn10));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int unkwn11").c_str(), asOFFSET(sObject, unkwn11));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int pic_gain").c_str(), asOFFSET(sObject, pic_gain));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int bottle_hp").c_str(), asOFFSET(sObject, bottle_hp));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int throwinjury").c_str(), asOFFSET(sObject, throwinjury));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn12").c_str(), asOFFSET(sObject, unkwn12));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int firzen_counter").c_str(), asOFFSET(sObject, firzen_counter));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int unkwn13").c_str(), asOFFSET(sObject, unkwn13));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int armour_multiplier").c_str(), asOFFSET(sObject, armour_multiplier));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int unkwn14").c_str(), asOFFSET(sObject, unkwn14));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int total_attack").c_str(), asOFFSET(sObject, total_attack));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int hp_lost").c_str(), asOFFSET(sObject, hp_lost));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int mp_usage").c_str(), asOFFSET(sObject, mp_usage));
             Engi01->RegisterObjectProperty("Object", (Temp01 + "CharArray unkwn15").c_str(), asOFFSET(sObject, unkwn15)); // Backward compatibility.
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int host").c_str(), asOFFSET(sObject, unkwn15));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int kills").c_str(), asOFFSET(sObject, kills));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int weapon_picks").c_str(), asOFFSET(sObject, weapon_picks));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int enemy").c_str(), asOFFSET(sObject, enemy));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "int team").c_str(), asOFFSET(sObject, team));
 Engi01->RegisterObjectProperty("Object", (Temp01 + "DataFile @data").c_str(), asOFFSET(sObject, data));
	
 Engi01->RegisterObjectType("Spawn", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectProperty("Spawn", (Temp01 + "IntArray unkwn1").c_str(), asOFFSET(sSpawn, unkwn1));
 Engi01->RegisterObjectProperty("Spawn", (Temp01 + "int id").c_str(), asOFFSET(sSpawn, id));
 Engi01->RegisterObjectProperty("Spawn", (Temp01 + "int x").c_str(), asOFFSET(sSpawn, x));
 Engi01->RegisterObjectProperty("Spawn", (Temp01 + "int hp").c_str(), asOFFSET(sSpawn, hp));
 Engi01->RegisterObjectProperty("Spawn", (Temp01 + "int times").c_str(), asOFFSET(sSpawn, times));
 Engi01->RegisterObjectProperty("Spawn", (Temp01 + "int reserve").c_str(), asOFFSET(sSpawn, reserve));
 Engi01->RegisterObjectProperty("Spawn", (Temp01 + "int join").c_str(), asOFFSET(sSpawn, join));
 Engi01->RegisterObjectProperty("Spawn", (Temp01 + "int join_reserve").c_str(), asOFFSET(sSpawn, join_reserve));
 Engi01->RegisterObjectProperty("Spawn", (Temp01 + "int act").c_str(), asOFFSET(sSpawn, act));
 Engi01->RegisterObjectProperty("Spawn", (Temp01 + "int unkwn2").c_str(), asOFFSET(sSpawn, unkwn2));
 Engi01->RegisterObjectProperty("Spawn", (Temp01 + "double ratio").c_str(), asOFFSET(sSpawn, ratio));
 Engi01->RegisterObjectProperty("Spawn", (Temp01 + "int role").c_str(), asOFFSET(sSpawn, role));
 Engi01->RegisterObjectProperty("Spawn", (Temp01 + "int unkwn3").c_str(), asOFFSET(sSpawn, unkwn3));
		
 Engi01->RegisterObjectType("Phase", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectProperty("Phase", (Temp01 + "int bound").c_str(), asOFFSET(sPhase,bound));
 Engi01->RegisterObjectProperty("Phase", (Temp01 + "CharArray music").c_str(), asOFFSET(sPhase, music));
 Engi01->RegisterObjectProperty("Phase", (Temp01 + "SpawnArray spawns").c_str(), asOFFSET(sPhase, spawns));
 Engi01->RegisterObjectProperty("Phase", (Temp01 + "int when_clear_goto_phase").c_str(), asOFFSET(sPhase, when_clear_goto_phase));
		
 Engi01->RegisterObjectType("Stage", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectProperty("Stage", (Temp01 + "int phase_count").c_str(), asOFFSET(sStage, phase_count));
 Engi01->RegisterObjectProperty("Stage", (Temp01 + "PhaseArray phases").c_str(), asOFFSET(sStage, phases));

 
 Engi01->RegisterObjectType("Layer", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectProperty("Layer", (Temp01 + "int transparency").c_str(), asOFFSET(sLayer, transparency));
 Engi01->RegisterObjectProperty("Layer", (Temp01 + "int width").c_str(), asOFFSET(sLayer, width));
 Engi01->RegisterObjectProperty("Layer", (Temp01 + "int x").c_str(), asOFFSET(sLayer, x));
 Engi01->RegisterObjectProperty("Layer", (Temp01 + "int y").c_str(), asOFFSET(sLayer, y));
 Engi01->RegisterObjectProperty("Layer", (Temp01 + "int height").c_str(), asOFFSET(sLayer, height));
 Engi01->RegisterObjectProperty("Layer", (Temp01 + "int loop").c_str(), asOFFSET(sLayer, loop));
 Engi01->RegisterObjectProperty("Layer", (Temp01 + "int c1").c_str(), asOFFSET(sLayer, c1));
 Engi01->RegisterObjectProperty("Layer", (Temp01 + "int c2").c_str(), asOFFSET(sLayer, c2));
 Engi01->RegisterObjectProperty("Layer", (Temp01 + "int cc").c_str(), asOFFSET(sLayer, cc));
 Engi01->RegisterObjectProperty("Layer", (Temp01 + "int animation").c_str(), asOFFSET(sLayer, animation));
 Engi01->RegisterObjectProperty("Layer", (Temp01 + "int rect").c_str(), asOFFSET(sLayer, rect));

 Engi01->RegisterObjectType("Background", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectProperty("Background", (Temp01 + "int bg_width").c_str(), asOFFSET(sBackground, bg_width));
 Engi01->RegisterObjectProperty("Background", (Temp01 + "int bg_zwidth1").c_str(), asOFFSET(sBackground, bg_zwidth1));
 Engi01->RegisterObjectProperty("Background", (Temp01 + "int bg_zwidth2").c_str(), asOFFSET(sBackground, bg_zwidth2));
 Engi01->RegisterObjectProperty("Background", (Temp01 + "int perspective1").c_str(), asOFFSET(sBackground, perspective1));
 Engi01->RegisterObjectProperty("Background", (Temp01 + "int perspective2").c_str(), asOFFSET(sBackground, perspective2));
 Engi01->RegisterObjectProperty("Background", (Temp01 + "int shadow1").c_str(), asOFFSET(sBackground, shadow1));
 Engi01->RegisterObjectProperty("Background", (Temp01 + "int shadow2").c_str(), asOFFSET(sBackground, shadow2));
 Engi01->RegisterObjectProperty("Background", (Temp01 + "int layer_count").c_str(), asOFFSET(sBackground, layer_count));
 Engi01->RegisterObjectProperty("Background", (Temp01 + "CharArrayArray30 layer_bmps").c_str(), asOFFSET(sBackground, layer_bmps));
 Engi01->RegisterObjectProperty("Background", (Temp01 + "CharArray shadow_bmp").c_str(), asOFFSET(sBackground, shadow_bmp));
 Engi01->RegisterObjectProperty("Background", (Temp01 + "CharArray unkwn1").c_str(), asOFFSET(sBackground, unknown_1));
 Engi01->RegisterObjectProperty("Background", (Temp01 + "CharArray name").c_str(), asOFFSET(sBackground, name));
 Engi01->RegisterObjectProperty("Background", (Temp01 + "CharArray unkwn2").c_str(), asOFFSET(sBackground, unknown_2));
 Engi01->RegisterObjectProperty("Background", (Temp01 + "LayerArray layer").c_str(), asOFFSET(sBackground, layer));
 Engi01->RegisterObjectProperty("Background", (Temp01 + "IntArray layer_ptrs").c_str(), asOFFSET(sBackground, layer_ptrs));
 Engi01->RegisterObjectProperty("Background", (Temp01 + "int ptr").c_str(), asOFFSET(sBackground, ptrs));

 Engi01->RegisterObjectType("FileManager", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectProperty("FileManager", (Temp01 + "DataFileArray datas").c_str(), asOFFSET(sFileManager, datas));
 Engi01->RegisterObjectProperty("FileManager", "const IntArray data_ptrs", asOFFSET(sFileManager, datas));  // Allows to check whether or not a datafile exists. If it's != 0, the datafile exists.
 Engi01->RegisterObjectProperty("FileManager", "const StageArray stages", asOFFSET(sFileManager, stages));
 Engi01->RegisterObjectMethod  ("FileManager", "const BackgroundArray &get_backgrounds() const", asFUNCTION(get_property < asOFFSET(sFileManager, backgrounds) >), asCALL_CDECL_OBJLAST);

 Engi01->RegisterObjectType("OGame", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectProperty("OGame", "const int state", asOFFSET(sGame, state));
 Engi01->RegisterObjectProperty("OGame", "const BoolArray exists", asOFFSET(sGame, exists));
 Engi01->RegisterObjectProperty("OGame", (Temp01 + "ObjectArray objects").c_str(), asOFFSET(sGame, objects));
 Engi01->RegisterObjectProperty("OGame", "const FileManager @files", asOFFSET(sGame, files));

 Engi01->RegisterObjectMethod("IntArray", (Temp01 + "int32 &opIndex(uint x) const").c_str(), asMETHOD(IntArray, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("BoolArray", (Temp01 + "bool &opIndex(uint x) const").c_str(), asMETHOD(BoolArray, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("CharArray", (Temp01 + "int8 &opIndex(uint x) const").c_str(), asMETHOD(CharArray, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("CharArrayArray30", (Temp01 + "CharArray &opIndex(uint x) const").c_str(), asMETHOD(CharArrayArray, opIndex < 30 >), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("CharArrayArray40", (Temp01 + "CharArray &opIndex(uint x) const").c_str(), asMETHOD(CharArrayArray, opIndex < 40 >), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("DataFileArray", (Temp01 + "DataFile &opIndex(uint x) const").c_str(), asMETHOD(DataFileArray, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("ObjectArray", (Temp01 + "Object &opIndex(uint x) const").c_str(), asMETHOD(ObjectArray, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("FrameArray", (Temp01 + "Frame &opIndex(uint x) const").c_str(), asMETHOD(FrameArray, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("LayerArray", (Temp01 + "Layer &opIndex(uint x) const").c_str(), asMETHOD(LayerArray, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("BackgroundArray", (Temp01 + "Background &opIndex(uint x) const").c_str(), asMETHOD(BackgroundArray, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("SpawnArray", (Temp01 + "Spawn &opIndex(uint x) const").c_str(), asMETHOD(SpawnArray, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("PhaseArray", (Temp01 + "Phase &opIndex(uint x) const").c_str(), asMETHOD(PhaseArray, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("StageArray", (Temp01 + "Stage &opIndex(uint x) const").c_str(), asMETHOD(StageArray, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("ItrArray", (Temp01 + "Itr &opIndex(uint x) const").c_str(), asMETHOD(ItrArray, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("BdyArray", (Temp01 + "Bdy &opIndex(uint x) const").c_str(), asMETHOD(BdyArray, opIndex), asCALL_THISCALL);
 #endif
 
 Engi01->RegisterObjectType("GAME", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("OBJECT", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("DATABASE", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("DATA", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("BMP", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("FILE", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("STRENGTH", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("ENTRY", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("FRAME", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("OPOINT", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("BPOINT", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("CPOINT", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("WPOINT", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("ITR", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("BDY", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("RECTANGLE", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("BACKGROUND", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("LAYER", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("STAGE", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("PHASE", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("SPAWN", 0, asOBJ_REF | asOBJ_NOCOUNT);

 Engi01->RegisterObjectType("array_bool", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("array_int8", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("array_int32", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("array_array30_int8", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("array_array40_int8", 0, asOBJ_REF | asOBJ_NOCOUNT);

 Engi01->RegisterObjectType("array_OBJECT", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("array_DATA", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("array_FILE", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("array_ENTRY", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("array_FRAME", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("array_ITR", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("array_BDY", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("array_BACKGROUND", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("array_LAYER", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("array_STAGE", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("array_PHASE", 0, asOBJ_REF | asOBJ_NOCOUNT);
 Engi01->RegisterObjectType("array_SPAWN", 0, asOBJ_REF | asOBJ_NOCOUNT);
 
 Engi01->RegisterObjectMethod("array_bool", (Temp01 + "bool &opIndex(uint32 Index) const").c_str(), asMETHOD(MD_ARRAY_INT1, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("array_int8", (Temp01 + "int8 &opIndex(uint32 Index) const").c_str(), asMETHOD(MD_ARRAY_INT8, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("array_int32", (Temp01 + "int32 &opIndex(uint32 Index) const").c_str(), asMETHOD(MD_ARRAY_INT32, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("array_array30_int8", (Temp01 + "array_int8 &opIndex(uint32 Index) const").c_str(), asMETHOD(MD_ARRAY_ARRAY_INT8, opIndex < 30 >), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("array_array40_int8", (Temp01 + "array_int8 &opIndex(uint32 Index) const").c_str(), asMETHOD(MD_ARRAY_ARRAY_INT8, opIndex < 40 >), asCALL_THISCALL);
 
 Engi01->RegisterObjectMethod("array_OBJECT", (Temp01 + "OBJECT &opIndex(uint32 Index) const").c_str(), asMETHOD(MD_ARRAY_OBJECT, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("array_DATA", (Temp01 + "DATA &opIndex(uint32 Index) const").c_str(), asMETHOD(MD_ARRAY_DATA, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("array_FILE", (Temp01 + "FILE &opIndex(uint32 Index) const").c_str(), asMETHOD(MD_ARRAY_FILE, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("array_ENTRY", (Temp01 + "ENTRY &opIndex(uint32 Index) const").c_str(), asMETHOD(MD_ARRAY_ENTRY, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("array_FRAME", (Temp01 + "FRAME &opIndex(uint32 Index) const").c_str(), asMETHOD(MD_ARRAY_FRAME, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("array_ITR", (Temp01 + "ITR &opIndex(uint32 Index) const").c_str(), asMETHOD(MD_ARRAY_ITR, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("array_BDY", (Temp01 + "BDY &opIndex(uint32 Index) const").c_str(), asMETHOD(MD_ARRAY_BDY, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("array_BACKGROUND", (Temp01 + "BACKGROUND &opIndex(uint32 Index) const").c_str(), asMETHOD(MD_ARRAY_BACKGROUND, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("array_LAYER", (Temp01 + "LAYER &opIndex(uint32 Index) const").c_str(), asMETHOD(MD_ARRAY_LAYER, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("array_STAGE", (Temp01 + "STAGE &opIndex(uint32 Index) const").c_str(), asMETHOD(MD_ARRAY_STAGE, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("array_PHASE", (Temp01 + "PHASE &opIndex(uint32 Index) const").c_str(), asMETHOD(MD_ARRAY_PHASE, opIndex), asCALL_THISCALL);
 Engi01->RegisterObjectMethod("array_SPAWN", (Temp01 + "SPAWN &opIndex(uint32 Index) const").c_str(), asMETHOD(MD_ARRAY_SPAWN, opIndex), asCALL_THISCALL);

 Engi01->RegisterObjectProperty("GAME", "const int32 State", asOFFSET(MD_GAME, State));
 Engi01->RegisterObjectProperty("GAME", "const array_bool Object_Exist", asOFFSET(MD_GAME, Object_Exist[0]));
 Engi01->RegisterObjectProperty("GAME", (Temp01 + "array_OBJECT Object").c_str(), asOFFSET(MD_GAME, Object[0]));
 Engi01->RegisterObjectProperty("GAME", "const DATABASE @Database", asOFFSET(MD_GAME, Database));
 
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Walk_Animation").c_str(), asOFFSET(MD_OBJECT, Walk_Animation));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Run_Animation").c_str(), asOFFSET(MD_OBJECT, Run_Animation));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Invisibility").c_str(), asOFFSET(MD_OBJECT, Invisibility));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "array_int8 Unknown_1").c_str(), asOFFSET(MD_OBJECT, Unknown_1[0]));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 X_Display").c_str(), asOFFSET(MD_OBJECT, X_Display));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Y_Display").c_str(), asOFFSET(MD_OBJECT, Y_Display));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Z_Display").c_str(), asOFFSET(MD_OBJECT, Z_Display));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "array_int8 Unknown_2").c_str(), asOFFSET(MD_OBJECT, Unknown_2[0]));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "double X_Acceleration").c_str(), asOFFSET(MD_OBJECT, X_Acceleration));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "double Y_Acceleration").c_str(), asOFFSET(MD_OBJECT, Y_Acceleration));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "double Z_Acceleration").c_str(), asOFFSET(MD_OBJECT, Z_Acceleration));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "double X_Velocity").c_str(), asOFFSET(MD_OBJECT, X_Velocity));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "double Y_Velocity").c_str(), asOFFSET(MD_OBJECT, Y_Velocity));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "double Z_Velocity").c_str(), asOFFSET(MD_OBJECT, Z_Velocity));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "double X").c_str(), asOFFSET(MD_OBJECT, X));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "double Y").c_str(), asOFFSET(MD_OBJECT, Y));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "double Z").c_str(), asOFFSET(MD_OBJECT, Z));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Frame").c_str(), asOFFSET(MD_OBJECT, Frame));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Frame_Hit").c_str(), asOFFSET(MD_OBJECT, Frame_Hit));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Frame_Calculation").c_str(), asOFFSET(MD_OBJECT, Frame_Calculation));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Frame_Last").c_str(), asOFFSET(MD_OBJECT, Frame_Last));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "bool Facing").c_str(), asOFFSET(MD_OBJECT, Facing));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "array_int8 Unknown_3").c_str(), asOFFSET(MD_OBJECT, Unknown_3[0]));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Wait").c_str(), asOFFSET(MD_OBJECT, Wait));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Catch").c_str(), asOFFSET(MD_OBJECT, Catch));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Caught").c_str(), asOFFSET(MD_OBJECT, Caught));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Catch_Decrease").c_str(), asOFFSET(MD_OBJECT, Catch_Decrease));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Held_Type").c_str(), asOFFSET(MD_OBJECT, Held_Type));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Held").c_str(), asOFFSET(MD_OBJECT, Held));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Holder").c_str(), asOFFSET(MD_OBJECT, Holder));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "array_int8 Unknown_4").c_str(), asOFFSET(MD_OBJECT, Unknown_4[0]));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Fall").c_str(), asOFFSET(MD_OBJECT, Fall));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Hitlag").c_str(), asOFFSET(MD_OBJECT, Hitlag));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Defend").c_str(), asOFFSET(MD_OBJECT, Defend));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "array_int8 Unknown_5").c_str(), asOFFSET(MD_OBJECT, Unknown_5[0]));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "bool Up_Hold").c_str(), asOFFSET(MD_OBJECT, Up_Hold));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "bool Down_Hold").c_str(), asOFFSET(MD_OBJECT, Down_Hold));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "bool Left_Hold").c_str(), asOFFSET(MD_OBJECT, Left_Hold));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "bool Right_Hold").c_str(), asOFFSET(MD_OBJECT, Right_Hold));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "bool A_Hold").c_str(), asOFFSET(MD_OBJECT, A_Hold));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "bool J_Hold").c_str(), asOFFSET(MD_OBJECT, J_Hold));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "bool D_Hold").c_str(), asOFFSET(MD_OBJECT, D_Hold));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "bool Up").c_str(), asOFFSET(MD_OBJECT, Up));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "bool Down").c_str(), asOFFSET(MD_OBJECT, Down));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "bool Left").c_str(), asOFFSET(MD_OBJECT, Left));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "bool Right").c_str(), asOFFSET(MD_OBJECT, Right));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "bool A").c_str(), asOFFSET(MD_OBJECT, A));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "bool J").c_str(), asOFFSET(MD_OBJECT, J));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "bool D").c_str(), asOFFSET(MD_OBJECT, D));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int8 Cast_DRA").c_str(), asOFFSET(MD_OBJECT, Cast_DRA));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int8 Cast_DLA").c_str(), asOFFSET(MD_OBJECT, Cast_DLA));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int8 Cast_DUA").c_str(), asOFFSET(MD_OBJECT, Cast_DUA));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int8 Cast_DDA").c_str(), asOFFSET(MD_OBJECT, Cast_DDA));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int8 Cast_DRJ").c_str(), asOFFSET(MD_OBJECT, Cast_DRJ));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int8 Cast_DLJ").c_str(), asOFFSET(MD_OBJECT, Cast_DLJ));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int8 Cast_DUJ").c_str(), asOFFSET(MD_OBJECT, Cast_DUJ));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int8 Cast_DDJ").c_str(), asOFFSET(MD_OBJECT, Cast_DDJ));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int8 Cast_DJA").c_str(), asOFFSET(MD_OBJECT, Cast_DJA));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "array_int8 Unknown_6").c_str(), asOFFSET(MD_OBJECT, Unknown_6[0]));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Heal").c_str(), asOFFSET(MD_OBJECT, Heal));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "array_int8 Unknown_7").c_str(), asOFFSET(MD_OBJECT, Unknown_7[0]));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Attack_Rest").c_str(), asOFFSET(MD_OBJECT, Attack_Rest));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "array_int8 Hit_Rest").c_str(), asOFFSET(MD_OBJECT, Hit_Rest[0]));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Last_Hit").c_str(), asOFFSET(MD_OBJECT, Last_Hit));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "array_int8 Unknown_8").c_str(), asOFFSET(MD_OBJECT, Unknown_8[0]));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Cloner").c_str(), asOFFSET(MD_OBJECT, Cloner));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Thrower").c_str(), asOFFSET(MD_OBJECT, Thrower));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Health").c_str(), asOFFSET(MD_OBJECT, Health));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Potential_Health").c_str(), asOFFSET(MD_OBJECT, Potential_Health));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Max_Health").c_str(), asOFFSET(MD_OBJECT, Max_Health));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Mana").c_str(), asOFFSET(MD_OBJECT, Mana));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Reserve").c_str(), asOFFSET(MD_OBJECT, Reserve));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "array_int8 Unknown_9").c_str(), asOFFSET(MD_OBJECT, Unknown_9[0]));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Pic_Offset").c_str(), asOFFSET(MD_OBJECT, Pic_Offset));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Drink_Health").c_str(), asOFFSET(MD_OBJECT, Drink_Health));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Thrown_Drop_Damage").c_str(), asOFFSET(MD_OBJECT, Thrown_Drop_Damage));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "array_int8 Unknown_10").c_str(), asOFFSET(MD_OBJECT, Unknown_10[0]));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Fusion").c_str(), asOFFSET(MD_OBJECT, Fusion));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "array_int8 Unknown_11").c_str(), asOFFSET(MD_OBJECT, Unknown_11[0]));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Defense").c_str(), asOFFSET(MD_OBJECT, Defense));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "array_int8 Unknown_12").c_str(), asOFFSET(MD_OBJECT, Unknown_12[0]));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Summary_Attack").c_str(), asOFFSET(MD_OBJECT, Summary_Attack));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Summary_HP_Lost").c_str(), asOFFSET(MD_OBJECT, Summary_HP_Lost));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Summary_MP_Usage").c_str(), asOFFSET(MD_OBJECT, Summary_MP_Usage));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Summary_Host").c_str(), asOFFSET(MD_OBJECT, Summary_Host));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Summary_Kill").c_str(), asOFFSET(MD_OBJECT, Summary_Kill));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Summary_Picking").c_str(), asOFFSET(MD_OBJECT, Summary_Picking));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Target").c_str(), asOFFSET(MD_OBJECT, Target));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "int32 Team").c_str(), asOFFSET(MD_OBJECT, Team));
 Engi01->RegisterObjectProperty("OBJECT", (Temp01 + "DATA @Data").c_str(), asOFFSET(MD_OBJECT, Data));

 Engi01->RegisterObjectProperty("DATABASE", (Temp01 + "array_DATA Data").c_str(), asOFFSET(MD_DATABASE, Data[0]));
 Engi01->RegisterObjectProperty("DATABASE", "const array_int32 Data_Ptr", asOFFSET(MD_DATABASE, Data[0]));  // Allows to check whether or not a datafile exists. If it's != 0, the datafile exists.
 Engi01->RegisterObjectProperty("DATABASE", "const array_STAGE Stage", asOFFSET(MD_DATABASE, Stage[0]));
 Engi01->RegisterObjectMethod  ("DATABASE", "const array_BACKGROUND &Background() const", asFUNCTION(Property < asOFFSET(MD_DATABASE, Background) >), asCALL_CDECL_OBJLAST);
 
 Engi01->RegisterObjectProperty("DATA", (Temp01 + "BMP Bmp").c_str(), NULL);
 Engi01->RegisterObjectProperty("DATA", (Temp01 + "STRENGTH Strength").c_str(), asOFFSET(MD_DATA, Strength));
 Engi01->RegisterObjectProperty("DATA", (Temp01 + "int32 id").c_str(), asOFFSET(MD_DATA, id));
 Engi01->RegisterObjectProperty("DATA", (Temp01 + "int32 type").c_str(), asOFFSET(MD_DATA, type));
 Engi01->RegisterObjectProperty("DATA", (Temp01 + "array_int8 Unknown_1").c_str(), asOFFSET(MD_DATA, Unknown_3[0]));
 Engi01->RegisterObjectProperty("DATA", (Temp01 + "array_int8 Unknown_2").c_str(), asOFFSET(MD_DATA, Unknown_4[0]));
 Engi01->RegisterObjectProperty("DATA", (Temp01 + "array_int8 Unknown_3").c_str(), asOFFSET(MD_DATA, Unknown_5[0]));
 Engi01->RegisterObjectProperty("DATA", (Temp01 + "array_FRAME Frame").c_str(), asOFFSET(MD_DATA, Frame[0]));

 Engi01->RegisterObjectProperty("BMP", (Temp01 + "int32 walking_frame_rate").c_str(), asOFFSET(MD_DATA, walking_frame_rate));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "array_int8 Unknown_1").c_str(), asOFFSET(MD_DATA, Unknown_1[0]));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "double walking_speed").c_str(), asOFFSET(MD_DATA, walking_speed));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "double walking_speedz").c_str(), asOFFSET(MD_DATA, walking_speedz));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "int32 running_frame_rate").c_str(), asOFFSET(MD_DATA, running_frame_rate));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "double running_speed").c_str(), asOFFSET(MD_DATA, running_speed));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "double running_speedz").c_str(), asOFFSET(MD_DATA, running_speedz));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "double heavy_walking_speed").c_str(), asOFFSET(MD_DATA, heavy_walking_speed));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "double heavy_walking_speedz").c_str(), asOFFSET(MD_DATA, heavy_walking_speedz));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "double heavy_running_speed").c_str(), asOFFSET(MD_DATA, heavy_running_speed));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "double heavy_running_speedz").c_str(), asOFFSET(MD_DATA, heavy_running_speedz));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "double jump_height").c_str(), asOFFSET(MD_DATA, jump_height));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "double jump_distance").c_str(), asOFFSET(MD_DATA, jump_distance));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "double jump_distancez").c_str(), asOFFSET(MD_DATA, jump_distancez));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "double dash_height").c_str(), asOFFSET(MD_DATA, dash_height));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "double dash_distance").c_str(), asOFFSET(MD_DATA, dash_distance));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "double dash_distancez").c_str(), asOFFSET(MD_DATA, dash_distancez));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "double rowing_height").c_str(), asOFFSET(MD_DATA, rowing_height));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "double rowing_distance").c_str(), asOFFSET(MD_DATA, rowing_distance));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "int32 weapon_hp").c_str(), asOFFSET(MD_DATA, weapon_hp));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "int32 weapon_drop_hurt").c_str(), asOFFSET(MD_DATA, weapon_drop_hurt));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "array_int8 Unknown_2").c_str(), asOFFSET(MD_DATA, Unknown_2[0]));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "array_int8 small").c_str(), asOFFSET(MD_DATA, small_[0]));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "array_int8 head").c_str(), asOFFSET(MD_DATA, head[0]));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "int32 file_Counts").c_str(), asOFFSET(MD_DATA, file_Count));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "array_array40_int8 file_Address").c_str(), asOFFSET(MD_DATA, file_Address[0][0]));
 Engi01->RegisterObjectProperty("BMP", (Temp01 + "array_FILE file").c_str(), asOFFSET(MD_DATA, file[0]));
 Engi01->RegisterObjectMethod  ("BMP", (Temp01 + "array_int8 &name() const").c_str(), asFUNCTION(Property < asOFFSET(MD_DATA, name) >), asCALL_CDECL_OBJLAST);
 
 Engi01->RegisterObjectProperty("FILE", (Temp01 + "int32 Index").c_str(), asOFFSET(MD_FILE, Index[0]));
 Engi01->RegisterObjectProperty("FILE", (Temp01 + "int32 w").c_str(), asOFFSET(MD_FILE, w[0]));
 Engi01->RegisterObjectProperty("FILE", (Temp01 + "int32 h").c_str(), asOFFSET(MD_FILE, h[0]));
 Engi01->RegisterObjectProperty("FILE", (Temp01 + "int32 row").c_str(), asOFFSET(MD_FILE, row[0]));
 Engi01->RegisterObjectProperty("FILE", (Temp01 + "int32 col").c_str(), asOFFSET(MD_FILE, col[0]));

 Engi01->RegisterObjectProperty("STRENGTH", (Temp01 + "array_ENTRY entry").c_str(), asOFFSET(MD_STRENGTH, entry[0]));
 Engi01->RegisterObjectProperty("STRENGTH", (Temp01 + "array_array30_int8 entry_Name").c_str(), asOFFSET(MD_STRENGTH, entry_Name[0][0]));
 Engi01->RegisterObjectProperty("STRENGTH", (Temp01 + "array_int8 Unknown_1").c_str(), asOFFSET(MD_STRENGTH, Unknown_1[0]));
 
 Engi01->RegisterObjectProperty("ENTRY", (Temp01 + "int32 dvx").c_str(), asOFFSET(MD_ENTRY, dvx));
 Engi01->RegisterObjectProperty("ENTRY", (Temp01 + "int32 dvy").c_str(), asOFFSET(MD_ENTRY, dvy));
 Engi01->RegisterObjectProperty("ENTRY", (Temp01 + "int32 fall").c_str(), asOFFSET(MD_ENTRY, fall));
 Engi01->RegisterObjectProperty("ENTRY", (Temp01 + "int32 arest").c_str(), asOFFSET(MD_ENTRY, arest));
 Engi01->RegisterObjectProperty("ENTRY", (Temp01 + "int32 vrest").c_str(), asOFFSET(MD_ENTRY, vrest));
 Engi01->RegisterObjectProperty("ENTRY", (Temp01 + "int32 respond").c_str(), asOFFSET(MD_ENTRY, respond));
 Engi01->RegisterObjectProperty("ENTRY", (Temp01 + "int32 effect").c_str(), asOFFSET(MD_ENTRY, effect));
 Engi01->RegisterObjectProperty("ENTRY", (Temp01 + "array_int8 Unknown_1").c_str(), asOFFSET(MD_ENTRY, Unknown_1[0]));
 Engi01->RegisterObjectProperty("ENTRY", (Temp01 + "int32 bdefend").c_str(), asOFFSET(MD_ENTRY, bdefend));
 Engi01->RegisterObjectProperty("ENTRY", (Temp01 + "int32 injury").c_str(), asOFFSET(MD_ENTRY, injury));
 Engi01->RegisterObjectProperty("ENTRY", (Temp01 + "int32 zwidth").c_str(), asOFFSET(MD_ENTRY, zwidth));
 Engi01->RegisterObjectProperty("ENTRY", (Temp01 + "array_int8 Unknown_2").c_str(), asOFFSET(MD_ENTRY, Unknown_2[0]));
 
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "bool Exist").c_str(), asOFFSET(MD_FRAME, Exist));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 pic").c_str(), asOFFSET(MD_FRAME, pic));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 state").c_str(), asOFFSET(MD_FRAME, state));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 wait").c_str(), asOFFSET(MD_FRAME, wait));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 next").c_str(), asOFFSET(MD_FRAME, next));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 dvx").c_str(), asOFFSET(MD_FRAME, dvx));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 dvy").c_str(), asOFFSET(MD_FRAME, dvy));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 dvz").c_str(), asOFFSET(MD_FRAME, dvz));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "array_int8 Unknown_1").c_str(), asOFFSET(MD_FRAME, Unknown_1[0]));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 hit_a").c_str(), asOFFSET(MD_FRAME, hit_a));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 hit_d").c_str(), asOFFSET(MD_FRAME, hit_d));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 hit_j").c_str(), asOFFSET(MD_FRAME, hit_j));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 hit_Fa").c_str(), asOFFSET(MD_FRAME, hit_Fa));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 hit_Ua").c_str(), asOFFSET(MD_FRAME, hit_Ua));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 hit_Da").c_str(), asOFFSET(MD_FRAME, hit_Da));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 hit_Fj").c_str(), asOFFSET(MD_FRAME, hit_Fj));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 hit_Uj").c_str(), asOFFSET(MD_FRAME, hit_Uj));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 hit_Dj").c_str(), asOFFSET(MD_FRAME, hit_Dj));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 hit_ja").c_str(), asOFFSET(MD_FRAME, hit_ja));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 mp").c_str(), asOFFSET(MD_FRAME, mp));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 centerx").c_str(), asOFFSET(MD_FRAME, centerx));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 centery").c_str(), asOFFSET(MD_FRAME, centery));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "OPOINT opoint").c_str(), asOFFSET(MD_FRAME, opoint));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "array_int8 Unknown_2").c_str(), asOFFSET(MD_FRAME, Unknown_2[0]));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "BPOINT bpoint").c_str(), asOFFSET(MD_FRAME, bpoint));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "CPOINT cpoint").c_str(), asOFFSET(MD_FRAME, cpoint));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "array_int8 Unknown_3").c_str(), asOFFSET(MD_FRAME, Unknown_3[0]));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "WPOINT wpoint").c_str(), asOFFSET(MD_FRAME, wpoint));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "array_int8 Unknown_4").c_str(), asOFFSET(MD_FRAME, Unknown_4[0]));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 itr_Count").c_str(), asOFFSET(MD_FRAME, itr_Count));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "int32 bdy_Count").c_str(), asOFFSET(MD_FRAME, bdy_Count));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "array_ITR @itr").c_str(), asOFFSET(MD_FRAME, itr));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "array_BDY @bdy").c_str(), asOFFSET(MD_FRAME, bdy));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "RECTANGLE itr_Rectangle").c_str(), asOFFSET(MD_FRAME, itr_Rectangle));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "RECTANGLE bdy_Rectangle").c_str(), asOFFSET(MD_FRAME, bdy_Rectangle));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "array_int8 Unknown_5").c_str(), asOFFSET(MD_FRAME, Unknown_5[0]));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "array_int8 Name").c_str(), asOFFSET(MD_FRAME, Name[0]));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "array_int8 @sound").c_str(), asOFFSET(MD_FRAME, sound));
 Engi01->RegisterObjectProperty("FRAME", (Temp01 + "array_int8 Unknown_6").c_str(), asOFFSET(MD_FRAME, Unknown_6[0]));
 
 Engi01->RegisterObjectProperty("OPOINT", (Temp01 + "int32 kind").c_str(), asOFFSET(MD_OPOINT, kind));
 Engi01->RegisterObjectProperty("OPOINT", (Temp01 + "int32 x").c_str(), asOFFSET(MD_OPOINT, x));
 Engi01->RegisterObjectProperty("OPOINT", (Temp01 + "int32 y").c_str(), asOFFSET(MD_OPOINT, y));
 Engi01->RegisterObjectProperty("OPOINT", (Temp01 + "int32 action").c_str(), asOFFSET(MD_OPOINT, action));
 Engi01->RegisterObjectProperty("OPOINT", (Temp01 + "int32 dvx").c_str(), asOFFSET(MD_OPOINT, dvx));
 Engi01->RegisterObjectProperty("OPOINT", (Temp01 + "int32 dvy").c_str(), asOFFSET(MD_OPOINT, dvy));
 Engi01->RegisterObjectProperty("OPOINT", (Temp01 + "int32 oid").c_str(), asOFFSET(MD_OPOINT, oid));
 Engi01->RegisterObjectProperty("OPOINT", (Temp01 + "int32 facing").c_str(), asOFFSET(MD_OPOINT, facing));
 
 Engi01->RegisterObjectProperty("BPOINT", (Temp01 + "int32 x").c_str(), asOFFSET(MD_BPOINT, x));
 Engi01->RegisterObjectProperty("BPOINT", (Temp01 + "int32 y").c_str(), asOFFSET(MD_BPOINT, y));
 
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 kind").c_str(), asOFFSET(MD_CPOINT, kind));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 x").c_str(), asOFFSET(MD_CPOINT, x));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 y").c_str(), asOFFSET(MD_CPOINT, y));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 injury").c_str(), asOFFSET(MD_CPOINT, injury_fronthurtact));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 cover").c_str(), asOFFSET(MD_CPOINT, cover_backhurtact));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 fronthurtact").c_str(), asOFFSET(MD_CPOINT, injury_fronthurtact));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 backhurtact").c_str(), asOFFSET(MD_CPOINT, cover_backhurtact));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 vaction").c_str(), asOFFSET(MD_CPOINT, vaction));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 aaction").c_str(), asOFFSET(MD_CPOINT, aaction));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 daction").c_str(), asOFFSET(MD_CPOINT, daction));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 jaction").c_str(), asOFFSET(MD_CPOINT, jaction));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 throwvx").c_str(), asOFFSET(MD_CPOINT, throwvx));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 throwvy").c_str(), asOFFSET(MD_CPOINT, throwvy));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 hurtable").c_str(), asOFFSET(MD_CPOINT, hurtable));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 decrease").c_str(), asOFFSET(MD_CPOINT, decrease));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 dircontrol").c_str(), asOFFSET(MD_CPOINT, dircontrol));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 taction").c_str(), asOFFSET(MD_CPOINT, taction));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 throwinjury").c_str(), asOFFSET(MD_CPOINT, throwinjury));
 Engi01->RegisterObjectProperty("CPOINT", (Temp01 + "int32 throwvz").c_str(), asOFFSET(MD_CPOINT, throwvz));
 
 Engi01->RegisterObjectProperty("WPOINT", (Temp01 + "int32 kind").c_str(), asOFFSET(MD_WPOINT, kind));
 Engi01->RegisterObjectProperty("WPOINT", (Temp01 + "int32 x").c_str(), asOFFSET(MD_WPOINT, x));
 Engi01->RegisterObjectProperty("WPOINT", (Temp01 + "int32 y").c_str(), asOFFSET(MD_WPOINT, y));
 Engi01->RegisterObjectProperty("WPOINT", (Temp01 + "int32 weaponact").c_str(), asOFFSET(MD_WPOINT, weaponact));
 Engi01->RegisterObjectProperty("WPOINT", (Temp01 + "int32 attacking").c_str(), asOFFSET(MD_WPOINT, attacking));
 Engi01->RegisterObjectProperty("WPOINT", (Temp01 + "int32 cover").c_str(), asOFFSET(MD_WPOINT, cover));
 Engi01->RegisterObjectProperty("WPOINT", (Temp01 + "int32 dvx").c_str(), asOFFSET(MD_WPOINT, dvx));
 Engi01->RegisterObjectProperty("WPOINT", (Temp01 + "int32 dvy").c_str(), asOFFSET(MD_WPOINT, dvy));
 Engi01->RegisterObjectProperty("WPOINT", (Temp01 + "int32 dvz").c_str(), asOFFSET(MD_WPOINT, dvz));
 
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "int32 kind").c_str(), asOFFSET(MD_ITR, kind));
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "int32 x").c_str(), asOFFSET(MD_ITR, x));
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "int32 y").c_str(), asOFFSET(MD_ITR, y));
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "int32 w").c_str(), asOFFSET(MD_ITR, w));
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "int32 h").c_str(), asOFFSET(MD_ITR, h));
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "int32 dvx").c_str(), asOFFSET(MD_ITR, dvx));
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "int32 dvy").c_str(), asOFFSET(MD_ITR, dvy));
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "int32 fall").c_str(), asOFFSET(MD_ITR, fall));
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "int32 arest").c_str(), asOFFSET(MD_ITR, arest));
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "int32 vrest").c_str(), asOFFSET(MD_ITR, vrest));
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "int32 respond").c_str(), asOFFSET(MD_ITR, respond));
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "int32 effect").c_str(), asOFFSET(MD_ITR, effect));
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "array_int32 catchingact").c_str(), asOFFSET(MD_ITR, catchingact[0]));
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "array_int32 caughtact").c_str(), asOFFSET(MD_ITR, caughtact[0]));
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "int32 bdefend").c_str(), asOFFSET(MD_ITR, bdefend));
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "int32 injury").c_str(), asOFFSET(MD_ITR, injury));
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "int32 zwidth").c_str(), asOFFSET(MD_ITR, zwidth));
 Engi01->RegisterObjectProperty("ITR", (Temp01 + "array_int8 Unknown_1").c_str(), asOFFSET(MD_ITR, Unknown_1[0]));
 
 Engi01->RegisterObjectProperty("BDY", (Temp01 + "int32 kind").c_str(), asOFFSET(MD_BDY, kind));
 Engi01->RegisterObjectProperty("BDY", (Temp01 + "int32 x").c_str(), asOFFSET(MD_BDY, x));
 Engi01->RegisterObjectProperty("BDY", (Temp01 + "int32 y").c_str(), asOFFSET(MD_BDY, y));
 Engi01->RegisterObjectProperty("BDY", (Temp01 + "int32 w").c_str(), asOFFSET(MD_BDY, w));
 Engi01->RegisterObjectProperty("BDY", (Temp01 + "int32 h").c_str(), asOFFSET(MD_BDY, h));
 
 Engi01->RegisterObjectProperty("RECTANGLE", (Temp01 + "int32 X").c_str(), asOFFSET(MD_RECTANGLE, X));
 Engi01->RegisterObjectProperty("RECTANGLE", (Temp01 + "int32 Y").c_str(), asOFFSET(MD_RECTANGLE, Y));
 Engi01->RegisterObjectProperty("RECTANGLE", (Temp01 + "int32 W").c_str(), asOFFSET(MD_RECTANGLE, W));
 Engi01->RegisterObjectProperty("RECTANGLE", (Temp01 + "int32 H").c_str(), asOFFSET(MD_RECTANGLE, H));
 
 Engi01->RegisterObjectProperty("BACKGROUND", (Temp01 + "int32 width").c_str(), asOFFSET(MD_BACKGROUND, width));
 Engi01->RegisterObjectProperty("BACKGROUND", (Temp01 + "array_int32 zboundary").c_str(), asOFFSET(MD_BACKGROUND, zboundary[0]));
 Engi01->RegisterObjectProperty("BACKGROUND", (Temp01 + "array_int32 perspective").c_str(), asOFFSET(MD_BACKGROUND, perspective[0]));
 Engi01->RegisterObjectProperty("BACKGROUND", (Temp01 + "array_int32 shadowsize").c_str(), asOFFSET(MD_BACKGROUND, shadowsize[0]));
 Engi01->RegisterObjectProperty("BACKGROUND", (Temp01 + "int32 layer_Count").c_str(), asOFFSET(MD_BACKGROUND, layer_Count));
 Engi01->RegisterObjectProperty("BACKGROUND", (Temp01 + "array_array30_int8 layer_Pic").c_str(), asOFFSET(MD_BACKGROUND, layer_Pic[0][0]));
 Engi01->RegisterObjectProperty("BACKGROUND", (Temp01 + "array_int8 shadow").c_str(), asOFFSET(MD_BACKGROUND, shadow[0]));
 Engi01->RegisterObjectProperty("BACKGROUND", (Temp01 + "array_int8 Unknown_1").c_str(), asOFFSET(MD_BACKGROUND, Unknown_1[0]));
 Engi01->RegisterObjectProperty("BACKGROUND", (Temp01 + "array_int8 name").c_str(), asOFFSET(MD_BACKGROUND, name[0]));
 Engi01->RegisterObjectProperty("BACKGROUND", (Temp01 + "array_int8 Unknown_2").c_str(), asOFFSET(MD_BACKGROUND, Unknown_2));
 Engi01->RegisterObjectProperty("BACKGROUND", (Temp01 + "array_LAYER layer").c_str(), asOFFSET(MD_BACKGROUND, layer));
 Engi01->RegisterObjectProperty("BACKGROUND", (Temp01 + "array_int32 layer_Ptr").c_str(), asOFFSET(MD_BACKGROUND, layer_Ptr[0]));
 Engi01->RegisterObjectProperty("BACKGROUND", (Temp01 + "int32 Ptr").c_str(), asOFFSET(MD_BACKGROUND, Ptr));
 
 Engi01->RegisterObjectProperty("LAYER", (Temp01 + "int32 transparency").c_str(), asOFFSET(MD_LAYER, transparency[0]));
 Engi01->RegisterObjectProperty("LAYER", (Temp01 + "int32 width").c_str(), asOFFSET(MD_LAYER, width[0]));
 Engi01->RegisterObjectProperty("LAYER", (Temp01 + "int32 x").c_str(), asOFFSET(MD_LAYER, x[0]));
 Engi01->RegisterObjectProperty("LAYER", (Temp01 + "int32 y").c_str(), asOFFSET(MD_LAYER, y[0]));
 Engi01->RegisterObjectProperty("LAYER", (Temp01 + "int32 height").c_str(), asOFFSET(MD_LAYER, height[0]));
 Engi01->RegisterObjectProperty("LAYER", (Temp01 + "int32 loop").c_str(), asOFFSET(MD_LAYER, loop[0]));
 Engi01->RegisterObjectProperty("LAYER", (Temp01 + "int32 c1").c_str(), asOFFSET(MD_LAYER, c1[0]));
 Engi01->RegisterObjectProperty("LAYER", (Temp01 + "int32 c2").c_str(), asOFFSET(MD_LAYER, c2[0]));
 Engi01->RegisterObjectProperty("LAYER", (Temp01 + "int32 cc").c_str(), asOFFSET(MD_LAYER, cc[0]));
 Engi01->RegisterObjectProperty("LAYER", (Temp01 + "int32 Animation").c_str(), asOFFSET(MD_LAYER, Animation[0]));
 Engi01->RegisterObjectProperty("LAYER", (Temp01 + "int32 rect").c_str(), asOFFSET(MD_LAYER, rect[0]));
 Engi01->RegisterObjectProperty("LAYER", (Temp01 + "int32 rect32").c_str(), asOFFSET(MD_LAYER, rect[0]));

 Engi01->RegisterObjectProperty("STAGE", (Temp01 + "int32 Phase_Count").c_str(), asOFFSET(MD_STAGE, Phase_Count));
 Engi01->RegisterObjectProperty("STAGE", (Temp01 + "array_PHASE Phase").c_str(), asOFFSET(MD_STAGE, Phase));
 
 Engi01->RegisterObjectProperty("PHASE", (Temp01 + "int32 bound").c_str(), asOFFSET(MD_PHASE, bound));
 Engi01->RegisterObjectProperty("PHASE", (Temp01 + "array_int8 music").c_str(), asOFFSET(MD_PHASE, music[0]));
 Engi01->RegisterObjectProperty("PHASE", (Temp01 + "array_SPAWN Spawn").c_str(), asOFFSET(MD_PHASE, Spawn[0]));
 Engi01->RegisterObjectProperty("PHASE", (Temp01 + "int32 when_clear_goto_phase").c_str(), asOFFSET(MD_PHASE, when_clear_goto_phase));
 
 Engi01->RegisterObjectProperty("SPAWN", (Temp01 + "array_int8 Unknown_1").c_str(), asOFFSET(MD_SPAWN, Unknown_1[0]));
 Engi01->RegisterObjectProperty("SPAWN", (Temp01 + "int32 id").c_str(), asOFFSET(MD_SPAWN, id));
 Engi01->RegisterObjectProperty("SPAWN", (Temp01 + "int32 x").c_str(), asOFFSET(MD_SPAWN, x));
 Engi01->RegisterObjectProperty("SPAWN", (Temp01 + "int32 hp").c_str(), asOFFSET(MD_SPAWN, hp));
 Engi01->RegisterObjectProperty("SPAWN", (Temp01 + "int32 times").c_str(), asOFFSET(MD_SPAWN, times));
 Engi01->RegisterObjectProperty("SPAWN", (Temp01 + "int32 reserve").c_str(), asOFFSET(MD_SPAWN, reserve));
 Engi01->RegisterObjectProperty("SPAWN", (Temp01 + "int32 join").c_str(), asOFFSET(MD_SPAWN, join));
 Engi01->RegisterObjectProperty("SPAWN", (Temp01 + "int32 join_reserve").c_str(), asOFFSET(MD_SPAWN, join_reserve));
 Engi01->RegisterObjectProperty("SPAWN", (Temp01 + "int32 act").c_str(), asOFFSET(MD_SPAWN, act));
 Engi01->RegisterObjectProperty("SPAWN", (Temp01 + "int32 y").c_str(), asOFFSET(MD_SPAWN, y));
 Engi01->RegisterObjectProperty("SPAWN", (Temp01 + "double ratio").c_str(), asOFFSET(MD_SPAWN, ratio));
 Engi01->RegisterObjectProperty("SPAWN", (Temp01 + "int32 Role").c_str(), asOFFSET(MD_SPAWN, Role));
 Engi01->RegisterObjectProperty("SPAWN", (Temp01 + "array_int8 Unknown_2").c_str(), asOFFSET(MD_SPAWN, Unknown_2[0]));
}