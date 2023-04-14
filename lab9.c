#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType *next; // create a next pointer (for linkedlist structure)
};

// Fill out this structure
struct HashType
{
    struct RecordType* Type_ptr;
};

// Compute the hash function
int hash(int x, int tableSize)
{
    return x % tableSize; // hash function is x % tableSize
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    int index = hash(record->id, tableSize);

    // if the RecordType at that index is NULL
    if (hashTable[index].Type_ptr == NULL){
        hashTable[index].Type_ptr = record;
    } else {
        struct RecordType *currentRecord = hashTable[index].Type_ptr;
        while (currentRecord->next != NULL){
            currentRecord = currentRecord->next;
        }
        currentRecord->next = record;
    }
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *hashTable, int tableSize) {
    for (int i = 0; i < tableSize; ++i) {
        struct RecordType *record = hashTable[i].Type_ptr;
        printf("Index %d -> ", i);


        while (record != NULL) {
            printf("%d, %c, %d -> ", record->id, record->name, record->order);
            record = record->next;
            if (record == NULL) {
                printf("NULL\n");
            }
        }
        printf("\n");
    }
}
// for each entry in the table
// print the contents in that index
// The output should look like this (for example): "Index 1 -> 21715, Q, 16 -> 28876, a, 26 -> NULL"

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // create a variable hashTableSize and assign it a value
    // initialize a hashTable, use calloc (so everything is assigned to NULL)
    // for each record in pRecords, insert it into the hash table using the insertRecord function
    // call the display records function
    // free all the allocated memory

    int hashTableSize = 11;

    struct HashType *hashTable = calloc(hashTableSize, sizeof(struct HashType));// Initialize the hash table

    for (int i = 0; i < recordSz; ++i){
        insertRecord(hashTable, pRecords + i, hashTableSize);
    }

    displayRecordsInHash(hashTable, hashTableSize);

    free(hashTable);
    free(pRecords);

    return 0;
}
