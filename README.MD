## LF2's Function & AI Injector
This is just a modification from [LF2-AI-ScriptEngine](https://github.com/zort/lf2-ai-scriptengine). <br/>
Instead of just meant to inject an AI(s) into Little Fighter 2 (LF2), this modified DDraw (`ddraw.dll`) also meant to inject a function(s) to LF2. <br/>
A friendly way to modify LF2, instead of messing up with `HEX`, with this DDraw, you can messing up with `C++` ( mainly `C++`) to modify LF2.

Dunno if this DDraw can be better than directly modifying from `HEX`.
But in fact, this way is much friendlier.
But yes, `HEX` has it's own favor.

## Modifying
To start modifying, you'll need [Microsoft Visual Studio](https://visualstudio.microsoft.com/), 2019 or higher. <br/>

- Open `ddwrapper.sln` to modify the project. <br/>
- Use `Build -> Build Solution` to build the `ddraw.dll`. Note the `Debug` / `Release` before building it up. <br/>

Inside the project, you'll see `ddwrapper.cpp`, it's the core of the DDraw. <br/>
( Better to reformat the code to get better look, if you didn't like/used to my code formatting style. )<br/>
Main changes from the original DDraw was in `//External Code` ( If you're using [Visual Studio Code](https://code.visualstudio.com/) in editing the code, the `+` feature beside the `//` should help a lot ).
<br/>
<br/>

> Credits (The Original DDraw) : [Doix](https://lf-empire.de/forum/member.php?action=profile&uid=8), [Some1Lse](https://lf-empire.de/forum/member.php?action=profile&uid=284), [zort](https://lf-empire.de/forum/member.php?action=profile&uid=4264), and everyone else who have an effort in it. <br/>
> Credits (This Modified DDraw) : [Mesujin](https://lf-empire.de/forum/member.php?action=profile&uid=6253). <br/>

> About Little Fighter 2 (LF2) : https://lf2.net
<div align="center"><h1></h1>
<a href="https://lf-empire.de/forum/showthread.php?tid=11273">Click here to back/go to the forum</a>.
</div>
