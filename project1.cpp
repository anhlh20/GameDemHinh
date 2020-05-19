#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
int hinhVuong=0,hinhTron=0,hinhTamGiac=0;
int timeGame=9;
struct diem{
	int x;
	int y;
};
typedef struct diem DIEM;
struct hinh {
	int id;
	DIEM diemGoc;
	int kichThuoc;
};
typedef struct hinh HINH;
struct danhsach{
	int n;
	HINH h[100];
};
typedef struct danhsach DS;
//DDA ve doan thang noi 2 diem
void veDoanThang(DIEM A,DIEM B,int color){
    int Dx = B.x-A.x, Dy=B.y-A.y;
    float x_inc , y_inc;
	float step=(abs(Dx)>=abs(Dy)?abs(Dx):abs(Dy));
    x_inc=Dx/step;
    y_inc=Dy/step;
	float x=A.x,y=A.y;
	putpixel(x, y, color);
      
    int k=1;
    while(k <=step){
        k++;
        x += x_inc;
        y += y_inc;
        putpixel(round(x),round(y),color);
	} 
}
//thuat toan ve hinh vuong
void veHinhVuong(DIEM A, int kichThuoc, int color){
	DIEM B,C,D;
	B.y=A.y;
	B.x=A.x+kichThuoc;
	C.x=A.x;
	C.y=A.y+kichThuoc;
	D.x=A.x+kichThuoc;
	D.y=A.y+kichThuoc;
	veDoanThang(A,B,color);
	veDoanThang(B,D,color);
	veDoanThang(C,D,color);
	veDoanThang(C,A,color);
} 
void put8pixel(DIEM M, DIEM O,int color) {
    putpixel( M.x+O.x , M.y+O.y, color);
    putpixel(-M.x+O.x , M.y+O.y, color);
    putpixel( M.x+O.x ,-M.y+O.y, color);
    putpixel(-M.x+O.x ,-M.y+O.y, color);
    putpixel( M.y+O.x , M.x+O.y, color);
	putpixel(-M.y+O.x , M.x+O.y, color);
	putpixel( M.y+O.x ,-M.x+O.y, color);
	putpixel(-M.y+O.x ,-M.x+O.y, color);
}
void veHinhTron(DIEM O, int duongKinh, int color){
    DIEM M;
    int banKinh = duongKinh/2;
	for(M.x=0;M.x<=round(banKinh*sqrt(2)/2);M.x++){
    	M.y=round(sqrt(banKinh*banKinh - M.x*M.x));
    	put8pixel(M,O,color);
		}
}  
//ve hinh tam giac can
void veHinhTamGiac(DIEM A,int kichThuoc , int color){
	DIEM B,C;
	B.x=A.x+kichThuoc;
	B.y=A.y;
	C.x=A.x+kichThuoc/2;
	C.y=A.y-kichThuoc;
	
	veDoanThang(A,B, color);
	veDoanThang(B,C, color);
	veDoanThang(C,A, color);
}
void veHinh(DS &ds){
//	ds.n=10;
	for(int i=0;i<ds.n;i++){
		
		ds.h[i].diemGoc.x = rand()%700;
	    ds.h[i].diemGoc.y = rand()%550 + 100;	
		ds.h[i].id = (-1)* (rand()%3 + 1);  //id={-1,-2,-3}
		ds.h[i].kichThuoc = (rand()%5 + 4)*10;//kichThuoc={40,50,60,70,80}
		if(ds.h[i].id == -1){
			veHinhVuong(ds.h[i].diemGoc,ds.h[i].kichThuoc,4);
		}
		else if(ds.h[i].id == -2){
			veHinhTron(ds.h[i].diemGoc,ds.h[i].kichThuoc,5);
		}
		else {
			veHinhTamGiac(ds.h[i].diemGoc,ds.h[i].kichThuoc,6);	
		}
	}
}

bool xuLyHinhVuong(DIEM M, DIEM A, int kichThuoc){
	if (M.x >= A.x && M.x <= A.x+kichThuoc && M.y >= A.y && M.y <= A.y+kichThuoc){
		veHinhVuong(A,kichThuoc,0);
		return true;
	}
	return false;
}
double khoangCach(DIEM A, DIEM B){
	return sqrt(pow((B.x-A.x),2) + pow((B.y-A.y),2));
}
bool xuLyHinhTron(DIEM M, DIEM O, int duongKinh){
	int banKinh = duongKinh/2;
	if (khoangCach(M,O) <= banKinh) {
		veHinhTron(O,duongKinh,0);
		return true;
	}
	return false;
}

//ham tinh dien tich tam giac theo cong thuc Herong
float dienTich(DIEM A, DIEM B, DIEM C){
	double canhA=khoangCach(A,B);
	double canhB=khoangCach(B,C);
	double canhC=khoangCach(C,A);
	double p = (canhA+canhB+canhC)/2; // p la nua chu vi
	return sqrt(p*(p-canhA)*(p-canhB)*(p-canhC));
}

bool xuLyTamGiac (DIEM M, DIEM A, int kichThuoc){
	DIEM B,C;
	B.x=A.x+kichThuoc;
	B.y=A.y;
	C.x=A.x+kichThuoc/2;
	C.y=A.y-kichThuoc;
	long s =  dienTich(A,B,C);
	long s1 = dienTich(M,A,B) + dienTich(M,B,C) + dienTich(M,A,C);
	if(s1 == s) {
		veHinhTamGiac(A,kichThuoc,0);
		return true;
	} 
	return false;
}
void xoa(DS &ds, int viTri){
	for(int i=viTri;i<ds.n;i++){
		ds.h[i]=ds.h[i+1];
	}
	ds.n--;
}
void xuLyClickChuot(DIEM M, DS &ds){
	for(int i=0;i<ds.n;i++){
		if(ds.h[i].id == -1){
			bool k = xuLyHinhVuong(M,ds.h[i].diemGoc,ds.h[i].kichThuoc);
			if (k == true){
				hinhVuong++;
				xoa(ds,i);	
			}
		}
		else if (ds.h[i].id == -2){
			bool k = xuLyHinhTron(M,ds.h[i].diemGoc,ds.h[i].kichThuoc);
			if(k==true){
				hinhTron++;
				xoa(ds,i);
			}
		}
		else {
			bool k = xuLyTamGiac(M,ds.h[i].diemGoc,ds.h[i].kichThuoc);
			if(k == true){
				hinhTamGiac++;
				xoa(ds,i);
			}
		}
	}
}

int main(){
	srand (time(NULL));
	//khoi dong che do do hoa
	initwindow(950, 700);			
	setbkcolor(0);					
   	cleardevice();
   	
	setcolor(7);	
	settextstyle(8, 0, 2);					
	outtextxy(300,10, "WELCOME TO THE GAME ");
	
	//sinh ngau nhien cac hinh 
	DS ds;
	ds.n=15;
	veHinh(ds);
	
	//xu ly click chuot
	DIEM M;
    char digit[100];
    outtextxy(700,50, "Time: ");
	
	while(!kbhit()){
		if(timeGame >= 0){
			if(ismouseclick(WM_LBUTTONDOWN)){
				getmouseclick(WM_LBUTTONDOWN, M.x, M.y);//lay toa do click chuot
				xuLyClickChuot(M,ds);
			}
			for(int i = timeGame;i>=0;i--){
				sprintf(digit,"%d",timeGame);
				outtextxy(760,50, digit);
			}
//			if(timeGame % 1000 == 0){
//				sprintf(digit,"%d",(timeGame)/1000);
//				outtextxy(760,50, digit);
//			}
		}
		else{
			for(int i=0;i<ds.n;i++){
				if(ds.h[i].id == -1){
					veHinhVuong(ds.h[i].diemGoc,ds.h[i].kichThuoc,0);
					xoa(ds,i);
				}
				else if(ds.h[i].id == -2){
					veHinhTron(ds.h[i].diemGoc,ds.h[i].kichThuoc,0);
					xoa(ds,i);
				}
				else {
					veHinhTamGiac(ds.h[i].diemGoc,ds.h[i].kichThuoc,0);	
					xoa(ds,i);
				}
			}
		
			outtextxy(700,70, "Hinh Tron: ");
			outtextxy(700,90, "Hinh Vuong: ");
			outtextxy(700,110, "Hinh Tam Giac: ");
			
			sprintf(digit,"%d",hinhTron); outtextxy(880,70, digit);
			sprintf(digit,"%d",hinhVuong); outtextxy(880,90, digit);
			sprintf(digit,"%d",hinhTamGiac); outtextxy(880,110, digit);
		}

		timeGame -=1;
		delay(1000);
	}
	/*
	while(!kbhit()){
		if(ismouseclick(WM_LBUTTONDOWN)){
				getmouseclick(WM_LBUTTONDOWN, M.x, M.y);//lay toa do click chuot
				xuLyClickChuot(M,ds);
	}
			outtextxy(700,70, "Hinh Tron: ");
			outtextxy(700,90, "Hinh Vuong: ");
			outtextxy(700,110, "Hinh Tam Giac: ");
			
			sprintf(digit,"%d",hinhTron); outtextxy(880,70, digit);
			sprintf(digit,"%d",hinhVuong); outtextxy(880,90, digit);
			sprintf(digit,"%d",hinhTamGiac); outtextxy(880,110, digit);
}
	*/
	getch();
	closegraph();
	return 0;
}
