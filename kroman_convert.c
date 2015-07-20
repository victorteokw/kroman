#include "kroman_convert.h"
#include <stdlib.h>
#include <string.h>
#define KROMAN_GA 0xac00
#define KROMAN_HIH 0xd7a3
#define KROMAN_HEAD_INTERVAL 588
#define KROMAN_BODY_INTERVAL 28
#define KROMAN_TAIL_INTERVAL 1
/* 
 * Referenced from
 * http://www.programminginkorean.com/programming/hangul-in-unicode
 * http://www.programminginkorean.com/programming/hangul-in-unicode/hangul-syllables-uac00-ud7a3/
 * Many thanks!
 * 
 * heads interval 588, total 19
 * g gg n d dd r m b bb s ss ng(0) j jj c k t p h
 * bodies interval 28, total 21
 * a ae ya yae eo e yeo ye o wa wae oe yo u weo we wi yu eu eui i
 * tails interval 1, total 28
 * 0 g gg gs n nj nh d r rk rm rb rs rt rp rh m b bs s ss ng j c k t p h
 *
 * starts at U+AC00, ends at U+D7A3
 */

void kroman_head_from_index(int, char *);
void kroman_body_from_index(int, char *);
void kroman_tail_from_index(int, char *);

void kroman_convert(wchar_t character, char *retstring, bool *is_hangul) {
  int char_int = (int)character;
  // If it is hangul
  if ((char_int >= KROMAN_GA) && (char_int <= KROMAN_HIH)) {
    int head_index = (char_int - KROMAN_GA) / KROMAN_HEAD_INTERVAL;
    int head_lefto = (char_int - KROMAN_GA) % KROMAN_HEAD_INTERVAL;
    int body_index = head_lefto / KROMAN_BODY_INTERVAL;
    int tail_index = head_lefto % KROMAN_BODY_INTERVAL;
    char head_string[10];
    kroman_head_from_index(head_index, head_string);
    char body_string[10];
    kroman_body_from_index(body_index, body_string);
    char tail_string[10];
    kroman_tail_from_index(tail_index, tail_string);
    strcat(retstring, head_string);
    strcat(retstring, body_string);
    strcat(retstring, tail_string);
    *is_hangul = true;
  } else { // else normal wide char
    wchar_t wchar_string[2];
    wchar_string[0] = character;
    wchar_string[1] = 0;
    wcstombs(retstring, (const wchar_t *)wchar_string, 6);
    *is_hangul = false;
  }
}

void kroman_head_from_index(int head_index, char *retstring) {
  char *head_string;

  switch(head_index) {
    case 0:
      head_string = "g";
      break;
    case 1:
      head_string = "gg";
      break;
    case 2:
      head_string = "n";
      break;
    case 3:
      head_string = "d";
      break;
    case 4:
      head_string = "dd";
      break;
    case 5:
      head_string = "r";
      break;
    case 6:
      head_string = "m";
      break;
    case 7:
      head_string = "b";
      break;
    case 8:
      head_string = "bb";
      break;
    case 9:
      head_string = "s";
      break;
    case 10:
      head_string = "ss";
      break;
    case 11:
      head_string = "";
      break;
    case 12:
      head_string = "j";
      break;
    case 13:
      head_string = "jj";
      break;
    case 14:
      head_string = "c";
      break;
    case 15:
      head_string = "k";
      break;
    case 16:
      head_string = "t";
      break;
    case 17:
      head_string = "p";
      break;
    case 18:
      head_string = "h";
      break;
    default:
      fprintf(stderr, "Error: Unknown head.\n");
      exit(1);
      break;
  }

  sprintf(retstring, "%s", head_string);
}

void kroman_body_from_index(int body_index, char *retstring) {
  char *body_string;

  switch(body_index) {
    case 0:
      body_string = "a";
      break;
    case 1:
      body_string = "ae";
      break;       
    case 2:
      body_string = "ya";
      break;
    case 3:
      body_string = "yae";
      break;
    case 4:
      body_string = "eo";
      break;
    case 5:
      body_string = "e";
      break;
    case 6:
      body_string = "yeo";
      break;
    case 7:
      body_string = "ye";
      break;   
    case 8:
      body_string = "o";
      break;
    case 9:
      body_string = "wa";
      break;
    case 10:
      body_string = "wae";
      break;
    case 11:
      body_string = "oe";
      break;
    case 12:
      body_string = "yo";
      break;
    case 13:
      body_string = "u";
      break;
    case 14:
      body_string = "weo";
      break;
    case 15:
      body_string = "we";
      break;
    case 16:
      body_string = "wi";
      break;
    case 17:
      body_string = "yu";
      break;
    case 18:
      body_string = "eu";
      break;
    case 19:
      body_string = "eui";
      break;
    case 20:
      body_string = "i";
      break;
    default:
      fprintf(stderr, "Error: unknown body\n");
      exit(1);
      break;
  }

  sprintf(retstring, "%s", body_string);
}

void kroman_tail_from_index(int tail_index, char *retstring) {
  char *tail_string;

  switch(tail_index) {
    case 0:
      tail_string = "";
      break;
    case 1:
      tail_string = "g";
      break;       
    case 2:
      tail_string = "gg";
      break;
    case 3:
      tail_string = "gs";
      break;
    case 4:
      tail_string = "n";
      break;
    case 5:
      tail_string = "nj";
      break;
    case 6:
      tail_string = "nh";
      break;
    case 7:
      tail_string = "d";
      break;   
    case 8:
      tail_string = "r";
      break;
    case 9:
      tail_string = "rk";
      break;
    case 10:
      tail_string = "rm";
      break;
    case 11:
      tail_string = "rb";
      break;
    case 12:
      tail_string = "rs";
      break;
    case 13:
      tail_string = "rt";
      break;
    case 14:
      tail_string = "rp";
      break;
    case 15:
      tail_string = "rh";
      break;
    case 16:
      tail_string = "m";
      break;
    case 17:
      tail_string = "b";
      break;
    case 18:
      tail_string = "bs";
      break;
    case 19:
      tail_string = "s";
      break;
    case 20:
      tail_string = "ss";
      break;
    case 21:
      tail_string = "ng";
      break;
    case 22:
      tail_string = "j";
      break;
    case 23:
      tail_string = "c";
      break;
    case 24:
      tail_string = "k";
      break;
    case 25:
      tail_string = "t";
      break;
    case 26:
      tail_string = "p";
      break;
    case 27:
      tail_string = "h";
      break;
    default:
      fprintf(stderr, "Error: unknown tail\n");
      exit(1);
      break;
  }

  sprintf(retstring, "%s", tail_string);
}