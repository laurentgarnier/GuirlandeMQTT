#include "LedStripConfig.h"

const int DureeDeChaqueEffetEnSecondes = 30; // 1mn
int timingDernierEffet;

byte brillance = 255;
byte saturation = 255;
byte pas = 10;
byte teinte = 0;
int indexLed = 0;
unsigned long dernierTemps = 0;
bool fonduRougeVersBlanc = true;
bool OLfonduRougeVersBleu = true;

int nombreBoucle = 0;

void effetFonduRougeBleu()
{
    for (int indexBoucle = 0; indexBoucle < 2; indexBoucle++)
    {
        // Fade IN
        for (int indexCouleur = 0; indexCouleur < 256; indexCouleur++)
        {
            switch (indexBoucle)
            {
            case 0:
                setAll(indexCouleur, 0, 0);
                break;
            case 1:
                setAll(0, 0, indexCouleur);
                break;
            }
            FastLED.show();
            delay(3);
        }
        // Fade OUT
        for (int indexCouleur = 255; indexCouleur >= 0; indexCouleur--)
        {
            switch (indexBoucle)
            {
            case 0:
                setAll(indexCouleur, 0, 0);
                break;
            case 1:
                setAll(0, 0, indexCouleur);
                break;
            }
            FastLED.show();
            delay(3);
        }
    }
}



void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i =((NUM_LEDS-EyeSize)/2); i>=0; i--) {
    setAll(0,0,0);
   
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
   
    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS-i-j, red, green, blue);
    }
    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
   
    FastLED.show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = 0; i<=((NUM_LEDS-EyeSize)/2); i++) {
    setAll(0,0,0);
   
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
   
    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS-i-j, red, green, blue);
    }
    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
   
    FastLED.show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    FastLED.show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    FastLED.show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void NewKITT(){
 int EyeSize = 8;
 int SpeedDelay = 100;
 int ReturnDelay = 50;

  RightToLeft(255, 0, 0, EyeSize, SpeedDelay, ReturnDelay);
  LeftToRight(0, 0, 255, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(255, 0, 0, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(0, 0, 255, EyeSize, SpeedDelay, ReturnDelay);
  LeftToRight(0, 0, 255, EyeSize, SpeedDelay, ReturnDelay);
  RightToLeft(255, 0, 0, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(0, 0, 0, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(255, 0, 0, EyeSize, SpeedDelay, ReturnDelay);
}

void DecalageADroite(byte red, byte green, byte blue) {
  int EyeSize = 8;
  int SpeedDelay = 100;
  int ReturnDelay = 250;

  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) 
  {
    setAll(0, 0, 0);
    setPixel(i, red / (EyeSize * i+1), green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++)
    {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
    FastLED.show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void RunningLights(byte red, byte green, byte blue)
{
  int Position = 0;
  int WaveDelay = 250;

  Position++;
  for (int i = 0; i < NUM_LEDS; i++)
  {
    setPixel(i, ((sin(i + Position) * 127 + 128) / 255) * red,
             ((sin(i + Position) * 127 + 128) / 255) * green,
             ((sin(i + Position) * 127 + 128) / 255) * blue);
  }

  FastLED.show();
  delay(WaveDelay);
}

void PoursuiteRougeBleu()
{
    RunningLights(255,0,0);
    RunningLights(0,0,255);
}

void colorWipe(byte red, byte green, byte blue) {
  int SpeedDelay = 50;
  for(uint16_t i=0; i<NUM_LEDS; i++) {
      setPixel(i, red, green, blue);
      FastLED.show();
      delay(SpeedDelay);
  }
}

void Poursuite()
{
  colorWipe(255,0,0);
  colorWipe(0,0,255);
}

void theaterChase() {
  int SpeedDelay = 250;
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NUM_LEDS; i=i+3) {
        setPixel(i+q, 255, 0, 0);    //turn every third pixel on
      }
     FastLED.show();
     
      delay(SpeedDelay);
     
      for (int i=0; i < NUM_LEDS; i=i+3) {
        setPixel(i+q, 0,0,255);        //turn every third pixel off
      }
    }
  }
}

void clignoterRVB()
{
  setAll(255, 0, 0);
  delay(1000);
  setAll(0, 255, 0);
  delay(1000);
  setAll(0, 0, 255);
  delay(1000);
  setAll(0, 0, 0);
}

void Meteorite(byte rouge, byte vert, byte bleu, byte tailleMeteorite, byte tailleTrainee, boolean traineeAleatoire, int vitesse)
{
    setAll(0, 0, 0);

    for (int i = 0; i < NUM_LEDS + NUM_LEDS; i++)
    {
        // Atténuation de la luminosité de toutes les leds en 1 étape
        for (int j = 0; j < NUM_LEDS; j++)
        {
            if ((!traineeAleatoire) || (random(10) > 5))
            {
                AttenuationVersNoir(j, tailleTrainee);
            }
        }

        // dessin de la météorite
        for (int j = 0; j < tailleMeteorite; j++)
        {
            if ((i - j < NUM_LEDS) && (i - j >= 0))
            {
                setPixel(i - j, rouge, vert, bleu);
            }
        }

        FastLED.show();
        delay(vitesse);
    }
}

void Transition()
{
    Meteorite(0xff, 0xff, 0xff, 5, 25, true, 5);
    timingDernierEffet = millis();
}

void Flash(int indexPixel)
{
    setPixel(indexPixel, 0xff, 0xff, 0xff);
    FastLED.show();
    delay(50);
}

void Scintillement(byte rouge, byte vert, byte bleu, int vitesse)
{
    int pixel = random(NUM_LEDS);
    Flash(pixel);
    setPixel(pixel, 0, 0, 0);
}

void Noel()
{
    setAll(32, 0, 0);

    for (int i = 0; i < 3; i++)
    {
        int pixel = random(NUM_LEDS);

        // Flash
        Flash(pixel);
        // Remet le pixel à sa couleur d'origine
        setPixel(pixel, 32, 0, 0);
    }
}

void MultiCouleursClignotant(int vitesse)
{
    if(indexLed > NUM_LEDS)
        indexLed = 0;

    for (int pixel = 0; pixel < NUM_LEDS; pixel++)
    {
        setPixel(pixel, random(255), random(255), random(255));
    }
    setPixel(indexLed, 0, 0, 0);
    FastLED.show();
    delay(vitesse);
    indexLed++;
}

void fill_rainbow_ctrl(struct CRGB *pFirstLED, int numToFill,
                       uint8_t teinteInitiale,
                       uint8_t deltaTeinte,
                       uint8_t saturation,
                       uint8_t brillanceSouhaitee)
{
    CHSV hsv;
    hsv.hue = teinteInitiale;
    hsv.sat = saturation;
    hsv.val = brillanceSouhaitee;
    for (int i = 0; i < numToFill; i++)
    {
        hsv2rgb_rainbow(hsv, pFirstLED[i]);
        hsv.hue += deltaTeinte;
    }
}

void ArcEnCielParZone()
{
    fill_rainbow_ctrl(leds, NUM_LEDS, teinte, pas, saturation, brillance);
    teinte++;
    FastLED.show();
    delay(5);
}

byte *RoueDeCouleur(byte positionSurLaRoue)
{
    static byte c[3];

    if (positionSurLaRoue < 85)
    {
        c[0] = positionSurLaRoue * 3;
        c[1] = 255 - positionSurLaRoue * 3;
        c[2] = 0;
    }
    else if (positionSurLaRoue < 170)
    {
        positionSurLaRoue -= 85;
        c[0] = 255 - positionSurLaRoue * 3;
        c[1] = 0;
        c[2] = positionSurLaRoue * 3;
    }
    else
    {
        positionSurLaRoue -= 170;
        c[0] = 0;
        c[1] = positionSurLaRoue * 3;
        c[2] = 255 - positionSurLaRoue * 3;
    }

    return c;
}

void ArcEnCiel(int vitesse)
{
    byte *c;
    uint16_t i, j;

    for (j = 0; j < 256; j++)
    { // 5 cycles of all colors on wheel
        for (i = 0; i < NUM_LEDS; i++)
        {
            c = RoueDeCouleur(((i * 256 / NUM_LEDS) + j) & 255);
            setPixel(i, *c, *(c + 1), *(c + 2));
        }
        FastLED.show();
        delay(vitesse);
    }
}

void FonduRougeVersBlanc()
{
    for (int colorStep = 0; colorStep < 33; colorStep++)
    {

        int r = 32;
        int b = colorStep;
        int g = colorStep;

        for (int x = 0; x < NUM_LEDS; x++)
        {
            leds[x] = CRGB(r, g, b);
        }

        FastLED.show();
        delay(50);
    }
}

void FonduRougeVersBleu()
{
    for (int colorStep = 0; colorStep < 255; colorStep = colorStep + 51)
    {
        int r = 255 - colorStep;
        int b = colorStep;
        int g = 0;

        for (int x = 0; x < NUM_LEDS; x++)
        {
            leds[x] = CRGB(r, g, b);
        }

        FastLED.show();
        delay(25);
    }
}

void FonduBleuVersRouge()
{
    for (int colorStep = 0; colorStep < 255; colorStep = colorStep + 51)
    {

        int r = colorStep;
        int b = 255 - colorStep;
        int g = 0;

        for (int x = 0; x < NUM_LEDS; x++)
        {
            leds[x] = CRGB(r, g, b);
        }

        FastLED.show();
        delay(25);
    }
}

void Flasher(int dureeDuFlash){
  int pixel = random(NUM_LEDS);

  int ancienneValeurRouge = leds[pixel].red;
  int ancienneValeurVert = leds[pixel].green;
  int ancienneValeurBleu = leds[pixel].blue;
  
  Flash(pixel);

   // On repositionne le pixel à son ancienne valeur
  setPixel(pixel,ancienneValeurRouge, ancienneValeurVert, ancienneValeurBleu);
  FastLED.show();
}

void FonduBlancVersRouge()
{
    for (int colorStep = 0; colorStep < 33; colorStep++)
    {

        int r = 32;
        int b = 32 - colorStep;
        int g = 32 - colorStep;

        for (int x = 0; x < NUM_LEDS; x++)
        {
            leds[x] = CRGB(r, g, b);
        }

        FastLED.show();
        delay(50);
    }
}

int dernierChangement = 0;
bool estCouleurDeFondBleue = true;

void ScintillementRougeBleu()
{
  int R, B;

  int timingCourant = millis();

  // toutes les 30s
  if(timingCourant - dernierChangement > 30000)
  {
    estCouleurDeFondBleue = !estCouleurDeFondBleue;  
    dernierChangement = timingCourant;
    if(estCouleurDeFondBleue)
      FonduRougeVersBleu();
    else
      FonduBleuVersRouge();
  }

  if(estCouleurDeFondBleue)
  {
    R = 0;
    B = 255;
  }
  else
  {
    R = 255;
    B = 0;
  }

  setAll(R, 0, B);

  int Pixel = random(NUM_LEDS);
  int Pixel2 = random(NUM_LEDS);
  int Pixel3 = random(NUM_LEDS);
  int Pixel4 = random(NUM_LEDS);

  setPixel(Pixel, B, 0, R);
  setPixel(Pixel2, B, 0, R);
  setPixel(Pixel3, B, 0, R);
  setPixel(Pixel4, B, 0, R);
  FastLED.show();
  delay(250);

  setPixel(Pixel, R, 0, B);

  Pixel = random(NUM_LEDS);
  Pixel2 = random(NUM_LEDS);
  Pixel3 = random(NUM_LEDS);
  Pixel4 = random(NUM_LEDS);
  setPixel(Pixel, B, 0, R);
  setPixel(Pixel2, B, 0, R);
  setPixel(Pixel3, B, 0, R);
  setPixel(Pixel4, B, 0, R);
  FastLED.show();
  delay(250);
}

void NoelAvecFondu()
{
    int couleurClignotement;
    int couleurDuFond;
    int couleurRougeClignotant;

    if (fonduRougeVersBlanc)
    {
        couleurClignotement = 128;
        couleurDuFond = 0;
        couleurRougeClignotant = 128;
    }
    else
    {
        couleurClignotement = 0;
        couleurDuFond = 32;
        couleurRougeClignotant = 255;
    }

    // on débute avec tout à rouge
    setAll(32, couleurDuFond, couleurDuFond);

    // 3 clignotements par cycle (blanc quand fond rouge et rouge quand fond blanc)

    for (int i = 0; i < 5; i++)
    {
        int pixel = random(NUM_LEDS);
        setPixel(pixel, couleurRougeClignotant, couleurClignotement, couleurClignotement);
        FastLED.show();
        delay(75);
        setPixel(pixel, 32, couleurDuFond, couleurDuFond);
    }

    if (millis() - dernierTemps > ((DureeDeChaqueEffetEnSecondes / 2) * 1000))
    {
        if (fonduRougeVersBlanc)
        {
            FonduRougeVersBlanc();
            fonduRougeVersBlanc = false;
        }
        else
        {
            FonduBlancVersRouge();
            fonduRougeVersBlanc = true;
        }
        dernierTemps = millis();
    }
}

void DegradeScintillant(){
      for(int bleu = 0; bleu < 255; bleu ++){
        setAll(255-bleu, 0, bleu);      

       if(bleu%3 == 0)
        Flasher(100);       
      }
       for(int rouge = 0; rouge < 255; rouge ++){
        setAll(0, rouge, 255-rouge);      

        if(rouge%3 == 0)
        Flasher(100);       
      }
       for(int vert = 0; vert < 255; vert ++){
        setAll(vert, 255-vert, 0);      

         if(vert%3 == 0)
        Flasher(100); 
      }
}



void EclatementAleatoire() 
{
  int rndidx = random16(0, NUM_LEDS);
  int rndhue = random8(0, 255);  
  int rndbright = random8(10, brillance);
  leds[rndidx] = CHSV(rndhue, saturation, rndbright);
  FastLED.show();
  delay(random8(0, 20));
}

void OL()
{
    int valeurRouge;
    int valeurBleu;

    if (OLfonduRougeVersBleu)
    {
        valeurRouge = 255;
        valeurBleu = 0;
    }
    else
    {
        valeurRouge = 0;
        valeurBleu = 255;
    }

    setAll(valeurRouge, 0, valeurBleu);

    // 3 clignotements par cycle (bleu quand fond rouge et rouge quand fond bleu)
    for (int i = 0; i < 5; i++)
    {
        int pixel = random(NUM_LEDS);
        setPixel(pixel, valeurBleu, 0, valeurRouge);
        FastLED.show();
        delay(75);
        setPixel(pixel, valeurRouge, 0, valeurBleu);
    }

    if (millis() - dernierTemps > ((DureeDeChaqueEffetEnSecondes / 2) * 1000))
    {
        if (OLfonduRougeVersBleu)
        {
            FonduRougeVersBleu();
            OLfonduRougeVersBleu = false;
        }
        else
        {
            FonduBleuVersRouge();
            OLfonduRougeVersBleu = true;
        }
        dernierTemps = millis();
    }
}

int boucle = 0;
void OLOld(){
    if(boucle > NUM_LEDS)
      boucle = 0;

    boucle++;

    // Tous les NUM_LEDS boucle affichage d'une météorite blanche sur toute la longueur
    if(boucle == (NUM_LEDS/2)){
      int ancienneValeurRouge;
      int ancienneValeurBleu;

      for (int i = 0; i <= NUM_LEDS; i++)
      {
        if(i > 0)
          setPixel(i-1, ancienneValeurRouge, 0, ancienneValeurBleu);
        
        if(i != NUM_LEDS) {

        ancienneValeurRouge = leds[i].red;
        ancienneValeurBleu = leds[i].blue;

        setPixel(i, 255,255,255);
        }
        FastLED.show();
      }
      return;
      
    }

    int pixel = random(0, NUM_LEDS);
    int ancienneValeur;
    int nouvelleValeur = random(5, 255);

    Serial.println("valeur : " + nouvelleValeur);

    // Le pixel était rouge, il devient bleu
    // fondu de sa couleur à éteint puis de éteint à la couleur cible
    if(leds[pixel].red > 0){
      
      ancienneValeur = leds[pixel].red;
      // fondu extinction
      for(int i=0; i < ancienneValeur; i+=2){
        setPixel(pixel, ancienneValeur-i, 0 , 0);
        FastLED.show();
      }
      // fondu vers sa nouvelle couleur
      for(int i=0; i < nouvelleValeur; i+=2){
        setPixel(pixel, 0, 0 , i);
        FastLED.show();
      }
      return;
    }

    // Le pixel était bleu, il devient rouge
    // fondu de sa couleur à éteint puis de éteint à la couleur cible
    if(leds[pixel].blue > 0){

      ancienneValeur = leds[pixel].blue;
      // fondu extinction
      for(int i=0; i < ancienneValeur; i+=2){
        setPixel(pixel, 0 , 0, ancienneValeur-i);
        FastLED.show();
      }
       // fondu vers sa nouvelle couleur
      for(int i=0; i < nouvelleValeur; i+=2){
        setPixel(pixel, i, 0 , 0);
        FastLED.show();
      }
      return;
    }

    // première fois, fondu pour atteindre la couleur cible
    // les coups paires on met la couleur rouge et impair en bleu
    if(leds[pixel].red == 0 && leds[pixel].blue == 0){
      
        for(int i=0; i < nouvelleValeur; i++){
          if(boucle % 2 != 0)
            setPixel(pixel, 0 , 0, i);
          else
            setPixel(pixel, i, 0 , 0);
          FastLED.show();
        }
    }
}
/************************* TEST ******************/


void addGlitter( fract8 chanceOfGlitter)
{
  if ( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}
 uint8_t gHue = 0;
 DEFINE_GRADIENT_PALETTE(bhw3_41_gp){
     255, 255, 0, 0,
     255, 128, 0, 0,
     255, 64, 0, 0,
     255, 0, 0, 64,
     255, 0, 0, 128,
     255, 0, 0, 255};


int idex = 0;
uint8_t thishuehail = 183;
int TOP_INDEX = int(NUM_LEDS / 2);
int antipodal_index(int i) {
  int iN = i + TOP_INDEX;
  if (i >= TOP_INDEX) {
    iN = ( i + TOP_INDEX ) % NUM_LEDS;
  }
  return iN;
}

void Test()
{
idex++;
    if (idex >= NUM_LEDS) {
      idex = 0;
    }
    int idexY = idex;
    int idexB = antipodal_index(idexY);
    int thathue = ( thishuehail + 64) % 255;
    leds[idexY] = CRGB::Blue; //CHSV(thishuehail, thissat, 255);
    leds[idexB] = CRGB::Red; //CHSV(thathue, thissat, 255);
    
    FastLED.show();  
}

 void Test2()
 {
     uint8_t BeatsPerMinute = 62;
     CRGBPalette16 palette = bhw3_41_gp;
     uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
     int indexPalette = 0;
     for (int i = 0; i < NUM_LEDS; i++)
     { //9948
         leds[i] = ColorFromPalette(palette, random(0, 255), beat - gHue + (i * 10));
        //  indexPalette = indexPalette + (255 / NUM_LEDS);
        //  if(indexPalette > 255) indexPalette = 0;
     }

     FastLED.show();
  }
/************************* TEST ******************/
int R = 255;
int B = 0;
int boucleOL = 0;
void OLChenillard()
{
    // for(int i = 0; i < boucle; i = i + 5)
    // {
    //     int swap = R;
    //     R = B;
    //     B = swap;
    //     for(int pixel = 0; pixel < boucle; pixel++)
    //         setPixel(i + pixel, R, 0, B);
    // }

    for(int position = boucleOL; position <= NUM_LEDS; position = position + 5)
    {
        for(int pixel = 0; pixel < 5; pixel++)
            setPixel(position + pixel, R, 0, B);
        
        int swap = R;
        R = B;
        B = swap;

    }
    FastLED.show();

    boucleOL++;
    if(boucleOL > NUM_LEDS)
        boucleOL = 0;
    
}

void ToutesCouleurs() 
{
  teinte = 0;
  indexLed++;

  int ghue = (teinte + 80) % 255;
  int bhue = (teinte + 160) % 255;
 
  int N3  = int(NUM_LEDS/10);
  int N12 = int(NUM_LEDS/40);  

  for(int i = 0; i < N3; i++ ) {
    int j0 = (indexLed + i + NUM_LEDS - N12) % NUM_LEDS;
    int j1 = (j0+N3) % NUM_LEDS;
    int j2 = (j1+N3) % NUM_LEDS;    
    leds[j0] = CHSV(teinte, saturation, brillance);
    leds[j1] = CHSV(ghue, saturation, brillance);
    leds[j2] = CHSV(bhue, saturation, brillance);    
  }
   FastLED.show();
   delay(100);
}

void FlashSurFondRouge()
{
 
    setAll(32, 0, 0);

    int Pixel = random(NUM_LEDS);
    setPixel(Pixel, 0xff, 0xff, 0xff);
   FastLED.show();
    delay(50);
    setPixel(Pixel, 32, 0, 0);

    Pixel = random(NUM_LEDS);
    setPixel(Pixel, 0xff, 0xff, 0xff);
   FastLED.show();
    delay(50);
 
}

void ArcEnCielQuiMonte() 
{
  indexLed++;
  teinte = teinte + pas;
  if (indexLed >= NUM_LEDS) {indexLed = 0;}
  if (teinte > 255) {teinte = 0;}
  leds[indexLed] = CHSV(teinte, saturation, brillance);
  FastLED.show();
  delay(5);
}