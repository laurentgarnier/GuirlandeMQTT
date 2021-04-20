# GuirlandeMQTT

## Descrition
Gestion d'une guirlande de led WS2811 avec différents effets pré programmés
Le pilotage des changements d'effets se fait par une page web.
La guirlande utilise MQTT pour publier à intervalles réguliers l'effet courant et pour recevoir l'effet à appliquer.
Le pilotage se fait par une page web qui effectue une requête get sur un serveur Nodered qui va publier en MQTT sur la file écoutée par la guirlande.

3 topics MQTT :
* Maison/Discovery/Guirlandes/GuirlandeSalon sur lequel la guirlande publie toutes les 10s son adresse MAC et IP
* Maison/Guirlandes/GuirlandeSalon/FromObject/EffetCourant sur lequel la guirlande publie l'effet courant lors de chaque changement
    Formalisme : {"effetCourant": [N°], "nomEffet": "[Nom enregistré]"}
* Maison/Guirlandes/GuirlandeSalon/ToObject/EffetDemande, topic d'écoute pour demander le changement d'effet
    Formalisme : {"effect":[N°]} avec N° allant de 1 à 12
