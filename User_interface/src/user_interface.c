#include "user_interface.h"
#include <gtk.h>
#include <stdlib.h>
#include <string.h>

GtkWidget *window_main;

static void __init(void);

int display(int argc, char **argv){
	gtk_init(&argc, &argv);

	GtkApplication *app;
	int status;
	app = gtk_application_new("com.github.husixu1.asm-sim",G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app,"activate",G_CALLBACK(__init),NULL);
	status	=	g_application_run(G_APPLICATION(app),argc,argv);
	g_object_unref(app);

	return status;
}

static void __init(void)
{
	GtkBuilder	*builder_builder	=	gtk_builder_new();

	gtk_builder_add_from_file(builder_builder,"uis/builder.ui",NULL);
	gtk_builder_connect_signals(builder_builder,NULL);

	window_main	=	GTK_WIDGET(gtk_builder_get_object(builder_builder,"window_main"));

	g_object_unref(G_OBJECT(builder_builder));
	gtk_widget_show(window_main);

	gtk_main();
}

/* call the assembler */
G_MODULE_EXPORT void on_button_assembler_released(void){
	GtkBuilder *builder_builder	=	gtk_builder_new();
	gtk_builder_add_from_file(builder_builder,"uis/builder.ui",NULL);
	gtk_builder_connect_signals(builder_builder,NULL);

	GtkDialog *file_chooser_dialog	=	GTK_DIALOG(gtk_builder_get_object(builder_builder, "filechooserdialog_open"));
	/* decide which file to open */
	if(gtk_dialog_run(file_chooser_dialog)==1){
		char filename[MAX_FILENAME_LEN];
		strncpy(filename, gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser_dialog)), MAX_FILENAME_LEN);

        /* run the assembler */

	}
	return;
}
