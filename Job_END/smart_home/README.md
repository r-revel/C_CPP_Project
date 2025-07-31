### Описание проекта "Умный дом"

Проект разделен на две основные части: **Model** (модели данных) и **Controller** (логика управления).  

#### **1. Model**  

Реализация абстрактного классы (интерфейсы) и композицию:

- **`IDevice `** – базовый интерфейс для всех устройств (ID, имя, статус онлайн/оффлайн).  
- **`IActiveDevice`** – интерфейс для устройств с управлением (вкл/выкл). (например, лампочка, пылесос).  
- **`ISensorDevice`** – интерфейс для устройств с датчиками (например, термометр).  

Содержит классы, описывающие структуру умного дома:  

- **`Device`** – базовая реализация IDevice  
- **`Room`** – описывает комнату (имя, номер, тип: кухня, коридор и т.д.).  
- **`SmartSpeaker`** – умная колонка, содержит информацию о комнате (`Room`) и список подключенных устройств (`Device`).  
- **`SmartHome`** – управляет колонками (`SmartSpeaker`), поддерживает сортировку по имени и поиск.  

#### **2. Controller**  
Разделяем логику на два контроллера:  

1. **`DeviceController`** – управляет устройствами:  
   - Включение/выключение (`ActiveDevice`).  
   - Получение данных с датчиков (`SensorDevice`).  
   - Проверка состояния устройств.  

2. **`SmartHomeController`** – управляет умным домом:  
   - Добавление/удаление колонок (`SmartSpeaker`).  
   - Поиск колонок по имени.  
   - Управление устройствами через колонки.  

---

### **Диаграммы**  

#### **1. Model (UML-диаграмма классов)**  

```mermaid
classDiagram
    class IDevice {
        <<interface>>
        +getId() string
        +getName() string
        +isOnline() bool
        +getStatus() DeviceStatus
        +setStatus(DeviceStatus) void
    }

    class IActiveDevice {
        <<interface>>
        +isActive() bool
        +activate() void
        +deactivate() void
    }

    class ISensorDevice {
        <<interface>>
        +readValue() float
    }

    class Device {
        <<IDevice>>
        +Device(string id, string name)
        +getId() string
        +getName() string
        +setStatus(DeviceStatus)
        +getStatus() DeviceStatus
        +isOnline() bool
        +toString() string
    }

    class SmartSpeaker {
        +Room room
        +vector<IDevice*> devices

        +getName() string
        +getRoom() Room
        +addDevice(shared_ptr~IDevice~ device) void
        +removeDevice(string deviceId) void
        +getDevices() vector~shared_ptr~IDevice~~
        +checkAndRepairDevices() void
        +addNewDevice~T, Args...~(Args... args) void
    }

    class SmartHome {
        +vector~SmartSpeaker~ speakers_
        +addSpeaker(SmartSpeaker) void
        +removeSpeaker(string name) void
        +findSpeaker(string name) SmartSpeaker*
        +getSpeakers() vector~SmartSpeaker~
        +operator[](string name) SmartSpeaker&
        +operator<<(ostream& os) ostream&
    }

    IDevice <|.. Device
    IDevice <|.. IActiveDevice
    IDevice <|.. ISensorDevice
    Device *-- IActiveDevice : Optional
    Device *-- ISensorDevice : Optional
    SmartSpeaker *-- IDevice
    SmartHome *-- SmartSpeaker
```

#### **2. Controller (UML-диаграмма классов)**  

```mermaid
classDiagram
    class DeviceController {
        +toggleDevice(shared_ptr~IActiveDevice~) static void
        +readSensorValue(shared_ptr~ISensorDevice~) static float
        +getDeviceStatus(shared_ptr~IDevice~) static string
        +setDeviceOnlineStatus(shared_ptr~IDevice~, bool) static void
    }

    class SmartHomeController {
        +addSpeaker(SmartHome&, SmartSpeaker&) static void
        +removeSpeaker(SmartHome&, string) static void
        +findSpeaker(SmartHome&, string) SmartSpeaker* static
        +listAllDevices(SmartSpeaker&) static void
        +controlDeviceInSpeaker(SmartSpeaker&, string) static void
    }

    DeviceController --> ActiveDevice
    DeviceController --> SensorDevice
    SmartHomeController --> SmartHome
    SmartHomeController --> SmartSpeaker
```

---

Идея но возможно не будет реализованно 
Собрать приложения в виде webAssemble а ui будет на js vue как будто это один из самых простых способов 

## Для сборки 

emcc main.cpp -o index.js -sEXPORTED_FUNCTIONS=_add 

## Установка среды для сборки **Emscripten**  
### **Linux/macOS**  
```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh  # Добавляет emcc в PATH
```

```bash
emcc --version  # Должен вывести версию Emscripten
```



