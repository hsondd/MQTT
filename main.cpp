#include "myMosquitto.h"

const char *id = "test1";
std::string _topic;
const char *host = "test.mosquitto.org";
int port = 1883;
std::string mess;

int main(int argc, char *argv[])
{   
    myMosquitto* mqtt;
    mqtt = new myMosquitto(id, host, port);
    sleep(2);
    std::cout << "Topic: ";
    std::getline(std::cin,_topic);
    mqtt->subscribe_to_topic(_topic);
    sleep(1);
    std::cout << "Enter message: ";
    std::getline(std::cin,mess);
    // std::cout << "Enter message: ";
    // std::getline(std::cin,mess);
    mqtt->myPublish(_topic, mess);   
    mqtt->unsubscribe_from_topic(_topic);
    // std::cout << "About to delete mqtt" << std::endl;
    //delete mqtt;
    // std::cout << "Mqtt deleted" << std::endl;
    return 0;
}