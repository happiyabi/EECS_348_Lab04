#include <stdio.h>

void findCombinations(int score)
{
    int found = 0;

    printf("Possible combinations of scoring plays if a team's score is %d:\n", score);

    for (int a = 0; 8 * a <= score; a++)
    {
        int remA = score - 8 * a;

        for (int b = 0; 7 * b <= remA; b++)
        {
            int remB = remA - 7 * b;

            for (int c = 0; 6 * c <= remB; c++)
            {
                int remC = remB - 6 * c;

                int startD = remC % 2;

                for (int d = startD; 3 * d <= remC; d += 2)
                {
                    int remD = remC - 3 * d;
                    if (remD % 2 == 0)
                    {
                        int e = remD / 2;
                        printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n",
                               a, b, c, d, e);
                        found = 1;
                    }
                }
            }
        }
    }

    if (!found)
    {
        printf("  No possible combinations of scoring plays for this score.\n");
    }
}

int readInt(int *value)
{
    int result = scanf("%d", value);

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

int main(void)
{
    int score;

    while (1)
    {
        printf("Enter the NFL score (Enter 1 to stop): ");

        int status = readInt(&score);
        if (status == -1)
        {
            break;
        }
        if (status == 0)
        {
            printf("Invalid input. Please enter a whole number.\n");
            continue;
        }

        if (score == 1)
        {
            break;
        }

        if (score < 0)
        {
            printf("Invalid score: a score cannot be negative. Please try again.\n");
            continue;
        }

        findCombinations(score);
    }

    return 0;
}