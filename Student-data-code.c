#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
//Khai bao cac bien co dinh
#define TRUE 1
#define INVALID_STUDENT_CODE -1
//Khai bao kieu du lieu sinh vien gom MSSV, ho va ten, CPA
struct Student{
    int MSSV;
    char name[1000];
    float CPA;
};
//Goi mot cai ten ngan gon hon 
typedef struct Student Student;
//Khai bao kieu du lieu Node trong Linked List
struct Node{
    Student student;
    struct node *next;
};
//Goi mot cai ten ngan gon hon
typedef struct Node *Node;
//Nhap du lieu vao tung Node
Node createNode(Student x){
    Node temp;
    temp = (Node)malloc(sizeof(struct Node));
    temp->next=NULL;
    temp->student=x;
    return temp;
}
//Khai bao Node Head cua Linked List
Node InitHead(){
    Node head;
    head = NULL;
    return head;
}
//Ham tim kiem vi tri cua sinh vien trong danh sach
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
//Ham tao du lieu cho sinh vien
Student createHS(Node head){
    Student newHS;
    //Nhap va kiem tra MSSV
    do{
    printf("Nhap MSSV:");
    scanf("%d", &newHS.MSSV);
    if(findIndexByCode(head, newHS.MSSV) >= 0){
    printf("MSSV da bi trung, vui long nhap lai!\n");
    }  
    }while(findIndexByCode(head, newHS.MSSV) >= 0);
    //Nhap Ho va Ten
    printf("Nhap Ten:");
    char *p;
    getchar();
    fgets(newHS.name,1000,stdin);
    if ((p=strchr(newHS.name, '\n')) != NULL){
        *p = '\0';
    }
    //Nhap va kiem tra CPA
    do{
    printf("Nhap CPA: ");
    scanf("%f", &newHS.CPA);
    if(newHS.CPA < 0||newHS.CPA >4)
    printf("CPA khong the nho hon 0 hoac lon hon 4. Nhap lai!\n");
    }while(newHS.CPA < 0||newHS.CPA >4);
    return newHS;
}
//Ham them Node vao cuoi danh sach
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
//Ham them Node o dau danh sach
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
//Ham them Node o vi tri bat ki theo yeu cau
Node AddAt(Node head, Student value,int position){
    position=position-1;
    //Neu vi tri la dau danh sach hoac chua co danh sach
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
        //Neu vi tri la cuoi danh sach
    if(k !=position){
        head = AddTail(head, value);
        printf("Vi tri chen vuot qua vi tri cuoi cung!\n");
    }
    else{
        //Vi tri giua danh sach
        Node temp = createNode(value);
        temp->next=p->next;
        p->next = temp;
    }
    }
    return head;
}
//Ham xoa Node Head
Node delHead(Node head){
    if(head==NULL){
        printf("Khong co gi de xoa!");
    }
    else{
        head=head->next;
    }
    return head;
}
//Ham xoa Node Cuoi
Node delTail(Node head){
    if(head==NULL||head->next==NULL){
        return delHead(head);
    }else{
        Node p = head;
        Node prev = NULL;
        while(p->next !=NULL){
            prev=p;
            p=p->next;
        }
        prev->next= NULL;
        free(p);
        p=NULL;
        return head;
    }
}
//Ham xoa Node bat ky
Node delAt(Node head, int position){
    //Neu vi tri xoa ở dau danh sach
    if(position == 0 || head == NULL || head->next == NULL){
        head = delHead(head); 
    }else{
        int k = 0;
        Node p = head;
        Node prev = NULL;
        while(p != NULL && k != position){
            prev = p;
            p=p->next;
            k++;
        }
        //Vi tri xoa ở giua danh sach
        if(k != position){
            head = delTail(head);
        }else{
            prev->next=p->next;
            free(p);
            p=NULL;
        }
    }
    return head;
}


//Ham tach du lieu trong file
Student handleLineData(char *line){
    Student student;
    student.MSSV = INVALID_STUDENT_CODE;
    const char delimiter[] = "\t";
    char *tmp;
    //Strtok dung de tach tung thanh phan
    tmp = strtok(line, delimiter);
    if (tmp == NULL) {
        printf("Du lieu khong dinh dang: %s", line);
        exit(EXIT_FAILURE);
    }
    //Nhap MSSV tu file vao chuong trinh
   student.MSSV = atoi(tmp);
    int index = 0;
    for (;;index++) {
        tmp = strtok(NULL, delimiter);
        if (tmp == NULL)
            break;
        if (index == 0){
            //Nhap ho va ten tu file vao chuong trinh
            strcpy(student.name, tmp);
        }else if (index == 1){
            //Nhap CPA tu file vao chuong trinh
           student.CPA = (float)atof(tmp);
        }else {
            printf("Du lieu khong dinh dang: %s", line);
            exit(EXIT_FAILURE);
        }
    }
    return student;
}
//Ham in danh sach sau khi da nhap file
void printlist(Node head){
    printf("Danh sach hien tai:\n");
    printf("-----------------------------------------\n");
    printf("%10s%15s%12s\n","Ma sinh vien","Ho va ten","CPA");
    for(Node p = head; p != NULL; p = p->next){
        printf("%10d%18s%12.2f\n",p->student.MSSV,p->student.name,p->student.CPA);
    }
    printf("-----------------------------------------\n");
}

//Ham tra ve thong tin sinh vien khi nhap MSSV
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
//Ham them du lieu vao danh sach
Node addNode(Node head){
    Student newHS;
    char option;
    int position;
    while(TRUE){
        printf("===========Nhap du lieu can them============\n");
        printf("Nhap vi tri muon them:");
        scanf("%d", &position);
        newHS=createHS(head);
        head = AddAt(head, newHS, position);
        printf("Them thanh cong! Them tiep? (Y/n)");
        getchar();
        scanf("%c", &option);
        if(option == 'N'||option =='n')
        break;
    }
    return head;
}
//Ham sua du lieu trong danh sach
void editNode(Node head){
    int code;
    char option;
    Student newHS;
    while(TRUE){
        printf("=================Chon Sinh vien can sua================\n");
        printf("Nhap MSSV can sua: ");
        scanf("%d", &code);
        int found  = 0;
        for(Node p = head; p != NULL; p=p->next){
            if(p->student.MSSV==code){
                found  = 1;
                printf("LUU Y! Sua lai toan bo thong tin sinh vien!!\n");
                newHS.MSSV = code;
                printf("Nhap ho va ten moi: ");
                char *q;
                getchar();
    fgets(newHS.name,1000,stdin);
    if ((q=strchr(newHS.name, '\n')) != NULL){
        *q = '\0';
    }
    do{
    if(newHS.CPA < 0||newHS.CPA >4)
    printf("CPA khong the nho hon 0 hoac lon hon 4. Nhap lai!\n");
    printf("Nhap CPA moi:");
    scanf("%f", &newHS.CPA);
    }while(newHS.CPA < 0||newHS.CPA >4);
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
//Ham xoa du lieu trong danh sach
Node removeNode(Node head){
    int code;
    char option;
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
//Ham tinh diem CPA trung binh
float Average(Node head){
    float sum = 0;
    int a = 0;
    for(Node p = head; p!=NULL;p=p->next){
        sum += p->student.CPA;
        a++;
    }
    return sum/a;
}
//Ham tim sinh vien co diem CPA cao nhat
void maxbyCPA(Node head){
    Student studentMax = head->student;
    for(Node p = head; p!=NULL;p=p->next){
        if(p->student.CPA>studentMax.CPA)
        studentMax = p->student;
        }
    //Truong hop 2 diem CPA bang nhau
    for(Node p = head; p!=NULL;p=p->next){
        if(p->student.CPA==studentMax.CPA)
        printf("Sinh vien %s voi MSSV %d co diem CPA cao nhat la: %.2f\n", p->student.name, p->student.MSSV, p->student.CPA);
        }
}
//Ham tim Node cuoi cua danh sach
Node LastNode(Node head){
    Node temp = head;
    while(temp != NULL && temp->next !=NULL){
        temp = temp->next;
    }
    return temp;
}
//Ham tim phan tu partion va sap xep lai danh sach theo CPA
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
//Ham tim phan tu partion va sap xep lai danh sach theo ho va ten
Node partion2(Node first, Node last){
    Node pivot = first;
    Node front = first;
    Student temp;
    while(front != NULL && front != last){
        if(strcmp(front->student.name, last->student.name) < 0){
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
//Ham sap xep theo giai thuat QuickSort khi da co phan tu partion sap xep theo CPA
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
//Ham sap xep theo giai thuat QuickSort khi da co phan tu partion sap xep theo ho va ten
void quickSort2(Node first, Node last){
    if(first == last){
        return;
    }
    Node pivot = partion2(first, last);
    if (pivot != NULL && pivot->next != NULL) {
        quickSort2(pivot->next, last);
    }
  
    if (pivot != NULL && first != pivot) {
        quickSort2(first, pivot);
    }
}
//Ham doc du lieu tu file
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
//Ham luu thay doi du lieu vao file
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
//Ham tao danh muc tren CMD
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
    printf("9. Sap xep danh sach theo Ho va Ten\n");
    printf("10. Luu thay doi\n");
    printf("11. Thoat chuong trinh\n");
    printf("================================================\n");
}
//Ham main
int main(){
    Node head = InitHead();
    //doc du lieu tu file
    head = readData(head, "E://Bai Tap//CTDL&GT//Linked list//DS_Sinhvien.txt" );
    int option;
    Student result;
    while(TRUE){
        printMenu();
        printf("Nhap lua chon cua ban (1-11): ");
        scanf("%d", &option);
        switch(option) {
            case 1:
                //Duyet danh sach
                system("cls");
                printlist(head);
                break;
            case 2:
                //Them du lieu
                system("cls");
                head = addNode(head);
                break;
            case 3:
                //Sua du lieu
                system("cls");
                editNode(head);
                break;
            case 4:
                //Xoa du lieu
                system("cls");
                head = removeNode(head);
                break;
            case 5:
                //Tinh diem CPA trung binh
                system("cls");
                printf("Diem CPA trung binh %.2f\n", Average(head));
                break;
            case 6:
                //Tim sinh vien co diem CPA cao nhat
                system("cls");
                maxbyCPA(head);
                break;
            case 7:
                //Tim thong tin sinh vien theo MSSV
                system("cls");
                result = IndexByCode(head);
                printf("MSSV: %d Sinh vien: %s Diem CPA: %.2f\n", result.MSSV, result.name, result.CPA);
                break;
            case 8:
                //Sap xep danh sach theo CPA
                system("cls");
                quickSort(head, LastNode(head));
                printlist(head);
                break;
            case 9:
                //Sap xep danh sach theo ho va ten
                system("cls");
                quickSort2(head, LastNode(head));
                printlist(head);
                break;
            case 10:
                //Luu thay doi vao file
                system("cls");
                head = writeData(head, "E://Bai Tap//CTDL&GT//Linked list//DS_Sinhvien.txt");
                printf("Luu thay doi thanh cong!\n");
                break;
            case 11:
                //Thoat chuong trinh
                system("cls");
                printf("Ket thuc chuong trinh!... Bam bat ky nut nao de thoat!\n");
                getch();
                exit(EXIT_SUCCESS);
            default:
                //Ham xu li loi nhap sai lua chon
                system("cls");
                printf("Lua chon khong dung, vui long nhap lai!\n");
                break;
        }
    }
    return;
}