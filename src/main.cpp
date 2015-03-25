/**
 * @file main.cpp
 * @author Henri Buyse <a href="mailto:henri.buyse@gmail.com">henri.buyse@gmail.com</a>
 */

#include "PushBullet.hpp"

#ifdef _LOG_
    #include "log.hpp"
#endif

#ifndef PUSHBULLET_INI
/**
 * File containing informations about the user account
 */
    #define PUSHBULLET_INI "./pb.ini"
#endif // PUSHBULLET_INI

#ifndef TOKEN_NODE
/**
 * Node that give the user's token from the config file.
 */
    #define TOKEN_NODE "token.personnal"
#endif // TOKEN_NODE


/**
 * @brief Get the token key from the file 'pb.ini'
 *
 * @return The user's token key.
 */
std::string get_token_key_ini(void)
{
    boost::property_tree::ptree pt;

    try {
        boost::property_tree::ini_parser::read_ini(PUSHBULLET_INI, pt);
        return pt.get<std::string>(TOKEN_NODE);
    }
    catch (const std::exception& e) {
        std::cerr   << "TOKENKEY > " << e.what() << std::endl
                    << "TOKENKEY > Using \"00000000000000000000000000000000\"" << std::endl;
        return "00000000000000000000000000000000";
    }
}




int main(int argc, char* argv[])
{

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
    boost::program_options::options_description test("Testing param");

    std::string device;
    std::string title;
    std::string body;
    std::string url;
    std::string path_file;


    try {
        /* Add the different options to generic options
         */
        generic.add_options()
            ("help,h", "Produce this help message.")
        ;

        display.add_options()
            ("display-all", "Display user informations and devices informations.")
            ("display-devices", "Display devices informations.")
            ("display-infos", "Display user informations.")
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

        test.add_options()
            ("test", "Testing parameters")
        ;

        visible.add(generic).add(display).add(type).add(param).add(contact).add(test);

        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, visible), vm);
        boost::program_options::notify(vm);
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR > " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "Exception of unknown type!" << std::endl;
        return EXIT_FAILURE;
    }



    /* Get the token from file
     */
    PushBullet pb(get_token_key_ini());

    /* Download all infos
     */
    pb.download_all_devices();
    pb.download_user_informations();
    pb.download_contacts();

    /* Asking for help
     */
    if (vm.count("help"))
    {
        std::cout << "Pushbullet v" << VERSION << std::endl;
        std::cout << visible << std::endl;
        return EXIT_SUCCESS;
    }

    /* If pushing a note
     */
    if (vm.count("note") && vm.count("body") && vm.count("title"))
    {
        pb.note(title, body);
        return EXIT_SUCCESS;
    }
    else if (vm.count("note"))
    {
        std::cerr << "NOTE > Need a title (-t) and a body (-b)" << std::endl;
        return EXIT_FAILURE;
    }

    /* If pushing a link
     */
    if (vm.count("link") && vm.count("body") && vm.count("title") && vm.count("url"))
    {
        pb.link(title, body, url);
        return EXIT_SUCCESS;
    }
    else if (vm.count("link"))
    {
        std::cerr << "LINK > Need a title (-t), a body (-b) and an URL (-u)" << std::endl;
        return EXIT_FAILURE;
    }

    /* Asking for all the infos
     */
    if (vm.count("display-all"))
    {
        pb.display_user_informations();
        pb.display_devices();

        return EXIT_SUCCESS;
    }

    /* Asking for user informations
     */
    if (vm.count("display-infos"))
    {
        pb.download_user_informations();
        pb.display_user_informations();

        return EXIT_SUCCESS;
    }

    /* Asking for devices informations
     */
    if (vm.count("display-devices"))
    {
        pb.display_devices();
        return EXIT_SUCCESS;
    }

    /* Contact
     */
    if (vm.count("contact"))
    {
        pb.display_contacts();
        pb.update_contact("Henri Buyse Pro", "Henri Buyse Pro");
        pb.display_contacts();
        // pb.delete_contact("Henri Buyse Pro");

        return EXIT_SUCCESS;
    }

    /* File
     */
    if (vm.count("file") && vm.count("path-file") && vm.count("body") && vm.count("title"))
    {
        pb.file(title, body, path_file);
        return EXIT_SUCCESS;
    }

    if (vm.count("test"))
    {
        // pb.list_pushes();
        pb.update_push("ujEIL5AaxhYsjAyGmVhHYO", 0);
        // pb.update_push("ujEIL5AaxhYsjAyGmVhHYO", 1);

        return EXIT_SUCCESS;
    }

    /* If no options are given, we display the help
     */
    std::cout << "Pushbullet v" << VERSION << std::endl;
    std::cout << visible << std::endl;
    return EXIT_SUCCESS;
}