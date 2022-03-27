
/*
 * Build: clang  -std=c++17 -O2  -Wall $(pkg-config --cflags --libs glib-2.0 gio-2.0 ) main.cc useful_service.o   -lstdc++ -o out_glib
 */

#include <glib.h>

#include <iostream>
#include <filesystem>
#include <fstream>

#include "useful_service.h"

static void on_name_acq(GDBusConnection *conn, const gchar *name, gpointer user_data);
static void on_handle_quit(Useful_service *skel,
                           GDBusMethodInvocation *inv,
                           gpointer user_data);

static int emit_full_status(gpointer skel);

static GMainLoop *loop{nullptr};

static int emit_full_status(gpointer skel)
{
    std::cout << "Full Status Update" << std::endl;
    return true;
}


static void on_handle_quit(Useful_service *skel,
                           GDBusMethodInvocation *inv,
                           gpointer user_data)
{
    std::cout << "Quitting service" << std::endl;

    // FIXME: quit properly using a flag in the timeout dispatch
    g_main_loop_quit(loop);
}

static void on_name_acq(GDBusConnection *conn, const gchar *name, gpointer user_data)
{
    std::cout << "Name acquired, name=[" << name << "]" << std::endl;

    auto* skel = useful_service_skeleton_new();
    g_signal_connect(skel, "handle-quit", G_CALLBACK(on_handle_quit), nullptr);

    g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(skel),
                                     conn, "/com/pobetiger/useful_service",
                                     nullptr);


    // add a time to emit status update every 3 seconds
    g_timeout_add_seconds(3, emit_full_status, skel);
}


int main()
{
    std::cout << "Service starts" << std::endl;

    loop = g_main_loop_new(nullptr, false);
    g_bus_own_name(G_BUS_TYPE_SESSION, "com.pobetiger.useful_service",
                   G_BUS_NAME_OWNER_FLAGS_NONE,
                   nullptr,
                   on_name_acq,
                   nullptr,
                   nullptr,
                   nullptr);

    std::cout << "Starting main loop" << std::endl;
    g_main_loop_run(loop);

    std::cout << "Service finished" << std::endl;
    return 0;
}

