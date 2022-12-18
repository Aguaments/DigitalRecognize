#include "file.h"
#include "matrixOp.h"


int main() {

    char imageRoot[] = "..\\Images\\";  //这地方是因为clion的exe文件在cmake那个文件夹里，所以路径改到上一级
    char name[16] = {0};
    char fileName[70] = {0};
    char ** fileArray;
    char ch;
    int num = 0;
    char * enterFile, *p;
    double max = 0;
    double ** A, **C1, **C2;
    double * B, * D, * E1, *E2, * F, * G, * H, * L, * S;

    fileArray = AcquireFileList(imageRoot);
    C1 = getMatrixC1();  //shape(784, 128)
    C2 = getMatrixC2();  //shape(128, 10)
    E1 = getMatrixE1();  //shape(1, 128)
    E2 = getMatrixE2();  //shape(1, 10)

    while (1) {
        fflush(stdin);
        printf("Please input filenames:");
        fgets(fileName, 70, stdin);


        enterFile = GetEnterFileList(fileName);

        p = strtok(enterFile, ",");
        while(p != NULL){
            if(!CheckName(p, fileArray)){
                printf("invalid file.\n");
            }else{
                num = 0;
                max = 0;
                strcat(name, imageRoot);
                strcat(name, p);
                printf("%s: ", p);
                /* 执行识别 */
                A = ImgToMatrix(name);  //shape(28, 28)
                B = Reshape(A);  //shape(1, 784)
                D = matrixMultiplyBC1(B, C1); //shape(1, 128)
                F = matrixAddDE1(D, E1);  //  shape(1, 128)
                G = matrixActivate(F);  //shape(1, 128)
                H = matrixMultiplyGC2(G, C2);  //shape(1, 10)
                L = matrixAddHE2(H, E2);  //shape(1, 10)
                S = SoftMax(L);

                free(A);
                free(B);
                free(D);
                free(F);
                free(G);
                free(H);
                free(L);
                for(int j = 0; j < 10; ++j){
                    max = fmax(max, S[j]);
                    if(max == S[j]) num = j;
                }
                printf("%d\n", num);
                free(S);
            }
            name[0] = '\0';
            p = strtok(NULL, ",");
        }
        printf("do you want to continue? please input [Y or N]:");
        fgets(&ch, 1, stdin);
        getchar();
        if (ch == 'N') {
            printf("Bye\n");
            break;
        }
    }
        return 0;
}
