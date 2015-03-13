#include "PushBullet.hpp"

#define APIKEY "YpiQLDdMfEkhAFabFZbNwAq8FVcBVGWn"
#define EXAMPLE "{\"type\": \"note\", \"title\": \"Note Title\", \"body\": \"Note Body\"}"

using namespace std;

int main(void) {

    #ifdef _DEBUG_
    std::cout << "Mode: DEBUG" << std::endl;
    #endif

    PushBullet pb = PushBullet(APIKEY);

    // std::string example = "{\"type\": \"note\", \"title\": \"Note Title\", \"body\": \"Note Body\"}";
    // pb.pushing(example);

    // std::string body = "Note Body";
    // std::string title = "Note Title";
    // pb.note(title, body);


    // std::string body = "URL Body";
    // std::string title = "URL Title";
    // std::string url = "https://www.google.fr";
    // pb.link(title, body, url);

    pb.list_devices();

    return 0;
}