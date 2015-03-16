#include "PushBullet.hpp"

#define APIKEY "YpiQLDdMfEkhAFabFZbNwAq8FVcBVGWn"

using namespace std;

int main(void) {

#ifdef _DEBUG_
    std::cout << "Mode:   DEBUG" << std::endl;
    std::cout << "APIKEY: " << APIKEY << std::endl;
#endif

    PushBullet      pb = PushBullet(APIKEY);

    pb.get_all_devices();
    // pb.get_user_informations();

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
    // pb.display_user_informations();

    pb.create_device_if_not_existing();

    pb.display_devices();

    pb.delete_device("AO725");
    pb.display_devices();

    // pb.get_all_devices();
    // pb.display_devices();


    return EXIT_SUCCESS;
}
