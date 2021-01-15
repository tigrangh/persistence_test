#include <belt.pp/log.hpp>
#include <belt.pp/scope_helper.hpp>
#include <belt.pp/direct_stream.hpp>
#include <belt.pp/log.hpp>

#include <mesh.pp/fileutility.hpp>

#include <boost/locale.hpp>

#include <iostream>
#include <exception>
#include <string>
#include <memory>

using std::unique_ptr;
using std::string;
using std::cout;
using std::endl;
using std::runtime_error;

int main(int argc, char** argv)
{
    try
    {
        //  boost filesystem UTF-8 support
        std::locale::global(boost::locale::generator().generate(""));
        boost::filesystem::path::imbue(std::locale());
    }
    catch (...)
    {}  //  don't care for exception, for now
    //
    meshpp::settings::set_application_name("persistence_test");
    meshpp::settings::set_data_directory(meshpp::config_directory_path().string());

    try
    {
        meshpp::create_config_directory();
        meshpp::create_data_directory();

        auto fs_data = meshpp::data_directory_path("data");
        
        beltpp::ilog_ptr plogger = beltpp::console_logger("main", true);
        //plogger->disable();

    }
    catch (std::exception const& ex)
    {
        cout << "exception cought: " << ex.what() << endl;
    }
    catch (...)
    {
        cout << "always throw std::exceptions" << endl;
    }

    cout << "quit." << endl;

    return 0;
}

