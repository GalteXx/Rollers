#include <TroykaDHT.h>
#include <AceRoutine.h>


DHT term(5, DHT11);

int lastInformationFetch;
int targetTMP;
bool isEnabled = true;


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
    Serial.begin(9600);
    term.begin();
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
        isEnabled = !isEnabled;
        //turn transistor on or off respectively
    }
    else
        targetTMP = prcss(order);

}

void loop(){
    dataExchange();

    if(!isEnabled)
        return;

    if(term.getTemperatureC() > targetTMP /*&& TransistorEnabled*/){
        //turn transistor off
    }
    else if(term.getTemperatureC() < targetTMP /*&& TransistorDisabled*/){
        //turns transistor on
    }
    
    //anything else?
    
}