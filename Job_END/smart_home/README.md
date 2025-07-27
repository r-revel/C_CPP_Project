### Описание проекта "Умный дом"

Проект разделен на две основные части: **Model** (модели данных) и **Controller** (логика управления).  

#### **1. Model**  
Содержит классы, описывающие структуру умного дома:  

- **`Device`** – базовый класс для всех устройств (ID, имя, статус онлайн/оффлайн).  
- **`ActiveDevice`** – наследник `Device`, добавляет методы активации/деактивации (например, лампочка, пылесос).  
- **`SensorDevice`** – наследник `Device`, добавляет методы для получения показаний (например, термометр).  
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
    class Device {
        <<abstract>>
        +string id
        +string name
        +bool isOnline
        +getStatus() bool
        +setStatus(bool) void
    }

    class ActiveDevice {
        +bool isActive
        +activate() void
        +deactivate() void
    }

    class SensorDevice {
        +float value
        +readValue() float
    }

    class Room {
        +string name
        +int number
        +string type
    }

    class SmartSpeaker {
        +Room room
        +vector<Device*> devices
        +addDevice(Device*) void
        +removeDevice(string id) void
        +listDevices() vector<Device*>
    }

    class SmartHome {
        +vector<SmartSpeaker> speakers
        +addSpeaker(SmartSpeaker) void
        +removeSpeaker(string name) void
        +operator[](string name) SmartSpeaker&
        +operator<<(ostream&, SmartHome&) ostream&
    }

    Device <|-- ActiveDevice
    Device <|-- SensorDevice
    SmartSpeaker "1" *-- "1" Room
    SmartSpeaker "1" *-- "0..*" Device
    SmartHome "1" *-- "0..*" SmartSpeaker
```

#### **2. Controller (UML-диаграмма классов)**  

```mermaid
classDiagram
    class DeviceController {
        +toggleDevice(ActiveDevice*) void
        +readSensor(SensorDevice*) float
        +checkDeviceStatus(Device*) bool
    }

    class SmartHomeController {
        +addSpeaker(SmartHome&, SmartSpeaker) void
        +removeSpeaker(SmartHome&, string name) void
        +findSpeaker(SmartHome&, string name) SmartSpeaker*
        +controlSpeakerDevices(SmartSpeaker&) void
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



