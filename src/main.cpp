#include "PushBullet.hpp"

#define VERSION "0.0.1"


// namespace po = boost::program_options;

int main(int argc, char* argv[]) {

#ifdef _DEBUG_
    std::cout << "Mode:   DEBUG" << std::endl;
#endif

    boost::program_options::variables_map vm;
    boost::program_options::options_description visible("Allowed options");
    boost::program_options::options_description generic("Generic options");
    boost::program_options::options_description type("Type of push");
    boost::program_options::options_description param("Parameters");

    std::string device;
    std::string title;
    std::string body;
    std::string url;
    std::string path_file;


    try {
        /* Add the different options to generic options
         */
        generic.add_options()
            ("help,h",    "Produce this help message.")
            ("version,v", "Print program's version.")
        ;

        type.add_options()
            ("note,n", "Push a note.")
            ("link,l", "Push a link.")
            ("file,f", "Push a file.")
        ;

        param.add_options()
            ("device,d",
                boost::program_options::value<std::string>(&device)->default_value("All devices"),
                "Send to a specific device (designated by its name).")
            ("title,t",
                boost::program_options::value<std::string>(&title),
                "Title of the push.")
            ("body,b",
                boost::program_options::value<std::string>(&body),
                "Body of the push.")
            ("url,u",
                boost::program_options::value<std::string>(&url),
                "URL that will be send push.")
            ("path-file,p",
                boost::program_options::value<std::string>(&path_file),
                "Path to the file you want to push.")
        ;

        visible.add(generic).add(type).add(param);

        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, visible), vm);
        boost::program_options::notify(vm);


    }
    catch(const std::exception& e) {
        std::cerr << "ERROR > " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch(...) {
        std::cerr << "Exception of unknown type!" << std::endl;
        return EXIT_FAILURE;
    }


    if (vm.count("help")) {
        std::cout << visible << std::endl;
        return EXIT_SUCCESS;
    }

    if (vm.count("version")) {
        std::cout << "Pushbullet v" << VERSION << std::endl;
        return EXIT_SUCCESS;
    }


    if (vm.count("note") && vm.count("body") && vm.count("title")) {
        std::cout << "Title  : " << title << std::endl;
        std::cout << "Body   : " << body  << std::endl;
        std::cout << "Device : " << device  << std::endl;

        try {
            PushBullet  pb;

            /* Download basic informations
             */
            pb.download_user_informations();
            pb.download_all_devices();

            /* Send a note
             */
            pb.note(title, body);

        }
        catch (const std::exception& e) {
            std::cerr << "PUSHBULLET_CREATION > " << e.what() << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
