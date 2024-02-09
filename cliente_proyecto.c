#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <atmi.h>
#include <fml32.h>
#include <string.h>
#include "bib_proyecto.fml.h"

// Estructura para almacenar los widgets necesarios para la inserción de automóviles
typedef struct {
    GtkWidget *entry_autoID;
    GtkWidget *entry_marca;
    GtkWidget *entry_modelo;
    GtkWidget *entry_anio;
    GtkWidget *entry_color;
    GtkWidget *entry_precio;
} InsertWidgets;


// Estructura para almacenar los datos del automóvil
typedef struct Autos {
    int autoID;
    char marca[50];
    char modelo[51];
    char anio[10];
    char color[50];
    double precio;
} Autos;

// Estructura para pasar múltiples objetos como argumento a la función on_buscar_clicked
typedef struct {
    GtkWidget *entry;
    GtkWidget *text_view;
} BuscarWidgets;

// Función de devolución de llamada para limpiar los valores cuando se cambia de pestaña
void on_notebook_switch_page(GtkNotebook *notebook, GtkWidget *page, guint page_num, gpointer user_data) {
    // Obtener el buffer de texto del text_view en la página actual
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(user_data));
    // Limpiar el buffer de texto
    gtk_text_buffer_set_text(buffer, "", -1);
}

// Prototipos de funciones de callback para los botones de las pestañas
void on_select_todos_clicked(GtkButton *button, GtkWidget *text_view);
void on_buscar_clicked(GtkButton *button, BuscarWidgets *widgets);
int clientDelete_AgenciaAutos(GtkButton *button, GtkWidget *entry;);

// Función para crear la ventana principal
GtkWidget *create_main_window() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Agencia de Autos");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    return window;
}

// Función para crear el contenedor de las pestañas
GtkWidget *create_notebook() {
    return gtk_notebook_new();
}

// Función para crear una página en el notebook
GtkWidget *create_notebook_page(GtkWidget *notebook, const gchar *label_text) {
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *label = gtk_label_new(label_text);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page, label);
    return page;
}

// Función para crear un campo de entrada
GtkWidget *create_entry() {
    return gtk_entry_new();
}

// Función para crear un botón con una etiqueta especificada
GtkWidget *create_button(const gchar *label_text) {
    return gtk_button_new_with_label(label_text);
}

// Función para crear un TextView no editable
GtkWidget *create_text_view() {
    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    return text_view;
}


// Función intermedia para conectarse a la señal de clic del botón de inserción
void on_button_insert_clicked(GtkButton *button, gpointer user_data) {
    // Obtener los widgets necesarios de los datos de usuario
    InsertWidgets *widgets = (InsertWidgets *)user_data;

    // Llamar a la función de inserción
    clientInsert_AgenciaAutos(widgets->entry_autoID, widgets->entry_marca, widgets->entry_modelo,
                              widgets->entry_anio, widgets->entry_color, widgets->entry_precio);
}

// Función intermedia para conectarse a la señal de clic del botón de update
void on_button_update_clicked(GtkButton *button, gpointer user_data) {
    // Obtener los widgets necesarios de los datos de usuario
    InsertWidgets *widgets = (InsertWidgets *)user_data;

    // Llamar a la función de inserción
    clientUpdate_AgenciaAutos(widgets->entry_autoID, widgets->entry_marca, widgets->entry_modelo,
                              widgets->entry_anio, widgets->entry_color, widgets->entry_precio);
}


// Función para crear la tercera pestaña para insertar un auto
    GtkWidget *create_insert_page(GtkWidget *notebook, InsertWidgets *insert_widgets) {
    GtkWidget *page_insert = create_notebook_page(notebook, "Insertar"); 
    GtkWidget *button_insert = create_button("Insertar");

    // Etiquetas explicativas
    GtkWidget *label_autoID = gtk_label_new("ID del Auto:");
    GtkWidget *label_marca = gtk_label_new("Marca:");
    GtkWidget *label_modelo = gtk_label_new("Modelo:");
    GtkWidget *label_anio = gtk_label_new("Año:");
    GtkWidget *label_color = gtk_label_new("Color:");
    GtkWidget *label_precio = gtk_label_new("Precio:");

    gtk_box_pack_start(GTK_BOX(page_insert), label_autoID, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_insert), insert_widgets->entry_autoID, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_insert), label_marca, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_insert), insert_widgets->entry_marca, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_insert), label_modelo, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_insert), insert_widgets->entry_modelo, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_insert), label_anio, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_insert), insert_widgets->entry_anio, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_insert), label_color, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_insert), insert_widgets->entry_color, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_insert), label_precio, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_insert), insert_widgets->entry_precio, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_insert), button_insert, FALSE, FALSE, 0);

    // Conectar señal de click del botón de inserción
    g_signal_connect(button_insert, "clicked", G_CALLBACK(on_button_insert_clicked), insert_widgets);
    
    return page_insert;
}

// Función para crear la tercera pestaña para insertar un auto
GtkWidget *create_update_page(GtkWidget *notebook, InsertWidgets *update_widgets) {
    GtkWidget *page_update = create_notebook_page(notebook, "Actualizar"); 
    GtkWidget *button_update = create_button("Actualizar");

    // Etiquetas explicativas
    GtkWidget *label_autoID = gtk_label_new("ID del Auto:");
    GtkWidget *label_marca = gtk_label_new("Marca:");
    GtkWidget *label_modelo = gtk_label_new("Modelo:");
    GtkWidget *label_anio = gtk_label_new("Año:");
    GtkWidget *label_color = gtk_label_new("Color:");
    GtkWidget *label_precio = gtk_label_new("Precio:");

    gtk_box_pack_start(GTK_BOX(page_update), label_autoID, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_update), update_widgets->entry_autoID, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_update), label_marca, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_update), update_widgets->entry_marca, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_update), label_modelo, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_update), update_widgets->entry_modelo, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_update), label_anio, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_update), update_widgets->entry_anio, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_update), label_color, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_update), update_widgets->entry_color, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_update), label_precio, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_update), update_widgets->entry_precio, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_update), button_update, FALSE, FALSE, 0);

    // Conectar señal de click del botón de inserción
    g_signal_connect(button_update, "clicked", G_CALLBACK(on_button_update_clicked), update_widgets);
    
    return page_update;
}


int main(int argc, char **argv) {
    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear la ventana principal
    GtkWidget *window = create_main_window();

    // Crear el contenedor de las pestañas
    GtkWidget *notebook = create_notebook();
    gtk_container_add(GTK_CONTAINER(window), notebook);

    // Crear la primera pestaña para seleccionar todos los autos
    GtkWidget *page_select_todos = create_notebook_page(notebook, "Seleccionar Todos");
    GtkWidget *button_select_todos = create_button("Seleccionar todos");
    GtkWidget *text_view_select_todos = create_text_view();
    gtk_box_pack_start(GTK_BOX(page_select_todos), button_select_todos, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_select_todos), text_view_select_todos, TRUE, TRUE, 0);

    // Crear la segunda pestaña para buscar un auto específico
    GtkWidget *page_buscar = create_notebook_page(notebook, "Buscar");
    GtkWidget *entry_buscar = create_entry();
    GtkWidget *button_buscar = create_button("Buscar");
    GtkWidget *text_view_buscar = create_text_view();
    gtk_box_pack_start(GTK_BOX(page_buscar), entry_buscar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_buscar), button_buscar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_buscar), text_view_buscar, TRUE, TRUE, 0);

    // Crear los widgets necesarios para la inserción de automóviles
    InsertWidgets insert_widgets;
    insert_widgets.entry_autoID = create_entry();
    insert_widgets.entry_marca = create_entry();
    insert_widgets.entry_modelo = create_entry();
    insert_widgets.entry_anio = create_entry();
    insert_widgets.entry_color = create_entry();
    insert_widgets.entry_precio = create_entry();

    // Agregar la tercera pestaña para insertar un auto
    create_insert_page(notebook, &insert_widgets);

    // Crear los widgets necesarios para la update de automóviles
    InsertWidgets update_widgets;
    update_widgets.entry_autoID = create_entry();
    update_widgets.entry_marca = create_entry();
    update_widgets.entry_modelo = create_entry();
    update_widgets.entry_anio = create_entry();
    update_widgets.entry_color = create_entry();
    update_widgets.entry_precio = create_entry();

    // Agregar la cuarta pestaña para insertar un auto
    create_update_page(notebook, &update_widgets);

    // Crear la quinta pestaña para eliminar un carro especifico
    GtkWidget *page_eliminar = create_notebook_page(notebook, "Eliminar");
    GtkWidget *entry_eliminar = create_entry();
    GtkWidget *button_eliminar = create_button("ELiminar");
    gtk_box_pack_start(GTK_BOX(page_eliminar), entry_eliminar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_eliminar), button_eliminar, FALSE, FALSE, 0);

    // Conectar señales de los botones
    g_signal_connect(button_select_todos, "clicked", G_CALLBACK(on_select_todos_clicked), text_view_select_todos);
    // Conectar señal de click del botón de búsqueda
    BuscarWidgets *buscar_widgets = g_new(BuscarWidgets, 1);
    buscar_widgets->entry = entry_buscar;
    buscar_widgets->text_view = text_view_buscar;
    g_signal_connect(button_buscar, "clicked", G_CALLBACK(on_buscar_clicked), buscar_widgets);

   // Conectar señal de click del botón de eliminar
    GtkWidget *entry;
    entry = entry_eliminar;
    g_signal_connect(button_eliminar, "clicked", G_CALLBACK(clientDelete_AgenciaAutos), entry);

    // Conectar la señal "switch-page" del GtkNotebook a la función de devolución de llamada
    g_signal_connect(notebook, "switch-page", G_CALLBACK(on_notebook_switch_page), text_view_select_todos);
    g_signal_connect(notebook, "switch-page", G_CALLBACK(on_notebook_switch_page), text_view_buscar);

    // Mostrar todo
    gtk_widget_show_all(window);

    // Iniciar el bucle principal de GTK
    gtk_main();

    return 0;
}

// Función de callback para el botón "Seleccionar todos"
void on_select_todos_clicked(GtkButton *button, GtkWidget *text_view) {
    // Lógica para llamar al servicio "SELECT_TODOS_AgenciaAutos"
    int ivL_resLlamd;
    long lvL_tamLongt;
    float fvL_recValor;
    FBFR32 *fbfr;
    FBFR32 *recv;
    FLDLEN32 flen;
    char msgbuf[64];
    Autos *autosRegis;
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
    char text[10000] = ""; // Almacenar todos los resultados en una cadena de texto
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

        sprintf(text, "%sID carro : %d\nNombre de la marca : %s\nModelo: %s\nAño del automóvil: %s\nColor del automóvil: %s\nPrecio del automóvil: %.2lf\n\n",
                text, autosRegis[ivl_iterador].autoID, autosRegis[ivl_iterador].marca, autosRegis[ivl_iterador].modelo,
                autosRegis[ivl_iterador].anio, autosRegis[ivl_iterador].color, autosRegis[ivl_iterador].precio);
    }

    // Obtener el buffer de texto del text_view
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    // Limpiar el buffer de texto antes de agregar nuevos resultados
    gtk_text_buffer_set_text(buffer, "", -1);

    // Actualizar el área de texto con los resultados obtenidos
    gtk_text_buffer_set_text(buffer, text, -1);

    // Liberar memoria y desconectar de la aplicación Tuxedo
    printf("Liberamos Buffer y desconectamos de la aplicacion\n");
    free(autosRegis);
    tpfree((char *)fbfr);
    tpfree((char *)recv);
    tpterm();
}

// Función de callback para el botón "Buscar"
void on_buscar_clicked(GtkButton *button, BuscarWidgets *widgets) {
    // Obtener el texto ingresado en el cuadro de entrada
    const char *entry_text = gtk_entry_get_text(GTK_ENTRY(widgets->entry));
    int id_auto = atoi(entry_text);

    // Lógica para llamar al servicio "SELECT_buscar_AgenciaAutos"
    int ivL_resLlamd;
    long lvL_tamLongt;
    float fvL_recValor;
    FBFR32 *fbfr;
    FBFR32 *recv;
    FLDLEN32 flen;
    char msgbuf[64];
    Autos *autosRegis;
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

    /* Manejo del Buffer FML */
    if (Fadd32(fbfr, AUTOID, (char *)&id_auto, 0) < 0) {
        printf("\n\tError insertando campo FML (AUTOID)");
        tpfree((char *)fbfr);
        tpterm();
        return;
    }

    // Invocamos el servicio
    printf("Llamada al servicio 'SELECT_BUSCAR_AgenciaAutos'\n");
    if (tpcall("SELECT_BUSCAR_AgenciaAutos", (char *)fbfr, 0, (char **)&recv, &lvL_tamLongt, 0L) == -1) {
        printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
        tpfree((char *)fbfr);
        tpfree((char *)recv);
        tpterm();
        return;
    }

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
    printf("Respuesta del servidor para EL autoID: %d\n", id_auto);
    printf("***************************************************\n");
    char text[10000] = ""; // Almacenar todos los resultados en una cadena de texto
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
        printf("COlor del automovil : %s\n", autosRegis[ivl_iterador].color);

        Fget32(recv, PRECIO, ivl_iterador, (char *)&autosRegis[ivl_iterador].precio, 0);
        printf("Precio del automovil : %lf\n", autosRegis[ivl_iterador].precio);

        sprintf(text, "%sID carro : %d\nNombre de la marca : %s\nModelo: %s\nAño del automóvil: %s\nColor del automóvil: %s\nPrecio del automóvil: %.2lf\n\n",
                text, autosRegis[ivl_iterador].autoID, autosRegis[ivl_iterador].marca, autosRegis[ivl_iterador].modelo,
                autosRegis[ivl_iterador].anio, autosRegis[ivl_iterador].color, autosRegis[ivl_iterador].precio);
    }

    // Obtener el buffer de texto del text_view
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widgets->text_view));

    // Limpiar el buffer de texto antes de agregar nuevos resultados
    gtk_text_buffer_set_text(buffer, "", -1);

    // Actualizar el área de texto con los resultados obtenidos
    gtk_text_buffer_set_text(buffer, text, -1);

    // Liberamos el buffer y desconectamos de la aplicacion
    printf("Liberamos Buffer y desconectamos de la aplicacion\n");
    tpfree((char *)fbfr);
    tpfree((char *)recv);
    tpterm();
}

// Función para realizar la inserción de un automóvil en la base de datos
int clientInsert_AgenciaAutos(GtkWidget *entry_autoID, GtkWidget *entry_marca, GtkWidget *entry_modelo, GtkWidget *entry_anio,
GtkWidget *entry_color, GtkWidget *entry_precio) {
    int ivL_resLlamd;
    long lvL_tamLongt;
    float fvL_recValor;
    FBFR32 *fbfr;
    FBFR32 *recv;
    FLDLEN32 flen;
    char msgbuf[64];

    // Estructura para almacenar los datos del automóvil
    Autos carro;

    // Obtener los valores ingresados en los widgets
    carro.autoID = atoi(gtk_entry_get_text(GTK_ENTRY(entry_autoID)));
    strcpy(carro.marca, gtk_entry_get_text(GTK_ENTRY(entry_marca)));
    strcpy(carro.modelo, gtk_entry_get_text(GTK_ENTRY(entry_modelo)));
    strcpy(carro.anio, gtk_entry_get_text(GTK_ENTRY(entry_anio)));
    strcpy(carro.color, gtk_entry_get_text(GTK_ENTRY(entry_color)));
    carro.precio = atof(gtk_entry_get_text(GTK_ENTRY(entry_precio)));

    // Conectamos con la aplicación Tuxedo Server
    printf("Conectamos con la aplicacion\n");
    if (tpinit((TPINIT *)NULL) == -1) {
        printf("Error en la conexion, tperrno = %d \n", tperrno);
        return (1);
    }

    // Reservamos espacio para el buffer FML
    printf("Reservamos Espacio para los buffers FML\n");
    if ((fbfr = (FBFR32 *)tpalloc("FML32", NULL, 1024)) == NULL) {
        printf("Error Reservando espacio para Buffer fbfr\n");
        tpterm();
        return (1);
    }
    if ((recv = (FBFR32 *)tpalloc("FML32", NULL, 1024)) == NULL) {
        printf("Error Reservando espacio para Buffer recv\n");
        tpterm();
        return (1);
    }

    /* Manejo del Buffer FML */
    printf("\nInsertamos datos en buffer FML.");
    if (Fadd32(fbfr, AUTOID, (char *)&carro.autoID, 0) < 0) {
        printf("\n\tError insertando campo FML (AUTOID)");
        tpfree((char *)fbfr);
        tpterm();
        return (0);
    }
    if (Fadd32(fbfr, MARCA, (char *)&carro.marca, 0) < 0) {
        printf("\n\tError insertando campo FML (MARCA)");
        tpfree((char *)fbfr);
        tpterm();
        return (0);
    }
    if (Fadd32(fbfr, MODELO, (char *)&carro.modelo, 0) < 0) {
        printf("\n\tError insertando campo FML (MODELO)");
        tpfree((char *)fbfr);
        tpterm();
        return (0);
    }
    if (Fadd32(fbfr, ANIO, (char *)&carro.anio, 0) < 0) {
        printf("\n\tError insertando campo FML (ANIO)");
        tpfree((char *)fbfr);
        tpterm();
        return (0);
    }
    if (Fadd32(fbfr, COLOR, (char *)&carro.color, 0) < 0) {
        printf("\n\tError insertando campo FML (COLOR)");
        tpfree((char *)fbfr);
        tpterm();
        return (0);
    }
    if (Fadd32(fbfr, PRECIO, (char *)&carro.precio, 0) < 0) {
        printf("\n\tError insertando campo FML (PRECIO)");
        tpfree((char *)fbfr);
        tpterm();
        return (0);
    }

    // Invocamos el servicio
    printf("Llamada al servicio 'INSERT_AgenciaAutos'\n");
    if (tpcall("INSERT_AgenciaAutos", (char *)fbfr, 0, (char **)&recv, &lvL_tamLongt, 0L) == -1) {
        printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
        tpfree((char *)fbfr);
        tpfree((char *)recv);
        tpterm();
        return (1);
    }
    flen = sizeof(msgbuf);
    Fget32(recv, OUTPUT, 0, (char *)msgbuf, &flen);
    printf("Respuesta del servidor: %s\n", msgbuf);

    // Liberamos el buffer y desconectamos de la aplicación
    printf("Liberamos Buffer y desconectamos de la aplicacion\n");
    tpfree((char *)fbfr);
    tpfree((char *)recv);
    tpterm();
    return 0;
}


int clientUpdate_AgenciaAutos(GtkWidget *entry_autoID, GtkWidget *entry_marca, GtkWidget *entry_modelo, GtkWidget *entry_anio,
GtkWidget *entry_color, GtkWidget *entry_precio){
   int ivL_resLlamd;
   long lvL_tamLongt;
   float fvL_recValor;
   FBFR32 *fbfr;
   FBFR32 *recv;
   FLDLEN32 flen;
   char msgbuf[64];
 
   // Estructura para almacenar los datos del automóvil
   Autos carro;

   // Obtener los valores ingresados en los widgets
   carro.autoID = atoi(gtk_entry_get_text(GTK_ENTRY(entry_autoID)));
   strcpy(carro.marca, gtk_entry_get_text(GTK_ENTRY(entry_marca)));
   strcpy(carro.modelo, gtk_entry_get_text(GTK_ENTRY(entry_modelo)));
   strcpy(carro.anio, gtk_entry_get_text(GTK_ENTRY(entry_anio)));
   strcpy(carro.color, gtk_entry_get_text(GTK_ENTRY(entry_color)));
   carro.precio = atof(gtk_entry_get_text(GTK_ENTRY(entry_precio)));


   /* Conectamos con la aplicacion Tuxedo Server */
   printf ("Conectamos con la aplicacion\n") ;
   if (tpinit((TPINIT *) NULL) == -1){
      printf("Error en la conexion, tperrno = %d \n", tperrno);
      return (1) ;
   }
   // Reservamos espacio para el buffer FML
   printf ("Reservamos Espacio para los buffers FML\n");
   if ((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
      printf("Error Reservando espacio para Buffer fbfr\n");
      tpterm();
      return(1);
   }
   if ((recv = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
      printf("Error Reservando espacio para Buffer recv\n");
      tpterm();
      return(1);
   }
   /* Manejo del Buffer FML */
   printf ("\nInsertamos datos en buffer FML.");
   if(Fadd32 (fbfr, AUTOID, (char *)&carro.autoID, 0) < 0) {
      printf ("\n\tError insertando campo FML (AUTOID)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, MARCA, (char *)&carro.marca, 0) < 0) {
      printf ("\n\tError insertando campo FML (MARCA)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, MODELO, (char *)&carro.modelo, 0) < 0) {
      printf ("\n\tError insertando campo FML (MODELO)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, ANIO, (char *)&carro.anio, 0) < 0) {
      printf ("\n\tError insertando campo FML (ANIO)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, COLOR, (char *)&carro.color, 0) < 0) {
      printf ("\n\tError insertando campo FML (COLOR)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, PRECIO, (char *)&carro.precio, 0) < 0) {
      printf ("\n\tError insertando campo FML (PRECIO)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }

   //Invocamos el servicio
   printf("Llamada al servicio 'UPDATE_AgenciaAutos'\n");
   if (tpcall("UPDATE_AgenciaAutos", (char *)fbfr, 0, (char **)&recv, &lvL_tamLongt, 0L) == -1){
       printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
       tpfree((char *)fbfr);
       tpfree((char *)recv);
       tpterm();
       return (1);
   }
   flen = sizeof(msgbuf);
   Fget32(recv, OUTPUT, 0, (char *)msgbuf, &flen);
   printf("Respuesta del servidor: %s\n", msgbuf);
   
   // Liberamos el buffer y desconectamos de la aplicacion
   printf("Liberamos Buffer y desconectamos de la aplicacion\n");
   tpfree((char *)fbfr);
   tpfree((char *)recv);
   tpterm();
   return 0;
}

int clientDelete_AgenciaAutos(GtkButton *button, GtkWidget *entry){
   // Obtener el texto ingresado en el cuadro de entrada
    const char *entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
    int id_auto = atoi(entry_text);

   int ivL_resLlamd;
   long lvL_tamLongt;
   float fvL_recValor;
   FBFR32 *fbfr;
   FBFR32 *recv;
   FLDLEN32 flen;
   char msgbuf[64];

   /* Conectamos con la aplicacion Tuxedo Server */
   printf ("Conectamos con la aplicacion\n") ;
   if (tpinit((TPINIT *) NULL) == -1){
      printf("Error en la conexion, tperrno = %d \n", tperrno);
      return (1) ;
   }
   // Reservamos espacio para el buffer FML
   printf ("Reservamos Espacio para los buffers FML\n");
   if ((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
      printf("Error Reservando espacio para Buffer fbfr\n");
      tpterm();
      return(1);
   }
   if ((recv = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
      printf("Error Reservando espacio para Buffer recv\n");
      tpterm();
      return(1);
   }
   /* Manejo del Buffer FML */
    if (Fadd32(fbfr, AUTOID, (char *)&id_auto, 0) < 0) {
        printf("\n\tError insertando campo FML (AUTOID)");
        tpfree((char *)fbfr);
        tpterm();
        return;
    }
   
   //Invocamos el servicio
   printf("Llamada al servicio 'DELETE_AgenciaAutos'\n");
   if (tpcall("DELETE_AgenciaAutos", (char *)fbfr, 0, (char **)&recv, &lvL_tamLongt, 0L) == -1){
       printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
       tpfree((char *)fbfr);
       tpfree((char *)recv);
       tpterm();
       return (1);
   }
   flen = sizeof(msgbuf);
   Fget32(recv, OUTPUT, 0, (char *)msgbuf, &flen);
   printf("Respuesta del servidor: %s\n", msgbuf);
   
   // Liberamos el buffer y desconectamos de la aplicacion
   printf("Liberamos Buffer y desconectamos de la aplicacion\n");
   tpfree((char *)fbfr);
   tpfree((char *)recv);
   tpterm();
   return 0;
}
