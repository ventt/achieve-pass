# achieve-pass

## Feladata
A program feladata nyilvantartani a felhasználó által megadott tárgyak, zárthelyieit, idopontját és az órák számát amit foglalkozott vele.
## Célja
A hallgató sikerélményét növelni az Achievement pontok által, és megfelelően belátni a készülésre való kezdés idejét
## bemenetek
Terminal alapú, szöveges commandok által lehet a programnak adatokat, parancsokat adni.
## kiemenetek
Külön ablakok állnak rendelkezésre, ahol az adatokat jeleníti meg a program, zhkra osztva. Minden ablaknál láthatjuk a command lehetőségeinket
## Program kezelése
### Main screen
- ***/addtime <SubjectId> <ExamId>***, ahol a SubjectId a tárgy egyedi azonosítója, az ExamId a tárgy alatt lévő Zárthelyi sorszáma, ezeket beírva tudunk egy zh-hoz időt hozzáadni
- ***/checksubject <SubjectId>***, ahol a SubjectId a tárgy egyedi azonosítója, ezzel tudjuk megnyitni a CheckSubject ablakot, a kiválasztott tárgyal
- ***/addsubject*** parancsal tudjuk megnyitni az addsubject ablakot, amelyben hozzátudunk adni egy új tárgyat, és a zh-it
- ***/showdone*** parancsal nézhetjük meg a már elkészült zh-kat
- ***/exit*** parancsal mentjük, és lépünk ki az alkalmazásból

### Check subject screen
- ***/mainmenu*** parancsal válthatunk vissza főképernyőre
- ***/addtime <SubjectId> <ExamId>***, ahol a SubjectId a tárgy egyedi azonosítója, az ExamId a tárgy alatt lévő Zárthelyi sorszáma, ezeket beírva tudunk egy zh-hoz időt hozzáadni
- ***/editdata <DataNumber> <data>*** parancsal tudunk adatokat valtoztatni, ahol a DataNumber a listán jelzet adat száma, és az új adat amit megakarunk adni
- ***/addexam <year> <month> <day>*** parancsal tudunk zh időpontot odaadni, év hónap nap
- ***/delete*** parancsal törölhetjük az egész tárgyat
- ***/exit*** parancsal mentjük, és lépünk ki az alkalmazásból

### Show done screen
- ***/mainmenu*** parancsal válthatunk vissza főképernyőre
- ***/checksubject <SubjectId>***, ahol a SubjectId a tárgy egyedi azonosítója, ezzel tudjuk megnyitni a CheckSubject ablakot, a kiválasztott tárgyal
- ***/exit*** parancsal mentjük, és lépünk ki az alkalmazásból