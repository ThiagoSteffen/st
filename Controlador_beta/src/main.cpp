
#include <LovyanGFX.hpp>
#include <WiFi.h>
#include <SPIFFS.h>
#include <time.h>

// Define display object
LGFX display;

// WiFi settings
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// NTP server settings
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;  // Adjust depending on timezone
const int   daylightOffset_sec = 3600;  // Adjust for daylight saving time if needed

// Function to initialize the display
void setupDisplay() {
    display.init();  // Initialize the display
    display.setRotation(1);  // Set display rotation (landscape mode)
    display.fillScreen(TFT_BLACK);  // Clear screen with black
    display.setTextSize(2);  // Set text size
    display.setTextColor(TFT_WHITE, TFT_BLACK);  // Set text color
    display.drawString("Initializing...", 10, 10);  // Display initial text
}

// Function to connect to WiFi
void setupWiFi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        display.fillScreen(TFT_BLACK);
        display.drawString("Connecting to WiFi...", 10, 30);
    }
    display.fillScreen(TFT_BLACK);
    display.drawString("WiFi connected", 10, 30);
}

// Function to initialize NTP and set system time
void setupNTP() {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    display.drawString("Time synchronized", 10, 50);
}

// Function to get current time
String getCurrentTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return "Failed to obtain time";
    }
    char timeStr[64];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return String(timeStr);
}

// Setup function to initialize the system
void setup() {
    // Initialize SPIFFS for storing and reading images
    if (!SPIFFS.begin(true)) {
        display.fillScreen(TFT_RED);
        display.drawString("SPIFFS Mount Failed!", 10, 50);
        return;
    }

    setupDisplay();  // Initialize display
    setupWiFi();  // Connect to WiFi
    setupNTP();  // Synchronize time via NTP

    // Display background image and button images
    display.drawBmpFile(SPIFFS, "/imagem/background.bmp", 0, 0);  // Display background
}

// Main loop to update time on display
void loop() {
    display.fillRect(10, 70, 200, 30, TFT_BLACK);  // Clear previous time
    display.drawString(getCurrentTime(), 10, 70);  // Display current time
    delay(1000);  // Update every second
}
