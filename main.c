#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *makeInput() {
  char *input = (char *)malloc(100 * sizeof(char));

  printf("Digite a operacao: ");
  fgets(input, 100, stdin);

  input[strcspn(input, "\n")] = '\0';

  return input;
}

void clearScreen() {
  system("cls");
}

int findFirstValue(char *input, char operator) {
  char *ptr;
  int index;

  ptr = strchr(input, operator);

  if (ptr == NULL) {
    printf("Character not found\n");
    return 0;
  }

  index = ptr - input;

  char firstValueStr[index + 1];

  strncpy(firstValueStr, input, index);
  firstValueStr[index] = '\0';

  return atoi(firstValueStr);
}

int findSecondValue(char *input, char operator) {
  char *ptr = strchr(input, operator);

  ptr++;

  char *secondValueStr = ptr;

  char *endPtr = secondValueStr;
  while (*endPtr >= '0' && *endPtr <= '9') {
    endPtr++;
  }

  char secondValueStrTrimmed[endPtr - secondValueStr + 1];
  strncpy(secondValueStrTrimmed, secondValueStr, endPtr - secondValueStr);
  secondValueStrTrimmed[endPtr - secondValueStr] = '\0';

  return atoi(secondValueStrTrimmed);
}

char *findOperator(char *input) {
  if (strchr(input, '+')) {
    return "+";
  } else if (strchr(input, '-')) {
    return "-";
  } else if (strchr(input, '*')) {
    return "*";
  } else if (strchr(input, '/')) {
    return "/";
  }
  return NULL;
}

char *removeSpaces(const char *value) {
  int valueLength = strlen(value);
  char *formattedValue = (char *)malloc((valueLength + 1) * sizeof(char));

  if (!formattedValue) {
    return NULL;
  }

  int j = 0;
  for (int i = 0; i < valueLength; i++) {
    if (value[i] != ' ') {
      formattedValue[j] = value[i];
      j++;
    }
  }

  formattedValue[j] = '\0';

  return formattedValue;
}

double sum(int firstValue, int secondValue) {
  return firstValue + secondValue;
}

double subtraction(int firstValue, int secondValue) {
  return firstValue - secondValue;
}

double division(int firstValue, int secondValue) {
  if (secondValue != 0) {
    return firstValue / (double)secondValue;
  } else {
    printf("Erro: divisao por zero !\n");
    return 0;
  }
}

double multiplication(int firstValue, int secondValue) {
  return firstValue * secondValue;
}

int main() {
  while (1) {
    char *input = makeInput();
    char *inputFormatted = removeSpaces(input);
    char *operator = findOperator(inputFormatted);

    if (operator == NULL) {
      free(inputFormatted);
      free(input);
      clearScreen();
      continue; 
    }

    int firstValue = findFirstValue(inputFormatted, operator[0]);
    int secondValue = findSecondValue(inputFormatted, operator[0]);
    double result = 0;
    
    if (strcmp(operator, "+") == 0) {
      result = sum(firstValue, secondValue);
    } else if (strcmp(operator, "-") == 0) {
      result = subtraction(firstValue, secondValue);
    } else if (strcmp(operator, "/") == 0) {
      result = division(firstValue, secondValue);
    } else if (strcmp(operator, "*") == 0) {
      result = multiplication(firstValue, secondValue);
    } else {
      printf("Operacao invalida\n");
    }

    printf("Resultado: %.2f\n", result);
    
    free(input);
    free(inputFormatted);

    printf("Deseja fazer outra operacao ? (S/N): ");
    char choice;
    fgets(&choice, 2, stdin);
    
    if (choice == 'N' || choice == 'n') {
      break;
    }
    
    clearScreen();
  }

  return 0;
}
