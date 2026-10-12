#include <stdio.h>
#include <string.h>

struct VeMayBay {
    char maPNR[10];
    char tenHanhKhach[50];
    char hangVe[15];
    float trongLuongHanhLy;
    long phiPhuThu;
};

int main() {
    struct VeMayBay ds[50];
    int n = 0;
    int i;

    printf("=== HE THONG CHECK-IN VE MAY BAY ===\n");

    // 1. Nhap so luong ve hop le (1 <= n <= 50)
    do {
        printf("Nhap so luong ve (1 - 50): ");
        scanf("%d", &n);
        while (getchar() != '\n'); // Xoa bo dem ban phim
        if (n < 1 || n > 50) {
            printf("So luong khong hop le! Vui long nhap lai.\n");
        }
    } while (n < 1 || n > 50);

    // 2. Nhap danh sach ve va 3. Tinh phi phu thu
    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin ve thu %d ---\n", i + 1);

        // Nhap ma PNR
        printf("Nhap ma PNR: ");
        fgets(ds[i].maPNR, sizeof(ds[i].maPNR), stdin);
        ds[i].maPNR[strcspn(ds[i].maPNR, "\n")] = '\0'; // Xoa ky tu '\n' thua

        // Nhap ho ten hanh khach
        printf("Nhap ho ten hanh khach: ");
        fgets(ds[i].tenHanhKhach, sizeof(ds[i].tenHanhKhach), stdin);
        ds[i].tenHanhKhach[strcspn(ds[i].tenHanhKhach, "\n")] = '\0';

        // Nhap hang ve
        printf("Nhap hang ve (Eco/Deluxe/Business): ");
        fgets(ds[i].hangVe, sizeof(ds[i].hangVe), stdin);
        ds[i].hangVe[strcspn(ds[i].hangVe, "\n")] = '\0';

        // Nhap trong luong hanh ly
        printf("Nhap trong luong hanh ly (kg): ");
        scanf("%f", &ds[i].trongLuongHanhLy);
        while (getchar() != '\n'); // Don sach bo dem sau khi dung scanf

        // Tinh phi phu thu theo quy tac nghiep vu
        if (ds[i].trongLuongHanhLy > 7.0f) {
            ds[i].phiPhuThu = (long)((ds[i].trongLuongHanhLy - 7.0f) * 50000);
        } else {
            ds[i].phiPhuThu = 0;
        }
    }

    // 4. Xuat danh sach ve dang bang
    printf("\n=== DANH SACH VE MAY BAY CHUYEN BAY ===\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("%-5s %-10s %-25s %-12s %-14s %-15s\n", 
           "STT", "MA PNR", "HO TEN HANH KHACH", "HANG VE", "HANH LY(KG)", "PHI PHU THU(VND)");
    printf("-----------------------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-5d %-10s %-25s %-12s %-14.1f %-15ld\n", 
               i + 1, 
               ds[i].maPNR, 
               ds[i].tenHanhKhach, 
               ds[i].hangVe, 
               ds[i].trongLuongHanhLy, 
               ds[i].phiPhuThu);
    }
    printf("-----------------------------------------------------------------------------------------\n");

    // 5. Tim kiem va cap nhat trong luong hanh ly
    char pnrTimKiem[10];
    int timThayIndex = -1;

    printf("\n=== CAP NHAT THONG TIN HANH LY ===\n");
    printf("Nhap ma PNR can cap nhat: ");
    fgets(pnrTimKiem, sizeof(pnrTimKiem), stdin);
    pnrTimKiem[strcspn(pnrTimKiem, "\n")] = '\0';

    // Tim kiem tuyen tinh trong mang struct
    for (i = 0; i < n; i++) {
        if (strcmp(ds[i].maPNR, pnrTimKiem) == 0) {
            timThayIndex = i;
            break;
        }
    }

    if (timThayIndex != -1) {
        printf("Tim thay ve cua hanh khach: %s\n", ds[timThayIndex].tenHanhKhach);
        printf("Nhap trong luong hanh ly moi (kg): ");
        scanf("%f", &ds[timThayIndex].trongLuongHanhLy);
        while (getchar() != '\n'); // Don sach bo dem

        // Tinh lai phi phu thu
        if (ds[timThayIndex].trongLuongHanhLy > 7.0f) {
            ds[timThayIndex].phiPhuThu = (long)((ds[timThayIndex].trongLuongHanhLy - 7.0f) * 50000);
        } else {
            ds[timThayIndex].phiPhuThu = 0;
        }

        printf("Cap nhat thanh cong! Phi phu thu moi: %ld VND\n", ds[timThayIndex].phiPhuThu);

        // In lai bang danh sach sau khi cap nhat
        printf("\n=== DANH SACH VE MAY BAY SAU CAP NHAT ===\n");
        printf("-----------------------------------------------------------------------------------------\n");
        printf("%-5s %-10s %-25s %-12s %-14s %-15s\n", 
               "STT", "MA PNR", "HO TEN HANH KHACH", "HANG VE", "HANH LY(KG)", "PHI PHU THU(VND)");
        printf("-----------------------------------------------------------------------------------------\n");
        for (i = 0; i < n; i++) {
            printf("%-5d %-10s %-25s %-12s %-14.1f %-15ld\n", 
                   i + 1, 
                   ds[i].maPNR, 
                   ds[i].tenHanhKhach, 
                   ds[i].hangVe, 
                   ds[i].trongLuongHanhLy, 
                   ds[i].phiPhuThu);
        }
        printf("-----------------------------------------------------------------------------------------\n");
    } else {
        printf("Khong tim thay ma PNR hop le trong he thong!\n");
    }

    return 0;
}