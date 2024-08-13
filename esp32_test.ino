#include <Arduino.h>
#include <ArduinoJson.h>
#include "LCD_Test.h"

UWORD Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
UWORD *BlackImage;
CST816S touch(6, 7, 13, 5); // sda, scl, rst, irq

bool displayFirstJson = true;

const char* jsonData1 = "{\"interpolate\":false,\"strokes\":[{\"x\":[42,42,42,42,42,42,42,42,42,42,44,45,47,48,49,52,54,56,58,60,63,66,68,71,74,77,81,84,87,89,92,97,99,102,105,108,111,114,117,120,124,127,131,133,136,137,139,141,142,143,144,144,144,144,144,144,143,141,140,139,138,137,136,133,132,130,129,127,125,123,120,118,114,112,108,106,102,99,95,93,89,86,82,80,78,74,74,72,71,70,70,70,70,70,70,71,72,74,76,78,80,83,86,88,93,95,99,104,108,114,119,125,132,136,143,149,156,162,169,173,179,184,188,193,195,198,201,204,207,208,210,211,212,42,42,42,42,42,42,42,42,42,42,44,45,47,48,49,52,54,56,58,60,63,66,68,71,74,77,81,84,87,89,92,97,99,102,105,108,111,114,117,120,124,127,131,133,136,137,139,141,142,143,144,144,144,144,144,144,143,141,140,139,138,137,136,133,132,130,129,127,125,123,120,118,114,112,108,106,102,99,95,93,89,86,82,80,78,74,74,72,71,70,70,70,70,70,70,71,72,74,76,78,80,83,86,88,93,95,99,104,108,114,119,125,132,136,143,149,156,162,169,173,179,184,188,193,195,198,201,204,207,208,210,211,212],\"y\":[129,128,127,126,124,122,119,116,113,110,106,103,100,97,94,91,89,86,83,81,79,77,75,74,72,71,69,69,69,69,69,69,69,70,71,73,75,77,80,83,88,92,97,100,105,108,110,116,119,123,126,127,131,132,136,137,139,141,143,143,144,145,146,147,148,149,149,149,149,150,150,150,150,150,150,150,148,148,147,146,145,144,142,141,141,139,138,137,135,134,132,130,128,124,123,117,115,112,109,106,103,101,98,96,93,92,90,89,88,88,87,87,87,87,87,87,88,89,92,93,95,97,98,101,102,104,106,108,109,110,112,113,113,129,128,127,126,124,122,119,116,113,110,106,103,100,97,94,91,89,86,83,81,79,77,75,74,72,71,69,69,69,69,69,69,69,70,71,73,75,77,80,83,88,92,97,100,105,108,110,116,119,123,126,127,131,132,136,137,139,141,143,143,144,145,146,147,148,149,149,149,149,150,150,150,150,150,150,150,148,148,147,146,145,144,142,141,141,139,138,137,135,134,132,130,128,124,123,117,115,112,109,106,103,101,98,96,93,92,90,89,88,88,87,87,87,87,87,87,88,89,92,93,95,97,98,101,102,104,106,108,109,110,112,113,113],\"color\":[\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\"]}]}";
const char* jsonData2 = "{\"interpolate\":true,\"strokes\":[{\"x\":[42,42,42,42,42,42,42,42,42,42,44,45,47,48,49,52,54,56,58,60,63,66,68,71,74,77,81,84,87,89,92,97,99,102,105,108,111,114,117,120,124,127,131,133,136,137,139,141,142,143,144,144,144,144,144,144,143,141,140,139,138,137,136,133,132,130,129,127,125,123,120,118,114,112,108,106,102,99,95,93,89,86,82,80,78,74,74,72,71,70,70,70,70,70,70,71,72,74,76,78,80,83,86,88,93,95,99,104,108,114,119,125,132,136,143,149,156,162,169,173,179,184,188,193,195,198,201,204,207,208,210,211,212,42,42,42,42,42,42,42,42,42,42,44,45,47,48,49,52,54,56,58,60,63,66,68,71,74,77,81,84,87,89,92,97,99,102,105,108,111,114,117,120,124,127,131,133,136,137,139,141,142,143,144,144,144,144,144,144,143,141,140,139,138,137,136,133,132,130,129,127,125,123,120,118,114,112,108,106,102,99,95,93,89,86,82,80,78,74,74,72,71,70,70,70,70,70,70,71,72,74,76,78,80,83,86,88,93,95,99,104,108,114,119,125,132,136,143,149,156,162,169,173,179,184,188,193,195,198,201,204,207,208,210,211,212,42,42,42,42,42,42,42,42,42,42,44,45,47,48,49,52,54,56,58,60,63,66,68,71,74,77,81,84,87,89,92,97,99,102,105,108,111,114,117,120,124,127,131,133,136,137,139,141,142,143,144,144,144,144,144,144,143,141,140,139,138,137,136,133,132,130,129,127,125,123,120,118,114,112,108,106,102,99,95,93,89,86,82,80,78,74,74,72,71,70,70,70,70,70,70,71,72,74,76,78,80,83,86,88,93,95,99,104,108,114,119,125,132,136,143,149,156,162,169,173,179,184,188,193,195,198,201,204,207,208,210,211,212],\"y\":[129,128,127,126,124,122,119,116,113,110,106,103,100,97,94,91,89,86,83,81,79,77,75,74,72,71,69,69,69,69,69,69,69,70,71,73,75,77,80,83,88,92,97,100,105,108,110,116,119,123,126,127,131,132,136,137,139,141,143,143,144,145,146,147,148,149,149,149,149,150,150,150,150,150,150,150,148,148,147,146,145,144,142,141,141,139,138,137,135,134,132,130,128,124,123,117,115,112,109,106,103,101,98,96,93,92,90,89,88,88,87,87,87,87,87,87,88,89,92,93,95,97,98,101,102,104,106,108,109,110,112,113,113,129,128,127,126,124,122,119,116,113,110,106,103,100,97,94,91,89,86,83,81,79,77,75,74,72,71,69,69,69,69,69,69,69,70,71,73,75,77,80,83,88,92,97,100,105,108,110,116,119,123,126,127,131,132,136,137,139,141,143,143,144,145,146,147,148,149,149,149,149,150,150,150,150,150,150,150,148,148,147,146,145,144,142,141,141,139,138,137,135,134,132,130,128,124,123,117,115,112,109,106,103,101,98,96,93,92,90,89,88,88,87,87,87,87,87,87,88,89,92,93,95,97,98,101,102,104,106,108,109,110,112,113,113,129,128,127,126,124,122,119,116,113,110,106,103,100,97,94,91,89,86,83,81,79,77,75,74,72,71,69,69,69,69,69,69,69,70,71,73,75,77,80,83,88,92,97,100,105,108,110,116,119,123,126,127,131,132,136,137,139,141,143,143,144,145,146,147,148,149,149,149,149,150,150,150,150,150,150,150,148,148,147,146,145,144,142,141,141,139,138,137,135,134,132,130,128,124,123,117,115,112,109,106,103,101,98,96,93,92,90,89,88,88,87,87,87,87,87,87,88,89,92,93,95,97,98,101,102,104,106,108,109,110,112,113,113],\"color\":[\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\",\"#ffffff\"]}]}";

bool wasTouchedLastTime = false; // To track the touch state

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
        if (!wasTouchedLastTime) { // Check if this is a new touch after lifting
            displayFirstJson = !displayFirstJson;
            displayJsonData();
            wasTouchedLastTime = true; // Set the flag to indicate the screen is currently being touched
            Serial.println("Touch detected and toggled display.");
        }
    } else {
        wasTouchedLastTime = false; // Reset the flag when the touch is released
    }

    delay(10); // Debounce delay
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
    int steps = max(dx, dy); // Calculate the number of steps required for interpolation
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
        JsonArray xArray = stroke["x"];
        JsonArray yArray = stroke["y"];
        JsonArray colorArray = stroke["color"];

        int prevX = xArray[0];
        int prevY = yArray[0];
        const char* prevColorStr = colorArray[0];

        for (int i = 1; i < xArray.size(); i++) {
            int x = xArray[i];
            int y = yArray[i];
            const char* colorStr = colorArray[i];

            uint16_t color = parseHexColor(colorStr);

            if (interpolate && strcmp(prevColorStr, colorStr) == 0) {
                interpolateAndDraw(prevX, prevY, x, y, color);
            }

            Paint_DrawPoint(x, y, color, DOT_PIXEL_1X1, DOT_STYLE_DFT);

            prevX = x;
            prevY = y;
            prevColorStr = colorStr;
        }
    }

    LCD_1IN28_Display(BlackImage);
}

void loop() {
    drawOnScreen();
}
