#include <gtk/gtk.h>
#include "interface.h"

int main(int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    // Inicializa o GTK application com as flags padrão
    app = gtk_application_new("com.exemplo.simulador", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(criar_interface), NULL);

    // Executa o aplicativo
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
