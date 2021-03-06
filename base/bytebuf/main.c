#include "bytebuffer.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
    bytebuffer_t bb;

    bb_init_str(&bb, "12345678");
    bb_print(bb);
    printf("size: %zu\n", bb_get_size(bb));
    printf("%u\n", bb_get_bytes(bb)[0]);
    printf("pos: %zu\n", bb.pos);
    printf("byte: %u\n", bb_get(&bb));
    printf("pos: %zu\n", bb.pos);
    bb_reset(&bb);
    printf("pos: %zu\n", bb.pos);
    printf("byte: %u\n", bb_get_at(bb, 1));
    printf("short: %u\n", bb_get_short(&bb));
    printf("short at: %u\n", bb_get_short_at(bb, 1));
    bb_reset(&bb);
    printf("int: %u\n", bb_get_int(&bb));
    printf("int at: %u\n", bb_get_int_at(bb, 0));
    bb_reset(&bb);
    printf("float: %f\n", bb_get_float(&bb));
    printf("float at: %f\n", bb_get_float_at(bb, 0));
    bb_destroy(&bb);

    printf("\n");
    bb_init_str_order(&bb, "12345678", BB_BIG_ENDIAN);
    bb_print(bb);
    printf("size: %zu\n", bb_get_size(bb));
    printf("%u\n", bb_get_bytes(bb)[0]);
    printf("pos: %zu\n", bb.pos);
    printf("byte: %u\n", bb_get(&bb));
    printf("pos: %zu\n", bb.pos);
    bb_reset(&bb);
    printf("pos: %zu\n", bb.pos);
    printf("byte: %u\n", bb_get_at(bb, 1));
    printf("short: %u\n", bb_get_short(&bb));
    printf("short at: %u\n", bb_get_short_at(bb, 1));
    bb_reset(&bb);
    printf("int: %u\n", bb_get_int(&bb));
    printf("int at: %u\n", bb_get_int_at(bb, 0));
    bb_reset(&bb);
    printf("float: %f\n", bb_get_float(&bb));
    printf("float at: %f\n", bb_get_float_at(bb, 0));
    bb_destroy(&bb);

    bb_init(&bb, 9);
    //bb_init_order(&bb, 8, BB_BIG_ENDIAN);
    bb_put(&bb, 33);
    bb_print(bb);
    bb_put_at(&bb, 0, 22);
    bb_print(bb);
    bb_put_short(&bb, 129);
    bb_print(bb);
    bb_put_short_at(&bb, 0, 133);
    bb_print(bb);
    bb_put_int(&bb, 70123);
    bb_print(bb);
    printf("int at: %u\n", bb_get_int_at(bb, 3));
    bb_put_int_at(&bb, 2, 70123);
    bb_print(bb);
    printf("int at: %u\n", bb_get_int_at(bb, 2));
    bb_reset(&bb);
    bb_put_float(&bb, 82.56f);
    bb_print(bb);
    printf("float at: %f\n", bb_get_float_at(bb, 0));
    bb_put_float_at(&bb, 2, 33.56f);
    bb_print(bb);
    printf("float at: %f\n", bb_get_float_at(bb, 2));
    bb_reset(&bb);
    bb_put_long(&bb, 12345678ULL);
    bb_print(bb);
    bb_put_long_at(&bb, 0, 12345678ULL);
    bb_print(bb);
    bb_reset(&bb);
    printf("long: %lu\n", bb_get_long(&bb));
    printf("long at: %lu\n", bb_get_long_at(bb, 0));
    bb_reset(&bb);
    bb_put_double(&bb, 125.12563);
    bb_print(bb);
    bb_put_double_at(&bb, 0, 125.12563);
    bb_reset(&bb);
    printf("double: %f\n", bb_get_double(&bb));

    printf("double at: %f\n\n", bb_get_double_at(bb, 0));
    bb_print(bb);
    bb_destroy(&bb);

    bb_init(&bb, 8);
    bb_put_string_at(&bb, 2, "Kaixop", 6);
    bb_print(bb);

    char *str = bb_get_string_at(bb, 2, 6);
    printf("Get string: [%s]\n", str);
    free(str);

    char *hex_string = bb_get_hex_string(bb);
    printf("Get hex string: [%s]\n", hex_string);
    free(hex_string);

    bytebuffer_t cloned;
    bb_clone(bb, &cloned);
    hex_string = bb_get_hex_string(cloned);
    printf("Get cloned hex string: [%s]\n", hex_string);
    free(hex_string);
    bb_print(cloned);

    bb_destroy(&bb);
    bb_destroy(&cloned);

    return 0;
}