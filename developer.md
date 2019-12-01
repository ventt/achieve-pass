# Fejlesztői dokumentáció
## környezetek
Környezet unix + cmake

## felépítés
A program felépítésének alap struktúrája: MVC (Model View Controller)

A data.h-ban találhatók a struktúrák, és a függvénydefiniciók a fájlkezeléshez, a data.c a megvalósításokat tartalmazza.

A view.h tartalmazza a megjelenítéshez tartozó függvény definiciókat, melyek csak a megjelenítést tartalmazzák, amihez az adatot a model.h-ban definiált struktúrákban kapja meg.

A controller irányítja a megjelenítést, és alakítja át az adatot a model.h szerint.

A main.c tartalmazza a menüt, és a hozzá tartozó parancs feldolgozást.

## Adatszerkezetek

A fájl adatszerkezete newline-al elválasztott sorok, melyek a data.h-ban lévő FileEntry struktúrát követi.
A FileEntry-ben vannak a Subject-ek amelyeket egy nem strázsás egyirányba bejárható láncolt listában tárol.

A Subjecteken belül a Examokat egy egydimenziós dinamikus tömbben tárolja a program.

## Függvények

###data.h
 - save: elmenti a FileEntry struktúrát a save.txt fájlba.
 - read: beolvassa a FilEntry struktúrát a save.txt fájlból.
 - free_entry: felszabadítja a memóriából a FileEntry adatszerkezetet.
 - is_file_exists: megnézi hogy létezik-e a save.txt
 - delete_subject: kitöröl egy tárgyat a FileEntry-ben tárolt láncolt listából.
 - add_exam: hozzá add egy zárthelyit egy SubjectEntry típuson keresztül, megadja a dátumot és hogy hány órát készültek rá.
 
 ###view.h
 - header: megjeleníti a fejlécet
 - progress_bar: megjeleníti az examok-hoz tartozó progress bart, egy százalékot vesz át
 - main_screen_window: a controller által generált model alapján megjeleníti az examokat
 - status_bar: controller által generált statul_model alapján megjeleníti az Achievement pontokat, és a sikeresen felkészült zh-kat
 - subject_window_details: 1-4-ig a subjectet részleteihez szükséges szöveget kiirja
 - add_subject_exam_date: a dátum beírásához szükséges szöveget jeleníti meg.
 - add_subject_exam_hours_done: a tanult órák beírásához szügséges szöveget jeleníti meg.
 - save_window: a mentést jelző ablakot jeleníti meg
 
  ###controller.h
  - get_line_from_input: egy tetszőleges méretű stringet olvas be az inputról az első '\n'-ig, és visszatér egy stringre mutató char típusú pointerrel. Későbbiekben fel kell szabadítani a tömböt.
  - create_new_save: létrehoz egy új üres mentést a felhasználó nevével.
  - add_subject: paraméterként kapja a FileEntry strukturában tárolt adatokat, amelynél a SubjectList tipusú láncolt listához fűz egy új subject elemet.
  - main_screen: paraméterként kapja a FileEntry struktúrában az adatokat, és egy integer értéket, hogy a folyamatban lévő examokat listázza ki vagy az elkészülteket. Ez a függvény készíti el a view.h-ban található main_screen számára a main_screen_model típusú adatot.
  - subject_delete: paraméterként kapja a láncolt listát és visszatér a listával, miután eltávolította az ID alapján megadott elemet.
  - check_subject_window: legenerálja a check subject windowt.
  - absolved_practicing: visszatér az elkészült zh-k számával
   
   ###main.c
   A main.c-ben található a menű rendszer és a bizonyos menű pontokhoz szükséges parancs kezelések.
  