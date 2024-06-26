<a name="_u5zk78gvyjp5"></a>Wizualizacja gry w szachy

<a name="_dj8g9wiiehlf"></a>Maurycy Szmuc 193194, Mateusz Dublinowski 193182

![](Aspose.Words.b1bed243-17e6-4631-b510-f2ce28b5b1c1.001.png)
## <a name="_dpsgkfyk9pqv"></a>Opis wizualizacji:
Celem programu jest przedstawienie algebraicznej notacji szachowej, czyli najczęściej używanej notacji, na przyjazną dla człowieka krok po kroku wizualizacje każdego ruchu.

Po lewej stronie okna wyświetlana jest szachownica z pionkami, a po prawej stronie odpowiednie informacje o grze, jak i kontrolki dla użytkownika.

Użytkownik jest w stanie za pomocą przycisków wybrać plik PGN do analizy, przejść do następnego ruchu, włączyć automatyczne przejścia po ruchach, oraz opcja zmiany z kamery ortograficznej na perspektywistyczną, którą można obracać wokół planszy.

![](Aspose.Words.b1bed243-17e6-4631-b510-f2ce28b5b1c1.002.png)

Pionki zostały specjalnie wymodelowane aby z lotu ptaka ortograficznej kamery wyglądały jak pionki dwuwymiarowe, gdzie w rzeczywistości są trzy.

Wszystkie modele zostały wykonane w programie graficznym Blender.
## <a name="_j5t51p76zj8c"></a>Struktura projektu:
Wizualizacja dzieli się na dwie części; frontend i backend, gdzie backend przesyła informacje do użycia przez frontend (zmienianie lokacji pionków, usuwanie pionków) i odwrotnie( komunikat o przejściu do następnej tury)

Program komunikuje się między frontendem używając slotów i sygnałów dostarczonych przez Qt.

Sloty są funkcjami używanymi przez frontenda do backenda, a sygnały przesyłają dane do użytku przez frontend.

Program działa używając czterech obiektów:
- ### <a name="_tg8upulqrh94"></a>fileLoader
  Jego zadaniem jest wczytanie pliku i przesłanie go do dalszego parsowania w dataParser.
- ### <a name="_d1ugw9m93lgk"></a>dataParser
  Przygotowuje plik dzieląc go na informacje o grze i ruchach, i wysyłanie do frontend i backend.
- ### <a name="_7i3lb7dfu9wi"></a>chessController 
  Główny obiekt definiujący grę w szachy, przetrzymujący informacje o pionkach i analizując ruchy w algebraicznej notacji.
- ### <a name="_7gdjktfj918k"></a>chessPiece 
  Obiekt definiujący pionki, ich lokacje, typ kolor itp.

