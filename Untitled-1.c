#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define TRUE 1
#define INVALID_STUDENT_CODE -1

struct Student{
    int MSSV;
    char name[1000];
    float CPA;
};

typedef struct Student Student;

struct Node{
    Student student;
    struct node *next;
};
 
typedef struct Node *Node;
Node createNode(Student x){
    Node temp;
    temp = (Node)malloc(sizeof(struct Node));
    temp->next=NULL;
    temp->student=x;
    return temp;
}

Node InitHead(){
    Node head;
    head = NULL;
    return head;
}

Student createHS(){
    Student newHS;
    printf("Nhap MSSV:");
  do{
    scanf("%d", &newHS.MSSV);
    if(findIndexByCode(head, newHS.MSSV) > 0){
printf("MSSV da bi trung, vui long nhap lai");
}
}while(findIndexByCode(head, newHS.MSSV) > 0)
    printf("Nhap Ten:");
    char *p;
    getchar();
    fgets(newHS.name,1000,stdin);
    if ((p=strchr(newHS.name, '\n')) != NULL){
        *p = '\0';
    }
    do{
    if(newHS.CPA < 0||newHS.CPA >4)
    printf("CPA khong the nho hon 0 hoac lon hon 4. Nhap lai!\n");
    printf("Nhap CPA:");
    scanf("%f", &newHS.CPA);
    }while(newHS.CPA < 0||newHS.CPA >4);
    return newHS;
}

Node AddTail(Node head, Student value){
    Node temp,p;
    temp = createNode(value);
    if(head==NULL){
        head=temp;
    }
    else{
        p = head;
        while(p->next!=NULL){
            p=p->next;
        }
        p->next=temp;
    }
    return head;
}

Node AddHead(Node head, Student value){
    Node temp = createNode(value);
    if(head==NULL){
        head=temp;
    }
    else{
        temp->next=head;
        head=temp;
    }
    return head;
}

Node AddAt(Node head, Student value,int position){
    position=position-1;
    if(position==0||head==NULL){
        head = AddHead(head, value);
    }
    else{
        int k =1;
        Node p = head;
        while(p != NULL && k!= position){
            p = p->next;
            ++k;
        }
    if(k !=position){
        head = AddTail(head, value);
        printf("Vi tri chen vuot qua vi tri cuoi cung");
    }
    else{
        Node temp = createNode(value);
        temp->next=p->next;
        p->next = temp;
    }
    }
    return head;
}

Node delHead(Node head){
    if(head==NULL){
        printf("Khong co gi de xoa!");
    }
    else{
        head=head->next;
    }
    return head;
}
Node delTail(Node head){
    if(head==NULL||head->next==NULL){
        return delHead(head);
    }else{
        Node p = head;
        Node q = p->next;
        while(q->next !=NULL){
            p=p->next;
        }
        p->next= q->next;
        return head;
    }
}
Node delAt(Node head, int position){
    if(position == 0 || head == NULL || head->next == NULL){
        head = delHead(head); 
    }else{

        int k = 1;
        Node p = head;
        Node q = p->next;
        while(q->next != NULL && k != position){
            p = p->next;
            ++k;
        }
        if(k != position){
            head = delTail(head);
        }else{
            p->next = q->next;
        }
    }
    return head;
}
Student handleLineData(char *line){
    Student student;
    student.MSSV = INVALID_STUDENT_CODE;
    const char delimiter[] = "\t";
    char *tmp;
    tmp = strtok(line, delimiter);
    if (tmp == NULL) {
        printf("Du lieu khong dinh dang: %s", line);
        exit(EXIT_FAILURE);
    }
   student.MSSV = atoi(tmp);
    int index = 0;
    for (;;index++) {
        tmp = strtok(NULL, delimiter);
        if (tmp == NULL)
            break;
        if (index == 0){
            strcpy(student.name, tmp);
        }else if (index == 1){
           student.CPA = (float)atof(tmp);
        }else {
            printf("Du lieu khong dinh dang: %s", line);
            exit(EXIT_FAILURE);
        }
    }
    return student;
}
void printlist(Node head){
    printf("Danh sach hien tai:\n");
    printf("-----------------------------------------\n");
    printf("%10s%15s%12s\n","Ma sinh vien","Ho va ten","CPA");
    for(Node p = head; p != NULL; p = p->next){
        printf("%10d%18s%12.2f\n",p->student.MSSV,p->student.name,p->student.CPA);
    }
    printf("-----------------------------------------\n");
}

int findIndexByCode(Node head, int code){
    int index = -1;
    for(Node p = head; p != NULL; p = p->next){
        index++;
        if (p->student.MSSV == code){
            return index;
        }
    }
    return -1;
}
 
Student IndexByCode(Node head){
    int code;
    Student newHS;
    int found = 0;
    char option;
    while(TRUE){
    printf("===================Tra cuu sinh vien==============\n");
    printf("Nhap MSSV muon tra cuu:");
    scanf("%d", &code);  
    for(Node p = head; p!=NULL;p=p->next){
        if(p->student.MSSV==code){
            newHS = p->student;
            found = 1;
            break;
        }
    }
    if(found){ 
        return newHS;
    }
        else{
            printf("Khong tim thay du lieu! Tim tiep (Y/n)?");
        }
        getchar();
        scanf("%c", &option);
        if(option =='N'||option == 'n'){
            break;
        }
    }
}

Node addNode(Node head){
    Student newHS;
    char option;
    int position;
    while(TRUE){
        printf("===========Nhap du lieu can them============\n");
        printf("Nhap vi tri muon them:");
        scanf("%d", &position);
        newHS=createHS();
        head = AddAt(head, newHS, position);
        printf("Them thanh cong! Them tiep? (Y/n)");
        getchar();
        scanf("%c", &option);
        if(option == 'N'||option =='n')
        break;
    }
    return head;
}
void editNode(Node head){
    int code;
    char option;
    Student newHS;
    while(TRUE){
        printf("=================Chon Sinh vien can sua================\n");
        printf("Nhap MSSV can sua:");
        scanf("%d", &code);
        int found  = 0;
        for(Node p = head; p != NULL; p=p->next){
            if(p->student.MSSV==code){
                found  = 1;
                printf("LUU Y! Sua lai toan bo thong tin sinh vien!!\n");
               newHS = createHS();
                p->student = newHS;
                break;
            }
        }
        if(found){
            printf("Sua thanh cong! Sua tiep (Y/n)? ");
        }else{
            printf("Khong tim thay du lieu! Sua tiep (Y/n)?");
        }
        getchar();
        scanf("%c", &option);
        if(option =='N'||option == 'n')
        break;
    }
}
Node removeNode(Node head){
    int code;
    char option;
    Student newHS;
    while(TRUE){
        printf("=================Chon Sinh vien can xoa================\n");
        printf("Nhap MSSV:");
        scanf("%d", &code);
        int position = findIndexByCode(head, code);
        if(position < 0){
            printf("Khong tim thay du lieu! Tiep tuc (Y/n)?");
        }
        else {
            head=delAt(head, position);
            printf("Xoa thanh cong! Xoa tiep (Y/n)?");
        }
        getchar();
        scanf("%c", &option);
        if(option =='N'||option == 'n')
        break;
    }
    return head;   
}

float Average(Node head){
    float sum = 0;
    int a = 0;
    for(Node p = head; p!=NULL;p=p->next){
        sum += p->student.CPA;
        a++;
    }
    return sum/a;
}

Student maxbyCPA(Node head){
    Student student = head->student;
    for(Node p = head; p!=NULL;p=p->next){
        if(p->student.CPA>student.CPA)
        student = p->student;
        }
    return student;
}

Node LastNode(Node head){
    Node temp = head;
    while(temp != NULL && temp->next !=NULL){
        temp = temp->next;
    }
    return temp;
}

Node partion(Node first, Node last){
    Node pivot = first;
    Node front = first;
    Student temp;
    while(front != NULL && front != last){
        if(front->student.CPA < last->student.CPA){
            pivot = first;
            temp = first->student;
            first->student = front->student;
            front->student = temp;
            first = first->next;
        }
        front = front->next;
    }
    temp = first->student;
    first->student = last->student;
    last->student=temp;
    return pivot;
}

void quickSort(Node first, Node last){
    if(first == last){
        return;
    }
    Node pivot = partion(first, last);
    if (pivot != NULL && pivot->next != NULL) {
        quickSort(pivot->next, last);
    }
  
    if (pivot != NULL && first != pivot) {
        quickSort(first, pivot);
    }
}


Node readData(Node head, const char* fileName){
    FILE* file = fopen(fileName, "r");
    if(!file){
        printf("Co loi khi mo file : %s\n", fileName);
        exit(EXIT_FAILURE);
    }
    char line[500];
    while (fgets(line, sizeof(line), file)) {
        Student student = handleLineData(line);
        if (student.MSSV != INVALID_STUDENT_CODE) {
            head = AddTail(head, student);
        }
    }
    fclose(file);
    return head;
}

Node writeData(Node head, const char* fileName){
    FILE* file = fopen(fileName, "w");
    if(file == NULL){
        printf("Co loi khi mo file : %s\n", fileName);
        exit(EXIT_FAILURE);
    }
    for(Node p = head; p != NULL; p=p->next){
        fprintf(file, "%d\t%s\t%.2f\n", p->student.MSSV, p->student.name, p->student.CPA);
    }
    fclose(file);
    return head;
}

void printMenu(){
    printf("------------------------------------------------\n");
    printf("|               Truong DHBK Ha Noi              |\n");
    printf("|       He thong quan ly du lieu sinh vien      |\n");
    printf("|                                               |\n");
    printf("|           Chon cac thao tac sau day           |\n");
    printf("------------------------------------------------\n");
    printf("===================== MENU =====================\n");
    printf("1. Duyet danh sach\n");
    printf("2. Them du lieu \n");
    printf("3. Sua du lieu \n");
    printf("4. Xoa du lieu \n");
    printf("5. Tinh diem CPA trung binh\n");
    printf("6. Sinh vien co diem CPA cao nhat\n");
    printf("7. Tra cuu MSSV\n");
    printf("8. Sap xep danh sach theo CPA\n");
    printf("9. Luu thay doi\n");
    printf("10. Thoat chuong trinh\n");
    printf("================================================\n");
}
int main(){
    Node head = InitHead();
    head = readData(head, "E://Bai Tap//CTDL&GT//Linked list//DS_Sinhvien.txt");
    int option;
    Student result;
    while(TRUE){
        printMenu();
        printf("Nhap lua chon cua ban (1-10): ");
        scanf("%d", &option);
        switch(option) {
            case 1:
                system("cls");
                printlist(head);
                break;
            case 2:
                system("cls");
                head = addNode(head);
                break;
            case 3:
                system("cls");
                editNode(head);
                break;
            case 4:
                system("cls");
                head = removeNode(head);
                break;
            case 5:
                system("cls");
                printf("Diem CPA trung binh %.2f\n", Average(head));
                break;
            case 6:
                system("cls");
                result = maxbyCPA(head);
                printf("Sinh vien %s co diem CPA cao nhat voi MSSV %d. Diem CPA: %.2f\n", result.name, result.MSSV,result.CPA);
                break;
            case 7:
                system("cls");
                result = IndexByCode(head);
                printf("MSSV: %d Sinh vien: %s Diem CPA: %.2f\n", result.MSSV, result.name, result.CPA);
                break;
            case 8:
                system("cls");
                quickSort(head, LastNode(head));
                printlist(head);
                break;
            case 9:
                system("cls");
                head = writeData(head, "E://Bai Tap//CTDL&GT//Linked list//DS_Sinhvien.txt");
                printf("Luu thay doi thanh cong!\n");
                break;
            case 10:
                system("cls");
                printf("Ket thuc chuong trinh!... Bam bat ky nut nao de thoat!\n");
                getch();
                exit(EXIT_SUCCESS);
            default:
                system("cls");
                printf("Lua chon khong dung, vui long nhap lai!\n");
                break;
        }
    }
    return;
}