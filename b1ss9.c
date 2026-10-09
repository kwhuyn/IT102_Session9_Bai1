#include <stdio.h>
#include <string.h>

// Định nghĩa cấu trúc VeMayBay theo đề bài
struct VeMayBay {
    char maPNR[10];
    char tenHanhKhach[50];
    char hangVe[15];
    float trongLuongHanhLy;
    long phiPhuThu;
};

int main() {
    int n;
    
    printf("=== HE THONG CHECK-IN VE MAY BAY ===\n");
    // 1. Nhập số lượng vé (1 <= n <= 50) với vòng lặp kiểm tra lỗi
    do {
        printf("Nhap so luong ve (1 - 50): ");
        if (scanf("%d", &n) != 1) {
            printf("Du lieu khong hop le! Vui long nhap lai.\n");
            while (getchar() != '\n'); // Xóa bộ đệm
            n = 0;
        } else if (n < 1 || n > 50) {
            printf("So luong ve phai tu 1 den 50! Vui long nhap lai.\n");
        }
    } while (n < 1 || n > 50);

    struct VeMayBay danhSachVe[50];

    // 2. Nhập danh sách vé máy bay
    for (int i = 0; i < n; i++) {
        printf("\n--- Nhập thông tin vé thứ %d ---\n", i + 1);
        
        printf("Nhap ma PNR: ");
        scanf("%s", danhSachVe[i].maPNR);
        while (getchar() != '\n'); // Xóa ký tự xuống dòng thừa sau scanf

        printf("Nhap ho ten hanh khach: ");
        fgets(danhSachVe[i].tenHanhKhach, sizeof(danhSachVe[i].tenHanhKhach), stdin);
        // Xóa ký tự xuống dòng '\n' do fgets thu nhận ở cuối chuỗi
        danhSachVe[i].tenHanhKhach[strcspn(danhSachVe[i].tenHanhKhach, "\n")] = '\0';

        printf("Nhap hang ve (Eco/Deluxe/Business): ");
        scanf("%s", danhSachVe[i].hangVe);
        while (getchar() != '\n');

        printf("Nhap trong luong hanh ly (kg): ");
        scanf("%f", &danhSachVe[i].trongLuongHanhLy);
        while (getchar() != '\n');

        // 3. Tự động tính phí phụ thu hành lý quá cước
        // Miễn phí tối đa 7.0 kg, vượt mức tính 50.000 VNĐ / kg
        if (danhSachVe[i].trongLuongHanhLy > 7.0f) {
            danhSachVe[i].phiPhuThu = (long)((danhSachVe[i].trongLuongHanhLy - 7.0f) * 50000);
        } else {
            danhSachVe[i].phiPhuThu = 0;
        }
    }

    // 4. Xuất danh sách vé ban đầu dạng bảng căn chỉnh cột
    printf("\n=== DANH SACH VE MAY BAY CHUYEN BAY ===\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("%-5s | %-10s | %-25s | %-12s | %-15s | %-15s\n", "STT", "MA PNR", "HO TEN HANH KHACH", "HANG VE", "HANH LY(KG)", "PHI PHU THU(VND)");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-5d | %-10s | %-25s | %-12s | %-15.1f | %-15ld\n", 
            i + 1, 
            danhSachVe[i].maPNR, 
            danhSachVe[i].tenHanhKhach, 
            danhSachVe[i].hangVe, 
            danhSachVe[i].trongLuongHanhLy, 
            danhSachVe[i].phiPhuThu);
    }
    printf("-----------------------------------------------------------------------------------------\n");

    // 5. Tìm kiếm theo mã PNR và cập nhật trọng lượng hành lý
    char searchPNR[10];
    printf("\n=== CAP NHAT THONG TIN HANH LY ===\n");
    printf("Nhap ma PNR can cap nhat: ");
    scanf("%s", searchPNR);
    while (getchar() != '\n');

    int foundIndex = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(danhSachVe[i].maPNR, searchPNR) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        printf("Tim thay ve cua hanh khach: %s\