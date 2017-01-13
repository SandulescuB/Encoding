/* EasyCASE V6.8 12.01.2017 12:37:55 */
/* EasyCASE O
If=vertical
LevelNumbers=no
LineNumbers=yes
Colors=16777215,0,12582912,12632256,0,0,0,16711680,8388736,0,33023,32768,0,0,0,0,0,32768,255,255,65280,255,255,16711935
ScreenFont=Courier New,Regular,100,4,-13,0,400,0,0,0,0,0,0,3,2,1,49,96,96
PrinterFont=Courier,,100,65530,-83,0,400,0,0,0,0,0,0,3,2,1,49,600,600
LastLevelId=511 */
/* EasyCASE ( 1 */
/* EasyCASE ( 511
   Header */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <limits.h>
/* EasyCASE - */
#include "cdefL.h"
/* EasyCASE ) */
/* EasyCASE ( 18
   Definitions */
#define nMaxSymbols             ((uint16) 256) /* 0 .. 255 = 256 possible values -> do not fit in one byte */
/* EasyCASE - */
/* NOTE: A Huffman code of a N symbol alphabet, could generate binary symbols with a maximum code length of N - 1 bits ! */
#define nMaxEncodedSymbolLength ((uint8) nMaxSymbols - 1)
/* EasyCASE - */
#define nOccuranceThreshold     ((uint32) 2)
/* EasyCASE ( 497
   Local Variables and Types */
/* Input file content */
static uint8 * AUDIO__pau8ReadDataArray = NULL;
/* EasyCASE ( 19
   time related */
#define _POSIX_C_SOURCE 200809L
/* EasyCASE ) */
/* EasyCASE < */
typedef struct Bitfield {
        bool B7;
        bool B6;
        bool B5;
        bool B4;
        bool B3;
        bool B2;
        bool B1;
        bool B0;
} stBitfield;
/* EasyCASE > */
/* EasyCASE - */
/* EasyCASE < */
typedef struct NewEncoding {
        uint8  Size:4 ;       /* New size is 2 or 3 .. 16 bits length */
        uint8  NewBitValue:7; /* New Bitwise encoding */
} tstNewEncoding;
/* EasyCASE > */
/* EasyCASE - */
/* EasyCASE < */
typedef struct Dictionary {
        uint8  u8SymbolIndex; /* Original ASCII encoding, 0 .. 255, where 2 (dec) = 0x52 */
        uint32 u32Occurance; 
        tstNewEncoding  stNewEncoding; /* initially, this is the same with Index, but will be modified at encoding phase */
} stDictionary;
/* EasyCASE > */
/* EasyCASE - */
/* EasyCASE < */
typedef struct Node {
        struct stNode * NodeLeft;
        struct stNode * NodeRigth;      /* Left will be '0', right will be '1' */
        struct stNode * NodeParent;     
        uint32 u32NodeOccurance;        /* Weight of each leaf/internal node = Occurance */
        uint8  u8NodeSymbol;            /* cannot be larger than 255, otherwise there is no point in building Huffman Tree?! */
} stNode;
/* EasyCASE > */
/* EasyCASE ) */
/* EasyCASE ( 496
   Local Functions */
static bool SORT_QuickSort(stDictionary *pstArray, uint32 u32Size);
/* EasyCASE - */
static bool AUDIO__boEncoder(uint8 * pu8Array, uint32 u32Size);
/* EasyCASE - */
static bool TREE__bNewEncoding(stDictionary * Symbols, uint8 u8DictSize, uint8 Threshold);
/* Dict Size can be at maximum 255 elements, for a maximum 256 Symbols inside input file -> 1 byte is enough */
/* EasyCASE - */
/* Function responsible with creating the Huffman binary tree */
static stNode * TREE__pstBuildHuffmanTree(stNode **stTree, uint8 u8Elements);
/* EasyCASE - */
/* Function responsible with adding new nodes to existing Huffman binary tree */
static stNode * TREE__pstNewHuffmanNode(uint8 u8Elements);
/* EasyCASE ) */
/* EasyCASE ) */
/* EasyCASE ( 510
   Local Funtion implementation */
/* EasyCASE ( 16
   AUDIO__boEncoder */
/* EasyCASE F */
static bool AUDIO__boEncoder(uint8 * pu8Array, uint32 u32Size)
   {
   uint32 au32ByteCount[nMaxSymbols];
   /* EasyCASE - */
   uint8 u8AboveThresholdOccur = 0;
   /* EasyCASE - */
   uint8 au8Entropy[nMaxSymbols];
   uint8 u8Position = 0;
   /* EasyCASE - */
   uint32 u32Counter = 0;
   uint8 u8Counter = 0;
   /* EasyCASE - */
   uint32 u32TotalNumberOfEncounters = 0;
   /* EasyCASE - */
   uint8 u8MostOftenData = 0;
   uint32 u32DataCounter = 1;
   
   uint8 u8OldMostOftenData = 0;
   uint32 u32OldDataCounter = 1;
   /* EasyCASE - */
   /* Insert Algo below! */
   /* EasyCASE - */
   #if 0 /* Check longest repeat of same Symbol */
   /* EasyCASE ( 353
      Count the longest-consecutive-data and print it */
   /* EasyCASE ( 327
      Count the longest-consecutive-data and print it */
   while (u32Size > 0)
      {
      if (*pu8Array != (*(pu8Array+1)))
         {
         u32DataCounter = 1;
         }
      else
         {
         u32DataCounter++;
         u8MostOftenData = *pu8Array;
         if (u32DataCounter <= u32OldDataCounter)
            {
            }
         else
            {
            u32OldDataCounter = u32DataCounter;
            u8OldMostOftenData = u8MostOftenData;
            }
         }
      pu8Array++;
      /* EasyCASE - */
      u32Size--;
      }
   #ifdef DEBUG
   fprintf(stderr, "\nMost often data = 0x%x, found = %u times \n", u8OldMostOftenData, (unsigned int)u32OldDataCounter);
   fflush(stderr);
   #endif
   /* EasyCASE ) */
   if (u32OldDataCounter <= 5)
      {
      fprintf(stderr, "Too few consecutive bytes. Ignore the Huffman Encoding compression!!\n");
      }
   else
      {
      /* Encoding algorithm here... */
      }
   /* EasyCASE ) */
   #endif
   /* EasyCASE - */
   #if 1 /* Occurance counter for each symbol */
   /* EasyCASE ( 331
      Print occurance counter for each input symbol */
   fprintf(stderr, "%d \n", nMaxSymbols);
   /* EasyCASE - */
   fflush(stderr);
   /* EasyCASE - */
   memset(&au32ByteCount[0], 0, nMaxSymbols * sizeof(au32ByteCount[0]) );
   for (u32Counter = 0; u32Counter < u32Size; u32Counter++, pu8Array++)
      {
      /* Increment X-th read value in position X from ByteCount array */
      au32ByteCount[ *pu8Array ]++;
      }
   /* Print how many times each value 0..255 is repeated inside input file */
   /* EasyCASE - */
   #ifdef DEBUG1
   /* EasyCASE ( 446 */
   fprintf(stderr, "Count each value in file: \n");
   for (u32Counter = 0; u32Counter < nMaxSymbols ; u32Counter++)
      {
      fprintf(stderr, "%02Xh = %u times\n", u32Counter, au32ByteCount[u32Counter]);
      }
   fflush(stderr);
   /* EasyCASE ) */
   #endif /* ifdef DEBUG1 */
   /* EasyCASE ) */
   #endif
   /* EasyCASE - */
   #if 0 /* Entropy */
   /* EasyCASE ( 416
      Entropy */
   /* Calculate min number of bits needed to encode each data from array */
   /* EasyCASE - */
   /* result = integral value, determined by the position (starting from 1 LSbit ) of the highest bit set in the data */
   /* EasyCASE - */
   memset(&au8Entropy[0], 0, nMaxSymbols * sizeof(au8Entropy[0]) );
   /* EasyCASE - */
   /* 0 and 1 can be encoded into one single bit */
   au8Entropy[0] = 1;
   au8Entropy[1] = 1;
   au8Entropy[255] = 8;
   for (u8Counter = 2; u8Counter < nMaxSymbols-1 ; u8Counter++)
      {
      u8Position = 8; // max number of bits needed for encoding
      while ((u8Counter & (1 << (u8Position-1) )) == 0)
         {
         u8Position--;
         }
      au8Entropy[u8Counter] = u8Position;
      }
   fprintf(stderr, "Data ->  Entropy (bits): \n");
   for (u32Counter = 0; u32Counter < nMaxSymbols ; u32Counter++)
      {
      fprintf(stderr, "%02Xh ->  %u\n", u32Counter, au8Entropy[u32Counter]);
      }
   fflush(stderr);
   /* EasyCASE ) */
   #endif /* Entropy */
   /* EasyCASE - */
   /* Now, all symbols (data) with large occurance counter will need to be encoded with smallest number of bits. 
    * For this, a translation between 0x00 = 0 (1 bit) to 0x55 = 0 (2 bits), must be implemented.
    * The symbols that are not present inside input string/wav will not be assigned a encoding number.
    * Steps:
    * 1. Sort input Symbols based on occurance counter, descending (largest encountered number is in position 0 of new array);
    * 2. Build new dictionary (Symbol table <-> encoding) based on occurance: largest ocurred symbol will be encoded in smalles 
    *    number of bits (e.g. 3 bits);
    * 3. Add the new Dictionary to the beggining of output/encoded file;
    * 4. Parse input file and for each input byte, add its new Encoding in the output file (which will be now a string of variable 
    *    sized elements, not an array of bytes) ;
    */
   /* EasyCASE - */
   stDictionary stSymbols[nMaxSymbols];
   /* EasyCASE - */
   /* Dictionary Initialization */
   for (u32Counter = 0; u32Counter < nMaxSymbols ; u32Counter++)
      {
      stSymbols[u32Counter].u8SymbolIndex = (uint8) (u32Counter & 0xFF);
      stSymbols[u32Counter].u32Occurance  = au32ByteCount[u32Counter];   /* Computed earlier */
      stSymbols[u32Counter].stNewEncoding.Size = 0; /* (uint8) (u32Counter & 0xFF); */
      stSymbols[u32Counter].stNewEncoding.NewBitValue = 0; /* (uint8) (u32Counter & 0xFF); */
      }
   /* 1. Sort */
   /* EasyCASE - */
   SORT_QuickSort(&stSymbols, nMaxSymbols);
   /* EasyCASE - */
   /* Determine how many symbols have more than 'defined' encounters. (At this point, 80 symbols out of 255 have more than 10 occurances!) */
   for (u32Counter = 0; u32Counter < nMaxSymbols ; u32Counter++)
      {
      if (stSymbols[u32Counter].u32Occurance >= nOccuranceThreshold)
         {
         u8AboveThresholdOccur++;
         }
      else
         {
         /* Do nothing */
         }
      }
   /* Most occurence will have 3 bit encoding = start array size .. last 8 Symbols from sorted array;
    * Next occurence will have 4 bit encoding = start last 8 Symbols from sorted array .. (last 8 Symbols from sorted array - 15);
    * Next occurence will have 5 bit encoding = start last 8 Symbols from sorted array -15 .. (last 8 Symbols from sorted array -15 -31);
    * Next occurence will have 6 bit encoding = start last 8 Symbols from sorted array -15-31 .. (last 8 Symbols from sorted array -15 -31 -63);
    */
    
    /* Therefore, there will be encoded: 7 + 15 + 31 symbols = 53 new symbols */
    /* If occurance > 1 will be true for <128 symbols, the symbols with occurance 1 will be encoded in 1 byte - fixed 8bits (ASCII),
     * the ones with occurance > 1 can be encoded in 1...7 bits?! */
     
     
     /* Occurance == 0 -> no encoding;
      * Occurance == 1 -> 1 byte/word, fixed length, encoding;
      * Occurance  > 1 -> 3..7 bits encoding = 120 symbols?!*/
   /* EasyCASE - */
   /* 2. Build new dictionary */
   /* EasyCASE - */
   /* 2.1. Build Huffman Tree */
   /* EasyCASE - */
   /* Create the 'Binary Tree of nodes' for all symbols present at least twice in input string! */
   /* EasyCASE - */
   TREE__bNewEncoding(&stSymbols, (uint8) (nMaxSymbols - u8AboveThresholdOccur), u8AboveThresholdOccur);
   /* EasyCASE - */
   /* 2.2. Traverse/parse Huffman Tree to generate variable postfix codes for each leaf (symbol) */
   /* EasyCASE - */
   /* 3. Add the new Dictionary to the beggining of output/encoded file */
   /* EasyCASE ( 437
      DEBUG */
   #ifdef DEBUG
   /* EasyCASE - */
   fprintf(stderr, "ASCII symbol (hex) -> Occurance -> NewEncoding");
   for (u32Counter = 0; u32Counter < nMaxSymbols ; u32Counter++)
      {
      fprintf(stderr, "%02Xh ->  %u -> %02Xh \n", stSymbols[u32Counter].u8SymbolIndex , stSymbols[u32Counter].u32Occurance, stSymbols[u32Counter].stNewEncoding.NewBitValue);
      }
   fprintf(stderr, "Number of symbols > Threshold (%d) = %d\n", nOccuranceThreshold, u8AboveThresholdOccur);
   /* EasyCASE - */
   fflush(stderr);
   /* EasyCASE - */
   #endif /* ifdef DEBUG */
   /* EasyCASE ) */
   return 1;
   }
/* EasyCASE ) */
/* EasyCASE ( 427
   SORT_QuickSort */
/* EasyCASE F */
static bool SORT_QuickSort(stDictionary * u8Array, uint32 u32Size)
   {
   /* Insert Algo below! */
   /* EasyCASE - */
   int i, j;
   if (u32Size > 0)
      {
      for (i = (u32Size - 1); i >= 0; i--)
         {
         for (j = 1; j <= i; j++)
            {
            if (u8Array[j-1].u32Occurance > u8Array[j].u32Occurance)
               {
               int temp = u8Array[j-1].u32Occurance;
               u8Array[j-1].u32Occurance = u8Array[j].u32Occurance;
               u8Array[j].u32Occurance = temp;
               
               /* Swap also index */
               int tempId = u8Array[j-1].u8SymbolIndex;
               u8Array[j-1].u8SymbolIndex = u8Array[j].u8SymbolIndex;
               u8Array[j].u8SymbolIndex = tempId;
               }
            }
         }
      }
   return 1;
   }
/* EasyCASE ) */
/* EasyCASE ( 495
   TREE__bNewEncoding */
/* EasyCASE F */
static bool TREE__bNewEncoding(stDictionary * Symbols, uint8 u8DictSize, uint8 Threshold)
   {
   /*
   Building a Huffman Tree
   
   The Huffman code for an alphabet (set of symbols) may be generated by constructing a binary tree with nodes containing the symbols to be encoded and their probabilities of occurrence. 
   This means that you must know all of the symbols that will be encoded and their probabilities prior to constructing a tree. The tree may be constructed as follows:
   
   Step 1. Create a parentless node for each symbol. Each node should include the symbol and its probability.
   Step 2. Select the two parentless nodes with the lowest probabilities.
   Step 3. Create a new node which is the parent of the two lowest probability nodes.
   Step 4. Assign the new node a probability equal to the sum of its children's probabilities.
   Step 5. Repeat from Step 2 until there is only one parentless node left.
   */
   return 1;
   }
/* EasyCASE ) */
/* EasyCASE ( 507
   TREE__pstBuildHuffmanTree */
/* EasyCASE F */
static stNode * TREE__pstBuildHuffmanTree(stNode **stTree, uint8 u8Elements)
   {
   return 1;
   }
/* EasyCASE ) */
/* EasyCASE ( 509
   TREE__pstNewHuffmanNode */
/* EasyCASE F */
static stNode * TREE__pstNewHuffmanNode(uint8 u8Elements)
   {
   return 1;
   }
/* EasyCASE ) */
/* EasyCASE ) */
/* EasyCASE ( 2
   MAIN() */
/* EasyCASE F */
void main(void)
   {
   struct timespec SORT_Spec;
   uint32            SORT_u32MsAtEnd;
   uint32            SORT_u32MsAtStart;
   /* EasyCASE - */
   int iFileSize = 0;
   /* EasyCASE - */
   uint32 u32Counter;
   /* EasyCASE - */
   /* Open file for write random data */
   FILE * filePointer = NULL;
   /* EasyCASE ( 43
      Initializations */
   /* Clear time holders */
   SORT_u32MsAtStart = 0;
   SORT_u32MsAtEnd = 0;
   /* EasyCASE ) */
   /* --------------  CODE -------------------*/
   /* EasyCASE - */
   filePointer = fopen("./input/Input_Snd.wav" , "r" );
   if (filePointer != NULL)
      {
      if (fseek(filePointer, 0L, SEEK_END) != 0)
         {
         perror("Cant calculate size of file");
         }
      else
         {
         iFileSize = ftell(filePointer);
         fseek(filePointer, 0L, SEEK_SET);
         }
      fprintf(stderr, "New position is = %d \n", fseek(filePointer, 0L, SEEK_SET));
      fflush (stderr);
      /* EasyCASE - */
      AUDIO__pau8ReadDataArray = malloc(iFileSize);
      if (AUDIO__pau8ReadDataArray != NULL)
         {
         memset(AUDIO__pau8ReadDataArray, 1, iFileSize);
         /* EasyCASE ( 82
            Read pointed File */
         /* Read content of pointed File, into local Array */
         /* EasyCASE - */
         /* read all file content into local array for later processing */
         /* EasyCASE - */
         fread(AUDIO__pau8ReadDataArray, iFileSize, 1, filePointer);
         /* EasyCASE - */
         fclose(filePointer);
         /* EasyCASE ) */
         /* We don't really need to print the file content! */
         /* EasyCASE ( 248
            removed prints */
         #ifdef DEBUG
         /* EasyCASE - */
         fprintf(stderr, "++++++++++ Input array is: ");
         for (u32Counter = 0; u32Counter < 10; u32Counter++)
            {
            fprintf(stderr, "%u ", AUDIO__pau8ReadDataArray[u32Counter]);
            }
         fprintf(stderr, "File size is = %d \n", iFileSize);
         fflush (stderr);
         /* EasyCASE - */
         #endif
         /* EasyCASE ) */
         /*
           ____ _____  _    ____ _____      _    _     ____  ___  
          / ___|_   _|/ \  |  _ \_   _|    / \  | |   / ___|/ _ \ 
          \___ \ | | / _ \ | |_) || |     / _ \ | |  | |  _| | | |
           ___) || |/ ___ \|  _ < | |    / ___ \| |__| |_| | |_| |
          |____/ |_/_/   \_\_| \_\|_|   /_/   \_\_____\____|\___/ 
                                                                  
         */
         /* EasyCASE ( 90
            TIME STAMP START */
         clock_gettime(CLOCK_MONOTONIC, &SORT_Spec);
         
         SORT_u32MsAtStart = SORT_Spec.tv_sec * 1000 + (SORT_Spec.tv_nsec / 1000);
         
         fprintf(stderr, "\n[%ld uSec] Started ALGO! \n", SORT_u32MsAtStart);
         fflush(stderr);
         /* EasyCASE ) */
         /* Call Quick Algo with pointer to RAM stored, unsorted file read data */
         AUDIO__boEncoder(AUDIO__pau8ReadDataArray, (uint32)iFileSize);
         /* EasyCASE ( 91
            TIME STAMP END */
         clock_gettime(CLOCK_MONOTONIC, &SORT_Spec);
         
         SORT_u32MsAtEnd = SORT_Spec.tv_sec * 1000 + (SORT_Spec.tv_nsec / 1000);
         
         fprintf(stderr, "[%ld uSec] Finished ALGO! Duration = %ld uSec \n", SORT_u32MsAtEnd, SORT_u32MsAtEnd - SORT_u32MsAtStart);
         fflush(stderr);
         /* EasyCASE ) */
         /* EasyCASE ( 257
            Write Sorted string to an txt file */
         filePointer = fopen("./output/Output_Snd.wav" , "w" );
         if (filePointer != NULL)
            {
            /* EasyCASE ( 262
               Write string to pointed File */
            /* Read content of pointed File, into local Array */
            /* EasyCASE - */
            /* read all file content into local array for later sorting */
            for (u32Counter = 0; u32Counter < iFileSize; u32Counter++)
               {
               fprintf(filePointer, "%d", AUDIO__pau8ReadDataArray[u32Counter]);
               }
            fflush(filePointer);
            /* EasyCASE - */
            fclose(filePointer);
            /* EasyCASE ) */
            }
         else
            {
            perror("Cannot write to file");
            }
         /* EasyCASE ) */
         free(AUDIO__pau8ReadDataArray);
         AUDIO__pau8ReadDataArray = NULL;
         }
      else
         {
         perror("Malloc failed");
         }
      }
   else
      {
      perror("Open file to read error");
      }
   return;
   }
/* EasyCASE ) */
/* EasyCASE ) */
