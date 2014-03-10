/**
 *  @file num2words.c
 *  @brief the description will be used in lists and at the start of the documentation page
 *  @author Blagovest Kostov
 *  @copy This software is distributed under GPL
 *  
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define BIG_NUMBER(POWER,NAME)                                                                                                           \
if ( number / (long long)powl(10,POWER) > 0) {                                                                                           \
	if( number / (long long)powl(10,POWER) % 10 ==2 )                                                                                      \
    UNITS[2][2]='a';                                                                                                                     \
  remaining = number_to_words_r(number / (long long)powl(10,POWER), words, remaining);                                                   \
  remaining -= append_string(words, remaining, number / (long long)powl(10,POWER)==1? " " TOSTRING(NAME) " ": " " TOSTRING(NAME) "� ");  \
  number %= (long long)powl(10,POWER);UNITS[2][2]='e';                                                                                   \
}





bool beginning = true;

static const char* const TENS[] = {
  "",
  "�����",
  "��������",
  "��������",
  "�����������",
  "��������",
  "���������",
  "����������",
  "���������",
  "����������"
};

char* UNITS[32];

double stotinki;


/**
 *  @fn    append_string
 *  @brief does something
 *  
 *  @param [in] buffer this parameter is passed
 *  @param [in] length this parameter is passed
 *  @param [in] str    this parameter is passed
 *  @return 0 on success, errorcode on failure
 *  
 *  @note for further details, refer to the documentation
 */
size_t append_string(char* buffer, const size_t length, const char* str) {
  strncat(buffer, str, length);
  size_t written = strlen(str);
  return (length > written) ? written : length;
}

/**
 *  @fn    number_to_words_r
 *  @brief does something
 *  
 *  @param [in] number this parameter is passed
 *  @param [in] words  this parameter is passed
 *  @param [in] length this parameter is passed
 *  @return 0 on success, errorcode on failure
 *  
 *  @note for further details, refer to the documentation
 */
size_t number_to_words_r(long long number, char* words, size_t length) {
  size_t remaining = length;
  if (number == 0)
    remaining -= append_string(words, remaining, "");
  else
    BIG_NUMBER(33,��������)
    BIG_NUMBER(30,��������)
    BIG_NUMBER(27,��������)
    BIG_NUMBER(24,���������)
    BIG_NUMBER(21,����������)
    BIG_NUMBER(18,����������)
    BIG_NUMBER(15,����������)
    BIG_NUMBER(12,�������)
    if ( number / (int)pow(10,9) > 0) {
    	if( number / 1000000000 % 10 ==2 )
        UNITS[2][2]='a';
      remaining = number_to_words_r(number / 1000000000, words, remaining);
      remaining -= append_string(words, remaining, number / 1000000000==1? " ������� ": " �������� ");
      number %= 1000000000;UNITS[2][2]='e';
    }
    if ( number / 1000000 > 0) {
    	if( number / 1000000 % 10 ==2 )
        UNITS[2][2]='a';
      remaining = number_to_words_r(number / 1000000, words, remaining);
      remaining -= append_string(words, remaining, number / 1000000==1? " ������ ": " ������a ");
      number %= 1000000;UNITS[2][2]='e';
    }
    if ( number / 1000 > 0) {
    	if(number / 1000 == 1){
	      remaining -= append_string(words, remaining, " ������ ");
	      number %= 1000;
      }else{
      	if(number/1000%10==1){
          UNITS[1][2]='�', UNITS[1][3]='�';
      	}
        remaining = number_to_words_r(number / 1000, words, remaining);
	      remaining -= append_string(words, remaining, " �����u ");
	      number %= 1000;
	      UNITS[1][2]='�', UNITS[1][3]='�';
      }
    }
    if ( number / 100 > 0) {
      if(number/100==1){
	      remaining -= append_string(words, remaining, "��� ");
	      number %= 100;        
      }else{
	      remaining = number_to_words_r(number / 100, words, remaining);
	      remaining -= append_string(words, remaining, (number / 100==2||number / 100==3)?"��� " : "������ ");
	      number %= 100;
      }
      if(number<20){
        remaining -= append_string(words, remaining, "u ");
        beginning=true;
      }
    }
    if (number > 0) {
      if (number < 20){
        if(beginning){
          beginning=false;
        }else{
          remaining -= append_string(words, remaining, ", ");
        }
        remaining -= append_string(words, remaining, UNITS[number]);
      }
      else
        {
          remaining -= append_string(words, remaining, TENS[number / 10]);
          if ( number % 10 > 0)
            remaining -= append_string(words, remaining, " u ");
          remaining -= append_string(words, remaining, UNITS[number % 10]);
        }
    }
    return remaining;
}

/**
 *  @fn    number_to_words
 *  @brief does something
 *  
 *  @param [in] number this parameter is passed
 *  @param [in] words  this parameter is passed
 *  @param [in] length this parameter is passed
 *  @return 0 on success, errorcode on failure
 *  
 *  @note for further details, refer to the documentation
 */
size_t number_to_words(long long number, char* words, size_t length) {
  memset(words, 0, length);
//stotinki = number - (double) ( (int) number ) ;
//stotinki*=100;
  return number_to_words_r( number, words, length);
}

/**
 *  @fn    init
 *  @brief does something
 *  
 *  @return 0 on success, errorcode on failure
 *  
 *  @note for further details, refer to the documentation
 */
void init(void){
  UNITS[ 0] = strdup("");
  UNITS[ 1] = strdup("����");
  UNITS[ 2] = strdup("���");
  UNITS[ 3] = strdup("���");
  UNITS[ 4] = strdup("������");
  UNITS[ 5] = strdup("���");
  UNITS[ 6] = strdup("����");
  UNITS[ 7] = strdup("�����");
  UNITS[ 8] = strdup("����");
  UNITS[ 9] = strdup("�����");
  UNITS[10] = strdup("�����");
  UNITS[11] = strdup("����������");
  UNITS[12] = strdup("����������");
  UNITS[13] = strdup("����������");
  UNITS[14] = strdup("�������������");
  UNITS[15] = strdup("����������");
  UNITS[16] = strdup("�����������");
  UNITS[17] = strdup("������������");
  UNITS[18] = strdup("�����������");
  UNITS[19] = strdup("������������");
}

/**
 *  @fn    release
 *  @brief does something
 *  
 *  @return 0 on success, errorcode on failure
 *  
 *  @note for further details, refer to the documentation
 */
void release(void){
	int i;
  for(i=0;i<20;i++) free(UNITS[i]);
}

/**
 *  @fn    main
 *  @brief does something
 *  
 *  @param [in] argc this parameter is passed
 *  @param [in] argv this parameter is passed
 *  @return 0 on success, errorcode on failure
 *  
 *  @note for further details, refer to the documentation
 */
int main(int argc, char**argv){
	char acWords[2078];
	char acStots[2078];
	if(argc<2){
		puts("���� �������� ������!");
		exit(5);
	}
  init();
	number_to_words(strtold(argv[1],NULL),acWords,2048);
  strcat(acWords, " ����");
/*strcat(acWords, " u ");
  UNITS[1][2]='�', UNITS[1][3]='�';
	number_to_words(stotinki,acStots,2048);
	strcat(acWords, acStots);
  strcat(acWords, " ��������");            */
  printf("��� ����� ��� ������ ������ : %s\n", acWords );
  release();
	return 0;
}


/******************************************************************************\
|                                                                              |
|   $Log$                                                                      |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
\******************************************************************************/


