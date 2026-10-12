#include <stdio.h>
#include <string.h>

#define MAX_VE 100

struct VeMayBay {
    char maVe[16];          // Toi da 15 ky tu (+1 null-terminator)
    char tenHanhKhach[51];  // Toi da 50 ky tu (+1 null-terminator)
    char hangVe[21];        // Toi da 20 ky tu (+1 null-terminator)
    float canNangHanhLy;    // Khoi luong hanh ly (kg)
    double cuocHanhLy;      // Cuoc phi hanh ly (VND)
};

int main() {
    struct VeMayBay danhSachVe[MAX_VE];
    int N = 0;
    int i;

    // 1. Nhap so luong ve va kiem tra dieu kien 1 <= N <= 100
    printf("Nhap so luong ve may bay: ");
    if (scanf("%d", &N) != 1 || N < 1 || N > MAX_VE) {
        printf("Loi: So luong ve phai nam trong khoang [1, %d]!\n", MAX_VE);
        return 1;
    }
    while (getchar() != '\n'); // Don sach bo dem sau khi scanf

    // 2. Nhap danh sach ve & 3. Tinh cuoc hanh ly tu dong
    for (i = 0; i < N; i++) {
        printf("\n--- Nhap thong tin ve thu %d ---\n", i + 1);

        printf("Ma ve PNR: ");
        scanf("%15s", danhSachVe[i].maVe);
        while (getchar() != '\n'); // Don bo dem truoc khi fgets

        printf("Ho ten hanh khach: ");
        fgets(danhSachVe[i].tenHanhKhach, sizeof(danhSachVe[i].tenHanhKhach), stdin);
        danhSachVe[i].tenHanhKhach[strcspn(danhSachVe[i].tenHanhKhach, "\n")] = '\0';

        printf("Hang ve (Business/Deluxe/Eco): ");
        scanf("%20s", danhSachVe[i].hangVe);
        while (getchar() != '\n');

        // Kiem chuan canNangHanhLy >= 0
        do {
            printf("Khoi luong hanh ly ky gui (kg): ");
            scanf("%f", &danhSachVe[i].canNangHanhLy);
            while (getchar() != '\n');
            if (danhSachVe[i].canNangHanhLy < 0.0f) {
                printf("Loi: Khoi luong hanh ly phai la so khong am! Vui long nhap lai.\n");
            }
        } while (danhSachVe[i].canNangHanhLy < 0.0f);

        // Quy tac tinh phi cuoc
        if (strcmp(danhSachVe[i].hangVe, "Business") == 0) {
            if (danhSachVe[i].canNangHanhLy <= 20.0f) {
                danhSachVe[i].cuocHanhLy = 0.0;
            } else {
                danhSachVe[i].cuocHanhLy = (double)(danhSachVe[i].canNangHanhLy - 20.0f) * 50000.0;
            }
        } else {
            // Eco hoac Deluxe
            danhSachVe[i].cuocHanhLy = (double)danhSachVe[i].canNangHanhLy * 50000.0;
        }
    }

    // 4. Hien thi danh sach dang bang va tinh tong cuoc, tim ve nang nhat
    double tongCuoc = 0.0;
    int indexMax = 0;

    printf("\n================================== DANH SACH VE MAY BAY CHUYEN BAY ==================================\n");
    printf("%-5s %-12s %-25s %-12s %12s %15s\n", 
           "STT", "MA VE", "HO TEN HANH KHACH", "HANG VE", "HANH LY (KG)", "CUOC PHI (VND)");
    printf("----------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < N; i++) {
        tongCuoc += danhSachVe[i].cuocHanhLy;
        if (danhSachVe[i].canNangHanhLy > danhSachVe[indexMax].canNangHanhLy) {
            indexMax = i;
        }

        printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n", 
               i + 1, 
               danhSachVe[i].maVe, 
               danhSachVe[i].tenHanhKhach, 
               danhSachVe[i].hangVe, 
               danhSachVe[i].canNangHanhLy, 
               danhSachVe[i].cuocHanhLy);
    }
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("Tong tien cuoc hanh ly toan chuyen: %.0f VND\n", tongCuoc);
    printf("Ve co hanh ly ky gui nang nhat: %s - %s (%.1f kg)\n", 
           danhSachVe[indexMax].maVe, 
           danhSachVe[indexMax].tenHanhKhach, 
           danhSachVe[indexMax].canNangHanhLy);

    // 5. Cap nhat thong tin hanh ly
    char pnrTimKiem[16];
    int timThayIndex = -1;

    printf("\n--- CAP NHAT THONG TIN HANH LY ---\n");
    printf("Nhap ma ve PNR can tim: ");
    scanf("%15s", pnrTimKiem);
    while (getchar() != '\n');

    for (i = 0; i < N; i++) {
        if (strcmp(danhSachVe[i].maVe, pnrTimKiem) == 0) {
            timThayIndex = i;
            break;
        }
    }

    if (timThayIndex != -1) {
        do {
            printf("Nhap can nang hanh ly ky gui moi (kg): ");
            scanf("%f", &danhSachVe[timThayIndex].canNangHanhLy);
            while (getchar() != '\n');
            if (danhSachVe[timThayIndex].canNangHanhLy < 0.0f) {
                printf("Loi: Khoi luong hanh ly phai la so khong am! Vui long nhap lai.\n");
            }
        } while (danhSachVe[timThayIndex].canNangHanhLy < 0.0f);

        // Tinh lai cuoc hanh ly
        if (strcmp(danhSachVe[timThayIndex].hangVe, "Business") == 0) {
            if (danhSachVe[timThayIndex].canNangHanhLy <= 20.0f) {
                danhSachVe[timThayIndex].cuocHanhLy = 0.0;
            } else {
                danhSachVe[timThayIndex].cuocHanhLy = (double)(danhSachVe[timThayIndex].canNangHanhLy - 20.0f) * 50000.0;
            }
        } else {
            danhSachVe[timThayIndex].cuocHanhLy = (double)danhSachVe[timThayIndex].canNangHanhLy * 50000.0;
        }

        printf("Tim thay ma ve %s. Da cap nhat cuoc hanh ly moi: %.0f VND.\n", 
               danhSachVe[timThayIndex].maVe, 
               danhSachVe[timThayIndex].cuocHanhLy);

        // In lai bang danh sach sau khi cap nhat
        printf("\n================================ DANH SACH VE MAY BAY SAU CAP NHAT ================================\n");
        printf("%-5s %-12s %-25s %-12s %12s %15s\n", 
               "STT", "MA VE", "HO TEN HANH KHACH", "HANG VE", "HANH LY (KG)", "CUOC PHI (VND)");
        printf("----------------------------------------------------------------------------------------------------\n");
        for (i = 0; i < N; i++) {
            printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n", 
                   i + 1, 
                   danhSachVe[i].maVe, 
                   danhSachVe[i].tenHanhKhach, 
                   danhSachVe[i].hangVe, 
                   danhSachVe[i].canNangHanhLy, 
                   danhSachVe[i].cuocHanhLy);
        }
        printf("----------------------------------------------------------------------------------------------------\n");
    } else {
        printf("Khong tim thay ma ve PNR nay trong he thong!\n");
    }

    return 0;
}