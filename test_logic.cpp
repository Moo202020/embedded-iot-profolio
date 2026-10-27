#include <cassert>
#include <cstring>
#include <iostream>
#include "projects/esp32-home-lighting/HomeLighting/LightController.h"
#include "projects/digital-white-stick/DistanceMonitor/DistanceAlarm.h"
#include "projects/stm32-foundations/FoundationLogic.h"
int main() {
 LightController light;
 assert(!light.update(0,false));
 assert(light.update(100,true));
 assert(light.update(240099,false));
 assert(!light.update(240100,false));
 assert(light.update(300000,true));
 assert(light.update(400000,true));
 assert(light.update(639999,false));
 assert(!light.update(640000,false));
 LightController wrap(100);
 assert(wrap.update(0xfffffff0u,true));
 assert(wrap.update(0x53u,false));
 assert(!wrap.update(0x54u,false));
 LightController zero(0);
 assert(zero.update(5,true)); assert(!zero.update(5,false));
 DistanceAlarm alarm;
 assert(!alarm.update(200,true));
 assert(alarm.update(150,true));
 assert(alarm.update(179,true));
 assert(!alarm.update(180,true));
 assert(alarm.update(100,true));
 assert(!alarm.update(100,false));
 assert(!alarm.update(160,true));
 assert(adcMillivolts(0)==0);
 assert(adcMillivolts(4095)==3300);
 assert(adcMillivolts(9000)==3300);
 assert(adcMillivolts(100,0)==0);
 assert(adcMillivolts(1023,1023,5000)==5000);
 LineParser<5> parser;
 assert(!parser.feed('O')); assert(!parser.feed('K'));
 assert(!parser.feed('\r')); assert(parser.feed('\n'));
 assert(std::strcmp(parser.line(),"OK")==0);
 assert(!parser.feed('\n'));
 for (char c: "ABCDE") if(c) assert(!parser.feed(c));
 assert(!parser.feed('\n')); // Overflowed line discarded.
 assert(!parser.feed('A')); assert(parser.feed('\n'));
 assert(std::strcmp(parser.line(),"A")==0);
 std::cout<<"All host application logic checks passed. Hardware checks pending.\n";
}
