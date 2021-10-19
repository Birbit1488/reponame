#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    unsigned char is_valid: 1;
    unsigned char referenced: 1;
    uint8_t counter;
    size_t page_index;
} page_frame_t;

size_t page_frame_count;
page_frame_t *page_frames;


void reference_page_frame(size_t frame_index) {page_frames[frame_index].referenced = 1;}

void reset_page_frame(size_t index) {page_frame_t *frame_ptr = page_frames + index; frame_ptr->is_valid = 0;}

void initialize_page_table() {
    page_frames = (page_frame_t *) calloc(sizeof(page_frame_t), page_frame_count);
    for (size_t i = 0; i < page_frame_count; i++) {reset_page_frame(i);}
}

void free_page_table() {free(page_frames);}

int is_in_page_table(size_t page_index, size_t *frame_index) {
    for (size_t i = 0; i < page_frame_count; i++) {
        page_frame_t *frame_ptr = page_frames + i;
        if (frame_ptr->is_valid && frame_ptr->page_index == page_index) {
            *frame_index = i;
            return 1;
        }
    }
    return 0;
}

int exists_empty_frame(size_t *empty_frame_index) {
    for (size_t i = 0; i < page_frame_count; i++) {
        if (!page_frames[i].is_valid) {
            *empty_frame_index = i;
            return 1;
        }
    }
    return 0;
}

void load_page_to_frame(size_t page_index, size_t frame_index) {
    page_frame_t *frame_ptr = page_frames + frame_index;
    frame_ptr->is_valid = 1;
    frame_ptr->page_index = page_index;
    frame_ptr->referenced = 0;
    frame_ptr->counter = 0;
}

size_t unload_not_frequently_used_frame() {
    uint8_t min_counter = page_frames[0].counter;
    size_t min_counter_index = 0;
    for (size_t i = 1; i < page_frame_count; i++) {
        page_frame_t *frame_ptr = page_frames + i;
        if (frame_ptr->is_valid && frame_ptr->counter < min_counter) {
            min_counter = frame_ptr->counter;
            min_counter_index = i;
        }
    }
    reset_page_frame(min_counter_index);
    return min_counter_index;
}


void access_page(size_t page_index, size_t *hits_ptr, size_t *misses_ptr) {
    size_t frame_index;
    if (is_in_page_table(page_index, &frame_index)) {(*hits_ptr)++;}
    else {
        (*misses_ptr)++;
        if (!exists_empty_frame(&frame_index)) {frame_index = unload_not_frequently_used_frame();}
        load_page_to_frame(page_index, frame_index);
    }
    reference_page_frame(frame_index);
}

void age() {
    for (size_t i = 0; i < page_frame_count; i++) {
        page_frame_t *frame_ptr = page_frames + i;
        if (frame_ptr->is_valid) {
            frame_ptr->counter >>= 1;
            size_t shift_amount = sizeof(frame_ptr->counter) * (8 -1);
            frame_ptr->counter += frame_ptr->referenced * shift_amount;
            frame_ptr->referenced = 0;
        }
    }
}

int main(int argc, char **argv) {
    sscanf(argv[1], "%lu", &page_frame_count);
    initialize_page_table();
    FILE *file = fopen("Lab 9 input.txt", "r");
    if (file == NULL) {
        printf("File '%s' does not exist.\n", "Lab 9 input.txt");
        free_page_table();
        return -1;
    }
    size_t page_index, hits = 0, misses = 0;
    while (fscanf(file, "%lu", &page_index) != EOF) {
        access_page(page_index, &hits, &misses);
        age();
    }
    printf("%lu hits/%lu misses. Hit ratio is %f.\n", hits, misses, (float) hits / (float) (hits + misses));
    free_page_table();
    fclose(file);
    return 0;
}