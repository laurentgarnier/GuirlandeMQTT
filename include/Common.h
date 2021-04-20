#include <Arduino.h>

const int nombreEffet = 12;
String listeDesEffets[nombreEffet];
int selectedEffect = 0;
int lastEffect = 0;

void remplirEffets()
{
    // Association du numéro et du libellé de l'effet
    listeDesEffets[0] = "Arc en ciel par zone";
    listeDesEffets[1] = "Arc en ciel";
    listeDesEffets[2] = "Arc en ciel par pas";
    listeDesEffets[3] = "Meteorite";
    listeDesEffets[4] = "Multicolor clignotant";
    listeDesEffets[5] = "Scintillement";
    listeDesEffets[6] = "Scintillement OL";
    listeDesEffets[7] = "OL";
    listeDesEffets[8] = "Poursuite OL";
    listeDesEffets[9] = "kitt OL";
    listeDesEffets[10] = "Poursuite rouge bleu";
    listeDesEffets[11] = "Fondu OL";
}


String macToStr(const uint8_t *mac)
{
    String result;
    for (int i = 0; i < 6; ++i)
    {
        result += String(mac[i], 16);
        if (i < 5)
            result += ':';
    }
    return result;
}

void publierEffetCourant(int effet, String categorie, String nom, PubSubClient *clientMqtt)
{
  publierMessage("Maison/" + categorie + "/" + nom + "/FromObject/EffetCourant", "{\"effetCourant\":" + String(effet) + ", \"nomEffet\":\""  + listeDesEffets[effet] + "\" }", clientMqtt);
}

void publierListeDesEffets(String categorie, String nom, PubSubClient *clientMqtt)
{
  Serial.println("Effets disponibles");
  String message = "{\"effet\":[";
  for(int indexEffet = 0; indexEffet < nombreEffet/2; indexEffet++)
  {
    if(indexEffet > 0)
      message = message + "," ;

    message = message + "{\"nomEffet\":\"" + listeDesEffets[indexEffet] + "\", \"code\":" + String(indexEffet) + "}";
  }
  message = message + "]}";

  //message = "j'essaie de comprendre";
  Serial.println(message);
  publierMessage("Maison/" + categorie + "/" + nom + "/FromObject/EffetsDisponibles", message, clientMqtt);
}

void gererReceptionMessage(char *topic, byte *payload, unsigned int len)
{
  Serial.println("");
  Serial.print("Message recu sur le topic=");
  Serial.println(topic);

  char msg[len];
  for(unsigned int i = 0; i < len; i++)
    msg[i] = payload[i];

  String data = String(msg);
  Serial.println("Payload : " + data);
  Serial.println("");

  int positionDeuxPoints = data.indexOf(":");
  int positionAccoladeFermante = data.indexOf("}");

  selectedEffect = data.substring(positionDeuxPoints+1, positionAccoladeFermante).toInt();

  if (selectedEffect > nombreEffet - 1)
      selectedEffect = 0;

  Serial.println("Effet : " + String(selectedEffect));
}