
/*
 * This is a minimal eaxmple of a useful service example using glibmm and giomm.
 * And it compiles...
 *
 * Build: clang  -std=c++17 -O2 -Werror -Weverything -Wall $(pkg-config --cflags --libs glibmm-2.4 giomm-2.4) mainpp.cc DBusApp.cc -lstdc++
 *
*/

#include <string_view>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat"
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wextra-semi"
#pragma clang diagnostic ignored "-Wextra-semi-stmt"

#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-exception-parameter"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wexit-time-destructors"

#include <glibmm.h>
#include <giomm.h>

#pragma clang diagnostic pop

#pragma clang diagnostic ignored "-Wc++98-compat"


class DBusApp
{
public:

    static void InitEnv();

    DBusApp();
    ~DBusApp();

    DBusApp(const DBusApp&) =delete;
    DBusApp(DBusApp&&) =delete;
    DBusApp& operator=(const DBusApp&) =delete;
    DBusApp& operator=(DBusApp&&) =delete;

    void Run();
    void on_name_acquired(const Glib::RefPtr<Gio::DBus::Connection>& conn, const Glib::ustring& name);
    void on_method_call(const Glib::RefPtr<Gio::DBus::Connection>&,
                        const Glib::ustring& , // sender
                        const Glib::ustring& , // obj path
                        const Glib::ustring& , // interface
                        const Glib::ustring& method_name,
                        const Glib::VariantContainerBase& params,
                        const Glib::RefPtr<Gio::DBus::MethodInvocation>& invocation);
    bool on_timeout();

private:

    Glib::RefPtr<Glib::MainLoop> loop;

    Glib::RefPtr<Gio::DBus::NodeInfo> introspectData;
    Gio::DBus::InterfaceVTable vtable;
    Glib::RefPtr<Gio::DBus::Connection> connection;

    static constexpr std::string_view serviceXml = {
        "<node>"
        "   <interface name='com.pobetiger.UsefulService'>"
        "       <method name='quit'></method>"
        "   </interface>"
        "</node>"
    };
};


