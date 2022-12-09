## Modified DDraw <font size="2">( Immersive Assistant in Modifying LF2 )</font>
Disclaimer, this is just a modification from [LF2-AI-ScriptEngine](https://github.com/zort/lf2-ai-scriptengine). <br/>

Instead of just meant to inject an AI(s) into Little Fighter 2 ( LF2 ), this Modified DDraw (`ddraw.dll`) is modified to be also meant to inject a function(s) into LF2 while also providing thing(s) for modifying LF2. <br/>

By providing a friendlier way to modify LF2, this Modified DDraw serving two way to modify, either with `AngelScript` moduling ( a buried feature from Original DDraw ) or directly modifying this Modified DDraw with `C++`. Instead of directly modifying the `.exe` with `Assembly` / `HEX` even though it has its own favor. <br/>
<br/>

### Modifying The DDraw
To start modifying, generally you'll need [Microsoft Visual Studio](https://visualstudio.microsoft.com/), 2019 or higher. <br/>

- Open `ddwrapper.sln`. <br/>
- Modify things you wanted in `ddwrapper.cpp`, it's the core of this DDraw. <br/>
- Once done modifying the code, open `Build` -> `Build Solution`. Note the `Multi` / `Debug` / `Release` before build it down. <br/>

( You'd better to reformat the code to get a better look, if you didn't like/used to my code formatting style. )<br/>
( If you're using [Visual Studio Code](https://code.visualstudio.com/) in editing the code, the `+` feature beside the `//` should help a lot if you keep my code formatting ).
<br/>
<br/>

### Modifying With Module
If you're familiar in scripting an AI for LF2 ( or `AngelScript` language ), then we can talk.

The how to use the `.as` as a Module instead of an AI-Script is simply by providing "`_`" as the initial letter, for example `_230.as`, and then Modified DDraw will use it as a Module instead of AI-Script. <br/>
( You can name the Module with text, but naming the Module with an ID of an Object is highly recommended because unlike AI-Script which are specified to an ID, a Module is a global usage. ) <br/>

In AI-Script, the main function to be used is known as `void id()` and `int ego()`, but in Module, the main function is different, which is ; <br/>

- `void game()` <br/>
  will be called for once, when you run LF2. <br/> Note that you may not call anything from `game` class in this function.
- `void init()` / `void once()` <br/>
  will be called for once, when initialization time is come. Both `init()` and `once()` are mainly the same, but unlike `init()`, `once()` won't be called again if the Module is being rebuilded on runtime.
- `void play()` <br/>
  will be called when entering a new battle.
- `void main()` <br/>
  will be called for every time unit ( TU ).
- `void mids()` <br/>
  will be called for every TU but in the middle of TU. <br/>
- `void last()` <br/>
  will be called for every TU but at the end of TU. <br/>
- `void fins()` <br/>
  will be called when exiting a battle. <br/>


( In the current version, `mids()` and `last()` are still be called just after the `main()` is called, but it's still worthy for last priority usage )

The other aspect is remain the same except `self` class and `target` class isn't exist and most of the value in `game` class is modifable, for example : `game.objects[0].hp = 0;` is allowed in Module. <br/>

There's also some new things comes within it, which ; <br/>

- `uint32 moduleID` <br/>
  which is the number in the Module's filename. ( `0` if the filename is non-numeric )
- `uint32 getobjectData(int32 Object_ID)` <br/>
  which will return the in-game Data address of an object. ( return `4294967295` on fail )
- `int32 getobjectSet(int32 Object_Num)` | `int32 getdataSet(int32 Object_Data)` <br/>
  which will return the `set:` of an Object.
- `void frameCopy(uint32 Object_Data, uint32 Frame1, uint32 Frame2)` <br/>
  which are used to copy datas in `Frame1` to `Frame2`.
- `void frameCopying(uint32 Object_Data1, uint32 Object_Data2, uint32 Frame1, uint32 Frame2)` <br/>
  which are used to copy datas in `Frame1` to `Frame2` from different Object.

And some basic stuff ;

- `int32 maximumFrame` <br/>
  return the maximum Frame, normally it's `400`, but you might want to use this for the compatibility of your script.
- `int32 maximumObject` <br/>
  return the maximum number of Object, normally it's `400`, ...
- `int32 maximumManaPoint` <br/>
  return the maximum Mana Point ( MP ), normally it's `500`, ...

Do note that Moduling has a priority in which supposed to be called first ...

<br/>
<br/>
<br/>



> About Little Fighter 2 (LF2) : https://lf2.net <br/>

> About AngelScript : https://www.angelcode.com/angelscript <br/>

> Credits (Original DDraw) : [Doix](https://lf-empire.de/forum/member.php?action=profile&uid=8), [Some1Lse](https://lf-empire.de/forum/member.php?action=profile&uid=284), [zort](https://lf-empire.de/forum/member.php?action=profile&uid=4264), and everyone else who have an effort in it. <br/>
> Credits (Modified DDraw) : [Mesujin](https://lf-empire.de/forum/member.php?action=profile&uid=6253). <br/>

<div align="center"><h1></h1>
<a href="https://lf-empire.de/forum/showthread.php?tid=11273">Click here to back/go to the forum</a>.
</div>
