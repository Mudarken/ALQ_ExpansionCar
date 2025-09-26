# Przewodnik dla Właścicieli Serwerów: Konfiguracja Modyfikacji DayZ

Witajcie, Właściciele Serwerów DayZ! Ten przewodnik ma na celu przedstawienie, jak skonfigurować i zarządzać modyfikacjami, które wprowadzają system King of the Hill (KOTH) oraz rozbudowany system nagród. Zrozumienie tych mechanik pozwoli Wam na pełne dostosowanie rozgrywki do potrzeb Waszego serwera i zapewnienie graczom angażujących wyzwań.

## 1. System King of the Hill (KOTH) - Flaga i Jej Konfiguracja

Centralnym elementem modu KOTH jest obiekt `Expansion_KOTHflag`. Jest to maszt flagowy, który pełni rolę punktu kontrolnego w wydarzeniach KOTH. Jego zachowanie i interakcje są zdefiniowane w plikach `.c`, ale kluczowe jest zrozumienie, jak działa z perspektywy konfiguracji serwera.

### Umieszczanie Flagi KOTH na Mapie

Flaga KOTH (`Expansion_KOTHflag`) musi zostać umieszczona na mapie serwera za pomocą narzędzi do edycji mapy (np. DayZ Editor). Po umieszczeniu, jej `ObjectiveID` i `ObjectiveType` są kluczowe dla powiązania jej z systemem nagród. Te wartości są ustawiane programowo, ale ich znajomość jest niezbędna do prawidłowego skonfigurowania nagród w `RewardConfig.json`.

### Efekty Wizualne Flagi (Dym)

Flaga KOTH generuje efekty cząsteczkowe (dym) za pomocą klasy `KOTH_Particle`. Dym ten może sygnalizować różne stany wydarzenia KOTH (np. aktywne, zakończone sukcesem, zakończone porażką). Domyślnie, flaga spawnuje biały dym, gdy jest aktywna. Gdy flaga zostanie opuszczona (co zazwyczaj oznacza przejęcie punktu), dym jest zatrzymywany, a cząsteczka usuwana. Możecie dostosować typy cząsteczek dymu w pliku `KOTH_Particle.c`, jeśli chcecie zmienić kolory lub efekty wizualne dla różnych stanów.

### Akcje Graczy

Gracze mogą wchodzić w interakcję z flagą poprzez akcje `ActionRaiseKOTHFlag` (podnoszenie flagi) i `ActionLowerKOTHFlag` (opuszczanie flagi). Te akcje są zdefiniowane w odpowiednich plikach `.c` i nie wymagają bezpośredniej konfiguracji, ale ich istnienie jest fundamentalne dla rozgrywki KOTH. Wysokość flagi jest synchronizowana między klientem a serwerem, co zapewnia spójne doświadczenie dla wszystkich graczy.

## 2. System Nagród - `RewardConfig.json`

Plik `RewardConfig.json` jest sercem systemu nagród. To tutaj definiujecie, jakie nagrody zostaną przyznane po zakończeniu konkretnych celów (np. po przejęciu flagi KOTH). Plik ten jest ładowany przez `RewardConfig.c`.

### Struktura Pliku `RewardConfig.json`

Plik `RewardConfig.json` jest tablicą obiektów, gdzie każdy obiekt reprezentuje konfigurację nagród dla konkretnego celu. Kluczowe pola to:

*   `_description`: Krótki opis konfiguracji (tylko dla czytelności, nie wpływa na działanie moda).
*   `ObjectiveID`: Unikalny identyfikator celu. Musi odpowiadać `m_ObjectiveID` ustawionemu dla flagi KOTH lub innego obiektu celu.
*   `ObjectiveType`: Typ celu. Musi odpowiadać `m_ObjectiveType` ustawionemu dla flagi KOTH lub innego obiektu celu. W przykładach widzieliśmy `10`.
*   `Groups`: Tablica grup nagród. System nagród losuje jedną z tych grup na podstawie ich `Weight`.

### Konfiguracja Grup Nagród (`Groups`)

Każda grupa nagród w tablicy `Groups` ma następujące pola:

*   `Weight`: Waga grupy. Im wyższa waga, tym większa szansa na wylosowanie tej grupy nagród. Suma wag wszystkich grup w danym `ObjectiveID`/`ObjectiveType` określa prawdopodobieństwo wylosowania każdej z nich.
*   `RewardType`: Typ nagrody. Może to być `"crate"` (skrzynia) lub `"vehicle"` (pojazd).
*   `Item`: Nazwa klasy przedmiotu, który ma zostać zespawnowany (np. `"ALQMilitaryCrate"` dla skrzyni, `"OffroadHatchback"` dla pojazdu).
*   `Position`: Pozycja spawnu nagrody w formacie `"X Y Z"`. Jest to kluczowe, aby nagrody pojawiały się w odpowiednim miejscu na mapie.
*   `Orientation`: Orientacja nagrody w formacie `"X Y Z"`. Określa, w którą stronę będzie zwrócony obiekt po zespawnowaniu.
*   `MinGuaranteedItems`: Minimalna liczba przedmiotów, które zawsze zostaną zespawnowane w nagrodzie, niezależnie od szansy.
*   `MaxItems`: Maksymalna liczba przedmiotów, które mogą zostać zespawnowane w nagrodzie.
*   `Contents`: Tablica obiektów definiujących zawartość nagrody. Każdy obiekt `Contents` ma pola:
    *   `ItemName`: Nazwa klasy przedmiotu (np. `"AKM"`, `"Mag_AKM_30Rnd"`).
    *   `Chance`: Szansa (w procentach, od 0 do 100) na zespawnowanie tego przedmiotu.
    *   `Quantity`: Liczba sztuk tego przedmiotu, która zostanie zespawnowana, jeśli zostanie wylosowany.
    *   `Attachments`: Tablica nazw klas załączników, które zostaną automatycznie dołączone do przedmiotu (np. `"KashtanOptic"` do `"AKM"`).
*   `Parts`: (Tylko dla `RewardType: "vehicle"`) Tablica nazw klas części pojazdu, które zostaną zespawnowane i dołączone do pojazdu. Jeśli ta lista jest pusta, system spróbuje załadować domyślne części z `VehicleParts.json`.
*   `VehicleTimer`: (Tylko dla `RewardType: "vehicle"`) Czas w milisekundach, po którym pojazd zostanie usunięty, jeśli nie zostanie przesunięty z miejsca spawnu. Wartość `0` oznacza brak timera.
*   `CrateTimer`: (Tylko dla `RewardType: "crate"`) Czas w milisekundach, po którym skrzynia zostanie usunięta, jeśli nie zostanie przesunięta z miejsca spawnu. Wartość `0` oznacza brak timera.

### Przykład Konfiguracji Nagrody (fragment z `RewardConfig.json`):

```json
{
    "_description": "NovoselkiFlag",
    "ObjectiveID": 1001,
    "ObjectiveType": 10,
    "Groups": [
        {
            "Weight": 50,
            "RewardType": "crate",
            "Item": "ALQMilitaryCrate",
            "Position": "5799.35 93.70 3071.77",
            "Orientation": "54.0 -0.0 -0.0",
            "MinGuaranteedItems": 2,
            "MaxItems": 4,
            "Contents": [
                {
                    "ItemName": "AKM",
                    "Chance": 80,
                    "Quantity": 1,
                    "Attachments": [
                        "Mag_AKM_30Rnd",
                        "KashtanOptic"
                    ]
                },
                {
                    "ItemName": "M4A1",
                    "Chance": 50,
                    "Quantity": 1,
                    "Attachments": [
                        "Mag_CMAG_40Rnd"
                    ]
                }
            ],
            "VehicleTimer": 0,
            "CrateTimer": 120000
        }
    ]
}
```

**Wskazówki do konfiguracji `RewardConfig.json`:**

*   **Unikalne ID/Typy**: Upewnijcie się, że kombinacje `ObjectiveID` i `ObjectiveType` są unikalne dla każdego celu na Waszym serwerze.
*   **Pozycje Spawnu**: Dokładnie określcie pozycje (`Position`) i orientacje (`Orientation`) dla spawnowanych nagród. Możecie użyć narzędzi do edycji mapy, aby uzyskać precyzyjne współrzędne.
*   **Balansowanie Lutu**: Eksperymentujcie z `Weight`, `Chance`, `MinGuaranteedItems` i `MaxItems`, aby zbalansować nagrody i dostosować je do ekonomii Waszego serwera.
*   **Timery**: Używajcie timerów (`VehicleTimer`, `CrateTimer`), aby zapobiec gromadzeniu się nagród i zachęcić graczy do szybkiego ich zbierania. Wartość `120000` milisekund to 2 minuty.

## 3. Konfiguracja Części Pojazdów - `VehicleParts.json`

Plik `VehicleParts.json` służy do definiowania domyślnych części dla różnych typów pojazdów. Jest to szczególnie przydatne, gdy spawnowane są pojazdy jako nagrody, a nie chcecie ręcznie wymieniać wszystkich części w `RewardConfig.json`.

### Struktura Pliku `VehicleParts.json`

Plik `VehicleParts.json` jest obiektem JSON, gdzie kluczem jest nazwa klasy pojazdu (np. `"Truck_01_Covered"`, `"OffroadHatchback"`), a wartością jest tablica nazw klas części, które zostaną automatycznie dołączone do tego pojazdu.

### Przykład Konfiguracji Części Pojazdów (fragment z `VehicleParts.json`):

```json
{
    "Truck_01_Covered": [
        "Truck_01_Wheel",
        "Truck_01_Wheel",
        "Truck_01_Wheel",
        "Truck_01_Wheel",
        "Truck_01_WheelDouble",
        "Truck_01_WheelDouble",
        "Truck_01_WheelDouble",
        "Truck_01_WheelDouble",
        "Truck_01_Door_1_1",
        "Truck_01_Door_2_1",
        "Truck_01_Hood",
        "HeadlightH7",
        "HeadlightH7",
        "TruckBattery"
    ],
    "OffroadHatchback": [
        "HatchbackWheel",
        "HatchbackWheel",
        "HatchbackWheel",
        "HatchbackWheel",
        "HatchbackDoors_Driver",
        "HatchbackDoors_CoDriver",
        "HatchbackHood",
        "CarRadiator",
        "SparkPlug",
        "CarBattery"
    ]
}
```

**Wskazówki do konfiguracji `VehicleParts.json`:**

*   **Kompletność**: Upewnijcie się, że lista części dla każdego pojazdu jest kompletna i zawiera wszystkie niezbędne elementy do jego uruchomienia (koła, drzwi, maska, akumulator, świece zapłonowe, chłodnica itp.).
*   **Dostosowanie**: Możecie dostosować te listy, aby pojazdy spawnowały się z różnym stopniem uszkodzenia lub z brakującymi częściami, co może stanowić dodatkowe wyzwanie dla graczy.

## 4. Niestandardowe Przedmioty i Flary Drogowe

Mod wprowadza również kilka niestandardowych przedmiotów, takich jak:

*   **ALQ Kontenery/Skrzynie**: `ALQContainer_Base`, `ALQGreenCrate_Base`, `ALQMilitaryCrate_Base`. Są to niestandardowe pojemniki, które mogą być używane jako nagrody w systemie nagród.
*   **ALQ Road Flare**: `ALQRoadFlare`. Jest to niestandardowa flara drogowa, którą gracze mogą włączać za pomocą akcji `ActionTurnOnALQRoadFlare`. Możecie użyć tych flar w konfiguracji nagród lub jako element lootu na mapie.

### Integracja z Serwerem

Upewnijcie się, że wszystkie pliki moda są prawidłowo umieszczone w strukturze folderów Waszego serwera DayZ (zazwyczaj w folderze `mpmissions` lub `mods`). Wszelkie niestandardowe klasy przedmiotów (takie jak `ALQMilitaryCrate` czy `ALQRoadFlare`) muszą być również zdefiniowane w pliku `types.xml` Waszego serwera, aby mogły być spawnowane jako loot lub nagrody.

--- 

**Autor**: Manus AI

**Data**: 20 września 2025


