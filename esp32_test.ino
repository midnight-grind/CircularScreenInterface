#include <Arduino.h>
#include <ArduinoJson.h>
#include "LCD_Test.h"

UWORD Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
UWORD *BlackImage;
CST816S touch(6, 7, 13, 5); // sda, scl, rst, irq

int lastX = -1;
int lastY = -1;

const char* jsonData = "{\"interpolate\":false,\"points\":[{\"x\":67,\"y\":131,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":67,\"y\":130,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":67,\"y\":129,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":67,\"y\":127,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":67,\"y\":122,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":67,\"y\":120,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":68,\"y\":118,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":69,\"y\":115,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":70,\"y\":112,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":72,\"y\":109,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":74,\"y\":105,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":76,\"y\":101,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":78,\"y\":98,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":84,\"y\":90,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":87,\"y\":88,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":91,\"y\":83,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":94,\"y\":80,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":98,\"y\":77,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":102,\"y\":75,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":105,\"y\":72,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":109,\"y\":70,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":113,\"y\":69,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":120,\"y\":68,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":121,\"y\":68,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":124,\"y\":67,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":127,\"y\":67,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":129,\"y\":67,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":132,\"y\":67,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":134,\"y\":68,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":136,\"y\":69,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":137,\"y\":72,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":141,\"y\":78,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":142,\"y\":79,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":143,\"y\":84,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":145,\"y\":89,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":145,\"y\":94,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":147,\"y\":100,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":147,\"y\":108,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":147,\"y\":114,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":147,\"y\":119,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":147,\"y\":134,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":146,\"y\":136,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":145,\"y\":142,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":143,\"y\":146,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":141,\"y\":150,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":140,\"y\":153,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":137,\"y\":156,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":135,\"y\":158,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":132,\"y\":161,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":125,\"y\":164,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":124,\"y\":164,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":121,\"y\":165,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":118,\"y\":165,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":114,\"y\":165,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":113,\"y\":165,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":110,\"y\":165,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":107,\"y\":165,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":104,\"y\":165,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":99,\"y\":163,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":97,\"y\":162,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":95,\"y\":161,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":92,\"y\":158,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":90,\"y\":156,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":88,\"y\":155,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":87,\"y\":152,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":86,\"y\":150,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":84,\"y\":148,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":82,\"y\":142,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":82,\"y\":140,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":82,\"y\":139,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":82,\"y\":138,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":82,\"y\":137,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":83,\"y\":136,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":84,\"y\":134,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":86,\"y\":133,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":88,\"y\":133,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":94,\"y\":132,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":97,\"y\":132,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":102,\"y\":132,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":106,\"y\":132,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":109,\"y\":132,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":116,\"y\":134,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":121,\"y\":135,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":126,\"y\":136,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":133,\"y\":138,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":136,\"y\":139,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":146,\"y\":141,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":150,\"y\":141,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":154,\"y\":142,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":162,\"y\":143,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":167,\"y\":143,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":173,\"y\":144,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":177,\"y\":144,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":183,\"y\":144,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":186,\"y\":144,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":194,\"y\":142,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":195,\"y\":142,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":198,\"y\":140,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":199,\"y\":139,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":200,\"y\":138,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":201,\"y\":136,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":202,\"y\":135,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":202,\"y\":134,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":202,\"y\":132,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":202,\"y\":129,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":201,\"y\":127,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":199,\"y\":125,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":198,\"y\":124,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":196,\"y\":121,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":193,\"y\":118,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":191,\"y\":116,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":188,\"y\":114,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":187,\"y\":112,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":179,\"y\":107,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":177,\"y\":105,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":172,\"y\":104,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":169,\"y\":102,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":165,\"y\":101,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":162,\"y\":100,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":158,\"y\":99,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":154,\"y\":98,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":151,\"y\":98,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":144,\"y\":98,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":141,\"y\":98,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":137,\"y\":98,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":134,\"y\":100,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":131,\"y\":101,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":129,\"y\":102,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":125,\"y\":105,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":123,\"y\":107,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":120,\"y\":111,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":115,\"y\":118,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":113,\"y\":120,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":112,\"y\":123,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":110,\"y\":128,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":108,\"y\":133,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":106,\"y\":137,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":105,\"y\":143,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":104,\"y\":146,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":102,\"y\":151,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":100,\"y\":159,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":100,\"y\":160,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":99,\"y\":161,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":98,\"y\":164,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":97,\"y\":167,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":96,\"y\":168,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":96,\"y\":170,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":94,\"y\":171,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":94,\"y\":172,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":92,\"y\":176,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":91,\"y\":177,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":90,\"y\":177,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":89,\"y\":178,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":89,\"y\":179,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":88,\"y\":180,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":87,\"y\":181,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":86,\"y\":181,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":85,\"y\":182,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":83,\"y\":183,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":82,\"y\":183,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":81,\"y\":184,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":80,\"y\":184,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":79,\"y\":185,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":78,\"y\":185,\"color\":\"#ffffff\",\"strokeId\":1}]}";


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
    LCD_1IN28_Clear(WHITE);

    // Create a new image cache named IMAGE_RGB and fill it with white
    Paint_NewImage((UBYTE *)BlackImage, LCD_1IN28.WIDTH, LCD_1IN28.HEIGHT, 0, WHITE);
    Paint_SetScale(65);
    Paint_SetRotate(ROTATE_0);
    Paint_Clear(WHITE);

    // Initial display with a message
    Paint_Clear(WHITE);
    Paint_DrawRectangle(0, 00, 240, 47, 0x2595, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawString_EN(60, 30, "Touch test", &Font16, WHITE, BLACK);
    LCD_1IN28_Display(BlackImage);
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
    DeserializationError error = deserializeJson(doc, jsonData);

    if (error) {
        Serial.print("Failed to parse JSON: ");
        Serial.println(error.c_str());
        return;
    }

    bool interpolate = doc["interpolate"];
    JsonArray points = doc["points"];

    int prevX = -1;
    int prevY = -1;
    const char* prevColorStr = "";

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

    // Refresh the display
    LCD_1IN28_Display(BlackImage);
}

void loop() {
jsonData = "{\"interpolate\":true,\"points\":[{\"x\":67,\"y\":131,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":67,\"y\":130,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":67,\"y\":129,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":67,\"y\":127,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":67,\"y\":122,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":67,\"y\":120,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":68,\"y\":118,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":69,\"y\":115,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":70,\"y\":112,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":72,\"y\":109,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":74,\"y\":105,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":76,\"y\":101,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":78,\"y\":98,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":84,\"y\":90,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":87,\"y\":88,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":91,\"y\":83,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":94,\"y\":80,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":98,\"y\":77,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":102,\"y\":75,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":105,\"y\":72,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":109,\"y\":70,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":113,\"y\":69,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":120,\"y\":68,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":121,\"y\":68,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":124,\"y\":67,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":127,\"y\":67,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":129,\"y\":67,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":132,\"y\":67,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":134,\"y\":68,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":136,\"y\":69,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":137,\"y\":72,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":141,\"y\":78,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":142,\"y\":79,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":143,\"y\":84,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":145,\"y\":89,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":145,\"y\":94,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":147,\"y\":100,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":147,\"y\":108,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":147,\"y\":114,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":147,\"y\":119,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":147,\"y\":134,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":146,\"y\":136,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":145,\"y\":142,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":143,\"y\":146,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":141,\"y\":150,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":140,\"y\":153,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":137,\"y\":156,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":135,\"y\":158,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":132,\"y\":161,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":125,\"y\":164,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":124,\"y\":164,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":121,\"y\":165,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":118,\"y\":165,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":114,\"y\":165,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":113,\"y\":165,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":110,\"y\":165,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":107,\"y\":165,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":104,\"y\":165,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":99,\"y\":163,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":97,\"y\":162,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":95,\"y\":161,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":92,\"y\":158,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":90,\"y\":156,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":88,\"y\":155,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":87,\"y\":152,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":86,\"y\":150,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":84,\"y\":148,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":82,\"y\":142,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":82,\"y\":140,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":82,\"y\":139,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":82,\"y\":138,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":82,\"y\":137,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":83,\"y\":136,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":84,\"y\":134,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":86,\"y\":133,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":88,\"y\":133,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":94,\"y\":132,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":97,\"y\":132,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":102,\"y\":132,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":106,\"y\":132,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":109,\"y\":132,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":116,\"y\":134,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":121,\"y\":135,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":126,\"y\":136,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":133,\"y\":138,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":136,\"y\":139,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":146,\"y\":141,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":150,\"y\":141,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":154,\"y\":142,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":162,\"y\":143,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":167,\"y\":143,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":173,\"y\":144,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":177,\"y\":144,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":183,\"y\":144,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":186,\"y\":144,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":194,\"y\":142,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":195,\"y\":142,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":198,\"y\":140,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":199,\"y\":139,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":200,\"y\":138,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":201,\"y\":136,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":202,\"y\":135,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":202,\"y\":134,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":202,\"y\":132,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":202,\"y\":129,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":201,\"y\":127,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":199,\"y\":125,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":198,\"y\":124,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":196,\"y\":121,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":193,\"y\":118,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":191,\"y\":116,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":188,\"y\":114,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":187,\"y\":112,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":179,\"y\":107,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":177,\"y\":105,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":172,\"y\":104,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":169,\"y\":102,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":165,\"y\":101,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":162,\"y\":100,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":158,\"y\":99,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":154,\"y\":98,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":151,\"y\":98,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":144,\"y\":98,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":141,\"y\":98,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":137,\"y\":98,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":134,\"y\":100,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":131,\"y\":101,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":129,\"y\":102,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":125,\"y\":105,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":123,\"y\":107,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":120,\"y\":111,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":115,\"y\":118,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":113,\"y\":120,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":112,\"y\":123,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":110,\"y\":128,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":108,\"y\":133,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":106,\"y\":137,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":105,\"y\":143,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":104,\"y\":146,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":102,\"y\":151,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":100,\"y\":159,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":100,\"y\":160,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":99,\"y\":161,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":98,\"y\":164,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":97,\"y\":167,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":96,\"y\":168,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":96,\"y\":170,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":94,\"y\":171,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":94,\"y\":172,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":92,\"y\":176,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":91,\"y\":177,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":90,\"y\":177,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":89,\"y\":178,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":89,\"y\":179,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":88,\"y\":180,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":87,\"y\":181,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":86,\"y\":181,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":85,\"y\":182,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":83,\"y\":183,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":82,\"y\":183,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":81,\"y\":184,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":80,\"y\":184,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":79,\"y\":185,\"color\":\"#ffffff\",\"strokeId\":1},{\"x\":78,\"y\":185,\"color\":\"#ffffff\",\"strokeId\":1}]}";

    displayJsonData();
    delay(1000);
}
