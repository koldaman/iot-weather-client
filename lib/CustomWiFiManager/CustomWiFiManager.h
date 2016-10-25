/**************************************************************
Zabaleni funkcionality pro WiFiManager (zapamatovani
posledniho nastaveni pripojeni k WiFi vcetne prenastaveni)
**************************************************************/

#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <Blink.h>
#include <Ticker.h>

class CustomWiFiManager {
public:
   static void start(Blink* blinker);
private:
   // tuto dobu cekej na zadani nove konfigurace WiFi
   static float WAIT_FOR_CONNECTION_TIMEOUT() { return 60*3; }; // 3 minuty

   static WiFiManager _wifiManager;
   static Blink* _blinker;
   static Ticker* _ticker;
   static void configModeCallback(WiFiManager *myWiFiManager);
   static void waitForConnectTimeout();
};
