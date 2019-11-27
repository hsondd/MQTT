#include "myMosquitto.h"

#include <iostream>

myMosquitto::myMosquitto(const char* _id, const char* _host, int _port) :
    mosquittopp(_id)
{
    int ret;
    mosqpp::lib_init();

    this->keepalive = 20;
    // const char *mosquitto_strerror(int mosq_errno);
    // if (username_pw_set("sampleuser", "samplepass") != MOSQ_ERR_SUCCESS) {
    //     std::cout << "setting passwd failed" << std::endl;
    // }
    this->id = _id;
    this->port = _port;
    this->host = _host;
    connect_async(host,port, keepalive);
    // std::cout << "connect ret " << ret << mosqpp::strerror(ret) << std::endl;
    // ret = subscribe(NULL, topic, 1);
    // std::cout << "subcribe ret" << ret << mosqpp::strerror(ret) << std::endl;

    // if (loop_start() != MOSQ_ERR_SUCCESS) {
    //     std::cout << "loop_start failed" << std::endl;
    // }
    loop_start();
}

myMosquitto::~myMosquitto()
{
    // std::cout << "1" << std::endl;
    // if (loop_stop() != MOSQ_ERR_SUCCESS) {
    //     std::cout << "loop_stop failed" << std::endl;
    // }
    // std::cout << "2" << std::endl;
    // mosqpp::lib_cleanup();
    // std::cout << "3" << std::endl;
    loop_stop();
    mosqpp::lib_cleanup();
}

void myMosquitto::on_connect(int rc){
    // std::cout << "Connected success " << rc << std::endl;
    if ( rc == 0 ) {
        std::cout << "Connected success with server: "<< this->host << std::endl;
        // std::cout << "Enter message: ";
        // std::getline(std::cin,mess);
    }
    else{
        std::cout << "Cant connect with server(" << rc << ")" << std::endl;
    }
}
void myMosquitto::on_disconnect(int rc){
   std::cout << "Disconnected (" << rc << ")" << std::endl;
}

void myMosquitto::on_publish(int mid) {
    std::cout << "Published message with id: " << mid << std::endl;
}

void myMosquitto::on_subscribe(int mid, int qos_count, const int *granted_qos){
    std::cout << "Subscribed(" << mid << ")" << std::endl;
}

void myMosquitto::on_unsubscribe(int mid){
    std::cout << "Unsubscribed(" << mid << ")" << std::endl;
}

void myMosquitto::myPublish(std::string topic, std::string mess){
    // std::cout << "Topic: ";
    // std::getline(std::cin,topic);
    // std::cout << "Enter message: ";
    // std::getline(std::cin,mess);
    int ret = publish(NULL, topic.c_str(), mess.size(), mess.c_str(), 1, false);
    if (ret != MOSQ_ERR_SUCCESS){
        std::cout << "Send failed." << std::endl;
    }
    else std::cout << "Message: " << mess << " >>> published to: " << topic << std::endl;
}
void myMosquitto::subscribe_to_topic(std::string topic){
    int ret = subscribe(NULL, topic.c_str());
    // if (ret != MOSQ_ERR_SUCCESS){
    //     std::cout << "Subcribe failed" << std::endl;
    // }
    // else std::cout << "Subcribe success " << std::endl;
}
void myMosquitto::unsubscribe_from_topic(std::string topic){
    int ret = unsubscribe(NULL, topic.c_str());
    if (ret != MOSQ_ERR_SUCCESS){
        std::cout << "Unsubcribe failed" << std::endl;
    }
    else std::cout << "Unsubcribe success " << std::endl;
    // return (MOSQ_ERR_SUCCESS);
}