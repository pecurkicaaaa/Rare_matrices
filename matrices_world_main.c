#include <stdio.h>
#include <stdlib.h>
int vrste, kolone;
void formiraj_matrice(int *R1,int *V1,int *C1,int *R2,int *V2,int *C2,int *R3,int *V3,int *C3)
{
    int redni_br=1, nenulti1, nenulti2;
    while(redni_br<=2)
    {
        int br=0,br_nenultih,vrednost,red_el,kolona_el,i=1,br_vrsta,br_kolona,res=1;
        printf("Enter dimnesion of the %d. matrix.\n",redni_br);
        printf("Enter the number of ROWS: ");
        scanf("%d",&br_vrsta);
        printf("Enter the number of COLUMNS: ");
        scanf("%d",&br_kolona);
        printf("Enter the number of non-zero elements: ");
        scanf("%d",&br_nenultih);
        if(br_nenultih<0)
            {printf("The number of non-zero elements must be bigger or equal to 0. Please enter data again.\n"); return;}

        printf("Enter the value, row, and column of non-zero elements in new line for every element:\n");
        while(i<=br_nenultih)
        {
            scanf("%d %d %d",&vrednost,&red_el,&kolona_el);
            if (redni_br==1)
            {
                vrste=br_vrsta;
                kolone=br_kolona;
                nenulti1=br_nenultih;
                V1[i]=vrednost;
                C1[i]=kolona_el;
                br++;
                if (R1[red_el]==0)
                    R1[red_el]=br;
                i++;
            }
            else
            {
                if (br_vrsta!=vrste || br_kolona!=kolone)
                {
                    res=0;
                    printf("Matrices must be the same dimension. Enter 1 to start from the beginning, or 2 in order to inter just the second matrix: ");
                    scanf("%d",redni_br);
                }
                else
                {
                    nenulti2=br_nenultih;
                    V2[i]=vrednost;
                    C2[i]=kolona_el;
                    br++;
                    if (R2[red_el]==0)
                        R2[red_el]=br;
                    i++;
                }

            }
        }
        if (res==1)
        {
            if (redni_br==1)
            {
                R1[br_vrsta+1]=br_nenultih+1;
                for (int i=1;i<=br_vrsta+1;i++)
                {
                    if (R1[i]==0)
                        R1[i]=R1[i+1];
                }

            }
            else
            {
                R2[br_vrsta+1]=br_nenultih+1;
                for (int i=1;i<=br_vrsta+1;i++)
                {
                    if (R2[i]==0)
                        R2[i]=R2[i+1];
                }
            }
            redni_br++;
        }
    }
    //SABIRANJE
    int nenultih1_tr_vrsta; // broj nenultih elemenata u i-toj vrsti prve matrice
    int nenultih2_tr_vrsta; // broj nenultih elemenata u i-toj vrsti druge matrice
    int brojac_nenultih_3=0;
    int j1=1,j2=1, k=1;

    for (int i=1;i<=vrste;i++)
    {
        nenultih1_tr_vrsta=(int)R1[i+1]-(int)R1[i];
        nenultih2_tr_vrsta=(int)R2[i+1]-(int)R2[i];
        while(nenultih1_tr_vrsta>0 || nenultih2_tr_vrsta>0)
        {
            if (nenultih1_tr_vrsta>0 && nenultih2_tr_vrsta>0)
            {
                if ((int)C1[j1]==(int)C2[j2])
                {
                    brojac_nenultih_3++;
                    if (R3[i]==0)
                        R3[i]=brojac_nenultih_3;
                    C3[k]=C1[j1];
                    V3[k]=(int)V1[j1]+(int)V2[j2];
                    k++;
                    j1++;
                    j2++;
                    nenultih1_tr_vrsta--;
                    nenultih2_tr_vrsta--;

                }
                else
                {
                    brojac_nenultih_3=brojac_nenultih_3+2;
                    if (R3[i]==0)
                        R3[i]=brojac_nenultih_3;
                    if ((int)C1[j1]<(int)C2[j2])
                    {
                        C3[k]=C1[j1];
                        V3[k]=V1[j1];
                        k++;
                        C3[k]=C2[j2];
                        V3[k]=V2[j2];
                        k++;
                    }
                    else
                    {
                        C3[k]=C2[j2];
                        V3[k]=V2[j2];
                        k++;
                        C3[k]=C1[j1];
                        V3[k]=V1[j1];
                        k++;
                    }
                    j1++;
                    j2++;
                    nenultih1_tr_vrsta--;
                    nenultih2_tr_vrsta--;
                }
            }

            else if (nenultih2_tr_vrsta==0)
            {
                brojac_nenultih_3++;
                if (R3[i]==0)
                    R3[i]=brojac_nenultih_3;

                C3[k++]=C1[j1];
                V3[k++]=V1[j1];
                j1++;
                nenultih1_tr_vrsta--;
            }
            else
            {
                brojac_nenultih_3++;
                if (R3[i]==0)
                    R3[i]=brojac_nenultih_3;

                C3[k]=C2[j2];
                V3[k]=V2[j2];
                k++;
                j2++;
                nenultih2_tr_vrsta--;
            }
        }
    }
    R3[vrste+1]=brojac_nenultih_3+1;
    for (int i=1;i<=vrste+1;i++)
    {
        if (R3[i]==0)
            R3[i]=R3[i+1];
    }
}

void ispis_CSR(int *R3,int *V3,int *C3)
{   int i=1, j=1,br;
    while(R3[i]!=0)
    {i++;}
    br=(int)R3[i-1]-1;
    printf("R  C  V\n");
    printf("-------\n");
    i=1;
    while(i<=vrste+1 || j<=br)
    {
        if (i>vrste+1)
            {printf("   %d  %d\n",C3[j],V3[j]); j++;}
        else if (j>br)
            {printf("%d\n",R3[i]); i++;}
        else
        {printf("%d  %d  %d\n",R3[i],C3[j],V3[j]);
        i++;
        j++;}
    }
}
ispis_cela(int *R3,int *V3,int *C3)
{
    int i=1, j=1,br,nenultih;
    while(R3[i]!=0)
    {i++;}
    br=(int)R3[i-1]-1;//br_nenultih
    int a[1000][1000];
    for (i;i<=vrste;i++)
        for (j;j<=kolone;j++)
            a[i][j]=0;
    for (i=1;i<=vrste+1;i++)
    {
        nenultih=(int)R3[i+1]-(int)R3[i];
    }
}

int main()
{
    int V1[1000]={0}, C1[1000]={0}, R1[1000]={0},V2[1000]={0}, C2[1000]={0}, R2[1000]={0},V3[1000]={0}, C3[1000]={0}, R3[1000]={0};
    int opcija=1;
    printf("       Welcome to rare matrix world.       \n\n\n");
    printf("1. Input and addition of two matrices.\n"
           "2. Print the result matrix in CSR format (Compressed row storage).\n"
           "3. Print the result matrix with default values.\n"
           "4. The value of an element of a certain position.\n"
           "4. EXIT.\n\n");
    printf("Enter the menu option you need: ");
    scanf("%d",&opcija);
    while(opcija!=4)
    {
        switch(opcija)
        {
            case 1: formiraj_matrice(R1,V1,C1,R2,V2,C2,R3,V3,C3); break;
            case 2: ispis_CSR(R3,V3,C3); break;
            case 3: ispis_cela(R3,V3,C3); break;
        }
        printf("Enter the next option from the menu: ");
        scanf("%d",&opcija);
    }
    printf("Goodbye.");



    return 0;
}
