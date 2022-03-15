
#include <TroykaThermometer.h>

#define TRANS 6



TroykaThermometer term(A0);

int lastInformationFetch = 0;
int targetTMP;
bool isEnabled = true;
bool TransEnabled = false;


int prcss(String str){
    String out = "";
    int i;
    for(i = 0; str[i] != ' '; i++){
        out = out + str[i];
    }
    if(out == "Toggle")
        return -1;
    if(out == "SetTMP"){
        int ret;
        for(i; str[i] != '\0'; i++){
            ret += str[i] - 48;
            ret *= 10;
        }
        return ret;
    }
        
}

void setup(){
    //pins should go here
    pinMode(7, OUTPUT);
    Serial.begin(9600);
    Serial.println(-1);
}


void dataExchange(){
    const unsigned long currentTime = millis(); //this should be fine, unless ran for 49 days straight
    
    if(currentTime - lastInformationFetch >= 10000){
        Serial.print("GetTMP\n");
        Serial.print(term.getTemperatureC());
        //Serial.print("GetBatteryStat\n");
        //Serial.print battery stat (lol, how?)
        lastInformationFetch = currentTime;
    }

    String order = Serial.readString();

    if(prcss(order) == -1){
        if(isEnabled)
            digitalWrite(TRANS, LOW);
        if(!isEnabled)
            digitalWrite(TRANS, HIGH);
        isEnabled = !isEnabled;
    }
    else
        targetTMP = prcss(order);

}



void loop(){
    dataExchange();

    if(!isEnabled)
        return;

    if(term.getTemperatureC() > targetTMP && TransEnabled){
        digitalWrite(TRANS, LOW);

    }
    else if(term.getTemperatureC() < targetTMP && !TransEnabled){
        digitalWrite(TRANS, HIGH);

    }
    
    //anything else?
    
}
