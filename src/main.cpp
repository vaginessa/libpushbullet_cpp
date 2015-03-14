#include "PushBullet.hpp"

#define APIKEY "YpiQLDdMfEkhAFabFZbNwAq8FVcBVGWn"

using namespace std;

int main(void) {

    #ifdef _DEBUG_
    std::cout << "Mode: DEBUG" << std::endl;
    #endif

    PushBullet pb = PushBullet(APIKEY);
    pb.get_all_devices();

    // std::string example = "{\"type\": \"note\", \"title\": \"Note Title\", \"body\": \"Note Body\"}";
    // pb.pushing(example);

    // std::string title = "Toto";
    // std::string body = "Toto est dans la place n3";
    // pb.note(title, body, "ujEIL5AaxhYsjAiVsKnSTs");


    // std::string body = "URL Body";
    // std::string title = "URL Title";
    // std::string url = "https://www.google.fr";
    // pb.link(title, body, url);


    pb.display_devices();

    return 0;
}