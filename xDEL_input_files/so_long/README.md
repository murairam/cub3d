# so_long
This project is a very small 2D game. Its purpose is to make you work with textures, sprites, and some other very basic gameplay elements.

used game assets:
https://itch.io/game-assets/free/tag-textures

* https://nulltale.itch.io/white-scape

https://medium.com/@simonzerisenay/exploring-so-long-game-a-dive-into-2d-game-development-f889f498e416

https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html

https://reactive.so/post/42-a-comprehensive-guide-to-so_long


https://www.paulgraham.com/avg.html


https://42-cursus.gitbook.io/guide/rank-02/so_long/understand-so_long

to do:
- counter ei loe oigesti, iga key on eraldi (omg sain toole)
- parse map floodfill alogrithm
- counter as a var?
- vaata makefile ule, see praegu suhteliselt kole, prindib liiga palju asju in my op

last thing i did
ma ei osanud headereid lisada. main parser peaks olema ok, pmts kopeerisin githubist. mlx init ok. pean vaatama ule kuidas ma saan tile lisada
vb oleks hea mote map parseda ja siis printida valja, et naha kas on korrektselt parsitud


lisasin init funtsiooni, aga sa peaks proovima kuidas valja printida mappi. also vaata parse func ule, minuarust ma kasutasin copilotit ja see pole paris oige


https://github.com/a-dylean/so_long/blob/main/src/image_rendering.c#L92

05. aprill
- lisa png voi mingi muu failid et window renderida
- sa pead kaardi populatima, st map maatriksisse lisa parameetrite tahed
- sul on parsingust veel kindlalt asjad puudu
- vaata ule kuidas sa koordinaate kasutad, sul peaks olema kahed koordinaadid - mangija asukoht asukoht gridil (vist)
- kui sa mappi populated siis salvesta akki mangija asukoht

9 april
- see nadal PEAD VALMIS SAAMA

11.aprill
-oops 10 aprill ei teinud midagi
 - aga tanasest olen academic weapon kuigi kell on juba 18 :)

15 aprill
uups
ikka ei teinud midagi, ainult googledasin
https://g.co/gemini/share/1db17ffba962

18.aprill
- lisa free funktsioonid
- vaata ule kas init funktsioonid on oiged
- vali valja oiged xpm failid
- midagi on valesti struktis

18april
valgrind ei toota. isegi akend ei avane. init mapis cvoi dup mapis on midagi valesti, saad homme vasrke peaga ule vaadata.

23.apr
okii tootab koik, nuud tee mang ilusaks ja vb saad boonuse ka lisada?
https://pulgamecanica.herokuapp.com/posts/mlx42-intro
https://42.nauman.cc/2023/09/13/intermediate-c-mlx/

