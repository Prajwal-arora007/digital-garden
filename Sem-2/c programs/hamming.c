#include <stdio.h>

// Function to calculate the parity bit
int calculateParity(int data[], int n)
{
    int parity = 0;
    for (int i = 0; i < n; i++)
    {
        parity ^= data[i];
    }
    return parity;
}

// Function to encode the data using Hamming Code
void encodeHammingCode(int data[], int n)
{
    // Calculate the parity bits
    int parity1 = calculateParity(data, n);
    int parity2 = calculateParity(&data[1], n - 1);
    int parity4 = calculateParity(&data[3], n - 3);

    // Insert the parity bits into the data
    data[0] = parity1;
    data[1] = parity2;
    data[3] = parity4;
}

// Function to decode the data using Hamming Code
void decodeHammingCode(int data[], int n)
{
    // Calculate the parity bits
    int parity1 = calculateParity(data, n);
    int parity2 = calculateParity(&data[1], n - 1);
    int parity4 = calculateParity(&data[3], n - 3);

    // Check if there is an error
    int error = (parity1 << 2) | (parity2 << 1) | parity4;
    if (error != 0)
    {
        // Correct the error
        data[error - 1] ^= 1;
    }
}

// Main function
int main()
{
    int data[20],i,N,n;
    printf("enter number of bits:");
    scanf("%d",&N);
    for(i=0;i<N;i++)
    {
        printf("Enter data:");
        scanf("%d",&data[i]);
    }

     n = N / sizeof(data[0]);

    // Encode the data
    encodeHammingCode(data, n);

    // Print the encoded data
    for (int i = 0; i < n; i++)
    {
        printf("%d", data[i]);
    }
    printf("\n");

    // Decode the data
    decodeHammingCode(data, n);

    // Print the decoded data
    for (int i = 0; i < n; i++)
    {
        printf("%d", data[i]);
    }
    printf("\n");

    return 0;
}