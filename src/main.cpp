/**
 * @file main.cpp
 * @author Henri Buyse <a href="mailto:henri.buyse@gmail.com">henri.buyse@gmail.com</a>
 */

#include "PushBullet.hpp"

#ifdef _LOG_
#include "log.hpp"
#endif

#define VERSION "0.0.1"



int main(int argc, char* argv[]) {

#ifdef _DEBUG_
    std::cout << "Mode:   DEBUG" << std::endl;
#endif

    boost::program_options::variables_map vm;
    boost::program_options::options_description visible;
    boost::program_options::options_description generic("Generic options");
    boost::program_options::options_description display("Display options");
    boost::program_options::options_description type("Type of push");
    boost::program_options::options_description contact("Contact options");
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
        ;

        display.add_options()
            ("display-all",      "Display user informations and devices informations.")
            ("display-devices", "Display devices informations.")
            ("display-infos",    "Display user informations.")
        ;

        type.add_options()
            ("note,n", "Push a note.")
            ("link,l", "Push a link.")
            ("file,f", "Push a file.")
        ;

        param.add_options()
            ("device,d",
                boost::program_options::value<std::string>(&device)->default_value("All"),
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

        contact.add_options()
            ("contact,c", "List all contacts.")
        ;

        visible.add(generic).add(display).add(type).add(param).add(contact);

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


    /* Asking for help
     */
    if (vm.count("help")) {
        std::cout << "Pushbullet v" << VERSION << std::endl;
        std::cout << visible << std::endl;
        return EXIT_SUCCESS;
    }


    /* If pushing a note
     */
    if (vm.count("note") && vm.count("body") && vm.count("title")) {
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
            std::cerr << "PB_CREATION > " << e.what() << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }
    else if (vm.count("note")) {
        std::cerr << "NOTE > Need a title (-t) and a body (-b)" << std::endl;
        return EXIT_FAILURE;
    }


    /* If pushing a link
     */
    if (vm.count("link") && vm.count("body") && vm.count("title") && vm.count("url")) {
        try {
            PushBullet  pb;

            /* Download basic informations
             */
            pb.download_user_informations();
            pb.download_all_devices();

            /* Send a note
             */
            pb.link(title, body, url);
        }
        catch (const std::exception& e) {
            std::cerr << "PB_CREATION > " << e.what() << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }
    else if (vm.count("link")) {
        std::cerr << "LINK > Need a title (-t), a body (-b) and an URL (-u)" << std::endl;
        return EXIT_FAILURE;
    }


    /* Asking for all the infos
     */
    if (vm.count("display-all")){
        try {
            PushBullet  pb;

            /* Download basic informations
             */
            pb.download_user_informations();
            pb.download_all_devices();

            /* Send a note
             */
            pb.display_user_informations();
            pb.display_devices();
        }
        catch (const std::exception& e) {
            std::cerr << "PB_CREATION > " << e.what() << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }


    /* Asking for user informations
     */
    if (vm.count("display-infos")){
        try {
            PushBullet  pb;

            /* Download and display the informations about the user
             */
            pb.download_user_informations();
            pb.display_user_informations();
        }
        catch (const std::exception& e) {
            std::cerr << "PB_CREATION > " << e.what() << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }


    /* Asking for devices informations
     */
    if (vm.count("display-devices")){
        try {
            PushBullet  pb;

            /* Download and display a list of the account devices
             */
            pb.download_all_devices();
            pb.download_user_informations();
            pb.display_devices();
        }
        catch (const std::exception& e) {
            std::cerr << "PB_CREATION > " << e.what() << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }


    /* Contact
     */
    if (vm.count("contact")) {
        try {
            PushBullet  pb;

            /* Download and display a list of the account devices
             */
            // pb.create_contact("Henri Buyse Pro", "henri.buyse.pro@gmail.com");
            pb.download_contacts();
            pb.display_contacts();

        }
        catch (const std::exception& e) {
            std::cerr << "PB_CREATION > " << e.what() << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    /* If no options are given, we display the help
     */
    std::cout << "Pushbullet v" << VERSION << std::endl;
    std::cout << visible << std::endl;
    return EXIT_SUCCESS;
}