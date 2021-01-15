#include "message.hpp"

#include <belt.pp/log.hpp>
#include <belt.pp/scope_helper.hpp>
#include <belt.pp/direct_stream.hpp>
#include <belt.pp/log.hpp>
#include <belt.pp/message_global.hpp>

#include <mesh.pp/fileutility.hpp>
#include <mesh.pp/settings.hpp>

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

static inline
beltpp::void_unique_ptr get_putl()
{
    beltpp::message_loader_utility utl;
    Test::detail::extension_helper(utl);

    auto ptr_utl =
        beltpp::new_void_unique_ptr<beltpp::message_loader_utility>(std::move(utl));

    return ptr_utl;
}

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

        meshpp::vector_loader<Test::Data> persistent("data", fs_data, 10000, 1, get_putl());

        bool append = true;
        size_t limit = 1;
        size_t step = 0;

        while (true)
        {
            try
            {
                if (append)
                {
                    cout << "size: " << persistent.size() << ";\tlimit: " << limit << ";\tpush_back ...\n";
                    Test::Data a;
                    a.s.reserve(limit);
                    for (size_t index = 0; index < limit; ++index)
                        a.s += "0";
                    persistent.push_back(a);

                    limit *= 10;
                }
                else
                {
                    cout << "size: " << persistent.size() << ";\tstep: " << step << ";\tpop_back ...\n";
                    persistent.pop_back();
                    append = true;
                }

                ++step;

                persistent.save();
                persistent.commit();
                //persistent.discard();
            }
            catch(std::logic_error const& ex)
            {
                cout << "logic error: " << ex.what() << endl;
                break;
            }
            catch(std::exception const& ex)
            {
                cout << "exception cought: " << ex.what() << endl;
                limit = 1;
                append = false;
                persistent.discard();
            }
            catch(...)
            {
                cout << "unknown exception cought\n";
                limit = 1;
                append = false;
                persistent.discard();
            }
        }

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

