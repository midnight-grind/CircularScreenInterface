#include <Arduino.h>
#include <SD.h>
#include <SPI.h>  // Include the SPI library

// Define custom GPIO pins for SPI
#define SD_CS_PIN 15    // Chip Select (CS) pin
#define SPI_MOSI 16     // MOSI pin
#define SPI_MISO 18     // MISO pin
#define SPI_CLK  17     // Clock (CLK) pin

void listDir(File dir, int numTabs) {
    while (true) {
        File entry = dir.openNextFile();
        if (!entry) {
            // No more files
            break;
        }
        for (int i = 0; i < numTabs; i++) {
            Serial.print('\t'); // Add tabs for formatting
        }
        if (entry.isDirectory()) {
            Serial.print("DIR: ");
            Serial.println(entry.name());
            listDir(entry, numTabs + 1); // Recursively list the contents of this directory
        } else {
            Serial.print("FILE: ");
            Serial.print(entry.name());
            Serial.print("\tSIZE: ");
            Serial.println(entry.size());
        }
        entry.close();
    }
}

void setup() {
    Serial.begin(115200);

    // Initialize SPI with custom GPIO pins
    SPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI, SD_CS_PIN);

    // Initialize SD card
    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("SD card initialization failed!");
        return;
    }
    Serial.println("SD card initialized.");

    // Open the root directory and list all files
    File root = SD.open("/");
    if (root) {
        Serial.println("Listing files and directories:");
        listDir(root, 0);
    } else {
        Serial.println("Failed to open root directory.");
    }
}

void loop() {
    // Empty loop function
}
