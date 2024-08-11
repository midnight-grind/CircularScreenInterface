#include <Arduino.h>
#include <ArduinoJson.h>
#include "LCD_Test.h"

UWORD Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
UWORD *BlackImage;
CST816S touch(6, 7, 13, 5); // sda, scl, rst, irq

int lastX = -1;
int lastY = -1;

const char* jsonData = R"([
  {
    "x": 109,
    "y": 99,
    "color": "#ffffff",
    "strokeId": 2
  },
  {
    "x": 110,
    "y": 99,
    "color": "#ffffff",
    "strokeId": 2
  },
  {
    "x": 111,
    "y": 99,
    "color": "#ffffff",
    "strokeId": 2
  }
])";

void setup()
{
    Serial.begin(115200);
    touch.begin();
    // PSRAM Initialize
    if (psramInit())
    {
        Serial.println("\nPSRAM is correctly initialized");
    }
    else
    {
        Serial.println("PSRAM not available");
    }
    if ((BlackImage = (UWORD *)ps_malloc(Imagesize)) == NULL)
    {
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

void drawOnScreen()
{
    // Continuous touch interaction
    if (touch.available())
    {
        int x = touch.data.x;
        int y = touch.data.y;
        
        // Draw a line from the last point to the current point
        if (lastX != -1 && lastY != -1)
        {
            Paint_DrawLine(lastX, lastY, x, y, BLACK, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
        }

        // Update the last point
        lastX = x;
        lastY = y;

        // Display the updated image
        LCD_1IN28_DisplayWindows(lastX, lastY, x + 3, y + 3, BlackImage);
    }
    else
    {
        // Reset lastX and lastY when the touch is not available
        lastX = -1;
        lastY = -1;
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

void displayJsonData() {
    StaticJsonDocument<2000> doc;
    DeserializationError error = deserializeJson(doc, jsonData);

    if (error) {
        Serial.print("Failed to parse JSON: ");
        Serial.println(error.c_str());
        return;
    }

    for (JsonObject point : doc.as<JsonArray>()) {
        int x = point["x"];
        int y = point["y"];
        const char* colorStr = point["color"];

        // Convert the color string to an RGB565 format
        uint16_t color = parseHexColor(colorStr);

        // Draw the point with the extracted color
        Paint_DrawPoint(x, y, color, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    }

    // Refresh the display
    LCD_1IN28_Display(BlackImage);
}


void loop()
{
    // drawOnScreen(); // Uncomment to use the touch drawing functionality
    displayJsonData(); // Comment out if you only want to use touch drawing
    delay(1000); // Adjusted delay to better visualize JSON data on screen
}
