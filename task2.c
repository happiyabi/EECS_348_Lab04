#include <stdio.h>
#include <ctype.h>

#define ABSOLUTE_ZERO_C -273.15

double toCelsius(double value, char scale)
{
    switch (scale)
    {
    case 'C':
        return value;
    case 'F':
        return (value - 32.0) * 5.0 / 9.0;
    case 'K':
        return value - 273.15;
    default:
        return value;
    }
}

double fromCelsius(double celsius, char scale)
{
    switch (scale)
    {
    case 'C':
        return celsius;
    case 'F':
        return celsius * 9.0 / 5.0 + 32.0;
    case 'K':
        return celsius + 273.15;
    default:
        return celsius;
    }
}

const char *categorize(double celsius)
{
    if (celsius < 0.0)
    {
        return "Freezing";
    }
    else if (celsius < 10.0)
    {
        return "Cold";
    }
    else if (celsius < 25.0)
    {
        return "Comfortable";
    }
    else if (celsius < 35.0)
    {
        return "Hot";
    }
    else
    {
        return "Extreme Heat";
    }
}

const char *advisory(const char *category)
{
    if (category[0] == 'F')
    {
        return "Wear a heavy coat and watch out for ice!";
    }
    else if (category[0] == 'C' && category[1] == 'o')
    {
        return "Wear a jacket.";
    }
    else if (category[0] == 'C')
    {
        return "Enjoy the nice weather!";
    }
    else if (category[0] == 'H')
    {
        return "Drink lots of water!";
    }
    else
    {
        return "Stay indoors and stay hydrated.";
    }
}

int readDouble(double *value)
{
    int result = scanf("%lf", value);

    if (result == EOF)
    {
        return -1;
    }
    if (result != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        return 0;
    }
    return 1;
}

int readScale(const char *prompt, char *scale)
{
    char buf[64];

    printf("%s", prompt);

    int result = scanf("%63s", buf);
    if (result == EOF)
    {
        return -1;
    }
    if (result != 1)
    {
        return 0;
    }

    char c = (char)toupper((unsigned char)buf[0]);
    if ((c == 'C' || c == 'F' || c == 'K') && buf[1] == '\0')
    {
        *scale = c;
        return 1;
    }

    return 0;
}

int main(void)
{
    double value;
    char fromScale, toScale;
    int status;

    while (1)
    {
        printf("Enter the temperature value: ");
        status = readDouble(&value);
        if (status == -1)
        {
            return 0;
        }
        if (status == 1)
        {
            break;
        }
        printf("Invalid input. Please enter a numeric temperature value.\n");
    }

    while (1)
    {
        status = readScale("Enter the original scale (C, F, or K): ", &fromScale);
        if (status == -1)
        {
            return 0;
        }
        if (status == 1)
        {
            if (fromScale == 'K' && value < 0.0)
            {
                printf("Invalid input: Kelvin temperatures cannot be negative. Please re-enter.\n");
                printf("Enter the temperature value: ");
                if (readDouble(&value) == -1)
                {
                    return 0;
                }
                continue;
            }
            double checkC = toCelsius(value, fromScale);
            if (checkC < ABSOLUTE_ZERO_C)
            {
                printf("Invalid input: temperature is below absolute zero. Please re-enter.\n");
                printf("Enter the temperature value: ");
                if (readDouble(&value) == -1)
                {
                    return 0;
                }
                continue;
            }
            break;
        }
        printf("Invalid scale. Please enter C, F, or K.\n");
    }

    while (1)
    {
        status = readScale("Enter the scale to convert to (C, F, or K): ", &toScale);
        if (status == -1)
        {
            return 0;
        }
        if (status == 1)
        {
            break;
        }
        printf("Invalid scale. Please enter C, F, or K.\n");
    }

    double celsius = toCelsius(value, fromScale);
    double converted = fromCelsius(celsius, toScale);
    const char *category = categorize(celsius);

    printf("Converted temperature: %.2f %c\n", converted, toScale);
    printf("Temperature category: %s\n", category);
    printf("Weather advisory: %s\n", advisory(category));

    return 0;
}