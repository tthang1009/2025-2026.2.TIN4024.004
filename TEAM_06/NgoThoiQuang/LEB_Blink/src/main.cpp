{
  "version": 1,
  "author": "Ngo Thoi Quang",
  "editor": "wokwi",
  "parts": [
    { "type": "board-esp32-devkit-c-v4", "id": "esp", "top": 67.2, "left": 72.04, "attrs": {} },
    { "type": "wokwi-led", "id": "led1", "top": -42, "left": 215, "attrs": { "color": "red" } },
    {
      "type": "wokwi-led",
      "id": "led2",
      "top": -61.2,
      "left": 80.6,
      "attrs": { "color": "yellow" }
    },
    {
      "type": "wokwi-led",
      "id": "led3",
      "top": -51.6,
      "left": -25,
      "attrs": { "color": "limegreen" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r1",
      "top": 23.15,
      "left": 0,
      "attrs": { "value": "1000" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r2",
      "top": 23.15,
      "left": 201.6,
      "attrs": { "value": "1000" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r3",
      "top": 23.15,
      "left": 86.4,
      "attrs": { "value": "1000" }
    }
  ],
  "connections": [
    [ "esp:TX", "$serialMonitor:RX", "", [] ],
    [ "esp:RX", "$serialMonitor:TX", "", [] ],
    [ "led3:A", "r1:1", "green", [ "v0" ] ],
    [ "led2:A", "r3:1", "green", [ "v0" ] ],
    [ "led1:A", "r2:1", "green", [ "v0" ] ],
    [ "r2:2", "esp:32", "green", [ "v0" ] ],
    [ "r3:2", "esp:33", "green", [ "v0" ] ],
    [ "r1:2", "esp:34", "green", [ "v0" ] ],
    [ "led3:C", "esp:GND.1", "green", [ "v0" ] ],
    [ "led2:C", "esp:GND.1", "green", [ "v0" ] ],
    [ "led1:C", "esp:GND.1", "green", [ "v220.8", "h-153.2" ] ]
  ],
  "dependencies": {}
}