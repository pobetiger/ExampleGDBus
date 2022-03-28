
// FIXME: go for an impl class
#include "DBusApp.hpp"

#include <iostream>

// this function is used to encapsulate any knowledge of the internal guts of GDBus
// from the top-level application
void DBusApp::InitEnv()
{
    Gio::init();
}


DBusApp::DBusApp()
    : loop(Glib::MainLoop::create())
    , vtable(sigc::mem_fun(*this, &DBusApp::on_method_call))
{
}

DBusApp::~DBusApp()
{
}

bool DBusApp::on_timeout()
{
    std::cout << "Timeout" << std::endl;

    auto x = Glib::VariantContainerBase::create_tuple(Glib::Variant<std::string>::create("some fun data"));
    connection->emit_signal("/com/pobetiger/UsefulService/Control",
                            "com.pobetiger.UsefulService",
                            "Timeout",
                            "", // to all listeners
                            x);

    return true; // recur
}

void DBusApp::on_method_call(const Glib::RefPtr<Gio::DBus::Connection>&,
                         const Glib::ustring& , // sender
                         const Glib::ustring& , // obj path
                         const Glib::ustring& , // interface
                         [[maybe_unused]]const Glib::ustring& method_name,
                         [[maybe_unused]]const Glib::VariantContainerBase& params,
                         const Glib::RefPtr<Gio::DBus::MethodInvocation>& invocation)
{
    std::cout << "Method called" << std::endl;

    auto resp = Glib::VariantContainerBase{};
    invocation->return_value(resp);

    loop->quit();
}

void DBusApp::on_name_acquired(const Glib::RefPtr<Gio::DBus::Connection>& conn, const Glib::ustring&)
{
    std::cout << "Name acquired" << std::endl;
    try
    {

        conn->register_object("/com/pobetiger/UsefulService/Control", introspectData->lookup_interface(), vtable);
        connection = conn; // making a ref copy
    }
    catch (const Glib::Error& ex)
    {
        std::cout << "Exception: " << ex.what() << std::endl;
    }
}

void DBusApp::Run()
{
    try
    {
        introspectData = Gio::DBus::NodeInfo::create_for_xml(Glib::ustring{serviceXml.data()});
        const auto id = Gio::DBus::own_name(Gio::DBus::BusType::BUS_TYPE_SESSION,
                                            "com.pobetiger.UsefulService",
                                            {}, // bus acq
                                            sigc::mem_fun(*this, &DBusApp::on_name_acquired),
                                            //sigc::ptr_fun(&on_name_acquired), // name acq
                                            {}); // name lost

        Glib::signal_timeout().connect(sigc::mem_fun(*this, &DBusApp::on_timeout), 3000);
        // start the loop
        loop->run();
        Gio::DBus::unown_name(id);
    }
    catch(const Glib::Error& ex)
    {
        std::cout << "Exception: " << ex.what() << std::endl;
        throw; // propagate and quit
    }
}


