#ifndef INTERFACE_H
#define INTERFACE_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include "emprestimo.h"

// Estrutura para armazenar o saldo e informações de empréstimo
struct AppData {
    float saldo;          // Saldo do usuário
    struct Emprestimo emp; // Dados do empréstimo
    GtkWidget *window_main; // Janela principal
};

// Função callback para o botão de empréstimo
void on_emprestimo_button_clicked(GtkWidget *widget, gpointer data);

// Função para calcular o empréstimo
void on_calcular_button_clicked(GtkWidget *widget, gpointer user_data);

// Função para exibir a mensagem de sucesso
// Função para exibir a mensagem de sucesso
void exibir_mensagem_sucesso(GtkWidget *parent) {
    GtkWidget *window;

    // Garante que o parent seja uma janela
    if (GTK_IS_WINDOW(parent)) {
        window = parent; // Se o parent já for uma janela, usa ele
    } else {
        window = gtk_widget_get_toplevel(parent); // Tenta pegar a janela pai
        if (!GTK_IS_WINDOW(window)) {
            window = NULL; // Se não for uma janela válida, seta como NULL
        }
    }

    // Cria a caixa de diálogo com o parent correto
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "Relatório gerado com sucesso!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


// Função que cria a interface do menu principal
void criar_interface(GtkApplication *app) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label_saldo;
    GtkWidget *button_emprestimo;
    struct AppData *app_data = g_new(struct AppData, 1); // Aloca memória para AppData

    // Inicializa o saldo
    app_data->saldo = 1000.00; // Exemplo de saldo inicial

    // Cria a janela principal
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Simulador de Empréstimo");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    app_data->window_main = window; // Armazena a janela principal

    // Cria um grid para organizar os widgets
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Cria o label para mostrar o saldo
    char saldo_text[50];
    snprintf(saldo_text, sizeof(saldo_text), "Saldo: R$%.2f", app_data->saldo);
    label_saldo = gtk_label_new(saldo_text);
    gtk_grid_attach(GTK_GRID(grid), label_saldo, 0, 0, 2, 1);

    // Cria o botão para acessar o empréstimo
    button_emprestimo = gtk_button_new_with_label("Empréstimo");
    gtk_grid_attach(GTK_GRID(grid), button_emprestimo, 0, 1, 2, 1);

    // Conecta o botão à função callback
    g_signal_connect(button_emprestimo, "clicked", G_CALLBACK(on_emprestimo_button_clicked), app_data);

    // Exibe todos os widgets
    gtk_widget_show_all(window);
}

// Função que cria a janela de empréstimo
void criar_janela_emprestimo(struct AppData *app_data) {
    GtkWidget *dialog;
    GtkWidget *grid;
    GtkWidget *label_valor, *label_meses;
    GtkWidget *entry_valor, *entry_meses;
    GtkWidget *button_calcular;
    GtkWidget *label_resultado;

    // Cria a janela de diálogo
    dialog = gtk_dialog_new_with_buttons("Empréstimo", GTK_WINDOW(app_data->window_main),
                                         GTK_DIALOG_MODAL, "_Fechar", GTK_RESPONSE_CLOSE, NULL);

    // Cria um grid para organizar os widgets
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), grid);

    // Cria os labels e as entradas de texto
    label_valor = gtk_label_new("Valor do Empréstimo (R$):");
    label_meses = gtk_label_new("Tempo de Pagamento (meses):");
    entry_valor = gtk_entry_new();
    entry_meses = gtk_entry_new();

    // Verifica se os widgets foram criados corretamente
    if (!label_valor || !label_meses || !entry_valor || !entry_meses) {
        g_print("Erro ao criar widgets de entrada.\n");
        return;
    }

    // Adiciona os labels e entradas ao grid
    gtk_grid_attach(GTK_GRID(grid), label_valor, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_valor, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_meses, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_meses, 1, 1, 1, 1);

    // Cria o botão para calcular o empréstimo
    button_calcular = gtk_button_new_with_label("Calcular");
    gtk_grid_attach(GTK_GRID(grid), button_calcular, 0, 2, 2, 1);

    // Label para mostrar o resultado
    label_resultado = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), label_resultado, 0, 3, 2, 1);

    // Verifica se o label de resultado foi criado corretamente
    if (!label_resultado) {
        g_print("Erro ao criar o label de resultado.\n");
        return;
    }

    // Cria um array de ponteiros para passar para a callback de cálculo
    GtkWidget **entries = g_new(GtkWidget *, 3);
    entries[0] = entry_valor;
    entries[1] = entry_meses;
    entries[2] = label_resultado;

    // Verificação adicional para garantir que os ponteiros não sejam nulos
    if (!entries[0] || !entries[1] || !entries[2]) {
        g_print("Erro: Entradas nulas detectadas.\n");
        return;
    }

    // Conecta o botão calcular com a função de cálculo
    g_signal_connect(button_calcular, "clicked", G_CALLBACK(on_calcular_button_clicked), entries);

    // Exibe todos os widgets da janela de diálogo
    gtk_widget_show_all(dialog);
}

// Função callback para o botão de empréstimo
void on_emprestimo_button_clicked(GtkWidget *widget, gpointer data) {
    struct AppData *app_data = (struct AppData *)data;
    criar_janela_emprestimo(app_data);
}

// Função para calcular o empréstimo
void on_calcular_button_clicked(GtkWidget *widget, gpointer user_data) {
    GtkWidget **entries = (GtkWidget **)user_data;

    // Verifica se as entradas e label estão corretamente inicializados
    if (!entries[0] || !entries[1] || !entries[2]) {
        g_print("Erro: Ponteiros nulos para os widgets.\n");
        return;
    }

    const char *valor_emprestimo_str = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const char *tempo_emprestimo_str = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    GtkLabel *label_resultado = GTK_LABEL(entries[2]);

    // Verifica se as entradas são válidas
    if (valor_emprestimo_str == NULL || tempo_emprestimo_str == NULL) {
        gtk_label_set_text(label_resultado, "Erro: Entradas inválidas.");
        return;
    }

    struct Emprestimo emp;
    
    // Converte os dados das entradas
    emp.valor_emprestimo = atof(valor_emprestimo_str);
    emp.tempo_emprestimo = atoi(tempo_emprestimo_str);

    // Verifica se os valores são válidos
    if (emp.valor_emprestimo <= 0 || emp.tempo_emprestimo <= 0) {
        gtk_label_set_text(label_resultado, "Valores inválidos!");
        return;
    }

    // Calcula a parcela e os juros totais
    emp.valor_parcela = calcular_parcela(&emp);
    emp.juros_totais = (emp.valor_parcela * emp.tempo_emprestimo) - emp.valor_emprestimo;

    // Gera o relatório no arquivo
    FILE *file = fopen("RELATORIO_DE_EMPRESTIMO.txt", "w");
    if (file == NULL) {
        gtk_label_set_text(label_resultado, "Erro ao abrir o arquivo!");
        return;
    }
    fprintf(file, "VALOR DO EMPRÉSTIMO: R$%.2f\n", emp.valor_emprestimo);
    fprintf(file, "PERÍODO DE PAGAMENTO: %d meses\n", emp.tempo_emprestimo);
    fprintf(file, "PARCELAS DO EMPRÉSTIMO: R$%.2f\n", emp.valor_parcela);
    fprintf(file, "JUROS TOTAIS DO EMPRÉSTIMO: R$%.2f\n", emp.juros_totais);
    fclose(file);

    // Exibe a mensagem de sucesso
    exibir_mensagem_sucesso(widget);

    // Fecha a janela de empréstimo
    GtkWidget *dialog = gtk_widget_get_toplevel(widget);
    gtk_widget_destroy(dialog);
}

#endif
