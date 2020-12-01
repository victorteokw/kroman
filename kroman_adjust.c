#include "kroman_adjust.h"
#include "kroman_process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <stdbool.h>

#define KROMAN_GA 0xac00
#define KROMAN_HIH 0xd7a3
#define KROMAN_HEAD_INTERVAL 588
#define KROMAN_BODY_INTERVAL 28
#define KROMAN_TAIL_INTERVAL 1

void kroman_adjust(wchar_t *char1, wchar_t *char2) {
    int char_int1 = (int)*char1, char_int2 = (int)*char2;

    if (((char_int1 >= KROMAN_GA) && (char_int1 <= KROMAN_HIH)) && (char_int2 >= KROMAN_GA) && (char_int2 <= KROMAN_HIH)) {
        int tail_index1 = ((char_int1 - KROMAN_GA) % KROMAN_HEAD_INTERVAL) % KROMAN_BODY_INTERVAL;
        int head_index2 = (char_int2 - KROMAN_GA) / KROMAN_HEAD_INTERVAL;
        int head_lefto2 = (char_int2 - KROMAN_GA) % KROMAN_HEAD_INTERVAL;
        int body_index2 = head_lefto2 / KROMAN_BODY_INTERVAL;
        int tail_index2 = head_lefto2 % KROMAN_BODY_INTERVAL;

        int tmp = head_index2;

        if(tail_index1 == 1 || tail_index1 == 7 || tail_index1 == 17) {
            switch(head_index2) {
                case 0:
                    head_index2 = 1;
                    break;
                case 3:
                    head_index2 = 4;
                    break;
                case 7:
                    head_index2 = 8;
                    break;
                case 9:
                    head_index2 = 10;
                    break;
                case 12:
                    head_index2 = 13;
                    break;
            }
        }
        
        if(tmp != head_index2) {
            *char2 = (wchar_t)((head_index2 * KROMAN_HEAD_INTERVAL) + (body_index2 * KROMAN_BODY_INTERVAL)
                    + (tail_index2 * KROMAN_TAIL_INTERVAL) + KROMAN_GA);
        }
    }
}