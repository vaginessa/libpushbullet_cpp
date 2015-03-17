#include "PushBullet.hpp"

#define VERSION 0.0.1

using namespace std;
namespace po = boost::program_options;

int main(int argc, char* argv[]) {

#ifdef _DEBUG_
    std::cout << "Mode:   DEBUG" << std::endl;
#endif
/*
    try {
        po::options_description generic("generic options");
        desc.add_options()
            ("help,h", "produce this help message")
            ("version,v", "print program's version")
        ;

        po::variables_map vm;        
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);    

        if (vm.count("help")) {
            cout << desc << "\n";
            return 0;
        }

        if (vm.count("compression")) {
            cout << "Compression level was set to " 
                 << vm["compression"].as<double>() << ".\n";
        } else {
            cout << "Compression level was not set.\n";
        }
    }
    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch(...) {
        cerr << "Exception of unknown type!\n";
    }
*/
    try {
        PushBullet  pb;
    
        pb.get_user_informations();
    
        #ifdef _DEBUG_
        pb.display_user_informations();
        pb.display_devices();
        #endif
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR > " << e.what() << std::endl;
        return -1; 
    }

    // pb.get_all_devices();

    // std::string example = "{\"type\": \"note\", \"title\": \"Note Title\", \"body\": \"Note Body\"}";
    // pb.pushing(example);

    // std::string title = "Toto";
    // std::string body = "Toto est dans la place n3";
    // pb.note(title, body, "ujEIL5AaxhYsjAiVsKnSTs");


    // std::string body = "URL Body";
    // std::string title = "URL Title";
    // std::string url = "https://www.google.fr";
    // pb.link(title, body, url);


    // pb.display_devices();
    // pb.create_device_if_not_existing();

    // pb.display_devices();

    // pb.delete_device("AO725");

    // pb.get_all_devices();
    // pb.display_devices();


    return EXIT_SUCCESS;
}
