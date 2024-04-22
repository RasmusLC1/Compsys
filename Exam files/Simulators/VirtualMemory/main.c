#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

struct pageTable{
    int VPN;
    int valid;
    int physicalpage;
};

struct TranslationTable{
    int valid;
    unsigned int tag;
    int physicalpage;
    int tsla;
};

int Bin2Dec(long n){
    long long dec = 0, i = 0, rem;
    while (n!=0) {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }

    return dec;
}

long long Dec2Bin(long long n){
  long long bin = 0;
  int rem, i = 1, k = 0;

  while (n!=0) {
    rem = n % 2;
    n /= 2;
    bin += rem * i;
    i *= 10;
    k++;
  }
  return bin;
}

int ptSize = 0;

int main(){
    struct pageTable PT[40];
    ptSize = Page_Table(PT);
    

    printf("Page Table\n%8s%8s%8s", "VPN", "PPN", "Valid\n");
    for (int i = 0; i < ptSize; i++){
        printf("%8x%8d%8d\n", PT[i].VPN, PT[i].physicalpage, PT[i].valid);
    }

    int pages, remainder, sets, ways, index = 0;
    printf("How many ways?\n");
    scanf("%d", &ways);

    struct TranslationTable tbl2d[20][10];
    int tblSize = TBL_Table(tbl2d, ways);
    sets = tblSize;

    printf("TBL\n");
    for (int i = 0; i < ways; i++){
        printf("%8s%8s%8s%8s%8c", "Tag", "PPN", "Valid", "Tsla", ' ');
    }
    putchar('\n');
    for (int i = 0; i < sets; i++){
        for (int j = 0; j < ways; j++){
            printf("%8x%8X%8x%8x%8c", tbl2d[i][j].tag, 
                tbl2d[i][j].physicalpage, tbl2d[i][j].valid, tbl2d[i][j].tsla, '|');
            index++;
        }
        putchar('\n');
    }
    

    char addr[10], virtualPage;
    printf("Pages size?\n");
    scanf("%d", &pages);
    int set = round(log2(1024));
    int offset = round(log2(pages));
    printf("\nthere are 4 bytes in a word, therefore the offset can be calculated the following way: log2(2^pages*1000)= %d\n",
        offset, offset/4);
    offset = pow(10, offset);
    for (int i = 0; i < sets; i++){
        for (int j = 0; j < ways; j++){
            printf("%8d%8X%8d%8d  |  ", tbl2d[i][j].valid ,tbl2d[i][j].tag,
                tbl2d[i][j].physicalpage, tbl2d[i][j].tsla);
        }
        putchar('\n');
    }
    int addrhex;
    
    while (1){
        printf("Enter address:\n");
        scanf("%x", &addrhex);
        long long addrBin = Dec2Bin(addrhex);
        
        printf("%d\n", addrBin);
        long long  VPNBin = addrBin/offset;
        printf("bits of virtual address: %d\n", Dec2Bin(addrhex));
        long long  indexBin = VPNBin % 100;
        long long  tagBin = VPNBin/100;
        int tag = Bin2Dec(tagBin);
        int index = Bin2Dec(indexBin);
        int VPN = Bin2Dec(VPNBin);
        
        printf("VPN: %x\nTLB Index: %x\n TLB Tag: %x\n", VPN, index, tag);
        int PPN = Checker(PT, tbl2d, tag, ways, sets, index, VPN, VPNBin);
        if (PPN != 999){

            printf("PPN %d\n", PPN);
            int PPNBIN = Dec2Bin(PPN) + Dec2Bin(addrhex) % offset;
            printf("Bits of phys. %d\n", PPNBIN);
        }
        TBL_Printer(tbl2d, ways, sets);
    }

    return 0;
}

//Setting up Page table
int Page_Table(struct pageTable *pt){
    unsigned int index;
    int valid, physicialpage, i = 0;

    FILE *fptr;
    fptr = fopen("PageTable.txt", "r");
    char line[30];

    while (fgets(line, sizeof(line), fptr)){
        sscanf(line, "%X %x %d\n", &index, &physicialpage, &valid);
        pt[i].VPN = index;
        pt[i].valid = valid;
        pt[i].physicalpage = physicialpage;   
        i++;     
    }
    return i;
}

//setting up TBL
int TBL_Table(struct TranslationTable tbl[20][10], int ways){
    unsigned int tag;
    int valid, physicialpage, tsla, i = 0, j = 0;
    FILE *fptr;
    fptr = fopen("TBL.txt", "r");
    char line[30];
    while (fgets(line, sizeof(line), fptr)){
        sscanf(line,"%x %x %x", &tag, &physicialpage, &valid);
        tbl[i][j].valid = valid;
        tbl[i][j].tag = tag;
        tbl[i][j].physicalpage = physicialpage;
        tbl[i][j].tsla = i+j;
        
        j++;
        if (j == ways){
            i++;
            j = 0;
        }
    }
    
    
    return i;
}

int Checker(struct pageTable *pt, struct TranslationTable tbl2d[10][10],
int tag, int ways, int sets, int index, int VPN, int VPNBin){
    
    int tblBool = 1, ptBool = 1, PPN = 0;
    //TBL hit
    for (int j = 0; j < ways; j++){
        tbl2d[index][j].tsla++;
        if (tag == tbl2d[index][j].tag && tbl2d[index][j].valid == 1){
            printf("TBL hit: Yes\nPage Fault: No\n");
            tblBool = 0;
            tbl2d[index][j].tsla = 0;
            PPN = tbl2d[index][j].physicalpage;
            break;
        }
    }
    if (tblBool == 1){
        printf("TBL hit: No\n");
    }

    int lru = 0, lruIndexj = 0, lruIndexi = 0;


    //TBL miss PT hit
    for (int i = 0; i < ptSize; i++){
        if (VPN == pt[i].VPN && pt[i].valid == 1){
            if (tblBool == 1){
                ptBool = 0;
                printf("Page Fault: No\n");
                    for (int j = 0; j < ways; j++){
                        tbl2d[index][j].tsla++;
                        if (tbl2d[index][j].tsla > lru){
                            lru = tbl2d[index][j].tsla;
                            lruIndexi = index;
                            lruIndexj = j;
                        }
                    }
                tbl2d[index][lruIndexj].physicalpage = pt[i].physicalpage;
                tbl2d[index][lruIndexj].tag = pt[i].VPN;
                tbl2d[index][lruIndexj].valid = 1;
                tbl2d[index][lruIndexj].tsla = 0;
                PPN = tbl2d[lruIndexi][lruIndexj].physicalpage;
            }
            break;
        }
    }

    //TBL miss and PageFault
    if (ptBool == 1 && tblBool == 1){
        int largestPage;
        printf("Page fault: Yes\n");
        for (int j = 0; j < ptSize; j++){
            if (pt[j].physicalpage > pt[j-1].physicalpage){
                largestPage = pt[j].physicalpage;
            }
        }
        pt[ptSize].VPN = tag;
        pt[ptSize].physicalpage = largestPage+1;
        pt[ptSize].valid = 1;


        for (int i = 0; i < sets; i++){
            for (int j = 0; j < ways; j++){
                tbl2d[i][j].tsla++;
                if (tbl2d[i][j].tsla > lru){
                    lru = tbl2d[i][j].tsla;
                    lruIndexi = i;
                    lruIndexj = j;
                }
            }
        }
        tbl2d[lruIndexi][lruIndexj].valid = 1;
        tbl2d[lruIndexi][lruIndexj].tsla = 0;
        tbl2d[lruIndexi][lruIndexj].tag = tag;
        tbl2d[lruIndexi][lruIndexj].physicalpage = pt[ptSize].physicalpage;
        ptSize++;
        return 999;
    }
    
    return PPN;
}

void TBL_Printer(struct TranslationTable tbl2d[20][10], int ways, int sets){
    printf("TBL\n");
    for (int i = 0; i < ways; i++){
        printf("%8s%8s%8s%8s%8c", "Tag", "PPN", "Valid", "Tsla", ' ');
    }
    putchar('\n');
    
    for (int i = 0; i < sets; i++){
        for (int j = 0; j < ways; j++){
            printf("%8x%8X%8x%8x%8c", tbl2d[i][j].tag, 
                tbl2d[i][j].physicalpage, tbl2d[i][j].valid, tbl2d[i][j].tsla, '|');
        }
        putchar('\n');
    }
    putchar('\n');
}

