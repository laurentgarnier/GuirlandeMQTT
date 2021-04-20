
#include "MQTTManagement.h"
#include "WifiManagement.h"
#include "common.h"
#include "Effets.h"
#include "Configuration.h"

WiFiClient clientWifi;
IPAddress adresseIP;
String adresseMAC;

int timingDernierEnvoiDesDonnees;
const int periodeEnvoiMessageDeVieEnMs = 10000; // Toutes les 10s

PubSubClient *clientMqtt;

void setup()
{
  Serial.begin(115200);
  delay(10);

  adresseIP = connectToWifi(ssidWifi, passwordWifi);
  // Récupération de l'adresse MAC du device
  uint8_t mac[6];
  WiFi.macAddress(mac);
  adresseMAC = macToStr(mac);

  creerRuban();
  remplirEffets();

  clientMqtt = new PubSubClient(serveurMqtt, 1883, gererReceptionMessage, clientWifi);

  connecterAuServeurMQTT(nomDevice, categorieDevice, adresseMAC, clientMqtt);
  envoyerMessageDeVie(nomDevice, adresseMAC, adresseIP, clientMqtt, categorieDevice);
  publierEffetCourant(selectedEffect, categorieDevice, nomDevice, clientMqtt);
  publierListeDesEffets(categorieDevice, nomDevice, clientMqtt);

  clignoterRVB();
  timingDernierEnvoiDesDonnees = millis();
}

void loop()
{
  int timingCourant = millis();

  if ((timingCourant - timingDernierEnvoiDesDonnees) > periodeEnvoiMessageDeVieEnMs)
  {
    envoyerMessageDeVie(nomDevice, adresseMAC, adresseIP, clientMqtt, categorieDevice);
    timingDernierEnvoiDesDonnees = timingCourant;
  }
  clientMqtt->loop();

  if (selectedEffect != lastEffect)
  {
    publierEffetCourant(selectedEffect, categorieDevice, nomDevice, clientMqtt);
    lastEffect = selectedEffect;
    setAll(0, 0, 0);
  }

  switch (selectedEffect)
  {
  case 0:
  {
    ArcEnCielParZone();
    break;
  }
  case 1:
  {
    ArcEnCiel(10);
    break;
  }
  case 2:
  {
    ArcEnCielQuiMonte();
    break;
  }
  case 3:
  {
    Meteorite(0xff, 0xff, 0xff, 5, 25, true, 15);
    break;
  }
  case 4:
  {
    MultiCouleursClignotant(250);
    break;
  }
  case 5:
  {
    Scintillement(0xff, 0xff, 0xff, 125);
    break;
  }
  case 6:
  {
    ScintillementRougeBleu();
    break;
  }
  case 7:
  {
    theaterChase();
    break;
  }
  case 8:
  {
    Poursuite();
    break;
  }
  case 9:
  {
    NewKITT();
    break;
  }
  case 10:
  {
    PoursuiteRougeBleu();
    break;
  }
  case 11:
  {
    effetFonduRougeBleu();
    break;
  }
  default:
  {
    ArcEnCielParZone();
    break;
  }
  }
  nombreBoucle++;
}