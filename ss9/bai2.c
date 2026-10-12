#include <stdio.h>
#include <string.h>

struct FlightTicket {
    char pnrCode[15];
    char passengerName[50];
    int ticketClass;      // 1: Eco, 2: Deluxe, 3: Business
    float baggageWeight;  // kg
    float baggageFee;     // VND
};

int main() {
    struct FlightTicket danhSachVe[100];
    int soLuong = 0;
    int luaChon;
    int i, j;
    char pnrTimKiem[15];
    int timThayIndex;

    do {
        printf("\n=== HE THONG BAN VE VA CHECK-IN MAY BAY ===\n");
        printf("1. Them ve may bay moi\n");
        printf("2. Hien thi danh sach ve\n");
        printf("3. Cap nhat hanh ly theo PNR\n");
        printf("4. Xoa ve theo PNR\n");
        printf("5. Thoat\n");
        printf("Lua chon cua ban: ");
        
        if (scanf("%d", &luaChon) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n'); // Don bo dem sau khi doc lua chon

        switch (luaChon) {
            case 1: {
                if (soLuong >= 100) {
                    printf("Danh sach ve da day, khong the them moi!\n");
                    break;
                }

                printf("\n--- THEM VE MAY BAY MOI ---\n");
                printf("Nhap ma PNR: ");
                scanf("%14s", danhSachVe[soLuong].pnrCode);
                while (getchar() != '\n'); // Don bo dem truoc khi fgets

                printf("Nhap ho ten hanh khach: ");
                fgets(danhSachVe[soLuong].passengerName, sizeof(danhSachVe[soLuong].passengerName), stdin);
                danhSachVe[soLuong].passengerName[strcspn(danhSachVe[soLuong].passengerName, "\n")] = '\0';

                do {
                    printf("Nhap hang ve (1-Eco, 2-Deluxe, 3-Business): ");
                    scanf("%d", &danhSachVe[soLuong].ticketClass);
                    while (getchar() != '\n');
                    if (danhSachVe[soLuong].ticketClass < 1 || danhSachVe[soLuong].ticketClass > 3) {
                        printf("Hang ve khong hop le! Vui long nhap lai (1, 2 hoac 3).\n");
                    }
                } while (danhSachVe[soLuong].ticketClass < 1 || danhSachVe[soLuong].ticketClass > 3);

                printf("Nhap khoi luong hanh ly (kg): ");
                scanf("%f", &danhSachVe[soLuong].baggageWeight);
                while (getchar() != '\n');

                // Tinh phi hanh ly qua cuoc
                if (danhSachVe[soLuong].ticketClass == 3) {
                    danhSachVe[soLuong].baggageFee = 0.0f;
                } else {
                    if (danhSachVe[soLuong].baggageWeight <= 7.0f) {
                        danhSachVe[soLuong].baggageFee = 0.0f;
                    } else {
                        danhSachVe[soLuong].baggageFee = (danhSachVe[soLuong].baggageWeight - 7.0f) * 50000.0f;
                    }
                }

                printf("=> Them ve thanh cong! Cuoc phat hanh ly qua can: %.0f VND.\n", danhSachVe[soLuong].baggageFee);
                soLuong++;
                break;
            }

            case 2: {
                if (soLuong == 0) {
                    printf("Danh sach ve dang rong!\n");
                    break;
                }

                printf("\n========================================================================================\n");
                printf("%-4s | %-10s | %-25s | %-10s | %-12s | %-15s\n", 
                       "STT", "Ma PNR", "Ho ten hanh khach", "Hang ve", "Hanh ly (kg)", "Cuoc qua cuoc");
                printf("========================================================================================\n");

                for (i = 0; i < soLuong; i++) {
                    char tenHangVe[15];
                    if (danhSachVe[i].ticketClass == 1) {
                        strcpy(tenHangVe, "Eco");
                    } else if (danhSachVe[i].ticketClass == 2) {
                        strcpy(tenHangVe, "Deluxe");
                    } else {
                        strcpy(tenHangVe, "Business");
                    }

                    printf("%-4d | %-10s | %-25s | %-10s | %-12.1f | %.0f VND\n",
                           i + 1,
                           danhSachVe[i].pnrCode,
                           danhSachVe[i].passengerName,
                           tenHangVe,
                           danhSachVe[i].baggageWeight,
                           danhSachVe[i].baggageFee);
                }
                printf("========================================================================================\n");
                break;
            }

            case 3: {
                if (soLuong == 0) {
                    printf("Danh sach ve dang rong!\n");
                    break;
                }

                printf("Nhap ma PNR can cap nhat hanh ly: ");
                scanf("%14s", pnrTimKiem);
                while (getchar() != '\n');

                timThayIndex = -1;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(danhSachVe[i].pnrCode, pnrTimKiem) == 0) {
                        timThayIndex = i;
                        break;
                    }
                }

                if (timThayIndex != -1) {
                    printf("Tim thay hanh khach: %s\n", danhSachVe[timThayIndex].passengerName);
                    printf("Nhap trong luong hanh ly moi (kg): ");
                    scanf("%f", &danhSachVe[timThayIndex].baggageWeight);
                    while (getchar() != '\n');

                    // Tinh lai cuoc phu thu
                    if (danhSachVe[timThayIndex].ticketClass == 3) {
                        danhSachVe[timThayIndex].baggageFee = 0.0f;
                    } else {
                        if (danhSachVe[timThayIndex].baggageWeight <= 7.0f) {
                            danhSachVe[timThayIndex].baggageFee = 0.0f;
                        } else {
                            danhSachVe[timThayIndex].baggageFee = (danhSachVe[timThayIndex].baggageWeight - 7.0f) * 50000.0f;
                        }
                    }
                    printf("=> Cap nhat thanh cong! Phi hanh ly qua cuoc moi: %.0f VND.\n", danhSachVe[timThayIndex].baggageFee);
                } else {
                    printf("Khong tim thay ve co ma PNR da nhap!\n");
                }
                break;
            }

            case 4: {
                if (soLuong == 0) {
                    printf("Danh sach ve dang rong!\n");
                    break;
                }

                printf("Nhap ma PNR can xoa: ");
                scanf("%14s", pnrTimKiem);
                while (getchar() != '\n');

                timThayIndex = -1;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(danhSachVe[i].pnrCode, pnrTimKiem) == 0) {
                        timThayIndex = i;
                        break;
                    }
                }

                if (timThayIndex != -1) {
                    // Don mang sang trai de xoa phan tu tai timThayIndex
                    for (j = timThayIndex; j < soLuong - 1; j++) {
                        danhSachVe[j] = danhSachVe[j + 1];
                    }
                    soLuong--;
                    printf("=> Da xoa thanh cong ve co ma PNR: %s ra khoi he thong.\n", pnrTimKiem);
                } else {
                    printf("Khong tim thay ve co ma PNR da nhap!\n");
                }
                break;
            }

            case 5:
                printf("\nCam on ban da su dung chuong trinh! Tam biet.\n");
                break;

            default:
                printf("Lua chon khong hop le! Vui long chon tu 1 den 5.\n");
                break;
        }
    } while (luaChon != 5);

    return 0;
}