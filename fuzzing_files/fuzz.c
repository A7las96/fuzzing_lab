#include "xlsxwriter.h"
#include <stdint.h>
#include <stdio.h>

// Точка входа для фаззинга
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Читаем путь к входному файлу
    const char *input_file = argv[1];

    // Пытаемся открыть файл как Excel с libxlsxwriter
    lxw_workbook *workbook = workbook_new("fuzz_output.xlsx");
    if (!workbook) {
        fprintf(stderr, "Failed to create workbook.\n");
        return 0; // Если не удалось создать файл, выходим
    }

    // Создаём лист
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);
    if (!worksheet) {
        fprintf(stderr, "Failed to add worksheet.\n");
        workbook_close(workbook);
        return 0; // Если не удалось создать лист, выходим
    }

    // Читаем входной файл
    FILE *file = fopen(input_file, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open input file: %s\n", input_file);
        workbook_close(workbook);
        return 0;
    }

    // Читаем содержимое файла
    uint8_t buffer[1024];
    size_t read_size = fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    // Пишем первые 1024 байта входного файла в первую строку Excel
    if (read_size > 0) {
        worksheet_write_string(worksheet, 0, 0, (char *)buffer, NULL);
    }

    // Закрываем Excel-файл
    workbook_close(workbook);

    return 0;
}
