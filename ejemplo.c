#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <atmi.h>
#include <fml32.h>
#include <string.h>
#include "bib_proyecto.fml.h"

// Estructura para almacenar los datos del automóvil
typedef struct Autos {
    int autoID;
    char marca[50];
    char modelo[51];
    char anio[10];
    char color[50];
    double precio;
} Autos;

// Prototipo de la función de callback para el botón "Seleccionar todos"
void on_select_todos_clicked(GtkButton *button, GtkWidget *text_view);

int main(int argc, char **argv) {
    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear la ventana principal
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Agencia de Autos");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Crear un botón para "Seleccionar todos"
    GtkWidget *button_select_todos = gtk_button_new_with_label("Mostrar");
    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);

    // Conectar la señal del botón con la función de callback
    g_signal_connect(button_select_todos, "clicked", G_CALLBACK(on_select_todos_clicked), text_view);

    // Crear un contenedor para organizar los widgets
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_box_pack_start(GTK_BOX(box), button_select_todos, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), text_view, TRUE, TRUE, 0);

    // Mostrar todo
    gtk_widget_show_all(window);

    // Iniciar el bucle principal de GTK
    gtk_main();

    return 0;
}

// Función de callback para el botón "Seleccionar todos"
void on_select_todos_clicked(GtkButton *button, GtkWidget *text_view) {
    // Obtener el buffer de texto del text_view
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    // Borrar el contenido anterior del área de texto
    gtk_text_buffer_set_text(buffer, "", -1);

    // Lógica para llamar al servicio "SELECT_TODOS_AgenciaAutos"
    int ivL_resLlamd;
    long lvL_tamLongt;
    float fvL_recValor;
    FBFR32 *fbfr;
    FBFR32 *recv;
    FLDLEN32 flen;
    char msgbuf[64];
    Autos *autosRegis;
    Autos carro;
    int ivL_numOcurr;
    int ivl_iterador;

    // Conectamos con la aplicación Tuxedo Server
    printf("Conectamos con la aplicacion\n");
    if (tpinit((TPINIT *)NULL) == -1) {
        printf("Error en la conexion, tperrno = %d \n", tperrno);
        return;
    }

    // Reservamos espacio para el buffer FML
    printf("Reservamos Espacio para los buffers FML\n");
    if ((fbfr = (FBFR32 *)tpalloc("FML32", NULL, 1024)) == NULL) {
        printf("Error Reservando espacio para Buffer fbfr\n");
        tpterm();
        return;
    }
    if ((recv = (FBFR32 *)tpalloc("FML32", NULL, 1024)) == NULL) {
        printf("Error Reservando espacio para Buffer recv\n");
        tpterm();
        return;
    }

    // Invocamos el servicio
    printf("Llamada al servicio 'SELECT_TODOS_AgenciaAutos'\n");
    if (tpcall("SELECT_TODOS_AgenciaAutos", (char *)fbfr, 0, (char **)&recv, &lvL_tamLongt, 0L) == -1) {
        printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
        tpfree((char *)fbfr);
        tpfree((char *)recv);
        tpterm();
        return;
    }

    // Lógica para procesar los datos recibidos y mostrarlos en el área de texto
    if ((ivL_numOcurr = Foccur32(recv, AUTOID)) < 0) {
        printf("Error en Foccur32\n");
        tpfree((char *)fbfr);
        tpfree((char *)recv);
        tpterm();
        return;
    }

    printf("Numero de ocurrencias: %d\n", ivL_numOcurr);
    autosRegis = (Autos *)malloc(sizeof(Autos) * ivL_numOcurr);

    flen = sizeof(msgbuf);
    printf("***************************************************\n");
    for (ivl_iterador = 0; ivl_iterador < ivL_numOcurr; ivl_iterador++) {
        Fget32(recv, AUTOID, ivl_iterador, (char *)&autosRegis[ivl_iterador].autoID, 0);
        printf("ID carro : %d\n", autosRegis[ivl_iterador].autoID);

        Fget32(recv, MARCA, ivl_iterador, (char *)autosRegis[ivl_iterador].marca, 0);
        printf("Nombre de la marca : %s\n", autosRegis[ivl_iterador].marca);

        Fget32(recv, MODELO, ivl_iterador, (char *)autosRegis[ivl_iterador].modelo, 0);
        printf("modelo: %s\n", autosRegis[ivl_iterador].modelo);

        Fget32(recv, ANIO, ivl_iterador, (char *)autosRegis[ivl_iterador].anio, 0);
        printf("Anio del automovil : %s\n", autosRegis[ivl_iterador].anio);

        Fget32(recv, COLOR, ivl_iterador, (char *)autosRegis[ivl_iterador].color, 0);
        printf("Color del automovil : %s\n", autosRegis[ivl_iterador].color);

        Fget32(recv, PRECIO, ivl_iterador, (char *)&autosRegis[ivl_iterador].precio, 0);
        printf("Precio del automovil : %lf\n", autosRegis[ivl_iterador].precio);

        // Concatenar la información en una cadena de texto y agregarla al área de texto
        char text[1000];
        sprintf(text, "ID carro : %d\nNombre de la marca : %s\nModelo: %s\nAño del automóvil: %s\nColor del automóvil: %s\nPrecio del automóvil: %.2lf\n\n",
                autosRegis[ivl_iterador].autoID, autosRegis[ivl_iterador].marca, autosRegis[ivl_iterador].modelo,
                autosRegis[ivl_iterador].anio, autosRegis[ivl_iterador].color, autosRegis[ivl_iterador].precio);
        gtk_text_buffer_insert_at_cursor(buffer, text, -1);
    }

    // Liberar memoria y desconectar de la aplicación Tuxedo
    printf("Liberamos Buffer y desconectamos de la aplicacion\n");
    free(autosRegis);
    tpfree((char *)fbfr);
    tpfree((char *)recv);
    tpterm();
}
