#include <Arduino.h>
#include <ArduinoJson.h>
#include "LCD_Test.h"

UWORD Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
UWORD *BlackImage;
CST816S touch(6, 7, 13, 5); // sda, scl, rst, irq

bool displayFirstJson = true;
int touchCount = 0;
int toggleCount = 0; // Counter to track touches for toggling

const char* jsonData1 = "{\"interpolate\":false,\"strokes\":[{\"points\":[{\"x\":49,\"y\":63,\"color\":\"#ffffff\"},{\"x\":49,\"y\":64,\"color\":\"#ffffff\"},{\"x\":49,\"y\":66,\"color\":\"#ffffff\"},{\"x\":49,\"y\":69,\"color\":\"#ffffff\"},{\"x\":49,\"y\":71,\"color\":\"#ffffff\"},{\"x\":49,\"y\":74,\"color\":\"#ffffff\"},{\"x\":49,\"y\":75,\"color\":\"#ffffff\"},{\"x\":49,\"y\":78,\"color\":\"#ffffff\"},{\"x\":49,\"y\":81,\"color\":\"#ffffff\"},{\"x\":49,\"y\":83,\"color\":\"#ffffff\"},{\"x\":49,\"y\":86,\"color\":\"#ffffff\"},{\"x\":49,\"y\":87,\"color\":\"#ffffff\"},{\"x\":49,\"y\":90,\"color\":\"#ffffff\"},{\"x\":49,\"y\":91,\"color\":\"#ffffff\"},{\"x\":49,\"y\":93,\"color\":\"#ffffff\"},{\"x\":49,\"y\":95,\"color\":\"#ffffff\"},{\"x\":49,\"y\":96,\"color\":\"#ffffff\"},{\"x\":49,\"y\":97,\"color\":\"#ffffff\"},{\"x\":49,\"y\":98,\"color\":\"#ffffff\"},{\"x\":49,\"y\":99,\"color\":\"#ffffff\"}]},{\"points\":[{\"x\":31,\"y\":58,\"color\":\"#ffffff\"},{\"x\":32,\"y\":58,\"color\":\"#ffffff\"},{\"x\":33,\"y\":58,\"color\":\"#ffffff\"},{\"x\":34,\"y\":58,\"color\":\"#ffffff\"},{\"x\":35,\"y\":58,\"color\":\"#ffffff\"},{\"x\":36,\"y\":58,\"color\":\"#ffffff\"},{\"x\":38,\"y\":58,\"color\":\"#ffffff\"},{\"x\":39,\"y\":58,\"color\":\"#ffffff\"},{\"x\":40,\"y\":58,\"color\":\"#ffffff\"},{\"x\":41,\"y\":58,\"color\":\"#ffffff\"},{\"x\":43,\"y\":58,\"color\":\"#ffffff\"},{\"x\":44,\"y\":58,\"color\":\"#ffffff\"},{\"x\":46,\"y\":58,\"color\":\"#ffffff\"},{\"x\":47,\"y\":58,\"color\":\"#ffffff\"},{\"x\":48,\"y\":58,\"color\":\"#ffffff\"},{\"x\":50,\"y\":58,\"color\":\"#ffffff\"},{\"x\":52,\"y\":58,\"color\":\"#ffffff\"},{\"x\":53,\"y\":58,\"color\":\"#ffffff\"},{\"x\":54,\"y\":58,\"color\":\"#ffffff\"},{\"x\":56,\"y\":58,\"color\":\"#ffffff\"},{\"x\":57,\"y\":58,\"color\":\"#ffffff\"},{\"x\":58,\"y\":58,\"color\":\"#ffffff\"},{\"x\":59,\"y\":58,\"color\":\"#ffffff\"},{\"x\":60,\"y\":58,\"color\":\"#ffffff\"},{\"x\":61,\"y\":58,\"color\":\"#ffffff\"},{\"x\":62,\"y\":58,\"color\":\"#ffffff\"}]},{\"points\":[{\"x\":61,\"y\":83,\"color\":\"#ffffff\"},{\"x\":61,\"y\":84,\"color\":\"#ffffff\"},{\"x\":62,\"y\":84,\"color\":\"#ffffff\"},{\"x\":63,\"y\":84,\"color\":\"#ffffff\"},{\"x\":64,\"y\":84,\"color\":\"#ffffff\"},{\"x\":65,\"y\":84,\"color\":\"#ffffff\"},{\"x\":67,\"y\":84,\"color\":\"#ffffff\"},{\"x\":68,\"y\":85,\"color\":\"#ffffff\"},{\"x\":70,\"y\":85,\"color\":\"#ffffff\"},{\"x\":71,\"y\":86,\"color\":\"#ffffff\"},{\"x\":72,\"y\":86,\"color\":\"#ffffff\"},{\"x\":73,\"y\":86,\"color\":\"#ffffff\"},{\"x\":74,\"y\":86,\"color\":\"#ffffff\"},{\"x\":76,\"y\":86,\"color\":\"#ffffff\"},{\"x\":77,\"y\":86,\"color\":\"#ffffff\"},{\"x\":78,\"y\":86,\"color\":\"#ffffff\"},{\"x\":79,\"y\":86,\"color\":\"#ffffff\"},{\"x\":80,\"y\":86,\"color\":\"#ffffff\"},{\"x\":82,\"y\":86,\"color\":\"#ffffff\"},{\"x\":82,\"y\":85,\"color\":\"#ffffff\"},{\"x\":83,\"y\":85,\"color\":\"#ffffff\"},{\"x\":84,\"y\":84,\"color\":\"#ffffff\"},{\"x\":84,\"y\":83,\"color\":\"#ffffff\"},{\"x\":85,\"y\":81,\"color\":\"#ffffff\"},{\"x\":85,\"y\":80,\"color\":\"#ffffff\"},{\"x\":85,\"y\":79,\"color\":\"#ffffff\"},{\"x\":85,\"y\":78,\"color\":\"#ffffff\"},{\"x\":85,\"y\":77,\"color\":\"#ffffff\"},{\"x\":85,\"y\":76,\"color\":\"#ffffff\"},{\"x\":84,\"y\":76,\"color\":\"#ffffff\"},{\"x\":83,\"y\":76,\"color\":\"#ffffff\"},{\"x\":82,\"y\":76,\"color\":\"#ffffff\"},{\"x\":81,\"y\":76,\"color\":\"#ffffff\"},{\"x\":80,\"y\":76,\"color\":\"#ffffff\"},{\"x\":79,\"y\":76,\"color\":\"#ffffff\"},{\"x\":78,\"y\":76,\"color\":\"#ffffff\"},{\"x\":77,\"y\":76,\"color\":\"#ffffff\"},{\"x\":76,\"y\":76,\"color\":\"#ffffff\"},{\"x\":76,\"y\":77,\"color\":\"#ffffff\"},{\"x\":75,\"y\":78,\"color\":\"#ffffff\"},{\"x\":74,\"y\":78,\"color\":\"#ffffff\"},{\"x\":72,\"y\":79,\"color\":\"#ffffff\"},{\"x\":71,\"y\":80,\"color\":\"#ffffff\"},{\"x\":70,\"y\":80,\"color\":\"#ffffff\"},{\"x\":70,\"y\":81,\"color\":\"#ffffff\"},{\"x\":69,\"y\":82,\"color\":\"#ffffff\"},{\"x\":68,\"y\":82,\"color\":\"#ffffff\"},{\"x\":68,\"y\":83,\"color\":\"#ffffff\"},{\"x\":67,\"y\":83,\"color\":\"#ffffff\"},{\"x\":67,\"y\":84,\"color\":\"#ffffff\"},{\"x\":67,\"y\":85,\"color\":\"#ffffff\"},{\"x\":66,\"y\":87,\"color\":\"#ffffff\"},{\"x\":66,\"y\":88,\"color\":\"#ffffff\"},{\"x\":65,\"y\":89,\"color\":\"#ffffff\"},{\"x\":65,\"y\":90,\"color\":\"#ffffff\"},{\"x\":65,\"y\":91,\"color\":\"#ffffff\"},{\"x\":65,\"y\":92,\"color\":\"#ffffff\"},{\"x\":65,\"y\":93,\"color\":\"#ffffff\"},{\"x\":65,\"y\":94,\"color\":\"#ffffff\"},{\"x\":65,\"y\":95,\"color\":\"#ffffff\"},{\"x\":65,\"y\":96,\"color\":\"#ffffff\"},{\"x\":65,\"y\":97,\"color\":\"#ffffff\"},{\"x\":65,\"y\":98,\"color\":\"#ffffff\"},{\"x\":65,\"y\":100,\"color\":\"#ffffff\"},{\"x\":66,\"y\":102,\"color\":\"#ffffff\"},{\"x\":67,\"y\":103,\"color\":\"#ffffff\"},{\"x\":68,\"y\":104,\"color\":\"#ffffff\"},{\"x\":69,\"y\":104,\"color\":\"#ffffff\"},{\"x\":70,\"y\":104,\"color\":\"#ffffff\"},{\"x\":71,\"y\":104,\"color\":\"#ffffff\"},{\"x\":72,\"y\":104,\"color\":\"#ffffff\"},{\"x\":73,\"y\":104,\"color\":\"#ffffff\"},{\"x\":74,\"y\":104,\"color\":\"#ffffff\"},{\"x\":74,\"y\":103,\"color\":\"#ffffff\"},{\"x\":75,\"y\":103,\"color\":\"#ffffff\"},{\"x\":75,\"y\":102,\"color\":\"#ffffff\"},{\"x\":76,\"y\":101,\"color\":\"#ffffff\"},{\"x\":77,\"y\":101,\"color\":\"#ffffff\"},{\"x\":77,\"y\":100,\"color\":\"#ffffff\"},{\"x\":78,\"y\":100,\"color\":\"#ffffff\"},{\"x\":79,\"y\":99,\"color\":\"#ffffff\"},{\"x\":80,\"y\":99,\"color\":\"#ffffff\"}]},{\"points\":[{\"x\":120,\"y\":79,\"color\":\"#ffffff\"},{\"x\":119,\"y\":79,\"color\":\"#ffffff\"},{\"x\":118,\"y\":79,\"color\":\"#ffffff\"},{\"x\":117,\"y\":79,\"color\":\"#ffffff\"},{\"x\":116,\"y\":79,\"color\":\"#ffffff\"},{\"x\":115,\"y\":79,\"color\":\"#ffffff\"},{\"x\":114,\"y\":79,\"color\":\"#ffffff\"},{\"x\":113,\"y\":79,\"color\":\"#ffffff\"},{\"x\":112,\"y\":79,\"color\":\"#ffffff\"},{\"x\":111,\"y\":79,\"color\":\"#ffffff\"},{\"x\":110,\"y\":79,\"color\":\"#ffffff\"},{\"x\":109,\"y\":79,\"color\":\"#ffffff\"},{\"x\":108,\"y\":79,\"color\":\"#ffffff\"},{\"x\":107,\"y\":79,\"color\":\"#ffffff\"},{\"x\":106,\"y\":79,\"color\":\"#ffffff\"},{\"x\":105,\"y\":79,\"color\":\"#ffffff\"},{\"x\":105,\"y\":80,\"color\":\"#ffffff\"},{\"x\":104,\"y\":80,\"color\":\"#ffffff\"},{\"x\":104,\"y\":81,\"color\":\"#ffffff\"},{\"x\":104,\"y\":82,\"color\":\"#ffffff\"},{\"x\":104,\"y\":83,\"color\":\"#ffffff\"},{\"x\":105,\"y\":83,\"color\":\"#ffffff\"},{\"x\":105,\"y\":84,\"color\":\"#ffffff\"},{\"x\":107,\"y\":84,\"color\":\"#ffffff\"},{\"x\":107,\"y\":85,\"color\":\"#ffffff\"},{\"x\":108,\"y\":86,\"color\":\"#ffffff\"},{\"x\":109,\"y\":87,\"color\":\"#ffffff\"},{\"x\":110,\"y\":88,\"color\":\"#ffffff\"},{\"x\":111,\"y\":88,\"color\":\"#ffffff\"},{\"x\":111,\"y\":89,\"color\":\"#ffffff\"},{\"x\":112,\"y\":90,\"color\":\"#ffffff\"},{\"x\":112,\"y\":91,\"color\":\"#ffffff\"},{\"x\":113,\"y\":91,\"color\":\"#ffffff\"},{\"x\":113,\"y\":92,\"color\":\"#ffffff\"},{\"x\":114,\"y\":93,\"color\":\"#ffffff\"},{\"x\":114,\"y\":94,\"color\":\"#ffffff\"},{\"x\":115,\"y\":94,\"color\":\"#ffffff\"},{\"x\":115,\"y\":95,\"color\":\"#ffffff\"},{\"x\":115,\"y\":96,\"color\":\"#ffffff\"},{\"x\":115,\"y\":97,\"color\":\"#ffffff\"},{\"x\":115,\"y\":98,\"color\":\"#ffffff\"},{\"x\":116,\"y\":98,\"color\":\"#ffffff\"},{\"x\":116,\"y\":99,\"color\":\"#ffffff\"},{\"x\":116,\"y\":100,\"color\":\"#ffffff\"},{\"x\":116,\"y\":101,\"color\":\"#ffffff\"},{\"x\":116,\"y\":102,\"color\":\"#ffffff\"},{\"x\":116,\"y\":103,\"color\":\"#ffffff\"},{\"x\":116,\"y\":104,\"color\":\"#ffffff\"},{\"x\":116,\"y\":105,\"color\":\"#ffffff\"},{\"x\":116,\"y\":106,\"color\":\"#ffffff\"},{\"x\":116,\"y\":107,\"color\":\"#ffffff\"},{\"x\":116,\"y\":108,\"color\":\"#ffffff\"},{\"x\":116,\"y\":109,\"color\":\"#ffffff\"},{\"x\":115,\"y\":109,\"color\":\"#ffffff\"},{\"x\":114,\"y\":109,\"color\":\"#ffffff\"},{\"x\":113,\"y\":109,\"color\":\"#ffffff\"},{\"x\":112,\"y\":109,\"color\":\"#ffffff\"},{\"x\":111,\"y\":108,\"color\":\"#ffffff\"},{\"x\":109,\"y\":107,\"color\":\"#ffffff\"},{\"x\":108,\"y\":107,\"color\":\"#ffffff\"},{\"x\":107,\"y\":105,\"color\":\"#ffffff\"},{\"x\":106,\"y\":104,\"color\":\"#ffffff\"},{\"x\":104,\"y\":103,\"color\":\"#ffffff\"},{\"x\":103,\"y\":102,\"color\":\"#ffffff\"},{\"x\":102,\"y\":101,\"color\":\"#ffffff\"},{\"x\":102,\"y\":100,\"color\":\"#ffffff\"},{\"x\":101,\"y\":100,\"color\":\"#ffffff\"},{\"x\":101,\"y\":99,\"color\":\"#ffffff\"},{\"x\":100,\"y\":99,\"color\":\"#ffffff\"},{\"x\":100,\"y\":98,\"color\":\"#ffffff\"}]},{\"points\":[{\"x\":153,\"y\":64,\"color\":\"#ffffff\"},{\"x\":153,\"y\":65,\"color\":\"#ffffff\"},{\"x\":153,\"y\":67,\"color\":\"#ffffff\"},{\"x\":154,\"y\":68,\"color\":\"#ffffff\"},{\"x\":154,\"y\":71,\"color\":\"#ffffff\"},{\"x\":154,\"y\":73,\"color\":\"#ffffff\"},{\"x\":155,\"y\":75,\"color\":\"#ffffff\"},{\"x\":155,\"y\":76,\"color\":\"#ffffff\"},{\"x\":156,\"y\":79,\"color\":\"#ffffff\"},{\"x\":156,\"y\":81,\"color\":\"#ffffff\"},{\"x\":156,\"y\":82,\"color\":\"#ffffff\"},{\"x\":157,\"y\":85,\"color\":\"#ffffff\"},{\"x\":157,\"y\":86,\"color\":\"#ffffff\"},{\"x\":157,\"y\":89,\"color\":\"#ffffff\"},{\"x\":157,\"y\":90,\"color\":\"#ffffff\"},{\"x\":157,\"y\":93,\"color\":\"#ffffff\"},{\"x\":158,\"y\":96,\"color\":\"#ffffff\"},{\"x\":158,\"y\":97,\"color\":\"#ffffff\"},{\"x\":158,\"y\":99,\"color\":\"#ffffff\"},{\"x\":159,\"y\":100,\"color\":\"#ffffff\"},{\"x\":159,\"y\":102,\"color\":\"#ffffff\"},{\"x\":159,\"y\":103,\"color\":\"#ffffff\"},{\"x\":159,\"y\":104,\"color\":\"#ffffff\"},{\"x\":159,\"y\":105,\"color\":\"#ffffff\"},{\"x\":159,\"y\":106,\"color\":\"#ffffff\"},{\"x\":159,\"y\":107,\"color\":\"#ffffff\"}]},{\"points\":[{\"x\":144,\"y\":88,\"color\":\"#ffffff\"},{\"x\":145,\"y\":88,\"color\":\"#ffffff\"},{\"x\":148,\"y\":87,\"color\":\"#ffffff\"},{\"x\":149,\"y\":87,\"color\":\"#ffffff\"},{\"x\":151,\"y\":87,\"color\":\"#ffffff\"},{\"x\":153,\"y\":86,\"color\":\"#ffffff\"},{\"x\":155,\"y\":86,\"color\":\"#ffffff\"},{\"x\":157,\"y\":85,\"color\":\"#ffffff\"},{\"x\":159,\"y\":85,\"color\":\"#ffffff\"},{\"x\":160,\"y\":84,\"color\":\"#ffffff\"},{\"x\":162,\"y\":84,\"color\":\"#ffffff\"},{\"x\":164,\"y\":84,\"color\":\"#ffffff\"},{\"x\":165,\"y\":84,\"color\":\"#ffffff\"},{\"x\":168,\"y\":83,\"color\":\"#ffffff\"},{\"x\":169,\"y\":83,\"color\":\"#ffffff\"},{\"x\":170,\"y\":83,\"color\":\"#ffffff\"},{\"x\":171,\"y\":83,\"color\":\"#ffffff\"},{\"x\":173,\"y\":82,\"color\":\"#ffffff\"},{\"x\":174,\"y\":82,\"color\":\"#ffffff\"},{\"x\":176,\"y\":82,\"color\":\"#ffffff\"},{\"x\":178,\"y\":82,\"color\":\"#ffffff\"},{\"x\":179,\"y\":82,\"color\":\"#ffffff\"},{\"x\":180,\"y\":82,\"color\":\"#ffffff\"},{\"x\":181,\"y\":82,\"color\":\"#ffffff\"},{\"x\":182,\"y\":81,\"color\":\"#ffffff\"},{\"x\":183,\"y\":81,\"color\":\"#ffffff\"},{\"x\":184,\"y\":81,\"color\":\"#ffffff\"}]},{\"points\":[{\"x\":144,\"y\":88,\"color\":\"#ffffff\"},{\"x\":145,\"y\":88,\"color\":\"#ffffff\"},{\"x\":148,\"y\":87,\"color\":\"#ffffff\"},{\"x\":149,\"y\":87,\"color\":\"#ffffff\"},{\"x\":151,\"y\":87,\"color\":\"#ffffff\"},{\"x\":153,\"y\":86,\"color\":\"#ffffff\"},{\"x\":155,\"y\":86,\"color\":\"#ffffff\"},{\"x\":157,\"y\":85,\"color\":\"#ffffff\"},{\"x\":159,\"y\":85,\"color\":\"#ffffff\"},{\"x\":160,\"y\":84,\"color\":\"#ffffff\"},{\"x\":162,\"y\":84,\"color\":\"#ffffff\"},{\"x\":164,\"y\":84,\"color\":\"#ffffff\"},{\"x\":165,\"y\":84,\"color\":\"#ffffff\"},{\"x\":168,\"y\":83,\"color\":\"#ffffff\"},{\"x\":169,\"y\":83,\"color\":\"#ffffff\"},{\"x\":170,\"y\":83,\"color\":\"#ffffff\"},{\"x\":171,\"y\":83,\"color\":\"#ffffff\"},{\"x\":173,\"y\":82,\"color\":\"#ffffff\"},{\"x\":174,\"y\":82,\"color\":\"#ffffff\"},{\"x\":176,\"y\":82,\"color\":\"#ffffff\"},{\"x\":178,\"y\":82,\"color\":\"#ffffff\"},{\"x\":179,\"y\":82,\"color\":\"#ffffff\"},{\"x\":180,\"y\":82,\"color\":\"#ffffff\"},{\"x\":181,\"y\":82,\"color\":\"#ffffff\"},{\"x\":182,\"y\":81,\"color\":\"#ffffff\"},{\"x\":183,\"y\":81,\"color\":\"#ffffff\"},{\"x\":184,\"y\":81,\"color\":\"#ffffff\"}]}]}";

const char* jsonData2 = "{\"interpolate\":true,\"strokes\":[{\"points\":[{\"x\":49,\"y\":63,\"color\":\"#ffffff\"},{\"x\":49,\"y\":64,\"color\":\"#ffffff\"},{\"x\":49,\"y\":66,\"color\":\"#ffffff\"},{\"x\":49,\"y\":69,\"color\":\"#ffffff\"},{\"x\":49,\"y\":71,\"color\":\"#ffffff\"},{\"x\":49,\"y\":74,\"color\":\"#ffffff\"},{\"x\":49,\"y\":75,\"color\":\"#ffffff\"},{\"x\":49,\"y\":78,\"color\":\"#ffffff\"},{\"x\":49,\"y\":81,\"color\":\"#ffffff\"},{\"x\":49,\"y\":83,\"color\":\"#ffffff\"},{\"x\":49,\"y\":86,\"color\":\"#ffffff\"},{\"x\":49,\"y\":87,\"color\":\"#ffffff\"},{\"x\":49,\"y\":90,\"color\":\"#ffffff\"},{\"x\":49,\"y\":91,\"color\":\"#ffffff\"},{\"x\":49,\"y\":93,\"color\":\"#ffffff\"},{\"x\":49,\"y\":95,\"color\":\"#ffffff\"},{\"x\":49,\"y\":96,\"color\":\"#ffffff\"},{\"x\":49,\"y\":97,\"color\":\"#ffffff\"},{\"x\":49,\"y\":98,\"color\":\"#ffffff\"},{\"x\":49,\"y\":99,\"color\":\"#ffffff\"}]},{\"points\":[{\"x\":31,\"y\":58,\"color\":\"#ffffff\"},{\"x\":32,\"y\":58,\"color\":\"#ffffff\"},{\"x\":33,\"y\":58,\"color\":\"#ffffff\"},{\"x\":34,\"y\":58,\"color\":\"#ffffff\"},{\"x\":35,\"y\":58,\"color\":\"#ffffff\"},{\"x\":36,\"y\":58,\"color\":\"#ffffff\"},{\"x\":38,\"y\":58,\"color\":\"#ffffff\"},{\"x\":39,\"y\":58,\"color\":\"#ffffff\"},{\"x\":40,\"y\":58,\"color\":\"#ffffff\"},{\"x\":41,\"y\":58,\"color\":\"#ffffff\"},{\"x\":43,\"y\":58,\"color\":\"#ffffff\"},{\"x\":44,\"y\":58,\"color\":\"#ffffff\"},{\"x\":46,\"y\":58,\"color\":\"#ffffff\"},{\"x\":47,\"y\":58,\"color\":\"#ffffff\"},{\"x\":48,\"y\":58,\"color\":\"#ffffff\"},{\"x\":50,\"y\":58,\"color\":\"#ffffff\"},{\"x\":52,\"y\":58,\"color\":\"#ffffff\"},{\"x\":53,\"y\":58,\"color\":\"#ffffff\"},{\"x\":54,\"y\":58,\"color\":\"#ffffff\"},{\"x\":56,\"y\":58,\"color\":\"#ffffff\"},{\"x\":57,\"y\":58,\"color\":\"#ffffff\"},{\"x\":58,\"y\":58,\"color\":\"#ffffff\"},{\"x\":59,\"y\":58,\"color\":\"#ffffff\"},{\"x\":60,\"y\":58,\"color\":\"#ffffff\"},{\"x\":61,\"y\":58,\"color\":\"#ffffff\"},{\"x\":62,\"y\":58,\"color\":\"#ffffff\"}]},{\"points\":[{\"x\":61,\"y\":83,\"color\":\"#ffffff\"},{\"x\":61,\"y\":84,\"color\":\"#ffffff\"},{\"x\":62,\"y\":84,\"color\":\"#ffffff\"},{\"x\":63,\"y\":84,\"color\":\"#ffffff\"},{\"x\":64,\"y\":84,\"color\":\"#ffffff\"},{\"x\":65,\"y\":84,\"color\":\"#ffffff\"},{\"x\":67,\"y\":84,\"color\":\"#ffffff\"},{\"x\":68,\"y\":85,\"color\":\"#ffffff\"},{\"x\":70,\"y\":85,\"color\":\"#ffffff\"},{\"x\":71,\"y\":86,\"color\":\"#ffffff\"},{\"x\":72,\"y\":86,\"color\":\"#ffffff\"},{\"x\":73,\"y\":86,\"color\":\"#ffffff\"},{\"x\":74,\"y\":86,\"color\":\"#ffffff\"},{\"x\":76,\"y\":86,\"color\":\"#ffffff\"},{\"x\":77,\"y\":86,\"color\":\"#ffffff\"},{\"x\":78,\"y\":86,\"color\":\"#ffffff\"},{\"x\":79,\"y\":86,\"color\":\"#ffffff\"},{\"x\":80,\"y\":86,\"color\":\"#ffffff\"},{\"x\":82,\"y\":86,\"color\":\"#ffffff\"},{\"x\":82,\"y\":85,\"color\":\"#ffffff\"},{\"x\":83,\"y\":85,\"color\":\"#ffffff\"},{\"x\":84,\"y\":84,\"color\":\"#ffffff\"},{\"x\":84,\"y\":83,\"color\":\"#ffffff\"},{\"x\":85,\"y\":81,\"color\":\"#ffffff\"},{\"x\":85,\"y\":80,\"color\":\"#ffffff\"},{\"x\":85,\"y\":79,\"color\":\"#ffffff\"},{\"x\":85,\"y\":78,\"color\":\"#ffffff\"},{\"x\":85,\"y\":77,\"color\":\"#ffffff\"},{\"x\":85,\"y\":76,\"color\":\"#ffffff\"},{\"x\":84,\"y\":76,\"color\":\"#ffffff\"},{\"x\":83,\"y\":76,\"color\":\"#ffffff\"},{\"x\":82,\"y\":76,\"color\":\"#ffffff\"},{\"x\":81,\"y\":76,\"color\":\"#ffffff\"},{\"x\":80,\"y\":76,\"color\":\"#ffffff\"},{\"x\":79,\"y\":76,\"color\":\"#ffffff\"},{\"x\":78,\"y\":76,\"color\":\"#ffffff\"},{\"x\":77,\"y\":76,\"color\":\"#ffffff\"},{\"x\":76,\"y\":76,\"color\":\"#ffffff\"},{\"x\":76,\"y\":77,\"color\":\"#ffffff\"},{\"x\":75,\"y\":78,\"color\":\"#ffffff\"},{\"x\":74,\"y\":78,\"color\":\"#ffffff\"},{\"x\":72,\"y\":79,\"color\":\"#ffffff\"},{\"x\":71,\"y\":80,\"color\":\"#ffffff\"},{\"x\":70,\"y\":80,\"color\":\"#ffffff\"},{\"x\":70,\"y\":81,\"color\":\"#ffffff\"},{\"x\":69,\"y\":82,\"color\":\"#ffffff\"},{\"x\":68,\"y\":82,\"color\":\"#ffffff\"},{\"x\":68,\"y\":83,\"color\":\"#ffffff\"},{\"x\":67,\"y\":83,\"color\":\"#ffffff\"},{\"x\":67,\"y\":84,\"color\":\"#ffffff\"},{\"x\":67,\"y\":85,\"color\":\"#ffffff\"},{\"x\":66,\"y\":87,\"color\":\"#ffffff\"},{\"x\":66,\"y\":88,\"color\":\"#ffffff\"},{\"x\":65,\"y\":89,\"color\":\"#ffffff\"},{\"x\":65,\"y\":90,\"color\":\"#ffffff\"},{\"x\":65,\"y\":91,\"color\":\"#ffffff\"},{\"x\":65,\"y\":92,\"color\":\"#ffffff\"},{\"x\":65,\"y\":93,\"color\":\"#ffffff\"},{\"x\":65,\"y\":94,\"color\":\"#ffffff\"},{\"x\":65,\"y\":95,\"color\":\"#ffffff\"},{\"x\":65,\"y\":96,\"color\":\"#ffffff\"},{\"x\":65,\"y\":97,\"color\":\"#ffffff\"},{\"x\":65,\"y\":98,\"color\":\"#ffffff\"},{\"x\":65,\"y\":100,\"color\":\"#ffffff\"},{\"x\":66,\"y\":102,\"color\":\"#ffffff\"},{\"x\":67,\"y\":103,\"color\":\"#ffffff\"},{\"x\":68,\"y\":104,\"color\":\"#ffffff\"},{\"x\":69,\"y\":104,\"color\":\"#ffffff\"},{\"x\":70,\"y\":104,\"color\":\"#ffffff\"},{\"x\":71,\"y\":104,\"color\":\"#ffffff\"},{\"x\":72,\"y\":104,\"color\":\"#ffffff\"},{\"x\":73,\"y\":104,\"color\":\"#ffffff\"},{\"x\":74,\"y\":104,\"color\":\"#ffffff\"},{\"x\":74,\"y\":103,\"color\":\"#ffffff\"},{\"x\":75,\"y\":103,\"color\":\"#ffffff\"},{\"x\":75,\"y\":102,\"color\":\"#ffffff\"},{\"x\":76,\"y\":101,\"color\":\"#ffffff\"},{\"x\":77,\"y\":101,\"color\":\"#ffffff\"},{\"x\":77,\"y\":100,\"color\":\"#ffffff\"},{\"x\":78,\"y\":100,\"color\":\"#ffffff\"},{\"x\":79,\"y\":99,\"color\":\"#ffffff\"},{\"x\":80,\"y\":99,\"color\":\"#ffffff\"}]},{\"points\":[{\"x\":120,\"y\":79,\"color\":\"#ffffff\"},{\"x\":119,\"y\":79,\"color\":\"#ffffff\"},{\"x\":118,\"y\":79,\"color\":\"#ffffff\"},{\"x\":117,\"y\":79,\"color\":\"#ffffff\"},{\"x\":116,\"y\":79,\"color\":\"#ffffff\"},{\"x\":115,\"y\":79,\"color\":\"#ffffff\"},{\"x\":114,\"y\":79,\"color\":\"#ffffff\"},{\"x\":113,\"y\":79,\"color\":\"#ffffff\"},{\"x\":112,\"y\":79,\"color\":\"#ffffff\"},{\"x\":111,\"y\":79,\"color\":\"#ffffff\"},{\"x\":110,\"y\":79,\"color\":\"#ffffff\"},{\"x\":109,\"y\":79,\"color\":\"#ffffff\"},{\"x\":108,\"y\":79,\"color\":\"#ffffff\"},{\"x\":107,\"y\":79,\"color\":\"#ffffff\"},{\"x\":106,\"y\":79,\"color\":\"#ffffff\"},{\"x\":105,\"y\":79,\"color\":\"#ffffff\"},{\"x\":105,\"y\":80,\"color\":\"#ffffff\"},{\"x\":104,\"y\":80,\"color\":\"#ffffff\"},{\"x\":104,\"y\":81,\"color\":\"#ffffff\"},{\"x\":104,\"y\":82,\"color\":\"#ffffff\"},{\"x\":104,\"y\":83,\"color\":\"#ffffff\"},{\"x\":105,\"y\":83,\"color\":\"#ffffff\"},{\"x\":105,\"y\":84,\"color\":\"#ffffff\"},{\"x\":107,\"y\":84,\"color\":\"#ffffff\"},{\"x\":107,\"y\":85,\"color\":\"#ffffff\"},{\"x\":108,\"y\":86,\"color\":\"#ffffff\"},{\"x\":109,\"y\":87,\"color\":\"#ffffff\"},{\"x\":110,\"y\":88,\"color\":\"#ffffff\"},{\"x\":111,\"y\":88,\"color\":\"#ffffff\"},{\"x\":111,\"y\":89,\"color\":\"#ffffff\"},{\"x\":112,\"y\":90,\"color\":\"#ffffff\"},{\"x\":112,\"y\":91,\"color\":\"#ffffff\"},{\"x\":113,\"y\":91,\"color\":\"#ffffff\"},{\"x\":113,\"y\":92,\"color\":\"#ffffff\"},{\"x\":114,\"y\":93,\"color\":\"#ffffff\"},{\"x\":114,\"y\":94,\"color\":\"#ffffff\"},{\"x\":115,\"y\":94,\"color\":\"#ffffff\"},{\"x\":115,\"y\":95,\"color\":\"#ffffff\"},{\"x\":115,\"y\":96,\"color\":\"#ffffff\"},{\"x\":115,\"y\":97,\"color\":\"#ffffff\"},{\"x\":115,\"y\":98,\"color\":\"#ffffff\"},{\"x\":116,\"y\":98,\"color\":\"#ffffff\"},{\"x\":116,\"y\":99,\"color\":\"#ffffff\"},{\"x\":116,\"y\":100,\"color\":\"#ffffff\"},{\"x\":116,\"y\":101,\"color\":\"#ffffff\"},{\"x\":116,\"y\":102,\"color\":\"#ffffff\"},{\"x\":116,\"y\":103,\"color\":\"#ffffff\"},{\"x\":116,\"y\":104,\"color\":\"#ffffff\"},{\"x\":116,\"y\":105,\"color\":\"#ffffff\"},{\"x\":116,\"y\":106,\"color\":\"#ffffff\"},{\"x\":116,\"y\":107,\"color\":\"#ffffff\"},{\"x\":116,\"y\":108,\"color\":\"#ffffff\"},{\"x\":116,\"y\":109,\"color\":\"#ffffff\"},{\"x\":115,\"y\":109,\"color\":\"#ffffff\"},{\"x\":114,\"y\":109,\"color\":\"#ffffff\"},{\"x\":113,\"y\":109,\"color\":\"#ffffff\"},{\"x\":112,\"y\":109,\"color\":\"#ffffff\"},{\"x\":111,\"y\":108,\"color\":\"#ffffff\"},{\"x\":109,\"y\":107,\"color\":\"#ffffff\"},{\"x\":108,\"y\":107,\"color\":\"#ffffff\"},{\"x\":107,\"y\":105,\"color\":\"#ffffff\"},{\"x\":106,\"y\":104,\"color\":\"#ffffff\"},{\"x\":104,\"y\":103,\"color\":\"#ffffff\"},{\"x\":103,\"y\":102,\"color\":\"#ffffff\"},{\"x\":102,\"y\":101,\"color\":\"#ffffff\"},{\"x\":102,\"y\":100,\"color\":\"#ffffff\"},{\"x\":101,\"y\":100,\"color\":\"#ffffff\"},{\"x\":101,\"y\":99,\"color\":\"#ffffff\"},{\"x\":100,\"y\":99,\"color\":\"#ffffff\"},{\"x\":100,\"y\":98,\"color\":\"#ffffff\"}]},{\"points\":[{\"x\":153,\"y\":64,\"color\":\"#ffffff\"},{\"x\":153,\"y\":65,\"color\":\"#ffffff\"},{\"x\":153,\"y\":67,\"color\":\"#ffffff\"},{\"x\":154,\"y\":68,\"color\":\"#ffffff\"},{\"x\":154,\"y\":71,\"color\":\"#ffffff\"},{\"x\":154,\"y\":73,\"color\":\"#ffffff\"},{\"x\":155,\"y\":75,\"color\":\"#ffffff\"},{\"x\":155,\"y\":76,\"color\":\"#ffffff\"},{\"x\":156,\"y\":79,\"color\":\"#ffffff\"},{\"x\":156,\"y\":81,\"color\":\"#ffffff\"},{\"x\":156,\"y\":82,\"color\":\"#ffffff\"},{\"x\":157,\"y\":85,\"color\":\"#ffffff\"},{\"x\":157,\"y\":86,\"color\":\"#ffffff\"},{\"x\":157,\"y\":89,\"color\":\"#ffffff\"},{\"x\":157,\"y\":90,\"color\":\"#ffffff\"},{\"x\":157,\"y\":93,\"color\":\"#ffffff\"},{\"x\":158,\"y\":96,\"color\":\"#ffffff\"},{\"x\":158,\"y\":97,\"color\":\"#ffffff\"},{\"x\":158,\"y\":99,\"color\":\"#ffffff\"},{\"x\":159,\"y\":100,\"color\":\"#ffffff\"},{\"x\":159,\"y\":102,\"color\":\"#ffffff\"},{\"x\":159,\"y\":103,\"color\":\"#ffffff\"},{\"x\":159,\"y\":104,\"color\":\"#ffffff\"},{\"x\":159,\"y\":105,\"color\":\"#ffffff\"},{\"x\":159,\"y\":106,\"color\":\"#ffffff\"},{\"x\":159,\"y\":107,\"color\":\"#ffffff\"}]},{\"points\":[{\"x\":144,\"y\":88,\"color\":\"#ffffff\"},{\"x\":145,\"y\":88,\"color\":\"#ffffff\"},{\"x\":148,\"y\":87,\"color\":\"#ffffff\"},{\"x\":149,\"y\":87,\"color\":\"#ffffff\"},{\"x\":151,\"y\":87,\"color\":\"#ffffff\"},{\"x\":153,\"y\":86,\"color\":\"#ffffff\"},{\"x\":155,\"y\":86,\"color\":\"#ffffff\"},{\"x\":157,\"y\":85,\"color\":\"#ffffff\"},{\"x\":159,\"y\":85,\"color\":\"#ffffff\"},{\"x\":160,\"y\":84,\"color\":\"#ffffff\"},{\"x\":162,\"y\":84,\"color\":\"#ffffff\"},{\"x\":164,\"y\":84,\"color\":\"#ffffff\"},{\"x\":165,\"y\":84,\"color\":\"#ffffff\"},{\"x\":168,\"y\":83,\"color\":\"#ffffff\"},{\"x\":169,\"y\":83,\"color\":\"#ffffff\"},{\"x\":170,\"y\":83,\"color\":\"#ffffff\"},{\"x\":171,\"y\":83,\"color\":\"#ffffff\"},{\"x\":173,\"y\":82,\"color\":\"#ffffff\"},{\"x\":174,\"y\":82,\"color\":\"#ffffff\"},{\"x\":176,\"y\":82,\"color\":\"#ffffff\"},{\"x\":178,\"y\":82,\"color\":\"#ffffff\"},{\"x\":179,\"y\":82,\"color\":\"#ffffff\"},{\"x\":180,\"y\":82,\"color\":\"#ffffff\"},{\"x\":181,\"y\":82,\"color\":\"#ffffff\"},{\"x\":182,\"y\":81,\"color\":\"#ffffff\"},{\"x\":183,\"y\":81,\"color\":\"#ffffff\"},{\"x\":184,\"y\":81,\"color\":\"#ffffff\"}]},{\"points\":[{\"x\":144,\"y\":88,\"color\":\"#ffffff\"},{\"x\":145,\"y\":88,\"color\":\"#ffffff\"},{\"x\":148,\"y\":87,\"color\":\"#ffffff\"},{\"x\":149,\"y\":87,\"color\":\"#ffffff\"},{\"x\":151,\"y\":87,\"color\":\"#ffffff\"},{\"x\":153,\"y\":86,\"color\":\"#ffffff\"},{\"x\":155,\"y\":86,\"color\":\"#ffffff\"},{\"x\":157,\"y\":85,\"color\":\"#ffffff\"},{\"x\":159,\"y\":85,\"color\":\"#ffffff\"},{\"x\":160,\"y\":84,\"color\":\"#ffffff\"},{\"x\":162,\"y\":84,\"color\":\"#ffffff\"},{\"x\":164,\"y\":84,\"color\":\"#ffffff\"},{\"x\":165,\"y\":84,\"color\":\"#ffffff\"},{\"x\":168,\"y\":83,\"color\":\"#ffffff\"},{\"x\":169,\"y\":83,\"color\":\"#ffffff\"},{\"x\":170,\"y\":83,\"color\":\"#ffffff\"},{\"x\":171,\"y\":83,\"color\":\"#ffffff\"},{\"x\":173,\"y\":82,\"color\":\"#ffffff\"},{\"x\":174,\"y\":82,\"color\":\"#ffffff\"},{\"x\":176,\"y\":82,\"color\":\"#ffffff\"},{\"x\":178,\"y\":82,\"color\":\"#ffffff\"},{\"x\":179,\"y\":82,\"color\":\"#ffffff\"},{\"x\":180,\"y\":82,\"color\":\"#ffffff\"},{\"x\":181,\"y\":82,\"color\":\"#ffffff\"},{\"x\":182,\"y\":81,\"color\":\"#ffffff\"},{\"x\":183,\"y\":81,\"color\":\"#ffffff\"},{\"x\":184,\"y\":81,\"color\":\"#ffffff\"}]},{\"points\":[{\"x\":144,\"y\":88,\"color\":\"#ffffff\"},{\"x\":145,\"y\":88,\"color\":\"#ffffff\"},{\"x\":148,\"y\":87,\"color\":\"#ffffff\"},{\"x\":149,\"y\":87,\"color\":\"#ffffff\"},{\"x\":151,\"y\":87,\"color\":\"#ffffff\"},{\"x\":153,\"y\":86,\"color\":\"#ffffff\"},{\"x\":155,\"y\":86,\"color\":\"#ffffff\"},{\"x\":157,\"y\":85,\"color\":\"#ffffff\"},{\"x\":159,\"y\":85,\"color\":\"#ffffff\"},{\"x\":160,\"y\":84,\"color\":\"#ffffff\"},{\"x\":162,\"y\":84,\"color\":\"#ffffff\"},{\"x\":164,\"y\":84,\"color\":\"#ffffff\"},{\"x\":165,\"y\":84,\"color\":\"#ffffff\"},{\"x\":168,\"y\":83,\"color\":\"#ffffff\"},{\"x\":169,\"y\":83,\"color\":\"#ffffff\"},{\"x\":170,\"y\":83,\"color\":\"#ffffff\"},{\"x\":171,\"y\":83,\"color\":\"#ffffff\"},{\"x\":173,\"y\":82,\"color\":\"#ffffff\"},{\"x\":174,\"y\":82,\"color\":\"#ffffff\"},{\"x\":176,\"y\":82,\"color\":\"#ffffff\"},{\"x\":178,\"y\":82,\"color\":\"#ffffff\"},{\"x\":179,\"y\":82,\"color\":\"#ffffff\"},{\"x\":180,\"y\":82,\"color\":\"#ffffff\"},{\"x\":181,\"y\":82,\"color\":\"#ffffff\"},{\"x\":182,\"y\":81,\"color\":\"#ffffff\"},{\"x\":183,\"y\":81,\"color\":\"#ffffff\"},{\"x\":184,\"y\":81,\"color\":\"#ffffff\"}]}]}";

void setup() {
    Serial.begin(115200);
    touch.begin();
    // PSRAM Initialize
    if (psramInit()) {
        Serial.println("\nPSRAM is correctly initialized");
    } else {
        Serial.println("PSRAM not available");
    }
    if ((BlackImage = (UWORD *)ps_malloc(Imagesize)) == NULL) {
        Serial.println("Failed to apply for black memory...");
        exit(0);
    }

    // Initialize GPIO and display
    if (DEV_Module_Init() != 0)
        Serial.println("GPIO Init Fail!");
    else
        Serial.println("GPIO Init successful!");

    LCD_1IN28_Init(HORIZONTAL);
    LCD_1IN28_Clear(BLACK);

    // Create a new image cache named IMAGE_RGB and fill it with BLACK
    Paint_NewImage((UBYTE *)BlackImage, LCD_1IN28.WIDTH, LCD_1IN28.HEIGHT, 0, BLACK);
    Paint_SetScale(65);
    Paint_SetRotate(ROTATE_0);
    Paint_Clear(BLACK);

    // Initial display
    displayJsonData();
}

void drawOnScreen() {
    // Handle screen touches and toggle between two JSON data sets
    if (touch.available()) {
        touchCount++;
        toggleCount++;
        Serial.print("Touch detected! Count: ");
        Serial.println(touchCount);

        if (toggleCount >= 2) { // Toggle after every second touch
            displayFirstJson = !displayFirstJson;
            displayJsonData();
            toggleCount = 0; // Reset toggle count
        }

        delay(50); // Debounce delay
    }
}

// Helper function to convert hex color string (e.g., "#RRGGBB") to RGB565 format
uint16_t parseHexColor(const char* hexColor) {
    uint8_t r = strtol(hexColor + 1, NULL, 16) >> 16;
    uint8_t g = strtol(hexColor + 3, NULL, 16) >> 8;
    uint8_t b = strtol(hexColor + 5, NULL, 16);

    // Convert RGB888 to RGB565
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

// Linear interpolation function between two points
int lerp(int start, int end, float t) {
    return start + t * (end - start);
}

void interpolateAndDraw(int x0, int y0, int x1, int y1, uint16_t color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int steps = max(dx, dy);
    float increment = 1.0 / steps;

    for (int i = 0; i <= steps; i++) {
        float t = i * increment;
        int x = lerp(x0, x1, t);
        int y = lerp(y0, y1, t);
        Paint_DrawPoint(x, y, color, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    }
}

void displayJsonData() {
    StaticJsonDocument<8000> doc;  // Increase size if necessary
    const char* jsonData = displayFirstJson ? jsonData1 : jsonData2;

    DeserializationError error = deserializeJson(doc, jsonData);

    if (error) {
        Serial.print("Failed to parse JSON: ");
        Serial.println(error.c_str());
        return;
    }

    bool interpolate = doc["interpolate"];
    JsonArray strokes = doc["strokes"];

    Paint_Clear(BLACK); // Clear the display before drawing new content

    for (JsonObject stroke : strokes) {
        int prevX = -1;
        int prevY = -1;
        const char* prevColorStr = "";

        JsonArray points = stroke["points"];
        for (JsonObject point : points) {
            int x = point["x"];
            int y = point["y"];
            const char* colorStr = point["color"];

            // Convert the color string to an RGB565 format
            uint16_t color = parseHexColor(colorStr);

            // If this is not the first point and interpolation is enabled, interpolate from the previous point
            if (interpolate && prevX != -1 && prevY != -1 && strcmp(prevColorStr, colorStr) == 0) {
                interpolateAndDraw(prevX, prevY, x, y, color);
            }

            // Update previous point
            prevX = x;
            prevY = y;
            prevColorStr = colorStr;

            // Draw the current point
            Paint_DrawPoint(x, y, color, DOT_PIXEL_1X1, DOT_STYLE_DFT);
        }
    }

    // Refresh the display
    LCD_1IN28_Display(BlackImage);
}

void loop() {
    drawOnScreen();
}
