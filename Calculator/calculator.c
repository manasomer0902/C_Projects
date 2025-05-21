#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

void print_menu();
double addition(FILE *history_file);
double subtraction(FILE *history_file);
double multiplication(FILE *history_file);
double division(FILE *history_file);
double modulus(FILE *history_file);
double power(FILE *history_file);;

int main () {
    int choice;
    double result;

    FILE *history_file = fopen("history.txt", "a"); 
    if (!history_file) {
        fprintf(stderr, "Could not open history.txt for writing.\n");
        return 1;
    }

    while(1) {
        print_menu();
        scanf("%d", &choice);   
        if (choice == 7){
            break;
        }

        if(choice < 1 || choice > 7){
            fprintf(stderr, "Invalid Menu Choice.");
            continue;
        }

         switch (choice) 
        {
        case 1: // Addition
            result = addition(history_file);
            break;    
        case 2: // Subtraction
            result = subtraction(history_file);
            break;     
        case 3: // Multiplication
            result = multiplication(history_file);
            break;     
        case 4: // Division
            result = division(history_file);
            break;     
        case 5: // Modulus
            result = modulus(history_file);
            break;     
        case 6: // Power
            result = power(history_file);
            break;        
        }
        if (!isnan(result)) {
        printf("\nresult of operation is: %.2f\n", result);
        }
    }    
    fclose(history_file);
    return 0;
}

double addition(FILE *history_file) {
    char input[256];
    double sum = 0;
    char *token;

    printf("Enter numbers to add, separated by '+':\n");
    fflush(stdin);
    fgets(input, sizeof(input), stdin);

    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') input[len-1] = '\0';

    char clean_input[256];
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != ' ') {
            clean_input[j++] = input[i];
        }
    }
    clean_input[j] = '\0';

    // Remove '=' at the end if present
    len = strlen(clean_input);
    if (len > 0 && clean_input[len-1] == '=') clean_input[len-1] = '\0';

    // Validate input
    if (strlen(clean_input) == 0) {
        printf("Not a valid format!\n");
        return NAN;
    }

    token = strtok(clean_input, "+");
    if (!token) {
        printf("Not a valid format!\n");
        return NAN;
    }

    fprintf(history_file, "Addition: ");
    int first = 1;
    while (token != NULL) {
        double num = atof(token);
        sum += num;
        if (!first) fprintf(history_file, " + ");
        fprintf(history_file, "%.2f", num);
        first = 0;
        token = strtok(NULL, "+");
    }
    fprintf(history_file, " = %.2f\n", sum);
    fflush(history_file);
    printf("\nresult of operation is: %.2f\n", sum);
    return sum;
}

double subtraction(FILE *history_file) {
    char input[256];
    double result = 0;
    char *token;

    printf("Enter numbers to subtract, separated by '-':\n");
    fflush(stdin);
    fgets(input, sizeof(input), stdin);

    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') input[len-1] = '\0';

    // Remove spaces
    char clean_input[256];
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != ' ') {
            clean_input[j++] = input[i];
        }
    }
    clean_input[j] = '\0';

    // Remove '=' at the end if present
    len = strlen(clean_input);
    if (len > 0 && clean_input[len-1] == '=') clean_input[len-1] = '\0';

    // Validate input
    if (strlen(clean_input) == 0) {
        printf("Not a valid format!\n");
        return NAN;
    }

    token = strtok(clean_input, "-");
    if (!token) {
        printf("Not a valid format!\n");
        return NAN;
    }

    fprintf(history_file, "Subtraction: ");
    int first = 1;
    while (token != NULL) {
        double num = atof(token);
        if (first) {
            result = num;
            fprintf(history_file, "%.2f", num);
            first = 0;
        } else {
            result -= num;
            fprintf(history_file, " - %.2f", num);
        }
        token = strtok(NULL, "-");
    }
    fprintf(history_file, " = %.2f\n", result);
    fflush(history_file);
    printf("\nresult of operation is: %.2f\n", result);
    return result;
}

double multiplication(FILE *history_file) {
    char input[256];
    double result = 1;
    char *token;

    printf("Enter numbers to multiply, separated by '*':\n");
    fflush(stdin);
    fgets(input, sizeof(input), stdin);

    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') input[len-1] = '\0';

    // Remove spaces
    char clean_input[256];
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != ' ') {
            clean_input[j++] = input[i];
        }
    }
    clean_input[j] = '\0';

    // Remove '=' at the end if present
    len = strlen(clean_input);
    if (len > 0 && clean_input[len-1] == '=') clean_input[len-1] = '\0';

    // Validate input
    if (strlen(clean_input) == 0) {
        printf("Not a valid format!\n");
        return NAN;
    }

    token = strtok(clean_input, "*");
    if (!token) {
        printf("Not a valid format!\n");
        return NAN;
    }

    fprintf(history_file, "Multiplication: ");
    int first = 1;
    while (token != NULL) {
        double num = atof(token);
        result *= num;
        if (!first) fprintf(history_file, " * ");
        fprintf(history_file, "%.2f", num);
        first = 0;
        token = strtok(NULL, "*");
    }
    fprintf(history_file, " = %.2f\n", result);
    fflush(history_file);
    printf("\nresult of operation is: %.2f\n", result);
    return result;
}

double division(FILE *history_file) {
    double a, b, result;
    printf("\nPlease enter the first number: ");
    scanf("%lf", &a);
    printf("\nPlease enter the second number: ");
    scanf("%lf", &b);
    if(b == 0) {
        fprintf(stderr, "Invalid Argument for division\n");
        fprintf(history_file, "%.2f / %.2f = nan\n", a, b);
        fflush(history_file);
        return NAN;
    } else {
        result = a / b;
        fprintf(history_file, "%.2f / %.2f = %.2f\n", a, b, result);
        fflush(history_file);
        return result;
    }
}

double modulus(FILE *history_file) {
    double a, b, result;
    printf("\nPlease enter the first number: ");
    scanf("%lf", &a);
    printf("\nPlease enter the second number: ");
    scanf("%lf", &b);
    if((int)b == 0) {
        fprintf(stderr, "Invalid Argument for modulus\n");
        fprintf(history_file, "%.0f %% %.0f = nan\n", a, b);
        fflush(history_file);
        return NAN;
    } else {
        result = (int)a % (int)b;
        fprintf(history_file, "%.0f %% %.0f = %.0f\n", a, b, result);
        fflush(history_file);
        return result;
    }
}

double power(FILE *history_file) {
    double a, b, result;
    printf("\nPlease enter the first number: ");
    scanf("%lf", &a);
    printf("\nPlease enter the second number: ");
    scanf("%lf", &b);
    result = pow(a, b);
    fprintf(history_file, "%.2f ^ %.2f = %.2f\n", a, b, result);
    fflush(history_file);
    return result;
}

void print_menu(){
    printf("\n--------------------------------------");
    printf("\nWelcome to Simple Calculator\n");
    printf("\nChoose one of the following options:");
    printf("\n1. Addition");
    printf("\n2. Subtraction");
    printf("\n3. Multiplication");
    printf("\n4. Divison");
    printf("\n5. Modulus");
    printf("\n6. Power");
    printf("\n7. Exit");
    printf("\nNow Enter your choice: ");
}